#pragma once
#define STANDARD2 3000
//����bhggckkfcdiiefejadjijlhhg
int my_k_go(int i, int j, int i1, int j1, Map cMap[12][5]);//������ʦ������·��ը����ʦ�����棬ʹը����Ӫ,˼·Ϊʦ��������·�����������ʦ����������ը��ը����֮ʦ��һֱ������·�ء�
int bomb_gozhong(int i, int j, int i1, int j1, Map cMap[12][5]);//���Ϻ�����ը������Ӫ������·ʦ����������������ʦ��λ�ã�ֱ����ը��ը����
int my_i_dig(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int ss[1][2]);//С������,�������Ϊ�ף�����׼ӷ֣���֮��¼Σ��λ��
//int CanOppget(int i, int j, int Pro[25][14], Map cMap[12][5], char mine);//�ж�Ŀ��λ�õ��Σ�յȼ���һ�����ڸ��ʱ�ˢ�²���ʱ��0Ϊ����������1Ϊ���������ܳ��Լ���2Ϊ���������ܶ��ӡ�3Ϊ���������ܱ������ԡ�4Ϊ���ʱ���ʱΪˢ�µ�Ŀ��֣��޷��ж���в   ���Σ�i��jΪ��ѯ���꣬ mineΪ��������
void find_bomb(int i, int j, int Pro[25][14], Map cMap[12][5], int mudi[20][2]); //������Χһ�ܣ��Ƿ���ը��, ը��λ�ô���mudi, ����ը��ʹmudi[0][0] = -1��
int good_choice(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int mudi1[20][2]);//�����ж�Σ�յȼ��ĺ������ж����ӵĽϺ�ѡ��
int b_c_gofirst(int i, int j, int i1, int j1, Map cMap[12][5]);//��һ�ţ�������ʦ����ǰը���ں󣬿��þ�����ʦ����ǰ��
int bombgo(int i, int j, int i1, int j1, Map cMap[12][5]);//ը�����Ƚ�������Ӫ


