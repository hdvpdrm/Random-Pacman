#ifndef TEXT_DRAWER_H
#define TEXT_DRAWER_H
#include"SFML/Graphics.hpp"
#include<string>
using namespace sf;

//include binary data of font
#include"Phased.h"

class TextDrawer
{
	Font font;
	Text high_score, score_value;
	Text title1, title2, adds1, adds2, SPACE;
	Text health, ur_dead1, ur_dead2, ur_dead3;
	Text victory;
public:
	TextDrawer();
	~TextDrawer(){}

	void draw_death_title(RenderWindow& window);
	void draw_score(RenderWindow& window,int score);
	void draw_title(RenderWindow& window);
	void draw_health(RenderWindow& window);
	void draw_victory_title(RenderWindow& window);
};
#endif //TEXT_DRAWER_H

