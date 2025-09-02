---
title: "【烂题杯 Round 1】糖果色的梦"
layout: "post"
diff: 省选/NOI-
pid: P10889
tag: ['网络流', 'O2优化', '费用流', '线性规划']
---
# 【烂题杯 Round 1】糖果色的梦
## 题目描述

小 A 做了一个糖果色的梦，于是他打算买一些糖果送给他的 $n$ 个小朋友。

小 A 可以零售地购买糖果，也可以批发地购买糖果，他还可以批发地回收糖果。

- 零售地购买糖果：每次小 A 可以给一个小朋友购买一个糖果，这将会花费 $1$ 元；

- 批发地购买糖果：每次小 A 可以给连续且不少于 $k$ 个小朋友分别购买一个糖果，设小朋友的个数为 $l$，这将会花费 $l-B$ 元；

- 批发地回收糖果：每次小 A 可以给连续且不少于 $k$ 个小朋友分别收回一个糖果，这将会获得 $C$ 元；

第 $i$ 个小朋友都希望自己得到不少于 $a_i$ 个糖果。求小 A 满足所有小朋友的希望的最小代价。
## 输入格式

第一行输入两个正整数 $n$、$k$，表示小朋友数量、批发最少需要的小朋友数量。

接下来输入两个整数 $B$、$C$。

接下来一行 $n$ 个非负整数 $a_1,a_2,\cdots,a_n$，表示每个小朋友希望的糖果个数。
## 输出格式

输出一行一个整数，表示最小代价。
## 样例

### 样例输入 #1
```
4 2
1 1
1 2 3 4
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
10 5
1 3
1 1 4 5 1 4 1 9 19 81
```
### 样例输出 #2
```
124
```
## 提示

**样例 1 解释：**

我们给 $[1,2]$ 小朋友批发分别购买 $1$ 个糖果，代价为 $1$；给 $[3,4]$ 小朋友批发分别购买 $3$ 个糖果，代价为 $3$；给 $2$ 小朋友单独购买糖果，代价为 $1$；给 $4$ 小朋友单独购买糖果，代价为 $1$。总共代价为 $6$。

**数据范围：**

对于 $20\%$ 数据，满足 $1\le k\le n\le 10$。

对于 $40\%$ 数据，满足内存限制至少为 512 MB。

对于 $100\%$ 数据，满足 $1\le k\le n\le 1000$，$0\le B\le k$，$0\le C\le k-B$，$0\le a_i\le 10^9$。满足内存限制至少为 10 MB。


---

---
title: "餐巾计划问题"
layout: "post"
diff: 省选/NOI-
pid: P1251
tag: ['贪心', '网络流', 'O2优化', '费用流', '网络流与线性规划 24 题']
---
# 餐巾计划问题
## 题目描述

一个餐厅在相继的 $N$ 天里，每天需用的餐巾数不尽相同。假设第 $i$ 天需要 $r_i$ 块餐巾（$i = 1, 2, \dots, N$）。餐厅可以购买新的餐巾，每块餐巾的费用为 $p$ 分；或者把旧餐巾送到快洗部，洗一块需 $m$ 天，其费用为 $f$ 分；或者送到慢洗部，洗一块需 $n$ 天（$n \gt m$），其费用为 $s$ 分（$s \lt f$）。

每天结束时，餐厅必须决定将多少块脏的餐巾送到快洗部，多少块餐巾送到慢洗部，以及多少块保存起来延期送洗。但是每天洗好的餐巾和购买的新餐巾数之和，要满足当天的需求量。

试设计一个算法为餐厅合理地安排好 $N$ 天中餐巾使用计划，使总的花费最小。编程找出一个最佳餐巾使用计划。

## 输入格式

由标准输入提供输入数据。文件第 $1$ 行有 $1$ 个正整数 $N$，代表要安排餐巾使用计划的天数。

接下来的一行是餐厅在相继的 $N$ 天里，每天需用的餐巾数。

最后一行包含 $5$ 个正整数 $p, m, f, n, s$。$p$ 是每块新餐巾的费用；$m$ 是快洗部洗一块餐巾需用天数；$f$ 是快洗部洗一块餐巾需要的费用；$n$ 是慢洗部洗一块餐巾需用天数；$s$ 是慢洗部洗一块餐巾需要的费用。

## 输出格式

将餐厅在相继的 $N$ 天里使用餐巾的最小总花费输出。

## 样例

### 样例输入 #1
```
3
1 7 5 
11 2 2 3 1

```
### 样例输出 #1
```
134

```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 2 \times 10^3$，$1 \le r_i \le 10^7$，$1 \le p, f, s \le 10^4$。



---

