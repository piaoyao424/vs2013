#include "ColorDetectController.h"
//静态成员变量必须在.cpp文件定义
ColorDetectController * ColorDetectController::singleton = 0;

ColorDetectController::ColorDetectController()
{
	cdetect = new ColorDetector();
}


ColorDetectController::~ColorDetectController()
{
	delete cdetect;
}

void ColorDetectController::setColorDistanceThreshold(int distance)
{
	cdetect->setColorDistanceTheshold(distance);
}

int ColorDetectController::getColorDistanceThreshold()
{
	return cdetect->getColorDistanceThreshold();
}

void ColorDetectController::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
	cdetect->setTargetColor(red, green, blue);
}

void ColorDetectController::getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue)
{
	cv::Vec3b color = cdetect->getTargetColor();
	red = color[2];
	green = color[1];
	blue = color[0];
}

bool ColorDetectController::setInputImage(std::string fileName)
{
	image = cv::imread(fileName);
	if (image.data)
	{
		return true;
	}
	else
	{
		return false;
	}
}

cv::Mat ColorDetectController::getInputImage()
{
	return image;
}

void ColorDetectController::process()
{
	result = cdetect->process(image);
}

cv::Mat ColorDetectController::getLastResult()
{
	return result;
}

ColorDetectController * ColorDetectController::getInstance()
{
	 if (singleton ==0)
	 {
		 singleton = new ColorDetectController();
	 }
	 return singleton;
}

void ColorDetectController::Destroy()
{
	if (singleton != 0)
	{
		delete singleton;
		singleton = 0;
	}
}



