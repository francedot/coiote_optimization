/*
 * Solution.hpp
 */

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <vector>
#include "SolutionCell.hpp"

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
        Solution(Solution *initialSolution, int n);
        //TODO: documentation (n = number of cells invariant)

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        SolutionCell *generateNeighborhood();

    private:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        vector<SolutionCell> cells;
};

#endif /* Solution_hpp */
