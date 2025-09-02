---
title: "『STA - R4』踱步"
layout: "post"
diff: 提高+/省选-
pid: P10119
tag: ['动态规划 DP', '单调队列', 'O2优化', '动态规划优化', '前缀和']
---
# 『STA - R4』踱步
## 题目描述

小 X 特别喜欢安静的环境，因为那可以让他心情愉悦。

现在给出 $N$ 分钟内每分钟屋内和屋外对小 X 的心情影响值，在这 $N$ 分钟内，小 X 可以从屋内踱步到屋外或是从屋外踱步到屋内**最多共** $K$ 次。（小 X 当且仅当每分钟初进行踱步，同一时刻至多踱步一次，并且踱步的时间忽略不计。第 $1$ 分钟初不可踱步，第 $N$ 分钟初可以踱步。但是在第 $1$ 分钟初可以自由选择初始状态）。

同时，过于频繁的改变会让小 X 心情烦躁，所以如果两次踱步的间隔**小于等于** $T$ 分钟，会对小 X 的心情额外造成 $P$ 点影响。（如果此次踱步是在第 $t_a$ 分钟初，上一次踱步是在第 $t_b$ 分钟初，那么这两次踱步的时间间隔为 $t_a - t_b$ 分钟）。

小 X 想知道自己的心情最好可以是多少，即第 $N$ 分钟末小 X 心情值的最大值。

若某一时刻小 X 的心情值为 $a$，之后小 X 的心情被影响了 $b$，那么在此之后小 X 的心情值将变为 $a + b$。
## 输入格式

**本题单个测试点内含有多组测试数据。**

第一行两个正整数 $\text{id},\text{TEST}$。其中 $\text{id}$ 代表 Subtask 编号，$\text{TEST}$ 代表测试数据组数。特别的，样例的 $\text{id}$ 为 $0$。

对于每组测试数据：

第一行为四个整数 $N, K, T, P$。

接下来 $N$ 行每行两个整数。其中第 $i$ 行的两个整数 $a_i, b_i$ 分别代表第 $i$ 分钟屋内和屋外对小 X 心情的影响值。
## 输出格式

对于每组测试数据，输出一行一个整数，代表第 $N$ 分钟末小 X 心情值的最大值。
## 样例

### 样例输入 #1
```
0 2
8 3 2 3
0 -2
5 -10
8 0
-10 -7
0 -3
-4 -9
-9 -3
-7 0
8 3 2 -6
9 6
9 -6
3 7
-4 3
8 -9
6 0
-10 9
-8 -4

```
### 样例输出 #1
```
5
36

```
### 样例输入 #2
```
0 1
12 3 2 -35771156
797235777 25138038
801541087 -405462832
936777370 -973167834
74493410 60154946
263320806 782480907
-940214410 805511853
806065179 463119365
-295177485 -112301429
-403964212 202831413
122359196 611468120
-555210139 549749508
793784715 -38433603

```
### 样例输出 #2
```
6706692096

```
### 样例输入 #3
```
0 1
5 2 1 -100
-44 -72
-36 -23
-4 0
-22 -1
-88 3

```
### 样例输出 #3
```
-65

```
## 提示

**【样例 #1 解释】**

对于第 $1$ 组数据，最优方案为初始时选择在屋内，分别在第 $4, 5, 7$ 分钟初进行踱步。

