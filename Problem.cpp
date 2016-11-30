/*
 * Problem.cpp
 */

#include "Problem.hpp"
#include <fstream>
#include <sstream>

using namespace std;

/*
 * get inputPath and outputPath from command line
 */
Problem::Problem(string inputPath, string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

/*
 * load Input file
 */
void Problem::load() {
    string line; // contains a line of the Input file
    string word; // contains a single word (into a line)

    // open Input file
    ifstream inputFileStream(Problem::inputPath.c_str());

    if (!inputFileStream.is_open()) {
        // todo lancia eccezione
        throw new Exception("Error: unable to open " + Problem::inputPath);
    }

    /*
     * read first line: cellsNumber periodsNumber peopleTypes
     */
    getline(inputFileStream, line);
    istringstream inputStringStream(line);

    inputStringStream >> word;

    return;
}

/*
 * todo comments
 */
void Problem::writeSolution(bool printScreen) {

}

/*
 * generate initial solution and solve the problem running innerSolve
 */
int Problem::solve(Solution *finalSolution) {
    return 0;
}

/*
 * uses the heuristic
 */
int Problem::innerSolve(Solution *initialSolution, Solution *finalSolution) {
    return 0;
}

/*
 * todo comments
 */
Solution *Problem::generateInitialSolution() {
    return nullptr;
}


