//ǰ�ڽ��������ڷ��ز���    chbihggkdeedcfkgiijafhjlj 
#pragma once 
/*��Ըò��ֵ���������*/

//�����ڶ���С�����ز������ö��湤����ײ
int Small_Nodong(Map cMap[12][5], int i0, int j0)
{
	int teshu=0;
	if (cMap[i0][j0].chess == 'h' || cMap[i0][j0].chess == 'g' || cMap[i0][j0].chess == 'j'&&i0 == 10 && (j0 == 0 || j0 == 4 || j0 == 2))
		return teshu;
}

//ǰ��һ·ʦ����ǰɱ������ը������
int	sz_sha(Map cMap[12][5], int i, int j, int i1, int j1)
{
	char mchess[25];
	int teshu=0;
	mychessdx(cMap, mchess);
	if (cMap[i][j].chess == 'c' && (i <= 9 && i >= 6) && (j == 0 || j == 4) && NumChess(cMap) >= 15) //ʦ�����ҷ�������ǰ��
	{
		if ((j1 == 4 || j1 == 0) && (11 >= 2 && 11 <= 5))
			teshu += 5000;
	}
	else if (cMap[3][0].chess == 'c' || cMap[2][1].chess == 'c'&&IsFilledCamp(cMap, 2, 1))//ʦ��˺��(3,0)����˺��(2,0)
	{
		if (i1 == 2 && j1 == 0)
			teshu += 5000;
	}
	if (cMap[3][0].chess == 'c' || cMap[2][0].chess == 'c' && !IsFilledCamp(cMap, 2, 1))//ʦ��ռס�������Ӫ
		teshu += 5000;
	else if (cMap[2][1].chess == 'c')
		teshu -= 2000;
	return teshu;
}

//ը������ʦ��
int Pro_sz(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'k'&&Ina_step[0] == 2 && (Judge(i1, j1, 0, Pro) > 5000 || Judge(i1, j1, 1, Pro) > 5000) && (cInMessage[8] - '0') == 1) //�з��д��ӳ��ҷ�ʦ��
	{
		teshu += 5000;
	}
	return teshu;
}

//ը������ըͨһ·�����˳���Ļ�����ƭ����˾����ҷ�ը��
int Bomb_NB(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'k')
	{
		if ((Judge(i1, j1, 0, Pro) > 5000 || Judge(i1, j1, 1, Pro) > 5000) && (cInMessage[8] - '0') == 1) //�ҷ�����ȥը
		{
			if (j1 == 0 || j1 == 4)
				teshu += 5000;
		}
		else if (i1 == 1 && j1 == 0 && cMap[1][0].chess == '0') //ը��ȥ(1,0)
		{
			teshu += 10000;
		}
		else if (i1 == 0 && (j1 == 0 || j1 == 4)) //ը������ը��0,0���ͣ�0,4��
		{
			teshu += 10000;
		}
		else if (i1 == 1 && (j1 == 1 || j1 == 2)) //������ԵĻ�ȥ��1,1����1,2��
		{
			teshu += 5000;
		}
	}
	return teshu;
}

//�ҷ��������ʦ����ը������������·˺��
int Jz_To_middle(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'b')
	{
		if (qqqqqq == 0||qqqqqq==1) //�ҷ���һ������ȥç��5��.2��
		{
			if (i1 == 5 && j1 == 2) 
			{
				teshu += 5000;
			}
		}
		else if (!IsFilledCamp(cMap, 4, 1)&&i1==4&&j1==1) //�����Ƚ�Ҫç��һ·����Ӫ,���ö�������е�ը������Ӫ
			teshu += 5000;
		else if (i == 4 && j == 1 && IsOppChess(cMap, 3, 0) == 1 && IsOppChess(cMap, 4, 0) == 1)//�ҷ��ڣ�4,1����Ӫ
		{
			if (IsOppChess(cMap, 3, 0) == 1 && (cMap[4][1].chess == 'b' || cMap[4][1].chess == 'c') && !IsFilledCamp(cMap, 2, 1))
			{
				teshu += 5000;
			}
			else
				teshu += 2000;
		}
		else if (j1 == 0&&i1>=2&&i1<=5) //��ͨ��һ·
		{
			teshu += 5000;
		}
	}
	return teshu;
}

