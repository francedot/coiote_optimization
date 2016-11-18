//
//  SolutionCell.hpp
//  ProvaOpt
//
//  Created by Gabriele Mosca on 17/11/16.
//  Copyright © 2016 Gabriele Mosca. All rights reserved.
//

#ifndef SolutionCell_hpp
#define SolutionCell_hpp

#include <stdio.h>
#include <stdlib.h>

class SolutionCell {
public:
    SolutionCell(int i, int j, int m, int t);

    //GETTERS
    int getI();

    int getJ();

    int getType();

    int getTime();

    //SETTERS
    int setI();

    int setJ();

    int setType();

    int setTime();

    void printCell();

private:
    int i, j;           // dst and src of the move
    int type;           // type of user asked to move
    int value;          // number of users with same characteristics asked to move
    int t;              // time period of the move
};

#endif /* SolCell_hpp */
