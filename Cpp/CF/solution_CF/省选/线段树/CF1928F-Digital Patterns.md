# Digital Patterns

## 题目描述

Anya is engaged in needlework. Today she decided to knit a scarf from semi-transparent threads. Each thread is characterized by a single integer — the transparency coefficient.

The scarf is made according to the following scheme: horizontal threads with transparency coefficients $ a_1, a_2, \ldots, a_n $ and vertical threads with transparency coefficients $ b_1, b_2, \ldots, b_m $ are selected. Then they are interwoven as shown in the picture below, forming a piece of fabric of size $ n \times m $ , consisting of exactly $ nm $ nodes:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1928F/7b752ff6c6aa2dba727d3451b2fd110135821975.png) Example of a piece of fabric for $ n = m = 4 $ .After the interweaving tightens and there are no gaps between the threads, each node formed by a horizontal thread with number $ i $ and a vertical thread with number $ j $ will turn into a cell, which we will denote as $ (i, j) $ . Cell $ (i, j) $ will have a transparency coefficient of $ a_i + b_j $ .

The interestingness of the resulting scarf will be the number of its sub-squares $ ^{\dagger} $ in which there are no pairs of neighboring $ ^{\dagger \dagger} $ cells with the same transparency coefficients.

Anya has not yet decided which threads to use for the scarf, so you will also be given $ q $ queries to increase/decrease the coefficients for the threads on some ranges. After each query of which you need to output the interestingness of the resulting scarf.

 $ ^{\dagger} $ A sub-square of a piece of fabric is defined as the set of all its cells $ (i, j) $ , such that $ x_0 \le i \le x_0 + d $ and $ y_0 \le j \le y_0 + d $ for some integers $ x_0 $ , $ y_0 $ , and $ d $ ( $ 1 \le x_0 \le n - d $ , $ 1 \le y_0 \le m - d $ , $ d \ge 0 $ ).

 $ ^{\dagger \dagger} $ . Cells $ (i_1, j_1) $ and $ (i_2, j_2) $ are neighboring if and only if $ |i_1 - i_2| + |j_1 - j_2| = 1 $ .

## 说明/提示

In the first example, the transparency coefficients of the cells in the resulting plate are as follows:

 2334233434454556Then there are the following sub-squares that do not contain two neighboring cells with the same transparency coefficient:

- Each of the $ 16 $ cells separately;
- A sub-square with the upper left corner at cell $ (3, 1) $ and the lower right corner at cell $ (4, 2) $ ;
- A sub-square with the upper left corner at cell $ (2, 3) $ and the lower right corner at cell $ (3, 4) $ ;
- A sub-square with the upper left corner at cell $ (2, 1) $ and the lower right corner at cell $ (3, 2) $ ;
- A sub-square with the upper left corner at cell $ (3, 3) $ and the lower right corner at cell $ (4, 4) $ .

In the second example, after the first query, the transparency coefficients of the horizontal threads are $ [1, 2, 2] $ . After the second query, the transparency coefficients of the vertical threads are $ [2, -4, 2] $ .

## 样例 #1

### 输入

```
4 4 0
1 1 2 3
1 2 2 3```

### 输出

```
20```

## 样例 #2

### 输入

```
3 3 2
1 1 1
2 2 8
1 2 3 1
2 2 3 -6```

### 输出

```
9
10
11```

## 样例 #3

### 输入

```
3 2 2
-1000000000 0 1000000000
-1000000000 1000000000
1 1 1 1000000000
2 2 2 -1000000000```

### 输出

```
8
7
7```

# 题解

## 作者：Register_int (赞：5)

首先题目中的条件是骗人的。单独对于一个格子 $(i,j)$ 考虑：

- $a_i+b_j\not=a_{i+1}+b_j$，也即 $a_i\not=a_{i+1}$。
- $a_i+b_j\not=a_i+b_{j+1}$，也即 $b_i\not=b_{i+1}$。

因此一个以 $(i,j)$ 为左上角，边长为 $d$ 的正方形合法，当且仅当：

- 对于 $x=i\sim i+d-2,y=j\sim j+d-2$，有 $a_x\not=a_{x+1}$ 且 $b_y\not=b_{y+1}$。

可以发现 $a,b$ 是独立的，所以若要计算方案数，可以单独计算出 $a,b$ 中长度为 $d$ 的合法子串数量再相乘。问题就变成了维护这个东西。

然后真正恶心的部分来了。来考虑 $a$ 中一个长度为 $x$ 的极长合法子串与 $b$ 中一个长度为 $y$ 的极长合法子串，他们能组成多少个合法正方形。不妨 $x\le y$，则有：

$$
\begin{aligned}
f(x,y)&=\sum^x_{i=1}(x-i+1)(y-i+1)\\
&=\sum^x_{i=1}i(y-x+i)\\
&=\sum^x_{i=1}i^2+i(y-x)\\
&=\frac{x(x+1)(2x+1)}6+(y-x)\times\frac{x(x+1)}2\\
&=\frac{x(x+1)(2x+1)}6-\frac{x^2(x+1)}2+\frac{x(x+1)y}2\\
\end{aligned}
$$

设 $a$ 中的极长连续段长度为 $x_1,x_2,\cdots,x_p$，$b$ 中的是 $y_1,y_2,\cdots,y_q$。再分别设 $u_i=i,v_i=\frac{x(x+1)}2,w_i=\frac{i(i+1)(2i+1)}6-\frac{i^2(i+1)}2$。则我们要求的就是：

$$
\begin{aligned}
&\sum_i\sum_jf(x_i,y_j)\\
=&\sum_i\sum_j[x_i\le y_j](w_{x_i}+v_{x_i}u_{y_j})+[x_i>y_j](w_{y_j}+v_{y_j}u_{x_i})\\
=&\sum_i\left(w_{x_i}\sum_j[x_i\le y_j]+v_{x_i}\sum_j[x_i\le y_j]u_{y_j}+\sum_j[x_i>y_j]w_{y_j}+u_{x_i}\sum_j[x_i>y_j]v_{y_j}\right)\\
=&\sum_i\left(w_{x_i}\sum_{y_j\ge x_i}1+v_{x_i}\sum_{y_j\ge x_i}u_{y_j}+\sum_{y_j<x_i}w_{y_j}+u_{x_i}\sum_{y_j<x_i}v_{y_j}\right)\\
\end{aligned}
$$

由于每个区间加只会造成 $O(1)$ 个区间的加入与删除，所以第一维求和可以直接暴力求和维护。第二维则是很多个前缀求和与后缀求和，可以简单树状数组解决。啊但是这时候改的如果是 $b$，又变成很麻烦的样子了。所以我们还得推改 $b$ 时的贡献：

$$
\begin{aligned}
&\sum_j\sum_if(x_i,y_j)\\
=&\sum_j\sum_i[x_i\le y_j](w_{x_i}+v_{x_i}u_{y_j})+[x_i>y_j](w_{y_j}+v_{y_j}u_{x_i})\\
=&\sum_j\left(\sum_i[x_i\le y_j]w_{x_i}+u_{y_j}\sum_i[x_i\le y_j]v_{x_i}+w_{y_j}\sum_i[x_i>y_j]1+v_{y_j}\sum_i[x_i>y_j]u_{x_i}\right)\\
=&\sum_j\left(\sum_{x_i\le y_j}w_{x_i}+u_{y_j}\sum_{x_i\le y_j}v_{x_i}+w_{y_j}\sum_{x_i>y_j}1+v_{y_j}\sum_{x_i>y_j}u_{x_i}\right)\\
=&\sum_j\left(w_{y_j}\sum_{x_i\ge y_j}1+v_{y_j}\sum_{x_i\ge y_j}u_{x_i}+\sum_{x_i<y_j}w_{x_i}+u_{y_j}\sum_{x_i<y_j}v_{x_i}\right)\\
\end{aligned}
$$

