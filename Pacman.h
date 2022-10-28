#ifndef PACMAN_H
#define PACMAN_H
#include"SFML/Graphics.hpp"
#include"MazeGenerator.h"
#include<vector>
#include<string>
using namespace std;
using namespace sf;

class Pacman
{
	Vector2i pos;
	CircleShape* body;

	const float body_radius = 16.0f;
	const float movement_offset = 32.0f;
	const Vector2f offset = Vector2f(16.0f, 0.0f);

	enum class Dir
	{
		Left, Right, Down, Up
	};
	Dir curr_dir;
private:
	Vector2i get_random_pos(const vector<string>& maze);
	bool can_move(const vector<string>& maze, const Vector2f& new_pos);
	bool does_eat(const vector<string>& maze, const Vector2f& new_pos);
	Vector2i get_pos_at_maze(const Vector2f& man_new_pos);
public:
	Pacman(const vector<string>& maze);
	~Pacman();

	CircleShape* get_body_to_draw()const { return body; };
	void run(vector<string>& maze,Clock* clock);
	void process_key();

};
#endif PACMAN_H