---
title: "[NERC 2020] Button Lock"
layout: "post"
diff: 省选/NOI-
pid: P12901
tag: ['2020', '网络流', 'Special Judge', '费用流', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Button Lock
## 题目描述

You are standing in front of the room with great treasures. The only thing stopping you is the door with a push-button combination lock. This lock has $d$ buttons with digits from $0$ to $d - 1$. Whenever you press a button, it stays pushed down. You can not pop back up just one button, but there is a "RESET" button --- pressing it pops up all other buttons. Initially, no buttons are pushed down.

The door instantly opens when some specific set of digits is pushed down. Sadly, you don't know the password for it. Having read the documentation for this specific lock, you found out that there are $n$ possible passwords for this particular lock.  

Find the shortest sequence of button presses, such that all possible passwords appear at least once during its execution. Any shortest correct sequence of button presses will be accepted.
## 输入格式

The first line contains two integers $d$ and $n$ ($1 \le d \le 10$; $1 \le n \le 2^d - 1$).
Next $n$ lines describe possible passwords. Each line contains a string $s_i$ of $d$ zeros and ones: for all $j$ from $1$ to $d$ the $j$-th character is $\tt{1}$ iff the button with the digit $j - 1$ must be pushed down.

All strings $s_i$ are different, and each string contains at least one $\tt{1}$.
## 输出格式

On the first line, print the number $k$ --- the minimum number of button presses.
On the second line, print $k$ tokens, describing the sequence. Whenever you press a button with a digit, print that digit. Whenever you press "RESET", print $\tt{R}$.
## 样例

### 样例输入 #1
```
2 2
10
11
```
### 样例输出 #1
```
2
0 1
```
### 样例输入 #2
```
3 4
001
111
101
011
```
### 样例输出 #2
```
6
2 0 R 1 2 0
```
## 提示

In the second example, the sequence $\tt{1 2 R 2 0 1}$ is also possible.


---

---
title: "[GCJ 2021 #3] Square Free"
layout: "post"
diff: 省选/NOI-
pid: P13040
tag: ['图论', '2021', 'Special Judge', '费用流', 'Google Code Jam']
---
# [GCJ 2021 #3] Square Free
## 题目描述

We have a matrix of square cells with $\mathbf{R}$ rows and $\mathbf{C}$ columns. We need to draw a diagonal in each cell. Exactly one of two possible diagonals must be drawn in each cell: the forward slash diagonal, which connects the bottom-left and the top-right corners of the cell, or the backslash diagonal, which connects the top-left and the bottom-right corners of the cell.

For each row and column, we want to draw a specific number of diagonals of each type. Also, after all the diagonals are drawn, the matrix should be square free. That is, there should be no squares formed using the diagonals we added.

For example, suppose we have a matrix with 4 rows and 4 columns. The number next to each row is the exact number of forward slash diagonals there must be in that row. The number below each column is the exact number of forward slash diagonals there must be in that column.

![](https://cdn.luogu.com.cn/upload/image_hosting/xc6yu1qy.png)

There are multiple ways to fill the matrix respecting those per-row and per-column amounts. Below we depict three possibilities:

![](https://cdn.luogu.com.cn/upload/image_hosting/1gul8pxa.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/xip3jkqs.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/o3qbkh80.png)

The first two matrices are not square free, while the third matrix is. In the first matrix, there is a square of side-length 2 diagonals with its vertices in the middle of each side of the matrix. In the second matrix, there is a square of side-length 1 diagonal drawn in the bottom-right corner. In the third matrix, there is no square. The third matrix would then be a valid drawing according to all the rules.

Given the size of the matrix and the exact number of forward slash diagonals that must be drawn in each row and column, produce any square free matrix that satisfies the row and column constraints, or say that one does not exist.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of exactly three lines. The first line of a test case contains $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns of the matrix. The second line of a test case contains $\mathbf{R}$ integers $\mathbf{S}_1, \mathbf{S}_2, \ldots, \mathbf{S}_\mathbf{R}$. $\mathbf{S}_i$ is the exact number of forward slash diagonals that must be drawn in the $i$-th row from the top. The third line of a test case contains $\mathbf{C}$ integers $\mathbf{D}_1, \mathbf{D}_2, \ldots, \mathbf{D}_\mathbf{C}$. $\mathbf{D}_i$ is the exact number of forward slash diagonals that must be drawn in the $i$-th column from the left.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is `IMPOSSIBLE` if there is no filled matrix that follows all rules and `POSSIBLE` otherwise. If you output `POSSIBLE`, output $\mathbf{R}$ more lines with $\mathbf{C}$ characters each. The $j$-th character of the $i$-th of these lines must be `/` if the diagonal drawn in the $i$-th row from the top and $j$-th column from the left in your proposed matrix is a forward slash diagonal, and `\` otherwise. Your proposed matrix must be valid according to all rules.
## 样例

### 样例输入 #1
```
4
4 4
3 2 3 3
3 3 2 3
2 3
1 1
1 1 1
2 3
1 2
1 1 1
3 3
2 0 2
2 0 2
```
### 样例输出 #1
```
Case #1: POSSIBLE
//\/
\/\/
///\
/\//
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
\\/
//\
Case #4: POSSIBLE
/\/
\\\
/\/
```
## 提示

**Sample Explanation**

Sample Case #1 is the one explained above.

In Sample Case #2, there must be a total of 2 forward slash diagonals according to the sum of the row totals, but a total of 3 according to the sum of the column totals. It is therefore impossible to follow all rules.

In Sample Case #3 the only matrices that follow the row and column totals are the following:

![](https://cdn.luogu.com.cn/upload/image_hosting/qrbza4hc.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/439fpaug.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/ib6vqil8.png)

Since the first two contain a square, the third one is the only valid output for this case.

In Sample Case #4 there is only one way to fill the matrix that follows the row and column totals, shown in the picture below. Note that it produces a single rectangle, shown in blue in the picture. But, since that rectangle is not a square, the matrix is square free.

![](https://cdn.luogu.com.cn/upload/image_hosting/ljxlouhx.png)

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $0 \leq \mathbf{S}_i \leq \mathbf{C}$, for all $i$.
- $0 \leq \mathbf{D}_i \leq \mathbf{R}$, for all $i$.

**Test Set 1 (7 Pts, Visible Verdict)**

- $2 \leq \mathbf{R} \leq 6$.
- $2 \leq \mathbf{C} \leq 6$.

**Test Set 2 (13 Pts, Hidden Verdict)**

- $2 \leq \mathbf{R} \leq 20$.
- $2 \leq \mathbf{C} \leq 20$.


---

---
title: "[NOI2012] 美食节"
layout: "post"
diff: 省选/NOI-
pid: P2050
tag: ['2012', 'NOI', '网络流', '费用流']
---
# [NOI2012] 美食节
## 题目描述

CZ 市为了欢迎全国各地的同学，特地举办了一场盛大的美食节。

作为一个喜欢尝鲜的美食客，小 M 自然不愿意错过这场盛宴。他很快就尝遍了美食节所有的美食。然而，尝鲜的欲望是难以满足的。尽管所有的菜品都很可口，厨师做菜的速度也很快，小 M 仍然觉得自己桌上没有已经摆在别人餐桌上的美食是一件无法忍受的事情。于是小 M 开始研究起了做菜顺序的问题，即安排一个做菜的顺序使得同学们的等待时间最短。

小 M 发现，美食节共有 $n$ 种不同的菜品。每次点餐，每个同学可以选择其中的**一个菜品**。总共有 $m$ 个厨师来制作这些菜品。当所有的同学点餐结束后，菜品的制作任务就会分配给每个厨师。然后每个厨师就会同时开始做菜。**厨师们会按照要求的顺序进行制作，并且每次只能制作一人份**。

此外，小 M 还发现了另一件有意思的事情——虽然这 $m$ 个厨师都会制作全部的 $n$ 种菜品，但**对于同一菜品，不同厨师的制作时间未必相同**。他将菜品用 $1, 2, \ldots, n$ 依次编号，厨师用 $1, 2, \ldots, m$ 依次编号，将第 $j$ 个厨师制作第 $i$ 种菜品的时间记为 $t_{i,j}$。

小 M 认为：每个同学的等待时间为**所有厨师开始做菜起，到自己那份菜品完成为止**的时间总长度。换句话说，如果一个同学点的菜是某个厨师做的第 $k$ 道菜，则他的等待时间就是这个厨师制作前 $k$ 道菜的时间之和。而**总等待时间**为**所有同学的等待时间之和**。

现在，小 M 找到了所有同学的点菜信息——有 $p_i$ 个同学点了第 $i$ 种菜品（$i=1, 2, \ldots, n$）。他想知道的是最小的总等待时间是多少。

## 输入格式

输入文件的第 $1$ 行包含两个正整数 $n$ 和 $m$，表示菜品的种数和厨师的数量。

第 $2$ 行包含 $n$ 个正整数，其中第 $i$ 个数为 $p_i$，表示点第 $i$ 种菜品的人数。

接下来有 $n$ 行，每行包含 $m$ 个非负整数，这 $n$ 行中的第 $i$ 行的第 $j$ 个数为 $t_{i,j}$，表示第 $j$ 个厨师制作第 $i$ 种菜品所需的时间。

输入文件中每行相邻的两个数之间均由一个空格隔开，行末均没有多余空格。

## 输出格式

输出仅一行包含一个整数，为总等待时间的最小值。

## 样例

### 样例输入 #1
```
3 2 
3 1 1 
5 7 
3 6 
8 9
```
### 样例输出 #1
```
47
```
## 提示

厨师 $1$ 先制作 $1$ 份菜品 $2$，再制作 $2$ 份菜品 $1$。点这 $3$ 道菜的 $3$ 个同学的等待时间分别为 $3$，$3+5=8$，$3+5+5=13$。

厨师 $2$ 先制作 $1$ 份菜品 $1$，再制作 $1$ 份菜品 $3$。点这 $2$ 道菜的 $2$ 个同学的等待时间分别为 $7$，$7+9=16$。

总等待时间为 $3+8+13+7+16=47$。

虽然菜品 $1$ 和菜品 $3$ 由厨师 $1$ 制作更快，如果这些菜品都由厨师 $1$ 制作，总等待时间反而更长。如果按上述的做法，将 $1$ 份菜品 $1$ 和 $1$ 份菜品 $3$ 调整到厨师 $2$ 制作，这样厨师 $2$ 不会闲着，总等待时间更短。

可以证明，没有更优的点餐方案。

每组数据的 $n,m$ 和 $p$ 值如下：  

|测试点编号| $n$| $m$| $p$|   
|:------:|:----:|:----:|:----:|    
|$1$|$n = 5$| $m = 5$| $p = 10$|   
|$2$| $n = 40$| $m = 1$ |$p = 400$ |  
|$3$| $n = 40$| $m = 2$ |$p = 300$ |
|$4$| $n = 40$| $m = 40$| $p = 40$ |
|$5$| $n = 5$| $m = 40$| $p = 100$ |
|$6$| $n = 10$| $m = 50$| $p = 200$ |
|$7$| $n = 20$| $m = 60$| $p = 400$ |
|$8$| $n = 40$| $m = 80$| $p = 600$ |
|$9$| $n = 40$| $m = 100$| $p = 800$ |
|$10$| $n = 40$| $m = 100$| $p = 800$ |


对于 $100\%$ 的数据，$n \leq 40$，$m\leq 100$，$p\leq 800$，$t_{i,j}\leq 1000$（其中 $p = \sum p_i$）。



---

---
title: "[SCOI2007] 修车"
layout: "post"
diff: 省选/NOI-
pid: P2053
tag: ['2007', '四川', '各省省选', '网络流', '费用流']
---
# [SCOI2007] 修车
## 题目描述

同一时刻有 $N$ 位车主带着他们的爱车来到了汽车维修中心。

维修中心共有 $M$ 位技术人员，不同的技术人员对不同的车进行维修所用的时间是不同的。

现在需要安排这 $M$ 位技术人员所维修的车及顺序，使得顾客平均等待的时间最小。

说明：顾客的等待时间是指从他把车送至维修中心到维修完毕所用的时间。
## 输入格式

第一行有两个数 $M,N$，表示技术人员数与顾客数。

接下来 $N$ 行，每行 $M$ 个整数。第 $i+1$ 行第 $j$ 个数表示第 $j$ 位技术人员维修第 $i$ 辆车需要用的时间 $T_{i,j}$。
## 输出格式

最小平均等待时间，答案精确到小数点后 $2$ 位。
## 样例

### 样例输入 #1
```
2 2
3 2
1 4
```
### 样例输出 #1
```
1.50
```
## 提示

对于 $100\%$ 的数据，$2\le M\le 9$，$1\le N\le 60$，$1\le T\le 10^3$。


---

---
title: "[SDOI2009] 晨跑"
layout: "post"
diff: 省选/NOI-
pid: P2153
tag: ['2009', '各省省选', '山东', '深度优先搜索 DFS', '费用流']
---
# [SDOI2009] 晨跑
## 题目描述

Elaxia 最近迷恋上了空手道，他为自己设定了一套健身计划，比如俯卧撑、仰卧起坐等等，不过到目前为止，他坚持下来的只有晨跑。 

现在给出一张学校附近的地图，这张地图中包含 $N$ 个十字路口和 $M$ 条街道，Elaxia 只能从 一个十字路口跑向另外一个十字路口，街道之间只在十字路口处相交。

Elaxia 每天从寝室出发跑到学校，保证寝室编号为 $1$，学校编号为 $N$。 

Elaxia 的晨跑计划是按周期（包含若干天）进行的，由于他不喜欢走重复的路线，所以在一个周期内，每天的晨跑路线都不会相交（在十字路口处），寝室和学校不算十字路口。

Elaxia 耐力不太好，他希望在一个周期内跑的路程尽量短，但是又希望训练周期包含的天数尽量长。

除了练空手道，Elaxia 其他时间都花在了学习和找 MM 上面，所有他想请你帮忙为他设计 一套满足他要求的晨跑计划。

可能存在 $1\rightarrow n$ 的边。这种情况下，这条边只能走一次。
## 输入格式

第一行两个整数 $N,M$，表示十字路口数和街道数。 

接下来 $M$ 行，每行 $3$ 个数 $a,b,c$，表示路口 $a$ 和路口 $b$ 之间有条长度为 $c$ 的街道（单向）。
## 输出格式

一行两个整数，最长周期的天数和满足最长天数的条件下最短的路程度。
## 样例

### 样例输入 #1
```
7 10
1 2 1
1 3 1
2 4 1
3 4 1
4 5 1
4 6 1
2 5 5
3 6 6
5 7 1
6 7 1
```
### 样例输出 #1
```
2 11

```
## 提示

- 对于 $30\%$ 的数据，$N\le 20$，$M \le 120$。
- 对于 $100\%$ 的数据，$N\le 200$，$M\le 2\times 10^4,1\le c\le 10^4$。


---

---
title: "[HNOI2001] 棋盘变换"
layout: "post"
diff: 省选/NOI-
pid: P2225
tag: ['动态规划 DP', '2001', '各省省选', '湖南', '费用流']
---
# [HNOI2001] 棋盘变换
## 题目描述

一个 $n\times n$ 的棋盘，在其中填入 $1$ 和 $-1$。经过一次变换后，方格里的每个数将会变成变换之前与之相邻的四个数的积。例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/2q4jbad8.png)

但有一些状态，变换前和变换后是一样的，例如全部是 $1$ 的状态。这种状态被称为不变状态。

你的任务是要找到所有本质不同的不变状态（旋转或翻转之后的状态被视为是本质上相同的）。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个正整数表示所有本质不同的方案数。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
5
```
## 提示

$1\le n\le 30$。

题目给出范围内，不变状态总数 $<9\times 10^3$。


---

---
title: "[SDOI2010] 星际竞速"
layout: "post"
diff: 省选/NOI-
pid: P2469
tag: ['2010', '各省省选', '网络流', '山东', '费用流']
---
# [SDOI2010] 星际竞速
## 题目描述

10 年一度的银河系赛车大赛又要开始了。作为全银河最盛大的活动之一，夺得这个项目的冠军无疑是很多人的梦想，来自杰森座 $\alpha$ 星的悠悠也是其中之一。

赛车大赛的赛场由 $N$ 颗行星和 $M$ 条双向星际航路构成，其中每颗行星都有一个不同的引力值。大赛要求车手们从一颗与这 $N$ 颗行星之间没有任何航路的天体出发，访问这 $N$ 颗行星每颗恰好一次，首先完成这一目标的人获得胜利。

由于赛制非常开放，很多人驾驶着千奇百怪的自制赛车来参赛。这次悠悠驾驶的赛车名为超能电驴，这是一部凝聚了全银河最尖端科技结晶的梦幻赛车。作为最高科技的产物，超能电驴有两种移动模式：高速航行模式和能力爆发模式。在高速航行模式下，超能电驴会展开反物质引擎，以数倍于光速的速度沿星际航路高速航行。在能力爆发模式下，超能电驴脱离时空的束缚，使用超能力进行空间跳跃——在经过一段时间的定位之后，它能瞬间移动到任意一个行星。

天不遂人愿，在比赛的前一天，超能电驴在一场离子风暴中不幸受损，机能出现了一些障碍：在使用高速航行模式的时候，只能由每个星球飞往引力比它大的星球，否则赛车就会发生爆炸。

尽管心爱的赛车出了问题，但是悠悠仍然坚信自己可以取得胜利。他找到了全银河最聪明的贤者——你，请你为他安排一条比赛的方案，使得他能够用最少的时间完成比赛。

## 输入格式

输入文件 starrace.in 的第一行是两个正整数 $N, M$。

第二行 $N$ 个数 $A_1,\cdots,A_N$，其中 $A_i$ 表示使用能力爆发模式到达行星 $i$ 所需的定位时间。

接下来 $M$ 行，每行 $3$ 个正整数 $u_i, v_i, w_i$，表示在编号为 $u_i$ 和 $v_i$ 的行星之间存在一条需要航行 $w_i$ 时间的星际航路。

输入数据已经按引力值排序，也就是编号小的行星引力值一定小，且不会有两颗行星引力值相同。

## 输出格式

输出文件 starrace.out 仅包含一个正整数，表示完成比赛所需的最少时间。

## 样例

### 样例输入 #1
```
3 3

1 100 100

2 1 10

1 3 1

2 3 1
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
3 3

1 2 3

1 2 100

1 3 100

2 3 100
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
4 5

100 1000 10 100

1 2 100

2 3 100

4 3 100

1 3 20

2 4 20
```
### 样例输出 #3
```
230
```
## 提示

样例一说明：先使用能力爆发模式到行星 $1$，花费时间 $1$。

然后切换到高速航行模式，航行到行星 $2$，花费时间 $10$。

之后继续航行到行星 $3$ 完成比赛，花费时间 $1$。

虽然看起来从行星 $1$ 到行星 $3$ 再到行星 $2$ 更优，但我们却不能那样做，因为那会导致超能电驴爆炸。

【数据规模和约定】

对于 $30\%$ 的数据 $N\leq 20$，$M\leq 50$；

对于 $70\%$ 的数据 $N\leq 200$，$M\leq 4\times 10^3$；

对于 $100\%$ 的数据 $N\leq 800$，$M\leq 1.5\times 10^4$。

输入数据中的任何数都不会超过 $10^6$。

输入数据保证任意两颗行星之间至多存在一条航道，且不会存在某颗行星到自己的航道。



---

---
title: "[SDOI2011] 工作安排"
layout: "post"
diff: 省选/NOI-
pid: P2488
tag: ['2011', '各省省选', '山东', '费用流']
---
# [SDOI2011] 工作安排
## 题目描述


你的公司接到了一批订单。订单要求你的公司提供 $n$ 类产品，产品被编号为 $1 \sim n$，其中第 $i$ 类产品共需要 $C_i$ 件。公司共有 $m$ 名员工，员工被编号为 $1 \sim m$ 员工能够制造的产品种类有所区别。一件产品必须完整地由一名员工制造，不可以由某名员工制造一部分配件后，再转交给另外一名员工继续进行制造。

我们用一个由 $0$ 和 $1$ 组成的 $m \times n$ 的矩阵 $A$ 来描述每名员工能够制造哪些产品。矩阵的行和列分别被编号为 $1 \sim m$ 和 $1 \sim n$，$A_i,j$ 为 $1$ 表示员工 $i$ 能够制造产品 $j$，为 $0$ 表示员工 $i$ 不能制造产品 $j$。

如果公司分配了过多工作给一名员工，这名员工会变得不高兴。我们用愤怒值来描述某名员工的心情状态。愤怒值越高，表示这名员工心情越不爽，愤怒值越低，表示这名员工心情越愉快。员工的愤怒值与他被安排制造的产品数量存在某函数关系，鉴于员工们的承受能力不同，不同员工之间的函数关系也是有所区别的。

对于员工 $i$，他的愤怒值与产品数量之间的函数是一个 $S_i+1$ 段的分段函数。当他制造第 $1 \sim T_{i,1}$ 件产品时，每件产品会使他的愤怒值增加 $W_{i,1}$，当他制造第 $T_{i,1}+1 \sim T_{i,2}$ 件产品时，每件产品会使他的愤怒值增加 $W_{i,2}$ ……为描述方便，设 $T_{i,0}=0,T_{i,s_{i+1}}=+\infty$，那么当他制造第 $T_{i,j-1}+1 \sim T_{i,j}$ 件产品时，每件产品会使他的愤怒值增加 $W_{i,j}$，$1 \le j \le S_i+1$。

你的任务是制定出一个产品的分配方案，使得订单条件被满足，并且所有员工的愤怒值之和最小。由于我们并不想使用Special Judge，也为了使选手有更多的时间研究其他两道题目，你只需要输出最小的愤怒值之和就可以了。

## 输入格式

https://cdn.luogu.com.cn/upload/pic/1608.png

第一行包含两个正整数 $m$ 和 $n$，分别表示员工数量和产品的种类数；

第二行包含 $n$ 个正整数，第 $i$ 个正整数为 $C_i$；

以下 $m$ 行每行 $n$ 个整数描述矩阵 $A$；

下面 $m$ 个部分，第 $i$ 部分描述员工 $i$ 的愤怒值与产品数量的函数关系。每一部分由三行组成：第一行为一个非负整数 $S_i$，第二行包含 $S_i$ 个正整数，其中第 $j$ 个正整数为 $T_{i,j}$，如果 $S_i=0$ 那么输入将不会留空行（即这一部分只由两行组成）。第三行包含 $S_i+1$ 个正整数，其中第 $j$ 个正整数为 $W_{i,j}$。

## 输出格式

仅输出一个整数，表示最小的愤怒值之和。

## 样例

### 样例输入 #1
```
2 3

2 2 2

1 1 0

0 0 1

1

2

1 10

1

2

1 6
```
### 样例输出 #1
```
24
```
## 提示


### 数据范围及约定

- 存在 $30\%$ 的数据，保证 $1\le n,m\le 30$；
- 均匀分布着约 $30\%$ 的数据，满足 $S_i = 0$；
- 均匀分布着约 $30\%$ 的数据，满足 $S_i \le 1$（不包含上述 $S_i = 0$ 的数据）。

对于全部数据，满足 $1\le m,n\le 250$，$0\le S_i\le 5$，$0\le A_{i, j}\le 1$，$0< T_{i, j}< T_{i, j + 1}$，$0< W_{i,j} < W_{i, j + 1}$。所有数据均不大于 $10^5$。


---

---
title: "[HAOI2010] 订货"
layout: "post"
diff: 省选/NOI-
pid: P2517
tag: ['动态规划 DP', '2010', '河南', '各省省选', '费用流']
---
# [HAOI2010] 订货
## 题目描述

某公司估计市场在第 $i$ 个月对某产品的需求量为 $U_i$，已知在第 $i$ 月该产品的订货单价为 $d_i$，上个月月底未销完的单位产品要付存贮费用 $m$，假定第一月月初的库存量为 $0$，第 $n$ 月月底的库存量也为 $0$，问如何安排这 $n$ 个月订购计划，才能使成本最低？每月月初订购，订购后产品立即到货，进库并供应市场，于当月被售掉则不必付存贮费。假设仓库容量为 $S$。
## 输入格式

第 $1$ 行：$n, m, S \ (0\le n\le50, 0\le m\le10, 0\le S\le10000)$。

第 $2$ 行：$U_1 , U_2 , \cdots , U_n \ (0\le U_i\le10000)$。

第 $3$ 行：$d_1, d_2, \cdots ,d_n \ (0\le d_i\le100)$。
## 输出格式

只有 $1$ 行，一个整数，代表最低成本。
## 样例

### 样例输入 #1
```
3 1 1000

2 4 8

1 2 4 
```
### 样例输出 #1
```
34
```


---

---
title: "[ZJOI2010] 网络扩容"
layout: "post"
diff: 省选/NOI-
pid: P2604
tag: ['2010', '各省省选', '网络流', '浙江', '图论建模', '费用流']
---
# [ZJOI2010] 网络扩容
## 题目描述

给定一张有向图，每条边都有一个容量 $c$ 和一个扩容费用 $w$。这里扩容费用是指将容量扩大 $1$ 所需的费用。求： 

1. 在不扩容的情况下，$1$ 到 $n$ 的最大流；

2. 将 $1$ 到 $n$ 的最大流增加 $k$ 所需的最小扩容费用。
## 输入格式

第一行包含三个整数 $n,m,k$，表示有向图的点数、边数以及所需要增加的流量。

接下来的 $M$ 行每行包含四个整数 $u,v,c,w$，表示一条从$u$ 到 $v$，容量为 $c$，扩容费用为 $w$ 的边。
## 输出格式

输出文件一行包含两个整数，分别表示问题 $1$ 和问题 $2$ 的答案。
## 样例

### 样例输入 #1
```
5 8 2
1 2 5 8
2 5 9 9
5 1 6 2
5 1 1 8
1 2 8 7
2 5 4 9
1 2 1 1
1 4 2 1
```
### 样例输出 #1
```
13 19

```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\le 100$。
- 对于 $100\%$ 的数据，保证 $1\le n\le 10^3$，$1\le m\le 5\times 10^3$，$1\le k\le 10$，$1 \leq u, v \leq n$，$1\le c,w\le 100$。


---

---
title: "[USACO10HOL] Cow War G"
layout: "post"
diff: 省选/NOI-
pid: P2974
tag: ['2010', 'USACO', 'Special Judge', '费用流']
---
# [USACO10HOL] Cow War G
## 题目描述

Farmer John has long had a dispute with neighbor Farmer Tom over a group of V (1 <= V <= 1,000) pastures conveniently numbered 1..V. Both farmers currently graze their cows on the pastures; each pasture might be empty or might have a single cow which is owned by either Farmer John or Farmer Tom.

Farmer John's patience is at an end, and he wishes to settle the dispute with Farmer Tom by tipping over Tom's cows. Of course, he wants to strike first and to tip as many of Farmer Tom's cows as possible.

A total of E (1 <= E <= 5,000) bidirectional cowpaths connect pairs of pastures. No two pastures are connected by more than one cowpath; each path connects exactly two distinct pastures. Paths are described by their endpoints P1\_i and P2\_i (1 <= P1\_i <= V; 1 <= P2\_i <= V).

During his offense, each of Farmer John's cows can traverse a single cowpath if she wishes. Whether or not she chooses to traverse a cowpath, she can then (if she wishes) launch a cow tipping attack to a pasture connected to her pasture by a single cowpath, thus tipping the enemy cow on that pasture. Note that a cow can move and then attack -- but she is not able to attack and then move.

Each pasture can hold exactly one cow at a time; no cow can move to a pasture occupied by another cow, especially if it has been tipped. Of course, if a pasture is vacated, another cow can later move in to take its place. A tipped cow cannot be tipped again.

Farmer John wants to know two things:

\* How many of Farmer Tom's cows he can tip in the first salvo

of the war

\* How to command his cows to move and attack so as to tip

that maximal number of Farmer Tom's cows in that first salvo

Find the maximum number of cows that can be tipped and construct a sequence of move and attack commands to his cows that then obey the rules and tip that number of cows. Any such sequence is acceptable, as long as it tips the maximum number of Farmer Tom's cows.

Consider, for instance, a group of 5 pastures arranged in a line, with each pasture connected (via '--'; see diagram below) to its left and right neighbors (if they exist). In other words, there is a cowpath from Pasture 1 to Pasture 2, Pasture 2 to Pasture 3, etc. Farmer Tom ('T') has 2 cows, standing on pastures 1 and 4, while Farmer John ('J') has 2 cows standing on pastures 3 and 5 ('E' means empty):

1    2    3    4    5

T -- E -- J -- T -- J

In this case, Farmer John can tip both of Farmer Tom's cows by first moving his cow on Pasture 3 to Pasture 2, so that the pastures in order are now TJETJ. Farmer John can then have both of his cows attack to the left.  Note that although the cow in Pasture 3 could have attacked to the right without moving, the rightmost cow would then be unable to attack. The only valid solutions thus have the same move and attacks, although the order in which Farmer John commands his cows can vary slightly.

If you compute the correct maximum number but do not provide a sequence (or your sequence is wrong), you will get 50% of the points for that test case. A program will grade your output.

Partial feedback will be provided for your first 50 submissions.
## 输入格式

\* Line 1: Two space separated integers: V and E

\* Line 2: A string of V characters (no spaces); character #i indicates whether pasture #i is empty ('E') or has a cow owned by Farmer John ('J') or Farmer Tom ('T')

\* Lines 3..E+2: Line i+2 contains two space separated integers: P1\_i and P2\_i

## 输出格式

\* Line 1: A single integer, the maximum number of enemy cows Farmer John can have tipped

\* Lines 2.....: One of Farmer John's instructions to his cows (to be executed in the order given):

MOVE A B

or
ATTACK A B

where A is the vertex the cow occupies before taking the action and B is the vertex it is moving to or attacking, respectively. Note that when instructing a cow that has already moved to attack, the instruction specifies the location the cow is currently standing, not where it was originally.

## 样例

### 样例输入 #1
```
5 4 
TEJTJ 
1 2 
2 3 
3 4 
4 5 

```
### 样例输出 #1
```
2 
MOVE 3 2 
ATTACK 2 1 
ATTACK 5 4 

```
## 提示

The other valid outputs are:

2
MOVE 3 2

ATTACK 5 4

ATTACK 2 1

and
2
ATTACK 5 4

MOVE 3 2

ATTACK 2 1

which are just reorderings of the output shown.  This might not be true on other testdata.

## 题目翻译

### 题目描述

给定 $V$ 个点，$E$ 条边的无向图。
一开始每个点上有 `T` 牛，`J` 牛，或者没有（`E`）。
`J` 牛可以 `MOVE` 到一个相邻的点，也可以 `ATTACK` 相邻点上的一个 `T` 牛。不过操作有限制，只能按照 `MOVE`,`ATTACK` 或者 `MOVE` 然后 `ATTACK` 三种方式操作。
一个 `T` 牛仅能被 `ATTACK` 一次，被 `ATTACK` 后它会留在原地。
需要保证任意时刻，每个点上有且仅有一头牛。
求所有 `T` 牛被 `ATTACK` 的最大次数，并给出一个可行的操作方案。

### 输入格式

第一行两个整数 $V,E$，表示无向图的点数和边数。
接下来一行 $V$ 个字符，第 $i$ 个字符表示第 $i$ 个点的初始状态。
接下来 $E$ 行每行两个整数 $u,v$，表示存在一条连接 $u,v$ 的无向边。

### 输出格式

第一行一个整数，表示所有 `T` 牛被 `ATTACK` 的最大次数。
接下来若干行，每行以 `MOVE u v` 或 `ATTACK u v` 的形式给出，表示你的操作方案。

### 说明/提示

对于测试点 $1\sim5$，$1\leq V\leq 30,1\leq E\leq 50$。
对于测试点 $6\sim 10$，$1\leq V\leq 500,1\leq E\leq 2\times 10^3$。
对于测试点 $11\sim 15$，$1\leq V\leq 10^3,1\leq E\leq 5\times 10^3$。
注意：一个操作需要描述现在的位置，例如：点 $3$ 上的牛先 `MOVE` 到点 $2$，再 `ATTACK` 点 $4$，应该写为：

\```
MOVE 3 2
ATTACK 2 4
\```



---

---
title: "[CQOI2012] 交换棋子"
layout: "post"
diff: 省选/NOI-
pid: P3159
tag: ['2012', '重庆', '各省省选', '网络流', '费用流']
---
# [CQOI2012] 交换棋子
## 题目描述

有一个 $n$ 行 $m$ 列的黑白棋盘，你每次可以交换两个相邻格子（**相邻是指有公共边或公共顶点**）中的棋子，最终达到目标状态。要求第 $i$ 行第 $j$ 列的格子只能参与 $m_{i,j}$ 次交换。
## 输入格式

第一行包含两个整数 $n,m$。以下 $n$ 行为初始状态，每行为一个包含 $m$ 个字符的 $01$ 串，其中 $0$ 表示黑色棋子，$1$ 表示白色棋子。以下 $n$ 行为目标状态，格式同初始状态。以下 $n$ 行每行为一个包含 $m$ 个 $0\sim9$ 数字的字符串，表示每个格子参与交换的次数上限。

## 输出格式

输出仅一行，为最小交换总次数。如果无解，输出 $-1$。
## 样例

### 样例输入 #1
```
3 3
110
000
001
000
110
100
222
222
222
```
### 样例输出 #1
```
4
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，$1\leq n,m\leq20$。


---

---
title: "[SDOI2013] 刺客信条"
layout: "post"
diff: 省选/NOI-
pid: P3296
tag: ['动态规划 DP', '2013', '山东', '费用流', '哈希 hashing']
---
# [SDOI2013] 刺客信条
## 题目描述

故事发生在1486 年的意大利，Ezio 原本只是一个文艺复兴时期的贵族，后来因为家族成员受到圣殿骑士的杀害，决心成为一名刺客。最终，凭借着他的努力和出众的天赋，成为了杰出的刺客大师，他不仅是个身手敏捷的武林高手，飞檐走壁擅长各种暗杀术。刺客组织在他的带领下，为被剥削的平民声张正义，赶跑了原本统治意大利的圣殿骑士首领-教皇亚历山大六世。在他的一生中，经历了无数次惊心动魄、扣人心弦的探险和刺杀。


曾经有一次，为了寻找Altair 留下的线索和装备，Ezio 在佛罗伦萨中的刺客墓穴进行探索。这个刺客墓穴中有许多密室，且任何两个密室之间只存在一条唯一的路径。这些密室里都有一个刺客标记，他可以启动或者关闭该刺客标记。为了打开储存着线索和装备的储藏室，Ezio 必须操作刺客标记来揭开古老的封印。要想解开这个封印，他需要通过改变某些刺客标记的启动情况，使得所有刺客标记与封印密码“看起来一样”。


在这里，“看起来一样”的定义是：存在一种“标记”密室与“密码”密室之间一一对应的关系，使得密室间的连接情况和启动情况相同（提示中有更详细解释）。幸运的是，在Ezio 来到刺客墓穴之前，在Da Vinci 的帮助下，Ezio 已经得知了打开储藏室所需要的密码。


而你的任务则是帮助Ezio 找出达成目标所需要最少的改动标记次数。

## 输入格式

第一行给出一个整数n, 表示密室的个数,


第二行至第 n 行, 每行绐出两个整数 a 和 b, 表示第 a 个密室和第 b 个密室之间存在一条通道.


第 n+1行1 绐出 n 个整数1 分别表示当时每个密室的启动情况 {0表示关闭, 1表示启动).


第 n+2 行7 给出 n 个整数, 分别表示密码中每个密室的启动情况.

## 输出格式

输出只有一行，即输出最少改动标记次数

## 样例

### 样例输入 #1
```
4
1 2
2 3
3 4
0 0 1 1
1 0 0 0
```
### 样例输出 #1
```
1
```
## 提示

密室的编号是可以变的！将第三个密室关闭后，在当前标记和密码之间，存在1->4,2->3,3->2,4->1 的对应关系，重新编号后连接情况没有改变，且标记与密码对应。对于更一般的情况，存在一个1 到n 的置换P，使得对于任意密室之间的道路u-v，都一定有密码密室中的道路P(u)-P(v)；如果不存在密室之间的道路u-v，则一定没有密码密室中的道路P(u)-P(v)。


对于100%的数据，n<=700，且每个密室至多与11个密室相通



---

---
title: "[POI 2011] PRO-Programming Contest"
layout: "post"
diff: 省选/NOI-
pid: P3529
tag: ['2011', 'POI（波兰）', 'Special Judge', '费用流']
---
# [POI 2011] PRO-Programming Contest
## 题目描述

Bartie and his friends compete in the Team Programming Contest.

There are $n$ contestants on each team, and each team has access to $n$ computers.

The contest lasts $t$ minutes, during which the contestants are to solve $m$ programming problems.

Furthermore, penalties are imposed on the teams: solving a problem $s$ minutes since the beginning of the contest amounts to $s$ penal points.

The team that solved the most problems wins the contest, with ties broken in    favour of the team with smaller penalty.

On the contest day Bartie quickly glances over the problem statements and    distributes them among his teammates.

He knows his team so well that he can exactly assess who is able to solve    which problem.

Solving any problem takes any contestant that is able to solve it exactly $r$ minutes of using the computer.

Bartie's team did not fare well in this year's contest.

Bartie is obsessed with the thought that it might be his fault, due to wrong    decisions regarding the distribution of problems.

He asks you to write a program that, given what Bartie knew at the beginning    of the contest, determines the best possible result of Bytie's team, together    with the assignment of problems to team members that attains the result.

## 输入格式

Five integers $n$, $m$, $r$, $t$, and $k$ ($1\le n,m\le 500$, $1\le r,t\le 1\ 000\ 000$) are given in the first line of the standard input, separated by single spaces.

These denote, respectively:

the number of contestants on a team, the number of problems, the time it      takes a contestant to solve a problem, the duration of the contest,and the number of contestant-problem pairs given on the input.

Each of the following $k$ lines holds two integers $a$ and $b$($1\le a\le n$,$1\le b\le m$), separated by a single space, denoting that the contestant $a$ is able to solve the problem $b$.Each such pair appears at most once in the input.

In tests worth at least 30% of the points it additionally holds that $n,m\le 100$.

## 输出格式

In the first line of the standard output the best possible result of Bytie's      team should be printed as two numbers separated by a single space:

the number of solved problems $z$ and the total penal points.

An exemplary assignment of problems that attains this result should be given in the following $z$ lines.

Each of those should hold three integers $a$, $b$ and $c$ ($1\le a\le n$,$1\le b\le m$, $0\le c\le t-r$),separated by single spaces, signifying that the contestant $a$ should start solving the problem $b$ at time $c$(the contest starts at time $0$).No contestant should be assigned a problem that they cannot solve. If more that one optimal assignment exists, your program can output any of them.

## 样例

### 样例输入 #1
```
2 4 3 15 4
1 1
2 3
1 4
1 3
```
### 样例输出 #1
```
3 12
1 4 0
2 3 0
1 1 3
```
## 题目翻译

### 题目描述
**译自 POI 2011 Round 3. Day 2. C「[Programming Contest](https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement)」**

Bartie 和他的朋友们都在打团体程序设计竞赛。每个队有 $n$ 名队员，每个队可以用 $n$ 台电脑。比赛持续 $t$ 分钟，比赛中选手们要解决 $m$ 道程序设计题目。此外，比赛会按如下规则记罚时：比赛开始 $s$ 分钟通过了一道题，则罚时加 $s$ 分。解题数目最多的队伍获胜，如果解题数目相同，罚时最少的队伍获胜。

在一次比赛中，Bartie 迅速浏览了全部题目并且把题目分配给了队友。他十分了解队友，并可以把题目分配给能解决这道题的人。对于每个选手，解决一道题的时间都恰好是 $r$ 分钟。

Bartie 的队伍在今年的比赛中表现不佳。Bartie 确信这是他的问题，是由于他分配问题失误造成的。他想让你写个程序，给出 Bartie 在比赛前知道的信息，请求出 Bartie 的队伍可能的最好成绩和分配题目的方式。

### 输入格式

第一行五个整数 $n,m,r,t,k$，分别表示一个队中的队员数，题目数，队员解决一道题的用时，比赛的时间长度和队员-题目对数；

接下来 $k$ 行，每行两个数 $a,b$，表示队员 $a$ 可以解决问题 $b$。每一个有序对在输入中最多出现一次。

### 输出格式

第一行输出两个整数，用一个空格隔开，分别表示解出的题目总数 $z$ 和最少总罚时。

接下来 $z$ 行，每行输出三个整数 $a,b,c\ (1 \le a \le n , 1 \le b \le m , 0 \le c \le t-r)$，表示队员 $a$ 在时刻 $c$ 时开始解决题目 $b$（比赛开始于时刻 $0$）。你不能把一道题分配给不会解决它的人。如果有多种分配方案，输出任意一组均可。

### 数据范围

对于全部数据，$ 1 \le n, m \le 500 , 1 \le r, t \le 1000000, 1 \le a \le n , 1 \le b \le m $

对于 $30\%$ 的分数，$n,m\le 100$。

翻译来自于 [LibreOJ](https://loj.ac/p/2171)。


---

---
title: "[SDOI2017] 新生舞会"
layout: "post"
diff: 省选/NOI-
pid: P3705
tag: ['2017', '二分', '各省省选', '山东', 'O2优化', '分数规划', '费用流']
---
# [SDOI2017] 新生舞会
## 题目描述

学校组织了一次新生舞会，Cathy 作为经验丰富的老学姐，负责为同学们安排舞伴。


有 $n$ 个男生和 $n$ 个女生参加舞会，一个男生和一个女生一起跳舞，互为舞伴。


Cathy 收集了这些同学之间的关系，比如两个人之前认识没，计算得出 $a_{i,j}$。

Cathy 还需要考虑两个人一起跳舞是否方便，比如身高体重差别会不会太大，计算得出 $b_{i,j}$，表示第 $i$ 个男生和第 $j$ 个女生一起跳舞时的不协调程度。


当然，还需要考虑很多其他问题。


Cathy 想先用一个程序通过 $a_{i,j}$ 和 $b_{i,j}$ 求出一种方案，再手动对方案进行微调。

Cathy 找到你，希望你帮她写那个程序。


一个方案中有 n 对舞伴，假设每对舞伴的喜悦程度分别是 $a'_1,a'_2,...,a'_n$，假设每对舞伴的不协调程度分别是 $b'_1,b'_2,...,b'_n$。令

$C=\frac {a'_1+a'_2+...+a'_n}{b'_1+b'_2+...+b'_n}$

Cathy 希望 $C$ 值最大。

## 输入格式

第一行一个整数 $n$。


接下来 $n$ 行，每行 $n$ 个整数，第 $i$ 行第 $j$ 个数表示 $a_{i,j}$。


接下来 $n$ 行，每行 $n$ 个整数，第 $i$ 行第 $j$ 个数表示 $b_{i,j}$。

## 输出格式

一行一个数，表示 $C$ 的最大值。四舍五入保留 $6$ 位小数，选手输出的小数需要与标准输出相等。

## 样例

### 样例输入 #1
```
3
19 17 16
25 24 23
35 36 31
9 5 6
3 4 2
7 8 9
```
### 样例输出 #1
```
5.357143
```
## 提示

对于 10% 的数据，$1\le n\le 5$

对于 40% 的数据，$1\le n\le 18$

另有 20% 的数据，$b_{i,j}\le 1$

对于 100% 的数据，$1\le n\le 100,1\le a_{i,j},b_{i,j}\le10^4$



---

---
title: "[TJOI2013] 循环格"
layout: "post"
diff: 省选/NOI-
pid: P3965
tag: ['2013', '各省省选', '图论建模', '费用流', '天津']
---
# [TJOI2013] 循环格
## 题目背景

一个循环格就是一个矩阵,其中所有元素为箭头,指向相邻四个格子。每个元素有一个坐标(行,列),其中左上角元素坐标为(0,0)。给定一个起始位(r,c),你可以沿着箭头方向在格子间行走。即:如果(r,c)是一个左箭头，那么走到(r,c-1);如果是一个右箭头,走到(r,c+1);如果是上箭头,走到(r-1,c);如果是下箭头,走到(r+1,c)。每一行和每一列都是循环的,即如果走出边界,你会出现在另一侧。比如在一个5\*5的循环格里,从(3,0)向左走会出现在(3,4)。

## 题目描述

一个完美的循环格是这样定义的:对于任意一个起始位置,你都可以沿着箭头最终回到起始位置。如果一个循环格不满足完美,你可以随意修改任意一个元素的箭头直到完美。例如下图,左边不是一个完美的循环格,因为只有从(1,1),(1,2),(2,0),(2,3)出发才会回到起始位置。通过修改其中两个箭头,可以得到右图,一个完美的循环格。

 ![](https://cdn.luogu.com.cn/upload/pic/10987.png) 

给定一个循环格,你需要计算最少需要修改多少个元素使其完美。

## 输入格式

第一行两个整数R和C,表示循环格的行和列。接下来R行,每一行包含C个字符LRUD表示左右上下

## 输出格式

一个整数,表示最少需要修改多少个元素使得给定的循环格完美。

## 样例

### 样例输入 #1
```
4 4
RRRD
URDD
UULD
ULLL
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
3 4
RRRD
URLL
LRRR
```
### 样例输出 #2
```
2
```
## 提示

### 数据范围

30%的数据，1 ≤ R, C ≤ 7

100%的数据，1 ≤ R, C ≤ 15



---

---
title: "[TJOI2014] 匹配"
layout: "post"
diff: 省选/NOI-
pid: P3967
tag: ['2014', '各省省选', '枚举', '二分图', '费用流', '天津']
---
# [TJOI2014] 匹配
## 题目描述

有 $N$ 个单身的男孩和 $N$ 个单身女孩，男孩 $i$ 和女孩 $j$ 在一起得到的幸福值为 $H_{i,j}$。

一个匹配即对这 $N$ 个男孩女孩的安排：每个男孩恰好有一个女朋友，每个女孩恰好有一个男朋友。

一个匹配的幸福值即这 $N$ 对男女朋友的幸福值的和。

经典的问题是计算幸福值最大的匹配，即完美匹配。然而完美匹配有时候并不唯一，你需要计算对于所有的完美匹配，其交集是什么。
## 输入格式

输入的第一行是一个正整数 $N$ 。

接下来是一个 $N\times N$ 大小的矩阵 $H$，$H_{i,j}$ 表示男孩 $i$ 和女孩 $j$ 在一起的幸福值。
## 输出格式

第一行输出完美匹配的幸福值，接下来是若干行，每一行是一对整数 $i$ 和 $j$，表示男孩 $i$ 和女孩 $j$ 在所有完美匹配的交集中，以 $i$ 的递增顺序输出。
## 样例

### 样例输入 #1
```
3
1 1 1
2 1 1
1 1 1
```
### 样例输出 #1
```
4
2 1
```
## 提示

- 对于 $30\%$ 的数据，$N \leq 30$；
- 对于 $100\%$ 的数据，$1\leq N \leq 80$，$0\leq H_{i,j}\leq 5\times10^3$。


---

---
title: "汽车加油行驶问题"
layout: "post"
diff: 省选/NOI-
pid: P4009
tag: ['图论', '网络流', 'O2优化', '最短路', '费用流', '网络流与线性规划 24 题']
---
# 汽车加油行驶问题
## 题目描述

给定一个 $N \times N$ 的方形网格，设其左上角为起点◎，坐标$(1,1)$，$X$ 轴向右为正， $Y$ 轴向下为正，每个方格边长为 $1$ ，如图所示。



 ![](https://cdn.luogu.com.cn/upload/pic/12156.png) 

一辆汽车从起点◎出发驶向右下角终点▲，其坐标为 $(N,N)$。


在若干个网格交叉点处，设置了油库，可供汽车在行驶途中加油。汽车在行驶过程中应遵守如下规则:


1. 汽车只能沿网格边行驶，装满油后能行驶 $K$ 条网格边。出发时汽车已装满油，在起点与终点处不设油库。

1. 汽车经过一条网格边时，若其 $X$ 坐标或 $Y$ 坐标减小，则应付费用 $B$ ，否则免付费用。

1. 汽车在行驶过程中遇油库则应加满油并付加油费用 $A$。

1. 在需要时可在网格点处增设油库，并付增设油库费用 $C$(不含加油费用$A$ )。

1. $N,K,A,B,C$ 均为正整数， 且满足约束: $2\leq N\leq 100,2 \leq K \leq 10$。


设计一个算法，求出汽车从起点出发到达终点所付的最小费用。

## 输入格式

文件的第一行是 $N,K,A,B,C$ 的值。


第二行起是一个$N\times N$ 的 $0-1$ 方阵,每行 $N$ 个值,至 $N+1$ 行结束。


方阵的第 $i$ 行第 $j$ 列处的值为 $1$ 表示在网格交叉点 $(i,j)$ 处设置了一个油库,为 $0$ 时表示未设油库。各行相邻两个数以空格分隔。

## 输出格式

程序运行结束时,输出最小费用。

## 样例

### 样例输入 #1
```
9 3 2 3 6
0 0 0 0 1 0 0 0 0
0 0 0 1 0 1 1 0 0
1 0 1 0 0 0 0 1 0
0 0 0 0 0 1 0 0 1
1 0 0 1 0 0 1 0 0
0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 1
1 0 0 1 0 0 0 1 0
0 1 0 0 0 0 0 0 0
```
### 样例输出 #1
```
12
```
## 提示

$2 \leq n \leq 100,2 \leq k \leq 10$



---

---
title: "深海机器人问题"
layout: "post"
diff: 省选/NOI-
pid: P4012
tag: ['图论建模', '费用流', '网络流与线性规划 24 题']
---
# 深海机器人问题
## 题目描述

深海资源考察探险队的潜艇将到达深海的海底进行科学考察。


潜艇内有多个深海机器人。潜艇到达深海海底后，深海机器人将离开潜艇向预定目标移动。


深海机器人在移动中还必须沿途采集海底生物标本。沿途生物标本由最先遇到它的深海机器人完成采集。


每条预定路径上的生物标本的价值是已知的，而且生物标本只能被采集一次。


本题限定深海机器人只能从其出发位置沿着向北或向东的方向移动，而且多个深海机器人可以在同一时间占据同一位置。


用一个 $P\times Q$ 网格表示深海机器人的可移动位置。西南角的坐标为 $(0,0)$，东北角的坐标为 $(Q,P)$ 。



 ![](https://cdn.luogu.com.cn/upload/pic/12215.png) 

给定每个深海机器人的出发位置和目标位置，以及每条网格边上生物标本的价值。


计算深海机器人的最优移动方案， 使深海机器人到达目的地后，采集到的生物标本的总价值最高。


## 输入格式

文件的第 $1$ 行为深海机器人的出发位置数 $a$,和目的地数 $b$ 。


第 $2$ 行为 $P$ 和 $Q$ 的值。


接下来的 $P+1$ 行,每行有 $Q$ 个正整数,表示向东移动路径上生物标本的价值,行数据依从南到北方向排列。


再接下来的 $Q+1$ 行,每行有 $P$ 个正整数,表示向北移动路径上生物标本的价值,行数据依从西到东方向排列。


接下来的 $a$ 行，每行有三个正整数 $k,x,y$,表示有 $k$ 个深海机器人从 $(y,x)$ 位置坐标出发。


再接下来的 $b$ 行，每行有三个正整数 $r,x,y$ ,表示有 $r$ 个深海机器人可选择 $(y,x)$ 位置坐标作为目的地。

## 输出格式

输出采集到的生物标本的最高总价值.

## 样例

### 样例输入 #1
```
1 1
2 2
1 2
3 4
5 6
7 2
8 10
9 3
2 0 0
2 2 2
```
### 样例输出 #1
```
42
```
## 提示

$1\leq P,Q\leq15$


$1\leq a\leq 4$


$1\leq b\leq 6$



---

---
title: "数字梯形问题"
layout: "post"
diff: 省选/NOI-
pid: P4013
tag: ['O2优化', '图论建模', '费用流', '网络流与线性规划 24 题']
---
# 数字梯形问题
## 题目描述

给定一个由 $n$ 行数字组成的数字梯形如下图所示。



 ![](https://cdn.luogu.com.cn/upload/pic/12216.png) 

梯形的第一行有 $m$ 个数字。从梯形的顶部的 $m$ 个数字开始，在每个数字处可以沿左下或右下方向移动，形成一条从梯形的顶至底的路径。


分别遵守以下规则：


1. 从梯形的顶至底的 $m$ 条路径互不相交；

1. 从梯形的顶至底的 $m$ 条路径仅在数字结点处相交；

1. 从梯形的顶至底的 $m$  条路径允许在数字结点相交或边相交。

## 输入格式

第 $1$ 行中有 $2$ 个正整数 $m$ 和 $n$，分别表示数字梯形的第一行有 $m$ 个数字，共有 $n$ 行。接下来的 $n$ 行是数字梯形中各行的数字。

第 $1$ 行有 $m$ 个数字，第 $2$ 行有 $m+1$ 个数字，以此类推。

## 输出格式

将按照规则 $1$，规则 $2$，和规则 $3$ 计算出的最大数字总和并输出，每行一个最大总和。

## 样例

### 样例输入 #1
```
2 5
2 3
3 4 5
9 10 9 1
1 1 10 1 1
1 1 10 12 1 1
```
### 样例输出 #1
```
66
75
77
```
## 提示

$1\leq m,n \leq 20$



---

---
title: "[AHOI2014/JSOI2014] 支线剧情"
layout: "post"
diff: 省选/NOI-
pid: P4043
tag: ['2014', '各省省选', '网络流', '江苏', '安徽', '上下界网络流', '费用流']
---
# [AHOI2014/JSOI2014] 支线剧情
## 题目背景

宅男 JYY 非常喜欢玩 RPG 游戏，比如仙剑，轩辕剑等等。不过 JYY 喜欢的并不是战斗场景，而是类似电视剧一般的充满恩怨情仇的剧情。这些游戏往往都有很多的支线剧情，现在 JYY 想花费最少的时间看完所有的支线剧情。
## 题目描述

JYY 现在所玩的 RPG 游戏中，一共有 $N$ 个剧情点，由 $1$ 到 $N$ 编号，第 $i$ 个剧情点可以根据 JYY 的不同的选择，而经过不同的支线剧情，前往 $K_i$ 种不同的新的剧情点。当然如果为 $0$，则说明 $i$ 号剧情点是游戏的一个结局了。

JYY 观看一个支线剧情需要一定的时间。JYY 一开始处在 $1$ 号剧情点，也就是游戏的开始。显然任何一个剧情点都是从 $1$ 号剧情点可达的。此外，随着游戏的进行，剧情是不可逆的。所以游戏保证从任意剧情点出发，都不能再回到这个剧情点。由于 JYY 过度使用修改器，导致游戏的“存档”和“读档”功能损坏了，

所以 JYY 要想回到之前的剧情点，唯一的方法就是退出当前游戏，并开始新的游戏，也就是回到 $1$ 号剧情点。JYY 可以在任何时刻退出游戏并重新开始。不断开始新的游戏重复观看已经看过的剧情是很痛苦，JYY 希望花费最少的时间，看完所有不同的支线剧情。
## 输入格式

输入一行包含一个正整数 $N$。

接下来 $N$ 行，第 $i$ 行为 $i$ 号剧情点的信息；

第一个整数为 $K_i$，接下来 $K_i$ 个整数对，$b_{i,j}$ 和 $t_{i,j}$，表示从剧情点 $i$ 可以前往剧情点 $b_{i,j}$，并且观看这段支线剧情需要花费 $t_{i,j}$ 的时间。
## 输出格式

输出一行包含一个整数，表示 JYY 看完所有支线剧情所需要的最少时间。
## 样例

### 样例输入 #1
```
6
2 2 1 3 2
2 4 3 5 4
2 5 5 6 6
0
0
0
```
### 样例输出 #1
```
24
```
## 提示

### 样例解释

JYY 需要重新开始 $3$ 次游戏，加上一开始的一次游戏，$4$ 次游戏的进程是：

- $1 \to 2 \to 4$；
- $1 \to 2 \to 5$；
- $1 \to 3 \to 5$；
- $1 \to 3 \to 6$。

对于 $100\%$ 的数据满足 $N \le 300$，$0 \le K_i \le 50$，$1 \le T_{i,j} \le 300$，$\sum K_i \le 5000$。


---

---
title: "[BJOI2012] 连连看"
layout: "post"
diff: 省选/NOI-
pid: P4134
tag: ['2012', '各省省选', '北京', '二分图', '费用流']
---
# [BJOI2012] 连连看
## 题目描述

凡是考智商的题里面总会有这么一种消除游戏。不过现在面对的这关连连看可不是 QQ 游戏里那种考眼力的游戏。我们的规则是，给出一个闭区间 $[a,b]$ 中的全部整数，如果其中某两个数 $x$，$y$（$x>y$）的平方差 $x^2-y^2$ 是一个完全平方数 $z^2$，并且 $y$ 与 $z$ 互质，那么就可以将 $x$ 和 $y$ 连起来并且将它们一起消除，同时得到 $x+y$ 点分数。那么过关的要求就是，消除的数对尽可能多的前提下，得到足够的分数。快动手动笔算一算吧。
## 输入格式

只有一行，两个整数，分别表示 $a$，$b$。
## 输出格式

两个数，可以消去的对数，及在此基础上能得到的最大分数。

## 样例

### 样例输入 #1
```
1 15
```
### 样例输出 #1
```
2 34
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $1\le a,b\le100$。
- 对于 $100\%$ 的数据，保证 $1\le a,b\le1000$。


---

---
title: "[JSOI2009] 球队收益 / 球队预算"
layout: "post"
diff: 省选/NOI-
pid: P4307
tag: ['2009', '各省省选', '江苏', '图论建模', '费用流']
---
# [JSOI2009] 球队收益 / 球队预算
## 题目描述

在一个篮球联赛里，有$n$支球队，球队的支出是和他们的胜负场次有关系的，具体来说，第i支球队的赛季总支出是$C_i\times x^2+D_i \times y^2,D_i \le C_i$。(赢得多，给球员的奖金就多嘛)
其中$x,y$分别表示这只球队本赛季的胜负场次。现在赛季进行到了一半，每只球队分别取得了$a_i$场胜利和$b_i$场失利。而接下来还有$m$场比赛要进行。问联盟球队的最小总支出是多少。
## 输入格式

第一行$n$，$m$

接下来$n$行每行$4$个整数$a_i,b_i,C_i,D_i$

再接下来$m$行每行两个整数$s$，$t$表示第$s$支队伍和第$t$支队伍之间将有一场比赛，注意两只队间可能有多场比赛。
## 输出格式

一个整数代表总支出的最小值。
## 样例

### 样例输入 #1
```
3 3
1 0 2 1
1 1 10 1
0 1 3 3
1 2
2 3
3 1
```
### 样例输出 #1
```
43
```
## 提示

对于20%的数据$2 \le n \le 10,0 \le m \le 20$；  
对于100%的数据$2 \le n \le 5000,0 \le m \le 1000,0 \le D_i \le C_i \le 10,0 \le a_i,b_i \le 50$。


---

---
title: "士兵占领"
layout: "post"
diff: 省选/NOI-
pid: P4311
tag: ['网络流', '费用流']
---
# 士兵占领
## 题目描述

有一个 $M \times N$ 的棋盘，有的格子是障碍。现在你要选择一些格子来放置一些士兵，一个格子里最多可以放置一个士兵，障碍格里不能放置士兵。我们称这些士兵占领了整个棋盘当满足第 $i$ 行至少放置了 $L_i$ 个士兵，第 $j$ 列至少放置了 $C_j$ 个士兵。现在你的任务是要求使用最少个数的士兵来占领整个棋盘。
## 输入格式

第一行两个数 $M, N, K$ 分别表示棋盘的行数，列数以及障碍的个数。  
第二行有 $M$ 个数表示 $L_i$。  
第三行有 $N$ 个数表示 $C_i$。  
接下来有 $K$ 行，每行两个数 $X, Y$ 表示 $(X, Y)$ 这个格子是障碍。
## 输出格式

输出一个数表示最少需要使用的士兵个数。如果无论放置多少个士兵都没有办法占领整个棋盘，输出”JIONG!” (不含引号)
## 样例

### 样例输入 #1
```
4 4 4
1 1 1 1
0 1 0 3
1 4
2 2
3 3
4 3

```
### 样例输出 #1
```
4
```
## 提示

对于 $100 \%$ 的数据，$1 \le M, N \le 100$，$0 \le K \le M \cdot N$。


---

---
title: "[国家集训队] 航班安排"
layout: "post"
diff: 省选/NOI-
pid: P4452
tag: ['2012', '集训队互测', '网络流', '费用流']
---
# [国家集训队] 航班安排
## 题目背景

1. wqs 爱好模拟飞行。
2. clj 开了一家神犇航空，由于 clj 还要玩游戏，所以公司的事务由你来打理。

注意：题目中只是用了这样一个背景，并不与真实 / 模拟飞行相符。
## 题目描述

神犇航空有 $K$ 架飞机，为了简化问题，我们认为每架飞机都是相同的。神犇航空的世界中有 $N$ 个机场，以 $0\cdots N-1$ 编号，其中 $0$ 号为基地机场，每天 $0$ 时刻起飞机才可以从该机场起飞，并不晚于 $T$ 时刻回到该机场。

一天，神犇航空接到了 $M$ 个包机请求，每个请求为在 $s$ 时刻从 $a$ 机场起飞，在恰好 $t$ 时刻到达 $b$ 机场，可以净获利 $c$。换言之，你只需要在 $s$ 时刻在 $a$ 机场选择提供一架飞机给请求方，那么这架飞机就会在 $t$ 时刻准时出现在 $b$ 机场，并且你将获得 $c$ 的净利润。

设计一种方案，使得总收益最大。
## 输入格式

第一行，$4$ 个正整数 $N,M,K,T$，如题目描述中所述；

以下 $N$ 行，每行 $N$ 个整数，描述一个 $N\times N$ 的矩阵 $t$，$t_{i,j}$ 表示从机场 $i$ 空载飞至机场 $j$，需要时间 $t_{i,j}$；

以下 $N$ 行，每行 $N$ 个整数，描述一个 $N\times N$ 的矩阵 $f$，$f_{i,j}$ 表示从机场 $i$ 空载飞至机场 $j$，需要费用 $f_{i,j}$；

以下 $M$ 行，每行 $5$ 个整数描述一个请求，依次为 $a,b,s,t,c$。
## 输出格式

　　仅一行，一个整数，表示最大收益。
## 样例

### 样例输入 #1
```
2 1 1 10
0 5
5 0
0 5
5 0
0 1 0 5 10
```
### 样例输出 #1
```
5
```
## 提示

对于 $10\%$ 的测试数据，$K=1$；

另有 $20\%$ 的测试数据，$K=2$；

对于全部的测试数据，$1\le N,M\le 200$，$1\le K\le 10$，$1\le T\le 3000$，$1\le t_{i,j}\le 200$，$f_{i,j}\le 2\times 10^3$，$0\le a,b<N$，$0\le s\le t\le T$，$0\le c\le 10000$，$t_{i,i}=f_{i,i}=0$，$t_{ij}\le t_{i,k}+t_{k,j}$，$f_{i,j}\le f_{i,k}+f_{k,j}$。


---

---
title: "80人环游世界"
layout: "post"
diff: 省选/NOI-
pid: P4553
tag: ['费用流']
---
# 80人环游世界
## 题目描述

想必大家都看过成龙大哥的《80天环游世界》，里面的紧张刺激的打斗场面一定给你留下了深刻的印象。现在就有这么一个80人的团伙，也想来一次环游世界。
  
他们打算兵分多路，游遍每一个国家。  

因为他们主要分布在东方，所以他们只朝西方进军。设从东方到西方的每一个国家的编号依次为$1 \cdots N$。假若第$i$个人的游历路线为$P_1,P_2,\cdots ,P_k(0≤k≤N)$，则$P_1<P_2<......<P_k$。  

众所周知，中国相当美丽，这样在环游世界时就有很多人经过中国。我们用一个正整数 $V_i$ 来描述一个国家的吸引程度，$V_i$值越大表示该国家越有吸引力，同时也表示有且仅有$V_i$个人会经过那一个国家。 
 
为了节省时间，他们打算通过坐飞机来完成环游世界的任务。同时为了省钱，他们希望总的机票费最小。
  
明天就要出发了，可是有些人临阵脱逃，最终只剩下了$M$个人去环游世界。他们想知道最少的总费用，你能告诉他们吗？  
## 输入格式

第一行两个正整数$N,M$。  

第二行有$N$个不大于$M$正整数，分别表示$V_1,V_2,\cdots, V_N$。 
 
接下来有$N-1$行。第$i$行有$N-i$个整数，该行的第$j$个数表示从第$i$个国家到第$i+j$个国家的机票费（如果该值等于$-1$则表示这两个国家间没有通航）。
## 输出格式

在第一行输出最少的总费用。
## 样例

### 样例输入 #1
```
6 3
2 1 3 1 2 1
2 6 8 5 0
8 2 4 1
6 1 0
4 -1
4
```
### 样例输出 #1
```
27
```
## 提示

在10%的数据中，$M=1$  
在20%的数据中，$1≤M≤2$  
在40%的数据中，$1≤M≤3$  
在60%的数据中，$1≤M≤4$  
在100%的数据中，$1≤N≤100$，$1≤M≤79$  
保证所以输入数据中最少费用小于$10^6$。  
保证至少存在一种可行方案。

纪中联赛模拟题  
BY CQF  


---

---
title: "逃生之路"
layout: "post"
diff: 省选/NOI-
pid: P4968
tag: ['2018', '网络流', 'O2优化', '费用流']
---
# 逃生之路
## 题目背景

还在茫茫宇宙中……
## 题目描述

还是这群生物 ccj，因为上次的打击太草率了，同时被他人侦测到了。在得知自己即将受到黑暗森林打击之后，选择逃离自己的家园。

他们的旅程计划在一条线上，其中，我们约定，一号点是他们的家园，有无限多个生物。每一个星球，都可以向之后连续的 $p$ 个星球进行转移。但由于每个星球的”体质“不同，每个星球所能接受的生物数量限定在一个范围 $[b,a]$ 之间。而且，由于星球本身资源匮乏，到达每一个星球都需要消耗星球一定的能源，补充飞船能源。并且又因为宇宙空间的复杂，所以这个能源是关于星球所接受生物数量的一个多项式。飞船年久失修，所以遇到任何星球必定前往去补充能源。

可惜这群生物有一个睿智的头领，他希望最终能有生物到达可以生存的星球，而且消耗的总能源要尽量少。那群生物对这个头领很失望，于是把任务丢给你。

请求出有生物到达可生存星球的情况下，最少的能源消耗是多少？

## 输入格式

第一行两个整数$n$和$p$，表示有$n$个星球（包括他们的家园和目的地），每次向后跳$p$个，保证 $p\le n-1$。

接下来有 $2\times n-2$ 行，偶数行有三个数字，$a_i$、$b_i$ 和 $f_i$，$i$ 从 $2$ 开始，表示第 $i$ 个星球能承载的生物数范围和这个星球是否能够生存，$f_i$ 为 $1$ 即能生存，$0$ 即为不能生存。

奇数行先有一个数字 $k$，表示这个多项式是  $k$ 次，接下来 $k+1$ 个整数，表示从高到低每一项的系数 $wi$。
## 输出格式

一个整数 $ans$ 表示花费最少的能源是多少，如果没有一个生物能到达，输出**"die"**（不包括引号）。
## 样例

### 样例输入 #1
```
3 1
5 2 0
2 30 17 28
5 1 1
2 47 56 -60
```
### 样例输出 #1
```
422

```
### 样例输入 #2
```
3 1
1 1 0
1 1 1
1 1 0
1 1 1
```
### 样例输出 #2
```
die
```
### 样例输入 #3
```
10 3
23 16 1
3 25 15 -27 47
43 38 0
3 19 35 40 -11
43 37 0
3 70 22 8 -28
41 36 0
3 86 -8 21 -59
39 33 1
3 83 37 -26 56
18 12 0
3 3 96 -75 43
50 43 0
3 85 -2 47 -36
48 41 1
3 36 -4 83 -61
14 8 1
3 33 13 35 -24

```
### 样例输出 #3
```
21071866

```
## 提示

**样例解释**

样例一中从 $1\to 2$ 两个ccj，$2\to 3$ 两个 ccj，$2\times 2\times 30+2\times 17+28+2\times 2\times 47+2\times 56-60=422$

样例二由于没有任何一个星球可以生存，故 die。

$2\le n\le 100\quad |w|\le 100\quad 1\le b\le a\le 100\quad 1\le k\le 5\quad 0\le p\le 10$。

保证多项式函数二阶导函数在 $x∈[1,100]$ 时恒大于 $0$。


---

---
title: "[CTSC2001] 终极情报网"
layout: "post"
diff: 省选/NOI-
pid: P5814
tag: ['2001', '网络流', '费用流', 'CTSC/CTS']
---
# [CTSC2001] 终极情报网
## 题目描述

在最后的诺曼底登陆战开始之前，盟军与德军的情报部门围绕着最终的登陆地点展开了一场规模空前的情报战。 这场情报战中，盟军的战术是利用那些潜伏在敌军内部的双重间谍，将假的登陆消息发布给敌军的情报机关的负责人。那些已经潜入敌后的间谍们都是盟军情报部的精英，忠实可靠；但是如何选择合适的人选，以及最佳的消息传递方法，才能保证假消息能够尽快而且安全准确地传递到德军指挥官们的耳朵里，成了困扰盟军情报部长的最大问题。他需要你的帮助。

以下是情报部长提供的作战资料：

在敌后一共潜伏着我方最优秀的 $N$ 名间谍，分别用数字 $1,2,\cdots,N$ 编号。在给定的作战时间内，任意两人之间至多只进行一次点对点的双人联系。 我将给你一份表格，表格中将提供任意两位间谍 $i$ 和 $j$ 之间进行联系的安全程度，用一个 $[0,1]$ 的实数 $S_{i,j}$ 表示；以及他们这次联系时，能够互相传递的消息的最大数目，用一个正整数表示 $M_{i,j}$（如果在表格中没有被提及，那么间谍 $i$ 和 $j$ 之间不进行直接联系）。 假消息从盟军总部传递到每个间谍手里的渠道也不是绝对安全，我们用 $[0,1]$ 的实数 $AS_j$ 表示总部与间谍 $j$ 之间进行联系的安全程度，$AM_j $  则表示总部和间谍 $j$ 之间进行联系时传递的消息的最大数目。对于不和总部直接联系的间谍，他的  $AM_j = 0$（而表格中给出的他的 $AS_j$ 是没有意义的）。 当然，假消息从间谍手中交到敌军的情报部官员的办公桌上的过程是绝对安全的，也即是说，间谍与敌军情报部门之间要么不进行直接联系，要么其联系的安全程度是 $1$（即完全可靠）。

现在情报部打算把 $K$ 条假消息“透露”到德军那里。消息先由总部一次性发给 $N$ 名间谍中的一些人，再通过他们之间的情报网传播，最终由这 $N$ 名间谍中的某些将情报送到德军手中。 对于一条消息，只有安全的通过了所有的中转过程到达敌军情报部，这个传递消息的过程才算是安全的；因此根据乘法原理，它的安全程度 $P$ 就是从总部出发，经多次传递直到到达德军那里，每一次传递该消息的安全程度的乘积。 而对于整个计划而言，只有当 $N$ 条消息都安全的通过情报网到达德军手中，没有一条引起怀疑时，才算是成功的。所以计划的可靠程度是所有消息的安全程度的乘积。 显然，计划的可靠性取决于这些消息在情报网中的传递方法。 我需要一个方案，确定消息应该从哪些人手中传递到哪些人手中，使得最终计划的可靠性最大。

你可以利用计算机，来求得这个最可靠的消息传递方案。
## 输入格式

输入包含了盟军的作战资料表格。

第一行包括两个整数 $N$ 和 $K$ ，分别是间谍的总人数和计划包含的消息总数。

第二行包括 $2N$ 个数，前 $N$ 个数是实数 $AS_1,AS_2,\cdots,AS_N$ （范围在 $[0,1]$ 以内）；后 $N$ 个数是整数 $AM_1,AM_2,\cdots,AM_N$ 。

第三行包含了 $N$ 个整数，其中第 $i$（$i = 1,2,\cdots,N$）个整数如果为 $0$ 表示间谍 $i$ 与德军情报部不进行联系，如果为 $1$ 则表示间谍 $i$ 与德军情报部进行联系。

第四行开始，每行包括 $4$ 个数，依次分别是：代表间谍编号的正整数 $i$ 和 $j$ ，间谍 $i$ 和 $j$ 联系的安全性参数 $S_{i,j}$ ( $[0,1]$ 范围内的实数)，以及 $i,j$ 之间传递的最大消息数 $M_{i,j}$ (每一行的 $i$ 均小于 $j$)。

最后的一行为 `-1 -1` ，表示输入数据的结束。
## 输出格式

输出只有一行。这一行中包含一个实数 $P$ ，给出的是整个计划的可靠程度 $P$ ，**保留 $5$ 位有效数字**（四舍五入）。

如果情报网根本不能将 $K$ 条消息传到德军手中，那么计划的可靠性为 $0$ 。

(你可以假定，如果计划存在，那么它的可靠性大于 $10^{-12}$)
## 样例

### 样例输入 #1
```
6 13
0.9 0.7 0.8 0 0 0 2 6 8 0 0 0
0 0 0 1 0 1
1 4 0.5 2
2 3 0.9 5
2 5 0.8 2
2 6 0.8 7
3 5 0.8 2
5 6 0.8 4
-1 -1

```
### 样例输出 #1
```
0.00021184

```
## 提示

$1 \le N,K \le 300$。


---

---
title: "[NEERC 2016] Mole Tunnels"
layout: "post"
diff: 省选/NOI-
pid: P6122
tag: ['2016', 'ICPC', '模拟费用流']
---
# [NEERC 2016] Mole Tunnels
## 题目描述

鼹鼠们在底下开凿了 $n$ 个洞，由 $n-1$ 条隧道连接，对于任意的 $i>1$，第 $i$ 个洞都会和第 $\frac{i}{2}$（取下整）个洞间有一条隧道，第 $i$ 个洞内还有 $c_i$ 个食物能供最多 $c_i$ 只鼹鼠吃。一共有 $m$ 只鼹鼠，第 $i$ 只鼹鼠住在第 $p_i$ 个洞内。

一天早晨，前 $k$ 只鼹鼠醒来了，而后 $m-k$ 只鼹鼠均在睡觉，前 $k$ 只鼹鼠就开始觅食，最终他们都会到达某一个洞，使得所有洞的 $c_i$ 均大于等于该洞内醒着的鼹鼠个数，而且要求鼹鼠行动路径总长度最小。现对于所有的 $1 \le k \le m$，输出最小的鼹鼠行动路径的总长度，保证一定存在某种合法方案。
## 输入格式

第一行两个数 $n,m$，表示有 $n$ 个洞，$m$ 只鼹鼠。
第二行 $n$ 个整数 $c_i$ 表示第 $i$个洞的食物数。
第三行 $m$ 个整数 $p_i$ 表示第 $i$只鼹鼠所在洞 $p_i$。
## 输出格式

输出一行 $m$ 个整数，第 $i$ 个整数表示当 $k=i$ 时最小的鼹鼠行动路径总长度。

## 样例

### 样例输入 #1
```
5 4
0 0 4 1 1
2 4 5 2
```
### 样例输出 #1
```
1 1 2 4
```
## 提示

$1 \le n,m \le 10^5$，$0 \le c_i \le m$，$1 \le p_i \le n$。


---

---
title: "[THUPC 2017] 机场"
layout: "post"
diff: 省选/NOI-
pid: P7425
tag: ['2017', '图论建模', '费用流', 'THUPC']
---
# [THUPC 2017] 机场
## 题目描述

飞机场有 $a+b$ 个停机位，其中 $a$ 个停机位有登机桥连接飞机和候机厅，乘客可以通过登机桥直接由候机厅登上飞机；另外 $b$ 个停机位没有登机桥和候机厅相连，所以乘客登机需要先搭乘摆渡车再登机。

毫无疑问，搭乘摆渡车的体验是非常差的，所以每位搭乘摆渡车的乘客都会产生不愉快度。

现在，给定每架飞机的乘客数量，登机时间和起飞时间；飞机需要在登机时间点选择一个空闲的停机位，在这个时间点内所有乘客会完成登机，然后飞机会一直停在该停机位，直到起飞时间；

若某飞机在时刻 $x$ 起飞，则在时刻 $x$ 该飞机所在的停机位是空闲的。

飞机场的管理层希望能够尽量减少乘客的不愉快度，为此飞机在登机时间到起飞时间之间，可以切换停机位；

假设某飞机从 $x$ 时间开始由停机位 A 切换到停机位 B，那么停机位 A 在 $x+1$ 时间是空闲的。能进行这样的切换当且仅当停机位 B 在 $x+1$ 时间是空闲的。
## 输入格式

输入有多组数据，第一行一个正整数 $T$ 表示数据组数；对于每组数据：

第一行输入三个非负整数 $n,a,b$，分别表示飞机数量、有登机桥的停机位数量、没有登机桥的停机位数量；

第二行一个浮点数 $p$，输入最多保留小数点后两位；

接下来 $n$ 行，每行三个正整数 $x,s,t$，描述一架飞机的乘客数量、登机时间和起飞时间。
## 输出格式

对于每组数据，输出一行一个整数，表示最小的不愉快度。

如果无法安排一个合理的方案使得所有飞机都完成登机，则输出 `impossible`。
## 样例

### 样例输入 #1
```
2
3 1 1
0.5
1 1 5
1 1 5
1 1 5
6 2 2
0.5
4 1 4
4 2 7
8 4 8
8 4 8
10 5 9
1 7 9
```
### 样例输出 #1
```
impossible
7
```
## 提示

题目中貌似没有给出明确的不愉快度的计算方法，据样例解释推测是不愉快度=所有乘坐摆渡车的人数$+p\times$ 每次切换停机位的飞机上的人数向下取整。
#### 数据范围
$1\le T\le 8,1\le n\le 200,0\le p\le1,1\le x\le 10^5,1\le s\le t\le10^9$
#### 样例解释
飞机从 $1$ 开始编号

在时刻 $1$，$1$ 号飞机安排到登机桥 A，乘客开始登机；目前 $1$ 号飞机在登机桥 A。

在时刻 $2$，$2$ 号飞机安排到登机桥 B，乘客开始登机；目前 $1$ 号飞机在登机桥 A，$2$ 号飞机在登机桥 B。

在时刻 $3$，$2$ 号飞机切换到摆渡车 A，此时登机桥 B 尚不可用。

在时刻 $4$，$1$ 号飞机起飞，$2$ 号飞机到达摆渡车 A， 号飞机安排到登机桥 A，$3$ 号飞机安排到登机桥 B，$4$ 号和 $3$ 号的乘客开始登机，登机完成之后 $4$ 号飞机切换到摆渡车 B，此时登机桥 A 和登机桥 B 都不空闲。

在时刻 $5$，$3$ 号飞机到达摆渡车 B，登机桥 A 变为可用，$5$ 号飞机安排到登机桥 A，开始登机；目前 $5$ 号——登机桥 A，$4$ 号——登机桥 B，$3$ 号——摆渡车 B，$2$ 号——摆渡车 A。

在时刻 $7$，$2$ 号飞机起飞，$6$ 号飞机安排到摆渡车 A。

不愉快度为 $7=1$（$6$ 号飞机乘客乘摆渡车）$+4\times 0.5$（$2$ 号飞机切换停机位）$+8\times 0.5$（$3$ 号飞机切换停机位）
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "[THUSC 2017] 换桌"
layout: "post"
diff: 省选/NOI-
pid: P7452
tag: ['2017', '线段树', '费用流', 'THUSC']
---
# [THUSC 2017] 换桌
## 题目描述

班级聚会的时候，班主任为了方便管理，规定吃饭的时候同一个寝室的同学必须坐在一起；但是吃完饭后，到了娱乐时间，喜欢不同游戏的同学会聚到一起；在这个过程中就涉及到了座位分配的问题。

有 $n$ 张圆桌排成一排（从左到右依次编号为 $0$ 到 $n-1$），每张桌子有 $m$ 个座位（按照逆时针依次编号为 $0$ 到 $m-1$），在吃饭时每个座位上都有一个人；在吃完饭后的时候，每个人都需要选择一个新的座位（新座位可能和原来的座位是同一个），具体来说，第 $i$ 桌第 $j$ 个人的新座位只能在第 $L_{i,j}$ 桌到第 $R_{i,j}$ 桌中选，可以是这些桌中的任何一个座位。确定好新座位之后，大家开始移动，移动的体力消耗按照如下规则计算：

移动座位过程分为两步：

1. 从起始桌移动到目标桌**对应座位**，这个过程中的体力消耗为**两桌距离的两倍**，即从第 $i$ 桌移动到第 $j$ 桌对应座位的体力消耗为 $2\times |i-j|$；
1. 从目标桌的对应座位绕着桌子移动到目标座位，由于桌子是圆的，所以客人会选择**最近的方向**移动，体力消耗为**移动距离的一倍**，即从编号为 $x$ 的座位移动的编号为 $y$ 的座位的体力消耗为 $\min(|x-y|,m-|x-y|)$；

详情如下图：
![pic1](https://i.loli.net/2019/01/16/5c3f2f01e0336.png)
现在，给定每个客人的限制（即每个人的新座位所在的区间），需要你设计一个方案，**使得所有客人消耗的体力和最小；本题中假设客人在移动的时候互不影响。**
## 输入格式

从标准输入读入数据。

第一行输入两个数 $n$ 和 $m$；

接下来输入 $n$ 行，每行 $m$ 个空格隔开的整数描述矩阵 $L$：其中，第 $i$ 行的第 $j$ 个数表示 $L_{i,j}$；

接下来输入 $n$ 行，每行 $m$ 个空格隔开的整数描述矩阵 $R$：其中，第 $i$ 行的第 $j$ 个数表示 $R_{i,j}$；

数据是随机生成的，生成数据的伪代码如下：
```cpp
for i <- 0 to n-1
    for j <- 0 to m-1
        L[i,j] <- 独立等概率地得到 0 到 n-1 中的一个整数
        R[i,j] <- 独立等概率地得到 0 到 n-1 中的一个整数
        if L[i,j] > R[i,j] then
            tmp <- L[i,j]
            L[i,j] <- R[i,j]
            R[i,j] <- tmp
```

## 输出格式

输出到标准输出。

输出总体力消耗的最小值，如果没有合法的方案输出 `no solution`。
## 样例

### 样例输入 #1
```
2 4
0 1 1 0
1 0 1 0
0 1 1 0
1 0 1 0
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
2 4
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
```
### 样例输出 #2
```
no solution
```
### 样例输入 #3
```
2 10
0 0 1 1 0 0 0 1 0 0
1 1 1 0 0 1 0 0 0 0
1 0 1 1 1 0 1 1 1 1
1 1 1 1 1 1 0 0 1 0
```
### 样例输出 #3
```
22
```
## 提示

#### 样例解释
对于样例 $1$，
![pic2](https://i.loli.net/2019/01/16/5c3f2f01d91ae.png)

第 $0$ 桌的 $0$ 和 $3$ 号，以及第 $1$ 桌的 $0$ 号和 $2$ 号都被限制为只能坐在他们原来的桌子（可以不是原来的座位），其他人分别需要换到第 $1$ 桌和第 $0$ 桌；

可以发现，最优方案如上图，总体力消耗为 $10$。

对于样例 $2$，所有人都想坐到第 $0$ 桌，所以没有合法的方案。

对于全部数据：$1\le n\le 300$，$1\le m\le 10$，$0\le L_i\le R_i\le n-1$ 。
| 测试点 | $n\le$ |
| :----------: | :----------: |
| 1~2 | $2$ |  |
| 3~8 | $40$ |  |
| 9~14 | $100$ |  |
| 15~20 | $300$ |  |



---

---
title: "[JDWOI-1] 蜀道难"
layout: "post"
diff: 省选/NOI-
pid: P7730
tag: ['网络流', '二分图', '费用流']
---
# [JDWOI-1] 蜀道难
## 题目背景

蜀道难，难于上青天…… 

蜀道之所以难，就是因为山路崎岖不平。
## 题目描述

小 K 和小 M 也模拟了蜀道难。在蜀道难中，有 $n$ 座山，每座山高度为 $h_i$。小 K 和小 M 有 $m$ 种魔法，每一次膜法可以把连续 $l_i$ 座山的高度抬高或压低 $1$，同时消耗 $c_i$ 点体力。

现在，小 K 和小 M 想让蜀道难的 $n$ 座山的高度不下降，这样蜀道就不难了。请问他们最少需消耗多少体力？

**注**：所有时候山的高度都不能为负。
## 输入格式

第一行两个整数 $n,m$，表示山的数量和膜法数量。

第二行 $n$ 个整数 $h_i$，表示山的高度。

接下来 $m$ 行，每行一个字符和两个整数 $w_i, l_i, c_i$，描述一种膜法（如果 $w_i$ 为 $+$，代表抬高；如果 $w_i$ 为 $-$，代表压低）。
## 输出格式

一行一个整数，表示最小消耗的体力。

如果无解，输出 $-1$。
## 样例

### 样例输入 #1
```
3 3
1 3 2
- 1 10
- 2 3
+ 1 1
```
### 样例输出 #1
```
1
```
## 提示

### 样例解释

使用 $1$ 体力值将第三座山升高 $1$。

### 数据范围

- 对于 $10\%$ 的数据，$1\leq n,m \leq 10$；
- 对于另外 $30\%$ 的数据，$1\leq n,m \leq 20$；
- 对于另外 $10\%$ 的数据，$m=1$；
- 对于所有的数据，$1\leq n, m \leq 200$，$1\leq l_i \leq n$，$1\leq h_i, c_i \leq 10^3$。


---

---
title: "「EVOI-RD1」飞鸟和蝉"
layout: "post"
diff: 省选/NOI-
pid: P7863
tag: ['图论建模', '二分图', '费用流']
---
# 「EVOI-RD1」飞鸟和蝉
## 题目背景

你骄傲地飞远，我栖息的叶片。  
听不见的宣言，重复过很多年。  
沧海月的想念羽化我昨天，  
在我成熟的笑脸，  
你却未看过一眼。
## 题目描述

蝉 Charlie 要去寻找他的好朋友飞鸟了。 

具体来说，Charlie 和他的好朋友生活的地方可以看作一个 $n \times m$ 的网格，左上角为 $(1,1)$，右下角为 $(n,m)$。每个格子 $(i,j)$ 有一个海拔高度 $h_{i,j}$。Charlie 的目标是从他的家 $(x_0,y_0)$ 出发，不重不漏地经过网格中的每个格子**恰好一次**，**最终回到自己的家** $(x_0,y_0)$。Charlie 有两种移动方式：

1. 跳跃。用这种方式，Charlie 可以到达上下左右 $4$ 个相邻格子中**海拔严格低于当前格子**的一个格子。注意跳跃不消耗体力。  
2. 飞行。用这种方式，Charlie 可以从当前格子 $(x,y)$ 到达网格中**任意一个**格子 $(x',y')$，并消耗 $h_{x',y'}-h_{x,y}$ 个单位的体力。**注意飞行所消耗的体力值可以是负数**。  

Charlie 希望用尽量少的飞行次数完成目标，**在此前提下**再令消耗的体力最少。由于网格实在太大了，Charlie 希望你能帮助他。
## 输入格式

第一行四个整数，分别代表 $n,m,x_0,y_0$，含义如上所述。  
接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 个数代表格子 $(i,j)$ 的海拔 $h_{i,j}$。
## 输出格式

一行两个整数，分别代表“飞行的最少次数”与“飞行次数最少的前提下消耗的最少体力值”。
## 样例

### 样例输入 #1
```
3 3 1 1
1 2 3
8 9 4
7 6 5
```
### 样例输出 #1
```
1 8
```
### 样例输入 #2
```
3 3 2 3
1 2 3
2 2 4
1 2 2
```
### 样例输出 #2
```
5 4
```
### 样例输入 #3
```
4 4 2 3
5 9 6 2
4 2 3 6
7 2 5 2
4 2 3 9
```
### 样例输出 #3
```
7 25
```
### 样例输入 #4
```
10 10 3 3
9 13 7 7 3 8 6 5 12 8
1 4 10 11 9 10 13 6 2 18
3 3 19 6 14 2 19 10 2 16
3 1 11 14 14 18 8 8 16 14
13 5 7 4 11 17 3 16 10 20
10 16 12 19 14 12 11 20 15 10
10 15 5 1 16 2 7 5 14 5
3 19 12 19 8 13 17 7 10 13
2 10 17 6 8 11 8 7 1 4
3 7 8 1 3 5 4 11 9 17
```
### 样例输出 #4
```
36 254
```
## 提示

**本题采用捆绑测试**

样例 1 解释：从 $(1,1)$ 飞到 $(2,2)$，再绕一圈即可。

样例 2 解释：一种最佳方案为：$(2,3)-(1,3)-(1,2)-(1,1)=(2,1)-(3,1)=(2,2)=(3,2)=(3,3)=(2,3)$，其中 $=$ 代表飞行。  

- Subtask 1 (10 pts)：满足 $1 \leq n,m \leq 3$。
- Subtask 2 (20 pts)：满足 $1 \leq n,m \leq 5$。
- Subtask 3 (20 pts)：保证至多有两种不同的海拔高度。 
- Subtask 4 (50 pts)：无特殊限制。

对于 $100\%$ 的数据：
- $1 \leq n,m \leq 50$。

- $1 \leq x_0 \leq n,1 \leq y_0 \leq m,1 \leq h_{i,j} \leq 10^9$。  

出题人：[冷月葬T魂](https://www.luogu.com.cn/user/340903)


---

---
title: "[ONTAK2015] Bajtman i Okrągły Robin"
layout: "post"
diff: 省选/NOI-
pid: P8021
tag: ['2015', '线段树', '图论建模', '费用流']
---
# [ONTAK2015] Bajtman i Okrągły Robin
## 题目背景

**警告：滥用本题评测将被封号！**
## 题目描述

有 $n$ 个强盗，其中第 $i$ 个强盗会在 $[a_i, a_i + 1], [a_i + 1, a_i + 2], \cdots, [b_i - 1, b_i]$ 这么多段长度为 $1$ 的时间中选出一个时间进行抢劫，并计划抢走 $c_i$ 元。作为保安，你在每一段长度为 $1$ 的时间内最多只能制止一个强盗，那么你最多可以挽回多少损失呢？
## 输入格式

第一行，一个整数 $n$；

接下来 $n$ 行，每行三个整数 $a_i, b_i, c_i$。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
4
1 4 40
2 4 10
2 3 30
1 3 20
```
### 样例输出 #1
```
90
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^3$，$1 \leq a_i < b_i \leq 5 \times 10^3$，$1 \leq c_i \leq 10^4$。


---

