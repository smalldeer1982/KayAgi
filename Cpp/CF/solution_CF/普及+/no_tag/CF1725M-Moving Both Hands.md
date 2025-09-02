# Moving Both Hands

## 题目描述

Alice 在进行一个有向图上做游戏。有向图上共有 $n$ 个节点，$m$ 条有向边。Alice的手上有
一个红色球和一个蓝色球。
游戏开始时，Alice将红色球放在 $1$ 号节点上，将蓝色球放在 $i$ 号节点上。
长度为 $w$
的有向边表示可以通过一次操作将在 $v$ 的点转移
到 $u$ 
花费 $w$ 时间。
每局游戏中，Alice 要通过尽可能少的时间将两个球共同转移到任意同一个节点上。Alice 同一时间只能操作一个球。现在 Alice 想知道对于每个点 $2\le i \le n$
，每局游戏完成的最小时间是
多少。

## 样例 #1

### 输入

```
5 7
1 2 2
2 4 1
4 1 4
2 5 3
5 4 1
5 2 4
2 1 1```

### 输出

```
1 -1 3 4```

# 题解

## 作者：Hisaishi_Kanade (赞：5)

约定 $\text{dis}(x,y)$ 表示 $x\to y$ 的最短路长度。

思考一下这个询问的本质。对于一次询问 $(1,i)$，就是寻找一个 $j$ 使得 $\text{dis}(1,j)+\text{dis}(i,j)$ 最小。

对于 $\text{dis}(1,j)$ 在原图上做最短路就可以完成。

对于 $\text{dis}(i,j)$，我们转换为反图上的 $\text{dis}(j,i)$。

那么，原式变为正图上的 $\text{dis}(1,j)$ 加反图上的 $\text{dis}(j,i)$。

我们令 $1\sim n$ 表示的是正图中的点，$n+1\sim 2\times n$ 对应 $1\sim n$，是反图中的点。

再“连接”一下两个图，对于 $1\le i\le n$，$i\to i+n$ 连边，边权为 $0$。

这样，查询 $(1,i)$ 时，我们的最短路就会在某个点 $j$（这里的 $j$ 和上文的 $j$ 是一样的）从正图跳到反图上，然后在反图上跑到点 $i+n$。

显然有 $\text{dis}(1,j)+\text{dis}(j+n,i+n)=\text{dis}(1,j)+\text{dis}(i,j)$。那么这样做是正确的。

提醒一下，总边数是 $n+2\times m$ 的，最大是 $5\times 10^5$。

~~板子是很久之前写的，码风现在看起来挺诡异的。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int _x;char _c;
int read(){
	_x=0;_c=getchar();
	while(_c<'0'||_c>'9')_c=getchar();
	while(_c<='9'&&_c>='0'){
		_x=(_x<<1)+(_x<<3)+(_c^'0');
		_c=getchar();
	}
	return(_x);
}
int top;
int pre[400005];
long long dis[400005];
bool v[400005];
class point{
	public:
		int id;
		long long dis;
		const bool operator >(const point& other)const{
			return(dis>other.dis);
		}
}now;
class node{
	public:
		int l,r,s;
}edge[500005];
inline void work(int l,int r,int s){
	++top;
	edge[top].l=pre[l];
	edge[top].r=r;
	edge[top].s=s;
	pre[l]=top;
}
long long inf=1ll<<55;
priority_queue< point,vector<point>,greater<point> >q;
int n,m,s,l,r,k;
signed main(){
	n=read();
	m=read();s=1;
	for(int i=2;i<=2*n;i++)dis[i]=inf;
	pre[s]=dis[s]=0;
	for(int i=1;i<=n;++i)
	{
		work(i,i+n,0);
	}
	for(int i=1;i<=m;i++){
		l=read();
		r=read();
		k=read();
		work(l,r,k);
		work(r+n,l+n,k);
	}
	q.push((point){1,0});
	while(!q.empty()){
		now=q.top();
		q.pop();
		if(!v[now.id]){
			v[now.id]=true;
			for(int i=pre[now.id];i>0;i=edge[i].l){
				if(dis[edge[i].r]>dis[now.id]+edge[i].s){
					dis[edge[i].r]=dis[now.id]+edge[i].s;
					if(!v[edge[i].r])q.push((point){edge[i].r,dis[edge[i].r]});
				}
			}
		}
	}
	for(int i=n+2;i<=2*n;i++)printf("%lld ",dis[i]==inf?-1:dis[i]);
	return(0);
}
```

---

## 作者：panyanppyy (赞：5)

分层图好题，可是这个人赛时降智了没有过。

## Problem
有一个有向图，图上有两只手，一只在点 $1$，一只在点 $i$，可以每次移动一只手，求两手相遇的最短路径。
## Solution

可以发现一只手在正图上走，还有一只在反图上走，然后就有一个简单的方法：

- 先在正图上 $1$ 跑一遍最短路，然后将跑出来的值在返图上和一个源点建边，然后再按那个源点跑最短路就行了。

**注意**：这样的话边权要开 `long long`。
## Code 1
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.emplace_back(y);}
const int N=1e5+7;
const ll inf=0x3f3f3f3f3f3f3f3fll;
int n,m;
ll g[N];
bool vis[N];
inline void dj(int u,vector<pair<int,ll>>(&e)[N]){
	memset(g,0x3f,sizeof(g)),g[u]=0;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>q;
	q.emplace(0,u);
	while(!q.empty()){
		u=q.top().se,q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto[v,w]:e[u])
			if(g[v]>g[u]+w){
				g[v]=g[u]+w;
				if(!vis[v])q.emplace(g[v],v);
			}
	}
}
vector<pair<int,ll>>e[N],E[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y,z;i<=m;i++)
		cin>>x>>y>>z,e[x]+={y,z},E[y]+={x,z};
	dj(1,e);
	for(int i=1;i<=n;i++)E[0]+={i,g[i]};
	dj(0,E);
	for(int i=2;i<=n;i++)
		if(g[i]==inf)cout<<"-1 ";
		else cout<<g[i]<<' ';
	cout<<'\n';
	return 0;
}
```
这种做法并不是我想说的，接下来介绍一个做法：**分层图最短路**。

