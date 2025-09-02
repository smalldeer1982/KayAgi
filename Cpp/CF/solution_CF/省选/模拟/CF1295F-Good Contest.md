# Good Contest

## 题目描述

An online contest will soon be held on ForceCoders, a large competitive programming platform. The authors have prepared $ n $ problems; and since the platform is very popular, $ 998244351 $ coder from all over the world is going to solve them.

For each problem, the authors estimated the number of people who would solve it: for the $ i $ -th problem, the number of accepted solutions will be between $ l_i $ and $ r_i $ , inclusive.

The creator of ForceCoders uses different criteria to determine if the contest is good or bad. One of these criteria is the number of inversions in the problem order. An inversion is a pair of problems $ (x, y) $ such that $ x $ is located earlier in the contest ( $ x < y $ ), but the number of accepted solutions for $ y $ is strictly greater.

Obviously, both the creator of ForceCoders and the authors of the contest want the contest to be good. Now they want to calculate the probability that there will be no inversions in the problem order, assuming that for each problem $ i $ , any integral number of accepted solutions for it (between $ l_i $ and $ r_i $ ) is equally probable, and all these numbers are independent.

## 说明/提示

The real answer in the first test is $ \frac{1}{2} $ .

## 样例 #1

### 输入

```
3
1 2
1 2
1 2```

### 输出

```
499122177```

## 样例 #2

### 输入

```
2
42 1337
13 420```

### 输出

```
578894053```

## 样例 #3

### 输入

```
2
1 1
0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
2
1 1
1 1```

### 输出

```
1```

# 题解

## 作者：xht (赞：13)

题意即 $a_i$ 在 $[l_i, r_i]$ 等概率随机，求 $a_{1 \dots n}$ 不增的概率。

