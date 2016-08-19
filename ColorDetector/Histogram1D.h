#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Histogram1D
{
public:
	Histogram1D();
	~Histogram1D();

	//����1Dֱ��ͼ
	cv::MatND  getHistogram(const cv::Mat &image);
	cv::Mat  getHistogramImage(const cv::Mat &image);

private:
	int HistSize[1];
	float hranges[2];  //���������Сֵ
	const float*ranges[1];
	int channels[1];
};

