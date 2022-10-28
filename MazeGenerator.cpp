#include "MazeGenerator.h"


void MazeGenerator::shuffle(int* arr, int size)
{
    int temporary;
    int randomNum;
    int last;

    for (last = size; last > 1; last--)
    {
        randomNum = PacmanRand::rand() % last;
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

    int r = PacmanRand::rand() % height;
    while (r % 2 == 0)
        r = PacmanRand::rand() % height;

    int c = PacmanRand::rand() % width;
    while (c % 2 == 0)
        c = PacmanRand::rand() % width;

    maze[r][c] = 0;

    recursion(r, c);
}

string  MazeGenerator::get_maze()
{
    generate();

    string m;
    auto init = [&](int i, int j)
    {
        if (i == 1 && j == 1)
            m += char(wumpaChar);
        else if (maze[i][j] == 0)
            m += char(pelletChar);
        else
            m += char(mazeChar);
    };
    for (int i = 0; i < height - 2; i++)
    {
        for (int j = 0; j < width - 2; j++)
        {
            init(i, j);
        }

        for (int j = width - 2; j >= 0; j--)
        {
            init(i, j);
        }
        m += '\n';
    }

    for (int i = height - 2; i >= 0; i--)
    {
        for (int j = 0; j < width - 2; j++)
        {
            init(i, j);
        }

        for (int j = width - 2; j >= 0; j--)
        {
            init(i, j);
        }
        m += '\n';
    }

    return m;
}