那这两部分实际上完全一样，可以节省些码量。维护区间可以用 set 暴力查找，时间复杂度为 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;

inline ll u(ll n) { return n; }
inline ll v(ll n) { return n * (n + 1) / 2; }
inline ll w(ll n) { return n * (n + 1) * (2 * n + 1) / 6 - n * n * (n + 1) / 2; }

struct bit {
	
	int n; vector<ll> c;
	
	bit(int n) : n(n), c(n + 1) {}
	
	inline void add(int k, ll x) {
		if (k <= 0) return ;
		for (int i = k; i <= n; i += i & -i) c[i] += x;
	}
	
	inline ll ask(int k) {
		if (k <= 0) return 0; if (k > n) k = n; ll res = 0;
		for (int i = k; i; i &= i - 1) res += c[i];
		return res;
	}
	
};

struct maintainer {
	
	int n; bit a, b, c, d;
	
	maintainer(int n) : n(n), a(n), b(n), c(n), d(n) {}
	
	inline 
	void insert(int k) {
		a.add(n - k + 1, 1), b.add(n - k + 1, u(k));
		c.add(k, v(k)), d.add(k, w(k));
	}
	
	inline 
	void erase(int k) {
		a.add(n - k + 1, -1), b.add(n - k + 1, -u(k));
		c.add(k, -v(k)), d.add(k, -w(k));
	}
	
	inline 
	ll query(int m) {
		return w(m) * a.ask(n - m + 1) + v(m) * b.ask(n - m + 1) 
		+ u(m) * c.ask(m - 1) + d.ask(m - 1);
	}
	
};

struct node {
	
	maintainer &a, &b; ll ans;
	vector<int> d; set<int> s;
	
	inline void insert(int k) { a.insert(k), ans += b.query(k); }
	inline void erase(int k) { a.erase(k), ans -= b.query(k); }
	
	node(vector<int> t, maintainer &a, maintainer &b) : s(), d(t.size()), a(a), b(b), ans() {
		s.insert(0), s.insert(t.size());
		for (int i = 1; i < t.size(); i++) {
			d[i] = t[i] - t[i - 1];
			if (!d[i]) s.insert(i);
		}
		for (auto it = s.begin(); next(it) != s.end(); ++it) insert(*next(it) - *it);
	}
	
	inline 
	void change(int k, ll x) {
		if (!k || k == a.n) return ;
		if (!d[k] && d[k] + x) {
			auto it = s.find(k), pre = prev(it), nxt = next(it);
			erase(*it - *pre), erase(*nxt - *it), insert(*nxt - *pre);
			s.erase(it);
		}
		if (d[k] && !(d[k] + x)) {
			auto it = s.insert(k).first, pre = prev(it), nxt = next(it);
			erase(*nxt - *pre), insert(*it - *pre), insert(*nxt - *it);
		}
		d[k] += x;
	}
	
	inline void add(int l, int r, ll x) { change(l - 1, x), change(r, -x); }
	
};

int n, m, q;

