#ifndef CONTROLLABILITY_INCLUDED_
#define CONTROLLABILITY_INCLUDED_

#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include "graph.hpp"
#include "Eigen/Dense"
using Eigen::MatrixXd;
using Eigen::VectorXd;

///================= Structral Controllability Algorithm Begin =================///
/**
 * The following functions calculate the controllaiblity using Maximum Matching.
 * Ref: Liu Y Y, Slotine J J, Barab¨¢si A L. Controllability of complex networks[J]. 
 *      Nature, 2011, 473(7346): 167-173.
 */ 
bool DFS(scn::UGraph& graph, int u, std::map<int, int>& matchedR, std::map<int, bool>& seen);
std::set<std::pair<int, int> > maxBipartiteMatch(scn::UGraph& graph, const std::vector<int>& outNodes, const std::vector<int>& inNodes);
std::set<int> structralControllability(scn::DGraph& g);
///================= Structral Controllability Algorithm END ==================///



///================= Exact Controllability Algorithm BEGIN ====================///

/**
 * This functions return the mininum number of driver nodes based on the exact 
 * controllability theory.
 * Ref: Exact controllability of complex networks. Zhengzhong Yuan, Chen Zhao, Zengru Di
 *      Wen-Xu Wang & Ying-Cheng Lai. Nature Communications, 2013.
 */
// Return the number of driver nodes and the set of driver nodes
int exactControllability(scn::Graph& g, std::set<int>& driverNodeSet);
// Return only the number of driver nodes
int numberofDriverNodesExactControllability(scn::Graph& g);
int numberofDriverNodesFastRankAlgorithm(scn::Graph& g);
/*
 * Return the minimum number of driver nodes of graph represent by m
 * ------
 * INPUT :  m   -   state matrix of graph
 * OUTPUT:  the minimum number of driver nodes
 */
int numberofDriverNodesExactControllability(const MatrixXd& m);

///================= Exact Controllability Algorithm END ====================///



///==== Fllowing is EO algorithm for controllability optimization Begin =====///

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
double globalFitness(const MatrixXd& A, const MatrixXd& B, const MatrixXd& D);

/**
 * Return the new chromosome after the index-th species has been mutation
 * INPUT:   MatrixXd D  -   the current chosen scheme
 *          index       -   the mutating position
 * OUTPUT:  MatrixXd D' -   the new chosen scheme(chromosome) after mutation
 */
MatrixXd mutate(const MatrixXd& D, int index, int& theOtherFlipIndex);

/**
 * Return the species with the worst (NOT EXACTLY the worst, will choose 
 * according to probability) local fitness.
 * INPUT :
 * ------
 * localFitness -   The local fitness of each species
 * OUTPUT:
 * ------
 * size_t       -   the chosen worst fitness species
 * Choosing Method:
 * prob(k) = k(-\tao)
 */
int chooseWorstSpecies(std::vector<double> localFitness);

/**
 * EO algorithm optimize the minimum driver nodes for directed weighted networks.
 * ------
 * INPUT :  A   -   state node matrix
 *          B   -   input matrix
 * OUTPUT:  N   -   the number of minimum driver nodes
 *          Dbest-  the best chosen scheme
 *          filename - store the optimization process.
 * ------
 * Ref: Ding J, Lu Y Z, Chu J. Studies on controllability of directed
 *      networks with extremal optimization[J].Physica A: Statistical
 *      Mechanics and its Applications, 2013, 392(24): 6603-6615.
 */
double extremalOptimizationAlgorithm(const MatrixXd& A, const MatrixXd& B, MatrixXd& Dbest, std::string filename="temp.txt");

///===== Fllowing is EO algorithm for controllability optimization END ======///


///===== Genetic Algorithm for Controllability Optimization BEGIN =====///

/**
 * GA Optimization Usage:
 * ------
 * Example:
 * 1. srand((unsigned)time(NULL));
 * 2. GeneticAlgorithm ga(A, B, 10, 0.90, 0.05);
 * 3. double ans; Chromosome ansChromosome
 *    ans = ga.run(ansChromosome)
 * 4. the ans and ansChromosome is the result
 * ------
 */

// Definition of Chromosome
struct Chromosome
{
    VectorXd binaryData_;           // binary 01 string
    double fitness_;                // fitness of current chromosome
public:
    // constructor
    Chromosome():fitness_(0.0){}
public:
    int numberOfControlNodes() const
    {
        double ans = 0.0;
        for (size_t i = 0; i < binaryData_.size(); ++i)
        {
            ans += binaryData_[i];
        }
        ans = static_cast<int>(ans);
        return ans;
    }
public:
    void PrintChromosome() const
    {
        std::cout << "\tBString:";
        for (size_t i = 0; i < binaryData_.size(); ++i)
        {
            std::cout << binaryData_[i];
        }
        std::cout << std::endl;
        std::cout << "\tFitness:" << fitness_ << std::endl;
    }
};

// Declaration of Class Genetic Algorithm
class GeneticAlgorithm
{
public:
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
    GeneticAlgorithm(MatrixXd stateMatrix, MatrixXd inputMatrix, 
        int populationSize, double crossoverProb, double mutationProb);
    // Deconstructor
    ~GeneticAlgorithm();
public:
   /**
    * Return the Fitness of given chromosome
    * --------
    * INPUT :  chromosome  -   chromosome to be evaluated
    * OUTPUT:  the fitness of chromosome & assign the fitness_
    * --------
    * Fitness Function:
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
    double EvaluateFitness(Chromosome& chromosome);

    /** 
     * Return the best Chromosome of current population base on the fitness
     * In this specific situation, the chromosome with the smallest fitness
     */
    Chromosome getBestChromosome();

   /* 
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
    Chromosome RouletteSelection();

    /**
     * Crossover
     * ------
     * INPUT :  parent1 -   the first parent chromosome
     *          parent2 -   the second parent chromosome
     * OUTPUT:  child1  -   the first child after crossover
     *          child2  -   the second child after crossover
     * ------
     * NOTE: Here we use single-point crossover, the crossover point is
     *       chosen randomly. The child chromosome fitness is not update.
     */
    void Crossover(const Chromosome& parent1, const Chromosome& parent2, Chromosome& child1, Chromosome& child2);
    
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
    void Mutation(Chromosome& chromosome);
    /**
     * Genetic Algorithm Main Function
     * -------
     * INPUT :  isAdaptive  -   whether or not use the adaptive GA
     * OUTPUT:  double      -   the best fitness
     *          bestScheme  -   the best chosen scheme
     *          numberOfControls -  the number of contorls change process
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
    double Run(bool isAdaptive, Chromosome& bestScheme, std::vector<int>& numberOfControls, std::string outputFilename);
//protected:
    std::vector<Chromosome> population_;    // current population
    int population_size_;                   // number of chromosome
    double probabilityOfCrossover_;         // crossover probability
    double probabilityOfMutation_;          // mutation probability
public:
    void PrintPopulation() const;
private:
    MatrixXd A_;                            // state matrix
    MatrixXd B_;                            // input matrix
};

double computeDegreeHeterogeneity(const MatrixXd& A);


///===== Genetic Algorithm for Controllability Optimization END =====///


#endif