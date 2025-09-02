# 「ZHQOI R1」幂和

## 题目描述

给定 $n,x,k$，求下列式子的值：
$$
\sum_{i=0}^n (-1)^{\operatorname{popcnt}(i)} (i+x)^k
$$
答案对 $998244353$ 取模。

特殊地，定义 $0^0=1$。

函数 $\operatorname{popcnt}(x)$ 表示 $x$ 在二进制表示下 $1$ 的个数。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据：$0\le n\le 10^{12},0\le x\le 10^9,0\le k\le 10^5$。

| 子任务编号 | $n\le $        | $k\le $ | 分数 |
| :----------: | :--------------: | :-------: | :----: |
| 1          | $10^6$         | $10^5$  | $7$  |
| 2          | $10^8$ | $10^5$  | $8$  |
| 3          | $10^{12}$          | $0$     | $5$  |
| 4          | $10^{12}$          | $1$     | $10$ |
| 5          | $10^{12}$          | $2$     | $10$ |
| 6          | $10^{12}$          | $100$   | $10$ |
| 7          | $10^{12}$          | $10^3$  | $15$ |
| 8          | $10^{12}$          | $10^4$  | $15$ |
| 9          | $10^{12}$          | $10^5$  | $20$ |

## 样例 #1

### 输入

```
5 5 2```

### 输出

```
23```

## 样例 #2

### 输入

```
12345678 1919810 11451```

### 输出

```
69157901```

## 样例 #3

### 输入

```
999999999999 125432670 1000```

### 输出

```
154496571```

# 题解

## 作者：LostKeyToReach (赞：6)

笑点解析：赛时使用封装的取模类导致 $100$ 变 $65$。

海亮是不是人均多项式代师啊。

这是一个不用动脑子的做法。我们不妨设答案为 $f(n, x)$，则对于所有 $m \in \N$ 都有：

$$
\begin{aligned}
f(2^m - 1, x) &= \sum_{i = 0} ^ {2^m - 1} (-1)^{\text{popcnt}(i)}(i + x)^k \\
&= \sum_{S \subseteq \{0, 1, \ldots, m - 1\}}(-1)^{|S|}\left(i + \sum_{v \in S}2^v\right)^k.
\end{aligned}
$$

这样只对 $n = 2^m - 1$ 有用，那么怎么处理普通情况？我们令 $m$ 为 $n + 1$ 最高位对应的幂，那么原式变为：

$$
\begin{aligned}
f(n, x) &= f(2^m - 1, x) + \sum_{i = 2^m}^n (-1)^{\text{popcnt}(i)}(i + x)^k \\
&= f(2^m - 1, x) + \sum_{i = 0}^{n - 2^m}(-1)^{\text{popcnt}(i + 2^m)}[x + (i + 2^m)]^k \\
&= f(2^m - 1, x) - \sum_{i = 0}^{n - 2^m}(-1)^{\text{popcnt}(i)}[(x + 2^m) + i]^k \\
&= f(2^m - 1, x) - f(n - 2^m, x + 2^m).
\end{aligned}
$$

接下来我们对 $f(2^m - 1, x)$ 根据二项式定理进行展开：

$$
\begin{aligned}
f(2^m - 1, x) &= \sum_{S \subseteq \{0, 1, \ldots, m - 1\}}(-1)^{|S|}\left(i + \sum_{v \in S}2^v\right)^k \\
&= \sum_{S \subseteq \{0, 1, \ldots, m - 1\}}(-1)^{|S|}\sum_{i = 0} ^ k {k \choose  i}x^{k - i}\left(\sum_{v \in S}2^v\right)^i \\
&= \sum_{i = 0} ^ k {k \choose  i}x^{k - i}\sum_{S \subseteq \{0, 1, \ldots, m - 1\}}(-1)^{|S|}\left(\sum_{v \in S}2^v\right)^i. \\
\end{aligned}
$$

考虑给 $\displaystyle x^{k - i}\sum_{S \subseteq \{0, 1, \ldots, m - 1\}}(-1)^{|S|}\left(\sum_{v \in S}2^v\right)^i$ 构造指数生成函数，那么这一部分所构成的答案为：

$$
\begin{aligned}
\prod_{i = 0} ^{m - 1}\left(1 - e^{2^it}\right) &=
\prod_{i = 0} ^{m - 1}\left(-\sum_{j = 1} ^ {\infty}\frac{2^{ij}}{j!}t^{j}\right).
\end{aligned}
$$

