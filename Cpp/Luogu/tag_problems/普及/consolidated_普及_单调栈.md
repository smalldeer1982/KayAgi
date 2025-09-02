---
title: "求数列所有后缀最大值的位置"
layout: "post"
diff: 普及/提高-
pid: B3666
tag: ['O2优化', '单调栈']
---
# 求数列所有后缀最大值的位置
## 题目描述

给定一个数列 $a$，初始为空。有 $n$ 次操作，每次在 $a$ 的末尾添加一个正整数 $x$。

每次操作结束后，请你找到当前 $a$ 所有的后缀最大值的下标（下标从 1 开始）。一个下标 $i$ 是当前 $a$ 的后缀最大值下标当且仅当：对于所有的 $i < j \leq |a|$，都有 $a_i > a_j$，其中 $|a|$ 表示当前 $a$ 的元素个数。

为了避免输出过大，请你**每次操作结束后都输出一个整数**，表示**当前数列**所有后缀最大值的下标的按位异或和。
## 输入格式

第一行是一个整数，表示操作次数 $n$。  
第二行有 $n$ 个整数，依次表示 $n$ 次操作所添加的整数 $x_i$。
## 输出格式

每次操作后请输出一行一个整数，表示当前数列所有后缀最大值下标的按位异或和。
## 样例

### 样例输入 #1
```
5
2 1 3 5 4
```
### 样例输出 #1
```
1
3
3
4
1
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^6$，$1 \leq x_i \lt 2^{64}$。


---

---
title: "[蓝桥杯 2023 国 C] 最大区间"
layout: "post"
diff: 普及/提高-
pid: P12241
tag: ['2023', '蓝桥杯国赛', '单调栈']
---
# [蓝桥杯 2023 国 C] 最大区间
## 题目描述

给定一个长度为 $n$ 的序列 $A_i$，求 $L, R$ 使 $(R - L + 1) \cdot \min(A_L, A_{L+1}, \ldots, A_R)$ 尽可能大，其中 $\min$ 表示最小值。

你只需要输出最大的值即可，不需要输出具体的 $L, R$。
## 输入格式

输入的第一行包含一个整数 $n$。

第二行包含 $n$ 个整数，分别表示 $A_1, A_2, \ldots, A_n$，相邻两个整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5
1 1 3 3 1
```
### 样例输出 #1
```
6
```
## 提示

### 评测用例规模与约定

对于 $40\%$ 的评测用例，$1 \leq n \leq 5000$，$1 \leq A_i \leq 5000$；

对于所有评测用例，$1 \leq n \leq 3 \times 10^5$，$1 \leq A_i \leq 10^9$。


---

---
title: "[SWERC 2023] Nicest view"
layout: "post"
diff: 普及/提高-
pid: P13796
tag: ['2023', 'ICPC', '单调栈']
---
# [SWERC 2023] Nicest view
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/93613cfd23ca0223b6f9aa573bf5381a7646cd95.png)

:::

Paris is so crowded with tourists during the Olympic games! You want to escape the city and go on a hike on a linear trail path, going from left to right. Every kilometre on that trail, including at start and end, is a milestone, on which is written the stone's altitude. The slope between two consecutive stones is constant, and no two stones have the same altitude.


Planning to come back with your friends, you try to identify the point of the hike at which you had the nicest view. The beauty of a point of view is defined as the distance (measured in kilometres) between your position and the leftmost position that you can see on your hike and that is at the same altitude as you are. If such a previous position fails to exist, it means that you can see the city and its smog, and the beauty of that view is zero.


You have listed the altitudes of the milestones. What is the maximal beauty on your hike?
## 输入格式

The input consists of two lines. The first line contains a single integer $N$, which is the number of milestones on the trail path. The second line contains $N$ space-separated integers $H_1, H_2, \dots, H_N$; each integer $H_k$ is the altitude (measured in metres) of the $k^\text{th}$ milestone on the path.


**Limits**

- $1 \leq N \leq 100~000$;
- $0 \leq H_k \leq 1~000~000$ for all $k \leq N$;
- the integers $H_k$ are pairwise distinct.

## 输出格式

The output should contain a single line, consisting of a single number $S$: the best beauty score on your hike. This number is written either as an integer or as an irreducible fraction $N/D$ for which $D \geq 2$; we recall that a fraction $N/D$ is irreducible when the greatest common divisor of $N$ and $D$ is $1$.
## 样例

