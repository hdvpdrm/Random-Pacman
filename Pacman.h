#ifndef PACMAN_H
#define PACMAN_H
#include"SFML/Graphics.hpp"
#include"MazeGenerator.h"
#include"Character.h"

class Pacman:Character
{
	Vector2i pos;
	CircleShape* body;

	const float body_radius = 16.0f;
	const Vector2f offset = Vector2f(16.0f, 0.0f);

	int score = 0;
	int health = 3;
private:
	bool does_eat(const vector<string>& maze, const Vector2f& new_pos);
public:
	Pacman(const vector<string>& maze);
	~Pacman();

	CircleShape* get_body_to_draw()const { return body; };
	void run(vector<string>& maze,Clock* clock);
	void process_key();

};
#endif PACMAN_H
