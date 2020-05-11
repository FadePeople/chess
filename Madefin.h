#pragma once
int buzhen = 1;          //1 右司令   2 左司令
int huang1 = 0;
int huang2 = 0;
int huang3 = 0;
//int zz=0;
int qqqqqq = 0;         //调试时使用 ，在“1”中显示“第 n 步的开始”
int z1 = 0, z2 = 0, z3 = 0, z4 = 0;//判断己方棋子，是否为第一次进行营
int Ina_step[2] = { 2,0 };  ///第一位代表谁先碰子的,1为我先碰子的，2为敌方先碰子的。第二位表示未碰子次数。
int tra = 0;
int track[100];
int jq = 0;//表示对方司令死后裁判发给我方对方军棋位置信息，1代表第一次发送，非1代表不是第一次发送
int x11, y11, x21, y21;//记录敌方上一步的行旗
int dfs(int Pro[25][14], Map cMap[12][5], int deep, char *cInMessage);
int comm = 0;   //标记是否判断出敌方司令，若判断出大于0，否则等于0
int KIND = 9;	//有几种布局就写几
char cot[10];
int RandKind;		//随机生成决定用哪种布阵
pair<int, int>bm[10];
char buzhenout[][27] = {
	"cehiakbcdikegfgjjdifhhglj",
	"bdagckikfigdhgeijcjjfhhle",
	"bhggckkfcdiiefejadjijlhhg",
	"cgeibkicefikggadjjfdjlhhh",
	"cgeibkicefikggadjjfdjlhhh",
  	"chbihggkdeedcfkgiijafhjlj",
  	"dgeibkgcffekgiadjjicjlhhh",
  	"cggiadfekbckegfhdiihjljhj",
  	"cihhbkgkdficgfdaiejeghjlj"
};
Map Empty;
