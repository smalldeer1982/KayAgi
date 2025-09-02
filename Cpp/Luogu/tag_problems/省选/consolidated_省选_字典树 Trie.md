---
title: "[USACO24OPEN] Identity Theft P"
layout: "post"
diff: 省选/NOI-
pid: P10283
tag: ['贪心', 'USACO', '2024', '字典树 Trie']
---
# [USACO24OPEN] Identity Theft P
## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**
## 题目描述

Farmer John 的 $N$（$1\le N\le 10^5$）头奶牛每头都有一个二进制字符串（由字符 `0` 和 `1` 组成的字符串）形式的农场证号。Bessie，最年长的奶牛，记住了所有奶牛的农场证号，还喜欢到处询问奶牛她们的农场证号。

当一头奶牛被询问她的农场证号时，她们会开始报正确的二进制字符串，但有可能会感到困惑并在报完之前停下来。当 Bessie 听到该二进制字符串时，如果它不等于农场上任何一头奶牛的农场证号，她就会耸耸肩走开。然而，如果它等于不同于她所询问的奶牛的另一头奶牛的农场证号，那么她就会认为发生了身份盗用并封锁整个农场。注意，这种情况即使当奶牛报出完整的农场证号时也可能发生。

Farmer John 希望防止这种情况发生，并愿意以添加更多二进制位的方式改变奶牛的农场证号。他可以在一秒钟内在任意一头牛的农场证号末尾添加一个二进制位。求出他所需要的最小时间以防止封锁发生。 
## 输入格式

输入的第一行包含 $N$，为 Farmer John 的农场上的奶牛数量。

以下 $N$ 行，第 $k$ 行包含表示 Farmer John 的农场上第 $k$ 头奶牛的农场证号的二进制字符串。

所有奶牛的农场证号均不为空，且所有农场证号的总长度不超过 $10^6$。 
## 输出格式

输出 Farmer John 需要花费的最小秒数以确保封锁不会发生。 
## 样例

### 样例输入 #1
```
3
1
1
1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3
1
11
111
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
1
1
11
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
5
0
01
0011
010
01
```
### 样例输出 #4
```
6
```
### 样例输入 #5
```
14
0
1
1
0
1
0
1
1
1
1
1
0
0
1
```
### 样例输出 #5
```
41
```
## 提示

### 样例解释 1

这一样例满足第一个子任务的性质。

我们可以花费 5 秒使得封锁不可能发生，通过对第一个农场证号添加 `0`，对第二个农场证号添加 `10`，对第三个农场证号添加 `11`，使农场证号变为 `10`，`110` 和 `111`。

你可以证明这不可能在 4 秒或更少的时间内完成。例如，如果你保持所有农场证号不变，则所有 3 头奶牛都具有相同的农场证号 `1`，因此当 Bessie 听到它时，它将始终等于另一头奶牛的农场证号。

作为另一个例子，如果你仅花费 2 秒对第二个农场证号添加 `0`，对第三个农场证号添加 `1`，则农场证号变为 `1`，`10` 和 `11`，因此第二头和第三头奶牛在报她们的农场证号时，可能会停在中间只报出 `1`，而这将等于第一头奶牛的农场证号。

### 样例解释 2

我们可以在 2 秒内使得封锁不可能发生，通过对前两个农场证号添加 `0`，像之前一样使农场证号变为 `10`，`110` 和 `111`。你可以证明这不可能在 1 秒内完成。

### 样例解释 3

我们可以在 4 秒内使得封锁不可能发生，通过对第一个农场证号添加 `00`，对第二个农场证号添加 `01`。你可以证明这不可能在 3 秒或更少的时间内完成。

### 样例解释 5

这一样例满足第一个子任务的性质。

### 测试点性质

- 测试点 $6-7$：所有农场证号的长度均恰好为 $1$。
- 测试点 $8-15$：$N\le 10^2$，且所有农场证号的总长度不超过 $10^3$。
- 测试点 $16-25$：没有额外限制。


---

---
title: "【MX-X2-T4】「Cfz Round 4」Gcd with Xor"
layout: "post"
diff: 省选/NOI-
pid: P10855
tag: ['数学', '数论', 'O2优化', '莫比乌斯反演', '容斥原理', '字典树 Trie', '梦熊比赛']
---
# 【MX-X2-T4】「Cfz Round 4」Gcd with Xor
## 题目背景

原题链接：<https://oier.team/problems/X2D>。

---

ねえ もしも全て投げ捨てられたら  
呐 若然能将一切舍弃的话

笑って生きることが楽になるの  
笑着活下去这样的事就会变的轻松吗
## 题目描述

给定两个正整数 $n,k$。

定义 $\displaystyle f(x)=\sum_{i=1}^x \gcd(i,i\oplus x)^k$。计算 $\displaystyle \sum_{i=1}^n f(i)$。其中 $\gcd(a,b)$ 表示 $a$ 和 $b$ 的最大公因数，$\oplus$ 表示**按位异或**，即 C++ 中的 `^`。

由于答案可能很大，所以你只需要输出答案对 $10^9+7$ 取模的结果。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据，输入一行两个正整数 $n,k$。
## 输出格式

对于每组测试数据，输出一行一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5
3 2
10 1
261 261
2333 2333
124218 998244353
```
### 样例输出 #1
```
17
134
28873779
470507314
428587718

