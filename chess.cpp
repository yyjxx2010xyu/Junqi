#include <iostream>
#include "chess.h"

/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方


output:
	true/false	当前执棋方无棋可走/有棋可走

function:
	根据棋盘this->Board，判断当前执子方是否无棋可走
*/

int Chess::Rank_Judgement(char a, char b)
{
	//新位置为空
	if (a == BLANK)
		return UNDER;
	if (b == BLANK)
		return ABOVE;
	if (a >= 'a' && a <= 'z')
		a = a - 'a' + 'A';
	if (b >= 'a' && b <= 'z')
		b = b - 'a' + 'A';
	if (a == 'Z' || b == 'Z' || a == b)//特殊：炸弹
		return SAME_RANK;
	if (a != 'G' && b == 'D' || a == 'D' && b != 'G')//特殊：地雷
		return SAME_RANK;
	if (a == 'G' && b == 'D')//特殊：工兵排雷
		return ABOVE;
	if (a == 'D' && b == 'G')//特殊：工兵排雷
		return UNDER;
	//以下为等级顺序
	int a_order;
	int b_order;
	for (int i = 0; i < strlen(RANK); i++) {
		if (a == RANK[i])
			a_order = i;
		if (b == RANK[i])
			b_order = i;
	}
	if (a_order < b_order)
		return ABOVE;
	else
		return UNDER;
}


bool Chess::Is_Over(const int& Role)
{
	/* NEED CODE */
	//只考虑了双方大本营内的军旗有没有被吃
	if ((Board[0][1] == 'F' || Board[0][3] == 'F') && (Board[12][1] == 'f' || Board[12][3] == 'f'))
		return false;
	//找到棋盘内可移动的棋子
	char ch0 = 'A';
	char ch1 = 'Z';
	if (Role == ROLE_LOWER) {
		ch0 = 'a';
		ch1 = 'z';
	}
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= ch0 && Board[i][j] <= ch1)
			{
				if (chessMap.at(Board[i][j]) == chessClass::dilei)
					continue;
				if (chessMap.at(Board[i][j]) == chessClass::junqi)
					continue;
				return false;
			}
		}
	}
	return true;
}



/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方


output:
	Weight，棋盘权重， 当前的执子方棋减去对方执子方棋
	Weight = Weigh_Role - Weight_Opp_Role
	对每个棋子进行赋权，具体可以自行赋值。

function:
	对棋盘的评估函数
*/


int Chess::Evaluate_Chess(const int& Role)
{
	int UPPER = 0;
	int LOWER = 0;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= 'A' && Board[i][j] <= 'Z')
				UPPER++;
			else
				LOWER++;
		}
	}
	if (Role == ROLE_LOWER)
		return LOWER - UPPER;
	else
		return UPPER - LOWER;
}


/*
input:
	Move			走棋方向

output:
	Next_Board		更新之后的棋盘

function:
	通过Move结合this->Board来更新棋盘
*/

