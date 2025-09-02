# Dynamic Shortest Path

## 题目描述

You are given a weighted directed graph, consisting of $ n $ vertices and $ m $ edges. You should answer $ q $ queries of two types:

- 1 v — find the length of shortest path from vertex $ 1 $ to vertex $ v $ .
- 2 c $ l_{1}\ l_{2}\ ...\ l_{c} $  — add $ 1 $ to weights of edges with indices $ l_{1},l_{2},...,l_{c} $ .

## 说明/提示

The description of changes of the graph in the first sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843D/24bd98e5125f858d47fdfa77b158c3a581ad248b.png)

The description of changes of the graph in the second sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843D/d325c1b90420a99987b13a59d8addca767eb6927.png)

## 样例 #1

### 输入

```
3 2 9
1 2 0
2 3 0
2 1 2
1 3
1 2
2 1 1
1 3
1 2
2 2 1 2
1 3
1 2
```

### 输出

```
1
0
2
1
4
2
```

## 样例 #2

### 输入

```
5 4 9
2 3 1
2 4 1
3 4 1
1 2 0
1 5
1 4
2 1 2
2 1 2
1 4
2 2 1 3
1 4
2 1 4
1 4
```

### 输出

```
-1
1
2
3
4
```

# 题解

## 作者：蒟蒻溴化氢 (赞：25)

神仙题 神仙切 @Ctime_Pup_314 orz

有一种$O(m+W)$的做法(W是值域)

考虑裸的迪杰斯特拉的过程

我们每次找全局$dis$的最小值  然后取出这个点进行拓展

现在我们在做迪杰斯特拉的时候 对值域开一个桶 dij的时候扫过这些桶
取出最小的值进行拓展(变成了bfs)

因为相同的值有很多点 因此我们要拿一个数据结构来保存这些点(可以是vector或者queue或者链表)

对于这道题 我们可以先用普通的迪杰斯特拉跑一边最短路 记录1到每一个点的最短路dis

然后我们赋值一个新边权:对于一条边$(x,y)$ 我们把它的边权赋值为$dis[x]+e[i].w-d[y]$ 

由于边权是只增加不减少的 所以最短路只会变大 不会变小

那么在新图上走的含义就是到这个点的距离增量

要最小化这个增量 我们就应该走一个最短路

还有一件事 ~~给老爹倒杯茶~~


因为更新c条边 所以最短路对多增加c

有因为最短路的路径构成是一棵树 所以最多增加$n-1$

所以我们把$<=min(c,n-1)$ 的增量加入队列


```cpp
#include <iostream> 
#include <cstdio>
#include <cstring>
#include <queue>
#define il inline
#define res register int
#define ll long long
#define pa pair <ll,int>
#define mp make_pair
using namespace std;
const int N=1e5+5;
const int M=1e5+5; 
const ll inf=0x3f3f3f3f3f3f3f3f;
il int read()
{
	int x=0,f=0,c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return f?-x:x;
}
struct Edge
{
	int to,next,w;
}e[M];
int head[N],cnt;
il void add(int a,int b,int c)
{
	cnt++;
	e[cnt].to=b;e[cnt].w=c;e[cnt].next=head[a];
	head[a]=cnt; 
}
ll d[N];
bool vis[N];
int n,m,q;
ll dij(int s)
{
	priority_queue< pa > q;
	memset(d,0x3f,sizeof d);
	memset(vis,0,sizeof vis);
	d[s]=0; q.push( mp(0,s) );
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(res i=head[x];i;i=e[i].next)
		{
			int y=e[i].to;
			if(d[y]>d[x]+e[i].w) d[y]=d[x]+e[i].w, q.push(mp(-d[y],y ));
		}
	}
}
queue<int> s[N];
ll f[N],mx;

void bfs(int c)
{
	mx=0;
	for(res i=0;i<=mx;i++)//遍历值域 更新值域
		while(!s[i].empty())
		{
			int x=s[i].front(); s[i].pop();
			if(f[x]<i) continue;
			for(res i=head[x];i;i=e[i].next)
			{
				int y=e[i].to,z=d[x]+e[i].w-d[y];
				if(f[y]>f[x]+z)
				{
					f[y]=f[x]+z;
					if(f[y]<=min(c,n-1))  
					{
						s[f[y]].push(y);
						mx=max((ll)mx,f[y]);
					}
				}
			}
		}
}

int main()
{
	n=read(); m=read(); q=read();
	for(res i=1;i<=m;i++) 
	{
		int x=read(),y=read(),z=read();
		add(x,y,z); 
	}
	dij(1);
//	cout<<"dfa:"<<inf<<endl;
	while(q--)
	{
		int opt=read(),c=read();
		if(opt==1) d[c]==inf?puts("-1"):printf("%I64d\n",d[c]);
		else 
		{
			for(res i=1;i<=c;i++) e[read()].w++;
			memset(f,0x3f,sizeof f);
			f[1]=0; s[0].push(1); 
			bfs(c);
			for(res i=1;i<=n;i++) d[i]=min(inf,f[i]+d[i]);
		}
	}
	return 0;
}
```


