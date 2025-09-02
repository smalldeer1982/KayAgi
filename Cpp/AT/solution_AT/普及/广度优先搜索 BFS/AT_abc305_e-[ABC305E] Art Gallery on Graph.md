# [ABC305E] Art Gallery on Graph

## 题目描述

### 题面

给定一张 $N$ 个点（编号为 $1 \sim N$），$M$ 条边的无向图，保证无重边无自环。现在有 $K$ 个被标记的点，其中第 $i$ 个被标记的点的编号为 $p_i$，任何从 $p_i$ 出发经过不超过 $h_i$ 条边能到达的点都会被染色（包括 $p_i$ 自身）。你需要求出这张图最终有哪些点被染色。


接下来 $M$ 行，每行两个正整数 $a_i,b_i$，表示编号为 $a_i,b_i$ 的点连有一条无向边。

## 说明/提示

$1 \le N \le 2 \times 10^5$，$0 \le M \le 2 \times 10^5$，$1 \le K,a_i,b_i,p_i,h_i \le N$，$p_i$ 互不相同。

保证给定的图无重边，无自环。

## 样例 #1

### 输入

```
5 5 2
1 2
2 3
2 4
3 5
1 5
1 1
5 2```

### 输出

```
4
1 2 3 5```

## 样例 #2

### 输入

```
3 0 1
2 3```

### 输出

```
1
2```

## 样例 #3

### 输入

```
10 10 2
2 1
5 1
6 1
2 4
2 5
2 10
8 5
8 6
9 6
7 9
3 4
8 2```

### 输出

```
7
1 2 3 5 6 8 9```

# 题解

## 作者：MoyunAllgorithm (赞：6)

**题意**

给你 $N$ 点 $M$ 边的无向图 $(N,M \le 2 \times 10^5)$。有 $K(\le N)$ 个保安，对于第 $i$ 保安有信息 $p_i$ 和 $h_i$，代表它在 $p_i$ 号点，可以看守距离它不大于 $h_i$ 条边的结点。你需要求出有几个、有哪些节点被看守。

**分析**

这是类似于无边权最短路的问题，考虑 bfs。

如果从每个保安都开始 bfs，时间复杂度为 $O(NM)$，不可接受。

但是，**有这样一个性质**：对于一个结点而言，所有保安中，到它的**剩余距离**最大的才是有效的。什么意思？形式化地，对于 $u$ 点，对于 $[1,K]$ 的所有保安，对它而言最有效的保安 $i$ 满足 $h_i-\text{dis}(p_i,u)$ 最大。为什么？因为这具有后无效性，对于 $u$ 点，它从哪个点而来不影响结果，我们只需要关心如何让 $u$ 点搜到尽可能多的其它点。

用 `priority_queue` 代替 `queue` 进行 bfs。注意：`pair<int,int>` 以第一个元素为第一个关键字排序。也就是说，我们应该将 $h$ 放在 $p$ 前面，加入堆。这样，堆顶元素 $(x,y)$ 就代表 $y$ 点的最大**剩余距离**是 $x$。

时间复杂度显然为 $O(N+M)$，因为每个点都只会被一个保安更新。

```cpp
#include <bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
const int MAXN=2e5+5;
int N,M,K;
int h[MAXN],p[MAXN];
int vis[MAXN],dis[MAXN];
vector<int>gra[MAXN];
priority_queue<PII>heap;
void bfs()
{
	while(heap.size())
	{
		int step=heap.top().first,u=heap.top().second;
		heap.pop();
		//printf("BFS%d %d\n",u,step);
		if(vis[u]) continue;
		vis[u]=1;
		if(step==0) continue;
		for(auto v:gra[u])
		{
			if(vis[v]) continue;
			heap.push({step-1,v});
		}
	}
	return;
}
int main()
{
	scanf("%d %d %d",&N,&M,&K);
	for(int i=1;i<=M;i++) 
	{
		int u,v;
		scanf("%d %d",&u,&v);
		//scanf("%d %d",&v,&u);
		gra[u].push_back(v);
		gra[v].push_back(u);
	}
	for(int i=1;i<=K;i++)
	{
		int h,p;
		scanf("%d %d",&p,&h);
		heap.push({h,p});
	}
	bfs();
	int ans=0;
	for(int i=1;i<=N;i++) if(vis[i]) ans++;
	printf("%d\n",ans);
	for(int i=1;i<=N;i++) if(vis[i]) printf("%d ",i);
	return 0;
}
```




