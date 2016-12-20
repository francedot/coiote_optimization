//
// Created by badal on 06/12/2016.
//

#include <stdlib.h>
#include "Dummy.hpp"

// NEW LINE ADDED TO CHECK BRANCH FUNCTIONALITY
// NEW LINE ADDED

/*
 * This static method fills the cost matrix with random numbers proportional to the distance between the cells
 * and the person types and updates the average cost per task for each cell.
 */
void Dummy::fillCostMatrix(CostMatrix *costMatrix, int cellsNumber, int timeSlots, int peopleTypes) {
    int RANGE_MODIFIER = 2;
    int cost, diff, index = 0;
    for (int i = 0; i < cellsNumber; i++) {
        for (int j = 0; j < cellsNumber; j++) {
            for (int t = 0; t < timeSlots; t++) {
                for (int m = 0; m < peopleTypes; m++) {
                    // Calculates diff to implement a locality in the random choice of costs
                    diff = (i < j) ? (j - i) : (i - j);
                    diff += 5;
                    cost = 1 + (int) ((((double) rand()) / RAND_MAX) * RANGE_MODIFIER * diff * (m + 1));
                    costMatrix->setValue(j, i, m, t, cost);
                    costMatrix->updateAvgCostsPerTask(j, (cost / (m + 1)), index++);
                }
            }
        }
    }
}

/*
 * This static method fills the "peopleMatrix" with random integers between "minPersons" and "maxPersons".
 * When using this method assure that "minPersons" is set such that the total number of people is sufficient
 * to satisfy all the tasks in each cell.
 */
void
Dummy::fillPeopleMatrix(PeopleMatrix *peopleMatrix, int cellsNumber, int timeSlots, int peopleTypes, int minPersons,
                        int maxPersons) {
    int persons;
    int MAX_RANGE = maxPersons - minPersons;
    for (int i = 0; i < cellsNumber; i++) {
        for (int t = 0; t < timeSlots; t++) {
            for (int m = 0; m < peopleTypes; m++) {
                persons = rand() % MAX_RANGE;
                persons += minPersons;
                peopleMatrix->setValue(t, m, i, persons);
            }
        }
    }

}

/*
 * This static method allocates the task array and returns it.
 * When deallocating, remember to use the "delete[]" operator.
 */
int *Dummy::allocateAndFillTasksArray(int size, int maxTasks) {
    int *tasks = new int[size]();
    for (int i = 0; i < size; i++)
        tasks[i] = rand() % maxTasks + 10;
    return tasks;
}

/*
 * This static method returns the maximum number of tasks in a single cell. It is required to compute
 * the minimum number of people.
 */
int Dummy::getMaxTasks(int *tasks, int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        max = (max < tasks[i]) ? tasks[i] : max;
    }
    return max;
}

