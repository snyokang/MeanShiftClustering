#include "MeanShift.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace cv;

int main() {
	mt19937 RNG(time(0));
	normal_distribution<float> dist(150, 50);
	normal_distribution<float> dist2(350, 50);
	Mat y(500, 500, CV_8UC3, Scalar(255, 255, 255));

	vector<vector<float> > data;
	
	for(int i=0; i<300; ++i) {
		vector<float> v;
		v.push_back((int)(dist(RNG)+500)%500);
		v.push_back((int)(dist(RNG)+500)%500);
		data.push_back(v);
		// circle(x, Point2i(v[0], v[1]), 2, 0, -1);
	}
	
	for(int i=0; i<300; ++i) {
		vector<float> v;
		v.push_back((int)(dist2(RNG)+500)%500);
		v.push_back((int)(dist2(RNG)+500)%500);
		data.push_back(v);
		// circle(x, Point2i(v[0], v[1]), 2, 0, -1);
	}
	
	for(int i=0; i<300; ++i) {
		vector<float> v;
		v.push_back((int)(dist(RNG)+500)%500);
		v.push_back((int)(dist2(RNG)+500)%500);
		data.push_back(v);
		// circle(x, Point2i(v[0], v[1]), 2, 0, -1);
	}
	
	for(int i=0; i<300; ++i) {
		vector<float> v;
		v.push_back((int)(dist2(RNG)+500)%500);
		v.push_back((int)(dist(RNG)+500)%500);
		data.push_back(v);
		// circle(x, Point2i(v[0], v[1]), 2, 0, -1);
	}

	cout << "BEGIN" << endl;

	vector<vector<float> > clusters;
	vector<int> group(data.size(), 0);
	cluster(data, 100, clusters, group);
	for(int i=0; i<clusters.size(); ++i)
		circle(y, Point2i(clusters[i][0], clusters[i][1]), 5, 210, -1);

	for(int i=0; i<data.size(); ++i)
		circle(y, Point2i(data[i][0], data[i][1]), 2, Scalar(40*group[i], 55*group[i]%255, 190*group[i]%255), -1);

	imshow("Clusters", y);

	waitKey(0);
	return 0;
}