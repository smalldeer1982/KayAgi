# [NEERC 2017] Connections

## 题目描述

艰难的时刻即将降临到 Byteland。量子计算正在成为主流，而 Qubitland 即将占领 Byteland。主要问题是 Byteland 没有足够的资金来进行这场战争，因此 Byteland 的国王 Byteman $0x0B$ 决定改革其道路系统以减少开支。

Byteland 有 $n$ 个城市，通过 $m$ 条单向道路连接，可以通过这些道路从任何城市到达其他城市。没有两条道路在城市外相交，也不存在其他道路。顺便说一下，道路是单向的，因为每条道路都有一个只能单向通过的中途障碍。这些障碍旨在迫使敌人在选择错误的方向时浪费时间。

即将到来的道路改革的想法是废弃一些道路，使得恰好剩下 $2n$ 条道路。国王的顾问认为这应该足以保持从任何城市到任何其他城市的通行能力。（也许更少也够？他们不确定。）问题是如何选择要废弃的道路。Byteland 的每个人都知道你是唯一能解决这个问题的人。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
4 9
1 2
1 3
2 3
2 4
3 2
3 4
4 1
4 2
4 3
```

### 输出

```
1 3
```

# 题解

## 作者：wgyhm (赞：3)

## [NEERC2017]Connections

### Description

给定一个 $n$ 点有向图，要求保留 $2n$ 条边使得强连通关系不变，输出删去的边。多测。

### Solution

先把强连通分量用 tarjan 跑出来。

* 连接两个强连通分量的不需要保留
* 对于其他的边，在一个强连通分量内部随便找个点 $x$，只要每个点与 $x$ 联通，那么其它点就可以经过 $x$ 到达所有点。所以只要对于 $x$ 分别跑个内向树和外向树，树边保留。
* 如果还没满 $2*n$ ，那么随便选几条就好。

多测不清空，$\_\_\_\_\_\_$。

code:

```cpp
#include<bits/stdc++.h>
#define maxn 200005
#define ll long long
#define put() putchar('\n')
using namespace std;
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	x*=f;
}
int n,m;
int stac[maxn],vis[maxn],scc[maxn],sccnum,tot,times;
int dfn[maxn],low[maxn],head=1,h[maxn],hh[maxn];
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[maxn*2];
struct node{
	int to,z;
	inline void add(int x,int y){
		to=y;z=hh[x];hh[x]=head;
	}
}e[maxn*2];
inline void tarjan(int x) {
	int i;
	vis[x]=1;dfn[x]=low[x]=++times;stac[++tot]=x;
    for (i=h[x];i;i=a[i].z) 
        if (!dfn[a[i].to]) tarjan(a[i].to),low[x]=min(low[a[i].to],low[x]);
		else if (vis[a[i].to]) low[x]=min(low[x],dfn[a[i].to]);
	if (low[x]==dfn[x]) {
		++sccnum;
		while (1) {
			vis[stac[tot]]=0;
			scc[stac[tot]]=sccnum;
			if (stac[tot--]==x) return; 
		}
	}
}
int flag[maxn];
inline void dfs1(int x) {
	int i;vis[x]=1;
	for (i=h[x];i;i=a[i].z)
	    if (!vis[a[i].to]&&scc[a[i].to]==scc[x]) 
	        flag[i]=1,dfs1(a[i].to);
}
inline void dfs2(int x) {
	int i;vis[x]=1;
	for (i=hh[x];i;i=e[i].z)
	    if (!vis[e[i].to]&&scc[e[i].to]==scc[x]) 
	        flag[i]=1,dfs2(e[i].to);
}
inline void solve(void) {
	int i,x,y;
    read(n);read(m);
    sccnum=times=0;head=0;
    for (i=1;i<=n;i++) {
    	h[i]=hh[i]=dfn[i]=stac[i]=low[i]=scc[i]=vis[i]=0;
	}
	for (i=1;i<=m;i++) flag[i]=0;
    for (i=1;i<=m;i++) {
    	read(x);read(y);
    	a[++head].add(x,y);
    	e[head].add(y,x);
	}
	for (i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
	for (i=1;i<=n;i++) vis[i]=0;
	for (i=1;i<=n;i++) if (!vis[i]) dfs1(i);
	for (i=1;i<=n;i++) vis[i]=0;
	for (i=1;i<=n;i++) if (!vis[i]) dfs2(i);
	int total=0;
	for (i=1;i<=m;i++) total+=flag[i];
	for (i=1;i<=m;i++)
	    if (flag[i]) ;
	    else if (total<2*n) total++;
	    else printf("%d %d\n",e[i].to,a[i].to);
}
signed main(void){
    int T;
    read(T);
    while (T--) solve();
	return 0;
}
```

 

---

## 作者：juju527 (赞：1)

### 题意
对于一个 $n$ 点有向图，要求保留 $2n$ 条边使得强连通关系不变
### $\texttt{Solution}$
考虑先进行强连通分量缩点

对于不同强连通分量之间的边显然没必要保留

我们仅考虑同scc内边该如何保留

对于一个大小为 $c$ 的强连通分量，我们保留至多 $2c$ 条边即可满足条件

想到生成树

我们任意以scc内一点跑内向、外向两棵生成树，记该点为 $u$

由于强连通，显然存在这两棵生成树

考虑对于scc内任意点 $v$，显然 $v\to u,u\to v$ 分别在两棵生成树上

故保留两棵生成树上的边即可，仅需 $2c-2$ 条边

时间复杂度 $O(n)$

[code](https://www.luogu.com.cn/paste/gg2wvowc)

---

