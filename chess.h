#pragma once
#include <vector>
#include "game.h"

//	棋盘的大小
static const int Chess_H = 13;
static const int Chess_W = 5;
const char blank = ' ';
const char RANK[10] = "AJSVTYLPG";//吃子排序

#define SAME_RANK 0
#define ABOVE 1
#define UNDER -1

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

	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	std::vector<Movement>  Search_Movement(const int& State);
	Chess Apply_Move(const Movement& V);
	void Display();
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

