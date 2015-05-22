//  µœ÷Brute-Force Clique Identification À„∑®
#ifndef BRUTEFORCECLIQUE_H
#define BRUTEFORCECLIQUE_H
#include <stack>
#include <vector>
#include <iostream>
#include "Eigen\dense"
using Eigen::MatrixXd;
using namespace std;

vector<int> neighborVertex(int vertexId, MatrixXd & m)
{
	assert(m.rows() == m.cols());
	int c = m.cols();
	vector<int> neighbors;
	for (int i = 0; i < c; i++)
	{
		if (m(vertexId, i) == 1)
		{
			neighbors.push_back(i);
		}
	}
	return neighbors;
}

bool isClique(vector<int> &clique, int newVertex, MatrixXd & m)
{
	int size = clique.size();
	bool result = true;
	for (int i = 0; i < size; i++)
	{
		if (m(newVertex, clique[i]) != 1)
		{
			result = false;
			return result;
		}
	}
	return result;
}

void printVector(vector<int> & v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "  ";
	}
	cout << endl;
}

vector<int> BruteForceClique(MatrixXd m, int vertexX)
{
	stack<vector<int> > CliqueStack;
	vector<int> clique;
	clique.push_back(vertexX);
	CliqueStack.push(clique);
	vector<vector<int> > Processed;

	while (!CliqueStack.empty())
	{
		vector<int> C = CliqueStack.top();
		CliqueStack.pop();
		Processed.push_back(C);
		
		int cSize = C.size();
		int vLast = C[cSize - 1];
		//
		vector<int> neighbors = neighborVertex(vLast, m);
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (isClique(C, neighbors[i], m))
			{
				C.push_back(neighbors[i]);
				CliqueStack.push(C);
			}

		}
	}
	// return the largest clique from Processed
	vector<int> maxClique = Processed[0];
	int maxSize = Processed[0].size();

	for (int j = 1; j < Processed.size(); j++)
	{
		//printVector(Processed[j]);
		if (Processed[j].size() > maxSize)
		{
			maxClique = Processed[j];
			maxSize = Processed[j].size();
		}
	}
	cout << maxSize << endl;
	cout << "maxClique :";
	printVector(maxClique);
	return maxClique;
}

#endif