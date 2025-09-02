# Rare Coins

## 题目描述

There are $ n $ bags numbered from $ 1 $ to $ n $ , the $ i $ -th bag contains $ a_i $ golden coins and $ b_i $ silver coins.

The value of a gold coin is $ 1 $ . The value of a silver coin is either $ 0 $ or $ 1 $ , determined for each silver coin independently ( $ 0 $ with probability $ \frac{1}{2} $ , $ 1 $ with probability $ \frac{1}{2} $ ).

You have to answer $ q $ independent queries. Each query is the following:

- $ l $ $ r $ — calculate the probability that the total value of coins in bags from $ l $ to $ r $ is strictly greater than the total value in all other bags.

## 说明/提示

In both queries from the first example, the answer is $ \frac{1}{4} $ .

## 样例 #1

### 输入

```
2 2
1 0
0 2
2 2
1 1```

### 输出

```
748683265 748683265```

## 样例 #2

### 输入

```
4 3
2 3 4 5
1 0 7 3
3 3
2 3
1 4```

### 输出

```
997756929 273932289 1```

# 题解

## 作者：Hooch (赞：13)

[可能更好的体验](https://www.cnblogs.com/CTHOOH/p/18076821)。

对于每个询问，可以把这 $r - l + 1$ 个袋子合并成一个 有 $\sum\limits_{i = l}^r a_i$ 个金币和 $\sum\limits_{i = l}^r b_i$ 个银币的袋子。$[l, r]$ 外的袋子同理也可以这样合并。

假设 $sum_a = \sum\limits_{i = 1}^n a_i, sum_b = \sum\limits_{i = 1}^n b_i$，$in_a = \sum\limits_{i = l}^r a_i, in_b = \sum\limits_{l = 1}^r b_i$, $out_a = sum_a - in_a, out_b = sum_b - in_b$。

那么原问题就是查询 $in_a + rand(in_b) > out_a + rand(out_b)$ 的概率，其中 $rand(x)$ 表示 $x$ 个银币时的随机取值。把上面的式子中符号两边的 $rand$ 移到同一边，得到：

$$
rand(in_b) - rand(out_b) > out_a - in_a
$$

观察到 $in_b + out_b = sum_b$，那么尝试把 $rand(in_b) - rand(out_b)$ 变成 $rand(in_b) + rand(out_b)$。只需两边同时加上 $out_b$，式子变成：

$$
rand(in_b) + rand(out_b) > out_a + out_b - in_a
$$

接着又有 $rand(in_b) + rand(out_b) = rand(in_b + out_b) = rand(sum_b)$，所以最终转化成了：

$$
rand(sum_b) > out_a + out_b - in_a
$$

其中 $out_a + out_b - in_a$ 是可以 $\Theta(1)$ 求得的，设 $Q = out_a + out_b - in_a$，那么答案是：

$$
\sum\limits_{x = Q + 1}^{sum_b} \binom{sum_b}{x} \times \left(\frac{1}{2}\right)^{n}
$$

预处理组合数后缀和即可，复杂度为 $O(n)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2E6 + 5;
template <class T>
T power(T a, long long b) {
  T res = 1;
  for (; b; b >>= 1, a *= a) {
    if (b & 1)
      res *= a;
  } return res;
}
#define C constexpr
#define FC friend constexpr
#define OP operator
template <long long mod>
class ModLL {
  public:
    long long n;
    static long long Mod;
    C ModLL() : n{} {}
    C ModLL(long long x) : n(norm(x % getmod())) {}
    C long long norm(long long x) {
      if (x >= getmod()) x %= getmod();
      if (x <= -getmod()) x %= getmod();
      if (x < 0) x += getmod();
      return x;
    }
    C long long getmod() {return (mod > 0 ? mod : Mod);}
    explicit C OP long long() const {return n;}
    C ModLL OP -() const {ModLL a; a.n = norm(getmod() - n); return a;}
    C ModLL inv() {assert(n != 0); return power((*this), getmod() - 2);}
    C ModLL &OP += (ModLL w) & {n = norm( n + w.n); return (*this);}
    C ModLL &OP -= (ModLL w) & {n = norm( n - w.n); return (*this);}
    C ModLL &OP *= (ModLL w) & {n = norm( 1LL * n * w.n % getmod()); return (*this);}
    C ModLL &OP /= (ModLL w) & {return (*this) *= w.inv();}
    FC ModLL OP + (ModLL a, ModLL b) {ModLL res = a; res += b; return res;}
    FC ModLL OP - (ModLL a, ModLL b) {ModLL res = a; res -= b; return res;}
    FC ModLL OP * (ModLL a, ModLL b) {ModLL res = a; res *= b; return res;}
    FC ModLL OP / (ModLL a, ModLL b) {ModLL res = a; res /= b; return res;}
    FC bool OP == (ModLL a, ModLL b) {return (a.n == b.n);}
    FC bool OP != (ModLL a, ModLL b) {return (a.n != b.n);}
    FC istream &OP >> (istream &is, ModLL &a) {
      long long x = 0; is >> x;
      a = ModLL(x); return is;
    }
    FC ostream &OP << (ostream &os, const ModLL &a) {return (os << (a.n));}
} ; 
template <int mod>
class ModInt {
  public:
    int n;
    static int Mod;
    C ModInt() : n{} {}
    C ModInt(int x) : n(norm(x % getmod())) {}
    C int norm(int x) {
      if (x >= getmod()) x %= getmod();
      if (x <= -getmod()) x %= getmod();
      if (x < 0) x += getmod();
      return x;
    }
    C static int getmod() {return (mod > 0 ? mod : Mod);}
    explicit C OP int() const {return n;}
    C ModInt OP -() const {ModInt a; a.n = norm(getmod() - n); return a;}
    C ModInt inv() const {assert(n != 0); return power((*this), getmod() - 2);}
    C ModInt &OP += (ModInt w) & {n = norm( n + w.n); return (*this);}
    C ModInt &OP -= (ModInt w) & {n = norm( n - w.n); return (*this);}
    C ModInt &OP *= (ModInt w) & {n = norm( 1LL * n * w.n % getmod()); return (*this);}
    C ModInt &OP /= (ModInt w) & {return (*this) *= w.inv();}
    FC ModInt OP + (ModInt a, ModInt b) {ModInt res = a; res += b; return res;}
    FC ModInt OP - (ModInt a, ModInt b) {ModInt res = a; res -= b; return res;}
    FC ModInt OP * (ModInt a, ModInt b) {ModInt res = a; res *= b; return res;}
    FC ModInt OP / (ModInt a, ModInt b) {ModInt res = a; res /= b; return res;}
    FC bool OP == (ModInt a, ModInt b) {return (a.n == b.n);}
    FC bool OP != (ModInt a, ModInt b) {return (a.n != b.n);}
    FC istream &OP >> (istream &is, ModInt &a) {
      int x = 0; is >> x;
      a = ModInt(x); return is;
    }
    FC ostream &OP << (ostream &os, const ModInt &a) {return (os << (a.n));}
} ; 
template <>
long long ModLL <0> :: Mod = (long long)(1E18) + 9;
template <>
int ModInt <0> :: Mod = 998244353;
using P = ModInt <998244353>;
#undef C
#undef FC
#undef OP
signed main(void) {
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n, q; cin >> n >> q;
  vector <int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  vector <int> suma(n + 1), sumb(n + 1);
  for (int i = 1; i <= n; ++i) {
    suma[i] = suma[i - 1] + a[i];
    sumb[i] = sumb[i - 1] + b[i];
  }
  vector <P> comb(sumb[n] + 1), fac(sumb[n] + 1); fac[0] = 1;
  for (int i = 1; i <= sumb[n]; ++i) fac[i] = fac[i - 1] * i;
  comb[sumb[n]] = 1;
  for (int i = sumb[n] - 1; i >= 0; --i) 
    comb[i] = comb[i + 1] + (fac[sumb[n]] / fac[i] / fac[sumb[n] - i]);
  P div = power(P(2), sumb[n]);
  for (int i = 1; i <= q; ++i) {
    int l, r; cin >> l >> r;
    --l;
    int in_a = suma[r] - suma[l], in_b = sumb[r] - sumb[l];
    int out_a = suma[n] - in_a, out_b = sumb[n] - in_b;
    int Q = out_a + out_b - in_a;
    if (Q >= sumb[n]) cout << 0 << ' ';
    else if (Q < 0) cout << 1 << ' ';
    else cout << comb[Q + 1] / div << ' ';
  }
  return 0;
}
```

---

## 作者：Meatherm (赞：5)

因为每个银币的价值是 $0,1$ 的概率相同，因此，要计算合法概率，只需要计数合法方案数除以总方案数。总方案数容易求得为 $2^{\sum b_i}$，因此我们只需要关心合法方案数。

设区间内部的金币和银币的数量分别为 $(G_A,S_A)$，区间外的为 $(G_B,S_B)$。记某种方案中，区间内外的银币价值分别为 $i,j$，那么一个方案合法当且仅当 $G_A+i > G_B+j$，化简得 $i-j > G_B-G_A$。

因此，合法的方案数为
$$
\sum \limits_{i} \binom{S_A}{i} \sum \limits_{j < i - (G_B-G_A)}  \binom{S_B}{j}
$$
内层和式中出现了组合数下指标和，而这是没有封闭形式的。我们只能尝试改变顺序，即枚举 $d = i-j$：
$$
\sum \limits_{d>G_B-G_A} \sum \limits_{j} \binom{S_B}{j}\binom{S_A}{j+d}
$$
很幸运，这次出现了范德蒙德卷积。用对称公式将 $\binom{S_B}{j}$ 写作 $\binom{S_B}{S_B-j}$ 后可以得到内层的和式等于 $\binom{S_A+S_B}{S_B+d}$，因此所求为
$$
\sum \limits_{d>G_B-G_A} \binom{S_A+S_B}{S_B+d}
$$
因为 $S_A+S_B$ 刚好等于整个序列中银币的数量 $\sum b_i$，因此对于每一组询问来说，我们只需要求出固定上标 $S_A+S_B$，下标在一个区间内 $[G_B-G_A+1+S_B,S_A+S_B]$ 的组合数之和。别忘了我们需要计算概率，因此最终答案为
$$
2^{-(\sum b_i)} \sum \limits_{G_B-G_A+1 \leq k \leq S_A+S_B} \binom{S_A+S_B}{k}
$$
我们可以预处理出这一行组合数的前缀和，并记录 $a,b$ 的前缀和。这样，每组询问时，我们可以 $O(1)$ 求得我们需要的所有信息，从而求解。

```cpp
# include <bits/stdc++.h>
 
const int N=2000010,INF=0x3f3f3f3f,mod=998244353;
 
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
 
int fac[N],finv[N];
 
int suma[N],sumb[N];
 
int n,q;
 
inline int qpow(int d,int p){
	int ans=1;
	while(p){
		if(p&1) ans=1ll*ans*d%mod;
		d=1ll*d*d%mod,p>>=1; 
	}
	return ans;
}
 
int bsum[N]; 
 
int pow2[N];
 
int inv2=(mod+1)/2;
 
inline void init(void){
	fac[0]=finv[0]=1,pow2[0]=1;
	for(int i=1;i<=N-10;++i){
		fac[i]=1ll*fac[i-1]*i%mod,pow2[i]=1ll*pow2[i-1]*inv2%mod;
	}
	finv[N-10]=qpow(fac[N-10],mod-2);
	for(int i=N-11;i;--i) finv[i]=1ll*finv[i+1]*(i+1)%mod;
	
	for(int i=0;i<=sumb[n];++i){ // binom(sumb,i)
		bsum[i]=1ll*fac[sumb[n]]*finv[sumb[n]-i]%mod*finv[i]%mod; 
		if(i) bsum[i]=(bsum[i-1]+bsum[i])%mod;
	}
	
	return;
}
 
inline int getsum(int l,int r){
	l=std::max(0,l),r=std::min(sumb[n],r);
	if(l>r) return 0;
	if(l==0) return bsum[r];
	return (bsum[r]-bsum[l-1]+mod)%mod;
}
 
inline int calc(int A,int B,int k){
	return getsum(B+k,A+B);	
}
 
int main(void){
	n=read(),q=read();
	
	for(int i=1;i<=n;++i) suma[i]=suma[i-1]+read();
	for(int i=1;i<=n;++i) sumb[i]=sumb[i-1]+read();
 
	init();
	
	while(q--){
		int l=read(),r=read();
		int A=sumb[r]-sumb[l-1],B=sumb[n]-A;
		int YA=suma[r]-suma[l-1],YB=suma[n]-YA;
		printf("%lld\n",1ll*calc(A,B,YB-YA+1)*pow2[A+B]%mod);
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：3)

计数简单。

先考虑一个询问怎么做。

我们发现问题可以化归到一边有 $x$ 个银币，另一边有 $y$ 个，求 $x$ 个银币的价值比另一边多 $k$ 的概率。

先乘上总方案数，把概率转成方案数。

我们关心 $x$ 个银币中有几个是 $1$，这是一个组合数。

枚举差量把不等式转成等式，有式子：$\sum\limits_{c=k}\sum\limits_{d=0}\binom yd \binom x{c+d}$。

由下指标反演推论，后面那个求和式是 $\binom{x+y}{y+c}$。

对下指标求缀和是没法好好做的。

但是关注到 $x+y$ 是一个定值，所以只需我们预处理出上指标为 $x+y$ 时的下指标后缀和即可。

容易做到 $O(n + q)$。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1948/submission/255043878)

---

## 作者：StayAlone (赞：3)

前置知识：范德蒙德恒等式。

显然可以先转成求方案数。对于一个询问，考虑枚举其内部和外部分别有多少个银币变成 $1$。

设内部金币、银币数量分别为 $x,k$，外部金币、银币数量分别为 $x',k'$。

显然 $k+k'$ 为定值。

枚举内部有 $i$ 个变成 $1$ 的银币，外部有 $j$ 个变成 $1$ 的银币。那么 $i+x>j+x'$，即 $i-j>x'-x$。

则方案数为：

$$
\sum_{i-j>x'-x} \binom{k}{i}\binom{k'}{j}=\sum_{i-j>x'-x} \binom{k}{i}\binom{k'}{k'-j}
$$

由于知道 $i-j$ 的范围，考虑枚举 $i-j$ 的值。令 $p=i-j$，原式可以写作 $\sum\limits_{p\geq x'-x+1}\sum\limits_{i-j=p}\binom{k}{i}\binom{k'}{k'-j}$。

由范德蒙德恒等式得，原式等于 $\sum\limits_{p\geq x'-x+1} \binom{k+k'}{p+k'}=\sum\limits_{p=x'-x+k'+1}^{k+k'} \binom{k+k'}{p}$。

由于 $k+k'$ 是定值，因此预处理前缀和即可做到查询 $\mathcal O(1)$。需要注意一些负数的细节。

此题有另一种推演方法，可以得出相同的结果，详见 [Hooch 的博客](https://www.cnblogs.com/CTHOOH/p/18076821)。

时间复杂度 $\mathcal O(n+v+q)$。

[AC record](https://codeforces.com/contest/1948/submission/251630017)

```cpp
int n, q, a[MAXN], b[MAXN], sa[MAXN], sb[MAXN];
ll fac[MAXN], inv[MAXN], sum[MAXN]; const int mod = 998244353;
 
il ll qpow(ll a, int b) {
	ll ans = 1;
	while (b) {
		if (b & 1) (ans *= a) %= mod;
		(a *= a) %= mod; b >>= 1;
	} return ans;
}
 
il ll C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
 
il int query(int l, int r, int *a) {
	return a[r] - a[l - 1];
}
 
int main() {
	read(n, q); rer(i, 1, n, a); rer(i, 1, n, b);
	rep1(i, 1, n) sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i];
	fac[0] = 1;
	rep1(i, 1, 1e6) fac[i] = fac[i - 1] * i % mod;
	inv[int(1e6)] = qpow(fac[int(1e6)], mod - 2);
	rep2(i, 1e6 - 1, 0) inv[i] = inv[i + 1] * (i + 1) % mod;
	
	sum[0] = 1;
	rep1(i, 1, sb[n]) sum[i] = (sum[i - 1] + C(sb[n], i)) % mod;
	
	const ll g = qpow(qpow(2, sb[n]), mod - 2);
	int l, r; while (q--) {
		read(l, r);
		int pre = sa[n] - 2 * query(l, r, sa) + sb[n] - query(l, r, sb);
		printf("%lld ", g * (sb[n] >= pre ? (sum[sb[n]] - (pre >= 0 ? sum[pre] : 0) + mod) : 0) % mod);
	}
	rout;
}
```

---

## 作者：2huk (赞：2)

令 $[l, r]$ 中有 $a$ 个金币，$[l,r]$ 外有 $b$ 个金币。$[l, r]$ 中有 $c$ 个银币，$[l, r]$ 外有 $d$ 个银币。

不妨枚举 $[l, r]$ 中有多少银币的价值为 $1$，$[l, r]$ 外有多少银币的价值为 $1$。令为 $x, y$。那么如果 $(x, y)$ 满足以下条件，就应将 $\dbinom cx \dbinom dy$ 累加入答案。

- $0 \le x \le c$
- $0 \le y \le d$
- $a+x > b+y$

其中第三条等价于 $x-y\ge b-a+1$。接下来令 $k=b-a+1$。

既然 $x,y$ 的差值不低于 $k$，那么不妨枚举这个差值 $p \in [k,c]$（上限 $c$ 在 $x$ 最大，$y$ 最小时取到）。那么答案为：

$$
\sum_{p=k}^{c} \sum_{y=0}^d \dbinom c{y+p}\dbinom dy
$$

~~可以证明~~我们来证明一下后面这个和式的答案为 $\dbinom {c+d}{d+p}$。

$$
\begin{aligned}
\sum_{y=0}^d \dbinom c{y+p}\dbinom dy &= 
\sum_{y=0}^d \dbinom c{(c-p)-y}\dbinom dy \\
&= \dbinom {c+d}{c-p} \\
&= \dbinom {c+d}{d+p}
\end{aligned}
$$

其中倒数第二步用到了范德蒙德卷积。证明考虑其组合意义，等式右边指从 $c+d$ 个物品中选择 $c-p$ 个的方案数，于是枚举 $i$ 表示在前 $c$ 个物品中选了 $i$ 个，那么剩下的 $c-p-i$ 个物品就应从后 $d$ 个中选，也就是等式左边的意义。

所以答案：

$$
\sum_{p=k}^{c} \dbinom {c+d}{d+p}
$$

换个记号：

$$
\sum_{p=k+d}^{c+d} \dbinom {c+d}{p}
$$

注意到对于每次询问 $c+d$ 的值是固定的，是整个序列的银币总数。所以预处理上指标为 $c+d$ 的组合数，再前缀和即可。

<https://codeforces.com/contest/1948/submission/291181927>

---

## 作者：HHH6666666666 (赞：2)

题目基本可以转化为：给你两堆银币分别为 $a$ 个与 $b$ 个，求 $P(value(a) - value(b) \geq c)$，其中 $value(x)$ 为 $x$ 个银币的价值。

直接求显然不可做。主要难点在于两堆中银币对答案的贡献是相反的。然而由于概率为 $\frac{1}{2}$，有：

$$ P(b - value(b) = i) = P(value(b)  = i) $$

这个式子的另一种理解是将那 $b$ 个银币的初始价值视为 $1$，有 $\frac{1}{2}$ 的概率变为 $0$，这样一来两堆中对答案的贡献方向相同。

令 $m = a+b$，根据题意其为定值。转化原式：

$$\begin{aligned} &P(value(a) - (b - value(b)) \geq c)\\ =&P(value(a) + value(b) \geq c + b)\\ =&\frac{\sum\limits_{i=c+b}^{m}\binom{m}{i}}{2^m}
\end{aligned}$$

后缀和计算即可。注意关于 $c+b$ 范围的特判。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 3e5 + 10;
const int MAXV = 1e6 + 10;
const int V = 1e6;
const int MOD = 998244353;

int n, q;
int a[MAXN], b[MAXN];
ll fac[MAXV], inv[MAXV];
ll sum[MAXV];

ll qpow(ll x, int y) {
    ll res = 1; x %= MOD;
    while (y) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}
ll C(ll x, ll y) {
    if (x < y) return 0;
    return fac[x] * inv[y] % MOD * inv[x - y] % MOD;
}

signed main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i], a[i] += a[i - 1];
    for (int i = 1; i <= n; ++i) cin >> b[i], b[i] += b[i - 1];
    fac[0] = 1;
    for (int i = 1; i <= V; ++i) fac[i] = fac[i - 1] * i % MOD;
    inv[V] = qpow(fac[V], MOD - 2);
    for (int i = V - 1; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % MOD;
    int m = b[n];
    for (int i = m; i >= 0; --i) sum[i] = (sum[i + 1] + C(m, i)) % MOD;
    ll iv = qpow(qpow(2, m), MOD - 2);
    while (q--) {
        int l, r; cin >> l >> r;
        int s = a[r] - a[l - 1];
        int c = b[n] - (b[r] - b[l - 1]) + (a[n] - s) - s + 1;
        // 注意这里的特判
        if (c < 0) cout << 1 << ' ';
        else if (c > m) cout << 0 << ' ';
        else cout << iv * (sum[c] % MOD) % MOD << ' ';
    }
    cout << endl;
    return 0;
}

```

---

## 作者：唐一文 (赞：2)

不太会这种题。

首先概率可以变成满足要求的方案数除以总方案数。

容易发现，对于一次询问的答案，只与区间内的金币数量 $A$，区间外的金币数量 $B$，区间内的银币数量 $C$，区间外的银币数量 $D$ 有关。

每个银币有两种方案，那么总方案数就是 $2^{C+D}$。

满足要求的方案数要咋算呢。一个很笨的想法是，枚举区间内有 $i$ 个价值为 $1$ 的银币，区间外有 $j$ 个价值为 $1$ 的银币，那么方案数为 $\binom{C}{i}\binom{D}{j}$，当 $A+i>B+j$ 时满足要求。

笔者往下不太会推了。换一种想法，考虑一个组合意义：

有一个长度为 $C+D$ 的序列和一个变量 $s$。对于前 $C$ 个位置，每个位置可以填 $0$ 或 $1$；对于后 $D$ 个位置，每个位置都可以填 $0$ 或 $-1$。初始时 $s=A$，在序列上从左往右走，$s$ 到一个位置就加上这个位置上的数，问最后 $s>B$ 的方案数。

这个问题和原问题很明显是对应的。

考虑统一一下这 $C+D$ 个位置的取值：将后 $D$ 个位置上的数加一，那么问题变成：每个位置填 $0$ 或 $1$，问最后 $s>B+D$ 的方案数。

$s$ 的初值也不太好看，让 $s$ 的初值为 $0$，那么就是最后 $s>B+D-A$ 的方案数。

此时这个序列 $1$ 的个数就为 $s$。一个长度为 $C+D$ 的 $01$ 序列中有 $s$ 个 $1$ 的方案数为 $\binom{C+D}{s}$。答案即为
$$
\sum_{s>B+D-A}\binom{C+D}{s}
$$

发现 $C+D$ 是固定的，为整个序列中银币的数量。那么这个式子只需要预处理一个后缀和即可。

[code](https://codeforces.com/contest/1948/submission/251642297)

---

## 作者：IceKylin (赞：2)

### CF1948F Rare Coins 题解

*2500 数数题。

考虑将每个问题转化为以下形式：袋子 A 有 $x$ 个银币，袋子 B 有 $y$ 个银币，设袋子 A 的价值为 $v_a$，袋子 B 的价值为 $v_b$，求 $\text{P}(v_a-v_b>z)$。

接下来给出一个很牛的 Trick：

$$\text{P}(v_b=k)=P(v_b=y-k)$$

那么就有：

$$\text{P}(v_a-v_b>z)=\text{P}(v_a-(y-v_b)>z)=\text{P}(v_a+v_b>y+z)$$

上式中 $v_a+v_b$ 可以理解为合并袋子 A 和 B 之后的结果，所以答案为：

$$\frac{\displaystyle\sum_{i=y+z+1}^{x+y}{x+y\choose i}}{2^m}$$

由于 $x+y$ 表示所有银币的数量，为定值，所以预处理组合数后缀和即可。

注意特判 $y+z+1$ 过大或过小的情况。

AC 代码：[link](https://codeforces.com/contest/1948/submission/254424536)。

---

## 作者：Gold14526 (赞：2)

$\rm Problem:$[Rare Coins](https://www.luogu.com.cn/problem/CF1948F)

### 题意

有 $n(1\le n\le3\times10^5)$ 个包，第 $i$ 个包里有 $a_i(0\le a_i,\sum a_i\le10^6)$ 个金币和 $b_i(0\le b_i,\sum b_i\le10^6)$ 个银币，金币的价值是 $1$，每一枚银币的价格都等概率取 $0$ 或 $1$。

有 $q(1\le q\le3\times10^5)$ 次询问，每次询问给出 $l,r(1\le l\le r\le n)$，求背包 $[l,r]$ 的价值之和严格大于其它背包价值之和的概率，对 $998244353$ 取模。

### 做法

对于询问区间 $[l,r]$，设其中分别有 $a_{in},b_{in}$ 枚金币、银币，其外分别有 $a_{out},b_{out}$ 枚金币、银币，不难用前缀和处理、求出。

于是，要求的是 $b_{in}$ 枚银币的价值减 $b_{out}$ 枚银币的价值严格大于 $a_{out}-a_{in}$ 的概率。

考虑如何求出 $b_{in}$ 枚银币的价值减 $b_{out}$ 枚银币的价值等于 $k$ 的方案数。

为了方便说明，我们这样理解：每一枚银币正面表示 $1$ 的价值，反面表示 $0$ 的价值。

现在让那内部的 $b_{in}$ 枚银币全都翻到正面，剩下的都翻到反面，这样内部的价值会比外面多 $b_{in}$。

如果我们翻一个银币呢？

不难发现无论翻的是内部的还是外部的，里面的价值都会比外面多 $b_{in}-1$。

一般的，如果翻 $m$ 个银币，里面的价值会比外面得多 $b_{in}-m$，那么如果希望里面的价值比外面多 $k$ 的话，就要翻 $b_{in}-k$ 个，方案数就是 $C_{b_{in}+b_{out}}^{b_{in}-k}$。

设 $tot_b$ 表示 $b$ 的总和，不难发现，$b_{in}+b_{out}$ 始终等于 $tot_b$，方案数可表示为 $C_{tot_b}^{b_{in}-k}$。

现在再来考虑里面的价值减外面的价值严格大于 $a_{out}-a_{in}$ 的方案数，显然这个数为：
$$\sum\limits_{a_{out}-a_{in}\le i\le b_{in}}C_{tot_b}^{b_{in}-i}$$

可以用前缀和优化，这样每次查询就是 $O(1)$ 的。

注意上面求的是方案数，所以最后还要除以 $2^{tot_b}$。

时间复杂度 $O(n+q+\sum b_i)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
cint mod=998244353;
int r[1000001],tc[1000001],tr[1000001];
void init()
{
	r[1]=tc[0]=tc[1]=tr[0]=tr[1]=1;
	for(int i=2;i<=1000000;++i)
	{
		r[i]=1ll*(mod-mod/i)*r[mod%i]%mod;
		tc[i]=1ll*tc[i-1]*i%mod;
		tr[i]=1ll*tr[i-1]*r[i]%mod;
	}
}
iint C(cint x,cint y)
{
	if(x<y||y<0)return 0;
	return 1ll*tc[x]*tr[y]%mod*tr[x-y]%mod;
}
int s[1000002];
int sa[300001],sb[300001];
int n,q,base=1;
int qpow(cint x,cint y)
{
	if(y==0)return 1;
	cint t=qpow(x,y>>1);
	if(y&1)return 1ll*t*t%mod*x%mod;
	return 1ll*t*t%mod;
}
void query()
{
	cint l=read();
	cint r=read();
	cint a=sa[n]-2*sa[r]+2*sa[l-1],b=sb[r]-sb[l-1];
	if(b<=a)puts("0");
	else printf("%d ",1ll*s[min(b-a-1,sb[n])]*base%mod);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	n=read();
	q=read();
	for(int i=1;i<=n;++i)
	{
		sa[i]=sa[i-1]+read();
	}
	for(int i=1;i<=n;++i)
	{
		sb[i]=sb[i-1]+read();
	}
	s[0]=C(sb[n],0);
	for(int i=1;i<=sb[n];++i)
	{
		s[i]=(s[i-1]+C(sb[n],i))%mod;
		base=2ll*base%mod;
	}
	base=qpow(base,mod-2);
	while(q--)query();
	return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

显然只有银币有作用，设金币总数为 $c_1$，银币总数为 $c_0$，选择的区间中银币个数为 $s$，所需要的银币个数（其他区间金币个数减去选择的区间中金币个数）为 $k$，$x$ 个银币的价值为 $v(x)$。则答案为 $P(v(s) - v(c_0 - s) > k)$。

显然是不能直接算的，但又因为概率为 $\frac 1 2$，所以对于每个可能的 $v(x)$，都存在一种情况，使得 $v(x) = x - v'(x)$，于是可以推柿子：

$$
\begin{aligned}
& P(v(s) - v(c_0 - s) > k) \\
= & P(v(s) - (c_0 - s - v(c_0 - s)) > k) \\
= & P(v(s) + v(c_0 - s) > k + c_0 - s)
\end{aligned}
$$

显然 $v(x)$ 满足 $v(x) + v(y) = v(x + y)$，所以答案即为：

$$P(v(c_0) > k + c_0 - s)$$

然后就简单了，考虑总情况数为 $2^{c_0}$，合法方案数为 $\sum \limits _{i > k + c_0 - s} \binom {c_0} i$，则答案为：

$$\frac {\sum \limits _{i > k + c_0 - s} \binom {c_0} i} {2^{c_0}}$$

发现 $c_0$ 固定，所以求个 $\binom {c_0} i$ 的后缀和就可以了。

## Code

```cpp
int n,q,a[MAXN],b[MAXN],sa[MAXN],sb[MAXN],sc[V];

signed main()
{
    read(n,q),_::r(a,n),_::r(b,n);
    rep(i,1,n) sa[i]=sa[i-1]+a[i],sb[i]=sb[i-1]+b[i];
    int c1=sa[n],c0=sb[n];

    init_inv(1);
    rpe(i,V-1,0) sc[i]=(sc[i+1]+C(c0,i))%mod;
    int iv=ginv(fpow(2ll,c0));

    int l,r,s,k,ind,ans;
    while(q--)
    {
        read(l,r);
        s=sb[r]-sb[l-1],k=(c1-(sa[r]-sa[l-1]))-(sa[r]-sa[l-1]);
        ind=k+c0-s+1;

        if(ind<0) ans=1;
        else if(ind>c0) ans=0;
        else ans=sc[ind]*iv%mod;

        write(ans,' ');
    }

    return fast_io::ot(),0;
}
```

---

## 作者：LCat90 (赞：1)

首先可以很容易地将有关金子的数据记录，记其差为 $num1$。

设区间内有 $num0$ 个银子，一共有 $m$ 个银子，则知区间外有 $m-num0$ 个。

现在就是要使区间内的银子变成 $0$ 或 $1$，区间外变成 $0$ 或 $-1$；使得最终的 $sum>0$。

-------

暴力：枚举区间内选几个，区间外选几个，单次询问就要 $O(n^2)$。

思考：我们希望将**区间内外的银币的操作尽可能统一**，这样我们就可以一起计算。考虑先假设银币可以随机加减 $\Delta x$，然后考虑修改本来的固定值。这样就可以将所有银币一起处理。

于是有一个很巧妙的转化：将区间内的银币给定值 $\frac{1}{2}$，外面则是 $-\frac{1}{2}$。每次银币随机加减 $\frac{1}{2}$。

-------------

至此，剩下的都是一些简单的推导和细节。留给读者自己思考。

比如我们每次要算一个组合数求和：$\large \sum_{i=0}^M C_{m}^i$，由于 $m$ 是一定的，我们只需要前缀和预处理即可。

还有这个 $\frac{1}{2}$ 很烦，考虑将原题的 $1$ 改成 $2$，这样就都是整数运算了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 5, Mod = 998244353, M = 2e6; int read();
int n, fac[N], q, m, ifac[N], ans, a[N], b[N]; 
int preG[N], preA[N], Pre[N];
int qkpow(int a, int b);
int C(int n, int m);
void init();

signed main() { 
	cin >> n >> q; init();
	for(int i = 1;i <= n; ++i) a[i] = read(), preG[i] = preG[i - 1] + a[i];
	for(int i = 1;i <= n; ++i) b[i] = read(), preA[i] = preA[i - 1] + b[i];
	m = preA[n]; // 可以选的银币个数 
	int inv = qkpow(qkpow(2, m), Mod - 2);
	Pre[0] = C(m, 0); for(int i = 1;i <= M; ++i) Pre[i] = (Pre[i - 1] + C(m, i)) % Mod; 
	while(q--) {
		int l = read(), r = read();
		int num1delta = 2 * (preG[r] - preG[l - 1]) - preG[n]; // 1 的个数 
		num1delta *= 2; 
		num1delta += preA[r] - preA[l - 1] - (m - (preA[r] - preA[l - 1])) - m;
		// 现在：使 num1delta > x
		// ans = \sum from [0,num1delta] (m, i) 
		num1delta /= -2;
		num1delta = m - num1delta;
		int ans = 0, rang = num1delta;  
		rang = min(rang, m + 1); 
		if(rang > 0) ans = Pre[rang - 1];  
		printf("%lld ", ans * inv % Mod);
	}
	return 0;
}
// 实现：考虑全部乘 2 一个东西的贡献是 2 or 0 
// 考虑银：[l,r] = 1/2，外 = -1/2；然后等概率加 +- 1/2

int qkpow(int a, int b) {
    if(b == 0) return 1;
    if(b & 1) return a * qkpow(a, b - 1) % Mod;
    int tmp = qkpow(a, b >> 1); return tmp * tmp % Mod;
}
int C(int n, int m) { return fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }
void init() {
    fac[0] = 1;
	for(int i = 1;i <= M + 1; ++i) fac[i] = fac[i - 1] * i % Mod;
	ifac[M + 1] = qkpow(fac[M + 1], Mod - 2);
	for(int i = M;i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % Mod;
} 
int read() {
   char c; int f = 1, sum = 0;
   while(c < '0' or c > '9') {if(c == '-') f = -1;c = getchar();}
   while(c >= '0' and c <= '9') {sum = (sum << 3) + (sum << 1) + (c ^ 48);c = getchar();} 
   return sum * f;
}
```

---

## 作者：MaxBlazeResFire (赞：1)

记范围内金币比范围外金币多 $g$ 个，范围内银币有 $S_1$ 个，范围外有 $S_2$ 个。

那么答案就是

$\displaystyle Ans=\frac{1}{2^{S_1+S_2}}\sum_{i=0}^{S_1}\binom{S_1}{i}\sum_{j=0}^{i+g-1}\binom{S_2}{j}$。

后面的组合数转化成

$\displaystyle\sum_{j=0}^{S_1+g-1}\binom{S_2}{j}\sum_{i=j-g+1}^{S_1}\binom{S_1}{i}=\sum_{j=0}^{S_1+g-1}\sum_{i=0}^{S_1+g-j-1}\binom{S_1}{i}\binom{S_2}{j}=\sum_{j=0}^{Lim}\sum_{i=0}^{Lim-j}\binom{S_2}{j}\binom{S_1}{i}=\sum_{t=0}^{Lim}\sum_{j=0}^{Lim}\sum_{i=0}^{Lim-j}\binom{S_2}{j}\binom{S_1}{i}[i+j=t]=\sum_{t=0}^{Lim}\sum_{j=0}^t\binom{S_2}{j}\binom{S_1}{t-j}=\sum_{t=0}^{Lim}\binom{S_2+S_1}{t}$。前缀和处理一下即可。

复杂度 $O(\sum (a+b)+q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 5000005
#define mod 998244353

int n,q,a[MAXN],b[MAXN],fac[MAXN],inv[MAXN],ifac[MAXN];
int pre[MAXN];

inline int C( int n , int m ){ return ( n >= m && n >= 0 && m >= 0 ) ? 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }
inline void chkequ( int &x , int k ){ x = k; if( x >= mod ) x -= mod; }

inline int fp( int x , int p ){ int res = 1; while( p ){ if( p & 1 ) res = 1ll * res * x % mod; x = 1ll * x * x % mod; p >>= 1; } return res; }

inline void solve(){
	scanf("%lld%lld",&n,&q);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]),a[i] += a[i - 1];
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&b[i]),b[i] += b[i - 1];
	pre[0] = 1;
	for( int i = 1 ; i <= b[n] ; i ++ ) chkequ( pre[i] , pre[i - 1] + C( b[n] , i ) ); 
	for( int i = 1 ; i <= q ; i ++ ){
		int l,r; scanf("%lld%lld",&l,&r);
		int S1 = b[r] - b[l - 1];
		int g = ( a[r] - a[l - 1] ) - ( a[n] - ( a[r] - a[l - 1] ) );
		int coef = fp( fp( 2 , b[n] ) , mod - 2 );
		if( S1 + g > b[n] + 1 ) printf("1 ");
		else if( S1 + ( a[r] - a[l - 1] ) <= a[n] - ( a[r] - a[l - 1] ) ) printf("0 ");
		else printf("%lld ",pre[S1 + g - 1] * coef % mod);
		
	} puts("");
}

signed main(){
	fac[0] = inv[1] = ifac[0] = 1;
	for( int i = 1 ; i < MAXN ; i ++ ) fac[i] = 1ll * fac[i - 1] * i % mod;
	for( int i = 2 ; i < MAXN ; i ++ ) inv[i] = 1ll * ( mod - mod / i ) * inv[mod % i] % mod;
	for( int i = 1 ; i < MAXN ; i ++ ) ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
	solve();
	return 0;
}
```

---

## 作者：subcrip (赞：0)

超级简单也好想的做法。

不妨设 $n_1$ 表示询问区间内银币的个数，$n_2$ 为除此之外的银币个数；设 $l_1$ 表示询问区间内金币的个数，$l_2$ 为除此之外的金币的个数。题目想让我们统计询问区间内选择 $i_1$ 个银币、除此之外选择 $i_2$ 个银币，并且满足

$$
i_1+l_1>i_2+l_2
$$

的方案数。设函数 $(1+x)^{n_1}$ 中的每一项表示询问区间内的银币选或不选；设函数 $\left(1+\dfrac 1x\right)^{n_2}$ 表示除此之外的每个银币选或不选。由于

$$
(1+x)^{n_1}\left(1+\dfrac 1x\right)^{n_2}=\sum_{i=0}^{n_1+n_2}\binom{n_1+n_2}{i}x^{i-n_2},
$$

所以只需要统计那些次数满足 $i-n_2>l_2-l_1$ 的系数和即可。也就是说，答案为

$$
\sum_{i=l_2-l_1+n_2+1}^{n_1+n_2}\binom{n_1+n_2}i.
$$

注意到 $n_1+n_2$ 是常量，于是一个前缀和就做完了。

Code：

```cpp
void solve() {
	read(int, n, q);
	readvec(int, a, n);
	readvec(int, b, n);

	int p = accumulate(b.begin(), b.end(), 0);

	vector<ll> f(p + 2);
	f[0] = 0;
	for (int i = 1; i <= p + 1; ++i) {
		f[i] = (f[i - 1] + comb(p, i - 1)) % M;
	}

	vector<int> pa(n + 1);
	vector<int> pb(n + 1);
	partial_sum(a.begin(), a.end(), pa.begin() + 1);
	partial_sum(b.begin(), b.end(), pb.begin() + 1);

	ll pw = inverse(qpow(2, p, M), M);

	while (q--) {
		read(int, l, r);
		--l, --r;

		int l1 = pa[r + 1] - pa[l];
		int l2 = pa[n] - l1;
		int n1 = pb[r + 1] - pb[l];
		int n2 = pb[n] - n1;
		cout << mod(f[p + 1] - f[clamp(l2 - l1 + n2 + 1, 0, p + 1)], M) * pw % M << ' ';
	}
	cout << '\n';
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个口袋，第 $i$ 个口袋里有 $a_i$ 个金币和 $b_i$ 个银币。

一枚金币的价值为 $1$；一枚银币有 $50\%$ 的概率价值为 $1$，$50\%$ 的概率价值为 $0$。

有 $q$ 次询问，每次询问给出区间 $[l,r]$，你需要输出区间中的所有口袋的所有钱币的价值总和，大于区间外所有口袋的钱币价值总和的概率。答案对 $998,244,353$ 取模。

$1\leq n,q\leq 3\times 10^5,0\leq \sum a_i,\sum b_i\leq 10^6$。

## 思路

大力推式子，考虑每次询问，区间内有 $G$ 个金币 $S$ 个银币，区间外有 $g$ 个金币和 $s$ 个银币，则答案为：
$$
\frac{1}{2^{S+s}}\sum_{i=0}^{S}\sum_{j=0}^{s} [G+i>g+j] \binom{S}{i}\binom{s}{j}
$$
注意到 $G+i>g+j$ 等价于 $i-j>g-G$ 即 $i-j\geq g-G+1$，于是改为枚举差值，得到：
$$
\frac{1}{2^{S+s}}\sum_{d=g-G+1}^{\infty} \sum_{j=0}^{s} \binom{S}{j+d}\binom{s}{j}
$$
这样我们就消去了不等式的限制，对于后面的形式，稍加变形，再应用范德蒙德卷积公式，得到：
$$
\frac{1}{2^{S+s}}\sum_{d=g-G+1}^{\infty} \sum_{j=0}^{s} \binom{S}{j+d}\binom{s}{s-j}
=
\frac{1}{2^{S+s}}\sum_{d=g-G+1}^{\infty}\binom{S+s}{d+s}
$$
令 $k=d+s$ 得到：
$$
\frac{1}{2^{S+s}}\sum_{k=g-G+1+s}^{S+s} \binom{S+s}{k}
$$
由于 $S+s$ 为所有口袋的银币总数 $\sum b_i$，是定值，于是可以预处理 $S+s$ 为上指标的组合数后缀和，来做到预处理 $O(n+\sum b_i)$，单次 $O(1)$。

## 代码

实现忘记保存 $\frac{1}{2^{S+s}}$ 的值了，退化为单次 $O(\log \sum b_i)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

int fastpow(int x, int y){
    int ret = 1;
    for(;y;y>>=1,x=Mul(x, x)){ if(y & 1) ret = Mul(ret, x); }
    return ret;
}

int n, q, a[N], b[N], fact[N], inv[N], f[N];

int binom(int n, int m){ return n < m ? 0 : Mul(fact[n], Mul(inv[m], inv[n - m])); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i], a[i] += a[i - 1];
    for(int i=1;i<=n;i++) cin >> b[i], b[i] += b[i - 1];
    fact[0] = inv[0] = fact[1] = inv[1] = 1;
    for(int i=2;i<=b[n];i++){
        fact[i] = Mul(fact[i - 1], i);
        inv[i] = Mul(inv[mod % i], mod - mod / i);
    }
    for(int i=2;i<=b[n];i++) inv[i] = Mul(inv[i - 1], inv[i]);
    for(int i=b[n];~i;i--) f[i] = Add(f[i + 1], binom(b[n], i));
    while(q--){
        int l, r; cin >> l >> r;
        int A = a[r] - a[l - 1], B = b[r] - b[l - 1], C = a[n] - A, D = b[n] - B;
        int tmp = min(max(C - A + D + 1, 0), b[n] + 1);
        cout << Mul(fastpow(2, mod - 1 - b[n]), f[tmp]) << ' ';
    }
    cout << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：arrow_king (赞：0)

# 题目大意

给定 $n$ 个袋子，第 $i$ 个袋子中有 $a_i$ 个金币和 $b_i$ 个银币。金币的价值固定为 $1$，银币的价值有 $0.5$ 的概率是 $1$，有 $0.5$ 的概率是 $0$。$q$ 次询问，每次询问给出 $[l,r]$，求 $[l,r]$ 内袋子中钱币的总价值大于 $[l,r]$ 外袋子中钱币的总价值的概率。$n,q\le3\times10^5$，$\sum a_i,\sum b_i\le10^6$。

# 思路

首先可以等价的将 $[l,r]$ 内袋子合并，记其中有 $A$ 块金币和 $B$ 块银币，区间外有 $A^\prime$ 块金币和 $B^\prime$ 块银币。由于金币的价值恒定不变，因此问题又等价于求 $B$ 块银币的价值减去 $B^\prime$ 块银币的价值大于 $A^\prime-A$ 的方案数（因为总方案数显然是所有银币的取值方案数，就是 $2^{B+B^\prime}$）。

这个问题直接做很难，因为 $B$ 的贡献是正的，但是 $B^\prime$ 的贡献是负的。但是我们注意到一个有用的、能将 $B^\prime$ 的贡献转成正的方法：因为每个硬币是否有价值的概率都是 $0.5$，同时它们是独立的事件。因此我们记 $b_i$ 为第 $i$ 枚银币价值对应的随机变量，则有
$$
\mathrm P(b=1)=1-\mathrm P(b=0)=1-\mathrm P(b=1)
$$
所以
$$
\mathrm P\left(\sum_{i=1}^Bb_i=k\right)=B-\mathrm P\left(\sum_{i=1}^Bb_i=k\right)
$$
可以化简得到
$$
\begin{aligned}
\mathrm P\left(\sum_{i=1}^Bb_i-\sum_{i=1}^{B^\prime} b_i>c\right)&=\mathrm P\left(\sum_{i=1}^Bb_i+\sum_{i=1}^{B^\prime} b_i>c+B^\prime\right)\\
&=\mathrm P\left(\sum_{i=1}^{B+B^\prime}b_i>c+B^\prime\right)\\
&=\dfrac{1}{2^{B+B^\prime}}\sum_{k=c+B^\prime+1}^{B+B^\prime}\dbinom{B+B^\prime}{k}
\end{aligned}
$$
这个公式没有什么通项公式，因此就打一个后缀和即可。查询的复杂度是 $O(1)$。

注意特判 $c+B^\prime<0$ 或者 $>B+B^\prime$ 的情况。

---

## 作者：ifffer_2137 (赞：0)

组合推柿子题。
### 题意
（转化后题意）$x_i$ 和 $y_i$ 是两个每一位在 $\{0,1\}$ 之间独立等概率随机的无限长数列。给定常数 $N$，每次给出 $m,k$ 然后询问：
$$\text{P}\{\sum_{i=1}^m x_i-\sum_{i=1}^{N-m}y_i\ge k\}$$
对 $998244353$ 取模。
### 分析
考虑算方案数再除以 $2^N$。

然后列个柿子，先枚 $y_i$ 里取到 $1$ 的个数，再枚 $x_i$ 里取到 $1$ 的个数：
$$\sum_{i=0}^{N-m}\dbinom{N-m}{i}\sum_{j=0}^{m}\dbinom{m}{i+k+j}$$
然后交换求和顺序：
$$
\begin{aligned}
{}&\sum_{j=0}^{m}\sum_{i=0}^{N-m}\dbinom{m}{i+k+j}\dbinom{N-m}{i}\\
=&\sum_{j=0}^{m}\sum_{i=0}^{N-m}\dbinom{m}{m-i-k-j}\dbinom{N-m}{i}\\
=&\sum_{j=0}^{m}\dbinom{m+N-m}{m-i-k-j+i}\\
=&\sum_{j=0}^{m}\dbinom{N}{m-k-j}\\
\end{aligned}
$$
倒数第二步用了范德蒙德卷积。然后预处理组合数前缀和即可，时间复杂度 $O(n+q\log V)$
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e6+5;
const int mod=998244353;
namespace Comb{
	int fac[maxn],inv[maxn];
	int pre[maxn];
	int pw(int a,int x){
		int s=1;
		while(x){
			if(x&1) s=s*a%mod;
			a=a*a%mod; x>>=1;
		}
		return s;
	}
	void init(){
		fac[0]=1;for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
		inv[maxn-1]=pw(fac[maxn-1],mod-2);
		for(int i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	}
	int C(int n,int m){
		if(n<m||n<0||m<0) return 0;
		return fac[n]*inv[m]%mod*inv[n-m]%mod;
	}
	void getpre(int x){
		pre[0]=1;
		for(int i=1;i<=x;i++) pre[i]=(pre[i-1]+C(x,i))%mod;
	}
}
using namespace Comb;
//----------------------
int n,q;
int a[maxn],b[maxn];
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	init();
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++) b[i]=b[i-1]+read();
	getpre(b[n]);
	while(q--){
		int l=read(),r=read();
		int A=a[r]-a[l-1],B=b[r]-b[l-1],C=a[n]-A,D=b[n]-B;
		int T=C-A+1;
		if(B-T<0){
			cout<<0<<'\n';
			continue;
		}
		int ans=pre[min(b[n],B-T)];
		cout<<ans*pw(pw(2,b[n]),mod-2)%mod<<'\n';
	}
	return 0;
}
```

---

