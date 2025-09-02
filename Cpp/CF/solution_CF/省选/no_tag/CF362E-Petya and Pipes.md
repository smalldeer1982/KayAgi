# Petya and Pipes

## 题目描述

A little boy Petya dreams of growing up and becoming the Head Berland Plumber. He is thinking of the problems he will have to solve in the future. Unfortunately, Petya is too inexperienced, so you are about to solve one of such problems for Petya, the one he's the most interested in.

The Berland capital has $ n $ water tanks numbered from $ 1 $ to $ n $ . These tanks are connected by unidirectional pipes in some manner. Any pair of water tanks is connected by at most one pipe in each direction. Each pipe has a strictly positive integer width. Width determines the number of liters of water per a unit of time this pipe can transport. The water goes to the city from the main water tank (its number is $ 1 $ ). The water must go through some pipe path and get to the sewer tank with cleaning system (its number is $ n $ ).

Petya wants to increase the width of some subset of pipes by at most $ k $ units in total so that the width of each pipe remains integer. Help him determine the maximum amount of water that can be transmitted per a unit of time from the main tank to the sewer tank after such operation is completed.

## 说明/提示

In the first test Petya can increase width of the pipe that goes from the $ 1 $ st to the $ 2 $ nd water tank by $ 7 $ units.

In the second test Petya can increase width of the pipe that goes from the $ 1 $ st to the $ 2 $ nd water tank by $ 4 $ units, from the $ 2 $ nd to the $ 3 $ rd water tank by $ 3 $ units, from the $ 3 $ rd to the $ 4 $ th water tank by $ 2 $ units and from the $ 4 $ th to $ 5 $ th water tank by $ 1 $ unit.

## 样例 #1

### 输入

```
5 7
0 1 0 2 0
0 0 4 10 0
0 0 0 0 5
0 0 0 0 10
0 0 0 0 0
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 10
0 1 0 0 0
0 0 2 0 0
0 0 0 3 0
0 0 0 0 4
100 0 0 0 0
```

### 输出

```
5
```

# 题解

## 作者：LinkWish (赞：5)

首先把原图的最大流跑出来，然后考虑一下怎么处理这个残量网络。

在这个问题中，我们需要让所有边增加的流量之和不大于 $k$，这并乍一看不太好维护，但是我们注意到 $k\leq 1000$，于是考虑原图的边保留，再给原图每一条边额外建立一条流量为 $k$，费用为 $1$ 的边（原图边费用为 $0$）。这样一来，使用最短路径算法寻找最短增广路的过程就变成了寻找需要增加流量的边最少的增广路的过程。于是我们可以暴力地每次送一个单位流量去寻找增广路，这样就不会存在只用了 $1$ 的费用但是增加了更多流量的情况。

使用 EK 实现的 SSP 算法解决。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。

```cpp
const int N=55,M=10005;
int s,t;
struct edge{
	int to,w,c,nxt;
}e[M];
int h[N],cnt=1;
inline void ade(int x,int y,int w,int c){
	e[++cnt]={y,w,c,h[x]};
	h[x]=cnt;
}
inline void add(int x,int y,int w,int c){
	ade(x,y,w,c);
	ade(y,x,0,-c);
}
int dis[N],mxf[N],pre[N];
bool vis[N];
inline int spfa(ci flow){
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s),dis[s]=0,mxf[s]=flow,mxf[t]=0;
	int to,w,c,now;
	while(!q.empty()){
		now=q.front();
		q.pop();
		vis[now]=0;
		for(int i=h[now];i;i=e[i].nxt){
			to=e[i].to,w=e[i].w,c=e[i].c;
			if(!w||dis[to]<=dis[now]+c)continue;
			dis[to]=dis[now]+c;
			mxf[to]=min(mxf[now],w);
			pre[to]=i;
			if(!vis[to])q.push(to),vis[to]=1;
		}
	}
	return mxf[t];
}
int ans;
inline void update(){
	ans+=mxf[t];
	for(int now=t;now!=s;now=e[pre[now]^1].to)
		e[pre[now]].w-=mxf[t],e[pre[now]^1].w+=mxf[t];
}
int n,K;
int a[55][55];
inline bool _update(){
	if(K<dis[t])return 0;
	ans+=mxf[t],K-=dis[t];
	for(int now=t;now!=s;now=e[pre[now]^1].to)
		e[pre[now]].w-=mxf[t],e[pre[now]^1].w+=mxf[t];
	return 1;
}
signed main(){
	read(n),read(K);
	s=1,t=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			read(a[i][j]);
			if(a[i][j])add(i,j,a[i][j],0);
		}
	}
	while(spfa(iinf))update(); 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j])add(i,j,K,1);
	while(spfa(1))
		if(!_update())break;
	writeln(ans);
	return 0;
}
```


