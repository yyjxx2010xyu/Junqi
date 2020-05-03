#include <iostream>
#include "connect.h"
#include "game.h"
#include "main.h"

/*
 例如: Junqi.exe –-role 1 –-time 60
	注： 参数role：0表示红方、1表示黑方。
		参数time：表示单步决策时间，单位秒。

*/

int main(int argc, char * argv[])
{
	Connect Con;
	Con.Init();

	//	缺省情况下，执先手
	//	int State = STATE_LOWER;
	

	//	设定执子方
	Game Junqi;
	Junqi.Arg_Init(argc, argv);

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
	return 0;
}