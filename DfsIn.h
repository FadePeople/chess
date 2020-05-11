#pragma once
int wylcb(Map cMap[12][5], int Pro[25][14], int deep, char *cInMessage)
{
	int move[4];
	int allmove[200][4], iSaMove[40][2];
	int i, j, num, num1, i1, j1, k = 0;
	int mn;//最小值
	Map cmap[12][5];
	Map ncp[12][5];//new cMap
	//ncp=cMap
	for (int k1 = 0; k1 < 12; k1++) {
		for (int k2 = 0; k2 < 5; k2++) {
			ncp[k1][k2] = cMap[k1][k2];
		}
	}
	for (i = 0; i < 12; i++)
		for (j = 0; j < 5; j++)
		{
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
							cmap[i1][j1] = cMap[i1][j1];
					}
					num = SapperRail(iSaMove, cmap, i, j, 0);
					for (num1 = 1; num1 < num; num1++)
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = iSaMove[num1][0];
						allmove[k][3] = iSaMove[num1][1];
						k++;
					}
				}
				//可以前移:不在第一行,不在山界后,前方不是己方棋子,前方不是有棋子占领的行营
				if (i > 0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j;
					k++;
					if ((j == 0 || j == 4) && i > 0 && i < 11)
					{
						for (i1 = i - 1; i1 > 0; i1--)
						{
							if (cMap[i1][j].chess == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
							}
							else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess == 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
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
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j - 1;
					k++;
					//是否在1,5,6,10铁道上
					if (i == 1 || i == 5 || i == 6 || i == 10)
					{
						for (int i1 = j - 1; i1 >= 0; i1--)
						{
							if (cMap[i][i1].chess == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
							}
							else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
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
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j + 1;
					k++;
					//是否在1,5,6,10铁道上
					if (i == 1 || i == 5 || i == 6 || i == 10)
					{
						for (int i1 = j + 1; i1 < 5; i1++)
						{
							if (cMap[i][i1].chess == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
							}
							else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
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
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j;
					k++;
					//可以在铁轨两侧向后移动，后方不是己方旗子，不是第一行，不在最后一行
					if ((j == 0 || j == 4) && i > 0 && i < 11)
					{
						for (i1 = i + 1; i1 < 11; i1++)
						{
							if (cMap[i1][j].chess == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
							}
							else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
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
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//可以左后移：左后方不是己方旗子，不是已占有的行营
				if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//可以右前移：右前方不是己方旗子，不是已占有的行营
				if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j + 1;
					k++;
				}
				//可以右后移：右后方不是己方旗子，不是已占有的行营
				if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j + 1;
					k++;
				}
			}
		}
	int score = -0x3f3f3f3f;
	mn = -0x3f3f3f3f;
	for (i = 0; i < k; i++)
	{
		//当前这么走的分
		int score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, deep);

		//这里还没有加随机函数，dfs尽力优化
		//pinggu函数有问题，需要仔细优化一下
		//以上问题解决差不多了

		if (RandKind == 0)
			score1 += spe1(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 1)
			score1 += spe2(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 2)
			score1 += spe3(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 3)
			score1 += spe4(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 4)
			score1 += spe5(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 5)
			score1 += spe6(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, cInMessage);
		else if (RandKind == 6)
			score1 += spe7(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 7)
			score1 += spe8(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
		else if (RandKind == 8)
			score1 += spe9(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);


		if (score1 > mn) {
			//刷新棋盘
			Map mm = ncp[allmove[i][0]][allmove[i][1]];
			ncp[allmove[i][0]][allmove[i][1]] = ncp[allmove[i][2]][allmove[i][3]];
			ncp[allmove[i][2]][allmove[i][3]] = mm;
			//深搜的分数和
			int score2 = dfs(Pro, ncp, deep + 1, cInMessage);
			//恢复
			mm = ncp[allmove[i][0]][allmove[i][1]];
			ncp[allmove[i][0]][allmove[i][1]] = ncp[allmove[i][2]][allmove[i][3]];
			ncp[allmove[i][2]][allmove[i][3]] = mm;
			///求最大值
			score = max(score, score1 + score2);
			mn = score1;
		}
	}
	memset(allmove, 0, sizeof(allmove));
	return score;
}
//深搜函数 
int dfs(int Pro[25][14], Map cMap[12][5], int deep, char *cInMessage)
{
	if (deep == 3)
		return 0;
	else {
		int score1 = wylcb(cMap, Pro, deep, cInMessage);
		if (score1 == -1) {
			score1 = 100000;
		}
		return score1;
	}
}
//横向标记
int cir_markers_long(Map cMap[12][5], int intmap[12][5], int x, int y)
{
	if (y < 0 || y>4)
		return 0;
	else if (cMap[x][y].chess == '0') {
		intmap[x][y] = 3;
		cir_markers_long(cMap, intmap, x, y + 1);
		cir_markers_long(cMap, intmap, x, y - 1);
	}
	else
		return 0;

}
//纵向标记
int cir_markers_tran(Map cMap[12][5], int intmap[12][5], int x, int y)
{
	if (x > 10)
		return 0;
	else if (cMap[x][y].chess == '0') {
		intmap[x][y] = 3;
		cir_markers_tran(cMap, intmap, x + 1, y);
	}
	else
		return 0;
}

int A_Out(Map cMap[12][5], int intmap[12][5])
{
	int flag = 0;
	if (cMap[0][1].chess == 'L') {
		if (cMap[1][1].chess == '0') {
			cir_markers_long(cMap, intmap, 1, 1);
			for (int i = 0; i < 5; i++) {
				if (intmap[1][i] != 0)
					intmap[1][i]--;
			}
			intmap[1][1] = 1;
			if (intmap[1][0]) {
				cir_markers_tran(cMap, intmap, 2, 0);
				flag = 1;
			}
			if (intmap[1][4]) {
				cir_markers_tran(cMap, intmap, 2, 4);
				flag = 1;
			}
			if (cMap[2][1].chess == '0') {
				for (int i = 2; i < 4; i++) {
					for (int j = 0; j < 3; j++) {
						if (cMap[i][j].chess == '0') {
							intmap[i][j] = 3;
							flag = 1;
						}
					}
				}
				intmap[2][1] = 2;
			}
		}
		if (cMap[0][0].chess == '0') {
			intmap[0][0] = 1;
			if (cMap[1][0].chess == '0') {
				intmap[1][0] = 2;
				cir_markers_tran(cMap, intmap, 2, 0);
				cir_markers_long(cMap, intmap, 1, 1);
				flag = 1;
				if (cMap[2][1].chess == '0') {
					intmap[2][1] = 3;
					flag = 1;
				}
			}
		}
		if (cMap[0][2].chess == '0') {
			intmap[0][2] = 1;
			if (cMap[1][2].chess == '0') {
				cir_markers_long(cMap, intmap, 1, 2);
				flag = 1;
				intmap[1][2] = 2;
				for (int i = 1; i < 4; i++) {
					if (cMap[2][i].chess == '0') {
						intmap[2][i] = 3;
						flag = 1;
					}
				}
			}
		}
		if (!flag)
			return 0;
		else
			return 1;
	}
	else if (cMap[0][3].chess == 'L') {
		if (cMap[1][3].chess == '0') {
			cir_markers_long(cMap, intmap, 1, 3);
			for (int i = 0; i < 5; i++) {
				if (intmap[1][i] != 0)
					intmap[1][i]--;
			}
			intmap[1][3] = 1;
			if (intmap[1][0]) {
				cir_markers_tran(cMap, intmap, 2, 0);
				flag = 1;
			}
			if (intmap[1][4]) {
				cir_markers_tran(cMap, intmap, 2, 4);
				flag = 1;
			}
			if (cMap[2][3].chess == '0') {
				for (int i = 2; i < 4; i++) {
					for (int j = 2; j < 5; j++) {
						if (cMap[i][j].chess == '0') {
							intmap[i][j] = 3;
							flag = 1;
						}
					}
				}
				intmap[2][3] = 2;
			}
		}
		if (cMap[0][4].chess == '0') {
			intmap[0][4] = 1;
			if (cMap[1][4].chess == '0') {
				intmap[1][4] = 2;
				cir_markers_tran(cMap, intmap, 2, 4);
				cir_markers_long(cMap, intmap, 1, 3);
				flag = 1;
				if (cMap[2][3].chess == '0') {
					intmap[2][3] = 3;
					flag = 1;
				}
			}
		}
		if (cMap[0][2].chess == '0') {
			intmap[0][2] = 1;
			if (cMap[1][2].chess == '0') {
				cir_markers_long(cMap, intmap, 1, 2);
				flag = 1;
				intmap[1][2] = 2;
				for (int i = 1; i < 4; i++) {
					if (cMap[2][i].chess == '0') {
						intmap[2][i] = 3;
						flag = 1;
					}
				}
			}
		}
		if (!flag)
			return 0;
		else
			return 1;
	}
	else
		return 0;
}
//半成品，不能和A*out接上，但是A*out可以自己用没问题
//deep传进来的时候已经走了一步，要传1，不能传0
int A_In(Map cMap[12][5], int Pro[25][14], int deep,int intmap[12][5],int ans)
{
	int move[4];
	int allmove[200][4], iSaMove[40][2];
	int i, j, num, num1, i1, j1, k = 0;
	Map cmap[12][5];
	if (A_Out(cMap, intmap)) {
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 5; j++)
			{
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
								cmap[i1][j1] = cMap[i1][j1];
						}
						num = SapperRail(iSaMove, cmap, i, j, 0);
						for (num1 = 1; num1 < num; num1++)
						{
							allmove[k][0] = i;
							allmove[k][1] = j;
							allmove[k][2] = iSaMove[num1][0];
							allmove[k][3] = iSaMove[num1][1];
							if (intmap[allmove[k][2]][allmove[k][3]] == -1) {
								intmap[allmove[k][2]][allmove[k][3]] = deep;
							}
							else {
								ans = min(ans, intmap[allmove[k][2]][allmove[k][3]] + deep);
							}
							k++;
						}
					}
					//可以前移:不在第一行,不在山界后,前方不是己方棋子,前方不是有棋子占领的行营
					if (i > 0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i - 1;
						allmove[k][3] = j;
						k++;
						if ((j == 0 || j == 4) && i > 0 && i < 11)
						{
							for (i1 = i - 1; i1 > 0; i1--)
							{
								if (cMap[i1][j].chess == '0')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i1;
									allmove[k][3] = j;
									k++;
								}
								else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess == 'X')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i1;
									allmove[k][3] = j;
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
						allmove[k][1] = j;
						allmove[k][2] = i;
						allmove[k][3] = j - 1;
						k++;
						//是否在1,5,6,10铁道上
						if (i == 1 || i == 5 || i == 6 || i == 10)
						{
							for (int i1 = j - 1; i1 >= 0; i1--)
							{
								if (cMap[i][i1].chess == '0')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i;
									allmove[k][3] = i1;
									k++;
								}
								else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i;
									allmove[k][3] = i1;
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
						allmove[k][1] = j;
						allmove[k][2] = i;
						allmove[k][3] = j + 1;
						k++;
						//是否在1,5,6,10铁道上
						if (i == 1 || i == 5 || i == 6 || i == 10)
						{
							for (int i1 = j + 1; i1 < 5; i1++)
							{
								if (cMap[i][i1].chess == '0')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i;
									allmove[k][3] = i1;
									k++;
								}
								else if (cMap[i][i1].chess >= 'A'&&cMap[i][i1].chess <= 'X')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i;
									allmove[k][3] = i1;
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
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i + 1;
						allmove[k][3] = j;
						k++;
						//可以在铁轨两侧向后移动，后方不是己方旗子，不是第一行，不在最后一行
						if ((j == 0 || j == 4) && i > 0 && i < 11)
						{
							for (i1 = i + 1; i1 < 11; i1++)
							{
								if (cMap[i1][j].chess == '0')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i1;
									allmove[k][3] = j;
									k++;
								}
								else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess <= 'X')
								{
									allmove[k][0] = i;
									allmove[k][1] = j;
									allmove[k][2] = i1;
									allmove[k][3] = j;
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
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i - 1;
						allmove[k][3] = j - 1;
						k++;
					}
					//可以左后移：左后方不是己方旗子，不是已占有的行营
					if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i + 1;
						allmove[k][3] = j - 1;
						k++;
					}
					//可以右前移：右前方不是己方旗子，不是已占有的行营
					if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i - 1;
						allmove[k][3] = j + 1;
						k++;
					}
					//可以右后移：右后方不是己方旗子，不是已占有的行营
					if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i + 1;
						allmove[k][3] = j + 1;
						k++;
					}
				}
			}
		}

	}
	return 0;
}
