#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cassert>
#include "game.h"
#include "connect.h"
#include "cmd_console_tools.h"
//��������Ȩ�أ�ִ�巽�������Ϸ�ΪUP�����·�ΪDOWN
#define UP 0
#define DOWN 1
static bool Upper_Role = DOWN;
static bool Lower_Role = UP;

//	���̵Ĵ�С
static const int Chess_H = 13;
static const int Chess_W = 5;
static const int Chess_Type = 12;

const int Chess_board[2][Chess_H] = {
	{0,0,0,0,0,0,0,1,1,2,2,3,3},
	{3,3,2,2,1,1,0,0,0,0,0,0,0}
};

class Movement;
class Coord;
class Connect;
extern const int ROLE_BLANK;
extern const int ROLE_LOWER;
extern const int ROLE_UPPER;

//�ȼ��ж���Ҫ
const char RANK[] = "AJSVTYLPGF";
const char BLANK = ' ';
static int Chess_Value['z' + 1] = { 0 };
#define UNDER -1
#define ABOVE 1
#define SAME_RANK 0

const int Value_G = 110;
const int Value_P = 120;
const int Value_L = 250;
const int Value_Y = 520;
const int Value_T = 1080;
const int Value_V = 2200;
const int Value_S = 4500;
const int Value_J = 9600;
const int Value_A = 20000;
const int Value_F = 204800;
const int Value_Z = 3600;
const int Value_D = 4000;
const int Value_B = 0;//BLANK




enum class PlayerType;


//	���ڱ�������̵��Ϸ������·�,0Ϊ��Ӫ���Ϸ���1Ϊ��Ӫ���·�
//	���ڱȽϴ�С
int Rank_Judgement(char a, char b);

/*
�洢��ʽ����Word��һ���������ô�д��������Сд��
*/
class Chess
{
private:
	char Board[Chess_H][Chess_W];
public:
	Chess()
	{
		memset(Board, 0, sizeof(char) * Chess_H * Chess_W);
	}
	Chess(const Chess& board_data)
	{
		memcpy(Board, board_data.Board, sizeof(char) * Chess_H * Chess_W);
	}
	Chess(const char board_data[][Chess_W])
	{
		memcpy(Board, board_data, sizeof(char) * Chess_H * Chess_W);
	}

	void init();//��ʼ������λ�ã�ȷ�ϴ�Сд�����̵�λ��
	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	int Evaluater(const int x, const int y, const char ch);
	std::vector<Movement>  Search_Movement(const int& State, PlayerType Player, const int Search_Width);
	Chess Apply_Move(const Movement& V);
	void Display();
	bool Is_Movable(Movement M);
	void Set_Board(int x, int y, int ch);
	void BFSSearch(int x, int y, std::vector<Coord>& Pos, const int& Role);
	char Get_Piece(int x, int y) const;
	void Set_Piece(int x, int y, char z);
	int Evaluater_Origin(const int x, const int y, const char ch);
	std::vector<Movement> SelectMoveMent(std::vector <Movement> M, const int& Role, PlayerType Player, const int Search_Width);
	friend static int Selector(Chess& chess, const int& Role, Movement M);
	friend class Zobrist;

	friend bool operator == (const Chess& A, const Chess& B);
	friend void Display_Chess(const char Board[][Chess_W], class Coord sizeofall, bool border, bool display);
};

const int frontEndPos = 7;	//	ǰ��λ��
//	����������Ӧλ�õ���ɫ
inline int isColor(int linePos, char ch);
//	������
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor);
//	������
inline void Display_Chess(const char Board[][Chess_W], class Coord sizeofall, bool border, bool display);

//����λ��
static int FlagPos[2][Chess_H][Chess_W] = { 0 };
//	��·λ��
const int Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{2, 1, 2, 1, 2},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{3, 1, 2, 1, 3},
	{1, 0, 1, 0, 1},
	{3, 1, 2, 1, 3},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{2, 1, 1, 1, 2},
	{0, 0, 0, 0, 0}
};

//	��Ӫλ��
const bool Station[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
};

// ���ɲ����ƶ���λ��
const bool SpecialPos[Chess_H][Chess_W]{
	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1}
};
//	���������ĸ�����
const int HV_DirectX[4] = { 1,0,0,-1 };
const int HV_DirectY[4] = { 0,1,-1,0 };

//	�ԽǷ���
const int Cross_DirectX[4] = { 1,1,-1,-1 };
const int Cross_DirectY[4] = { 1,-1,1,-1 };


//	��·λ��
//	��·��ͨ����
enum class HighwayConn { full, half, none };

//	·����ͨ����
enum class ConnWay { Railway, Highway, none };


//	˾��*1������*1��ʦ��*2���ó�*2���ų�*2��Ӫ��*2������*3���ų�*3������*3������*3��ը��*2������*1�� ��25ö
const int chessClassNum = 12;
enum class chessClass { none, zhadan, dilei, junqi, gongbing, pai, lian, ying, tuan, lv, shi, jun, siling };


//	�ַ�

const std::map<char, chessClass> chessMap{
	{BLANK,chessClass::none},
	{'a',chessClass::siling},
	{'A',chessClass::siling},
	{'j',chessClass::jun},
	{'J',chessClass::jun},
	{'s',chessClass::shi},
	{'S',chessClass::shi},
	{'v',chessClass::lv},
	{'V',chessClass::lv},
	{'t',chessClass::tuan},
	{'T',chessClass::tuan},
	{'y',chessClass::ying},
	{'Y',chessClass::ying},
	{'l',chessClass::lian},
	{'L',chessClass::lian},
	{'p',chessClass::pai},
	{'P',chessClass::pai},
	{'g',chessClass::gongbing},
	{'G',chessClass::gongbing},
	{'d',chessClass::dilei},
	{'D',chessClass::dilei},
	{'z',chessClass::zhadan},
	{'Z',chessClass::zhadan},
	{'f',chessClass::junqi},
	{'F',chessClass::junqi}
};


const std::map<char, int> chessNum{
	{BLANK,0},
	{'a',1},
	{'A',2},
	{'j',3},
	{'J',4},
	{'s',5},
	{'S',6},
	{'v',7},
	{'V',8},
	{'t',9},
	{'T',10},
	{'y',11},
	{'Y',12},
	{'l',13},
	{'L',14},
	{'p',15},
	{'P',16},
	{'g',17},
	{'G',18},
	{'d',19},
	{'D',20},
	{'z',21},
	{'Z',22},
	{'f',23},
	{'F',24}
};





//	���̸�������
enum class BoardClass {
	camp,		//	��ͨ��Ӫ
	frontline,		//	ǰ��
	station,		//	��Ӫ
	headquarter,		//	��Ӫ
	empty,		//	���������򣬳��Ӻ���֮��
};

//	���̲���
const int Field[Chess_H][Chess_W] = {
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::frontline, (int)BoardClass::empty,(int)BoardClass::frontline,(int)BoardClass::empty,(int)BoardClass::frontline},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp}
};
