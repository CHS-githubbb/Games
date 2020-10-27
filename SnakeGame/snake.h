#ifndef SNAKE_H
#define SNAKE_H
#include<vector>

class Snake {
public:
	enum DIRECTION { UP, DOWN, LEFT, RIGHT };
private:
	struct coord{
		int x, y;
		coord(int x_ = 0, int y_ = 0):x(x_), y(y_){}
	};
	//prepraring work

	std::vector<coord> snake_body;//save all the coordinates of snake
	DIRECTION direct;//moving direction of snake
	inline coord & head();
	inline coord & tail();
	inline coord & at(const int index);

public:
	Snake();
	void change_direction(const DIRECTION &);
	void move();
	bool is_alive();
	bool not_there(const int x, const int y);
	inline int get_x();
	inline int get_y();
};


#endif // !SNAKE_H
