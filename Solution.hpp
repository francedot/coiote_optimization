//
//  Solution.hpp
//  ProvaOpt
//
//  Created by Gabriele Mosca on 18/11/16.
//  Copyright © 2016 Gabriele Mosca. All rights reserved.
//

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <vector>
#include "SolutionCell.hpp"

using namespace std;

class Solution {
public:
    Solution();

    Solution(Solution *initialSolution, int n); //TODO: documentation (n = number of cells invariant)
    SolutionCell *generateNeighborhood();

private:
    vector<SolutionCell> cells;
};

#endif /* Solution_hpp */
