# [POI 2003] Smugglers

## 题目描述

Byteotia 因为它丰富的金矿资源而闻名世界. 所以在和它的邻国 Bitland 的边界上每年都有大量的金矿交易。不幸的是由于税务的繁重，商人带着矿产穿过边境时都要交纳矿产价格的 $50\%$ 作为关税。但是幸运的是，有一些炼金术士已经发明了一些方法能把某一种矿产转化成另一种的矿物。于是这样在交易时就可以先把昂贵的矿产转化成便宜的，等到带过边境以后在转换回来。但是由于这项工作费时费力，炼金术士对于每种转换都要收取相应的费用。现在有个商人想将 $1$ kg 金子带过边境，他想知道最少的花费是多少。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 5000$，$0 \le p_k \le 10^9$，$0 \le m \le 100000$，$1 \le a,b \le n$，$0 \le c \leq 10000$。

## 样例 #1

### 输入

```
4
200
100
40
2
6
1 2 10
1 3 5
2 1 25
3 2 10
3 4 5
4 1 50```

### 输出

```
60```

# 题解

## 作者：Soul_Love (赞：6)

## 题目大意
我觉得这道题最大的难点就是题目的意思，在此我简单说明一下。一开始，商人就有 1kg 黄金（也就是说没有费用）。接着就是转化，这是在过边境前后都可以进行的。还有就是在过边境之后经过若干次转化后，商人手上拿着的必须是黄金。

~~是不是感觉换了道题？？？~~

## 思路
我用的是 Dijkstra，这很好想。为了解决过边境的问题，对于每种金属都建两个点，分别是过边境前的和过边境后的。对于转化，直接连两种所给的金属。对于交税，直接把两个同金属过边境前和过边境后的点连边，费用为该金属的单价的一半。最后套模板就可以了。

## 代码
```c
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
int n,m,s=1,h[500100],dis[500100],l,vis[500100],x,y,z,t;
struct node
{
	int dis,pos;
	bool operator <(const node &x)const
	{
		return x.dis<dis;
	}
};
inline int read()
{
	int k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
priority_queue<node> q;
struct edge
{
	int v,next,w;
}e[500100];
inline void add(int x,int y,int z)
{
	e[++l].v=y;
	e[l].w=z;
	e[l].next=h[x];
	h[x]=l;
}
inline void d()//模板 
{
	for(int i=1;i<=t;i++) dis[i]=inf;
	dis[s]=0;
	q.push((node){0,s});
	while(!q.empty())
	{
		node t=q.top();
		q.pop();
		int k=t.pos;
		if(vis[k]) continue;
		vis[k]=1;
		for(int i=h[k];i;i=e[i].next)
		{
			if(dis[e[i].v]>dis[k]+e[i].w)
			{
				dis[e[i].v]=dis[k]+e[i].w;
				if(!vis[e[i].v]) q.push((node){dis[e[i].v],e[i].v});
			}
		}
	}
}
int main()
{
	n=read();
	t=2*n;
	for(int i=1;i<=n;i++) add(i,i+n,read()*0.5);//依法纳税  
	m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		add(x,y,z);//过边境前的转化 
		add(x+n,y+n,z);//过边境后的转化 
	}
	d();
	printf("%d",dis[n+1]);
	return 0;
}
```


---

## 作者：run_away (赞：1)

## 题意

给定 $n$ 种金属的价格，带任意一种金属过境都要交其价格 $50\%$ 的税。

有 $m$ 种关系，每种可以把第 $a_i$ 种金属**单向**转换成第 $b_i$ 种金属，花费 $c_i$ 的代价。你可以在过境前后进行任意次转换。

最开始你有第 $1$ 种金属，并需要带第 $1$ 种金属过境，求最小代价。

## 分析

比较明显的最短路。

设 $i$ 为第 $i$ 种金属过境前的编号；$i+n$ 为第 $i$ 种金属过境后的编号。

把 $i$ 向 $i+n$ 连边，边权为金属价格的一半。

把 $a$ 向 $b$，$a+n$ 向 $b+n$ 连边，边权为 $c$。

从 1 跑最短路，答案为 $dis_{n+1}$。

用 Dijkstra，时间复杂度为 $O((n+m)\log (n+m))$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=5005;
ll n,m,head[maxn<<1],tot,dis[maxn<<1];
bool vis[maxn<<1];
struct edge{ll to,nxt,val;}e[300005];
struct node{
    ll dis,pos;
    inline bool operator<(const node& b)const{
        return b.dis<dis;
    }
};
inline void add(ll u,ll v,ll w){
    e[++tot]=(edge){v,head[u],w};
    head[u]=tot;
}
inline void dij(ll s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    priority_queue<node>q;
    q.push((node){0,s});
    while(!q.empty()){
        node u=q.top();q.pop();
        if(vis[u.pos])continue;
        vis[u.pos]=1;
        for(ll i=head[u.pos];i;i=e[i].nxt){
            ll v=e[i].to;
            if(dis[u.pos]+e[i].val<dis[v]){
                dis[v]=dis[u.pos]+e[i].val;
                if(!vis[v])q.push((node){dis[v],v});
            }
        }
    }
}
signed main(){
    n=read();
    for(ll i=1;i<=n;++i)add(i,i+n,read()/2);
    m=read();
    while(m--){
        ll u=read(),v=read(),w=read();
        add(u,v,w),add(u+n,v+n,w);
    }
    dij(1);
    printf("%lld",dis[n+1]);
    return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：1)

