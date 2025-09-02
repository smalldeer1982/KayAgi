---
title: "[GCJ 2012 #2] Aerobics"
layout: "post"
diff: 普及+/提高
pid: P13325
tag: ['贪心', '2012', 'Special Judge', '随机化', 'Google Code Jam']
---
# [GCJ 2012 #2] Aerobics
## 题目描述

The aerobics class begins. The trainer says, "Please position yourselves on the training mat so that each one of you has enough space to move your arms around freely, and not hit anybody else." People start milling around on the mat, trying to position themselves properly. Minutes pass, and finally the trainer is so annoyed that he asks you to write a program that will position all the people correctly, hoping it will be quicker than letting them figure it out for themselves!

You are given the dimensions (width and length) of the mat on which the class takes place. For every student, there is a circular area she has to have for herself, with radius equal to the reach of her arms. These circles can not intersect, though they can touch; and the center of each circle (where the student stands) has to be on the mat. Note that the arms **can** reach outside the mat. You know that there's plenty of space on the mat — the area of the mat is at least five times larger than the total area of the circles required by all the people in the class. It will always be possible for all the people to position themselves as required.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of two lines. The first line contains three integers: $\mathbf{N}$, $\mathbf{W}$ and $\mathbf{L}$, denoting the number of students, the width of the mat, and the length of the mat, respectively. The second line contains $\mathbf{N}$ integers $\mathbf{r}_i$, denoting the reach of the arms of the $i^{th}$ student.

## 输出格式

For each test case, output one line containing "Case #$n$: $y$", where $n$ is the case number (starting from 1) and $y$ is a string containing $2\mathbf{N}$ numbers, each of which can be an integer or a real number: $\mathbf{x}_1$, $\mathbf{y}_1$, $\mathbf{x}_2$, $\mathbf{y}_2$, etc., where the pair $(\mathbf{x}_i, \mathbf{y}_i)$ is the position where the $i^{th}$ student should stand (with $0 \leq \mathbf{x}_i \leq \mathbf{W}$ and $0 \leq \mathbf{y}_i \leq \mathbf{L}$).

As there will likely be multiple ways to position the students on the mat, you may output any correct positioning; but remember that you may not submit an output file more than 200kB in size.
## 样例

### 样例输入 #1
```
2
2 6 6
1 1
3 320 2
4 3 2
```
### 样例输出 #1
```
Case #1: 0.0 0.0 6.0 6.0
Case #2: 0.0 0.0 7.0 0.0 12.0 0.0
```
## 提示

**Limits**

- $1 \leq \mathbf{T} \leq 50$.
- $1 \leq \mathbf{W}, \mathbf{L} \leq 10^9$.
- $1 \leq \mathbf{r}_i \leq 10^5$.
- The area of the mat is at least 5 times larger than the total area of the circles:
- $5 \times \pi \times (\mathbf{r}_1^2 + \ldots + \mathbf{r}_\mathbf{N}^2) \leq \mathbf{W} \times \mathbf{L}$.

**Test set 1 (6 Pts, Visible Verdict)**

- $1 \leq \mathbf{N} \leq 10$.

**Test set 2 (15 Pts, Hidden Verdict)**

- $1 \leq \mathbf{N} \leq 10^3$.
- The total number of circles in all test cases will be $\leq 6000$.


---

---
title: "[GCPC 2023] Balloon Darts"
layout: "post"
diff: 普及+/提高
pid: P13667
tag: ['2023', '鸽笼原理', '随机化', '构造', 'ICPC']
---
# [GCPC 2023] Balloon Darts
## 题目描述

As you may know, you get a colourful balloon for each problem you solve in an ICPC contest.
You were quite successful in your last contest
and now you own a remarkable collection of $n$ balloons.
The obvious thing to do with these balloons is to pop them all using darts.
However, you only have three darts.