![](https://cdn.luogu.com.cn/upload/image_hosting/cx7tr8m2.png)

其中第 $2$ 次踱步与第 $1$ 次踱步之间的间隔为 $5 - 4 = 1$ 分钟，对小 $\text{X}$ 的心情产生 $3$ 的贡献，第 $3$ 次踱步与第 $2$ 次踱步之间的间隔为 $7 - 5 = 2$ 分钟，对小 X 的心情产生 $3$ 的贡献。

因此小 X 的心情值为

$$\left(0+5+8-7+0-4-3+0\right) + 6 = 5$$

前半部分为灰色格子的权值和，后半部分为两次频繁踱步产生的额外贡献，可以证明此方案最优。

**【样例 #2 解释】**

请注意答案可能超过 $32$ 位整型数字的范围。

**【样例 #3 解释】**

请注意答案可能为负数。


**【数据范围】**

对于 $100\%$ 的数据：

- $1 \le \text{TEST} \le 10^5$；
- $2 \le N \le 2 \times 10^5$；
- $1 \le K \le \min\left\{200, N\right\}$；
- $1 \le T \le \min\left\{2 \times 10^4, N\right\}$；
- $\left\lvert a_i \right\rvert,\left\lvert b_i \right\rvert,\left\lvert P \right\rvert \le 10^9$。
- $\sum N \cdot K \le 5 \times 10^7$。
- 保证单个测试点输入数据规模不超过 10 MB。

**本题采用捆绑测试。**

|Subtask 编号|数据范围|分值|依赖子任务|
|:--------:|:--------:|:--------:|:--------:|
|1|$N \le 20, \text{TEST} \le 10$|$5$||
|2|$\sum N^2K \le 5 \times 10^7$|$20$|$1$|
|3|$K \le 5, N \le 5 \times 10^4, \text{TEST} \le 10$|$15$||
|4|$P=-10^9, 0 \le \left\lvert a_i \right\rvert,\left\lvert b_i \right\rvert \le 100$|$30$||
|5|无特殊限制|$30$|$1,2,3,4$|


---

---
title: "「SMOI-R1」Game"
layout: "post"
diff: 提高+/省选-
pid: P10407
tag: ['动态规划 DP', '单调队列']
---
# 「SMOI-R1」Game
## 题目背景

myz 很喜欢玩一款病毒游戏。
## 题目描述

在这个游戏里，一开始有 $n$ 个病毒，每个病毒的危害值为 $1$。

每隔一段时间，病毒就会变异，会分裂成两个病毒，右边的病毒会比左边的病毒危害值多 $1$，变异过的病毒不会再变异。

每个病毒有个变异极限 $b_i$，当这个病毒变异到 $b_i$ 时，这个病毒就会停止变异。也就是说，第 $i$ 个病毒最后都会分裂成一个危害值为 $\{1,2,3,\ldots,b_i\}$ 的病毒序列，当所有病毒变异完时，游戏开始，最终变异完的序列是 $\{1,2,3,\ldots,b_1,1,2,3,\ldots,b_2,\ldots,1,2,3,\ldots,b_n\}$。

每次游戏，系统会选择一个区间，myz 需要把这个区间的病毒全部杀死，如果这个区间内的病毒的危害值的最大值是 $x$，那么 myz 需要花费 $x$ 的能量才能消灭它们。

因为不知道系统会选择哪个区间，myz 想知道每个区间需要消耗的**能量值之和**。

由于答案太大了，myz 想让你把答案对 $998244353$ 取模。
## 输入格式

第一行有一个整数 $n$，表示最开始有 $n$ 个病毒。

第二行有 $n$ 个整数，第 $i$ 个整数是 $b_i$，表示第 $i$ 个病毒的变异上限。
## 输出格式

一个整数，表示 myz 需要消耗的能量值之和，答案对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
2
2 3
```
### 样例输出 #1
```
33
```
## 提示

### 样例解释
第一个样例，病毒最后分裂成 $\{1,2,1,2,3\}$，区间  $[1,1],[1,2],[1,3],[1,4],[1,5],[2,2],[2,3],[2,4],[2,5],[3,3],[3,4],[3,5],[4,4],[4,5],[5,5]$ 的最小代价和就是 $1+2+2+2+3+2+2+2+3+1+2+3+2+3+3=33$。

### 数据范围
**本题采用捆绑测试**。

subtask 编号|$n\leq$|$b_i\leq$|特殊性质|分值
-|-|-|-|-
$1$|$10^2$|$10^2$|无|$20$
$2$|$10^4$|$10^2$|无|$20$
$3$|$10^6$|$10^9$|A|$20$
$4$|$10^6$|$10^9$|无|$40$

**特殊性质 A**： $b_1 \leq b_2 \leq \ldots \leq b_n$。

对于 $100\%$ 的数据，保证 $1\le n\le10^6$，$1\le b_i\le 10^9$。


---

---
title: "[蓝桥杯 2025 省 A] 扫地机器人"
layout: "post"
diff: 提高+/省选-
pid: P12145
tag: ['线段树', '单调队列', '2025', '树形 DP', '树的直径', 'ST 表', '基环树', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A] 扫地机器人
## 题目描述

在一个含有 $n$ 个点 $n$ 条边的无重边无自环的连通无向图中，有一个扫地机器人在执行清扫作业。其中结点 $i$ 的标记 $t_i \in \{0,1\}$：如果为 $1$，则说明该结点需要进行清扫，扫地机器人在到达这个结点时会顺便进行清扫工作。机器人想知道，如果选定任意结点出发，每条边只能经过一次的话，最多能清扫多少个待清扫结点？
## 输入格式

输入的第一行包含一个正整数 $n$。

第二行包含 $n$ 个整数 $t_1, t_2, \cdots, t_n$，相邻整数之间使用一个空格分隔。

接下来 $n$ 行，每行包含两个正整数 $u_i, v_i$，用一个空格分隔，表示结点 $u_i$ 和结点 $v_i$ 之间有一条边。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
9
1 0 1 0 0 1 1 0 1
2 8
2 9
2 5
1 5
1 3
1 4
4 5
4 6
6 7
```
### 样例输出 #1
```
4
```
## 提示

### 样例说明
其中一种可行路线：$3 \rightarrow 1 \rightarrow 4 \rightarrow 6 \rightarrow 7$，清扫结点 $3, 1, 6, 7$（共 $4$ 个）。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 5000$；
- 对于所有评测用例，$1 \leq n \leq 500000$，$t_i \in \{0,1\}$，$1 \leq u_i, v_i \leq n$。


---

---
title: "[UTS 2024] Matrix"
layout: "post"
diff: 提高+/省选-
pid: P12561
tag: ['递推', '倍增', '单调队列', '2024', 'UOI（乌克兰）']
---
# [UTS 2024] Matrix
## 题目描述

You are given a matrix of size $n \times m$ consisting of elements $a_{i,j}$. 

We call a **triangle** on the matrix of size $k$ starting at point $(x;y)$ a set of points that can be reached from $(x;y)$ in no more than $k$ steps going either up or right. 

You are asked to find for each $(x;y)$ $(k \le x \le n, 1 \le y \le m-k+1)$ the following values:

- The maximal value in the triangle of size $k$ starting at point $(x;y)$;
- The number of occurrences of the maximal value in that triangle.
## 输入格式

The first line contains three integers $n$, $m$, and $k$ $(1 \le n,m \le 2\,000, 1 \le k \le \min(n,m))$ --- dimensions of the matrix and the size of the triangle.

The following $n$ lines contain $m$ integers $a_{i,j}$ $(0 \le a_{i,j} \le 10^6)$ --- description of the matrix.
## 输出格式

Print two matrices of size $(n-k+1)\times(m-k+1)$. 

The first matrix in position $(i;j)$ should contain the maximal value of a triangle of size $k$ starting at $(i+k-1;j)$.

The second matrix in position $(i;j)$ should contain the number of occurrences of the maximal value in the triangle of size $k$ starting at $(i+k-1;j)$.
## 样例

### 样例输入 #1
```
4 4 2
1 2 6 14
12 3 13 5
11 4 7 8
10 16 9 15
```
### 样例输出 #1
```
12 13 13 
12 7 13 
16 16 15 
1 1 1 
1 1 1 
1 1 1 
```
## 提示

- ($5$ points) $n,m \le 20$;
- ($10$ points) $n,m \le 100$;
- ($30$ points) $a_{i,j} \le 1$;
- ($35$ points) $n,m \le 1\,000$;
- ($20$ points) no additional restrictions.


---

---
title: "[USACO04DEC] Dividing the Path G"
layout: "post"
diff: 提高+/省选-
pid: P1545
tag: ['动态规划 DP', '2004', '线段树', 'USACO', '单调队列', '动态规划优化']
---
# [USACO04DEC] Dividing the Path G
## 题目描述

约翰的奶牛们发现山脊上的草特别美味。为了维持草的生长，约翰打算安装若干喷灌器。

为简化问题，山脊可以看成一维的数轴，长为 $L\ (1\le L\le 10^6)$，而且 $L$ 一定是一个偶数。每个喷灌器可以双向喷灌，并有确定的射程，该射程不短于 $A$，不长于 $B$，$A$，$B(1\le A\le B\le 10^3)$ 都是给出的正整数。它所在位置的两边射程内，都属它的灌溉区域。

现要求山脊的每一个区域都被灌溉到，而且喷灌器的灌溉区域不允许重叠。约翰有 $N(1\le N\le 10^3)$ 只奶牛，每一只都有特别喜爱的草区，第 $i$ 奶牛的草区是 $[S_i,E_i]$，不同奶牛的草区可以重叠。现要求，每只奶牛的草区仅被一个喷灌器灌溉。

注意：

1. 数轴 $L$ 从 $0$ 开始标记（即坐标范围 $0\sim L$）  
2. 喷灌器坐标和射程必须为整数，对于坐标为 $i$ 射程为 $x$ 的喷灌器，它的灌溉范围为 $[i-x,i+x]$。
3. 浇灌区间必须在山脊范围内。例如，不能在 $0$ 位置放一个半径为 $1$ 的浇灌器。

寻找最少需要的喷灌器数目。
## 输入格式

第一行两个整数 $N,L$。

第二行两个整数 $A,B$。

然后 $N$ 行每一行两个整数 $S_i,E_i$（$1\le S_i < E_i\le L$）。
## 输出格式

一行，输出所需的最少洒水器数量。如果无法为农夫约翰设计喷头配置，则输出 $-1$。
## 样例

### 样例输入 #1
```
2 8
1 2
6 7
3 6
```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的数据，$1\le L\le 10^6$，$1\le A,B\le 10^3$，$1\le N\le 10^3$，$1\le S_i<E_i\le L$。

样例解释：

![](https://vj.csgrandeur.cn/d4313c41a71f91cdadfcba2601cf5034?v=1699442455)


---

---
title: "[HAOI2007] 修筑绿化带"
layout: "post"
diff: 提高+/省选-
pid: P2219
tag: ['2007', '河南', '各省省选', '平衡树', '单调队列', '队列']
---
# [HAOI2007] 修筑绿化带
## 题目描述

为了增添公园的景致，现在需要在公园中修筑一个花坛，同时在花坛四周修建一片绿化带，让花坛被绿化带围起来。

如果把公园看成一个 $M\times N$ 的矩形，那么花坛可以看成一个 $C\times D$ 的矩形，绿化带和花坛一起可以看成一个 $A\times B$ 的矩形。

如果将花园中的每一块土地的“肥沃度”定义为该块土地上每一个小块肥沃度之和，那么，绿化带的肥沃度为 $A\times B$ 块的肥沃度减去 $C\times D$ 块的肥沃度。

为了使得绿化带的生长得旺盛，我们希望绿化带的肥沃度最大。
## 输入格式

第一行有六个正整数 $M,N,A,B,C,D$。

接下来一个 $M\times N$ 的数字矩阵，其中矩阵的第 $i$ 行 $j$ 列元素为一个整数 $x_{i,j}$，表示该花园的第 $i$ 行第 $j$ 列的土地 “肥沃度”。
## 输出格式

一个正整数，表示绿化带的最大肥沃程度。

## 样例

### 样例输入 #1
```
4 5 4 4 2 2
20 19 18 17 16
15 14 13 12 11
10 9 8 7 6
5 4 3 2 1

```
### 样例输出 #1
```
132
```
## 提示

对于 $30\%$ 的数据，$1\leq M,N\leq 50$。

对于 $100\%$ 的数据，$1\leq M,N\leq 1000$，$1\leq A\leq M$，$1\leq B\leq N$，$1\leq C\leq A-2$，$1\leq D\leq B-2$，$1\leq x_{i,j}\leq 100$。


---

---
title: "[NOI2005] 瑰丽华尔兹"
layout: "post"
diff: 提高+/省选-
pid: P2254
tag: ['动态规划 DP', '2005', '单调队列', 'NOI', '队列']
---
# [NOI2005] 瑰丽华尔兹
## 题目背景

你跳过华尔兹吗？当音乐响起，当你随着旋律滑动舞步，是不是有一种漫步仙境的惬意？

众所周知，跳华尔兹时，最重要的是有好的音乐。但是很少有几个人知道，世界上最伟大的钢琴家一生都漂泊在大海上，他的名字叫丹尼・布德曼・T.D.・柠檬・1900，朋友们都叫他 1900。

1900 在 20 世纪的第一年出生在往返于欧美的邮轮弗吉尼亚号上。很不幸，他刚出生就被抛弃，成了孤儿。1900 孤独的成长在弗吉尼亚号上，从未离开过这个摇晃的世界。也许是对他命运的补偿，上帝派可爱的小天使艾米丽照顾他。可能是天使的点化，1900 拥有不可思议的钢琴天赋：从未有人教，从没看过乐谱，但他却能凭着自己的感觉弹出最沁人心脾的旋律。当 1900 的音乐获得邮轮上所有人的欢迎时，他才 8 岁，而此时，他已经乘着海轮往返欧美大陆 50 余次了。

虽说是钢琴奇才，但 1900 还是个孩子，他有着和一般男孩一样的好奇和调皮，只不过更多一层浪漫的色彩罢了：这是一个风雨交加的夜晚，海风卷起层层巨浪拍打着弗吉尼亚号，邮轮随着巨浪剧烈的摇摆。船上的新萨克斯手迈克斯・托尼晕船了，1900 招呼托尼和他一起坐到舞厅里的钢琴上，然后松开了固定钢琴的闸，于是，钢琴随着海轮的倾斜滑动起来。准确的说，我们的主角 1900…

## 题目描述

不妨认为舞厅是一个 $N$ 行 $M$ 列的矩阵，矩阵中的某些方格上堆放了一些家具，其他的则是空地。钢琴可以在空地上滑动，但不能撞上家具或滑出舞厅，否则会损坏钢琴和家具，引来难缠的船长。每个时刻，钢琴都会随着船体倾斜的方向向相邻的方格滑动一格，相邻的方格可以是向东、向西、向南或向北的。而艾米丽可以选择施魔法或不施魔法：如果不施魔法，则钢琴会滑动；如果施魔法，则钢琴会原地不动。

艾米丽是个天使，她知道每段时间的船体的倾斜情况。她想使钢琴在舞厅里滑行的路程尽量长，这样 1900 会非常高兴，同时也有利于治疗托尼的晕船。但艾米丽还太小，不会算，所以希望你能帮助她。

## 输入格式

输入文件的第一行包含 $5$ 个数 $N$, $M$, $x$, $y$ 和 $K$。$N$ 和 $M$ 描述舞厅的大小，$x$ 和 $y$ 为钢琴的初始位置；我们对船体倾斜情况是按时间的区间来描述的，且从 $1$ 开始计算时间，比如 “在 $[1, 3]$ 时间里向东倾斜，$[4, 5]$ 时间里向北倾斜”，因此这里的 $K$ 表示区间的数目。

以下 $N$ 行，每行 $M$ 个字符，描述舞厅里的家具。第 $i$ 行第 $j$ 列的字符若为 `.`，则表示该位置是空地；若为 `x`，则表示有家具。

以下 $K$ 行，顺序描述 $K$ 个时间区间，格式为：$s_i\ t_i\ d_i (1 \leq i \leq K)$。表示在时间区间 $[s_i, t_i]$ 内，船体都是向 $d_i$ 方向倾斜的。$d_i$ 为 $1$, $2$, $3$, $4$ 中的一个，依次表示北、南、西、东（分别对应矩阵中的上、下、左、右）。输入保证区间是连续的，即

$s_1 = 1$，$s_i = t_{i-1} + 1 (1 < i \leq K)$，$t_K = T$。
## 输出格式

输出文件仅有 $1$ 行，包含一个整数，表示钢琴滑行的最长距离 (即格子数)。

## 样例

### 样例输入 #1
```
4 5 4 1 3
..xx.
.....
...x.
.....
1 3 4
4 5 1
6 7 3
```
### 样例输出 #1
```
6
```
## 提示

钢琴的滑行路线：

 ![](https://cdn.luogu.com.cn/upload/pic/1307.png) 

钢琴在“×”位置上时天使使用一次魔法，因此滑动总长度为 $6$。

【数据范围】

$50\%$ 的数据中，$1\leq N, M\leq 200，T\leq 200$；

$100\%$ 的数据中，$1\leq N$, $M \leq 200$，$K \leq 200$，$T\leq 40000$。



---

---
title: "[SCOI2010] 股票交易"
layout: "post"
diff: 提高+/省选-
pid: P2569
tag: ['动态规划 DP', '2010', '四川', '各省省选', '单调队列', '队列']
---
# [SCOI2010] 股票交易
## 题目描述

最近 $\text{lxhgww}$ 又迷上了投资股票，通过一段时间的观察和学习，他总结出了股票行情的一些规律。

通过一段时间的观察，$\text{lxhgww}$ 预测到了未来 $T$ 天内某只股票的走势，第 $i$ 天的股票买入价为每股 $AP_i$，第 $i$ 天的股票卖出价为每股 $BP_i$（数据保证对于每个 $i$，都有 $AP_i \geq BP_i$），但是每天不能无限制地交易，于是股票交易所规定第 $i$ 天的一次买入至多只能购买 $AS_i$ 股，一次卖出至多只能卖出 $BS_i$ 股。

另外，股票交易所还制定了两个规定。为了避免大家疯狂交易，股票交易所规定在两次交易（某一天的买入或者卖出均算是一次交易）之间，至少要间隔 $W$ 天，也就是说如果在第 $i$ 天发生了交易，那么从第 $i+1$ 天到第 $i+W$ 天，均不能发生交易。同时，为了避免垄断，股票交易所还规定在任何时间，一个人的手里的股票数不能超过 $\text{MaxP}$。

在第 $1$ 天之前，$\text{lxhgww}$ 手里有一大笔钱（可以认为钱的数目无限），但是没有任何股票，当然，$T$ 天以后，$\text{lxhgww}$ 想要赚到最多的钱，聪明的程序员们，你们能帮助他吗？


## 输入格式

输入数据第一行包括 $3$ 个整数，分别是 $T$，$\text{MaxP}$，$W$。

接下来 $T$ 行，第 $i$ 行代表第 $i-1$ 天的股票走势，每行 $4$ 个整数，分别表示 $AP_i,\ BP_i,\ AS_i,\ BS_i$。
## 输出格式

输出数据为一行，包括 $1$ 个数字，表示 $\text{lxhgww}$ 能赚到的最多的钱数。
## 样例

### 样例输入 #1
```
5 2 0
2 1 1 1
2 1 1 1
3 2 1 1
4 3 1 1
5 4 1 1

```
### 样例输出 #1
```
3
```
## 提示

- 对于 $30\%$ 的数据，$0\leq W<T\leq 50,1\leq\text{MaxP}\leq50$；
- 对于 $50\%$ 的数据，$0\leq W<T\leq 2000,1\leq\text{MaxP}\leq50$；
- 对于 $100\%$ 的数据，$0\leq W<T\leq 2000,1\leq\text{MaxP}\leq2000$；
- 对于所有的数据，$1\leq BP_i\leq AP_i\leq 1000,1\leq AS_i,BS_i\leq\text{MaxP}$。


---

---
title: "[USACO12MAR] Flowerpot S"
layout: "post"
diff: 提高+/省选-
pid: P2698
tag: ['2012', '二分', 'USACO', '单调队列']
---
# [USACO12MAR] Flowerpot S
## 题目描述

Farmer John has been having trouble making his plants grow, and needs your help to water them properly.  You are given the locations of N raindrops (1 <= N <= 100,000) in the 2D plane, where y represents vertical height of the drop, and x represents its location over a 1D number line:

 ![](https://cdn.luogu.com.cn/upload/pic/9174.png) 

Each drop falls downward (towards the x axis) at a rate of 1 unit per second.  You would like to place Farmer John's flowerpot of width W somewhere along the x axis so that the difference in time between the first raindrop to hit the flowerpot and the last raindrop to hit the flowerpot is at least some amount D (so that the flowers in the pot receive plenty of water).  A drop of water that lands just on the edge of the flowerpot counts as hitting the flowerpot. 

Given the value of D and the locations of the N raindrops, please compute the minimum possible value of W.

老板需要你帮忙浇花。给出 $N$ 滴水的坐标，$y$ 表示水滴的高度，$x$ 表示它下落到 $x$ 轴的位置。

每滴水以每秒 $1$ 个单位长度的速度下落。你需要把花盆放在 $x$ 轴上的某个位置，使得从被花盆接着的第 $1$ 滴水开始，到被花盆接着的最后 $1$ 滴水结束，之间的时间差至少为 $D$。

我们认为，只要水滴落到 $x$ 轴上，与花盆的边沿对齐，就认为被接住。给出 $N$ 滴水的坐标和 $D$ 的大小，请算出最小的花盆的宽度 $W$。
## 输入格式

第一行 $2$ 个整数 $N$ 和 $D$。

接下来 $N$ 行每行 $2$ 个整数，表示水滴的坐标 $(x,y)$。
## 输出格式

仅一行 $1$ 个整数，表示最小的花盆的宽度。如果无法构造出足够宽的花盆，使得在 $D$ 单位的时间接住满足要求的水滴，则输出 $-1$。
## 样例

### 样例输入 #1
```
4 5
6 3
2 4
4 10
12 15
```
### 样例输出 #1
```
2
```
## 提示

有 $4$ 滴水，$(6,3)$ ，$(2,4)$ ，$(4,10)$ ，$(12,15)$ 。水滴必须用至少 $5$ 秒时间落入花盆。花盆的宽度为 $2$ 是必须且足够的。把花盆放在 $x=4\dots6$ 的位置，它可以接到 $1$ 和 $3$ 水滴, 之间的时间差为 $10-3=7$ 满足条件。

**【数据范围】**

$40\%$ 的数据：$1 \le N \le 1000$ ，$1 \le D \le 2000$ 。

$100\%$ 的数据：$1 \le N \le 10 ^ 5$ ，$1 \le D \le 10 ^ 6$ ，$0\le x,y\le10^6$ 。


---

---
title: "[USACO09OPEN] Bovine Embroidery G"
layout: "post"
diff: 提高+/省选-
pid: P2950
tag: ['动态规划 DP', '递推', '2009', 'USACO', '单调队列']
---
# [USACO09OPEN] Bovine Embroidery G
## 题目描述

Bessie has taken up the detailed art of bovine embroidery. Cows embroider a cloth mounted in a circular hoop of integer radius d (1 <= d <= 50,000). They sew N (2 <= N <= 50,000) threads, each in a straight line from one point on the edge of the hoop to another point on the edge of the hoop (no two embroidered points share a location on the hoop's edge).

Being mathematically inclined, Bessie knows a formula of the form ax + by + c = 0 for each straight line piece of thread. Conveniently, a, b, and c are integers (-1,000,000 <= a <= 1,000,000; -1,000,000 <= b <= 1,000,000; -1,000,000 <= c <= 1,000,000). Even more

conveniently, no two threads coincide exactly.

Perhaps less conveniently, Bessie knows that her set of formula coefficients also includes a number of formulae for threads that do not appear to pass inside the hoop's circle. She regrets this greatly.

The origin (0,0) is in the precise middle of the hoop, so all points on the hoop's edge are distance d from the origin. At least one of the coefficients a and b is non-zero for each thread's formula.

Bovine embroidery is more highly regarded when the number of thread intersections is maximized. Help Bessie: count the number of pairs of threads that intersect on the cloth (i.e., within distance d of the origin). Note that if three threads happen to coincide at the same point, that would be three pairs of intersections. Four threads at the same point -> six pairs of intersections, etc.

Bessie学会了刺绣这种精细的工作。牛们在一片半径为d(1 <= d <= 50000)的圆形布上绣花. 它们一共绣了N (2 <= N <= 50000)条直线，每条直线连接布的边缘上的两个点(没有两条线通过边上同一个点)。

作为一只热爱数学的牛，Bessie 知道每条线的公式, ax + by + c = 0. a, b, 和 c 为整数(-1000000 <= a <= 1000000; -1000000 <= b <= 1000000; -1000000 <= c <= 1000000).没有两条线完全重合。

不幸的是, 一部分线不通过圆布的内部. 原点(0,0)在布的正中央, 所有边上的点离原点距离为d. 每条线的公式满足至少a,b中的一个非零. 对于牛来说，刺绣作品中线的交点越多，便越有价值。帮助Bessie计算在圆中相交的线的对数，也就是说交点与原点的距离小于d。注意如果三条线在圆内同一点相交,这算3对线。4线共点->6对线.

## 输入格式

\* Line 1: Two space-separated integers: N and d

\* Lines 2..N+1: Line i+1 describes thread i with three integers: a, b, and c

## 输出格式

\* Line 1: One integer, on a line by itself, that is the count of pairs of threads that intersect.

## 样例

### 样例输入 #1
```
2 1 
1 0 0 
0 1 0 

```
### 样例输出 #1
```
1 

```
## 提示

The two lines are x=0 and y=0. 

The two lines intersect at (0,0), which is clearly with 1 of the origin. 




---

---
title: "[USACO11OPEN] Odd degrees G"
layout: "post"
diff: 提高+/省选-
pid: P3022
tag: ['动态规划 DP', '2011', 'USACO', '单调队列', 'Special Judge']
---
# [USACO11OPEN] Odd degrees G
## 题目描述

The cows are being invaded! Their republic comprises N (1 <= N <= 50,000) towns that are connected by M (1 <= M <= 100,000) undirected paths between two towns A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i; no duplicate paths will occur). However the republic is not necessarily connected--there may be pairs of towns that are unable to reach each other through the paths.

The cows know their invaders plan to conduct an inventory of every path within their republic, so they are willing to shut down various paths to make it as difficult as possible for their invaders to do so.

Please help the cows find a way to shut down a subset of the paths such that each town has an odd number of remaining paths connected to it, or determine if no such subset exists.

For example, consider the following cow republic: 

1---2
\ /
3---4
If we keep the paths 1-3, 2-3, and 3-4, and remove the path 1-2, then towns 1, 2, and 4 will be an endpoint of exactly one path, whereas town 3 will be an endpoint of three paths:

1   2
\ /
3---4
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 contains two space-separated integers: A\_i and B\_i

## 输出格式

\* Line 1: A single integer that is the number of paths to keep. If no subset exists output only a single line with the integer -1.

\* Lines 2..K+1: Each line contains an index of an path to keep, in the range 1..M. These indices must be pairwise distinct.

## 样例

### 样例输入 #1
```
4 4 
1 2 
2 3 
3 1 
3 4 

```
### 样例输出 #1
```
3 
2 
3 
4 

```
## 提示

感谢@cn：苏卿念 提供的Special Judge
## 题目翻译

## 题意
牛们正在被入侵。 有$N$个点，由$M$条无向边连接。 无向边从$A_i$到$B_i$。数据保证无重边，但不保证连通(即从一个点不一定能到达另一点)。

牛知道入侵他们的人正计划清点所有的边，所以他们想切掉一些边使入侵者的计划尽可能的困难

请找出一个方法，留下一些边，使每个点都只有奇数条边与之连接。并输出留下的边的方案。

下面是一个样例
```
1---2
 \ /
  3---4
我们把1——2那条边拆掉， 就会变成下图
1   2
 \ /
  3---4
对于每个点都只有奇数条边连接，符合题意
```
## 读入输出格式
 ### 读入格式
 * 第一行两个整数 $N$ 和 $M$
 * 第二到$M+1$行，每行描述一条边 有两个整数$A_i$和$B_i$
 ### 输出格式
 * 第一行一个整数 剩下边的数量，如果不可能请输出-1
 * 之后每一行一个数，边的编号(按输入顺序来)。

感谢@ToBiChi 提供翻译


---

---
title: "[USACO13JAN] Cow Lineup G"
layout: "post"
diff: 提高+/省选-
pid: P3069
tag: ['2013', 'USACO', '树状数组', '单调队列', '队列']
---
# [USACO13JAN] Cow Lineup G
## 题目描述

Farmer John's N cows (1 <= N <= 100,000) are lined up in a row.  Each cow is identified by an integer "breed ID" in the range 0...1,000,000,000; the breed ID of the ith cow in the lineup is B(i).  Multiple cows can share the same breed ID.

FJ thinks that his line of cows will look much more impressive if there is a large contiguous block of cows that all have the same breed ID.  In order to create such a block, FJ chooses up to K breed IDs and removes from his lineup all the cows having those IDs.  Please help FJ figure out the length of the largest consecutive block of cows with the same breed ID that he can create by doing this.

农夫约翰的N(1 <= N <= 100,000)只奶牛排成了一队，每只牛都用编上了一个“血统编号”，该编号为范围0...1,000,000,000的整数。血统相同的奶牛有相同的编号，也就是可能有多头奶牛是相同的"血统编号"。

约翰觉得如果连续排列的一段奶牛有相同的血统编号的话，奶牛们看起来会更具有威猛。为了创造这样的连续段，约翰最多能选出k种血统的奶牛，并把他们全部从队列中赶走。


请帮助约翰计算这样做能得到的由相同血统编号的牛构成的连续段的长度最大是多少？

## 输入格式

\* Line 1: Two space-separated integers: N and K.

\* Lines 2..1+N: Line i+1 contains the breed ID B(i). 


## 输出格式

\* Line 1: The largest size of a contiguous block of cows with

identical breed IDs that FJ can create.

## 样例

### 样例输入 #1
```
9 1 
2 
7 
3 
7 
7 
3 
7 
5 
7 

```
### 样例输出 #1
```
4 

```
## 提示

There are 9 cows in the lineup, with breed IDs 2, 7, 3, 7, 7, 3, 7, 5, 7. FJ would like to remove up to 1 breed ID from this lineup.


By removing all cows with breed ID 3, the lineup reduces to 2, 7, 7, 7, 7, 5, 7.  In this new lineup, there is a contiguous block of 4 cows with the same breed ID (7).



---

---
title: "[USACO13NOV] Pogo-Cow S"
layout: "post"
diff: 提高+/省选-
pid: P3089
tag: ['动态规划 DP', '2013', 'USACO', '单调队列', '枚举']
---
# [USACO13NOV] Pogo-Cow S
## 题目描述

In an ill-conceived attempt to enhance the mobility of his prize cow Bessie, Farmer John has attached a pogo stick to each of Bessie's legs. Bessie can now hop around quickly throughout the farm, but she has not yet learned how to slow down.

To help train Bessie to hop with greater control, Farmer John sets up a practice course for her along a straight one-dimensional path across his farm.  At various distinct positions on the path, he places N targets on which Bessie should try to land (1 <= N <= 1000).  Target i is located at position x(i), and is worth p(i) points if Bessie lands on it.  Bessie starts at the location of any target of her choosing and is allowed to move in only one direction, hopping from target to target.  Each hop must cover at least as much distance as the previous hop, and must land on a target.

Bessie receives credit for every target she touches (including the initial target on which she starts).  Please compute the maximum number of points she can obtain.

FJ给奶牛贝西的脚安装上了弹簧，使它可以在农场里快速地跳跃，但是它还没有学会如何降低速度。


FJ觉得让贝西在一条直线的一维线路上进行练习，他在不同的目标点放置了N (1 <= N <= 1000)个目标点，目标点i在目标点x(i)，该点得分为p(i)。贝西开始时可以选择站在一个目标点上，只允许朝一个方向跳跃，从一目标点跳到另外一个目标点，每次跳跃的距离至少和上一次跳跃的距离相等，并且必须跳到一个目标点。


每跳到一个目标点，贝西可以拿到该点的得分，请计算他的最大可能得分。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..1+N: Line i+1 contains x(i) and p(i), each an integer in the range 0..1,000,000.

## 输出格式

\* Line 1: The maximum number of points Bessie can receive.

## 样例

### 样例输入 #1
```
6 
5 6 
1 1 
10 5 
7 6 
4 8 
8 10 

```
### 样例输出 #1
```
25 

```
## 提示

There are 6 targets.  The first is at position x=5 and is worth 6 points, and so on.


Bessie hops from position x=4 (8 points) to position x=5 (6 points) to position x=7 (6 points) to position x=10 (5 points).



---

---
title: "[USACO13NOV] No Change G"
layout: "post"
diff: 提高+/省选-
pid: P3092
tag: ['2013', 'USACO', '单调队列', '状压 DP']
---
# [USACO13NOV] No Change G
## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1

## 输入格式

\* Line 1: Two integers, K and N.

\* Lines 2..1+K: Each line contains the amount of money of one of FJ's coins.

\* Lines 2+K..1+N+K: These N lines contain the costs of FJ's intended purchases.

## 输出格式

\* Line 1: The maximum amount of money FJ can end up with, or -1 if FJ cannot complete all of his purchases.

## 样例

### 样例输入 #1
```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 

```
### 样例输出 #1
```
12 

```
## 提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.



---

---
title: "[USACO15JAN] Cow Rectangles G"
layout: "post"
diff: 提高+/省选-
pid: P3117
tag: ['2015', 'USACO', '单调队列', '离散化', '前缀和', '扫描线']
---
# [USACO15JAN] Cow Rectangles G
## 题目描述

The locations of Farmer John's N cows (1 <= N <= 500) are described by distinct points in the 2D plane.  The cows belong to two different breeds: Holsteins and Guernseys.  Farmer John wants to build a rectangular fence with sides parallel to the coordinate axes enclosing only Holsteins, with no Guernseys (a cow counts as enclosed even if it is on the boundary of the fence).  Among all such fences, Farmer John wants to build a fence enclosing the maximum number of Holsteins.  And among all these fences, Farmer John wants to build a fence of minimum possible area.  Please determine this area.  A fence of zero width or height is allowable.

## 输入格式

The first line of input contains N.  Each of the next N lines describes a cow, and contains two integers and a character. The integers indicate a point (x,y) (0 <= x, y <= 1000) at which the cow is located. The character is H or G, indicating the cow's breed.  No two cows are located at the same point, and there is always at least one Holstein.

## 输出格式

Print two integers. The first line should contain the maximum number of Holsteins that can be enclosed by a fence containing no Guernseys, and second line should contain the minimum area enclosed by such a fence.
## 样例

### 样例输入 #1
```
5 
1 1 H 
2 2 H 
3 3 G 
4 4 H 
6 6 H 

```
### 样例输出 #1
```
2 
1 
```
## 题目翻译

### 题目描述

农夫约翰的 $N$ 头牛（$1 \leq N \leq 500$）的位置由二维平面上互不相同的点描述。这些牛分为两个品种：Holsteins 和 Guernseys。农夫约翰希望建造一个边与坐标轴平行的矩形围栏，仅包含 Holsteins 且不包含任何 Guernseys（即使牛位于围栏边界上也视为被包含）。在所有满足条件的围栏中，农夫约翰希望选择包含最多 Holsteins 的围栏。若存在多个这样的围栏，则选择其中面积最小的一个。请确定这个面积。允许围栏的宽度或高度为零。

### 输入格式

第一行输入包含 $N$。接下来的 $N$ 行每行描述一头牛，包含两个整数和一个字符。整数表示牛所在点的坐标 $(x, y)$（$0 \leq x, y \leq 1000$），字符为 H 或 G 表示牛的品种。没有两头牛位于同一位置，且至少存在一头 Holstein。

### 输出格式

输出两个整数。第一行应包含不包含任何 Guernseys 的围栏能包围的最大 Holsteins 数量，第二行应包含满足该条件的围栏的最小面积。


---

---
title: "仓鼠窝"
layout: "post"
diff: 提高+/省选-
pid: P3400
tag: ['单调队列', '洛谷原创', '洛谷月赛']
---
# 仓鼠窝
## 题目描述

萌萌哒的 Created equal 是一只小仓鼠，小仓鼠自然有仓鼠窝啦。

仓鼠窝是一个由 $n\times m$ 个格子组成的行数为 $n$、列数为 $m$ 的矩阵。小仓鼠现在想要知道，这个矩阵中有多少个子矩阵。

比如说有一个 $2\times 3$ 的矩阵，那么 $1\times 1$ 的子矩阵有 $6$ 个，$1\times 2$ 的子矩阵有 $4$ 个，$1\times 3$ 的子矩阵有 $2$ 个，$2\times 1$ 的子矩阵有 $3$ 个，$2\times 2$ 的子矩阵有 $2$ 个，$2\times 3$ 的子矩阵有 $1$ 个，所以子矩阵共有 $6+4+2+3+2+1=18$ 个。

可是仓鼠窝中有的格子被破坏了。现在小仓鼠想要知道，有多少个内部不含被破坏的格子的子矩阵。

## 输入格式

第一行两个正整数 $n$ 和 $m$，分别表示仓鼠窝的行数 $n$，列数 $m$。

接下来 $n$ 行，每行 $m$ 个数，每个数代表对应的格子，非 $0$ 即 $1$。若为 $0$，表示这个格子被破坏；反之代表这个格子是完好无损的。
## 输出格式

仅一个正整数，表示未被破坏的子矩阵的个数。

## 样例

### 样例输入 #1
```
3 4
1 1 1 1
1 0 1 1
1 1 0 1
```
### 样例输出 #1
```
26
```
## 提示

本题时限 $2\text{s}$，内存限制 $256\text{M}$，因新评测机速度较为接近 NOIP 评测机速度，请注意常数问题带来的影响。

|    数据编号     |     $n$       |     $m$      |        特殊性质        |
| :------------: | :-----------: | :----------: | :--------------------: |
|     $1, 2, 3$    |       $2$       |       $2$      |           无           |
|        $4$       |      $10$       |      $10$      |           无           |
|      $5, 6$      |      $2000$     |     $2000$     |   所有格子均未被破坏     |
|        $7$       |      $2500$     |     $3000$     |  有且仅有一个格子被破坏  |
|        $8$       |      $3000$     |     $2500$     |  有且仅有一个格子被破坏  |
|        $9$       |       $200$     |      $200$     |           无           |
|   $10, 11, 12$   |       $500$     |      $500$     |           无           |
|     $13, 14$     |      $1000$     |     $1000$     |           无           |
|       $15$       |      $1000$     |     $1500$     |           无           |
|       $16$       |      $2500$     |     $2500$     |           无           |
|       $17$       |      $2500$     |     $3000$     |           无           |
|       $18$       |      $3000$     |     $2500$     |           无           |
|     $19, 20$     |      $3000$     |     $3000$     |           无           |


---

---
title: "[POI 2005] LOT-A Journey to Mars"
layout: "post"
diff: 提高+/省选-
pid: P3422
tag: ['2005', '单调队列', 'POI（波兰）', '前缀和']
---
# [POI 2005] LOT-A Journey to Mars
## 题目背景

Byteazar 决定去火星参加一个空间站旅行。
## 题目描述

火星的所有空间站都位于一个圆上，Byteazar 在其中一个空间站登陆然后开始绕圈旅行。  

旅行需要耗费油料，一升油料只能跑 $1$ 米，每个空间站可以补给的油料都有所不同。 

Byteazar 每到一个空间站便可以把该空间站的油料全部拿走（他的油箱是没有容量限制的）。但是如果走到某个时候突然没油了那么旅行便失败了。

Byteazar 需要决定要在哪个地方登陆使得他能顺利访问完所有的空间站后回到他当初登陆的地方，他登陆后可以选择两个方向中的任意一个进行旅行。
## 输入格式

第一行一个整数 $n$，代表空间站数量，所有空间站由 $1$ 至 $n$ 进行标号。

之后 $n$ 行，每行两个整数 $p_i,d_i$，第 $i + 1$ 行描述了第 $i$ 号空间站的信息，其中 $p_i$ 表示该空间站可以补给的油量，$d_i$ 则指明了它到 $i+1$ 号空间站的距离，对于 $n$ 号空间站，$d_i$ 表示它和 $1$ 号空间站的距离。
## 输出格式

输出 $n$ 行，每行一个字符串 `TAK` 或 `NIE`。

若你认为在 $i$ 号空间站登陆是可行的，则需要在第 $i$ 行输出 `TAK`，否则输出 `NIE`。
## 样例

### 样例输入 #1
```
5
3 1
1 2
5 2
0 1
5 4

```
### 样例输出 #1
```
TAK
NIE
TAK
NIE
TAK
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，$3\le n\le10^6$，$p_i\ge0$，$d_i>0$，$\sum d_i\le2\times10^9$。


---

---
title: "[POI 2009] ARC-Architects"
layout: "post"
diff: 提高+/省选-
pid: P3487
tag: ['2009', '单调队列', 'POI（波兰）']
---
# [POI 2009] ARC-Architects
## 题目描述

给定一个序列 $a_i$（$1\leq a_i\leq 10^9$）且 $1\leq i\le n$ 且 $n\leq  
 1.5\times 10^7$，和一个整数 $k$（$k\leq n$ 且 $k\leq 10^6$），求出 $a$ 的一个长度为 $k$ 的子序列 $a_{b_i}$ 满足：

1. $1\leq b_1\leq b_2\leq \ldots\leq b_k$
2. 在满足 $1$ 的情况下 $a_{b_1}, a_{b_2},\ldots , a_{b_k}$ 字典序最大。

## 输入格式

第一行一个数 $k$，以下一行，为序列 $a_i$。以一个单独的 $0$ 结束。

## 输出格式

$k$ 行，每行一个数，其中第 $i$ 行为 $a_{b_i}$。

## 样例

### 样例输入 #1
```
3
12 5 8 3 15 8 0
```
### 样例输出 #1
```
12
15
8
```
## 提示

本题原为交互题，为评测方便，需要将下面的代码粘贴到文件中。

将第一次输入改为 `=inicjuj()` 形式，将之后的每一次输入改为 `=wczytaj()` 形式，将输出改为 `wypisz(jakoscProjektu)` 形式（`jakoscProjektu` 代表你输出的数）。

```cpp
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAGIC_BEGIN -435634223
#define MAGIC_END -324556462

#define MIN_K 1
#define MAX_K 1000000
#define MAX_N 15000000
#define MIN_A 1
#define MAX_A 1000000000
#define MIN_TYP 1
#define MAX_TYP 3
#define MIN_PAR 0
#define MAX_PAR 1000000000

#define ERROR 0
#define CORRECT 1

#define unlikely(x) __builtin_expect(!!(x), 0)

static int init = 0; // czy zostala juz wywolana funkcja inicjuj()
static int lib_n; // ile biblioteka podala juz liczb
static int con_k; // ile zawodnik podal liczb

static int N, K, A, TYP, PAR; // parametry testu wczytywane z pliku
static int bre, len_sub, bou, is_end; // zmienne pomocnicze

static int rand2_status = 198402041;

static inline int rand2(int a, int b){
  rand2_status = rand2_status * 1103515245ll + 12345;
  int x = rand2_status;
  if (x < 0) x = -x; // -2^31 sie nie zdarza :D
  x >>= 1;
  x = a + x % (b - a + 1);
  return x;
}

/* test losowy */
static inline int random_test()
{
    return rand2(1, A);
}

/* test z dlugim podciagiem nierosnacym */
static inline int decreasing_test()
{
    int tmp;
    if(bre == 0) {
        bre = rand2(0, (N - lib_n + 1 - len_sub));
        tmp = A;
        A -= rand2(0, (A - 1) / len_sub);
        len_sub--;
    }
    else {
        bre--;
        tmp = rand2(1, A);
    }
    return tmp;
}

/* test z dlugim podciagiem niemalejacym */
static inline int increasing_test()
{
    return bou - decreasing_test();
}

static void finish(int res, const char com[])
{
    if(res == ERROR)
        printf("%s\n", com);
    exit(0);
}

/* Inicjuje dane wejsciowe i zwraca liczbe projektow */
int inicjuj()
{
    if(init == 1)
        finish(ERROR, "Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    init = 1;
    scanf("%d", &K);
    if (K > 0){
      TYP = 0;
      N = MAX_N + 2;
      return K;
    }
    int magic_begin, magic_end;
    scanf("%d%d", &magic_begin, &TYP);
    if(magic_begin != MAGIC_BEGIN || TYP < MIN_TYP || TYP > MAX_TYP)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d%d%d%d", &N, &K, &A, &PAR);
    if(N < 1 || N > MAX_N || N < K || K > MAX_K || A < MIN_A || A > MAX_A 
        || PAR < MIN_PAR || PAR > MAX_PAR)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d", &magic_end);
    if(magic_end != MAGIC_END)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    con_k = 0;
    lib_n = 0;
    is_end = 0;
    if(TYP == 2 || TYP == 3) {
        len_sub = PAR;
        bre = 0;
    }
    if(TYP == 2)
        bou = A--;
    return K;
}

/* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
int wczytaj()
{
    if(unlikely(init == 0))
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(unlikely(lib_n > N || is_end == 1))
        finish(ERROR, "Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    if(unlikely(lib_n == N))
        return 0;
    lib_n++;
    switch (TYP) {
      case 0:
        scanf("%d", &A);
        if(A == 0)
          is_end = 1;
        return A;
        break;
      case 1: return random_test(); break;
      case 2: return increasing_test(); break;
      case 3: return decreasing_test(); break;
      default:
              finish(ERROR, "Nieznany typ testu");
    }
    return -1;
}

/* Sluzy do wypisania wyznaczonego podciagu */
void wypisz(int jakoscProjektu)
{
    if(init == 0)
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    printf("%d\n", jakoscProjektu);
    if(++con_k == K)
        finish(CORRECT, "");
}
```


---

---
title: "[POI 2014] PTA-Little Bird"
layout: "post"
diff: 提高+/省选-
pid: P3572
tag: ['动态规划 DP', '2014', '单调队列', 'POI（波兰）']
---
# [POI 2014] PTA-Little Bird
## 题目描述

In the Byteotian Line Forest there are $n$ trees in a row.

On top of the first one, there is a little bird who would like to fly over to the top of the last tree.

Being in fact very little, the bird might lack the strength to fly there without any stop.

If the bird is sitting on top of the tree no. i, then in a single flight leg it can fly toany of the trees no. $i+1,i+2,\cdots,i+k$, and then has to rest afterward.

Moreover, flying up is far harder to flying down.  A flight leg is tiresome if it ends in a tree at leastas high as the one where is started.  Otherwise the flight leg is not tiresome.

The goal is to select the trees on which the little bird will land so that the overall flight is leasttiresome, i.e., it has the minimum number of tiresome legs.

We note that birds are social creatures, and our bird has a few bird-friends who would also like to getfrom the first tree to the last one.  The stamina of all the birds varies,so the bird's friends may have different values of the parameter $k$.

Help all the birds, little and big!
## 输入格式

There is a single integer $n$ ($2\le n\le 1\ 000\ 000$) in the first line of the standard input:

the number of trees in the Byteotian Line Forest.

The second line of input holds $n$ integers $d_1,d_2,\cdots,d_n$ ($1\le d_i\le 10^9$)separated by single spaces: $d_i$ is the height of the i-th tree.

The third line of the input holds a single integer $q$ ($1\le q\le 25$): the number of birds whoseflights need to be planned.

The following $q$ lines describe these birds: in the $i$-th of these lines, there is an integer $k_i$ ($1\le k_i\le n-1$) specifying the $i$-th bird's stamina. In other words, the maximum number of trees that the $i$-th bird can pass before it has to rest is $k_i-1$.

## 输出格式

Your program should print exactly $q$ lines to the standard output.

In the $i$-th line, it should specify the minimum number of tiresome flight legs of the $i$-th bird.

## 样例

### 样例输入 #1
```
9
4 6 3 6 3 7 2 6 5
2
2
5

```
### 样例输出 #1
```
2
1

```
## 题目翻译

有 $n$ 棵树排成一排，第 $i$ 棵树的高度是 $d_i$。

有 $q$ 只鸟要从第 $1$ 棵树到第 $n$ 棵树。

当第 $i$ 只鸟在第 $j$ 棵树时，它可以飞到第 $j+1, j+2, \cdots, j+k_i$ 棵树。

如果一只鸟飞到一颗高度大于等于当前树的树，那么它的劳累值会增加 $1$，否则不会。

由于这些鸟已经体力不支，所以它们想要最小化劳累值。

### 输入格式

第一行输入 $n$。

第二行 $n$ 个数，第 $i$ 个数表示 $d_i$。

第三行输入 $q$。

接下来 $q$ 行，每一行一个整数，第 $i$ 行的整数为 $k_i$。

### 输出格式

共 $q$ 行，每一行输出第 $i$ 只鸟的最小劳累值。

### 数据范围

$1 \le n \le 10^6$，$1 \le d_i \le 10^9$，$1 \le q \le 25$，$1 \le k_i \le n - 1$。



---

---
title: "[POI 2015] WIL"
layout: "post"
diff: 提高+/省选-
pid: P3594
tag: ['动态规划 DP', '2015', '单调队列', 'POI（波兰）']
---
# [POI 2015] WIL
## 题目描述

给定一个长度为 $n$ 的序列，你有一次机会选中一段连续的长度不超过 $d$ 的区间，将里面所有数字全部修改为 $0$。请找到最长的一段连续区间，使得该区间内所有数字之和不超过 $p$。
## 输入格式

输入的第一行包含三个整数，分别代表 $n,p,d$。

第二行包含 $n$ 个整数，第 $i$ 个整数代表序列中第 $i$ 个数 $w_i$。
## 输出格式

包含一行一个整数，即修改后能找到的最长的符合条件的区间的长度。

## 样例

### 样例输入 #1
```
9 7 2
3 4 1 9 4 1 7 1 3
```
### 样例输出 #1
```
5
```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le d \le n \le 2 \times 10^6$，$0 \le p \le 10^{16}$，$1 \leq w_i \leq 10^9$。

----

原题名称：Wilcze doły。


---

---
title: "[NOIP 2017 普及组] 跳房子"
layout: "post"
diff: 提高+/省选-
pid: P3957
tag: ['动态规划 DP', '2017', '二分', '单调队列', 'NOIP 普及组', '队列']
---
# [NOIP 2017 普及组] 跳房子
## 题目背景

NOIP2017 普及组 T4
## 题目描述

跳房子，也叫跳飞机，是一种世界性的儿童游戏，也是中国民间传统的体育游戏之一。

跳房子的游戏规则如下：

在地面上确定一个起点，然后在起点右侧画 $n$ 个格子，这些格子都在同一条直线上。每个格子内有一个数字（整数），表示到达这个 格子能得到的分数。玩家第一次从起点开始向右跳，跳到起点右侧的一个格子内。第二次再从当前位置继续向右跳，依此类推。规则规定：

玩家每次都必须跳到当前位置右侧的一个格子内。玩家可以在任意时刻结束游戏，获得的分数为曾经到达过的格子中的数字之和。

现在小 R 研发了一款弹跳机器人来参加这个游戏。但是这个机器人有一个非常严重的缺陷，它每次向右弹跳的距离只能为固定的 $d$。小 R 希望改进他的机器人，如果他花 $g$ 个金币改进他的机器人，那么他的机器人灵活性就能增加 $g$，但是需要注意的是，每 次弹跳的距离至少为 $1$。具体而言，当 $g<d$ 时，他的机器人每次可以选择向右弹跳的距离为 $d-g,d-g+1,d-g+2,\ldots,d+g-1,d+g$；否则当 $g \geq d$ 时，他的机器人每次可以选择向右弹跳的距离为 $1,2,3,\ldots,d+g-1,d+g$。

现在小 R 希望获得至少 $k$ 分，请问他至少要花多少金币来改造他的机器人。
## 输入格式

第一行三个正整数 $n,d,k$，分别表示格子的数目，改进前机器人弹跳的固定距离，以及希望至少获得的分数。相邻两个数 之间用一个空格隔开。

接下来 $n$ 行，每行两个整数 $x_i,s_i$，分别表示起点到第 $i$ 个格子的距离以及第 $i$ 个格子的分数。两个数之间用一个空格隔开。保证 $x_i$ 按递增顺序输入。
## 输出格式

共一行，一个整数，表示至少要花多少金币来改造他的机器人。若无论如何他都无法获得至少 $k$ 分，输出 $-1$。
## 样例

### 样例输入 #1
```
7 4 10
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7 4 20
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #2
```
-1
```
## 提示

**样例 1 说明**

花费 $2$ 个金币改进后，小 R 的机器人依次选择的向右弹跳的距离分别为 $ 2, 3, 5, 3, 4,3$，先后到达的位置分别为 $2, 5, 10, 13, 17, 20$，对应 $ 1, 2, 3, 5, 6, 7$ 这 $6$ 个格子。这些格子中的数字之和 $ 15$ 即为小 R 获得的分数。

**样例 2 说明**

由于样例中 $7$ 个格子组合的最大可能数字之和只有 $18$，所以无论如何都无法获得 $20$ 分。

**数据规模与约定**

本题共 10 组测试数据，每组数据等分。

对于全部的数据满足 $1 \le n \le 5\times10^5$，$1 \le d \le2\times10^3$，$1 \le x_i, k \le 10^9$，$|s_i| < 10^5$。

对于第 $1, 2$ 组测试数据，保证 $n\le 10$。

对于第 $3, 4, 5$ 组测试数据，保证 $n \le 500$。

对于第 $6, 7, 8$ 组测试数据，保证 $d = 1$。


---

---
title: "[USACO18FEB] Snow Boots G"
layout: "post"
diff: 提高+/省选-
pid: P4269
tag: ['2018', '线段树', 'USACO', '并查集', '单调队列']
---
# [USACO18FEB] Snow Boots G
## 题目描述

It's winter on the farm, and that means snow! There are $N$ tiles on the path from the farmhouse to the barn, conveniently numbered $1 \dots N$, and tile $i$ is covered in $f_i$ feet of snow.
In his farmhouse cellar, Farmer John has $B$ pairs of boots, numbered $1 \dots B$. Some pairs are more heavy-duty than others, and some pairs are more agile than others. In particular, pair $i$ lets FJ step in snow at most $s_i$ feet deep, and lets FJ move at most $d_i$ forward in each step.

Farmer John starts off on tile $1$ and must reach tile $N$ to wake up the cows. Tile $1$ is sheltered by the farmhouse roof, and tile $N$ is sheltered by the barn roof, so neither of these tiles has any snow. Help Farmer John determine which pairs of snow boots will allow him to make the trek.
## 输入格式

The first line contains two space-separated integers $N$ and $B$ ($1 \leq N,B \leq 10^5$).
The second line contains $N$ space-separated integers; the $i$th integer is $f_i$, the depth of snow on tile $i$ ($0 \leq f_i \leq 10^9$). It's guaranteed that $f_1 = f_N = 0$.

The next $B$ lines contain two space-separated integers each. The first integer on line $i+2$ is $s_i$, the maximum depth of snow in which pair $i$ can step. The second integer on line $i+2$ is $d_i$, the maximum step size for pair $i$. It's guaranteed that $0 \leq s_i \leq 10^9$ and $1 \leq d_i \leq N-1$.
## 输出格式

The output should consist of $B$ lines. Line $i$ should contain a single integer: $1$ if Farmer John can trek from tile $1$ to tile $N$ wearing the $i$th pair of boots, and $0$ otherwise.
## 样例

### 样例输入 #1
```
8 7
0 3 8 5 6 9 0 0
0 5
0 6
6 2
8 1
10 1
5 3
150 7
```
### 样例输出 #1
```
0
1
1
0
1
1
1

```
## 提示

Problem credits: Dhruv Rohatgi
## 题目翻译

到冬天了，这意味着下雪了！从农舍到牛棚的路上有 $N$ 块地砖，方便起见编号为 $1 \dots N$，第 $i$ 块地砖上积了 $f_i$ 英尺的雪。
在 Farmer John 的农舍的地窖中，总共有 $B$ 双靴子，编号为 $1 \dots B$。其中某些比另一些结实，某些比另一些轻便。具体地说，第 $i$ 双靴子能够让 FJ 在至多 $s_i$ 英尺深的积雪中行走，能够让 FJ 每步至多前进 $d_i$。

Farmer John 从 $1$ 号地砖出发，他必须到达 $N$ 号地砖才能叫醒奶牛们。$1$ 号地砖在农舍的屋檐下，$N$ 号地砖在牛棚的屋檐下，所以这两块地砖都没有积雪。帮助 Farmer John 求出哪些靴子可以帮助他走完这段艰辛的路程。

**【输入格式】**

第一行包含两个空格分隔的整数 $N$ 和 $B$（$1 \leq N,B \leq 10^5$）。  
第二行包含$N$个空格分隔的整数；第 $i$ 个整数为 $f_i$，即 $i$ 号地砖的积雪深度（$0 \leq f_i \leq 10^9$）。输入保证 $f_1 = f_N = 0$。

下面 $B$ 行，每行包含两个空格分隔的整数。第 $i+2$ 行的第一个数为 $s_i$，表示第 $i$ 双靴子能够承受的最大积雪深度。第 $i+2$ 行的第二个数为 $d_i$，表示第 $i$ 双靴子的最大步长。输入保证 $0 \leq s_i \leq 10^9$ 以及 $1 \leq d_i \leq N-1$。

**【输出格式】**

输出包含 $B$ 行。第 $i$ 行包含一个整数：如果 Farmer John 能够穿着第 $i$ 双靴子从 $1$ 号地砖走到 $N$ 号地砖，为 $1$，否则为 $0$。



---

---
title: "[USACO10NOV] Buying Feed G"
layout: "post"
diff: 提高+/省选-
pid: P4544
tag: ['2010', 'USACO', '单调队列', '背包 DP', '队列']
---
# [USACO10NOV] Buying Feed G
## 题目描述

约翰开车来到镇上，他要带$K$吨饲料回家。运送饲料是需要花钱的，如果他的车上有$X$吨饲料，每公里就要花费$X^2$元，开车D公里就需要$D\times  X^2$元。约翰可以从$N$家商店购买饲料，所有商店都在一个坐标轴上，第$i$家店的位置是$X_i$，饲料的售价为每吨$C_i$元，库存为$F_i$。

约翰从坐标$X=0$开始沿坐标轴正方向前进，他家在坐标$X=E$上。为了带$K$吨饲料回家，约翰最少的花费是多少呢？假设所有商店的库存之和不会少于$K$。

举个例子，假设有三家商店，情况如下所示：

|坐标|$X=1$|$X=3$|$X=4$|$E=5$|
|:-:|:-:|:-:|:-:|:-:|
|库存|$1$|$1$|$1$|
|售价|$1$|$2$|$2$|

如果$K=2$，约翰的最优选择是在离家较近的两家商店购买饲料，则花在路上的钱是$1+4=5$，花在商店的钱是$2+2=4$，共需要$9$元。
## 输入格式

第$1$行:三个整数$K,E,N$ 第$2..N+1$行:第$i+1$行的三个整数代表,$X_i,F_i,C_i$.
## 输出格式

一个整数,代表最小花费
## 样例

### 样例输入 #1
```
2 5 3
3 1 2
4 1 2
1 1 1
```
### 样例输出 #1
```
9
```
## 提示

$1 \leq K \leq 10000 , 1 \leq E \leq 500 , 1 \leq N \leq 500$

$0 < Xi < E, 1 \leq Fi \leq 10000, 1 \leq C_i \leq 10^7$


---

---
title: "[COCI 2018/2019 #1] Strah"
layout: "post"
diff: 提高+/省选-
pid: P7306
tag: ['2018', '单调队列', 'COCI（克罗地亚）']
---
# [COCI 2018/2019 #1] Strah
## 题目背景

任何人都会对某事感到害怕。有些怕黑，有些怕高，还有些惧怕 Vinnie Jones……
## 题目描述

Mirko 最害怕的是寻找合适的土地来种植草莓。他的土地可以用一个 $N \times M$ 的矩阵来表示。土地中有些田地适合种植草莓，而有些不适合，因为那里杂草丛生。

Mirko 正在寻找一块合适矩形。当土地中有一块矩形区域包含的所有田地均适合种植草莓，则该矩形被称为合适矩形。

Mirko 还对所有田地的潜力值感兴趣。一块田地的潜力值定义为包含该田地的合适矩形的个数。

求 Mirko 所有田地的潜力值之和。
## 输入格式

第一行输入正整数 $N,M$，表示土地的规模。

接下来的 $N$ 行，每行输入 $M$ 个字符。其中 `.` 表示该块田地适合种植草莓，而 `#` 表示不适合。
## 输出格式

输出 Mirko 所有田地的潜力值之和。
## 样例

### 样例输入 #1
```
2 3
.#.
..#
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
3 3
...
...
...
```
### 样例输出 #2
```
100
```
### 样例输入 #3
```
3 4
..#.
#...
...#
```
### 样例输出 #3
```
40
```
## 提示

#### 样例 1 解释

下列矩阵代表各个田地的潜力值。所有田地潜力值总和为 $8$。

|$2$|$0$|$1$|
| :----------: | :----------: | :----------: |
|$3$|$2$|$0$|

#### 数据规模与约定

对于 $20\%$ 的数据，$1 \le N,M \le 10$。

对于另外 $30\%$ 的数据，$1 \le N,M \le 300$。

对于 $100\%$ 的数据，$1 \le N,M \le 2000$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2018-2019](https://hsin.hr/coci/archive/2018_2019/) [CONTEST #1](https://hsin.hr/coci/archive/2018_2019/contest1_tasks.pdf)  _T4 Strah_。**


---

---
title: "Inferno"
layout: "post"
diff: 提高+/省选-
pid: P8945
tag: ['贪心', '单调队列', '2023', '洛谷原创', 'O2优化', '前缀和']
---
# Inferno
## 题目背景

> 我是幽灵。  
> 穿过悲惨之城，我落荒而逃。  
> 穿过永世凄苦，我远走高飞。

沿着阿尔诺河的堤岸，我夺路狂奔，气喘吁吁……左转上了卡斯特拉尼大街，一直朝北而行，始终隐蔽在乌菲兹美术馆的阴影之下。

但他们还是穷追不舍。

他们的脚步声越来越响，这些追捕者冷酷无情，不达目的绝不善罢甘休。

这么多年来，他们一直尾随着我。他们锲而不舍，是的我只能活在地下……被迫呆在炼狱之中……就像冥府的恶魔，时刻忍受地狱的煎熬。

> 我是幽灵。

如今浮生尘世，我举目北望，却看不到通往救赎的捷径——那高耸的亚平宁山脉挡住了黎明的第一缕阳光。
## 题目描述

罗伯特 · 兰登在洗下但丁死亡面具上的丙烯石膏后，在背面发现了一行字：

> 哦，有着稳固智慧的人啊，  
> 请注意这里的含义  
> 就藏在晦涩的序列面纱之下。

下面有一行由 $1,-1$ 组成的长度为 $n$ 的序列。面具经受了岁月的侵蚀，序列中有一些数已经模糊不清。幸运的是，面具下面有给出两条线索：

> 你只得往空缺的位置填 $k$ 个 $1$，其余填入 $-1$，需要最大化这个序列的最大子段和。

 > > **一个序列的最大子段和定义为，其在一段连续长度的区间内的最大和。形式化地，一个序列 $a$ 的最大子段和即为 $\max\limits_{l=1}^n\max\limits_{r=l}^n\left(\sum\limits_{i=l}^r a_i\right)$。**

罗伯特 · 兰登希望在瘟疫扩散之前找到有关的线索。于是他找到了你。

- - -

#### 【形式化题意】

给定一个只包含 $-1,0,1$ 的序列，求出往 $0$ 的位置上填 $k$ 个 $1$，其余填 $-1$ 后最大子段和的最大值。
## 输入格式

第一行两个正整数 $n,k$。

接下来一行 $n$ 个整数 $a_i\in\{-1,0,1\}$，其中 $0$ 表示数字模糊不清。
## 输出格式

一行一个正整数，表示可能的最大子段和。
## 样例

### 样例输入 #1
```
5 2
1 0 -1 0 0
```
### 样例输出 #1
```
2
```
## 提示

#### 【样例解释】

一种可行的方案是填入 $\{1,1,-1\}$，最大子段和为 $2$。

#### 【数据范围】


**本题开启捆绑测试。**

| $\text{SubTask}$ | 分值 | $n,k\le $ |
| :----------: | :----------: | :----------: |
| $0$ | $4$ | $20$ | 
| $1$ | $6$ | $200$ | 
| $2$ | $10$ | $5\times 10^3$ | 
| $3$ | $30$ | $5\times 10^5$ | 
| $4$ | $50$ | $10^7$ | 


对于 $100\%$ 的数据，$1\le n,k\le10^7$，$a_i\in \{-1,0,1\}$。保证 $k\le$ 序列中 $0$ 的个数。

**本题标程使用优化后的输入输出，在 O2 优化下最大点用时约 $350$ ms，足以通过此题。如果您自认为您的程序复杂度正确，却超出时间限制，请使用更优的输入输出方式，或者优化常数。**



---

