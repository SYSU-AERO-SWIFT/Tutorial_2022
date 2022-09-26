#pragma once
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
class Recovery {

public:
    /* readVideo
    * @param filePath �ļ�����·��
    * ���ݾ���·����ȡ��Ҫ��ԭ�������ļ�
    */
    void readVideo(String filePath);

    /* process
    * ���л�ԭ����
    */
    void process();

    /* showResult
    * ����չʾ������ԭ��Ľ��
    */
    void showResult();
private:
    Mat frame;//ÿһ֡
    Mat ans;//��
    vector<vector<unordered_map<uchar, int>>> picture[3];//����������ͨ����ÿһ֡ÿһ�����ص����ɫ���ִ���
    vector<vector<pair<uchar, int>>> res[3];//�����ͨ����ÿһ֡ÿһ�����ص����ɫ���ִ������Ľ��
    int height = 0;//ÿһ֡�ĸ�
    int width = 0;//ÿһ֡�Ŀ�
    int frame_count = 0;//��Ƶ��֡��
};
