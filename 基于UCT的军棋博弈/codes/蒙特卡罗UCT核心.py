from 全局变量辅助 import *
from 变量 import *
from random import *
from Queue import *
import math
import numpy as np
import logging
logging.basicConfig(level=logging.INFO)

def 蒙特卡罗抛针(剩余可分配棋子,棋子概率分布):
    while True:
        随机数 = randint(0,10000)
        底线 = 0
        for 棋种概率 in 棋子概率分布:
            if 棋种概率 !=0:
                上线 = 底线+棋种概率
                if 底线<随机数<=上线:
                    return 棋种概率
                else:
                    底线 = 上线


棋种灵活度 = {
    '司令':2.0,
    '军长':1.8,
    '师长':1.6,
    '旅长':1.4,
    '团长':1.2,
    '营长':1.0,
    '连长':0.8,
    '排长':0.6,
    '工兵':0.4,
    '地雷':0,
    '炸弹':0.2,
    '军旗':0
}

棋种价值分 = {
    '司令':500,
    '军长':400,
    '师长':320,
    '旅长':256,
    '团长':204,
    '营长':163,
    '连长':131,
    '排长':104,
    '工兵':163,
    '地雷':200,
    '炸弹':320,
    '军旗':1000
}

棋种可吃表 = {
    '司令':{'军长','师长','旅长','团长','营长','连长','排长','工兵','军旗'},
    '军长':{'师长','旅长','团长','营长','连长','排长','工兵','军旗'},
    '师长':{'旅长','团长','营长','连长','排长','工兵','军旗'},
    '旅长':{'团长','营长','连长','排长','工兵','军旗'},
    '团长':{'营长','连长','排长','工兵','军旗'},
    '营长':{'连长','排长','工兵','军旗'},
    '连长':{'排长','工兵','军旗'},
    '排长':{'工兵','军旗'},
    '工兵':{'地雷','军旗'},
    '地雷':{'司令','军长','师长','旅长','团长','营长','连长','排长'},
    '炸弹':{'军旗'},
    '军旗':{}
}

#接下来的内容极度复杂，中文写可能会糊成一滩人教版语文教材，所以此处采用英文码字
#目前UCT算法还在研究阶段，详细注释将在未来完成
#当前这个板子还不能跑，细节还未完善
#板子构造参考自github：Uct、Tic-Tac-Toe、Gomoku
#由于这部分还处于写着试一试的阶段，开发文档目前没有更新这部分，（未来补）

#当前局势类
#   目前局势类是为了能尽快测试上UCT构建的
#   在之后局势类调用的参数可以再优化，减少复杂度
class Board(object):
    def __init__(self,棋局,敌方棋子集合,己方棋子集合,敌方军旗位置,parent=None, prior=0):#这里的棋局为提取出的完备棋局，这里的棋子集合均为存活棋子
        #game_state
        self.states = 棋局 
        self.enemyunits = 敌方棋子集合
        self.myunits = 己方棋子集合
        self.enemyflagpst = 敌方军旗位置
        
        #node
        self.is_expanded = False
        self.parent = parent  # Optional[UCTNode]
        self.children = {}  # Dict[move, UCTNode]
        self.prior = prior  # float
        self.total_value = 0  # float
        self.number_visits = 0  # int
        self.depth = 0
        if parent!=None:
            self.depth = parent.depth+1

    def Q(self):  # returns float
         return self.total_value / (1 + self.number_visits)

    def U(self):  # returns float
        return (math.sqrt(self.parent.number_visits)*self.prior / (1 + self.number_visits))
    
    def best_child(self):
        return max(self.children.values(),key=lambda node: node.Q() + node.U())

    def select_leaf(self):
        current = self
        while current.is_expanded:
             current = current.best_child()
        return current

    def expand(self, child_priors):
        self.is_expanded = True
        for move, prior in enumerate(child_priors):
            self.add_child(move, prior)

    def add_child(self, move, prior):
        起点 = [ord(move[0])-65,move[1]]
        终点 = [ord(move[2])-65,move[3]]
        newstates = self.states
        newenemyunits = self.enemyunits
        newmyunits = self.myunits

        if self.states[终点[0]][终点[1]] == -1:#移动
            newstates[终点[0]][终点[1]] = newstates[起点[0]][起点[1]]
            newstates[起点[0]][起点[1]] = -1

        else:
            goID = self.states[终点[0]][终点[1]]
            chessID = self.states[起点[0]][起点[1]]
            gokind = self.enemyunits[goID]
            if chessID == gokind:           #移动子和目标子对死
                newstates[终点[0]][终点[1]] = -1
                newstates[起点[0]][起点[1]] = -1
            elif goID in 棋种可吃表[chessID]:#移动子将目标子吃掉
                newstates[终点[0]][终点[1]] = chessID
                newstates[起点[0]][起点[1]] = -1
            elif chessID in 棋种可吃表[goID]:#移动子被目标子吃掉
                newstates[起点[0]][起点[1]] = -1
                

        self.children[move] = Board(newstates, newenemyunits, newmyunits, self.enemyflagpst, parent=self, prior=prior)

    def backup(self, value_estimate: float):
        current = self
        while current.parent is not None:
            current.number_visits += 1
            current.total_value += (value_estimate * (self.depth&1))#有待争议
            current = current.parent

class NeuralNet():#对局势进行平分
    @classmethod
    def evaluate(self,棋局,敌方棋子集合,己方棋子集合,敌方军旗位置):
        return np.random.random([362]), np.random.random()#待删除
        #未完善功能：
        #   根据当前的局势的要素：存活棋子，棋局占位等因素对局势打分
        #   返回child_priors与value_estimate
        #   等再参考一些资料再对这部分模块进行完善
        #？？？


#未测试功能：UCT搜索
#   由于上面的局势打分未完成，整体的UCT搜索目前还未测试在比赛中可支持的最大的搜索深度
def UCT_search(棋局,敌方棋子集合,己方棋子集合,敌方军旗位置,num_reads):
    root = Board(棋局,敌方棋子集合,己方棋子集合,敌方军旗位置)
    for _ in (num_reads):
        leaf = root.select_leaf()
        child_priors, value_estimate = NeuralNet.evaluate(棋局,敌方棋子集合,己方棋子集合,敌方军旗位置)
        leaf.expand(child_priors)
        leaf.backup(value_estimate)
    # 总感觉这里缺少点什么
    # 等上面全完事了再写吧  

    
    


