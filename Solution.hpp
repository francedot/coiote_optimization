/*
 * Solution.hpp
 */

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <vector>
#include "SolutionCell.hpp"
#include "CostMatrix.hpp"

using namespace std;

class Solution {

public:
    /*
     * todo comments
     */
    Solution();

    Solution(const Solution &toCopy);

    vector<Solution *> *
    generateNeighborhood(int size, int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N);

    void generateInitialSolution(int *remainingTask, int sizeOfTasks, int ***people, CostMatrix *costs, int N);

    void addSolutionCell(SolutionCell *toAdd);

    Solution *generateNeighbor(int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N);

    SolutionCell getCell(int n);

    int evaluate();

private:
    /*
     * todo comments
     */
    vector<SolutionCell> cells;

    void populateSolution(Solution *initialSolution, int n, int *task, int sizeOfTasks, int ***people,
                          CostMatrix *costs, int N);

    int totalCost;

};

#endif /* Solution_hpp */
