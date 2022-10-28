#ifndef GHOST_WALKER_H
#define GHOST_WALKER_H
#include"Character.h"
#include"SFML/Graphics.hpp"
using namespace sf;
class GhostWalker:Character
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
};
#endif GHOST_WALKER_H

