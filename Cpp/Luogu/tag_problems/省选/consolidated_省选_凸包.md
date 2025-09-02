---
title: "[USACO24FEB] Lazy Cow P"
layout: "post"
diff: 省选/NOI-
pid: P10196
tag: ['线段树', '二分', 'USACO', '2024', 'O2优化', '凸包']
---
# [USACO24FEB] Lazy Cow P
## 题目描述

Bessie 正在努力为美国件算机奥林匹克二月的竞赛准备测试用例。每一分钟，她可以选择不准备测试用例，不花费能量；或者对于某个正整数 $a$，花费 $3^{a−1}$ 能量准备 $a$ 个测试用例。

Farmer John 有 $D$（$1\le D\le 2\cdot 10^5$）个需求。对于第 $i$ 个需求，他告诉 Bessie，在前 $m_i$ 分钟内她总共需要准备至少 $b_i$ 个测试用例（$1\le m_i\le 10^6,1\le b_i\le 10^{12}$）。

令 $e_i$ 为满足前 $i$ 个需求 Bessie 最小需要花费的能量。输出 $e_1,\ldots,e_D$ 模 $10^9+7$ 的余数。 
## 输入格式

输入的第一行包含 $D$。以下 $D$ 行，第 $i$ 行包含两个空格分隔的整数 $m_i$ 和 $b_i$。
## 输出格式

输出 $D$ 行，第 $i$ 行包含 $e_i \bmod 10^9+7$。 
## 样例

### 样例输入 #1
```
4
5 11
6 10
10 15
10 30
```
### 样例输出 #1
```
21
21
25
90
```
### 样例输入 #2
```
2
100 5
100 1000000000000
```
### 样例输出 #2
```
5
627323485
```
### 样例输入 #3
```
20
303590 482848034083
180190 112716918480
312298 258438719980
671877 605558355401
662137 440411075067
257593 261569032231
766172 268433874550
8114 905639446594
209577 11155741818
227183 874665904430
896141 55422874585
728247 456681845046
193800 632739601224
443005 623200306681
330325 955479269245
377303 177279745225
880246 22559233849
58084 155169139314
813702 758370488574
929760 785245728062
```
### 样例输出 #3
```
108753959
108753959
108753959
148189797
148189797
148189797
148189797
32884410
32884410
32884410
32884410
32884410
32884410
32884410
3883759
3883759
3883759
3883759
3883759
3883759
```
## 提示

### 样例解释 1

对于第一个测试用例，

- $i=1$：如果 Bessie 在前 $5$ 天分别制作 $[2,3,2,2,2]$ 个测试用例，她将花费 $3^1+3^2+3^1+3^1+3^1=21$ 单位能量，并在第 $5$ 天结束时制作了 $11$ 个测试用例。
- $i=2$：Bessie 可以遵循上面的策略，确保在第 $5$ 天结束时制作了 $11$ 个测试用例，而这将自动满足第二个需求。
- $i=3$：如果 Bessie 在前 $10$ 天分别制作 $[2,3,2,2,2,0,1,1,1,1]$ 个测试用例，她将花费 $25$ 单位能量并满足所有需求。可以证明她无法花费更少的能量。
- $i=4$：如果 Bessie 在前 $10$ 天每一天制作 $3$ 个测试用例，她将花费 $3^2\cdot 10=90$ 单位能量并满足所有需求。

对于每一个 $i$，可以证明 Bessie 无法花费更少的能量满足前 $i$ 个需求。

### 测试点性质

- 测试点 $4-5$：$D\le 100$，且对于所有 $i$，$m_i\le 100$。
- 测试点 $6-8$：$D\le 3000$。
- 测试点 $9-20$：没有额外限制。


---

---
title: "[COTS 2022] 点组 Točkice"
layout: "post"
diff: 省选/NOI-
pid: P10876
tag: ['博弈论', '2022', 'O2优化', '凸包', 'COCI（克罗地亚）']
---
# [COTS 2022] 点组 Točkice
## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D2T3。$\texttt{1s,0.5G}$。
## 题目描述


二维平面上画了 $N$ 个点 $(x_i,y_i)$，其中任意三点不共线。

从 A 开始，AB 两人轮流玩游戏：

- 选择两个点 $(x_i,y_i),(x_j,y_j)$（$i\neq j$）。若连接这两点的线段不与之前的线段相交，则在两点间连一条线段。
- 不能操作的玩家负。

需要注意的是：**线段可以在顶点处相交**（即可以共用一个顶点）。

A 和 B 都绝顶聪明，请你判断鹿死谁手。

## 输入格式

第一行，一个整数 $N$；

接下来 $N$ 行，每行两个整数 $x_i,y_i$。
## 输出格式

如果 A（先手）胜，输出 `Alenka`；否则输出 `Bara`。
## 样例

### 样例输入 #1
```
4
0 0
0 10
10 0
10 10
```
### 样例输出 #1
```
Alenka
```
### 样例输入 #2
```
5
2 1
1 3
6 4
3 5
5 2
```
### 样例输出 #2
```
Alenka
```
### 样例输入 #3
```
4
4 2
2 4
2 2
1 1
```
### 样例输出 #3
```
Bara
```
## 提示


对于 $100\%$ 的数据，保证：

- $1\le N\le 10^5$；
- $1\le x_i,y_i\le 10^6$；
- 任意三点不共线。

| 子任务编号 | 分值 | $N\le$ |
|:-----:|:------:|:-------:|
| $1$  | $13$  | $7$  |
| $2$  | $17$  | $300$  |
| $3$  | $21$  | $1\, 000$ |
| $4$  | $49$  | $10^5$ |


---

---
title: "[COTS 2020] 王国 Kraljevstvo"
layout: "post"
diff: 省选/NOI-
pid: P11023
tag: ['2020', 'O2优化', '斜率优化', '四边形不等式', '凸包', 'COCI（克罗地亚）']
---
# [COTS 2020] 王国 Kraljevstvo
## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D1T1。$\texttt{1s,0.5G}$。

## 题目描述


给定二维平面上的 $N$ 个点。选择 $K$ 个点，最大化这 $K$ 个点的凸包面积。

此外，要求必须选择平面上 $x$ 坐标最小/最大的两个点。保证这两个点所在的与 $y$ 轴平行的直线上没有其他点，且这两个点的 $y$ 坐标为 $0$。

只需要输出最大的面积。

## 输入格式


第一行，两个正整数 $N,K$。

接下来 $N$ 行，每行两个整数 $x_i,y_i$，描述一个点。

## 输出格式


输出一行一个实数，表示凸包的最大面积。

输出不应有多余的前导零或后导零。
## 样例

### 样例输入 #1
```
6 4
0 0
9 0
2 8
6 5
2 -7
8 -7
```
### 样例输出 #1
```
67.5
```
### 样例输入 #2
```
5 3
0 0
10 0
5 0
5 5
5 -5
```
### 样例输出 #2
```
25
```
### 样例输入 #3
```
8 5
0 0
15 0
2 -2
4 12
10 -14
6 -12
2 -10
13 10
```
### 样例输出 #3
```
238
```
## 提示

####

- 样例 $1$ 解释：选择 $(0, 0), (2, −7),(2, 8) , (9, 0) $ 即可。
- 样例 $2$ 解释：选择 $(0, 0), (10, 0) ,
(5, −5) $ 即可。

亦可参阅下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/jp2ibsfe.png)



#### 数据范围

对于 $100\%$ 的数据，保证：

- $3\le K\le N\le 3\, 000$；
- 给出的点不重合；
- $x$ 坐标最小/最大的点唯一，且对应的点的 $y$ 坐标为 $0$。


| 子任务编号 | $N\le $ | 得分 |  
| :--: | :--: | :--: |
| $ 1 $    | $20$ |$ 11 $   |  
| $ 2 $    | $100$ | $ 25 $   |  
| $ 3 $    | $500$ | $ 15 $   |  
| $ 4 $    | $3\, 000$ | $ 49 $   |  


---

---
title: "[Code+#6] 进阶法师"
layout: "post"
diff: 省选/NOI-
pid: P11441
tag: ['计算几何', 'Special Judge', '凸包', '叉积', '旋转卡壳', 'Code+']
---
# [Code+#6] 进阶法师
## 题目背景

