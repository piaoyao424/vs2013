#include "ColorDetector.h"

ColorDetector::ColorDetector()
{
	target[0] = target[1] = target[2] = 0;
	minDist = 100;
}


ColorDetector::~ColorDetector()
{
}

void ColorDetector::setColorDistanceTheshold(int distance)
{
	if (distance<0)
	{
		minDist = 0;
	}
	else
	{
		minDist = distance;
	}
}

const int ColorDetector::getColorDistanceThreshold()
{
	return minDist;
}

void ColorDetector::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
	////BGR
	//target[2] = red;
	//target[1] = green;
	//target[0] = blue;

	//临时的1px图像
	cv::Mat tmp(1,1,CV_8UC3);
	tmp.at<cv::Vec3b>(0, 0)[0] = blue;
	tmp.at<cv::Vec3b>(0, 0)[1] = green;
	tmp.at<cv::Vec3b>(0, 0)[2] = red;
	//转换目标色到Lab颜色空间
	cv::cvtColor(tmp, tmp, CV_BGR2Lab);
	target = tmp.at<cv::Vec3b>(0,0);
}

void ColorDetector::setTargetColor(cv::Vec3b color)
{
	target = color;
}

cv::Vec3b ColorDetector::getTargetColor()
{
	return target;
}

cv::Mat ColorDetector::process(const cv::Mat &image)
{
	//按需重新分配 二值图像，与输入图像尺寸相同，但只有一个通道
	cv::Mat result;
	result.create(image.rows, image.cols, CV_8U);
	//按需重新分配中间图像
	converted.create(image.rows, image.cols, image.type());
	//转换到Lab颜色空间
	cv::cvtColor(image, converted, CV_BGR2Lab);

	//创建迭代器
	cv::Mat_<cv::Vec3b>::const_iterator it = converted.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = converted.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	//处理像素
	for (; it != itend; ++it, ++itout)
	{
		if (getDistance(*it) < minDist)
		{
			*itout = 255;
		}
		else
		{
			*itout = 0;
		}
	}


	return result;
}

int  ColorDetector::getDistance(const cv::Vec3b& color)
{
	return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0] - target[0] + color[1] - target[1] + color[2] - target[2]))) ;
}