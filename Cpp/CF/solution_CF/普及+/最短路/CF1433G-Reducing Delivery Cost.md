# Reducing Delivery Cost

## 题目描述

You are a mayor of Berlyatov. There are $ n $ districts and $ m $ two-way roads between them. The $ i $ -th road connects districts $ x_i $ and $ y_i $ . The cost of travelling along this road is $ w_i $ . There is some path between each pair of districts, so the city is connected.

There are $ k $ delivery routes in Berlyatov. The $ i $ -th route is going from the district $ a_i $ to the district $ b_i $ . There is one courier on each route and the courier will always choose the cheapest (minimum by total cost) path from the district $ a_i $ to the district $ b_i $ to deliver products.

The route can go from the district to itself, some couriers routes can coincide (and you have to count them independently).

You can make at most one road to have cost zero (i.e. you choose at most one road and change its cost with $ 0 $ ).

Let $ d(x, y) $ be the cheapest cost of travel between districts $ x $ and $ y $ .

Your task is to find the minimum total courier routes cost you can achieve, if you optimally select the some road and change its cost with $ 0 $ . In other words, you have to find the minimum possible value of $ \sum\limits_{i = 1}^{k} d(a_i, b_i) $ after applying the operation described above optimally.

## 说明/提示

The picture corresponding to the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/458c58c5f1fe2e61828172bc475f01c796e3199a.png)

There, you can choose either the road $ (2, 4) $ or the road $ (4, 6) $ . Both options lead to the total cost $ 22 $ .

The picture corresponding to the second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1433G/b1ea600359edb25eb81785c2a8e73df295a9c0a5.png)

There, you can choose the road $ (3, 4) $ . This leads to the total cost $ 13 $ .

## 样例 #1

### 输入

```
6 5 2
1 2 5
2 3 7
2 4 4
4 5 2
4 6 8
1 6
5 3```

### 输出

```
22```

## 样例 #2

### 输入

```
5 5 4
1 2 5
2 3 4
1 4 3
4 3 7
3 5 2
1 5
1 3
3 3
1 5```

### 输出

```
13```

# 题解

## 作者：vectorwyx (赞：8)

~~Codeforces竟然也会出纯图论题~~


------------
这题的核心是一个很经典的套路，就是求两点之间经过某一条边的最短路。

假设这两点为 $x,y$，且必须经过由点 $u$ 连向点 $v$ 的边，那么从 $x$ 到 $y$ 的最短路（将图看做有向图）肯定能划分为三部分：从 $x$ 到 $u$，从 $u$ 到 $v$，从 $v$ 到 $y$。

从 $u$ 到 $v$ 的长度已经确定，剩下两部分贪心地走最短路一定是最优的，因此答案为 $dis(x,u)+dis(u,v)+dis(v,y)$，其中 $dis(p,q)$ 表示从点 $p$ 到点 $q$ 的最短路。


------------

回到这题上来，我们可以把任意一条边的边权变为 $0$，那这个操作会对两点间的最短路产生什么影响呢？肯定是**对于所有经过这条边的路径的长度都有影响**。所以我们可以求出两点间经过这条边权变为 $0$ 的边的最短路的长度，然后与原来的最短路相比较，其中的最小值就是我们此次操作后两点间的最短路。

因此，我们只需要对每个顶点跑一遍 Dijkstra，然后枚举每一条边，求出将这一条边的边权变为 $0$ 之后题目所给点对之间的最短路，求和并更新答案，时间复杂度为 $O(n^2\log{n}+nm)$。注意，由于本题是无向图，因此还要考虑经过这条边的顶点的先后顺序，具体怎么做请看代码。



------------


代码如下（点个赞呗QAQ）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i) 
using namespace std;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

const int maxn=1005;
struct Edge{
	int to,next,val;
}e[maxn<<1];
int head[maxn],tot,n,m,k,dis[maxn][maxn],d[maxn],ti,a[maxn],b[maxn];

void connect(int x,int y,int V){
	e[++tot]=(Edge){y,head[x],V};
	head[x]=tot; 
}

struct Node{
	int num,dist;
	bool operator<(const Node &x)const{
		return dist>x.dist;
	}
};

priority_queue<Node> q;