组合意义显然，那么第 $i$ 项的系数便是答案。所以我们用 NTT 预处理一下多项式再上一个记忆化搜索就做完了，时间复杂度 $\mathcal{O}(k\log k\log n)$。

参考代码：

```cpp
VVI polys, polyss;
int n, x, k;
VI fact, ifact;
void prepare() {
    polys.resize(46);
    fact.resize(k + 1, 0);
    ifact.resize(k + 1, 0);
    fact[0] = 1;
    For(i, 1, k) fact[i] = modMul(fact[i - 1], i);
    For(i, 0, k) ifact[i] = power(fact[i], mod - 2);
    For(i, 0, 45) {
        polys[i].resize(k + 1, 0);
        For(r, 0, k) {
            if (r == 0) {
                continue;
            }
            polys[i][r] = modMul(-power(2, i * r), ifact[r]);
        }
    }
    polyss.resize(46);
    polyss[0].resize(k + 1, 0);
    polyss[0][0] = 1;
    For(i, 0, 44) polyss[i + 1] = convolution(polyss[i], polys[i], k);
}
int calc(int m, int x, int kk) {
    int ans = 0;
    For(j, 0, kk) {
        ans = modAdd(ans, modMul(modMul(modMul(modMul(modMul(fact[k], ifact[j]), 
            ifact[k - j]), power(x, kk - j)), polyss[m][j]), fact[j]));
    }
    return ans;
}
std::map<PII, int> mp;
int solve(int n, int x) {
    if (n == -1) return 0;
    if (mp.find({n, x}) != mp.end())
        return mp[{n, x}];
    int m = 64 - __builtin_clzll(n + 1) - 1;
    int p = 1LL << m;
    if (n == p - 1) return mp[{n, x}] = calc(m, x, k);
    else {
        return mp[{n, x}] = modSub(calc(m, x, k), solve(n - p, (x + p) % mod));
    }
}
#define MULTI_TEST 0
int32_t main() {
#if MULTI_TEST == 1
#else
    std::cin >> n >> x >> k;
    prepare();
    std::cout << solve(n, x) << "\n";
#endif
}
```

---

## 作者：Zzzcr (赞：5)

验题人题解

$$
\sum_{i=0}^{n}(-1)^{\operatorname{pc}(i)}(i+x)^k=\sum_{i=0}^{n}(-1)^{\operatorname{pc}(i)}\sum_{j=0}^k(^k_j)i^jx^{k-j}=\sum_{j=0}^{k}(^k_j)x^{k-j}\sum_{i=0}^{n}(-1)^{\operatorname{pc}(i)}i^j
$$

所以，只需要求出

$$
\sum_{i=0}^{n}(-1)^{\operatorname{pc}(i)}i^j,\forall j\in[0,k]
$$

注意到 $(-1)^{\operatorname{pc}(i)}$ 的生成方式形如每次复制一遍，再将后半取反，容易想到倍增。具体的，令 $ g_{p,j}=\sum_{i=0}^{2^p-1}(-1)^{\operatorname{pc}(i)}i^j $，有：

$$
g_{p+1,j}=g_{p,j}-\sum_{i=0}^{2^p-1}(-1)^{\operatorname{pc}(i)}(i+2^p)^j
$$

只用考虑式子的后半部分，令 $t=2^p$，再次使用二项式定理：

$$
\sum_{i=0}^{t-1}(-1)^{\operatorname{pc}(i)}(i+t)^j=\sum_{i=0}^{t-1}(-1)^{\operatorname{pc}(i)}\sum_{d=0}^{j}(^j_d)i^{j-d}t^d=\sum_{d=0}^jg_{p,j-d}(^j_d)t^d
$$

把组合数拆开就是一个卷积形式，对 $n$ 二进制拆位，从高位到低位每个再卷一遍，即可做到 $\mathcal{O}(k\log k\log n)$。

---

## 作者：System_Error_ (赞：1)

~~免责申明~~，以下的 $k$ 有多种含义，请读者仔细分辨。

