#include "Block.h"
#include <stdlib.h>

IMAGE* Block::imgs[7] = { NULL, };
int Block::size = 36;

Block::Block()
{
	if (imgs[0] == NULL)
	{
		//���뷽��ͼƬ
		IMAGE img_tmp;
		loadimage(&img_tmp, "res/tiles.png");

		SetWorkingImage(&img_tmp);
		//�и��ͼƬ
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage(); // �ָ�������
	}

	//7�ַ���
	int blocks[7][4] = 
	{
		1,3,5,7, // I
		2,4,5,7, // Z 1
		3,5,4,6, // Z 2
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // ��
	};

	//�������һ�ַ���
	block_tpye = 1 + rand() % 7;

	//��ʼ��small_blocks���ʼ�ĸ�С�����λ��
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[block_tpye - 1][i];
		small_blocks[i].row = value / 2;
		small_blocks[i].col = value % 2;
	}

	img = imgs[block_tpye - 1];
}

void Block::drop()
{

}

void Block::move_left()
{

}

void Block::move_right()
{

}

void Block::rotate()
{

}

void Block::draw(int left_margin, int top_margin)
{
	for (int i = 0; i < 4; i++)
	{
		//��ȡС�����λ��
		int x = left_margin + small_blocks[i].col * size;
		int y = top_margin + small_blocks[i].row * size;

		//����С����
		putimage(x, y, img);
	}
}
