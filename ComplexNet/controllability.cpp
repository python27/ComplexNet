#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <utility>
#include <numeric>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include "controllability.h"
#include "graph.hpp"
#include "Eigen/Dense"
#include "Eigen/src/SVD/JacobiSVD.h"
using namespace std;
using Eigen::MatrixXd;
using Eigen::EigenSolver;
using Eigen::FullPivLU;

const double EPS = 1e-8;        // smaller than EPS will be regarded as 0.0;

//
// for person U, find a suitable job for him
//
bool DFS(scn::UGraph& graph, int u, map<int, int>& matchedR, map<int, bool>& seen)
{
    // visited all his interested job
    int n = matchedR.size();
    for (int j = n; j < 2 * n; ++j)
    {
        int v = j;
        if (graph.HasEdge(u, v) && seen[v] == false)
        {
            seen[v] = true;
            // if this job has not been assigned to other person
            // or if this job has been assigned to other person, but that person can
            // find an alternative job
            if (matchedR[v] == -1 || DFS(graph, matchedR[v], matchedR, seen) == true)
            {
                matchedR[v] = u;
                return true;
            }
        }
    }
    return false;
}

set<pair<int, int> > maxBipartiteMatch(scn::UGraph& graph, const vector<int>& outNodes, const vector<int>& inNodes)
{
    int m = outNodes.size();
    //int n = inNodes.size();

    map<int, int> matchedR;
    for (int i = 0; i < inNodes.size(); ++i)
    {
        matchedR[inNodes[i]] = -1;
    }

    int ans = 0;
    // for each person, assign him a job recursively
    for (int u = 0; u < m; ++u)
    {
        map<int, bool> seen;
        for (int i = 0; i < inNodes.size(); ++i) seen[inNodes[i]] = false;

        if (DFS(graph, u, matchedR, seen))
        {
            ans++;
        }
    }

    set<pair<int, int> > matchedEdges;
    // print the match result
    for (auto it = matchedR.begin(); it != matchedR.end(); ++it)
    {
        if (it->second != -1)
        {
            //cout << it->second << "---" << it->first << endl;
            matchedEdges.insert(make_pair(it->second, it->first));
        }
    }
    return matchedEdges;
}

set<int> structralControllability(scn::DGraph& g)
{
    int n = g.GetNumberOfNodes();

    // 根据输入的有向图，构建对应的无向二部图
    scn::UGraph bGraph;
    vector<int> outNodes;
    for (int i = 0; i < n; ++i)
    {
        bGraph.AddNode(i);
        outNodes.push_back(i);
    }

    vector<int> inNodes;
    for (int j = n; j < 2 * n; ++j)
    {
        bGraph.AddNode(j);
        inNodes.push_back(j);
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0;j < n; ++j)
        {
            if (g.HasEdge(i, j))
            {
                bGraph.AddEdge(i, j + n);
            }
        }
    }

    set<pair<int, int> > matchedEdges = maxBipartiteMatch(bGraph, outNodes, inNodes);
    set<int> matchedNodes;
    for (auto it = matchedEdges.begin(); it != matchedEdges.end(); ++it)
    {
        matchedNodes.insert(it->second);
    }
    set<int> unmatchedNodes;
    for (int j = n; j < 2 * n; ++j)
    {
        if (matchedNodes.count(j) == 0)
        {
            unmatchedNodes.insert(j-n);
        }
    }
    return unmatchedNodes;
}


/** 
 * Return the minimum number of driver nodes, also the set of driver nodes
 * ------
 * INPUT : g - the given graph
 * OUTPUT: the minimum set of driver nodes
 *         driverNodeSet - The set of driver nodes
 * ------
 * NOTE: This function calculate the driver nodes using Gauss Elimination
 *       with Time Complexity O(n^3). If you only need to calculate the 
 *       number of driver nodes, DO NOT care the set of driver nodes, please
 *       use the Function numberofDriverNodesExactControllability, it is much 
 *       more efficient.
 */
