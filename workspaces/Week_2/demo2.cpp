#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include <chrono>
#include <thread>
using namespace std;

int main( int argc, char** argv )
{
	//声明IplImage图像指针
	IplImage* pFrame  = NULL; 
	IplImage* pFrameR = NULL; 
	IplImage* pFrameG = NULL; 
	IplImage* pFrameB = NULL;  
	IplImage* BackgroundFrame = NULL;
	
	//开辟vector容器存放CvMat矩阵指针
	vector<CvMat*> pFrameMatR(40, NULL);
	vector<CvMat*> pFrameMatG(40, NULL);
	vector<CvMat*> pFrameMatB(40, NULL);
	vector<float> vec;
	
	//声明CvMat矩阵指针
	CvMat* pEndR = NULL;
	CvMat* pEndG = NULL;
	CvMat* pEndB = NULL;
	
	CvCapture* pCapture = NULL;
	
	if( argc != 2 ) {
		fprintf(stderr, "Usage: bkgrd [video_file_name]\n");
		fprintf(stderr, "Usage: bkgrd\n");
		return -1;
	}
	else
		if( !(pCapture = cvCaptureFromFile(argv[1]))) {
			fprintf(stderr, "Can not open video file %s\n", argv[1]);
			return -2;
		}

	chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
	
	try	{
		int count = 0;
		//读入视频 
		int Number_frame = 0;
		while(Number_frame < 120 && (pFrame = cvQueryFrame( pCapture )))
		{	
			Number_frame ++;
			if(Number_frame % 3 != 0) 
				continue; 
			if(count == 0) {
				pFrame = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, pFrame->nChannels);
				BackgroundFrame = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, pFrame->nChannels);
				pFrameR = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);
				pFrameG = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);
				pFrameB = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);
				
				pEndR = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
				pEndG = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
				pEndB = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			}
			
			//初始化矩阵 
			pFrameMatR[count] = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrameMatG[count] = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrameMatB[count] = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			
			//RGB图像分离成单通道图像再处理
			cvSplit(pFrame, pFrameR, pFrameG, pFrameB, 0); 
			
			//cvConvert函数用于图像和矩阵之间的相互转换 
			cvConvert(pFrameR, pFrameMatR[count]);
			cvConvert(pFrameG, pFrameMatG[count]);
			cvConvert(pFrameB, pFrameMatB[count]);
			
			count++;
		}
		while(pFrame = cvQueryFrame( pCapture )) ;
		//遍历寻找想要的像素
		int i, j, k;
		for(j = 0;j < pFrameMatR[0]->rows; ++ j) {
			for(k = 0;k < pFrameMatR[0]->cols; ++ k) {
				for(i = 0;i < count; ++ i)
					vec.push_back(pFrameMatR[i]->data.fl[j*pFrameMatR[0]->cols+k]);
				sort(vec.begin(), vec.end());
				pEndR->data.fl[j*pFrameMatR[0]->cols+k] = vec[count/2];
				vec.clear();
			}
		}
		
		for(j = 0;j < pFrameMatG[0]->rows; ++ j) {
			for(k = 0;k < pFrameMatG[0]->cols; ++ k) {
				for(i = 0;i < count; ++ i)
					vec.push_back(pFrameMatG[i]->data.fl[j*pFrameMatG[0]->cols+k]);
				sort(vec.begin(), vec.end());
				pEndG->data.fl[j*pFrameMatG[0]->cols+k] = vec[count/2];
				vec.clear();
			}
		}
		
		for(j = 0;j < pFrameMatB[0]->rows; ++ j) {
			for(k = 0;k < pFrameMatB[0]->cols; ++ k) {
				for(i = 0;i < count; ++ i)
					vec.push_back(pFrameMatB[i]->data.fl[j*pFrameMatB[0]->cols+k]);
				sort(vec.begin(), vec.end());
				pEndB->data.fl[j*pFrameMatB[0]->cols+k] = vec[count/2];
				vec.clear();
			}
		}
		
		cvConvert(pEndR, pFrameR);
		cvConvert(pEndG, pFrameG);
		cvConvert(pEndB, pFrameB);
		
		cvMerge(pFrameR, pFrameG, pFrameB, 0, BackgroundFrame);
		
	}
	catch(cv::Exception& e) {
		std::cout<<e.what()<<std::endl;
	}
	cvNamedWindow("background",CV_WINDOW_NORMAL);
	cvResizeWindow("background", 960, 720);
	cvShowImage("background", BackgroundFrame);
	
	chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();

   	chrono::duration<double> elapsed = end - start;
    	cout << "Elapsed time: " << elapsed.count() << "s" << endl;
    
	cvWaitKey(0);
	cvDestroyWindow("background");

	cvReleaseImage(&pFrame);
	cvReleaseImage(&pFrameR);
	cvReleaseImage(&pFrameG);
	cvReleaseImage(&pFrameB);
	cvReleaseImage(&BackgroundFrame);	
	
	cvReleaseMat(&pEndR);
	cvReleaseMat(&pEndG);
	cvReleaseMat(&pEndB);
	
	pFrameMatR.clear();
	pFrameMatG.clear();
	pFrameMatB.clear();
	
	cvReleaseCapture(&pCapture);
 
	return 0;
}
