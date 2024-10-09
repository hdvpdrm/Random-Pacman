#include "Window.h"

Render::Window::Window()
{
    win = new RenderWindow(VideoMode(win_width, win_height), "pacman", sf::Style::Titlebar | sf::Style::Close);
    win->setFramerateLimit(20);
    set_icon();

    view = new View();
    view->setCenter(view_center_x, view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(2.0f);
    maze = maze_gen.get_maze();

    man = new Pacman(maze);

    score_to_win = compute_score_to_win();
    background.openFromMemory(background_ogg,background_ogg_len);
    background.setLoop(true);
    background.setVolume(70);
    background.play();

    heart.loadFromMemory(heart_png,heart_png_len);
    broken_heart.loadFromMemory(broken_heart_png,broken_heart_png_len);
    ghost_apperance.loadFromMemory(ghost_apperance_ogg,ghost_apperance_ogg_len);
    ghost_apperance_sound.setBuffer(ghost_apperance);

    generate_ghosts();
}
Render::Window::~Window()
{
  delete win;
  delete view;
  delete man;
  delete clock;
}
void Render::Window::generate_ghosts()
{
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

        if (!game_started and Keyboard::isKeyPressed(Keyboard::Space) and !is_space_pressed)
        {
            game_started = true;
            is_space_pressed = true;
        }

        if (pacman_is_dead and Keyboard::isKeyPressed(Keyboard::Space) and !is_space_pressed)
        {
	  exit(0);
        }
        if (victory and Keyboard::isKeyPressed(Keyboard::Keyboard::Space) and !is_space_pressed)
        {
	    exit(0);
        }

        if (game_started)
        {
            if (!pacman_is_dead and !victory)
            {
                man->process_key();
                man->run(maze, clock);
            }

            if (!pacman_is_dead and man->get_health() == 0)
            {
                pacman_is_dead = true;
            }

            if (score_to_win == man->get_score())
            {
                victory = true;
            }

            if (!victory)
            {
                add_ghosts();
                process_ghosts();
                process_teleports();
            }
        }
        win->setView(*view);
        win->clear();
        draw_maze();

        if (game_started)
        {
            if (!pacman_is_dead)
                draw_man();

            text_drawer.draw_score(*win,man->get_score());
            draw_health();
            draw_ghosts();

            if (pacman_is_dead)
                text_drawer.draw_death_title(*win);

        }
        else if(!pacman_is_dead)
        {
            text_drawer.draw_title(*win);
        }
        if (victory)
        {
            text_drawer.draw_victory_title(*win);
        }
       
        win->display();

        if (!Keyboard::isKeyPressed(Keyboard::Space)) is_space_pressed = false;
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
                    wall.setOutlineColor(Color(101,101,101,255));
                    //wall.setOutlineThickness(2.0f);
                    wall.setFillColor(Color(101,101,101,255));
                    win->draw(wall);
                }
                break;
                case char(MazeGenerator::pelletChar):
                {
                    CircleShape pellet;
		    auto r  = element_size /4;
                    pellet.setRadius(r-2);

                    auto offset = element_size / 4;
                    pellet.setPosition(x * element_size+ offset+2 , y * element_size+ offset+2);
                    pellet.setFillColor(Color(255, 226, 0,255));
		    //pellet.setFillColor(Color::Yellow);
		    //pellet.setOutlineThickness(-0.5f);
		    //pellet.setOutlineColor(Color::Black);
                    draw_floor(Vector2f(x * element_size, y * element_size));
                    win->draw(pellet);                }
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
    man->animate();
    win->draw(man->get_body_to_draw());
}
void Render::Window::draw_floor(const Vector2f& pos)
{
    RectangleShape floor;
    floor.setSize(Vector2f(element_size, element_size));
    floor.setPosition(pos.x, pos.y);
    //floor.setFillColor(Color(180,180,180,255));
    floor.setFillColor(Color::Black);
    //floor.setFillColor(Color::White);
    win->draw(floor);
}

void Render::Window::draw_health()
{
    text_drawer.draw_health(*win);
    Vector2f start_pos(2030.0f, -280.0f);

    auto draw = [&](const Texture& texture)
    {
        Sprite heart;
        heart.setTexture(texture);
        heart.setScale(Vector2f(0.2f, 0.2f));
        heart.setPosition(start_pos);
        win->draw(heart);
        start_pos.x += 100.0f;
    };

    int number_of_good_hearts = man->get_health();
    int number_of_broken_hearts = 3 - number_of_good_hearts;


    //bugfix
    if (number_of_broken_hearts > 3)number_of_broken_hearts = 3;

    for (int i = 0; i < number_of_good_hearts; i++)draw(heart);
    for (int i = 0; i < number_of_broken_hearts;i++)draw(broken_heart);

}
void Render::Window::draw_ghosts()
{
    for (auto& walker : walkers)
    {
        walker->animate();
        win->draw(walker->get_sprite_to_draw());
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
    bool time_to_add = (man->get_score() % 2000) == 0;
    if (time_to_add and !walker_added)
    {
        GhostWalker* walker = new GhostWalker(maze);
        Clock* clock = new Clock();
        walkers.push_back(walker);
        walkers_clocks.push_back(clock);
        walkers_number++;
        walker_added = true;
        ghost_apperance_sound.play();
    }

    if (!time_to_add)
    {
        walker_added = false;
    }
}
int Render::Window::compute_score_to_win()
{
    int score = 0;
    for (auto& line : maze)
    {
        score += count(line.begin(), line.end(), (char)MazeGenerator::pelletChar) * 10;
    }
    return score;
}
void Render::Window::restart()
{
    maze = maze_gen.get_maze();
    walkers.clear();
    walkers_clocks.clear();
    generate_ghosts();

    delete man;
    man = new Pacman(maze);
    pacman_is_dead = false;
    game_started = false;
    score_to_win = compute_score_to_win();
    walkers_number = 2;
    win->clear();
    walker_added = false;
}
void Render::Window::set_icon()
{
    auto image = sf::Image{};
    image.loadFromMemory(pacman2_png,pacman2_png_len);

    win->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}