---

## 作者：skylee (赞：19)

# [CF843D]Dynamic Shortest Path

### 题目大意：

给定一个带权有向图，包含$n(n\le10^5)$个点和$m(m\le10^5)$条边。共$q(q\le2000)$次操作，操作包含以下两种：

- $1\:v$——查询从$1$到$v$的最短路。
- $2\:c\:l_1\:l_2\:\ldots\:l_c$——将边$l_1,l_2,\ldots,l_c$增加$1$的权值。

### 思路：

首先使用Dijkstra算法求出原图的单源最短路径$dis[i]$。对于所有的操作$2$，考虑增加边权后对答案的影响。不难发现每次修改边权后$dis[i]$都会增加一定量或保持不变。不妨将每次每个点的增加量记作$add[i]$，考虑增加边权后计算$add[i]$的值。

类比Dijkstra算法的“松弛”操作，对于一个结点$x$，若$add[x]\ne0$，我们可以用$x$来松弛别的结点。枚举$x$的下一个结点$y$，若此时用$x$作为最短路中的上一任结点，则最短路长度需要增加$dis[x]+w(x,y)+add[x]-dis[y]$。而$add[y]$则需要对所有这样的值取$\min$。这样完成所有的松弛操作后，$dis'[i]=dis[i]+add[i]$。而这可以用BFS实现，其中当$add[i]>c$时则没有“松弛”的必要，可以进行剪枝。

配对堆优化Dijkstra复杂度$\mathcal O(n\log n+m)$，单次BFS更新最短路$\mathcal O(q(n+m))$，总时间复杂度$\mathcal O(n\log n+m+q(n+m))$。

### 细节：

注意边权可能为$0$，因此Dijkstra中被松弛的结点可能会跑到堆顶，不能松弛完再删除堆顶元素。本题时间限制较紧，实现时注意优化常数。

### 源代码：

```cpp
#include<queue>
#include<cstdio>
#include<cctype>
#include<climits>
#include<algorithm>
#include<functional>
#include<forward_list>
#include<ext/pb_ds/priority_queue.hpp>
using int64=long long;
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
constexpr int N=1e5+1;
int n,w[N],add[N];
int64 dis[N];
using Edge=std::pair<int,int>;
std::forward_list<Edge> e[N];
using Vertex=std::pair<int64,int>;
__gnu_pbds::priority_queue<Vertex,std::greater<Vertex>> q;
__gnu_pbds::priority_queue<Vertex,std::greater<Vertex>>::point_iterator p[N];
inline void dijkstra() {
	for(register int i=1;i<=n;i++) {
		p[i]=q.push({dis[i]=i==1?0:LLONG_MAX,i});
	}
	while(!q.empty()&&q.top().first!=LLONG_MAX) {
		const int x=q.top().second;
		q.pop();
		for(register auto &j:e[x]) {
			const int &y=j.first,&w=::w[j.second];
			if(dis[x]+w<dis[y]) {
				q.modify(p[y],{dis[y]=dis[x]+w,y});
			}
		}
	}
	q.clear();
}
std::queue<int> v[N];
int main() {
	n=getint();
	const int m=getint(),q=getint();
	for(register int i=1;i<=m;i++) {
		const int u=getint(),v=getint();
		w[i]=getint();
		e[u].emplace_front(std::make_pair(v,i));
	}
	dijkstra();
	for(register int i=1;i<=n;i++) {
		if(dis[i]==LLONG_MAX) dis[i]=-1;
	}
	for(register int i=0;i<q;i++) {
		if(getint()==1) {
			printf("%lld\n",dis[getint()]);
		} else {
			const int c=getint();
			for(register int i=0;i<c;i++) w[getint()]++;
			std::fill(&add[1],&add[n]+1,c+1);
			v[add[1]=0].emplace(1);
			for(register int i=0;i<=c;i++) {
				for(;!v[i].empty();v[i].pop()) {
					const int &x=v[i].front();
					if(add[x]!=i) continue;
					for(register auto &j:e[x]) {
						const int &y=j.first,&w=::w[j.second];
						const int64 d=dis[x]+w+add[x]-dis[y];
						if(d<add[y]) v[add[y]=d].emplace(y);
					}
				}
			}
			for(register int i=1;i<=n;i++) {
				if(add[i]!=c+1) dis[i]+=add[i];
			}
		}
	}
	return 0;
}
```



