/*
 * CostMatrix.hpp
 */

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class CostMatrix {

public:
    /*
     * todo comments
     */
    CostMatrix(int cellsNumber, int periodsNumber, int peopleTypes);

    int loadMatrix();

    void getMinimumCost(int j, int *i, int *m, int *t, int ***people);

private:
    /*
     * todo comments
     */
    int dim;
    int ****costs;
    double *averageCosts; // Array of size N of avg costs
};

#endif /* CostMatrix_hpp */
