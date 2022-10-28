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
	Vector2f offset = Vector2f(16.0f, 0.0f);
private:
	Vector2i get_random_pos(const vector<string>& maze);
public:
	Pacman(const vector<string>& maze);
	~Pacman();

	Vector2i get_pos()const { return pos; }

	CircleShape* get_body_to_draw()const { return body; };
	float get_radius()const { return body_radius; };

};
#endif PACMAN_H
