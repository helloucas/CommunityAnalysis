#include <fstream>
#include <string>
#include "JsonParse\json\json.h"
#include <vector>
#include <algorithm>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   /* time */
#include "Eigen\dense"
using Eigen::MatrixXd;
using namespace Json;
using namespace std;

//
void readGraphToJson(string graphFileName, bool isUnDirected,string outputFileName)
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
			//cout << sourceId << " " << targetId << endl;
			//cout << "readfile" << endl;
		}
	}
	readFile.close();
	int maxSource = *max_element(sourceNodes.begin(), sourceNodes.end());
	int maxTarget = *max_element(targetNodes.begin(), targetNodes.end());
	int maxNodeId = max(maxSource, maxTarget);

	//
	Json::Value root;
	srand(time(NULL));
	for (int i = 0; i <=maxNodeId; i++)
	{
		Json::Value eachNode;
		eachNode["id"] = "n" + std::to_string(i);
		eachNode["label"] = "Node n"+std::to_string(i);
		eachNode["color"] = "rgb(255, 128, 0)";
		eachNode["x"] = rand() % 300;
		eachNode["y"] = rand() % 300;
		eachNode["size"] = 3;
		root["nodes"].append(eachNode);
	}
	//cout << sourceNodes.size() <<" "<< targetNodes.size();
	for (int i = 0; i < sourceNodes.size()-1; i++)
	{
		Json::Value eachEdge;
		eachEdge["id"] = "e" + std::to_string(i);
		eachEdge["source"] = "n" + std::to_string(sourceNodes[i]);
		eachEdge["target"] = "n" + std::to_string(targetNodes[i]);
		root["edges"].append(eachEdge);
	}
	//
	//Json::StyledWriter cw;
	//cout << cw.write(root);

	Json::StyledWriter sw;
	ofstream os;
	os.open(outputFileName);
	os << sw.write(root);
	os.close();
}

//
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

string readGraphToString(string graphFileName)
{
	vector<int> sourceNodes;
	vector<int> targetNodes;
	string resultString;
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
			//cout << sourceId << " " << targetId << endl;
			//cout << "readfile" << endl;
		}
	}
	readFile.close();
	int maxSource = *max_element(sourceNodes.begin(), sourceNodes.end());
	int maxTarget = *max_element(targetNodes.begin(), targetNodes.end());
	int maxNodeId = max(maxSource, maxTarget);

	//
	Json::Value root;
	srand(time(NULL));
	for (int i = 0; i <= maxNodeId; i++)
	{
		/*Json::Value eachNode;
		eachNode["id"] = "n" + std::to_string(i);
		eachNode["label"] = "Node n" + std::to_string(i);
		eachNode["x"] = rand() % 300;
		eachNode["y"] = rand() % 300;
		eachNode["size"] = 3;
		root["nodes"].append(eachNode);*/
		resultString = resultString + "n" + std::to_string(i) + ":" + "Node" + std::to_string(i) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3)+" ";
	}
	resultString += "\n";
	//cout << sourceNodes.size() <<" "<< targetNodes.size();
	for (int i = 0; i < sourceNodes.size() - 1; i++)
	{
		//Json::Value eachEdge;
		//eachEdge["id"] = "e" + std::to_string(i);
		//eachEdge["source"] = "n" + std::to_string(sourceNodes[i]);
		//["target"] = "n" + std::to_string(targetNodes[i]);
		//root["edges"].append(eachEdge);
		resultString = resultString + "edge" + std::to_string(i) + ":" + "n" + std::to_string(sourceNodes[i]) + ":" + "n" + std::to_string(targetNodes[i]) + " ";
	}
	return resultString;
}