int exactControllability(scn::Graph& g, set<int>& driverNodeSet)
{
    int n = g.GetNumberOfNodes();

    // Get the adjacency matrix of the graph. Note: if Node ipoint to Node j, 
    // the true is j->i != 0, which is different from the traditional notation.
    vector<vector<double> > adjMatrix(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(g.HasEdge(i, j))
            {
                adjMatrix[j][i] = 1.0;
				adjMatrix[i][j] = 1.0;
            }
        }
    }  
    // Convert the Adjmatrix of the graph to the form of Eigen
    // for calculate the eigenvalues and eigenvectors
    MatrixXd m(n, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            m(i, j) = adjMatrix[i][j];
        }
    }

	//FullPivLU<MatrixXd> lu(m);
	Eigen::JacobiSVD<MatrixXd> lu(m);
	int myRank = lu.rank();

    // calculate the eigenvalue and eigenvectors
    EigenSolver<MatrixXd> es(m);
    auto res1 = es.eigenvalues();           // eigenvalues
    auto res2 = es.eigenvectors();          // eigenvectors

    // Covert back to the C++ matrix form
    vector<double> evalues(n, 0.0);
    vector<vector<double>> evectors(n, vector<double>(n, 0.0));
	for (int i = 0; i < n; ++i)
	{
		if (abs(res1[i].real() - 1E-8) <= 0.0)
		{
			evalues[i] = 0.0;
		}
		else
		{
			evalues[i] = res1[i].real();
		}		
	}
    for (int i = 0; i < n; ++i)
    {
        auto row = res2.row(i).real();
        for (int j = 0; j < n; ++j)
        {
            evectors[i][j] = row[j];
        }
    }

    vector<int> mu(n, 0);                   // geometric multiplicity for each eigenvalue
    auto eye = MatrixXd::Identity(n, n);    // Identity Matrix        
    for (int i = 0; i < n; ++i)
    {
        FullPivLU<MatrixXd> lu(evalues[i] * eye - m);
		lu.setThreshold(1e-8);
        mu[i] = n - lu.rank();
    }
    // find the maximum geometric multiplicity
    assert(n >= 1);
    int max_mu = mu[0];
    double max_eigenvalue = evalues[0];
    for (int i = 0; i < n; ++i)
    {
        if (mu[i] > max_mu)
        {
            max_mu = mu[i];
            max_eigenvalue = evalues[i];
        }
    }
    int numberOfDrivers = max(1, max_mu);

    // temp matrix \lambda_max * eye - A
    MatrixXd temp(n, n);
    temp = max_eigenvalue * eye - m;

	/*
	Eigen::ColPivHouseholderQR<MatrixXd> qrA(temp);
	qrA.setThreshold(1e-8);
	auto ans = qrA.colsPermutation().indices();
	for (int i = 0; i < ans.rows(); i++)
	{
		TRACE("%d\n", ans(i));
	}
	*/

	
    // Covert to C++ Matrix Form
    vector<vector<double>> temp2(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        auto row = temp.row(i).real();
        for (int j = 0; j < n; ++j)
        {
            temp2[i][j] = row[j];
        }
    }

    // Guass Elimatation to do Elementary column Transformation
    for (int k = 0; k < n; ++k)
    {
        // Find the largest pivot
        double maxPivot = abs(temp2[k][k]);
        double maxIndex = k;
        for (int j = k + 1; j < n; ++j)
        {
            if (abs(temp2[k][j]) > maxPivot)
            {
                maxPivot = abs(temp2[k][j]);
                maxIndex = j;
            }
        }
        // swap the possbible pivot to position, two columns
        if (maxIndex != k)
        {
            for (int i = 0; i < n; ++i) swap(temp2[i][k], temp2[i][maxIndex]);
        }

        // if encount the max pivot is still 0, skip the Elimination procedure
        if (temp2[k][k] == 0.0) continue;

        // eliminate all the columns under the pivot columns
        for (int j = k + 1; j < n; ++j)
        {
            assert(abs(temp2[k][k]) != 0.0);
            double c = (double)temp2[k][j] / (double)temp2[k][k];
            temp2[k][j] = 0.0;
            for (int i = k + 1; i < n; ++i)
            {
                temp2[i][j] -= c * temp2[i][k];
            }
        }
    }

    // Find all the Independent Rows of temp2
    set<int> independentRowSet;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            if (abs(temp2[i][j]) > EPS)
            {
                independentRowSet.insert(i);
                break;
            }
        }
    }
    // Find all the dependent rows, i.e. complement of independentRowSet;
    driverNodeSet.clear();
    for (int i = 0; i < n; ++i)
    {
        if (independentRowSet.count(i) == 0) driverNodeSet.insert(i);
    }
	

    return numberOfDrivers;
}

/**
 * Return the minimum number of driver nodes of the given graph
 * ------
 * INPUT:  g - the Graph without self-loop
 * OUTPUT: the minimum number of driver node that needed to be
 *         controlled to control the full network
 * ------
 * NOTE: The weight of every edge currently is 1, you can change 
 *       it when necessary.
 */
int numberofDriverNodesExactControllability(scn::Graph& g)
{
	int n = g.GetNumberOfNodes();

	// Get the adjacency matrix of the graph. Note: if Node ipoint to Node j, 
	// the true is j->i != 0, which is different from the traditional notation.
	vector<vector<double> > adjMatrix(n, vector<double>(n, 0.0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (g.HasEdge(i, j))
			{
				adjMatrix[j][i] = 1.0;
			}
		}
	}
	// Convert the Adjmatrix of the graph to the form of Eigen
	// for calculate the eigenvalues and eigenvectors
	MatrixXd m(n, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			m(i, j) = adjMatrix[i][j];
		}
	}
	// calculate the eigenvalue and eigenvectors
	//EigenSolver<MatrixXd> es(m);
	//auto res1 = es.eigenvalues();           // eigenvalues
	auto res1 = m.eigenvalues();

	// Covert back to the C++ matrix form
	vector<double> evalues(n, 0.0);
	for (int i = 0; i < n; ++i)
	{
		evalues[i] = res1[i].real();
		if ( abs (evalues[i] - 0.0) <= 1E-6 ) evalues[i] = 0.0;
		else evalues[i] = round(evalues[i] * 1E6 + 0.5) / 1E6;
	}
	set<double> tempEvalues(evalues.begin(), evalues.end());
	evalues.assign(tempEvalues.begin(), tempEvalues.end());

    vector<int> mu(n, 0);                   // geometric multiplicity for each eigenvalue
    auto eye = MatrixXd::Identity(n, n);    // Identity Matrix        
    for (size_t i = 0; i < evalues.size(); ++i)
    {
        FullPivLU<MatrixXd> lu(evalues[i] * eye - m);
		lu.setThreshold(1E-6);
        mu[i] = n - lu.rank();
    }
    // find the maximum geometric multiplicity
    assert(n >= 1);
    int max_mu = mu[0];
    double max_eigenvalue = evalues[0];
    for (size_t i = 0; i < evalues.size(); ++i)
    {
        if (mu[i] > max_mu)
        {
            max_mu = mu[i];
            max_eigenvalue = evalues[i];
        }
    }
    int numberOfDrivers = max(1, max_mu);

    return numberOfDrivers;
}

