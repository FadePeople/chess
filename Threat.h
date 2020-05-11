#pragma once
//所要行走的位置对己方造成的威胁分值
int weixie(int x, int y, int x1, int y1, int Pro[25][14], Map cMap[12][5])
{
	int n, score = 0, k, i, j, t, t1 = 0;
	if (cMap[x1][y1].chess == '0')
		return 0;
	for (n = 0; n < 25; n++)//在猜测概率表中找到想要行走的位置
	{
		if (Pro[n][12] == x1 && Pro[n][13] == y1)
			break;
	}
	k = cMap[x][y].chess - 'a';
	//进行分值评估
	if (k >= 0 && k != 10)  //     k==10           为炸弹，先不考虑
	{
		for (i = 0; i < 9; i++)//可以行走的棋的分值
		{
			if (i < k)
				score = score - Pro[n][i];
			else if (i > k)
				score = score + Pro[n][i];
			else
				continue;
		}
		if (cMap[x][y].chess == 'i')
			score = score + Pro[n][9];
		else
			score = score - Pro[n][9];//地雷的分值
	}
	//统计该棋子是否为现有棋子中最大的两个
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (cMap[i][j].chess >= 'a' && cMap[i][j].chess <= 'i')
			{
				if (i == x && j == y)
					continue;
				else
				{
					t = cMap[i][j].chess - 'a';
					if (t <= k)   //比较两个棋子的大小
						t1++;  //计数
				}
			}
		}
	}
	if (t1 < 3)//如果棋子是己方最大的两个减去炸弹的分值
		score = score - Pro[n][10];
	return score;
}
//
int jweixie(int i, int j, int Pro[25][14], Map cMap[12][5])
{
	int i1, j1;
	int score = 0, score1 = 0;
	if (IsMoveCamp(i, j) == 1)
		score = 0;
	else//分数取最小值，因为行棋分数为行走最大分数
	{
		//向前搜索找到对己方棋子的威胁概率
		//不在第一排，不在山界后，前方不是己方棋子
		if (i > 0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j))
		{
			score1 = weixie(i, j, i - 1, j, Pro, cMap);
			if (score1 < score)
				score = score1;
			if (i > 1 && i < 11 && (j == 0 || j == 4))//在铁轨上
			{
				for (i1 = i - 1; i1 > 0; i1--)
				{
					if (cMap[i1][j].chess == '0')
						continue;
					else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess <= 'X')
					{
						score1 = weixie(i, j, i1, j, Pro, cMap);
						if (score1 < score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//向后搜索
		if (i < 11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j))
		{
			score1 = weixie(i, j, i + 1, j, Pro, cMap);
			if (score1 < score)
				score = score1;
			if (i > 0 && i < 10 && (j == 0 || j == 4))
			{
				for (i1 = i + 1; i1 < 11; i1++)
				{
					if (cMap[i1][j].chess == '0')
						continue;
					else if (cMap[i1][j].chess >= 'A' && cMap[i1][j].chess <= 'X')
					{
						score1 = weixie(i, j, i1, j, Pro, cMap);
						if (score1 < score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//向左搜索
		if (j > 0 && !IsMyChess(cMap, i, j - 1))
		{
			score1 = weixie(i, j, i, j - 1, Pro, cMap);
			if (score1 < score)
				score = score1;
			if (j > 0 && j < 5 && (i == 1 || i == 5 || i == 6 || i == 10))
			{
				for (j1 = j - 1; j1 >= 0; j1--)
				{
					if (cMap[i][j1].chess == '0')
						continue;
					else if (cMap[i][j1].chess >= 'A' && cMap[i][j1].chess <= 'X')
					{
						score1 = weixie(i, j, i, j1, Pro, cMap);
						if (score1 < score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//向右搜索
		if (j < 4 && !IsMyChess(cMap, i, j + 1))
		{
			score1 = weixie(i, j, i, j + 1, Pro, cMap);
			if (score1 < score)
				score = score1;
			if (j >= 0 && j < 4 && (i == 1 || i == 5 || i == 6 || i == 10))
			{
				for (j1 = j + 1; j1 < 5; j1++)
				{
					if (cMap[i][j1].chess == '0')
						continue;
					else if (cMap[i][j1].chess >= 'A' && cMap[i][j1].chess <= 'X')
					{
						score1 = weixie(i, j, i, j1, Pro, cMap);
						if (score1 < score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return score;
}