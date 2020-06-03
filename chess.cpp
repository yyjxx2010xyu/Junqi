#include <iostream>
#include <cassert>
#include "chess.h"
#include "game.h"

const int CENTER_ONE = 10;
const int CENTER_TWO = 8;
const int CENTER_THREE = 2;


void Chess::init()
{
	if (Board[0][1] == 'f' || Board[0][3] == 'f') {
		Lower_Role = UP;
		Upper_Role = DOWN;
	}
	else {
		Lower_Role = DOWN;
		Upper_Role = UP;
	}
	if (Lower_Role == UP) {
		if (Board[0][1] == 'f') {
			FlagPos[Upper_Role][0][1] = CENTER_ONE;
			FlagPos[Upper_Role][0][0] = CENTER_TWO;
			FlagPos[Upper_Role][0][2] = CENTER_TWO;
			FlagPos[Upper_Role][1][1] = CENTER_TWO;
			FlagPos[Upper_Role][1][0] = CENTER_THREE;
			FlagPos[Upper_Role][2][1] = CENTER_THREE;
			FlagPos[Upper_Role][1][2] = CENTER_THREE;
			FlagPos[Upper_Role][0][3] = CENTER_THREE;
		}
		else {
			FlagPos[Upper_Role][0][3] = CENTER_ONE;
			FlagPos[Upper_Role][0][2] = CENTER_TWO;
			FlagPos[Upper_Role][0][4] = CENTER_TWO;
			FlagPos[Upper_Role][1][3] = CENTER_TWO;
			FlagPos[Upper_Role][0][1] = CENTER_THREE;
			FlagPos[Upper_Role][1][2] = CENTER_THREE;
			FlagPos[Upper_Role][2][3] = CENTER_THREE;
			FlagPos[Upper_Role][1][4] = CENTER_THREE;
		}
		if (Board[12][1] == 'F') {
			FlagPos[Lower_Role][12][1] = CENTER_ONE;
			FlagPos[Lower_Role][12][0] = CENTER_TWO;
			FlagPos[Lower_Role][12][2] = CENTER_TWO;
			FlagPos[Lower_Role][11][1] = CENTER_TWO;
			FlagPos[Lower_Role][11][0] = CENTER_THREE;
			FlagPos[Lower_Role][10][1] = CENTER_THREE;
			FlagPos[Lower_Role][11][2] = CENTER_THREE;
			FlagPos[Lower_Role][12][3] = CENTER_THREE;
		}
		else {
			FlagPos[Lower_Role][12][3] = CENTER_ONE;
			FlagPos[Lower_Role][12][2] = CENTER_TWO;
			FlagPos[Lower_Role][12][4] = CENTER_TWO;
			FlagPos[Lower_Role][11][3] = CENTER_TWO;
			FlagPos[Lower_Role][12][1] = CENTER_THREE;
			FlagPos[Lower_Role][11][2] = CENTER_THREE;
			FlagPos[Lower_Role][10][3] = CENTER_THREE;
			FlagPos[Lower_Role][11][4] = CENTER_THREE;
		}
	}
	else {
		if (Board[0][1] == 'F') {
			FlagPos[Lower_Role][0][1] = CENTER_ONE;
			FlagPos[Lower_Role][0][0] = CENTER_TWO;
			FlagPos[Lower_Role][0][2] = CENTER_TWO;
			FlagPos[Lower_Role][1][1] = CENTER_TWO;
			FlagPos[Lower_Role][1][0] = CENTER_THREE;
			FlagPos[Lower_Role][2][1] = CENTER_THREE;
			FlagPos[Lower_Role][1][2] = CENTER_THREE;
			FlagPos[Lower_Role][0][3] = CENTER_THREE;
		}
		else {
			FlagPos[Lower_Role][0][3] = CENTER_ONE;
			FlagPos[Lower_Role][0][2] = CENTER_TWO;
			FlagPos[Lower_Role][0][4] = CENTER_TWO;
			FlagPos[Lower_Role][1][3] = CENTER_TWO;
			FlagPos[Lower_Role][0][1] = CENTER_THREE;
			FlagPos[Lower_Role][1][2] = CENTER_THREE;
			FlagPos[Lower_Role][2][3] = CENTER_THREE;
			FlagPos[Lower_Role][1][4] = CENTER_THREE;
		}
		if (Board[12][1] == 'f') {
			FlagPos[Upper_Role][12][1] = CENTER_ONE;
			FlagPos[Upper_Role][12][0] = CENTER_TWO;
			FlagPos[Upper_Role][12][2] = CENTER_TWO;
			FlagPos[Upper_Role][11][1] = CENTER_TWO;
			FlagPos[Upper_Role][11][0] = CENTER_THREE;
			FlagPos[Upper_Role][10][1] = CENTER_THREE;
			FlagPos[Upper_Role][11][2] = CENTER_THREE;
			FlagPos[Upper_Role][12][3] = CENTER_THREE;
		}
		else {
			FlagPos[Upper_Role][12][3] = CENTER_ONE;
			FlagPos[Upper_Role][12][2] = CENTER_TWO;
			FlagPos[Upper_Role][12][4] = CENTER_TWO;
			FlagPos[Upper_Role][11][3] = CENTER_TWO;
			FlagPos[Upper_Role][12][1] = CENTER_THREE;
			FlagPos[Upper_Role][11][2] = CENTER_THREE;
			FlagPos[Upper_Role][10][3] = CENTER_THREE;
			FlagPos[Upper_Role][11][4] = CENTER_THREE;
		}
	}
	Chess_Value['g'] = Value_G;
	Chess_Value['G'] = Value_G;
	Chess_Value['p'] = Value_P;
	Chess_Value['P'] = Value_P;
	Chess_Value['l'] = Value_L;
	Chess_Value['L'] = Value_L;
	Chess_Value['y'] = Value_Y;
	Chess_Value['Y'] = Value_Y;
	Chess_Value['t'] = Value_T;
	Chess_Value['T'] = Value_T;
	Chess_Value['v'] = Value_V;
	Chess_Value['V'] = Value_V;
	Chess_Value['s'] = Value_S;
	Chess_Value['S'] = Value_S;
	Chess_Value['j'] = Value_J;
	Chess_Value['J'] = Value_J;
	Chess_Value['a'] = Value_A;
	Chess_Value['A'] = Value_A;
	Chess_Value['f'] = Value_F;
	Chess_Value['F'] = Value_F;
	Chess_Value['z'] = Value_Z;
	Chess_Value['Z'] = Value_Z;
	Chess_Value['d'] = Value_D;
	Chess_Value['D'] = Value_D;
	Chess_Value[' '] = Value_B;
	Chess_Value[' '] = Value_B;

}

