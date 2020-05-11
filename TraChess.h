#pragma once
//�з�ĳ��λ�õ����ӵ���һ�����������λ��
//��ȷ���ǲ��ǹ���
int Oppnextmove(int i, int j, Map cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	char cmap[12][5];
	if (IsOppChess(cMap, i, j) && !IsBaseCamp(i, j))
	{
		//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
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
		//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
		if (j > 0 && !IsOppChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//�Ƿ���1,5,6,10������
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
		//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
		if (j < 4 && !IsOppChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//�Ƿ���1,5,6,10������
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

		//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
		if (i < 11 && !IsBehindHill(i, j) && !IsOppChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
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
		//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}

	return k;
}
//����ĳ��λ�õ����ӵ���һ�����������λ��
int nextmove1(int i, int j, Map cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	Map cmap[12][5];
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
		//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
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
		//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
		if (j > 0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//�Ƿ���1,5,6,10������
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
		//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
		if (j < 4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//�Ƿ���1,5,6,10������
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

		//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
		if (i < 11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
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
		//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}
	return k;
}