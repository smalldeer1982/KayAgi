# 「RiOI-03」A Journey to the Moonlight

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/hi1cu7o7.png)

（图片来自 phigros 曲绘，侵删。）

[加强版链接](/problem/P10286)

KDOI 的业务发展到月亮上了。但是月亮上网速很慢，他们需要解决网速问题。

KDOI 的工作人员研发了一种新型无线局域网模块 Wife（WIreless Fidelity Extend），每个模块最多连接两个用户，并且可以选择为其中一位客户提供 $1$ 单位带宽。不过，无论有多少个模块同时为一位客户提供带宽，他的总带宽永远是 $1$。

公司的员工都很懒，经常 ppt 一鸽就是一个月。因此，他们也懒得为 Wife 贴上标签，也就是所有模块间不做区分。另外，为了节省电费，不能有两个模块的工作客户范围完全相同。

现在有 $n$ 个用户购买了服务。当 Wife 系统正式启动时，鹿由器发现了一个问题：可能有些用户没有宽带可以使用！快斗现在手里没有 Wife，只能抢来一个，牺牲一个用户的利益，按一定顺序给所有包括有宽带的用户使用。然而，没有宽带的用户们要求很苛刻，只要没有给他们按注册顺序连续地提供宽带，他们就会威胁鹿由器退钱。

快斗已经忘了他们的注册时间了，只能随机选一个 $1\sim n$ 的排列来决定提供宽带的顺序。为了让尝试的次数尽量小，他会调整 Wife 连接的用户。他想知道，要让这些顾客平息愤怒，需要尝试的最小期望次数是多少。

特别的，Wife 有两种型号。型号 $1$ 可以选择只连接一位，型号 $2$ 则只能连接两个不同客户。你需要分别计算出这两种型号的答案。

快斗自己肯定~~不~~会做，所以他要让你求出所有 $i\in[0,n]$ 的结果 $ans_i$。考虑到你如果一个一个汇报会累死的，仁慈的鹿由器会给你数组 $a$，让你输出 $\sum a_i\times ans_i$。



## 题目描述

#### 【形式化题意】

对于一个右部点为 $m$ 个的二分图 $G$，定义它的权值 $w(G)$ 如下：

- 选择一种匹配方案，标记第一个已匹配的右部点。如果不存在这样的点，那么标记第一个未匹配的右部点。
- 每次随机选择一个 $1,2,\cdots,m$ 的排列，当未匹配的右部点与被标记的点 **按标号顺序作为一个子段出现在排列中时** 停止操作。
- $w(G)$ 为在所有匹配方案中操作次数期望的 **最小值**。

将这个二分图 $G$ 定义为 **$k$ 合法** 的，当且仅当：

- 所有左部点的度数在 $k\sim 2$ 之间。
- 没有任意两个左部点，与其相邻的点组成的集合相同。

定义 $f(k,x)$ 为所有右部点 $x$ 个，左部点不进行区分的 $k$ 合法二分图 $G$ 的 $w(G)$ 之和。

给定 $n,k,a_{0\sim n}$，求 $\sum\limits^n_ia_if(k,i) \bmod998244353$。

## 说明/提示

约定一个左部点连接了编号为 $x,y$ 的右部点表示为 $(x,y)$。

#### 【样例 1 解释】

对于 $n=0,1$，答案显然为 $1,2$。

对于 $n=2$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1),(2),(1,2)$

$\{(1),(2)\},\{(1,2),(2)\},\{(1,2),(1)\},\{(1,2),(1),(2)\}$

期望相同的二分图被分为一组。答案为 $\dfrac21+\dfrac21\times3+\dfrac22\times4=12$，输出 $1\times1+1\times2+1\times12=15$。

#### 【样例 2 解释】

对于 $n=0,1,2$，答案为 $1,1,4$。

对于 $n=3$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1,2),(1,3),(2,3)$

