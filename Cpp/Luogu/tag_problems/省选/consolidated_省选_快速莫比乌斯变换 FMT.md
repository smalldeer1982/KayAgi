---
title: "[NWRRC2024] Longest Common Substring"
layout: "post"
diff: 省选/NOI-
pid: P12116
tag: ['动态规划 DP', '2024', '快速莫比乌斯变换 FMT', 'ICPC', '状压 DP', '俄罗斯西北']
---
# [NWRRC2024] Longest Common Substring
## 样例

### 样例输入 #1
```
2 2 1
1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 4 2
01
```
### 样例输出 #2
```
28
```
### 样例输入 #3
```
7 5 3
110
```
### 样例输出 #3
```
399
```
### 样例输入 #4
```
23 42 3
000
```
### 样例输出 #4
```
174497840
```


---

---
title: "集合幂级数 exp"
layout: "post"
diff: 省选/NOI-
pid: P12230
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数 exp
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)=0$。定义 $x$ 的乘法为子集卷积，你需要对所有 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]e^{F(x)}$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]e^{F(x)}$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
0 1 2 3
```
### 样例输出 #1
```
1 1 2 5
```
### 样例输入 #2
```
4
0 11 83 73 34 53 72 57 81 92 10 31 44 33 93 10
```
### 样例输出 #2
```
1 11 83 986 34 427 2894 38772 81 983 6733 87643 2798 38232 238499 3459260
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)=0$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

根据泰勒展开，有：
$$e^{F(x)}=\sum_{n\ge 0}\frac{F^n(x)}{n!}$$


---

---
title: "集合幂级数 ln"
layout: "post"
diff: 省选/NOI-
pid: P12231
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数 ln
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)=1$。定义 $x$ 的乘法为子集卷积，可以证明存在一个 $G(x)$ 满足 $e^{G(x)}=F(x)$，你需要对 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]G(x)$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]G(x)$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
1 2 3 4
```
### 样例输出 #1
```
0 2 3 998244351
```
### 样例输入 #2
```
4
1 8 3 9 2 0 1 8 7 0 0 1 7 3 4 1
```
### 样例输出 #2
```
0 8 3 998244338 2 998244337 998244348 78 7 998244297 998244332 274 998244346 171 60 998242876
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)=1$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

根据泰勒展开，有：
$$e^{F(x)}=\sum_{n\ge 0}\frac{F^n(x)}{n!}$$

可以证明本题答案唯一。


---

---
title: "集合幂级数求逆"
layout: "post"
diff: 省选/NOI-
pid: P12232
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数求逆
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)\neq 0$。定义 $x$ 的乘法为子集卷积，可以证明存在一个 $G(x)$ 满足 $F(x)G(x)=1$，你需要对 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]G(x)$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]G(x)$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
1 2 3 4
```
### 样例输出 #1
```
1 998244351 998244350 8
```
### 样例输入 #2
```
4
1 1 4 5 1 4 1 9 1 9 8 1 0 1 2 3
```
### 样例输出 #2
```
1 998244352 998244349 3 998244352 998244351 7 11 998244352 998244346 0 73 2 19 998244345 998244164
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)\neq 0$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

可以证明本题答案唯一。


---

---
title: "[NERC 2022] Game of Questions"
layout: "post"
diff: 省选/NOI-
pid: P12796
tag: ['2022', 'Special Judge', '快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', 'ICPC', '状压 DP', 'NERC/NEERC']
---
# [NERC 2022] Game of Questions
## 题目描述

Genie is taking part in an intellectual game. The game consists of $n$ questions, and there are $m$ participants numbered from $1$ to $m$. Genie is the participant number $1$.

For each question $i$ and participant $j$, it is known whether the participant will answer the question correctly or not.

The goal of the game is to be the last participant staying in the game.

The game is conducted as follows. First, all $n$ questions get shuffled uniformly at random (all $n!$ permutations are equally likely). Then, the questions are asked one by one. Each participant answers the question. If all participants still in the game answer the question correctly, or if all of them answer the question incorrectly, nothing happens. Otherwise, those participants who answer the question incorrectly lose and leave the game.

After all $n$ questions are asked, all participants who are still in the game are declared to be the winners.

What is the probability that Genie will win the game?
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of questions and the number of participants ($1 \le n \le 2 \cdot 10^5$; $2 \le m \le 17$).

The $i$-th of the next $n$ lines contains $m$ characters $s_{i, 1}, s_{i, 2}, \ldots, s_{i, m}$. Character $s_{i, j}$ is $\tt{1}$ if participant $j$ answers question $i$ correctly or $\tt{0}$ otherwise.
## 输出格式

Print the probability that Genie will win the game. Your answer will be considered correct if its absolute or relative error does not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
1 5
11010
```
### 样例输出 #1
```
1.0000000000000000
```
### 样例输入 #2
```
3 3
011
101
110
```
### 样例输出 #2
```
0.3333333333333333
```
### 样例输入 #3
```
6 4
1011
0110
1111
0110
0000
1101
```
### 样例输出 #3
```
0.1666666666666667
```
## 提示

In the first example, there is a single question and Genie will answer it correctly, thus winning the game (along with participants $2$ and $4$).

In the second example, one participant will leave after the first asked question, and another participant will leave after the second asked question. Each participant will win with probability $\frac{1}{3}$.


---

---
title: "【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)"
layout: "post"
diff: 省选/NOI-
pid: P4717
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT']
---
# 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
## 题目描述

给定长度为 $2^n$ 两个序列 $A,B$，设 

$$C_i=\sum_{j\oplus k = i}A_j \times B_k$$

分别当 $\oplus$ 是 or, and, xor 时求出 $C$。
## 输入格式

第一行，一个整数 $n$。  
第二行，$2^n$ 个数 $A_0, A_1, \ldots, A_{2^n-1}$。  
第三行，$2^n$ 个数 $B_0, B_1, \ldots, B_{2^n-1}$。

## 输出格式

三行，每行 $2^n$ 个数，分别代表 $\oplus$ 是 or, and, xor 时 $C_0, C_1, \ldots, C_{2^n-1}$ 的值 $\bmod\ 998244353$。

## 样例

### 样例输入 #1
```
2
2 4 6 8
1 3 5 7

```
### 样例输出 #1
```
2 22 46 250
88 64 112 56
100 92 68 60

```
## 提示

$1 \le n \le 17$。


---

---
title: "【模板】子集卷积"
layout: "post"
diff: 省选/NOI-
pid: P6097
tag: ['O2优化', '快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 【模板】子集卷积
## 题目背景

这是一道模板题。
## 题目描述

给定两个长度为 $2^n$ 的序列 $a_0,a_1,\cdots,a_{2^n-1}$ 和 $b_0,b_1,\cdots,b_{2^n-1}$，你需要求出一个序列 $c_0,c_1,\cdots,c_{2^n-1}$，其中 $c_k$ 满足：

$$c_k=\sum_{\substack{{i \& j=0}\\{i~\mid~ j=k}}} a_i b_j$$

其中$~\mid~$表示按位或，$\&$表示按位与。

答案对 $10^9+9$ 取模。
## 输入格式

第一行输入一个正整数 $n$ ，表示集合的大小。

第二行有 $2^n$ 个整数，描述了 $a$。

第三行有 $2^n$ 个整数，描述了 $b$。
## 输出格式

输出一行 $2^n$ 个整数，表示 $c$。
## 样例

### 样例输入 #1
```
2
1 0 2 1
2 0 2 1
```
### 样例输出 #1
```
2 0 6 3
```
## 提示

对于所有数据，$1\le n\le 20$，$0\le a_i,b_i< 10^9+9$。


---

