---
title: "[USACO24FEB] Milk Exchange G"
layout: "post"
diff: 提高+/省选-
pid: P10194
tag: ['USACO', '2024', 'O2优化', '前缀和', '差分', '单调栈']
---
# [USACO24FEB] Milk Exchange G
## 题目描述

Farmer John 的 $N$（$1\le N \le 5\cdot 10^5$）头奶牛排成一圈。第 $i$ 头奶牛有一个容量为整数 $a_i$（$1\le a_i\le 10^9$）升的桶。所有桶初始时都是满的。

每一分钟，对于 $1\le i<N$，奶牛 $i$ 会将其桶中所有牛奶传递给奶牛 $i+1$，奶牛 $N$ 将其牛奶传递给奶牛 $1$。所有交换同时发生（即，如果一头奶牛的桶是满的，送出 $x$ 升牛奶同时收到 $x$ 升，则她的牛奶量保持不变）。如果此时一头奶牛的牛奶量超过 $a_i$，则多余的牛奶会损失。

在 $1,2,\ldots,N$ 的每一分钟后，所有奶牛总共还余下多少牛奶？ 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\ldots,a_N$。
## 输出格式

输出 $N$ 行，其中第 $i$ 行包含 $i$ 分钟后所有奶牛总共余下的牛奶量。
## 样例

### 样例输入 #1
```
6
2 2 2 1 2 1
```
### 样例输出 #1
```
8
7
6
6
6
6
```
### 样例输入 #2
```
8
3 8 6 4 8 3 8 1
```
### 样例输出 #2
```
25
20
17
14
12
10
8
8
```
### 样例输入 #3
```
10
9 9 10 10 6 8 2 1000000000 1000000000 1000000000
```
### 样例输出 #3
```
2000000053
1000000054
56
49
42
35
28
24
20
20
```
## 提示

### 样例解释 1

最初，每个桶中的牛奶量为 $[2,2,2,1,2,1]$。

- $1$ 分钟后，每个桶中的牛奶量为 $[1,2,2,1,1,1]$，因此总牛奶量为 $8$。
- $2$ 分钟后，每个桶中的牛奶量为 $[1,1,2,1,1,1]$，因此总牛奶量为 $7$。
- $3$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $4$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $5$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $6$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。

### 样例解释 2

$1$ 分钟后，每个桶中的牛奶量为 $[1,3,6,4,4,3,3,1]$，因此总牛奶量为 $25$。

### 测试点性质

- 测试点 $4-5$：$N\le 2000$。
- 测试点 $6-8$：$a_i\le 2$。
- 测试点 $9-13$：所有 $a_i$ 在范围 $[1,10^9]$ 内均匀随机生成。
- 测试点 $14-23$：没有额外限制。


---

---
title: "高效清理"
layout: "post"
diff: 提高+/省选-
pid: P10266
tag: ['前缀和', '差分']
---
# 高效清理
## 题目背景

清理炸弹设计理念图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mjfmevu2.png)
## 题目描述

真寻的房间太大了，但是作为家里蹲，她又懒得打扫，于是美波里发明了一款清理炸弹给真寻使用。

真寻的房间由 $n$ 行 $m$ 列的方砖组成，第 $i$ 行第 $j$ 列的方砖上的灰尘数量为 $a_{i,j}$。

真寻将会使用 $k$ 次清理炸弹，第 $i$ 次她会在第 $x_i$ 行第 $y_i$ 列的方砖上使用能量值为 $p_i$ 的清理炸弹，这将会使 $(x_i,y_i)$ 的灰尘数量减少 ${p_i}^2$，$(x_i,y_i)$ 外围第一圈的方砖上的灰尘数量减少 $(p_i-1)^2$，外围第二圈的方砖上的灰尘数量减少 $(p_i-2)^2$ $\cdots$ 外围第 $(p_i-1)$ 圈的方砖上的灰尘数量减少 $1$。

当然，灰尘数量不能为负数，所以若某次操作前，某块方砖上的灰尘数量小于它将要减少的灰尘数量，那么它的灰尘数量将变为 $0$。

请你输出真寻使用完 $k$ 次清理炸弹后，每块方砖上的灰尘数量。
## 输入格式

第一行三个整数 $n,m,k$，分别表示方砖行数、列数及操作次数；

接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示 $a_{i,j}$，描述每一块方砖上的灰尘数量；

接下来 $k$ 行，第 $i$ 行三个整数 $x_i,y_i,p_i$，描述一次操作。
## 输出格式

共 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示方砖 $(i,j)$ 上最终的灰尘数量。
## 样例

### 样例输入 #1
```
4 5 2
7 5 4 6 5
2 4 7 9 5
6 4 5 3 5
1 2 3 0 7
2 4 2
3 3 2
```
### 样例输出 #1
```
7 5 3 5 4
2 3 5 4 4
6 3 0 1 4
1 1 2 0 7
```
### 样例输入 #2
```
6 7 3
6 4 7 8 4 6 1
4 5 4 6 7 5 9
1 4 3 0 7 1 3
4 6 0 7 9 0 0
1 2 3 4 4 5 8
4 7 6 8 7 4 9
5 5 3
2 3 4
3 6 2
```
### 样例输出 #2
```
2 0 0 0 0 5 1 
0 0 0 0 2 3 8 
0 0 0 0 1 0 1 
0 2 0 0 0 0 0 
0 1 1 0 0 0 7 
4 7 5 4 3 0 8 
```
## 提示

**样例** $\mathbf{1}$ **解释**

第一次操作在方砖 $(2,4)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(2,4)$ 的灰尘数量减少 $4$，$(1,3),(1,4),(1,5),(2,3),(2,5),(3,3),(3,4),(3,5)$ 的灰尘数量减少 $1$；

第二次操作在方砖 $(3,3)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(3,3)$ 的灰尘数量减少 $4$，$(2,2),(2,3),(2,4),(3,2),(3,4),(4,2),(4,3),(4,4)$ 的灰尘数量减少 $1$。

**数据范围**

对于所有数据，$1\leq n,m,p_i\leq 10^3$，$1\leq k\leq 10^6$，$0\leq a_{i,j}\leq 10^{12}$，$1\leq x_i\leq n$，$1\leq y_i\leq m$。

本题共 $11$ 个数据点，**采用捆绑测试**，子任务及数据点分配如下：

| 子任务编号 | 数据点编号 | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $0$ | $1\sim 4$ | $n,m,k\leq 300$ | $10$ |
| $1$ | $5$ | $p_i\leq 3$ | $10$ |
| $2$ | $6\sim 7$ | $k\leq 10^3$ | $20$ |
| $3$ | $8\sim 9$ | $n,m\leq 300$ | $20$ |
| $4$ | $10\sim 11$ | 无特殊限制 | $40$ |


---

---
title: "[USACO24OPEN] Painting Fence Posts S"
layout: "post"
diff: 提高+/省选-
pid: P10278
tag: ['USACO', '2024', '图论建模', '差分']
---
# [USACO24OPEN] Painting Fence Posts S
## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**
## 题目描述

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^5$）每头都喜欢日常沿围着牧场的栅栏散步。不幸的是，每当一头奶牛走过栅栏柱子时，她就会碰到它，这要求 Farmer John 需要定期重新粉刷栅栏柱子。

栅栏由 $P$ 根柱子组成（$4\le P\le 2\cdot 10^5$，$P$ 为偶数），每根柱子的位置是 FJ 农场地图上的一个不同的二维坐标点 $(x,y)$（$0\le x,y\le 10^9$）。每根柱子通过垂直或水平线段的栅栏连接到两根相邻的柱子，因此整个栅栏可以被视为各边平行于 $x$ 轴或 $y$ 轴的一个多边形（最后一根柱子连回第一根柱子，确保围栏形成一个包围牧场的闭环）。栅栏多边形是「规则的」，体现在栅栏段仅可能在其端点处重合，每根柱子恰好属于两个栅栏段，同时每两个在端点处相交的栅栏段都是垂直的。

每头奶牛的日常散步都有一个偏好的起始和结束位置，均为沿栅栏的某个点（可能在柱子处，也可能不在）。每头奶牛日常散步时沿着栅栏行走，从起始位置开始，到结束位置结束。由于栅栏形成闭环，奶牛有两条路线可以选择。由于奶牛是一种有点懒的生物，每头奶牛都会选择距离较短的方向沿栅栏行走。值得注意的是，这个选择总是明确的——不存在并列的情况！

一头奶牛会触碰一根栅栏柱子，当她走过这根柱子，或者当这根栅栏柱子是她散步的起点或终点时。请帮助 FJ 计算每个栅栏柱子每天所经历的触碰次数，以便他知道接下来要重新粉刷哪根柱子。

可以证明，给定所有柱子的位置，组成的栅栏仅有唯一的可能性。
## 输入格式

输入的第一行包含 $N$ 和 $P$。以下 $P$ 行的每一行包含两个整数，表示栅栏柱子的位置，没有特定的顺序。以下 $N$ 行的每一行包含四个整数 $x_1\ y_1\ x_2\ y_2$，表示一头奶牛的起始位置 $(x_1,y_1)$ 和结束位置 $(x_2,y_2)$。
## 输出格式

输出 $P$ 个整数，包含每个栅栏柱子所经历的触碰次数。
## 样例

### 样例输入 #1
```
5 4
3 1
1 5
3 5
1 1
2 1 1 5
1 5 3 4
3 1 3 5
2 1 2 1
3 2 3 3
```
### 样例输出 #1
```
1
2
2
1
```
### 样例输入 #2
```
2 8
1 1
1 2
0 2
0 3
0 0
0 1
2 3
2 0
1 1 2 1
1 0 1 3
```
### 样例输出 #2
```
1
0
0
0
1
1
1
2
```
### 样例输入 #3
```
1 12
0 0
2 0
2 1
1 1
1 2
3 2
3 3
1 3
1 4
2 4
2 5
0 5
2 2 0 2
```
### 样例输出 #3
```
1
1
1
1
1
0
0
0
0
0
0
0
```
## 提示

### 样例解释 1

柱子以如下方式由栅栏段连接：

$$
(3,1)\leftrightarrow(3,5)\leftrightarrow(1,5)\leftrightarrow(1,1)\leftrightarrow(3,1)
$$

各奶牛接触的柱子如下：

1. 柱子 $2$ 和 $4$。
2. 柱子 $2$ 和 $3$。
3. 柱子 $1$ 和 $3$。
4. 无。
5. 无。

### 测试点性质

- 测试点 $4-6$：$N,P\le 1000$。
- 测试点 $7-9$：所有位置均有 $0\le x,y\le 1000$。
- 测试点 $10-15$：没有额外限制。


---

---
title: "【MX-J2-T4】Turtle and Cycles"
layout: "post"
diff: 提高+/省选-
pid: P10843
tag: ['二分', 'O2优化', '前缀和', '差分', '双指针 two-pointer', '梦熊比赛']
---
# 【MX-J2-T4】Turtle and Cycles
## 题目背景

原题链接：<https://oier.team/problems/J2E>。
## 题目描述

给你一个环形的 $0 \sim n - 1$ 的**排列** $a_0, a_1, \ldots, a_{n - 1}$。

一次操作你可以选择一个整数 $i \in [0, n - 1]$，把 $a_i$ 赋值成 $a_{(i - 1) \bmod n} + a_{(i + 1) \bmod n} - a_i$。

一个位置 $i \in [0, n - 1]$ 是好的当且仅当 $a_{(i - 1) \bmod n} < a_i$ 且 $a_{(i + 1) \bmod n} < a_i$。

环形序列 $a$ 是好的当且仅当存在**恰好**一个位置 $i \in [0, n - 1]$ 使得位置 $i$ 是好的。

求至少要进行多少次操作能让 $a$ 变成好的。可以证明一定有解。
## 输入格式

**本题有多组测试数据。**

第一行输入一个正整数 $T$，表示测试数据组数。

对于每组测试数据：

第一行包含一个正整数 $n$。

