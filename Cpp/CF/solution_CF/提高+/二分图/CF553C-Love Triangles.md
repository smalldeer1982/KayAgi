# Love Triangles

## 题目描述

There are many anime that are about "love triangles": Alice loves Bob, and Charlie loves Bob as well, but Alice hates Charlie. You are thinking about an anime which has $ n $ characters. The characters are labeled from $ 1 $ to $ n $ . Every pair of two characters can either mutually love each other or mutually hate each other (there is no neutral state).

You hate love triangles (A-B are in love and B-C are in love, but A-C hate each other), and you also hate it when nobody is in love. So, considering any three characters, you will be happy if exactly one pair is in love (A and B love each other, and C hates both A and B), or if all three pairs are in love (A loves B, B loves C, C loves A).

You are given a list of $ m $ known relationships in the anime. You know for sure that certain pairs love each other, and certain pairs hate each other. You're wondering how many ways you can fill in the remaining relationships so you are happy with every triangle. Two ways are considered different if two characters are in love in one way but hate each other in the other. Print this count modulo $ 1000000007 $ .

## 说明/提示

In the first sample, the four ways are to:

- Make everyone love each other
- Make 1 and 2 love each other, and 3 hate 1 and 2 (symmetrically, we get 3 ways from this).

In the second sample, the only possible solution is to make 1 and 3 love each other and 2 and 4 hate each other.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 1
```

### 输出

```
0
```

# 题解

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://codeforces.ml/contest/553/problem/C)

和 APIO2011 的方格染色有点像，可惜昨天模拟赛上把边权转点权想错了。

定义一条爱边边权为 $1$，恨边边权为 $0$。

注意到题目里”任意三个人“是一个很强的约束。考虑一条 $1$ 边 $(u,v)$ 产生的约束：对于一个其它的点 $w$，$(u,w)$ 和 $(v,w)$ 应该边权相同。

再考虑一条 $0$ 边 $(u,v)$ 产生的约束，对于一个其它的点 $w$，$(u,w)$ 和 $(v,w)$ 应该边权不同。

然后考虑一个性质：对于 $u,v,w$，我们任意定下其中任意两条边的边权，剩下一条边的合法边权应该唯一确定。即$(1,1)\rightarrow 1,(1,0)/(0,1)\rightarrow 0,(0,0)\rightarrow 1$。

于是得到结论：如果我们把给出的所有边（无论边权）连上。最后，对于任意两个极大连通块，其连法只有 $2$ 种。这是因为，确定两个连通块之间的一条边的边权，根据上面的性质，剩下的连接两个连通块之间的边权是唯一确定的，而这一条边又有 $2$ 种不同边权。更进一步地，我们可以直接缩点，一个连通块就等价于一个点。

假设最后剩下了 $m$ 个点同时不存在任何约束，显然答案为 $2^{m-1}$。 确定点 $2\sim m$ 和点 $1$ 之间的边权，类似地根据上面的那个性质，其他边都唯一确定。

但是缩点的同时还要判断是否合法。显然这是个经典问题，使用带权并查集或者种类并查集都能解决。

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,mod=1e9+7;
ll n,m,u,v,w,cnt;
ll fa[MAXN],d[MAXN],vis[MAXN];
ll power[MAXN];
int Find(int x){
	if(fa[x]==x)return x;
	int rt=Find(fa[x]);
	d[x]^=d[fa[x]];
	return fa[x]=rt;
}
int main(){
	power[0]=1;
	rep(i,1,1e5)power[i]=power[i-1]*2%mod;
	cin>>n>>m;
	rep(i,1,n)fa[i]=i;
	rep(i,1,m){
		cin>>u>>v>>w;
		int ru=Find(u),rv=Find(v);
		if(ru==rv){
			if(w==1){
				if(d[u]!=d[v])return printf("0"),0;
			}else{
				if(d[u]==d[v])return printf("0"),0;
			}
		}else{
			if(w==1){
				d[ru]=d[u]^d[v]; 
			}else{
				d[ru]=1^d[u]^d[v];
			}
			fa[ru]=rv;
		}
	}
	rep(i,1,n){
		if(vis[Find(i)])continue;
		vis[Find(i)]=1;cnt++;
	}
	cout<<power[cnt-1];
	return 0;
}
```