先起手推柿子，把 $(i + x)^k$ 暴力展开，得：
$$
\sum_{i = 0}^n (-1)^{popcnt(i)} \sum_{j = 0}^k i^{k - j} x^j \binom{k}{j} \\
= \sum_{j = 0}^k x_j \binom{k}{j} \sum_{i = 0}^n (-1)^{popcnt(i)} i^{k - j}
$$
我们设 $\sum_{i = 0}^n (-1)^{popcnt(i)} i^k$ 为 $ans_{n,k}$，那么答案等于 $\sum_{j = 0}^k x_j \binom{k}{j} ans_{n,k - j}$，我们考虑求出 $ans_n$ 序列。

首先考虑 $ans_{n,0}$ 怎么求，相当于我们要求一个 $(-1)^{popcnt(i)}$ 的前缀和，设为 $pre_i$，打表容易发现：当 $i$ 为奇数时 $pre_i = 0$，否则 $pre_i = (-1)^{popcnt(i)}$。证明如下：

- 首先 $pre_{2k - 1} = pre_{2k + 1}$，设 $(-1)^{popcnt(2k)} = x$，则 $(-1)^{popcnt(2k+1)} = -x$，所以 $pre_{2k + 1} = pre_{2k - 1} + x - x = pre_{2k - 1}$。由于 $pre_1 = 0$，所以当 $i$ 为奇数时 $pre_i = 0$。
- 其次 $pre_{2k} = pre_{2k - 1} + (-1)^{popcnt(2k)}$，又因为 $pre_{2k - 1} = 0$，所以 $pre_{2k} = (-1)^{popcnt(2k)}$。

这样你就会 $\Theta(1)$ 求 $pre$ 了，开始推柿子。
$$
ans_{n,k} = \sum_{i = 0}^n (-1)^{popcnt(i)} i^k \\
= n^k \sum_{i = 0}^n (-1)^{popcnt(i)} - \sum_{i = 0}^n (-1)^{popcnt(i)} (n^k - i^k) \\
= n^k pre_n - \sum_{i = 0}^n (-1)^{popcnt(i)} (n^k - i^k)
$$
考虑计算后面的柿子：
$$
\sum_{i = 0}^n (-1)^{popcnt(i)} (n^k - i^k) \\
= \sum_{i = 0}^{n - 1} pre_i ((i + 1)^k - i^k)
$$
考虑证明（也可以用数形结合简单证明）：
$$
\sum_{i = 0}^{n - 1} pre_i ((i + 1)^k - i^k) \\
= \sum_{i = 0}^{n - 1} \sum_{j = 0}^i (-1)^{popcnt(j)} ((i+1)^k - i^k) \\
= \sum_{j = 0}^{n - 1} (-1)^{popcnt(j)} \sum_{i = j}^{n - 1} (i+1)^k - i^k \\
= \sum_{j = 0}^{n - 1} (-1)^{popcnt(j)} (n^k - j^k)
$$
将 $(i+1)^k - i^k$ 用二项式定理展开：
$$
= \sum_{i = 0}^{n - 1} pre_i \sum_{j = 0}^{k - 1} \binom{k}{j} i^j \\
= \sum_{j = 0}^{k - 1} \binom{k}{j} \sum_{i = 0}^{n - 1} pre_i i^j
$$
考虑计算第二个求和符号及其后面的东西，由于当 $i$ 为奇数时 $pre_i = 0$，所以可以跳过，而由 $popcnt$ 的性质可得当 $i$ 为偶数时 $(-1)^{popcnt(i)} = (-1)^{popcnt(i/2)}$。

所以：
$$
\sum_{i = 0}^{n - 1} pre_i i^j \\
 = \sum_{i = 0}^{\lfloor \frac{n - 1}{2} \rfloor} pre_{2i} (2i)^j \\
 = 2^j \sum_{i = 0}^{\lfloor \frac{n - 1}{2} \rfloor} (-1)^{popcnt(i)}i^j \\
 = 2^j ans_{\lfloor \frac{n - 1}{2} \rfloor,j}
$$
代回原式得：
$$
\sum_{i = 0}^{n - 1} (-1)^{popcnt(i)} (n^k - i^k) \\
= \sum_{j = 0}^{k - 1} \binom{k}{j} 2^j ans_{\lfloor \frac{n - 1}{2} \rfloor,j}
$$
由于需要计算的 $ans$ 的第一维只有 $\log n$ 个，所以此时你已经会了 $\Theta(k^2 \log n)$ 做法。



