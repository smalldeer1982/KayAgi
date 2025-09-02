# [USACO17OPEN] Switch Grass P

## 题目描述

Farmer John 最近在他的农场尝试种植不同类型的草，发现不同类型的奶牛喜欢不同类型的草。然而，他必须小心确保不同类型的草种植得足够远，以防止它们不可分割地混合在一起。

FJ 的农场由 $N$ 块田地组成（$1 \leq N \leq 200,000$），其中 $M$ 对田地通过双向路径连接（$1 \leq M \leq 200,000$）。使用这些路径，可以从任何田地走到任何其他田地。每条路径的长度是一个在 $1 \ldots 1,000,000$ 范围内的整数。任何一对田地之间最多只有一条直接路径。

在每块田地中，FJ 最初种植了 $K$ 种草中的一种（$1 \leq K \leq N$）。然而，随着时间的推移，他可能会决定将某块田地的草更换为另一种类型。他称这种操作为“更新”操作。他可能会在一段时间内执行多次更新，这些更新都是累积性质的。

每次更新后，FJ 想知道种植不同草类型的两块田地之间的最短路径长度。也就是说，在所有种植不同草类型的田地对中，他希望知道哪两块田地最接近。理想情况下，这个数字应该较大，以便他可以防止一种类型的草与另一种类型的草混合。保证农场中始终至少有两块田地种植不同的草类型。

在 30% 的输入案例中，每块田地最多直接连接 10 条路径。

## 样例 #1

### 输入

```
3 2 3 4
1 2 3
2 3 1
1 1 2
3 3
2 3
1 2
2 2```

### 输出

```
1
3
3
1```

# 题解

## 作者：zzwdsj (赞：12)

