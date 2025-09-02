# [ABC375G] Road Blocked 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc375/tasks/abc375_g

AtCoder国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ M $ の番号がついた $ M $ 本の道路があります。  
 道路 $ i $ は都市 $ A_i $ と都市 $ B_i $ を双方向に結び長さは $ C_i $ です。

各 $ i=1,\ldots,M $ について、以下の $ 2 $ つの値が異なるかどうか判定してください。

- 全ての道路が通行可能なときの、都市 $ 1 $ から都市 $ N $ への最短距離
- 道路 $ i $ 以外の $ M-1 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ N $ への最短距離
 
ただし、一方では都市 $ 1 $ から都市 $ N $ に到達可能で、他方では到達不可能なとき、両者の値は異なるとみなします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ N $ へは到達可能
- 入力は全ては整数である
 
### Sample Explanation 1

全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ 3 $ への最短距離は $ 10 $ です。 - 道路 $ 1 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 10 $ です - 道路 $ 2 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 11 $ です - 道路 $ 3 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 10 $ です

### Sample Explanation 2

全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ 4 $ への最短距離は $ 1 $ です。 道路 $ 6 $ 以外の $ 5 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 4 $ への最短距離 は $ 2 $ です。

### Sample Explanation 3

道路 $ 1 $ 以外の $ 0 $ 本の道路が通行可能なとき、都市 $ 1 $ から都市 $ 2 $ へは到達できません。

## 样例 #1

### 输入

```
3 3
1 2 5
1 3 10
2 3 6```

### 输出

```
No
Yes
No```

## 样例 #2

### 输入

```
4 6
2 3 1
2 4 1
3 4 1
1 2 1
1 3 1
1 4 1```

### 输出

```
No
No
No
No
No
Yes```

## 样例 #3

### 输入

```
2 1
1 2 1```

### 输出

```
Yes```

# 题解

## 作者：I_will_AKIOI (赞：9)

第一次尝试赛时写 ABC 的 G 题，虽然没过，但是思路已经出来了，第二天给他调一下就过了，故写题解纪念。

这里设 $dis_{i,j}$ 表示在原图上 $i$ 到 $j$ 的最短路。首先如果删去一条边后，$dis_{1,n}$ 增大，则这条边一定是最短路上的必经边。因此可以求出 $1\sim n$ 每一条最短路上经过的边，给他建个图，如果一条边是这张图上的割边，那么最短路就会增大，反之不变。

