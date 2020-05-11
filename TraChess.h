#pragma once
//敌方某个位置的棋子的下一步行棋的所有位置
//不确定是不是工兵
int Oppnextmove(int i, int j, Map cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	char cmap[12][5];
	if (IsOppChess(cMap, i, j) && !IsBaseCamp(i, j))
	{
		//可以前移:不在第一行,不在山界后,前方不是己方棋子,前方不是有棋子占领的行营
		if (i > 0 && !IsAfterHill(i, j) && !IsOppChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j;
			k++;
			if ((j == 0 || j == 4) && i > 0 && i < 11)
			{
				for (i1 = i - 1; i1 > 0; i1--)
				{
					if (cMap[i1][j].chess == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
					}
					else if (cMap[i1][j].chess >= 'a' && cMap[i1][j].chess <= 'l')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//可以左移:不在最左列,左侧不是己方棋子,左侧不是被占用的行营
		if (j > 0 && !IsOppChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//是否在1,5,6,10铁道上
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j - 1; i1 >= 0; i1--)
				{
					if (cMap[i][i1].chess == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1].chess >= 'a'&&cMap[i][i1].chess <= 'l')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//可以右移:不在最右列,右侧不是己方棋子,右侧不是被占用的行营
		if (j < 4 && !IsOppChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//是否在1,5,6,10铁道上
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j + 1; i1 < 5; i1++)
				{
					if (cMap[i][i1].chess == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1].chess >= 'a'&&cMap[i][i1].chess <= 'l')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}

		//可以后移：不在最后一列，后方不是己方旗子，后面不是已占有的行营
		if (i < 11 && !IsBehindHill(i, j) && !IsOppChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//可以在铁轨两侧向后移动，后方不是己方旗子，不是第一行，不在最后一行
			if ((j == 0 || j == 4) && i > 0 && i < 11)
			{
				for (i1 = i + 1; i1 < 11; i1++)
				{
					if (cMap[i1][j].chess == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;

						k++;
					}
					else if (cMap[i1][j].chess >= 'a' && cMap[i1][j].chess <= 'l')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else  break;
				}

			}
		}
		//可以左前移：左前方不是已占有的行营，不是己方旗子
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//可以左后移：左后方不是己方旗子，不是已占有的行营
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//可以右前移：右前方不是己方旗子，不是已占有的行营
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//可以右后移：右后方不是己方旗子，不是已占有的行营
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}

	return k;
}
//己方某个位置的棋子的下一步行棋的所有位置
int nextmove1(int i, int j, Map cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	Map cmap[12][5];
	if (IsMyMovingChess(cMap, i, j) && !IsBaseCamp(i, j))  //己方不在大本营的可移动棋子
	{
		//工兵形棋
		if (cMap[i][j].chess == 'i' && IsRailway(i, j))
		{
			iSaMove[0][0] = i;
			iSaMove[0][1] = j;
			for (i1 = 0; i1 < 12; i1++)
			{
				for (j1 = 0; j1 < 5; j1++)
					cmap[i1][j1].chess = cMap[i1][j1].chess;
			}
			num = SapperRail(iSaMove, cmap, i, j, 0);
			for (num1 = 1; num1 < num; num1++)
			{
				allmove[k][0] = iSaMove[num1][0];
				allmove[k][1] = iSaMove[num1][1];
				k++;
			}
		}
		//可以前移:不在第一行,不在山界后,前方不是己方棋子,前方不是有棋子占领的行营
		if (i > 0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j;
			k++;
			if ((j == 0 || j == 4) && i > 0 && i < 11)
			{
				for (i1 = i - 1; i1 > 0; i1--)
				{
					if (cMap[i1][j].chess == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
					}
					else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess == 'X')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//可以左移:不在最左列,左侧不是己方棋子,左侧不是被占用的行营
		if (j > 0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//是否在1,5,6,10铁道上
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j - 1; i1 >= 0; i1--)
				{
					if (cMap[i][i1].chess == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//可以右移:不在最右列,右侧不是己方棋子,右侧不是被占用的行营
		if (j < 4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//是否在1,5,6,10铁道上
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j + 1; i1 < 5; i1++)
				{
					if (cMap[i][i1].chess == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}

		//可以后移：不在最后一列，后方不是己方旗子，后面不是已占有的行营
		if (i < 11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//可以在铁轨两侧向后移动，后方不是己方旗子，不是第一行，不在最后一行
			if ((j == 0 || j == 4) && i > 0 && i < 11)
			{
				for (i1 = i + 1; i1 < 11; i1++)
				{
					if (cMap[i1][j].chess == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;

						k++;
					}
					else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess <= 'X')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else  break;
				}

			}
		}
		//可以左前移：左前方不是已占有的行营，不是己方旗子
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//可以左后移：左后方不是己方旗子，不是已占有的行营
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//可以右前移：右前方不是己方旗子，不是已占有的行营
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//可以右后移：右后方不是己方旗子，不是已占有的行营
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}
	return k;
}