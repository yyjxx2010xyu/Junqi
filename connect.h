#pragma once
#include "game.h"


/*
用于完成于界面之间的交互内容
*/
class Connect
{
public:
	void Init();
	Chess Get_NCN(int& State);
	void Send_NCN(const Movement& Move);
};