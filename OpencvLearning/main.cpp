#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

void salt(cv::Mat &image, int n){

	for (int k = 0; k < n; k++)
	{
		//生成随机数
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1)//灰度图
		{
			image.at<uchar>(j, i) = 255;
		}
		else if (image.channels() == 3)//彩色图
		{
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void colorReduce(cv::Mat &image, int div = 64)
{
	int nl = image.rows; //行数
	int nc = image.cols*image.channels(); // 每行的通道数
	for (int j = 0; j < nl;j++)
	{
		//得到第j行的首地址
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc;i++)
		{
			//处理每个通道
			//data[i] = data[i] / div*div + div / 2;
			*data++ = *data / div*div + div / 2;
			//通道处理完成
		}//行处理完成
	}
}

//取模的方式处理数据，效率高
void colorReduceWithMask(cv::Mat &image, int div = 64)
{
	int nl = image.rows; //行数
	int nc = image.cols*image.channels(); // 每行的通道数
	uchar mask = 0xFF << 6;  // e.g. for div = 16, mask = 0xF0;
	for (int j = 0; j < nl; j++)
	{
		//得到第j行的首地址
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			//处理每个通道
			data[i] = (data[i] & mask) + div / 2;
			//通道处理完成
		}//行处理完成
	}
}

void Sharpen(const cv::Mat &image,cv::Mat&result)
{
	//cv::cvtColor(image, result_img, CV_BGR2GRAY);   //把输入的彩色图像转化为灰度图像

		//参数检测及初始化
	result.create(image.size(), image.type());
	int rw = image.rows - 1;
	int cl = image.cols - 1;

	for (int j = 1; j < rw; j++) //处理除了第一行和最后一行以外的
	{
		const uchar* previoous = image.ptr<const uchar>(j - 1);
		const uchar* current = image.ptr<const uchar>(j);
		const uchar* next = image.ptr<const uchar>(j+1);

		uchar* output = result.ptr<uchar>(j);
		
		for (int i = 1; i < cl;i++)//处理除了第一列和最后一列以外的
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - current[i + 1] - current[i - 1] - previoous[i] - next[i]);
		}
	}
	//未处理的像素置零
	result.row(0).setTo(cv::Scalar(0));
	result.row(rw).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(cl).setTo(cv::Scalar(0));
}

void sharpen2D(const cv::Mat &image,cv::Mat &result)
{
		//构造核（所有项都初始化为0 ）
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;

	//对图像滤波
	cv::filter2D(image, result, image.depth(), kernel);
}



int main()
{
	//read an image
	cv::Mat  image = cv::imread("img.jpg");
	if (!image.data)
	{
		//图像加载失败
		std::cout << "image loading failed";
		return 1;
	}
	else
	{
		//create image window named "My Image"
		cv::namedWindow("My Image");
		//添加噪点
		//salt(image, 1000);

		//show the image on window
		cv::imshow("My Image", image);
		//wait key for 5000ms
		//cv::waitKey(5000);

		//save the new image
		cv::Mat result_img;
		//正数表示水平反转，0表示垂直反转，负数表示既有水平也有垂直反转
		//cv::flip(image, result_img, 1);

		cv::namedWindow("new image");
		//colorReduceWithMask(result_img);
		cv::Mat rs;
		rs = cv::imread("Q.jpg");
		//sharpen2D(result_img, rs);
	//	cv::addWeighted(image, 0.9, rs, 0.5, 0., result_img);
		result_img = 0.7*image + 0.9*rs;
		cv::imshow("new image", result_img);
		////输出图片
		//cv::imwrite("newimage.jpg", result_img);
		////无限等待
		cv::waitKey(0);
	}
	return 1;
}