---

## 作者：_lbw_ (赞：4)

已有题解好像都不是很清晰，所以我来发一篇清晰的吧。

我们设爱边为 A，恨边为 B，先考虑没有限制的情况

我们考虑每一个 A 组成的连通块 设为 S

S 里面所有三元环的连边均符合条件为 AAA

因为它是完全图，所以只要连通块超过 2 个就会出现 ABB 或 BBB

考虑有限制

先把它染色一下，看一下哪些点在一个连通块里，那些不在

然后写个快速幂计数一下就解决了

难度虚高

```cpp
ll ksm(ll a,ll base)
{
	ll res=1;
	while(base)
	{
		if(base&1)res=res*a%mod;
		a=a*a%mod;
		base>>=1;
	}
	return res;
}
void dfs(ll u,ll ff,ll ty){
	if(vis[u])
		if(cor[u]!=ty)cout<<"0"<<endl,exit(0);
		else return;
	vis[u]=1;cor[u]=ty;
	for(int i=first[u];i;i=e[i].nxt){
		ll v=e[i].to;
		if(v==ff)continue;
		dfs(v,u,(e[i].w?ty:-ty));
	}
}
int main()
{
	n=read();m=read();
	for(ll i=1,u,v,ww;i<=m;i++)
		u=read(),v=read(),ww=read(),add(u,v,ww),add(v,u,ww);
	for(ll i=1;i<=n;i++)if(!vis[i])ans++,dfs(i,0,1);
	cout<<ksm(2,ans-1);
	return 0;
}
```




---

## 作者：Brioche (赞：4)

### [BLOG](https://www.cnblogs.com/terribleterrible/p/9879191.html)
 
Tyher推的好题.

题意就是给你一些好边一些坏边,其他边随意,让你求符合好坏坏~,或者只包含好好好的三元环的无向图个数.

坏坏的Tyher的题意是这样的.

再翻译得更加透彻一点就是:给你一些0(好边)边和1(坏边)边,让你求只包含011或者000的三元环的图的个数.

强强的zsy说:"Tyher你好坏啊!这不就是求合法的二分图个数嘛."

容易发现满足题目条件的图一定是只含有偶环(这里是边权和为偶数)的图,那不就是二分图嘛,于是只要统计一下1边相连的联通块个数k,答案就是$2^{k-1}$(因为二分图的两个集合是无区别的两个集合,所以除以2)
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define maxn 100005
#define ll long long
using namespace std;
int n,m,vis[maxn],ans,cor[maxn];
int head[maxn],nxt[maxn<<1],to[maxn<<1],w[maxn<<1],cnt;
void add(int u,int v,int ww)
{
	nxt[++cnt]=head[u];head[u]=cnt;
	to[cnt]=v;w[cnt]=ww;
}
int ksm(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)res=(ll)res*a%mod;
		b>>=1;a=(ll)a*a%mod;
	}
	return res;
}
void dfs(int u,int ff,int ty)
{
	if(vis[u])
	{
		if(cor[u]!=ty)cout<<"0"<<endl,exit(0);
		return ;
	}
	vis[u]=1;cor[u]=ty;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];if(v==ff)continue;
		dfs(v,u,(w[i]?ty:-ty));
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1,u,v,ww;i<=m;i++)
		scanf("%d%d%d",&u,&v,&ww),add(u,v,ww),add(v,u,ww);
	for(int i=1;i<=n;i++)if(!vis[i])ans++,dfs(i,0,1);
	printf("%d\n",ksm(2,ans-1));
	return 0;
}

