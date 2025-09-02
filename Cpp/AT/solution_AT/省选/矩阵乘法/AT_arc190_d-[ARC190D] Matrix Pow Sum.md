# [ARC190D] Matrix Pow Sum

## 题目描述

给定素数 $p$ 和一个 $N \times N$ 的矩阵 $A = (A_{i,j})$（$1 \leq i,j \leq N$），其中每个元素 $A_{i,j}$ 是 $0$ 到 $p-1$ 之间的整数。  

定义矩阵 $B$ 为将 $A$ 中所有 $0$ 替换为 $1$ 到 $p-1$ 之间的整数后得到的矩阵。设 $A$ 中 $0$ 的个数为 $K$，则共有 $(p-1)^K$ 种可能的 $B$。  

要求计算所有可能的 $B$ 对应的 $B^p$（矩阵的 $p$ 次幂）之和，并将每个元素对 $p$ 取模后输出。  

## 说明/提示

### 约束条件  
- $1 \leq N \leq 100$  
- $p$ 是满足 $1 \leq p \leq 10^9$ 的素数  
- $0 \leq A_{i,j} \leq p-1$  
- 输入均为整数  

### 样例解释 1  
所有可能的 $B$ 对应的 $B^3$ 如下：  
- $\begin{pmatrix}1 & 1 \\ 1 & 2\end{pmatrix}^3 = \begin{pmatrix}5 & 8 \\ 8 & 13\end{pmatrix}$  
- $\begin{pmatrix}1 & 1 \\ 2 & 2\end{pmatrix}^3 = \begin{pmatrix}9 & 9 \\ 18 & 18\end{pmatrix}$  
- $\begin{pmatrix}2 & 1 \\ 1 & 2\end{pmatrix}^3 = \begin{pmatrix}14 & 13 \\ 13 & 14\end{pmatrix}$  
- $\begin{pmatrix}2 & 1 \\ 2 & 2\end{pmatrix}^3 = \begin{pmatrix}20 & 14 \\ 28 & 20\end{pmatrix}$  
总和为 $\begin{pmatrix}48 & 44 \\ 67 & 65\end{pmatrix}$，各元素对 $p=3$ 取模后输出。  

### 样例解释 2  
所有可能的 $B$ 对应的 $B^2$ 为：  
- $\begin{pmatrix}1 & 1 & 1 \\ 1 & 1 & 1 \\ 1 & 1 & 1\end{pmatrix}^2 = \begin{pmatrix}3 & 3 & 3 \\ 3 & 3 & 3 \\ 3 & 3 & 3\end{pmatrix}$  
总和对 $p=2$ 取模后输出。  

翻译由 DeepSeek R1 完成  

## 样例 #1

### 输入

```
2 3
0 1
0 2```

### 输出

```
0 2
1 2```

## 样例 #2

### 输入

```
3 2
1 0 0
0 1 0
0 0 1```

### 输出

```
1 1 1
1 1 1
1 1 1```

## 样例 #3

### 输入

```
4 13
0 1 2 0
3 4 0 5
0 6 0 7
8 9 0 0```

### 输出

```
8 0 6 5
11 1 8 5
8 0 4 12
8 0 1 9```

# 题解

## 作者：fydj (赞：13)

考虑把未知的位置替换成变量，如样例一的 $\begin{bmatrix}0&1\\0&2\end{bmatrix}$ 就可以变成 $\begin{bmatrix}x&1\\y&2\end{bmatrix}$，而它的三次方就是 $\begin{bmatrix}x^3+2xy+2y&x^2+2x+y+4\\x^2y+y^2+2xy+4y&xy+4y+8\end{bmatrix}$。关于矩阵 $p$ 次幂的计算，可以由 $A^2_{i,j}=\sum _{k}A_{i,k}\times A_{k,j}$ 类比出 $A^{p}_{i,j}=\prod _{k_{1,2,\dots,p-1}} A_{i,k_1}\times A_{k_1,k_2}\times\dots\times A_{k_{p-1},j}$。

注意到，$\sum_{i=1}^{p-1}i^{k}\bmod p$ 只有当 $k=p-1$ 时才不为零（并且刚好是 $p-1$）。

