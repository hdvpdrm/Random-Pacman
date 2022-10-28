#include "Window.h"

Render::Window::Window()
{
	win = new RenderWindow(VideoMode(win_width, win_height), "pacman");
    win->setFramerateLimit(40);
    view = new View();
    view->setCenter(view_center_x,view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(2.0f);
    maze = split(maze_gen.get_maze());

}
Render::Window::~Window()
{
	delete win;
    delete view;
}
void Render::Window::run()
{
    
    while (win->isOpen())
    {
        sf::Event event;
        while (win->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win->close();
        }
       
        win->setView(*view);
        win->clear();
        draw_maze();
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