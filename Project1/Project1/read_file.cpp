#include"component_label.h"
#include"Dice_coefficient.h"
#include"k_means.h"
#include"RLC.h"
int main()
{
	Mat cimage = imread("D:/data structures university/Assignment1/Assignment 1/Original Images/IMD042.bmp");//loading an image//
	Mat ximage = imread("D:/data structures university/Assignment1/Assignment 1/Ground Truths/IMD042_lesion.bmp");	
	Mat zimage = imread("D:/data structures university/Assignment1/Assignment 1/Segmented Outputs/mIMD042.bmp");
	Mat img;
	Mat img2;
	Mat img3;
	cvtColor(cimage, img, COLOR_BGR2GRAY);
	cvtColor(ximage, img2, COLOR_BGR2GRAY);
	cvtColor(zimage, img3, COLOR_BGR2GRAY);
	//imshow("Bismilllah", img);
	/*imshow("Bismillah1", img);
	imshow("Bismillah2", img2);*/
	//imshow("Bismillah1", img);
	Mat temp = component_labelling(img3);
	imshow("Bismillah3", temp);
	cout<<"The dice coefficient of the labelled image is: "<<dice_coefficient(img2, temp)<<'\n';
	Mat temp1 = k_clustering(img);
	imshow("Bismillah", temp1);
	cout << "The dice coefficient of the clustered image is: " << dice_coefficient(img2, temp1) << '\n';
	cout << "The RLC of the segmented image is:\n";
	display_RLC(RLC(img3));
	//cout << dice_coefficient(img2,temp);
	/*imshow("Bismillah", img);*/
	//imshow("Ya ALlah madad", temp);
	waitKey();

	return 0;
}