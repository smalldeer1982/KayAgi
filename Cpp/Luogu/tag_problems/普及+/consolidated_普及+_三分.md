---
title: "[蓝桥杯 2024 国 Java B] 激光炮"
layout: "post"
diff: 普及+/提高
pid: P12261
tag: ['数学', '2024', '三分', 'Special Judge', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java B] 激光炮
## 题目描述

小明在二维平面上放置了 $n$ 门激光炮，第 $i$ 门激光炮位于坐标 $(-10^5, a_i)$，射向靶点 $(10^5, b_i)$，形成 $n$ 条线段。他想使用一条垂直于 $x$ 轴且其中一个端点在 $x$ 轴上的线段挡住所有激光炮的发射路线，这条线段的长度最短为多少？
## 输入格式

输入共 $n+1$ 行。

第一行为一个正整数 $n$。

后面 $n$ 行，每行 2 个由空格分开的非负整数表示 $a_i, b_i$。
## 输出格式

输出共 $1$ 行，一个浮点数表示答案（输出四舍五入到 $2$ 位小数）。
## 样例

### 样例输入 #1
```
3
0 100000
100000 200000
200000 0
```
### 样例输出 #1
```
133333.33
```
## 提示

### 样例说明

第 $2,3$ 门激光炮发射路线的交点为 $(-\frac{100000}{3}, \frac{400000}{3})$，因此，只需要在 $(-\frac{100000}{3}, 0)$ 处放置一条长度为 $\frac{400000}{3} = 133333.33$ 的线段即可挡住所有 3 门激光炮。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，保证 $n \leq 10^2$。
- 对于 $100\%$ 的评测用例，保证 $n \leq 10^5$，$0 \leq a_i, b_i \leq 10^6$。


---

---
title: "[JOI2025 预选赛 R2] 冰淇淋"
layout: "post"
diff: 普及+/提高
pid: P12458
tag: ['博弈论', '二分', '2024', '三分', 'JOI（日本）']
---
# [JOI2025 预选赛 R2] 冰淇淋
## 题目描述

Alice 和 Bob 来到了 JOICE 冰淇淋店。这家店的顾客可以通过选择一种口味、一种蛋筒和一种配料来订购冰淇淋。

- 口味有 $X$ 种，价格分别为 $A_1, A_2, \ldots, A_X$。
- 蛋筒有 $Y$ 种，价格分别为 $B_1, B_2, \ldots, B_Y$。
- 配料有 $Z$ 种，价格分别为 $C_1, C_2, \ldots, C_Z$。

冰淇淋的价格是所选口味、蛋筒和配料价格的总和。给定一个整数 $P$，冰淇淋的**得分**定义为价格与 $P$ 之差的绝对值。

Alice 和 Bob 想要一起订购一个冰淇淋，但他们对冰淇淋的选择目标完全相反。具体来说，Alice 希望最大化得分，而 Bob 希望最小化得分。因此，他们决定按照以下方式选择冰淇淋的口味、蛋筒和配料：

1. 首先，Alice 选择口味。
2. 然后，Bob 选择蛋筒。
3. 最后，Alice 选择配料。

给定口味、蛋筒、配料的信息以及整数 $P$，编写一个程序，计算当双方都采取最佳策略时，最终订购的冰淇淋的得分。
## 输入格式

输入按以下格式给出：
$$
\begin{aligned}
&X\ Y\ Z\ P\\
&A_1\ A_2\ \ldots\ A_X\\
&B_1\ B_2\ \ldots\ B_Y\\
&C_1\ C_2\ \ldots\ C_Z\\
\end{aligned}
$$
## 输出格式

输出最终订购的冰淇淋的得分。
## 样例

### 样例输入 #1
```
1 1 3 22
5
10
9 2 3
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
1 2 2 100
11
33 44
40 60
```
### 样例输出 #2
```
15
```
### 样例输入 #3
```
2 2 2 0
15 23
5 16
23 45
```
### 样例输出 #3
```
73
```
### 样例输入 #4
```
3 3 3 50
12 5 5
2 19 37
10 5 15
```
### 样例输出 #4
```
14
```
## 提示

### 样例解释
#### 样例 1 解释

- 口味价格为 5。
- 蛋筒价格为 10。
- 配料价格分别为 9、2、3。

Alice 首先选择价格为 5 的口味，Bob 选择价格为 10 的蛋筒。最后，Alice 选择价格为 2 的配料，使得总价格为 17，得分为 $|17-22|=5$。

### 输入例 2 解释

- 口味价格为 11。
- 蛋筒价格分别为 33、44。
- 配料价格分别为 40、60。