int main() {
	scanf("%d%d%d", &n, &m, &q);
	vector<int> a(n), b(m);
	for (int &x : a) scanf("%d", &x);
	for (int &x : b) scanf("%d", &x);
	maintainer ta(n), tb(m);
	node pa(a, ta, tb), pb(b, tb, ta);
	printf("%lld\n", pa.ans + pb.ans);
	for (int t, l, r, x; q--;) {
		scanf("%d%d%d%d", &t, &l, &r, &x);
		t == 1 ? pa.add(l, r, x) : pb.add(l, r, x);
		printf("%lld\n", pa.ans + pb.ans);
	}
}
```

---

## 作者：honglan0301 (赞：3)

## 题目分析

容易发现一个正方形 $((i,j),(i+d,j+d))$ 合法当且仅当 $\forall i\leq p<i+d,a_i\neq a_{i+1}$ 且 $\forall j\leq p<j+d,b_j\neq b_{j+1}$，即正方形合法当且仅当 $a,b$ 序列的这两个子区间合法（我们定义序列的子区间合法当且仅当其中不存在相邻且相等的数）。

那么我们套路地对 $a,b$ 分别考虑，令 $ca_i$ 表示 $a$ 序列有多少长为 $i$ 的子区间，$cb_i$ 表示 $b$ 序列有多少长为 $i$ 的子区间，所求答案就等于 $\sum ca_i\times cb_i$。

于是我们就会不带修的情况了：以 $a$ 序列为例（$b$ 序列同理），我们找出所有极长合法连续段，一个长为 $k$ 的极长段对 $ca_i$ 的贡献就是 ${\max\{0,k-i+1\}}$。

再考虑带修怎么办：${\max\{0,k-i+1\}}$ 其实等价于前缀加公差为 $-1$ 的等差数列。而区间加显然只会导致 $O(1)$ 个极长段的变化，那只需要动态地维护以下操作即可：

1. 对 $ca$ 序列前缀加/减公差为 $-1$ 的等差数列。

2. 对 $cb$ 序列前缀加/减公差为 $-1$ 的等差数列。

3. 查询全局 $\sum ca_i\times cb_i$。

我们进行序列分块，散块操作平凡，这里说一下对整块全局加/减等差数列的影响。对每块 $[l,r]$ 维护 $suma=\sum\limits_{i=l}^r ca_i,sumsa=\sum\limits_{i=l}^r\sum\limits_{j=l}^i ca_i,sumb=\sum\limits_{i=l}^r cb_i,sumsb=\sum\limits_{i=l}^r\sum\limits_{j=l}^i cb_i,sumab=\sum\limits_{i=l}^r ca_i\times cb_i$，那么对 $ca$ 序列加上首项为 $s$，公差为 $-1$ 的等差数列的影响就是：

$$suma\gets suma+f_{0,r-l+1}\times(s-(r-l+1))+f_{1,r-l+1}$$

$$sumsa\gets sumsa+f_{1,r-l+1}\times(s-(r-l+1))+f_{2,r-l+1}$$

$$sumab\gets sumab+sumb\times(s-(r-l+1))+sumsb$$

其中 $f_{k,i}=\sum\limits_{j=1}^i j^k$。

于是做完了，时间复杂度 $O((n+q)\sqrt n)$，我赛后卡了很久常才过。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define endl "\n"
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define ull unsigned long long
#define mod 998244353
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));
 
int n,m,q,a[300005],b[300005],op,u,v,w;
 
struct ODT
{
	int l,r;
	bool operator<(const ODT &x) const
	{
		return l<x.l;
	}
};
set <ODT> oa,ob;
 
void initA()
{
	int nl=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1]) oa.insert({nl,i-1}),nl=i;
	}
	oa.insert({nl,n});
	nl=1;
	for(int i=2;i<=m;i++)
	{
		if(b[i]==b[i-1]) ob.insert({nl,i-1}),nl=i;
	}
	ob.insert({nl,m});
}
int tra[300005],trb[300005];
#define lowbit(x) (x&(-x))
void adda(int x,int k) {for(int i=x;i<=n;i+=lowbit(i)) tra[i]+=k;}
void addb(int x,int k) {for(int i=x;i<=m;i+=lowbit(i)) trb[i]+=k;}
int aska(int x) {int na=0; for(int i=x;i>0;i-=lowbit(i)) na+=tra[i]; return na;}
int askb(int x) {int na=0; for(int i=x;i>0;i-=lowbit(i)) na+=trb[i]; return na;}
 
#define B 345
int K[300005],L[1005],R[1005],len[1005],suma[1005],sumb[1005],sumsa[1005],sumsb[1005],sumab[1005];
int taga[1005],csa[1005],tagb[1005],csb[1005],bh[1005],fta[1005],fca[1005],ftb[1005],fcb[1005];
int aa[300005],bb[300005],ans;
 
void initk()
{
	memset(L,127,sizeof(L));
	for(int i=1;i<=max(n,m);i++) K[i]=(i-1)/B+1,L[K[i]]=min(L[K[i]],i),R[K[i]]=max(R[K[i]],i);
	for(int i=1;i<=K[max(n,m)];i++) len[i]=R[i]-L[i]+1;
}
void build(int p)
{
	for(int i=L[p];i<=R[p];i++)
	{
		aa[i]+=taga[p]-csa[p]*(i-L[p]);
		bb[i]+=tagb[p]-csb[p]*(i-L[p]);
	}
	taga[p]=tagb[p]=csa[p]=csb[p]=fta[p]=fca[p]=ftb[p]=fcb[p]=0;
}
void re(int p)
{
	suma[p]=sumb[p]=sumsa[p]=sumsb[p]=sumab[p]=0;
	for(int i=L[p];i<=R[p];i++)
	{
		suma[p]+=aa[i]; sumsa[p]+=suma[p];
		sumb[p]+=bb[i]; sumsb[p]+=sumb[p]; sumab[p]+=aa[i]*bb[i];
	}
	bh[p]=0;
}
int calc1(int l,int r)
{
	return (l+r)*(r-l+1)/2;
}
int calc2(int l,int len)
{
	int nans=(l-1)*calc1(1,len);
	nans+=len*(len+1)*(2*len+1)/6; return nans;
}
int val1[300005],val2[300005];
void init2()
{
	for(int i=1;i<=max(n,m);i++) val1[i]=i*(i+1)/2,val2[i]=i*(i+1)*(2*i+1)/6;
}
int nmx=0;
void CZA(int r,int k)
{
	int l=1; nmx=max(nmx,r);
	if(K[l]==K[r])
	{
		ans-=sumab[K[l]];
		build(K[l]);
		for(int i=l;i<=r;i++) aa[i]+=k*(r-i+1);
		re(K[l]); 
		ans+=sumab[K[l]]; return;
	}
	ans-=sumab[K[r]];
	build(K[r]); for(int i=L[K[r]];i<=r;i++) aa[i]+=k*(r-i+1); re(K[r]);
	ans+=sumab[K[r]];
	for(int i=1;i<=K[r]-1;i++)
	{
		int addl=r-L[i]+1,addr=(r-R[i]);
		taga[i]+=k*addl; csa[i]+=k; 
		fta[i]+=k*addl; fca[i]+=k; bh[i]=1;
	}
}
void CZB(int r,int k)
{
	int l=1; nmx=max(nmx,r);
	if(K[l]==K[r])
	{
		ans-=sumab[K[l]];
		build(K[l]);
		for(int i=l;i<=r;i++) bb[i]+=k*(r-i+1);
		re(K[l]);
		ans+=sumab[K[l]]; return;
	}
	ans-=sumab[K[r]];
	build(K[r]); for(int i=L[K[r]];i<=r;i++) bb[i]+=k*(r-i+1); re(K[r]);
	ans+=sumab[K[r]];
	for(int i=1;i<=K[r]-1;i++)
	{
		int addl=r-L[i]+1,addr=(r-R[i]);
		tagb[i]+=k*addl; csb[i]+=k;
		ftb[i]+=k*addl; fcb[i]+=k; bh[i]=1;
	}
}
void GA(int r)
{
	for(int i=1;i<=K[r]-1;i++)
	{
		if(!bh[i]) continue;
		int addr=fta[i]-fca[i]*len[i];
		ans-=sumab[i];
		suma[i]+=addr*len[i]+fca[i]*val1[len[i]];
		sumsa[i]+=addr*val1[len[i]]+fca[i]*val2[len[i]];
		sumab[i]+=addr*sumb[i]+fca[i]*sumsb[i];
		ans+=sumab[i];
		fta[i]=fca[i]=bh[i]=0;
	}
}
void GB(int r)
{
	for(int i=1;i<=K[r]-1;i++)
	{
		if(!bh[i]) continue;
		int addr=ftb[i]-fcb[i]*len[i];
		ans-=sumab[i];
		sumb[i]+=addr*len[i]+fcb[i]*val1[len[i]];
		sumsb[i]+=addr*val1[len[i]]+fcb[i]*val2[len[i]];
		sumab[i]+=addr*suma[i]+fcb[i]*sumsa[i];
		ans+=sumab[i];
		ftb[i]=fcb[i]=bh[i]=0;
	}
}
int ask()
{
	int na=0;
	for(int i=1;i<=K[max(n,m)];i++) na+=sumab[i]; return na;
}
 
void cza(int x,int k)
{
	if(x==1||x==n+1) return adda(x,k),void();
	int op1=aska(x-1)==aska(x);
	adda(x,k);
	int op2=aska(x-1)==aska(x);
	if(op1==op2) return;
	nmx=0;
	if(op1==0&&op2==1)
	{
		auto it=--oa.upper_bound({x-1,0});
		auto lst=(*it);
		CZA(lst.r-lst.l+1,-1); oa.erase(it);
		CZA(x-1-lst.l+1,1); oa.insert({lst.l,x-1});
		CZA(lst.r-x+1,1); oa.insert({x,lst.r});
	}
	else
	{
		auto itl=--oa.upper_bound({x-1,0}),itr=--oa.upper_bound({x,0});
		int l=(*itl).l,r=(*itr).r;
		CZA((*itl).r-(*itl).l+1,-1); CZA((*itr).r-(*itr).l+1,-1); itr++; oa.erase(itl,itr);
		CZA(r-l+1,1); oa.insert({l,r});
	}
	GA(nmx);
}
void czb(int x,int k)
{
	if(x==1||x==n+1) return addb(x,k),void();
	int op1=askb(x-1)==askb(x);
	addb(x,k);
	int op2=askb(x-1)==askb(x);
	if(op1==op2) return;
	nmx=0;
	if(op1==0&&op2==1)
	{
		auto it=--ob.upper_bound({x-1,0});
		auto lst=(*it);
		CZB(lst.r-lst.l+1,-1); ob.erase(it);
		CZB(x-1-lst.l+1,1); ob.insert({lst.l,x-1});
		CZB(lst.r-x+1,1); ob.insert({x,lst.r});
	}
	else
	{
		auto itl=--ob.upper_bound({x-1,0}),itr=--ob.upper_bound({x,0});
		int l=(*itl).l,r=(*itr).r;
		CZB((*itl).r-(*itl).l+1,-1); CZB((*itr).r-(*itr).l+1,-1); itr++; ob.erase(itl,itr);
		CZB(r-l+1,1); ob.insert({l,r});
	}
	GB(nmx);
}
 
signed main()
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>a[i],adda(i,a[i]-a[i-1]);
	for(int i=1;i<=m;i++) cin>>b[i],addb(i,b[i]-b[i-1]);
	initA(); initk(); init2();
	for(auto i:oa) CZA(i.r-i.l+1,1);
	for(auto i:ob) CZB(i.r-i.l+1,1);
	ans=0;
	for(int i=1;i<=K[max(n,m)];i++) build(i),re(i),ans+=sumab[i];
	cout<<ans<<endl;
	for(int i=1;i<=q;i++)
	{
		cin>>op>>u>>v>>w;
		if(w==0) {cout<<ans<<endl; continue;}
		if(op==1)
		{
			cza(u,w); cza(v+1,-w);
		}
		else
		{
			czb(u,w); czb(v+1,-w);
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：EuphoricStar (赞：2)

为什么我场上被卡常了。

转化题意，将 $a, b$ 差分，答案为在 $a, b$ 选出相同长度的不含 $0$ 的子段方案数。

设 $a$ 选出长度为 $i$ 的不含 $0$ 的子段方案数为 $x_i$，$b$ 选出长度为 $i$ 的不含 $0$ 的子段方案数为 $y_i$。答案为 $\sum x_i y_i$。考虑线段树维护这个东西。

一个 $a$ 中长度为 $l$ 的极长子段会给 $\forall k \in [1, l]$ 的 $x_k$ 贡献 $k - l  + 1$。$b$ 同理。$k + 1$ 和 $-l$ 是独立的，先考虑 $-l$ 这部分。也就是要支持 $x_i \gets x_i + di$ 或 $y_i \gets y_i + di$。

只考虑修改 $x$，$y$ 是对称的。拆式子：$\sum (x_i + di) y_i = \sum x_i y_i + d \sum i y_i$。再维护 $\sum i x_i$ 和 $\sum i y_i$ 就可以完成 $\sum x_i y_i$ 的修改。$\sum i x_i$ 的修改是容易的，考虑 $\sum i (x_i + i) = \sum i x_i + \sum i^2$，后者显然可以 $O(1)$ 求的。

还要支持 $x_i \gets x_i + d$ 或者 $y_i \gets y_i + d$。继续拆式子：$\sum (x_i + d) y_i = \sum x_i y_i + d \sum x_i$。再维护 $\sum x_i, \sum y_i$ 即可。

于是线段树每个结点维护 $5$ 个值：$\sum x_i y_i, \sum x_i, \sum y_i, \sum i x_i, \sum i y_i$ 和 $4$ 种懒标记即可。

差分后区间加变成了单点修改。考虑对 $a, b$ 分别开个 `set` 维护非 $0$ 极长连续段。显然单点修改只会加入或删除 $O(1)$ 个段，讨论下就行了。

时间复杂度 $O((n + q) \log n)$，但是线段树的常数巨大，实现精细点就能过了。

[真的有人会想看 7KB+ 的代码吗？](https://codeforces.com/contest/1928/submission/245855764)

---

## 作者：Eraine (赞：1)

编号：CF1928F

tag：数据结构，推式子

这里是 $\Theta(n\log n)$ 但是大常数做法。

题目大意解释一下。给定一个 $n\times m$ 的矩阵 $a$，$a_{i,j}$ 的值为 $r_i+c_j$。求相邻两个元素不相等的正方形个数。

我们很容易将题目转换成求满足对应行和列的相邻权值不相等的正方形的个数。容易发现，对于 $1\times 1$ 的正方形无论如何修改都是满足条件的，所以我们只考虑边长 $\ge 2$ 的正方形。我们将条件转换成相邻元素差 $\ne0$。在差分矩阵中，每个正方形的边长对应减少 $1$。

考虑一次更改会对答案造成什么影响。一次更改是列或行区间加，在差分数组上至多两个值发生更改。为了维护个数，我们需要维护差分数组中不为 $0$ 的极长连续段。$\text{set}$ 简单维护即可。（感谢 $\text{R}\color{red}{\text{egister\_int}}$ 奆佬的提醒，不然笔者就傻*地去写 $\text{fhq-Treap}$ 了）两个值发生更改，于是顶多三段的值（$(l,pos),(pos,r),(l,r)$）会对答案产生贡献。

由于 $a,b$ 贡献对称，所以这里只阐述 $b$ 更改时的贡献。考虑新加进长度为 $b$ 的极长连续段。对于 $a\le b$ 的情况，贡献为 $\sum_{i=1}^ai(b-a+i)$，式子可以推成（本篇题解不展示推式子过程）：

$$\sum_{i=1}^ai^2-a\sum_{i=1}^ai+b\sum_{i=1}^ai$$

这三个部分都可以用支持单点修改，区间求和的值域数据结构维护。本篇题解采用修改和查询复杂度均为 $\Theta(\log n)$ 的树状数组。同理，对于 $a\gt b$ 的部分，贡献为 $\sum_{i=1}^bi(a-b+i)$。式子可以推成：

$$\sum_{i=1}^bi^2+a\sum_{i=1}^bi-b\sum_{i=1}^bi$$

注意这个式子的第 $1$ 项和第 $3$ 项的系数和 $a$ 有关，虽然是 $1$，但也要维护。

$\Theta(n\log n)$。

赛后代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+5;
int n,m,q,lmt,a[N],b[N];
struct bitTree{
	ll sub[N];
#define lowbit(i) (i&(-i))
	void add(int x,ll k){
		for(int i=x;i<=lmt;i=i+lowbit(i)){
			sub[i]=sub[i]+k;
		}
	}
	ll getsum(int x){
		ll res=0;
		for(int i=x;i;i=i-lowbit(i)){
			res=res+sub[i];
		}
		return res;
	}
}bit[10];
set<int>sa,sb;
ll f1(ll x){
	return x*(x+1)/2;
}
ll f2(ll x){
	return x*(x+1)*(2*x+1)/6;
}
ll calcA(int x){
	ll res=0;
	res=res+bit[9].getsum(x);
	res=res-bit[8].getsum(x);
	res=res+x*bit[7].getsum(x);
	res=res+f2(x)*(bit[5].getsum(lmt)-bit[5].getsum(x));
	res=res+f1(x)*(bit[6].getsum(lmt)-bit[6].getsum(x));
	res=res-f1(x)*x*(bit[5].getsum(lmt)-bit[5].getsum(x));
	return res;
}
ll calcB(int x){
	ll res=0;
	res=res+bit[4].getsum(x);
	res=res-bit[3].getsum(x);
	res=res+x*bit[2].getsum(x);
	res=res+f2(x)*(bit[0].getsum(lmt)-bit[0].getsum(x));
	res=res+f1(x)*(bit[1].getsum(lmt)-bit[1].getsum(x));
	res=res-f1(x)*x*(bit[0].getsum(lmt)-bit[0].getsum(x));
	return res;
}
ll ans;
void adda(int pos){
	auto it=sa.lower_bound(pos);
	int len1,len2,len3;
	len2=*it-pos;
	--it;
	len1=pos-*it;
	len3=len1+len2;
	--len1;
	--len2;
	--len3;
	if(len1){
		ans=ans+calcA(len1);
		bit[0].add(len1,1);
		bit[1].add(len1,len1);
		bit[2].add(len1,f1(len1));
		bit[3].add(len1,len1*f1(len1));
		bit[4].add(len1,f2(len1));
	}
	if(len2){
		ans=ans+calcA(len2);
		bit[0].add(len2,1);
		bit[1].add(len2,len2);
		bit[2].add(len2,f1(len2));
		bit[3].add(len2,len2*f1(len2));
		bit[4].add(len2,f2(len2));
	}
	if(len3){
		ans=ans-calcA(len3);
		bit[0].add(len3,-1);
		bit[1].add(len3,-len3);
		bit[2].add(len3,-f1(len3));
		bit[3].add(len3,-len3*f1(len3));
		bit[4].add(len3,-f2(len3));
	}
	sa.insert(pos);
}
void addb(int pos){
	auto it=sb.lower_bound(pos);
	int len1,len2,len3;
	len2=*it-pos;
	--it;
	len1=pos-*it;
	len3=len1+len2;
	--len1;
	--len2;
	--len3;
	if(len1){
		ans=ans+calcB(len1);
		bit[5].add(len1,1);
		bit[6].add(len1,len1);
		bit[7].add(len1,f1(len1));
		bit[8].add(len1,len1*f1(len1));
		bit[9].add(len1,f2(len1));
	}
	if(len2){
		ans=ans+calcB(len2);
		bit[5].add(len2,1);
		bit[6].add(len2,len2);
		bit[7].add(len2,f1(len2));
		bit[8].add(len2,len2*f1(len2));
		bit[9].add(len2,f2(len2));
	}
	if(len3){
		ans=ans-calcB(len3);
		bit[5].add(len3,-1);
		bit[6].add(len3,-len3);
		bit[7].add(len3,-f1(len3));
		bit[8].add(len3,-len3*f1(len3));
		bit[9].add(len3,-f2(len3));
	}
	sb.insert(pos);
}
void dela(int pos){
	sa.erase(pos);
	auto it=sa.lower_bound(pos);
	int len1,len2,len3;
	len2=*it-pos;
	--it;
	len1=pos-*it;
	len3=len1+len2;
	--len1;
	--len2;
	--len3;
	if(len1){
		ans=ans-calcA(len1);
		bit[0].add(len1,-1);
		bit[1].add(len1,-len1);
		bit[2].add(len1,-f1(len1));
		bit[3].add(len1,-len1*f1(len1));
		bit[4].add(len1,-f2(len1));
	}
	if(len2){
		ans=ans-calcA(len2);
		bit[0].add(len2,-1);
		bit[1].add(len2,-len2);
		bit[2].add(len2,-f1(len2));
		bit[3].add(len2,-len2*f1(len2));
		bit[4].add(len2,-f2(len2));
	}
	if(len3){
		ans=ans+calcA(len3);
		bit[0].add(len3,1);
		bit[1].add(len3,len3);
		bit[2].add(len3,f1(len3));
		bit[3].add(len3,len3*f1(len3));
		bit[4].add(len3,f2(len3));
	}
}
void delb(int pos){
	sb.erase(pos);
	auto it=sb.lower_bound(pos);
	int len1,len2,len3;
	len2=*it-pos;
	--it;
	len1=pos-*it;
	len3=len1+len2;
	--len1;
	--len2;
	--len3;
	if(len1){
		ans=ans-calcB(len1);
		bit[5].add(len1,-1);
		bit[6].add(len1,-len1);
		bit[7].add(len1,-f1(len1));
		bit[8].add(len1,-len1*f1(len1));
		bit[9].add(len1,-f2(len1));
	}
	if(len2){
		ans=ans-calcB(len2);
		bit[5].add(len2,-1);
		bit[6].add(len2,-len2);
		bit[7].add(len2,-f1(len2));
		bit[8].add(len2,-len2*f1(len2));
		bit[9].add(len2,-f2(len2));
	}
	if(len3){
		ans=ans+calcB(len3);
		bit[5].add(len3,1);
		bit[6].add(len3,len3);
		bit[7].add(len3,f1(len3));
		bit[8].add(len3,len3*f1(len3));
		bit[9].add(len3,f2(len3));
	}
}
int main(){
	lmt=3e5;
	scanf("%d%d%d",&n,&m,&q);
	if(n==1||m==1){
		for(int i=0;i<=q;i++){
			printf("%d\n",max(n,m));
		}
		return 0;
	}
	for(int i=1;i<=min(n,m);i++){
		ans=ans+(ll)(n-i+1)*(m-i+1);
	}
	bit[0].add(n-1,1);
	bit[1].add(n-1,n-1);
	bit[2].add(n-1,f1(n-1));
	bit[3].add(n-1,(n-1)*f1(n-1));
	bit[4].add(n-1,f2(n-1));
	bit[5].add(m-1,1);
	bit[6].add(m-1,m-1);
	bit[7].add(m-1,f1(m-1));
	bit[8].add(m-1,(m-1)*f1(m-1));
	bit[9].add(m-1,f2(m-1));
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
	sa.insert(0);
	sa.insert(n);
	sb.insert(0);
	sb.insert(m);
	for(int i=1;i<n;i++){
		a[i]=a[i+1]-a[i];
		if(!a[i]){
			adda(i);
		}
	}
	for(int i=1;i<m;i++){
		b[i]=b[i+1]-b[i];
		if(!b[i]){
			addb(i);
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=q;i++){
		int t,l,r;ll k;
		scanf("%d%d%d%lld",&t,&l,&r,&k);
		if(t==1){
			if(l-1>0){
				if(!a[l-1]){
					dela(l-1);
				}
				a[l-1]=a[l-1]+k;
				if(!a[l-1]){
					adda(l-1);
				}
			}
			if(r<n){
				if(!a[r]){
					dela(r);
				}
				a[r]=a[r]-k;
				if(!a[r]){
					adda(r);
				}
			}
		}else{
			if(l-1>0){
				if(!b[l-1]){
					delb(l-1);
				}
				b[l-1]=b[l-1]+k;
				if(!b[l-1]){
					addb(l-1);
				}
			}
			if(r<m){
				if(!b[r]){
					delb(r);
				}
				b[r]=b[r]-k;
				if(!b[r]){
					addb(r);
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


5.5k。又臭又长。各位看官点个赞再走吧 qwq

---

## 作者：hcywoi (赞：0)

### 题意

- 给定一个 $n\times m$ 的矩阵，每行有一个系数 $a_i$，每列有一个系数 $b_i$。
- 有 $q$ 次修改，每次修改给 $a$ 的一段区间加 $x$ 或给 $b$ 的一段区间加 $x$。
- 定义一个格子 $(i, j)$ 的权值为 $a_i+b_j$。
- 求出每次修改后和原始矩阵有多少个子矩阵满足相邻格子的权值互不相同。
- 子矩阵的定义：所有 $(i, j)$ 满足 $x\le i\le x+d, y\le j\le y+d$ 的集合。
- $1\le n, m\le 3\times 10^5, 0\le q\le 3\times 10^5$。

---

如果 $a_i=a_{i+1}$，那么 $\forall j\in [1, m]$，$(i, j)$ 和 $(i+1, j)$ 的权值相等，$b_i=b_{i+1}$ 也同理。所以一个子矩阵合法等价于不存在 $a_i=a_{i+1}$ 和 $b_i=b_{i+1}$。

假设 $a_i\neq a_{i+1}$ 并且 $b_i\neq b_{i+1}$，怎么求出有多少个子矩阵。

记 $f(n, m)$ 表示矩阵大小为 $n\times m$ 有多少个子矩阵。假设 $n\le m$，$f(n, m)=\sum_{k=1}^{n}(n-k+1)(m-k+1)=\sum_{k=1}^{n}(k^2+(m-n)k)=\frac{n(n+1)(2n+1)}{6}+(m-n)\frac{n(n+1)}{2}$。

记 $a_n=1, b_n=n, c_n=\frac{n(n+1)}{2}, d_n=\frac{n(n+1)(2n+1)}{6}-\frac{n^2(n+1)}{2}$，那么对于 $n\le m$，$f(n, m)=d_na_m+c_nb_m$，对于 $n>m$，$f(n, m)=a_nd_m+b_nc_m$。

---

如果有相邻的元素相等，相当于将矩阵分成若干块，记 $n_{1\sim k}$ 表示 $a$ 中块的长度，$m_{1\sim l}$ 表示 $b$ 中块的长度。那么答案为 $\sum_{i=1}^{k}\sum_{j=1}^{l}f(n_i, m_j)$。

考虑如何快速求出 $f(x, m_1)+f(x, m_2)+\cdots + f(x, m_l)$。

等价于求出 $a_x\sum_{m_i<x}d_{m_i}+b_x\sum_{m_i<x}c_{m_i}+c_x\sum_{m_i\ge x}b_{m_i}+d_x\sum_{m_i\ge x}a_{m_i}$。我们用权值树状数组维护 $\sum a_{w}$, $\sum b_{w}$, $\sum c_{w}$, $\sum d_{w}$ 即可。计算 $f(n_1, x)+f(n_2, x)+\cdots + f(n_k, x)$ 也同理。

对于序列 $a$ 修改，最多改变 $3$ 个块的长度，记 $x$ 为之前的块长，$x'$ 为现在的块长，那么相当于减去 $f(x, m_1)+f(x, m_2)+\cdots+f(x, m_l)$，加上 $f(x', m_1)+f(x', m_2)+\cdots+ f(x', m_l)$，对于 $b$ 的修改也同理。

我们可以用 `std::set` 来维护所有 $a_i=a_{i+1}$ 和 $b_i=b_{i+1}$ 的位置。

将 $a, b$ 变成差分数组 $c, d$，那么 $c_i=0$ 等价于 $a_i=a_{i-1}$，$d_i=0$ 等价于 $b_{i}=b_{i-1}$，实现方便些。

时间复杂度：$O(n\log n)$。

---

## 作者：Z1qqurat (赞：0)

非常标准的 CF 式 DS，很有启发。

首先观察一下限制，两个相邻格子权值相同当且仅当相邻两行 $a_i=a_{i+1}$ 或者两列权值相同 $b_i=b_{i+1}$。发现相当于如果 $a_i=a_{i+1}$，就是把 $a$ 划分为若干段，不同段的点不能在一起选，$b$ 同理，其实就是说把整个 $n\times m$ 划分为了若干小长方形，只能从一个长方形内选择小矩形。假设 $a$ 划分为了长度分别为 $n_1,n_2,\cdots,n_l$ 的段，$b$ 划分为了长度分别为 $m_1,m_2\cdots,m_r$ 的段，记 $f(n,m)$ 表示一个 $n\times m$ 的能选出多少个本质不同子矩形，那么如果 $n\le m$，有：

$$
\begin{aligned}
f(n,m)&=\sum\limits_{i=1}^n (n-i+1)(m-i+1)\\
&=n(n+1)(m+1)-(n+m+2)\sum\limits_{i=1}^n i+ \sum\limits_{i=1}^n i^2\\
&=n(n+1)(m+1)-(n+m+2)\frac{n(n+1)}{2}+\frac{n(n+1)(2n+1)}{6}\\
&= (m-n)\frac{n(n+1)}{2}+\frac{n(n+1)(2n+1)}{6}
\end{aligned}
$$

于是答案就是 $\sum\limits_{i=1}^l \sum\limits_{j=1}^r f(n_i,m_j)$，考虑如果带修了怎么做。维护值域线段树，如果 $n$ 上有值（$a$ 有长为 $n$ 的极长连续段），那么 $a_n=1,b_n=n,c_n=\frac{n(n+1)}{2},d_n=\frac{n(n+1)(2n+1)}{6}-\frac{n^2(n+1)}{2}$。于是可以得到转化：

$$
f(n,m)=
\begin{cases}
a_n d_m+b_n c_m &(n\le m)\\
d_n a_m+c_n b_m &(n> m)
\end{cases}
$$

那么考虑在值域线段树上维护每种连续段长度区间内对应的 $\sum a_n,\sum b_n,\sum c_n,\sum d_n$，对于行、列分开两个线段树分别维护这 $4$ 种信息，每次修改的时候，分开讨论两个端点 $l,r$ 的情况是否会改变，要么是裂开一个连续段，要么是合并两个连续段，或者不变，直接在值域线段树上改节点对应的 $\sum a_n,\sum b_n,\sum c_n,\sum d_n$ 即可，单点修改。

询问答案的话考虑到每次只会修改到 $\mathcal{O}(1)$ 条线段的长度，直接维护答案的变化量（转化为区间询问），以修改 $a$ 为例，变化量应该是 $f(x,m_1)+f(x,m_2)+\dots+f(x,m_l)$ 的形式，那么将 $m_{1\sim l}$ 中 $\le x$ 和 $>x$ 的部分分开考虑，可以转化为线段树上 $4$ 次询问（也可以压缩为两次减小常数）：$a_x\sum\limits_{i=1}^{x} d_i+b_x\sum\limits_{i=1}^{x} c_i+c_x\sum\limits_{i=x+1}^{m} b_i+d_x\sum\limits_{i=x+1}^{m} a_i$，所以直接可以 $\mathcal{O}((n+m+q)\log (n+m))$ 解决。

还有一些细节，比如要支持区间加，单点查询 $a$ 的值，可以用树状数组维护 $a$ 的差分；要维护有哪些连续段，可以用 std::set 分别记录 $a,b$ 中连续段的所有右端点。由于修改的时候要对 $l,r$ 都讨论一遍，所以一些功能封装成函数可以很好地减小代码量。~~虽然但是我仍然写了 5.3KB。~~

注意一些实现细节，比如说把 $0,n$（或者 $0,m$）也提前放入存右端点的 set 以及将树状数组、线段树都封装写成 struct 可以规避很多边界问题。总之写起来很舒服，没怎么调就过了。

[Submission.](https://codeforces.com/problemset/submission/1928/246625151)

---

## 作者：MaxBlazeResFire (赞：0)

我们发现一个正方形合法当且仅当形成它的两个子区间分别满足没有相邻相同元素。换句话说，$a,b$ 中每一对等长的没有相邻相同元素的子区间都可以做贡献。如果记 $A_i,B_i$ 表示长度为 $i$ 的合法区间个数，答案就是 $\displaystyle\sum_{i=1}^nA_iB_i$。如果不带修，考虑对两个序列分别扫描线，然后就是区间加。

考虑算上区间加操作，重新记 $c_i=[a_i\neq a_{i-1}],d_i=[b_i\neq b_{i-1}]$（$c_1,d_1=0$），那么序列 $c,d$ 每一个长度为 $K$ 的极长 $1$ 连续段可以为 $A_i,B_i$ 贡献 $K+2-i$。一次区间加操作会修改 $O(1)$ 个 $c,d$ 的值，考虑暴力维护 $c,d$ 的极长连续段，问题转化为前缀加减等差数列，全局 $A_iB_i$ 和查询。

可以硬拆贡献。开一棵线段树，维护区间 $A_iB_i$ 和，区间 $iB_i,iA_i$ 和，区间 $A,B$ 和即可，因为线段树的标记总可以写作 $A$ 或 $B$ 区间 $+ki+C$ 的形式。

复杂度 $O((n+q)\log n)$。

```cpp
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MAXN 300005