大概就是将图分成两层，在第 $1$ 层跑的**方式**和第 $2$ 层或更多不同或者[**状态**](https://www.luogu.com.cn/problem/AT4733)不同，具体实现可以向编号 $+n$ 的点连边来模仿进入下一层，这题就是典型的方式不同。

- 这里分成两层，第 $1$ 层是正图，也就是第一只手的方向，第 $2$ 层则是返图，是另一只手的方向，所以只要每个点向 $+n$ 的点连一条边，$1\sim n$ 的点建正图，$1+n\sim2n$ 的点建反图，然后从 $1$ 开始跑最短路，最后 $g_{i+n}$ 就是答案了。

## Code 2
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
const int N=1e5+7;
const ll inf=0x3f3f3f3f3f3f3f3fll;
int n,m;
ll g[N*2];
bool vis[N*2];
vector<pair<int,int>>e[N*2];
inline void dj(int u){
	memset(g,0x3f,sizeof(g)),g[u]=0;
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>q;
	q.emplace(0,u);
	while(!q.empty()){
		u=q.top().se,q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto[v,w]:e[u])
			if(g[v]>g[u]+w){
				g[v]=g[u]+w;
				if(!vis[v])q.emplace(g[v],v);
			}
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)e[i].emplace_back(i+n,0);
	for(int i=1,x,y,z;i<=m;i++){
		cin>>x>>y>>z;
		e[x].emplace_back(y,z),e[y+n].emplace_back(x+n,z);
	}
	dj(1);
	for(int i=2;i<=n;i++)
		if(g[i+n]==inf)cout<<"-1 ";
		else cout<<g[i+n]<<' ';
	cout<<'\n';
	return 0;
}
```
两篇代码之间时间间隔有点长，可能有些地方码风并不雷同。

不错的典题，建议反复观看。

---

## 作者：Mariposa (赞：3)

题意：

给定一张带权有向图，对于每个点 $p$，你需要求出若 $A$ 在 $1$，$B$ 在 $p$ 在某点汇合的最小路程和，或报告无解。

题解：

显然就是从 $1$ 点走一段正图，再走一段反图到 $p$ 的最短路。

可以建分层图：

- $(i,i+n,0)$，从一层走到二层，表示从此开始走反图，不花费时间；

- $(u_i,v_i,w_i)$，一层建正图；

- $(v_i+n,u_i+n,w_i)$，二层建反图；

不难发现这样跑出来是符合题意的。注意要开 long long。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e18
const int maxn=2e6+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,beg[maxn],nex[maxn],to[maxn],w[maxn],e;
inline void add(int x,int y,int z){
	++e;nex[e]=beg[x];beg[x]=e;to[e]=y;w[e]=z;
}
ll dis[maxn];int vis[maxn];
priority_queue<pair<ll,int> >Q;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)add(i,i+n,0);
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v+n,u+n,w);
	}Q.push(make_pair(0,1));
	for(int i=2;i<=n+n;i++)dis[i]=INF;
	while(!Q.empty()){
		int x=Q.top().second;Q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=beg[x];i;i=nex[i]){
			int t=to[i];
			if(dis[t]>dis[x]+w[i]){
				dis[t]=dis[x]+w[i];
				Q.push(make_pair(-dis[t],t));
			}
		}
	}
	for(int i=n+2;i<=n+n;i++)
		printf("%lld ",dis[i]==INF?-1:dis[i]);
	return 0;
}
```

