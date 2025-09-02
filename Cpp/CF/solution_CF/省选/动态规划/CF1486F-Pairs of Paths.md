# Pairs of Paths

## 题目描述

You are given a tree consisting of $ n $ vertices, and $ m $ simple vertex paths. Your task is to find how many pairs of those paths intersect at exactly one vertex. More formally you have to find the number of pairs $ (i, j) $ $ (1 \leq i < j \leq m) $ such that $ path_i $ and $ path_j $ have exactly one vertex in common.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486F/a19cd21d095785ac889753153b27201ab276d741.png)

The tree in the first example and paths look like this. Pairs $ (1,4) $ and $ (3,4) $ intersect at one vertex.

In the second example all three paths contain the same single vertex, so all pairs $ (1, 2) $ , $ (1, 3) $ and $ (2, 3) $ intersect at one vertex.

The third example is the same as the first example with two additional paths. Pairs $ (1,4) $ , $ (1,5) $ , $ (2,5) $ , $ (3,4) $ , $ (3,5) $ , $ (3,6) $ and $ (5,6) $ intersect at one vertex.

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
3 5
4
2 3
2 4
3 4
3 5```

### 输出

```
2```

## 样例 #2

### 输入

```
1
3
1 1
1 1
1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
3 5
6
2 3
2 4
3 4
3 5
1 1
1 2```

### 输出

```
7```

# 题解

## 作者：syksykCCC (赞：6)

不妨钦定 $1$ 为根分析。 

考虑如下问题：恰有一个交点的两条链会长成什么样子。

其实分为两种情况：一是它们的 $\text{LCA}$ 相同，而是它们的 $\text{LCA}$ 不同。如下图所示。

![image.png](https://i.loli.net/2021/02/19/GCde8hplymbBWYR.png)

左图中 `LCA` 表示两条链 $A, B$ 公共的 $\text{LCA}$，而右图中 `LCA` 则是 $A$ 的 $\text{LCA}$（也就是两条链的 $\text{LCA}$ 中较深的那一个）。

现在，我们对于给定的一条链 $(u, v)$，求出它的三个值：$lca, a, b$。$a$ 表示 $u$ 在 $lca$ 的哪一棵子树中，$b$ 表示 $v$ 在 $lca$ 的哪一棵子树中。或者可以理解为，设 $u$ 与 $lca$ 的深度差为 $k$，则 $a$ 是 $u$ 的 $k-1$ 级祖先，$b$ 是 $v$ 的 $k-1$ 级祖先。值得注意的是，可能 $u, v$ 互为祖先—后代关系，比如 $u$ 是 $v$ 的祖先，那么我们可以钦定 $a$ 为一个**新开的点**，避免对后面的统计造成影响。同时为了方便，请确保 $a<b$，这一点可以通过交换 $u, v$ 和 $a, b$ 很简单的达到。

现在，我们分别考虑求出上面两种情况对答案的贡献。

先考虑第一种情况，我们可以把所有的链先按 $lca$ 的深度，再按 $lca$ 排序。对于 $lca$ 相同的一些链，显然我们求的就是 **$\boldsymbol{a_x, b_x, a_y, b_y(a_x<a_y)}$ 互不相同的链对 $\boldsymbol{(x, y)}$** 的数量。为了确保不重不漏，我们不妨按照 $a$ **严格递增**的顺序去一段一段地枚举链 $y$，同时开个桶 $buk_i$ 记录一下从子树 $i$ 中伸出来的链的条数。每次 $ans \gets ans + cnt - buk_{b_y}$，然后分别把 $buk_{a_y}, buk_{b_y} + 1$ 就好了。上面 $cnt$ 表示的是已经枚举过的链的条数。具体细节参考代码。

考虑第二种情况，我们依然可以把所有的链先按 $lca$ 的深度，再按 $lca$ 排序。设以 $u$ 为根的子树对应 $\text{DFS}$ 序上 $[\textit{ldf}_u, \textit{rdf}_u]$ 这一段。用树状数组维护一个 $\text{DFS}$ 序，每次 $ans \gets ans + \operatorname{Sum}(\textit{ldf}_{lca}, \textit{rdf}_{lca})$，然后如果 $a$ 不是新建的点的话，$ans \gets ans - \operatorname{Sum}(\textit{ldf}_{a}, \textit{rdf}_{a})$，$b$ 同理。最终我们把 $\text{DFS}$ 序上的 $x$ 和 $y$ 位置分别 $+1$ 就可以了。正确性显然。

按照上面的做法是一个 $\log$ 的，但是通过一些奇技淫巧可以优化成线性，这里不再讨论。

代码实现推荐兔队长的[赛时提交](https://codeforces.com/contest/1486/submission/107847205)，个人认为写的很清晰了。

---

## 作者：ExplodingKonjac (赞：4)

### [【原题链接】](http://9ng.cn/UvWH)

提供一种充分发扬人类智慧的解法。

## 题目分析

为了方便叙述，我们采取以下称谓：题目中给的那 $m$ 条链成为**关键链**；每一条链两个端点的 $\text{LCA}$ 叫做这条链的**顶点**；在这条链上顶点的两个儿子称为 **关键点**；特别地，如果一条链只有一个或者没有关键点，我们钦定一个新点（编号 $n+1,n+2,\dots$）顶替关键点的位置，便于处理。

首先分类讨论：

### 两条链的顶点相同：

我们用一条链去数和这条链顶点相同且只有一个交点的链的数量。假设这个数量为 $cnt_1$，则

$$cnt_1=|\{\text{顶点与该链相同}\}|-|\{\text{有一个关键点相同}\}|+|\{\text{两个关键点都相同}\}|$$

这里的统计可以用桶和 `map` 完成。

### 两条链的顶点不同：

引入：如果没有交点仅有一个的限制应该怎么做。

我们对于每条关键链，我们把链上的点点权 $+1$，把链上的边边权 $-1$。然后，你会神奇地发现，如果你查询某条链上的点权与边权之和，每条和其相交关键链的贡献刚好是 $1$，你也就知道了经过查询链的链个数。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uyse2c91.png)

如上过程可以用树上差分和前缀和轻松解决，于是我们知道了与询问链相交的关键链数。

现在我们使用类似的思路。目标是找出来**不符合规定**，即交点大于一个的关键链个数。

对于一条关键链，我们这样改一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/swhyemnm.png)

在这种处理方法中，顶点相同的链对会被算两次。但是我们之前已经处理了顶点相同的情况，减回去即可。于是，我们近乎完美地解决了这个问题。但是问题结束了吗？没有，考虑一些特殊情况。

### 特例以及特例的特例：

考虑如下方式的诡异关键链。

![](https://cdn.luogu.com.cn/upload/image_hosting/z41ete4q.png)

我们发现，这种关键链的贡献为 $2$。所以，我们要加回一个关键点与查询链完全相同的关键链个数。

再考虑如下方式的诡异询问链：

![](https://cdn.luogu.com.cn/upload/image_hosting/8mfhkl81.png)

我们发现，它对自己的贡献为 $1$，但是在上面的处理中被加回来了。因此，遇到这种情况，我们需要再 $-1$。

有且仅有这两种特例，处理完就没有问题了。

### 总结

我们的思路是：对于一条链，求出经过其关键链个数，减去其中交点不只一个的个数。求和即得一个答案。但是这个答案中有重算，减去就得到正确答案。

## 代码实现

讲的你大概率是看不懂的，最好结合一下代码自行理解。我自己写的时候也绕了好久。

```cpp
#include <bits/stdc++.h>
using namespace std;
  
