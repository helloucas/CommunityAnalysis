#ifndef GROUTCOMMUNITY_H
#define GROUPCOMMUNITY_H
#include "utility.h"
#include "Eigenvalues"
#include "KMeans.h"

// Balanced Communities
string BalancedCommunity(string graphName)
{
	MatrixXd m = readUnDirectedGraphToMatrix(graphName);
	int row = m.rows();
	int col = m.cols();
	assert(col == row);

	// ����ԽǾ���D
	vector<int> diagElems;
	for (int i = 0; i < row; i++)
	{
		int iSum = 0;
		for (int j = 0; j < col; j++)
		{
			iSum += m(i, j);
		}
		diagElems.push_back(iSum);
	}
	//���ɶԽǾ���D
	MatrixXd D;
	D.resize(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j)
			{
				D(i, j) = diagElems[i];
			}
			else
			{
				D(i, j) = 0;
			}
		}
	}

	MatrixXd L = D - m;

	//���L���������ֵ����������
	//cout << L << endl;
	Eigen::EigenSolver<MatrixXd> es;
	es.compute(L);
	//
	vector<double> LEigenValues;
	MatrixXd LE = es.eigenvalues().real();
	//cout << LE << endl;
	double minEigen = LE.row(0).real()(0);
	LEigenValues.push_back(minEigen);
	int secondMinindex = 0;
	for (int i = 1; i < LE.rows(); i++)
	{
		if (LE.row(i).real()(0) < minEigen)
		{
			minEigen = LE.row(i).real()(0);
		}
		LEigenValues.push_back(LE.row(i).real()(0));
		//cout << LE.row(i).real()(0) << " ";
	}
	//�õ��ڶ�С������ֵ������
	vector<double> backUp = LEigenValues;
	sort(LEigenValues.begin(), LEigenValues.end());
	double secondMinEigen = LEigenValues[1];
	for (int i = 0; i < backUp.size(); i++)
	{
		if (backUp[i] == secondMinEigen)
		{
			secondMinindex = i;
		}
	}

	//
	//cout << es.eigenvectors() << endl;
	//cout << secondMinindex << endl;
	vector<double> LEigenVector;
	MatrixXd eigenVecotor= es.eigenvectors().real().col(secondMinindex);
	for (int k = 0; k < eigenVecotor.rows(); k++)
	{
		//cout << eigenVecotor(k, 0) << " ";
		LEigenVector.push_back(eigenVecotor(k, 0));
	}

	vector<vector<double> > kMeansVector(LEigenVector.size());
	for (int i = 0; i < LEigenVector.size(); i++)
	{
		kMeansVector[i].push_back(LEigenVector[i]);
	}
	vector<vector<int> > clusterResult = myKMeans(kMeansVector, 2, 100);

	// ��ӽڵ�
	string resultString;
	for (int i = 0; i < clusterResult.size(); i++)
	{
		for (int j = 0; j < clusterResult[i].size(); j++)
		{
			string currentCommColor = Color[i];
			resultString = resultString + "n" + std::to_string(clusterResult[i][j]) + ":" + "Node" + std::to_string(clusterResult[i][j]) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + currentCommColor + " ";
		}
	}
	resultString += "\n";
	//��ӡ��
	//
	int communityCount = clusterResult.size();
	string* communityColors = new string[communityCount];
	for (int i = 0; i < communityCount; i++)
	{
		communityColors[i] = edgeColor[i];
	}
	//
	int count = -1;
	for (int j = 0; j < m.rows(); j++)
	{
		for (int k = j + 1; k < m.cols(); k++)
		{
			if (m(j, k) == 1)
			{
				count++;
				//resultString = resultString + "edge" + std::to_string(count) + ":" + "n" + std::to_string(j) + ":" + "n" + std::to_string(k) + " ";
				// ��ӿ��Ʊߵ���ɫ�Ĵ���
				for (int c = 0; c < communityCount; c++)
				{
					if (isInSameCommunity(clusterResult[c], j, k))
					{
						string curEdgeColor = communityColors[c];
						resultString = resultString + "edge" + std::to_string(count) + ":" + "n" + std::to_string(j) + ":" + "n" + std::to_string(k) + ":"+curEdgeColor+" ";
					}
				}
				
			}

		}
	}
	return resultString;
}

//Modular Communities
string ModularCommunity(string graphName)
{
	MatrixXd A = readUnDirectedGraphToMatrix(graphName);
	int row = A.rows();
	int col = A.cols();
	assert(row == col);
	MatrixXd d;
	d.resize(row, 1);
	// ����ڵ�Ķ�
	//vector<int> vertexDegrees;
	for (int i = 0; i < row; i++)
	{
		int iSum = 0;
		for (int j = 0; j < col; j++)
		{
			iSum += A(i, j);
		}
		//vertexDegrees.push_back(iSum);
		d(i, 0) = iSum;
	}
	//cout << d << endl;
	MatrixXd td = d.transpose();
	//cout << td << endl;
	//����ߵĸ���
	double scalarFactor = 1.0/A.sum() ;
	//����Modularity Matrix
	MatrixXd B = A - (d*td)*scalarFactor;

	//�����������ֵ����������
	Eigen::EigenSolver<MatrixXd> es;
	es.compute(B);
	MatrixXd eigenValues = es.eigenvalues().real();
	MatrixXd eigenVectors = es.eigenvectors().real();
	//cout << eigenValues << endl;
	//cout << eigenVectors << endl;
	vector<int> positiveIndex;
	int positiveCount = 0;
	//
	for (int i = 0; i < eigenValues.rows(); i++)
	{
		if (eigenValues(i, 0) > 0)
		{
			positiveIndex.push_back(i);
			positiveCount++;
		}
	}

	vector<vector<double> > kMeansVec(row);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < positiveIndex.size(); j++)
		{
			kMeansVec[i].push_back(eigenVectors.col(positiveIndex[j])(i, 0));
		}
	}

	vector<vector<int> > clusterResult = myKMeans(kMeansVec, 2, 100);

	// ��ӽڵ�
	string resultString;
	for (int i = 0; i < clusterResult.size(); i++)
	{
		for (int j = 0; j < clusterResult[i].size(); j++)
		{
			string currentCommColor = Color[i];
			resultString = resultString + "n" + std::to_string(clusterResult[i][j]) + ":" + "Node" + std::to_string(clusterResult[i][j]) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(rand() % 300) + ":" + std::to_string(3) + ":" + currentCommColor + " ";
		}
	}
	resultString += "\n";
	//��ӱߵ�
	int communityCount = clusterResult.size();
	string* communityColors = new string[communityCount];
	for (int i = 0; i < communityCount; i++)
	{
		communityColors[i] = edgeColor[i];
	}
	//
	int count = -1;
	for (int j = 0; j < A.rows(); j++)
	{
		for (int k = j + 1; k < A.cols(); k++)
		{
			if (A(j, k) == 1)
			{
				count++;
				//��ӿ��Ʊߵ���ɫ�Ĵ���
				for (int c = 0; c < communityCount; c++)
				{
					if (isInSameCommunity(clusterResult[c], j, k))
					{
						string curEdgeColor = communityColors[c];
						resultString = resultString + "edge" + std::to_string(count) + ":" + "n" + std::to_string(j) + ":" + "n" + std::to_string(k) + ":" + curEdgeColor + " ";
					}
				}
				//resultString = resultString + "edge" + std::to_string(count) + ":" + "n" + std::to_string(j) + ":" + "n" + std::to_string(k) + " ";
			}

		}
	}
	return resultString;

}

#endif