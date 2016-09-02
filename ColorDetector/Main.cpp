#include "ColorDetector.h"
#include "Histogram1D.h"
#include "MorphoFeatures.h"
#include <iostream>

int main()
{
	//ColorDetector cdetector;
	//cv::Mat  image = cv::imread("img.jpg", 0);
	//if (!image.data)
	//{
	//	return 0;
	//}
	//cdetector.setTargetColor(63, 126, 177);
	//cv::namedWindow("My Image1");
	//cv::imshow("My Image1", image);

	//Histogram1D h;
	//cv::MatND histo = h.getHistogram(image);

	//for (int i = 0; i < 256; i++)
	//{
	//	std::cout << "value" << i << "=" << histo.at<float>(i)<< std::endl;
	//}

	//cv::Mat img = h.getHistogramImage(image);
	//cv::Mat img = h.equalize(image);
	//create image window named "My Image"

	MorphoFeatures morpho;
	morpho.setThreshold(50);
	//获取边缘
	cv::Mat edges;
	cv::Mat image = cv::imread("sdf.jpg", 0);
	edges = morpho.getCorners(image);
	//在图像中显示角点
	morpho.drawOnImage(edges,image);

	cv::namedWindow("My Image");
	cv::imshow("My Image", image);
	cv::waitKey(0);
	return 0;
}

