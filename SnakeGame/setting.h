#ifndef SETTING_H
#define SETTING_H
#include"snake.h"
#include<windows.h>

namespace cursor {
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	static const int RED = 12, GREEN = 2, WHITE = 15, BLACK = 0;

	void hide();
	inline void gotoxy(const int x, const int y);
	inline void set_color(const int color);
}

namespace basic {
	static const int win_wid = 110, win_hei = 28;
	static int score = 0, level = 1;
	static int food_x = 0, food_y = 0;
	static bool food_is_ate = true;

	void Game_initial();
	void generate_food(Snake &);
	bool cover_food(const int x, const int y);
	void listen_key_board(Snake &);
	bool check_state();
	void show_lose_mess();
	void show_win_mess();
	void stop();
}


#endif
