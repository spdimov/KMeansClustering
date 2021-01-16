#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<string>
#include <vector>
#include <iostream>
#include <math.h>
#include "Pixel.cpp"
using namespace cv;

using namespace std;

void kmeans(string path, int k);

/**
* Converts an image into a vector of RGB pixels
*
* @param path the path of wanted image 
* @returns image pixels as vector<Pixel>
*
*/
vector<Pixel> getImageAsPixels(string path);

/**
* @Initialize @param k random centroids from @param pixels for first time
*
* @returns centroids as vector<Pixel>
*/
vector<Pixel> initializeCentroids(vector<Pixel>& pixels, int k);

/**
* Sets each pixel cluster field from @param pixels to the closest of the k @param centroids
*/
void assignPixelsToCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids);

/**
* Recomputes each of the @param cetroids using the mean values of RGB of the @param pixels assigned to it
*
* @returns true if no changes were made and false if algorithm is not finished yet
*/
bool recomputeCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids);

/**
* Changes RGB values of each pixel from @param pixels with the values of the @param centroids it belongs to
*/
void changePixels(vector<Pixel>& pixels, vector<Pixel>& centroids);

/*
* Changes @param image pixels RGB values with @param pixels RGB values 
*/
void convertImage(Mat& image, vector<Pixel>& pixels);
