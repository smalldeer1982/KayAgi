# [Aboi 2077] SL2(Z/NZ)

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/gdzfpiv1.png)

## 题目描述

求模 $N$ 意义下行列式为 $1$ 的 $2\times2$ 矩阵数量。

即：
$$
\sum_{a=0}^{N-1}\sum_{b=0}^{N-1}\sum_{c=0}^{N-1}\sum_{d=0}^{N-1}[ad-bc\equiv1\ (\bmod\ N)]
$$

## 说明/提示

| 子任务编号 | $N$ | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $\le50$ | $10$ |
| $2$ | $\le200$ | $10$ |
| $3$ | $\le10^3$ | $20$ |
| $4$ | $\le10^6$ | $20$ |
| $5$ | $\le10^9$ | $20$ |
| $6$ | $\le10^{18}$ | $20$ |


对于所有数据，$1\le T\le10$，$1\le N\le10^{18}$。

## 样例 #1

### 输入

```
10
2
5
11
23
101
64
128
114514
1919810
1145141919810```

### 输出

```
6
120
1320
12144
1030200
196608
1572864
173069674
546691096
761755430```

# 题解

## 作者：WorldMachine (赞：11)

首先来求模素数 $p$ 意义下行列式为 $1$ 的 $2\times 2$ 矩阵个数，即 $|\text{SL}_2(\mathbb Z/p\mathbb Z)|$。注意到可以通过给矩阵的某一行乘上 $k$ 使得它的行列式变为原来的 $k$ 倍，那么在模 $p$ 意义下，行列式为 $1$ 的矩阵和行列式为 $k$ 的矩阵是一一对应的。记 $|\text{GL}_2(\mathbb Z/p\mathbb Z)|$ 为模 $p$ 意义下 $2\times2$ 的可逆矩阵（行列式不为 $0$）的个数，有：
$$
|\text{SL}_2(\mathbb Z/p\mathbb Z)|=\dfrac{|\text{GL}_2(\mathbb Z/p\mathbb Z)|}{p-1}
$$
现在要求模 $p$ 意义下行列式不为 $0$ 的 $2\times 2$ 矩阵个数，这就要求矩阵是满秩的，也即第一行和第二行线性无关。让第一行随便选，只要不全为 $0$ 即可，有 $p^2-1$ 种选法；第二行还要求不能和第一行线性相关，即不能等于 $kr_1$ 的形式，$k$ 可以取 $0\sim p-1$，一共有 $p^2-p$ 种选法。故有 $|\text{GL}_2(\mathbb Z/p\mathbb Z)|=(p^2-1)(p^2-p)$，则 $|\text{SL}_2(\mathbb Z/p\mathbb Z)|=p^3\left(1-\dfrac{1}{p^2}\right)$。

现在要求解 $\text{SL}_2(\mathbb Z/p^k\mathbb Z)$ 的大小，考虑如何从 $p^{k-1}$ 推到 $p^k$。对于模 $p^k$ 意义下的矩阵，将它的每个元素对 $p^{k-1}$ 取模，可以得到群同态 $f:\text{SL}_2(\mathbb Z/p^k\mathbb Z)\mapsto\text{SL}_2(\mathbb Z/p^{k-1}\mathbb Z)$，并且这是一个满同态。根据群同态基本定理，有 $\dfrac{|\text{SL}_2(\mathbb Z/p^k\mathbb Z)|}{|\ker f|}=|\text{SL}_2(\mathbb Z/p^{k-1}\mathbb Z)|$，那么现在要求 $f$ 的核的大小，也就是有多少个模 $p^{k-1}$ 意义下的单位矩阵在模 $p^k$ 意义下行列式为 $1$。

设该矩阵为 $\begin{bmatrix}ap^{k-1}+1&bp^{k-1}\\cp^{k-1}&dp^{k-1}+1\end{bmatrix}$，其中有 $0\le a,b,c,d<p$。其行列式为 $(ap^{k-1}+1)(dp^{k-1}+1)-bcp^{2k-2}$，对 $p^k$ 取模后为 $(a+d)p^{k-1}+1$，要使得其同余于 $1$，需要 $p\mid(a+d)$，满足条件的矩阵共有 $p^3$ 个，因此有 $|\ker f|=p^3$。那么 $|\text{SL}_2(\mathbb Z/p^k\mathbb Z)|=p^3|\text{SL}_2(\mathbb Z/p^{k-1}\mathbb Z)|$。边界情况为 $|\text{SL}_2(\mathbb Z/p\mathbb Z)|=p^3\left(1-\dfrac{1}{p^2}\right)$，那么有：
$$
|\text{SL}_2(\mathbb Z/p^k\mathbb Z)|=p^{3k}\left(1-\dfrac{1}{p^2}\right)
$$
最后要对任意的 $N$ 求出 $\text{SL}_2(\mathbb Z/N\mathbb Z)$。根据环论中的中国剩余定理，有环同构 $\mathbb Z/N\mathbb Z\cong\prod\limits_{p^k||N}\mathbb Z/p^k\mathbb Z$（$p^k\mid\mid N$ 表示 $p^k\mid N$ 且 $p^{k+1}\nmid N$）。因此有群同构：
$$
\text{SL}_2(\mathbb Z/N\mathbb Z)\cong\prod_{p^k||N}\text{SL}_2(\mathbb Z/p^k\mathbb Z)
$$
那么 $|\text{SL}_2(\mathbb Z/N\mathbb Z)|$ 是积性函数，因此有：
$$
|\text{SL}_2(\mathbb Z/N\mathbb Z)|=\prod_{p^k||N}p^{3k}\left(1-\dfrac{1}{p^2}\right)
$$
Pollard-ρ 分解素因子计算即可。

