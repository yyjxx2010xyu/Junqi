#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstring>
#include "game.h"
#include "connect.h"
#include "zobrist.h"

//#define ENABLE_ZOB
#define ENABLE_ALPHABETA

const int ROLE_UPPER = 1;
const int ROLE_LOWER = -1;

/*
input:
����: Junqi.exe �C-role 1 �C-time 60
	ע�� ����role��0��ʾ�췽��1��ʾ�ڷ���
		����time����ʾ��������ʱ�䣬��λ�롣

output:

function:
	����Game���е�Role��Time_Limit
*/

void Game::Arg_Init(int argc, char* argv[])
{
	Role = 1;
	Time_Limit = 60;
	if (argc == 3)
	{
	
		if (strcmp(argv[1], "--role") == 0)
			Role = atoi(argv[2]);
		if (strcmp(argv[1], "--time") == 0)
			Time_Limit = atoi(argv[2]);
	}
	if (argc == 5)
	{
		if (strcmp(argv[1], "--role") == 0)
			Role = atoi(argv[2]);
		if (strcmp(argv[1], "--time") == 0)
			Time_Limit = atoi(argv[2]);
		if (strcmp(argv[3], "--role") == 0)
			Role = atoi(argv[4]);
		if (strcmp(argv[3], "--time") == 0)
			Time_Limit = atoi(argv[4]);
	}
}


/*
input:
	depth	�������

output:
	Move	�������ӷ���

function:
	��������ȷ���������ӷ���
*/

static int begin_time;
static int finish_time;
Movement Game::Search(Chess Board, int Depth)
{

	int alpha = -INF;
	int beta = INF;

	begin_time = (int)time(0);

	Chess Cur_Board(Board);

	Eval_Move Ret = _Search(Cur_Board, Depth, alpha, beta, PlayerType::MaximizingPlayer, Role, SEARCH_WIDTH);

	finish_time = (int)time(0);

	//	std::cout << "search time:" << finish_time - begin_time << std::endl;
	
	return Ret.second;
}



/*
input:
	Cur_Role	ִ�ӷ�

output:
	Opp_Role	����ִ�ӷ�

function:

	���ؽ���ִ��״̬
*/

static int Oppsite_Role(int Cur_Role)
{


	return (Cur_Role == ROLE_UPPER) ? ROLE_LOWER : ROLE_UPPER;
}

/*
input:
	Cur_Board	��ǰ����
	Depth		��ǰ���
	Alpha		Alpha����
	Beta		Beta����
	Player		PlayerType MaximizingPlayer/MinimizingPlayer
	Cur_Role	ִ�ӷ�

output:
	Eval_Move		_Search��������ֵ
		Eval		��ǰ��ֵ
		Move_His	��ǰ���ŵ��ƶ�·��

function:
	����mimmax��������ʹ��alpha-beta��֦���������ŵ�����·���������ŵĽ�
*/
Eval_Move Game::_Search(Chess& Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_Role, int Search_Width)
{

	finish_time = (int)time(0);
	if (finish_time - begin_time > this->Time_Limit - 1)
		return std::make_pair(-INF + 1, Movement(Coord(), Coord()));

	if (Depth == 0 || Cur_Board.Is_Over(Cur_Role))
	{
		//	Eval����ʼ�շ��صĻ���ִ�ӷ������Ž�
		return std::make_pair(Cur_Board.Evaluate_Chess(Cur_Role), Movement(Coord(), Coord()));
	}

	if (Player == PlayerType::MaximizingPlayer)
	{
		int Max_Eval = -INF;
		Movement Best_Move = Movement(Coord(), Coord());
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role, Player, Search_Width);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			char From_Piece = Cur_Board.Get_Piece(V.From.x, V.From.y);
			char To_Piece = Cur_Board.Get_Piece(V.To.x, V.To.y);
			Cur_Board = Cur_Board.Apply_Move(V);
			//	Cur_Board.Display();

			Eval_Move Ret = _Search(Cur_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_Role(Cur_Role), Search_Width - SEARCH_DEC);
			Cur_Board.Set_Piece(V.From.x, V.From.y, From_Piece);
			Cur_Board.Set_Piece(V.To.x, V.To.y, To_Piece);

			int Eval = Ret.first;

			if (Depth == SEARCH_DEPTH)
			{
				//	std::cout << "Depth == " << SEARCH_DEPTH << " " << (char)('A' + 12 - V.From.x) << V.From.y << " " << (char)('A' + 12 - V.To.x) << V.To.y << " Eval:" << Eval << " Heur Eval:" << Cur_Board.Evaluate_Chess(Cur_Role) << std::endl;
				if (To_Piece == 'f' || To_Piece == 'F')
					return std::make_pair(Max_Eval, V);
			}

			if (Eval > Max_Eval)
			{
				Max_Eval = Eval;
				Best_Move = V;

				Alpha = (Eval > Alpha) ? Eval : Alpha;

				if (Beta <= Alpha)
					break;
			}
		}
		return std::make_pair(Max_Eval, Best_Move);
	}

	//	��С����ǰEval��Player
	if (Player == PlayerType::MinimizingPlayer)
	{
		int Min_Eval = INF;
		Movement Best_Move = Movement(Coord(), Coord());
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role, Player, Search_Width);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			char From_Piece = Cur_Board.Get_Piece(V.From.x, V.From.y);
			char To_Piece = Cur_Board.Get_Piece(V.To.x, V.To.y);
			Cur_Board = Cur_Board.Apply_Move(V);
			//	Cur_Board.Display();
			Eval_Move Ret = _Search(Cur_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_Role(Cur_Role), Search_Width - SEARCH_DEC);

			Cur_Board.Set_Piece(V.From.x, V.From.y, From_Piece);
			Cur_Board.Set_Piece(V.To.x, V.To.y, To_Piece);


			int Eval = Ret.first;

			if (Eval < Min_Eval)
			{
				Min_Eval = Eval;
				Best_Move = V;
				Beta = (Eval < Beta) ? Eval : Beta;
				if (Beta <= Alpha)
					break;
			}
		}

		return std::make_pair(Min_Eval, Best_Move);
	}


	//	non-existent situation
	assert(false);
	return std::make_pair(0, Movement(Coord(), Coord()));
}
