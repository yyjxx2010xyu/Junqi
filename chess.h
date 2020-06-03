#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cassert>
#include "game.h"
#include "connect.h"
#include "cmd_console_tools.h"
//用于棋盘权重，执棋方在棋盘上方为UP，在下方为DOWN
#define UP 0
#define DOWN 1
static bool Upper_Role = DOWN;
static bool Lower_Role = UP;

//	棋盘的大小
static const int Chess_H = 13;
static const int Chess_W = 5;
static const int Chess_Type = 12;

const int Chess_board[2][Chess_H] = {
	{0,0,0,0,0,0,0,1,1,2,2,3,3},
	{3,3,2,2,1,1,0,0,0,0,0,0,0}
};

class Movement;
class Coord;
class Connect;
extern const int ROLE_BLANK;
extern const int ROLE_LOWER;
extern const int ROLE_UPPER;

//等级判断需要
const char RANK[] = "AJSVTYLPGF";
const char BLANK = ' ';
static int Chess_Value['z' + 1] = { 0 };
#define UNDER -1
#define ABOVE 1
#define SAME_RANK 0

const int Value_G = 110;
const int Value_P = 120;
const int Value_L = 250;
const int Value_Y = 520;
const int Value_T = 1080;
const int Value_V = 2200;
const int Value_S = 4500;
const int Value_J = 9600;
const int Value_A = 20000;
const int Value_F = 204800;
const int Value_Z = 3600;
const int Value_D = 4000;
const int Value_B = 0;//BLANK




enum class PlayerType;


//	用于标记在棋盘的上方还是下方,0为大本营在上方，1为大本营在下方
//	用于比较大小
int Rank_Judgement(char a, char b);

/*
存储方式就与Word中一样，上面用大写，下面用小写。
*/
class Chess
{
private:
	char Board[Chess_H][Chess_W];
public:
	Chess()
	{
		memset(Board, 0, sizeof(char) * Chess_H * Chess_W);
	}
	Chess(const Chess& board_data)
	{
		memcpy(Board, board_data.Board, sizeof(char) * Chess_H * Chess_W);
	}
	Chess(const char board_data[][Chess_W])
	{
		memcpy(Board, board_data, sizeof(char) * Chess_H * Chess_W);
	}

	void init();//初始化棋盘位置，确认大小写在棋盘的位置
	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	int Evaluater(const int x, const int y, const char ch);
	std::vector<Movement>  Search_Movement(const int& State, PlayerType Player, const int Search_Width);
	Chess Apply_Move(const Movement& V);
	void Display();
	bool Is_Movable(Movement M);
	void Set_Board(int x, int y, int ch);
	void BFSSearch(int x, int y, std::vector<Coord>& Pos, const int& Role);
	char Get_Piece(int x, int y) const;
	void Set_Piece(int x, int y, char z);
	int Evaluater_Origin(const int x, const int y, const char ch);
	std::vector<Movement> SelectMoveMent(std::vector <Movement> M, const int& Role, PlayerType Player, const int Search_Width);
	friend static int Selector(Chess& chess, const int& Role, Movement M);
	friend class Zobrist;

	friend bool operator == (const Chess& A, const Chess& B);
	friend void Display_Chess(const char Board[][Chess_W], class Coord sizeofall, bool border, bool display);
};

const int frontEndPos = 7;	//	前线位置
//	返回棋盘相应位置的颜色
inline int isColor(int linePos, char ch);
//	画棋盘
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor);
//	画棋子
inline void Display_Chess(const char Board[][Chess_W], class Coord sizeofall, bool border, bool display);

//军旗位置
static int FlagPos[2][Chess_H][Chess_W] = { 0 };
//	铁路位置
const int Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{2, 1, 2, 1, 2},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{3, 1, 2, 1, 3},
	{1, 0, 1, 0, 1},
	{3, 1, 2, 1, 3},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{2, 1, 1, 1, 2},
	{0, 0, 0, 0, 0}
};

//	行营位置
const bool Station[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
};

// 不可侧向移动的位置
const bool SpecialPos[Chess_H][Chess_W]{
	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1}
};
//	上下左右四个方向
const int HV_DirectX[4] = { 1,0,0,-1 };
const int HV_DirectY[4] = { 0,1,-1,0 };

//	对角方向
const int Cross_DirectX[4] = { 1,1,-1,-1 };
const int Cross_DirectY[4] = { 1,-1,1,-1 };


//	公路位置
//	公路联通种类
enum class HighwayConn { full, half, none };

//	路线联通种类
enum class ConnWay { Railway, Highway, none };


//	司令*1、军长*1、师长*2、旅长*2、团长*2、营长*2、连长*3、排长*3、工兵*3、地雷*3、炸弹*2、军棋*1。 共25枚
const int chessClassNum = 12;
enum class chessClass { none, zhadan, dilei, junqi, gongbing, pai, lian, ying, tuan, lv, shi, jun, siling };


//	字符

const std::map<char, chessClass> chessMap{
	{BLANK,chessClass::none},
	{'a',chessClass::siling},
	{'A',chessClass::siling},
	{'j',chessClass::jun},
	{'J',chessClass::jun},
	{'s',chessClass::shi},
	{'S',chessClass::shi},
	{'v',chessClass::lv},
	{'V',chessClass::lv},
	{'t',chessClass::tuan},
	{'T',chessClass::tuan},
	{'y',chessClass::ying},
	{'Y',chessClass::ying},
	{'l',chessClass::lian},
	{'L',chessClass::lian},
	{'p',chessClass::pai},
	{'P',chessClass::pai},
	{'g',chessClass::gongbing},
	{'G',chessClass::gongbing},
	{'d',chessClass::dilei},
	{'D',chessClass::dilei},
	{'z',chessClass::zhadan},
	{'Z',chessClass::zhadan},
	{'f',chessClass::junqi},
	{'F',chessClass::junqi}
};


const std::map<char, int> chessNum{
	{BLANK,0},
	{'a',1},
	{'A',2},
	{'j',3},
	{'J',4},
	{'s',5},
	{'S',6},
	{'v',7},
	{'V',8},
	{'t',9},
	{'T',10},
	{'y',11},
	{'Y',12},
	{'l',13},
	{'L',14},
	{'p',15},
	{'P',16},
	{'g',17},
	{'G',18},
	{'d',19},
	{'D',20},
	{'z',21},
	{'Z',22},
	{'f',23},
	{'F',24}
};





//	棋盘格子种类
enum class BoardClass {
	camp,		//	普通军营
	frontline,		//	前线
	station,		//	行营
	headquarter,		//	大本营
	empty,		//	不可走区域，楚河汉界之类
};

//	棋盘布置
const int Field[Chess_H][Chess_W] = {
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::frontline, (int)BoardClass::empty,(int)BoardClass::frontline,(int)BoardClass::empty,(int)BoardClass::frontline},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp}
};
