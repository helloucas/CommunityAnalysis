#ifndef READWIRTEGRAPH_H
#define READWIRTEGRAPH_H
#include "utility.h"
#include "dense"
#include <string>
#include <sstream>
#include <set>
using Eigen::MatrixXd;
using namespace std;
extern void setMatrixValue(MatrixXd m, double value);
extern string Color[];

//MatrixXd readUnDirectedGraphToMatrix(string graphFileName)
//{
//	vector<int> sourceNodes;
//	vector<int> targetNodes;
//	//
//	fstream readFile;
//	readFile.open(graphFileName, ios::in);
//	if (readFile.good())
//	{
//		while (!readFile.eof())
//		{
//			int sourceId;
//			readFile >> sourceId;
//			int targetId;
//			readFile >> targetId;
//			sourceNodes.push_back(sourceId);
//			targetNodes.push_back(targetId);
//			//cout << "readfile" << endl;
//		}
//	}
//	readFile.close();
//	int maxSource = *max_element(sourceNodes.begin(), sourceNodes.end());
//	int maxTarget = *max_element(targetNodes.begin(), targetNodes.end());
//	int maxNodeId = max(maxSource, maxTarget);
//
//	//matrix
//	MatrixXd m;
//	m.resize(maxNodeId + 1, maxNodeId + 1);
//	for (int i = 0; i < m.rows(); i++)
//	{
//		for (int j = 0; j < m.cols(); j++)
//		{
//			//cout << m(i, j) << "  ";
//			m(i, j) = 0;
//		}
//		//cout << endl;
//	}
//	for (int i = 0; i < sourceNodes.size(); i++)
//	{
//		m(sourceNodes[i], targetNodes[i]) = 1;
//		m(targetNodes[i], sourceNodes[i]) = 1;
//	}
//	return m;
//}
//
////

//
//在vector 中查找某个元素的下标,如果下标没找到返回-1
int indexVec(int element, vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == element)
		{
			return i;
		}
	}
	return -1;
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
	//为什么减1.
	for (int i = 0; i < sourceNodes.size() ; i++)
	{

		resultString = resultString + "edge" + std::to_string(i) + ":" + "n" + std::to_string(sourceNodes[i]) + ":" + "n" + std::to_string(targetNodes[i]) + " ";
	}
	return resultString;
}

//重新写读取图数据文件的函数
extern void printVector(vector<int> & v);

MatrixXd readUnDirectedGraphToMatrix(string graphFileName)
{
	//
	ifstream readFile;
	readFile.open(graphFileName, ios::in);

	vector<int> sourceNodeIds;
	vector<int> targetNodeIds;
	if (readFile.good())
	{
		char eachLine[1024] = {0};
		while (readFile.getline(eachLine,sizeof(eachLine)))
		{
			stringstream eachLineStr(eachLine);
			string sourceIDStr;
			string targetIDStr;
			eachLineStr >> sourceIDStr;
			if (sourceIDStr != "#")
			{
				eachLineStr >> targetIDStr;
				int sourceID = stoi(sourceIDStr);
				int targetID = stoi(targetIDStr);
				sourceNodeIds.push_back(sourceID);
				targetNodeIds.push_back(targetID);
			}

		}
	}
	readFile.close();

	//
	vector<int> uniqueIds;
	set<int> uniqueNodesSet;
	assert(sourceNodeIds.size() == targetNodeIds.size());
	for (int i = 0; i < sourceNodeIds.size(); i++)
	{
		uniqueNodesSet.insert(sourceNodeIds[i]);
		uniqueNodesSet.insert(targetNodeIds[i]);
	}
	//
	set<int>::iterator j = uniqueNodesSet.begin();
	for (; j != uniqueNodesSet.end(); j++)
	{
		uniqueIds.push_back(*j);
	}
	//
	sort(uniqueIds.begin(), uniqueIds.end());

	//根据sourceNodeIds targetNodeIds uniqueIds 设置无向图图的邻接矩阵
	int n = uniqueIds.size();
	//cout << n << endl;
	int edgeCount = 0;
	MatrixXd m;
	m.resize(n, n);
	setMatrixValue(m, 0);
	//cout << m << endl;
	for (int r = 0; r < sourceNodeIds.size(); r++)
	{
		int sourceIndex = indexVec(sourceNodeIds[r], uniqueIds);
		int targetIndex = indexVec(targetNodeIds[r], uniqueIds);
		if (sourceIndex != -1 && targetIndex != -1)
		{
			m(sourceIndex, targetIndex) = 1;
			m(targetIndex, sourceIndex) = 1;
			edgeCount++;
		}

	}
	//

	//cout << edgeCount << endl;
	//printVector(uniqueIds);
	//cout << m << endl;
	return m;
}

