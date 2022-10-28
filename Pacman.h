#ifndef PACMAN_H
#define PACMAN_H
#include"SFML/Graphics.hpp"
#include"MazeGenerator.h"
#include"Character.h"

class Pacman:Character
{
	Vector2i pos;
	Vector2f start_pos;
	CircleShape* body;

	const float body_radius = 16.0f;

	int score = 0;
	int health = 3;
private:
	bool does_eat(const vector<string>& maze, const Vector2f& new_pos);
public:
	Pacman(const vector<string>& maze);
	~Pacman();

	const CircleShape* get_body_to_draw()const { return body; };
	Vector2f get_position()const { return body->getPosition(); };
	Vector2f get_start_position()const { return start_pos; };
	void run(vector<string>& maze,Clock* clock);
	void process_key();
	void decrease_health() { health--; };
	int get_health() { return health; }
	void get_back_to_start()
	{
		body->setPosition(start_pos);
		curr_dir = (Dir)PacmanRand::rand(0, 3);
	}

	int get_score()const { return score; }

};
#endif PACMAN_H
