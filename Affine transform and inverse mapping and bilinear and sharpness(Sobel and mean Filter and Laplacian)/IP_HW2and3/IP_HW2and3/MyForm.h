#pragma once

/**
* Created by 05 on 2018/8/20.
*/

#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

void imageA(Mat, Mat, int, int, int, int);
//void onMouse(int, int, int, int, void*);

//Mat XYMatrix(4, 2, CV_32F, Scalar(0));
//int i(0);

//�ץ���
void imageA(Mat orImage, Mat result, int heigth, int width, int newHeigth, int newWidth) {

	result.at<uchar>(0, 0) = orImage.at<uchar>(0, 0);
	result.at<uchar>(0, newWidth - 1) = orImage.at<uchar>(0, width - 1);
	result.at<uchar>(newHeigth - 1, 0) = orImage.at<uchar>(heigth - 1, 0);
	result.at<uchar>(newHeigth - 1, newWidth - 1) = orImage.at<uchar>(heigth - 1, width - 1);

	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {

			if (i == 0) {
				result.at<uchar>(i, j + 1) = orImage.at<uchar>(i, j);
			}
			if (i == heigth - 1) {
				result.at<uchar>(i + 2, j + 1) = orImage.at<uchar>(i, j);
			}
			if (j == 0) {
				result.at<uchar>(i + 1, j) = orImage.at<uchar>(i, j);
			}
			if (j == width - 1) {
				result.at<uchar>(i + 1, j + 2) = orImage.at<uchar>(i, j);
			}
			result.at<uchar>(i + 1, j + 1) = orImage.at<uchar>(i, j);
		}
	}
}

/*void onMouse(int event, int x, int y, int flags, void* param) {

	if (event == CV_EVENT_LBUTTONDOWN && i < 4) {

		XYMatrix.at<float>(i, 0) = y;
		XYMatrix.at<float>(i, 1) = x;
		i++;
	}
}*/