跟 [P3643 [APIO2016]划艇](https://www.luogu.com.cn/problem/P3643) 几乎一样：$a_i$ 在 $[l_i, r_i]$ 等概率随机，也可以跳过，求形成的序列递增的方案数。

先考虑这题。

首先将区间离散化成若干个左闭右开的区间。

设 $f_{i, j}$ 表示考虑到 $a_i$，$a_i$ 在第 $j$ 个区间内的方案数。

枚举上一个在 $j$ 之前的位置 $a_k$ 转移。

设 $k + 1 \sim i$ 中有 $c$ 个位置可以选择第 $j$ 个区间，设第 $j$ 个区间的长度为 $l_j$，则方案数为 $\binom{l_j + c}{c}$。

需要前缀和优化，时间复杂度 $\mathcal O(n^3)$。

```cpp
const int N = 507;
int n, a[N], b[N], c[N*2], t;
modint f[N], g[N], ans;

int main() {
	rd(n);
	for (int i = 1; i <= n; i++)
		rd(a[i]), rd(b[i]), c[++t] = a[i], c[++t] = ++b[i];
	sort(c + 1, c + t + 1), t = unique(c + 1, c + t + 1) - (c + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(c + 1, c + t + 1, a[i]) - c,
		b[i] = lower_bound(c + 1, c + t + 1, b[i]) - c;
	f[0] = 1;
	for (int j = 1; j < t; j++) {
		int l = c[j+1] - c[j];
		g[0] = 1;
		for (int i = 1; i <= n; i++) g[i] = g[i-1] * (l + i - 1) / i;
		for (int i = n; i; i--)
			if (a[i] <= j && j < b[i])
				for (int c = 1, k = i - 1; ~k; k--) {
					f[i] += g[c] * f[k];
					if (a[k] <= j && j < b[k]) ++c;
				}
	}
	for (int i = 1; i <= n; i++) ans += f[i];
	print(ans);
	return 0;
}
```

再来看原题就很简单了，照着做即可。

```cpp
const int N = 57;
int n, a[N], b[N], c[N*2], t;
modint f[N], g[N], ans;

int main() {
	rd(n);
	for (int i = 1; i <= n; i++)
		rd(a[i]), rd(b[i]), c[++t] = a[i], c[++t] = ++b[i];
	sort(c + 1, c + t + 1), t = unique(c + 1, c + t + 1) - (c + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(c + 1, c + t + 1, a[i]) - c,
		b[i] = lower_bound(c + 1, c + t + 1, b[i]) - c;
	f[0] = 1;
	for (int j = t - 1; j; j--) {
		int l = c[j+1] - c[j];
		g[0] = 1;
		for (int i = 1; i <= n; i++) g[i] = g[i-1] * (l + i - 1) / i;
		for (int i = n; i; i--)
			if (a[i] <= j && j < b[i])
				for (int c = 1, k = i - 1; ~k; k--, ++c) {
					f[i] += g[c] * f[k];
					if (a[k] > j || j >= b[k]) break;
				}
	}
	ans = f[n];
	for (int i = 1; i <= n; i++) ans /= c[b[i]] - c[a[i]];
	print(ans);
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：11)

趁着刚刚写出这一道题，赶紧写题解巩固。

题意：$a_i$ 在 $[l_i,r_i]$ 等概率随机，求 $a_{1\cdots n}$ 单调不增的概率。

做法：明显可以转化为求 $a_{1\cdots n}$ 单调不增的方案数。容易想到令 $dp_{i,j}$ 标示已经选了 $i$ 个数，且 $a_i = j $ 的方案数。明显 $dp_{i, j} = \sum_{j \le k} dp_{i-1, k}$

然后，我们再想一想怎么优化这个 DP。转移方程基本上也只能长这个样子，所以我们只能从状态入手来优化。本题中值域较大，我们可以先将原题中的区间变为左闭右开，然后再进行离散化。那么此时，每一个区间 $[l_i,r_i)$ 都可以由若干个形如 $[j,j+1)$ 的单位区间构成。这也是我们可以这样进行 DP 的原因。

此时我们设 $dp_{i, j}$ 表示 $a_i$ 的范围在单位区间 $[j, j + 1)$ 内，所形成序列单调不增的方案数。转移也比较类似，但要稍作更改。因为如果由 $dp_{i-1, j}$ 转移至 $dp_{i, j}$ 时， $a_{i-1}$ 与 $a_i$ 虽然都在 $[j, j+1)$ 内，但是 $a_{i-1}$ 仍然有可能小于 $a_i$。于是我们可以枚举一个 $k$，使得 $k + 1$ 到 $i$ 的所有数都在一个单位区间内，这样就可以正确的统计这种情况。令 $len$ 标示 $[j,j+1)$ 实际的长度，那选出 $i-k$ 个数单调不增的方案便是 $\binom{len+i - k-1}{i-k}$。具体的转移方程写起来会有点长，就不在这里列了，可以参考一下代码。最后别忘了除以总方案数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 60;
int g[N], c[N << 1], tt, a[N], b[N], inv[N], n, f[N][N << 1];
const int P = 998244353;
int power(int a, int b) {
	int c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = 1ll * c * a % P;
		a = 1ll * a * a % P;
	}
	return c;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", a + i, b + i);
		c[++tt] = a[i];
		c[++tt] = ++b[i];
	}
	sort(c + 1, c + tt + 1);
	tt = unique(c + 1, c + tt + 1) - c - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(c + 1, c + tt + 1, a[i]) - c;
		b[i] = lower_bound(c + 1, c + tt + 1, b[i]) - c;
	}
	for (int i = 1; i <= n; ++i) inv[i] = power(i, P - 2);
	a[0] = 1, b[0] = tt + 1;
	for (int i = 1; i <= tt; ++i) f[0][i] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = a[i]; j < b[i]; ++j) {
			int len = c[j + 1] - c[j];
			g[1] = len;
			for (int k = 2; k <= i; ++k) g[k] = 1ll * g[k - 1] * (len + k - 1) % P * inv[k] % P;
			for (int k = i - 1; k >= 0; --k) {
				f[i][j] += 1ll * f[k][j + 1] * g[i - k] % P;//C(len + i - k - 1, i - k)  
				f[i][j] %= P;
				if (j < a[k] || j >= b[k]) break;
			}
		}
		for (int j = tt - 1; j; --j) {
			f[i][j] += f[i][j + 1];
			f[i][j] %= P;
		}
	}
	int ans = f[n][1];
	for (int i = 1; i <= n; ++i) ans = 1ll * ans * power(c[b[i]] - c[a[i]], P - 2) % P;
	printf("%d", ans);
}
```

---

## 作者：_SeeleVollerei_ (赞：3)

我数组开小了一半都能过 70 个点，有点好笑了。

昨天就会了，但是懒得写，今天抽空写了一下。

朴素的方法是 $f_{i,j}$ 表示 $a_i=j$ 时，$a_{[1,i]}$ 的方案数，暴力转移即可。复杂度 $O(na^2)$。

考虑优化，把所有的 $l_i,r_i$ 一起放到数轴上，会发现形成了若干个区间，每个区间内的点是可以一起考虑的，且只有至多 $2n$ 个区间。

那么做法显然了，把区间离散化，$f_{i,j}$ 表示 $a_i$ 在第 $j$ 个区间的时候，$a_{[1,i]}$ 的方案数。

考虑转移，对于每个区间需要一下子选出连续一段的东西，也就是说对于 $l>j,i<k$，从$f_{i,l}$ 向 $f_{k,j}$ 转移时，相当于 $[i+1,k]$ 全部都在第 $j$ 个区间。

相当于有 $cnt=k-i$ 个无差别的东西，要把它们分到 $len_j$ 个盒子里，可以有盒子为空，求方案数。根据插板法强制每个盒子本来就有一个东西即可，所以这部分的系数是 $\binom{len_j+cnt-1}{len_j-1}$。因为 $cnt$ 只有 $n$ 级别，所以直接暴力组合数即可。

这样就得到了一个 $O(n^5)$ 的做法，不过我 $O(n^4)$ 只跑了 15ms，所以估计也能过。然后考虑有两个地方可以优化，一个是组合数里的计算可以放到和 $k$ 的枚举一起，一个是 $\sum_{l>k}f_{i,l}$ 可以用一个后缀和，所以实际上复杂度可以降到 $O(n^3)$。但是我懒，所以组合数单独写了。

https://codeforces.com/contest/1295/submission/172110006

---

## 作者：UltiMadow (赞：3)

首先把题目所求的概率变成合法方案数除以总方案数，所以这题就变成了一个计数问题

发现值域很大，但是 $n$ 很小，考虑把区间化成左闭右开的形式然后离散化

记所有端点排好序之后为 $b_1, b_2\dots,b_q$，$b_{q+1}=b_q+1$，这些端点把值域分成 $[b_1,b_2),[b_2,b_3),\dots,[b_q,b_{q+1})$ 这 $q$ 段区间

为了设定边界，$[b_q,b_{q+1})$ 中强制放一个 0 号区间

设 $f_{i,j}$ 表示前 $i$ 个数不增，第 $i$ 个数在第 $j$ 段区间的方案数

设枚举第 $j$ 段区间放了 $k$ 个数，考虑枚举 $k$，则方案数为 $\binom {b_{j+1}-b_j+i-k-1}{i-k}$

那么有转移方程 $f_{i,j}=\sum\limits_{k<i}\binom {b_{j+1}-b_j+i-k-1}{i-k}\sum\limits_{t>j}f_{k,t}$

注意在枚举 $k$ 的时候判断一下是否 $k+1,\dots ,i$ 中的所有区间都包含第 $j$ 段区间

总方案数即为所有区间长的乘积

时间复杂度 $\mathcal O(n^4)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 110
#define p 998244353
#define int long long
using namespace std;
int n,l[MAXN],r[MAXN],s[MAXN];
int b[MAXN],tot;
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)ret=ret*x%p;
	return ret;
}
int C(int x,int y){
	int ret=1;
	for(int i=x;i>=x-y+1;i--)ret=ret*i%p;
	for(int i=y;i;i--)ret=ret*qpow(i,p-2)%p;
	return ret;
}
int f[MAXN][MAXN];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l[i],&r[i]);r[i]++;
		b[++tot]=l[i];b[++tot]=r[i];s[i]=r[i]-l[i];
	}sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(b+1,b+tot+1,l[i])-b;
		r[i]=lower_bound(b+1,b+tot+1,r[i])-b;
	}
	f[0][tot]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<tot;j++)
			for(int k=i-1;k>=0;k--){
				if(!(l[k+1]<=j&&j+1<=r[k+1]))break;
				int now=0;
				for(int t=j+1;t<=tot;t++)now=(now+f[k][t])%p;
				now=now*C(b[j+1]-b[j]-1+i-k,i-k)%p;
				f[i][j]=(f[i][j]+now)%p;
			}
	int ans=0;
	for(int i=1;i<tot;i++)ans=(ans+f[n][i])%p;
	for(int i=1;i<=n;i++)ans=ans*qpow(s[i],p-2)%p;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：iostream (赞：3)

