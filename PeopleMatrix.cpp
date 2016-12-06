//
// Created by Gabriele Mosca on 30/11/16.
//

#include "PeopleMatrix.hpp"

/*
 * It returns the internal representation of the people matrix. Should be used with caution.
 */
int ***PeopleMatrix::getPeopleMatrix() {
    return peopleMatrix;
}

/*
 * It sets the value of the people matrix corrisponding to time period "t", person type "m" and cell "i".
 */
void PeopleMatrix::setValue(int t, int m, int i, int value) {
    peopleMatrix[t][m][i] = value;
}
