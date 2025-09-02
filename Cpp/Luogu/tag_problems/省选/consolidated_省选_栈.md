---
title: "[DTCPC 2024] mex,min,max"
layout: "post"
diff: 省选/NOI-
pid: P10169
tag: ['线段树', '2024', '颜色段均摊（珂朵莉树 ODT）', '洛谷月赛', '单调栈']
---
# [DTCPC 2024] mex,min,max
## 题目描述

给定序列 $\{a_n\}$ 和 $k$，求有多少子区间 $[l,r]$ 满足 $\operatorname{mex}\{a_l,a_{l+1},\dots,a_{r-1},a_r\}+\min\{a_l,a_{l+1},\dots,a_{r-1},a_r\}+k\geq \max\{a_l,a_{l+1},\dots,a_{r-1},a_r\}$。

$\operatorname{mex}$ 定义为集合内没有出现过的最小的**非负整数**。
## 输入格式

第一行两个整数 $n,k$（$1\leq n\leq 5\times 10^5,0\leq k\leq n$）。

第二行 $n$ 个非负整数，第 $i$ 个表示 $a_i$（$0\leq a_i\leq n$）。
## 输出格式

一行一个数，表示满足条件的子区间个数。
## 样例

### 样例输入 #1
```
3 0
1 0 2
```
### 样例输出 #1
```
5
```


---

---
title: "[Opoi 2024] 二十六点"
layout: "post"
diff: 省选/NOI-
pid: P10536
tag: ['线段树', '树上启发式合并', 'O2优化', '树链剖分', '单调栈']
---
# [Opoi 2024] 二十六点
## 题目背景

二十六点：

> 。 。 。 。 。 。 。 。 。 。 。 。 。
>
> 。 。 。 。 。 。 。 。 。 。 。 。 。

凑二十六点真好玩，而为了凑四道题，就有了这道权值只有 $26$ 种的凑数题。
## 题目描述


给你一棵有 $n$ 个结点的以 $1$ 为根的树 $T$，第 $i$ 个结点有一个颜色 $c_i$，${\tt a} \le c_i \le {\tt z}$，和一个值 $P_i$。

对于每一个点 $x$，**从它到它子树中每一个点**（注意顺序是从它本身到子树中的点）都有一条路径，一共有子树的大小条路径。

现在忽略掉这些路径中的第 $2$ 到第 $P_x$ 个的点，特别地，若 $P_x = 1$ 则不忽略任何点。将忽略后的路径当作一个序列，序列中每个点的权值为路径上点的 $c_i$，求**每一个点的所有序列最长不下降子序列长度的最大值**。

注: 若有路径 $j$ 上的节点数 $len_j < P_x$，则相当于忽略这条路径上除第一个点外的所有点。

## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数 $P_i$。

第三行 $n$ 个小写字母 $c_i$，**字符与字符间没有空格**。

接下来 $n - 1$ 行，描述树 $T$，每行两个整数 $u,v$，表示 $u,v$ 存在一条边。

行末可能有多余空格（慎用 `getchar()`）。
## 输出格式

输出 $n$ 行，表示每一个点的答案，按照编号从小到大输出。
## 样例

### 样例输入 #1
```
7
2 1 1 9 8 5 1
zzabcad
1 2
2 3
3 4
3 5
5 6
5 7
```
### 样例输出 #1
```
3
3
3
1
1
1
1

```
### 样例输入 #2
```
12
1 2 2 4 1 3 4 3 1 4 3 1 
baabbbbbbbaa
4 6
5 7
1 2
12 10
8 2
10 11
5 9
10 3
2 3
4 3
4 5

```
### 样例输出 #2
```
5
4
3
1
2
1
1
1
1
1
1
1
```
## 提示



### 样例一解释：

样例中树的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/6vbio7vo.png?x-oss-process=image/resize,h_450,m_lfit)

对于 $1$ 号节点：
$P_1=2$。

|  序列| 权值 | 最长不下降子序列长度 | 最长不下降子序列 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | z | 1 | z |
| 1 3 | za | 1 |  z |
| 1 3 4 |  zab | 2  | ab |
| 1 3 5  |  zac | 2 |  ac   |
| 1 3 5 6 |  zaca | 2  | ac |
| 1 3 5 7 | zacd| 3 | acd  |

长度最长的最长不降子序列：acd。

$2$ 号节点和 $1$ 号节点同理。

对于 $3$ 号节点：
$P_3=1$。

|  序列| 权值 | 最长不下降子序列长度 | 最长不下降子序列 |
| :----------: | :----------: | :----------: | :----------: |
| 3 | a | 1 | a |
| 3 4 | ab | 1 |  ab |
| 3 5  |  ac | 2  | ac |
| 3 5 6  |  aca | 2 |  ac   |
|3 5 7   |  acd | 3  |acd |

长度最长的最长不降子序列：acd。

对于 $4,5,6,7$，它的所有序列中都只有它自己一个点，所以输出 $1$。
### 数据范围

本题采用 Subtask 计分。

| Subtask | Limit | Pts |
| :-----------: | :-----------: | :-----------: |
| 0 | $n \le 100$ | 5 |
| 1 | $n \le 2000$ | 15 |
| 2 | $\forall 1 \le i \le n \quad P_i=1$ | 30 |
| 3 | Empty | 50 |

对于 $100\%$ 的数据：

$1 \le n \le 10^5$。

$\forall 1 \le i \le n$， $c_i$ 为小写字母，$1 \le P_i \le n$。

给出的树连通且合法。


---

---
title: "[CEOI 2009] Harbingers"
layout: "post"
diff: 省选/NOI-
pid: P10602
tag: ['动态规划 DP', '2009', '二分', 'O2优化', 'CEOI（中欧）', '斜率优化', '单调栈']
---
# [CEOI 2009] Harbingers
## 题目描述

给定一颗树，树中每个结点有一个邮递员，每个邮递员要沿着唯一的路径走向 capital（$1$ 号结点），每到一个城市他可以有两种选择：

1. 继续走到下个城市；
2. 让这个城市的邮递员替他出发。

每个邮递员出发需要一个准备时间 $W_i$，他们的速度是 $V_i$，表示走一公里需要多少分钟。现在要你求出每个城市的邮递员到 capital 的最少时间（不一定是他自己到 capital，可以是别人帮他）？
## 输入格式

第一行一个正整数 $N$；

接下来 $N-1$ 行，每行三个正整数 $A,B,C$，表示结点 $A$ 和 $B$ 之间有一条长度为 $C$ 的边；

再接下来 $N-1$ 行，每行 $2$ 个整数 $W_i,V_i$。
## 输出格式

输出每个城市的邮递员到 capital 的最少时间。
## 样例

### 样例输入 #1
```
5
1 2 20
2 3 12
2 4 1
4 5 3
26 9
1 10
500 2
2 30
```
### 样例输出 #1
```
206 321 542 328
```
## 提示

对于 $20\%$ 的数据，$N\leq 2500$；

对于 $50\%$ 的数据，树是一条链；

对于所有数据，$3\leq N\leq 10^5$，$0\leq W_i,V_i\leq 10^9$，每条边长度不超过 $10^4$。


---

---
title: "[COTS 2023] 下 Niz"
layout: "post"
diff: 省选/NOI-
pid: P10833
tag: ['线段树', '2023', 'O2优化', '分治', '哈希 hashing', 'COCI（克罗地亚）', '单调栈']
---
# [COTS 2023] 下 Niz
## 题目背景


译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D2T2。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述


给定长度为 $N$ 的序列 $a$，求满足以下条件的 $(l,r)$ 对数：

- $1\le l\le r\le N$；
- $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 是 $1\sim r-l+1$ 的排列。

## 输入格式


第一行，一个正整数 $N$，表示序列长度；

第二行，$N$ 个正整数，描述序列 $a$。
## 输出格式

一行一个整数，即满足条件的 $(l,r)$ 的数量。
## 样例

### 样例输入 #1
```
3
3 1 2 
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
3 2 1 2 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
7
2 1 3 1 2 3 4
```
### 样例输出 #3
```
8
```
## 提示


### 样例解释

样例 $3$ 解释：满足条件的 $(l,r)$ 有 $(2,2),(1,2),(1,3),(4,4),(4,5),(4,6),(4,7),(3,5)$。   

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 10^6$；
- $1\le a_i\le N$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $13$  | 每个数只在序列中出现一次  |
| $2$  | $20$  | $N\le 5\, 000$  |
| $3$  | $33$  | $N\le 50\, 000$ |
| $4$  | $34$  | 无额外约束 |






---

---
title: "「GFOI Round 2」Turtle and Nediam"
layout: "post"
diff: 省选/NOI-
pid: P11283
tag: ['洛谷原创', 'O2优化', '洛谷月赛', '单调栈']
---
# 「GFOI Round 2」Turtle and Nediam
## 题目背景

**[English statement](https://www.luogu.com.cn/problem/T533511). You must submit your code at the Chinese version of the statement.**
## 题目描述

对一个元素互不相同的长度 $\ge 3$ 的正整数序列 $a$，定义 $a$ 的“肿胃数（nediam）”$f(a)$ 为：

- 当 $|a| = 3$ 时，$f(a)$ 为 $a$ 的中位数；
- 当 $|a| > 3$ 时，取 $a$ 的任意一个长度为 $3$ 的子段 $[a_i, a_{i + 1}, a_{i + 2}]$，记这个子段的中位数为 $x$，$a$ 删掉 $x$ 后的序列为 $b$，$f(a)$ 为所有 $b$ 中 $f(b)$ 的最大值。

乌龟给你一个 $1 \sim n$ 的排列 $p_1, p_2, \ldots, p_n$ 和 $m$ 次询问，每次询问给定 $l, r$，你需要求出 $[p_l, p_{l + 1}, \ldots, p_r]$ 的“肿胃数（nediam）”，即 $f([p_l, p_{l + 1}, \ldots, p_r])$。
## 输入格式

为了加快读入速度，我们采用以下读入方法。

第一行包含六个正整数 $n, m, seed, A, B, C$。

第二行包含一个排列 $p_1, p_2, \ldots, p_n$。

接下来的 $m$ 组询问，每组询问你要按照如下的方式生成 $(l, r)$：

```cpp
unsigned seed, A, B, C;

inline unsigned rnd() {
	seed = A * seed * seed + B * seed + C;
	seed = seed ^ (seed << 27);
	seed = seed ^ (seed >> 19);
	return seed;
}

inline std::pair<int, int> gen() {
	int l, r;
	do {
		l = rnd() % n + 1;
		r = rnd() % n + 1;
	} while (abs(l - r) < 2);
	if (l > r) {
		std::swap(l, r);
	}
	return std::make_pair(l, r);
}
```

每组询问调用一次 `gen()` 生成这组询问的 $(l, r)$。
## 输出格式

为了加快输出速度，我们采用以下输出方法。

设第 $i$ 组询问的答案为 $ans_i$，你需要输出 $(1 \times ans_1) \oplus (2 \times ans_2) \oplus \cdots \oplus (m \times ans_m)$，其中 $\oplus$ 为按位异或。
## 样例

### 样例输入 #1
```
4 4 114 514 1919 810
1 3 4 2

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
10 100 123456 789123 456789 123456789
3 9 5 7 6 4 10 8 2 1

```
### 样例输出 #2
```
142

```
## 提示

#### 【样例解释 #1】

生成的四组询问分别为 $(1, 4), (1, 3), (1, 3), (2, 4)$，答案分别为 $2, 3, 3, 3$，所以你需要输出 $(1 \times 2) \oplus (2 \times 3) \oplus (3 \times 3) \oplus (4 \times 3) = 2 \oplus 6 \oplus 9 \oplus 12 = 1$。

对于第一组询问，选择子段 $[1, 3, 4]$ 或 $[3, 4, 2]$ 都会使得 $3$ 被删除。删除 $3$ 后的序列为 $[1, 4, 2]$，中位数为 $2$。

#### 【数据范围】

**本题使用捆绑测试。**

| 子任务编号 | $n \le$ | $m \le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $18$ | $100$ | 无 | $9$ |
| $2$ | $10^6$ | $5 \times 10^6$ | A | $5$ |
| $3$ | $10^3$ | $10^4$ | 无 | $19$ |
| $4$ | $10^5$ | $10^5$ | 无 | $17$ |
| $5$ | $10^6$ | $10^6$ | B | $15$ |
| $6$ | $10^6$ | $10^6$ | 无 | $13$ |
| $7$ | $10^6$ | $5 \times 10^6$ | 无 | $22$ |

- 特殊性质 A：$p_i = i$；
- 特殊性质 B：$p$ 从所有 $1 \sim n$ 的排列中等概率随机生成。

对于所有数据，满足：

- $3 \le n \le 10^6$；
- $1 \le m \le 5 \times 10^6$；
- $0 \le seed, A, B, C < 2^{32}$；
- $p$ 是一个 $1 \sim n$ 的排列。


---

---
title: "[USACO25FEB] Min Max Subarrays P"
layout: "post"
diff: 省选/NOI-
pid: P11845
tag: ['二分', 'USACO', '2025', '分类讨论', '单调栈']
---
# [USACO25FEB] Min Max Subarrays P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

给定一个长为 $N$ 的整数数组 $a_1,a_2,\dots,a_N$（$2\le N \le 10^6$，$1\le a_i\le N$)。输出所有 $N(N+1)/2$ 个 $a$ 的连续子数组的以下子问题的答案之和。

