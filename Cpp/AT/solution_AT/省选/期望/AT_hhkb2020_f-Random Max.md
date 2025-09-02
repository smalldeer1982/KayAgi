# Random Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_f

$ N $ 個の連続型確率変数 $ x_i $ ($ 1\ <\ =\ i\ <\ =\ N $) があり、それぞれ $ [L_i,\ R_i] $ の範囲をとる連続一様分布にしたがいます。 (すなわち、$ x_i $ は $ L_i $ 以上 $ R_i $ 以下の実数を等確率でとりうるランダムな変数です)

本問題の制約下では、これらの $ N $ 個の確率変数の最大値の期待値を $ E $ とすると、$ E\ \times\ (N+1)!\ \times\ \prod_{i=1}^N\ (R_i\ -\ L_i) $ は正整数であることが示せます。この値を $ 1,000,000,007 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 1000 $
- $ 0\ <\ =\ L_i\ <\ R_i\ <\ =\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

この確率変数の最大値の期待値は、とりうる範囲の中央値、すなわち $ E\ =\ \frac{3}{2} $ に等しいです。 よって、 $ E\ \times\ (N+1)!\ \times\ (R_1\ -\ L_1)\ =\ E\ \times\ 2\ =\ 3 $ が正解となります。

### Sample Explanation 2

求める期待値は $ E\ =\ \frac{5}{3} $ です。

## 样例 #1

### 输入

```
1
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
2
1 2
1 2```

### 输出

```
10```

## 样例 #3

### 输入

```
2
1 2
2 4```

### 输出

```
36```

## 样例 #4

### 输入

```
5
40 96
81 92
16 384
32 768
65 536```

### 输出

```
52776507```

# 题解

## 作者：joke3579 (赞：1)

## $\text{Statement}$

设随机变量 $X_1, X_2, \dots, X_n$ 分别在区间 $[L_1, R_1], [L_2, R_2], \dots, [L_n, R_n]$ 上均匀分布，求 $\max(X_1, X_2, \dots, X_n)$ 的期望值。

## $\text{Solution}$

令 $\max X$ 为代表 $\max(X_1, X_2, \dots, X_n)$ 的随机变量。同时设 $F(x) = \Pr[\max X \le x]$ 为 $\max X$ 的累积分布函数（CDF）。令 $\max X$ 的概率密度函数（PDF）为 $P(x)$。由变量的取值非负，且 PDF 的积分为 CDF，我们可以导出使用 CDF 表示 $E[\max X]$ 的方式：
$$\begin{aligned}

& E[\max X]
\\ = \ & \int_{0}^{\infty} yP(y) \text d y
\\ = \ & \int_{0}^{\infty}  \int_{0}^{y}P(y) \text dx \text d y
\\ = \ & \int_{0}^{\infty} \int_{x}^{\infty}P(y) \text d y\text d x 
\\ = \ & \int_{0}^{\infty}\left( 1 - \int_{0}^{x}P(y) \text d y \right) \text d x 
\\ = \ & \int_{0}^{\infty}1 - F(x) \text d x 

\end{aligned}$$

我们记 $\max X$ 的取值上界为 $R = \max\left\{R_i\right\}$。重写答案为
$$R - \int_{0}^{R} F(x) \text d x $$

这样只需要在 $[0,R]$ 的范围内考察 $F$。

我们发现，$\max X \le x$，当且仅当 $\forall X_i \le x$。因此 $\max X$ 的 CDF 应当是各个 $X_i$ 的 CDF $f_i$ 的乘积：

$$F(x) = \Pr [\max X \le x] = \prod_{i=1}^n \Pr [X_i \le x] = \prod_{i=1}^n f_i(x)$$

而 $f_i(x)$ 是易表出的：

