from 全局变量辅助 import *
from 概率表刷新 import *
from 蒙特卡罗UCT核心 import *、
from 变量 import *
import  logging
logging.basicConfig(level=logging.INFO)

def 信息处理INFO():     #读取INFO信息内容，修改协议版本并输出队伍名称
    输入消息 = val('输入消息')
    队伍名称 = val('队伍名称')

    协议版本 = 输入消息[1]

    val('协议版本',协议版本)
    val('输出消息',队伍名称)

def 反馈布局START():
    输入消息 = val('输入消息')
    棋盘 = val('棋盘')
    棋子编码转化表 = val('棋子编码转化表')
    
    先手 = '' 
    布局 = []

    if 输入消息[1] == '0':
        先手 = '己方'
    elif 输入消息[1] == '1':
        先手 = '敌方'

    行棋限制时间 = 输入消息[2]
    非进攻步限制 = 输入消息[3]

    if 先手 == '己方':
        布局 = val('布局一号')
    elif 先手 == '敌方':
        布局 = val('布局一号')

    棋盘.初始化(布局)
    概率表初始化()
    输出消息 = 'ARRAY '
    for line in 布局:
        for chessID in line:
            if chessID != -1:
                输出消息+=棋子编码转化表[chessID]
    
    val('输出消息',输出消息)
    val('先手',先手)
    val('行棋限制时间',行棋限制时间)
    val('非进攻步限制',非进攻步限制)
    val('棋盘',棋盘)

def 信息处理GO指令():   #处理对手行棋
    输入消息 = val('输入消息')
    棋盘 = val('棋盘')
    敌方军旗位置 = val('敌方军旗位置')
    敌方司令编号 = val('敌方司令编号')

    move = 输入消息[1]
    result = 输入消息[2]
    res = ['吃掉','被吃','对死','移动']
    flag = 输入消息[3]
    if move == '0000': #通知先手先行不作为
        pass
    else:
        起点 = [ord(move[0])-65,int(move[1])]
        终点 = [ord(move[2])-65,int(move[3])]
        结果 = res[int(result)]
        if 敌方军旗位置=='未知' and flag !='00':#第一次得知对面军旗位置&对面司令已经暴毙
            敌方司令ID =  棋盘.棋局[起点[0]][起点[1]]#起点棋子为司令
            改变概率表(敌方司令ID,'司令',10000)
            敌方司令编号 = 敌方司令ID
            敌方军旗位置 = [ord(flag[0])-65,int(flag[1])]
            敌方军旗ID = 棋盘.棋局[ord(flag[0])-65][int(flag[1])]
            改变概率表(敌方军旗ID,'军旗',10000)
            val('敌方军旗位置',敌方军旗位置)
            val('敌方司令编号',敌方司令编号)
        棋盘.移动棋子(起点,终点,结果)
        val('棋盘',棋盘)

def 信息处理RESULT指令():#处理己方行棋结果
    输入消息 = val('输入消息')
    棋盘 = val('棋盘')
    输出消息 = val('输出消息') #获取刚刚走的那一步
    敌方军旗位置 = val('敌方军旗位置')
    敌方司令编号 = val('敌方司令编号')

    result = 输入消息[1]
    res = ['吃掉','被吃','对死','移动']
    flag = 输入消息[2]
    move = 输出消息.split()[1]

    起点 = [ord(move[0])-65,int(move[1])] 
    终点 = [ord(move[2])-65,int(move[3])]
    结果 = res[int(result)]
    if 敌方军旗位置=='未知' and flag !='00':#第一次得知对面军旗位置&对面司令已经暴毙
        敌方司令ID =  棋盘.棋局[终点[0]][终点[1]]#终点棋子为司令
        敌方司令编号 = 敌方司令ID
        改变概率表(敌方司令ID,'司令',10000)
        敌方军旗位置 = [ord(flag[0])-65,int(flag[1])]
        敌方军旗ID = 棋盘.棋局[ord(flag[0])-65][int(flag[1])]
        改变概率表(敌方军旗ID,'军旗',10000)
        val('敌方军旗位置',敌方军旗位置)
        val('敌方司令编号',敌方司令编号)
    棋盘.移动棋子(起点,终点,结果)
    val('棋盘',棋盘)


def 行棋函数驱动():
    输入消息 = val('输入消息')
    棋盘 = val('棋盘')
    输出消息 = val('输出消息')
    敌方军旗位置 = val('敌方军旗位置')
    敌方司令编号 = val('敌方司令编号')
    棋种可吃表 = val('棋种可吃表')
    棋种被吃表 = val('棋种被吃表')
    棋种最大数目表 = val('棋种最大数目表')
    敌方棋子集合 = val('敌方棋子集合')
    棋种概率表 = val('棋种概率表')
    己方棋子集合 = val('己方棋子集合')

    
    敌方存活棋子 = {}
    i = 0
    for line in 棋盘.棋局:
        j = 0
        for chessID in line:
            if not 是己方棋子(chessID):
                敌方存活棋子[chessID].位置 = [i,j]
            else:
                己方棋子集合[chessID].位置 = [i,j]


    剩余可分配棋子 = 棋种最大数目表
    #将已经确定的棋子标记上
    for chessID in 敌方棋子集合:
        if 敌方棋子集合[chessID].是啥 != '未知':
            剩余可分配棋子[敌方棋子集合[chessID].是啥]-=1
    
    #反复抛针
    wmove = {}#储存行走
    for i in range(10):#10次
        虚拟敌方棋子集合 = 敌方棋子集合#用于抛针
        for chessID in 虚拟敌方棋子集合:#抛针
            if 敌方棋子集合[chessID].是啥 != '未知': 
                虚拟敌方棋子集合[chessID].是啥 = 蒙特卡罗抛针(剩余可分配棋子,虚拟敌方棋子集合[chessID].概率)
                剩余可分配棋子[虚拟敌方棋子集合[chessID].是啥]-=1
            if chessID in 敌方存活棋子:
                敌方存活棋子[chessID].是啥 = 虚拟敌方棋子集合[chessID].是啥
        
        move = UCT_search(棋盘.棋局,敌方棋子集合,己方棋子集合,敌方军旗位置)
        if not move in wmove:
            wmove[move] = 0
        else:        
            wmove[move]+=1

        #目前拥有一个完备信息棋盘
        #信心上限树搜索 
        #每一个节点都是一副完备信息棋盘                
        #根节点为原始棋盘                
        #子节点展开为当前棋盘一步之内可以达到的棋盘                
        #对达到的棋盘状态进行评分                          


        