### 样例输入 #1
```
7
0 5 3 1 4 8 2
```
### 样例输出 #1
```
13/4
```
### 样例输入 #2
```
5
3 5 8 7 1
```
### 样例输出 #2
```
0
```


---

---
title: "发射站"
layout: "post"
diff: 普及/提高-
pid: P1901
tag: ['NOI 导刊', '栈', '单调栈']
---
# 发射站
## 题目描述

某地有 $N$ 个能量发射站排成一行，每个发射站 $i$ 都有不相同的高度 $H_i$，并能向两边（两端的发射站只能向一边）同时发射能量值为 $V_i$ 的能量，发出的能量只被两边**最近的且比它高**的发射站接收。显然，每个发射站发来的能量有可能被 $0$ 或 $1$ 或 $2$ 个其他发射站所接受。

请计算出接收最多能量的发射站接收的能量是多少。

## 输入格式

第 $1$ 行一个整数 $N$。

第 $2$ 到 $N+1$ 行，第 $i+1$ 行有两个整数 $H_i$ 和 $V_i$，表示第 $i$ 个发射站的高度和发射的能量值。
## 输出格式

输出仅一行，表示接收最多能量的发射站接收到的能量值。答案不超过 32 位带符号整数的表示范围。

## 样例

### 样例输入 #1
```
3
4 2 
3 5 
6 10

```
### 样例输出 #1
```
7
```
## 提示

对于 $40\%$ 的数据，$1\le N\le 5000,1\le H_i\le 10^5,1\le V_i\le 10^4$。

对于 $70\%$ 的数据，$1\le N\le 10^5,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。

对于 $100\%$ 的数据，$1\le N\le 10^6,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。


---

---
title: "[USACO06NOV] Bad Hair Day S"
layout: "post"
diff: 普及/提高-
pid: P2866
tag: ['2006', 'USACO', '栈', 'ST 表', '单调栈']
---
# [USACO06NOV] Bad Hair Day S
## 题目描述


农夫约翰有 $N$ 头奶牛正在过乱头发节。

每一头牛都站在同一排面朝右，它们被从左到右依次编号为 $1, 2, \cdots, N$。编号为 $i$ 的牛身高为 $h_i$。第 $N$ 头牛在最前面，而第 $1$ 头牛在最后面。

对于第 $i$ 头牛**前面**的第 $j$ 头牛，如果 $h_i>h_{i+1}, h_i>h_{i+2}, \cdots, h_i>h_j$，那么认为第 $i$ 头牛可以看到第 $i+1$ 到第 $j$ 头牛。

定义 $C_i$ 为第 $i$ 头牛所能看到的牛的数量。请帮助农夫约翰求出 $C _ 1 + C _ 2 + \cdots + C _ N$。

## 输入格式

输入共 $N + 1$ 行。

第一行为一个整数 $N$，代表牛的个数。  
接下来 $N$ 行，每行一个整数 $a _ i$，分别代表第 $1, 2, \cdots, N$ 头牛的身高。
## 输出格式

输出共一行一个整数，代表 $C _ 1 + C _ 2 + \cdots + C _ N$。
## 样例

### 样例输入 #1
```
6
10
3
7
4
12
2
```
### 样例输出 #1
```
5
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq N \leq 8 \times 10 ^ 4$，$1 \leq h _ i \leq 10 ^ 9$。


---

---
title: "[USACO09MAR] Look Up S"
layout: "post"
diff: 普及/提高-
pid: P2947
tag: ['2009', 'USACO', '单调栈']
---
# [USACO09MAR] Look Up S
## 题目描述

Farmer John's N (1 <= N <= 100,000) cows, conveniently numbered 1..N, are once again standing in a row. Cow i has height H\_i (1 <= H\_i <= 1,000,000).

Each cow is looking to her left toward those with higher index numbers. We say that cow i 'looks up' to cow j if i < j and H\_i < H\_j. For each cow i, FJ would like to know the index of the first cow in line looked up to by cow i.

Note: about 50% of the test data will have N <= 1,000. 

约翰的 $N(1\le N\le10^5)$ 头奶牛站成一排，奶牛 $i$ 的身高是 $H_i(1\le H_i\le10^6)$。现在，每只奶牛都在向右看齐。对于奶牛 $i$，如果奶牛 $j$ 满足 $i<j$ 且 $H_i<H_j$，我们可以说奶牛 $i$ 可以仰望奶牛 $j$。 求出每只奶牛离她最近的仰望对象。

Input
## 输入格式

1. \* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains the single integer: H\_i

第 $1$ 行输入 $N$，之后每行输入一个身高 $H_i$。

## 输出格式

\* Lines 1..N: Line i contains a single integer representing the smallest index of a cow up to which cow i looks. If no such cow exists, print 0.

共 $N$ 行，按顺序每行输出一只奶牛的最近仰望对象，如果没有仰望对象，输出 $0$。

## 样例

### 样例输入 #1
```
6 
3 
2 
6 
1 
1 
2 

