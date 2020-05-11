#pragma once
#include "game.h"
#include "chess.h"

/*
用于完成于界面之间的交互内容
*/
class Chess;
class Movement;
class Connect
{
public:
	void Init();
	int Get_Board(Chess &Board);
	void Send_Move(Movement Move);
};