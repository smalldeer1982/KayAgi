---
title: "[NOISG 2025 Finals] Flooding"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12019
tag: ['2025', '扫描线', 'NOISG（新加坡）']
---
# [NOISG 2025 Finals] Flooding
## 题目描述

Pavementland is a rectangle-shaped city, which can be modelled as a $h \times w$ grid of cells. The rows of the grid are numbered $1$ to $h$ from north to south, and the columns of the grid are numbered $1$ to $w$ from west to east. We refer to the cell located at row $r$ and column $c$ of the grid as cell $(r, c)$.

In the grid, each cell is either empty or contains a building. At least one cell is empty.

Due to a monsoon surge, flash floods are occurring throughout Pavementland. Initially, one empty cell becomes flooded with water by the rain. Then, the water flows according to the following rules:

- If an empty cell is adjacent to at least one flooded cell, it becomes flooded.
- If a cell containing a building is adjacent to at least two flooded cells, the building collapses and the cell becomes flooded.

Note that a cell is adjacent to another cell if they share an edge. A cell is adjacent to at most four other cells. Further note that water may not flow outside the grid. Let $f((r, c))$ be the number of cells that would be flooded after the process if the cell $(r, c)$ were initially flooded.

City officials are seeking to forecast the extent of flash floods in all possible scenarios. Help them determine the sum of $f((r, c))$ over all empty cells $(r, c)$.

## 输入格式

Your program must read from standard input.

The first line of input contains two space-separated integers $h$ and $w$.

The next $h$ lines of input each contain a binary string of length $w$. If the $c$-th character of the $r$-th line is $0$, then the cell $(r, c)$ is empty. If the $c$-th character of the $r$-th line is $1$, then the cell $(r, c)$ contains a building.

## 输出格式

Your program must print to standard output.

Output a single integer, the sum of $f((r, c))$ over all empty cells $(r, c)$.

## 样例

### 样例输入 #1
```
3 3
000
011
010
```
### 样例输出 #1
```
46
```
### 样例输入 #2
```
5 5
00101
01011
11010
01101
11000
```
### 样例输出 #2
```
182
```
### 样例输入 #3
```
1 10
1101011100
```
### 样例输出 #3
```
6
```
## 提示

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $1 \leq h, w \leq 5000$
- There is at least one empty cell in the grid.

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Marks | Additional Constraints |
| :-: | :-: | :-: |
| $0$ | $0$ | Sample test cases |
| $1$ | $5$ | $h = 1$ |
| $2$ | $7$ | $h, w \leq 80$ |
| $3$ | $16$ | $h, w \leq 500$ |
| $4$ | $32$ | $h, w \leq 2000$ |
| $5$ | $40$ | No additional constraints |

### Sample Test Case 1 Explanation

This test case is valid for subtasks $2$ to $5$.

If cells $(1, 1), (1, 2), (1, 3), (2, 1)$, or $(3, 1)$ were initially flooded, the entire grid would become flooded after the process. If cell $(3, 3)$ were initially flooded, only $1$ cell would become flooded after the process. Hence, the output is $9 + 9 + 9 + 9 + 9 + 1 = 46$.

### Sample Test Case 2 Explanation

This test case is valid for subtasks $2$ to $5$.

### Sample Test Case 3 Explanation

This test case is valid for all subtasks.



---

---
title: "[集训队互测 2024] 基础 01? 练习题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12473
tag: ['线段树', '集训队互测', '2024', '矩阵乘法', '扫描线']
---
# [集训队互测 2024] 基础 01? 练习题
## 题目描述

下标从 $0$ 开始的 $\texttt{01}$ 无穷序列 $P$ 由如下方式生成：

- $P_0=\texttt{0}$；
- $P_{2n}=P_{n}$；
- $P_{2n+1}=\texttt{1}-P_{n}$。

这里给出 $P$ 序列的前若干项：

$$
\texttt{01101001100101101001011001101001}\cdots
$$

方便起见，接下来将 $P$ 看做一个字符串，且字符串的下标均从 $0$ 开始。

定义 $f(S)$ 表示有限 $\texttt{01}$ 串 $S$ 是否为 $P$ 的子串，若是，则 $f(S)=1$，否则为 $0$。

定义 $g(S)$ 表示有限 $\texttt{01}$ 串 $S$ 中【是 $P$ 的子串】的子串个数，即：

$$
g(S)=\sum_{0\le l \le r < |S|}f(S_lS_{l+1}\cdots S_r)
$$