我们将 $C_k^j$ 展开：
$$
\sum_{j = 0}^{k - 1} \frac{k!}{j!(k-j)!} 2^j ans_{\lfloor \frac{n - 1}{2} \rfloor,j} \\
= k! \sum_{j = 0}^{k - 1} \frac{1}{j!(k-j)!} 2^j ans_{\lfloor \frac{n - 1}{2} \rfloor,j} \\
= k!\sum_{j = 0}^{k - 1} \frac{2^j ans_{\lfloor \frac{n - 1}{2} \rfloor,j}}{j!} \times  \frac{1}{(k-j)!}
$$
我们设当 $k$ 取 $0 \sim K$ 时上述柿子的答案为 $h_k$，$f_i = \frac{2^i ans_{\lfloor \frac{n - 1}{2} \rfloor,i}}{i!},g_i = \frac{1}{i!}$，那么有 $h = f * g$ 再对每个 $h_k$ 减去上述柿子取 $j = k$ 的答案再乘上 $k!$ 即可。其中 $*$ 是卷积，可以用 NTT 快速做。

这样你就可以以 $\Theta(k \log k \log n)$ 的时间复杂度求出 $ans_n$ 序列，代回一开始的式子做一遍就得到答案了。

闲话：没被超级大神 @Zzzcr 爆掉之前还以为这道题有 *3100（

---

## 作者：lbmzxhb (赞：0)

有趣数论题。

## 思路：

看到 $\text{popcnt}(i)$ 和 $n$ 的数据范围，容易想到数位 dp 与倍增。

令 $dp_{j,k}=\sum_{i=0}^{2^j-1}(-1)^{\text{popcnt}(i)}i^k$，则有：

$$\begin{aligned}dp_{j,k}&=\sum_{i=0}^{2^j-1}(-1)^{\text{popcnt}(i)}i^k\\&=\sum_{i=0}^{2^{j-1}-1}(-1)^{\text{popcnt}(i)}i^k-\sum_{i=0}^{2^{j-1}-1}(-1)^{\text{popcnt}(i)}(i+2^{j-1})^k\\&=dp_{j-1,k}-\sum_{w=0}^k\sum_{i=0}^{2^{j-1}-1}(-1)^{\text{popcnt}(i)}{k\choose w}i^w(2^{j-1})^{k-w}\\&=dp_{j-1,k}-\sum_{w=0}^k{k\choose w}(2^{j-1})^{k-w}\sum_{i=0}^{2^{j-1}-1}(-1)^{\text{popcnt}(i)}i^w\\&=dp_{j-1,k}-\sum_{w=0}^k{k\choose w}(2^{j-1})^{k-w}dp_{j-1,w}\\&=dp_{j-1,k}-\sum_{w+w'=k}\frac{k!}{w!(w')!}(2^{j-1})^{w'}dp_{j-1,w}\\&=dp_{j-1,k}-k!\sum_{w+w'=k}\frac{(2^{j-1})^{w'}}{(w')!}\cdot\frac{dp_{j-1,w}}{w!}\end{aligned}$$

后面的求和显然是卷积，上 NTT 即可。由于 $j\le \log n$，所以这部分的时间复杂度 $O(k\log k\log n)$。

然后考虑求原来的式子。直接求不好做，可以把 $n$ 二进制拆位，对于第 $j$ 位可以这么算：