~~[测试点下载：测试点.zip](https://vdse.bdstatic.com//192d9a98d782d9c74c96f09db9378d93.mp4?authorization=bce-auth-v1%2F40f207e648424f47b2e3dfbb1014b1a5%2F2021-07-12T02%3A14%3A24Z%2F-1%2Fhost%2F530146520a1c89fb727fbbdb8a0e0c98ec69955459aed4b1c8e00839187536c9)~~

### 思路

两个结论：

- 异色点对的最短距离一定是一条边。
  证明：当一条路径上的边两端颜色均相同是，这条路径两端颜色也相同，所以如果一条路径上两端颜色不同，那么这条路径上必有一条边两端颜色不同。那么如果异色点对的最短距离是一条（边数大于一的）路径，那么选这条路径上的一条两端颜色不同的边肯定比选这条路径更优。
- 异色点对的最短距离一定是一条最小生成树上的边。
  证明：如果一条两端异色的边 $(u,v)$ 没有被加入最小生成树。$u$ 到 $v$ 必有一条只经过最小生成树上边的路径，且这条路径上的边权均不大于 $(u,v)$ 的边权，与 $(u,v)$ 形成环。已知点 $u$ 与点 $v$ 异色，那么 $u$ 到 $v$ 只经过最小生成树上边的路径上必有一条两端异色的边 $(u_0,v_0)$。$(u_0,v_0)$ 的边权比 $(u,v)$ 小，所以选 $(u_0,v_0)$（最小生成树上的边）一定更优。

设 $\min n_{i,j}$ 为最小生成树上点 $i$ 的儿子中颜色为 $j$ 的儿子连接点 $i$ 的边权构成的可重集；$dis_i$ 为任意 $j$（$\min n_{i,j}$ 不为空，$i$ 的颜色不为 $j$）$\min n_{i,j}$ 中的**最小值**构成的可重集；$ans$ 为任意 $i$ ($dis_i$ 不为空)$dis_i$ 中的**最小值**最小值构成的可重集。

建树时。先跑一遍 Kruskal，求出原图的最小生成树，只保留生成树上的边。然后跑 dfs 按照定义求出 $\min n_{i,j}$，$dis_i$ 和 $ans$，同时记下每个点的父亲记作 $f_i$，每个点与父亲相连的边的边权记作 $l_i$，每个点的颜色记作 $v_i$。

将点 $x$ 的颜色修改为 $j$ 时，进行一下操作以更新 $\min n_{i,j}$，$dis_i$ 和 $ans$：

1. 更新 $ans$：由于在下面修改了 $dis_{f_x}$，$dis_{f_x}$ 可能有新的最小值，应该删掉原本的最小值。在 $ans$ 中删除 $dis_{f_x}$ 的最小值。
2. 当 $x$ 与 $f_x$ 异色时，更新 $dis_{f_x}$：由于在操作 3 中更新了 $\min n_{f_x,v_x}$，$\min n_{f_x,v_x}$ 可能有新的最小值，而当 $x$ 与 $f_x$ 异色时 $\min n_{f_x,v_x}$ 的最小值对 $dis_{f_x}$ 有贡献，应该删掉原本的最小值。在 $dis_{f_x}$ 中删除 $\min n_{f_x,v_x}$ 的最小值（此时直到更新 $v_x$ 前 $v_x$ 仍是修改前 $v_x$ 的颜色）。
3. 更新 $\min n_{f_x,v_x}$：由于修改颜色后，$x$ 颜色改变了，按照 $\min n_{f_x,v_x}$ 的定义，$l_X$，不在 $\min n_{f_x,v_x}$ 里。在 $\min n_{f_x,v_x}$ 中删除 $l_x$。
4. 当 $x$ 与 $f_x$ 异色时，更新 $dis_{f_X}$：同 2，由于在操作 3 中更新了 $\min n_{f_x,v_x}$，$\min n_{f_x,v_x}$ 可能有新的最小值。而当 $x$ 与 $f_x$ 异色时 $\min n_{f_x,v_x}$ 的最小值对 $dis_{f_x}$ 有贡献，应该加上现在的最小值。在 $dis_{f_x}$ 中插入 $\min n_{f_x,v_x}$ 的最小值（此时直到更新 $v_x$ 前 $v_x$ 仍是修改前 $v_x$ 的颜色）。
5. 更新 $ans$：由于在 6 和 8 中修改了 $dis_x$，$dis_x$ 可能有新的小值，应该删掉原本的最小值。在 $ans$ 中删除 $dis_x$ 的最小值。
6. 更新 $dis_x$：由于修改颜色后，$x$ 的颜色可能不为 $v_x$，那么 $x$ 的子节点中颜色为 $v_x$ 的节点可能可以对 $dis_x$ 产生贡献。在 $dis_x$ 中插入 $\min n_{x,v_x}$ 的最小值。
7. 更新 $v_x$ : 将 $v_x$ 更新为 $y$。
8. 更新 $dis_x$：由于修改颜色后，$x$ 的儿子中与 $v_x$ 同色的儿子不能对 $dis_x$ 产生贡献，但之前考虑了它的贡献。在 $dis_x$ 中删除 $\min n_{x,v_x}$ 的最小值。（此后的 $v_x$ 为 $x$ 修改后的颜色）
9. 更新 $ans$：同 5，由于在 6 和 8 中修改了 $dis_x$，$dis_x$ 可能有新的小值，应该加上现在的最小值。在 $ans$ 插入 $dis_x$ 的最小值。
10. 当 $x$ 与 $f_x$ 异色时，更新 $dis_{f_X}$：由于在 11 中修改了 $\min n_{f_x,v_x}$，$\min n_{f_x,v_x}$ 可能有新的小值，应该删掉原本的最小值。在 $dis_{f_X}$ 中删除 $\min n_{f_x,v_x}$ 的最小值。
11. 更新 $\min n_{f_x,v_x}$：由于修改颜色后，$x$ 颜色改变了，按照 $\min n_{f_x,v_x}$ 的定义，$l_X$，在 $\min n_{f_x,v_x}$ 里。在 $\min n_{f_x,v_x}$ 中插入 $l_x$。
12. 当 $x$ 与 $f_x$ 异色时，更新 $dis_{f_X}$：由于在 11 中修改了 $\min n_{f_x,v_x}$，$\min n_{f_x,v_x}$ 可能有新的小值，应该加上现在的最小值。在 $dis_{f_X}$ 插入 $\min n_{f_x,v_x}$ 的最小值。
13. 更新 $ans$：由于在上面修改了 $dis_{f_x}$，$dis_{f_x}$ 可能有新的最小值，应该加上现在的最小值。在 $ans$ 插入 $dis_{f_x}$ 的最小值。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,q,v[200005],l[200005],fa[200005]/*用于存储并查集中每个节点的父亲*/,f[200005],x,y;
vector<pair<int,int> >mp[200005];
multiset<int>dis[200005],ans;
unordered_map<int,multiset<int> >minn[200005];
//定义见上文
struct edge
{
	int x,y,l;
	bool operator<(const edge t)const{return l<t.l;}	
}e[200005];
int find(int x)
{
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
//并查集的实现
void dfs(int x,int fa)
{
	f[x]=fa;
	for(pair<int,int> i:mp[x])if(i.first!=fa) minn[x][v[i.first]].insert(i.second),l[i.first]=i.second,dfs(i.first,x);
    for(auto i:minn[x])if(i.first!=v[x])dis[x].insert(*i.second.begin());
	if(dis[x].size())ans.insert(*dis[x].begin());
}
//按照定义求出 ans,minn[i][j]和dis[i]
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].l);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	sort(e+1,e+m+1),iota(fa+1,fa+n+1,1);//此函数的功能是把fa[1],fa[2],...,fa[n]依次赋值为1,2,...,n。
	for(int i=1,cnt=0;i<=m&&cnt<n-1;i++)
		if(find(e[i].x)!=find(e[i].y))
			fa[find(e[i].x)]=find(e[i].y),mp[e[i].x].push_back({e[i].y,e[i].l}),mp[e[i].y].push_back({e[i].x,e[i].l}),cnt++;
	//Kruskal 的过程
	dfs(1,0);
	while(q--)
	{
		scanf("%d%d",&x,&y);
		if(f[x])
		{
			if(dis[f[x]].size())ans.erase(ans.find(*dis[f[x]].begin()));//见上文操作1
			if(v[x]!=v[f[x]])dis[f[x]].erase(dis[f[x]].find(*minn[f[x]][v[x]].begin()));//见上文操作2
			minn[f[x]][v[x]].erase(minn[f[x]][v[x]].find(l[x]));//见上文操作3
			if(v[x]!=v[f[x]]&&minn[f[x]][v[x]].size())dis[f[x]].insert(*minn[f[x]][v[x]].begin());//见上文操作4
		}
		if(dis[x].size())ans.erase(ans.find(*dis[x].begin()));//见上文操作5
		if(minn[x][v[x]].size())dis[x].insert(*minn[x][v[x]].begin());//见上文操作6
		v[x]=y;//见上文操作7
		if(minn[x][v[x]].size()&&dis[x].size())dis[x].erase(dis[x].find(*minn[x][v[x]].begin()));//见上文操作8
		if(dis[x].size())ans.insert(*dis[x].begin());//见上文操作9
		if(f[x])
		{
			if(v[x]!=v[f[x]]&&minn[f[x]][v[x]].size())dis[f[x]].erase(dis[f[x]].find(*minn[f[x]][v[x]].begin()));//见上文操作10
			minn[f[x]][v[x]].insert(l[x]);//见上文操作11
			if(v[x]!=v[f[x]])dis[f[x]].insert(*minn[f[x]][v[x]].begin());//见上文操作12
			if(dis[f[x]].size())ans.insert(*dis[f[x]].begin());//见上文操作13
		}
		printf("%d\n",*ans.begin());
	}
	return 0;
}
```

---

## 作者：zzw4257 (赞：11)

>给定一个 $n$ 点 $m$ 边无向图，每个点有初始颜色，多次修改一个点颜色，动态回答所有异色点对间最短距离

首先发现一件事情，我们选择的一定是**一条边**,考虑一条路径首尾异色，期间一定有至少一对相邻的点异色，所以直接取这些边更优

其次我们选择的来源一定是**任何一棵最小生成树上的边**,证明基于消圈定律，考虑一个环上的最大边

- 若是同色，删掉无影响
- 若是异色，删掉两点间路径上一定有两个相邻点异色并且权值不会更大(显然)

生成树形态已定

问题可以简单转化为维护每个点不同色儿子中的最小距离

我们可以开$n$棵动态开点线段树下标为颜色，在叶子处插入这种颜色边权，维护颜色区间的最值，然后前后缀($[1,x)+(x,K]$)拼凑不同色中的最值

每次更改只会影响自己和父亲的答案，只会动父亲的线段树


```cpp
#include<bits/stdc++.h>
#define N 200001
#define INF 0x3f3f3f3f
#define M N*32
#define ls(a) *son[a]
#define rs(a) son[a][1]
typedef long long ll;
using namespace std;
inline int read(void){int x;scanf("%d",&x);return x;}
struct Edge{int x,y,v;inline char operator<(Edge a)const{return v<a.v;}}e[N]; 
struct edge{int to,v;};
multiset<int>s[N<<1],ans;
int n,m,K,q,tot,son[M][2],mi[M],num[M],last[N],a[N],sign,fa[N],len[N],rt[N];
vector<edge>g[N];
inline int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);}
inline void pushup(int x){mi[x]=min(mi[ls(x)],mi[rs(x)]);}
inline void Insert(int&pos,int l,int r,int x,int v){
	if(!pos)pos=++tot;int mid=(l+r)>>1;
	if(l==r){if(!num[pos])num[pos]=++sign;s[num[pos]].insert(v);mi[pos]=*s[num[pos]].begin();return ;}
	(x<=mid)?Insert(ls(pos),l,mid,x,v):Insert(rs(pos),mid+1,r,x,v);pushup(pos);
}
inline void Delete(int&pos,int l,int r,int x,int v){
	int mid=(l+r)>>1;
	if(l==r){s[num[pos]].erase(s[num[pos]].find(v));mi[pos]=s[num[pos]].size()?*s[num[pos]].begin():INF;return ;}
	(x<=mid)?Delete(ls(pos),l,mid,x,v):Delete(rs(pos),mid+1,r,x,v);pushup(pos);
}
inline int Query(int pos,int l,int r,int ql,int qr){
	if(!pos||ql>qr)return INF;
	int mid=(l+r)>>1,res=INF;
	if(ql<=l&&r<=qr)return mi[pos];
	if(ql<=mid)res=min(res,Query(ls(pos),l,mid,ql,qr));
	if(qr>mid)res=min(res,Query(rs(pos),mid+1,r,ql,qr));
	return res;
}
inline int Ask(int x){return min(Query(rt[x],1,K,1,a[x]-1),Query(rt[x],1,K,a[x]+1,K));}
inline void dfs(int x,int prt){int y;fa[x]=prt;for(auto t:g[x])if((y=t.to)^prt)len[y]=t.v,dfs(y,x),Insert(rt[x],1,K,a[y],len[y]);ans.insert(last[x]=Ask(x));/*printf("%d :%d %d\n",x,last[x],len[x]);*/}
signed main(void){
	int i,x,y,v,fx,fy;*mi=INF;
	n=read(),m=read(),K=read(),q=read();
	for(i=1;i<=n;++i)fa[i]=i;
	for(i=1;i<=m;++i)e[i]={read(),read(),read()};
	for(i=1;i<=n;++i)a[i]=read();
	sort(e+1,e+m+1);
	for(i=1;i<=m;++i){x=e[i].x,y=e[i].y;if((fx=getf(x))^(fy=getf(y)))fa[fx]=fy,g[x].push_back({y,e[i].v}),g[y].push_back({x,e[i].v});}
	dfs(1,0);
	while(q--){
		y=fa[x=read()],v=read();
		ans.erase(ans.find(last[x]));if(y)ans.erase(ans.find(last[y])),Delete(rt[y],1,K,a[x],len[x]);a[x]=v;
		ans.insert(last[x]=Ask(x));if(y)Insert(rt[y],1,K,a[x],len[x]),ans.insert(last[y]=Ask(y));
		printf("%d\n",*ans.begin());
	}
	return 0;
}
```

---

## 作者：5ab_juruo (赞：10)

给一种跑得飞快而且还好写的做法，发布的时候 994ms 最优解。感谢 @[chenxinyang2006](/user/49776) 和 @[I_am_Accepted](/user/101868) 两位神仙的指点。

首先注意到最短的路径一定只有一条边，且仅保留原图的最小生成树答案不变。因为对于一条边权更大的边，如果无法加入最小生成树，则必然在两点之间有一条更短的边作为答案。

考虑原图的 Kruskal 重构树，对于一个虚点，其可能成为答案的条件为：

- 左子树和右子树内的类型都相同，否则儿子作为答案肯定不劣；
- 两边子树内存在类型不同的点。

所以，对于一棵子树，任何一个点都可以代表这棵子树的颜色。

接下来考虑重构这张图为一条链，使其答案相同且可以暴力处理，方法如下：

- 初始每个点为自身；
- Kruskal 合并时，将左子树的链尾和右子树的链首连边，权值为对应的图上的边。

注意到对于这张图，原图中的答案一定会算上，且优于答案的部分一定不会算上，所以可以直接暴力求解。复杂度 $\mathcal{O}((n+q)\log n)$。

实现时，可以用两个堆来代替 set 从而减小常数。

```cpp
/* name: P3665
 * author: 5ab
 * created at: 2023-02-03
 */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