给定一个非空整数列表，交替执行以下操作（从第一个操作开始）直到列表大小恰好为一。

1. 将列表内的两个相邻整数替换为它们的较小值。
1. 将列表内的两个相邻整数替换为它们的较大值。

求最终余下的整数的最大可能值。

例如，

$[4, 10, 3] \to [4, 3] \to [4]$

$[3, 4, 10] \to [3, 10] \to [10]$

在第一个数组中，$(10, 3)$ 被替换为 $\min(10, 3)=3$，随后 $(4, 3)$ 被替换为 $\max(4, 3)=4$。

## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\dots,a_N$。
## 输出格式

输出所有连续子数组的子问题的答案之和。

## 样例

### 样例输入 #1
```
2
2 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
3 1 3
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
4
2 4 1 3
```
### 样例输出 #3
```
22
```
## 提示

样例 1 解释：

对于 $[2]$ 答案为 $2$，对于 $[1]$ 答案为 $1$，对于 $[2, 1]$ 答案为 $1$。

因此，我们的输出应当为 $2+1+1 = 4$。

样例 3 解释：

考虑子数组 $[2, 4, 1, 3]$。


1. 在 $(1, 3)$ 上应用第一次操作，我们的新数组是 $[2, 4, 1]$。
1. 在 $(4, 1)$ 上应用第二次操作，我们的新数组是 $[2, 4]$。
1. 在 $(2, 4)$ 上应用第三次操作，我们最终的数是 $2$。

可以证明 $2$ 是最终的数的最大可能值。

- 测试点 $4\sim 5$：$N\le 100$。
- 测试点 $6\sim 7$：$N\le 5000$。
- 测试点 $8\sim 9$：$\max(a)\le 10$。
- 测试点 $10\sim 13$：没有额外限制。


---

---
title: "[科大国创杯初中组 2023] 石子"
layout: "post"
diff: 省选/NOI-
pid: P11953
tag: ['2023', '安徽', '栈', '随机化', '科大国创杯']
---
# [科大国创杯初中组 2023] 石子
## 题目描述

小可可面前有 $n$ 堆石子，第 $i$ 堆石子有 $a_i$ 个石子。小可可想要在开始选择一堆石子，然后从它开始，每次合并这堆石子左边的那堆石子或者右边的那堆石子。合并两堆石子个数为 $x, y$ 的石子堆需要花 $x + y$ 的力气，并且会合并成一堆 $x + y$ 个石子的石子堆。

小可可想花费最小的力气从最初选择的那堆石子开始，将所有石子都合并完。小可可想知道，如果他选择编号在 $[l, r]$ 里面的每一堆石子作为最初的石子，那么他将 $n$ 堆石子合并成一堆花的最小力气是多少。

小可可不想太为难你，所以他保证所有的 $a_i$ 是随机的。
## 输入格式

第一行输入一行三个整数 $n, l, r$，石子堆数和最开始选择的那堆石子的编号区间。

第二行输入 $n$ 个整数 $a_1, a_2, \cdots, a_n$，表示每堆石子的石子个数。
## 输出格式

输出一行 $r - l + 1$ 个整数，第 $i$ 个整数表示小可可选择编号为 $l - 1 + i$ 的石子堆作为最开始的那堆石子时，将所有石子都合并完花的最少力气。
## 样例

### 样例输入 #1
```
4 1 4
5 1 3 1
```
### 样例输出 #1
```
25 19 19 19
```
## 提示

### 样例 1 解释

对于第 $1$ 堆石子作为初始的石子堆，最优（也是唯一）的合并策略是先合并第 $2$ 堆，再合并第 $3$ 堆，随后合并第 $4$ 堆，花费力气为 $25$；

对于第 $2$ 堆石子作为初始的石子堆，最优的合并策略是先合并第 $3$ 堆，再合并第 $4$ 堆，随后合并第 $1$ 堆，花费力气为 $19$；

对于第 $3$ 堆石子作为初始的石子堆，最优的合并策略是先合并第 $2$ 堆，再合并第 $4$ 堆，随后合并第 $1$ 堆，花费力气为 $19$；

对于第 $4$ 堆石子作为初始的石子堆，最优（也是唯一）的合并策略是先合并第 $3$ 堆，再合并第 $2$ 堆，随后合并第 $1$ 堆，花费力气为 $19$。

### 数据规模与约定

对于 $20 \%$ 的数据，满足 $n \leq 10$；

对于 $40 \%$ 的数据，满足 $n \leq 300$；

对于 $60 \%$ 的数据，满足 $n \leq 5000$；

对于另外 $20 \%$ 的数据，满足 $n \leq 10^5, r - l + 1 \leq 50$；

对于 $100 \%$ 的数据，有 $1 \leq l \leq r \leq n \leq 10^5, 1 \leq a_i \leq 10^8$。保证 $a_i$ 随机。随机方式为：先选择一个所有 $a_i$ 的上界 $v$，对于每个 $a_i$，它在 $[1, v]$ 中的所有整数中等概率随机选取一个。


---

---
title: "[APIO2012] 派遣"
layout: "post"
diff: 省选/NOI-
pid: P1552
tag: ['动态规划 DP', '2012', '平衡树', 'APIO', '可并堆', '栈']
---
# [APIO2012] 派遣
## 题目背景

在一个忍者的帮派里，一些忍者们被选中派遣给顾客，然后依据自己的工作获取报偿。

## 题目描述

在这个帮派里，有一名忍者被称之为 Master。除了 Master 以外，每名忍者都有且仅有一个上级。为保密，同时增强忍者们的领导力，所有与他们工作相关的指令总是由上级发送给他的直接下属，而不允许通过其他的方式发送。

现在你要招募一批忍者，并把它们派遣给顾客。你需要为每个被派遣的忍者支付一定的薪水，同时使得支付的薪水总额不超过你的预算。另外，为了发送指令，你需要选择一名忍者作为管理者，要求这个管理者可以向所有被派遣的忍者发送指令，在发送指令时，任何忍者（不管是否被派遣）都可以作为消息的传递人。管理者自己可以被派遣，也可以不被派遣。当然，如果管理者没有被排遣，你就不需要支付管理者的薪水。

   
你的目标是在预算内使顾客的满意度最大。这里定义顾客的满意度为派遣的忍者总数乘以管理者的领导力水平，其中每个忍者的领导力水平也是一定的。

   
写一个程序，给定每一个忍者 $i$ 的上级 $B_i$，薪水 $C_i$，领导力 $L_i$，以及支付给忍者们的薪水总预算 $M$，输出在预算内满足上述要求时顾客满意度的最大值。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，其中 $N$ 表示忍者的个数，$M$表示薪水的总预算。

 
接下来 $N$ 行描述忍者们的上级、薪水以及领导力。其中的第i行包含三个整数 $B_i,C_i,L_i$ 分别表示第 $i$ 个忍者的上级，薪水以及领导力。Master 满足 $B_i=0$，并且每一个忍者的老板的编号一定小于自己的编号 $B_i\lt i$。

## 输出格式

一行一个整数，表示在预算内顾客的满意度的最大值。

## 样例

### 样例输入 #1
```
5 4
0 3 3
1 3 5
2 2 2
1 2 4
2 3 1

```
### 样例输出 #1
```
6

```
## 提示

$1 \le N \le 10^5$，$1 \le M \le 10^9$，$0 \le B_i \lt i$，$1 \le C_i \le M$，$1 \le L_i \le 10^9$。

对于 $30\%$ 的数据，$N \le 3000$。



---

---
title: "[NOI2009] 诗人小G"
layout: "post"
diff: 省选/NOI-
pid: P1912
tag: ['动态规划 DP', '贪心', '2009', 'NOI', 'Special Judge', '栈']
---
# [NOI2009] 诗人小G
## 题目描述

小 G 是一个出色的诗人，经常作诗自娱自乐。但是，他一直被一件事情所困扰，那就是诗的排版问题。

一首诗包含了若干个句子，对于一些连续的短句，可以将它们用空格隔开并放在一行中，注意一行中可以放的句子数目是没有限制的。小 G 给每首诗定义了一个行标准长度（行的长度为一行中符号的总个数），他希望排版后每行的长度都和行标准长度相差不远。显然排版时，不应改变原有的句子顺序，并且小 G 不允许把一个句子分在两行或者更多的行内。在满足上面两个条件的情况下，小 G 对于排版中的每行定义了一个不协调度, 为这行的实际长度与行标准长度差值绝对值的 $P$ 次方，而一个排版的不协调度为所有行不协调度的总和。

小 G 最近又作了几首诗，现在请你对这首诗进行排版，使得排版后的诗尽量协调（即不协调度尽量小），并把排版的结果告诉他。

## 输入格式

输入文件中的第一行为一个整数 $T$，表示诗的数量。

接下来为 $T$ 首诗，这里一首诗即为一组测试数据。每组测试数据中的第一行为三个由空格分隔的正整数 $N,L,P$，其中：$N$ 表示这首诗句子的数目，$L$ 表示这首诗的行标准长度，$P$ 的含义见问题描述。

从第二行开始，每行为一个句子，句子由英文字母、数字、标点符号等符号组成（ASCII 码 $33 \sim 127$，但不包含 `-`）。

## 输出格式

于每组测试数据，若最小的不协调度不超过 $10^{18}$，则第一行为一个数，表示不协调度。接下来若干行，表示你排版之后的诗。注意：在同一行的相邻两个句子之间需要用一个空格分开。

如果有多个可行解，它们的不协调度都是最小值，则输出任意一个解均可。若最小的不协调度超过 $10^{18}$，则输出 `Too hard to arrange`。每组测试数据结束后输出 `--------------------`，共 20 个 `-`，`-` 的 ASCII 码为 45，请勿输出多余的空行或者空格。
## 样例

### 样例输入 #1
```
4
4 9 3
brysj,
hhrhl.
yqqlm,
gsycl.
4 9 2
brysj,
hhrhl.
yqqlm,
gsycl.
1 1005 6
poet
1 1004 6
poet

```
### 样例输出 #1
```
108
brysj,
hhrhl.
yqqlm,
gsycl.
--------------------
32
brysj, hhrhl.
yqqlm, gsycl.
--------------------
Too hard to arrange
--------------------
1000000000000000000
poet
--------------------

```
## 提示

#### 样例输入输出 1 解释

前两组输入数据中每行的实际长度均为 $6$，后两组输入数据每行的实际长度均为 $4$。一个排版方案中每行相邻两个句子之间的空格也算在这行的长度中（可参见样例中第二组数据）。每行末尾没有空格。

#### 数据规模与约定

| 测试点 | $T$ | $N$ | $L$ | $P$ |
| - | - | - | - | - |
| $1$ | $\le 10$ | $\le18$ | $\le 100$ | $\le5$ |
| $2$ | $\le 10$ | $\le 2\times 10^3$ |  $\le 6\times 10^4$| $\le10$ |
| $3$ | $\le 10$ | $\le 2\times 10^3$ |  $\le 6\times 10^4$| $\le10$ |
| $4$ | $\le 5$ | $\le 10^5$ | $\le 200$ | $\le10$ |
| $5$ | $\le 5$ | $\le 10^5$ | $\le 200$ | $\le10$ |
| $6$ | $\le 5$ | $\le 10^5$ | $\le 3\times 10^6$ | $2$ |
| $7$ | $\le 5$ | $\le 10^5$ | $\le 3\times 10^6$ | $2$ |
| $8$ | $\le 5$ | $\le 10^5$ | $\le 3\times 10^6$ | $\le10$ |
| $9$ | $\le 5$ | $\le 10^5$ | $\le 3\times 10^6$ | $\le10$ |
| $10$ | $\le 5$ | $\le 10^5$ | $\le 3\times 10^6$ | $\le10$ |

所有句子的长度不超过 $30$ 。


---

