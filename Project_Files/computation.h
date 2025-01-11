#pragma once
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include"Equivalence.h"

using namespace std;
using namespace cv;

int get_label(Mat& orig_img,int**& label_img,int i,int j,int& equivalence_count, equivalence*& eq_labels)
{
	bool chk_label = false;

	if (i == 0 && j != 0)
		chk_label = (value_at(orig_img, i, j - 1) > 0);
	else if (i != 0 && j == 0)
		chk_label = (value_at(orig_img, i - 1, j) > 0) || (value_at(orig_img, i - 1, j + 1) > 0);
	else if (j == orig_img.cols - 1)
		chk_label = (value_at(orig_img, i - 1, j) > 0) || (value_at(orig_img, i - 1, j - 1) > 0) ||
		(value_at(orig_img, i, j - 1) > 0);
	else if (i != 0 && j != 0)
		chk_label = (value_at(orig_img, i, j - 1) > 0) || (value_at(orig_img, i - 1, j) > 0) ||
					(value_at(orig_img, i - 1, j - 1) > 0) || (value_at(orig_img, i - 1, j + 1) > 0);
	else if (i == 0 && j == 0)
		chk_label = false;

	if (!chk_label)
		 return 0;
	else
	{
		int* neighbours = new int[4];
		int neighbours_count = 0;

		if (i == 0 && j != 0)
		{
			neighbours[0] = label_img[i][j - 1];
			neighbours[1] = neighbours[2] = neighbours[3] = 0;
			neighbours_count = 1;
		}
		else if (i != 0 && j == 0)
		{
			neighbours[0] = label_img[i - 1][j];
			neighbours[1] = label_img[i - 1][j + 1];
			neighbours[2] = neighbours[3] = 0;
			neighbours_count = 2;
		}
		else if (j == orig_img.cols - 1)
		{
			neighbours[0] = label_img[i - 1][j];
			neighbours[1] = label_img[i - 1][j - 1];
			neighbours[2] = label_img[i][j - 1];
			neighbours[3] = 0;
			neighbours_count = 3;
		}
		else if (i != 0 && j != 0)
		{
			neighbours[0] = label_img[i][j-1];
			neighbours[1] = label_img[i - 1][j];
			neighbours[2] = label_img[i - 1][j - 1];
			neighbours[3] = label_img[i - 1][j + 1];
			neighbours_count = 4;
		}

		int min_index = 0;
		int minimum = find_min(neighbours, min_index);

		if (neighbours_count >= 2)
			make_equivalence(eq_labels, equivalence_count, neighbours, min_index);

		return minimum;

	}
}

void compute_labels(Mat& orig_img,int**& label_img,int i,int j,int& count_label,int& equivalence_count,equivalence*& eq_labels)
{
	int label = get_label(orig_img, label_img, i, j,equivalence_count, eq_labels);

	if (label == 0)
		asign_newLabel(label_img, i, j, count_label);
	else
		asign_label(label_img, i, j, label);
}

void specific_pixel_count(int val, int**& arr, int i, int j, int rows, int cols)
{
	int* pixel = new int[8] {};
	int neighbour_count = 0;

	if (i != 0 && j != 0 && i != rows - 1 && j != cols - 1)
	{
		pixel[0] = arr[i][j - 1];
		pixel[1] = arr[i - 1][j];
		pixel[2] = arr[i - 1][j - 1];
		pixel[3] = arr[i - 1][j + 1];
		pixel[4] = arr[i][j + 1];
		pixel[5] = arr[i + 1][j];
		pixel[6] = arr[i + 1][j - 1];
		pixel[7] = arr[i + 1][j + 1];
		neighbour_count = 8;
	}

	int opposite_val = (val == 255) ? 0 : 255, specific_pixel = 0;

	for (int i = 0; i < neighbour_count; i++)
		if (pixel[i] == opposite_val)
			specific_pixel++;

	if (specific_pixel >= 5)
	{
		if (j != 0 && i != 0 && i != rows - 1 && j != cols - 1)
		{
			arr[i][j - 1] = opposite_val;
			arr[i - 1][j] = opposite_val;
			arr[i - 1][j - 1] = opposite_val;
			arr[i - 1][j + 1] = opposite_val;
			arr[i][j + 1] = opposite_val;
			arr[i + 1][j] = opposite_val;
			arr[i + 1][j - 1] = opposite_val;
			arr[i + 1][j + 1] = opposite_val;
		}
	}
}

void last_processing(int**& arr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (arr[i][j] == 255)
				specific_pixel_count(255, arr, i, i, rows, cols);
			else
				specific_pixel_count(0, arr, i, j, rows, cols);
}