Alice 选择价格为 11 的口味，Bob 选择价格为 44 的蛋筒（因为这样可以使 Alice 选择价格为 60 的配料，得分为 $|115 - 100|=15$）。

### 输入例 3 解释

- 口味价格分别为 15、23。
- 蛋筒价格分别为 5、16。
- 配料价格分别为 23、45。

Alice 选择价格为 23 的口味，Bob 选择价格为 5 的蛋筒，Alice 选择价格为 45 的配料，总价格为 73，得分为 $|73-0|=73$。

### 输入例 4 解释

- 口味价格分别为 12、5、5。
- 蛋筒价格分别为 2、19、37。
- 配料价格分别为 10、5、15。

Alice 选择价格为 12 的口味，Bob 选择价格为 2 的蛋筒，Alice 选择价格为 15 的配料，总价格为 29，得分为 $|29 - 50| = 21$。然而，Bob 会选择价格为 19 的蛋筒，使得 Alice 选择价格为 15 的配料，总价格为 46，得分为 $|46-50|=4$。但最终得分为 14，因为 Alice 会选择最优策略。

### 数据范围

- $1 \leq X \leq 200\,000$。
- $1 \leq Y \leq 200\,000$。
- $1 \leq Z \leq 200\,000$。
- $0 \leq P \leq 3 \times 10^8$。
- $0 \leq A_i \leq 10^8$ ($1 \leq i \leq X$)。
- $0 \leq B_j \leq 10^8$ ($1 \leq j \leq Y$)。
- $0 \leq C_k \leq 10^8$ ($1 \leq k \leq Z$)。
- 输入的所有值都是整数。

### 子任务

1. (7 分) $X = 1$，$Y = 1$，$Z \leq 100$。
2. (17 分) $X = 1$，$Y \leq 100$，$Z \leq 100$。
3. (21 分) $X \leq 100$，$Y \leq 100$，$Z \leq 100$。
4. (22 分) $X \leq 4\,000$，$Y \leq 4\,000$，$Z \leq 4\,000$。
5. (33 分) 无额外约束。


---

---
title: "[GCJ 2009 #1C] Center of Mass"
layout: "post"
diff: 普及+/提高
pid: P13438
tag: ['数学', '2009', '三分', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2009 #1C] Center of Mass
## 题目描述

You are studying a swarm of $N$ fireflies. Each firefly is moving in a straight line at a constant speed. You are standing at the center of the universe, at position $(0, 0, 0)$. Each firefly has the same mass, and you want to know how close the center of the swarm will get to your location (the origin).

You know the position and velocity of each firefly at $t = 0$, and are only interested in $t \geq 0$. The fireflies have constant velocity, and may pass freely through all of space, including each other and you. Let $M(t)$ be the location of the center of mass of the $N$ fireflies at time $t$. Let $d(t)$ be the distance between your position and $M(t)$ at time $t$. Find the minimum value of $d(t)$, $d_{\text{min}}$, and the earliest time when $d(t) = d_{\text{min}}$, $t_{\text{min}}$.
## 输入格式

The first line of input contains a single integer $T$, the number of test cases. Each test case starts with a line that contains an integer $N$, the number of fireflies, followed by $N$ lines of the form

$x\ y\ z\ v_x\ v_y\ v_z$

Each of these lines describes one firefly: $(x, y, z)$ is its initial position at time $t = 0$, and $(v_x, v_y, v_z)$ is its velocity.

## 输出格式

For each test case, output

Case #$X$: $d_{\text{min}}$ $t_{\text{min}}$

where $X$ is the test case number, starting from 1. Any answer with absolute or relative error of at most $10^{-5}$ will be accepted.
## 样例

### 样例输入 #1
```
3
3
3 0 -4 0 0 3
-3 -2 -1 3 0 0
-3 -1 2 0 3 0
3
-5 0 0 1 0 0
-7 0 0 1 0 0
-6 3 0 1 0 0
4
1 2 3 1 2 3
3 2 1 3 2 1
1 0 0 0 0 -1
0 10 0 0 -10 -1
```
### 样例输出 #1
```
Case #1: 0.00000000 1.00000000
Case #2: 1.00000000 6.00000000
Case #3: 3.36340601 1.00000000
```
## 提示

**Notes**

Given $N$ points $(x_i, y_i, z_i)$, their center of the mass is the point $(x_c, y_c, z_c)$, where:

- $x_c = (x_1 + x_2 + \ldots + x_N) / N$
- $y_c = (y_1 + y_2 + \ldots + y_N) / N$
- $z_c = (z_1 + z_2 + \ldots + z_N) / N$

**Limits**

- All the numbers in the input will be integers.
- $1 \leq T \leq 100$
- The values of $x$, $y$, $z$, $v_x$, $v_y$, and $v_z$ will be between $-5000$ and $5000$, inclusive.

**Small dataset(10 Pts)**

- $3 \leq N \leq 10$

**Large dataset(17 Pts)**

- $3 \leq N \leq 500$


---

---
title: "[CERC 2023] Going to the Moon"
layout: "post"
diff: 普及+/提高
pid: P13851
tag: ['数学', '2023', '三分', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2023] Going to the Moon
## 题目描述

Alice and Bob are playing a game in the sand outside their mansion. A circle representing the Moon is drawn somewhere, and they each also pick a place to stand (inside, on the edge, or outside the Moon). The goal of the game is that one of the players runs to the other as fast as possible, while also touching the Moon during the run.

Given the positions of the Moon, Alice, and Bob, find the length of the shortest path that starts at one of the players, touches (or crosses) the edge or the interior of the Moon, and ends at the position of the other player.

## 输入格式

The first line contains an integer $T$, the number of test cases. It’s followed by $T$ lines, each containing 7 space-separated integers $x_A$, $y_A$, $x_B$, $y_B$, $x_C$, $y_C$, $r$, representing coordinates of Alice, $A = (x_A, y_A)$, Bob, $B = (x_B, y_B)$, the center of the circle, $C = (x_C, y_C)$, and its radius $r$.

## 输出格式

For each test case output a single decimal number representing the length of the shortest path from $A$ to $B$ that also touches at least one point inside or on the edge of a circle with the center $C$ and radius $r$. The solution will be considered correct if the relative or absolute error compared to the official solution is within $10^{-6}$.

## 样例

### 样例输入 #1
```
2
0 0 2 0 -1 2 1
5 0 3 0 2 0 2
```
### 样例输出 #1
```
3.9451754612261913
2
```
## 提示

### Comment

The solution for the first test case is shown in the picture.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/rnv9of0l.png)
:::align

