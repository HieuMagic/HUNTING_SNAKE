#include "object.h"
#include "console.h"
#include <iostream>

const char* LIST = "2312024523120258231202602312021923120213";

food::food()
{
	srand(time(NULL));
	x = rand() % (FOOD_SIZE - 1) + 1;
	y = rand() % (FOOD_SIZE - 1) + 1;

	gotoXY(x, y);
	std::cout << " ";
}
food::~food()
{

	gotoXY(x, y);
	std::cout << " ";
}
snake::snake()
{
	speed = SNAKE_MIN_SPEED;
	length = SNAKE_INIT_SIZE;
}
void snake::updateLength()
{
	length++;
}
snake::~snake()
{
	delete[] body;
}
door::door()
{
	srand(time(NULL));
	kernel.x = rand() % (FOOD_SIZE - 1) + 1;
	kernel.y = rand() % (FOOD_SIZE - 1) + 1;
	wall[0].x = kernel.x - 1; wall[0].y = kernel.y - 1;
	wall[1].x = kernel.x - 1; wall[1].y = kernel.y;
	wall[2].x = kernel.x - 1; wall[2].y = kernel.y + 1;
	wall[3].x = kernel.x; wall[3].y = kernel.y - 1;
	wall[4].x = kernel.x; wall[4].y = kernel.y + 1;

	gotoXY(kernel.x, kernel.y);
	std::cout << " ";
	for (int i = 0; i < 5; i++)
	{
		gotoXY(wall[i].x, wall[i].y);
		std::cout << " ";
	}
}
door::~door()
{
	delete[] wall;
}

bool operator==(point a, point b)
{
	if (a.x == b.x && a.y == b.y)
	{
		return true;
	}
	return false;
}

void eatFood(snake& snake, food food)
{
	if (snake.body[0].x == food.x && snake.body[0].y == food.y)
	{
		snake.length++;
	}
}
void moveSnake(snake& snake, direction direction)
{
	gotoXY(snake.body[snake.length - 1].x, snake.body[snake.length - 1].y);
	std::cout << " ";
	for (int i = snake.length; i > 0; i--)
	{
		snake.body[i] = snake.body[i - 1];

	}
	switch (direction) {
	case direction::UP:
		snake.body[0].y--;
		break;
	case direction::DOWN:
		snake.body[0].y++;
		break;
	case direction::LEFT:
		snake.body[0].x--;
		break;
	case direction::RIGHT:
		snake.body[0].x++;
		break;
	}
}
void drawSnake(const snake& snake)
{
	int LENGTH = snake.length;
	int speed = ONE_SECOND / snake.speed;

	for (int i = 0; i < snake.length; i++)
	{
		gotoXY(snake.body[i].x, snake.body[i].y);
		std::cout << LIST[i % LENGTH];
		Sleep(speed);
	}
}
void impactWall(const snake& snake, int width, int height, bool& isImpact)
{
	if (snake.body[0].x == 0 || snake.body[0].x == width - 1 || snake.body[0].y == 0 || snake.body[0].y == height - 1)
	{
		isImpact = true;
	}
}
void impactItself(const snake& snake, bool& isImpact)
{
	point head = snake.body[0];
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.body[i].x == head.x && snake.body[i].y == head.y)
		{
			isImpact = true;
			break;
		}
	}
}
void impactDoor(const snake& snake, const door& door, bool& isImpact, bool& next)
{
	point head = snake.body[0];

	if (head == door.kernel)
	{
		next = true;
		return;
	}
	for (int i = 0; i < 5; i++)
	{
		if (head == door.wall[i])
		{
			isImpact = true;
			break;
		}
	}
}

namespace level_1
{
	struct obstacle
	{

	};
}

namespace level_2
{
	struct obstacle
	{

	};
}

namespace level_3
{
	struct obstacle
	{

	};
}

namespace level_4
{
	struct obstacle
	{

	};
	struct monster
	{

	};
}

namespace level_5
{
	struct obstacle
	{

	};
	struct monster
	{

	};
}