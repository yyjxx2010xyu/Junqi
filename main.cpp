#include <iostream>
#include "connect.h"
#include "game.h"
#include "main.h"

/*
 例如: Junqi.exe –-role 1 –-time 60
	注： 参数role：0表示红方、1表示黑方。
		参数time：表示单步决策时间，单位秒。

*/

#if 0
int main(int argc, char* argv[])
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
#endif

int main() {
	std::vector<std::vector<char> >  Board = { {'p','p','d','f','d'}, {'p','l','l','d','z'}, {'z','1','g','1','y'}, {'y','t','1','t','y'},
		{'s','1','g','1','s'}, {'j','v','g','v','a'},{'5'},{'J','V','G','V','A'},{'S','1','G','1','S'},{'Y','T','1','T','Y'},{ 'Z','1','G','1','Y'}, {'P','L','L','D','Z'},{'P','P','D','F','D'} };
	Chess cb(Board);
	//	cb.Display();
	std::vector<Movement> m = cb.Search_Movement(ROLE_UPPER);
	for (std::vector<Movement>::iterator iter = m.begin(); iter != m.end(); iter++)
		std::cout << (*iter).From.x << (*iter).From.y << ' ' << (*iter).To.x << (*iter).To.y << std::endl;
	return 0;
}