#include "Pacman.h"

Pacman::Pacman(const vector<string>& maze)
{
	pos = get_random_pos(maze);
	pos.y += offset.y;
	body = new CircleShape(body_radius);
	body->setFillColor(Color::Yellow);
	body->setPosition(Vector2f(pos));
}
Pacman::~Pacman()
{
	delete body;
}
Vector2i Pacman::get_random_pos(const vector<string>& maze)
{
	vector<Vector2i> free_poses;
	for(int y = 0;y<maze.size();y++)
		for (int x = 0; x < maze[y].size(); x++)
		{
			if(maze[y][x] == MazeGenerator::pelletChar)
				free_poses.push_back(Vector2i(x, y));
		}

	auto id = PacmanRand::rand(0, free_poses.size());
	auto random_vec = free_poses[id];

	const int elem_size = 32;
	random_vec.x *= elem_size;
	random_vec.y *= elem_size;
	return random_vec;
}