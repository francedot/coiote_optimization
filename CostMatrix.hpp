//
//  CostMatrix.hpp
//  ProvaOpt
//
//  Created by Gabriele Mosca on 17/11/16.
//  Copyright © 2016 Gabriele Mosca. All rights reserved.
//

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class CostMatrix {
public:

    CostMatrix(int dim);

    int loadMatrix(ifstream inputFile);


private:
    int dim;
    int **costs;
};

#endif /* CostMatrix_hpp */
