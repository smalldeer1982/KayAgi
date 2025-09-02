---
title: "「DLESS-2」XOR and Even"
layout: "post"
diff: 省选/NOI-
pid: P12827
tag: ['O2优化', '数位 DP', '线性基', '洛谷比赛']
---
# 「DLESS-2」XOR and Even
## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，$q$ 次询问，每次询问形如以下两种中的一种：

- ```0 l r x```: 在区间 $[l,r]$ 中选出**偶数**个数（可以是 $0$ 个，此时异或和为 $0$，下同），使得这些数的异或和小于等于 $x$，求方案数，答案对 $10^9+7$ 取模。
- ```1 l r x```: 在区间 $[l,r]$ 中选出**偶数**个数，使得这些数的异或和异或上 $x$ 最大，求这个最大值。
## 输入格式

本题有多组测试数据，第一行输入一个数 $T$ 表示数据组数。

对于每组数据，第一行输入两个数 $n,q$。

第二行输入 $n$ 个数，代表序列 $a$。

接下来 $q$ 行，每行一次询问，格式如问题描述所示。
## 输出格式

对于每次询问，输出一行一个数，表示答案。
## 样例

### 样例输入 #1
```
2
5 6
1 2 4 8 16
0 1 3 3
0 1 4 3
1 2 4 0
1 2 4 1
0 1 5 114514
0 1 4 5
6 7
1 1 4 5 1 4
0 1 3 0
1 2 4 0
1 1 2 1
1 2 6 0
1 1 4 5
0 2 4 4
1 1 2 0
```
### 样例输出 #1
```
2
2
12
13
16
3
2
5
1
5
5
3
0
```
## 提示

对于所有数据，保证：

- $1\le T\le 10^4$
- $1\le n,\sum n\le 5\times10^5$
- $1\le q,\sum q\le 5\times10^5$
- $1\le l<r\le n$
- $0\le a_i,x<2^{30}$

**本题采用捆绑测试**，各子任务描述如下：

| Subtask | $\sum n\le$ | $\sum q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ | $1000$ | 无 | $10$ |
| $2$ | $1000$ | $1000$ | A | $15$ |
| $3$ | $1000$ | $1000$ | B | $15$ |
| $4$ | $1000$ | $1000$ | 无 | $10$ |
| $5$ | $5\times10^4$ | $5\times10^4$ | 无 | $10$ |
| $6$ | $5\times10^5$ | $5\times10^5$ | A | $15$ |
| $7$ | $5\times10^5$ | $5\times10^5$ | B | $15$ |
| $8$ | $5\times10^5$ | $5\times10^5$ | 无 | $10$ |

特殊性质 A：操作类型一定为 $0$。

特殊性质 B：操作类型一定为 $1$。


---

---
title: "[GCJ 2010 #3] Different Sum"
layout: "post"
diff: 省选/NOI-
pid: P13406
tag: ['动态规划 DP', '2010', '数位 DP', 'Google Code Jam']
---
# [GCJ 2010 #3] Different Sum
## 题目描述

We have come up with a wonderful problem for Google Code Jam 2010 that involves contestants solving a cryptarithm. But we need your help in creating testcases for the problem; more precisely, we're concerned with addition equations that are good enough (in the sense defined below) for conversion into cryptarithms.

You don't need to know what a cryptarithm is to solve this problem, as we'll provide all required definitions. We define a cryptarithm equation to be an addition equation written in such a way that all summands (numbers being added) and the sum are aligned to the same right border like this:

```
124
 31
 25
---
180
```

Additionally, for each column of a cryptarithm equation, all digits of the summands in that column must be different. Note that we don't include the sum in this constraint. So for example in the above equation the first column contains only digit $1$, the second column contains digits $2,3$ and $2$, and the third column contains digits $4, 1$ and $5$. This equation is not a cryptarithm equation since the second column contains two $2$'s. However, it would be a cryptarithm equation if we replaced the last summand with $15$ (and the sum with $170$).

Note that summands in a cryptarithm equation are always positive and written without leading zeros. The order of summands is not important (in other words, two equations which differ only in the order of the summands are considered the same).

The example above was in base $10$, but we're also interested in cryptarithm equations in other bases. Note that a "digit" in base $b$ could mean any integer between $0$ and $b-1$. Here is a cryptarithm equation in base $23$:

```
 I7B
 JJJ
----
1F47
```

In this example, "I" stands for digit $18$, "B" stands for digit $11$, "J" stands for digit $19$, and "F" stands for digit $15$. In decimal notation, the two summands are $18\times 23^2 + 7\times 23 + 11 = 9694$ and $19\times 23^2 + 19\times 23 + 19 = 10507$, and the sum is $1\times 23^3 + 15\times 23^2 + 4\times 23 + 7 = 20201$. Please note that denoting digits of $10$ and more with letters was done purely for the clarity of the example; it doesn't really matter in this problem how exactly we denote such digits in writing.

How many cryptarithm equations are there with the given sum $N$ in the given base $B$?

