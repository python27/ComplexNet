#pragma once
#include "graph.hpp"
#include "NetFunDll.h"
namespace scn
{
/**
 * @name ComputeAverageDegree - compute the average degree of the given graph
 * @return std::vector
 */
    NETWORKLIBDLL double ComputeAverageDegree(UGraph::pGraph graph);
/**
 * @name ComputeSpectrum - compute the spectrum of the adjacency
 * matrix of the given graph
 * @return std::vector
 */
      NETWORKLIBDLL valarray<double> ComputeSpectrum(UGraph::pGraph graph);
/**
 * @name GetLambda2AndRatio - compute the lambda 2 of Lapalacian
 * matrix and the the ratio of lambda2 and lambda n
 * @return std::pair<lambda2, ratio>
 */
      NETWORKLIBDLL void GetLambda2AndRatio(double &lambda2, double &ratio,UGraph::pGraph graph);
/**
 * @name DrawDegreeDistribution - Draw the histogram image of degree
 * distribution of the graph. The drawing tool is Gnuplot
 * @return std::string - return the path of generated image
 */
      NETWORKLIBDLL void GetDegreeDistribution(vector<pair<size_t, size_t>> &pairs,UGraph::pGraph graph);
/**
 * @name ComputeSpectralDensity - Compares the
 * @param slide - Identifier of
 * @return Mapping
 */
      NETWORKLIBDLL void ComputeSpectralDensity(std::unordered_map<double,double> &result,UGraph::pGraph graph,double slide);
/**
 * @name GetEntropyOfDegreeDist - compute the entropy of degree
 * distribution. This measurement is related to the robustness of
 * network
 * @return double
 */
      NETWORKLIBDLL double GetEntropyOfDegreeDist(UGraph::pGraph graph);
/**
 * @name GetShortestDistance - compute shortest distance between two
 * nodes, this function is implemented by breadth-first search, thus
 * only unweighted graph is valid.  
 * @param indexOfSource -  index Of Source 
 * @param indexOfTarget -  index Of Target 
 * @return size_t
 */
      NETWORKLIBDLL size_t GetShortestDistance(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget);
/**
 * @name GetDeodesicMatrix - Get a symmetric matrix whose element
 * reprensents the short-length between a pair of nodes
 * @return Matrix
 */
      NETWORKLIBDLL Matrix GetGeodesicMatrix(UGraph::pGraph graph);

/**
 * @name GetDiameter - compute the diameter of a given graph, the
 * default algorithm is SPFA
 * @return size_t
 */
      NETWORKLIBDLL size_t GetDiameter(UGraph::pGraph graph);
/**
 * @name GetDiameterAndAverageDistance - compute diameter and average
 * distance together. It is a efficient way if these two value are needed
 * @return pair<diameter, average_distance>
 */
      NETWORKLIBDLL void GetDiameterAndAverageDistance(size_t &Diamter,double &APL, UGraph::pGraph graph);
/**
 * @name GetShortestDistanceDistribution - compute the
 * distance distribution. It is a efficient way if these two value are needed
 * @return distribution
 */
	  NETWORKLIBDLL void GetShortestDistanceDistribution(vector<pair<size_t, size_t>> &distribution,UGraph::pGraph graph);
/**
 * @name GetAverageDistanceByDjikstra - compute average distance of a
 * given graph by Djikstra algorithm
 * @return double
 */
      NETWORKLIBDLL double GetAverageDistanceByDjikstra(UGraph::pGraph graph);
/**
 * @name GetAverageDistance - compute average distance of a given
 * graph by default SPFA algorithm
 * @return double
 */
      NETWORKLIBDLL double GetAverageDistance(UGraph::pGraph graph);


/**
 * @name GetClusteringCoeffDist - get the distribution of clustering
 * coefficient in the network
 * @param slide - the width of beam in the distribution. If this value
 * is equal to 0, there is no re-sampling operation
 * @return DVector
 */
      NETWORKLIBDLL void GetClusteringCoeffDist(vector<pair<double, double>> &distribution, UGraph::pGraph graph, double slide);

/**
 * @name GetPSDegreeCorrelation - get the list of degree correlation
 * proposed by Pastor-Satorras
 * @return DVector - list of pair<degree, degree-correlation>
 * @ref 2001+PhysRevLett+R.Pastor-Satorras+Dynamical and Correlation
 * Properties of the Internet
 */
      NETWORKLIBDLL void GetPSDegreeCorrelation(vector<pair<size_t, double>> &correlation,UGraph::pGraph graph);
/**
 * @name GetClusterDegreeCorre - compute the clustering-degree
 * correlation of the network
 * @return DVector: list of pair<degree, local clustering coefficient>
 */
/**
 * @name GetClusteringDegreeCorre - compute the clustering-degree
 * correlation and the global degree-correlation based clustering
 * coefficient of the network
 * @return pair<global clustering coefficient, list of pair<degree,
 * local clustering coefficient>
 */
      NETWORKLIBDLL void GetClusteringDegreeCorre(pair<double, vector<pair<size_t, double>>> &correlation,UGraph::pGraph graph);
/**
 * @name GetGlobalEfficiency - return the global efficiency of a given
 * network by default SPFA algorithm. This measurement quantifies
 * the efficiency of the network in sending information between vertices, assuming
 * that the efficiency for sending information between two vertices i and j is proportional
 * to the reciprocal of their distance. 
 * @return double
 * @ref 2001_PhysRevLett_V.Latora_Efficient Behavior of Small-World Networks
 */
      NETWORKLIBDLL double GetGlobalEfficiency(UGraph::pGraph graph);
/**
 * @name GetVulnerability - compute the vulnerability of whole network
 * or a single node. the vulnerability of a vertex can be defined as
 * the drop in global efficiency when the vertex and all its edges are 
 * removed from the network
 * @param indexOfNode -  when this argument is absent then this
 * function compute the vulnerability of whole network, else compute
 * the vulnerability of a node indexed by indexOfNode
 * @return double
 * @ref 2005_PhysRevE_V.Latora_Vulnerability and protection of infrastructure networks
 */
      NETWORKLIBDLL double GetVulnerability(UGraph::pGraph graph,size_t indexOfNode = UGraph::NaF);
/**
 * @name GetTransitivity - Get the transitivity of a given
 * network. The transitivity is the first kind of clustering
 * coefficient based on undirected unweighted network.
 * @return double
 * @ref 2001_PhysRevE_M.E.J.Newman_Scientific collaboration
 * networks. I. Network construction and fundamental results
 */
      NETWORKLIBDLL double GetTransitivity(UGraph::pGraph graph);
/**
 * @name GetClusteringCoefficient - Get the clustering coefficient of
 * a network.
 * @param indexOfNode -  return the clustering coefficient of specified vertex 
 * @param - return the average clustering coefficient of every vertex
 * in network
 * @return double
 */
     NETWORKLIBDLL double GetClusteringCoeff(UGraph::pGraph graph,size_t indexOfNode = UGraph::NaF);
/**
 * @name GetCyclicCoeff - compute the cyclic coefficient of network
 * @param indexOfNode -  get the cyclic coefficient of the vertex
 * @param  -  return the average cyclic coefficient of all verteices
 * in network
 * @return double
 */
      NETWORKLIBDLL double GetCyclicCoeff(UGraph::pGraph graph,size_t indexOfNode = UGraph::NaF);
/**
 * @name GetRichClubCoeff - compute the rich-club coefficient of
 * degree k of a given network
 * @param degree -  input degree 
 * @return double
 */
      NETWORKLIBDLL double GetRichClubCoeff(UGraph::pGraph graph,size_t degree);
/**
 * @name GetPearsonCorrCoeff - compute the Pearson correlation
 * coefficient of the given network. When this coefficient is
 * positive, the network is assortative, when it is negative, the
 * network is disassortative
 * @return double
 */
      NETWORKLIBDLL double GetPearsonCorrCoeff(UGraph::pGraph graph);
/**
 * @name GetSearchInfo - compute search information to locate vertex
 * 'indexOfTarget' from vertex 'indexOfSource' 
 * @param indexOfSource -  index Of Source 
 * @param indexOfTarget -  index Of Target 
 * @return double
 * @ref 2005_PhysRevLett_M.Rosvall_Networks and Cities An information Perspective
 */
      NETWORKLIBDLL double GetSearchInfo(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget);
/**
 * @name GetAverageSearchInfo - compute average search information
 * through all pairs of nodes in a network
 * @return double
 * @ref 2005_PhysRevLett_M.Rosvall_Networks and Cities An information Perspective
 */
      NETWORKLIBDLL double GetAverageSearchInfo(UGraph::pGraph graph);    
/**
 * @name GetAccessInfo - compute how difficult it is to locate a
 * vertex in the network from the given node designated by indexOfNode
 * @param indexOfNode -  the given node
 * @return double
 */
      NETWORKLIBDLL double GetAccessInfo(UGraph::pGraph graph,size_t indexOfNode);
/**
 * @name GetHideInfo - compute how difficult it is to find the given
 * node specified by indexOfNode from other vertices in the network
 * @param indexOfNode -  index Of Node 
 * @return double
 */
      NETWORKLIBDLL double GetHideInfo(UGraph::pGraph graph,size_t indexOfNode);
/**
 * @name GetBetweennessCentrality - compute the betweenness centrality
 * of an given node
 * @param indexOfNode -  index Of Node 
 * @return double
 */
      NETWORKLIBDLL double GetBetweennessCentrality(UGraph::pGraph graph,size_t indexOfNode);
/**
 * @name FindClosureGroup - find a community in which the shortest length of
 * any pairs of nodes are less than "length"
 * @param indexOfSeed -  the found community contains this node 
 * @param length -  length 
 * @return IndexList - the node list of this community
 */
      NETWORKLIBDLL IndexList FindClosureGroup(UGraph::pGraph graph,size_t indexOfSeed, size_t length);
/**
 * @name RandomWalkByURW - unrestricted random walk
 * @param indexOfSource - index Of Source 
 * @param indexOfTarget - index Of Target 
 * @return size_t - number of steps of this random walk
 */
      NETWORKLIBDLL size_t RandomWalkByURW(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget);
/**
 * @name RandomWalkByNRRW - no-retracting random walk
 * @param indexOfSource - index Of Source 
 * @param indexOfTarget - of index Of Target 
 * @return size_t - number of steps of this random walk
 */
      NETWORKLIBDLL size_t RandomWalkByNRRW(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget);
/**
 * @name RandomWalkBySARW - self-avoiding random walk
 * @param indexOfSource - Number of index Of Source 
 * @param indexOfTarget - Number of index Of Target 
 * @return size_t
 */
      NETWORKLIBDLL size_t RandomWalkBySARW(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget);
/**
 * @name MFPTByRandomWalk - Mean First-Passage Time by random walk
 * @return size_t
 */
      NETWORKLIBDLL size_t MFPTofRandomWalk(UGraph::pGraph graph);
/**
 * @name MRTofRandomWalk - Mean Return-time by a random walker. the
 * step the walker returns to a node first since it left the node. 
 * @return size_t
 */
      NETWORKLIBDLL size_t MRTofRandomWalk(UGraph::pGraph graph);
 /**Private using
 * @name RunDjikstra - single source shorest path of Djikstra
 * @param indexOfSource -  index Of Source 
 * @return void
 */
      NETWORKLIBDLL void RunDjikstra(UGraph::pGraph graph,size_t indexOfSource,std::unordered_map<size_t,size_t> &distance);
/**Private using
 * @name RunSPFA - single source, shorest path of SPFA 
 * @param indexOfSource -  index Of Source 
 * @return void
 */
      NETWORKLIBDLL void RunSPFA(UGraph::pGraph graph,size_t indexOfSource,std::unordered_map<size_t,size_t> &distance);
/**private using
 * @name GetNumberOfShortestPath - compute the number of shorest path
 * from indexOfSource to indexOfTarget that passing through the indexOfThrough
 * @param indexOfSource -  index Of Source 
 * @param indexOfTarget -  index Of Target 
 * @param indexOfThrough -  index Of Through 
 * @param  -  if this argument is empty, this function just compute
 * the number of shorest path without passing any specified node
 * @return std::pair<number of shortest path from source to target,
 * number of shortest path that passing through the indexOfThrough>,
 * if the third argument is absent, the second returned value is same
 * to the first one
 */
      NETWORKLIBDLL std::pair<size_t, size_t> GetNumberOfShortestPath(UGraph::pGraph graph,size_t indexOfSource, size_t indexOfTarget,
							size_t indexOfThrough = UGraph::NaF);      
};