//readgraph to string 加上过滤值
string readGraphToStringFilter(string graphFileName, int filter)
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

	//添加过滤后的代码
	vector<int> filterSourceNodes;
	vector<int> filterTargetNodes;
	for (int i = 0; i < sourceNodes.size(); i++)
	{
		if (sourceNodes[i] <= filter && targetNodes[i] <= filter)
		{
			filterSourceNodes.push_back(sourceNodes[i]);
			filterTargetNodes.push_back(targetNodes[i]);
		}
	}

	int maxSource = *max_element(filterSourceNodes.begin(), filterSourceNodes.end());
	int maxTarget = *max_element(filterTargetNodes.begin(), filterTargetNodes.end());
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
	//为什么减1.
	for (int i = 0; i < filterSourceNodes.size(); i++)
	{

		resultString = resultString + "edge" + std::to_string(i) + ":" + "n" + std::to_string(filterSourceNodes[i]) + ":" + "n" + std::to_string(filterTargetNodes[i]) + " ";
	}
	return resultString;

}

//添加过滤后的代码
MatrixXd readUnDirectedGraphToMatrixFilter(string graphFileName, int filter)
{
	//
	ifstream readFile;
	readFile.open(graphFileName, ios::in);

	vector<int> sourceNodeIds;
	vector<int> targetNodeIds;
	if (readFile.good())
	{
		char eachLine[1024] = { 0 };
		while (readFile.getline(eachLine, sizeof(eachLine)))
		{
			stringstream eachLineStr(eachLine);
			string sourceIDStr;
			string targetIDStr;
			eachLineStr >> sourceIDStr;
			if (sourceIDStr != "#")
			{
				eachLineStr >> targetIDStr;
				int sourceID = stoi(sourceIDStr);
				int targetID = stoi(targetIDStr);
				//添加filter
				if (sourceID <= filter&&targetID <= filter)
				{
					sourceNodeIds.push_back(sourceID);
					targetNodeIds.push_back(targetID);
				}
				
			}

		}
	}
	readFile.close();

	//
	vector<int> uniqueIds;
	set<int> uniqueNodesSet;
	assert(sourceNodeIds.size() == targetNodeIds.size());
	for (int i = 0; i < sourceNodeIds.size(); i++)
	{
		uniqueNodesSet.insert(sourceNodeIds[i]);
		uniqueNodesSet.insert(targetNodeIds[i]);
	}
	//
	set<int>::iterator j = uniqueNodesSet.begin();
	for (; j != uniqueNodesSet.end(); j++)
	{
		uniqueIds.push_back(*j);
	}
	//
	sort(uniqueIds.begin(), uniqueIds.end());

	//根据sourceNodeIds targetNodeIds uniqueIds 设置无向图图的邻接矩阵
	int n = uniqueIds.size();
	//cout << n << endl;
	int edgeCount = 0;
	MatrixXd m;
	m.resize(n, n);
	setMatrixValue(m, 0);
	for (int r = 0; r < sourceNodeIds.size(); r++)
	{
		int sourceIndex = indexVec(sourceNodeIds[r], uniqueIds);
		int targetIndex = indexVec(targetNodeIds[r], uniqueIds);
		if (sourceIndex != -1 && targetIndex != -1)
		{
			m(sourceIndex, targetIndex) = 1;
			m(targetIndex, sourceIndex) = 1;
			edgeCount++;
		}

	}
	//

	//cout << edgeCount << endl;
	//printVector(uniqueIds);
	//cout << m << endl;
	return m;
}

#endif