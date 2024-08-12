#ifndef PACMAN_H
#define PACMAN_H
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"MazeGenerator.h"
#include"Character.h"

class Pacman:public Character
{
	Vector2i pos;
	Vector2f start_pos;
	CircleShape* body;

	Sprite sprite;
	Texture pacman1, pacman2;
	bool show1_rate = true;
	Clock pacman_animation_clock;

	SoundBuffer eat, heal, hurt;
	Sound eat_sound, heal_sound, hurt_sound;

	const float body_radius = 16.0f;
	

	int score = 0;
	int health = 3;
private:
	bool does_eat(const vector<string>& maze, const Vector2f& new_pos);
	bool does_heal(const vector<string>& maze, const Vector2f& new_pos);
public:
	Pacman(const vector<string>& maze);
	~Pacman();

	const Sprite& get_body_to_draw()const { return sprite; };
	Vector2f get_position() { return body->getPosition(); };
	Vector2f get_start_position()const { return start_pos; };
	void run(vector<string>& maze,Clock* clock);
	void process_key();
	void decrease_health() 
	{ 
		hurt_sound.play();
		health--; 
	};
	int get_health() { return health; }
	void get_back_to_start()
	{
		body->setPosition(start_pos);
		curr_dir = (Dir)PacmanRand::rand(0, 3);
	}
	void set_position(const Vector2f& pos)
	{
		body->setPosition(pos);
	}

	int get_score()const { return score; }
	void animate();

};
#endif //PACMAN_H