### Input limits

- $1 \leq T \leq 10^3$
- $-10^3 \leq x_A, y_A, x_B, y_B, x_C, y_C \leq 10^3$
- $0 \leq r \leq 10^3$


---

---
title: "「RdOI R2」称重(weigh)"
layout: "post"
diff: 普及+/提高
pid: P7579
tag: ['二分', '2021', '三分', '交互题', 'Special Judge', '分治']
---
# 「RdOI R2」称重(weigh)
## 题目背景

因为 rui_er 是一个良心出题人，所以本题是一道交互题。
## 题目描述

rui_er 为了准备体测，买了 $n$ 个实心球准备练习，但是却发现在发货时混入了两个质量明显较轻但外观相似的球（这两个球质量相等），且已知这两个球的质量之和大于一个正常的球。为了防止影响训练效果，现在需要找出这两个球。因为手动找太慢了，现在拿来了一个天平，可以在两侧各放上若干个球，得到两侧的质量大小关系。请你帮帮 rui_er，在使用不超过 $k$ 次天平的情况下，找出这两个较轻的球。

这里 $k$ 是每个测试点的属性，你不必也不应该读入。

---

**交互方式**

本题采用 I/O 交互。

你可以选择进行称量操作，此时向标准输出打印一行 `1 p a1 a2 ... ap q b1 b2 ... bq`，表示在天平左盘放入编号为 $a_1,a_2,\cdots,a_p$ 的 $p$ 个球，在天平右盘放入编号为 $b_1,b_2,\cdots,b_q$ 的 $q$ 个球。随后清空缓冲区，并从标准输入读入一个 `<>=` 之一的字符，表示左盘与右盘的质量关系。

对于每次此类询问，你需要保证 $1\le p,q\le n$，$p+q\le n$，所有 $a_i$ 和 $b_i$ 互不相同，且你最多进行此类询问 $k$ 次。

在得到答案后，向标准输出打印一行 `2 x y` 来提交答案，表示编号为 $x$ 的球和编号为 $y$ 的球质量偏轻。

你需要保证 $1\le x\lt y\le n$（注意需要严格按照从小到大顺序输出），且在进行完这一操作后立即终止程序。

交互库在一开始就已经确定小球的情况，不会随着你的询问而改变。
## 输入格式

第一行一个整数 $n$，表示球的数量。这里 $k$ 是每个测试点的属性，你不必也不应该读入。

接下来若干行，见【交互方式】。
## 输出格式

若干行，见【交互方式】。
## 样例

