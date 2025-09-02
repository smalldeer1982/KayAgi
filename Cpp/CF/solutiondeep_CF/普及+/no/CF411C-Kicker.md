# 题目信息

# Kicker

## 题目描述

Kicker (table football) is a board game based on football, in which players control the footballers' figures mounted on rods by using bars to get the ball into the opponent's goal. When playing two on two, one player of each team controls the goalkeeper and the full-backs (plays defence), the other player controls the half-backs and forwards (plays attack).

Two teams of company Q decided to battle each other. Let's enumerate players from both teams by integers from $ 1 $ to $ 4 $ . The first and second player play in the first team, the third and the fourth one play in the second team. For each of the four players we know their game skills in defence and attack. The defence skill of the $ i $ -th player is $ a_{i} $ , the attack skill is $ b_{i} $ .

Before the game, the teams determine how they will play. First the players of the first team decide who will play in the attack, and who will play in the defence. Then the second team players do the same, based on the choice of their opponents.

We will define a team's defence as the defence skill of player of the team who plays defence. Similarly, a team's attack is the attack skill of the player of the team who plays attack. We assume that one team is guaranteed to beat the other one, if its defence is strictly greater than the opponent's attack and its attack is strictly greater than the opponent's defence.

The teams of company Q know each other's strengths and therefore arrange their teams optimally. Identify the team that is guaranteed to win (if both teams act optimally) or tell that there is no such team.

## 说明/提示

Let consider the first test sample. The first team can definitely win if it will choose the following arrangement: the first player plays attack, the second player plays defence.

Consider the second sample. The order of the choosing roles for players makes sense in this sample. As the members of the first team choose first, the members of the second team can beat them (because they know the exact defence value and attack value of the first team).

## 样例 #1

### 输入

```
1 100
100 1
99 99
99 99
```

### 输出

```
Team 1
```

## 样例 #2

### 输入

```
1 1
2 2
3 3
2 2
```

### 输出

```
Team 2
```

## 样例 #3

### 输入

```
3 3
2 2
1 1
2 2
```

### 输出

```
Draw
```

# AI分析结果

### 题目内容
#### Kicker
1. **题目描述**：桌上足球（Kicker）是一种以足球为基础的棋盘游戏，玩家通过操纵杆控制安装在杆上的足球运动员模型，将球踢进对方球门。在双打比赛中，每队的一名球员控制守门员和后卫（负责防守），另一名球员控制中场和前锋（负责进攻）。

公司Q的两个团队决定相互较量。让我们将两队的球员从1到4编号。第1和第2名球员在第一队，第3和第4名球员在第二队。对于这四名球员，我们都知道他们在防守和进攻方面的游戏技能。第i名球员的防守技能为$a_{i}$，进攻技能为$b_{i}$。

在比赛前，两队决定比赛方式。首先，第一队的球员决定谁将进攻，谁将防守。然后，第二队的球员根据对手的选择做出同样的决定。

我们将一个队的防守定义为该队负责防守的球员的防守技能。同样，一个队的进攻定义为该队负责进攻的球员的进攻技能。我们假设，如果一个队的防守严格大于对手的进攻，且其进攻严格大于对手的防守，那么这个队必定能击败对手。

公司Q的团队了解彼此的实力，因此会以最优方式安排他们的队伍。确定必定会获胜的队伍（如果两队都以最优方式行动），或者说明不存在这样的队伍。
2. **说明/提示**：考虑第一个测试用例。如果第一队选择如下安排：第一名球员进攻，第二名球员防守，那么第一队肯定能赢。

考虑第二个测试用例。在这个用例中，球员选择角色的顺序是有意义的。由于第一队的成员先选择，第二队的成员可以击败他们（因为他们知道第一队确切的防守值和进攻值）。
3. **样例 #1**
    - **输入**：
```
1 100
100 1
99 99
99 99
```
    - **输出**：
```
Team 1
```
4. **样例 #2**
    - **输入**：
```
1 1
2 2
3 3
2 2
```
    - **输出**：
```
Team 2
```
5. **样例 #3**
    - **输入**：
```
3 3
2 2
1 1
2 2
```
    - **输出**：
```
Draw
```

### 算法分类
无算法分类

### 题解综合分析与结论
所有题解的核心思路均是通过分析两队球员攻防能力的大小关系来判断哪队必胜或是否平局。要点在于明确一队获胜需满足一人攻击值大于对方两人防守值，且另一人防守值大于对方两人攻击值，对于第二队还需考虑针对第一队不同选择的应对策略。各题解的难点主要在于准确梳理和表达两队获胜的条件逻辑。不同题解在代码实现上，有的直接判断，有的使用函数封装部分逻辑，整体思路差异不大。

### 通用建议与扩展思路
通用建议：在处理此类逻辑判断问题时，要清晰梳理各种条件关系，可通过画图或列举简单例子辅助理解。代码实现上，注意逻辑的准确性和代码的可读性，可适当添加注释。
扩展思路：同类型题可涉及更多人数或更复杂的比赛规则，例如增加队伍数量、改变获胜条件等。类似算法套路是对于这种双方对抗且有固定规则判断胜负的问题，关键在于分析双方各种策略下的结果，通过比较条件来确定最终答案。

### 相似知识点洛谷题目
1. [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析每天的活动安排对心情值的影响，判断哪一天最不高兴，与本题类似之处在于都是通过分析条件得出结论。
2. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和所需铅笔数量，选择最省钱的购买方案，同样是在多种选择下通过比较条件得出最优解。
3. [P5717 闰年判断](https://www.luogu.com.cn/problem/P5717)：依据闰年的判断规则，对输入年份进行判断，和本题一样是基于特定规则进行逻辑判断。 

---
处理用时：38.98秒