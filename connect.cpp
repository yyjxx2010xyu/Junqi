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
	
	/* NEED CODE */
	
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

	/* NEED CODE */

	std::cout << Str_Move << std::endl;
}




