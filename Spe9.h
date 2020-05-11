#pragma once
///布阵cihhbkgkdficgfdaiejeghjlj
int spe9(int i0, int j0, int i1, int j1, int Pro[25][14],Map cMap[12][5])
{
	//a司令, b军长, c师长, d旅长, e团长, f营长, g连长, h排长, i工兵, j地雷k炸弹, l军旗
	int i2, j2, dl = 0;
	int sscore=0;

	// 找己方地雷的数目
	for (i2 = 0; i2 < 12; i2++) 
	{
		for (j2 = 0; j2 < 5; j2++)
			if (cMap[i2][j2].chess == 'j')
				- dl++;
	} 
	//如果地雷没被吃 我方旗子比对方多进行31步 
	if (dl == 3) 
	{
		int n = 0; //我方棋子数	
		int m = 0; //我敌棋子数

		int i, j;
		for (i = 0; i < 12; i++)
			for (j = 0; j < 5; j++)
				if (cMap[i][j].chess >= 'a'&&cMap[i][j].chess <= 'l')
					n++;
		for (i = 0; i < 12; i++)
			for (j = 0; j < 5; j++)
				if (cMap[i][j].chess >= 'A'&&cMap[i][j].chess <= 'X')
					m++;
		if (n > m)//我方棋子多余敌方 进行31步
		{
			if (cMap[i1][j1].chess != 'X')
			{
				sscore += 900;
			}
		}
	}
	//地雷旁有棋子守护防止工兵直接挖雷
	if (cMap[i0][j0].chess == 'j'&&i0 != 0 && i0 != 11)
	{
		if (cMap[i0][j0 + 1].chess >= 'a'&&cMap[i0][j0 + 1].chess <= 'h'&&j0 + 1 < 5)
		{
			sscore += 100;
		}
		if (cMap[i0][j0 - 1].chess >= 'a'&&cMap[i0][j0 - 1].chess <= 'h'&&j0 + 1 >= 0)
		{
			sscore += 100;
		}
	}
	//地雷边上没子 把子移过去
	if (cMap[10][3].chess == 'j' && (cMap[10][2].chess == '0' || cMap[10][4].chess == '0'))
	{
		if (cMap[i0][j0].chess >= 'e'&&cMap[i0][j0].chess <= 'i'&&cMap[10][2].chess == '0')
		{
			if (i1 == 10 && j1 == 2)
			{
				sscore += 200;
			}
		}
		if (cMap[i0][j0].chess >= 'e'&&cMap[i0][j0].chess <= 'i'&&cMap[10][4].chess == '0')
		{
			if (i1 == 10 && j1 == 4)
			{
				sscore += 200;
			}
		}
	}
	if (cMap[10][1].chess == 'j' && (cMap[10][2].chess == '0' || cMap[10][0].chess == '0'))
	{
		if (cMap[i0][j0].chess >= 'e'&&cMap[i0][j0].chess <= 'i'&&cMap[10][2].chess == '0')
		{
			if (i1 == 10 && j1 == 2)
			{
				sscore += 200;
			}
		}
		if (cMap[i0][j0].chess >= 'e'&&cMap[i0][j0].chess <= 'i'&&cMap[10][0].chess == '0')
		{
			if (i1 == 10 && j1 == 0)
			{
				sscore += 200;
			}
		}
	}
	//我方阵营边角要有大子拦截
	//a司令, b军长, c师长, d旅长, e团长, f营长, g连长, h排长, i工兵, j地雷,k炸弹, l军旗
	
	//炸弹优先进行营 进行防守加固
	if (cMap[i0][j0].chess == 'k')
	{
		if ((i1 == 7 && j1 == 1) || (i1 == 7 && j1 == 3) )
		{
			sscore += 500;
		}
		else
		{
			sscore += 0;
		}
	}
	//如果 我方军营 左右边角被吃 直接炸
	//a司令, b军长, c师长, d旅长, e团长, f营长, g连长, h排长, i工兵, j地雷k炸弹, l军旗
	if (cMap[i0][j0].chess == 'k')
	{
		if (cMap[6][0].chess == 'X')
		{
			if (i1 == 6 && j1 == 0)
			{
				sscore += 700;
			}
		}
		if (cMap[6][4].chess == 'X')
		{
			if (i1 == 6 && j1 == 4)
			{
				sscore += 700;
			}
		}
	}
	//如果第十行地雷被吃 第二大子充当地雷守护军旗
	if (cMap[10][3].chess == '0')
	{
		if (cMap[i0][j0].chess <= 'b'&&cMap[i0][j0].chess >= 'e')
		{
			if (i1 == 10 && j1 == 3)
				sscore += 300;
		}
	}
	if (cMap[10][1].chess == '0')
	{
		if (cMap[i0][j0].chess <= 'b'&&cMap[i0][j0].chess >= 'e')
		{
			if (i1 == 10 && j1 == 1)
				sscore += 300;
		}
	}
	//工兵碰炸弹 保护大子
	if (cMap[i0][j0].chess == 'i')
	{
		if (Judge(i1, j1, 10, Pro) >= 3000)   //工兵碰炸弹
		{
			sscore += 500;
		}
	}
	//小子碰炸弹 保护大子
	if (cMap[i0][j0].chess > 'e'&&cMap[i0][j0].chess < 'i')
	{
		if (Judge(i1, j1, 10, Pro) >= 3000)
		{
			sscore += 500;
		}
	}
	//后期工兵排雷
	if (NumChess(cMap) < 12 && NumOppChess(cMap) < 12)
	{
		if (cMap[i0][j0].chess == 'i')
		{
			if (Judge(i1, j1, 9, Pro) >= 3000)
			{
				sscore += 900;
			}
		}
	}
	//保护军旗
	if (cMap[11][1].chess == 'l')
	{
		if (cMap[10][1].chess == 'X' && i1 == 10 && j1 == 1)
			sscore = sscore + (13 - (cMap[i0][j0].chess - 'a')) * 500;
		if (cMap[10][0].chess == 'X' && cMap[11][0].chess== '0' && i1 == 10 && j1 == 0)
			sscore = sscore + (13 - (cMap[i0][j0].chess- 'a')) * 500;
		if (cMap[10][0].chess == 'X' && cMap[11][0].chess == 'j' && Judge(10, 0, 8, Pro) > 6000)
			sscore = sscore + (13 - (cMap[i0][j0].chess - 'a')) * 500;
	}
	if (cMap[11][3].chess == 'l')
	{
		if (cMap[10][3].chess== 'X' && i1 == 10 && j1 == 3)
			sscore = sscore + (13 - (cMap[i0][j0].chess - 'a')) * 500;
		if (cMap[10][4].chess == 'X' && cMap[11][4].chess == '0' && i1 == 10 && j1 == 4)
			sscore = sscore + (13 - (cMap[i0][j0].chess- 'a')) * 500;
		if (cMap[10][4].chess == 'X' && cMap[11][4].chess== 'j' && Judge(10, 4, 8, Pro) > 6000)
			sscore = sscore + (13 - (cMap[i0][j0].chess - 'a')) * 500;
	}
	////炸弹吃司令或军长
	if (cMap[i0][j0].chess == 'k')
	{
		if (Judge(i1, j1, 0, Pro) + Judge(i1, j1, 1, Pro) >= 4000)
		{
			sscore += 700;
		}
	}

	return sscore;
}
////a司令, b军长, c师长, d旅长, e团长, f营长, g连长, h排长, i工兵, j地雷k炸弹, l军旗
