---
title: "「ALFR Round 3」C 割"
layout: "post"
diff: 普及/提高-
pid: P11447
tag: ['字符串', '贪心', '洛谷原创', 'O2优化', '鸽笼原理', '洛谷月赛']
---
# 「ALFR Round 3」C 割
## 题目背景

[English Statement](https://www.luogu.com.cn/problem/U517305).

**upd:** 添加的 hack 在 Sub 7。
## 题目描述

设 $f(S)$ 表示字符串 $S$ 字典序最大的子序列，给定 $k$，你需要将原字符串 $S$ 分割成 $k$ 段，设第 $i$ 段子串为 $a_i$，则该分割方案的权值为 $\max f(a_i)$，其中 $1\le i\le k$。由于分割方案有很多种，你需要求出所有分割方案中**字典序最小的权值**。

注：这里的权值实际上指的是字符串。

关于子序列的定义：某个序列的子序列是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。

关于字典序的定义：在字典序中，首先比较两个字符串的第一个字符，如果不同，则第一个字符较小的字符串更小；如果相同，则继续比较下一个字符，依此类推，直到比较完所有字符。如果一个字符串是另一个字符串的前缀，则较短的字符串更小。
## 输入格式

输入共两行。

第一行两个整数 $n,k$，$n$ 表示字符串 $S$ 的长度，$k$ 表示你需要将字符串分割为 $k$ 段。

第二行为一个字符串，即 $S$。
## 输出格式

输出一个字符串表示所有分割方案中字典序最小的权值。
## 样例

### 样例输入 #1
```
7 2
skyaqua
```
### 样例输出 #1
```
y
```
## 提示

### 样例解释
可以将字符串 $S$ 分割成 `sky`、`aqua` 这 $2$ 段，这 $2$ 段的 $f$ 分别为 `y`、`ua`，其中字典序最大的 $f$ 为 `y`，所以该分割方案的权值为 `y`。可以证明 `y` 是所有分割方案中字典序最小的权值。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $n\le 10$ |
| $2$ | $20$ | $n\le 10^2$ |
| $3$ | $20$ | $n\le 3\times 10^2$| 
| $4$ | $10$ | 保证字符串 $S$ 中所有字符都相等 |
| $5$ | $10$ | $k=1$ |
| $6$ | $30$ | - |

对于 $100\%$ 的数据，$1\le k\le n\le 2\times10^5$，且字符串 $S$ 中的字符均为小写英文字母。


---

---
title: "[NWRRC 2023] Divisibility Trick"
layout: "post"
diff: 普及/提高-
pid: P13584
tag: ['2023', 'Special Judge', '鸽笼原理', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Divisibility Trick
## 题目描述

Dmitry has recently learned a simple rule to check if an integer is divisible by 3. An integer is divisible by 3 if the sum of its digits is divisible by 3.

Later he also learned that the same rule can be used to check if an integer is divisible by 9. An integer is divisible by 9 if the sum of its digits is divisible by 9.

Dmitry's elder sister Daria wants to trick him by showing that the same rule can be applied to any divisor~$d$. To do this, she wants to show Dmitry an example of a positive integer $n$ such that $n$ is divisible by $d$, and the sum of the digits of $n$ is also divisible by $d$. Help her to find such a number.
## 输入格式

The only line contains a single integer $d$ ($1\le d\le 1000$).
## 输出格式

Print a positive integer $n$ divisible by $d$ such that the sum of its digits is also divisible by $d$.

The value of $n$ must consist of at most $10^6$ digits and must not have leading zeroes. It can be shown that such an integer always exists. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
13
```
### 样例输出 #2
```
1898
```
### 样例输入 #3
```
1
```
### 样例输出 #3
```
239
```
## 提示

In the first example, $3$ is divisible by $3$, and its sum of digits, $3$, is also divisible by $3$.

In the second example, $1898$ is divisible by $13$, and its sum of digits, $1 + 8 + 9 + 8 = 26$, is also divisible by $13$.

In the third example, any positive integer satisfies the conditions.


---

---
title: "[蓝桥杯 2022 国 C] 取模"
layout: "post"
diff: 普及/提高-
pid: P8807
tag: ['2022', '数论', '枚举', '鸽笼原理', '蓝桥杯国赛']
---
# [蓝桥杯 2022 国 C] 取模
## 题目描述

给定 $n, m$，问是否存在两个不同的数 $x,y$ 使得 $1 \le x < y \le m$ 且 $n \bmod x = n \bmod ⁡y$。
## 输入格式

输入包含多组独立的询问。

第一行包含一个整数 $T$ 表示询问的组数。

接下来 $T$ 行每行包含两个整数 $n,m$，用一个空格分隔，表示一组询问。
## 输出格式

  输出 $T$ 行，每行依次对应一组询问的结果。如果存在，输出单词 `Yes`；如果不存在，输出单词 `No`。
## 样例

### 样例输入 #1
```
3
1 2
5 2
999 99
```
### 样例输出 #1
```
No
No
Yes
```
## 提示

对于 $20\%$ 的评测用例，$T \le 100$，$n, m \le 1000$；

对于 $50\%$ 的评测用例，$T \le 10000$，$n, m \le 10^5$；

对于所有评测用例，$1\le T \le 10^5$，$1\le n\le 10^9$，$2\le m \le 10^9$。

蓝桥杯 2022 国赛 C 组 C 题。


---