搬运自 [Code+ 第 6 次网络赛](https://gitlink.org.cn/thusaa/codeplus6/)。
## 题目描述

传说在 $100000$ 年后，又有大量陨石即将撞击企鹅大陆。散布在企鹅大陆各个地点的进阶企鹅法师们张开法阵保护企鹅大陆。

法师站在一些固定的点，如果一个点与某两个法师连线形成的夹角大于等于 $90$ 度，那么这个点可以免于灾害。

每个法师的坐标可以使用一组非负整数 $\left(X, Y\right)$ 表示。不存在两个法师在同一个位置。

一想到这里，企鹅豆豆又想到一个问题——能被保护的区域的面积有大？
## 输入格式

输入的第一行包含一个正整数 $n$，表示法师人数，保证 $2 \le n \le 10^5$。

接下来 $n$ 行每行两个非负整数，表示一位法师的坐标位置。保证数值不超过 $10^9$。
## 输出格式

输出一个小数，表示被保护的区域的面积。如果你的输出与标算的答案的相对误差不超过 $10^{-7}$ 即被认为是正确的。
## 样例

### 样例输入 #1
```
2
0 0
0 2
```
### 样例输出 #1
```
3.14159265358979326666666666666233333333
```
### 样例输入 #2
```
3
0 1
3 0
2 2
```
### 样例输出 #2
```
10.353981582
```
## 提示

### 样例解释

**【样例 1】**

对于样例一，显然被保护面积是以这两点连线作为直径的圆形。根据圆的面积计算公式即可得出答案。而且你与标算的相对误差不超过 $10^{-7}$ 即被认为正确。

**【样例 3】**

见题目目录下的 `3.in` 与 `3.ans`。

### 数据范围

保证 $2 \le n \le 10^5$，$0\le X,Y\le 10^9$。


---

---
title: "[USACO24DEC] It's Mooin' Time P"
layout: "post"
diff: 省选/NOI-
pid: P11459
tag: ['动态规划 DP', 'USACO', '2024', '动态规划优化', '凸包']
---
# [USACO24DEC] It's Mooin' Time P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

Bessie 有一个长度为 $N$（$1\le N\le 3\cdot 10^5$）的字符串，仅由字符 M 和 O 组成。对于字符串中的每个位置 $i$，需要花费 $c_i$ 来将该位置上的字符修改为另一种字符（$1\le c_i\le 10^8$）。

Bessie 认为，如果字符串包含更多长度为 $L$（$1\le L\le \min(N, 3)$）的哞叫会看起来更好。一个长度为 $L$ 的哞叫指的是一个 M 后面跟着 $L-1$ 个 O。

对于从 $1$ 到 $\lfloor N/L\rfloor$ 的每一个正整数 $k$，计算将字符串修改至包含至少 $k$ 个等于长度为 $L$ 的哞叫的子串的最小花费。
## 输入格式

输入的第一行包含 $L$ 和 $N$。

下一行包含 Bessie 的长为 $N$ 的字符串，仅由字符 M 和 O 组成。

下一行包含空格分隔的整数 $c_1\dots c_N$。
## 输出格式

输出 $\lfloor N/L\rfloor$ 行，依次包含每一个 $k$ 的答案。

## 样例

### 样例输入 #1
```
1 4
MOOO
10 20 30 40
```
### 样例输出 #1
```
0
20
50
90
```
### 样例输入 #2
```
3 4
OOOO
50 40 30 20
```
### 样例输出 #2
```
40
```
### 样例输入 #3
```
2 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142
```
### 样例输出 #3
```
0
0
0
0
0
12851185
35521020
60232254
99881782
952304708
```
### 样例输入 #4
```
3 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142
```
### 样例输出 #4
```
0
0
0
44743602
119332891
207066974
```
## 提示

- 测试点 $5$：$L=3, N\le 5000$。
- 测试点 $6$：$L=1$。
- 测试点 $7\sim 10$：$L=2$。
- 测试点 $11\sim 18$：$L=3$。


---

---
title: "[集训队互测 2024] 长野原龙势流星群"
layout: "post"
diff: 省选/NOI-
pid: P12479
tag: ['二分', '平衡树', '集训队互测', '2024', 'Special Judge', '树形 DP', '凸包']
---
# [集训队互测 2024] 长野原龙势流星群
## 题目描述

Naganohara Yoimiya 给了你一棵 $n$ 个节点的有根树，$1$ 号节点是根节点，每个点有点权 $w_i$。

你需要对每个点 $u$ 找到一个以 $u$ 为根的非空连通块，并最大化这个连通块内所有点的点权的平均值。

对每个点 $u$ 输出这个最大的平均值。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $n-1$ 个正整数 $p_2,p_3,\cdots,p_n$，$p_i$ 表示 $i$ 的父节点的编号，保证 $p_i< i$。

接下来一行 $n$ 个正整数 $w_1,w_2,\cdots,w_n$。
## 输出格式

输出 $n$ 行，第 $i$ 行输出一个实数表示以节点 $i$ 为根的连通块内点权平均值的最大值。

如果你的答案和标准答案的相对误差或绝对误差不超过 $10^{-6}$ 则视为正确。
## 样例

### 样例输入 #1
```
6
1 2 2 1 4
3 1 5 6 6 7
```
### 样例输出 #1
```
4.6666666667
4.7500000000
5.0000000000
6.5000000000
6.0000000000
7.0000000000
```
## 提示

### 测试点约束

对于所有数据，$1\le n\le 2\times 10^5,1\le w_i\le 10^9$。

- Subtask 1（$10$ 分）：$1\le n\le 2000$。
- Subtask 2（$10$ 分）：$p_i=\lfloor i/2\rfloor$。
- Subtask 3（$40$ 分）：$1\le n\le 50000$。
- Subtask 4（$40$ 分）：无特殊限制。


---

---
title: "[GCJ 2013 #3] Rural Planning [Unverified]"
layout: "post"
diff: 省选/NOI-
pid: P13299
tag: ['计算几何', '2013', 'Special Judge', '凸包', 'Google Code Jam']
---
# [GCJ 2013 #3] Rural Planning [Unverified]
## 题目描述

You have recently purchased a nice big farmyard, and you would like to build a fence around it. There are already N fence posts in your farmyard.

You will add lengths of fence in straight lines connecting the fence posts. Unfortunately, for reasons you don't fully understand, your lawyers insist you actually have to use all the fence posts, or things will go bad.

In this problem, the posts will be represented as points in a 2-dimensional plane. You want to build the fence by ordering the posts in some order, and then connecting the first with the second, second with third, and finally the last one with the first. The fence segments you create should be a polygon without self-intersections. That is, at each fence-post there are only two fence segments, and at every other point there is at most one fence segment.

Now that's easy, but you also actually want to preserve the fact your farmyard is big! It's not really fun to wall off most of your farmyard with the fences. So you would like to create the fence in such a way that the enclosed area is more than half of the maximum area you could enclose if you were allowed not to use all the posts.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of each test case contains the number $N$ of posts. The posts are numbered from $0$ to $N - 1$. Each of the next $N$ lines contains two integers $X_i$ and $Y_i$ separated by a single space: the coordinates of the $i$-th post.

## 输出格式

For each test case, output one line containing "Case #x: ", where $x$ is the case number (starting from 1), followed by $N$ distinct integers from $0$ to $N - 1$, separated by spaces. They are the numbers of the posts, in either clockwise or counter-clockwise direction, that you will use to build the fence. Note that the first and last posts are connected.

If there are multiple solutions, print any of them.
## 样例

### 样例输入 #1
```
3
4
1 2
2 0
0 0
1 1
5
0 0
1 1
2 2
0 2
2 0
3
0 0
1 0
0 1
```
### 样例输出 #1
```
Case #1: 0 1 2 3
Case #2: 0 1 4 2 3
Case #3: 0 2 1
```
## 提示

**Sample Explanation**

In the first test case, there are three polygons we can construct, and two of them have a large enough area — the ones described by sequences 0 1 2 3 and 0 2 1 3. The polygon described by 0 1 3 2 would be too small. In the second test case, we have make sure the polygon does not intersect itself, so, for instance, 0 1 2 3 4 or 0 1 3 4 2 would be bad. In the third case, any order describes the same triangle and is fine.

**Limits**

- The posts will be at $N$ unique points, and will not all lie on the same line.

**Small dataset (9 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq T \leq 100$
- $3 \leq N \leq 10$
- $-100 \leq X_i, Y_i \leq 100$

**Large dataset (13 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq T \leq 30$
- $3 \leq N \leq 1000$
- $-50000 \leq X_i, Y_i \leq 50000$


---

---
title: "[GCJ 2013 Finals] Drummer"
layout: "post"
diff: 省选/NOI-
pid: P13303
tag: ['计算几何', '2013', 'Special Judge', '凸包', '旋转卡壳', 'Google Code Jam']
---
# [GCJ 2013 Finals] Drummer
## 题目描述

The drummer has a very important role in any band -- keeping the rhythm. If the drummer's rhythm is uneven, it can ruin the entire performance.

You are the lead singer of a very popular rock band, and you have a bit of a problem. Your drummer has just quit the band to become a professional video gamer. You need to find a new drummer immediately. Fortunately, there is no shortage of candidates. Everyone wants a chance to join your band. Your task is to find the best drummer among the candidates, and you want the person who can keep the most consistent rhythm.

Your plan is as follows. You will ask each candidate to audition individually. During the audition, the candidate will play one drum by striking it with a drum stick several times. Ideally, the time difference between consecutive strikes should be exactly the same, producing a perfect rhythm. In a perfect rhythm, the drum strikes will have time stamps that follow an arithmetic progression like this: $T_0$, $T_0 + K$, $T_0 + 2\times K$, $\dots$, $T_0 + (N - 1)\times K$.

In real life, of course, it is nearly impossible for a human to produce a perfect rhythm. Therefore, each candidate drummer will produce a rhythm that has an error $E$, such that each $T_i$ differs by at most $E$ from some perfect rhythm. Given a candidate's sequence of drum strikes, find the smallest possible $E$ among all perfect rhythms that the candidate might have been trying to play.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one consists of two lines and represents the audition of one candidate. The first line contains a single integer -- $N$. The next line contains $N$ integers separated by spaces -- the time stamps, in milliseconds, of the drum strikes played by the candidate. The time stamps are in increasing order.

## 输出格式

For each test case, output one line containing "Case #x: $E$", where $x$ is the case number (starting from 1) and $E$ is the smallest among all possible numbers that describe the error of the candidate's drum strike sequence.

Your answer will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
3
2
10 70
4
0 10 19 30
6
2 5 10 15 20 24
```
### 样例输出 #1
```
Case #1: 0
Case #2: 0.5
Case #3: 0.75
```
## 提示

**Limits**

- $1 \leq T \leq 100.$

**Small dataset (9 Pts, Test set 1 - Visible)**

- Time limit: ~~60~~ 6 seconds.
- $2 \leq N \leq 10.$
- $0 \leq T_i \leq 100.$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- For 90% of the test cases, $2 \leq N \leq 1000.$
- For all test cases, $2 \leq N \leq 50000.$
- $0 \leq T_i \leq 10^6.$


---

---
title: "[GCJ 2012 Finals] Twirling Towards Freedom"
layout: "post"
diff: 省选/NOI-
pid: P13335
tag: ['数学', '计算几何', '2012', 'Special Judge', '凸包', '旋转卡壳', 'Google Code Jam']
---
# [GCJ 2012 Finals] Twirling Towards Freedom
## 题目背景

> "I say we must move forward, not backward;
upward, not forward;    
> and always twirling, twirling, twirling towards freedom!"    
> — Former U.S. Presidential nominee Kodos.
## 题目描述

After hearing this inspirational quote from America's first presidential nominee from the planet Rigel VII, you have decided that you too would like to twirl (rotate) towards freedom. For the purposes of this problem, you can think of "freedom" as being as far away from your starting location as possible.

The galaxy is a two-dimensional plane. Your space ship starts at the origin, position $(0, 0)$. There are $N$ stars in the galaxy. Every minute, you can choose a star and rotate your space ship 90 degrees clockwise around the star. You may also choose to stay where you are.

How far away can you move from the origin after $M$ minutes?

![](https://cdn.luogu.com.cn/upload/image_hosting/3jmyptcf.png)

The image illustrates the first 3 rotations for a possible path in sample case 1. Note that this path is not necessarily a part of any optimal solution.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, beginning with two lines containing integers $N$ and $M$. The next $N$ lines each contain two integers, $X_i$ and $Y_i$, representing the locations of stars.

## 输出格式

For each test case, output one line containing "Case #$x$: $D$", where $x$ is the case number (starting from 1) and $D$ is the distance from the origin to the optimal final position. Answers with absolute or relative error no larger than $10^{-6}$ will be accepted.
## 样例

### 样例输入 #1
```
3
4
1
-2 4
1 -2
4 1
0 2
1
4
-5 0
2
5
-1 1
-2 2
```
### 样例输出 #1
```
Case #1: 6.3245553203
Case #2: 10.0000000000
Case #3: 6.3245553203
```
## 提示

**Limits**

- $1 \leq T \leq 100;$
- $-1000 \leq X_i \leq 1000;$
- $-1000 \leq Y_i \leq 1000.$
- No two stars will be at the same location.
- There may be a star at the origin.

**Test set 1 (10 Pts, Visible Verdict)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 10.$
- $1 \leq M \leq 10.$

**Test set 2 (39 Pts, Hidden Verdict)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 5000.$
- $1 \leq M \leq 10^8.$



---

---
title: "[GCJ 2010 #2] Grazing Google Goats"
layout: "post"
diff: 省选/NOI-
pid: P13402
tag: ['计算几何', '2010', 'Special Judge', '凸包', 'Google Code Jam']
---
# [GCJ 2010 #2] Grazing Google Goats
## 题目描述

Farmer John has recently acquired a nice herd of $N$ goats for his field. Each goat $i$ will be tied to a pole at some position $P_i$ using a rope of length $L_i$. This means that the goat will be able to travel anywhere in the field that is within distance $L_i$ of the point $P_i$, but nowhere else. (The field is large and flat, so you can think of it as an infinite two-dimensional plane.)

Farmer John already has the pole positions picked out from his last herd of goats, but he has to choose the rope lengths. There are two factors that make this decision tricky:

- The goats all need to be able to reach a single water bucket. Farmer John has not yet decided where to place this bucket. He has reduced the choice to a set of positions $\{Q_1, Q_2, \ldots, Q_M\}$, but he is not sure which one to use.
- The goats are ill-tempered, and when they get together, they sometimes get in noisy fights. For everyone's peace of mind, Farmer John wants to minimize the area $A$ that can be reached by all the goats.

Unfortunately, Farmer John is not very good at geometry, and he needs your help for this part!

For each bucket position $Q_j$, you should choose rope lengths so as to minimize the area $A_j$ that can be reached by every goat when the bucket is located at position $Q_j$. You should then calculate each of these areas $A_j$.

### Example

In the picture below, there are four blue points, corresponding to the pole positions: $P_1$, $P_2$, $P_3$, and $P_4$. There are also two red points, corresponding to the potential bucket positions: $Q_1$ and $Q_2$. You need to calculate $A_1$ and $A_2$, the areas of the two shaded regions.

![](https://cdn.luogu.com.cn/upload/image_hosting/mnv6gfis.png)
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integers $N$ and $M$.

The next $N$ lines contain the positions $P_1, P_2, \ldots, P_N$, one per line. This is followed by $M$ lines, containing the positions $Q_1, Q_2, \ldots, Q_M$, one per line.

Each of these $N + M$ lines contains the corresponding position's $x$ and $y$ coordinates, separated by a single space.

## 输出格式

For each test case, output one line containing "Case #$x$: $A_1$ $A_2$ ... $A_M$", where $x$ is the case number (starting from 1), and $A_1$ $A_2$ ... $A_M$ are the values defined above. Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
3
2 3
0 20
20 0
-20 10
40 20
0 19
4 2
0 0
100 100
300 0
380 90
400 100
1000 5
3 1
0 0
10 10
20 0
10 5
```
### 样例输出 #1
```
Case #1: 1264.9865911 1713.2741229 0.2939440
Case #2: 1518.9063729 1193932.9692206
Case #3: 0.0
```
## 提示

**Limits**

- All coordinates are integers between $-10,000$ and $10,000$.
- The positions $P_1, P_2, \ldots, P_N, Q_1, Q_2, \ldots, Q_M$ are all distinct and no three are collinear.

**Small dataset (7 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq T \leq 100$.
- $N = 2$.
- $1 \leq M \leq 10$.

**Large dataset (25 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- $1 \leq T \leq 10$.
- $2 \leq N \leq 5,000$.
- $1 \leq M \leq 1,000$.



---

---
title: "[SWERC 2023] Favourite dish"
layout: "post"
diff: 省选/NOI-
pid: P13798
tag: ['计算几何', '2023', '凸包', 'ICPC', '李超线段树']
---
# [SWERC 2023] Favourite dish
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/f4e13fe8cb3692d86fceaeba9e38456b9c240bed.png)

:::

France is a country of gastronomy. For a dish, both the taste and plating are important. Nevertheless, when different people evaluate a dish, some focus more on taste and some focus more on plating. At the Olympic Village dining hall, there are $N$ dishes, numbered from 1 to $N$; each dish has a score on its taste and a score on its plating. There are also $M$ persons, numbered from 1 to $M$; each person has a weight on taste and a weight on plating. One person's final score of a dish is the weighted average of the dish's scores on taste and plating.


The chefs at the Olympics want to provide everyone with their favourite dish on the evening of the closing ceremony. Your task is to calculate everyone's favourite dish. If multiple dishes tie for the highest score as a person's favourite, choose the one with the smallest number.


## 输入格式

Each line contains two space-separated integers. The first line contains the numbers $N$ and $M$. Then follow $N$ lines; the $k^\text{th}$ such line contains two integers $t_k$ and $p_k$, which are the scores of the dish $k$ on taste and on plating. Then come $M$ more lines; the $l^\text{th}$ such line contains two integers $T_l$ and $P_l$, which are the weights of person $l$ on taste and on plating.

**Limits**

- $1 \leq N \leq 500~000$;
- $1 \leq M \leq 500~000$;
- $0 \leq t_k \leq 1~000~000, 0 \leq p_k \leq 1~000~000$, and $(t_k, p_k) \neq (0, 0)$ for all $k \leq N$;
- $0 \leq T_l \leq 1~000~000, 0 \leq P_l \leq 1~000~000$, and $(T_l, P_l) \neq (0, 0)$ for all $l \leq M$;
- the $N$ pairs $(t_k, p_k)$ are pairwise distinct;
- the $M$ pairs $(T_l, T_l)$ are pairwise distinct.
## 输出格式

The output should contain $M$ lines. The $l^\text{th}$ such line should contain one number: the number of the favourite dish of person $l$.
## 样例

### 样例输入 #1
```
4 3
2 5
3 4
4 2
1 6
6 4
2 8
5 5
```
### 样例输出 #1
```
2
4
1
```
### 样例输入 #2
```
3 4
1 0
0 2
0 1
1 1
2 2
2 1
1 0
```
### 样例输出 #2
```
2
2
1
1
```
## 提示

**Sample Explanation 1**

Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$; person 3 has three tied favourite dishes, so we chose the first one.

|   | Dish | < | < | < |
|:-:|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 | 4 |
| 1 | $3.2$ | $3.4^\ast$ | $3.2$ | $3$ |
| 2 | $4.4$ | $3.8$ | $2.4$ | $5^\ast$ |
| 3 | $3.5^\ast$ | $3.5$ | $3$ | $3.5$ |

**Sample Explanation 2**


Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$.

|   | Dish | < | < |
|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 |
| 1 | $0.5$ | $1^\ast$ | $0.5$ |
| 2 | $0.5$ | $1^\ast$ | $0.5$ |
| 3 | $2/3^\ast$ | $2/3$ | $1/3$ |
| 4 | $1^\ast$ | $0$ | $0$ |



---

---
title: "[CERC 2022] Mortgage"
layout: "post"
diff: 省选/NOI-
pid: P13814
tag: ['线段树', '2022', '凸包', 'ICPC', 'CERC']
---
# [CERC 2022] Mortgage
## 题目描述

Andrej is a typical modern student, dreaming to buy a house one day. Since buying real property is no piece of cake, he is planning out his life and trying to figure out exactly how and when he will be able to afford one. To buy a house, he aims to take a mortgage loan that will then need to be paid back in multiple payments over the course of several months. For each of the next $n$ months of his life, he will earn the income $a_i$ that can be spent on the mortgage (other costs have already been accounted for, hence $a_i$ can be negative). He is now looking at a list of various properties and mortgage loans and is trying to figure out which of them he can afford.

Suppose that he takes a mortgage that involves paying $x$ units of money over the course of $k$ months, starting in month $i$, and ending in month $i + k - 1$. Each of these months, he needs to be able to pay $x$ units of money. If he has any leftover income in month $i$, i.e. $a_i > x$, he can save the rest and use it towards some of the future payments (same for any leftover money in months $i + 1$ to $i + k - 1$). However, he cannot count on saving any money prior to month $i$, regardless of the income in those months. He will spend it all on his current rent and avocado toast.

You are given the list of Andrej's income for the next $n$ months and a list of $m$ different time intervals. The $i$-th time interval is defined by two numbers, $s_i$, and $k_i$. The mortgage loan starts on the month $s_i$ and lasts for $k_i$ months, i.e. the last payment is done on the month $s_i + k_i - 1$. For each of the time intervals, determine what the largest monthly payment that Andrej can afford is.
## 输入格式

The first line contains two integers, $n$ and $m$, the number of months, and the number of different time intervals, respectively. The second line contains $n$ space-separated integers, $a_1, \ldots, a_n$, Andrej's income over the next $n$ months. This is followed by $m$ lines describing different time intervals, each line containing two space-separated integers $s_i$ and $k_i$.
## 输出格式

Print out $m$ lines, one for each time interval. Print out the largest integer amount of monthly payment that Andrej can afford to pay for the $i$-th mortgage. If the number is strictly smaller than 0, print "stay with parents" (without quotation marks).
## 样例

### 样例输入 #1
```
9 5
6 1 10 9 5 -2 3 1 -1
3 6
1 4
3 3
6 1
8 2
```
### 样例输出 #1
```
4
3
8
stay with parents
0
```
## 提示

### Comment

For the first interval, a monthly payment of $4$ units is the largest Andrej can afford. For a monthly payment of $5$, he would run out of money for his final payment. Negative income on month $6$ means that Andrej cannot afford any mortgage for interval $4$, regardless of its size.

### Input limits

- $1 \leq n, m \leq 2 \cdot 10^5$
- $-10^9 \leq a_i \leq 10^9$
- $1 \leq s_i \leq n; \forall i$
- $1 \leq k_i$ and $s_i + k_i - 1 \leq n; \forall i$


---

---
title: "【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G"
layout: "post"
diff: 省选/NOI-
pid: P1452
tag: ['计算几何', '2003', 'USACO', '枚举', '凸包', '旋转卡壳']
---
# 【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G
## 题目描述

给定平面上 $n$ 个点，求凸包直径。

## 输入格式

第一行一个正整数 $n$。   
接下来 $n$ 行，每行两个整数 $x,y$，表示一个点的坐标。保证所有点的坐标两两不同。
## 输出格式

输出一行一个整数，表示答案的平方。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 1
1 0

```
### 样例输出 #1
```
2
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$2\le n \le 50000$，$|x|,|y| \le 10^4$。

---

$\text{upd 2022.7.22}$：新增加四组 Hack 数据。


---

---
title: "[HNOI2004] 最佳包裹"
layout: "post"
diff: 省选/NOI-
pid: P2287
tag: ['动态规划 DP', '递推', '2004', '各省省选', '湖南', '凸包']
---
# [HNOI2004] 最佳包裹
## 题目描述

发强公司生产了一种金属制品，是由一些笔直的金属条连接起来的，金属条和别的金属条在交点上被焊接在了一起。现在由于美观需要，在这个产品用一层特殊的材料包裹起来。公司为了节约成本，希望消耗的材料最少（不计裁剪时的边角料的损失）。

编程，输入包括该产品的顶点的个数，以及所有顶点的坐标；请计算出包裹这个产品所需要的材料的最小面积。结果要求精确到小数点后第六位（四舍五入）。
## 输入格式

输入文件由 $(n+1)$ 行组成。

第 $1$ 行是一个整数 $n$（$4 \leq n \leq 100$），表示顶点的个数；

第 $2$ 行到第 $(n+1)$ 行，第 $(i+1)$ 行有 $3$ 个实数 $x_i$，$y_i$，$z_i$，表示第 $i$ 个顶点的坐标。

保证顶点的位置各不相同。
## 输出格式

输出文件只有一个实数，四舍五入精确到小数点后六位，表示包裹一个该产品所需的材料面积的最小值。
## 样例

### 样例输入 #1
```
4 

0 0 0

1 0 0

0 1 0

0 0 1


```
### 样例输出 #1
```
2.366025
```


---

---
title: "[HAOI2011] 防线修建"
layout: "post"
diff: 省选/NOI-
pid: P2521
tag: ['2011', '河南', '各省省选', '平衡树', '凸包']
---
# [HAOI2011] 防线修建
## 题目描述

近来A国和B国的矛盾激化，为了预防不测，A 国准备修建一条长长的防线，当然修建防线的话，肯定要把需要保护的城市修在防线内部了。  

可是A国上层现在还犹豫不决，到底该把哪些城市作为保护对象呢？又由于 A 国的经费有限，所以希望你能帮忙完成如下的一个任务：

1、给出你所有的 A 国城市坐标

2、A国上层经过讨论，考虑到经济问题，决定取消对 $u$ 城市的保护，也就是说 $u$ 城市不需要在防线内了

3、A国上层询问对于剩下要保护的城市，修建防线的总经费最少是多少

你需要对每次询问作出回答。注意单位长度的防线花费为 $1$。

A 国的地形是这样的，形如下图，$x$ 轴是一条河流，相当于一条天然防线，不需要你再修建。

![](https://cdn.luogu.com.cn/upload/image_hosting/rkaw5kay.png)

A 国总是有两个城市在河边，一个点是 $(0,0)$，一个点是 $(n,0)$，其余所有点的横坐标均在 $(0,n)$ 范围内，纵坐标均大于0。  
A国有一个不在 $(0,0)$ 和 $(n,0)$ 的首都。$(0,0),(n,0)$ 和首都这三个城市是一定需要保护的。

上图中，A,B,C,D,E 点为 A 国城市，且目前都要保护，那么修建的防线就会是 A-B-C-D，花费也就是线段 AB 的长度+线段 BC 的长度+线段 CD 的长度,如果，这个时候撤销 B 点的保护，那么防线变成下图

![](https://cdn.luogu.com.cn/upload/image_hosting/cd7dpmcj.png)

## 输入格式

第一行三个整数 $n,x,y$ 分别表示河边城市和首都是 $(0,0),(n,0),(x,y)$。

第二行一个整数 $m$。

接下来 $m$ 行，每行两个整数 $a,b$ 表示 A 国的一个非首都非河边城市的坐标为 $(a,b)$。

再接下来一个整数 $q$，表示修改和询问总数。


接下来 $q$ 行每行要么形如 `1 u`，要么形如 `2`，分别表示撤销第 $u$ 个城市的保护和询问。

## 输出格式

对于每个询问输出一行一个实数 $v$，表示修建防线的花费，保留两位小数。

## 样例

### 样例输入 #1
```
4 2 1                                
2                                 
1 2                               
3 2                               
5                                 
2
1 1
2
1 2
2
```
### 样例输出 #1
```
6.47
5.84
4.47
```
## 提示

【数据范围】   
对于 $30\%$ 的数据，$1\le m,q \le 1000$；   
对于 $100\%$ 的数据，$1\le m \le 10^5$，$1\le q \le 2 \times 10^5$，$1 < n \le 10^4$。

所有点的坐标范围均在 $10^4$ 以内, 数据保证没有重点。

---

~~$\text{upd 2022.7.21}$：新增加一组 Hack 数据。~~ 该数据有误，已经被移除。


---

---
title: "[USACO08DEC] Largest Fence G"
layout: "post"
diff: 省选/NOI-
pid: P2924
tag: ['数学', '2008', 'USACO', '素数判断,质数,筛法', '凸包']
---
# [USACO08DEC] Largest Fence G
## 题目描述

Farmer John has purchased N (5 <= N <= 250) fence posts in order to build a very nice-looking fence. Everyone knows the best fences are convex polygons where fence posts form vertices of a polygon. The pasture is represented as a rectilinear grid; fencepost i is at integer coordinates (x\_i, y\_i) (1 <= x\_i <= 1,000; 1 <= y\_i <= 1000).

Given the locations of N fence posts (which, intriguingly, feature no set of three points which are collinear), what is the largest number of fence posts FJ can use to create a fence that is convex?

For test cases worth 45% of the points for this problem, N <= 65.

Time limit: 1.2 seconds

POINTS: 400

Farmer John的农场里有N（5<=N<=250）个篱笆桩，每个都有独一无二的坐标(xi,yi)（1<=xi,yi<=1000）。他想选择尽量多的篱笆桩来构建他的围栏。这个围栏要美观，所以必须是凸多边形的。那他最多能选多少个呢？

所有的篱笆桩中不存在三点共线。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 describes fence post i's location with two space-separated integers: x\_i and y\_i

## 输出格式

\* Line 1: A single integer, the maximum possible number of fence posts that form a convex polygon.

## 样例

### 样例输入 #1
```
6 
5 5 
2 3 
3 2 
1 5 
5 1 
1 1 

```
### 样例输出 #1
```
5 

```
## 提示

A square with two points inside.


The largest convex polygon is the pentagon (2,3), (3,2), (5,1), (5,5), (1,5).



---

---
title: "[USACO15FEB] Fencing the Herd G"
layout: "post"
diff: 省选/NOI-
pid: P3122
tag: ['计算几何', '2015', 'USACO', 'cdq 分治', '凸包']
---
# [USACO15FEB] Fencing the Herd G
## 题目描述

Farmer John 需要你帮助他决定在哪里建造形状是一条无限长的直线的栅栏来限制他的牛的活动。他选出了几个可能的建造栅栏的位置，你需要帮助他判断哪些栅栏是有用的。一个栅栏是有用的当且仅当所有奶牛都在栅栏的同一侧。（如果有牛群在栅栏所在的直线上，那么栅栏是没用的），Farmer John 将会多次询问你一个栅栏是否有用，如果这个栅栏是有用的，需要输出 `YES`，反之输出 `NO`。

另外，Farmer John 也可能会带来一些新的奶牛加入这个牛群。一头牛加入之后，以后的所有询问中，这头牛也需要与其它的牛在栅栏的同一侧。

## 输入格式


第一行，两个正整数 $n,q$，表示初始时牛群的数量与询问个数；

后 $n$ 行，每行两个整数 $x,y$，表示一个牛群的初始位置；

后 $q$ 行，每行多个整数，表示一次询问，询问的格式如下：

- 1 $x$ $y$：表示一个新的牛群加入了牧场，驻留在 $(x,y)$ 上；
- 2 $A$ $B$ $C$：表示 Farmer John 询问栅栏 $Ax+By=C$ 是否有用。
## 输出格式

对于每个 $2$ 类型的询问，如果栅栏有用，输出 `YES`，否则输出 `NO`。

## 样例

### 样例输入 #1
```
3 4 
0 0 
0 1 
1 0 
2 2 2 3 
1 1 1 
2 2 2 3 
2 0 1 1 

```
### 样例输出 #1
```
YES 
NO 
NO 


```
## 提示

直线 $2x+2y=3$ 使得初始的三个牛群都在同侧；然而在该栅栏另一侧的牛群 $(1,1)$ 的加入使得它没有用了。

直线 $y=1$ 没用因为牛群 $(0,1)$，$(1,1)$ 恰好在它上面。

---

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^5$，$1\leq q\leq 10^5$，所有牛群的坐标都各不相同且满足 $-10^9\leq x,y\leq 10^9$，$-10^9\leq A,B\leq 10^9$，$-10^{18}\leq C\leq 10^{18}$。

数据保证不存在栅栏满足 $A=B=0$。


---

---
title: "[HNOI2007] 最小矩形覆盖"
layout: "post"
diff: 省选/NOI-
pid: P3187
tag: ['2007', '湖南', 'Special Judge', '枚举', '凸包', '旋转卡壳']
---
# [HNOI2007] 最小矩形覆盖
## 题目描述

给定一些点的坐标，求能够覆盖所有点的最小面积的矩形，输出所求矩形的面积和四个顶点坐标。
## 输入格式

第一行为一个整数 $n$，从第 $2$ 至第 $n+1$ 行每行有两个浮点数（精确到至多五位小数，不使用科学计数法），表示一个顶点的 $x$ 和 $y$ 坐标。
## 输出格式

第一行为一个浮点数，表示所求矩形的面积，接下来 $4$ 行每行表示一个顶点坐标，**按逆时针**输出顶点坐标。
## 样例

### 样例输入 #1
```
6
1.0 3.00000
1 4.00000
2.0000 1
3 0.0000
3.00000 6
6.0 3.0
```
### 样例输出 #1
```
18.00000
3.00000 0.00000
6.00000 3.00000
3.00000 6.00000
0.00000 3.00000
```
## 提示

$3 \le n \le 50000$，坐标范围 $\in [0,10]$。保证覆盖所有点所需要的最小矩形面积至少是 $0.1$。

如果你的矩形面积为 $S'$，正确答案为 $S$，那么当 $\frac{|S'-S|}{\max\{1,S\}}<10^{-4}$，且所有点满足在矩形内或者到矩形的距离 $<10^{-4}$ 时，你的答案会被判定为正确（你可以忽略这段话，简而言之你的答案只要不是有特别大的精度误差就可以通过）。

感谢 @intruder 提供题目简述



---

---
title: "[HNOI2012] 射箭"
layout: "post"
diff: 省选/NOI-
pid: P3222
tag: ['2012', '二分', '湖南', '凸包', '半平面交']
---
# [HNOI2012] 射箭
## 题目描述

沫沫最近在玩一个二维的射箭游戏，如下图 $1$ 所示，这个游戏中的 $x$ 轴在地面，第一象限中有一些竖直线段作为靶子，任意两个靶子都没有公共部分，也不会接触坐标轴。

沫沫控制一个位于 $(0,0)$ 的弓箭手，可以朝 $0$ 至 $90$ 中的任意角度（不包括 $0$ 度和 $90$ 度），以任意大小的力量射出带有穿透能力的光之箭。由于游戏中没有空气阻力，并且光之箭没有箭身，箭的轨迹会是一条标准的抛物线，被轨迹穿过的所有靶子都认为被沫沫射中了，包括那些只有端点被射中的靶子。

这个游戏有多种模式，其中沫沫最喜欢的是闯关模式。

在闯关模式中，第一关只有一个靶子，射中这个靶子即可进入第二关，这时在第一关的基础上会出现另外一个靶子，若能够一箭双雕射中这两个靶子便可进入第三关，这时会出现第三个靶子。依此类推，每过一关都会新出现一个靶子，在第 $K$ 关必须一箭射中前 $K$ 关出现的所有 $K$ 个靶子才能进入第 $K+1$ 关，否则游戏结束。

沫沫花了很多时间在这个游戏上，却最多只能玩到第七关“七星连珠”，这让她非常困惑。于是她设法获得了每一关出现的靶子的位置，想让你告诉她，最多能通过多少关？
## 输入格式

输入文件第一行是一个正整数 $N$，表示一共有 $N$ 关。

接下来有 $N$ 行，第 $i+1$ 行是用空格隔开的三个正整数 $x_i,y_{i1},y_{i2}\ (y_{i1}<y_{i2})$，表示第 $i$ 关出现的靶子的横坐标是 $x_i$，纵坐标的范围是从 $y_{i1}$ 到 $y_{i2}$。
## 输出格式

仅包含一个整数，表示最多的通关数。

## 样例

### 样例输入 #1
```
5
2  8 12
5  4 5
3  8 10
6  2 3
1  3 7
```
### 样例输出 #1
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/jv279yqz.png)

### 数据范围及约定

- $30\%$ 的数据满足 $N \le 100$；
- $50\%$ 的数据满足 $N \le 5000$；
- $100\%$ 的数据满足 $N \le 100000$ 且给出的所有坐标不超过 $10^9$。


---

---
title: "[SCOI2016] 妖怪"
layout: "post"
diff: 省选/NOI-
pid: P3291
tag: ['2016', '四川', '二分', '枚举', '凸包']
---
# [SCOI2016] 妖怪
## 题目描述


邱老师是妖怪爱好者，他有 $n$ 只妖怪，每只妖怪有攻击力 $\mathrm{atk}$ 和防御力 $\mathrm{dnf}$ 两种属性。邱老师立志成为妖怪大师，于是他从真新镇出发，踏上未知的旅途，见识不同的风景。

环境对妖怪的战斗力有很大影响，环境 $(a,b)$ 由 $a,b$ 两个参数定义，其中 $a,b$ 为**正实数**。在环境 $(a,b)$ 中，妖怪可以降低自己 $k\times a$ 点攻击力，提升 $k\times b$ 点防御力或者提升自己 $k\times a$ 点攻击力，降低 $k\times b$ 点防御力。其中 $k$ 为**任意实数**，但是 **$\mathrm{atk}$ 和 $\mathrm{dnf}$ 必须始终非负**。

妖怪在环境 $(a,b)$ 中的**战斗力** $\mathrm{strength}$ 定义为妖怪在该种环境中能达到的最大攻击力和最大防御力之和，即 $\mathrm{strength}(a,b)=\max(\mathrm{atk}(a,b))+\max(\mathrm{dnf}(a,b))$。

比如当前环境 $a=3,b=2$，那么攻击力为 $6$，防御力为 $2$ 的妖怪，能达到的最大攻击力为 $9$，最大防御力为 $6$。所以该妖怪在 $a=3,b=2$ 的环境下战斗力为 $15$。

因此，在不同的环境，战斗力最强的妖怪可能发生变化。

作为一名优秀的妖怪训练师，邱老师想发掘每一只妖怪的最大潜力，他想知道在**最为不利的情况下**，他的 $n$ 只妖怪能够达到的最强战斗力值。换言之，存在一组正实数 $(a,b)$ 使得 $n$ 只妖怪在该环境下最强战斗力最低，你需要输出这个最低的战斗力。
## 输入格式

第一行一个n，表示有 $n$ 只妖怪。

接下来 $n$ 行，每行两个整数 $\mathrm{atk}_i$ 和 $\mathrm{dnf}_i$，表示第 $i$ 只妖怪的攻击力和防御力。

## 输出格式

输出在最不利情况下最强妖怪的战斗力值，保留 $4$ 位小数。
## 样例

### 样例输入 #1
```
3
1 1
1 2
2 2
```
### 样例输出 #1
```
8.0000
```
## 提示


对于 $100\%$ 的数据，$1\le n\le 10^6$，$0\lt \mathrm{atk},\mathrm{dnf}\le 10^8$。

Statement fixed by Starrykiller.


---

---
title: "[SDOI2013] 保护出题人"
layout: "post"
diff: 省选/NOI-
pid: P3299
tag: ['2013', '山东', '凸包']
---
# [SDOI2013] 保护出题人
## 题目描述

出题人铭铭认为给SDOI2012出题太可怕了，因为总要被骂，于是他又给SDOI2013出题了。


参加SDOI2012的小朋友们释放出大量的僵尸，企图攻击铭铭的家。而你作为SDOI2013的参赛者，你需要保护出题人铭铭。


僵尸从唯一一条笔直道路接近，你们需要在铭铭的房门前放置植物攻击僵尸，避免僵尸碰到房子。


第一关，一只血量为$a_1$点的墦尸从距离房子$x_1$米处速接近，你们放置了攻击力为$y_1$点/秒的植物进行防御；第二关，在上一关基础上，僵尸队列排头增加一只血量为$a_2$点的僵尸，与后一只僵尸距离$d$米，从距离房$x_2$米处匀速接近，你们重新放置攻击力为$y_2$点/秒的植物；……；第$n$关，僵尸队列共有$n$只僵尸，相邻两只僵尸距离$d$米，排头僵尸血量为$a_n$点，排第二的 僵尸血量$a_{n-1}$，以此类推，排头僵尸从距离房子$x_n$米处匀速接近，其余僵尸跟随排头同时接近，你们重新放置攻击力为$y_n$点/秒的植物。


每只僵尸直线移动速度均为$1$米/秒，由于植物射击速度远大于僵尸移动速度，可忽略植物子弹在空中的时间。所有僵尸同时出现并接近，因此当一只僵尸死亡后，下一只僵尸立刻开始受到植物子弹的伤害。


游戏得分取决于你们放置的植物攻击力的总和$\sum \limits _{i=1} ^{n} y_i$，和越小分数越高，为了追求分数上界，你们每关都要放置攻击力尽量小的植物。


作为SDOI2013的参赛选手，你们能保护出题人么？

## 输入格式

第一行两个空格隔开的正整数n和d，分别表示关数和相邻僵尸间的距离。

接下来n行每行两个空格隔开的正整数，第i + 1行为Ai和 Xi，分别表示相比上一关在僵尸队列排头增加血量为Ai 点的僵尸，排头僵尸从距离房子Xi米处开始接近。

## 输出格式

一个数，n关植物攻击力的最小总和 ，保留到整数。

## 样例

### 样例输入 #1
```
5  2
3  3
1  1
10 8
4  8
2  3
```
### 样例输出 #1
```
7
```
## 提示

第一关：距离房子3米处有一只血量3点的僵尸，植物最小攻击力为1.00000；  
第二关：距离房子1米处有一只血量1点的僵尸、3米处有血量3点的僵尸，植物最小攻击力为1.33333；  
第三关：距离房子8米处有一只血量10点的僵尸、10米处有血量1点的僵尸、12米处有血量3点的僵尸，植物最小攻击力为1.25000；  
第四关：距离房子8米处有一只血量4点的僵尸、10米处有血量10点的僵尸、12米处有血量1点的僵尸、14米处有血量3点的僵尸，植物最小攻击力为1.40000；  
第五关：距离房子3米处有一只血量2点的僵尸、5米处有血量4点的僵尸、7米处有 血量10点的僵尸、9米处有血量1点的僵尸、11米处有血量3点的僵尸，植物最小攻击力 为2.28571。  
植物攻击力的最小总和为7.26905。

对于100%的数据， $ 1\le n \le 10^5  ,1 \le d,x,a \le 10^{12} $ 。



---

---
title: "[SDOI2014] 向量集"
layout: "post"
diff: 省选/NOI-
pid: P3309
tag: ['2014', '线段树', '山东', '向量', '凸包']
---
# [SDOI2014] 向量集
## 题目描述

维护一个向量集合，在线支持以下操作：

- `A x y`（$|x|,|y| \le 10^8$）：加入向量 $(x,y)$；
- `Q x y l r`（$|x|,|y| \le 10^8$，$1 \le l \le r \le t$，其中 $t$ 为已经加入的向量个数）：询问第 $l$ 个到第 $r$ 个加入的向量与向量 $(x,y)$ 的点积的最大值。

集合初始时为空。
## 输入格式

输入的第一行包含整数 $N(1 \le N \le 4 \times 10^5)$ 和字符 $s$，分别表示操作数和数据类别；

接下来 $N$ 行，每行一个操作，格式如上所述。    

请注意 $s$ 不为 `E` 时，输入中的所有整数都经过了加密。你可以使用以下程序得到原始输入：

```
inline int decode(int x, long long lastans) {    
    return x ^ (lastans & 0x7fffffff);
}
```

其中 `x` 为程序读入的数，`lastans` 为之前最后一次询问的答案。在第一次询问之前，`lastans` 为 $0$。注：向量 $(x, y)$ 和 $(z, w)$ 的点积定义为 $xz+yw$。
## 输出格式

对每个 `Q` 操作，输出一个整数表示答案。
## 样例

### 样例输入 #1
```
6 A
A 3 2
Q 1 5 1 1
A 15 14
A 12 9
Q 12 8 12 15
Q 21 18 19 18
```
### 样例输出 #1
```
13
17
17

```
## 提示

样例解释：解密之后的输入为
```
    6 E
    A 3 2
    Q 1 5 1 1
    A 2 3
    A 1 4
    Q 1 5 1 2
    Q 4 3 2 3
```



---

---
title: "[POI 2006] NAJ-The Invasion"
layout: "post"
diff: 省选/NOI-
pid: P3442
tag: ['2006', 'POI（波兰）', '凸包']
---
# [POI 2006] NAJ-The Invasion
## 题目描述

And so it has come - the Triangles have invaded Byteotia!

Byteotia lies on an island, occupying its entire surface.

The shape of the island is a convex polygon(i.e. a polygon whose each inner angle is smaller than $180\degree$).

A certain number of software factories are located in Byteotia, each of which generates constant gains or losses.

The Triangles have decided to occupy such a part of Byteotia which:

is a triangle-shaped area, the vertices of which are three different vertices of the polygon-island,     brings the largest income i.e. the sum of all gains and losses generated by factories within the occupied area is maximal.

We assume that a factory located on the border or in the vertex of occupied area belongs to that area. A territory which contains no factory brings, obviously, a zero income.

Byteasar, the King of Byteotia, is concerned by the amount of losses the Triangles' invasion could generate. Help him by writing a programme which shall calculate the sum of gains and losses generated by factories which the Triangles wish to capture.

TaskWrite a programme which:

reads a decription of Byteotia's shape and the locations of factories from the input file,     determines the maximal value of sum of all gains and losses generated by factories within a triangle, whose vertices are three different vertices of the polygon island,     writes the outcome to the output file.

给定一个凸包， 并给出凸包内部或边上的若干个资源，每个资源都有权值,现在要在凸包上面选择不同的3个点，使得3个点组成的三角形


内部的资源的权值之和最大。


凸包点个数 $n \le 600$


资源个数 $m \le 10000$

## 输入格式

The first line of the input file contains a single integer $n$ ($3 \le n \le 600$), denoting the number of vertices of the polygon-island.

The following $n$ lines of the input contain two integers each $x_j$ and $y_j$ ($-10\ 000 \le x_j, y_j \le 10\ 000$), separated by a single space, denoting the coordinates $x$ and $y$ of consecutive vertices of the island, in a clockwise order.

The $(n+2)$-nd line contains a single integer $m$ ($1 \le m \le 10\ 000$), denoting thetotal number of factories.

In each of the following $m$ lines there are three integers $x_i'$, $y_i'$ and $w_i$ ($-10\ 000 \le x_i', y_i' \le 10\ 000$, $-100\ 000 \le w_i \le 100\ 000$), separated by single spaces, denoting: the coordinates $x$ and $y$ of the $i$-th factory and the gain (for $w_i \ge 0$) or loss (for $w_i < 0$) this factory generates, respectively. Each factory is situated on the polygon-island i.e. within or on the border of it. Distinct factories may be located in the same place i.e. have the same coordinates.

## 输出格式

The first and only line of the output file should contain a single integer denoting the maximal value of sum of all gains and losses generated by factories within a triangle whose vertices are three different vertices of the polygon-island. Notice that it may happen that the outcome is a negative integer.

## 样例

### 样例输入 #1
```
5
4 1
1 4
8 9
11 5
8 1
4
7 2 3
6 3 -1
4 5 3
9 6 -4
```
### 样例输出 #1
```
5
```
## 提示

the correct result is:

![](https://cdn.luogu.com.cn/upload/pic/6970.png)



---

---
title: "[CERC2016] 凸轮廓线 Convex Contour"
layout: "post"
diff: 省选/NOI-
pid: P3680
tag: ['字符串', '数学', '计算几何', '2016', 'Special Judge', '凸包']
---
# [CERC2016] 凸轮廓线 Convex Contour
## 题目描述

一些几何图形整齐地在一个网格图上从左往右排成一列。它们占据了连续的一段横行，每个位置恰好一个几何图形。每个图形是以下的三种之一：


1. 一个恰好充满单个格子的正方形。


2. 一个内切于单个格子的圆。


3. 一个底边与格子重合的等边三角形。


 ![](https://cdn.luogu.com.cn/upload/pic/4685.png) 

已知每个格子的边长都为 $1$，请求出这些几何图形的凸包的周长。
## 输入格式

第一行包含一个正整数 $n$，表示几何图形的个数。

第二行包含 $n$ 个字符，从左往右依次表示每个图形，`S` 表示正方形，`C` 表示圆形，`T` 表示等边三角形。

## 输出格式

输出一行一个实数，即凸包的周长。与答案的绝对或相对误差不超过 $10^{-6}$ 时被认为是正确的。
## 样例

### 样例输入 #1
```
4
TSTC
```
### 样例输出 #1
```
9.088434417

```
## 提示

对于 $100\%$ 的数据，$1 \le n \le 20$。


---

---
title: "[NOI2007] 货币兑换"
layout: "post"
diff: 省选/NOI-
pid: P4027
tag: ['2007', 'NOI', 'Special Judge', '分治', '斜率优化', '凸包']
---
# [NOI2007] 货币兑换
## 题目描述

小 Y 最近在一家金券交易所工作。该金券交易所只发行交易两种金券：A 纪念券（以下简称 A 券）和 B 纪念券（以下简称 B 券）。每个持有金券的顾客都有一个自己的帐户。金券的数目可以是一个实数。

每天随着市场的起伏波动，两种金券都有自己当时的价值，即每一单位金券当天可以兑换的人民币数目。我们记录第 $K$ 天中 A 券和 B 券的价值分别为 $A_K$ 和 $B_K$（元/单位金券）。

为了方便顾客，金券交易所提供了一种非常方便的交易方式：比例交易法。

比例交易法分为两个方面：

a)  卖出金券：顾客提供一个 $[0, 100]$ 内的实数 $OP$ 作为卖出比例，其意义为：将 $OP\%$ 的 A 券和 $OP\%$ 的 B 券以当时的价值兑换为人民币；

b)  买入金券：顾客支付 $IP$ 元人民币，交易所将会兑换给用户总价值为 $IP$ 的金券，并且，满足提供给顾客的 A 券和 B 券的比例在第 $K$ 天恰好为 $\mathrm{Rate}_ K$；

例如，假定接下来 $3$ 天内的 $A_K,B_K,\mathrm{Rate}_ K$ 的变化分别为：

| 时间 | $A_K$ | $B_K$ | $\mathrm{Rate}_ K$ |
| ----- | ----- | ----- | ----- |
| 第一天 | $1$ | $1$ | $1$ |
| 第二天 | $1$ | $2$ | $2$ |
| 第三天 | $2$ | $2$ | $3$ |



假定在第一天时，用户手中有 $100$ 元人民币但是没有任何金券。

用户可以执行以下的操作：

| 时间 | 用户操作 | 人民币(元) | A 券的数量 | B 券的数量 |
| ----- | ----- | ----- | ----- | ----- |
| 开户 | 无 | $100$ | $0$ | $0$ |
| 第一天 | 买入 $100$ 元 | $0$ | $50$ | $50$ |
| 第二天 | 卖出 $50\%$ | $75$ | $25$ | $25$ |
| 第二天 | 买入 $60$ 元 | $15$ | $55$ | $40$ |
| 第三天 | 卖出 $100\%$ | $205$ | $0$ | $0$ |

注意到，同一天内可以进行多次操作。

小 Y 是一个很有经济头脑的员工，通过较长时间的运作和行情测算，他已经知道了未来 $N$ 天内的 A 券和 B 券的价值以及 $\mathrm{Rate}$。他还希望能够计算出来，如果开始时拥有 $S$ 元钱，那么 $N$ 天后最多能够获得多少元钱。

## 输入格式

第一行两个正整数 $N,S$，分别表示小 Y 能预知的天数以及初始时拥有的钱数。

接下来 $N$ 行，第 $K$ 行三个实数 $A_K,B_K,\mathrm{Rate} _ K$ ，意义如题目中所述。

## 输出格式

只有一个实数 $\mathrm{MaxProfit}$，表示第 $N$ 天的操作结束时能够获得的最大的金钱数目。答案保留 $3$ 位小数。

## 样例

### 样例输入 #1
```
3 100
1 1 1
1 2 2
2 2 3
```
### 样例输出 #1
```
225.000
```
## 提示

| 时间 | 用户操作 | 人民币(元) | A 券的数量 | B 券的数量 |
| ----- | ----- | ----- | ----- | ----- |
| 开户 | 无 | $100$ | $0$ | $0$ |
| 第一天 | 买入 $100$ 元 | $0$ | $50$ | $50$ |
| 第二天 | 卖出 $100\%$ | $150$ | $0$ | $0$ |
| 第二天 | 买入 $150$ 元 | $0$ | $75$ | $37.5$ |
| 第三天 | 卖出 $100\%$ | $225$ | $0$ | $0$ |


本题没有部分分，你的程序的输出只有和标准答案相差不超过 $0.001$ 时，才能获得该测试点的满分，否则不得分。


测试数据设计使得精度误差不会超过 $10^{-7}$ 。

对于 $40\%$ 的测试数据，满足 $N \le 10$。

对于 $60\%$ 的测试数据，满足 $N \le 1 000$。

对于 $100\%$ 的测试数据，满足 $N \le 10^5$。

对于 $100\%$ 的测试数据，满足：

$0 < A_K \leq 10$，$0 < B_K\le 10$，$0 < \mathrm{Rate}_K \le 100$，$\mathrm{MaxProfit}  \leq 10^9$。

输入文件可能很大，请采用快速的读入方式。

必然存在一种最优的买卖方案满足：

每次买进操作使用完所有的人民币，每次卖出操作卖出所有的金券。



---

---
title: "[JSOI2007] 合金"
layout: "post"
diff: 省选/NOI-
pid: P4049
tag: ['2007', '各省省选', '江苏', '图论建模', '最短路', '凸包']
---
# [JSOI2007] 合金
## 题目描述

某公司加工一种由铁、铝、锡组成的合金。他们的工作很简单。首先进口一些铁铝锡合金原材料，不同种类的原材料中铁铝锡的比重不同。然后，将每种原材料取出一定量，经过融解、混合，得到新的合金。新的合金的铁铝锡比重为用户所需要的比重。 

现在，用户给出了 $n$ 种他们需要的合金，以及每种合金中铁铝锡的比重。公司希望能够订购最少种类的原材料，并且使用这些原材料可以加工出用户需要的所有种类的合金。
## 输入格式

第一行两个整数 $m$ 和 $n$，分别表示原材料种数和用户需要的合金种数。

第 $2$ 到 $m+1$ 行，每行三个实数 $a_i, b_i, c_i$，分别表示铁铝锡在一种原材料中所占的比重。

第 $m+2$ 到 $m+n+1$ 行，每行三个实数 $d_i, e_i, f_i$，分别表示铁铝锡在一种用户需要的合金中所占的比重。
## 输出格式

一个整数，表示最少需要的原材料种数。若无解，则输出 `–1`。
## 样例

### 样例输入 #1
```
10 10
0.1 0.2 0.7
0.2 0.3 0.5
0.3 0.4 0.3
0.4 0.5 0.1
0.5 0.1 0.4
0.6 0.2 0.2
0.7 0.3 0
0.8 0.1 0.1
0.9 0.1 0
1 0 0
0.1 0.2 0.7
0.2 0.3 0.5
0.3 0.4 0.3
0.4 0.5 0.1
0.5 0.1 0.4
0.6 0.2 0.2
0.7 0.3 0
0.8 0.1 0.1
0.9 0.1 0
1 0 0
```
### 样例输出 #1
```
5
```
## 提示

#### 数据规模与约定

对于全部的测试点，满足 $1\le m,n\le 500$，$0 \leq a_i,b_i,c_i,d_i,e_i,f_i \leq 1$，且 $a_i+b_i+c_i=1$，$d_i+e_i+f_i=1$，小数点后最多有六位数字。


---

---
title: "[SDOI2016] 征途"
layout: "post"
diff: 省选/NOI-
pid: P4072
tag: ['2016', '各省省选', '单调队列', '山东', 'O2优化', '斜率优化', '前缀和', '凸包']
---
# [SDOI2016] 征途
## 题目描述

Pine 开始了从 $S$ 地到 $T$ 地的征途。

从 $S$ 地到 $T$ 地的路可以划分成 $n$ 段，相邻两段路的分界点设有休息站。

Pine 计划用 $m$ 天到达 $T$ 地。除第 $m$ 天外，每一天晚上 Pine 都必须在休息站过夜。所以，一段路必须在同一天中走完。

Pine 希望每一天走的路长度尽可能相近，所以他希望每一天走的路的长度的方差尽可能小。

帮助 Pine 求出最小方差是多少。

设方差是 $v$，可以证明，$v\times m^2$ 是一个整数。为了避免精度误差，输出结果时输出 $v\times m^2$。
## 输入格式

第一行两个数 $n, m$。

第二行 $n$ 个数，表示 $n$ 段路的长度。
## 输出格式

一个数，最小方差乘以 $m^2$ 后的值。
## 样例

### 样例输入 #1
```
5 2
1 2 5 8 6
```
### 样例输出 #1
```
36
```
## 提示

### 数据范围及约定

- 对于 $30\%$ 的数据，$1 \le n \le 10$；
- 对于 $60\%$ 的数据，$1 \le n \le 100$；
- 对于 $100\%$ 的数据，$1 \le n \le 3000$。

保证从 $S$ 到 $T$ 的总路程不超过 $3\times 10^4$。

$2 \leq m \leq n+1$，每段路的长度为不超过 $3 \times 10^4$ 的**正整数**。


---

---
title: "[SCOI2007] 最大土地面积"
layout: "post"
diff: 省选/NOI-
pid: P4166
tag: ['2007', '四川', '各省省选', '枚举', '向量', '凸包', '叉积']
---
# [SCOI2007] 最大土地面积
## 题目描述

在某块平面土地上有N个点，你可以选择其中的任意四个点，将这片土地围起来，当然，你希望这四个点围成的多边形面积最大。

## 输入格式

第1行一个正整数N，接下来N行，每行2个数x,y，表示该点的横坐标和纵坐标。

## 输出格式

最大的多边形面积，答案精确到小数点后3位。

## 样例

### 样例输入 #1
```
5
0 0
1 0
1 1
0 1
0.5 0.5
```
### 样例输出 #1
```
1.000
```
## 提示

数据范围 n<=2000, |x|,|y|<=100000



---

---
title: "[WC2010] 能量场"
layout: "post"
diff: 省选/NOI-
pid: P4293
tag: ['计算几何', '2010', 'Special Judge', '凸包', 'WC']
---
# [WC2010] 能量场
## 题目背景


官方spj：https://www.luogu.org/paste/03wjc4ne

spj provider: @hehezhou 
## 题目描述

物理学家栋栋最近在研究一个能量场。在这个能量场中有n个粒子，每个粒子都有两个属性：质量m和结合系数c。  

栋栋发现，在这个能量场中，每个粒子都有两极，N极和S极。两个粒子相遇时，符合“同极相斥，异极相吸”的原则，只能是一个粒子的N极和另一个粒子的S极连接到一起。当质量为ma，结合系数为ca的粒子a的N极与另一个质量为mb，结合系数为cb的粒子b的S极直接连接时，可以产生大小为  $m_a m_b (c_a - c_b)$  的结合能量。    

请解决以下两个问题：  
1. 在能量场的n个粒子中哪两个粒子直接连接的能量最大。  
2. 栋栋发明了一种方法，能选择其中的任意k个粒子p1, p2, …, pk，将pi的 N极与pi+1的S极连接(1 ≤ i < k)， pk的N极与p1的S极连接， 其中p1, p2, …, pk两两不同。k可以在1至n中任意取值，如使用栋栋的这种方法连接，选择哪些粒子可以得到最大的能量。
## 输入格式

第一行包含一个整数n，表示粒子的个数。 

 接下来n行，每行两个实数，第i+1行的两个实数表示第i个粒子的质量mi和结合系数ci。(0< mi, ci <10^5)
## 输出格式

第一行包含两个整数a, b，表示将粒子a的N极与粒子b的S极连接可以得到最大的能量。  

第二行包含一个整数k，表示第二问中要得到最大的能量需要多少个粒子。 第三行包含k个整数，表示p1, p2, …, pk，即第二问中的最优方案。
## 样例

### 样例输入 #1
```
4  
1.0 2.0 
3.0 1.0 
5.0 4.0 
2.0 2.0
```
### 样例输出 #1
```
3 2 
3  
1 3 2
```
## 提示

【样例说明】  
对于第一问，第三个粒子的N极与第二个粒子的S极连接，能得到的能量为$5\times3\times(4-1) = 45$。  

对于第二问，顺次连接1, 3, 2号粒子，能量为  $1\times5\times(2-4) + 5\times3\times(4-1) + 3\times1\times(1-2) = 32$。 

【数据规模】  

10%的数据，n ≤ 8； 

20%的数据，n ≤ 15； 

40%的数据，n ≤ 1 000；

50%的数据，n ≤ 5 000； 

100%的数据，n ≤ 50 000。 

【评分标准】  

此题可能有多解，如果用你的解产生的能量与参考答案的绝对误差或相对误差小于10–5，则得满分。否则不得分。  对于本题，每问的分数各占50%。如果你的输出任何一问的格式或结果不正确，则不得分；否则如果其中的一问正确，则得到该测试点50%的分数；如果两问都正确，得到该测试点100%的分数。


---

---
title: "Added Sequence"
layout: "post"
diff: 省选/NOI-
pid: P4756
tag: ['O2优化', '前缀和', '凸包', '洛谷月赛']
---
# Added Sequence
## 题目描述

小$L$发明了一种新的数据结构，并将其命名为$L$数组。$L$数组的作用是可以在$O(1)$时间内将整个数组加上或减去一个数。现在给你一个长度为$N$的数组$a$，他想用$L$数组来挑战你的计算能力。

定义$f(i,j)=|\sum_{p=i}^{j} a_p|$其中$|x|$表示$x$的绝对值。

定义一个数组的美丽度为$\max_{1 \le i \le j \le N} f(i,j)$，每当他将整个数组加上$x$ ，请你回答此时的美丽度。

注意，你的算法必须为在线的。
## 输入格式

第一行输入两个整数$N,M$，分别表示数组长度和询问数量。

第二行输入$N$个整数，表示起始的数组$a$。

接下来$M$行，每行一个整数$x_i$，设前面一次回答的答案为$pre$，那么表示第$i$次询问时在起始数组的基础上整个数组加上$[(x_i+pre)\%(4n+1)-2n]$。其中$\%$表示求余运算，第一次回答时$pre=0$。
## 输出格式

输出$M$行，第$i$行为在起始数组的基础上整个数组加上$x_i$时的美丽度。
## 样例

### 样例输入 #1
```
4 4
4 5 6 7
1
15
0
12
```
### 样例输出 #1
```
6
6
14
26

```
## 提示

四次加上的数字分别为-7，-4，-2，1。

$1 \le N,M \le 200000$

$|a_i| \le 200000$

$0 \le x_i \le 800000$


---

---
title: "忘情"
layout: "post"
diff: 省选/NOI-
pid: P4983
tag: ['斜率优化', '凸完全单调性（wqs 二分）', '凸包']
---
# 忘情
## 题目背景

 “为什么要离开我！”

 “因为你没玩儿转！”

 “我玩儿转了！”

 “那好，你现在就给我维护这么一个式子！”

 “为什么要出这么毒瘤的东西。”

 “为了恶心你。”

 “......”

$…………………………….$

## 题目描述

你的 $npy$ 为了恶心你，特地请了四位大神和一个辣鸡！

 $\rm hdxrie$ 说：“我们得求和。”于是有了 $\sum\limits_{i=1}^{n}x_i $ 。

 $\rm Imagine$ 说：“我们得有平均数。”于是有了 $\bar x $ 。

 $\rm TimeTraveller$ 说：“我们得有加减乘除。”于是有了一些恶心的组合。

 $\rm Althen·Way·Satan$ 说：“我们还得有平方。”于是我们将它平方。

最垃圾的 $\rm ZredXNy$ 说：“那我帮你们整合一下。”

于是，我们得到了这么一个式子 $:$

$$\frac{\left((\sum\limits_{i=1}^{n}x_i×\bar x)+\bar x\right)^2}{\bar x^2}$$


我们定义一段序列的值为这个，其中  $n$为此序列的元素个数。

我们给定一段长度为 $n$ 的序列,现在要求将它分成 $m$ 段，要求每一段的值的总和最小，求出这个最小值。

## 输入格式

第一行两个正整数，分别为 $n$，$m$，定义见题面。

接下来一行为 $n$ 个正整数，依次给出这个序列的每个元素的值 $x_i$ 。
## 输出格式

一个整数，求出这个最小值。
## 样例

### 样例输入 #1
```
3 2
1 2 3

```
### 样例输出 #1
```
32
```
### 样例输入 #2
```
10 3
1 2 3 4 5 6 7 8 9 10

```
### 样例输出 #2
```
1140
```
## 提示

- 对于 $30 \%$ 的数据，$m≤n≤500$；

- 另有 $20 \%$ 的数据，保证 $m=2$；

- 对于 $100 \%$ 的数据，$m≤n≤100000$，$1≤x_i≤1000$。



---

---
title: "[USACO18DEC] Balance Beam P"
layout: "post"
diff: 省选/NOI-
pid: P5155
tag: ['数学', '2018', 'USACO', '期望', '凸包']
---
# [USACO18DEC] Balance Beam P
## 题目描述

Bessie为了存钱给她的牛棚新建一间隔间，开始在当地的马戏团里表演，通过在平衡木上小心地来回走动来展示她卓越的平衡能力。

Bessie能够通过表演赚到的钱取决于她最终成功跳下平衡木的位置。平衡木上从左向右的位置记为 $ 0,1,\ldots,N+1 $ 。如果Bessie到达了位置 $ 0 $ 或是 $ N+1 $ ，她就会从平衡木的一端掉下去，遗憾地得不到报酬。

如果Bessie处在一个给定的位置 $ k $ ，她可以进行下面两项中的任意一项：

1. 投掷一枚硬币。如果背面朝上，她前往位置 $ k-1 $ ，如果正面朝上，她前往位置 $ k+1 $ （也就是说，每种可能性 $ 1/2 $ 的概率）。

2. 跳下平衡木，获得 $ f(k) $ 的报酬（ $ 0 \leq f(k) \leq 10^9 $ ）。

Bessie意识到她并不能保证结果能够得到某一特定数量的报酬，这是由于她的移动是由随机的掷硬币结果控制。然而，基于她的起始位置，她想要求出当她进行一系列最优的决定之后，她能够得到的期望报酬（“最优”指的是这些决定能够带来最高可能的期望报酬）。

例如，如果她的策略能够使她以 $ 1/2 $ 的概率获得 $ 10 $ 的报酬，$ 1/4 $ 的概率获得 $ 8 $ 的报酬，$ 1/4 $ 的概率获得 $ 0 $ 的报酬，那么她的期望报酬为加权平均值 $ 10 \times (1/2)+8 \times (1/4)+0 \times (1/4)=7 $ 。
## 输入格式

输入的第一行包含 $ N $ （ $ 2 \leq N \leq 10^5 $ ）。以下 $ N $ 行包含 $ f(1) \ldots f(N) $ 。
## 输出格式

输出 $ N $ 行。第 $ i $ 行输出 $ 10^5 $ 乘以Bessie从位置 $ i $ 开始使用最优策略能够获得的报酬的期望值，向下取整。
## 样例

### 样例输入 #1
```
2
1
3
```
### 样例输出 #1
```
150000
300000

```


---

---
title: "[清华集训 2014] 文学"
layout: "post"
diff: 省选/NOI-
pid: P5928
tag: ['计算几何', '2015', '集训队互测', '凸包', '半平面交']
---
# [清华集训 2014] 文学
## 题目描述

巨酱和主席是一对好朋友。他们都很喜欢读书，经常一起阅读相关领域书籍，进行系统的学习。一天主席列出了一份列表，里面共 $p$ 本书，其中不乏《约翰克里斯多夫》，《名人传》等名著。作为一名在文学上有很高修养的知名青年，巨酱打算用尽量少的时间把这份列表中的所有书籍都读完。

作为一名文化人，巨酱阅读书籍的方式也与一般人不同。他使用一种叫做“批量阅读”的阅读方式。首先他根据自己的喜好，对每本书给出了个参数 $x,y$，其中 $i$ 本书的两个参数为 $x_i,y_i$。当然，由于巨酱独特的口味，可能有两本不同的书，它们的 $x,y$ 参数均相同。而每次阅读的时候，他会设置三个系数 $a, b, c$，所有满足 $a \times x+b \times y \leq c$ 的书籍都可以通过这次“批量阅读”读完，这次批量阅读总共需要 $w$ 的时间。
现在，巨酱有 $n$ 种 “批量阅读”的方案，第 $i$ 种“批量阅读”三个参数为 $a_i,b_i,c_i$，需要的时间为 $w_i$。现在巨酱打算从这 $n$ 种“批量阅读”中选出若干，使得巨酱可以用尽量少的时间读完所有的书。现在我们想知道，巨酱最少用多少时间？
## 输入格式

第一行两个正整数 $n,p$，分别表示“批量阅读”的方案数以及书的数量。

接下来 $n$ 行，每行四个整数，其中第 $i$ 行包含四个整数 $a_i,b_i,c_i,w_i$，表示第 $i$ 种“批量阅读”的方案。

接下来 $p$ 行，每行两个整数，其中第 $i$ 行包含两个整数 $x_i,y_i$，表示第 $i$ 本书的参数。
## 输出格式

一行一个整数，表示最少需要的时间。若无论如何也无法读完全部书籍，则输出 $−1$。
## 样例

### 样例输入 #1
```
4 3
-1 0 0 10
-1 -1 -1 2
-1 1 -1 2
-1 -2 -1 1
0 2
0 -2
1 0
```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的测试数据，$1 \leq n,p \leq 100，−10^6 \leq a_i,b_i,c_i,x_i,y_i \leq 10^6， 0 \lt w_i \leq 10^6$，且保证对于任何一种“批量阅读”方案，其 $a_i$ 与 $b_i$ 不会同时为 $0$。且不存在 $i, j$（$i$ 不等于 $j$）使得 $a_i \times b_j=a_j \times b_i$。


---

---
title: "[CEOI 2008] Fence"
layout: "post"
diff: 省选/NOI-
pid: P5977
tag: ['动态规划 DP', '计算几何', '2008', 'CEOI（中欧）', '最短路', '凸包']
---
# [CEOI 2008] Fence
## 题目描述

在一个大小为 $1000\times 1000$ 的区域中，有 $n$ 个固定点, $m$ 棵树 。

现在你要建一个围栏来保护树，建它的费用为你选用的固定点的个数 $\times 20$ +你没有圈进围栏的树 $\times 111$。

现在希望这个值越小越好，求最小值。
## 输入格式

第一行给出 $n,m$。

接下来的 $n$ 行，给出固定的坐标。

接下来的 $m$ 行，给出树的坐标。
## 输出格式

输出最小费用。

## 样例

### 样例输入 #1
```
4 3
800 300
200 200
200 700
600 700
400 300
600 500
800 900
```
### 样例输出 #1
```
171
```
## 提示

对于 $100\%$ 的数据，$3\le N,M\le 100$。

----

## 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/7vebu0t2.png)


---

---
title: "[USACO20JAN] Falling Portals P"
layout: "post"
diff: 省选/NOI-
pid: P6010
tag: ['贪心', '2020', '倍增', '二分', 'USACO', '凸包']
---
# [USACO20JAN] Falling Portals P
## 题目描述

有 $N$（$2 \leq N \leq 2 \times 10^5$）个世界，每个世界有一个传送门。初始时，世界 $i$（对于 $1 \leq i \leq N$）位于 $x$ 坐标 $i$，$y$ 坐标 $A_i$（$1 \leq A_i \leq 10^9$）。每个世界里还有一头奶牛。在时刻 $0$，所有的 $y$ 坐标各不相同，然后这些世界开始坠落：世界 $i$ 沿着 $y$ 轴负方向以 $i$ 单位每秒的速度移动。

在任意时刻，如果两个世界在某一时刻 $y$ 坐标相同（可能是非整数时刻），传送门之间就会“同步”，使得其中一个世界的奶牛可以选择瞬间传送到另一个世界。

对于每一个 $i$，在世界 $i$ 的奶牛想要去往世界 $Q_i$（$Q_i \neq i$）。帮助每头奶牛求出如果她以最优方案移动需要多少时间。

每个询问的输出是一个分数 $a/b$，其中 $a$ 和 $b$ 为互质的正整数，或者 $-1$，如果不可能到达。
## 输入格式

输入的第一行包含一个整数 $N$。

下一行包含 $N$ 个空格分隔的整数 $A_1,A_2,\ldots,A_N$。

下一行包含 $N$ 个空格分隔的整数 $Q_1,Q_2,\ldots,Q_N$。
## 输出格式

输出 $N$ 行，第 $i$ 行包含奶牛 $i$ 的旅程的时间。
## 样例

### 样例输入 #1
```
4
3 5 10 2
3 3 2 1
```
### 样例输出 #1
```
7/2
7/2
5/1
-1
```
## 提示

### 样例解释

考虑原先在世界 $2$ 的奶牛的答案。在时刻 $2$ 世界 $1$ 和世界 $2$ 同步，所以奶牛可以前往世界 $1$。在时刻 $\frac{7}{2}$ 世界 $1$ 和世界 $3$ 同步，所以奶牛可以前往世界 $3$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 100$。
- 测试点 $4 \sim 5$ 满足 $N \leq 2000$。
- 测试点 $6 \sim 14$ 没有额外限制。


---

---
title: "[SDOI2012] 最近最远点对"
layout: "post"
diff: 省选/NOI-
pid: P6247
tag: ['2012', '各省省选', '山东', 'Special Judge', '分治', '凸包', 'K-D Tree']
---
# [SDOI2012] 最近最远点对
## 题目描述

给定平面直角坐标系上的 $n$ 个点，分别求出距离最近的两个点的距离和距离最远的两个点的距离。注意，距离为直线距离。
## 输入格式

第一行一个整数，$n$。
接下来 $n$ 行每行两个非负浮点数，$x_i$,$y_i$，表示第 $i$ 个点的 X 坐标与 Y 坐标。
## 输出格式

总共一行，两个浮点数，为最短距离与最长距离。误差不超过 $0.01$ 视为正确。
## 样例

### 样例输入 #1
```
4
0.0 0.0
0.0 1.0
1.0 0.0
1.0 1.0
```
### 样例输出 #1
```
1.00 1.41
```
## 提示

- 对于 $30\%$ 的数据，$n\leq 2000$；
- 对于 $70\%$ 的数据，$n\leq 20000$；
- 对于 $100\%$ 的数据，$0 \lt n\leq 10^5$，输入数据中所有数均为不超过 $10^9$ 的非负数。


---

---
title: "[NWRRC 2017] Joker"
layout: "post"
diff: 省选/NOI-
pid: P7028
tag: ['2017', '分块', '凸包', 'ICPC']
---
# [NWRRC 2017] Joker
## 题目描述



Joker prepares a new card trick with a strong mathematical background. You are asked to help Joker with calculations.

There is a row of $n$ cards with non-zero numbers $a_{i}$ written on them. Let's call the sum of all positive numbers $P$ and the sum of all negative numbers $N$ . Every card $i$ has a weight $w_{i} = a_{i}/P$ if $a_{i} > 0$ and $a_{i}/|N|$ otherwise.

Let's denote $s_{i} = ( \sum_{j=1}^{j \le i}{w_j})$. Joker needs to know positive $i$ with the largest $s_{i}.$ If there is more than one such $i$ , he is interested in the smallest one.

But static tricks are boring, so Joker wants to change numbers on some cards, and after each change he needs to known where is the largest $s_{i}$ is.


## 输入格式



The first line of the input contains two integers $n$ and $m$ -- the number of cards and the number of changes $(1 \le n , m \le 50 000)$ .

The second line consists of $n$ integers $a_{i}$ -- numbers written on cards at the beginning $(−10^{9} \le a_{i} \le 10^{9}; a_{i} ≠ 0)$ .

The following $m$ lines contain two integers each: $p_{i}$ and $v_{i},$ that means value of card at position $p_{i}$ is changed to $v_{i} (1 \le p_{i} \le n$ ; $−10^{9} \le v_{i} \le 10^{9}; v_{i} ≠ 0)$ .

It is guaranteed that at each moment there is at least one card with positive number and at least one card with negative number. The sum of all positive cards will never exceed $10^{9}$ and the sum of all negative cards will never exceed $−10^{9}.$


## 输出格式



You should output $m+1$ integers. The first integer is the position of the largest $s_{i}$ for the initial numbers. Next $m$ numbers are positions of the largest $s_{i}$ after each change.


## 样例

### 样例输入 #1
```
4 7
1 -5 3 -5
4 -1
2 -1
3 10
4 10
1 -1
2 1
3 -1

```
### 样例输出 #1
```
3
1
3
3
1
4
4
4

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

有一个长度为 $n$ 的数列，第 $i$ 个元素的值为 $a_i$，定义 $P$ 为数列中所有正整数的和，$N$ 为所有负整数的和。定义一个元素的重要值 $w_i=\begin{cases}\dfrac{a_i}{P}&a_i>0\\\dfrac{a_i}{|N|}&\text{otherwise}\end{cases}$，并定义 $s_i$ 为前 $i$ 个元素的重要值之和，即 $\sum\limits_{j=1}^iw_j$。

请先求出当前数列中使 $s_i$ 最大的 $i$。然后有 $m$ 次操作，每次操作将某个元素改成一个给定的值，请在每次操作后求出当数列中使 $s_i$ 最大的 $i$。

如果有多个满足要求的 $i$，则答案取最小的。

Translated by Eason_AC  
2020.11.15


---

---
title: "雨水收集系统（2021 CoE-I E）"
layout: "post"
diff: 省选/NOI-
pid: P7397
tag: ['计算几何', '2021', 'Special Judge', '凸包', '半平面交']
---
# 雨水收集系统（2021 CoE-I E）
## 题目背景

Rain 市的环保部门为部分建筑的顶层安装了雨水收集装置，使得能够将雨水进行循环利用。雨水收集系统通过每栋建筑的顶层地面来收集雨水，利用特殊的管道将雨水集中引流到一个蓄水池中以待后续使用。环保部门计划根据降水量来估计蓄水池的容量大小以便进行设计制造。
## 题目描述

为了简化问题的处理，将每栋建筑的顶层视为一个边与坐标轴平行的矩形，使用矩形的一条对角线顶点坐标来表示该矩形。每次降雨时，降雨云沿着特定的方向以一定的速度做匀速运动，降雨云所经过的区域均会有雨水降落。将降雨云抽象为一个凸多边形，给定初始时降雨云的位置以及移动方向和速率，确定在某段时间内雨水收集系统能够接受降雨的面积大小。
## 输入格式

**输入包含多组测试数据**。

输入的第一行为一个整数 $T$，表示测试数据的组数，接下来共 $T$ 组数据，相邻两组测试数据之间有一个空行。每组测试数据的第一行为一个整数 $n$，表示建筑的数量。接下来 $n$ 行，每行四个整数，表示第 $i$ 栋建筑顶层所对应矩形的对角线顶点坐标。接下来一行是一个整数 $m$，表示降雨云对应凸多边形的顶点数目，接下来是 $m$ 个表示该凸多边形的顶点坐标（**不保证有序，即顶点可能不是按照顺时针或逆时针顺序给出，但给定的坐标点唯一地确定了表示降雨云的凸多边形**）：（$x_1$，$y_1$），（$x_2$，$y_2$），...，（$x_m$，$y_m$）。再接下来是起点 $s$（$x_s$，$y_s$）和终点 $e$（$x_e$，$y_e$）的坐标值，表示降雨云沿着从起点 $s$ 到终点 $e$ 的直线方向做平移运动。后续是一个整数 $v$，表示降雨云沿着直线方向的移动速率为 $v$ 单位距离/分钟，最后一行表示降雨的起始时间 $hh_{start}$ 时 $mm_{start}$ 分和结束时间  $hh_{end}$ 时 $mm_{end}$ 分，以 $24$ 小时计时法表示。
## 输出格式

输出在指定时间内能够接受降雨的建筑顶层面积之和，精确到小数点后一位。如果你的输出和参考输出绝对误差在$10^{-1}$之内，均认为正确。
## 样例

### 样例输入 #1
```
2

2
0 0 10 10
20 20 30 10
4
-10 8 -5 8 -5 13 -10 13
15 0 25 0
1
15:30 16:05

2
0 0 10 10
20 20 30 10
4
-10 8 -5 8 -5 13 -10 13
-5 8 19 1
1
15:30 16:30
```
### 样例输出 #1
```
50.0
60.5
```
## 提示

#### 样例说明

![](https://cdn.luogu.com.cn/upload/image_hosting/jf0ig9zb.png)

第一组测试数据，此组测试数据一共有 $2$ 栋建筑 $\operatorname{B_1}$ 和 $\operatorname{B_2}$，降雨云 $\operatorname{C}$ 为一个正方形（正方形的左下角位于坐标点（$-10$，$8$），边长为 $5$），降雨云沿着从起点（$15$，$0$）到终点（$25$，$0$）的方向匀速移动，移动速率为 $1$ 单位距离/分钟，降雨起始时间为 $15$ 时 $30$ 分，结束时间为 $16$ 时 $05$ 分，降雨时间为 $35$ 分钟，降雨云沿着箭头所示方向移动了 $35$ 单位距离。如上图所示，能够接受降雨的面积为阴影区域的面积，易知面积为 $50.0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/two4uh3q.png)
第二组测试数据，降雨云的移动方向不同，从起点（$-5$，$8$）到终点（$19$，$1$）的方向匀速移动，降雨时间为 $60$ 分钟，沿着箭头所示方向的移动距离为 $60$ 单位距离，其他条件相同，能够接受降雨的面积为上图中的阴影区域，其面积为 $60.5$。注意，第二组测试数据的示意图中，为了示意的方便，所绘制的降雨云“最终位置”并不是其实际的最终位置。

------------

#### 数据范围与约定

对于 $100\%$ 的数据，$1 \leq T \leq 10^3$，$1 \leq n \leq 50$，$3 \leq m \leq 100$，$0 \lt v \leq 100$。所有坐标值均为整数，位于闭区间 $[-10^5,10^5]$。

输入数据保证表示建筑顶层的矩形不会发生重叠。降雨的结束时间一定晚于起始时间。表示降雨云移动方向的起点 $s$ 和终点 $e$ 不同。


---

---
title: "[WFOI - 01] 循环节（circle）"
layout: "post"
diff: 省选/NOI-
pid: P8000
tag: ['计算几何', '洛谷原创', 'Special Judge', 'O2优化', '凸包', '旋转卡壳', '洛谷月赛']
---
# [WFOI - 01] 循环节（circle）
## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/v7gqdh44)。

出题人注：これは非常に嫌な質問なので、あまり時間をかけたくない場合は、この質問を見る前に他の質問を終えることをお勧めします。
## 题目描述

给你一个坐标系上的点集 $a$，你需要找出一个子点集 $b$ 和一个向量 $x$，使得 $\exist\ z\in N^+,\{b\cup b+x\cup b+2x\cup\dots\cup b+zx=a\}$。

现在想让你求出任意一对 $b_0,x_0,z_0$，其中 $z_0$ 为所有满足条件的三元组中 $z$ 最大的，$b_0$ 中任意三点不共线，任意四点不构成梯形或平行四边形且 $b_0\cap b_0+x_0=\varnothing,b_0\cap b_0+2x_0=\varnothing,\dots,b_0\cap b+yx_0=\varnothing|{y\to+\infty}$。

其中 $b+x$ 的意思是，$b$ 中的所有点都平移向量 $x$ 后组成的点集。
## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，每行 $2$ 个整数，表示一个点。
## 输出格式

输出共 $4$ 行：

第一行一个整数 $|b|$。

第二行 $|b|$ 个整数 $b_1,b_2,\dots,b_{|b|}$（对应编号）。

第三行两个整数 $x$。

第四行一个整数 $z$。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 0
1 1
```
### 样例输出 #1
```
2
1 3
0 1
1
```
### 样例输入 #2
```
3
0 0
0 1
1 0
```
### 样例输出 #2
```
3
1 2 3
0 0
0
```
## 提示

由于本题有样例解释也只是照着念一遍，并且相信既然您都做到这一题来了应该能读懂题目含义，所以本题不提供样例解释（~~其实是出题人懒~~）。

**本题采用 Subtask 捆绑测试。**
Subtask 编号 | 数据规模与约定
:-: | :-:
**Subtask #0($\text{20 pts}$)** | $1\le n\le10$；$-10\le x_i,y_i \le 10$
**Subtask #1($\text{20 pts}$)** | $1\le n\le10^3$
**Subtask #2($\text{30 pts}$)** | $z>1$
**Subtask #3($\text{30 pts}$)** | 无特殊限制

对于 $100\%$ 的数据，$1\le n\le10^5$，点的坐标范围 $\in\left(-10^9,10^9\right)$，数据保证有解。


---

---
title: "[USACO22JAN] Multiple Choice Test P"
layout: "post"
diff: 省选/NOI-
pid: P8101
tag: ['USACO', '2022', '凸包', '极角排序']
---
# [USACO22JAN] Multiple Choice Test P
## 题目描述

奶牛们正在参加一个选择题测试。在通常的测试中，对每个问题你的选项会被单独评分然后累加，而在此测试中，你的选项在累加之后再评分。

具体地说，你被给定二维平面上的 $N$（$2 \le N \le 10^5$）组整数向量，其中每个向量用一个有序对 $(x,y)$ 表示。从每组中选择一个向量，使向量的总和尽可能远离原点。

输入保证向量的总数不超过 $2 \times 10^5$。每组至少包含 $2$ 个向量，并且一组内所有向量各不相同。输入同时保证每个 $x$ 和 $y$ 坐标的绝对值不超过 $\dfrac{10^9}{N}$。
## 输入格式

输入的第一行包含 $N$，为向量的组数。

每一组的第一行包含 $G$，为组中的向量数。以下 $G$ 行包含组中的向量。相邻组之间用空行分隔。
## 输出格式

输出最大可能的欧几里得距离的平方。
## 样例

### 样例输入 #1
```
3

2
-2 0
1 0

2
0 -2
0 1

3
-5 -5
5 1
10 10
```
### 样例输出 #1
```
242
```
## 提示

【样例解释】

最优方案是从第一组选择 $(1,0)$，从第二组中选择 $(0,1)$，从第三组选择 $(10,10)$。这些向量之和等于 $(11,11)$，与原点的距离平方等于 $11^2+11^2=242$。

【数据范围】

- 测试点 1-5 中，向量的总数不超过 $10^3$。
- 测试点 6-9 中，每一组恰好包含 $2$ 个向量。
- 测试点 10-17 没有额外限制。

供题：Benjamin Qi


---

---
title: "[WFOI - 02] I wanna escape the shadow（阴影）"
layout: "post"
diff: 省选/NOI-
pid: P8222
tag: ['洛谷原创', 'O2优化', '凸包', '旋转卡壳', '其它技巧', '洛谷月赛', '双指针 two-pointer']
---
# [WFOI - 02] I wanna escape the shadow（阴影）
## 题目背景

> Define adventure with death
>
> You are the shadow to my life

背景突然阴沉了下来，但是 kid 清楚，这是最黑暗的时刻，也是黎明之前...
## 题目描述

现在 kid 身处一个**圆心为 $(0,0)$，半径为 $r$ 的**圆中，并且学会了一种新的操作 `mklig(X,Y,Z)` 来消除黑暗，具体如下：

$X,Y,Z$ 是三个不同的点，作射线 $XY,ZY$，设两条射线与圆周交于 $d_1,d_2$，那么将 弧 $d_1d_2$，线段 $Yd_1,Yd_2$ 围成的区域照亮。

现在圆内有一些点，记 $S_{光}$ 是圆的半径为 $r$ 的时候被照亮的总面积，现在 kid 想知道在使 $\lim\limits_{r \to \infty} \dfrac{S_{光}}{\pi r^2}$ （可以理解为 r 无穷大时）最大时，最少需要多少次 `mklig` 操作。你只需要给出答案，剩下的操作就交给 €€£ 吧！

数据保证不存在三点共线。
## 输入格式

**本题有多组数据**

第一行一个整数 $T$，表示数据组数；

对于每组数据：

第一行一个正整数 $n$；

接下来 $n$ 行，每行两个整数，分别表示一个点的横纵坐标。
## 输出格式

共 $T$ 行，每行一个整数，表示答案。
## 样例

### 样例输入 #1
```
1
3
0 0
0 2
-1 1
```
### 样例输出 #1
```
3
```
## 提示

- ####  样例解释

![](https://s1.ax1x.com/2022/03/14/bXTM01.png)

**本题采用 Subtask 捆绑测试。**

- $\texttt{Subtask \#0 (30pts)}$：$n = 10^3$ 且数据随机；
- $\texttt{Subtask \#1 (30pts)}$：$n \le 5$ ；
- $\texttt{Subtask \#2 (40pts)}$：$n \le 10^6$；

对于每个测试点，保证 $T \le 5 ，\sum n\le 10^6$，点的坐标的绝对值不超过 $10^9$。


---

---
title: "[USACO23JAN] Mana Collection P"
layout: "post"
diff: 省选/NOI-
pid: P9020
tag: ['USACO', '2023', '凸包', '李超线段树', '状压 DP']
---
# [USACO23JAN] Mana Collection P
## 题目描述

**Note: The time limit for this problem is 5s, 2.5 times the default. The memory limit for this problem is 512MB, twice the default.**

Bessie has recently taken an interest in magic and needs to collect mana for a very important spell. Bessie has $N(1 \le N \le 18)$ mana pools, the ith of which accumulates $m_i$ mana per second $(1 \le m_i \le 10^8)$. The pools are linked by a collection of $M (0 \le M \le N(N−1))$ directed edges $(a_i,b_i,t_i)$, meaning that she can travel from $a_i$ to $b_i$ in $t_i$ seconds $(1 \le a_i,b_i \le N, a_i \neq b_i, 1 \le t_i \le 10^9)$. Whenever Bessie is present at a pool, she can collect all the mana stored at that location, emptying it. At time $0$, all mana pools are empty, and Bessie can select any pool to start at.

Answer $Q(1 \le Q \le 2 \cdot 10^5)$ queries, each specified by two integers $s$ and $e (1 \le s \le 10^9, 1 \le e \le N)$. For each query, determine the maximum amount of mana Bessie can collect in s seconds if she must be at mana pool $e$ at the end of the $s$-th second. 
## 输入格式

First line contains $N$ and $M$.

Next line contains $m_1,m2, \cdots ,m_N$.

Next $M$ lines contain $a_i,b_i,t_i$. No ordered pair $(a_i,b_i)$ appears more than once in the input.

Next line contains $Q$.

Next $Q$ lines contain two integers $s$ and $e$. 
## 输出格式

$Q$ lines, one for each query. 
## 样例

### 样例输入 #1
```
2 1
1 10
1 2 10
4
5 1
5 2
100 1
100 2
```
### 样例输出 #1
```
5
50
100
1090
```
### 样例输入 #2
```
4 8
50000000 100000000 20000000 70000000
1 2 20
2 1 50
2 3 90
1 3 40
3 1 10
4 1 25
1 4 5
4 3 70
3
8 3
1000000000 1
500000 4
```
### 样例输出 #2
```
160000000
239999988050000000
119992550000000
```
## 提示

### Explanation for Sample 1

First query: Bessie takes $5$ mana from pool $1$ after $5$ seconds.

Second query: Bessie takes $50$ mana from pool $2$ after $5$ seconds.

Third query: Bessie takes $100$ mana from pool $1$ after $100$ seconds.

Fourth query: Bessie takes $90$ mana from pool $1$ after $90$ seconds and $1000$ mana from pool $2$ after $100$ seconds. 

### Explanation for Sample 2

An example where Bessie is able to collect much larger amounts of mana. 

### Scoring

 - Inputs $3-4$: $N \le 10$,$Q \le 100$
 - Inputs $5-9$: $N \le 10$
 - Inputs $10-14$: $Q \le 100$
 - Inputs $15-17$: $N=16$
 - Inputs $18-20$: $N=17$
 - Inputs $21-24$: No additional constraints.
## 题目翻译

## 题目背景

**注意：这个问题的时间限制是5秒，是默认的2.5倍。这个问题的内存限制是512MB，是默认值的两倍。**

## 题目描述

贝西需要为一个非常重要的法术收集法力。贝西有 $N$  $(1\le N\le 18)$ 个法力池，其中第 $i$ 个法力池每秒可积累 $m_i$ 法力 $(1\le m_i\le 10^8)$ 。这些池子由 $M$ $(0\le M\le N \cdot (N-1))$  条有向边 $(a_i,b_i,t_i)$ 连接，这意味着她可以在 $t_i$ 秒内从 $a_i$ 移动到 $b_i$ $(1\le a_i, b_i\le N$, $a_i\neq b_i$, $1\le t_i\le 10^9)$ 。每当贝西出现在一个池子里，她就可以收集储存在那个地方的所有法力，把它清空。在 $0$ 的时候，所有的法力池都是空的，贝西可以选择任何一个池子来开始收集。

回答 $Q$ $(1\le Q\le 2\cdot 10^5)$ 个查询，每个查询由两个整数 $s$ 和 $e$ 指定 $(1\le s\le 10^9$，$1\le e\le N)$ 。对于每个查询，如果贝西在第 $s$ 秒结束时必须在法力池 $e$ 处，请确定她在 $s$ 秒内能收集的最大法力值。

## 输入格式

第一行包含 $N$ 和 $M$ 。

下一行包含 $m_1,m_2,\dots, m_N$ 。

接下来的 $M$ 行每行包含 $a_i,b_i,t_i$ 。在输入中没有一对有序的 $(a_i,b_i)$ 出现超过一次。

下一行包含 $Q$ 。

接下来的 $Q$ 行每行包含两个整数 $s$ 和 $e$ 。

## 输出格式

输出 $Q$ 行，每个查询所对应的答案。

## 提示

对于第一个样例：

第一次询问。贝西在 $5$ 秒后从水池 $1$ 中取出 $5$ 个法力值。

第二次查询。 $5$ 秒后，贝西从水池 $2$ 中获取 $50$ 点法力。

第三次查询。 $100$ 秒后，贝西从水池 $1$ 中获取 $100$ 法力值。

第四次查询。 $90$ 秒后贝西从水池 $1$ 中获得 $90$ 法力， $100$ 秒后从水池 $2$ 中获得 $1000$ 法力。

测试点 $3-4$: $N\le 10, Q\le 100$ 。

测试点 $5-9$: $N\le 10$ 。

测试点 $10-14$: $Q\le 100$ 。

测试点 $15-17$: $N = 16$ 。

测试点 $18-20$: $N = 17$ 。

测试点 $21-24$：没有其他约束条件 。


---