//�Ҳ�ǰ��˾�����
//��ʱ����
void Ritgt_Pro(char *cInMessage, Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (NumChess(cMap)>15)
	{
		if (cMap[6][4].chess == 'a') //˾���ڣ�6,4��
		{
			if ((cInMessage[8] - '0') == 0) //����С��ײ��˾��
			{
				if (i1 == 7 && j1 == 3) //��Ӫ
					teshu += 10000;
				else if (i1 == 7 && (j1 == 2 || j1 == 3)) //�ز���Ӫ����ɽ���
					teshu += 5000;
			}
		}
		else if (cMap[7][3].chess == 'a')  //˾���Ѿ�����Ӫ
		{
			if (cMap[6][4].chess != 'X'&&cMap[7][4].chess != 'X') //�Ҳ��޵з��ӣ�����������Ӫ��˾�����Ӫ����
			{
				if (IsOppChess(cMap, 6, 2) || IsOppChess(cMap, 6, 3))
					teshu += 5000;
			}
			else if (cMap[6][4].chess != 'X' && (i1 == 7 || i1 == 8) && j1 == 4)  //�ҷ����Ӷ�ס�Է����ܵ�ը����˾����ԳԶ�����
			{
				teshu += 5000;
			}
			else
			{
				if (i1 == 8 && j1 == 2) //ռ����Ӫ
				{
					teshu += 50000;
				}
			}
		}
	}
	else //�������ҷ����巽����أ���ֹ����͵��
	{
		if (cMap[7][3].chess == 'a')
		{
			if (i1 == 8 && j1 == 2)
				teshu += 5000;
		}
		else if (cMap[8][2].chess == 'a')  //��˾����������Ӫ
		{
			if (cMap[11][1].chess == 'l') //�ҷ����������·�
			{
				if (i1 == 9 && j1 == 1)
					teshu += 5000;
			}
			else if (cMap[11][3].chess == 'l') //�ҷ����������·�
			{
				if (i1 == 9 && j1 == 3)
					teshu += 5000;
			}
		}
		else if (cMap[9][1].chess == 'a')
		{
			if (cMap[10][0].chess == 'X' || cMap[10][0].chess == '0') //���ԣ�����˾�����ھ���һ�ౣ������ʱ�����������;���
				teshu += 5000;
			if (cMap[10][j1].chess == 'X')
				teshu += 5000;
		}
		else if (cMap[9][3].chess == 'a')
		{
			if (cMap[10][4].chess == 'X' || cMap[10][5].chess == '0') //���ԣ�����˾�����ھ���һ�ౣ������ʱ�����������;���
				teshu += 5000;
			if (cMap[10][j1].chess == 'X')
				teshu += 5000;
		}
	}
}

//������ç����һ������
int Gb_Go(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[i][j].chess == 'i')
	{
		if (cMap[0][1].chess == 'L')
		{
			if (i1 == 0 && j1 == 1)
				teshu += 500000;
		}
		else if (cMap[0][3].chess == 'L')
		{
			if (i1 == 0 && j1 == 3)
				teshu += 500000;
		}
		else if ((j1 == 1 || j1 == 3) && i == 1)
		{
			if (Judge(i1, j1, 9, Pro) > 4000)
				teshu += 10000;
		}
		return teshu;
	}
}


//������ʱ��˾������ҷ��Ӷ����
int To_flag(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if (cMap[0][1].chess == 'L')
	{
		if (cMap[0][0].chess == '0') //����������û��
		{
			for (int ii = 2; ii <= 10; ii++)
			{
				if (cMap[ii][0].chess == 'a' || cMap[ii][0].chess == 'b')
				{
					if (i1 == 1 && j1 == 0&&cMap[1][0].chess=='0') //�¾���
						teshu += 50000;
				}
			}
			if ((i1 == 0 && j1 == 0)||(cMap[0][2].chess=='0'&&i1==0&&j1==2)) //ȥ��0,0����0,2��
			{
				teshu += 500000;
			}
		}
		if (cMap[0][2].chess == '0'&&i1 == 0 && j1 == 2) //ȥ�м�����
		{
			teshu += 50000;
		}
		if (cMap[1][0].chess == 'k') //ը���ڴ�çͨȥ��������·
		{
			if (i1 == 1 && j1 == 1)
				teshu += 500000;
			if (i1 == 0 && j1 == 0)
				teshu += 600000;
		}
		if (i1 == 0 && j1 == 1) //�����
			teshu += 1000000;
	}
	else if (cMap[0][3].chess == 'L')
	{
		if (cMap[1][4].chess == '0')
		{
			if (i1 == 1 && j1 == 4 && (cMap[i][j].chess == 'a' || cMap[i][j].chess == 'b' || cMap[i][j].chess == 'k'))
				teshu += 50000;
		}
		if (cMap[1][4].chess == 'k') //ը���ڴ�çͨȥ��������·
		{
			if (i1 == 1 && j1 == 3)
				teshu += 50000;
			if (i1 == 0 && j1 == 4)
				teshu += 60000;
		}
		if (cMap[0][4].chess == '0') //�¾����ɱ
		{
			if (i1 == 0 && j1 == 4)
				teshu += 50000;
		}
		if (cMap[1][3].chess == '0')
		{
			if(i1==1&&j1==3)
				teshu += 50000;
		}
		if (cMap[0][2].chess == '0'&&i1 == 0 && j1 == 2) //ȥ�м�����
		{
			teshu += 50000;
		}
		if (i1 == 0 && j1 == 3) //�����
			teshu += 1000000;
	}
	return teshu;
}