---

## 作者：飞雨烟雁 (赞：6)

这题还是比较简单的，本文证明一个更广的结论。

定义 $M_n(R)$ 为含幺交换环 $R$ 上的 $n$ 阶矩阵群，定义

$$\text{GL}_n(R)=\{A\in M_n(R):\det A\text{ is invertible in }R\},$$
$$\text{SL}_n(R)=\{A\in M_n(R):\det A=1\}.$$

我们的结论是：固定 $n$，则 $|\text{SL}_ n(\mathbb Z/m\mathbb Z)|$ 是关于 $m$ 的积性函数，且任给素数的幂 $p^k$，有

$$|\text{SL}_ n(\mathbb Z/p^k\mathbb Z)|=\frac{\prod_{i=0}^{n-1}(p^n-p^i)}{p-1}p^{(n^2-1)(k-1)}.$$

特别地，当 $n=2$ 就得到本题答案：

$$\text{SL}_2(\mathbb Z/n\mathbb Z)=\prod_{p^k\Vert n}p^{3k-2}(p^2-1).$$

------------

首先声明一下，结论的证明参考了资料 [How to calculate |SL2(Z/NZ)|](https://math.stackexchange.com/a/341435)。

关于积性函数的论断是易证的，采用中国剩余定理即可。

当 $k=1$ 时，要求 $|\text{SL}_ n(\mathbb Z/p\mathbb Z)|$，即求 $|\text{SL}_ n(\mathbb F_p)|$。注意到在 $\text{GL}_ n(\mathbb F_p)$ 中，行列式值是均匀分布的（因为可以给第一行所有数乘上 $s$，使之行列式值变为 $s$ 倍；从而任何行列式值为 $t$ 的矩阵都可与行列式值为 $1$ 的矩阵一一对应）。故有 $|\text{SL}_ n(\mathbb F_p)|=|\text{GL}_ n(\mathbb F_p)|/(p-1)$。

而 $|\text{GL}_ n(\mathbb F_p)|$ 的值是个经典结论，我们这里推导一下。

我们逐行填写矩阵，使其成为一个可逆矩阵。第一行可以随便填，只要不是零向量就行，故有 $p^n-1$ 种填法。第二行除了不能填成零向量，还不能与第一行的向量线性相关，所以有 $p^n-p$ 种填法。以此类推，第 $i$ 行不能填与前 $i-1$ 行向量线性相关的向量，即不能取由前 $i-1$ 行向量所张成的空间内的向量，故有 $p^n-p^{i-1}$ 种选法。全部乘起来就有

$$|\text{GL}_ n(\mathbb F_p)|=\prod_{i=0}^{n-1}(p^n-p^i).$$

这样就知道 $k=1$ 时 $|\text{SL}_ n(\mathbb Z/p\mathbb Z)|$ 是多少了。下面我们来求 $k\ge 2$ 时的公式。

一个自然的想法是，对于每个矩阵 $A\in\text{SL}_ n(\mathbb Z/p\mathbb Z)$，我们可以给每个元素都加上 $p$ 的倍数，共有 $p^{(k-1)n^2}$ 种方案。而且，这些矩阵的行列式值应该是均匀分布在 $1+jp$ 上的，$0\le j<p^{k-1}$，所以除掉 $p^{k-1}$ 就是行列式值为 $1$ 的方案个数了。

但这样不够严谨，我们来说明一下它们确实是均匀分布的。

对于矩阵 $A\in\text{SL}_ n(\mathbb Z/p\mathbb Z)$，我们按最后一列展开可知，其代数余子式 $A_{n,i},1\le i\le n$ 中必有一个不为 $0$，不妨设 $A_{n,n}\neq 0$。我们给 $A$ 除了第 $n$ 行第 $n$ 列之外的元素任意加上 $p$ 的倍数，然后给第 $n$ 行第 $n$ 列加上 $pj$，记这样得到的矩阵为 $B_j$。断言 $B_1,\cdots,B_{p^{k-1}}$ 中恰有一个的行列式为 $1$。要证明这个断言，只需证 $\det B_i$ 是个单射。这个是好证的，因为它们的代数余子式 $ B_{n,n}=A_{n,n}+pj$，必然可逆，然后用行列式的线性性去证就行了。

综上，$|\text{SL}_ n(\mathbb Z/p^k\mathbb Z)|=p^{(n^2-1)(k-1)}|\text{SL}_ n(\mathbb Z/p\mathbb Z)|$。

---