接下来定义 $h(S)$：对于一个仅包含 $\texttt{0,1,?}$ 的有限字符串 $S$ 中，将 $S$ 中 $\texttt{?}$ 各自替换成 $\texttt{0}$ 或 $\texttt{1}$，则 $h(S)$ 表示所有可能生成的 $\texttt{01}$ 串 $T$ 的 $g(T)$ 之和。

给定长度为 $n$ 的仅包含 $\texttt{0,1,?}$ 的字符串 $S$，有 $m$ 次询问，每次询问给出 $l,r$，求出 $h(S_lS_{l+1}\cdots S_r)$ 的值。

由于答案可能很大，所以输出答案对 $998244353$ 取模的结果。
## 输入格式

第一行两个正整数 $n,m$。

第二行一个长度为 $n$ 的仅包含 $\texttt{0,1,?}$ 的字符串 $S$。

接下来 $m$ 行，每行两个非负整数 $l,r$，表示一组询问。
## 输出格式

输出 $m$ 行，对于每组询问输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
4 4
??00
0 0
0 1
0 2
0 3
```
### 样例输出 #1
```
2
12
23
35
```
## 提示

### 样例 2

见下发文件，满足 $n,m \le 15$ 和特殊性质 C。

### 样例 3

见下发文件，满足 $n,m \le 100$ 和特殊性质 B。

### 样例 4

见下发文件，满足 $n,m \le 10^3$ 和特殊性质 BC。

### 样例 5

见下发文件，满足 $n,m \le 10^3$ 和特殊性质 A。

## 数据范围

对于 $100\%$ 的数据，$1\le n \le 5\times 10^4$，$1\le m \le 2\times 10^5$，$0\le l_1\le r_1 < n$，$0\le l_2\le r_2 < n$。

| 子任务 | $n\le$         | $m\le$         | 特殊性质 | 分值 |
| ----------- | -------------- | -------------- | -------- | ---- |
| 1           | $15$           | $15$           | A       | 10   |
| 2           | $20$           | $2\times 10^5$ | 无       | 10   |
| 3           | $5\times 10^4$ | $2\times 10^5$ | A        | 5    |
| 4           | $5\times 10^4$ | $1$            | BC       | 5    |
| 5           | $5\times 10^4$ | $1$            | C        | 15   |
| 6           | $500$          | $10^3$         | B        | 5    |
| 7           | $10^3$         | $2\times 10^3$ | BC        | 5    |
| 8           | $5\times 10^3$ | $10^5$         | C       | 10   |
| 9           | $2\times 10^4$ | $10^5$         | 无       | 15   |
| 10          | $5\times 10^4$ | $2\times 10^5$ | 无       | 20   |

特殊性质 A：$r-l+1 \le 15$；

特殊性质 B：$S$ 中 $\texttt{?}$ 的个数不超过 $8$；

特殊性质 C：$l=0$。


---

---
title: "[GDCPC 2024] 田字格"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13351
tag: ['树状数组', '2024', '广东', '扫描线', 'XCPC']
---
# [GDCPC 2024] 田字格
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

小 I 正在学习练字，可当他打开白纸时才想起来自己之前无聊在白纸上将 $n$ 条线段涂黑了，纸上其他部分都是白的。

这 $n$ 条被涂黑的线段都是水平的或者竖直的：以白纸中心为原点，平行白纸的某条边构建 $x$ 轴，另一条边构建 $y$ 轴，那么每条被涂黑的线段的两个端点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 满足：$x_1 = x_2$ 和 $y_1 = y_2$ 恰有一个成立。同时，任意两条水平的线段没有交点，任意两条竖直的线段没有交点。

尽管涂黑的线段很让小 I 糟心，深谙福祸相依的小 I 还是发现，涂黑的 $n$ 条线段构成了若干田字格，而他可以在这些田字格上练字。

田字格可以由三元组 $(x_0, y_0, d)$ 描述。一个三元组 $(x_0, y_0, d)$ 是田字格当且仅当以下条件成立：

- $x_0, y_0 \in \mathbb{R}$, $d \in \mathbb{R}^+$；
- 设 $R = [x_0-d,x_0+d] \times [y_0-d,y_0+d]$，即横坐标在 $[x_0-d,x_0+d]$ 内、纵坐标在 $[y_0-d,y_0+d]$ 内的所有点。那么 $R$ 中被涂黑的部分恰好构成六条线段，且这六条线段分别是 $x=x_0-d,x=x_0,x=x_0+d,y=y_0-d,y=y_0,y=y_0+d$ 这六条直线与 $R$ 的交。

小 I 于是想想算算白纸上有几个田字格，也就是有多少个满足以上条件的三元组 $(x_0,y_0,d)$。但按照惯例小 I 不会算，所以这个任务交给了你。
## 输入格式

输入的第一行一个整数 $n (1 \le n \le 3 \times 10^5)$ 表示线段数。接下来 $n$ 行每行四个整数 $x_1,y_1,x_2,y_2 (-10^9 \le x_1 \le x_2 \le 10^9, -10^9 \le y_1 \le y_2 \le 10^9)$ 表示一条线段。

输入的每条线段满足 $x_1 = x_2$ 和 $y_1 = y_2$ 恰有一个成立，且任意两条满足 $x_1 = x_2$ 的线段间没有交点，任意两条满足 $y_1 = y_2$ 的线段间没有交点。

## 输出格式

输出一行一个整数表示田字格的数量。
## 样例

### 样例输入 #1
```
10
-10 -10 -10 10
0 -10 0 10
10 -10 10 10
-10 -10 10 -10
-10 0 10 0
-10 10 10 10
5 -10 5 10
-10 5 10 5
-2 0 -2 10
-5 -5 10 -5
```
### 样例输出 #1
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/9hq95rak.png)

如上图所示，$(5, 5, 5), (5, 0, 5), (5, -5, 5)$ 是三个合法的田字格。注意以下几个都不是田字格：

- $(0, 0, 10)$，因为除了需要的六条线段以外还有其他部分被涂黑了；
- $(-5, 5, 5)$，因为 $x=-5$ 与正方形的交没有被涂黑。


---

---
title: "[OOI 2023] A task for substrings / 字符串问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13531
tag: ['堆', '2023', '扫描线', 'AC 自动机', 'Moscow Olympiad']
---
# [OOI 2023] A task for substrings / 字符串问题
## 题目背景

CF1801G
## 题目描述

菲利普非常喜欢关于字符串的小题目。他已经解完了所有他知道的相关题目，但这还不能让他满足。于是，菲利普决定自己出一道题。

为此，他准备了一个字符串 $t$，以及一个由 $n$ 个字符串 $s_1, s_2, s_3, \ldots, s_n$ 组成的集合。菲利普还有 $m$ 个查询，每个查询中，他会取出字符串 $t$ 的第 $l_i$ 到第 $r_i$ 个字符组成的子串，并统计其中有多少个子串和集合中的某个字符串完全相同。更正式地说，菲利普想要计算有多少对位置 $(a, b)$ 满足 $l_i \le a \le b \le r_i$，并且 $t$ 的第 $a$ 到第 $b$ 个字符组成的子串等于集合中的某个 $s_j$。

字符串 $t$ 的第 $a$ 到第 $b$ 个字符的子串，指的是从 $t$ 的开头删除 $a-1$ 个字符，从结尾删除 $|t|-b$ 个字符后剩下的字符串，其中 $|t|$ 表示 $t$ 的长度。

菲利普已经解决了这个问题，你能做到吗？
## 输入格式

第一行包含两个正整数 $n$ 和 $m$（$1 \le n, m \le 500\,000$），分别表示集合中字符串的数量和查询的数量。

第二行给出一个只包含小写英文字母的字符串 $t$（$1 \le |t| \le 5 \cdot 10^6$）。

接下来的 $n$ 行，每行包含一个集合中的字符串 $s_i$，每个 $s_i$ 仅包含小写英文字母。记 $S$ 为所有 $s_i$ 的总长度。保证 $S \le 10^6$，且所有 $s_i$ 互不相同。

接下来的 $m$ 行，每行包含两个正整数 $l_i$ 和 $r_i$（$1 \le l_i \le r_i \le |t|$），表示第 $i$ 个查询中子串的左右端点。

## 输出格式

输出 $m$ 个整数，第 $i$ 个数表示第 $i$ 个查询的答案。
## 样例

### 样例输入 #1
```
3 5
abacaba
aba
a
ac
1 7
1 3
2 7
2 5
4 5
```
### 样例输出 #1
```
7 3 5 3 1
```
### 样例输入 #2
```
4 4
abcdca
ab
ca
bcd
openolympiad
1 5
2 2
2 6
1 6
```
### 样例输出 #2
```
2 0 2 3
```
## 提示

### 样例解释

在第一个样例中，第一个查询要求统计整个字符串中属于集合的子串个数。字符串 "aba" 对应的子串有 $[1, 3]$ 和 $[4, 6]$，字符串 "a" 对应的子串有 $[1, 1]$、$[3, 3]$、$[5, 5]$、$[7, 7]$，字符串 "ac" 对应的子串有 $[3, 4]$。所以总共有 $7$ 个子串与集合中的字符串匹配。

在第二个查询中，取 $t$ 的第 $1$ 到第 $3$ 个字符，即字符串 "aba"。其中 "aba" 匹配 $1$ 次，"a" 匹配 $2$ 次，"ac" 不出现。

在第三个查询中，取 $t$ 的第 $2$ 到第 $7$ 个字符，即字符串 "bacaba"。其中 "aba" 匹配 $1$ 次，"a" 匹配 $3$ 次，"ac" 匹配 $1$ 次。

### 评分说明

本题测试点分为 9 组。只有通过某一组的所有测试点，且通过部分之前组的所有测试点，才能获得该组分数。**离线评测**表示该组测试结果会在比赛结束后公布。

| 组别 | 分值 | $n$ | $m$ | $\mid t\mid $ | $S$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:----:|:----:|:------------:|:-----|
| 0    | 0    | --  | --  | --   | --   | --           | 样例测试点 |
| 1    | 10   | $n \le 100$ | $m \le 100$ | $\mid t\mid  \le 100$ | $S \le 10\,000$ | 0 |  |
| 2    | 12   | $n \le 100$ | $m \le 500$ | $\mid t\mid \le 5000$ | -- | 0, 1 |  |
| 3    | 7    | $n \le 5000$ | -- | $\mid t\mid  \le 5000$ | -- | 0, 1, 2 |  |
| 4    | 8    | $n \le 100$ | -- | $\mid t\mid  \le 50\,000$ | -- | 0, 1, 2 |  |
| 5    | 12   | -- | -- | $\mid t \mid \le 100\,000$ | $S \le 100\,000$ | 0, 1 |  |
| 6    | 8    | -- | -- | $\mid t \mid \le 250\,000$ | $S \le 100\,000$ | 0, 1, 5 |  |
| 7    | 7    | -- | -- | $\mid t \mid \le 500\,000$ | $S \le 100\,000$ | 0, 1, 5, 6 |  |
| 8    | 7    | -- | -- | $\mid t \mid \le 750\,000$ | $S \le 100\,000$ | 0, 1, 5, 6, 7 |  |
| 9    | 29   | -- | -- | --   | --   | 0--8          | **离线评测** |



---

---
title: "「TPOI-5C」mαtrixing ωiθ μ"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13664
tag: ['线段树', 'O2优化', '树套树', '扫描线', '整体二分']
---
# 「TPOI-5C」mαtrixing ωiθ μ
## 题目背景

**本题禁止卡评测。**

![](https://cdn.luogu.com.cn/upload/image_hosting/qphit8fj.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)
## 题目描述

在东京的大雨后，天野阳菜给了 kele7 一个 $n$ 行 $m$ 列的矩阵 $A$。从上往下第 $i$ 行，从左往右第 $j$ 列的元素被称为 $A_{i,j}$。

kele7 喜欢删除矩阵。对于一个 $r$ 行 $c$ 列的矩阵 $B$，他会对它执行两种操作，同时会用**优雅值**衡量一个操作的优雅程度：

- 删除矩阵的某一行 $B_{i,1},\dots,B_{i,c}$，优雅值为 $\text{mex}_{j=1}^cB_{i,j}$。然后将第 $i+1\sim r$ 行往上平移一行，令 $r\leftarrow r-1$。
- 删除矩阵的某一列 $B_{1,i},\dots,B_{r,i}$，优雅值为 $\text{mex}_{j=1}^rB_{j,i}$。然后将第 $i+1\sim c$ 列往左平移一列，令 $c\leftarrow c-1$。

最终 kele7 要将矩阵内的元素全部删除（即 $r$ 或 $c$ 变为 $0$）。定义一种删除方案 $S$ 的权值 $f(S)$ 为其中所有操作的优雅值的**最小值**。定义矩阵 $B$ 的权值 $F(B)$ 为所有删除它的方案 $S$ 中 $f(S)$ 的**最大值**。

kele7 把这个题目给了 lzyqwq。lzyqwq 觉得还可以加上 $q$ 次查询，每次给出 $x_1,y_1,x_2,y_2$，你需要回答当矩阵 $B$ 为矩阵 $A$ 以 $A_{x_1,y_1}$ 为左上角元素、$A_{x_2,y_2}$ 为右下角元素的子矩阵时，$F(B)$ 的值。

一个集合 $M$ 的 $\operatorname{mex}(M)$ 定义为最小的没有在 $M$ 中出现的自然数。如 $\text{mex}\{1,2,3,4\}=0,\text{mex}\{0,1,3,4\}=2$。
## 输入格式

第一行三个正整数 $n,m,q$。

接下来 $n$ 行，每行 $m$ 个自然数。第 $i$ 行为 $A_{i,1},\dots,A_{i,m}$。

接下来 $q$ 行，每行四个整数 $x_1,y_1,x_2,y_2$ 表示一组询问。
## 输出格式

$q$ 行，每行一个自然数，表示一个询问的答案。
## 样例

### 样例输入 #1
```
5 5 5
0 1 0 1 2
3 2 0 1 4
5 4 3 0 1
0 2 0 3 1
0 0 0 1 2
1 1 5 5
2 2 4 4
1 2 4 5
3 2 4 4
1 2 2 3
```
### 样例输出 #1
```
2
1
2
1
1

