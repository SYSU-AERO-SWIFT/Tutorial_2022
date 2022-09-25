#include "../inc/recovery.h"

// 参数列表
int FRM_SAMP = 1;                   // 抽帧比
double XCEPT_S_URATE = 0.7;         // 异常判断的面积比例上界阈值
double XCEPT_S_LRATE = 0.1;         // 静止判断的面积比例下界阈值

double SCL_RATE = 0.01;             // 变动点分块的相对比例 - 相对于图片(R+C)/2
int THRE_METHOD = 50;               // 判断使用哪种复原方式
int THRE_DIFF = 5;                  // 判断帧差变动点的像素阈值
int THRE_DENSE = 200;               // 判断分块密度图中为前景的密度阈值
double BDR_WID_RATE = 0.05;         // 前景框边缘外扩的相对比例 - 相对于密度图的R_、C_
double W_UPDATE = 0.5;              // 背景部分的迭代更新比例（定值）

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
    m_R = m_capture.get(CAP_PROP_FRAME_WIDTH);
    m_C = m_capture.get(CAP_PROP_FRAME_HEIGHT);
    m_scale = (int)(SCL_RATE * (m_R + m_C) / 2);
    m_scale_inv = 1./m_scale;
    m_R_scaled = (int)(m_scale_inv * m_R);
    m_C_scaled = (int)(m_scale_inv * m_C);
    m_area_upperbound = (int)(XCEPT_S_URATE * m_scale * m_scale * m_R * m_C);
    m_area_lowerbound = (int)(XCEPT_S_LRATE * m_scale * m_scale * m_R * m_C);
    m_border_width_R = (int)(BDR_WID_RATE * m_R * m_scale);
    m_border_width_C = (int)(BDR_WID_RATE * m_C * m_scale);

    // process & time
    auto t_start = system_clock::now();
    process();
    auto t_end = system_clock::now();
    auto duration = duration_cast<microseconds>(t_end - t_start);
    m_duration = (double)(duration.count()) * microseconds::period::num / microseconds::period::den;
}

void Recovery::process() {
    cout << m_frame_count << endl;

    if (m_frame_count <= THRE_METHOD) {
        cout << "Insufficient Frames" << endl;
        recoverMode();
    }
    else {
        recoverForegroundRm();
    }
}

void Recovery::showResult() {
    cout << "=== result ===" << endl;
    // show background
    namedWindow("Result", 0);
    resizeWindow("Result", 1280, 720);
    imshow("Result", m_background);

    // save dir
    string resPath = "../result";
    DIR *dir = opendir(resPath.c_str());
    if (!dir) {
        mkdir(resPath.c_str(), S_IRWXU);
        cout << "Result Dir Created" << endl;
    }
    else {
        cout << "Result Dir Already Exits" << endl;
    }

    // background save
    imwrite(resPath + m_preffix_name + "_m_background.jpg", m_background);

    // duration output
    cout << "Process spent: " << m_duration << "s" << endl;
}

void Recovery::recoverForegroundRm() {
    Mat frm;
    Mat frmG, preG, subG;  // Gray
    int pre_r1=0, pre_c1=0, pre_r2=0, pre_c2=0;
    m_capture >> m_background;
    cvtColor(m_background, frmG, COLOR_RGB2GRAY);
    preG = frmG.clone();

    // cout << "Init..." << endl;

    int frm_count = 1;
    while (1) {
        for (int i = 0; i < FRM_SAMP; i++) m_capture >> frm;
        m_capture >> frm;
        if (frm.empty()) break;

        cvtColor(frm, frmG, COLOR_RGB2GRAY);
        add(frmG-preG, preG-frmG, subG);  // 帧差
        threshold(subG, subG, THRE_DIFF, 256, THRESH_BINARY);
        resize(subG, subG, Size_<int>(0,0), m_scale_inv, m_scale_inv, INTER_AREA);  // 计算分块中变动点密度

        // 确定前景框
        int r1=0, c1=0, r2=0, c2=0;
        uchar *prow = nullptr;
        for (int r = 0; r < m_R_scaled; r++) {
            prow = subG.ptr<uchar>(r);
            for (int c = 0; c < m_C_scaled; c++) {
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

        r1 = max(r1 - m_border_width_R, 0);
        c1 = max(c1 - m_border_width_C, 0);
        r2 = min(r2 + m_border_width_R, m_R_scaled);
        c2 = min(c2 + m_border_width_C, m_C_scaled);

        Mat mask = Mat::zeros(m_R_scaled, m_C_scaled, CV_8UC1);
        rectangle(mask, Point(c1, r1), Point(c2, r2), Scalar(255), CV_FILLED);
        resize(mask, mask, frm.size());
        Mat tmp = frm.clone();
        m_background.copyTo(tmp, mask);

        // 更新背景
        addWeighted(m_background, (1.-W_UPDATE), tmp, W_UPDATE, 0, m_background);
        
        frm_count++;
        preG = frmG.clone();
    }
}

void Recovery::recoverMode() {
    Mat frm, votes;
    m_capture >> m_background;
    frm = m_background.clone();
    vector<Mat> v_ones(3);
    for (int i = 0; i < 3; i++) 
        v_ones[i] = Mat::ones(m_background.size(), CV_64FC1);
    merge(v_ones, votes);

    // Update Background
    m_capture >> frm;
    while (! frm.empty()) {
        uchar *prow = nullptr;
        for (int r = 0; r < frm.rows; r++) {
            prow = frm.ptr<uchar>(r);

        }
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < frm.rows; i++) {
                for (int j = 0; j < frm.cols; j++) {
                    uchar pix = frm.at<Vec3b>(i, j)[c];
                    if (pix == m_background.at<Vec3b>(i, j)[c]) {
                        votes.at<Vec3d>(i, j)[c] ++;
                    }
                    else if (votes.at<Vec3d>(i, j)[c] == 0) {
                        m_background.at<Vec3b>(i, j)[c] = pix;
                        votes.at<Vec3d>(i, j)[c] = 1;
                    }
                    else {
                        votes.at<Vec3d>(i, j)[c] --;
                    }
                }
            }
        }
        m_capture >> frm;
    }
}