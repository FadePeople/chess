#pragma once
int pinggu(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int deep)
{
	int zha = 0;                                  //��¼�ҷ�ը������
	char mchess[25];                              //���ڽ��ҷ����Ӱ������Ӵ�С���򲢱���
	int score = 0, weixief = 0, qipan = 0, jweixief = 0, sanyif = 0, teshu = 0;//���ַ�
	bool sanyi1 = false, sanyi2 = false, sanyi3 = false;//��������һ��ģ��Ͷ���ģ��Ĳ�������
	Map cmap[12][5], cmap1[12][5];                //����ģ���α����
	int k1, k2, k3;                               //��������
	int allmove1[200][2], allmove2[200][2];       //���ڴ��һ��ģ�������ģ����߷�
	int x = 0;                                    //��¼ʦ������
	int i2, j2, i3, j3;                           //ѭ���ñ���
	int flag = 0, flag1, flag2 = 0;               //��������
	int flag3 = 0, flag4 = 0;                     //��������
	int flagz = 0;                                //��������
	FILE *fp;
	fp = fopen("�������պ����ѧ.txt", "a");
	for (i2 = 0; i2 < 12; i2++)
	{
		for (j2 = 0; j2 < 5; j2++)
			cmap[i2][j2] = cMap[i2][j2];
	}
	cmap[i1][j1] = cmap[i][j];
	cmap[i][j].chess = '0';

	if (Pro[1][11] == 0)
		cMap[0][3].chess = 'L';
	if (Pro[3][11] == 0)
		cMap[0][1].chess = 'L';
	mychessdx(cMap, mchess);
	/******************************************************************************************************************/
	//�����ϴ�����Ӻ�ը������������Ӫ�����ӣ�31��Ӱ���µĹ�ܣ�
	if ((i1 == 11 && j1 == 1) || (i1 == 11 && j1 == 3))
	{
		if (cMap[i][j].chess <= mchess[3] || cMap[i][j].chess == 'k')
			teshu = teshu - 10000;
	}
	fprintf(fp, "\n�����ϴ�����Ӻ�ը������������Ӫ������ %d ", teshu);
	/******************************************************************************************************************/
	//��ֹ����������
	if (cMap[i1][j1].chess == 'X' && i1 < 2)                ///////////////////////////////
	{
		if (Ina_step[0] == 2 && Ina_step[1] > 12)  //��ִ��31��
		{
			if (cMap[i][j].chess < 'e' && Judge(i1, j1, 9, Pro)>4000)
				teshu = teshu - 4000;       ///////////////////////////
			if ((cMap[i][j].chess == 'f' || cMap[i][j].chess == 'g' || cMap[i][j].chess == 'h') && Judge(i1, j1, 9, Pro) > 4000)
				teshu = teshu - 2000;
		}
		else
		{
			if (cMap[i][j].chess < 'e' && Judge(i1, j1, 9, Pro)>4000)
				teshu = teshu - 6000;       ///////////////////////////
			if ((cMap[i][j].chess == 'f' || cMap[i][j].chess == 'g' || cMap[i][j].chess == 'h') && Judge(i1, j1, 9, Pro) > 4000)
				teshu = teshu - 5000;
		}
	}
	fprintf(fp, "\n��ֹ��������Ӱ��������� %d ", teshu);
	/******************************************************************************************************************/
	//��Ӫ�����ез����ӣ�������Ӫ
	if (IsMoveCamp(i, j) && (cMap[i + 1][j].chess == 'X' || cMap[i + 1][j + 1].chess == 'X' || cMap[i + 1][j - 1].chess == 'X' || cMap[i][j + 1].chess == 'X' || cMap[i][j - 1].chess == 'X' || cMap[i - 1][j - 1].chess == 'X' || cMap[i - 1][j].chess == 'X' || cMap[i - 1][j + 1].chess == 'X'))
	{
		if (i == 9 && (j == 1 || j == 3) && cMap[i1][j1].chess == '0')
			teshu = teshu - 1000;
		else if (i == 8 && j == 2)
			teshu = teshu - 2000;
		else if (cMap[i][j].chess > 'd' && cMap[i1][j1].chess == 'X')
			teshu = teshu - 800;
		else if (cMap[i][j].chess <= 'd' && cMap[i1][j1].chess == 'X')
			teshu = teshu + 500;
		else
			teshu = teshu - 500;
	}
	fprintf(fp, "\n��Ӫ�����ез����ӣ�������ӪӰ��� ����� %d ", teshu);
	//����Ӫ�����ез����ӣ���ռ��Ӫ
	if (IsMoveCamp(i1, j1) && (cMap[i1 + 1][j1].chess == 'X' || cMap[i1 + 1][j1 + 1].chess == 'X' || cMap[i1 + 1][j1 - 1].chess == 'X' || cMap[i1][j1 + 1].chess == 'X' || cMap[i1][j1 - 1].chess == 'X' || cMap[i1 - 1][j1 - 1].chess == 'X' || cMap[i1 - 1][j1].chess == 'X' || cMap[i1 - 1][j1 + 1].chess == 'X'))
	{
		teshu = teshu + 1000;
	}
	fprintf(fp, "\n����Ӫ�����ез����ӣ���ռ��Ӫ Ӱ��������� %d ", teshu);
	/******************************************************************************************************************/
	//ը������������ۿ��������ҿ�����̬����
	//ը��������ʹ��
	//ը����Դ��ӻ���
	if ((Judge(2, 1, 0, Pro) + Judge(2, 1, 1, Pro) + Judge(2, 1, 2, Pro) + Judge(2, 1, 3, Pro)) > 6000)   //��
	{
		if (cMap[i][j].chess == 'k')
		{
			if (j1 == 0)
				if (i1 == 1 || i1 == 2 || i1 == 3)
				{
					teshu = teshu + 8000;
				}
		}
		else
			teshu -= 5000;
	}
	if ((Judge(2, 3, 0, Pro) + Judge(2, 3, 1, Pro) + Judge(2, 3, 2, Pro) + Judge(2, 3, 3, Pro)) > 6000)   //�һ�
	{
		if (cMap[i][j].chess == 'k')
		{
			if (j1 == 4)
				if (i1 == 1 || i1 == 2 || i1 == 3)
				{
					teshu = teshu + 8000;
				}
		}
		else
			teshu -= 5000;
	}
	//�˴��ѽ�return�޸�Ϊteshu+=
	//����ը���÷�
	int  NextNumberOfSteps = nextmove1(i1, j1, cmap, allmove1);    //����ģ�⣿
	char mc[25];
	mychessdx(cMap, mc);//���ҷ����Ӱ������Ӵ�С���в�����mc�С�Ȼ����������ȫ��ͬ���ܵ����ݺ���䣬�Ҳ�֪�����ڸ�ʲô
	if ((Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 2, Pro)) > 7000)
	{
		if (cMap[i][j].chess == 'k')
		{
			fp = fopen("�������պ����ѧ.txt", "a");
			fprintf(fp, "\nը��ը�˵з��ϴ�����");
			fclose(fp);
			teshu += 30000;
		}
	}
	//�ⲿ���ǹ涨ը��Ŀ�귶Χ
	for (i2 = 0; i2 < 12; i2++)  // �Ҽ���ը������Ŀ
	{
		for (j2 = 0; j2 < 5; j2++)
			if (cMap[i2][j2].chess == 'k')
				zha++;
	}
	int f = 0;//���ڼ�¼�Է�˾��������˼���
	for (int m = 0; m < 25; m++)  //�жϵз�˾��;����Ƿ�����
	{
		if (Pro[m][0] >= 8000 && Pro[m][12] > 12)
			f++;
		if (Pro[m][1] >= 8000 && Pro[m][12] > 13)
			f++;
	}
	if (zha == 2)
	{
		if (f == 2)//�з�������˾��ȫ������
		{
			if (cMap[i][j].chess == 'k')
			{
				if (Judge(i1, j1, 2, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) + Judge(i1, j1, 3, Pro) >= 9000)  //ը����˾�������ʦ�����ó�
					teshu = teshu + 9000;
			}
		}
		if (f == 1 || f == 0)//�з�������˾������һ��
		{
			if (cMap[i][j].chess == 'k')
			{
				if (Judge(i1, j1, 2, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) >= 9000)  //ը����˾�������ʦ��
					teshu = teshu + 9000;
			}
		}
	}
	if (zha == 1)
	{
		if (cMap[i][j].chess == 'k')
		{
			if (Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) + Judge(i1, j1, 2, Pro) >= 9000)  //ը����˾�������ʦ��
				teshu = teshu + 9000;
		}
	}
	//ը������вʱ����
	flag = 0;
	flag1 = 0;
	for (int m = 0; m < 12; m++)
	{
		for (int n = 0; n < 5; n++)
		{
			k1 = Oppnextmove(m, n, cMap, allmove1);//�Է��Ƿ�������������ij
			for (k2 = 0; k2 < k1; k2++)
			{
				if (allmove1[k2][0] == i && allmove1[k2][1] == j)
					flag = 1;
			}
		}
	}
	for (int m = 0; m < 12; m++)
	{
		for (int n = 0; n < 5; n++)
		{
			k1 = Oppnextmove(m, n, cmap, allmove1);//�Է��Ƿ�������������i1j1
			for (k2 = 0; k2 < k1; k2++)
			{
				if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
					flag1 = 1;
			}
		}
	}
	if (cMap[i][j].chess == 'k')
	{
		if (flag == 1 && flag1 == 0)
			teshu = teshu + 1000;
		else
			teshu = teshu - 1000;
	}
	fprintf(fp, "\nը��������ʹ��Ӱ�������� %d ", teshu);
	/******************************************************************************************************************/
	//4.��������(����������)	
	flag = 0;
	flag1 = 0;
	flag3 = 0;
	flag4 = 0;
	sanyi1 = false;
	if (cMap[i][j].chess == 'i')
	{
		flag = walei(cMap, Pro);
		if (flag == 1)
		{
			if (Judge(i1, j1, 9, Pro) > 4500)   //�����ڵ���
			{
				sanyi1 = true;
				teshu = teshu + 4000;
			}
			if (sanyi1 == false && cMap[i1][j1].chess == '0')
			{
				for (int m = 0; m < 12; m++)
				{
					for (int n = 0; n < 5; n++)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2 < k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								flag3 = 1;
						}
					}
				}
				if (flag3 == 0)
					teshu = teshu + 2000;
			}
		}
		if (flag == 0)
		{
			if (Judge(i1, j1, 10, Pro) >= 4000)   ///������ը��
			{
				teshu = teshu + 4000;
			}
		}
		///���������з�����
		flag = 0;
		for (int m = 0; m < 12; m++)
		{
			for (int n = 0; n < 5; n++)
			{
				k1 = Oppnextmove(m, n, cMap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (allmove1[k2][0] == i && allmove1[k2][1] == j)
						flag = 1;
				}
			}
		}
		for (int m = 0; m < 12; m++)
		{
			for (int n = 0; n < 5; n++)
			{
				k1 = Oppnextmove(m, n, cmap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
						flag1 = 1;
				}
			}
		}
		if (flag == 1 && flag1 == 0)
			teshu = teshu + 1000;
		else
			teshu = teshu - 1000;
		if (IsMoveCamp(i1, j1))
			teshu = teshu + 300;
		/**************************************************************************************************************/
	}
	sanyi1 = false;
	flag3 = 0;
	flag = 0;
	if (cMap[i][j].chess > 'e' && cMap[i][j].chess < 'i')
	{
		if (Judge(i1, j1, 10, Pro) >= 4000)   //С��������ը��
		{
			teshu = teshu + 4000;
		}
	}
	if (i >= 10)
		teshu = teshu - 300;
	fprintf(fp, "\n�������÷�Ӱ���������ֵ %d ", teshu);
	fprintf(fp, "\n�ҷ����ƶ������� %d", MyMovingChess(cMap));
	fprintf(fp, "\nͬ��    %d \n��ǰ�����ǵ�%d��", teshu, deep);
	fclose(fp);
	/******************************************************************************************************************/
	weixief = weixie(i, j, i1, j1, Pro, cMap) / 10;            /////   ��Ϊ�ͼ����в��ͬ/  //weixief=weixie(i,j,i1,j1,Pro,cMap)/5;
	qipan = qipanfen[i1][j1] - qipanfen[i][j];
	jweixief = jweixie(i1, j1, Pro, cmap) / 10;
	if (NumChess(cMap) <= 15)
		sanyif = _31Step(i, j, i1, j1, Pro, cMap, cmap, mchess) * 10;
	else
		sanyif = _31Step(i, j, i1, j1, Pro, cMap, cmap, mchess);
	score = weixief + qipan + jweixief + sanyif + teshu;
	fp = fopen("�������պ����ѧ.txt", "a");
	fprintf(fp, "\n%s,%d,%s,%d,%s,%d,%s,%d,%s,%d\n%c %d,%d,%d,%d\n", "ֱ����в", weixief, "�����в", jweixief, "��ʮһ����ֵ", sanyif, "�����", teshu, "�ܷ�", score, cMap[i][j].chess, i, j, i1, j1);
	fclose(fp);
	return score;
}