## Part 1 题意

某个商人要把黄金带过边境，有多种方法可以将黄金转化为其他金属，或将其他金属转化成黄金，有一定的代价。带金属过边境需要缴纳金属价格的百分之五十作为关税，求将黄金带过边境的最小花费价值是多少。

## Part 2 引入

一般而言，我们使用最短路算法都是在题目明确给出清晰的图和清晰的表达后才使用的，但本题依旧可以使用最短路算法。只需要对图与题目进行一个转化：

1. 金属 $\longmapsto$ 图的节点。

2. 金属间的转换方式 $\longmapsto$ 图的边。

3. 金属间转换的代价 $\longmapsto$ 图的边权。

4. 黄金 $\longmapsto$ 图的起点。

5. 带过边境的黄金 $\longmapsto$ 图的终点。

在此方法下，我们便可以对此题进行最短路计算。

## Part 3 思路

首先，按照上文中的方法将图储存下来。对于最短路算法，鉴于 $1 \leq n \leq 5000$ 和 $0 \leq m \leq 100000$，推荐使用 Dijkstra 算法的堆优化。

不过，本题的同一种金属也分为两种情况，即过边境了的和还未过边境的。如果对同一金属的两种形态进行分别判断相对麻烦。由于题目已经确定了有 $n$ 种金属，那我们就可以记录有 $2n$ 种金属，$1 \dots n$ 种金属为未过边境的金属，$n+1 \dots 2n$ 种金属为过边境了的金属。

已经确定了黄金为第 $1$ 种金属，那过边境了的黄金就是第 $n+1$ 种金属。故求的是节点 $1$ 到节点 $n+1$ 的最短路。

## Part 4 代码

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > que;
int n,m;
int to[maxn],las[maxn],nex[maxn],len[maxn],sum,dis[maxn];
bool vis[maxn];
inline int read()
{
	int x=0,y=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-') y=-1;ch=getchar();
	}
	while (ch>='0' && ch<='9')
	{
		x=x*10+int(ch-'0');ch=getchar();
	}
	return x*y;
}
inline void add(int x,int y,int z)
{
	sum++,to[sum]=y,len[sum]=z,nex[sum]=las[x],las[x]=sum;
	return ;
}
inline void dijkstra()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	que.push(make_pair(0,1));
	while (!que.empty())
	{
		int x=que.top().second;
		que.pop();
		if (vis[x]) continue;
		vis[x]=true;
		for (int i=las[x];i;i=nex[i])
		{
			int y=to[i],lon=len[i];
			if (dis[y]>dis[x]+lon)
			{
				dis[y]=dis[x]+lon;
				que.push(make_pair(dis[y],y));
			}
		}
	}
	return ;
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		int money=read();add(i,i+n,money/2);
	}
	m=read();
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z),add(x+n,y+n,z);
	}
	dijkstra();
	cout<<dis[n+1];
	return 0;
}
```

---

## 作者：Autream (赞：0)

### [[POI 2003] Smugglers](https://www.luogu.com.cn/problem/P8385) 解题记录
---
#### 题意简述
有 $n$ 种金属（金子编号为 $1$），每种金属有自己的单价，金属之间可以互相转换，编号为 $i$ 的金属转换为 $j$ 需要 $k$ 的代价。穿过边境花费 $50\%$ 当前的金属的单价。
问要把金子带过边境，需要的最少的代价。

---
#### 题目分析
对于题目中的“$i$ 到 $j$ 花费 $k$”，很容易就可以想到建图。考虑如何建图。
可以把图分为两部分：过边境前和过边境后。
那么我们就可以设 $1 \sim n$ 为过边境前的部分，$n+1 \sim 2n$ 为过边境后的部分。对于金属 $i$ 和金属 $j$，如果可以转换，那么就把 $i$ 和 $j$ 之间连一条**单向边**，同时在 $i+n$ 和 $j+n$ 之间也连一条**单向边**。
对于两个部分之间的连接，其实就是扣税的过程，直接将 $i$ 与 $i+n$ 连一条权值为金属 $i$ 单价的 $50\%$ 的边。
最后跑一遍最短路即可。

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=1e5+5;
struct edge {
    int to,nex,data;
}e[N<<2];//图要开4倍
int n,m,tot,head[N],dis[N];
void add(int x,int y,int z) {
    e[++tot].to=y;
    e[tot].data=z;
    e[tot].nex=head[x];
    head[x]=tot;
}
struct node {
    int to,data;
    bool operator<(const node& b)const {
        return data>b.data;
    }
};
std::priority_queue<node> q;
void dijkstra(int st) {
    mem(dis,0x3f);
    q.push(node{st,0});
    dis[st]=0;
    while(!q.empty()) {
        node u=q.top();
        q.pop();
        int x=u.to;
        if(dis[x]!=u.data) {
            continue;
        }
        erg(i,x) {
            int y=e[i].to,z=e[i].data;
            if(dis[y]>dis[x]+z) {
                dis[y]=dis[x]+z;
                q.push(node{y,dis[y]});
            }
        }
    }
}
signed main() {
    std::cin>>n;
    rep(i,1,n) {
        int x;
        std::cin>>x;
        add(i,n+i,x/2);//扣税
    }
    std::cin>>m;
    rep(i,1,m) {
        int x,y,z;
        std::cin>>x>>y>>z;
        add(x,y,z);//转换
        add(x+n,y+n,z);
    }
    dijkstra(1);
    std::cout<<dis[n+1];
    return 0;
}
```

