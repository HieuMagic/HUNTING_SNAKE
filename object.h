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
};
struct food
{
	int x, y;
	food();//hàm t?o th?c ?n ng?u nhiên
	~food();
};
struct snake
{
	point body[SNAKE_MAX_SIZE];
	int length;
	int speed;
	snake();//hàm t?o r?n
	void updateLength();//hàm c?p nh?t chi?u dài r?n
	~snake();//hàm xóa r?n
};

void eatFood(snake& snake, food food);//hàm ?n th?c ?n
void moveSnake(snake& snake, direction direction);//hàm di chuy?n r?n
void drawSnake(const snake& snake);//hàm v? r?n
void impactWall(snake& snake, int width, int height, bool& isImpact);//hàm va ch?m v?i t??ng
void impactItself(snake& snake, bool& isImpact);//hàm va ch?m v?i chính nó

#endif // !_MY_OBJECT