using namespace std;

typedef long long ll;
const int max_n = 200000, max_m = 300000;

struct edge
{
	int u, v, w;
}
e[max_m];
int dsu[max_n], c[max_n], l[max_n], r[max_n];
int hd[max_n], des[max_n * 2], val[max_n * 2], nxt[max_n * 2], e_cnt = 0;
priority_queue<int, vector<int>, greater<int>> pq, del;

int fnd(int x) { return x == dsu[x] ? x : (dsu[x] = fnd(dsu[x])); }
void add(int s, int t, int v)
{
	des[e_cnt] = t;
	val[e_cnt] = v;
	nxt[e_cnt] = hd[s];
	hd[s] = e_cnt++;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m, lim, q;
	
	cin >> n >> m >> lim >> q;
	fill(hd, hd + n, -1);
	for (int i = 0; i < m; i++)
	{
		auto& [u, v, w] = e[i];
		cin >> u >> v >> w;
		u--, v--;
	}
	for (int i = 0; i < n; i++)
		cin >> c[i];
	sort(e, e + m, [](const edge& lhs, const edge& rhs) {
		return lhs.w < rhs.w;
	});
	
	iota(dsu, dsu + n, 0);
	iota(l, l + n, 0);
	iota(r, r + n, 0);
	for (int i = 0; i < m; i++)
	{
		auto [u, v, w] = e[i];
		u = fnd(u), v = fnd(v);
		if (u != v)
		{
			add(r[u], l[v], w);
			add(l[v], r[u], w);
			dsu[v] = u;
			r[u] = r[v];
		}
	}
	
	for (int i = 0; i < n; i++)
		for (int p = hd[i], dst; p != -1; p = nxt[p])
		{
			dst = des[p];
			if (c[i] != c[dst] && i < dst)
				pq.push(val[p]);
		}
	
	int x, v;
	while (q--)
	{
		cin >> x >> v, x--;
		for (int p = hd[x], dst; p != -1; p = nxt[p])
		{
			dst = des[p];
			if (c[x] != c[dst])
				del.push(val[p]);
			if (v != c[dst])
				pq.push(val[p]);
		}
		c[x] = v;
		
		while (!pq.empty() && !del.empty() && pq.top() == del.top())
			pq.pop(), del.pop();
		cout << pq.top() << "\n";
	}
	
	return 0;
}
```

---

## 作者：pmt2018 (赞：7)

#题目简述

给定一张$n,m(n,m\le200,000)$带权(权为正)无向图，每个点有一个颜色$k(k\le n)$，每次改变一个点的颜色，要求你在操作后输出这个图中最近异色点对之间的距离。最近异色点对定义为：一对点颜色不同，且距离最小.

[传送门](https://www.luogu.org/problem/P3665)

#解题报告

一道非常**清新脱俗**的US open题。

##Part1

首先因为边权为正，显然可以想到答案一定是某一条边的权值。

进一步可以猜想答案一定是在图的最小生成树上。

给出一个证明：

考虑``Kruskal``的过程，我们先把边按边权排序，我们不断把边加入最小生成树的集合。

若某条连接$u,v$的边不能被加入集合（称为我们放弃的边），则这条边一定和某一条连接$u,v$的路径**形成环**。且环上**所有边权**都比这一条边小。

若$u,v$两端颜色相同，则这一条边**一定**没有贡献

否则$u,v$颜色不同，在原有的$u,v$路径中，至少有一条边连接的两端颜色也不同，且那条边边权比我们放弃的边边权更小，显然更优。

##Part 2

考虑维护这颗最小生成树。

我们先把它变成一颗有根树，然后考虑每个点  **它的所有儿子 与他的连边的贡献**

USACO官方题解给出了一种非常优美的解法（虽然写起来又臭又长）。

我们对于每一个点($u$)的所有**儿子的颜色**都开一个``multiset``,

我们称其为$CLS_{u,c}(c为颜色)$，存储它和所有颜色为$c$的儿子的边长

显然每一条边只有可能在一个``multiset``里，总的节点数只有$n-1$,不会炸空间。（下面有具体实现）

再为每一个节点开一个``multiset``，称其为$best_u$，储存所有的$（min\{CLS_{u,c} \}）_{C \in all colors }$

我们再建一颗线段树，称其为$SGT$，储存每个节点和他儿子的最近异色点对长度。

所以对于每一个节点$u$,他的答案不是``*(best[u]).begin()``就是``*((best_u).begin()++)``

因为$best_u$中每种颜色显然只有一个，若第一个是同色，那第二个一定是异色（或者没有第二个）。

那我们如何维护呢？

首先，当对于每一个点的颜色(从$c$改为$c'$)进行修改时，我们要修改两个部分。

1. 考虑它和它父亲之间的影响。

    我们先要把它从原来在的$CLS_{fa[u],c}$取出来，放进$CLS_{fa[u],c'}$中，这时$min\{CLS_{fa[u],c}\}$和

$min\{CLS_{fa[u],c'}\}$都会改变,我们还要修改$best_u$中的这两项。

2. 考虑改过颜色后，它和它儿子的答案可能由``*(best[u]).begin()``变为``*((best_u).begin()++)``

或``*((best_u).begin()++)``变为``*(best[u]).begin()``，我们对其进行修改。

代码如下

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef map<int,multiset<int> >::iterator MSIT;
typedef set<pair<int,int > >::iterator SPIT;


const int INF=0x3f3f3f3f, maxn=200007;
int n,m,q,k;
struct edge{
	int to,nxt,val;
}e[maxn<<1];
int head[maxn];
int tot;
void addedge(int u,int v,int val){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].val=val;
	head[u]=tot;
}//树边

namespace MST{
	struct edge1{
		int x,y,val;	
		friend bool operator <(const edge1 &a,const edge1 &b){
			return a.val<b.val;	
		}
	}G[maxn];
	int fa[maxn];
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	void init(){for(int i=1;i<=n;i++)fa[i]=i;}
	void GMST(){
		init();
		sort(G+1,G+m+1);
		int cnt=0;
		for(int i=1;i<=m;i++){
			int u=G[i].x,v=G[i].y;
			int fu=find(u),fv=find(v);
			if(fu==fv)continue;
			cnt++,fa[fu]=fv;
			addedge(u,v,G[i].val);
			addedge(v,u,G[i].val);
		}
	}
}//求最小生成树
using namespace MST;

struct SGT{
	int t[maxn<<2];

	void pushup(int x){
		t[x]=min(t[x<<1],t[x<<1|1]);
	}
	void build(int x,int l,int r){
		if(l==r){
			t[x]=INF;
			return ;
		}
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pushup(x);
	}
	void update(int id,int l,int r,int pos,int val ){
		if(l==r){
			t[id]=val;
			return ;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)update(id<<1,l,mid,pos,val);
		else update(id<<1|1,mid+1,r,pos,val);
		pushup(id);
	}
}T;//线段树
multiset<pair<int,int > > best[maxn];
map<int,multiset<int > > cls[maxn];
int cl[maxn];
int f[maxn];
int w[maxn];

void dfs(int u,int ff){
	f[u]=ff;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==ff)continue;
		w[v]=e[i].val;
		cls[u][cl[v]].insert(w[v]);
		dfs(v,u);
	}
	for(MSIT it=cls[u].begin();it!=cls[u].end();it++){
		best[u].insert(mp(*(*it).se.begin(),(*it).fi));//初始化best数组
	}
	//初始化线段树
	if(!best[u].empty()){
		SPIT it=best[u].begin();
		if(cl[u]!=(*it).se)T.update(1,1,n,u,(*it).fi);
		else{
			it++;
			if(it==best[u].end())T.update(1,1,n,u,INF);
			else T.update(1,1,n,u,(*it).fi);
		}
	}
		
}

int main(){

	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=m;i++){
		int u,v,val;
		scanf("%d%d%d",&u,&v,&val);
		G[i]=(edge1){u,v,val};
	}	
	GMST();
	for(int i=1;i<=n;i++)scanf("%d",&cl[i]);
	T.build(1,1,n);
	dfs(1,0);
	while(q--){
		int u,c2;
		scanf("%d%d",&u,&c2);//每一次更改
		if(f[u]){
			int c1=cl[u];
			best[f[u]].erase(best[f[u]].find(mp(*cls[f[u]][c1].begin(),c1)));
			cls[f[u]][c1].erase(cls[f[u]][c1].find(w[u]));
			if(cls[f[u]][c1].empty())cls[f[u]][c1].insert(INF);
			best[f[u]].insert(mp(*cls[f[u]][c1].begin(),c1));
			//我们先把u从cl[u]抹去
			if(!cls[f[u]][c2].empty())
				best[f[u]].erase(best[f[u]].find(mp(*cls[f[u]][c2].begin(),c2)));
			cls[f[u]][c2].insert(w[u]);
			best[f[u]].insert(mp(*cls[f[u]][c2].begin(),c2));
			//再加入新的集合中
			SPIT it=best[f[u]].begin();
			if(cl[f[u]]!=(*it).se)T.update(1,1,n,f[u],(*it).fi);
			else{
				it++;
				if(it==best[f[u]].end())T.update(1,1,n,f[u],INF);
				else T.update(1,1,n,f[u],(*it).fi);
			}
		}
		if(!best[u].empty()){
			SPIT it=best[u].begin();
			if(c2!=(*it).se)T.update(1,1,n,u,(*it).fi);
			else{
				it++;
				if(it==best[u].end())T.update(1,1,n,u,INF);
				else T.update(1,1,n,u,(*it).fi);
			}
		}
		cl[u]=c2;
		printf("%d\n",T.t[1]);
	}
	return 0;
}

```







