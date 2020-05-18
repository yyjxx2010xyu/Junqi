#include <cassert>
#include <map>
#include "zobrist.h"
#include "chess.h"
#include "game.h"


//	生成unsigned long long 大小的随机数
static ull Rand_ULL()
{
	return ((((ull)rand()) & 0x0000000000007FFFull) |
		(((ull)rand() << 15) & 0x000000003FFF8000ull) |
		(((ull)rand() << 30) & 0x00001FFFC0000000ull) |
		(((ull)rand() << 45) & 0x07FFF00000000000ull) |
		(((ull)rand() << 60) & 0xF800000000000000ull)
		);
}

//	生成函数	初始化每个位置的不同棋子的权重，初始化Hash表
Zobrist::Zobrist()
{
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			for (int k = 0; k < Chess_Type * 2 + 1; k++)
				Zobrist_Table[i][j][k] = Rand_ULL();
	Hash_Table = new int[Table_Size];
	memset(Hash_Table, -1, sizeof(Hash_Table[0]) * Table_Size);
	Hash_Depth = new int[Table_Size];
	memset(Hash_Depth, -1, sizeof(Hash_Depth[0]) * Table_Size);
	Hash_Bool = new bool[Table_Size];
	memset(Hash_Bool, 0, sizeof(Hash_Bool[0]) * Table_Size);
}

Zobrist::~Zobrist()
{
	delete[] Hash_Table;
}

//	表中的一个位置添加一个棋子
ull Zobrist::Add_Piece(ull Chess, int x, int y, char Piece) const
{
	return Chess ^ Zobrist_Table[x][y][chessNum.at(Piece)];
}

//	表中的一个位置去掉一个棋子
ull Zobrist::Remove_Piece(ull Chess, int x, int y, char Piece) const
{
	return Chess ^ Zobrist_Table[x][y][chessNum.at(Piece)];
}

//	记录状态的Eval
void Zobrist::Record_State(ull Chess, int Eval, int Depth) const
{
	
	Hash_Bool[Chess % Table_Size] = true;
	if (Hash_Depth[Chess % Table_Size] <= Depth)
	{
		Hash_Depth[Chess % Table_Size] = Depth;
		Hash_Table[Chess % Table_Size] = Eval;
	}
}

//	查询状态的Eval
int Zobrist::Search_State(ull Chess, int Depth) const
{
	if (Hash_Bool[Chess % Table_Size] == false || Hash_Depth[Chess % Table_Size] < Depth)
		return -1;
	return Hash_Table[Chess % Table_Size];
}

ull Zobrist::Evaluate_Chess(Chess C) const
{
	ull Ret = 0;
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			Ret = Add_Piece(Ret, i, j, C.Board[i][j]);
	return Ret;
}

ull Zobrist::Apply_Move(const Chess& C, const Movement& V, const ull& Zob) const
{

	ull Ret = Zob;
	int result = Rank_Judgement(C.Board[V.To.x][V.To.y], C.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK)
	{
		Ret = Remove_Piece(Zob, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.To.x, V.To.y, BLANK);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}
	if (result == ABOVE)
	{

		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}
	if (result == UNDER)
	{
		Ret = Remove_Piece(Zob, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.To.x, V.To.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}

	return Ret;
}