```
## 提示

**【样例解释】**

以第一个询问为例。初始矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\3&2&0&1&4\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

一种可行的删除方案如下。

先删除第二行，优雅值为 $5$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

再删除第二列，优雅值为 $3$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&0&1&2\\5&3&0&1\\0&0&3&1\\0&0&1&2\end{bmatrix}$$

再依次删除所有行，优雅值分别为 $3,2,2,3$。

因此这种删除方案的权值为 $2$。可以证明，不存在优雅值的最小值更大的删除方案，因此答案为 $2$。

**【数据范围】**

|$\text{Subtask}$|$n,m$     |$q$       |特殊性质      |分值  |
|:--------:|:--------:|:--------:|:--------:|:--:|
|$0$       |$n\times m\le3\times10^5$|$q=1$     |无         |$11$|
|$1$       |$\color{red}{n,m\le300}$|$q\le10^5$|^         |^   |
|$2$       |$n\times m\le10^5$|^         |^         |$20$|
|$3$       |$n\times m\le2\times10^5$|$q\le2\times10^5$|^         |$24$|
|$4$       |$n\times m\le3\times10^5$|$q\le3\times10^5$|$x_1=y_1=1$|$8$ |
|$5$       |^         |^         |无         |$26$|

对于 $100\%$ 的数据，满足 $1\le n\times m,q\le 3\times 10^5$，$0\le A_{i,j}\le 10^9$。


---

---
title: "「TPOI-5D」「僕は…」"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13665
tag: ['字符串', 'O2优化', '分块', '扫描线']
---
# 「TPOI-5D」「僕は…」
## 题目背景

![](https://pic.kts.g.mi.com/e5e19c35ec3d824c4a6b5f7d094de6fd7605802814182560045.png)
## 题目描述

由于你让我看到了世界的绮丽，所以需要解决一道题目。

定义 $f(a,b)$ 为字符串 $a$ 在 $b$ 中出现的次数。

给出 $n$ 个字符串 $s_1,\dots,s_n$，$q$ 次询问 $l,r,L,R$，求：

$$\sum\limits_{i=l}^r\sum\limits_{j=L}^Rf(s_i,s_j)$$
## 输入格式

第一行输入两个正整数 $n,q$。

接下来 $n$ 行输入 $n$ 个字符串 $s_1,\dots,s_n$。

接下来 $q$ 行输入 $q$ 个询问 $l,r,L,R$。
## 输出格式

输出 $q$ 个正整数，为每个询问的答案。
## 样例

### 样例输入 #1
```
5 5
a
ab
abab
ababab
b
1 5 4 5
3 5 4 5
1 5 2 4
1 5 3 5
2 4 3 4

