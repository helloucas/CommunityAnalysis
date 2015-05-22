#include <iostream>
#include "BruteForceClique.h"
#include "Eigen\dense"
#include "ReadWriteGraph.h"
using Eigen::MatrixXd;
int main()
{
	//接收邻接矩阵输入
	/*MatrixXd m;
	int r;
	cout << "请输入矩阵的阶数" << endl;
	cin >> r;
	m.resize(r, r);
	cout << "请依次输入矩阵的元素值" << endl;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> m(i, j);
		}
	}

	BruteForceClique(m, 5);*/
	//std::cout << m << std::endl;
	MatrixXd m;
	m = readUnDirectedGraphToMatrix("test.txt");
	BruteForceClique(m,7);
	/*for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			cout<< m(i, j)<<"  ";
		}
		cout << endl;
	}
*/
	readGraphToJson("test.txt", true,"Clique.json");
	cout << readGraphToString("test.txt");
}