/*
 * CostMatrix.hpp
 */

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class CostMatrix {

public:
    /*
     * todo comments
     */
    CostMatrix(int cellsNumber, int periodsNumber, int peopleTypes);

    int loadMatrix();

private:
    /*
     * todo comments
     */
    int dim;
    int **costs;
};

#endif /* CostMatrix_hpp */