const int INF = 1000000000;
const int Lim = 300000;

inline int read(){
	int x = 0,f = 1; char ch = getchar();
	while( ch < '0' || ch > '9' ){ f = ch == '-' ? -1 : 1; ch = getchar(); }
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48,ch = getchar();
	return x * f;
}

void write( ll x ){
	if( x >= 10 ) write( x / 10 );
	putchar( x % 10 + 48 );
}

int n,m,q,a[MAXN],b[MAXN];
ll tra[MAXN + 5],trb[MAXN + 5],s[MAXN],S[MAXN];
int c[MAXN],d[MAXN];

inline void add( ll *tr , int x , int k ){ for( ; x <= MAXN ; x += x & -x ) tr[x] += k; }
inline ll sum( ll *tr , int x ){ ll ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }

struct mes{
	ll sab;
	ll ai,bi,sa,sb;
}M[MAXN << 2];

struct tag{
	ll ka,ca,kb,cb;
	inline bool isc(){ return !ka && !ca && !kb && !cb; }
	inline void clear(){ ka = ca = kb = cb = 0; }
}T[MAXN << 2];

inline mes operator +( mes A , mes B ){
	A.sab += B.sab;
	A.ai += B.ai,A.bi += B.bi;
	A.sa += B.sa,A.sb += B.sb;
	return A;
}