namespace IP_HW2and3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_HW2;
	protected:
	private: System::Windows::Forms::Button^  btn_HW3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_HW2 = (gcnew System::Windows::Forms::Button());
			this->btn_HW3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_HW2
			// 
			this->btn_HW2->Location = System::Drawing::Point(91, 64);
			this->btn_HW2->Name = L"btn_HW2";
			this->btn_HW2->Size = System::Drawing::Size(75, 23);
			this->btn_HW2->TabIndex = 0;
			this->btn_HW2->Text = L"HW2";
			this->btn_HW2->UseVisualStyleBackColor = true;
			this->btn_HW2->Click += gcnew System::EventHandler(this, &MyForm::btn_HW2_Click);
			// 
			// btn_HW3
			// 
			this->btn_HW3->Location = System::Drawing::Point(91, 170);
			this->btn_HW3->Name = L"btn_HW3";
			this->btn_HW3->Size = System::Drawing::Size(75, 23);
			this->btn_HW3->TabIndex = 1;
			this->btn_HW3->Text = L"HW3";
			this->btn_HW3->UseVisualStyleBackColor = true;
			this->btn_HW3->Click += gcnew System::EventHandler(this, &MyForm::btn_HW3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btn_HW3);
			this->Controls->Add(this->btn_HW2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn_HW2_Click(System::Object^  sender, System::EventArgs^  e) {

		Mat input = imread("test.png", 1);

		int height(0), width(0);
		int bilX(0), bilY(0); //bilinear interpolation ����I��m�����W���I
		int max_X(0), max_Y(0), min_X(0), min_Y(0);
		float x(0.0), y(0.0); //����I����m
		float a(0.0), b(0.0); //bilinear interpolation ���
		//Matrix �sX�MY�ȡAAnsMatrix�s��X�ϥ|�Ө����I�AXYMatrix�s��ϥ|�Ө����I
		Mat Matrix(4, 4, CV_32F, Scalar(1));
		Mat AnsMatrix(4, 2, CV_32F, Scalar(1));
		Mat XYMatrix(4, 2, CV_32F, Scalar(0));
		Mat output;

		/*imshow("Input", input);
		setMouseCallback("Input", onMouse, NULL);
		waitKey(0);*/
		//�]�w��ϥ|�Ө��I
		XYMatrix.at<float>(0, 0) = 42;
		XYMatrix.at<float>(0, 1) = 123;
		XYMatrix.at<float>(1, 0) = 30;
		XYMatrix.at<float>(1, 1) = 255;
		XYMatrix.at<float>(2, 0) = 344;
		XYMatrix.at<float>(2, 1) = 155;
		XYMatrix.at<float>(3, 0) = 364;
		XYMatrix.at<float>(3, 1) = 288;
		//��X�Ϫ����M�e
		max_X = XYMatrix.at<float>(0, 0);
		min_X = XYMatrix.at<float>(0, 0);
		max_Y = XYMatrix.at<float>(0, 1);
		min_Y = XYMatrix.at<float>(0, 1);
		for (int i = 1; i < 4; i++) {
			
			if (XYMatrix.at<float>(i, 0) > max_X)
				max_X = XYMatrix.at<float>(i, 0);
			if (XYMatrix.at<float>(i, 0) < min_X)
				min_X = XYMatrix.at<float>(i, 0);
			if (XYMatrix.at<float>(i, 1) > max_Y)
				max_Y = XYMatrix.at<float>(i, 1);
			if (XYMatrix.at<float>(i, 1) < min_Y)
				min_Y = XYMatrix.at<float>(i, 1);
		}
		width = abs(max_Y - min_Y);
		height = abs(max_X - min_X);
		//��X�ϥ|�Ө��I
		AnsMatrix.at<float>(0, 0) = 0;
		AnsMatrix.at<float>(0, 1) = 0;
		AnsMatrix.at<float>(1, 0) = 0;
		AnsMatrix.at<float>(1, 1) = width;
		AnsMatrix.at<float>(2, 0) = height;
		AnsMatrix.at<float>(2, 1) = 0;
		AnsMatrix.at<float>(3, 0) = height;
		AnsMatrix.at<float>(3, 1) = width;
		//�Ыؿ�X��
		output.create(height, width, CV_8UC3);
		//���X�ϯx�}
		for (int i = 0; i < 4; i++) {

			Matrix.at<float>(i, 0) = AnsMatrix.at<float>(i, 0);
			Matrix.at<float>(i, 1) = AnsMatrix.at<float>(i, 1);
			Matrix.at<float>(i, 2) = AnsMatrix.at<float>(i, 0) * AnsMatrix.at<float>(i, 1);
		}
		//�ϯx�}���W��ϥ|�Ө��I�A�o��8�Ѽƭ�
		XYMatrix = Matrix.inv() * XYMatrix;
		//inverse mapping�o���X��
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				
				x = XYMatrix.at<float>(0, 0) * i + XYMatrix.at<float>(1, 0) * j + XYMatrix.at<float>(2, 0) * i * j + XYMatrix.at<float>(3, 0);
				y = XYMatrix.at<float>(0, 1) * i + XYMatrix.at<float>(1, 1) * j + XYMatrix.at<float>(2, 1) * i * j + XYMatrix.at<float>(3, 1);

				bilX = x;
				bilY = y;

				a = x - bilX;
				b = y - bilY;
				//��bilinear interpolation
				if (i >= 0 && j >= 0 && i < height && j < width) {

					output.at<Vec3b>(i, j)[0] = (1 - a) * (1 - b) * input.at<Vec3b>(bilX, bilY)[0] + (1 - a) * b *input.at<Vec3b>(bilX, bilY + 1)[0] +
						                        a * (1 - b) * input.at<Vec3b>(bilX + 1, bilY)[0] + a * b * input.at<Vec3b>(bilX + 1, bilY + 1)[0];

					output.at<Vec3b>(i, j)[1] = (1 - a) * (1 - b) * input.at<Vec3b>(bilX, bilY)[1] + (1 - a) * b *input.at<Vec3b>(bilX, bilY + 1)[1] +
						                        a * (1 - b) * input.at<Vec3b>(bilX + 1, bilY)[1] + a * b * input.at<Vec3b>(bilX + 1, bilY + 1)[1];

					output.at<Vec3b>(i, j)[2] = (1 - a) * (1 - b) * input.at<Vec3b>(bilX, bilY)[2] + (1 - a) * b *input.at<Vec3b>(bilX, bilY + 1)[2] +
						                        a * (1 - b) * input.at<Vec3b>(bilX + 1, bilY)[2] + a * b * input.at<Vec3b>(bilX + 1, bilY + 1)[2];
				}
			}
		}
		imshow("123", output);
		imwrite("output.jpg", output);
	}

	private: System::Void btn_HW3_Click(System::Object^  sender, System::EventArgs^  e) {
		
		Mat input = imread("lena512_8bit.bmp", 0);

		int max = 0;
		float temp = 0;

		int height(input.rows);
		int width(input.cols);
		//�ץ��ϰ���e
		int newHeight = height + 2;
		int newWidth = width + 2;
		//�s�� SLImg�sSobel��G���L�� LMNImg�s�G���L���B�����o�i�H�ΰ����W�ƥ�
		Mat img(newHeight, newWidth, CV_8U, Scalar(255));
		Mat SLImg(height, width, CV_8U, Scalar(255));
		Mat LMNImg(height, width, CV_8U, Scalar(255));
		//�ץ���
		imageA(input, img, height, width, newHeight, newWidth);
		//��Sobel
		for (int i = 1; i < newHeight - 1; i++) {
			for (int j = 1; j < newWidth - 1; j++) {

				temp = abs( (img.at<uchar>(i + 1, j - 1) + 2 * img.at<uchar>(i + 1, j) + img.at<uchar>(i + 1, j + 1)) -
					        (img.at<uchar>(i - 1, j - 1) + 2 * img.at<uchar>(i - 1, j) + img.at<uchar>(i - 1, j + 1)) ) +
					   abs( (img.at<uchar>(i - 1, j + 1) + 2 * img.at<uchar>(i, j + 1) + img.at<uchar>(i + 1, j + 1)) -
					        (img.at<uchar>(i - 1, j - 1) + 2 * img.at<uchar>(i, j - 1) + img.at<uchar>(i + 1, j - 1)) );
				if (temp > 255) temp = 255;
				else if (temp < 0) temp = 0;
				SLImg.at<uchar>(i - 1, j - 1) = temp;
			}
		}
		imshow("Sobel", SLImg);
		//���G���ɼ�
		for (int i = 1; i < newHeight - 1; i++) {
			for (int j = 1; j < newWidth - 1; j++) {

				temp = (-1) * img.at<uchar>(i - 1, j - 1) + (-1) * img.at<uchar>(i - 1, j) + (-1) * img.at<uchar>(i - 1, j + 1) +
					   (-1) * img.at<uchar>(i, j - 1) + 8 * img.at<uchar>(i, j) + (-1) * img.at<uchar>(i, j + 1) +
					   (-1) * img.at<uchar>(i + 1, j - 1) + (-1) * img.at<uchar>(i + 1, j) + (-1) * img.at<uchar>(i + 1, j + 1);
				if (temp > 255) temp = 255;
				else if (temp < 0) temp = 0;
				LMNImg.at<uchar>(i - 1, j - 1) = temp;
			}
		}
		imshow("L", LMNImg);

		imageA(SLImg, img, height, width, newHeight, newWidth);
		SLImg = LMNImg.clone();
		//�������o�i
		for (int i = 1; i < newHeight - 1; i++) {
			for (int j = 1; j < newWidth - 1; j++) {

				temp = (float) ( img.at<uchar>(i - 1, j - 1) + img.at<uchar>(i - 1, j) + img.at<uchar>(i - 1, j + 1) +
					             img.at<uchar>(i, j - 1) + img.at<uchar>(i, j) + img.at<uchar>(i, j + 1) +
					             img.at<uchar>(i + 1, j - 1) + img.at<uchar>(i + 1, j) + img.at<uchar>(i + 1, j + 1) ) / 9;
				if (temp > 255) temp = 255;
				else if (temp < 0) temp = 0;
				if (temp > max)  max = temp;
				LMNImg.at<uchar>(i - 1, j - 1) = temp;
			}
		}
		imshow("mean Filter", LMNImg);
		//�G���ɼƸ򥿳W�ƫ᪺�����o�i�ۭ�
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {

				LMNImg.at<uchar>(i, j) = (float) (SLImg.at<uchar>(i, j) * ((float) LMNImg.at<uchar>(i, j) / max));
				/*if (temp > 255) temp = 255;
				else if (temp < 0) temp = 0;*/
			}
		}
		imshow("A", LMNImg);
		//��A���Ϭۥ[
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {

				temp = input.at<uchar>(i, j) + LMNImg.at<uchar>(i, j);
				if (temp > 255) temp = 255;
				else if (temp < 0) temp = 0;
				input.at<uchar>(i, j) = temp;
			}
		}

		imshow("output", input);
		imwrite("output2.jpg", input);
	}
	};
}
