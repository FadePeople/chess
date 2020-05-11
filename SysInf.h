#pragma once				//上个头文件只编译一次"
/* ************************************************************************ */
/* 函数功能：双方布局后棋局初始化											*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     char *cOutMessage 布局字符序列										*/
/* ************************************************************************ */
void InitMap(Map cMap[12][5], char *cOutMessage)
{
	int i, j, k;
	for (i = 0; i < 6; i++)	//标记对方棋子
		for (j = 0; j < 5; j++)
			if (IsMoveCamp(i, j))
				cMap[i][j].chess = '0';
			else
				cMap[i][j].chess = 'X';
	k = 6;
	for (i = 6; i < 12; i++)	//标记己方棋子
		for (j = 0; j < 5; j++)
			if (IsMoveCamp(i, j))
				cMap[i][j].chess = '0';
			else
				cMap[i][j].chess = cOutMessage[k++];
}
/* ************************************************************************ */
/* 函数功能：根据INFO指令,返回参赛队名										*/
/* 接口参数：																*/
/*     char *cInMessage 接收的INFO ver指令									*/
/*     char *cOutMessage 参赛队名											*/
/* ************************************************************************ */
void CulInfo(char *cInMessage, char *cVer, char *cOutMessage)
{
	strcpy(cVer, cInMessage + 5);																												//此语句没用
	strcpy(cOutMessage, "NAME The sword refers to the sky");
}
/* ************************************************************************ */
/* 函数功能：根据START指令,返回布局											*/
/* 接口参数：																*/
/*     char *cInMessage 接收的START first time steps指令					*/
/*     int *iFirst 先行权[0先行，1后行]										*/
/*     int *iTime 行棋时间限制(单位秒)[1000,3600]							*/
/*     int *iStep 进攻等待限制(单位步)[10,31]								*/
/*     char *cOutMessage 布局字符序列										*/
/* ************************************************************************ */
void CulArray(char *cInMessage, int *iFirst, int *iTime, int *iStep, char *cOutMessage)
{
	//memset(cOutMessage, '\0', sizeof(cOutMessage));
	fill(cOutMessage, cOutMessage + 200, '\0');
	FILE *fp;
	*iFirst = cInMessage[6] - '0';
	*iTime = cInMessage[8] - '0';
	*iTime = *iTime * 10 + (cInMessage[9] - '0');
	*iTime = *iTime * 10 + (cInMessage[10] - '0');
	*iTime = *iTime * 10 + (cInMessage[11] - '0');
	*iStep = cInMessage[13] - '0';
	*iStep = *iStep * 10 + (cInMessage[14] - '0'); 
	if (*iFirst == 0)	//先手	1	a司令,b军长,c师长,d旅长,e团长,f营长,g连长,h排长,i工兵,j地雷k炸弹,l军旗   cdgdckhkfiifebejagjihljhg    hegickfkcibefigjajdhdljhg
						//	strcpy(cOutMessage,"ARRAY cehiakbcdikegfgjjdifhhglj");         chdfckgkdiefabgjjiiejlghh           cdgdckhkfiifebejagjihljhg   cdedckfkfiiegbijajjghlhhg    cdedckfkfiiegbijajjghlhhg
	{
		rin();					//随机生成布阵
      	//RandKind=8;//测试哪个就等于这个头文件-1
		strcpy(cOutMessage, "ARRAY ");       //1.    cgdgckfkeiiefgbjajjdhlhhi   2.cgdgckekfiifeibjajjdhlhhg
		for (int flagi = 6; flagi < 6 + 25; flagi++) {
			cOutMessage[flagi] = buzhenout[RandKind][flagi - 6];
		}
		strcpy(cot, "first");
		fp=fopen("沈阳航空航天大学.txt","a");
		fprintf(fp,"先手是布局%d\n",RandKind);
		fclose(fp);
	}
	else if (*iFirst == 1)			//后手	1			chefckgkfiidgbjjidjeghhlj     hegickfkcibefigjajdhdljhg
	{
		//	strcpy(cOutMessage,"ARRAY hcgcgkikgfdfadbejiiejljhh");		chdfckgkdiefabijjgiejlghh    chdfckgkdiefabgjjiiejlghh   cdgdhkbkfiifecejagjihljhg
		rin();					//随机生成布阵
		//RandKind=8;//测试哪个就等于这个头文件-1
		strcpy(cOutMessage, "ARRAY ");       //1.       cgdgckfkeiiefgbjajjdhlhhi   2.cgdgckekfiifeibjajjdhlhhg
				//	strcpy(cOutMessage,"ARRAY hcgcgkikgfdfadbejiiejljhh");		chdfckgkdiefabijjgiejlghh    chdfckgkdiefabgjjiiejlghh   cdgdhkbkfiifecejagjihljhg
				//1.       cgdgckfkeiiefgbjajjdhlhhi   2.cgdgckekfiifeibjajjdhlhhg
		//后手	2			chefckgkfiidgbjjidjeghhlj     hegickfkcibefigjajdhdljhg
		for (int flagi = 6; flagi < 6 + 25; flagi++) {
			cOutMessage[flagi] = buzhenout[RandKind][flagi - 6];
		}
		Ina_step[0] = 1;
		strcpy(cot, "last");
		fp=fopen("沈阳航空航天大学.txt","a");
		fprintf(fp,"后手是布局%d\n",RandKind);
		fclose(fp);
	}
}
/* ************************************************************************ */
/* 函数功能：计算己方最佳着法(本程序为示例算法,请参赛选手自行改进算法)		*/
/* 接口参数：																*/
/*     char *cMap 棋盘局面													*/
/*     char *cInMessage 来自裁判的 GO 命令									*/
/*     char *cOutMessage 发给裁判的 BESTMOVE 命令							*/
/* ************************************************************************ */
void CulBestmove(Map cMap[12][5], char *cInMessage, char *cOutMessage, int Pro[25][14])
{
	strcpy(cOutMessage, "BESTMOVE A0A0");
	int move[4];
	int allmove[200][4], iSaMove[40][2];
	int i, j, num, num1, i1, j1, k = 0;
	Map cmap[12][5];
	Map ncp[12][5];//new cMap
	//ncp=cMap
	for (int k1 = 0; k1 < 12; k1++) {
		for (int k2 = 0; k2 < 5; k2++) {
			ncp[k1][k2] = cMap[k1][k2];
		}
	}
	int score1, score = -10000;
	//定式
	if (1)
	{
		//我方子在敌方军旗旁边
		if (cMap[0][1].chess == 'L')
		{
			if (IsMyMovingChess(cMap, 0, 0))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '0';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
			if (IsMyMovingChess(cMap, 0, 2))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '2';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
			if (IsMyMovingChess(cMap, 1, 1))
			{
				cOutMessage[9] = 'B';
				cOutMessage[10] = '1';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
		}
		if (cMap[0][3].chess == 'L')
		{
			if (IsMyMovingChess(cMap, 0, 4))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '4';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
			if (IsMyMovingChess(cMap, 0, 2))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '2';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
			if (IsMyMovingChess(cMap, 1, 3))
			{
				cOutMessage[9] = 'B';
				cOutMessage[10] = '3';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
		}

		if (cMap[0][0].chess >= 'e' && cMap[0][0].chess < 'j' && !IsMyChess(cMap, 0, 1))
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '0';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}
		if (cMap[0][2].chess >= 'e' && cMap[0][2].chess < 'j' && !IsMyChess(cMap, 0, 1))
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '2';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}
		if (cMap[1][1].chess >= 'e' && cMap[1][1].chess < 'j' && !IsMyChess(cMap, 0, 1))
		{
			cOutMessage[9] = 'B';
			cOutMessage[10] = '1';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}

		if (cMap[0][4].chess >= 'e' && cMap[0][4].chess < 'j' && !IsMyChess(cMap, 0, 3))
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '4';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
		if (cMap[0][2].chess >= 'e' && cMap[0][2].chess < 'j' && !IsMyChess(cMap, 0, 3))
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '2';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
		if (cMap[1][3].chess >= 'e' && cMap[1][3].chess < 'j' && !IsMyChess(cMap, 0, 3))
		{
			cOutMessage[9] = 'B';
			cOutMessage[10] = '3';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
	}
	FILE *fp;
	fp = fopen("沈阳航空航天大学.txt", "a");
	for (int m = 0; m < 12; m++)
	{
		for (int n = 0; n < 5; n++)
		{
			fprintf(fp, "%c ", cMap[m][n]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n\n\n%d,%d\n", Ina_step[0], Ina_step[1]);
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 14; j++)
			fprintf(fp, "%5d,", Pro[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);

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
	score = -0x3f3f3f3f;
	if (NumChess(cMap) > 15)
	{
		if (RandKind == 0) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe1(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
		else if (RandKind == 1) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe2(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
		else if (RandKind == 2) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe3(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
		else if (RandKind == 3) 
		{
			if (NumChess(cMap) > 18)
			{ 
				for (i = 0; i < k; i++)
				{
					score1 = spe4(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
					score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
					if ((score1) >= score)
					{
						if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
							continue;
						else
						{
							score = score1;
							move[0] = allmove[i][0];
							move[1] = allmove[i][1];
							move[2] = allmove[i][2];
							move[3] = allmove[i][3];
						}
					}
				}
			}
			else
			{
				for (i = 0; i < k; i++)
				{
					score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
					if ((score1) >= score)
					{
						if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
							continue;
						else
						{
							score = score1;
							move[0] = allmove[i][0];
							move[1] = allmove[i][1];
							move[2] = allmove[i][2];
							move[3] = allmove[i][3];
						}
					}
				}
			} 
		}
		else if (RandKind == 4) 
		{
			if (NumChess(cMap) > 18)
			{ 
				for (i = 0; i < k; i++)
				{
					score1 = spe5(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
					score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
					if ((score1) >= score)
					{
						if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
							continue;
						else
						{
							score = score1;
							move[0] = allmove[i][0];
							move[1] = allmove[i][1];
							move[2] = allmove[i][2];
							move[3] = allmove[i][3];
						}
					}
				}
			}
			else
			{
				for (i = 0; i < k; i++)
				{
					score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
					if ((score1) >= score)
					{
						if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
							continue;
						else
						{
							score = score1;
							move[0] = allmove[i][0];
							move[1] = allmove[i][1];
							move[2] = allmove[i][2];
							move[3] = allmove[i][3];
						}
					}
				}
			} 
		}
      	else if (RandKind == 5) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe6(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, cInMessage);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
      	else if (RandKind == 6) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe7(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
        else if (RandKind == 7) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe8(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
        else if (RandKind == 8) 
		{
			for (i = 0; i < k; i++)
			{
				score1 = spe9(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap);
				score1 += pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
				if ((score1) >= score)
				{
					if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
						continue;
					else
					{
						score = score1;
						move[0] = allmove[i][0];
						move[1] = allmove[i][1];
						move[2] = allmove[i][2];
						move[3] = allmove[i][3];
					}
				}
			}
		}
		/*score1 = dfs(Pro, cMap, 0);
		if ((score1) >= score)
		{
			if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
				continue;
			else
			{
				score = score1;
				move[0] = allmove[i][0];
				move[1] = allmove[i][1];
				move[2] = allmove[i][2];
				move[3] = allmove[i][3];
			}
		}*/

	}
	else
	{
		for (i = 0; i < k; i++)
		{
			score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, 0);
			if ((score1) >= score)
			{
				if ((allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3]) || (NoGrind.IsGrind(allmove[i], cMap[allmove[i][0]][allmove[i][1]].chess) && k != 1))
					continue;
				else
				{
					score = score1;
					move[0] = allmove[i][0];
					move[1] = allmove[i][1];
					move[2] = allmove[i][2];
					move[3] = allmove[i][3];
				}
			}
		}
	}
	cOutMessage[9] = move[0] + 'A';
	cOutMessage[10] = move[1] + '0';
	cOutMessage[11] = move[2] + 'A';
	cOutMessage[12] = move[3] + '0';
	memset(allmove, 0, sizeof(allmove));
	fp = fopen("沈阳航空航天大学.txt", "a");
	qqqqqq++;
	if (k)
	{
		fprintf(fp, "\nMove %c %d,%d,%d,%d,%d,%d\n\n", cMap[move[0]][move[1]].chess, move[0], move[1], move[2], move[3], score, cMap[move[0]][move[1]].Attr.IsFollowed);
		NoGrind.Pop(move, cMap[move[0]][move[1]].chess);           //记录我方目前走法
	}
	fclose(fp);
}
