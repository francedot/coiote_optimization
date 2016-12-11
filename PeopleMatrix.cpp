//
// Created by Gabriele Mosca on 30/11/16.
//

#include "PeopleMatrix.hpp"

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

/*
 * It sets the value of the people matrix corrisponding to time period "t", person type "m" and cell "i".
 */
void PeopleMatrix::setValue(int t, int m, int i, int value) {
    peopleMatrix[t][m][i] = value;
}

int PeopleMatrix::getPeople(int t, int m, int i) {
    return peopleMatrix[t][m][i];
}

void PeopleMatrix::printPeople() {
    cout << timePeriods << " " << peopleTypes << " " << cellsNumber << endl;
    for (int time = 0; time < timePeriods; time++) {
        for (int type = 0; type < peopleTypes; type++) {
            cout << time << " " << type << endl;
            for (int cell = 0; cell < cellsNumber; cell++)
                cout << peopleMatrix[time][type][cell] << " ";
            cout << endl;
        }
    }
}
