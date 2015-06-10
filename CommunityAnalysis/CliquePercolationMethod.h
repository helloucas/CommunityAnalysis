/** 
	implementation of Clique Percolation Method algorithm
*/
#ifndef CPM_H
#define CPM_H
#include <queue>
#include "utility.h"
#include "BruteForceClique.h"
//implementation of Brute-Force Clique Identification algorithm
vector<vector<int>> BruteForceClique(MatrixXd A, int vertexX)
{
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

		int vLast = C[C.size()-1];
		//get vLast's neighbors
		vector<int> N_vLast;
		for(int i=0;i<A.cols();i++)
		{
			if(A(vLast,i) == 1)
				N_vLast.push_back(i);
		}
		//try to enlarge clique C
		for(int vTemp=0;vTemp<N_vLast.size();vTemp++)
		{
			if(isClique(C,N_vLast[vTemp],A))
			{
				C.push_back(N_vLast[vTemp]);
				CliqueStack.push(C);
				C.pop_back();
			}
		}
	}
	// return the largest clique from Processed
	vector<vector<int>> maxCliques;
	vector<int> maxCliqueIndex;
	maxCliqueIndex.push_back(0);
	int maxSize = Processed[0].size();
	/*if(vertexX == 2) 
	{
		printf("\nclique contain vertex 2:");
		printVector(Processed[0]);
	}*/
	for (int j = 1; j < Processed.size(); j++)
	{
		/*if(vertexX == 2)
		{
			printf("clique contain vertex 2:");
			printVector(Processed[j]);
		}*/
		if (Processed[j].size() > maxSize)
		{
			maxSize = Processed[j].size();
			maxCliqueIndex.clear();
			maxCliqueIndex.push_back(j);
		}
		else if(Processed[j].size() == maxSize)
		{
			maxCliqueIndex.push_back(j);
		}
	}
	for(int j=0;j<maxCliqueIndex.size();j++)
	{
		maxCliques.push_back(Processed[maxCliqueIndex[j]]);
	}
	return maxCliques;
}
//check if two cliques are the same
bool isTheSameClique(vector<int> a,vector<int> b)
{
	if(a.size() != b.size())
		return false;
	bool same = true;
	bool exist = false;
	for(int i=0;i<a.size();i++)
	{
		exist = false;
		for(int j=0;j<b.size();j++)
		{
			if(a[i] == b[j])
			{
				exist = true;
				break;
			}
		}
		if(!exist)
		{
			same = false;
			break;
		}
	}
	return same;
}
int getCommonNodesCount(vector<int> a, vector<int> b)
{
	int count = 0;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<b.size();j++)
		{
			if(a[i] == b[j])
			{
				count++;
				break;
			}
		}
	}
	return count;
}
//get k-clique-communities based on the overlapMatrix
vector<vector<int>> getCommunities(int** overlapMatrix, int k, vector<vector<int>> cliques)
{
	//erasing every off-diagonal entry smaller than k-1 and every diagonal element smaller than k
	for(int i=0;i<cliques.size();i++)
	{
		for(int j=i;j<cliques.size();j++)
		{
			if(i==j)
			{
				if(overlapMatrix[i][j]<k)
					overlapMatrix[i][j] = 0;
				else
					overlapMatrix[i][j] = 1;
			}
			else{
				if(overlapMatrix[i][j]<(k-1))
				{
					overlapMatrix[i][j] = 0;
					overlapMatrix[j][i] = 0;
				}
				else
				{
					overlapMatrix[i][j] = 1;
					overlapMatrix[j][i] = 1;
				}
			}
		}
	}
	//connect cliques(just like graph search,take the cliques as vertex)
	int *visited = new int[cliques.size()];
	for(int i=0;i<cliques.size();i++)
		visited[i] = 0;
	vector<vector<int>> communities;
	queue<int> q;
	for(int i=0;i<cliques.size();i++)
	{
		if(visited[i] == 0 && overlapMatrix[i][i]!=0)
		{
			vector<int> oneC;
			int cur = -1;
			q.push(i);
			visited[i] = 1;
			while(!q.empty())
			{
				cur = q.front();
				q.pop();
				oneC.push_back(cur);
				for(int j=0;j<cliques.size();j++)
				{
					if(overlapMatrix[cur][j]==1 && visited[j] == 0)
					{
						q.push(j);
						visited[j] = 1;
					}
				}
			}
			communities.push_back(oneC);
		}
	}
	//generate communities incllude nodes
	vector<vector<int>> com;
	vector<int> nodeSet;
	int cliqueIndex = -1;
	bool exist = false;
	for(int i=0;i<communities.size();i++)
	{
		nodeSet.clear();
		for(int j=0;j<communities[i].size();j++)
		{
			cliqueIndex = communities[i][j];
			for(int x=0;x<cliques[cliqueIndex].size();x++)
			{
				exist = false;
				for(int y=0;y<nodeSet.size();y++)
				{
					if(cliques[cliqueIndex][x] == nodeSet[y])
					{
						exist = true;
						break;
					}
				}
				if(!exist)
					nodeSet.push_back(cliques[cliqueIndex][x]);
			}
		}
		com.push_back(nodeSet);
	}
	return com;
}