int spe3(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5])
{
	int score = 0;
	char ChessRank[25];
	mychessdx(cMap, ChessRank);
	int left = strlen(ChessRank);
	if (IsOppChess(cMap, 10, 1)) {
		if (i1 == 10 && j1 == 1) {
			score += 25000;
			if (left <= 10 && i1 == 10 && j1 == 1) score += (25 - NumOppChess(cMap)) * 2000;
			
		}
		if (i == 9 && j == 1) score += 10000;
		return score;
	}
	if (IsOppChess(cMap, 10, 2)) {
		if (i1 == 10 && j1 == 2) {
			score += 25000;
			if (left <= 10 && i1 == 10 && j1 == 2) score += (25 - NumOppChess(cMap)) * 2000;
		}
		if (i == 9 && j == 1) score += 10000;
		return score;
	}
	if (IsOppChess(cMap, 10, 0)) {
		if (i1 == 10 && j1 == 0) {
			score += 19000;
			if (left <= 10 && i1 == 10 && j1 == 0) score += (25 - NumOppChess(cMap)) * 2000;
		}
		if (i == 9 && j == 1) score += 10000;
		return score;
	}
	if (cMap[10][0].chess == 'X' && cMap[10][1].chess == 'a')
	{
		if (IsMyChess(cMap,11,0))
		{
			if (i == 10 && j == 1)
			{
				if (i1 == 10 && j1 == 0)
				{
					score -= 10000;
				}
			}
		}
	}
	if (i == 3 && j == 0)
	{
		if (IsOppChess(cMap, 3, 2) == 0)
		{
			if (i1 == 3 && j1 == 1)
			{
				score += 3000;
			}
		}
		else
		{
			score += i1 * 250;
		}
	}
	if (i == 2 && j == 0)
	{
			if (i1 == 3 && j1 == 0)
			{
				score += 4000;
			}
	}
	if (i == 3 && j == 4)
	{
		if (IsOppChess(cMap, 3, 2) == 0)
		{
			if (i1 == 3 && j1 == 3)
			{
				score += 3000;
			}
		}
		else
		{
			score += i1 * 250;
		}
	}
	if (i == 2 && j == 4)
	{
		if (i1 == 3 && j1 == 4)
		{
			score += 4000;
		}
	}
	if (left < 15)
	{
		if (j1 < j)
		{
			score += (4 - j1)*(25 - left) * 75;
		}
	}
	int k_sum = 0;
	for (int a = 0; a <= 11; a++)
	{
		for (int b = 0; b <= 4; b++)
		{
			if (cMap[a][b].chess == 'k')
				k_sum++;
		}
	}
	if (cMap[i][j].chess == ChessRank[0]) 
	{
		if (i != 10 && j != 1) {
			if (j1 <= 2) {
				score += (3-j1) * 1500;
			}
			if (i >= 7) score += i1 * 500;
		}
		if (i == 10 && j == 0 && i1 == 10 && j1 == 1) score += 10000;
	}
	if (cMap[i][j].chess == 'a')
	{
		if (i <= 5)
		{
			if (NumOppChess(cMap) >= (NumChess(cMap) - 3))
			{
					score += i1 * 300;
			}
			else
			{
				if (Judge(0, 1, 11, Pro) == 0)//�з���������
				{
					if (i1 == 4 && j1 == 1)
					{
						score += 2500;
					}
					if (i1 == 3 && j1 == 2)
					{
						score += 2500;
					}
					if (i1 == 2 && j1 == 3)
					{
						score += 2500;
					}
					if (i1 == 0 && j1 == 3)
					{
						score += 2500;
					}
				}
				if (Judge(0, 3, 11, Pro) == 0)//�з���������
				{
					if (i1 == 4 && j1 == 1)
					{
						score += 2500;
					}
					if (i1 == 3 && j1 == 2)
					{
						score += 2500;
					}
					if (i1 == 2 && j1 == 1)
					{
						score += 2500;
					}
					if (i1 == 0 && j1 == 1)
					{
						score += 2500;
					}
				}
				else//�з����첻ȷ��
				{
					if (i1 == 4 && j1 == 1)
					{
						score += 2500;
					}
					if (i1 == 3 && j1 == 2)
					{
						score += 2500;
					}
					if (i1 == 2 && j1 == 2)
					{
						score += 2500;
					}
					if (i1 == 1 & j1 == 2)
					{
						score += 2500;
					}
				}
			}
		}
	}
	
	//ը��
	if (cMap[i][j].chess == 'k')
	{
		if (NumOppChess(cMap) <= 15)
		{
			if (IsOppChess(cMap, i1, j1)) score += 1000;
			if (IsMoveCamp(i, j))
			{
				if (IsRailway(i1, j1)) {
					if (j1 == 0 || j1 == 4) score += (25 - NumOppChess(cMap)) * 200;
				}
			}
			return score;
		}
		if (Judge(i1, j1, 0, Pro) >= STANDARD2)
		{
			score += 3000;
		}
		if(Judge(i1, j1, 1, Pro) >= STANDARD2)
		{
			score += 3000;
		}
		if (NumOppChess(cMap) < 13)
		{
			if (IsOppChess(cMap, i1, j1))
			{
				score += 5000;
			}
		}
		if (!IsMoveCamp(i, j))
		{
			if (k_sum == 2) {
				if (IsMoveCamp(i1, j1))
				{
					score += (25 - NumOppChess(cMap)) * 100;
				}
			}
			if (k_sum == 1)
			{
				if (i1 == 9 && j1 == 1)
				{
					score += 3000;
				}
				if (i == 7 && j == 1 && i1 == 8 && j1 == 2) score += 2600;
				if (IsMoveCamp(i1, j1))
				{
					score += (25 - NumOppChess(cMap)) * 100;
				}
			}
		}
		else
		{
			if (k_sum == 2)
			{
				if (cMap[9][1].chess == 'k')
				{
					if (i == 9 && j == 1)
					{
						score -= 1000;
					}
					else if(i!=8&&j!=2){
						if (i1 == 8 && j1 == 2)
						{
							score += 2000;
						}	
					}
					else
					{
						score -= 1000;
					}

				}
				else
				{
					if (i1 == 9 && j1 == 1)
					{
						score += 2000;
					}
				}	
			}
		}
	}
	//͵�������Բй���
	if (NumOppChess(cMap) <= 16 && cMap[i][j].chess == 'i') {
		if (IsOppChess(cMap, i1, j1)) {//��Ϲײ
			if (i <= 2 && cMap[i1][j1].IsTouch == 0) score += 1200;
			else score -= 2300;
		}
		if (i == 1 && j == 4 && Judge(0, 3, 11, Pro) != 0) {//͵��
			if (i1 == 0 && j1 == 4) {//����
				score += 2000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))//������
					score -= 2000;
			}
			if (Judge(1, 3, 9, Pro) >= STANDARD2 && CanOppget('i', 1, 3, cMap, Pro) == 0) {//����
				score += 4000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 4000;
			}
		}
		if (i == 1 && j == 0 && Judge(0, 1, 11, Pro) != 0) {//͵��
			if (i1 == 0 && j1 == 0) {
				score += 2000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 2000;
			}
			if (Judge(1, 1, 9, Pro) >= STANDARD2 && CanOppget('i', 1, 1, cMap, Pro) == 0) {
				score += 4000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 4000;
			}
		}

		if (IsMoveCamp(i, j) && left <= 17) {
			if (i1 == 1 && j1 == 4) score += (800 + (25 - NumOppChess(cMap)) * 100);
			if (i1 == 1 && j1 == 0) score += (800 + (25 - NumOppChess(cMap)) * 100);
		}

		if (Judge(i1, j1, 10, Pro) >= (STANDARD - 500)) score += 15000;
		if (left <= 15) {
			if (IsRailway(i1, j1))
				if (CanOppget('i', i1, j1, cMap, Pro) == 0) score += (25 - NumOppChess(cMap)) * 125;
		}


	}
	return score;
}


