#include"setting.h"
#include"snake.h"
#include<iostream>

int main(){
game_start:
	basic::Game_initial();
	Snake snake;
	while (snake.is_alive() && basic::check_state()) {
		basic::generate_food(snake);
		basic::listen_key_board(snake);
		snake.move();
	}

	if (!snake.is_alive()) {
		basic::show_lose_mess();
	}
	else {
		basic::show_win_mess();
	}

	cursor::gotoxy(28, basic::win_hei / 2 + 2);
	std::cout << "ENTER Y TO REPLAY:  ";
	char order;
	std::cin >> order;
	if (order == 'Y' || order == 'y')
		goto game_start;

	getchar();
    return 0;
}