inline tag operator *( tag A , tag B ){
	A.ka += B.ka,A.ca += B.ca;
	A.kb += B.kb,A.cb += B.cb;
	return A;
}

//( A[i] + kai + ca )( B[i] + kbi + cb )
inline mes apply( mes A , tag B , int l , int r ){
	ll sum = s[r] - s[l - 1],summ = S[r] - S[l - 1],delta = 0;
	ll ka = B.ka,kb = B.kb,ca = B.ca,cb = B.cb;
	mes C = A;
	kb ? delta += ( A.ai + ka * summ ) * kb,C.bi += kb * summ,C.sb += kb * sum : 0;
	ka ? delta += A.bi * ka,C.ai += ka * summ,C.sa += ka * sum : 0;
	cb ? delta += ( A.sa + ka * sum + ca * ( r - l + 1 ) ) * cb,C.bi += cb * sum,C.sb += cb * ( r - l + 1 ) : 0;
	ca ? delta += ( A.sb + kb * sum ) * ca,C.ai += ca * sum,C.sa += ca * ( r - l + 1 ) : 0;
	C.sab += delta;
	return C;
}

inline void update( int t , tag Tag , int l , int r ){ M[t] = apply( M[t] , Tag , l , r ),T[t] = T[t] * Tag; }

inline void push_down( int t , int l , int r ){
	int mid = ( l + r ) >> 1;
	if( !T[t].isc() ){
		M[t * 2] = apply( M[t * 2] , T[t] , l , mid );
		T[t * 2] = T[t * 2] * T[t];
		M[t * 2 + 1] = apply( M[t * 2 + 1] , T[t] , mid + 1 , r );
		T[t * 2 + 1] = T[t * 2 + 1] * T[t];
		T[t].clear();
	}
}