---

## 作者：Coffee_zzz (赞：5)

### 思路

首先很容易想出 $O(NK)$ 的朴素做法。此做法是将 $K$ 次搜索分开搜的，我们可以考虑将 $K$ 次搜索合并在一起。

对于每个节点 $u$，我们求出对于每一个 $1 \le i\le K$，$h_i-dis_{i,u}$ 的值，其中 $dis_{i,u}$ 表示节点 $i$ 和节点 $u$ 之间的距离。$\max\limits^K_{i=1} (h_i-dis_{i,u})$ 即每个节点 $u$ 可以向外拓展的步数。

容易发现只有最大值是有用的，所以对于每个节点 $u$，我们只需要求出 $h_i-dis_{i,u}$ 的最大值。不难想到使用 BFS 的变形解决。

我们每次取队列中向外拓展步数最多的点，对所有与它之间有连边的点进行遍历，这样可以保证取到的一定是最大值。所有被遍历到的点即最终的答案。

要注意给定的 $K$ 个点中，有些节点 $u$ 的 $h_u$ 不一定是 $\max\limits^K_{i=1} (h_i-dis_{i,u})$，所以不能在一开始就打上标记。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int N=2e5+5;
int n,m,k,to[N<<1],nxt[N<<1],p[N],h[N],head[N],cnt;
bool vis[N];
void add(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
priority_queue <pair<int,int> > q;
signed main(){
	int u,v,g;
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++) u=read(),v=read(),add(u,v),add(v,u);
	for(int i=1;i<=k;i++) p[i]=read(),h[i]=read(),q.push({h[i],p[i]});
	while(!q.empty()){
		u=q.top().second,g=q.top().first,q.pop();
		vis[u]=1;
		if(g==0) continue;
		for(int i=head[u];i;i=nxt[i]){
			v=to[i];
			if(vis[v]) continue;
			vis[v]=1;
			q.push({g-1,v});
		}
	}
	int tmp=0;
	for(u=1;u<=n;u++) if(vis[u]) tmp++;
	cout<<tmp<<endl;
	for(u=1;u<=n;u++) if(vis[u]) cout<<u<<' ';
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc305_e)         
简单图论，但是我赛时因为大于号打成小于号导致丢了这道题的分，失去了上大分的机会。     
## 题意    
给你一张无向简单图，我们要在上面布设 $k$ 个警卫。     
第 $i$ 个警卫位于 $p_i$，可以看守和它最短距离不超过 $h_i$ 的所有结点。      
求最后有多少个结点被看守并且看守的结点是哪几个。   
## 解法    
我们可以对于每一个警卫做“发散”操作。    
“发散”操作指把其的状态转移到它所有的子结点上，之后子结点继续转移。    
转移的量有两个，$p$ 和 $h$，和题意意义一样。    
转移时，我们需要让 $h$ 减一。       
这里补充一个关键结论：$h$ 越大越好。      
所以我们可以用一个数组来维护。     
设 $d_i$ 为第 $i$ 个结点被访问时所传递过来的 $h$ 最大值。我们遍历时套上这个内容即可。     
我们可以使用 dfs 实现，但是 dfs 做不到每次都最大化 $h$，因此这么做会 TLE。     
每次都最大化 $h$，我们可以想到一个常用的 STL——优先队列。     
我们使用优先队列实现即可。        
我们可以给被扫到的结点打标记，最后遍历输出。     
[CODE](https://www.luogu.com.cn/paste/emaxqksd)

---

## 作者：luogu_gza (赞：1)

暴力是 $O(nk)$ 的。

考虑暴力，但是优化。

一个点的监控等级是 $k$ ，与其相邻的点的监控等级就是 $k-1$。

求出每一个点的监控等级，当当前点的当前监控等级大于目前搜索的点的监控等级时，**就不用继续搜索了。**

注意，这样的算法会被链的特殊数据卡到 $O(n^2)$。

所以，按照 $k$ 从大到小看一遍。

[$\texttt{\color{green}{AC\ code}}$](https://atcoder.jp/contests/abc305/submissions/42155103)

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc305_e)

#### 前言

挺好想的题，赛时打错了。

#### 题目大意

给出一个 $N$ 个点，$M$ 条边的简单无向图，有 $K$ 个守卫，每个守卫在 $p_i$，守护距离为 $h_i$，当第 $j$ 个点到第 $p_i$ 个点的最短距离小于等于 $h_i$，则称第 $j$ 个点可以被保护，输出共有几个点被保护，然后升序输出每个被保护的点。

#### 思路

由于是要尽可能多的点被保护，所以我们希望到达每个点后剩余距离能到达的点尽可能多，例如有两个点都能更新同一个点，但一个剩余保护距离是 $10$，一个是 $4$，那么我们应该让保护距离是 $10$ 的来更新这个点，所以可以用优先队列将其按剩余保护距离排序，然后套一个最短路，改一下就可以了。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,v[400010],l,ans,bj[400010];
vector<int>w[400010];
struct www
{
	int id,jl;
	bool operator < (const www & a) const {return a.jl > jl;}//重在运算符，按剩余保护距离排序 
};
priority_queue<www>kk;
void bfs()
{
	while(!kk.empty())
	{
		www oo = kk.top();
		l = oo.id;//取出编号 
		kk.pop();
		if(v[l] - 1 < 0 || bj[l]) continue;//超出保护距离或已经被更优的便利过了 
		bj[l] = 1;
		for(int i = 0;i < w[l].size();i++)
		{
			if(v[w[l][i]] < v[l] - 1)//比最优的优 
			{
				v[w[l][i]] = v[l] - 1;
				kk.push((www){w[l][i],v[w[l][i]]});
			}
		}
		
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= n;i++) v[i] = -100;
	while(m--)
	{
		scanf("%d%d",&x,&y);
		w[x].push_back(y);
		w[y].push_back(x);
	}
	for(int i = 1;i <= k;i++) 
	{
		scanf("%d%d",&x,&y);
		kk.push(www{x,y});//插入队列 
		v[x] = y;
	}
	bfs();
	for(int i = 1;i <= n;i++)  if(v[i] != -100) ans++;
	printf("%d\n",ans);
	for(register int i = 1;i <= n;i++)  if(v[i] != -100) printf("%d ",i);
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## 分析

我们可以将保安的能力值转化为点权。那么在某个点的点权大于等于 $1$ 时，就表示跟这个点相连的点都能够被保护，且它们的点权都不小于这个点的点权减 $1$，因为别的点也可能改变这个点的点权，也有可能更大。为了使保护到的点更多，我们需要让所有点的点权尽量大，所以需要取最大值。找最大值，可以转化成求 dijkstra 最长路，也就是把点变成边（点权赋给边，暂存在点上）。最后，如果一个点能被保护，那么它在求最长路时就会被标记，所以我们直接输出所有被标记的点即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
int n,m,k;
const int N=1e6+10;
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[idx]=h[a],e[idx]=b,h[a]=idx++;
}
int u,v;
int p[N],hk[N];
int dis[N];
priority_queue<PII> qu;
bool vis[N];
bool viss[N];
signed main(){
	memset(dis,-1,sizeof(dis));
	cin>>n>>m>>k;
	memset(h,-1,sizeof(h));
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	for(int i=1;i<=k;i++){
		cin>>p[i]>>hk[i];
		dis[p[i]]=max(dis[p[i]],hk[i]);//取最大值 
	}
	for(int i=1;i<=k;i++){//每个保安所在的点都放进去 
		if(!viss[p[i]]){//判断重复 
			viss[p[i]]=1;
			qu.push({dis[p[i]],p[i]});
		}
	}
	while(!qu.empty()){
		PII now=qu.top();
		qu.pop();
		if(vis[now.y]) continue;
		vis[now.y]=1;
		if(now.x>=1){ 
			for(int i=h[now.y];~i;i=ne[i]){
				int j=e[i];
				if(dis[j]<now.x-1){
					dis[j]=now.x-1;
					qu.push({dis[j],j});
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i]){
			ans++;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(vis[i]){
			cout<<i<<" ";
		}
	}
	return 0; 
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这个有一个比较简单的思路，赛事并没有卡掉。

我们对于每一次操作进行广搜，对于每一个搜到的节点取 $\max$，如果这个点的值被更新了，那么就加入队列，但这样会被卡到 $O(NK)$，我们考虑可以将每个点的值排一遍序，那么就能够不会卡到那么多。

但是赛后的一个点还是卡不过。

我们考虑这里的时间耗费主要是有重复的，我们可以考虑全部加进优先队列里然后进行广搜。

我们这样就可以保证只会遍历 $N$ 个点。

这样就可以通过这道题了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
priority_queue<pair<int, int>> qp;
int mp[maxn], ans;
vector<int> e[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	memset(mp, -1, sizeof mp);
	for (int i = 1; i <= k; i++) {
		int p, h;
		cin >> p >> h;
		mp[p] = h;
		qp.push({h, p});
	}
	while (qp.size()) {
		auto [h, p] = qp.top();
		qp.pop();
		if (mp[p] <= h) {
			mp[p] = h;
			for (int v : e[p]) {
				if (mp[v] < h - 1) {
					mp[v] = h - 1;
					qp.push({h - 1, v});
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (mp[i] >= 0) {
			++ans;
		}
	}
	cout << ans << "\n";
	for (int i = 1; i <= n; i++) {
		if (mp[i] >= 0) {
			cout << i << " ";
		}
	}
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

> [Art Gallery on Graph の 传送门](https://www.luogu.com.cn/problem/AT_abc305_e)

> [更杂乱的阅读体验](https://www.cnblogs.com/Silver-Wolf/p/ABC305E.html)

## Problem

有一个由 $N$ 个点 $M$ 边的简单无向图，顶点编号为 $1$ 到 $N$，边的编号为 $1$ 到 $M$。

第 $i$ 条边连接着点 $a_i$ 和 $b_i$。

在一些点上有编号为 $1$ 到 $K$ 的 $K$ 个守卫。

守卫 $i$ 位于顶点 $p_i$，保护范围为 $h_i$。（这里所有的 $p_i$ 都是相互不同的）

如果一个点 $v$ 满足以下条件，则称为**被保护的点**。

- 至少存在一个守卫 $ i $，使得点 $ v $ 与点 $ p_i $ 之间的距离小于或等于 $ h_i $。
 
顶点 $ u $ 和顶点 $ v $ 之间的距离是连接顶点 $ u $ 和顶点 $ v $ 的路径上的最小边数。

输出所有被保护的顶点，**顺序是从小到大**。

## Solution

因为 $i$ 号守卫可以保护距离不超过 $h_i$ 的点，所以考虑定义 $f_i$ 为 $i$ 点可以保护的距离。

初始化：

1. 将 $f$ 全赋为 $-1$；
2. 把每个守卫的 $f$ 值设为 $h_i$。

然后从 $1$ 点开始 BFS，对于当前点 $u$，遍历 $u$ 连的点 $v$。

然后用 `f[u] - 1` 更新 $f_v$，如果更新成功，就将 $v$ 加入处理用来处理的优先队列 $q$。

$q$ 要从大到小的顺序，因为每次更新都是把当前点 $u$ 的 $f$ 值减少，为了尽量让 $f_u$ 更大以更新更多的点，应让 $q$ 从大到小。

特殊的，如果当前点 $u$ 的 $f_u \le 0$ 时，$u$ 就对答案没有贡献，所以直接 `continue`。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define int long long
#define pi pair<int,int>
#define mk make_pair
#define w first
#define v second
const int N = 2e5 + 5;
int n, m, k;
int vis[N], dis[N];
vector<int> g[N];
vector<int> ans;
priority_queue<pi> q;
signed main() {
    cin >> n >> m >> k;
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dis, -1, sizeof(dis));
    while (k--) {
        int u, w;
        cin >> u >> w;
        dis[u] = w;
        q.push(mk(w, u));
    }
    while (!q.empty()) {
        int v = q.top().v;
        q.pop();
        for (int i : g[v])
            if (dis[i] < dis[v] - 1) {
                dis[i] = dis[v] - 1;
                q.push(mk(dis[i], i));
            }
    }
    for (int i = 1; i <= n; ++i)
        if (dis[i] >= 0)	ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i : ans)   cout << i << ' ';
    return 0;
}
```

---

