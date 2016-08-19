#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ColorHistogram
{
public:
	ColorHistogram();
	~ColorHistogram();

	//����1Dֱ��ͼ
	cv::MatND  getHistogram(const cv::Mat &image);
	cv::Mat  getHistogramImage(const cv::Mat &image);
	cv::SparseMat getSparseHistogram(const cv::Mat &image);

private:
	int HistSize[3];
	float hranges[2];  //���������Сֵ
	const float*ranges[3];
	int channels[3];
};


