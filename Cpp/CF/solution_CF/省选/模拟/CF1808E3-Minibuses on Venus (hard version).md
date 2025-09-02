# Minibuses on Venus (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the three versions is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

Maxim is a minibus driver on Venus.

To ride on Maxim's minibus, you need a ticket. Each ticket has a number consisting of $ n $ digits. However, as we know, the residents of Venus use a numeral system with base $ k $ , rather than the decimal system. Therefore, the ticket number can be considered as a sequence of $ n $ integers from $ 0 $ to $ k-1 $ , inclusive.

The residents of Venus consider a ticket to be lucky if there is a digit on it that is equal to the sum of the remaining digits, modulo $ k $ . For example, if $ k=10 $ , then the ticket $ 7135 $ is lucky because $ 7 + 1 + 5 \equiv 3 \pmod{10} $ . On the other hand, the ticket $ 7136 $ is not lucky because no digit is equal to the sum of the others modulo $ 10 $ .

Once, while on a trip, Maxim wondered: how many lucky tickets exist? At the same time, Maxim understands that this number can be very large, so he is interested only in the answer modulo some prime number $ m $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808E3/2314a7c75bce1209ddf61a583b83dbea8efe39a0.png)

## 说明/提示

In the first example, there are only four lucky tickets: $ 000 $ , $ 011 $ , $ 101 $ , and $ 110 $ .

## 样例 #1

### 输入