---

## 作者：feecle6418 (赞：5)

两个重要结论：

1. 答案一定是一条边的长度。
2. 答案一定在最小生成树上。

读者容易自己证明上述结论。

这两个结论的意义在于，第一条让我们把难以维护的“图上路径”变为了易于维护的权值；第二条使得用 STL set 直接维护每个点的出边变得可行，因为每个点只会影响 $O(1)$ 个 set（自己的，父亲的）。

考虑具体如何用 set 维护。先建出最小生成树：

1. 对每个点 `x`，维护 $O(son)$（儿子个数）个 set（其实是 multiset，以下不区分，需要注意 multiset 的删除正确写法应是 `s.erase(s.find(x))`）`mxc[x][col]`，表示 $x$ 的儿子中所有权值为 $col$ 的与 $x$ 的连边的边权集合；
2. 对每个点 $x$ 维护 `mx[x]`，里面存放所有 `mxc[x][...]` 中的最小值（显然 $x$ 对答案的贡献只可能来源于 `mx` 中最小值或者次小值）；
3. 全局上维护 `ans` 表示所有点的 `mx` 中最小值或者次小值（儿子最小值的颜色与自己相同时）的最小值，显然 `ans.begin()` 就是答案。

修改时，分两步：

- 修改 $x$ 的儿子对 $x$ 的贡献。实现上即是修改 `mx[x]` 对 `ans` 的贡献。
- 令 $fa_x=p$，修改 $x$ 对 $p$ 的贡献。这里稍有麻烦，需要先修改 `mxc[p][a[x]]` 和 `mxc[p][y]`，再修改 `mx[p]` 及 `ans`。

