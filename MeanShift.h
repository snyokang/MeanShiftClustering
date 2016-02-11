#ifndef _MEANSHIFT_H_
#define _MEANSHIFT_H_

#include <vector>

using namespace std;

void cluster(vector<vector<float> > data, float bandwidth, vector<vector<float> >& clusters, vector<int>& group);

#endif // _MEANSHIFT_H_