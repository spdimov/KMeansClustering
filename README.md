
# **K Means Image Segmentation**

##  What is K Means Clustering
> "k-means clustering allows us to find  groups of similar points within a dataset"

## Algorithm idea
> The idea of the algorithm is:
    1. Initialise K clusters
    2. Assign each point to the nearest cluster
    3. Calculate new centroids by calculating the average values of the points assigned to it
    4. Repeating steps 2. and 3.

## Implementation
> Pixel.cpp represents a single RGB pixel plus to which cluster this pixel belongs.
Clusters a numerated from 0 to k.

> With *opencv* library we are able to save image as vector of pixel and that is the starting point of the algorithm.

> For every single step in the algorithm we have separate function as follows:

* vector<Pixel> initializeCentroids(vector<Pixel>& pixels, int k)
* void assignPixelsToCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids)
* bool recomputeCentroids(vector<Pixel>& pixels, vector<Pixel>& centroids)
* void changePixels(vector<Pixel>& pixels, vector<Pixel>& centroids)
* void convertImage(Mat& image, vector<Pixel>& pixels)





