#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#define F "\U0001F6A9"
#define H "⬜"

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <iomanip>


using namespace std;

class Minesweeper
{
private:
    // state
    vector<vector<string>> A1;
    vector<vector<string>> A2;
    vector<vector<string>> A3;
    vector<vector<string>> A4;
    vector<vector<string>> A5;

    vector<vector<string>> hiddenMap;
    vector<vector<string>> publicMap;

    int rowSize;
    int columnSize;
    int mineCount;
    int countOfHiden;

    // function
    // PhaseOne
    void getRandomCoordinates(int &x, int &y) const;
    void mapMaker();
    vector<vector<string>> mapMaker(int rowSize, int columnSize, int MineCount);
    int countOfMinesOnboard(const vector<vector<string>> &A, int x, int y) const;

    // PhaseTwo
    void firstOpen(int x, int y);
    void mapChouseing(int x, int y);
    void open(int x, int y);
    void Boom();
    void flag(int x, int y);
    void doubleOpen(int x, int y);
    void del();
    int countOfFlagsOnboard(int x, int y);
    void printMap();
    void printMapH();
public:
    Minesweeper();
    ~Minesweeper() {}
    void play();
};

#endif