考虑证明。找到 $p$ 的原根 $r$，则原式等价于 $\sum_{i=0}^{p-2}r^{ik}=\sum_{i=0}^{p-2}(r^k)^i$。当 $k=p-1$ 时 $r^k\equiv 1$，则原式 $\equiv p-1$。反之，可以运用等比数列求和公式得出原式 $\equiv \frac{r^{k(p-1)}-1}{r^k-1}$，根据费马小定理，$r^{k(p-1)}\equiv 1\pmod p$，则分子是 $0$，整个分数就是 $0$，得证。

有了这个强有力的结论，正解就呼之欲出了。

先把没有未知数的贡献用矩阵快速幂算出来。可以发现矩阵的某个位置的某一项中所有未知数的指数都是 $p-1$ 时这一项的贡献才不为零。$p=2$ 的情况当作 corner case，很好处理。其余情况只有当 $k_{1,2,\dots,p-1}=i$ 或者 $k_{1,2,\dots,p-1}=j$ 时才可能会出现未知数的指数是 $p-1$ 的情况，只有两种情况有贡献，这部分很好做。当 $p=3$ 时，$k_1=j,k_2=i$，$A_{i,j}$ 的指数是 $2$，也符合条件，要把它看成一个 corner case。贡献记得乘上选其它未知数的方案数。

时间复杂度是 $O(n^3\log p)$，瓶颈在于矩阵快速幂。

[代码](https://atcoder.jp/contests/arc190/submissions/61648920)。

---

## 作者：xiezheyuan (赞：2)

## 简要题意

给定一个 $n\times n$ 的方阵 $A$，若 $A_{ij}=0$，表示 $A_{ij}$ 不确定。

给出整数 $p$，你需要将每个不确定的位置填上一个 $[1,p)$ 的整数得到矩阵 $B$。求全体 $B^p$ 的和。答案对 $p$ 取模。

$1\leq n\leq 100,p\in\mathbb{P},p\leq 10^9$。

## 思路

对于 $p=2$，求解是平凡的，这里只考虑 $p>2$ 的情况。

不妨将每个不确定的位置 $A_{ij}$ 看成一个自由元 $x_{ij}$。先考察 $A_{ij}^k$，则每个位置都是一个多元至多 $p$ 次的多项式。

考虑每一个单元格的多项式的每一项，应当形如 $C x_1^{k_1} x_2^{k_2} \cdots$，则这一项产生的贡献也应当形如 $C\left(\sum_{i=1}^{p-1} i^{k_1}\right)\left(\sum_{i=1}^{p-1} i^{k_2}\right)\cdots$。这启发我们往 $F_p(k)=\left(\sum_{i=1}^{p-1} i^k\right)\bmod p$ 去思考。

直觉告诉你这个 $F_p(k)$ 一定是好求的，考虑打表：

```mathematica
F[p_] := Table[Mod[Sum[i ^ k, {i, 1, p - 1}], p], {k, 0, p - 1}]
F[17]
```

得到 `{16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16}`，于是做出猜想：
$$
F_p(k) = \begin{cases}
p - 1& p - 1\mid k\\
0& \mathrm{otherwise}
\end{cases}
$$
尝试证明这个结论。取模 $p$ 意义下的某一个原根 $g$，若 $p-1\nmid k$ 则得到：
$$
F_p(k)=\sum_{i=1}^{p-1}i^k\bmod p=\sum_{i=0}^{p-2} g^{ik} \bmod p=\frac{g^{k(p-1)}-1}{g^k-1} \bmod p=\frac{1-1}{g^k-1}=0
$$
否则，$i^k\equiv 1\pmod{p}$，所以 $F_p(k)=p-1$，证毕。

所以只有形如 $Cx_1^{p-1}$ 的项或常数项才会对答案产生贡献。

先来考虑常数项，这是容易的，$A^p$ 就是答案，然后尝试求出形如 $x_1^{p-1}$ 的系数之和。

看起来十分困难，不妨模拟矩阵乘法的过程，分析每一项是如何得到的。

对于 $p>3$，我们只有下面的两种方法：

- $x_{ii}\cdot \cdots\cdot x_{ii}\cdot A_{ij}$。
- $A_{ji}\cdot x_{ii}\cdot\cdots\cdot x_{ii}$。

对于 $p=3$，还有一种方法 $x_{ij}\cdot A_{ji}\cdot x_{ij}$。依照这种方法统计系数即可。

时间复杂度 $O(\mathrm{MatrixMul}(n)\log p)$。

[Submission](https://atcoder.jp/contests/arc190/submissions/64223293)。

---

