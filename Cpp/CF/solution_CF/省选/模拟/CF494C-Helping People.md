# Helping People

## 题目描述

有一个长为 $n$ 的数列，初始时为 $a_{1..n}$。

给你 $q$ 个操作，第 $i$ 个操作将 $[l_i,r_i]$ 内的数全部加一，有 $p_i$ 的概率被执行。保证区间不会交错，即：$\forall i,j\in[1,q],l_i\le r_i<l_j\le r_j$ 或 $l_i\le l_j\le r_j\le r_i$ 或 $l_j\le r_j<l_i\le r_i$ 或 $l_j\le l_i\le r_i\le r_j$ 。

求操作完成后数列的最大值的期望。

## 样例 #1

### 输入

```
5 2
1 7 2 4 3
1 3 0.500
2 2 0.500
```

### 输出

```
8.000000000
```

## 样例 #2

### 输入

```
5 2
281 280 279 278 282
1 4 1.000
1 4 0.000
```

### 输出

```
282.000000000
```

## 样例 #3

### 输入

```
3 5
1 2 3
1 3 0.500
2 2 0.250
1 2 0.800
1 1 0.120
2 2 0.900
```

### 输出

```
4.465000000
```

# 题解

## 作者：Azazеl (赞：24)

### CF494C Helping People 题解

