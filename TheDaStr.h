#pragma once				//上个头文件只编译一次
typedef struct Point
{
	int i = 0;
	int j = 0;
}Point;

typedef struct Step
{
	Point From;              //起点
	Point To;                //终点
	char chess;              //棋子种类
}Step;

//防止来回磨棋
class Grind
{
public:
	Step Steps[20];           //走法
	int Num = 0;              //走法数
	void Clear();
	void Pop(int move[4], char chess);
	int IsGrind(int move[4], char chess);

private:

};

//函数名称 压入
//函数作用 保存
//传入参数
//   move    走法
//   chess   当前棋种
//返回值  无
void Grind::Pop(int move[4], char chess)
{
	if (chess != M_BOOM)
	{
		Steps[Num].From.i = move[0];           //记录我方目前走法
		Steps[Num].From.j = move[1];
		Steps[Num].To.i = move[2];
		Steps[Num].To.j = move[3];
		Steps[Num].chess = chess;
		Num++;
	}
}

//函数名称 清空
//函数作用 清空
//传入参数
//   无
//返回值  无
void Grind::Clear()
{
	Num = 0;
}

//函数名称
//函数作用 判断是否在磨棋
//传入参数
//  move    接下来的移动方向
//  chess   当前将要移动的棋子
//返回值  1 确实在磨棋 2 没有在磨棋
int Grind::IsGrind(int move[4], char chess)
{
	if (Num > 5)                                                                     //有5个值以上的进行运算
	{
		int i;
		int n = 0;                                                                   //
		for (i = Num; i >= 2; i--)
		{
			if (Steps[i].From.i == Steps[i - 2].From.i&&                            //从后往前走   记录磨棋次数
				Steps[i].From.j == Steps[i - 2].From.j&&
				Steps[i].To.i == Steps[i - 2].To.i&&
				Steps[i].To.j == Steps[i - 2].To.j&&
				Steps[i].chess == Steps[i - 2].chess&&
				Steps[i].chess == chess)
			{
				n++;                                                               //记录磨棋次数 实际要加2
				continue;
			}
			else
				break;

		}
		if (n > 2)                                                                  //判断磨棋超过5次认为在磨棋
			if (Steps[Num].From.i == move[0] &&                                       //判断下一个点是否在循环
				Steps[Num].From.i == move[1] &&
				Steps[Num].To.i == move[2] &&
				Steps[Num].To.j == move[3])
				return 1;                                                           //是确实在循环
		return 0;                                                                   //没有循环的情况
	}
	return 0;                                                                       //有5个值以下的直接返回0
}

Grind NoGrind;
typedef struct Attribute              //属性值
{
	int IsFollowed = NOATTR;         //被跟踪  敌方属性或己方锁定对方的棋子在概率表的位置
	int IsTrace = NOATTR;            //跟踪    己方属性
	int Type = 0;                    //棋子种类
}Attribute;

typedef struct Map                   //地图
{
	char        chess = '0';         //棋子种类
	Attribute   Attr;                //属性
	int IsTouch = 0;                 //主动撞击次数
	int IsTouched = 0;               //被撞次数
}Map;