这个题题意可以转化为有 $n$ 个区间 $[L_i,R_i]$ 然后在这些区间中产生随机整数 $x_1\sim x_n$ 求这些随机数非降序的概率。

$n\le 50,1\le L_i,R_i\le 10^9$

值域很大，很容易想到 《NOI2019 机器人》，于是考虑分段函数优化 dp。

直接计算合法方案数，最后除以 $\prod (R_i-L_i+1)$ 就是概率。

暴力 dp 有转移为 $dp_{i,j}=\sum_{k\le j} dp_{i-1,k}$ 其中 $j\in [L_i,R_i]$。

是一个前缀和的形式，那么我们只要实现分段函数加法、分段函数前缀和，以及将分段函数中间一段拉出来的操作。

分段函数前缀和可以当做在每个 $x^k$ 上做自然数幂和，你可以选择你喜欢的方式计算。

算法时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> poly;

#define SZ(x) (int(x.size()))

const int N=63,P=998244353,inf=1e9;

int fexp(int a, int b) {
	ll x = 1, o = a;
	for(; b; b >>= 1, o = o * o % P)
		if(b & 1) x = x * o % P;
	return x;
}

struct Node_t
{
	poly K;
	int r;
};

typedef vector<Node_t> Node;

inline void poly_free(poly &a)
{
	if(a.empty()) return;
	while(!a.back()) a.pop_back();
}

poly operator + (const poly&a, const poly&b)
{
	poly c(max(SZ(a), SZ(b)));
	for(int i = 0; i < SZ(a); i ++)
		c[i] = a[i];
	for(int i = 0; i < SZ(b); i ++)
		c[i] = (c[i] + b[i]) % P;
	poly_free(c);
	return c;
}

void operator += (poly&a, const poly&b)
{
	a = a + b;
}

poly operator * (const poly&a, const poly&b)
{
	if(!SZ(a) || !SZ(b))
		return poly();
	static long long F[N * 2];
	int l = SZ(a) + SZ(b) - 1;
	for(int i = 0; i < l; i ++)
		F[i] = 0;
	for(int i = 0; i < SZ(a); i ++)
		for(int j = 0; j < SZ(b); j ++)
		{
			F[i + j] += 1LL * a[i] * b[j];
			if(F[i + j] > 200000000000000000LL)
				F[i + j] %= P;
		}
	poly c(l);
	for(int i = 0; i < l; i ++)
		c[i] = F[i] % P;
	poly_free(c);
	return c;
}

int calc(const poly&a, int x)
{
	int y = 0;
	for(int i = SZ(a) - 1; i >= 0; i --)
		y = (1LL * y * x + a[i]) % P;
	return y;
}

int n, Bo[N], C[N][N], inv[N];
poly coef[N];

void init(int n)
{
	n += 2;
	for(int i = 0; i <= n + 1; i ++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
	}
	inv[1] = 1;
	for(int i = 2; i <= n + 1; i ++)
		inv[i] = (ll) inv[P % i] * (P - P / i) % P;
	Bo[0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 0; j < i; j ++)
			Bo[i] = (Bo[i] - (ll)C[i + 1][j] * Bo[j]) % P;
		Bo[i] = (ll)(Bo[i] + P) % P * inv[i + 1] % P;
	}
	coef[0] = poly{0, 1};
	for(int i = 1; i <= n; i ++)
	{
		coef[i].resize(i + 2);
		for(int j = 1; j <= i + 1; j ++)
		{
			coef[i][j] = (ll) Bo[i + 1 - j] * C[i + 1][j] % P * inv[i + 1] % P;
			if((i + 1 - j) & 1)
				coef[i][j] = (P - coef[i][j]) % P;
		}
	}
}

poly operator ! (const poly&a)
{
	poly b;
	for(int i = 0; i < SZ(a); i ++)
		b += poly {a[i]} * coef[i];
	poly_free(b);
	return b;
}

Node operator + (const Node&a, const Node&b)
{
	Node c;
	for(int i = 0, j = 0, k; i < SZ(a) && j < SZ(b); i += (k == a[i].r), j += (k == b[j].r))
	{
		k = min(a[i].r, b[j].r);
		c.push_back({a[i].K + b[j].K, k});
	}
	return c;
}

void operator += (Node&a, const Node&b)
{
	a = a + b;
}

Node operator * (const Node&a, const Node&b)
{
	Node c;
	for(int i = 0, j = 0, k; i < SZ(a) && j < SZ(b); i += (k == a[i].r), j += (k == b[j].r))
	{
		k = min(a[i].r, b[j].r);
		c.push_back({a[i].K * b[j].K, k});
	}
	return c;
}

Node operator ! (const Node&a)
{
	Node b;
	b.push_back({!a[0].K, a[0].r});
	for(int i = 1; i < SZ(a); i ++)
	{
		poly S = !a[i].K;
		if(!S.size())
			S.resize(1);
		S[0] -= calc(S, a[i - 1].r);
		S[0] += calc(b[i - 1].K, a[i - 1].r);
		if(S[0] < 0) S[0] += P;
		if(S[0] >= P) S[0] -= P;
		poly_free(S);
		b.push_back({S, a[i].r});
	}
	return b;
}

Node split(const Node&a, int l, int r)
{
	Node b;
	b.push_back({poly(), l - 1});
	for(int i = 0; i < SZ(a); i ++)
	{
		if(a[i].r > b.back().r && a[i].r < r)
			b.push_back(a[i]);
		else if(a[i].r >= r)
		{
			b.push_back({a[i].K, r});
			break;
		}
	}
	if(b.back().r < inf)
		b.push_back({poly(), inf});
	return b;
}

void out(const Node&F)
{
	for(auto x:F)
	{
		printf("<%d:", x.r);
		for(auto y:x.K)
			printf(" %d",y);
		puts("");
	}
	puts("");
}

int main()
{
	cin >> n;
	vector<int> l(n), r(n);
	for(int i = 0; i < n; ++i)
		cin >> l[i] >> r[i];
	reverse(l.begin(), l.end());
	reverse(r.begin(), r.end());
	init(n);
	Node f = Node {
		(Node_t) {poly(), l[0] - 1},
		(Node_t) {poly{1}, r[0]},
		(Node_t) {poly(), inf}
	};
	for(int i = 1; i < n; ++i)
		f = split(!f, l[i], r[i]);
	int res = calc((!f).back().K, inf);
	for(int i = 0; i < n; i ++)
		res = (ll)res * fexp(r[i] - l[i] + 1, P - 2) % P;
	printf("%d", res);
	return 0;
}


