#include "Pacman.h"

Pacman::Pacman(const vector<string>& maze):Character(32.0f)
{
	body = new CircleShape();
	body->setRadius(body_radius);

	pos = get_random_pos(maze);
	start_pos = Vector2f(pos);

	body->setPosition(start_pos);
	sprite.setPosition(Vector2f(pos));

	pacman1.loadFromFile("assets/pacman1.png");
	pacman2.loadFromFile("assets/pacman2.png");

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
	if (does_heal(maze, body->getPosition()) && health < 3)
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
void Pacman::animate()
{
	sprite.setScale(0.06f, 0.06f);

	auto curr_pos = get_position();
	curr_pos.y += 16.0f;
	curr_pos.x += 13.0f;
	sprite.setPosition(curr_pos);

	auto pacman_center_x = (sprite.getTextureRect().left + sprite.getTextureRect().width) / 2;
	auto pacman_center_y = (sprite.getTextureRect().top + sprite.getTextureRect().height) / 2;
	sprite.setOrigin(pacman_center_x, pacman_center_y);

	switch (get_dir())
	{
	case Character::Dir::Down:
		sprite.setRotation(90);
		break;
	case Character::Dir::Up:
		sprite.setRotation(-90);
		break;
	case Character::Dir::Left:
		sprite.setRotation(180);
		break;
	case Character::Dir::Right:
		sprite.setRotation(-360);
		break;
	};
	if (pacman_animation_clock.getElapsedTime().asSeconds() > 0.2f)
	{
		if (show1_rate)
		{
			sprite.setTexture(pacman1);
			show1_rate = false;
		}
		else
		{
			show1_rate = true;
			sprite.setTexture(pacman2);
		}

		pacman_animation_clock.restart();
	}
}