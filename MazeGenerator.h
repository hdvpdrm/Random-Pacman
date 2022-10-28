#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include<vector>
#include<iostream>
#include<string>
#include"rand.h"
using namespace std;

class MazeGenerator
{
const int height = 13;
const int width = 39;
int** maze;

public:
	static const short mazeChar = 0;
	static const short pelletChar = 1;
	static const short wumpaChar = 2;
private:
	void shuffle(int* arr, int size);
	void recursion(int r, int c);
	void generate();

public:
	MazeGenerator()
	{
		maze = new int*[height];
		for (int i = 0; i < height; ++i)
			maze[i] = new int[width];

	}
	~MazeGenerator()
	{
		for (int i = 0; i < height; ++i) 
			delete[] maze[i];

		delete[] maze;
	}

	string get_maze();

};
#endif MAZE_GENERATOR_H

