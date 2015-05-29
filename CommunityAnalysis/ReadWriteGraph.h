#ifndef READWIRTEGRAPH_H
#define READWIRTEGRAPH_H
#include "utility.h"
#include "dense"
#include <string>
using Eigen::MatrixXd;
using namespace std;

extern string Color[];

MatrixXd readUnDirectedGraphToMatrix(string graphFileName)
{
	vector<int> sourceNodes;
	vector<int> targetNodes;
	//
	fstream readFile;
	readFile.open(graphFileName, ios::in);
	if (readFile.good())
	{
		while (!readFile.eof())
		{
			int sourceId;
			readFile >> sourceId;
			int targetId;
			readFile >> targetId;
			sourceNodes.push_back(sourceId);
			targetNodes.push_back(targetId);
			//cout << "readfile" << endl;
		}
	}
	readFile.close();
	int maxSource = *max_element(sourceNodes.begin(), sourceNodes.end());
	int maxTarget = *max_element(targetNodes.begin(), targetNodes.end());
	int maxNodeId = max(maxSource, maxTarget);

	//matrix
	MatrixXd m;
	m.resize(maxNodeId + 1, maxNodeId + 1);
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			//cout << m(i, j) << "  ";
			m(i, j) = 0;
		}
		//cout << endl;
	}
	for (int i = 0; i < sourceNodes.size(); i++)
	{
		m(sourceNodes[i], targetNodes[i]) = 1;
		m(targetNodes[i], sourceNodes[i]) = 1;
	}
	return m;
}

//
string readGraphToString(string graphFileName)
{
	vector<int> sourceNodes;
	vector<int> targetNodes;
	string resultString;
	fstream readFile;
	readFile.open(graphFileName, ios::in);
	if (readFile.good())
	{
		while (!readFile.eof())
		{
			int sourceId;
			readFile >> sourceId;
			int targetId;
			readFile >> targetId;
			sourceNodes.push_back(sourceId);
			targetNodes.push_back(targetId);
		}
	}
	readFile.close();
	int maxSource = *max_element(sourceNodes.begin(), sourceNodes.end());
	int maxTarget = *max_element(targetNodes.begin(), targetNodes.end());
	int maxNodeId = max(maxSource, maxTarget);

	//
	srand(time(NULL));
	string nodeColor = Color[rand() % 4];
	for (int i = 0; i <= maxNodeId; i++)
	{
		resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + nodeColor + " ";
	}
	resultString += "\n";
	//cout << sourceNodes.size() <<" "<< targetNodes.size();
	//ÎªÊ²Ã´¼õ1.
	for (int i = 0; i < sourceNodes.size() ; i++)
	{
		resultString = resultString + "edge" + std::to_string(i) + ":" + "n" + std::to_string(sourceNodes[i]) + ":" + "n" + std::to_string(targetNodes[i]) + " ";
	}
	return resultString;
}

#endif