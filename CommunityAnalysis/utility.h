#ifndef UTILITY_H
#define UTILITY_H
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

//Ԥ���弸����ɫ
string Color[] = { "rgb(255,0,0)", "rgb(0,255,0)", "rgb(0,0,255)", "rgb(255,255,0)", "rgb(100,100,100)", "rgb(100,100,100)","rgb(120,120,100)","rgb(140,140,100)" };
string NonCommunityColor[] = { "rgb(0,0,0)" };
string edgeColor[] = { "rgb(128,128,128)", "rgb(0,128,128)", "rgb(0,0,128)", "rgb(64,255,255)" };

//�ж��������Ƿ���ͬһ������
bool isInSameCommunity(vector<int> community, int sourceVertex, int targetVertex)
{
	bool result = true;
	vector<int>::iterator iterSource = find(community.begin(), community.end(),sourceVertex);
	vector<int>::iterator iterTarget = find(community.begin(), community.end(), targetVertex);
	if (iterSource == community.end() || iterTarget == community.end())
	{
		result = false;
	}
	return result;
}

//��vector<int> community ת����string���ڿ��ӻ�

// �ж�ĳ���ڵ��Ƿ���������
bool isInCommunity(int vertexId, vector<int> community)
{
	bool isIn = false;
	for (int i = 0; i < community.size(); i++)
	{
		if (vertexId == community[i])
		{
			isIn = true;
			return isIn;
		}
	}
	return isIn;
}



string communityToString(vector<int> community, MatrixXd A)
{
	string communColor = Color[0];
	string nonCommunColor = Color[1];
	int commSize = community.size();
	int nodeSize = A.rows();
	string resultString;
	//��ӽڵ����ɫ
	for (int i = 0; i < nodeSize; i++)
	{
		//�����ͬһ����
		if (isInCommunity(i, community))
		{
			resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + communColor + " ";
		}
		else
		{
			resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + nonCommunColor + " ";
		}
	}
	resultString += "\n";
	//��ӱߵ���ɫ
	int edgeCount = -1;
	for (int i = 0; i < A.rows(); i++)
	{
		for (int j = 0; j < A.cols(); j++)
		{
			if (A(i, j) == 1)
			{
				//�����������ͬһ����
				edgeCount++;
				if (isInSameCommunity(community, i, j))
				{
					resultString = resultString + "edge" + std::to_string(edgeCount) + ":" + "n" + std::to_string(i) + ":" + "n" + std::to_string(j) + ":" + communColor + " ";
				}
				else
				{
					resultString = resultString + "edge" + std::to_string(edgeCount) + ":" + "n" + std::to_string(i) + ":" + "n" + std::to_string(j) + ":" + nonCommunColor + " ";
				}

			}
		}
	}
	return resultString;
}

void writeStringToFile(string str, string outFileName)
{
	ofstream of;
	of.open(outFileName, ios::out);
	if (of.is_open())
	{
		of << str;
	}
	of.close();
}


//���þ����Ԫ��ȫΪĳ��ֵ
void setMatrixValue(MatrixXd m, double value)
{
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
			m(i, j) = value;
	}
}
#endif