---
title: "[SDOI2011] 消耗战"
layout: "post"
diff: 省选/NOI-
pid: P2495
tag: ['2011', '各省省选', '山东', '最近公共祖先 LCA', '虚树', '栈']
---
# [SDOI2011] 消耗战
## 题目描述

在一场战争中，战场由 $n$ 个岛屿和 $n-1$ 个桥梁组成，保证每两个岛屿间有且仅有一条路径可达。现在，我军已经侦查到敌军的总部在编号为 $1$ 的岛屿，而且他们已经没有足够多的能源维系战斗，我军胜利在望。已知在其他 $k$ 个岛屿上有丰富能源，为了防止敌军获取能源，我军的任务是炸毁一些桥梁，使得敌军不能到达任何能源丰富的岛屿。由于不同桥梁的材质和结构不同，所以炸毁不同的桥梁有不同的代价，我军希望在满足目标的同时使得总代价最小。  

侦查部门还发现，敌军有一台神秘机器。即使我军切断所有能源之后，他们也可以用那台机器。机器产生的效果不仅仅会修复所有我军炸毁的桥梁，而且会重新随机资源分布（但可以保证的是，资源不会分布到 $1$ 号岛屿上）。不过侦查部门还发现了这台机器只能够使用 $m$ 次，所以我们只需要把每次任务完成即可。  
## 输入格式

第一行一个整数 $n$，表示岛屿数量。  

接下来 $n-1$ 行，每行三个整数 $u,v,w$ ，表示 $u$ 号岛屿和 $v$ 号岛屿由一条代价为 $w$ 的桥梁直接相连。  

第 $n+1$ 行，一个整数 $m$ ，代表敌方机器能使用的次数。  

接下来 $m$ 行，第 $i$ 行一个整数 $k_i$ ，代表第 $i$ 次后，有 $k_i$ 个岛屿资源丰富。接下来 $k_i$ 个整数 $h_1,h_2,..., h_{k_i}$ ，表示资源丰富岛屿的编号。  
## 输出格式

输出共 $m$ 行，表示每次任务的最小代价。  
## 样例

### 样例输入 #1
```
10
1 5 13
1 9 6
2 1 19
2 4 8
2 3 91
5 6 8
7 5 4
7 8 31
10 7 9
3
2 10 6
4 5 7 8 3
3 9 4 6

```
### 样例输出 #1
```
12
32
22

```
## 提示

#### 数据规模与约定

- 对于 $10\%$ 的数据，$n\leq 10, m\leq 5$ 。  
- 对于 $20\%$ 的数据，$n\leq 100, m\leq 100, 1\leq k_i\leq 10$ 。  
- 对于 $40\%$ 的数据，$n\leq 1000, 1\leq k_i\leq 15$ 。  
- 对于 $100\%$ 的数据，$2\leq n \leq 2.5\times 10^5, 1\leq m\leq 5\times 10^5, \sum k_i \leq 5\times 10^5, 1\leq k_i< n, h_i\neq 1, 1\leq u,v\leq n, 1\leq w\leq 10^5$ 。  


---

---
title: "[ZJOI2012] 小蓝的好友"
layout: "post"
diff: 省选/NOI-
pid: P2611
tag: ['2012', '各省省选', '平衡树', '浙江', '深度优先搜索 DFS', '栈']
---
# [ZJOI2012] 小蓝的好友
## 题目背景

终于到达了这次选拔赛的最后一题，想必你已经厌倦了小蓝和小白的故事。

为了回馈各位比赛选手，此题的主角是贯穿这次比赛的关键人物——小蓝的好友。

在帮小蓝确定了旅游路线后，小蓝的好友也不会浪费这个难得的暑假。

与小蓝不同，小蓝的好友并不想将时间花在旅游上，而是盯上了最近发行的即时战略游戏——SangoCraft。

但在前往通关之路的道路上，一个小游戏挡住了小蓝的好友的步伐。
## 题目描述


“国家的战争其本质是抢夺资源的战争”是整款游戏的核心理念，这个小游戏也不例外。

简单来说，用户需要在一块 $R\times C$ 的长方形土地上选出一块子矩形。

而系统随机生成了 $N$ 个资源点，第 $i$ 个资源点的坐标为 $(x_i,y_i)$。

位于用户所选的长方形土地上的资源点越多，给予用户的奖励也越多。

悲剧的是，小蓝的好友虽然拥有着极其优秀的能力，但同时也有着极差的 RP，小蓝的好友所选的区域总是没有一个资源点。

终于有一天，小蓝的好友决定投诉这款游戏的制造厂商，为了搜集证据，小蓝的好友想算出至少包含一个资源点的区域的数量。

具体的说，你需要计算有多少个四元组 $(LB,DB,RB,UB)$ 满足 $1\le LB\le RB\le R,1\le DB\le UB\le C$ ，且存在一个 $i$ 使得 $LB\le x_i\le RB,DB\le y_i\le UB$ 均成立。

作为小蓝的好友，这自然是你分内之事。
## 输入格式

第一行三个正整数 $R,C,N$。

接下来有 $N$ 行，每行包含两个整数 $x_i,y_i$，表示第 $i$ 个资源点的坐标。
## 输出格式

一行一个整数，表示至少包含一个资源点的区域的数量。
## 样例

### 样例输入 #1
```
5 5 4
1 2
2 3
3 5
4 1

```
### 样例输出 #1
```
139
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，$N\le 50$。
- 对于 $40\%$ 的数据，$N\le 2\times 10^3$。
- 对于 $100\%$ 的数据，$1\le R,C\le 4\times 10^4$，$1\le N\le 10^5$，题目保证资源点的位置两两不同，且位置为随机生成。


---

---
title: "[USACO15FEB] Censoring G"
layout: "post"
diff: 省选/NOI-
pid: P3121
tag: ['2015', 'USACO', '哈希 hashing', '栈', 'AC 自动机']
---
# [USACO15FEB] Censoring G
## 题目描述

FJ 把杂志上所有的文章摘抄了下来并把它变成了一个长度不超过 $10^5$ 的字符串 $s$。他有一个包含 $n$ 个单词的列表，列表里的 $n$ 个单词记为 $t_1 \cdots t_n$。他希望从 $s$ 中删除这些单词。

FJ 每次在 $s$ 中找到最早出现的列表中的单词（最早出现指该单词的开始位置最小），然后从 $s$ 中删除这个单词。他重复这个操作直到 $s$ 中没有列表里的单词为止。注意删除一个单词后可能会导致 $s$ 中出现另一个列表中的单词。

FJ 注意到列表中的单词不会出现一个单词是另一个单词子串的情况，这意味着每个列表中的单词在 $s$ 中出现的开始位置是互不相同的。

请帮助 FJ 完成这些操作并输出最后的 $s$。
## 输入格式

第一行是一个字符串，表示文章 $s$。

第二行有一个整数，表示单词列表的单词个数 $n$。

第 $3$ 到第 $(n + 2)$ 行，每行一个字符串，第 $(i + 2)$ 行的字符串 $t_i$ 表示第 $i$ 个单词。
## 输出格式

输出一行一个字符串，表示操作结束后的 $s$。
## 样例

### 样例输入 #1
```
begintheescapexecutionatthebreakofdawn 
2 
escape 
execution 

```
### 样例输出 #1
```
beginthatthebreakofdawn 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq |s|, \sum\limits_{i = 1}^n |t_i|, n \leq 10^5$。
- 字符串均只含小写字母。
- 操作结束后 $s$ 不会被删成空串。
- 对于所有的 $i \neq j$，$t_i$ 不是 $t_j$ 的子串。

其中对于一个字符串 $x$，约定 $|x|$ 表示 $x$ 的长度。

---

#### 提示

操作过程中 $s$ 有可能某一个前缀子串被完全删除，请格外注意这一点。



---

---
title: "[HNOI2009] 有趣的数列"
layout: "post"
diff: 省选/NOI-
pid: P3200
tag: ['2009', '湖南', '素数判断,质数,筛法', 'Catalan 数', '栈']
---
# [HNOI2009] 有趣的数列
## 题目描述

我们称一个长度为 $2n$ 的数列是有趣的，当且仅当该数列满足以下三个条件：

- 它是从 $1 \sim 2n$ 共 $2n$ 个整数的一个排列 $\{a_n\}_{n=1}^{2n}$；

- 所有的奇数项满足 $a_1<a_3< \dots < a_{2n-1}$，所有的偶数项满足 $a_2<a_4< \dots <a_{2n}$；

- 任意相邻的两项 $a_{2i-1}$ 与 $a_{2i}$ 满足：$a_{2i-1}<a_{2i}$。

对于给定的 $n$，请求出有多少个不同的长度为 $2n$ 的有趣的数列。  
因为最后的答案可能很大，所以只要求输出答案对 $p$ 取模。

## 输入格式

一行两个正整数 $n,p$
## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
3 10
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】   
对于 $50\%$ 的数据，$1\le n \le 1000$；  
对于 $100\%$ 的数据，$1\le n \le 10^6$，$1\le p \le 10^9$。

【样例解释】   
对应的5个有趣的数列分别为（1,2,3,4,5,6），（1,2,3,5,4,6），（1,3,2,4,5,6），（1,3,2,5,4,6），（1,4,2,5,3,6）。


---

---
title: "[HNOI2016] 序列"
layout: "post"
diff: 省选/NOI-
pid: P3246
tag: ['2016', '各省省选', '湖南', '前缀和', '栈', 'ST 表']
---
# [HNOI2016] 序列
## 题目描述

给定长度为 $ n $ 的序列：$ a_1, a_2, \cdots , a_n $，记为 $ a[1 \colon n] $。类似地，$ a[l \colon r] $（$ 1 \leq l \leq r \leq N$）是指序列：$ a_{l}, a_{l+1}, \cdots ,a_{r-1}, a_r$。若 $1\leq l \leq s \leq t \leq r \leq n$，则称 $ a[s \colon t] $ 是 $ a[l \colon r] $ 的子序列。

现在有 $ q $ 个询问，每个询问给定两个数 $ l $ 和 $ r $，$ 1 \leq l \leq r \leq n $，求 $ a[l \colon r] $ 的不同子序列的最小值之和。例如，给定序列
 $ 5, 2, 4, 1, 3 $，询问给定的两个数为 $ 1 $ 和 $ 3 $，那么 $ a[1 \colon 3] $ 有 $ 6 $ 个子序列 $a[1 \colon 1], a[2 \colon 2], a[3 \colon 3], a[1 \colon 2],a[2 \colon 3], a[1 \colon 3] $，这 $6 $ 个子序列的最小值之和为 $5+2+4+2+2+2=17$。
## 输入格式

输入文件的第一行包含两个整数 $ n $ 和 $ q $，分别代表序列长度和询问数。

接下来一行，包含 $ n $ 个整数，以空格隔开，第 $ i $ 个整数为 $ a_i $，即序列第 $i$ 个元素的值。

接下来 $ q $ 行，每行包含两个整数 $ l $ 和 $ r $，代表一次询问。
## 输出格式

对于每次询问，输出一行，代表询问的答案。

## 样例

### 样例输入 #1
```
5 5
5 2 4 1 3
1 5
1 3
2 4
3 5
2 5
```
### 样例输出 #1
```
28 
17 
11 
11 
17
```
## 提示

对于 $100\%$ 的数据，$ 1 \leq n,q \leq 100000$，$|a_i| \leq 10^9$。


---

---
title: "[JLOI2013] 赛车"
layout: "post"
diff: 省选/NOI-
pid: P3256
tag: ['2013', '吉林', '枚举', '栈', '半平面交']
---
# [JLOI2013] 赛车
## 题目描述

这里有一辆赛车比赛正在进行，赛场上一共有 $n$ 辆车，分别称为个 $g_1,g_2,...,g_n$。赛道是一条无限长的直线。最初，$g_i$ 位于距离起跑线前进 $k_i$ 的位置。比赛开始后，车辆 $g_i$ 将会以 $v_i$ 单位每秒的恒定速度行驶。在这个比赛过程中，如果一辆赛车曾经处于领跑位置的话（即没有其他的赛车跑在他的前面），这辆赛车最后就可以得奖，而且比赛过程中不用担心相撞的问题。现在给出所有赛车的起始位置和速度，你的任务就是算出那些赛车将会得奖。

## 输入格式

第一行有一个正整数 $n$，表示赛车的个数。

接下来一行，包含 $n$ 个整数，按顺序给出 $n$ 辆赛车的起始位置。再接下来一行给出 $n$ 个整数，按顺序给出 $n$ 辆赛车的恒定速度。
## 输出格式

输出包括两行，第一行为获奖的赛车个数。第二行按从小到大的顺序输出获奖赛车的编号，编号之间用空格隔开，注意最后一个编号后面不要加空格。
## 样例