---

## 作者：xxr___ (赞：1)

提供一种复杂度较高但是好写的方法。

首先概率转换成求合法方案数再除以总的方案数，和划艇一题一样的思路，把值域离散化成形容 $[l_i,r_i + 1)$ 的形式，方便我们计算。

可以发现，离散化之后，原来每个区间 $[l_i,r_i]$ 现在变成了很多连续的段拼接起来，且是连续的。

所以我们设 $f(i,j)$ 表示第 $i$ 个数，选择第 $j$ 个离散化后的段的方案数。

转移就是枚举 $i$ 之前的那些数和 $i$ 同属于同一个段，由于可以有相同的数，所以等价于那些相同的数可选可不选，由于 $a_i$ 必须选，设上一次不选择在这个段的位置是 $j$，设当前这个段的长度是 $l$，根据插板法，方案数应该是 $\dbinom{l + i - j - 1}{i - j}$ 的，所以转移就是 $f(i,j) = \sum_{k < i} \sum_{p > j} f(k,p)\times \dbinom{l + i - k - 1}{i - k}$ 直接转移就是 $\mathcal O(n^4)$ 的。

代码：
```cpp
#include<iostream>
#include<algorithm>

#define int long long
const int N = 105;
const int mod = 998244353;
int f[N][N],li[N],cnt = 0,n,l[N],r[N];
//第 i 个数在 [a[i],b[i]) 的范围内的方案数 
inline int ksm(int x,int y){
	int ans = 1;
	while(y){
		if(y & 1){
			(ans *= x) %= mod;
		}
		y >>= 1;
		(x *= x) %= mod;
	}
	return ans;
}
inline int inv(int x){
	return ksm(x,mod - 2);
}
inline int C(int x,int y){
	int ans1 = 1,ans2 = 1;
	for(int i = x;i >= x - y + 1; -- i){
		(ans1 *= i) %= mod;
	}
	for(int i = 2;i <= y; ++ i){
		(ans2 *= i) %= mod;
	}
	return (ans1 * inv(ans2)) % mod;
}
auto main() -> signed{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n;
	for(int i = 1;i <= n; ++ i){
		std::cin >> l[i];
		std::cin >> r[i];
		++ r[i];
		li[++ cnt] = l[i];
		li[++ cnt] = r[i];
	}
	std::sort(li + 1,li + cnt + 1);
	cnt = std::unique(li + 1,li + cnt + 1) - li - 1;
	for(int i = 1;i <= n; ++ i){
		l[i] = std::lower_bound(li + 1,li + cnt + 1,l[i]) - li;
		r[i] = std::lower_bound(li + 1,li + cnt + 1,r[i]) - li;
	}
	f[0][cnt] = 1;
	for(int i = 1;i <= n; ++ i){
		for(int j = 1;j < cnt; ++ j){
			int len = li[j + 1] - li[j];
			if(l[i] <= j && r[i] > j){
				for(int k = i - 1; ~ k; -- k){
					if(l[k + 1] <= j && r[k + 1] > j){
						int sz = i - k;
						for(int p = j + 1;p <= cnt; ++ p){
							f[i][j] = (f[i][j] + f[k][p] * C(len + sz - 1,sz)) % mod;
						}
					}else{
						break;
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1;i < cnt; ++ i){
		(ans += f[n][i]) %= mod;
	}
	for(int i = 1;i <= n; ++ i){
		(ans *= inv(li[r[i]] - li[l[i]])) %= mod;
	}
	std::cout << ans;
	return 0;
}
```

---

## 作者：PNNNN (赞：1)

#### 思路

题目要求 $a_{1 \dots n}$ 单调不增的概率，可以转化为求  $a_{1 \dots n}$ 单调不增的方案数，最后再乘上个总方案数的逆元即可。总方案数好求，即为 $\prod\limits_{i = 1}^{n} (r_i-l_i+1)$，现考虑如何求  $a_{1 \dots n}$ 单调不增的方案数。


设 $dp_{i,j}$ 表示考虑前 $i$ 个数，当第 $i$ 个数为 $j$ 时的方案数。转移则为 $dp_{i,j}= \sum\limits_{k\ge j} dp_{i-1,k},j \in [l_i,r_i]$。将 $\sum\limits_{k\ge j} dp_{i-1,k}$ 用后缀和优化后就得到了 $O(n+ \sum\limits_{i = 1}^{n} (r_i-l_i+1))$ 的暴力。


如何优化？

首先 $\sum\limits_{i = 1}^{n} (r_i-l_i+1)$ 可以达到 $998244351 \times 50$ 的规模，非常大，因此考虑将其离散化。将所有的 $l_i$ 和 $r_i+1$ 进行离散化。

设离散化前的值为 $x$，离散化后的值为 $val$，$lim$ 为最大的 $val$，对此建立离散化数组 $mp_x=val,fp_{val}=x$。则离散化后的每个 $val$ 都代表了一个左闭右开的区间 $[fp_{val},fp_{val+1})$。

那这样做的正确性是什么？易证，对于每个区间 $[fp_{val},fp_{val+1}),\forall i \ \forall j,k \in [fp_{val},fp_{val+1})\ dp_{i,j}=dp_{i,k}$，正确性显然。

而在离散化后 $dp_{i,j}$ 的含义变为了考虑前 $i$ 个数，当第 $i$ 个数的取值范围为 $[fp_{j},fp_{j+1})$ 时的方案数。


那么优化后该如何转移？比较显然的是 $dp_{i,j} = \sum \limits_{k\ge j} dp_{i-1,k}$。

但这样转移是错的。

因为当 $k=j$ 时我们无法保证 $a_{i-1}\ge a_i$，于是我们将 $k=j$ 单独考虑。先设 $sum_{i,j} = \sum \limits_{k=j}^{lim} dp_{i,k}$。

接下来分类讨论。


若 $k> j$，此时已经保证了 $a_{i-1}>a_i$，所以 $dp_{i,j} = sum_{i-1,j+1} \times (r_i-l_i+1)$。

若 $k= j$ 考虑该如何保证 $a_{1 \dots i}$ 单调不增。已知 $n$ 的范围很小，$O(n^3)$ 也不会超时。因此，我们可以枚举出一个下标 $p$，钦定 $a_{p \dots i} \in [fp_{j},fp_{j+1})$，且 $a_{p-1} \ge fp_{j+1}$。