void dij(int s){
	++ti;
	dis[s][s]=0;
	q.push((Node){s,0});
	fo(i,1,n){
		while(!q.empty()&&d[q.top().num]==ti) q.pop();
		if(q.empty()) break;
		int x=q.top().num;q.pop();d[x]=ti;
		for(int j=head[x];j;j=e[j].next){
			int p=e[j].to;
			if(d[p]==ti) continue;
			if(dis[s][p]>dis[s][x]+e[j].val){
				dis[s][p]=dis[s][x]+e[j].val;
				q.push((Node){p,dis[s][p]}); 
			}
		}
	}
	while(!q.empty()) q.pop();
}

int main(){
	memset(dis,0x3f,sizeof dis);
	n=read(),m=read(),k=read();
	fo(i,1,m){
		int x=read(),y=read(),v=read();
		connect(x,y,v);
		connect(y,x,v);
	}
	int ans=0;
	fo(i,1,n) dij(i);
	fo(i,1,k){
		a[i]=read();
		b[i]=read();
		ans+=dis[a[i]][b[i]];
	}
	fo(i,1,n){
		for(int j=head[i];j;j=e[j].next){
			int p=e[j].to;
			int sum=0;
			//yrztxdy!! 
			fo(w,1,k){
				//无向图与有向图的差别就在于可以先x->v,再v->u,u->y，处理一下就行 
				int yrztxdy=min(dis[a[w]][i]+dis[p][b[w]],dis[a[w]][p]+dis[i][b[w]]);
				if(yrztxdy<=dis[a[w]][b[w]]) sum+=yrztxdy;
				else sum+=dis[a[w]][b[w]];
			}
			ans=min(ans,sum);
		}
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：Base_ring_tree (赞：1)

# solution
## 大暴力
这个题，我们从最最暴力的思路开始想起。第一，我们可以用 $O(n)$ 枚举让哪一条边变为 $0$ 在分别做弗洛伊德。时间复杂度为 $O(n^4)$。
## 假做法
这种方法很明显会炸，怎么办呢？我这个蒟蒻又想到了一个假的不行的做法，那就是先做一遍迪杰斯特拉或弗洛伊德，再在我们选出的最短路中把每一条边的边权乘上他出现的次数，再把边权最大的那个变为 $0$。然后一眼找到了反例。

![](https://cdn.luogu.com.cn/upload/image_hosting/nurc33ds.png)

按照我的做法，就会把长度为 $2$ 的那条边变为 $0$，答案为 $2$。可是正确答案应该是 $0$，因为我们可以把长度为 $100$ 的边变为 $0$。
## 真做法
有了假做法的前车之鉴，我们不难发现**修改的边不一定是最短路上的**，那就好说了，直接 $O(n)$ 暴力修改。但我们真的要对每一次修改进行迪杰斯特拉吗？肯定不是因为我们可以发现，在跑了一遍迪杰斯特拉之后所有点到点的距离就都被记下来了。那就直接容斥不就行了吗，直接把他当作跳过了那条便就好了，也就是前半段加后半段的和。
# code
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=1005;
struct edge
{
	int to,nxt,v;
}edge[N*2];
int head[N],cnt;
void add(int u,int v,int w)
{
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
	edge[cnt].v=w;
}
int dis[N][N];
struct node
{
	int num,dis;
	node(int x,int y)
	{
	    num=x;
		dis=y;
	}
	bool  operator <(const node &p)
	const{
		return dis>p.dis;
	}
};
priority_queue<node> q;
void dijkstra(int s)
{
	memset(dis[s],0x3f,sizeof dis[s]);
	dis[s][s]=0;
	q.push(node(s,0));
	while(!q.empty())
	{
		int tmp=q.top().num;q.pop();
		for(int i=head[tmp];i;i=edge[i].nxt)
		{
			if(dis[s][edge[i].to]>dis[s][tmp]+edge[i].v)
			{
				dis[s][edge[i].to]=dis[s][tmp]+edge[i].v;
				q.push(node(edge[i].to,dis[s][edge[i].to]));
			}
		}
	 } 
}
int n,m,k;
int a[N],b[N];
int ans;
int main()
{
	cin>>n>>m>>k; 
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	
	for(int i=1;i<=n;i++)
	{
		dijkstra(i);
	}
	for(int i=1;i<=k;i++)
	{
		cin>>a[i];
		cin>>b[i];
		ans+=dis[a[i]][b[i]];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=edge[j].nxt)
		{
			int sum=0;
			for(int l=1;l<=k;l++)
			{
				sum+=min(dis[a[l]][b[l]],min(dis[a[l]][i]+dis[edge[j].to][b[l]],dis[a[l]][edge[j].to]+dis[i][b[l]]));
			}
			ans=min(ans,sum);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lndjy (赞：1)

大套路题。

首先看见 1000 的范围，可以考虑枚举边，再暴力枚举点对重新计算答案，这样是 $nk$ 的。

然而它不可能是一个纯暴力，我们需要 $O(1)$ 的方法求出边权为 0 后的新距离。

这部分是一个经典套路：

先用 $n^2logn$ 的时间对每一个点做一遍 dij，这样就知道了任意两点的最短路。

那么两点间的新最短距离可能经过变 0 的边，也可能不经过。

令 $dis_{x,y}$ 表示原图 $x$ 到 $y$ 的最短路，则这对点对的贡献为：

$$\min(dis_{x,y},\min(dis_{x,from}+dis_{to,y},dis_{x,to}+dis_{y,from})))$$

然后取加和的最小值即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
const int N=1005;
struct edge
{
	int to,nxt,v;
}e[N*2];
int head[N],cnt;
void add(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].v=w;
}
int dis[N][N];
struct node
{
	int num,dis;
	node(int x,int y){num=x,dis=y;}
	bool  operator <(const node &p)
	const{
		return dis>p.dis;
	}
};
priority_queue<node> q;
void dij(int st)
{
	memset(dis[st],0x3f,sizeof dis[st]);
	dis[st][st]=0;
	q.push(node(st,0));
	while(!q.empty())
	{
		int now=q.top().num;q.pop();
		for(int i=head[now];i;i=e[i].nxt)
		{
			if(dis[st][e[i].to]>dis[st][now]+e[i].v)
			{
				dis[st][e[i].to]=dis[st][now]+e[i].v;
				q.push(node(e[i].to,dis[st][e[i].to]));
			}
		}
	 } 
}
int n,m,k,ans=2e9;
int a[N],b[N];
int main()
{
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=k;i++)
	{
		a[i]=read();b[i]=read();
	}
	for(int i=1;i<=n;i++)
	dij(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=e[j].nxt)
		{
			int sum=0;
			for(int x=1;x<=k;x++)
			{
				sum+=min(dis[a[x]][b[x]],min(dis[a[x]][i]+dis[e[j].to][b[x]],dis[a[x]][e[j].to]+dis[i][b[x]]));
			}
			ans=min(ans,sum);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：KarmaticEnding (赞：0)

首先，让我们一起来想一个暴力做法。

暴力应该怎么做？肯定是对于图中的每一条边，枚举使它的边权变为 $0$ 之后每一组点对的最短路，最后取一个最小值就行了。时间复杂度是 $O(m\times k\times n\log n)$。这个时间复杂度肯定是过不了的。

学过图论的人都知道，对于一个出发点，Dijkstra 一般只跑一遍，哪有 Dijkstra 跑 $m$ 遍的？所以我们先对于每个出发点只跑一遍 Dijkstra，并记录下在没有任何边的边权被变为 $0$ 的时候两个点之间的最短路。那么现在我们已经有 $n^2\log n$ 的复杂度了。

我们想想，在有向图之中，“必须经过某条边”的最短路径是怎么算的？假设必须经过的边为 $u\rightarrow v$，起点为 $s$，终点为 $t$，那么结果就应该是 $dis(s,u)+w(u,v)+dis(v,t)$。其中 $dis(i,j)$ 表示 $i$ 和 $j$ 之间的最短路，$w(u,v)$ 表示 $u\rightarrow v$ 这条边的边权。

那么我们再想想，无向图中呢？也一样，只不过结果变成了 $\min(dis(s,u)+w(u,v)+dis(v,t),dis(s,v)+w(u,v)+dis(u,t))$。

现在回到这道题上面来。我们现在就可以枚举每一条边了，假设某一条边的边权变为 $0$，我们只需要比较每组点对 $s,t$ 的原最短路和必须经过经过这条边的最短路，取最小值，再把每一组点对的结果加起来，记为 $sum$，再取 $sum$ 中的最小值，记为 $ans$，然后输出 $ans$ 就可以了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int MAXN=1024;
int dis[MAXN][MAXN],a[MAXN],b[MAXN];
bool vis[MAXN];
vector<PII> g[MAXN];
int n,m,k,ans=0;
priority_queue<PII,vector<PII>,greater<PII> > q;
void Dijkstra(int s){
	for(int i=1;i<=n;++i){
		vis[i]=false;
	}
	dis[s][s]=0;
	q.push({0,s});
	while(q.size()){
		PII t=q.top();
		q.pop();
		int u=t.second;
		if(vis[u]){
			continue;
		}
		vis[u]=true;
		for(PII k:g[u]){
			int v=k.second,ds=k.first;
			if(dis[s][v]>dis[s][u]+ds){
				dis[s][v]=dis[s][u]+ds;
				q.push({dis[s][v],v});
			}
		}
	}
	while(!q.empty()){
		q.pop();
	}
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0,u,v,w;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		g[u].emplace_back(w,v);
		g[v].emplace_back(w,u);
	}
	for(int i=1;i<=n;++i){
		Dijkstra(i);
	}
	for(int i=1;i<=k;++i){
		scanf("%d%d",&a[i],&b[i]);
		ans+=dis[a[i]][b[i]];
	}
	for(int i=1;i<=n;++i){
		for(PII j:g[i]){
			int p=j.second;
			int sum=0;
			for(int h=1;h<=k;++h){
				int tmp=min(dis[a[h]][i]+dis[p][b[h]],dis[a[h]][p]+dis[i][b[h]]);//将边i->p变为0
				sum=sum+min(tmp,dis[a[h]][b[h]]);
			}
			ans=min(ans,sum);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：zztqwq (赞：0)

# Codeforces 1433G 题解

## Solution

一开始的想法是把所有最短路在途中标记出来，然后取一个 经过次数$\times$边权 最大的边边权置为 $0$，然后就成为了标准错解，WA ON TEST 2。这是因为删之前的最短路径和删之后的最短路径不一定重合，这点从样例二就可以看出来。

令 $\text{dis}(x,y)$ 表示 $x$ 到 $y$ 的最短距离，那么我们要考虑的就是将一条边 $(u,v)$ 边权置零后 $\text{dis}(a_i,b_i)$ 会如何变化。如果想要让 $\text{dis}(a_i,b_i)$ 变小，则最短路径一定会经过 $(u,v)$ 这条边。显然，此时 $\text{dis}(a_i,b_i)=\min\{\text{dis}(a_i,b_i),\text{dis}(a_i,u)+\text{dis}(b_i,v),\text{dis}(a_i,v)+\text{dis}(b_i,u)\}$。$\text{dis}$ 可以跑 $n$ 遍 Dijkstra 预处理，然后枚举哪条边被删掉即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
inline void read(int &x)
{
	x=0; int f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar(); 
	}
	x*=f;
}
const int N=1000,M=2000,INF=0x3f3f3f3f;
int head[N+10],ver[M+10],nxt[M+10],edge[M+10],tot=1;
void add(int x,int y,int z)
{
	ver[++tot]=y;
	edge[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
int dis[N+10][N+10];
bool vis[N+10];
int n,m,k;
void dij(int S)
{
	for(int i=1;i<=n;i++) dis[S][i]=INF;
	dis[S][S]=0;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<int,int> > que;
	que.push(make_pair(0,S));
	while(!que.empty())
	{
		int x=que.top().second; que.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i],z=edge[i];
			if(dis[S][x]+z<dis[S][y])
			{
				dis[S][y]=dis[S][x]+z;
				que.push(make_pair(-dis[S][y],y));
			}
		}
	}
}
struct node
{
	int a,b;
//	bool operator < (const node &x) const {return a==x.a?b<x.b:a<x.a;}
//	bool operator == (const node &x) const {return a==x.a && b==x.b;}
}s[N+10];
int U[N+10],V[N+10];
int main()
{
	read(n);read(m);read(k);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		read(u);read(v);read(w);
		U[i]=u;V[i]=v;
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=n;i++) dij(i);
	for(int i=1;i<=k;i++) 
	{
		read(s[i].a);
		read(s[i].b);
	}
//	sort(s+1,s+k+1);
//	k=unique(s+1,s+k+1)-s-1;
	int ans=INF;
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=1;j<=k;j++)
			sum+=min(dis[s[j].a][s[j].b],min(dis[s[j].a][U[i]]+dis[V[i]][s[j].b],dis[s[j].a][V[i]]+dis[U[i]][s[j].b]));
		ans=min(ans,sum);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

设变为 $0$ 的边是 $(x,y)$，那么对于一对点 $(X,Y)$，它们之间只有三种走法：$X\to Y,X\to x\to y\to Y,X\to y\to x\to Y$。以每一个点为源点跑一遍单源最短路即可。复杂度瓶颈在最短路上，时间复杂度 $O(n^2\log^2 m)$。

---

