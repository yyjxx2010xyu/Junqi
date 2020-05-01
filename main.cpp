#include <iostream>
#include "connect.h"
#include "game.h"
#include "main.h"

using namespace std;


int main()
{
	Connect Con;
	Con.Init();

	//	缺省情况下，执先手
	int State = STATE_LOWER;

	while (true)
	{
		Chess Board;
		Board = Con.Get_NCN(State);
		if (State == STATE_END)
			break;
		
		if (0)
		{
			Board.Display();
		}

		Game Cur(Board, State);
		Movement Move = Cur.Search();
		Con.Send_NCN(Move);
	}

	return 0;
}