//*******************************************
//������ʦ������·��ը����ʦ�����棬ʹը����Ӫ,˼·Ϊʦ��������·�����������ʦ����������ը��ը����֮ʦ��һֱ������·�ء�
int my_k_go(int i, int j, int i1, int j1, Map cMap[12][5])
{
	int score = 0;
	if (cMap[i][j].chess == 'k'&&i == 7 && j == 2)//�ж��ض�λ��ʹ����ը��
	{
		if (i1 == 7 && j1 == 3)
		{
			score += 150;//3000
		}
		else
		{
			score += 0;
		}
	}
	return score;
}


//*******************************************
//���ϲ���ը������Ӫ������·ʦ����������������ʦ��λ�ã�ֱ����ը��ը����
int bomb_gozhong(int i, int j, int i1, int j1, Map cMap[12][5])
{
	int score = 0;
	if (IsOppChess(cMap, 6, 2))
	{
		if (cMap[i][j].chess == 'k'&&i == 7 && j == 3 && i1 == 6 && j1 == 2)
		{
			score += 150;//3000
		}
		else
		{
			score += 0;
		}
	}
	return score;
}


//********************************************
//С������,�������Ϊ�ף�����׼ӷ֣���֮��¼Σ��λ��
int my_i_dig(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int ss[1][2])
{
	int score = 0;
	if (Judge(i1, j1, 9, Pro) >= STANDARD2)
	{
		if (cMap[i][j].chess == 'i') {
			score += 250;//5000
		}
		else
		{
			score -= 500;//5000
		}
	}
	else
	{
		ss[0][0] = i1;
		ss[0][1] = j1;
	}
	return score;
}


//**********************************************
//������Χһ�ܣ��Ƿ���ը��,ը��λ�ô���mudi,����ը��ʹmudi[0][0]=-1��
void find_bomb(int i, int j, int Pro[25][14], Map cMap[12][5], int mudi[20][2])
{
	memset(mudi, -1, sizeof(mudi));
	int s = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			if (i + a > 4 || i - a < 0 || j + b>11 || j - b < 0 || ((i + a == i) && (j + b == j)))
			{
				continue;
			}
			else
			{
				if (Judge(i + a, j + b, 10, Pro) > STANDARD2)//�ж��Ƿ���ը��
				{
					mudi[s][0] = i + a;
					mudi[s][1] = j + b;
					s++;
				}
			}
		}
	}

}

//********************************************
//�����ж�Σ�յȼ��ĺ������ж����ӵĽϺ�ѡ��
int good_choice(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int mudi1[20][2])
{
	memset(mudi1, -1, sizeof(mudi1));
	int score = 0;
	if (IsMyChess(cMap, i, j))
	{
		int x = CanOppget(cMap[i][j].chess, i, j, cMap, Pro);
		if (x == 1)
		{
			int y = CanOppget(cMap[i][j].chess, i, j, cMap, Pro);
			if (y == 0 || y == 3)
			{
				if (y == 0)
				{
					score += 150;//3000
				}
				else
				{
					score += 250;//5000
				}
			}
			else if (y == 4 || y == 2)
			{
				if (y == 4)
				{
					score += 0;
				}
				else
				{
					find_bomb(i1, j1, Pro, cMap, mudi1);
					if (mudi1[0][0] == -1)
					{
						score += 0;
					}
					else
					{
						score -= 200;//2000
					}
				}
			}
			else
			{
				score -= 300;//5000
			}
		}
		else if (x == 2)
		{
			find_bomb(i, j, Pro, cMap, mudi1);
			if (mudi1[0][0] == -1)
			{
				score += 0;
			}
			else
			{
				score -= 300;//2000
			}
		}
		else if (x == 0 || x == 3)
		{
			if (x == 0)
			{
				score += 150;//3000
			}
			else
			{
				score += 300;//5000
			}
		}
		else
		{
			score += 0;
		}
	}
	return score;
}


//****************************************
//��һ�ţ�������ǰը���ں󣬿��þ�����ǰ��
int b_c_gofirst(int i, int j, int i1, int j1, Map cMap[12][5])
{
	int score = 0;
	if ((i == 6 && j == 0) && cMap[i][j].chess == 'b')
	{
		if (cMap[i + 1][j].chess == 'k')
		{
			if (i1 == i - 1 && j1 == j)
			{
				score += 150;//3000
			}
		}
	}
	return score;
}


//*****************************************
//ը�����Ƚ�������Ӫ
int bombgo(int i, int j, int i1, int j1, Map cMap[12][5])
{
	int score = 0;
	if (cMap[i][j].chess == 'k')
	{
		if (!IsMoveCamp(i,j))
		{
			if ((i1 == 7 && j1 == 1) || (i1 == 7 && j1 == 3) || (i1 == 8 && j1 == 2) || (i1 == 9 & j1 == 1) || (i1 == 9 && j1 == 3))
			{
				score += 1000;
			}
		}
	}
	return score;
}