### 样例输入 #1
```
6

=

<

>
```
### 样例输出 #1
```

1 1 1 1 2

1 1 3 1 4

1 1 5 1 6

2 3 6
```
## 提示

**样例解释**

三次询问的结果为 $a_1=a_2,a_3\lt a_4,a_5\gt a_6$，可以知道编号为 $3,6$ 的两个球质量偏轻。

---

**数据范围**

本题按点得分。

$20$ 个非 HACK 测试点中，第一个点 $4$ 分，其它点每点 $5$ 分；$4$ 个 HACK 测试点共 $1$ 分，任意一个测试点不通过则不得分。

|测试点|$n\le$|$k=$|特殊性质|测试点|$n\le$|$k=$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|1|$5$|$50$|无|11|$500$|$50$|无|
|2|$10$|$50$|无|12|$500$|$50$|无|
|3|$100$|$50$|无|13|$500$|$20$|A|
|4|$100$|$50$|无|14|$500$|$20$|B|
|5|$500$|$50$|A|15|$500$|$20$|A|
|6|$500$|$50$|B|16|$500$|$20$|B|
|7|$500$|$50$|A|17|$500$|$20$|无|
|8|$500$|$50$|B|18|$500$|$20$|无|
|9|$500$|$50$|无|19|$500$|$20$|无|
|10|$500$|$50$|无|20|$500$|$20$|无|
|ex1|$500$|$12$|B/HACK|ex3|$500$|$13$|HACK|
|ex2|$500$|$13$|HACK|ex4|$500$|$14$|HACK|

- 特殊性质 A：$n=2^i-1,i\in\left\{4,5,6,7,8\right\}$。
- 特殊性质 B：$n=2^i,i\in\left\{4,5,6,7,8\right\}$。
- 备注：HACK 数据的 $k$ 根据测试点实际情况设置，会卡一些奇怪的做法，保证正解可过。

对于全部数据，$5\le n\le 500$，$k\in\left\{50,20,14,13,12\right\}$。


---

---
title: "[USACO23DEC] Haybale Distribution G"
layout: "post"
diff: 普及+/提高
pid: P9982
tag: ['数学', '二分', 'USACO', '2023', '三分', 'O2优化']
---
# [USACO23DEC] Haybale Distribution G
## 题目描述

Farmer John 正在农场上分发干草堆。

Farmer John 的农场上有 $N$（$1 \le N \le 2\cdot 10^5$）座谷仓，分别位于数轴上的整点 $x_1,\ldots,x_N$（$0 \le x_i \le 10^6$）。Farmer John 正计划将 $N$ 车干草堆运输到整点 $y$（$0 \le y \le 10^6$），然后为每一座谷仓运输一车干草堆。

不幸的是，Farmer John 的运输系统浪费了很多干草堆。具体来说，给出一些 $a_i,b_i$（$1 \le a_i,b_i \le 10^6$），每车干草堆每向左移动一单位距离，$a_i$ 堆干草堆会被浪费；每车干草堆每向右移动一单位距离，$b_i$ 堆干草堆会被浪费。形式化地，一车干草堆从整点 $y$ 运动到位于 $x$ 的谷仓，被浪费的干草堆堆数如下：

$$\begin{cases}a_i\cdot (y-x) & \text{if} \ y>x \\ b_i\cdot(x-y)&\text{if}\ x>y\end{cases}$$

给出 $Q$（$1 \le Q \le 2 \cdot 10^5$）组相互独立的询问，每组询问给出一组 $(a_i,b_i)$ 的值，帮助 Farmer John 计算当按照最佳方案选择 $y$，最少有多少堆干草堆被浪费。
## 输入格式

第一行包含 $N$。

接下来一行包含 $x_1\dots x_N$。

接下来一行包含 $Q$。

接下来 $Q$ 行，每行包含两个整数 $a_i,b_i$。
## 输出格式

输出 $Q$ 行，第 $i$ 行包含第 $i$ 个询问的答案。
## 样例

### 样例输入 #1
```
5
1 4 2 3 10
4
1 1
2 1
1 2
1 4
```
### 样例输出 #1
```
11
13
18
30
```
## 提示

### 样例解释 1

样例中第二个询问，最佳方案为选择 $y=2$，被浪费的干草堆数量为 $2(2-1)+2(2-2)+1(3-2)+1(4-2)+1(10-2)=1+0+1+2+8=13$。

### 测试点性质

- 测试点 $2$ 满足 $N,Q \le 10$。
- 测试点 $3$ 满足 $N,Q \le 500$。
- 测试点 $4-6$ 满足 $N,Q \le 5000$。
- 测试点 $7-16$ 没有额外限制。


---

