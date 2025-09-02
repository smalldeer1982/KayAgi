---
title: "Choose"
layout: "post"
diff: 普及+/提高
pid: P10059
tag: ['贪心', '二分', '单调队列', '洛谷原创', 'O2优化', '前缀和', 'ST 表', '洛谷月赛']
---
# Choose
## 题目背景

[加强版](https://www.luogu.com.cn/problem/U397746)

对于一个长度为 $n$ 的序列 $a$ ，定义 $a$ 的极差表示 $a$ 中最大值与最小值之差；定义 $C(a,l,r)$ 表示 $a$ 的**连续**子序列 $[a_l,a_{l+1},\dots,a_r]$，其中 $1\le l\le r\le n$。
## 题目描述

给定一个长度为 $n$ 的序列 $a$。

你需要选出 $a$ 的 $k$ 个长度均为 $L$ $(1\le L\le n-k+1)$ 的不同**连续**子序列 
$C(a,l_1,l_1+L-1),C(a,l_2,l_2+L-1),\dots,C(a,l_k,l_k+L-1)$，其中 $1\le l_1<l_2< \dots< l_k\le n-L+1$。

记这 $k$ 个子序列中极差的最小值为 $X$，你需要求出 $X$ 的最大值。同时，你还需要求出，在满足 $X$ 最大的情况下  $L$ 的最小值。
## 输入格式

**本题有多组测试数据。**

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据：

- 第一行两个整数 $n,k$。
- 第二行 $n$ 个整数 $a_1,a_2,...,a_n$。
## 输出格式

对于每组测试数据：

- 一行两个整数 $X,L$，表示所求极差和子序列长度。
## 样例

### 样例输入 #1
```
3
5 1
1 2 3 4 5
5 2
1 2 3 4 5
5 3
1 2 3 4 5
```
### 样例输出 #1
```
4 5
3 4
2 3
```
### 样例输入 #2
```
2
5 1
1 2 2 2 3
5 2
1 2 2 2 3
```
### 样例输出 #2
```
2 5
1 2
```
## 提示

**【样例 1 解释】**

- $k=1$ 时，极差最大不超过 $4$，此时满足长度最短的一种方案为 $[1,2,3,4,5]$。
- $k=2$ 时，极差最大不超过 $3$，此时满足长度最短的一种方案为 $[1,2,3,4],[2,3,4,5]$。
- $k=3$ 时，极差最大不超过 $2$，此时满足长度最短的一种方案为 $[1,2,3],[2,3,4],[3,4,5]$。

**【数据规模与约定】**

**本题采用捆绑测试。**

| 子任务 | 分值 | $n\le$ | $k\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^5$ | $n$ | $a_i$ 均相等 |
| $2$ | $5$ | $10^5$ | $1$ | 数据随机生成 |
| $3$ | $10$ | $100$ | $n$ | 所求的 $X$ 不超过 $10^3$ |
| $4$ | $20$ | $100$ | $n$ | 无 |
| $5$ | $20$ | $10^4$ | $n$ | 无 |
| $6$ | $40$ | $10^5$ | $n$ | 无 |

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le n\le 10^5$，$1\le k\le n$，$-10^9\le a_i\le 10^9$。


---

---
title: "「XSOI-R1」跳跃游戏"
layout: "post"
diff: 普及+/提高
pid: P10403
tag: ['线段树', '二分', '2024', '洛谷原创', 'O2优化', '枚举', 'ST 表', '双指针 two-pointer']
---
# 「XSOI-R1」跳跃游戏
## 题目背景

本来可怜的 $\texttt{MhxMa}$ 想出这道题，但是已经被 $\texttt{Ferm\_Tawn}$ 抢了，此时 $\texttt{MhxMa}$ 坐在电脑面前，看着马上要造好的数据，想象着自己的题难倒一大片选手的梦想破灭了。
## 题目描述

这是一个跳跃游戏。在游戏中你可以跳到任意位置，其中有 $n$ 个点：$1 , 2 , 3, \cdots , n$，跳到那里会有奖励分数 $a_1 , a_2 , \cdots , a_n$。

显然，这个游戏很简单，$\texttt{MhxMa}$ 没过多久就获得了所有分数，于是改进了代码，添加了经验值这个参数。

对于有奖励分数的 $n$ 个点，若从点 $x$ 跳到点 $y$，会获得经验值 $\operatorname{score}_{x , y}(1\le x\le y\le n)$：

$$\operatorname{score}_{x,y}=\begin{cases}\operatorname{len}  & \operatorname{gcd}(a_x , a_{x+1} , \dots , a_y)=2 , \operatorname{len \ mod} 2 = 0  \\ \operatorname{len} &\gcd(a_x , a_{x + 1} , \dots , a_y)=3 , \operatorname{len \ mod} 2 = 1\\ 0 & \operatorname{others} \end{cases}$$

其中，$\operatorname {len}$ 表示区间的长度，即 $y-x+1$。

**对于每一对位置 $(x,y)$，多次跳跃只会获得一次经验值。**

为了向 $\texttt{MhxMa}$ 展现你的编程实力，你决定写一个代码算出这个游戏能刷到的最大经验值。
## 输入格式

输入共两行。

输入第一行包含一个整数 $n$。

第二行包含 $n$ 个整数 $a_i$。
## 输出格式

输出一个整数，表示答案。
## 样例

### 样例输入 #1
```
5
2 3 6 3 9
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
5
2 2 2 2 2
```
### 样例输出 #2
```
16
```
### 样例输入 #3
```
9
6 2 3 6 4 6 8 2 5
```
### 样例输出 #3
```
19
```
## 提示

**请使用较快的读入方式。**

### 样例解释 #1

$\operatorname{score_{2 , 2}}= 1$。

$\operatorname{score_{2 , 4}}= 3$。

$\operatorname{score_{3 , 5}}= 3$。

$\operatorname{score_{4 , 4}}= 1$。

$1+3+3+1=8$。

### 样例解释 #2

$\operatorname{score_{1 , 2}}= 2$。

$\operatorname{score_{1 , 4}}= 4$。

$\operatorname{score_{2 , 3}}= 2$。

$\operatorname{score_{2 , 5}}= 4$。

$\operatorname{score_{3 , 4}}= 2$。

$\operatorname{score_{4 , 5}}= 2$。

$2+ 4 + 2 + 4 + 2 + 2 = 16$。

------------
### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 0（20 pts）：$n \le 10^2$。 

- Subtask 1（10 pts）：$n \le 2 \times 10^3$。

- Subtask 2（20 pts）：$n \le 10^4$。

- Subtask 3（50 pts）：$n \le 6 \times 10^5 $。


对于所有测试数据，$1 \le n \le 6 \times 10^5$，$1 \le a_i \le 10^7$。


---

---
title: "「CZOI-R1」消除威胁"
layout: "post"
diff: 普及+/提高
pid: P10798
tag: ['贪心', 'O2优化', 'ST 表', '单调栈']
---
# 「CZOI-R1」消除威胁
## 题目背景

**本题数据已修复。**
## 题目描述

给定一个序列 $\{A_n\}$。

我们称序列 $A$ 中的一个区间 $[l,r]$ 具有威胁，当且仅当 $1\le l<r\le n$ 且 $A_l=A_r$，且 $\forall i\in[l,r]$ 满足 $|A_i|\le|A_l|$。

你可以操作 $A$ 任意次，每次操作选择一个 $A_i$ 修改为 $-A_i$。请问最后序列 $A$ 中具有威胁的**不同**区间**最少**有多少个？



两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 不同，当且仅当 $l_1 \ne l_2$ 或 $r_1 \ne r_2$。


## 输入格式

第一行一个整数 $n$ ，表示 $A$ 的长度。

第二行 $n$ 个整数，表示 $\{A_n\}$。
## 输出格式

第一行一个正整数，表示**最少**的具有威胁的区间个数。
## 样例

### 样例输入 #1
```
8
3 2 1 2 3 -1 3 3
```
### 样例输出 #1
```
2
```
## 提示

**【数据范围】**

**本题采用捆绑测试**。
- Subtask #1（$10\text{ pts}$）：$n\le10$。
- Subtask #2（$10\text{ pts}$）：$n\le10^3$。
- Subtask #3（$10\text{ pts}$）：$|A_i|\le60$。
- Subtask #4（$10\text{ pts}$）：$|A_i|$ 均相等。
- Subtask #5（$20\text{ pts}$）：$n\le10^5$。
- Subtask #6（$40\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$|A_i|\le10^9$。


---

---
title: "[JSOI2008] 最大数"
layout: "post"
diff: 普及+/提高
pid: P1198
tag: ['2008', '线段树', '二分', '各省省选', '江苏', '栈', 'ST 表']
---
# [JSOI2008] 最大数
## 题目描述

现在请求你维护一个数列，要求提供以下两种操作：

1.  查询操作。

语法：`Q L`

功能：查询当前数列中末尾 $L$ 个数中的最大的数，并输出这个数的值。

限制：$L$ 不超过当前数列的长度。$(L > 0)$

2. 插入操作。

语法：`A n`

功能：将 $n$ 加上 $t$，其中 $t$ 是最近一次查询操作的答案（如果还未执行过查询操作，则 $t=0$），并将所得结果对一个固定的常数 $D$ 取模，将所得答案插入到数列的末尾。

限制：$n$ 是整数（可能为负数）并且在长整范围内。

注意：初始时数列是空的，没有一个数。

## 输入格式

第一行两个整数，$M$ 和 $D$，其中 $M$ 表示操作的个数，$D$ 如上文中所述。

接下来的 $M$ 行，每行一个字符串，描述一个具体的操作。语法如上文所述。
## 输出格式

对于每一个查询操作，你应该按照顺序依次输出结果，每个结果占一行。

## 样例

### 样例输入 #1
```
5 100
A 96
Q 1
A 97
Q 1
Q 2

```
### 样例输出 #1
```
96
93
96

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq M \leq 2 \times 10^5$，$1 \leq D \leq 2 \times 10^9$。


---

---
title: "扶苏出勤日记"
layout: "post"
diff: 普及+/提高
pid: P12000
tag: ['二分', '单调队列', '洛谷原创', 'O2优化', 'ST 表', '洛谷月赛']
---
# 扶苏出勤日记
## 题目描述

扶苏是一个舞萌吃。在接下来的 $n$ 天里，她每天都要去玩舞萌，并且她希望每天**游玩的局数相同**。

游玩一局舞萌固定花费 $1$ 个游戏币。然而，游戏币每天的价格都有可能变化。具体来说，在第 $i$ 天，一元可以购买 $a_i$ 个游戏币。

靠着给洛谷打~~黑~~工，扶苏每天都会有一些收入。她会在第 $i$ 天收入 $b_i$ 元。

每天，扶苏会**先**得到当天的收入 $b_i$ 元，再去购买游戏币，再游玩舞萌。

扶苏每天可以使用自己拥有的钱的任意金额按照当天的币价购买游戏币。也就是说，她不必一次性换光所有的钱，可以在当天只使用一部分钱购买游戏币，存下一些剩余的钱留在今后的若干天购买游戏币。同时，她一天不必花光所有的游戏币，可以只在当天花费一部分游戏币，存下一些剩余的游戏币在之后的若干天玩。

扶苏知道今后 $n$ 天的币价和她每天的收入，她想在接下来 $n$ 天里每天游玩相同局数的舞萌。因此她想知道，在她使用最优策略购买游戏币的情况下，她每天最多可以游玩多少局舞萌？
## 输入格式

**本题单个测试点内有多组测试数据**。第一行是一个正整数 $T$，表示数据组数。对每组数据：

第一行是一个整数 $n$，表示总天数。  
第二行是 $n$ 个整数 $a_1, a_2, \dots ,a_n$，表示每天一元钱购买的币数。  
第三行是 $n$ 个整数 $b_1, b_2, \dots ,b_n$，表示扶苏每天的收入。  
## 输出格式

对每组测试数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
5
1 2 3 4 5
5 4 3 2 1
5
1 1 1 1 1
2 3 4 5 6
9
9 9 8 2 4 4 3 5 3
10 10 10 10 10 10 10 10 10
```
### 样例输出 #1
```
5
2
55
```
## 提示

### 数据规模与约定

用 $N$ 表示单个测试点内 $n$ 的和。
- 对 $20\%$ 的数据，保证 $1 \leq n \leq 3$，$N \leq 1000$；
- 对 $40\%$ 的数据，保证 $1\le n \le 2000$，$N \leq 10000$；
- 对 $60\%$ 的数据，满足 $1\le n \le 10^5$，$N \leq 2 \times 10^5$；
- 另有 $10\%$ 的数据，满足 $a_i \geq a_{i + 1}$（对 $1 \leq i \leq n-1$）。
- 另有 $10\%$ 的数据，满足 $a_i \leq a_{i + 1}$（对 $1 \leq i \leq n-1$）。
- 对于 $100\%$ 的数据，满足 $1\le n\le 10^6$，$1\le a_i \le 1000$，$1\le b_i \le 10^9$，$n \leq N \leq 2 \times 10^6$，$1 \leq T \leq 2 \times 10^6$。



---

---
title: "[USACO16OPEN] Splitting the Field G"
layout: "post"
diff: 普及+/提高
pid: P3145
tag: ['2016', 'USACO', '枚举', '排序', 'ST 表']
---
# [USACO16OPEN] Splitting the Field G
## 题目描述

Farmer John's $N$ cows ($3 \leq N \leq 50,000$) are all located at distinct positions in his two-dimensional field.  FJ wants to enclose all of the cows with a rectangular fence whose sides are parallel to the x and y axes, and hewants this fence to be as small as possible so that it contains every cow (cowson the boundary are allowed).

FJ is unfortunately on a tight budget due to low milk production last quarter.He would therefore like to enclose a smaller area to reduce maintenance costs,and the only way he can see to do this is by building two enclosures instead of one.  Please help him compute how much less area he needs to enclose, in total,by using two enclosures instead of one. Like the original enclosure, the two enclosures must collectively contain all the cows (with cows on boundaries allowed), and they must have sides parallel to the x and y axes.  The two enclosures are not allowed to overlap -- not even on their boundaries. Note that enclosures of zero area are legal, for example if an enclosure has zero width and/or zero height.
## 输入格式

The first line of input contains $N$.  The next $N$ lines each contain two integers specifying the location of a cow. Cow locations are positive integers in the range $1 \ldots 1,000,000,000$.
## 输出格式

Write a single integer specifying amount of total area FJ can save by using two enclosures instead of one.
## 样例

### 样例输入 #1
```
6
4 2
8 10
1 1
9 12
14 7
2 3
```
### 样例输出 #1
```
107
```
## 题目翻译

### 题目描述

Farmer John 的 $N$ 头奶牛（$3 \leq N \leq 50,000$）位于他二维牧场的不同位置。FJ 想要用一个与 x 轴和 y 轴平行的矩形围栏将所有奶牛围住，并且他希望这个围栏尽可能小，以便它包含每一头奶牛（允许奶牛位于边界上）。

由于上季度牛奶产量低，FJ 的预算紧张。因此，他希望围住更小的区域以减少维护成本，而他唯一能想到的方法就是建造两个围栏而不是一个。请帮助他计算使用两个围栏而不是一个围栏总共可以减少多少面积。与原始围栏一样，这两个围栏必须共同包含所有奶牛（允许奶牛位于边界上），并且它们的边必须与 $x$ 轴和 $y$ 轴平行。这两个围栏不允许重叠——即使在它们的边界上也不行。注意，零面积的围栏是合法的，例如如果一个围栏的宽度和/或高度为零。

### 输入格式

输入的第一行包含 $N$。接下来的 $N$ 行每行包含两个整数，指定一头奶牛的位置。奶牛的位置是 $1 \ldots 1,000,000,000$ 范围内的正整数。

### 输出格式

输出一个整数，表示 FJ 通过使用两个围栏而不是一个围栏总共可以减少的面积。


---

---
title: "[USACO17DEC] Haybale Feast G"
layout: "post"
diff: 普及+/提高
pid: P4085
tag: ['2017', '线段树', 'USACO', '前缀和', 'ST 表', '双指针 two-pointer']
---
# [USACO17DEC] Haybale Feast G
## 题目描述

Farmer John is preparing a delicious meal for his cows! In his barn, he has $N$ haybales ($1 \le N \le 100,000$). The $i$th haybale has a certain flavor $F_i$ ($1 \le F_i \le 10^9$) and a certain spiciness $S_i$ ($1 \le S_i \le 10^9$).

The meal will consist of a single course, being a contiguous interval containing one or more consecutive haybales (Farmer John cannot change the order of the haybales). The total flavor of the meal is the sum of the flavors in the interval. The spiciness of the meal is the maximum spiciness of all haybales in the interval.


Farmer John would like to determine the minimum spiciness his single-course meal could achieve, given that it must have a total flavor of at least $M$ ($1 \le M \le 10^{18}$).

## 输入格式

The first line contains the integers $N$ and $M$, the number of haybales and the minimum total flavor the meal must have, respectively. The next $N$ lines describe the $N$ haybales with two integers per line, first the flavor $F$ and then the spiciness $S$.

## 输出格式

Please output the minimum spiciness in a single course meal that satisfies the minimum flavor requirement. There will always be at least one single-course meal that satisfies the flavor requirement.

## 样例

### 样例输入 #1
```
5 10
4 10
6 15
3 5
4 9
3 6
```
### 样例输出 #1
```
9
```
## 题目翻译

### 题目描述

农夫约翰正在为他的奶牛准备一顿美味的晚餐！在他的谷仓里，他有 $N$ 个干草捆 $(1 \le N \le 10^5)$ 。第 $i$ 个干草捆有一定的风味 $F_i(1 \le F_i \le 10^9)$ 和一定的辣度 $S_i(1 \le S_i \le 10^9)$ 。

这顿饭将由一道菜组成，是一个连续的区间，包含一个或多个连续的干草捆(农夫约翰不能改变干草捆的顺序)。这顿饭的总体的风味是这段区间里风味的总和。这顿饭的总体辣度是区间中所有草包的最大辣度。

农夫约翰想确定他的这道菜所能达到的最小辣度，但是这道菜的总风味必须至少为 $M(1 \le M \le 10^{18})$ 。

### 输入格式

第一行包含两个整数 $N$ 和 $M$ ，分别是干草包的数量和这顿饭必须有的最小风味之和。

接下来的 $N$ 行，每行两个整数描述这 $N$ 个草包，首先是风味 $F_i$，然后是辣度 $S_i$。

### 输出格式

请输出这道菜中在满足最低风味时的最低辣度。保证至少有一顿单道菜的饭能满足风味的要求。


---

---
title: "[JRKSJ R1] JFCA"
layout: "post"
diff: 普及+/提高
pid: P7333
tag: ['二分', '2021', '洛谷原创', 'ST 表']
---
# [JRKSJ R1] JFCA
## 题目描述

给出一个环，上面有 $n$ 个点，每个相邻的点对之间的距离为 $1$。

每个点有两个属性 $a_i$ 和 $b_i$，对于点 $i$，定义 $f_i$ 为它与满足 $a_j\ge b_i$ 的最近的点 $j$ 与 $i$ 在环上距离较短一边的长度，其中 $i\ne j$。如果没有满足条件的 $j$，其 $f_i=-1$。
## 输入格式

输入共 $3$ 行。\
第 $1$ 行 $1$ 个整数 $n$ 。\
第 $2$ 行 $n$ 个整数，其中第 $i$ 个表示 $a_i$，意义同上。\
第 $3$ 行 $n$ 个整数，其中第 $i$ 个表示 $b_i$，意义同上。
## 输出格式

输出 $1$ 行 $n$ 个整数，其中第 $i$ 个表示 $f_i$，意义同上。
## 样例

### 样例输入 #1
```
3
1 2 3
3 2 1
```
### 样例输出 #1
```
1 1 1
```
### 样例输入 #2
```
5
5 4 3 5 6
7 6 5 4 3
```
### 样例输出 #2
```
-1 2 1 1 1
```
### 样例输入 #3
```
5
1 1 2 1 1
2 2 2 2 2
```
### 样例输出 #3
```
2 1 -1 1 2
```
## 提示

对于 $20\%$ 的数据，$1\le n \le 10^3$；\
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le a_i,b_i\le 10^9$。

我们对于测试点 $4$ 至 $11$ 采用捆绑测试。

#### 样例 1 解释
对于 $i=1$，$a_3=3= b_1=3$, $1$ 和 $3$ 的距离是 $1$，所以 $f_1=1$。\
对于 $i=2$，$a_3=3> b_2=2$, $2$ 和 $3$ 的距离是 $1$，所以 $f_2=1$。\
对于 $i=3$，$a_2=2> b_3=1$, $2$ 和 $3$ 的距离是 $1$，所以 $f_3=1$。

$\text{upd2021.3.30}$：增加一组 hack 数据，卡掉了@[wu0615](https://www.luogu.com.cn/user/133037) 的提交。




---

---
title: "[JRKSJ R2] 01 序列"
layout: "post"
diff: 普及+/提高
pid: P7809
tag: ['2021', '洛谷原创', 'O2优化', 'ST 表']
---
# [JRKSJ R2] 01 序列
## 题目背景

$\text{upd2021.8.16}$：增加两组 hack 数据，并缩小时限至 1.2s。
## 题目描述

给你一个长度为 $n$ 的 $01$ 序列 $a$，$m$ 次询问，支持 $2$ 种询问：

- `1 l r` 表示询问 $l$ 到 $r$ 区间的最长不下降子序列的长度。
- `2 l r` 表示询问 $l$ 到 $r$ 区间的最长上升子序列的长度。
## 输入格式

输入 $m+2$ 行。\
第 $1$ 行两个正整数 $n,m$。\
第 $2$ 行 $n$ 个数字 $0$ 或 $1$ 代表序列 $a$。\
接下来 $m$ 行每行三个正整数表示一次询问，格式如上。
## 输出格式

输出 $m$ 行。\
对于每一次询问求出答案并输出。
## 样例

### 样例输入 #1
```
8 4
0 1 1 0 1 0 0 1
1 1 8
2 1 8
1 3 6
2 5 6
```
### 样例输出 #1
```
5
2
2
1
```
## 提示

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $m\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{1}$ | $10^6$ | $10^6$ | 所有 $a_i$ 均相等 | $5$ |
| $\text{2}$ | $10^3$ | $10^3$ | 无 | $10$ |
| $\text{3}$ | $10^4$ | $10^4$ | 无 | $15$ |
| $\text{4}$ | $10^5$ | $10^5$ | 无 | $30$ |
| $\text{5}$ | $10^6$ | $5\times10^6$ | 无 | $40$ |
| $\text{6}$ | $10^6$ | $5\times10^6$ | hack 数据 | $0$ |

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le m\le 5\times10^6$，$0\le a_i\le 1$。
****
本题输入输出量极大，这里给出出题人使用的快读快写。（当然，使用您自己编写的大概率也能通过）
```cpp
namespace IO{//by cyffff
	int len=0;
	char ibuf[(1<<20)+1],*iS,*iT,out[(1<<26)+1];
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#define reg register
	inline int read(){
		reg char ch=gh();
		reg int x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
	inline void putc(char ch){
		out[len++]=ch;
	}
	template<class T>
	inline void write(T x){
		if(x<0)putc('-'),x=-x;
		if(x>9)write(x/10);
		out[len++]=x%10+48;
	}
	inline void flush(){
		fwrite(out,1,len,stdout);
		len=0;
	}
}
using IO::read;
using IO::write;
using IO::flush;
using IO::putc;
```
使用这种快读快写读入一个数 $x$ 时请使用语句 `x=read();`，输出时使用语句 `write(x);`。注意，换行时需使用语句 `putc('\n');`，程序执行结束时使用语句 `flush();`。

在使用此快读时请加上 `#include<bits/stdc++.h>`。

如果本地无法输入，可以尝试使用 [这里的快读快写](https://www.luogu.com.cn/paste/6za5gs1z)。

若仍看不懂，请在赛时答疑帖回复/私信出题人。

由于出题人只会 `C++`，本处无法给出其他语言的快读快写，深感歉意。
****
#### 样例解释:
对于第一个询问，满足的序列有：$\{0,1,1,1,1\},\{0,0,0,0,1\}$。\
对于第二个询问，满足的序列有：$\{0,1\}$。\
对于第三个询问，满足的序列有：$\{0,0\},\{0,1\},\{1,1\}$。\
对于第四个询问，满足的序列有：$\{0\},\{1\}$。

本题时限、空限保证为出题人所用的两倍以上。\
如果您仍认为卡常，则请私信出题人或者发帖并 @ 出题人。


---

---
title: "[KSN2021] Self Permutation"
layout: "post"
diff: 普及+/提高
pid: P7972
tag: ['2021', 'ST 表']
---
# [KSN2021] Self Permutation
## 题目描述

给定一个长度为 $N$ 的排列 $a_i$，你可以执行若干次操作：

* 选择两个相邻的数，删除它们中较大的那个。

问最后可能得到序列的数量，答案对 $10^9+7$ 取模。

注意如果两个数中间所有的数被删除了，它们会变成相邻的。
## 输入格式

第一行输入一个正整数 $N$。

第二行输入 $N$ 个正整数 $a_i$。
## 输出格式

输出一个整数代表答案。
## 样例

### 样例输入 #1
```
3
2 3 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
2 1 4 3
```
### 样例输出 #2
```
6
```
## 提示

**【样例解释】**

对于第一组样例，以下为所有可能得到的序列：

- $[2,3,1]$
- $[\bold2,\bold3,1]\to[2,1]$
- $[\bold2,\bold3,1]→[\bold2,\bold1]→[1]$

对于第二组样例，以下为所有可能得到的序列：

- $[2,1,4,3]$
- $[\bold2,\bold1, 4, 3]\to[1, 4, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[1, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[\bold1,\bold3]\to[1]$
- $[2, 1,\bold4,\bold3]\to[2, 1, 3]$
- $[2, 1,\bold4,\bold3]\to[2,\bold1,\bold3]\to[2, 1]$

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：只存在一组数据，满足 $N=6$，$A=[2,5,1,3,4,6]$。
- Subtask 2（20 points）：$N\leq 200$。
- Subtask 3（13 points）：$N\leq 2000$，$A_i=i$。
- Subtask 4（9 points）：$A_i=i$。
- Subtask 5（23 points）：$N\leq 2000$。
- Subtask 6（27 points）：无特殊限制。

对于所有数据，$N\leq 3\times 10^5$，保证输入的 $a_i$ 能构成一个排列。


---

---
title: "[蓝桥杯 2022 省 A] 选数异或"
layout: "post"
diff: 普及+/提高
pid: P8773
tag: ['2020', '线段树', '2022', 'ST 表', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 选数异或
## 题目描述

给定一个长度为 $n$ 的数列 $A_{1}, A_{2}, \cdots, A_{n}$ 和一个非负整数 $x$, 给定 $m$ 次查询, 每次询问能否从某个区间 $[l, r]$ 中选择两个数使得他们的异或等于 $x$ 。

## 输入格式

输入的第一行包含三个整数 $n, m, x$ 。

第二行包含 $n$ 个整数 $A_{1}, A_{2}, \cdots, A_{n}$。

接下来 $m$ 行，每行包含两个整数 $l_{i}, r_{i}$ 表示询问区间 $\left[l_{i}, r_{i}\right]$ 。

## 输出格式

对于每个询问, 如果该区间内存在两个数的异或为 $x$ 则输出 `yes`, 否则输出 `no`。
## 样例

### 样例输入 #1
```
4 4 1
1 2 3 4
1 4
1 2
2 3
3 3
```
### 样例输出 #1
```
yes
no
yes
no
```
## 提示

**【样例说明】**

显然整个数列中只有 2,3 的异或为 1 。

**【评测用例规模与约定】**

对于 $20 \%$ 的评测用例, $1 \leq n, m \leq 100$;

对于 $40 \%$ 的评测用例, $1 \leq n, m \leq 1000$;

对于所有评测用例, $1 \leq n, m \leq 10^5,0 \leq x<2^{20}, 1 \leq l_{i} \leq r_{i} \leq n$ ， $0 \leq A_{i}<2^{20}$ 。

蓝桥杯 2022 省赛 A 组 D 题。


---

---
title: "[CSP-S 2022] 策略游戏"
layout: "post"
diff: 普及+/提高
pid: P8818
tag: ['贪心', '线段树', '2022', 'O2优化', 'ST 表', 'CSP-S 提高级']
---
# [CSP-S 2022] 策略游戏
## 题目描述

小 L 和小 Q 在玩一个策略游戏。

有一个长度为 $n$ 的数组 $A$ 和一个长度为 $m$ 的数组 $B$，在此基础上定义一个大小为 $n \times m$ 的矩阵 $C$，满足 $C_{i j} = A_i \times B_j$。所有下标均从 $1$ 开始。

游戏一共会进行 $q$ 轮，在每一轮游戏中，会事先给出 $4$ 个参数 $l_1, r_1, l_2, r_2$，满足 $1 \le l_1 \le r_1 \le n$、$1 \le l_2 \le r_2 \le m$。

游戏中，小 L 先选择一个 $l_1 \sim r_1$ 之间的下标 $x$，然后小 Q 选择一个 $l_2 \sim r_2$ 之间的下标 $y$。定义这一轮游戏中二人的得分是 $C_{x y}$。

小 L 的目标是使得这个得分尽可能大，小 Q 的目标是使得这个得分尽可能小。同时两人都是足够聪明的玩家，每次都会采用最优的策略。

请问：按照二人的最优策略，每轮游戏的得分分别是多少？
## 输入格式

第一行输入三个正整数 $n, m, q$，分别表示数组 $A$，数组 $B$ 的长度和游戏轮数。

第二行：$n$ 个整数，表示 $A_i$，分别表示数组 $A$ 的元素。

第三行：$m$ 个整数，表示 $B_i$，分别表示数组 $B$ 的元素。

接下来 $q$ 行，每行四个正整数，表示这一次游戏的 $l_1, r_1, l_2, r_2$。
## 输出格式

输出共 $q$ 行，每行一个整数，分别表示每一轮游戏中，小 L 和小 Q 在最优策略下的得分。
## 样例

### 样例输入 #1
```
3 2 2
0 1 -2
-3 4
1 3 1 2
2 3 2 2

```
### 样例输出 #1
```
0
4

```
### 样例输入 #2
```
6 4 5
3 -1 -2 1 2 0
1 2 -1 -3
1 6 1 4
1 5 1 4
1 4 1 2
2 6 3 4
2 5 2 3

```
### 样例输出 #2
```
0
-2
3
2
-1

```
## 提示

**【样例解释 \#1】**

这组数据中，矩阵 $C$ 如下：

$$ \begin{bmatrix} 0 & 0 \\ -3 & 4 \\ 6 & -8 \end{bmatrix} $$

在第一轮游戏中，无论小 L 选取的是 $x = 2$ 还是 $x = 3$，小 Q 都有办法选择某个 $y$ 使得最终的得分为负数。因此小 L 选择 $x = 1$ 是最优的，因为这样得分一定为 $0$。

而在第二轮游戏中，由于小 L 可以选 $x = 2$，小 Q 只能选 $y = 2$，如此得分为 $4$。

**【样例 \#3】**

见附件中的 `game/game3.in` 与 `game/game3.ans`。

**【样例 \#4】**

见附件中的 `game/game4.in` 与 `game/game4.ans`。

**【数据范围】**

对于所有数据，$1 \le n, m, q \le {10}^5$，$-{10}^9 \le A_i, B_i \le {10}^9$。对于每轮游戏而言，$1 \le l_1 \le r_1 \le n$，$1 \le l_2 \le r_2 \le m$。

| 测试点编号 | $n, m, q \le$ | 特殊条件 |
|:-:|:-:|:-:|
| $1$ | $200$ | 1, 2 |
| $2$ | $200$ | 1 |
| $3$ | $200$ | 2 |
| $4 \sim 5$ | $200$ | 无 |
| $6$ | $1000$ | 1, 2 |
| $7 \sim 8$ | $1000$ | 1 |
| $9 \sim 10$ | $1000$ | 2 |
| $11 \sim 12$ | $1000$ | 无 |
| $13$ | ${10}^5$ | 1, 2 |
| $14 \sim 15$ | ${10}^5$ | 1 |
| $16 \sim 17$ | ${10}^5$ | 2 |
| $18 \sim 20$ | ${10}^5$ | 无 |

其中，特殊性质 1 为：保证 $A_i, B_i > 0$。  
特殊性质 2 为：保证对于每轮游戏而言，要么 $l_1 = r_1$，要么 $l_2 = r_2$。


---

---
title: "[CCC 2021 S5]  Math Homework"
layout: "post"
diff: 普及+/提高
pid: P9027
tag: ['线段树', '2021', 'Special Judge', 'CCC（加拿大）', 'ST 表', '构造']
---
# [CCC 2021 S5]  Math Homework
## 题目描述

构造一个长度为 $N$ 的整数序列 $A$，使得：

1. $\forall i,1\leq A_i\leq 10^9$；
2. $\forall i,\gcd(A_{X_i},A_{X_i+1},\cdots,A_{Y_i})=Z_i$。

或者报告无解。
## 输入格式

第一行，$N,M$。

接下来 $M$ 行，每行有 $X_i,Y_i,Z_i$，描述一个限制 2.
## 输出格式

一行，序列 $A$，或者 `Impossible`。
## 样例

### 样例输入 #1
```
2 2
1 2 2
2 2 6

```
### 样例输出 #1
```
4 6
```
### 样例输入 #2
```
2 2
1 2 2
2 2 5

```
### 样例输出 #2
```
Impossible
```
## 提示

$$1\leq N\leq 150000,1\leq M\leq 150000,1\leq Z_i\leq 16$$

译自 [CCC2021 S5](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

spj 在附件里，发现锅了请联系[我](/user/90693)。


---

---
title: "「LAOI-1」小熊游景点"
layout: "post"
diff: 普及+/提高
pid: P9487
tag: ['线段树', '倍增', '洛谷原创', 'O2优化', '树形 DP', '树链剖分', 'ST 表', '分类讨论']
---
# 「LAOI-1」小熊游景点
## 题目描述

小熊的地图上有 $n$ 个景点，每个景点有分数 $s_i$。

$n-1$ 个点对之间有双向直达的公交线路，每条线路有收费 $w_i$。

现在小熊在 $a$ 景点，总司令在 $b$ 景点，他们要**沿简单路径**在 $a\to b$ 路径上的 $p$ 景点汇合，然后**沿简单路径**一起去 $q$ 景点。（$q$ 为任意点，每个人不会游览两次 $p$ 景点）

$m$ 次询问，给定 $a,b$，求 $p,q$，使得小熊和总司令花费之和最小的前提下他们经过的景点分数之和最大，输出他们经过的景点分数之和。（指小熊经过的景点分数之和 $+$ 总司令经过的景点分数之和）

**重复经过的线路收费重复计算，重复经过的景点分数重复计算。**
## 输入格式

第一行两个整数 $n,m$。分别表示景点个数和询问次数。

接下来一行 $n$ 个整数 第 $i$ 个整数 $s_i$ 表示第 $i$ 个景点的权值。

接下来 $n-1$ 行，每行 $3$ 个整数 $u,v,w$，表示 $u$ 节点和 $v$ 节点之间有一条收费 $w$ 的双向公交路线。

接下来 $m$ 行，每行两个整数 $a$ 和 $b$，表示小熊和总司令所在的景点位置。
## 输出格式

对于每组询问，每行输出一个整数表示结果。
## 样例

### 样例输入 #1
```
7 1
1 1 1 1 1 1 1
1 2 3
3 6 -4
2 5 2
1 3 6
2 4 1
3 7 5
4 7
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10 10
786755 -687509 368192 154769 647117 -713535 337677 913223 -389809 -824004 
1 2 -785875
1 3 -77082
1 4 -973070
3 5 -97388
2 6 -112274
3 7 657757
4 8 741733
3 9 5656
4 10 -35190
3 3
3 10
7 3
5 1
2 10
10 10
1 6
7 2
8 9
9 1

```
### 样例输出 #2
```
971424
-1257332
1309101
3420605
-2313033
-2567048
-2467802
352646
759321
1368370

```
## 提示

### 样例说明
对于第一组样例，小熊的地图如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ktyzyrx7.png)

其中 $a=4,b=7$，令 $p=3,q=6$。

小熊的路径为 $4\to2\to1\to3\to6$，花费之和为 $1+3+6+(-4)=6$，景点分数之和为 $1+1+1+1+1=5$。

总司令的路径为 $7\to3\to6$，花费之和为 $5+(-4)=1$，景点分数之和为 $1+1+1=3$。

小熊和总司令花费之和为 $6+1=7$，经过的景点分数之和为 $5+3=8$。

可以证明此时小熊和总司令花费之和最小的前提下他们经过的景点分数之和最大。

------------

### 数据范围
**本题采用捆绑测试。**

| Subtask | $n,m$ | $s_i,w_i$ | 特殊性质 | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $=3\times10^5$ | $\in\lbrack0,10^6\rbrack$ | 无 | $10$ |
| $2$ | $=3\times10^5$ | $\in\lbrack-10^6,10^6\rbrack$ | 小熊的地图是一条链 | $10$ |
| $3$ | $=3\times10^2$ | $\in\lbrack-10^6,10^6\rbrack$ | 无 | $5$ |
| $4$ | $=3\times10^3$ | $\in\lbrack-10^6,10^6\rbrack$ | 无 | $15$ |
| $5$ | $\le 3\times10^5$ | $\in\lbrack-10^6,10^6\rbrack$ | 无 | $60$ |

对于 $100\%$ 的数据，$1\le n,m\le 3\times 10^5$，$\vert s_i\vert,\vert w_i\vert\le10^6$，小熊的地图是一棵树。

（小熊都可以游览景点了，公交价格和景点分数怎么不可以是负数呢？）


---

---
title: "「TFOI R1」Tree Home"
layout: "post"
diff: 普及+/提高
pid: P9704
tag: ['线段树', 'O2优化', 'ST 表']
---
# 「TFOI R1」Tree Home
## 题目背景

阳光开朗大男孩天才 Z 今天要向蕉太狼表白力！

众所周知，蕉太狼是一个很可爱的女孩纸。
从前的天才 Z 总是担心因为自己表白失败而受到别人的嘲笑。但是今天，天才 Z 就要做出自己一生中最重要的一件事，那就是真诚地表白，无论后果如何。

出乎意料，蕉太狼其实也喜欢着天才 Z！

天才 Z 开心得像个 0#。

但是没过多久，天才 Z 就被甩力，原因蕉太狼发现天才 Z 对自己的闺蜜有非分之想。

天才 Z 拿出了自己的树状家谱，问候起了自己的祖宗们。
## 题目描述

有一个由 $n - 1$ 条**带权无向边**连接成的有 $n$ 个节点的树，每个节点都有它对应的**编号**以及**权值** $v_{i}$，整棵树的根节点为编号为 $1$ 的节点。

令 $f(a, b, c) = (a - b) \times \left[a^2 + b^2 + a \times b + 3 \times c \times (a + b + c)\right]$，其中 $a,b,c$ 可以为任意整数。同时用 $d_i$ 表示 $i$ 到根节点的每条边的**边权**之和。

现在天才 Z 要进行 $T$ 次询问，每次询问给定四个正整数 $l_{1},r_{1},l_{2},r_{2}$，你要从**编号**在区间 $[l_{1}, r_{1}]$ 和 $[l_{2}, r_{2}]$ 的点中各选择一个点 $p$ 和 $q$，当然你选择的两个点需要保证 $p \neq q$。用 $r$ 表示 $p$ 和 $q$ 的最近公共祖先，要使得 $|f(d_{p} - d_{r}, d_{q} - d_{r}, d_{r})| + |v_{p} - v_{q}|$ 的值最大，而你需要对每次询问输出这个最大值。
## 输入格式

第一行输入两个正整数 $n$ 和 $T$，表示这棵树的节点个数以及询问次数。

第二行输入 $n$ 个整数，第 $i$ 个数表示编号为 $i$ 的节点的权值。

接下来 $n - 1$ 行，每行输入三个整数 $u,v,w$，表示节点 $u$ 到节点 $v$ 之间有一条边权为 $w$ 的无向边。

接下来 $T$ 行，每行输入四个整数 $l_{1},r_{1},l_{2},r_{2}$，表示一次询问（意义如题面所述）。
## 输出格式

输出 $T$ 行，每行输出一个整数，表示每次询问的答案。
## 样例

### 样例输入 #1
```
7 2
5 1 7 12 5 9 6
1 2 5
3 1 1
6 2 9
4 6 14
7 6 4
5 2 10
2 4 5 7
1 1 3 3
```
### 样例输出 #1
```
19211
3
```
## 提示

#### 样例解释

对于第一次询问，我们在两个区间分别取 $4$ 号点和 $6$ 号点即可得出答案 $19211$。

对于第二次询问，两个区间都只能取一个节点，所以答案为 $3$。


#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$1 \leqslant n, T \leqslant 10$。
- Subtask 2（10 points）：$1 \leqslant n, T \leqslant 100$。
- Subtask 3（30 points）：$1 \leqslant n, T \leqslant 3000$。
- Subtask 4（55 points）：无特殊限制。

对于所有数据，$1 \leqslant n, T \leqslant 2 \times 10^5$，$0 \leqslant |w| \leqslant 25$，$1 \leqslant v_{x} \leqslant 10^9$，$1 \leqslant l_{1} \leqslant r_{1} \leqslant n$，$1 \leqslant l_{2} \leqslant r_{2} \leqslant n$，保证树中最大深度不超过 $100$。

**注意：两个区间 $[l_{1}, r_{1}]$ 和 $[l_{2}, r_{2}]$ 可能有重合部分。**


---

