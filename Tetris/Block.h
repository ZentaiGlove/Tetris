#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

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
	void down();//下降

	void move_left_right(int offset);//左右移

	void rotate();//旋转

	//绘制方块
	void draw(int left_margin, int top_margin);

	static IMAGE** get_images();

	//赋值构造函数
	Block& operator=(const Block& other);

	//判断当前方块是否在地图内
	bool block_in_map(const vector<vector<int>>& map);

	void stop(vector<vector<int>>& map);
	//Point* get_small_blocks();

private:
	int block_tpye;// 方块类型
	Point small_blocks[4];
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

