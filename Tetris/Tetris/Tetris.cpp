#include "Tetris.h"
#include "Block.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

const int SPEED_NORMAL = 500;
const int SPEED_FAST = 50;

Tetris::Tetris(int rows, int cols, int left, int top, int block_size)
{
	this->rows = rows; // 窗口高度
	this->cols = cols; // 窗口宽度
	this->left_margin = left; // 初始方块的位置距离左边界的距离
	this->top_margin = top; // 初始方块的位置距离上边界的距离
	this->block_size = block_size; // 方块大小

	for (int i = 0; i < rows; i++)
	{
		vector<int> map_row;
		for (int j = 0; j < cols; j++)
		{
			map_row.push_back(0);
		}
		map.push_back(map_row);
	}
}

void Tetris::init()
{
	delay = SPEED_NORMAL;

	//配置随机种子
	srand(time(NULL));

	//创建游戏窗口
	initgraph(938, 896);

	//加载背景图片
	loadimage(&img_bg, "res/bg2.png");

	//初始化游戏数据
	char data[20][10];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}

}

void Tetris::play()
{
	init();

	int timer = 0;

	while (1) 
	{
		//接收用户输入
		key_event();

		//统计延时
		timer += get_delay();

		if (timer > delay) {
			timer = 0;
			drop();
			update = true;
		}

		if (update)
		{
			update = false;
			//更新游戏画面
			update_window();

			//更新游戏相关数据
			clear_line();
		}
		
	}


}

void Tetris::key_event()
{
	update = true;
}

void Tetris::update_window()
{
	//绘制背景图片
	putimage(0, 0, &img_bg);

	//画方块
	Block block;
	block.draw(263,133);
}

//第一次调用时返回0，后面返回距离上一次调用，间隔多少ms
int Tetris::get_delay()
{
	static unsigned long long last_time = 0;
	unsigned long long current_time = GetTickCount();

	if (last_time == 0)
	{
		last_time = current_time;
		return 0;
	}
	else
	{
		int ret = current_time - last_time;
		last_time = current_time;
		return ret;
	}
}

void Tetris::drop()
{

}

void Tetris::clear_line()
{

}
