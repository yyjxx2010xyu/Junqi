#include <iostream>
#include <string>
#include "connect.h"
#include "chess.h"

/*
(1)	ready
��������������淢��ready��������洦�ڿ���״̬��
*/
void Connect::Init()
{
	std::cout << "ready" << std::endl;
}

/*
input: �����������
(2)	<��ǰ���>
���潫��ǰ�����NCN����ʽʹ�ñ�׼���봫�ݸ����棬���濪ʼ����
����: ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/JVGVA/S1G1S/YT1TY/Z1G1Y/PLLDZ/PPDFD 0 0
(3)	init <��ǰ���>
���ڽ�����ʱ����ִ��ݸ����ֵ����棬��֤��ʼ�����ʱ�����һ�¡�
����: init dfdvl/vdygp/l1g1t/st1yp/z1s1z/apglj/5/JLGPA/Z1S1Z/PY1TS/T1G1L/PGYDV/LVDFD 0 0
slow case dfdvl/vdygp/l1g1t/st1yp/zasjz/1pgl1/5/1LGP1/ZJSAZ/PY1TS/T1G1L/PGYDV/LVDFD 0 0
(5)	end
��ֽ����������˳���

output��
Status			�Ƿ����
	���������Status == STATUS_END
		���� Status == STATUS_OK
Chess Board		�����������ݣ���¼��Board��
*/
int Connect::Get_Board(Chess& Board)
{
	std::string Str;
	
	std::cin >> Str;
	
	bool after = false;
	if (Str == "end")
		return STATUS_END;
	if (Str == "init") {
		std::cin >> Str;
		after = true;
	}
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
	if (after)
		return STATUS_AFTER;
	return STATUS_OK;
}

/*
input:	Move�ṹ��
		Move.From	��ʾ��ʼ���� ���������ֱ�ʾ
		Move.To		��ʾ�յ����� ���������ֱ�ʾ
output:
(4)	<���Ӿ���>
	ʹ�ñ�׼����ķ�ʽ�������������˺����淵�ؿ���״̬����Ǽ������㡣
����: h2i2
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




