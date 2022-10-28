#include "Pacman.h"

Pacman::Pacman(const vector<string>& maze):Character(32.0f)
{
	pos = get_random_pos(maze);
	pos.y += offset.y;
	body = new CircleShape(body_radius);
	body->setFillColor(Color::Yellow);
	body->setPosition(Vector2f(pos));

	curr_dir = (Dir)PacmanRand::rand(0, 3);
}
Pacman::~Pacman()
{
	delete body;
}
void Pacman::run(vector<string>& maze,Clock* clock)
{
	auto new_pos = body->getPosition();
	switch (curr_dir)
	{
	case Dir::Down:
	{
		new_pos.y += movement_offset;
	}
	break;
	case Dir::Up:
	{
		new_pos.y += -movement_offset;
	}
	break;
	case Dir::Left:
	{
		new_pos.x += -movement_offset;
	}
	break;
	case Dir::Right:
	{
		new_pos.x += movement_offset;
	}
	break;
	};

	auto time = clock->getElapsedTime().asSeconds();
	if (can_move(maze, new_pos) and time > 0.2f)
	{
		if (does_eat(maze, new_pos))
		{
			auto pos = get_pos_at_maze(new_pos);
			maze[pos.y][pos.x] = (char)MazeGenerator::openChar;
			score += 10;
		}
		body->setPosition(new_pos);
		clock->restart();
	}
}

bool Pacman::does_eat(const vector<string>& maze, const Vector2f& new_pos)
{
	auto pos = get_pos_at_maze(new_pos);
	if (maze[pos.y][pos.x] == MazeGenerator::pelletChar)return true;
	
	return false;
}
void Pacman::process_key()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		curr_dir = Dir::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		curr_dir = Dir::Right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		curr_dir = Dir::Down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		curr_dir = Dir::Up;
	}
}