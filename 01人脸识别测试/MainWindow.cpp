#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Mat MainWindow::Image_BGR2RGB(Mat &srcImage)
{
	Mat tempImage;
	tempImage = srcImage.clone();
	for (int i = 0; i < tempImage.rows; i++)
	{
		Vec3b *p2 = tempImage.ptr<Vec3b>(i);	//获取第i行首像素指针
		Vec3b *p1 = srcImage.ptr<Vec3b>(i);
		for (int j = 0; j < tempImage.cols; j++)
		{
			//交换G\B通道
			p2[j][2] = p1[j][0];
//			p2[j][1] = p1[j][1];
			p2[j][0] = p1[j][2];
		}
	}
	return tempImage;
}

void MainWindow::on_OpenImage_Click()
{
	camera.release();
	ui.status_out->setText(tr(u8"摄像头关闭！"));
	QString imageName = QFileDialog::getOpenFileName(this, tr("打开图片"), ".", tr("Image file(*.jpg *.png)"));
	srcImage = imread(imageName.toLocal8Bit().data());
//	Mat tempImage = Image_BGR2RGB(srcImage);
	Mat tempImage;
	cvtColor(srcImage, tempImage, COLOR_BGR2RGB);

	QImage qtImage = QImage((const unsigned char*)(tempImage.data), tempImage.cols, tempImage.rows, QImage::Format_RGB888);	//转化为qt的图像文件
	qtImage = qtImage.scaled(ui.label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	//适应label尺寸大小
	ui.label->setPixmap(QPixmap::fromImage(qtImage));	//显示
}

void MainWindow::on_close_click()
{
	camera.release();
	qApp->quit();
}

void MainWindow::on_openVidio_click()
{
	//VideoCapture camera;
	int device_ID = 0;
	int api_ID = CAP_ANY;
	Mat frame;
	camera.open(device_ID, api_ID);
	//	VideoCapture(0 + CAP_DSHOW);
	if (!camera.isOpened())
	{
		ui.status_out->setText(tr(u8"打开摄像头失败！"));
	}
	else
	{
		ui.status_out->setText(tr(u8"打开摄像头成功！"));
	}
	for (;;)
	{
		camera.read(frame);
		if (frame.empty())
		{
			/*std::cout << "空白图像！！" << std::endl;*/
			ui.status_out->setText(tr(u8"空白图像！"));
			break;
		}

		//人脸检测部分
		CascadeClassifier faceCascade;
		//faceCascade.load("haarcascade_frontalface_alt2.xml");	//加载分类器
		faceCascade.load("haarcascade_frontalface_alt.xml");	//加载分类器

		//方法1
		Mat grayImage;
		std::vector<Rect> faces;	//存放人脸的向量容器
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		faceCascade.detectMultiScale(grayImage, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));	//检测人脸

		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
				Scalar(0, 255, 0), 1, 8);
		}
		Mat tempImage;
		cvtColor(frame, tempImage, COLOR_BGR2RGB);

		//方法2
		//faceDetectAndDraw(frame, faceCascade, 4);
		//Mat tempImage;
		//cvtColor(frame, tempImage, COLOR_BGR2RGB);

		QImage qtImage = QImage((const unsigned char*)(tempImage.data), tempImage.cols, tempImage.rows, QImage::Format_RGB888);	//转化为qt的图像文件
		qtImage = qtImage.scaled(ui.label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	//适应label尺寸大小
		ui.label->setPixmap(QPixmap::fromImage(qtImage));	//显示
		waitKey(1);	//视频刷新率
	}
}

void MainWindow::faceDetectAndDraw(Mat &srcImage, CascadeClassifier &faceCascade, double scale)
{
	std::vector<Rect> faces, faces2;	//存放人脸的向量容器
	Mat	grayImage;	//存放灰度图片
	Mat smallImage(cvRound(srcImage.rows / scale), cvRound(srcImage.cols / scale), CV_8UC3);		//存放缩小的图片
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//改变图像大小，使用双线性差值
	cv::resize(grayImage, smallImage, smallImage.size(), 0, 0, INTER_LINEAR);	
	//变换后的图像进行直方图均值化处理
	equalizeHist(smallImage, smallImage);	

	faceCascade.detectMultiScale(smallImage, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(3, 3));	//检测人脸

	/* 画矩形框出目标 */
	for (size_t i = 0; i < faces.size(); i++) // faces.size():检测到的目标数量
	{
		Rect rectFace = faces[i];

		rectangle(srcImage, Point(rectFace.x, rectFace.y) * scale,
			Point(rectFace.x + rectFace.width, rectFace.y + rectFace.height) * scale,
			Scalar(0, 255, 0), 2, 8);
	}
}