通过组合数学易得 $a_{p \dots i} \in [fp_{j},fp_{j+1})$ 的方案数，即 $C_{i-p+fp_{j+1}-fp_{j}}^{fp_{j+1}-fp_{j}-1}$。而 $a_{p-1} \ge fp_{j+1}$ 的方案即为 $sum_{p-1,j+1}$。

所以 $dp_{i,j}= \sum \limits_{p=1}^{i-1} sum_{p-1,j+1} \times C_{i-p+fp_{j+1}-fp_{j}}^{fp_{j+1}-fp_{j}-1}$。
#### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod=998244353;

inline int ksm(int base,int exp){
	int res=1;
	while(exp>0){
		if(exp&1)res=res*base%mod;
		exp>>=1,base=base*base%mod;
	}return res;
}

inline int inv(int x){return ksm(x,mod-2);}

int n,l[505],r[505],dp[505][505],sum[505][505],rinv[505],ans=1;

int fp[505],lim;

inline int read(){
	register int x=0,t=0;
	static char ch=getchar();
	while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
	return t?-x:x;
}

signed main(){
//	freopen("array.in","r",stdin);
//	freopen("array.ans","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read()+1;
		(ans*=inv(r[i]-l[i]))%=mod;
		fp[++lim]=l[i],fp[++lim]=r[i];
	}
	sort(fp+1,fp+lim+1);
	lim=unique(fp+1,fp+lim+1)-fp-1;
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(fp+1,fp+1+lim,l[i])-fp;
		r[i]=lower_bound(fp+1,fp+1+lim,r[i])-fp;
	}
	for(int i=1;i<=lim;i++){
		sum[0][i]=1;
	}
	for(int i=1;i<=n;i++){
		rinv[i]=inv(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=l[i];j<r[i];j++){
			int len=fp[j+1]-fp[j]-1,C=len+1;
			dp[i][j]=sum[i-1][j+1]*(len+1)%mod;
			for(int k=i-1;k>=1;k--){
				if(!(l[k]<=j&&j<r[k]))break;
				(C*=(len+i-k+1)*rinv[i-k+1]%mod)%=mod;
				dp[i][j]=(dp[i][j]+sum[k-1][j+1]*C%mod)%mod;
			}
		}
		for(int j=lim;j>=1;j--){
			(sum[i][j]=sum[i][j+1]+dp[i][j])%=mod;
		}
	}
	cout<<sum[n][1]*ans%mod;
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：1)

实际难度只有 \*2200 左右 。

值域很大，但是段数不多，可以离散化。设 $f_i(j)$ 表示到 $i$ 为止值在第 $j$ 段的概率。

可以枚举最后相同段的长度进行转移。在 $[j,i]$ 中放入 $v_{k+1}-v_k$ 个数，要求它们递减，方案数为 $\displaystyle\binom{v_{k+1}-v_k + i - j + 1 -1}{i-j+1}$，概率则除以 $[j,i]$ 之间段长的积即可。上指标很大，但是下指标不大，可以暴力计算。转移则直接把概率乘上 $\sum_{p>k} f_{j-1}(p)$。前缀和优化，最终复杂度为 $O(n^4)$。

