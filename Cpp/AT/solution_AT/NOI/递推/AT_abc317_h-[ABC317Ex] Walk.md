# [ABC317Ex] Walk

## 题目描述

有一个有 $N$ 个顶点的有向图，顶点编号为 $1$ 到 $N$。图中不存在重边，但可能存在自环。此外，图中所有的边都满足以下条件：

- 假设有一条从顶点 $s$ 指向顶点 $t$ 的边，则 $s,\ t$ 至少满足 $0 \leq t - s \leq 2$ 或 $t = 1$ 之一。

图中边的存在情况由长度为 $N$ 的数列 $A,B,C,D$ 给出。$A,\ B,\ C,\ D$ 的每个元素含义如下（以下 $A$ 的第 $n$ 个元素记为 $A_n$，$B_n,\ C_n,\ D_n$ 同理）：

- $A_n$：如果存在从顶点 $n$ 到顶点 $n$ 的边，则 $A_n = 1$，否则 $A_n = 0$。
- $B_n$：如果存在从顶点 $n$ 到顶点 $n+1$ 的边，则 $B_n = 1$，否则 $B_n = 0$（其中 $B_N = 0$）。
- $C_n$：如果存在从顶点 $n$ 到顶点 $n+2$ 的边，则 $C_n = 1$，否则 $C_n = 0$（其中 $C_{N-1} = C_N = 0$）。
- $D_n$：如果存在从顶点 $n$ 到顶点 $1$ 的边，则 $D_n = 1$，否则 $D_n = 0$（其中 $D_1 = A_1$）。

请你求出，在给定的图中，从顶点 $1$ 出发，以顶点 $N$ 结束，且恰好经过 $K$ 条边的 walk 的数量，并对 $998244353$ 取模。

这里，“从顶点 $1$ 出发，以顶点 $N$ 结束，且恰好经过 $K$ 条边的 walk”指的是一个顶点序列 $v_0 = 1, v_1, \dots, v_K = N$，对于每个 $i$（$0 \leq i < K$），存在从 $v_i$ 到 $v_{i+1}$ 的有向边。两个 walk 只要顶点序列不同就视为不同。

## 说明/提示

## 约束条件

- $2 \leq N \leq 5 \times 10^4$
- $1 \leq K \leq 5 \times 10^5$
- $A_i, B_i, C_i, D_i \in \lbrace 0, 1 \rbrace$
- $A_1 = D_1$
- $B_N = C_{N-1} = C_N = 0$

## 样例解释 1