```
## 提示

**【样例解释】**

对于第 $1$ 组测试数据：

$f(1)=\gcd(1,0)^2=1$。

$f(2)=\gcd(1,3)^2+\gcd(2,0)^2=5$。

$f(3)=\gcd(1,2)^2+\gcd(2,1)^2+\gcd(3,0)^2=11$。

$f(1)+f(2)+f(3)=17$。

**【数据范围】**

对于所有测试数据，$1\le T\le 1000$，$1\le n\le 2\times 10^5$，$\sum n\le 2\times 10^5$，$1\le k\le 10^9$。

**本题采用捆绑测试。**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

- Subtask 1（10 points）：$\sum n\le 2000$。
- Subtask 2（12 points）：$\sum n\le 10^4$。
- Subtask 3（15 points）：$k=1$。
- Subtask 4（45 points）：$\sum n\le 10^5$。
- Subtask 5（18 points）：无特殊限制。


---

---
title: "【MX-X6-T6】機械生命体"
layout: "post"
diff: 省选/NOI-
pid: P11160
tag: ['O2优化', '字典树 Trie', '梦熊比赛']
---
# 【MX-X6-T6】機械生命体
## 题目背景

原题链接：<https://oier.team/problems/X6G>。

---

> _許してよ、もう$\\$
分かってよ$\\$
此処の正体を$\\$
僕ですら僕を$\\$
愛せないんだって$\\$
感情を持った代償をくれよ$\\$
狂っている_
>
> _—— [機械生命体 - Nanatsukaze](https://music.163.com/#/song?id=2627128854)_

二进制的运算和记忆，能够在机械生命体中还原出人类的情感吗？
## 题目描述

维护一个**可重集** $S$，初始为空。支持如下操作：

- `1 x`，你需要在 $S$ 中加入一个数 $x$。
- `2 x`，你需要在 $S$ 中删除一个数 $x$。保证此时 $S$ 中存在至少一个 $x$。如果存在多个 $x$，则仅删除一个。
- `3 x k v`，你需要对 $S$ 中所有满足 $\operatorname{lowbit}(x\oplus y)\geq 2^k$ 的 $y$ 增加 $v$ 并对 $2^{32}$ 取模。
- `4 x`，你需要求出 $\max\limits_{y\in S} \operatorname{lowbit}(x\oplus y)$。保证此时 $S$ 不为空。

其中 $\operatorname{lowbit}(x)$ 表示最大的整数 $k$，使得 $k$ 是 $2$ 的整数次幂并且整除 $x$。$\oplus$ 代表[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677)。

**特殊的，我们在本题定义 $\boldsymbol{\textbf{lowbit}(0)=2^{32}}$。**
## 输入格式

第一行一个整数 $q$，代表询问数量。

接下来 $q$ 行，每行首先输入一个整数 $opt$ 表示操作类型；如果 $opt=3$，则接下来依次输入三个整数 $x,k,v$，否则接下来输入一个整数 $x$。
## 输出格式

对每一次 `4` 操作，输出一个整数代表答案。
## 样例

### 样例输入 #1
```
11
1 1
1 2
1 2
1 3
1 4
4 10
3 2 1 2
2 4
4 16
2 4
4 16
```
### 样例输出 #1
```
8
4
2
```
## 提示

**【样例解释】**

第 $6$ 次操作时，集合为 $\{1,2,2,3,4\}$，查询 $10$ 时，$\operatorname{lowbit}(10\oplus 2)=\operatorname{lowbit}(8)=8$ 为最大值。

第 $7$ 次操作后，所有 $\operatorname{lowbit}(x\oplus 2)\geq 2^1$ 的数增加 $2$，集合中满足条件的数有 $2,2,4$，于是集合变为 $\{1,3,4,4,6\}$。

第 $8$ 次操作删去一个 $4$，集合变为 $\{1,3,4,6\}$。

第 $9$ 次操作查询 $16$，$\operatorname{lowbit}(16\oplus 4)=\operatorname{lowbit}(20)=4$ 为最大值。

第 $10$ 次操作再次删去一个 $4$，集合变为 $\{1,3,6\}$。

第 $11$ 次操作查询 $16$，$\operatorname{lowbit}(16\oplus 6)=\operatorname{lowbit}(22)=2$ 为最大值。

**【数据范围】**

对于所有数据，$1\leq q\leq 5\times 10^5$，$0\leq x,y,v\leq 2^{32}-1$，$0\leq k\leq 32$。

**捆绑测试**，共 5 个 Subtask，具体限制如下所示：

- Subtask 1（7 pts）：$q\leq 10^3$。
- Subtask 2（16 pts）：不存在 3 操作。
- Subtask 3（21 pts）：对于 3 操作，$k=0$。
- Subtask 4（28 pts）：对于 3 操作，$v=1$。
- Subtask 5（28 pts）：无特殊限制。


---

---
title: "[PA 2016] 归约 / CNF-SAT"
layout: "post"
diff: 省选/NOI-
pid: P11611
tag: ['动态规划 DP', '2016', '虚树', '字典树 Trie', 'PA（波兰）']
---
# [PA 2016] 归约 / CNF-SAT
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R5 CNF-SAT [B] (CNF)。$\texttt{1s,256M}$。

## 题目描述


我们给定 SAT 问题的定义。本题中，不区分 $1$ 与 $\mathrm{True}$，$0$ 与 $\mathrm{False}$。

SAT 问题用来求出一组逻辑变量 $x_1,x_2,\cdots,x_n$ 的取值（其中 $x_i\in \{\mathrm{True},\mathrm{False}\}$），使得以下的**合取范式**取值为真：

$$(l_{1,1}\lor l_{1,2}\lor \ldots\lor l_{1,q_1})\land (l_{2,1}\lor l_{2,2}\lor \ldots\lor l_{2,q_2})\land \ldots \land (l_{m,1}\lor l_{m,2}\lor \ldots\lor l_{m,q_m})$$



其中，$(l_{i,1}\lor l_{i,2}\lor \ldots\lor l_{i,q_i})$ 称为**子句**（Clause），$l_{i,j}$ 是 $x_1,\ldots,x_n$ 中的变量或其否定。我们规定一个子句中，不存在 $j\lt k$，使得 $l_{i,j}$ 中的变量与 $l_{i,k}$ 中的变量相同。

---


某人声称解决了世界难题 $\mathrm{P}=\mathrm{NP?}$。他声称，一般的 SAT 问题都可以归约到一种特例，而这种特例中的所有子句都满足特殊性质：

- $\forall 1\le i\le n$，$x_i$ 和 $\neg x_i$ 不会同时在子句中出现。
- $\forall 1\le i\lt j\lt k\le n$，若子句中出现了 $x_i$（或 $\neg x_i$）和 $x_k$（或 $\neg x_k$），则必然有 $x_j$（或 $\neg x_j$）在这个子句中出现。

这里，所有出现的变量的下标都是 $1\sim n$。

给定满足特例的合取范式，统计有多少种不同的取值能够使其取值为真。只需要求出答案对 $(10^9+7)$ 取模后的结果。
## 输入格式


第一行，一个正整数 $n$，表示**变量的数量**。

第二行，描述一个由若干个子句组成的合取范式：

- 两个子句之间由 ` ^ ` 隔开（一个空格，和 `^`，然后再是一个空格）。
- 每个子句由一对圆括号 `()` 包围。圆括号内部是若干变量，每个变量形如 `xi` 或者 `~xi`（这里，`x` 是英文字母 $x$，`i` 是一个正整数），其中 `xi` 表示 $x_i$，`~xi` 表示 $\neg x_i$。两个变量之间用 ` v ` 隔开（一个空格，和英文字母 `v`，然后再是一个空格）。

这里，保证有 $1\le i\le n$，且子句满足题目描述中的特殊性质。

## 输出格式


输出答案对 $(10^9+7)$ 取模后的结果。

## 样例

### 样例输入 #1
```
3
(x2) ^ (x3 v ~x2) ^ (x2 v x1 v ~x3)
```
### 样例输出 #1
```
2
```
## 提示

#### 样例解释

两个合法解为 $(0,1,1)$ 和 $(1,1,1)$。

#### 数据范围

- $1\le n\le 10^6$；
- 所有子句中变量个数的和不超过 $10^6$。


---

---
title: "[GCJ 2014 #2] Trie Sharding"
layout: "post"
diff: 省选/NOI-
pid: P13259
tag: ['2014', '树形 DP', '组合数学', '字典树 Trie', 'Google Code Jam']
---
# [GCJ 2014 #2] Trie Sharding
## 题目描述

A set of strings $\mathbf{S}$ can be stored efficiently in a trie. A trie is a rooted tree that has one node for every prefix of every string in $\mathbf{S}$, without duplicates.

For example, if $\mathbf{S}$ were "AAA", "AAB", "AB", "B", the corresponding trie would contain 7 nodes corresponding to the prefixes "", "A", "AA", AAA", "AAB", "AB", and "B".

I have a server that contains $\mathbf{S}$ in one big trie. Unfortunately, $\mathbf{S}$ has become very large, and I am having trouble fitting everything in memory on one server. To solve this problem, I want to switch to storing $\mathbf{S}$ across $\mathbf{N}$ separate servers. Specifically, $\mathbf{S}$ will be divided up into disjoint, non-empty subsets $\mathbf{T}_{1}, \mathbf{T}_{2}, \ldots, \mathbf{T}_{\mathbf{N}}$, and on each server i, I will build a trie containing just the strings in $\mathbf{T}_{\mathbf{i}}$. The downside of this approach is the total number of nodes across all $\mathbf{N}$ tries may go up. To make things worse, I can't control how the set of strings is divided up!

For example, suppose "AAA", "AAB", "AB", "B" are split into two servers, one containing "AAA" and "B", and the other containing "AAB", "AB". Then the trie on the first server would need 5 nodes ("", "A", "AA", "AAA", "B"), and the trie on the second server would also need 5 nodes ("", "A", "AA", "AAB", "AB"). In this case, I will need 10 nodes altogether across the two servers, as opposed to the 7 nodes I would need if I could put everything on just one server.

Given an assignment of strings to $\mathbf{N}$ servers, I want to compute the worst-case total number of nodes across all servers, and how likely it is to happen. I can then decide if my plan is good or too risky.

Given $\mathbf{S}$ and $\mathbf{N}$, what is the largest number of nodes that I might end up with? Additionally, how many ways are there of choosing $\mathbf{T}_{1}, \mathbf{T}_{2}, \ldots, \mathbf{T}_{\mathbf{N}}$ for which the number of nodes is maximum? Note that the $\mathbf{N}$ servers are different -- if a string appears in $\mathbf{T}_{\mathbf{i}}$ in one arrangement and in $\mathbf{T}_{\mathbf{j}}$ ($i \neq j$) in another arrangement, then the two arrangements are considered different. Print the remainder of the number of possible arrangements after division by 1,000,000,007.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two space-separated integers: $\mathbf{M}$ and $\mathbf{N}$. $\mathbf{M}$ lines follow, each containing one string in $\mathbf{S}$.
## 输出格式

For each test case, output one line containing "Case #i: $\mathbf{X} \mathbf{Y}$", where i is the case number (starting from 1), $\mathbf{X}$ is the worst-case number of nodes in all the tries combined, and $\mathbf{Y}$ is the number of ways (modulo 1,000,000,007) to assign strings to servers such that the number of nodes in all $\mathbf{N}$ servers are $\mathbf{X}$.
## 样例

### 样例输入 #1
```
2
4 2
AAA
AAB
AB
B
5 2
A
B
C
D
E
```
### 样例输出 #1
```
Case #1: 10 8
Case #2: 7 30
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- Strings in $\mathbf{S}$ will contain only upper case English letters.
- The strings in $\mathbf{S}$ will all be distinct.
- $\mathrm{N} \leq \mathrm{M}$

