#pragma once

#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

class ColorDetector
{
public:
	ColorDetector();
	~ColorDetector();
	cv::Mat process(const cv::Mat &image);
	void setColorDistanceTheshold(int distance);
	const int  getColorDistanceThreshold();
	void  setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
	void  setTargetColor(cv::Vec3b color);
	cv::Vec3b getTargetColor();
private:
	//最小可接受距离
	int minDist;
	//目标色
	cv::Vec3b target;
	//包含转换后的图像
	cv::Mat converted;

	int  getDistance(const cv::Vec3b& color) ;
};

