#pragma once
#pragma once
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include"Helping.h"

using namespace std;
using namespace cv;

struct node
{
	int val;
	node* next;
	node* down;
	node()
	{
		this->val = -1;
		this->next = nullptr, this->down = nullptr;
	}
};

void assign_next(node*& start_temp, int value)
{
	start_temp->val = value;
	start_temp->next = new node;
	start_temp = start_temp->next;
}

void add_dimensions(node*& start_temp,int rows,int cols)
{
	node* temp = start_temp;
	start_temp->val = rows;
	start_temp->next = new node;
	start_temp = start_temp->next;
	start_temp->val = cols;
	temp->down = new node;
	start_temp = temp->down;
}

node* RLC(Mat& orig_img)
{
	node* start = new node;
	node* start_temp = start;
	node* row_first = start_temp;
	add_dimensions(start_temp, orig_img.rows, orig_img.cols);

	for (int i = 0; i < orig_img.rows; i++)
	{
		for (int j = 0; j < orig_img.cols; j++)
		{
			if (value_at(orig_img,i,j) == 255)
			{
				assign_next(start_temp, j);

				while (value_at(orig_img,i,j) == 255 && j < orig_img.cols) j++; // one liner loop
				
				assign_next(start_temp, j - 1);
			}
		}

		if (i < orig_img.rows - 1)
		{
			row_first->down = new node;
			row_first = row_first->down;
			start_temp = row_first;
		}
	}
	return start;
}

void display_RLC(node* head)
{
	node* row_first = head;

	while (head != nullptr)
	{
		row_first = head;
		while (row_first != nullptr)
		{
			cout << row_first->val << "->";
			row_first = row_first->next;
		}
		cout << "NULL\n";
		cout << "! \n";
		head = head->down;
		row_first = head;
	}
	cout << "NULL";
}