void modify( int t , int l , int r , int Ql , int Qr , tag T ){
	if( Ql <= l && r <= Qr ){
		update( t , T , l , r );
		return;
	}
	push_down( t , l , r ); int mid = ( l + r ) >> 1;
	if( Ql <= mid ) modify( t * 2 , l , mid , Ql , Qr , T );
	if( Qr > mid ) modify( t * 2 + 1 , mid + 1 , r , Ql , Qr , T );
	M[t] = M[t * 2] + M[t * 2 + 1];
}

set< pair<int,int> > As,Bs;
inline void applyA( int x , int k ){
	c[x] = k;
	if( k ){
		set< pair<int,int> >::iterator it = As.lower_bound( make_pair( x , x ) ),it2 = it; it2 --;
		int L = x,R = x;
		if( it != As.end() && it -> first == x + 1 ){
			int len = it -> second - it -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 1 , -( len + 2 ) , 0 , 0 } );
			R = it -> second;
			As.erase( it );
		}
		if( it2 != As.end() && it2 -> second == x - 1 ){
			int len = it2 -> second - it2 -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 1 , -( len + 2 ) , 0 , 0 } );
			L = it2 -> first;
			As.erase( it2 );
		}
		int len = R - L + 1;
		modify( 1 , 1 , Lim , 2 , len + 1 , tag{ -1 , len + 2 , 0 , 0 } );
		As.insert( make_pair( L , R ) );
	}
	else{
		set< pair<int,int> >::iterator it = As.upper_bound( make_pair( x , INF ) ); it --;
		if( it != As.end() && it -> first <= x && x <= it -> second ){
			int len = it -> second - it -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 1 , -( len + 2 ) , 0 , 0 } );
			if( x != it -> first ){
				len = x - it -> first;
				modify( 1 , 1 , Lim , 2 , len + 1 , tag{ -1 , len + 2 , 0 , 0 } );
				As.insert( make_pair( it -> first , x - 1 ) );
			}
			if( x != it -> second ){
				len = it -> second - x;
				modify( 1 , 1 , Lim , 2 , len + 1 , tag{ -1 , len + 2 , 0 , 0 } );
				As.insert( make_pair( x + 1 , it -> second ) );
			}
			As.erase( it );
		}
	}
}

