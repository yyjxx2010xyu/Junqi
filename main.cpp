#include <iostream>
#include "connect.h"
#include "game.h"
#include "main.h"
#include "chess.h"
#include "zobrist.h"
#include <ctime>
#include <windows.h>

#ifdef DEBUG
#include <time.h>
#endif // DEBUG 在game.h里定义

/*
 例如: Junqi.exe –-role 1 –-time 60
	注：  参数role：	0表示红方、1表示黑方。
		 参数time：	表示单步决策时间，单位秒。
*/

Movement Human_Input()
{
	std::cout << "请输入移动坐标，用大写比如(H0J0):";
	std::string Str;
	std::cin >> Str;
	return Movement(Coord(Chess_H - (Str[0] - 'A') - 1, Str[1] - '0'), Coord(Chess_H - (Str[2] - 'A') - 1, Str[3] - '0'));
}

int main(int argc, char* argv[])
{
	Connect Con;
	Con.Init();

	//	缺省情况下，执先手
	//	int State = STATE_LOWER;

	//	设定执子方
	Game Junqi;
	Junqi.Arg_Init(argc, argv);


	/*

	while (true)
	{
		Chess Board;
		int Status = Con.Get_Board(Board);
		if (Status == STATUS_END)
			break;
		Board.Display();
		Movement Move = Junqi.Search(Board);
		Board = Board.Apply_Move(Move);
		Board.Display();
		Con.Send_Move(Move);

	}
	*/
	srand(time(NULL));
	Chess Board;

	int Status = Con.Get_Board(Board);
	Board.init();
	while (true)
	{
		Board.Display();
#ifdef DEBUG
		int begin_time = (int)time(0);
#endif // DEBUG
		Movement Move = Junqi.Search(Board, SEARCH_DEPTH);
#ifdef DEBUG
		int finish_time = (int)time(0);
		std::cout << "search time:" << finish_time - begin_time << std::endl;
		getchar();
		getchar();
#endif // DEBUG
		Board = Board.Apply_Move(Move);
		Board.Display();
		Con.Send_Move(Move);
		Move = Human_Input();
		Board= Board.Apply_Move(Move);
		Sleep(2000);

	}
	return 0;
}
