# 「EZEC-10」「Byakkai OI 2021」Estahv

## 题目背景

> chrisl gjeztor Amledza  
> prof ovelmizer  
> dos carm ammeidha alzenghar  
> kawy may noxial gjeztor  
> Rupieilla vas photreywz idha

## 题目描述

我们有排成一排的无限个格子，它们从左往右以 $1,2,\dots$ 编号。

你可以在每个格子中填入任意**正整数** $k$，则你会得到 $C_k$ 的权值。  
其中满足 $C_0=C_1=1$，$C_i = \sum\limits_{j=0}^{i-1} C_j C_{i-j-1}$ $(i \ge 2)$。  
若干个格子的总权值定义为它们的权值之积。

现在你需要从左往右依次在格子中填入数字，直到填入的数字之和等于 $n$ 或超过 $n$ 为止。  
如此之后，你还需要为每个填入数字的格子涂上黑色或者白色。需要满足：不存在任意连续的 $2$ 个及以上白色的格子，且第一个格子必须为黑色，最后一个填入数字的格子必须为白色。  
然后，你需要把所有相邻的均填入了数字的同色格子两两连边，并从中选出一个格子集合 $S$，满足 $S$ 内的格子两两不连通（可以为空）。

一种方案的权值定义为所有格子的总权值。

给定 $n$，请你对于 $s=0,1,\dots,n$，计算所有完成以上操作，且填入的数字之和**恰好**为 $n$，且黑色的格子数为 $s$ 的所有方案的权值之和。  
两种方案不同当且仅当填入数字的格子数不同或对应格子填入的数字不同或对应格子颜色不同或 $S$ 集合不同。  
对 $998244353$ 取模。

## 说明/提示

【样例 $1$ 说明】

当 $n=3$ 时，可以有 $2$ 或 $3$ 个格子。  
若有 $2$ 个格子，则填数方案为 $[1,2]$ 或 $[2,1]$，权值共为 $2 \times C_1 \times C_2 = 4$；填色方案为 `BW`，必有一个黑色格子；$S$ 集合的选择是 $\{\},\{1\},\{2\},\{1,2\}$（以格子的编号表示）。  
若有 $3$ 个格子，则填数方案为 $[1,1,1]$，权值为 $C_1^3=1$；填色方案为 `BBW`，必有两个黑色格子；$S$ 集合的选择是 $\{\},\{1\},\{2\},\{3\},\{1,3\},\{2,3\}$（以格子的编号表示）。  
其中 `B` 表示黑色，`W` 表示白色。

【数据规模与约定】

**本题采用捆绑测试。**

- Subtask 1（30 points）：$n\le10$。
- Subtask 2（20 points）：$n\le300$。
- Subtask 3（20 points）：$n \le 5000$。
- Subtask 4（30 points）：无特殊限制，时限为 $3.5s$。

对于 $100\%$ 的数据，$1 \le n \le 10^5$。 


### 提示

为了方便各位获得暴力分，这里给出结论：
$$
C_k = \frac1k \binom{2k}{k-1} = \binom{2k-1}{k-1}-\binom{2k-1}{k-2}
$$

## 样例 #1

### 输入

```
3```

### 输出

```
0 16 6 0```

## 样例 #2

### 输入

```
8```

### 输出

```
0 8008 24388 29840 16788 4360 476 16 0```

# 题解

## 作者：Aleph1022 (赞：12)

令 $C(z) = z(1+C(z))^2$ 也就是卡特兰数去掉常数。  
分析一下题目给出的代数结构，显然可以刻画成
$$
[z^n] \frac1{1-2C(z)G(C(z))}, \qquad G(z) = \frac{zw(2-zw)}{(1-zw)^2}
$$

令
$$
F(z) = \frac1{1-2zG(z)} = \frac{1-2zw+z^2w^2}{1-2zw+z^2w^2-4z^2w+2z^3w^2}
$$

## 算法 0 from EI

根据直觉可以发现答案是 D-finite 的。  
高斯消元即可。

---

或者，作另类拉格朗日反演可得
$$
[z^n] F(C(z)) = [z^n] F(z) (1-z)(1+z)^{2n-1}
$$