```
### 样例输出 #1
```
13
7
22
20
9

```
## 提示

记 $m=\sum\limits_{i=1}^n|s_i|$。

| $\text{Subtask}$ | $n,m,q\le$ |特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^2$ | 无 | $5$ | 
| $2$ | $2\times 10^5$ | 所有字符串均为 `a` | ^ |
| $3$ | $10^4$ | 无 | $10$ |
| $4$ | $2\times 10^5$ | 所有字符串的长度不超过 $10$ | ^ |
| $5$ | ^ | $n\le 10^2$ | ^ |
| $6$ | $5\times 10^4$ | 无 | $20$ |
| $7$ | $2\times 10^5$ | ^ | $40$ |



对于 $100\%$ 的数据，满足 $1\le n,m,q\le 2\times 10^5$，$1\le l\le r\le n$，$1\le L\le R\le n$。


---

---
title: "[USACO21JAN] Sum of Distances P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7293
tag: ['动态规划 DP', '线段树', 'USACO', '2021', 'O2优化', '组合数学', '容斥原理', '扫描线']
---
# [USACO21JAN] Sum of Distances P
## 题目描述

Bessie 有一些无向连通图 $G_1,G_2,…,G_K$（$2≤K≤5⋅10^4$）。对于每一个 $1≤i≤K$，$G_i$ 有 $N_i$（$N_i≥2$）个编号为 $1…N_i$ 的结点与 $M_i$（$M_i≥N_i−1$）条边。$G_i$ 可能含有自环，但同一对结点之间不会存在多条边。 现在 Elsie 用 $N_1⋅N_2⋯N_K$ 个结点建立了一个新的无向图 $G$，每个结点用一个 $K$ 元组 $(j_1,j_2,…,j_K)$ 标号，其中 $1≤j_i≤N_i$。若对于所有的 $1≤i≤K$，$j_i$ 与 $k_i$ 在 $G_i$ 中连有一条边，则在 $G$ 中结点 $(j_1,j_2,…,j_K)$ 和 $(k_1,k_2,…,k_K)$ 之间连有一条边。 定义 $G$ 中位于同一连通分量的两个结点的 *距离* 为从一个结点到另一个结点的路径上的最小边数。计算 $G$ 中结点 $(1,1,…,1)$ 与所有与其在同一连通分量的结点的距离之和，对 $10^9+7$ 取模。
## 输入格式

输入的第一行包含 $K$，为图的数量。

每个图的描述的第一行包含 $N_i$ 和 $M_i$，以下是 $M_i$ 条边。

为提高可读性，相邻的图之间用一个空行隔开。输入保证 $∑N_i≤10^5$ 以及 $∑M_i≤2⋅10^5$。
## 输出格式

输出结点 $(1,1,…,1)$ 与所有该结点可以到达的结点的距离之和，对 $10^9+7$ 取模。


## 样例

### 样例输入 #1
```
2