总复杂度是 $O((n+q)\log n+m\log m)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
struct Edge{
	int x,y,z;
}e[200005];
struct E{
	int to,val;
};
vector<E> g[200005];
int n,m,K,q,a[200005],f[200005],fa[200005],v[200005],len[200005];
map<int,multiset<int> > mxc[200005];
multiset<int> ans;
multiset<pair<int,int> > mx[200005];
int gf(int x){
	return f[x]==x?x:f[x]=gf(f[x]);
}
void dfs(int x,int f){
	fa[x]=f,v[x]=1;
	for(E i:g[x]){
		int y=i.to;
		if(y==f)continue;
		len[y]=i.val,dfs(y,x),mxc[x][a[y]].insert(i.val);
	}
	if(!mxc[x].size())return ;
	for(auto i:mxc[x])mx[x].insert(mp(*i.second.begin(),i.first));
	auto it=mx[x].begin();
	if(it->second^a[x])ans.insert(it->first);
	else if((++it)!=mx[x].end())ans.insert(it->first);
}
void Upd1(int x,int y){
	if(a[x]==y||!mx[x].size())return ;
	auto it=mx[x].begin();
	if(it->second^a[x])ans.erase(ans.find(it->first));
	else if((++it)!=mx[x].end())ans.erase(ans.find(it->first));
	it=mx[x].begin();
	if(it->second^y)ans.insert(it->first);
	else if((++it)!=mx[x].end())ans.insert(it->first);
}
void Upd2(int x,int y){
	int p=fa[x];
	if(a[x]==y||!p)return ;
	auto it=mx[p].begin();
	if(it->second^a[p])ans.erase(ans.find(it->first));
	else if((++it)!=mx[p].end())ans.erase(ans.find(it->first));
	mx[p].erase(mx[p].find(mp(*mxc[p][a[x]].begin(),a[x])));
	mxc[p][a[x]].erase(mxc[p][a[x]].find(len[x]));
	if(mxc[p].count(y))mx[p].erase(mx[p].find(mp(*mxc[p][y].begin(),y)));
	mxc[p][y].insert(len[x]);
	mx[p].insert(mp(*mxc[p][y].begin(),y));
	if(!mxc[p][a[x]].size())mxc[p].erase(a[x]);
	else mx[p].insert(mp(*mxc[p][a[x]].begin(),a[x]));
	it=mx[p].begin();
	if(it->second^a[p])ans.insert(it->first);
	else if((++it)!=mx[p].end())ans.insert(it->first);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&K,&q);
	for(int i=1,x,y,z;i<=m;i++)scanf("%d%d%d",&x,&y,&z),e[i]={x,y,z};
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),f[i]=i;
	sort(e+1,e+m+1,[](Edge i,Edge j){return i.z<j.z;});
	for(int i=1;i<=m;i++){
		int x=e[i].x,y=e[i].y,z=e[i].z,fx=gf(x),fy=gf(y);
		if(fx==fy)continue;
		f[fx]=fy,g[x].push_back({y,z}),g[y].push_back({x,z});
	}
	for(int i=1;i<=n;i++)if(!v[i])dfs(i,0);
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y),Upd1(x,y),Upd2(x,y),a[x]=y,printf("%d\n",*ans.begin());
	}
}
```

---

## 作者：北文 (赞：3)

唐诗了，模拟赛出了这道题，也许只有我这种 nt 才能想到用线段树分治去做。   
前面的和大家一样，有用的答案只存在于最小生成树上。因此先建出最小生成树，然后考虑怎么维护异色树边最小值。   
我们考虑一个经典的 trick：当一个点同时对父亲和儿子有贡献的时候，我们将贡献拆为对父亲的，和对儿子的，这样每次就能 $O(1)$ 修改。  
由于询问异色边权最小值，我们要对每个节点记录：当前最小的边权；最小边另一端的颜色；与最小边另一端颜色不同的最小边。  
这三个信息在加入的时候容易维护，但修改颜色的时候不好维护。  
有一个瞬间线段树分治出现在我的脑海里，我们不放考虑线段树分治。  
套路地，原来的 $\mathcal O(n)$ 个修改，放在线段树上变成了 $\mathcal O(n\log n)$ 个加入。  
现在在分治过后的树上维护以上的三个信息，用栈存下修改信息，回溯的时候回退即可。  
时间复杂度 $\mathcal O(n\log n)$


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace slowIO
{
	const int _Pu = 1 << 23;
	const int _d = 32;
	char buf[_Pu];
	char obuf[_Pu];
	char *p1 = buf + _Pu;
	char *p2 = buf + _Pu;
	char *p3 = obuf, *p4 = obuf + _Pu - _d;
	inline void flushin()
	{
		memmove(buf, p1, p2 - p1);
		int rlen = fread(buf + (p2 - p1), 1, p1 - buf, stdin);
		if (p1 - rlen > buf) { buf[p2 - p1 + rlen] = EOF; }
		p1 = buf;
	}
	inline void flushout() { fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf; }
	template <typename T> inline void read(T &x)
	{
		if (p1 + _d > p2) { flushin(); }
		int isne = 0;
		for (; !isdigit(*p1); ++p1) { isne = (*p1 == '-'); }
		x = (*p1++ - '0');
	    for (; isdigit(*p1); ++p1) { x = x * 10 + (*p1 - '0'); }
		if (isne) { x = -x; }
	}
	template <typename T> inline void write(T x, char end = '\n')
	{
		if (p3 > p4) { flushout(); }
		if (x < 0) { *p3++ = '-'; x = -x; }
		char sta[20];
		char *top = sta;
		do { *top++ = (x % 10) + '0'; x /= 10; } while (x);
		do { *p3++ = *--top; } while (top != sta);
		(*p3++) = end;
	}
} using namespace slowIO;
const int N=2e5+5;
int n, m, k, q;
struct E{
	int u, v, w;
} e[N*4];
vector<pair<int, int> > g[N];
bool cmp(E a, E b) {
	return a.w<b.w;
}
int fa[N];
int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
} 
int col[N], tc[N], lst[N], ft[N], lt[N];
void dfs(int u, int fa) {
	ft[u]=fa;
	for(auto t:g[u]) {
		int v=t.first;
		if(v==fa) continue ;
		lt[v]=t.second; dfs(v, u);
	}
}
int mn1[N], cc1[N], mn2[N];

vector<pair<int, int> > t[N*4];
void update(int u, int l, int r, int L, int R, pair<int, int> v) {
	if(L>R) return ;
	if(L<=l&&r<=R) return void(t[u].push_back(v));
	int mid=l+r>>1;
	if(L<=mid) update(u<<1, l, mid, L, R, v);
	if(R>mid) update(u<<1|1, mid+1, r, L, R, v);
}
struct MM{
	int x, m1, c1, m2;
} st[N*4];
int top;
void mk(int x) {
	st[++top]={x, mn1[x], cc1[x], mn2[x]};
}

void solve(int u, int l, int r, int mn) {
	int prmn=mn, lst=top;
	for(auto v:t[u]) {
		int x=v.first, c=v.second;
		tc[x]=c;
		if(tc[ft[x]]&&tc[ft[x]]!=tc[x])
			mn=min(mn, lt[x]);
		int f=ft[x];
		
		if(lt[x]<mn1[f]) {
			mk(f);
			if(tc[x]!=cc1[f]) mn2[f]=mn1[f], mn1[f]=lt[x], cc1[f]=tc[x];
			else mn1[f]=lt[x];
		} else if(lt[x]<mn2[f]&&tc[x]!=cc1[f]) {
			mk(f);
			mn2[f]=lt[x];
		}
		
		if(tc[x]!=cc1[x]) mn=min(mn, mn1[x]);
		else mn=min(mn, mn2[x]);
		 
	}
	if(l==r) {
		printf("%d\n", mn);
	} else {
		int mid=l+r>>1;
		solve(u<<1, l, mid, mn);
		solve(u<<1|1, mid+1, r, mn);
	}
	for(auto v:t[u]) {
		int x=v.first, c=v.second;
		tc[x]=0;
	}
	while(top>lst) {
		int x=st[top].x, m1=st[top].m1, c1=st[top].c1, m2=st[top].m2;
		top--;
		mn1[x]=m1;
		cc1[x]=c1;
		mn2[x]=m2;
	}
	mn=prmn;
}
int main() {
//	freopen("cup.in", "r", stdin);
//	freopen("cup.out","w",stdout);
	memset(mn1, 0x3f, sizeof(mn1));
	memset(mn2, 0x3f, sizeof(mn2));
	read(n); read(m); read(k); read(q);
	for(int i=1; i<=m; i++) {
		int u, v, w;
		read(u); read(v); read(w);
		e[i]={u, v, w};
	}
	sort(e+1, e+1+m, cmp);
	int tot=0;
	for(int i=1; i<=n; i++) fa[i]=i;
	for(int i=1; i<=m; i++) {
		int u=find(e[i].u), v=find(e[i].v), w=e[i].w;
		int x=e[i].u, y=e[i].v;
		if(u==v) continue ;
		fa[u]=v; tot++;
		g[x].push_back({y, w});
		g[y].push_back({x, w});
		if(tot==n-1) break ;
	}
	dfs(1, 0);
	for(int i=1; i<=n; i++) 
		read(col[i]), lst[i]=1;
	for(int i=1; i<=q; i++) {
		int x, c;
		read(x); read(c);
		update(1, 1, q, lst[x], i-1, {x, col[x]});
		lst[x]=i; col[x]=c;
	} 
	for(int i=1; i<=n; i++) {
		update(1, 1, q, lst[i], q, {i, col[i]});
	}
	solve(1, 1, q, 1e9);
	return 0;
}
```

