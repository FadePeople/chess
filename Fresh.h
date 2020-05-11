#pragma once
/* ************************************************************************ */
/* �������ܣ����յķ���														*/
/* �ӿڲ�����																*/
/*     nΪ����λ��	 											            */
/*     iΪ���Ӵ�С			           									    */
/*     sfen���ʱ�����ķ�	                 					            */
/*     int Pro[25][14]  ���ʱ�                                              */
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
				Pro[n][8] = 10000;		//������ֵ��10000
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
					Pro[n][8] = 10000;		//������ֵ��10000
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
							Pro[n][8] = 10000;		//������ֵ��10000
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
						Pro[n][8] = 10000;		//������ֵ��10000
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
/* ************************************************************************ */
/* �������ܣ�ˢ��G0״̬�µ����� 											*/
/*                  ���Է����壬�ҶԷ����ӱ������Ե�,�Է���������С�ڼ����� */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�з����ӣ�           							*/
/*     int i2,j2  ������꣨�������ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
/* ************************************************************************ */
void shuaxinG0(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	//m=6
	int i, n, n1;
	int zong = 1, sfen = 0;
	if ((i2 == 6 && j2 == 4) || (i2 == 6 && j2 == 0))
		huang1 = 1;
	//���Ӻ�û�ж������ų�ը���Ŀ�����
	for (n = 0; n < 25; n++)
	{
		if (Pro[n][12] == i1 && Pro[n][13] == j1)
		{
			if (Pro[n][10] != 0)
			{
				for (i = 0; i < 25; i++)  //ͬһ���ţ���ը��������������
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
	if (IsRailway(i1, j1) && IsRailway(i2, j2))     //�ж������Ƿ�Ϊ����
		if (RefreshSapper(cMap, Pro, i1, j1, i2, j2))
		{
			for (n = 0; n < 25; n++)
			{
				if ((Pro[n][12] == i1) && (Pro[n][12] == j1))
					Pro[n][12] = 14;
			}
			return;
		}
	if (m < 8 && m >= 0)//��������Ϊ˾��������
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
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //��������������λ�ñȼ������Ӵ�ķ�ֵ��     ���Ե�������ֻ��Ϊ�ų��͹��������������ط���Ӧ�����ӵķ�ֵ����
						Pro[n][i] = 0;   			//�з��������������Դ�λ��Ϊ�ȼ������Ӵ�ķ�ֵΪ0
					}
				}
				zong = 1;
				for (i = m + 1; i <= 8; i++)
					zong = zong + Pro[n][i];
				for (i = m + 1; i <= 8; i++) //�������������ط��ȸ�����С�ķ�ֵ����
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);                                                        //���λ��Ϊ�ų�����Ӧ�����ط�Ϊ�ų��ĵĸ��ʼ���
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
	if (m == 9)//��������Ϊ����
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i == 8 || i == 10) && Pro[n][i] != 10000)    //����ը�����߹���
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
				for (i = 0; i < 8; i++) //�������������ط�Ϊ˾�����ų��ķ�ֵ����
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
/* �������ܣ�ˢ��G1״̬�µ����� 											*/
/*                  ���Է����壬�ҶԷ��Ե���������,�Է������������ڼ�����   */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�з����ӣ�           							*/
/*     int i2,j2  ������꣨�������ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
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
	//���Ӻ�û�ж������ų�ը���Ŀ�����
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
	//�Ե��ҷ����ף��Է�Ϊ����
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
	if (m < 9 && m > 0)//��������Ϊ����������		m>0
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
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //��������������λ�ñȼ�������С�ķ�ֵ��
						Pro[n][i] = 0;            //�����������������Դ�λ��Ϊ�ȼ�������С�ķ�ֵΪ0
					}
				}
				zong = 1;
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //�������������ط��ȸ����Ӵ�ķ�ֵ����
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
/* �������ܣ�ˢ��G2״̬�µ����� 											*/
/*                  ���Է����壬����,�Է������������ڼ�����                 */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�з����ӣ�           							*/
/*     int i2,j2  ������꣨�������ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
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
	if (m < 9 && m >= 0)//��������Ϊ˾��������
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i1 && Pro[n][13] == j1)
			{
				Pro[n][12] = 14;
				if (m == 0)  //��������Ϊ˾��
				{
					if (jq == 1)//�Է�����Ϊ˾��
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
					else      //�Է�����Ϊը��
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
				else   //��������Ϊ����������
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
	if (m == 9)   //��������Ϊ����
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
/* �������ܣ�ˢ��G3״̬�µ����� 											*/
/*                  ���Է����壬���ƶ���                                    */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�з����ӣ�           							*/
/*     int i2,j2  ������꣨�������ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
/* ************************************************************************ */
void shuaxinG3(Map cMap[12][5], int i1, int j1, int i2, int j2, int Pro[25][14]) //���ƶ�����
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
/* �������ܣ�ˢ��R0״̬�µ����� 											*/
/*                  ���������壬�ҶԷ��Ե���������,�Է������������ڼ�����   */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�������ӣ�           							*/
/*     int i2,j2  ������꣨�з����ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
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
	if (m == 8)//��������Ϊ����
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i == 8 || i == 9 || i == 10) && Pro[n][i] != 10000)    //����,����,ը��������
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //��������������λ�ñȼ�������С�ķ�ֵ��
						Pro[n][i] = 0;            //�����������������Դ�λ�õ���ը����ֵΪ0
					}
				}
				zong = 1;    //   ��  û�е��ף�
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //�������������ط��ȸ����Ӵ�ķ�ֵ����
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}

			}
		}
	}
	if (m < 8 && m>0)//��������Ϊ�������ų�
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && ((i >= m && i < 9) || (i == 10)) && Pro[n][i] != 10000)    //�����ų�������
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //��������������λ�ñȼ�������С�ķ�ֵ��
						Pro[n][i] = 0;            //�����������������Դ�λ��Ϊ�ȼ�������С�ķ�ֵΪ0(�����ܵ�����)
					}
				}
				zong = 1;    //   ��  û�е��ף�
				for (i = 0; i < m; i++)
					zong = zong + Pro[n][i];
				for (i = 0; i < m; i++) //�������������ط��ȸ����Ӵ�ķ�ֵ����
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}

			}
		}
	}
	if (m == 0)// ��������Ϊ˾��з�Ϊ����
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
	//���Ӻ�û�ж������ų�ը���Ŀ�����
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
/* �������ܣ�ˢ��R1״̬�µ����� 											*/
/*                  ���������壬�Ҽ����Ե��Է�����,�Է���������С�ڼ�����   */
/* �ӿڲ�����																*/
/*     int m ����������������С											*/
/*     int i1,ji  ������꣨�������ӣ�           							*/
/*     int i2,j2  ������꣨�Է����ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
/* ************************************************************************ */
void shuaxinR1(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{   //m=6
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (m < 8 && m >= 0)//��������Ϊ˾�����ų�
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
				for (i = 0; i < 12; i++)
				{
					if (Pro[n][i] != 0 && (i <= m || i > 8) && Pro[n][i] != 10000)    //�����ų����߹���
					{
						if (i == 0 || i == 1 || i == 11)
							zong = 10000;
						else if (i > 5 && i < 10)
							zong = 30000;
						else
							zong = 20000;
						for (n1 = 0; n1 < 25; n1++)
							if (n1 != n && Pro[n1][i] < 9000)
								Pro[n1][i] = (int)(1.0*Pro[n1][i] * (1 + 1.0*Pro[n][i] / (zong - Pro[n][i])));    //��������������λ�ñȼ������Ӵ�ķ�ֵ��     ���Ե�������ֻ��Ϊ�ų��͹��������������ط���Ӧ�����ӵķ�ֵ����
						Pro[n][i] = 0;            //�з��������������Դ�λ��Ϊ�ȼ������Ӵ�ķ�ֵΪ0
					}
				}
				zong = 1;
				for (i = m + 1; i <= 8; i++)
					zong = zong + Pro[n][i];
				for (i = m + 1; i <= 8; i++) //�������������ط��ȸ�����С�ķ�ֵ����
				{
					sfen = (int)(1.0 * 10000 * Pro[n][i] / zong - Pro[n][i]);
					souhui(n, i, sfen, Pro);                                                        //���λ��Ϊ�ų�����Ӧ�����ط�Ϊ�ų��ĵĸ��ʼ���
					Pro[n][i] = (int)(1.0 * 10000 * Pro[n][i] / zong);
				}
			}
		}
	}
	if (m == 8)//����Ϊ�������з�Ϊ����
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
	//���Ӻ�û�ж������ų�ը���Ŀ�����
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
/* �������ܣ�ˢ��R2״̬�µ����� 											*/
/*                  ���Է����壬����,�Է������������ڼ�����                 */
/* �ӿڲ�����																*/
/*     int m ����������������С											    */
/*     int i1,ji  ������꣨�������ӣ�           							*/
/*     int i2,j2  ������꣨�з����ӣ�	                 					*/
/*     int Pro[25][14]  ���ʱ�                                               */
/* ************************************************************************ */
void shuaxinR2(int m, Map cMap[12][5], int Pro[25][14], int i1, int j1, int i2, int j2)
{
	int i, n, n1;
	int zong = 1, sfen = 0;
	if (m < 9 && m >= 0)//��������Ϊ˾��������
	{
		for (n = 0; n < 25; n++)
		{
			if (Pro[n][12] == i2 && Pro[n][13] == j2)
			{
				Pro[n][12] = 14;
				if (m == 0)  //��������Ϊ˾��
				{
					if (jq == 1)//�Է�����Ϊ˾��
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
					else      //�Է�����Ϊը��
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
				else   //��������Ϊ����������
				{
					if (m < 2)//�����������Ϊʦ�����ϣ���ô�з����ӿ���Ϊը��
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

						zong = Pro[n][m] + Pro[n][10] + 1;  //��ֹ��ĸΪ0������

						sfen = (int)(1.0 * 10000 * Pro[n][m] / zong - Pro[n][m]);
						souhui(n, m, sfen, Pro);
						Pro[n][m] = (int)(1.0 * 10000 * Pro[n][m] / zong);

						sfen = (int)(1.0 * 10000 * Pro[n][10] / zong - Pro[n][10]);
						souhui(n, 10, sfen, Pro);
						Pro[n][10] = (int)(1.0 * 10000 * Pro[n][10] / zong);
					}
					else//�з�����Ϊʦ�����£��򲻿���ը���ĸ���
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
/* �������ܣ����ݲ��з���ˢ������											*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     char *cInMessage ���Բ��е�GO YXYX R YX����							*/
/*     char *cOutMessage �������е�BESTMOVE YXYX����						*/
/* ************************************************************************ */
void FreshMap(Map cMap[12][5], char *cInMessage, char *cOutMessage, int Pro[25][14])
{
	int x1, y1;				//���					//x1,y1,x2,y2,result��char�͸�Ϊint�ͣ�ûʲôӰ��
	int x2, y2;				//���
	int result = -1, k;			//���ӽ��
	int n, i, j, n1, zong = 1;

	if (cInMessage[0] == 'G')	// GO ָ��
	{
		if (cInMessage[3] >= 'A' && cInMessage[3] <= 'L')																					//x,y���귢���Ի�����Ϊ��ϰ��
		{
			y1 = cInMessage[3] - 'A';
			x1 = cInMessage[4] - '0';
			y2 = cInMessage[5] - 'A';
			x2 = cInMessage[6] - '0';
			result = cInMessage[8] - '0';		//���ӽ��
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
			if ((cInMessage[10] >= 'A') && (cInMessage[10] <= 'L') && (comm == 0)) //�Է�˾��ս������ʾ����λ��
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
				for (n = 0; n < 25; n++)  //��һ����ʾ����λ�ã�֤���Է���ȥ����Ϊ˾��
				{
					if (Pro[n][12] == y1 && Pro[n][13] == x1)
					{
						for (i = 0; i < 25; i++)  //�Ժ��ŵ�ˢ��
						{
							for (j = 1; j < 12; j++)
							{
								if (j == 0 || j == 1 || j == 11)
									zong = 10000;           //˾������;��춼ֻ��һ��
								else if (j > 5 && j < 10)
									zong = 10000 * 3;         //ÿ�����ӹ���3��
								else
									zong = 10000 * 2;         //ÿ������������
								if ((10000 - Pro[i][0] > 0) && (i != n) && (zong - Pro[n][j] > 0))
								{
									Pro[i][j] = (int)((double)Pro[i][j] + (double)Pro[i][0] * (double)Pro[i][j] / (double)(10000 - Pro[i][0]) + (double)Pro[i][j] * (double)Pro[n][j] / (double)(zong - Pro[n][j]));
									//��˾���ͬһ��ͬһ�е����Ӹ��ʱ��
									Pro[i][0] = 0;  //��˾��ͬһ�е����� ��������
									Pro[n][j] = 0;  //��˾��ͬһ�е����ӷ�������
								}
							}
						}
						Pro[n][0] = 10000;
					}
				}
			}
			/////�жϵ��׵ĸ���///////////
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
			switch (result)		//���ݲ�ͬ����޸�����
			{
			case 0:			//�Է����ӱ������Ե�
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';  //�յ�Ϊ��������
				shuaxinG0(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y1][x1].chess = '0';
				break;
			case 1:			//�Է��Ե���������
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';//�յ�Ϊ��������
				shuaxinG1(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1].chess = '0';
				break;
			case 2:			//˫�����Ӷ���
				Ina_step[0] = 2;
				Ina_step[1] = 0;
				k = cMap[y2][x2].chess - 'a';//�յ�Ϊ��������
				shuaxinG2(k, cMap, Pro, y1, x1, y2, x2);
				cMap[y1][x1] = Empty;
				cMap[y2][x2] = Empty;
				break;
			case 3:			//�Է��ƶ����ӡ�����///�� ��Ӫը����������
				Ina_step[1]++;
				shuaxinG3(cMap, y1, x1, y2, x2, Pro);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1] = Empty;
				break;
			}
		}
	}
	if (cInMessage[0] == 'R')	// RESULT ָ��
	{
		y1 = cOutMessage[9] - 'A';
		x1 = cOutMessage[10] - '0';
		y2 = cOutMessage[11] - 'A';
		x2 = cOutMessage[12] - '0';
		result = cInMessage[7] - '0';		//������
		if (IsBaseCamp(y2, x2))  //�����Ӫ��û�н���ս�� ��һ����Ӫ����Ǿ���
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
		if ((cInMessage[8] == ' ') && (cInMessage[9] >= 'A') && (cInMessage[9] <= 'L') && (comm == 0)) //�Է�˾��ս������ʾ����λ��
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
			for (n = 0; n < 25; n++)  //��һ����ʾ����λ�ã�֤���Է���ȥ����Ϊ˾��
			{
				if (Pro[n][12] == y1 && Pro[n][13] == x1)
				{
					for (i = 0; i < 25; i++)  //�Ժ��ŵ�ˢ��
					{
						for (j = 1; j < 12; j++)
						{
							if (j == 0 || j == 1 || j == 11)
								zong = 10000;           //˾������;��춼ֻ��һ��
							else if (j > 5 && j < 10)
								zong = 10000 * 3;         //ÿ�����ӹ���3��
							else
								zong = 10000 * 2;         //ÿ������������
							if ((10000 - Pro[i][0] > 0) && (i != n) && (zong - Pro[n][j] > 0))
							{
								Pro[i][j] = (int)((double)Pro[i][j] + (double)Pro[i][0] * (double)Pro[i][j] / (double)(10000 - Pro[i][0]) + (double)Pro[i][j] * (double)Pro[n][j] / (double)(zong - Pro[n][j]));
								//��˾���ͬһ��ͬһ�е����Ӹ��ʱ��
								Pro[i][0] = 0;  //��˾��ͬһ�е����� ��������
								Pro[n][j] = 0;  //��˾��ͬһ�е����ӷ�������
							}
						}
					}
					Pro[n][0] = 10000;
				}
			}
		}
		switch (result)		//���ݲ�ͬ����޸�����
		{
		case 0:			//�������ӱ��Է��Ե�
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';  //���Ϊ��������
			shuaxinR0(k, cMap, Pro, y1, x1, y2, x2);//���ݼ���������ˢ�²²���ʱ�
			cMap[y1][x1] = Empty;
			break;
		case 1:			//�����Ե��Է�����
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';
			shuaxinR1(k, cMap, Pro, y1, x1, y2, x2);
			cMap[y2][x2] = cMap[y1][x1];
			cMap[y1][x1] = Empty;
			break;
		case 2:			//˫�����Ӷ���
			Ina_step[0] = 1;
			Ina_step[1] = 0;
			k = cMap[y1][x1].chess - 'a';
			shuaxinR2(k, cMap, Pro, y1, x1, y2, x2);
			cMap[y1][x1] = Empty;
			cMap[y2][x2] = Empty;
			break;
		case 3:			//�����ƶ�����
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
	int a, b, c;//ѭ������
	int sum = 0;
	int flat = 0;
	for (i = 0; i < 25; i++)
	{
		k = 0;
		for (j = 0; j < 12; j++)   //�жϺ����Ƿ��һ���ط��и���
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
		if (k == 11)    //���ž�һ���ط��и��ʻ�����һ���ӵĸ��ʴ���9000
		{
			if (flat == 0)
			{
				for (c = 0; c < 12; c++)
				{
					if (Pro[i][c] < 50)
					{
						Pro[i][c] = 0;         //�����ŵ���50�ֵĵط�����
					}
					else {
						Pro[i][c] = 10000;         //������󴦸�����Ϊ10000
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
			for (b = 0; b < 12; b++)     //�ж������ܷ��ٲ���
			{
				sum = 0;
				for (a = 0; a < 25; a++)
				{
					sum = sum + Pro[a][b];
				}
				if (b == 0 || b == 1 || b == 11)
					zong = 10000;           //˾������;��춼ֻ��һ��
				else if (b > 5 && b < 10)
					zong = 10000 * 3;         //ÿ�����ӹ���3��
				else
					zong = 10000 * 2;         //ÿ������������
				if (sum < zong)            //�����ܷ���
				{
					for (n = 0; n < 25; n++)
					{
						if ((Pro[n][b] < 10000) && (sum != 0))
						{
							Pro[n][b] = (int)(1.0*Pro[n][b] * (1 + 1.0*(zong - sum) / sum));  //���ٵ��Ĳ��ּӵ�����
						}
					}
				}
			}
		}
	}
	FILE *fp;
	fp = fopen("�������պ����ѧ.txt", "a");
	fprintf(fp, "\n\n\n\n\n\n\n\n��%d���Ŀ�ʼ   ��ʱ��ʮһ���Ĳ���%d:\n", qqqqqq + 1, Ina_step[1]);
	for (int i = 0; i != 12; i++)
	{
		for (int j = 0; j != 5; j++)
		{
			if (cMap[i][j].chess == 'X')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'L')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == '0')
				fprintf(fp, "oo");
			if (cMap[i][j].chess == 'a')
				fprintf(fp, "˾ ");
			if (cMap[i][j].chess == 'b')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'c')
				fprintf(fp, "ʦ ");
			if (cMap[i][j].chess == 'd')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'e')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'f')
				fprintf(fp, "Ӫ ");
			if (cMap[i][j].chess == 'g')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'h')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'i')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'j')
				fprintf(fp, "�� ");
			if (cMap[i][j].chess == 'k')
				fprintf(fp, "ը ");
			if (cMap[i][j].chess == 'l')
				fprintf(fp, "�� ");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	FILE *abcd = fopen("�������պ����ѧ.txt", "a");
	fprintf(abcd, "\n�˴�Ϊ���ʱ�\n");
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
