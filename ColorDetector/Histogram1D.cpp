#include "Histogram1D.h"


Histogram1D::Histogram1D()
{
	HistSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = hranges;
	channels[0] = 0;
}


Histogram1D::~Histogram1D()
{
}

cv::MatND Histogram1D::getHistogram(const cv::Mat &image)
{
		cv::MatND hist;
		//计算直方图
		cv::calcHist(&image,
			1,							//计算单张图像的直方图
			channels,			//通道数量
			cv::Mat(),			//	不使用图像作为掩码
			hist,					//返回的直方图
			1,							//这是1D的直方图
			HistSize,				//项的数量
			ranges				//像素值的范围
			);
		return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat &image)
{
	cv::MatND hist = getHistogram(image);
	//获取最大最小值
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	//显示直方图的图像
	cv::Mat histImg(HistSize[0], HistSize[0], CV_8U, cv::Scalar(255));
	//设置最高点为nbins的90%
	int hpt = static_cast<int>(0.9*HistSize[0]);
	//每个条目都绘制一条垂直线
	for (int h = 0; h < HistSize[0]; h++)
	{
		float binVal = hist.at<float>(h);
		int  internsity = static_cast<int>(binVal*hpt / maxVal);
		//两点之间绘制一条线
		cv::line(histImg,
			cv::Point(h, HistSize[0]),
			cv::Point(h, HistSize[0] - internsity),
			cv::Scalar::all(0));
	}
	return histImg;
}
