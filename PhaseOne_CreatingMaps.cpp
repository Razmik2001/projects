#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    // Initialize variables with default values or get input
    rowSize = 0;
    columnSize = 0;
    mineCount = 0;
    mapMaker();
}

void Minesweeper::mapMaker()
{
    while (rowSize <= 0)
    {
        cout << "Please set row size (it must be a positive number): ";
        cin >> rowSize;
    }
    while (columnSize <= 0)
    {
        cout << "Please set column size (it must be a positive number): ";
        cin >> columnSize;
    }
    while (mineCount <= 0 || mineCount > (rowSize * columnSize * 0.6))
    {
        cout << "Please set mines count (it must be a number between 0 and " << rowSize * columnSize * 0.6 << "): ";
        cin >> mineCount;
    }
    countOfHiden = rowSize * columnSize;
    thread t1(&Minesweeper::treadFunction, this, ref(A1));
    thread t2(&Minesweeper::treadFunction, this, ref(A2));
    thread t3(&Minesweeper::treadFunction, this, ref(A3));
    thread t4(&Minesweeper::treadFunction, this, ref(A4));
    thread t5(&Minesweeper::treadFunction, this, ref(A5));
    publicMap = vector<vector<string>>(rowSize, vector<string>(columnSize, "⬜"));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

vector<vector<string>> Minesweeper::mapMaker(int rowSize, int columnSize, int MineCount)
{
    vector<vector<string>> A(rowSize, vector<string>(columnSize, "-"));
    int x, y;
    int n = MineCount;

    while (n != 0)
    {
        getRandomCoordinates(x, y);
        if (A[x][y] != "M")
        {
            A[x][y] = "M";
            n--;
        }
    }

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < columnSize; j++)
        {
            if (A[i][j] == "M")
                continue;
            else
            {
                int count = countOfMinesOnboard(A, i, j);
                if (count != 0)
                    A[i][j] = to_string(count);
            }
        }
    }
    return A;
}

int Minesweeper::countOfMinesOnboard(const vector<vector<string>> &A, int x, int y) const
{
    int count = 0;

    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        if (newX >= 0 && newX < rowSize && newY >= 0 && newY < columnSize)
        {
            if (A[newX][newY] == "M")
            {
                ++count;
            }
        }
    }

    return count;
}

void Minesweeper::treadFunction(vector<vector<string>> &A)
{
    A = mapMaker(rowSize, columnSize, mineCount);
}

void Minesweeper::getRandomCoordinates(int &x, int &y) const
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distX(0, rowSize - 1);
    uniform_int_distribution<> distY(0, columnSize - 1);

    x = distX(gen);
    y = distY(gen);
}

#include <iostream>

void Minesweeper::printMap()
{
    const int width = 1;
    for (const auto &row : publicMap)
    {
        for (const auto &cell : row)
        {
            std::cout << std::setw(width) << cell;
        }
        std::cout << "\n";
    }
}
