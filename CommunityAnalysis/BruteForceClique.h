// 实现Brute-Force Clique Identification 算法
#ifndef BRUTEFORCECLIQUE_H
#define BRUTEFORCECLIQUE_H

#include "utility.h"

vector<int> neighborVertex(int vertexId, MatrixXd & m)
{
	//assert(m.rows() == m.cols());
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

//Clique to string to visual
string CliqueToString(int vertexID, vector<int> &clique, MatrixXd& m)
{
	//
	int NodeCount = m.rows();
	// 打印节点
	srand(time(NULL));
	string NonCommColor = NonCommunityColor[0];
	string CommColor = Color[rand() % 4];
	string resultString;
	for (int i = 0; i < NodeCount; i++)
	{
		vector<int>::iterator iterFind = find(clique.begin(), clique.end(), i);
		if (iterFind == clique.end())
		{
			resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + NonCommColor + " ";
		}
		else
		{
			resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + CommColor + " ";
		}
	}

	resultString += "\n";
	//打印边
	int count = -1;
	for (int j = 0; j < NodeCount; j++)
	{
		for (int k = j + 1; k < NodeCount; k++)
		{
			if (m(j, k) == 1)
			{
				count++;
				resultString = resultString + "edge" + std::to_string(count) + ":" + "n" + std::to_string(j) + ":" + "n" + std::to_string(k) + " ";
			}
			
		}
	}
	return resultString;
}


string BruteForceClique(string readFileName, int vertexX)
{
	MatrixXd m = readUnDirectedGraphToMatrix(readFileName);
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
	// maxClique 生成输出要可视化的字符串
	//cout << CliqueToString(vertexX, maxClique,  m) << endl;
	string result = CliqueToString(vertexX, maxClique, m);
	return result;
}

#endif