/*
省略100多行的快读快写模板
即下文中的qin、qout
*/

typedef long long LL;
int n,m,up[300005],l[300005],r[300005];
int bk[900005],zt[300005],fuck[300005];
LL ans,sum;
struct Pair
{
	int x,y;
	Pair()=default;
	Pair(int _x,int _y): x(_x),y(_y)
		{ if(x>y)swap(x,y); }
	inline bool operator <(const Pair &b)const
		{ return x!=b.x?x<b.x:y<b.y; }
}p[300005];
map<Pair,int> mp;
struct Edge{ int to,nxt; }e[600005];
int cnt,head[300005];
inline void addEdge(int u,int v)
	{ e[++cnt]=(Edge){v,head[u]},head[u]=cnt; }
int dep[300005],f[300005][20];
int d1[300005],a1[900005],s1[300005],d2[300005],a2[900005],s2[300005];
//1: vert, 2: edge
void dfs(int u,int fa=0)
{
	dep[u]=dep[fa]+1,f[u][0]=fa;
	for(int i=1;(1<<i)<=dep[u];i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa)	dfs(v,u);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])	swap(x,y);
	for(int i=19;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y)	return x;
	for(int i=19;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
int tot;
int jump(int x,int y)
{
	if(dep[x]<=dep[y])	return ++tot;
	for(int i=19;i>=0;i--)
		if(dep[f[x][i]]>dep[y])
			x=f[x][i];
	return x;
}
void prework1(int u,int fa=0)
{
	a1[u]=d1[u],a2[u]=d2[u];
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa)
			prework1(v,u),a1[u]+=a1[v],a2[u]+=a2[v];
}
void prework2(int u,int fa=0)
{
	s1[u]=a1[u]+s1[fa],s2[u]=a2[u]+s2[fa];
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa)	prework2(v,u);
}
inline void add1(int x,int y,int l,int v)
	{ d1[x]+=v,d1[y]+=v,d1[l]-=v,d1[f[l][0]]-=v; }
inline void add2(int x,int y,int l,int v)
	{ d2[x]+=v,d2[y]+=v,d2[l]-=2*v; }
inline int query1(int i)
	{ return s1[l[i]]+s1[r[i]]-s1[up[i]]-s1[f[up[i]][0]]; }
inline int query2(int i)
	{ return s2[l[i]]+s2[r[i]]-2*s2[up[i]]; }
int main()
{
	qin>>n,tot=n;
	for(int i=1;i<n;i++)
	{
		int u,v;qin>>u>>v;
		addEdge(u,v),addEdge(v,u);
	}
	dfs(1);
	qin>>m;
	for(int i=1;i<=m;i++)
	{
		qin>>l[i]>>r[i];
		up[i]=lca(l[i],r[i]),p[i]=Pair(jump(l[i],up[i]),jump(r[i],up[i]));
		mp[p[i]]++,bk[p[i].x]++,bk[p[i].y]++,zt[up[i]]++;
		add1(l[i],r[i],up[i],1),add2(l[i],r[i],up[i],-1);
	}
	prework1(1),prework2(1);
	for(int i=1;i<=m;i++)	ans+=query1(i)+query2(i);
	for(int i=1;i<=m;i++)	a1[up[i]]--,a2[p[i].x]++,a2[p[i].y]++;
	prework2(1);
	for(int i=1;i<=m;i++)
	{
		ans-=query1(i)+query2(i);
		if(p[i].y<=n)	ans+=mp[p[i]];
		if(p[i].x>n)	ans--;
	}
	for(int i=1;i<=m;i++)	sum+=zt[up[i]]-bk[p[i].x]-bk[p[i].y]+mp[p[i]];
	qout<<ans-sum/2;
//	return qout.flush(),0;
}

