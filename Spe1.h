#pragma once
int spe1(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5])
{
	int spe1score = 0;
	FILE *fp = fopen("沈阳航空航天大学.txt", "a");
	//DefendFlag
	int ii = 10, jj, Score = 10000000;
	char ChessRank[25];
	if (cMap[11][1].chess == 'l')
		jj = 1;
	else
		jj = 3;
	if ((IsOppChess(cMap, ii, jj)) && ii == i1 && jj == j1 || (IsOppChess(cMap, ii, 2) && i1 == ii && j1 == 2))
	{
		mychessdx(cMap, ChessRank);
		for (int k = 0; k < NumChess(cMap); k++)
			if (cMap[i][j].chess == ChessRank[k])
				spe1score += Score - k;
	}
	// DefendLeft
	ii = 6;
	jj = 0;
	Score = 20000;
	if (cMap[7][1].chess == 'k' || cMap[7][0].chess == 'k')
	{
		if (i == ii && j == jj)
		{
			fprintf(fp, "堵左翼影响后的分值 -50000");
			spe1score += -50000;
		}
		if (cMap[ii][jj].chess == '0' && i1 == ii && j1 == jj)
		{
			for (int k = 0; k < NumChess(cMap); k++)
				if (cMap[i][j].chess == ChessRank[k])
				{
					fprintf(fp, "堵左翼影响后的分值 %d", Score - k);
					spe1score += Score - k;
				}
		}
	}
	//DefendRight
	ii = 6;
	jj = 4;
	Score = 50000;
	if (cMap[7][3].chess == 'k' || cMap[7][4].chess == 'k')
	{
		if (i == ii && j == jj)
		{
			fprintf(fp, "堵右翼影响后的分值 -50000");
			spe1score += -50000;
		}
		if (cMap[ii][jj].chess == '0' && i1 == ii && j1 == jj)
		{
			for (int k = 0; k < NumChess(cMap); k++)
				if (cMap[i][j].chess == ChessRank[k])
				{
					fprintf(fp, "堵右翼影响后的分值 %d", Score - k);
					spe1score += Score - k;
				}
		}
	}
	//AttackFor31
	//针对这种布局，拉炸弹出来师长往前撞
	if (Ina_step[0] == 2 && Ina_step[1] > 15)
	{
		if (i == 7 && j == 0 && cMap[i][j].chess != 'k'&&i1 > 7 && j1 == 0)
			spe1score += 50000;
		if (IsMyChess(cMap, 6, 0))
			if (cMap[i][j].chess == 'k' && j1 == 0 && i1 == 7 && cMap[7][0].chess != 'X')
			{
				fprintf(fp, "AttackFor31影响的分值 50000");
				spe1score += 50000;
			}
		if (i == 6 && j == 0)
		{
			bool Flag = 0;
			for (ii = 8; ii > 6; ii--)
				if (cMap[ii][0].chess == 'k')
				{
					Flag = 1;
					break;
				}
			if (Flag)
			{
				if (IsOppChess(cMap, i1, j1) && j1 == 0)
				{
					fprintf(fp, "AttackFor31影响的分值 80000");
					spe1score += 80000;
				}
			}
		}

		if (i == 7 && j == 4 && cMap[i][j].chess != 'k'&&i1 > 7 && j1 == 4)
			spe1score += 50000;
		if (IsMyChess(cMap, 6, 4))
			if (cMap[i][j].chess == 'k' && j1 == 4 && i1 == 7 && cMap[7][4].chess != 'X')
			{
				fprintf(fp, "AttackFor31影响的分值 50000");
				spe1score += 50000;
			}
		if (i == 6 && j == 4)
		{
			bool Flag = 0;
			for (ii = 8; ii > 6; ii--)
				if (cMap[ii][4].chess == 'k')
				{
					Flag = 1;
					break;
				}
			if (Flag)
			{
				if (IsOppChess(cMap, i1, j1) && j1 == 4)
				{
					fprintf(fp, "AttackFor31影响的分值 80000");
					spe1score += 80000;
				}
			}
		}
	}
	//原评估内特殊行棋
	char mchess[25];           //用于将我方棋子按棋力从大到小排序并保存
	int teshu = 0;
	//司令碰子回营
	mychessdx(cMap, mchess);
	if (buzhen == 1)//军旗在右下
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
		if (cMap[6][2].chess == 'X'&&cMap[7][3].chess == 'a' && (mchess[1] != 'b'))//对方强攻，吃子，司令回1营
		{
			if (i == 7 && j == 3 && i1 == 6 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;//？？？？？？？？
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
	if (buzhen == 2)//军旗在左下
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
	//糖醋小排
	//扩充
	if (cMap[i][j].chess == 'h')
	{
		if (buzhen == 1 && i == 11 && j == 0)
			if (cMap[i - 1][j].chess == 'X'&&i1 == i - 1)
				teshu += 5000;
		if (buzhen == 2 && i == 11 && j == 4)
			if (cMap[i - 1][j].chess == 'X'&&i1 == i - 1)
				teshu += 5000;
		if (buzhen == 1 && i == 10 && j == 0 && i1 == 1 && cMap[i1][j].chess == 'X')
			teshu += 3000;
		if (buzhen == 2 && i == 10 && j == 4 && i1 == 1 && cMap[i1][j].chess == 'X')
			teshu += 3000;
	}
	//军长封堵中路
	if (cMap[i][j].chess == 'b')
	{
		if (i == 7 && j == 2)
		{
			if (cMap[6][2].chess >= 'c'&&cMap[6][2].chess <= 'i' || cMap[6][2].chess == '0')
			{
				teshu -= 3000;
				if ((buzhen == 1 && cMap[9][3].chess == 'a') || (buzhen == 2 && cMap[9][1].chess == 'a') || mchess[0] != 'a')
					teshu += 3000;
				if (cMap[8][1].chess == 'X'&&i1 == 8 && j1 == 2)
					teshu += 7000;
			}
			if (cMap[6][2].chess == 'X'&&Judge(6, 2, 10, Pro) < 3000 && Judge(6, 2, 0, Pro) < 3000 && Judge(6, 2, 1, Pro) < 3000 && i1 == 6 && j1 == 2)
				teshu += 8000;
		}
		if (i == 6 && j == 2)
		{
			if (i1 == 7 && j1 == 2 && cMap[5][2].chess == 'X')
				teshu += 8000;
		}
		if (i == 8 && j == 2 && ((buzhen == 1 && cMap[9][3].chess == 'a') || (buzhen == 2 && cMap[9][1].chess == 'a')))
		{
			teshu -= 5000;
			if (cMap[8][3].chess == 'X'&&buzhen == 1 && cMap[9][3].chess == 'a'&&i1 == 8 && j1 == 3 && Judge(8, 3, 10, Pro) < 3000 && Judge(8, 3, 0, Pro) < 3000 && Judge(8, 3, 1, Pro) < 3000)
				teshu += 5000;
			if (cMap[9][2].chess == 'X'&&i1 == 9 && j1 == 2 && Judge(9, 2, 10, Pro) < 3000 && Judge(9, 2, 0, Pro) < 3000 && Judge(9, 2, 1, Pro) < 3000)
				teshu += 5000;
			if (cMap[8][1].chess == 'X'&&buzhen == 2 && cMap[9][1].chess == 'a'&&i1 == 8 && j1 == 1 && Judge(8, 1, 10, Pro) < 3000 && Judge(8, 1, 0, Pro) < 3000 && Judge(8, 1, 1, Pro) < 3000)
				teshu += 5000;
			if (cMap[7][2].chess == 'X'&&cMap[8][1].chess != 'X'&&cMap[8][3].chess != 'X'&&Judge(7, 2, 10, Pro) < 3000 && Judge(7, 2, 0, Pro) < 3000 && Judge(7, 2, 1, Pro) < 3000)
				teshu += 5000;
		}
	}
	fprintf(fp, "\n军长封堵中路的特殊分 %d ", teshu);
	//静若处子 动若脱兔——营长
	if (cMap[i][j].chess == 'f')
	{
		if (buzhen == 1 && i == 10 && j == 4)
			if (huang3 == 0)
				teshu -= 50000;
		if (buzhen == 2 && i == 10 && j == 0)
			if (huang3 == 0)
				teshu -= 50000;
	}
	//疑似重复
	//保护军旗
	if (cMap[11][1].chess == 'l')
	{
		if (cMap[10][1].chess == 'X' && i1 == 10 && j1 == 1)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
		if (cMap[10][0].chess == 'X' && cMap[11][0].chess == '0' && i1 == 10 && j1 == 0)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
		if (cMap[10][0].chess == 'X' && cMap[11][0].chess == 'j' && Judge(10, 0, 8, Pro) > 6000)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
	}
	if (cMap[11][3].chess == 'l')
	{
		if (cMap[10][3].chess == 'X' && i1 == 10 && j1 == 3)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
		if (cMap[10][4].chess == 'X' && cMap[11][4].chess == '0' && i1 == 10 && j1 == 4)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
		if (cMap[10][4].chess == 'X' && cMap[11][4].chess == 'j' && Judge(10, 4, 8, Pro) > 6000)
			teshu = teshu + (13 - (cMap[i][j].chess - 'a')) * 500;
	}
	fprintf(fp, "\n保护军旗影响后的特殊分 %d ", teshu);
	if (cMap[i][j].chess == 'k')
	{
		if (i == 8 && j == 3 && buzhen == 1)
		{
			if (i1 == 9 && j == 3)
				teshu -= 10000;
			else if (i1 == 8 && j1 == 2)
				teshu -= 10000;
			else if (i1 == 7 && j1 == 3 && cMap[6][4].chess == 'a')
				teshu -= 100000;
		}

		else if (i == 8 && j == 1 && buzhen == 2)
		{
			if (i1 == 9 && j == 1)
				teshu -= 10000;
			else if (i1 == 8 && j1 == 2)
				teshu -= 10000;
			else if (i1 == 7 && j1 == 1 && cMap[6][0].chess == 'a')
				teshu -= 100000;
		}
		if (i == 7 && j == 3 && cMap[6][4].chess >= 'c'&&cMap[6][4].chess <= 'f')
			if (j1 == 3 || j1 == 2)
				teshu -= 5000;
		if (i == 7 && j == 1 && cMap[6][0].chess >= 'c'&&cMap[6][0].chess <= 'f')
			if (j1 == 1 || j1 == 2)
				teshu -= 5000;
	}
	fclose(fp);
	spe1score += teshu;
	return spe1score;
}