$\{(1,2),(1,3)\},\{(1,2),(2,3)\},\{(1,3),(2,3)\}$

$\{(1,2),(2,3),(1,3)\}$

答案为 $\dfrac61+\dfrac61\times3+\dfrac62\times3+\dfrac66=34$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le n\le1.5\times10^4$，$1\le k\le2$，$0\le a_i<998244353$。

**本题开启捆绑测试**

|$\text{Subtask}$|$\text{Score}$|$n\le $|$k\ge$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$0$|$5$|$5$|$1$||
|$1$|$10$|$500$|$2$||
|$2$|$20$|$500$|$1$|$a_i\equiv\dfrac1{i!}$|
|$3$|$20$|$1.5\times10^4$|$2$|$a_i\equiv\dfrac1{i!}$|
|$4$|$45$|$1.5\times10^4$|$1$||

## 样例 #1

### 输入

```
2 1
1 1 1```

### 输出

```
15```

## 样例 #2

### 输入

```
3 2
1 1 1 1```

### 输出

```
40```

## 样例 #3

### 输入

```
12 1
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
721168027```

# 题解

## 作者：Register_int (赞：7)

显然在最大匹配下题面中函数的值最小，设最大匹配数为 $k$，则答案为：

$$\dfrac{n!}{(k-1)!\times k}=\dfrac{n!}{k!}$$

组合意义为枚举连续段位于排列的哪个位置。有 $k=0$ 的 corner，但容易验证也满足该式。那么问题转化为对关于最大匹配的计数。

先不考虑度数为 $1$ 的点。此时是一个二度点二分图匹配问题。考虑左点转为无向边后的无向图，由条件得无重边。那么最大匹配即为节点数减去图中树的个数。问题转化为对恰好有 $k$ 棵树的无向图个数。

容易得知单棵树的 $\text{EGF}$ 为 $F(x)=\sum_i\dfrac{i^{i-2}}{i!}x^i$，$k$ 棵树组成的森林则为 $\dfrac{F^k(x)}{k!}$。

其余部分需要保证联通块都不为树。考虑无向图的 $\text{EGF}$ 为 $A(x)=\sum_i\dfrac{2^{\binom i2}}{i!}x^i$，有自环为 $\sum_i\dfrac{2^{\binom{i+1}2}}{i!}x^i$ 。则不为树的连通无向图的 $\text{EGF}$ 为 $\ln A(x)-F(x)$，因此不要求连通的 $\text{EGF}$ 为 $G(x)=A(x)/\exp F(x)$。

对树的个数进行枚举，可得：

$$
\begin{aligned}
ans_n&=\sum^n_i\dfrac{n!}{(n-i)!}\times n![x^n]\dfrac{F^i(x)}{i!}G(x)\\
&=\sum^n_i\dbinom ni\times n![x^n]F^i(x)G(x)\\
&=n![x^n]G(x)\sum^n_i\dbinom niF^i(x)\\
&=n![x^n]G(x)(F(x)+1)^n\\
\end{aligned}
$$

分块：

$$
\begin{aligned}
&\sum^n_ii!x^i[x^i]G(x)(F(x)+1)^i\\
=&\sum^{L}_i\sum^L_j(iL+j)!x^{iL+j}[x^{iL+j}]G(x)(F(x)+1)^{iL+j}\\
=&\sum^{L}_i\sum^L_j(iL+j)!x^{iL+j}[x^{iL+j}]\left((F(x)+1)^{iL}\times G(x)(F(x)+1)^j\right)\\
\end{aligned}
$$

预处理 $(F(x)+1)^{iL}$ 与 $G(x)(F(x)+1)^j$，单点相乘的复杂度为 $O(n)$，总时间复杂度为 $O(n^2+n\sqrt n\log n)$。

下面这一版是造数据的代码，最大点 $1.87\text s$。标程最大点 $1.19\text s$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define _POW_OPTIMIZE_FOR_K

namespace polynomial {
	
