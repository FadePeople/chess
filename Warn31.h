#pragma once
int _31Step(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], Map cmap[12][5], char mchess[])
{
	int sanyif = 0, score = 0;
	int k1, k2, k3;
	int allmove1[200][2], allmove2[200][2];
	int flag = 0, flag2 = 0;
	bool sanyi1 = false, sanyi2 = false, sanyi3 = false;

	if (Ina_step[0] == 2 && Ina_step[1] > 12 && Ina_step[1] <= 18)
	{
		if (cMap[i][j].chess >= 'e' && cMap[i][j].chess < 'i')
		{
			k1 = nextmove1(i1, j1, cmap, allmove1);	//判断棋盘上，己方大于工兵小于旅长的棋子能否在两步之内碰子，
			for (k2 = 0; k2 < k1; k2++)
			{
				if (cmap[allmove1[k2][0]][allmove1[k2][1]].chess >= 'A' && cmap[allmove1[k2][0]][allmove1[k2][1]].chess <= 'X')
					flag = 1;
			}
		}
		if (cMap[i1][j1].chess >= 'A' && cMap[i1][j1].chess <= 'X')
		{
			if (!IsMoveCamp(i, j) && cMap[i][j].chess >= 'e' && cMap[i][j].chess < 'i')//己方不再行营且小于旅长大于排长的棋子。碰子的分值最大
			{
				sanyif = 30000;
				sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
				sanyi1 = true;
			}
			else if (cMap[i][j].chess == mchess[0])//己方工兵不参与三十一步，己方最大棋子不参与三十一步
			{
				sanyif = 0;
				sanyi1 = false;
			}
			else if (cMap[i][j].chess == 'i')
			{
				if (walei(cMap, Pro))//判断工兵是否需要挖雷，不需要则，进行。三十一步
				{
					sanyi1 = true;
					sanyif = 40000;                     //////////////////////////////////////////
														//sanyif=sanyif+(cMap[i][j]-'a')*10;
				}
				else
				{
					sanyif = 0;
					sanyi1 = false;
				}
			}
			else if (IsMoveCamp(i, j) && weixie(i, j, i1, j1, Pro, cMap) < 0)//己方在行营的棋子	cMap[i][j]<'d'
			{
				sanyif = 20000;
				sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
				sanyi1 = false;
			}
			else if (cMap[i][j].chess == 'k')//己方在行营小于旅长的棋子	cMap[i][j]<'d'
			{
				sanyif = 20000;
				sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
				sanyi1 = false;
			}
			else//己方大于团长的棋子
			{
				sanyi1 = true;
				sanyif = 28000;
				if (Judge(i1, j1, 9, Pro) > 4000)
				{
					sanyif = 20000;
					sanyi1 = false;
				}
				sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;

			}
			//
			if (weixie(i, j, i1, j1, Pro, cMap) < 0)         //比自己大不走
				sanyif = sanyif - 5000;
		}
		if (sanyi1 == false)//第二步能碰到子
		{
			int f = 1;
			k1 = nextmove1(i1, j1, cmap, allmove1);
			for (k2 = 0; k2 < k1; k2++)
				if (cmap[allmove1[k2][0]][allmove1[k2][1]].chess >= 'A' && cmap[allmove1[k2][0]][allmove1[k2][1]].chess <= 'X')
				{
					sanyi2 = true;
					if (cMap[i][j].chess == mchess[0])//己方工兵不参与三十一步，己方最大棋子不参与三十一步
					{
						sanyif = 0;
						sanyi2 = false;
					}
					else if (cMap[i][j].chess == 'i')
					{
						if (walei(cMap, Pro))//判断工兵是否需要挖雷，不需要则，进行。三十一步
						{
							sanyif = 28000;                   ///////////////////////////////
															  //sanyif=sanyif+(cMap[i][j]-'a')*10;
						}
						else
							sanyif = 0;
					}
					else if (cMap[i][j].chess == 'k')
					{
						sanyif = 15000;
						sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
					}
					else if (cMap[i][j].chess >= 'e' && cMap[i][j].chess < 'i')
					{
						sanyif = 25000;
						sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
						if (weixie(i, j, i1, j1, Pro, cMap) < 0)         //比自己打不走
							sanyif = 20000;
					}
					else//己方大于团长的棋子
					{
						sanyif = 23000;
						if (Judge(allmove1[k2][0], allmove1[k2][1], 9, Pro) > 4000)
						{
							sanyif = 15000;
							sanyi2 = false;
						}
						sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
					}
				}
			if (sanyi2 == false && flag == 0)				//第三步能碰子
			{
				for (k2 = 0; k2 < k1; k2++)
				{
					cmap[allmove1[k2][0]][allmove1[k2][1]] = cmap[i1][j1];
					cmap[i1][j1].chess = '0';
					k3 = nextmove1(allmove1[k2][0], allmove1[k2][1], cmap, allmove2);
					for (int k4 = 0; k4 < k3; k4++)
						if (cmap[allmove2[k4][0]][allmove2[k4][1]].chess >= 'A' && cmap[allmove2[k4][0]][allmove2[k4][1]].chess <= 'X')
						{
							if (cMap[i][j].chess >= 'e' && cMap[i][j].chess < 'i')
							{
								sanyif = 20000;
								sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
								if (weixie(i, j, i1, j1, Pro, cMap) < 0)         //比自己打不走
									sanyif = 15000;
							}
							else if (cMap[i][j].chess == mchess[0])
								sanyif = 0;
							else if (cMap[i][j].chess == 'i')
							{
								if (walei(cMap, Pro))//判断工兵是否需要挖雷，不需要则进行。三十一步
								{
									sanyif = 22000;                  //////////////////////////////////////
									sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;
								}
								else
									sanyif = 0;
							}
							else
							{
								sanyif = 13000;
								sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;

							}
							sanyi3 = true;

						}
					cmap[i1][j1] = cmap[allmove1[k2][0]][allmove1[k2][1]];
					cmap[allmove1[k2][0]][allmove1[k2][1]].chess = '0';
				}
			}
		}
		if (NumOppChess(cMap) < 15)              //炸弹走31步
			if (Judge(2, 1, E_COMMANDER, Pro) > 6000 && Judge(2, 1, E_ARMYCOM, Pro) && Judge(2, 1, E_TEACOM, Pro))
				if (cMap[i][j].chess == E_BOOM)
					if (j1 == 0 && i1 < 5)
						sanyif = sanyif + 6000;


		switch (cMap[i][j].chess)
		{
		case M_BATCOM:sanyif = sanyif;
		case M_SAPCOM:sanyif = sanyif + 1000;
		case M_COMCOM:sanyif = sanyif + 1000;
		case M_PLACOM:sanyif = sanyif + 1000;          //就是没有break
		}
	}
	int f = 0;
	if (Ina_step[0] == 2 && Ina_step[1] > 18)
	{
		k1 = nextmove1(i1, j1, cmap, allmove1);
		for (k2 = 0; k2 < k1; k2++)//模拟下一步
		{
			if ((allmove1[k2][1] == 0 || allmove1[k2][1] == 4) && (allmove1[k2][0] > 0 && allmove1[k2][0] < 11))
				sanyif = 25000;
			if (cMap[allmove1[k2][0]][allmove1[k2][1]].chess == 'L')
				f = 1;
		}
		if (i1 > 0 && i1 < 11 && (j1 == 0 || j1 == 4))
			sanyif = 35000;
		if ((j == 0 || j == 4) && (i > 0 && i < 11))
			if (i1 == 1 && (j1 == 0 || j1 == 4))
				sanyif = 45000;

		if (cMap[i1][j1].chess == 'X')
		{
			sanyif = 60000;
			if (Judge(i1, j1, 9, Pro) > 3000)
				sanyif = sanyif - 10000;
		}
		if (i1 == 1 && (j1 == 1 || j1 == 3))
			sanyif = sanyif + 10000;
		if (i1 == 0 && j1 == 0)
			if (cMap[0][1].chess == 'X' || cMap[0][1].chess == 'L')
				sanyif = sanyif + 10000;
		if (i1 == 0 && j1 == 4)
			if (cMap[0][4].chess == 'X' || cMap[0][4].chess == 'L')
				sanyif = sanyif + 10000;
		if (cMap[i][j].chess == 'k')
			sanyif = sanyif - 1000;
		if ((Judge(1, 1, 9, Pro) < 50 || Judge(0, 0, 9, Pro) < 50) && j1 == 0)
			sanyif = sanyif + 500;
		if ((Judge(1, 3, 9, Pro) < 50 || Judge(0, 4, 9, Pro) < 50) && j1 == 4)
			sanyif = sanyif + 500;
		if (cMap[0][1].chess == 'L' && i1 == 1 && j1 == 1)
			sanyif = sanyif + 5000;
		if (cMap[0][3].chess == 'L' && i1 == 1 && j1 == 3)
			sanyif = sanyif + 5000;
		if (cMap[i][j].chess > mchess[0] && cMap[i][j].chess < 'j')
			sanyif = sanyif + (cMap[i][j].chess - 'a') * 10;

		if (NumOppChess(cMap) < 15)             //炸弹走31步
			if ((Judge(2, 1, E_COMMANDER, Pro) > 6000 && Judge(2, 1, E_ARMYCOM, Pro) && Judge(2, 1, E_TEACOM, Pro)) || (Judge(2, 3, E_COMMANDER, Pro) > 6000 && Judge(2, 3, E_ARMYCOM, Pro) && Judge(2, 3, E_TEACOM, Pro)))
				if (cMap[i][j].chess == E_BOOM)
					sanyif = sanyif + 4000;
		switch (cMap[i][j].chess)
		{
		case M_BATCOM:sanyif = sanyif;
		case M_SAPCOM:sanyif = sanyif + 1000;
		case M_COMCOM:sanyif = sanyif + 1000;
		case M_PLACOM:sanyif = sanyif + 1000;          //就是没有break
		}
		if (f)
			sanyif = 70000;
	}

	if (Ina_step[0] == 1 && Ina_step[1] > 12) //敌方的三十一步进行躲闪
	{
		if (cMap[i][j].chess != mchess[0] && cMap[i1][j1].chess != 'X')
		{
			for (int m = 0; m < 12; m++)
			{
				for (int n = 0; n < 5; n++)
				{
					if (Judge(m, n, 9, Pro) < 5000)
					{
						k1 = Oppnextmove(m, n, cMap, allmove1);
						for (k2 = 0; k2 < k1; k2++)
						{
							if (allmove1[k2][0] == i && allmove1[k2][1] == j)
								sanyi1 = true;
						}
					}
				}
			}
			for (int m = 0; m < 12; m++)
			{
				for (int n = 0; n < 5; n++)
				{
					if (Judge(m, n, 9, Pro) < 5000)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2 < k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								sanyi2 = true;
						}
					}
				}
			}
			if (sanyi1 == false && sanyi2 == false)
			{
				if (IsMoveCamp(i1, j1) == 1)
					sanyif = 4000;
				else
					sanyif = 3000;
			}
		}
	}
	//if (NumChess(cMap) < 15 || NumOppChess(cMap) < 15)
	//	if (cMap[i][j] == 'k')
	//		sanyif = sanyif + 20000;
	FILE *fp;
	fp = fopen("沈阳航空航天大学.txt", "a");
	fprintf(fp, "\n%d,%d", Ina_step[0], Ina_step[1]);
	fclose(fp);

	return sanyif;
}//_31Step