```
3 2 1000000007```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4 1000000007```

### 输出

```
28```

# 题解

## 作者：Fido_Puppy (赞：14)

## 题目链接

[CF1808E3 Minibuses on Venus (hard version)](https://codeforces.com/contest/1808/problem/E3)

## 题解

看到 $n \le 10 ^ {18}, k \le 2000$ 的数据范围，我们容易想到数位 $\text{dp}$ 和矩阵乘法没有前途，所以可以考虑组合数学。

我们首先枚举最后的总和 $s$，并且找到对应的 $x$，使得 $2x \equiv s \pmod k$，明显地，如果我们保证序列的总和为 $s$，并且序列中出现过 $x$，那么这个序列就是合法的。

### 情况 $1$：$k \equiv 1 \pmod 2$

这种情况下，对于每个 $s \in [0, k)$，只有一个 $x$ 与之对应。

考虑设 $f_i$ 表示至少填 $i$ 个 $x$ 的方案数，$g_i$ 表示恰好填 $i$ 个 $x$ 的方案数。

对于 $f_i$ 的计算，我们考虑先把 $i$ 个 $x$ 给填好，方案数为 $\dbinom{n}{i}$，然后剩下的 $n - i$ 个位置中，我们考虑前 $n - i - 1$ 个可以随意填，方案数为 $k ^ {n - i - 1}$，为了使得整个序列的总和为 $s$，所以最后那个数是唯一的。

所以 $\forall i \in [1, n), f_i = \dbinom{n}{i} \times k ^ {n - i - 1}$，而 $f_n$ 则需特判是否有 $xn \equiv s \pmod k$。

然后我们考虑如何通过 $f$ 来计算 $g$。

对于一个恰好填 $m$ 个 $x$ 的方案，在这 $m$ 个 $x$ 中，可以任选 $i$ 个 $x$ 作为 $f$ 中最先填的 $i$ 个数，所以 $g_m$ 中的一个方案在 $f_i$ 中会被重复计算 $\dbinom{m}{i}$ 次。

所以有：

$$f_i = \sum_{j = i} ^ n \dbinom{j}{i} \times g_j$$

根据二项式反演：

$$g_i = \sum_{j = i} ^ n (-1) ^ {j - i} \times \dbinom{j}{i} \times f_j$$

这样我们就得到了一个 $\Theta(n ^ 2 k)$ 的做法。

然后直接考虑推式子，最终答案为：

$$\sum_{i = 1} ^ n \sum_{j = i} ^ n (-1) ^ {j - i} \times \dbinom{j}{i} \times f_j$$

由于 $f_n$ 的计算方法不太一样，所以将其拎出，单独处理，我们首先计算：

$$\sum_{i = 1} ^ {n - 1} \sum_{j = i} ^ {n - 1} (-1) ^ {j - i} \times \dbinom{j}{i} \times f_j$$

$$= \sum_{i = 1} ^ {n - 1} \sum_{j = i} ^ {n - 1} (-1) ^ {j - i} \times \dbinom{j}{i} \times \dbinom{n}{j} \times k ^ {n - j - 1}$$

$$= \sum_{j = 1} ^ {n - 1} \dbinom{n}{j} \times k ^ {n - j - 1} \times \sum_{i = 1} ^ {j} (-1) ^ {j - i} \times \dbinom{j}{i}$$

而后面的求和式可以用二项式定理：

$$= \sum_{j = 1} ^ {n - 1} \dbinom{n}{j} \times k ^ {n - j - 1} \times (-1) ^ {j + 1}$$

然后再次使用二项式定理：

$$= -\dfrac1k \times \sum_{j = 1} ^ {n - 1} \dbinom{n}{j} \times k ^ {n - j} \times (-1) ^ j$$

$$= -\dfrac1k \times \left[ (k - 1) ^ n - k ^ n - (-1) ^ n \right]$$

接着考虑 $f_n$ 的贡献：

$$\sum_{i = 1} ^ n \dbinom{n}{i} \times (-1) ^ {n - i} \times f_n$$

$$= f_n \times \sum_{i = 1} ^ n \dbinom{n}{i} \times (-1) ^ {n - i}$$

使用二项式定理可得：

$$= f_n \times (-1) ^ {n + 1}$$

至此，我们得到了一个 $\Theta(k \log n)$ 的做法，预处理 $(k - 1) ^ n$ 和 $k ^ n$ 可以做到 $\Theta(k + \log n)$。

### 情况 $2$：$k \equiv 0 \pmod 2$

和情况 $1$ 相似，只是对于每个偶数 $s$，有两个 $x_1, x_2$ 与之对应。

我们仍然考虑设 $f_i$ 表示至少选 $i$ 个 $x_1$ 或 $x_2$，设 $g_i$ 表示恰好选 $i$ 个。

类似地，$\forall i \in [1, n), f_i = \dbinom{n}{i} \times k ^ {n - 1 - i} \times 2 ^ {i}$，其余推式子的部分与情况 $1$ 类似。

然后考虑 $f_n$ 如何计算，首先容易想到一个 $\Theta(n)$ 做法：

枚举 $i$ 表示选择 $i$ 个 $x_1$，$n - i$ 个 $x_2$，然后判断是否合法，若合法，则将 $f_n$ 加上 $\dbinom{n}{i}$。

然后我们考虑合法的条件：

$$i \times x _1 + (n - i) \times x_2 \equiv s \pmod k$$

$$i \times (x_1 - x_2) \equiv s - n \times x_2 \pmod k$$

而 $s - n \times x_2$ 为一个常量，这里记作 $c$。

由于 $x_1 = \dfrac{s}{2}, x_2 = \dfrac{s}{2} + \dfrac{k}{2}$，所以 $x_1 - x_2 \equiv \dfrac{k}{2} \pmod k$。

也就是说：

$$\dfrac{k}{2} \times i \equiv c \pmod k$$

当 $i$ 为偶数时，左式恒为 $0$；当 $i$ 为奇数时，左式恒为 $\dfrac{k}{2}$。

所以可得：

$$f_n = \begin{cases} \sum_{i \equiv 0 \pmod 2} \binom{n}{i} \quad c = 0 \\ \sum_{i \equiv 1 \pmod 2} \binom{n}{i} \quad c = \frac{k}{2} \\ 0 \quad \text{otherwise} \end{cases}$$

而对于形如：

$$\sum_{i \equiv b \pmod 2} \dbinom{n}{i}$$

这样的式子，可以考虑将其放到杨辉三角上的第 $n$ 行，然后将所有组合数都拆成 $n - 1$ 行的组合数，可以发现无论 $b = 0 / 1$，答案都是第 $n - 1$ 行组合数的和，等于 $2 ^ {n - 1}$。

所以问题就解决了，时间复杂度 $\Theta(k + \log n)$。

我这里的实现复杂度是 $\Theta(k \log n)$ 的。![](//图.tk/j)

### 代码链接

<https://codeforces.com/contest/1808/submission/200386783>

---

## 作者：ღꦿ࿐ (赞：9)

whk 的时候想到的 $O(\log k)$ 做法，很带劲，建议加强到 $10^{18}$。

考虑因为不好计算 **具体是哪个元素满足 $2x\equiv S \pmod  k $**，所以考虑统计全都不满足的序列然后减去。

$k=1$ 或 $n=1$ 时问题平凡，后文假设 $k > 1,n>1$。


$\text i . \  k\equiv 1\pmod 2 $

枚举 和 $S$ 后有唯一的 $x$ 使得 $2x\equiv S \pmod  k $。

现在要求不存在任何 $x$ 且和为 $S$ 的情况。

然后用一个容斥来计算（钦定 $x$ 个不满足，全都满足）


$f(i)$ 为钦定 $i$ 个 $x$ 的方案数，答案为 $\sum_{i=1}^{n} (-1)^if(i) $， $f(i)=\binom n ik^{n-i-1}(x\neq n)$， 因为无论前面的和是多少，最后一位都可以选择某个唯一的数使得答案是 $S$，所以原式可以化为

$$
\begin{aligned}
&\sum_{i=1}^{n-1}(-1)^i \binom n ik^{n-i-1} + (-1)^nf(n)
\\
=&\frac 1 k((k-1)^n-(-1)^n)+(-1)^n f(n)

\end{aligned}
$$

使用二项式定理处理求和，补上一个 $(-1)^n$。

所有 $S$ 的不符合的方案数之和就是 

$$

(k-1)^n-(-1)^n+(-1)^n\sum_{s=0}^{k-1} f_s(n)
$$

其中 $f_s(x)$ 表示和为 $s$ 且钦定全放 $x$ 的方案数等于 $[nx\equiv S\pmod  k] =[(n-2)S\pmod k]$。

所以 $\sum_{s=0}^{k-1} f_s(n) = \operatorname {gcd}(k,n-2)$。

整理得答案等于 $k^n-(k-1)^n+(-1)^n-(-1)^n\operatorname {gcd}(k,n-2)$。

$\text {ii}. k\equiv 0\pmod 2$

此时对于所有的奇数 $S$ 一定不合法，考虑从 $\dfrac {k^n} 2$ 中减去不合法且 $S$ 是偶数的方案数。

对于偶数 $S$，有且仅有 $x_1= \dfrac S 2 ,x_2=\dfrac {S+k} 2$ 被禁止。

令 $f(i)$ 为钦定 $i$ 个 $x_1$ 或 $x_2$ 的方案数

$$

\begin{aligned}
&\sum_{i=1}^{n-1}(-1)^i \binom n i 2^ik^{n-i-1} + (-1)^nf(n)
\\
=&\frac 1 k((k-2)^n-(-2)^n)+(-1)^n f(n)

\end{aligned}

$$

所有 $S$ 的不符合的方案数之和就是 


$$

\frac 1 2( (k-2)^n-(-2)^n )+(-1)^n \sum_{s=0}^{k-1} f_s(n)
$$



其中 $f_s(n) $ 是  $n$ 个 $x_1$ 或 $x_2$ 和为 $S$ 的方案数。


假设有 $c$ 个 $x_1$，$n-c$ 个 $x_2$，那么要求

$$
\sum_{c=0}^n [cx_1+(n-c)x_2\equiv S \pmod k] \binom n c
$$

其中 

$$


\begin{aligned}

cx_1+(n-c)x_2&\equiv S \pmod k \\

\dfrac k 2 c+\dfrac S 2 n &\equiv S \\

\frac k 2 &c\equiv (2-n)\frac S 2

\end{aligned}
$$

仅当 $(2-n)S\equiv 0\pmod \frac k 2$  时，才有 $c = 2^{n-1}$，否则 $c = 0$，因为这相当于限制了组合数下指标的奇偶性，然后求和，所以答案总是等于 $2^{n-1}$

那么有

$$
\begin{aligned}
f_s(n) &= 2^{n-1}[(2-n)S\equiv 0\pmod {\frac k 2}]

\end{aligned}
$$

那么 


$$
\begin{aligned}
\sum_{s=2t,0<2t<k} f_s(n)&= \sum_{s=2t,0<2t<k} 2^{n-1}[(2-n)S\equiv 0\pmod {\frac k 2}]
\\
&=2^{n-1}\operatorname{gcd}(n-2,\frac k 2)
\end{aligned}
$$


整理得答案为

$$

\frac 1 2 (k^n-(k-2)^n+(-2)^n)+(-1)^n2^{n-1}\operatorname{gcd}(n-2,{\frac k 2})
$$

时间复杂度 $O(\log n)$，瓶颈在求最大公因数。

---

## 作者：Alex_Wei (赞：8)

### [CF1808E3 Minibuses on Venus (hard version)](https://www.luogu.com.cn/problem/CF1808E3)

**一**

设 $s = (\sum a_i) \bmod k$，不存在 $2a_i\equiv s\pmod k$。

补集转化，枚举 $s$，设 $f_{i, j}$ 表示长度为 $i$ 且总和为 $j$ 的非法序列，转移即枚举 $2a_{i + 1}\not\equiv s\pmod k$，$f_{i, j}\to f_{i + 1, (j + a_i)\bmod k}$。

对每个 $s$ 的 $f_{n, s}$ 求和，再用 $k ^ n$ 减掉，即为答案。

时间复杂度 $\mathcal{O}(n k ^ 3)$，可以通过 E1。[代码](https://codeforces.com/contest/1808/submission/208229905)。

**二**

先把 $k = 1$ 判掉。

当 $2\nmid k$ 时，对每个 $s\in [0, k - 1]$，存在恰好一个 $x$ 使得 $2x\equiv s\pmod k$，即 $x = \begin{cases} \frac s 2 & (2\mid s) \\ \frac {s + k} 2 & (2\nmid s) \end{cases}$。将 $a_i$ 减去 $x$，问题转化为：求 $\sum a_i\equiv s - nx\pmod k$ 且包含 $0$ 的序列数量。补集转化，套用 E1 的 DP，可知对于 $1\leq j < k$，$f_{i, k}$ 相等。有递推式 $f_{i, 0} = (k - 1) f_{i - 1, 1}$，$f_{i, 1} = f_{i - 1, 0} + (k - 2) f_{i - 1, 1}$。矩阵快速幂求出 $f_{n, 0 / 1}$，再根据 $s - nx$ 是否为 $k$ 的倍数计算答案。

当 $2\mid k$ 时，对每个 $s\in [0, k - 1]$，若 $2\nmid s$，则所有序列均不合法，否则恰存在两个 $x$ 使得 $2x \equiv s\pmod k$，记为 $x_1$ 和 $x_2$，则 $x_1 = \frac s 2$，$x_2 = \frac {s + k} 2 = x_1 + \frac k 2$。将 $a_i$ 减去 $x_1$，问题转化为：求 $\sum a_i\equiv s - nx_1$ 且包含 $0$ 或 $\frac k 2$ 的序列数量。补集转化，套用 E1 的 DP，可知对于 $i\geq 1$，$f_{i, 0} = f_{i, \frac k 2}$，且对于所有 $j\in [1, \frac k 2 - 1]\cup [\frac k 2 + 1, k - 1]$，$f_{i, j}$ 相等。有递推式 $f_{i, 0} = (k - 2) f_{i - 1, 1}$，$f_{i, 1} = 2f_{i - 1, 0} + (k - 4)f_{i - 1, 1}$。注意该递推式对于 $i = 1$ 不成立。同样可以矩阵快速幂解决。

时间复杂度 $\mathcal{O}(k + \log n)$。[代码](https://codeforces.com/contest/1808/submission/208250923)。

**三**

对于 $2\nmid k$，瓶颈在于计算 $s - nx\equiv 0\pmod k$ 的 $s$ 的数量。因为 $s = 2x$ 且 $s$ 和 $x$ 一一对应，所以相当于计算 $(n - 2)x\equiv 0\pmod k$ 的 $x$ 的数量。典中典，$x$ 必须是 $\frac {k} {\gcd(n - 2, k)}$ 的倍数，在 $[0, k)$ 里面恰有 $\gcd(n - 2, k)$ 个。

对于 $2\mid k$，瓶颈在于计算 $s - nx_1\equiv 0\pmod k$ 或 $s - nx_1 \equiv \frac k 2\pmod k$ 的 $s$ 的数量，即 $n - sx_1\equiv 0\pmod {\frac k 2}$。因为 $s = 2x_1$ 且 $s$ 和 $x_1$ 一一对应，所以相当于计算 $(n - 2)x_1\equiv 0 \pmod {\frac k 2}$ 的 $x$ 的数量。因为 $0\leq x_1 < \frac k 2$，所以类似地，$x_1$ 的数量为 $\frac {k / 2} {\gcd(n - 2, k / 2)}$。

时间复杂度 $\mathcal{O}(\log k + \log n)$。注意特判 $n = 1$。[代码](https://codeforces.com/contest/1808/submission/208253825)。

**四**

对于 $2\nmid k$，打表观察发现对于偶数 $i$ 有 $f_{i, 1} = f_{i, 0} - 1$，对于奇数 $i$ 有 $f_{i, 0} = f_{i, 1} + 1$，即 $f_{i, 1} = f_{i, 0} + (-1) ^ {i - 1}$，容易归纳证明。由此可知 $f_{n, 0} = vf_{n - 1, 1} = v(f_{n - 1, 0} + (-1) ^ {n - 1})$，即 $((((0 + 1) \cdot v - 1)\cdot v + 1) \cdot v - 1)\cdots v$，共乘以 $n - 1$ 个 $v$，其中 $v = k - 1$。将括号拆开，发现就是 $\sum_{i = 1} ^ {n - 1} (-1) ^ {i - 1} v ^ {n - i}$，变形得 $(-1) ^ {n - 1} \sum_{i = 1} ^ {n - 1} (-1) ^ {n - i} v ^ {n - i}$，等比数列求和得 $(-1) ^ {n - 1} \frac {(-v) ^ n - (-v) ^ 1} {-v - 1}$，即 $(-1) ^ n \frac {(1 - k) ^ n - (1 - k)}{k}$。设 $c = \gcd(n - 2, k)$，推式子：
$$
\begin{aligned}
\mathrm{illegal}
& = cf_{n, 0} + (k - c) f_{n, 1} \\
& = cf_{n, 0} + (k - c) (f_{n, 0} - (-1) ^ n) \\
& = kf_{n, 0} + (-1) ^ n (c - k) \\
& = (-1) ^ n ((1 - k) ^ n - (1 - k)) + (-1) ^ n(c - k) \\
& = (k - 1) ^ n + (-1) ^ n (c - 1)
\end{aligned}
$$
因此对于 $2\nmid k$，答案为 $k ^ n - (k - 1) ^ n + (-1) ^ n (\gcd(n - 2, k) - 1)$。

对于 $2\mid k$，打表观察发现有 $f_{i, 1} = f_{i, 0} + (-2) ^ {i - 1}$。一个感性理解：$2\mid k$ 的 DP 相当于两个规模为 $\frac k 2$ 的 $2\nmid k$ 的 DP（注意不是分成两个子问题，只是借用 DP 转移方式），而两个 DP 之间是对称的，产生双倍贡献。类似地，得到递推式 $f_{n, 0} = (k - 2) f_{n - 1, 0} = (k - 2)(f_{n - 1, 0} + (-2) ^ {n - 2})$。对比它和 $2\nmid k$ 的 DP 递推式 $f_{n, 0} = (k - 1)(f_{n - 1, 0} + (-1) ^ {n - 1})$，结合之前的感性理解，即做规模为 $\frac k 2$ 的 $2\nmid k$ 的 DP 且每次系数翻倍，考虑设 $g_{n, 0} = \frac {f_{n, 0}} {2 ^ {n - 1}}$，得 $g_{n, 0} = (\frac k 2 - 1)(g_{n - 1, 0} + (-1) ^ {n - 1})$。对于 $g_{n, 1}$ 类似，有 $f_{n, 1} = g_{n, 1}2 ^ {n - 1}$。所以，先做规模为 $\frac k 2$ 的 $2\nmid k$ 的 DP 得到 $g$，然后根据 $g$ 反推出 $f$：仅仅是将答案乘以 $2 ^ {n - 1}$。设 $k' = \frac k 2$，$c' = \gcd(n - 2, k')$：
$$
\begin{aligned}
\mathrm{illegal}
& = c'f_{n, 0} + (k' - c') f_{n, 1} \\
& = 2 ^ {n - 1} (c'g_{n, 0} + (k' - c') g_{n, 1}) \\
& = 2 ^ {n - 1} ((k' - 1) ^ n + (-1) ^ n (c' - 1))
\end{aligned}
$$
因此对于 $2\mid k$，答案为 $\frac {k ^ n} 2 - 2 ^ {n - 1}((\frac k 2 - 1) ^ n + (-1) ^ n (\gcd(n - 2, \frac k 2) - 1))$。

时间复杂度 $\mathcal{O}(\log k + \log n)$，但是封闭形式。[代码](https://codeforces.com/contest/1808/submission/208258810)。

**五**

不觉得打表找规律有点不牛吗？

设 $F_n$ 表示 $n$ 个 $[1, k)$ 之间的数之和为 $k$ 的倍数的方案数，则 $F_n = f_{n, 0}$。

考虑任意填 $a_1\sim a_{n - 1}$，最后用 $a_n$ 补成 $k$ 的倍数。发现当且仅当 $k\mid \sum a_{1\sim n - 1}$ 时不合法，得到递推式 $F_n = (k - 1) ^ {n - 1} - F_{n - 1}$。注意边界 $F_1 = 0$，这直接说明 $F_n = \sum_{i = 1} ^ {n - 1} (k - 1) ^ {n - i} (-1) ^ {i - 1}$。

对于 $f_{n, 1}$，推导是类似的。

**六**

除了上述做法外，还存在根据 “不能放 ……” 的限制二项式反演 + 推式子的做法。不过该做法比较平凡，就不赘述了。

---

## 作者：yukimianyan (赞：4)

## problem
一个长为 $n$ 的序列，每一个数是 $[0,k)$ 的整数。说一个数列幸运，当且仅当 $\exists i$ 使得 $a_i\equiv(\sum_j a_j)-a_i\pmod k$，求方案数，$n,k\leq 10^{18}$。

引理：若钦定数列的和为 $s$ ，则方案数为 $k^{n-1}$，注意 $n=0$ 特判。

显然题目条件可转化为：$\sum_j a_j\equiv 2 a_i\pmod k$

## solution when $k$ is odd
Let $\sum a_i=2s$，算出有至少一个 $s$ 的方案数：

$$\sum_{i=1}^n(-1)^{i+1}\binom{n}{i}k^{n-i-1}-\frac{(-1)^{n+1}}{k}+(-1)^{n+1}[ns\equiv 2s\pmod k].$$

$$-\frac{1}{k}(\boxed{\sum_{i=0}^n(-1)^i\binom{n}{i}k^{n-i}}-k^n)-\frac{(-1)^{n+1}}{k}+(-1)^{n+1}[ns\equiv 2s\pmod k].$$

$$k^{n-1}-\frac{(k-1)^n}{k}-\frac{(-1)^{n+1}}{k}+(-1)^{n+1}[ns\equiv 2s\pmod k].$$

枚举所有的 $s$，

$$ans=k^n-(k-1)^n+(-1)^n+(-1)^{n+1}\sum_{s=0}^{k-1}[ns\equiv 2s\pmod k].$$

$$ans=k^n-(k-1)^n+(-1)^n-(-1)^{n}\gcd(n-2,k).$$

## solution when $k$ is even
因为在这里 $i$ 和 $i+k/2$ 翻一倍是一样的，所以假如总和是 $s$，开始容斥：

$$ans=k^{n-1}-\left(
\sum_{0\leq a+b\leq n}(-1)^{a+b}\binom{n}{a,b,n-a-b}k^{n-a-b-1}-\sum_{a+b=n}(-1)^n\binom{n}{a}k^{-1}+(-1)^n\Delta
\right)$$

$\Delta$ 是正确的余项，我们等会再来；$\binom{n}{a,b,n-a-b}$ 是广义组合数，表示把 $n$ 划分为 $a,b,n-a-b$ 三个集合的方案数，它等于 $\frac{n!}{a!b!(n-a-b)!}$。

化简**括号内**除了 $\Delta$ 的部分：枚举 $a+b$，

$$\frac{1}{k}\left(\sum_{0\leq t\leq n}(-1)^tk^{n-t}\boxed{\frac{n!}{(n-t)!}}\sum_{a=0}^t\boxed{\frac{1}{a!(t-a)!}}-(-1)^n\boxed{\sum_{a=0}^n\binom{n}{a}}\right)$$

补全两个组合数，写二项式定理：

$$=\frac{1}{k}\left(\sum_{0\leq t\leq n}(-1)^tk^{n-t}\boxed{\frac{n!}{(n-t)!t!}}\sum_{a=0}^t\boxed{\frac{t!}{a!(t-a)!}}-2^n(-1)^n\right)$$

$$=\frac{1}{k}\left(\sum_{0\leq t\leq n}(-1)^tk^{n-t}\binom{n}{t}\boxed{\sum_{a=0}^t\binom{t}{a}}-2^n(-1)^n\right)$$

$$=\frac{1}{k}\left(\sum_{0\leq t\leq n}(-1)^tk^{n-t}\binom{n}{t}2^t-2^n(-1)^n\right)$$

$$=\frac{1}{k}\left(\boxed{\sum_{0\leq t\leq n}\binom{n}{t}(-2)^tk^{n-t}}-2^n(-1)^n\right)$$

$$=\frac{(k-2)^n-(-2)^n}{k}$$

所以答案

$$ans=k^{n-1}-\frac{(k-2)^n-(-2)^n}{k}-(-1)^n\Delta$$

现在想一下 $\Delta$：就是说 $i,i+k/2$ 填满了整个序列，总和又是 $2i$ 的方案数，

$$\Delta=[2i\equiv ni\pmod k]\sum_{a\text{是偶数}}^n\binom{n}{a}+[2i\equiv ni+k/2\pmod k]\sum_{a\text{是奇数}}^n\binom{n}{a}=2^{n-1}([2i\equiv ni\pmod k]+[2i\equiv ni+k/2\pmod k])$$

注意到若设 $m=n-2$ 则相当于求 $[mi\equiv 0\pmod k]+[mi\equiv k/2\pmod k]$，除非 $k=0$ 否则这两个只能成立一个，所以这相当于：

$$[mi\equiv 0\pmod{k/2}]$$

注意到这样做连上下界都调好了

所以

$$total=\frac{k^n-(k-2)^n+(-2)^n}{2}+(-2)^{n-1}\gcd(n-2,k/2)$$

## 回顾与反思
### 二项式定理
$$\sum_{i=0}^n\binom{n}{i}a^ib^{n-i}=(a+b)^n.$$

$$\Rightarrow\sum_{i=0}^n\binom{n}{i}(-1)^ik^{n-i}=(k-1)^n.$$

$$\Rightarrow\sum_{a=0}^t\binom{t}{a}=2^n.$$

$$\Rightarrow\sum_{a \text{是奇数}}^t\binom{t}{a}=\sum_{a \text{是偶数}}^t\binom{t}{a}=2^{n-1}.$$

### 组合数
$$\binom{n}{m}=\frac{n!}{m!(n-m)!}$$

$$\Rightarrow \binom{n}{a,b,n-a-b}=\binom{n}{a}\binom{n-a}{b}\binom{n-a-b}{n-a-b}=\frac{n!}{a!b!(n-a-b)!}$$

### 数论
关于 $i$ 的同余方程，$mi\equiv 0\pmod k$ 在 $[0,k)$ 内有 $\gcd(m,k)$ 个解。

证明：$\Rightarrow \frac{m}{d}i\equiv0\pmod{k/d}$（$d=\gcd(m,k)$），此时等式两边同时乘上 $\frac{m}{d}$ 的乘法逆元，得到了原方程的所有解是 $i\equiv 0\pmod{k/d}$。

所以一共有 $\frac{k}{k/d}=\gcd(m,k)$ 个解，且都是 $\frac{k}{\gcd(m,k)}$ 的倍数。

---

## 作者：Gorenstein (赞：3)

一个数竞神仙的做法，很厉害，详细解释一下。

题意即求存在 $i$ 使得 $x_1+\cdots+x_n\equiv2x_i\pmod k$ 的序列数量，亦即 $x_i\equiv\dfrac{x_1+\cdots+x_n}{2}\pmod k$。对于一个序列，取其最小的符合条件的 $i$ 作为代表。记 $A_i$ 为满足 $2x_i\equiv S\pmod k$ 且 $\forall j<i,2x_j\not\equiv S\pmod k$ 的序列数量，则我们只需求 $A_1+\cdots+A_n$。

下面以 $2\nmid k$ 为例介绍该做法。

对于 $i<n$ 的 $A_i$，$x_i$ 有 $k$ 种取值；由于我们钦定 $j<i$ 的 $x_j$ 皆不满足条件，故 $x_1$ 到 $x_{i-1}$ 这些数各个都有 $k-1$ 种取值；$x_{i+1}$ 到 $x_{n-1}$ 可任取，$x_n$ 总有唯一的数使得整个序列符合条件。因此若 $i<n$，则 $A_i=(k-1)^{i-1}k^{n-i}$。

着重讨论 $A_n$。此时由于 $x_n$ 被占位，故不同于前述 $i<n$ 时的情形。此时我们须求 $x_1+\cdots+x_{n-1}=x_n\pmod k$ 的序列数量，其中 $x_i\neq x_n\;(i\neq n)$。设 $x_n=t$，考察每一个 $t\in[0,k)$。

经典地，同余式左侧的生成函数为：

$$
F(z)=\left(\sum_{0\leqslant i<k,i\neq t}z^{i}\right)^{n-1}
$$

我们只须求同余 $t$ 次项的系数。进一步转化：

$$
\begin{aligned}
A_{n,t}=\sum_{k\mid(d-t)}\left[z^d\right]\!F(z)=\sum_{k\mid d}\left[z^d\right]\!z^{k-t}F(z)
\end{aligned}
$$

设 $\omega_n$ 为 $n$ 次单位根，我们知道：

$$
\sum_{k=0}^{n-1}\omega_n^{kl}=\begin{cases}
n,&n\mid l\\0,&n\nmid l
\end{cases}
$$

故令 $G(z)=z^{k-t}F(z)$，将 $k$ 次单位根代入 $G(z)$，算得：

$$
\begin{aligned}
A_{n,t}&=\frac{1}{k}\sum_{i}G\!\left(\omega^{i}\right)\\
&=\frac{1}{k}\sum_i\omega^{i(k-t)}\left(\sum_{j\neq t}\omega^{ij}\right)^{n-1}\\
&=\frac{1}{k}\sum_i\omega^{-it}(-\omega^{t})^{n-1}\\
&=\frac{(-1)^{n-1}}{k}\sum_i\omega^{it(n-2)}
\end{aligned}
$$

据此便可求出 $A_n$：

$$
\begin{aligned}
A_n&=\sum_{t}\frac{(-1)^{n-1}}{k}\sum_i\omega^{it(n-2)}\\
&=(-1)^{n-1}\frac{1}{k}\sum_{i=1}^{k-1}\sum_{t=0}^{k-1}\omega_k^{it(n-2)}\\
&=(-1)^{n-1}\sum_{i=1}^{k-1}\big[k\mid i(n-2)\big]\\
&=(-1)^{n-1}(\gcd(k,n-2)-1)
\end{aligned}
$$

从而最终答案为：

$$
\begin{aligned}
\sum_{i=1}^nA_{i}&=A_n+\sum_{i=1}^n(k-1)^{i-1}k^{n-i}\\
&=A_n+k^{n-1}\sum_{i=0}^{n-1}\left(\frac{k-1}{k}\right)^i\\
&=A_n+k^n-(k-1)^n\\
&=k^n-k^{n-1}+(-1)^{n-1}(\gcd(k,n-2)-1)
\end{aligned}
$$

$2\mid k$ 与 $2\nmid k$ 的做法完全类似。着重考察 $A_n$ 的情形，枚举 $t$，此时的 OGF 为：

$$
F(z)=\left(\sum_{0\leqslant i<k}[i\neq t]\left[i \neq t{+}\tfrac{k}{2}\right]z^{i}\right)^{n-1}
$$

此后的步骤与 $2\mid k$ 相同。可得最终答案为：

$$
\frac{k^n}{2}-2^{n-1}\left(\left(\frac{k}{2}-1\right)^n-(-1)^{n-1}\left(\gcd\left(\frac{k}{2},n-2\right)-1\right)\right)
$$

---

## 作者：SDSXC (赞：1)

无脑矩阵做法。

第一步 $O(k^4 \log n)$

假设这个数是$a_{n-1}a_{n-2}\dots a_0$，令 $sum=\sum\limits_{i=0}^{n-1}a_i$，那么约束转化为存在一个 $x$ 使得 $a_x\equiv sum-a_x (\bmod k)$，移项，变为 $2a_x\equiv sum (\bmod k)$。存在性问题比较难统计，我们考虑正难则反，计算不存在的个数。

那么我们考虑枚举 $sum\bmod k$，然后要求每一位都不满足 $2a_i\equiv sum\bmod k$，这个东西显然是可以 $O(k^3\log n)$ 的矩阵快速幂计算的，然后再算上枚举 $sum$ 的复杂度，总体上是 $O(k^4\log n)$，显然无法通过。

第二步 $O(k^3 \log n)$

我们注意到矩阵快速幂的矩阵是一个循环矩阵，利用循环矩阵乘循环矩阵还是循环矩阵的性质，我们矩阵乘法的时候只需要乘出一行即可，成功优化到了 $O(k^3 \log n)$

第三步 $O(k^2\log n)$

我们在注意到，改变 $sum$ 的时候的矩阵其实变化不大，每次都乘实在太浪费了。

对于 $k$ 是奇数的时候，此时 $2x\equiv sum(\bmod k)$ 只有唯一解，此时每次的矩阵就是 $A=([i!=j])_{k\times k}$ 右移 $x$ 次（右移定义为最右侧一列移到第零列，其他的右移一列）。然后我们不难发现它的 $n$ 次方就是 $A^n$ 右移 $nx$ 次。这一点从它的数论含义或者循环矩阵的性质都不难证明。

对于 $k$ 是偶数的时候，如果 $sum$ 是偶数，那么$2x\equiv sum(\bmod k)$ 有两个相差为 $\frac{k}{2}$ 的解，我们同上的处理它。如果 $sum$ 是奇数，那么不难发现原矩阵就是每项都是 $1$，答案就是 $k^{n-1}$。

这样时间复杂度就优化到了 $O(k^2\log n)$，足以通过。

代码，实现的比较垃圾，常数很大，但是能过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2009
using namespace std;
ll mul(ll a,ll b,ll p){
	ll c=(long double)a/p*b;
	ll ret=(unsigned long long)a*b-(unsigned long long)c*p;
	return (ret+p)%p;
}
ll n;
int k;
ll p;
struct cycmat{
	ll a[N];
	void init(){memset(a,0,sizeof(a));}
	cycmat operator*(const cycmat &b){
		cycmat ret;ret.init();
		for(int i=0;i<k;i++){
			for(int j=0,u=i;j<k;j++){
				ret.a[u]+=a[i]*b.a[j]%p;
				u++;if(u==k) u-=k;
			}
		}
		for(int i=0;i<k;i++) ret.a[i]%=p;
		return ret;
	}
};
cycmat qpow(cycmat x,ll y){
	if(y==1) return x;
	cycmat tmp=qpow(x,y>>1);
	if(y&1) return tmp*tmp*x;
	else return tmp*tmp;
}
ll qpow(ll x,ll y){
	if(!y) return 1ll;
	ll tmp=qpow(x,y>>1);
	if(y&1) return tmp*tmp%p*x%p;
	else return tmp*tmp%p;
}
cycmat a,b;
ll ans=0;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k>>p;
	if(k&1){
		for(int i=1;i<k;i++)a.a[i]=1;
		a=qpow(a,n);
		for(int i=0;i<k;i++){
			ll x=i*2%k,y=mul(n,i,k);
			ans+=a.a[(x-y+k)%k];
		}
	}
	else{
		for(int i=0;i<k;i++) a.a[i]=1;
		a.a[0]=a.a[k/2]=0;
		a=qpow(a,n);
		for(int i=0;i<(k>>1);i++){
			ll x=i*2,y=mul(n,i,k);
			ans+=a.a[(x-y+k)%k];
		}
		ans+=(k>>1)*qpow(k,n-1);
	}
	ans=(qpow(k,n)-ans%p+p)%p;
	cout<<ans;
	return 0;
}
```

