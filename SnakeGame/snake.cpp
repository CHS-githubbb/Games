#include"snake.h"
#include"setting.h"
#include<iostream>


inline Snake::coord & Snake::head() {
	return snake_body[0];
}

inline Snake::coord & Snake::tail() {
	return snake_body[snake_body.size() - 1];
}

inline Snake::coord & Snake::at(const int index) {
	return snake_body[index];
}

Snake::Snake() {
	direct = RIGHT;
	for (int i = 0; i < 3; ++i)
		snake_body.push_back(coord{ 10 - i, basic::win_hei - 1 });//initial value area //5
	
	cursor::set_color(cursor::GREEN);
	//draw head
	cursor::gotoxy(head().x, head().y);
	std::cout << "*";
	//draw body
	for (int i = 1; i < snake_body.size(); ++i) {
		cursor::gotoxy(at(i).x, at(i).y);
		std::cout << "+";
	}

	//set back color
	cursor::set_color(cursor::WHITE);
}

void Snake::change_direction(const DIRECTION & dir){
	switch (dir){
	case UP:
		if (direct != DOWN) direct = dir;
		break;
	case DOWN:
		if (direct != UP) direct = dir;
		break;
	case LEFT:
		if (direct != RIGHT) direct = dir;
		break;
	case RIGHT:
		if (direct != LEFT) direct = dir;
		break;
	}
}

void Snake::move(){

	cursor::set_color(cursor::GREEN);

	coord temp;//find the way
	switch (direct) {
	case UP:
		temp.x = head().x; temp.y = head().y - 1;
		break;
	case DOWN:
		temp.x = head().x; temp.y = head().y + 1;
		break;
	case LEFT:
		temp.x = head().x - 1; temp.y = head().y;
		break;
	case RIGHT:
		temp.x = head().x + 1; temp.y = head().y;
		break;
	}

	cursor::gotoxy(tail().x, tail().y);
	if (!basic::cover_food(temp.x, temp.y)) {//snake did not eat food
		std::cout << " ";
	}
	else {
		std::cout << "+";
		snake_body.push_back(coord());
	}
	cursor::gotoxy(head().x, head().y);
	std::cout << "+";
	cursor::gotoxy(temp.x, temp.y);
	std::cout << "*";

	for (auto i = snake_body.size() - 1; i > 0; --i) {
		at(i).x = at(i - 1).x;
		at(i).y = at(i - 1).y;
	}
	head().x = temp.x;
	head().y = temp.y;

	cursor::set_color(cursor::WHITE);
}

bool Snake::is_alive() { 
	coord judge = head();
	if (judge.x == 0 || judge.x == basic::win_wid - 40 ||
		judge.y == 0 || judge.y == basic::win_hei)
		return false;//touch wall

	for (int i = 1; i < snake_body.size(); ++i)
		if (judge.x == at(i).x && judge.y == at(i).y)
			return false;//touch body

	return true;
}

bool Snake::not_there(const int x, const int y) {
	for (int i = 0; i < snake_body.size(); ++i)
		if (x == at(i).x && y == at(i).y)
			return false;

	return true;
}

inline int Snake::get_x() {
	return head().x;
}

inline int Snake::get_y() {
	return head().y;
}
