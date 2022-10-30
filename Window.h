#ifndef WINDOW_H
#define WINDOW_H
#include"SFML/Graphics.hpp"
#include<iostream>
#include"Pacman.h"
#include"GhostWalker.h"
#include"TextDrawer.h"
using namespace sf;
using namespace std;

//use namespace to avoid problem with compilation
//because sfml has Window too
namespace Render
{
class Window
{
	MazeGenerator maze_gen;
	vector<string> maze;

	RenderWindow* win;
	View* view;
	Pacman* man;

	int walkers_number = 2;
	vector<Clock*> walkers_clocks;
	vector<GhostWalker*> walkers;
	bool walker_added = false;

	Clock* clock;
	TextDrawer text_drawer;

	Texture heart, broken_heart;

	SoundBuffer ghost_apperance;
	Sound ghost_apperance_sound;
	Music background;


	bool is_space_pressed = false;
	bool game_started = false;
	bool pacman_is_dead = false;
	bool victory = false;

	const int win_height = 580;
	const int win_width = 1280;
	const float view_center_x = 1200.0f;
	const float view_center_y = 220.0f;
	const float element_size = 32.0f;
	int score_to_win;
	
	void draw_maze();
	void draw_floor(const Vector2f& pos);
	void draw_man();
	void draw_ghosts();
	void draw_health();


	void add_ghosts();
	void process_ghosts();
	void process_teleports();
	void teleport_object(Character* ch, int port_id,const Vector2f& port_pos);

	void generate_ghosts();

	int compute_score_to_win();
	void restart();
	void set_icon();
public:
	Window();
	~Window();

	void run();
};
}
#endif WINDOW_H