	typedef long long ll;
	
	vector<int> rev;
	
	int ig[17][1 << 16];
	
	int getrev(int n) {
	    int l = 1 << __lg(2 * n - 1) + 1; rev.resize(l);
	    for (int i = 1; i < l; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? l >> 1 : 0);
	    return l;
	}
	
	const int mod = 998244353;
	
	int add(int x, int y) { x += y; return x < mod ? x : x - mod; }
	int sub(int x, int y) { x -= y; return x < 0 ? x + mod : x; }
	
	void tadd(int &x, int y) { (x += y) < mod || (x -= mod); }
	void tsub(int &x, int y) { (x -= y) < 0 && (x += mod); }
	
	int qpow(int b, int p) {
	    int res = 1;
	    for (; p; b = (ll)b * b % mod, p >>= 1) if (p & 1) res = (ll)res * b % mod;
	    return res;
	}
	
	int inv(int n) { return qpow(n, mod - 2); }
	
	const int gw = 3;
	
	inline 
	void init() {
		for (int i = 0; i < 17; i++) {
			int w = qpow(3, (mod - 1) / (1 << i + 1)); ig[i][0] = 1;
			for (int j = 1; j < 1 << i; j++) ig[i][j] = (ll)ig[i][j - 1] * w % mod;
		}
	}
	
	template 
	<typename T> 
	class poly {
		
	private:
		vector<T> func;
		
	public:
		T &operator [] (int n) { return func[n]; }
		T operator [] (int n) const { return func[n]; }
		void resize(size_t n) { func.resize(n); }
		size_t size() const { return func.size(); }
		void push_back(T x) { func.push_back(x); }
		T &back() { return func.back(); }
		auto begin() { return func.begin(); }
		auto end() { return func.end(); }
		void clear() { func.clear(); }
		void reverse() { ::reverse(begin(), end()); }
		
		poly<T>() {}
		poly<T>(int n) { resize(n); }
		~poly<T>() {}
		
		void ntt(bool t) {
			int n = size();
		    for (int i = 0; i < n; i++) if (i < rev[i]) swap(func[i], func[rev[i]]);
		    for (int i = 1; i < n; i <<= 1) {
		        int *tg = ig[__lg(i)], w;
		        for (int j = 0; j < n; j += i << 1) {
		            for (int k = j; k < i + j; k++) {
		                w = (ll)func[i + k] * tg[k - j] % mod;
		                func[i + k] = sub(func[k], w), func[k] = add(func[k], w);
		            }
		        }
		    }
		    if (t) {
		        int q = qpow(n, mod - 2);
		        for (int i = 0; i < n; i++) func[i] = (ll)func[i] * q % mod;
		        ::reverse(next(begin()), end());
		    }
		}
		
		void print() {
			int n = size();
			for (int i = 0; i < n; i++) printf("%lld ", func[i]); puts("");
		}
	
	public: 
		poly operator + (const poly &rhs) const {
			int n = size(), m = rhs.size(); poly res(max(n, m));
			for (int i = 0; i < max(n, m); i++) res[i] = add(i < n ? func[i] : 0, i < m ? rhs[i] : 0);
			return res;
		}
		poly operator - (const poly &rhs) const {
			int n = size(), m = rhs.size(); poly res(max(n, m));
			for (int i = 0; i < res.size(); i++) res[i] = sub(i < n ? func[i] : 0, i < m ? rhs[i] : 0);
			return res;
		}
		poly operator * (const poly &rhs) const {
			int n = size(), l = getrev(n);
			poly f = *this, g = rhs; g.resize(n);
			poly res(l); f.resize(l), g.resize(l), f.ntt(0), g.ntt(0);
			for (int i = 0; i < l; i++) res[i] = (ll)f[i] * g[i] % mod;
			res.ntt(1), res.resize(n);
			return res;
		}
		poly operator / (const poly &rhs) const {
			if (size() < rhs.size()) return 0;
			poly f = *this, g = rhs; f.reverse(), g.reverse();
			g.resize(size() - rhs.size() + 1), g = inv(g) * f, g.reverse();
			return g;
		}
		poly operator % (const poly &rhs) const {
			if (size() < rhs.size()) return *this;
			poly a = *this - rhs * (*this / rhs); a.resize(rhs.size() - 1);
			return a;
		}
		