第二行包含 $n$ 个非负整数 $a_0, a_1, \ldots, a_{n - 1}$。
## 输出格式

对于每组数据，输出一行一个整数，表示最少要进行的操作次数。
## 样例

### 样例输入 #1
```
3
2
1 0
5
2 3 0 4 1
10
0 5 9 7 3 1 6 4 8 2

```
### 样例输出 #1
```
0
1
5

```
## 提示

#### 【样例解释】

在第一组数据中，初始序列恰好存在一个好的位置 $i = 0$，所以答案为 $0$。

在第二组数据中，可以选择 $i = 2$ 操作，操作后序列变为 $a = [2, 3, 7, 4, 1]$。此时序列恰好存在一个好的位置 $i = 2$，所以答案为 $1$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $19$ | $6$ | $10^4$ | 无 | 无 |
| $2$ | $14$ | $12$ | $10^4$ | 无 | $1$ |
| $3$ | $27$ | $2 \cdot 10^3$ | $10^4$ | 无 | $1, 2$ |
| $4$ | $2$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | $a_i = i$ | 无 |
| $5$ | $38$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | 无 | $1, 2, 3, 4$ |

对于所有数据，满足 $1 \le T \le 10^4$，$2 \le n, \sum n \le 2 \cdot 10^5$，$0 \le a_i \le n - 1$，$a$ 是一个 $0 \sim n - 1$ 的排列。


---

---
title: "「CZOI-R2」天平"
layout: "post"
diff: 提高+/省选-
pid: P11373
tag: ['平衡树', '数论', 'O2优化', '最大公约数 gcd', '差分', '洛谷比赛']
---
# 「CZOI-R2」天平
## 题目描述

你有 $n$ 个**砝码组**，编号为 $1$ 至 $n$。对于第 $i$ 个**砝码组**中的砝码有共同的正整数质量 $a_i$，每个**砝码组**中的**砝码**数量无限。

其中，有 $q$ 次操作：

- `I x v`：在第 $x$ 个**砝码组**后新增一组单个**砝码**质量为 $v$ 的**砝码组**，当 $x=0$ 时表示在最前面新增；
- `D x`：删除第 $x$ 个**砝码组**；
- `A l r v`：把从 $l$ 到 $r$ 的所有**砝码组**中的砝码质量加 $v$；
- `Q l r v`：判断能否用从 $l$ 到 $r$ 的**砝码组**中的砝码，称出质量 $v$。每个砝码组中的砝码可以使用任意个，也可以不用。

对于操作 `I` 和 `D`，操作后编号以及 $n$ 的值自动变化。

称一些**砝码**可以称出质量 $v$，当且仅当存在将这些砝码分别放在天平两边的摆放方法，使得将 $1$ 个质量为 $v$ 的物体摆放在某边可以让天平平衡。
## 输入格式

第一行输入 $2$ 个整数 $n,q$。

第二行输入 $n$ 个整数，第 $i$ 个整数为 $a_i$。

接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个 `Q` 操作，输出一行 `YES` 或者 `NO`，表示能否称出重量 $v$。
## 样例

### 样例输入 #1
```
5 5
1 10 8 4 2
I 2 1
A 1 4 4
A 2 4 4
D 5
Q 1 4 4
```
### 样例输出 #1
```
YES
```
### 样例输入 #2
```
10 10
2 2 1 4 2 10 8 7 10 6
Q 5 6 1
Q 5 7 7
I 5 1
Q 4 5 3
Q 2 9 2
A 3 5 1
Q 7 8 5
D 7
A 3 9 7
Q 3 7 6
```
### 样例输出 #2
```
NO
NO
NO
YES
NO
YES
```
## 提示

**【样例解释】**

对于样例组 $1$，最后有 $5$ 个中的**砝码组**，质量分别为 $5,18,9,16,2$。在天平左边放上 $1$ 个**砝码组一**中的**砝码**，右边放上 $1$ 个**砝码组三**的砝码，即可称出质量 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/lwd6643t.png)

**【数据范围】**

**本题采用捆绑测试**。

记 $m_1$ 为所有时刻中 $a_i$ 与 $v$ 的最小值，$m_2$ 为所有时刻中 $a_i$ 与 $v$ 的最大值。

- Subtask #1（$5\text{ pts}$）：$1\le n,q\le 10$，$1\le m_1\le m_2 \le50$。
- Subtask #2（$15\text{ pts}$）：$1\le n,q\le 4\times10^2$。
- Subtask #3（$20\text{ pts}$）：没有操作 `I` 与操作 `D`。
- Subtask #4（$60\text{ pts}$）：无特殊性质。

对于 $100\%$ 的数据，$1\le n,q\le 10^5$，$1\le m_1\le m_2\le 10^{18}$，保证所有操作合法，且任意时刻至少存在一个砝码组。


---

---
title: "[RMI 2019] 还原 / Restore Arrays"
layout: "post"
diff: 提高+/省选-
pid: P12088
tag: ['2019', 'Special Judge', '差分约束', 'RMI（罗马尼亚）']
---
# [RMI 2019] 还原 / Restore Arrays
## 题目描述

**本题中下标是 $\texttt{\textcolor{red}{0-indexed}}$ 的。**

构造一个长度为 $n$ 的 $\text{01}$ 串 $a_0\sim a_{n-1}$，满足以下条件：

- $\forall 0\le i\lt m$，都有 $k_i\mathrm{thmin}(a_{l_i},a_{{l_i}+1},\ldots,a_{r_i})=\mathrm{val}_i$。

这里，$k\mathrm{thmin}$ 表示一个数列内第 $k$ 小的元素。
## 输入格式


第一行，两个正整数 $n,m$。

接下来 $m$ 行，第 $i$ 行四个非负整数 $l_{i-1},r_{i-1},k_{i-1},\mathrm{val}_{i-1}$。

## 输出格式


如果有解，直接输出对应的 $01$ 串（元素中间**要**加空格）。

否则输出一行一个 $\texttt{-1}$。

## 样例

### 样例输入 #1
```
4 5
0 1 2 1
0 2 2 0
2 2 1 0
0 1 1 0
1 2 1 0
```
### 样例输出 #1
```
0 1 0 0
```
## 提示


对于 $100\%$ 的数据，保证：

- $1\le n\le 5\times 10^3$；
- $1\le m\le 10^4$；
- $0\le l_i\le r_i\lt n$；
- $1\le k_i\le r_i-l_i+1$；
- $\mathrm{val}_i\in \{0,1\}$。

### 子任务

| 编号 | $n\le$ | $m\le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $18$ | $200$ | / | $7$ |
| $2$ | $5\times 10^3$ | $10^4$ | $\text{A}$| $13$ |
| $3$ | $5\times 10^3$ | $10^4$ | $\text{B}$ | $25$ |
| $4$ | $5\times 10^3$ | $10^4$ | / | $55$ |

- 特殊性质 $\text{A}$：$\forall 0\le i\lt m$，$k_i=1$。
- 特殊性质 $\text{B}$：$\forall 0\le i\lt m$，要么 $k_i=1$，要么 $k_i=r_i-l_i+1$。



---

---
title: "[蓝桥杯 2025 省 A 第二场] 交互"
layout: "post"
diff: 提高+/省选-
pid: P12348
tag: ['2025', '差分约束', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A 第二场] 交互
## 题目描述

小蓝正在做一道交互题。有一个未知的下标从 1 到 $m$ 的数组 $a$，小蓝每次可以进行一次询问 $(l, r, p, q)$，然后交互程序会返回 $ans$ 满足 $\min\limits_{l \leq x \leq r} a[x] - \max\limits_{p \leq y \leq q} a[y] \geq ans$。但小蓝很快就发现，因为 $ans$ 并不是精确的值，所以他永远也无法得到实际的数组元素的值。

给定小蓝的几次询问和交互程序的返回值，请你帮他求出 $\max\limits_{1 \leq x \leq m} a[x] - \min\limits_{1 \leq y \leq m} a[y]$ 的可能的最小值。
## 输入格式

输入的第一行包含两个正整数 $n, m$，用一个空格分隔，分别表示小蓝的询问次数和数组长度。

接下来 $n$ 行，每行包含五个正整数 $l_i, r_i, p_i, q_i, ans_i$，相邻整数之间使用一个空格分隔，表示第 $i$ 次小蓝询问及其结果，含义如问题描述所述。
## 输出格式

输出一行包含一个整数表示答案，即 $\max\limits_{1 \leq x \leq m} a[x] - \min\limits_{1 \leq y \leq m} a[y]$ 的可能的最小值，如果无解请输出 `No Solution`。
## 样例

