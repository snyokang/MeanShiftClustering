#include "MeanShift.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

float kernel(float dist, float bandwidth) {
	if(dist > bandwidth) return 0;
	return 1;
}

float distance(vector<float> a, vector<float> b) {
	assert(a.size()==b.size());

	float dist = 0;
	for(int i=0; i<a.size(); ++i)
		dist += (a[i]-b[i])*(a[i]-b[i]);
	return sqrt(dist);
}

void shift(vector<float> oldMean, vector<vector<float> > data, float bandwidth, vector<float>& newMean) {
	int dim = oldMean.size();
	float scale = 0;
	for(vector<vector<float> >::iterator it=data.begin(); it!=data.end(); ++it) {
		vector<float> pt = *it;
		float weight = kernel(distance(oldMean, pt), bandwidth);
		for(int i=0; i<dim; ++i)
			newMean[i] += pt[i]*weight;
		scale += weight;
	}
	for(int i=0; i<dim; ++i) {
		if(scale != 0)
			newMean[i] /= scale;
		else
			newMean[i] = oldMean[i];
	}
}

void cluster(vector<vector<float> > data, float bandwidth, vector<vector<float> >& clusters, vector<int>& group) {
	for(int i=0; i<data.size(); ++i) {
		vector<float> oldMean = data[i];
		vector<float> newMean(oldMean.size(), 0);
		while(1) {
			newMean.assign(oldMean.size(), 0);
			shift(oldMean, data, bandwidth, newMean);
			if(distance(oldMean, newMean) < 1e-3*bandwidth)
				break;
			oldMean = newMean;
		}

		int j;
		for(j=0; j<clusters.size(); ++j)
			if(distance(newMean, clusters[j]) < bandwidth/2)
				break;

		if(j==clusters.size())
			clusters.push_back(newMean);
		
		group[i] = j;
	}
}