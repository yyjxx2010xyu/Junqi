#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include "game.h"
#include "connect.h"
#include "cmd_console_tools.h"

//	棋盘的大小
static const int Chess_H = 13;
static const int Chess_W = 5;

class Movement;
class Coord;
class Connect;
extern const int ROLE_BLANK;
extern const int ROLE_LOWER;
extern const int ROLE_UPPER;

//等级判断需要
const char RANK[] = "AJSVTYLPGF";
const char BLANK = ' ';

#define UNDER -1
#define ABOVE 1
#define SAME_RANK 0

enum class PlayerType;

/*
存储方式就与Word中一样，上面用大写，下面用小写。
*/
class Chess
{
private:
	std::vector<std::vector<char> >  Board;
	int Rank_Judgement(char a, char b);
public:
	Chess()
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++)
			Board[i].resize(Chess_W);
	}
	Chess(std::vector<std::vector<char> >  board_data)
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++) {
			Board[i].resize(Chess_W);
			Board[i] = board_data[i];
		}
	}
	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	int Evaluater(const int x, const int y, const char ch);
	std::vector<Movement>  Search_Movement(const int& State, PlayerType Player);
	Chess Apply_Move(const Movement& V);
	void Display();
	bool Is_Movable(Movement M);
	void Set_Board(int x, int y, int ch);
	void BFSSearch(int x, int y, std::vector<Coord>& Pos);
	int Selector(Chess chess, const int& Role, Movement M);
	std::vector<Movement> SelectMoveMent(std::vector <Movement> M, const int& Role, PlayerType Player);
};

const int frontEndPos = 7;	//	前线位置
//	返回棋盘相应位置的颜色
inline int isColor(int linePos);
//	画棋盘
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor);
//	画棋子
inline void Display_Chess(std::vector<std::vector<char> >  Board, class Coord sizeofall, bool border, bool display);


//	铁路位置
const int Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{2, 1, 2, 1, 2},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{2, 1, 3, 1, 2},
	{1, 0, 1, 0, 1},
	{2, 1, 3, 1, 2},
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