将给定的图画出来如下所示。  
![](https://img.atcoder.jp/abc317/2106e1b4faaa87d208ed3e3a275cda1b.jpg)  
满足条件的 walk 有如下 $6$ 个：

- $1, 1, 1, 3$
- $1, 1, 2, 3$
- $1, 1, 3, 3$
- $1, 2, 3, 3$
- $1, 3, 1, 3$
- $1, 3, 3, 3$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 0 1
1 1 0
1 0 0
1 0 1```

### 输出

```
6```

## 样例 #2

### 输入

```
4 6
1 1 1 1
1 1 1 0
1 1 0 0
1 0 0 0```

### 输出

```
50```

## 样例 #3

### 输入

```
10 500000
0 1 0 1 0 0 0 0 1 1
1 1 1 0 1 1 1 0 1 0
0 0 1 1 0 0 1 1 0 0
0 1 1 1 1 1 0 1 1 0```

### 输出

```
866263864```

# 题解

## 作者：zhouyuhang (赞：3)

设 $f_{i,j}$ 为 $j$ 步走到 $i$ 的方案数，答案即为 $f_{n,k}$。

对每一行建立生成函数，即 $F_i(x)=\sum_{j=0}f_{i,j}x^j$。根据题意不难得到 $F_i(x)=\frac{B_{i-1}xF_{i-1}(x)+C_{i-2}xF_{i-2}(x)}{1-A_ix}$。于是我们可以得到形如 $F_i(x)=\alpha_iF_1(x)$ 的式子。现在问题只在于求出 $F_1(x)$。

注意到 $F_1(x)=1+\sum_{i=1}^nA_ixF_i(x)$，即 $F_1(x)=\frac{1}{1-\sum_{i=1}^n\alpha_iA_ix}$。因此我们只需求出 $\alpha_n$ 和 $\sum_{i=1}^n\alpha_iA_i$ 即可。

我们将一开始的递推式写成矩阵形式，即为 

$$
\begin{aligned}
& \begin{bmatrix}
F_n(x) \\
F_{n-1}(x)
\end{bmatrix} \\
& =
\begin{bmatrix}
\frac{B_{n-1}x}{1-A_nx} & \frac{C_{n-2}x}{1-A_nx} \\
1 & 0 \\
\end{bmatrix}
\times
\begin{bmatrix}
F_{n-1}(x) \\
F_{n-2}(x)
\end{bmatrix} \\
& = \prod_{i=2}^n \begin{bmatrix}
\frac{B_{i-1}x}{1-A_ix} & \frac{C_{i-2}x}{1-A_ix} \\
1 & 0 \\
\end{bmatrix}
\end{aligned}
$$

分治 NTT 并分别维护矩阵中每一项的分子分母即可求出 $\alpha_n$。求 $\sum_{i=2}^nA_i\alpha_i$ 类似。

实现时，暴力通分会导致多项式次数爆炸，但是注意到分母总是形如 $(1-x)^c$，因此只需记录 $c$。这样不仅可以省掉许多常数，通分时也可以保证复杂度（分式加法时分母次数只会取 $\max$）。

---

## 作者：Shattered_Shade (赞：1)

发现如果没有返回 1 号节点的边可以直接 dp，此时设 $f_{i,j}$ 为经过 $j$ 条边的到 $i$ 的方案数，此时有递推式 $f_{i,j}=A_if_{i,j-1}+B_{i-1}f_{i-1,j-1}+C_{i-2}f_{i-2,j-1}$，写成 GF 有 $F_i=A_ixF(x)+B_{i-1}xF_{i-1}(x)+C_{i-2}xF_{i-2}(x)$，即 $F_i=\frac{B_{i-1}x}{1-A_ix}F_{i-1}(x)+\frac{C_{i-2}x}{1-A_ix}F_{i-2}(x)$，写成矩阵的形式有 $\begin{aligned} & \begin{bmatrix} F_n(x) \\ F_{n-1}(x) \end{bmatrix} = \begin{bmatrix} \frac{B_{n-1}x}{1-A_nx} & \frac{C_{n-2}x}{1-A_nx} \\ 1 & 0 \\ \end{bmatrix} \times \begin{bmatrix} F_{n-1}(x) \\ F_{n-2}(x) \end{bmatrix}= \prod_{i=2}^n \begin{bmatrix} \frac{B_{i-1}x}{1-A_ix} & \frac{C_{i-2}x}{1-A_ix} \\ 1 & 0 \\ \end{bmatrix} \end{aligned}$，由于通分的复杂度很爆炸，考虑单独提取分母有 $\frac{1}{\prod_{i=2}^n(1-A_ix)}\prod_{i=2}^n \begin{bmatrix} B_{i-1}x & C_{i-2}x \\ 1-A_ix & 0 \\ \end{bmatrix}$，可以分治 NTT $O(n\log^2n)$ 计算。

考虑返回 1 号节点的边，此时上述的 $F_i(x)$ 为 1 走到 $i$ 不重复经过 1 的方案数，类似地，定义 $G(x)$ 为从 1 返回 1，且之间不经过 1 的方案数，则有 $G(x)=x\sum_{i=1}^{n}D_iF_i(x)$，答案多项式即为 $F_n(x)\times(1+G(x)+G^2(x)\dots)=\frac{F(x)}{1-G(x)}$。现在考虑如何算出 $G(x)$，发现同样为线性递推，设 $G_i(x)=\sum_{j=1}^{i}D_jF_j=G_{i-1}+D_iF_i$，和 $F$ 的递推矩阵结合一下则有

$\begin{bmatrix} F_n(x) \\ F_{n-1}(x)\\ G_n(x) \end{bmatrix}=\frac{1}{\prod_{i=2}^n(1-A_ix)}\prod_{i=2}^n \begin{bmatrix} B_{i-1}x & C_{i-2}x & 0 \\ 1-A_ix & 0 & 0 \\ D_iB_{i-1}x & D_iC_{i-2}x & 1-A_ix \end{bmatrix}\times \begin{bmatrix}1\\ 0\\ D_1\end{bmatrix}$，可以 $O(n\log^2n)$ 计算出。

最后答案即为 $[x^k]\frac{F_n(x)}{1-xG_n(x)}$，多项式求逆计算即可。

[大常数代码 qwq](https://atcoder.jp/contests/abc317/submissions/58537341)

---

