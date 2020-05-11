#pragma once
/* ************************************************************************ */
/* 函数功能：回收的分数														*/
/* 接口参数：																*/
/*     n为旗子位置	 											            */
/*     i为旗子大小			           									    */
/*     sfen概率表里面的分	                 					            */
/*     int Pro[25][14]  概率表                                              */
/* ************************************************************************ */
void souhui(int n, int i, int sfen, int Pro[25][14])       
{
	int zong = 0;
	int n1;
	if (sfen == 0)
		return;
	if (i == 0 || i == 1 || i == 11)
		zong = 10000;
	else if (i > 5 && i < 10)
		zong = 30000;
	else
		zong = 20000;
	for (n1 = 0; n1 < 25; n1++)
	{
		if (n1 != n && (zong - Pro[n][i]) != 0 && Pro[n1][i] < 9500)
			Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 - 1.0*sfen / (zong - Pro[n][i])));
	}
}
/* ************************************************************************ */
/* 函数功能：刷新工兵的概率 							    				*/
/* 接口参数：																*/
/*     char cMap 棋盘 											            */
/*     int i1,ji  起点坐标（敌方棋子初始坐标）           				    */
/*     int i2,j2  落点坐标	                 					            */
/*     int Pro[25][14]  概率表                                              */
/* ************************************************************************ */
int RefreshSapper(Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	int n, n1;
	int i, j;
	int zong = 0;
	if ((i1 != i2) && (j1 != j2))
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				//Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
				souhui(n, 8, 10000 - Pro[n][8], Pro);
				Pro[n][8] = 10000;		//工兵分值变10000
			}
		}
		return 1;
	}//if((i1 != i2) && (j1 != j2))
	else if ((i1 == i2) && (j1 != j2))
	{
		if ((i1 != 1) && (i1 != 5) && (i1 != 6) && (i1 != 10))
		{
			for (n = 0; n < 25; n++)
			{
				if (Pro[n][12] == i1 && Pro[n][13] == j1)
				{
					//Pro[n][12] = 14;
					for (i = 0; i < 12; i++)
					{
						if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)
						{
							if (i == 0 || i == 1 || i == 11)
								zong = 10000;
							else if (i > 5 && i < 10)
								zong = 30000;
							else
								zong = 20000;
							for (n1 = 0; n1 < 25; n1++)
								if (n1 != n && Pro[n1][i] < 9000)
									Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
							Pro[n][i] = 0;
						}
					}
					souhui(n, 8, 10000 - Pro[n][8], Pro);
					Pro[n][8] = 10000;		//工兵分值变10000
				}
			}
			return 1;
		}//if
		else
		{
			for (j = min(j1, j2) + 1; j < max(j1, j2); j++)
			{
				if (cMap[i1][j].chess != '0')
				{
					for (n = 0; n < 25; n++)
					{
						if (Pro[n][12] == i1 && Pro[n][13] == j1)
						{
							//Pro[n][12] = 14;
							for (i = 0; i < 12; i++)
							{
								if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)
								{
									if (i == 0 || i == 1 || i == 11)
										zong = 10000;
									else if (i > 5 && i < 10)
										zong = 30000;
									else
										zong = 20000;
									for (n1 = 0; n1 < 25; n1++)
										if (n1 != n && Pro[n1][i] < 9000)
											Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
									Pro[n][i] = 0;
								}
							}
							souhui(n, 8, 10000 - Pro[n][8], Pro);
							Pro[n][8] = 10000;		//工兵分值变10000
							return 1;
						}
					}
				}
			}
			return 0;
		}//else
	}//else if((i1 == i2) && (j1 != j2))
	else if ((i1 != i2) && (j1 == j2))
	{
		if ((j1 != 0) && (j1 != 4))
		{
			if ((j1 == 2) && (i1 + i2 == 11))
			{
				return 0;
			}
			else
			{
				for (n = 0; n < 25; n++)
				{
					if (Pro[n][12] == i1 && Pro[n][13] == j1)
					{
						Pro[n][12] = 14;
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						souhui(n, 8, 10000 - Pro[n][8], Pro);
						Pro[n][8] = 10000;		//工兵分值变10000
						return 1;
					}
				}
			}
			return 0;
		}
		else
		{
			for (i = min(i1, i2) + 1; i < max(i1, i2); i++)
			{
				if (cMap[i][j1].chess != '0')
				{
					for (n = 0; n < 25; n++)
					{
						if (Pro[n][12] == i1 && Pro[n][13] == j1)
						{
							//Pro[n][12] = 14;
							for (i = 0; i < 12; i++)
							{
								if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)
								{
									if (i == 0 || i == 1 || i == 11)
										zong = 10000;
									else if (i > 5 && i < 10)
										zong = 30000;
									else
										zong = 20000;
									for (n1 = 0; n1 < 25; n1++)
										if (n1 != n && Pro[n1][i] < 9000)
											Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
									Pro[n][i] = 0;
								}
							}
							souhui(n, 8, 10000 - Pro[n][8], Pro);
							Pro[n][8] = 10000;		//工兵分值变10000
							return 1;
						}
					}
				}
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}
	return 0;
}
/* ************************************************************************ */
/* 函数功能：刷新G0状态下的棋盘 											*/
/*                  （对方行棋，且对方棋子被己方吃掉,对方棋子棋力小于己方） */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（敌方棋子）           							*/
/*     int i2,j2  落点坐标（己方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinG0(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	//m=6
	int i, n, n1;
	int zong = 1, sfen = 0;
	if ((i2 == 6 && j2 == 4) || (i2 == 6 && j2 == 0))
		huang1 = 1;
	//碰子后没有对死，排除炸弹的可能性
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			if (Pro[n][10] != 0)
			{
				for (i = 0; i < 25; i++)  //同一竖排，除炸弹棋子外分数变大
				{
					if ((i != n) && (Pro[i][10] != 0))
					{
						Pro[i][10] = (int)((double)Pro[i][10] + (double)Pro[n][10] * (double)Pro[i][10] / (double)(zong - Pro[n][10]));
					}
				}
				Pro[n][10] = 0;
			}
		}
	}
	if (IsRailway(i1, j1) && IsRailway(i2, j2))     //判断棋子是否为工兵
		if (RefreshSapper(cMap, Pro, i1, j1, i2, j2))
		{
			for (n = 0; n < 25; n++)
			{
				if ((Pro[n][12] == i1) && (Pro[n][12] == j1))
					Pro[n][12] = 14;
			}
			return;
		}
	if (m < 8 && m >= 0)//己方棋子为司令至工兵
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i <= m || i > 8) && Pro[n][i] != 10000)   
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //增加棋盘上其他位置比己方棋子大的分值，     被吃掉的旗子只能为排长和工兵，所以其他地方相应其他子的分值增加
						Pro[n][i] = 0;   			//敌方棋子死掉，所以此位置为比己方棋子大的分值为0
					}
				}
				zong = 1;
				for (i = m + 1; i <= 8; i++)
					zong = zong + Pro[n][i];
				for (i = m + 1; i <= 8; i++) //将棋盘上其他地方比该棋子小的分值减少
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);                                                        //这个位置为排长，相应其他地方为排长的的概率减少
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
	if (m == 9)//己方棋子为地雷
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i == 8 || i == 10) && Pro[n][i] != 10000)    //不是炸弹或者工兵
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
				zong = 1;
				for (i = 0; i < 8; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < 8; i++) //将棋盘上其他地方为司令至排长的分值增加
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
	if ((i2 == 10 && j2 == 4 && buzhen == 1 && Judge(i1, j1, 8, Pro) > 9000) || (i2 == 10 && j2 == 0 && buzhen == 2 && Judge(i1, j1, 8, Pro) > 9000) || (NumChess(cMap) <= 12))
		huang3 = 1;
}

/* ************************************************************************ */
/* 函数功能：刷新G1状态下的棋盘 											*/
/*                  （对方行棋，且对方吃掉己方棋子,对方棋子棋力大于己方）   */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（敌方棋子）           							*/
/*     int i2,j2  落点坐标（己方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinG1(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{  //m=4 tuanzhang
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (cMap[i2][j2].chess <= 'd')
	{
		for (n = 0; n < 25; n++)
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				track[tra] = n;
				tra++;
			}
	}
	//碰子后没有对死，排除炸弹的可能性
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			if (Pro[n][10] != 0)
			{
				for (i = 0; i < 25; i++)
				{
					if ((i != n) && (Pro[i][10] != 0))
					{
						Pro[i][10] = (int)((double)Pro[i][10] + (double)Pro[n][10] * (double)Pro[i][10] / (double)(zong - Pro[n][10]));
					}
				}
				Pro[n][10] = 0;
			}
		}
	}
	if (IsRailway(i1, j1) && IsRailway(i2, j2))
		if (RefreshSapper(cMap, Pro, i1, j1, i2, j2))
		{
			for (n = 0; n < 25; n++)
			{
				if ((Pro[n][12] == i1) && (Pro[n][13] == j1))
				{
					Pro[n][12] = i2;
					Pro[n][13] = j2;
				}
			}
			return;
		}
	//吃掉我方地雷，对方为工兵
	if(m==9)            
	{
		for(n = 0; n < 25; n++)
		{
			if(Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = i2;
				Pro[n][13] = j2;
				for(i = 0; i < 12; i++)
				{
					if(Pro[n][i] != 0 && i != 8 && Pro[n][i] < 9500)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for(n1 = 0; n1 < 25; n1++)
						{
							if(Pro[n1][i] != 0 && n1 != n && Pro[n1][i] < 9500)
							{
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
							}
						Pro[n][i] = 0;
						}
					}
				}
			souhui(n, 8, 10000 - Pro[n][8], Pro);
			Pro[n][8] = 10000;
			}
		}
	} 
	if (m < 9 && m > 0)//己方棋子为军长至工兵		m>0
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = i2;
				Pro[n][13] = j2;

				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && ((i >= m && i < 9) || (i == 10)) && Pro[n][i] != 10000)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (Pro[n1][i] != 0&& n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //增加棋盘上其他位置比己方棋子小的分值，
						Pro[n][i] = 0;            //己方棋子死掉，所以此位置为比己方棋子小的分值为0
					}
				}
				zong = 1;
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //将棋盘上其他地方比该棋子大的分值减少
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
}
/* ************************************************************************ */
/* 函数功能：刷新G2状态下的棋盘 											*/
/*                  （对方行棋，对死,对方棋子棋力等于己方）                 */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（敌方棋子）           							*/
/*     int i2,j2  落点坐标（己方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinG2(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	int i, n, n1;
	int zong = 0, sfen = 0;
	if (IsRailway(i1, j1) && IsRailway(i2, j2))
		if (RefreshSapper(cMap, Pro, i1, j1, i2, j2))
		{
			for (n = 0; n < 25; n++)
			{
				if ((Pro[n][12] == i1) && (Pro[n][13] == j1))
				{
					Pro[n][12] = 14;
				}
			}
			return;
		}
	if (m < 9 && m >= 0)//己方棋子为司令至工兵
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				if (m == 0)  //己方棋子为司令
				{
					if (jq == 1)//对方棋子为司令
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != 0 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9500)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						Pro[n][0] = 10000;
					}
					else      //对方棋子为炸弹
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != 10 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9500)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						sfen = 10000 - Pro[n][10];
						souhui(n, 10, sfen, Pro);
						Pro[n][10] = 10000;
					}
				}
				else   //己方棋子为军长到工兵
				{
					if (m < 2)
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && (i != m && i != 10) && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						zong = Pro[n][m] + Pro[n][10] + 1;

						sfen = (int)(1.0 * 10000 * Pro[n][10] / zong - Pro[n][10]);
						souhui(n, 10, sfen, Pro);
						Pro[n][10] = (int)(10000 * (1.0*Pro[n][10] / zong));

						sfen = (int)(1.0 * 10000 * Pro[n][m] / zong - Pro[n][m]);
						souhui(n, m, sfen, Pro);
						Pro[n][m] = (int)(10000 * (1.0*Pro[n][m] / zong));
					}
					else
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != m && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}

						sfen = 10000 - Pro[n][m];
						souhui(n, m, sfen, Pro);
						Pro[n][m] = 10000;
					}

				}
			}
		}
	}
	if (m == 9)   //己方棋子为地雷
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && i != 10 && Pro[n][i] != 10000)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
				sfen = 10000 - Pro[n][10];
				souhui(n, 10, sfen, Pro);
				Pro[n][10] = 10000;
			}
		}
	}
	if (m == 10)
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
			}
		}
	}
}
/* ************************************************************************ */
/* 函数功能：刷新G3状态下的棋盘 											*/
/*                  （对方行棋，仅移动）                                    */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（敌方棋子）           							*/
/*     int i2,j2  落点坐标（己方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinG3(Map cMap[12][5], int i1, int j1, int i2, int j2, int Pro[25][14]) //仅移动棋子
{
	int n;
	int zong = 0;
	if (IsRailway(i1, j1) && IsRailway(i2, j2))
		if (RefreshSapper(cMap, Pro, i1, j1, i2, j2))
		{
			for (n = 0; n < 25; n++)
			{
				if ((Pro[n][12] == i1) && (Pro[n][13] == j1))
				{
					Pro[n][12] = i2;
					Pro[n][13] = j2;
				}
			}
			return;
		}
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			Pro[n][12] = i2;
			Pro[n][13] = j2;
			if (z1 == 1 && y21 == 2 && x21 == 1)
				Pro[n][10] = 4000;
			if (z2 == 1 && y21 == 2 && x21 == 3)
				Pro[n][10] = 4000;
			if (z3 == 1 && y21 == 4 && x21 == 1)
				Pro[n][10] = 4000;
			if (z4 == 1 && y21 == 4 && x21 == 3)
				Pro[n][10] = 4000;
		}
	}
}
/* ************************************************************************ */
/* 函数功能：刷新R0状态下的棋盘 											*/
/*                  （己方行棋，且对方吃掉己方棋子,对方棋子棋力大于己方）   */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（己方棋子）           							*/
/*     int i2,j2  落点坐标（敌方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinR0(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{  //m=4 tuanzhang
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (cMap[i1][j1].chess <= 'd')
	{
		for (n = 0; n < 25; n++)
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				track[tra] = n;
				tra++;
			}
	}
	if (m == 8)//己方棋子为工兵
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i == 8 || i == 9 || i == 10) && Pro[n][i] != 10000)    //不是,工兵,炸弹，地雷
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //增加棋盘上其他位置比己方棋子小的分值，
						Pro[n][i] = 0;            //己方棋子死掉，所以此位置地雷炸弹分值为0
					}
				}
				zong = 1;    //   （  没有地雷）
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //将棋盘上其他地方比该棋子大的分值减少
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}

			}
		}
	}
	if (m < 8 && m>0)//己方棋子为军长至排长
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && ((i >= m && i < 9) || (i == 10)) && Pro[n][i] != 10000)    //不是团长到工兵
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //增加棋盘上其他位置比己方棋子小的分值，
						Pro[n][i] = 0;            //己方棋子死掉，所以此位置为比己方棋子小的分值为0(不可能的棋子)
					}
				}
				zong = 1;    //   （  没有地雷）
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //将棋盘上其他地方比该棋子大的分值减少
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}

			}
		}
	}
	if (m == 0)// 己方棋子为司令，敌方为地雷
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				souhui(n, 9, 10000 - Pro[n][9], Pro);
				Pro[n][9] = 10000;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && i != 9 && Pro[n][i] != 10000)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9500)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
			}
		}
	}
	//碰子后没有对死，排除炸弹的可能性
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			if (Pro[n][10] != 0)
			{
				for (i = 0; i < 25; i++)
				{
					if ((i != n) && (Pro[i][10] != 0))
					{
						Pro[i][10] = (int)((double)Pro[i][10] + (double)Pro[n][10] * (double)Pro[i][10] / (double)(zong - Pro[n][10]));
					}
				}
				Pro[n][10] = 0;
			}
		}
	}
}
/* ************************************************************************ */
/* 函数功能：刷新R1状态下的棋盘 											*/
/*                  （己方行棋，且己方吃掉对方棋子,对方棋子棋力小于己方）   */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											*/
/*     int i1,ji  起点坐标（己方棋子）           							*/
/*     int i2,j2  落点坐标（对方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinR1(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{   //m=6
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (m < 8 && m >= 0)//己方棋子为司令至排长
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i <= m || i > 8) && Pro[n][i] != 10000)    //不是排长或者工兵
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //增加棋盘上其他位置比己方棋子大的分值，     被吃掉的旗子只能为排长和工兵，所以其他地方相应其他子的分值增加
						Pro[n][i] = 0;            //敌方棋子死掉，所以此位置为比己方棋子大的分值为0
					}
				}
				zong = 1;
				for (i = m + 1; i <= 8; i++)
					zong = zong + Pro[n][i];
				for (i = m + 1; i <= 8; i++) //将棋盘上其他地方比该棋子小的分值减少
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);                                                        //这个位置为排长，相应其他地方为排长的的概率减少
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
	if (m == 8)//己方为工兵，敌方为地雷
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
				souhui(n, 9, 10000 - Pro[n][9], Pro);
				Pro[n][9] = 10000;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && i != 9)
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if ((n1 != n) && (Pro[n1][i] < 9000) && ((zong - Pro[n][i]) > 0))
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
			}
		}

	}
	//碰子后没有对死，排除炸弹的可能性
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			if (Pro[n][10] != 0)
			{
				for (i = 0; i < 25; i++)
				{
					if ((i != n) && (Pro[i][10] != 0))
					{
						Pro[i][10] = (int)((double)Pro[i][10] + (double)Pro[n][10] * (double)Pro[i][10] / (double)(zong - Pro[n][10]));
					}
				}
				Pro[n][10] = 0;
			}
		}
	}
}
/* ************************************************************************ */
/* 函数功能：刷新R2状态下的棋盘 											*/
/*                  （对方行棋，对死,对方棋子棋力等于己方）                 */
/* 接口参数：																*/
/*     int m 己方被吃子棋力大小											    */
/*     int i1,ji  起点坐标（己方棋子）           							*/
/*     int i2,j2  落点坐标（敌方棋子）	                 					*/
/*     int Pro[25][14]  概率表                                               */
/* ************************************************************************ */
void shuaxinR2(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (m < 9 && m >= 0)//己方棋子为司令至工兵
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
				if (m == 0)  //己方棋子为司令
				{
					if (jq == 1)//对方棋子为司令
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != 0 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9500)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						Pro[n][0] = 10000;
					}
					else      //对方棋子为炸弹
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != 10 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9500)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}
						sfen = 10000 - Pro[n][10];
						souhui(n, 10, sfen, Pro);
						Pro[n][10] = 10000;
					}
				}
				else   //己方棋子为军长到工兵
				{
					if (m < 2)//如果己方棋子为师长以上，那么敌方棋子可能为炸弹
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != m && i != 10 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}

						zong = Pro[n][m] + Pro[n][10] + 1;  //防止分母为0，出错。

						sfen = (int)(1.0 * 10000 * Pro[n][m] / zong - Pro[n][m]);
						souhui(n, m, sfen, Pro);
						Pro[n][m] = (int)(1.0 * 10000 * Pro[n][m] / zong);

						sfen = (int)(1.0 * 10000 * Pro[n][10] / zong - Pro[n][10]);
						souhui(n, 10, sfen, Pro);
						Pro[n][10] = (int)(1.0 * 10000 * Pro[n][10] / zong);
					}
					else//敌方棋子为师长以下，则不考虑炸弹的概率
					{
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i != m && i != 10 && Pro[n][i] != 10000)
							{
								if (i == 0 || i == 1 || i == 11)
									zong = 10000;
								else if (i > 5 && i < 10)
									zong = 30000;
								else
									zong = 20000;
								for (n1 = 0; n1 < 25; n1++)
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
								Pro[n][i] = 0;
							}
						}

						sfen = 10000 - Pro[n][m];
						souhui(n, m, sfen, Pro);
						Pro[n][m] = 10000;
					}
				}
			}
		}
	}
	if (m == 10)
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
			}
		}
	}
}
/* ************************************************************************ */
/* 函数功能：根据裁判反馈刷新棋盘											*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     char *cInMessage 来自裁判的GO YXYX R YX命令							*/
/*     char *cOutMessage 发给裁判的BESTMOVE YXYX命令						*/
/* ************************************************************************ */
void FreshMap(Map cMap[12][5], char *cInMessage, char *cOutMessage, int Pro[25][14])
{
	int x1, y1;				//起点					//x1,y1,x2,y2,result由char型改为int型，没什么影响
	int x2, y2;				//落点
	int result = -1, k;			//碰子结果
	int n, i, j, n1, zong = 1;

	if (cInMessage[0] == 'G')	// GO 指令
	{
		if (cInMessage[3] >= 'A' && cInMessage[3] <= 'L')																					//x,y坐标发生对换，因为不习惯
		{
			y1 = cInMessage[3] - 'A';
			x1 = cInMessage[4] - '0';
			y2 = cInMessage[5] - 'A';
			x2 = cInMessage[6] - '0';
			result = cInMessage[8] - '0';		//碰子结果
			y11 = y1;
			x11 = x1;
			y21 = y2;
			x21 = x2;
			if (y21 == 2 && x21 == 1 && y11 < 5)
				z1++;
			if (y21 == 2 && x21 == 3 && y11 < 5)
				z2++;
			if (y21 == 4 && x21 == 1 && y11 < 5)
				z3++;
			if (y21 == 4 && x21 == 3 && y11 < 5)
				z4++;
			if ((cInMessage[10] >= 'A') && (cInMessage[10] <= 'L') && (comm == 0)) //对方司令战死后显示军旗位置
			{
				comm++;
				cMap[cInMessage[10] - 'A'][cInMessage[11] - '0'].chess = 'L';
				jq++;
				if (cInMessage[11] - '0' == 1)
				{
					Pro[1][11] = 10000;
					for (i = 0; i < 11; i++)
					{
						Pro[1][i] = 0;
					}
					Pro[3][11] = 0;
					Pro[3][7] = 6000;
					Pro[3][9] = 4000;
					cMap[0][1].chess = 'L';
				}
				if (cInMessage[11] - '0' == 3)
				{
					Pro[3][11] = 10000;
					for (i = 0; i < 11; i++)
					{
						Pro[3][i] = 0;
					}
					Pro[1][11] = 0;
					Pro[1][7] = 6000;
					Pro[1][9] = 4000;
					cMap[0][3].chess = 'L';
				}
				for (n = 0; n < 25; n++)  //第一次显示军棋位置，证明对方死去的子为司令
				{
					if (Pro[n][12] == y1 && Pro[n][13] == x1)
					{
						for (i = 0; i < 25; i++)  //对横排的刷新
						{
							for (j = 1; j < 12; j++)
							{
								if (j == 0 || j == 1 || j == 11)
									zong = 10000;           //司令，军长和军旗都只有一个
								else if (j > 5 && j < 10)
									zong = 10000 * 3;         //每个棋子共有3个
								else
									zong = 10000 * 2;         //每个棋子有两个
								if ((10000 - Pro[i][0] > 0) && (i != n) && (zong - Pro[n][j] > 0))
								{
									Pro[i][j] = (int)((double)Pro[i][j] + (double)Pro[i][0] * (double)Pro[i][j] / (double)(10000 - Pro[i][0]) + (double)Pro[i][j] * (double)Pro[n][j] / (double)(zong - Pro[n][j]));
									//与司令不是同一行同一列的棋子概率变大
									Pro[i][0] = 0;  //与司令同一列的棋子 分数归零
									Pro[n][j] = 0;  //与司令同一行的棋子分数归零
								}
							}
						}
						Pro[n][0] = 10000;
					}
				}
			}
			/////判断地雷的概率///////////
			if (y1 < 2)
			{
				for (n = 0; n < 25; n++)
				{
					if (Pro[n][12] == y1 && Pro[n][13] == x1)
					{
						Pro[n][12] = y2;
						Pro[n][13] = x2;
						for (i = 0; i < 12; i++)
						{
							if (Pro[n][i] != 0 && i == 9 && Pro[n][i] != 10000)
							{
								for (n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n && Pro[n1][i] < 9000)
										Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (30000 - Pro[n][i])));
								}
								Pro[n][i] = 0;
							}
						}
						zong = 1;
						for (i = 0; i < 9; i++)
							zong = zong + Pro[n][i];
						for (i = 0; i < 9; i++)
						{
							souhui(n, i, (int)(1.0 * 10000 * Pro[n][i] / (zong + 1) - Pro[n][i]), Pro);
							Pro[n][i] = 10000 * Pro[n][i] / (zong + 1);
						}

					}
				}
			}
			switch (result)		//根据不同结果修改棋盘
			{
			case 0:			//对方棋子被己方吃掉
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';  //终点为己方棋子
				shuaxinG0(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y1][x1].chess = '0';
				break;
			case 1:			//对方吃掉己方棋子
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';//终点为己方棋子
				shuaxinG1(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1].chess = '0';
				break;
			case 2:			//双方棋子对死
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';//终点为己方棋子
				shuaxinG2(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y1][x1] = Empty;
				cMap[y2][x2] = Empty;
				break;
			case 3:			//对方移动棋子、、、///进 行营炸弹概率增加
				Ina_step[1]++;
				shuaxinG3(cMap, y1, x1, y2, x2, Pro);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1] = Empty;
				break;
			}
		}
	}
	if (cInMessage[0] == 'R')	// RESULT 指令
	{
		y1 = cOutMessage[9] - 'A';
		x1 = cOutMessage[10] - '0';
		y2 = cOutMessage[11] - 'A';
		x2 = cOutMessage[12] - '0';
		result = cInMessage[7] - '0';		//结果结果
		if (IsBaseCamp(y2, x2))  //进入大本营后没有结束战斗 另一个大本营里的是军棋
		{
			if (x2 == 1)
			{
				Pro[3][11] = 10000;
				for (i = 0; i < 11; i++)
				{
					Pro[3][i] = 0;
				}
				Pro[1][11] = 0;
				Pro[1][7] = 6000;
				Pro[1][9] = 4000;
				cMap[0][3].chess = 'L';
			}
			else if (x2 == 3)
			{
				Pro[1][11] = 10000;
				Pro[3][11] = 0;
				Pro[3][7] = 6000;
				Pro[3][9] = 4000;
				for (i = 0; i < 11; i++)
				{
					Pro[1][i] = 0;
				}
				cMap[0][3].chess = 'L';
			}
		}
		if ((cInMessage[8] == ' ') && (cInMessage[9] >= 'A') && (cInMessage[9] <= 'L') && (comm == 0)) //对方司令战死后显示军旗位置
		{
			comm++;
			cMap[cInMessage[9] - 'A'][cInMessage[10] - '0'].chess = 'L';
			jq++;
			if (cInMessage[10] - '0' == 1)
			{
				Pro[1][11] = 10000;
				for (i = 0; i < 11; i++)
				{
					Pro[1][i] = 0;
				}
				Pro[3][11] = 0;
				Pro[3][7] = 6000;
				Pro[3][9] = 4000;
				cMap[0][1].chess = 'L';
			}
			if (cInMessage[10] - '0' == 3)
			{
				Pro[3][11] = 10000;
				Pro[1][11] = 0;
				for (i = 0; i < 11; i++)
				{
					Pro[3][i] = 0;
				}
				Pro[1][7] = 6000;
				Pro[1][9] = 4000;
				cMap[0][3].chess = 'L';
			}
			for (n = 0; n < 25; n++)  //第一次显示军棋位置，证明对方死去的子为司令
			{
				if (Pro[n][12] == y1 && Pro[n][13] == x1)
				{
					for (i = 0; i < 25; i++)  //对横排的刷新
					{
						for (j = 1; j < 12; j++)
						{
							if (j == 0 || j == 1 || j == 11)
								zong = 10000;           //司令，军长和军旗都只有一个
							else if (j > 5 && j < 10)
								zong = 10000 * 3;         //每个棋子共有3个
							else
								zong = 10000 * 2;         //每个棋子有两个
							if ((10000 - Pro[i][0] > 0) && (i != n) && (zong - Pro[n][j] > 0))
							{
								Pro[i][j] = (int)((double)Pro[i][j] + (double)Pro[i][0] * (double)Pro[i][j] / (double)(10000 - Pro[i][0]) + (double)Pro[i][j] * (double)Pro[n][j] / (double)(zong - Pro[n][j]));
								//与司令不是同一行同一列的棋子概率变大
								Pro[i][0] = 0;  //与司令同一列的棋子 分数归零
								Pro[n][j] = 0;  //与司令同一行的棋子分数归零
							}
						}
					}
					Pro[n][0] = 10000;
				}
			}
		}
		switch (result)		//根据不同结果修改棋盘
		{
		case 0:			//己方棋子被对方吃掉
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';  //起点为己方棋子
			shuaxinR0(k, cMap, Pro, y1, x1, y2, x2);//根据己方的棋子刷新猜测概率表
			cMap[y1][x1] = Empty;
			break;
		case 1:			//己方吃掉对方棋子
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';
			shuaxinR1(k, cMap, Pro, y1, x1, y2, x2);
			cMap[y2][x2] = cMap[y1][x1];
			cMap[y1][x1] = Empty;
			break;
		case 2:			//双方棋子对死
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';
			shuaxinR2(k, cMap, Pro, y1, x1, y2, x2);
			cMap[y1][x1] = Empty;
			cMap[y2][x2] = Empty;
			break;
		case 3:			//己方移动棋子
			Ina_step[1]++;
			cMap[y2][x2] = cMap[y1][x1];
			cMap[y1][x1] = Empty;
			break;
		}
	}
	int p, q;
	for (p = 0; p < 25; p++)
	{
		for (q = 0; q < 14; q++)
		{
			if (Pro[p][q] > 1000000)
				Pro[p][q] = 0;
		}
	}
	int a, b, c;//循环变量
	int sum = 0;
	int flat = 0;
	for (i = 0; i < 25; i++)
	{
		k = 0;
		for (j = 0; j < 12; j++)   //判断横排是否就一个地方有概率
		{
			if (Pro[i][j] < 50)
				k++;
			else if (Pro[i][j] > 9000)
			{
				k = 11;
				flat = 1;
				break;
			}
		}
		if (k == 11)    //横排就一个地方有概率或者有一处子的概率大于9000
		{
			if (flat == 0)
			{
				for (c = 0; c < 12; c++)
				{
					if (Pro[i][c] < 50)
					{
						Pro[i][c] = 0;         //将横排低于50分的地方清零
					}
					else {
						Pro[i][c] = 10000;         //概率最大处概率设为10000
						souhui(i, c, 10000 - Pro[i][c], Pro);
					}
				}
			}
			else if (flat == 1)
			{
				for (c = 0; c < 12; c++)
				{
					if (Pro[i][c] > 9000)
					{
						Pro[i][c] = 10000;
						souhui(i, c, 10000 - Pro[i][c], Pro);
					}
					else {
						Pro[i][c] = 0;
					}
				}
			}
			for (b = 0; b < 12; b++)     //判断竖排总分少不少
			{
				sum = 0;
				for (a = 0; a < 25; a++)
				{
					sum = sum + Pro[a][b];
				}
				if (b == 0 || b == 1 || b == 11)
					zong = 10000;           //司令，军长和军旗都只有一个
				else if (b > 5 && b < 10)
					zong = 10000 * 3;         //每个棋子共有3个
				else
					zong = 10000 * 2;         //每个棋子有两个
				if (sum < zong)            //竖排总分少
				{
					for (n = 0; n < 25; n++)
					{
						if ((Pro[n][b] < 10000) && (sum != 0))
						{
							Pro[n][b] = (int)(1.0*Pro[n][b] * (1 + 1.0*(zong - sum) / sum));  //将少掉的部分加到竖排
						}
					}
				}
			}
		}
	}
	FILE *fp;
	fp = fopen("沈阳航空航天大学.txt", "a");
	fprintf(fp, "\n\n\n\n\n\n\n\n第%d步的开始   此时三十一步的步数%d:\n", qqqqqq + 1, Ina_step[1]);
	for (int i = 0; i != 12; i++)
	{
		for (int j = 0; j != 5; j++)
		{
			if (cMap[i][j].chess == 'X')
				fprintf(fp, "敌 ");
			if (cMap[i][j].chess == 'L')
				fprintf(fp, "旗 ");
			if (cMap[i][j].chess == '0')
				fprintf(fp, "oo");
			if (cMap[i][j].chess == 'a')
				fprintf(fp, "司 ");
			if (cMap[i][j].chess == 'b')
				fprintf(fp, "军 ");
			if (cMap[i][j].chess == 'c')
				fprintf(fp, "师 ");
			if (cMap[i][j].chess == 'd')
				fprintf(fp, "旅 ");
			if (cMap[i][j].chess == 'e')
				fprintf(fp, "团 ");
			if (cMap[i][j].chess == 'f')
				fprintf(fp, "营 ");
			if (cMap[i][j].chess == 'g')
				fprintf(fp, "连 ");
			if (cMap[i][j].chess == 'h')
				fprintf(fp, "排 ");
			if (cMap[i][j].chess == 'i')
				fprintf(fp, "兵 ");
			if (cMap[i][j].chess == 'j')
				fprintf(fp, "雷 ");
			if (cMap[i][j].chess == 'k')
				fprintf(fp, "炸 ");
			if (cMap[i][j].chess == 'l')
				fprintf(fp, "旗 ");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	FILE *abcd = fopen("沈阳航空航天大学.txt", "a");
	fprintf(abcd, "\n此处为概率表\n");
	for (int temp = 0; temp != 26; temp++)
	{
		for (int tt = 0; tt != 14; tt++)
		{
			fprintf(abcd, "%5d  ", Pro[temp][tt]);
		}
		fprintf(abcd, "\n");
	}
	fclose(abcd);
}
