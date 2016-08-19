#include "ColorDetector.h"
#include "Histogram1D.h"
#include <iostream>

int main()
{
	ColorDetector cdetector;
	cv::Mat  image = cv::imread("img.jpg", 0);
	if (!image.data)
	{
		return 0;
	}
	//cdetector.setTargetColor(63, 126, 177);

	Histogram1D h;
	cv::MatND histo = h.getHistogram(image);

	for (int i = 0; i < 256; i++)
	{
		std::cout << "value" << i << "=" << histo.at<float>(i)<< std::endl;
	}

	cv::Mat img = h.getHistogramImage(image);

	//create image window named "My Image"
	cv::namedWindow("My Image");
	cv::imshow("My Image", img);
	cv::waitKey(0);
	return 0;
}