### 样例输入 #1
```
4
1 1 0 0
15 16 10 20
```
### 样例输出 #1
```
3
1 2 4
```
## 提示

#### 数据范围与约定

- 对于 $100\%$ 的数据，$1 \le n \le 10^4$，$0 \le k_i \le 10^9$，$0 \le v_i \le 10^9$。


---

---
title: "[JLOI2015] 城池攻占"
layout: "post"
diff: 省选/NOI-
pid: P3261
tag: ['2015', '吉林', '可并堆', '栈']
---
# [JLOI2015] 城池攻占
## 题目描述

小铭铭最近获得了一副新的桌游，游戏中需要用 $m$ 个骑士攻占 $n$ 个城池。

这 $n$ 个城池用 $1$ 到 $n$ 的整数表示。除 $1$ 号城池外，城池 $i$ 会受到另一座城池 $f_i$ 的管辖，其中 $f_i<i$。也就是说，所有城池构成了一棵有根树。 

这 $m$ 个骑士用 $1$ 到 $m$ 的整数表示，其中第 $i$ 个骑士的初始战斗力为 $s_i$，第一个攻击的城池为 $c_i$。

每个城池有一个防御值 $h_i$，如果一个骑士的战斗力大于等于城池的生命值，那么骑士就可以占领这座城池；否则占领失败，骑士将在这座城池牺牲。占领一个城池以后，骑士的战斗力将发生变化，然后继续攻击管辖这座城池的城池，直到占领 $1$ 号城池，或牺牲为止。

除 $1$ 号城池外，每个城池 $i$ 会给出一个战斗力变化参数 $(a_i,v_i)$。若 $a_i=0$，攻占城池 $i$ 以后骑士战斗力会增加 $v_i$；若 $a_i=1$，攻占城池 $i$ 以后，战斗力会乘以 $v_i$。

注意每个骑士是单独计算的。也就是说一个骑士攻击一座城池，不管结果如何，均不会影响其他骑士攻击这座城池的结果。

现在的问题是，对于每个城池，输出有多少个骑士在这里牺牲；对于每个骑士，输出他攻占的城池数量。
## 输入格式

第 $1$ 行包含两个正整数 $n,m$，表示城池的数量和骑士的数量。

第 $2$ 行包含 $n$ 个整数，其中第 $i$ 个数为 $h_i$，表示城池 $i$ 的防御值。

第 $3\sim n+1$ 行，每行包含三个整数。其中第 $i+1$ 行的三个数为 $f_i,a_i,v_i$，分别表示管辖这座城池的城池编号和两个战斗力变化参数。

第 $n+2\sim n+m+1$ 行，每行包含两个整数。其中第 $n+i$ 行的两个数为 $s_i,c_i$，分别表示初始战斗力和第一个攻击的城池。

## 输出格式

输出 $n+m$ 行，每行包含一个非负整数。其中前 $n$ 行分别表示在城池 $1$ 到 $n$ 牺牲的骑士数量，后 $m$ 行分别表示骑士 $1$ 到 $m$ 攻占的城池数量。
## 样例

### 样例输入 #1
```
5 5
50 20 10 10 30
1 1 2
2 0 5
2 0 -10
1 0 10
20 2
10 3
40 4
20 4
35 5
```
### 样例输出 #1
```
2
2
0
0
0
1
1
3
1
1
```
## 提示

对于 $100\%$ 的数据，$1\le n,m\le 3\times 10^5$，$
-10^{18}\le h_i,v_i,s_i\le 10^{18}$，$1\le f_i<i,1\le c_i\le n,a_i\in\{0,1\}$，保证 $a_i=1$ 时，$v_i>0$，保证任何时候骑士战斗力值的绝对值不超过 $10^{18}$。



---

---
title: "[POI 2007] TET-Tetris Attack"
layout: "post"
diff: 省选/NOI-
pid: P3460
tag: ['贪心', '2007', '树状数组', 'POI（波兰）', 'Special Judge', '栈']
---
# [POI 2007] TET-Tetris Attack
## 题目描述

一种名为 *Tetris Attack* 的猜谜游戏风靡 Byteotia。游戏本身非常复杂，因此我们只介绍它的简化规则：

玩家拥有一个有 $2n$ 个元素的栈，一个元素放置在另一个元素上，这样一个组合有 $n$ 个不同的符号标记。对于每个符号，栈中恰好有两个元素用一个符号标记。

玩家可以交换两个相邻元素，即互换他们的位置。交换后，如果有两个相邻的元素标有相同的符号，则将他们都从栈中删除。然后，位于其上方的所有元素都会掉落下来，并且可以造成再次删除。

玩家的目标是以最少的移动次数清空堆栈。请你编写一个程序，找出最少的移动次数及方案。
## 输入格式

第一行一个整数 $n$。

接下来的 $2n$ 行里给出了栈的初始内容，第 $i+1$ 行包含一个整数 $a_i$（$1 \leq a_i \leq n $），表示从底部数起第 $i$ 个元素所标记的符号（每个符号都在栈中出现正好两次）。

最初不存在相邻的两个元素符号相同的情况，保证有不超过 $10^6$ 次操作的方案。
## 输出格式

第一行一个整数 $m$ ，表示最小的移动次数。

接下来 $m$ 行，每行输出一个数。

第 $i + 1$ 行输出 $p_i$，即表示玩家在第 $i$ 步时选择交换 $p_i$ 与 $p_{i+1}$。

如果存在多个方案，则输出其中任何一个。
## 样例

### 样例输入 #1
```
5
5
2
3
1
4
1
4
3
5
2
```
### 样例输出 #1
```
2
5
2
```
## 提示

$1 \le n \le 50000$


---

---
title: "[POI 2011] Lightning Conductor"
layout: "post"
diff: 省选/NOI-
pid: P3515
tag: ['动态规划 DP', '2011', 'POI（波兰）', '凸完全单调性（wqs 二分）', '栈']
---
# [POI 2011] Lightning Conductor
## 题目描述

Progressive climate change has forced the Byteburg authorities to build a huge lightning conductor    that would protect all the buildings within the city.