```


---

## 作者：Luciylove (赞：3)

都 3202 年了，我还是永远喜欢正向计数（bushi）。

显然是 CF1336F 弱化版。值得一提的是，在 standing 上有一个老哥，交了一份很神奇的代码，好像拼了 CF1336F 的 std，然后拼了两份，一减就求得答案。

考虑分类计数，目前我们有两条链 $x \to y$ 和 $p\to q$。

记录 $l_{x, y}$ 为两条链底部分别为 $x,y$ 的 LCA。

$l_{x, y} = l_{p, q}$

这个 case 建议正难则反，考虑为所有过这个点的 chains 的个数 $\dfrac{size \times (size - 1)}{2}$ 减去有一个子树走向相同，再加上有两个子树走向相同。

这个是简单的。

$l_{x, y} \not = l_{p, q}$

容易发现深度大的那个点必然再另一个路径上。考虑钦定前者为 $x \to y$ 用这个来计数。考虑树上差分，那么可以从 $l_{x, y}$ 的子树内的一个点走上来且与 $x \to l_{x, y},l_{x, y} \to y$ 这两颗子树不交的点才是和法的。结合树状数组可以做到 $1\log$。

注意 $l_{x, y} = x$ 之类的，这些情况都要在计算贡献时加**特判**，具体细节可以参考代码。

我写了一份比较清真的实现如下：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

using namespace std;
typedef long long ll;

const int _ = 4e5 + 5, mod = 998244353;

namespace FenwickIndex {
	#define lowbit(x) (x & -x)
	int sz;
	int c[_];
	void init (int tot) { memset(c, 0, sizeof(c)); sz = tot; }
	void add (int x, int k) { while (x <= sz) c[x] += k, x += lowbit(x); }
	ll query (int x) { 
		ll res = 0;
		while (x) res += c[x], x -= lowbit(x);
		return res;
	}
	ll querysum (int l, int r) { 
		return query(r) - query(l - 1); 
	}
} using namespace FenwickIndex;

int n, m, dfc;
ll ret;
int dfn[_], ed[_], dep[_], anc[_][20];
vector <int> e[_];
vector <pair<int, int> > ad[_];

void dfs1 (int x, int fa) {
	dep[x] = dep[fa] + 1, anc[x][0] = fa;
	dfn[x] = ++ dfc;
	rep(i, 1, 19) anc[x][i] = anc[anc[x][i - 1]][i - 1];
	for (int y : e[x]) if (y ^ fa) dfs1(y, x);
	ed[x] = dfc;
}
int LCA (int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int d = (dep[x] - dep[y]);
	rep(i, 0, 19) if (d & (1 << i)) x = anc[x][i];
	if (x == y) return x;
	per(i, 19, 0) if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}
int kthanc (int x, int k) { 
	if (k == -1) return x;
	rep(i, 0, 19) if (k & (1 << i)) x = anc[x][i]; return x; 
}

int tmp[_];
map <pair<int, int>, int> mp;
vector <pair<int, int> > chain[_];

void dfs2 (int x, int fa) {
	int num = chain[x].size();
	ll res = 1ll * (num - 1) * num / 2, de = 0;
	for (auto & [u, v] : chain[x]) tmp[u] ++, tmp[v] ++, mp[{u, v}] ++;
	for (auto & [u, v] : chain[x]) {
		if (u != x) de += tmp[u] - 1;
		if (v != x) de += tmp[v] - 1;
		if (u != x && v != x) de -= mp[{u, v}] - 1;
	}
	res -= de / 2ll, ret += res;
	for (auto & [u, v] : chain[x]) tmp[u] = tmp[v] = mp[{u, v}] = 0;
	for (auto & [u, v] : chain[x]) {
		ll nd = querysum(dfn[x], ed[x]);
		if (u != x) nd -= querysum(dfn[u], ed[u]);
		if (v != x) nd -= querysum(dfn[v], ed[v]);
		ret += nd;
	}
	for (auto & [p, k] : ad[x]) add(dfn[p], k);  
	for (int y : e[x]) if (y ^ fa) dfs2(y, x);
}
int main() {
	/*
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
	黛拉可玛莉·岗德森布莱德，一亿年一遇美少女。
	*/
	cin >> n;
	init(n + 2);
	rep(i, 1, n - 1) {
		int x, y;
		scanf("%d%d", & x, & y);
		e[x].push_back(y), e[y].push_back(x);
	}
	dfs1(1, 0);
	cin >> m;
	rep(i, 1, m) {
		int x = 1, y = 1, lc;
		scanf("%d%d", & x, & y);
		lc = LCA(x, y);
		int a = kthanc(x, dep[x] - dep[lc] - 1), b = kthanc(y, dep[y] - dep[lc] - 1);
		if (a < b) swap(a, b);
		chain[lc].push_back({a, b});
		if (x != lc) ad[lc].push_back({x, 1}), ad[x].push_back({x, -1});
		if (y != lc) ad[lc].push_back({y, 1}), ad[y].push_back({y, -1});
	}
	dfs2(1, 0);
	cout << ret << endl;
	return 0;
}
```





---

## 作者：zjjws (赞：3)