```


---

## 作者：Krystallos (赞：2)

我们先理一下题意：

> 有一个无向图完全，边有爱边与恨边两种，三个点的关系要么由爱边连通，要么有且仅有一条爱边。

不难看出最后的图中点分为几个集合，集合内部全部是爱边，集合之间全都是恨边。

略略深入一想，最多只能有两个集合。但一个是可以的。

我们先看一个简化版的问题：图的要求与原题相同，点数为$n$，不给出已知边。那么答案显然为$2^{n-1}$。先固定第一个点，其余的$n-1$个点均有两种选择，加入1号点或与1号点对立。

看回原题：我们可不可以将相对关系已经确定的若干点压缩为一个点，把原题变成上面的简化版呢？

答案是肯定的。

使用并查集将由爱边连接的点合并，并压缩为一个点。判断原图是否满足题意`dfs`一遍即可。

答案为缩点后集合的数量带入公式。

**注意：由恨边连接的点也需要记为一个集合，因为它们的相对关系已经固定**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int nn = 1e5 + 5;
const int mod = 1000000007;
int father[nn], n, m, tot;
pair<int, int>hate[nn];
int vis[nn]; 
int getfather(int p) {
	return father[p] == p ? p : father[p] = getfather(father[p]);
}
inline void merge(int p, int q) {
	father[getfather(p)] = getfather(q);
}
int cnt, Begin[nn << 1], End[nn << 1], Last[nn], Prev[nn << 1];
inline void addedge(int p, int q) {
	cnt++;
	Begin[cnt] = p;
	End[cnt] = q;
	Prev[cnt] = Last[p];
	Last[p] = cnt;
}
void dfs(int p, int ff) {
	vis[p] = ff;
	for (int i = Last[p]; i; i = Prev[i]) {
		if (vis[End[i]] == 1) {
			dfs(End[i], ~ff);
		} else {
			if (~ff != vis[End[i]]) {
				printf("0");
				exit(0);
			}
		}
	}
}
int ksm(int a, int n) {
	long long ans = 1;
	while (n) {
		if (n & 1)
			ans = (ans * a) % mod;
		n >>= 1;
		a = 1ll * a * a % mod;
	}
	return ans;
}
int main() {
	scanf("%d %d", &n, &m);
	int a, b, c;
	for (int i = 1; i <= n; i++)
		father[i] = i;
	while (m--) {
		scanf("%d %d %d", &a, &b, &c);
		if (c == 1)
			merge(a, b);
		else
			hate[++tot] = pair<int, int>{a, b};
	}
	for (int i = 1; i <= tot; i++) {
		hate[i].first = getfather(hate[i].first);
		hate[i].second = getfather(hate[i].second);
		addedge(hate[i].first, hate[i].second);
		addedge(hate[i].second, hate[i].first);
	} 
	for (int i = 1; i <= n; i++)
		vis[i] = 1;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (vis[getfather(i)] == 1) {
			ans++;
			dfs(getfather(i), 0);
		}
	printf("%d", ksm(2, ans - 1));
	return 0;
}
```

---

## 作者：cosf (赞：1)

## [CF553C](https://www.luogu.com.cn/problem/CF553C)

感觉紫有点虚高了。

---

## 想法 1

这是一道性质题。

假设 $a \texttt{ love } b, b \texttt{ hate } c$，则显然 $a \texttt{ hate } c$，否则就矛盾了。

反之，假设 $a \texttt{ love } b, b \texttt{ love } c$，则显然 $a \texttt{ love } c$。

将其推广，就可以发现所有的 $\texttt{love}$ 连通块之内的所有人都是相 $\texttt{love}$ 的。如果条件不满足就直接输出 $0$。

那么，我们可以对原图进行 $\texttt{love}$ 连通块缩点，图上只剩下 $\texttt{love}$ 连通块和 $\texttt{hate}$ 边。

---

缩完点后，我们可以发现，图一定要是二分图才能满足要求。

为什么？假设图不是二分图，则存在奇环 $b_1, \dots, b_{k}$，其中 $b_i$ 代表一个连通块，相邻块之间有一条 $\texttt{hate}$ 边。那么，根据开头提到的结论，$b_i$ 与 $b_{i + 1}$ 中的每一对人都是互相 $\texttt{hate}$ 的，$b_{i + 1}$ 和 $b_{i + 2}$ 也是如此。那么随便从 $b_i, b_{i + 1}, b_{i + 2}$ 中抽三个人，他们中有两对是互相 $\texttt{hate}$ 的，那么剩下的，也就是 $b_i$ 和 $b_{i + 2}$ 中的那一对是相 $\texttt{love}$ 的。

