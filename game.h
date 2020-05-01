#pragma once
#include <vector>

/*
State状态	
STATE_END	表示当前棋盘结束
STATE_UPPER	当前执子方为上部，棋盘数据中的大写部分
STATE_LOWER	当前执子方为下部，期盼数据中的小写部分
*/
const int STATE_END = -1;
const int STATE_UPPER = 1;
const int STATE_LOWER = 0;

//	用于初始化的最大值
const int INF = 0x3f3f3f3f;

//	棋子坐标
class Coord
{
public:
	int x, y;
};

/*	
棋子的移动路径
Coord From	表示棋子的起始位置
Coord To	表示棋子的终点位置
*/
class Movement
{
public:
	Coord From, To;
};


/*
_Search函数的返回值
Eval		估值
Move_His	移动路径
*/
class Search_Returns
{
public:
	int Eval;
	std::vector<Movement> Move_His;
	Search_Returns(int _Eval, std::vector<Movement> _Move_His): Eval(_Eval), Move_His(_Move_His) {}
};

//	棋盘的大小
static const int Chess_H = 13;
static const int Chess_W = 5;

/*
存储方式就与Word中一样，上面用大写，下面用小写。
*/
class Chess
{
public:
	std::vector<std::vector<char> >  Board;

	Chess()
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++)
			Board[i].resize(Chess_W);
	}
	
	void Display();
};

//	在minmax搜索中的玩家类型
enum class PlayerType {
	MaximizingPlayer,
	MinimizingPlayer
};

class Game
{
protected:
	Chess Board;
	int State;
public:
	Game(Chess _Board, int _State);
	Movement Search(int depth = 5);
private:
	Search_Returns _Search(Chess Cur_Board, int depth, int alpha, int beta, PlayerType Player, int State);
	bool Is_Over(const Chess& Cur_Board, const int& State);
	int Evaluate_Chess(const Chess& Cur_Board);
	std::vector<Movement> Search_Movement(const Chess& Board, const int& State);
	Chess Apply_Move(const Chess& Cur_Board, const Movement& V);
};




//	铁路位置
const int Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0}
};

//	司令*1、军长*1、师长*2、旅长*2、团长*2、营长*2、连长*3、排长*3、工兵*3、地雷*3、炸弹*2、军棋*1。 共25枚