Since the answer might be very large, please output it modulo $1000000007$.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each contains two positive integers $N$ and $B$. All input numbers are given in base $10$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is the number of different cryptarithm equations with the given sum. Since this number can be very big, please output it modulo $1000000007$. Of course, the output itself should be in base $10$.
## 样例

### 样例输入 #1
```
2
6 10
8 4
```
### 样例输出 #1
```
Case #1: 4
Case #2: 4
```
## 提示

**Sample Explanation**

Here are the $4$ cryptarithm equations with sum $6$:

```
6   1   2   1
-   5   4   2
6   -   -   3
    6   6   -
            6
```

And here are the $4$ cryptarithm equations in base $4$ with sum $8=(20)_4$:

```
20   11   13   10
--    3    1    3
20   --   --    1
     20   20   --
               20
```

**Limits**

- $1 \leq T \leq 20$.

**Small dataset (7 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 100$.
- $2 \leq B \leq 10$.

**Large dataset (22 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 20 seconds.
- $1 \leq N \leq 10^{18}$.
- $2 \leq B \leq 70$.


---

---
title: "杠杆数"
layout: "post"
diff: 省选/NOI-
pid: P1831
tag: ['动态规划 DP', '枚举', '数位 DP']
---
# 杠杆数
## 题目描述

如果把一个数的某一位当成支点，且左边的数字到这个点的力矩和等于右边的数字到这个点的力矩和，那么这个数就可以被叫成杠杆数。

比如 $4139$ 就是杠杆数，把 $3$ 当成支点，我们有这样的等式：$4\times 2+1\times 1=9\times 1$。

给定区间 $[x,y]$，求出在 $[x,y]$ 中有几个杠杆数。
## 输入格式

两个数，表示 $x,y$。
## 输出格式

一个输出，表示区间 $[x,y]$ 中杠杆数的个数。

## 样例

### 样例输入 #1
```
7604 24324
```
### 样例输出 #1
```
897
```
## 提示

### 数据范围及约定

- 对于 $40\%$ 的数据，$x \le y \le x+10^5$；
- 对于 $100\%$ 的数据，$1 \le x \le y \le 10^{18}$。


---

---
title: "[HNOI2002] Kathy函数"
layout: "post"
diff: 省选/NOI-
pid: P2235
tag: ['动态规划 DP', '高精度', '2002', '各省省选', '湖南', '数位 DP']
---
# [HNOI2002] Kathy函数
## 题目描述

Tiger 非常喜欢数学，所以他参加了学校组织的数学课外兴趣小组。在兴趣小组的学习当中，老师向 Tiger 介绍了 Kathy 函数，Kathy 函数是这样定义的：

$$
\left\{
\begin{aligned}
&f(1)=1\\
&f(3)=3\\
&f(2n)=f(n)\\
&f(4n+1)=2f(2n+1)-f(n)\\
&f(4n+3)=3f(2n+1)-2f(n)
\end{aligned}
\right.
$$

Tiger 对 Kathy 函数产生了浓厚的兴趣，他通过研究发现有很多的数 $n$ 都满足 $f(n)=n$。

对于一个给定的数 $m$，他希望你求出所有的满足 $f(n)=n$ 的正整数 $n$ 的个数，其中 $n\leq m$。
## 输入格式

输入只有一行一个整数，表示 $m$。
## 输出格式

输出一行一个整数，表示 $n$。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq m \leq 10^{100}$。


---

---
title: "[SDOI2010] 代码拍卖会"
layout: "post"
diff: 省选/NOI-
pid: P2481
tag: ['2010', '各省省选', '山东', '数位 DP', '组合数学']
---
# [SDOI2010] 代码拍卖会
## 题目描述

随着 iPig 在 P++ 语言上的造诣日益提升，他形成了自己一套完整的代码库。猪王国想参加 POI 的童鞋们都争先恐后问 iPig 索要代码库。iPig 不想把代码库给所有想要的小猪，只想给其中的一部分既关系好又肯出钱的小猪，于是他决定举行了一个超大型拍卖会。

在拍卖会上，所有的 $N$ 头小猪将会按照和 iPig 的好感度从低到高，从左到右地在 iPig 面前站成一排。每个小猪身上都有 $9$ 猪币（与人民币汇率不明），从最左边开始，每个小猪依次举起一块牌子，上面写上想付出的买代码库的猪币数量（$1$ 到 $9$ 之间的一个整数）。大家都知道，如果自己付的钱比左边的猪少，肯定得不到梦寐以求的代码库，因此从第二只起，每只猪出的钱都大于等于左边猪出的价钱。最终出的钱最多的小猪（们）会得到 iPig 的代码库真传，向着保送 PKU（Pig Kingdom University）的梦想前进。

iPig 对自己想到的这个点子感到十分满意，在去现场的路上，iPig 就在想象拍卖会上会出现的场景，例如一共会出现多少种出价情况之类的问题，但这些问题都太简单了，iPig 早已不感兴趣了，他想要去研究更加困难的问题。iPig 发现如果他从台上往下看，所有小猪举的牌子从左到右将会正好构成一个 $N$ 位的整数，他现在想要挑战的问题是所有可能构成的整数中能正好被 $P$ 整除的有多少个。由于答案过大，他只想要知道答案 $\bmod\ 999911659$ 就行了。
## 输入格式

有且仅有一行两个数 $N\ (1 \le N \le 10^{18})$ 和 $P\ (1 \le P \le 500)$，用一个空格分开。
## 输出格式

有且仅有一行一个数，表示答案除以 $999911659$ 的余数。

## 样例

### 样例输入 #1
```
2 3
```
### 样例输出 #1
```
15
```
## 提示

### 样例解释

方案可以是：$12,\allowbreak 15,\allowbreak 18,\allowbreak 24,\allowbreak 27,\allowbreak 33,\allowbreak 36,\allowbreak 39,\allowbreak 45,\allowbreak 48,\allowbreak 57,\allowbreak 66,\allowbreak 69,\allowbreak 78,\allowbreak 99$，共 $15$ 种。

### 数据规模

![](https://cdn.luogu.com.cn/upload/image_hosting/y0nme218.png)



---

---
title: "[SCOI2013] 数数"
layout: "post"
diff: 省选/NOI-
pid: P3281
tag: ['字符串', '2013', '四川', '数位 DP', '进制']
---
# [SCOI2013] 数数
## 题目描述

Fish 是一条生活在海里的鱼，有一天他很无聊，就开始数数玩。他数数玩的具体规则是：

1. 确定数数的进制B

2. 确定一个数数的区间[L, R]

3. 对于[L, R] 间的每一个数，把该数视为一个字符串，列出该字符串的每一个（连续的）子串对应的B进制数的值。

4. 对所有列出的数求和。现在Fish 数了一遍数，但是不确定自己的结果是否正确了。由于[L, R] 较大，他没有多余精力去验证是否正确，你能写一个程序来帮他验证吗？

## 输入格式

输入包含三行。

第一行仅有一个数B，表示数数的进制。

第二行有N +1 个数，第一个数为N，表示数L 在B 进制下的长度为N，接下里的N个数从高位到低位的表示数L 的具体每一位。

第三行有M+ 1 个数，第一个数为M，表示数R 在B 进制下的长度为M，接下里的M个数从高位到低位的表示数R 的具体每一位。

## 输出格式

输出仅一行，即按照Fish 数数规则的结果，结果用10 进制表示，由于该数可能很大，输出该数模上20130427的模数。

数据中有 $r<l$ 的情况，输出的是 $-ans[r+1,l-1]\bmod 20130427$
## 样例

### 样例输入 #1
```
10
3 1 0 3
3 1 0 3
```
### 样例输出 #1
```
120

```
## 提示

【样例解释】

[103, 103] 之间仅有数103，该数的所有子串包括1, 10, 103, 0, 03, 3，其和为120。

【数据范围与约定】

20% 数据，0 <= L <= R <= 10^5。

50% 数据，2 <= B <= 1000，1 <= N,M <= 1000。

100% 数据，2 <= B <= 10^5，1 <= N,M <= 10^5。



---

---
title: "[SCOI2014] 方伯伯的商场之旅"
layout: "post"
diff: 省选/NOI-
pid: P3286
tag: ['动态规划 DP', '2014', '四川', 'O2优化', '枚举', '数位 DP']
---
# [SCOI2014] 方伯伯的商场之旅
## 题目描述

方伯伯有一天去参加一个商场举办的游戏。商场派了一些工作人员排成一行。每个人面前有几堆石子。

说来也巧，位置在 $i$ 的人面前的第 $j$ 堆的石子的数量，刚好是 $i$ 写成 $K$ 进制后的第 $j$ 位。现在方伯伯要玩一个游戏，商场会给方伯伯两个整数 $L,R$。

方伯伯要把位置在 $[L, R]$ 中的每个人的石子都合并成一堆石子。每次操作，他可以选择一个人面前的两堆石子，将其中的一堆中的某些石子移动到另一堆，代价是移动的石子数量 $\times$ 移动的距离。

商场承诺，方伯伯只要完成任务，就给他一些椰子，代价越小，给他的椰子越多。所以方伯伯很着急，想请你告诉他最少的代价是多少。例如：$10$ 进制下的位置在 $12312$ 的人，合并石子的最少代价为：$1 \times 2 + 2 \times 1 + 3 \times 0 + 1 \times1 + 2 \times 2 = 9$即把所有的石子都合并在第三堆。

## 输入格式

输入仅有 $1$ 行，包含 $3$ 个用空格分隔的整数 $L,R,K$，表示商场给方伯伯的 $2$ 个整数，以及进制数。
## 输出格式

输出仅有 $1$ 行，包含 $1$ 个整数，表示最少的代价。
## 样例

### 样例输入 #1
```
3 8 3
```
### 样例输出 #1
```
5
```
## 提示

对于 $100\%$ 的数据，$1 \le L \le R \le 10^{15}, 2 \le K \le 20$。


---

---
title: "[SDOI2013] 淘金"
layout: "post"
diff: 省选/NOI-
pid: P3303
tag: ['动态规划 DP', '2013', '山东', '数位 DP']
---
# [SDOI2013] 淘金
## 题目描述

小 Z 在玩一个叫做《淘金者》的游戏。游戏的世界是一个二维坐标。$X$ 轴、$Y$ 轴坐标范围均为$1\ldots N$。初始的时候，所有的整数坐标点上均有一块金子，共 $N^2$ 块。

一阵风吹过，金子的位置发生了一些变化。细心的小 Z 发现，初始在 $(i,j)$ 坐标处的金子会变到 $(f(i),f(j))$ 坐标处。其中 $f(x)$ 表示 $x$ 各位数字的乘积，例如 $f(99)=81,~f(12)=2,~f(10)=0$。

如果金子变化后的坐标不在 $1\ldots N$ 的范围内，我们认为这块金子已经被移出游戏。同时可以发现，对于变化之后的游戏局面，某些坐标上的金子数量可能不止一块，而另外一些坐标上可能已经没有金子。这次变化之后，游戏将不会再对金子的位置和数量进行改变，玩家可以开始进行采集工作。

小 Z 很懒，打算只进行 $K$ 次采集。每次采集可以得到某一个坐标上的所有金子，采集之后，该坐标上的金子数变为 $0$。

现在小 Z 希望知道，对于变化之后的游戏局面，在采集次数为 $K$ 的前提下，最多可以采集到多少块金子？ 答案可能很大，小 Z 希望得到对 $10^9+7$ 取模之后的答案。
## 输入格式

共一行，包含两个正整数 $N, K$。

## 输出格式

一个整数，表示最多可以采集到的金子数量。

## 样例

### 样例输入 #1
```
12 5
```
### 样例输出 #1
```
18
```
## 提示

对于 $100\%$ 的数据，$N \leq 10^{12}, K \leq \min(N^2, 10^5)$。



---

---
title: "[SDOI2014] 数数"
layout: "post"
diff: 省选/NOI-
pid: P3311
tag: ['字符串', '动态规划 DP', '2014', '山东', 'O2优化', '数位 DP', 'AC 自动机']
---
# [SDOI2014] 数数
## 题目描述

我们称一个正整数 $x$ 是幸运数，当且仅当它的十进制表示中不包含数字串集合 $s$ 中任意一个元素作为其子串。例如当 $s = \{22, 333, 0233\}$ 时，$233$ 是幸运数，$2333$、$20233$、$3223$ 不是幸运数。给定 $n$ 和 $s$，计算不大于 $n$ 的幸运数个数。

答案对 $10^9 + 7$ 取模。
## 输入格式

第一行有一个整数，表示 $n$。

第二行有一个整数，表示 $s$ 中的元素个数 $m$。

接下来 $m$ 行，每行一个数字串 $s_i$，表示 $s$ 中的一个元素。
## 输出格式

输出一行一个整数，表示答案对 $10^9 + 7$ 取模的结果。
## 样例

### 样例输入 #1
```
20
3
2
3
14
```
### 样例输出 #1
```
14
```
## 提示

#### 样例 1 解释

除了 $3, 13, 2, 12, 20, 14$ 以外，不大于 $20$ 的整数都是幸运数字。

#### 数据规模与约定

对于全部的测试点，保证：

$1 \leq n < 10^{1201}$，$1 \leq m \leq 100$，$1 \leq \sum_{i = 1}^m |s_i| \leq 1500$，$\min_{i = 1}^m |s_i| \geq 1$，其中 $|s_i|$ 表示字符串 $s_i$ 的长度。$n$ 没有前导 $0$，但是 $s_i$ 可能有前导 $0$。


---

---
title: "SAC#1 - 萌数"
layout: "post"
diff: 省选/NOI-
pid: P3413
tag: ['动态规划 DP', '洛谷原创', '数位 DP', '洛谷月赛']
---
# SAC#1 - 萌数
## 题目背景

本题由世界上最蒟蒻的 SOL 提供。

寂月城网站是完美信息教室的官网。地址：<http://191.101.11.174/mgzd>。

## 题目描述

蒟蒻 SOL 居然觉得数很萌！

好在在他眼里，并不是所有数都是萌的。只有满足“存在长度至少为 $2$ 的回文子串”的数是萌的——也就是说，$101$ 是萌的，因为 $101$ 本身就是一个回文数；$110$ 是萌的，因为包含回文子串 $11$；但是 $102$ 不是萌的，$1201$ 也不是萌的。

现在 SOL 想知道从 $l$ 到 $r$ 的所有整数中有多少个萌数。

由于答案可能很大，所以只需要输出答案对 $1000000007$（$10^9+7$）的余数。
## 输入格式

输入包含仅 $1$ 行，包含两个整数：$l$，$r$。
## 输出格式

输出仅 $1$ 行，包含一个整数，即为答案。

## 样例

### 样例输入 #1
```
1 100
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
100 1000
```
### 样例输出 #2
```
253
```
## 提示

记 $n$ 为 $r$ 在 $10$ 进制下的位数。

对于 $10\%$ 的数据，$n \le 3$。

对于 $30\%$ 的数据，$n \le 6$。

对于 $60\%$ 的数据，$n \le 9$。

对于全部的数据，$n \le 1000$，$l < r$。


------------

2024/2/4 添加一组 hack 数据。


---

---
title: "[COCI 2018/2019 #4] Akvizna"
layout: "post"
diff: 省选/NOI-
pid: P5308
tag: ['2018', '数位 DP', 'COCI（克罗地亚）']
---
# [COCI 2018/2019 #4] Akvizna
## 题目描述

你面临 $n$ 名参赛者的挑战，最终要将他们全部战胜。  
每一轮中，都会淘汰一些选手；你会得到这一轮奖金池中 被淘汰者 除以 这一轮对手总数 比例的奖金。  

例如某一轮有 $10$ 个对手，淘汰了 $3$ 个，那么你将获得奖金池中 $3/10$ 的奖金。  

假设每一轮的奖金池均为一元，`Mirko` 希望通过恰好 $k$ 轮赢得比赛，那么他最多可能获得多少奖金呢？   

你只需要输出答案保留 $9$ 位小数即可。
## 输入格式

一行两个正整数 $n,k$。
## 输出格式

输出一行一个实数表示答案。
## 样例

### 样例输入 #1
```
5 3
```
### 样例输出 #1
```
2.100000000
```
### 样例输入 #2
```
10 10
```
### 样例输出 #2
```
2.928968254
```
## 提示

### 样例1解释：   

最优的情况为：  
第一轮淘汰 $3$ 人，剩下两轮各淘汰 $1$ 人。  
获得奖金为 $\frac{3}{5}+\frac{1}{2}+\frac{1}{1}=2.1$ 元。

### 数据范围：   

对于$20\%$的数据，$1\le n\le 100$。

对于$40\%$的数据，$1\le n \le 3000$。

对于$100\%$的数据，$1\le k \le n \le 10^5$。

本题较卡精度，请留意。


---

---
title: "「SWTR-2」Magical Gates"
layout: "post"
diff: 省选/NOI-
pid: P5674
tag: ['高精度', '数位 DP']
---
# 「SWTR-2」Magical Gates
## 题目背景

小 $\mathrm{A}$ 找到了一张藏宝图。

他顺着藏宝图上的路线来到了一扇古老的大门前，门上有六芒星的图案。

他把手轻轻地放在六芒星上……

霎时间，六芒星光芒大放，四周亮如白昼。

（新增一组大样例）
## 题目描述

小 $\mathrm{A}$ 面前出现了 $10^{1000}$ 扇门，每个门上都写着它自己的编号，分别为 $1,2,3,\dots,10^{1000}$。

这时，守门人小 $\mathrm{M}$  向小 $\mathrm{A}$ 走来。

“这些门，并不普通，它有魔力。”

“我会给你一些区间 $l,r$，请你求出区间 $[l,r]$ 里所有门的魔力值之**和**与魔力值之**积**。”

“因为结果可能很大，请你将结果 $mod\ p$。 ”

“如果你正确地回答了所有询问，你将会拥有这扇门后的所有宝藏。”

“哦，对了，一扇门的魔力值就是其在二进制下 $1$ 的个数。”

简单来说，记第 $i$ 扇门的魔力值为 $d_i$，给定的区间为 $[l,r]$，请求出：

$$\sum_{l}^{r}d_i\bmod\ p \quad \prod_{l}^{r}d_i\bmod\ p$$

由于门的数量实在太多，小 $\mathrm{A}$ 决定向你请求帮助。
## 输入格式

第一行三个正整数 $T,p,n$（$n$ 会在数据范围中说明）。

接下来 $T$ 行，第 $i$ 行两个**正整数** $l_i,r_i$。
## 输出格式

输出 $T$ 行，每行 $2$ 个数，由空格隔开，第 $i$ 行分别为：

$$\sum_{l}^{r}d_i\bmod\ p \quad \prod_{l}^{r}d_i\bmod\ p$$
## 样例

### 样例输入 #1
```
7 1000000007 0
3 7
1 10
1 1048576
20180815 20180830
20180632 20180639
123456789 987654321
123456789987654321 123456789987654321123456789987654321
```
### 样例输出 #1
```
10 24
17 96
10485761 64327945
255 803716286
124 290111979
996409842 54001814
253678327 263109263
```
## 提示

---

### 样例说明

数据 $1$：

$$\sum_{3}^{7}d_i=2+1+2+2+3=10$$

$$\prod_{3}^{7}d_i=2\times 1\times 2\times 2\times 3=24$$

数据 $2$：

$$\sum_{1}^{10}d_i=1+1+2+1+2+2+3+1+2+2=17$$

$$\prod_{1}^{10}d_i=1\times 1\times 2\times 1\times 2\times 2\times 3\times 1\times 2\times 2=96$$

---

### 数据范围与约定

![](https://cdn.luogu.com.cn/upload/image_hosting/zv6ppsk4.png)

为了方便拿部分分，输入格式中的 $n$ 为**该测试点的编号**。

所有具有特殊性质的测试点一共 $31\%$。

对于 $100\%$ 的数据，有 $1\leq n\leq 27,1\leq T \leq 10,10^9 \leq p \leq 1.001\times 10^9,1\leq l\leq r\leq 10^{1000}$，**保证 $p$ 为质数**。

---

对于测试点 $1-20$，时限 $300ms$，剩下的 $7$ 个测试点时限 $2s$。

对于所有测试点，空间限制 $256MB$

---

“吱嘎”一声，封尘千年的大门缓缓打开。

刺眼的金光照了出来……


---

---
title: "[COCI 2006/2007 #6] V"
layout: "post"
diff: 省选/NOI-
pid: P6371
tag: ['2006', 'O2优化', '数位 DP', 'COCI（克罗地亚）']
---
# [COCI 2006/2007 #6] V
## 题目描述

使用给定的数字，组成一些在 $[A,B]$ 之间的数使得这些数每个都能被 $X$ 整除。
## 输入格式

输入第一行包含三个整数 $X,A,B$。

第二行为一个数字串，表示可以使用的数字。一个数字可以使用多次，数字不会重复出现。
## 输出格式

输出一行一个整数，表示在 $[A,B]$ 这个区间用这些给定的数字能组成多少个被 $X$ 整除的数字。
## 样例

### 样例输入 #1
```
2 1 20
0123456789
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
6 100 9294
23689
```
### 样例输出 #2
```
111
```
### 样例输入 #3
```
5 4395 9999999999
12346789
```
### 样例输出 #3
```
0
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1\le X\lt 10^{11}$，$1\le A\le B\lt 10^{11}$。
#### 说明

**题目译自 [COCI2006-2007](https://hsin.hr/coci/archive/2006_2007/) [CONTEST #6](https://hsin.hr/coci/archive/2006_2007/contest6_tasks.pdf) *T5 V***。


---

---
title: "[清华集训 2016] 组合数问题"
layout: "post"
diff: 省选/NOI-
pid: P6669
tag: ['2016', '数位 DP', 'CTT（清华集训/北大集训）']
---
# [清华集训 2016] 组合数问题
## 题目描述

组合数 $C_n^m$ 表示的是从 $n$ 个物品中选出 $m$ 个物品的方案数。举个例子，从 $(1,2,3)$ 三个物品中选择两个物品可以有 $(1,2),(1,3),(2,3)$ 这三种选择方法。根据组合数的定义，我们可以给出计算组合数 $C_n^m$ 的一般公式：

$$C_n^m=\dfrac{n!}{m!(n-m)!}$$

其中 $n!=1×2×⋯×n$。（额外的，当 $n=0$ 时，$n!=1$）

小葱想知道如果给定 $n,m$ 和 $k$，对于所有的 $0≤i≤n,0≤j≤\min(i,m)$ 有多少对 $(i,j)$ 满足 $C^j_i$ 是 $k$ 的倍数。

答案对 $10^9+7$ 取模。
## 输入格式

第一行有两个整数 $t,k$，其中 $t$ 代表该测试点总共有多少组测试数据。

接下来 $t$ 行每行两个整数 $n,m$。

## 输出格式

$t$ 行，每行一个整数代表所有的 $0≤i≤n,0≤j≤\min(i,m)$ 中有多少对 $(i,j)$ 满足 $C^j_i$ 是 $k$ 的倍数。
## 样例

### 样例输入 #1
```
1 2
3 3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
2 5
4 5
6 7
```
### 样例输出 #2
```
0
7
```
### 样例输入 #3
```
3 23
23333333 23333333
233333333 233333333
2333333333 2333333333
```
### 样例输出 #3
```
851883128
959557926
680723120
```
## 提示

#### 样例 $1$ 解释

在所有情况中，只有 $C_{2}^{1}=2$ 是 $2$ 的倍数。

#### 限制与约定

对于 $20\%$ 的测试点，$1≤n,m≤100$；

对于另外 $15\%$ 的测试点，$n≤m$；

对于另外 $15\%$ 的测试点，$k=2$；

对于另外 $15\%$ 的测试点， $m\le10$；

对于 $100\%$ 的测试点， $1≤n,m≤10^{18}$，$1≤t,k≤100$，且 $k$ 是一个质数。


---

---
title: "[BalticOI 2013] Palindrome-Free Numbers (Day1)"
layout: "post"
diff: 省选/NOI-
pid: P6754
tag: ['2013', '数位 DP', 'BalticOI（波罗的海）']
---
# [BalticOI 2013] Palindrome-Free Numbers (Day1)
## 题目描述

我们定义回文串为正着读反着读都一样的数字串，如果一个数字串的一个长度大于 $1$ 的子串也为回文串的话，那么我们也定义这个数字串为回文串。

顾名思义，不是回文串的数字串为非回文串。

给定 $a,b$，求区间 $[a,b]$ 中有多少个数字串为非回文串。
## 输入格式

一行两个整数 $a,b$ 代表这个区间。
## 输出格式

一行一个整数代表答案。
## 样例

### 样例输入 #1
```
123 321
```
### 样例输出 #1
```
153
```
### 样例输入 #2
```
123456789 987654321
```
### 样例输出 #2
```
167386971
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$0 \le a \le b \le 10^{18}$。    
对于其中的 $25\%$ 的数据，$b-a \le 10^5$。

#### 说明

翻译自 [BalticOI 2013 Day1 B Palindrome-Free Numbers](https://boi.cses.fi/files/boi2013_day1.pdf)。


---

---
title: "[CCO 2021] Weird Numeral System"
layout: "post"
diff: 省选/NOI-
pid: P7829
tag: ['2021', 'Special Judge', 'CCO（加拿大）', '记忆化搜索', '数位 DP', '进制']
---
# [CCO 2021] Weird Numeral System
## 题目描述

Alice 正在思考一个关于 $k$ 进制整数的问题。

普通的 $k$ 进制可以将整数 $n$ 表示为 $d_{m - 1} d_{m - 2} \cdots d_0$，且满足：

1. $0 \leq d_i < k$；
2. $n = \displaystyle\sum_{i = 0}^{m - 1} d_i k^i$。

然而，普通的 $k$ 进制整数对于 Alice 来说太简单了，Alice 更喜欢奇怪的 $k$ 进制整数。它与普通 $k$ 进制整数的差别仅仅在于将 $0 \leq d_i < k$ 换成了 $d_i \in a$，其中 $a$ 为一个长为 $D$ 的数列。

现在有一组固定的 $a_1, a_2, \cdots, a_D$，Alice 想要将 $q$ 个十进制整数 $n_1, n_2, \cdots, n_q$ 全部转化为奇怪的 $k$ 进制整数，这种问题显然更适合写程序来解决。
## 输入格式

第一行，四个整数 $k, q, D, M$；

第二行，$D$ 个整数 $a_1, a_2, \cdots, a_D$；

接下来 $q$ 行，每行一个整数 $n_i$。
## 输出格式

$q$ 行，第 $i$ 行表示 $n_i$ 转化后的结果，按幂次从高到低的顺序输出每一位，两个位之间用单个空格间隔。当 $a_i$ 中包含 $0$ 时，你转化的结果可以包含前导零，但最好不要太多；当 $n_i = 0$ 时，你转化的结果也不能为空。如果有多种方案可以随便输出一种，如果无法转化输出 `IMPOSSIBLE`。
## 样例

### 样例输入 #1
```
3 3 3 1
-1 0 1
15
8
-5
```
### 样例输出 #1
```
1 -1 -1 0
1 0 -1
-1 1 1
```
### 样例输入 #2
```
10 1 3 2
0 2 -2
17
```
### 样例输出 #2
```
IMPOSSIBLE
```
## 提示

**本题由 @[Leasier](https://www.luogu.com.cn/user/201007) 提供 SPJ。**
#### 数据范围
对于 $100\%$ 的数据，$2 \leq k \leq 10^6$，$1 \leq q \leq 5$，$1 \leq D \leq 801$，$1 \leq M \leq 400$，$-M \leq a_i \leq M$，$-10^{18} \leq n_i \leq 10^{18}$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T2


---

---
title: "[蓝桥杯 2019 省 A] 组合数问题"
layout: "post"
diff: 省选/NOI-
pid: P8688
tag: ['2019', '数位 DP', 'Lucas 定理', '蓝桥杯省赛']
---
# [蓝桥杯 2019 省 A] 组合数问题
## 题目描述

给 $n,m,k$，求有多少对 $(i,j)$ 满足 $1 \le i \le n,0 \le j \le \min(i,m)$ 且 ${i\choose j} \equiv 0\pmod{k}$，$k$ 是质数。其中 ${i\choose j}$ 是组合数，表示从 $i$ 个不同的数中选出 $j$ 个组成一个集合的方案数。
## 输入格式

第一行两个数 $t,k$，其中 $t$ 代表该测试点包含 $t$ 组询问，$k$ 的意思与上文中相同。

接下来 $t$ 行每行两个整数 $n,m$，表示一组询问。
## 输出格式

输出 $t$ 行，每行一个整数表示对应的答案。由于答案可能很大，请输出答案除以 $10^9+7$ 的余数。
## 样例

### 样例输入 #1
```
1 2
3 3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
2 5
4 5
6 7
```
### 样例输出 #2
```
0
7
```
### 样例输入 #3
```
3 23
23333333 23333333
233333333 233333333
2333333333 2333333333
```
### 样例输出 #3
```
851883128
959557926
680723120
```
## 提示

**【样例说明】**

在所有可能的情况中，只有 ${2 \choose 1}=2$ 是 $2$ 的倍数。

**【数据规模和约定】**

对于所有评测用例，$1 \le k \le 10^8,1 \le t \le 10^5,1 \le n,m \le 10^{18}$，且 $k$ 是质数。

评测时将使用 $10$ 个评测用例测试你的程序，每个评测用例的限制如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/jb7e32a0.png)

蓝桥杯 2019 年省赛 A 组 J 题。


---

---
title: "[PA 2020] Liczba Potyczkowa"
layout: "post"
diff: 省选/NOI-
pid: P9092
tag: ['2020', '数位 DP', 'PA（波兰）']
---
# [PA 2020] Liczba Potyczkowa
## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda próbna [Liczba Potyczkowa](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/lic/)。**

Bajtek 在数学史课上了到解了一位俄罗斯数学家弗拉基米尔·波季奇科夫（Vladimir Potyczkow）。这位科学家以对数字的研究而闻名，为了纪念他，今天我们将这些数称为 **Potyczkow 数**：是一个正整数，并且可以用其十进制表示中出现过的每个数字整除。特别地，这意味着十进制表示中不能有零。例如 $48$、$1$ 和 $112$ 是 Potyczkow 数，而 $23$、$10$ 和 $121$ 不是。Bajtek 想知道在 $[l, r]$ 范围内有多少这样的数，请帮助他数一数！
## 输入格式

一行输入两个正整数 $l,r$。

## 输出格式

输出一行一个整数，表示在 $[l, r]$ 范围内 Potyczkow 数的数量。
## 样例

### 样例输入 #1
```
1 100
```
### 样例输出 #1
```
23
```
## 提示

#### 样例 1 解释

不超过 $100$ 的 Potyczkow 数有 $1, 2, 3, 4, 5, 6, 7, 8, 9,11,12, 15, 22, 24, 33, 36, 44, 48, 55, 66, 77, 88$ 和 $99$。

------------

#### 数据范围

**本题采用捆绑测试**

对于部分子任务，满足 $r-l\le 10^6$。

对于 $100\%$ 的数据，保证 $1\le l\le r\le 10^{18}$。


---

---
title: "[USACO23FEB] Piling Papers G"
layout: "post"
diff: 省选/NOI-
pid: P9129
tag: ['USACO', '2023', '数位 DP', '区间 DP']
---
# [USACO23FEB] Piling Papers G
## 题目描述

Farmer John wrote down $N (1 \le N \le 300)$ digits on pieces of paper. For each $i \in [1,N]$, the ith piece of paper contains digit $a_i (1 \le a_i \le 9)$.

The cows have two favorite integers $A$ and $B(1 \le A \le B<10^{18})$, and would like you to answer $Q (1 \le Q \le 5⋅10^4)$ queries. For the $i$-th query, the cows will move left to right across papers $l_i \cdots r_i (1 \le l_i \le r_i \le N)$, maintaining an initially empty pile of papers. For each paper, they will either add it to the top of the pile, to the bottom of the pile, or neither. In the end, they will read the papers in the pile from top to bottom, forming an integer. Over all $3 ^ {r_i−l_i+1}$ ways for the cows to make choices during this process, count the number of ways that result in the cows reading an integer in $[A,B]$ inclusive, and output this number modulo $10^9+7$. 
## 输入格式

The first line contains three space-separated integers $N, A$, and $B$.

The second line contains $N$ space-separated digits $a_1,a_2, \cdots ,a_N$.

The third line contains an integer $Q$, the number of queries.

The next $Q$ lines each contain two space-separated integers $l_i$ and $r_i$. 
## 输出格式

For each query, a single line containing the answer. 
## 样例

### 样例输入 #1
```
5 13 327
1 2 3 4 5
3
1 2
1 3
2 5
```
### 样例输出 #1
```
2
18
34
```
## 提示

### Explanation for Sample 1

For the first query, there are nine ways Bessie can stack papers when reading the interval $[1,2]$:

 - Bessie can ignore $1$ then ignore $2$, getting $0$.
 - Bessie can ignore $1$ then add $2$ to the top of the stack, getting $2$.
 - Bessie can ignore $1$ then add $2$ to the bottom of the stack, getting $2$.
 - Bessie can add $1$ to the top of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the bottom of the stack, getting $12$.
 - Bessie can add $1$ to the bottom of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the bottom of the stack, getting $12$. 

Only the $2$ ways that give $21$ yield a number between $13$ and $327$, so the answer is $2$.

### SCORING

 - Inputs $2-3$: $B<100$
 - Inputs $4-5$: $A=B$
 - Inputs $6-13$: No additional constraints.
## 题目翻译

给定长度为 $n(1\leq n\leq 300)$ 的整数序列 $a(1\leq a_i\leq 9)$，和整数区间 $[A,B](1\leq A\leq B\leq 10^{18})$，有 $q$ 次询问，每次询问给出 $l,r$。每次询问开始，你有一个空串 $x$，你可以正序对 $a_{l\sim r}$ 进行操作，操作有三种：$x\rightarrow\overline{x+a_i}$，$x\rightarrow\overline{a_i+x}$，或者什么也不做，求 $\overline{x}$ 的取值在 $[A,B]$ 的不同的操作方案数，对 $10^9+7$ 取模。


---

