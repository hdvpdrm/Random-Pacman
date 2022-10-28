#ifndef GHOST_WALKER_H
#define GHOST_WALKER_H
#include"Character.h"
#include"SFML/Graphics.hpp"
using namespace sf;
class GhostWalker:public Character
{
private:
	RectangleShape* body;
	void generate_random_dir();
public:
	GhostWalker(const vector<string>& maze);
	~GhostWalker();

	const RectangleShape* get_body()const { return body; };
	void run(vector<string>& maze, Clock* clock);
	bool does_intersects_pacman(const Vector2f& man_pos);

	void set_position(const Vector2f& pos)
	{
		body->setPosition(pos);
	}
	Vector2f get_position(){ return body->getPosition(); };
};
#endif GHOST_WALKER_H