$$\begin{aligned}\sum_{i=0}^{2^j-1}(-1)^{\text{popcnt}(i)}(i+x)^k&=\sum_{w=0}^k\sum_{i=0}^{2^j-1}(-1)^{\text{popcnt}(i)}{k\choose w}i^wx^{k-w}\\&=\sum_{w=0}^k{k\choose w}x^{k-w}\sum_{i=0}^{2^j-1}(-1)^{\text{popcnt}(i)}i^w\\&=\sum_{w=0}^k{k\choose w}x^{k-w}dp_{j,w}\\&=k!\sum_{w+w'=k}\frac{x^{w'}}{(w')!}\cdot\frac{dp_{j,w}}{w!}\end{aligned}$$

也化成了卷积的形式。但由于这个式子最多求 $\log n$ 次，所以可以暴力求，这部分的时间复杂度 $O(k\log n)$。

总时间复杂度 $O(k\log k\log n)$。

## 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int P(998244353);
template<int P>
struct modint {
private:
    template<typename T>
    inline static const T Down(const T&x) {return x >= P ? x - P : x;}
public:
    unsigned int v;
    modint(unsigned int v=0) : v(v%P) {}
    using mint = modint;
    #define FI friend inline
    FI ostream&operator<<(ostream&o, mint v) {return o<<v.v;}
    FI istream&operator>>(istream&i, mint&v) {int x;return i>>x,v.v=Down(x%P+P),i;}
    FI mint operator+(mint a, mint b) {return Down(a.v + b.v);}
    FI mint operator-(mint a, mint b) {return Down(a.v - b.v + P);}
    FI mint operator*(mint a, mint b) {return 1ull * a.v * b.v % P;}
    FI mint operator/(mint a, mint b) {return a * ~b;}
    FI mint operator^(mint a, int p) {mint r=1; for(; p; p >>= 1, a = a * a) if (p & 1) r = r * a; return r;}
    FI mint operator~(mint a) {return a ^ (P - 2);}
    FI mint operator-(mint a) {return a.v ? P - a.v : 0;}
    FI mint&operator+=(mint&a, mint b) {return a=a+b;}
    FI mint&operator-=(mint&a, mint b) {return a=a-b;}
    FI mint&operator*=(mint&a, mint b) {return a=a*b;}
    FI mint&operator/=(mint&a, mint b) {return a=a/b;}
    FI mint&operator^=(mint&a, int b) {return a=a^b;}
    FI mint&operator++(mint&a) {return a += 1;}
    FI mint&operator--(mint&a) {return a -= 1;}
    FI mint operator++(mint&a, signed) {mint x=a; return ++a, x;}
    FI mint operator--(mint&a, signed) {mint x=a; return --a, x;}
    FI bool operator==(mint a, mint b) {return a.v==b.v;}
    FI bool operator!=(mint a, mint b) {return a.v!=b.v;}
};
typedef modint<998244353> mint;
const int K((1 << 18) + 5), len(1 << 18);
const mint G(3), GI((P+1)/G), rlen((mint)(1)/len);
typedef array<mint, K> Arr;
Arr t1, t2, dp[40], fac, ifac;
int rev[K], n, k, x;
void NTT(Arr&a, int f) {
	for (int i = 0; i < len; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int h = 1; h < len; h <<= 1) {
		mint g0 = (f == 1 ? G : GI) ^ ((P - 1) / (h * 2));
		for (int i = 0; i < len; i += h << 1) {
			mint g = 1;
			for (int j = i; j < i + h; j++, g *= g0) {
				mint x = a[j], y = g * a[j + h];
				a[j] = x + y, a[j + h] = x - y;
			}
		}
	}
	if (f == -1) 
		for (int i = 0; i < len; i++) a[i] *= rlen;
}
void init() {
	fac[0] = 1;
	for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << 17);
	for (int i = 1; i < len; i++) fac[i] = fac[i - 1] * i;
	ifac[len - 1] = 1 / fac[len - 1];
	for (int i = len - 1; i; i--) ifac[i - 1] = ifac[i] * i;
}
void work() {
	cin >> n >> x >> k;
	dp[0][0] = 1;
	for (int i = 1; i < 40; i++) {
		mint p2 = (1ll << i - 1) % P;
		for (int j = 0; j <= k; j++) t1[j] = (p2 ^ j) * ifac[j];
		fill(t1.begin() + k + 1, t1.end(), 0);
		dp[i] = t2 = dp[i - 1];
		for (int j = 0; j <= k; j++) t2[j] *= ifac[j];
		NTT(t1, 1), NTT(t2, 1);
		for (int j = 0; j < len; j++) t1[j] *= t2[j];
		NTT(t1, -1);
		for (int j = 0; j <= k; j++) dp[i][j] -= fac[j] * t1[j];
	}//按照上面的式子计算
	n++;//因为直接二进制拆位后计算的结果为 0~n-1 的答案，所以 n++
	mint ans = 0, ff = 1;
	for (int i = 39; ~i; i--) {
		if ((n >> i) & 1) {
			x %= P;
			mint tt = 0, x2 = x;
			for (int j = 0; j <= k; j++) tt += (x2 ^ j) * ifac[j] * dp[i][k - j] * ifac[k - j];
			ans += ff * fac[k] * tt;
			ff = -ff;
			x += 1ll << i;
		}
	}
	cout << ans;
}
signed main() {
	init();
	work();
} 
```

---

