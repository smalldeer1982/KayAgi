# [ARC061E] すぬけ君の地下鉄旅行

## 题目描述

Snuke的城镇有地铁行驶，地铁线路图包括 $N$ 个站点和 $M$ 个地铁线。站点被从 $1$ 到 $N$ 的整数所标记，每条线路被一个公司所拥有，并且每个公司用彼此不同的整数来表示。

第 $i$ 条线路( $1≤i≤M$ )是直接连接 $p_i$ 与 $q_i$ 的双向铁路，中间不存在其他站点，且这条铁路由 $c_i$ 公司所拥有。

如果乘客只乘坐同一公司的铁路，他只需要花费一元，但如果更换其他公司的铁路需要再花一元。当然，如果你要再换回原来的公司，你还是要花一元。

Snuke在1号站的位置出发，他想通过地铁去第 $N$ 站，请求出最小钱数。如果无法到达第 $N$ 站，输出-1。

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
8 11
1 3 1
1 4 2
2 3 1
2 5 1
3 4 3
3 6 3
3 7 3
4 8 4
5 6 1
6 7 5
7 8 5```

### 输出

```
2```

## 样例 #3

### 输入

```
2 0```

### 输出

```
-1```

# 题解

## 作者：封禁用户 (赞：15)

[传送门](https://www.luogu.com.cn/problem/AT2069)

### 分析

这题的建图非常巧妙。

发现题目要求两点之间的钱数最小值，不难往最短路方面想。

由于切换连通块一定会导致答案 $+1$，因此只要统计连通块的个数即可。最朴素的建图方式是：把连在一起的同一城市的道路两端的点放进一个连通块内，块内每个点两两之间连一条权值为 $1$ 的边。但是，这样建图边数最多可以达到 $\dfrac{n(n-1)}{2}$ 条，显然会爆空间。

考虑优化。

边数爆炸，则尝试建立虚点。对于每个连通块，建立一个虚点。把连通块内每个点和虚点连一条权值为 $0.5$ 的边。这样，任意两点都能以虚点为中转站来保持距离仍为 $1$。优化后，点的数量不超过 $n+m$，边的数量不超过 $2m$，时间、空间复杂度都 OK。

样例 $2$ 原图（边上的数是城市编号）：

![](https://cdn.luogu.com.cn/upload/image_hosting/qq1u3kgk.png)

以本样例中城市 $1$ 唯一的连通块来对比优化前后（边上的数是边权）。

优化前：

![](https://cdn.luogu.com.cn/upload/image_hosting/r69qruet.png)

优化后（$9$ 为虚点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0ecclvlb.png)

为了方便计算，将全部边权 $\times 2$ 来变成整数，最后答案再 $\div 2$ 即可。

具体流程：

1. 把每条边的两端点按城市保存在 vector 里面（省空间）。
2. 循环遍历每个出现过的城市，用并查集维护连通块，找出连通块内所有点，和该连通块的虚点连边。
3. 跑一遍最短路，得出答案。

注意：

- 对于每个不同的城市，并查集和保存虚点编号的数组都要初始化。
- 存 vector 时，可能会把同一个点放入同一个城市所对应的 vector 多次，所以需要去重。

### 代码

[click](https://atcoder.jp/contests/arc061/submissions/28663640)

---

## 作者：__Hacheylight__ (赞：7)

すぬけ君の地下鉄旅行 / Snuke's Subway Trip AtCoder - 2069

题意是从1到$N$，乘多次地铁。每个地铁有一个运营公司。如果公司不同，那么换乘需要1的费用。

解析：

很自然能够想到并查集。

每个并查集维护每个公司的线路，站点等信息

首先读入之后，我们把同公司的线路放入$G$中，

之后，现将每个公司的站点合并到一个并查集里去

之后，新建一个图（类似$bipartite$ $graph$）,左边是站，右边是公司（无向边）

拿第二个样例举例：

~~此图来自本人博客~~

![这里写图片描述](https://cdn.luogu.com.cn/upload/pic/44643.png)


之后通过$BFS$求出$DP$数组（表示从1到达N最少的价值数）

注意：

我们发现当要在某公司的某条线上从起点到达终点时，要在图中跑两段路，2 $yen$
不同公司4短路 4 $yen$

于是答案就是$BFS$后的$DP[N]/2$

```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 1234567;
vector <pair<int,int> > G[N] ;
vector <int> newg[N] ;
queue <int> q ;
int f[N],son[N],id[N],dp[N] ;
bool use[N] ;
int n,m ;
inline void init(int i){
	f[i]=i;son[i]=0;id[i]=-1;use[i]=false ;
}
int find(int x){
	return (x==f[x])?x:f[x]=find(f[x]) ; 
}
inline void merge(int x,int y){
	int X=find(x),Y=find(y) ;
	if (X==Y) return ;
	if (son[X]<son[Y]) f[X]=Y ;//避免WA?RE? 小技巧 
	else {
		f[Y]=X ;
		if (son[X]==son[Y]) son[X]++ ;
	}
} 
inline int read(){
	char c;int f=1 ;
	while ((c=getchar())<'0' || c>'9') if (c=='-') f=-1 ;
	int res=c-'0' ;
	while ((c=getchar())>='0' && c<='9') res=res*10+c-'0' ;
	return res*f ; 
}
int main(){
	n=read();m=read() ;
	for (int i=1;i<=m;i++){
		int a,b,c ;
		a=read();b=read();c=read() ;
		G[c].push_back(make_pair(a,b)) ;
	}
	int cnt=n; 
	for (int i=1;i<=N;i++){
		if (G[i].empty()) continue ; //无该公司 
		for (int j=0;j<G[i].size();j++){ //初始 
			init(G[i][j].first) ;
			init(G[i][j].second) ;
		}
		for (int j=0;j<G[i].size();j++) merge(G[i][j].first,G[i][j].second) ;
		for (int j=0;j<G[i].size();j++){
			if (!use[G[i][j].first]){
				use[G[i][j].first]=true ;
				int X=find(G[i][j].first) ;
				if (id[X]==-1) id[X]=++cnt ;
				newg[G[i][j].first].push_back(id[X]) ;//该站点与公司建无向边 
				newg[id[X]].push_back(G[i][j].first) ;
			}
			if (!use[G[i][j].second]){ //同样的工作在second上再做一遍 
				use[G[i][j].second]=true ;
				int X=find(G[i][j].second) ;
				if (id[X]==-1) id[X]=++cnt ;
				newg[G[i][j].second].push_back(id[X]) ;
				newg[id[X]].push_back(G[i][j].second) ;
			}
		}
 	}
 	q.push(1) ;
 	memset(dp,-1,sizeof(dp)) ;
 	dp[1]=0; //初始在0号节点
	while(!q.empty()){ //BFS 
		int v=q.front();q.pop() ;
		for (int i=0;i<newg[v].size();i++){
			int to=newg[v][i] ;
			if (dp[to]==-1){ //还没访问 
				dp[to]=dp[v]+1 ;
				q.push(to) ;
			}
		}
	}
	if (dp[n]==-1) cout<<-1 ;
	else cout<<dp[n]/2 ;
}
```

当然也有不用并查集的方法（BFS)，

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1234567;
 
int dist[N];
vector < pair <int, int> > g[N];
vector <int> new_g[N], all[N];
int was[N];
int x[N];
int ptr[N];
 
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int foo, bar, qwe;
    scanf("%d %d %d", &foo, &bar, &qwe);
    foo--; bar--;
    g[foo].push_back(make_pair(qwe, bar));
    g[bar].push_back(make_pair(qwe, foo));
    all[qwe].push_back(foo);
    all[qwe].push_back(bar);
  }
  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
    ptr[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    was[i] = -1;
  }
  int new_n = n;
  for (int i = 0; i < N; i++) {
    new_g[i].clear();
  }
  for (int color = 0; color < N; color++) {
    if (all[color].empty()) {
      continue;
    }
    for (int it = 0; it < (int) all[color].size(); it++) {
      int v = all[color][it];
      if (was[v] == color) {
        continue;
      }
      int b = 0, e = 1;
      x[0] = v;
      was[v] = color;
      while (b < e) {
        while (ptr[x[b]] < (int) g[x[b]].size()) {
          int c = g[x[b]][ptr[x[b]]].first;
          if (c != color) {
            break;
          }
          int u = g[x[b]][ptr[x[b]]].second;
          if (was[u] != color) {
            was[u] = color;
            x[e] = u;
            e++;
          }
          ptr[x[b]]++;
        }
        b++;
      }
      for (int i = 0; i < e; i++) {
        new_g[x[i]].push_back(new_n);
        new_g[new_n].push_back(x[i]);
      }
      new_n++;
    }
  }
  for (int i = 0; i < new_n; i++) {
    dist[i] = -2;
  }
  int b = 0, e = 1;
  x[0] = 0;
  dist[0] = 0;
  while (b < e) {
    for (int j = 0; j < (int) new_g[x[b]].size(); j++) {
      int u = new_g[x[b]][j];
      if (dist[u] == -2) {
        dist[u] = dist[x[b]] + 1;
        x[e] = u;
        e++;
      }
    }
    b++;
  }
  printf("%d\n", dist[n - 1] / 2);
  return 0;
}
```