[代码](https://www.luogu.com.cn/paste/195q438o)。事实上，预处理每次计算组合数时与上指标相关的区间积，可以做到 $O(n^3)$。

---

## 作者：crashed (赞：1)

**去往[原博客](https://www.cnblogs.com/crashed/p/13826441.html)食用更佳。**

# 题目

[点这里](https://www.luogu.com.cn/problem/CF1295F)看题目。

# 分析

初看似乎只能想到一个暴躁的 DP：   

$f_{i,j}$：前 $i$ 个数，最后一个数是 $j$ 的序列方案数。   

 ...... 嗯，显然会 TLE。   

不过，由于总共的区间数很少，所以由区间的端点组合的区间会很少。我们可以从这个方向入手压缩状态。   

考虑将原先的闭区间 $[l_i,r_i]$ 转为开区间 $[l'_i,r'_i)$。然后将所有的 $l'_i$ 和 $r'_i$ 拿出来排序并去重，得到了序列 $P$。并记 $I_j=[P_{j},P_{j+1})$。我们于是可以考虑重新定义状态：   

$f_{i,j}$：前 $i$ 个数，最后一个数落在了 $I_j$ 中的方案数。   

转移时我们可以考虑枚举属于 $I_j$ 的数的范围。同一个区间中选取出不增序列的方案数可以**隔板法**计算，本质上求出 $[l,r)$ 中随便选出 $c$ 个数组成不增子序列等价于**从 $[l,r)$ 中随便选出 $c$ 个数**，也即是 $\binom{r-l+c-1}{c}$。具体写出来就长这个样子：   

$$
f_{i,j}=\sum_{k=0}^{i-1}[\forall k<p\le i,I_j\subset [l_p,r_p]]\sum_{j<t}f_{k,t}\binom{|I_j|+i-k-1}{i-k}
$$  
   
最终的答案就是 $\sum_{j}f_{n,j}$ 除以总的序列数。

实际转移的时候，我们可以在发现 $[\forall k<p\le i,I_{j}\subset[l_p,r_p]]= 0$ 时直接跳出。后面的 $\sum_{j<t} f_{k,t}$ 可以运用后缀和优化。 $\binom{|I_j|+i-k}{i-k}$ 需要 $O(n)$ 单独计算。

因此转移的时间复杂度是 $O(n^4)$。      

# 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

const int mod = 998244353;
const int MAXN = 105;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ); s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) putchar( '-' ), x = -x;
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int f[MAXN][MAXN];
int l[MAXN], r[MAXN], pnt[MAXN << 1];
int lef[MAXN], rig[MAXN];
int N;

int Qkpow( int base, int indx );
int Inv( const int a ) { return Qkpow( a, mod - 2 ); }
int Mul( LL x, int v ) { x *= v; if( x >= mod ) x %= mod; return x; }
int Add( int x, int v ) { return x + v >= mod ? x + v - mod : x + v; }

int Qkpow( int base, int indx )
{
	int ret = 1;
	while( indx )
	{
		if( indx & 1 ) ret = Mul( ret, base );
		base = Mul( base, base ), indx >>= 1;
	}
	return ret;
}

int C( const int n, const int m )
{
	if( n < m ) return 0; int ret = 1;
	for( int i = 1 ; i <= m ; i ++ ) 
		ret = Mul( ret, Mul( n - i + 1, Inv( i ) ) );
	return ret;
}

int main()
{
	read( N ); int tot = 0;
	for( int i = 1 ; i <= N ; i ++ ) read( l[i] ), read( r[i] );
	for( int i = 1 ; i <= N ; i ++ ) pnt[++ tot] = l[i], pnt[++ tot] = r[i] + 1;
	sort( pnt + 1, pnt + 1 + tot );
	tot = unique( pnt + 1, pnt + 1 + tot ) - pnt - 1;
	for( int i = 1 ; i <= N ; i ++ ) 
		lef[i] = lower_bound( pnt + 1, pnt + 1 + tot, l[i] ) - pnt,
		rig[i] = lower_bound( pnt + 1, pnt + 1 + tot, r[i] + 1 ) - pnt;
	
	int ans = 0, L;
	lef[0] = 1, rig[0] = tot + 1;
	for( int i = 1 ; i <= tot ; i ++ ) f[0][i] = 1;
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = lef[i] ; j < rig[i] ; j ++ )
		{
			L = pnt[j + 1] - pnt[j];
			for( int k = i ; k ; k -- )
			{
				if( j < lef[k] || rig[k] <= j ) break;
				f[i][j] = Add( f[i][j], Mul( f[k - 1][j + 1], C( i - k + L, i - k + 1 ) ) );
			}
		}
		for( int j = tot - 1 ; j ; j -- )
			f[i][j] = Add( f[i][j + 1], f[i][j] );
	}
	ans = f[N][1];
	for( int i = 1 ; i <= N ; i ++ )
		ans = Mul( ans, Inv( r[i] - l[i] + 1 ) );
	write( ans ), putchar( '\n' );
	return 0;
}
```


---

## 作者：cqbzlzm (赞：0)

### Description

$a_i$ 是在 $[L_i,R_i]$ 上均匀随机分布的整数，求 $a_{1\cdots n}$ 单调不增的概率。

### Solution

因为总方案很好求，所以我们需要计算 $a_{1\cdots n}$ 单调不增的方案数。

我们用计数 dp，首先有一个很好想的思路：

设 $dp_{i,j}$ 表示前 $i$ 个数，最后一个数是 $j$ 的合法方案数，转移：$dp_{i,j}=\sum^{k\geq j}{dp_{i-1,k}}$。显然这样空间会爆炸。

由于 $j$ 很大，所以我们对它离散化一下，即用每个 $L_i,R_i$ 做分界点，把所有的数分组。

设离散化的数组为 $re$，则第 $i$ 组的数包括 $[re_i,re_{i+1})$。

这样我们可以愉快地 dp 了，设 $dp_{i,j}$ 表示前 $i$ 个数，最后一个数在第 $j$ 组的合法方案数。通过枚举 $k$，表示 $a_{k+1,\cdots ,i}$ 全在第 $j$ 组，进行转移：
$$
dp_{i,j}=\sum^{i-1}_{k=1}{\sum^{p>j}{dp_{k,p}\times \binom{len+i-k-1}{len-1}}}
$$
 这个内层求和显然可以用前缀和优化，所以总时间复杂度为 $O(n^3)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353, MAXN = 60;
int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1ll) ans = ans * a % mod;
		a = a * a % mod;
		b = b / 2ll;
	}
	return ans;
}
int n;
int l[MAXN + 5], r[MAXN + 5];
int re[MAXN * 2 + 5], rcnt;
int dp[MAXN + 5][MAXN * 2 + 5], C[MAXN * 2 + 5];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld%lld", &l[i], &r[i]);
		re[++ rcnt] = l[i];
		re[++ rcnt] = ++ r[i];
	}
	sort(re + 1, re + rcnt + 1);
	rcnt = unique(re + 1, re + rcnt + 1) - re - 1;
	for (int i = 1; i <= n; i ++) {
		l[i] = lower_bound(re + 1, re + rcnt + 1, l[i]) - re;
		r[i] = lower_bound(re + 1, re + rcnt + 1, r[i]) - re;
	}
    dp[0][rcnt] = 1; re[rcnt + 1] = 114514;
    for (int i = 1; i < rcnt; i ++) dp[0][i] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = l[i]; j < r[i]; j ++) {
            int len = re[j + 1] - re[j];
            C[1] = len;
            for (int k = 2; k <= i; k ++)
                C[k] = C[k - 1] * (len + k - 1) % mod * qpow(k, mod - 2) % mod;
            for (int k = i - 1; k >= 0; k --) {
                dp[i][j] = (dp[i][j] + dp[k][j + 1] * C[i - k] % mod) % mod;
                if (j < l[k] || j >= r[k]) break;
            }
        }
        for (int j = rcnt - 1; j >= 1; j --) dp[i][j] = (dp[i][j] + dp[i][j + 1]) % mod;
    }
    int ans = dp[n][1];
    for (int i = 1; i <= n; i ++)
        ans = ans * qpow(re[r[i]] - re[l[i]], mod - 2) % mod;
    cout<<ans;
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

一开始并没有完全理解做法，就草草的参考题解之后自己想了想，做了这道题。今天跟同学讲完题，感觉对这道题有了更多的思考。所以来发一篇题解。

## 思路

显然，我们可以先记录可行方案数，再除以总方案数得到答案。

首先，我们考虑暴力的 dp。令 $dp_{i,j}$ 表示当前到第 $i$ 个数，$a_i = j$ 的时候的方案数。显然，$a_i$ 前面的所有的数只能取 $\geq j$ 的值。因此，得到转移方程：

$$dp_{i,j} = \sum\limits_{k=j+1}^n dp_{i-1,k}$$

但是这个时空都带一个 $r_i$，范围太大了。因此我们直接考虑离散化。离散化之后，$r_i$ 的范围缩小至 $2n$ 大小，可以接受。但是，我们也要对 dp 稍作修改。

第一，我们发现一个性质：每一个区间离散化之后，可以看成若干个 $[ x, x + 1 )$ 的左闭右开区间组合而成。为什么不是左闭右闭呢，因为那样其实是不可做的。

第二，我们可以根据第一条大致对状态有了思路：$dp_{i,j}$ 表示当前到第 $i$ 个数，$a_i \in [j, j + 1)$ 时的方案数。转移也就和之前的**大致类似**，大概是：

$$dp_{i,j} = \sum\limits_{k=j}^{M}dp_{i-1,k}$$

其中 $M$ 表示离散化之后不同的数的个数，即离散化之后的最大值。

但是，这个转移是有问题的！问题就出在 $k$ 从 $j$ 开始这里。因为离散化之后，$[j,j+1)$ 可以代表很大范围的一个区间，但是在这里被缩的很小，因此可能出现两个数同在这个区间里，但是大小不一样的情况。

所以我们要特判 $k=j$ 的情况。那么 $k=j$ 的情况一定是从 $k$ 到 $i$ 的一段连续子段，因为 $k>j$ 的情况不可能出现在 $k=j$ 后面，因为无论离散化或者不离散化，不同**区间的大小关系是恒定不变的**。

所以我们枚举 $k$，假设 $a_k...a_i$ 都在 $[j,j+1)$ 这个区间里，并分成两种情况考虑：

- $1$ 到 $k-1$：这个值就是 $\sum\limits_{p=j+1}^{M} dp_{i-k,p}$。因为这一部分已经确定和 $a_i$ 不相等，即 $\forall q \in [1,k-1],a_q>a_i$。那么放在 dp 中，第二位就是 $j+1$（因为 $a_i$ 取到 $j$）。

- $k$ 到 $i-1$：由于这些都和 $a_i$ 相等，所以不需要考虑是否单调不降。方案数怎么求的话详见下面 qwq！

但是，离散化之后怎么统计方案数呢？我们可以令 $d_i$ 表示离散化后 $[i,i+1)$ 对应的原来区间的长度。那么每次转移的时候相当于从里面选出 $i-k$ 个数，方案数显然是 $\dbinom{d_i+i-k-1}{i-k}$。

所以我们的转移方程：

$$dp_{i,j}=\sum\limits_{k=0}^{i-1}\sum\limits_{p=j+1}^{M} dp_{k,p} \times \dbinom{d_i+i-k-1}{i-k}$$

答案就是 $\sum\limits_{i=0}^{M} dp_{n,i}$。

当然，我们可以每次 dp 的时候顺便把 dp 记成一个前缀和。

也就是说，$dp_{i,j}$ 表示的是原来的 $\sum\limits_{k=j}^{M} dp_{i,k}$。转移方程就去掉一个求和即可：

$$dp_{i,j}=\sum\limits_{k=0}^{i-1} dp_{k,j+1} \times \dbinom{d_i+i-k-1}{i-k}$$

时间复杂度 $O(n^3)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,MAXN=60;
int a[MAXN],b[MAXN],f[MAXN][MAXN<<1];
int inv[MAXN],g[MAXN],tmp[MAXN<<1];

int ksm(int a,int b)
{
    int base=a,ans=1;
    while(b)
    {
        if(b&1) ans=1ll*ans*base%mod;
        base=1ll*base*base%mod;
        b>>=1;
    }
    return ans;
}
int main()
{
    int n,m=0; scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
        tmp[++m]=a[i];
        tmp[++m]=(++b[i]);
    }

    sort(tmp+1,tmp+m+1);
    m=unique(tmp+1,tmp+m+1)-tmp-1;
    for(int i=1;i<=n;i++)
    {
        a[i]=lower_bound(tmp+1,tmp+m+1,a[i])-tmp;
        b[i]=lower_bound(tmp+1,tmp+m+1,b[i])-tmp;
    }
    for(int i=1;i<=n;i++) inv[i]=ksm(i,mod-2);
    a[0]=1,b[0]=m+1;

    for(int i=1;i<=m;i++) f[0][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=a[i];j<b[i];j++)
        {
            int d; g[1]=d=tmp[j+1]-tmp[j];
            for(int k=2;k<=i;k++) g[k]=1ll*g[k-1]*(d+k-1)%mod*inv[k]%mod;
            for(int k=i-1;k>=0;k--)
            {
                f[i][j]=(f[i][j]+1ll*f[k][j+1]*g[i-k])%mod;
                if(j<a[k] || j>=b[k]) break;
            }
        }
        for(int j=m;j>=1;--j) f[i][j]=(f[i][j]+f[i][j+1])%mod;
    }
    int ans=f[n][1];
    for(int i=1;i<=n;i++)
        ans=1ll*ans*ksm(tmp[b[i]]-tmp[a[i]],mod-2)%mod;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：MoonPie (赞：0)

## 题意

$a_i$ 在 $l_i, r_i$ 等概率随机，求 $a_{1 \dots n}$ 不增的概率。
$$
\begin{aligned}
n &\le 50\\
l_i,r_i &< 998244353
\end{aligned}
$$

## 题解

别问我为啥，就图个方便，我们将 $a$ reverse，做 $a_{1\dots n}$ 单调不降的方案数。

考虑对 $l_i,r_i$ 离散化之后，最多有 $2n+1$ 个区间。设第 $i$ 个区间长度为 $len_i =$ 区间内数的个数。

$dp(i,j)$ 表示第 $i$ 个点，放在了第 $j$ 个区间中。$f(i,j)$ 表示 $i$ 个点放在第 $\le j$ 个区间中的方案数。
$$
\begin{aligned}
dp(i,j) =& f(i-1,j-1)\times len_j\\
dp(i,j) =& \sum_{k=1} f(i-k-1,j-1) \times \binom{len_j+k}{k+1}
\end{aligned}
$$
有一个细节需要注意，就是要把每个端点 $-1$ 的坐标也放入离散化的数组中，因为这样才能把所有的相交段都算进去（建议手模一下第二个样例）。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 55, mod = 998244353;
struct node { int l,r; }a[N];
ll inv[N<<1];
ll len[N<<2],dp[N][N<<2],f[N][N<<2],tot=1;

template<class T> void add_(T &x,T y) { x = (x+y) % mod; }
int qpow(int x,int y) {
	int res = 1;
	for (int i = 0; (y>>i) > 0; ++i, x = 1ll*x*x%mod)
		if (y>>i&1) res = 1ll * res * x % mod;
	return res;
}
void init(int n) {
	inv[1]=1;                
  for (int i = 2; i <= n; ++i)
		inv[i]=-mod/i*inv[mod%i]%mod,inv[i]=(inv[i]+mod)%mod;
}
int C(int n,int m) {
	if (m < 0 || m > n) return 0;
	int res = 1;
	for (int i = 0; i < m; ++i) res = 1ll * res * (n-i) % mod * inv[i+1] % mod;
	return res;
}

int n,m,X[N<<2];
int main()
{
	scanf("%d",&n);
	init(n<<1);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d",&a[i].l,&a[i].r); 
		tot = tot * (a[i].r - a[i].l + 1) % mod;
		X[++m] = a[i].l, X[++m] = a[i].r;
		X[++m] = a[i].l-1, X[++m] = a[i].r-1;
	}
	sort(X+1,X+m+1);
	m = unique(X+1,X+m+1)-X-1;
	for (int i = 1; i <= n; ++i) {
		a[i].l = lower_bound(X+1,X+m+1, a[i].l)-X;
		a[i].r = lower_bound(X+1,X+m+1,a[i].r)-X;
	}
	reverse(a+1,a+n+1);

	for (int i = 2; i <= m; ++i) len[i] = X[i] - X[i-1];
	for (int i = a[1].l; i <= a[1].r; ++i) dp[1][i] = len[i];
	for (int i = 2; i <= m; ++i) f[1][i] = (f[1][i-1] + dp[1][i]) % mod;

	for (int i = 2; i <= n; ++i) {
		for (int j = a[i].l; j <= a[i].r; ++j) {
			dp[i][j] = f[i-1][j-1] * len[j] % mod;
			for (int k = 1; k < i && a[i-k].l <= j && j <= a[i-k].r; ++k) {
				ll pr = i-k-1>0? f[i-k-1][j-1]: 1;
				add_(dp[i][j], pr * C(len[j]+k,k+1) % mod);
			}
		}
		for (int j = 2; j <= m; ++j) f[i][j] = (f[i][j-1] + dp[i][j]) % mod;
	}
	printf("%lld\n",f[n][m] * qpow(tot,mod-2) % mod);
	return 0;
}
```



