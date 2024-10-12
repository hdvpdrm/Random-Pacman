#include "GhostWalker.h"

GhostWalker::GhostWalker(const vector<string>& maze):Character(32.0f)
{
	body = new RectangleShape;
	auto pos = get_random_pos(maze);
	body->setPosition(pos.x,pos.y);
	generate_random_dir(maze);

	ghost_up.loadFromMemory(ghost_up_png,ghost_up_png_len);
	ghost_down.loadFromMemory(ghost_down_png,ghost_down_png_len);
	ghost_left.loadFromMemory(ghost_left_png,ghost_left_png_len);
	ghost_right.loadFromMemory(ghost_right_png,ghost_right_png_len);

	ghost.setScale(0.03f, 0.03f);
}
void GhostWalker::generate_random_dir(const vector<string>& maze)
{
	vector<Dir> dirs;
	if (can_move(maze, move(body->getPosition(), Dir::Up)))
		dirs.push_back(Dir::Up);
	if (can_move(maze, move(body->getPosition(), Dir::Down)))
		dirs.push_back(Dir::Down);
	if (can_move(maze, move(body->getPosition(), Dir::Left)))
		dirs.push_back(Dir::Left);
	if (can_move(maze, move(body->getPosition(), Dir::Right)))
		dirs.push_back(Dir::Right);

	int random_id = PacmanRand::rand(0, dirs.size()-1);
	curr_dir = dirs[random_id];

}
GhostWalker::~GhostWalker()
{
	delete body;
}
void GhostWalker::run(vector<string>& maze, Clock* clock, const Vector2f& man_pos)
{
	auto new_pos = move(body->getPosition(),curr_dir);
	
	
	if (!can_move(maze, new_pos))
	{
		//if you can move, then go back
		if (curr_dir == Dir::Left)curr_dir = Dir::Right;
		else if (curr_dir == Dir::Right)curr_dir = Dir::Left;
		else if (curr_dir == Dir::Up)curr_dir = Dir::Down;
		else if (curr_dir == Dir::Down)curr_dir = Dir::Up;

	}
	else if (does_see_pacman(man_pos, maze))
	{
		//if ghost starts seeing pacman 
		//it changes own direction to move forward to pacman

		auto my_pos = get_pos_at_maze(body->getPosition());
		auto _man_pos = get_pos_at_maze(man_pos);

		if (my_pos.x == _man_pos.x)
		{
			if (my_pos.y > _man_pos.y)
				curr_dir = Dir::Up;
			else
				curr_dir = Dir::Down;
		}
		if (my_pos.y == _man_pos.y)
		{
			if (my_pos.x > _man_pos.x)
				curr_dir = Dir::Left;
			else
				curr_dir = Dir::Right;
		}

		auto time = clock->getElapsedTime().asSeconds();
		if (time > 0.2f)
		{
			body->setPosition(move(body->getPosition(), curr_dir));
			clock->restart();
		}
	}
	else
	{
		auto time = clock->getElapsedTime().asSeconds();
		if (can_move(maze,new_pos) and time > 0.2f)
		{
			if (curr_dir == Dir::Left or curr_dir == Dir::Right)
			{
				auto try_up = move(body->getPosition(), Dir::Up);
				auto try_down = move(body->getPosition(), Dir::Down);

				auto move_up = [&]()
				{
					curr_dir = Dir::Up;
					body->setPosition(try_up);
				};
				auto move_down = [&]()
				{
					curr_dir = Dir::Down;
					body->setPosition(try_down);
				};
				if (can_move(maze, try_up) and can_move(maze, try_down))
				{
					int choice = PacmanRand::rand(0, 10);
					if (choice > 5)
						move_up();
					else
						move_down();
				}
				else if (can_move(maze, try_up))
					move_up();
				else if (can_move(maze, try_down))
					move_down();
				else
					body->setPosition(new_pos);

			}
			else if (curr_dir == Dir::Down or curr_dir == Dir::Up)
			{
				auto try_left = move(body->getPosition(), Dir::Left);
				auto try_right = move(body->getPosition(), Dir::Right);

				auto move_left = [&]()
				{
					curr_dir = Dir::Left;
					body->setPosition(try_left);
				};
				auto move_right = [&]()
				{
					curr_dir = Dir::Right;
					body->setPosition(try_right);
				};
				if (can_move(maze, try_left) and can_move(maze, try_right))
				{
					int choice = PacmanRand::rand(0, 10);
					if (choice > 5)
						move_right();
					else
						move_left();
				}
				else if (can_move(maze, try_left))
					move_left();
				else if (can_move(maze, try_right))
					move_right();
				else
					body->setPosition(new_pos);

			}
			
			clock->restart();
		}
	}
}
bool GhostWalker::does_intersects_pacman(const Vector2f& man_pos)
{
	return get_pos_at_maze(man_pos) == get_pos_at_maze(body->getPosition());
}
int GhostWalker::compute_distance(const Vector2i& pos1, const Vector2i& pos2)
{
	int dx = pow(pos1.x - pos2.x, 2);
	int dy = pow(pos1.y - pos2.y, 2);
	return (int)sqrt(dx + dy);
}
vector<char> GhostWalker::get_maze_elements_between(const Vector2i& pos1, 
						    const Vector2i& pos2,
						    const vector<string>& maze)
{
	vector<char> elements;
	if (pos1.x == pos2.x)
	{
		int beg = pos1.y < pos2.y ? pos1.y : pos2.y;
		int end = beg == pos1.y ? pos2.y : pos1.y;

		for (int i = beg; i < end+1; i++)
		{
			elements.push_back(maze[i][pos1.x]);
		}
	}
	if (pos1.y == pos2.y)
	{
		int beg = pos1.x < pos2.x ? pos1.x : pos2.x;
		int end = beg == pos1.x ? pos2.x : pos1.x;

		for (int i = beg; i < end+1; i++)
		{
			elements.push_back(maze[pos1.y][i]);
		}
	}
	return elements;
}
bool GhostWalker::does_see_pacman(const Vector2f& man_pos, const vector<string>& maze)
{
	auto my_pos = get_pos_at_maze(body->getPosition());
	auto _man_pos = get_pos_at_maze(man_pos);

	auto dist = compute_distance(my_pos, _man_pos);
	bool on_the_same_line = my_pos.x == _man_pos.x or my_pos.y == _man_pos.y;
	if (dist <= 15 and on_the_same_line)
	{
		auto elements_between = get_maze_elements_between(my_pos, _man_pos, maze);
		bool no_walls = find(elements_between.begin(), elements_between.end(), 0) == elements_between.end();
		return no_walls;
	}
	return false;
}
void GhostWalker::animate()
{
  auto pos = sf::Vector2f(get_position().x+40,get_position().y+80);
  ghost.setPosition(pos);
	switch (get_dir())
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
}
