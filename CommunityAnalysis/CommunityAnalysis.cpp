#include <iostream>
#include "BruteForceClique.h"
#include "dense"
#include "ReadWriteGraph.h"
#include "GroupCommunity.h"
#include "CliquePercolationMethod.h"
#include "CommunityEvolution.h"
//using Eigen::MatrixXd;
int main(int argc, char* argv[])
{
	//MatrixXd m;
	//char command = argv[1][0];
	char command = 'E';
	string result;
	switch (command)
	{
	case 'R':
		//cout << readGraphToString(argv[2]);
		//cout << readGraphToString("test.txt");
		result = readGraphToString("facebook_combined.txt");
		writeStringToFile(result, "FaceboolResult.txt");
		break;
	case 'P':
		//cout<<CPM("cpm.txt", 4);
		result = CPM("facebook_combined.txt", 4);
		cout << result << endl;
		writeStringToFile(result, "CPM_result.txt");
		break;
	case 'B':
		//cout << BruteForceClique(argv[2], atoi(argv[3]));
		cout << BruteForceClique("cpm.txt", 3);
		break;
	case 'G':
		//cout << BalancedCommunity(argv[2]);
		cout << BalancedCommunity("Figure6.3.txt");
		break;
	case 'M':
		//cout << ModularCommunity(argv[2]);
		cout << ModularCommunity("facebook_combined.txt");
		break;
	case 'E':
		cout<<CommunityEvolve("facebook_combined.txt");
	default:
		break;
	}
	//BruteForceClique(argv[1], atoi(argv[2]));
	//readUnDirectedGraphToMatrix("facebook_combined.txt");
	//cout << readGraphToString("facebook_combined.txt");
	//cout << BalancedCommunity("Figure6.8.txt");
	//cout << ModularCommunity("facebook_combined.txt");
	return 0;
}