#ifndef WINDOW_H
#define WINDOW_H
#include <sstream>
#include"SFML/Graphics.hpp"
#include"MazeGenerator.h"
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

	const int win_height = 580;
	const int win_width = 1280;
	const float view_center_x = 1200.0f;
	const float view_center_y = 220.0f;
	const float element_size = 32.0f;
	
	void draw_maze();
	vector<string> split(const string& str);
public:
	Window();
	~Window();

	void run();
};
}
#endif WINDOW_H

