# Banned X

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_f

$ 0,1,2 $ のみからなる長さ $ N $ の数列であって、 どの連続する部分列に対してもそれに含まれる数の総和がちょうど $ X $ にはならないようなものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ X\ \leq\ 2N $
- $ N,X $ は整数である

### Sample Explanation 1

$ (0,0,0),(0,0,1),(0,0,2),(0,1,0),(0,1,1),(0,2,0),(0,2,2),(1,0,0),(1,0,1),(1,1,0),(2,0,0),(2,0,2),(2,2,0),(2,2,2) $ の $ 14 $ 個の数列が条件を満たします。

## 样例 #1

### 输入

```
3 3```

### 输出

```
14```

## 样例 #2

### 输入

```
8 6```

### 输出

```
1179```

## 样例 #3

### 输入

```
10 1```

### 输出

```
1024```

## 样例 #4

### 输入

```
9 13```

### 输出

```
18402```

## 样例 #5

### 输入

```
314 159```

### 输出

```
459765451```

# 题解

## 作者：masterhuang (赞：1)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $13$ 篇。

第一个线性做法题解。下文规定若 $m<0$ 或 $n<m$，则 $\dbinom{n}{m}=0$。

先不考虑 $0$，设长度为 $m$ 的 $1,2$ 序列满足条件的方案数为 $f_m$，则答案为 $\sum\limits_{i=0}^n\dbinom{n}{i}f_m$。考虑线性求 $f_m$。

设总和为 $s$，分讨：

若 $s<X-1$，则数量为 $\sum\limits_{s=m}^{X-2} \dbinom{m}{s-m}$。

否则，若序列合法一定存在前缀和为 $X-1$。

首先总和要 $\ge X-1$，而又不存在为 $X$ 的前缀和，且序列中元素在 $\{1,2\}$ 中，于是存在。

特判 $m=0$，此时考虑 $0\le k\le m$ 位置的前缀和为 $X-1$，发现 $a_{k+1}=2$，又发现 $a_1=1$ 不满足条件，于是 $a_1=2$。
               
递推下去，于是 $a_{1,2,\cdots,m-k},a_{k+1,k+2,\cdots ,m}$ 均为 $2$，其他位置任意。

再分讨，若 $m-k\le k$，则对 $(m-k,k]$ 中填数方案计数，否则判断全填 $2$ 可不可行即可。

后者是容易的，前者是要 $2k-m$ 个数，和为 $x-1-2(m-k)$，简单计算后发现为 $\dbinom{2k-m}{X-1-m}$。

于是这时方案数为 $\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}+[2\nmid X]\times [(m-1)/2\ge (X-1)/2]$。

设 $n,X$ 同阶，复杂度 $O(n^2)$。[代码](https://atcoder.jp/contests/tenka1-2019/submissions/50954269)。

---

接下来考虑线性求 $\sum\limits_{s=m}^{X-2} \dbinom{m}{s-m}=\sum\limits_{i=0}^{X-2-m} \dbinom{m}{i}$，这是容易的。先预处理阶乘逆元。

$\sum\limits_{i=0}^{X-2-m} \dbinom{m}{i}=\sum\limits_{i=0}^{X-2-(m-1)} \left(\dbinom{m-1}{i}+\dbinom{m-1}{i-1}\right)-\dbinom{m}{X-m+1}=2\sum\limits_{i=0}^{X-2-(m-1)} \dbinom{m-1}{i}-\dbinom{m-1}{X-m+1}-\dbinom{m}{X-m+1}$。就能每次 $O(1)$ 递推啦。

---

最后线性求 $\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}$。第一步思路来源于官方题解，但最后式子比官方题解简单。

$\begin{aligned}
\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}&=\dfrac{1}{2}\left(\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}+\dbinom{2k-m}{X-1-m}\right)\\
&=\dfrac{1}{2}\left(\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}+\dbinom{2k-(m+1)}{X-1-m}+\dbinom{2k-(m+1)}{X-1-(m+1)}\right)\\
&=\dfrac{1}{2}\left(\sum\limits_{k=0}^{2m} \dbinom{k-m}{X-1-m}+\sum\limits_{k=0}^m\dbinom{2k-(m+1)}{X-1-(m+1)}\right)\\
&=\dfrac{1}{2}\left(\dbinom{m+1}{X-m}+\sum\limits_{k=0}^{m+1}\dbinom{2k-(m+1)}{X-1-(m+1)}-\dbinom{m+1}{X-1-(m+1)}\right)
\end{aligned}$

于是 $2\sum\limits_{k=0}^m \dbinom{2k-m}{X-1-m}+\dbinom{m+1}{X-1-(m+1)}-\dbinom{m+1}{X-m}=\sum\limits_{k=0}^{m+1}\dbinom{2k-(m+1)}{X-1-(m+1)}$。一样预处理阶乘线性递推即可。

最终复杂度 $O(n)$。[代码](https://atcoder.jp/contests/tenka1-2019/submissions/50976393)。

---

## 作者：canadian_people (赞：1)

#### [原题传送门](https://www.luogu.com.cn/problem/AT_tenka1_2019_f)

题目大致题意：

给定一个数字 $n$, 求有多少个由数字 $0$, $1$, $2$ 组成的序列满足它任意的子序列都不等于 $x$，请注意结果要对 $998244353$ 取模。

思路：

- 首先可以枚举 $0$ 的个数 $i$，计算 $f(n-i,x)$ 表示由 $n-i$ 个 $1$,$2$ 构成的，且不存在和为 $x$ 的子序列个数，然后将已经处理过的数组 $ dp(n,i) \times f(n-i,x) $ 计入答案，答案需对 $998244353$ 取模。

- 对于 $1$,$2$ 序列的合法方案，其实只有三种情况：

  1. 序列和 $S<x-1$。
  
  2.  $S-x$ 为奇数,且此序列仅由 $2$ 构成。
 
  3.  $S-x$ 为奇数，且任何一个 $1$ 左侧和右侧的所有数之和 $<x$。
  
- 枚举序列和 $S$，对于条件 $1$ 和 $2$，可以由组合数简单计算。

- 对于条件 $3$，首先 $S-x$ 要为奇数，其次序列的左侧和右侧都应该有至少  $\frac{S-x+1}{2}$ 个 $2$，中间可以任意摆放，由组合数简单计算即可。

- 由此可以计算出时间复杂度为 $O(n^2)$，最多 $3000 \times 3000=9000000$，不会超时。



[AC代码](https://www.luogu.com.cn/paste/9px4j2u6)

[AC记录](https://www.luogu.com.cn/record/118591106)

  
  



---

