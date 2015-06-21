//
// ������ ������������� cvMatchShapes()
// ��������� �������� �� �������� �� �������� 
//
// http://robocraft.ru
//

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* templ = 0;

int main(int argc, char* argv[])
{
	// ����� ����
	char* filename = argc >= 2 ? argv[1] : "d:\\img.jpg";

	printf("file = %s", filename);
	image = cvLoadImage(filename, 1);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// ������
	char* filename2 = argc >= 3 ? argv[2] : "D:\\tmp.jpg";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

	cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);

	// ������ �������
	int width = templ->width;
	int height = templ->height;

	cvShowImage("template", templ);

	// ����������� ��� �������� ���������� ���������
	// ������ ����������: ���� image WxH � templ wxh, �� result = (W-w+1)x(H-h+1)
	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);

	// ��������� ����������� � ��������
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	// ����������� ������ ��������� ��� ���������
	// (����� ��������� � ���������� �� �����������)
	double    minval, maxval;
	CvPoint    minloc, maxloc;
	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	// ������� ������� ���������������
	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);

	cvShowImage("Match", image);

	cvWaitKey(0);

	cvReleaseImage(&image);
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();
	return 0;
}