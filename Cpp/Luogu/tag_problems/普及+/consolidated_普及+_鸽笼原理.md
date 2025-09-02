---
title: "[USACO24JAN] Cowlendar S"
layout: "post"
diff: 普及+/提高
pid: P10136
tag: ['USACO', '2024', '数论', '鸽笼原理']
---
# [USACO24JAN] Cowlendar S
## 题目描述

Bessie 在一个陌生的星球上醒来。这个星球上有 $N$（$1\le N\le 10^4$）个月，分别有 $a_1,\ldots,a_N$ 天（$1\le a_i\le 4\cdot 10^9$，所有 $a_i$ 均为整数）。此外，这个星球上还存在周，一周为 $L$ 天，其中 $L$ 是一个正整数。有趣的是，Bessie 知道以下事情：

- 对于正确的 $L$，每个月至少有 $4$ 周。
- 对于正确的 $L$，$a_i\bmod L$ 至多有 $3$ 个不同值。

不幸的是，Bessie 忘记了 $L$ 是多少！请通过输出 $L$ 的所有可能值之和来帮助她。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**
## 输入格式

输入的第一行包含一个整数 $N$。第二行包含 $N$ 个空格分隔的整数 $a_1,\ldots,a_N$。
## 输出格式

输出一个整数，为 $L$ 的所有可能值之和。
## 样例

### 样例输入 #1
```
12
31 28 31 30 31 30 31 31 30 31 30 31
```
### 样例输出 #1
```
28
```
### 样例输入 #2
```
4
31 35 28 29
```
### 样例输出 #2
```
23
```
## 提示

### 样例解释 1

$L$ 的可能值为 $1$，$2$，$3$，$4$，$5$，$6$ 和 $7$。例如，$L=7$ 是合法的，因为每个月的至少有 $4\cdot 7=28$ 天，且每个月的天数模 $7$ 的余数均为 $0$，$2$ 或 $3$。

### 样例解释 2

$L$ 的可能值为 $1$，$2$，$3$，$4$，$6$ 和 $7$。例如，$L=6$ 是合法的，因为每个月的至少有 $4\cdot 6=24$ 天，且每个月的天数模 $6$ 的余数均为 $1$，$4$ 或 $5$。

### 测试点性质

- 测试点 $3-4$：$1\le a_i\le 10^6$。
- 测试点 $5-14$：没有额外限制。


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

