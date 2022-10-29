#include "Pacman.h"

Pacman::Pacman(const vector<string>& maze):Character(32.0f)
{
	pos = get_random_pos(maze);
	start_pos = Vector2f(pos);
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
	auto clear_space = [&]()
	{
		auto pos = get_pos_at_maze(body->getPosition());
		maze[pos.y][pos.x] = (char)MazeGenerator::openChar;
	};
	if (does_eat(maze, body->getPosition()))
	{
		clear_space();
		score += 10;
	}
	if (does_heal(maze, body->getPosition()))
	{
		clear_space();
		health++;
	}

	auto new_pos = move(body->getPosition(),curr_dir);

	auto time = clock->getElapsedTime().asSeconds();
	if (can_move(maze, new_pos) and time > 0.2f)
	{
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
bool Pacman::does_heal(const vector<string>& maze, const Vector2f& new_pos)
{
	auto pos = get_pos_at_maze(new_pos);
	if (maze[pos.y][pos.x] == MazeGenerator::wumpaChar)return true;
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