---

## 作者：yuzhechuan (赞：4)

如此熟悉的增流操作，让人一下就想到了ZJOI的[网络扩容](https://www.luogu.com.cn/problem/P2604)

没错，这两题可以近似地看做双倍经验

---

### 题解：

与网络扩容同样的做法：

先在原图上跑一边费用都为0的费用流，然后不断地对那些被使用的边（有流经过）的边增加容量并修改费用为1

修改完后再用费用流搞一遍扩流，累加费用和总流量就好啦

要注意的是退出扩流循环的条件的细节处理

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=55,M=2505;
int en=1,mc,mf,h[N],dis[N],n,k;
bool v[N];

struct edge{
	int n,v,f,w;
}e[M<<1];

struct fafafa{
	int fa,id;
}pre[N];

void add(int x,int y,int f,int w){
	e[++en]=(edge){h[x],y,f,w};
	h[x]=en;
}

bool spfa(int s,int t){
	memset(v,0,sizeof v);
	memset(pre,0,sizeof pre);
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	v[s]=1;
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(e[i].f&&dis[x]+e[i].w<dis[y]){
				dis[y]=dis[x]+e[i].w;
				pre[y]=(fafafa){x,i};
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
		v[x]=0;
	}
	return dis[t]^0x3f3f3f3f;
}

void mcmf(int s,int t){
	while(spfa(s,t)){
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		mf+=flow;
		mc+=flow*dis[t];
	}
}

void exadd(int x,int y,int f,int w){
	add(x,y,f,w);
	add(y,x,0,-w);
}
//上面是模板
signed main(){
	read(n);read(k);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=n;j++){
			read(x);
			if(x) exadd(i,j,x,0);
		}
	exadd(0,1,INT_MAX,0);
	exadd(n,n+1,INT_MAX,0); //两个超级点
	mcmf(0,n+1); //先跑一遍费用流
	while(mc<k){
		for(int i=2;i<=en;i+=2) if(!e[i].f){ //对被使用的边扩容
			e[i].f++;
			e[i].w=1;
		}
		int s,t;
		spfa(s=0,t=n+1); //跑费用流扩流
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		if(!flow) break; //没得增加了就退出
		if(mc+flow*dis[t]>k){ //超出了就特判，不能全用
			mf+=(k-mc)/dis[t];
			break;
		}
		mf+=flow; //否则就全用，并累加
		mc+=flow*dis[t];
	}
	write(mf);
}
```

---

## 作者：DiDi123 (赞：1)

看到这道题之后发现是很明显的网络流，但是难点在于可以用花费使得容量增加，而网络流的图中容量大小是不能变的，所以我们考虑先给这个图**定容**，也就是指定好最大流量。

所以我们考虑二分答案，二分到 $mid$ 的时候代表这个图的最大流量为 $mid$，然后我们从 $s$ 向 $1$ 连一条容量为 $mid$ 的边。我们对任意有边的两个点 $i,j$ 从 $i$ 向 $j$ 连一条容量为 $c[i][j]$，费用为 $0$ 的边，代表可以免费通过 $c[i][j]$ 的流量；再从 $i$ 向 $j$ 连一条容量为 $+\infty$，费用为 $1$ 的边，代表每扩容 $1$ 的容量，就需要付出 $1$ 的代价。然后再对整个图跑最小费用最大流，易知肯定跑满，所以符合设定。检查最小的费用是否小于等于 $k$，然后继续二分。

所以二分答案相当于就是把流量转化为了费用的判定。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 10010
#define INF 1e8
struct edge
{
	int to,nex,w,f;
}Edge[MAXN];
int head[MAXN],cnt;
void add_o(int u,int v,int c,int w)
{
	Edge[cnt].to=v;
	Edge[cnt].w=w;
	Edge[cnt].f=c;
	Edge[cnt].nex=head[u];
	head[u]=cnt++;
}
void add(int u,int v,int c,int w)
{
	add_o(u,v,c,w),add_o(v,u,0,-w);
}
int n,m,s,t,c[110][110];
void build(int x)
{
	memset(head,-1,sizeof(head));
	cnt=0;
	add(s,1,x,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(c[i][j]) add(i,j,c[i][j],0),add(i,j,INF,1);
}
int q[MAXN],incf[MAXN],d[MAXN],pre[MAXN],st[MAXN];
bool spfa()
{
	int hh=0,tt=1;
	memset(d,0x3f,sizeof(d));
	memset(incf,0,sizeof(incf));
	q[0]=s,d[s]=0,incf[s]=INF,st[s]=1;
	while(hh!=tt)
	{
		int x=q[hh++];
		if(hh==MAXN) hh=0;
		st[x]=0;
		for(int i=head[x];i!=-1;i=Edge[i].nex)
		{
			int y=Edge[i].to;
			if(Edge[i].f && d[x]+Edge[i].w<d[y])
			{
				d[y]=d[x]+Edge[i].w;
				pre[y]=i;
				incf[y]=min(incf[x],Edge[i].f);
				if(!st[y])
				{
					q[tt++]=y;
					if(tt==MAXN) tt=0;
					st[y]=1;
				}
			}
		}
	}
	return incf[t]>0;
}
int EK()
{
	int flow=0,cost=0;
	while(spfa())
	{
		int tp=incf[t];
		flow+=tp,cost+=tp*d[t];
		for(int i=t;i!=s;i=Edge[pre[i]^1].to)
			Edge[pre[i]].f-=tp,Edge[pre[i]^1].f+=tp;
	}
	if(!flow) return INF; //注意特判无法到达的情况
	return cost;
}
int main()
{
	cin>>n>>m;
	s=0,t=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>c[i][j];
	int l=0,r=INF,mid;
	while(l<=r)
	{
		if(l==r)
		{
			cout<<l;
			break;
		}
		mid=(l+r+1)>>1;
		build(mid);
		if(EK()<=m) l=mid;
		else r=mid-1;
	}
}
```