这也就是说 $b_i$ 总是与 $b_{i + 2}$ 相 $\texttt{love}$。因为这是奇环，所以必当能推出 $b_i \texttt{ love } b_{i + 1}$，矛盾。

事实上，只要是通过 $\texttt{hate}$ 边连成的环 $b_i$，总是有 $b_i \texttt{ love } b_{i + 2}$ 的。

---

如果当前图是二分图，则答案就是把不同的连通块（指通过 $\texttt{hate}$ 边连通的 $\texttt{love}$ 块组成的连通块）连成二分图的方案数。

显然，连二分图的方案数就是 $2^{\text{连通块数量}-1}$。每一个块都可以分在两边，两种方案对称。

同一边的连通块都连上 $\texttt{love}$ 的边，不同的之间连 $\texttt{hate}$ 的边。

## 想法 2

事实上，我们可以将两人之间的关系视为一种等价关系。定义关系 $\sim: a \sim b \iff a \texttt{ love } b$。我们可以证明该关系是等价关系。

- 反身性：显然 $a \sim b$。
- 对称性：题目给定若 $a \sim b$，则 $b \sim a$。反之亦然。
- 传递性：若 $a \sim b, b \sim c$。由题目条件知必须 $a \sim c$，否则矛盾。

证明完毕。

选任意三人必有两人相 $\sim$，说明由所有人组成的集合最多只能划分成两个等价类。

这意味着等价类内的关系均为 $\texttt{love}$，等价类间的关系均为 $\texttt{hate}$。

这和二分图几乎是一样的。

因此只要判定题目给的关系没有矛盾后，对于每一个连通块，我们可以任意选择它属于哪一个等价类。

那么答案就是 $2^{\text{连通块个数}-1}$。两种分法对称。

## 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100005
#define MOD 1000000007

using pii = pair<int, int>;

vector<pii> e[2];

vector<int> f[MAXN];

int fa[MAXN];

int co[MAXN];

int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, m;

bool dfs(int p, int c)
{
    co[p] = c;
    for (int u : f[p])
    {
        if (co[u])
        {
            if (co[u] == co[p])
            {
                return false;
            }
            continue;
        }
        if (!dfs(u, c ^ 1))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[w].push_back({u, v});
    }
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    for (pii c : e[1])
    {
        fa[find(c.first)] = find(c.second);
    }
    for (pii c : e[0]) // 判断条件是否矛盾
    {
        int ff = find(c.first), sf = find(c.second);
        if (ff == sf)
        {
            cout << 0 << endl;
            return 0;
        }
        f[ff].push_back(sf);
        f[sf].push_back(ff);
    }
    for (int i = 1; i <= n; i++) // 判断是否是二分图
    {
        if (find(i) == i)
        {
            if (!co[i])
            {
                if (!dfs(i, 2))
                {
                    cout << 0 << endl;
                    return 0;
                }
            }
        }
    }
    for (pii c : e[0])
    {
        fa[find(c.first)] = find(c.second);
    }
    int cnt = -1;
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
        {
            cnt++;
        }
    }
    int r = 1;
    for (int i = 0; i < cnt; i++)
    {
        r = r * 2 % MOD;
    }
    cout << r << endl;
    return 0;
}

