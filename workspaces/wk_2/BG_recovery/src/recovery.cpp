#include "../inc/recovery.h"

// 参数列表
double XCEPT_S_URATE = 0.7;         // 异常判断的面积比例上界阈值
double XCEPT_S_LRATE = 0.1;         // 静止判断的面积比例下界阈值
double SCL_RATE = 0.02;             // 变动点分块的相对比例 - 相对于图片(R+C)/2
int THRE_METHOD = 50;               // 判断使用哪种复原方式
int THRE_DIFF = 5;                  // 判断帧差变动点的像素阈值
int THRE_DENSE = 200;               // 判断分块密度图中为前景的密度阈值
double BDR_WID_RATE = 0.05;         // 前景框边缘外扩的相对比例 - 相对于密度图的R_、C_
double W_UPDATE = 0.5;              // 背景部分的迭代更新比例（定值）
int FRM_SAMP = 4;                   // 抽帧比

void Recovery::readVideo(string filePath) {
    // read file
    m_capture.open(filePath);
    if (! m_capture.isOpened()) {
        cout << "Video not found" << endl;
        return;
    }

    // get video preffix name
    char *dirc = strdup(filePath.c_str());
    m_preffix_name = strtok(basename(dirc), ".");
    cout << "Video Preffix Name: " << m_preffix_name << endl;

    // get prop
    m_frame_count = m_capture.get(CAP_PROP_FRAME_COUNT);
    m_R = m_capture.get(CAP_PROP_FRAME_HEIGHT);
    m_C = m_capture.get(CAP_PROP_FRAME_WIDTH);
    m_scale = (int)(SCL_RATE * (m_R + m_C) / 2);
    m_scale_inv = 1./m_scale;
    m_R_scaled = (int)(m_scale_inv * m_R);
    m_C_scaled = (int)(m_scale_inv * m_C);
    m_area_upperbound = (int)(XCEPT_S_URATE * m_scale_inv * m_scale_inv * m_R * m_C);
    m_area_lowerbound = (int)(XCEPT_S_LRATE * m_scale_inv * m_scale_inv * m_R * m_C);
    m_border_width_R = (int)(BDR_WID_RATE * m_R * m_scale_inv);
    m_border_width_C = (int)(BDR_WID_RATE * m_C * m_scale_inv);
}

void Recovery::process() {
    auto t_start = system_clock::now();

    if (m_frame_count <= THRE_METHOD) {
        cout << "Insufficient Frames" << endl;
        recoverMode();
    }
    else {
        recoverForegroundRm();
    }

    auto t_end = system_clock::now();
    auto duration = duration_cast<microseconds>(t_end - t_start);
    m_duration = (double)(duration.count()) * microseconds::period::num / microseconds::period::den;
}

void Recovery::showResult() {
    cout << "=========== result ===========" << endl;
    // show background
    namedWindow("Result", 0);
    resizeWindow("Result", 1280, 720);
    imshow("Result", m_background);

    // save dir
    string res_path = "./result/";
    DIR *dir = opendir(res_path.c_str());
    if (!dir) {
        mkdir(res_path.c_str(), S_IRWXU);
        cout << "Result dir created" << endl;
    }
    else {
        cout << "Result dir already exits" << endl;
    }

    res_path = res_path + m_preffix_name + "_background.jpg";
    imwrite(res_path, m_background);
    cout << "Background result saved: " << res_path << endl;
    cout << "Process spent: " << m_duration << "s" << endl;

    cv::waitKey(0);
}

void Recovery::recoverForegroundRm() {
    Mat frm, bg;
    Mat frmG, preG, subG;  // Gray
    int pre_r1=0, pre_c1=0, pre_r2=0, pre_c2=0;
    m_capture >> bg;
    cvtColor(bg, frmG, COLOR_RGB2GRAY);
    preG = frmG.clone();

    // int frm_count = 1;
    while (1) {
        for (int i = 0; i < FRM_SAMP; i++) m_capture.grab();  // 抽帧
        m_capture >> frm;
        if (frm.empty()) break;

        cvtColor(frm, frmG, COLOR_RGB2GRAY);
        add(frmG-preG, preG-frmG, subG);  // 帧差

        threshold(subG, subG, THRE_DIFF, 256, THRESH_BINARY);
        resize(subG, subG, Size_<int>(0,0), m_scale_inv, m_scale_inv, INTER_AREA);  // 分块计算变动点密度

        // 确定前景框
        int r1=0, c1=0, r2=0, c2=0;

        uchar *prow = nullptr;
        for (int r = 0; r < m_R_scaled-1; r++) {
            prow = subG.ptr<uchar>(r);
            for (int c = 0; c < m_C_scaled-1; c++) {
                if (prow[c] > THRE_DENSE) {
                    if (r1 == 0) r1 = r;
                    if (c1 == 0) c1 = c;
                    r1 = min(r1, r);
                    c1 = min(c1, c);
                    r2 = max(r2, r);
                    c2 = max(c2, c);
                }
            }
        }

        // 异常检测 + 前景静止检测
        if (((r2-r1)*(c2-c1) > m_area_upperbound) ||  // 异常
            ((r2-r1)*(c2-c1) < m_area_lowerbound))    // 静止
            r1=pre_r1, c1=pre_c1, r2=pre_r2, c2=pre_c2;

        pre_r1=r1, pre_c1=c1, pre_r2=r2, pre_c2=c2;

        // 前景框外扩
        r1 = max(r1 - m_border_width_R, 0);
        c1 = max(c1 - m_border_width_C, 0);
        r2 = min(r2 + m_border_width_R, m_R_scaled);
        c2 = min(c2 + m_border_width_C, m_C_scaled);

        // 前景框掩码
        Mat mask = Mat::zeros(m_R_scaled, m_C_scaled, CV_8UC1);
        rectangle(mask, Point(c1, r1), Point(c2, r2), Scalar(255), CV_FILLED);
        resize(mask, mask, frm.size());
        bg.copyTo(frm, mask);

        // 更新背景
        addWeighted(bg, (1.-W_UPDATE), frm, W_UPDATE, 0, bg, INTER_NEAREST);

        // cout << frm_count << " ";
        // frm_count++;
        preG = frmG.clone();
    }
    m_background = bg;
}

void Recovery::recoverMode() {
    // 摩尔投票法
    Mat frm, bg, votes;
    m_capture >> bg;
    frm = bg.clone();
    vector<Mat> v_ones(3);
    for (int i = 0; i < 3; i++) 
        v_ones[i] = Mat::ones(bg.size(), CV_16SC1);
    merge(v_ones, votes);

    uchar *p_frm, *p_bg, *p_vts;
    int step = frm.step;

    while (1) {
        m_capture >> frm;
        if (frm.empty()) break;
        for (int r = 0; r < m_R; r++) {
            p_frm = frm.data + r*step;
            p_bg = bg.data + r*step;
            p_vts = votes.data + r*votes.step;
            for (int c = 0; c < m_C; c++) {
                for (int ch = 0; ch < 3; ch++) {
                    if (p_frm[ch] == p_bg[ch]) {
                        p_vts[ch] ++;
                    }
                    else if (p_vts[ch] == 0) {
                        p_bg[ch] = p_frm[ch];
                        p_vts[ch] = 1;
                    }
                    else {
                        p_vts[ch] --;
                    }
                }
                p_frm += 3;
                p_bg += 3;
                p_vts += 3;
            }
        }
    }
    m_background = bg;
}