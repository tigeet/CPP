#include <iostream>
#include <vector>
#include <string>

enum direction {counter, clock};


class Cube {
private:
    static void rot90(std::vector<std::vector<char>> &face, bool clockwise) {
        if (clockwise) {
            char t;
            t = face[0][0];
            face[0][0] = face[2][0];
            face[2][0] = face[2][2];
            face[2][2] = face[0][2];
            face[0][2] = t;

            t = face[0][1];
            face[0][1] = face[1][0];
            face[1][0] = face[2][1];
            face[2][1] = face[1][2];
            face[1][2] = t;
        } else {
            char t;
            t = face[0][0];
            face[0][0] = face[0][2];
            face[0][2] = face[2][2];
            face[2][2] = face[2][0];
            face[2][0] = t;

            t = face[0][1];
            face[0][1] = face[1][2];
            face[1][2] = face[2][1];
            face[2][1] = face[1][0];
            face[1][0] = t;
        }
    }

    static void copyStickers(std::vector<char> &dest, std::vector<char> &origin) {
        dest[0] = origin[0];
        dest[1] = origin[1];
        dest[2] = origin[2];
    }

    static void copyVertStickers(
        std::vector<std::vector<char>> &dest,
        int destIdx, 
        std::vector<std::vector<char>> &origin,
        int originIdx
    ) {
        for (int i = 0; i < 3; ++i)
            dest[i][destIdx] = origin[i][originIdx];
    }

    static void copyVertReverseStickers(
        std::vector<std::vector<char>> &dest, 
        int destIdx, 
        std::vector<std::vector<char>> &origin,
        int originIdx
    ) {
        int j = 3;
        for (int i = 0; i < 3; ++i)
            dest[i][destIdx] = origin[--j][originIdx];

    }

    static void copyVertToHorStickers(std::vector<std::vector<char>> &dest, int destIdx, std::vector<char> &origin) {
        for (int i = 0; i < 3; ++i)
            dest[i][destIdx] = origin[i];

    }

    static void copyVertToHorReverseStickers(std::vector<std::vector<char>> &dest, int destIdx, std::vector<char> &origin) {
        int j = 3;
        for (int i = 0; i < 3; ++i)
            dest[i][destIdx] = origin[--j];

    }

    static void copyHorToVertStickers(std::vector<char> &dest, std::vector<std::vector<char>> &origin, int originIdx) {
        for (int i = 0; i < 3; ++i)
            dest[i] = origin[i][originIdx];

    }

    static void copyHorToVertReverseStickers(std::vector<char> &dest, std::vector<std::vector<char>> &origin, int originIdx) {
        int j = 3;
        for (int i = 0; i < 3; ++i)
            dest[i] = origin[--j][originIdx];

    }


    static void rotateZ(std::vector<char> &t1, std::vector<char> &t2, std::vector<char> &t3, std::vector<char> &t4) {
        std::vector<char> backup = {' ', ' ', ' '};
        copyStickers(backup, t4);
        copyStickers(t4, t3);
        copyStickers(t3, t2);
        copyStickers(t2, t1);
        copyStickers(t1, backup);
    }

    static void rotateX(
        std::vector<std::vector<char>> &t1, int idx1, bool flipT1,
        std::vector<std::vector<char>> &t2, int idx2, bool flipT2,
        std::vector<std::vector<char>> &t3, int idx3, bool flipT3,
        std::vector<std::vector<char>> &t4, int idx4, bool flipT4
    ) {

        std::vector<std::vector<char>> backup(3, std::vector<char>(3, ' '));

        if (flipT4) {
            copyVertReverseStickers(backup, idx1, t4, idx4);
        } else
            copyVertStickers(backup, idx4, t4, idx4);


        if (flipT3) {
            copyVertReverseStickers(t4, idx4, t3, idx3);
        } else
            copyVertStickers(t4, idx3, t3, idx3);

        if (flipT2) {
            copyVertReverseStickers(t3, idx3, t2, idx2);
        } else
            copyVertStickers(t3, idx2, t2, idx2);

        if (flipT1) {
            copyVertReverseStickers(t2, idx2, t1, idx1);
        } else
            copyVertStickers(t2, idx1, t1, idx1);

        copyVertStickers(t1, idx1, backup, idx1);
    }

