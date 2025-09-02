# Minibuses on Venus (medium version)

## 题目描述

This is the medium version of the problem. The only difference between the three versions is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

Maxim is a minibus driver on Venus.

To ride on Maxim's minibus, you need a ticket. Each ticket has a number consisting of $ n $ digits. However, as we know, the residents of Venus use a numeral system with base $ k $ , rather than the decimal system. Therefore, the ticket number can be considered as a sequence of $ n $ integers from $ 0 $ to $ k-1 $ , inclusive.

The residents of Venus consider a ticket to be lucky if there is a digit on it that is equal to the sum of the remaining digits, modulo $ k $ . For example, if $ k=10 $ , then the ticket $ 7135 $ is lucky because $ 7 + 1 + 5 \equiv 3 \pmod{10} $ . On the other hand, the ticket $ 7136 $ is not lucky because no digit is equal to the sum of the others modulo $ 10 $ .

Once, while on a trip, Maxim wondered: how many lucky tickets exist? At the same time, Maxim understands that this number can be very large, so he is interested only in the answer modulo some prime number $ m $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808E2/2314a7c75bce1209ddf61a583b83dbea8efe39a0.png)

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

## 作者：ღꦿ࿐ (赞：7)

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

## 作者：Engulf (赞：3)

首先，请先解决问题的简单版本，或阅读简单版本[题解](https://www.luogu.com.cn/article/hn4azcyc)中的**方法一**了解基本的 dp 思路。

这个 dp 可以用矩阵快速幂进行优化。

定义转移矩阵 $A$，其中 $A_{i, (i + j) \bmod k} = [2j \neq S (\bmod k)]$。

所以就有

$$[f_{i, 0}, f_{i, 1}, \cdots, f_{i, k - 1}] \times A = [f_{i + 1, 0}, f_{i + 1, 1}, \cdots, f_{i + 1, k - 1}]$$

令 $f_0 = [1, 0, 0, \cdots, 0]$，答案就是 $f_0 \times A^n$ 的第 $S$ 项。

枚举 $S$，再按上面的方法容斥计算，矩阵快速幂 $O(k^3\log n)$，再加上枚举 $S$，复杂度 $O(k^4\log n)$，无法通过本题。[代码](https://www.luogu.com.cn/paste/41z4rpeg)。

然后就要引入一个新的优化 dp 的科技，好像是叫作循环卷积。

考虑定义多项式 $g_i = a_{i, 0}x^0 + a_{i, 1}x^1 + \cdots + a_{i, k - 1}x^{k - 1}$，系数 $a_{i, j}$ 表示的就是 dp 中的 $f_{i, j}$。

定义转移多项式 $A$，其中 $i$ 次项系数 $a_i = [2i \neq S (\bmod k)]$。

然后就有 $g_i \times A = g_{i + 1}$。

但这里的多项式乘法有些许区别，就是指数要对 $k$ 取模。

这个也是可以快速幂加速的，答案就是 $g_0 \times A^n$ 的第 $S$ 项。

多项式乘法的时间复杂度是 $O(k^2)$，如果你会 FFT 的话就更好了，变成 $O(k \log k)$，但对于本题没有必要。所以时间复杂度是 $O(k^3 \log n)$，可以通过本题。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int K = 105;

ll n;
int k, mod;

int qpow(int a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

vector<int> operator*(const vector<int> &a, const vector<int> &b) {
    vector<int> c(k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            c[(i + j) % k] = (c[(i + j) % k] + 1ll * a[i] * b[j]) % mod;
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> mod;

    int ans = qpow(k, n);
    for (int s = 0; s < k; s++) {
        vector<int> A(k);
        for (int i = 0; i < k; i++) A[i] = 2 * i % k != s % k;
        vector<int> f(k);
        f[0] = 1;
        ll nn = n;
        while (nn) {
            if (nn & 1) f = f * A;
            A = A * A;
            nn >>= 1;
        }
        ans = (ans - f[s] + mod) % mod;
    }

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：masonpop (赞：3)

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