```

---

## 作者：esquigybcu (赞：1)

# Analysis

不妨记 $\oplus$ 为异或，记 $x\sim y=0$ 当且仅当 $x$ loves $y$，否则 $x\sim y=1$（注意这和输入格式是反的）。特殊地，记 $x\sim x=0$.

不难发现题目的要求相当于 $x\sim z=(x\sim y)\oplus(y\sim z)$. 那么：

> Lemma. 可以将 $n$ 个人每个人赋予一个值 $w_i$ 为 $0$ 或 $1$，使得 $i\sim j=w_i\oplus w_j$.

> Proof. 不妨令 $w_i=1\sim i$. 
> 
> 显然有 $i\sim j=(1\sim i)\oplus(1\sim j)=w_i\oplus w_j$. 

记 $S=\{i|w_i=0\},T=\{i|w_i=1\}$. 题目中每对给定的关系相当于指定 $i,j$ 在同一个/不同的集合中。这种关系我们可以用 **扩展并查集**（本人口胡的名字）维护。

# Extended DSU

我们维护一个大小为 $2n$ 的并查集。我们定义 $i$ 代表 $i\in S$，而 $i+n$ 代表 $i\in T$. 

这样，如果 $x\sim y=0$，我们就 `merge(x, y), merge(x + n, y + n);`

如果 $x\sim y=1$，我们就 `merge(x, y + n), merge(x + n, y);`

# The Answer

考虑所有“爱”和“恨”的关系构成的连通块。设一共有 $k$ 个这样的连通块。每个块中的关系是“相对”固定的：如果我们决定了其中**一个**元素属于 $S$ 还是 $T$，那么就可以推出整个块的每个元素属于 $S$ 还是 $T$. 从而一共有 $2^k$ 中方法……

但是我们交换 $S$ 和 $T$ 时，每对人的爱/恨关系是不变的，所以答案要除以 $2$.

# When Impossible? 

有的时候不存在答案，可以在 Extended DSU 中判断：

- 若输入 $x\sim y=0$ 但是 $x$ 与 $y+n$ 在同一个连通块中（或 $x+n$ 和 $y$）此时不存在答案；
- 若输入 $x\sim y=1$ 但是 $x$ 与 $y$ 在同一个连通块中（或 $x+n$ 和 $y+n$）此时不存在答案。

# Code
```cpp#include <stdio.h>

const int N = 1e5 + 5, MOD = 1e9 + 7;
typedef long long ll;

int father[N << 1], bl;
inline int fa(int x)
{
    if (x == father[x]) return x;
    return father[x] = fa(father[x]);
}
inline void merge(int x, int y)
{
    x = fa(x), y = fa(y);
    father[x] = y;
}

inline int qpow(int x, int k)
{
    if (k == 0) return 1;
    ll t = qpow(x, k >> 1); t = (t * t) % MOD;
    if (k & 1) t = (t * x) % MOD;
    return t;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    bl = n;
    for (int i = 1; i <= n * 2; i++) father[i] = i;

    while (m--)
    {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        if (w == 0)
        {
            if (fa(x) == fa(y)) return printf("0"), 0;
            if (fa(x) != fa(y + n)) bl--;
            merge(x, y + n); merge(x + n, y);
        }
        if (w == 1)
        {
            if (fa(x) == fa(y + n)) return printf("0"), 0;
            if (fa(x) != fa(y)) bl--;
            merge(x, y); merge(x + n, y + n);
        }
    }
    printf("%d", qpow(2, bl - 1));
    return 0;
}
```

---

## 作者：Otue (赞：0)

## [CF553C](https://www.luogu.com.cn/problem/CF553C)

考虑题目限制：其中任意三个点，连成的边合法的组合有 $111$，$100$。这就意味着确定三个点中的任意两条边，就可以确定另外一条边。例如 $(1,1)\to 1,(1,0)\to 0,(1,0)\to 0,(0,0)\to 1$。即异或值取反。

如果我们把给出的所有边连上，对于任意两个极大连通块，如果确定这两个联通块之间的任意一条边 $0/1$，则可确定这两个联通块的所有边。这样连接会不会出现矛盾？结论是，如果两个联通块之间的边无矛盾，则不会出现矛盾。

假设最后有 $m$ 个联通块，如何确定方案数？可以这样连：如果让 $1$ 联通块和 $2,3,\dots,m$ 确定关系，则 $2,3,\dots,m$ 之间的关系可以被确定。由于两个联通块之间有 $2$ 种方案，则答案为 $2^{m-1}$。

先用带权并查集先判断联通块之间的边有无矛盾！

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 3e5 + 5, mod = 1e9 + 7;

int n, m, p[N], d[N];

int find(int x) {
	if (p[x] != x) {
		int t = find(p[x]);
		d[x] ^= d[p[x]];
		p[x] = t;
	}
	return p[x];
}

int qpow(int a, int k, int p) {
	int res = 1;
	while (k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

signed main() {
	cin >> n >> m;
	_for(i, 1, n) p[i] = i;
	_for(i, 1, m) {
		int x, y, w;
		cin >> x >> y >> w;
		int fx = find(x), fy = find(y);
		if (fx == fy) {
			if (w == 1) {
				if (d[x] != d[y]) puts("0"), exit(0);
			}
			else if (d[x] == d[y]) puts("0"), exit(0);
		}
		else {
			if (w == 1) d[fx] = d[x] ^ d[y];
			else d[fx] = (1 ^ d[x] ^ d[y]);
			p[fx] = fy;
		}
	}
	int res = 0;
	_for(i, 1, n) if (find(i) == i) res++;
	cout << qpow(2, res - 1, mod) << endl;
}
```

