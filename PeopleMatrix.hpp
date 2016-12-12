//
// Created by Gabriele Mosca on 30/11/16.
//

#ifndef COIOTE_PROJECT_PEOPLEMATRIX_HPP
#define COIOTE_PROJECT_PEOPLEMATRIX_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class PeopleMatrix {
public:
    PeopleMatrix(const PeopleMatrix &toCopy);
    PeopleMatrix(int timePeriods, int peopleTypes, int cellsNumber);
    int load(ifstream *inputFileStream);

    int ***getPeopleMatrix();

    void setValue(int t, int m, int i, int value);

    void decrementPeople(int t, int m, int i, int decrement);

    int getPeople(int t, int m, int i);

    int getCellsNumber();

    int getPeopleTypes();

    int getTimePeriods();

    void printPeople();

private:
    int ***peopleMatrix;        // Indexes, for now, are t (time), m (personType), i (cell), in this order.
    int timePeriods, peopleTypes, cellsNumber;
};


#endif //COIOTE_PROJECT_PEOPLEMATRIX_HPP
