#pragma once
//��Ҫ���ߵ�λ�öԼ�����ɵ���в��ֵ
int weixie(int x, int y, int x1, int y1, int Pro[25][14], Map cMap[12][5])
{
	int n, score = 0, k, i, j, t, t1 = 0;
	if (cMap[x1][y1].chess == '0')
		return 0;
	for (n = 0; n < 25; n++)//�ڲ²���ʱ����ҵ���Ҫ���ߵ�λ��
	{
		if (Pro[n][12] == x1 && Pro[n][13] == y1)
			break;
	}
	k = cMap[x][y].chess - 'a';
	//���з�ֵ����
	if (k >= 0 && k != 10)  //     k==10           Ϊը�����Ȳ�����
	{
		for (i = 0; i < 9; i++)//�������ߵ���ķ�ֵ
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
			score = score - Pro[n][9];//���׵ķ�ֵ
	}
	//ͳ�Ƹ������Ƿ�Ϊ������������������
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
					if (t <= k)   //�Ƚ��������ӵĴ�С
						t1++;  //����
				}
			}
		}
	}
	if (t1 < 3)//��������Ǽ�������������ȥը���ķ�ֵ
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
	else//����ȡ��Сֵ����Ϊ�������Ϊ����������
	{
		//��ǰ�����ҵ��Լ������ӵ���в����
		//���ڵ�һ�ţ�����ɽ���ǰ�����Ǽ�������
		if (i > 0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j))
		{
			score1 = weixie(i, j, i - 1, j, Pro, cMap);
			if (score1 < score)
				score = score1;
			if (i > 1 && i < 11 && (j == 0 || j == 4))//��������
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
		//�������
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
		//��������
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
		//��������
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