![](https://cdn.luogu.com.cn/upload/image_hosting/3lkiybcb.png)

:::align{center}
Popping balloons as an amusement park attraction. Photo by blende12, [Pixabay](https://pixabay.com/photos/balloon-leisure-time-4525887/)
:::

The balloons are modelled as points in the plane with fixed locations.
For each dart you choose from where and in which direction to throw it.
The dart travels in a straight line, popping all balloons in its way.

As you practised a lot during the last years,
you can throw a dart precisely in any direction and it will fly infinitely far.
Thus, if anyone can pop all the balloons, it is you. 
However, before the fun begins, you first need to determine
if you can pop all balloons using at most three darts.
## 输入格式

The input consists of:
- One line containing an integer $n$ ($1 \leq n \leq 10^4$), the number of balloons.
- $n$ lines, each containing two integers $x$ and $y$ ($|x|, |y| \leq 10^9$), the coordinates of a balloon.

It is guaranteed that no two balloons are at the same location.
## 输出格式

Output "$\texttt{possible}$" if three darts are sufficient to pop all balloons and "$\texttt{impossible}$" otherwise.
## 样例

### 样例输入 #1
```
6
0 0
1 1
2 4
3 9
4 16
5 25
```
### 样例输出 #1
```
possible
```
### 样例输入 #2
```
7
0 0
1 1
2 4
3 9
4 16
5 25
6 36
```
### 样例输出 #2
```
impossible
```
### 样例输入 #3
```
7
-1 -1
0 0
1 1
2 4
3 9
4 16
5 25
```
### 样例输出 #3
```
possible
```


---

---
title: "[CERC 2022] Differences"
layout: "post"
diff: 普及+/提高
pid: P13810
tag: ['2022', '随机化', 'ICPC', 'CERC']
---
# [CERC 2022] Differences
## 题目描述

We have a list of $N$ strings $S_i$. All strings have length $M$ and consist only of characters A, B, C and D. Let us define the distance between two strings $X$ and $Y$ as the number of indices $j$, where the strings have different characters ($X_j \neq Y_j$). We know that the list of strings $S_i$ contains precisely one special string that has distance $K$ to all other strings. Note that there might be other pairs of strings with a distance of $K$. We are experiencing problems finding this special string, so please write a program to help us out.
## 输入格式

The first line contains space-separated integers $N$, $M$ and $K$. Strings $S_i$ are given in the following $N$ lines.

## 输出格式

Output the index $i$ of the special string. Strings are numbered from 1 to $N$ as given in the input.
## 样例

### 样例输入 #1
```
5 10 2
DCDDDCCADA
ACADDCCADA
DBADDCCBDC
DBADDCCADA
ABADDCCADC
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4 6 5
AABAAA
BAABBB
ABAAAA
ABBAAB
```
### 样例输出 #2
```
2
```
## 提示

### Input limits

* $2 \leq N, M \leq 10^5$
* $1 \leq K \leq M$
* $NM \leq 2 \cdot 10^7$


---

---
title: "『STA - R3』Aulvwc"
layout: "post"
diff: 普及+/提高
pid: P9509
tag: ['动态规划 DP', 'O2优化', '背包 DP', '随机化']
---
# 『STA - R3』Aulvwc
## 题目背景

统计学是一门古老而迷人的学科。

传说早在若干年前，一位名为惠普的神灵来到地球，发现了人类——另一种有智慧的物种……

**已加入 Hack 数据，位于 Subtask 5，不计分。**
## 题目描述

定义一个序列 $\{a_n\}$ 是分部平均的，当且仅当存在一个 $\{1,2,\cdots,n\}$ 的划分 $S_1,S_2,\cdots,S_k$（其中 $k>1$），满足对于每个整数 $1\le i\le k$，序列 $\{a\}$ 中以 $S_i$ 为下标的元素之平均数都是相等的**整数**。

现在，给定序列 $\{a_n\}$，问它是否是分部平均的。

如果你对于一些定义不很清楚，可以查阅最后的「提示」部分。


## 输入格式

第一行，一个正整数 $q$，表示询问组数。

对于每组询问，第一行一个正整数 $n$，描述序列长度。第二行 $n$ 个整数，表示序列 $\{a_n\}$。
## 输出格式

$q$ 行，对于每组询问，如果序列是分部平均的，则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
4
5
1 1 1 1 1
5
1 2 3 4 5
5
1 1 1 1 6
5
-1 0 1 0 1
```
### 样例输出 #1
```
Yes
Yes
No
No
```
## 提示

### 提示
一个集合 $S$ 的划分定义为一组集合 $U_1,U_2,\cdots,U_k$，满足：
- 对于所有 $i\neq j$，有 $U_i\cap U_j=\varnothing$。
- $U_1\cup U_2\cup\cdots\cup U_k=S$。

一个序列 $\{x_n\}$ 的平均数定义为：
$$\bar x=\dfrac{x_1+x_2+\cdots+x_n}{n}=\dfrac 1n\sum_{i=1}^nx_i$$
### 样例解释
第一组数据的一种划分方案：$\{1\},\{2\},\{3\},\{4\},\{5\}$。

第二组数据的一种划分方案：$\{1,5\},\{2,4\},\{3\}$。

注意：划分方案所提供的集合是下标集合。

### 数据范围

**本题采用捆绑测试及子任务依赖。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}&\textbf{依赖子任务}\\\hline
\textsf{1} & 10 & 5 & \\\hline
\textsf{2} & 10^3 & 20 & \sum a_i=0 \\\hline
\textsf{3} & 100 & 25 & & \sf1\\\hline
\textsf{4} & 10^3 & 50 & & \sf1\texttt{,}\ 3\\\hline
\end{array}
$$

对于全部数据，$1\le q\le 10$，$2\le n\le 10^3$，$|a_i|\le 5\times10^3$。


---