---

## 作者：Hellsing_Alucard (赞：0)

### [Love Triangles](https://www.luogu.com.cn/problem/CF553C)

又是神仙题。

对于一个连通块来说，里面的边是全部确定的，这很显然。

对于多个连通块，他们的边可能是爱边，也可能是恨边。

所以只用求出有多少个连通块就可以了。

至于判断无解的情况，假设爱边为 $1$，恨边为 $-1$，一个合法的三元环乘积为 $1$，记录到每一个点的答案，如果冲突，则无解。


```cpp

int n,m;
inline int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int vis[N];
vector<pii>g[N];
int col[N];
inline void dfs(int u,int from,int tp){
	vis[u]=1;col[u]=tp;
	for(auto [v,w]:g[u]){
		if(v==from)continue;
		if(vis[v]){
	        if(col[v]!=(w?tp:-tp)){
		         cout<<"0"<<endl;
		         exit(0);
	        }
	        continue;
	    }
		dfs(v,u,(w?tp:-tp));
	}
}
signed main(){
	cin>>n>>m;
	int u,v,w;
    up(i,1,m){
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int ans=0;
	up(i,1,n)if(!vis[i])ans++,dfs(i,0,1);
	cout<<ksm(2,ans-1);
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

这道题由于本人实力有限，部分思路参考[大佬题解](https://www.cnblogs.com/PYWBKTDA/p/11254599.html)

------------
## 大致思路：
这道题可以分为三个部分：

1、建图，一定要用**链式前向星**~~否则 TLE 崩溃~~。

2、深度优先搜索，找出图中的的~~爱情之链~~联通块，进行**染色**（~~是的，你没听错，绕来绕去还是二分图~~）。

3、输出所有情况，可以用组合数学水过。


## 具体步骤：

1. 输入图的信息，用前向星存储~~避免超时~~，同时初始化 $is$ 数组为 $-1$，因为在后面找联通快时需要判断 $is$ 是否大于 $0$，从而实现染色功能。

2. 用 $O(n)$ 的时间复杂度循环遍历每个点，只要遇到 $is$ 数组（就是联通快中能进行匹配的王子数）小于 $0$ 的点，就进行染色，运行 dfs 函数。

3. 由于**只有“爱爱爱”与“爱恨恨”的情况**所以一条边上的点只有**两个点都染色**（爱爱）或者**一个染色一个不染**（爱恨），因此判断当 $is$ 数组大于等 $0$（染色了）时，返回与这条边上另外一个节点的颜色，并递归答案，实现染色功能。

4. 在计算答案之前，要把 $ans$ 赋值为 $mod$ 值除以 $2$ 再加 $1$ 的结果，因为染色只有 $1$ 和 $0$，属于组合数学中的以 $2$ 为底的组合数，所以要先除以 $2$，否则当 $ans$ 为 $0$ 时直接进行乘法运算就会“一片大红”。

------------



## 代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 6;
const int mod = 1000000007;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int to, val, next;
} edge[maxn];
int n, m, cnt;
int head[maxn], is[maxn], ans;
void add(int x, int y, int z)
{
    edge[++cnt].to = y;
    edge[cnt].val = z;
    edge[cnt].next = head[x];
    head[x] = cnt;
}
bool dfs(int x, int fa)
{
    if (is[x] >= 0)
    {
        return is[x] == fa;
    }
    is[x] = fa;
    for (int i = head[x]; i; i = edge[i].next)
    {
        if (!dfs(edge[i].to, fa ^ edge[i].val ^ 1))
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    n = read();
    m = read();
    memset(head, 0, sizeof(head));
    memset(is, -1, sizeof(is));
    ans = mod / 2 + 1;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    for (int i = 1; i <= n; i++)
    {
        if (is[i] < 0)
        {
            if (!dfs(i, 0))
            {
                ans = 0;
            }
            else
            {
                ans = ans * 2 % mod;
            }
        }
    }
    cout << ans;
    return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/120131076)


---

## 作者：Graphcity (赞：0)

由于作者并没有在这道题中看出二分图，所以写一个利用不同方式推导的题解。

不妨把爱边设为 $0$，恨边设为 $1$，那么可以发现题目中的限制即为任意一个三元环中边的异或和为 $0$。根据异或的性质，如果三元环中的两条边已经确定了，那么剩下的一条边也可以确定。

接下来观察整个完全图，观察到如果整个完全图外围的边确定了（也就是 $1-2,\ 2-3,\cdots,\ n-1$ 的边），那么整张完全图的边都可以随之确定。

更进一步可以发现外围边的异或和必然为 0。所以只需确定 $n-1$ 条边就好了。

考察限制 $(l,r,id)$，指的是边 $l-r$ 的权值为 $id$。事实上这等价于这些边 $l-(l+1),\ (l+1)-(l+2),\cdots,(r-1)-r$ 的异或和为 $id$。设 $sum_i$ 表示前 $i$ 条边的异或和，那么就有 $sum_{r-1}\operatorname{xor} sum_{l-1}=id$。也就是说，如果 $sum_{l-1}$ 的值确定了，那么 $sum_{r-1}$ 的值也就会随之确定。

判断是否能够满足所有限制，显然可以用 2-SAT 或者种类并查集。这里使用的是 2-SAT。

最后，如果一个连通块的某个值确定了，那么整个连通块都可以被确定。设连通块的个数为 $k$，那么答案就是 $2^{k-1}$，因为永远有 $sum_{0}=0$，$sum_0$ 所在的连通块可以被完全确定。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Mod=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Query{int l,r,id;} qry[Maxn+5];
int n,m,dfn[Maxn+5],low[Maxn+5],vis[Maxn+5];
int st[Maxn+5],col[Maxn+5],fa[Maxn+5],cur,tmp,top;
vector<int> v[Maxn+5];

inline int Find(int x) {return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Tarjan(int x)
{
    dfn[x]=low[x]=++cur,st[++top]=x,vis[x]=1;
    for(auto y:v[x])
    {
        if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        ++tmp;
        while(1)
        {
            int y=st[top--]; vis[y]=0,col[y]=tmp;
            if(x==y) break;
        }
    }
}

int main()
{
    n=read(),m=read();
    For(i,1,m)
    {
        qry[i].l=read(),qry[i].r=read(),qry[i].id=read()^1;
        if(qry[i].l>qry[i].r) swap(qry[i].l,qry[i].r);
    }
    For(i,1,m)
    {
        int l=qry[i].l,r=qry[i].r,id=qry[i].id;
        // sum[r-1]^sum[l-1]=id
        if(id) v[l].push_back(r+n),v[l+n].push_back(r),
               v[r].push_back(l+n),v[r+n].push_back(l);
        else v[l].push_back(r),v[l+n].push_back(r+n),
             v[r].push_back(l),v[r+n].push_back(l+n);
    }
    For(i,1,n*2) if(!dfn[i]) Tarjan(i);
    For(i,1,n) if(col[i]==col[n+i]) {printf("0\n"); return 0;}
    For(i,1,n) fa[i]=i;
    For(i,1,m)
    {
        int l=qry[i].l,r=qry[i].r;
        if(Find(l)!=Find(r)) fa[Find(l)]=Find(r);
    }
    int cnt=0,ans=1;
    For(i,1,n) if(fa[i]==i) cnt++;
    For(i,1,cnt-1) ans=ans*2%Mod;
    printf("%d\n",ans);
    return 0;
}
```

---

