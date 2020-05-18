#pragma once
#include <iostream>
#include "chess.h"
#include "game.h"

typedef unsigned long long ull;

//	看网上说可以用2^n做Table_Size，可以位运算加速，但是我觉得不靠谱，Hash的Mod还是素数好
const int Table_Size = 1000003;

class Chess;
class Movement;
class Zobrist
{
private:
	ull Zobrist_Table[13][5][12 * 2 + 1];
	mutable int* Hash_Table;
public:
	Zobrist();
	~Zobrist();
	ull Add_Piece(ull Chess, int x, int y, char Piece) const ;
	ull Remove_Piece(ull Chess, int x, int y, char Piece) const ;
	void Record_State(ull Chess, int Eval) const;
	int Search_State(ull Chess) const;
	ull Evaluate_Chess(Chess C) const;
	ull Apply_Move(const Chess& C,const Movement& V, const ull& Zob) const;
};