#include "GhostWalker.h"

GhostWalker::GhostWalker(const vector<string>& maze):Character(32.0f)
{
	body = new RectangleShape;
	body->setFillColor(Color::Magenta);
	body->setSize(Vector2f(32.0f, 32.0f));

	auto pos = get_random_pos(maze);
	body->setPosition(Vector2f(pos));
	generate_random_dir(maze);
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
void GhostWalker::run(vector<string>& maze, Clock* clock)
{
	auto new_pos = move(body->getPosition(),curr_dir);
	
	if (!can_move(maze, new_pos))
	{
		//generate_random_dir();
		if (curr_dir == Dir::Left)curr_dir = Dir::Right;
		else if (curr_dir == Dir::Right)curr_dir = Dir::Left;
		else if (curr_dir == Dir::Up)curr_dir = Dir::Down;
		else if (curr_dir == Dir::Down)curr_dir = Dir::Up;

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