还有通过dijkstra解决的方法
```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 1e5 +10 ;
const int inf = 0x3f3f3f3f ;
struct st{int p,b,c;};
bool operator < (st a,st b){return a.c>b.c;}
inline int read(){
	char c;int f=1 ;
	while ((c=getchar())<'0' || c>'9') if (c=='-') f=-1 ;
	int res=c-'0' ;
	while ((c=getchar())>='0' && c<='9') res=res*10+c-'0' ;
	return res*f ; 
}
map<int ,vector<int> > E[N] ; 
map<int,int > d[N] ; 
vector <int> G[N];
priority_queue <st> q ;
int n,m;
int main(){
	n=read();m=read() ;
	for (int i=1;i<=m;i++){
		int a,b,c ;
		a=read();b=read();c=read();a--;b-- ;
		E[a][c].push_back(b) ;E[b][c].push_back(a) ;
		G[a].push_back(c) ;G[b].push_back(c) ; 
	}
	d[0][0]=0;q.push({0,0,0}) ;
	while(!q.empty()){ //一波Dijkstra 
		st p=q.top();q.pop() ;
		if (d[p.p][p.b]!=p.c){
			continue ;
		}
		if (d[p.p].find(0)==d[p.p].end() || d[p.p][0]>p.c){
			d[p.p][0]=p.c ;
			q.push({p.p,0,p.c}) ;
 		}
 		if (p.b==0){
 			for (int i=0;i<G[p.p].size();i++){
 				int v=G[p.p][i] ;
 				if (d[p.p].find(v)==d[p.p].end() || d[p.p][v]>p.c+1){
 					d[p.p][v]=p.c+1 ;
 					q.push({p.p,v,p.c+1}) ;
				 }
			 }
			continue ; 
		}
		for (int i=0;i<E[p.p][p.b].size();i++){
			int v=E[p.p][p.b][i] ;
			if (d[v].find(p.b)==d[v].end() || d[v][p.b]>p.c){
				d[v][p.b]=p.c ;
				q.push({v,p.b,p.c}) ;
			}
		}
	}
	int ans=inf ;
	for (map<int,int>::iterator p=d[n-1].begin();p!=d[n-1].end();p++) ans=min(ans,p->second) ;
	if (ans==inf) printf("-1\n") ;
	else printf("%d\n",ans) ;
}
```

---

## 作者：igAC (赞：6)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_arc061_c)

