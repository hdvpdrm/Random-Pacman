#include "Window.h"

Render::Window::Window()
{
	win = new RenderWindow(VideoMode(win_width, win_height), "pacman");
    win->setFramerateLimit(40);
    view = new View();
    view->setCenter(view_center_x,view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(4.0f);
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

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            view->move(-10.0f, 0.0f);
            cout << view->getCenter().x << "  " << view->getCenter().y << endl;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            view->move(10.0f, 0.0f);
            cout << view->getCenter().x << "  " << view->getCenter().y << endl;
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
            if (line[x] == char(MazeGenerator::mazeChar))
            {
                RectangleShape wall;
                wall.setSize(Vector2f(element_size, element_size));
                wall.setPosition(x * element_size, y * element_size);
                wall.setFillColor(Color::White);
                win->draw(wall);

            }
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