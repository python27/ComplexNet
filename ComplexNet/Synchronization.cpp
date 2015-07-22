#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "graph.hpp"
#include "Synchronization.h"
#include "Eigen/Dense"
#include "Eigen/src/SVD/JacobiSVD.h"
using namespace std;

double GetLambda2(scn::UGraph::pGraph pgraph)
{
	Matrix lpMatrix = pgraph->GetLaplacianMatrix();
	int n = lpMatrix.GetWidth();

	Eigen::MatrixXd LM(n, n);
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
		LM(i, j) = (double)lpMatrix(i, j);

	Eigen::EigenSolver<Eigen::MatrixXd> es(LM);
	auto res1 = es.eigenvalues();
	
	vector<double> v(n, 0.0);
	for (int i = 0; i < n; ++i) v[i] = res1(i).real();
	sort(v.begin(), v.end(), greater<double>());
	assert(n >= 2);
	return v[1];
}

double GetLambdaNRatioLambda2(scn::UGraph::pGraph pgraph)
{
	Matrix lpMatrix = pgraph->GetLaplacianMatrix();
	int n = lpMatrix.GetWidth();

	Eigen::MatrixXd LM(n, n);
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
		LM(i, j) = (double)lpMatrix(i, j);
	
	auto res1 = LM.eigenvalues();

	vector<double> v(n, 0.0);
	for (int i = 0; i < n; ++i)
	{
		v[i] = res1(i).real();
		v[i] = round(v[i] * 1E8) / 1E8;	 // precision 8 digit
	}
	sort(v.begin(), v.end(), greater<double>());
	assert(n >= 2);

	//std::ofstream fout("LNRatioL2.txt", std::ofstream::app);
	//fout << "LN = " << v[n - 1] << "; L2 = " << v[1] << endl;
	return v[n - 1] / v[1];
}


SASyncOptimization::SASyncOptimization(double T_MAX, 
	double T_MIN, 
	double rate) : m_TMax(T_MAX), m_TMin(T_MIN), m_Rate(rate)
{}

double SASyncOptimization::RatioOfEigenvalue(scn::UGraph::pGraph graph)
{
	return GetLambdaNRatioLambda2(graph);
}

void SASyncOptimization::DFS(scn::UGraph::pGraph pgraph, int src, std::vector<bool>& visited)
{
	int n = pgraph->GetNumberOfNodes();
	visited[src] = true;
	for (int j = 0; j < n; ++j)
	{
		if (pgraph->HasEdge(src, j) && !visited[j])
		{
			DFS(pgraph, j, visited);
		}
	}
}

bool SASyncOptimization::IsConnectedGraph(scn::UGraph::pGraph pgraph)
{
	int n = pgraph->GetNumberOfNodes();
	vector<bool> visited(n, false);
	assert(n >= 1);
	DFS(pgraph, 0, visited);

	for (size_t i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == false) return false;
	}
	return true;
}

void SASyncOptimization::Run(scn::UGraph::pGraph pgraph)
{
	int N = pgraph->GetNumberOfNodes();
	int iterTimes = 0;
	double curRatio = 0.0;
	double nextRatio = 0.0;

	std::ofstream fout("./Results/SyncOptimizationBySA.txt");
	fout << "Iteration CurSyncRatio NextSyncRatio" << endl;
	double T = m_TMax;
	int u1 = -1, v1 = -1;	// first edge
	int u2 = -1, v2 = -1;	// second edge
	while (T > m_TMin)
	{
		curRatio = RatioOfEigenvalue(pgraph);

		// choose (u1, v1) as to be removed edge
		// choose (u2, v2) as to be added edge
		while (true)
		{
			// choose two edges to rewiring
			do {
				u1 = rand() % N;
				v1 = rand() % N;
				u2 = rand() % N;
				v2 = rand() % N;
			} while (!(u1 != v1 && u2 != v2 && pgraph->HasEdge(u1, v1) && !pgraph->HasEdge(u2, v2)));

			// try rewiring
			pgraph->RemoveEdge(u1, v1);
			pgraph->AddEdge(u2, v2);

			// if connected, goto next
			if (IsConnectedGraph(pgraph))
			{
				break;
			}
			else // if not connected, reject rewiring, rechoose two edges
			{
				pgraph->AddEdge(u1, v1);
				pgraph->RemoveEdge(u2, v2);
			}
		}

		// compute the sync ratio of the next generated graph
		nextRatio = RatioOfEigenvalue(pgraph);
		double dE = nextRatio - curRatio;

		fout << iterTimes << " " << curRatio << " " << nextRatio << endl;
		if (dE <= 0.0)
		{
			// accept the rewiring, do nothing
		}
		else 
		{
			double randomNum = (double)rand() / RAND_MAX;
			double acceptProb = exp(-dE / T);
			if (randomNum <= acceptProb)
			{
				// accept the rewiring, do nothing
			}
			else
			{
				// reject the rewiring by restore the (u1, v1) and (u2, v2) edges
				pgraph->AddEdge(u1, v1);
				pgraph->RemoveEdge(u2, v2);
			}
		}		
		T = m_Rate * T; // annealling
		iterTimes++;
	}
	fout.close();
}

