#pragma once
#pragma once
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include"Helping.h"
#include"component_label.h"

using namespace std;
using namespace cv;

void removeuseless_whites(int**& arr, int rows, int cols)
{
	int j = 0,temp=0;

	while (j < cols - 1)
	{
		temp = 0;
		while (temp < rows - 1 && arr[temp][j] == 255)
		{
			arr[temp][j] = 0;
			temp++;
		}
		j++;
	}

	j = cols - 1, temp = rows - 1;

	while (j >= 0)
	{
		temp = rows - 1;
		while (temp >= 0 && arr[temp][j] == 255)
		{
			arr[temp][j] = 0;
			temp--;
		}
		j--;
	}
}

Mat k_clustering(Mat& orig_img)
{
	srand(time(0));
	int** binary_image = nullptr;
	allocate_2d(binary_image, orig_img.rows, orig_img.cols); 

	int prev_c1 = rand() % 127, prev_c2 = (rand() % 127) + 127, new_c1 = 0, new_c2 = 0;
	int count_0 = 0 , count_255 = 0; 
	bool first_time = false; 

	while (prev_c1 != new_c1 || prev_c2 != new_c2) //Condition until the new and previous clusters are not same the loop will run that is why
	{												// || is written so that only if both prev and new clusters are same only then
		if (first_time)								// the loop would terminate else not
			prev_c1 = new_c1, prev_c2 = new_c2;
		new_c1 = 0, new_c2 = 0;			//the new clusters would be initizlied to zero because we have to calculate them in every iteration
											//down below
		for(int i = 0 ; i < orig_img.rows ;i++)
			for(int j = 0; j < orig_img.cols ;j++)
				if (abs(prev_c1 - value_at(orig_img, i, j)) < abs(prev_c2 - value_at(orig_img, i, j))) 
				{			
					binary_image[i][j] = 255;	//Scanning of 2d image(Mat) and where ever the distance is shorter for cluster 1 that would
					count_255++;				//belong to 1st cluster and vice versa 
					new_c1 += value_at(orig_img, i, j);
				}								//if absolute is shorter for cluster 1 i would put 255 in the second array in the respective
				else                            //indices indicating that these belong to cluster 1 and vice versa
				{								
					binary_image[i][j] = 0;
					count_0++;
					new_c2 += value_at(orig_img, i, j);
				}

		new_c1 /= count_255,new_c2 /= count_0;  // new clusters are basically average so here is the average calculation
		count_0 = 0 , count_255 = 0;			//initializing count with 0, and first_time with true as first iteration has passed
		first_time = true;
	}

	removeuseless_whites(binary_image, orig_img.rows, orig_img.cols);
	Mat clustered = arr_toMat(binary_image, orig_img); //putting 2d array to mat object and returning its
	return component_labelling(clustered);
	//return clustered;
}
