#include "Window.h"

Render::Window::Window()
{
    win = new RenderWindow(VideoMode(win_width, win_height), "pacman");
    win->setFramerateLimit(40);
    view = new View();
    view->setCenter(view_center_x, view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(2.0f);
    maze = split(maze_gen.get_maze());

    man = new Pacman(maze);

    font.loadFromFile("Phased.ttf");
    high_score.setFont(font);
    high_score.setCharacterSize(56);
    high_score.setString("High Score:");
    score_value.setFont(font);
    score_value.setCharacterSize(52);

    for (int i = 0; i < 2; i++)
    {
        GhostWalker* walker = new GhostWalker(maze);
        walkers.push_back(walker);
    }
    for (int i = 0; i < 2; i++)
    {
        Clock* clock = new Clock();
        walkers_clocks.push_back(clock);
    }

}
Render::Window::~Window()
{
	delete win;
    delete view;
    delete man;
    delete clock;
}
void Render::Window::process_ghosts()
{
    for (int i = 0;i<2;i++)
    {
        walkers[i]->run(maze, walkers_clocks[i]);
    }
}
void Render::Window::run()
{
    clock = new Clock();
    while (win->isOpen())
    {
        sf::Event event;
        while (win->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win->close();
        }
        man->process_key();
        man->run(maze,clock);

        process_ghosts();

        win->setView(*view);
        win->clear();
        draw_maze();
        draw_man();
        draw_score();
        draw_ghosts();
        win->display();
    }
}
void Render::Window::draw_maze()
{
    for (int y = 0; y < maze.size(); y++)
    {
        auto line = maze[y];
        for (int x = 0; x < line.size(); x++)
        {
            switch (line[x])
            {
                case char(MazeGenerator::mazeChar):
                {
                    RectangleShape wall;
                    wall.setSize(Vector2f(element_size, element_size));
                    wall.setPosition(x* element_size, y* element_size);
                    wall.setFillColor(Color::White);
                    win->draw(wall);
                }
                break;
                case char(MazeGenerator::pelletChar):
                {
                    CircleShape pellet;
                    pellet.setRadius(element_size / 4);

                    auto offset = element_size / 4;
                    pellet.setPosition(x * element_size+ offset , y * element_size+ offset);
                    pellet.setFillColor(Color::White);
                    win->draw(pellet);
                }
                break;
                case char(MazeGenerator::wumpaChar):
                {
                    CircleShape cherry;
                    cherry.setRadius(element_size / 4);

                    auto offset = element_size / 4;
                    cherry.setPosition(x * element_size + offset, y * element_size + offset);
                    cherry.setFillColor(Color::Red);
                    win->draw(cherry);
                };
                break;
            };
        }
    }
}
void Render::Window::draw_man()
{
    win->draw(*man->get_body_to_draw());
}
void Render::Window::draw_score()
{
    score_value.setString(to_string(man->get_score()));
    score_value.setPosition(10.0f, -240.0f);
    high_score.setPosition(10.0f, -300.0f);
    win->draw(high_score);
    win->draw(score_value);
}
void Render::Window::draw_ghosts()
{
    for (auto& walker : walkers)
    {
        win->draw(*walker->get_body());
    }
}
vector<string> Render::Window::split(const string& str)
{
    vector<string> lines;
    stringstream streamData(str);

    string val;
    while (std::getline(streamData, val, '\n')) 
    {
        lines.push_back(val);
    }
    return lines;
}