### 样例输入 #1
```
2 4
1 1 2 2 2
1 2 3 4 2

```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2 2
1 1 2 2 1
2 2 1 1 1
```
### 样例输出 #2
```
No Solution
```
## 提示

### 样例说明

- 对于样例 $1$，$a_1 - a_2 \geq 2$，$\min(a_1, a_2) - \max(a_3, a_4) \geq 2$。所以 $a_1 - a_3 \geq 4$，所以 $a_i$ 之间差值的最大值不会小于 $4$。
- 对于样例 $2$，$a_1 - a_2 \geq 1$，$a_2 - a_1 \geq 1$，这种情况显然是无解的。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$m \leq 300$；
- 对于所有评测用例，$1 \leq n \leq 500$，$1 \leq m \leq 10000$，$-100000 \leq ans_i \leq 100000$，$1 \leq l_i, r_i, p_i, q_i \leq m$，$0 \leq q_i - p_i < 100$，$0 \leq r_i - l_i < 100$。


---

---
title: "Range | Sum | Maximum"
layout: "post"
diff: 提高+/省选-
pid: P12498
tag: ['O2优化', '差分', '单调栈', '洛谷比赛']
---
# Range | Sum | Maximum
## 题目描述

给出一个长度为 $n$ 的序列 $a$，定义一个区间 $[l,r]$ 的权值为 $\max_{l\le L\le R\le r}|\sum_{i=L}^Ra_i|$。

对于 $k=1,2,3,\dots,n$，求所有长度为 $k$ 的区间权值和。
## 输入格式

本题有多组测试数据，第一行输入一个正整数 $T$，代表数据组数。

对于每组数据，第一行输入一个正整数 $n$。

第二行输入 $n$ 个整数，代表序列 $a$。
## 输出格式

为了避免输出量过大，设长度为 $k$ 的区间权值和为 $ans_k$，对于每组测试数据，你只需要输出：

$$\bigoplus_{i=1}^nans_i\bmod i^2$$

（其中 $\oplus$ 表示按位异或运算）

正解做法不依赖于该输出方式。
## 样例

### 样例输入 #1
```
5
3
1 -1 2
7
1 -2 -3 4 5 -6 -7
7
-1 2 3 -4 -5 6 7
4
1 1 2 3
5
1 4 -5 -2 6
```
### 样例输出 #1
```
1
31
31
4
11
```
## 提示

#### 【样例解释】

样例中五组数据的 $ans$ 分别为：
- $\{4,3,2\}$
- $\{28,39,41,36,31,22,13\}$
- $\{28,39,41,36,31,22,13\}$
- $\{7,10,10,7\}$
- $\{18,23,19,14,7\}$

其中，对于第一组数据，各个区间的权值分别如下：

- $[1,1]:1$
- $[2,2]:1$
- $[3,3]:2$
- $[1,2]:1$
- $[2,3]:2$
- $[1,3]:2$

其中，长度为 $1$ 的区间有 $[1,1],[2,2],[3,3]$，权值和为 $4$；长度为 $2$ 的区间有 $[1,2],[2,3]$，权值和为 $3$；长度为 $3$ 的区间有 $[1,3]$，权值和为 $2$。

#### 【数据范围】

对于所有数据，保证：
- $1\le T\le10^4$
- $1\le n,\sum n\le10^6$
- $-10^6\le a_i\le10^6$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $\sum n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $500$ | 无 | $5$ |
| $2$ | $5000$ | 无 | $20$ |
| $3$ | $10^6$ | $a_i\ge 0$ | $25$ |
| $4$ | $3\times10^5$ | 无 | $25$ |
| $5$ | $10^6$ | 无 | $25$ |



---

---
title: "[GCJ 2015 #3] Smoothing Window"
layout: "post"
diff: 提高+/省选-
pid: P13229
tag: ['贪心', '2015', '差分', 'Google Code Jam']
---
# [GCJ 2015 #3] Smoothing Window
## 题目描述

Adamma is a climate scientist interested in temperature. Every minute, she records the current temperature as an integer, creating a long list of integers: $x_{1}, x_{2}, \ldots, x_{\mathrm{N}}$. (Adamma uses her own special temperature scale rather than a familiar one like Celsius or Kelvin, so it's possible for the values to be large and negative!) She often plots these temperatures on her computer screen.

This morning, she decided to compute a sliding average of this list in order to get a smoother plot. She used a smoothing window of size $\mathbf{K}$, which means that she converted the sequence of $\mathbf{N}$ temperatures into a sequence of $(\mathbf{N}-\mathbf{K}+1)$ average temperatures: $s_{1}, s_{2}, \ldots, s_{\mathbf{N}-\mathbf{K}+1}$. Each $s_{i}$ is the average of the values $x_{i}, x_{i+1}, \ldots, x_{i+\mathbf{K}-1}$. The original $x_{i}$ values were all integers, but some of the $s_{i}$ may be fractional.

Unfortunately, Adamma forgot to save the original sequence of temperatures! And now she wants to answer a different question -- what was the difference between the largest temperature and the smallest temperature? In other words, she needs to compute $\max \left\{x_{1}, \ldots, x_{\mathrm{N}}\right\}-\min \left\{x_{1}, \ldots, x_{\mathrm{N}}\right\}$. But she only has $\mathrm{N}, \mathrm{K}$, and the smoothed sequence.

After some thinking, Adamma has realized that this might be impossible because there may be several valid answers. In that case, she wants to know the smallest possible answer among all of the possible original sequences that could have produced her smoothed sequence with the given values of $\mathrm{N}$ and $\mathrm{K}$.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow; each test case consists of two lines. The first line contains integers $\mathrm{N}$ and $\mathbf{K}$ separated by a space character. The second line contains integer values $\operatorname{sum}_{1}, \operatorname{sum}_{2}, \ldots, \operatorname{sum}_{\mathrm{N}-\mathbf{K}+1}$, separated by space characters. $s_{i}$ is given by $\operatorname{sum}_{i} / \mathbf{K}$.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the smallest possible difference between the largest and smallest temperature.
## 样例

### 样例输入 #1
```
3
10 2
1 2 3 4 5 6 7 8 9
100 100
-100
7 3
0 12 0 12 0
```
### 样例输出 #1
```
Case #1: 5
Case #2: 0
Case #3: 12
```
## 提示

**Sample Explanation**

In Case #1, the smoothed sequence is:

$$0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5$$

The integer sequence that gives the smallest difference is:

$$0, 1, 1, 2, 2, 3, 3, 4, 4, 5$$

Note that the sequence:

$$0.5, 0.5, 1.5, 1.5, 2.5, 2.5, 3.5, 3.5, 4.5, 4.5$$

Would give the same smoothed sequence with a maximum difference of $4$, but this is not a valid answer because the original temperatures are known to have been integers.

In Case #2, all we know is that the sum of the $100$ original values was $-100$. It's possible that all of the original values were exactly $-1$, in which case the difference between the largest and smallest temperatures would be $0$, which is as small as differences get!

In Case #3, the original sequence could have been:

$$-4, 8, -4, 8, -4, 8, -4$$

**Sample Explanation**

- $1 \leq \mathrm{T} \leq 100 .$
- $2 \leq \mathbf{K} \leq \mathrm{N} .$
- The $\operatorname{sum}_{i}$ will be integers between -10000 and 10000, inclusive.

**Small dataset(6 Pts)**

- Time limit: ~~240~~ 5 seconds.
- $2 \leq \mathrm{N} \leq 100 .$

**Large dataset(7 Pts)**

- Time limit: ~~480~~ 10 seconds.
- $2 \leq \mathrm{N} \leq 1000 .$
- $2 \leq \mathbf{K} \leq 100 .$


---

---
title: "「WWOI R1」WsW 的田地"
layout: "post"
diff: 提高+/省选-
pid: P13562
tag: ['O2优化', '哈希 hashing', '前缀和', '差分']
---
# 「WWOI R1」WsW 的田地
## 题目背景

WsW 是会开心和生气的。
## 题目描述

WsW 和 bln 分别有一块田地。这两块田地都由 $n\times m$ 个格子组成，其中左上角格子的坐标为 $(1,1)$，右下角格子的坐标为 $(n,m)$。  

最开始，WsW 的田地里坐标为 $(x,y)$ 的格子中长着一株生长度为 $a_{x,y}$ 的禾苗；bln 的田地里坐标为 $(x,y)$ 的格子中长着一株生长度为 $b_{x,y}$ 的禾苗。  

在之后的每一天的开始，都会有一个小精灵在 **WsW 或 bln 的田地**中坐标为 $(x_0,y_0)$ 的格子上使用药水，药水分为三种：

- 药水 $1$，包括 $3$ 个参数，可以使这片田地内满足 $x=x_0$ **或** $y=y_0$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  
- 药水 $2$，包括 $5$ 个参数，可以使这片田地内满足 $x_0\le x\le x_0+u$ 且 $y_0\le y\le y_0+v$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  
- 药水 $3$，包括 $5$ 个参数，可以使这片田地内满足 $x_0\le x\le x_0+u$ 且 $y_0+x-x_0\le y\le y_0+x-x_0+v$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  

药水不会影响田地外的区域。  
**药水瞬间生效，且效果在一天结束后不会消失。**  

小精灵使用药水后，WsW 会查看自己和 bln 的田地。如果 WsW 的田地与 bln 的田地坐标相同的格子中禾苗的生长度都相等，那么 WsW 将会很开心；否则 WsW 会很生气。  


## 输入格式

第一行输入两个整数 $n,m$，表示田地的大小。  

接下来 $n$ 行，每行 $m$ 个数，表示最开始 WsW 田地格子中禾苗的生长度。  
接下来 $n$ 行，每行 $m$ 个数，表示最开始 bln 田地格子中禾苗的生长度。  

接下来一行一个正整数 $q$，表示共有 $q$ 天。  

接下来 $q$ 行，每行表示使用一次药水。首先读入两个整数 $t,f$。其中 $t$ 表示使用的药水类型，若 $f=0$ 表示对 WsW 的田地使用药水，若 $f=1$ 表示对 bln 的田地使用药水，接下来：

- 若 $t=1$，表示使用药水 $1$。接着输入 $3$ 个整数 $x_0,y_0,k$。  
- 若 $t=2$，表示使用药水 $2$。接着输入 $5$ 个整数 $x_0,y_0,k,u,v$。 
- 若 $t=3$，表示使用药水 $3$。接着输入 $5$ 个整数 $x_0,y_0,k,u,v$。
## 输出格式

输出共 $q$ 行，表示每天使用药水后 WsW 的心情。  
若 WsW 很开心，输出 `Happy`；若 WsW 很生气，输出 `Angry`。
## 样例

### 样例输入 #1
```
2 3
1 1 4
5 1 4
0 0 3
5 0 4
5
1 1 1 2 1
1 0 1 1 4
1 1 1 3 4
2 1 2 1 4 0 1
2 0 2 2 4 0 1
```
### 样例输出 #1
```
Happy
Angry
Angry
Angry
Happy
```
### 样例输入 #2
```
3 3
1 9 1
9 8 1
3 0 5
3 11 1
9 10 3
3 0 5
1
3 1 1 1 -2 1 1
```
### 样例输出 #2
```
Happy
```
## 提示

### 【样例 1 解释】
红色数字表示当天发生改变的格子中的生长值。  
![](https://cdn.luogu.com.cn/upload/image_hosting/xpcmfh4l.png)

可以发现，只有第 $1$ 天和第 $5$ 天两块田地中对应格子的生长值相同。

### 【数据范围】

**本题采用捆绑测试**。

对于所有测试数据，保证:
* $1\le n,m\le 800$，$1\le q\le 5\times 10^5$。
* 对于所有 $a_{x,y},b_{x,y}$，均有 $|a_{x,y}|,|b_{x,y}|\le 5\times 10^5$。
* $t\in \{1,2,3\}$，$f\in \{0,1\}$。
* $1\le x_0\le n$，$1\le y_0\le m$，$|k| \le 5\times 10^5$，$0\le u\le n$，$0\le v\le m$。  

|子任务编号|$n,m\le$|$q\le$| $\lvert a_{i,j}\rvert,\lvert b_{i,j}\rvert,\lvert k\rvert\le$ |特殊限制|分数|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$| $100$ | $100$ | $100$ |保证没有 $t=3$ 的情况|$10$|
|$2$| ^ | ^ | ^ | 无 |$20$|
|$3$| $800$ | $5\times10^5$ | $5\times10^5$ |保证没有 $t=3$ 的情况|$30$|
|$4$| ^ | ^ | ^ | 无 |$40$|


---

---
title: "[USACO12DEC] Running Away From the Barn G"
layout: "post"
diff: 提高+/省选-
pid: P3066
tag: ['2012', 'USACO', 'O2优化', '差分']
---
# [USACO12DEC] Running Away From the Barn G
## 题目描述

给定一颗 $n$ 个点的有根树，边有边权，节点从 $1$ 至 $n$ 编号，$1$ 号节点是这棵树的根。

再给出一个参数 $t$，对于树上的每个节点 $u$，请求出 $u$ 的子树中有多少节点满足该节点到 $u$ 的距离不大于 $t$。
## 输入格式

输入的第一行是两个整数，分别表示节点数 $n$ 和给出的参数 $t$。

第 $2$ 到第 $n$ 行，每行两个整数，第 $i$ 行的整数 $p_i, w_i$ 表示节点 $i$ 的父节点为 $p_i$，连结 $i$ 与 $p_i$ 的边的边权为 $w_i$。
## 输出格式

输出 $n$ 行，每行一个整数，第 $i$ 行的整数表示 $i$ 的子树内到 $i$ 的距离不大于 $t$ 的节点个数。
## 样例

### 样例输入 #1
```
4 5 
1 4 
2 3 
1 5 

```
### 样例输出 #1
```
3 
2 
1 
1 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 2 \times 10^5$，$1 \leq t \leq 10^{18}$。
- $1 \leq p_i \lt i$，$1 \leq w_i \leq 10^{12}$。




---

---
title: "[SCOI2011] 糖果"
layout: "post"
diff: 提高+/省选-
pid: P3275
tag: ['2011', '四川', '各省省选', '最短路', '差分约束']
---
# [SCOI2011] 糖果
## 题目描述

幼儿园里有 $N$ 个小朋友，$\text{lxhgww}$ 老师现在想要给这些小朋友们分配糖果，要求每个小朋友都要分到糖果。但是小朋友们也有嫉妒心，总是会提出一些要求，比如小明不希望小红分到的糖果比他的多，于是在分配糖果的时候，$\text{lxhgww}$ 需要满足小朋友们的 $K$ 个要求。幼儿园的糖果总是有限的，$\text{lxhgww}$ 想知道他至少需要准备多少个糖果，才能使得每个小朋友都能够分到糖果，并且满足小朋友们所有的要求。
## 输入格式

输入的第一行是两个整数 $N$，$K$。接下来 $K$ 行，表示这些点需要满足的关系，每行 $3$ 个数字，$X$，$A$，$B$。

+ 如果 $X=1$， 表示第 $A$ 个小朋友分到的糖果必须和第 $B$ 个小朋友分到的糖果一样多；
+ 如果 $X=2$， 表示第 $A$ 个小朋友分到的糖果必须少于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=3$， 表示第 $A$ 个小朋友分到的糖果必须不少于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=4$， 表示第 $A$ 个小朋友分到的糖果必须多于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=5$， 表示第 $A$ 个小朋友分到的糖果必须不多于第 $B$ 个小朋友分到的糖果；
## 输出格式