---

## 作者：robin12138 (赞：9)


#### 动态最短路：[CF843D Dynamic Shortest Path](https://www.luogu.org/problem/CF843D)


题意：
有一张$n$个点$m$条边的有向带权图，$q$次询问：

```1``` $1 v$ 询问从$1$到$v$的最短路，无解输-$1$

```2``` $c\ l_1\ l_2\ ...\ l_c\ l_i$的边权增加$1$

$q \leqslant 2000 n,m \leqslant 10^5$

题解：

暴力$dij$显然过不了，需要优化

首先我们知道一种$dij$的优化方法：
保证边权都为正，且边权和不超过$W$的时候

性质：如果用 $x$ 更新周围的点 $t$ 的最短路，那么
源到 $t$ 的最短路长度一定大于到 $x$ 的最短路长度。

用$0$~$W$ 的(桶)队列代替堆

从小到大枚举值来取出当前最小值。根据性质，加
入的元素一定只会加到当前枚举的这个值的后面。

复杂度$O(m+W)$，现在我们要尽量缩小值域就可以优化了

先做一遍正常$dij$，然后考虑该边若干条边造成的影响

令每条边$(x,y)$的边权为$dis[x]+edge[i]-dis[y]$,

假设这样求出来的最短路为$f[x]$，则$f[x]$表示新图中此点的距离较原图的增量

分析$f[x]$的值域：一次更新$c$条边，则最短路最多增加$c$，$n$个点的最短路共经过$n-1$条边，
则最短路增加不超过$n-1$,而$n$的范围是$10^5$，就可以接受了，总共复杂度$O(q(m+W))$

```cpp
//CF843D-Dynamic-ShortestPath
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <queue>
using namespace std;

typedef long long LL;
#define cls(x) memset(x,0,sizeof(x))
#define For(i,j,k) for(register int i=(j);i<=(k);++i)
#define Rep(i,j,k) for(register int i=(j);i>=(k);--i)
#define rint register int
#define il inline

il int read(int x=0,int f=1,char ch='0')
{
    while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f*x;
}

const int N=1e5+5;
int head[N],ver[N],nxt[N],edge[N];
int n,m,Q,tot;
LL d[N],f[N],t; bool v[N];
il void add(int x,int y,int z)
{ ver[++tot]=y; nxt[tot]=head[x]; head[x]=tot; edge[tot]=z; }

il void dij()
{
    priority_queue<pair<LL,int> > q; 
    memset(d,0x3f,sizeof(d)); d[1]=0;
    q.push(make_pair(0,1));
    while(q.size())
    {
        int x=q.top().second; q.pop();
        if(v[x]) continue; v[x]=1;
        for(rint i=head[x];i;i=nxt[i])
        {
            int y=ver[i]; if(d[y]<=d[x]+edge[i]) continue;
            d[y]=d[x]+edge[i]; q.push(make_pair(-d[y],y));
        }
    }
}

queue<int> q[N];
il void work(int maxn)
{
    memset(f,0x3f,sizeof(f)); 
    f[1]=0; q[0].push(1);
    for(rint now=0;now<=t;++now) while(q[now].size())
    {
        int x=q[now].front(); q[now].pop(); if(f[x]<now) continue;
        //一个点可能被插入多个队列中
        for(rint i=head[x];i;i=nxt[i])
        {
            int y=ver[i],z=d[x]+edge[i]-d[y];
            if(f[y]<=f[x]+z) continue;
            f[y]=f[x]+z; if(f[y]>maxn) continue;
            q[f[y]].push(y); t=max(t,f[y]);
        }
    }
    For(i,1,n) d[i]=min(d[0],d[i]+f[i]);
}

int main()
{
    n=read(); m=read(); Q=read();
    For(i,1,m) { int x=read(),y=read(),z=read(); add(x,y,z); }
    dij();
    while(Q--)
    {
        int op=read();
        if(op==1)
        {
            int x=read();
            printf("%lld\n",d[x]>=d[0]?-1:d[x]);
        }
        else
        {
            int c=read(),k; For(i,1,c) k=read(),++edge[k];
            work(min(c,n-1));
        }
    }
    return 0;
}
```

