#pragma once
//���ֿ칥	����		dgeibkgcffekgiadjjicjlhhh


int sselect = 1;//0 Ϊ��	1 Ϊ��
/*int qipanfen[12][5] = {
	500 ,1000,600 ,1000,800,
	200 ,600 ,500 ,600 ,200,
	250 ,800 ,20  ,800 ,250,
	140 ,20  ,700 ,20  ,140,
	130 ,400 ,20  ,400 ,130,
	120 ,80  ,150 ,80  ,120,
	110 ,100 ,50 ,100 ,110,
	100 ,500 ,150  ,500 ,100,
	100 ,20  ,400 ,20  ,100,
	100 ,600 ,20  ,600 ,100,
	500 ,100 ,100 ,100 ,500,
	200 ,-1000 ,200 ,-1000 ,200 };
	*/

void qipanfentiaozheng()  	//���ݽ�������������̷�
{
	if (sselect == 0)
	{
		for (int i = 2, j = 0; i < 6; i++)
		{
			qipanfen[i][j] += 200;
		}
		qipanfen[4][1] -= 200;
	}
	if (sselect == 1)
	{
		for (int i = 2, j = 4; i < 6; i++)
		{
			qipanfen[i][j] += 200;
		}
		qipanfen[4][3] -= 200;
	}

}