[更好的阅读体验](https://www.cnblogs.com/zjjws/p/14458365.html)

---

### 题意

[题链](https://codeforces.com/contest/1486/problem/F)

给定 $n$ 个点的树，和 $m$ 路径，求有且仅有一个公共点的路径对数。

---

### Solution

分类讨论一下：

$1.$ 除了一个点的路径以外，其它的路径相互之间若要只有一个公共点，那么这个公共点必定在其中一个路径的 Lca 上。这点易证。

对于剩下的情况中，我们把路径按照 Lca 是否相同来分类，并且对于同类和不同类的两种贡献分开计算。

我们会发现，一条路经 $(x,y,z),z=\texttt{Lca}(x,y)$，另外一条路径 $(a,b)$ 与 $(x,y)$ 只有一个公共点的充要条件是：找到 $x,y$ 对应的祖先，满足是 $z$ 的儿子的两个点 $x',y'$，$(a,b)$ 不经过 $x'$ 且不经过 $y'$。

$2.$ 对于不同类的两条路径，只需要对于每条路径 $(x,y)$ 查询 **经过它们 Lca 的不同类路径数量**，和分别 **经过** $x',y'$ **的不同类路径数量**。（因为是不同类路径，所以不存在同时经过 $x',y'$ 的路径，除了 $\texttt{Lca}(x,y)=y$ 的情况特殊考虑一下）

$3.$ 对于同类的，只需要容斥一下，因为两两不同的不太好算，我们用总的减去两个都相同的，以及有且仅有一个相同的数量。

大体思路就是这么简单，具体代码实现可能有一点细节需要注意。

因为这是我自己胡的 $\operatorname O(n\log n)$ 做法，没看题解，所以可能会有更加简便的同类复杂度做法在常数上爆踩我，毕竟我是大常数选手。

说不定不是常数的问题，因为我预处理的复杂度是 $\operatorname O(n\log n)$ 的，如果能够有 $\operatorname O(n)$ 处理出 Lca 以及 $x',y'$ 的东西，那这道题的复杂度就能够达到 $\operatorname O(n)$ 了。

不知道 CF 上 DP 的标签是怎么回事，说不定有 DP 的做法。

---

### Code

```cpp
#include <vector>
#include <stdio.h>
#include <algorithm>
#define LL long long
#pragma GCC optimize(3)
using namespace std;
const int Rea=1e5+3;
struct Rin
{
    char c;
    inline char gc()
    {
        static char rea[Rea];
        static char *head,*tail;
        return head==tail&&(tail=(head=rea)+fread(rea,1,Rea,stdin),head==tail)?EOF:*head++;
    }
    inline Rin&operator >>(int &x)
    {
        x=0;
        bool tag=false;
        for(c=gc();c>'9'||c<'0';c=gc())if(c=='-'){c=gc();tag=true;break;}
        for(;c>='0'&&c<='9';c=gc())x=(x<<1)+(x<<3)+(c^'0');
        if(tag)x=-x;
        return *this;
    }
}rin;
inline void jh(int &x,int &y){if(x^y)x^=y^=x^=y;return;}
const int N=3e5+3;
int n,m;

namespace St
{
    vector<int>nxt[N];
    int f[20][N];
    int dep[N];
    inline void dfs(int x,int fa){dep[x]=dep[fa]+1;f[0][x]=fa;for(vector<int>::iterator i=nxt[x].begin();i!=nxt[x].end();i++)if((*i)!=fa)dfs(*i,x);}
    inline int Lca(int x,int y)
    {
        if(dep[x]<dep[y])jh(x,y);
        for(int i=dep[x]-dep[y],j=0;i;i>>=1,j++)if(i&1)x=f[j][x];
        for(int j=0;j>=0;){if(f[j][x]!=f[j][y])x=f[j][x],y=f[j][y],j++;else j--;}
        if(x!=y)x=f[0][x];
        return x;
    }
    inline int find(int x,int y){for(int i=dep[x]-dep[y]-1,j=0;i>0;i>>=1,j++)if(i&1)x=f[j][x];return x;}
}
using namespace St;


vector<int>a[N];
vector<pair<int,int> >b[N];
int les[N];
int cutt[N];
int ruir[N];
int ruier[N];
LL ans;

inline void init_ans(int x,int fa)
{
    int cuts=a[x].size()+b[x].size();
    for(vector<int>::iterator i=nxt[x].begin();i!=nxt[x].end();i++)if((*i)!=fa)init_ans(*i,x),ruir[x]+=ruir[*i];
    ans+=1LL*ruir[x]*ruier[x];ans+=1LL*ruier[x]*(ruier[x]-1)>>1;
    for(vector<int>::iterator i=a[x].begin();i!=a[x].end();i++)ruir[*i]--;
    for(vector<pair<int,int> >::iterator i=b[x].begin();i!=b[x].end();i++)ruir[i->first]--,ruir[i->second]--;
    for(vector<int>::iterator i=a[x].begin();i!=a[x].end();i++)ans+=(ruir[x]-cuts-ruir[*i]);
    for(vector<pair<int,int> >::iterator i=b[x].begin();i!=b[x].end();i++)ans+=(ruir[x]-cuts-ruir[i->first]-ruir[i->second]);
    ans+=1LL*cuts*(cuts-1)>>1;
    sort(b[x].begin(),b[x].end());
    for(vector<int>::iterator j=a[x].begin();j!=a[x].end();j++)ans-=cutt[*j],cutt[*j]++;
    for(vector<pair<int,int> >::iterator j=b[x].begin(),k;j!=b[x].end();j=k)
    {
        int nows=1;
        for(k=j+1;k!=b[x].end()&&(*j)==(*k);k++)nows++;
        ans-=1LL*nows*(nows-1)>>1;
        ans-=1LL*(cutt[j->first]+cutt[j->second])*nows;
        cutt[j->first]+=nows;cutt[j->second]+=nows;
    }
    for(vector<int>::iterator j=a[x].begin();j!=a[x].end();j++)cutt[*j]--;
    for(vector<pair<int,int> >::iterator j=b[x].begin();j!=b[x].end();j++)cutt[j->first]--,cutt[j->second]--;
    ruir[x]-=les[x];
    return;
}
int main()
{
    rin>>n;for(int i=1;i<n;i++){int x,y;rin>>x>>y;nxt[x].push_back(y);nxt[y].push_back(x);}
    dfs(1,0);for(int i=1;(1<<i)<=n;i++)for(int j=1;j<=n;j++)f[i][j]=f[i-1][f[i-1][j]];
    rin>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        rin>>x>>y;
        if(x==y){ruier[x]++;continue;}
        if(dep[x]<dep[y])jh(x,y);
        z=Lca(x,y);
        int x_=find(x,z),y_=find(y,z);
        if(y==z)a[z].push_back(x_);
        else b[z].push_back(make_pair(min(x_,y_),max(x_,y_)));
        ruir[x]++;ruir[y]++;ruir[z]--;les[z]++;
    }
    init_ans(1,0);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Chr0n1CleC (赞：1)

我不会性质但是我会点边容斥。

### Part 1 交集长度 $\ge x$ 的对数

我们发现交集是一个链，那么交集 $\ge x$ 的方案即为指定穿过一个长度为 $x$ 的链的方案数减去指定穿过一个长度为 $x+1$ 的链的方案数。

因为这两者在一个长为 $n$ 的链上出现次数分别为 $n-x+1$ 和 $n-x$，于是这个方法完全正确。

### Part 2 具体的实现

然后计算答案就是交集 $\ge1$ 的答案减去 $\ge 2$ 的答案。

其中长度为 $1$ 和 $2$ 的都是容易计算的，考虑算长度为 $3$ 的答案。

如果端点有祖先关系，那么这样的链是特别少的，可以直接通过容斥统计。

如果没有，不难发现这条链的中点即路径的 lca。有一个路径时也容易找到这个长度为 $3$ 的链。然后开一个 `unordered_map` 维护这个东西。

### 复杂度

我们只需要可离线地求出每条链那个中点为 lca 的那条链的另外两个点。其中可以用长剖+线性 lca 做到 $O(n+m)$ 的复杂度。

因为偷懒，写的倍增，所以复杂度为 $O((n+m)\log n)$。

[submission](https://codeforces.com/contest/1486/submission/327041898)

---

## 作者：7KByte (赞：1)

经典结论：指定一个根，则两条路径的交一定过一条路径的 $\texttt{LCA}$。

所以如果两条路径的交是一个点，则一定是一条路径的 $\texttt{LCA}$，更具体一点，一定是较深的 $\texttt{LCA}$。

所以我们枚举较深的 $\texttt{LCA}$ ，对于另外一条路径分开讨论。

第一种情况：两条路径的 $\texttt{LCA}$ 相同。

容斥一下即可，总数$\dfrac{size\times (size-1)}{2}$，减去在一个子树内相交的个数，再加上两个子树都相交的个数。这里我们可以开一个桶解决，排序线性的话可以在 $\rm O(N)$ 时间内解决。

第二种情况：另一条路径的 $\texttt{LCA}$ 深度小。

我们对所有路径按 $\texttt{LCA}$ 深度从小到大排序。将 $\texttt{LCA}$ 深度小于当前 $\texttt{LCA}$ 深度的点的 $cnt+1$。这样当前 $\texttt{LCA}$ 对答案的贡献也可以容斥一下算出来。具体一点，就是以 $\texttt{LCA}$ 为根整个子树的 $cnt$ 之和，减去路径一端 $u$ 对应的子树的和，再减去路径另一端 $v$ 对应的子树之和。

这可以用 $\rm DFS$ 序 $+$ 树状数组在$\rm O(M\log N)$的时间内解决。

注意一下如果路径是一条单链/一个点需要特别处理边界情况。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 300005
using namespace std;
int n,m,h[N],tot,d[N],f[N][20],t,dfn[N],idx,c[N],sz[N],u[N],v[N];long long ans=0;
struct edge{int to,nxt;}e[N<<1];
inline void adde(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
inline void add(int x,int y){for(;x<=n;x+=x&-x)c[x]+=y;}
inline int ask(int x){int sum=0;for(;x;x-=x&-x)sum+=c[x];return sum;}
void dfs(int x,int fa){
	f[x][0]=fa;dfn[x]=++idx;d[x]=d[fa]+1;sz[x]=1;
	rep(i,1,t)f[x][i]=f[f[x][i-1]][i-1];
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa)dfs(e[i].to,x),sz[x]+=sz[e[i].to];
}
inline int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	pre(i,t,0)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	pre(i,t,0)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int get(int x,int y){
	pre(i,t,0)if(d[f[x][i]]>=y)x=f[x][i];
	return x;
}
struct node{
	int l,x,y;
	bool operator<(const node o)const{return l<o.l;}
}a[N];
bool cmp(node x,node y){return d[x.l]<d[y.l];}
map<pair<int,int>,int>w;
void calc(int l,int r){
	rep(i,l,r){
		ans+=i-l;
		if(~a[i].x)ans-=c[a[i].x];
		if(~a[i].y)ans-=c[a[i].y];
		if(~a[i].x&&~a[i].y&&w.count(make_pair(a[i].x,a[i].y)))ans+=w[make_pair(a[i].x,a[i].y)];
		if(~a[i].x)c[a[i].x]++;
		if(~a[i].y)c[a[i].y]++;
		if(~a[i].x&&~a[i].y)w[make_pair(a[i].x,a[i].y)]++;
	}
	rep(i,l,r){
		if(~a[i].x)c[a[i].x]--;
		if(~a[i].y)c[a[i].y]--;
	}
	w.clear();
}
void calc1(){
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		a[i].l=lca(x,y);u[i]=x;v[i]=y;
		a[i].x=(x==a[i].l?-1:get(x,d[a[i].l]+1));
		a[i].y=(y==a[i].l?-1:get(y,d[a[i].l]+1));
		if(a[i].x>a[i].y)swap(a[i].x,a[i].y);
	}
	sort(a+1,a+m+1);int pre=1;
	//rep(i,1,m)printf("%d %d %d\n",a[i].l,a[i].x,a[i].y);
	rep(i,2,m)if(a[i].l!=a[i-1].l){calc(pre,i-1);pre=i;}
	calc(pre,m);
}
inline void solve(int l,int r){rep(i,l,r)add(dfn[a[i].x],1),add(dfn[a[i].y],1);}
void calc2(){
	rep(i,1,m)a[i].l=lca(u[i],v[i]),a[i].x=u[i],a[i].y=v[i];
	sort(a+1,a+m+1,cmp);int pre=1;
	rep(i,2,m){
		if(d[a[i].l]!=d[a[i-1].l])solve(pre,i-1),pre=i;
		ans+=ask(dfn[a[i].l]+sz[a[i].l]-1)-ask(dfn[a[i].l]-1);
		int cur;
		if(a[i].x!=a[i].l){
			cur=get(a[i].x,d[a[i].l]+1);
			ans-=ask(dfn[cur]+sz[cur]-1)-ask(dfn[cur]-1);
		}
		if(a[i].y!=a[i].l){
			cur=get(a[i].y,d[a[i].l]+1);
			ans-=ask(dfn[cur]+sz[cur]-1)-ask(dfn[cur]-1);
		}
	}
}
int main(){
	scanf("%d",&n);t=log2(n);
	rep(i,1,n-1){int x,y;scanf("%d%d",&x,&y);adde(x,y);adde(y,x);}
	dfs(1,0);scanf("%d",&m);calc1();calc2();
	return printf("%lld\n",ans),0;
}
```

---

## 作者：冷却心 (赞：0)

> 给定一棵树，$n$ 个结点，又给定了 $m$ 条简单路径，每条路径从 $u_i$ 到 $v_i$。求有多少对简单路径有且仅有一个交点。

方便起见，以下钦定 $1$ 为根。记 $l_i$ 表示 $u_i,v_i$ 的最近公共祖先，则与这条路径的交为一个点的另一条路径 $j$ 一定满足如下任意一个条件：

- $l_j=l_i$ 且 $u_i,v_i,u_j,v_j$ 都不在 $l_i$ 的同一个子树内，如果在同一个子树内，显然交点不止一个。
- $u_i,v_i$ 其中有且仅有一个在 $l_i$ 子树内，另一个在子树外，并且在子树内的这一个点 $p$ 不在 $u_i$ 或 $v_i$ 的子树内。

所以我们考虑把路径挂到 LCA 上统计答案，用 `vector` 可以简单维护，然后针对这两种情况分类讨论。

针对第一种情况，我们预处理一个 $w_i$ 表示一端在 $i$ 子树内，另一端在 $i$ 子树外的路径条数，以及 $c_i$ 表示一端在 $i$ 子树内，一端在 $i$ 父亲的子树外的路径个数。那么对于路径 $i$，根据我们的讨论，它的贡献是一个端点在 $l_i$ 子树内且不在包含 $u_i$ 或 $v_i$ 的子树内的路径个数，即 $w_{l_i} - c_{u_i}-c_{v_i}$。然后考虑树上差分可以简单处理出 $w_i,c_i$。

针对第二种情况，我们发现睁着不好直接求，考虑容斥，第 $i$ 条边造成的贡献等于：**路径 LCA 为 $l_i$ 的总数** 减去 **路径一端在包含 $u_i$ 的子树内的个数** 减去 **路径一端在包含 $v_i$ 的子树内的个数** 加上重复减掉的 **路径两端分别在包含 $u_i,v_i$ 的子树内的个数**。中间两种是可以直接开一个桶维护，最后一种可以写一个哈希表维护。注意这种情况每对路径会被统计两次，要除以 $2$。

然后就做完了。

上文中提到了许多形如“$l$ 中包含 $u$ 的子树内”，考虑怎么求这个，也就是求出 $u$ 在 $l$ 的哪一棵子树内，求出其根，倍增 LCA 可以直接做，树剖 LCA 可以考虑在跳重链的时候记录一个链顶，最后考虑跳到的是轻儿子还是重儿子即可，具体参考代码中的 `Jump` 函数。

然后这题还有一些 Corner Case：

- $u_i=v_i$ 的时候单独统计。
- $u_i$ 是 $v_i$ 的祖先的时候也要注意讨论（反之同理）。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define LL long long
using namespace std;
const int N = 3e5 + 10;
int n, m; vector<int> G[N]; // 存图
namespace SPLIT { // 树剖
int dfn[N], top[N], depth[N], fa[N], dfntot = 0, sz[N], hson[N];
void DFS1(int u, int f) {
	depth[u] = depth[f] + 1; fa[u] = f; sz[u] = 1;
	for (int v : G[u]) if (v != f) {
		DFS1(v, u); sz[u] += sz[v]; if (sz[v] > sz[hson[u]]) hson[u] = v; 
	} return ;
}
void DFS2(int u, int f) { dfn[u] = ++ dfntot;
	if (hson[u]) { top[hson[u]] = top[u]; DFS2(hson[u], u); }
	for (int v : G[u]) if (v != f && v != hson[u]) {
		top[v] = v; DFS2(v, u);
	} return ;
}
void build(int rt) { top[rt] = rt; DFS1(rt, 0); DFS2(rt, 0); }
int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
		u = fa[top[u]];
	} return (depth[u] < depth[v] ? u : v);
} 
int Jump(int u, int l) { // 找到具体所在子树的根
	if (u == l) return 0; // 这里是考虑如果其中一个点就是 LCA 的特判。
	int res = 0; while (top[u] != top[l]) { res = top[u]; u = fa[top[u]]; }
	return (u == l ? res : hson[l]);
} } using SPLIT::build, SPLIT::LCA, SPLIT::Jump;
vector<pair<int, int> > qry[N]; int W[N], V[N], cnt[N]; // qry 就是把路径挂到 LCA 上，W 数组即文中 w 数组，V 数组即文中 v 数组，cnt 数组就是桶。
void DFS(int u, int f) {
	for (int v : G[u]) if (v != f) { DFS(v, u); W[u] += W[v]; V[u] += V[v]; }
	return ;
}
int main() {
	cin >> n;
	for (int i = 1, u, v; i < n; i ++) {
		cin >> u >> v; G[u].emplace_back(v); G[v].emplace_back(u);
	} build(1); cin >> m;
	for (int i = 1, u, v; i <= m; i ++) {
		cin >> u >> v; int l = LCA(u, v); int a = Jump(u, l), b = Jump(v, l); // 下面是树上差分
		V[u] ++; V[v] ++; V[(!a ? u : a)] --; V[(!b ? v : b)] --;
		qry[l].emplace_back(make_pair(a, b)); W[u] ++; W[v] ++; W[l] -= 2;
	} DFS(1, 0); LL Ans = 0; W[0] = 0; V[0] = 0;
	for (int i = 1; i <= n; i ++) if (qry[i].size()) {
		__gnu_pbds::gp_hash_table<LL, int> hsh; int atri = 0; // 这里的 atri 就表示 u_i=v_i 的 corner case 计数。
		for (auto [u, v] : qry[i]) {
			if (u == v) { ++ atri; continue; }
			cnt[u] ++; cnt[v] ++; 
			Ans += W[i] - V[u] - V[v];
			if (u > v) { swap(u, v); } hsh[1ll * u * n + v] ++; // 哈希表，但是实现的时候可以把点对压成一个整数。
		} Ans += 1ll * atri * (qry[i].size() - 1) - 1ll * (atri - 1) * atri / 2 + 1ll * atri * W[i]; // 特判
		LL cur = 0; 
		for (auto [u, v] : qry[i]) { 
			if (u > v) { swap(u, v); }
			if (u == v) continue;
			if (!u) cur += qry[i].size() - atri - cnt[v]; // 特判如果一个点就是其中的 LCA，那么单独计算。
			else cur += qry[i].size() - atri - cnt[u] - cnt[v] + hsh[1ll * u * n + v];
		} Ans += cur / 2;
		for (auto [u, v] : qry[i]) if (u != v) cnt[u] --, cnt[v] --;
	} cout << Ans;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑在 $\text{lca}(x_i,y_i)$ 计算这条路径和所有在它子树内的路径的方案数。记每条边的 $\text{lca}$ 为 $l_i$。

先考虑和另一条在他子树内且 $l_i\neq l_j$ 不同的路径 $j$ 在何时会有交点，不难发现当且仅当 $l_j$ 在 $x_i$ 到 $l_i$ 路径上或 $y_i$ 到 $l_i$ 的路径上且不能有其他交点。

考虑用线段树维护到目前节点位置，如果路径 $i$ 的一端在 $p$，符合要求的路径数。将所有路径 $j$ 在 $l_j$ 子树内全部加一。然后对于路径 $j$ 的两条下去的路径所在子树减一即可。

考虑 $l_i=l_j$ 的情况，沿用前面的想法，考虑容斥，将所有组合减去其中一条向下的链在下一个位置重合的方案，然后加上两条向下的链在下一个位置都重合的方案即可。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[300005];
vector<pair<int,int>> bel[300005];
int dep[300005],f[300005][20],ind[300005],outd[300005],cnt;
void dfs1(int now,int fa){
	dep[now]=dep[fa]+1;
	ind[now]=++cnt;
	f[now][0]=fa;
	for(int i=1;i<=19;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs1(v,now); 
	}
	outd[now]=cnt;
}
int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=19;i>=0;i--) if(dep[f[u][i]]>=dep[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=19;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int finds(int now,int anc){
	int len=dep[now]-dep[anc]-1;
	for(int i=19;i>=0;i--) if((1<<i)<=len) len-=(1<<i),now=f[now][i];
	return now;
}
struct sgt{
	int f[1200005],lzt[1200005];
	void pushdown(int i,int l,int r){
		f[i*2]+=(mid-l+1)*lzt[i];
		f[i*2+1]+=(r-mid)*lzt[i];
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=(r-l+1)*cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i,l,r);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg); 
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i,l,r);
		return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr); 
	}
}tree;
int ans=0,n;
int num[300005];
map<pair<int,int>,int> mp;
void dfs2(int now,int fa){
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs2(v,now);
	}
	for(auto v:bel[now]){
		if(v.first!=0) ans+=tree.qry(1,1,n,ind[v.first],ind[v.first]);
		if(v.second!=0) ans+=tree.qry(1,1,n,ind[v.second],ind[v.second]);
	}