//������������ҷ��ӣ���һ������ȥײ��������ը��
int GB_NB(char *cInMessage,Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	if ((cInMessage[8] - '0') == 1)  //�ҷ����Ե�
	{
		if (NumOppChess(cMap) >= 20)
		{
			//�Է����ӵ��ҷ���7,0����8,0��
			if ((Judge(7, 0, 3, Pro) + Judge(7, 0, 3, Pro) + Judge(7, 0, 3, Pro)) > 9000 || (Judge(8, 0, 3, Pro) + Judge(8, 0, 3, Pro) + Judge(8, 0, 3, Pro)) > 9000)
			{
				if (((x11 == 5 && y11 == 0) || (x11 == 6 && y11 == 0)) && ((x21 == 7 && y21 == 0) || (x21 == 8 && y21 == 0)))
					teshu += 50000;
			}
			//�Է����ӵ��ҷ���7,4����8,4��
			else if ((Judge(7, 4, 3, Pro) + Judge(7, 4, 3, Pro) + Judge(7, 4, 3, Pro)) > 9000 || (Judge(8, 4, 3, Pro) + Judge(8, 4, 3, Pro) + Judge(8, 4, 3, Pro)) > 9000)
			{
				if (((x11 == 5 && y11 == 4) || (x11 == 6 && y11 == 4)) && ((x21 == 7 && y21 == 4) || (x21 == 8 && y21 == 4)))
					teshu += 50000;
			}
		}
	}
	return teshu;
}

