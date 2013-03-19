#pragma once
#include <vector>
#include <map>

#define	MAXLINKS 1000000
#define	MAXNODES 500000
using   namespace   std;
struct Edge
{
	long int Head;
	long int Tail;
	double Weight;
	Edge()
	{
		Head=-1;
		Tail=0;
		Weight=1.0;
	}
	Edge(long int source, long int target, double weight = 1.0)
	{
		Head=source;
		Tail=target;
		Weight=weight;
	}
};

struct Node
{
    long int NodeNo;
    char NodeName[21];
    double X;
    double Y;
    double Z;
	long int Degree;
    long int Indegree;
    long int Outdegree;
    double Strength;
	double Instrength;
	double Outstrength;
    double Clustercoeff;
    double Inclustercoeff;
    double Outclustercoeff;
	multimap<long int, Edge>  Edges;
	double Closeness;
	double Betweenness;
	double AppEigenve;
	double AppEigenvetemp;
	double AppBetweenness;
	double AppBetw;
	double AppBetwtemp;
	double Nomination;
	double Nominationtemp;
	double Nominationtest;
	int    KLComunNum;
};

struct NETWORK
{
    vector <Node> Net;
	vector <long int> DistanceNum;
	bool Weighted;
    bool Directed;
    long int NodeNumber;
    long int LinkNumber;
    long int DegreeNumber;
    long int IndegreeNumber;
    long int OutdegreeNumber;
	long int StrengthNumber;
    long int InstrengthNumber;
    long int OutstrengthNumber;
	long int ClustercoeffNumber;
	long int InclustercoeffNumber;
    long int OutclustercoeffNumber;
	long int Diameter;
    double Averagedegree;
    double Averageindegree;
    double Averageoutdegree;
	double Averagestrength;
    double Averageinstrength;
    double Averageoutstrength;
    double Clustercoeff;
    double Inclustercoeff;
    double Outclustercoeff;
    double AverageDistance;
};

