#pragma once
#include <graphics.h>
#include <vector>
#include "Block.h"
using namespace std;
class Tetris
{
public:
	//构造函数，行，列，左侧距离，上侧距离
	Tetris(int rows, int cols, int left, int top, int block_size);

	//初始化
	void init();

	//开始游戏
	void play();

private:
	//接收用户输入
	void key_event();

	//渲染游戏窗口
	void update_window();

	//返回距离上次调用该函数，间隔多少时间（ms）
	//第一次调用该函数，返回0
	int get_delay();

	//下落
	void drop();

	//清行
	void clear_line();
	
	//左右移动
	void move(int offset);

private:
	int delay;//延时（下降速度）
	bool update;//是否更新

	//背景地图
	//0：表示没有方块
	//5：表示第5中方块
	vector<vector<int>> map;
	int rows, cols, left_margin, top_margin;
	int block_size;
	IMAGE img_bg;

	Block* curBlock; // 当前方块
	Block* nextBlock; // 预告方块
	Block bakBlock; // 当前方块降落过程中，用来备份上一个合法位置

};