---

## 作者：1saunoya (赞：3)

两个显然的结论

**1.答案一定是相邻两边**

证明:如果相邻两点 $x \to y$ 同色，$x \to z$ 不同色，没必要选 $y \to z$。

**2.答案一定在最小生成树上**

证明:结合第一个结论，发现这个是对的。

然后就是简单数据结构的事情了。

代码是啥，这辈子都不会写的。

---

## 作者：yqr123YQR (赞：1)

### 分析
我们可得以下二结论：
+ 答案必为一条边的边权

  若为一条路径，利用反证，可知必有路径上一边满足条件，其长度一定比路径总长短。
+ 答案所在边必为最小生成树树边

  若为非树边，则树上连接两端点的路径同样合题。由上条，其中又必有一条合法边。再由最小生成树性质，这条树边一定不比此非树边长，自然选该树边不劣。

综上，我们只需单独拎出最小生成树，在树上维护父子不同色的最短边。这个很容易想到单次修改 $O(\log n)$、查询 $O(1)$ 的实现：

对于每个点 $i$，以 $mn_{i,j}$ 维护颜色为 $j$ 的子节点中，与 $i$ 的距离所构成的可重集；以 $len_i$ 维护 $i$ 与其每种颜色的子节点形成的最短合法边的可重集。再以 $ans$ 维护每个点与其子节点形成的最短合法边的可重集合。

