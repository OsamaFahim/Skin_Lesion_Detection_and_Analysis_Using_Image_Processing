#pragma once
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include"Equivalence.h"

using namespace std;
using namespace cv;

void allocate_2d(int **&arr,int row,int col)
{
	arr = new int*[row];
	for (int i = 0; i < row; i++)
		arr[i] = new int[col] {} ;
}

int value_at(Mat& img,int x,int y)
{
	return static_cast<int>(img.at<uchar>(x, y));
}

int find_min(int* arr, int& min_index)
{
    int min = INT_MAX;
    for (int i = 0; i < 4; i++)
        if (arr[i] != 0 && arr[i] < min)
            min = arr[i],
            min_index = i;
    return min;
}


void asign_newLabel(int**& arr,int i,int j,int& label)
{
	arr[i][j] = label++ ;
}

void asign_label(int**& arr, int i, int j, int label)
{
	arr[i][j] = label;
}

Mat arr_toMat(int**& arr,Mat& orig_img)
{
	Mat temp(orig_img.rows, orig_img.cols, orig_img.type());

	for (int i = 0; i < orig_img.rows; i++)
		for (int j = 0; j < orig_img.cols; j++)
			temp.at<uchar>(i, j) = arr[i][j];

	return temp;
}

int most_occured(int**& arr, int row, int col)
{
    int second_max_count = 0, maximum_count = 0, max_occured = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            second_max_count = 0;
            if (arr[i][j] != 0)
            {
                for (int k = 0; k < row; k++)
                    for (int l = 0; l < col; l++)
                        if (arr[i][j] == arr[k][l])
                            second_max_count++;
                if (second_max_count > maximum_count)
                {
                    maximum_count = second_max_count;
                    max_occured = arr[i][j];
                }
            }
        }
    return max_occured;
}

void make_occuring_white(int**& arr, int rows, int cols, int i, int j)
{
	if (i != 0 && j != 0 && i!=rows-1 && j!=cols-1)
	{
		if (arr[i][j - 1] == 0)
			arr[i][j - 1] = 255;
		if (arr[i - 1][j] == 0)
			arr[i - 1][j] = 255;
		if (arr[i - 1][j - 1] == 0)
			arr[i - 1][j - 1] = 255;
		if (arr[i - 1][j + 1] == 0)
			arr[i - 1][j + 1] = 255;
        if (arr[i][j + 1] == 0)
            arr[i][j + 1] = 255;
        if (arr[i + 1][j] == 0)
            arr[i + 1][j] = 255;
        if (arr[i + 1][j - 1] == 0)
            arr[i + 1][j - 1] = 255;
        if (arr[i + 1][j + 1] == 0)
            arr[i + 1][j + 1] = 255;

	}
}

void remove_most(int**& arr, int element,int rows,int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] == element)
            {
				make_occuring_white(arr ,rows, cols, i, j);
                arr[i][j] = 255;
            }
            else 
                arr[i][j] = 0;
        }
    }
}

int** Mat_toarr(Mat& img)
{
    int** arr = nullptr;
    allocate_2d(arr, img.rows, img.cols);

    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
            arr[i][j] = value_at(img, i, j);

    return arr;
}