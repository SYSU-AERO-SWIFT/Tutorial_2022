#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>

using namespace cv;
using namespace std;
using namespace chrono;


class Recovery {
    public:
        void readVideo(string filePath);
        void process();
        void showResult();

    private:
        void recoverMode();
        void recoverForegroundRm();

        // 内置对象
        string m_preffix_name;
        VideoCapture m_capture;
        Mat m_background;

        // 属性值
        int m_R;
        int m_C;
        int m_R_scaled;
        int m_C_scaled;
        int m_frame_count;
        double m_duration;
        int m_scale;
        double m_scale_inv;
        int m_border_width_R;
        int m_border_width_C;
        int m_area_upperbound;
        int m_area_lowerbound;
};