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
public:
	enum class Dir
	{
		Left, Right, Down, Up
	};
protected:
	const float movement_offset;
	const float y_offset = 2.0f;

	Dir curr_dir;
protected:
	Character(float movement_offset):movement_offset(movement_offset){}
	~Character(){}

	bool can_move(const vector<string>& maze, const Vector2f& new_pos);
	Vector2i get_random_pos(const vector<string>& maze);
public:
	Vector2i get_pos_at_maze(const Vector2f& man_new_pos);
	void set_direction(Dir dir)
	{
		curr_dir = dir;
	}
	Vector2f move(const Vector2f& old_pos, Dir dir);

	virtual Vector2f get_position() = 0;
	virtual void set_position(const Vector2f& pos) = 0;
};
#endif