//print communities in the console
void printCommunities(vector<vector<int>> communities,char *str)
{
	for(int i=0;i<communities.size();i++)
	{
		printf("%s %d: ",str,i);
		for(int j=0;j<communities[i].size();j++)
		{
			printf("%d,",communities[i][j]);
		}
		printf("\n");
	}
}
//print Matrix
void printMatrix(MatrixXd A)
{
	for(int i=0;i<A.rows();i++)
	{
		for(int j=0;j<A.cols();j++)
		{
			printf("%d,",(int)A(i,j));
		}
		printf("\n");
	}
}
//implementation of Clique Percolation Method algorithm
string CPM(string graphFileName, int k)
{
	//MatrixXd A = readUnDirectedGraphToMatrix(graphFileName);
	MatrixXd A = readUnDirectedGraphToMatrixFilter(graphFileName,100);
	//print matrixt A
	//printf("adjacent matrix:\n");
	//printMatrix(A);
	//First prunning all nodes with degrees less than k-1
	int degree = 0;
	vector<int> preservedNode;
	for(int i=0;i<A.rows();i++)
	{
		degree = 0;
		for(int j=0;j<A.cols();j++)
		{
			if(i!=j && A(i,j)==1)
				degree++;
		}
		if(degree >= k-1)
			preservedNode.push_back(i);
		if(degree < k-1)
		{
			for(int x=0;x<A.rows();x++)
			{
				A(x,i) = 0;
				A(i,x) = 0;
			}
		}
		//preservedNode.push_back(i);
	}
	/**
		For every preserved node v,generate Maximal Clique C containing v 
	*/
	vector<vector<int>> cliques;
	//printf("preservedNodes:");
	for(int i=0;i<preservedNode.size();i++)
	{
		//printf("%d,",preservedNode[i]);
		vector<vector<int>> maxCliques = BruteForceClique(A,preservedNode[i]);
		//check the maxCliques found is exist or not
		bool same = false;
		
		for(int j=0;j<maxCliques.size();j++)
		{
			same = false;
			for(int y=0;y<cliques.size();y++)
			{
				if(maxCliques[j].size() == cliques[y].size())
				{
					same = isTheSameClique(maxCliques[j],cliques[y]);
					if(same)
						break;
				}
			}
			if(!same)
			{
				cliques.push_back(maxCliques[j]);
			}
		}
	}
	//printf("\n");
	//print all maximal cliques
	//printCommunities(cliques,"maximal cliques");
	//printf("-------------------------------------------------\n");

	//prepare clique-clique overlap matrix
	int **overlapMatrix = new int*[cliques.size()];
	for(int i=0;i<cliques.size();i++)
		overlapMatrix[i] = new int[cliques.size()];

	for(int i=0;i<cliques.size();i++)
	{
		for(int j=i;j<cliques.size();j++)
		{
			if(i == j)
				overlapMatrix[i][j] = cliques[i].size();
			else{
				overlapMatrix[i][j] = getCommonNodesCount(cliques[i],cliques[j]);
				overlapMatrix[j][i] = overlapMatrix[i][j];
			}
		}
	}
	//get k-clique-communities based on the overlapMatrix
	vector<vector<int>> communities = getCommunities(overlapMatrix,k,cliques);
	//print communities in the console
	//printCommunities(communities,"communities");
	//
	string resultString = communityToString(communities[0], A);

	//
	resultString += "\n";
	int size = communities.size();
	for (int i = 0; i < communities.size(); i++)
	{
		for (int j = 0; j < communities[i].size(); j++)
		{
			resultString += std::to_string(communities[i][j]) + ",";
		}
		resultString += " ";
	}
	cout << resultString << endl;
	return resultString;
}
#endif