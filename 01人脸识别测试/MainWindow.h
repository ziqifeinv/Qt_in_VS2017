#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "qfiledialog.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

using namespace cv;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
	Mat srcImage;
	VideoCapture camera;

	Mat Image_BGR2RGB(Mat &srcImage);
	void faceDetectAndDraw(Mat &srcImage, CascadeClassifier &faceCascade, double scale);

private slots:

	void on_OpenImage_Click();
	void on_close_click();
	void on_openVidio_click();
};
