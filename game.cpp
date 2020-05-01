#include <iostream>
#include <vector>
#include <cassert>
#include "game.h"

/*
input: 
	_Board	期盼状态
	_State	执子方

function:
	生成函数，初始化棋盘和执棋状态
*/
Game::Game(Chess _Board, int _State)
{
	Board = _Board;
	State = _State;
}

/*
input:
	depth	搜索深度

output: 
	Move	最优下子

function:
	进行搜索确定最优下子方案
*/
Movement Game::Search(int depth)
{
	Movement Move;
	int alpha = -INF;
	int beta = INF;
	Search_Returns Ret = _Search(Board, depth, alpha, beta, PlayerType::MaximizingPlayer, State);
	if (!Ret.Move_His.empty())
		Move = Ret.Move_His.back();
	else
		assert(false);
	return Move;
}

/*
input:
	State	执子方

output:
	Oppte	交换执子方

function:
	返回交换执子状态
*/
static int Oppsite_State(int State)
{
	int Opp_State = 0;

	/* NEED CODE */

	return Opp_State;
}

/*
input:
	Cur_Board	当前棋盘
	Depth		当前深度
	Alpha		Alpha参数
	Beta		Beta参数
	Player		PlayerType MaximizingPlayer/MinimizingPlayer
	State		执子方

output:
	Search_Returns	_Search函数返回值			
		Eval		当前估值
		Move_His	当前最优的移动路径

function:
	进行mimmax搜索，并使用alpha-beta剪枝，返回最优的下子路径，和最优的解
*/
Search_Returns Game::_Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int State)
{
	if (Depth == 0 || Is_Over(Cur_Board, State))
	{
		return Search_Returns(Evaluate_Chess(Cur_Board), std::vector<Movement>());
	}

	if (Player == PlayerType::MaximizingPlayer)
	{
		int Max_Eval = -INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Search_Movement(Cur_Board, State);
		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			Chess Next_Board = Apply_Move(Cur_Board, V);
			Search_Returns Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_State(State));
			
			if (Ret.Eval > Max_Eval)
			{
				Max_Eval = Ret.Eval;
				Best_Move = Ret.Move_His;
				Best_Move.push_back(V);
				
				Alpha = (Ret.Eval > Alpha) ? Ret.Eval : Alpha;
				if (Beta <= Alpha)
					break;
			}
		}
		return Search_Returns(Max_Eval, Best_Move);
	}
	if (Player == PlayerType::MinimizingPlayer)
	{
		int Min_Eval = INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Search_Movement(Cur_Board, State);
		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			Chess Next_Board = Apply_Move(Cur_Board, V);
			Search_Returns Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_State(State));
			
			if (Ret.Eval < Min_Eval)
			{
				Min_Eval = Ret.Eval;
				Best_Move = Ret.Move_His;
				Best_Move.push_back(V);
				
				Beta = (Ret.Eval < Beta) ? Ret.Eval : Beta;
				if (Beta <= Alpha)
					break;
			}
		}
		return Search_Returns(Min_Eval, Best_Move);
	}
	
	
	//	non-existent situation
	assert(false);
	return Search_Returns(0, std::vector<Movement>());
}


/*
input:
	Cur_Board	棋盘数据
	State	执棋方
		State == STATE_UPPER	表示执棋方为大写，即上方
		State == STATE_LOWER	表示执棋方为小写，即下方

output:
	true/false	当前执棋方无棋可走/有棋可走

function:
	判断当前执子方是否无棋可走
*/

bool Game::Is_Over(const Chess& Cur_Board, const int& State)
{
	/* NEED CODE */
	return bool();
}

/*
input:
	Cur_Board	棋盘数据

output:
	Weight，棋盘权重， 小写的棋子权重减去大写的棋子权重
	Weight = Weigh_lower - Weight_upper
	对每个棋子进行赋权，具体可以自行赋值。

function:
	对棋盘的评估函数
*/
int Game::Evaluate_Chess(const Chess& Cur_Board)
{
	/* NEED CODE */
	return 0;
}

/*
input:
	Cur_Board	棋盘数据
	State	执棋方
		State == STATE_UPPER	表示执棋方为大写，即上方
		State == STATE_LOWER	表示执棋方为小写，即下方

output:
	Move 表示每个可行的Movement，存储在vector中

function:
	寻找搜索方向，有着充分的想象空间
*/
std::vector<Movement> Game::Search_Movement(const Chess& Board, const int& State)
{
	std::vector<Movement> Move;
	Move.clear();

	/* NEED CODE */

	return Move;
}

/*
input:
	Cur_Board	棋盘数据
	Move		走棋方向

output:
	Board		更新之后的棋盘

function:
	通过Move，来更新棋盘
*/

Chess Game::Apply_Move(const Chess& Cur_Board, const Movement& V)
{
	Chess Next_Board;

	/* NEED CODE */

	return Next_Board;
}


/*
function:
	可视化棋盘效果，用-+|表示即可，主要用于调试。

*/
void Chess::Display()
{

}
