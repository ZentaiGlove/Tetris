#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

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
	void down();//�½�

	void move_left_right(int offset);//������

	void rotate();//��ת

	//���Ʒ���
	void draw(int left_margin, int top_margin);

	static IMAGE** get_images();

	//��ֵ���캯��
	Block& operator=(const Block& other);

	//�жϵ�ǰ�����Ƿ��ڵ�ͼ��
	bool block_in_map(const vector<vector<int>>& map);

	void stop(vector<vector<int>>& map);
	//Point* get_small_blocks();

private:
	int block_tpye;// ��������
	Point small_blocks[4];
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

