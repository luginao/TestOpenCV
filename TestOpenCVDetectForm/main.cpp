//
// пример использование cvMatchShapes()
// сравнение объектов по моментам их контуров 
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
	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "d:\\img.jpg";
	// получаем картинку
	printf("file = %s", filename);
	image = cvLoadImage(filename, 1);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// шаблон
	char* filename2 = argc >= 3 ? argv[2] : "D:\\tmp.jpg";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

//	cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// размер шаблона
	int width = templ->width;
	int height = templ->height;

	// оригинал и шаблон
//	cvShowImage("origianl", image);
	cvShowImage("template", templ);

	// изображение для хранения результата сравнения
	// размер результата: если image WxH и templ wxh, то result = (W-w+1)x(H-h+1)
	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);

	// сравнение изображения с шаблоном
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	// покажем что получили
//	cvShowImage("res", res);

	// определение лучшее положение для сравнения
	// (поиск минимумов и максимумов на изображении)
	double    minval, maxval;
	CvPoint    minloc, maxloc;
//	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	double    minvalM[3], maxvalM[3];
	CvPoint    minlocM[3], maxlocM[3];
	for (int i = 0; i < 3; i++)
		cvMinMaxLoc(res, &minvalM[i], &maxvalM[i], &minlocM[i], &maxlocM[i], 0);

	// нормализуем
//	cvNormalize(res, res, 1, 0, CV_MINMAX);
//	cvNamedWindow("res norm", CV_WINDOW_AUTOSIZE);
//	cvShowImage("res norm", res);

	// выделим область прямоугольником
//	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);
	for (int i = 0; i < 3; i++)
		cvRectangle(image, cvPoint(minlocM[i].x, minlocM[i].y), cvPoint(minlocM[i].x + templ->width - 1, minlocM[i].y + templ->height - 1), CV_RGB(0, 255, 0), 4, 8);
	// показываем изображение
	cvShowImage("Match", image);

	// ждём нажатия клавиши
	cvWaitKey(0);

	// освобождаем ресурсы
	cvReleaseImage(&image);
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();
	return 0;
}