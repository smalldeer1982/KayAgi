---
title: "猫粮规划"
layout: "post"
diff: 普及/提高-
pid: B3624
tag: ['深度优先搜索 DFS', '剪枝']
---
# 猫粮规划
## 题目描述

到中午了，机器猫要吃猫粮了。

机器猫掏出 $n$ 份食物，第 $i$ 份食物含有的能量为 $w[i]$。机器猫可以吃掉其中一些食物，获得这些食物的能量之和。

机器猫又不想变得太胖又不想变得太瘦，所以指定了一个目标区间 $[l, r]$。显然，可能有很多种选择食物的方式可以达成这个目标，因此机器猫想知道方案总数。


## 输入格式

第一行，三个正整数 $n, l, r$。

第二行，$n$ 个正整数，表示每一份食物含有的能量 $w[i]$。
## 输出格式

仅一行，一个整数，表示方案数。
## 样例

### 样例输入 #1
```
4 70 85
10 10 20 50

```
### 样例输出 #1
```
4
```
## 提示

#### 样例解释

所有方案如下：

选择食物 1, 2, 4，能量 10+10+50 = 70  
选择食物 1, 3, 4，能量 10+20+50 = 80  
选择食物 2, 3, 4，能量 10+20+50 = 80  
选择食物 3, 4，能量 50+20 = 70

共 4 种方案。

#### 数据规模与约定

对于 $50\%$ 的数据，满足 $n\leq 20$。

对于 $100\%$ 的数据，满足 $n\leq 40, 20\leq w[i] \leq 100, l\leq r \leq 300$。

提示：$w[i]$ 在范围内均匀随机生成。



---

---
title: "树的直径"
layout: "post"
diff: 普及/提高-
pid: B4016
tag: ['O2优化', '深度优先搜索 DFS', '树的直径']
---
# 树的直径
## 题目描述

给定一棵 $n$ 个结点的树，树没有边权。请求出树的直径是多少，即树上的最长路径长度是多少。
## 输入格式

第一行输入一个正整数 $n$，表示结点个数。

第二行开始，往下一共 $n-1$ 行，每一行两个正整数 $(u,v)$，表示一条边。
## 输出格式

输出一行，表示树的直径是多少。
## 样例

### 样例输入 #1
```
5
1 2
2 4
4 5
2 3
```
### 样例输出 #1
```
3
```
## 提示

数据保证，$1 \leq n \leq 10^5$。


---

---
title: "[BCSP-X 2024 12 月小学高年级组] 质数补全"
layout: "post"
diff: 普及/提高-
pid: B4158
tag: ['2024', '北京', '枚举', '深度优先搜索 DFS', '筛法', 'BCSP-X']
---
# [BCSP-X 2024 12 月小学高年级组] 质数补全
## 题目描述

Alice 在纸条上写了一个质数，第二天再看时发现有些地方污损看不清了。

- 在大于 $1$ 的自然数中，除了 $1$ 和它本身以外不再有其他因数的自然数称为质数

请你帮助 Alice 补全这个质数，若有多解输出数值最小的，若无解输出 $-1$。

例如纸条上的数字为 $\tt{1*}$（$\tt{*}$ 代表看不清的地方），那么这个质数有可能为 $11, 13, 17, 19$，其中最小的为 $11$。
## 输入格式

第一行 $1$ 个整数 $t$，代表有 $t$ 组数据。

接下来 $t$ 行，每行 $1$ 个字符串 $s$ 代表 Alice 的数字，仅包含数字或者 $\tt{*}$，并且保证首位不是 $\tt{*}$ 或者 $0$。
## 输出格式

输出 $t$ 行，每行 $1$ 个整数代表最小可能的质数，或者 $-1$ 代表无解。
## 样例

### 样例输入 #1
```
10
1*
3**
7**
83*7
2262
6**1
29*7
889*
777*
225*
```
### 样例输出 #1
```
11
307
701
8317
-1
6011
2917
8893
-1
2251
```
### 样例输入 #2
```
10
4039***
2***5*5
4099961
25**757
7***0**
1***00*
41811*9
6***0*7
8***1**
6561*59
```
### 样例输出 #2
```
4039019
-1
4099961
2509757
7000003
1000003
4181129
6000047
8000101
6561259
```
## 提示

### 样例 3-6

参考附件中的样例。

### 数据范围

$|s|$ 代表 $s$ 串的长度，对于所有数据，$1 \leq t \leq 10, 1 \leq |s| \leq 7$，$s$ 中仅包含数字或者 $\tt{*}$，并且保证首位不是 $\tt{*}$ 或者 $0$。

本题采用捆绑测试，你必须通过子任务中的所有数据点以及其依赖的子任务，才能获得子任务对应的分数。

| 子任务编号 | 分值 | $\mid s\mid$ | 特殊性质 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $35$ | $\leq 7$ | $s$ 中没有 $\tt{*}$ |  |
| $2$ | $30$ | $\leq 4$ |  |  |
| $3$ | $24$ | $\leq 7$ | $s$ 中至多包含 $1$ 个 $\tt{*}$ | $1$ |
| $4$ | $11$ | $\leq 7$ |  | $1,2,3$ |



---

---
title: "[蓝桥杯青少年组国赛 2023] 数独填数"
layout: "post"
diff: 普及/提高-
pid: B4279
tag: ['搜索', '2023', '深度优先搜索 DFS', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组国赛 2023] 数独填数
## 题目背景

