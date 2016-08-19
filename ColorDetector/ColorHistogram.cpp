#include "ColorHistogram.h"


ColorHistogram::ColorHistogram()
{
	HistSize[0] = HistSize[1] = HistSize[2] = 256;;
	hranges[0] = 0.0;      //BRG 的范围
	hranges[1] = 255.0;

	ranges[0] = hranges;  //所以通道拥有相同的范围
	ranges[1] = hranges;  //所以通道拥有相同的范围
	ranges[2] = hranges;  //所以通道拥有相同的范围

	channels[0] = 0;
	channels[1] = 1;
	channels[2] = 2;
}


ColorHistogram::~ColorHistogram()
{
}

cv::MatND ColorHistogram::getHistogram(const cv::Mat &image)
{
	cv::MatND hist;
	//计算直方图
	cv::calcHist(&image,
		1,							//计算单张图像的直方图
		channels,			//通道数量
		cv::Mat(),			//	不使用图像作为掩码
		hist,					//返回的直方图
		3,							//这是1D的直方图
		HistSize,				//项的数量
		ranges				//像素值的范围
		);
	return hist;
}

cv::Mat ColorHistogram::getHistogramImage(const cv::Mat &image)
{

}

//cv::SparseMat 数据结构，它旨在表示大型的稀疏矩阵（即矩阵拥有少量非零元素），
//同时不会消耗过多的内存，
//
cv::SparseMat ColorHistogram::getSparseHistogram(const cv::Mat &image)
{
	cv::SparseMat hist(3,HistSize,CV_32F);
	
	cv::calcHist(&image,
		1,							//计算单张图像的直方图
		channels,			//通道数量
		cv::Mat(),			//	不使用图像作为掩码
		hist,					//返回的直方图
		3,							//这是1D的直方图
		HistSize,				//项的数量
		ranges				//像素值的范围
		);
	return hist;
}