```
### 样例输出 #1
```
3 
3 
0 
6 
6 
0 

```
## 提示

FJ has six cows of heights 3, 2, 6, 1, 1, and 2.


Cows 1 and 2 both look up to cow 3; cows 4 and 5 both look up to cow 6; and cows 3 and 6 do not look up to any cow.

【输入说明】$6$ 头奶牛的身高分别为 3,2,6,1,1,2。

【输出说明】奶牛 #1,#2 仰望奶牛 #3，奶牛 #4,#5 仰望奶牛 #6，奶牛 #3 和 #6 没有仰望对象。

【数据规模】

对于 $20\%$ 的数据：$1\le N\le10$；

对于 $50\%$ 的数据：$1\le N\le10^3$；

对于 $100\%$ 的数据：$1\le N\le10^5,1\le H_i\le10^6$。



---

---
title: "【模板】单调栈"
layout: "post"
diff: 普及/提高-
pid: P5788
tag: ['线性数据结构', '栈', '单调栈']
---
# 【模板】单调栈
## 题目背景

模板题，无背景。  

2019.12.12 更新数据，放宽时限，现在不再卡常了。
## 题目描述

给出项数为 $n$ 的整数数列 $a_{1 \dots n}$。

定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**，即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$。若不存在，则 $f(i)=0$。

试求出 $f(1\dots n)$。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数 $a_{1\dots n}$。
## 输出格式

一行 $n$ 个整数表示 $f(1), f(2), \dots, f(n)$ 的值。  
## 样例

### 样例输入 #1
```
5
1 4 2 3 5

```
### 样例输出 #1
```
2 5 4 5 0

```
## 提示

【数据规模与约定】

对于 $30\%$ 的数据，$n\leq 100$；

对于 $60\%$ 的数据，$n\leq 5 \times 10^3$ ；

对于 $100\%$ 的数据，$1 \le n\leq 3\times 10^6$，$1\leq a_i\leq 10^9$。


---

---
title: "[USACO22JAN] Cow Frisbee S"
layout: "post"
diff: 普及/提高-
pid: P8094
tag: ['USACO', '2022', '单调栈']
---
# [USACO22JAN] Cow Frisbee S
## 题目描述

Farmer John 的 $N\ (N\le 3\times 10^5)$ 头奶牛的高度为 $1, 2, \ldots, N$。一天，奶牛以某个顺序排成一行玩飞盘；令 $h_1 \ldots h_N$ 表示此顺序下奶牛们的高度（因此 $h$ 是 $1 \ldots N$ 的一个排列）。

队伍中位于位置 $i$ 和 $j$ 的两头奶牛可以成功地来回扔飞盘当且仅当她们之间的每头奶牛的高度都低于 $\min(h_i, h_j)$。

请计算所有可以成功地来回扔飞盘的奶牛所在的位置对 $i\le j$ 之间的距离总和。位置 $i$ 和 $j$ 之间的距离为 $j-i+1$。
## 输入格式

输入的第一行包含一个整数 $N$。第二行包含 $h_1 \ldots h_N$，用空格分隔。
## 输出格式

输出可以成功地来回扔飞盘的奶牛所在的位置对 $i\le j$ 之间的距离总和。注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C 或 C++ 中的 "long long"）。
## 样例

### 样例输入 #1
```
7
4 3 1 2 5 6 7
```
### 样例输出 #1
```
24
```
## 提示

【样例解释】

这个例子中可以成功的位置对如下：

```
(1, 2), (1, 5), (2, 3), (2, 4), (2, 5), (3, 4), (4, 5), (5, 6), (6, 7)
```

【数据范围】

- 测试点 1-3 满足 $N\le 5000$。

- 测试点 4-11 没有额外限制。


---