---

## 作者：hhhqx (赞：4)

~~luogu RMJ 加油.......~~

如果每修改一次就 dij 复杂度 $O(q (n + m \log n))$ 过不去的。

暴力 dij 是因为值域很大需要用到堆，带个 log，要是值域很小就可以直接分层 BFS 了……

每次增加的边权很小，求最短路增量？设 $dis_i$ 表示这次修改前最短路，$f_i$ 表示这次修改后最短路增量。

有 $f_v = \min\limits_{(u,v) \in E}{dis_u + f_u + w(u,v) - dis_v}$。

而每次修改后最大增量是小于等于 $c$ 的，可以分层 BFS。

注意每一层可能由自己这一层转移来（因为边权为 0），所以每一层内部需要用队列。

复杂度 $O(q(c + m + n))$。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = 1e5 + 3;

struct Edge{ // 链式前向星 方便修改边权
  int to, epre, w;
}eg[MAXN];
int egtop[MAXN], tot = 0;

int ADDeg(int u, int v, int val){
  tot++, eg[tot].to = v, eg[tot].w = val;
  eg[tot].epre = egtop[u], egtop[u] = tot;
  return tot;
}

int n, m, Q, id[MAXN];
LL dis[MAXN], f[MAXN];
queue<int> p[MAXN];

