#include <iostream>
#include "BruteForceClique.h"
#include "dense"
#include "ReadWriteGraph.h"
#include "GroupCommunity.h"
using Eigen::MatrixXd;
int main(int argc, char* argv[])
{
	MatrixXd m;
	char command='G';
	switch (command)
	{
	case 'B':
		cout<<BruteForceClique("test.txt",3);
		break;
	case 'G':
		cout << BalancedCommunity("Figure6.8.txt");
		break;
	case 'R':
		cout << readGraphToString("Figure6.8.txt");
		break;
	case 'M':
		cout << ModularCommunity("Figure6.8.txt");
		break;
	default:
		break;
	}
	//BruteForceClique(argv[1], atoi(argv[2]));
	return 0;
}