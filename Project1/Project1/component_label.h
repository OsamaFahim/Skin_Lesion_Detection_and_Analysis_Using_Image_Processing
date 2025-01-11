#pragma once
#include<iostream>,
#include"Helping.h"
#include"computation.h"


using namespace std;
using namespace cv;


Mat component_labelling(Mat& orig_img)
{
	int** label_img = nullptr;
	allocate_2d(label_img, orig_img.rows, orig_img.cols);
	int count_label = 1, equivalence_count = 0;
	equivalence* eq_labels = new equivalence[100000]{};

	for (int i = 0; i < orig_img.rows; i++)
		for (int j = 0; j < orig_img.cols; j++)
			if (value_at(orig_img, i, j) == 255)
				compute_labels(orig_img, label_img, i, j, count_label, equivalence_count, eq_labels);

	second_scan(eq_labels, equivalence_count, label_img, orig_img.rows, orig_img.cols);

	int max_occurence = most_occured(label_img, orig_img.rows, orig_img.cols);

	remove_most(label_img, max_occurence, orig_img.rows, orig_img.cols);

	for(int i = 0 ; i < 25 ; i++)
	last_processing(label_img, orig_img.rows, orig_img.cols);

	Mat temp = arr_toMat(label_img, orig_img);

	return temp;

}