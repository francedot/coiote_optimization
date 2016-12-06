//
// Created by Gabriele Mosca on 30/11/16.
//

#ifndef COIOTE_PROJECT_PEOPLEMATRIX_HPP
#define COIOTE_PROJECT_PEOPLEMATRIX_HPP


class PeopleMatrix {
public:
    int ***getPeopleMatrix();

    void setValue(int t, int m, int i, int value);
private:
    int ***peopleMatrix;        // Indexes, for now, are t (time), m (personType), i (cell), in this order.
};


#endif //COIOTE_PROJECT_PEOPLEMATRIX_HPP
