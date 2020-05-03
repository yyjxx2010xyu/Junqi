#pragma once
#include "game.h"


/*
用于完成于界面之间的交互内容
*/
class Connect
{
public:
	void Init();
	int Get_Board(Chess &Board);
	void Send_Move(const Movement& Move);
};