inline void applyB( int x , int k ){
	d[x] = k;
	if( k ){
		set< pair<int,int> >::iterator it = Bs.lower_bound( make_pair( x , x ) ),it2 = it; it2 --;
		int L = x,R = x;
		if( it != Bs.end() && it -> first == x + 1 ){
			int len = it -> second - it -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , 1 , -( len + 2 ) } );
			R = it -> second;
			Bs.erase( it );
		}
		if( it2 != Bs.end() && it2 -> second == x - 1 ){
			int len = it2 -> second - it2 -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , 1 , -( len + 2 ) } );
			L = it2 -> first;
			Bs.erase( it2 );
		}
		int len = R - L + 1;
		modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , -1 , len + 2 } );
		Bs.insert( make_pair( L , R ) );
	}
	else{
		set< pair<int,int> >::iterator it = Bs.upper_bound( make_pair( x , INF ) ); it --;
		if( it != Bs.end() && it -> first <= x && x <= it -> second ){
			int len = it -> second - it -> first + 1;
			modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , 1 , -( len + 2 ) } );
			if( x != it -> first ){
				len = x - it -> first;
				modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , -1 , len + 2 } );
				Bs.insert( make_pair( it -> first , x - 1 ) );
			}
			if( x != it -> second ){
				len = it -> second - x;
				modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , -1 , len + 2 } );
				Bs.insert( make_pair( x + 1 , it -> second ) );
			}
			Bs.erase( it );
		}
	}
}

