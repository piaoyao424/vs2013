#pragma once
#include "ColorDetector.h"

class ColorDetectController
{
public:
	ColorDetectController();
	~ColorDetectController();
	void setColorDistanceThreshold(int distance);
	int    getColorDistanceThreshold();
	void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
	void getTargetColor(unsigned char &red,unsigned char &green,unsigned char &blue);
	bool setInputImage(std::string fileName);
	cv::Mat getInputImage();
	void process();
	cv::Mat getLastResult();
	static ColorDetectController *getInstance();
	static void Destroy();

private:
	//À„∑®¿‡
	ColorDetector* cdetect;
	cv::Mat image;
	cv::Mat result;
	static ColorDetectController *singleton;
};

