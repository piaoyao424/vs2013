#pragma once
#include <iostream>
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
	cv::Mat  applyLookUp(const cv::Mat & image,
		const cv::Mat &lookup)
	{
		//输出图像
		cv::Mat result;
		//应用查找表
		cv::LUT(image, lookup, result);
		return result;
	}

		cv::Mat stretch(const cv::Mat &image, int minValue = 0)
		{
			//计算直方图
			cv::MatND hist = getHistogram(image);
			//寻找直方图的左端
			int imin = 0;
			int imax = HistSize[0] - 1;

			for (; imin < HistSize[0];imin++)
			{
				std::cout << hist.at<float>(imin) << std::endl;
				if (hist.at<float>(imin)>minValue)
				{
					break;
				}
			}

			//寻找直方图的右端
			
			for (; imax >= 0; imax--)
			{
				if (hist.at<float>(imax)>minValue)
				{
					break;
				}
			}

			//创建查找表
			int dim = 256;
			cv::Mat  lookup(1, &dim, CV_8U);
			//填充查找表
			for (int i = 0; i < 256;i++)
			{
				//确保数值位于imin与imax 之间
				if (i < imin)
				{
					lookup.at<uchar>(i) = 0;
				}
				else if (i>imax)
				{
					lookup.at<uchar>(i) = 255;
				} 
				else
				{
					lookup.at<uchar>(i) = static_cast<uchar>(255*(i-imin)/(imax-imin)+0.5) ;
				}
			}
			// 应用查找表
			cv::Mat result;
			result = applyLookUp(image, lookup);
			return result;
			}
		
		//像素均衡化,显著提高图像质量
		cv::Mat equalize(const cv::Mat &image)
		{
			cv::Mat  result;
			cv::equalizeHist(image, result);
			return result;
		}

private:
	int HistSize[1];
	float hranges[2];  //保存最大最小值
	const float*ranges[1];
	int channels[1];
};