/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�


output:
	true/false	��ǰִ�巽�������/�������

function:
	��������this->Board���жϵ�ǰִ�ӷ��Ƿ��������
*/

int Rank_Judgement(char a, char b)
{
	//��λ��Ϊ��
	if (a == BLANK)
		return UNDER;
	if (b == BLANK)
		return ABOVE;
	if (a >= 'a' && a <= 'z')
		a = a - 'a' + 'A';
	if (b >= 'a' && b <= 'z')
		b = b - 'a' + 'A';
	if (a == 'Z' || b == 'Z' || a == b)//���⣺ը��
		return SAME_RANK;
	if (a != 'G' && b == 'D' || a == 'D' && b != 'G')//���⣺����
		return SAME_RANK;
	if (a == 'G' && b == 'D')//���⣺��������
		return ABOVE;
	if (a == 'D' && b == 'G')//���⣺��������
		return UNDER;
	//����Ϊ�ȼ�˳��
	int a_order;
	int b_order;
	for (int i = 0; i < strlen(RANK); i++) {
		if (a == RANK[i])
			a_order = i;
		if (b == RANK[i])
			b_order = i;
	}
	if (a_order < b_order)
		return ABOVE;
	else
		return UNDER;
}


bool Chess::Is_Over(const int& Role)
{
	//ֻ������˫����Ӫ�ڵľ�����û�б���
	if (Role == ROLE_LOWER) {
		if (Lower_Role == UP) {
			if (Board[0][1] != 'f' && Board[0][3] != 'f')
				return true;
		}
		else {
			if (Board[12][1] != 'f' && Board[12][3] != 'f')
				return true;
		}
	}

	if (Role == ROLE_UPPER) {
		if (Upper_Role == UP) {
			if (Board[0][1] != 'F' && Board[0][3] != 'F')
				return true;
		}
		else {
			if (Board[12][1] != 'F' && Board[12][3] != 'F')
				return true;
		}
	}

	//�ҵ������ڿ��ƶ�������
	char ch0 = 'A';
	char ch1 = 'Z';
	if (Role == ROLE_LOWER) {
		ch0 = 'a';
		ch1 = 'z';
	}
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= ch0 && Board[i][j] <= ch1)
			{
				if (chessMap.at(Board[i][j]) == chessClass::dilei)
					continue;
				if (chessMap.at(Board[i][j]) == chessClass::junqi)
					continue;
				return false;
			}
		}
	}
	return true;
}



