#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

void salt(cv::Mat &image, int n){

	for (int k = 0; k < n; k++)
	{
		//���������
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1)//�Ҷ�ͼ
		{
			image.at<uchar>(j, i) = 255;
		}
		else if (image.channels() == 3)//��ɫͼ
		{
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void colorReduce(cv::Mat &image, int div = 64)
{
	int nl = image.rows; //����
	int nc = image.cols*image.channels(); // ÿ�е�ͨ����
	for (int j = 0; j < nl;j++)
	{
		//�õ���j�е��׵�ַ
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc;i++)
		{
			//����ÿ��ͨ��
			//data[i] = data[i] / div*div + div / 2;
			*data++ = *data / div*div + div / 2;
			//ͨ���������
		}//�д������
	}
}

//ȡģ�ķ�ʽ�������ݣ�Ч�ʸ�
void colorReduceWithMask(cv::Mat &image, int div = 64)
{
	int nl = image.rows; //����
	int nc = image.cols*image.channels(); // ÿ�е�ͨ����
	uchar mask = 0xFF << 6;  // e.g. for div = 16, mask = 0xF0;
	for (int j = 0; j < nl; j++)
	{
		//�õ���j�е��׵�ַ
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			//����ÿ��ͨ��
			data[i] = (data[i] & mask) + div / 2;
			//ͨ���������
		}//�д������
	}
}

void Sharpen(const cv::Mat &image,cv::Mat&result)
{
	//cv::cvtColor(image, result_img, CV_BGR2GRAY);   //������Ĳ�ɫͼ��ת��Ϊ�Ҷ�ͼ��

		//������⼰��ʼ��
	result.create(image.size(), image.type());
	int rw = image.rows - 1;
	int cl = image.cols - 1;

	for (int j = 1; j < rw; j++) //������˵�һ�к����һ�������
	{
		const uchar* previoous = image.ptr<const uchar>(j - 1);
		const uchar* current = image.ptr<const uchar>(j);
		const uchar* next = image.ptr<const uchar>(j+1);

		uchar* output = result.ptr<uchar>(j);
		
		for (int i = 1; i < cl;i++)//������˵�һ�к����һ�������
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - current[i + 1] - current[i - 1] - previoous[i] - next[i]);
		}
	}
	//δ�������������
	result.row(0).setTo(cv::Scalar(0));
	result.row(rw).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(cl).setTo(cv::Scalar(0));
}

void sharpen2D(const cv::Mat &image,cv::Mat &result)
{
		//����ˣ��������ʼ��Ϊ0 ��
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;

	//��ͼ���˲�
	cv::filter2D(image, result, image.depth(), kernel);
}



int main()
{
	//read an image
	cv::Mat  image = cv::imread("img.jpg");
	if (!image.data)
	{
		//ͼ�����ʧ��
		std::cout << "image loading failed";
		return 1;
	}
	else
	{
		//create image window named "My Image"
		cv::namedWindow("My Image");
		//������
		//salt(image, 1000);

		//show the image on window
		cv::imshow("My Image", image);
		//wait key for 5000ms
		//cv::waitKey(5000);

		//save the new image
		cv::Mat result_img;
		//������ʾˮƽ��ת��0��ʾ��ֱ��ת��������ʾ����ˮƽҲ�д�ֱ��ת
		//cv::flip(image, result_img, 1);

		cv::namedWindow("new image");
		//colorReduceWithMask(result_img);
		cv::Mat rs;
		rs = cv::imread("Q.jpg");
		//sharpen2D(result_img, rs);
	//	cv::addWeighted(image, 0.9, rs, 0.5, 0., result_img);
		result_img = 0.7*image + 0.9*rs;
		cv::imshow("new image", result_img);
		////���ͼƬ
		//cv::imwrite("newimage.jpg", result_img);
		////���޵ȴ�
		cv::waitKey(0);
	}
	return 1;
}

