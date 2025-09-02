# [POI 2020/2021 R3] 收藏家 2 / Kolekcjoner Bajtemonów 2

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Kolekcjoner Bajtemonów 2](https://szkopul.edu.pl/problemset/problem/yI8VISW680r7ktJAPvA5QPkl/statement/)。

试机题。

## 题目描述

给你 $n$ 个数对，你要进行 $n$ 次二选一，这样你就有了 $n$ 个数，最大化这 $n$ 个数的 $\gcd$。

## 说明/提示

对于所有数据，$1\leq n\leq 10^6$，$1\leq a_i\leq 5\times 10^5$，$1\leq b_i<2^{63}$。

对于 $42pts$ 的数据，$n\leq 5000$。

## 样例 #1

### 输入

```
4
5 7
10 15
13 20
7 5
```

### 输出

```
5```

## 样例 #2

### 输入

```
2
18900 22050
14700 17640
```

### 输出

```
7350```

## 样例 #3

### 输入

```
见附件```

### 输出

```
2```

# 题解

## 作者：_•́へ•́╬_ (赞：13)

## 思路

首先可以全选 $b$。

如果选了任何一个 $a$，那么答案不会超过 $5\times 10^5$。考虑枚举这个答案。

结论：对于两对数，如果它们的 $a$ 相同，那么可以合并，新的 $b$ 为它们的 $b$ 的 $\gcd$。

理由：选一个 $a$ 一个 $b$ 肯定不优于选两个 $a$。

所以 $n\leq 10^6$ 是吓人的。

然后 ST 表随便维护一下就好了。

具体地，枚举答案，把非答案倍数的 $a$ 对应的 $b$，$\gcd$ 起来，如果得到的是答案的倍数，那就可行。

复杂度 $\mathcal O(a\log a)$。这里我没算 $\gcd$ 产生的 $\log$，因为[位运算优化的 `gcd`](/discuss/442855) 太 tm 快了。

## code

```cpp
#include<stdio.h>
#define N 500001
#define LG 19
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>>63?-(x):(x))
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
inline void read(long long&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,lg[N];long long a[N],tmp,st[LG][N],ans,gg;
inline long long gcd(long long x,long long y)
{
	if(!x||!y)return x|y;
	if(x==1||y==1)return 1;
	int cx=__builtin_ctzll(x),cy=__builtin_ctzll(y),z=min(cx,cy);
	y>>=cy;
	for(long long diff;x;
		x>>=cx,cx=__builtin_ctzll(diff=x-y),y=min(x,y),x=abs(diff));
	return y<<z;
}
inline void get(const int&l,const int&r)
	{int i=lg[r-l];ans=gcd(ans,st[i][l]);ans=gcd(ans,st[i][r-(1<<i)+1]);}
main()
{
	read(n);
	for(int x;n--;read(x),read(tmp),a[x]=gcd(a[x],tmp),gg=gcd(gg,tmp));
	for(int i=2;i<N;lg[i]=lg[i>>1]+1,++i);
	for(int i=1;i<N;st[0][i]=a[i],++i);
	for(int i=1;i<LG;++i)for(int j=1;j<N;++j)
		if(j+(1<<i-1)<N)st[i][j]=gcd(st[i-1][j],st[i-1][j+(1<<i-1)]);
		else st[i][j]=st[i-1][j];
	for(int i=N-1;i>gg;--i)
	{
		ans=0;get(1,i-1);
		if((N-1)%i)get((N-1)/i*i+1,N-1);
		for(int j=2;i*j<N&&!(ans%i);++j)get(i*(j-1)+1,i*j-1);
		if(!(ans%i)){printf("%d",i);return 0;}
	}
	printf("%lld",gg);
}
```

---

## 作者：Tmbcan (赞：4)

## [P9401 [POI 2020/2021 R3] Kolekcjoner Bajtemonów 2](https://www.luogu.com.cn/problem/P9401)
### 题目描述
给定 $n$ 个数对，在每个数对中选一个数，最大化所选的 $n$ 个数的最大公约数。
### 思路
先看数据范围 $1\le a\le 5\times 10^5$ 而 $1\le b<2^{63}$。  
发现 $b_i$ 比 $a_i$ 大很多，且如果要选择一个 $a_i$ 那么最终的答案一定 $1\le ans \le 5\times 10^5$。  
所以考虑先预处理出所有 $b_i$ 的最大公约数，再枚举所有可能的 $ans$，通过最终答案来选择将一些 $b_i$ 替换为 $a_i$。  
具体地：  
对于 $ans\mid a_i$ 直接选 $a_i$；对于 $ans\nmid a_i$ 就只能选 $b_i$。

如何进行维护和优化：  
1. 考虑基于值域进行处理。令 $X_{a_i} = b_i$，此时更新答案需要求 $X$ 中 $\frac{n}{ans}$ 个区间的 $b_i$ 的 GCD。用 ST 表维护区间 GCD，每次暴力查询判断答案是否合法。
2. 如果使用循环递归求 GCD 其常数十分大会被卡飞，请使用[二进制求 GCD](https://rainppr.github.io/blog/math/number-theory/gcd/#stein-binary-gcd:~:text=Stein%20%E7%AE%97%E6%B3%95%20/-,Binary%20GCD,-%C2%B6)。

复杂度分析：  
1. ST 表预处理 GCD 单次查询 $O(\log{b})$；
2. 总查询次数为调和级数 $O(\sum_{i=1}^n \frac{n}{i}) = O(n\ln{n})$。

[代码](https://www.luogu.com.cn/paste/wlhh6hnu)总复杂度 $O(n\ln{n}\log{b})$。

---

## 作者：Alex_Wei (赞：4)

### [P9401 [POI2020-2021R3] Kolekcjoner Bajtemonów 2](https://www.luogu.com.cn/problem/P9401)

一个 $\mathcal{O}((n + d(V)) \log V)$ 的做法，甚至可以做 $1\leq a_i, b_i < 2 ^ {63}$。

答案要么是 $a_1$ 的因数，要么是 $b_1$ 的因数，所以考虑 $\mathrm{solve}(x)$ 表示在 $x$ 的因数内寻找答案。

首先特判全选 $b_i$ 的情况，答案不大于 $5\times 10 ^ 5$。对 $x$ 分解质因数且只保留不大于 $5\times 10 ^ 5$ 的质因子。设得到分解 $X = \prod_{i = 1} ^ k p_i ^ {c_i}$，其中 $p_i$ 是不大于 $5\times 10 ^ 5$ 的质数。

对每个 $a_i$ 和 $b_i$（$2\leq i\leq n$），将 $\gcd(a_i, X)$ 的所有因子出现次数加 $1$，将 $\gcd(b_i, X)$ 的所有因子出现次数加 $1$，但是这样将导致 $\gcd(\gcd(a_i, b_i), X)$ 的所有因子出现次数多算了 $1$，要减掉。最后找到最大的出现次数为 $n - 1$ 的因子作为答案。

对于形如 “将 $i\mid d$ 的 $f_i$ 加上 $v$” 的操作，将 $f_i$ 加上 $v$，处理完所有操作后狄利克雷后缀和。相当于对第 $i$ 维大小是 $c_i + 1$ 的 $k$ 维数组做高维后缀和。因为 $\prod (c_i + 1) = d(X) \leq d(x)$，所以这部分复杂度是 $d(V)\log V$。

求 $\gcd(a_i, X)$ 和 $\gcd(b_i, X)$ 太慢了，直接对每个 $p_j$ 求出 $a_i$ 和 $b_i$ 分别有多少个质因子 $p_j$，此时 $\gcd(a_i, b_i)$ 含有多少个质因子 $p_j$ 也是容易算的。但是取模依然有点慢。注意到只对所有 $p_i$ 取模，所以对每个质因子预处理 FastMod（Barrett Reduction）就跑得飞快。

上述做法可以处理 $1\leq a_i, b_i < 2 ^ {63}$ 的情况，但需要 Pollard-rho 分解质因数（实际上可以不需要，但做法较复杂）。

时间复杂度是 $\mathcal{O}((n + d(V))\log V)$。可以选最小的 $b_i$ 以及对应的 $a_i$，跑得更快。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ui = unsigned int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using ull = unsigned long long;
using vint = vector<int>;
using vll = vector<ll>;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd(20060130);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

char buf[1 << 25], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + \
  fread(buf, 1, 1 << 25, stdin), p1 == p2) ? EOF : *p1++)
inline ll read() {
  ll x = 0;
  char s = getc();
  while(!isdigit(s)) s = getc();
  while(isdigit(s)) x = x * 10 + s - '0', s = getc();
  return x;
}

#define putc(x) putchar(x)
inline void print(ui x) {
  if(x >= 10) print(x / 10);
  putc(x % 10 + '0');
}

// ---------- templates above ----------

constexpr int N = 1e6 + 5;
constexpr int D = 3e5 + 5;

pii pf[20];
int mnb = 1, f[D], a[N];
ll n, ans, b[N];
struct FastMod {
  ull b, m;
  void init(ull b) {this->b = b, m = ull((lll(1) << 64) / b);}
  bool reduce(ll &a) {
    ull q = ull((lll(m) * a) >> 64);
    ull r = a - q * b;
    r >= b && (r -= b, q++);
    return r ? 0 : (a = q, 1);
  }
} F[20];

void solve(ll x) {
  memset(f, 0, D << 2);
  ll tmp = x;
  int tot = 1, sz = 0;
  for(int i = 2; i <= 5e5 && tmp > 1; i++) {
    if(tmp % i) continue;
    int cnt = 1;
    while(tmp % i == 0) tmp /= i, cnt++;
    F[sz].init(i);
    pf[sz++] = {i, cnt};
    tot *= cnt;
  }
  assert(tot <= D);
  for(int i = 1; i <= n; i++) {
    if(i == mnb) continue;
    ll a = ::a[i], b = ::b[i];
    ll ida = 0, idb = 0, idc = 0, c = 1;
    for(int i = 0; i < sz; i++) {
      int ca = 0, cb = 0;
      while(F[i].reduce(a) && ++ca < pf[i].second - 1);
      while(F[i].reduce(b) && ++cb < pf[i].second - 1);
      int cc = min(ca, cb);
      ida += ca * c, idb += cb * c, idc += cc * c;
      c *= pf[i].second;
    }
    f[ida]++, f[idb]++, f[idc]--;
  }
  for(int i = 0, c = 1; i < sz; i++) {
    for(int j = tot - 1; ~j; j--) {
      int v = j / c % pf[i].second;
      if(v) f[j - c] += f[j];
    }
    c *= pf[i].second;
  }
  for(int j = 0; j < tot; j++) {
    if(f[j] < n - 1) continue;
    ll rep = 1;
    for(int i = 0, c = 1; i < sz; i++) {
      int v = j / c % pf[i].second;
      while(v--) rep *= pf[i].first;
      c *= pf[i].second;
    }
    ans = max(ans, rep);
  }
}
void mian() {
  n = read();
  for(int i = 1; i <= n; i++) {
    a[i] = read(), b[i] = read();
    if(b[i] < b[mnb]) mnb = i;
    ans = __gcd(ans, b[i]);
  }
  solve(a[mnb]), solve(b[mnb]);
  cout << ans << "\n";
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  // cin >> T;
  while(T--) mian();
  fprintf(stderr, "%d ms\n", int(1e3 * clock() / CLOCKS_PER_SEC));
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：dead_X (赞：3)

先特判掉全选 $b$ 的情况。

考虑如果选了一个 $a$，那么答案一定 $\leq 5\times 10^5$。

然后枚举答案，假设我们枚举了 $x$ 作为答案，它合法当且仅当 $a_i\bmod x >0\Rightarrow b_i|x$。

然后显然 $a_i\bmod x>0$ 只有 $\lceil\frac{n}{x}\rceil$ 个区间，写个 ST 表维护区间查询 $\gcd$。

$O(a\log^2a+n\log a)$。有点卡常，记得剪枝。

---

## 作者：zzx0102 (赞：2)

我们可以先全选 $b_i$，然后只能选 $a_i$，这样答案一定不大于 $a_i$。

如果两个 $(a_i,b_i)$ 和 $(a_j,b_j)$，当 $a_i=a_j$ 时，可以将两个数对合并为 $(a_i,\gcd(b_i,b_j))$，因为选一 $a$ 一 $b$ 肯定不如两个 $a$。

然后枚举答案 $ans$，当 $ans\mid a_i$ 时，一定可行，然后我们记 $B_{a_i}=b_i$，对 $B$ 数组建立 ST 表，然后看 $[k\times ans+1,(k+1)\times ans-1]$  的 $\gcd$  能不能被 $ans$ 整除即可。

复杂度 $\mathcal{O(a\log^2a)}$，过不了，所以考虑使用超快 $\gcd$。

$$
\gcd(a,b) = 
\left \{
\begin{aligned}
&\gcd(b,a-b)\ && a\bmod 2=1\ b\bmod 2=1 \\
&\gcd(\dfrac{a}{2},b)\ && a\bmod 2=0\ b\bmod 2=1 \\
&\gcd(a,\dfrac{b}{2})\ && a\bmod 2=1\ b\bmod 2=0 \\
&\gcd(\dfrac{a}{2},\dfrac{b}{2})\times 2\ && a\bmod 2=0\ b\bmod 2=0 \\
\end{aligned}
\right.
$$

这样快速递归虽然理论上也是 $\mathcal{O}(\log a)$，但是实际上常数极小且很容易一次就完事了，所以可以当成 $\mathcal{O}(1)$ 的。

注意有些地方要开 `long long`，加超快读。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define I inline
const int N = 1000010, M = 500010;
int n, a[N], maxa; ll b[N], G;
ll B[M], g[M][19];
#define ctz __builtin_ctzll
ll gcd(ll a, ll b) {
	if(!a || !b) return a + b;
    ll az = ctz(a);
    ll bz = ctz(b);
    ll z = min(az, bz);
    b >>= bz;
    while(a) {
        a >>= az;
        ll det = a - b;
        az = ctz(det);
        b = min(a, b);
		a = labs(det);
    }
    return b << z;
}
#define gc getchar
I ll read() {
	ll x = 0; char ch = gc();
	while(ch < '0' || ch > '9') ch = gc();
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
	return x;
}
void ST() {
	for(int i = 1; i <= maxa; i++) g[i][0] = B[i];
	for(int i = 1; i < 19; i++)
		for(int j = 1; j + (1 << i) <= maxa + 1; j++)
			g[j][i] = gcd(g[j][i - 1], g[j + (1 << i - 1)][i - 1]);
}
ll ask(int l, int r) {
	int k = __lg(r - l + 1);
	return gcd(g[l][k], g[r - (1 << k) + 1][k]);
}
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read(); b[i] = read();
		maxa = max(maxa, a[i]);
		if(i == 1) G = b[i];
		else G = gcd(G, b[i]);
	}
	if(G >= maxa) {cout << G; return 0;}
	for(int i = 1; i <= n; i++) {
		if(!B[a[i]]) B[a[i]] = b[i];
		else B[a[i]] = gcd(B[a[i]], b[i]);
	}
	ST();
	for(int i = maxa; i > G; i--) {
		bool flag = 1;
		for(int j = 1; j <= maxa; j += i) {
			int l = j, r = min(j + i - 2, maxa);
			if(ask(l, r) % i) {
				flag = 0;
				break;
			}
		}
		if(flag) cout << i, exit(0);
	}
	cout << G;
	return 0;
}
```

---

## 作者：strcmp (赞：1)

提供一个纯不动脑子的做法。

先特判掉全部选 $b_i$ 的情况，特判完后答案 $\le 5 \times 10^5$。

考虑枚举 $\text{gcd} = k$。

然后找出 $a$ 中所有 $k$ 的倍数，根据调和级数的结论枚举所有 $k$，那么 $a$ 中 $k$ 的倍数的个数至多是 $\Theta(n \ln n)$ 级别的。它们之间的那些东西显然只能选 $b$。

于是你用 ST 表在 $b$ 上跑一个区间 GCD 即可。

时间复杂度 $\Theta(n \ln n \log V)$。

好了如果你直接写肯定收获一个 TLE 42pts。

两个关键常数优化：

1. 把 gcd 的实现改为基于位运算的快速 gcd。

2. 对于相同的 $a_i$，可以将它们合并为一个，然后令新的 $b$ 为这坨 $a_i$ 的 gcd。

为啥能合并？考虑你要么不取这坨 $a_i$，要么全取这坨 $a_i$。因为如果取了一部分 $a_i$，那这坨的 gcd 上界就定死了是 $a_i$，要么一定是 $a_i$ 的因数。而我们全取就取到这个上界了。因此要么全取要么不取。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pq = priority_queue<int>;
using ld = double;
constexpr int maxn = 1e6 + 10, mod = 1e9 + 7; 
int n, a[maxn], lg[maxn], vis[maxn]; ll b[maxn], s[21][maxn];
inline ll gcd(ll a, ll b) {
	if (!a || !b) return a | b;
    ll az = __builtin_ctzll(a);
    ll bz = __builtin_ctzll(b);
    ll z = min(az, bz);
    b >>= bz;
    while (a) {
        a >>= az;
        ll diff = a - b;
        az = __builtin_ctzll(diff);
        b = min(a, b), a = abs(diff);
    }
    return b << z;
}
inline ll rmq(int l, int r) {
    int g = lg[r - l + 1];
    return gcd(s[g][l], s[g][r - (1 << g) + 1]);
}
int t[maxn], c[maxn], p = 0;
inline int solve(int k) {
    int lst = 0; c[++p] = n + 1;
    rep(i, 1, p) {
        int x = c[i];
        if (lst + 1 <= x - 1) {
            ll w = rmq(lst + 1, x - 1);
            if (w % k) return 0; 
        }
        lst = x;
    }
    return 1;
}
pil d[maxn];
int main() {
    scanf("%d", &n); lg[0] = -1; int mx = 0;
    rep(i, 1, n) scanf("%d%lld", &d[i].X, &d[i].Y);
    sort(d + 1, d + n + 1); int N = 0; ll now = 0;
    rep(i, 1, n) {
    	if (d[i].X != d[i - 1].X) now = d[i].Y, a[++N] = d[i].X, b[N] = d[i].Y;
    	else b[N] = gcd(b[N], d[i].Y);
    }
    n = N;
    rep(i, 1, n) mx = max(mx, a[i]), t[a[i]] = i, lg[i] = lg[i >> 1] + 1;
    rep(i, 1, n) s[0][i] = b[i]; int ans = 0;
    rep(i, 1, lg[n]) rep(j, 1, n - (1 << i - 1)) s[i][j] = gcd(s[i - 1][j], s[i - 1][j + (1 << i - 1)]);
    ll MX = rmq(1, n);
    if (MX > mx) printf("%lld\n", MX), exit(0);
    rep(i, 2, mx) {
        for (int j = i; j <= mx; j += i) if (t[j]) if (!vis[t[j]]) c[++p] = t[j], vis[t[j]] = 1;
        rep(j, 1, p) vis[c[j]] = 0;
        if (p) {
            sort(c + 1, c + p + 1);
            if (solve(i)) ans = i; p = 0;
        }
    }
    printf("%lld\n", max((ll)ans, MX));
    return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

一些可能会用到的定理：

$\textbf{Lemma}$ 对于任意的一个 $\le x$ 的正整数 $y$，任意的正整数 $z$ 和 $y$ 的 $\gcd$ 即 $\gcd(y,z)$ 必然有 $\gcd(y,z)\le x$。

-------------------------------------

注意到 $a_i\le 5\times 10^5,b_i<2^{63}$。也就是说若选择了至少一个 $a$ 组中的数，根据前面的 $\textbf{Lemma}$，她们的 $\gcd$ 的值必然不会超过 $5\times 10^5$。

所以特判掉全部选择 $b$ 组中的数的答案，其他的情况考虑枚举最后的答案 $\gcd$ 的值。问题在于如何判断当前的 $\gcd$ 的值是否可行。

很显然的，因为 $a_i$ 的范围很小，所以新设立一个数组 $c$ 满足 $c_{a_i}=b_i$。判断 $k$ 是否是一组可行的答案当且仅当 $[1,k-1],[k+1,2\times k-1],[2\times k+1,3\times k-1],\ldots$ 在数组 $c$ 中的所有的区间的 $\gcd$ 是否都是 $k$ 的倍数。因为是静态的所以考虑使用一个 ST 表来维护。加上处理 $\gcd$ 的时间复杂度是 $O(n\log^2n)$ 的，卡卡常可过。

---

## 作者：SegTree (赞：1)

+ 给你 $n$ 个数对 $(a_i,b_i)$，你要进行 $n$ 次二选一，这样你就有了 $n$ 个数，最大化这 $n$ 个数的 $\gcd$。
+ $1\leq n\leq 10^6$，$1\leq a_i\leq 5\times 10^5$，$1\leq b_i<2^{63}$。


------------
发现 $a_i\le 5\times 10^5$，说明二选一中只要选了 $a_i$ 答案就一定不超过 $5\times 10^5$。所以需要单考虑全选 $b_i$ 的情况。

对于选 $a_i$ 的情况，直接枚举答案。对于所有非 $x$ 倍数的 $a_i$，$b_i$ 一定是 $x$ 的倍数，此时 $x$ 才符合条件。

于是用 $a_i$ 为下标 $b_i$ 为值，那么等价于查询 $[1,x-1],[x+1,2x-1],\cdots$ 的区间 $\gcd$。可以使用 ST 表维护。显然对于 $x$ 只需要查询 $\dfrac{V}x$ 个区间（$V$ 是值域）。显然如果忽略 $\gcd$ 的复杂度这是 $\mathcal{O}(V\log V)$。

本题如果用普通的 `gcd` 实现的话相当卡常，使用 Binary Gcd 常数更小一些。

[代码。](https://www.luogu.com.cn/paste/aee76bay)

---

## 作者：Purslane (赞：0)

# Solution

如果 $b$ 并不是全选，那么答案 $\le 5 \times 10^5$，因此考虑判定每个数是否能够成为答案。

维护数组 $s_i$，我们需要对 $\forall x \nmid a_i$，$s_x \leftarrow \gcd(s_x,b_i)$。

只需要一个质数 $p$ 满足 $v_p(x) > v_p(s_i)$，就不整除。

这是容易维护的，找到几个点做高维前缀和即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,tot,m=500000,sv[MAXN],a[MAXN],Lst[MAXN],lst[MAXN],rnk[MAXN],flg[MAXN];
ll b[MAXN],pre[MAXN];
vector<int> vc;
inline void init(const int mx) {
	sv[1]=1;
	ffor(i,2,mx) {
		if(!flg[i]) sv[i]=i,lst[i]=i,Lst[i]=i,vc.push_back(i),rnk[i]=++tot;
		for(auto v:vc) {
			if(i*v>mx) break ;
			flg[i*v]=1,lst[i*v]=v;
			if(i%v==0) {sv[i*v]=sv[i],Lst[i*v]=Lst[i]*v;break ;}
			Lst[i*v]=v,sv[i*v]=sv[i]*v;
		}
	}
	return ;
}
inline vector<pair<int,ll>> gain(int a) {
	vector<pair<int,ll>> ans;
	while(a!=1) ans.push_back({lst[a],1ll*Lst[a]*lst[a]}),a/=Lst[a];
	return ans;
}
namespace DS {
	ll tag[MAXN<<2];
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	inline void update(const int k,const int l,const int r,const int x,const int y,const ll v) {
		if(x<=l&&r<=y) return tag[k]=gcd(tag[k],v),void();
		if(x<=mid) update(lson,l,mid,x,y,v);
		if(y>mid) update(rson,mid+1,r,x,y,v);
		return ;
	}
	inline void dfs(const int k,const int l,const int r,ll v) {
		v=gcd(v,tag[k]);
		if(l==r) pre[vc[l-1]]=gcd(pre[vc[l-1]],v);
		else dfs(lson,l,mid,v),dfs(rson,mid+1,r,v);
		return ;
	}
};
class IO_helper{
private:
	static const int L = 1 << 16;
	char in_buf[L], *in_st, *out_st;

	char _getc(){
		if (in_st == out_st)
		{
			out_st = (in_st = in_buf) + fread(in_buf, 1, L, stdin);
			if (in_st == out_st) return EOF;
		}
		return *in_st++;
	}
public:
	template <typename IntType>
	IO_helper &operator>>(IntType &x){
		bool ok=0;
		char c; while ((c = _getc()) < '0' || c > '9')ok|=c=='-';
		for (x = 0; c >= '0' && c <= '9'; c = _getc())
			x = x * 10 + c - '0';
		x=(ok?-x:x);
		return *this;
	}
} IO;
ll yh[MAXN],tmp[MAXN];
signed main() {	
	IO>>n;
	ffor(i,1,n) IO>>a[i]>>b[i],tmp[a[i]]=gcd(tmp[a[i]],b[i]);
	n=0;
	ffor(i,1,m) if(tmp[i]) ++n,a[n]=i,b[n]=tmp[i];
	init(m);
	ffor(i,1,n) {
		auto vc=gain(a[i]);
		int mul=sv[a[i]];
		yh[mul]=gcd(yh[mul],b[i]);
		for(auto pr:vc) if(pr.second<=m) pre[pr.second]=gcd(pre[pr.second],b[i]);
	}
	ffor(i,1,m) if(yh[i]) {
		int psl=i;
		vector<int> vc;
		while(psl!=1) vc.push_back(rnk[lst[psl]]),psl/=lst[psl];
		vc.push_back(tot+1);
		int lst=0;
		for(auto id:vc) {
			if(lst!=id-1) DS::update(1,1,tot,lst+1,id-1,yh[i]);
			lst=id;	
		}
	}
	DS::dfs(1,1,tot,0);
	for(auto p:vc) ffor(i,1,m/p) pre[i*p]=__gcd(pre[i*p],pre[i]);
	ll ans=0;
	ffor(i,1,n) ans=__gcd(ans,b[i]);
	ffor(i,1,m) if(pre[i]%i==0) ans=max(ans,1ll*i);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lzh301 (赞：0)

## Solution
首先可以全选 $b_i$，这样可以得到一个答案。

否则你一定会选择至少一个 $a_i$，那么答案会被限制在 $[1,\max a_i]$。

考虑到如果你不选 $a_i$，就一定要选 $b_i$。

记 $c_x=\gcd_{a_i=x}b_i$ 那么可以得到一个做法，假设答案为 $d$，判定是否可行：

对于任意的 $k$，如果 $\gcd_{kd<i<(k+1)d}c_i$ 是 $d$ 的倍数，那么 $d$ 就是可行的。
区间静态 $\gcd$，考虑使用 ST 表，做到单次 $O(\log a)$ 的区间查询。

由于调和级数 $\sum\dfrac{n}{i}=O(n\log n)$ 综上，我们得到了一个 $O(n\log n\log a)$ 的做法，可以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define maxn 500005
#define val 20
#define rg register
using namespace std;
int x,n,tmp,eco,ans,t;
int mem[maxn],a[maxn],s[val][maxn];
inline int gcd(int a, int b) {
    if(a==0)return b;
    if(b==0)return a;
    int shift=0;
    while(((a|b)&1)==0){ 
        a>>=1;
        b>>=1;
        shift++;
    }
    while((a&1)==0)a>>=1;
    do{
        while((b&1)==0)b>>=1;
        if(a>b)swap(a,b);
        b-=a;
    }while(b!=0);
    return a<<shift;
}
inline void process(const int&l,const int&r){
	t=mem[r-l];
	eco=gcd(eco,s[t][l]);
	eco=gcd(eco,s[t][r-(1<<t)+1]);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(rg int i=1;i<=n;i++){
		cin>>x>>tmp;
		a[x]=gcd(a[x],tmp);ans=gcd(ans,tmp);
	}
	for(rg int i=2;i<=500000;i++)mem[i]=mem[i>>1]+1;
	for(rg int i=1;i<=500000;i++)s[0][i]=a[i];
	for(rg int i=1;i<=18;i++)
	for(rg int j=1;j<=500000;j++){
		if(j+(1<<i-1)<=500000)s[i][j]=gcd(s[i-1][j],s[i-1][j+(1<<i-1)]);
		else s[i][j]=s[i-1][j];
	}
	for(rg int i=500000;i>ans;i--){
		eco=0;process(1,i-1);
		if(500000%i)process(500000/i*i+1,500000);
		for(int j=2;i*j<=500000&&(!(eco%i));j++)process(i*(j-1)+1,i*j-1);
		if(!(eco%i)){cout<<i<<"\n";return 0;}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

