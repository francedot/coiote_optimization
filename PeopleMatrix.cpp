//
// Created by Gabriele Mosca on 30/11/16.
//

#include "PeopleMatrix.hpp"

/*
 * constructor: allocate memory and initialize values for peopleMatrix
 */

PeopleMatrix::PeopleMatrix(const PeopleMatrix &toCopy) {
    timePeriods = toCopy.timePeriods;
    peopleTypes = toCopy.peopleTypes;
    cellsNumber = toCopy.cellsNumber;
    peopleMatrix = new int **[timePeriods]();
    for (int t = 0; t < timePeriods; t++) {
        peopleMatrix[t] = new int *[peopleTypes]();
        for (int m = 0; m < peopleTypes; m++) {
            peopleMatrix[t][m] = new int[cellsNumber]();
            for (int i = 0; i < cellsNumber; i++) {
                peopleMatrix[t][m][i] = toCopy.peopleMatrix[t][m][i];
            }
        }
    }
}

PeopleMatrix::PeopleMatrix(int timePeriods, int peopleTypes, int cellsNumber) {

    this->cellsNumber = cellsNumber;
    this->peopleTypes = peopleTypes;
    this->timePeriods = timePeriods;

    peopleMatrix = new int **[this->timePeriods]();
    for (int t = 0; t < timePeriods; t++) {
        peopleMatrix[t] = new int *[this->peopleTypes]();
        for (int m = 0; m < peopleTypes; m++) {
            peopleMatrix[t][m] = new int[this->cellsNumber]();
            for (int i = 0; i < cellsNumber; i++) {
                peopleMatrix[t][m][i] = 0;
            }
        }
    }
}

/*
 * load people matrix from inputFileStream
 */
int PeopleMatrix::load(ifstream *inputFileStream) {
    string line;    // contains a line of the Input file
    string word;    // contains a single word (into a line)
    int m;          // index for peopleTypes
    int t;          // index for timePeriods
    int i;          // index for cellsNumber

    // jump empty line
    getline(*inputFileStream, line);

    for (m = 0; m < peopleTypes; m++) {
        for (t = 0; t < timePeriods; t++) {
            // jump line with m and t indexes
            getline(*inputFileStream, line);

            getline(*inputFileStream, line);
            istringstream inputStringStream(line);
            for (i = 0; i < cellsNumber; i++) {
                inputStringStream >> word;
                peopleMatrix[t][m][i] = atoi(word.c_str());
            }
        }
    }


    return 1;
}

/*
 * It returns the internal representation of the people matrix. Should be used with caution.
 */
int ***PeopleMatrix::getPeopleMatrix() {
    return peopleMatrix;
}

int PeopleMatrix::getCellsNumber() {
    return cellsNumber;
}

int PeopleMatrix::getPeopleTypes() {
    return peopleTypes;
}

int PeopleMatrix::getTimePeriods() {
    return timePeriods;
}

void PeopleMatrix::decrementPeople(int t, int m, int i, int decrement) {
    peopleMatrix[t][m][i] -= decrement;
    if (peopleMatrix[t][m][i] < 0) peopleMatrix[t][m][i] = 0;
}

/*
 * It sets the value of the people matrix corrisponding to time period "t", person type "m" and cell "i".
 */
void PeopleMatrix::setValue(int t, int m, int i, int value) {
    peopleMatrix[t][m][i] = value;
}

/*
 * It returns the value of the people matrix corrisponding to time period "t", person type "m" and cell "i".
 */
int PeopleMatrix::getPeople(int t, int m, int i) {
    return peopleMatrix[t][m][i];
}

/*
 * screen print of the people matrix
 */

void PeopleMatrix::printPeople() {
    for (int m = 0; m < peopleTypes; m++) {
        for (int t = 0; t < timePeriods; t++) {
            cout << m << " " << t << endl;
            for (int i = 0; i < cellsNumber; i++) {
                cout << peopleMatrix[t][m][i] << " ";
            }
            cout << endl;
        }
    }
}