#include "ColorHistogram.h"


ColorHistogram::ColorHistogram()
{
	HistSize[0] = HistSize[1] = HistSize[2] = 256;;
	hranges[0] = 0.0;      //BRG �ķ�Χ
	hranges[1] = 255.0;

	ranges[0] = hranges;  //����ͨ��ӵ����ͬ�ķ�Χ
	ranges[1] = hranges;  //����ͨ��ӵ����ͬ�ķ�Χ
	ranges[2] = hranges;  //����ͨ��ӵ����ͬ�ķ�Χ

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
	//����ֱ��ͼ
	cv::calcHist(&image,
		1,							//���㵥��ͼ���ֱ��ͼ
		channels,			//ͨ������
		cv::Mat(),			//	��ʹ��ͼ����Ϊ����
		hist,					//���ص�ֱ��ͼ
		3,							//����1D��ֱ��ͼ
		HistSize,				//�������
		ranges				//����ֵ�ķ�Χ
		);
	return hist;
}

cv::Mat ColorHistogram::getHistogramImage(const cv::Mat &image)
{

}

//cv::SparseMat ���ݽṹ����ּ�ڱ�ʾ���͵�ϡ����󣨼�����ӵ����������Ԫ�أ���
//ͬʱ�������Ĺ�����ڴ棬
//
cv::SparseMat ColorHistogram::getSparseHistogram(const cv::Mat &image)
{
	cv::SparseMat hist(3,HistSize,CV_32F);
	
	cv::calcHist(&image,
		1,							//���㵥��ͼ���ֱ��ͼ
		channels,			//ͨ������
		cv::Mat(),			//	��ʹ��ͼ����Ϊ����
		hist,					//���ص�ֱ��ͼ
		3,							//����1D��ֱ��ͼ
		HistSize,				//�������
		ranges				//����ֵ�ķ�Χ
		);
	return hist;
}