本题使用的数独均较为简单，不接受 hack 数据，感兴趣的同学可以查看 [此题目](https://www.luogu.com.cn/problem/P1784) 的说明/提示部分。
## 题目描述

数独是源自 18 世纪瑞士的一种数学游戏。玩家需要根据 $9 \times 9$ 网格上的已知数字，将剩余的所有空格填上数字，使得：
1. 每一行包含数字 $1 \sim 9$ 且不重复；
2. 每一列包含数字 $1 \sim 9$ 且不重复；
3. 每一个 $3 \times 3$ 方块（粗线划分）包含数字 $1 \sim 9$ 且不重复。
## 输入格式

共有 $9$ 行，表示未完成的数独：
- 每行包含 $9$ 个字符（字符只能为 $1 \sim 9$ 的数字和 `.`）；
- `.` 表示数独上的空格；
- 题目数据保证数独有效且答案唯一。
## 输出格式

输出 $9$ 行，表示已完成的数独：
- 每行 $9$ 个数字，数字之间没有空格及其他字符。
## 样例

### 样例输入 #1
```
17.5..8..
.52.1....
.....759.
.8...94.3
.197.4..8
7......15
4.1...6..
3...2..59
...96..3.
```
### 样例输出 #1
```
174593826
952816347
638247591
286159473
519734268
743682915
491375682
367428159
825961734
```


---

---
title: "[CCO 2022] Alternating Heights"
layout: "post"
diff: 普及/提高-
pid: P10050
tag: ['二分', '2022', 'CCO（加拿大）', '深度优先搜索 DFS', '图论建模', '双指针 two-pointer']
---
# [CCO 2022] Alternating Heights
## 题目描述

Troy 计划给 CCO 的学生拍一张合影，他向你寻求帮助。

有 $K$ 个学生，编号从 $1$ 到 $K$。Troy 忘记了学生的身高，但他记得没有两个学生的身高相同。

Troy 有一个序列 $A_{1}, A_{2}, \ldots, A_{N}$，表示合影中从左到右的学生顺序。一个学生可能在 $A$ 中出现多次。你不确定这张合影会怎么拍，但你不愿意认为 Troy 犯了错误。

Troy 会给你 $Q$ 个形式为 $x,y$ 的询问，每个询问为「给定学生序列 $A_{x}, A_{x+1}, \ldots, A_{y}$，他们的身高能否形成一个交替序列？」更具体地说，我们用 $h_i$ 表示第 $i$ 个学生的身高。如果存在一种身高分配$ h_1, h_2, \ldots, h_K$，使得 $h_{A_{x}}>h_{A_{x+1}}<h_{A_{x+2}}>h_{A_{x+3}}<\ldots h_{A_{y}}$，回答 `YES`；否则回答 `NO`。

注意，每个查询都是独立的：也就是说，询问 $i$ 的身高分配与询问 $j$ 的身高分配无关 $(i\neq j)$。
## 输入格式

第一行包含三个用空格分隔的整数 $N, K$ 和 $Q$。

第二行包含 $N$ 个整数，表示 $A_{1}, A_{2}, \ldots, A_{N}\left(1 \leq A_{i} \leq K\right)$。

接下来的 $Q$ 行，每行包含两个用空格分隔的整数 $x$ 和 $y (1 \leq x<y \leq N)$，表示一组查询。
## 输出格式

输出 $Q$ 行。第 $i$ 行，输出 `YES` 或者 `NO`，表示 Troy 的第 $i$ 个查询的答案。
## 样例

### 样例输入 #1
```
6 3 3
1 1 2 3 1 2
1 2
2 5
2 6
```
### 样例输出 #1
```
NO
YES
NO
```
## 提示

## 样例说明

对于第一个询问，不可能有 $h_1>h_1$，所以答案是 `NO`。

对于第二个询问，$h_1>h_2<h_3>h_1$ 的一种方案是 $h_1=160 \mathrm{~cm}, h_2=140 \mathrm{~cm}, h_3=180 \mathrm{~cm}$。另一种方案是 $h_1=1.55 \mathrm{~m}, h_2=1.473 \mathrm{~m}, h_3=1.81 \mathrm{~m}$。

对于第三个询问，不可能同时有 $h_1>h_2$ 和 $h_1<h_2$。

## 数据范围

对于所有的数据，有 $2 \leq N \leq 3000$，$2 \leq K \leq N$，$1 \leq Q \leq 10^{6}$。

子任务编号|	分值|	$N$|	$K$|	$Q$
:-:|:-:|:-:|:-:|:-:
$1$|	$16$|	$2 \leq N \leq 3000$|	$K=2$|	$1 \leq Q \leq 10^{6}$
$2$|	$24$|	$2 \leq N \leq 500$|	$2 \leq K \leq \min (N, 5)$|$1 \leq Q \leq 10^{6}$
$3$	|$28$|	$2 \leq N \leq 3000$	|$2 \leq K \leq N$	|$1 \leq Q \leq 2000$
$4$|	$32$| $2 \leq N \leq 3000$	|$2 \leq K \leq N$	|	$1 \leq Q \leq 10^{6}$


---

---
title: "[ROIR 2023] 斐波那契乘积 (Day 1)"
layout: "post"
diff: 普及/提高-
pid: P10095
tag: ['搜索', '数学', '递归', '2023', 'Special Judge', '枚举', '深度优先搜索 DFS', '斐波那契数列', 'ROIR（俄罗斯）']
---
# [ROIR 2023] 斐波那契乘积 (Day 1)
## 题目背景

翻译自 [ROIR 2023 D1T2](https://neerc.ifmo.ru/school/archive/2022-2023/ru-olymp-regional-2023-day1.pdf)。

斐波那契数指斐波那契数列（$f_0=1,f_1=1,f_i=f_{i-2}+f_{i-1}$）中出现的数。
## 题目描述

给定一个自然数 $n$，求出将其表示为若干个大于 $1$ 的斐波那契数的乘积的方案数。
## 输入格式

第一行一个数 $t$，表示数据组数。

接下来 $t$ 行，每行输入一个数 $n$。
## 输出格式

对于每组测试数据，输出一个数表示答案。
## 样例

### 样例输入 #1
```
5
2
7
8
40
64
```
### 样例输出 #1
```
1
0
2
2
3
```
## 提示

样例解释：
- $2=2$。
- $7$ 无法被表示为斐波那契乘积。
- $8=8=2\times2\times2$。
- $40=5\times8=2\times2\times2\times5$。
- $64=8\times8=2\times2\times2\times8=2\times2\times2\times2\times2\times2$。

本题使用捆绑测试。

| 子任务编号 | 分值 | $2\le n\le$ |
| :----------: | :----------: | :----------: |
| $1$ | $15$ | $100$ |
| $2$ | $17$ | $10^5$ |
| $3$ | $9$ | $n$ 是 $2$ 的整数次幂 |
| $4$ | $38$ | $10^9$ |
| $5$ | $21$ | $10^{18}$ |

对于所有数据，$1\le t\le50$，$2\le n\le10^{18}$。


---

---
title: "[NOIP 2002 普及组] 产生数"
layout: "post"
diff: 普及/提高-
pid: P1037
tag: ['高精度', '2002', 'NOIP 普及组', '深度优先搜索 DFS']
---
# [NOIP 2002 普及组] 产生数
## 题目描述

给出一个整数 $n$ 和 $k$ 个变换规则。

规则：
- 一位数可变换成另一个一位数。
- 规则的右部不能为零。

例如：$n=234,k=2$。有以下两个规则：

- $2\longrightarrow 5$。  
- $3\longrightarrow 6$。 

上面的整数 $234$ 经过变换后可能产生出的整数为（包括原数）:

- $234$。
- $534$。
- $264$。
- $564$。

共 $4$ 种不同的产生数。

现在给出一个整数 $n$ 和 $k$ 个规则。求出经过任意次的变换（$0$ 次或多次），能产生出多少个不同整数。

仅要求输出个数。
## 输入格式

第一行两个整数 $n,k$，含义如题面所示。

接下来 $k$ 行，每行两个整数 $x_i,y_i$，表示每条规则。
## 输出格式

共一行，输出能生成的数字个数。

## 样例

### 样例输入 #1
```
234 2
2 5
3 6

```
### 样例输出 #1
```
4

```
## 提示

对于 $100\%$ 数据，满足 $n \lt 10^{30}$，$k \le 15$。

**【题目来源】**

NOIP 2002 普及组第三题


---

---
title: "[蓝桥杯 2024 省 A] 五子棋对弈"
layout: "post"
diff: 普及/提高-
pid: P10386
tag: ['2024', '深度优先搜索 DFS', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 A] 五子棋对弈
## 题目描述

“在五子棋的对弈中，友谊的小船说翻就翻？” 不！对小蓝和小桥来说，五子棋不仅是棋盘上的较量，更是心与心之间的沟通。这两位挚友秉承着 “友谊第一，比赛第二” 的宗旨，决定在一块 $5 × 5$ 的棋盘上，用黑白两色的棋子来决出胜负。但他们又都不忍心让对方失落，于是决定用一场**和棋（平局）** 作为彼此友谊的见证。
比赛遵循以下规则：
1. 棋盘规模：比赛在一个 $5 × 5$ 的方格棋盘上进行，共有 $25$ 个格子供下棋使用。
2. 棋子类型：两种棋子，黑棋与白棋，代表双方。小蓝持白棋，小桥持黑棋。
3. 先手规则：白棋（小蓝）具有先手优势，即在棋盘空白时率先落子（下棋）。
4. 轮流落子：玩家们交替在棋盘上放置各自的棋子，每次仅放置一枚。
5. 胜利条件：率先在横线、竖线或斜线上形成连续的五个同色棋子的一方获胜。
6. 平局条件：当所有 $25$ 个棋盘格都被下满棋子，而未决出胜负时，游戏以平局告终。

在这一设定下，小蓝和小桥想知道，有多少种不同的棋局情况（终局不同看成不同情况，终局相同而落子顺序不同看成同一种情况），既确保棋盘下满又保证比赛结果为平局。
## 输入格式

这是一道结果填空题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只填写这个整数，填写多余的内容将无法得分。


## 输出格式

这是一道结果填空题，你只需要算出结果后提交即可。本题的结果为一个整数，在提交答案时只填写这个整数，填写多余的内容将无法得分。




---

---
title: "Subway tree systems"
layout: "post"
diff: 普及/提高-
pid: P10477
tag: ['深度优先搜索 DFS', '图遍历', '树的遍历']
---
# Subway tree systems
## 题目描述

Some major cities have subway systems in the form of a tree, i.e. between any pair of stations, there is one and only one way of going by subway. Moreover, most of these cities have a unique central station. Imagine you are a tourist in one of these cities and you want to explore all of the subway system. You start at the central station and pick a subway line at random and jump aboard the subway car. Every time you arrive at a station, you pick one of the subway lines you have not yet travelled on. If there is none left to explore at your current station, you take the subway line back on which you first came to the station, until you eventually have travelled along all of the lines twice,once for each direction. At that point you are back at the central station. Afterwards, all you remember of the order of your exploration is whether you went further away from the central station or back towards it at any given time, i.e. you could encode your tour as a binary string, where 0 encodes taking a subway line getting you one station further away from the central station, and 1 encodes getting you one station closer to the central station.

![](https://cdn.luogu.com.cn/upload/image_hosting/57sf9gvq.png)
## 输入格式

On the first line of input is a single positive integer n, telling the number of test scenarios to follow.Each test scenario consists of two lines, each containing a string of the characters '0' and '1' of length at most 3000, both describing a correct exploration tour of a subway tree system.
## 输出格式

exploration tours of the same subway tree system, or the text "different" if the two strings cannot be exploration tours of the same subway tree system.
## 样例

### 样例输入 #1
```
2
0010011101001011
0100011011001011
0100101100100111
0011000111010101
```
### 样例输出 #1
```
same
different
```
## 题目翻译

**【题目描述】**

一些主要城市的地铁系统采用树状结构，即在任何两个车站之间，只有一条且仅有一条地铁线路。此外，大多数这些城市都有一个独特的中央车站。想象一下，你是这些城市中的一名游客，你想要探索整个地铁系统。你从中央车站出发，随机选择一条地铁线路，跳上地铁列车。每当你到达一个车站，你就会选择一条你尚未乘坐过的地铁线路。如果在当前车站没有其他要探索的地铁线路了，你就会乘坐第一次到达该车站的地铁线路返回，直到最终你沿着所有的线路都行驶了两次，即每个方向都行驶了一次。在那时，你回到了中央车站。之后，你所记得的探索顺序只是在任何给定时间是否向中央车站更远或更近，也就是说，你可以将你的旅程编码为一个二进制字符串，其中 0 表示乘坐一条地铁线路使你离中央车站更远一站，而 1 表示使你离中央车站更近一站。

**【输入格式】**

输入的第一行是一个正整数 $n$，表示接下来要跟随的测试方案的数量。每个测试方案包括两行，每行包含一个长度最多为 $3000$ 的由字符 '0' 和 '1' 组成的字符串，描述了地铁树系统的正确探索旅程。

**【输出格式】**

对于每个测试方案，如果两个字符串可以表示相同地铁树系统的探索旅程，则输出 "same"；如果两个字符串不能表示相同地铁树系统的探索旅程，则输出 "different"。

翻译来自于：ChatGPT。


---

---
title: "Missile Defence System"
layout: "post"
diff: 普及/提高-
pid: P10490
tag: ['搜索', 'O2优化', '深度优先搜索 DFS']
---
# Missile Defence System
## 题目描述

To play against the threats of malicious countries nearby, Country R has updated their missile defence system. The new type system can bring down a series of missiles as long as they are coming in ascending order by altitude or descending order by altitude.

Given the heights of a sequence of coming missiles, the general wants to know how many sets of the new type systems are needed to bring down all of them.
## 输入格式

The input consists of several test cases. The first line of each test case contains an integer $n (1 \le n \le 50)$. The next line contains n different integers indicating the heights.
## 输出格式

For each test case output a single line containing the number of systems needed.For each test case output a single line containing the number of systems needed.
## 样例

### 样例输入 #1
```
5 
3 5 2 4 1 
0
```
### 样例输出 #1
```
2
```
## 提示

Two sets of systems are needed for the sample. One brings down 3, 4 and the other brings down 5, 2, 1.
## 题目翻译

### 题目描述

为了对抗附近恶意国家的威胁，R 国更新了他们的导弹防御系统。

一套防御系统的导弹拦截高度要么一直严格单调上升要么一直严格单调下降。

例如，一套系统先后拦截了高度为 $3$ 和高度为 $4$ 的两发导弹，那么接下来该系统就只能拦截高度大于 $4$ 的导弹。

给定即将袭来的一系列导弹的高度，请你求出至少需要多少套防御系统，就可以将它们全部击落。

### 输入格式

输入包含多组测试用例。

对于每个测试用例，第一行包含整数 $n$，表示来袭导弹数量。

第二行包含 $n$ 个不同的整数，表示每个导弹的高度。

当输入测试用例 $n=0$ 时，表示输入终止，且该用例无需处理。

### 输出格式

对于每个测试用例，输出一行，一个整数，表示所需的防御系统数量。

### 说明与提示

#### 样例解释
对于样例，需要两套系统。一套击落 $3,4$ 号导弹，另一套击落 $5,2,1$ 号导弹。

#### 数据规模与约定
$1 \leq n \leq 50$。


---

---
title: "[USACO06FEB] Backward Digit Sums G/S"
layout: "post"
diff: 普及/提高-
pid: P1118
tag: ['搜索', '2006', 'USACO', '枚举', '深度优先搜索 DFS']
---
# [USACO06FEB] Backward Digit Sums G/S
## 题目描述

`FJ` and his cows enjoy playing a mental game. They write down the numbers from $1$ to$ N(1 \le N  \le 10)$ in a certain order and then sum adjacent numbers to produce a new list with one fewer number.  They repeat this until only a single number is left.  For example, one instance of the game (when $N=4$) might go like this:

```cpp
    3   1   2   4
      4   3   6
        7   9
         16
```
Behind `FJ`'s back, the cows have started playing a more difficult game, in which they try to determine the starting sequence from only the final total and the number $N$.  Unfortunately, the game is a bit above `FJ`'s mental arithmetic capabilities.


Write a program to help `FJ` play the game and keep up with the cows.


## 输入格式

共一行两个正整数 $n,sum$。

## 输出格式

输出包括一行，为字典序最小的那个答案。

当无解的时候，请什么也不输出。

## 样例

### 样例输入 #1
```
4 16
```
### 样例输出 #1
```
3 1 2 4
```
## 提示

- 对于 $40\%$ 的数据，$1\le n\le 7$；  
- 对于 $80\%$ 的数据，$1\le n \le 10$；
- 对于 $100\%$ 的数据，$1\le n \le 12$，$1\le sum\le 12345$。

## 题目翻译


有这么一个游戏：

写出一个 $1\sim n$ 的排列 $a$，然后每次将相邻两个数相加，构成新的序列，再对新序列进行这样的操作，显然每次构成的序列都比上一次的序列长度少 $1$，直到只剩下一个数字位置。

下面是一个例子：

- $3,1,2,4$；
- $4,3,6$；
- $7,9$；
- $16$。

最后得到 $16$ 这样一个数字。

现在想要倒着玩这样一个游戏，如果知道 $n$，以及最后得到的数字的大小 $sum$，请你求出最初序列 $a_i$（应该是一个 $1\sim n$ 的排列）。若答案有多种可能，则输出字典序最小的那一个。

我们称序列 $a=\lang a_1,a_2,\cdots,a_n\rang$ 的字典序小于序列 $b=\lang b_1,b_2,\cdots,b_n\rang$ 的字典序，当且仅当存在一个位置 $p$，满足 $a_1=b_1,a_2=b_2,\cdots,a_{p-1}=b_{p-1},a_p<b_p$。


---

---
title: "取数游戏"
layout: "post"
diff: 普及/提高-
pid: P1123
tag: ['搜索', '枚举', '深度优先搜索 DFS']
---
# 取数游戏
## 题目描述

一个 $N\times M$ 的由非负整数构成的数字矩阵，你需要在其中取出若干个数字，使得取出的任意两个数字不相邻（若一个数字在另外一个数字相邻 $8$ 个格子中的一个即认为这两个数字相邻），求取出数字和最大是多少。
## 输入格式

第一行有一个正整数 $T$，表示了有 $T$ 组数据。

对于每一组数据，第一行有两个正整数 $N$ 和 $M$，表示了数字矩阵为 $N$ 行 $M$ 列。

接下来 $N$ 行，每行 $M$ 个非负整数，描述了这个数字矩阵。
## 输出格式

共 $T$ 行，每行一个非负整数，输出所求得的答案。

## 样例

### 样例输入 #1
```
3
4 4
67 75 63 10
29 29 92 14
21 68 71 56
8 67 91 25
2 3
87 70 85
10 3 17
3 3
1 1 1
1 99 1
1 1 1


```
### 样例输出 #1
```
271
172
99

```
## 提示

### 样例解释

对于第一组数据，取数方式如下：

$$\begin{matrix}
[67] & 75 & 63 & 10 \\
29 & 29 & [92] & 14 \\
[21] & 68 & 71 & 56 \\
8 & 67 & [91] & 25 \\
\end{matrix}$$


### 数据范围及约定

- 对于$20\%$的数据，$1\le N, M \le 3$；
- 对于$40\%$的数据，$1\le N, M\le 4$；
- 对于$60\%$的数据，$1\le N, M\le 5$；
- 对于$100\%$的数据，$1\le N, M\le 6$，$1\le T\le 20$。



---

---
title: "奇怪的电梯"
layout: "post"
diff: 普及/提高-
pid: P1135
tag: ['模拟', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# 奇怪的电梯
## 题目背景

感谢 @[yummy](https://www.luogu.com.cn/user/101694) 提供的一些数据。
## 题目描述

呵呵，有一天我做了一个梦，梦见了一种很奇怪的电梯。大楼的每一层楼都可以停电梯，而且第 $i$ 层楼（$1 \le i \le N$）上有一个数字 $K_i$（$0 \le K_i \le N$）。电梯只有四个按钮：开，关，上，下。上下的层数等于当前楼层上的那个数字。当然，如果不能满足要求，相应的按钮就会失灵。例如： $3, 3, 1, 2, 5$ 代表了 $K_i$（$K_1=3$，$K_2=3$，……），从 $1$ 楼开始。在 $1$ 楼，按“上”可以到 $4$ 楼，按“下”是不起作用的，因为没有 $-2$ 楼。那么，从 $A$ 楼到 $B$ 楼至少要按几次按钮呢？

## 输入格式

共二行。  

第一行为三个用空格隔开的正整数，表示 $N, A, B$（$1 \le N \le 200$，$1 \le A, B \le N$）。

第二行为 $N$ 个用空格隔开的非负整数，表示 $K_i$。

## 输出格式

一行，即最少按键次数，若无法到达，则输出 `-1`。
## 样例

### 样例输入 #1
```
5 1 5
3 3 1 2 5

```
### 样例输出 #1
```
3

```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 200$，$1 \le A, B \le N$，$0 \le K_i \le N$。

本题共 $16$ 个测试点，前 $15$ 个每个测试点 $6$ 分，最后一个测试点 $10$ 分。


---

---
title: "[USACO1.5] 八皇后 Checker Challenge"
layout: "post"
diff: 普及/提高-
pid: P1219
tag: ['搜索', 'USACO', '深度优先搜索 DFS']
---
# [USACO1.5] 八皇后 Checker Challenge
## 题目描述

一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3h71x0yf.png)

上面的布局可以用序列 $2\ 4\ 6\ 1\ 3\ 5$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：

行号 $1\ 2\ 3\ 4\ 5\ 6$

列号 $2\ 4\ 6\ 1\ 3\ 5$

这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。  
并把它们以上面的序列方法输出，解按字典顺序排列。  
请输出前 $3$ 个解。最后一行是解的总个数。


## 输入格式

一行一个正整数 $n$，表示棋盘是 $n \times n$ 大小的。


## 输出格式

前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。

## 样例

### 样例输入 #1
```
6

```
### 样例输出 #1
```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4

```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$6 \le n \le 13$。

题目翻译来自NOCOW。

USACO Training Section 1.5



---

---
title: "[蓝桥杯 2024 国 C] 树的结点值"
layout: "post"
diff: 普及/提高-
pid: P12317
tag: ['2024', '深度优先搜索 DFS', '树的遍历', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 C] 树的结点值
## 题目描述

给定一棵包含 $n$ 个结点的树，其树根编号为 $1$。我们规定其第 $i$ 个结点的值为其对应的子树内所有与 $i$ 奇偶性相同的结点数量。请按编号从小到大的顺序输出其每个结点的值。
## 输入格式

输入的第一行包含一个整数 $n$。

接下来 $n-1$ 行描述每个结点的父结点，其中第 $i$ 行包含一个整数 $F_{i+1}$，表示第 $i+1$ 个结点的父结点。
## 输出格式

输出 $n$ 行，每行包含一个整数表示编号为 $i$ 的结点的值。
## 样例

### 样例输入 #1
```
5
1
2
1
2
```
### 样例输出 #1
```
3
1
1
1
1
```
## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$1 \leq n \leq 5000$；
- 对于所有评测用例，$1 \leq n \leq 2 \times 10^5$，$1 \leq F_i < i$。


---

---
title: "封锁阳光大学"
layout: "post"
diff: 普及/提高-
pid: P1330
tag: ['搜索', '图论', '福建省历届夏令营', '广度优先搜索 BFS', '深度优先搜索 DFS', '二分图']
---
# 封锁阳光大学
## 题目描述

曹是一只爱刷街的老曹，暑假期间，他每天都欢快地在阳光大学的校园里刷街。河蟹看到欢快的曹，感到不爽。河蟹决定封锁阳光大学，不让曹刷街。

阳光大学的校园是一张由 $n$ 个点构成的无向图，$n$ 个点之间由 $m$ 条道路连接。每只河蟹可以对一个点进行封锁，当某个点被封锁后，与这个点相连的道路就被封锁了，曹就无法在这些道路上刷街了。非常悲剧的一点是，河蟹是一种不和谐的生物，当两只河蟹封锁了相邻的两个点时，他们会发生冲突。

询问：最少需要多少只河蟹，可以封锁所有道路并且不发生冲突。

## 输入格式

第一行两个正整数，表示节点数和边数。
接下来 $m$ 行，每行两个整数 $u,v$，表示点 $u$ 到点 $v$ 之间有道路相连。

## 输出格式

仅一行如果河蟹无法封锁所有道路，则输出 `Impossible`，否则输出一个整数，表示最少需要多少只河蟹。

## 样例

### 样例输入 #1
```
3 3
1 2
1 3
2 3

```
### 样例输出 #1
```
Impossible

```
### 样例输入 #2
```
3 2
1 2
2 3

```
### 样例输出 #2
```
1
```
## 提示

【数据规模】   
对于 $100\%$ 的数据，$1\le n \le 10^4$，$1\le m \le 10^5$，保证没有重边。


---

---
title: "[GCJ 2012 #1C] Diamond Inheritance"
layout: "post"
diff: 普及/提高-
pid: P13321
tag: ['搜索', '2012', '深度优先搜索 DFS', 'Google Code Jam']
---
# [GCJ 2012 #1C] Diamond Inheritance
## 题目描述

You are asked to help diagnose class diagrams to identify instances of diamond inheritance. The following example class diagram illustrates the property of diamond inheritance. There are four classes: $A, B, C$ and $D$. An arrow pointing from $X$ to $Y$ indicates that class $X$ inherits from class $Y$.

![](https://cdn.luogu.com.cn/upload/image_hosting/g3yse0or.png)

In this class diagram, $D$ inherits from both $B$ and $C$, $B$ inherits from $A$, and $C$ also inherits from $A$. An inheritance path from $X$ to $Y$ is defined as a sequence of classes $X$, $C_1$, $C_2$, $C_3$, $\dots$, $C_n$, $Y$ where $X$ inherits from $C_1$, $C_i$ inherits from $C_{i+1}$ for $1 \leq i \leq n - 1$, and $C_n$ inherits from $Y$. There are two inheritance paths from $D$ to $A$ in the example above. The first path is $D$, $B$, $A$ and the second path is $D$, $C$, $A$.

A class diagram is said to contain a diamond inheritance if there exists a pair of classes $X$ and $Y$ such that there are at least two different inheritance paths from $X$ to $Y$. The above class diagram is a classic example of diamond inheritance. Your task is to determine whether or not a given class diagram contains a diamond inheritance.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each specifies a class diagram. The first line of each test case gives the number of classes in this diagram, $N$. The classes are numbered from $1$ to $N$. $N$ lines follow. The $i^{th}$ line starts with a non-negative integer $M_i$ indicating the number of classes that class $i$ inherits from. This is followed by $M_i$ distinct positive integers each from $1$ to $N$ representing those classes. You may assume that:

* If there is an inheritance path from $X$ to $Y$ then there is no inheritance path from $Y$ to $X$.
* A class will never inherit from itself.
## 输出格式

For each diagram, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is "Yes" if the class diagram contains a diamond inheritance, "No" otherwise.
## 样例

### 样例输入 #1
```
3
3
1 2
1 3
0
5
2 2 3
1 4
1 5
1 5
0
3
2 2 3
1 3
0
```
### 样例输出 #1
```
Case #1: No
Case #2: Yes
Case #3: Yes
```
## 提示

**Limits**

- $1 \leq T \leq 50$.
- $0 \leq M_i \leq 10$.

**Test set 1 (14 Pts, Visible Verdict)**

- $1 \leq N \leq 50$.

**Test set 2 (14 Pts, Hidden Verdict)**

- $1 \leq N \leq 1,000$.


---

---
title: "[COCI 2020/2021 #1] Bajka"
layout: "post"
diff: 普及/提高-
pid: P13425
tag: ['字符串', '动态规划 DP', '2020', '深度优先搜索 DFS', '记忆化搜索', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #1] Bajka
## 题目描述

Little Fabijan got bored with picture books, so he decided to read his first fairytale. Unfortunately, Fabijan often encounters a word that scares him. To overcome his fear, he will play a game he invented.

The scary word can be represented as an array of $n$ lowercase letters. To start the game, Fabijan puts his finger on some position of the array and writes the letter from that position on a piece of paper. He then performs one of the following moves an arbitrary number of times:

- He moves the finger to a position that is one place to the left or to the right of the current position, if that position exists. Also, Fabijan will then write the letter from the new position on the paper, after the last written letter.
- He moves the finger to any position with the same letter as the current one. Fabijan will not write anything on the paper in this case.

It takes him $|x - y|$ seconds to move the finger from position $x$ to position $y$.

Fabijan will overcome his fear of the word if, at the end of the game, his favourite word is written on the paper. He wants to finish the fairytale as soon as possible, so he asks you to tell him the minimum number of seconds it will take him to overcome his fear of the given scary word.
## 输入格式

The first line contains integers $n$ and $m$ ($1 \leq n, m \leq 300$).

The second line contains $n$ lowercase letters, the word that scares Fabijan.

The third line contains $m$ lowercase letters, Fabijan's favourite word.
## 输出格式

Print the shortest possible time in seconds Fabijan needs to write his favourite word on the paper, or $-1$ if that is not possible.
## 样例

### 样例输入 #1
```
2 2
wa
ac
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
7 7
monolog
nogolom
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
14 5
niskoobrazovan
boook
```
### 样例输出 #3
```
5
```
## 提示

Clarification of the third example:

Fabijan will first put his finger on position 7 and write down the letter 'b'. He will then move the finger two times to the left, and each time write down the letter 'o'. In the next step, he will move the finger to position 6 using the second type of move. Finally, he will again move the finger two times to the left, and write down the letters 'o' and 'k'. It took him five seconds in total, one second per move.

### Scoring

In test cases worth $20$ points, letters in the word that scares Fabijan will be pairwise distinct.


---

---
title: "[NOI2011] 道路修建"
layout: "post"
diff: 普及/提高-
pid: P2052
tag: ['树形数据结构', '2011', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2011] 道路修建
## 题目描述

在 W 星球上有 $n$ 个国家。为了各自国家的经济发展，他们决定在各个国家之间建设双向道路使得国家之间连通。但是每个国家的国王都很吝啬，他们只愿意修建恰好 $n - 1$ 条双向道路。

每条道路的修建都要付出一定的费用，这个费用等于道路长度乘以道路两端 的国家个数之差的绝对值。例如，在下图中，虚线所示道路两端分别有 $2$ 个、$4$ 个国家，如果该道路长度为 $1$，则费用为 $1×|2 - 4|=2$。图中圆圈里的数字表示国家的编号。
 
 ![](https://cdn.luogu.com.cn/upload/pic/2604.png) 

由于国家的数量十分庞大，道路的建造方案有很多种，同时每种方案的修建费用难以用人工计算，国王们决定找人设计一个软件，对于给定的建造方案，计算出所需要的费用。请你帮助国王们设计一个这样的软件。

## 输入格式

输入的第一行包含一个整数 $n$，表示 W 星球上的国家的数量，国家从 $1$ 到 $n$ 编号。

接下来 $n–1$ 行描述道路建设情况，其中第 $i$ 行包含三个整数 $a_i,b_i$ 和 $c_i$，表示第 $i$ 条双向道路修建在 $a_i$ 与 $b_i$ 两个国家之间，长度为 $c_i$。

## 输出格式

输出一个整数，表示修建所有道路所需要的总费用。

## 样例

### 样例输入 #1
```
6
1 2 1
1 3 1
1 4 2
6 3 1
5 2 1
```
### 样例输出 #1
```
20
```
## 提示

对于 $100\%$ 的数据，$1\leq a_i, b_i\leq n$，$0\leq c_i\leq10^6$，$2\leq n\leq 10^6$。
|测试点编号|$n=$|
|:-:|:-:|
|$1$|$2$|
|$2$|$10$|
|$3$|$100$|
|$4$|$200$|
|$5$|$500$|
|$6$|$600$|
|$7$|$800$|
|$8$|$1000$|
|$9$|$10^4$|
|$10$|$2\times 10^4$|
|$11$|$5\times 10^4$|
|$12$|$6\times 10^4$|
|$13$|$8\times 10^4$|
|$14$|$10^5$|
|$15$|$6\times 10^5$|
|$16$|$7\times 10^5$|
|$17$|$8\times 10^5$|
|$18$|$9\times 10^5$|
|$19,20$|$10^6$|




---

---
title: "[NOIP 1996 提高组] 挖地雷"
layout: "post"
diff: 普及/提高-
pid: P2196
tag: ['动态规划 DP', '搜索', '2001', 'NOIP 提高组', '深度优先搜索 DFS', '1996']
---
# [NOIP 1996 提高组] 挖地雷
## 题目描述

在一个地图上有 $N\ (N \le 20)$ 个地窖，每个地窖中埋有一定数量的地雷。同时，给出地窖之间的连接路径。当地窖及其连接的数据给出之后，某人可以从任一处开始挖地雷，然后可以沿着指出的连接往下挖（仅能选择一条路径），当无连接时挖地雷工作结束。设计一个挖地雷的方案，使某人能挖到最多的地雷。

## 输入格式

有若干行。

第 $1$ 行只有一个数字，表示地窖的个数 $N$。

第 $2$ 行有 $N$ 个数，分别表示每个地窖中的地雷个数。

第 $3$ 行至第 $N+1$ 行表示地窖之间的连接情况：

第 $3$ 行有 $n-1$ 个数（$0$ 或 $1$），表示第一个地窖至第 $2$ 个、第 $3$ 个 $\dots$ 第 $n$ 个地窖有否路径连接。如第 $3$ 行为 $11000\cdots 0$，则表示第 $1$ 个地窖至第 $2$ 个地窖有路径，至第 $3$ 个地窖有路径，至第 $4$ 个地窖、第 $5$ 个 $\dots$ 第 $n$ 个地窖没有路径。

第 $4$ 行有 $n-2$ 个数，表示第二个地窖至第 $3$ 个、第 $4$ 个 $\dots$ 第 $n$ 个地窖有否路径连接。

……

第 $n+1$ 行有 $1$ 个数，表示第 $n-1$ 个地窖至第 $n$ 个地窖有否路径连接。（为 $0$ 表示没有路径，为 $1$ 表示有路径）。
## 输出格式

第一行表示挖得最多地雷时的挖地雷的顺序，各地窖序号间以一个空格分隔，不得有多余的空格。

第二行只有一个数，表示能挖到的最多地雷数。

## 样例

### 样例输入 #1
```
5
10 8 4 7 6
1 1 1 0
0 0 0
1 1
1

```
### 样例输出 #1
```
1 3 4 5
27
```
## 提示

**【题目来源】**

NOIP 1996 提高组第三题


---

---
title: "让我们异或吧"
layout: "post"
diff: 普及/提高-
pid: P2420
tag: ['树形数据结构', '洛谷原创', '深度优先搜索 DFS']
---
# 让我们异或吧
## 题目描述

异或是一种神奇的运算,大部分人把它总结成不进位加法.

在生活中 xor 运算也很常见。比如，对于一个问题的回答，是为 $1$，否为 $0$，那么：

（$A$ 是否是男生）xor（$B$ 是否是男生）＝ $A$ 和 $B$ 是否能够成为情侣

好了，现在我们来制造和处理一些复杂的情况。比如我们将给出一颗树，它很高兴自己有 $N$ 个结点。树的每条边上有一个权值。我们要进行 $M$ 次询问，对于每次询问，我们想知道某两点之间的路径上所有边权的异或值。

## 输入格式

输入文件第一行包含一个整数 $N$ ，表示这颗开心的树拥有的结点数，以下有 $N-1$ 行，描述这些边，每行有3个数，$u,v,w$，表示 $u$ 和 $v$ 之间有一条权值为 $w$ 的边。接下来一行有一个整数 $M$，表示询问数。之后的 $M$ 行，每行两个数 $u,v$，表示询问这两个点之间的路径上的权值异或值。

## 输出格式

输出 $M$ 行，每行一个整数，表示异或值

## 样例

### 样例输入 #1
```
5
1 4 9644
2 5 15004
3 1 14635
5 3 9684
3
2 4
5 4
1 1

```
### 样例输出 #1
```
975
14675
0

```
## 提示

对于 $40\%$ 的数据，有 $1 \le N,M \le 3000$；  
对于 $100\%$ 的数据，有 $1 \le N ,M\le 100000$。

保证边权在 `int` 范围内。


---

---
title: "[USACO06DEC] Cow Picnic S"
layout: "post"
diff: 普及/提高-
pid: P2853
tag: ['搜索', '贪心', '2006', 'USACO', '深度优先搜索 DFS']
---
# [USACO06DEC] Cow Picnic S
## 题目描述

The cows are having a picnic! Each of Farmer John's K (1 ≤ K ≤ 100) cows is grazing in one of N (1 ≤ N ≤ 1,000) pastures, conveniently numbered 1...N. The pastures are connected by M (1 ≤ M ≤ 10,000) one-way paths (no path connects a pasture to itself).

The cows want to gather in the same pasture for their picnic, but (because of the one-way paths) some cows may only be able to get to some pastures. Help the cows out by figuring out how many pastures are reachable by all cows, and hence are possible picnic locations.

$K(1 \le K \le 100)$ 只奶牛分散在 $N(1 \le N \le 1000)$ 个牧场．现在她们要集中起来进餐。牧场之间有 $M(1 \le M \le 10000)$ 条有向路连接，而且不存在起点和终点相同的有向路．她们进餐的地点必须是所有奶牛都可到达的地方。那么，有多少这样的牧场可供进食呢？
## 输入格式

Line 1: Three space-separated integers, respectively: K, N, and M


Lines 2..K+1: Line i+1 contains a single integer (1..N) which is the number of the pasture in which cow i is grazing.


Lines K+2..M+K+1: Each line contains two space-separated integers, respectively A and B (both 1..N and A != B), representing a one-way path from pasture A to pasture B.

## 输出格式

Line 1: The single integer that is the number of pastures that are reachable by all cows via the one-way paths.

## 样例

### 样例输入 #1
```
2 4 4
2
3
1 2
1 4
2 3
3 4
```
### 样例输出 #1
```
2
```
## 提示

The cows can meet in pastures 3 or 4.



---

---
title: "[TJOI2007] 跳棋"
layout: "post"
diff: 普及/提高-
pid: P3848
tag: ['搜索', '2007', '各省省选', '递归', '深度优先搜索 DFS', '天津']
---
# [TJOI2007] 跳棋
## 题目背景

在一个n×n的棋盘上，布满了0和1，如图（a）所示（n=7），为叙述方便，将0用字母表示，如图（b）。

![](https://cdn.luogu.com.cn/upload/pic/6077.png)

## 题目描述

跳棋规则：

（1）从某个0格出发，可以向上，下，左，右4个方向连续越过若干个（至少1个）

1格而跳入下一个0格。如图（b）中从A出发，可跳到B，或者到E，但不能直接到K。在跳到B之后还可以继续跳到F;在跳到E之后可继续跳到F或K。直到不能再跳为止。

（2）每个0格只能到达一次，给出的起始点不能再到达，也不能越过。

跳过的距离为跳过1格个数加1，如从A到B，跳过距离为3，从B到F，跳过距离为2。

问   题： 当棋盘和起始点给出之后，问最远能跳的距离是多少？

如上图（b）中，从A出发，可跳过的路线不止一条，其中一条为：

A － B － F － L － K － E  （可能不唯一）

3    2    3    3     3

它的距离为14。

## 输入格式

第一行三个整数  n（1≤n≤100），x，y（起点坐标，上图（b）中A处坐标为1，3）

接下来n行，每行n个数（0或1），数与数之间用一个空格分隔。

## 输出格式

一个整数，即最大可跳距离（若不能跳，输出0）。

## 样例

### 样例输入 #1
```
4  3  2
1  0  1  0 
1  1  1  1
0  0  1  0
1  1  0  1
```
### 样例输出 #1
```
6
```
## 提示

$\text{upd 2022.7.27}$：新增加一组 Hack 数据。


---

---
title: "[USACO1.2] 命名那个数字 Name That Number"
layout: "post"
diff: 普及/提高-
pid: P3864
tag: ['模拟', '字符串', '搜索', 'USACO', '枚举', '深度优先搜索 DFS']
---
# [USACO1.2] 命名那个数字 Name That Number
## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。

## 输入格式

第一行一行包含一个编号(长度可能从1到12)。

接下来4617行，每行一个字符串表示可以被接受的名字
## 输出格式

(file namenum.out)

以字典顺序输出一个有效名字的不重复列表，一行一个名字。 如果没有有效名字，输出'NONE'。 //注释：似乎数字只有8^4种排列（1与0不能用）

## 样例

### 样例输入 #1
```
4734
NMSL
GREG
LSDC
....(太多了不写了)
```
### 样例输出 #1
```
GREG

```


---

---
title: "[JLOI2009] 二叉树问题"
layout: "post"
diff: 普及/提高-
pid: P3884
tag: ['2009', '各省省选', '吉林', '深度优先搜索 DFS']
---
# [JLOI2009] 二叉树问题
## 题目描述

如下图所示的一棵二叉树的深度、宽度及结点间距离分别为：

- 深度：$4$
- 宽度：$4$
- 结点 8 和 6 之间的距离：$8$
- 结点 7 和 6 之间的距离：$3$

其中宽度表示二叉树上同一层最多的结点个数，节点 $u, v$ 之间的距离表示从 $u$ 到 $v$ 的最短有向路径上向根节点的边数的两倍加上向叶节点的边数。

![](https://cdn.luogu.com.cn/upload/pic/6843.png)

给定一颗以 1 号结点为根的二叉树，请求出其深度、宽度和两个指定节点 $x, y$ 之间的距离。

## 输入格式

第一行是一个整数，表示树的结点个数 $n$。  
接下来 $n - 1$ 行，每行两个整数 $u, v$，表示树上存在一条连接 $u, v$ 的边。  
最后一行有两个整数 $x, y$，表示求 $x, y$ 之间的距离。
## 输出格式

输出三行，每行一个整数，依次表示二叉树的深度、宽度和 $x, y$ 之间的距离。
## 样例

### 样例输入 #1
```
10                                
1 2                            
1 3                            
2 4
2 5
3 6
3 7
5 8
5 9
6 10
8 6

```
### 样例输出 #1
```
4
4
8
```
## 提示

对于全部的测试点，保证 $1 \leq u, v, x, y \leq n \leq 100$，且给出的是一棵树。保证 $u$ 是 $v$ 的父结点。


---

---
title: "树的分解"
layout: "post"
diff: 普及/提高-
pid: P3915
tag: ['贪心', '树形数据结构', '深度优先搜索 DFS']
---
# 树的分解
## 题目描述

给出 $N$ 个点的树和 $K$，问能否把树划分成 $\frac{N}{K}$ 个连通块，且每个连通块的点数都是 $K$。
## 输入格式

第一行，一个整数 $T$，表示数据组数。接下来 $T$ 组数据，对于每组数据：

第一行，两个整数 $N, K$。

接下来 $N - 1$ 行，每行两个整数 $A_i, B_i$，表示边 $(A_i, B_i)$。点用 $1, 2, \ldots, N$ 编号。
## 输出格式

对于每组数据，输出 `YES` 或 `NO`。
## 样例

### 样例输入 #1
```
2
4 2
1 2
2 3
3 4
4 2
1 2
1 3
1 4

```
### 样例输出 #1
```
YES
NO
```
## 提示

- 对于 $60 \%$ 的数据，$1 \le N, K \le 10^3$；
- 对于 $100 \%$ 的数据，$1 \le T \le 10$，$1 \le N ,K \le 10^5$。


---

---
title: "[NOIP 2017 提高组] 奶酪"
layout: "post"
diff: 普及/提高-
pid: P3958
tag: ['搜索', '2017', '并查集', 'NOIP 提高组', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOIP 2017 提高组] 奶酪
## 题目背景

NOIP2017 提高组 D2T1
## 题目描述

现有一块大奶酪，它的高度为 $h$，它的长度和宽度我们可以认为是无限大的，奶酪中间有许多半径相同的球形空洞。我们可以在这块奶酪中建立空间坐标系，在坐标系中，奶酪的下表面为 $z = 0$，奶酪的上表面为 $z = h$。

现在，奶酪的下表面有一只小老鼠 Jerry，它知道奶酪中所有空洞的球心所在的坐标。如果两个空洞相切或是相交，则 Jerry 可以从其中一个空洞跑到另一个空洞，特别地，如果一个空洞与下表面相切或是相交，Jerry 则可以从奶酪下表面跑进空洞；如果一个空洞与上表面相切或是相交，Jerry 则可以从空洞跑到奶酪上表面。

位于奶酪下表面的 Jerry 想知道，在不破坏奶酪的情况下，能否利用已有的空洞跑 到奶酪的上表面去?

空间内两点 $P_1(x_1,y_1,z_1)$、$P2(x_2,y_2,z_2)$ 的距离公式如下：


$$\mathrm{dist}(P_1,P_2)=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2}$$

## 输入格式

每个输入文件包含多组数据。

第一行，包含一个正整数 $T$，代表该输入文件中所含的数据组数。

接下来是 $T$ 组数据，每组数据的格式如下： 第一行包含三个正整数 $n,h,r$，两个数之间以一个空格分开，分别代表奶酪中空洞的数量，奶酪的高度和空洞的半径。

接下来的 $n$ 行，每行包含三个整数 $x,y,z$，两个数之间以一个空格分开，表示空洞球心坐标为 $(x,y,z)$。

## 输出格式

 $T$ 行，分别对应 $T$ 组数据的答案，如果在第 $i$ 组数据中，Jerry 能从下表面跑到上表面，则输出 `Yes`，如果不能，则输出 `No`。

## 样例

### 样例输入 #1
```
3 
2 4 1 
0 0 1 
0 0 3 
2 5 1 
0 0 1 
0 0 4 
2 5 2 
0 0 2 
2 0 4
```
### 样例输出 #1
```
Yes
No
Yes
```
## 提示

【输入输出样例 $1$ 说明】

 ![](https://cdn.luogu.com.cn/upload/pic/10860.png) 

第一组数据,由奶酪的剖面图可见：

第一个空洞在 $(0,0,0)$ 与下表面相切；

第二个空洞在 $(0,0,4)$ 与上表面相切；

两个空洞在 $(0,0,2)$ 相切。

输出 `Yes`。

 
第二组数据,由奶酪的剖面图可见：

两个空洞既不相交也不相切。

输出 `No`。

 
第三组数据,由奶酪的剖面图可见：

两个空洞相交，且与上下表面相切或相交。

输出 `Yes`。

【数据规模与约定】

对于 $20\%$ 的数据，$n = 1$，$1 \le h$，$r \le  10^4$，坐标的绝对值不超过 $10^4$。

对于 $40\%$ 的数据，$1 \le n \le 8$，$1 \le h$，$r \le 10^4$，坐标的绝对值不超过 $10^4$。

对于 $80\%$ 的数据，$1 \le n \le 10^3$，$1 \le h , r \le 10^4$，坐标的绝对值不超过 $10^4$。

对于 $100\%$ 的数据，$1 \le n \le 1\times 10^3$，$1 \le h , r \le 10^9$，$T \le 20$，坐标的绝对值不超过 $10^9$。


---

---
title: "最大食物链计数"
layout: "post"
diff: 普及/提高-
pid: P4017
tag: ['动态规划 DP', '搜索', '图论', '排序', '深度优先搜索 DFS', '拓扑排序']
---
# 最大食物链计数
## 题目背景

你知道食物链吗？Delia 生物考试的时候，数食物链条数的题目全都错了，因为她总是重复数了几条或漏掉了几条。于是她来就来求助你，然而你也不会啊！写一个程序来帮帮她吧。

## 题目描述

给你一个食物网，你要求出这个食物网中最大食物链的数量。

（这里的“最大食物链”，指的是**生物学意义上的食物链**，即**最左端是不会捕食其他生物的生产者，最右端是不会被其他生物捕食的消费者**。）

Delia 非常急，所以你只有 $1$ 秒的时间。

由于这个结果可能过大，你只需要输出总数模上 $80112002$ 的结果。

## 输入格式

第一行，两个正整数 $n、m$，表示生物种类 $n$ 和吃与被吃的关系数 $m$。

接下来 $m$ 行，每行两个正整数，表示被吃的生物A和吃A的生物B。

## 输出格式

一行一个整数，为最大食物链数量模上 $80112002$ 的结果。

## 样例

### 样例输入 #1
```
5 7
1 2
1 3
2 3
3 5
2 5
4 5
3 4
```
### 样例输出 #1
```
5
```
## 提示

各测试点满足以下约定：

 ![](https://cdn.luogu.com.cn/upload/pic/12011.png) 

【补充说明】

数据中不会出现环，满足生物学的要求。（感谢 @AKEE ）



---

---
title: "[USACO19JAN] Icy Perimeter S"
layout: "post"
diff: 普及/提高-
pid: P5198
tag: ['搜索', '2019', 'USACO', '深度优先搜索 DFS']
---
# [USACO19JAN] Icy Perimeter S
## 题目背景

USACO 一月月赛银组第二题
## 题目描述

Farmer John 要开始他的冰激凌生意了！他制造了一台可以生产冰激凌球的机器，然而不幸的是形状不太规则，所以他现在希望优化一下这台机器，使其产出的冰激凌球的形状更加合理。
机器生产出的冰激凌的形状可以用一个 $N \times N$（$1 \leq N \leq 1000$）的矩形图案表示，例如：

```
##....
....#.
.#..#.
.#####
...###
....##
```

每个 `.` 字符表示空的区域，每个 `#` 字符表示一块 $1 \times 1$ 的正方形格子大小的冰激凌。

不幸的是，机器当前工作得并不是很正常，可能会生产出多个互不相连的冰激凌球（上图中有两个）。一个冰激凌球是连通的，如果其中每个冰激凌的正方形格子都可以从这个冰激凌球中其他所有的冰激凌格子出发重复地前往东、南、西、北四个方向上相邻的冰激凌格子所到达。

Farmer John 想要求出他的面积最大的冰激凌球的面积和周长。冰激凌球的面积就是这个冰激凌球中 `#` 的数量。如果有多个冰激凌球并列面积最大，他想要知道其中周长最小的冰激凌球的周长。在上图中，小的冰激凌球的面积为 $2$，周长为 $6$，大的冰激凌球的面积为 $13$，周长为 $22$。

注意一个冰激凌球可能在中间有“洞”（由冰激凌包围着的空的区域）。如果这样，洞的边界同样计入冰激凌球的周长。冰激凌球也可能出现在被其他冰激凌球包围的区域内，在这种情况下它们计为不同的冰激凌球。例如，以下这种情况包括一个面积为 $1$ 的冰激凌球，被包围在一个面积为 $16$ 的冰激凌球内：

```
#####
#...#
#.#.#
#...#
#####
```

同时求得冰激凌球的面积和周长十分重要，因为 Farmer John 最终想要最小化周长与面积的比值，他称这是他的冰激凌的“冰周率”。当这个比率较小的时候，冰激凌化得比较慢，因为此时冰激凌单位质量的表面积较小。

## 输入格式

输入的第一行包含 $N$，以下 $N$ 行描述了机器的生产结果。其中至少出现一个 `#` 字符。
## 输出格式

输出一行，包含两个空格分隔的整数，第一个数为最大的冰激凌球的面积，第二个数为它的周长。如果多个冰激凌球并列面积最大，输出其中周长最小的那一个的信息。
## 样例

### 样例输入 #1
```
6
##....
....#.
.#..#.
.#####
...###
....##
```
### 样例输出 #1
```
13 22
```


---

---
title: "[USACO19OPEN] Fence Planning S"
layout: "post"
diff: 普及/提高-
pid: P5429
tag: ['模拟', '2019', 'USACO', '并查集', '深度优先搜索 DFS']
---
# [USACO19OPEN] Fence Planning S
## 题目描述

Farmer John 的 $ N $ 头奶牛，编号为 $ 1 \ldots N $ （ $ 2 \leq N \leq 10^5 $ ），拥有一种围绕“哞网”，一些仅在组内互相交流却不与其他组进行交流的奶牛小组，组成的复杂的社交网络。

每头奶牛位于农场的二维地图上的不同位置 $ (x,y) $ ，并且我们知道有 $ M $ 对奶牛( $ 1 \leq M<10^5 $ )会相互哞叫。两头相互哞叫的奶牛属于同一哞网。

为了升级他的农场，Farmer John 想要建造一个四边与 $ x $ 轴和 $ y $ 轴平行的长方形围栏。Farmer John 想要使得至少一个哞网完全被围栏所包围（在长方形边界上的奶牛计为被包围的）。请帮助 Farmer John 求出满足他的要求的围栏的最小可能周长。有可能出现这一围栏宽为 $0$ 或高为 $0$ 的情况。
## 输入格式

输入的第一行包含 $ N $ 和 $ M $ 。以下 $ N $ 行每行包含一头奶牛的 $ x $ 坐标和 $ y $ 坐标（至多 $ 10^8 $ 的非负整数）。以下 $ M $ 行每行包含两个整数 $ a $ 和 $ b $ ，表示奶牛 $ a $ 和 $ b $ 之间有哞叫关系。每头奶牛都至少存在一个哞叫关系，并且输入中不会出现重复的哞叫关系。
## 输出格式

输出满足 Farmer John 的要求的围栏的最小周长。
## 样例

### 样例输入 #1
```
7 5
0 5
10 5
5 0
5 10
6 7
8 6
8 4
1 2
2 3
3 4
5 6
7 6
```
### 样例输出 #1
```
10
```


---

---
title: "[USACO18JAN] MooTube S"
layout: "post"
diff: 普及/提高-
pid: P6111
tag: ['搜索', '2018', 'USACO', '并查集', '深度优先搜索 DFS']
---
# [USACO18JAN] MooTube S
## 题目背景

*本题与 [金组同名题目](/problem/P4185) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 5000$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。
## 输入格式

第一行输入包含 $N$ 和 $Q$（$1 \leq Q \leq 5000$）。

接下来的 $N-1$ 行描述了 FJ 手动比较的一对视频。 每行包括三个整数  $p_i$，$q_i$ 和 $r_i$（$1 \leq p_i, q_i \leq N$，$1 \leq r_i \leq 10^9$），表示视频 $p_i$ 和 $q_i$ 已连接并且相关性为 $r_i$。

接下来的 $Q$ 行描述了 Farmer John 的 $Q$ 个问题。每行包含两个整数，$k_i$ 和 $v_i$（$1 \leq k_i \leq 10^9$，$1 \leq v_i \leq N$），表示 FJ 的第 $i$ 个问题询问中当 $K = k_i$ 时，第 $v_i$ 个视频推荐列表中将推荐的视频数。
## 输出格式

输出 $Q$ 行。在第 $i$ 行，输出 FJ 的第 $i$ 个问题的答案。
## 样例

### 样例输入 #1
```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
```
### 样例输出 #1
```
3
0
2
```


---

---
title: "[USACO06OCT] Cows on Skates G"
layout: "post"
diff: 普及/提高-
pid: P6207
tag: ['搜索', '2006', 'USACO', 'Special Judge', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [USACO06OCT] Cows on Skates G
## 题目描述

**本题使用 Special Judge。**

Farmer John 把农场划分为了一个 $r$ 行 $c$ 列的矩阵，并发现奶牛们无法通过其中一些区域。此刻，Bessie 位于坐标为 $(1,1)$ 的区域，并想到坐标为 $(r,c)$ 的牛棚享用晚餐。她知道，以她所在的区域为起点，每次移动至相邻的四个区域之一，总有一些路径可以到达牛棚。

这样的路径可能有无数种，请你输出任意一种，并保证所需移动次数不超过 $100000$。
## 输入格式

第一行两个整数 $r,c$。
 
接下来 $r$ 行，每行 $c$ 个字符，表示 Bessie 能否通过相应位置的区域。字符只可能是 `.` 或 `*`。

- `.` 表示 Bessie 可以通过该区域。
- `*` 表示 Bessie 无法通过该区域。
## 输出格式

若干行，每行包含两个用空格隔开的整数，表示 Bessie 依次通过的区域的坐标。

显然，输出的第一行是 `1 1` ，最后一行是 `r c`。

相邻的两个坐标所表示的区域必须相邻。
## 样例

### 样例输入 #1
```
5 8
..*...**
*.*.*.**
*...*...
*.*.*.*.
....*.*.
```
### 样例输出 #1
```
1 1
1 2
2 2
3 2
3 3
3 4
2 4
1 4
1 5
1 6
2 6
3 6
3 7
3 8
4 8
5 8
```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le r\le 113$，$1\le c\le 77$。

------------

**【样例说明】* *

![](https://cdn.luogu.com.cn/upload/image_hosting/3gsutffb.png)

图为样例输出的示意图。答案不唯一。


---

---
title: "[YsOI2020] 植树"
layout: "post"
diff: 普及/提高-
pid: P6591
tag: ['O2优化', '枚举', '深度优先搜索 DFS']
---
# [YsOI2020] 植树
## 题目背景


Ysuperman 响应号召，决定在幼儿园里植树。
## 题目描述

Ysuperman 有一棵 $n$ 个节点的无根树 $T$。如果你不知道树是什么，TA 很乐意告诉你，树是一个没有环的无向联通图。

既然树是无根的，那就没有办法种植。Ysuperman 研究了很久的园艺，发现一个节点如果可以成为根，它必须十分平衡，这意味着以它为根时，与它**直接相连的节点，他们的子树大小都相同**。

你作为幼儿园信息组一把手，Ysuperman 给你一棵树，你能在 $1s$ 内找到所有可能成为根的节点吗？
## 输入格式

第一行一个正整数 $n$，表示树的节点个数。

此后 $n-1$ 行，每行两个正整数 $u_i,v_i$，表示树上有一条直接连接 $u_i,v_i$ 的边。保证每条边只会给出一次。
## 输出格式

不超过 $n$ 个从小到大的整数，用空格隔开，表示每一个可能成为根的节点。
## 样例

### 样例输入 #1
```
2
1 2

```
### 样例输出 #1
```
1 2 
```
### 样例输入 #2
```
4
1 2
2 3
3 4

```
### 样例输出 #2
```
1 4 

```
### 样例输入 #3
```
9
1 2
1 3
4 1
5 1
1 6
1 9
8 1
1 7

```
### 样例输出 #3
```
1 2 3 4 5 6 7 8 9 

```
## 提示

### 样例说明

#### 样例说明 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/gsiug69y.png)

以 $1$ 为根时，与 $1$ 直接相连的点有 $\{2\}$，因为只有一个所以大小全部相同。

以 $2$ 为根时，与 $2$ 直接相连的点有 $\{1\}$，因为只有一个所以大小全部相同。

所以答案为 $1,2$。

#### 样例说明 $2$

![](https://cdn.luogu.com.cn/upload/image_hosting/p7fsretv.png)

以 $1$ 为根时，与 $1$ 直接相连的点有 $\{2\}$，因为只有一个所以大小全部相同。

以 $2$ 为根时，与 $2$ 直接相连的点有 $\{1,3\}$，子树大小分别为 $\{1,2\}$，不相同。

以 $3$ 为根时，与 $3$ 直接相连的点有 $\{2,4\}$，子树大小分别为 $\{2,1\}$，不相同。

以 $4$ 为根时，与 $4$ 直接相连的点有 $\{3\}$，因为只有一个所以大小全部相同。

所以答案为 $1,4$。

----

### 数据范围

**本题采用捆绑测试。**

| $\rm{subtask}$ | $n$ |  分数|
| :-----------: | :-----------: | :----: |
| $1$ | $\le 5000$ | $40$ |
| $2$ | $\le 10^6$ | $60$ |

对于 $100\%$ 的数据，满足 $1 \le n\le 10^6$。

------

### 提示

由于输入输出量较大，你可能需要快速输入/输出。


---

---
title: "[Code+#7] 最小路径串"
layout: "post"
diff: 普及/提高-
pid: P6606
tag: ['深度优先搜索 DFS', 'Code+']
---
# [Code+#7] 最小路径串
## 题目描述

$n$ 个点 $m$ 条边的无向图中，所有点用从 `0` 开始的 `6` 位数字串编号，即 `000000`、`000001`、`000002`、……直到 $n-1$ 对应的 $6$ 位数字串。保证 $n\le 10^6$，所以 $6$ 位的编号不会溢出。

对于除了 `000000` 以外的每个点，你需要找到一条从 `000000` 出发且不经过重复点的路径，使得路径上所有点的数字串顺次连接形成的串的字典序最小。比较两个不同的串的字典序的方法是：如果其中某个串是另一个的前缀，则较短的串字典序较小；否则，找出两个串从左往右扫描时遇到的首个不相等的位置，在这个位置上的数字较小的串字典序较小。

由于输出路径过于麻烦，你不需要完整地输出路径，只需要将路径上所有点的数字串视作一个整数，输出这个数对 $998244353$ 取模的结果。
## 输入格式

第一行输入两个整数 $n$ 和 $m$。

第二行输入一个长度为 $12m$ 的数字串，依次表示每条边。每条边用 $12$ 个数字表示，其中前 $6$ 个与后 $6$ 个数字分别表示这条边所连接的两个点的编号。

注意，输入中可能会包含自环或重边。
## 输出格式

输出 $n-1$ 行，依次输出除了点 `000000` 本身以外，点 `000000` 到每个点的字典序最小的路径，视为整数后对 $998244353$ 取模的结果。如果点 `000000` 不可到达某个点，则在对应的行改为输出 $-1$。
## 样例

### 样例输入 #1
```
5 5
000000000003000001000003000001000002000002000000000002000003
```
### 样例输出 #1
```
2000001
2
517560944
-1
```
## 提示

### 样例解释

- 从 `000000` 到 `000001` 所求的路径对应的串为 `000000000002000001`。
- 从 `000000` 到 `000002` 所求的路径对应的串为 `000000000002`。
- 从 `000000` 到 `000003` 所求的路径对应的串为 `000000000002000001000003`，对 $998244353$ 取模后为 $517560944$。
- 从 `000000` 到 `000004` 不存在路径。

### 子任务

子任务 $1$（$11$ 分）
- $1\le n\le 10^6, m = 0$。

子任务 $2$（$55$ 分）
- $1\le n\le 10, 0\le m\le20$。

子任务 $3$（$34$ 分）
- $1\le n\le 10^6, 0\le m\le 10^6$。


---

---
title: "选择题"
layout: "post"
diff: 普及/提高-
pid: P6691
tag: ['图论', '2020', '并查集', 'O2优化', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# 选择题
## 题目背景

小 L 喜欢逻辑推理。

一天，他在一本由英国哲士沃·协德编写的《我也不知道为什么要叫这个名字的一本有关逻辑学的书》中翻到了一道奇特的问题，但他并不会做。他知道你善于用程序解决问题，于是决定让你来帮助他完成这些问题。
## 题目描述

这是一道有 $n$ 个选项的选择题，每个选项的内容都很独特。第 $i$ 个选项的内容的形式如下：

+ 第 $a_i$ 个选项是正确/错误的

小 L 认为这种题目的答案不一定是唯一的，所以他想问题这道题有多少种合法的答案（可以全部正确或全部错误）。他还想问你这么多答案中，正确选项最多和最少的答案分别有多少个正确选项。

当然，如果这道题不存在合法的答案，你可以直接回答小 L `No answer`。
## 输入格式

第一行有一个正整数 $n$，表示选项个数。

接下来 $n$ 行，每行有两个整数 $a_i,opt_i$，描述一个选项。其中当 $opt_i=1$ 时，表示这个选项的内容为 **第 $a_i$ 个选项是正确的**；当 $opt_i=0$ 时，表示这个选项的内容为 **第 $a_i$ 个选项是错误的**。
## 输出格式

如果没有答案满足这道选择题，输出`No answer`。

否则输出三行，每行一个正整数，分别为合法答案数及正确选项最多和最少的答案分别有多少个正确选项。其中合法答案数要对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
4
2 1
4 0
1 1
2 0
```
### 样例输出 #1
```
2
3
1
```
### 样例输入 #2
```
10
4 1
7 0
2 0
3 1
7 1
5 0
9 1
10 1
8 0
1 1
```
### 样例输出 #2
```
No answer
```
## 提示

对于样例一，一共有下面 $2$ 种正确答案：

+ 第 $1,2,3$ 个选项是正确的。
+ 第 $4$ 个选项是正确的。

其中正确选项最多的答案有 $3$ 个选项正确，正确选项最少的答案有 $1$ 个选项正确。

### 数据范围
对于 $10\%$ 的数据，$n\leq 10$。  
对于 $30\%$ 的数据，$n\leq 100$。  
对于 $60\%$ 的数据，$n\leq 10^3$。  
对于 $100\%$ 的数据，$n\leq 10^6,1\leq a_i\leq n,i\neq a_i,opt_i\in\{0,1\}$。


---

---
title: "[COCI 2015/2016 #3] MOLEKULE"
layout: "post"
diff: 普及/提高-
pid: P7228
tag: ['2015', 'Special Judge', '深度优先搜索 DFS', 'COCI（克罗地亚）']
---
# [COCI 2015/2016 #3] MOLEKULE
## 题目描述

有 $N$ 个点和 $N-1$ 条无向边，定义一张有向图的代价为一条在这张有向图上的最长通路长度。

现在把这 $N-1$ 条无向边指定方向，使得形成的有向图代价最小。

求一种指定方向的方案。
## 输入格式

第一行一个整数 $N$ 代表点数。      
接下来 $N-1$ 行每行两个整数 $a_i,b_i$ 代表一条边。
## 输出格式

$N-1$ 行每行一个整数 $r$：

- 如果 $r=1$ 代表从 $a_i$ 连向 $b_i$。
- 如果 $r=0$ 代表从 $b_i$ 连向 $a_i$。
## 样例

### 样例输入 #1
```
3
1 2
2 3
```
### 样例输出 #1
```
1
0
```
### 样例输入 #2
```
4
2 1
1 3
4 1
```
### 样例输出 #2
```
0
1
0
```
## 提示

#### 样例 1 解释

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/f1q6jgtu.png)

这张图的代价为 $1$，注意 $0\ 1$ 也是一组最优解。

#### 样例 2 解释

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/96aku20f.png)

#### 数据规模与约定

对于 $30\%$ 的数据，$N \le 20$。       
对于 $100\%$ 的数据，$2 \le N \le 10^5$，$1 \le a_i,b_i\le N$。

**本题采用 Special Judge。**        
你只需要输出任意一种合法方案。

#### 说明

翻译自 [COCI 2015-2016 #3 C MOLEKULE](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)。


---

---
title: "[USACO21DEC] Walking Home B"
layout: "post"
diff: 普及/提高-
pid: P7995
tag: ['搜索', 'USACO', '2021', '深度优先搜索 DFS']
---
# [USACO21DEC] Walking Home B
## 题目描述

奶牛 Bessie 正准备从她最喜爱的草地回到她的牛棚。

农场位于一个 $N \times N$ 的方阵上（$2 \leq N \leq 50$），其中她的草地在左上角，牛棚在右下角。Bessie 想要尽快回家，所以她只会向下或向右走。有些地方有草堆（haybale），Bessie 无法穿过；她必须绕过它们。

Bessie 今天感到有些疲倦，所以她希望改变她的行走方向至多 $K$ 次（$1 \leq K \leq 3$）。

Bessie 有多少条不同的从她最爱的草地回到牛棚的路线？如果一条路线中 Bessie 经过了某个方格而另一条路线中没有，则认为这两条路线不同。
## 输入格式

每个测试用例的输入包含 $T$ 个子测试用例，每个子测试用例描述了一个不同的农场，并且必须全部回答正确才能通过整个测试用例。输入的第一行包含 $T$（$1 \leq T \leq 50$）。每一个子测试用例如下。

每个子测试用例的第一行包含 $N$ 和 $K$。

以下 $N$ 行每行包含一个长为 $N$ 的字符串。每个字符为 $\texttt{.}$，如果这一格是空的，或 $\texttt{H}$，如果这一格中有草堆。输入保证农场的左上角和右下角没有草堆。
## 输出格式

输出 $T$ 行，第 $i$ 行包含在第 $i$ 个子测试用例中 Bessie 可以选择的不同的路线数量。
## 样例

### 样例输入 #1
```
7
3 1
...
...
...
3 2
...
...
...
3 3
...
...
...
3 3
...
.H.
...
3 2
.HH
HHH
HH.
3 3
.H.
H..
...
4 3
...H
.H..
....
H...
```
### 样例输出 #1
```
2
4
6
2
0
0
6
```
## 提示

【样例解释】

我们将使用一个由字符 D 和 R 组成的字符串来表示 Bessie 的路线，其中 D 和 R 分别表示 Bessie 向下（down）或向右（right）移动。

第一个子测试用例中，Bessie 的两条可能的路线为 DDRR 和 RRDD。

第二个子测试用例中，Bessie 的四条可能的路线为 DDRR，DRRD，RDDR 和 RRDD。

第三个子测试用例中，Bessie 的六条可能的路线为 DDRR，DRDR，DRRD，RDDR，RDRD 和 RRDD。

第四个子测试用例中，Bessie 的两条可能的路线为 DDRR 和 RRDD。

第五和第六个子测试用例中，Bessie 不可能回到牛棚。

第七个子测试用例中，Bessie 的六条可能的路线为 DDRDRR，DDRRDR，DDRRRD，RRDDDR，RRDDRD 和 RRDRDD。

【数据范围】

- 测试点 2 满足 $K = 1$。
- 测试点 3-5 满足 $K = 2$。
- 测试点 6-10 满足 $K = 3$。


---

---
title: "[传智杯 #3 决赛] 面试"
layout: "post"
diff: 普及/提高-
pid: P8838
tag: ['枚举', '深度优先搜索 DFS', '传智杯']
---
# [传智杯 #3 决赛] 面试
## 题目背景

disangan233 和 disangan333 去面试了，面试官给了一个问题，热心的你能帮帮他们吗？
## 题目描述

现在有 $n$ 个服务器，服务器 $i$ 最多能处理 $a_i$ 大小的数据。

接下来会有 $k$ 条指令 $b_k$，指令 $i$ 表示发送 $b_i$ 的数据，需要你分配一个空闲的服务器。

请你算出一个序列 $p_k$ 表示指令 $i$ 的数据分配给服务器 $p_i$，且 $p_k$ 的字典序最小；如果无法分配，输出 "-1"。

对于所有数据，$n,k\leq 6$，$a_i,b_i \leq 10$。 
## 输入格式

输入共 $3$ 行。

第 $1$ 行输入 $2$ 个正整数 $n,k$。

第 $2$ 行输入 $n$ 个正整数 $a_i$，表示服务器 $i$ 最多能处理的数据大小。

第 $3$ 行输入 $k$ 个正整数 $b_i$，表示指令 $i$。
## 输出格式

输出共 $1$ 行 $k$ 个正整数 $p_1\ldots p_k$，或者输出 "-1"。
## 样例

### 样例输入 #1
```
6 6
1 9 1 9 8 1
1 1 4 5 1 4
```
### 样例输出 #1
```
1 3 2 4 6 5
```
## 提示

### 样例解释

第 1 条指令分给服务器 1；  
第 2 条指令分给服务器 3；  
第 3 条指令分给服务器 2；  
第 4 条指令分给服务器 4；  
第 5 条指令分给服务器 6；  
第 6 条指令分给服务器 5。


---

---
title: "[USACO23JAN] Following Directions S"
layout: "post"
diff: 普及/提高-
pid: P9014
tag: ['模拟', '搜索', 'USACO', '2023', '深度优先搜索 DFS']
---
# [USACO23JAN] Following Directions S
## 题目描述

**Note: The time limit for this problem is 8s, four times the default.** 

Farmer John has a big square field split up into an $(N+1) \times (N+1) (1 \le N \le 1500)$ grid of cells. Let cell $(i,j)$ denote the cell in the $i$-th row from the top and $j$-th column from the left. There is one cow living in every cell $(i,j)$ such that $1 \le i,j \le N$, and each such cell also contains a signpost pointing either to the right or downward. Also, every cell $(i,j)$ such that either $i=N+1$ or $j=N+1$, except for $(N+1,N+1)$, contains a vat of cow feed. Each vat contains cow feed of varying price; the vat at $(i,j)$ costs $c_{i,j} (1 \le c_{i,j} \le 500)$ to feed each cow.

Every day at dinner time, Farmer John rings the dinner bell, and each cow keeps following the directions of the signposts until it reaches a vat, and is then fed from that vat. Then the cows all return to their original positions for the next day.

To maintain his budget, Farmer John wants to know the total cost to feed all the cows each day. However, during every day, before dinner, the cow in in some cell $(i,j)$ flips the direction of its signpost (from right to down or vice versa). The signpost remains in this direction for the following days as well, unless it is flipped back later.

Given the coordinates of the signpost that is flipped on each day, output the cost for every day (with $Q$ days in total, $1 \le Q \le 1500$). 
## 输入格式

The first line contains $N (1 \le N \le 1500)$.

The next $N+1$ lines contain the rows of the grid from top to bottom, containing the initial directions of the signposts and the costs ci,j of each vat. The first $N$ of these lines contain a string of $N$ directions `R` or `D` (representing signposts pointing right or down, respectively), followed by the cost $c_{i,N+1}$. The $(N+1)$-th line contains $N$ costs $c_{N+1,j}$.

The next line contains $Q(1 \le Q \le 1500)$.

Then follow $Q$ additional lines, each consisting of two integers $i$ and $j (1 \le i,j \le N)$, which are the coordinates of the cell whose signpost is flipped on the corresponding day. 
## 输出格式

$Q+1$ lines: the original value of the total cost, followed by the value of the total cost after each flip. 
## 样例

### 样例输入 #1
```
2
RR 1
DD 10
100 500
4
1 1
1 1
1 1
2 1
```
### 样例输出 #1
```
602
701
602
701
1501
```
## 提示

### Explanation for Sample 1

Before the first flip, the cows at $(1,1)$ and $(1,2)$ cost $1$ to feed, the cow at $(2,1)$ costs $100$ to feed, and the cow at $(2,2)$ costs $500$ to feed, for a total cost of $602$. After the first flip, the direction of the signpost at $(1,1)$ changes from `R` to `D`, and the cow at $(1,1)$ now costs $100$ to feed (while the others remain unchanged), so the total cost is now $701$. The second and third flips switch the same sign back and forth. After the fourth flip, the cows at $(1,1)$ and $(2,1)$ now cost $500$ to feed, for a total cost of $1501$.

### Scoring

 - Inputs $2-4$: $1 \le N,Q \le 50$
 - Inputs $5-7$: $1 \le N,Q \le 250$
 - Inputs $2-10$: The initial direction in each cell, as well as the queries, are uniformly randomly generated.
 - Inputs $11-15$: No additional constraints.
## 题目翻译

## 题目描述

**注：本题时限为 8s，是默认时限的四倍。**

Farmer John 有一个正方形的草地，草地被划分为了 $(N + 1) \times (N + 1)(1 \leq N \leq 1500)$ 的格子。设 $(i, j)$ 为从上到下、从左到右第 $i$ 行，第 $j$ 列的格子。每个满足 $1 \leq i, j \leq n$ 的格子 $(i, j)$ 之中都住着一头牛，而且每个这样的格子上都有一个路标指向右或下。除此之外，所有满足 $i = N + 1$ 或 $j = N + 1$ 的格子，除了 $(N + 1, N + 1)$ 都会有一个饲料桶。牛在每个饲料桶进食需要的价格不同；位置 $(i, j)$ 上的桶喂饱一只牛需要价格 $c_{i, j}(1 \leq c_{i, j} \leq 500)$。

每天晚饭时间，Farmer John 摇响晚餐铃时，所有牛都沿着路标的指向前进，直到它们遇到了饲料桶，之后它们会在它们自己遇到的饲料桶那里进食。第二天，所有牛又会回到自己原来的位置。

为了维持预算，Farmer John 想要知道每天喂食需要的价钱。然而，每天晚饭之前，总会有一头牛 $(i, j)$ 翻转它那里的路标（原来向下则变成向右，反之亦然）。被翻转的路标指向将在后面的日子里保持不变，除非它又被进行了翻转。

给出每天被翻转的路标的坐标，请输出每天喂食需要的价格（总共有 $Q$ 天，$1 \leq Q \leq 1500$）。

## 输入格式

第一行为 $N(1 \leq N \leq 1500)$

接下来的 $N + 1$ 行从上到下输入初始的路标朝向和每个饲料桶的价格 $c_{i, j}$。前 $N$ 行每行包含一个长度为 $N$ 的字符串，其中每个字符只能是 `R` 或 `D`（`R` 表示向右，`D` 表示向下），之后是一个数，表示价格 $c_{i, N + 1}$，第 $(N + 1)$ 行包含 $N$ 个数，依次表示价格 $c_{N + 1, j}$。

接下来的一行为 $Q(1 \leq Q \leq 1500)$。

之后的 $Q$ 行，每行有两个整数 $i$ 和 $j(1 \leq i, j \leq N$，表示每天被翻转的路标的坐标。

## 输出格式

共 $Q + 1$ 行：第一行是初始的总价格，之后 $Q$ 行依次是每次被翻转后的总价格。

## 说明/提示

### 样例 1 解释

在第一次翻转之前，喂养在位置 $(1, 1)$ 和 $(1, 2)$ 的牛需要的价格都为 $1$，喂养在 $(2, 1)$ 的牛需要的价格为 $100$，喂养在 $(2, 2)$ 的牛需要的价格为 $500$。总价格为 $602$。第一次翻转后，在 $(1, 1)$ 处的路标由 `R` 变为 `D`，此时在位置 $(1, 1)$ 的牛喂养的价格变为 $100$（其它牛的价格没有变化），所以总价为 $701$。第二次和第三次翻转都在来回翻转同一个路标。第四次翻转后，在位置 $(1, 1)$ 和位置 $(2, 1)$ 的牛喂养的价格变为 $500$，总价变为 $1501$。

### 数据范围

- 测试点 $2 - 4$ 中：$1 \leq N, Q \leq 50$。

- 测试点 $5 - 7$ 中：$1 \leq N, Q \leq 250$。

- 测试点 $2 - 10$ 中：每个路标初始朝向以及被翻转的路标为随机生成。

- 测试点 $11 - 15$ 中：无特殊条件。


---

---
title: "「DTOI-5」3-1"
layout: "post"
diff: 普及/提高-
pid: P9304
tag: ['树形数据结构', 'O2优化', '深度优先搜索 DFS', '树的遍历']
---
# 「DTOI-5」3-1
## 题目背景

——『太阳』这种东西，以前似乎是存在的。

传说是这么讲的——白色的火焰发出闪耀的光芒，天空则是清澄无比的蔚蓝。

据说诸神与其创造物所掀起的『大战』，使得大地化为焦土，灰烬遮蔽了苍穹。

灰烬冲击到天上流动的星辰之力——精灵回廊，发出了光芒，将天空染成红色。

而那样的红色，覆盖了仍然持续着互相残杀的每一块土地。

或者那是这个星球本身发出的悲鸣与流出的鲜血吧……

血色的天空上，只有——蓝色的灰飘然落下。

~~回来吧3579，我最骄傲的信仰/ll~~
## 题目描述

里克在视线可及的范围内发现了一颗古老的「神树」。

神树是一颗树，树上有 $n$ 个含有魔法装置的位置。经过初步「考察」，有 $n - 1$ 条魔法连接，第 $i(1 \leq i \leq n - 1)$ 条连接 $u_i, v_i$ 两个魔法装置，保证 $u_i \neq v_i$ 且 $1\leq u_i,v_i\leq n$。这两个装置可以相互**双向地**在 $1$ 单位时间内通行，保证仅由这 $n - 1$ 条连接，每个魔法装置都可以相互到达。

此外，有 $n - 1$ 条特殊连接，对于每个魔法装置 $i \in [2, n]$，可以**瞬间**传送到第 $1$ 个魔法装置，花费 $0$ 单位时间。**特殊连接总共只能使用一次**。

里克初始在魔法装置 $1$ 处。现在，给出这棵「神树」的结构，里克想要在若干时间内研究尽可能多的魔法装置。我们假定，研究一个魔法装置只需要到达该装置处，并且不需要花费额外时间。

里克想让你尽快计算出，对所有 $k \in [1, n]$，如果要恰好研究 $k$ 个不同的魔法装置，**并且随之返回魔法装置 $\bm 1$**，最少应花费多少时间。
## 输入格式

第一行，一个整数 $n$。

接下来 $n - 1$ 行，每行两个整数 $u_i, v_i$。
## 输出格式

共 $n$ 行，第 $i$ 行一个整数表示 $k = i$ 的答案。
## 样例

### 样例输入 #1
```
5
1 2
1 3
2 4
2 5
```
### 样例输出 #1
```
0
1
2
4
6
```
### 样例输入 #2
```
见下发的 hope/hope2.in
```
### 样例输出 #2
```
见下发的 hope/hope2.ans
```
## 提示

**【样例解释 $\bm 1$】**

+ $k = 1$ 时，里克只需要呆在装置 $1$ 处。
+ $k = 2$ 时，里克的路径可以是 $1 \rightarrow 2 \Rightarrow 1$。
+ $k = 3$ 时，里克的路径可以是 $1 \rightarrow 2 \rightarrow 4 \Rightarrow 1$。
+ $k = 4$ 时，里克的路径可以是 $1 \rightarrow 2 \rightarrow 4 \Rightarrow 1 \rightarrow 3\rightarrow 1$。
+ $k = 5$ 时，里克的路径可以是 $1 \rightarrow 3\rightarrow 1 \rightarrow 2 \rightarrow 5 \rightarrow 2 \rightarrow 4 \Rightarrow 1$。

**【样例解释 $\bm 2$】**

这组数据满足测试点编号 $13 \sim 20$ 的性质。

**【数据规模与约定】**

| 测试点编号 | 特殊限制 |
| :--------: | :------: |
| $1 \sim 2$ | $n = 3$ |
| $3 \sim 4$ | $n = 5$ |
| $5 \sim 6$ | $n = 100$ |
| $7 \sim 8$ | $n = 1000$ |
| $9 \sim 10$ | $u_i = 1, v_i = i + 1$ |
| $11 \sim 12$ | $u_i = i, v_i = i + 1$ |
| $13 \sim 20$ | 无特殊限制 |

对于所有数据，$1 \leq n \leq 10^5$，$1 \leq u_i, v_i \leq n$。


---