输出一行，表示 $\text{lxhgww}$ 老师至少需要准备的糖果数，如果不能满足小朋友们的所有要求，就输出 $-1$。
## 样例

### 样例输入 #1
```
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1
```
### 样例输出 #1
```
11
```
## 提示

对于 $30\%$ 的数据，保证 $N\leq100$

对于 $100\%$ 的数据，保证 $N\leq100000$

对于所有的数据，保证 $K\leq100000, 1\leq X\leq5, 1\leq A, B\leq N$

---

$\text{upd 2022.7.6}$：新添加 $21$ 组 [Hack 数据](https://www.luogu.com.cn/discuss/454051)。


---

---
title: "[APIO/CTSC2007] 数据备份"
layout: "post"
diff: 提高+/省选-
pid: P3620
tag: ['贪心', '2007', 'APIO', '优先队列', '差分', 'CTSC/CTS']
---
# [APIO/CTSC2007] 数据备份
## 题目描述

你在一家 IT 公司为大型写字楼或办公楼的计算机数据做备份。然而数据备份的工作是枯燥乏味的，因此你想设计一个系统让不同的办公楼彼此之间互相备份，而你则坐在家中尽享计算机游戏的乐趣。

已知办公楼都位于同一条街上。你决定给这些办公楼配对（两个一组）。每一对办公楼可以通过在这两个建筑物之间铺设网络电缆使得它们可以互相备份。

然而，网络电缆的费用很高。当地电信公司仅能为你提供 $K$ 条网络电缆，这意味着你仅能为 $K$ 对办公楼（或总计 $2K$ 个办公楼）安排备份。任一个办公楼都属于唯一的配对组（换句话说，这 $2K$ 个办公楼一定是相异的）。

此外，电信公司需按网络电缆的长度（公里数）收费。因而，你需要选择这 $K$ 对办公楼使得电缆的总长度尽可能短。换句话说，你需要选择这 $K$ 对办公楼，使得每一对办公楼之间的距离之和（总距离）尽可能小。

下面给出一个示例，假定你有 $5$ 个客户，其办公楼都在一条街上，如下图所示。这 $5$ 个办公楼分别位于距离大街起点 $1\rm km$, $3\rm km$, $4\rm km$, $6\rm km$ 和 $12\rm km$ 处。电信公司仅为你提供 $K=2$ 条电缆。

  ![](https://cdn.luogu.com.cn/upload/pic/4386.png) 

上例中最好的配对方案是将第 $1$ 个和第 $2$ 个办公楼相连，第 $3$ 个和第 $4$ 个办公楼相连。这样可按要求使用 $K=2$ 条电缆。第 $1$ 条电缆的长度是 $\rm 3km-1km = 2km$，第 2 条电缆的长度是 $\rm 6km―4km = 2 km$。这种配对方案需要总长 $4\rm km$ 的网络电缆，满足距离之和最小的要求。
## 输入格式

输入文件的第一行包含整数 $N$ 和 $K$，其中 $N$（$1\leq N \leq 10^5$）表示办公楼的数目，$K$（$\displaystyle 1\leq K \leq \frac{N}{2}$）表示可利用的网络电缆的数目。

接下来的 $N$ 行每行仅包含一个整数 $s$（$0\leq s \leq 10^9$）, 表示每个办公楼到大街起点处的距离。这些整数将按照从小到大的顺序依次出现。
## 输出格式

输出文件应当由一个正整数组成，给出将 $2K$ 个相异的办公楼连成 $K$ 对所需的网络电缆的最小总长度。
## 样例

### 样例输入 #1
```
5 2 
1 
3 
4 
6 
12 
```
### 样例输出 #1
```
4
```
## 提示

$30\%$ 的输入数据满足 $N\leq 20$。

$60\%$ 的输入数据满足 $N\leq 10^4$。


---

---
title: "[USACO17OPEN] Modern Art P"
layout: "post"
diff: 提高+/省选-
pid: P3664
tag: ['2017', 'USACO', '前缀和', '差分']
---
# [USACO17OPEN] Modern Art P
## 题目描述

Art critics worldwide have only recently begun to recognize the creative genius behind the great bovine painter, Picowso.


Picowso paints in a very particular way. She starts with an $N \times N$ blank canvas, represented by an $N \times N$ grid of zeros, where a zero indicates an empty cell of the canvas. She then draws $N^2$ rectangles on the canvas, one in each of $N^2$ colors (conveniently numbered $1 \ldots N^2$). For example, she might start by painting a rectangle in color 2, giving this intermediate canvas:


```
2 2 2 0

2 2 2 0

2 2 2 0

0 0 0 0
```




She might then paint a rectangle in color 7:

```
2 2 2 0

2 7 7 7

2 7 7 7

0 0 0 0
```




And then she might paint a small rectangle in color 3:

```
2 2 3 0

2 7 3 7

2 7 7 7

0 0 0 0
```


Each rectangle has sides parallel to the edges of the canvas, and a rectangle could be as large as the entire canvas or as small as a single cell. Each color from $1 \ldots N^2$ is used exactly once, although later colors might completely cover up some of the earlier colors.


Given the final state of the canvas, please count how many of the $N^2$ colors could have possibly been the first to be painted.
## 输入格式

The first line of input contains $N$, the size of the canvas ($1 \leq N \leq 1000$).

The next $N$ lines describe the final picture of the canvas, each containing $N$ integers that are in the range $0 \ldots N^2$. The input is guaranteed to have been drawn as described above, by painting successive rectangles in different colors.

## 输出格式

Please output a count of the number of colors that could have been drawn first.

## 样例

### 样例输入 #1
```
4
2 2 3 0
2 7 3 7
2 7 7 7
0 0 0 0
```
### 样例输出 #1
```
14
```
## 提示

In this example, color 2 could have been the first to be painted. Color 3 clearly had to have been painted after color 7, and color 7 clearly had to have been painted after color 2. Since we don't see the other colors, we deduce that they also could have been painted first.
## 题目翻译

### 题目描述

世界各地的艺术评论家最近才开始认识到伟大的奶牛画家 Picowso 的创作天才。

Picowso 以一种非常独特的方式作画。她从一个 $N \times N$ 的空白画布开始，画布用一个 $N \times N$ 的零网格表示，其中零表示画布的一个空单元格。然后她在画布上绘制 $N^2$ 个矩形，每个矩形使用 $N^2$ 种颜色中的一种（方便地用编号 $1 \ldots N^2$ 标识）。例如，她可能首先用颜色 2 绘制一个矩形，得到以下中间画布：

```
2 2 2 0

2 2 2 0

2 2 2 0

0 0 0 0
```

然后她可能用颜色 7 绘制一个矩形：

```
2 2 2 0

2 7 7 7

2 7 7 7

0 0 0 0
```

接着她可能用颜色 3 绘制一个小矩形：

```
2 2 3 0

2 7 3 7

2 7 7 7

0 0 0 0
```

每个矩形的边都与画布的边缘平行，矩形可以大到整个画布，也可以小到一个单元格。每种颜色从 $1 \ldots N^2$ 恰好使用一次，尽管后来的颜色可能会完全覆盖一些先前的颜色。

给定画布的最终状态，请计算有多少种颜色可能是第一个被绘制的。

### 输入格式

输入的第一行包含 $N$，表示画布的大小（$1 \leq N \leq 1000$）。

接下来的 $N$ 行描述画布的最终状态，每行包含 $N$ 个整数，范围在 $0 \ldots N^2$。输入保证是按照上述方式通过连续绘制不同颜色的矩形生成的。

### 输出格式

请输出可能是第一个被绘制的颜色的数量。

### 说明/提示

在这个例子中，颜色 2 可能是第一个被绘制的。颜色 3 显然必须在颜色 7 之后绘制，而颜色 7 显然必须在颜色 2 之后绘制。由于我们没有看到其他颜色，我们推断它们也可能是第一个被绘制的。


---

---
title: "[USACO18FEB] Teleportation S"
layout: "post"
diff: 提高+/省选-
pid: P4264
tag: ['数学', '2018', 'USACO', '枚举', '差分']
---
# [USACO18FEB] Teleportation S
## 题目描述

One of the farming chores Farmer John dislikes the most is hauling around lots of cow manure. In order to streamline this process, he comes up with a brilliant invention: the manure teleporter! Instead of hauling manure between two points in a cart behind his tractor, he can use the manure teleporter to instantly transport manure from one location to another.
Farmer John's farm is built along a single long straight road, so any location on his farm can be described simply using its position along this road (effectively a point on the number line). A teleporter is described by two numbers $x$ and $y$, where manure brought to location $x$ can be instantly transported to location $y$.

Farmer John decides to build a teleporter with the first endpoint located at $x=0$; your task is to help him determine the best choice for the other endpoint $y$. In particular, there are $N$ piles of manure on his farm ($1 \leq N \leq 100,000$). The $i$th pile needs to moved from position $a_i$ to position $b_i$, and Farmer John transports each pile separately from the others. If we let $d_i$ denote the amount of distance FJ drives with manure in his tractor hauling the $i$th pile, then it is possible that $d_i = |a_i-b_i|$ if he hauls the $i$th pile directly with the tractor, or that $d_i$ could potentially be less if he uses the teleporter (e.g., by hauling with his tractor from $a_i$ to $x$, then from $y$ to $b_i$).

Please help FJ determine the minimum possible sum of the $d_i$'s he can achieve by building the other endpoint $y$ of the teleporter in a carefully-chosen optimal position. The same position $y$ is used during transport of every pile.
## 输入格式

The first line of input contains $N$. In the $N$ lines that follow, the $i$th line contains $a_i$ and $b_i$, each an integer in the range $-10^8 \ldots 10^8$. These values are not necessarily all distinct.
## 输出格式

Print a single number giving the minimum sum of $d_i$'s FJ can achieve. Note that this number might be too large to fit into a standard 32-bit integer, so you may need to use large integer data types like a "long long" in C/C++. Also you may want to consider whether the answer is necessarily an integer or not...
## 样例

### 样例输入 #1
```
3
-5 -7
-3 10
-2 7
```
### 样例输出 #1
```
10

```
## 提示

In this example, by setting $y = 8$ FJ can achieve $d_1 = 2$, $d_2 = 5$, and $d_3 = 3$. Note that any value of $y$ in the range $[7,10]$ would also yield an optimal solution.

Problem credits: Brian Dean
## 题目翻译

### 题目描述

Farmer John 最不喜欢的农活之一就是到处搬运牛粪。为了简化这一过程，他发明了一个绝妙的装置：牛粪传送器！与其用拖拉机后面的拖车搬运牛粪，他可以使用牛粪传送器将牛粪从一个位置瞬间传送到另一个位置。

Farmer John 的农场建在一条笔直的长路上，因此农场上的任何位置都可以简单地用其在这条路上的位置来描述（实际上就是数轴上的一个点）。传送器由两个数字 $x$ 和 $y$ 描述，其中被带到位置 $x$ 的牛粪可以瞬间传送到位置 $y$。

Farmer John 决定建造一个传送器，其第一个端点位于 $x = 0$；你的任务是帮助他确定另一个端点 $y$ 的最佳选择。特别地，农场上有 $N$ 堆牛粪（$1 \leq N \leq 100,000$）。第 $i$ 堆牛粪需要从位置 $a_i$ 搬运到位置 $b_i$，Farmer John 会分别搬运每一堆牛粪。如果我们用 $d_i$ 表示 Farmer John 搬运第 $i$ 堆牛粪时拖拉机行驶的距离，那么如果他直接用拖拉机搬运第 $i$ 堆牛粪，则 $d_i = |a_i - b_i|$；如果他使用传送器，则 $d_i$ 可能会更小（例如，通过用拖拉机从 $a_i$ 运到 $x$，然后从 $y$ 运到 $b_i$）。

请帮助 Farmer John 确定通过将传送器的另一个端点 $y$ 建在一个精心选择的最优位置，可以实现的最小 $d_i$ 总和。搬运每堆牛粪时使用相同的 $y$ 位置。

### 输入格式

输入的第一行包含 $N$。接下来的 $N$ 行中，第 $i$ 行包含 $a_i$ 和 $b_i$，每个整数的范围在 $-10^8 \ldots 10^8$ 之间。这些值不一定全部不同。

### 输出格式

输出一个数字，表示 Farmer John 可以实现的最小 $d_i$ 总和。请注意，这个数字可能超过标准 32 位整数的范围，因此可能需要使用更大的整数类型，例如 C/C++ 中的 `long long`。此外，你可能需要考虑答案是否一定是整数……

### 提示

在这个例子中，通过设置 $y = 8$，Farmer John 可以实现 $d_1 = 2$、$d_2 = 5$ 和 $d_3 = 3$。请注意，$y$ 在范围 $[7,10]$ 内的任何值也会产生最优解。

题目来源：Brian Dean


---

---
title: "上帝造题的七分钟"
layout: "post"
diff: 提高+/省选-
pid: P4514
tag: ['树状数组', '前缀和', '差分']
---
# 上帝造题的七分钟
## 题目背景

裸体就意味着身体。
## 题目描述

“第一分钟，X 说，要有矩阵，于是便有了一个里面写满了 $0$ 的 $n\times m$ 矩阵。

第二分钟，L 说，要能修改，于是便有了将左上角为 $(a,b)$，右下角为 $(c,d)$ 的一个矩形区域内的全部数字加上一个值的操作。

第三分钟，k 说，要能查询，于是便有了求给定矩形区域内的全部数字和的操作。

第四分钟，彩虹喵说，要基于二叉树的数据结构，于是便有了数据范围。

第五分钟，和雪说，要有耐心，于是便有了时间限制。

第六分钟，吃钢琴男说，要省点事，于是便有了保证运算过程中及最终结果均不超过 $32$ 位有符号整数类型的表示范围的限制。

第七分钟，这道题终于造完了，然而，造题的神牛们再也不想写这道题的程序了。”。

——《上帝造裸题的七分钟》。

所以这个神圣的任务就交给你了。
## 输入格式

输入数据的第一行为 `X n m`，代表矩阵大小为 $n\times m$。  
从输入数据的第二行开始到文件尾的每一行会出现以下两种操作：  
-    `L a b c d delta` —— 代表将 $(a,b),(c,d)$ 为顶点的矩形区域内的所有数字加上 $delta$。  
-    `k a b c d`     —— 代表求 $(a,b),(c,d)$ 为顶点的矩形区域内所有数字的和。  

请注意，$k$ 为小写。  
## 输出格式

针对每个 $k$ 操作，在单独的一行输出答案。
## 样例

### 样例输入 #1
```
X 4 4
L 1 1 3 3 2
L 2 2 4 4 1
k 2 2 3 3
```
### 样例输出 #1
```
12
```
## 提示

对于 $10\%$ 的数据，$1 \le n \le 16$，$1 \le m \le 16$， 操作不超过 $200$ 个。

对于 $60\%$ 的数据，$1 \le n \le 512$，$1 \le m \le 512$。

对于 $100\%$ 的数据，$1 \le n \le 2048$，$1 \le m \le 2048$，$-500 \le delta \le 500$，操作不超过 $2\times 10^5$ 个，保证运算过程中及最终结果均不超过 $32$ 位带符号整数类型的表示范围。


---

---
title: "[SNOI2017] 一个简单的询问"
layout: "post"
diff: 提高+/省选-
pid: P5268
tag: ['2017', '莫队', '各省省选', '差分']
---
# [SNOI2017] 一个简单的询问
## 题目描述

给你一个长度为 $N$ 的序列 $a_i$，$1\leq i\leq N$，和 $q$ 组询问，每组询问读入 $l_1,r_1,l_2,r_2$，需输出

$$
\sum\limits_{x=0}^\infty \text{get}(l_1,r_1,x)\times \text{get}(l_2,r_2,x)
$$

$ \text{get}(l,r,x)$ 表示计算区间 $[l,r]$ 中，数字 $x$ 出现了多少次。
## 输入格式

第一行，一个数字 $N$，表示序列长度。  
第二行，$N$ 个数字，表示 $a_1\sim a_N$。  
第三行，一个数字 $Q$，表示询问个数。  
第 $4\sim Q+3$ 行，每行四个数字 $l_1,r_1,l_2,r_2$，表示询问。
## 输出格式

对于每组询问，输出一行一个数字，表示答案。
## 样例

### 样例输入 #1
```
5
1 1 1 1 1
2
1 2 3 4
1 1 4 4
```
### 样例输出 #1
```
4
1
```
## 提示

对于 $20\%$ 的数据，$1\leq N,Q\leq 1000$；  
对于另外 $30\%$ 的数据，$1\leq a_i\leq 50$；  
对于 $100\%$ 的数据，$N,Q\leq 50000$，$1\leq a_i\leq N$，$1\leq l_1\leq r_1\leq N$，$1\leq l_2\leq r_2\leq N$。

数据范围与原题相同，但测试数据由 LibreOJ 自制，并非原数据。  

**注意：** 答案有可能超过 `int` 的最大值。


---

---
title: "「ACOI2020」学园祭"
layout: "post"
diff: 提高+/省选-
pid: P6042
tag: ['数学', '递推', '2020', '前缀和', '差分']
---
# 「ACOI2020」学园祭
## 题目背景

![T4](https://s2.ax1x.com/2020/01/12/lopWDS.md.png)

秋天，是学习之秋，食欲之秋，更是，学园祭之秋！随着时间流逝，学园祭也越来越近。终于等到这一天，可是没想到在冲绳岛上邂逅到女装的渚同学的勇次竟然来了！中村 莉櫻（Nakamura Rio）见到这个情况，忙给渚同学换上女装。没办法，勇次已经来了，于是渚同学鼓起勇气迈出了第一步。（为什么自顾自地加提示框啊喂！）
## 题目描述

莉櫻为了利用这个人傻钱多的少爷，尽全力提高消费额，努力地暗示渚同学。没办法，于是渚同学想了一下，提出了一个问题：

给出一个 $n$，定义：
$$
\Gamma(0)=1,\Gamma(n)={n!}
$$

$$
A_i^j=\frac{\Gamma(i)}{\Gamma(j)}
$$
求
$$
\sum_{i=1}^n \sum_{j=1}^i \sum_{k=1}^j \gcd(A_{i-j}^j \times \Gamma(j),A_{j-k}^k \times \Gamma(k)) 
$$

渚同学念着莉櫻举起的对话板上写的字：如果不能在规定时间回答出问题的话，就要把菜单全部买一遍哦！

尽管勇次钱多，但是他并不想吃得太多，因为这个问题有 $T$ 个小问题！

**由于答案可能太大，请将答案对 $10086001$ 取模。**
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据：

只有一行一个整数 $n$。
## 输出格式

对于每组数据，一行一个整数，表示问题的答案对 $10086001$ 取模后的值。
## 样例

### 样例输入 #1
```
5
1
2
3
4
5

```
### 样例输出 #1
```
1
4
10
20
36

```
## 提示

#### 数据范围
**本题采用捆绑测试**。

- Subtask 1（20 points）：$T \leq 10^3$，$n \leq 10^2$。   
- Subtask 2（30 points）：$T \leq 10^6$，$n \leq 5 \times 10^3$。  
- Subtask 3（50 points）：$T \leq 10^6$，$n \leq 10^6$。   

对于 $100\%$ 的数据，$1 \leq T,n \leq 10^6$。


---

---
title: "[USACO19FEB] Painting the Barn G"
layout: "post"
diff: 提高+/省选-
pid: P6100
tag: ['动态规划 DP', '2019', 'USACO', '差分']
---
# [USACO19FEB] Painting the Barn G
## 题目描述

Farmer John 不太擅长多任务处理。他经常分心，很难完成一些长期的项目。目前，他正在谷仓的一侧刷油漆，但他一直忙着在很小的区域涂抹油漆，然后由于抚育母牛的需要而陷入困境，使谷仓的某些部分比其他部分涂有更多的油漆。

我们将谷仓的墙描述为一个 X-Y 平面，每次涂油漆的区域都是一个矩形。FJ 在这个平面上绘制了 $N$ 个矩形，每个矩形的边均与坐标轴平行。因此我们用矩形的左下角和右上角坐标来描述一个矩形。

FJ 想在谷仓里涂几层油漆，这样就不需要在不久的将来再次重新涂油漆。但是，他不想浪费时间涂过多的油漆。事实证明，$K$ 层涂料是最佳用量。但是因为涂油漆的面积太小了，FJ 并不太高兴。他决定最多再绘制两个**不相交**的矩形（这里的相交指两个矩形交的面积大于零，即如果两个矩形仅共用一条边或一个点，则不视为相交）来增加面积。当然不绘制新矩形或仅绘制一个新矩形也是允许的。
## 输入格式

第一行两个整数 $N,K$（$1 \leq N,K \leq 10^5$）。

接下来 $N$ 行，每行四个整数 $x_1,y_1,x_2,y_2$（$0 \leq x_1,y_1,x_2,y_2 \leq 200$），描述一个矩形。其左下角坐标为 $(x_1,y_1)$，右上角坐标为 $x_2,y_2$。保证所有矩形面积为正，即其不会退化为线段或点。

和现有的矩形一样，新绘制的矩形，其左下角和右上角坐标也必须是整数，且坐标必须在 $0 \sim 200$ 之间，面积也必须为正。
## 输出格式

输出被涂油漆恰好 $K$ 次区域的最大面积。
## 样例

### 样例输入 #1
```
3 2
1 1 4 4
3 3 7 6
2 2 8 7
```
### 样例输出 #1
```
26
```


---

---
title: "「Wdsr-1」笨蛋结构"
layout: "post"
diff: 提高+/省选-
pid: P6308
tag: ['2020', 'O2优化', '组合数学', '差分']
---
# 「Wdsr-1」笨蛋结构
## 题目背景

众所周知，琪露诺是笨蛋。
## 题目描述

琪露诺希望维护一个长度为 $n$ 的整数序列 $a$，初始值都为 $0$。

现在琪露诺想要进行 $q$ 次操作，每次选择序列中的一段区间 $[s,s+l-1]$ 并给出两个数字 $w,k$，使对所有的 $i \in [1,l]$，$a_{s+i-1}$ 加上 $w\times i^k$ 。  

琪露诺不希望 $k$ 很大，因此她给出了一个整数 $m$，满足 $0\le k\le m$。

为了不让头脑简单的琪露诺感到困惑，你只需要输出 依次进行完所有操作后，序列中的每个数字对 $2^{64}$ 取模（即 $\text{unsigned long long}$ 自然溢出）后的结果即可。

为了帮助你更好的理解题意，这里给出一段伪代码：

$$\def{\b}#1{\textbf{ #1 }}\def{\t}#1{\text{ #1 }}\def{\s}{\quad}
\def{\l}{\underline{\kern{300pt}}\cr[-10pt]}
\def{\r}{\overline{\underline{\kern{300pt}}}}
\begin{aligned}
&\r\cr&\b{Algorithm:}\t{An easy structure}\cr[-13pt]&\l\cr
&\begin{aligned}
    \t{1.}&\b{input}n,m,q \cr
    \t{2.}&\b{for}i=1\b{to} q \b{do} \cr
    \t{3.}&\s\b{input} s,l,w,k \cr
    \t{4.}&\s\b{for} j=1 \b{to} l \b{do}\cr
    \t{5.}&\s\s a[s+j-1] \gets a[s+j-1]+w\times \t{pow}(j,k) \cr
    \t{6.}&\s\b{end}\cr
    \t{7.}&\b{end}\cr
    \t{8.}&\b{for} i=1 \b{to} n \b{do}\cr
    \t{9.}&\s\b{output} a[i]\cr
    \t{10.}&\b{end}\cr
    \end{aligned}\cr[-12pt]
&\r\end{aligned}
%Made by @离散小波变换° .
%You can find his contributions by searching "JoesSR".
$$
其中 $\rm pow(a,b)$ 的含义为 $a^b$。 
## 输入格式

请调用下方代码的 `input(n,m,q,S,L,W,K)` 来输入 $n,m,q,s_i,l_i,w_i,k_i$。下标**从一开始**。  

其中 $s,l,w,k$ 的含义与题目描述保持一致。
## 输出格式

请调用下方代码的 `output(n,R)` 进行输出。其中 $R_i$ 为所有操作结束后的数列，下标**从一开始**。
## 样例

### 样例输入 #1
```
10 0 5 233

```
### 样例输出 #1
```
6942214367

```
### 样例输入 #2
```
1000 9 500 6666

```
### 样例输出 #2
```
7636746723064426256
```
## 提示

#### 样例一说明

生成的数据为：
```plain
10 0 5
7 1 1558211206 0
1 3 401324017 0
4 5 235225636 0
6 4 2137131141 0
1 2 3791175968 0
```
它的结果是：
```plain
4192499985 4192499985 401324017 235225636 235225636 2372356777 3930567983 2372356777 2137131141 0
```

---

#### 数据生成&数据输出

```cpp
typedef unsigned long long u64;
typedef unsigned int       u32;
u32 MT[624],idx;
void _init(u32 seed){
    MT[0]=seed; idx=0; for(int i=1;i<624;++i) 
    MT[i]=(0x6c078965*(MT[i-1]^((MT[i-1])>>30)+i));
}
void _gene(){
    for(int i=0;i<624;++i){
        int x=MT[i]&0x80000000+(MT[(i+1)%624]&0x7fffffff);
        MT[i]=MT[(i+397)%624]^(x>>1);
        if(x&2)MT[i]^=0x9908b0df;
    }
}
u32  _calc(){
    if(!idx) _gene(); int x=MT[idx];
    x^=x>>11,x^=(x<<7)&(0x9d2c5680);
    x^=(x<<15)&0xefc60000,x^=x>>18;
    idx=(idx+1)%624; return x;
}
u64 _get(){u64 ret=_calc()*_calc(); return ret;}
u64 _get(u64 _l,u64 _r){return _get()%(_r-_l+1ull)+_l;}
void input(int &_n,int &_m,int &_q,int *_S,int *_L,u64 *_W,int *_K){
    u32 seed; scanf("%d%d%d%u",&_n,&_m,&_q,&seed); _init(seed); int i=1;
    if(_n>100) for(;i<=_q/4;++i){
        int _a=_get(1,_n-100),_b=_get(_a+_m,_a+_m+1),_l=_b-_a+1,_k=_get(0,_m);
        u64 _w=_get(); _S[i]=_a,_L[i]=_l,_W[i]=_w,_K[i]=_k;
    }
    if(_n>100) for(;i<=_q/2;++i){
        int _a=_get(1,100),_b=_get(_n-100,_n),_l=_b-_a+1,_k=_get(0,_m);
        u64 _w=_get(); _S[i]=_a,_L[i]=_l,_W[i]=_w,_K[i]=_k;
    }
    for(;i<=_q;++i){
        int _a=_get(1,_n),_b=_get(1,_n); if(_a>_b) swap(_a,_b);
        int _l=_b-_a+1,_k=_get(0,_m); u64 _w=_get();
        _S[i]=_a,_L[i]=_l,_W[i]=_w,_K[i]=_k;
    }
}
void output(int n,u64 *R){
    u64 ret=n^_get(); for(int i=1;i<=n;i++) ret^=_get()+R[i];
    printf("%llu\n",ret);
}
```
其中，调用 `input()` 读入数据；调用 `output()` 输出数据。

**请勿在任何时候调用除了`input`和`output`外的函数，且这两个函数只能调用一次**。

--- 

#### 数据范围 

共 $20$ 个测试点，满足如下条件：

$$\def\arraystretch{1.5}\begin{array}{|c|c|c|c|}\hline
\textbf{编号} & n & m & q \\ \hline
[1,3] & \le 3\times 10^3 & =9 & \le 3\times 10^3 \\\hline
[4,5] & \le 3\times 10^5 & =0 & \le 3\times 10^5 \\\hline
[6,9] & \le 3\times 10^5 & =1 & \le 3\times 10^5 \\\hline
[10,13] & \le 3\times 10^5 & =2 & \le 3\times 10^5 \\\hline
[14,16] & \le 3\times 10^5 & =9 & \le 3\times 10^5 \\\hline
[17,20] & \le 5\times 10^5 & =9 & \le 1\times 10^6 \\\hline
\end{array}$$

其中，$[l,r]$ 表示编号为 $l,l+1,\cdots,r-1,r$ 的测试点。

对于 $100\%$ 的数据，满足 $1\le l_i \le l_i+s_i-1 \le n,0\le k_i\le m,0 \le w\le 2^{64}-1$。


---

---
title: "[BalticOI 2017] Railway"
layout: "post"
diff: 提高+/省选-
pid: P6572
tag: ['2017', '虚树', '差分', 'BalticOI（波罗的海）']
---
# [BalticOI 2017] Railway
## 题目背景

Bergen 基础设施建设部在一年前就有了把所有的城市用道路连起来的想法。  
可惜的是，过了一年了，这个计划烂尾了。  
所以，基础设施建设部部长就准备重启这个计划，然后把它搞得简单亿点。
## 题目描述

原定的计划是有 $n$ 个城市用 $n-1$ 个道路连起来。    
现在有 $m$ 个副部长，每个副部长都认为有一些城市是必须连起来的。  
比如说这个副部长想把 $a$ 和 $c$ 连起来，有两条道路 $a - b$ 和 $b - c$，那么副部长的要求等价过来就是选择这两条道路。  
现在要找出几条道路是至少 $k$ 个副部长选择的。  
部长就找到了您，想让您找出这几条道路。
## 输入格式

第一行三个整数 $n,m,k$ 代表城市数，副部长数和最少需要满足多少个副部长。  
接下来 $n-1$ 行每行两个整数 $a_i$ 和 $b_i$ 代表第 $i$ 条道路是 $a_i$ 和 $b_i$ 之间的。  
这 $n-1$ 个道路的编号就是 $1$ 到 $n-1$。  
接下来 $m$ 行首先一个整数 $s_i$ 代表这个副部长觉得有 $s_i$ 个城市需要相连，接下来 $s_i$ 个整数代表副部长觉得哪些城市需要相连。
## 输出格式

第一行一个整数 $r$ 代表至少满足 $k$ 个副部长的道路有多少个。  
第二行 $r$ 个整数代表要搭建编号为哪些的道路的升序排列。
## 样例

### 样例输入 #1
```
6 3 2
1 3
2 3
3 4
6 4
4 5
4 1 3 2 5
2 6 3
2 3 2
```
### 样例输出 #1
```
2
2 3
```
## 提示

#### 样例说明

$3$ 个副部长的要求如下：

- $1-3,2-3,3-4,4-5$
- $3-4,4-6$
- $2-3$

至少满足 $2$ 个副部长的道路为 $2$ 号和 $3$ 号。

#### 数据范围

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$n \le 10^4$，$\sum s_i \le 2 \times 10^3$。
- Subtask 2（15 pts）：$n \le 10^4$，$m \le 2 \times 10^3$。
- Subtask 3（7 pts）：每个城市最多是 $2$ 条道路的端点。
- Subtask 4（29 pts）：$k=m$，$s_i=2$。
- Subtask 5（16 pts）：$k=m$。
- Subtask 6（25 pts）：无特殊限制。

对于 $100\%$ 的数据，$2 \le s_i \le n \le 10^5$，$1 \le k \le m \le 5 \times 10^4$，$\sum s_i \le 10^5$。

#### 说明

**翻译自 [BOI 2017 D1](https://boi.cses.fi/files/boi2017_day1.pdf) T2 Railway。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

应扶咕咕的要求已经删减 $1 \sim 5$ 子任务中的部分数据，保留了 $6$ 子任务中的极限数据。


---

---
title: "[YsOI2020] 换寝室"
layout: "post"
diff: 提高+/省选-
pid: P6594
tag: ['二分', 'O2优化', '深度优先搜索 DFS', '树形 DP', '最近公共祖先 LCA', '差分']
---
# [YsOI2020] 换寝室
## 题目背景

马上要开学了，Ysuperman 正在为给孩子们分配寝室忙得不可开交......
## 题目描述

幼儿园里面有 $n$ 个房间，这些房间由 $n-1$ 条双向道路连接着，第 $i$ 条道路连接着房间 $u_i$ 和 $v_i$ ，每条道路 Ysuperman 都可以选择开启或者是关闭，每个房间**在所有道路开启的前提下**都可以到达其他任意一个房间。

每个房间有一个差异值，其中，第 $i$ 个房间的差异值为 $h_i$ 。

在选择完关闭哪些道路后，整个寝室会被分成许多连通块，一个联通块内的小朋友的不满意值定义为连通块内差异值的**最大值减去最小值**，小朋友们的总不满意值定义为**所有联通块不满意值的最大值**。

寝室里有 $m$ 个寝室老师，每个老师晚上都要查寝，第 $i$ 个老师会从第 $x_i$ 个房间走到第 $y_i$ 个房间，如果老师在查寝时经过了某条被关闭的道路，TA就会很生气，一个老师的不满意值定义为**从 $x_i$ 走到 $y_i$ 经过的被关闭的道路数量**，老师的总不满意值定义为**所有老师的不满意值之和**。

Ysuperman 能承受的老师的总不满意值最大为 $k$ ，现在TA想知道小朋友们的总不满意值最小可以达到多少。
## 输入格式

输入共 $n+m+1$ 行。

第一行三个整数 $n,m,k$，表示房间个数，寝室老师个数和Ysuperman 能承受的老师的总不满意值。

接下来一行，共 $n$ 个整数，第 $i$ 个整数是 $h_i$，表示第 $i$ 个房间的差异值。

接下来 $n-1$ 行，每行两个整数，第 $i+2$ 行是 $u_i$ 和 $v_i$，表示寝室 $u_i,v_i$ 之间有直接道路。

接下来 $m$ 行，每行两个整数，第 $i+n+1$ 行是 $x_i$ 和 $y_i$，表示第 $i$ 个老师的查寝路线。
## 输出格式

一行一个整数，即答案。
## 样例

### 样例输入 #1
```
5 2 0
1 3 1 4 0
1 2
1 3
1 4
1 5
2 3
1 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5 2 1
1 3 1 4 0
1 2
1 3
1 4
1 5
2 3
1 4
```
### 样例输出 #2
```
2
```
## 提示

### 样例说明

#### 样例说明 $1$

![](https://cdn.luogu.com.cn/upload/image_hosting/mf6j6hz3.png)

Ysuperman选择关闭连接着 $1$ 和 $5$ 的道路，老师的总不满意值为 $0$，寝室被分为 $2$ 个连通块，小朋友们的总不满意值为 $3$。

#### 样例说明 $2$

图同样例一。

Ysuperman选择关闭连接着 $1$ 和 $5$ 的道路以及连接着 $1$ 和 $4$ 的道路，老师的总不满意值为 $1$，寝室被分为 $3$ 个连通块，小朋友们的总不满意值为 $2$。

------
### 数据范围

**本题采用捆绑测试。**

| Subtask | $n$ | $m$ | $k$ | 特殊性质 | 分数 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| 1 | $\le 20$ | $\le 10$ | $\le 80$ | 无 | 8 |
| 2 | $\le 150$ | $\le 10^3$ | $\le 8 \times 10^4$ | 无 | 13 |
| 3 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 树为一条链 | 13 |
| 4 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 树为一朵盛开的菊花 | 13 |
| 5 | $\le 800$ | $\le 10^5$ | $= 0$ | 无 | 13 |
| 6 | $\le 800$ | $\le 10^5$ | $\le 8 \times 10^7$ | 无 | 40 |

【一条链】定义为：所有点的度数 $\le2$。

【一朵盛开的菊花】定义为：存在一个点的度数为 $n-1$。

对于 $100\%$ 的数据，满足 $1\le h_i\le 10^9，0\le k \le 8\cdot 10^7,u_i\ne v_i$ 。


---

---
title: "「Wdsr-2.7」天才⑨与数学递推式"
layout: "post"
diff: 提高+/省选-
pid: P7705
tag: ['递推', 'O2优化', '差分']
---
# 「Wdsr-2.7」天才⑨与数学递推式
## 题目描述

生活在雾之湖的冰精琪露诺，向来以智慧而著称。作为寺子屋的老学员，琪露诺可是对数学递推式了如指掌。

有一天，慧音老师想要考一考琪露诺。于是她写出了一个长度为 $m$ 的递推公式：

$$F_t=\sum_{i=1}^m K_i\times F_{t-i} \quad (t> m)$$

其中 $m,\{K_i\}$ 都是被给定的。不过，由于这个序列 $\{F_i\}$ 的初始 $m$ 项并没有被确定，所以可能存在无穷个满足这个递推式，但是初始 $m$ 项并不一致的递推数列。慧音打算选择其中 $q$ 个 $F$ ，来考考琪露诺对数列知识的掌握。

具体而言，慧音会依次告诉琪露诺，若干个 $\{F_i\}$ 的起始 $m$ 项。显然，这样就能生成无穷序列 $\{F_i\}$ 了。尽管如此，生成这么多序列并不好玩。于是慧音又创造了一个答案序列 $\{A_i\}$ ，满足初始时 $A_i=0$ 。

每当给出一个新的 $\{F_i\}$ ，慧音都要琪露诺使 $\{A_i\}$ 的第 $a,a+1,\cdots b-1,b$ 项分别加上 $F_1,F_2,F_3,\cdots,F_{b-a+1}$ 。

当然，慧音老师不想为难琪露诺，于是对于所有数字，只要输出其对 $p$ 取模的值即可。其中 $p$ 是一个被给定的常数。

---

形式化地讲述题面：给定 $n,q,m,p,\{K_1,K_2,\cdots ,K_m\}$ 。有 $q$ 次操作，每次给定一组 $a,b,\{G_1,G_2\cdots G_m\}$ ，求出无穷序列 $\{F_i\}$ ：

$$F_t=\begin{cases}
G_t & t\le m \cr
\sum_{i=1}^m K_iF_{t-i} & t>m
\end{cases}$$

然后令 $\forall i\in [a,b] ,A_i\gets A_i+F_{i-a+1}$ 。最后分别输出 $\{A_i\}$ 的前 $n$ 项对 $p$ 取模后的结果。
## 输入格式

- 第一行有四个正整数 $n,q,m,p$ ，含义如题面所示。

- 第二行有 $m$ 个整数 $\{K_1,K_2,\cdots ,K_m\}$ ，表示递推式中的系数。

- 接下来 $q$ 行，每行 $2+m$ 个整数 $a,b,\{G_1,G_2,\cdots G_m\}$ ，描述一次操作。
## 输出格式

- 共一行， $n$ 个整数，输出 $A_i \bmod p$ 的值。
## 样例

### 样例输入 #1
```
5 3 2 114514
1 1
1 3 1 1
2 5 1 1
1 5 2 0
```
### 样例输出 #1
```
3 2 5 4 7
```
### 样例输入 #2
```
20 5 4 1919810
2 5 4 3
1 20 1 1 1 1
5 12 7 6 1 2
2 18 9 0 0 1
9 11 5 4 4 1
10 14 1 0 0 0
```
### 样例输出 #2
```
1 10 1 1 22 75 221 850 3176 11706 43324 160379 586060 249707 351705 931555 619201 372869 1800119 1750063

```
## 提示

#### 样例解释

对于样例 $1$ ：

- 初始时， $\{A_i\}=\{0,0,0,0,0\}$ 。

- 第一步生成了一个 $\{F_i\}=\{1,1,2,3,5\}$ ，加至 $A_1,A_2,A_3$ ，此时 $\{A_i\}=\{1,1,2,0,0\}$ 。

- 第二步生成了一个 $\{F_i\}=\{1,1,2,3,5\}$ ，加至 $A_2,A_3,\cdots ,A_5$ ，此时 $\{A_i\}=\{1,2,3,2,3\}$ 。

- 第三步生成了一个 $\{F_i\}=\{2,0,2,2,4\}$ ，加至 $A_1,A_2,\cdots ,A_5$ ，此时 $\{A_i\}=\{3,2,5,4,7\}$ 。

对于样例 $2$ ，我们既没有一个绝妙的解释，又没有足够大的空间，于是我们写不下了。

#### 数据范围及约定

$$\def{\arraystretch}{1.5}\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n} & \bm{m} & \bm{q}& \textbf{分值}\cr\hline
1 & n\le  10^4 & m\le 10 & q\le 10^3 & 10 \cr\hline
2 & n\le  10^5 & m=1 & q\le 10^5  & 20\cr\hline
3 & n\le  10^5 & m=2 & q\le 10^5 & 20\cr\hline
4 & \text{无特殊限制} & \text{无特殊限制} & \text{无特殊限制}& 50 \cr\hline
\end{array}$$

- 对于 $100\%$ 的数据，满足 $ 1 \leq n\le 1\times 10^6;1\le q \leq 1.2 \times 10^5;1 \leq m \leq 15;1 \leq K_i,G_i,p \leq 10^8;1\le a\le b\le n$ 。


---

---
title: "「CGOI-1」收税"
layout: "post"
diff: 提高+/省选-
pid: P7768
tag: ['树状数组', 'Special Judge', 'O2优化', '可持久化线段树', '差分']
---
# 「CGOI-1」收税
## 题目背景

~~签到题~~

由于举办选丑大赛消耗了太多钱财，ac 决定派出 Push_Y 去收税。
## 题目描述

丑国由 $n$ 座城市组成，编号 $1$ 的为首都。这 $n$ 座城市由 $n-1$ 条长度为 $1$ 的双向道路连接。从编号为 $x$ 的城市出发，往**远离**首都的方向（即往儿子节点走），距离不超过 $h$ 的就是这座城市要收税的范围。

第 $i$ 座城市将要上缴 $a_i$ **元**的所得税。但由于收税官 Push_Y 很喜欢异或，因此每座城市最终上缴的所得税将是在其收税范围内每座城市**应缴税额**的异或和。

Push_Y 将向你提出 $m$ 个询问，他将问你城市 $x$ 在收税距离为 $h$ 时将收到多少**千元**的所得税。

**简化版题意：**

给定一棵 $n$ 个点的树，根节点为 $1$ 号点，第 $i$ 个点的点权为 $a_i$，$dep_u$ 表示 $u$ 点的深度，根节点的深度为 $1$，$q$ 次询问，每次给定两个整数 $x,h$，表示询问 $\bigoplus_{u\in son(x)\land dep_u-dep_x\le h}a_i$ 除以 $1000$ 后的值。

其中 $\bigoplus_{i=1}^ni$ 表示 $1\operatorname{xor} 2\operatorname{xor}\cdots\operatorname{xor} n$。

此处 $\land$ 是“且”，$\operatorname{xor}$ 是异或。
## 输入格式

第一行两个正整数 $n,m$，表示城市数和询问数。

第二行 $n$ 个正整数 $a_i$， 表示每座城市应缴的所得税额。

第三行 $n-1$ 个正整数，其中第 $i$ 个数 $f_i$ 表示城市 $i+1$ 与城市 $f_i$ 有一条路相连。

从第 $4$ 行开始 $m$ 行，每行两个正整数 $x,h$，表示一组询问。
## 输出格式

对于每组询问，输出一行，一个实数，表示这座城市收取的税额。

**答案保留三位小数。**
## 样例

### 样例输入 #1
```
6 3
604 545 402 378 25 13
1 2 2 3 3
1 2
3 0
2 4
```
### 样例输出 #1
```
0.149
0.402
0.733
```
### 样例输入 #2
```
6 3
6 5 4 3 2 1
1 2 2 3 3
1 2
3 0
2 4
```
### 样例输出 #2
```
0.004
0.004
0.001
```
## 提示

对于 $30\%$ 的数据，$1\le n,m\le 10^3$。

对于 $70\%$ 的数据，$1\le n,m\le5 \times 10^4$。其中有 $20\%$ 的数据是链。

对于 $100\%$ 的数据，$1\le n,m\le 10^6$，$1 \le a_i \le 10^9$，$1\le x \le n$，$0 \le h \le n$。


---

---
title: "「EVOI-RD2」旅行家"
layout: "post"
diff: 提高+/省选-
pid: P7924
tag: ['O2优化', '双连通分量', '最近公共祖先 LCA', '差分']
---
# 「EVOI-RD2」旅行家
## 题目描述

小 A 是一个热衷于旅行的旅行家。有一天，他来到了一个城市，这个城市由 $n$ 个景点与 $m$ 条连接这些景点的道路组成。每个景点有一个**美观度** $a_i$。

定义一条**旅游路径**为两个景点之间的一条非严格简单路径，也就是点可以重复经过，而边不可以。

接下来有 $q$ 个旅游季，每个旅游季中，小 A 将指定两个顶点 $x$ 和 $y$，然后他将走遍 $x$ 到 $y$ 的**所有旅游路径**。 

所有旅游季结束后，小 A 会统计他所经过的所有景点的美观度之和（重复经过一个景点只统计一次美观度）。他希望你告诉他这个美观度之和。
## 输入格式

第一行两个正整数 $n,m$。

第二行 $n$ 个正整数 $a_i$，代表顶点 $i$ 的权值。

接下来 $m$ 行，每行 $2$ 个正整数，表示一条无向边的两个端点。

然后一个正整数 $q$，代表有 $q$ 个旅游季。

接下来 $q$ 行，每行 $2$ 个整数 $x,y$，表示指定的起点和终点。
## 输出格式

一行，一个整数表示最终的美观度总和。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
2 3
1 4
4 3
3 5
3
1 2
1 4
1 3

```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5 6
1 2 3 4 5
1 2
2 3
1 4
1 5
4 3
3 5
3
1 2
1 4
1 3

```
### 样例输出 #2
```
15
```
## 提示

**【数据规模与范围】**

**本题采用捆绑测试**

+ Subtask 1 (30 pts)：$3 \leq n \leq 500,m \leq 2 \times 10^5,q=200$。
+ Subtask 2 (30 pts)：$3 \leq n \leq 3 \times 10^5,m \leq 2 \times 10^6,q=10^6$。
+ Subtask 3 (40 pts)：$3 \leq n \leq 5 \times 10^5,m \leq 2 \times 10^6,q=10^6$。

对于 $100\%$ 的数据，保证 $3 \leq n \leq 5 \times  10^5$，$m \leq 2 \times 10^6$，$q=10^6$，$1 \leq a_i \leq 100$，且该图联通，没有重边和自环。

---

**对于题面的解释：**


![](https://cdn.luogu.com.cn/upload/image_hosting/a2oku1vq.png)

上图与样例无关。

如图，为城市的景点分布图，为无向图。  
假设 $6$ 号顶点为 $x$ 景点，$5$ 号顶点为 $y$ 景点。  
很显然，路径 $6 \rightarrow 2 \rightarrow 4 \rightarrow 5$ 和路径 $6 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 5$ 都是合法的，这两条路径满足了都是简单路径的条件，并且都是在一次旅游季中行走的。  
虽然 $6 \rightarrow 2$ 这条边经过了 $2$ 次，但仍旧是合法的，因为它们不是在一条路径中经过的。

简单来说，一次旅游季会走不定条路径，每条路径必须是简单路径，但是每条简单路径之间可以有重边。


---

---
title: "[传智杯 #4 决赛] [yLOI2021] 生活在树上（hard version）"
layout: "post"
diff: 提高+/省选-
pid: P8201
tag: ['树形数据结构', 'Special Judge', 'O2优化', '最近公共祖先 LCA', '前缀和', '差分', '传智杯']
---
# [传智杯 #4 决赛] [yLOI2021] 生活在树上（hard version）
## 题目背景

**本题是 P8200 的较难版本，两道题目的解法略有不同。本题和 P8200 在题意上的区别在于本题给定树上的点权，而不是边权。**

小智生活在「传智国」，这是一个有 $n$ 个城市的国家，各个城市由 $n-1$ 条道路相连。

每个城市都有一个财富指数 $w_i$ ，我们定义，小智从城市 $a$ 走到城市 $b$ 的代价是 $\mathrm{dis}_{a, b} = \bigoplus \limits_{u \in \mathrm{path}\left(a, b\right)} w_u$，其中 $\bigoplus$ 表示**按位异或**（如果你不知道什么是**按位异或**，请参见题目下方的提示/说明），$\mathrm{path}\left(a,b\right)$ 表示 $a$ 到 $b$ 的简单路径上的点集（包括 $a$ 和 $b$）。也即 $\mathrm{dis}_{a, b}$ 表示将 $a$ 与 $b$ 的简单路径上所有点写作 $u_1, u_2, u_3, \dots$ 后，求 $w_{u_1} \bigoplus w_{u_2}\bigoplus w_{u_3} \dots$ 的结果。

有一天，小智获得了去参加传智杯的机会，他在前往比赛地的路上想到了一个问题，但他好像不会做，于是他把这个题告诉了你。聪明的同学，你可以帮帮他吗？
## 题目描述

小智说：「由于我们的国家只有 $n$ 个城市和 $n-1$ 条道路，那么我们的国家就相当于是一棵树。我在想，在我们的国家中，是否存在城市满足『到城市 $a$ 的代价和到城市 $b$ 的代价的异或等于 $k$』。好难哦，我想不出来，你能帮帮我吗？」

也就是说，给定城市 $a, b$ 和整数 $k$，请你计算是否存在城市 $t$ 满足 $\mathrm{dis}_{t, a} \bigoplus \mathrm{dis}_{t, b} = k$。
## 输入格式

第一行有两个整数 $n$，$m$，表示国家的城市数和询问的个数。

第二行有 $n$ 个整数 $w_i$，表示 $i$ 号城市的财富指数。

接下来 $n-1$ 行，每行有两个整数 $x, y$，表示城市 $x$ 与城市 $y$ 有一条边相连。

接下来 $m$ 行，每行有三个整数 $a, b, k$，表示小智从城市 $a$ 走到城市 $b$，$k$ 的含义与题目描述一致。
## 输出格式

输出共 $m$ 行。

对于第 $i$ 个询问，如果存在至少一个城市 $t$ 满足要求，则输出 `Yes`。

如果不存在任何一个城市满足条件，则输出 `No`。

输出字符串大小写不敏感，例如，`Yes`、`yES`、`YES`、`yes` 等都算作 `Yes`。
## 样例

### 样例输入 #1
```
5 3
2 6 8 1 5
1 2
1 3
2 4
2 5
1 2 4
2 3 12
2 3 10
```
### 样例输出 #1
```
nO
No
YeS
```
### 样例输入 #2
```
5 10
93 97 100 93 93
2 1
3 2
4 3
5 1
5 2 93
4 1 93
3 2 100
3 2 100
2 3 9999998
1 2 93
2 3 97
1 2 93
2 3 97
4 3 93
```
### 样例输出 #2
```
no
nO
yEs
yEs
No
yEs
yeS
YES
yES
yes
```
## 提示

### 相关概念解释
「树」：树是一个有 $n$ 个结点和 $n-1$ 条边的无向简单连通图。

「按位异或」：按位异或是一个二元运算，步骤是将两个数的二进制位按位比较，相同为 $0$，不同为 $1$ 。例如：$3 \bigoplus 5 = (011)_2 \bigoplus (101)_2 = (110)_2 = 6$。
### 样例 1 解释
下图为传智国的地图。

$\forall t \in \{1, 2, 3, 4, 5\}$，都不可能有 $\mathrm{dis} _{t,1} \bigoplus \mathrm{dis}_{t, 2} = 4$，$\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 12$，于是输出 `No`；

而取 $t=4$，有 $\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 10$，于是输出 `Yes`。

![](https://cdn.luogu.com.cn/upload/image_hosting/d3phj9di.png)
### 数据规模与约定
对于所有测试点，保证 $1 < n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq w_i \leq 1\times 10^7$。

对于每次询问，保证 $1 \leq a,b \leq n$ 且 $a \neq b$，$0 \leq k \leq 1\times 10^7$。
### 提示
- 请注意常数因子对程序效率造成的影响。
- 对于两个 $x, y \leq 10^7$，$x \bigoplus y$ 可能大于 $10^7$，请特别注意这一点。


---

---
title: "「CGOI-2」No cost too great"
layout: "post"
diff: 提高+/省选-
pid: P8502
tag: ['动态规划 DP', 'O2优化', '容斥原理', '差分']
---
# 「CGOI-2」No cost too great
## 题目背景

光芒浸透圣巢，她正犯下弥天之错。

所剩寥寥无几的信仰，为什么始终执着。

我将作灯塔，照耀王国。

但在那之前有更重要的事去做，

无论什么代价都在所不惜，尽管我所剩无多……
## 题目描述

白王正在最后一次参观他建造的宏伟宫殿。现在假设宫殿由 $n$ 个房间构成，房间之间有若干个**单向**通道。出于白王奇怪的装修癖好（不是指到处安电锯），对于第 $i$ 个房间，它向编号在区间 $[l_i,r_i]$ 中的所有房间都连有一条单向通道。例如，$4$ 号房间向 $[2,5]$ 连有单向通道，就意味着从 $4$ 号房间到 $2,3,4,5$ 号房间各有一条单向通道（一个房间可以向自己连有通道）。当一个房间向 $[0,0]$ 连有通道时，表示没有从这个房间出发的通道。

白王提出了 $q$ 个问题，每次询问从 $a$ 号房间，通过恰好 $m$ 条单向通道且不经过 $c$ 号房间到达 $b$ 号房间的方案数（两方案不同，当且仅当存在 $i$ 使得两方案通过的第 $i$ 条通道不同）。因为这个数字可能会很大，所以白王让你将答案模 $998244353$ 后再回答。
## 输入格式

第一行，两个整数 $n, q$ 表示点数和询问数。

接下来 $n$ 行，每行两个整数 $l, r$，第 $i+1$ 行的整数 $l_i, r_i$ 表示 $i$ 号节点向区间 $[l_i, r_i]$ 中的每个点都连了一条单向边。当 $l_i=r_i=0$ 时，表示该节点没有向任何点连边。

接下来 $q$ 行，每行四个整数 $a, b, c, m$ 表示一个询问。
## 输出格式

$q$ 行，每行一个整数，第 $i$ 行的数字表示第 $i$ 个询问的方案数模 $998244353$ 的结果。
## 样例

### 样例输入 #1
```
4 5
2 3
1 1
2 4
0 0
1 3 4 5
1 4 2 4
2 3 1 2
4 4 3 0
1 3 2 5
```
### 样例输出 #1
```
5
1
0
1
1
```
### 样例输入 #2
```
10 10
6 6
4 10
2 5
1 7
3 4
5 7
4 10
1 7
1 3
2 5
8 8 5 1
4 7 5 3
5 9 4 4
1 5 5 2
6 2 10 2
3 3 7 4
1 10 1 2
6 2 4 4
9 2 1 4
9 10 3 2
```
### 样例输出 #2
```
0
17
2
0
0
46
0
12
23
1
```
### 样例输入 #3
```
10 10
2 6
6 9
5 7
3 9
0 0
0 0
3 5
5 5
3 6
1 10
5 9 6 3
10 8 6 4
10 8 5 1
8 6 5 4
7 2 5 4
6 1 5 3
10 4 5 1
5 5 6 0
7 9 6 4
4 9 6 2
```
### 样例输出 #3
```
0
17
1
0
0
0
1
1
4
1
```
## 提示

### 样例说明

在样例一中，$1$ 号房间能到达 $2,3$ 号房间，$2$ 号房间能到达 $1$ 号房间，$3$ 号房间能到达 $2,3,4$ 号房间，$4$ 号房间不能到达任何房间。

对于第一个询问，从 $1$ 号房间经过 $5$ 条通道且不经过 $4$ 号房间到达 $3$ 号房间的方案有 `121213`，`121333`，`133213`，`132133`，`133333` 共五种。

---

### 数据范围

**本题采用捆绑测试。**

| 编号| 特殊性质 | 空间限制 |分数 |
| :-: | :-: | :-: | :-: |
| 0 | $n\le10$，$q\le10$，$m\le4$ | 256MB | 10pts |
| 1 | $n\le100$，$q\le10^4$，$m\le40$ | 256MB | 15pts |
| 2 | 对于所有询问，$l_c=r_c=0$ | 256MB | 15pts |
| 3 | 无 | 256MB | 30pts |
| 4 | 无 | 128MB | 30pts |

对于 $100\%$ 的数据，$1\le n \le 500$，$1\le q \le 10^5$，$1\le m \le 100$，$0 \le l_i \le r_i \le n$，$1 \le a,b,c \le n$。当且仅当 $l_i=0$ 时 $r_i=0$。时间限制均为 1s。

---

### 提示

**注意空间常数。**


---

---
title: "[POI 2020/2021 R3] Les Bitérables"
layout: "post"
diff: 提高+/省选-
pid: P9403
tag: ['2020', 'POI（波兰）', '差分', '双指针 two-pointer']
---
# [POI 2020/2021 R3] Les Bitérables
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Les Bitérables](https://szkopul.edu.pl/problemset/problem/Lpz563_ATiESIrNZxiT5bwIx/statement/)。

d1t2。
## 题目描述

有 $t$ 个时刻，第 $i$ 个时刻给出了局面 $p_1,p_2,\dots,p_{s_i}$，表示在数轴的 $(0,d)$ 范围内，有且仅有 $p_1,p_2,\dots,p_{s_i}$ 这些位置上有物品。

在 $0$ 位置和 $d$ 位置有无穷多个物品。

你可以花费一个代价，将一个物品向左移动一个位置或向右移动一个位置。

问你在相邻两个时刻之间，把前一个局面转化为后一个局面，最少需要多少代价。
## 输入格式

第一行两个正整数 $n,d$。

接下来 $n$ 行，每行描述一个时刻的局面，首先是一个非负整数 $s_i$，接下来是 $s_i$ 个正整数，分别为 $p_1,p_2,\dots,p_{s_i}$。保证 $0<p_1<p_2<\dots<p_{s_i}<d$。
## 输出格式

$n-1$ 行，每行一个整数，你的答案。
## 样例

### 样例输入 #1
```
3 10
2 4 7
3 3 6 8
1 5

```
### 样例输出 #1
```
4
6
```
### 样例输入 #2
```
见附件
```
### 样例输出 #2
```
6252500
6252500

```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
999990000
999990000
999990000
999990000

```
### 样例输入 #4
```
生成器：/paste/3igmip11
```
### 样例输出 #4
```
生成器：/paste/fusadpm0
```
## 提示

对于所有数据，$2\leq n\leq 500000$，$2\leq d\leq 10^{12}$，$\sum s_i\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $s_i\leq 1$ | 5 |
| 2 | $s_i\leq 3$ | 10 |
| 3 | $d\leq 7$ | 12 |
| 4 | $\sum s_i\leq 5000$ | 27 |
| 5 | 如果 $s_i>0$，那么 $p_{s_i}=p_1+s_i-1$ | 11 |
| 6 |  | 35 |



---