---

## 作者：chroneZ (赞：0)

这不是我们[[APIO2016] 划艇](https://www.luogu.com.cn/problem/P3643)吗，那题的式子还略微难一点。

首先很容易想到一种 DP，$f_{i, j}$ 表示前 $i$ 项，第 $i$ 项为 $j$ 时的方案数，值域过大所以复杂度是假的。

考虑我们其实只关心这个数列里的数的大小关系，因此可以离散化一下，本质上是划分成了 $\Theta(n)$ 个值域区间 $[d_i, d_{i + 1})$。

记 $f_{i, j}$ 表示前 $i$ 项，第 $i$ 项位于第 $j$ 个值域区间时的方案数。由于位于相同值域区间的数也可以合法，因此考虑每次枚举上一个与第 $i$ 项所位于的值域区间不同的位置，则我们需要求解下面的问题：

> 求长为 $n$，每一项都位于值域 $[d_j, d_{j + 1})$ 的单调不增序列数。

经典组合数学问题，我的做法是考虑用差分序列来刻画原序列，然后问题等价于 $d_{j + 1} - d_j - 1$ 个球分给 $n + 1$ 个盒子，允许盒子为空的方案数，即 $\binom{d_{j + 1} - d_j - 1 + n}{n}$。

最终有

$$
f_{i, j} \gets \sum_{t = 0} ^ {i - 1} (\sum_{k > j} f_{t, k}) \times \binom{d_{j + 1} - d_j - 1 + i - t}{i - t}, [d_j, d_{j + 1}) \subseteq [l_k, r_k], \forall k \in [t + 1, i]
$$

后缀和优化后，显然可以做到 $\Theta(n ^ 3)$。

注意组合数的上指标可能很大，因此要递推地求，即 $\binom{L + n - 1}{n - 1} \times \frac{L + n}{n} \to \binom{L + n}{n}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int mod = 998244353, N = 50 + 5;
namespace basic {
  inline int add(int x, int y) {return (x + y >= mod ? x + y - mod : x + y);}
  inline int dec(int x, int y) {return (x - y < 0 ? x - y + mod : x - y);}
  inline void ad(int &x, int y) {x = add(x, y);}
  inline void de(int &x, int y) {x = dec(x, y);}

  inline int qpow(int a, int b) {
    int r = 1;
    while(b) {
      if(b & 1) r = 1ll * r * a % mod;
      a = 1ll * a * a % mod; b >>= 1;
    }
    return r;
  }
  inline int inv(int x) {return qpow(x, mod - 2);}

  int fac[N], ifac[N];
  inline void fac_init(int n = N - 1) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
      fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = inv(fac[n]);
    for(int i = n - 1; i >= 0; i--)
      ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  }
  int invx[N];
  inline void inv_init(int n = N - 1) {
    invx[1] = 1;
    for(int i = 2; i <= n; i++)
      invx[i] = 1ll * (mod - mod / i) * invx[mod % i] % mod;
  }
  inline int binom(int n, int m) {
    if(n < m || m < 0) return 0;
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }

  int rev[N];
  inline void rev_init(int n) {
    for(int i = 1; i < n; i++)
      rev[i] = (rev[i >> 1] >> 1) + (i & 1 ? n >> 1 : 0);
  }
}
using namespace basic;

