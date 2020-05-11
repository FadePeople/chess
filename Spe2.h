#pragma once

//"bhagckikfigdhgeijcjefhdlj"
#define STANDARD 3000	//概率表判断基准

//如果倒数第两排都没动，不去撞
//1为不能去撞 0为动了，可以赌
int Lizhi(Map cMap[12][5]) {
	if (!IsOppChess(cMap, 1, 0)) return 0;
	if (!IsOppChess(cMap, 1, 1)) return 0;
	if (!IsOppChess(cMap, 1, 2)) return 0;
	if (!IsOppChess(cMap, 1, 3)) return 0;
	if (!IsOppChess(cMap, 1, 4)) return 0;
	return 1;
}


//1 打左 0 打右
int JinGongFangXiang(Map cMap[12][5], int Pro[25][14]) {
	if (Judge(0, 1, 11, Pro) >= STANDARD && Judge(0, 3, 11, Pro) == 0) return 1;
	if (Judge(0, 1, 11, Pro) == 0 && Judge(0, 3, 11, Pro) >= STANDARD) return 0;
}

//查询某点处棋子能否接敌
//0为不能摸到
//1为对面大概率能吃自己
//2为对面大概率能对子
//3位对面大概率能被己方吃。
//4为有棋子能摸到查询位置，不能确定大小关系
// i，j为查询坐标， mine为己方棋子
//概率表判断准则为3000，前期可能用不了。
//目测没什么毛病了，待测试
int CanOppget(char mine, int i, int j, Map cMap[12][5], int Pro[25][14]) {
	int way_8[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1},			//行营八个角
					   {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
	int way_4[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };			//内部兵站四个角，左三个：上左右， 右三个：下左右。
	int kase = 0;													//判断查询地址的位置分类
	if (i == 0 || i == 11) kase = 3;								//最上一排/最下一排
	else if (IsRailway(i, j)) kase = 2;								//铁道
	else if (IsMoveCamp(i, j)) kase = 1;							//行营
	else kase = 4;													//其他位置（正常兵站）
	int oppBig = 0, oppSmall = 0, oppEqual = 0;						//全局赋值

	int flag_0 = 1;													//是否有棋子能触碰到查询位置的flag，与return 4区分。

	if (kase == 1) {												//行营
		if (!IsFilledCamp(cMap, i, j)) {								//若查询坐标是已占位行营（可能没什么用）
			return 0;

		}
		else {
			for (int k = 0; k < 8; k++) {							//行营八个方向
				for (int t = 0; t <= 8; t++) {						//司令，军长……工兵一共 八个棋子，未判断炸弹地雷，未判断炸弹地雷，未判断炸弹地雷。
					if (Judge(i + way_8[k][0], j + way_8[k][1], t, Pro) >= STANDARD) {//ij加上八个方向坐标的到周围一圈的情况
						if ((mine - 'a') < t) oppSmall = 1;			//mine为查询的目标字母，mine-‘a’为查询棋子的编号 t为八个可能敌方棋子的编号
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
		}
	}
	else if (kase == 2) {											//铁路线上
		if (i == 1 || i == 5 || i == 6 || i == 11) {				//横排铁路
			int mark_left = 1, mark_right = 1;						//两侧的mark， 1代表还须继续扫，0代表不需要了
			for (int j_ = 1; mark_left + mark_right; j_++) {		//横排铁路查询目标位置两侧开始扫， 左mark和右mark同时为0时，跳出循环。
				int tj_left = j - j_, tj_right = j + j_;			//左右的tj坐标，扫（i， tj）
				//mark_left = 1, mark_right = 1;
				if (tj_left >= 0 && mark_left) {					//目标左翼 && 标记
					if (IsMyChess(cMap, i, tj_left)) mark_left = 0;	//如果扫到我方棋子，不需要继续扫了
					if (IsOppChess(cMap, i, tj_left)) {				//若扫到对面棋子，判断
						flag_0 = 0;									//标记设为0；
						for (int t = 0; t <= 8; t++) {				//8个子标号
							if (Judge(i, tj_left, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
						mark_left = 0;								//扫到对面了就可以停了。
					}
				}
				else if (tj_left < 0) mark_left = 0;				//左路没人，左扫停止。

				if (tj_right <= 4 && mark_right) {					//目标右翼
					if (IsMyChess(cMap, i, tj_right)) mark_right = 0;
					if (IsOppChess(cMap, i, tj_right)) {
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(i, tj_right, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
						mark_right = 0;
					}
				}
				else if (tj_right > 4) mark_right = 0;
			}
			if (i == 1) {							//内侧棋子,最上排铁道的下侧，对方前线内侧，我方前线内侧，我方最下排铁道上侧。中线的上侧子和两角的上侧子下文判断
				if (j == 2) {
					if (IsOppChess(cMap, 2, 2)) {	//1，2 判断2，2
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(2, 2, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j <= 2) {
					if (IsOppChess(cMap, 2, 1)) {	//左侧三个， 判断2，1（左行营）
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(2, 1, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j >= 2) {
					if (IsOppChess(cMap, 2, 3)) {	//右侧三个， 判断2，3（右行营）
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(2, 3, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
			if (i == 5) {
				if (j == 2) {
					if (IsOppChess(cMap, 4, 2)) {	//5，2判断4，2
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(4, 2, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j <= 2) {
					if (IsOppChess(cMap, 4, 1)) {	//左侧三个，判断4，1行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(4, 1, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j >= 2) {
					if (IsOppChess(cMap, 4, 3)) {	//右侧三个，判断4，3行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(4, 3, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
			if (i == 6) {
				if (j == 2) {
					if (IsOppChess(cMap, 7, 2)) {	//中线，判断下方7，2
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(7, 2, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j <= 2) {
					if (IsOppChess(cMap, 7, 1)) {	//左三，判断7，1行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(7, 1, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j >= 2) {
					if (IsOppChess(cMap, 7, 3)) {	//右三，判断7，3行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(7, 3, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
			if (i == 10) {
				if (j == 2) {
					if (IsOppChess(cMap, 9, 2)) {	//中线上方9，2
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(9, 2, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j <= 2) {
					if (IsOppChess(cMap, 9, 1)) {	//左三，判断9，1行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(9, 1, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				if (j >= 2) {
					if (IsOppChess(cMap, 9, 3)) {	//右三，判断9，3行营
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(9, 3, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
		}
		if (j == 0 || j == 4) {						//竖排铁路
			int mark_up = 1, mark_down = 1;
			for (int i_ = 1; mark_up + mark_down; i_++) {				//上mark和下mark加一块为0跳出
				int ti_up = i - i_, ti_down = i + i_;
				if (ti_up >= 1 && mark_up) {
					if (IsMyChess(cMap, ti_up, j)) mark_up = 0;
					if (IsOppChess(cMap, ti_up, j)) {
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(ti_up, j, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				else if (ti_up <= 0) mark_up = 0;

				if (ti_down <= 10 && mark_down) {
					if (IsMyChess(cMap, ti_down, j)) mark_down = 0;
					if (IsOppChess(cMap, ti_down, j)) {
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(ti_down, j, t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
				else if (ti_down >= 11) mark_down = 0;
			}
			//纵向铁路四角边缘。
			if (i == 1 && j == 0 && IsOppChess(cMap, 0, 0)) {//左上
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(0, 0, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			if (i == 10 && j == 0 && IsOppChess(cMap, 11, 0)) {//左下
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(11, 0, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			if (i == 1 && j == 4 && IsOppChess(cMap, 0, 4)) {	//右上
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(0, 4, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			if (i == 10 && j == 4 && IsOppChess(cMap, 11, 4)) {	//右下
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(11, 4, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			if (i >= 1 && i <= 3) {						//内侧
				if (j == 0 && IsOppChess(cMap, 2, 1)) {	//左侧铁路判断其右侧
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(2, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 2, 3)) {	//右侧铁路判断其左侧
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(2, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
			else if (i == 3) {
				if (j == 0 && IsOppChess(cMap, 3, 1)) {	//左侧铁路判断其右侧
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(3, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 3, 3)) {	//右侧铁道判断左侧
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(3, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
			else if (i >= 3 && i <= 5) {
				if (j == 0 && IsOppChess(cMap, 4, 1)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(4, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 4, 3)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(4, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
			else if (i >= 6 && i <= 8) {
				if (j == 0 && IsOppChess(cMap, 7, 1)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(7, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 7, 3)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(7, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
			else if (i == 8) {
				if (j == 0 && IsOppChess(cMap, 8, 1)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(8, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 8, 3)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(8, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
			else if (i >= 8 && i <= 10) {
				if (j == 0 && IsOppChess(cMap, 9, 1)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(9, 1, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
				if (j == 4 && IsOppChess(cMap, 9, 3)) {
					flag_0 = 0;
					for (int t = 0; t <= 8; t++) {
						if (Judge(9, 3, t, Pro) >= STANDARD) {
							if ((mine - 'a') < t) oppSmall = 1;
							if ((mine - 'a') == t) oppEqual = 1;
							if ((mine - 'a') > t) oppBig = 1;
						}
					}
				}
			}
		}
		if (j == 2) {//中线
			if (i == 1 && IsOppChess(cMap, 0, 2)) {
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(0, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (i == 5 && IsOppChess(cMap, 6, 2)) {
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(6, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (i == 6 && IsOppChess(cMap, 5, 2)) {
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(5, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (i == 10 && IsOppChess(cMap, 11, 2)) {
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(11, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
		}
	}
	else if (kase == 3) {//最上，最下
		if (i == 0) {		//最上排
			if (j == 0 && IsOppChess(cMap, 1, 0)) {		//左上角，只看自己下面
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(1, 0, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (j == 4 && IsOppChess(cMap, 1, 4)) {		//右上角，只看自己下面
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(1, 4, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (j == 1 || j == 3) {			//大本营，下左右三个方向
				for (int k = 1; k < 4; k++) {
					if (IsOppChess(cMap, i + way_4[k][0], j + way_4[k][1])) {
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(i + way_4[k][0], j + way_4[k][1], t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
			else if (j == 2 && IsOppChess(cMap, 1, 2)) {	//中线
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(1, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
		}
		else if (i == 11) {							//最下
			if (j == 0 && IsOppChess(cMap, 10, 0)) {	//左下角
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(10, 0, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (j == 4 && IsOppChess(cMap, 10, 4)) {	//右下角
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(10, 4, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
			else if (j == 1 || j == 3) {
				for (int k = 0; k < 3; k++) {			//大本营，上左右三个方向
					if (IsOppChess(cMap, i + way_4[k][0], j + way_4[k][1])) {
						flag_0 = 0;
						for (int t = 0; t <= 8; t++) {
							if (Judge(i + way_4[k][0], j + way_4[k][1], t, Pro) >= STANDARD) {
								if ((mine - 'a') < t) oppSmall = 1;
								if ((mine - 'a') == t) oppEqual = 1;
								if ((mine - 'a') > t) oppBig = 1;
							}
						}
					}
				}
			}
			else if (j == 2 && IsOppChess(cMap, 10, 2)) {	//中线
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(10, 2, t, Pro) >= STANDARD) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
		}
	}
	else if (kase == 4) {							//普通兵站
		for (int k = 0; k < 4; k++) {
			if (IsOppChess(cMap, i + way_4[k][0], j + way_4[k][1])) {
				flag_0 = 0;
				for (int t = 0; t <= 8; t++) {
					if (Judge(i + way_4[k][0], j + way_4[k][1], t, Pro) >= 3000) {
						if ((mine - 'a') < t) oppSmall = 1;
						if ((mine - 'a') == t) oppEqual = 1;
						if ((mine - 'a') > t) oppBig = 1;
					}
				}
			}
		}
	}

	if (oppBig) return 1;
	else if (oppEqual) return 2;
	else if (oppSmall) return 3;
	else if (flag_0) return 0;
	else return 4;				//有棋子摸到他，不能确定大小关系
}



//莽家
int JiangJun(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5]) {
	char ChessRank[25];
	mychessdx(cMap, ChessRank);
	int left = strlen(ChessRank);

	int score = 0;
	int way_8[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
					   {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
	int way_4[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

	if (cMap[i][j].chess == 'b' && i <= 5) score += 3000;
	if (cMap[i][j].chess == 'b' && i > 5) score -= 3000;

	if (cMap[i][j].chess == 'b') {//军长
		if (NumOppChess(cMap)>= 19 && i1 <= 1) score -= 20000;
		if (i <= 4) {
			//突进成功
			if (IsMoveCamp(i1, j1) && left >= 19) score += 3000;
			if (j1 >= 1) score += 300;
			else if (j1 >= 2) score += 400;
			else if (j1 >= 3) score += 500;//往右偏
			if (i <= 4 && i1 == 5 && j1 == 0) score -= 900;//不重新回到第一排吃炸弹
			if (IsMoveCamp(i, j) && i<= 5) {
				//突击到对面行营里，不动, 不往两侧车路走
				if ( NumOppChess(cMap)>= 20 && j1== 0) { score -= 7000; }
				if (IsMoveCamp(i1, j1)) score += 7000;
			}
			if (i == 4 && j == 1) {
				//突进到第一个营
				if (i1 == 3 && j1 == 2) score += 13200;//往里冲
				if (i1 == 5 && j1 == 2) score -= 13200;//不往后退
				return score;
			}
			//不能再冲了鸭
			if (i == 2 && NumOppChess(cMap) >= 20 && i1 == 1) {
				score -= (NumOppChess(cMap) * 1700);
			}
			if (i == 2 && j == 2 && NumOppChess(cMap)>= 19) {
				//如果突进到死地，退一步
				if (i1 == 1) { score = 0; score -= 50000; return score; }//不向前走
				if (i1 == 2 && j1 == 1) score += 3600;
				if (i1 == 2 && j1 == 3) score += 3600;
				if (i1 == 3 && j1 == 2) score += 3200;
			}
			if (i == 1 && NumOppChess(cMap) >= 18) {
				if (IsMoveCamp(i1, j1)) score += 30000;//回来,虽然一般回不来
			}
			if (i == 2 && IsMoveCamp(i, j)) {
				if (NumOppChess(cMap) >= 19) score -= 6000;//在营里不动
			}
		}
		if (i == 5 && j!= 0) {
			//横排突进 赌对面炸弹全在边路
			if (!IsOppChess(cMap, 4, 2)) {
				if (IsFilledCamp(cMap, 4, 1) && i1 == 5 && j1 == 1 && left >= 23) { score += 3200; return score; }
				if (IsFilledCamp(cMap, 4, 3) && i1 == 5 && j1 == 3 && left >= 23) { score += 3200; return score; }
			}
		}
		if (IsMoveCamp(i1, j1) && !IsFilledCamp(cMap, i1, j1)) {
			for (int i = 0; i < 8; i++) {
				int tx = i1 + way_8[i][0];
				int ty = j1 + way_8[i][1];
				if (tx < 0 || tx> 11 || ty < 0 || ty> 4) continue;
				if (Judge(tx, ty, 0, Pro) > STANDARD) score -= 5000;
				else if (Judge(tx, ty, 1, Pro) > 3000) {
					if (ChessRank[0] == 'a') score -= 1000;
					else score -= 5000;
				}
				else if (Judge(tx, ty, 10, Pro) > 3000) score -= 5000;
				else if (Judge(tx, ty, 9, Pro) > 3000) score -= 1000;
				else score += 2500;
			}
		}
		if (IsRailway(i1, j1)) {
			int situation = CanOppget('b', i1, j1, cMap, Pro);
			if (!situation) {							//不能摸到
				score += 2500;
			}
			if (situation == 1) {						//大概率被吃
				score -= 2000;
			}
			if (situation == 2) {						//对子
				int left = strlen(ChessRank);
				if (left <= 15) {
					score -= 1500;
				}
				else score += 500;
			}
			if (situation == 3) {						//无敌
				score += 7000;
			}
			if (situation == 4) {
				score += 6000;
			}
		}
		if (Pro[1][11] == 0 && j1 >= 2) score += 500;	//军旗
		else if (Pro[3][11] == 0 && j1 <= 2) score += 500;

		if (i1 <= 1) {
			int left = strlen(ChessRank);
			if (left > 13) score -= 1000;
		}
	}
	else if (cMap[i][j].chess != 'a') {//除司令外其他子莽。
		if (IsMoveCamp(i1, j1) && !IsFilledCamp(cMap, i1, j1)) {
			if (strlen(ChessRank) > 13) score += 1500;
			else score += 500;
		}
		if (IsRailway(i1, j1)) {
			int situation = CanOppget('b', i1, j1, cMap, Pro);
			if (!situation) {							//不能摸到
				score += 1500;
			}
			if (situation == 1) {						//大概率被吃
				score -= 1000;
			}
			if (situation == 2) {						//对子
				int left = strlen(ChessRank);
				if (left <= 15) {
					score -= 1000;
				}
				else score += 1000;
			}
			if (situation == 3) {						//无敌
				score += 2000;
			}
			if (situation == 4) {						//情况不明，出去浪。
				int left = strlen(ChessRank);
				if (left >= 20)score += 700;
				else if (left < 20 && left >= 15) score += 500;
				else score += 400;
			}
		}
	}

	if (i1 == 1 && Lizhi(cMap)) score = 0;
	return score;
}



int spe2(int i, int j, int i1, int j1, int Pro[25][14], Map cMap[12][5]) {
	int score = 0;
	char ChessRank[25];
	mychessdx(cMap, ChessRank);
	int left = strlen(ChessRank);//我方棋子数目

	//守家
	if (IsOppChess(cMap, 10, 3)) {
		if (i1 == 10 && j1 == 3) {
			score += 19000;
			if (left <= 10 && i1 == 10 && j1 == 3) score += (25 - NumOppChess(cMap)) * 1600;
		}
		if (score < 50000) score = 60000;
		return score;
	}
	else if (IsOppChess(cMap, 10, 2)) {
		if (i1 == 10 && j1 == 2) {
			score += 17000;
			if (left <= 10 && i1 == 10 && j1 == 2) score += (25 - NumOppChess(cMap)) * 1200;
		}
		if (score < 50000) score = 60000;
		return score;
	}
	else if (IsOppChess(cMap, 10, 4)) {
		if (i1 == 10 && j1 == 4) {
			score += 17000;
			if (left <= 10 && i1 == 10 && j1 == 4) score += (25 - NumOppChess(cMap)) * 1200;
		}
		if (score < 50000) score = 60000;
		return score;
	}

	//冲鸭
	if (cMap[i][j].chess == 'b' && (i1 == 5 && j1 == 0) && left >= 24 && IsOppChess(cMap, i1, j1)
		&& cMap[i][j].IsTouch== 0 && cMap[i][j].IsTouched== 0 && i== 6 && j== 0)
		return 50000;
	//继续冲鸭
	if (cMap[i][j].chess == 'b' && i == 4 && j == 1 && i1 == 3 && j1 == 2) return 50000;
	//还能再冲鸭！
	if (cMap[i][j].chess == 'b' && i == 3 && j == 2 && i1 == 2 && j1 == 1) return 51000;
	if (cMap[i][j].chess == 'b' && i == 3 && j == 2 && i1 == 2 && j1 == 2) return 50000;


	if (i1 == 11 && j1 == 1) score -= 10000;
	if (i1 == 11 && j1 == 3) score -= 10000;
	if (NumOppChess(cMap) >= 20) {
		if (i1 == 1) score -= 10000;
	}

	if (cMap[i][j].chess == 'b') {//军长更新v1.0 蠢得一匹的军长
		if (i == 2 && j == 1) {
			if (NumOppChess(cMap) >= 18) {
				score -= 2000;
				if (IsOppChess(cMap, 1, 1)) score -= 3000;
			}
		}
		if (i == 2 && j == 2) {//死地 //为啥就是傻冲前面....
			if (IsOppChess(cMap, 1, 2)) score -= 2000;
			if (i1 == 1) {
				if (j1 == 1) {
					score = 0;
					score -= 40000;
					if (IsOppChess(cMap, 1, 1) && cMap[1][1].IsTouch == 0) score -= 10000;
					if (Lizhi(cMap)) score -= 20000;
					return score;
				}
			}
			if (IsMoveCamp(i1, j1)) {
				if (NumOppChess(cMap) >= 19) score += 3000;
				score += (25 - NumOppChess(cMap)) * 1100;
				if (left > NumOppChess(cMap)) {
					//优势
					;
				}
			}
		}
		if (i == 2 && j == 1 ) {
			if (i1 == 2 && j1 == 2 && !IsFilledCamp(cMap, 3, 2)) {
				score += (left - NumOppChess(cMap)) * 900;
			}
			if (i1 == 2 && j1 == 2 && !IsFilledCamp(cMap, 2, 3)) {
				score += (left - NumOppChess(cMap)) * 910;
			}
		}
		if (i == 5 && j == 0 && NumOppChess(cMap)>= 20) {
			if (i1 == 4 && j1 == 1) {
				score += 50000;
				return score;
			}
			if (i1 == 5 && j1 == 1) {
				score += 50000;
				return score;
			}
		}
	}
	else {
		if (left >= 20) score += JiangJun(i, j, i1, j1, Pro, cMap);
		else if (left < 20 && left >= 15) score += JiangJun(i, j, i1, j1, Pro, cMap)* 0.8;
		else if (left < 15 && left >= 10) {
			if (ChessRank[0] <= 'e' && cMap[i][j].chess <= 'e') { //最大子比团长大于等于
				if (ChessRank[1] <= 'e' && i1 <= 5) {//有不止一个大子
					if (!CanOppget(cMap[i][j].chess, i1, j1, cMap, Pro)) {
						score += 1200;
					}
					if (CanOppget(cMap[i][j].chess, i1, j1, cMap, Pro) == 1) {
						score -= 900;
					}
					if (CanOppget(cMap[i][j].chess, i1, j1, cMap, Pro) == 2) {
						score -= 600;
					}
					if (CanOppget(cMap[i][j].chess, i1, j1, cMap, Pro) == 3) {
						score += 1000;
					}
				}
				else if (ChessRank[1] >= 'e' && i1 >= 5) {//只有一个大子
					if (cMap[11][1].chess == 'l') {//保护军棋
						int dan = CanOppget('l', 11, 1, cMap, Pro);
						if (!dan) {//没有子摸得到军棋
							if ((i1 <= 11 && i1 >= 9) || (j1 >= 0 && j1 <= 2)) score += 1300;
							if (cMap[i][j].chess >= 'e') score += 500;
							if (left <= 13) score += 700;
						}
						if (dan) {
							if ((i1 <= 11 && i1 >= 10) || (j1 >= 0 && j1 <= 2)) score += 1800;
							if (cMap[i][j].chess >= 'e') score += 1000;
						}
					}
					if (cMap[11][3].chess == 'l') {
						int dan = CanOppget('l', 11, 3, cMap, Pro);
						if (!dan) {//没有子摸得到军棋
							if ((i1 <= 11 && i1 >= 9) || (j1 >= 2 && j1 <= 4)) score += 1300;
							if (cMap[i][j].chess >= 'e') score += 500;
							if (left <= 13) score += 700;
						}
						if (dan) {
							if ((i1 <= 11 && i1 >= 10) || (j1 >= 0 && j1 <= 2)) score += 1800;
							if (cMap[i][j].chess >= 'e') score += 1000;
						}
					}
				}
			}
		}
	}

	//司令守中及相关
	if (cMap[i][j].chess == 'a') {
		if (i1 == 2 && j1 == 4) {
			score -= 3600;
			if (IsOppChess(cMap, 2, 4) && cMap[2][4].IsTouch== 0) score -= 10000;
		}
		if (left >= 22) {
			if (i == 6 && j == 2) score -= 50000;				//一开始守家
			if (cMap[i][j].IsTouch >= 3) {						//被打了几下就撤销死守的分准备跑路
				score += 50000;
				if (IsMoveCamp(i1, j1)) score += 1000;
			}
		}
		if (i <= 5 && IsMoveCamp(i1, j1)) score += 1100;			//到对面家营

		if (left <= 21) {										//跑路
			if (IsMoveCamp(i1, j1)) score += 1000;
			if (j1 <= 1) score += 600;							//哪边能跑往哪跑
			if (j1 >= 3) score += 600;
			if (i1 <= 7) score += 800;
			if (left >= 16 && IsMoveCamp(i1, j1)) score -= 1700;	//差不多这个时候炸弹死的差不多了，可以出去浪了
			if (Judge(i1, j1, 0, Pro) >= STANDARD)
				;
			else
				score += (25 - NumOppChess(cMap)) * 140;						//要是还有命就去冲锋

			if (i == 6 && j == 2 && left <= 18) score += 3200;	//无脑跑路
			if (IsOppChess(cMap, 5, 2) && NumOppChess(cMap) <= 19) {
				if (cMap[5][2].IsTouch == 0 && cMap[5][2].IsTouched == 0) {
					if (i1 == 5 && j1 == 2) score -= 50000;
					else score += 5000;

					if (j1 >= 2) score += 1700;
					else score == 1600;
				}
			}
		}


		if (i == 6 && j == 2 && Judge(5, 2, 1, Pro) >= STANDARD) {
			score += 5600;
			if (!IsFilledCamp(cMap, 4, 1) || !IsFilledCamp(cMap, 4, 3)) score += 1200;
		}

		if (NumOppChess(cMap) >= 13) {							//不随便冲家（雷）
			if (i1 <= 3) score -= 2000;
			if (IsMoveCamp(i1, j1)) score += 2000;
		}
		if (i1 <= 3 && cMap[i1][j1].IsTouched == 0) score -= 5000;//不冲未知的子（雷）

		if (left >= 19 && CanOppget('a', i1, j1, cMap, Pro) != 3) score -= 3000;

		if (IsMoveCamp(i, j) && i <= 5) {
			if (NumOppChess(cMap) >= 18) score -= 1300;
		}

		if (i == 6 && j == 4) {
			if (Judge(5, 4, 10, Pro) >= STANDARD) {
				if (i1 == 6 && j1 == 2) score += 5000;
			}
		}

		if (IsOppChess(cMap, i1, j1)) {
			if (Judge(i1, j1, 1, Pro) >= STANDARD) score += 3200;
		}
	}

	if (left >= 23 && i == 6 && j == 3) score += 600;			//防止赌司令路

	//确认过的军旗能不撞就不撞
	if (Judge(i1, j1, 'l', Pro) == 0) score -= 50000;

	//撞可能的炸弹
	if (cMap[6][2].chess == 'a' && IsOppChess(cMap, 5, 2) && cMap[i][j].chess!= 'a') score += 3600;

	//不随便趟地雷
	if (cMap[i][j].chess != 'i' ) {//非工兵
		if (i1 <= 1 && NumOppChess(cMap)>= 15)
			score -= ((25 - NumOppChess(cMap))* 1000);
		if (i1 == 1 && j1 == 4) score -= 7600;
		if (cMap[i1][j1].IsTouch == 0) score -= 3600;
	}

	//旅长
	if (cMap[i][j].chess == 'd') {
		if (i1 == 4 && j1 == 4 && IsOppChess(cMap, 4, 4) && left >= 20) score += 1250;
	}

	//劣势守家
	if (1) {
		if (cMap[i][j].chess == ChessRank[0]) {
			if (i != 9 && j != 3) {
				if (j1 >= 2) {
					score += j1 * 1500;
				}
				if (i >= 7) score += i1 * 500;
			}

		}

	}

	if (NumOppChess(cMap) >= 19) {
		if (i1 == 2) score -= 1700;
	}

	if (Judge(10, 4, 8, Pro) >= STANDARD || !IsMyChess(cMap, 10, 4)) {
		if (i == 9 && j == 3 && i1 == 10 && j1 == 4) score += 13000;
	}
	if (IsOppChess(cMap, 10, 3) && i1 == 10 && j1 == 3) score += 13000;
	if (!IsMyChess(cMap, 9, 4) && i1 == 9 && j1 == 4) score += 3600;
	if (!IsMyChess(cMap, 10, 3) && i1 == 10 && j1 == 3) score += 3600;

	//偷鸡摸狗脑残工兵
	if (NumOppChess(cMap) <= 16 && cMap[i][j].chess == 'i') {
		if (IsOppChess(cMap, i1, j1)) {//不瞎撞
			if (i <= 2 && cMap[i1][j1].IsTouch== 0) score += 1200;
			else score -= 2300;
		}
		if (i == 1 && j == 4 && Judge(0, 3, 11, Pro) != 0) {//偷右
			if (i1 == 0 && j1 == 4) {//赌下
				score += 2000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))//防换家
					score -= 2000;
			}
			if (Judge(1, 3, 9, Pro) >= STANDARD && CanOppget('i', 1, 3, cMap, Pro) == 0) {//横排
				score += 4000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 4000;
			}
		}
		if (i == 1 && j == 0 && Judge(0, 1, 11, Pro) != 0) {//偷左
			if (i1 == 0 && j1 == 0) {
				score += 2000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 2000;
			}
			if (Judge(1, 1, 9, Pro) >= STANDARD && CanOppget('i', 1, 1, cMap, Pro) == 0) {
				score += 4000;
				if (IsOppChess(cMap, 10, 2) || IsOppChess(cMap, 10, 3) || IsOppChess(cMap, 10, 4))
					score -= 4000;
			}
		}

		if (IsMoveCamp(i, j) && left <= 17) {
			if (i1 == 1 && j1 == 4) score += (800 + (25 - NumOppChess(cMap)) * 100);
			if (i1 == 1 && j1 == 0) score += (800 + (25 - NumOppChess(cMap)) * 100);
		}

		if (Judge(i1, j1, 10, Pro) >= (STANDARD-500)) score += 15000;
		if (left <= 15) {
			if (IsRailway(i1, j1))
				if (CanOppget('i', i1, j1, cMap, Pro) == 0) score += (25 - NumOppChess(cMap)) * 125;
		}


	}

	//不赌家里的营
	if (i == 8 && j == 2) {
		if (IsMyChess(cMap, 7, 1) || IsMyChess(cMap, 7, 3)) score += 3000;
		//if (i1 == 8 && j1 == 1) score += 2000;
	}

	//炸弹
	if (cMap[i][j].chess == 'k') {
		if (NumOppChess(cMap) >= 15) {//优势炸大子
			if (i1 <= 1) {
				if (Judge(i1, j1, 9, Pro) >= STANDARD) score -= 10000;
			}
			if (Judge(i1, j1, 0, Pro) <= STANDARD) {
				score -= 5000;
			}
			else score += (25 - NumOppChess(cMap)) * 450;
			if (Judge(i1, j1, 1, Pro) <= STANDARD) {
				score -= 4500;
			}
			else score += (25 - NumOppChess(cMap)) * 400;
			if (cMap[i][j].IsTouch == 0 && cMap[i][j].IsTouched == 0) score -= 5000;
		}

		//进营
		if (IsMoveCamp(i1, j1)) {
			if (i == 7 && j == 0 && i1== 7 && j1== 1) score += 9000;
			if (i == 7 && j == 4 && i1== 7 && j1== 3) score += 9000;
			if (!IsMoveCamp(i, j)) score += 1200;
		}
		if (IsMoveCamp(i1, j1) && left>= 20  && !IsMoveCamp(i, j)) {
			score += (25 - NumOppChess(cMap)) * 3000;
			if (Judge(i1, j1, 0, Pro) <= STANDARD) {
				score -= 5000;
			}
			else score += (25 - NumOppChess(cMap)) * 450;
			if (Judge(i1, j1, 1, Pro) <= STANDARD) {
				score -= 4500;
			}
			else score += (25 - NumOppChess(cMap)) * 400;
			if (cMap[i][j].IsTouch == 0 && cMap[i][j].IsTouched == 0) score -= 5000;
		}
		//进对面营
		if (i <= 5) {
			if (IsMoveCamp(i1, j1)) score += 1300;
			if (Judge(i1, j1, 0, Pro) <= STANDARD) {
				score -= 5000;
			}
			else score += (25 - NumOppChess(cMap)) * 450;
			if (Judge(i1, j1, 1, Pro) <= STANDARD) {
				score -= 4500;
			}
			else score += (25 - NumOppChess(cMap)) * 400;
			if (cMap[i][j].IsTouch == 0 && cMap[i][j].IsTouched == 0) score -= 5000;
		}
		if (i == 7 && j == 1 && i1 == 8 && j == 2) {
			score += 1200;
			score += (25 - left) * 175;
		}

		if (ChessRank[0] >= 'c') {
			if (Judge(i1, j1, 0, Pro) >= STANDARD ||
				Judge(i1, j1, 1, Pro) >= STANDARD ||
				Judge(i1, j1, 2, Pro) >= STANDARD) {
				score += (25 - NumOppChess(cMap)) * 130;
			}
		}

	}

	//残局进攻
	if (NumOppChess(cMap) <= 13) {
		if (cMap[i][j].chess != 'a') {
			//除了司令
			if (IsMoveCamp(i, j) && i == 4) {
				//下方行营
				if (i1 == 3 && j1 == 2) score += (25 - NumOppChess(cMap)) * 105;
				else if (i1 == 3)score += (25 - NumOppChess(cMap)) * 70;

				if (Judge(0, 1, 11, Pro) != 0) {
					if (i1 == 1 && j1 == 1) score += (25 - NumOppChess(cMap)) * 110;
				}
				if (Judge(0, 3, 11, Pro) != 0) {
					if (i1 == 1 && j1 == 3) score += (25 - NumOppChess(cMap)) * 110;
				}
			}

			if (left > NumOppChess(cMap)) {
				//优势
				if (cMap[i][j].chess == ChessRank[1]) {
					if (cMap[9][3].chess == ChessRank[0]) {
						if (i1 <= 5) {
							score += (5 - i1) * 600;
							score += (25 - NumOppChess(cMap)) * 110;
						}
					}
				}
			}
		}
		else {
			//仁义无双总司令
			if (Judge(0, 1, 11, Pro) != 0) {
				//旗子在左面
				if (j1<= 2) score+= (25 - NumOppChess(cMap)) * 110;
				if (i1<= 2) score+= (25 - NumOppChess(cMap)) * 100;

				if (Judge(i1, j1, 9, Pro) >= STANDARD) score -= 30000;
			}
			else {
				if (j1 >= 2) score += (25 - NumOppChess(cMap)) * 120;
				if (i1 <= 2) score += (25 - NumOppChess(cMap)) * 110;

				if (Judge(i1, j1, 9, Pro) >= STANDARD) score -= 30000;
			}
		}
	}


	return score;
}
