#include "MazeGenerator.h"


void MazeGenerator::shuffle(int* arr, int size)
{
    int temporary;
    int randomNum;
    int last;

    for (last = size; last > 1; last--)
    {
        randomNum = rand() % last;
        temporary = arr[randomNum];
        arr[randomNum] = arr[last - 1];
        arr[last - 1] = temporary;
    }
}
void MazeGenerator::recursion(int r, int c) 
{
    const int dir_number = 4;
    int randDirs[dir_number];
    for (int i = 0; i < dir_number; i++)
    {
        randDirs[i] = i + 1;
    }
    shuffle(randDirs, dir_number);

    for (int i = 0; i < dir_number; i++)
    {
        switch (randDirs[i]) {
        case 1:
            // up
            if (r - 2 <= 0) {
                continue;
            }
            if (maze[r - 2][c] != 0) {
                maze[r - 2][c] = 0;
                maze[r - 1][c] = 0;
                recursion(r - 2, c);
            }
            break;
        case 2:
            // right
            if (c + 2 >= width - 1) {
                continue;
            }
            if (maze[r][c + 2] != 0) {
                maze[r][c + 2] = 0;
                maze[r][c + 1] = 0;
                recursion(r, c + 2);
            }
            break;
        case 3:
            // down
            if (r + 2 >= height - 1) {
                continue;
            }
            if (maze[r + 2][c] != 0) {
                maze[r + 2][c] = 0;
                maze[r + 1][c] = 0;
                recursion(r + 2, c);
            }
            break;
        case 4:
            // left
            if (c - 2 <= 0) {
                continue;
            }
            if (maze[r][c - 2] != 0) {
                maze[r][c - 2] = 0;
                maze[r][c - 1] = 0;
                recursion(r, c - 2);
            }
            break;
        }
    }
}
void MazeGenerator::generate()
{
    for (int i = 0; i < height; i++)
        for (int x = 0; x < width; x++)
            maze[i][x] = 1;

    int r = rand() % height;
    while (r % 2 == 0)
        r = rand() % height;

    int c = rand() % width;
    while (c % 2 == 0)
        c = rand() % width;

    maze[r][c] = 0;

    recursion(r, c);
}
int MazeGenerator::rand()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0, RAND_MAX); 

    return dist6(rng);
}

vector<vector<MazeGenerator::Type>>  MazeGenerator::get_maze()
{
    generate();

    vector<vector<MazeGenerator::Type>> _maze;
    _maze.resize(height);
    for (int i = 0; i < _maze.size(); i++)_maze[i].resize(width);

    auto init = [&](int x, int y, vector<vector<MazeGenerator::Type>>& _maze)
    {
        if (y == 1 && x == 1)
            _maze[y][x] = Type::cherry;
        else if (maze[y][x] == 0)
            _maze[y][x] = Type::pellet;
        else
            _maze[y][x] = Type::wall;
    };
    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 0; x < width - 2; x++)
        {
            init(x, y, _maze);
        }

        for (int x = width - 2; x >= 0; x--)
        {
            init(x, y, _maze);
        }
    }
    for (int y = height - 2; y >= 0; y--)
    {
        for (int x = 0; x < width - 2; x++)
        {
            init(x, y, _maze);
        }

        for (int x = width - 2; x >= 0; x--)
        {
            init(x, y, _maze);
        }
    }

    return _maze;
}
