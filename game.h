#pragma once
#include <vector>
#include "chess.h"
#include "zobrist.h"
#define DEBUG





/*
State状态
STATE_END	表示当前棋盘结束
STATE_UPPER	当前执子方为上部，棋盘数据中的大写部分
STATE_LOWER	当前执子方为下部，期盼数据中的小写部分
*/
const int STATUS_END = -1;
const int STATUS_OK = 0;
const int STATUS_AFTER = 1;


const int SEARCH_DEC = 4;
typedef unsigned long long ull;

//	搜索宽度
const int SEARCH_WIDTH = 36;
//	搜索深度
const int SEARCH_DEPTH = 8;
/*
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方
*/
//	const int ROLE_UPPER = 1;
//	const int ROLE_LOWER = 0;
//	const int ROLE_BLANK = -1;
extern const int ROLE_UPPER;
extern const int ROLE_LOWER;


//	用于初始化的最大值
const int INF = 0x3f3f3f3f;


//	棋子坐标
class Coord
{
public:
	int x, y;
	Coord(int _x = 0, int _y = 0) :x(_x), y(_y) {}
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
	Movement(Coord _From = (0, 0), Coord _To = (0, 0)) :From(_From), To(_To) {}
};


//	在minmax搜索中的玩家类型
enum class PlayerType {
	MaximizingPlayer,
	MinimizingPlayer
};

//	Return of function "_Search"
typedef std::pair<int, Movement> Eval_Move;

/*
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方

Time_Limit	时间限制
	目前还没加以限制。
*/

class Chess;
class Zobrist;
class Game
{
protected:
	int Role;
	int Time_Limit;
public:
	void Arg_Init(int argc, char* argv[]);
	Movement Search(Chess Board, int Depth);
private:
	Eval_Move _Search(Chess& Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_State, int Search_Width);
};
