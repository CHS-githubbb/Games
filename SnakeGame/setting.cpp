#include"setting.h"
#include"snake.h"
#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>//listen keyboard
#include<ctime>

//namespace cursor
void cursor::hide() {
	CONSOLE_CURSOR_INFO cur_info;
	GetConsoleCursorInfo(handle, &cur_info);
	cur_info.bVisible = false;
	SetConsoleCursorInfo(handle, &cur_info);
}

inline void cursor::gotoxy(const int x, const int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

inline void cursor::set_color(const int color) {
	SetConsoleTextAttribute(handle, color);
}




//namespace basic
void basic::Game_initial() {
	system("cls");
	score = 0;
	level = 1;
	food_is_ate = true;
	cursor::hide();
	for (int i = 1; i < win_wid; ++i) {
		cursor::gotoxy(i, 0);
		std::cout << "#";
		cursor::gotoxy(i, win_hei);
		std::cout << "#";
		if (i >= win_wid - 40) {
			cursor::gotoxy(i, 12);
			std::cout << "#";
		}
	}

	for (int i = 0; i <= win_hei; ++i) {
		cursor::gotoxy(0, i);
		std::cout << "#";
		cursor::gotoxy(win_wid - 40, i);
		std::cout << "#";
		cursor::gotoxy(win_wid, i);
		std::cout << "#";
	}//finish making the basic frame

	cursor::gotoxy(win_wid - 28, 4);
	std::cout << "Your Score:   " << 0;//now score is -10, and I can not come up with a better idea
	cursor::gotoxy(win_wid - 28, 7);
	std::cout << "Game Level:   " << level;//finish giving right-top info

	cursor::gotoxy(win_wid - 35, 14);
	std::cout << "Game Rules:";
	cursor::gotoxy(win_wid - 35, 17);
	std::cout << "W:  upwards       S:  dowards";
	cursor::gotoxy(win_wid - 35, 20);
	std::cout << "A:  leftwards     D:  rightwards";
	cursor::gotoxy(win_wid - 35, 23);
	std::cout << "J:  speed up      K:  speed down";
	cursor::gotoxy(win_wid - 35, 26);
	std::cout << "SPACE:            stop or continue";
}

void basic::generate_food(Snake & snake) {
	if (!food_is_ate)
		return;
	food_is_ate = false;
	score += 10;
	//you can change the difficulty here
	if (score > 0 && score % 20 == 0)
		level += 1;
	srand(time(nullptr));
	do {
		food_x = rand() % (win_wid - 40 - 1) + 1;
		food_y = rand() % (win_hei - 1) + 1;
	} while (!snake.not_there(food_x, food_y));

	cursor::set_color(cursor::RED);
	cursor::gotoxy(food_x, food_y);
	std::cout << "@";
	cursor::set_color(cursor::WHITE);
}

bool basic::cover_food(const int x, const int y) {//invoked by Snake::move
	return ( food_is_ate = (food_x == x && food_y == y) );
}

void basic::listen_key_board(Snake & snake) {
	if (kbhit()) {
		char order = getch();
		switch (order) {
		case'W':
		case'w':
			snake.change_direction(Snake::UP);
			break;
		case'S':
		case's':
			snake.change_direction(Snake::DOWN);
			break;
		case'A':
		case'a':
			snake.change_direction(Snake::LEFT);
			break;
		case'D':
		case'd':
			snake.change_direction(Snake::RIGHT);
			break;
		case'J':
		case'j':
			if (level < 10) level += 1;
			break;
		case'K':
		case'k':
			if (level > 1) level -= 1;
			break;
		case' ':
			stop();
			break;
		}
	}
}

bool basic::check_state() {
	if (score >= 100 && level < 6)
		level = 6;
	if (score >= 200)
		level = 10;
	cursor::gotoxy(win_wid - 14, 4);
	std::cout << score;
	cursor::gotoxy(win_wid - 14, 7);
	std::cout << level;
	Sleep(111 - 10 * level);
	return score < 1000;//win or not
}

void basic::show_lose_mess() {
	cursor::set_color(cursor::RED);
	cursor::gotoxy(28, basic::win_hei / 2 - 4);
	std::cout << "YOU LOSE!";
	cursor::gotoxy(28, basic::win_hei / 2 - 2);
	std::cout << "FINAL SCORE:  " << basic::score;
	cursor::set_color(cursor::WHITE);
}

void basic::show_win_mess() {
	cursor::set_color(cursor::RED);
	cursor::gotoxy(28, basic::win_hei / 2 - 4);
	std::cout << "OH!! YOU DID WIN!! BRAVO!!";
	cursor::gotoxy(28, basic::win_hei / 2 - 2);
	std::cout << "FINAL SCORE:  " << basic::score;
	cursor::set_color(cursor::WHITE);
}

void basic::stop() {
	while (true) {
		if (kbhit() && getch() == ' ')
			return;
	}
}
