#include "TextDrawer.h"

TextDrawer::TextDrawer()
{
  font.loadFromMemory(ARCADECLASSIC_TTF,ARCADECLASSIC_TTF_len);
  high_score.setFont(font);
  high_score.setCharacterSize(70);
  high_score.setString("High Score");
  score_value.setFont(font);
  score_value.setCharacterSize(70);

  health.setFont(font);
  health.setCharacterSize(70);
  health.setString("Health");
  health.setPosition(Vector2f(1020.0f, -28.0f));

  ur_dead1.setFont(font);
  ur_dead1.setCharacterSize(80);
  ur_dead1.setString("YOU");
  ur_dead1.setPosition(Vector2f(500.0f, -70.0f));

  ur_dead2.setFont(font);
  ur_dead2.setCharacterSize(80);
  ur_dead2.setString("ARE");
  ur_dead2.setPosition(Vector2f(640.0f, -70.0f));

  ur_dead3.setFont(font);
  ur_dead3.setCharacterSize(100);
  ur_dead3.setString("DEAD");
  ur_dead3.setPosition(Vector2f(530.0f, -30.0f));
  ur_dead3.setFillColor(Color::Magenta);


  title1.setString("RANDOM");
  title1.setFont(font);
  title1.setCharacterSize(100);
  title1.setPosition(Vector2f(250.0f, -80.0f));

  title2.setString("PACMAN");
  title2.setFont(font);
  title2.setCharacterSize(100);
  title2.setPosition(Vector2f(640.0f, -80.0f));
  title2.setFillColor(Color::Yellow);

  adds1.setString("press");
  adds1.setFont(font);
  adds1.setCharacterSize(70);
  adds1.setPosition(Vector2f(270.0f, 5.0f));

  SPACE.setString("SPACE");
  SPACE.setFont(font);
  SPACE.setCharacterSize(80);
  SPACE.setPosition(Vector2f(480.0f, -5.0f));
  SPACE.setFillColor(Color::Magenta);

  adds2.setString("to play");
  adds2.setFont(font);
  adds2.setCharacterSize(70);
  adds2.setPosition(Vector2f(720.0f, 5.0f));

  victory.setString("VICTORY");
  victory.setFont(font);
  victory.setCharacterSize(90); 
  victory.setFillColor(Color::Yellow);
  victory.setPosition(Vector2f(450.0f, -40.0f));
}
void TextDrawer::draw_death_title(RenderWindow& window)
{
    window.draw(ur_dead1);
    window.draw(ur_dead2);
    window.draw(ur_dead3);
}
void TextDrawer::draw_score(RenderWindow& window, int score)
{
    score_value.setString(std::to_string(score));
    score_value.setPosition(380.0f, -28.0f);
    high_score.setPosition(-20.0f, -30.0f);
    window.draw(high_score);
    window.draw(score_value);
}
void TextDrawer::draw_title(RenderWindow& window)
{
    window.draw(title1);
    window.draw(title2);
    window.draw(adds1);
    window.draw(SPACE);
    window.draw(adds2);
}
void TextDrawer::draw_health(RenderWindow& window)
{
    window.draw(health);
}
void TextDrawer::draw_victory_title(RenderWindow& window)
{
    window.draw(victory);
}
