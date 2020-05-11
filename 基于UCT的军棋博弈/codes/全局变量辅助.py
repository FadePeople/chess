import  logging
logging.basicConfig(level=logging.INFO)


global var 

var = {} #储存全部全局的变量

def val(name,value = 'no1215_'):#得到值 & 赋值
    if value != 'no1215_':
        var[name] = value
    try:
        return var[name]
    except:
        return None

def log(name):                   #log全局变量
    try:
        print('log{'+name+':'+str(var[name])+'}')
    except:
        print('log{'+name+':None}')