void dij(){
  for(int i = 1; i <= n; i++){
    dis[i] = 1e18;
  }
  priority_queue<pair<LL, int>> pq;
  dis[1] = 0, pq.push({0, 1});
  while(!pq.empty()){
    pair<LL, int> w = pq.top();
    int i = w.second;
    pq.pop();
    if(dis[i] < -w.first) continue;
    for(int e = egtop[i]; e > 0; e = eg[e].epre){
      int nx = eg[e].to;
      LL nw = dis[i] + eg[e].w;
      if(dis[nx] > nw) dis[nx] = nw, pq.push({-nw, nx});
    }
  }
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0); 
  cin >> n >> m >> Q;
  for(int i = 1, U, V, W; i <= m; i++){
    cin >> U >> V >> W, id[i] = ADDeg(U, V, W);
  }
  dij();
  for(int q = 1, op, c, v; q <= Q; q++){
    cin >> op >> c;
    if(op == 1){
      cout << (dis[c] >= 1e18 ? -1 : dis[c]) << "\n";
    }else{
      for(int _c = 0; _c < c; _c++){
        cin >> v, eg[id[v]].w++;
      }
      for(int i = 1; i <= n; i++) f[i] = c + 1;
      f[1] = 0, p[0].push(1);
      for(int d = 0; d <= c; d++){
        while(!p[d].empty()){
          int x = p[d].front();
          p[d].pop();
          if(f[x] < d) continue;
          for(int e = egtop[x]; e > 0; e = eg[e].epre){
            int nx = eg[e].to;
            LL nw = dis[x] + f[x] + eg[e].w - dis[nx];
            if(nw < f[nx]) f[nx] = nw, p[nw].push(nx);
          }
        }
      }
      for(int i = 1; i <= n; i++) dis[i] += f[i];
      for(int d = 0; d <= c; d++){
        while(!p[d].empty()) p[d].pop();
      }
    }
  }
  return 0; 
}
```

---

## 作者：Super_Cube (赞：4)

# Solution

~~不会有人看到这题会去想正解吧。~~

注意到数据范围很小啊，$q\le 2000$，还良心地给开了 10s，那这不纯纯暴力题？

修改操作先存着，等到询问时一起改完了重跑最短路，当然如果没有存储的修改那就不重跑最短路。

不连通无解的情况可以预处理，因为图的形态不会改变，在询问开始前跑最短路，现在跑不到的地方一定以后也跑不到。

时间复杂度（粗略计算）：$O(qm\log m)$。有个 $\dfrac{1}{2}$ 的常数在前面（因为最多只会重跑 $\dfrac{q}{2}$ 次最短路）。

最短路如果用 Dijkstra 会 TLE（用的 `std::priority_queue`，没有尝试过 `__gnu_pbds::priority_queue`），推测是堆的 $\log$ 导致的。去掉它的想法也很单纯与直接啊：换成 SPFA。

朴素 SPFA 还是会 TLE 的，但是你随便打几个关于 SPFA 的优化，CF 上的数据就能飞快地草过去了。

当然复杂度肯定是错的。讨论区已经给出 hack 的方法了，不过那个数据用 Dijkstra 刚好可以过。

如果你实在卡不过去，打快读快写与火车头。

不然你还是去学正解吧。

**谨记：SPFA 已死，慎用 SPFA。**

---

## 作者：傅思维666 (赞：3)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11778651.html)

~~2019.11.1模拟赛T3 50分场~~

一开始觉得正解应该使用数据结构优化一下，但是并不知道用什么数据结构。所以直接暴力修改反复跑最短路。~~我傻X用了SPFA~~

不要幻想了，一定会T。

#### **正解：**

因为跑很多遍DIJ一定会T，这不是你加不加优化就能改变的了的。

所以我们想一下，能不能只跑一遍DIJ。

跟着这个思路，我们发现：由于是单源最短路，所以对于更改的边权，只会更改一部分节点的最短路。所以我们试着只跑一遍DIJ，然后在这个已经被处理出来的初始状态下的最短路进行修改。

具体怎么办呢？

我们设置$f[i]$表示$i$点的最短路距离增加量。对于增加值，我们开一个桶。这个桶可以使用$queue$来实现。这个队列里存的是这个距离增加量的节点编号们。那么我们从这些点中进行扩展。这次的扩展需要引入新边权（因为$val$已经被修改过了，所以扩展增量的边权应该被定义成$dist[x]-dist[y]+val[i]$）因为我们一次性增加了$c$条边，所以需要把$c$和$n-1$（最短路路径是树）做一下比较，如果这个增量比他俩的最小值还要小，说明还有后续的更新，再把它压入桶里进行继续松弛。

这样就完成了修改的过程。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int maxn=1e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
int n,m,Q;
int tot,head[maxn],val[maxn],nxt[maxn],to[maxn];
priority_queue<pair<int,int> >q;
int v[maxn],dist[maxn];
queue<int> t[maxn];
int f[maxn],maxx;
void add(int x,int y,int z)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    val[tot]=z;
    head[x]=tot;
}
void dijkstra()
{
    memset(dist,0x3f,sizeof(dist));
    memset(v,0,sizeof(v));
    q.push(make_pair(0,1));
    dist[1]=0;
    while(!q.empty())
    {
        int x=q.top().second;
        if(v[x])
        {
            q.pop();
            continue;
        }
        x=q.top().second;q.pop();v[x]=1;
        for(int i=head[x];i;i=nxt[i])
        {
            int y=to[i];
            if(dist[y]>dist[x]+val[i])
                dist[y]=dist[x]+val[i],q.push(make_pair(-dist[y],y));
        }
    }
}
void bfs(int v)
{
    memset(f,0x3f,sizeof(f));
    f[1]=0;
    t[0].push(1);
    maxx=0;
    for(int i=0;i<=maxx;i++)
        while(!t[i].empty())
        {
            int x=t[i].front();
            t[i].pop();
            if(f[x]<i)
                continue;
            for(int i=head[x];i;i=nxt[i])
            {
                int y=to[i];
                int z=dist[x]+val[i]-dist[y];
                if(f[y]>f[x]+z)
                {
                    f[y]=f[x]+z;
                    if(f[y]<=min(v,n-1))
                    {
                        t[f[y]].push(y);
                        maxx=max(maxx,f[y]);
                    }
                }
            }
        }
}
signed main()
{
    scanf("%I64d%I64d%I64d",&n,&m,&Q);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%I64d%I64d%I64d",&x,&y,&z);
        add(x,y,z);
    }
    dijkstra();
    while(Q--)
    {
        int opt,v,c;
        scanf("%I64d%I64d",&opt,&v);
        if(opt==1)
        {
            if(dist[v]==INF)
            {
                puts("-1");
                continue;
            }
            printf("%I64d\n",dist[v]);
        }
        else
        {
            for(int i=1;i<=v;i++)
            {
                int a;
                scanf("%I64d",&a);
                val[a]++;
            }
            bfs(v);
            for(int i=1;i<=n;i++)
                dist[i]=min(INF,f[i]+dist[i]);
        }
    }
    return 0;
}
```



