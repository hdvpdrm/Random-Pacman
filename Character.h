#ifndef CHARACTER_H
#define CHARACTER_H
#include<vector>
#include<string>
#include"SFML/System/Vector2.hpp"
#include"MazeGenerator.h"
using namespace std;
using namespace sf;

class Character
{
protected:
	const float movement_offset;
	enum class Dir
	{
		Left, Right, Down, Up
	};
	Dir curr_dir;
protected:
	Character(float movement_offset):movement_offset(movement_offset){}
	~Character(){}

	Vector2i get_pos_at_maze(const Vector2f& man_new_pos);
	bool can_move(const vector<string>& maze, const Vector2f& new_pos);
	Vector2i get_random_pos(const vector<string>& maze);
};
#endif