~~至于怎么实操就不说了~~
### 代码
```cpp
//......
int n, m, K, q, f[maxn + 5], v[maxn + 5], d[maxn + 5];//v：点权 d：与父节点连边的边权
struct edge {
	int st, to, value;
	friend bool operator < (const edge &a, const edge &b) {return a.value < b.value;}
}s[maxm + 5];
std::vector<edge> g[maxn + 5];
std::multiset<int> len[maxn + 5], ans;
std::unordered_map<int, std::multiset<int> > mn[maxn + 5];//定义同上文
void solve(int a, int b)
{
	if(f[a])
	{
		if(len[f[a]].size()) ans.erase(ans.find(*len[f[a]].begin()));
		if(v[a] != v[f[a]]) len[f[a]].erase(len[f[a]].find(*mn[f[a]][v[a]].begin()));
		mn[f[a]][v[a]].erase(mn[f[a]][v[a]].find(d[a]));
		if(v[a] != v[f[a]] && mn[f[a]][v[a]].size()) len[f[a]].insert(*mn[f[a]][v[a]].begin());
	}
	if(len[a].size()) ans.erase(ans.find(*len[a].begin()));
	if(mn[a][v[a]].size()) len[a].insert(*mn[a][v[a]].begin());
	int last = v[a];
	v[a] = b;
	if(f[a])
	{
		if(v[a] != v[f[a]] && mn[f[a]][v[a]].size()) len[f[a]].erase(len[f[a]].find(*mn[f[a]][v[a]].begin()));
		mn[f[a]][v[a]].insert(d[a]);
		if(v[a] != v[f[a]]) len[f[a]].insert(*mn[f[a]][v[a]].begin());
		if(len[f[a]].size()) ans.insert(*len[f[a]].begin());
	}
	if(mn[a][v[a]].size()) len[a].erase(len[a].find(*mn[a][v[a]].begin()));
	if(len[a].size()) ans.insert(*len[a].begin());
	printf("%d\n", *ans.begin());
}
int main()
{
  //init & kruscal & build......
	for(int i = 1, a, b; i <= q; i++) a = read(), b = read(), solve(a, b);
	return 0;
}
```

---

## 作者：lzqy_ (赞：1)

不太一样的实现方法。

先找性质：

- 答案一定是一条边。

	考虑反证法。如果答案是 $\{x\rightarrow y\}$ 的路径，那么 $x,y$ 异色，路径上的点 $z$ 不可能同时和 $x,y$ 同色。所以 $\{x\rightarrow z\},\{z\rightarrow y\}$ 肯定有一个可取且更优。
    
- 答案一定在最小生成树上。

	证明类似。假设答案为不在MST上的边 $(u,v)$。根据MST的定义，$\{u\rightarrow v\}$ 路径上的每一条边的边权都小于等于 $(u,v)$ 的边权，显然选MST $\{u \rightarrow v\}$ 路径上的边不劣。
    
    
所以问题转化为求树上最小的边权，满足两个端点的颜色不同。

从图转化为树，肯定要利用树唯一前驱的性质。考虑每个节点维护其连向子节点的边，这样每次修改只需要改变父节点的信息。

对于点 $x$，其子节点 $u$ 的有效信息为 $(col_u,u)$
。$col_u$ 是为了查询哪些子节点与 $x$ 颜色不同，$u$ (编号) 是为了定位修改的位置。

