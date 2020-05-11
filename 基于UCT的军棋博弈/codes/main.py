from 全局变量辅助 import *
from 基础函数 import *
from 变量 import *
import  logging
logging.basicConfig(level=logging.INFO)

#参考原C++军旗代码，python3.7复刻框架
#概率表是完全复刻的，包括刷新机制和初始值与原来的一样
#框架绝大部分采用中文编程，方便快速入门与维护（未来将写成维护手册），整个程序就是大一个注释
#构建时间 19.7.24 -> ?
#最后维护 19.8.2

###本来除了行棋之外的东西在第2天结束的时候就写完了，项目迟迟没有发布一直拖到现在原因是：
# Upper Confidence Bound Apply to Tree 真难
# 本以为UCT和最大最小搜索差不多
# 在粗略看完wls给的论文后夸下海口，"看我在三天内让他跑起来”
# 没想到在后续的工作进程中遇到了巨大的坎坷
# 从0开始学习MCsl、UCB耗费了不少时间，（主要是因为一年多没学数学）
# 然后在开源社区找了大量的UCT板子
# 都是基于类围棋那种布子类的，局势比较单调
# 反复研读资料，终于，及众家之所长，造了一个板子出来，
# 虽然还不能跑，不过至少离成功又近了一步
# 假期还有其他项目要写，上面监督的比较紧，UCT的研究进度要暂停一段时间了


# 任何人可以随意修改框架(本体在github),希望有有志人士可以帮我提前完成他
# github的本体是实时同步更新，如果取得了较大的进展，会尽可能第一时间同步到coding上（如果有机会的话）
# 本项目基于GLWTPL许可证开源（https://github.com/me-shaon/GLWTPL）
# 项目本体于github私人仓库（https://github.com/DOEMsy/JunQi）,进不去因为没有开放

#编译: python 3.7
#编辑：vscode
#不是很推荐用vs2017/2019修改本项目，无厘头的报错
#本项目的全局变量采用全局dict,在引用的时候一定要相信自己的操作，不要盲目的相信IDE补全
#除行棋以外的功能均已测试过了，可以跑，而且跑下来的问题均已修复

#def main：
输入消息 = val('输入消息',input().split())
while 输入消息[0]!='END':
    if 输入消息[0] == 'INFO':
        信息处理INFO()
        print(val('输出消息'))
    elif 输入消息[0] == 'START':
        反馈布局START()
        print(val('输出消息'))
        #log######
        概率表log()
    elif 输入消息[0] == 'GO':
        信息处理GO指令()
        #行棋 ： 复刻当前棋局和概率表 ->>{ 抛针得到完备棋局 -> UTC算法得到最优解([起点,终点]) } -> 选择重复最多的最优解 
        行棋函数驱动()
        print(val('输出消息'))
        #log#####
        概率表log()
        val('棋盘').display()
    elif 输入消息[0] == 'RESULT':
        信息处理RESULT指令()
    elif 输入消息[0] == 'END':
        break
    else:
        break
    
    输入消息 = val('输入消息',input().split())