---

## 作者：_abcd_ (赞：1)

[[CF1808E3] Minibuses on Venus](https://codeforces.com/problemset/problem/1808/E3)

为方便起见，令原文的 $k \to m$，原文的 $m \to p$。

设 $\sum\limits_{i=1}^n a_i - a_{k1} \equiv a_{k1} \pmod m$，且 $\sum\limits_{i=1}^n a_i - a_{k2} \equiv a_{k2} \pmod m$，那么将两式相减有 $2 a_{k1} \equiv 2 a_{k2} \pmod m$。

分成两类讨论，若 $m$ 为奇数，则有 $a_{k1} = a_{k2}$，不妨枚举 $i$，使得 $i$ 为最大的数，使得 $\sum\limits_{j=1}^n a_j - a_i \equiv a_i$。那么需要算出两种值，$f_{i,j}$ 为有多少个 $i$ 位数，使得各位数的和为 $j$。$g_{i,j,k}$ 为有多少个 $i$ 位数，其中不包含数字 $k$，且各位数的和为 $j$。

对于 $f_{i,j}$，我们随意填 $1 \sim i-1$ 位，然后根据前 $i-1$ 位的和填出第 $i$ 位，因此有 $f_{i,j} = m^{i-1}$。

对于 $g_{i,j,k}$，设多项式 $F = \sum\limits_{i=0}^{m-1} x^i - x^k$，则 $g_{i,j,k} = [x^j] F^i$。注意，这里的多项式乘法为循环卷积，这样有 $[x^j] F^i = \sum\limits_{l=0}^{m-1} [x^l] F^{i-1} - [x^{j-k \bmod m}] F^{i-1}$，这样仔细推一下或者打个表就会发现 $g_{i,j,k} = h_i - (-1)^{i-1} [ik \equiv j \pmod m]$，其中序列 $h$ 满足递推式 $h_i = (m-1) h_{i-1} + (-1)^{i-1}$，因此
$$H = (m-1)x H + \frac{x}{1+x}$$
$$H = \frac{x}{(1+x)(1-(m-1)x)}$$
设
$$H = \frac{a}{1+x} + \frac{b}{1-(m-1)x}$$
$$ = \frac{a-a(m-1)x+b+bx}{(1+x)(1-(m-1)x)}$$
因此有
$$a+b = 0,b-a(m-1) = 1$$
解得
$$a = -\frac{1}{m}, b = \frac{1}{m}$$
所以
$$H = \frac{-\frac{1}{m}}{1+x} + \frac{\frac {1}{m}}{1-(m-1)x}$$
$$ = \sum\limits_{i=0} \frac {(m-1)^i - (-1)^i}{m} x^i$$
因此
$$h_i = \frac {(m-1)^i - (-1)^i}{m}$$
那么，我们已经算出了 $f_{i,j}$ 和 $g_{i,j,k}$，就有答案为
$$\sum\limits_{i=2}^{n} \sum\limits_{j=0}^{m-1} \sum\limits_{k=0}^{m-1} f_{i-1,j-k \bmod m} g_{n-i,k,j} + \sum\limits_{i=0}^{m-1} f_{0,0} g_{n-1,j,j}$$
$$ = \sum\limits_{i=2}^n \sum\limits_{j=0}^{m-1} \sum\limits_{k=0}^{m-1} m^{i-2} (\frac {(m-1)^{n-i} - (-1)^{n-i}}{m} - (-1)^{n-i-1} [j(n-i) \equiv k]) + \sum\limits_{i=0}^{m-1} \frac {(m-1)^{n-1} - (-1)^{n-1}}{m} - (-1)^{n-2}[i(n-1) \equiv i]$$
不难发现满足 $j(n-i) \equiv k$ 的 $k$ 只有一个，因此
$$\sum\limits_{i=2}^n \sum\limits_{j=0}^{m-1} \sum\limits_{k=0}^{m-1} m^{i-2} (\frac {(m-1)^{n-i} - (-1)^{n-i}}{m} - (-1)^{n-i-1} [j(n-i) \equiv k]) $$
$$ = \sum\limits_{i=2}^n \sum\limits_{j=0}^{m-1} m^{i-2}(m \frac {(m-1)^{n-i} - (-1)^{n-i}}{m} - (-1)^{n-i-1})$$
$$ = \sum\limits_{i=2}^n \sum\limits_{j=0}^{m-1} m^{i-2} (m-1)^{n-i}$$
$$ = \sum\limits_{i=2}^n m^{i-1}(m-1)^{n-i}$$
$$ = \sum\limits_{i=0}^{n-2} m^{i+1} (m-1)^{n-i-2}$$
$$ = m^{n-1} \sum\limits_{i=0}^{n-2} (\frac {m-1}{m})^{n-2-i}$$
$$ = m^{n-1} \frac {1 - (\frac {m-1}{m})^{n-1}}{1 - \frac {m-1}{m}}$$
$$ = m^n (1 - (\frac {m-1}{m})^{n-1})$$
而
$$\sum\limits_{i=0}^{m-1} f_{0,0} g_{n-1,j,j} = \sum\limits_{i=0}^{m-1} \frac {(m-1)^{n-1} - (-1)^{n-1}}{m} - (-1)^{n-2} [i(n-1) \equiv i]$$
$$ = (m-1)^{n-1} - (-1)^{n-1} - (-1)^{n-2} \sum\limits_{i=0}^{m-1} [i(n-2) \equiv 0]$$
对于 $[i(n-2) \equiv 0]$，等同于 $i(n-2)$ 为 $m$ 的倍数，即 $i$ 为 $\frac {m}{\gcd(m,n-2)}$ 的倍数，因此有
$$\text{上式} = (m-1)^{n-1} - (-1)^{n-1} - (-1)^{n-2} \gcd(m,n-2)$$
所以答案为
$$m^n (1 - (\frac {m-1}{m})^{n-1}) + (m-1)^{n-1} - (-1)^{n-1} - (-1)^{n-2} \gcd(m,n-2)$$
若 $m$ 为偶数，有 $k_1 \equiv k_2 \pmod {\frac{m}{2}}$，通过类似的推导，就能得出答案为
$$\frac {m^n (1 - (\frac {m-2}{m})^{n-1})}{2} + (m-2)^{n-1} - (-2)^{n-1} - 2 \times (-2)^{n-2} \gcd(m/2,n-2)$$
复杂度为 $O(\log n + \log m + \log p)$

---

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define maxn 2005
#define int ll
using namespace std;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*t;
}
int n,m,mod,ans;
int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    n=re(),m=re(),mod=re();
    if(n==1)
        return puts("1"),0;
    if(m&1)
    {
        ans=ksm(m,n)*(1-ksm((m-1)*ksm(m,mod-2)%mod,n-1)+mod)%mod;
        ans=(ans+ksm(m-1,n-1)-ksm(mod-1,n-1)+mod)%mod;
        ans=(ans-__gcd(m,n-2)*ksm(mod-1,n-2)%mod+mod)%mod;
    }
    else
    {
        ans=ksm(m,n)*(1-ksm((m-2)*ksm(m,mod-2)%mod,n-1)+mod)%mod*ksm(2,mod-2)%mod;
        ans=(ans+ksm(m-2,n-1)-ksm(mod-2,n-1)+mod)%mod;
        ans=(ans-2*__gcd(m/2,n-2)*ksm(mod-2,n-2)%mod+mod)%mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：masonpop (赞：1)

$n$ 的范围这么大，dp 肯定不行了，考虑直接组合计数。

仍然考虑反面，即 $2a_i\not\equiv S\pmod k$。

先枚举 $S$，根据 $k$ 的奇偶性分类讨论：

① $k\equiv 1 \pmod 2$。

此时，不满足上述那个同余方程的数只有一个并且可以解出来，记为 $t$。显然可以容斥了。设 $f(i)$ 表示**钦定** $i$ 个位置的值为 $t$ 的方案数，$g(i)$ 表示**恰好** $i$ 个位置的值为 $t$ 的方案数。则 $f(i)=\sum\limits_{j=i}^nC_j^ig(j)$。我们要求 $g(0)$。

直接二项式反演得到 $g(i)=\sum\limits_{j=i}^n(-1)^{j-i}C_j^if(j)$。带入 $i=0$ 即得 $g(0)=\sum\limits_{i=0}^n(-1)^if(i)$。

再考虑直接计算 $f(i)$。当 $i=n$ 时 $f(i)=[nt\equiv S \pmod k]$，否则容易发现，剩余的 $n-i$ 个位置中的 $n-i-1$ 个位置可以随便选，而由于和一定因此最后一个位置可以自动确定。因此，$f(i)=C_n^ik^{n-1-i}$。

由于 $i=n$ 的情况略有不同，因此将其分离出来。带入：

$g(0)=\sum\limits_{i=0}^{n-1}(-1)^iC_n^ik^{n-1-i}+(-1)^nf(n)$。

左边那个式子是个类似二项式定理的形式。将其分离一下略作调整即可化简为如下形式：

$g(0)=\frac{(k-1)^n-(-1)^n}{k}+(-1)^nf(n)$。

注意到这个是建立在枚举 $S$ 的基础上的，所以将 $f(n)$ 写为 $f_{S}(n)$。将其对 $0\le S\le k-1$ 累加求和即可得到这部分的答案为 $(k-1)^n-(-1)^n+(-1)^n\sum\limits_{i=0}^{k-1}f_i(n)$。再利用 $t$ 的定义即可得到 $f_i(n)=[(n-2)i\equiv 0 \pmod k]$。这样的 $i$ 显然有 $\gcd(n-2,k)$ 个。

带入，并注意这是反面情况，即可得到这部分的答案为 $k^n-(k-1)^n+(-1)^n-(-1)^n\gcd(n-2,k)$。

② $k\equiv 0\pmod 2$

此时发现，当 $S$ 为奇数时显然无解。考虑统计 $S$ 为偶数且不包含满足 $2a_i\equiv 0\pmod k$ 的 $a_i$ 的方案。

和上一种情况不同的是，此时不满足条件的数有两个，记为 $t_1,t_2$。且可以解出这两个值，分别为 $\frac{S}{2},\frac{S+k}{2}$。

仍然容斥。设 $f(i)$ 表示**钦定** $i$ 个值为 $t_1$ 或 $t_2$ 的方案数。$g(i)$ 表示恰好 $i$ 个值为 $t_1$ 或 $t_2$。所求即为 $g(0)$。

显然 $f(i)=\sum\limits_{j=i}^nC_j^ig(j)$。二项式反演得到 $g(i)=\sum\limits_{j=i}^nC_j^i(-1)^{j-i}f(j)$。带入得到 $g(0)=\sum\limits_{i=0}^n(-1)^if(i)$。

考虑计算 $f(i)$。当 $i\ne n$ 时，可得 $f(i)=C_n^i2^ik^{n-1-i}$。否则记为 $f_S(n)$，稍后处理。

类似于上面的情况，对偶数 $S$ 累加求和即得

$\frac{(k-2)^n-(-2)^n}{2}+(-1)^n\sum\limits_{S=2t,0\le 2t<k}f_S(n)$

考虑计算 $f_S(n)$。枚举其中有 $j$ 个 $t_1$，$n-j$ 个 $t_2$。则 $f_S(n)=\sum\limits_{j=0}^nC_n^j[jt_1+(n-j)t_2\equiv0\pmod k]$

代入 $t_1,t_2$ 表达式，化简为：

$f_S(n)=\sum\limits_{j=0}^nC_n^j[\frac{k}{2}j\equiv \frac{S+k}{2}n-S\pmod k]$

注意到，$\frac{k}{2}j$ 模 $k$ 的值只可能为 $0$ 或 $\frac{k}{2}$，而右边是定值。发现无论是哪种情况，都是组合数上指标的交换求和，其值均为 $2^{n-1}$。

而 $\frac{S+k}{2}n-S\equiv 0\pmod \frac{k}{2}$。因此有 $\frac{S}{2}(n-2)\equiv 0\pmod \frac{k}{2}$。这种式子再熟悉不过了，满足条件的 $S$ 有 $\gcd(n-2,\frac{k}{2})$ 个。

综上，我们得到：$\sum\limits_{S=2t,0\le 2t<k}f_S(n)=2^{n-1}\gcd(n-2,\frac{k}{2})$。

同样注意这是反面情况。整理可得这部分的答案为

$\frac{k^n-(k-2)^n+(-2)^n}{2}-(-1)^n2^{n-1}\gcd(n-2,\frac{k}{2})$

时间复杂度为 $O(\log n+\log k)$。注意 $2$ 关于模数的逆元有可能不存在，需要通过微操避免除法。（具体的，就是把一个 $k$ 拆开除以 $2$）。[代码](https://codeforces.com/contest/1808/submission/220091882)。

---

## 作者：daniEl_lElE (赞：1)

很好玩的一个题。

## 思路

### 思路一

首先形式化一下题面

> 求所有数组 $\{a_1,a_2,\dots,a_n\}$ 使得对于所有 $1\leq i\leq n$，$0\leq a_i<k$ 且存在 $1\leq i\leq n$ 使得 $2a_i\equiv\sum_{i=1}^na_i(\bmod\ k)$。

考虑分类讨论。

$k$ 为奇数时，存在 $k$ 组 $2b\equiv c(\bmod\ k)$，于是我们可以枚举 $c=\sum_{i=1}^na_i$，然后计算 $a_i\not=b$ 的方案数，用总方案数减去即可。如何计算？考虑 $dp_{i,j,b}$ 表示看到第 $i$ 位，$\sum_{i=1}^n$ 在模 $k$ 意义下为 $j$，钦定 $a_i\not=b$ 的方案数，转移时枚举 $a_i$ 的值即可。

$k$ 偶数时，唯一不同的是对于每个偶数 $c<k$ 均有两个 $b_1,b_2$ 使得 $2b_i\equiv c(\bmod\ k)$，实则同理，考虑 $dp_{i,j,b_1,b_2}$ 类似奇数情况即可。不难发现 $b_1,b_2$ 成对出现一共有 $\dfrac{k}{2}$ 对，所以完全可以压到一个 $O(k)$ 的维度。你压不压都能过 E1 题。

### 思路二

考虑优化，考虑生成函数，记 $g(i)$ 的第 $j$ 项为在钦定好上一个思路的 $b(b_1,b_2)$ 后选到 $a_i$，模 $k$ 为 $j$ 的方案数。考虑每次选择的 $a_i$，也可以表示为 $h=\sum_{i=0}^{k-1}x^i-x^{b}$（奇数的情况后面扣减部分为 $(x^{b_1}+x^{b_2})$）。也就是说 $g(i)=h^i$。$O(k)$ 枚举钦定的 $b$，后面可以 $O(k^2\log n)$ 使用矩阵快速幂优化解决。综复杂度 $O(k^3\log n)$，可以通过 E2。

### 思路三

考虑继续优化，（以奇数情况为例），我们想要重复利用钦定好某一个 $b$ 的 $g(n)$。不难发现由于是在取模意义下，当 $b$ 增加 $1$ 时，可以理解成将原来的每种方案的 $a_i$ 增加 $1$，总和增加 $n$，由此我们可以发现 $b$ 增加 $1$ 时，$g(i)$ 变为 $x^ng(i)\bmod x^k$。这时我们可以仅计算对于一个 $b$ 时的答案。由于偶数的情况 $b_1,b_2$ 会同时加减，所以也可以使用类似方法。总复杂度 $O(k^2\log n)$，可以通过 E3。

### 思路四

手模发现，我们的 $g(i)$ 有众多同样的项。（以奇数情况为例）$g(i)=1(x^0+x^1+\dots+x^{k-2})+0(x^{k-1})$，$g^2(i)=(k-2)(x^0+x^1+\dots+x^{k-3}+x^{k-1})+(k-1)(x^{k-2})$ 等。

证明的话可以使用归纳法，归纳 $g^d(i)$ 只有 $x^{(k-d)\bmod k}$ 一项系数不同，设分别系数为 $a,b$，不难推出 $g^{d+1}(i)$ 的每一项的系数，发现除了 $x^{(k-d)\bmod k}$ 的系数均相等即可。同时可以得到转移系数。

当只有两项时，我们可以分别算出转移系数矩阵快速幂，后续操作同思路三，总复杂度 $O(\log n+k)$。

对于偶数的情况读者可以手模，同样有该性质，区别在于有两项系数是不同的，且这两项同样按顺序位移。

## 代码

以下为思路三的实现代码：

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"inline","Ofast") 
#define int __int128
using namespace std;
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
int mod;
int pw(int a,int b){
    int ans=1;
    while(b){
        if(b&1) (ans*=a)%=mod;
        (a*=a)%=mod;
        b>>=1;
    }
    return ans;
}
int k;
struct node{
	int a[2005];	
}ept;
int add[2005][2005];
node mul(node x,node y){
	node z=ept;
	for(int i=0;i<k;++i) for(int j=0;j<k;++j) z.a[add[i][j]]+=x.a[i]*y.a[j];
	for(int i=0;i<k;++i) z.a[i]%=mod;
	return z;
}
node qp(node a,int b){
	node ans; for(int i=0;i<k;i++) ans.a[i]=0; ans.a[0]=1;
	while(b){
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
signed main(){
	int n,ans=0; n=read(),k=read(),mod=read();
	for(int i=0;i<2000;i++) for(int j=0;j<2000;j++) add[i][j]=(i+j)%k;
	node g; for(int i=0;i<k;i++) g.a[i]=pw(k,n-1);
	if(k&1){
		node h; for(int i=0;i<k-1;i++) h.a[i]=1; h.a[k-1]=0;
		h=qp(h,n);
		for(int i=0;i<k;i++){
			int aim=i*2%k;
			aim=(aim-(i+1)*(n%k)%k+k)%k;
			(ans+=g.a[i*2%k]+mod-h.a[aim])%=mod;
		}
	}
	else{
		node h;
		for(int i=0;i<k/2-1;i++) h.a[i]=1; h.a[k/2-1]=0;
		for(int i=k/2;i<k-1;i++) h.a[i]=1; h.a[k-1]=0;
		h=qp(h,n);
		for(int i=0;i<k/2;i++){
			int aim=i*2%k;
			aim=(aim-(i+1)*(n%k)%k+k)%k;
			(ans+=mod-h.a[aim])%=mod;
			(ans+=g.a[i*2%k])%=mod;
		}
	}
	print(ans);
    return 0;
}
```

---

## 作者：Mashu77 (赞：0)

条件等价于存在某一位 
$x$，满足 
$2
x
≡
s
(
\bmod ~
k
)$。容易想到一个 
$O
(
n
k^
3
)$
 的数位 
DP
 做法，即钦定 
$s$，然后计数不存在 
$x$
 的方案数。但 
$n$
 和 
$k$
 的范围都很大，用矩阵快速幂等方式优化没有前途。考虑组合计数。

如果 
$k$
 为奇数，则 
$x$
 与 
$s$
 是一一对应的。先考虑这种情况。

每一位都可以取 
$[
0
,
k
)$
 中任意一个数，这产生了一个很好的性质：如果一位一位填数，最后一位可以将任意 
$s$
 变为任意想要的结果。

这启发我们使用二项式反演。先钦定 
$s$。设 
$f_
i$
 表示有恰好 
$i$
 位为 
$x$
 的方案数，
$g_
i$
 表示钦定 
$i$
 位为 
$x$，剩下随意放的方案数。则易得

$$g_i=\left\{ \begin{array}{rcl}
C^i_nk^{n-i-1} &(i<n)\\
[nx\equiv s] & (i=n)
\end{array}\right.\\ f_i=\sum^n_{j=i}(-1)^{j-i}C_j^ig_j)
$$
我们要对所有 
$s$，求 
$f_
0$
 之和，最后用总方案数减去即为答案。因为 
$g_
n$
 特殊，所以提出来单独考虑。稍微化一下

$$ f_0=\sum^{n-1}_{i=0}(-1)^iC^i_nk^{n-i-1}+(-1)^ng_n
\\
=\sum^n_{i=0}(-1)^iC^i_nk^{n-i-1}-(-1)^nk^{-1}+(-1)^ng_n\\=k^{-1}(\sum^n_{i=0}(-1)^{n-i}C^n_ik^i-(-1)^n)+(-1)^ng_n$$
上式中的 
$k^
i$
 很适合二项式反演。反演得

$$f_0=
k^
{−
1}
(
(
k
−
1
)^
n
−
(
−
1
)^
n
)
+
(
−
1
)^
n
g_
n$$
完成。预处理后复杂度 
$O
(
\log
n
+
k
)$。

还有一部分是 
$k$
 为偶数的情况。此时 
$s$
 为奇数显然没有方案，偶数则有两个 
$x$
 与之对应。则改写上式为

$$\displaystyle g_i=\left\{ \begin{array}{rcl}
C^i_n2^ik^{n-i-1} & (i<n)\\ \sum^n_{j=0}C^j_n[jx_1+(n-j)x_2\equiv s] & (i=n)
\end{array}\right.$$
小于 
$n$
 的部分如上化简即可。接下来考虑如何快速求 
$g_
n$。

因为 
$x_1=\dfrac{s+k}{2},x_2=
\dfrac{s}{
2}$，所以化为 
$j
(
x_
1
−
x_
2
)
≡
s
−
n
x_
2$，即 $j
⋅
\dfrac{k}{
2}
≡
s
−
n
x_
2
(
\bmod
~k
)$。右边为定值。左边只和 
$j$
 的奇偶性有关。

因为  
$\displaystyle \sum_{i\equiv0\bmod 2}C^i_n=\sum_{i\equiv\bmod2}C^i_n=2^{n-1}$，所以 
$g_n=2^{n−1}[(s−nx_2≡0)∨(s−nx_2≡\dfrac{k}{2})]$。
于是此题得解。

---

