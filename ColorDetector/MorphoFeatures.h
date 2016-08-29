//检测图像特征
#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2/highgui/highgui.hpp>

class MorphoFeatures
{
public:
	MorphoFeatures();
	~MorphoFeatures();

	void applyThreshold(cv::Mat & result){
		//使用阀值化
		if (threshold>0)
		{
			cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY);
		}
	}

	cv::Mat getEdges(const cv::Mat &image){
		//得到梯度图
		cv::Mat  result;
		cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
		//阀值化以得到二值图像
		applyThreshold(result);
		return result;
	}

	void setThreshold(int threshold){
		this->threshold = threshold;
	}

	cv::Mat getCorners(const cv::Mat &image){
		cv::Mat result;
		//十字形膨胀
		cv::dilate(image, result, cross);
		//菱形腐蚀
		cv::erode(result, result, diamond);
		cv::Mat result2;
		//X形膨胀
		cv::dilate(image, result2, x);
		//方形腐蚀
		cv::erode(result2, result2, square);
		//通过对比两张图像做差值得到角点图像
		cv::absdiff(result2, result, result);
		//阀值化得到二值图像
		applyThreshold(result);
		return result;
	}

	void drawOnImage(const cv::Mat &binary, cv::Mat & image){
		cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
		//遍历每个像素
		for (int i = 0; it != itend;++it,++i)
		{
			if (!*it)
			{
				cv::circle(image, cv::Point(i%image.step, i / image.step), 5, cv::Scalar(255, 0, 0));
			}
		}

	}

private:
	//生成二值图像的阀值
	int  threshold;
	//角点检测中用到的结构元素
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;

};

