---
title: "[KTSC 2023 R1] 出租车旅行"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11343
tag: ['点分治', '2023', '交互题', '斜率优化', 'KOI（韩国）']
---
# [KTSC 2023 R1] 出租车旅行
## 题目背景

**请勿用 C++14 (GCC 9) 提交。**

请在程序开头加入如下代码：

```cpp
#include<vector>
std::vector<long long> travel(std::vector<long long> A, std::vector<int> B, std::vector<int> U, std::vector<int> V, std::vector<int> W);
```
## 题目描述

**题目译自 [2023년도 국제정보올림피아드 대표학생 선발고사 - 1차 선발고사](https://www.ioikorea.kr/archives/ioitst/2023/)  T3 「[택시 여행](https://assets.ioikorea.kr/ioitst/2023/1/taxi/taxi_statement.pdf)」**

IOI 国由 $N$ 个城市和连接这些城市的 $N-1$ 条双向道路组成，任意两个不同的城市都可以通过这些道路互相到达。也就是说，IOI 国的道路网络是一个树结构。

每个城市都有一个编号，从 $0$ 到 $N-1$，其中 $0$ 号城市是 IOI 国的首都。对于每个 $i$ $(0 \leq i \leq N-2)$，第 $i$ 条道路连接 $U[i]$ 号城市和 $V[i]$ 号城市，道路长度为 $W[i]$ 公里。

在 IOI 国，不同城市的出租车费用不同。具体来说，对于每个 $i$ $(0 \leq i \leq N-1)$，从 $i$ 号城市出发的出租车有一个基本费用 $A[i]$ 元和每公里的费用 $B[i]$ 元。这意味着，如果从 $i$ 号城市出发并行驶 $d$ 公里，需要支付 $A[i] + d \times B[i]$ 元。

小明目前住在首都 $0$ 号城市，他计划乘坐出租车去其他城市旅行。当他到达一个城市时，可以选择继续乘坐当前的出租车，或者换乘该城市出发的出租车。当然，换乘出租车需要支付基本费用，并且每公里的费用也可能不同。请计算从 0 号城市出发到达其他所有城市的最小费用。

你需要实现以下函数：

```cpp
vector<long long> travel(vector<long long> A, vector<int> B, vector<int> U, vector<int> V, vector<int> W);
```

- 该函数只会被调用一次。
- `A`：大小为 $N$ 的整数数组。对于每个 $i$ $(0 \leq i \leq N-1)$，$A[i]$ 是从 $i$ 号城市出发的出租车的基本费用。
- `B`：大小为 $N$ 的整数数组。对于每个 $i$ $(0 \leq i \leq N-1)$，$B[i]$ 是从 $i$ 号城市出发的出租车的每公里费用。
- `U, V, W`：大小为 $N-1$ 的整数数组。对于每个 $i$ $(0 \leq i \leq N-2)$，$U[i]$ 号城市和 $V[i]$ 号城市之间有一条长度为 $W[i]$ 公里的道路。
- 该函数返回一个大小为 $N-1$ 的数组 $C$。对于每个 $i$ $(0 \leq i \leq N-2)$，$C[i]$ 是从 $0$ 号城市出发到达 $i+1$ 号城市的最小费用。

注意，提交的代码中不应包含任何输入输出操作。
## 输入格式

示例评测程序按以下格式读取输入：

- 第 $1$ 行：$N$
- 第 $2$ 行：$A[0]\,A[1]\,\cdots\,A[N-1]$
- 第 $3$ 行：$B[0]\,B[1]\,\cdots\,B[N-1]$
- 第 $4+i$ $(0 \leq i \leq N-2)$ 行：$U[i]\,V[i]\,W[i]$
## 输出格式

示例评测程序按以下格式输出：

- 第 $i$ 行：函数 `travel` 返回的数组的第 $i$ 个元素
## 样例

### 样例输入 #1
```
5
10 5 13 4 3
10 7 5 9 1
1 0 1
0 2 5
3 2 10
2 4 3
```
### 样例输出 #1
```
20
60
104
88
```
## 提示

### 样例解释

考虑 $N=5, A=[10,5,13,4,3], B=[10,7,5,9,1], U=[1,0,3,2], V=[0,2,2,4], W=[1,5,10,3]$ 的情况。

评测程序将调用如下函数：

```cpp
travel([10, 5, 13, 4, 3], [10, 7, 5, 9, 1], [1, 0, 3, 2], [0, 2, 2, 4], [1, 5, 10, 3]);
```

- 从 $0$ 号城市到 $1$ 号城市的最优方案是直接从 $0$ 号城市乘坐出租车，总费用为 $20$ 元。
- 从 $0$ 号城市到 $2$ 号城市的最优方案是直接从 $0$ 号城市乘坐出租车，总费用为 $60$ 元。
- 从 $0$ 号城市到 $4$ 号城市的最优方案是先从 $0$ 号城市乘坐出租车到 $1$ 号城市，然后换乘，再经过 $0$ 号和 $2$ 号城市到达 $4$ 号城市，总费用为 $88$ 元。
- 从 $0$ 号城市到 $3$ 号城市的最优方案是先从 $0$ 号城市乘坐出租车到 $1$ 号城市，然后换乘，再经过 $0$ 号和 $2$ 号城市到达 $4$ 号城市，再换乘，经过 $2$ 号城市到达 $3$ 号城市，总费用为 $104$ 元。

函数应返回 `[20, 60, 104, 88]`。

### 数据范围

对于所有输入数据，满足：

- $2 \leq N \leq 10^5$
- 对于所有 $i$ $(0 \leq i \leq N-1)$，$0 \leq A[i] \leq 10^{12}$
- 对于所有 $i$ $(0 \leq i \leq N-1)$，$0 \leq B[i] \leq 10^6$
- 对于所有 $i$ $(0 \leq i \leq N-2)$，$0 \leq U[i], V[i] \leq N-1 ; U[i] \neq V[i]$
- 对于所有 $i$ $(0 \leq i \leq N-2)$，$1 \leq W[i] \leq 10^6$

详细子任务附加限制及分值如下表所示。

| 子任务 | 分值 | 附加限制 |
| :-: | :-: | :-: |
| $1$ | $7$ | $N \leq 20$ |
| $2$ | $8$ | 对于所有 $i$ $(0 \leq i \leq N-2)$，$U[i]=i ; V[i]=i+1$ |
| $3$ | $13$ | $N \leq 2000$ |
| $4$ | $17$ | 对于所有 $i$ $(0 \leq i \leq N-1)$，$B[i] \leq 30$ |
| $5$ | $29$ | $B[i] \neq 0$ $(0 \leq i \leq N-1)$ 的 $i$ 不超过 $2000$ 个 |
| $6$ | $26$ | 无附加限制 |


---

---
title: "[NOI2016] 国王饮水记"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1721
tag: ['动态规划 DP', '2016', 'NOI', 'Special Judge', '斜率优化']
---
# [NOI2016] 国王饮水记
## 题目描述

跳蚤国有 $n$ 个城市，伟大的跳蚤国王居住在跳蚤国首都中，即 $1$ 号城市中。

跳蚤国最大的问题就是饮水问题，由于首都中居住的跳蚤实在太多，跳蚤国王又体恤地将分配给他的水也给跳蚤国居民饮用，这导致跳蚤国王也经常喝不上水。

于是，跳蚤国在每个城市都修建了一个圆柱形水箱，这些水箱完全相同且足够高。一个雨天后，第 $i$ 个城市收集到了高度为 $h_i$ 的水。由于地理和天气因素的影响，任何两个不同城市收集到的水高度互不相同。

跳蚤国王也请来蚂蚁工匠帮忙，建立了一个庞大的地下连通系统。跳蚤国王每次使用地下连通系统时，可以指定任意多的城市，将这些城市的水箱用地下连通系统连接起来足够长的时间之后，再将地下连通系统关闭。由连通器原理，这些城市的水箱中的水在这次操作后会到达同一高度，并且这一高度等于指定的各水箱高度的平均值。

由于地下连通系统的复杂性，跳蚤国王至多只能使用 $k$ 次地下连通系统。

跳蚤国王请你告诉他，首都 $1$ 号城市水箱中的水位最高能有多高？
## 输入格式

输入的第一行包含三个正整数 $n,k,p$ 分别表示跳蚤国中城市的数量，跳蚤国王能使用地下连通系统的最多次数，以及你输出的答案要求的精度。$p$ 的含义将在输出格式中解释。

接下来一行包含 $n$ 个正整数，描述城市的水箱在雨后的水位。其中第 $i$ 个正整数 $h_i$ 表示第 $i$ 个城市的水箱的水位。保证 $h_i$ 互不相同，$1 \leq h_i \leq 10^5$。
## 输出格式

仅一行一个实数，表示 $1$ 号城市的水箱中的最高水位。

这个实数只可以包含非负整数部分、小数点和小数部分。其中非负整数部分为必需部分，不加正负号。若有小数部分，则非负整数部分与小数部分之间以一个小数点隔开。若无小数部分，则不加小数点。

你输出的实数在小数点后不能超过 $2p$ 位，建议保留至少 $p$ 位。数据保证参考答案与真实答案的绝对误差小于 $10^{-2p}$。

你的输出被判定为正确当且仅当你的输出与参考答案的绝对误差小于 $10^{-p}$。

如果你的输出与参考答案的绝对误差不小于 $10^{-p}$ 但小于 $10^{-5}$，你可以获得该测试点 $40\%$ 的分数。
## 样例

### 样例输入 #1
```
3 1 3
1 4 3
```
### 样例输出 #1
```
2.666667
```
### 样例输入 #2
```
3 2 3
1 4 3
```
### 样例输出 #2
```
3.000000
```
## 提示

### 样例解释 1

由于至多使用一次地下连通系统，有以下五种方案：
 
1. 不使用地下连通系统：此时 $1$ 号城市的水箱水位为 $1$。 
2. 使用一次连通系统，连通 $1$、$2$ 号：此时 $1$ 号城市的水箱水位为 $5/2$。 
3. 使用一次连通系统，连通 $1$、$3$ 号：此时 $1$ 号城市的水箱水位为 $2$。 
4. 使用一次连通系统，连通 $2$、$3$ 号：此时 $1$ 号城市的水箱水位为 $1$。 
5. 使用一次连通系统，连通 $1$、$2$、$3$ 号：此时 $1$ 号城市的水箱水位为 $8/3$。

### 样例解释 2

此时最优方案为使用两次连通系统，第一次连通 $1,3$ 号，第二次连通 $1,2$ 号。

### 样例 3

详见附加文件。

### 提示

为保证答案精度，我们一般需要尽可能地在运算过程中保留超过 $p$ 位小数。我们可以证明，在各个子任务的参考算法中都能保证，在任何时候始终保留 $\frac{6}{5}p$ 位小数时，对任何输入得到的输出，与参考答案的绝对误差都小于 $10^{-p}$。

为了方便选手处理高精度小数，我们提供了定点高精度小数类。选手可以根据自己的需要参考与使用该类，也可以不使用该类。其具体的使用方法请参考下发的文档 `decimal.pdf`（见附件）。

### 数据范围

| 测试点编号 | $n$ | $k$ | $p$ |
|-|-|-|-|
| 1 | $\le 2$ | $\le 5$ | $=5$ |
| $2$ | $\le 4$ | $\le 5$ | $=5$ |
| $3$ | $\le 4$ | $\le 5$ | $=5$ |
| 4 | $\le 10$ | $=1$ | $=5$ |
| $5$ | $\le 10$ | $=10^9$ | $=5$ |
| $6$ | $\le 10$ | $\le 10$ | $=5$ |
| $7$ | $\le 10$ | $\le 10$ | $=5$ |
| $8$ | $\le 100$ | $=1$ | $=5$ |
| $9$ | $\le 100$ | $=10^9$ | $=40$ |
| $10$ | $\le 100$ | $\le 10^9$ | $=40$ |
| $11$ | $\le 100$ | $\le 10^9$ | $=40$ |
| $12$ | $\le 100$ | $\le 10^9$ | $=40$ |
| $13$ | $\le 250$ | $\le 10^9$ | $=100$ |
| $14$ | $\le 500$ | $\le 10^9$ | $=200$ |
| $15$ | $\le 700$ | $\le 10^9$ | $=300$ |
| $16$ | $\le 700$ | $\le 10^9$ | $=300$ |
| $17$ | $\le 700$ | $\le 10^9$ | $=300$ |
| $18$ | $\le 2500$ | $\le 10^9$ | $=1000$ |
| $19$ | $\le 4000$ | $\le 10^9$ | $=1500$ |
| $20$ | $\le 8000$ | $\le 10^9$ | $=3000$ |


---

---
title: "[NOI2014] 购票"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2305
tag: ['图论', '2014', '线段树', 'NOI', '分治', '斜率优化']
---
# [NOI2014] 购票
## 题目描述

今年夏天，NOI 在 SZ 市迎来了她三十周岁的生日。来自全国 $n$ 个城市的 OIer 们都会从各地出发，到 SZ 市参加这次盛会。

全国的城市构成了一棵以 SZ 市为根的有根树，每个城市与它的父亲用道路连接。为了方便起见，我们将全国的 $n$ 个城市用 $1\sim n$ 的整数编号。其中 SZ 市的编号为 $1$。对于除 SZ 市之外的任意一个城市 $v$，我们给出了它在这棵树上的父亲城市 $f_v$  以及到父亲城市道路的长度 $s_v$。

从城市 $v$ 前往 SZ 市的方法为：选择城市 $v$ 的一个祖先 $a$，支付购票的费用，乘坐交通工具到达 $a$。再选择城市 $a$ 的一个祖先 $b$，支付费用并到达 $b$。以此类推，直至到达 SZ 市。

对于任意一个城市 $v$，我们会给出一个交通工具的距离限制 $l_v$。对于城市 $v$ 的祖先 A，只有当它们之间所有道路的总长度不超过 $l_v$  时，从城市 $v$ 才可以通过一次购票到达城市 A，否则不能通过一次购票到达。  

对于每个城市 $v$，我们还会给出两个非负整数 $p_v,q_v$  作为票价参数。若城市 $v$ 到城市 A 所有道路的总长度为 $d$，那么从城市 $v$ 到城市 A 购买的票价为 $dp_v+q_v$。

每个城市的 OIer 都希望自己到达 SZ 市时，用于购票的总资金最少。你的任务就是，告诉每个城市的 OIer 他们所花的最少资金是多少。

## 输入格式

第一行包含两个非负整数 $n,t$，分别表示城市的个数和数据类型（其意义将在「提示与说明」中提到）。

接下来 $2 \sim n$ 行，每行描述一个除 SZ 之外的城市。其中第 $v$ 行包含五个非负整数 $f_v,s_v,p_v,q_v,l_v$，分别表示城市 $v$ 的父亲城市，它到父亲城市道路的长度，票价的两个参数和距离限制。

请注意：输入不包含编号为 1 的 SZ 市，第 $2\sim n$ 行分别描述的是城市 $2$ 到城市 $n$。

## 输出格式

输出包含 $n-1$ 行，每行包含一个整数。

其中第 $v$ 行表示从城市 $v+1$ 出发，到达 SZ 市最少的购票费用。

同样请注意：输出不包含编号为 1 的 SZ 市。

## 样例

### 样例输入 #1
```
7 3 
1 2 20 0 3 
1 5 10 100 5 
2 4 10 10 10 
2 9 1 100 10 
3 5 20 100 10 
4 4 20 0 10 

```
### 样例输出 #1
```
40 
150 
70 
149 
300 
150
```
## 提示

从每个城市出发到达 SZ 的路线如下（其中箭头表示一次直达）：

城市 $2$：只能选择 $2 \rightarrow 1$，花费为 $2 \times 20 + 0 = 40$。

城市 $3$：只能选择 $3 \rightarrow 1$，花费为 $5 \times 10 + 100 = 150$。

城 市 $4$ ： 由于 $4 + 2 =6 \leq l_4 = 10$，故可以选择 $4\rightarrow1$。若选择 $4 \rightarrow 1$，花费为 $(4 +2) \times 10 + 10 = 70$ ； 若选择 $4 \rightarrow 2 \rightarrow 1$，则花费为 $(4\times 10 + 10) + (2 \times  20 + 0) =90$；因此选择 $4 \rightarrow 1$。

城市 $5$：只能选择 $5\rightarrow 2\rightarrow 1$，花费为 $(9 \times 1 +100) + (2 \times  20 + 0) = 149$；无法选择 $5 \rightarrow 1$，因为 $l_5 =10$，而城市 $5$ 到城市 $1$ 总路程为 $9 + 2 = 11 \gt 5$，城市 $5$ 不能直达城市 $1$。

城市 $6$：若选择 $6 \rightarrow 1$，花费为 $(5 + 5) \times 20 + 100 = 300$；若选择 $6 \rightarrow 3 \rightarrow 1$，花费为 $(5 \times 20 + 100) + (5 \times 10 + 100) = 350$；因此选择 $6 \rightarrow 1$。

城市 $7$：选择 $7 \rightarrow 4 \rightarrow 1$，花费为 $(4 \times 20 + 0) + ((4 + 2) \times 10 + 10) = 150$；

其他方案均比该方案差。

 ![](https://cdn.luogu.com.cn/upload/pic/2592.png) 

### 数据范围

![](https://cdn.luogu.com.cn/upload/pic/2591.png)

对于所有数据，$n\leq 2 \times 10^5, 0 \leq p_v \leq 10^6,\ 0 \leq q_v \leq 10^{12},\ 1\leq f_v<v,\ 0<s_v\leq lv \leq 2 \times 10^{11}$，且任意城市到 SZ 市的总路程长度不超过 $2 \times 10^{11}$。

输入的 $t$ 表示数据类型，$0\leq t<4$，其中：
- 当 $t=0$ 或 $2$ 时，对输入的所有城市 $v$，都有 $f_v=v-1$，即所有城市构成一个以 SZ 市为终点的链；
- 当 $t=0$ 或 $1$ 时，对输入的所有城市 $v$，都有 $l_v=2 \times 10^{11}$，即没有移动的距离限制，每个城市都能到达它的所有祖先；
- 当 $t=3$ 时，数据没有特殊性质。


---

---
title: "[POI 2014] SUP-Supercomputer"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3571
tag: ['2014', 'POI（波兰）', '斜率优化', '凸包']
---
# [POI 2014] SUP-Supercomputer
## 题目描述

Byteasar has designed a supercomputer of novel architecture.

```plain
It may comprise of many (identical) processing units.
```
Each processing unit can execute a single instruction per time unit.

The programs for this computer are not sequential but rather have a tree structure.

Each instruction may have zero, one, or multiple subsequent instructions,    for which it is the parent instruction.

The instructions of the program can be executed in parallel on all available    processing units.  Moreover, they can be executed in many orders: the only    restriction is that an instruction cannot be executed unless its parent    instruction has been executed before.  For example, as many subsequent    instructions of an instruction that has been executed already can be    executed in parallel as there are processing units.

Byteasar has a certain program to run.  Since he likes utilizing his resources    optimally, he is wondering how the number of processing units would affect the running time.

He asks you to determine, for a given program and number of processing units,    the minimum execution time of the program on a supercomputer with this many processing units.

给定一棵N个节点的有根树，根节点为1。Q次询问，每次给定一个K，用最少的操作次数遍历完整棵树，输出最少操作次数。每次操作可以选择访问不超过K个未访问的点，且这些点的父亲必须在之前被访问过。

## 输入格式

In the first line of standard input, there are two integers, $n$ and $q$ ($1\le n,q\le 1\ 000\ 000$), separated by a single space, that specify the number of    instructions in Byteasar's program and the number of running time queries (for different numbers    of processing units).

In the second line of input, there is a sequence of $q$ integers, $k_1,k_2,\cdots,k_q$ ($1\le k_i\le 1\ 000\ 000$), separated by single spaces: $k_i$ is the number of processing units in    Byteasar's $i$-th query.

In the third and last input line, there is a sequence of $n-1$ integers, $a_2,a_3,\cdots,a_n$($1\le a_i<i$) separated by single spaces: $a_i$ specifies the number of the parent instruction of the instruction number $i$. The instructions are numbered with successive integers from 1 to $n$, where the instruction no. 1 is the first instruction of the program.

## 输出格式

Your program should print one line consisting of $q$ integers, separated by single spaces,    to the standard output:

the $i$-th of these numbers should specify the minimum execution time of the program on a supercomputer with $k_i$ processing units.

## 样例

### 样例输入 #1
```
20 1
3
1 1 1 3 4 3 2 8 6 9 10 12 12 13 14 11 11 11 11

```
### 样例输出 #1
```
8

```
## 题目翻译

给定一棵 $n$ 个节点的有根树，根节点为 $1$。$q$ 次询问，每次给定一个 $k$，用最少的操作次数遍历完整棵树，输出最少操作次数。每次操作可以选择访问不超过 $k$ 个未访问的点，且这些点的父亲必须在这次操作之前被访问过。

$n, q \leq 10^6$。


---

