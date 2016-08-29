//���ͼ������
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
		//ʹ�÷�ֵ��
		if (threshold>0)
		{
			cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY);
		}
	}

	cv::Mat getEdges(const cv::Mat &image){
		//�õ��ݶ�ͼ
		cv::Mat  result;
		cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
		//��ֵ���Եõ���ֵͼ��
		applyThreshold(result);
		return result;
	}

	void setThreshold(int threshold){
		this->threshold = threshold;
	}

	cv::Mat getCorners(const cv::Mat &image){
		cv::Mat result;
		//ʮ��������
		cv::dilate(image, result, cross);
		//���θ�ʴ
		cv::erode(result, result, diamond);
		cv::Mat result2;
		//X������
		cv::dilate(image, result2, x);
		//���θ�ʴ
		cv::erode(result2, result2, square);
		//ͨ���Ա�����ͼ������ֵ�õ��ǵ�ͼ��
		cv::absdiff(result2, result, result);
		//��ֵ���õ���ֵͼ��
		applyThreshold(result);
		return result;
	}

	void drawOnImage(const cv::Mat &binary, cv::Mat & image){
		cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
		//����ÿ������
		for (int i = 0; it != itend;++it,++i)
		{
			if (!*it)
			{
				cv::circle(image, cv::Point(i%image.step, i / image.step), 5, cv::Scalar(255, 0, 0));
			}
		}

	}

private:
	//���ɶ�ֵͼ��ķ�ֵ
	int  threshold;
	//�ǵ������õ��ĽṹԪ��
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;

};