---

## 作者：M_CI (赞：1)

### Part0：前言

奆佬们怎么都说这题是两只手，我英文还是太菜了，就按红蓝两球来讲吧。

---

### Part1：思路

显然，对于每局游戏，可将蓝球移动化为红球在反图上移动，需经过的边不变。于是我们就可以自然地想到使用分层图。

不同边的含义如下：

- 对于边 $(u,v,w)$，表示正图的边。

- 对于边 $(v+n,u+n,w)$，表示反图的边。

- 对于边 $(i,i+n,0)$，表示从 $i$ 开始走反图。

最终的输出即为 $1 \to i+n$ 的最短路程。

---

### Part2：代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m,k,tot,hd[2000010],nx[2000010],to[2000010],vl[2000010],dis[2000010];
bool vis[2000010];

void add (int u,int v,int w) {
	nx[++tot]=hd[u];
	to[tot]=v;
	vl[tot]=w;
	hd[u]=tot;
}

signed main () {
	cin>> n>> m;
	for (int i=1,u,v,w;i<=m;i++) {
		cin>> u>> v>> w;
		add (u,v,w);
		add (v+n,u+n,w);
	}
	for (int i=1;i<=n;i++)
		add (i,i+n,0); 
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > heap;
	memset (dis,0x3f,sizeof dis);
	heap.push ({0,1});
	dis[1]=0;
	while (heap.size ()) {
		int u=heap.top ().second;
		heap.pop ();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=hd[u];i;i=nx[i]) {
			int v=to[i],w=vl[i];
			if (dis[v]>dis[u]+w) {
				dis[v]=dis[u]+w;
				heap.push ({dis[v],v});
			}
		}
	}
	for (int i=n+2;i<=n*2;i++)
		cout<< (dis[i]==0x3f3f3f3f3f3f3f3f? -1: dis[i])<< " ";
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m,k,tot,hd[2000010],nx[2000010],to[2000010],vl[2000010],dis[2000010];
bool vis[2000010];

void add (int u,int v,int w) {
	nx[++tot]=hd[u];
	to[tot]=v;
	vl[tot]=w;
	hd[u]=tot;
}

