//前期进攻，后期防守布局    chbihggkdeedcfkgiijafhjlj 
#pragma once 
/*针对该布局的特殊行棋*/

//倒数第二排小子死守不动，让对面工兵误撞
int Small_Nodong(Map cMap[12][5], int i0, int j0)
{
	int teshu=0;
	if (cMap[i0][j0].chess == 'h' || cMap[i0][j0].chess == 'g' || cMap[i0][j0].chess == 'j'&&i0 == 10 && (j0 == 0 || j0 == 4 || j0 == 2))
		return teshu;
}

//前期一路师长往前杀，后面炸弹保护
int	sz_sha(Map cMap[12][5], int i, int j, int i1, int j1)
{
	char mchess[25];
	int teshu=0;
	mychessdx(cMap, mchess);
	if (cMap[i][j].chess == 'c' && (i <= 9 && i >= 6) && (j == 0 || j == 4) && NumChess(cMap) >= 15) //师长在我方棋盘往前调
	{
		if ((j1 == 4 || j1 == 0) && (11 >= 2 && 11 <= 5))
			teshu += 5000;
	}
	else if (cMap[3][0].chess == 'c' || cMap[2][1].chess == 'c'&&IsFilledCamp(cMap, 2, 1))//师长撕到(3,0)接着撕到(2,0)
	{
		if (i1 == 2 && j1 == 0)
			teshu += 5000;
	}
	if (cMap[3][0].chess == 'c' || cMap[2][0].chess == 'c' && !IsFilledCamp(cMap, 2, 1))//师长占住对面后行营
		teshu += 5000;
	else if (cMap[2][1].chess == 'c')
		teshu -= 2000;
	return teshu;
}

//炸弹保护师长
int Pro_sz(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'k'&&Ina_step[0] == 2 && (Judge(i1, j1, 0, Pro) > 5000 || Judge(i1, j1, 1, Pro) > 5000) && (cInMessage[8] - '0') == 1) //敌方有大子吃我方师长
	{
		teshu += 5000;
	}
	return teshu;
}

//炸弹给我炸通一路，如果顺利的话可以骗对面司令吃我方炸弹
int Bomb_NB(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'k')
	{
		if ((Judge(i1, j1, 0, Pro) > 5000 || Judge(i1, j1, 1, Pro) > 5000) && (cInMessage[8] - '0') == 1) //我方被吃去炸
		{
			if (j1 == 0 || j1 == 4)
				teshu += 5000;
		}
		else if (i1 == 1 && j1 == 0 && cMap[1][0].chess == '0') //炸弹去(1,0)
		{
			teshu += 10000;
		}
		else if (i1 == 0 && (j1 == 0 || j1 == 4)) //炸弹优先炸（0,0）和（0,4）
		{
			teshu += 10000;
		}
		else if (i1 == 1 && (j1 == 1 || j1 == 2)) //如果可以的话去（1,1）或（1,2）
		{
			teshu += 5000;
		}
	}
	return teshu;
}

//我方军长配合师长和炸弹将对面中下路撕开
int Jz_To_middle(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'b')
	{
		if (qqqqqq == 0||qqqqqq==1) //我方第一步军长去莽（5，.2）
		{
			if (i1 == 5 && j1 == 2) 
			{
				teshu += 5000;
			}
		}
		else if (!IsFilledCamp(cMap, 4, 1)&&i1==4&&j1==1) //军长先进要莽穿一路的行营,不让对面可能有的炸弹进行营
			teshu += 5000;
		else if (i == 4 && j == 1 && IsOppChess(cMap, 3, 0) == 1 && IsOppChess(cMap, 4, 0) == 1)//我方在（4,1）行营
		{
			if (IsOppChess(cMap, 3, 0) == 1 && (cMap[4][1].chess == 'b' || cMap[4][1].chess == 'c') && !IsFilledCamp(cMap, 2, 1))
			{
				teshu += 5000;
			}
			else
				teshu += 2000;
		}
		else if (j1 == 0&&i1>=2&&i1<=5) //吃通这一路
		{
			teshu += 5000;
		}
	}
	return teshu;
}

