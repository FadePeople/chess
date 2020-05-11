#pragma once
int pinggu(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5], int deep)
{
	int zha = 0;                                  //记录我方炸弹数量
	char mchess[25];                              //用于将我方棋子按棋力从大到小排序并保存
	int score = 0, weixief = 0, qipan = 0, jweixief = 0, sanyif = 0, teshu = 0;//各种分
	bool sanyi1 = false, sanyi2 = false, sanyi3 = false;//疑似用于一步模拟和二步模拟的布尔变量
	Map cmap[12][5], cmap1[12][5];                //用于模拟的伪棋盘
	int k1, k2, k3;                               //常数变量
	int allmove1[200][2], allmove2[200][2];       //用于存放一步模拟和两步模拟的走法
	int x = 0;                                    //记录师长数量
	int i2, j2, i3, j3;                           //循环用变量
	int flag = 0, flag1, flag2 = 0;               //布尔变量
	int flag3 = 0, flag4 = 0;                     //布尔变量
	int flagz = 0;                                //布尔变量
	FILE *fp;
	fp = fopen("沈阳航空航天大学.txt", "a");
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
	//己方较大的棋子和炸弹不碰己方大本营的棋子（31步影响下的规避）
	if ((i1 == 11 && j1 == 1) || (i1 == 11 && j1 == 3))
	{
		if (cMap[i][j].chess <= mchess[3] || cMap[i][j].chess == 'k')
			teshu = teshu - 10000;
	}
	fprintf(fp, "\n己方较大的棋子和炸弹不碰己方大本营的棋子 %d ", teshu);
	/******************************************************************************************************************/
	//阻止大子碰地雷
	if (cMap[i1][j1].chess == 'X' && i1 < 2)                ///////////////////////////////
	{
		if (Ina_step[0] == 2 && Ina_step[1] > 12)  //该执行31步
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
	fprintf(fp, "\n阻止大子碰雷影响后的特殊分 %d ", teshu);
	/******************************************************************************************************************/
	//行营外面有敌方棋子，不让行营
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
	fprintf(fp, "\n行营外面有敌方棋子，不让行营影响的 特殊分 %d ", teshu);
	//空行营附近有敌方棋子，抢占行营
	if (IsMoveCamp(i1, j1) && (cMap[i1 + 1][j1].chess == 'X' || cMap[i1 + 1][j1 + 1].chess == 'X' || cMap[i1 + 1][j1 - 1].chess == 'X' || cMap[i1][j1 + 1].chess == 'X' || cMap[i1][j1 - 1].chess == 'X' || cMap[i1 - 1][j1 - 1].chess == 'X' || cMap[i1 - 1][j1].chess == 'X' || cMap[i1 - 1][j1 + 1].chess == 'X'))
	{
		teshu = teshu + 1000;
	}
	fprintf(fp, "\n空行营附近有敌方棋子，抢占行营 影响后的特殊分 %d ", teshu);
	/******************************************************************************************************************/
	//炸弹部分请谨慎观看，反正我看完心态崩了
	//炸弹保护和使用
	//炸弹针对大子护旗
	if ((Judge(2, 1, 0, Pro) + Judge(2, 1, 1, Pro) + Judge(2, 1, 2, Pro) + Judge(2, 1, 3, Pro)) > 6000)   //左护
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
	if ((Judge(2, 3, 0, Pro) + Judge(2, 3, 1, Pro) + Judge(2, 3, 2, Pro) + Judge(2, 3, 3, Pro)) > 6000)   //右护
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
	//此处已将return修改为teshu+=
	//补充炸弹用法
	int  NextNumberOfSteps = nextmove1(i1, j1, cmap, allmove1);    //用于模拟？
	char mc[25];
	mychessdx(cMap, mc);//将我方棋子按棋力从大到小排列并存于mc中。然而上面有完全相同功能的数据和语句，我不知道他在干什么
	if ((Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 2, Pro)) > 7000)
	{
		if (cMap[i][j].chess == 'k')
		{
			fp = fopen("沈阳航空航天大学.txt", "a");
			fprintf(fp, "\n炸弹炸了敌方较大棋子");
			fclose(fp);
			teshu += 30000;
		}
	}
	//这部分是规定炸弹目标范围
	for (i2 = 0; i2 < 12; i2++)  // 找己方炸弹的数目
	{
		for (j2 = 0; j2 < 5; j2++)
			if (cMap[i2][j2].chess == 'k')
				zha++;
	}
	int f = 0;//用于记录对方司令军长死了几个
	for (int m = 0; m < 25; m++)  //判断敌方司令和军长是否死亡
	{
		if (Pro[m][0] >= 8000 && Pro[m][12] > 12)
			f++;
		if (Pro[m][1] >= 8000 && Pro[m][12] > 13)
			f++;
	}
	if (zha == 2)
	{
		if (f == 2)//敌方军长和司令全部死掉
		{
			if (cMap[i][j].chess == 'k')
			{
				if (Judge(i1, j1, 2, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) + Judge(i1, j1, 3, Pro) >= 9000)  //炸弹碰司令，军长，师长或旅长
					teshu = teshu + 9000;
			}
		}
		if (f == 1 || f == 0)//敌方军长和司令死掉一个
		{
			if (cMap[i][j].chess == 'k')
			{
				if (Judge(i1, j1, 2, Pro) + Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) >= 9000)  //炸弹碰司令，军长或师长
					teshu = teshu + 9000;
			}
		}
	}
	if (zha == 1)
	{
		if (cMap[i][j].chess == 'k')
		{
			if (Judge(i1, j1, 1, Pro) + Judge(i1, j1, 0, Pro) + Judge(i1, j1, 2, Pro) >= 9000)  //炸弹碰司令，军长或师长
				teshu = teshu + 9000;
		}
	}
	//炸弹受威胁时开溜
	flag = 0;
	flag1 = 0;
	for (int m = 0; m < 12; m++)
	{
		for (int n = 0; n < 5; n++)
		{
			k1 = Oppnextmove(m, n, cMap, allmove1);//对方是否有棋子能碰到ij
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
			k1 = Oppnextmove(m, n, cmap, allmove1);//对方是否有棋子能碰到i1j1
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
	fprintf(fp, "\n炸弹保护和使用影响的特殊分 %d ", teshu);
	/******************************************************************************************************************/
	//4.工兵行棋(保护与挖雷)	
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
			if (Judge(i1, j1, 9, Pro) > 4500)   //工兵挖地雷
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
			if (Judge(i1, j1, 10, Pro) >= 4000)   ///工兵碰炸弹
			{
				teshu = teshu + 4000;
			}
		}
		///工兵躲闪敌方棋子
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
		if (Judge(i1, j1, 10, Pro) >= 4000)   //小的棋子碰炸弹
		{
			teshu = teshu + 4000;
		}
	}
	if (i >= 10)
		teshu = teshu - 300;
	fprintf(fp, "\n工兵的用法影响后的特殊分值 %d ", teshu);
	fprintf(fp, "\n我方可移动棋子数 %d", MyMovingChess(cMap));
	fprintf(fp, "\n同上    %d \n当前层数是第%d层", teshu, deep);
	fclose(fp);
	/******************************************************************************************************************/
	weixief = weixie(i, j, i1, j1, Pro, cMap) / 10;            /////   改为和间接威胁相同/  //weixief=weixie(i,j,i1,j1,Pro,cMap)/5;
	qipan = qipanfen[i1][j1] - qipanfen[i][j];
	jweixief = jweixie(i1, j1, Pro, cmap) / 10;
	if (NumChess(cMap) <= 15)
		sanyif = _31Step(i, j, i1, j1, Pro, cMap, cmap, mchess) * 10;
	else
		sanyif = _31Step(i, j, i1, j1, Pro, cMap, cmap, mchess);
	score = weixief + qipan + jweixief + sanyif + teshu;
	fp = fopen("沈阳航空航天大学.txt", "a");
	fprintf(fp, "\n%s,%d,%s,%d,%s,%d,%s,%d,%s,%d\n%c %d,%d,%d,%d\n", "直接威胁", weixief, "间接威胁", jweixief, "三十一步分值", sanyif, "特殊分", teshu, "总分", score, cMap[i][j].chess, i, j, i1, j1);
	fclose(fp);
	return score;
}

