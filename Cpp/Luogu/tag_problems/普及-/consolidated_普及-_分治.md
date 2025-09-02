---
title: "[NOIP 1998 普及组] 幂次方"
layout: "post"
diff: 普及-
pid: P1010
tag: ['数学', '1998', 'NOIP 普及组', '分治']
---
# [NOIP 1998 普及组] 幂次方
## 题目描述

任何一个正整数都可以用 $2$ 的幂次方表示。例如 $137=2^7+2^3+2^0 $。

同时约定次方用括号来表示，即 $a^b$ 可表示为 $a(b)$。

由此可知，$137$ 可表示为 $2(7)+2(3)+2(0)$

进一步：

$7= 2^2+2+2^0$  ( $2^1$ 用 $2$ 表示)，并且 $3=2+2^0$。

所以最后 $137$ 可表示为 $2(2(2)+2+2(0))+2(2+2(0))+2(0)$。

又如 $1315=2^{10} +2^8 +2^5 +2+1$

所以 $1315$ 最后可表示为 $2(2(2+2(0))+2)+2(2(2+2(0)))+2(2(2)+2(0))+2+2(0)$。
## 输入格式

一行一个正整数 $n$。

## 输出格式

符合约定的 $n$ 的 $0, 2$ 表示（在表示中不能有空格）。
## 样例

### 样例输入 #1
```
1315
```
### 样例输出 #1
```
2(2(2+2(0))+2)+2(2(2+2(0)))+2(2(2)+2(0))+2+2(0)
```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le n \le 2 \times {10}^4$。

NOIP1998 普及组 第三题


---

---
title: "[NOIP 2001 提高组] 一元三次方程求解"
layout: "post"
diff: 普及-
pid: P1024
tag: ['数学', '2001', '二分', 'NOIP 提高组', '枚举', '分治']
---
# [NOIP 2001 提高组] 一元三次方程求解
## 题目描述

有形如：$a x^3 + b x^2 + c x + d = 0$  这样的一个一元三次方程。给出该方程中各项的系数（$a,b,c,d$ 均为实数），并约定该方程存在三个不同实根（根的范围在 $-100$ 至 $100$ 之间），且根与根之差的绝对值 $\ge 1$。要求由小到大依次在同一行输出这三个实根(根与根之间留有空格)，并精确到小数点后 $2$ 位。

提示：记方程 $f(x) = 0$，若存在 $2$ 个数 $x_1$ 和 $x_2$，且 $x_1 < x_2$，$f(x_1) \times f(x_2) < 0$，则在 $(x_1, x_2)$ 之间一定有一个根。
## 输入格式

一行，$4$ 个实数 $a, b, c, d$。
## 输出格式

一行，$3$ 个实根，从小到大输出，并精确到小数点后 $2$ 位。
## 样例

### 样例输入 #1
```
1 -5 -4 20

```
### 样例输出 #1
```
-2.00 2.00 5.00

```
## 提示

**【题目来源】**

NOIP 2001 提高组第一题


---

---
title: "最大子段和"
layout: "post"
diff: 普及-
pid: P1115
tag: ['动态规划 DP', '递推', '分治', '前缀和']
---
# 最大子段和
## 题目描述

给出一个长度为 $n$ 的序列 $a$，选出其中连续且非空的一段使得这段和最大。

## 输入格式

第一行是一个整数，表示序列的长度 $n$。

第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
7
2 -4 3 -1 2 -4 3

```
### 样例输出 #1
```
4
```
## 提示

#### 样例 1 解释

选取 $[3, 5]$ 子段 $\{3, -1, 2\}$，其和为 $4$。

#### 数据规模与约定

- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 2 \times 10^5$，$-10^4 \leq a_i \leq 10^4$。



---

---
title: "南蛮图腾"
layout: "post"
diff: 普及-
pid: P1498
tag: ['字符串', '递归', '湖南', '分治', '深度优先搜索 DFS']
---
# 南蛮图腾
## 题目背景

自从到了南蛮之地，孔明不仅把孟获收拾的服服帖帖，而且还发现了不少少数民族的智慧，他发现少数民族的图腾往往有着一种分形的效果，在得到了酋长的传授后，孔明掌握了不少绘图技术，但唯独不会画他们的图腾，于是他找上了你的爷爷的爷爷的爷爷的爷爷……帮忙，作为一个好孙子的孙子的孙子的孙子……你能做到吗？
## 题目描述

给定一个正整数 $n$，参考输出样例，输出图形。
## 输入格式

每个数据输入一个正整数 $n$，表示图腾的大小（此大小非彼大小）
## 输出格式

这个大小的图腾

## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
   /\
  /__\
 /\  /\
/__\/__\

```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
       /\
      /__\
     /\  /\
    /__\/__\
   /\      /\
  /__\    /__\
 /\  /\  /\  /\
/__\/__\/__\/__\
```
## 提示

数据保证，$1 \leq n \leq 10$。


---

---
title: "[USACO17JAN] Secret Cow Code S"
layout: "post"
diff: 普及-
pid: P3612
tag: ['字符串', '2017', 'USACO', '递归', '分治', '栈']
---
# [USACO17JAN] Secret Cow Code S
## 题目描述

The cows are experimenting with secret codes, and have devised a method for creating an infinite-length string to be used as part of one of their codes.

Given a string $s$, let $F(s)$ be $s$ followed by $s$ "rotated" one character to the right (in a right rotation, the last character of $s$ rotates around and becomes the new first character). Given an initial string $s$, the cows build their infinite-length code string by repeatedly applying $F$; each step therefore doubles the length of the current string.


Given the initial string and an index $N$, please help the cows compute the character at the $N$th position within the infinite code string.


## 输入格式

The input consists of a single line containing a string followed by $N$. The string consists of at most 30 uppercase characters, and $N \leq 10^{18}$.

Note that $N$ may be too large to fit into a standard 32-bit integer, so you may want to use a 64-bit integer type (e.g., a "long long" in C/C++).


## 输出格式

Please output the $N$th character of the infinite code built from the initial string. The first character is $N=1$.



## 样例

### 样例输入 #1
```
COW 8
```
### 样例输出 #1
```
C
```
## 提示

In this example, the initial string COW expands as follows:


COW -> COWWCO -> COWWCOOCOWWC

12345678



## 题目翻译

### 题目描述

奶牛们正在实验秘密代码，并设计了一种方法用于生成无限长度的字符串，作为他们代码的一部分。

给定一个字符串 $s$，令 $F(s)$ 为 $s$ 后接 $s$ 向右“旋转”一个字符的结果（在右旋转中，$s$ 的最后一个字符旋转并成为新的第一个字符）。给定初始字符串 $s$，奶牛们通过重复应用 $F$ 来构建他们的无限长度代码字符串；因此每一步都会使当前字符串的长度翻倍。

给定初始字符串和一个索引 $N$，请帮助奶牛计算无限代码字符串中第 $N$ 个位置的字符。

### 输入格式

输入由一行组成，包含一个字符串和 $N$。字符串最多由 30 个大写字母组成，且 $N \leq 10^{18}$。

请注意，$N$ 可能太大，无法放入标准的 32 位整数中，因此你可能需要使用 64 位整数类型（例如，C/C++ 中的 "long long"）。

### 输出格式

请输出从初始字符串构建的无限代码字符串的第 $N$ 个字符。第一个字符的位置为 $N=1$。

### 提示

在这个例子中，初始字符串 COW 按以下方式扩展：

COW -> COWWCO -> COWWCOOCOWWC


---

