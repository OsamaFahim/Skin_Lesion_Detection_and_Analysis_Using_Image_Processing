#pragma once
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include"Helping.h"

using namespace std;
using namespace cv;

double dice_coefficient(Mat& ground, Mat& segmented)
{
	int** ground_arr = Mat_toarr(ground);
	int** segmented_arr = Mat_toarr(segmented);

	double tp = 0, fn = 0, fp = 0;

	for (int i = 0; i < ground.rows; i++)
		for (int j = 0; j < ground.cols; j++)
			if (ground_arr[i][j] == 255 && segmented_arr[i][j] == 255)
				 tp++;
			else if (ground_arr[i][j] != 255 && segmented_arr[i][j] == 255)
				 fp++;
			else if (ground_arr[i][j] == 255 && segmented_arr[i][j] != 255)
				fn++;

	return  ((2 * tp) / (fn + (2 * tp) + fp)) * 100;
}