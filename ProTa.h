#pragma once				//�ϸ�ͷ�ļ�ֻ����һ��


/* ************************************************************************ */
/* �������ܣ��ж���ĳ�����ӵĸ���                                      		*/
/* �ӿڲ�����																*/
/*     int i													            */
/*     int j		  ��Ҫ�ж����ӵ�λ��								    */
/*     int k		  ���ӱ��  											*/
/*     int Pro[25][14] �з����Ӹ���							                */
/* ************************************************************************ */
int Judge(int i, int j, int k, int Pro[25][14])
{
	for (int n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i && Pro[n][13] == j)
			return Pro[n][k];
	}
	return 0;
}


int qipanfen[12][5] = {     //��ʼ���̷�
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


/* ************************************************************************ */
/* �������ܣ����ݵ��Ҿ���λ���趨�ķ���                                     */
/* �ӿڲ�����																*/
/*     Map cMap       Ŀǰ������								            */
/*     int Pro		  ���ʱ�											    */
/* ************************************************************************ */
void jushipg(Map cMap[12][5], int Pro[25][14])
{
	if (cMap[11][1].chess == 'l')//���������λ������
	{
		qipanfen[6][0] = 130;
		qipanfen[7][0] = 120;
		qipanfen[7][1] = 600;
		qipanfen[8][0] = 120;
		qipanfen[8][1] = 80;
		qipanfen[9][0] = 120;
		qipanfen[9][1] = 700;
		qipanfen[10][0] = 600;
		qipanfen[10][1] = 200;
	}
	if (cMap[11][3].chess == 'l')//���������λ������
	{
		qipanfen[6][4] = 130;
		qipanfen[7][4] = 120;
		qipanfen[7][3] = 600;
		qipanfen[8][4] = 120;
		qipanfen[8][3] = 80;
		qipanfen[9][4] = 120;
		qipanfen[9][3] = 700;
		qipanfen[10][4] = 600;
		qipanfen[10][3] = 200;
	}
	if (Pro[1][11] >= 10000)//������������Ӫ�ľ���ִﵽ10000�֣��������ֽ����޸�
	{
		qipanfen[0][3] = -10000;
		qipanfen[0][4] = -10000;
		qipanfen[0][1] = 10000;
		qipanfen[0][0] = 600;
		qipanfen[1][0] = 400;
		qipanfen[1][1] = 700;
		qipanfen[2][0] = 300;
		qipanfen[2][1] = 900;
		qipanfen[3][0] = 240;
		qipanfen[3][1] = 100;
		qipanfen[4][0] = 230;
		qipanfen[4][1] = 500;
		qipanfen[5][0] = 220;
	}
	if (Pro[3][11] >= 10000)//������������Ӫ�ľ���ִﵽ10000�֣��������ֽ����޸�
	{
		qipanfen[0][1] = -10000;
		qipanfen[0][0] = -10000;
		qipanfen[0][3] = 10000;
		qipanfen[0][4] = 600;
		qipanfen[1][4] = 400;
		qipanfen[1][3] = 700;
		qipanfen[2][4] = 300;
		qipanfen[2][3] = 900;
		qipanfen[3][4] = 240;
		qipanfen[3][3] = 100;
		qipanfen[4][4] = 230;
		qipanfen[4][3] = 500;
		qipanfen[5][4] = 220;
	}
}


/* ************************************************************************ */
/* �������ܣ�         ���շ���                             		            */
/* �ӿڲ�����																*/
/*     int n		  Ҫ���յ����ӣ������ʱ���ĳһ�У�						*/
/*     int i		  �������											    */
/*     int sfen		  ���ӱ��  											*/
/*     int Pro[25][14] �з����Ӹ���							                */
/* ************************************************************************ */
void souhui(int n, int i, int sfen, int Pro[25][14])         //sfen ���յķ���   nΪ����λ��   iΪ���Ӵ�С
{
	int zong = 0;
	int n1;
	if (sfen == 0)
		return;
	if (i == 0 || i == 1 || i == 11)//��Ϊ˾�����������ֻ��һ���������ܷ�Ϊ10000
		zong = 10000;
	else if (i > 5 && i < 10)//���м�����Ӹ���Ϊ3���ܷ�Ϊ30000
		zong = 30000;
	else//ʣ�µ�Ϊ20000
		zong = 20000;
	for (n1 = 0; n1 < 25; n1++)
	{
		if (n1 != n && (zong - Pro[n][i]) != 0 && Pro[n1][i] < 9500)
			Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 - 1.0*sfen / (zong - Pro[n][i])));
	}
}



/* ************************************************************************ */
/* �������ܣ�ˢ�¹����ĸ��� 							    				*/
/* �ӿڲ�����																*/
/*     char cMap ���� 											            */
/*     int i1,ji  ������꣨�з����ӳ�ʼ���꣩           				    */
/*     int i2,j2  �������	                 					            */
/*     int Pro[25][14]  ���ʱ�                                              */
/* ************************************************************************ */
int RefreshSapper(Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	int n, n1;
	int i, j;
	int zong = 0;
	if ((i1 != i2) && (j1 != j2))//����յ㲻��һ������
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				//Pro[n][12] = 14;00
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && i != 8 && Pro[n][i] != 10000)//�Ѳ��ǹ��������������°�Ȩ����ã�10000��0������Ϊ���Ѿ�ȷ������
					{
						if (i == 0 || i == 1 || i == 11)//˾�����������ֻ��һ��
							zong = 10000;
						else if (i > 5 && i < 10)//��֮�ڵ���������
							zong = 30000;
						else//���м����������
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)//�������°�Ȩ������ʱ�
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));
						Pro[n][i] = 0;
					}
				}
				souhui(n, 8, 10000 - Pro[n][8], Pro);
				Pro[n][8] = 10000;		//������ֵ��10000
			}
		}
		return 1;
	}
	else if ((i1 == i2) && (j1 != j2))//��һ��������
	{
		if ((i1 != 1) && (i1 != 5) && (i1 != 6) && (i1 != 10))//����2��6��7��11��������
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
					Pro[n][8] = 10000;		//������ֵ��10000
				}
			}
			return 1;
		}
		else//��2��6��7��11��������
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
							Pro[n][8] = 10000;		//������ֵ��10000
							return 1;
						}
					}
				}
			}
			return 0;
		}
	}
	else if ((i1 != i2) && (j1 == j2))//��һ����
	{
		if ((j1 != 0) && (j1 != 4))//����1��4����
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
						Pro[n][8] = 10000;		//������ֵ��10000
						return 1;
					}
				}
			}
			return 0;
		}
		else//��1��4����
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
							Pro[n][8] = 10000;		//������ֵ��10000
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