#include "test.h"
#include <QtWidgets/QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	test w;

	//w.show();
	//return a.exec();

	Mat srcImage;
	srcImage = imread("../image/1.jpg", 1);
	imshow("≤‚ ‘", srcImage);
	waitKey(0);
	return 0;
}
