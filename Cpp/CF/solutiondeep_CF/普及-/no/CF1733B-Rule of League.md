# 题目信息

# Rule of League

## 题目描述

There is a badminton championship in which $ n $ players take part. The players are numbered from $ 1 $ to $ n $ .

The championship proceeds as follows: player $ 1 $ and player $ 2 $ play a game, then the winner and player $ 3 $ play a game, and then the winner and player $ 4 $ play a game, and so on. So, $ n-1 $ games are played, and the winner of the last game becomes the champion. There are no draws in the games.

You want to find out the result of championship. Currently, you only know the following information:

- Each player has either won $ x $ games or $ y $ games in the championship.

Given $ n $ , $ x $ , and $ y $ , find out if there is a result that matches this information.

## 说明/提示

In the first test case, player $ 1 $ and player $ 4 $ won $ x $ times, player $ 2 $ and player $ 3 $ won $ y $ times.

In the second, third, and fifth test cases, no valid result exists.

## 样例 #1

### 输入

```
5
5 2 0
8 1 2
3 0 0
2 0 1
6 3 0```

### 输出

```
1 1 4 4
-1
-1
2 
-1```

# AI分析结果

### 题目内容
# 联赛规则

## 题目描述
有一场羽毛球锦标赛，$n$ 名选手参赛。选手编号从 $1$ 到 $n$。
锦标赛流程如下：选手 $1$ 和选手 $2$ 进行一场比赛，然后胜者与选手 $3$ 进行一场比赛，接着胜者再与选手 $4$ 进行一场比赛，依此类推。所以，总共进行 $n - 1$ 场比赛，最后一场比赛的胜者成为冠军。比赛无平局。
你想知道锦标赛的结果。目前，你仅知道以下信息：
- 每位选手在锦标赛中要么赢了 $x$ 场比赛，要么赢了 $y$ 场比赛。
给定 $n$、$x$ 和 $y$，判断是否存在符合此信息的比赛结果。

## 说明/提示
在第一个测试用例中，选手 $1$ 和选手 $4$ 赢了 $x$ 次，选手 $2$ 和选手 $3$ 赢了 $y$ 次。
在第二、第三和第五个测试用例中，不存在有效的结果。

## 样例 #1
### 输入
```
5
5 2 0
8 1 2
3 0 0
2 0 1
6 3 0
```
### 输出
```
1 1 4 4
-1
-1
2 
-1
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先判断无解的情况，再进行有解时的结果构造。
1. **无解判断**：
    - 因为每场比赛必有胜负，所以第一轮比赛两人中必有一人赢 $0$ 场，即 $\min(x,y)=0$，若 $\min(x,y)\neq0$ 则无解。
    - 又因为比赛必有胜者，所以不可能 $x = 0$ 且 $y = 0$，即 $\max(x,y)>0$，若 $\max(x,y)=0$ 则无解。
    - 设获胜人数为 $a$，由于获胜者每人赢 $\max(x,y)$ 场，共进行 $n - 1$ 场比赛，所以 $a\times\max(x,y)=n - 1$，若 $(n - 1)\bmod\max(x,y)\neq0$ 则无解。
2. **有解构造**：
    - 假设 $2$ 号选手为第一轮胜者，其连续赢 $\max(x,y)$ 场，之后下一个胜者为 $\max(x,y)+2$ 号选手，依此规律循环直至 $n$ 号选手，通过双重循环输出结果。

### 所选的题解
- **作者：ImNot6Dora (赞：4)  星级：4星**
    - **关键亮点**：思路清晰，先明确阐述无解的条件，再详细说明输出结果的构造依据，代码简洁明了。
    - **重点代码**：
```cpp
if(maxx>0&&0==(n-1)%maxx&&minn==0){
    for(int i=2;i<=n;i+=maxx){
        for(int j=1;j<=maxx;j++)cout<<i<<' ';
    }
    cout<<endl;
}else cout<<-1<<endl;
```
核心实现思想：先判断满足有解的条件，然后通过外层循环枚举获胜选手，内层循环控制每个获胜选手连续获胜的场次并输出。
- **作者：yanhao40340 (赞：3)  星级：4星**
    - **关键亮点**：对题意的阐述详细，无解条件和构造过程的分析逻辑连贯，代码核心部分展示清晰。
    - **重点代码**：
```cpp
if (min(x,y)!=0||max(x,y)==0){puts("-1");return;}//条件1和条件2
if ((n-1)%max(x,y)){puts("-1");return;}//条件3
for (int i=2;i<=n;i+=max(x,y))
    for (int j=1;j<=max(x,y);++j) printf("%d ",i);
putchar('\n');
```
核心实现思想：先判断无解条件，若有解则通过循环按规律输出获胜选手编号。

### 最优关键思路或技巧
1. **数学分析**：通过对比赛场次和胜负关系的数学分析，得出无解的条件以及有解时获胜选手的分布规律。
2. **代码实现技巧**：利用双重循环，外层循环控制获胜选手的切换，内层循环控制每个选手连续获胜的场次，简洁地构造出比赛结果。

### 拓展思路
同类型题通常围绕比赛场次、选手胜负关系以及特定条件下的结果判断或构造。类似算法套路是先根据比赛规则进行数学分析，找出关键的限制条件用于判断无解情况，再基于规则和条件构造有解时的结果。

### 洛谷相似题目推荐
1. **P1028 [NOIP2001 普及组] 数的计算**：通过对数字计算规则的分析，利用递推思想解决问题，与本题分析比赛规则找规律类似。
2. **P1226 【模板】快速幂||取余运算**：需要对幂运算和取余规则进行数学分析，与本题通过数学分析得出条件的思路相似。
3. **P1962 斐波那契数列**：根据数列规则进行数学推导和代码实现，和本题分析比赛规则并构造结果的方式类似。 

---
处理用时：38.27秒