#pragma once
#include <graphics.h>
struct Point // 小方块的位置
{
	int row;
	int col;
};

class Block
{
public:
	Block();

	//操作
	void drop();//下降

	void move_left();//左移

	void move_right();//右移

	void rotate();//旋转

	//绘制方块
	void draw(int left_margin, int top_margin);

private:
	int block_tpye;// 方块类型
	Point small_blocks[4];
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

