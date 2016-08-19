#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Histogram1D
{
public:
	Histogram1D();
	~Histogram1D();

	//计算1D直方图
	cv::MatND  getHistogram(const cv::Mat &image);
	cv::Mat  getHistogramImage(const cv::Mat &image);

private:
	int HistSize[1];
	float hranges[2];  //保存最大最小值
	const float*ranges[1];
	int channels[1];
};

