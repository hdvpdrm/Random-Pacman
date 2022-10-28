#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include<random>
#include<vector>
using namespace std;

class MazeGenerator
{
const int height = 13;
const int width = 39;

int mazeChar = 475;
int pelletChar = 250;
int wumpaChar = 21;
int** maze;

public:
	enum class Type
	{
		wall,
		pellet,
		cherry
	};
private:
	void shuffle(int* arr, int size);
	void recursion(int r, int c);
	void generate();

	int rand();
public:
	MazeGenerator()
	{
		maze = new int*[height];
		for (int i = 0; i < height; ++i)
			maze[i] = new int[width];

	}
	~MazeGenerator()
	{
		for (int i = 0; i < height; ++i) {
			delete[] maze[i];
		}
		delete[] maze;
	}

	vector<vector<Type>> get_maze();

};
#endif MAZE_GENERATOR_H