因此问题就变成了怎么求出 $1\sim n$ 每一条最短路上经过的边，设 ，则如果从 $1,n$ 分别到这条边的两端点最短路之和，加上这条边的边权，等于 $dis_{1,n}$，那么一定有一条最短路是经过了这条边。所以对点 $1,n$ 分别跑一遍最短路，然后记录下 $1\sim n$ 每一条最短路上经过的边，跑一遍 tarjan 记录下割边就行。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
struct Data
{
  int to,val;
  bool operator<(const Data &w)const{return w.val<val;}
};
int n,m,cnt;
int x[N],y[N],z[N],d1[N],d2[N],dfn[N],low[N],cut[N];
bool vis[N];
vector<Data>v[N];
vector<pair<int,int> >G[N];
priority_queue<Data>q;
void dfs(int k,int fa)
{
	dfn[k]=low[k]=++cnt;
	for(auto now:G[k])
	{
		if(now.second==fa) continue;
		if(!dfn[now.first])
		{
			dfs(now.first,now.second);
			low[k]=min(low[k],low[now.first]);
			if(low[now.first]>dfn[k]) cut[now.second]=1;
		}
		else low[k]=min(low[k],low[now.first]);
	}
	return;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=m;i++)
  {
    cin>>x[i]>>y[i]>>z[i];
    v[x[i]].push_back(Data{y[i],z[i]});
    v[y[i]].push_back(Data{x[i],z[i]});
  }
  for(int i=1;i<=n;i++) d1[i]=1e18,vis[i]=0;
  d1[1]=0;
  q.push(Data{1,0});
  while(!q.empty())
  {
    int x=q.top().to;
    q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(auto now:v[x])
    {
      int y=now.to,z=now.val;
      if(d1[x]+z<d1[y])
			{
				d1[y]=d1[x]+z;
				q.push(Data{y,d1[y]});
			}
    }
  }
	for(int i=1;i<=n;i++) d2[i]=1e18,vis[i]=0;
  d2[n]=0;
  q.push(Data{n,0});
  while(!q.empty())
  {
    int x=q.top().to;
    q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(auto now:v[x])
    {
      int y=now.to,z=now.val;
      if(d2[x]+z<d2[y])
			{
				d2[y]=d2[x]+z;
				q.push(Data{y,d2[y]});
			}
    }
  }
  for(int i=1;i<=m;i++)
	{
		if(d1[x[i]]+z[i]+d2[y[i]]==d1[n]||d1[y[i]]+z[i]+d2[x[i]]==d1[n])
		{
			G[x[i]].push_back({y[i],i});
			G[y[i]].push_back({x[i],i});
		}
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,0);
	for(int i=1;i<=m;i++)
	{
		if(cut[i]) cout<<"Yes\n";
		else cout<<"No\n";
	}
  return 0;
}
```

---

## 作者：rainbow_cat (赞：8)

很好发现,去掉边 $i$ 最短路发生改变当且仅当边 $i$ 一定在每条最短路上。定义从点 $1$ 到 $i$ 的最短路距离为 $dis1_i$，从点 $n$ 到 $i$ 的最短路距离为 $dis2_i$，从点 $1$ 到 $i$ 的最短路方案数为 $posi1_i$，从点 $n$ 到 $i$ 的最短路方案数为 $posi2_i$。那么一条从 $u$ 到 $v$ 长度为 $z$ 边一定在最短路上当且仅当满足以下条件中的一个：    
- $dis1_u+dis2_v+z=dis1_n$ 且 $posi1_u \times posi2_v=posi1_n$
- $dis1_v+dis2_u+z=dis1_n$ 且 $posi1_v \times posi2_u=posi1_n$

上面这些信息很好处理，唯一需要注意的就是对于任意一点 $u$，方案数可能会溢出。只需要把它们对 $998244353$ 取模即可。
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int mod=998244353;
long long n,m,st,ed,idx,x,y,z;
int elast[200010];
int dis[200010],posi[200010],dis2[200010],posi2[200010];
struct edge{int x,y,z,pre;}a[400010];
void merge(int x,int y,int z)
{
	a[++idx]={x,y,z,elast[x]};
	elast[x]=idx;
}
struct node{int u,dis;};
bool operator < (node x,node y){return x.dis>y.dis;} 
priority_queue<node>q;
bool vis[200010];
void dijkstra()//从 1 开始跑最短路
{
	q.push({st,0});
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=elast[u];i;i=a[i].pre)
		{
			if(dis[a[i].y]>=dis[u]+a[i].z)
			{
				if(dis[a[i].y]==dis[u]+a[i].z)posi[a[i].y]=(posi[a[i].y]+posi[u])%mod;//距离相等则方案数累加
				else
				{
					posi[a[i].y]=posi[u];//距离更短则方案数为先前结点的方案数
					dis[a[i].y]=dis[u]+a[i].z;
					q.push({a[i].y,dis[a[i].y]});
				}
			}
			
		}
	}
}
void dijkstra2()//从 n 开始跑最短路，与前面大致相同
{
	q.push({ed,0});
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=elast[u];i;i=a[i].pre)
		{
			if(dis2[a[i].y]>=dis2[u]+a[i].z)
			{
				if(dis2[a[i].y]==dis2[u]+a[i].z)posi2[a[i].y]=(posi2[a[i].y]+posi2[u])%mod;
				else 
				{
					posi2[a[i].y]=posi2[u];
					dis2[a[i].y]=dis2[u]+a[i].z;
					q.push({a[i].y,dis2[a[i].y]});
				}
			}
			
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(dis,0x7f,sizeof dis);
	memset(dis2,0x7f,sizeof dis2);
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		merge(x,y,z),merge(y,x,z);
	}
	st=1,ed=n;
	dis[st]=0;
	posi[st]=1;
	dijkstra();
	memset(vis,0,sizeof vis);
	dis2[ed]=0;
	posi2[ed]=1;
	dijkstra2();
	for(int i=1;i<=idx;i+=2)
	{
		if(dis[a[i].x]+dis2[a[i].y]+a[i].z!=dis[ed]&&dis[a[i].y]+dis2[a[i].x]+a[i].z!=dis[ed])cout<<"No\n";//距离不相等
		else
		{
			if(((dis[a[i].x]+dis2[a[i].y]+a[i].z==dis[ed])&&(posi[a[i].x]*posi2[a[i].y]%mod==posi[ed]))||((dis[a[i].y]+dis2[a[i].x]+a[i].z==dis[ed])&&(posi[a[i].y]*posi2[a[i].x])%mod==posi[ed]))cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：yzljy (赞：3)

人生中第一次场切 G 题  
这次的 ABC 似乎有点太简单了？  
[题目传送门](https://atcoder.jp/contests/abc375/tasks/abc375_g)

## 题意简述

给定一张 $n$ 个点，$m$ 条边的有权无向图，对每条边进行询问，当前询问的是第 $i (1 \le i \le m)$ 条边，询问如下：  
 + 令 $dis$ 为从 $1$ 号点到 $n$ 号点的最短路长度，
 + 令 $dis'$ 为删掉第 $i$ 条边后的最短路长度，
 + 若 $dis \not ={dis'}$ 则输出 `Yes`，否则输出 `No`。

（若原本可以到达，现在不可以到达也输出 `Yes`。）  
每次询问独立。  

数据范围：  
 + $2 \le n \le 2 \times 10^{5}$
 + $1 \le m \le 2 \times 10^{5}$

## 思路

因为 $m$ 最大可以到 $2 \times 10^{5}$，假如每次都暴力做，每次去掉一条边，重新建图，跑一次最短路，再检查是否相等，视实现方法不同，时间复杂度会是 $O(mn^{2})$，$O(m^{2}\log{m})$ 以及其他复杂度，这显然是没法通过的，我们需要更优的方法。

我们来看这个样例：

```
4 6
2 3 1
2 4 1
3 4 1
1 2 1
1 3 1
1 4 2
```

建出图后长这样：（这里我用红色标注边权）  
![](https://cdn.luogu.com.cn/upload/image_hosting/5ifn7926.png)

很明显，从 $1$ 号点到 $n$ 号点的最短路为 $2$，而且不止有一条从 $1$ 到 $n$ 的路径的长度为 $2$。  
我们将所有从 $1$ 到 $n$ 的长度为 $2$ 的路径拿出来，是这样的：  
![](https://cdn.luogu.com.cn/upload/image_hosting/onbj2bcd.png)

我们可以从中发现，如果一条边不在**所有**最短路径上，那么将这条边删去后，最短路的值**不会**发生变化。  
那么如果在最短路上呢？

再来看一个样例：

```
5 5
1 2 1
1 3 1
2 4 1
3 4 1
4 5 1
```

很显然，连边后是这样的：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jdisofu0.png)  
也很显然的，从 $1$ 号点到 $n$ 号点的最短路为 $3$，将所有最短路径拿出来后的图也是长这样的。

发现将 $(1,2),(2,4),(1,3),(3,4)$ 这几条边删去后，并不会影响最短路的长度。  
而将 $(4,5)$ 这条边删去后，就直接变得不连通了。

而这样删去后，会对答案造成影响的，是什么样的边呢？  
其实就是所有最短路径都必须要经过的边，也就是所有最短路径构成的一张新图（这张图也叫做最短路图）中的**割边**。  
而更一般的，删去这些**割边**中的一条或者多条后，要么使得两点不连通，要么使新的最短路变大。

那现在思路就很明确了，先找到所有的最短路径，再找最短路图中的割边即可。  
如果一条边是割边，那么删去后最短路就会发生变化，也就该输出 `Yes`。否则的话，就不会发生变化，也就输出 `No`。

时间复杂度会在实现的部分分析。

## 实现

我们首先需要找出所有的最短路径，这是容易的。

我们首先求出 $1$ 号点到所有点的最短路，记为 $dis_{1,i}$。  
再求出从 $n$ 号点到所有点的最短路，记为 $dis_{n,i}$。  
这一部分可以使用任何优化（比如优先队列优化，堆优化）过的 Dijkstra 算法。（大概率是会卡 SPFA 的）  
这会是 $O(m \log m)$ 或是 $O(n \log n)$ 之类的。（根据具体的实现方法不同）下面就以我写的优先队列优化的为例。

接下来遍历所有的边，设当前遍历的边为第 $i$ 条边，这条边的两个端点分别是 $u$ 和 $v$，这条边的边权是 $w$。  
若 $dis_{1,u} + dis_{n,v} + w = dis_{1,n}$，第 $i$ 条边就是所有最短路径中的一条边。  
因为这里是无向边，所以当 $dis_{1,v} + dis_{n,u} + w = dis_{1,n}$ 时，第 $i$ 条边也是所有最短路径中的一条边。  
（若是有向边，就要注意一下方向的问题了）  
这一部分是 $O(m)$ 的。

我们建出这一个新图后，再找出图中的所有割边就行啦，这一部分可以使用 Tarjan 来实现，时间复杂度会是 $O(n+m)$ 的。  

总的时间复杂度是 $O(m \log m)$ 的，可以轻松通过。

## 代码

```cpp
// Problem: G - Road Blocked 2
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 375）
// URL: https://atcoder.jp/contests/abc375/tasks/abc375_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
const int mod1=1e9+7;
const int mod2=998244353;
const int inf_int=0x7f7f7f7f;
const long long inf_long=0x7f7f7f7f7f7f7f7f;
const double eps=1e-9;
char Buf[1<<23],*P1=Buf,*P2=Buf;
#define getchar() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<23,stdin),P1==P2)?EOF:*P1++)
template<typename type>
inline void read(type &x){
	x=0;
	bool f=false;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename type,typename... args>
inline void read(type &x,args&... y){
	read(x),read(y...);
}

int n,m,k,k2,head[MAXN],head2[MAXN],dis[2][MAXN],y[MAXN<<1];
int low[MAXN],dfn[MAXN],times;
bool vis[MAXN],cut_edge[MAXN<<1];
struct node{
	int to,next,val;
}edge[MAXN<<1],edge2[MAXN<<1];

struct node2{
	int to,val;
	friend bool operator < (node2 n1,node2 n2){
		return n1.val>n2.val;
	}
};

struct node3{
	int u,v,w;
}e[MAXN];

void build(int u,int v,int w){
	edge[++k].to=v;
	edge[k].next=head[u];
	edge[k].val=w;
	head[u]=k;
}

void build2(int u,int v,int w){
	edge2[++k2].to=v;
	edge2[k2].next=head2[u];
	edge2[k2].val=w;
	head2[u]=k2;
}

void dij(int s,bool type){
	for(int i=1;i<=n;i++) vis[i]=false;
	for(int i=1;i<=n;i++) dis[type][i]=1e18;
	priority_queue<node2> q;
	dis[type][s]=0;
	q.push((node2){s,0});
	while(!q.empty()){
		int u=q.top().to;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(vis[v]) continue;
			if(dis[type][v]>dis[type][u]+edge[i].val){
				dis[type][v]=min(dis[type][v],dis[type][u]+edge[i].val);
				q.push((node2){v,dis[type][v]});
			}
		}
	}
}

