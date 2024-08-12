#ifndef GHOST_WALKER_H
#define GHOST_WALKER_H
#include"Character.h"
#include"SFML/Graphics.hpp"
#include"MazeGenerator.h"
#include<cmath>
#include<iostream>
using namespace sf;
class GhostWalker:public Character
{
private:
	RectangleShape* body;

	Texture ghost_up, ghost_down, ghost_right, ghost_left;
	Sprite ghost;
private:
	void generate_random_dir(const vector<string>& maze);
	int compute_distance(const Vector2i& pos1, const Vector2i& pos2);
	vector<char> get_maze_elements_between(const Vector2i& pos1, 
					       const Vector2i& pos2,
					       const vector<string>& maze);
	bool does_see_pacman(const Vector2f& man_pos, const vector<string>& maze);
public:
	GhostWalker(const vector<string>& maze);
	~GhostWalker();

	void run(vector<string>& maze, Clock* clock, const Vector2f& man_pos);
	bool does_intersects_pacman(const Vector2f& man_pos);

	void set_position(const Vector2f& pos)
	{
		body->setPosition(pos);
	}

	void animate();
	const Sprite& get_sprite_to_draw()const { return ghost; }
	Vector2f get_position(){ return body->getPosition(); };
};
#endif //GHOST_WALKER_H

