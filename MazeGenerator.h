#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include<vector>
#include<map>
#include<string>
#include <sstream>
#include<iostream>
#include"SFML/System/Vector2.hpp"
#include"rand.h"
using namespace std;
using namespace sf;

class MazeGenerator
{
const int height = 20;
const int width = 20;
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

	map<int, Vector2i> teleports;
	void generate_teleports(vector<string>& maze);
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
  map<int,Vector2i> get_teleports() { return teleports; }
  //i know it's shit
  Vector2f get_center(){ return Vector2f((get_maze()[0].size()/2)*32,(get_maze().size()/2)*32);}
};
#endif //MAZE_GENERATOR_H