**Small dataset(9 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq M \leq 8$
- $1 \leq N \leq 4$
- Each string in $\mathbf{S}$ will have between 1 and 10 characters, inclusive.

**Large dataset(30 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leq M \leq 1000$
- $1 \leq N \leq 100$
- Each string in $\mathbf{S}$ will have between 1 and 100 characters, inclusive.



---

---
title: "[SCOI2016] 背单词"
layout: "post"
diff: 省选/NOI-
pid: P3294
tag: ['贪心', '2016', '四川', '深度优先搜索 DFS', '字典树 Trie']
---
# [SCOI2016] 背单词
## 题目描述

Lweb 面对如山的英语单词，陷入了深深的沉思：我怎么样才能快点学完，然后去玩三国杀呢？这时候睿智的凤老师从远处飘来，他送给了 Lweb 一本计划册和一大缸泡椒，他的计划册是长这样的：

| 序号    | 单词 |
| ------- | ---- |
| $1$     |      |
| $2$     |      |
| $\dots$ |      |
| $n-1$    |      |
| $n$     |      |

然后凤老师告诉 Lweb ，我知道你要学习的单词总共有 $n$ 个，现在我们从上往下完成计划表，对于一个序号为 $x$ 的单词（序号 $1,\dots ,x-1$ 都已经被填入）：

1. 如果存在一个单词是它的后缀，并且当前没有被填入表内，那他需要吃 $n \times n$ 颗泡椒才能学会；
2. 当它的所有后缀都被填入表内的情况下，如果在 $1,\dots,x-1$ 的位置上的单词都不是它的后缀，那么你吃 $x$ 颗泡椒就能记住它；
3. 当它的所有后缀都被填入表内的情况下，如果 $1,\dots,x-1$ 的位置上存在是它后缀的单词，所有是它后缀的单词中，序号最大为 $y$，那么你只要吃 $x-y$ 颗泡椒就能把它记住。

Lweb 是一个吃到辣辣的东西会暴走的奇怪小朋友，所以请你帮助 Lweb ，寻找一种最优的填写单词方案，使得他记住这 $n$ 个单词的情况下，吃最少的泡椒。

形式化题意：

你需要为 $n$ 个字符串排列一个顺序，每个字符串都会产生一定代价。

对于一个字符串 $s$，其所在位置为 $x$：

1. 如果存在至少一个其他字符串是 $s$ 后缀，且这个字符串的位置在 $s$ 后面， $s$ 将产生 $n \times n$ 的代价。

2. 如果不存在其他字符串是 $s$ 的后缀，则 $s$ 产生 $x$ 的代价。

3. 如果所有是 $s$ 后缀的字符串的位置都在 $s$ 的前面，若这些字符串的位置的最大值为 $y$ ， 则 $s$ 产生 $x-y$ 的代价。

为 $n$ 个字符串排列一个顺序，使总代价最小。
## 输入格式

输入一个整数 $n$ ，表示 Lweb 要学习的单词数。

接下来 $n$ 行，每行有一个单词（由小写字母构成，且保证任意单词两两互不相同）。
## 输出格式

Lweb 吃的最少泡椒数。
## 样例

### 样例输入 #1
```
2
a
ba
```
### 样例输出 #1
```
2
```
## 提示

$1\le n\le100000$，所有字符的长度总和 $1\le \sum|S| \le510000$。


---

---
title: "[POI 2006] PAL-Palindromes"
layout: "post"
diff: 省选/NOI-
pid: P3449
tag: ['2006', 'POI（波兰）', '哈希 hashing', '字典树 Trie']
---
# [POI 2006] PAL-Palindromes
## 题目描述

Little Johnny enjoys playing with words. He has chosen $n$ palindromes (a palindrome is a wordthat reads the same when the letters composing it are taken in the reverse order, such as dad, eye orracecar for instance) then generated all $n^2$ possible pairs of them and concatenated the pairs intosingle words. Lastly, he counted how many of the so generated words are palindromes themselves.

However, Johnny cannot be certain of not having comitted a mistake, so he has asked you to repeatthe very same actions and to give him the outcome. Write a programme which shall perform thistask for you.

TaskWrite a programme which:

reads the palindromes given by Johnny from the standard input,        determines the number of words formed out of pairs of palindromes from the input, which are palindromes    themselves,        writes the outcome to the standard output.

## 输入格式

The first line of the standard input contains a single integer $n$, $n\ge 2$, denoting the number ofpalindromes given by Johnny. The following $n$ lines contain a description of the palindromes. The $(i+1)$'st line contains a single positive integer $a_i$ denoting the length of $i$'th palindrome and apalindrome of $a_i$ small letters of English alphabet. The number $a_i$ is separated from the palindromeby a single space. The palindromes in distinct lines are distinct. The total length of all palindromesdoes not exceed $2\ 000\ 000$.

## 输出格式

The first and only line of the standard output should contain a single integer: the number of distinctordered pairs of palindromes which form a palindrome upon being concatenated.

## 样例

### 样例输入 #1
```
6
2 aa
3 aba
3 aaa
6 abaaba
5 aaaaa
4 abba
```
### 样例输出 #1
```
14
```
## 题目翻译

### 题目描述

Johnny 喜欢玩文字游戏。

他写下了 $n$ 个回文串，随后将这些串两两组合，合并成一个新串。容易看出，一共会有 $n^2$ 个新串。

两个串组合时顺序是任意的，即 `a` 和 `b` 可以组合成 `ab` 和 `ba`，另外自己和自己组合也是允许的。

现在他想知道这些新串中有多少个回文串，你能帮帮他吗？

### 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行包含一个数 $a_i$ 和一个长度为 $a_i$ 的回文串。

保证所有串只包含小写字母，且所有串两两不同，所有回文串的长度和不超过 $2 \times 10^6$。

### 输出格式

输出一个整数，代表满足条件的新串的数量。


---

---
title: "[HAOI2017] 供给侧改革"
layout: "post"
diff: 省选/NOI-
pid: P3732
tag: ['2017', '河南', '各省省选', '排序', '进制', '字典树 Trie']
---
# [HAOI2017] 供给侧改革
## 题目描述

你调查了某个产业近来 $n$ 个时期的供求关系平衡情况，每个时期的情况都用 $0$ 或 $1$ 中的一个数字来表示。于是这就是—个长度为 $n$ 的 $\texttt{01}$ 字符串 $S$。为了更好的了解这一些数据，你需要解决一些询问，我们令 $\text{data}(L,R)$ 表示：在字符串 $S$ 中，起始位置在 $[L,R]$ 之间的这些后缀之中，具有最长公共前缀的两个后缀的最长公共前缀的长度。

对于每一个询问 $L,R$，求：

$$ans = \sum_{L \leqslant i < R} \text{data}(i,R)$$

数据范围保证，串 $S$ 中的每一位都是在 $0$ 和 $1$ 之间随机产生的。
## 输入格式

第一行 $2$ 个整数 $n,Q$，表示字符串的长度，以及询问个数。

接下来一行长度为 $n$ 的一个 $\texttt{01}$ 串 $S$。

接下来 $Q$ 行，每行 $2$ 个整数 $L,R$，一个询问 $L,R$。
## 输出格式


共 $Q$ 行，每行一个整数，表示对应询问的答案。
## 样例

### 样例输入 #1
```
6 3
010110
2 5
1 6
1 2
```
### 样例输出 #1
```
4
6
0
```
## 提示

【数据规模与约定】

|数据点|$n$ 的规模|$Q$ 的规模|
|:-:|:-:|:-:|
|$1,2$|$\leqslant 20$|$\leqslant 20$|
|$3,4$|$\leqslant 100$|$\leqslant 100$|
|$5,6$|$\leqslant 5 \times 10^3$|$\leqslant 5 \times 10^3$|
|$7,8,9,10$|$\leqslant 10^5$|$\leqslant 10^5$|



对于所有的数据保证：$n \leqslant 10^5$，$Q \leqslant 10^5$，$1 \leqslant L < R \leqslant n$，$\texttt{01}$ 串随机生成。


---

---
title: "[HEOI2013] ALO"
layout: "post"
diff: 省选/NOI-
pid: P4098
tag: ['2013', '各省省选', '河北', '枚举', '可持久化', '字典树 Trie']
---
# [HEOI2013] ALO
## 题目描述

Welcome to ALO (Arithmetic and Logistic Online）。这是一个 VR MMORPG，如名字所见，到处充满了数学的谜题。

现在你拥有 $n$ 颗宝石，第 $i$ 颗宝石有一个能量密度，记为 $a_i$，这些宝石的能量密度**两两不同**。现在你可以选取**连续**的一些宝石（必须多于一个）进行融合，设他们的能量密度为 $a_i,a_{i+1},\cdots,a_j$，则融合而成的宝石的能量密度为这些宝石中能量密度的次大值与其他任意一颗宝石的能量密度按位异或的值的最大值。即，假设该段宝石能量密度次大值为 $k$，则生成的宝石的能量密度为 $\max\{k\oplus a_p\mid a_p\ne k, i\le p\le j\}$。

现在你需要知道你怎么选取需要融合的宝石，才能使生成的宝石能量密度最大。
## 输入格式

第一行，一个整数 $n$，表示宝石个数。

第二行，$n$ 个整数，分别表示 $a_1$ 至 $a_n$，表示每颗宝石的能量密度，保证对于 $i\ne j$ 有 $a_i\ne a_j$。
## 输出格式

输出一行一个整数，表示最大能生成的宝石能量密度。

## 样例

### 样例输入 #1
```
5 
9 2 1 4 7
```
### 样例输出 #1
```
14
```
## 提示

### 样例解释

选择区间 $[1,5]$，最大值为 $7\oplus 9 = 14$。

### 数据规模与约定

- 对于 $20\%$ 的数据有 $n\le 100$；
- 对于 $50\%$ 的数据有 $n\le 2000$；
- 对于 $100\%$ 的数据有 $1\le n\le 50000$，$0\le a_i\le 10^9$。

2023.4.28：添加两组 hack 数据，不计分。


---

---
title: "最大异或和"
layout: "post"
diff: 省选/NOI-
pid: P4735
tag: ['O2优化', '可持久化', '前缀和', '字典树 Trie']
---
# 最大异或和
## 题目描述

给定一个非负整数序列 $\{a\}$，初始长度为 $N$。  

有 $M$ 个操作，有以下两种操作类型：  

1. `A x`：添加操作，表示在序列末尾添加一个数 $x$，序列的长度 $N$ 加 $1$。  
2. `Q l r x`：询问操作，你需要找到一个位置 $p$，满足 $l \le p \le r$，使得：$a[p] \oplus a[p+1] \oplus ... \oplus a[N] \oplus x$ 最大，输出最大值。  
## 输入格式

第一行包含两个整数 $N, M$，含义如问题描述所示。     
第二行包含 $N$ 个非负整数，表示初始的序列 $A$。   
接下来 $M$ 行，每行描述一个操作，格式如题面所述。     
## 输出格式

假设询问操作有 $T$ 个，则输出应该有 $T$ 行，每行一个整数表示询问的答案。
## 样例

### 样例输入 #1
```
5 5
2 6 4 3 6
A 1 
Q 3 5 4 
A 4
Q 5 7 0 
Q 3 6 6 
```
### 样例输出 #1
```
4
5
6
```
## 提示

- 对于所有测试点，$1\le N,M \le 3\times 10 ^ 5$，$0\leq a_i\leq 10 ^ 7$。


---

---
title: "[十二省联考 2019] 异或粽子"
layout: "post"
diff: 省选/NOI-
pid: P5283
tag: ['2019', '各省省选', '堆', '字典树 Trie']
---
# [十二省联考 2019] 异或粽子
## 题目描述

小粽是一个喜欢吃粽子的好孩子。今天她在家里自己做起了粽子。

小粽面前有 $n$ 种互不相同的粽子馅儿，小粽将它们摆放为了一排，并从左至右编号为 $1$ 到 $n$。第 $i$ 种馅儿具有一个非负整数的属性值 $a_i$。每种馅儿的数量都足够多，即小粽不会因为缺少原料而做不出想要的粽子。小粽准备用这些馅儿来做出 $k$ 个粽子。

小粽的做法是：选两个整数数 $l$,  $r$，满足 $1 \leqslant l \leqslant r \leqslant n$，将编号在 $[l, r]$ 范围内的所有馅儿混合做成一个粽子，所得的粽子的美味度为这些粽子的属性值的**异或和**。（异或就是我们常说的 xor 运算，即 C/C++ 中的 `ˆ` 运算符或 Pascal 中的 `xor` 运算符）

小粽想品尝不同口味的粽子，因此它不希望用同样的馅儿的集合做出一个以上的
粽子。

小粽希望她做出的所有粽子的美味度之和最大。请你帮她求出这个值吧！
## 输入格式

第一行两个正整数 $n$, $k$，表示馅儿的数量，以及小粽打算做出的粽子的数量。

接下来一行为 $n$ 个非负整数，第 $i$ 个数为 $a_i$，表示第 $i$ 个粽子的属性值。
对于所有的输入数据都满足：$1 \leqslant n \leqslant 5 \times 10^5$,  $1 \leqslant k \leqslant \min\left\{\frac{n(n-1)}{2},2 \times 10^{5}\right\}$,  $0 \leqslant a_i \leqslant 4 294 967 295$。

## 输出格式

输出一行一个整数，表示小粽可以做出的粽子的美味度之和的最大值。
## 样例

### 样例输入 #1
```
3 2
1 2 3
```
### 样例输出 #1
```
6
```
## 提示

| 测试点 | $n$ | $k$ |
| :---------- | :---------- | :---------- |
| $1$, $2$, $3$, $4$, $5$, $6$, $7$, $8$ | $\leqslant 10^3$ | $\leqslant 10^3$ |
| $9$, $10$, $11$, $12$ | $\leqslant 5 \times 10^5$ | $\leqslant 10^3$ |
| $13$, $14$, $15$, $16$ | $\leqslant 10^3$ | $\leqslant 2 \times 10^5$ |
| $17$, $18$, $19$, $20$ | $\leqslant 5 \times 10^5$ | $\leqslant 2 \times 10^5$ |



---

---
title: "[BJOI2016] IP地址"
layout: "post"
diff: 省选/NOI-
pid: P5460
tag: ['字符串', '2016', '各省省选', '北京', 'O2优化', '字典树 Trie']
---
# [BJOI2016] IP地址
## 题目描述

路由表中每一项对应了一个形如 1011101????????????????????????? 的规则，会匹配指定的前缀为给定形式的 $\texttt{ip}$。  

当有多个规则匹配时，前缀最长的生效。同一时刻不会有多个匹配的规则的前缀一样长。每一个时刻，会有一条规则被加入，或者之前被加入的某条规则会过期。   

给一系列 $\texttt{ip}$，问每一个 $\texttt{ip}$ 在一个给定的时间区间内匹配到的生效规则变了几次？  
   
例如，有一系列事件：    
 
$\texttt{Add}$ $110$   
$\texttt{Add}$ $11$   
$\texttt{Del}$ $110$   
$\texttt{Del}$ $11$   
$\texttt{Add}$ $110$     

那么，$\texttt{ip}$ 地址 11011101001001010101011101000010 在这五个时刻之后匹配到的生效规则分别是：  

$110$ (第一条)，   
$110$ (第一条)，   
$11$ (第二条)，   
空，   
$110$ (第三条)。     

其中，在第二个事件后到第五个事件后的这段过程中，一共变了 $3$ 次。
## 输入格式

第一行两个正整数 $n,q$，表示事件数有询问数。  
接下来 $n$ 行，每行描述一个事件，格式为：  

$\texttt{Add}$ $s$ 表示新建一个规则，匹配前缀为 $s$ 的所有 $\texttt{ip}$。  
$\texttt{Del}$ $s$ 表示把当前前缀 $s$ 对应的规则删掉(过期)。保证之前有这样的一条规则还没被删。     

接下来 $q$ 行，每行一个 $\texttt{ip}$ 与两个正整数 $a,b$，表示查询在第 $a$ 个事件后到第 $b$ 个事件的这段时间里，这个 $\texttt{ip}$ 匹配到的生效规则变化的次数。 $\texttt{ip}$ 用01字符串来表示。
## 输出格式

对于每次查询，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 1
Add 110
Add 11
Del 110
Del 11
Add 110
11011101001001010101011101000010 2 5
```
### 样例输出 #1
```
3
```
## 提示

【数据范围】  

$1\le n,q \le 10^5$


---

---
title: "[Ynoi2010] Fusion tree"
layout: "post"
diff: 省选/NOI-
pid: P6018
tag: ['树形数据结构', '2010', 'O2优化', '字典树 Trie', 'Ynoi']
---
# [Ynoi2010] Fusion tree
## 题目背景

题目背景和题意无关，可以跳过

## 1.前言：
Fusion Tree，中文译作融合树，是一种亚log的数据结构，与1993年由Michael L.Fredman和Dan E.Willard提出。

用途：$O( \log n/ \log w+ \log w )$时间复杂度支持插入，删除，前驱，后继，min，max，以及用于整数排序。

信息论断言对$n$个数的排序在最坏情况下需要$n\log n$次比较，不过对这个界我们还需要一些研究。

有人证明了任意unit cost RAM算法，其中只包含加法，减法，乘法，和0比较（但是不包含除法和位运算）最坏情况下需要$\Omega(n\log n)$的时间去对$n$个数排序。

如果允许使用除法和位运算，他们有一个线性时间复杂度的算法，但是这个算法对unit cost滥用。

这里我们规定我们使用的计算模型的字长是w，每个输入的数都是在$[0,2^w-1]$中的整数。

## 2.一些记号：
对于一个集合$S$和一个整数$x$，定义$rank(S,x)$为S集合中$\le x$的元素个数。
对于一些非负整数$a$，定义$bin(a_1,...,a_n)=2^{a_i}+...+2^{a_n}$。

对于两个非负整数$a,b$，定义$msb(u,v)$为$u$和$v$最高的不相同的位。

## 3.概述：
Fusion Tree大概可以看做是一棵特殊的B-Tree，特性：

1. 叉数$B=O(w^{1/5})$

2. 在一次搜索时，每个在搜索路径上的节点的正确的儿子可以被$O(1)$确定

从这些特性我们可以看出Fusion Tree单次操作的时间复杂度是$O( \log _w(n) + \log w) = O( \log n/\log w +\log  w)$的，比$O( \log n )$低。

但是由于其实现方式，Fusion Tree每次对内部节点的更新复杂度是$O( B^4 )$的。
为了控制Fusion Tree均摊的更新复杂度，我们将这棵B-Tree的每对叶子节点之间的部分替换为一个大小大约为$O( B^4 )$的Weight Balanced Tree，只在WBT根节点发生变化的时候更新Fusion Tree的内部节点。

具体来说，我们B-Tree维护的是一个排序后的数组的分块，其中每个块都由一棵平衡二叉搜索树维护，fusion tree上只维护一个值来表示块边界，用途是指引每次插入，删除，查询在哪个块中。

可以发现这样我们把内部节点的变化次数除掉了一个$B^4$。

## 4.压缩key的表示：

如何$O(1)$确定搜索路径上的一个节点的正确的儿子：

考虑一个B-Tree的节点，其上面包含了$k$个key，其中$B/2 \le k \le B$，记作$S={u_1,u_2,...u_k}$。

然后我们定义出$B(S)$表示"有区别的位的位置"，用人话来说就是我们把这$k$个key的trie建出来，然后所有有超过$1$个儿子的节点的高度构成的集合
（当然这里我们不用把trie建出来，只是这么解释比较直观，而且更能反映出其的一些性质）。

再定义一个集合$K(S)$，为$S$只保留$B(S)$中那些位之后的值，记作$K(S)={u'_1,u'_2,...u'_k}$，发现这个压缩操作对于原集合是保序的。

对于一个任意的$w-bit$的数$u$，我们记$u'(S)$表示$u$只保留$B(S)$中那些位，即把非$B(S)$中的位都置为$0$之后的值。

下面引理表达了一个压缩key的重要性质：

### 引理1：
设$B(S)$排序后为$c_1<c_2<...<c_r$，定义边界$c_0=-1,c_{r+1}=b$。

定义$u'_i$为$K(S)$中任意的一个压缩后的key。

对于一个任意的$w-bit$的数$u$，满足$u \neq u_i$，

设$msb(u'(S),u'_i)=c_m$，即$u$和$u_i$在bit位置$c_{m+1},...,c_r$位置处相等，但是在$c_m$处不相等，如果$u'(S)=u'_i$，则我们记$m=0$。

如果$u$和$u_i$不同的最高位$p$满足$p>c_m$，那么我们可以通过：

1. 唯一的一个区间$[c_{j-1},c_j]$满足$p$属于这个区间

2. $u$和$u_i$的大小关系

来确定$rank(S,u)$的值。

证明平凡，把trie画出来，显然可以画成一个平面图，然后可以发现这两个可以唯一地确定出一个平面区域，这个区域中的$S$集合元素个数就是$rank(S,u)$（感觉这种东西光写一堆自然语言也不能说明正确性，需要形式化证明一下？）。

注意到这个引理虽然是对任意$u_i$成立的，但是要求$u$和$u_i$不相同的最高位不是$B(S)$中的一个点，可以发现这个$u_i$其实必须在$u$"脱离"这个trie的位置，也就是$p$的父亲子树中。

引理$1$使得我们可以将$rank(S,u)$的计算规模降低到$rank(K(S),u'(S))$，通过计算$rank(K(S),u'(S))$，我们可以确定$u'(S)$在$K(S)$中的前驱后继$u'_j$和$u'_{j+1}$（这两个值不一定存在，但经过平凡的讨论就可以解决。

如果$u_j \le u \le u_{j+1}$，那我们已经解决了这个问题
否则我们令$i=j$或者$i=j+1$，计算出$msb(u_i,u)=p$，然后只要我们知道了包含$p$的区间$[c_j,c_{j+1}]$，我们就可以通过引理$1$来确定出$rank(S,u)$的值。

这里如果我们$u_j \le u \le u_{j+1}$，那我们已经达成了目的，不用继续考虑了。

否则如果不满足$u_j \le u \le u_{j+1}$，也就是说我们在这个sketch的过程中丢失了信息，即说明保留$K(S)$这些位的信息是不够的，那么$p$一定不在$K(S)$中，也就是说$i=j$和$i=j+1$中$p$较小的$i$满足$p>c_m$，故可以使用引理$1$。

计算$K(S)$和$u'(S)$：
我们发现没有平凡的方法可以将一个$w-bit$的数$u$在$O(1)$时间把$B(S)$那些位提取出来之后放到连续的一段中（可能可以通过硬件支持实现？），即使经过了一定预处理。

其实我们不需要做到这个，可以用具有：

1. 将需要提取出的位提取出，并放到（可以不连续）的更短的一段中

2. 保序性

的其他变化来实现我们需要的效果。

我们可以通过一次恰当的乘法和一次与运算来实现这个：

沿用引理$1$的定义，设我们需要从$u$中提取这些位，令$C=bin(c_1,...,c_r)$。

假设我们已经算出了$C$，我们先通过令$v=u\;\mathrm{AND}\;C$来将$u$中不需要的那些位置$0$。

然后我们将$v$乘以一个量$M$，从而把$v$中我们需要的那些$bit$转化到一个狭窄的范围内，然后再通过一次$\mathrm{AND}$来清除掉不需要的位置
这里给出对一个量$M$的存在性证明和构造：

记$M=bin(m_1,...,m_r)$，如果我们暂时忽略交叉和进位造成的影响，那么可以认为$v$乘$M$是把$c_1,...c_r$这些位置的位重新定位到了。

$c_1+m_1,...,c_r+m_r$上。

如果对任意$1 \le i,j \le r$，这$r^2$个$c_i+m_j$都是不同的，那么就不会发生交叉和进位了。

我们现在的目标是构造一个整数集合${m_1,...,m_r}$，使得：

1. $c_1+m_1<c_2+m_2<...<c_r+m_r$

2. 对任意$1 \le i,j \le r$，$c_i+m_j$都是两两不同的。

3. 变换后的区间$[c_1+m_1,c_r+m_r]$"相对较小"，这里的相对较小其实只要是$O( poly(r) )$的即可，因为这样我们可以通过调整树的叉数来满足后续的条件。

### 引理2：

给一个$r$个整数的序列，$c_1<...<c_r$，存在一个$r$个整数的序列，$m_1,...m_r$，满足：

1. $c_1+m_1<c_2+m_2<...<c_r+m_r$

2. 对任意$1 \le i,j \le r$，$c_i+m_j$都是两两不同的。

3. $(c_r+m_r)-(c_1+m_1) \le r^4$

证明：

先考虑证明存在整数序列$m'_1,...,m'_r$，使得对任意$i,j,a,b$，$m'_i+c_a$与$m'_j+c_b$在模$r^3$的意义下不同余。

如果我们找到了这样的整数序列，那么所有$r^2$个$c_i+m'_j$都是两两不同的，并且由于这个是在模$r^3$意义下两两不同的，所以我们可以对第$i$个$c_i+m'_i$加上$(i-1)*r^3$，这样就可以保证对所有$i$满足$c_i+m'_i<c_{i+1}+m'_{i+1}$了。

关于$m'_1,...,m'_r$的存在性：

使用数学归纳法来证明，显然我们可以找到$m'_1$，这个平凡。

假设结论对$t$成立，即我们已经找到了$m'_1,...,m'_t$，满足对任意$1 \le i,j \le t$，$a,b$,有$m'_i+c_a$与$m'_j+c_b$在模$r^3$的意义下不同余。
可以观察到$m'_{t+1}+c_i \equiv m'_s+c_j (\mod r^3\;)$，即$m'_{t+1} \equiv m'_s+c_j-c_i (\mod r^3\;)$。


我们可以令$m'_{t+1}$是$[0,r^3)$中最小的和所有$m'_s+c_j-c_i$不同余的数，这里$1 \le s \le t,1 \le i,j \le r$。

由鸽巢原理，由于$t*r^2<r^3$，所以我们一定可以找到$m'_{t+1}$。

故当$t+1 \le s$时，结论对$t+1$成立
由数学归纳法知结论对$s$成立，同时我们这里给出了一个暴力的$O( r^4 )$的构造算法（$r$轮，每轮最坏枚举$O( r^3 )$个位置）。

## 5.融合：
融合树的"融合"即指将每个节点上的key放到同一个$w-bit$的word上，通过对这个word进行运算来一起处理这些key。

沿用之前$u_i$和$B(S)=\{c_i\}$的记号：

我们这个B-Tree的每个节点存了$C=bin(c_1,...c_r)$和$M=bin(m_1,...,m_r)$这两个量，用于计算$u'(S)$，同时还存了$D=bin(c_1+m_1,...,c_r+m_r)$这个量，用于清空$u'(S)$的计算中不需要的位。

同时还需要两个数组，存排序后的$u_i$和$u'_i$，和一个表$f[i][j][2]$表示引理$1$中，如果知道了$u_i$和$j$，还有$u$和$u_i$的大小关系，我们唯一确定的答案是多少。

回顾之前的内容，当我们算出了$j=rank(K(S),u'(S))$后，如果$u$不在$[u_j,u_{j+1}]$的区间中，那么我们把$u'(S) \;\mathrm{XOR}\; u'_j$和$u'(S) \;\mathrm{XOR}\; u'_{j+1}$比较一下，较小的值所对应的$u'_h$，$h=j$或$j+1$，和$u$有更长的公共前缀，即$msb$更小。

令$m=msb(u,u_h)$，然后我们需要知道$m$被哪个$B(S)$中的区间$[c_i,c_{i+1}]$包含，所以需要进行一次$i=rank(B(S),m)$的计算
还需要进行一次$u$和$u_h$的比较，这个平凡，当这些都做完了，我们查一下表$f$即可得到$rank(S,u)$。

可以发现fusion tree的每个内部节点需要存下$O( B^2 )$大小的表，内部节点个数是$O( n/B^4 )$个，所以是$O( n )$空间的。

下面给出对

1. $rank(K(S),u'(S))$

2. $rank(B(S),m)$，其中$m$是在$[0,w]$中的整数

3. 两个$w-bit$的整数$u,v$，$msb(u,v)$

的计算方法：

### $O(1)$计算$rank(K(S),u'(S))$：
我们把每个$K(S)$中的元素前面补一个$1$，然后从小到大拼到一起来，这个拼起来的操作就是所谓的"融合"。

由于我们$K(S)$中有$k$个元素，每个元素有$r^4$位，所以这里总共用了$k(r^4+1)$位，由于$B/2 \le k \le B$，所以我们总的位数是$O( B^5 )$的，由于$B=O( w^{1/5} )$，所以总的位数是$O( w )$的。

所以我们拼起来的这个东西是$O( 1 )$个word的，这里将其定义为$A$。

令$C=\sum \limits _{i = 0} ^ {B} 2^{(r^4+1)i}$
通过$u'(S) \times C$，可以将$u'(S)$前面补一个$0$之后复制$B$遍，然后拼到一起
通过$A-u'(S) \times C$，可以发现对每个$A$中补$1$的位置，其对应的那个$u_i(S)$如果$<u'(S)$，则这个$1$变成$0$，否则$1$不变
所以我们通过$(A-u'(S) \times C)\&C$，然后对这个word数$1$的个数即可知道$rank(K(S),u'(S))$。

由于这个word只在$2^{(r^4+1)i}$这样的位置有$1$，我们可以通过一次对$2^{r^4+1}-1$的取模来得到其中$1$的个数，虽然对常数取模可以用乘法和位运算$O(1)$实现，但我们这里可以给出一个更合适的构造。

我们可以通过将其乘$C \& (2^{(r^4+1)k}-1)$，这样相当于把其叠加了$k$次之后加起来，可以发现其中有一个长为$r^4+1$的段，这段的二进制表示的值等于这个word在$2^{(r^4+1)i}$这些位置的元素的和。

通过位移和$\mathrm{AND}$我们可以取出这个长$r^4+1$的段，于是就完成了。

答案即$((((A-u'(S) \times C) \& C) \times (C \& (2^{(r^4+1)k}-1))) \& C)>>((k(r^4+1)-1)$

### $O(1)$计算$rank(B(S),m)$，$m$是在$[0,w]$中的整数：

由于我们可以$O(1)$计算$rank(K(S),u'(S))$，所以把这个查出来然后判断那一个数的大小，并且进行一次查表即可。

### $O(1)$计算$msb(u,v)$：
等价于求$u \;\mathrm{XOR}\; v$的最高位$1$的位置，设$A=u \;\mathrm{XOR}\; v$。

我们将$A$分为$r^c$大小的块，总共$r$块，这里$c$是一个常数,$c>1$
令$C=(100...0100...0......)_2$，这里每两个$1$之间有$r-1$个$1$，$C$是一个常数。

注意到：

$((100...0)_2-0)\&(1<<(r^c)-1)=(1<<(r^c)-1)$

$((100...0)_2-y)\&(1<<(r^c)-1)=0$，这里$y>0$

先考虑对每个块去掉首位，块内是否有$1$。

我们用$A\& \sim C$可以去掉每一块的首位。

然后用$C-(A\& \sim C)$可以使得每一块中除首位外如果有$1$，则其在该块首位为$0$，否则为$1$。

然后用$(C-(A\& \sim C))\&C$去掉了$C-(A\& \sim C)$中每一块中除首位外的部分。

然后用$(C-((C-(A\& \sim C))\&C))$可以得到：如果一块中除首位外有$1$，则块首位为$1$，否则为$0$，且块首位外所有位置都是$0$的一个数
再考虑对每个块只保留首位，块内是否有$1$。

这个用$A\&C$即可。

最后$(A\&C)|(C-((C-(A\& \sim C))\&C))$可以得到：如果一块中有$1$，则块首位为$1$，否则为$0$，且块首位外所有位置都是$0$的一个数。

令$D= \sum \limits _{k=0}^{r-1} 2^{k(r^c-1)}$，

通过$(((A\&C)|(C-((C-(A\& \sim C))\&C))) \times D)>>(w-r)$可以将每块首位的数字拼到一个长$r$的二进制数中。

然后我们可以使用前面的$O(1)$计算$rank$的方法，令$B'(S)={2^i}$，$i$在$[0,r-1]$间，是整数。

通过$rank(B'(S),(((A\&C)|(C-((C-(A\& \sim C))\&C))) \times D)>>(w-r))$就可以得到这个长$r$的二进制数中第一个非0的首位的位置了。

我们知道了第一个非$0$位在哪个块中，然后查这个块里面第一个非$0$位的位置就可以了。

由于我们每个块是$r^c$的大小，所以对一个大小为$r^c$，包含了$2^i$的集合用一次rank即找到了块内第一个非$0$的首位位置。

取$c=4,r=w^{1/5}$，$r^c=w^{4/5}$，我们便$O(1)$查询，$O(w^{4/5})$预处理时间复杂度解决了这个问题，由于预处理次数是$O( n/B^4 )$，所以这里也是线性的。

综上所述，我们得到了一个单次操作复杂度$O( \log n/\log w + \log w )$的数据结构，这里**据说**可以通过一些优化做到$O( \log n/\log w )$，但在这里由于我还没看所以暂时不做介绍。

## 6.一些拓展
如果我们允许下列中的一个：

1. 放松线性空间的限制

2. 保留线性空间的限制，但是使用随机化和整数除法

那么我们可以得到一个$O( \sqrt{ \log n } )$的动态搜索的时间复杂度上界。

当$n$超过$2^{(\log w)^2/36}$时（这里$1/36$的常数是论文中给出的，由于我的部分细节和论文中不同，可能是不同的常数），

对于1的case，可以通过使用vEB树来实现，对于2的case，可以通过使用Y-fast trie实现。

对于这样的$n$，这两个数据结构可以在$O( \log \log U )=O( \log w )=O( \sqrt{\log n} )$的时间完成一次搜索操作。

当$n$小于这个数时，

对于较小的$n$，我们使用fusion tree，通过调节$B=Θ(2^ {\sqrt{\log n}})$。

在这个$B$下，我们的时间复杂度是$O( \log n/\log B + \log B ) = O( \sqrt{\log n} )$。

综上所述，如果引入随机化和整数除法，可以$O( n \sqrt{\log n} )$时间，线性空间整数排序。

## 7.总结
由信息论可以证明基于比较的排序下界是$\Omega( n\log n )$的，但整数排序其实是非常复杂的一个问题，还有待研究。
## 题目描述

魔法森林里有一颗大树，下面经常有小孩召开法。

大树可以看做一个有 $n$ 个节点，$n - 1$ 条边的无向连通图。大树的每个节点都有若干瓶矿泉水，初始第 $i$ 个节点有 $a_i$ 瓶矿泉水。

麦杰斯住在大树顶端，有一天他想改造一下大树，方便他巨大多喝水之后可以垃圾分类矿泉水瓶。

麦杰斯喜欢二进制运算，所以他会有以下三种操作：

1. 将树上与一个节点 $x$ 距离为 $1$ 的节点上的矿泉水数量 $+1$。这里树上两点间的距离定义为从一点出发到另外一点的最短路径上边的条数。
2. 在一个节点 $x$ 上喝掉 $v$ 瓶水。
3. 询问树上与一个节点 $x$ 距离为 $1$ 的所有节点上的矿泉水数量的异或和。

麦杰斯共有 $m$ 次操作，他希望你在每次 $3$ 操作后告诉他答案。
## 输入格式

第一行两个正整数 $n,m$，分别表示树的节点个数和麦杰斯的询问个数。

第二行到第 $n$ 行，每行两个整数表示有一条连接这两个节点的边。

第 $n + 1$ 行 $n$ 个整数，第 $i$ 个整数表示初始第 $i$ 个节点上的矿泉水数量。

第 $n + 2$ 行到第 $n + m + 1$ 行，每行先读入一个整数 $opt$ 表示操作类型。

如果 $opt = 1$ 或 $3$ ，接下来读入一个整数 $x$ 表示麦杰斯操作的节点标号。

否则接下来读入两个整数 $x, v$ 表示麦杰斯操作的节点标号和他喝的水的数量。
## 输出格式

对于每一个 $3$ 操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
1 1 4
1 1
3 2
```
### 样例输出 #1
```
5
```
## 提示

Idea：dangxingyu，Solution：dangxingyu，Code：dangxingyu，Data：dangxingyu

对于 $30\%$ 的数据，满足 $n \le 10^3$，$m\le 10^3$。

对于 $60\%$ 的数据，满足 $n \le 10^5$，$m \le 10^5$。

对于另外 $10\%$ 的数据，存在一个点满足所有点到该节点的距离 $\le 1$。

对于 $100\%$ 的数据，满足 $1\le n \le 5\times 10^5$，$1\le m \le 5\times 10^5$，$0\le a_i \le 10^5$，$1 \le x \le n$，$opt\in\{1,2,3\}$。

保证任意时刻每个节点的矿泉水数非负。

温馨提示：矿泉水瓶不是干垃圾也不是湿垃圾，而是可回收垃圾。



---

---
title: "『MdOI R1』Path"
layout: "post"
diff: 省选/NOI-
pid: P6072
tag: ['莫队', 'O2优化', '分治', '字典树 Trie']
---
# 『MdOI R1』Path
## 题目描述

给定一棵 $n$ 个点的无根树，边有边权。

令 $V(x,y),E(x,y)$ 分别表示树上 $x,y$ 之间的简单路径上的所有点的集合和所有边的集合，特别地，当 $x=y$ 时，$V(x,y) = \{x\}$，$E(x,y) = \varnothing$。

再令边集 $E$ 的权值 $f(E)$ 为 $E$ 中所有边的权值的 **异或和**，当 $E = \varnothing$ 时，$f(E) = 0$。

现在，要你求出
$$
\max_{1\le x,y,u,v \le n,V(x,y)\cap V(u,v) = \varnothing}(f(E(x,y)) + f(E(u,v)))
$$
通俗的讲，你要选择两条简单路径，满足没有重合的点，且边权异或和之和最大。
## 输入格式

第一行一个整数 $n$，表示树上点的个数。

接下来 $n-1$ 行，每行三个整数 $x,y,w$，表示编号为 $x$ 和 $y$ 的点之间有一条权值为 $w$ 的边。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
9
1 2 1
1 3 7
2 4 8
3 5 3
4 6 3
3 7 3
7 8 5
7 9 2

```
### 样例输出 #1
```
21

```
### 样例输入 #2
```
3
1 2 2
2 3 1

```
### 样例输出 #2
```
2

```
## 提示

【样例 1 解释】

样例中的树如图所示，选择标红色和蓝色的两条路径，满足没有重合的点，且边权异或和之和最大，为 $(7\oplus 1\oplus 8)+(5\oplus 2)=21$（其中 $\oplus$ 表示异或运算）。

![](https://cdn.luogu.com.cn/upload/image_hosting/jen9sxcf.png)

【样例 2 解释】

样例中的树如图所示，为一条链的形状，选择标红色和蓝色的两条路径，蓝色路径退化成了一个点，使异或和之和达到最大值 $2+0=2$。注意红色路径并不能延申到 $3$，否则蓝色路径将无法存在。

![](https://cdn.luogu.com.cn/upload/image_hosting/1xzo1lh2.png)

---

【数据范围】

**本题采用捆绑测试。**

| 子任务编号 |    $n\leq$     |  特殊性质   | 分值 | 时限 |
| :--------: | :------------: | :---------: | :--: | :--: |
|     1      |      $50$      |     无      |  12  |  1s  |
|     2      | $2\times 10^3$ |     无      |  28  |  2s  |
|     3      | $2\times 10^4$ | $y = x + 1$ |  20  |  3s  |
|     4      | $3\times 10^4$ |     无      |  40  | 3.5s |

对于 $100\%$ 的数据，$2\leq n\leq 3\times 10^4$，$1\leq x,y\leq n$，$0\leq w\leq 10^9$。


---

---
title: "[省选联考 2020 A 卷] 树"
layout: "post"
diff: 省选/NOI-
pid: P6623
tag: ['2020', '倍增', '各省省选', '字典树 Trie', '位运算']
---
# [省选联考 2020 A 卷] 树
## 题目描述

给定一棵 $n$ 个结点的有根树 $T$，结点从 $1$ 开始编号，根结点为 $1$ 号结点，每个结点有一个正整数权值 $v_i$。

设 $x$ 号结点的子树内（包含 $x$ 自身）的所有结点编号为 $c_1,c_2,\dots,c_k$，定义 $x$ 的价值为：

$
val(x)=(v_{c_1}+d(c_1,x)) \oplus (v_{c_2}+d(c_2,x)) \oplus \cdots \oplus (v_{c_k}+d(c_k, x))
$

其中 $d(x,y)$ 表示树上 $x$ 号结点与 $y$ 号结点间唯一简单路径所包含的边数，$d(x, x) = 0$。$\oplus$ 表示异或运算。

请你求出 $\sum\limits_{i=1}^n val(i)$ 的结果。

## 输入格式

第一行一个正整数 $n$ 表示树的大小。

第二行 $n$ 个正整数表示 $v_i$。

接下来一行 $n-1$ 个正整数，依次表示 $2$ 号结点到 $n$ 号结点，每个结点的父亲编号 $p_i$。

## 输出格式

仅一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5
5 4 1 2 3
1 1 2 2
```
### 样例输出 #1
```
12
```
## 提示

【样例解释 $1$】

$val(1)=(5+0)\oplus(4+1)\oplus(1+1)\oplus(2+2)\oplus(3+2)=3$。

$val(2)=(4+0)\oplus(2+1)\oplus(3+1) = 3$。

$val(3)=(1+0)=1$。

$val(4)=(2+0)=2$。

$val(5)=(3+0)=3$。

和为 $12$。

【数据范围】

对于 $10\%$ 的数据：$1\leq n\leq 2501$；

对于 $40\%$ 的数据：$1\leq n\leq 152501$；

另有 $20\%$ 的数据：所有 $p_i=i-1$（$2\leq i\leq n$）；

另有 $20\%$ 的数据：所有 $v_i=1$（$1\leq i\leq n$）；

对于 $100\%$ 的数据：$1\leq n,v_i \leq 525010$，$1\leq p_i\leq n$。


---

---
title: "「C.E.L.U-02」简易输入法"
layout: "post"
diff: 省选/NOI-
pid: P7475
tag: ['平衡树', 'O2优化', '树套树', '字典树 Trie']
---
# 「C.E.L.U-02」简易输入法
## 题目背景

YQH 有一个伟大的梦想，他想成为全世界最强的男人。为了实现这一个目标，他准备从一个简易的输入法入手开始征程。
## 题目描述

这个简易输入法原先有一个词典 $\text{U}$，用户输入时，输入法从用户处读入一个字符串 $s$ ，以及一个整数 $x$ 对于这个字符串有以下几种情形：  
设$s_i \in \text{U} $ 且 $s$ 为 $s_i$ 的前缀的个数为 $a$。  

当 $a\ge x$ 时，请输出按照以输出次数从大到小为第一关键字，以字典序为第二关键字排序后的第 $x$ 个 $s_i$，并将其输出次数加 $1$。    

当 $x>a>0$ 时，请输出按照以输出次数从大到小为第一关键字，以字典序为第二关键字排序后的最后一个 $s_i$，并将其输出次数加 $1$。  

当 $a=0$ 时，输出 `404Error`。  
## 输入格式

第$1$行输入一个整数 $n$，代表 $\text{U}$ 中原有 $n$ 个单词，每个原始存在的单词一开始输入次数都是 $0$。  

第 $2$ 至 $n+1$ 行，每行输入一个字符串 $str$，代表一个词典中原来出现的单词。  

第 $n+2$ 行输入一个整数 $m$，代表用户进行了 $m$ 次操作。  

第 $n+3$ 至 $n+m+2$ 行，输入一个字符串 $s$ 和一个整数 $x$ ，含义在题目描述中已经说了。 
## 输出格式

对于每一个用户的 $1$ 操作，输出一个字符串。
## 样例

### 样例输入 #1
```
3
fan
fantasy
father
6
fat 1
fa 1
fan 1
fan 1
fa 1
fant 1
```
### 样例输出 #1
```
father
father
fan
fan
fan
fantasy
```
### 样例输入 #2
```
5
uva
usaco
usa
usssu
konjac
11
u 2
u 2
kkk 1
uv 2
us 3
u 4
u 1
u 2
k 1
u 3
usa 1
```
### 样例输出 #2
```
usaco
usa
404Error
uva
usssu
uva
uva
usa
konjac
usaco
usa
```
## 提示

### 样例解释 

**样例解释一**

`fat` 为前缀只有 $1$ 个，故输出 `father`，并将其输出次数加 $1$。  
`fa` 为前缀中输出次数最多是 `father`，故输出它，并将其输出次数加 $1$。  
`fan` 为前缀中输出次数都是 $0$，但 `fan` 字典序最小，故输出它，并将其输出次数加 $1$。  
`fan` 为前缀 `fan` 输出次数最多，故输出 `fan`，并将其输出次数加 $1$。  
`fa` 为前缀中输出次数最多是 `fan`，故输出它，并将其输出次数加 $1$。  
`fant` 为前缀只有一个单词 `fantasy`，故输出它，并将其输出次数加 $1$。

 ### 数据范围

| 数据编号 | $n$ | $m$ | $x$ | $\sum str$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim 2$ | $\le100$ | $\le100$ | $=1$ | $\le10^3$ |
| $3\sim 4$ | $\le100$ | $\le100$ | $\diagdown$ | $10^3$ |
| $5\sim 8$ | $\le5\times10^4$ | $\le10^5$ | $=1$ | $\le5\times10^5$ |
| $9\sim 14$ | $\le10^4$ | $\le10^5$ | $\diagdown$ | $\le10^5$ |
| $15\sim 20$ | $\le5\times10^4$ | $\le10^5$ | $\diagdown$ | $\le5\times10^5$ |

对于$100\%$的数据，$|s|,|str|\le10,1\leq x\le10^4$，所有字母都是小写字母。


---

---
title: "[CoE R5] 斑马王子"
layout: "post"
diff: 省选/NOI-
pid: P8582
tag: ['线段树', '洛谷原创', 'O2优化', '字典树 Trie', '位运算', '洛谷月赛']
---
# [CoE R5] 斑马王子
## 题目背景

#### 注意：此题 Sub #4 中 $opt_i=3$，可视作 $opt_i=0$。数据将稍后修复，修复后将另行通知。

#### UPD: 已修复。
## 题目描述

**题意简述**

有一长度为 $k+1$ 的数组 $s$，下标依次为 $0$ 到 $k$，初始时有 $s_i = 0 \ (0 \leqslant i \leqslant k)$。
接下来给定 $n$ 个非负整数二元组 $(l_i,\ r_i)$，记 $T = \bigcup\limits_{i = 1}^n [l_i,\ r_i] $，将所有符合 $i \in T \bigcap \mathbb{Z}$ 的 $s_i$ 赋值为 $1$。
在任意时刻，记 $S =\{ x |x \in \mathbb{Z} \bigwedge x \in [0,\ k] \bigwedge s_x = 0 \}$。接下来给定 $m$ 个非负整数三元组 $(opt_i,\ a_i,\ b_i)$。

当 $opt_i = 0$ 时，求：

$$t_i = \sum\limits_{x = a_i}^{b_i} \min\limits_{y \in S}(x \oplus y)$$

当 $opt_i = 1$ 时，将所有符合 $i \in [a_i,\ b_i] \bigcap \mathbb{Z}$ 的 $s_i$ 赋值为 $1$。

当 $opt_i = 2$ 时，将所有符合 $i \in [a_i,\ b_i] \bigcap \mathbb{Z}$ 的 $s_i$ 赋值为 $0$。

符号 $\mathbb{Z}$ 表示全体整数，$\oplus$ 表示异或。

---

**原版题面**

『斑马王子』统治着无垠的草原。

一条小河无息地流淌在草原的中央，与河流源头距离为 $y$ 的草地被赋予了 $y \ (0 \leqslant y \leqslant k)$ 的『膜力』。

第 $x \ (0 \leqslant x \leqslant k)$ 天，『斑马王子』的『潜力智商』为 $x$。

他会来到一片自己心仪的草地用膳，并以 $x \oplus y$ 的『智商』开始新的一天。

有一种叫『猎人』的生物，热衷于剥夺草原居民的生命。

他们初始时设立了 $n$ 个形如 $(l_i,\ r_i) \ (0 \leqslant l_i \leqslant r_i \leqslant k)$ 的营地，用『枪』屠杀着所有在 $[l_i,\ r_i]$ 中驻足的生灵。

作为『斑马王子』的得力大臣，你需要回答他的若干个问题，以保证草原的安全。

在风云变幻的草原上，会依次发生 $m$ 个形如 $(opt_i,\ a_i,\ b_i) \ (0 \leqslant a_i \leqslant b_i \leqslant k , \ opt_i \in \{0,\ 1,\ 2\})$ 的事件。

当 $opt_i = 1$ 时，事件 $i$ 代表猎人在 $[a_i,\ b_i]$ 中全部驻扎了新营地。

当 $opt_i = 2$ 时，事件 $i$ 代表斑马王子英勇的部队摧毁了 $[a_i,\ b_i]$ 中的全部营地。

而当 $opt_i = 0$ 时，斑马王子向你发出了灵魂拷问：

每一个问题中，『斑马王子』希望从第 $a_i$ 到第 $b_i$ 天 $(0 \leqslant a_i \leqslant b_i \leqslant k)$，在非『猎人』营地的草地用膳。『斑马王子』希望知道从第 $a_i$ 到 $b_i$ 天，『智商』之和的最小可能值 $t_i$。

你苦思冥想，忽然，『枪』的吼叫声撕裂了空气，如果不在 $1 \ sec$ 内回答问题 $\dots \dots$
## 输入格式

第一行输入整数 $n, \ m, \ k$。

接下来 $n$ 行，每行两个整数 $l_i, \ r_i$，表示『猎人』的一个营地。

接下来 $m$ 行，每行三个整数 $opt_i,\ a_i,\ b_i$，表示一组操作。
## 输出格式

对于第 $i$ 组操作 $(1 \leqslant i \leqslant m)$，当 $opt_i = 1$ 或 $opt_i = 2$ 时，不需要输出。

当 $opt_i = 0$ 时，当所有草地都属于猎人的营地时，输出一行 ``Death``,否则输出一行一个整数，表示 $t_i$。
## 样例

### 样例输入 #1
```
0 16 3
0 0 3
1 3 3
0 0 3
1 1 2
0 0 3
2 1 3
0 0 3
1 0 0
1 1 1
0 0 3
0 1 2
0 1 3
1 2 3
0 2 3
2 3 3
0 2 3
```
### 样例输出 #1
```
0
1
6
0
4
2
2
Death
1
```
## 提示

**数据范围**

**本题采用捆绑测试。**

$\texttt{Subtask 1 (5 pts)}$：对于 $5\%$ 的数据，保证 $0 \leqslant n,m,k \leqslant 20$。

$\texttt{Subtask 2 (5 pts)}$：对于 $5\%$ 的数据，保证 $0 \leqslant n,m,k \leqslant 500$。

$\texttt{Subtask 3 (15 pts)}$：对于 $15\%$ 的数据，保证 $0 \leqslant n,m,k \leqslant 4000$。

$\texttt{Subtask 4 (5 pts)}$：对于 $5\%$ 的数据，保证 $opt_i = 0$。

$\texttt{Subtask 5 (70 pts)}$：无特殊限制。

对于 $100 \%$ 的数据， $0 \leqslant n,\ m,\ k \leqslant 2 \times 10^5$，$0 \leqslant l_i \leqslant r_i \leqslant k$，$0 \leqslant a_i \leqslant b_i \leqslant k$，$opt_i \in \{0,\ 1,\ 2\}$。


---

---
title: "[北大集训 2021] 经典游戏"
layout: "post"
diff: 省选/NOI-
pid: P8994
tag: ['树状数组', '2021', 'O2优化', '分治', '树链剖分', '字典树 Trie', 'SG 函数']
---
# [北大集训 2021] 经典游戏
## 题目背景

CTT2021 D4T2
## 题目描述

某天，`C` 和 `K` 觉得很无聊，于是决定玩一个经典小游戏：

在一棵有 $n$ 个结点的有根树上，标号为 $i$ 的节点上有 $a_i$ 个棋子。游戏时玩家轮流操作，每次可以将任意一个节点 $u$ 上的一个棋子放置到任意一个点 $v \in U(u)$上，其中 $U(u)=subtree\{u\}\setminus\{u\}$ ，表示 $u$ 的子树内（不包含 $u$ 本身）的点组成的集合。不能进行操作者失败。

而 `C` 和 `K` 作为 `P**` 和 `T**` 的在读学生，这种一眼就能找出必胜策略的游戏实在是索然无味，于是两人觉得，每个人给自己一个特殊能力可能会比较有趣：

`C` 在开始游戏之前，**可以选择**将当前树的树根 $R$ 换到与 $R$ 相邻的任意一个点 $R^{\prime}$ 上。定义两个点相邻当且仅当这两个点有边直接相连。

`K` 在开始游戏之前，**必须选择**树上的一个节点，在上面加上一颗棋子。

`C` 和 `K` 决定玩 $m$ 局游戏。每局游戏的流程如下：

1. 游戏开始前，`C` 和 `K` 会商量好，先在标号为 $x$ 的节点上放上一个棋子，然后将树根设为 $y$。
2. 之后 `C` 可以选择是否发动特殊能力，`C` 决策完之后 `K` 可以选择是否发动特殊能力。
3. 特殊能力的决策结束后，会在这棵树上进行一局 `C` 先手、`K` 后手的游戏。游戏完成后会将树上棋子的状态**还原到流程 `1` 结束后的状态**。

`C` 觉得这个游戏可以出成一个简单题，于是他决定考考你：`C` 在每局游戏的第二步的时候，有多少种决策方式使得不管 `K` 如何进行特殊能力的操作，开始游戏时都存在**必胜策略**？两种决策方式不同，**当且仅当**两种决策**更换的树根** $R^{\prime}$ **不同**，或者**两者中仅有一个没有发动特殊能力**。

## 输入格式

第一行包括一个整数，表示该测试点所在的子任务的分数。你可以使用这个信息判断该测试点满足的特殊性质。特别的，下发样例中此行使用 $0$ 代替。

第二行包含两个用空格隔开的正整数 $n, m$，表示树的节点数目以及游戏的轮数。树上的节点从 $1$ 到 $n$ 编号。

接下来 $n-1$ 行，每行包含两个用空格隔开的正整数 $u_i,v_i$，满足 $1 \le u_i,v_i \le n$，表示编号为 $u_i$ 和 $v_i$ 的节点之间有边直接相连。

接下来一行包含 $n$ 个用空格隔开的整数 $a_1,a_2,\ldots,a_n$，满足 $0 \leq a_1,a_2,\ldots,a_n \leq 10^9$。

接下来 $m$ 行，每行包含两个用空格隔开的正整数 $x, y$ 描述一局游戏，满足 $1 \le x,y \le n$。

## 输出格式


你需要输出 $m$ 行，其中第 $i$ 行应当包含一个非负整数 $x$ 表示第 $i$ 局游戏中，`C` 存在多少种使用特殊能力的决策方案，使得 `C` 在这局游戏中存在必胜策略。注意，**不使用特殊能力**也是一种**可能可行**的决策方案。

## 样例

### 样例输入 #1
```
0
5 2
1 2
1 3
2 4
2 5
1 0 1 0 1
2 2
4 4
```
### 样例输出 #1
```
2
1

```
### 样例输入 #2
```
0
10 10
6 3
7 4
8 2
2 1
9 1
1 3
3 4
4 5
5 10
0 0 1 1 1 0 1 1 0 0 
8 3
2 3
7 10
7 3
6 7
8 5
9 8
2 10
5 4
3 9

```
### 样例输出 #2
```
1
1
0
1
1
1
0
0
2
1

```
## 提示

| 子任务分数 | $1\le n,m\le$ | $\max\{a_1,a_2,\dots,a_n\}\le$ |              特殊性质              |
| :--------: | :-----------: | :----------------------------: | :--------------------------------: |
|    $16$    |      $5$      |              $1$               |                 无                 |
|    $15$    |     $300$     |              $1$               |                 无                 |
|    $14$    |    $5000$     |             $10^9$             |                 无                 |
|    $13$    |   $100000$    |             $10^9$             |        保证给出的树是一条链        |
|    $12$    |   $100000$    |             $10^9$             | 保证给出的树存在一个点度数为 $n-1$ |
|    $11$    |   $100000$    |             $10^9$             |   保证 $m$ 次游戏初始给定根一致    |
|    $10$    |   $500000$    |             $10^9$             |                 无                 |
|    $9$     |   $1000000$   |             $10^9$             |                 无                 |





---

---
title: "[NFLSPC #6] 啊，忘记了。"
layout: "post"
diff: 省选/NOI-
pid: P9935
tag: ['字符串', '线段树', 'O2优化', '哈希 hashing', '虚树', '字典树 Trie', 'AC 自动机']
---
# [NFLSPC #6] 啊，忘记了。
## 题目背景

> 好像忘了什么事…… 算了，想必不是什么重要的事吧。
## 题目描述



你在你的电脑上发现了 $n$ 份文本。冥冥之中，你没来由地感觉这似乎全都是一份记录的复制。

- 首先，原始记录是一个长度未知（甚至可以为空）的字符串，称作 **记录串**。对于一份复制，其将记录串切成了三段 **可以为空** 的字符串 **片段**。**每份复制中切割方案不保证相同**。你暂且将这三份 **片段** 依次称作 **前面**，**中间** 和 **后面**。
- 某些复制中的某些片段可能被忘记了。具体而言，前面有可能被替换为 `QIANMIANWANGLE`，中间有可能被替换为 `ZHONGJIANWANGLE`，后面有可能被替换为 `HOUMIANWANGLE`；在发生替换的场合，表示这一段片段被 **完全遗忘** 了；否则，表示该片段被 **完整保存**。
- 你有一种预感，记录串中的所有字符都是 **小写英文字符**。
- $n$ 份复制不一定自洽。

你的目标是，寻找初始的记录串。这个记录串需要满足所有字符均是小写英文字符。你希望其匹配尽量多的复制串。

- 记录串与复制串匹配的要求是，存在记录串的一种划分，使得其中记录串的三段与复制串的三段分别相同，或者复制串中这段划分忘了（此时本段划分中，记录串为任何可以为空的小写英文字符串均合法）。

你希望求出该记录串能匹配的最多复制串数目。**至于记录串本身，你感觉它并不是很重要，所以你不需要求出它**。

> / 我，毋畏遗忘 /
## 输入格式

**为了避免输入过大，输入进行了一定程度的压缩。请务必认真阅读输入格式**。

第一行一个正整数 $n$，表示记录数目。

接下来 $n$ 行，每行三个非空字符串，其中第一段要么是非空小写字符串，要么是 `Q`（表示 `QIANMIANWANGLE`），要么是 `E` 表示这是一段空串（因为空串不可见所以选取 `E` 作为占位符），不存在其它可能；第二段则是非空小写字符串、`Z`（表示 `ZHONGJIANWANGLE`）、`E` 三者之一；最后一段是非空小写字符串、`H`（表示 `HOUMIANWANGLE`）、`E` 三者之一。
## 输出格式

一行一个整数，表示所有记录串中，能匹配的最多的复制的数目。

## 样例

### 样例输入 #1
```
3
nflsalgo Z H
Q nflspc H
Q Z qidong

```
### 样例输出 #1
```
3

```
## 提示

### 样例 1 解释

你希望这个串是 `nflsalgonflspcqidong`。你确信，不会再有其它串比它更匹配现存的记录了。

### 数据范围与约定

对于所有数据，保证输入的所有字符串长度之和不超过 $5\times 10 ^ 5$。

- 子任务 1（$30$ 分）：保证所有复制的 “后面” 段都是 `H`。
- 子任务 2（$70$ 分）：无特殊限制。

Source：NFLSPC #6 K by Troverld


---