---

## 作者：ty_xyz (赞：0)

分析题目，看到 “$n$ 种金属” “$m$ 种转换方式”就可以大致看出这是一道图论，再看就可以发现这其实就是一道分层图最短路。

于是考虑如何跑最短路。我们可以定义 $d_{1\sim n}$ 为第 $1\sim n$ 种金属在**过境前**的价格，$d_{n+1\sim n+n}$ 为第 $1\sim n$ 种金属在**过境后**的价格。根据题意连边，每组转换方式 $a_i,b_i,c_i$ 就是在 $a_i$，$b_i$ 与 $a_i+n$，$b_i+n$ 间连一条权为 $c_i$ 的**单向**边，并且对于第 $k$ 种金属，在 $k$ 与 $k+n$ 之间连一条权为 $\left\lfloor\dfrac{p_k}{2}\right\rfloor$ 的**单向**边。

于是跑一遍最短路即可，答案即为 $d_{n+1}$。

时间复杂度 $\mathcal{O}((n+m)\log n+m)$，可以通过本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct stu
{
	int id,d;
	bool operator<(stu a)const
	{
		return d>a.d;
	}
};
int n,m,d[10001];
vector<stu>g[10001];
bool vis[10001];
priority_queue<stu>q;
void dijsktra()
{
	memset(d,127,sizeof(d));
	d[1]=0;
	q.push((stu){1,d[1]});
	while(!q.empty())
	{
		int u=q.top().id;
		q.pop();
		vis[u]=1;
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i].id,w=g[u][i].d;
			if(!vis[v]&&d[u]+w<d[v])
			{
				d[v]=d[u]+w;
				q.push((stu){v,d[v]});
			}
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		g[i].push_back((stu){i+n,x/2});
	}
	cin>>m;
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		g[x].push_back((stu){y,z});
		g[x+n].push_back((stu){y+n,z});
	}
	dijsktra();
	cout<<d[n+1];
	return 0;
}
```

---

## 作者：Epoch_L (赞：0)

## Solution
很明显这种题就需要转化为图论问题，设过边境之前的点为 $1\sim n$，过边境之后的点为 $n+1\sim 2n$，则根据题意建边有 $i$ 连 $i+n$ 边权为 $0.5a_i$；若 $i$ 可转化为 $j$ 花费 $k$，则 $i$ 连 $j$ 边权为 $k$，$i+n$ 连 $j+n$ 边权为 $k$。最后以 $1$ 为源点跑最短路即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=5e5+7;
int n,m,tot,pre[N],now[N],son[N],dis[N],d[N];
priority_queue<pii>q;
bool bb[N];
void add(int x,int y,int z){
  pre[++tot]=now[x];
  son[tot]=y;
  dis[tot]=z;
  now[x]=tot;
}
void dij(int s){
  memset(d,63,sizeof d);d[s]=0;
  q.push(mkp(0,s));
  while(!q.empty()){
    int u=q.top().se;q.pop();
    if(bb[u])continue;
    bb[u]=1;
    for(int i=now[u];i;i=pre[i]){
      int v=son[i],w=dis[i];
      if(d[v]>d[u]+w)d[v]=d[u]+w,q.push(mkp(-d[v],v));
    }
  }
}
main(){
  read(n);
  for(int i=1,x;i<=n;i++)read(x),add(i,i+n,x/2);
  read(m);
  for(int i=1,x,y,z;i<=m;i++)
    read(x),read(y),read(z),add(x,y,z),add(x+n,y+n,z);
  dij(1);
  printf("%lld\n",d[1+n]);
  return 0;
}
```

---

