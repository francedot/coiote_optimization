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
         * TODO WRITE DESCRIPTION HERE
         */
        Solution();

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        void
        populateSolution(Solution *initialSolution, int n, int *remainingTask, int ***people, CostMatrix *costs, int N);

    void generateInitialSolution(int *remainingTask, int ***people, CostMatrix *costs, int N);

    void addSolutionCell(SolutionCell toAdd);


    SolutionCell getCell(int n);
    private:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        vector<SolutionCell> cells;
    int totalCost;
};

#endif /* Solution_hpp */