//	int tmpp=0;
	for(auto v:bel[now]){
		tree.change(1,1,n,ind[now],outd[now],1);
		if(v.first!=0) tree.change(1,1,n,ind[finds(v.first,now)],outd[finds(v.first,now)],-1);
		if(v.second!=0) tree.change(1,1,n,ind[finds(v.second,now)],outd[finds(v.second,now)],-1);
//		if((v.first==0)&&(v.second==0)) tmpp++;
	}
	int tmp=(bel[now].size()-1)*bel[now].size()/2;
	for(auto v:bel[now]){
//		cout<<v.first<<" "<<v.second<<" ";
		if(v.first!=0) num[finds(v.first,now)]++;//,cout<<finds(v.first,now)<<" ";
		if(v.second!=0) num[finds(v.second,now)]++;//,cout<<finds(v.second,now)<<" ";
		if(v.first!=0&&v.second!=0){
			int X=finds(v.first,now),Y=finds(v.second,now);
			if(X>Y) swap(X,Y);
			mp[make_pair(X,Y)]++; 
		}
//		cout<<"\n";
	}
	for(auto v:bel[now]){
		if(v.first!=0) tmp-=num[finds(v.first,now)]*(num[finds(v.first,now)]-1)/2,num[finds(v.first,now)]=0;
		if(v.second!=0) tmp-=num[finds(v.second,now)]*(num[finds(v.second,now)]-1)/2,num[finds(v.second,now)]=0;
		if(v.first!=0&&v.second!=0){
			int X=finds(v.first,now),Y=finds(v.second,now);
			if(X>Y) swap(X,Y);
			tmp+=mp[make_pair(X,Y)]*(mp[make_pair(X,Y)]-1)/2;
			mp[make_pair(X,Y)]=0;
		}
	}
	ans+=tmp;
