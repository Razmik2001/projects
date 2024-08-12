#include "Minesweeper.hpp"
void Minesweeper::del()
{
    A1.clear();
    A2.clear();
    A3.clear();
    A4.clear();
    A5.clear();
    hiddenMap.clear();
    publicMap.clear();
    rowSize = -1;
    columnSize = -1;
    mineCount = -1;
}

void Minesweeper::mapChouseing(int x, int y)
{
    vector<vector<string>> maps[] = {A1, A2, A3, A4, A5};
    char mapName = 'A';

    for (auto &map : maps)
    {
        if (map[x][y] != "M")
        {
            hiddenMap = std::move(map);
            map.clear();
            map = mapMaker(rowSize, columnSize, mineCount);
            break;
        }
        ++mapName;
    }
}

void Minesweeper::Boom()
{
    hiddenMap.clear();
    char c;
    cout << "\t\t\tGAME OVER\n\n\n";
    cout << "if you want a rematch/r, if a new map/n, if you want to end the game, press any other button:";
    cin >> c;
    switch (c)
    {
    case 'n':
        std::cout << "you start new game with new map:" << std::endl;
        del();
        mapMaker();
        play();
        break;
    case 'r':
        std::cout << "you start new game:" << std::endl;
        publicMap = vector<vector<string>>(rowSize, vector<string>(columnSize, "⬜"));
        play();
        break;
    default:
        std::cout << "thanks for a good game:" << std::endl;
        exit(0);
        break;
    }
}

void Minesweeper::firstOpen(int x, int y)
{
    mapChouseing(x, y);
    if (hiddenMap.empty())
    {
        cout << "you have no luck:";
        Boom();
    }
    for (auto &row : hiddenMap)
        for (auto &colum : row)
            colum += "c";
    open(x, y);
}

void Minesweeper::flag(int x, int y)
{
    if (publicMap[x][y] == F)
    {
        publicMap[x][y] = H;
        countOfHiden++;
        return;
    }
    if (hiddenMap[x][y][1] == 'c')
    {
        publicMap[x][y] = F;
        countOfHiden--;
    }
   
}

void Minesweeper::open(int x, int y)
{
    if (publicMap[x][y] != H)
        doubleOpen(x, y);
    else if (publicMap[x][y] == H && hiddenMap[x][y][0] == 'M')
        Boom();
    else
    {
        if (hiddenMap[x][y][0] != '-')
            publicMap[x][y] = hiddenMap[x][y][0];
        else
            publicMap[x][y] = "▢";
        countOfHiden--;
        doubleOpen(x,y);
    }
}

void Minesweeper::doubleOpen(int x, int y)
{
    if (hiddenMap[x][y][0] == '-' || (isdigit(hiddenMap[x][y][0]) && countOfFlagsOnboard(x, y) == stoi(hiddenMap[x][y])))
    {
        int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1}, {0, 1},
            {1, -1}, {1, 0}, {1, 1}};

        for (int i = 0; i < 8; ++i)
        {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (newX >= 0 && newX < rowSize && newY >= 0 && newY < columnSize && publicMap[x][y] != "▢")
            {
                open(newX, newY);
            }
        }
    }
}


int Minesweeper::countOfFlagsOnboard(int x, int y)
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
            if (publicMap[newX][newY] == F)
            {
                ++count;
            }
        }
    }

    return count;
}

void Minesweeper::play()
{
    int x = -1, y = -1;
    while (true)
    {
        cout << "Please set [x,y] (both positive and within bounds): ";
        cin >> x >> y;
        if (cin.fail() || x < 1 || x > rowSize || y < 1 || y > columnSize)
        {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Try again.\n";
            continue;
        }
        x--;
        y--;
        break;
    }
    firstOpen(x, y);
    printMap();

    while (countOfHiden != 0)
    {
        cout << "Please set [x,y]: ";
        cin >> x >> y;
        if (cin.fail() || x < 1 || x > rowSize || y < 1 || y > columnSize)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        x--;
        y--;

        char c;
        cout << "if you want open/o, set flag/f, double open/other: ";
        cin >> c;

        switch (c)
        {
        case 'o':
            open(x, y);
            break;
        case 'f':
            flag(x, y);
            break;
        default:
            doubleOpen(x, y);
            break;
        }
        printMap();
    }
    cout << "\t\t\t\t YOU WIN\n";
}