#include "Character.h"

Vector2i Character::get_pos_at_maze(const Vector2f& man_new_pos)
{
	auto y = (int)man_new_pos.y / movement_offset;
	auto x = (int)man_new_pos.x / movement_offset;
	return Vector2i(x, y);
}
bool Character::can_move(const vector<string>& maze, const Vector2f& new_pos)
{
	auto pos = get_pos_at_maze(new_pos);
	if (maze[pos.y][pos.x] != MazeGenerator::mazeChar)return true;

	return false;
}
Vector2i Character::get_random_pos(const vector<string>& maze)
{
	vector<Vector2i> free_poses;
	for (int y = 0; y < maze.size(); y++)
		for (int x = 0; x < maze[y].size(); x++)
		{
			if (maze[y][x] == MazeGenerator::pelletChar)
				free_poses.push_back(Vector2i(x, y));
		}

	auto id = PacmanRand::rand(0, free_poses.size());
	auto random_vec = free_poses[id];

	const int elem_size = 32;
	random_vec.x *= elem_size;
	random_vec.y *= elem_size;
	return random_vec;
}
Vector2f Character::move(const Vector2f& old_pos,Dir dir)
{
	auto new_pos = old_pos;
	switch (dir)
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
	return new_pos;
}