---

## 作者：xxseven (赞：0)

对于原图中的每条边 $(u,v,w)$，我们将其费用设为 $0$，同时加上一条边 $(u,v,\inf)$ 并将其费用设为 $1$。

那么问题转化为在这张图上求出费用 $\le k$ 的最大流量。

正常跑最小费用最大流，当费用即将超过 $k$ 时 `break` 即可。

正确性证明：假如每次强制只增加 $1$ 的流量，那么每个流量取到的费用都是可行的最小值，并且不会改变算法流程。因此正常增广时也成立。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9,N=55,M=5100;
int n,k,s,t;
struct edge{
	int to,next,val,cost;
}path[M<<1];
int head[N],cnt=1;
void add(int x,int y,int z,int c){
	path[++cnt].to=y;
	path[cnt].next=head[x];
	path[cnt].val=z;
	path[cnt].cost=c;
	head[x]=cnt;
}
void _add(int x,int y,int z,int c){
	add(x,y,z,c); add(y,x,0,-c);
}
int dis[N],inque[N];
struct Pre{
	int u,id;
}pre[N];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(inque,0,sizeof(inque));
	memset(pre,0,sizeof(pre));
	queue<int> q; q.push(s); dis[s]=0;
	while(!q.empty()){
		int u=q.front(); q.pop(); inque[u]=0;
		for(int v,i=head[u];i;i=path[i].next){
			v=path[i].to;
			if(!path[i].val) continue;
			if(dis[v]>dis[u]+path[i].cost) {
				dis[v]=dis[u]+path[i].cost;
				pre[v].id=i; pre[v].u=u;
				if(!inque[v]) q.push(v),inque[v]=1;
			}
		}
	}
	return dis[t]!=0x3f3f3f3f;
}
void EK(){
	int flow=0,cost=0;
	while(spfa()){
		int mn=inf;
		for(int i=t;i!=s;i=pre[i].u){
			mn=min(mn,path[pre[i].id].val);
		}
		for(int i=t;i!=s;i=pre[i].u){
			path[pre[i].id].val-=mn;
			path[pre[i].id^1].val+=mn;
		}
		if(cost+1ll*dis[t]*mn>k) {
			cout<<flow+(k-cost)/dis[t]; 
			return;
		}
		cost+=dis[t]*mn; flow+=mn;
	}
	cout<<flow;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>k; s=n+1,t=n+2;
	for(int x,i=1;i<=n;++i) {
		for(int j=1;j<=n;++j){
			cin>>x;
			if(i==j||!x) continue;
			_add(i,j,x,0);
			_add(i,j,inf,1);		
		}	
	}
	_add(s,1,inf,0); _add(n,t,inf,0);
	EK();
	return 0;
}


```

希望这篇题解能够帮到你！

---