int spe7(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5])
{
	int score = 0, sznum = 0, gbnum = 0;
	bool junzhang = false;	//�жϾ����Ƿ���	true���		false����
	bool shizhang1 = false;//�ж�ǰ���ʦ���Ƿ���
	bool shizhang2 = false;//�жϺ����ʦ���Ƿ���
	bool siling = false;	//�ж�˾���Ƿ���
	bool gongbing1 = false;		//�ж�ǰ��Ĺ����Ƿ���
	bool gongbing2 = false;		//�жϺ���Ĺ����Ƿ���
	bool gbchudong = false;		//�ж��Ƿ񹤱�����
	bool slchudong = false;		//�ж�˾�����
	bool dlweixie = true;		//1,4���Ƿ�Ϊ����
	for (int i = 0; i < 12; i++)  		//����ɨ��	�ж�˾�����ʦ�����������
	{
		for (int j = 0; j < 5; j++)
		{
			if (cMap[i][j].chess == 'b')
			{
				junzhang = true;
			}
			if (cMap[i][j].chess == 'a')
			{
				siling = true;
			}
			if (cMap[i][j].chess == 'c')
			{
				sznum++;
			}
			if (cMap[i][j].chess == 'i')
			{
				gbnum++;
			}
		}
	}
	if ((cMap[2][4].chess == 'b' || cMap[2][4].chess == 'c' || cMap[2][4].chess == 'a') && (cMap[3][4].chess == '0') && (cMap[4][4].chess == '0') && (cMap[5][4].chess == '0') && (cMap[6][4].chess == '0'))
	{
		gbchudong = true;
	}
	if ((cMap[3][4].chess == 'b' || cMap[3][4].chess == 'c' || cMap[3][4].chess == 'a') && (cMap[2][4].chess == '0') && (cMap[4][4].chess == '0') && (cMap[5][4].chess == '0') && (cMap[6][4].chess == '0'))
	{
		gbchudong = true;
	}
	if (sznum == 2)  	//ʦ����Ŀ
	{
		shizhang1 = true;	//ʦ��1���
		shizhang2 = true;	//ʦ��2���
	}
	else if (sznum == 1)
	{
		shizhang1 = false;
		shizhang2 = true;
	}
	else
	{
		shizhang1 = false;
		shizhang2 = false;
	}
	if (gbnum == 3)  	//������Ŀ
	{
		gongbing1 = true;	//����1���
		gongbing2 = true;	//����2���
	}
	else if (gbnum == 2)
	{
		gongbing1 = false;
		gongbing2 = true;
	}
	else
	{
		gongbing1 = false;
		gongbing2 = false;
	}
	if (Judge(1, 4, 9, Pro) == 0)//ȷ��1,4���Ƿ�Ϊ����
	{
		dlweixie = false;
	}
	if (x21 == 6 && y21 == 0)		//��6����0�����ó�����ը����
	{
		if (cMap[x21][y21].chess == 'X')
		{
			if (cMap[i][j].chess == 'k')
			{
				if (i == 7 && j == 0)
				{
					if (i1 == 6 && j1 == 0)
					{
						score += 5000;
					}
				}
			}
		}
	}
	if (junzhang == true)  			//��������
	{
		if (cMap[i][j].chess == 'b')
		{
			if (gbchudong == false)
			{
				if (cMap[i1][j1].chess == 'X')
				{
					if (i1 > 1 && j1 == 4)
					{
						score += 5000;
					}
				}
			}
			else                //���㹤��������������س�
			{
				if (i == 2 && j == 4)	//�������ǰ��λ��
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
						else if (i1 == 3 && j1 == 4)
						{
							score += 5000;
						}
					}
				}
				else if (i == 3 && j == 4)
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
					}
					else if (i1 == 3 && j1 == 3)//����3,3��Ϊ�����õ�
					{
						score += 3000;
					}
				}
			}
		}
	}
	if (junzhang == false && shizhang1 == true)  		//��������ʦ��ǰ��
	{
		if (cMap[i][j].chess == 'c')
		{
			if (gbchudong == false)
			{
				if (cMap[i1][j1].chess == 'X')
				{
					if (j1 == 4 && i1 > 1)
					{
						score += 5000;
					}
				}
			}
			else                //�س�
			{
				if (i == 2 && j == 4)	//�������ǰ��λ��
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
						else if (i1 == 3 && j1 == 4)
						{
							score += 5000;
						}
					}
				}
				else if (i == 3 && j == 4)
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
					}
					else if (i1 == 3 && j1 == 3)//����3,3��Ϊ�����õ�
					{
						score += 3000;
					}
				}
			}
		}
	}
	if (shizhang1 == false)  		//ʦ������ը��ը����
	{
		if (cMap[i][j].chess == 'k')
		{
			if (cMap[i1][j1].chess == 'X')
			{
				if (j1 == 4)
				{
					score += 5000;
				}
			}
		}
	}

	if (junzhang == false && shizhang1 == false)		//����ʦ������˾������
	{
		if (cMap[i][j].chess == 'a')
		{
			if (gbchudong == false)
			{
				if (cMap[i1][j1].chess == 'X')
				{
					if (i1 > 1 && j1 == 4)
					{
						score += 5000;
					}
					else if (i1 == 1 && j1 == 4)
					{
						score -= 30000;
					}
				}
			}
			else  if(gbchudong==true)              //�س�
			{
				if (i == 2 && j == 4)	//�������ǰ��λ��
				{
					if (i1 == 2 && j1 == 3)
					{
						score += 5000;
					}
					else if (i1 == 3 && j1 == 4)
					{
						score += 5000;
					}
				}
				else if (i == 3 && j == 4)
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
					}
					else if (i1 == 3 && j1 == 3)
					{
						score += 3000;
					}
				}
			}
			else if (dlweixie == false)//���������в���������
			{
				if (cMap[3][3].chess == 'a'||cMap[2][3].chess=='a')
				{
					if (i1 > 0 && j1 == 4)
					{
						score += 2500;
					}
				}
			}
		}
	}
	
	if (junzhang == true && (cMap[3][3].chess == 'b') || (cMap[2][3].chess == 'b'))//��1,4���Ƿ�Ϊ����
	{
		if (cMap[i][j].chess == 'i')
		{
			if (i1 == 1 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	else if (junzhang == false && shizhang1 == true && (cMap[3][3].chess == 'c') || (cMap[2][3].chess == 'c'))
	{
		if (cMap[i][j].chess == 'i')
		{
			if (i1 == 1 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	else if (junzhang == false && shizhang1 == false && (cMap[3][3].chess == 'a') || (cMap[2][3].chess == 'a'))
	{
		if (cMap[i][j].chess == 'i')
		{
			if (i1 == 1 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	if (junzhang == false && shizhang1 == false)//ʦ��2����
	{
		if (cMap[i][j].chess == 'c')
		{
			if (siling == false)
			{
				if (dlweixie == true)//˾�������ҹ���δ̽��1,4���Ƿ�Ϊ����
				{
					if (cMap[i1][j1].chess == 'X')
					{
						if (i1 > 1 && j1 == 4)
						{
							score += 5000;
						}
					}
					if (gbchudong == true)              //�س�
					{
						if (i == 2 && j == 4)	//�������ǰ��λ��
						{
							if (i1 == 2 && j1 == 3)
							{
								score += 7000;
							}
							else if (i1 == 3 && j1 == 4)
							{
								score += 7000;
							}
						}
						else if (i == 3 && j == 4)
						{
							if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//��ӪΪ�������Ӫ
							{
								if (i1 == 2 && j1 == 3)
								{
									score += 7000;
								}
							}
							else if (i1 == 3 && j1 == 3)
							{
								score += 7000;
							}
						}
					}
				}
				else//̽��1,4�����ǵ���
				{
					if (dlweixie == false)
					{
						if (cMap[i1][j1].chess == 'X')
						{
							if (i1 > 0 && j1 == 4)
							{
								score += 5000;
							}
						}
					}
				}
			}
		}
	}
	if (gbnum == 2)  		//�������һ���׺�������½���
	{
		if (cMap[1][4].chess == 'i')
		{
			if (i1 == 0 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	else if (gbnum == 1)  	//��1����4��λ�ô����ǵ���
	{
		if (cMap[i][j].chess == 'a' || cMap[i][j].chess == 'b' || cMap[i][j].chess == 'c')
		{
			if (i1 == 1 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	//��1����4��֮���������
	if (cMap[1][4].chess == 'i')  		//��1����4����Ϊ��������������
	{
		if (cMap[1][3].chess == 'X')
		{
			if (i1 == 1 && j1 == 3)
			{
				score += 5000;
			}
		}
	}
	//�����ڡ�1����3���������Ӫһ��
	if (cMap[1][3].chess == 'i')
	{
		if (i1 == 0 && j1 == 3)
		{
			score += 5000;
		}
	}
	//�������ڡ�1����3����	������������ȥ��1����3����
	if (Judge(1, 3, 9, Pro) <= 1000)
	{
		if (i1 == 1 && j1 == 3)
		{
			score += 5000;
		}
		else if (j1 == 4)
		{
			if (i1 == 1)
			{
				score += 5000;
			}
			else
			{
				if (i1 == 1)
				{
					score +=5000;
				}
			}
		}
	}
	//�����ڡ�1����3��������Ӫ
	if (cMap[1][3].chess != '0'&&cMap[1][3].chess != 'X')
	{
		if (i == 1 && j == 3)
		{
			if (i1 == 0 && j1 == 3)
			{
				score += 5000;
			}
		}
	}
	if (cMap[i][j].chess == 'a')//��ֹ˾��ײ��
	{
		if (Judge(i1, j1, 9, Pro) > 2000)
		{
			score -= 5000;
		}
	}
	return score;
}

