#pragma once
int wylcb(Map cMap[12][5], int Pro[25][14], int deep, char *cInMessage)
{
	int move[4];
	int allmove[200][4], iSaMove[40][2];
	int i, j, num, num1, i1, j1, k = 0;
	int mn;//��Сֵ
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
			if (IsMyMovingChess(cMap, i, j) && !IsBaseCamp(i, j))  //�������ڴ�Ӫ�Ŀ��ƶ�����
			{
				//��������
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
				//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
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
				//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
				if (j > 0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j - 1;
					k++;
					//�Ƿ���1,5,6,10������
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
				//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
				if (j < 4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j + 1;
					k++;
					//�Ƿ���1,5,6,10������
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

				//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
				if (i < 11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j;
					k++;
					//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
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
				//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
				if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
				if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
				if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j + 1;
					k++;
				}
				//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
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
		//��ǰ��ô�ߵķ�
		int score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], Pro, cMap, deep);

		//���ﻹû�м����������dfs�����Ż�
		//pinggu���������⣬��Ҫ��ϸ�Ż�һ��
		//���������������

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
			//ˢ������
			Map mm = ncp[allmove[i][0]][allmove[i][1]];
			ncp[allmove[i][0]][allmove[i][1]] = ncp[allmove[i][2]][allmove[i][3]];
			ncp[allmove[i][2]][allmove[i][3]] = mm;
			//���ѵķ�����
			int score2 = dfs(Pro, ncp, deep + 1, cInMessage);
			//�ָ�
			mm = ncp[allmove[i][0]][allmove[i][1]];
			ncp[allmove[i][0]][allmove[i][1]] = ncp[allmove[i][2]][allmove[i][3]];
			ncp[allmove[i][2]][allmove[i][3]] = mm;
			///�����ֵ
			score = max(score, score1 + score2);
			mn = score1;
		}
	}
	memset(allmove, 0, sizeof(allmove));
	return score;
}
//���Ѻ��� 
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
//������
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
//������
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
//���Ʒ�����ܺ�A*out���ϣ�����A*out�����Լ���û����
//deep��������ʱ���Ѿ�����һ����Ҫ��1�����ܴ�0
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
				if (IsMyMovingChess(cMap, i, j) && !IsBaseCamp(i, j))  //�������ڴ�Ӫ�Ŀ��ƶ�����
				{
					//��������
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
					//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
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
					//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
					if (j > 0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i;
						allmove[k][3] = j - 1;
						k++;
						//�Ƿ���1,5,6,10������
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
					//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
					if (j < 4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i;
						allmove[k][3] = j + 1;
						k++;
						//�Ƿ���1,5,6,10������
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

					//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
					if (i < 11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i + 1;
						allmove[k][3] = j;
						k++;
						//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
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
					//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
					if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i - 1;
						allmove[k][3] = j - 1;
						k++;
					}
					//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
					if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i + 1;
						allmove[k][3] = j - 1;
						k++;
					}
					//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
					if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = i - 1;
						allmove[k][3] = j + 1;
						k++;
					}
					//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
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
