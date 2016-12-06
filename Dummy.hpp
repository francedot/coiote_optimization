//
// Created by badal on 06/12/2016.
//

#ifndef COIOTE_PROJECT_DUMMY_HPP
#define COIOTE_PROJECT_DUMMY_HPP

#include "CostMatrix.hpp"
#include "PeopleMatrix.hpp"

class Dummy {
public:
    static void fillCostMatrix(CostMatrix *costMatrix, int cellsNumber, int timeSlots, int personTypes);

    static void
    fillPeopleMatrix(PeopleMatrix *peopleMatrix, int cellsNumber, int timeSlots, int personTypes, int minPersons,
                     int maxPersons);

    static int *allocateAndFillTasksArray(int size, int maxTasks);

    static int getMaxTasks(int *tasks, int size);
};


#endif //COIOTE_PROJECT_DUMMY_HPP
