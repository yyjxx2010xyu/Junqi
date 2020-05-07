#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include "game.h"
#include "cmd_console_tools.h"

//	棋盘的大小
static const int Chess_H = 13;
static const int Chess_W = 5;
const char blank = ' ';
const char RANK[10] = "AJSVTYLPG";//吃子排序

#define SAME_RANK 0
#define ABOVE 1
#define UNDER -1

class Movement;
class Coord;
extern const int ROLE_BLANK;
extern const int ROLE_LOWER;
extern const int ROLE_UPPER;

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
	std::vector<Movement>  Search_Movement(const int& State);
	Chess Apply_Move(const Movement& V);
	void Display();
};


//	inline 函数

const int frontEndPos = 7;	//	前线位置
//	将对应的数字转换成其他占位符（'*'）
inline void TransChessBoard(std::vector<std::vector<char> >& BoardData);
//	返回棋盘相应位置的颜色
inline int isColor(int linePos);
//	画棋盘
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor);
//	画棋子
inline void Display_Chess(std::vector<std::vector<char> >  Board, class Coord sizeofall, bool border, bool display);



//	棋盘格子种类
enum class BoardClass { camp, frontline, station, headquarter, empty };

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

//	公路位置
//	公路联通种类
enum class HighwayConn { full, half, none };

//	路线联通种类
enum class ConnWay { Railway, Highway, none };


//	司令*1、军长*1、师长*2、旅长*2、团长*2、营长*2、连长*3、排长*3、工兵*3、地雷*3、炸弹*2、军棋*1。 共25枚
const int chessClassNum = 12;
enum class chessClass { none, zhadan, dilei, junqi, gongbing, pai, lian, ying, tuan, lv, shi, jun, siling };
const char placeholder = '*';

const std::vector<std::pair<char, chessClass>> chessPiece({
	std::make_pair(placeholder,chessClass::none),
	std::make_pair('a',chessClass::siling),		std::make_pair('A',chessClass::siling),
	std::make_pair('j',chessClass::jun),		std::make_pair('J',chessClass::jun),
	std::make_pair('s',chessClass::shi),		std::make_pair('S',chessClass::shi),
	std::make_pair('v',chessClass::lv),			std::make_pair('V',chessClass::lv),
	std::make_pair('t',chessClass::tuan),		std::make_pair('T',chessClass::tuan),
	std::make_pair('y',chessClass::ying),		std::make_pair('Y',chessClass::ying),
	std::make_pair('l',chessClass::lian),		std::make_pair('L',chessClass::lian),
	std::make_pair('p',chessClass::pai),		std::make_pair('P',chessClass::pai),
	std::make_pair('g',chessClass::gongbing),	std::make_pair('G',chessClass::gongbing),
	std::make_pair('d',chessClass::dilei),		std::make_pair('D',chessClass::dilei),
	std::make_pair('z',chessClass::zhadan),		std::make_pair('Z',chessClass::zhadan),
	std::make_pair('f',chessClass::junqi),		std::make_pair('F',chessClass::junqi),
	});

//	None表示棋子移动不符合规律
//	Equal表示同归于尽
enum class AttackResult { None, Bigger, Smaller, Equal };

class Piece {
private:
	chessClass id;
	int role;
public:
	Piece(chessClass id = chessClass::none, int role = ROLE_BLANK) :id(id),role(role)  {}
	Piece(const char ch);						//	need implementation
	chessClass getId() const { return this->id; }
	int getRole() const { return this->role; }
	char getchessClass() const;					//	need implementation
	AttackResult attack(const Piece& target);	//	need implementation
	bool operator == (const Piece& right) const { return (this->id == right.id); }
	bool operator != (const Piece& right) const { return !(*this == right); }
	Piece& operator = (const Piece& right) { this->id = right.id; this->role = right.role;  return *this; }
	friend std::ostream& operator<<(std::ostream& o, Piece& p) { o << p.getchessClass(); return o; }
};


class PieceCeil {
private:
	Piece p;
	int x, y;	//	行, 列
public:
	PieceCeil(Piece piece = chessClass::none, int x = 0, int y = 0):p(piece),x(x),y(y) {}
	int getX() { return this->x; }
	int getY() { return this->y; }
	Piece getPiece() { return this->p; }
	friend std::ostream& operator<<(std::ostream& o, PieceCeil& pc) { o << pc.p << pc.x << pc.y; return o; }
	bool isValidCeil() { return this->x >= 0 && this->x < Chess_H&& this->y >= 0 && this->y < Chess_W; }
	ConnWay isConnPieceCeil(PieceCeil& ceil);
	bool isSameRolePiece(PieceCeil& ceil) { return this->p.getRole() == ceil.p.getRole(); }
};

class PieceBoard {
private:
	PieceCeil pieceboard[Chess_H][Chess_W];
public:
	PieceBoard(std::vector<std::vector<char> >  BoardData) {
		for (unsigned i = 0; i < BoardData.size(); i++)
			for (unsigned j = 0; j < BoardData[i].size(); j++)
				pieceboard[i][j] = PieceCeil(Piece(BoardData[i][j]), i, j);
	}
	PieceCeil& getCeil(int x, int y) { return this->pieceboard[x][y]; }
	//	PieceCeil& getCeil(Coord ceil) { return this->pieceboard[ceil.x][ceil.y]; }
	std::vector<PieceCeil> get4NearestCeil(PieceCeil cur);		//	其他兵种搜索算法
	std::vector<PieceCeil> getBFSCeil(PieceCeil cur);			//	工兵搜索算法
};

const int Direction[][2] = { {1,0},{0,1},{-1,0},{0,-1} };
const int FullDirection[][2] = { {1,0},{0,1},{-1,0},{0,-1},{1,1,},{1,-1},{-1,1},{-1,-1} };
//	const Coord p = { 0,0 };