$$f_i(x) = \left\{
    \begin{aligned}
    & 0 && x\le L_i \\ 
    & \frac{x - L_i}{R_i - L_i} && L_i \le x \le R_i \\ 
    & 1 && x \ge R_i \\
    \end{aligned}
\right .$$

$L_i \le x \le R_i$ 段的解析式可由 CDF 的定义导出。

注意到我们可以通过将 $[0, R]$ 以 $L_i, R_i$ 为间隔分为 $O(n)$ 个段，从大到小进行处理。如果扫到一个 $L_i$，则无需接着进行，因为这其中定有一个元素为 $0$，之后的 $F(x)$ 定为 $0$。

注意到加入一段等于是给当前的 $F(x)$ 乘入了一个度数为 $1$ 的多项式，且 $F(x)$ 初始时 $=1$，因此 $F$ 在任何时刻也是多项式。我们在移动段时只需要乘入 $\frac{x - L_i}{R_i - L_i}$ 即可。

需要注意的是，我们对每段 $[l, r]$ 考虑的积分是
$$ \int_{l}^{r}1 - F(x) \text d x = (r - l) - \int_{l}^{r}F(x) \text d x $$

由于 $F$ 为多项式，直接做即可。

计算结果乘入 $(n+1)! \times \prod_{i=1}^n (R_i - L_i)$ 即为最终答案。

总时间复杂度为 $O(n^2)$。

[Submission](https://atcoder.jp/contests/hhkb2020/submissions/37455737).

---

## 作者：Galois_Field_1048576 (赞：1)

## 前记
本题需要一定的微积分基础。您需要了解积分的意义和求多项式积分的方法。
## 期望的定义
我们一般把离散期望做如下定义：  
$$\mathcal E(S) = \sum_{s \in S} s {\bf Prob}(s)$$
**例 1：骰子的期望点数。**
$$\mathcal E(\{1,2,3,4,5,6\}) = \sum_{i=1}^6 \dfrac 16i = \dfrac 72$$

**例 2：$\bf [0,1)$ 间均匀分布实数的期望**  
也许你会想当然地认为是 $0.5$，但是我们还没有定义连续的期望。  
考虑每 $\epsilon$ 取一个样（$\dfrac 1\epsilon \in \mathbb N^+$），最终取 $\dfrac 1\epsilon$ 个样，然后把所有 $[x, x+\epsilon)$ 都映射到 $x$。  
例如：当 $\epsilon = \dfrac 13$ 时：
- $[0, \frac 13) \to 0$
- $[\frac 13, \frac 23) \to \frac 13$
- $[\frac 23, 1) \to \frac 23$

，当 $\epsilon \to 0$ 时就可以视为 $[0,1)$ 的期望值，而期望值又是：
$$\begin{array}{ll}& \sum_{i=0}^{1/\epsilon-1} i \epsilon^2\\
=&\epsilon^2\sum_{i=0}^{1/\epsilon-1} i\\
=&\epsilon^2\frac{(1/\epsilon-1)(1/\epsilon)}2\\
=&\frac{\epsilon(1/\epsilon-1)}2\\
=&\frac{1-\epsilon}{2}
\end{array}$$
，所以期望值为
$$\mathcal E = \lim_{\epsilon \to 0} \dfrac{1-\epsilon}{2}=\dfrac 12$$
，这样我们才能完成结论：期望值为 $\dfrac 12$。

**例 3：连续期望的定义**  
定义 $\mathcal P_{C}(x) = \lim\limits_{\epsilon \to 0} \dfrac{{\bf Prob}(X \in [x, x+\epsilon))}\epsilon$，其中 $X$ 是随机值。  
由此定义的函数可以在连续问题上当作概率使用，被称为概率密度函数（Probability Density Function，PDF）  
则考虑取样，期望值为：
$$\sum_{i=D/\epsilon}^{U/\epsilon-1} i\epsilon \mathcal {\bf Prob}(X \in [i\epsilon, i\epsilon+\epsilon))$$
，进行一系列推导得到
$$\int_{D}^{U} \mathcal P_C(x) x {\bf d}x$$
。此又可作为连续期望的定义

（$D$ 是下界，$U$ 是上界）

**例 4：用定义求 $\bf [0,1)$ 间均匀分布实数的期望**
会发现 $\mathcal P_C(x) = 1$，则
$$\mathcal E = \int_0^1 x {\bf d}x = \dfrac 12$$
。

## PDF 与 CDF
设 $P(x)$ 是 PDF，定义 CDF（Cumulative Density Function）
$$C(x) = \int_{0}^{x} P(t) {\bf d}t$$
。  
**定理 2.1** $C(x) = {\bf Prob}(X \lt x)$。  
证明：
$$\begin{aligned}
C(x)&=\lim\limits_{\epsilon\to0} \epsilon\sum_{i=0}^{x/\epsilon} P(i\epsilon)\\
&=\lim\limits_{\epsilon\to0}\epsilon\sum\limits_{i=0}^{x/\epsilon} \dfrac{{\bf Prob}(X \in [i\epsilon,(i+1)\epsilon))}{\epsilon} \\
&=\lim\limits_{\epsilon\to0}\sum\limits_{i=0}^{x/\epsilon} {{\bf Prob}(R \in [i\epsilon,(i+1)\epsilon))}\\
&={\bf Prob}(X \lt x)
\end{aligned}$$
**定理 2.2**
$$\int_{0}^{+\infty} x\mathcal P_C(x) {\bf d}x = \int_0^{+\infty}1-C(x){\bf d}x$$
证明：
$$\begin{aligned}
\int_0^{+\infty}x \mathcal P_C(x){\bf d}x&=\int_0^{+\infty} \int_0^x \mathcal P_C(x){\bf d}y{\bf d}x\\
&=\int_0^{+\infty}\int_x^{+\infty} \mathcal P_C(y) {\bf d}y {\bf d}x \\
&=\int_0^{+\infty}\int_0^{+\infty} \mathcal P_C(y) {\bf d}y - \int_0^{x} \mathcal P_C(y) {\bf d}y {\bf d}x \\
&=\int_0^{+\infty} C(+\infty) - C(x) {\bf d}x \\
&=\int_0^{+\infty} 1 - C(x) {\bf d}x
\end{aligned}$$

## 本题解法
因为 $\max_{i} x_i < t \iff \forall i,x_i < t$，所以 
$$C(x) = \prod_{i=1}^{n} {\bf Prob}(x_i < x)$$
，而 
$${\bf Prob}(x_i<x) = \left\{\begin{matrix}
0 & x < L_i \\
\dfrac{x-L_i}{R_i-L_i} & x \in [L_i, R_i] \\
1 & x > R_i
\end{matrix}\right.$$
设集合 $E = \{\max L\} \cup \{r \in R \mid r > \max L\}$。显然 $|E| = O(n)$。将 $E$ 从大到小排序 得到 $E'$，钦定 $E_0' = \infty$，则有在 $[E_i',E_{i-1}']$ 里的多项式是一样的，对每一个区间去积分即可。

两个区间内是乘一个一次多项式，所以两个区间之间的时间复杂度为 $O(n)$，每一个区间的积分的时间复杂度为 $O(n)$，总时间复杂度 $O(n^2)$。

代码没写。
## 后记
这是我的连续积分入门题，请期待《浅谈期望》（也许可能是日报水平）。

---

