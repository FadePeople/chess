#pragma once				//上个头文件只编译一次

//棋盘分
int qipanfen[12][5] = {
	500 ,1000,600 ,1000,800,  //
	200 ,600 ,500 ,600 ,200,
	250 ,800 ,20  ,800 ,250,
	140 ,20  ,700 ,20  ,140,
	130 ,400 ,20  ,400 ,130,
	120 ,80  ,150 ,80  ,120,
	110 ,100 ,50 ,100 ,110,
	100 ,500 ,150  ,500 ,100,
	100 ,20  ,400 ,20  ,100,
	100 ,600 ,20  ,600 ,100,
	500 ,100 ,100 ,100 ,500,
	200 ,-1000 ,200 ,-1000 ,200 };
void jushipg(Map cMap[12][5], int Pro[25][14])
{
	if (cMap[11][1].chess == 'l')    ///己方军旗的位置
	{
		qipanfen[6][0] = 130;
		qipanfen[7][0] = 120;
		qipanfen[7][1] = 600;
		qipanfen[8][0] = 120;
		qipanfen[8][1] = 80;
		qipanfen[9][0] = 120;
		qipanfen[9][1] = 700;
		qipanfen[10][0] = 600;
		qipanfen[10][1] = 200;
	}
	if (cMap[11][3].chess == 'l')
	{
		qipanfen[6][4] = 130;
		qipanfen[7][4] = 120;
		qipanfen[7][3] = 600;
		qipanfen[8][4] = 120;
		qipanfen[8][3] = 80;
		qipanfen[9][4] = 120;
		qipanfen[9][3] = 700;
		qipanfen[10][4] = 600;
		qipanfen[10][3] = 200;
	}
	if (Pro[1][11] == 10000)  //敌方军旗的位置
	{
		qipanfen[0][3] = -10000;
		qipanfen[0][4] = -10000;
		qipanfen[0][1] = 10000;
		qipanfen[0][0] = 600;
		qipanfen[1][0] = 400;
		qipanfen[1][1] = 700;
		qipanfen[2][0] = 300;
		qipanfen[2][1] = 900;
		qipanfen[3][0] = 240;
		qipanfen[3][1] = 100;
		qipanfen[4][0] = 230;
		qipanfen[4][1] = 500;
		qipanfen[5][0] = 220;
	}
	if (Pro[3][11] == 10000)
	{
		qipanfen[0][1] = -10000;
		qipanfen[0][0] = -10000;
		qipanfen[0][3] = 10000;
		qipanfen[0][4] = 600;
		qipanfen[1][4] = 400;
		qipanfen[1][3] = 700;
		qipanfen[2][4] = 300;
		qipanfen[2][3] = 900;
		qipanfen[3][4] = 240;
		qipanfen[3][3] = 100;
		qipanfen[4][4] = 230;
		qipanfen[4][3] = 500;
		qipanfen[5][4] = 220;
	}
}
