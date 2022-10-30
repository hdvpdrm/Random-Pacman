#include "TextDrawer.h"

TextDrawer::TextDrawer()
{
    font.loadFromFile("Phased.ttf");
    high_score.setFont(font);
    high_score.setCharacterSize(56);
    high_score.setString("High Score:");
    score_value.setFont(font);
    score_value.setCharacterSize(52);

    health.setFont(font);
    health.setCharacterSize(56);
    health.setString(":Health");
    health.setPosition(Vector2f(2100.0f, -300.0f));

    ur_dead1.setFont(font);
    ur_dead1.setCharacterSize(70);
    ur_dead1.setString("YOU");
    ur_dead1.setPosition(Vector2f(1100.0f, -350.0f));

    ur_dead2.setFont(font);
    ur_dead2.setCharacterSize(70);
    ur_dead2.setString("ARE");
    ur_dead2.setPosition(Vector2f(1100.0f, -250.0f));

    ur_dead3.setFont(font);
    ur_dead3.setCharacterSize(80);
    ur_dead3.setString("DEAD");
    ur_dead3.setPosition(Vector2f(1060.0f, -160.0f));
    ur_dead3.setFillColor(Color::Red);


    title1.setString("RANDOM");
    title1.setFont(font);
    title1.setCharacterSize(128);
    title1.setPosition(Vector2f(600.0f, -300.0f));

    title2.setString("PACMAN");
    title2.setFont(font);
    title2.setCharacterSize(128);
    title2.setPosition(Vector2f(1250.0f, -300.0f));
    title2.setFillColor(Color::Yellow);

    adds1.setString("press");
    adds1.setFont(font);
    adds1.setCharacterSize(60);
    adds1.setPosition(Vector2f(800.0f, -140.0f));

    SPACE.setString("SPACE");
    SPACE.setFont(font);
    SPACE.setCharacterSize(70);
    SPACE.setPosition(Vector2f(1080.0f, -150.0f));
    SPACE.setFillColor(Color::Blue);

    adds2.setString("to play");
    adds2.setFont(font);
    adds2.setCharacterSize(60);
    adds2.setPosition(Vector2f(1400.0f, -140.0f));

    victory.setString("VICTORY!");
    victory.setFont(font);
    victory.setCharacterSize(120);
    victory.setFillColor(Color::Red);
    victory.setPosition(Vector2(920.0f, -300.0f));
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
    score_value.setPosition(10.0f, -240.0f);
    high_score.setPosition(10.0f, -300.0f);
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