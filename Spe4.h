#pragma once
//����:cgeibkicefikggadjjfdjlhhh  �Ҳ����
void reqipanfen()
{
	qipanfen[4][0] += 200;
	qipanfen[4][1] += 200;
	qipanfen[4][2] += 200;
	qipanfen[4][3] += 200;
	qipanfen[4][4] += 200;
	qipanfen[4][5] += 200;
	qipanfen[3][1] += 200;
}
int spe4(int i0, int j0, int i1, int j1, int Pro[25][14],Map cMap[12][5])
{
	int spe4score = 1000;
	//�ж�˾�� ���� �Լ�������ʦ���������ը���Ƿ���
	bool zhadan = false;
	bool shizhang = false;
	bool junzhang = false;
	bool siling = false;
	for (int i = 0;i < 12;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (cMap[i][j].chess == 'b')
			{
				junzhang = true;
			}
			if (cMap[i][j].chess == 'a')
			{
				siling = true;
			}
			if (j > 2 && cMap[i][j].chess == 'k')
			{
				zhadan = true;
			}
			if (i != 6 && j != 0 && cMap[i][j].chess == 'c')
			{
				shizhang = true;
			}
		}
	}
	//���ز�
		 //�ǽ�����ʦ��������סһ�߹������˴��ӻ����������
	if (cMap[6][0].chess == 'c')
	{
		if (i0 == 6 && j0 == 0)
		{
			spe4score -= 5000;
		}
	}
	//(7.1)����Ӫ����,����ʦ���Ե��������ը���ܲ���
	if (cMap[6][0].chess == 'c'&&i1 == 7 && j1 == 1 && cMap[i0][j0].chess != 'k')
	{
		return spe4score - 7000;
	}
	//�ǽ�����ը������
	//������ط�ʦ�������ӳԵ� ը��ը��
	if (i1 == 6 && j1 == 0 && cMap[6][0].chess == 'X')
	{
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 0, Pro) >= 4000)
		{
			spe4score += 8000;
		}
	}
	//������ز�ʦ�������� ը������Ӫ
	if (cMap[6][0].chess == '0' || Judge(6, 0, 0, Pro) + Judge(6, 0, 1, Pro) <= 4000)
	{
		if (i1 == 7 && j1 == 1)
		{
			return spe4score += 1000;
		}
	}
	//ը����Ӫ��
	if (i0 == 7 && j0 == 1)
	{
		if (cMap[i1][j1].chess == '0')
		{
			spe4score -= 1000;
		}
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) <= 4000)
		{
			spe4score -= 1000;
		}
	}
	//(10,0)�����Ӳ������ƶ�ð�����ƭ���湤��
	if (i0 == 10 && j0 == 0)
	{
		spe4score - 3000;
	}
	//(10,1)����Ӫ��ռ
	if (i0 != 10 && j0 != 0 && i1 == 10 && j1 == 1)
	{
		spe4score += 1000;
	}


	//������
	//���н���
	if (cMap[i0][j0].chess == 'b')     //������ǰ���
	{
		if (j1 == j0 && i1 <= 6 && i1 >= 2 && cMap[i1][j1].chess == 'X')
			spe4score += 2000;
		//�������;��ײ
		if (Judge(i1, j1, 9, Pro) > 3000)
		{
			spe4score -= 6000;
		}
		if (cMap[3][4].chess == '0'&&cMap[4][4].chess == '0'&&cMap[5][4].chess == '0'&&cMap[6][4].chess == '0')
		{
			if (i1 == 7 && j1 == 4)
			{
				spe4score += 3500;
			}
			if (i1 == 2 && j1 == 3)
			{
				spe4score += 3500;
			}
			if (i1 == 4 && j1 == 3)
			{
				spe4score += 3500;
			}
		}
		//����Ѳ�߷��ֵз���ɱ
		for (int i = 2;i < 6;i++)
		{
			if (cMap[i][4].chess == 'X'&&Judge(i1, j1, 0, Pro) < 4000)
			{
				if (i1 == i && j1 == 4)
					spe4score += 3000;
			}
		}
	}

	//��������
	if (cMap[i0][j0].chess == 'i')       //�������Է������ڶ�����
	{
		if (i1 == 1 && j1 == 4)
		{
			spe4score += 3000;
		}
		         //��������� ��һ������̽��
		if (i1 == 1 && j1 == 3)
		{
				spe4score += 3000;
		}
	}

	if (!junzhang)
	{
		if (cMap[i0][j0].chess == 'c')     //ʦ����ǰ���
		{
			if (j1 == j0 && i1 <= 6 && i1 >= 2 && cMap[i1][j1].chess == 'X')
			{
				spe4score += 2000;
			}
			if (Judge(i1, j1, 9, Pro) > 3000)
			{
				spe4score -= 1000;
			}
			//ʦ������ɱ
			for (int i = 2;i < 6;i++)
			{
				if (cMap[i][4].chess == 'X'&&Judge(i1, j1, 0, Pro) < 4000)
				{
					if (i1 == i && j1 == 4)
						spe4score += 2000;
				}
			}
			if (cMap[3][4].chess == '0'&&cMap[4][4].chess == '0'&&cMap[5][4].chess == '0'&&cMap[6][4].chess == '0')
			{
				if (i1 == 7 && j1 == 4)
				{
					spe4score += 3500;
				}
				if (i1 == 2 && j1 == 3)
				{
					spe4score += 3500;
				}
				if (i1 == 4 && j1 == 3)
				{
					spe4score += 3500;
				}
			}
			//����Ѿ����˺��� ������һ������
			if (i0 == 1 && j0 == 4)
			{
				if (i1 == 1 && j1 == 3)
				{
					spe4score += 2000;
				}
			}
		}
	}
	//ը���Դ���
	if (cMap[i0][j0].chess == 'k')
	{
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) >= 4000)
		{
			spe4score += 7000;
		}
	}
	if (!junzhang && !shizhang)
	{
		if (cMap[i0][j0].chess == 'a')     //˾����ǰ���
		{
			if (j1 == j0 && i1 <= 6 && i1 >= 2 && cMap[i1][j1].chess == 'X')
			{
				spe4score += 2000;
			}
			if (Judge(i1, j1, 9, Pro) > 3000)
			{
				spe4score -= 4000;
			}
			for (int i = 2;i < 6;i++)
			{
				if (cMap[i][4].chess == 'X'&&Judge(i1, j1, 0, Pro) < 4000)
				{
					if (i1 == i && j1 == 4)
						spe4score += 1000;
				}
			}
			if (cMap[3][4].chess == '0'&&cMap[4][4].chess == '0'&&cMap[5][4].chess == '0'&&cMap[6][4].chess == '0')
			{
				if (i1 == 7 && j1 == 4)
				{
					spe4score += 3500;
				}
				if (i1 == 2 && j1 == 3)
				{
					spe4score += 3500;
				}
				if (i1 == 4 && j1 == 3)
				{
					spe4score += 3500;
				}
			}
			//����Ѿ����˺��� ������һ������
			if (i0 == 1 && j0 == 4)
			{
				if (i1 == 1 && j1 == 3)
				{
					spe4score += 2000;
				}
			}
		}
	}
	return spe4score;
}