signed main(){
	for( int i = 0 ; i < MAXN ; i ++ ) s[i] = 1ll * i * ( i + 1 ) / 2;
	for( int i = 0 ; i < MAXN ; i ++ ) S[i] = 1ll * i * ( i + 1 ) * ( i * 2 + 1 ) / 6;
	n = read(),m = read(),q = read();
	for( int i = 1 ; i <= n ; i ++ ) a[i] = read(),add( tra , i , a[i] - a[i - 1] );
	for( int i = 1 ; i <= m ; i ++ ) b[i] = read(),add( trb , i , b[i] - b[i - 1] );
	As.insert( make_pair( n + 2 , n + 2 ) );
	for( int l = 2 , r = 0 ; l <= n ; l = r + 1 ){
		r = l - 1; while( r < n && a[r + 1] != a[r] ) c[r + 1] = 1,r ++;
		if( l > r ){ r = l; continue; }
		int len = r - l + 1;
		As.insert( make_pair( l , r ) );
		modify( 1 , 1 , Lim , 2 , len + 1 , tag{ -1 , len + 2 , 0 , 0 } );
	}
	Bs.insert( make_pair( m + 2 , m + 2 ) );
	for( int l = 2 , r = 0 ; l <= m ; l = r + 1 ){
		r = l - 1; while( r < m && b[r + 1] != b[r] ) d[r + 1] = 1,r ++;
		if( l > r ){ r = l; continue; }
		int len = r - l + 1;
		Bs.insert( make_pair( l , r ) );
		modify( 1 , 1 , Lim , 2 , len + 1 , tag{ 0 , 0 , -1 , len + 2 } );
	}
	write( M[1].sab + 1ll * n * m ),puts("");
	for( int i = 1 ; i <= q ; i ++ ){
		int opt = read();
		if( opt == 1 ){
			int l = read(),r = read(),k = read(); if( !k ) continue;
			add( tra , l , k ),add( tra , r + 1 , -k );
			if( l != 1 ){
				if( !c[l] ) applyA( l , 1 );
				else if( sum( tra , l ) == sum( tra , l - 1 ) ) applyA( l , 0 );
			}
			if( r != n ){
				if( !c[r + 1] ) applyA( r + 1 , 1 );
				else if( sum( tra , r + 1 ) == sum( tra , r ) ) applyA( r + 1 , 0 );
			}
		}
		else if( opt == 2 ){
			int l = read(),r = read(),k = read(); if( !k ) continue;
			add( trb , l , k ),add( trb , r + 1 , -k );
			if( l != 1 ){
				if( !d[l] ) applyB( l , 1 );
				else if( sum( trb , l ) == sum( trb , l - 1 ) ) applyB( l , 0 );
			}
			if( r != m ){
				if( !d[r + 1] ) applyB( r + 1 , 1 );
				else if( sum( trb , r + 1 ) == sum( trb , r ) ) applyB( r + 1 , 0 );
			}
		}
		write( M[1].sab + 1ll * n * m ),puts("");
	}
	return 0;
}
```

---

## 作者：zhuzhu2891 (赞：0)

显然对于一个 $x$ 坐标范围 $[x_0,x_0+d)$，$y$ 坐标范围 $[y_0,y_0+d)$ 的正方形，合法当且仅当 $a_x,a_{x+1},\cdots,a_{x+d-1}$ 两两不同以及 $b_x,b_{x+1},\cdots,b_{x+d-1}$ 两两不同。所以对于 $a$ 我们只需要考虑每个极长连续段 $[l,r)$ 使 $a_l,a_{l+1},\cdots,a_{r-1}$ 两两不同，对于 $b$ 同理。

于是序列 $a$ 就被分成了许多段，对于每段，只有它的长度有意义。

对于 $a$ 中长度为 $x$，$b$ 中长度为 $y$ 的连续段（假设 $x\le y$），对答案的贡献为 $\frac{(x+1)xy}2-\frac{(x+1)x(x-1)}6$（请自行理解）。答案就是所有这种连续段对的贡献的和。

考虑每次加入或删除一个长度为 $x$ 的连续段的影响是什么。显然对于 $y\le x$ 与 $y>x$（$y$ 为 $b$ 中连续段的长度）分类讨论，只需要对于所有 $y$ 在其值域上用树状数组维护 $1,y,\frac{(y+1)y}2,\frac{(y+1)y(y-1)}6$ 这四个函数前缀和即可，对于 $a$ 亦然。加入或删除时只需要修改维护信息和计算贡献改变即可

然后考虑一次题目中的修改，只会带来常数个连续段的改变，可以使用 `set` 维护，于是这题就做完了。

代码，仅供参考
```
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#define pr pair
#define f first
#define s second
#define ll long long
#define mp make_pair
#define pll pr<ll,ll>
#define pii pr<int,int>
#define piii pr<int,pii>
using namespace std;
ll q[300005];
ll w[300005];
ll e[300005];
ll r[300005];
ll a[300005];
ll s[300005];
ll d[300005];
ll f[300005];
ll ans;
void add(ll z[],int x,ll d)
{
	while(x<=300002)
	{
		z[x]+=d;
		x+=x&-x;
	}
}
ll ask(ll z[],int x)
{
	ll rt=0;
	while(x>0)
	{
		rt+=z[x];
		x&=x-1;
	}
	return rt;
}
void da(ll x,int t)
{
	add(q,x,t);
	add(w,x,t*x);
	add(e,x,t*x*(x+1)/2);
	add(r,x,t*x*(x+1)*(x-1)/6);
	ans-=t*x*(x+1)*(x-1)/6*(ask(a,300001)-ask(a,x));
	ans+=t*x*(x+1)/2*(ask(s,300001)-ask(s,x));
	ans+=t*x*ask(d,x);
	ans-=t*ask(f,x);
}
void db(ll x,int t)
{
	add(a,x,t);
	add(s,x,t*x);
	add(d,x,t*x*(x+1)/2);
	add(f,x,t*x*(x+1)*(x-1)/6);
	ans-=t*x*(x+1)*(x-1)/6*(ask(q,300001)-ask(q,x));
	ans+=t*x*(x+1)/2*(ask(w,300001)-ask(w,x));
	ans+=t*x*ask(e,x);
	ans-=t*ask(r,x);
}
set<int> fa,fb;
set<int>::iterator i;
void ina(int x)
{
	i=fa.lower_bound(x);
	int to=*i;
	int fr=*--i;
	da(to-fr,-1);
	da(to-x,1);
	da(x-fr,1);
	fa.insert(x);
}
void inb(int x)
{
	i=fb.lower_bound(x);
	int to=*i;
	int fr=*--i;
	db(to-fr,-1);
	db(to-x,1);
	db(x-fr,1);
	fb.insert(x);
}
void dea(int x)
{
	fa.erase(x);
	i=fa.lower_bound(x);
	int to=*i;
	int fr=*--i;
	da(to-fr,1);
	da(to-x,-1);
	da(x-fr,-1);
}
void deb(int x)
{
	fb.erase(x);
	i=fb.lower_bound(x);
	int to=*i;
	int fr=*--i;
	db(to-fr,1);
	db(to-x,-1);
	db(x-fr,-1);
}
ll ca[300005],cb[300005];
int main()
{
	ios_base::sync_with_stdio(0);
	int n,m,k;
	cin>>n>>m>>k;
	int t,x,y,z;
	for(int i=0;i<n;i++) cin>>ca[i];
	for(int i=n-1;i>0;i--) ca[i]-=ca[i-1];
	for(int i=0;i<m;i++) cin>>cb[i];
	for(int i=m-1;i>0;i--) cb[i]-=cb[i-1];
	fa.insert(0);
	fa.insert(n);
	fb.insert(0);
	fb.insert(m);
	da(n,1);
	db(m,1);
	for(int i=1;i<n;i++) if(ca[i]==0) ina(i);
	for(int i=1;i<m;i++) if(cb[i]==0) inb(i);
	cout<<ans<<endl;
	while(k--)
	{
		cin>>t>>x>>y>>z;
		x--;
		if(t==1)
		{
			if(x>0)
			{
				bool og=ca[x]==0;
				ca[x]+=z;
				bool cr=ca[x]==0;
				if((!og)&&cr) ina(x);
				if((!cr)&&og) dea(x);
			}
			if(y<n)
			{
				bool og=ca[y]==0;
				ca[y]-=z;
				bool cr=ca[y]==0;
				if((!og)&&cr) ina(y);
				if((!cr)&&og) dea(y);
			}
		}
		else
		{
			if(x>0)
			{
				bool og=cb[x]==0;
				cb[x]+=z;
				bool cr=cb[x]==0;
				if((!og)&&cr) inb(x);
				if((!cr)&&og) deb(x);
			}
			if(y<m)
			{
				bool og=cb[y]==0;
				cb[y]-=z;
				bool cr=cb[y]==0;
				if((!og)&&cr) inb(y);
				if((!cr)&&og) deb(y);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