//右侧前期司令防守
//暂时不用
void Ritgt_Pro(char *cInMessage, Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (NumChess(cMap)>15)
	{
		if (cMap[6][4].chess == 'a') //司令在（6,4）
		{
			if ((cInMessage[8] - '0') == 0) //对面小子撞我司令
			{
				if (i1 == 7 && j1 == 3) //回营
					teshu += 10000;
				else if (i1 == 7 && (j1 == 2 || j1 == 3)) //回不了营，回山界后
					teshu += 5000;
			}
		}
		else if (cMap[7][3].chess == 'a')  //司令已经在行营
		{
			if (cMap[6][4].chess != 'X'&&cMap[7][4].chess != 'X') //右侧无敌方子，进不了你行营，司令出行营吃子
			{
				if (IsOppChess(cMap, 6, 2) || IsOppChess(cMap, 6, 3))
					teshu += 5000;
			}
			else if (cMap[6][4].chess != 'X' && (i1 == 7 || i1 == 8) && j1 == 4)  //我方有子堵住对方可能的炸弹，司令可以吃对面子
			{
				teshu += 5000;
			}
			else
			{
				if (i1 == 8 && j1 == 2) //占中行营
				{
					teshu += 50000;
				}
			}
		}
	}
	else //后期向我方军棋方向防守，防止对面偷家
	{
		if (cMap[7][3].chess == 'a')
		{
			if (i1 == 8 && j1 == 2)
				teshu += 5000;
		}
		else if (cMap[8][2].chess == 'a')  //我司令在我中行营
		{
			if (cMap[11][1].chess == 'l') //我方军棋在左下方
			{
				if (i1 == 9 && j1 == 1)
					teshu += 5000;
			}
			else if (cMap[11][3].chess == 'l') //我方军棋在右下方
			{
				if (i1 == 9 && j1 == 3)
					teshu += 5000;
			}
		}
		else if (cMap[9][1].chess == 'a')
		{
			if (cMap[10][0].chess == 'X' || cMap[10][0].chess == '0') //策略：后期司令守在军棋一侧保护，待时机攻到对面掏军棋
				teshu += 5000;
			if (cMap[10][j1].chess == 'X')
				teshu += 5000;
		}
		else if (cMap[9][3].chess == 'a')
		{
			if (cMap[10][4].chess == 'X' || cMap[10][5].chess == '0') //策略：后期司令守在军棋一侧保护，待时机攻到对面掏军棋
				teshu += 5000;
			if (cMap[10][j1].chess == 'X')
				teshu += 5000;
		}
	}
}

//工兵从莽穿的一侧挖雷
int Gb_Go(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'i')
	{
		if (cMap[0][1].chess == 'L')
		{
			if (i1 == 0 && j1 == 1)
				teshu += 500000;
		}
		else if (cMap[0][3].chess == 'L')
		{
			if (i1 == 0 && j1 == 3)
				teshu += 500000;
		}
		else if ((j1 == 1 || j1 == 3) && i == 1)
		{
			if (Judge(i1, j1, 9, Pro) > 4000)
				teshu += 10000;
		}
		return teshu;
	}
}


//后期有时机司令配合我方子夺军旗
int To_flag(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[0][1].chess == 'L')
	{
		if (cMap[0][0].chess == '0') //对面军棋左侧没子
		{
			for (int ii = 2; ii <= 10; ii++)
			{
				if (cMap[ii][0].chess == 'a' || cMap[ii][0].chess == 'b')
				{
					if (i1 == 1 && j1 == 0&&cMap[1][0].chess=='0') //下军旗
						teshu += 50000;
				}
			}
			if ((i1 == 0 && j1 == 0)||(cMap[0][2].chess=='0'&&i1==0&&j1==2)) //去（0,0）或（0,2）
			{
				teshu += 500000;
			}
		}
		if (cMap[0][2].chess == '0'&&i1 == 0 && j1 == 2) //去中间夺军旗
		{
			teshu += 50000;
		}
		if (cMap[1][0].chess == 'k') //炸弹在此莽通去对面军棋的路
		{
			if (i1 == 1 && j1 == 1)
				teshu += 500000;
			if (i1 == 0 && j1 == 0)
				teshu += 600000;
		}
		if (i1 == 0 && j1 == 1) //夺军旗
			teshu += 1000000;
	}
	else if (cMap[0][3].chess == 'L')
	{
		if (cMap[1][4].chess == '0')
		{
			if (i1 == 1 && j1 == 4 && (cMap[i][j].chess == 'a' || cMap[i][j].chess == 'b' || cMap[i][j].chess == 'k'))
				teshu += 50000;
		}
		if (cMap[1][4].chess == 'k') //炸弹在此莽通去对面军棋的路
		{
			if (i1 == 1 && j1 == 3)
				teshu += 50000;
			if (i1 == 0 && j1 == 4)
				teshu += 60000;
		}
		if (cMap[0][4].chess == '0') //下军棋封杀
		{
			if (i1 == 0 && j1 == 4)
				teshu += 50000;
		}
		if (cMap[1][3].chess == '0')
		{
			if(i1==1&&j1==3)
				teshu += 50000;
		}
		if (cMap[0][2].chess == '0'&&i1 == 0 && j1 == 2) //去中间夺军旗
		{
			teshu += 50000;
		}
		if (i1 == 0 && j1 == 3) //夺军旗
			teshu += 1000000;
	}
	return teshu;
}


