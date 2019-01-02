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
		Vec3b *p2 = tempImage.ptr<Vec3b>(i);	//��ȡ��i��������ָ��
		Vec3b *p1 = srcImage.ptr<Vec3b>(i);
		for (int j = 0; j < tempImage.cols; j++)
		{
			//����G\Bͨ��
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
	ui.status_out->setText(tr(u8"����ͷ�رգ�"));
	QString imageName = QFileDialog::getOpenFileName(this, tr("��ͼƬ"), ".", tr("Image file(*.jpg *.png)"));
	srcImage = imread(imageName.toLocal8Bit().data());
//	Mat tempImage = Image_BGR2RGB(srcImage);
	Mat tempImage;
	cvtColor(srcImage, tempImage, COLOR_BGR2RGB);

	QImage qtImage = QImage((const unsigned char*)(tempImage.data), tempImage.cols, tempImage.rows, QImage::Format_RGB888);	//ת��Ϊqt��ͼ���ļ�
	qtImage = qtImage.scaled(ui.label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	//��Ӧlabel�ߴ��С
	ui.label->setPixmap(QPixmap::fromImage(qtImage));	//��ʾ
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
		ui.status_out->setText(tr(u8"������ͷʧ�ܣ�"));
	}
	else
	{
		ui.status_out->setText(tr(u8"������ͷ�ɹ���"));
	}
	for (;;)
	{
		camera.read(frame);
		if (frame.empty())
		{
			/*std::cout << "�հ�ͼ�񣡣�" << std::endl;*/
			ui.status_out->setText(tr(u8"�հ�ͼ��"));
			break;
		}

		//������ⲿ��
		CascadeClassifier faceCascade;
		//faceCascade.load("haarcascade_frontalface_alt2.xml");	//���ط�����
		faceCascade.load("haarcascade_frontalface_alt.xml");	//���ط�����

		//����1
		Mat grayImage;
		std::vector<Rect> faces;	//�����������������
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		faceCascade.detectMultiScale(grayImage, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));	//�������

		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
				Scalar(0, 255, 0), 1, 8);
		}
		Mat tempImage;
		cvtColor(frame, tempImage, COLOR_BGR2RGB);

		//����2
		//faceDetectAndDraw(frame, faceCascade, 4);
		//Mat tempImage;
		//cvtColor(frame, tempImage, COLOR_BGR2RGB);

		QImage qtImage = QImage((const unsigned char*)(tempImage.data), tempImage.cols, tempImage.rows, QImage::Format_RGB888);	//ת��Ϊqt��ͼ���ļ�
		qtImage = qtImage.scaled(ui.label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	//��Ӧlabel�ߴ��С
		ui.label->setPixmap(QPixmap::fromImage(qtImage));	//��ʾ
		waitKey(1);	//��Ƶˢ����
	}
}

void MainWindow::faceDetectAndDraw(Mat &srcImage, CascadeClassifier &faceCascade, double scale)
{
	std::vector<Rect> faces, faces2;	//�����������������
	Mat	grayImage;	//��ŻҶ�ͼƬ
	Mat smallImage(cvRound(srcImage.rows / scale), cvRound(srcImage.cols / scale), CV_8UC3);		//�����С��ͼƬ
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	//�ı�ͼ���С��ʹ��˫���Բ�ֵ
	cv::resize(grayImage, smallImage, smallImage.size(), 0, 0, INTER_LINEAR);	
	//�任���ͼ�����ֱ��ͼ��ֵ������
	equalizeHist(smallImage, smallImage);	

	faceCascade.detectMultiScale(smallImage, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(3, 3));	//�������

	/* �����ο��Ŀ�� */
	for (size_t i = 0; i < faces.size(); i++) // faces.size():��⵽��Ŀ������
	{
		Rect rectFace = faces[i];

		rectangle(srcImage, Point(rectFace.x, rectFace.y) * scale,
			Point(rectFace.x + rectFace.width, rectFace.y + rectFace.height) * scale,
			Scalar(0, 255, 0), 2, 8);
	}
}