signed main () {
	cin>> n>> m;
	for (int i=1,u,v,w;i<=m;i++) {
		cin>> u>> v>> w;
		add (u,v,w);
		add (v+n,u+n,w);
	}
	for (int i=1;i<=n;i++)
		add (i,i+n,0); 
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > heap;
	memset (dis,0x3f,sizeof dis);
	heap.push ({0,1});
	dis[1]=0;
	while (heap.size ()) {
		int u=heap.top ().second;
		heap.pop ();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=hd[u];i;i=nx[i]) {
			int v=to[i],w=vl[i];
			if (dis[v]>dis[u]+w) {
				dis[v]=dis[u]+w;
				heap.push ({dis[v],v});
			}
		}
	}
	for (int i=n+2;i<=n*2;i++)
		cout<< (dis[i]==0x3f3f3f3f3f3f3f3f? -1: dis[i])<< " ";
	return 0;
}
```

---

### Part3：后记

分层图板题，如果想要练手的话，还可以做一做 [P4568](https://www.luogu.com.cn/problem/P4568)、[P4822](https://www.luogu.com.cn/problem/P4822) 等题。

---

## 作者：jiangzenyu (赞：1)

### CF1725M Moving Both Hands

题面：[快速跳转](https://www.luogu.com.cn/problem/CF1725M)

一个 $K$ 层图的练习题。

#### 简述题面
你可以从第一个点的路线方式走到交点，同时可以通过其他点的方式走到交点。

#### 做题方法

根据数据范围 $1 \times 10 ^ 5$ 可以简单想到直接通过用 点 $1$ 来经过**某条反边**来求达到某个点的最小代价。

我们用一个简单图来理解这句话。

![](https://cdn.luogu.com.cn/upload/image_hosting/w66siavd.png)
这个图我们可以发现从 $1$ 到 $3$ 的最短路显然长度是 $2$，那么我们就很容易想到建一个反图来使点 $1$ 可以直接到达点 $3$。

其他照常跑最短路。

代码如下：
```c++
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int maxn = 200020;
const int mod = 1000000007;
const int inf = 4611686018427387904;
int d[maxn],vis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > q;
vector<pii> g[maxn];
int n,m;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i = 1;i<=m;i++)
	{
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		g[u].push_back(make_pair(v,w));
		g[v+n].push_back(make_pair(u+n,w));
	}
	for(int i = 1;i<=n;i++)
	{
		g[i].push_back(make_pair(i+n,0));
	}
	for(int i = 1;i<=2*n;i++) d[i] = inf;
	q.push(make_pair(0,1));
	d[1] = 0;
	while(!q.empty()){
		int u = q.top().second;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i = 0;i<g[u].size();i++)
		{
			int v = g[u][i].first,w = g[u][i].second;
			if(d[v]>d[u]+w)
			{
				d[v] = d[u]+w;
				q.push(make_pair(d[v],v));
			}
		}
	}
	for(int i=n+2;i<=2*n;i++) {
		if(d[i]==inf) cout<<-1<<" ";
		else cout<<d[i]<<" ";
	}
	return 0;
}
```

---

## 作者：fantastic_dream (赞：1)

#### 解答
转化下题意：从 $1$ 号节点出发，每次用 $w$ 的代价从 $u$ 到 $v$，你有一次机会，使此后只能走反边，即从 $v$ 到 $u$，问到各点的最短路。

注意到只有一次机会，于是建分层图，第一层原图，第二层建反图，再把第一层的点与第二层对应的点用边权为 $0$ 的边相连，跑最短路即可。
#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int ma=4e5+5;
int n,m,tot,head[ma],dis[ma];
bool vi[ma];
struct ed{
	int v,ne,w;
}p[ma<<1];
struct poi{
	int pos,dis;
	bool operator <(const poi &x)const{
		return x.dis<dis;
	}
};
priority_queue<poi> q;
void add(int u,int v,int w){
	p[++tot]={v,head[u],w};
	head[u]=tot;
}
void dij(){
	for(int i=1;i<=(n<<1);i++)	dis[i]=1e17;
	dis[1]=0,q.push({1,0});
	while(!q.empty()){
		poi t=q.top();
		q.pop();
		int pos=t.pos;
		if(vi[pos])	continue;
		vi[pos]=1;
		for(int i=head[pos];i;i=p[i].ne){
			int v=p[i].v,val=p[i].w;
			if(dis[v]>dis[pos]+val){
				dis[v]=dis[pos]+val;
				if(!vi[v])	q.push({v,dis[v]});
			}
		}
	}
}
main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v+n,u+n,w);
	}
	for(int i=1;i<=n;i++)	add(i,i+n,0);
	dij();
	for(int i=2;i<=n;i++){
		int re=min(dis[i],dis[i+n]);
		if(re==1e17)	cout<<-1<<' ';
		else	cout<<re<<' ';
	}
	return 0;
} 
```


---

## 作者：Xiphi (赞：1)

分层图好题。把题意简化为，在走一段从 $1$ 开始的正图，再走一段到 $i$ 的反图。接着就可以分层图了，第一层是正图，第二层是反图。中间连起来的是每一个原编号相同的点，连接的边权为 $0$ 的边。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int v,w,next;
}e[1000005];
struct Node{
    int d,h;
    bool operator<(const Node &x)const{
        return x.d<d;
    }
};
int n,m,s,head[1000005],cur,dp[200005];
void add(int u,int v,int w){
    e[++cur].v=v;
    e[cur].w=w;
    e[cur].next=head[u];
    head[u]=cur;
}
int vis[200005];
void dij(int s){
    priority_queue<Node> q;
    q.push({0,s});
    dp[s]=0;
    while(!q.empty()){
        int top=q.top().h;
        q.pop();
        if(vis[top]==0)
        for(int i=head[top];i;i=e[i].next){
            int v=e[i].v;
            if(dp[v]>dp[top]+e[i].w&&!vis[v]){
                dp[v]=dp[top]+e[i].w;
                q.push({dp[v],v});
            }
        }
        vis[top]=1;
    }
}
signed main(){
    cin>>n>>m;
    s=1;
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        add(u,v,w);
        add(v+n,u+n,w);
    }
    for(int i=1;i<=n;++i){
        add(i,i+n,0);
    }
    memset(dp,0x3f,sizeof dp);
    dij(s);
    for(int i=n+2;i<=n+n;++i){
        if(dp[i]==0x3f3f3f3f3f3f3f3f&&dp[i-n]==0x3f3f3f3f3f3f3f3f) cout<<-1<<' ';
        else cout<<min(dp[i],dp[i-n])<<' ';
    }
    return 0;
}