int numberofDriverNodesFastRankAlgorithm(scn::Graph& g)
{
	int n = g.GetNumberOfNodes();
	// 生成邻接矩阵
	vector<vector<double> > adjMatrix(n, vector<double>(n, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		if (g.HasEdge(i, j))
			adjMatrix[j][i] = 1.0;

	// 转换成 Eigen 形式
	Eigen::MatrixXd m(n, n);
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
		m(i, j) = adjMatrix[i][j];

	// 计算矩阵秩,利用 LU 分解
	Eigen::FullPivLU<Eigen::MatrixXd> lu(m);
	lu.setThreshold(1E-6);
	int myRank = lu.rank();

	// 利用 SVD 分解计算矩阵秩
	//Eigen::JacobiSVD<Eigen::MatrixXd> svd(m);
	//svd.setThreshold(1E-6);
	//int myRank = svd.rank();

	return n - myRank;
}

/*
 * Return the minimum number of driver nodes of graph represent by m
 * ------
 * INPUT :  m   -   state matrix of graph
 * OUTPUT:  the minimum number of driver nodes
 */
int numberofDriverNodesExactControllability(const MatrixXd& m)
{
    int n = m.rows();
    // calculate the eigenvalue and eigenvectors
    EigenSolver<MatrixXd> es(m);
    auto res1 = es.eigenvalues();           // eigenvalues

    // Covert back to the C++ matrix form
    vector<double> evalues(n, 0.0);
    for (int i = 0; i < n; ++i) evalues[i] = res1[i].real();

    vector<int> mu(n, 0);                   // geometric multiplicity for each eigenvalue
    auto eye = MatrixXd::Identity(n, n);    // Identity Matrix        
    for (int i = 0; i < n; ++i)
    {
        FullPivLU<MatrixXd> lu(evalues[i] * eye - m);
        mu[i] = n - lu.rank();
    }
    // find the maximum geometric multiplicity
    assert(n >= 1);
    int max_mu = mu[0];
    double max_eigenvalue = evalues[0];
    for (int i = 0; i < n; ++i)
    {
        if (mu[i] > max_mu)
        {
            max_mu = mu[i];
            max_eigenvalue = evalues[i];
        }
    }
    int numberOfDrivers = max(1, max_mu);

    return max(1, numberOfDrivers); 
}


/**
 * Return the Global Fitness of the Given seleted scheme D
 * ------
 * INPUT:   MatrixXd A   -   state Matrix
 *          MatrixXd B   -   Input Matrix
 *          MatrixXd D   -   chromosome scheme, a diag Matrix, its diag line 
 *                           is the corresponding chromosome
 * OUTPUT:  double num   -   the global fitness
 * ------
 * GlobalFitness Definition:
 * globalFiness : sum(dj) + c(rank(C) - N)^2, j = 1,2,3,...,P
 * where C = (BDM, ABDM, ..., A^(N-1)BDM)
 * ------
 * Ref: Ding J, Lu Y Z, Chu J. Studies on controllability of directed
 *      networks with extremal optimization[J].Physica A: Statistical
 *      Mechanics and its Applications, 2013, 392(24): 6603-6615.
 */
double globalFitness(const MatrixXd& A, const MatrixXd& B, const MatrixXd& D)
{
    // choose all the nonzeros col to form indicator matrix M
    int nonZeroColNum = 0;
    for (int j = 0; j < D.cols(); ++j)
    {
        if (!D.col(j).isZero()) nonZeroColNum++;
    }
    MatrixXd M(D.rows(), nonZeroColNum);
    int curColNum = 0;
    for (int j = 0; j < D.cols(); ++j)
    {
        if (!D.col(j).isZero()) M.col(curColNum++) = D.col(j);
    }
    //cout << "M:" << endl;
    //cout << M << endl;

    int N = A.rows();
    int P = B.cols();
    int r = M.cols();
    assert(A.rows() == A.cols());
    assert(A.rows() == B.rows());
    assert(B.cols() == D.rows());
    assert(D.rows() == D.cols());
    assert(M.rows() == D.rows());

    const double PENALTY_FACTOR = 1.0;
    double sumd = 0.0;
    for (size_t i = 0; i < P; ++i) sumd += D(i, i);

    MatrixXd C(N, N*r);
    MatrixXd BDM = B * D * M;
    // Eigen DONOT support power of matrix, has to compute A^i
    // using Naive algorithm, E = E * A;
    MatrixXd eye = MatrixXd::Identity(N, N);
    for (int i = 0; i <= N - 1; ++i)
    {
        C.block(0, i * r, N, r) = eye * BDM;
        eye = eye * A;
    }
    // compute rank(C)
    FullPivLU<MatrixXd> lu(C);
    lu.setThreshold(1e-8);
    double rankC = static_cast<double>(lu.rank());
    // compuate penality part vales
    double penalityValues = PENALTY_FACTOR * (rankC - (double)N) * (rankC - (double)N);

    return (sumd + penalityValues);
}


/**
 * Return the new chromosome after the index-th species has been mutation
 * INPUT:   MatrixXd D  -   the current chosen scheme
 *          index       -   the mutating position
 * OUTPUT:  MatrixXd D' -   the new chosen scheme(chromosome) after mutation
 *          theOtherFlipIndex - the randomly chosen flip index
 */
MatrixXd mutate(const MatrixXd& D, int index, int& theOtherFlipIndex)
{
    int P = D.rows();
    MatrixXd ans(D);
    srand((unsigned)time(NULL));
    // randomly choose another flip position to form a fliping window
    int anotherFlipIndex = -1;
    do{
        anotherFlipIndex = rand() % P;
    }while (anotherFlipIndex == index);

    // flip all the bits between the fliping window
    for (int i = min(index, anotherFlipIndex); 
        i <= max(index, anotherFlipIndex); ++i)
    {
        ans(i, i) = 1 - ans(i, i);
    }
    theOtherFlipIndex = anotherFlipIndex;
    return ans;
}

/**
 * Return the species with the worst (NOT EXACTLY the worst, will
 * choose according to probability) local fitness.
 * ------
 * INPUT :  localFitness -   The local fitness of each species
 * OUTPUT:  size_t       -   the chosen worst fitness species
 * ------
 * Choosing Method:
 * prob(k) = k(-\tao)
 */
int chooseWorstSpecies(vector<double> localFitness)
{
    const double tao = 3.0;

    int P = localFitness.size();

    // local fitness with index respectively
    vector<pair<double, int> > genes;
    for (size_t i = 0; i < localFitness.size(); ++i)
    {
        genes.push_back(make_pair(localFitness[i], i));
    }

    // sorting according to the localfitness of each gene
    sort(genes.begin(), genes.end());
    
    // calculate all the prob for each gene, the worst fit
    // -ness, the higher probability to choose
    vector<double> prob(P, 0.0);
    for (size_t i = 0; i < genes.size(); ++i)
    {
        prob[i] = pow((double)(i+1), -tao);
    }
    // normalization
    double totalProb = accumulate(prob.begin(), prob.end(), 0.0);
    for (size_t i = 0; i < genes.size(); ++i)
    {
        prob[i] /= totalProb;
    }

    // wheel selection algorithm
    vector<double> accuProb(P, 0.0);
    partial_sum(prob.begin(), prob.end(), accuProb.begin());
    assert(abs(accuProb[P-1] - 1.0) < 1e-9);
    srand((unsigned)time(NULL));
    double randomNum = (double)rand() / (double)RAND_MAX;

    auto it = upper_bound(accuProb.begin(), accuProb.end(), randomNum);
    assert(it != accuProb.end());
    int chosenIndex = it - accuProb.begin();
    int ans = genes[chosenIndex].second;

    return ans;
}

/**
 * EO algorithm optimize the minimum driver nodes for directed weighted networks.
 * ------
 * INPUT :  A       -   state node matrix
 *          B       -   input matrix
 * OUTPUT:  N       -   the number of minimum driver nodes
 *          Dbest   -   the best chosen scheme
 * ------
 * Ref: Ding J, Lu Y Z, Chu J. Studies on controllability of directed
 *      networks with extremal optimization[J].Physica A: Statistical
 *      Mechanics and its Applications, 2013, 392(24): 6603-6615.
 */
double extremalOptimizationAlgorithm(const MatrixXd& A, const MatrixXd& B, MatrixXd& Dbest, string filename)
{
    assert(A.rows() == A.cols());
    assert(A.rows() == B.rows());
    //int N = A.rows();
    int P = B.cols();

    const int MAX_ITERATION_TIMES = 1000;

    // open file to store optimization process info.
    string filepath = "output/" + filename;
    std::ofstream fout(filepath, ofstream::out);
    fout << "Iteration" << "\tCurrentGlobalFitness" << "\tBestGlobalFitness"
         << "\tCurrentControlNumber" << "\tBestControlNumber" << endl;

    // Step 1: randomly generate a initial chosen scheme D
    MatrixXd D(P, P);
    for (int i = 0; i < D.rows(); ++i)
    {
        for (int j = 0; j < D.cols(); ++j)
        {
            D(i, j) = 0;
        }
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < D.rows(); ++i)
    {
        D(i, i) = rand() % 2;
    }

    MatrixXd bestD(D);
    double bestDGlobalFitness = globalFitness(A, B, bestD);
    int iterationTimes = 0;

    while (iterationTimes < MAX_ITERATION_TIMES)
    {
        // step2(a): evaluate local fitness for each species
        vector<double> localFitness(P, 0.0);
        vector<int> otherFlipIndex(P, -1);
        for (int j = 0; j < P; ++j)
        {
            int otherIndex = -1;
            MatrixXd mutateOnSpeciesJ = mutate(D, j, otherIndex);
            localFitness[j] = globalFitness(A, B, mutateOnSpeciesJ) - bestDGlobalFitness;
            assert(otherIndex != -1);
            otherFlipIndex[j] = otherIndex;
        }

        // step2(b): choose the "worst" local fitness species
        int worstSpecies = chooseWorstSpecies(localFitness);

        // step2(c): mutate on the worst species to get better chosen scheme
        // MatrixXd nextD = mutate(D, worstSpecies);
        MatrixXd nextD(D);
        for (int i = min(worstSpecies, otherFlipIndex[worstSpecies]);
            i <= max(worstSpecies, otherFlipIndex[worstSpecies]); i++)
        {
            nextD(i, i) = 1 - nextD(i, i);
        }

        // step2(d): if current found D is better than best D, update best D
        D = nextD;
        double DGlobalFitness = globalFitness(A, B, D);

        // store optimization process info to file
        fout << iterationTimes << " " << DGlobalFitness << " " << bestDGlobalFitness
             << " " << D.trace() << " " << bestD.trace() << endl;

        cout << iterationTimes << " " << DGlobalFitness << " " << bestDGlobalFitness
            << " " << D.trace() << " " << bestD.trace() << endl;

        if (DGlobalFitness < bestDGlobalFitness)
        {
            bestD = D;
            bestDGlobalFitness = DGlobalFitness;
        }

        // step 3
        iterationTimes++;
    }
    
    // close file
    fout.close();

    Dbest = bestD;
    return bestDGlobalFitness;
}


//==================== Implementation of Genetic Algorithm BEGIN ====================//

/**
 * Constructor
 * -----------
 * INPUT :  stateMatrix     -   state nodes relationship
 *          inputMatrix     -   state nodes and control nodes relationship
 *          populationSize  -   the number of chromosomes
 *          crossoverProb   -   the probability of crossover
 *          mutationProb    -   the probability of mutation
 * OUTPUT:  void
 * ------------
 * NOTE:    This will generate the N random initial chromosomes
 */
GeneticAlgorithm::GeneticAlgorithm(MatrixXd stateMatrix, MatrixXd inputMatrix, 
    int populationSize, double crossoverProb, double mutationProb) : 
    A_(stateMatrix),
    B_(inputMatrix),
    population_size_(populationSize),
    probabilityOfCrossover_(crossoverProb),
    probabilityOfMutation_(mutationProb)
{
    int N = stateMatrix.rows();
    int P = inputMatrix.cols();
    population_.resize(populationSize);
    for (int i = 0; i < population_size_; ++i)
    {
        population_[i].fitness_ = 0.0;
        population_[i].binaryData_.resize(P);
        for (int j = 0; j < P; ++j)
        {
            population_[i].binaryData_[j] = rand() % 2;
        }
    }
}

/**
 * Deconstuctor
 */
GeneticAlgorithm::~GeneticAlgorithm()
{}

/**
 * Return the Fitness of given chromosome
 * --------
 * INPUT :  chromosome  -   chromosome to be evaluated
 * OUTPUT:  the fitness of chromosome & assign the fitness_
 * --------
 * Fitness Function
 * Given a chromosome of binary string binaryData, First Construct
 * the diag matrix D on the basis of binaryData, D is the chosen 
 * scheme, choose all the non zero columns of D to form a new matrix
 * M, the new B* = B_ x D x M, the objective function is to minimize
 * the number of chosen control nodes, i.e.
 *    min{d_j} where d_j is diag element of matrix D.
 * Also we need to get the full control of the network, so we need
 * satisfy the PBH rank condition, which says:
 *    rank(lambda * I_N - A, B*) = N, where lambda is eigenvalue of A
 * We add the penalty coefficient to the condition to get the final 
 * objective Fitness Function:
 *    min{d_j} + sum (rank(lambda * I_N - A, B*) - N)
 *    where lambda is all the distinct eigenvalues of A
 */
double GeneticAlgorithm::EvaluateFitness(Chromosome& chromosome)
{
    // construct D matrix based on the chromosome
    MatrixXd D(chromosome.binaryData_.asDiagonal());

    int nonZeroColNum = 0;
    for (int j = 0; j < D.cols(); ++j)
    {
        if (!D.col(j).isZero()) nonZeroColNum++;
    }
    MatrixXd M(D.rows(), nonZeroColNum);
    int curColNum = 0;
    for (int j = 0; j < D.cols(); ++j)
    {
        if (!D.col(j).isZero()) M.col(curColNum++) = D.col(j);
    }

    int N = A_.rows();
    int P = B_.cols();
    int r = M.cols();
    assert(A_.rows() == A_.cols());
    assert(A_.rows() == B_.rows());
    assert(B_.cols() == D.rows());
    assert(D.rows() == D.cols());
    assert(M.rows() == D.rows());

    const double PENALTY_FACTOR = 100.0;
    double sumdj = 0.0;
    for (int j = 0; j < P; ++j) sumdj += D(j, j);
    MatrixXd BDM = B_ * D * M;
    MatrixXd eye = MatrixXd::Identity(N, N);

    EigenSolver<MatrixXd> es(A_);
    auto egValues  = es.eigenvalues();
    auto egVectors = es.eigenvectors(); 
    VectorXd eigenValuesOfA(N);
    set<double> uniqueEigenValuesA;
    for (int i = 0; i < eigenValuesOfA.size(); ++i)
    {
        eigenValuesOfA[i] = abs(egValues[i].real()) < 1E-5 ? 0.0 : egValues[i].real();
        uniqueEigenValuesA.insert(eigenValuesOfA[i]);
        //cout << "eigen:" << eigenValuesOfA[i] << endl;
    }

    
    eigenValuesOfA.resize(uniqueEigenValuesA.size());
    int k = 0;
    for (auto it = uniqueEigenValuesA.begin(); it != uniqueEigenValuesA.end(); ++it)
    {
        eigenValuesOfA[k++] = *it;
    }

    double penalityParts = 0.0;
    for (int i = 0; i < eigenValuesOfA.size(); ++i)
    {
        double lmda = eigenValuesOfA[i];
        //cout << "lmda:" << lmda << endl;
        MatrixXd temp(N, N + r);
        temp.block(0, 0, N, N) = lmda * eye - A_;
        temp.block(0, N, N, r) = BDM;
        //cout << "temp:" << temp << endl;

        FullPivLU<MatrixXd> lu(temp);
        lu.setThreshold(1e-8);
        double rankTemp = static_cast<double>(lu.rank());
        //cout << "rankTemp:" << rankTemp << endl;

        penalityParts += (rankTemp - N) * (rankTemp - N);
    }
    //cout << "sumdj :" << sumdj << endl;
    //cout << "penalty parts:" << penalityParts << endl;
    double ans = sumdj + penalityParts * PENALTY_FACTOR;
    chromosome.fitness_ = ans;

    return ans;
}

/** 
 * Return the best Chromosome of current population base on the fitness
 * In this specific situation, the chromosome with the smallest fitness
 */
Chromosome GeneticAlgorithm::getBestChromosome()
{
    Chromosome ans;
    ans.fitness_ = 1E9;

    for (int i = 0; i < population_.size(); ++i)
    {
        if (population_[i].fitness_ < ans.fitness_)
        {
            ans = population_[i];
        }
    }
    return ans;
}

/** 
 * Select a chromosome proportional to its fitness from population
 * ------
 * NOTE:
 * The Roulette Selection is a little different from the traditional
 * method, since the traditional way keeps that the higher fitness the
 * better, here the objective is that the lower fitness the better, to
 * keep the chosen probability if proportational to its fitness, we 
 * adjust the method as follows
 * step 1:  sum {1 / f_i} = S
 * step 2:  P_i = 1 / (S * f_i) is the chosen probability of chromosome i
 *          with fitness f_i, this way works cause
 * Proof:
 * P_i * f_i = 1 / S = constant, thus can keep the equation invariant
 * P_i / P_j = f_j / f_i, i.e. the chose probablity is proportational to
 * fitness.
 */
Chromosome GeneticAlgorithm::RouletteSelection()
{
    vector<double> allFitness(population_.size(), 0.0);

    // the smaller fitness, the better, the more chance to be chosen
    for (size_t i = 0; i < population_.size(); ++i)
    {
        allFitness[i] = 1.0 / population_[i].fitness_;
    }
    double totalFitness = accumulate(allFitness.begin(), allFitness.end(), 0.0);
    
    for (size_t i = 0; i < allFitness.size(); ++i)
    {
        allFitness[i] = 1.0 / (totalFitness * population_[i].fitness_);
    }

    // normalization
    double totalProbs = accumulate(allFitness.begin(), allFitness.end(), 0.0);
    //cout << "after normalization:" << endl;
    for (size_t i = 0; i < allFitness.size(); ++i)
    {
        allFitness[i] /= totalProbs;
        //cout << allFitness[i] << endl;
    }

    // accumulate the fitness
    vector<double> accuFitness(allFitness.size(), 0.0);
    partial_sum(allFitness.begin(), allFitness.end(), accuFitness.begin());

    // generate a random number in [0, 1]
    double randomNum = static_cast<double>(rand()) / RAND_MAX;
    //cout << "random number:" << randomNum << endl;
    
    auto it = lower_bound(accuFitness.begin(), accuFitness.end(), randomNum);

    // The last element of accuFitness must be 1.0, but it may be 0.99999 due
    // to the division, so if the random number is 1.0, it will fail, to avoid
    // this situation, set the slice point to the last part.
    if (it == accuFitness.end())
    {
        it = accuFitness.end() - 1;
    }
    assert(it != accuFitness.end());
    int ansIndex = it - accuFitness.begin();

    return population_[ansIndex];
}


/**
 * Crossover Operator
 * ------
 * INPUT :  parent1 -   the first parent chromosome
 *          parent2 -   the second parent chromosome
 * OUTPUT:  child1  -   the first child after crossover
 *          child2  -   the second child after crossover
 * ------
 * NOTE: Here we use single-point crossover, the crossover point is
 *       chosen randomly. The child chromosome fitness is not update.
 */
void GeneticAlgorithm::Crossover(const Chromosome& parent1, const Chromosome& parent2, Chromosome& child1, Chromosome& child2)
{
    int geneSize = parent1.binaryData_.size();
    // randomly generate the crossover position
    int crossoverPos = rand() % geneSize;
    //cout << "gene size:" << geneSize << endl;
    //cout << "crossover pos:" << crossoverPos << endl;

    // init child = parent
    child1 = parent1;      
    child2 = parent2;

    // crossover
    for (int i = crossoverPos; i < geneSize; ++i)
    {
        child1.binaryData_[i] = parent2.binaryData_[i];
        child2.binaryData_[i] = parent1.binaryData_[i];
    }

    return;
}


/** 
 * Mutation Operator
 * ------
 * INPUT : chromesome - to be mutated chromosome
 * OUTPUT: chromosome - chromosome after mutation
 * ------
 * NOTE: Every gene is the chromosome is mutated randomly with
 *       the probability of mutation specified by Users.
 * 
 */
void GeneticAlgorithm::Mutation(Chromosome& chromosome)
{
    for (int i = 0; i < chromosome.binaryData_.size(); ++i)
    {
        double randomNum = static_cast<double>(rand()) / RAND_MAX;
        //cout << "random number:" << randomNum << endl;
        if (randomNum <= probabilityOfMutation_)
        {
            // bit flip
            chromosome.binaryData_[i] = 1 - chromosome.binaryData_[i];
        }
    }
    return;
}


/**
 * Genetic Algorithm Main Function
 * -------
 * INPUT :  isAdaptive  -   whether or not use the adaptive GA
 * OUTPUT:  double      -   the best fitness
 *          bestScheme  -   the best chosen scheme
 * -------
 * The Steps of GA:
 * Step 1: Evaluate the fitness of current population (N chromosomes)
 * Step 2: choose two parent from current population (RouletteSelect)
 *         crossover to generate two child choromosome
 * Step 3: mutate on the two child choromosome
 * Step 4: repeated Step2 and Step3 until N new chromosomes have been
 *         generated, assign current population with N new chromosomes
 * Step 5: If reach termination condition, terminate; else goto Step1.
 *
 */
double GeneticAlgorithm::Run(bool isAdaptive, Chromosome& bestScheme, vector<int>& numberOfControls, string outputFilename)
{
    // MAX iteration times threshold
    const int MAX_GENERATION = 1000;
    
    // MAX unchanged times threshold, if the global fitness
    // keep unchanged continuous for MAX_UNCHANGED times, then
    // terminate the algorithm
    const int MAX_UNCHANGED = 1000;

    // Minimum driver nodes that need to control the network
    int MINIMUM_DRIVER_NODES = numberofDriverNodesExactControllability(A_);

    // global best chromosome
    Chromosome globalBestChromosome;
    double globalMinFitness = 1E9;

    // initialize the number of controls output
    numberOfControls.clear();

    outputFilename = "output/" + outputFilename;
    ofstream fout(outputFilename, ofstream::out);
    if (!fout.is_open())
    {
        cerr << "Cannot open file to write !!!" << endl;
        return -1.0;
    }
    fout << "-----  ------- -------  ------- ------ ------- --------- --------" << endl;
    fout << "gener  global  average  current gCtrl  curCtrl crossover Mutation" << endl;
    fout << "ation  fitness fitness  fitness number number  Probs     Probs   " << endl;
    fout << "-----  ------- -------  ------- ------ ------- --------- --------" << endl;

    cout << "-----  ------- -------  ------- ------ ------- --------- --------" << endl;
    cout << "gener  global  average  current gCtrl  curCtrl crossover Mutation" << endl;
    cout << "ation  fitness fitness  fitness number number  Probs     Probs   " << endl;
    cout << "-----  ------- -------  ------- ------ ------- --------- --------" << endl;
    int curGeneration = 0;
    int curUnchangedCount = 0;
    while (curGeneration < MAX_GENERATION && curUnchangedCount < MAX_UNCHANGED)
    {
        // evaluate fitness of current population
        double avgFitness = 0.0;
        for (size_t i = 0; i < population_.size(); ++i)
        {
            EvaluateFitness(population_[i]);
            avgFitness += population_[i].fitness_;
        }
        avgFitness = avgFitness / static_cast<double>(population_.size());

        Chromosome curBestChromosome = getBestChromosome();

        /*
        cout << curGeneration 
             << "\t" << globalMinFitness 
             << "\t" << avgFitness
             << "\t" << curBestChromosome.fitness_
             << "\t" << globalBestChromosome.numberOfControlNodes()
             << "\t" << curBestChromosome.numberOfControlNodes()
             << "\t" << probabilityOfCrossover_
             << "\t" << probabilityOfMutation_ << endl;

        fout << curGeneration 
            << "\t" << globalMinFitness 
            << "\t" << avgFitness
            << "\t" << curBestChromosome.fitness_
            << "\t" << globalBestChromosome.numberOfControlNodes()
            << "\t" << curBestChromosome.numberOfControlNodes()
            << "\t" << probabilityOfCrossover_
            << "\t" << probabilityOfMutation_ << endl;
            */

        numberOfControls.push_back(globalBestChromosome.numberOfControlNodes());

        // has found the best fitness value, terminate the algorithm
        /*
        if (globalMinFitness == MINIMUM_DRIVER_NODES)
        {
            break;
        }
        */

        // update date the best chromosome
        if (curBestChromosome.fitness_ < globalMinFitness)
        {
            globalBestChromosome = curBestChromosome;
            globalMinFitness = curBestChromosome.fitness_;
            curUnchangedCount = 0;
        }
        else
        {
            curUnchangedCount++; 
        }

        // generation the next generation
        vector<Chromosome> nextPopulation;
        nextPopulation.reserve(population_.size());
        while (nextPopulation.size() < population_.size())
        {
            Chromosome parent1 = RouletteSelection();
            Chromosome parent2 = RouletteSelection();

            if (isAdaptive)
            {
                //-------------Adaptive GA Parameter P_c BEGIN--------------//
                const double k1 = 1.0;      // adjust coefficient
                const double k3 = 1.0;      // adjust coefficient

                double pc1 = 0.0;
                if (parent1.fitness_ <= avgFitness)
                {
                    pc1 = k1 * (parent1.fitness_ - curBestChromosome.fitness_) /
                        (avgFitness - curBestChromosome.fitness_);
                }
                else
                {
                    pc1 = k3;
                }

                double pc2 = 0.0;
                if (parent2.fitness_ <= avgFitness)
                {
                    pc2 = k1 * (parent2.fitness_ - curBestChromosome.fitness_) / 
                        (avgFitness - curBestChromosome.fitness_);
                }
                else
                {
                    pc2 = k3;
                }

                probabilityOfCrossover_ = (pc1 + pc2) / 2.0;
                // ---------- Adaptive GA Parameter P_c END ----------//
            }

            // crossover
            // if the current probability if smaller than the Crossover 
            // Probability, then do crossover; otherwise, keep unchanged
            Chromosome child1 = parent1;
            Chromosome child2 = parent2;

            double randomNum = static_cast<double>(rand()) / RAND_MAX;
            if (randomNum <= probabilityOfCrossover_)
            {
                Crossover(parent1, parent2, child1, child2); 
            }

            if (isAdaptive)
            {
                // ---------- Adaptive GA Parameter P_m BEGIN ----------//
                const double k2 = 0.5;      // adjust coefficient
                const double k4 = 0.5;      // adjust coefficient
                const double MIN_MUTATION_PROBABILITY = 0.03;

                double pm1 = 0.0;
                if (child1.fitness_ <= avgFitness)
                {
                    pm1 = k2 * (child1.fitness_ - curBestChromosome.fitness_) / 
                        (avgFitness - curBestChromosome.fitness_);
                }
                else
                {
                    pm1 = k4;
                }
                if (pm1 - 0.0 < 1E-8) pm1 = 0.03;

                probabilityOfMutation_ = pm1;
                Mutation(child1);

                double pm2 = 0.0;
                if (child2.fitness_ <= avgFitness)
                {
                    pm2 = k2 * (child2.fitness_ - curBestChromosome.fitness_) / 
                        (avgFitness - curBestChromosome.fitness_);
                }
                else
                {
                    pm2 = k4;
                }

                if (pm2 - 0.0 < 1E-8) pm2 = MIN_MUTATION_PROBABILITY;

                probabilityOfMutation_ = pm2;
                Mutation(child2);
                // ---------- Adaptive GA Parameter P_m END ----------//
            }
            else
            {
                // Not Adaptive, not change P_m, mutate directly on children
                Mutation(child1);
                Mutation(child2);
            }

            // add two child to next generation
            nextPopulation.push_back(child1);
            nextPopulation.push_back(child2);
        }

        // update current generation to next generation
        population_ = nextPopulation;

        // updata generation 
        curGeneration++;
    }

    fout.close();
    bestScheme = globalBestChromosome;
    return globalMinFitness;
}

void GeneticAlgorithm::PrintPopulation() const
{
    cout << "The number of chromosome : " << population_size_ << endl;
    for (size_t i = 0; i < population_.size(); ++i)
    {
        cout << "chromosome " << i << ":" << endl;
        population_[i].PrintChromosome();
    }
}

double computeDegreeHeterogeneity(const MatrixXd& A)
{
    int N = A.rows();
    assert(A.rows() == A.cols());

    vector<double> inDegree(N, 0.0);
    for (int i = 0; i < N; ++i)
    {
        inDegree[i] = 0.0;
        for (int j = 0; j < N; ++j)
        {
            if (abs(A(i,j)) > 1E-8)
            {
                inDegree[i] += 1;
            }
        }
    }

    vector<double> outDegree(N, 0.0);
    for (int j = 0; j < N; ++j)
    {
        outDegree[j] = 0;
        for (int i = 0; i < N; ++i)
        {
            if (abs(A(i, j)) > 1E-8)
            {
                outDegree[j] += 1;
            }
        }
    }

    vector<double> InOutDegree(N, 0.0);
    for (int i = 0; i < N; ++i) InOutDegree[i] = inDegree[i] + outDegree[i];

    double avgDegree = accumulate(InOutDegree.begin(), InOutDegree.end(), 0.0);
    avgDegree /= double(N);

    double h = 0.0;
    for (int i = 0; i < N; ++i)
    {
        h += (InOutDegree[i] - avgDegree) * (InOutDegree[i] -avgDegree);
    }

    h = sqrt(h / N);

    return h;
}

//==================== Implementation of Genetic Algorithm END ====================//