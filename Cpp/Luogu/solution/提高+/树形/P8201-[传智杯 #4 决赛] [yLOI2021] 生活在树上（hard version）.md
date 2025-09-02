# [传智杯 #4 决赛] [yLOI2021] 生活在树上（hard version）

## 题目背景

**本题是 P8200 的较难版本，两道题目的解法略有不同。本题和 P8200 在题意上的区别在于本题给定树上的点权，而不是边权。**

小智生活在「传智国」，这是一个有 $n$ 个城市的国家，各个城市由 $n-1$ 条道路相连。

每个城市都有一个财富指数 $w_i$ ，我们定义，小智从城市 $a$ 走到城市 $b$ 的代价是 $\mathrm{dis}_{a, b} = \bigoplus \limits_{u \in \mathrm{path}\left(a, b\right)} w_u$，其中 $\bigoplus$ 表示**按位异或**（如果你不知道什么是**按位异或**，请参见题目下方的提示/说明），$\mathrm{path}\left(a,b\right)$ 表示 $a$ 到 $b$ 的简单路径上的点集（包括 $a$ 和 $b$）。也即 $\mathrm{dis}_{a, b}$ 表示将 $a$ 与 $b$ 的简单路径上所有点写作 $u_1, u_2, u_3, \dots$ 后，求 $w_{u_1} \bigoplus w_{u_2}\bigoplus w_{u_3} \dots$ 的结果。

有一天，小智获得了去参加传智杯的机会，他在前往比赛地的路上想到了一个问题，但他好像不会做，于是他把这个题告诉了你。聪明的同学，你可以帮帮他吗？

## 题目描述

小智说：「由于我们的国家只有 $n$ 个城市和 $n-1$ 条道路，那么我们的国家就相当于是一棵树。我在想，在我们的国家中，是否存在城市满足『到城市 $a$ 的代价和到城市 $b$ 的代价的异或等于 $k$』。好难哦，我想不出来，你能帮帮我吗？」

也就是说，给定城市 $a, b$ 和整数 $k$，请你计算是否存在城市 $t$ 满足 $\mathrm{dis}_{t, a} \bigoplus \mathrm{dis}_{t, b} = k$。

## 说明/提示

### 相关概念解释
「树」：树是一个有 $n$ 个结点和 $n-1$ 条边的无向简单连通图。

「按位异或」：按位异或是一个二元运算，步骤是将两个数的二进制位按位比较，相同为 $0$，不同为 $1$ 。例如：$3 \bigoplus 5 = (011)_2 \bigoplus (101)_2 = (110)_2 = 6$。
### 样例 1 解释
下图为传智国的地图。

$\forall t \in \{1, 2, 3, 4, 5\}$，都不可能有 $\mathrm{dis} _{t,1} \bigoplus \mathrm{dis}_{t, 2} = 4$，$\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 12$，于是输出 `No`；

而取 $t=4$，有 $\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 10$，于是输出 `Yes`。

![](https://cdn.luogu.com.cn/upload/image_hosting/d3phj9di.png)
### 数据规模与约定
对于所有测试点，保证 $1 < n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq w_i \leq 1\times 10^7$。

对于每次询问，保证 $1 \leq a,b \leq n$ 且 $a \neq b$，$0 \leq k \leq 1\times 10^7$。
### 提示
- 请注意常数因子对程序效率造成的影响。
- 对于两个 $x, y \leq 10^7$，$x \bigoplus y$ 可能大于 $10^7$，请特别注意这一点。

## 样例 #1

### 输入

```
5 3
2 6 8 1 5
1 2
1 3
2 4
2 5
1 2 4
2 3 12
2 3 10```

### 输出

```
nO
No
YeS```

## 样例 #2

### 输入

```
5 10
93 97 100 93 93
2 1
3 2
4 3
5 1
5 2 93
4 1 93
3 2 100
3 2 100
2 3 9999998
1 2 93
2 3 97
1 2 93
2 3 97
4 3 93```

### 输出

```
no
nO
yEs
yEs
No
yEs
yeS
YES
yES
yes```

# 题解

## 作者：一扶苏一 (赞：16)

题外话，比赛时大家好像都在树剖，没见到几个写差分的（（这题不会成了天天爱跑步 2.0 吧（

## F2. 生活在树上（hard version）

**题意**：给定一棵树，点数为 $n$，点有点权。定义树上两点间路径的权值是其简单路径上点权的异或和。有 $q$ 次询问，每次给定两个节点 $x, y$ 查询是否存在一个点 $u$，使 $u$ 到 $x$ 和 $u$ 到 $y$ 的路径的权值的异或为 $k$。

**关键词**：前缀和，构造，树上差分。

**参考难度**：绿。

**分析**：首先异或构成一个 Abel 群，所以如果一个点在 $u$ 到 $x$ 和 $y$ 的路径上都出现了，那么他对答案没有贡献。

考虑 $u$ 到 $x$ 的路径和 $u$ 到 $y$ 的路径总是先经过若干个相同的点，然后与 $(x, y)$ 所成的链有一个交点 $t$，接着在这个交点处分开，一个走向 $x$ 一个走向 $y$，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/x024zkpa.png)

图中红色路径是 $u$ 到 $x$ 的路径，蓝色路径是 $u$ 到 $y$ 的路径，二者在 $(u, t)$ 部分是重复的。不难验证，无论 $u$ 在哪个位置，都满足这个性质。

于是我们发现，$\mathrm{dis}_{u, x} \bigoplus \mathrm{dis}_{u, y}$ 的值可能是 $s_x \bigoplus s_y \bigoplus  w_a \bigoplus w_t$，$s_x$ 和 $s_y$ 表示 $x$，$y$ 到根路径的点权异或和，$t$ 是 $x$ 到 $y$ 的链上任何一个点，$a$ 是 $x$ 和 $y$ 的最近公共祖先。注意到 $a$ 在链上，但是 $w_a$ 在 $s_x$ 和 $s_y$ 中都被计算了一次，二者的异或没有了 $w_a$ 的贡献，因此要再异或一次把贡献加回来；此外考虑 $t$ 是两条路径上重复的点，因此对异或和没有贡献，需要异或一次将其贡献去掉。

于是问题就变成了 $s_x \bigoplus s_y \bigoplus  w_a \bigoplus w_t = k$ 是否成立。注意到 $x, y, a, k$ 都是定值，根据消去律，$w_t = k \bigoplus s_x \bigoplus s_y \bigoplus w_a$。于是问题转化成了：在 $x$ 到 $y$ 的链上是否存在一个 $t$，使得 $t$ 的权值是 $W= k \bigoplus s_x \bigoplus s_y \bigoplus w_a$。也即查询这条链上权值为 $W$ 的点的个数。这是一个经典的树上差分问题：我们只需要查询 $(x, a)$ 和 $(y, b)$ 两条链上其个数然后相加即可，其中 $b$ 是 $a$ 的「是 $y$ 的祖先的」孩子。我们只需要在 $x, y, a, fa(a)$ 四个点分别打上查询标记，查询这四个位置到根的路径上 $W$ 的权值个数，记为 $p$，则 $(x, y)$ 上 $W$ 权值个数即为 $p_x + p_y - p_a - p_{fa(a)}$。

统计 $p$ 只需要用树上差分的套路，离线询问，在树上打标记，最后进行一次 dfs，用一个全局桶维护当前节点到根的权值数量即可，详见代码。

时间复杂度为 $O(n \log n)$ 或 $O(n \alpha (n))$。其中 $\log n$ 或 $\alpha (n)$ 是求 LCA 的开销。因为本身就需要离线询问，std 使用的是 tarjan 求 LCA 的 $O(n \alpha (n))$ 的做法，使用倍增求 LCA 可能需要一定的常数优化，但是根据验题人程序，也可以通过本题。

(C++)

```cpp
#include <array>
#include <vector>
#include <iostream>

const int maxn = 1000005;
const int maxw = 10000007;

int n, q;
std::array<std::vector<int>, maxn> e;
std::array<int, maxn> a, b, lca, ufs, rnk, anc, kk, cnt, fa, k, ans;
std::array<bool, maxn> vis;
std::array<std::vector<std::pair<int, int> >, maxn> qry, QQ;
std::array<std::pair<int, int>, maxn> Q;
std::array<int, maxw> bk;

void dfs2(const int u);
void dfs(const int u, const int f);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    rnk[ufs[i] = anc[i] = i] = 1;
  }
  for (int u, v, i = 1; i < n; ++i) {
    std::cin >> u >> v;
    e[u].push_back(v); e[v].push_back(u);
  }
  for (int i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v >> kk[i];
    qry[u].push_back(std::make_pair(v, i));
    qry[v].push_back(std::make_pair(u, i));
    Q[i] = std::make_pair(u, v);
  }
  dfs(1, 0);
  for (int i = 1; i <= q; ++i) if ((k[i] = b[Q[i].first] ^ b[Q[i].second] ^ a[lca[i]] ^ kk[i]) < maxw) {
    QQ[Q[i].first].push_back(std::make_pair(i, 1));
    QQ[Q[i].second].push_back(std::make_pair(i, 1));
    QQ[lca[i]].push_back(std::make_pair(i, -1));
    QQ[fa[lca[i]]].push_back(std::make_pair(i, -1));
  }
  dfs2(1);
  std::array<std::string, 2> prt{"nO\n", "yEs\n"};
  for (int i = 1; i <= q; ++i) std::cout << prt[ans[i] > 0];
}

int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }

void dfs(const int u, const int f) {
  b[u] = a[u] ^ b[f];
  fa[u] = f;
  for (auto v : e[u]) if (v != f) {
    dfs(v, u);
    int x = find(u), y = find(v);
    if (rnk[x] > rnk[y]) std::swap(x, y);
    anc[ufs[x] = y] = u;
    if (rnk[x] == rnk[y]) ++rnk[y];
  }
  for (auto [v, i] : qry[u]) if (vis[v]) {
    lca[i] = anc[find(v)];
  }
   vis[u] = true;
}

void dfs2(const int u) {	// 这里是树上差分对应求结果的 dfs 函数
  ++bk[a[u]];
  for (auto [i, w] : QQ[u]) {
    ans[i] += w * bk[k[i]];
  }
  for (auto v : e[u]) if (v != fa[u]) {
    dfs2(v);
  }
  --bk[a[u]];
}
```

---

## 作者：stntn (赞：7)

## **莫队**

### 题目描述

[link](https://www.luogu.com.cn/problem/P8201)

### 简要题意

给你一颗树，节点有点权，若干次询问，求是否存在一点 $t$，满足两点到 $t$ 的路径上的点权异或和等于 $k$。

即 $dis_{t,a}\oplus dis_{t,b} = k$

### 树上莫队

简单观察即可发现：

- 若点 $t$ 位于 $a$，$b$ 两点任意一点 $p$ 的子树中，有 $dis_{t,a} \oplus dis_{t,b} = dis_{t,a} \oplus dis_{t,b} \oplus w_p$

- 若点 $t$ 位于 $lca_{a,b}$ 之上，则有 $dis_{t,a} \oplus dis_{t,b} = dis_{t,a} \oplus dis_{t,b} \oplus w_{lca}$。

- 若点 $t$ 位于 $a$，$b$ 两点路径上点 $p$ 上或点 $p$ 的子树中，则 $dis_{t,a} \oplus dis_{t,b} = dis_{t,a} \oplus dis_{t,b} \oplus w_p$

可以发现，**无论 $t$ 处于何处，$dis_{t,a}\oplus dis_{t,b}$ 的值只与 $a$，$b$ 路径上的点有关。** 我们令该点为 $q$。

易得 $dis_{t,a} \oplus dis_{t,b} = k \Leftrightarrow  k \oplus dis_{a,b} = w_q$

于是问题就变成了，**求 $a$，$b$ 路径上是否有一点 $q$ 满足 $w_q= k \oplus dis_{a,b} $。**

因为 $w_i \le  10^7$， 树上莫队可做。

### CODE

```cpp
#include<bits/stdc++.h>
#define N 1000010
#define re register
using namespace std;
template <typename T> inline void read(T &a)
{
	T x=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	a=x*w;
}
int n,m,head[N],cc,val[N],mcc;
struct EDGE{int v,nxt;}e[N<<1];
inline void add_edge(int u,int v)
{
	e[++cc].v=v;e[cc].nxt=head[u];head[u]=cc;
	e[++cc].v=u;e[cc].nxt=head[v];head[v]=cc;
}
int fa[N],dep[N],dis[N],top[N],son[N],siz[N],dfn[N<<1],dfcc,l[N],r[N];
struct QUERY{int l,r,k,id,lca;}q[N];
inline void dfs1(int u)
{
	siz[u]=1;dep[u]=dep[fa[u]]+1;dis[u]=dis[fa[u]]^val[u];dfn[++dfcc]=u;l[u]=dfcc;
	for(re int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;if(v==fa[u]) continue;
		fa[v]=u;dfs1(v);siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
	}
	dfn[++dfcc]=u;r[u]=dfcc;
}
inline void dfs2(int u,int tp)
{
	top[u]=tp;if(son[u]) dfs2(son[u],tp);
	for(re int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline int get_lca(int a,int b)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]]) a=fa[top[a]];
		else b=fa[top[b]];
	}
	return dep[a]<dep[b] ? a:b;
}
int bnum,blen,belong[N],nl=1,nr=0,cnt[100000010];
bool ans[N],vis[N];
inline bool cmp(QUERY x,QUERY y){return belong[x.l] ^ belong[y.l] ? belong[x.l] < belong[y.l] : ( (belong[x.l]&1) ? x.r<y.r : x.r>y.r);}
inline void add(int x)
{
	if(vis[dfn[x]]) cnt[val[dfn[x]]]--;
	else cnt[val[dfn[x]]]++;
	vis[dfn[x]]^=1;
}
signed main()
{
	read(n);read(m);
	for(re int i=1;i<=n;++i) read(val[i]);
	for(re int i=1,u,v;i<n;++i){read(u),read(v),add_edge(u,v);}
	dfs1(1);dfs2(1,1);
	blen=sqrt(dfcc);
	for(re int i=1;i<=dfcc;++i) belong[i]=(i-1)/blen+1;
	for(re int i=1,u,v,k,lca;i<=m;++i)
	{
		read(u);read(v);read(k);
		if(l[u]>l[v]) swap(u,v);
		lca=get_lca(u,v);
		k=k^dis[u]^dis[v]^val[lca];
		q[++mcc].l= lca==u ? l[u]:r[u];
		q[mcc].r=l[v];q[mcc].k=k;
		q[mcc].id=i;q[mcc].lca=lca;
		if(val[lca]==q[mcc].k) ans[i]=1,mcc--;
	}
	sort(q+1,q+1+mcc,cmp);
	for(re int i=1;i<=mcc;++i)
	{
		while(nl<q[i].l) add(nl++);
		while(nl>q[i].l) add(--nl);
		while(nr<q[i].r) add(++nr);
		while(nr>q[i].r) add(nr--);
		ans[q[i].id]=cnt[q[i].k];
	}
	for(re int i=1;i<=m;++i) printf(ans[i] ? "YES\n":"NO\n");
	return 0;
}
```




---

## 作者：Pengzt (赞：6)

[P8201](https://www.luogu.com.cn/problem/P8201)

简单题。

题中求的是 $dis_{a, t} \oplus dis_{t, b} = k$ 是否存在，显然不好直接维护，考虑转化。

令 $dist = dis_{a, t} \oplus dis_{t, b}$，$val = \bigoplus\limits_{x\in \text{path}(a, b)} w_x$。

如果 $t$ 在 $\text{path}(a, b)$ 上，则 $dist = val \oplus a_t$。
如果 $t$ 不在上面，其实就是从 $a$ 到 $b$ 的简单路径上的某点走了一个来回，显然这里的 $dist$ 值所构成的集合一定被前一种情况包含。

此时就变为了判断是否存在点 $t$，满足在 $a$ 到 $b$ 的路径上，且 $val \oplus w_t = k$。即找路径上是否存在某点。

由于是查询无修改的路径信息，考虑对每个结点建一棵权值线段树，维护的时该点到根节点的路径上每个点的权值出现的次数。显然此时可以直接动态开点。由于空间比较紧，但时间较充裕，可以先离散化后再进行操作。

[评测记录](https://www.luogu.com.cn/record/113964534)

---

## 作者：Lamorak (赞：5)

[题面](https://www.luogu.com.cn/problem/P8201)

这道题就是询问把路径上某一点去掉的异或值可不可以是 $k$，因为随意选一个点 $x$ ，它到 $u,v$ 的路径与路径 $u\rightarrow v$ 必有且只有一个交点（建议动手画一画）。

然后题上的 $dis_{t,a}⨁dis_{t,b}$ 就是把路径 $u\rightarrow v$ 上去掉一点的异或值。

可以令 $dis_{u,v}$ 表示 $u$ 到 $v$ 的路径上所有点的异或值，$w_i$ 
表示 $i$ 点的值。若在路径上找到点 $p$ 使得 $dis_{u,v}~\text{xor}~w_p=k$ ，即 $w_p=dis_{u,v}~\text{xor}~k$，那么答案显然是肯定的。

则考虑树上主席树，把点权离散化，在线求出 $u$ 和 $v$ 路径上点 $p$ 的个数。

怎么求？可以令 $lca_{u,v}$ 表示 $u$ 和 $v$ 的最近公共祖先 ~~可以用树剖，但我觉得太长了就打倍增~~，$f_{i}$ 为 1 到 $i$ 路径上的异或值。$dis_{u,v}=f_u~\text{xor}~f_v~\text{xor}~w_{lca}$，然后就是板子了。

[树上主席树模板](https://www.luogu.com.cn/problem/P2633)

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+500;

struct node
{
	int u,v,nxt;
}e[N];

struct nodee
{
	int l,r,tl,tr,v;
}t[N<<3];

int n,m,f[N],head[N],cnt,w[N],fa[N][25],d[N],tot,cc,rt[N];
map<int,int>mp;

void add(int u,int v)
{
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void ADD(int a,int b,int x)
{
	t[a].l=t[b].l;t[a].r=t[b].r;
	if(t[b].tl==0)
	{
		t[a].v=t[b].v+1;
		return;
	}
	if(x>(t[b].l+t[b].r)/2)//rightson
	{
		t[a].tl=t[b].tl;
		t[a].tr=++cc;
		ADD(t[a].tr,t[b].tr,x);
	}
	else//leftson
	{
		t[a].tr=t[b].tr;
		t[a].tl=++cc;
		ADD(t[a].tl,t[b].tl,x);
	}
	t[a].v=t[t[a].tl].v+t[t[a].tr].v;
	return;
}

void dfs(int x,int ff)
{
	f[x]=f[ff]^w[x];fa[x][0]=ff;d[x]=d[ff]+1;
	rt[x]=++cc,ADD(rt[x],rt[ff],mp[w[x]]);
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff)continue;
		dfs(v,x);
	}
}

int LCA(int u,int v)
{
	if(d[u]<d[v])swap(u,v);
	for(int i=20;i>=0;i--)
	if(d[u]-(1<<i)>=d[v])
	u=fa[u][i];
	if(u==v)return u;
	for(int i=20;i>=0;i--)
	if(fa[u][i]!=fa[v][i])
	u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

int get(int a,int b,int x)
{
	if(t[a].tl==0)return t[b].v-t[a].v;
	if(x<=(t[a].l+t[a].r)/2)return get(t[a].tl,t[b].tl,x);//lson
	return get(t[a].tr,t[b].tr,x);//rson
}

int check(int u,int v,int k,int lca)
{
	int l=f[u]^f[v]^w[lca];
	if(!mp[(k^l)])return 0;
	int x=mp[(k^l)];
	if(get(rt[fa[lca][0]],rt[u],x)>0||get(rt[fa[lca][0]],rt[v],x)>0)return 1;
	return 0;
	
}

void build(int id,int l,int r)
{
	t[id].l=l,t[id].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	t[id].tl=++cc;build(t[id].tl,l,mid);
	t[id].tr=++cc;build(t[id].tr,mid+1,r);
}

main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		if(!mp[w[i]])mp[w[i]]=++tot;
	}
	rt[0]=++cc;
	build(rt[0],1,tot);
	int u,v;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
	for(int j=1;j<=n;j++)
	fa[j][i]=fa[fa[j][i-1]][i-1];
	int k,lca;
	while(m--)
	{
		cin>>u>>v>>k;
		lca=LCA(u,v);
		if(check(u,v,k,lca))puts("YES");
		else puts("NO");
	}
}
```
码风不好，勿喷。~~跑的好慢~~

~~把一道绿做成了蓝，我好菜~~

---

## 作者：Troubadour (赞：5)

这场比赛我用小号打的，在还剩 $40$ 分钟的时候分析出本题做法，还剩 $20$ 分钟的时候成功 RE，然后经历漫长的调试与多次提交，终于在还有两分钟的时候通过本题。好家伙，真有打 CF 那感觉了。

### 思路：

我们注意到，设所选的这个点为 $k$，记 $d_{x,y}$ 表示从 $x$ 到 $y$ 这条路径的异或和，那么我们就要找到一个 $k$ 使得 $d_{x,k}\operatorname{xor}d_{y,k}=w$。不难发现，在 $(x,y)$ 这条路径上有且仅有一个点的权值被算了两遍消失了，而根据题意，这个点权值应该是 $d_{x,y}\operatorname{xor}w$。

所以，题意转化为：给定 $x,y,w$，判断 $(x,y)$ 这条路径上是否有一个点 $k$，使得 $a_k=d_{x,y}\operatorname{xor}w$。

为行文方便，下文中用 $w$ 代替 $d_{x,y}\operatorname{xor}w$。

具体怎么实现呢，我们可以考虑把询问离线下来，对于相同的 $w$ 进行统一处理。

考虑采用树剖+线段树，对于每一个权值为 $w$ 的点，在线段树上所对应的位置 $+1$，每次查询只需要查 $(x,y)$ 这条链上的权值是否 $\ge 0$ 即可。

~~于是呢，我成功的把一道绿题做成了蓝题。~~

哦对了，这题不需要开 long long。

### Code:
```cpp
/*
	Copyright (C) 2022  Troubadour_Ggmz

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include<bits/stdc++.h>
struct istream {  //快读板子
	inline char gc() {
		static const int IN_LEN = 1 << 18 | 1;
		static char buf[IN_LEN], *s, *t;
		return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
	}

	template <typename _Tp> inline istream & operator >> (_Tp&x) {
		static char ch, sgn; ch = gc(), sgn = 0;
		for (;!isdigit(ch);ch = gc()) { if (ch == -1)return *this;sgn |= ch == '-'; }
		for (x = 0;isdigit(ch);ch = gc())x = x * 10 + (ch^'0');
		sgn && (x = -x); return *this;
	}
} cin;
namespace GGMZ
{
	const int N = 5e5 + 5;
	struct edge
	{
		int to, nxt;
	}e[N << 1];
	int head[N], cnt;
	void add(int u, int v)
	{
		cnt++;
		e[cnt].to = v;
		e[cnt].nxt = head[u];
		head[u] = cnt;
	}
	int top[N], size[N], fa[N], son[N], tot, a[N], dis[N], dep[N], dfn[N], nfd[N];
	void dfs1(int u, int f)
	{
		dep[u] = dep[f] + 1;
		size[u] = 1;
		fa[u] = f;
		dis[u] = dis[f] ^ a[u];
		for (int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if (v == f)continue;
			dfs1(v, u);
			size[u] += size[v];
			if (size[son[u]] < size[v])son[u] = v;
		}
	}
	void dfs2(int u, int tp)
	{
		top[u] = tp;
		dfn[u] = ++tot;
		nfd[tot] = u;
		if (son[u])dfs2(son[u], tp);
		for (int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if (v == fa[u] || v == son[u])continue;
			dfs2(v, v);
		}
	}
	std::map<int, std::vector<int>>mp;
	struct seg
	{
		int l, r, val, clear;
	}f[N << 2];
	void update(int p)
	{
		f[p].val = f[p << 1].val + f[p << 1 | 1].val;
	}
	void brush(int p)
	{
		f[p].val = 0;
		f[p].clear = 1;
	}
	void push_down(int p)
	{
		if (f[p].clear)
		{
			brush(p << 1);
			brush(p << 1 | 1);
			f[p].clear = 0;
		}
	}
	void build(int p, int l, int r)
	{
		f[p].l = l, f[p].r = r;
		if (l == r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
	}
	void modify(int p, int x)
	{
		if (f[p].l == f[p].r)
		{
			f[p].val = 1;
			return;
		}
		push_down(p);
		int mid = (f[p].l + f[p].r) >> 1;
		if (mid >= x)modify(p << 1, x);
		if (mid < x) modify(p << 1 | 1, x);
		update(p);
	}
	int query(int p, int l, int r)
	{
		if (l <= f[p].l&&f[p].r <= r)
		{
			return f[p].val;
		}
		push_down(p);
		int res = 0, mid = (f[p].l + f[p].r) >> 1;
		if (mid >= l)res += query(p << 1, l, r);
		if (mid < r)res += query(p << 1 | 1, l, r);
		return res;
	}
	inline int lca(int x, int y)
	{
		while (top[x] != top[y])
		{
			if (dep[top[x]] < dep[top[y]])std::swap(x, y);
			x = fa[top[x]];
		}
		if (dep[x] > dep[y])std::swap(x, y);
		return x;
	}
	int query(int x, int y)
	{
		int res = 0;
		while (top[x] != top[y])
		{
			if (dep[top[x]] < dep[top[y]])std::swap(x, y);
			res += query(1, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		if (dep[x] > dep[y])std::swap(x, y);
		res += query(1, dfn[x], dfn[y]);
		return res;
	}
	int n, m;
	struct query_
	{
		int x, y, w, id, skipped;
		bool operator<(const query_ a)const
		{
			return w < a.w;
		}
	}q[N];
	bool vis[10000005];
	std::string ans[N];
	void work()
	{
		cin >> n >> m;
		for (int i = 1;i <= n;i++)
		{
			cin >> a[i];
		}
		for (int i = 1;i < n;i++)
		{
			int u, v;
			cin >> u >> v;
			add(u, v);
			add(v, u);
		}
		dfs1(1, 0);
		dfs2(1, 1);
		build(1, 1, n);
		for (int i = 1;i <= m;i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			int p = dis[u] ^ dis[v] ^ a[lca(u, v)];
			q[i].x = u, q[i].y = v;
			q[i].w = w ^ p;
			q[i].id = i;
			if (q[i].w > 10000000)
			{
				ans[i] = "NO";
				q[i].skipped = 1;
				continue;
			}
			vis[w^p] = 1;
		}
		for (int i = 1;i <= n;i++)
		{
			if (vis[a[i]])
			{
				mp[a[i]].push_back(i);
			}
		}
		std::sort(q + 1, q + 1 + m);
		q[0].w = -1;
		for (int i = 1;i <= m;i++)
		{
			if (q[i].skipped)continue;
			if (q[i].w != q[i - 1].w)
			{
				brush(1);
				for (int a : mp[q[i].w])
				{
					modify(1, dfn[a]);
				}
			}
			if (query(q[i].x, q[i].y))
			{
				ans[q[i].id] = "YES";
			}
			else
			{
				ans[q[i].id] = "NO";
			}
		}
		for (int i = 1;i <= m;i++)
		{
			puts(ans[i].c_str());
		}
	}
}
int main()
{
	return GGMZ::work(), 0;
}
```

---

## 作者：Claysonleet (赞：4)

- **前言** ： 生活在树上——始终热爱大地——升上天空。 


- **题目** : [生活在树上（hard version)](https://www.luogu.com.cn/problem/P8201)

- **大致题意** ：
	
   给出一颗 $n$ 个节点的树， 每个点 $u$ 有权值 $w_u$ , 有 $m$ 个询问， 求两个节点 $u, v$ 之间的路径上是否有一个点 $t$ 满足所有 路径 $(u, t)$, $(v, t)$ 所经过的所有结点权值异或和为 $k$ 。
   
   其中 $n \leq 10^5, m \leq10^5,w_i \leq10^7$。
   
- **思路** ：
	
	考虑记录 $dist_u$ 为根节点到 $u$ 的结点权值异或和， 然后可以套路地转化为求路径 $(u,v)$ 上有没有点 $t$ 其权值为 $k \oplus dist_u \oplus dist_v \oplus w_{lca(u, v)} = w_t$ 。
   
	然后我们发现路径也是可以树上差分， 拆出来 $u, v, lca(u, v), fa_{lca(u, v)}$ 到根节点的路径， 然后开一个桶去计数即可， 结合倍增时间复杂度 $O(n \log_2 n)$ 其时间复杂度瓶颈在于求最近公共祖先。
  
- [**代码**](https://www.luogu.com.cn/paste/wr8dyuct) 

---

## 作者：npqenqpve (赞：3)

### 题意:

给定一棵树，定义 $d(u,v)$ 为 $u$ 和 $v$ 路径上所有点权的异或，多组询问，给定 $u,v,k$，问是否存在 $x$ 使得 $d(u,x) \bigoplus d(x,v)=k$。

### 思路：

观察性质发现，如果存在 $x$ 不在 $u,v$ 路径上满足条件，那么 $u,x$ 路径和 $v,x$ 路径的第一个交点必然也满足条件，因为第一个交点往后必然一直重合，所以都能够抵消。还可以发现，这个交点必然在 $u,v$ 路径上，想一想，为什么。

因此，问题等价于在 $u,v$ 路径上是否存在 $x$ 使得 $d(u,x) \bigoplus d(x,v)=k$，由于 $d(u,x) \bigoplus d(x,v)=d(u,v)\bigoplus w_x$，转化为在 $u,v$ 路径上是否存在 $x$ 使得 $d(u,v)\bigoplus w_x=k$，左右同时异或 $d(u,v)$ 得到 $w_x=d(u,v)\bigoplus k$，由于右式是个常数，设为 $y$，最终转化为判断一条路径上是否存在点权为 $y$ 的点。

与其维护是否存在，不如直接维护个数，定义 $f(u,v,w)$ 表示 $u,v$ 路径上 $x$ 的出现次数。

由于出现次数具有可减性，所以 $f(u,v,w)=f(u,1,w)+f(v,1,w)-f(lca(u,v),1,w)-f(father_{lca(u,v)},1,w)$，把 $f(u,v,w)$ 这一个询问拆成四个询问处理，转化为任意 $u,w$ 求 $f(u,1,w)$。

这很明显是个数据结构问题，下面给出两种做法：

1. 考虑主席树，由于加入 $x$ 这个点相当于是在其父亲的版本上加入有关 $w_x$ 的信息，那么可以在合理的时间内建出每个点的主席树，直接求解即可，代码难度稍大。
2. 考虑离线下来，全局桶维护，离开这个点时删除这个点在桶中的贡献，那么对于每一个点都能得到一个维护它到根路径信息的桶，但是这个点的顺序是 dfn 序，对询问的点并不连续，所以将所有拆开的询问按 dfn 排序，那么可以得到答案的总是询问的一个前缀，单指针扫一遍即可，实现细节比较多。

### 代码：

给出第二种做法的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,id,dfn[(int)(5e5+10)],w[(int)(5e5+10)],f[35][(int)(5e5+10)];
int res[(int)(5e5+10)],dep[(int)(5e5+10)],p[(int)(5e5+10)],d[(int)(5e5+10)];
vector<int>edge[(int)(5e5+10)];
void dfs(int u,int fa)
{
	dfn[u]=++id;f[0][u]=fa;
	dep[u]=dep[fa]+1;p[u]^=p[fa];
	for(int i=1;i<=20;i++)
	{
		f[i][u]=f[i-1][f[i-1][u]];
	}
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
    {
        x=f[d[dep[x]-dep[y]]-1][x];
    }
    if(x==y) return x;
    for(int i=d[dep[x]]-1;i>=0;i--)
    {
        if(f[i][x]!=f[i][y]) x=f[i][x],y=f[i][y];
    }
    return f[0][x];
}

struct node
{
	int id,type,u,val,dfn,from,ans;
}a[(int)(2e6+10)],b[(int)(2e6+10)];
bool cmp(node a,node b)
{
	return a.dfn<b.dfn;
}
map<int,int>mp;
int now=1,top=0;
void dfs1(int u,int fa)
{
	mp[w[u]]++;
	while(a[now].u==u&&now<=top) 
	{
		a[now].ans=mp[a[now].val];
		now++;
	}
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		dfs1(v,u);
	}
	mp[w[u]]--;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld",&w[i]),p[i]=w[i];
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%lld %lld",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
    {
        d[i]=d[i-1]+(1<<d[i-1]==i);
    }
	dfs(1,0);
	for(int i=1;i<=m;i++)
	{
		int u,v,k;scanf("%lld %lld %lld",&u,&v,&k);
		int t=lca(u,v);
		if(t==u||t==v)
		{
			if(v==t)
			{
				a[++top]=(node){top,1,u,p[u]^p[f[0][t]]^k,dfn[u],i,0};
				if(t!=1) a[++top]=(node){top,-1,f[0][t],p[u]^p[f[0][t]]^k,dfn[f[0][t]],i,0};
			}
			else
			{
				a[++top]=(node){top,1,v,p[v]^p[f[0][t]]^k,dfn[v],i,0};
				if(t!=1) a[++top]=(node){top,-1,f[0][t],p[v]^p[f[0][t]]^k,dfn[f[0][t]],i,0};
			}
		}
		else
		{
			a[++top]=(node){top,1,u,p[u]^p[v]^w[t]^k,dfn[u],i,0};
			a[++top]=(node){top,1,v,p[u]^p[v]^w[t]^k,dfn[v],i,0};
			a[++top]=(node){top,-1,t,p[u]^p[v]^w[t]^k,dfn[t],i,0};
			if(t!=1) a[++top]=(node){top,-1,f[0][t],p[u]^p[v]^w[t]^k,dfn[f[0][t]],i,0};
		}
	}
	sort(a+1,a+1+top,cmp);
	dfs1(1,0);
	for(int i=1;i<=top;i++)
	{
		// cout<<a[i].u<<"\n";
		b[a[i].id]=a[i];
	}
	for(int i=1;i<=top;i++)
	{
		res[b[i].from]+=b[i].type*b[i].ans;
	}
	for(int i=1;i<=m;i++)
	{
		// assert(res[i]>=0);
		if(res[i]) puts("Yes");
		else puts("No");
	}
	system("pause > null");
}
```



---

## 作者：zzxLLL (赞：3)

upd on 2023.8.3

树剖+动态开点线段树做法。

分两种情况讨论：

1. $t$ 在路径 $(u, v)$ 上。

显然 $dis_{u, t} \bigotimes dis_{t, v} = dis_{u, v} \bigotimes w_t$。

2. $t$ 不在路径 $(u, v)$ 上。

因为是一棵树所以 $(u, v), (u, t), (v, t)$ 三条路径交于一点 $s$，那么 $dis_{u, t} \bigotimes dis_{t, v} = dis_{u, v} \bigotimes w_s$。

显然 $s$ 在 $(u, v)$ 上，其实和第一种情况相同，所以直接在 $(u, v)$ 上找点 $t$ 即可。

---

问题化为：$(u, v)$ 上是否存在 $t$，使得 $dis_{u, v} \bigotimes w_t = k$，其中 $k$ 是给出的，$dis_{u, v}$ 是容易求得的，所以移项(?)得 $w_t = k \bigotimes dis_{u, v}$，也就是询问路径 $(u, v)$ 上是否存在权值为 $k \bigotimes dis_{u, v}$ 的点。

注意到值域~~仅~~有 $10^7$ 故开 $10^7$ 颗线段树，树链剖分时将每个节点 $u$ 加入第 $w_u$ 颗线段树内。查询直接查路径 $(u, v)$ 上第 $k \bigotimes dis_{u, v}$ 颗线段树的区间和即可。
 
 ```cpp
 #include<cstdio>
#include<cstring>
const int M=1e7+10,N=5e5+10;

void swap(int &p,int &q){
	int t=p;p=q;q=t;
}

struct Edge{
	int to,next;
}edge[N<<1];
int head[N],cnte;
void add(int u,int v){
	edge[++cnte].to=v;
	edge[cnte].next=head[u];
	head[u]=cnte;
}

int son[N],fa[N],size[N],dep[N];
void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1;
	size[u]=1;
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v!=f){
			dfs1(v,u);
			size[u]+=size[v];
			if(size[v]>size[son[u]]) son[u]=v;
		}
	}
}
int top[N],id[N],rev[N],cntp;
void dfs2(int u,int t){
	top[u]=t;
	id[u]=++cntp,rev[cntp]=u;
	if(!son[u]) return;
	dfs2(son[u],t);
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
}

namespace SegmentTree{
	struct Tree{
		int lc,rc,val;
	}tr[M];
	int rt[M],cntt;
	void pushup(int p){
		tr[p].val=tr[tr[p].lc].val+tr[tr[p].rc].val;
	}
	void update(int &p,int l,int r,int pos,int val){
		if(!p) p=++cntt;
		if(l==pos&&r==pos){
			tr[p].val=val;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) update(tr[p].lc,l,mid,pos,val);
		if(pos>mid)  update(tr[p].rc,mid+1,r,pos,val);
		pushup(p);
		
		if(!tr[p].val) p=0;
	}
	int query(int p,int L,int R,int l,int r){
		if(!p) return 0;
		if(L<=l&&r<=R) return tr[p].val;
		int mid=(l+r)>>1,ans=0;
		if(L<=mid) ans+=query(tr[p].lc,L,R,l,mid);
		if(R>mid)  ans+=query(tr[p].rc,L,R,mid+1,r);
		return ans;
	}
}
using namespace SegmentTree;

int n,m,w[M];
int dis[N];
void dfs(int u,int f){
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v!=f){
			dis[v]=dis[u]^w[v];
			dfs(v,u);
		}
	}
}

int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) return v;
	else return u;
}

bool query_path(int u,int v,int val){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		if(query(rt[val],id[top[u]],id[u],1,n)) return true;
		u=fa[top[u]];
	}
	if(id[u]>id[v]) swap(u,v);
	if(query(rt[val],id[u],id[v],1,n)) return true;
	else return false;
}

int main(){
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0),dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++) update(rt[w[i]],1,n,id[i],1);
	
	while(m--){
		int a,b,k;
		scanf("%d%d%d",&a,&b,&k);
		int lca=LCA(a,b);
		int res=dis[a]^dis[b]^w[lca]^k;
		if(res>1e7){
			printf("No\n");
			continue;
		}
		if(query_path(a,b,res)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```


---

## 作者：Dusker (赞：2)

这边是验题人的 $\mathcal{O}(n \log n)$ 的倍增 LCA 做法，造数据的时候只记得卡暴力了，于是有了几组链的数据，并且有 $\dfrac 78$ 的查询均为 $1\sim n$，结果忘了 $\mathcal{O}(n\log^2n)$ 的树剖，结果现在看起来没卡树剖是正确的（？

题意转化和式子转化此处略去。

小声说一下链套菊花是可以卡树剖的 如果有人感兴趣的话可以找我或者@一扶苏一提供 hack 数据（

```cpp
#include<bits/stdc++.h>
#define ioclear std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define endl '\n'

const int mmax = 5e5 + 10;
const int maxw = 1e7 + 10;
const int inf = 1e7;
using i64 = unsigned long long;

int n, m, u[mmax], v[mmax], zx[mmax][30], dep[mmax], fl[mmax];
i64 a[mmax], Xor[mmax], k[mmax];
std::vector<int> edge[mmax];
std::vector<int> qry[mmax];
std::unordered_map<int, int> tong, Ans[mmax];

void dfs1(int cur, int fa)
{
	Xor[cur] = Xor[fa] ^ a[cur];
	dep[cur] = dep[fa] + 1;
	zx[cur][0] = fa;
	for(int i = 1;(1 << i) <= dep[cur];i++)
		zx[cur][i] = zx[zx[cur][i-1]][i-1];
	for(auto v : edge[cur])
		if(v != fa)
			dfs1(v, cur);
	return;
}

int lca(int x, int y)
{
	if(dep[x] < dep[y]) std::swap(x, y);
	for(int i = 19;i >= 0;i--)
		if(dep[x] - (1 << i) >= dep[y]) x = zx[x][i];
	if(x == y) return x;
	for(int i = 19;i >= 0;i--)
		if(zx[x][i] != zx[y][i]) x = zx[x][i], y = zx[y][i];
	return zx[x][0];
}

void dfs2(int cur, int fa)
{
	tong[a[cur]]++;
	for(auto v : qry[cur])
		Ans[cur][v] = tong[v];
	for(auto v : edge[cur])
		if(v != fa)
			dfs2(v, cur);
	tong[a[cur]]--;
	return;
}

int main()
{
	ioclear;
	std::cin >> n >> m;
	for(int i = 1;i <= n;i++)
		std::cin >> a[i];
	for(int i = 1;i < n;i++)
	{
		int x, y;
		std::cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs1(1, 0);
	for(int i = 1;i <= m;i++)
	{
		std::cin >> u[i] >> v[i] >> k[i];
		fl[i] = lca(u[i], v[i]);
		i64 t = k[i] ^ Xor[u[i]] ^ Xor[v[i]] ^ a[fl[i]];
		if(t > inf) continue;
		qry[u[i]].push_back(t);
		qry[v[i]].push_back(t);
		qry[fl[i]].push_back(t);
		qry[zx[fl[i]][0]].push_back(t);
	}
	dfs2(1, 0);
	for(int i = 1;i <= m;i++)
	{
		i64 t = k[i] ^ Xor[u[i]] ^ Xor[v[i]] ^ a[fl[i]];
		if(Ans[u[i]][t] + Ans[v[i]][t] - Ans[fl[i]][t] - Ans[zx[fl[i]][0]][t])
			puts("Yes");
		else
			puts("No");
	}
}
```


---

## 作者：青鸟_Blue_Bird (赞：1)

这是一篇大量利用 STL 的题解。

## 1、题意转化

原题说了非常多的路径费用定义，不妨直接画图来研究一下：

![666](https://cdn.luogu.com.cn/upload/image_hosting/ojhuv5aw.png)

手摸一下可以发现，对于上图中 $t_1$、$t_2$、$t_3$、$t_4$四个点，所谓的 $dis_{t,a}$ 与 $dis_{t,b}$ 的异或值，不正是在 $a$ 到 $b$ 的路径上的挖掉一个点后的所有点权的总异或和吗？以 $t_1$ 为例子，其到 $a$ 与 $b$ 的最近公共祖先 $t_4$ 的这段路，在总答案的异或和中，其实是被异或了两次，即消去了。（不了解异或性质的可自行百度）。

那么，原问题其实可以转化为：**询问树上的一对点，将其简单路径上挖去一个点（包括端点）的值，问是否可以使其总异或和为 $k$。**

如果一个个暴力删除路径上的点，显然时间复杂度是不可能过得去的。正难则反，不妨如此考虑：路径总异或和 $tot$ 和目标 $k$ 其实是确定的，因此我们可以求出目标删除值为 $d = tot ⨁ k$。

现在，问题就转化了为**求一段路径上是否有权值为 $d$ 的点。**

## 2、实现

对于路径总异或和，我们可以使用树链剖分与前缀和（或线段树）解决。如何查询是否存在权值 $d$ 成为主要问题。

不妨考虑树链剖分的实现过程：每次选中一条链，将当前点跳到链顶，以此往复。需要注意的是，一条链中的点的 dfn 序是连续的。那这就给了我们一个思路。

首先，使用 map 对所有权值离散化。然后，对于每个权值，用 multiset 维护其对应的所有点的 dfn 序，以此存储所有权值所出现在的位置。

接下来就好办了。在树链剖分上跳的过程中，对目标权值的 multiset 进行二分查找，判断是否有对应的点存在当前这条链上即可。

## 3、注意事项

- 注意 $LCA(a,b)$ 的权值其实被计算了两次，要将其补回来。
- 对 multiset 和 set 使用 lower_bound 或 upper_bound 函数时，因使用其自带的那种，不能使用头文件中的通用函数，否则时间复杂度会退化成 $O(N)$。
- 在树链剖分上跳之前直接求出目标值 $d$ 的对应离散化编号，而不是边跳边求。否则时间复杂度也会退化，有可能导致超时。


上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define ll long long

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){ if(c == '-') s = -1; c = getchar(); }
	while(isdigit(c)){ x = x * 10 + (c ^ '0'); c = getchar(); }
	a = x * s;
	return ;
}

struct node{
  int u, v;
  ll w; 
  int next; 
} t[N << 1];
int head[N];

int bian = 0;
inline void addedge(int u, int v, ll w){  // 双向边
  t[++bian] = (node){u, v, w, head[u]}, head[u] = bian;
  t[++bian] = (node){v, u, w, head[v]}, head[v] = bian; 
  return ; 
}

int n, Q; 
multiset <int> G[N]; 
ll a[N]; 

int dfn[N], top[N], son[N], siz[N], deth[N]; 
int fa[N], id = 0, rev[N];

ll sum[N];   // 树上前缀和数组

void dfs1(int u, int father){
  deth[u] = deth[father] + 1; 
  siz[u] = 1; 
  fa[u] = father; 
  sum[u] = a[u] ^ sum[father]; 
  int maxn = -1e9; 
  for(int i = head[u]; i; i = t[i].next){
    int v = t[i].v; 
    if(v != father){
      dfs1(v, u); 
      siz[u] += siz[v]; 
      if(siz[v] > maxn){
        maxn = siz[v];
        son[u] = v; 
      }
    }
  }
  return ; 
}

void dfs2(int u, int tp){
  top[u] = tp; 
  dfn[u] = ++id; 
  rev[id] = u; 
  if(!son[u]) return ;
  dfs2(son[u], tp);
  for(int i = head[u]; i; i = t[i].next){
    int v = t[i].v;
    if(v != fa[u] && v != son[u])
      dfs2(v, v); 
  }
  return ; 
}

int LCA(int x, int y){   // 求 LCA
  while(top[x] != top[y]){
    if(deth[top[x]] < deth[top[y]]) swap(x, y);
    x = fa[top[x]]; 
  }
  return deth[x] < deth[y] ? x : y; 
}

int check(int x, int y, int d){  // 检查值
  while(top[x] != top[y]){
    if(deth[top[x]] < deth[top[y]]) swap(x, y); 
    auto l = G[d].lower_bound(dfn[top[x]]); 
    auto r = G[d].upper_bound(dfn[x]); 
    if(l != r) return 1; 
    x = fa[top[x]]; 
  }
  if(deth[x] < deth[y]) swap(x, y); 
  auto r = G[d].upper_bound(dfn[x]); 
  auto l = G[d].lower_bound(dfn[y]);
  if(l != r) return 1;
  return 0; 
}

int hehe = 0; 
map <int, int> g; 

int main(){
  // freopen("hh.txt", "r", stdin); 
  read(n), read(Q);
  for(int i = 1; i <= n; i++){
    read(a[i]);
    if(!g.count(a[i])) g[a[i]] = ++hehe;    // 离散化
  } 
  for(int i = 1; i < n; i++){
    int x, y;
    read(x), read(y);
    addedge(x, y, 0); 
  }
  dfs1(1, 0);
  dfs2(1, 1); 

  for(int i = 1; i <= n; i++){
    G[g[a[i]]].insert(dfn[i]);      // 插入点的值
  }
  while(Q--){
    ll x, y, k;
    read(x), read(y); read(k); 
    ll ans = sum[x] ^ sum[y];
    int lca = LCA(x, y); 
    ans ^= a[lca]; 
    ll d = ans ^ k;  // d: 需要寻找的值
    d = g[d];    // 提前找好编号
    if(check(x, y, d)) puts("Yes");
    else puts("No"); 
  }
  return 0;
}

```


---

## 作者：RoFtaCD (赞：0)

## 树剖+哈希表+STL 平衡树

我相对较逊，我在做了[这题的简单版本后](https://www.luogu.com.cn/problem/P8200)就不想再动代码了））。

于是观察题目，发现这题是求点权异或和而不是边权。

我们知道根据按位异或的性质：有 $ a \oplus b \oplus b = a $，即如果一个节点被计算了两次，那么就对答案没有贡献。

可以发现如果询问点 $a,b$ 和值 $k$，我们在计算任意点 $t$ 的 $\mathrm{dis}_{t, a} \oplus \mathrm{dis}_{t, b}$ 的路径异或和时，部分重复的节点的权值会被消除掉。

如果记 $s$ 为 $\mathrm{dis}_{a, b} \oplus k$，**那么问题转换为**：询问树上从 $u$ 到 $v$ 的简单路径中，是否存在点 $t$ 权值为 $s$。

可以用树剖将树剖成链，转换为区间求异或和以及区间查询问题：

给定序列 $a$ 询问 $[a_l, a_r]$ 中是否存在数字 $s$。

**奇妙想法**：用哈希表离散化，对于每一个值建一棵平衡树，计入所有出现的位置，对于询问 $l,r$ 查找第一个大于等于 $l$ 的元素是否小于等于 $r$，如果存在这样的元素就可以直接输出 `YES` 了。

充分利用STL数据结构，运用 ```unordered_map``` 套 ``` set``` 实现代码。


时间复杂度 $ \mathcal{O}(m \cdot \log^2 n) $ 比较劣，但能过。

常数大，适合吸氧，记得在 ```set``` 中预先插入正负无穷。



## 代码

（其实链异或和树上差分就可以求了，我之前写了树剖懒得改）。

```
#include <bits/stdc++.h>
using std::swap;
typedef long long ll;
const int N=5e5+15,inf=0x3f3f3f3f;
int head[N],tt,n,q;
int a[N],sum[N];

std::map<int,std::set<int> >num;

struct edge{int to,fr,nxt;}ed[N<<1];
inline void added(int u,int v){
	ed[++tt].to=v,ed[tt].fr=u,ed[tt].nxt=head[u],head[u]=tt;
}

int fa[N],son[N],dep[N],top[N],sze[N],seg[N];

void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1,sze[u]=1;
	for(int i=head[u],v;i;i=ed[i].nxt){
		v=ed[i].to;if(v==f) continue;
		dfs1(v,u),sze[u]+=sze[v];
		if(sze[v]>sze[son[u]]) son[u]=v;
	}
}

void dfs2(int u){
	if(son[u]){
		seg[son[u]]=++seg[0],top[son[u]]=top[u];
		dfs2(son[u]);
	}
	for(int i=head[u],v;i;i=ed[i].nxt){
		v=ed[i].to;if(seg[v]) continue;
		seg[v]=++seg[0],top[v]=v;
		dfs2(v);
	}
}

#define lb (x&-x)
inline void add(int x,int v){
	for(;x<=n;x+=lb) sum[x]^=v;
}
inline int ques(int x){int r=0;for(;x;x-=lb) r^=sum[x];return r;}
inline int query(int x,int y){return ques(y)^(x-1>0 ? ques(x-1) : 0);}

inline bool qnum(int l,int r,int v){
	if(num[v].empty()) return 0;
	return (*num[v].lower_bound(l))<=r;  // 非常的（非常）
}

inline int chainq1(int x,int y){
	int res=0;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]) swap(x,y),swap(fx,fy);
		res^=query(seg[fx],seg[x]);
		x=fa[fx],fx=top[x];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res^=query(seg[x],seg[y]);
	return res;
}

inline bool chainq2(int x,int y,int v){
	int res=0;
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy]) swap(x,y),swap(fx,fy);
		if(qnum(seg[fx],seg[x],v)) return 1;
		x=fa[fx],fx=top[x];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return qnum(seg[x],seg[y],v);
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v),added(u,v),added(v,u);
	}
	dep[1]=1,dfs1(1,0);
	seg[0]=seg[1]=1,top[1]=1,dfs2(1);
	for(int i=1;i<=n;++i) add(seg[i],a[i]),num[a[i]].insert(seg[i]),num[a[i]].insert(inf),num[a[i]].insert(-inf);
	while(q--){
		int a,b,k;
		scanf("%d%d%d",&a,&b,&k);
		//printf("q1:%d\n",chainq1(a,b));
		k^=chainq1(a,b);
		puts(chainq2(a,b,k) ? "YES" : "NO");
	}   

	return 0;
}
```


---

