#include "solver.h"
#include <fstream>

int main() {
    Solver solver;
    solver.init(500, 300, 10, 50);
    std::string scrambler;

    /* from file */
    // string inPath, outPath;
    // std::cout << "Input file:\n";
    // std::cin >> inPath;
    // std::cout << "Output file:\n";
    // std::cin >> outPath;


    // std::ifstream inputFile(inPath);
    // std::ofstream outputFile(outPath);

    // while (std::getline(inputFile, scrambler)){}

    // Cube cube;
    // cube.generateCube();
    // cube.execute(scrambler);
    // outputFile << solver.solve(cube);
    // inputFile.close();
    // outputFile.close();



    /* random generated cube */
    Cube cube;
    cube.generateCube();
    for (int i = 0; i < RAND; ++i) {
        solver.randomExecute(cube);
    }

    cube.outputCube();
    solver.solve(cube);




    return 0;
}





// scrambler = "B F' L' R U L2 D' B F' D' R D R D2 U2 F2 D' U R' D F2 U' R B R2 U F2 L2 D2 L'";
// scrambler = "L' F2 D U2 B L2 B' L' B2 F' D U2 F' D2 U' R2 B F R' F' L' B D2 F' D' U' R U' L2 R";
// scrambler = "F2 U' B' R' B R2 B2 R2 U' R' U B U F2 R2 D U2 B D U2 R' F' L' U B2 U F' U2 R F";