[ATlink](https://atcoder.jp/contests/arc061/tasks/arc061_c)

简要题意（洛谷翻译）：

Snuke 的城镇有地铁行驶，地铁线路图包括 $n$ 个站点和 $m$ 个地铁线。站点被从 $1$ 到 $n$ 的整数所标记，每条线路被一个公司所拥有，并且每个公司用彼此不同的整数来表示。

第 $i$ 条线路（$1 \le i \le m$）是直接连接 $p_i$ 与 $q_i$ 的双向铁路，中间不存在其他站点，且这条铁路由 $c_i$ 公司所拥有。

如果乘客只乘坐同一公司的铁路，他只需要花费一元，但如果更换其他公司的铁路需要再花一元。当然，如果你要再换回原来的公司，你还是要花一元。

Snuke 在 $1$ 号站的位置出发，他想通过地铁去第 $n$ 站，请求出最小钱数。如果无法到达第 $n$ 站，输出 ``-1``。

# $\text{Solution}$

## $\text{Sol1}$

不难想到拆点，我们将每个点拆成与每个公司的铁路相连的点，每个拆出来的点只与公司编号相同的点相连（语文烂，轻喷）。

将 $1$ 号站点拆成 $(1,1)$，每个由 $1$ 号公司运营的铁路与它相连。

如 ``1 3 1`` 就将 $(1,1)$ 与 $(3,1)$ 相连。

每条铁路最多新增加 $2$ 个节点，节点个数不会超过 $2m$。

接下来考虑如何转线，若每个节点都连向相邻的结点的话，边数会达到 $O(m^2)$，我们接受不了。

> 对于图论来说，复杂度不对的话，可以考虑建虚点。----沃兹基烁德

我们可以对每个站点新建一个 $0$ 号节点，站点拆出来的点都向 $0$ 号节点连一条费用为 $0$ 的边，$0$ 号节点向其他点连费用为 $1$ 的边。

这样就很好的处理了转线的问题，而且边数降到了 $O(m)$。

接下来在这张图上以 $(1,0)$ 为起点，$(n,0)$ 为终点跑最短路（Dijkstra，SPFA，01BFS 均可），就可得出答案。

## $\text{Sol2}$

考虑为什么直接 01BFS 跑出来的答案是错误的，如下例：

![](https://cdn.luogu.com.cn/upload/image_hosting/9tma6k2e.png)

01BFS 只考虑 $dis_{to}>dis_{now}+w$ 的情况。

若我们先遍历 $1 \to 2 \to 4$ 这一条路，那么 $dis_{4}=1$，而 $1 \to 3 \to 4$ 则不会被考虑。

而对于 $4 \to 5$ 的转移，我们发现 $1 \to 3 \to 4$ 是更优的，但是我们将它忽略了。

所以我们需要多考虑 $dis_{to}=dis_{now}+w$ 的情况。

我们可以对每个节点都维护一个 ``set``，每次转移的时候在 ``set`` 中查找是否有与当前路公司相同的。

对于 $dis_{to}=dis_{now}+w$ 的情况，我们就将 $col[now][to]$ 加入 $to$ 的集合中。

对于 $dis_{to}>dis_{now}+w$ 的情况，显然公司是否相同是不重要的，直接花费 $1$ 的代价转线是不劣于从相同公司转移过来的。

于是就将 ``set`` 清空，重新加入公司编号。

在最短路转移的时候考虑以上两种情况，就可得出答案。

具体实现可参考代码。

# $\text{Code}$

## $\text{Code1}$

```cpp
#include<bits/stdc++.h>
#define LLINF 1e18
#define int long long
#define N 200005
#define M 1000005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,dis[M],tot;
map<int,vector<int>>mp[N];
map<int,int>bel[M];
vector<int>col[M],p[M];
vector<pair<int,int>>g[M];
void add_edge(int x,int y,int z){g[x].push_back({y,z});}
void BFS(int s){
	for(int i=1;i<=tot;++i) dis[i]=LLINF;
	deque<int>q;
	dis[s]=0,q.push_front(s);
	while(!q.empty()){
		int x=q.front();q.pop_front();
		for(auto [y,z]:g[x]){
			if(!z){
				if(dis[y]>dis[x]){
					dis[y]=dis[x];
					q.push_front(y);
				}
			}
			else{
				if(dis[y]>dis[x]+1){
					dis[y]=dis[x]+1;
					q.push_back(y);
				}
			}
		}
	}
	if(dis[p[n][0]]==LLINF) puts("-1");
	else printf("%lld",dis[p[n][0]]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read(),z=read();
		mp[x][z].push_back(y);
		mp[y][z].push_back(x);
		col[x].push_back(z);
		col[y].push_back(z);
	}
	for(int i=1;i<=n;++i) col[i].push_back(0);
	for(int i=1;i<=n;++i){
		sort(col[i].begin(),col[i].end());
		col[i].erase(unique(col[i].begin(),col[i].end()),col[i].end());
		for(int x:col[i]){
			p[i].push_back(++tot);
			bel[i][x]=tot;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<col[i].size();++j){
			add_edge(p[i][j],p[i][0],0);
			add_edge(p[i][0],p[i][j],1);
			for(int x:mp[i][col[i][j]]) add_edge(p[i][j],bel[x][col[i][j]],0);
		}
	}
	BFS(p[1][0]);
	return 0;
}
```

## $\text{Code2}$

```cpp
#include<bits/stdc++.h>
#define LLINF 1e18
#define int long long
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int head[N],tot,n,m,dis[N];
bool vis[N];
struct Edge{
	int to,nxt;
	int c;
}e[N<<2];
void add_edge(int x,int y,int c){
	e[++tot].to=y;
	e[tot].c=c;
	e[tot].nxt=head[x];
	head[x]=tot;
}
set<int>vis_col[N];
int val(int x,int c){return (vis_col[x].find(c)==vis_col[x].end());}
void SPFA(){
	for(int i=1;i<=n;++i) dis[i]=LLINF;
	queue<int>q;
	dis[1]=0,vis[1]=true,q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to,c=e[i].c,w=val(x,c);
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				if(!vis[y]){
					q.push(y);
					vis[y]=true;
				}
				vis_col[y].clear();
				vis_col[y].insert(c);
			}
			else if(dis[y]==dis[x]+w){
				if(val(y,c)){
					if(!vis[y]){
						q.push(y);
						vis[y]=true;
					}
					vis_col[y].insert(c);
				}
			}
		}
	}
	if(dis[n]==LLINF) puts("-1");
	else printf("%lld",dis[n]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read(),c=read();
		add_edge(x,y,c);
		add_edge(y,x,c);
	}
	SPFA();
	return 0;
}
```

---

## 作者：louhao088 (赞：6)

说一种不用转换建图的方法。



------------

我们先建出原图，然后直接维护从 $1$ 开始的最短路。由于每个点连入其边的编号对其答案会产生影响。所以我们需要维护对于每个点以第 $i$ 种编号的边连入其代价最小为多少。这个看起来很大，但实际只有边数种。而且由于我们发现这个边权只有 $0,1$ 所以我们可以直接用双端队列来优化。

但这样做的复杂度最大为 $O(m^2)$，因为可能每次都到同一个点，且那个点度数极大。


------------

我们考虑优化，我们发现其实如果一个点 $x$ 以一种编号为 $y$ 的边连入被访问过了，且该点 $x$ 又以一种新的编号为 $z$ 的边连入，那么现在该点能更新的点只有其连出编号为 $z$ 的点，因为对于其他点来说代价不会比以 $y$ 连入更优。这样每个点连出的点只会被访问至多 $2$ 次。

这样复杂度瓶颈就在前期预处理时，用 map 把一个点 $x$ 以一种编号为 $y$ 的边连入这种情况压成一个较小的数上。这个应该也能优化成线性，但是没必要。

复杂度为 $O(m\log m+m)$


------------
代码如下

```cpp
// Problem: AT2069 [ARC061C] すぬけ君の地下鉄旅行 / Snuke's Subway Trip
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2069
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 2022-05-13 20:06:28
// Author : louhao088

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit(x) (x&-x)
const int maxn=4e5+5,M=34005;
inline int read(){
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x){
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,x,y,z,tot=0,id[maxn];
vector<pi>e[maxn];
int f[maxn],vis[maxn],c[maxn],vis2[maxn],a[maxn];
map<int,int>h[maxn];
deque<pi>q;vector<pi>E[maxn];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x=read(),y=read(),z=read();
		if(!h[x][z])h[x][z]=++tot;
		if(!h[y][z])h[y][z]=++tot;
		E[h[x][z]].pb(mp(y,h[y][z]));
		E[h[y][z]].pb(mp(x,h[x][z]));
		c[h[x][z]]=z,c[h[y][z]]=z;
		e[x].pb(mp(y,h[y][z])),e[y].pb(mp(x,h[x][z]));
	}
	for(auto i:e[n])q.push_back(i),f[i.se]=1;
	while(!q.empty()){
		pi p=q.front();q.pop_front();
		int x=p.fi,z=p.se;int g=f[z];
		if(vis[z])continue;vis[z]=1;
		if(x==1)cout<<g,exit(0);
		if(vis2[x]==1){
			for(auto i:E[z])
				if(!vis[i.se])q.push_front(i),f[i.se]=g;
			continue;
		}vis2[x]=1;
		for(auto i:e[x])
			if(c[i.se]==c[z]){
				if(!vis[i.se])q.push_front(i),f[i.se]=g;
			}
			else{
				if(!f[i.se])q.push_back(i),f[i.se]=g+1;
			}
	}
	puts("-1");
 	return 0;
}




```


---

## 作者：SMZX_LRJ (赞：6)

最短路变式。

这题特殊之处在于，若经过某个点的上一条边和将要走的下一条边的颜色相同，那么下一条边将会免费。

考虑建虚点。对于相邻点 $(u,v)$，将一个虚点 $w$ 插进它们中间，令 $(u,w),(w,v)$ 边权为 $0.5$。并且给这个虚点颜色。

然后考虑怎么处理免费的情况。对于一个真实点，相邻的必定都是虚点，那么将颜色相同的虚点都连接起来，边权为 $0$，使其相互可到达。这样处理之后，就能跳过到这个真实点的两条边了，即节省了 $1$ 花费。

图解：
![](https://cdn.luogu.com.cn/upload/image_hosting/kgssmmqw.png)

然后跑 Dijkstra 就做完了。

复杂度证明：

对于每条边只开一个虚点，一共 $n+m$ 个节点。虚点之间的连边最坏情况下是菊花图且所有边颜色相同，最多 $m-1$ 条。

```cpp
int n,extra,m;
struct edge{int to,val,col,nxt;}e[N];
int head[N],cnt_e;
int last[N],del[N];
void add(int u,int v,int val,int col)
{
	e[++cnt_e]=(edge){v,val,col,head[u]};
	head[u]=cnt_e;
}
struct dataX
{
	int p,dis;
	friend bool operator<(dataX A,dataX B)
	{
		return A.dis>B.dis;
	}
};
priority_queue<dataX> q; 
int dis[N],vis[N];
void dijkstra()
{
	memset(dis,125,sizeof(dis));
	q.push((dataX){1,1});
	dis[1]=0;
	while(!q.empty())
	{
		dataX h=q.top();
		q.pop();
		if(vis[h.p]) continue;
		vis[h.p]=1;
		for(int i=head[h.p];i;i=e[i].nxt)
		{
			int to=e[i].to;
			if(dis[to]>e[i].val+dis[h.p])
			{
				dis[to]=e[i].val+dis[h.p];
				q.push((dataX){to,dis[to]});
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	extra=n;
	for(int i=1,u,v,c;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&c);
		add(u,++extra,1,c),add(extra,v,1,0);
		add(v,extra,1,c),add(extra,u,1,0); 
	} 
	int cnt_del;
	for(int i=1;i<=n;i++)
	{
		cnt_del=0;
		for(int j=head[i];j;j=e[j].nxt)
		{
			int col=e[j].col;
			if(last[col]) add(e[j].to,last[col],0,col),add(last[col],e[j].to,0,col);
			else del[++cnt_del]=col;
			last[col]=e[j].to;
		}
		for(int j=1;j<=cnt_del;j++)
		last[del[j]]=0;
	}
	dijkstra();
	if(dis[n]==dis[0]) cout<<-1;
	else cout<<dis[n]/2;
	return 0;
}
```


---

## 作者：P_VICVIC_R (赞：3)

~~集训时保一波咕值。~~

---

题意不讲，请参见别人的翻译。

### 思路：
没搞错的话，这题应该是运用的拆点的思想。

拆点是一种图论建模思想，常用于**网络流**，用来处理**点权或者点的流量限制**的问题，也常用于**分层图**。（源自 [oiwiki](https://oi-wiki.org/graph/node/)。）

本题思路就是把一个点拆成**该点连接的不同公司的数量加一个点**，即**每个公司都单独建一个负责连接同一个公司的路径的点**，再连接到一个点 $i(1\le i \le n)$（就是题面里的原节点），注意同一个公司的路径的边权为 $0$，原节点到任意公司的节点的边权为 $1$，任意公司的节点到原节点的边权为 $0$。最后跑最短路就行

### code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
static const int N=500010;
static const int INF=LONG_LONG_MAX-100000;;
int n,m;
map<pair<int,int>,int> ml;
int nodecnt; 
struct Edge{
	int to,vl;
	int Nxt;
}e[10000000];//边数有点上天，尽可能开大些
int tot;
int Sign[N];
inline void add(int fr,int to,int vl){
	tot++;
	e[tot].Nxt=Sign[fr];
	e[tot].to=to;
	e[tot].vl=vl;
	Sign[fr]=tot;
}

int vis[N];
int dis[N];
inline void dijkstra(){
	for(int i=1;i<=nodecnt;i++)
		dis[i]=INF;
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > ql;
	dis[1]=0;
	ql.push({0,1});
	while(!ql.empty()){
		int rt=ql.top().second;
		ql.pop();
		if(vis[rt]) 
			continue;
		vis[rt]=1;
		for(int i=Sign[rt];i;i=e[i].Nxt){
			int to=e[i].to;
			int vl=e[i].vl; 
			if(dis[to]>dis[rt]+vl){
				dis[to]=dis[rt]+vl;
				ql.push({dis[to],to}); 
			}
		} 
	} 
}

signed main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		ml[{i,0}]=++nodecnt;
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		if(!ml[{x,z}]){
			ml[{x,z}]=++nodecnt;
			add(ml[{x,z}],x,1);
			add(x,ml[{x,z}],0);
		}
		
		if(!ml[{y,z}]){
			ml[{y,z}]=++nodecnt;
			add(ml[{y,z}],y,1);
			add(y,ml[{y,z}],0);
		}
		add(ml[{y,z}],ml[{x,z}],0);
		add(ml[{x,z}],ml[{y,z}],0);
	}
	dijkstra();
	cout<<(dis[n]!=INF?dis[n]:-1);
	return 0;
}
```

---

## 作者：llqqhh (赞：3)

# AT_arc061_e

## 题面

Snuke 的城镇有地铁行驶，地铁线路图包括 $N$ 个站点和 $M$ 个地铁线。站点被从 $1$ 到 $N$ 的整数所标记，每条线路被一个公司所拥有，并且每个公司用彼此不同的整数来表示。

第 $i$ 条线路( $1≤i≤M$ )是直接连接 $p_i$ 与 $q_i$ 的双向铁路，中间不存在其他站点，且这条铁路由 $c_i$ 公司所拥有。

如果乘客只乘坐同一公司的铁路，他只需要花费一元，但如果更换其他公司的铁路需要再花一元。当然，如果你要再换回原来的公司，你还是要花一元。

Snuke 在 $1$ 号站的位置出发，他想通过地铁去第 $N$ 站，请求出最小钱数。如果无法到达第 $N$ 站，输出 `-1`。

## 思路

考虑对每条线路建立一个虚点，如下图所示（以样例 $1$ 为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3hmpk4dt.png)

可以发现一个公司统属的线路连接的所有站点之间可以任意通行而只产生 $1$ 次贡献。若两条线路**属于同一个公司**并且**同时连接一个站点**则可以用 $0$ 边将这两条线路连接起来，产生短路的效果。

![](https://cdn.luogu.com.cn/upload/image_hosting/g2hctluz.png)

这样操作之后就可以实现同一个公司连接的一个联通块内的所有站点可以任意通行而只产生 $1$ 次贡献。

为了帮助理解，下面给出更一般的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/7wov8es5.png)

建完图以后，就可以对图跑一遍正常的最短路。需要注意的是，为了避免计算边权时出现浮点数，可以通过把上图的所有 $0.5$ 边权改为 $1$ 边权，最后对答案除以 $2$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int N = 2e6+10;
struct node {int to, w, c;};
bool cmp(node x, node y) {return x.c < y.c;}
vector<node> g[N];
int n, m;

int dist[N];
bitset<N> st;
inline void dij() {
    priority_queue<pii, vector<pii>, greater<pii>> hp;
    memset(dist, 0x3f, sizeof dist);
    hp.push({0, 1});
    dist[1] = 0;
    while(!hp.empty()) {
        int u = hp.top().second;
        hp.pop();
        if(st[u]) continue;
        st[u] = 1;
        for(auto i : g[u]) {
            int v = i.to;
            if(dist[v] > dist[u] + i.w) {
                dist[v] = dist[u] + i.w;
                hp.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 1, u, v, c; i <= m; i ++) {
        cin >> u >> v >> c;
        g[u].push_back({i + n, 1, c});
        g[v].push_back({i + n, 1, c});
        g[i + n].push_back({u, 1, c});
        g[i + n].push_back({v, 1, c});
    }
    for(int i = 1; i <= n; i ++) {
        sort(g[i].begin(), g[i].end(), cmp);
        for(int j = 1; j < g[i].size(); j ++) {
            if(g[i][j].c == g[i][j - 1].c) {
                g[g[i][j].to].push_back({g[i][j - 1].to, 0, 0});
                g[g[i][j - 1].to].push_back({g[i][j].to, 0, 0});
            }
        }
    }
    dij();
    if(dist[n] == 0x3f3f3f3f) cout << -1;
    else cout << dist[n] / 2;
}
```

---

## 作者：MrPython (赞：2)

想一下，生活中我们是怎样乘坐地铁的？
1. 从站厅层刷卡进站；
2. 前往站台层乘车；
3. 下车后从站台层走到站厅层；
4. 从站厅层刷卡出站，此时闸机会自动从卡中扣除相应费用。

在本题中，我们模仿上述过程，每个车站都分成至少两个节点——一个站厅层和若干个站台层。从站台层前往站厅层（出站）需要支付 $1$ 元费用，而从站厅层往站台层（进站）不需要花费。通过同一公司的地铁来回移动不收费。

不同地铁公司间换乘需要收费，可以看作必须“出站换乘”，即先出站到站厅层（此时付费）再从其他公司的闸机进入其他线路。

按照上述所说，我们将每个“站台”向相应的“站厅”连一条权值为 $1$ 的有向边，从“站厅”到各个“站台”连一条权值为 $0$ 的有向边，某条地铁线路即为一条连接两个该公司所管辖“站台”的权值为 $0$ 的无向边。这样，就可以建出一个 0-1 图，进行 0-1 BFS 即可。

实际操作中显式建边会很复杂。我使用 `map` 存储图和 dis 数组，`mp[x][c]` 表示在点 $x$ 乘坐 $c$ 公司的线路可以直接到达的节点，`dis[x][c]` 表示从起点到 $x$ 站的 $c$ 公司站台所需的花费。特别地，我的代码中 `dis[x][~0]` 表示到达站厅层所需要的花费。队头为站厅时，将所有的站台从队头入队；队头是站台时，将所有连在该节点的地铁线路从队头入队，以及将站厅从队尾入队。从起点的站厅开始，到终点的站厅结束，进行 0-1 BFS 即可。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<map<ui,vector<size_t>>> mp(n);
    while (m--){
        size_t x,y;ui z;cin>>x>>y>>z;--x,--y;
        mp[x][z].push_back(y),mp[y][z].push_back(x);
    }
    deque<pair<size_t,ui>> q({{0,~0}});
    vector<map<ui,ui>> dis(n);dis[0][~0]=0;
    while (!q.empty()){
        size_t p=q.front().first;ui c=q.front().second;q.pop_front();
        ui d=dis[p][c];
        if (~c){
            if (!dis[p].count(~0)||dis[p][~0]>d+1)
                dis[p][~0]=d+1,q.emplace_back(p,~0);
            for (size_t i:mp[p][c]) if (!dis[i].count(c)||dis[i][c]>d)
                dis[i][c]=d,q.emplace_front(i,c);
        }else for (pair<ui,vector<size_t>> const& i:mp[p])
            if (!dis[p].count(i.first)||d<dis[p][i.first]) 
                dis[p][i.first]=d,q.emplace_front(p,i.first);
    }
    dis[n-1].count(~0)?cout<<dis[n-1][~0]:cout<<"-1";
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

用同样颜色的边所连接成的连通块可以互相到达，不难想到建一个虚点，将这个联通块内的所有点向虚点连一个权值为 $0$ 的边，由这个连通块切换到别的连通块都需要 $1$ 的代价，因此虚点向连通块内所有点连权值为 $1$ 的边。

并查集加 01 BFS 就可以完成这个过程，应该是 $O(m\log m)$ 的。

```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int C = 1000000; 

int n, m, tot; 
vector<pair<int, int>> E[1000005]; 
int fa[200005]; 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int col[200005]; 
vector<pair<int, int>> G[400005]; 

inline void addedge(int u, int v) {
    G[u].emplace_back(v, 0); 
    G[v].emplace_back(u, 1); 
}

int d[400005]; 
void bfs(void) {
    deque<int> q; memset(d, 0xff, sizeof d); d[1] = 0; q.push_back(1); 
    while (!q.empty()) {
        int u = q.front(); q.pop_front(); 
        for (auto [v, w] : G[u]) if (d[v] == -1) {
            d[v] = d[u] + w; 
            if (w == 1) q.push_back(v); 
            else q.push_front(v); 
        }
    }
    cout << d[n] << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m; tot = n; 
    while (m--) {
        int u, v, c; cin >> u >> v >> c; 
        E[c].emplace_back(u, v); 
    }
    for (int i = 1; i <= C; ++i) if (E[i].size()) {
        vector<int> p; 
        for (auto [x, y] : E[i]) p.emplace_back(x), p.emplace_back(y); 
        sort(p.begin(), p.end()); 
        p.erase(unique(p.begin(), p.end()), p.end()); 
        for (int x : p) fa[x] = x; 
        for (auto [x, y] : E[i]) fa[find(x)] = find(y); 
        for (int x : p) if (find(x) == x) col[x] = ++tot; 
        for (int x : p) addedge(x, col[find(x)]); 
    } bfs(); 
    return 0; 
}
```

---

## 作者：Supor__Shoep (赞：2)

话说这道题评紫是不是有一点高了啊……

按照我的直觉来看，这一道题应该是蓝的水平，但是做完之后发现，确实只有蓝的水平。

首先我们可以发现题目中有一个 $c_i$ 公司拥有第 $i$ 号地铁线的条件，这个 $c_i$ 八九不离十都会出现不同的，所以如果相互转换到不同公司拥有的地铁线，那么最短路也是参差不齐。那么我们就不难想到拆点了（分层图）。

我们可以分成两层。对于同一家公司的地铁线，我们可以在其构成的图中随便走，没有任何影响，它的边权为 $0$；对于不同的公司，我们需要花费 $1$，即边权为 $1$。这样非常好理解，因为我们进入 $1$ 号点的时候也是需要边权 $1$ 的，我们可以想象是一家公司到另一家公司的地铁，其边权为 $1$。所以这样设边权是没有问题的。

但是这样建立边的话会爆炸，边的个数会达到惊人的数目。所以我们还需要进行改进。

我们可以想到建立虚点。假设我们建立另一个地铁站 $k$ 连接每一层的点，这样我们就可以让每一个点借助 $k$ 到达另一层的点。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/6t8cnp93.png)

设第一层的点数为 $n_1$,第二层的点数为 $n_2$，则原图建立的边数为 $n1\times n2$，而加入点 $k$ 后建立的边数为 $n1+n2$。这样我们就有足够的空间存边了。

需要注意的是，原本贯穿两层的线的边权为 $1$，如果加入点 $k$ 之后，我们需要满足两条边的边权和是 $1$，所以与 $k$ 连接的点构成的线的边权为 $0.5$，在原基础上除以 $2$ 就可以了。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e6+5;
int n,m;
int to[MAXN],nxt[MAXN],val[MAXN],head[MAXN],tot;
int dis[MAXN],vis[MAXN],cnt;
map<pair<int,int>,int> mp;
void add(int x,int y,int z)
{
	to[++tot]=y;
	val[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
priority_queue<pair<int,int> > que;
void Dijkstra()
{
	for(int i=0;i<=1000000;i++)	dis[i]=1e15;
	dis[1]=0;
	que.push(make_pair(0,1));
	while(!que.empty())
	{
		int t=que.top().second;que.pop();
		if(vis[t])	continue;
		vis[t]=1;
		for(int i=head[t];i;i=nxt[i])
		{
			if(dis[to[i]]>dis[t]+val[i])
			{
				dis[to[i]]=dis[t]+val[i];
				que.push(make_pair(-dis[to[i]],to[i]));
			}
		}
	}
}
int find(int x,int y)
{
	if(mp.find(make_pair(x,y))!=mp.end())	return mp[make_pair(x,y)];
	return mp[make_pair(x,y)]=++cnt;
}
signed main()
{
	cin>>n>>m;
	cnt=n;
	for(int i=1;i<=m;i++)
	{
		int from,tog,id;
		cin>>from>>tog>>id;
		int u=find(from,id),v=find(tog,id);
		add(u,v,0),add(v,u,0);
		add(from,u,1),add(u,from,1);
		add(tog,v,1),add(v,tog,1);
	}
	Dijkstra();
	if(dis[n]==1e15)	puts("-1");
	else	cout<<dis[n]/2<<endl;
	return 0;
}
```

---

## 作者：KaisuoShutong (赞：2)

AT2069 [ARC061C] すぬけ君の地下鉄旅行 / Snuke's Subway Trip 题解。

基本思路——边上建点，优化建图。

考虑这样连边。

$(x_i,bel(E_i)) \leftrightarrow E_i \leftrightarrow (y_i,bel(E_i))$，全部是 $0$。

$\forall bel,(x,bel)$ 之间前后缀连边（其实可以直接连上同一虚点，因为不优），表现出 $1$ 贡献。

特判起点终点。$O(n\log)$。实现可能稍复杂。

---

考虑更简单的写法，隐式建图。

会发现如果直接做 dij，问题在于所有的 $(x,fr)$ 都会更新一遍所有出边。

这是不优的，因为除了第一个，其他的 $(x,fr)$ 最多更新同 $fr$ 的点。

优化到 $O(n\log)$，如果认为 $n$、$m$ 同阶的话。

```cpp
void m_dij() {
	priority_queue<info>q;q.push((info){d[1][-1]=0,1,-1});
	while(!q.empty()) {
		int x=q.top().y,fr=q.top().z;q.pop();
		if(x==n) cout<<d[x][fr]<<'\n',exit(0);
		if(v[x][fr]) continue;v[x][fr]=1;
		for(int y:mp[x][fr])
			if(!d[y].count(fr)||d[y][fr]>d[x][fr])
					q.push((info){d[y][fr]=d[x][fr],y,fr});
		mp[x][fr].clear();
		if(!un[x]) for(int i=h[x];i;i=a[i].next)
			if(!d[a[i].to].count(a[i].fr)||d[a[i].to][a[i].fr]>d[x][fr]+1)
				q.push((info){d[a[i].to][a[i].fr]=d[x][fr]+1,a[i].to,a[i].fr});
		un[x]=1;
	}cout<<-1<<'\n';
}
```

---

## 作者：小木虫 (赞：2)

### Preface  
这篇题解会是题解区唯一一种魔改 dij 的做法。做完后看了题解才知道有建图的做法。  
### Problem  
给你一个无向图，每条边有颜色，从一个颜色的边走到另外一个颜色的边需要花费 1 代价，问你最短路。  
### Solution  
我们发现，每个点可以有若干状态，即上一个走到的边的颜色，很显然一个点最多有 $n$ 个状态，但是实际上全局的总状态量应为 $m$ 量级的，因为一个点的状态仅仅与其入度数量有关，显然全局入度数就是边数，由于是无向图还要乘上一个二的常数。  

那这样我们就可以把一个点拆分成若干状态，信息用 vector 维护。然后来跑 dij。但是有一个问题：一个点有若干个状态，这些状态还要转移到下一个点，那每个状态又会贡献这个点出度数的转移复杂度，这个复杂度我们可承担不起。  

但是我们发现，一条边最多为答案 +1。那这个就很有意思了。我们知道，一个点的所有状态会对出度中与其状态相等的边给予优惠，为 0 贡献，其它部分都是 1 贡献。  

根据 dij 堆优化的性质，一个点中最先到的状态是其所有状态中答案最小的。  
那么这个状态暴力转移到下一个点后，所有该点其它状态转移到下一个点并且不带优惠的情况都不会比现在的转移更优。于是我们暴力转移第一个到达的状态，后面的状态仅仅转移与其颜色相等的出边。显然这样的复杂度是很优秀的，因为一个点所有的出边都只会被转移线性次数。 当然，要注意状态去重，否则复杂度就不对了。 

上述的去重和找相同颜色出边的操作都可以通过先将边排序后一个个加来进行。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=6e5+10;
struct e{int u,v,w;}E[N];
bool cmp(e a,e b){return a.w<b.w;}
int n,m;int cnt;int head[N];
struct EDGE{int v,w,next,id;}edge[N];
vector <int> col[N];int lst[N];
vector <int> dis[N];int MIN[N];
vector <int> vis[N];
vector <int> p[N];int pin[N];
void add(int u,int v,int w){
	edge[++cnt].next=head[u];
	if(edge[head[u]].w!=w)p[u].push_back(head[u]);
	edge[cnt].v=v;edge[cnt].w=w;
	if(col[v].size()==0)
		col[v].push_back(w),dis[v].push_back(1e9),vis[v].push_back(0);
	else if(col[v][col[v].size()-1]!=w)
		col[v].push_back(w),dis[v].push_back(1e9),vis[v].push_back(0);
	head[u]=cnt;
	edge[cnt].id=col[v].size()-1;
}
struct node{
	int u,id,dis;
	bool operator <(const node &a)const{
		return dis>a.dis;
	}
};
priority_queue <node> Q;
void dijkstra(){
	dis[1].push_back(1);vis[1].push_back(0);col[1].push_back(-1);
	for(int i=1;i<=n;i++)MIN[i]=1e9;MIN[1]=1;
	node st=(node){1,col[1].size()-1,1};Q.push(st);
	while(!Q.empty()){
		node now=Q.top();Q.pop();
		int u=now.u;int id=now.id;
		//cout<<dis[u][id]<<endl;
		if(vis[u][id])continue;
		vis[u][id]=1;lst[u]++;
		if(dis[u][id]>MIN[u])continue;
		MIN[u]=min(MIN[u],dis[u][id]);
		if(head[u]==0)continue;
		if(lst[u]==1){
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].v;int w=edge[i].w;
				if(vis[v][edge[i].id])continue;
				if(dis[v][edge[i].id]>dis[u][id]+(w!=col[u][id]&&col[u][id]!=-1)){
					dis[v][edge[i].id]=dis[u][id]+(w!=col[u][id]&&col[u][id]!=-1);
					if(MIN[v]<dis[v][edge[i].id])continue;
					MIN[v]=min(MIN[v],dis[v][edge[i].id]);
					Q.push((node){v,edge[i].id,dis[v][edge[i].id]});
				}
			}
		}
		int l=0;int r=p[u].size()-1;
		while(l<r){
			int mid=(l+r)/2;
			if(edge[p[u][mid]].w>=col[u][id])
				r=mid;
			else l=mid+1;
		}
		if(edge[p[u][l]].w!=col[u][id])continue;
		for(int i=p[u][l];edge[i].w==col[u][id];i=edge[i].next){
			int v=edge[i].v;if(vis[v][edge[i].id])continue;
			if(dis[v][edge[i].id]>dis[u][id]){
				dis[v][edge[i].id]=dis[u][id];
				if(MIN[v]<dis[v][edge[i].id])continue;
				MIN[v]=min(MIN[v],dis[v][edge[i].id]);
				Q.push((node){v,edge[i].id,dis[v][edge[i].id]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>E[i].u>>E[i].v>>E[i].w;
	}sort(E+1,E+1+m,cmp);
	for(int i=1;i<=m;i++){
		add(E[i].u,E[i].v,E[i].w);
		add(E[i].v,E[i].u,E[i].w);
	}
	for(int i=1;i<=n;i++)p[i].push_back(head[i]);
	dijkstra();int ans=1e9;
	for(int i=0;i<dis[n].size();i++){
		ans=min(ans,dis[n][i]);
	}
	if(ans>m)cout<<-1;
	else cout<<ans;
	return 0;
}
```


---

## 作者：lgswdn_SA (赞：2)

首先我们发现一个公司包管的线路可以组成一些连通块，但是这些不同连通块之间完全可以考虑成不同公司。所以可以化简成每个公司只会包管形成一个连通块的子图，即每个公司包管的点可以互通。这里一定需要注意复杂度不能假，必须把所有公司拆开来考虑，对每个公司内部进行一个再拆分。这样才能保证每个点被访问 $O(\deg )$ 次，即总共（如果用并查集的话）复杂度为 $O(m\alpha)$。（我代码实现中为了简便做了一个简单的去重多了个 $\log$，实际上可以不需要，而且这个并查集也是可以用线性的 dfs 解决掉的，不过不影响大局）。

容易发现我们乘车相当于不断地换乘，每次换乘永远是 $1$ 元。对于这种情况，可以建立一些辅助点，每个点代表一个公司（的连通块），然后所有其连通的点以 $\frac{1}{2}$ 的边权与它相连，然后跑一个最短路即可（这样每次出入都是 $1/2$，所以进行一次换乘的代价就是 $1$）。

每个点连的额外边最多为 $\deg(u)$，然后原图上的原边是可以去掉的，也就是说新图总边数 $\le \sum \deg(u)=2m$，总点数 $\le m+n$。还有实际操作的时候由于边权全是 $1/2$ 所以先当 $1$ 来做最后全部除以 $2$ 即可。

代码：https://atcoder.jp/contests/arc061/submissions/28443592

p.s. 感谢兔兔对这篇题解的细致纠错和治好了我的眼睛。

---

## 作者：tommy0221 (赞：2)

[ATCoder题目传送门](https://atcoder.jp/contests/arc061/tasks/arc061_c)

[洛谷中文翻译传送门](https://www.luogu.com.cn/problem/AT2069)

[更好的阅读体验](https://www.cnblogs.com/zzctommy/p/14134800.html)

这题好像有好多种建图方法。

一个套路的建图方法，做过[这题](https://www.luogu.com.cn/problem/P6822)就很容易想到。

感觉这种题解不是很好写，那就直接写怎么建图然后讲每一种边的意义吧。

【建点】把边当成点，正向边和反向边分别建点，再建立超级源点 $S$ ，超级汇点 $T$

对于每一个节点 $u$ 按照 $v$ 颜色的颜色从小到大排序（我习惯把边设成 $u\to v$）。这样所有起点为 $u$ ，终点颜色相同的点会相邻。

【边一】如果这条边的终点是 $n$ ，那么拉边 $(id,T,0)$ ，因为它可以直接连到 $n$。

【边二】如果这条边的起点是 $1$ ，那么拉边 $(S,id,1)$，因为它从 $S$ 出发就已经相当于“换”了一次颜色。

【边三】对于 $u$ 相同的两个**相邻的**出边终点 $v_1,v_2$ （边的编号为 $id_1,id_2$），如果颜色相同，那么拉边 $(id_1,id_2,0),(id_2,id_1,0)$ ，因为这两条边可以免费走。【边五】会讲如果不同怎么拉边。

【边四】正向边向反向边拉边，因为走过去再走回来也可以。

我感觉剩下这种边是这种建图方法唯一的难点。

【边五】我们现在还没有处理颜色转换的边。这个东西看着贼难搞，不同颜色暴力拉边的话复杂度就又可以被卡成平方了。

换个思路，新建一个虚点，对于 $u$ 出发的**每种**颜色，随便取一个边对应的点往虚点连长度为 $1$ 的边，这个虚点往那个点连长度为 $0$ 的边。

往虚点走就意味着要换颜色，否则根本不会走长度为 $1$ 的边。而每一个颜色内部是可以随便走的，所以这种建图方法是对的。

总点数为 $2m+n+2$ ，正向边和反向边总共 $2m$ 个，加上 $n$ 个虚点，再加上超源超汇，不要开小。还有颜色值域上限是 $10^6$ ，不要开小了。

可以发现边权只有 $0$ 和 $1$ ，直接bfs就可以 $O(n)$ ，我偷懒写了dij。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N = 500005;
const int C = 1000005;
const int inf=0x3f3f3f3f;
int n, m, S, T, tot;
int dis[N];
bool vis[N];
struct node{
	int w, v, id;
	node(){w = v = id = 0;}
	node(int w_, int v_, int id_) {w = w_, v = v_, id = id_;}
	inline bool operator < (const node&t) const {return w < t.w;}
};
vector <node> E[N];
vector <pair<int, int> > e[N];
void Dij(){
	priority_queue <pair<int,int> > pq;
	memset(dis, 0x3f, sizeof(dis));
	pq.push(mkp(dis[S]=0, S));
	while (!pq.empty()){
		int u = pq.top().se; pq.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = 0, up = sz(e[u]); i < up; ++ i){
			int v = e[u][i].se;
			if (ckmin(dis[v] , dis[u] + e[u][i].fi))
				if(!vis[v]) pq.push(mkp(-dis[v], v));
		}
	}
}
signed main() {
	n = read(), m = read(), S = m * 2 + 2, T = tot = S + 1;
	rep(i, 1, m) {
		int x = read(), y = read(), z = read();
		E[x].pb(node(z, y, i << 1)),E[y].pb(node(z, x, i << 1 | 1));
	}
	rep(i, 1, n){
		static int tag[C];
		sort(E[i].begin(), E[i].end()), ++tot;
		for (int j = 0, up = sz(E[i]); j < up; ++ j){
			node now = E[i][j];
			if(tag[now.w]!=i){
				tag[now.w]=i;
				e[now.id].pb(mkp(1, tot));
				e[tot].pb(mkp(0, now.id));
			}
			e[now.id].pb(mkp(0,now.id ^ 1));
			if (i == 1) e[S].pb(mkp(1, now.id));
			if (now.v == n) e[now.id].pb(mkp(0, T));
			if (j && now.w == E[i][j-1].w) e[E[i][j-1].id].pb(mkp(0, now.id)), e[now.id].pb(mkp(0, E[i][j-1].id));
		}
	}
	Dij(), printf("%d\n", dis[T] == inf ? -1 : dis[T]);
	return 0;
}

``` 

---

## 作者：cjh20090318 (赞：2)

# 题解 [[ARC061E] すぬけ君の地下鉄旅行](https://www.luogu.com.cn/problem/AT_arc061_c)

## 题意

翻译很清楚，不讲。

## 分析

首先我们考虑一条线路两两之间都连上一个边权为 $1$ 的点。

很显然空间承受不了。

但是有一个优化技巧叫做**建虚点**。

### 建虚点是什么？

建虚点，字面意思上理解来说就是建一个毫不存在的点。

### 建虚点有什么用？

它可以将类似于**一票制**的**公交线路**（即**一条线路串联多个点**，任意两个点之间的距离或花费**相等**），减少空间复杂度。

### 如何建虚点？

首先我们来看这样一个地铁图。（下面的边权指的是公司编号）

![graph (1)](https://cdn.luogu.com.cn/upload/image_hosting/50vdb7ub.png)

这样的图转化一下就是下面这个样子（边权默认为 $1$）：

![graph (2)](https://cdn.luogu.com.cn/upload/image_hosting/iexyk4ob.png)

因为是同一个公司下的地铁线路，所以保证两两连边，然后就会像上图一样建很多不必要的边。

但是，我们建一个虚点 $C_1$，所有联通的 $1$ 公司下的点全部连到这个虚点上。

![graph (3)](https://cdn.luogu.com.cn/upload/image_hosting/7f5p70oc.png)

极大节省了空间！而这样同时也保证了联通的同一公司可以互相到达。

我们用同样的方式观察样例 2：

原图：![graph (4)](https://cdn.luogu.com.cn/upload/image_hosting/tjw8aoil.png)

建虚点转化后（边权默认为 $0.5$）：![graph (5)](https://cdn.luogu.com.cn/upload/image_hosting/tqt7lg35.png)

鉴于 $0.5$ 并不是很方便计算，我们直接将边权扩大两倍，计算时答案再缩小 $\dfrac{1}{2}$ 即可。

### 如何应用到本题上？

用并查集维护联通，**如果两条同一个公司的地铁不连通，那么这两条线路无法连接在同一个虚点上！**

建虚点后直接 $1 \sim n$ 跑最短路即可。

### 建虚点的其他练习题

- [P7646 [COCI2012-2013#5] HIPERCIJEVI](https://www.luogu.com.cn/problem/P7646)，个人觉得还是比较不错（你从空间限制就看得出来不能直接暴力建图）。

## 注意事项

- 多测要清空！但是不需要全部清空完，**用多少清空多少**，否则你会超时整整 $5$ 个点！
- 公司可能有 $10^6$，建虚点的新图过后最坏情况下会有 $N+M$ 个点，请保证你的数组足够。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cassert>
#include<cstring>
#include<queue>
#include<utility>
#include<vector>
#define MAXN 100001
#define mp std::make_pair
typedef std::pair<int,int> PII;
struct dsu{//并查集。
    public:
    	int *fa;
        dsu(int _n=0):n(_n){fa=new int[n+1](),sz=new int[n+1];fa[0]=sz[0]=0;for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;}//构造函数，初始化并查集。
        inline int* get_fa()const{return fa;}
        inline int* get_sz()const{return sz;}
        dsu&operator = (const dsu&y){if(this!=&y){n=y.size();int*new_fa=new int[n+1]();memcpy(new_fa,y.get_fa(),sizeof(int)*(n+1));delete[] fa;fa=new_fa;int*new_sz=new int[n+1]();memcpy(new_sz,y.get_sz(),sizeof(int)*(n+1));delete[] sz;sz=new_sz;}}
        dsu(const dsu& y){*this=y;}
        ~dsu(){delete[] fa;delete[] sz;}
        inline void clear(){n=0;delete[] fa;fa=new int[n+1]();fa[0]=0;}
        inline void resize(int _n){assert(_n>=0);delete[] fa;delete[] sz;fa=new int[(n=_n)+1]();sz=new int[n+1]();fa[0]=sz[0]=0;for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;}
        inline int size()const{return n;}
        inline int size(int x)const{assert(0<x && x<=n);return sz[x];}
        inline int find(const int x){assert(0<x && x<=n);return _find(x);}
        inline void merge(int x,int y){assert(0<x && x<=n);assert(0<y && y<=n);x=_find(x),y=_find(y);if(x==y)return;if(sz[x]<sz[y])std::swap(x,y);fa[y]=x,sz[x]+=sz[y];}//按秩合并。
        inline bool same(int x,int y){assert(0<x && x<=n);assert(0<y && y<=n);return _find(x)==_find(y);}
    private:
        int n;
        int*sz;
        inline int _find(const int x){return x==fa[x]?x:fa[x]=find(fa[x]);}//路径压缩。
};
int n,m,t=0;
std::vector<PII> G[1000001];//存储公司的线路。
std::vector<int> E[MAXN<<2];//建虚点后的新图。
int g[MAXN];//这个点对应虚点的编号。
bool vis[MAXN<<2];int dis[MAXN<<2];//是否访问和距离。
int dj(int S,int T){//广搜跑最短路。
	memset(vis,0,sizeof vis);
	std::queue<int> Q;
	memset(dis,0x3f,sizeof dis);
	dis[S]=0;Q.push(S);
	for(int u;!Q.empty();){
		u=Q.front();Q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		if(u==T) return dis[T];
		for(int v:E[u])if(!vis[v] && dis[v]>dis[u]+1) dis[v]=dis[u]+1,Q.push(v);
	}
	return vis[T]?dis[T]:-2;//因为最终答案会除以 2 所以不能到达要返回 -2。
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0,u,v,w;i<m;i++){
		scanf("%d%d%d",&u,&v,&w);
		G[w].push_back(mp(u,v));//记录 w 公司的线路是 u 到 v。
	}
	dsu d(n);
	for(int i=1;i<=1000000;i++){//枚举每一个公司。
		if(G[i].empty()) continue;
		for(const PII&e:G[i])d.fa[e.first]=e.first,d.fa[e.second]=e.second,g[e.first]=g[e.second]=vis[e.first]=vis[e.second]=0;//用多少清空多少，不要全部清空，否则会超时。
		std::vector<int>v;
		for(const PII&e:G[i]){
			d.merge(e.first,e.second);//合并两个点。
			if(!vis[e.first]) v.push_back(e.first),vis[e.first]=1;//记录被操作过的点。
			if(!vis[e.second]) v.push_back(e.second),vis[e.second]=1;
		}
		for(int j:v)if(d.size(d.find(j))>1){//当前点集的大小要大于 1，否则就是没有被合并过。
			int r=d.find(j);
			if(!g[r]) g[r]=++t;//如果没有建则新建一个虚点。
			int u=n+g[r];
			E[j].push_back(u),E[u].push_back(j);//当前点和虚点连边。
		}
	}
	printf("%d\n",dj(1,n)>>1);
	return 0;
}
```

---

## 作者：Zyh_AKer (赞：1)

## AT_arc061_c
### 题意简述
乘坐地铁从 $1$ 到 $n$，每个地铁属于一个公司，换乘到不同公司的地铁线路是，需要花费 $1$ 元，求最小花费。
### 算法标签
并查集，01-BFS。
### 题解
容易想到并查集，用并查集维护每个公司的连通块。  
#### Step 1
先读入，把同一公司的边放入 $C$ 中。
#### Step 2
遍历每个公司的边，建立并查集。
#### Step 3
将同一连通块内的点 $x$ 连向一个虚点 $y$ 连边，$x \to y$ 的边权为 $0$，$x \gets y$ 的边权为 $1$。
#### Step 4
01-BFS 求出 $1 \to n$ 的最短路即可。  
时间复杂度：$O(m \log m)$。
### My Code
```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int INF = 1e9;
int n, m;
vector < pair <int, int> > g[N];
vector < pair <int, int> > C[N + 1];
int hhoppitree[N];
int Find(int x){return (hhoppitree[x] == x ? x : hhoppitree[x] = Find(hhoppitree[x]));}
int tot;
int col[N];
int dis[N];
deque <int> dq;
void bfs()
{
    fill(dis + 1, dis + N, INF);
    dq.push_front(1);
    dis[1] = 0;
    while (!dq.empty())
    {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u])
        {
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                (w ? dq.push_back(v) : dq.push_front(v));
            }
        }
    }
    cout << (dis[n] == INF ? -1 : dis[n]);
}
int main()
{
    cin >> n >> m;
    tot = n;
    for (int i = 1, u, v, c; i <= m; i ++)
    {
        cin >> u >> v >> c;
        C[c].emplace_back(u, v);
    }
    for (int i = 1; i < N; i ++)
    {
        set <int> s;
        for (auto [x, y] : C[i])
        {
            s.insert(x), s.insert(y);
        }
        for (int x : s)
        {
            hhoppitree[x] = x;
        }
        for (auto [x, y] : C[i])
        {
            hhoppitree[Find(x)] = Find(y);
        }
        for (int x : s)
        {
            if (x == hhoppitree[x])
            {
                col[x] = ++tot;
            }
        }
        for (int x : s)
        {
            g[x].emplace_back(col[Find(x)], 0);
            g[col[Find(x)]].emplace_back(x, 1);
        }
    }
    bfs();
    return 0;
}
```

---

## 作者：yhylivedream (赞：1)

很容易想到每遇到通过同个颜色的边连通的连通块，就建一个虚点，将连通块内所有点向虚点连边权为 $1$ 的边，跑 BFS 再将答案除二。

这是 CF1941G 的做法，但这题不保证同颜色的边连通，所以还需处理出连通块，给出两种和题解里不同的方法。

## 第一种

对每个点开个 set 判重，枚举每个点的临边，若某临边的颜色 $c$ 该点没有出现过，该点出发搜出连通块。

瓶颈在于搜索时如何找到当前点临边中所有颜色为 $c$ 的边。

暴力找时间复杂度是 $m^2$，因为每种颜色都会对所有边遍历一遍，造出每条边颜色不同的菊花图即可卡掉，~~实际 2986ms 卡过去了~~。

考虑用 set 存边，使用 lower_bound 即可快速找到。

```cpp
#include <bits/stdc++.h>

using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 3e5 + 5, kMaxV = 1e6 + 5;

int n, m, idx, col[kMaxV], f[kMaxN];
set<int> st[kMaxN];
set<Pii> v[kMaxN];
vector<int> e[kMaxN];

inline void S(int x, int col) {
  if (st[x].count(col)) {
    return;
  }
  st[x].insert(col);
  e[x].push_back(idx), e[idx].push_back(x);
  auto it = v[x].lower_bound(Pii{col, 0});
  if (it->first == col) {
    for (; it != v[x].end() && it->first == col; it++) {
      S(it->second, col);
    }
  } 
}

int main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  cin >> n >> m, idx = n;
  for (int x, y, w; m--;) {
    cin >> x >> y >> w;
    v[x].insert({w, y}), v[y].insert({w, x});
  }
  for (int i = 1; i <= n; i++) {
    for (auto [w, nxt] : v[i]) {
      if (!st[i].count(w)) {
        idx++, S(i, w);
      }
    }
  }
  queue<int> q;
  fill(f + 1, f + idx + 1, -1);
  for (q.push(1), f[1] = 0; q.size(); q.pop()) {
    for (int nxt : e[q.front()]) {
      if (!~f[nxt]) {
        f[nxt] = f[q.front()] + 1, q.push(nxt);
      }
    }
  }
  cout << (~f[n] ? f[n] / 2 : -1);
  return 0;
}
```

## 第二种

对边按颜色排序，双指针找出所有颜色为 $c$ 的边。

对这些边建图，跑普通 DFS 搜连通块即可，而起点只可能是一条边的某个端点，快速清空图直接回滚即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 3e5 + 5, kMaxV = 1e6 + 5;

int n, m, idx, tg, f[kMaxN], vis[kMaxN];
array<int, 3> a[kMaxN];
vector<int> e_[kMaxN], e[kMaxN];

void S(int x) {
  if (vis[x] == tg) {
    return;
  }
  vis[x] = tg;
  e[x].push_back(idx), e[idx].push_back(x);
  for (int nxt : e_[x]) {
    S(nxt);
  }
}

int main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  cin >> n >> m, idx = n;
  for (int i = 1, x, y, w; i <= m; i++) {
    cin >> x >> y >> w;
    a[i] = {w, x, y};
  }
  sort(a + 1, a + m + 1);
  for (int i = 1, j; i <= m; i = j) {
    for (j = i; a[j][0] == a[i][0]; j++);
    for (int x = i; x < j; x++) {
      e_[a[x][1]].push_back(a[x][2]);
      e_[a[x][2]].push_back(a[x][1]);
    }
    tg++;
    for (int x = i; x < j; x++) {
      vis[a[x][1]] != tg && (idx++, S(a[x][1]), 0);
    }
    for (int x = i; x < j; x++) {
      e_[a[x][1]].clear(), e_[a[x][2]].clear();
    }
  }
  queue<int> q;
  fill(f + 1, f + idx + 1, -1);
  for (q.push(1), f[1] = 0; q.size(); q.pop()) {
    for (int nxt : e[q.front()]) {
      if (!~f[nxt]) {
        f[nxt] = f[q.front()] + 1, q.push(nxt);
      }
    }
  }
  cout << (~f[n] ? f[n] / 2 : -1);
  return 0;
}
```

---

## 作者：i_love_xqh (赞：1)

# 题目链接

[[ARC061E] すぬけ君の地下鉄旅行](https://www.luogu.com.cn/problem/AT_arc061_c)。

# 分析

## 题目大意

给出 $N$ 个站点和 $M$ 条地铁线，每条地铁线都有自己所属的公司。经过相同公司的地铁线只需花费一元，但换乘其他公司的地铁线就需再花一元。求从 $1$ 号站台到 $N$ 号站台的最小花费。

## 题目分析

不难发现，将相同公司的边提出来，边与边之间会产生连通块，连通块中从一点到其它任意一点的花费为 $1$，所以本质上就是求 $1$ 号站台到 $N$ 号站台的经过的最少连通块的数量。

比如拿样例二举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/s9ek0s5n.png)

如图，边上的值表示所属的公司，那么由图可分为以下连通块：

![](https://cdn.luogu.com.cn/upload/image_hosting/zgg6xdm8.png)

将相同颜色的边视为一个连通块，那么从 $1$ 到 $8$ 所需的最少经过的连通块的数量即为 $2$，经过绿色和棕色两个连通块。

于是一种暴力的方法就是，将每个连通块中的点，两两连一条边权为 $1$ 的边，然后再跑最短路，但这样建边数量达到了 $N^2$ 级别。

于是考虑建图优化，如果 $1\sim 4$ 在同一个连通块中，那么暴力的建边为：

![](https://cdn.luogu.com.cn/upload/image_hosting/lj8x840x.png)

考虑一种虚点的技巧，增加一个虚拟节点 $5$，然后每个点向 $5$ 连一条边权为 $0.5$ 的无向边：

![](https://cdn.luogu.com.cn/upload/image_hosting/3nrpzr27.png)

这样也可以实现连通块中一点到其他任意一点花费为 $1$，且最多只用连 $4\times M$ 条有向边，因为取极端情况每条边所属的公司都不一样，即每条边单独一个连通块，那么连接虚点的有 $2\times M$ 条无向边，即连 $4\times M$ 条有向边，这样点数最多也就只有 $N+M$ 个点。

于是便得出最终的做法：

- 将每个公司的边单独提出来，将边连接的两个点并在一个连通块中。

- 对于每个公司，看边所构成的**所有**连通块，对于每个连通块创建一个虚拟节点，连通块内的点向虚拟节点连一条边权为 $0.5$ 的无向边。

- 跑正常最短路。

为了方便计算，将边权改为 $1$，最终答案 $\times \frac{1}{2}$ 即可，因为边权有且只有 $1$，所以可以舍弃 dijkstra，用 bfs。

Code：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
};
vector<node>cp[1000010];
set<int>p,d[1000010];
int fath[1000010];
int getfath(int v){
	return v==fath[v]?v:fath[v]=getfath(fath[v]);
}
struct edge{
	int y,next;
}e[800010];
int cnt,elast[300010],ds;
void add(int x,int y){
	e[++cnt].y=y;
	e[cnt].next=elast[x];
	elast[x]=cnt;
}
bool vis[300010];
int dis[300010];//注意数组大小
queue<int>pq;
int main(){
	int n,m,mx=0;
	scanf("%d%d",&n,&m);
	ds=n;
	for(int i=1;i<=m;i++){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		mx=max(mx,c);
		cp[c].push_back({x,y});//将同一个公司的边存进vector中
	}
	for(int i=1;i<=mx;i++){
		p.clear();//清空
		for(auto j:cp[i]){
			if(!p.count(j.x))p.insert(j.x);//避免重复
			if(!p.count(j.y))p.insert(j.y);
		}//开一个集合，放入该公司所有边所连接的点
		for(auto j:p)fath[j]=j,d[j].clear();//将并查集初始化
		for(auto j:cp[i])fath[getfath(j.x)]=getfath(j.y);//将边所连接的两个点放入同一个连通块中
		for(auto j:p)d[getfath(j)].insert(j);//存入同一个连通块的点
		for(auto j:p){
			if(getfath(j)==j){//枚举每个连通块
				ds++;//虚拟节点
				for(auto k:d[j]){
					add(k,ds);
					add(ds,k);//连边
				}
			}
		}
	}
	for(int i=1;i<=ds;i++)dis[i]=1e9;//dis初始化
	dis[1]=0;
	pq.push(1);
	while(!pq.empty()){
		int u=pq.front();
		pq.pop();
		if(u==n){
			printf("%d\n",dis[u]/2);//注意除以2
			return 0;
		}
		if(vis[u])continue;
		vis[u]=true;
		for(int i=elast[u];i;i=e[i].next){
			int v=e[i].y;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				pq.push(v);
			}
		}
	}//bfs
	if(dis[n]==1e9)printf("-1");//无解情况
	return 0;
}
```

---

## 作者：CoderCharlie (赞：0)

### 题意
在某个城市中有 $N$ 个车站，由 $M$ 条地铁线连接起来。已知第 $i$ 条地铁线连接两个车站 $p_i$ 和 $q_i$，由公司 $c_i$ 运营。在两个不同公司运营的线路之间换乘要付钱~~抢铁行为~~，现在求从 $1$ 号站到 $N$ 号站要多少钱。

### 思路
由于相同的地铁公司之间换乘是不要付钱的，所以可以考虑把相同地铁公司运营的所有车站缩成一个点。更进一步想，我们可以给每一个公司修建一个总的“车辆段”，把所有该公司运营线路可以到达的车站都连接到这个“车辆段”上去，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uopy0gab.png)

这样我们就可以用很少的边去实现上述操作。

但是这样做有一个**漏洞**，会错。

原因就在于，**一个地铁公司运营的所有线路可能不止在一个联通块内**。~~南京地铁7号线就是这样。~~

所以我们可以用一个并查集去给每个公司维护若干个这样的联通块。

然后我们再在处理后的图上跑一遍最短路即可。

注意我们建边的时候为方便起见，边权为整数 $1$。但是这样会导致换乘的代价变成了原来的两倍。故答案输出时要额外除以 $2$。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define PI pair<int,int>
int fa[2001000],id[2001000];
int dis[2001000];
bool h[2001000];
vector<int> a[2001000];
vector<PI> e[2001000];
priority_queue<PI,vector<PI>,greater<PI> > q;
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void dijk(int s)
{
	memset(dis,0x3f,sizeof dis);
	memset(h,0,sizeof h);
	dis[s]=0;
	q.push(make_pair(0,s));
	while (!q.empty())
	{
		int u;
		u=q.top().second;
		q.pop();
		if (h[u]) continue;
		h[u]=1;
		for (auto v:a[u])
		{
			if (dis[v]>dis[u]+1)
			{
				dis[v]=dis[u]+1;
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		e[c].push_back({u,v});
	}
	//记录每一条边
	int ID=n+1;
	for (int i=1;i<=1000000;i++)
	{
		for (auto j:e[i])
		{
			fa[j.first]=j.first;
			fa[j.second]=j.second;
			id[j.first]=-1;
			id[j.second]=-1;
			h[j.first]=0;
			h[j.second]=0;
		}
		for (auto j:e[i])
			fa[Find(j.first)]=Find(j.second);
		for (auto j:e[i])
		{
			int x=j.first,y=j.second;
			if (!h[x])
			{
				int rt=Find(x);
				if (id[rt]==-1)
				{
					id[rt]=ID;
					ID++;
				}
				a[x].push_back(id[rt]);
				a[id[rt]].push_back(x);
				h[x]=1;
			}
			if (!h[y])
			{
				int rt=Find(y);
				if (id[rt]==-1)
				{
					id[rt]=ID;
					ID++;
				}
				a[y].push_back(id[rt]);
				a[id[rt]].push_back(y);
				h[y]=1;
			}
		}
	}
	//处理出若干联通块，并重新建图
	dijk(1);
	if (dis[n]==0x3f3f3f3f) cout<<-1;
	else cout<<dis[n]/2;
	return 0;
}
```

---