void tarjan(int u,int fa){
	dfn[u]=low[u]=++times;
	for(int i=head2[u];i;i=edge2[i].next){
        //在最短路图上找割边，而不是在原图上找
		int v=edge2[i].to;
		if(v==fa) continue;
		if(dfn[v]==0){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]){
				cut_edge[i]=true;
				cut_edge[i%2==0?i-1:i+1]=true;
                //反向边也要标记为割边
			}
		}
		else low[u]=min(low[u],low[v]);
	}
}

signed main(){
	read(n,m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		read(u,v,w);
		e[i].u=u;e[i].v=v;e[i].w=w;
		build(u,v,w);
		build(v,u,w);
	}
	dij(1,false);
	dij(n,true);
	for(int i=1;i<=m;i++){
		int val1=dis[0][e[i].u]+dis[1][e[i].v]+e[i].w;
		int val2=dis[0][e[i].v]+dis[1][e[i].u]+e[i].w;
		if(val1==dis[0][n]||val2==dis[0][n]){
			y[i]=k2+1;
			build2(e[i].u,e[i].v,e[i].w);
			build2(e[i].v,e[i].u,e[i].w);
		}
	}
	for(int i=1;i<=n;i++) vis[i]=false;
	for(int i=1;i<=n;i++) if(dfn[i]==0) tarjan(i,0);
	for(int i=1;i<=m;i++){
		if(cut_edge[y[i]]) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：hjyowl (赞：3)

### 题目大意

给定你一个图，让你求出 $1$ 到 $n$ 的最短路的必经过边，如果这条边是必经边，输出 ```Yes```，否则输出 ```No```。

### 前置知识

最短路，最短路计数。

### 思路

考虑从 $1$ 开始求出到其他店的最短路和最短路数量。

然后再从 $n$ 开始在求一个。

然后，对于每一条边 $i$，只要 $1$ 到 $u_i$ 的最短路加上 $v_i$ 到 $n$ 的最短路加上边权等于最短路并且 $1$ 到 $u_i$ 的最短路条数乘 $v_i$ 到 $n$ 的最短路条数（这里是乘法原理），那么就输出 ```Yes```，有一这里是双向边，所以说还需要反过来考虑（也就是先走到 $v_i$ 再到 $u_i$ 也可以）。

不过这道题还有一个坑人的地方，就是最短路数量求出来可能很多，可以考虑写高精度，但是这道题可以直接对于某个数去取模（很玄学），如果不放心那就搞个双哈希，作者是直接对 $10^{15}+7$ 取模的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const __int128 N = 4000010, M = 4000010;
__int128 h[N], ne[M], e[M], w[M], idx = 0;
typedef pair<__int128, __int128> PII;

void add(__int128 a, __int128 b, __int128 c) {
	w[idx] = c, e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
__int128 dist[M], cnt[M];
bool st[M];

void dijkstra(__int128 s) {
	for (int i = 0; i < M; i ++ ) {
		dist[i] = 1e18;
	}
	dist[s] = 0;
	cnt[s] = 1;
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	heap.push({0, s});
	while (heap.size()) {
		auto t = heap.top();
		heap.pop();
		__int128 v = t.second;
		if (st[v]) {
			continue;
		}
		st[v] = true;
		for (__int128 i = h[v]; ~i; i = ne[i]) {
			__int128 j = e[i];
			if (dist[j] > dist[v] + w[i]) {
				dist[j] = dist[v] + w[i];
				cnt[j] = cnt[v];
				heap.push({dist[j], j});
			} else if (dist[j] == dist[v] + w[i]) {
				cnt[j] = (cnt[j] + cnt[v]) % (__int128)(1e15 + 7);
			}
		}
	}
}
__int128 dist2[M], cnt2[M];
bool st2[M];

void dijkstra2(__int128 s) {
	for (int i = 0; i < M; i ++ ) {
		dist2[i] = 1e18;
	}
	dist2[s] = 0;
	cnt2[s] = 1;
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	heap.push({0, s});
	while (heap.size()) {
		auto t = heap.top();
		heap.pop();
		__int128 v = t.second;
		if (st2[v]) {
			continue;
		}
		st2[v] = true;
		for (__int128 i = h[v]; ~i; i = ne[i]) {
			__int128 j = e[i];
			if (dist2[j] > dist2[v] + w[i]) {
				dist2[j] = dist2[v] + w[i];
				cnt2[j] = cnt2[v];
				heap.push({dist2[j], j});
			} else if (dist2[j] == dist2[v] + w[i]) {
				cnt2[j] = (cnt2[j] + cnt2[v]) % (__int128)(1e15 + 7);
			}
		}
	}
}
long long u[M], v[M], d[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	memset(h, -1, sizeof h);
	int n, m;
	cin >> n >> m;
	for (__int128 i = 1; i <= m ; i ++ ) {
		int a, b, c;
		cin >> a >> b >> c;
		u[i] = a, v[i] = b, d[i] = c;
		add(a, b, c);
		add(b, a, c);
	}
	dijkstra(1);
	dijkstra2(n);
	for (__int128 i = 1; i <= m ; i ++ ) {
		if (dist[u[i]] + dist2[v[i]] + d[i] == dist[n] &&  (__int128)cnt[u[i]] * cnt2[v[i]] == cnt[n]) {
			cout << "Yes\n";
			continue;
		}
		if (dist[v[i]] + dist2[u[i]] + d[i] == dist[n] && (__int128)cnt[v[i]] * cnt2[u[i]] == cnt[n]) {
			cout << "Yes\n";
			continue;
		}
		cout << "No\n";
	}
	return 0;
}
```

---

## 作者：SwordDance (赞：2)

我们先搜出任意一条最短路(记作 $P$)，然后考虑删除一条边后的最短路会是什么样的。首先如果这条边不在 $P$ 中，那么必然没有影响，输出 $No$。如果它在 $P$ 中，新图的最短路之一（记作 $Q$）必然是先走一段 $P$，然后向外绕一段，再走回 $P$，如下图所示。

![1](https://cdn.luogu.com.cn/upload/image_hosting/idh0sfhu.png)

这个证明比较简单，大家可以自行理解一下。

显然，如果 $P$ 和 $Q$ 长度一致，那么这条边显然是不必要的。暴力删除每条边后判断肯定是不可行的，为此，我们需要找出所有与 $P$ 长度相等的 $Q$，那么 $P$、$Q$ 不重合的部分显然是不必要的，差分处理即可。

剩下的问题就是如何找出这样的 $Q$。记 $i$ 号点与 $1$ 号点的距离为 $d_i$，$i$ 与 $j$ 的距离为 $e(i,j)$，那么如果 $x\notin P$，$y\in P$，$d_x+e(x,y)=d_y$，那么就找到了一个合法的 $Q$。这是因为到达 $x$ 的**最短路之一**一定会在 $P$ 上走一段，而经过 $x->y$ 的路径后，必然会再在 $P$ 上走一段。记 $x$ 与 $P$ 分开的点为 $p_x$，那么 $p_x$ 在 $P$ 上到 $y$ 的路径就是不必要的边。

不过这里有个问题，上面加粗部分强调了，这是**最短路之一**，也就是说，可能出现长度一样，但是与 $P$ 分开更早的点，如下图所示。

其中，橙色为另一条到 $x$ 的最短路，但是与 $P$ 分开得更早。
![2](https://cdn.luogu.com.cn/upload/image_hosting/atxcr9vc.png)



这个问题很好处理，以 $d_i$ 为第一关键字，$p_i$ 为第二关键字，再跑一遍 $dijkstra$ 就行了。

不过实际上并不需要第二关键字，因为在 $i$ 号点去更新其他点之前，$i$ 号点的最优路径已经确定了。由于不存在边权为 $0$ 的路径，所以所有可能更新 $i$ 的点 $j$ 必然满足 $d_j<d_i$，而 $i$ 号点必然排在所有这些 $j$ 之后。

时间复杂度 $O(n\log n)$，读者可自行思考删去一条边后求新图的最短路长度该怎么做。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,int>PII;
const int N=2e5+3;
const LL INF=1e18;
int n,m,x,y,z,h[N],idx;
LL d[N];
int ans[N],fr[N],num[N],p[N],cnt[N],sum;
bool st[N],vis[N];
struct node{
	int u,v,w,ne;
}e[N<<1];
void add(int x,int y,int z){
	e[++idx]={x,y,z,h[x]};
	h[x]=idx;
}
void D()
{
	memset(d,0x3f,sizeof d);
	d[1]=0;
	priority_queue<PII,vector<PII>,greater<PII> >q;
	q.push({0,1});
    while(q.size()){
        int u=q.top().second;
		q.pop();
        if(st[u]) continue;
        st[u]=1;
    	for(int i=h[u];i;i=e[i].ne){
    		int j=e[i].v;
    	    if(d[j]>d[u]+e[i].w){
    	    	d[j]=d[u]+e[i].w;
    	    	fr[j]=i;
    	    	q.push({d[j],j});
    	    }
        }
    }
}
void D2()
{
	memset(d,0x3f,sizeof d);
	memset(st,0,sizeof st);
	d[1]=0;p[1]=1;
	priority_queue<pair<pair<LL,int>,int>,vector<pair<pair<LL,int>,int>>,greater<pair<pair<LL,int>,int>> >q;
	q.push({{0,1},1});
    while(q.size()){
        int u=q.top().second;
		q.pop();
        if(st[u]) continue;
        st[u]=1;
    	for(int i=h[u];i;i=e[i].ne){
    		int j=e[i].v;
    	    if(d[j]>d[u]+e[i].w||d[j]==d[u]+e[i].w&&num[p[u]]<num[p[j]]){
    	    	d[j]=d[u]+e[i].w;
    	    	p[j]=p[u];
    	    	if(vis[j]) p[j]=j;
				q.push({{d[j],p[j]},j});
    	    }
        }
    }
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	D();
	if(d[n]>INF){
		for(int i=1;i<=m;i++) puts("No");
		return 0;
	}
	int now=n,id=n;
	while(now>1) vis[now]=1,num[now]=id,id--,now=e[fr[now]].u;//num是P上点出现的顺序优先度 
	vis[1]=1,num[1]=id;
	memset(p,0x3f,sizeof p);
	D2();
	for(int u=1;u<=n;u++){
		if(!vis[u]) continue;
	    for(int i=h[u];i;i=e[i].ne){
	    	int v=e[i].v,w=e[i].w;
	    	if(vis[v]) continue;
	    	if(d[v]+w==d[u]) cnt[p[v]]--,cnt[u]++;//找出一条Q 
		}
	}
	now=n;
	while(now>1){//差分 
		sum+=cnt[now];
		if(sum==0) ans[(fr[now]+1)>>1]=1;
		now=e[fr[now]].u;
	}
	for(int i=1;i<=m;i++) puts(ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：shinzanmono (赞：2)

**English version is at the end of the text.**

先 Dijkstra 跑出 $1$ 到点 $i$ 的最短路 $dis_i$ 和 $n$ 到点 $i$ 的距离 $dis'_i$。

考虑一条边 $(u,v,w)$ 在 $1\rightarrow n$ 的最短路上当且仅当 $dis_u+dis'_v+w=dis_n$ 或 $dis_v+dis'_u+w=dis_n$。将满足条件的边加入新图。原题就是求每条边是否是新图上的割边，跑 Tarjan 即可。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using ll=long long;
using piit=std::pair<ll,int>;
const int sz=2e5+10;
const ll inf=0x3fffffffffffffff;
struct edge{
    int nxt,to;
    ll w;
}graph[sz<<1];
int head[sz],hpp;
void addEdge(int from,int to,int w){
    graph[++hpp]=edge{head[from],to,w};
    head[from]=hpp;
}
ll dis[2][sz],n,m;
int u[sz],v[sz],w[sz];
bool vis[sz];
std::priority_queue<piit,std::vector<piit>,std::greater<piit>>pq;
void dijkstra(int s,ll *dis){
    std::fill(dis+1,dis+n+1,inf);
    std::fill(vis+1,vis+n+1,0);
    dis[s]=0,pq.push(std::make_pair(dis[s],s));
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(int p=head[u];p;p=graph[p].nxt){
            int v=graph[p].to;
            if(dis[v]>dis[u]+graph[p].w){
                dis[v]=dis[u]+graph[p].w;
                pq.push(std::make_pair(dis[v],v));
            }
        }
    }
}
int dfn[sz],low[sz],dpp,id[sz];
bool bridge[sz<<1];
void tarjan(int u,int pid){
	dfn[u]=low[u]=++dpp;
	for(int p=head[u];p;p=graph[p].nxt){
		int v=graph[p].to;
		if(dfn[v]==0){
			tarjan(v,p),low[u]=std::min(low[u],low[v]);
			if(low[v]>dfn[u])bridge[p]=bridge[p^1]=true;
		}else if(p!=(pid^1))low[u]=std::min(low[u],dfn[v]);
	}
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n>>m;
    for(int i=1;i<=m;i++)
        std::cin>>u[i]>>v[i]>>w[i],addEdge(u[i],v[i],w[i]),addEdge(v[i],u[i],w[i]);
    dijkstra(1,dis[0]),dijkstra(n,dis[1]);
    std::fill(head+1,head+n+1,0),hpp=1;
    for(int i=1;i<=m;i++){
        if(dis[0][u[i]]+dis[1][v[i]]+w[i]!=dis[0][n]&&dis[0][v[i]]+dis[1][u[i]]+w[i]!=dis[0][n])continue;
        vis[i]=true,addEdge(u[i],v[i],w[i]),addEdge(v[i],u[i],w[i]),id[i]=hpp;
    }
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)dpp=0,tarjan(i,0);
    for(int i=1;i<=m;i++){
        if(id[i]==0)std::cout<<"No\n";
        else std::cout<<(bridge[id[i]]?"Yes\n":"No\n");
    }
    return 0;
}
```

First of all, we use Dijkstra algorithm to find the shortest path from vertex $1$ to vertex $i$, which is called $dis_i$, and the shortest path from vertex $n$ to vertex $i$, which is called $dis'_i$.

Consider if an edge $(u,v,w)$ is on the shortest path from $1$ to $n$, there must exist $dis_u+dis'_v+w=dis_n$ or $dis_v+dis'_u+w=dis_n$. We add all the edges satisfy this into a new graph. You need to find whether an edge is a bridge in the new graph. That will be easy by using Tarjan algorithm.

---

## 作者：mathcode (赞：0)

好久没遇到这么简单的 G 题了。

简述题意：给定一个无向图，对于每一条边独立的判断去掉该边前后从 $1$ 节点到 $n$ 节点的最短路是否相同。

思路：首先对于每一条边，判断其是否在一条可能的最短路上，如果不在，则去掉该边前后从 $1$ 节点到 $n$ 节点的最短路一定还是相同的。这是一个相当典的问题，只需要以 $1$ 作为源点还有以 $n$ 作为源点分别跑 Dijkstra ，然后对每一条边 $(u, v, w)$ 分别判断是否存在一点到 $1$ 的最短路长度与另一点 $n$ 的最短路长度与 $w$ 之和等于 $1$ 到 $n$ 最短路长度即可。

对于剩余在其中一条最短路上的边，不难想到抽出这些边重新建图，只要该边不是桥边，即说明删掉该边前后最短路不会受到影响。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 2147483647
#define pii pair<int, int>
const int N = 5e5 + 5;

int n, m, s;
int d1[N], d2[N], v[N];
priority_queue<pii, vector<pii>, greater<pii>> q; 
vector<pii> g[N];
void dijkstra(int d[])
{
    for (int i = 1; i <= n; i++) d[i] = 1e18;
    d[s] = 0;
    q.push({0, s}); 
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (auto [y, w]: g[x]) 
        {
            if (d[y] > d[x] + w)
            {
                d[y] = d[x] + w;
                q.push({d[y], y});
            } 
        }
    }
}
struct node
{
    int u, v, w, id;
} e[N];
int ans[N];

int tmp, dfn[N], low[N];
vector<pii> g2[N << 1];
map<pii, bool> mp;
void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++tmp;
    for (auto &i : g2[u])
    {
        int v = i.first;
        if (dfn[v] == 0)
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                mp[{u, v}] = 1, mp[{v, u}] = 1;
        }
        else if (v != fa)
            low[u] = min(low[u], dfn[v]);
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] =  {u, v, w, i};
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    s = 1;
    dijkstra(d1);
    int dis = d1[n];
    for (int i = 1; i <= n; i++) v[i] = 0;
    s = n;
    dijkstra(d2);

    vector<node> vn;
    for (int i = 1; i <= m; i++)
    {
        auto [u, v, w, id] = e[i];
        if (d1[u] + d2[v] + w == dis || d1[v] + d2[u] + w == dis) 
        {
            g2[u].push_back({v, i << 1}),
            g2[v].push_back({u, i << 1 | 1});
            vn.push_back(e[i]);
        }
        else ans[i] = 0;
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i, 0);

    for (auto [u, v, w, id]: vn)
    {
        if (mp[{u, v}]) ans[id] = 1;
        else ans[id] = 0;
    }
    for (int i = 1; i <= m; i++) cout << (ans[i] ? "Yes\n" : "No\n") ;
}   
```

---

## 作者：zrl123456 (赞：0)

[[ABC375G] Road Blocked 2](https://www.luogu.com.cn/problem/AT_abc375_g)  

题目考察：dijkstra，哈希。  
题目简述：
在一个图 $G$ 中，有 $n$ 个点，$m$ 条边（表示为 $u_i,v_i,w_i$），$m$ 个询问，第 $i$ 次询问去掉第 $i$ 条边后从 $1$ 到 $n$ 是否不连通或最短路的值改变（询问是独立的）。  
数据范围：  
- $2\le n\le 2\times 10^5$
- $1\le m\le 2\times 10^5$
- $1\le u_i<v_i\le n$
- $1\le w_i\le 10^9$
- $G$ 中无重边，点 $1$ 到点 $n$ 联通。
---
满足该条件，当且仅当所有的最短路都经过这条边，然后需要满足两个条件：
- 首先最短路要经过这条边。
- 然后经过这条边的最短路数等于总的最短路数。

那么我们继续思考（设 $dis_{u,v}$ 为 $u$ 到 $v$ 的最短路，$cnt_{u,v}$ 为从 $u$ 到 $v$ 的最短路数）：
- 最短路经过第 $i$ 边说明 $dis_{1,u_i}+w_i+dis_{v_i,n}=dis_{1,n}$。
- 经过这条边的最短路数等于总的最短路数说明 $cnt_{1,u_i}\times cnt_{v_i,n}=cnt_{1,n}$。

这两个值是可以分别从 $1$ 和 $n$ 分别跑 dijkstra 用 $\Theta((n+m)\log n)$ 求出来，但是 $cnt_{1,n}$ 的值非常大，所以我们要用哈希。  

时间复杂度为 $\Theta((n+m)\log n)$。  

[代码](https://atcoder.jp/contests/abc375/submissions/58733043})

---

## 作者：OIer_Tan (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc375_g) [AT 传送门](https://atcoder.jp/contests/abc375/tasks/abc375_g)

水 G，但是赛时调 F 去了所以成功场外。

## 题目翻译

在 AtCoder 国家中，有 $n$ 座城市，编号为 $1$ 至 $n$，以及 $m$ 条道路，编号为 $1$ 至 $m$。
道路 $i$ 双向连接城市 $A_i$ 和 $B_i$，长度为 $C_i$。

对于每个 $i = 1, \ldots, m$，判断下列两个值是否不同。

- 当所有道路都可以通行时，从城市 $1$ 到城市 $n$ 的最短距离；
- 当除道路 $i$ 之外的道路均可通行时，从城市 $1$ 到城市 $n$ 的最短距离。

如果从城市 $1$ 到城市 $n$ 的距离在其中一种情况下可以达到，而在另一种情况下不能达到，那么这两个值被认为是不同的。

## 做法

显然考虑先求点 $1$ 至点 $n$ 的最短路上的所有边，然后判断删掉之后这些边是否仍然可以相连。

前一步，可以通过先求点 $1$ 和点 $n$ 到所有点的最短路长度，这显然可以通过跑两遍 Dijkstra 来实现。然后可以枚举每条边，看是否点 $1$ 到 $A_i$ 的距离加上点 $B_i$ 到点 $n$ 再加上这条边的长度为点 $1$ 到点 $n$ 的最短路长度。

后一步，割边板子，做完了。

总时间复杂度 $O(m\log n+n)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

#define bool ll
#define int ll

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , m ;

vector <pair <ll,ll>> edge [N] ;

map <pair <ll,ll>,ll> edge_num ;

ll dis_1 [N] , dis_n [N] ;

bool vis [N] ;

vector <ll> edge_over [N] ;

bool is_bridge [N] ;

ll cnt_bridge = 0 , father [N] , low [N] , dfn [N] , dfs_clock , ans [N] ;

void tarjan ( ll now , ll fa )
{
//	cout << now << " " << fa << endl ;
	father [now] = fa ;
	low [now] = dfn [now] = ++ dfs_clock ;
	for ( ll i = 0 ; i < edge_over [now].size () ; i ++ )
	{
		ll nxt = edge_over [now] [i] ;
		if ( ! dfn [nxt] )
		{
//			cout << "CRT" << endl ;
			tarjan ( nxt , now ) ;
			low [now] = min ( low [now] , low [nxt] ) ;
			if ( low [nxt] > dfn [now] )
			{
				is_bridge [nxt] = 1  ;
				cnt_bridge ++ ;
			}
		}
		else if ( dfn [nxt] < dfn [now] && nxt != fa )
		{
//			cout << "CRCC" << endl ;
			low [now] = min ( low [now] , dfn [nxt] ) ;
		}
//		else
//		{
//			cout << "CR" << endl ;
//		}
		
	}
//	cout << now << " " << dfn [now] << " " << low [now] << endl ;
	return ;
}

signed main ()
{
#if not defined ( CRCC ) and not defined ( ONLINE_JUDGE ) 
	freopen ( ".in" , "r" , stdin ) ;
	freopen ( ".out" , "w" , stdout ) ;
#endif
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> m ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		dis_1 [i] = dis_n [i] = 1e18 ;
	}
	dis_1 [1] = dis_n [n] = 0 ;
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		ll u , v , w ;
		cin >> u >> v >> w ;
		edge [u].emplace_back ( make_pair ( v , w ) ) ;
		edge [v].emplace_back ( make_pair ( u , w ) ) ;
		edge_num [make_pair ( u , v )] = i ;
		edge_num [make_pair ( v , u )] = i ;
	}
	priority_queue <pair <ll,ll>,vector <pair <ll,ll>>,greater <pair<ll,ll>>> q ;
	q.push ( { 0ll , 1 } ) ;
	while ( ! q.empty () )
	{
		auto now = q.top ().second ;
		q.pop () ;
		if ( vis [now] )
		{
			continue ;
		}
		vis [now] = 1 ;
		for ( auto nxt : edge [now] )
		{
//			cout << dis [nxt.first] [s] << endl ;
			if ( dis_1 [nxt.first] > dis_1 [now] + nxt.second )
			{
				dis_1 [nxt.first] = dis_1 [now] + nxt.second ;
				q.push ( { dis_1 [nxt.first] , nxt.first } ) ;
			}
		}
	}
	while ( q.size () )
	{
		q.pop () ;
	}
	memset ( vis , 0 , sizeof vis ) ;
	q.push ( { 0ll , n } ) ;
	while ( ! q.empty () )
	{
		auto now = q.top ().second ;
		q.pop () ;
		if ( vis [now] )
		{
			continue ;
		}
		vis [now] = 1 ;
		for ( auto nxt : edge [now] )
		{
//			cout << dis [nxt.first] [s] << endl ;
			if ( dis_n [nxt.first] > dis_n [now] + nxt.second )
			{
				dis_n [nxt.first] = dis_n [now] + nxt.second ;
				q.push ( { dis_n [nxt.first] , nxt.first } ) ;
			}
		}
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		for ( auto x : edge [i] )
		{
			if ( dis_1 [i] + x.second + dis_n [x.first] == dis_1 [n] ||
				 dis_n [i] + x.second + dis_1 [x.first] == dis_n [1] )
			{
				edge_over [i].emplace_back ( x.first ) ;
//				edge_over [x.first].emplace_back ( i ) ;
			}
		}
	}
//	for ( ll i = 1 ; i <= n ; i ++ )
//	{
//		cout << i << ":" ;
//		for ( auto x : edge_over [i] )
//		{
//			cout << x << " " ;
//		}
//		cout << endl ;
//	}
	tarjan ( 1 , 1 ) ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		if ( is_bridge [i] )
		{
			ans [edge_num [make_pair ( i , father [i] )]] = 1 ;
		}
//		cout << i << " " << is_bridge [i] << endl ;
	}
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cout << ( ans [i] ? "Yes" : "No" ) << endl ;
	}
	return 0 ;
}
```

---

