#pragma once
#include <iostream>
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
	cv::Mat  applyLookUp(const cv::Mat & image,
		const cv::Mat &lookup)
	{
		//���ͼ��
		cv::Mat result;
		//Ӧ�ò��ұ�
		cv::LUT(image, lookup, result);
		return result;
	}

		cv::Mat stretch(const cv::Mat &image, int minValue = 0)
		{
			//����ֱ��ͼ
			cv::MatND hist = getHistogram(image);
			//Ѱ��ֱ��ͼ�����
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

			//Ѱ��ֱ��ͼ���Ҷ�
			
			for (; imax >= 0; imax--)
			{
				if (hist.at<float>(imax)>minValue)
				{
					break;
				}
			}

			//�������ұ�
			int dim = 256;
			cv::Mat  lookup(1, &dim, CV_8U);
			//�����ұ�
			for (int i = 0; i < 256;i++)
			{
				//ȷ����ֵλ��imin��imax ֮��
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
			// Ӧ�ò��ұ�
			cv::Mat result;
			result = applyLookUp(image, lookup);
			return result;
			}
		
		//���ؾ��⻯,�������ͼ������
		cv::Mat equalize(const cv::Mat &image)
		{
			cv::Mat  result;
			cv::equalizeHist(image, result);
			return result;
		}

private:
	int HistSize[1];
	float hranges[2];  //���������Сֵ
	const float*ranges[1];
	int channels[1];
};