		poly operator << (const int &rhs) const {
			int n = size(); poly f = *this;
			for (int i = 0; i < n - rhs; i++) f[i] = f[i + rhs]; f.resize(n - rhs);
			return f;
		}
		poly operator >> (const int &rhs) const {
			int n = size(); poly f = *this; f.resize(n + rhs);
			for (int i = n + rhs - 1; i >= rhs; i--) f[i] = f[i - rhs];
			for (int i = rhs - 1; i >= 0; i--) f[i] = 0;
			return f;
		}
		
		poly operator - () const {
			poly res = *this; int n = size();
			for (int i = 0; i < n; i++) res[i] = mod - res[i];
			return res;
		}
		
		poly &operator += (const poly &rhs) { return *this = *this + rhs; }
		poly &operator -= (const poly &rhs) { return *this = *this - rhs; }
		poly &operator *= (const poly &rhs) { return *this = *this * rhs; }
		poly &operator /= (const poly &rhs) { return *this = *this / rhs; }
		poly &operator %= (const poly &rhs) { return *this = *this % rhs; }
		poly &operator <<= (const int &rhs) { return *this = *this << rhs; }
		poly &operator >>= (const int &rhs) { return *this = *this >> rhs; }
		
		poly operator + (const T &rhs) const {
			poly res = *this;
			size() ? (tadd(res[0], rhs), 0) : (res.push_back(rhs), 0);
			return res;
		}
		poly operator - (const T &rhs) const {
			poly res = *this;
			size() ? (tsub(res[0], rhs), 0) : (res.push_back(mod - rhs), 0);
			return res;
		}
		poly operator * (const T &rhs) const {
			poly res = *this; int n = size();
			for (int i = 0; i < n; i++) res[i] = (ll)res[i] * rhs % mod;
			return res;
		}
		
		poly &operator += (const T &rhs) { return *this = *this + rhs; }
		poly &operator -= (const T &rhs) { return *this = *this - rhs; }
		poly &operator *= (const T &rhs) { return *this = *this * rhs; }
	};
	
	template 
	<typename T> 
	poly<T> inv(poly<T> f) {
		int s[30], t, n; poly<T> g, a;
	    for (t = 0, n = f.size(); n > 1; n = n + 1 >> 1) s[++t] = n;
	    for (g += inv(f[0]); t; t--) {
	    	int l = getrev(s[t]); g.resize(l), a.resize(l);
	    	for (int i = 0; i < s[t]; i++) a[i] = f[i];
	    	for (int i = s[t]; i < l; i++) a[i] = 0;
	    	a.ntt(0), g.ntt(0);
	    	for (int i = 0; i < l; i++) g[i] = (ll)sub(2, (ll)a[i] * g[i] % mod) * g[i] % mod;
	    	g.ntt(1), g.resize(s[t]);
		}
		return g;
	}
	
	template 
	<typename T> 
	poly<T> differential(const poly<T> &f) {
		int n = f.size(); poly<T> g(n);
		for (int i = 1; i < n; i++) g[i - 1] = (ll)i * f[i] % mod;
		return g;
	}
	
	template 
	<typename T> 
	poly<T> integral(const poly<T> &f) {
		int n = f.size(); poly<T> g(n);
		for (int i = 1; i < n; i++) g[i] = (ll)f[i - 1] * qpow(i, mod - 2) % mod;
		return g;
	}
	
	template 
	<typename T> 
	poly<T> ln(const poly<T> &f) {
		return integral(differential(f) * inv(f));
	}