[或许好一点的阅读体验](https://www.cnblogs.com/Azazel/p/13490350.html)

----

#### 题意 

>  $\ \ \ \ \ \ $ 给出长为 $n\ (1\le n\le 10^5)$ 的数列 $\{a_i\}\ (1\le a_i\le 10^9)$。共 $m\ (1\le m\le 5\times 10^3)$ 次操作，第 $i$ 次操作有 $p_i$ 的概率将 $[l_i,r_i]$ 内所有数加 $1$ ，求所有操作完成后的数列最大值的期望。保证所有操作区间不相交。（即仅会相离或包含）  

---

#### 题解  

$~~~~$ 很好的题，用学长的话来说可以让人回归期望的本质。

$~~~~$ 要先知道 $\operatorname{E}(\max\{a_i\}) \not = \max\{\operatorname{E}(a_i)\}$ . ~~（不然就是线段树板子了）~~

$~~~~$ 如果我们从期望DP入手，很难找到一个合适的方法去DP。这个时候不妨想想：期望 $=$ 概率 $\times$ 值，而这道题中值是很好求的，因此不妨直接DP概率。  

$~~~~$ 再看操作区间不相交的条件，这个条件使得区间之间构成树形的关系，所有操作就是一个森林了。因此不难想到增加一个操作 $m+1$ ： $l_{m+1}=1,r_{m+1}=n,p_{m+1}=0$ 这样既不会对答案有影响，又让所有区间形成了一棵树。  

$~~~~$ 得到这个性质后不难想到树形 DP ，定义DP状态 $dp_{u,i}$ 表示在 $u$ 节点对应的区间内最大值 $\le i$ 的概率。由于某个区间的最大值 $maxn$ 在任何操作后一定在 $[maxn,maxn+m]$ 之间，因此仅在 $i \in [maxn,maxn+m]$ 时我们才需要这个值。因此更改定义： $dp_{u,i}$ 表示在 $u$ 节点对应的区间内最大值 $\le i+maxn_u$ 的概率。此时 $i$ 一定满足 $0 \le i \le m$ ，时空都得到了优化。  

$~~~~$ 由此可以得到一个转移：  
$$
\large dp_{u,i}=p_u\times \prod _{v\in \operatorname{son(u)}} dp_{v,i-maxn_v+maxn_u-1}\ +\ (1-p_u) \times \prod_{v\in \operatorname{son(x)}} dp_{v,i-maxn_v+maxn_u}
$$
$~~~~$ 而当 $i=0$ 时仅取上式加号的后面部分即可。

$~~~~$ 若令我们新增的区间为 $1$ ，则最后答案即为：
$$
\large \sum_{i=0}^m (dp_{1,i}-dp_{1,i-1})\times (i+maxn_1)
$$


$~~~~$ 求取最大值时可以用 ST 表。  

$~~~~$ 总的时间复杂度为 $\mathcal{O(n\ \log\ n+m^2)}$ .  

$~~~~$ 另外注意千万不能在CF将 C++11 和 long double 并用。  

### 代码 

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector <int> G[5005];
struct node{
	int l,r,maxn;
	double p;
	node(){}
	node(int L,int R,double P,int Maxn){l=L,r=R,p=P,maxn=Maxn;}
}op[5005];
double dp[5005][5005];
int n,m,lg[100005],arr[100005],f[100005][105];
void inti()
{
	for(int i=1;i<=n;i++) f[i][0]=arr[i];
	int t=lg[n]+1;
	for(int j=1;j<t;j++)
	{
		for(int i=1;i<=n-(1<<j)+1;i++)
		{
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r)
{
	int k=lg[r-l+1];
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
void read(int &x)
{
	int f=1;x=0;char c=getchar();
	while(!('0'<=c&&c<='9')){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+(c-'0');c=getchar();}
	x*=f;
}
inline bool cmp(node x,node y)
{
	return x.l^y.l?x.l<y.l:x.r>y.r;
}
void DP(int u)
{
	int v;
	for(int i=0;i<(int)G[u].size();i++) DP(G[u][i]);
	dp[u][0]=1-op[u].p;
	for(int i=0;i<(int)G[u].size();i++) v=G[u][i],dp[u][0]*=dp[v][op[u].maxn-op[v].maxn];
	for(int i=1;i<=m;i++)
	{
		double p1=1,p2=1;
		for(int j=0;j<(int)G[u].size();j++)
		{
			v=G[u][j];
			p1*=dp[v][min(i-op[v].maxn+op[u].maxn-1,m)];
			p2*=dp[v][min(i-op[v].maxn+op[u].maxn,m)];
		}
		dp[u][i]=op[u].p*p1+(1-op[u].p)*p2;
	}	
	
}
int main() {
	int maxn=-1;
	read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(arr[i]);
		maxn=max(maxn,arr[i]);
		if(i!=1) lg[i]=lg[i>>1]+1;	
	}
	inti();
	for(int i=1;i<=m;i++)
	{
		read(op[i].l);read(op[i].r);
		scanf("%lf",&op[i].p);
		op[i].maxn=query(op[i].l,op[i].r);
	}
	op[++m]=node(1,n,0.0,query(1,n));
	sort(op+1,op+1+m,cmp);
	for(int i=2;i<=m;i++)
	{
		for(int j=i-1;j>=1;j--)
		{
			if(op[j].l<=op[i].l&&op[i].r<=op[j].r)
			{
				G[j].push_back(i);
				break;
			}
		}
	}
	DP(1);
	long double ans=0;
	for(int i=0;i<=m;i++) ans+=((dp[1][i]-(!i?0:dp[1][i-1]))*(i+maxn));
	printf("%.9Lf",ans);
	return 0;
}
```





---

## 作者：ButterflyDew (赞：10)

考虑区间不交错的用处，一个区间向ta完全包含的区间连边，可以构成一棵树。

然后区间又只有5000个，搞一个$n^2$的树形dp多好

考虑求出每个最大值的概率。

令$dp_{i,j}$代表区间$i$最大值不大于$j+\max_{l\le i\le r}a_i$的概率，这样等于的概率只需要$dp_{i,j}-dp_{i,j-1}$就可以得到了

转移
$$dp_{i,j}=p_i\prod_sdp_{s,j+\max_i-\max_v-1}+(1-p_i)\prod_sdp_{s,j+\max_i-\max_v}$$
注意上下边界。

---

## 作者：Vsinger_洛天依 (赞：6)

#  [Helping People](https://www.luogu.com.cn/problem/CF494C)


逆天[冲刺 NOIP 题单](https://www.luogu.com.cn/training/484173)可做题之三。

**因为我脑瘫记错题面里的变量名了，下面的 $m$ 其实是 $q$，但是应该不影响阅读。**

首先我们要知道 $\text{E}(\max\{\})\ne \max\{\text{E()}\}$，不然就会理解错题意，然后错误的像我一样感觉是数据结构题。

观察题面可以发现本题保证区间不会交错，要么包含要么不交，所以根据以往的经验我们选择直接树形 $\text{dp}$。

这是因为区间不交我们就可以把其建成一个树形的结构，然后来大力 $\text{dp}$。

首先每个区间可以建立一个树，然后如果包含起来就可以直接去合成一颗比起原来更大的树，把包含的区间变成这个区间的子树，最后我们会形成一棵森林。

对于森林我们可以建立一个$\{1\sim n\}$的区间，这样整个森林就可以形成单独的一颗树，从而维护，这个区间我们对其编号为 $1$。

然后可以比较暴力的去想，$f_{i,j}$ 表示节点 $i$ 的子树(点 $i$ 所对应的区间)在经过操作后的最大值小于等于 $j$ 的概率。

但是我们能够发现一个性质，对于某个区间，定义 $mx$ 为其 $\max$，那么 $j\in\{mx,mx+m\}$(这里很明显是因为每次 $mx$ 至多都只会 $+1$ 且有且只有 $m$ 次操作，所以 $mx$ 的最大值就是 $mx+m$)。

那么我们就可以改变 $f$ 数组的定义，定义 $f_{i,j}$ 为节点 $i$ 的子树（点 $i$ 所对应的区间）在经过操作后最大值小于等于 $j+maxn_i$ 的概率（$0\le j\le m$），时空都优化了。

$$f_{i,j}=p_i\times \prod _{k\in \text{son(i)}} f_{k,j-mx_k+mx_i-1}\ +\ (1-p_i) \times \prod_{k\in \text{son(i)}} f_{k,j-mx_k+mx_i}$$

然后这很明显是非常对的，因为 $\text P(A+B)=\text P(A)+\text P(B)$。

再用ST表去求出最开始每个区间的 $mx$ 就可以做出来这道题了。

最后的答案很明显是 $\text E(1)=\text P(1)\times \text{val}(1)=\sum\limits_{i=0}^{m}((f_{m+1,i}-f_{m+1,i-1})(i+mx_{1}))$。

---

## 作者：i207M (赞：4)

~~cool，最优解，比第二名快一倍~~

~~左闭右开区间害死人...~~

这道题的套路前几天做网络流的题时见过。**见到区间两两要么不交要么包含，这样的关系形成了一棵树！** 树的性质往往可以解题。

我们可以设$dp[x][i]$表示点x代表的区间中，最小值$\le i$的概率，转移的话比较显然。

```cpp
#define pid pair<int,double>
int n,cq;
double f[5005][5005];
vector< pid > qz[10005];
int val[10005];
int mnv[5005],mxv[5005];
int tot;
void work(int l,int r,int x,const double p)
{
	for(ri i=l; i<r; ++i) ckmax(mnv[x],val[i]);
	mxv[x]=mnv[x];
	f[x][0]=1;
	for(ri tl=l; tl<r; ++tl)
	{
		if(qz[tl].empty()) continue;
		int id=0;
		for(ri i=1; i<Size(qz[tl]); ++i)
			if(qz[tl][i].fi>qz[tl][id].fi) id=i;
		if(qz[tl][id].fi==0) continue;
		pid t=qz[tl][id]; qz[tl][id].fi=0;
		int v=++tot; work(tl,t.fi,v,t.se);
		if(mnv[x]>=mxv[v]) continue;
		if(mxv[x]<mxv[v])
		{
			while(mxv[x]+1<=mxv[v]) f[x][++mxv[x]-mnv[x]]=1;
		}
		int z=mnv[x]-mnv[v];
		for(ri i=z; i<=mxv[v]-mnv[v]; ++i)
			f[x][mnv[v]+i-mnv[x]]*=f[v][i];
		tl=t.fi-1;
	}
	for(ri i=mxv[x]-mnv[x]; i>=1; --i) f[x][i]-=f[x][i-1];
	f[x][mxv[x]-mnv[x]+1]=f[x][mxv[x]-mnv[x]]*p;
	for(ri i=mxv[x]-mnv[x]; i>=1; --i)
		f[x][i]=f[x][i-1]*p+f[x][i]*(1-p);
	f[x][0]*=1-p;
	++mxv[x];
	for(ri i=1; i<=mxv[x]-mnv[x]; ++i) f[x][i]+=f[x][i-1];
}
int ql[5005],qr[5005];
double qk[5005];
int ct[10005],cntc;
int a[100005];
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n,cq); int mx=0;
	for(ri i=1; i<=n; ++i) in(a[i]),ckmax(mx,a[i]);
	for(ri i=1; i<=cq; ++i)
	{
		in(ql[i],qr[i]);
		scanf("%lf",&qk[i]);
		ct[++cntc]=ql[i],ct[++cntc]=qr[i]+1;
	}
	ct[++cntc]=1,ct[++cntc]=n+1;
	sort(ct+1,ct+1+cntc); cntc=unique(ct+1,ct+1+cntc)-ct-1;
	for(ri i=1; i<=cq; ++i)
	{
		ql[i]=lower_bound(ct+1,ct+1+cntc,ql[i])-ct;
		qr[i]=lower_bound(ct+1,ct+1+cntc,qr[i]+1)-ct;
		qz[ql[i]].pb(mp(qr[i],qk[i]));
	}
	for(ri i=1; i<cntc; ++i)
		for(ri j=ct[i]; j<ct[i+1]; ++j) ckmax(val[i],a[j]);
	work(1,cntc,++tot,0);
	double ans=mnv[1];
	for(ri i=1; i<=mxv[1]-mnv[1]; ++i)
		ans+=i*(f[1][i]-f[1][i-1]);
	printf("%.10f\n",ans);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：2)

首先区间没有相交，要么包含要么不交。因此可以用包含关系建出一棵真正意义上的“线段森林”。由于题目的优美性质，我们可以通过添加 $l_i=1,r_i=n,p_i=0$ 的一个区间，来把这个森林变成一颗树。

然后考虑树形 DP。由于这个期望不好算，而期望等于概率乘上值。求值我们可以枚举，因此只需要求出概率就好了。

最朴素的做法就是令 $f_{i,j}$ 表示以 $i$ 为根的子树内，最大值为 $j$ 的概率。为方便表示，后文令 $T_i$ 表示 $i$ 子树内的点集。

但是以 $i$ 为根的子树内最大值至少也是 $\max\limits_{u \in T_i} a_u$，最多也只有 $\max\limits_{u \in T_i}+|T_i|$，所以 $j$ 这一维太浪费了。

因此考虑 $f_{i,j}$ 表示以 $i$ 为根的子树内，最大值比 $\max\limits_{u \in T_i} a_u$ 大 $j$ 的概率。令 $mx_i=\max\limits_{u \in T_i}a_u$，则明显有转移：

$$f_{i,j}=p_i \times \prod_{v \in E_i}f_{v,j-mx_v+mx_i-1}+(1-p_i) \times \prod_{v \in E_i}f_{v,j-mx_v+mx_i}$$

注意到当 $j=0$ 的时候第一种转移不合法，特判即可。最后的答案就是每种可能的值乘上其概率。假设我们人工添加的 $l_i=1,r_i=n,p_i=0$ 的编号为 $x$，则答案为：

$$M \cdot f_{x,0}+\sum_{i=1}^{q}(f_{x,i}-f_{x,i-1})(M+i)$$

复杂度 $O(n \log n+q^2)$，可以通过。

[Code & Submission](https://codeforces.com/contest/494/submission/224870370)

---

## 作者：duyi (赞：2)

# CF494C Helping People

## 本题题解

在“要么并列、要么包含”的条件下，发现区间之间构成了**树形结构**。准确地说是一个森林，但我们可以通过补一个 $l = 1, r = n, p = 0$ 的区间，然后森林里所有树根会向这个点连边，于是就变成了一棵树，这使得后续的实现方便地多。

建这棵树，可以先把区间按左端点**从小到大**排序（左端点相同时按右端点**从大到小**排，总之保证被包含的区间出现在包含它的区间后面）。然后扫描一遍，维护一个栈。具体见代码。

建出树后，考虑树形 DP。设 $\text{dp}(u,j)$ 表示考虑了节点 $u$ 的子树，点 $u$ 所对应的区间在经过操作后的最大值**小于等于** $j$ 的概率。朴素想法是 $0\leq j\leq 10^9 + q$。转移式就是：
$$
\text{dp}(u,j) = p_u\prod_{v \in\text{son}(u)}\text{dp}(v, j - 1) + (1 - p_u)\prod_{v \in\text{son}(u)}\text{dp}(v, j)
$$
两种转移分别对应 $u$ 这个节点代表的区间，是否被选中。

但是 $j$ 这么大显然是无法用代码实现的。需要进一步优化。

发掘性质。对于任意区间 $l,r$，设 $\text{mx}(l,r) = \max_{i = l}^{r}a_i$，设 $\text{mx}_u = \text{mx}(l_u,r_u)$。发现，区间 $l,r$ 在经过操作后的最大值，一定在 $[\text{mx}(l,r), \text{mx}(l,r) + q]$ 之间，也就是至多只有 $q + 1$ 种取值。所以可以改变一下 DP 状态，我们设 $\text{dp}_2(u, j)$ 表示考虑了节点 $u$ 的子树，点 $u$ 所对应的区间在经过操作后的最大值小于等于 $j + \text{mx}_u$ 的概率，即 $\text{dp}_2(u,j) = \text{dp}(u, j + \text{mx}_u)$。这样状态数就被精简到了 $\mathcal{O}(q^2)$ 级别。

转移还是类似的：
$$
\text{dp}_2(u,j) = p_u \prod_{v \in\text{son}(u)}\text{dp}_2(v, j + \text{mx}_u - \text{mx}_v - 1) + (1 - p_u)\prod_{v \in\text{son}(u)}\text{dp}_2(v, j + \text{mx}_u - \text{mx}_v)
$$
特别地，在 $j = 0$ 时不发生第一种转移。当 $j + \text{mx}_u - \text{mx}_v > q$ 时，$\text{dp}_2(v, j + \text{mx}_u - \text{mx}_v)$ 直接取 $\text{dp}_2(v, q)$ 即可。

时间复杂度 $\mathcal{O}(n + q^2)$。

## 参考代码

```cpp
// problem: CF494C
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5, MAXQ = 5001;
const int LOG = 16;

int n, q, a[MAXN + 5];

struct RangeMaxQuery {
	int _log2[MAXN + 5];
	pii st[MAXN + 5][LOG + 1];
	void build(int* a, int n) {
		_log2[0] = -1;
		for (int i = 1; i <= n; ++i) {
			_log2[i] = _log2[i >> 1] + 1;
			st[i][0] = mk(a[i], i);
		}
		for (int j = 1; j <= LOG; ++j) {
			for (int i = 1; i + (1 << (j - 1)) <= n; ++i) {
				st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); // *****
			}
		}
	}
	pii rmq(int l, int r) {
		int k = _log2[r - l + 1];
		return max(st[l][k], st[r - (1 << k) + 1][k]); // *****
	}
	int rmq_val(int l, int r) { return rmq(l, r).fi; }
	int rmq_pos(int l, int r) { return rmq(l, r).se; }
	RangeMaxQuery() {}
} RMQ;

struct Seg {
	int l, r, mx;
	double p;
} s[MAXQ + 5];

bool cmp(Seg x, Seg y) {
	if (x.l == y.l)
		return x.r > y.r;
	return x.l < y.l;
}

int sta[MAXQ + 5], top;

struct EDGE { int nxt, to; } edge[MAXQ * 2 + 5];
int head[MAXQ + 5], tot;
inline void add_edge(int u, int v) { edge[++tot].nxt = head[u]; edge[tot].to = v; head[u] = tot; }

double dp[MAXQ + 5][MAXQ + 5];
void dfs(int u) {
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		dfs(v);
	}
	
	for (int j = 0; j <= q; ++j) {
		double p = 1.0 - s[u].p;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			p *= dp[v][min(q, j + s[u].mx - s[v].mx)];
		}
		dp[u][j] += p;
	}
	for (int j = 1; j <= q; ++j) {
		double p = s[u].p;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			p *= dp[v][min(q, j + s[u].mx - s[v].mx - 1)];
		}
		dp[u][j] += p;
	}
}

int main() {
	ios :: sync_with_stdio(false);
	
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	RMQ.build(a, n);
	
	for (int i = 1; i <= q; ++i) {
		cin >> s[i].l >> s[i].r >> s[i].p;
		s[i].mx = RMQ.rmq_val(s[i].l, s[i].r);
	}
	++q;
	s[q].l = 1;
	s[q].r = n;
	s[q].p = 0;
	s[q].mx = RMQ.rmq_val(1, n);
	
	sort(s + 1, s + q + 1, cmp);
	sta[++top] = 1;
	for (int i = 2; i <= q; ++i) {
		while (s[sta[top]].r < s[i].l)
			--top;
		assert(top >= 1);
		assert(s[sta[top]].r >= s[i].r);
		
		add_edge(sta[top], i);
		sta[++top] = i;
	}
	
	dfs(1);
	double ans = 0;
	for (int i = 0; i <= q; ++i) {
		double v = s[1].mx + i;
		double p = dp[1][i];
		if (i) p -= dp[1][i - 1];
		ans += v * p;
	}
	cout << setiosflags(ios :: fixed) << setprecision(8) << ans << endl;
	return 0;
}
```



---

## 作者：Demeanor_Roy (赞：1)

- 《关于我误以为 $m$ 和 $n$ 同阶傻傻写不出来这件事》。

------------

- 性质一：区间不交 $\rightarrow$ 区间之间满足树形结构。

常见套路。加上操作 $(1,n,0)$，就可以根据区间包含关系建树。问题转化为树形 dp。

建树代码：

```cpp
	sort(q+1,q+m+1,[](node a,node b){return a.l==b.l?a.r>b.r:a.l<b.l;});
	int top=0;
	for(int i=1;i<=m;i++)
	{
		while(top&&q[i].r>q[stk[top]].r) top--;
		if(top) add(stk[top],i);stk[++top]=i;
	}
```

- 性质二：$\max$ 的期望不等于期望的 $\max$。

这里建议推推式子或手模样例深刻理解这句话，否则期望的路上会很难走。

根据前两个性质，我们考虑 $dp(u,x)$ 表示在以 $u$ 为根的子树内，最大值不超过 $x$ 的概率是多少。之所以状态定义为不超过是为了方便转移，不信你可以试试定义为恰好。此状态下转移显然是：

$$dp(u,x)= p_u \times \prod\limits_{v \in son_u}dp(v,x-1) \ + \ (1-p_u) \times \prod\limits_{v \in son_u}dp(v,x)$$

显然这个 dp 时间复杂度 $O(n + mv)$，无法接受。

那么考虑优化，发现第二维实际上有用的状态只有 $m$ 个，即 $x \in [max_{k=l_u}^{r_u}v_k,max_{k=l_u}^{r_u}v_k + m]$ 这 $m$ 个。于是考虑将第二维改成最大不超过区间最大值 $x$，同理转移即可。st 表维护区间最大值可以做到 $O(n \log n + m^2)$。

注意边界条件。下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10,M=5010;
int n,m,sz[N],stk[N],st[N][18];
int h[M],e[M],ne[M],idx;
double f[M][M];
struct node{int l,r;double p;}q[M];
inline void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
inline int query(int l,int r)
{
	int T=log2(r-l+1);
	return max(st[l][T],st[r-(1<<T)+1][T]);
}
inline void dp(int u)
{	
	sz[u]=1;
	for(int i=h[u];~i;i=ne[i]) dp(e[i]),sz[u]+=sz[e[i]];
	if(~h[u])
	for(int j=0;j<=sz[u];j++)
	{
		double pL=1,pR=1;
		for(int i=h[u];~i;i=ne[i]) 
		{
			int lim=j+query(q[u].l,q[u].r)-query(q[e[i]].l,q[e[i]].r);
			if(lim<=sz[e[i]]) pR*=f[e[i]][lim];		
			if(lim<=sz[e[i]]+1) pL*=f[e[i]][lim-1];			
		}
		f[u][j]=pL*q[u].p*(!!j)+pR*(1-q[u].p);
	}
	else 
	{
		f[u][0]=1-q[u].p;
		for(int j=1;j<=sz[u];j++) f[u][j]=1;
	}
}
int main()
{
	memset(h,-1,sizeof h);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&st[i][0]);
	for(int j=1;j<18;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=m;i++) scanf("%d%d%lf",&q[i].l,&q[i].r,&q[i].p);
	q[++m]={1,n,0};
	sort(q+1,q+m+1,[](node a,node b){return a.l==b.l?a.r>b.r:a.l<b.l;});
	int top=0;
	for(int i=1;i<=m;i++)
	{
		while(top&&q[i].r>q[stk[top]].r) top--;
		if(top) add(stk[top],i);stk[++top]=i;
	}
	dp(1);
	int maxn=query(1,n);double ans=f[1][0]*maxn;
	for(int i=1;i<=m;i++) ans+=(f[1][i]-f[1][i-1])*(maxn+i);
	printf("%.8lf",ans);
	return 0;
}
```




---

## 作者：Purslane (赞：0)

# Solution

挺简单的题目啊。

令 $a= \max_{1 \le i \le n} a_i$，显然可以 $a_i \leftarrow \max\{a_i,a-q\}$，答案不变。

将线段的包含关系看成树，可以设 $dp_{i,j}$ 表示考虑了第 $i$ 条线段包含的所有线段，操作完成之后区间最大值为 $j$ 的概率（$j$ 显然只有 $O(q)$ 种情况）。

发现转移有：

- 如果线段之间没有包含关系，那么做了一个 $c_i = \sum_{\max\{j,k\}=i} a_jb_k$ 的卷积，显然可以前缀和优化。
- 如果有包含关系，要做一遍 01 背包。

这样复杂度 $O(q^2)$。

如何找树的关系？考虑按照 $l$ 为第一关键字，$-r$ 为第二关键字排序，得到的就是树的一个 DFS 序。

可以插入一个 $(1,n,0)$ 的线段作为边界。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=5000+10;
int n,q,a[MAXN],mx,st[MAXN][20];
struct SEG {int l,r;double p;}t[MAXM];
int query(int l,int r) {
	int k=log2(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);	
}
vector<double> solve(int lid,int rid) {
	vector<double> ans; ans.resize(2*q-1);
	ans[query(t[lid].l,t[lid].r)]=1;
	ffor(i,0,q+q-2) ans[i]+=ans[i-1];
	int pos=lid;
	ffor(i,lid+1,rid) if(t[i].l==t[lid].l&&t[i].r==t[lid].r) pos=i;
	int nxt=pos+1;
	while(nxt<=rid) {
		int fyz=nxt;
		ffor(i,nxt+1,rid) if(t[i].l<=t[nxt].r) fyz=i; else break ;
		auto vc=solve(nxt,fyz);
		ffor(i,1,q+q-2) vc[i]+=vc[i-1];
		ffor(i,0,q+q-2) ans[i]=ans[i]*vc[i];
		nxt=fyz+1;
	}
	roff(i,q+q-2,1) ans[i]-=ans[i-1];
	ffor(i,lid,pos) {
		roff(j,q+q-2,1) ans[j]=ans[j]*(1-t[i].p)+ans[j-1]*t[i].p;
		ans[0]=ans[0]*(1-t[i].p);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	mx=*max_element(a+1,a+n+1);
	ffor(i,1,n) a[i]=max(a[i]-mx+q,0),st[i][0]=a[i];
	ffor(j,1,20) for(int l=1,r=(1<<j);r<=n;l++,r++) st[l][j]=max(st[l][j-1],st[l+(1<<j-1)][j-1]);
	ffor(i,1,q) cin>>t[i].l>>t[i].r>>t[i].p;
	++q,t[q].l=1,t[q].r=n,t[q].p=0;
	sort(t+1,t+q+1,[](SEG A,SEG B) {
		if(A.l!=B.l) return A.l<B.l;
		return A.r>B.r;	
	});
	auto vc=solve(1,q);
	double ans=0;
	ffor(i,0,q+q-2) ans+=i*vc[i];
	ans+=mx-(q-1);
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF494C)

# 前置知识

[概率 DP](https://oi-wiki.org/dp/probability/) | [树形 DP](https://oi-wiki.org/dp/tree/) |[RMQ](https://oi-wiki.org/topic/rmq/)

# 解法

观察到区间只有相离或包含关系，类似线段树的管辖区间，考虑将其构成树形关系。为方便代码书写，将原来的森林构成一棵树，即增加一个区间 $l_{q+1}=1,r_{q+1}=n,p_{q+1}=0$。

由于对于一个区间 $[l,r]$ 的最大值在经历任意次操作后，一定有 $\max\limits_{k=l}^{r} \{ a_{k} \} \le \max\limits_{k=l}^{r} \{ a_{k}' \} \le \max\limits_{k=l}^{r} \{ a_{k} \}+q$，故可以据此优化空间。设 $f_{x,i}$ 表示第 $x$ 个节点对应的区间的最大值 $\le \max\limits_{k=x_{l}}^{x_{r}} \{ a_{k} \}+i$ 的概率，状态转移方程为 $\begin{cases} f_{x,i}=(1-p_{x}) \times \prod\limits_{y \in Son(x)}f_{y,\min(q+1,\max\limits_{k=x_{l}}^{x_{r}} \{ a_{k} \}+i-\max\limits_{k=y_{l}}^{y_{r}} \{ a_{k} \})} & i=0 \\ f_{x,i}=p_{x} \times \prod\limits_{y \in Son(x)}f_{y,\min(q+1,\max\limits_{k=x_{l}}^{x_{r}} \{ a_{k} \}+i-\max\limits_{k=y_{l}}^{y_{r}} \{ a_{k} \}-1)}+(1-p_{x}) \times \prod\limits_{y \in Son(x)}f_{y,\min(q+1,\max\limits_{k=x_{l}}^{x_{r}} \{ a_{k} \}+i-\max\limits_{k=y_{l}}^{y_{r}} \{ a_{k} \})} & i \ne 0 \end{cases}$。

假设区间按照左端点升序，右端点降序的方式排序。最终，有 $f_{1,0} \times \max\limits_{k=1}^{n} \{ a_{k} \}+\sum\limits_{i=1}^{q+1}(f_{1,i}-f_{1,i-1}) \times (i+ \max\limits_{k=1}^{n} \{ a_{k} \})$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct edge
{
    int nxt,to;
}e[5010];
struct node
{
    int l,r,maxx;
    double p;
}b[5010];
int head[5010],a[100010],fmaxx[100010][20],cnt=0;
double f[5010][5010];
bool cmp(node a,node b)
{
    return (a.l==b.l)?(a.r>b.r):(a.l<b.l);
}
void init(int n)
{
    for(int j=1;j<=log2(n);j++)
    {
        for(int i=1;i<=n-(1<<j)+1;i++)
        {
            fmaxx[i][j]=max(fmaxx[i][j-1],fmaxx[i+(1<<(j-1))][j-1]);
        }
    }
}
int query(int l,int r)
{
    int t=log2(r-l+1);
    return max(fmaxx[l][t],fmaxx[r-(1<<t)+1][t]);
}
void add(int u,int v)
{
    cnt++;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
void dfs(int x,int q)
{
    double sum1,sum2=1;
    for(int i=head[x];i!=0;i=e[i].nxt)
    {
        dfs(e[i].to,q);
        sum2*=f[e[i].to][min(q,b[x].maxx+0-b[e[i].to].maxx)];
    }
    f[x][0]=(1-b[x].p)*sum2;
    for(int i=1;i<=q;i++)
    {
        sum1=sum2=1;
        for(int j=head[x];j!=0;j=e[j].nxt)
        {
            sum1*=f[e[j].to][min(q,b[x].maxx+i-b[e[j].to].maxx-1)];
            sum2*=f[e[j].to][min(q,b[x].maxx+i-b[e[j].to].maxx)];
        }
        f[x][i]=b[x].p*sum1+(1-b[x].p)*sum2;
    }
}
int main()
{
    int n,q,i,j;
    double ans=0;
    cin>>n>>q;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        fmaxx[i][0]=a[i];
    }
    init(n);
    for(i=1;i<=q;i++)
    {
        cin>>b[i].l>>b[i].r>>b[i].p;
        b[i].maxx=query(b[i].l,b[i].r);
    }
    q++;
    b[q].l=1;
    b[q].r=n;
    b[q].p=0;
    b[q].maxx=query(1,n);
    sort(b+1,b+1+q,cmp);
    for(i=1;i<=q;i++)
    {   
        for(j=i-1;j>=1;j--)
        {
            if(b[j].l<=b[i].l&&b[i].r<=b[j].r)
            {
                add(j,i);
                break;
            }
        }
    }
    dfs(1,q);
    for(i=0;i<=q;i++)
    {
        ans+=(f[1][i]-(i==0?0:f[1][i-1]))*(i+b[1].maxx);
    }
    printf("%.9lf\n",ans);
    return 0;
}  	
```

---

## 作者：shao0320 (赞：0)

#### CF494C Helping People

首先要明白不能直接算每个点的期望然后取最大值。

考虑下边这组样例：

```
2 2
7 8
1 1 0.100
1 1 0.100
```

如果直接算那么第一个点的期望是$7.2$，第二个点是$8$，然而第一个点有概率变成$9$，因而最终的最大值的期望一定大于$8$，也就是最大值的期望不等于期望的最大值。

考虑题目给的限制条件，可以发现其询问呈森林状结构，这提醒我们在树上解决这个问题。

考虑每个点加的钱数，因为每次操作只会加$1\space dollar$，因此我们考虑记录每个询问加的钱数，由于期望是总价值和概率的乘积，因此​实际上我们只需要概率即可。

考虑一个区间内，要加一起加，要不加一起不加，那么也就是说我们可以让初始值最大的点来做"代表"，这样就可以进行$dp$了。

设$dp[i][j]$表示第$i$个操作的范围内，最大值是$maxn_i+j$块钱的概率，枚举子区间转移即可。

还有一个地方就是要处理出每个区间内初始的最大值，这个用$ST$表$O(N\log N)$预处理即可。

时间复杂度$O(N\log N+q^2)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#define N 5005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,q,a[100005],st[100005][25];
struct node
{
	int l,r,maxn;
	double p;
}b[N];
vector<int>G[N];
double f[N][N];
int cmp(node a,node b)
{
	if(a.l==b.l)return a.r>b.r;
	return a.l<b.l;
}
int query(int l,int r)
{
	int k=log(r-l+1)/log(2);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
void dfs(int x)
{
	//cout<<"********"<<G[1][0]<<endl;
	//cout<<x<<endl;
	int siz=G[x].size();
	for(int i=0;i<siz;i++)dfs(G[x][i]);
	f[x][0]=1-b[x].p;
	for(int i=0;i<siz;i++)f[x][0]*=f[G[x][i]][b[x].maxn-b[G[x][i]].maxn];
	for(int i=1;i<=q;i++)
	{
		double p1=1,p2=1;
		for(int j=0;j<siz;j++)
		{
			int v=G[x][j];
			p1*=f[v][min(i-b[v].maxn-1+b[x].maxn,q)];
			p2*=f[v][min(i-b[v].maxn+b[x].maxn,q)];
		}
		//cout<<"!!!"<<endl;
		f[x][i]=b[x].p*p1+(1-b[x].p)*p2;
	}
	//cout<<x<<endl;
}
int main()
{
	n=read();q=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		st[i][0]=a[i];
	}
	for(int j=1;j<=20;j++)
	{
		for(int i=1;i+(1<<(j-1))<=n;i++)
		{
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=q;i++)
	{
		b[i].l=read();
		b[i].r=read();
		scanf("%lf",&b[i].p);
		b[i].maxn=query(b[i].l,b[i].r);
	}
	b[++q]=(node){1,n,query(1,n),0.0};
	sort(b+1,b+1+q,cmp);
	for(int i=1;i<=q;i++)
	{
		for(int j=i-1;j>=1;j--)
		{
			if(b[j].l<=b[i].l&&b[j].r>=b[i].r)
			{
				G[j].push_back(i);
				break;
			}
		}
	}
	//for(int i=1;i<=q;i++)
	//{
	//	cout<<i<<" "<<b[i].l<<" "<<b[i].r<<" "<<b[i].p<<" "<<b[i].maxn<<endl;;
	//}
	//for(int i=1;i<=q;i++)
	//{
	//	int siz=G[i].size();
		//cout<<"---"<<i<<" "<<siz<<endl;
	///	for(int j=0;j<siz;j++)
	//	{
	///		cout<<G[i][j]<<" ";
	///	}
	//	puts("");
	//}
	//return 0;
	dfs(1);
	double ans=f[1][0]*b[1].maxn;
	//for(int i=1;i<=q;i++)
	//{
	//	for(int j=0;j<=q;j++)
	//	{
	//		cout<<f[i][j]<<" ";
	//	}
	//	puts("");
	//}
	for(int i=1;i<=q;i++)
	{
		ans+=(f[1][i]-f[1][i-1])*(b[1].maxn+i); 
	}
	printf("%.12lf",ans);
	return 0;
}
```



---

