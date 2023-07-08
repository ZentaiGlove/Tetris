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
	this->rows = rows; // ���ڸ߶�
	this->cols = cols; // ���ڿ��
	this->left_margin = left; // ��ʼ�����λ�þ�����߽�ľ���
	this->top_margin = top; // ��ʼ�����λ�þ����ϱ߽�ľ���
	this->block_size = block_size; // �����С

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

	//�����������
	srand(time(NULL));

	//������Ϸ����
	initgraph(938, 896);

	//���ر���ͼƬ
	loadimage(&img_bg, "res/bg2.png");

	//��ʼ����Ϸ����
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
		//�����û�����
		key_event();

		//ͳ����ʱ
		timer += get_delay();

		if (timer > delay) {
			timer = 0;
			drop();
			update = true;
		}

		if (update)
		{
			update = false;
			//������Ϸ����
			update_window();

			//������Ϸ�������
			clear_line();
		}
		
	}


}

void Tetris::key_event()
{
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;
	//��ȡ�û�����,��һ��ֱ�����룬���ð��س�
	//if(_kbhit())
	//{
	//	ch = _getch();

	//	//������·�������᷵�������ַ�
	//	//������¡������Ⱥ󷵻� 224��72
	//	//������¡������Ⱥ󷵻� 224��80
	//	//������¡������Ⱥ󷵻� 224��75
	//	//������¡������Ⱥ󷵻� 224��77
	//	if (ch == 224) 
	//	{
	//		ch = _getch();
	//		switch (ch)
	//		{
	//		case 72: // ������ת
	//			rotateFlag = true;
	//			break;
	//		case 80: // ������׹
	//			delay = SPEED_FAST;
	//			break;
	//		case 75: // ��������
	//			dx = -1;
	//			break;
	//		case 77: // ��������
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

	//if (rotateFlag) // ��ת
	//{
	//	curBlock->rotate();
	//}

	if (dx != 0) // �����ƶ�
	{
		move(dx);
		update = true;
	}

}

void Tetris::update_window()
{
	//���Ʊ���ͼƬ
	putimage(0, 0, &img_bg);

	//���Ի�����
	/*
	Block block;
	block.draw(263,133);
	*/

	//���䵽�ײ��ķ�����Ⱦ
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

	//��ʾ��ǰ�������һ������
	curBlock->draw(left_margin, top_margin);
	nextBlock->draw(689, 150);
}

//��һ�ε���ʱ����0�����淵�ؾ�����һ�ε��ã��������ms
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
		//����ͣ��
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
