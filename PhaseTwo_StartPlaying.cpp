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
            thread t1(&Minesweeper::treadFunction, this, ref(map));
            t1.join();
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
    if (hiddenMap[x][y][1] == 'c')
        publicMap[x][y] = F;
    countOfHiden--;
}

void Minesweeper::open(int x, int y)
{
    if (publicMap[x][y] != H)
        doubleOpen(x, y);
    else if (publicMap[x][y] == H && hiddenMap[x][y][0] == 'M')
        Boom();
    else
    {
        publicMap[x][y] = hiddenMap[x][y][0];
        countOfHiden--;
        doubleOpen(x, y);
    }
}

void Minesweeper::doubleOpen(int x, int y)
{
    if (hiddenMap[x][y][0] == '-' || countOfFlagsOnboard(x, y) == stoi(hiddenMap[x][y]))
    {
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
    while ((x < 0 || x > rowSize) || (y < 0 || y > columnSize))
    {
        cout << "Please set [x,y] (x must be positive and less than " << rowSize + 1 << ", y must be positive and less than " << columnSize + 1 << "): ";
        cin >> x >> y;
    }
    x--;y--;
    firstOpen(x, y);
    printMap();
    while (countOfHiden != 0)
    {
    	x = -1;
    	y = -1;
        while ((x < 0 || x > rowSize) || (y < 0 || y > columnSize))
        {
            cout << "Please set [x,y] (x must be positive and less than " << rowSize + 1 << ", y must be positive and less than " << columnSize + 1 << "): ";
            cin >> x >> y;
        }
        x--;y--;
        char c;
        cout << "if you want open/o,if you want set flag/f if doubleOpen other button:" << endl;
        cin >> c;
        switch (c)
        	{
        	case 'o':
       			open(x, y);
       			break;
       		case 'f':
       			flag(x,y);
       			break;
       		default:
       			doubleOpen(x,y);
       			break;
        	}
        printMap();
    }
}