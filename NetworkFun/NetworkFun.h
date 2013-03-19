#pragma once
#include "Network.h"
#include "NetFunDll.h"
NETWORKLIBDLL int ReadNetworkFile(char * filename,NETWORK *ntwk);
NETWORKLIBDLL void CalculateDegrees(NETWORK *ntwk);
NETWORKLIBDLL int CalculateNetworkDegreeDistribution(NETWORK *ntwk,double *degree,double *prob);
NETWORKLIBDLL int CalculateNetworkDegreeCorrelation(NETWORK *ntwk,double *degree,double *corr);
NETWORKLIBDLL int CalculateNetworkClusterCoeff(NETWORK *ntwk);
NETWORKLIBDLL int CalculateNetworkClusteringDistribution(NETWORK *ntwk,double *cluster,double *prob);
NETWORKLIBDLL int CalculateNetworkClusterDegreeCorrelation(NETWORK *ntwk,double *degree,double *corr);
NETWORKLIBDLL void CalculateNetworkAverageDistanceAndDiameter(NETWORK *ntwk);
NETWORKLIBDLL long int ComputeDistance(NETWORK ntwk,long int Node1,long int Node2);
NETWORKLIBDLL size_t GetShortestDistanceA(NETWORK ntwk,size_t indexOfSource, size_t indexOfTarget);
NETWORKLIBDLL int RandomNetworkGenerate(char * filename,long int m_ran_nodes,long int m_ran_edges);
NETWORKLIBDLL int RegularNetworkGenerate(char * filename,long int m_reg_nodes,long int m_reg_neighbors);
NETWORKLIBDLL int WSSmallWorldNetworkGenerate(char * filename,long int m_wssmall_nodes,long int m_wssmall_neighbors,double m_wssmall_prob);
NETWORKLIBDLL int NWSmallWorldNetworkGenerate(char * filename,long int m_nwsmall_nodes,long int m_nwsmall_neighbors,double m_nwsmall_prob);
NETWORKLIBDLL int BANetworkGenerate(char * filename,long int m_ba_inodes,long int m_ba_onodes,long int m_ba_iterations);
NETWORKLIBDLL int EdgeIterationDeterminSWNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int DeterminURTNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int DeterminSWURTNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int DeterminTSSWNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int PinWheelDeterminSWNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int SwirlDeterminSWNetworkGenerate(char *filename,long int m_iterations);
NETWORKLIBDLL int DeterminTSSFSWNetworkGenerate(char *filename, long int m_nodes);
NETWORKLIBDLL int TriangleExtendedDSWNGenerate(char *filename, long int m_iterations);
NETWORKLIBDLL void RenormalizeByBoxCountingA(NETWORK *ntwk,size_t length);
NETWORKLIBDLL int CalculateNetworkCommunityKernighanLin(NETWORK ntwk,int numone,int numtwo,int *comlist);
NETWORKLIBDLL void CalculateNodesCentralityNomination(NETWORK *ntwk,double *feature,double *temp,double*temp1);
NETWORKLIBDLL void CalculateNodesCentralityAppFlowBetweenness(NETWORK *ntwk,double *feature,double *temp);
NETWORKLIBDLL void CalculateNodesCentralityAppEigenvector(NETWORK *ntwk,double *feature,double *temp);
NETWORKLIBDLL void CalculateNodesCentralityCloseness(NETWORK *ntwk,double *feature);
NETWORKLIBDLL void CalculateHistogramDouble(double *input,double *output,long int len,long int bins,double min,double max);
NETWORKLIBDLL void CalculateHistogramLongint(long *input,double *output,long int len,long int bins,long int min,long int max);
NETWORKLIBDLL void CalculateHistogramInt(WORD *input,double *output,int len,int bins,WORD min,WORD max);
NETWORKLIBDLL void CalculateHistogramChar(BYTE *input,double *output,int len,int bins,BYTE min,BYTE max);