int n, a[N], b[N];
int m, d[N * 2];
int f[N][N * 2], s[N][N * 2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  fac_init(); inv_init();

  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    d[++m] = a[i], d[++m] = b[i] + 1;
  }
  sort(d + 1, d + m + 1);
  m = unique(d + 1, d + m + 1) - d - 1;

  f[0][m] = 1;
  for(int i = 0; i <= m; i++) {
    s[0][i] = 1;
  }
  for(int i = 1; i <= n; i++) {
    for(int j = m - 1; j >= 1; j--) {
      s[i][j] = s[i][j + 1];
      if(!(a[i] <= d[j] && d[j + 1] - 1 <= b[i])) {
        continue;
      }
      int cur = 1, L = d[j + 1] - d[j];
      for(int t = i - 1; t >= 0; t--) {
        int p = i - t;
        cur = 1ll * cur * (L - 1 + p) % mod * invx[p] % mod;
        ad(f[i][j], 1ll * s[t][j + 1] * cur % mod);
        if(!(a[t] <= d[j] && d[j + 1] - 1 <= b[t])) {
          break;
        }
      }
      ad(s[i][j], f[i][j]);
    }
  }
  int prod = 1;
  for(int i = 1; i <= n; i++) {
    prod = 1ll * prod * (b[i] - a[i] + 1) % mod;
  }
  cout << 1ll * s[n][1] * inv(prod) % mod << "\n";
}
```

---

