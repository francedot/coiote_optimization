/*
 * Solution.cpp
 */

#include "Solution.hpp"

using namespace std;

/*
 * todo da eliminare ?
 */
Solution::Solution(PeopleMatrix *peopleMatrix) {
    solutionPeople = new PeopleMatrix(*peopleMatrix);
}

Solution::Solution(const Solution &toCopy) {
    totalCost = toCopy.totalCost;
//    for (int i = 0; i < toCopy.cells.size(); i++) {
//        cells.push_back(toCopy.cells[i]);
//    }
    cells = toCopy.cells; // Should be faster and uses copy constructors
}

/*
 * This function is used when generating the neighboor. It returns the best k solutionCells
 * of the Solution, which enables us to keep the best k solutionCells instead of the first
 * k solutionCells.
 *
 * TODO: it can be improved in timing by changing Solution implementation and keeping
 * TODO:      SolutionCells in Solution sorted by cost and not by <i,j> pair.
*/
vector<SolutionCell> *getBestKSolutions(Solution *currentSolution, double percentage, CostMatrix *costs) {
    double cur_max = 100000;
    int k = (int) ((percentage * (double) currentSolution->getSize()) / 100);
    vector<SolutionCell> *bestSolutions = new vector<SolutionCell>[k];
    for (int i = 0; i < currentSolution->getSize(); i++) {
        if (currentSolution->getCell(i)->getCostOfSolutionCell(costs) < cur_max) {
            vector<SolutionCell>::iterator it = bestSolutions->begin();
            while ((it != bestSolutions->end()) && (currentSolution->getCell(i)->getCostOfSolutionCell(costs) >
                                                    it->getCostOfSolutionCell(costs)))
                it++;
            bestSolutions->insert(it, *currentSolution->getCell(i));
            if (bestSolutions->size() > k)
                bestSolutions->pop_back();
            it = bestSolutions->end();
            it--;
            cur_max = it->getCostOfSolutionCell(costs);
        }
    }
    return bestSolutions;
}

/*
 * initialSolution = eventuale soluzione iniziale di cui generare il vicinato. (null = genera nuova soluzione)
 * n = numero di celle da lasciare invariate nella generazione del vicinato
 * N = numero di celle in totale [parametro del problema]
 * null implica n = 0
 * populateSolution popola se stessa partendo da una initial solution di cui ne tiene n
 */
void Solution::populateSolution(Solution *initialSolution, double keptSolCellsPercentage, int *tasks, int sizeOfTasks,
                                CostMatrix *costs, int N) {
    // People is a matrix Time x TypePerson x CellNumber
    // TODO: Add exception / full control of passed parameters
    int *remainingTask = new int[sizeOfTasks];
    // TODO: [available/pickable]People never used/initialized
    this->totalCost = 0;
    for (int i = 0; i < sizeOfTasks; i++)
        remainingTask[i] = tasks[i];

    //solutionPeople->printPeople();
    //printTasks(remainingTask, N);
    //se c'è una soluzione di partenza parte di essa viene riutilizzata
    if (initialSolution != nullptr) {
        //soluzione banale e provvioria che prende le prime celle della soluzione iniziale
        /*for (int kept = 0; kept < (initialSolution->getSize() / keptSolCellsRatio); kept++) {
            SolutionCell *toAdd = new SolutionCell(initialSolution->cells[kept]);
            totalCost += (costs->getCost(toAdd->getJ(), toAdd->getI(), toAdd->getType(), toAdd->getTime()) *
                          toAdd->getX());
            remainingTask[toAdd->getJ()] -= ((toAdd->getType() + 1) * toAdd->getX());
            if (remainingTask[toAdd->getJ()] < 0) remainingTask[toAdd->getJ()] = 0;
            solutionPeople->decrementPeople(toAdd->getTime(), toAdd->getType(), toAdd->getI(), 1);
            addSolutionCell(toAdd);
        }*/
        vector<SolutionCell> *bestSolutions = getBestKSolutions(initialSolution, keptSolCellsPercentage, costs);
        vector<SolutionCell>::iterator it;
        for (it = bestSolutions->begin(); it != bestSolutions->end(); it++) {
            SolutionCell *toAdd = new SolutionCell(*it);
            totalCost += (costs->getCost(toAdd->getJ(), toAdd->getI(), toAdd->getType(), toAdd->getTime()) *
                          toAdd->getX());
            remainingTask[toAdd->getJ()] -= ((toAdd->getType() + 1) * toAdd->getX());
            if (remainingTask[toAdd->getJ()] < 0) remainingTask[toAdd->getJ()] = 0;
            solutionPeople->decrementPeople(toAdd->getTime(), toAdd->getType(), toAdd->getI(), 1);
            addSolutionCell(toAdd);
        }
        /*
        double keptCellProbability = ((double) keptSolCells / (double) initialSolution->cells.size());
        int kept = 0;
        while (kept < keptSolCells) {
            for (vector<SolutionCell>::iterator it = initialSolution->cells.begin();
                 it != initialSolution->cells.end() && kept < keptSolCells; it++) {
                double r = ((double) rand()) / RAND_MAX;
                if (r >= keptCellProbability) {
                    // TODO: Valuta se usare addSolutionCell [ Meno efficiente. Probabilmente è già ordinata ]
                    SolutionCell cellToAdd(*it);
                    this->cells.insert(this->cells.begin(), cellToAdd);
                    remainingTask[cellToAdd.getJ()] -= cellToAdd.getX() * (cellToAdd.getType() + 1);
//                    people[cellToAdd.getTime()][cellToAdd.getType()][cellToAdd.getI()] -= cellToAdd.getX();
//                    totalCost += costs->getCost(cellToAdd.getI(), cellToAdd.getJ(), cellToAdd.getType(), cellToAdd.getTime());
//                    addSolutionCell(new SolutionCell(*it));
                    remainingTask[it->getJ()] -= (it->getX() * (it->getType() + 1));
                    if (remainingTask[it->getJ()] < 0)
                        remainingTask[it->getJ()] = 0;
//                    printTasks(remainingTask, N);
                    people->setValue(it->getTime(), it->getType(), it->getI(), (people->getPeople(it->getTime(), it->getType(), it->getI()) - it->getX()));
                    totalCost += costs->getCost(it->getI(), it->getJ(), it->getType(), it->getTime()) * it->getX();
                    kept++;
                }
            }
        }
         */

    }

    //solutionPeople->printPeople();
    //printTasks(remainingTask, N);
    int x;
    for (int j = 0; j < N; j++) {
        while (remainingTask[j] > 0) {
            CostMatrix::CostCoordinates *c = costs->getMinimumCost(j, solutionPeople, remainingTask, N,
                                                                   solutionPeople->getPeopleTypes(),
                                                                   solutionPeople->getTimePeriods());
            x = 0;

            //solutionPeople->printPeople();
            //printTasks(remainingTask, N);

            while (remainingTask[j] > 0 && solutionPeople->getPeople(c->t, c->m, c->i) > 0) {
                remainingTask[j] -= (c->m + 1);
                solutionPeople->decrementPeople(c->t, c->m, c->i, 1);
                x++;
            }
            if (remainingTask[j] < 0) remainingTask[j] = 0;
            if (x > 0) {
                totalCost += (costs->getCost(c->j, c->i, c->m, c->t) * x);
                addSolutionCell(new SolutionCell(c->i, c->j, c->m, c->t, x));
            }
            //printTasks(remainingTask, N);
        }
    }


    /*
    //   printTasks(remainingTask, N);
    vector<CostMatrix::CostCoordinates> *minsVector;
    vector<CostMatrix::CostCoordinates>::iterator it;
    for (int j = 0; j < N; j++) {
        int x = 0;
        if (remainingTask[j] <= 0) continue;
        minsVector = costs->getMinimumTaskCost(j, remainingTask[j], people);
        it = minsVector->begin();
        if (it == minsVector->end()) exit(8);
        while (it != minsVector->end() && remainingTask[j] > 0) {
            x = 0;
            //SI PIANTA ALLA RIGA QUI SOTTO
            while (people->getPeople(it->t, it->m, it->i) > 0 && remainingTask[j] > 0) {
                remainingTask[j] -= (it->m + 1);
                people->setValue(it->t, it->m, it->i, (people->getPeople(it->t, it->m, it->i) - 1));
                x++;
            }
            if (remainingTask[j] < 0) remainingTask[j] = 0;

            totalCost += (costs->getCost(j, it->i, it->m, it->t) * x);

            addSolutionCell(new SolutionCell(it->i, it->j, it->m, it->t, x));
            it++;
        }
        free(minsVector);
        //printTasks(remainingTask, N);
    }
     */
    //cout << "solution generated, cost: " << totalCost << endl;
}

