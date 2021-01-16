#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Pixel.cpp"
#include "kmeans.h"

using namespace cv;
using namespace std;

void kmeans(string path, int k) {
	Mat image = imread(path);

	vector<Pixel> pixels = getImageAsPixels(path);
	vector<Pixel> centroids = initializeCentroids(pixels, k);

	assignPixelsToCentroids(pixels, centroids);
	
	
	bool isFinished = false;
	int i = 0;
	while(!isFinished) {
		isFinished = recomputeCentroids(pixels, centroids);
		assignPixelsToCentroids(pixels, centroids);
		cout << i++;
	}

	changePixels(pixels, centroids);

	convertImage(image, pixels);

	imshow("converted", image);
	waitKey();
}

vector<Pixel> getImageAsPixels(String path) {
	Mat src = imread(path);

	vector<Pixel> pixels;
	for (size_t i = 0; i < src.rows; i++) {
		for (size_t j = 0; j < src.cols; j++) {
			pixels.push_back({ src.at<Vec3b>(i, j)[2],
							   src.at<Vec3b>(i, j)[1],
							   src.at<Vec3b>(i, j)[0] });
		}
	}

	return pixels;
}

vector<Pixel> initializeCentroids(vector<Pixel>& pixels, int k) {
	vector<Pixel> centroids;
	size_t size = pixels.size();
	srand(time(NULL));
	for (int i = 0; i < k; ++i) {
		
		centroids.push_back(pixels[rand() % size]);
	}

	return centroids;
}

void assignPixelsToCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids) {
	int clusterId = 0;
	for (auto centroid : centroids) {
		for (auto& pixel : pixels) {

			double dist = pixel.distanceTo(centroid);
			if (dist < pixel.minDist) {
				pixel.cluster = clusterId;
				pixel.minDist = dist;
			}
		}
		++clusterId;
	}
}

bool recomputeCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids) {
	vector<long long> pixelCount(centroids.size(),1);
	vector<long long> sumRed(centroids.size(),1);
	vector<long long> sumGreen(centroids.size(),1);
	vector<long long> sumBlue(centroids.size(),1);

	for (auto& pixel : pixels) {
		int clusterId = pixel.cluster;
		pixelCount[clusterId]++;
		sumRed[clusterId] += pixel.r;
		sumGreen[clusterId] += pixel.g;
		sumBlue[clusterId] += pixel.b;
		pixel.minDist = INT16_MAX;
	}

	bool isFinished = true;
	int clusterId = 0;
	for (auto& centroid : centroids) {
		
		short recomputedR = (sumRed[clusterId] / pixelCount[clusterId]);
		short recomputedG = (sumGreen[clusterId] / pixelCount[clusterId]);
		short recomputedB = (sumBlue[clusterId] / pixelCount[clusterId]);

		if (abs(centroid.r - recomputedR) > 1 ||
			(abs(centroid.g - recomputedG) > 1) ||
			(abs(centroid.b - recomputedB) > 1)) {

			isFinished = false; // centroid should be moved
		}
		
		centroid.r = recomputedR;
		centroid.g = recomputedG;
		centroid.b = recomputedB;
		++clusterId;
	}
	return isFinished;
}

void changePixels(vector<Pixel>& pixels, vector<Pixel>& centroids) {
	for (auto& pixel : pixels) {
		int clusterId = pixel.cluster;
		pixel.r = centroids[clusterId].r;
		pixel.g = centroids[clusterId].g;
		pixel.b = centroids[clusterId].b;
	}
}

void convertImage(Mat& image, vector<Pixel>& pixels){
	for (size_t i = 0; i < image.rows; i++) {
		for (size_t j = 0; j < image.cols; j++) {
			//Vec3b is in BGR format
			image.at<Vec3b>(i, j)[0] = pixels[j + image.cols * i].b;
			image.at<Vec3b>(i, j)[1] = pixels[j + image.cols * i].g;
			image.at<Vec3b>(i, j)[2] = pixels[j + image.cols * i].r;
		}
	}
}
