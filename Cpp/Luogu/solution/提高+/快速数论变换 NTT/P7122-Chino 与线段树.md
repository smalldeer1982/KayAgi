# Chino 与线段树

## 题目描述

Chino 刚学习了一种叫做线段树的数据结构。可是她在写线段树时遇到了一个问题：她不知道该使用多大的空间，只知道线段树的叶子结点个数 $n$ 为一个在范围 $[a,b]$ 之内的正整数。

Chino 设 $f(n)$ 表示一棵 $n$ 个叶子结点的线段树所占的最大数组下标。她觉得如果她知道了

$$\sum_{n=a}^{b}f(n)$$

那么她就能够算出她需要多少使用多大的空间。所以她来请教聪明的你来帮帮她。

具体地，Chino 构建线段树的伪代码如下：

$\begin{aligned}
&\underline{\kern{300pt}}\\
&\mathbf{Function:}\ \text{Build a Segment Tree.}\\[-10pt]
&\underline{\kern{300pt}}\\[-5pt]
&\begin{array}{r|l}
1&\ \mathbf{function}\ \text{BuildSegmentTree}(x,l,r):\\
2&\qquad \mathbf{if}\ (l \ne r)\ \mathbf{then}:\\
3&\qquad\qquad m \gets \left\lfloor (l+r)/2 \right\rfloor\\
4&\qquad\qquad \text{BuildSegmentTree}(2x,l,m)\\
5&\qquad\qquad \text{BuildSegmentTree}(2x+1,m+1,r)\\
6&\qquad \mathbf{end\ if}\\
7&\ \mathbf{end\ function}\\
\end{array}\\[-13pt]
&\underline{\kern{300pt}}
\end{aligned}$

线段树所占的最大数组下标即为在 $\def\t#1{\text{#1}}\t{BuildSegmentTree}\left(1,1,n\right)$ 后所有调用的 $\def\t#1{\text{#1}}\t{BuildSegmentTree}$ 中参数 $x$ 的最大值。

## 说明/提示

### 样例解释 #1
$1\sim 10$ 个叶子结点的线段树的最大下标分别为 $1,3,5,7,9,13,13,15,17,25$，求和得到 $108$。

### 测试点约束
**本题采用捆绑测试。**

对于全部数据，有 $1\le a\le b\le10^{10^6}$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | $b\le$ | $a=b$ |
|:-:|:-:|:-:|:-:|
| 1 | 10 | $10^{10^0}$ | $\times$ |
| 2 | 10 | $10^{10^1}$ | $\times$ |
| 3 | 10 | $10^{10^2}$ | $\times$ |
| 4 | 10 | $10^{10^3}$ | $\surd$ |
| 5 | 10 | $10^{10^3}$ | $\times$ |
| 6 | 10 | $10^{10^4}$ | $\surd$ |
| 7 | 10 | $10^{10^4}$ | $\times$ |
| 8 | 10 | $10^{10^5}$ | $\surd$ |
| 9 | 10 | $10^{10^5}$ | $\times$ |
| 10 | 10 | $10^{10^6}$ | $\times$ |

## 样例 #1

### 输入

```
1
10
```

### 输出

```
108
```

## 样例 #2

### 输入

```
233333
666666
```

### 输出

```
588544964910
```

## 样例 #3

### 输入

```
1
1000000000000000000
```

### 输出

```
1419691012023749904603586777179575510
```

# 题解

## 作者：Daniel13265 (赞：12)

设 $d\left(n\right)$ 表示一棵 $n$ 个叶子结点的线段树的深度，那么有 $d\left(1\right)=1$ 与
$$
\begin{aligned}
d\left(2n\right)&=d\left(n\right)+1,\\
d\left(2n+1\right)&=\max\left\{d\left(n+1\right),d\left(n\right)\right\}+1.
\end{aligned}
$$
所以
$$
d\left(n\right)=\left\lceil\log n\right\rceil+1.
$$
我们又有
$$
\begin{aligned}
f\left(2n\right)&=2^{d\left(n\right)+1}+f\left(n\right),\\
f\left(2n+1\right)&=\begin{cases}
2^{d\left(n\right)}+f\left(n+1\right), &d\left(n+1\right)>d\left(n\right),\\
2^{d\left(n\right)+1}+f\left(n\right), &d\left(n+1\right)\le d\left(n\right).
\end{cases}
\end{aligned}
$$
按 $n$ 的二进制位从高位向低位递推。发现 $d\left(n+1\right)>d\left(n\right)$ 当且仅当 $n=2^k\left(k\in\N\right)$，因此 $n$ 最高 $\texttt1$ 位后的全 $\texttt0$ 段这一部分的答案可以直接计算，之后的 $\texttt1$ 位就一定是第二种情况，于是第一段全 $\texttt0$ 位后的 $\texttt0$ 位就与 $\texttt1$ 位一样了。

有了这点，我们就容易发现
$$
f\left(n\right)=\begin{cases}
2^{x+1}-1, &n=2^x\left(x\in\N\right),\\
2^{x+2}-2^{x-y+1}+1, &n=2^x+2^y+t\left(x,y\in\N,0\le t<2^y<2^x\right).
\end{cases}
$$
现在我们要对 $f$ 求和。我们可以分别求出 $n=1,2,3,\dots,b$ 时的和与 $n=1,2,3,\dots,a-1$ 时的和，然后作差得出答案，所以我们现在要对于 $N=a-1$ 和 $N=b$ 求
$$
\sum_{n=1}^Nf\left(n\right).
$$
若 $N=2^X\left(X\in\N\right)$，那么我们单独计算 $f\left(N\right)$ 然后并计算 $N$ 减去一后的答案，求和就可以得到答案。所以我们假设 $N=2^X+2^Y+T\left(X,Y\in\N,0\le T<2^Y<2^X\right)$，那么
$$
\begin{aligned}
\sum_{n=1}^Nf\left(n\right)=&\sum_{x=0}^{X-1}\left(2^{x+1}-1+\sum_{y=0}^{x-1}2^y\left(2^{x+2}-2^{x-y+1}+1\right)\right)+2^{X+1}-1\\
&\qquad+\sum_{y=0}^{Y-1}2^y\left(2^{X+2}-2^{X-y+1}+1\right)+\left(T+1\right)\left(2^{X+2}-2^{X-Y+1}+1\right)\\
=&3\times2^X-2^{X+1}X-2X+\frac{2^{2X+2}-13}3+2^{X+1}-1\\
&\qquad+\left(2^{X+2}+1\right)\left(2^Y-1\right)-Y\times2^{X+1}+\left(T+1\right)\left(2^{X+2}-2^{X-Y+1}+1\right).
\end{aligned}
$$
于是就可以计算了。~~你可能需要一个高精度板子。时间复杂度 $\sout{O\left(\log b\log\log b\right)}$，空间复杂度 $\sout{O\left(\log b\right)}$。~~**人生苦短，我用 Ruby。**

---

