#include "Window.h"

Render::Window::Window()
{
    win = new RenderWindow(VideoMode(win_width, win_height), "pacman", sf::Style::Titlebar | sf::Style::Close);
    win->setFramerateLimit(40);
    view = new View();
    view->setCenter(view_center_x, view_center_y);
    view->setSize(win_width, win_height);
    view->zoom(2.0f);
    maze = maze_gen.get_maze();

    man = new Pacman(maze);

    heart.loadFromFile("assets/heart.png");
    broken_heart.loadFromFile("assets/broken_heart.png");
    ghost_up.loadFromFile("assets/ghost_up.png");
    ghost_down.loadFromFile("assets/ghost_down.png");
    ghost_left.loadFromFile("assets/ghost_left.png");
    ghost_right.loadFromFile("assets/ghost_right.png");

    font.loadFromFile("Phased.ttf");
    high_score.setFont(font);
    high_score.setCharacterSize(56);
    high_score.setString("High Score:");
    score_value.setFont(font);
    score_value.setCharacterSize(52);

    health.setFont(font);
    health.setCharacterSize(56);
    health.setString(":Health");
    health.setPosition(Vector2f(2100.0f,-300.0f));

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

        if (!game_started and Keyboard::isKeyPressed(Keyboard::Space))
            game_started = true;

        if (pacman_is_dead and Keyboard::isKeyPressed(Keyboard::Space))
        {
            maze = maze_gen.get_maze();
            walkers.clear();
            walkers_clocks.clear();
            generate_ghosts();

            delete man;
            man = new Pacman(maze);
            pacman_is_dead = false;
            game_started = false;
        }

        if (game_started)
        {
            if (!pacman_is_dead)
            {
                man->process_key();
                man->run(maze, clock);
            }

            if (!pacman_is_dead and man->get_health() == 0)
            {
                pacman_is_dead = true;
            }
            add_ghosts();
            process_ghosts();
            process_teleports();
        }
        win->setView(*view);
        win->clear();
        draw_maze();

        if (game_started)
        {
            if (!pacman_is_dead)
                draw_man();

            draw_score();
            draw_health();
            draw_ghosts();

            if (pacman_is_dead)
                draw_death_title();

        }
        else if(!pacman_is_dead)
        {
            draw_title();
        }
       
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
void Render::Window::draw_title()
{
    win->draw(title1);
    win->draw(title2);
    win->draw(adds1);
    win->draw(SPACE);
    win->draw(adds2);
}
void Render::Window::draw_death_title()
{
    win->draw(ur_dead1);
    win->draw(ur_dead2);
    win->draw(ur_dead3);
}
void Render::Window::draw_health()
{
    win->draw(health);
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
        Sprite ghost;
        ghost.setScale(0.03f, 0.03f);
        ghost.setPosition(walker->get_position());
        switch (walker->get_dir())
        {
        case Character::Dir::Down:
            ghost.setTexture(ghost_down);
        break;
        case Character::Dir::Up:
            ghost.setTexture(ghost_up);
        break;
        case Character::Dir::Left:
            ghost.setTexture(ghost_left);
        break;
        case Character::Dir::Right:
            ghost.setTexture(ghost_right);
        break;
        }
        win->draw(ghost);
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