/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�


output:
	Weight������Ȩ�أ� ��ǰ��ִ�ӷ����ȥ�Է�ִ�ӷ���
	Weight = Weigh_Role - Weight_Opp_Role
	��ÿ�����ӽ��и�Ȩ������������и�ֵ��

function:
	�����̵���������
*/
//const char RANK[] = "AJSVTYLPGF";

int Chess::Evaluater(const int x, const int y, const char ch)
{
	int value = Chess_Value[ch];
	int temp;
	int killFlag;
	//���ӶԷ�����Ȩ��
	if (ch >= 'A' && ch <= 'Z') {
		temp = Chess_board[Upper_Role][x];
		killFlag = FlagPos[Upper_Role][x][y];
	}
	else {
		temp = Chess_board[Lower_Role][x];
		killFlag = FlagPos[Lower_Role][x][y];
	}
	//������Ӫ��ռ��Ȩ�أ�ϣ��������ռ������Ӫ
	return (int)((double)(1.0 + 0.008 * (double)Station[x][y] + 0.0025 * (double)Railway[x][y] + 0.006 * (double)temp + 0.04 * (double)killFlag) * (double)value);

}

int Chess::Evaluater_Origin(const int x, const int y, const char ch)
{
	//֮ǰ�Ĺ�ֵ����
	int value = 0;
	//�����ȼ�
	if (ch == 'g' || ch == 'G')
		value = 110;
	else if (ch == 'p' || ch == 'P')
		value = 120;
	else if (ch == 'l' || ch == 'L')//X2
		value = 250;
	else if (ch == 'y' || ch == 'Y')//X3
		value = 520;
	else if (ch == 't' || ch == 'T')//X4
		value = 1080;
	else if (ch == 'v' || ch == 'V')//X5
		value = 2200;
	else if (ch == 's' || ch == 'S')//X6
		value = 4500;
	else if (ch == 'j' || ch == 'J')//X7
		value = 9600;
	else if (ch == 'a' || ch == 'A')//X8
		value = 20000;
	else if (ch == 'f' || ch == 'F')//X8
		value = 204800;
	else if (ch == 'z' || ch == 'Z')
		value = 3600;//ϣ��ը�����������ų��������ų����µĵ�λ����������ը��
	else if (ch == 'd' || ch == 'D')
		value = 4000;//���ײ���Ϊ��в��Ӫ����Ӫ�����¶�����������
	else if (ch == BLANK)
		value = 0;
	int temp;
	int killFlag;
	//���ӶԷ�����Ȩ��
	if (ch >= 'A' && ch <= 'Z') {
		temp = Chess_board[Upper_Role][x];
		killFlag = FlagPos[Upper_Role][x][y];
	}
	else {
		temp = Chess_board[Lower_Role][x];
		killFlag = FlagPos[Lower_Role][x][y];
	}


	//������Ӫ��ռ��Ȩ�أ�ϣ��������ռ������Ӫ
	return (int)((double)(1.0 + 0.01 * (double)Station[x][y] + 0.003 * (double)Railway[x][y] + 0.008 * (double)temp + 0.05 * (double)killFlag) * (double)value);
	//	return (1000 + 1 * Station[x][y] + 3 * Railway[x][y] + 8 * temp + 5 * killFlag) * value;

		//	return (int)((double)(1.0 + 0.01 * (double)Station[x][y] + 0.001 * (double)Railway[x][y]+0.003*(double)temp+0.05*(double)killFlag) * (double)value);
}

