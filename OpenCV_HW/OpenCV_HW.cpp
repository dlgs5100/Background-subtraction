#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
using namespace cv;
IplImage* frame = NULL;
IplImage* frame_last = NULL;
IplImage* frame_diff = NULL;
IplImage* frame_mask = NULL; //cvCreateImage();

void mouseHandler(int event, int x, int y, int flags, void* param)
{
	CvScalar s;

	switch (event) {
	case CV_EVENT_LBUTTONDOWN:
		if (frame != NULL)
		{
			s = cvGet2D(frame, frame->height - y - 1, x);
			std::cout << " B= " << s.val[0]
				<< " G= " << s.val[1]
				<< " R= " << s.val[2] << " ("
				<< x << "," << y << ")\n";
		}
		if (frame_diff != NULL)
		{
			s = cvGet2D(frame_diff, frame_diff->height - y - 1, x);
			std::cout << " B= " << s.val[0]
				<< " G= " << s.val[1]
				<< " R= " << s.val[2] << " ("
				<< x << "," << y << ") d\n";
		}
		break;

	case CV_EVENT_LBUTTONUP:
		//printf("Left button up\n");
		break;
	}
}

void VideoCaptureTest()
{
	VideoCapture video(0);
	if (!video.isOpened()) {
		printf("No image");
	}
	else
	{
		printf("VideoCapture worked");
	}
	Size videoSize = Size((int)video.get(CV_CAP_PROP_FRAME_WIDTH), (int)video.get(CV_CAP_PROP_FRAME_HEIGHT));
	namedWindow("test", 1);
	namedWindow("diff", 2);
	Mat videoFrame;
	Mat videoFrame_init;
	Mat videoFrame_diff;

	while (true) {
		video >> videoFrame;
		if (videoFrame.empty())
		{
			break;
		}
		else
		{
			flip(videoFrame, videoFrame, 1);
		}
		if (!videoFrame_init.empty())
		{
			videoFrame_diff = videoFrame - videoFrame_init;
		}
		else 
		{
			waitKey(10);
			videoFrame_init = videoFrame.clone();
		}
		imshow("test", videoFrame);
		if (!videoFrame_diff.empty())
		{
			imshow("diff", videoFrame_diff);
		}
		waitKey(10);
		
	}

}

int main()
{
	VideoCaptureTest();

	cvReleaseImage(&frame_last);
	cvReleaseImage(&frame_diff);
	cvDestroyWindow("test");
	cvDestroyWindow("diff");

	return 0;
}