    static void rotateY(
        std::vector<std::vector<char>> &t1, int idx1, bool flipT1,
        std::vector<std::vector<char>> &t2, int idx2, bool flipT2,
        std::vector<std::vector<char>> &t3, int idx3, bool flipT3,
        std::vector<std::vector<char>> &t4, int idx4, bool flipT4
    ) {

        std::vector<std::vector<char>> backup(3, std::vector<char>(3, ' '));

        if (flipT4) {
            copyVertReverseStickers(backup, idx4, t4, idx4);
        } else
            copyVertStickers(backup, idx4, t4, idx4);

        if (flipT3) {
            copyVertToHorReverseStickers(t4, idx4, t3[idx4]);
        } else
            copyVertToHorStickers(t4, idx4, t3[idx3]);

        if (flipT2) {
            copyHorToVertReverseStickers(t3[idx3], t2, idx3);
        } else
            copyHorToVertStickers(t3[idx3], t2, idx2);
            
        if (flipT1) {
            copyVertToHorReverseStickers(t2, idx1, t1[idx1]);
        } else
            copyVertToHorStickers(t2, idx3, t1[idx1]);

        copyHorToVertStickers(t1[idx1], backup, idx4);
    }

    static int cntMisplacedInCenter(std::vector<std::vector<char>> &face) {
        int res = 0;
        char center = face[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (face[i][j] != center)
                    ++res;

        return res;
    }

    void getFitness() {
        int misplaced = cntMisplacedInCenter(_front);
        misplaced += cntMisplacedInCenter(_top);
        misplaced += cntMisplacedInCenter(_back);
        misplaced += cntMisplacedInCenter(_left);
        misplaced += cntMisplacedInCenter(_right);
        misplaced += cntMisplacedInCenter(_bottom);

        fitness = misplaced;
    }

public:
    int fitness = 0;
    std::vector<std::string> history;

    std::vector<std::vector<char>> _front;
    std::vector<std::vector<char>> _left;
    std::vector<std::vector<char>> _right;
    std::vector<std::vector<char>> _top;
    std::vector<std::vector<char>> _bottom;
    std::vector<std::vector<char>> _back;

    std::string getScramble() {
        return history[0];
    }

    std::string getHistory() {
        std::string s;
        for (int i = 1; i < history.size(); ++i) {
            s += " ";
            s += history[i];

        }
        return s;
    }

    void generateCube() {
        _front.assign(3, std::vector<char>(3, 'G'));
        _left.assign(3, std::vector<char>(3, 'O'));
        _right.assign(3, std::vector<char>(3, 'R'));
        _top.assign(3, std::vector<char>(3, 'W'));
        _bottom.assign(3, std::vector<char>(3, 'Y'));
        _back.assign(3, std::vector<char>(3, 'B'));
    }

    void outputCube() {
        for (int i = 0; i < 3; ++i) {
            std::cout << "   " << _top[i][0] << _top[i][1] << _top[i][2];
            std::cout << '\n';
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                std::cout << _left[i][j];
            for (int j = 0; j < 3; ++j)
                std::cout << _front[i][j];
            for (int j = 0; j < 3; ++j)
                std::cout << _right[i][j];
            for (int j = 0; j < 3; ++j)
                std::cout << _back[i][j];
            std::cout << '\n';
        }

        for (int i = 0; i < 3; ++i) {
            std::cout << "   " << _bottom[i][0] << _bottom[i][1] << _bottom[i][2];
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    bool isSolved() const {
        return (fitness == 0);
    }

    void D() {
        rot90(_bottom, 1);
        rotateZ(_front[2], _right[2], _back[2], _left[2]);
    }

    void DPrime() {
        rot90(_bottom, 0);
        rotateZ(_front[2], _left[2], _back[2], _right[2]);
    }

    void D2() {
        D();
        D();
    }

    void E() {
        rotateZ(_front[1], _right[1], _back[1], _left[1]);
    }

    void EPrime() {
        rotateZ(_front[1], _left[1], _back[1], _right[1]);
    }

    void E2() {
        E();
        E();
    }

    void U() {
        rot90(_top, 1);
        rotateZ(_front[0], _left[0], _back[0], _right[0]);
    }

    void UPrime() {
        rot90(_top, 0);
        rotateZ(_front[0], _right[0], _back[0], _left[0]);
    }

    void U2() {
        U();
        U();
    }


    void L() {
        rot90(_left, 1);
        rotateX(_bottom, 0, true, _back, 2, true, _top, 0, false, _front, 0, false);
    }

    void LPrime() {
        rot90(_left, 0);
        rotateX(_bottom, 0, false, _front, 0, false, _top, 0, true, _back, 2, true);
    }

    void L2() {
        L();
        L();
    }

    void M() {
        rotateX(_bottom, 1, true, _back, 1, true, _top, 1, false, _front, 1, false);
    }

    void MPrime() {
        rotateX(_bottom, 1, false, _front, 1, false, _top, 1, true, _back, 1, true);
    }

    void M2() {
        M();
        M();
    }

    void R() {
        rot90(_right, 1);
        rotateX(_bottom, 2, false, _front, 2, false, _top, 2, true, _back, 0, true);
    }

    void RPrime() {
        rot90(_right, 0);
        rotateX(_bottom, 2, true, _back, 0, true, _top, 2, false, _front, 2, false);
    }

    void R2() {
        R();
        R();
    }


    void B() {
        rot90(_back, 1);
        rotateY(_bottom, 2, true, _right, 2, false, _top, 0, true, _left, 0, false);
    }

    void BPrime() {
        rot90(_back, 0);
        rotateY(_bottom, 2, false, _left, 0, true, _top, 0, false, _right, 2, true);
    }

    void B2() {
        B();
        B();
    }

    void F() {
        rot90(_front, 1);
        rotateY(_bottom, 0, false, _left, 2, true, _top, 2, false, _right, 0, true);

    }

    void FPrime() {
        rot90(_front, 0);
        rotateY(_bottom, 0, true, _right, 0, false, _top, 2, true, _left, 2, false);
    }

    void F2() {
        F();
        F();
    }

    void S() {
        rotateY(_bottom, 1, false, _left, 1, true, _top, 1, false, _right, 1, true);
    }

    void SPrime() {
        rotateY(_bottom, 1, true, _right, 1, false, _top, 1, true, _left, 1, false);
    }

    void S2() {
        S();
        S();
    }


    void xFullRot() {
        LPrime();
        MPrime();
        R();
    }

    void xPrimeFullRot() {
        L();
        M();
        RPrime();
    }

    void x2FullRot() {
        xFullRot();
        xFullRot();
    }

    void yFullRot() {
        U();
        EPrime();
        DPrime();
    }

    void yPrimeFullRot() {
        UPrime();
        E();
        D();
    }

    void y2FullRot() {
        yFullRot();
        yFullRot();
    }

    void zFullRot() {
        F();
        S();
        BPrime();
    }

    void zPrimeFullRot() {
        FPrime();
        SPrime();
        B();
    }

    void z2FullRot() {
        zFullRot();
        zFullRot();
    }

    bool operator==(const Cube &cube) const {
        if (cube.fitness == fitness)
            return true;
        return false;
    }

    bool operator!=(const Cube &cube) const {
        if (cube.fitness != fitness)
            return true;
        return false;
    }

    bool operator<(const Cube &cube) const {
        if (cube.fitness > fitness)
            return true;
        return false;
    }

    bool operator>(const Cube &cube) const {
        if (cube.fitness < fitness)
            return true;
        return false;
    }

    bool operator>=(const Cube &cube) const {
        if (cube.fitness <= fitness)
            return true;
        return false;
    }

    bool operator<=(const Cube &cube) const {
        if (cube.fitness >= fitness)
            return true;
        return false;
    }

    void execute(std::string scrambler) {
        std::vector<std::string> moves;
        std::string temp = "";

        for (char i : scrambler) {

            if (i == ' ') {
                moves.push_back(temp);
                temp = "";
            } else
                temp.push_back(i);

        }
        moves.push_back(temp);

        for (auto move : moves) {
            if (move == "D") {
                D();
            } else if (move == "D'") {
                DPrime();
            } else if (move == "D2") {
                D2();
            } else if (move == "E") {
                E();
            } else if (move == "E'") {
                EPrime();
            } else if (move == "E2") {
                E2();
            } else if (move == "U") {
                U();
            } else if (move == "U'") {
                UPrime();
            } else if (move == "U2") {
                U2();
            } else if (move == "L") {
                L();
            } else if (move == "L'") {
                LPrime();
            } else if (move == "L2") {
                L2();
            } else if (move == "R") {
                R();
            } else if (move == "R'") {
                RPrime();
            } else if (move == "R2") {
                R2();
            } else if (move == "M") {
                M();
            } else if (move == "M'") {
                MPrime();
            } else if (move == "M2") {
                M2();
            } else if (move == "B") {
                B();
            } else if (move == "B'") {
                BPrime();
            } else if (move == "B2") {
                B2();
            } else if (move == "F") {
                F();
            } else if (move == "F'") {
                FPrime();
            } else if (move == "F2") {
                F2();
            } else if (move == "S") {
                S();
            } else if (move == "S'") {
                SPrime();
            } else if (move == "S2") {
                S2();
            } else if (move == "x") {
                xFullRot();
            } else if (move == "x'") {
                xPrimeFullRot();
            } else if (move == "x2") {
                x2FullRot();
            } else if (move == "y") {
                yFullRot();
            } else if (move == "y'") {
                yPrimeFullRot();
            } else if (move == "y2") {
                y2FullRot();
            } else if (move == "z") {
                zFullRot();
            } else if (move == "z'") {
                zPrimeFullRot();
            } else if (move == "z2") {
                z2FullRot();
            }
        }
        history.push_back(scrambler);
        getFitness();
    }
};
