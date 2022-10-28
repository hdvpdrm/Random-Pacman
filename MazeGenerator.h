#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include<vector>
#include<string>
#include <sstream>
#include"SFML/System/Vector2.hpp"
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
	static const short openChar = 3;
	static const short teleportChar = 4;
private:
	void shuffle(int* arr, int size);
	void recursion(int r, int c);
	void generate();
	vector<string> split(const string& str);

	sf::Vector2i teleport1_pos, teleport2_pos;
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

	vector<string> get_maze();
	sf::Vector2i get_teleport1_pos()const { return teleport1_pos; }
	sf::Vector2i get_teleport2_pos()const { return teleport2_pos; }
};
#endif MAZE_GENERATOR_H

