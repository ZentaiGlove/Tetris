#include "Block.h"
#include <stdlib.h>
using namespace std;

IMAGE* Block::imgs[7] = { NULL, };
int Block::size = 36;

Block::Block()
{
	if (imgs[0] == NULL)
	{
		//载入方块图片
		IMAGE img_tmp;
		loadimage(&img_tmp, "res/tiles.png");

		SetWorkingImage(&img_tmp);
		//切割方块图片
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage(); // 恢复工作区
	}

	//7种方块
	int blocks[7][4] = 
	{
		1,3,5,7, // I
		2,4,5,7, // Z 1
		3,5,4,6, // Z 2
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};

	//随机生成一种方块
	block_tpye = 1 + rand() % 7;

	//初始化small_blocks，最开始四个小方块的位置
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[block_tpye - 1][i];
		small_blocks[i].row = value / 2;
		small_blocks[i].col = value % 2;
	}

	img = imgs[block_tpye - 1];
}

void Block::down()
{
	/*for (int i = 0; i < 4; i++)
	{
		Block::small_blocks[i].row++;
	}*/

	//与上方是等价写法
	for (auto& block : small_blocks)
	{
		block.row++;
	}
}

void Block::move_left_right(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		small_blocks[i].col += offset;
	}
}


void Block::rotate()
{

}

void Block::draw(int left_margin, int top_margin)
{
	for (int i = 0; i < 4; i++)
	{
		//获取小方块的位置
		int x = left_margin + small_blocks[i].col * size;
		int y = top_margin + small_blocks[i].row * size;

		//绘制小方块
		putimage(x, y, img);
	}
}

IMAGE** Block::get_images()
{
	return imgs;
}

//赋值构造函数
Block& Block::operator=(const Block& other)
{
	if (this == &other) return *this;
	
	this->block_tpye = other.block_tpye;

	for (int i = 0; i < 4; i++)
	{
		this->small_blocks[i] = other.small_blocks[i];
	}

	return *this;
}

//判断当前方块是否在地图内
bool Block::block_in_map(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++) {
		if (small_blocks[i].col < 0 
			|| small_blocks[i].col >= cols
			|| small_blocks[i].row < 0
			|| small_blocks[i].row >= rows
			|| map[small_blocks[i].row][small_blocks[i].col] != 0)
		{
			return false;
		}
	}
	return true;
}

void Block::stop(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++)
	{
		map[small_blocks[i].row][small_blocks[i].col] = block_tpye;
	}
}
