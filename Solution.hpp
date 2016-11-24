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

    void
    populateSolution(Solution *initialSolution, int n, int *remainingTask, int ***people, CostMatrix *costs, int N);

    SolutionCell *generateNeighborhood();
    void generateInitialSolution(int *remainingTask, int ***people, CostMatrix *costs, int N);
    void addSolutionCell(SolutionCell toAdd);
    SolutionCell getCell(int n);

private:
    /*
     * todo comments
     */
    vector<SolutionCell> cells;
    int totalCost;
};

#endif /* Solution_hpp */
