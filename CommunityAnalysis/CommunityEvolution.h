#ifndef COMMUNITY_EVOLUTION_H
#define COMMUNITY_EVOLUTION_H
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   /* time */
#include <vector>
#include <stack>
#include "ReadWriteGraph.h"
#include "dense"

using Eigen::MatrixXd;
using namespace std;
using std::string;
//求某一个定点的度
int sumIRow(MatrixXd m, int r)
{
	double sum = 0;
	for (int i = 0; i < m.cols(); i++)
	{
		sum += m(r, i);
	}
	return sum;
}

//寻找某一结点的邻接节点
vector<int> adjVertex(int vetexId, MatrixXd m)
{
	vector<int> adjVec;
	for (int i = 0; i < m.cols(); i++)
	{
		if (m(vetexId, i) == 1)
			adjVec.push_back(i);
	}
	return adjVec;
}

string CommunityEvolve(string inFileName, double r0=0.0005, double r1=2, double r2=0.005, double ka=3, double kd=3,double z=5)

{
	//MatrixXd  A = readUnDirectedGraphToMatrix(inFileName);
	MatrixXd A = readUnDirectedGraphToMatrixFilter(inFileName, 100);
	//cout << A << endl;
	double  np = (A.rows()*(A.rows() - 1)) / 2;
	double  ne = A.sum() / 2;
	//
	vector<int> nodeDegrees;
	for (int i = 0; i < A.rows(); i++)
	{
		nodeDegrees.push_back(sumIRow(A, i));
	}
	//
	double nm = 0;
	for (int i = 0; i < A.rows(); i++)
	{
		double temp = nodeDegrees[i] * (nodeDegrees[i] - 1);
		nm += temp;
	}
	nm = nm / 2;

	//step 1
	int randomCount = np*r0;
	int n = A.rows();
	for (int i = 0; i < randomCount; i++)
	{
		srand(time(NULL));
		int sourceVertex = rand() % n;
		int targetVertex = rand() % n;
		while (targetVertex == sourceVertex)
		{
			targetVertex = rand() % n;
		}
		if (A(sourceVertex, targetVertex) == 0 && (sumIRow(A, sourceVertex) <= z && sumIRow(A, targetVertex) <= z))
		{
			A(sourceVertex, targetVertex) = 1;
		}
	}

	// step 2
	int randomVertexCount = nm * r1/100;
	//先随机选择2*nm*r1个节点 然后根据每个节点的度从大到小依次选择nm*r1个节点
	for (int i = 0; i < randomVertexCount; i++)
	{
		srand(time(NULL));
		int choosedVertex = rand() % n;
		vector<int> adjVec = adjVertex(choosedVertex, A);
		int randId = rand() % adjVec.size();
		int sourceVertex = adjVec[randId];
		int anotherRandId = rand() % adjVec.size();
		while (anotherRandId == randId)
		{
			anotherRandId = rand() % adjVec.size();
		}
		int targetVertex = adjVec[anotherRandId];
		if (A(sourceVertex, targetVertex) == 0 && (sumIRow(A, sourceVertex) <= z && sumIRow(A, targetVertex) <= z))
		{
			A(sourceVertex, targetVertex) = 1;
		}
	}
	//cout << "Evolution:" << endl;
	//cout << A << endl;

	// step 3
	int randomVertice2 = ne*r2;
	for (int i = 0; i < randomVertice2; i++)
	{
		srand(time(NULL));
		int choosedVertex = rand() % n;
		vector<int> adjVec = adjVertex(choosedVertex, A);
		int randId = rand() % adjVec.size();
		int sourceVertex = adjVec[randId];
		int anotherRandId = rand() % adjVec.size();
		while (anotherRandId == randId)
		{
			anotherRandId = rand() % adjVec.size();
		}
		int targetVertex = adjVec[anotherRandId];
		if (A(sourceVertex, targetVertex) == 1 )
		{
			A(sourceVertex, targetVertex) = 0;
		}
	}
	//对字符进行拼接
	string resultString;
	string nodeColor = Color[0];
	for (int i = 0; i <= A.rows(); i++)
	{
		resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 640) + ":" + std::to_string(rand() % 480) + ":" + std::to_string(3) + ":" + nodeColor + " ";
	}
	resultString += "\n";
	//cout << sourceNodes.size() <<" "<< targetNodes.size();
	//为什么减1.
	int edgeCount = -1;
	for (int i = 0; i < A.rows(); i++)
	{
		for (int j = 0; j < A.cols(); j++)
		{
			if (A(i, j) == 1)
			{
				edgeCount++;
				resultString = resultString + "edge" + std::to_string(edgeCount) + ":" + "n" + std::to_string(i) + ":" + "n" + std::to_string(j) + " ";
			}
		}

	}
	return resultString;
	//cout << resultString << endl;
	//cout << "Evolution" << endl;
	//cout << A << endl;
}
#endif