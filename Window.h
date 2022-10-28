#ifndef WINDOW_H
#define WINDOW_H
#include <sstream>
#include"SFML/Graphics.hpp"
#include"Pacman.h"
#include"GhostWalker.h"
using namespace sf;

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

	vector<Clock*> walkers_clocks;
	vector<GhostWalker*> walkers;

	Clock* clock;
	Font font;
	Text high_score,score_value;

	const int win_height = 580;
	const int win_width = 1280;
	const float view_center_x = 1200.0f;
	const float view_center_y = 220.0f;
	const float element_size = 32.0f;
	
	void draw_maze();
	void draw_man();
	void draw_ghosts();
	void draw_score();

	void process_ghosts();

	bool is_pressed = false;
	vector<string> split(const string& str);
public:
	Window();
	~Window();

	void run();
};
}
#endif WINDOW_H

