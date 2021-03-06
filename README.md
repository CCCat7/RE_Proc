# RE_Proc  

## 目录结构：
### RE2NFAepsilon  
包含正则表达式的处理以及正则表达式到NFA-epsilon的转换  
### NFAepsilon2DFA  
包含NFA-epsilon到NFA以及NFA到DFA的转换  
### DFA2MINIDFA  
包含DFA到DFA-mini的转换  

## 部分算法说明：  
### 1 正则表达式到NFA-epsilon的转换  

中缀表达式到后缀表达式的转换方式  
从中缀式的左端开始逐个读取字符x，逐序进行如下步骤：  
①若x是操作数，则分析出完整的运算数，将x直接压入栈s2；  
②若x是运算符，则分情况讨论：  
a)若x是'('，则直接压入栈s1；  
b)若x是')'，则将距离栈s1栈顶的最近的'('之间的运算符，逐个出栈，依次压入栈s2，此时抛弃'(‘；  
c)若x是除'('和')'外的运算符，则再分如下情况讨论：  
i)若当前栈s1的栈顶元素为'('，则将x直接压入栈s1；  
　　ii)若当前栈s1的栈顶元素不为'('，则将x与栈s1的栈顶元素比较，若x的优先级大于栈s1栈顶运算符优先级，则将x直接压入栈s1。否者，将栈s1的栈顶运算符弹出，压入栈s2中，直到栈s1的栈顶运算符优先级别低于（不包括等于）x的优先级，或栈s2的栈顶运算符为'('，此时再则将x压入栈s1;  
③在进行完②后，检查栈s1是否为空，若不为空，则将栈中元素依次弹出并压入栈s2中（不包括'#'）；  

### 2 Thompson构造法:
Thompson构造法在计算机科学中是指一个能将正则表达式转化为一个与之等价的非确定有限状态自动机（NFA）的算法。算法得到的NFA可以在编程中用于匹配一个正则表达式，这也是正则表达式引擎实现的基本思路之一。

### 3 Subset construction算法
Subset construction算法概念:
让构造得到的DFA的每个状态对应NFA的一个状态集合。DFA在读入a1a2...ana1a2...an之后到达的状态应该对应于相应的NFA从开始状态出发，沿着以a1a2...ana1a2...an为边的路径能达到的状态的集合。

算法步骤
①根据NFA-ε 的txt文件中的起始状态q0，和状态转移函数，将q0和q0通过连续ε 所到达的所有节点构成一个新的状态A集合，将A加入NFA的状态集。
②将集合状态A中包含的所有节点，通过循环遍历符号集的各个符号生成相应的结果状态集合B',C',D'。
③将集合状态B',C',D'的各个状态进行连续的ε所到达的状态集合设置为B,C,D...，将B,C,D...状态 加入 NFA自动机的状态集。将A-->“符号”-->(B||C||D||...)加入状态转换函数。
④遍历A,B,C,D...状态集合，将包含q0的状态设置为起始状态，包含F的状态设置为F结束状态。

 
### 4 DFA到极小化DFA的转换

极小化DFA与Hopcroft算法

A) 何谓极小化DFA？
1）没有多余状态（死状态）
      多余状态：
          ①从这个状态没有通路到达终态；
          ②从开始状态出发，任何输入串也不能到达的状态。
2）没有两个状态是互相等价（不可区别）
      两个状态s和t等价的条件：
          ①兼容性（一致性）条件——同是终态或同是非终态
          ②传播性（蔓延性）条件——对于所有输入符号，状     态s和状态t必须转换到等价的状态里。

C) Hopcroft 算法流程：
①设有非极小化的DFA，M，将M的状态划分为两个集合N（非终态）、A（终态）
②依次考察每个集合，如果该DFA的符号集中有符号能使得该集合中的状态经过该符号后到达不同的集合，则将该集合依据到达的集合进行划分，重新进行考察，否则继续考察下个集合
③如果集合仍在变化，则重复步骤2，否则划分结束
④划分结束后，在每个集合中指定一个代表状态来指定集合中的其他状态，更新DFA，即得到极小化的DFA

