#include "cube.h"
#include<algorithm>
using namespace std;


const int RAND = 10;


class Solver{
private:
    int _population, _maxGeneration, _maxResets, _elitism;

    vector<string> singleMoves = {
        "U", "U'", "U2", "D", "D'", "D2", "R", "R'", "R2", "L",
        "L'", "L2", "F", "F'", "F2", "B", "B'", "B2",
    };
    
    vector<string> permutation = {
        "F' L' B' R' U' R U' B L F R U R' U",
        "F R B L U L' U B' R' F' L' U' L U'",
        "U2 B U2 B' R2 F R' F' U2 F' U2 F R'",
        "U2 R U2 R' F2 L F' L' U2 L' U2 L F'",
        "U' B2 D2 L' F2 D2 B2 R' U'",
        "U B2 D2 R F2 D2 B2 L U",
        "D' R' D R2 U' R B2 L U' L' B2 U R2",
        "D L D' L2 U L' B2 R' U R B2 U' L2",
        "R' U L' U2 R U' L R' U L' U2 R U' L U'",
        "L U' R U2 L' U R' L U' R U2 L' U R' U",
        "F' U B U' F U B' U'",
        "F U' B' U F' U' B U",
        "L' U2 L R' F2 R",
        "R' U2 R L' B2 L",
        "M2 U M2 U2 M2 U M2",
    };
    
    vector<string> fullRotations = {"x", "x'", "x2",  "y", "y'", "y2"};

    vector<string> orientations = {"z", "z'", "z2"};

    static void outputSolve(int reset, int generation,  string scramble, string algorithm) {
        cout << algorithm << '\n';
    }

public:
    void init(int population,int maxGeneration,int maxResets, int elitism) {
        _population = population;
        _maxGeneration = maxGeneration;
        _maxResets = maxResets;
        _elitism = elitism;
    }

    
    string solve(Cube &cube) {
        for (int res = 0; res < _maxResets; ++res) {
            vector<Cube> cubes;

            for (int i = 0; i < _population; ++i) {
                cube.execute(singleMoves[rand() % (singleMoves.size() - 1)]);
                cube.execute(singleMoves[rand() % (singleMoves.size() - 1)]);
                cubes.push_back(cube);
            }

            for (int gen = 0; gen < _maxGeneration; ++gen) {
                
                sort(cubes.begin(), cubes.end());

                for (int i = 0; i < cubes.size(); ++i) {
                    if (cubes[i].fitness == 0) {
                        outputSolve(res, gen, cubes[i].getScramble(), cubes[i].getHistory());
                        copy(cube, cubes[i]);
                        return cubes[i].getHistory();
                    }

                    if (i > _elitism){
                        copy(cubes[i], cubes[rand()% _elitism]);
                        randomExecute(cubes[i]);
                    }
                }
            }
        }

        return "";
    }

    void randomExecute(Cube &cube){
        int evo = rand() % 6;

        switch (evo) {
            case 0:
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
            case 1:
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
            case 2:
                cube.execute(fullRotations[rand() % (fullRotations.size() - 1)]);
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
            case 3:
                cube.execute(orientations[rand() % (orientations.size() - 1)]);
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
            case 4:
                cube.execute(fullRotations[rand() % (fullRotations.size() - 1)]);;
                cube.execute(orientations[rand() % (orientations.size() - 1)]);
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
            case 5:
                cube.execute(orientations[rand() % (orientations.size() - 1)]);
                cube.execute(fullRotations[rand() % (fullRotations.size() - 1)]);;
                cube.execute(permutation[rand() % (permutation.size() - 1)]);
                break;
        }
    }

    static void copy(Cube &to, Cube &from){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                to._front[i][j] = from._front[i][j];
                to._bottom[i][j] = from._bottom[i][j];
                to._back[i][j] = from._back[i][j];
                to._top[i][j] = from._top[i][j];
                to._right[i][j] = from._right[i][j];
                to._left[i][j] = from._left[i][j];
            }
        }

        to.history.clear();
        to.history.resize(from.history.size());

        for (int i = 0; i < from.history.size(); ++i) {
            to.history[i] = from.history[i];
        }
        to.fitness = from.fitness;
    }

};
