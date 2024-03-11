#pragma once
#ifndef _MY_OBJECT
#define _MY_OBJECT

#define ONE_SECOND 1000
#define SNAKE_COLOR 10
#define FOOD_COLOR 12

const int FOOD_SIZE = 12;
const int SNAKE_INIT_SIZE = 3;
const int SNAKE_MAX_SIZE = 100;
const int SNAKE_MIN_SPEED = 10;
const int SNAKE_MAX_SPEED = 100;

enum direction {
	UP, DOWN, LEFT, RIGHT
};
struct point {
	int x, y;
	friend bool operator==(point a, point b);
};
struct food
{
	int x, y;
	food();//h�m t?o th?c ?n ng?u nhi�n
	~food();
};
struct snake
{
	point body[SNAKE_MAX_SIZE];
	int length;
	int speed;
	snake();//h�m t?o r?n
	void updateLength();//h�m c?p nh?t chi?u d�i r?n
	~snake();//h�m x�a r?n
};
struct door
{
	point kernel;
	point wall[5];
	door();
	~door();
	//00
	//01
	//00
};

void eatFood(snake& snake, food food);//h�m ?n th?c ?n
void moveSnake(snake& snake, direction direction);//h�m di chuy?n r?n
void drawSnake(const snake& snake);//h�m v? r?n
void impactWall(const snake& snake, int width, int height, bool& isImpact);//h�m va ch?m v?i t??ng
void impactItself(const snake& snake, bool& isImpact);//h�m va ch?m v?i ch�nh n�
void impactDoor(const snake& snake, const door& door, bool& isImpact, bool& next);//h�m va ch?m v?i c?a


namespace level_1
{
	struct obstacle;

}

#endif // !_MY_OBJECT