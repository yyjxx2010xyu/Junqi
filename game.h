#pragma once
#include <vector>
#include "chess.h"

/*
State状态	
STATE_END	表示当前棋盘结束
STATE_UPPER	当前执子方为上部，棋盘数据中的大写部分
STATE_LOWER	当前执子方为下部，期盼数据中的小写部分
*/
const int STATUS_END = -1;
const int STATUS_OK = 0;

/*
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方
*/
const int ROLE_UPPER = 1;
const int ROLE_LOWER = 0;



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


//	在minmax搜索中的玩家类型
enum class PlayerType {
	MaximizingPlayer,
	MinimizingPlayer
};

//	Return of function "_Search"
typedef std::pair<int, std::vector<Movement> > Eval_Move;

/*
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方

Time_Limit	时间限制
	目前还没加以限制。
*/

class Game
{
protected:
	int Role;
	int Time_Limit;
public:
	void Arg_Init(int argc, char * argv[]);
	Movement Search(Chess Board, int Depth = 5);
private:
	Eval_Move _Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_State);

};
