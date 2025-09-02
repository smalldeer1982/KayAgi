# 「DTOI-4」白的 Fibonacci

## 题目描述

定义 $F(k, n)$ 如下：

$$
F(k,n) = 
\left \{
\begin{aligned}
&st_0\ && k = 1\ \land\ n = 0 \\
&st_1\ && k = 1\ \land\ n = 1 \\
&0\ && k > 1 \ \land \ n < 0 \\
&a \times F(k, n - 1) + b \times F(k, n - 2)\ && k = 1 \ \land\ n > 1 \\
&t_k \times F(k, n - 1) + s^n \times F(k - 1, n)\ && \text{otherwise}
\end{aligned}
\right.
$$

给定 $F$ 递推式的各项系数和 $k, n$，请你求出 $F(k, n) \bmod 998244353$ 的值。

## 说明/提示

| $\textbf{Subtask}$ | $k \leq$ | $n \leq$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | $100$ | 无 | $5$ |
| $2$ | $100$ | $2^{63}$ | 无 | $25$ |
| $3$ | $5000$ | $2^{63}$ | $s = 1, \forall 2 \leq i \leq k, t_i = 1$ | $10$ |
| $4$ | $5000$ | $2^{63}$ | 无 | $60$ |

对于 $100\%$ 的数据，$1 \leq k \leq 5 \times 10^3$，$0 \leq n \le 2^{63}$，$-998244352 \leq st_0, st_1, a, b, s, t_i \leq 998244352$。

## 样例 #1

### 输入

```
10 25
-5 -73 -95 64 15
-80 -31 -58 15 95 -1 14 -30 31 ```

### 输出

```
998096342```

# 题解

## 作者：NaCly_Fish (赞：12)

偶然看到这题，就稍微回应一下题目提供者，虽然具体做法算是比较经典了。为方便表述，本文中记 $F(1,0)=r_0$，$F(1,1)=r_1$。

首先我们容易对 $F(1,n)$ 建立关于 $n$ 的生成函数：
$$F_1(x)=\frac{r_0+(r_1-r_0a)x}{1-ax-bx^2}$$
把递推式用生成函数表达：
$$F_k(x)=t_k x F_k(x)+ F_{k-1}(sx)$$
$$F_k(x) =  \frac{F_{k-1}(sx)}{1-t_kx}$$
递推的时候把 $x$ 替换为 $sx$ 的操作其实很好处理：
$$F_k(x)=  \frac{r_0+(r_1-r_0a)s^{k-1}x}{1-as^{k-1}x-bs^{2k-2}x^2}\prod_{i=2}^k \frac{1}{1-t_is^{k-i}x}$$
大力分治乘然后做线性递推，时间复杂度 $\Theta(k \log^2 k+k \log k \log n)$ 可以通过本题，但是还不够优秀。继续优化可以做到 $\mathcal O(k \log^2 k+k \log n)$，不过写起来比较复杂，看看就好。

EI 讲过，这种形式可以做分式分解。首先，我们把分母中的那个二次多项式做因式分解（可能需要扩域），我们的目标就是将这样一个形式的分式（注意一点，虽然乍一看分解后有 $k+1$ 项，但是可能有重复，要记为重根）：
$$\frac{1}{Q(x)}=\prod_{i=1}^m \frac{1}{(1-q_ix)^{d_i}}$$
改写为
$$\sum_{i=1}^m \frac{P_i(x)}{(1-q_ix)^{d_i}}$$
这样一个形式就很容易提取一项系数了。

通分后可以得到这样一个结果（对于各 $i \in [1,m]$）：
$$\frac{P_i(x)Q(x)}{(1-q_ix)^{d_i}}\equiv 1 \pmod{(1-q_ix)^{d_i}}$$
所以我们只需要求出各 $\dfrac{Q(x)}{(1-q_ix)^{d_i}} \bmod (1-q_ix)^{d_i}$ 之后，再分别求出它们**在模 $(1-q_ix)^{d_i}$ 意义下的逆**得到的便是 $P_i(x)$。

对于前者，可以分治处理：不要把它看作分式，它本身就是许多一次式的乘积，利用 $F(x) \equiv (F(x) \bmod A(x)B(x)) \pmod {A(x)}$ 这一性质即可。

后者也比较简单，我[另一篇题解](https://www.luogu.com.cn/blog/NaCly-Fish-blog/solution-at-s8pc-3-g)中也有提到，就不复读了（

所以为什么参数的数据范围还要开到负数呢？

---

## 作者：joke3579 (赞：4)

可能有更简单的推法和更优的复杂度，本题解只作抛砖引玉。

经过一些手膜，我们推断 $F(k,n)$ 可以使用 $k+1$ 阶常齐次线性递推表出。

设
$$F(k,n) = \sum_{i = 1}^{k+1} f_{k,i} \times F(k, n-i) $$
自然地，$f_{1,1} = a, f_{1,2} = b$。

现在讨论如何使用 $f_{k-1}$ 推出 $f_{k}$ 。以下讨论中 $k > 1$。

$$\begin{aligned}
& F(k,n) = t_k \times F(k, n-1) + s^n \times F(k-1, n)
\\  = \ & t_k \times F(k, n-1) + s^n \times \sum_{i = 1}^{k} f_{k-1,i} \times F(k-1, n-i) \qquad \text{(使用递推式表出)}
\\  = \ & t_k \times F(k, n-1) + \sum_{i = 1}^{k} f_{k-1,i} \times s^{i} \times s^{n-i} \times F(k-1, n-i) \qquad (将s^n拆分，凑出系数)
\\  = \ & t_k \times F(k, n-1) + \sum_{i = 1}^{k} f_{k-1,i} \times s^{i} \times (F(k, n-i) - t_k \times F(k, n - i - 1))\qquad  (递推式移项带入)
\\  = \ & t_k \times F(k, n-1) + \sum_{i = 1}^{k} f_{k-1,i} \times s^{i} \times F(k, n-i) - \sum_{i = 2}^{k+1} f_{k-1,i-1} \times s^{i-1} \times t_k \times F(k, n - i) \qquad  (拆分和式)
\\  = \ & \sum_{i=1}^{k+1} ( f_{k-1,i} \times s^i - f_{k-1,i-1} \times s^{i-1} \times t_k + t_k[i = 1] ) \times F(k, n-i) \qquad  (表出系数)
\end{aligned}$$

为方便，设 $\forall k > 1,i > k+1, \ f_{k,0} = f_{k,i} = 0$。于是 $f_k$ 可以被 $f_{k-1}$ 表为如下形式：
$$ f_{k,i} = f_{k-1,i} \times s^i - f_{k-1,i-1} \times s^{i-1} \times t_k + t_k[i = 1]  $$

因此我们可以 $O(k^2)$  地推出 $F(k,n)$ 的递推系数与前 $k+1$ 项值。随后 $O(k \log k \log n)$ 地递推即可。

总时间复杂度 $O(k ^ 2 + k \log k \log n)$。

Bonus: 能否 $O(k\log^2 k + k\log k \log n)$？ 


```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for (register int(i) = (a); (i) <= (b); ++(i))
#define pre(i,a,b) for (register int(i) = (a); (i) >= (b); --(i))
using namespace std;
typedef unsigned long long ll;
const int N = 5000 + 10;
const int mod = 998244353, g = 3;
int k, st0, st1, a, b, s, ans;
int t[N], f[N], st[N];
ll n;

#ifdef ONLINE_JUDGE
    char buf[1<<21], *p1 = buf, *p2 = buf;  inline char getc() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF : *p1++); }
    #define getchar getc
#endif
template <typename T> inline void get(T & x){
	x = 0; char ch = getchar(); bool f = false;
	while (ch < '0' or ch > '9') f = f or ch == '-',  ch = getchar();
	while (ch >= '0' and ch <= '9') x = (x<<1) + (x<<3) + (ch^48), ch = getchar(); f && (x = -x);
} template <typename T, typename ... Args> inline void get(T & x, Args & ... _Args) { get(x); get(_Args...); }

struct Light {
    int p, mx, sq, dsq[100], usq[100];
    void init(int _p, int _mx) {
        p = _p, mx = _mx; sq = sqrt(mx) + 1;
        dsq[0] = usq[0] = 1;
        rep(i,1,sq - 1) dsq[i] = 1ll * dsq[i-1] * p % mod;
        usq[1] = 1ll * dsq[sq - 1] * p % mod;
        rep(i,2,sq) usq[i] = 1ll * usq[i-1] * usq[1] % mod;
    } int qp(int k) {
        return 1ll * dsq[k % sq] * usq[k / sq] % mod;
    }
} pw;

int btrs[N << 5]; // butterfly_transform
inline int initrs(int k) {
    int limit = 1;
    while (limit < k) limit <<= 1;
    for (register int i = 0  ; i < limit; i ++) 
        btrs[i] = ((btrs[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0));
    return limit;
}

inline ll qp(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    } return ret;
} inline ll inv(ll a) { return qp(a, mod-2); }

int L, w[2][1<<19];
inline int __INITILIZE__UNIT__ROOT__() {
    L = 1<<19;
    w[0][0] = w[1][0] = 1;
    int wn = qp(g, (mod-1) / L);
    for (register int i = 1; i < L; i++) w[0][L - i] = w[1][i] = 1ll * w[1][i - 1] * wn % mod;
    return 1;
} int __INITIALIZER__ = __INITILIZE__UNIT__ROOT__();

struct poly {
    vector <ll> f; 
    ll operator [] (const int & pos) const { return f[pos]; }
    ll & operator [] (const int & pos) { return f[pos]; }
    int deg() {return f.size(); }
    int deg() const  {return f.size(); }
    void Set(int n) { f.resize(n); }
    void Adjust() { while (f.size() > 1 and f.back() == 0) f.pop_back(); }
    void Reverse() { reverse(f.begin(), f.end()); }
    inline void NTT (const int lim, const int type) {
        Set(lim);
        for (register int i = 0; i < lim; i++) if (i < btrs[i]) swap(f[i], f[btrs[i]]);
        for (register int mid = 1; mid < lim; mid <<= 1) {
            for (register int i = L / (mid<<1), j = 0; j < lim; j += (mid << 1)) {
                for (register int k = 0; k < mid; k++) {
                    int x = f[j + k], y = w[type][i * k] * f[j + k + mid] % mod;
                    f[j + k] = (x + y) % mod;
                    f[j + k + mid] = (x - y + mod) % mod;
                }
            }
        } if (type == 1) return;
        ll inv = qp(lim, mod - 2);
        for (register int i = 0; i < lim; i++) f[i] = f[i] * inv % mod;
    } 
    friend poly operator - (const poly & x, const poly & y) {
        poly ret; ret.Set(max(x.deg(), y.deg()));
        for (register int i = 0; i < x.deg(); ++i) ret[i] = x[i];
        for (register int i = 0; i < y.deg(); ++i) ret[i] = (ret[i] - y[i] + mod) % mod;
        return ret;
    } void operator -= (const poly & x) {
        Set(max(deg(), x.deg()));
        for (register int i = 0; i < x.deg(); ++i) f[i] = (f[i] - x[i] + mod) % mod;
    } 
    friend poly operator * (const poly & x, const poly & y) {
        poly ret, A = x, B = y;
        int limit = initrs(A.deg() + B.deg() - 1);
        A.NTT(limit, 1), B.NTT(limit, 1); ret.Set(limit);
        for (register int i = 0; i < limit; i++) ret[i] = 1ll * A[i] * B[i] % mod;
        ret.NTT(limit, 0); ret.Adjust();
        return ret;
    } void operator *= (const poly & x) {
        poly A = x;
        int limit = initrs(deg() + A.deg() - 1);
        A.NTT(limit, 1); NTT(limit, 1);
        for (register int i = 0; i < limit; i++) f[i] = 1ll * A[i] * f[i] % mod;
        NTT(limit, 0); Adjust();
    }
    friend poly operator % (const poly & x, const poly & y) {
        poly A = x, B = y;
        A.Reverse(), B.Reverse(); B.Set(x.deg() - y.deg() + 1);
        B = B.Inv(); B *= A;
        B.Set(x.deg() - y.deg() + 1); B.Reverse();
        poly R = x - B * y; R.Set(y.deg() - 1);
        return R;
    }
    poly Inv() {
        poly ret; ret.Set(1);
        if (f.empty()) return ret;
        ret[0] = inv(f[0]); poly A, B;
        for (register int len = 2, limit; len < (deg() << 1); len <<= 1) {
            A.f.assign((*this).f.begin(), (*this).f.begin() + min(len, deg()));
            B = ret; B.Set(min(len, deg()));
            limit = initrs(A.deg() + B.deg() - 1);
            A.NTT(limit, 1); B.NTT(limit, 1);
            ret.Set(limit);
            for (register int i = 0; i < limit; i++) ret[i] = (2 - A[i] * B[i] % mod + mod) * B[i] % mod;
            ret.NTT(limit, 0);
            ret.Set(len);
        } ret.Set(deg()); return ret;
    }
} F, I;

inline void mul(poly & a, poly b, poly m) {
    a *= b;
    if (a.deg() >= m.deg()) a = a % m;
}

poly qp(poly a, ll b, poly m) {
    poly ret; ret.Set(1), ret[0] = 1;
    while (b) {
        if (b & 1) mul(ret, a, m);
        mul(a, a, m);
        b >>= 1;
    } return ret;
}

signed main() {
    get(k, n); 
    get(st[0], st[1], a, b, s);
    st[0] = (mod + st[0]) % mod; st[1] = (mod + st[1]) % mod; a = (mod + a) % mod; b = (mod + b) % mod; s = (mod + s) % mod;
    pw.init(s, k + 2);
    rep(i,2,k) get(t[i]), t[i] = (mod + t[i]) % mod;
    
    rep(i,2,k) st[i] = (1ll * a * st[i-1] + 1ll * b * st[i-2]) % mod; 
    rep(i,2,k) rep(j,1,k) 
        st[j] = (1ll * t[i] * st[j-1] + 1ll * pw.qp(j) * st[j]) % mod;
    if (n <= k) printf("%d\n", st[n]), exit(0);

    f[1] = a, f[2] = b;
    rep(i,2,k) pre(j,i+1,1) 
        f[j] = (1ll * pw.qp(j) * f[j] - 1ll * t[i] * pw.qp(j-1) % mod * f[j-1] % mod + (j == 1 ? t[i] : 0) + mod) % mod;

    F.Set(k+2); rep(i,1,k+1) F[k + 1 - i] = (mod - f[i]) % mod; 
    F[k+1] = 1;
    I.Set(2); I[0] = 0, I[1] = 1; 
    poly Ans = qp(I, n, F);
    rep(i,0,k) ans = (ans + 1ll * st[i] * Ans[i]) % mod;
    printf("%d\n", ans);
    return 0;
}
```

---

