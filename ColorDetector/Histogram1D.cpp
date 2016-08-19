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
		//����ֱ��ͼ
		cv::calcHist(&image,
			1,							//���㵥��ͼ���ֱ��ͼ
			channels,			//ͨ������
			cv::Mat(),			//	��ʹ��ͼ����Ϊ����
			hist,					//���ص�ֱ��ͼ
			1,							//����1D��ֱ��ͼ
			HistSize,				//�������
			ranges				//����ֵ�ķ�Χ
			);
		return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat &image)
{
	cv::MatND hist = getHistogram(image);
	//��ȡ�����Сֵ
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	//��ʾֱ��ͼ��ͼ��
	cv::Mat histImg(HistSize[0], HistSize[0], CV_8U, cv::Scalar(255));
	//������ߵ�Ϊnbins��90%
	int hpt = static_cast<int>(0.9*HistSize[0]);
	//ÿ����Ŀ������һ����ֱ��
	for (int h = 0; h < HistSize[0]; h++)
	{
		float binVal = hist.at<float>(h);
		int  internsity = static_cast<int>(binVal*hpt / maxVal);
		//����֮�����һ����
		cv::line(histImg,
			cv::Point(h, HistSize[0]),
			cv::Point(h, HistSize[0] - internsity),
			cv::Scalar::all(0));
	}
	return histImg;
}
