#include "Tetris.h"
#include "Block.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

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
	update = true;
}

void Tetris::update_window()
{
	//���Ʊ���ͼƬ
	putimage(0, 0, &img_bg);

	//������
	Block block;
	block.draw(263,133);
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

}

void Tetris::clear_line()
{

}