Chess Chess::Apply_Move(const Movement& V)
{
	Chess Next_Board;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			Next_Board.Board[i][j] = Board[i][j];
		}
	}
	int result = Rank_Judgement(Next_Board.Board[V.To.x][V.To.y], Next_Board.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK) {
		Next_Board.Board[V.To.x][V.To.y] = BLANK;
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else if (result == ABOVE) {
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else {
		Next_Board.Board[V.To.x][V.To.y] = Next_Board.Board[V.From.x][V.From.y];
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}

	return Next_Board;
}


/*
function:
	简单的可视化棋盘效果，用-+|表示即可，主要用于调试。
	假如有颜色区别就更好了
*/
void Chess::Display()
{
	const Coord board = { Chess_W, Chess_H };
	//	std::cout << "Display Testcase" << std::endl;
	//	1. 清屏
	cls();
	//	2. 设置界面大小
	setconsoleborder(130, 40);

	//	3. 画界面和棋子
	common_draw_background(board, true, true, true, { 0,0 });
	Display_Chess(Board, board, true, true);
	//	4. 恢复默认设置
	setcolor();
	std::cout << std::endl << std::endl;
}


//	该棋子为执棋方
static bool Is_Role_Chess(char ch, int Role)
{
	if (Role == ROLE_UPPER && ch >= 'A' && ch <= 'Z')
		return true;
	if (Role == ROLE_LOWER && ch >= 'a' && ch <= 'z')
		return true;
	return false;
}


//	该棋子为工兵
static bool Is_GongBing(char ch)
{
	return (ch == 'g') || (ch == 'G');
}

//	合法位置
static bool Is_Valid(int x, int y)
{
	return x >= 0 && x < Chess_H&& y >= 0 && y < Chess_W;
}


//	在铁路上
static bool Is_Railway(int x, int y)
{
	return Railway[x][y];
}

//	在行营中
static bool Is_Station(int x, int y)
{
	return Station[x][y];
}

//	有棋子
static bool Has_Chess(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}


//	比大小
static bool Is_Greater(char From, char To)
{
	if (chessMap.at(From) == chessClass::gongbing && chessMap.at(From) == chessClass::dilei)
		return true;
	//	const char RANK[11] = "AJSVTYLPGF";


	if (From >= 'a' && From <= 'z')
		From = From - 'a' + 'A';

	if (To >= 'a' && To <= 'z')
		To = To - 'a' + 'A';

	std::cout << From << " " << To << std::endl;
	int a_order;
	int b_order;
	for (int i = 0; i < strlen(RANK); i++) {
		if (From == RANK[i])
			a_order = i;
		if (To == RANK[i])
			b_order = i;
	}
	if (a_order <= b_order)
		return true;
	return false;
}
bool Chess::Is_Movable(Movement M)
{
	char From = Board[M.From.x][M.From.y];
	char To = Board[M.To.x][M.To.y];
	//	强制要求吃子
	if (To == BLANK)
		return false;

	if (chessMap.at(From) == chessClass::dilei)
		return false;
	if (chessMap.at(From) == chessClass::junqi)
		return false;

	//	对方的棋子大
	if (!Is_Greater(From, To))
		return false;

	//	方向是行营且有棋子
	if (Is_Station(M.To.x, M.To.y) && Has_Chess(To))
		return false;

	return true;
}

void Chess::Set_Board(int x, int y, int ch)
{
	Board[x][y] = ch;
}

/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方

output:
	Move 表示每个可行的Movement，存储在vector中

function:
	寻找搜索方向，有着充分的想象空间
*/
std::vector<Movement> Chess::Search_Movement(const int& Role)
{
	std::vector<Movement> Move;
	Move.clear();

	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			if (Is_Role_Chess(Board[i][j], Role))
			{
				if (Is_GongBing(Board[i][j]))
					continue;
				//	std::vector<Coord> v2 = Railway(ceil);
				//	v1.insert(v1.end(), v2.begin(), v2.end());


					//	上下左右方向，铁路上自动扩展
				for (int k = 0; k < 4; k++)
				{
					int cur_x = i, cur_y = j;

					while (true)
					{
						cur_x += HV_DirectX[k];
						cur_y += HV_DirectY[k];
						//	判断坐标合法性
						if (!Is_Valid(cur_x, cur_y))
							break;
						//	如果不在铁轨上，或者脱离铁轨那么就直接退出
						if (!(Is_Railway(cur_x, cur_y) && Is_Railway(i, j)))
							break;
						//	如果碰到棋子了
						if (Has_Chess(Board[cur_x][cur_y]))
							break;

					}

					if (!Is_Valid(cur_x, cur_y))
						continue;
					if (!Has_Chess(Board[cur_x][cur_y]))
						continue;
					if (Is_Role_Chess(Board[cur_x][cur_y], Role))
						continue;
					//	如果起始位置在铁轨上，结束位置不在铁轨上，则不合法
					if (!Is_Railway(cur_x, cur_y) && Is_Railway(i, j))
						continue;

					Movement M = Movement(Coord(i, j), Coord(cur_x, cur_y));
					if (!Is_Movable(M))
						continue;
					Move.push_back(M);
				}

				// 斜向方向只能为1
				for (int k = 0; k < 4; k++)
				{
					int cur_x = i + Cross_DirectX[k];
					int cur_y = j + Cross_DirectY[k];
					if (!(Is_Station(i, j) || Is_Station(cur_x, cur_y)))
						continue;
					if (!Is_Valid(cur_x, cur_y))
						continue;
					Movement M = Movement(Coord(i, j), Coord(cur_x, cur_y));
					if (!Is_Movable(M))
						continue;
					Move.push_back(M);

				}
			}

	return Move;
}





//	返回棋盘相应位置的颜色
inline int isColor(int linePos) {
	if (linePos >= 0 && linePos < frontEndPos - 1)
		return COLOR_BLUE;
	else if (linePos == frontEndPos - 1)
		return COLOR_BLACK;
	else
		return COLOR_RED;
}

//	画棋盘
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor) {
	const char* Solid[][13] = { {"║", "═","╔" ,"╗" ,"╚" , "╝", "╠" ,"╣" ,"╦═","╩═","═╬","  " ,"  ║" },
	{ "┃","━","┏","┓","┗","┛","┣","┫","┳━","┻━","━╋" ,"  " ,"  ┃" } };
	enum class Pos { vertical, horizonal, lefttop, righttop, leftbottom, rightbottom, leftmid, rightmid, upmid, downmid, center, empty, straight };

	//	four corners
	showstr(2 * display + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::lefttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::righttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::leftbottom], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::rightbottom], COLOR_HWHITE, COLOR_BLACK);

	//	horizonal
	showstr(2 * display + 2 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	showstr(2 * display + 2 + cursor.x, 3 + display + (border + 1) * (sizeofall.y - 1) + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	if (border) {
		showstr(2 * display + 4 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::upmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
		showstr(2 * display + 4 + cursor.x, 2 * sizeofall.y + 1 + display + cursor.y, Solid[solid][(int)Pos::downmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
	}

	//	vertical
	for (int i = 0; i < sizeofall.y; i++) {
		showstr(2 * display + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 * (1 + border) * (sizeofall.x - 1) + 4 + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 + display + i + cursor.y, Solid[solid][(int)Pos::empty], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	}
	if (border) {
		for (int i = 0; i < sizeofall.y - 1; i++) {
			showstr(2 * display + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::leftmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::rightmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 2 + cursor.x, 2 * i + 2 + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
			showstr(2 * display + 2 + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::center], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
			showstr(2 * display + 2 + 4 * (sizeofall.x - 1) + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK);
		}
		showstr(2 * display + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
	}

	//	display coordinates
	if (display) {
		for (int i = 0; i < sizeofall.x; i++) {
			showch(5 + 2 * (border + 1) * i, 1, '0' + i);
		}
		for (int i = 0; i < sizeofall.y; i++) {
			showch(0, 3 + (border + 1) * i, 'A' + sizeofall.y - 1 - i);
		}
	}
}

//	画棋子
inline void Display_Chess(std::vector<std::vector<char> >  Board, class Coord sizeofall, bool border, bool display) {
	if (Board.size() != sizeofall.y || Board[0].size() != sizeofall.x)
		return;

	for (unsigned i = 0; i < Board.size(); i++) {
		for (unsigned j = 0; j < Board[i].size(); j++) {
			showch(2 * display + 2 + 2 * j * (border + 1), 2 + display + i * (border + 1), Board[i][j], COLOR_HWHITE, isColor(i));
		}
		std::cout << std::endl;
	}
}

