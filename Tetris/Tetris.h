#pragma once
#include <graphics.h>
#include <vector>
#include "Block.h"
using namespace std;
class Tetris
{
public:
	//���캯�����У��У������룬�ϲ����
	Tetris(int rows, int cols, int left, int top, int block_size);

	//��ʼ��
	void init();

	//��ʼ��Ϸ
	void play();

private:
	//�����û�����
	void key_event();

	//��Ⱦ��Ϸ����
	void update_window();

	//���ؾ����ϴε��øú������������ʱ�䣨ms��
	//��һ�ε��øú���������0
	int get_delay();

	//����
	void drop();

	//����
	void clear_line();
	
	//�����ƶ�
	void move(int offset);

private:
	int delay;//��ʱ���½��ٶȣ�
	bool update;//�Ƿ����

	//������ͼ
	//0����ʾû�з���
	//5����ʾ��5�з���
	vector<vector<int>> map;
	int rows, cols, left_margin, top_margin;
	int block_size;
	IMAGE img_bg;

	Block* curBlock; // ��ǰ����
	Block* nextBlock; // Ԥ�淽��
	Block bakBlock; // ��ǰ���齵������У�����������һ���Ϸ�λ��

};