由于是单点修改区间查询，所以对于每个节点按照 $col$ 为第一关键字，编号为第二关键字，建一棵 $n\times k$ 的动态开点线段树，修改操作变成两次单点修改（$(col_x,x)$ 变为 $0$，$(col'_x,x)$ 变为边权），当前节点的答案变成挖掉 $col_x$ 的 $n$ 个数后的最值。

然后最后再拿一棵线段树维护每个节点的答案的最值就好，时间复杂度 $O(n\log n^2)$。

~~冷知识：最值维护成最大值有90分~~
 
 
 ```cpp
 #include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define il inline
using namespace std;
const int maxn=200010;
const int maxN=maxn*70;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x; 
}
struct Edge{
	int u,v,w;
}E[maxn];
il bool cmp(Edge a,Edge b){return a.w<b.w;}
struct edge{
	int v,w,to;
}e[maxn<<1];
int head[maxn],ecnt=1;
void addedge(int u,int v,int w){
	e[++ecnt].v=v,e[ecnt].w=w;
	e[ecnt].to=head[u],head[u]=ecnt;
}
int lw[maxn];
int ans[maxn<<2],fa[maxn];
int rt[maxn],data[maxN],ls[maxN],rs[maxN];
int n,m,k,q,cnt,N;
int col[maxn],f[maxn];
int sz[maxn],Son[maxn];
int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);} 
void Kruscal(int cn=1){
	for(int i=1;cn<n;i++)
		if(Find(E[i].u)^Find(E[i].v)){
			sz[E[i].u]++,sz[E[i].v]++;
			addedge(E[i].u,E[i].v,E[i].w);
			addedge(E[i].v,E[i].u,E[i].w);
			f[Find(E[i].u)]=Find(E[i].v),cn++;
		}
	for(int i=2;i<=n;i++) sz[i]--;
} 
il int Min(int x,int y){if(!x) return y;if(!y) return x;return min(x,y);} 
void Modify1(int &i,ll l,ll r,ll x,int k){
//	printf("%d,%d\n",l,r);
	if(!i) i=++cnt;
	if(l==x&&r==x){
		data[i]=k;
		return ;
	}ll mid=l+r>>1;
	if(x<=mid) Modify1(ls[i],l,mid,x,k);
	else Modify1(rs[i],mid+1,r,x,k);
	data[i]=Min(data[ls[i]],data[rs[i]]);
}
int Query1(int i,ll l,ll r,ll L,ll R){
	if(l>=L&&r<=R) return data[i];
	if(l>R||r<L||!i) return 0;
	ll mid=l+r>>1;
	return Min(Query1(ls[i],l,mid,L,R),Query1(rs[i],mid+1,r,L,R));
}
void Modify2(int i,int l,int r,int x,int k){
	if(l==x&&r==x){
		ans[i]=k;
		return ;
	}int mid=l+r>>1;
	if(x<=mid) Modify2(i<<1,l,mid,x,k);
	else Modify2(i<<1|1,mid+1,r,x,k);
	ans[i]=Min(ans[i<<1],ans[i<<1|1]);
}
void dfs(int fath,int x,int llw=0){
	int cn=0;fa[x]=fath,lw[x]=llw;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fath){
			Son[e[i].v]=++cn;
			Modify1(rt[x],1,sz[x]*1ll*k,(col[e[i].v]-1ll)*sz[x]+Son[e[i].v],e[i].w);
			dfs(x,e[i].v,e[i].w);
		}
	Modify2(1,1,n,x,Min(Query1(rt[x],1,sz[x]*1ll*k,1,(col[x]-1ll)*sz[x]),
						Query1(rt[x],1,sz[x]*1ll*k,col[x]*1ll*sz[x]+1,sz[x]*1ll*k)));
}
int main(){
	int x,y,z;
	n=read(),m=read(),k=read(),q=read();
	for(int i=1;i<=m;i++)
		E[i].u=read(),E[i].v=read(),E[i].w=read(); 
	for(int i=1;i<=n;i++) f[i]=i,col[i]=read(); 
	sort(E+1,E+1+m,cmp),Kruscal(),dfs(0,1);
	while(q--){
		x=read(),y=fa[x],z=read();
		if(y){
			Modify1(rt[y],1,sz[y]*1ll*k,(col[x]-1ll)*sz[y]+Son[x],0);
			Modify1(rt[y],1,sz[y]*1ll*k,(z-1ll)*sz[y]+Son[x],lw[x]);
			Modify2(1,1,n,y,Min(Query1(rt[y],1,sz[y]*1ll*k,1,(col[y]-1ll)*sz[y]),
								Query1(rt[y],1,sz[y]*1ll*k,col[y]*1ll*sz[y]+1,sz[y]*1ll*k)));
		}col[x]=z;
		Modify2(1,1,n,x,Min(Query1(rt[x],1,sz[x]*1ll*k,1,(col[x]-1ll)*sz[x]),
							Query1(rt[x],1,sz[x]*1ll*k,col[x]*1ll*sz[x]+1,sz[x]*1ll*k)));
		printf("%d\n",ans[1]);
	}
	return 0;
} 
 ```

---

## 作者：louhao088 (赞：1)

非常好的线段树题

首先我们很容易发现答案在 MST 上，否则一定不是最优。

我们可以用动态开点线段树维护每个点连出去颜色的信息。

具体的，我们用一个 map 记录每种儿子每个颜色的编号，用 multiset 记录其一种颜色儿子的边的长度，把最短的放入线段树中维护，答案即为 $ [1,col[x]),(col[x],n]$ 这两段区间最小值。统计答案时只要用 multiset 维护每点的最小值，输出最小值即可。

对于修改操作，我们只需对其父亲的线段树进行修改，要注意在 multiset 中删除点。然后重新统计其父亲与其本身答案。最后再修改维护每点答案的 multiset 即可。

时间复杂度 $O(n\log n)$



------------
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=4e5+5,M=8e6+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,ls[M],rs[M],rt[maxn],k,q,Min[M],b[maxn],f[maxn],ans[maxn],tot,cnt,fa[maxn],g[maxn],x,y;
multiset<int>s[maxn],Ans;
map<int,int>id[maxn];
vector<pi>e[maxn];
struct node{int u,v,w;}a[maxn];
bool cmp(node a,node b){return a.w<b.w;}
int getf(int x){if(fa[x]==x)return x;return fa[x]=getf(fa[x]);}
void change(int &rt,int l,int r,int x,int num)
{
	if(l>x||r<x)return;
	if(!rt)rt=++tot;//cout<<rt<<" "<<l<<" "<<r<<endl;
	if(l==x&&r==x){Min[rt]=num;return;}
	change(ls[rt],l,mid,x,num);change(rs[rt],mid+1,r,x,num);
	Min[rt]=1e9;
	if(ls[rt])Min[rt]=min(Min[rt],Min[ls[rt]]);
	if(rs[rt])Min[rt]=min(Min[rt],Min[rs[rt]]);
}
int query(int rt,int l,int r,int L,int R)
{
	if(!rt)return 1e9;
	if(l>R||r<L)return 1e9;
	if(l>=L&&r<=R)return Min[rt];
	return min(query(ls[rt],l,mid,L,R),query(rs[rt],mid+1,r,L,R)); 
}
void dfs(int x,int fa)
{
	//cout<<x<<endl;
	f[x]=fa;
	for(auto i:e[x])
		if(i.fi^fa)
		{
			dfs(i.fi,x);g[i.fi]=i.se;
			if(!id[x][b[i.fi]])id[x][b[i.fi]]=++cnt;
			s[id[x][b[i.fi]]].insert(i.se);		
			change(rt[x],1,n,b[i.fi],*s[id[x][b[i.fi]]].begin());
		}
	ans[x]=min(query(rt[x],1,n,1,b[x]-1),query(rt[x],1,n,b[x]+1,n));
	Ans.insert(ans[x]);
}
signed main()
{
	//freopen("P3665_2.in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();k=read(),q=read();
	for(int i=1;i<=m;i++)
		a[i].u=read(),a[i].v=read(),a[i].w=read();
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i,b[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=getf(a[i].u),y=getf(a[i].v);
		if(x==y)continue;
		e[a[i].u].pb(mp(a[i].v,a[i].w)),e[a[i].v].pb(mp(a[i].u,a[i].w));
		fa[x]=y;
	}
	dfs(1,0);
	for(int i=1;i<=q;i++)
	{
		x=read(),y=read();Ans.erase(Ans.find(ans[x]));
	//	cout<<x<<" "<<y<<endl;
		if(x!=1)
		{
			int t=id[f[x]][b[x]];//cout<<t<<endl;
			s[t].erase(s[t].find(g[x]));//cout<<"A";
			Ans.erase(Ans.find(ans[f[x]]));
			if(s[t].empty())change(rt[f[x]],1,n,b[x],1e9);
			else change(rt[f[x]],1,n,b[x],*s[t].begin());
			b[x]=y;
			if(!id[f[x]][b[x]])id[f[x]][b[x]]=++cnt;
			t=id[f[x]][b[x]];s[t].insert(g[x]);change(rt[f[x]],1,n,b[x],*s[t].begin());
			ans[f[x]]=min(query(rt[f[x]],1,n,1,b[f[x]]-1),query(rt[f[x]],1,n,b[f[x]]+1,n));
			Ans.insert(ans[f[x]]);
		}
		b[x]=y;
		ans[x]=min(query(rt[x],1,n,1,b[x]-1),query(rt[x],1,n,b[x]+1,n));
		Ans.insert(ans[x]),printf("%d\n",*Ans.begin());
	}
 	return 0;
}


/*********************************************************************
    作者:louhao088
    日期: 2022-01-24 13:45
*********************************************************************/

```


---