//对面大子来吃我方子，用一个工兵去撞对面后面的炸弹
int GB_NB(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if ((cInMessage[8] - '0') == 1)  //我方被吃掉
	{
		if (NumOppChess(cMap) >= 20)
		{
			//对方大子到我方（7,0）或（8,0）
			if ((Judge(7, 0, 3, Pro) + Judge(7, 0, 3, Pro) + Judge(7, 0, 3, Pro)) > 9000 || (Judge(8, 0, 3, Pro) + Judge(8, 0, 3, Pro) + Judge(8, 0, 3, Pro)) > 9000)
			{
				if (((x11 == 5 && y11 == 0) || (x11 == 6 && y11 == 0)) && ((x21 == 7 && y21 == 0) || (x21 == 8 && y21 == 0)))
					teshu += 50000;
			}
			//对方大子到我方（7,4）或（8,4）
			else if ((Judge(7, 4, 3, Pro) + Judge(7, 4, 3, Pro) + Judge(7, 4, 3, Pro)) > 9000 || (Judge(8, 4, 3, Pro) + Judge(8, 4, 3, Pro) + Judge(8, 4, 3, Pro)) > 9000)
			{
				if (((x11 == 5 && y11 == 4) || (x11 == 6 && y11 == 4)) && ((x21 == 7 && y21 == 4) || (x21 == 8 && y21 == 4)))
					teshu += 50000;
			}
		}
	}
	return teshu;
}