//	cout<<now<<" "<<ans<<" TAG\n";
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs1(1,0);
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		int l=lca(u,v);
		if(u!=l&&v!=l) bel[l].push_back(make_pair(u,v));
		else if(u!=l) bel[l].push_back(make_pair(u,0));
		else if(v!=l) bel[l].push_back(make_pair(v,0));
		else bel[l].push_back(make_pair(0,0));
	}
	dfs2(1,0);
	cout<<ans;
	return 0;
}

```

---

## 作者：shinkuu (赞：0)

简单题。

树上路径相交有个很经典的性质：如果 $(u_1,v_1),(u_2,v_2)$ 相交，则一定在 $\operatorname{lca}(u_1,v_1),\operatorname{lca}(u_2,v_2)$ 中更深的那个相交。所以只用看两条路径是否除了这个点没有其他交点即可。

考虑在 $u\to v$ 路径上 $\operatorname{lca}(u,v)$ 的前一个和后一个点分别为 $x,y$，简单容斥，则我们要计算的就是：设 $w=\operatorname{lca}(u,v)$，经过 $w$ 的路径有 $a$ 条，经过 $w,x$ 和 $w,y$ 的路径分别有 $b,c$ 条，经过 $w,x,y$ 的路径有 $d$ 条。则 $ans=a-b-c+d$。

其中 $a,b,c$ 树剖+BIT 维护，$d$ 开个 map 维护。

code：

```cpp
int n,m;
int fa[N],dep[N],siz[N],son[N];
int cur,dfn[N],rk[N],top[N];
map<ll,int> c;
int tot,head[N];
struct node{int to,nxt;}e[N<<1];
struct Node{int u,v,w;}d[N];
il void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1,siz[u]=1;
	go(i,u){
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int t){
	rk[dfn[u]=++cur]=u,top[u]=t;
	if(!son[u])return;
	dfs2(son[u],t);
	go(i,u){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
struct BIT{
	ll tr[N];
	#define lb(x) (x&(-x))
	il void upd(int x,int y){while(x<=n)tr[x]+=y,x+=lb(x);}
	il ll qry(int x){ll ret=0;while(x)ret+=tr[x],x-=lb(x);return ret;}
	il void update(int l,int r){
		if(l>r)return;
		upd(l,1);if(r<n)upd(r+1,-1);
	}
}T,R;
il int getLca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
il int getSon(int u,int v){
	if(u==v)return 0;
	int lst=0;
	while(top[u]!=top[v])lst=top[u],u=fa[top[u]];
	if(u==v)return lst;
	return rk[dfn[v]+1];
}
il void update(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.update(dfn[top[u]],dfn[u]);
		R.update(dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dfn[u]>dfn[v])swap(u,v);
	T.update(dfn[u],dfn[v]);
	R.update(dfn[u]+1,dfn[v]);
}
il bool cmp(Node x,Node y){return dep[x.w]<dep[y.w];}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs1(1,0),dfs2(1,1);
	scanf("%d",&m);
	rep(i,1,m){
		scanf("%d%d",&d[i].u,&d[i].v);
		d[i].w=getLca(d[i].u,d[i].v);
	}
	sort(d+1,d+m+1,cmp);
	ll ans=0;
	rep(i,1,m){
		int u=d[i].u,v=d[i].v,w=d[i].w;
		ans+=T.qry(dfn[w]);
		int x=getSon(u,w),y=getSon(v,w);
		if(x>y)swap(x,y);
		ans-=R.qry(dfn[x])+R.qry(dfn[y]);
		if(x)ans+=c[1ll*x*n+y];
		update(d[i].u,d[i].v);
		if(x)c[1ll*x*n+y]++;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