2 1
1 2

4 4
1 2
2 3
3 4
4 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3

4 4
1 2
2 3
3 1
3 4

6 5
1 2
2 3
3 4
4 5
5 6

7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1
```
### 样例输出 #2
```
706
```
## 提示

#### 样例 1 解释

$G$ 包含 $2⋅4=8$ 个结点，其中 $4$ 个结点不与结点 $(1,1)$ 连通。有 $2$ 个结点与 $(1,1)$ 的距离为 $1$，$1$ 个结点的距离为 $2$。所以答案为 $2⋅1+1⋅2=4$。 

#### 样例 2 解释

$G$ 包含 $4⋅6⋅7=168$ 个结点，均与结点 $(1,1,1)$ 连通。对于每一个 $i∈[1,7]$，与结点 $(1,1,1)$ 距离为 $i$ 的结点数量为下列数组中的第 $i$ 个元素：$[4,23,28,36,40,24,12]$。

#### 测试点特性

 - 测试点 $3-4$ 满足 $∏N_i≤300$。
 - 测试点 $5-10$ 满足 $∑N_i≤300$。
 - 测试点 $11-20$ 没有额外限制。

供题：Benjamin Qi 


---

---
title: "[JSOI2016] 炸弹攻击1 - 数据加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8061
tag: ['计算几何', '2016', '各省省选', '江苏', 'Special Judge', '扫描线']
---
# [JSOI2016] 炸弹攻击1 - 数据加强版
## 题目背景

JYY 最近迷上了一款塔防游戏，在游戏里 JYY 除了建设建筑，还可以使用炸弹对屏幕上的敌人进行范围杀伤。
## 题目描述

游戏地图可以简单认为是一个二维平面。JYY 建造了 $N $ 个建筑，每个建筑都是一个圆，其中第 $i$ 个建筑的圆心位于 $(x_i,y_i)$ 且半径为 $r_i$。地图上一共有 $M$ 个敌人，一个敌人可以近似看成一个平面上的点，其中第 $i$ 个敌人位于 $(p_i,q_i)$。JYY 可以使用一枚可以设置半径的炸弹，可以设置一个不超过 $R$ 的范围，然后选择平面上的一个点引爆，范围内的所有敌人全部消灭。

当然，由于炸弹威力巨大，如果爆炸范围接触到 JYY 的建筑，那么 JYY 的建筑也会受到损伤。（注：如果炸弹的爆炸范围仅接触到了 JYY 建筑的边界，则不会对 JYY 的建筑造成损伤；如果敌人出现在了爆炸范围的边界，则该敌人被消灭）JYY 可以自由控制炸弹的爆炸地点和爆炸半径。作为一个保守的玩家，他希望在保证自己建筑毫发无损的情况下，消灭尽量多的敌人。
## 输入格式

第一行包含三个非负整数，分别为 $N,M,R$；

接下来 $N$ 行，每行三个整数，其中第 $i$ 行 $x_i,y_i,r_i$，表示第 $i$ 个建筑的位置和半径。数据保证所有建筑不相交（但是有可能边界接触）；

接下来 $M$ 行，每行两个整数，其中第 $i$ 行为 $p_i,q_i$，表示第 $i$ 个敌人的位置。任意两个敌人的位置不同，且敌人不会出现在建筑里。
## 输出格式

输出一行一个整数，表示 JYY 最多可以消灭的敌人数量。
## 样例

### 样例输入 #1
```
1 3 3
0 0 1
3 3
-3 3
3 -3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
1 5 3
0 0 1
3 3
-3 3
3 -3
3 0
0 3
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
4 10 100
0 0 3
10 0 3
10 10 3
0 10 3
0 4
0 5
0 6
5 3
5 -3
5 5
6 7
3 6
10 4
8 4
```
### 样例输出 #3
```
5
```
## 提示

对于 $100\%$ 的数据，满足 $1\leq N\leq 10$，$1\leq M\leq 2000$，$1\leq R,r_i\leq 2\times 10^4$，$|p_i|,|q_i|,|x_i|,|y_i|\leq 2\times 10^4$。

数据来源于 NAIPC 2015 Problem A - Area of Effect，并有部分自造新数据。


---

---
title: "[USACO22FEB]  Paint by Rectangles P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8192
tag: ['线段树', 'USACO', '2022', '平面图欧拉公式', '扫描线']
---
# [USACO22FEB]  Paint by Rectangles P
## 题目背景

翻译来自 @wlzhouzhuan。
## 题目描述

在她之前的作品受到好评后，Bessie 得到了一份设计绘画套装的工作。她通过在平面中选择 $N\ (1\le N\le 10^5)$ 个平行于坐标轴的矩形来设计该画作，没有两条边是共线的。这些矩形的边界定义了绘画着色区域的边界。

作为一名先锋艺术家，Bessie 觉得这幅画应该像一头荷斯坦奶牛。更具体地，由矩形构成的每个区域都被着色为黑色或白色，没有两个相邻区域具有相同的颜色，并且所有矩形之外的区域都被着色为白色。

选完矩形后，Bessie 想根据参数 $T$ 让你输出：

- 若 $T=1$，则输出区域总数；
- 若 $T=2$，则依次输出白色区域数量和黑色区域数量。

**注意：本题的时间限制为 4s，是默认的 2 倍。**
## 输入格式

第一行，输入 $N$ 和 $T$。

接下来 $N$ 行，每行读入 $x_1,y_1,x_2,y_2$，表示一个左下角为 $(x_1,y_1)$，右上角为 $(x_2,y_2)$ 的矩形。

数据保证 $x_i$ 形成了一个 $1\sim 2N$ 的排列，$y_i$ 同理。
## 输出格式

若 $T=1$，输出一个整数；否则输出两个整数，用空格隔开。
## 样例

### 样例输入 #1
```
2 1
1 1 3 3
2 2 4 4 
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5 2
1 5 3 6
5 4 7 9
4 1 8 3
9 8 10 10
2 2 6 7
```
### 样例输出 #2
```
4 5
```
## 提示

**【样例解释 #1】**

有 $2$ 个白色区域和 $2$ 个黑色区域，共有 $4$ 个区域。所有矩形的边界连通，因此该输入满足 subtask 3。

![](https://cdn.luogu.com.cn/upload/image_hosting/v34kpbhi.png)

**【样例解释 #2】**

右上方的矩形不与其余的矩形连通，因此该输入不满足 subtask 4。

![](https://cdn.luogu.com.cn/upload/image_hosting/boqnrha0.png)

**【数据范围】**

- subtask 1：数据 $3\sim 4$ 满足 $N\le 10^3$；
- subtask 2：数据 $5\sim 7$ 满足不存在两个矩形相交；
- subtask 3：数据 $8\sim 10$ 满足 $T=1$，且所有矩形的边界连通；
- subtask 4：数据 $11\sim 13$ 满足 $T=2$，且所有矩形的边界连通；
- subtask 5：数据 $14\sim 18$ 满足 $T=1$；
- subtask 6：数据 $19\sim 23$ 满足 $T=2$。


---

---
title: "「GMOI R2-T4」电子木鱼"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9201
tag: ['洛谷原创', 'O2优化', '动态树 LCT', '扫描线', '基环树', '洛谷月赛', '分类讨论']
---
# 「GMOI R2-T4」电子木鱼
## 题目背景

运营电子资本，招聘赛博佛祖，积累虚拟功德。

功德无量，随喜赞叹。

111
## 题目描述

给你 $n$，表示一共有 $n$ 位赛博佛祖，编号依次为 $1 \sim n$。

第 $i\ (1 \leq i \leq n)$ 位赛博佛祖可以对应为一个二元组 $\langle S_i, d_i \rangle$，其中 $S$ 在任意时刻均为 $\{1, 2, 3, \dots, m\}$ 的一个子集（可以为空），而 $d_i$ 为 $1 \sim m$ 间的整数。

如果在某一时刻，存在一位赛博佛祖的 $S_i$ 为空集，佛祖会感到很开心而给你加功德。具体地，他会敲响第 $d_i$ 个木鱼，并 **在下一时刻同时** 影响所有的 $n$ 位赛博佛祖（包括他自己）。对第 $j(1 \leq j \leq n)$ 位赛博佛祖，如果 $d_i \in S_j$，那么将从 $S_j$ 内删去 $d_i$；否则向 $S_j$ 内加入 $d_i$。如果有多位赛博佛祖的 $S_i$ 为空集，取编号最小的 $i$ 为你加功德。

现在作为电子资本家的你，想要功德无量。你想知道，最少再请来几位赛博佛祖，可以使得你的这些佛祖们 **源源不断地** 为你加功德。假设这个答案是 $s$（可以为 $0$），那么新的佛祖们的编号依次为 $(n+1) \sim (n+s)$。

**因为你是个资本家，有时候你不想请那么多佛祖**。所以你有许多组询问，对于一组 $l, r$，设 $f(l, r)$ 表示如果初始只有 $[l, r]$ 之间的佛祖，答案将会是多少，注意，每组询问相互独立，上一次添加的佛祖不会延续到以后的询问中。

为了避免太多的输出，你只需要输出： 

$$\sum\limits_{l=1}^n\sum\limits_{r=l}^n f(l,r)\times2^l$$

即可，答案对 $10^9 + 7$ 取模。
## 输入格式

第一行，两个整数 $n, m$。

接下来 $n$ 行，第 $i$ 行首先一个整数描述 $d_i$，接着一个长度为 $m$ 的 $\texttt{01}$ 字符串表示 $S_i$。如果第 $j$ 个字符为 $1$，表示 $j \in S_i$；否则 $j \notin S_i$。
## 输出格式

一行，表示最终答案取模后的值。
## 样例

### 样例输入 #1
```
4 3
1 010
2 001
3 000
3 001
```
### 样例输出 #1
```
52
```
### 样例输入 #2
```
5 4
1 1000
4 0100
1 0000
2 0001
2 0000
```
### 样例输出 #2
```
128
```
## 提示

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（10 pts）：$n \leq 10$，$m \leq 5$。
- Subtask 1（10 pts）：$n \leq 300$，$m \leq 10$。
- Subtask 2（15 pts）：$n \leq 1024$，$m \leq 10$。保证每个 $S_i$ 均不同。
- Subtask 3（15 pts）：$n \leq 10^4$。
- Subtask 4（10 pts）：每个 $S_i$ 均在 $2^m$ 种情况中等概率随机生成，$d_i$ 均在 $m$ 种情况中等概率随机生成。
- Subtask 5（40 pts）：无特殊限制。

对于所有数据，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 17$。


---

