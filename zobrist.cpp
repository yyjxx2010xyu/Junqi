#include <cassert>
#include <map>
#include "zobrist.h"
#include "chess.h"
#include "game.h"

class Chess;
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
	srand(time(0));
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			for (int k = 0; k < Chess_Type * 2 + 1; k++)
				Zobrist_Table[i][j][k] = Rand_ULL();
	Hash_Table = new int[Table_Size];
	memset(Hash_Table, -1, sizeof(Hash_Table[0]) * Table_Size);
	Hash_Depth = new int[Table_Size];
	memset(Hash_Depth, -1, sizeof(Hash_Depth[0]) * Table_Size);
	Hash_Flag = new int[Table_Size];
	memset(Hash_Flag, -1, sizeof(Hash_Flag[0]) * Table_Size);

	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			for (int k = 0; k < Chess_Type * 2 + 1; k++)
				Verified_Table[i][j][k] = Rand_ULL();
	Hash_Verified = new int[Table_Size];
	memset(Hash_Verified, -1, sizeof(Hash_Verified[0]) * Table_Size);
}

Zobrist::~Zobrist()
{
	delete[] Hash_Table;
	delete[] Hash_Depth;
	delete[] Hash_Flag;
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
void Zobrist::Record_State(ull Zob_Num, int Eval, int Depth, int Flag) const
{
	ull Mod = Zob_Num % Table_Size;
	if (Hash_Depth[Mod] <= Depth)
	{
		Hash_Depth[Mod] = Depth;
		Hash_Table[Mod] = Eval;
		Hash_Flag[Mod] = Flag;
	}
}

//	查询状态的Eval
int  Zobrist::Search_State(ull Chess, int Depth, int Alpha, int Beta) const
{
	ull Mod = Chess % Table_Size;
	if (Hash_Depth[Mod] < Depth)
		return -INF;
	if (Hash_Flag[Mod] == HASH_EXACT)
		return Hash_Table[Mod];
	if (Hash_Flag[Mod] == HASH_ALPHA && Hash_Table[Mod] <= Alpha)
		return Alpha;
	if (Hash_Flag[Mod] == HASH_BETA && Hash_Table[Mod] >= Beta)
		return Beta;
	return -INF;
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
		Ret = Remove_Piece(Ret, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Ret, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Ret, V.To.x, V.To.y, BLANK);
		Ret = Add_Piece(Ret, V.From.x, V.From.y, BLANK);
	}
	if (result == ABOVE)
	{

		Ret = Remove_Piece(Ret, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Ret, V.From.x, V.From.y, BLANK);
	}
	if (result == UNDER)
	{
		Ret = Remove_Piece(Ret, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Ret, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Ret, V.To.x, V.To.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Ret, V.From.x, V.From.y, BLANK);
	}
	return Ret;
}

bool Zobrist::Same_Role(ull Chess, int Depth) const
{
	if ((Depth ^ Hash_Depth[Chess % Table_Size]) & 1)
		return false;
	return true;
}

int Zobrist::Get_Depth(ull Chess) const
{
	return Hash_Depth[Chess % Table_Size];
}

void Zobrist::Clear_Depth() const
{
	memset(Hash_Depth, -1, sizeof(Hash_Depth[0]) * Table_Size);
}

static int R[13][5];
static int cnt = 0;
void Zobrist::_Check(int Depth) const
{
	if (Depth == 65)
	{
		ull Ret = 0;
		for (int i = 0; i < Chess_H; i++)
			for (int j = 0; j < Chess_W; j++)
				Ret = Ret ^ Zobrist_Table[i][j][R[i][j]];
		
		cnt++;
		if (cnt % 1000 == 0)
		{
			std::cout << cnt << " " <<  Ret << std::endl;
			fflush(stdout);
		}
		assert(Hash_Depth[Ret % Table_Size] == -1);
		Hash_Depth[Ret % Table_Size] = 0;
		return;
	}
	for (int i = 0; i < 25; i++)
	{
		R[Depth / 5][Depth % 5] = i;
		_Check(Depth + 1);
	}
}
void Zobrist::Check() const
{
	memset(Hash_Depth, -1, sizeof(Hash_Depth[0]) * Table_Size);
	_Check(0);
}


