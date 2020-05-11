#pragma once
//先手快攻	布局		dgeibkgcffekgiadjjicjlhhh


int sselect = 1;//0 为左	1 为右
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

void qipanfentiaozheng()  	//根据进攻方向调整棋盘分
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
	bool junzhang = false;	//判断军长是否存活	true存活		false死亡
	bool shizhang1 = false;//判断前面的师长是否存活
	bool shizhang2 = false;//判断后面的师长是否存活
	bool siling = false;	//判断司令是否存活
	bool gongbing1 = false;		//判断前面的工兵是否存活
	bool gongbing2 = false;		//判断后面的工兵是否存活
	bool gbchudong = false;		//判断是否工兵出击
	bool slchudong = false;		//判断司令出击
	bool dlweixie = true;		//1,4处是否为地雷
	for (int i = 0; i < 12; i++)  		//棋盘扫描	判断司令军长师长工兵的情况
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
	if (sznum == 2)  	//师长数目
	{
		shizhang1 = true;	//师长1存活
		shizhang2 = true;	//师长2存活
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
	if (gbnum == 3)  	//工兵数目
	{
		gongbing1 = true;	//工兵1存活
		gongbing2 = true;	//工兵2存活
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
	if (Judge(1, 4, 9, Pro) == 0)//确认1,4处是否为地雷
	{
		dlweixie = false;
	}
	if (x21 == 6 && y21 == 0)		//【6】【0】处旅长死后炸弹上
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
	if (junzhang == true)  			//军长行棋
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
			else                //满足工兵出击的条件后回撤
			{
				if (i == 2 && j == 4)	//到达地雷前的位置
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
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
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
					}
					else if (i1 == 3 && j1 == 3)//进入3,3处为工兵让道
					{
						score += 3000;
					}
				}
			}
		}
	}
	if (junzhang == false && shizhang1 == true)  		//军长死后师长前进
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
			else                //回撤
			{
				if (i == 2 && j == 4)	//到达地雷前的位置
				{
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
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
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
					{
						if (i1 == 2 && j1 == 3)
						{
							score += 5000;
						}
					}
					else if (i1 == 3 && j1 == 3)//进入3,3处为工兵让道
					{
						score += 3000;
					}
				}
			}
		}
	}
	if (shizhang1 == false)  		//师长死后炸弹炸大子
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

	if (junzhang == false && shizhang1 == false)		//军长师长死后司令行棋
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
			else  if(gbchudong==true)              //回撤
			{
				if (i == 2 && j == 4)	//到达地雷前的位置
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
					if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
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
			else if (dlweixie == false)//解除地雷威胁后继续进攻
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
	
	if (junzhang == true && (cMap[3][3].chess == 'b') || (cMap[2][3].chess == 'b'))//看1,4处是否为地雷
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
	if (junzhang == false && shizhang1 == false)//师长2行棋
	{
		if (cMap[i][j].chess == 'c')
		{
			if (siling == false)
			{
				if (dlweixie == true)//司令死亡且工兵未探明1,4处是否为地雷
				{
					if (cMap[i1][j1].chess == 'X')
					{
						if (i1 > 1 && j1 == 4)
						{
							score += 5000;
						}
					}
					if (gbchudong == true)              //回撤
					{
						if (i == 2 && j == 4)	//到达地雷前的位置
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
							if (IsMoveCamp(2, 3) == 1 && cMap[2][3].chess == '0')//行营为空则进行营
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
				else//探明1,4处不是地雷
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
	if (gbnum == 2)  		//在排完第一个雷后继续向下进发
	{
		if (cMap[1][4].chess == 'i')
		{
			if (i1 == 0 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	else if (gbnum == 1)  	//【1】【4】位置处不是地雷
	{
		if (cMap[i][j].chess == 'a' || cMap[i][j].chess == 'b' || cMap[i][j].chess == 'c')
		{
			if (i1 == 1 && j1 == 4)
			{
				score += 5000;
			}
		}
	}
	//【1】【4】之后进行试雷
	if (cMap[1][4].chess == 'i')  		//【1】【4】处为工兵，继续排雷
	{
		if (cMap[1][3].chess == 'X')
		{
			if (i1 == 1 && j1 == 3)
			{
				score += 5000;
			}
		}
	}
	//工兵在【1】【3】处进入大本营一试
	if (cMap[1][3].chess == 'i')
	{
		if (i1 == 0 && j1 == 3)
		{
			score += 5000;
		}
	}
	//工兵死于【1】【3】处	调用其它棋子去【1】【3】处
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
	//棋子在【1】【3】处进大本营
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
	if (cMap[i][j].chess == 'a')//防止司令撞雷
	{
		if (Judge(i1, j1, 9, Pro) > 2000)
		{
			score -= 5000;
		}
	}
	return score;
}

