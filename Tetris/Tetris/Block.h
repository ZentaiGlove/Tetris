#pragma once
#include <graphics.h>
struct Point // С�����λ��
{
	int row;
	int col;
};

class Block
{
public:
	Block();

	//����
	void drop();//�½�

	void move_left();//����

	void move_right();//����

	void rotate();//��ת

	//���Ʒ���
	void draw(int left_margin, int top_margin);

private:
	int block_tpye;// ��������
	Point small_blocks[4];
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

