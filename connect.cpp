#include <iostream>
#include <string>
#include "connect.h"
#include "chess.h"

/*
(1)	ready
引擎启动后向界面发送ready，随后引擎处于空闲状态。
*/
void Connect::Init()
{
	std::cout << "ready" << std::endl;
}

/*
input: 以下三种情况
(2)	<当前棋局>
界面将当前棋局以NCN的形式使用标准输入传递给引擎，引擎开始推理。
例如: ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/JVGVA/S1G1S/YT1TY/Z1G1Y/PLLDZ/PPDFD 0 0
(3)	init <当前棋局>
用于将开局时的棋局传递给后手的引擎，保证开始运算的时间基本一致。
例如: init dfdvl/vdygp/l1g1t/st1yp/z1s1z/apglj/5/JLGPA/Z1S1Z/PY1TS/T1G1L/PGYDV/LVDFD 0 0
(5)	end
棋局结束，引擎退出。

output：
Status			是否结束
	如果结束则Status == STATUS_END
		否则 Status == STATUS_OK
Chess Board		返回棋盘数据，记录在Board中
*/
int Connect::Get_Board(Chess& Board)
{
	std::string Str;
	std::cin >> Str;
	if (Str == "end")
		return STATUS_END;
	if (Str == "init")
		std::cin >> Str;
	int x = 0, y = 0;
	for (int i = 0; i < Str.length(); i++)
	{
		if (Str[i] == '/')
			continue;
		if ((Str[i] >= 'A' && Str[i] <= 'Z') || (Str[i] >= 'a' && Str[i] <= 'z'))
		{
			Board.Set_Board(x, y, Str[i]);
			y++;
			if (y == Chess_W)
			{
				x++;
				y = 0;
			}
		}

		if (Str[i] >= '0' && Str[i] <= '9')
		{
			for (int j = 1; j <= Str[i] - '0'; j++)
			{
				Board.Set_Board(x, y, BLANK);
				y++;
				if (y == Chess_W)
				{
					x++;
					y = 0;
				}
			}
		}
	}
	int Value1, Value2;
	std::cin >> Value1 >> Value2;
	return STATUS_OK;
}

/*
input:	Move结构体
		Move.From	表示起始坐标 都是用数字表示
		Move.To		表示终点坐标 都是用数字表示
output:
(4)	<落子决策>
	使用标准输入的方式反馈运算结果，此后引擎返回空闲状态亦或是继续运算。
例如: h2i2
*/
void Connect::Send_Move(Movement Move)
{
	std::string Str_Move;

	std::string s1, s2, s3, s4;
	s1 = 'a' + 13 - Move.From.x - 1;
	s2 = '0' + Move.From.y;
	s3 = 'a' + 13 - Move.To.x - 1;
	s4 = '0' + Move.To.y;
	Str_Move = s1 + s2 + s3 + s4;

	std::cout << Str_Move << std::endl;
}