int Chess::Evaluate_Chess(const int& Role)
{
	int UPPER = 0;
	int LOWER = 0;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= 'A' && Board[i][j] <= 'Z')
				UPPER += Evaluater(i, j, Board[i][j]);
			else
				LOWER += Evaluater(i, j, Board[i][j]);
		}
	}
	if (Role == ROLE_LOWER)
		return LOWER - UPPER;
	else
		return UPPER - LOWER;
}


/*
input:
	Move			���巽��

output:
	Next_Board		����֮�������

function:
	ͨ��Move���this->Board����������
*/

Chess Chess::Apply_Move(const Movement& V)
{
	Chess Next_Board(this->Board);
	int result = Rank_Judgement(Next_Board.Board[V.To.x][V.To.y], Next_Board.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK) {
		Next_Board.Board[V.To.x][V.To.y] = BLANK;
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else if (result == ABOVE) {
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else {
		Next_Board.Board[V.To.x][V.To.y] = Next_Board.Board[V.From.x][V.From.y];
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}

	return Next_Board;
}

/*
function:
	�򵥵Ŀ��ӻ�����Ч������-+|��ʾ���ɣ���Ҫ���ڵ��ԡ�
	��������ɫ����͸�����
*/
void Chess::Display()
{
	const Coord board = { Chess_W, Chess_H };
	//	std::cout << "Display Testcase" << std::endl;
	//	1. ����
	cls();
	//	2. ���ý����С
	setconsoleborder(130, 40, 130, 800);

	//	3. �����������
	common_draw_background(board, true, true, true, { 0,0 });
	Display_Chess(Board, board, true, true);
	//	4. �ָ�Ĭ������
	setcolor();
	std::cout << std::endl << std::endl;
}


//	������Ϊִ�巽
static bool Is_Role_Chess(char ch, int Role)
{
	if (Role == ROLE_UPPER && ch >= 'A' && ch <= 'Z')
		return true;
	if (Role == ROLE_LOWER && ch >= 'a' && ch <= 'z')
		return true;
	return false;
}


//	������Ϊ����
static bool Is_GongBing(char ch)
{
	return (ch == 'g') || (ch == 'G');
}

//	�Ϸ�λ��
static bool Is_Valid(int x, int y)
{
	//  Ŀ�ĵ�Ϊɽ��
	if (Field[x][y] == (int)BoardClass::empty)
		return false;
	return (x >= 0 && x < Chess_H&& y >= 0 && y < Chess_W);
}


//	����·��
static bool Is_Railway(int x, int y)
{
	return Railway[x][y];
}

//	����Ӫ��
static bool Is_Station(int x, int y)
{
	return Station[x][y];
}

//	������
static bool Has_Chess(char ch)
{
	return ch != BLANK;
}

static bool Special_move(int x, int y, int cur_x, int cur_y)
{
	if (abs(x - cur_x) + abs(y - cur_y) > 1)
		return false;
	return true;
}

bool Chess::Is_Movable(Movement M)
{
	char From = Board[M.From.x][M.From.y];
	char To = Board[M.To.x][M.To.y];
	int x = M.From.x;
	int y = M.From.y;
	int cur_x = M.To.x;
	int cur_y = M.To.y;

	//  ����λ���ж�
	//  Ŀ�ĵ�Ϊɽ��
	if (Field[cur_x][cur_y] == (int)BoardClass::empty)
		return false;
	//  ���ɲ����ƶ���λ��
	if (SpecialPos[cur_x][cur_y] || SpecialPos[x][y])
		return Special_move(x, y, cur_x, cur_y);
	//  �����ж�
	//	ǿ��Ҫ�����
	if (To == BLANK)
		return false;

	if (chessMap.at(From) == chessClass::dilei)
		return false;
	if (chessMap.at(From) == chessClass::junqi)
		return false;

	//	�Է������Ӵ�
	if (Rank_Judgement(From, To) == UNDER)
		return false;

	//	��������Ӫ��������
	if (Is_Station(M.To.x, M.To.y) && Has_Chess(To))
		return false;
	return true;
}

void Chess::Set_Board(int x, int y, int ch)
{
	Board[x][y] = ch;
}

/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�

output:
	Move ��ʾÿ�����е�Movement���洢��vector��

function:
	Ѱ�������������ų�ֵ�����ռ�
*/

static int Selector(Chess& chess, const int& Role, Movement M)
{
	int after;
	int before;
	if (Has_Chess(chess.Board[M.To.x][M.To.y])) {
		char From_Piece = chess.Get_Piece(M.From.x, M.From.y);
		char To_Piece = chess.Get_Piece(M.To.x, M.To.y);

		before = chess.Evaluater(M.From.x, M.From.y, chess.Board[M.From.x][M.From.y]) - chess.Evaluater(M.To.x, M.To.y, chess.Board[M.To.x][M.To.y]);
		chess = chess.Apply_Move(M);
		if (Is_Role_Chess(chess.Board[M.To.x][M.To.y], Role))
			after = chess.Evaluater(M.To.x, M.To.y, chess.Board[M.To.x][M.To.y]);
		else
			after = 0 - chess.Evaluater(M.To.x, M.To.y, chess.Board[M.To.x][M.To.y]);

		chess.Set_Piece(M.From.x, M.From.y, From_Piece);
		chess.Set_Piece(M.To.x, M.To.y, To_Piece);
	}
	else {
		before = chess.Evaluater(M.From.x, M.From.y, chess.Board[M.From.x][M.From.y]);
		//�ٵ���һ��apply_move
		after = chess.Evaluater(M.To.x, M.To.y, chess.Board[M.From.x][M.From.y]);
	}

	return after - before;
}

bool operator==(const Chess& A, const Chess& B)
{
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			if (A.Board[i][j] != B.Board[i][j])
				return false;
	return true;
}
//	���ڲ���Selector��ȷ�Ե�
static int Selector_Origin(Chess chess, const int& Role, Movement M)
{
	int before = chess.Evaluate_Chess(Role);
	chess = chess.Apply_Move(M);
	int after = chess.Evaluate_Chess(Role);
	return after - before;
}

inline int Min(int x, int y) { return x > y ? y : x; }
std::vector<Eval_Move> Chess::SelectMoveMent(std::vector <Movement> M, const int& Role, PlayerType Player, const int Search_Width)
{
	Chess T(this->Board);

	typedef std::pair<int, Movement> move_pair;
	auto comp = [](const move_pair& a, const move_pair& b) {return a.first > b.first; };

	std::priority_queue<move_pair, std::vector<move_pair>, decltype(comp)> Q(comp);

	for (int i = 0; i < M.size(); i++)
	{
		int temp = Selector(T, Role, M[i]);
		if (!Q.empty() && (temp < Q.top().first && Q.size() == Search_Width))
			continue;

		Q.push(std::make_pair(temp, M[i]));
		if (Q.size() == Search_Width + 1)
			Q.pop();
	}
	std::vector<Eval_Move> result;

	result.resize(Q.size());
	for (int i = Min(Search_Width, Q.size()) - 1; i >= 0; i--)
	{
		result[i] = std::make_pair(Q.top().first, Q.top().second);
		Q.pop();
	}

	return result;
}

static int Oppsite_Role(int Cur_Role)
{
	return (Cur_Role == ROLE_UPPER) ? ROLE_LOWER : ROLE_UPPER;
}

void Chess::BFSSearch(int cur_x, int cur_y, std::vector<Coord>& Pos, const int& Role)
{
	bool visit[Chess_H][Chess_W];
	memset(visit, false, sizeof(visit));
	visit[cur_x][cur_y] = true;

	std::queue<std::pair<int, int> > Q;
	Q.push(std::make_pair(cur_x, cur_y));
	while (!Q.empty())
	{
		std::pair<int, int> Cur_Node = Q.front();
		Q.pop();
		for (int k = 0; k < 4; k++)
		{
			int next_x = Cur_Node.first + HV_DirectX[k];
			int next_y = Cur_Node.second + HV_DirectY[k];
			if (Is_Valid(next_x, next_y) && !visit[next_x][next_y] && Is_Railway(next_x, next_y))
			{
				visit[next_x][next_y] = true;
				if (Has_Chess(Board[next_x][next_y]))
				{
					if (Is_Role_Chess(Board[next_x][next_y], Oppsite_Role(Role)))
					{
						if (Board[next_x][next_y] == 'D' || Board[next_x][next_y] == 'd')
							Pos.push_back(Coord(next_x, next_y));
						if (Board[next_x][next_y] == 'Z' || Board[next_x][next_y] == 'z')
							Pos.push_back(Coord(next_x, next_y));
						if (Board[next_x][next_y] == 'G' || Board[next_x][next_y] == 'g')
							Pos.push_back(Coord(next_x, next_y));
					}
					continue;
				}
				Q.push(std::make_pair(next_x, next_y));
			}
		}

	}
}

char Chess::Get_Piece(int x, int y) const
{
	return Board[x][y];
}

void Chess::Set_Piece(int x, int y, char z)
{
	Board[x][y] = z;
}


bool Expand_Move(std::vector<Movement>& Move, const int cur_x, const int cur_y, const int next_x, const int next_y, const char next_ch, const int Role, const int distance)
{
	Movement V = Movement(Coord(cur_x, cur_y), Coord(next_x, next_y));
	if (Is_Railway(cur_x, cur_y) && !Is_Railway(next_x, next_y) && distance > 1)
		return false;
	if (Is_Station(next_x, next_y) && Has_Chess(next_ch))
		return false;
	if (Is_Role_Chess(next_ch, Role))
		return false;
	if (Has_Chess(next_ch))
	{
		Move.push_back(V);
		return false;
	}
	Move.push_back(V);
	return true;
}

bool Cross_Move(std::vector<Movement>& Move, const int cur_x, const int cur_y, const int next_x, const int next_y, const char next_ch, const int Role)
{
	Movement V = Movement(Coord(cur_x, cur_y), Coord(next_x, next_y));
	if (Is_Role_Chess(next_ch, Role))
		return false;
	if (Is_Station(next_x, next_y) && Has_Chess(next_ch))
		return false;
	if (!(Is_Station(cur_x, cur_y) || Is_Station(next_x, next_y)))
		return false;
	Move.push_back(V);
	return true;
}

std::vector<Eval_Move> Chess::Search_Movement(const int& Role, PlayerType Player, const int Search_Width)
{
	std::vector<Movement> Move;
	Move.clear();

	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Is_Role_Chess(Board[i][j], Role) && chessMap.at(Board[i][j]) != chessClass::junqi && chessMap.at(Board[i][j]) != chessClass::dilei)
			{

				//	ֻ��������·�ϵ�������������������ῼ�ǵ�
				if (Is_GongBing(Board[i][j]) && Is_Railway(i, j))
				{
					std::vector<Coord> Pos;
					Pos.clear();
					BFSSearch(i, j, Pos, Role);
					for (int k = 0; k < Pos.size(); k++)
					{
						Movement M = Movement(Coord(i, j), Pos[k]);
						Move.push_back(M);
					}

				}


				//	�������ҷ�����·���Զ���չ
				for (int k = 0; k < 4; k++)
					for (int d = 1; d <= Chess_H; d++)
					{
						int next_x = i + HV_DirectX[k] * d;
						int next_y = j + HV_DirectY[k] * d;
						if (!Is_Valid(next_x, next_y))
							break;
						bool Ret = Expand_Move(Move, i, j, next_x, next_y, Board[next_x][next_y], Role, d);
						//	����Ѿ��������ӻ����������죬�����ܹ���������
						if (!Ret || !Is_Railway(i, j))
							break;
					}

				// б����
				for (int k = 0; k < 4; k++)
				{
					int next_x = i + Cross_DirectX[k];
					int next_y = j + Cross_DirectY[k];
					if (!Is_Valid(next_x, next_y))
						continue;
					bool _ = Cross_Move(Move, i, j, next_x, next_y, Board[next_x][next_y], Role);
				}
			}
		}
		//	std::cout <<"Move.size:"<< Move.size() << std::endl;
	}
	//return Move;
	return SelectMoveMent(Move, Role, Player, Search_Width);
}





