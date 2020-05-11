#pragma once
//布阵   cggiadfekbckegfhdiihjljhj

int spe8(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5])
{
	int allmove1[200][2];
	int spe6score = 0;
	//有司令一侧行营不占
	if (cMap[6][0].chess == 'a'&&IsFilledCamp(cMap, 7, 1) == 0)
	{
		if (i1 == 7 && j1 == 1)
			spe6score -= 1000;//减分
	}
	if (cMap[6][4].chess == 'a'&&IsFilledCamp(cMap, 7, 3) == 0)
	{
		if (i1 == 7 && j1 == 3)
			spe6score -= 1000;//减分
	}
	//无司令一侧炸弹占营
	if (cMap[6][0].chess != 'a'&&IsFilledCamp(cMap, 7, 1) == 0)//司令在右前
	{
		if (cMap[8][0].chess == 'k' || cMap[7][0].chess == 'k')
		{
			if (i1 == 7 && j1 == 1)
				spe6score += 1000;
		}
	}
	if (cMap[6][4].chess != 'a'&&IsFilledCamp(cMap, 7, 3) == 0)//司令在左前
	{
		if (cMap[8][4].chess == 'k' || cMap[7][4].chess == 'k')
		{
			if (i1 == 7 && j1 == 1)
				spe6score += 1000;
		}
	}
	//炸弹占营后如果师长被吃用炸弹炸掉
	if (IsOppChess(cMap, 6, 0) == 1 && cMap[7][1].chess == 'k')
	{
		if (i1 == 6 && j1 == 0)
		{
			spe6score += 1000;//炸比师长大的子，加分
		}
		else spe6score += 0;
	}
	//营，团，旅，师协助大子护旗
	struct point
	{
		int x, y;
		char zhonglei;
	}point[25];//结构体point用来存储查找结果，x,y为坐标，种类为棋子种类
	if (NumChess(cMap) <= 16)//在中期查找除了司令军长外较大棋子
	{
		int ii, jj;
		for (ii = 0; ii < 12; ii++)
			for (jj = 0; jj < 5; jj++)
			{
				if (cMap[i][j].chess >= 'c'&&cMap[i][j].chess <= 'g')
				{
					int t = 0;
					point[t].x = i;
					point[t].y = j;
					point[t].zhonglei = cMap[i][j].chess;
					t++;
				}
			}
	}
	//搜索出中等棋子后将中等棋子移向军旗


	//后两排棋子不会主动移动用以伪装地雷
	if (cMap[10][0].chess <= 'i'&&cMap[10][0].chess >= 'a')
	{
		if (i == 10 && j == 0)//左后方伪装
		{
			if ((cMap[10][0].IsTouched == 0 && i1 != 10) || (cMap[10][0].IsTouched == 0 && j1 != 0))
			{
				spe6score -= 0;//未被碰即移动，不能伪装成地雷，扣分
			}
		}

	}
	if (cMap[10][4].chess <= 'i'&&cMap[10][4].chess >= 'a')
	{
		if (i == 10 && j == 4)//右后方伪装
		{
			if ((cMap[10][4].IsTouched == 0 && i1 != 10) || (cMap[10][4].IsTouched == 0 && j1 != 4))
			{
				spe6score -= 0;//未被碰即移动，不能伪装成地雷，扣分
			}
		}
	}
	//在两个边路被吃后两个大本营前兵站内棋子不动接着伪装地雷
	if (cMap[10][0].chess == '0')//左侧大本营
	{
		if (cMap[10][1].IsTouched == 0)
		{
			if (i1 != 10 || j1 != 1)
			{
				spe6score -= 1000;//减分
			}

		}
	}
	if (cMap[10][4].chess == '0')//右侧大本营
	{
		if (cMap[10][3].IsTouched == 0)
		{
			if (i1 != 10 || j1 != 3)
			{
				spe6score -= 2000;//减分
			}
		}

	}
	//中间行营在司令进行大子护旗之前不能被占
	if (cMap[9][1].chess != 'a')
	{
		if ((i == 8 && j == 0)||(i==8&&j==1)||(i==9&&j==0)||(i==9&&j==2))
		{
			if (i1 == 9 && j1 == 1)
				spe6score -= 1000;
		}
	}
	//司令骗子后回营进行大子护旗
	if (huang1 == 1 && cMap[6][4].chess == 'a')//进右上营
	{
		if (i1 == 7 && j1 == 3)
		{
			spe6score += 1000;
		}
	}
	if (huang1 == 1 && cMap[7][3].chess == 'a')//右上营进中营
	{
		if (i1 == 8 && j1 == 2)
		{
			spe6score += 2000;
		}
	}
	if (huang1 == 1 && cMap[8][2].chess == 'a')//中营进左下，实现大子护旗
	{
		if (i1 == 9 && j1 == 1)
		{
			spe6score += 2000;
		}
	}
	//护旗
	//军棋左前旅长被吃，判定为大子，司令出
	if (IsOppChess(cMap, 10, 0) == 1 && Judge(10, 0, 1, Pro) >= 2500)
	{
		if (cMap[9][1].chess == 'a'&&i1 == 10 && j1 == 0)
		{
			spe6score += 2500;
		}
	}
	if (IsOppChess(cMap, 10, 0) == 1 && Judge(10, 0, 2, Pro) >= 2500)
	{
		if (cMap[9][1].chess == 'a'&&i1 == 10 && j1 == 0)
		{
			spe6score += 2500;
		}
	}
	//军旗左前被吃后，司令出击后回营
	if (cMap[10][0].chess == 'a'&&IsFilledCamp(cMap,9,1)==0)
	{
		if (i1 == 9 && j1 == 1)
		{
			spe6score += 2500;
		}
	}
	//军旗正前被吃，司令直接上
	if (IsOppChess(cMap, 10, 1) == 1)
	{
		if (cMap[9][1].chess == 'a'&&i1 == 10 && j1 == 1)
		{
			spe6score += 2000;
		}
	}
	//从军旗正前方回营
	if (cMap[10][1].chess == 'a'&&IsFilledCamp(cMap, 9, 1) == 0)
	{
		if (i1 == 9 && j1 == 1)
		{
			spe6score += 2500;
		}
	}
	//准备写小子碰炸弹
	/*if (cMap[i][j].chess >= 'd'&&cMap[i][j].chess <= i)
	{
		if (Judge(i1, j1, 10, Pro) >= 2500 && nextmove1(i, j, cMap, allmove1) >= 1)
		{
			
		}
	}*/
	//最后期工兵挖雷
	/*if (cMap[i][j].chess == 'i')
	{
		int ii, jj;
		if (Judge(ii, jj, 9, Pro) > 2500)
		{
			if (i1 == ii && j1 == jj)
			{
				spe6score += 1500;
			}
		}
	}
	if (cMap[i][j].chess == 'i')
	{
		int ii, jj;
		if (Judge(ii, jj, 10, Pro) > 2500)
		{
			if (i1 == ii && j1 == jj)
			{
				spe6score += 2000;
			}
		}
	}*/
	//盘面已经干净且确定军旗位置后尝试进攻
	if(NumOppChess(cMap))
	{
		if (cMap[0][1].chess == 'L')//确定军旗在左侧
		{
			if (cMap[0][0].chess == '0')
			{
				if (cMap[i][0].chess <= 'e')
				{
					if (i1 == 1 && j1 == 0)
					{
						spe6score += 3000;
					}
				}
			}
			if (cMap[1][0].chess >= 'a'&&cMap[1][0].chess <= 'i')
			{
				if (cMap[0][0].chess == '0')
				{
					if (i1 == 0 && j1 == 0)
					{
						spe6score += 10000;
					}
				}
				if (cMap[1][1].chess == '0')
				{
					if (i1 == 1 && j1 == 1)
					{
						spe6score += 5000;
					}
				}
			}
			if (cMap[0][0].chess >= 'a'&&cMap[0][0].chess <= 'i')
			{
				if (i1 == 0 && j1 == 1)
					spe6score += 50000;
			}
			if (cMap[1][1].chess >= 'a'&&cMap[1][1].chess <= 'i')
			{
				if (i1 == 0 && j1 == 1)
					spe6score += 50000;
			}
		}
		if (cMap[0][3].chess == 'L')//确定军旗在右侧
		{
			if (cMap[0][4].chess == '0')
			{
				if (cMap[i][4].chess <= 'e')
				{
					if (i1 == 1 && j1 == 4)
					{
						spe6score += 3000;
					}
				}
			}
			if (cMap[1][4].chess >= 'a'&&cMap[1][4].chess <= 'i')
			{
				if (cMap[0][4].chess == '0')
				{
					if (i1 == 0 && j1 == 4)
					{
						spe6score += 10000;
					}
				}
				if (cMap[1][3].chess == '0')
				{
					if (i1 == 1 && j1 == 3)
					{
						spe6score += 5000;
					}
				}
			}
			if (cMap[0][4].chess >= 'a'&&cMap[0][4].chess <= 'i')
			{
				if (i1 == 0 && j1 == 3)
					spe6score += 50000;
			}
			if (cMap[1][3].chess >= 'a'&&cMap[1][3].chess <= 'i')
			{
				if (i1 == 0 && j1 == 3)
					spe6score += 50000;
			}
		}
	}
	//己方炸弹炸大子
	if (cMap[7][1].chess == 'k')
	{
		if (Judge(6, 0, 0, Pro) + Judge(6, 0, 1, Pro) >= 4000)
		{
			if (i1 == 6 && j1 == 0)
			{
				spe6score += 2500;
			}
		}
		if (Judge(7, 0, 0, Pro) + Judge(7, 0, 1, Pro) >= 4000)
		{
			if (i1 == 7 && j1 == 0)
			{
				spe6score += 2500;
			}
		}
		if (Judge(8, 0, 0, Pro) + Judge(8, 0, 1, Pro) >= 4000)
		{
			if (i1 == 8 && j1 == 0)
			{
				spe6score += 2500;
			}
		}
	}
	return spe6score;
}
