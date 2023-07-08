#include "Tetris.h"
#include "Block.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <windows.h>

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

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

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
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;
	//获取用户输入,按一次直接输入，不用按回车
	//if(_kbhit())
	//{
	//	ch = _getch();

	//	//如果按下方向键，会返回两个字符
	//	//如果按下↑，会先后返回 224，72
	//	//如果按下↓，会先后返回 224，80
	//	//如果按下←，会先后返回 224，75
	//	//如果按下→，会先后返回 224，77
	//	if (ch == 224) 
	//	{
	//		ch = _getch();
	//		switch (ch)
	//		{
	//		case 72: // ↑：旋转
	//			rotateFlag = true;
	//			break;
	//		case 80: // ↓：下坠
	//			delay = SPEED_FAST;
	//			break;
	//		case 75: // ←：左移
	//			dx = -1;
	//			break;
	//		case 77: // →：右移
	//			dx = 1;
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	if (GetAsyncKeyState(VK_UP))
	{
		rotateFlag = true;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		delay = SPEED_FAST;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		dx = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dx = 1;
	}

	//if (rotateFlag) // 旋转
	//{
	//	curBlock->rotate();
	//}

	if (dx != 0) // 左右移动
	{
		move(dx);
		update = true;
	}

}

void Tetris::update_window()
{
	//绘制背景图片
	putimage(0, 0, &img_bg);

	//测试画方块
	/*
	Block block;
	block.draw(263,133);
	*/

	//降落到底部的方块渲染
	IMAGE** imgs = Block::get_images();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] != 0)
			{
				int x = j * block_size + left_margin;
				int y = i * block_size + top_margin;
				putimage(x, y, imgs[map[i][j]-1]);
			}
		}
	}

	//显示当前方块和下一个方块
	curBlock->draw(left_margin, top_margin);
	nextBlock->draw(689, 150);
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
	bakBlock = *curBlock;
	curBlock->down();

	if (!curBlock->block_in_map(map))
	{
		//方块停下
		bakBlock.stop(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	delay = SPEED_NORMAL;
}

void Tetris::clear_line()
{

}

void Tetris::move(int offset)
{
	bakBlock = *curBlock;
	curBlock->move_left_right(offset);

	if (curBlock->block_in_map(map))
	{
		*curBlock = bakBlock;
	}
}
