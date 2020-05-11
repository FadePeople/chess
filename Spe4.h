#pragma once
//布局:cgeibkicefikggadjjfdjlhhh  右侧进攻
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
	//判断司令 军长 以及进攻侧师长与进攻侧炸弹是否存活
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
	//防守侧
		 //非进攻侧师长不动锁住一边勾引敌人大子或防御薄弱侧
	if (cMap[6][0].chess == 'c')
	{
		if (i0 == 6 && j0 == 0)
		{
			spe4score -= 5000;
		}
	}
	//(7.1)处行营锁死,避免师长对掉的情况下炸弹跑不了
	if (cMap[6][0].chess == 'c'&&i1 == 7 && j1 == 1 && cMap[i0][j0].chess != 'k')
	{
		return spe4score - 7000;
	}
	//非进攻侧炸弹防守
	//如果防守方师长被大子吃掉 炸弹炸掉
	if (i1 == 6 && j1 == 0 && cMap[6][0].chess == 'X')
	{
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 0, Pro) >= 4000)
		{
			spe4score += 8000;
		}
	}
	//如果防守侧师长被换掉 炸弹进行营
	if (cMap[6][0].chess == '0' || Judge(6, 0, 0, Pro) + Judge(6, 0, 1, Pro) <= 4000)
	{
		if (i1 == 7 && j1 == 1)
		{
			return spe4score += 1000;
		}
	}
	//炸弹进营后
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
	//(10,0)处棋子不进行移动冒充地雷骗对面工兵
	if (i0 == 10 && j0 == 0)
	{
		spe4score - 3000;
	}
	//(10,1)处行营必占
	if (i0 != 10 && j0 != 0 && i1 == 10 && j1 == 1)
	{
		spe4score += 1000;
	}


	//进攻侧
	//阵列进攻
	if (cMap[i0][j0].chess == 'b')     //军长向前冲锋
	{
		if (j1 == j0 && i1 <= 6 && i1 >= 2 && cMap[i1][j1].chess == 'X')
			spe4score += 2000;
		//不与地雷;碰撞
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
		//军长巡逻发现敌方就杀
		for (int i = 2;i < 6;i++)
		{
			if (cMap[i][4].chess == 'X'&&Judge(i1, j1, 0, Pro) < 4000)
			{
				if (i1 == i && j1 == 4)
					spe4score += 3000;
			}
		}
	}

	//工兵试雷
	if (cMap[i0][j0].chess == 'i')       //工兵摸对方倒数第二个子
	{
		if (i1 == 1 && j1 == 4)
		{
			spe4score += 3000;
		}
		         //如果摸成了 下一步继续探雷
		if (i1 == 1 && j1 == 3)
		{
				spe4score += 3000;
		}
	}

	if (!junzhang)
	{
		if (cMap[i0][j0].chess == 'c')     //师长向前冲锋
		{
			if (j1 == j0 && i1 <= 6 && i1 >= 2 && cMap[i1][j1].chess == 'X')
			{
				spe4score += 2000;
			}
			if (Judge(i1, j1, 9, Pro) > 3000)
			{
				spe4score -= 1000;
			}
			//师长来回杀
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
			//如果已经打到了后排 继续下一步进攻
			if (i0 == 1 && j0 == 4)
			{
				if (i1 == 1 && j1 == 3)
				{
					spe4score += 2000;
				}
			}
		}
	}
	//炸弹吃大子
	if (cMap[i0][j0].chess == 'k')
	{
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) >= 4000)
		{
			spe4score += 7000;
		}
	}
	if (!junzhang && !shizhang)
	{
		if (cMap[i0][j0].chess == 'a')     //司令向前冲锋
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
			//如果已经打到了后排 继续下一步进攻
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



