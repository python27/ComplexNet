#ifndef SYNCHRONIZATION_INCLUDE_H_
#define SYNCHRONIZATION_INCLUDE_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "graph.hpp"

double GetLambda2(scn::UGraph::pGraph);
double GetLambdaNRatioLambda2(scn::UGraph::pGraph pgraph);

class SASyncOptimization
{
public:
	SASyncOptimization(double T_Max = 100, double T_Min = 0.01, double rate = 0.995);
	void Run(scn::UGraph::pGraph pgraph);
public:
	bool IsConnectedGraph(scn::UGraph::pGraph pgraph);
	void DFS(scn::UGraph::pGraph graph, int src, std::vector<bool>& visited);
	double RatioOfEigenvalue(scn::UGraph::pGraph graph);	
private:
	double m_TMin;
	double m_TMax;
	double m_Rate;
};

#endif // SYNCHRONIZATION_INCLUDE_H_