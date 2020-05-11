#pragma once
int walei1(Map cMap[12][5], int Pro[25][14])
{
	int k = 0;
	if (cMap[1][0].chess == '0' || (cMap[1][0].chess == 'X' && Judge(1, 0, 9, Pro) > 5000))
	{
		if (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000))
			k = 1;
		if (cMap[0][0].chess == '0' || (cMap[0][0].chess == 'X' && Judge(0, 0, 9, Pro) > 5000))
			k = 1;
	}
	return k;
}
int walei3(Map cMap[12][5], int Pro[25][14])
{
	int k = 0;
	if (cMap[1][4].chess == '0' || (cMap[1][4].chess == 'X' && Judge(1, 4, 9, Pro) > 5000))
	{
		if (cMap[1][3].chess == '0' || (cMap[1][3].chess == 'X' && Judge(1, 3, 9, Pro) > 5000))
			k = 1;
		if (cMap[0][4].chess == '0' || (cMap[0][4].chess == 'X' && Judge(0, 4, 9, Pro) > 5000))
			k = 1;
	}
	return k;
}
int walei(Map cMap[12][5], int Pro[25][14])//ÅĞ¶ÏµĞ·½¾üÆì¸½½üÊÇ·ñÓĞµØÀ×
{
	int k = 0;
	if (Pro[1][11] > 9000)
	{
		if (cMap[1][0].chess == '0' || (cMap[1][0].chess == 'X' && Judge(1, 0, 9, Pro) > 5000))
		{
			if (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000))
				k = 1;
			if (cMap[0][0].chess == '0' || (cMap[0][0].chess == 'X' && Judge(0, 0, 9, Pro) > 5000))
				k = 1;
		}
		if ((cMap[1][4].chess == '0' || (cMap[1][4].chess == 'X' && Judge(1, 4, 9, Pro) > 5000)) && (cMap[1][3].chess == '0' || (cMap[1][3].chess == 'X' && Judge(1, 3, 9, Pro) > 5000)) && (cMap[1][2].chess == '0' || (cMap[1][2].chess == 'X' && Judge(1, 2, 9, Pro) > 5000)) && (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000)))
			k = 1;
	}
	else if (Pro[3][11] > 9000)
	{
		if (cMap[1][4].chess == '0' || (cMap[1][4].chess == 'X' && Judge(1, 4, 9, Pro) > 5000))
		{
			if (cMap[1][4].chess == '0' || (cMap[1][4].chess == 'X' && Judge(1, 4, 9, Pro) > 5000))
				k = 1;
			if (cMap[0][4].chess == '0' || (cMap[0][4].chess == 'X' && Judge(0, 4, 9, Pro) > 5000))
				k = 1;
		}
		if ((cMap[1][0].chess == '0' || (cMap[1][0].chess == 'X' && Judge(1, 0, 9, Pro) > 5000)) && (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000)) && (cMap[1][2].chess == '0' || (cMap[1][2].chess == 'X' && Judge(1, 2, 9, Pro) > 5000)) && (cMap[1][3].chess == '0' || (cMap[1][3].chess == 'X' && Judge(1, 3, 9, Pro) > 5000)))
			k = 1;
	}
	else
	{
		if (walei1(cMap, Pro) && walei3(cMap, Pro))
			k = 1;
		if ((cMap[1][4].chess == '0' || (cMap[1][4].chess == 'X' && Judge(1, 4, 9, Pro) > 5000)) && (cMap[1][3].chess == '0' || (cMap[1][3].chess == 'X' && Judge(1, 3, 9, Pro) > 5000)) && (cMap[1][2].chess == '0' || (cMap[1][2].chess == 'X' && Judge(1, 2, 9, Pro) > 5000)) && (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000)))
			k = 1;
		if ((cMap[1][0].chess == '0' || (cMap[1][0].chess == 'X' && Judge(1, 0, 9, Pro) > 5000)) && (cMap[1][1].chess == '0' || (cMap[1][1].chess == 'X' && Judge(1, 1, 9, Pro) > 5000)) && (cMap[1][2].chess == '0' || (cMap[1][2].chess == 'X' && Judge(1, 2, 9, Pro) > 5000)) && (cMap[1][3].chess == '0' || (cMap[1][3].chess == 'X' && Judge(1, 3, 9, Pro) > 5000)))
			k = 1;
	}

	return k;
}