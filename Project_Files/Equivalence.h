#pragma once
#include<iostream>

using namespace std;

struct equivalence
{
	int opr1;
	int opr2;
	equivalence()
	{
		opr1 = 0, opr2 = 0;
	}
};

void second_scan(equivalence*& eq_labels, int equivalence_count, int**& label_img, int rows, int cols)
{
	for (int i = 0; i < equivalence_count; i++)
	{
		for (int j = 0; j < rows; j++)
			for (int k = 0; k < cols; k++)
				if (eq_labels[i].opr2 == label_img[j][k])
					label_img[j][k] = eq_labels[i].opr1;

		for (int l = i+1; l < equivalence_count; l++)
		{
			if (eq_labels[i].opr2 == eq_labels[l].opr2)
				eq_labels[l].opr2 = eq_labels[i].opr1;
			if(eq_labels[i].opr2 == eq_labels[l].opr1)
				eq_labels[l].opr1 = eq_labels[i].opr1;
		}
	}

}

bool notalready_eq(equivalence*& eq_labels, int equivalence_count, int val1, int val2)
{
	for (int i = 0; i < equivalence_count; i++)
		if (eq_labels[i].opr1 == val1 && eq_labels[i].opr2 == val2)
			return false;
	return true;
}

void make_equivalence(equivalence*& eq_labels, int& equivalence_count, int* neighbours, int min_index)
{
	for (int i = 0; i < 4; i++)
		if (i != min_index && neighbours[i] != 0 && neighbours[i] != neighbours[min_index])
			if (notalready_eq(eq_labels, equivalence_count, neighbours[min_index], neighbours[i]))
			{
				eq_labels[equivalence_count].opr1 = neighbours[min_index];
				eq_labels[equivalence_count].opr2 = neighbours[i];
				equivalence_count++;
			}
}
