# [ICPC 2019 WF] Dead-End Detector

## 题目描述

你所在家乡的市政委员会决定改善道路标志的设置，特别是对于死胡同的标志。他们给了你一张道路地图，你需要确定在哪里设置标志来标记死胡同。他们希望你使用尽可能少的标志。

这张道路地图是由通过双向街道连接的多个地点组成的。以下规则描述了如何完成死胡同标志的设置。考虑一条街道 $S$ 连接地点 $x$ 和另一个地点。如果从 $x$ 进入 $S$ 后，无法在不掉头的情况下返回 $x$，则在 $S$ 的 $x$ 入口处设置一个死胡同标志。掉头是指立即反向的 180 度转弯。

为了节省成本，你决定不安装冗余的死胡同标志，具体规则如下。考虑一条在 $x$ 入口处有死胡同标志的街道 $S$ 和另一条在 $y$ 入口处有死胡同标志的街道 $T$。如果从 $x$ 进入 $S$ 后，可以在不掉头的情况下到达 $y$ 并进入 $T$，那么 $T$ 的 $y$ 入口处的死胡同标志是冗余的。参见图 E.1 以获取示例。

![](https://cdn.luogu.com.cn/upload/image_hosting/33rn5okp.png)

图 E.1：示例输入的说明，指示放置非冗余死胡同标志的位置。

## 说明/提示

来源：ICPC 世界总决赛 2019 问题 E。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 5
1 2
1 3
2 3
4 5
5 6
```

### 输出

```
2
4 5
6 5```

## 样例 #2

### 输入

```
8 8
1 2
1 3
2 3
3 4
1 5
1 6
6 7
6 8
```

### 输出

```
3
1 5
1 6
3 4
```

# 题解

## 作者：StudyingFather (赞：13)

对于每个连通分量分两种情况来讨论。

### 连通分量是一棵树

此时按题目要求，从任何一个点出发选任何一条边都是死路。但事实上，只需要在叶节点处标记从叶节点出发的边即可（这些标记已经可以完整覆盖所有死路了）。

### 连通分量不是一棵树

这种情况下，如果一条 $u \to v$ 边满足其被割断后图分为两个连通分量，且 $v$ 所在连通分量是一棵树，那么就可以在 $u$ 入口处安装标记。

这样可能会存在重复覆盖的情况，我们可以这样做：逐步删除所有叶子节点，直到无法再删为止，那么从没被删的点 $u$ 到被删的点 $v$ 之间就是死路。

这个标记完整覆盖了 $v$ 所处的子树，从而避免了不必要的标记。

```cpp
// Problem : P6255 [ICPC2019 WF]Dead-End Detector
// Contest : Luogu Online Judge
// URL : https://www.luogu.com.cn/problem/P6255
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 1000 MB
// Time Limit : 5000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
int t[500005],vis[500005];
vector<int> e[500005],l,p[500005];
vector<pair<int,int> > res;
queue<int> q;
set<int> s;
void dfs(int u)
{
 vis[u]=1;
 s.insert(u);
 if(t[u]==1)
 {
  q.push(u);
  l.push_back(u);
 }
 for(auto v:e[u])
  if(!vis[v])
   dfs(v);
}
int main()
{
 ios::sync_with_stdio(false);
 int n,m;
 cin>>n>>m;
 for(int i=1;i<=m;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
  t[u]++,t[v]++;
 }
 for(int i=1;i<=n;i++)
  if(!vis[i])
  {
   s.clear();
   l.clear();
   dfs(i);
   while(!q.empty())
   {
    int u=q.front();
    q.pop();
    s.erase(u);
    for(auto v:e[u])
    {
     t[v]--;
     if(t[v]==1)q.push(v);
    }
   }
   if(s.empty())
    for(auto u:l)
     res.push_back({u,e[u].front()});
   else
    for(auto u:s)
     for(auto v:e[u])
      if(!s.count(v))
       res.push_back({u,v});
  }
 sort(res.begin(),res.end());
 cout<<res.size()<<endl;
 for(auto p:res)
  cout<<p.first<<' '<<p.second<<endl;
 return 0;
}
```

---

## 作者：比利♂海灵顿 (赞：6)

# P6255 ICPC2019 WF Dead-End Detector

想当年这道题被选为校内 ACM 赛前训练，结果是历城二中 57 级全灭，全场三个队，只有有一个队有分，并且只有一道题，非常惨烈，今天重新审视这道题，发现当时水平确实太低。

## 题意

这题题意比较绕，场上对题意也是一知半解，感到迷茫的话可以好好研究样例。

一个无向图，给死路的起点打标记，死路定义为从起点经过这条边后，无法不掉头走回起点。一条死路如果被一条有标记的死路不掉头地到达，那么这个死路的标记便不必打，求最少的标记数量和标记位置。

## 解法

首先，边双连通分量中的边一定不是死路，所以先缩点，考虑边双构成的树的树边即可。

我们发现，可以把问题转化为打 Tag 和删 Tag 两步，而这两个阶段是互不干扰的，也就是说我们可以先打 Tag，然后考虑如何删除多余的 Tag 即可。

说明这个结论，因为死路的定义是确定的，所以无论如何删除 Tag，一条路该是死路仍然是死路，所以打 Tag 删 Tag 互不影响。

## 删 Tag

因为删 Tag 需要的是有打 Tag 的边能不掉头经过这条边。能经过一条边也就是能经过这条边的起点，所以我们对于一个点讨论是否存在有这种边连入即可。

这个时候可能就会产生问题，就是删除 Tag 之后，原本连入某个点的有 Tag 的边的 Tag 被删除后，这条边的 Tag 就不能被删除了。但是，我们知道能否到达是可以传递的，所以如果有一条边的 Tag 被删除，它删除的 Tag 的正确性不会受到影响，所以我们对每次打 Tag，将终点记录一个 Deleted 标记，最后将有标记的所有点的出边的 Tag 都删掉即可。

但是有一种情况比较特殊，就是一条入边不能删除自己的回边的标记，这时因为走了入边再走回边就相当于是掉头了，但是如果有多个带 Tag 的入边，就无需考虑这个问题，因为多条入边的回边可以相互被删除。这些情况每个点记录一个唯一带 Tag 入边的地址，特判一下即可。

```cpp
void Del(BCC* x) {
  EdgeB* Sid(x->Fst);
  while (Sid) { if (Sid != x->Dont) Sid->Deleted = 1; Sid = Sid->Nxt; }
}
```

值得注意的是：不能每次入边连进来就执行这个操作，必须离线处理，因为缩点之后是菊花图的数据可以卡到 $O(n^2)$，打标记，最后统一删除可以保证每个点只回遍历一次它的连边。

## 打 Tag

我们发现，一条路径只要能通向一个非节点的双连通分量，在这个双连通分量里绕一圈，就可以不掉头地从原地反向出来。这个结论是接下来打 Tag 的基础。

对于一个连通块，随便找一个点为根，然后将边分成两类，连向父亲和连向儿子。

对于连向儿子的边，如果儿子的子树中有非节点的边双，那么不用打 Tag。如果没有，则说明这走条边后没法不掉头回到起点，则给连向儿子的边打 Tag。

如下是代码：

```cpp
void DFSFall(BCC* x) {
  EdgeB* Sid(x->Fst);
  x->SubTree = x->Turn;
  while (Sid) {
    if (Sid->To != x->Fa) {
      DFSFall(Sid->To), x->SubTree |= Sid->To->SubTree;
      if (!(Sid->To->SubTree)) {
        Sid->Ava = 1;
        if (Sid->To->Dont) Sid->To->Dont = EB + 0x3f3f3f3f;
        else Sid->To->Dont = EB + ((Sid - EB) ^ 1);
        Sid->To->Deleted = 1;
      }
    }
    Sid = Sid->Nxt;
  }
}
```

然后是儿子连父亲的边，这种边需要讨论不打 Tag 的情况。

第一种是经过父亲往上走，能走到至少一个非节点边双，对于每个父亲，这种情况可以 DFS 过程中统计。

第二种情况，注意第二种情况都是建立在前面所说的情况不存在的前提下的。这时父亲存在儿子，它的子树中至少一个非节点边双。

第二种情况还需要讨论子树存在非节点边双的儿子的数量，当父亲只有一个儿子子树中存在非节点边双，则除了这个儿子以外都可以不打 Tag，但是需要在父亲连向这个特定的儿子的边上打 Tag。当有大于一个儿子的子树中有非节点边双，则按第一种情况处理即可。

接下来是程序实现：

```cpp
void DFSRise(BCC* x) {
  BCC* Son(NULL);
  EdgeB* Sid(x->Fst);
  char More(0);
  while (Sid) {
    if ((Sid->To != x->Fa) && (Sid->To->SubTree)) More = (Son ? 1 : 0), Son = Sid->To;
    Sid = Sid->Nxt;
  }
  Sid = x->Fst;
  if (More || (x->Turn)) {
    while (Sid) {
      if (Sid->To != x->Fa) Sid->To->Turn = 1, DFSRise(Sid->To);
      Sid = Sid->Nxt;
    }
    return;
  }
  if (!Son) {
    while (Sid) {
      if (Sid->To != x->Fa) {
        DFSRise(Sid->To), EB[((Sid - EB) ^ 1)].Ava = 1, x->Deleted = 1;
        if (x->Dont) x->Dont = EB + 0x3f3f3f3f; else x->Dont = Sid;
      }
      Sid = Sid->Nxt;
    }
    return;
  }
  while (Sid) {
    if (Sid->To != x->Fa) {
      if (Sid->To == Son) {
        DFSRise(Sid->To), EB[((Sid - EB) ^ 1)].Ava = 1, x->Deleted = 1;
        if (x->Dont) x->Dont = EB + 0x3f3f3f3f; else x->Dont = Sid;
      }
      else Sid->To->Turn = 1, DFSRise(Sid->To);
    }
    Sid = Sid->Nxt;
  }
}
```

## 代码

接下来的内容就是人尽皆知的 Tarjan 了，直接缩点即可。

接下来给出代码省略缺省源的其余部分：

```cpp
unsigned m, n, M;
unsigned A, C, D, t;
unsigned Cnt(0), Top(0), CntRoot(0), CntPrt(0);
struct Node;
struct BCC;
struct Edge {
  Node* To;
  Edge* Nxt;
}E[1000005];
struct EdgeIO {
  unsigned Frm, To;
  const inline char operator <(const EdgeIO& x) const { return (this->Frm ^ x.Frm) ? (this->Frm < x.Frm) : (this->To < x.To); }
}IO[1000005];
struct EdgeB {
  BCC* To;
  EdgeB* Nxt;
  EdgeIO UsedTo;
  char Ava, Deleted;
}EB[1000005];
struct BCC {
  BCC* Fa;
  EdgeB* Fst, * Dont;
  char Turn, SubTree, Deleted;
}B[500005], * Root[500005], * CntB(B);
struct Node {
  Edge* Fst;
  BCC* Bel;
  unsigned DFSr, Low;
}N[500005], * Stack[500005];
void Link(Node* x) {
  Edge* Sid(x->Fst);
  while (Sid) {
    if (Sid->To->Bel) {
      if (Sid->To->Bel < x->Bel) {
        EB[Cnt].UsedTo.Frm = x - N, EB[Cnt].UsedTo.To = Sid->To - N;
        EB[Cnt].Nxt = x->Bel->Fst, x->Bel->Fst = EB + Cnt, EB[Cnt++].To = Sid->To->Bel;
        EB[Cnt].UsedTo.Frm = Sid->To - N, EB[Cnt].UsedTo.To = x - N;
        EB[Cnt].Nxt = Sid->To->Bel->Fst, Sid->To->Bel->Fst = EB + Cnt, EB[Cnt++].To = x->Bel;
        Sid->To->Bel->Fa = x->Bel;
      }
    }
    Sid = Sid->Nxt;
  }
}
void Shrink(Node* x, Edge* No) {
  x->Low = x->DFSr = ++Cnt, Stack[++Top] = x;
  Edge* Sid(x->Fst);
  while (Sid) {
    if (Sid != No) {
      if (!(Sid->To->DFSr)) Shrink(Sid->To, E + ((Sid - E) ^ 1)), x->Low = min(x->Low, Sid->To->Low);
      else x->Low = min(x->Low, Sid->To->Low);
    }
    Sid = Sid->Nxt;
  }
  if (x->DFSr == x->Low) {
    ++CntB, CntB->Turn = (Stack[Top] != x);
    do { Stack[Top]->Bel = CntB; } while (Stack[Top--] != x);
  }
}
signed main() {
  n = RD(), m = RD(), M = (m << 1);
  for (unsigned i(0); i < m; ++i) IO[i].Frm = RD(), IO[i].To = RD();
  sort(IO, IO + m);
  for (unsigned i(0); i < M; i += 2) {
    C = IO[i >> 1].Frm, D = IO[i >> 1].To;
    E[i].Nxt = N[C].Fst, N[C].Fst = E + i, E[i].To = N + D;
    E[i ^ 1].Nxt = N[D].Fst, N[D].Fst = E + (i ^ 1), E[i ^ 1].To = N + C;
  }
  for (unsigned i(1); i <= n; ++i) if (!(N[i].DFSr)) Shrink(N + i, NULL), Root[++CntRoot] = CntB;
  Cnt = 0;
  for (unsigned i(1); i <= n; ++i) Link(N + i);
  for (unsigned i(1); i <= CntRoot; ++i) DFSFall(Root[i]), DFSRise(Root[i]);
  for (BCC* i(B + 1); i <= CntB; ++i) if (i->Deleted) Del(i);
  for (unsigned i(0); i < Cnt; ++i) if (EB[i].Ava && (!EB[i].Deleted)) IO[++CntPrt] = EB[i].UsedTo;
  sort(IO + 1, IO + CntPrt + 1);
  printf("%u\n", CntPrt);
  for (unsigned i(1); i <= CntPrt; ++i) printf("%u %u\n", IO[i].Frm, IO[i].To);
  system("pause");
  return Wild_Donkey;
}
```


---

## 作者：lgswdn_SA (赞：2)

考虑两种不同的情况。

1. 连通块是一棵树

在每个度为 1 的节点处装上即可。

2. 连通块不是一棵树

那么 $s\to t$ 是 non-rebundant dead-end 当且仅当割掉这条边后 $t$ 所在的连通分量是树且 $s$ 是环上点（否则是 rebundant）。

我们找到所有环上点（用类似于拓扑排序）即可。

具体操作就是我们把一个点删除的条件从有向图的度为 $0$ 改成度为 $1$，然后做一边这样的拓扑排序即可。然后如果一条边 $(s,t)$ 满足 $s$ 没有被删除且 $t$ 被删除了那么 $s\to t$ 就是一个 non-rebundant dead-end。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+9;
typedef pair<int,int> pii;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,su[N],sv[N],id[N],sz[N],tot[N],deg[N];
vector<int>e[N],c[N];
vector<pii>ans;

int find(int i) {return id[i]==i?i:id[i]=find(id[i]);}
void add(int u,int v) {
	e[u].push_back(v), e[v].push_back(u);
	id[find(u)]=find(v);
	deg[u]++, deg[v]++;
}

void topo(int u) {
	queue<int>q;
	for(auto v:c[u]) if(deg[v]==1) q.push(v);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(auto v:e[u]) {
			deg[v]--;
			if(deg[v]==1) q.push(v);
		}
	}
}

int main() {
	n=read(), m=read();
	rep(i,1,n) id[i]=i;
	rep(i,1,m) add(su[i]=read(),sv[i]=read());
	rep(i,1,n) sz[find(i)]++, c[id[i]].push_back(i);
	rep(i,1,m) tot[id[su[i]]]++;
	rep(i,1,n) if(id[i]==i) {
		if(tot[i]==sz[i]-1) {
			for(auto u:c[i]) if(deg[u]==1) ans.push_back(pii(u,e[u][0]));
		} else {
			topo(i);
			for(auto u:c[i]) if(deg[u])
				for(auto v:e[u]) if(deg[v]==1) ans.push_back(pii(u,v));
		}
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(auto x:ans) printf("%d %d\n",x.first,x.second);
	return 0;
}
```

---

## 作者：Provicy (赞：1)

$\text{Problem}:$[题目链接](https://codeforces.com/gym/102511/problem/E)

$\text{Solution}:$

考虑从 $u$ 出发能回到 $u$，说明 $u$ 点一定在环上。如果 $u\rightarrow v$ 后必须掉头才能回到 $u$，则说明将 $u\rightarrow v$ 这条无向边断掉，$v$ 所在的连通块是无环的。无向图连通块无环，$v$ 所在的连通块是一个树。

那么只需要将原图所有在环上的点保留下来，将环上点和相邻的非环上点之间标记路标即可。具体的，从所有 $deg_{x}=1$ 的点出发，类似于拓扑排序的方法进行 $BFS$。

对于连通块是一个树的情况，显然的，在所有度为 $1$ 的节点的处标记路标就可以包含所有情况，特殊处理即可。

$\text{Code}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=500010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,m,book[N],vis[N],deg[N],d[N];
int head[N],maxE; struct Edge { int nxt,to; }e[N<<1];
inline void Add(int u,int v) { e[++maxE].nxt=head[u]; head[u]=maxE; e[maxE].to=v; }
vector<int> g;
vector<pair<int,int> > ans;
void DFS(int x)
{
	book[x]=1, g.eb(x);
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		deg[x]++;
		if(book[v]) continue;
		DFS(v);
	}
}
inline void BFS()
{
	if((int)g.size()<=1) return;
	queue<int> Q;
	for(auto i:g)
	{
		d[i]=deg[i];
		if(deg[i]==1) Q.push(i);
	}
	int cnt=0;
	while(!Q.empty())
	{
		int x=Q.front(); Q.pop();
		for(ri int i=head[x];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(vis[v]) continue;
			deg[v]--, deg[x]--;
			if(deg[v]==1) Q.push(v);
		}
		if(!deg[x]) vis[x]=1, cnt++;
	}
	if(cnt==(int)g.size())
	{
		for(auto i:g) if(d[i]==1)
		{
			for(ri int j=head[i];j;j=e[j].nxt)
			{
				int v=e[j].to;
				ans.eb(mk(i,v));
			}
		}
		return;
	}
	for(auto i:g)
	{
		if(vis[i]) continue;
		for(ri int j=head[i];j;j=e[j].nxt)
		{
			int v=e[j].to;
			if(vis[v]) ans.eb(mk(i,v));
		}
	}
}
signed main()
{
	n=read(), m=read();
	for(ri int i=1;i<=m;i++)
	{
		int u,v;
		u=read(), v=read();
		Add(u,v), Add(v,u);
	}
	for(ri int i=1;i<=n;i++)
	{
		if(book[i]) continue;
		g.clear();
		DFS(i), BFS();
	}
	printf("%lld\n",(int)ans.size());
	sort(ans.begin(),ans.end());
	for(auto i:ans) printf("%lld %lld\n",i.fi,i.se);
	return 0;
}
```



---

