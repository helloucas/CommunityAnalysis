#ifndef KMEANS_H
#define KMEANS_H

#include<iostream>
#include<cmath>
#include<vector>
#include<ctime>
#include<cstdlib> 
using namespace std;
typedef unsigned int uint;

struct Cluster
{
	vector<double> centroid;
	vector<uint> samples;
};
double cal_distance(vector<double> a, vector<double> b)
{
	uint da = a.size();
	uint db = b.size();
	if (da != db) cerr << "Dimensions of two vectors must be same!!\n";
	double val = 0.0;
	for (uint i = 0; i < da; i++)
	{
		val += pow((a[i] - b[i]), 2);
	}
	return pow(val, 0.5);
}


// 定义我自己的KMeans算法
vector<vector<int> > myKMeans(vector<vector<double> > trainX, uint k, uint maxepoches)
{
	const uint row_num = trainX.size();
	const uint col_num = trainX[0].size();

	/*初始化聚类中心*/
	vector<Cluster> clusters(k);
	uint seed = (uint)time(NULL);
	for (uint i = 0; i < k; i++)
	{
		srand(seed);
		int c = rand() % row_num;
		clusters[i].centroid = trainX[c];
		seed = rand();
	}

	/*多次迭代直至收敛，本次试验迭代100次*/
	for (uint it = 0; it < maxepoches; it++)
	{
		/*每一次重新计算样本点所属类别之前，清空原来样本点信息*/
		for (uint i = 0; i < k; i++)
		{
			clusters[i].samples.clear();
		}
		/*求出每个样本点距应该属于哪一个聚类*/
		for (uint j = 0; j < row_num; j++)
		{
			/*都初始化属于第0个聚类*/
			uint c = 0;
			double min_distance = cal_distance(trainX[j], clusters[c].centroid);
			for (uint i = 1; i < k; i++)
			{
				double distance = cal_distance(trainX[j], clusters[i].centroid);
				if (distance < min_distance)
				{
					min_distance = distance;
					c = i;
				}
			}
			clusters[c].samples.push_back(j);
		}

		/*更新聚类中心*/
		for (uint i = 0; i < k; i++)
		{
			vector<double> val(col_num, 0.0);
			for (uint j = 0; j < clusters[i].samples.size(); j++)
			{
				uint sample = clusters[i].samples[j];
				for (uint d = 0; d < col_num; d++)
				{
					val[d] += trainX[sample][d];
					if (j == clusters[i].samples.size() - 1)
						clusters[i].centroid[d] = val[d] / clusters[i].samples.size();
				}
			}
		}
	}

	//对得到的Clusters进行处理
	int c = clusters.size();
	vector<vector<int> > result(c);
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < clusters[i].samples.size(); j++)
		{
			result[i].push_back(clusters[i].samples[j]);
		}
	}
	return result;
}

#endif