/*
 * todo comments
 */
void Solution::generateInitialSolution(int *remainingTask, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    populateSolution(nullptr, 0, remainingTask, sizeOfTasks, costs, N);
}


void Solution::addSolutionCell(SolutionCell *toAdd) {
    // Adds a solution cell using an insertion sort
    if (toAdd == NULL) {
        exit(101);
        // TODO: Throw exception
    }
    vector<SolutionCell>::iterator it;
    for (it = cells.begin(); (it != cells.end()) && (toAdd->getI() > it->getI()); it++);
    if (it == cells.end()) {
        cells.push_back(*toAdd);
        return;
    }
    for (; (toAdd->getI() == it->getI()) && (toAdd->getJ() > it->getJ()) && (it != cells.end()); it++);
    cells.insert(it, *toAdd);
    return;
}

vector<Solution *> *Solution::generateNeighborhood(int size, int keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    vector<Solution *> *neighborhood = new vector<Solution *>((unsigned long) size);
    for (int i = 0; i < size; i++) {
        neighborhood->push_back(generateNeighbor(keptSolCells, tasks, sizeOfTasks, people, costs, N));
    }
    return neighborhood; //Use delete[] to delete this array;
}

Solution *
Solution::generateNeighbor(double keptSolCellsPercentage, int *tasks, int sizeOfTasks, PeopleMatrix *people,
                           CostMatrix *costs,
                           int N) {
    Solution *newSol = new Solution(people);
    newSol->populateSolution(this, keptSolCellsPercentage, tasks, sizeOfTasks, costs, N);
    return newSol;
}

int Solution::evaluate() {
    return totalCost;
}

PeopleMatrix *Solution::getSolutionPeople() {
    return solutionPeople;
}

void Solution::setSolutionPeople(PeopleMatrix peopleToSet) {
    solutionPeople = new PeopleMatrix(peopleToSet);
}

void Solution::print(bool screen, string path) {
    if (screen)
        for (int i = 0; i < cells.size(); i++)
            cells[i].print(1, path);
    //todo print on output file
}

void Solution::printTasks(int *remainingTask, int N) {
    if (remainingTask != nullptr) {
        std::cout << "Tasks: ";
        for (int h = 0; h < N; h++) {
            std::cout << remainingTask[h] << " ";
        }
    }
    std::cout << std::endl;
}

int Solution::getSize() {
    return cells.size();
}

SolutionCell *Solution::getCell(int i) {
    if (i >= cells.size()) return nullptr;
    return &cells[i];
}