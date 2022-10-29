#include "Window.h"

Render::Window::Window()
{
    win = new RenderWindow(VideoMode(win_width, win_height), "pacman");
    win->setFramerateLimit(40);
    view = new View();
    view->setCenter(view_center_x, view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(2.0f);
    maze = maze_gen.get_maze();

    man = new Pacman(maze);

    font.loadFromFile("Phased.ttf");
    high_score.setFont(font);
    high_score.setCharacterSize(56);
    high_score.setString("High Score:");
    score_value.setFont(font);
    score_value.setCharacterSize(52);

    for (int i = 0; i < walkers_number; i++)
    {
        GhostWalker* walker = new GhostWalker(maze);
        walkers.push_back(walker);
    }
    for (int i = 0; i < walkers_number; i++)
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
    for (int i = 0; i < walkers_number; i++)
    {
        walkers[i]->run(maze, walkers_clocks[i],man->get_position());
        if (walkers[i]->does_intersects_pacman(man->get_position()))
        {
            man->get_back_to_start();
            man->decrease_health();
        }
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

        add_ghosts();
        process_ghosts();
        process_teleports();

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
                    wall.setOutlineColor(Color::Blue);
                    wall.setOutlineThickness(2.0f);
                    wall.setFillColor(Color::Black);
                    win->draw(wall);
                }
                break;
                case char(MazeGenerator::pelletChar):
                {
                    CircleShape pellet;
                    pellet.setRadius(element_size / 4);

                    auto offset = element_size / 4;
                    pellet.setPosition(x * element_size+ offset , y * element_size+ offset);
                    pellet.setFillColor(Color(244, 129, 9,255));
                    draw_floor(Vector2f(x * element_size, y * element_size));
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

                    draw_floor(Vector2f(x * element_size, y * element_size));
                    win->draw(cherry);
                };
                break;
                default:
                    draw_floor(Vector2f(x * element_size, y * element_size));
                    break;
            };
        }
    }
}
void Render::Window::draw_man()
{
    win->draw(*man->get_body_to_draw());
}
void Render::Window::draw_floor(const Vector2f& pos)
{
    RectangleShape floor;
    floor.setSize(Vector2f(element_size, element_size));
    floor.setPosition(pos.x, pos.y);
    floor.setFillColor(Color(154,155,167,100));
    win->draw(floor);
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
void Render::Window::process_teleports()
{
    for (auto& port : maze_gen.get_teleports())
    {
        auto port_pos = Vector2f(port.second.x * element_size, port.second.y * element_size);
        teleport_object(man, port.first, port_pos);
       
        for (auto& walker : walkers)
            teleport_object(walker, port.first, port_pos);
    }
}
void Render::Window::teleport_object(Character* ch, int port_id, const Vector2f& port_pos)
{
    if (ch->get_position() == port_pos)
    {
        Vector2i pos_to_go;
        int new_dir;
        if (port_id == 0)
        {
            pos_to_go = maze_gen.get_teleports()[1];
            new_dir = 0;

            pos_to_go.x *= element_size;
            pos_to_go.y *= element_size;

            pos_to_go.x -= element_size;
        }
        if (port_id == 1)
        {
            pos_to_go = maze_gen.get_teleports()[0];
            new_dir = 1;
            pos_to_go.x *= element_size;
            pos_to_go.y *= element_size;

            pos_to_go.x += element_size;
        }
        if (port_id == 2)
        {
            pos_to_go = maze_gen.get_teleports()[3];
            pos_to_go.x *= element_size;
            pos_to_go.y *= element_size;
            new_dir = 3;

            pos_to_go.y -= element_size;
        }
        if (port_id == 3)
        {
            pos_to_go = maze_gen.get_teleports()[2];
            pos_to_go.x *= element_size;
            pos_to_go.y *= element_size;
            new_dir = 2;

            pos_to_go.y += element_size;
        }

        ch->set_direction((Character::Dir)new_dir);
        ch->set_position(Vector2f(pos_to_go));
    }
}
void Render::Window::add_ghosts()
{

    bool time_to_add = find(score_to_add_ghosts.begin(), score_to_add_ghosts.end(), man->get_score()) != score_to_add_ghosts.end();
    if (time_to_add and !walker_added)
    {
        GhostWalker* walker = new GhostWalker(maze);
        Clock* clock = new Clock();
        walkers.push_back(walker);
        walkers_clocks.push_back(clock);
        walkers_number++;
        walker_added = true;
    }

    if (!time_to_add)
    {
        walker_added = false;
    }
}