//针对该布阵后期司令大子护旗
int Defend_my(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	char mchess[25];
	mychessdx(cMap, mchess);
	if (cMap[11][3].chess == 'l')//军旗在右下
	{
		if (cMap[i][j].chess == 'a')
		{
			if (i == 6 && j == 4)
			{
				if ((huang1 == 1 && i1 == 7 && j1 == 3) || ((mchess[1] != 'b' || cMap[7][2].chess == '0') && i1 == 7 && j1 == 3 && cMap[6][2].chess == 'X') || (NumChess(cMap) <= 19 && i1 == 7 && j1 == 3))
					teshu += 100000;
				else
					teshu -= 100000;
			}
		}
		if (cMap[6][2].chess == 'X'&&cMap[7][3].chess == 'a' && (mchess[1] != 'b'))	//对方强攻，吃子，司令回1营
		{
			if (i == 7 && j == 3 && i1 == 6 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[6][2].chess == 'a')
		{
			if (i == 6 && j == 2 && i1 == 7 && j1 == 3)
				teshu += 10000;
		}
		if (cMap[7][2].chess == 'X'&&cMap[7][3].chess == 'a'&&mchess[1] != 'b')//吃子后，司令落2营
		{
			if (i == 7 && j == 3 && i1 == 7 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[7][2].chess == 'a'&&huang2 == 1)
		{
			if (i == 7 && j == 2 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}

		if ((mchess[1] != 'b'&& cMap[7][3].chess == 'a' && cMap[6][2].chess != 'X' && cMap[7][2].chess != 'X') || (cMap[7][3].chess == 'a' && huang1 == 1) || (NumChess(cMap) <= 19))//回2行营
		{
			if (i == 7 && j == 3 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}
		if (cMap[8][2].chess == 'a') //司令落2营后，炸弹先行营
		{
			if (cMap[8][3].chess == 'k'&&i == 8 && j == 3 && i1 == 7 && j1 == 3)
				teshu += 15000;
		}
		if (cMap[8][2].chess == 'a')//回3行营
		{
			if (i == 8 && j == 2 && i1 == 9 && j1 == 3)
				if (cMap[7][2].chess == 'X' && cMap[8][4].chess != 'X' && cMap[9][4].chess != 'X' && cMap[8][3].chess != 'X' && cMap[10][4].chess != 'X' && cMap[10][3].chess != 'X' && cMap[10][2].chess != 'X')
					teshu -= 8000;
				else
					teshu += 8000;
		}
		if (cMap[6][4].chess == 'a' || cMap[7][3].chess == 'a' || cMap[8][2].chess == 'a')//不允许其他棋子占据行营
		{
			if ((i1 == 7 && j1 == 3) || (i1 == 8 && j1 == 2) || (i1 == 9 && j1 == 3))
				teshu -= 8000;
		}
	}
	if (cMap[11][0].chess=='l')//军旗在左下
	{
		if (cMap[i][j].chess == 'a')
		{
			if (i == 6 && j == 0)
			{
				if ((huang1 == 1 && i1 == 7 && j1 == 1) || ((mchess[1] != 'b' || cMap[7][2].chess == '0') && i1 == 7 && j1 == 1 && cMap[6][2].chess == 'X') || (NumChess(cMap) <= 19 && i1 == 7 && j1 == 1))
					teshu += 100000;
				else
					teshu -= 100000;
			}
		}
		if (cMap[6][2].chess == 'X'&&cMap[7][1].chess == 'a' && (mchess[1] != 'b'))//对方强攻，吃子，司令回1营
		{
			if (i == 7 && j == 1 && i1 == 6 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[6][2].chess == 'a')
		{
			if (i == 6 && j == 2 && i1 == 7 && j1 == 1)
				teshu += 10000;
		}
		if (cMap[7][2].chess == 'X'&&cMap[7][1].chess == 'a'&&mchess[1] != 'b')//吃子后，司令落2营
		{
			if (i == 7 && j == 1 && i1 == 7 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[7][2].chess == 'a'&&huang2 == 1)
		{
			if (i == 7 && j == 2 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}

		if ((mchess[1] != 'b'&& cMap[7][1].chess == 'a' && cMap[6][2].chess != 'X' && cMap[7][2].chess != 'X') || (cMap[7][1].chess == 'a' && huang1 == 1) || (NumChess(cMap) <= 19))//回2行营
		{
			if (i == 7 && j == 1 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}
		if (cMap[8][2].chess == 'a') //司令落2营后，炸弹先行营
		{
			if (cMap[8][1].chess == 'k'&&i == 8 && j == 1 && i1 == 7 && j1 == 1)
				teshu += 15000;
		}
		if (cMap[8][2].chess == 'a')//回3行营
		{
			if (i == 8 && j == 2 && i1 == 9 && j1 == 1)
				if (cMap[7][2].chess == 'X' && cMap[8][0].chess != 'X' && cMap[9][0].chess != 'X' && cMap[8][1].chess != 'X' && cMap[10][0].chess != 'X' && cMap[10][1].chess != 'X' && cMap[10][2].chess != 'X')
					teshu -= 8000;
				else
					teshu += 8000;
		}
		if (cMap[6][0].chess == 'a' || cMap[7][1].chess == 'a' || cMap[8][2].chess == 'a')//不允许其他棋子占据行营
		{
			if ((i1 == 7 && j1 == 1) || (i1 == 8 && j1 == 2) || (i1 == 9 && j1 == 1))
				teshu -= 8000;
		}
	}
	return teshu;
}

int spe6(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], char *cInMessage)
{
	int score=0;
	score += Bomb_NB(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Defend_my(cMap, i, j, i1, j1, Pro);
	score += GB_NB(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Gb_Go(cMap, i, j, i1, j1, Pro);
	score+=Jz_To_middle(cMap, i, j, i1, j1, Pro);
	score+=Pro_sz(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Small_Nodong(cMap, i, j);
	score += To_flag(cMap, i, j, i1, j1, Pro);
	score += sz_sha(cMap, i, j, i1, j1);
	return score;
}