```

---

## 作者：zhouzihang1 (赞：0)

# CF1725M Moving Both Hands 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF1725M)

[CF 传送门](https://codeforces.com/problemset/problem/1725/M)

[文章区链接](https://www.luogu.com.cn/article/abjio57g)

## 题意

给出 $n$ 个点，$m$ 条边的有向图，在 $1$ 到每个点之间找一个中间点使这两个点到这个中间点的最短距离最短。

## 思路

$2 \le n \le 10^5$

$1 \le m \le 2 \times 10^5$

发现暴力不行。

遇到这种没有思路的图论题我们可以想一想能不能建**分层图**来解决。

分层图就是再建一个图然后让原图和这个图连边。

~~因为 CS Academy 有点 bug，就不画图了。~~

我们在第二层建反图可以找出所有点到 $1$ 号节点的最短距离，然后分别让正图中的每一个点向他们在反图中对应的点建边，边权为 $0$。

可以画图想一下，这样子我们就可以求出题目所求的最短距离了。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define PII pair<int,int>
#define PLI pair<ll,int>
using namespace std;
const int N=1e5+10,M=2e5+10;
int n,m;
ll dis[N<<1];
vector<PII > vc[N<<1];
bool vis[N<<1];
priority_queue<PLI,vector<PLI >,greater<PLI > > q;
void Dijkstra()//标准的 Dijkstra
{
	q.push({0ll,1});
	dis[1]=0;
	while(q.size())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto vx:vc[u])
		{
			int v=vx.first,w=vx.second;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
}
int main()
{
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		vc[u].push_back({v,w});
		vc[v+n].push_back({u+n,w});//建反图
	}
	for(int i=1;i<=n;i++) vc[i].push_back({i+n,0});//正图向反图连边
	Dijkstra();
	for(int i=2;i<=n;i++)
		printf("%lld ",dis[i+n]>=0x3f3f3f3f3f3f3f3f?-1:dis[i+n]);
  //三目运算符好！
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

转化题意，对于每一个 $i$，求 $\min_{j=1}^n \{dis(1,j)+dis(i,j)\}$

直接枚举 $j$ 显然是没有前途的，考虑如何使这两段距离出现在一个图上，于是想到了建分层图。

具体的，我们在原来连边的基础上再建 $n$ 个点，并从第 $i(1 \le i \le n)$ 个点向第 $i+n$ 个点连边。再从第 $v_i+n$ 个点向第 $u_i+n$ 个点连边，这样，原图的 $dis(1,j)$ 就相当于新图的 $dis(1,j)$,原图的 $dis(i,j)$ 就相当于新图的 $dis(j+n,i)$，两条路径用一条长度为 $0$ 的边连接。这样只需要跑一遍以 $1$ 为起点的最短路，第 $i$ 个答案就是 $dis(1,i+n)$。

时间复杂度与跑最短路的复杂度相同。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,m;
int h[200005];
struct edge{
	int nxt;
	int to;
	int val;
};
edge e[1000005];
int cnt;
void add(int x,int y,int z){
	cnt++;
	e[cnt].to=y;
	e[cnt].nxt=h[x];
	h[x]=cnt;
	e[cnt].val=z;
	return;
}
bool vis[200005];
long long dis[200005];
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > q;
void dij(){
	for(int i=2;i<=n*2;i++)
		dis[i]=1e18;
	q.push(make_pair(0,1));
	while(!q.empty()){
		pair<int,int> x=q.top();
		q.pop();
		int s=x.second;
		if(vis[s]) continue;
		vis[s]=1;
		for(int i=h[s];i;i=e[i].nxt)
			if(!vis[e[i].to]&&dis[e[i].to]>dis[s]+e[i].val){
				dis[e[i].to]=dis[s]+e[i].val;
				q.push(make_pair(dis[e[i].to],e[i].to));
			}
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		add(i,i+n,0);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v+n,u+n,w);
	}
	dij();
	for(int i=n+2;i<=n*2;i++){
		if(dis[i]==1e18) printf("-1 ");
		else printf("%lld ",dis[i]);
	}
	return 0;
}
```


---