These buildings form a row along a single street, and are numbered from ![](http://main.edu.pl/images/OI18/pio-en-tex.1.png) to ![](http://main.edu.pl/images/OI18/pio-en-tex.2.png).

The heights of the buildings and the lightning conductor are non-negative integers.

Byteburg's limited funds allow construction of only a single lightning conductor.

Moreover, as you would expect, the higher it will be, the more expensive.

The lightning conductor of height ![](http://main.edu.pl/images/OI18/pio-en-tex.3.png) located on the roof of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.4.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.5.png))    protects the building ![](http://main.edu.pl/images/OI18/pio-en-tex.6.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.7.png)) if the following inequality holds:

![](http://main.edu.pl/images/OI18/pio-en-tex.8.png)        where ![](http://main.edu.pl/images/OI18/pio-en-tex.9.png) denotes the absolute value of the difference between ![](http://main.edu.pl/images/OI18/pio-en-tex.10.png) and ![](http://main.edu.pl/images/OI18/pio-en-tex.11.png).

Byteasar, the mayor of Byteburg, asks your help.

Write a program that, for every building ![](http://main.edu.pl/images/OI18/pio-en-tex.12.png), determines the minimum height    of a lightning conductor that would protect all the buildings if it were put    on top of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.13.png).



## 输入格式

In the first line of the standard input there is a single integer    ![](http://main.edu.pl/images/OI18/pio-en-tex.14.png) (![](http://main.edu.pl/images/OI18/pio-en-tex.15.png)) that denotes the number of buildings in Byteburg.

Each of the following ![](http://main.edu.pl/images/OI18/pio-en-tex.16.png) lines holds a single integer ![](http://main.edu.pl/images/OI18/pio-en-tex.17.png) (![](http://main.edu.pl/images/OI18/pio-en-tex.18.png))    that denotes the height of the ![](http://main.edu.pl/images/OI18/pio-en-tex.19.png)-th building.

## 输出格式

Your program should print out exactly ![](http://main.edu.pl/images/OI18/pio-en-tex.20.png) lines to the standard output.

The ![](http://main.edu.pl/images/OI18/pio-en-tex.21.png)-th line should give a non-negative integer ![](http://main.edu.pl/images/OI18/pio-en-tex.22.png) denoting the minimum    height of the lightning conductor on the ![](http://main.edu.pl/images/OI18/pio-en-tex.23.png)-th building.

## 样例

### 样例输入 #1
```
6
5
3
2
4
2
4
```
### 样例输出 #1
```
2
3
5
3
5
4
```
## 题目翻译

给定一个长度为 $n$ 的序列 $\{a_n\}$，对于每个 $i\in [1,n]$ ，求出一个最小的非负整数 $p$ ，使得 $\forall j\in[1,n]$，都有 $a_j\le a_i+p-\sqrt{|i-j|}$

$1 \le n \le 5\times 10^{5}$，$0 \le a_i \le 10^{9}$ 。


---

---
title: "[POI 2014] DOO-Around the world"
layout: "post"
diff: 省选/NOI-
pid: P3575
tag: ['搜索', '2014', '倍增', 'POI（波兰）', '栈']
---
# [POI 2014] DOO-Around the world
## 题目描述

After trying hard for many years, Byteasar has finally received a pilot license.

To celebrate the fact, he intends to buy himself an airplane and fly around the planet  3-SATurn (as you may have guessed, this is the planet on which Byteotia is located).

Specifically, Byteasar plans to fly along the equator.

Unfortunately, the equator is rather long, necessitating refuels.

  The flight range (on full tank) of each aircraft is known.

There is a number of airports along the equator, and a plane can be refueled when it lands on one.

Since buying an airplane is a big decision, Byteasar asks your help.

He is about to present you with a list of different plane models he is considering.

Naturally, these differ in their flight range.

For each plane model, he would like to know the minimum number of landings  (including the final one) he would have to make in order to complete the journey.

Note that for each airplane model, the journey may start at a different airport.

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。

## 输入格式

The first line of the standard input contains two integers $n$ and $s$ ($2\le n\le 1\ 000\ 000$, $1\le s\le 100$),separated by a single space,  denoting the number of airports along the equator and the number of airplane models Byteasar is considering.

The second line contains $n$ positive integers $l_1,l_2,\cdots,l_n$ ($l_1+l_2+\cdots+l_n\le 10^9$), separated by single spaces, specifying the distances between successive airports along the equator.

The number $l_i$ is the distance between the $i$-th and $(i+1)$-st (or $n$-th and first if $i=n$) in kilometers.

The third line contains $s$ integers $d_1,d_2,\cdots,d_s$ ($1\le d_i\le l_1+l_2+\cdots+l_n$), separated by single spaces. The number $d_i$ is the $i$-th airplane model's flight range in kilometers, i.e., the maximum distance it can fly before landing and refueling.

## 输出格式

Your program should print $s$ lines to the standard output: the $i$-th of these should contain a single integer, namely, the minimum lumber of flight segments (and thus also landings) necessary to fly the $i$-th airplane around the planet 3-SATurn along the equator, starting at an airport of choice, or the word NIE (Polish for no) if it is impossible to complete the journey with this airplane.

## 样例

### 样例输入 #1
```
6 4
2 2 1 3 3 1
3 2 4 11

```
### 样例输出 #1
```
4
NIE
3
2

```
## 提示

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。



---

---
title: "[USACO17OPEN] COWBASIC P"
layout: "post"
diff: 省选/NOI-
pid: P3666
tag: ['模拟', '2017', 'USACO', '矩阵乘法', '栈', '构造']
---
# [USACO17OPEN] COWBASIC P
## 题目描述

Bessie has invented a new programming language, but since there is no compiler yet, she needs your help to actually run her programs.


COWBASIC is a simple, elegant language. It has two key features: addition and MOO loops. Bessie has devised a clever solution to overflow: all addition is done modulo $10^9+7$. But Bessie's real achievement is the MOO loop, which runs a block of code a fixed number of times. MOO loops and addition can, of course, be nested.


Given a COWBASIC program, please help Bessie determine what number it returns.

## 输入格式

You are given a COWBASIC program at most 100 lines long, with each line being at most 350 characters long. A COWBASIC program is a list of statements.

There are three types of statements:

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

There are three types of expressions:

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

A literal is a positive integer at most 100,000.

A variable is a string of at most 10 lowercase English letters.

It is guaranteed that no variable will be used or RETURNed before it is defined. It is guaranteed that RETURN will happen exactly once, on the last line of the program.
## 输出格式

Output a single positive integer, giving the value of the RETURNed variable.

## 样例

### 样例输入 #1
```
x = 1
10 MOO {
x = ( x ) + ( x )
}
RETURN x
```
### 样例输出 #1
```
1024
```
### 样例输入 #2
```
n = 1
nsq = 1
100000 MOO {
100000 MOO {
nsq = ( nsq ) + ( ( n ) + ( ( n ) + ( 1 ) ) )
n = ( n ) + ( 1 )
}
}
RETURN nsq
```
### 样例输出 #2
```
4761
```
## 提示

Scoring

In 20 percent of all test cases - MOO loops are not nested.

In another 20 percent of all test cases - The program only has 1 variable. MOO loops can be nested.

In the remaining test cases, there are no further restrictions.
## 题目翻译

### 题目描述

Bessie 发明了一种新的编程语言，但由于还没有编译器，她需要你的帮助来实际运行她的程序。

COWBASIC 是一种简单而优雅的语言。它有两个关键特性：加法和 MOO 循环。Bessie 设计了一个巧妙的解决方案来处理溢出：所有的加法都是在模 $10^9+7$ 下进行的。但 Bessie 的真正成就是 MOO 循环，它可以固定次数地运行一段代码。当然，MOO 循环和加法可以嵌套。

给定一个 COWBASIC 程序，请帮助 Bessie 确定它返回的数字。

### 输入格式

你将获得一个最多 100 行的 COWBASIC 程序，每行最多 350 个字符。一个 COWBASIC 程序是一个语句列表。

有三种类型的语句：

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

有三种类型的表达式：

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

字面量是一个最多为 100,000 的正整数。

变量是一个最多由 10 个小写英文字母组成的字符串。

保证在定义之前不会使用或 RETURN 任何变量。保证 RETURN 恰好发生一次，并且在程序的最后一行。

### 输出格式

输出一个正整数，表示 RETURN 的变量的值。

### 说明/提示

评分

在 20% 的测试用例中，MOO 循环不会嵌套。

在另外 20% 的测试用例中，程序只有一个变量。MOO 循环可以嵌套。

在剩余的测试用例中，没有进一步的限制。


---

---
title: "[AH2017/HNOI2017] 影魔"
layout: "post"
diff: 省选/NOI-
pid: P3722
tag: ['2017', '线段树', '各省省选', '湖南', '排序', '栈']
---
# [AH2017/HNOI2017] 影魔
## 题目背景

影魔，奈文摩尔，据说有着一个诗人的灵魂。事实上，他吞噬的诗人灵魂早已成千上万。

千百年来，他收集了各式各样的灵魂，包括诗人、牧师、帝王、乞丐、奴隶、罪人，当然，还有英雄。

每一个灵魂，都有着自己的战斗力，而影魔，靠这些战斗力提升自己的攻击。
## 题目描述

奈文摩尔有 $n$ 个灵魂，他们在影魔宽广的体内可以排成一排，从左至右标号 $1$ 到 $n$。第 $i$ 个灵魂的战斗力为 $k_i$，灵魂们以点对的形式为影魔提供攻击力。对于灵魂对 $i, j\ (i<j)$ 来说，若不存在 $k_s\ (i<s<j)$ 大于 $k_i$ 或者 $k_j$，则会为影魔提供 $p_1$ 的攻击力。另一种情况，令 $c$ 为 $k_{i + 1}, k_{i + 2}, \cdots, k_{j -1}$ 的最大值，若 $c$ 满足：$k_i < c < k_j$，或者 $k_j < c < k_i$，则会为影魔提供 $p_2$ 的攻击力，当这样的 $c$ 不存在时，自然不会提供这 $p_2$ 的攻击力；其他情况的点对，均不会为影魔提供攻击力。

影魔的挚友噬魂鬼在一天造访影魔体内时被这些灵魂吸引住了，他想知道，对于任意一段区间 $[a, b]$，位于这些区间中的灵魂对会为影魔提供多少攻击力，即考虑所有满足 $a\le i<j\le b$ 的灵魂对 $i, j$ 提供的攻击力之和。

顺带一提，灵魂的战斗力组成一个 $1$ 到 $n$ 的排列：$k_1, k_1, \cdots, k_n$。
## 输入格式

第一行四个整数 $n,m,p_1,p_2$。  

第二行 $n$ 个整数 $k_1, k_2,\cdots, k_n$。

接下来 $m$ 行,每行两个数 $a,b$，表示询问区间 $[a,b]$ 中的灵魂对会为影魔提供多少攻击力。
## 输出格式

共输出 $m$ 行，每行一个答案，依次对应 $m$ 个询问。
## 样例

### 样例输入 #1
```
10 5 2 3
7 9 5 1 3 10 6 8 2 4
1 7
1 9
1 3
5 9
1 5
```
### 样例输出 #1
```
30
39
4
13
16
```
## 提示

对于 $30\%$ 的数据，$1\le n, m\le 500$。

另有 $30\%$ 的数据，$p_1 = 2p_2$。

对于 $100\%$ 的数据，$1\le n,m\le 200000, 1\le p_1, p_2\le 1000$。


---

---
title: "[JXOI2017] 颜色"
layout: "post"
diff: 省选/NOI-
pid: P4065
tag: ['2017', '线段树', '各省省选', '枚举', '概率论', '栈']
---
# [JXOI2017] 颜色
## 题目描述

可怜有一个长度为 $n$ 的正整数序列 $A_i$，其中相同的正整数代表着相同的颜色。

现在可怜觉得这个序列太长了，于是她决定选择一些颜色把这些颜色的所有位置都删去。

删除颜色 $i$ 可以定义为把所有满足 $A_j = i$ 的位置 $j$ 都从序列中删去。

然而有些时候删去之后，整个序列变成了好几段，可怜不喜欢这样，于是她想要知道有多少种删去颜色的方案使得最后剩下来的序列非空且连续。

例如颜色序列 $\{1, 2, 3, 4, 5\}$，删除颜色 $3$ 后序列变成了 $\{1, 2\}$ 和 $\{4, 5\}$ 两段，不满足条件。而删除颜色 $1$ 后序列变成了 $\{2, 3, 4, 5\}$，满足条件。

两个方案不同当且仅当至少存在一个颜色 $i$ 只在其中一个方案中被删去。

## 输入格式

第一行输入一个整数 $T$ 表示数据组数。

每组数据第一行，输入一个整数 $n$ 表示数列长度；第二行输入 $n$ 个整数描述颜色序列。

## 输出格式

对于每组数据输出一个整数表示答案。
## 样例

### 样例输入 #1
```
1
5
1 3 2 4 3
```
### 样例输出 #1
```
6
```
## 提示

满足条件的删颜色方案有 $\{1\}, \{1, 3\}, \{1, 2, 3\}, \{1, 3, 4\}, \{2, 3, 4\}, \varnothing$。

对于 $20\%$ 的数据，保证 $1 \le \sum n \le  20$。

对于 $40\%$ 的数据，保证 $1 \le \sum n \le  500$。

对于 $60\%$ 的数据，保证 $1 \le \sum n \le  10^4$。

对于 $100\%$ 的数据，保证 $1 \le  T,\sum n \le  3 \times 10^5, 1 \le  A_i \le  n$。

$\text{Statement fixed by @Starrykiller.}$


---

---
title: "[HEOI2014] 大工程"
layout: "post"
diff: 省选/NOI-
pid: P4103
tag: ['2014', '倍增', '各省省选', '河北', '虚树', '栈']
---
# [HEOI2014] 大工程
## 题目描述

国家有一个大工程，要给一个非常大的交通网络里建一些新的通道。

我们这个国家位置非常特殊，可以看成是一个单位边权的树，城市位于顶点上。

在 $2$ 个国家 $a,b$ 之间建一条新通道需要的代价为树上 $a,b$ 的最短路径的长度。

现在国家有很多个计划，每个计划都是这样，我们选中了 $k$ 个点，然后在它们两两之间 新建 $\dbinom{k}{2}$ 条新通道。

现在对于每个计划，我们想知道： 
1. 这些新通道的代价和。
2. 这些新通道中代价最小的是多少。
3. 这些新通道中代价最大的是多少。
## 输入格式

第一行 $n$ 表示点数。

接下来 $n-1$ 行，每行两个数 $a,b$ 表示 $a$ 和 $b$ 之间有一条边。点从 $1$ 开始标号。

接下来一行 $q$ 表示计划数。对每个计划有 $2$ 行，第一行 $k$ 表示这个计划选中了几个点。

第二行用空格隔开的 $k$ 个互不相同的数表示选了哪 $k$ 个点。
## 输出格式

输出 $q$ 行，每行三个数分别表示代价和，最小代价，最大代价。

## 样例

### 样例输入 #1
```
10 
2 1 
3 2 
4 1 
5 2 
6 4 
7 5 
8 6 
9 7 
10 9 
5 
2 
5 4 
2
10 4 
2 
5 2 
2
6 1 
2 
6 1
```
### 样例输出 #1
```
3 3 3 
6 6 6 
1 1 1 
2 2 2 
2 2 2
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 10^6,1\le q\le 5\times 10^4,\sum k\le 2\times n$。

每个测试点的具体限制见下表：

| 测试点编号 | $n$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $1\sim 2$ | $\le 10^4$ |  |
|$3\sim 5$  | $\le 10^5$ | 树的形态是链 |
| $6\sim 7$ | $\le 10^5$ |  |
| $8\sim 10$ | $\le 10^6$ |  |


---

---
title: "[CQOI2006] 凸多边形 /【模板】半平面交"
layout: "post"
diff: 省选/NOI-
pid: P4196
tag: ['2006', '重庆', '各省省选', '排序', '向量', '栈', '队列', '半平面交']
---
# [CQOI2006] 凸多边形 /【模板】半平面交
## 题目描述

逆时针给出 $n$ 个凸多边形的顶点坐标，求它们交的面积。例如 $n=2$ 时，两个凸多边形如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ieux7g3.png)

则相交部分的面积为 $5.233$。
## 输入格式

第一行有一个整数 $n$，表示凸多边形的个数，以下依次描述各个多边形。第 $i$ 个多边形的第一行包含一个整数 $m_i$，表示多边形的边数，以下 $m_i$ 行每行两个整数，逆时针给出各个顶点的坐标。
## 输出格式

输出文件仅包含一个实数，表示相交部分的面积，保留三位小数。
## 样例

### 样例输入 #1
```
2
6
-2 0
-1 -2
1 -2
2 0
1 2
-1 2
4
0 -3
1 -1
2 2
-1 0
```
### 样例输出 #1
```
5.233
```
## 提示

对于 $100\%$ 的数据：$2 \leq n \leq 10$，$3 \leq m_i \leq 50$，每维坐标为 $[-1000,1000]$ 内的整数。


---

---
title: "[BalticOI 2004] Sequence 数字序列"
layout: "post"
diff: 省选/NOI-
pid: P4331
tag: ['2004', '线段树', 'Special Judge', '可并堆', '栈', 'BalticOI（波罗的海）']
---
# [BalticOI 2004] Sequence 数字序列
## 题目描述

给定一个整数序列 $a_1, a_2, \cdots , a_n$，求出一个递增序列 $b_1 < b_2 < ··· < b_n$，使得序列 $a_i$ 和 $b_i$ 的各项之差的绝对值之和 $|a_1 - b_1| + |a_2 - b_2| + \cdots + |a_n - b_n|$ 最小。
## 输入格式

第一行为数字 $n (1≤n≤10^6)$，接下来一行共有 $n$ 个数字，表示序列 $a_i (0≤a_i≤2^{31}-1)$。
## 输出格式

第一行输出最小的绝对值之和。

第二行输出序列 $b_i$，若有多种方案，只需输出其中一种。
## 样例

### 样例输入 #1
```
5
2 5 46 12 1

```
### 样例输出 #1
```
47
2 5 11 12 13
```
## 提示

【数据范围】

- $40\%$ 的数据 $n≤5000$；
- $60\%$ 的数据 $n≤300000$；
- $100\%$ 的数据 $n≤10^6 , 0≤a_i≤2^{31}-1$；

题目来源：BalticOI 2004 Day 1, Sequence。

感谢 @TimeTraveller 提供 SPJ。



---

---
title: "[HNOI/AHOI2018] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P4436
tag: ['2018', '各省省选', '安徽', '湖南', '枚举', '剪枝', '强连通分量', '栈']
---
# [HNOI/AHOI2018] 游戏
## 题目描述

一次小G和小H在玩寻宝游戏，有 $n$ 个房间排成一列，编号为 $1,2,\cdots,n$ ，相邻的房间之间都有一道门。其中一部分门上锁（因此需要有对应的钥匙才能开门），其余的门都能直接打开。现在小G告诉了小H每把锁的钥匙在哪个房间里（**每把锁有且只有一把钥匙与之对应**），并作出 $p$ 次指示：第 $i$ 次让小H从第 $S_i$ 个房间出发到 $T_i$ 个房间里。但是小G有时会故意在指令中放入死路，而小H也不想浪费多余的体力去尝试，于是想事先调查清楚每次的指令是否会存在一条通路。

你是否能为小H作出解答呢？
## 输入格式

第一行三个数字： $n,m,p$ ，代表有 $n$ 个房间， $m$ 道门上了锁，以及 $p$ 个询问。接下来$m$行，每行两个数字 $x,y$ 代表 $x$ 到 $x+1$ 的钥匙在房间 $y$ 。接下来 $p$ 行，其中第$i$行是两个整数 $S_i$，$T_i$，代表一次询问
## 输出格式

输出 $p$ 行，每行一个`YES`或`NO`，分别代表能或不能到达。
## 样例

### 样例输入 #1
```
5 4 5 
1 3
2 2 
3 1
4 4
2 5
3 5
4 5 
2 1
3 1
```
### 样例输出 #1
```
YES
NO
YES
YES
NO
```
### 样例输入 #2
```
7 5 4
2 2
3 3 
4 2 
5 3 
6 6
2 1
3 4
3 7
4 5
```
### 样例输出 #2
```
YES
YES
NO
NO
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/17503.png)

$1\le n,p\le 10^6$ ， $0\le m <n$ ， $1\le x,y,S_i,T_i<n$ 保证 $x$ 不重复


---

---
title: "[CEOI 2011] Balloons"
layout: "post"
diff: 省选/NOI-
pid: P4697
tag: ['计算几何', '2011', 'Special Judge', 'CEOI（中欧）', '单调栈']
---
# [CEOI 2011] Balloons
## 题目描述

有 $n$ 个气球，他们一开始都是空的。

接下来，它们会按照从 $1$ 到 $n$ 的顺序依次充气，其中第 $i$ 个气球与地面在 $x_i$ 位置接触。

当气球碰到碰到前面的某个气球，或者达到半径最大限制时，就会停止充气。其中第 $i$ 个气球的半径最大限制为 $r_i$。

现在请你求出，每个气球最终半径是多少。
## 输入格式

第一行一个正整数 $n$，表示气球个数。

接下来 $n$ 行，每行两个空格隔开的整数 $x_i,r_i$。
## 输出格式

输出 $n$ 行，每行一个浮点数，第 $i$ 行的浮点数表示最终第 $i$ 个气球的半径。

你的答案会被判为正确，当且仅当与答案的绝对误差不超过 $10^{-3}$​​。
## 样例

### 样例输入 #1
```
3
0 9
8 1
13 7
```
### 样例输出 #1
```
9.000
1.000
4.694
```
## 提示

对于 $100\%$ 的数据，保证 $1\le n\le 200\ 000;0\le x_i\le 10^9;1\le r_i\le 10^9;x_1< x_2< \cdots < x_n$。


---

---
title: "小奔上课"
layout: "post"
diff: 省选/NOI-
pid: P4908
tag: ['字符串', '递归', '栈']
---
# 小奔上课
## 题目背景

这一堂课是数学课！
## 题目描述

小奔最喜欢数学了QvQ，但是因为晚上太困睡着了，所以当他反应过来要写题目时，黑板上的算式已经残缺不堪了。

没办法，小奔只好依靠人品猜一下了，只是猜也是有方法的，小奔想请你给出最大可能值和最输出只有一行，为最大可能值和最小可能值的平均值，并保留两位小数小可能值的平均值。
## 输入格式

只有一行，为残缺的算式（可能有括号），残缺部分用$*$表示~~（与乘号相同）~~，残缺部分可以为数字$0$到$9$，也可以是四则运算符号之一，不存在残缺括号。

## 输出格式

输出只有一行，为最大可能值和最小可能值的平均值，并保留两位小数
## 样例

### 样例输入 #1
```
1*1+9-2*3/1
```
### 样例输出 #1
```
-41.50
```
## 提示

样例解释:

最大值：$191+9-2+3/1=201$

最小值：$1-1+9-293/1=-284$

$07+1$（0不能打头），$5/0$（0不能做除数）等算式都是非法的

但$8+-6$是合法的，代表$8$加负$6$，同理$8/-6$也可

保证结果在$float$范围内


对于$40$%的数据，算式有括号

对于$10$%的数据，算式完全残缺（全是 * ）



---

---
title: "河童重工的计算机"
layout: "post"
diff: 省选/NOI-
pid: P4911
tag: ['模拟', '字符串', '栈']
---
# 河童重工的计算机
## 题目背景

河童重工业会社的计算机产品在幻想乡中有着极其广泛的应用。

有一天，妖怪之山发大水啦！洪水夹杂着泥沙和滚木汹涌着冲进了河童的城市。

本来河童们的机械设施都是防水的，可是洪水还是对城市造成了不小的破坏。其中，河童们的服务器被砸坏了！

坏掉的电脑在短时间内不能修复，可是幻想乡里的许多事情都离不开河童们的服务器！河童们也很无奈，于是荷取找到了你！你作为一名优秀的信竞选手，决定帮助荷取，减轻服务器故障所带来的压力。
## 题目描述

你从荷取那里得到了一份纸质资料，扫描版在这里：

[Ktx-65式微处理器汇编语言规范文件.pdf](https://www.touhou-oi.tk/uploads/Ktx-65%E5%BC%8F%E5%BE%AE%E5%A4%84%E7%90%86%E5%99%A8%E6%B1%87%E7%BC%96%E8%AF%AD%E8%A8%80%E8%A7%84%E8%8C%83%E6%96%87%E4%BB%B6.pdf)

（若此网站无法打开，请在附件中下载）

（为什么说是扫描版呢，因为，你应该不能复制里面的文字）

以下这一段是汇编教程附带的示例：
```asm
[ progfunc.asm ]
[ Shows the function functionailties of the KTX-65 ALI ]

[main]
wint #line;    [output the current physical line number]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
callfunc $Function1;
callfunc $Function2;
hlt;           [halt]

function $Function1;
rint %r1;      [read int]
add %r2 1 %r2; [loop contents]
lle %r2 %r1;   [loop conditions]
jif 2;         [end loop conditional jump]
wint %r2;      [output int]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
ret;           [return]

function $Function2;
rint %r1;      [read int]
rint %r2;      [read int]
add %r1, %r2;  [add]
wint %val;     [output value]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
ret;           [return]
```
你需要用洛谷评测机支持的语言编写一个程序，它读入一个Ktx-65汇编语言程序和一段输入，解释运行这个程序，然后输出这个程序输出的东西。
## 输入格式

第一行是一个整数N，表示汇编程序的行数。

接下来N行是这个汇编程序，保证不会出现空行。

接下来的所有行都是这个汇编程序的输入。
## 输出格式

一堆东西，表示这个汇编程序的输出。

~~**评测系统将以逐字节比较的方式判断你的输出是否正确。**~~假的，洛谷不支持
## 样例

### 样例输入 #1
```
5
rint %r1;
rint %r2;
add %r1 %r2;
wint;
hlt;
5 4
```
### 样例输出 #1
```
9
```
## 提示



**注意**：样例输出中只有9这一个字节。

**保证一行中只有一个指令。**

对于10%的数据：程序中只有输入和输出的指令，且不会出现数字常量，也不会有注释。

对于另外10%：程序中只有输入、输出和加法指令，且没有注释。

对于另外30%：包括除函数调用和跳转在内的所有指令。

对于剩下50%：指令没有限制。

对于全部的数据：命令条数不超过50000条，剩余输入不超过500千字节，程序需要执行的步数不超过80000步。

保证汇编程序和数据不出现编译或是运行时错误。

保证程序输入足够满足汇编程序中读入的需要。

不保证这是或不是一道毒瘤题

不保证考试时会不会有人AC这道题

不保证这次考试会不会有人AK

保证出题人为：[洩矢诹访子](https://www.luogu.org/space/show?uid=53151)

考试时打不开河童给的文件可以向我索要，不保证是否会回答

~~其实这道题数据非常简单，只是量大而已~~


---

---
title: "绫小路的特别考试"
layout: "post"
diff: 省选/NOI-
pid: P4964
tag: ['贪心', '枚举', '排序', '深度优先搜索 DFS', '栈']
---
# 绫小路的特别考试
## 题目背景

>  这世界上「胜利」便是一切。无关乎过程。
要付出多少牺牲都无所谓。只要最后我「胜出」那就行了。

![](https://i.loli.net/2018/10/06/5bb879f4ac370.jpg)
## 题目描述

一场新的特别考试来临了，这次的考试内容是（wan e de）文化课，但有所不同的是，考试中允许学生使用对讲机。然而，对讲机的接收范围是有限的（每个对讲机都能发送无限远，但是只能接收到接收范围内的信号），所以不是所有学生都能接收到其他同学的广播。

考试时，共有 $n$ 名学生坐成一排（从左至右依次编号为 $1$ ~ $n$），绫小路自己坐在第 $c$ 号位置。每名学生都有一个能力值 $w_i$。绫小路已经给每名学生安排了一个接收范围为 $d_i$ 的对讲机。

每名学生可以直接做出难度**不超过**自身能力值的**所有**题目，一旦一名学生凭能力做出某道题，他就会把这道题的做法进行广播。一名坐在位置 $i$，有接收范围为 $d_i$ 的对讲机的学生，可以接收到 $[i-d_i,\ i+d_i]$ 范围内所有学生的广播，若这个范围内有人公布了做法，则他将会做这道题，并也会把这道题的做法进行广播。

绫小路会问你一些问题：当一道题目难度为 $x$ 时，有多少学生会做这道题？由于绫小路想隐藏实力，他可能会修改自己的能力值。这两种操作分别用以下两种方式表示：

- $1\ x$，表示询问当一道题目难度为 $x$ 时，有多少学生会做这道题。

- $2\ x$，将绫小路的能力值修改为 $x$，即将 $w_c$ 修改为 $x$。

---

形式化描述（与上文同义）：

> 给你两个长为 $n$ 的数列 $w_{1..n}$ 和 $d_{1..n}$，以及一个 $w_c$ 可修改的位置 $c$。现在有两种操作（共 $m$ 次）：
- $1\ x$ 表示一次询问：设 $f_i=\begin{cases}1\quad(w_i\ge x)\\1\quad(\exists\ j \in [i - d_i,\ i + d_i],\ f_j=1)\\ 0\quad(otherwise)\end{cases}$，这里的 $f_i$ 定义中引用了 $f_j$，$\ \ \ \ $所以 $f_{1..n}$ 是会不断更新的，直到无法继续更新时，计算这次询问的答案为 $\sum\limits_{i=1}^nf_i$。
- $2\ x$ 表示一次修改：把 $w_c$ 修改为 $x$。
## 输入格式

由于数据量太大，为了避免读入耗时过长，使用**伪随机数生成器**的方式输入，并**强制在线**。

**建议你忽略输入格式，直接使用下面提供的数据生成器模板，了解具体的生成过程对你来说是不必要的。**

第一行，三个正整数 $n,\ m,\ c$，分别代表学生的总人数，操作总数和绫小路所在的位置。

第二行，五个整数 $\mathrm{seed},\ \mathrm{mind},\ \mathrm{maxd},\ \mathrm{mfq},\ k$。

> 此处的 $\mathrm{mind},\ \mathrm{maxd}$ 仅用于生成初始的 $d_{1..n}$，下文中调整 $d_p$ 所用的 $t$ 可能不在 $[\mathrm{mind},\ \mathrm{maxd}]$ 范围内。

接下来的 $k$ 行，每行两个整数 $p,\ t$，表示调整第 $p$ 号同学的对讲机接收范围（即 $d_p$）为 $t$。

> 若一名同学的对讲机接收范围被调整多次，以**最后一次**为准。

---

** 数据生成器模板：**

```cpp
#include <cstdio>

unsigned long long seed;
int n, m, c, mfq, mind, maxd, k, w[2000001], d[2000001];

inline int randInt() { seed = 99999989 * seed + 1000000007; return seed >> 33; } 

void generate()
{
	// 在读入种子后生成初始的 w 数组和 d 数组.
    for (int i = 1; i <= n; i++) { w[i] = randInt() % n; }
    for (int i = 1; i <= n; i++) { d[i] = randInt() % (maxd - mind + 1) + mind; }
}

void getOperation(int lastans, int &opt, int &x)
{
    // 生成一次操作的参数 opt 和 x, lastans 表示上一次询问的答案, 初始值为 0.
    if ((0ll + randInt() + lastans) % mfq) { opt = 1; } else { opt = 2; }
    x = (0ll + randInt() + lastans) % n;
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);
    scanf("%llu %d %d %d %d", &seed, &mind, &maxd, &mfq, &k);
    generate();
    for (int i = 1; i <= k; i++)
    {
        int p, t;
        scanf("%d %d", &p, &t);
        d[p] = t;
    }
    // 从这里开始，你可以使用生成的 w 数组和 d 数组.
    int lastans = 0, finalans = 0;
    for (int i = 1; i <= m; i++)
    {
        int opt, x;
        getOperation(lastans, opt, x);
        if (opt == 1)
        {
            // 在这里执行询问操作，并用答案的表达式替代下面的 ___.      
            finalans = (finalans * 233ll + ___) % 998244353;
            lastans = ___;
        }
        else
        {
            // 在这里执行修改操作.
        }
    }
    printf("%d\n", finalans);
    return 0;
}
```
## 输出格式

令 $ans_i$ 表示第 $i$ 次询问（操作 $1$）的答案，$T_i=\begin{cases}(T_{i-1}\times 233+ans_i)\mod 998244353\quad(i\ge 1)\\0\quad(i=0)\end{cases}$

设 $q$ 表示询问（操作 $1$）的个数，你只需要输出一个整数 $T_q$。
## 样例

### 样例输入 #1
```
3 3 2
19720918 0 1 2 0
```
### 样例输出 #1
```
700
```
### 样例输入 #2
```
10 10 8
2102036 0 1 4 1
5 2
```
### 样例输出 #2
```
760521825
```
### 样例输入 #3
```
1000 1000 126
114321251 1 2 2 0
```
### 样例输出 #3
```
91977056
```
## 提示

### 你需要用到的变量：

$1\le c\le n\le 2\times 10^6$，$1\le m\le 2\times 10^6$，$0\le w_i,\ d_i,\ x<n$。

### 其它用于生成数据的变量：

$1\le \mathrm{seed},\ \mathrm{mfq}\le 10^9$，$0\le \mathrm{mind}\le \mathrm{maxd}<n$，$0\le k\le 2\times 10^5$，$1\le p\le n$，$0\le t<n$。

## 样例解释

### 样例一：

生成得到三名同学的能力值 $w_{1..3} = \{0,\ 1,\ 2\}$，对讲机接收范围 $d_{1..3} = \{1,\ 0,\ 1\}$。

第一个操作是 `1 1`，询问有多少同学会做难度为 $1$ 的题。

绫小路（第 $2$ 名同学）和第 $3$ 名同学能够独立做出这道题（$w_2 \ge 1$ ，$w_3 \ge 1$），第 $1$ 名同学虽然能力不足，但通过对讲机能接收到绫小路广播的做法（$2 \in [1 - d_1,\ 1 + d_1]$），所以他也会做。故 $ans_1 = 3$。

第二个操作是 `2 0`，修改绫小路（第 $2$ 名同学）的能力值为 $0$。此时 $w_{1..3} = \{0,\ 0,\ 2\}$。

第三个操作是 `1 1`，再次询问有多少同学会做难度为 $1$ 的题。

只有第 $3$ 名同学能够独立做出（$w_3 \ge 1$），然而第 $1$ 名同学和绫小路（第 $2$ 名同学）都无法接收到他广播的做法（$3 \notin [1 - d_1,\ 1 + d_1]$，$3 \notin [2 - d_2,\ 2 + d_2]$），做不出来。故 $ans_2 = 1$。

综上所述，$T_1 = ans_1 = 3$，$T_2 = 3 \times T_1+ ans_2 = 3 \times 233 + 1 = 700$，仅输出 $700$ 即可。

### 样例二：

生成得到 $w_{1..10} = \{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 7,\ 9,\ 5\}$，$d_{1..10} =\{1,\ 1,\ 1,\ 1,\ 2,\ 0,\ 1,\ 0,\ 1,\ 1\}$。

十次操作及对应结果如下所示：

`1 6`，查询操作，$ans_1 = 9$，$T_1 = 9$。

`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。

`1 7`，查询操作，$ans_2 = 2$，$T_2 = 2099$。

`1 3`，查询操作，$ans_3 = 9$，$T_3 = 489076$。

`2 4`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 4,\ 9,\ 5\}$。

`1 3`，查询操作，$ans_4 = 10$，$T_4 = 113954718$。
  
`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。
  
`1 9`，查询操作，$ans_5 = 2$，$T_5 = 597096118$。  

`1 0`，查询操作，$ans_6 = 10$，$T_6 = 367430437$。    

`1 3`，查询操作，$ans_7 = 9$，$T_7 = 760521825$。

仅输出 $760521825$ 即可。

### 样例三：

~~出题人有足够的良心写出这个样例的解释，可惜版面太小，写不下。~~


---

---
title: "[CTSC1998] 算法复杂度"
layout: "post"
diff: 省选/NOI-
pid: P5698
tag: ['模拟', '字符串', '1998', '栈', 'CTSC/CTS']
---
# [CTSC1998] 算法复杂度
## 题目背景

CTSC1998 D1T3

我们在编程时，最关心的一个问题就是算法的时间复杂度。但是分析一个程序的复杂度是一项很困难的工作，在程序的码风不是很好的情况下更是如此。

所以，专门研究算法的 SERKOI 小组决定开发出一个分析程序时间复杂度的软件。由于这是一个全新的领域，所以 SERKOI 小组决定先从简单情况入手进行分析。
## 题目描述

为了简化问题,程序只包含循环和顺序结构,程序的结构定义如下：

$\texttt{begin <statement> end}$ 

一个语句块的结构是**递归定义**的，如下所示：

$\texttt{loop x <statement> end}$

或者 $\texttt{op <statement>}$ 

或者为 $\texttt{break <statement>}$ 

或者为 $\texttt{continue <statement>}$ 

语句块可以为空。

注意：

1. 一个程序都是以 $\texttt{begin}$ 开始，以相应的 $\texttt{end}$ 结束；

2. $\texttt{loop x <statement> end}$ 表示其中的语句重复执行 $x$ 次；

3. $\texttt{op x}$ 表示执行 $x$ 个单位操作；

4. 上面两点中的 $x$ 可以是一个正整数或 $n$；

5. $\texttt{break}$ 语句的作用是跳出这一层循环, $\texttt{continue}$ 语句的作用是跳过这一层循
环的其它语句，直接进入下一次循环。如果它（$\texttt{break}$ 或 $\texttt{continue}$）不在任何一层循环中，**请忽略它们**。

你需要写一个程序，用来求出题目描述的程序的时间复杂度，并以多项式的形式输出。

注意，该多项式是关于 $n$ 的多项式，而且，**常数项和系数不能省略**。

数据保证能求出该程序的时间复杂度。
## 输入格式

输入中包含一个完整的程序，
每两条语句之间至少用一个空格或换行符隔开。

## 输出格式

将计算出的时间复杂度多项式按**降幂排列**输出。
## 样例

### 样例输入 #1
```
begin loop n loop 3 loop n
op 20
end end end
loop n op 3 break end
loop n loop n
op 1
break
end end
end

```
### 样例输出 #1
```
60n^2+n+3
```
### 样例输入 #2
```
begin
op n
loop 3
op n
break
end
loop n
loop n
op 1
continue
op n
end
end
end 
```
### 样例输出 #2
```
n^2+2n
```
## 提示

循环的嵌套最多不超过 $20$ 层。

保证最终时间复杂度多项式每项的系数不超过 ${10}^9$。


---

---
title: "[JOI 2019 Final] 珍しい都市"
layout: "post"
diff: 省选/NOI-
pid: P6118
tag: ['2019', '树的直径', '栈', 'JOI（日本）']
---
# [JOI 2019 Final] 珍しい都市
## 题目背景

JOI 2019 Final T5

由于数据点较多，本题只评测其中的部分数据。
## 题目描述

JOI 国有 $N$ 个城市，城市从 $1$ 到 $N$ 编号。这些城市被 $N-1$ 条双向道路连接，第 $i$ 条路连接两个城市 $A_i$ 和 $B_i$。从任何城市出发，可以到达所有城市。

JOI 国有些特产，每种特产的编号都在 $1$ 到 $M$ 之间（包括 $1$ 和 $M$），但是 $1$ 到 $M$ 的某些整数可能不代表 JOI 国的特产。JOI 国的每个城市都产一种特产。$j$ 城产的特产是 $C_j$。多个城市可能产相同的特产。

我们定义两个城市之间的距离为从一个城市到另一个城市需要经过的最少道路数，对于城市 $x$，我们定义城市 $y$（$y\neq x$）是**独特的城市**当且仅当对于任何一个城市 $z$（$z\neq x,z\neq y$），$x$ 与 $y$ 间的距离不等于 $x$ 与 $z$ 之间的距离。

JOI 国交通部部长 K 先生想知道对于城市 $j$ 的**独特的城市**一共能产多少种特产。

给出 JOI 国的道路信息与每个城市产的特产，写一个程序计算对于每个城市的**独特的城市**，一共能产多少种特产。
## 输入格式

第一行两个整数 $N,M$，意义如题目描述。

接下来 $N-1$ 行，每行两个整数 $A_i,B_i$，意义如题目描述。

最后一行 $N$ 个正整数，第 $i$ 个为 $C_i$，意义如题目描述。
## 输出格式

输出 $N$ 行，第 $i$ 行表示对于城市 $i$ 的独特的城市一共能产多少种特产。
## 样例

### 样例输入 #1
```
5 4
1 2
2 3
3 4
3 5
1 2 1 2 4
```
### 样例输出 #1
```
2
0
1
1
1
```
### 样例输入 #2
```
7 1
1 2
2 3
3 4
4 5
5 6
6 7
1 1 1 1 1 1 1
```
### 样例输出 #2
```
1
1
1
0
1
1
1
```
### 样例输入 #3
```
10 10
2 6
5 8
10 8
1 4
10 6
4 5
10 7
6 9
3 7
1 2 3 4 5 6 7 8 9 10
```
### 样例输出 #3
```
4
3
4
2
0
2
2
0
3
2
```
### 样例输入 #4
```
22 12
9 6
12 13
4 20
21 22
3 19
2 9
6 18
18 11
18 3
16 2
6 4
3 17
16 10
8 16
22 1
16 14
15 8
9 21
2 12
21 5
12 7
1 1 4 8 4 11 7 6 7 11 6 11 10 4 7 5 3 12 9 6 12 2
```
### 样例输出 #4
```
2
0
1
1
1
1
1
0
0
1
2
0
1
1
2
0
2
1
2
3
0
0
```
## 提示

样例解释 $1$：  

对于城市 $1$，它的独特城市是城市 $2,3$，城市 $2$ 产特产 $2$，城市 $3$ 产特产 $3$，一共产两种特产，因此答案是 $2$；  

对于城市 $2$，没有独特城市，因此输出 $0$；
  
对于城市 $3$，它的独特城市是城市 $1$，城市 $1$ 产特产 ，因此答案是 $1$；  

对于城市 $4$，它的独特城市是城市 $1,3$，城市 $1,3$ 均产特产 $1$，因此答案是 $1$；  

对于城市 $5$，它的独特城市是城市 $1,3$，城市 $1,3$ 均产特产 $1$，因此答案是 $1$。  

注意：没有城市产特产 $3$。  

对于 $4\%$ 的数据，$N\le 2000$。

另有 $32\%$ 的数据，$M=1$。

另有 $32\%$ 的数据，$M=N,C_j=j(1\le j \le N)$。

对于 $100\%$ 的数据，$1\le N \le 2\times 10^5,1\le M,A_i,B_i \le N,A_i \neq B_i,1\le C_j \le M$。


---

---
title: "『STA - R1』Crossnews"
layout: "post"
diff: 省选/NOI-
pid: P8879
tag: ['Special Judge', '单调栈']
---
# 『STA - R1』Crossnews
## 题目背景

Informational problems make us better.
## 题目描述

定义两个序列 $\{a_n\}$，$\{b_n\}$ 的联合权值为
$$\operatorname{unval}(a,b)=\sum_{i=1}^nb_i(b_i-a_i)$$

现给定一个序列 $\{a_n\}$，求满足 $\operatorname{unval}(a,b)$ 最小的单调不减序列 $\{b\}$，只需输出 $\operatorname{unval}(a,b)$ 的值即可。

注意，$\{b\}$ 中的元素不一定要为整数。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个整数表示 $a_i$。
## 输出格式

一行一个答案。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
```
### 样例输出 #1
```
-13.7500000
```
### 样例输入 #2
```
10
1000 1 2 8 9 5 4 1000 -40 1000
```
### 样例输出 #2
```
-403015.7500000
```
## 提示

提示：如果你不会做这道题，可以问问 [APJifengc](/user/279652)。
***

样例 1 解释：使得联合权值取到最小值的 $\{b\}$ 为 `0.5 1 1.5 2 2.5`。

***
数据范围和约定：
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}\\\hline
\textsf{1} & 100 & 10 & \textbf{无} \\\hline
\textsf{2} & 10^6 & 5 & \{a\}\textbf{ 全部相等} \\\hline
\textsf{3} & 10^6 & 5 & \{a\}\textbf{ 单调不减} \\\hline
\textsf{4} & 10^4 & 30 & \textbf{无} \\\hline
\textsf{5} & 10^6 & 50 & \textbf{无}
\\\hline\hline
\end{array}
$$

对于全部数据，有 $1\le n\le 10^6$，$|a_i|\le 10^3$。

***

评分规则：

本题使用 Special Judge，如果你的答案是 $pans$，标准答案是 $cans$，则你将获得
$$\min\Bigg\{100,\Bigg\lfloor\dfrac{0.1}{\min\Big\{|pans-cans|,\Big|\dfrac{|pans-cans|}{cans}\Big|\Big\}}\Bigg\rfloor\Bigg\}$$
分。

**每个 Subtask 内捆绑测试**。即取 Subtask 内得分最小的作为 Subtask 得分。


---

---
title: "[BalkanOI 2018] Popa"
layout: "post"
diff: 省选/NOI-
pid: P9507
tag: ['2018', '交互题', 'Special Judge', '栈', '构造', 'BalkanOI（巴尔干半岛）']
---
# [BalkanOI 2018] Popa
## 题目背景

翻译自 BalkanOI 2018 Day2 T2「Popa」

> *"He's an outlaw and he's famous*  
> *Andrii Popa the courageous.*  
> *Day and night he rides,*  
> *He takes his tribute from the main road*  
> *And everywhere in the country*  
> *The thief catchers are running away as fast as they can"*
> 
> *\- ["Andrii Popa", Phoenix](https://music.163.com/song?id=508736536)*
## 题目描述

Ghiță 有一个下标从 $0$ 开始的正整数序列 $S$。因为他是喀尔巴阡的国王，所以他想要构造一个节点编号为 $0,1,\ldots ,N-1$ 的二叉树，满足：

- 树的中序遍历按节点编号升序排列。二叉树的中序遍历由以根的左子节点（如果存在）为根形成的子树的中序遍历，根的节点编号和以根的右子节点（如果存在）为根形成的子树的中序遍历顺次连接组成。  
- 如果 $x$ 是 $y$ 节点的父亲，那么 $S_x$ 整除 $S_y$。

二叉树是一种树形结构，每个节点最多有两个子节点，分别称为左子节点和右子节点。

不幸的是，著名的亡命之徒 Andrii Popa 偷走了序列 $S$，Ghiță 不能直接获取到。但对于任意两个连续的子序列 $[a,b]$ 和 $[c,d]$，他可以使用最先进的技术（他的手机）求出 $\gcd[a,b]$ 是否等于 $\gcd [c,d]$，其中 $\gcd[x,y]$ 指 $S_x,S_{x+1},S_{x+2},\ldots ,S_y$ 的最大公因数。不幸的是，这项技术十分昂贵——如果 Ghiță 使用超过 $Q$ 次，他将会支付一大笔罚金。请帮他在使用这项技术最多 $Q$ 次的情况下构建出他想要的树。保证这是可能的。任何合法的构建方案都可以被接受。

### 交互

本题只支持 C++ 语言使用函数交互。选手代码并不需要也不能包含 `popa.h`。

选手需实现如下函数：

```cpp
int solve(int N, int* Left, int* Right);
```

函数需返回树的根节点，并且将 `Left[i]` 和 `Right[i]` 分别赋值为 $i$ 的左子节点和右子节点。如果节点 $i$ 没有左子节点，则 `Left[i]` 应被赋为 $-1$，如果节点 $i$ 没有右子节点，则 `Right[i]` 应被赋为 $-1$。`Left` 和 `Right` 分别指向两个空间已被分配好且长度恰好为 $N$ 的数组。

函数 `solve` 在一次运行中会被调用最多 $5$ 次。我们建议谨慎使用全局变量。

选手可以调用如下函数（注意，选手须在代码中声明此函数）：

```cpp
int query(int a, int b, int c, int d);
```

这个函数当且仅当 $\gcd[a,b]=\gcd[c,d]$ 时返回 $1$，其中 $0\le a\le b<n,0\le c\le d<N$，否则返回 $0$。


### 样例

例如 $S=[12, 4, 16, 2, 2, 20]$，一组交互过程如下：

| 调用 `solve` | 调用 `query` | 调用 `solve` 之后 |
| :-----------: | :-----------: | :-----------: |
| `solve(6, Left, Right)` |  |  |
|  | `query(0, 1, 3, 5)` 返回 $0$ |  |
|  | `query(4, 5, 1, 3)` 返回 $1$ |  |
|  |  | `solve` 返回值为 $3$；`Left` 指向 $[-1, 0, -1, 1, -1, -1]$；`Right` 指向 $[-1, 2, -1, 4, 5, -1]$ |

样例中，Ghiță 国王想要的树形态如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/y5whph6a.png)

## 输入格式

见「交互」。


## 输出格式

见「交互」。


## 提示

### 数据范围

| 子任务编号 | 限制 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $N=100,Q=10^4$ | $37$ |
| $2$ | $N=10^3,Q=2\times 10^4$ | $24$ |
| $3$ | $N=10^3,Q=2\times 10^3$ | $39$ |



---

---
title: "「Cfz Round 1」Wqs Game"
layout: "post"
diff: 省选/NOI-
pid: P9580
tag: ['树状数组', '洛谷原创', 'O2优化', '线性基', '洛谷月赛', '单调栈']
---
# 「Cfz Round 1」Wqs Game
## 题目背景

『博』和『奕』喜欢博弈，尤其喜欢 wqs 带权博弈。
## 题目描述

wqs 带权博弈在一个数列 $\{a_i\}$ 上进行，对应有一个 $01$ 串 $\{b_i\}$。

1. 若 $b_i=0$，则 $a_i$ 这个数字是属于『博』的；
2. 若 $b_i=1$，则 $a_i$ 这个数字是属于『奕』的。

游戏规则是，每次给定一个区间 $[l,r]$，从 $a_l$ 到 $a_r$，拥有这个数的人**依次**决定选该数或者不选，两个人都会采用**最优策略**。

因为『博』很强大，她会让着『奕』，于是博弈的规则是，如果最后两个人选的数**按位异或和不为零**，则『奕』获胜，否则『博』获胜。

注意每个人**能看到**对方的选数情况，可以选**多个**数（只要这个数是自己的），最后计算两个人选数的总**异或**和。

对于任意区间 $[l,r]$，若『奕』获胜，则 $w(l,r)=1$，否则 $w(l,r)=0$。

每次查询 $\sum\limits_{l=L}^R\sum\limits_{r=l}^Rw(l,r)$ 的值，对 $2^{32}$ 取模。

由于输入输出量过大，对于 $tp\ne 0$ 的测试点，选手需要自行生成数列 $a_i$ 和询问区间 $[L,R]$，并用特殊方式输出答案。

注意正解**不依赖**特殊的输入输出方式。
## 输入格式

第一行三个正整数 $n,q,tp$，表示数列长度，天数以及每天局数，以及读入方式。

第二行一个长度为 $n$ 的字符串，表示 $01$ 串 $\{b_i\}$；

若 $tp=0$，则第三行 $n$ 个正整数，表示数列 $\{a_i\}$，接下来 $q$ 行，每行两个正整数 $L,R$，表示询问  $\sum\limits_{l=L}^R\sum\limits_{r=l}^Rw(l,r)$ 对 $2^{32}$ 取模的值。

否则，令 `Sd` 初值为 $tp$，`Cnt` 初值为 $0$，先使用函数 `GetA` 依次生成 $a_i$，再使用函数 `GetLR` 依次生成 $L,R$，具体方式以代码形式后附。
## 输出格式

若 $tp=0$ 则输出 $q$ 行，每行一个正整数，表示该询问的答案。

否则，令 $ans_i$ 为第 $i$ 次询问的答案，你需要输出 $(ans_i\times i)\bmod 2^{32}$ 的**按位异或和**。
## 样例

### 样例输入 #1
```
3 2 0
100
3 1 2
1 3
2 3
```
### 样例输出 #1
```
2
0
```
### 样例输入 #2
```
5 2 0
10100
2 7 6 3 5
1 5
2 4
```
### 样例输出 #2
```
8
4
```
### 样例输入 #3
```
20 100 8551679995685981130
11001000000000000000
```
### 样例输出 #3
```
1673
```
## 提示

#### 【样例解释 #1】

只有 $w(1,1)=w(1,2)=1$。

对于区间 $[1,3]$，如果『奕』选第一个数，则『博』选后两个数，否则『博』不选，于是『博』获胜。

注意是从左往右依次选取，『博』在选后两个数之前能够知道『奕』是否选了第一个数。

#### 【样例解释 #2】

只有 $w(1,1)=w(1,2)=w(1,3)=w(1,4)=w(2,3)=w(2,4)=w(3,3)=w(3,4)=1$。

#### 【样例解释 #3】

由于本样例 $tp\ne 0$，所以你需要使用特殊方式输入输出。

#### 【数据范围】

对于所有数据，$1\le n\le5\times10^5,1\le q\le 1.5\times10^6,0<a_i<2^{60},1\le L\le R\le n,0\le tp<2^{64}$。

| 子任务编号 | 分值 |    $n\le$     |     $q\le$      |  $tp$  |  $a_i<$  | 特殊性质 |
| :--------: | :--: | :-----------: | :-------------: | :----: | :------: | :------: |
|    $1$     | $6$  |     $20$      |      $100$      |  $=0$  | $2^{60}$ |    有    |
|    $2$     | $7$  |     $100$     |     $10^3$      |  $=0$  | $2^{10}$ |    有    |
|    $3$     | $8$  |     $700$     |     $10^3$      |  $=0$  | $2^{10}$ |    无    |
|    $4$     | $9$  |    $3000$     |     $10^5$      |  $=0$  | $2^{60}$ |    无    |
|    $5$     | $14$ | $3\times10^4$ |     $10^5$      |  $=0$  | $2^{20}$ |    无    |
|    $6$     | $17$ | $2\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $7$     | $19$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $8$     | $20$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    无    |

特殊性质：序列 $b_i$ 中最多有 $10$ 个 $0$。

#### 【备注】

数据生成方式：

```cpp
using ul=unsigned long long;
using ui=unsigned int;
ui Ans,ans;
ul Sd,Cnt;
ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
void GetA(ul &a){a=Rd()%((1ull<<60)-2)+1;}
void GetLR(int &l,int &r){
    l=Rd()%n+1,r=Rd()%n+1;
    if(l>r)swap(l,r);
}
int main(){
    //read n,q,tp,b[i]
    if(tp){
        Sd=tp,Cnt=0;
        for(int i=1;i<=n;++i)GetA(a[i]);
        for(int qi=1;qi<=q;++qi){
            GetLR(l,r);
            //sol
            Ans^=ans*qi;
        }
        printf("%u\n",Ans);
	}
}
```


---

---
title: "[CERC2019] Be Geeks!"
layout: "post"
diff: 省选/NOI-
pid: P9607
tag: ['2019', '线段树', '倍增', 'ST 表', 'ICPC', '笛卡尔树', '单调栈']
---
# [CERC2019] Be Geeks!
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Be Geeks!](https://contest.felk.cvut.cz/19cerc/solved/begeeks.pdf)」**
## 题目描述

音乐乐队 Be Geeks! 的名字并非偶然，因为所有成员都是真正的数学怪才。除此之外，他们喜欢研究数列的各种性质。下面是他们感兴趣的一个例子：
- 设 $A$ 是一个非空正整数序列，$A=(a_1, a_2, \dots, a_N)$。
- $G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N$。
- $F(A)=\sum P(i, j)[1\le i\le j\le N]$。

给出一个序列 $A$，你需要求出 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 2\times 10^5)$，代表序列 $A$ 的长度。

第二行包含 $N$ 个整数 $a_1, a_2, \dots, a_N\ (1\le a_i\le 10^9)$，代表序列 $A$。
## 输出格式

输出一个整数，代表 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 样例

### 样例输入 #1
```
4
1 2 3 4

```
### 样例输出 #1
```
50

```
### 样例输入 #2
```
5
2 4 6 12 3

```
### 样例输出 #2
```
457

```


---