//��Ըò������˾����ӻ���
int Defend_my(Map cMap[12][5], int i, int j, int i1, int j1, int Pro[25][14])
{
	int teshu=0;
	char mchess[25];
	mychessdx(cMap, mchess);
	if (cMap[11][3].chess == 'l')//����������
	{
		if (cMap[i][j].chess == 'a')
		{
			if (i == 6 && j == 4)
			{
				if ((huang1 == 1 && i1 == 7 && j1 == 3) || ((mchess[1] != 'b' || cMap[7][2].chess == '0') && i1 == 7 && j1 == 3 && cMap[6][2].chess == 'X') || (NumChess(cMap) <= 19 && i1 == 7 && j1 == 3))
					teshu += 100000;
				else
					teshu -= 100000;
			}
		}
		if (cMap[6][2].chess == 'X'&&cMap[7][3].chess == 'a' && (mchess[1] != 'b'))	//�Է�ǿ�������ӣ�˾���1Ӫ
		{
			if (i == 7 && j == 3 && i1 == 6 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[6][2].chess == 'a')
		{
			if (i == 6 && j == 2 && i1 == 7 && j1 == 3)
				teshu += 10000;
		}
		if (cMap[7][2].chess == 'X'&&cMap[7][3].chess == 'a'&&mchess[1] != 'b')//���Ӻ�˾����2Ӫ
		{
			if (i == 7 && j == 3 && i1 == 7 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[7][2].chess == 'a'&&huang2 == 1)
		{
			if (i == 7 && j == 2 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}

		if ((mchess[1] != 'b'&& cMap[7][3].chess == 'a' && cMap[6][2].chess != 'X' && cMap[7][2].chess != 'X') || (cMap[7][3].chess == 'a' && huang1 == 1) || (NumChess(cMap) <= 19))//��2��Ӫ
		{
			if (i == 7 && j == 3 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}
		if (cMap[8][2].chess == 'a') //˾����2Ӫ��ը������Ӫ
		{
			if (cMap[8][3].chess == 'k'&&i == 8 && j == 3 && i1 == 7 && j1 == 3)
				teshu += 15000;
		}
		if (cMap[8][2].chess == 'a')//��3��Ӫ
		{
			if (i == 8 && j == 2 && i1 == 9 && j1 == 3)
				if (cMap[7][2].chess == 'X' && cMap[8][4].chess != 'X' && cMap[9][4].chess != 'X' && cMap[8][3].chess != 'X' && cMap[10][4].chess != 'X' && cMap[10][3].chess != 'X' && cMap[10][2].chess != 'X')
					teshu -= 8000;
				else
					teshu += 8000;
		}
		if (cMap[6][4].chess == 'a' || cMap[7][3].chess == 'a' || cMap[8][2].chess == 'a')//��������������ռ����Ӫ
		{
			if ((i1 == 7 && j1 == 3) || (i1 == 8 && j1 == 2) || (i1 == 9 && j1 == 3))
				teshu -= 8000;
		}
	}
	if (cMap[11][0].chess=='l')//����������
	{
		if (cMap[i][j].chess == 'a')
		{
			if (i == 6 && j == 0)
			{
				if ((huang1 == 1 && i1 == 7 && j1 == 1) || ((mchess[1] != 'b' || cMap[7][2].chess == '0') && i1 == 7 && j1 == 1 && cMap[6][2].chess == 'X') || (NumChess(cMap) <= 19 && i1 == 7 && j1 == 1))
					teshu += 100000;
				else
					teshu -= 100000;
			}
		}
		if (cMap[6][2].chess == 'X'&&cMap[7][1].chess == 'a' && (mchess[1] != 'b'))//�Է�ǿ�������ӣ�˾���1Ӫ
		{
			if (i == 7 && j == 1 && i1 == 6 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[6][2].chess == 'a')
		{
			if (i == 6 && j == 2 && i1 == 7 && j1 == 1)
				teshu += 10000;
		}
		if (cMap[7][2].chess == 'X'&&cMap[7][1].chess == 'a'&&mchess[1] != 'b')//���Ӻ�˾����2Ӫ
		{
			if (i == 7 && j == 1 && i1 == 7 && j1 == 2)
			{
				teshu += 10000;
				huang2 = 1;
			}
		}
		if (cMap[7][2].chess == 'a'&&huang2 == 1)
		{
			if (i == 7 && j == 2 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}

		if ((mchess[1] != 'b'&& cMap[7][1].chess == 'a' && cMap[6][2].chess != 'X' && cMap[7][2].chess != 'X') || (cMap[7][1].chess == 'a' && huang1 == 1) || (NumChess(cMap) <= 19))//��2��Ӫ
		{
			if (i == 7 && j == 1 && i1 == 8 && j1 == 2)
				teshu += 10000;
		}
		if (cMap[8][2].chess == 'a') //˾����2Ӫ��ը������Ӫ
		{
			if (cMap[8][1].chess == 'k'&&i == 8 && j == 1 && i1 == 7 && j1 == 1)
				teshu += 15000;
		}
		if (cMap[8][2].chess == 'a')//��3��Ӫ
		{
			if (i == 8 && j == 2 && i1 == 9 && j1 == 1)
				if (cMap[7][2].chess == 'X' && cMap[8][0].chess != 'X' && cMap[9][0].chess != 'X' && cMap[8][1].chess != 'X' && cMap[10][0].chess != 'X' && cMap[10][1].chess != 'X' && cMap[10][2].chess != 'X')
					teshu -= 8000;
				else
					teshu += 8000;
		}
		if (cMap[6][0].chess == 'a' || cMap[7][1].chess == 'a' || cMap[8][2].chess == 'a')//��������������ռ����Ӫ
		{
			if ((i1 == 7 && j1 == 1) || (i1 == 8 && j1 == 2) || (i1 == 9 && j1 == 1))
				teshu -= 8000;
		}
	}
	return teshu;
}

int spe6(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], char *cInMessage)
{
	int score=0;
	score += Bomb_NB(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Defend_my(cMap, i, j, i1, j1, Pro);
	score += GB_NB(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Gb_Go(cMap, i, j, i1, j1, Pro);
	score+=Jz_To_middle(cMap, i, j, i1, j1, Pro);
	score+=Pro_sz(cInMessage, cMap, i, j, i1, j1, Pro);
	score += Small_Nodong(cMap, i, j);
	score += To_flag(cMap, i, j, i1, j1, Pro);
	score += sz_sha(cMap, i, j, i1, j1);
	return score;
}
