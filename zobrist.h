#pragma once
#include <iostream>
#include "chess.h"
#include "game.h"

typedef unsigned long long ull;

//	看网上说可以用2^n做Table_Size，可以位运算加速，但是我觉得不靠谱，Hash的Mod还是素数好
const ull Table_Size = 1000000037;

const int HASH_BETA = 0;
const int HASH_ALPHA = 1;
const int HASH_EXACT = 2;

class Chess;
class Movement;
class Zobrist
{
private:
	ull Zobrist_Table[13][5][12 * 2 + 1];
	mutable int* Hash_Table;
	mutable int* Hash_Depth;
	mutable int* Hash_Flag;

	ull Verified_Table[13][5][12 * 2 + 1];
	mutable int* Hash_Verified;
public:
	Zobrist();
	~Zobrist();
	ull Add_Piece(ull Chess, int x, int y, char Piece) const;
	ull Remove_Piece(ull Chess, int x, int y, char Piece) const;
	void Record_State(ull Zob_Num, int Eval, int Depth, int Flag) const;
	int Search_State(ull Chess, int Depth, int Alpha, int Beta) const;
	ull Evaluate_Chess(Chess C) const;
	ull Apply_Move(const Chess& C, const Movement& V, const ull& Zob) const;
	bool Same_Role(ull Chess, int Depth) const;
	int Get_Depth(ull Chess) const;
	void Clear_Depth() const;
	void Check() const;
	void _Check(int Depth) const;
};