	template 
	<typename T> 
	poly<T> exp(poly<T> f) {
		int s[30], t, n; poly<T> a, g;
	    for (t = 0, n = f.size(); n > 1; n = n + 1 >> 1) s[++t] = n;
	    for (g += 1; t; t--) {
	    	g.resize(s[t]), a = ln(g);
		    for (int i = 1; i < s[t]; i++) a[i] = sub(f[i], a[i]);
		    g *= a + 1;
		}
		return g;
	}
	
	template 
	<typename T> 
	poly<T> pow(poly<T> f, ll k) {
		int n = f.size(), p;
		for (p = 0; p < n; p++) if (f[p]) break;
		if (p == n || p * k >= n) { f.resize(0), f.resize(n); return f; }
		f <<= p; int x = qpow(f[0], k);
		poly<ll> g = ln(f * inv(f[0])); f = exp(g * k), f *= x;
		f >>= p * k, f.resize(n);
		return f;
	}
	
}

using namespace polynomial;

const int MAXN = 1.5e4 + 10;

int fac[MAXN], ifac[MAXN], tk[MAXN], p2[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
	tk[1] = 1;
	for (int i = 2; i <= n; i++) tk[i] = qpow(i, i - 2);
	*p2 = 1;
	for (int i = 1; i <= n; i++) p2[i] = (p2[i - 1] << 1) % mod;
}

template 
<typename T> 
poly<T> solve(poly<T> f, poly<T> g) {
	vector<poly<T>> b1, b2;
	int n = f.size(), l = getrev(n), b = sqrt(n) + 1; f.resize(l);
	b1.resize(b + 1), b2.resize(b); b1[1] = f, f.ntt(0);
	b1[0].resize(l), b2[0].resize(l); b1[0][0] = b2[0][0] = 1; 
	for (int i = 2; i <= b; i++) {
		poly<T> &pre = b1[i - 1], &nw = b1[i]; nw.resize(l), pre.ntt(0);
		for (int j = 0; j < l; j++) nw[j] = (ll)f[j] * pre[j] % mod;
		pre.ntt(1), nw.ntt(1);
		for (int j = n; j < l; j++) nw[j] = 0;
	}
	poly<T> bb = b1[b]; b2[1] = bb, bb.ntt(0);
	for (int i = 2; i < b; i++) {
		poly<T> &pre = b2[i - 1], &nw = b2[i]; nw.resize(l), pre.ntt(0);
		for (int j = 0; j < l; j++) nw[j] = (ll)bb[j] * pre[j] % mod;
		pre.ntt(1), nw.ntt(1);
		for (int j = n; j < l; j++) nw[j] = 0;
	}
	for (int i = 0; i <= b; i++) b1[i] *= g;
	poly<T> ans(n);
	for (int i = 0; i < b; i++) {
		const poly<T> &af = b2[i];
		for (int j = 0; j < b; j++) {
			int x = i * b + j; const poly<T> &bf = b1[j];
			if (x >= n) break;
			for (int k = 0; k <= x; k++) tadd(ans[x], (ll)af[k] * bf[x - k] % mod);
		}
	}
	for (int i = 0; i < n; i++) ans[i] = (ll)ans[i] * fac[i] % mod;
	return ans;
}

int n, k, ans, t = 1, a[MAXN];

poly<int> f, g;

int main() {
	polynomial::init();
	scanf("%d%d", &n, &k), init(++n), f.resize(n), g.resize(n);
	for (int i = 0; i < n; i++) g[i] = (ll)t * ifac[i] % mod, t = (ll)t * p2[i + 2 - k] % mod;
	for (int i = 0; i < n; i++) f[i] = (ll)tk[i] * ifac[i] % mod; g *= inv(exp(f)), f[0]++;
	g = solve(f, g);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]), ans = (ans + (ll)a[i] * g[i] % mod) % mod;
	printf("%lld", ans);
}
```

---

