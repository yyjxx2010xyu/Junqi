#include <iostream>
#include <string>
#include "connect.h"


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
例如: init ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/JVGVA/S1G1S/YT1TY/Z1G1Y/PLLDZ/PPDFD 0 0
(5)	end
棋局结束，引擎退出。

output：
Status			是否结束
	如果结束则Status == STATUS_END
		否则 Status == STATUS_OK
Chess Board		返回棋盘数据，记录在Board中
*/
int Connect::Get_Board(Chess & Board)
{
	int Status = STATUS_OK;
	
	char ch;
	int i = 0, j = 0;
	while (std::cin >> ch)
	{
		if (ch == 'i')
			for (int i = 0; i <= 3; i++)
				std::cin >> ch;
		else if (ch == 'e')
			return STATUS_END;
		else if (ch == '/')
			i++;
		else if (ch <= 53 && ch >= 49)
			for (int i = 48; i < (int)ch; i++)
			{
				Board[i][j] = '*';
				j++;
			}
		else
		{
			Board[i][j] = ch;
			j++;
		}

	}
	
	return Status;
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
void Connect::Send_Move(const Movement& Move)
{
	std::string Str_Move;

	std::string s1, s2, s3, s4;
	s1 = 'a' + 13 - Move.From.x;
	s2 = '0' + Move.From.y;
	s3 = 'a' + 13 - Move.To.x;
	s4 = '0' + Move.To.y;
	Str_Move = s1 + s2 + s3 + s4;

	std::cout << Str_Move << std::endl;
}