//	����������Ӧλ�õ���ɫ
inline int isColor(int linePos, char ch) {
	if (linePos == frontEndPos - 1)
		return COLOR_BLACK;
	if (ch >= 'a' && ch <= 'z')
		return COLOR_RED;
	else
		return COLOR_BLUE;
}

//	������
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor) {
	const char* Solid[][13] = { {"�U", "�T","�X" ,"�[" ,"�^" , "�a", "�d" ,"�g" ,"�j�T","�m�T","�T�p","  " ,"  �U" },
	{ "��","��","��","��","��","��","��","��","�ש�","�ߩ�","����" ,"  " ,"  ��" } };
	enum class Pos { vertical, horizonal, lefttop, righttop, leftbottom, rightbottom, leftmid, rightmid, upmid, downmid, center, empty, straight };

	//	four corners
	showstr(2 * display + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::lefttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::righttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::leftbottom], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::rightbottom], COLOR_HWHITE, COLOR_BLACK);

	//	horizonal
	showstr(2 * display + 2 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	showstr(2 * display + 2 + cursor.x, 3 + display + (border + 1) * (sizeofall.y - 1) + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	if (border) {
		showstr(2 * display + 4 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::upmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
		showstr(2 * display + 4 + cursor.x, 2 * sizeofall.y + 1 + display + cursor.y, Solid[solid][(int)Pos::downmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
	}

	//	vertical
	for (int i = 0; i < sizeofall.y; i++) {
		showstr(2 * display + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 * (1 + border) * (sizeofall.x - 1) + 4 + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 + display + i + cursor.y, Solid[solid][(int)Pos::empty], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	}
	if (border) {
		for (int i = 0; i < sizeofall.y - 1; i++) {
			showstr(2 * display + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::leftmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::rightmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 2 + cursor.x, 2 * i + 2 + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
			showstr(2 * display + 2 + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::center], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
			showstr(2 * display + 2 + 4 * (sizeofall.x - 1) + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK);
		}
		showstr(2 * display + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
	}

	//	display coordinates
	if (display) {
		for (int i = 0; i < sizeofall.x; i++) {
			showch(5 + 2 * (border + 1) * i, 1, '0' + i);
		}
		for (int i = 0; i < sizeofall.y; i++) {
			showch(0, 3 + (border + 1) * i, 'A' + sizeofall.y - 1 - i);
		}
	}
}

//	������
void Display_Chess(const char Board[][Chess_W], class Coord sizeofall, bool border, bool display) {
	if (Chess_H != sizeofall.y || Chess_W != sizeofall.x)
		return;

	for (unsigned i = 0; i < Chess_H; i++) {
		for (unsigned j = 0; j < Chess_W; j++) {
			showch(2 * display + 2 + 2 * j * (border + 1), 2 + display + i * (border + 1), Board[i][j], COLOR_HWHITE, isColor(i, Board[i][j]));
		}
		std::cout << std::endl;
	}
}