记 $H(z) = (1-z)(1+z)^{2n-1}$。  
接下来有两条路可选。

## 算法 1

考虑记 $h_k = [z^{n-k}] H(z)$，则所求即
$$
\sum\limits_{k\ge0} h_k [z^k] F(z)
$$

典型的线性算法。考虑转置原理，变成计算
$$
\sum\limits_{k\ge0} h_k [w^k] F(z)
$$

换元 $s = zw$，
$$
\sum\limits_{k\ge0} h_k z^k [s^k] \frac{(1-s)^2}{1-s(2-s)(1+2z)}
$$

记 $f_k = z^k [s^k] \frac{(1-s)^2}{1-s(2-s)(1+2z)}$，则可以写出递推式
$$
f_k = (1+2z)(2zf_{k-1}-z^2f_{k-2})+[k=0]-2z[k=1]+z^2[k=2]
$$

其转移可写作矩阵，则问题变成若干矩阵的前缀积的带权和，可以利用[这里](https://www.luogu.com.cn/blog/your-alpha1022/she-lun-fou-cdq-di-fen-zhi-ntt-yang-xi-jie-mi-post)的技术做到 $\Theta(n \log^2 n)$。

然后将以上算法转置即可。  
时间复杂度 $\Theta(n \log^2 n)$。

## 算法 2

作代换 $s=zw$，则
$$
[w^n] F(z) = z^n [s^n] \frac{(1-s)^2}{1-2s(1+2z)+s^2(1+2z)}
$$

作分式分解，则
$$
\frac{(1-s)^2}{1-2s(1+2z)+s^2(1+2z)} = \frac{(1-s)^2}{A(z)-B(z)}\left(\frac{A(z)}{1-sA(z)}-\frac{B(z)}{1-sB(z)}\right)
$$

其中 $\begin{cases}
A(z)=1+2z+\sqrt{2z(1+2z)} \\
B(z)=1+2z-\sqrt{2z(1+2z)}
\end{cases}$。

则考虑
$$
[w^k z^n] F(C(z)) = [w^k z^n] F(z) H(z)
$$
可以拆成若干个
$$
[z^m] \frac{z^kH(z)}{A(z)-B(z)} \left(A^{k+1}(z) - B^{k+1}(z)\right) = 2[z^m] \frac{z^kH(z)}{A(z)-B(z)} A^{k+1}(z),\qquad m\in \mathbb Z
$$

为了消除 $\sqrt z$ 项，将 $z$ 代换到 $z^2$ 并整理，可以转化为计算
$$
[z^{2m+1}] \frac{Q(z)}{1-tP^2(z)}
$$

其中
$$
P(z)=z\sqrt{1+2z^2+z\sqrt{2(1+2z^2)}}, Q(z)=\frac{(1-z^2)(1+z^2)^{2n-1}(1+2z^2+z\sqrt{2(1+2z^2)})}{\sqrt{2(1+2z^2)}}
$$

再次拉格朗日反演即可：
$$
[z^{2m+1}] \frac{Q(z)}{1-tP^2(z)} = \frac1{2m+1}[z^{2m}] \left[\frac{Q\left(P^{\langle -1\rangle}(z)\right)}{1-tP^2(z)}\right]' \left(\frac z{P^{\langle -1\rangle}(z)}\right)^{2m+1}
$$

令 $R(z)=Q\left(P^{\langle -1\rangle}(z)\right),S(z)=\left(\frac z{P^{\langle -1\rangle}(z)}\right)^{2m+1}$，则
$$
\left[\frac{R(z)}{1-tz^2}\right]' = \frac{R'(z) + tz[2R(z)-zR'(z)]}{[1-tz^2]^2}
$$

故
$$
\begin{aligned}
[t^k z^{2m+1}] \frac{Q(z)}{1-tP^2(z)}
&= \frac1{2m+1}[z^{2m}]\left[z^{2k}R'(z)S(z) + 2kz^{2k-1}R(z)S(z)\right] \\
&= \frac1{2m+1}\left[[z^{2(m-k)}]R'(z)S(z) + 2k[z^{2(m-k)+1}]R(z)S(z)\right]
\end{aligned}
$$

总时间复杂度 $\Theta(n \log n)$。

---