---

## 作者：xfrvq (赞：3)

每次修改都跑 $\tt dijkstra$，复杂度 $O\left(q(n+m)\log n\right)$，少个 $\log$ 可以通过。

注意到 $\tt dijkstra$ 的 $\log$ 复杂度来自于堆，如果不用堆而是对 $dis$ 的值域开 $\tt queue$，枚举小值域向大值域转移，复杂度 $O(V+n+m)$。

于是设每一轮 $dis$ 的增加量为 $\Delta$，$0\le\Delta\le c$（$c$ 条边每条至多贡献一次）。正常转移是 $dis_v\gets dis_u+w$，这里 $dis_v+\Delta_v\gets dis_u+\Delta_u+w$，即 $\Delta_v\gets dis_u+\Delta_u-dis_v+w$。

代入 $V=c$，总复杂度 $O((n+m)\log n+q(n+m))$。

代码使用 `__gnu_pbds` 配对堆，可让 $\tt dijkstra$ 做到 $O(n\log n+m)$。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;

#ifdef ONLINE_JUDGE
static char buf[16777216],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,16777216,stdin),p1==p2)?EOF:*p1++
#endif

inline int read(){
    register int x = 0;
    register char c = getchar();
    for(;c < '0' || c > '9';c = getchar());
    for(;c >= '0' && c <= '9';c = getchar())
        x = x * 10 + (c ^ '0');
    return x;
}

using ll = long long;
using pq = __gnu_pbds::priority_queue<pair<ll,int>,greater<>,__gnu_pbds::pairing_heap_tag>;

const int N = 1e5 + 5;

int n,m,q,k,w[N],dlt[N];
ll dis[N];
vector<pair<int,int>> G[N];
queue<int> V[N];
pq Q; pq::point_iterator P[N];

void dij(){
	for(int i = 1;i <= n;++i)
		P[i] = Q.push({dis[i] = i == 1 ? 0 : 1e18,i});
	while(Q.size() && Q.top().first < 1e18){
		auto[d,u] = Q.top(); Q.pop();
		for(auto[v,i] : G[u])
			if(dis[v] > dis[u] + w[i])
				Q.modify(P[v],{dis[v] = dis[u] + w[i],v});
	}
	for(int i = 1;i <= n;++i) if(dis[i] == 1e18) dis[i] = -1;
}

void dij1(){
	for(int i = 2;i <= n;++i) dlt[i] = k + 1;
	V[0].push(1);
	for(int d = 0;d <= k;++d)
		while(V[d].size()){
			int u = V[d].front(); V[d].pop();
			if(dlt[u] != d) continue;
			for(auto[v,i] : G[u])
				if(dlt[v] > dis[u] + w[i] - dis[v] + dlt[u])
					V[dlt[v] = dis[u] + w[i] - dis[v] + dlt[u]].push(v);
		}
	for(int i = 1;i <= n;++i) if(dlt[i] < k + 1) dis[i] += dlt[i];
}

int main(){
	n = read(),m = read(),q = read();
	for(int i = 1,u,v;i <= m;++i)
		u = read(),v = read(),w[i] = read(),G[u].emplace_back(v,i);
	for(dij();q--;){
		if(read() == 2){
			for(int i = k = read();i--;) ++w[read()];
			dij1();
		} else printf("%lld\n",dis[read()]);
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

~~没卡 SPFA+SLF+LLL，秒了~~

每次更新完了暴力 dij，时间复杂度是 $O(qm\log m)$，难以通过。

问题主要出现在这个 $\log$ 上，为了优化掉这个 $\log$，我们可以考虑 ~~SPFA~~ 使用其它的结构来搞掉这个堆。

发现增量非常少，最多只有 $10^6$，如果我们是对增量跑最短路的话，给每种增量开个队列就行了。

考虑增量的计算式子：

$$f_v\gets\max\{dis_u+f_u+w_{u,v}-dis_v\}$$

仍然地，每条边只会在 $u$ 第一次出队的时候松弛，所以单次更新最短路的时间复杂度就是 $O(m)$，总时间复杂度就是 $O(qm)$。

本题略微卡常。

---

