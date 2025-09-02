# [CEOI 2008] order

## 题目描述

有 $N$ 个工作，$M$ 种机器，每种机器可以租或者买。每个工作包括若干道工序，每道工序需要某种机器来完成。

你需要最大化利益。

## 说明/提示

对于 $100\%$ 的数据满足 $1\le N,M\le 1200，1\le x_i\le 5000，b_{ij},y_i\le 20000$。

## 样例 #1

### 输入

```
2 3
100 2
1 30
2 20
100 2
1 40
3 80
50
80
110```

### 输出

```
50```

# 题解

## 作者：YoungLove (赞：17)

[Youngsc](https://youngscc.github.io/)  
**首先如果没有租用机器这种鬼畜的操作，那么就是一个裸的最大权闭合子图例如
[太空飞行计划](https://www.luogu.org/problemnew/show/P2762)**  
**但是有了租用这种操作显然就那样来解决这个问题了**  
**普通的最大权闭合子图将工作与源相连，容量为收益，机器与汇相连，容量为代价的相反数，对应的工作与机器之间是无穷大**  
**这样割掉与源点或汇点相连的边表示选择失去那种利益**  
**感性认识一下，租用机器这种操作仅仅只会对一种工作产生影响，无论其他工作是否需要它**  
**那么启发我们是不是可以用中间工作与机器的相连的边搞一些事情**  
**我们将工作与机器之间的边容量由正无穷变为租用的代价即可处理租用问题**  
**原理就是最大权闭合子图问题的实质是割掉一些边使源和汇不连通**  
**考虑源和汇之间的一条路径，有三种选择，对应割掉三条边**  
**显然个点左右两条边可以影响其他的路径，而割掉中间不会**
**因此我们就可以将中间的边转化为租用操作**
**其他的就和普通的最大权闭合子图一毛一样了**

### 代码
```cpp
# include <bits/stdc++.h>
# define LL long long
# define R register
# define N 1210
# define inf 2000101900
using namespace std;

int n,s,t,e=-1,h[N*2],ans,used[N*2],tot,d,w,m,num;
struct zx{int v,flow,pre;} ed[2000010];
int v[N*2];
queue <int> q;

template <typename T> inline void in(R T& a){
    R char c=getchar(); R T x=0,f=1;
    while (!isdigit(c)) {if (c == '-') f=-1; c=getchar();}
    while (isdigit(c)) x = (x<<1)+(x<<3)+c-'0', c=getchar();
    a = x*f;
}

inline void add(R int x,R int y,R int z){
    ed[++e] = (zx){y,z,h[x]};
    h[x] = e;
}

inline bool bfs(){
    for(R int i=0; i<=t; ++i) v[i] = 0;
    v[0] = 1;
    q.push(0);
    while(!q.empty()){
        R int x=q.front();
        q.pop();
        for(R int i=h[x]; i!=-1; i=ed[i].pre)
        {
            R int p=ed[i].v;
            if(ed[i].flow&&!v[p])
            {
                v[p] = v[x]+1;
                q.push(p);
            }
        }
    }
    return v[t];
}

inline int maxflow(R int x,R int want){
    if(x==t||!want) return want;
    R int flow = 0;
    for(R int i=used[x]; i!=-1; i=ed[i].pre,used[x]=i)
    {
        R int p=ed[i].v;
        if(!ed[i].flow||v[p] != v[x]+1) continue;
        R int f=maxflow(p,min(want,ed[i].flow));
        if(!f) continue;
        ed[i].flow -= f;
        ed[i^1].flow += f;
        flow += f;
        want -= f;
    }
    return flow;
}

int main(){
    in(n),in(m);
    s = 0,t = n+m+1;
    for (R int i=s; i<=t; ++i) h[i] = -1;
    for (R int i=1; i<=n; ++i)
    {
        in(w); add(s,i,w),add(i,s,0);
        tot += w;
        in(num);
        while (num--)
        {
            in(d),in(w);
            add(i,d+n,w),add(d+n,i,0);
        }
    }
    for (R int i=1; i<=m; ++i) in(w), add(n+i,t,w),add(t,n+i,0);
    while (bfs()){
        memcpy(used,h,sizeof(h));
        ans += maxflow(s,inf);
    }
    printf("%d\n",tot-ans);
    return 0;
}

```

---

## 作者：wxwoo (赞：8)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/07/10/solution-p4177)

******

[原题目链接](https://www.luogu.org/problemnew/show/P4177)

先无视租机器，~~明显的~~最大权闭合子图

最大权闭合子图：

> 给定一个有向图，点有点权，选择一个子图，满足子图上如果选择了一个点就必须选择它后继的所有点。最大化点权和。

我们将机器和任务都看成一个点

如果这题没有租机器，这题的建边方式就应该是这样：

> 1. 源点向订单连流量为利润的边
>
> 1. 机器向汇点连流量为购买价格的边
>
> 1. 每个订单向需要的机器连流量为inf的边

可以发现，源点连的边都是订单的利润，汇点连的边都是机器的成本，只有机器和订单之间的边是$inf$

对于每个订单需要的相同机器，租用的价格也不一样

所以我们考虑把$inf$换成租机器的费用

从正确性的角度考虑，跑最大流（最小割）是计算最优方案下的成本，若总租借费用低于购买机器费用，表示购买费用的那条边就不会满流，防止购买机器反而增加成本；反之表示购买费用的那条边就会满流，限制住成本因多次租用同一机器而增加

最终建边方式如下：

> 1. 源点向订单连流量为利润的边
>
> 1. 机器向汇点连流量为购买价格的边
>
> 1. 每个订单向需要的机器连流量为租用费用的边

代码如下

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
template<typename T>
inline void read(T &x)
{
    int ch=getchar();
    T f=1;
    x=0;
    while(!('0'<=ch&&ch<='9'))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9')
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    x*=f;
}
const int inf=1e9,N=3e5+1;
struct edge
{
    int from,to,nxt,cap,flow;
}e[N*20];
int cnt,n,m,sour,sink,head[N],ans,q[N],l[N],p[N];
inline void add(const int &u,const int &v,const int &f)
{
    e[++cnt]=(edge){u,v,head[u],f,0};
    head[u]=cnt;
    e[++cnt]=(edge){v,u,head[v],0,0};
    head[v]=cnt;
}
inline bool find()
{
    memset(l,0,sizeof(l));
    int h=1,t=1;
    q[1]=sour;
    l[sour]=1;
    while(h<=t)
    {
        int x=q[h++];
        for(int i=head[x];i;i=e[i].nxt)
        {
            if(!l[e[i].to]&&e[i].cap>e[i].flow)
            {
                q[++t]=e[i].to;
                l[e[i].to]=l[x]+1;
                if(e[i].to==sink)
                    return 1;
            }
        }
    }
    return 0;
}
int dfs(const int &x,const int &now)
{
    if(x==sink||!now)
        return now;
    int t=now,detla;
    for(int i=head[x];i;i=e[i].nxt)
    {
        if(e[i].cap>e[i].flow&&l[e[i].to]==l[x]+1)
        {
            detla=dfs(e[i].to,min(t,e[i].cap-e[i].flow));
            if(!detla)
                l[e[i].to]=0;
            e[i].flow+=detla;
            e[((i-1)^1)+1].flow-=detla;
            t-=detla;
            if(t==0)
                break;
        }
    }
    return now-t;
}
inline void dinic()
{
    while(find())
        ans+=dfs(sour,inf);
}
int main()
{
    read(n);
    read(m);
    sour=0;
    sink=n+m+1;
    int u,v,t,r,tot=0;
    for(int i=1;i<=n;++i)
    {
        read(v);
        read(t);
        add(sour,i,v);
        for(int j=1;j<=t;++j)
        {
            read(u);
            read(r);
            add(i,u+n,r);
        }
        tot+=v;
    }
    for(int i=1;i<=m;++i)
    {
        read(v);
        add(i+n,sink,v);
    }
    dinic();
    printf("%d",tot-ans);
    return 0;
}
```

---

## 作者：AuZeb (赞：5)

## 思路

本题可转化为最大权闭合图问题。最大权闭合图是指在一个有向图中，对于图中的任意一个点，其所有出边指向的点都在该闭合图内，且该闭合图的权值之和最大。

1. **节点设置**：
    - 设立一个源点 $S$ 和一个汇点 $T$。
    - $n$ 个工作对应图中的节点 $1$ 到 $n$。
    - $m$ 种机器对应图中的节点 $n+1$ 到 $n+m$。

3. **边的构建**：
    - 从源点 $S$ 向每个工作节点连接一条边，边的容量为该工作的收入 $x_i$。
    - 从该工作节点向其需要的机器节点连接一条边，边的容量为租用该机器的费用 $b_{ij}$。
    - 从每个机器节点向汇点 $T$ 连接一条边，边的容量为购买该机器的费用 $y_i$。

最终输出总收益减去最小割（最大流），样例如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3hjvpup.png)

简单的来说，成本限制了最大流，保证了一定不会亏本，而当且仅当跑满最大流时，赚的最多（投的多，机器多，能做的项目多），最终用总共得到的钱减去成本就是赚的钱。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2500,M=5000000,INF=0x3f3f3f3f;
struct Edge{int to,cap,flow,ne;}e[M];
int he[N],cnt=0,cur[N],dep[N],S,T;
void addEdge(int u,int v,int cap){
	e[cnt]={v,cap,0,he[u]},he[u]=cnt++,
	e[cnt]={u,0,0,he[v]},he[v]=cnt++;
}
bool bfs(){
	memset(dep,-1,sizeof(dep));
	queue<int> q; q.push(S),dep[S]=0;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=he[u];i!=-1;i=e[i].ne){
			int v=e[i].to;
			if(dep[v]==-1&&e[i].cap>e[i].flow)
				dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[T]!=-1;
}
int dfs(int u,int f){
	if(u==T||f==0) return f;
	int flow=0;
	for(int &i=cur[u];i!=-1;i=e[i].ne){
		int v=e[i].to;
		if(dep[v]==dep[u]+1){
			int newf=dfs(v,min(f,e[i].cap-e[i].flow));
			if(newf>0){
				e[i].flow+=newf,e[i^1].flow-=newf,flow+=newf,f-=newf; // 边的编号要从 0 开始，head 要赋值为 -1。
				if(f==0) break;
			}
		}
	}
	return flow;
}
int dinic(){
	int maxFlow=0;
	while(bfs()){
		for(int i=S;i<=T;i++) cur[i]=he[i];
		maxFlow+=dfs(S,INF);
	}
	return maxFlow;
}
int main() {
	int n,m,h=0; cin>>n>>m; S=0,T=n+m+1;
	memset(he,-1,sizeof(he));
	for(int i=1,x,t;i<=n;i++) {
		cin>>x>>t,h+=x,addEdge(S,i,x);
		for(int j=0,a,b;j<t;j++)
			cin>>a>>b,addEdge(i,n+a,b);
	}
	for(int i=1,y;i<=m;i++) cin>>y,addEdge(n+i,T,y);
	cout<<h-dinic();
	return 0;
}
```

---

## 作者：YZren (赞：3)

这么好的最小割题竟然没有 vector 的题解，不妨让我写一篇吧。

# 思路

1. 如果没有租的话，其实就和 [P4174 \[NOI2006\] 最大获利](https://www.luogu.com.cn/problem/P4174)一样了，用户连源点（流量为收益），仓库连汇点（流量为成本），用户和仓库间流量为无穷大（避免被割了），跑最小割就好了。由于其他题解没有用 vector，一下便是最小割模版。

```cpp
struct edge{int to,val,id;}; vector<edge> vec[maxn];
inline bool bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int> q; q.push(S); dis[S]=0;
	while(!q.empty()){
		int p=q.front(); q.pop();
		for(auto y:vec[p]) if(dis[y.to]==-1&&y.val) dis[y.to]=dis[p]+1,q.push(y.to);
	}
	memset(cur,0,sizeof(cur));
	return dis[T]!=-1;
}
inline int dfs(int x,int inc){
	if(x==T) return inc;
	int delta=inc;
	f(i,cur[x],(int)vec[x].size()-1){
		cur[x]=i;//当前弧优化
		if(vec[x][i].val&&dis[vec[x][i].to]==dis[x]+1){
			int d=dfs(vec[x][i].to,min(delta,vec[x][i].val));
			vec[x][i].val-=d; vec[vec[x][i].to][vec[x][i].id].val+=d;
			delta-=d; if(!d) dis[vec[x][i].to]=-1;
			if(!delta) break;
		}
	}
	return inc-delta;
}
inline void Dinic(){
	while(bfs()) ans-=dfs(S,LLONG_MAX);
	write(ans);
}
```

其中建图可以这么建。

```cpp
inline void add(int u,int v,int w){
	Uto=vec[u].size();//求v放得位置，方便找反边
	Vto=vec[v].size();
	vec[u].push_back({v,w,Vto});
	vec[v].push_back({u,0,Uto});
};
```

2. 考虑有租的情况，可以将中间的流量从无穷大改为租的费用，以下便是建图的代码（图可以参照 [zeb6666](https://www.luogu.com.cn/user/387585) 题解的图)。

```cpp
f(i,1,n){
		u=read(); v=read(); Uto=vec[S].size(); Vto=vec[i].size(); ans+=u;
		vec[S].push_back({i,u,Vto}); vec[i].push_back({S,0,Uto});
		f(j,1,v){
			w=read(); cost=read(); Uto=vec[i].size(); Vto=vec[n+w].size();
			vec[i].push_back({n+w,cost,Vto}); vec[w+n].push_back({i,0,Uto});
		}
	}
	f(i,1,m) u=read(),Uto=vec[i+n].size(),Vto=vec[T].size(),vec[i+n].push_back({T,u,Vto}),vec[T].push_back({i+n,0,Uto});
```

这样一个用 vector 的代码好了。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define f(i,j,k) for(int i=j;i<=k;i++)
#define F(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
const int maxn=10000+10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x){
	if(x<0) {x=~(x-1); putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n=read(),m=read(),S=0,T=n+m+1,cur[maxn],dis[maxn],Uto,Vto,u,v,w,cost,ans;
struct edge{int to,val,id;}; vector<edge> vec[maxn];
inline bool bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int> q; q.push(S); dis[S]=0;
	while(!q.empty()){
		int p=q.front(); q.pop();
		for(auto y:vec[p]) if(dis[y.to]==-1&&y.val) dis[y.to]=dis[p]+1,q.push(y.to);
	}
	memset(cur,0,sizeof(cur));
	return dis[T]!=-1;
}
inline int dfs(int x,int inc){
	if(x==T) return inc;
	int delta=inc;
	f(i,cur[x],(int)vec[x].size()-1){
		cur[x]=i;
		if(vec[x][i].val&&dis[vec[x][i].to]==dis[x]+1){
			int d=dfs(vec[x][i].to,min(delta,vec[x][i].val));
			vec[x][i].val-=d; vec[vec[x][i].to][vec[x][i].id].val+=d;
			delta-=d; if(!d) dis[vec[x][i].to]=-1;
			if(!delta) break;
		}
	}
	return inc-delta;
}
inline void Dinic(){
	while(bfs()) ans-=dfs(S,LLONG_MAX);
	write(ans);
}
inline void work(){
	f(i,1,n){
		u=read(); v=read(); Uto=vec[S].size(); Vto=vec[i].size(); ans+=u;
		vec[S].push_back({i,u,Vto}); vec[i].push_back({S,0,Uto});
		f(j,1,v){
			w=read(); cost=read(); Uto=vec[i].size(); Vto=vec[n+w].size();
			vec[i].push_back({n+w,cost,Vto}); vec[w+n].push_back({i,0,Uto});
		}
	}
	f(i,1,m) u=read(),Uto=vec[i+n].size(),Vto=vec[T].size(),vec[i+n].push_back({T,u,Vto}),vec[T].push_back({i+n,0,Uto});
	Dinic();
}
signed main(){work();return 0;}
```

---

## 作者：wjl1100 (赞：3)

~~这么好的紫题竟然还可以写题解，赶紧来水一篇~~

### [题意](https://www.luogu.com.cn/problem/P4177)

这道题是最大流的板子题，主要思考怎么建图。

### 思路

首先我们建立源点和汇点，这不用多说。然后我们将每个工作与源点连一条流量为收入的边，每个机器与汇点建一条流量为购买费用的边，每个工作与它所需的机器连一条流量为租用费用的边。最后我们用总收入减去最大流就可以得到答案。

### 代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x7f7f7f7f
using namespace std;
const int maxn = 1e5 + 100;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n , m , s , t , dis[maxn] , head[maxn] , cul[maxn] , tot = 1 , u , w , v;
struct node {
	int to , next , w;
}e[maxn << 6];
inline void add(int u , int v , int w) {
	e[++tot] = {v , head[u] , w};
	head[u] = tot;
}
inline bool bfs() {
	memset(dis , -1 , sizeof(dis));
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = e[i].next) {
			int v = e[i].to;
			if(dis[v] == -1 && e[i].w) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
	return dis[t] != -1;
}
inline int dfs(int x , int sum) {
	if(x == t) return sum;
	int last = sum;
	for(int i = cul[x]; i; i = e[i].next) {
		cul[x] = i;
		int v = e[i].to;
		if(dis[v] == dis[x] + 1 && e[i].w) {
			int w = dfs(v , min(last , e[i].w));
			e[i].w -= w;
			e[i ^ 1].w += w;
			last -= w;
			if(!last) break;
		}
	}
	return sum - last;
}
signed main() {
	n = read();
	m = read();
	s = n + m + 1;
	t = s + 1;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		w = read();
		u = read();
		sum += w;
		add(s , i , w);
		add(i , s , 0);
		for(int j = 1; j <= u; j++) {
			v = read();
			w = read();
			add(i , v + n , w);
			add(v + n , i , 0);
		}
	}
	for(int i = 1; i <= m; i++) {
		w = read();
		add(i + n , t , w);
		add(t , i + n , 0);
	}
	int ans = 0;
	while(bfs()) {
		memcpy(cul , head , sizeof(head));
		ans += dfs(s , inf);
	}
	cout << sum - ans << endl;
	return 0;
} 
```

---

## 作者：MloVtry (赞：3)

最小割。

如果不能租用肯定就是最小割的裸题。

现在考虑租用。

租用就是只可以在这一个任务上使用这台机器，不影响其他任务；换言之就是只会影响这一个任务与这一台机器之间的s-t联通关系。

考虑到之前不能租用的模型，任务与机器之间的连边是INF，现在更改成租用费用即可。

代码

```
#define inf (1<<30)
#include<iostream>
#include<cstring>
#include<cstdio>
#define M 5000000
#include<queue>
#define N 5000
using namespace std;
int head[N],to[M],Next[M],cup[M],e=1;
void buid(int u,int v,int c)
{
	Next[++e]=head[u];head[u]=e;to[e]=v;cup[e]=c;
	Next[++e]=head[v];head[v]=e;to[e]=u;cup[e]=0;
}
int itc[N],ans,use[N],n,m,s,t;
queue<int> q;
bool bfs()
{
	memset(itc,0,sizeof(itc));
	itc[s]=1;q.push(s);
	while(!q.empty())
	{
		int now=q.front();q.pop();
		for(int i=head[now];i;i=Next[i])
		{
			if(!cup[i]) continue;
			int j=to[i];
			if(!itc[j]) itc[j]=itc[now]+1,q.push(j);
		}
	}
	return itc[t];
}
int doit(int now,int want)
{
	if(now==t||!want) return want;
	int get=0;
	for(int i=use[now];i;i=Next[i],use[now]=i)
	{
		int j=to[i];
		if(itc[j]!=itc[now]+1) continue;
		int f=doit(j,min(want,cup[i]));
		want-=f;get+=f;
		cup[i]-=f;cup[i^1]+=f;
		if(!want) return get;
	}
	return get;
}
void max_flow()
{
	while(bfs())
	{
		for(int i=s;i<=t;++i) use[i]=head[i];
		ans-=doit(s,inf);
	}
}
int main()
{
	scanf("%d%d",&n,&m);t=n+m+1;
	for(int i=1;i<=n;++i)
	{
		int f,m;scanf("%d%d",&f,&m);ans+=f;
		buid(s,i,f);
		for(int j=1;j<=m;++j)
		{
			int id,z;scanf("%d%d",&id,&z);
			buid(i,id+n,z);
		}
	}
	for(int i=1;i<=m;++i)
	{
		int f;scanf("%d",&f);
		buid(n+i,t,f);
	}
	max_flow();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：mqmhaaaa1 (赞：2)

# 水

第一眼看上去就想到 [p4174](https://www.luogu.com.cn/problem/P4174)，就是求净利润，主要考点是我们要理解最小割求这类问题的原理，想明白就是水题一堆了。

# 正片开始

题意就不解释了，这题和 p4174 唯一不同的地方就是加了一个奇奇怪怪的租用操作，如果没有这个操作，问题就很好办了，就是一个十分简单的划分问题，建图大概长下面这样（$x$ 为工作，$y$ 为机器）。

![](https://cdn.luogu.com.cn/upload/image_hosting/zi3ldjso.png)

具体思路有点像小 M 的作物，把工作当成一种划分关系，再去掉机器与 $s$ 的连边（因为没有贡献，把机器到 $t$ 连边割掉就相当于选了该机器，花了一些钱，事实上可以想成：**不选这个机器，就有一定贡献**）。

但加上这个“租用”操作后怎么做呢？

这便是本题难点，也就是考验对最小割用途的理解了。

## 正确做法

首先上面的模型肯定有用，也就是在上面修修改改。

让我们想一下租用的本质。思考下就会发现，当我们买了这个机器，就不会再任何工作中租这个机器了，当我们不卖这台机器，就需要我们在工作中租用。

把上面的转化成最小割模型，就变成：**不割 $y\to t$ 的边，就要把所有到 $y$ 的边割掉，否则，就把 $y\to t$ 的边割掉**，也就是，我们把图变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/whwcx2l8.png)

这样做的话，我们要么把所有工作到该机器的边割掉（租用），要么割掉该机器与 $t$ 的连边（买下机器），根据最小割定义，上述成立。

以这个方法建图，就可以通过本题（因为是个二分图，dinic 大法很快）。

建注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
inline void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
inline ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=5e3+10,M=2e6+10,inf=0x3f3f3f3f;
ll to[M<<1],nxt[M<<1],w[M<<1],bh[N],tot=1;
ll head[N],st[N];
bool vis[N];
inline void add(ll u,ll v,ll z){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=z;
	bh[u]=tot;
//	cout<<u<<" "<<v<<" "<<z<<'\n';
	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	bh[v]=tot;
}
ll s,t;
inline bool bfs(){
	for(ll i=s;i<=t;i++){
		head[i]=bh[i];
		st[i]=0;
	}
	queue<ll>q;
	q.push(s);
	st[s]=0;vis[s]=1;
	while(q.size()){
		ll u=q.front();q.pop();
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&!st[v]&&v!=s){
				st[v]=st[u]+1;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return st[t];
}
ll mxf=0;
ll dic(ll u,ll flow){
	vis[u]=1;
	if(u==t){
		mxf+=flow;return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&(!vis[v]||v==t)&&st[v]==st[u]+1){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb,w[i^1]+=jb;
			zy+=jb;flow-=jb;
			if(!flow)break;
		}
	}
	vis[u]=0;
	return zy;
}
//引以为傲的dinic板子 ，我几乎把简单的优化都写上了
ll n,m,sum=0;
int main(){
	//这里sum只加上能赚的，因为求净利润 
	n=read();m=read();
	s=0;t=n+m+1;
	for(ll i=1;i<=n;i++){
		ll u=i;
		ll val=read(),q=read();
		sum+=val;
		add(s,u,val);//s->x 
		while(q--){
			ll v=read(),cost=read();
			v=v+n;
			add(u,v,cost);//x->y
		}
	}
	for(ll i=1;i<=m;i++){
		ll u1=i+n;
		ll cost=read();
		add(u1,t,cost); //y->t
	}
	while(bfs()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inf);
		}
	}
	write(sum-mxf);
	return 0;
	// track complete 
}
```

goodbye，简单 wll 题。

# 补录

上传成功后才发现还有一种思考方式就是把这题想成**最大权闭合子图**，不过我这个主体以最小割的想法因该没问题

---

## 作者：ker_xyxyxyx_xxs (赞：2)

[P4177 [CEOI2008]order](https://www.luogu.com.cn/problem/P4177)

乍一看，就是最大权值闭合子图。

但是有租用。租用和买有什么区别？费用不一样，没了。那么直接把连边的 $ \infty $ 变成费用即可。

为什么可以这样做？本题答案是总收益 $ - $ 最小割。这样修改之后最小割可能变小，可以保障答案正确性，又因为他们也是连起来的需要费用保证联通，所以是满足题意的。（说的可能不太清楚）。

常规连边即可。

源点 $ \rightarrow $ 每个工作，边权为利益。

每台机器 $ \rightarrow $ 汇点，边权为购买费用。

每个工作 $ \rightarrow $ 所需机器，边权为租用的费用。

Code

```cpp
 # include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int M = 2e6 + 5;
const int inf = 1e9; 

typedef struct {
	int x , y , z , next;
}Node;
Node edge[M];
int E = 1 , elast[N];
int S , T;

void add(int x , int y , int z) {
	E ++ , edge[E].x = x , edge[E].y = y , edge[E].z = z , edge[E].next = elast[x] , elast[x] = E;
}

int dis[N] , cnt[N];
void bfs(int start) {
    queue<int> q;
    q.push(start);
    dis[start] = 0;
    cnt[S] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = elast[cur] ; i ; i = edge[i].next) {
            int v = edge[i].y;
            if (dis[v] != -1) continue;
            dis[v] = dis[cur] + 1;
            q.push(v);
            cnt[dis[v]] ++;
        }
    }
}
int cur[N];
int dfs(int u , int flow) {
    if (u == T) return flow;
    int delta = 0;
    for (int i = cur[u] ; i ; i = edge[i].next) {
        cur[u] = i;
        int v = edge[i].y;
        if (edge[i].z > 0 && dis[u] == dis[v] + 1) {
            int temp = dfs(v , min(flow - delta , edge[i].z));
            edge[i].z -= temp;
            edge[i ^ 1].z += temp;
            delta += temp;
            if (delta == flow) return delta;
        }
    }
    if (dis[S] >= T + 1) return delta;
    cur[u] = elast[u];
    if (-- cnt[dis[u]] == 0) dis[S] = T + 1;
    cnt[++ dis[u]] ++;
    return delta;
}
int Isap() {
    int ans = 0;
    memset(cnt , 0 , sizeof cnt);
    memset(dis , -1 , sizeof dis);
    bfs(T);
    for (int i = 0 ; i <= T ; i ++) {
        cur[i] = elast[i];
    }
    while (dis[S] < T + 1) ans += dfs(S , inf);
    return ans;
}

int m , n , sum = 0;
int main() {
	cin >> n >> m;
	S = 0 , T = n + m + 1;
	for (int i = 1 ; i <= n ; i ++) {
		int in_Kikyo , step;
		cin >> in_Kikyo >> step;
		sum += in_Kikyo;
		add(S , i , in_Kikyo) , add(i , S , 0);
		for (int j = 1 ; j <= step ; j ++) {
			int used , use;
			cin >> used >> use;
			add(i , n + used , use) , add(n + used , i , 0);
		}
	}
	for (int i = 1 ; i <= m ; i ++) {
		int cos;
		cin >> cos;
		add(n + i , T , cos) , add(T , n + i , 0);
	}
	cout << sum - Isap() << endl;
	return 0;
}
```





---

## 作者：zac2010 (赞：2)

不妨先看一个子问题：[太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)，它就是广为人知的“最大权闭合子图”模型。

在这道子问题中，仪器（机器）不能租用。我们考虑一个反悔的过程——开始先把所有实验的贡献算上，之后利用最小割模型去掉最小代价使得方案合法。

在最小割模型中，我们把所有实验、仪器都分别看成一个点。其中，源点向所有实验连一条容量为实验赞助费的边，所有仪器向汇点连一条容量为购买代价的边。对于实验、仪器两者之间的边，只需要把实验连向它所需要的仪器，容量为无穷大（表示中间的边不能割，只能割掉实验的边或者所有相关仪器的边）。

最后求一个最小割就行了。

然而在这道题中，却出现了租用的代价。考虑把工序与机器之间的边权替换成租用的价格——问题迎刃而解。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 2410, M = 1442410;
const ll INF = 1e18;
struct E{int v; ll w, nxt;} e[M << 1];
int n, m, s, t, ans, vis[N], a[N], b[N], tote, head[N], now[N], dep[N];
vector<int> id;
void Adde(int u, int v, ll w){
    e[tote] = {v, w, head[u]}, head[u] = tote++;
}
int bfs(){
    queue<int> q; q.push(s);
    memset(dep, 0, sizeof(dep)), dep[s] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = now[u] = head[u]; ~i; i = e[i].nxt)
            if(e[i].w && !dep[e[i].v])
				q.push(e[i].v), dep[e[i].v] = dep[u] + 1;
    }
    return dep[t];
}
ll dfs(int u, ll in){
    if(u == t) return in; ll out = 0;
    for(int i = now[u]; ~i && in; i = e[i].nxt){
        int v = e[i].v; ll w = e[i].w; now[u] = i;
        if(dep[v] == dep[u] + 1 && w){
            ll flow = dfs(v, min(in, (ll)w));
            in -= flow, out += flow;
            e[i].w -= flow, e[i ^ 1].w += flow;
        }
    }
    if(!out) dep[u] = 0; return out;
}
ll dinic(){
    ll ret = 0;
    while(bfs()) ret += dfs(s, INF);
    return ret;
}
int main(){
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int ti; s = 0; t = n + m + 1;
    FL(i, 1, n){
        scanf("%d%d", &a[i], &ti), ans += a[i];
        Adde(s, i, a[i]), Adde(i, s, 0);
        FL(j, 1, ti){
            int x, y; scanf("%d%d", &x, &y);
            Adde(i, n + x, y), Adde(n + x, i, 0);
        }
    }
    FL(i, 1, m){
        scanf("%d", &b[i]);
        Adde(n + i, t, b[i]), Adde(t, n + i, 0);
    }
    ans -= dinic(), printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：crescentic (赞：2)

[order](https://www.luogu.com.cn/problem/P4177)

明显的最大权闭合图，唯一有所不同的就只有**租**这种~~迷惑~~操作了。

**题目分析**： 

采用模板化的建图方式：

- 首先，因为第 $i$ 个任务的收入相当于正边权，所以连由**源点** $s$ 到任务 $i$ 的容量为**收入** $xi$ 的有向边；

- 然后，先不考虑购买操作，假定**只能租**，那问题就很简单了，直接连一条由任务 $i$ 到机器 $b$ 的容量为其**费用** $b$ 的有向边；

- 最后，考虑购买操作会对结果产生什么影响。可以发现，对于第 $i$ 台机器而言，当且仅当前面所有租用第 $i$ 机器产生的总费用**大于**购买机器的费用 $c$ 时，我们才会选择购买机器。于是就可以利用**网络流**的特性，将第 $i$ 台机器向**汇点** $t$ 连一条容量为 $c$ 的有向边。因为，第一，费用相当于负权，应该连向汇点；其次，这样连边可以限制当前机器的费用（如果总租金小于购买费用，选择租；如果大于了购买费用，当前边的容量会限制流量，将费用变为购买值）。

最后答案就是所有任务总收入减去最小割的值。剩下的都是板子啦~~



**完整代码**:

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 2420, M = 3e6, inf = 1e9;
int n,m,s,t,tot = -1,head[N],cur[N],dep[N],f[M],sum,q[M],top,ed;
struct node {
	int to,nex;
}e[M];
inline void add(int x,int y,int w) {
	e[++tot] = (node) {y,head[x]}, f[tot] = w, head[x] = tot;
	e[++tot] = (node) {x,head[y]}, head[y] = tot; 
}
inline bool bfs() {
	memset(dep,-1,sizeof(dep));
	dep[s] = 0, cur[s] = head[s], q[top = 1] = s; ed = 1;
	int now,ver;
	while(top <= ed) {
		now = q[top++];
		for(register int i = head[now]; ~i; i = e[i].nex) {
			ver = e[i].to;
			if(dep[ver] == -1 && f[i]) {
				dep[ver] = dep[now] + 1, cur[ver] = head[ver];
				if(ver == t) return 1;
				q[++ed] = ver;
			}
		}
	}
	return 0;
}
inline int find(int x,int limit) {
	if(x == t) return limit;
	int flow = 0, tmp, ver;
	for(register int i = head[x]; ~i && flow < limit; i = e[i].nex) {
		ver = e[i].to;
		if(dep[ver] == dep[x] + 1 && f[i]) {
			tmp = find(ver,min(limit - flow,f[i]));
			if(!tmp) dep[ver] = -1;
			f[i] -= tmp, f[i ^ 1] += tmp, flow += tmp; 
		}
	}
	return flow;
}
inline int dinic() {
	int res = 0, flow;
	while(bfs()) res += find(s,inf);
	return res;
}
inline void read(int &x) {
	x = 0;int ff = 1;
	char s = getchar();
	while(s < '0' || s > '9') {
		if(s == '-') ff = -1;
		s = getchar();
	}
	while(s <= '9' && s >= '0') {x = x * 10 + s - '0', s = getchar(); }
	x *= ff;
}
signed main() {
	memset(head,-1,sizeof(head));
	read(n), read(m);
	int a,b,xi,ti;
	s = 0, t = n + m + 1;
	for(register int i = 1; i <= n; i ++) {
		read(xi), read(ti);
		sum += xi, add(s,i,xi);
		while(ti --) read(a), read(b), add(i,a + n,b);
	}
	for(register int i = 1; i <= m; i ++) read(a), add(i + n,t,a);
	printf("%d",sum - dinic());
	return 0;
} 
```


---

## 作者：cike_bilibili (赞：1)

显然一个工作可以选择做或者不做，一个机器也可以考虑买或租，都是二选一，所以考虑最小割。

建立源点与汇点，将源点与每一个工作连上权值为这件工作价值的边，然后将每一件工作与每一道工序所需的机器连上权值为租这台机器的代价的边，最后将每一个机器向汇点连上权值为买这台机器的代价的边，跑最小割就行了。

正确性显然，因为每一种边分别代表了不做这项工作、租和买。

理解不了可以看一下这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hsi170t3.png)

---

## 作者：HHC883 (赞：0)

# 题目分析
前置知识：最小割。

最小割板子题。

若不允许租用机器，那么这题就变成了[P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)。建图如下：

- 源点向工作 $i$ 连容量为 $x_i$ 的边。
- 每个工作向它需要的每个机器连容量为 $+\infty$ 的边。
- 机器 $i$ 向汇点连容量为 $y_i$ 的边。

然后答案就是所有 $x_i$ 的和减去上面建的网络的最小割（**注意并不是最小割本身**）。

考虑这样做的本质。一个割其实是删去某些边使得网络不连通。而由于是最小割，工作与机器之间容量为 $+\infty$ 肯定不会被选为割边。那么对于某个工作和其中一个它需要的机器，只能选源点与工作之间的边或机器与汇点之间的边并把这条边割断（不能都不选，否则源点汇点可以依次通过它们而连通）。

选择源点与工作之间的边就相当于这个工作不做了，它能产生的收入也不要了，对应地在答案中被减掉。这样它所需要的机器对应的边就没必要去割断了，也就不会产生买机器的代价（除非其它工作还需要这个机器）。而选择机器与汇点之间的边就相当于买下这个机器，对应地从答案中减去它的费用。这样只要买了某个工作需要的所有机器，通过这个工作已经到达不了汇点，那么源点和这个工作之间的边就没必要割掉，相当于说就可以去完成这个工作了，它产生的收入在答案中得以保留，没有被扣去。这符合题意。

说了这么多，回来看看可以租用机器的情况下要怎么做。这相当于对于某个工作和其中一个它需要的机器，你多了一种选择——既完成（不割去）这个工作，也不买（不割去）这个机器，而是租用这个机器。这让我们想起那条容量为 $+\infty$ 的边——如果把它的容量改为租用这个机器的费用，那么想要断掉源点到汇点的路径，还可以选择割断这条工作与机器之间的边，相当于租用这个机器，对应地从答案中减去租用的费用。这符合题意。

于是，本题的做法也很显然了——建图如下：

- 源点向工作 $i$ 连容量为 $x_i$ 的边。
- 每个工作向它需要的每个机器连容量为租用机器的费用的边。
- 机器 $i$ 向汇点连容量为 $y_i$ 的边。

然后答案就是所有 $x_i$ 的和减去上面建的网络的最小割。

其中源点可以编号为 $0$，汇点编号为 $n + m + 1$，工作 $i$ 编号为 $i$，机器 $i$ 编号为 $n+i$。

最小割可以用 Dinic 算法求得。

时间复杂度为 $O\left((n + m)^2 (n + m + \sum_{i = 1}^n t_i)\right)$。当然，网络流的题分析时间复杂度的意义不大。

# 参考代码
```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,m;
int nxt[(int)3e6+5],head[2405],cnt=1;
struct edge{
	int v,cap,flow;
} es[(int)3e6+5];
int d[2405],cur[2405];
void link(int u,int v,int cap,int flow){
	es[++cnt]=edge{v,cap,flow};
	nxt[cnt]=head[u];
	head[u]=cnt;
}
bool bfs(){
	queue<int> q;
	for(int i=0;i<=n+m+1;i++) d[i]=0;
	q.push(0);
	d[0]=1;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=nxt[i]){
			if(!d[es[i].v]&&es[i].cap-es[i].flow>0){
				d[es[i].v]=d[now]+1;
				if(es[i].v==n+m+1) return true;
				q.push(es[i].v);
			}
		}
	}
	return false;
}
int dfs(int now,int minn){
	if(now==n+m+1) return minn;
	int flow=0;
	for(int& i=cur[now];i;i=nxt[i]){
		if(d[es[i].v]==d[now]+1){
			int f=dfs(es[i].v,min(minn,es[i].cap-es[i].flow));
			flow+=f;
			minn-=f;
			es[i].flow+=f;
			es[i^1].flow-=f;
			if(!minn) break;
		}
	}
	return flow;
}
int dinic(){
	int flow=0;
	while(bfs()){
		for(int i=0;i<=n+m+1;i++) cur[i]=head[i];
		flow+=dfs(0,1e9);
	}
	return flow;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	int tot=0;
	int cost,k,id;
	for(int i=1;i<=n;i++){
		cin>>cost>>k;
		link(0,i,cost,0);
		link(i,0,0,0);
		tot+=cost;
		while(k--){
			cin>>id>>cost;
			link(i,n+id,cost,0);
			link(n+id,i,0,0);
		}
	}
	for(int i=1;i<=m;i++){
		cin>>cost;
		link(n+i,n+m+1,cost,0);
		link(n+m+1,n+i,0,0);
	}
	cout<<tot-dinic();
	return 0;
}
```

---

## 作者：mjsdnz (赞：0)

+ [原题链接](https://www.luogu.com.cn/problem/P4177)

由于这道题题目太过简洁，所以就不放题目大意了。

## 建模

一个最大权闭合子图的变种。此类问题可以抽象为以下几个对象的关系：
  
  + 1.**大项目**，对应题中的工作。**大项目**中会包含许多个**小项目**，只有完成所有**小项目**才能完成**大项目**，并且完成**大项目**会获得相应的**收益**。

  + 2.**小项目**，对应题中的工序。完成**小项目**需要一定的**花费**。

我们最终的任务就是选择需要完成的**大项目**，来使得**收益**减**花费**最大。

我们发现最小割可以完美解决这样的问题。只要将源点连向所有**大项目**，流量为**大项目的收益**，每个**大项目**向其所需的**小项目**连流量为无穷大的边，每个**小项目**向汇点连流量为**小项目的花费**的边。那么最小割割掉的割边流量就是保证合法性的最小流量。那么让**所有大项目的收益**减去最小割就是最大的收益。

不过这道题有一个“租”的操作，那我们就可以吧原本每个**大项目**向其所需的**小项目**连的边的流量由无穷大改为租金。原本设为无穷大的目的是为了在割边是不影响大小项目之间的连通性，毕竟这部分与统计答案无关。但是在多了个租金限制之后就需要统计**小项目**每次的花费了。因此将无穷大流量改为租金。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,s,t;
int inf=0x3f3f3f3f;
const int N=1e5+10;
const int M=5e6+10;
struct edge {
	int u, v, c, val, nxt;
	edge(int u = 0, int v = 0, int c = 0, int val = 0, int nxt = 0): u(u), v(v), c(c), val(val), nxt(nxt) {}
}e[M];
int head[N];
int now[N];
int cnt=1;
void ADD(int u,int v,int c){
	cnt++;
	e[cnt]=edge(u,v,c,0,head[u]);
	head[u]=cnt;
}
void add_edge(int u,int v,int c){
	ADD(u,v,c);
	ADD(v,u,0);
}
int dep[N];
bool bfs(){
	memset(dep,0,sizeof dep);
	memcpy(now,head,sizeof head);
	dep[s]=1;
	queue<int>q;q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			int c=e[i].c;
			if(!c||dep[v]!=0) continue;
			dep[v]=dep[u]+1;
			q.push(v);
		}
	}
	return dep[t]!=0;
}
int dfs(int u,int t,int flow){
	if(u==t) return flow;
	int nowflow=0;
	for(int i=now[u];i&&nowflow<flow;i=e[i].nxt){
		now[u]=i;
		int v=e[i].v;
		int c=e[i].c;
		if(!c||dep[v]!=dep[u]+1)continue;
		int ff=dfs(v,t,min(c,flow-nowflow));
		if(ff) e[i].c-=ff,e[i^1].c+=ff,nowflow+=ff;
		else dep[v]=inf;
	}
	return nowflow;
}
int maxflow(){
	int ans=0;
	while(bfs()){
		int nowflow;
		while((nowflow=dfs(s,t,inf))) ans+=nowflow;
	}
	return ans;
}
int main()
{
	cin>>n>>m;
	s=n+m+1,t=s+1;
	int sum=0;
	for(int i=1;i<=n;i++){
		int x,tt;
		cin>>x>>tt;
		sum+=x;
		add_edge(s,i,x);
		while(tt--){
			int aa,bb;
			cin>>aa>>bb;
			add_edge(i,n+aa,bb);
		}
	}
	for(int i=1;i<=m;i++){
		int vv;
		cin>>vv;
		add_edge(n+i,t,vv);
	}
	cout<<sum-maxflow();
}
```

---

## 作者：Stinger (赞：0)

**本题缺少 $\sum t_i$ 的范围，必须人肉二分数组大小才能通过，建议管理员加上**。

最小割经典题。

首先不考虑租用，只考虑购买机器。最大流显然是凉了，所以考虑最小割。我们需要构造一个图，如果表示获得这个任务收益的边和表示购买所需要的机器的边都没有割掉，那么 $s,t$ 连通（$s$ 为源点，$t$ 为汇点）。

那么从源点 $s$ 向这些机器连边权为购买这个机器所需的费用的边，从机器向一个任务连边权为 INF 的边，从任务向汇点 $t$ 连一条边权为这个任务的收益的边。

~~其实以上是完全按照 [P4313 文理分科](https://www.luogu.com.cn/problem/P4313) 的套路连的边（（（~~

考虑租用。如果租用了机器我就不用买机器也能获得任务的受益了，所以机器向任务连的边并不是不可以割掉的，边权应该为这个任务租用这台机器的费用。

然后就完美解决了。数组开三百万能过。

```cpp
#include <cstdio>
#include <queue>
#include <cstring>

const int INF = 1e9;
inline int min(const int x, const int y) {return x < y ? x : y;}
struct Edge {
	int to, nxt, cap;
} e[3000005];
int head[10005], dep[10005], cur[10005], num[10005], tot = 1, s, t, n, m;
std::queue<int> Q;
inline void AddEdge(const int u, const int v, const int cap) {
	e[++ tot].to = v, e[tot].cap = cap, e[tot].nxt = head[u], head[u] = tot;
	e[++ tot].to = u, e[tot].cap = 0, e[tot].nxt = head[v], head[v] = tot;
}

void bfs() {
	memcpy(cur, head, sizeof cur);
	num[dep[t] = 1] = 1;
	Q.push(t);
	while (Q.size()) {
		int u = Q.front();
		Q.pop();
		for (int i = head[u]; i; i = e[i].nxt)
			if (!dep[e[i].to]) ++ num[dep[e[i].to] = dep[u] + 1], Q.push(e[i].to);
		
	}
}
int dfs(const int u, const int flow) {
	if (u == t) return flow;
	int used = 0, tmp = 0;
	for (int i = cur[u]; i; i = e[i].nxt) {
		cur[u] = i;
		if (e[i].cap && dep[u] - 1 == dep[e[i].to]) {
			tmp = dfs(e[i].to, min(e[i].cap, flow - used));
			used += tmp, e[i].cap -= tmp, e[i ^ 1].cap += tmp;
			if (used == flow) return used;
		}
	}
	cur[u] = head[u];
	if (!(-- num[dep[u]])) dep[s] = n + m + 2;
	++ num[++ dep[u]];
	return used;
}

int ISAP() {
	int Maxflow = 0;
	bfs();
	while (dep[s] <= n + m + 1) Maxflow += dfs(s, INF);
	return Maxflow;
}

int main() {
	int ans = 0;
	scanf("%d%d", &n, &m);
	s = 0, t = n + m + 1;
	for (int i = 1; i <= n; ++ i) {
		int x, T;
		scanf("%d%d", &x, &T);
		ans += x;
		AddEdge(i + m, t, x);
		while (T --) {
			int a, b;
			scanf("%d%d", &a, &b);
			AddEdge(a, i + m, b);
		}
	}
	for (int i = 1; i <= m; ++ i) {
		int x;
		scanf("%d", &x);
		AddEdge(s, i, x);
	}
	printf("%d\n", ans - ISAP());
	return 0;
}
```

---

## 作者：chihik (赞：0)

如果没有租用机器这一操作，做法同 [P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)，用最大权闭合子图模型解决。

考虑如何在经典方法构造的新图中体现租用机器这一操作。

新图中对于工作和它所需的机器之间的容量为 $+\infty$ , 意义即为选择这个工作就**必须购买**这个机器。

那么 ‘租用’ 就可以将这条边的容量改为 $b_{ij}$ , 表示选择这个工作后，可以花费 $b_{i,j}$ 的代价代替购买机器。

其它的仍同最大权闭合子图模型。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define Inf 0x3f3f3f3f

const int MAXN = 2400 , MAXM = MAXN * ( MAXN + 1 );
struct Edge {
    int v , flw , nxt;
    Edge(){}
    Edge( int V , int Flw , int Nxt ) { v = V , flw = Flw , nxt = Nxt; }
}Graph[ 2 * MAXM + 5 ];
int Head[ MAXN + 5 ] , Enum = 1;
void Add_Edge( int u , int v , int flw ) {
    Graph[ ++ Enum ] = Edge( v , flw , Head[ u ] ); Head[ u ] = Enum;
    Graph[ ++ Enum ] = Edge( u , 0   , Head[ v ] ); Head[ v ] = Enum;
}
int cur[ MAXN + 5 ] , lev[ MAXN + 5 ];
bool Layer( int S , int T ) {
    memcpy( cur , Head , sizeof( Head ) );
    memset( lev , -1 , sizeof( lev ) );
    queue< int > Que;
    lev[ S ] = 0 , Que.push( S );
    while( !Que.empty() ) {
        int u = Que.front(); Que.pop();
        for( int i = Head[ u ] ; i ; i = Graph[ i ].nxt ) {
            int v = Graph[ i ].v , flw = Graph[ i ].flw;
            if( flw && lev[ v ] == -1 )
                lev[ v ] = lev[ u ] + 1 , Que.push( v );
        }
    }
    return lev[ T ] != -1;
}
int dfs( int u , int t , int f ) {
    if( u == t ) return f;
    for( int &i = cur[ u ] ; i ; i = Graph[ i ].nxt ) {
        int v = Graph[ i ].v , flw = Graph[ i ].flw;
        if( flw && lev[ v ] == lev[ u ] + 1 ) {
            int d = dfs( v , t , min( f , flw ) );
            if( d ) {
                Graph[ i ].flw -= d , Graph[ i ^ 1 ].flw += d;
                return d;
            }
        }
    }
    return 0;
}
int Dinic( int S , int T ) {
    int Mxf = 0;
    while( Layer( S , T ) ) for( int fl = 0 ; ( fl = dfs( S , T , Inf ) ) > 0 ; Mxf += fl );
    return Mxf;
}

int n , m , s , t , val[ MAXN + 5 ];

int main( ) {
    scanf("%d %d",&m,&n); s = n + m + 1,  t = s + 1;
    for( int i = 1 , p ; i <= m ; i ++ ) {
        scanf("%d %d",&val[ n + i ],&p);
        for( int j = 1 , id , ct ; j <= p ;j ++ ) {
            scanf("%d %d",&id,&ct);
            Add_Edge( n + i , id , ct );
        }
    }
    for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&val[ i ]) , val[ i ] *= -1;

    int all = 0;
    for( int i = 1 ; i <= n + m ; i ++ ) {
        if( val[ i ] > 0 ) Add_Edge( s , i , val[ i ] ) , all += val[ i ];
        if( val[ i ] < 0 ) Add_Edge( i , t , -val[ i ] );
    }
    printf("%d\n", all - Dinic( s , t ) );
    return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### P.S.
这题还算比较清新，毕竟是个不需要拆点的网络流。  
毕竟我这个不会最大权闭合子图的菜鸡都能构造出来建图方式。
### Description.
你需要完成很多个工作，每个工作需要一些机器，完成后会得到一定的收益。  
对于每个机器，你可以买下它，是永久的，需要一定的代价。  
对于每个机器，在每个工作中，你可以一次性地租用这个机器，需要一定的代价。  

### Solution.
笔者刚开始看到这题的时候并没有想到最大权闭合子图，但是一样做出来了。  
~~虽然事后发现这个思路就是最大权闭合子图。~~  
首先，我们贪心地假设我们能完成所有工作并不花费任何代价 ~~，做梦~~。  
然后，我们此时有三种选择，如下：
1. 我们可以放弃一个工作不完成。
2. 我们可以在完成一个工作的前提下放弃购买机器（租用
3. 我们可以在完成一个工作的前提下选择购买机器。

那么这就是一个比较显然的最小割了。  
我们需要构造出一个图满足上面的三种割边方式。  
具体构造过程这里就不具体展开了，展示一下笔者构造的结果，如下：  
1. 从源点向每个工作连边，权值为这个工作的收益。
2. 从每个工作向每个工作所需机器连边，权值为租用这个机器的代价。
3. 从每个机器向汇点连边，权值为这个购买这个机器的价格。

~~感性理解~~具体分析一下就知道割去下面的边分别对应上面的选择。  
然后套一个 dinic 板子就好了，还挺清新的qwq。  

### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;const int INF=1e9;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
struct edge{int to,w,nxt;}e[5000005];
int n,m,s,t,sm,et,head[5005],cur[5005],d[5005];
inline void ADDE(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void adde(int x,int y,int w) {ADDE(x,y,w),ADDE(y,x,0);}
inline char bfs(int s,int t)
{
	queue<int>q;q.push(s),memset(d,0,sizeof(d)),d[s]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt) if(e[i].w&&!d[e[i].to]) d[e[i].to]=d[x]+1,q.push(e[i].to);
	}
	return !!d[t];
}
#define rev(x) ((((x)&1)?1:-1)+(x))
inline int dfs(int x,int t,int lim=INF)
{
	int f=lim;if(x==t) return lim;
	for(int i=cur[x];i;cur[x]=i=e[i].nxt) if(d[e[i].to]==d[x]+1&&e[i].w)
	{
		int g=dfs(e[i].to,t,min(f,e[i].w));f-=g;
		e[i].w-=g,e[rev(i)].w+=g;if(!f) break;
	}
	return lim-f;
}
inline int dinic(int s,int t) {int r=0;while(bfs(s,t)) memcpy(cur,head,sizeof(cur)),r+=dfs(s,t);return r;}
//上面全都是dinic板子，看不懂请自学网络流
int main()
{//主程序如果看不懂看上面的建图方式
	read(n),read(m),s=n+m+1,t=s+1;//源点汇点
	for(int i=1,q,c,x,y;i<=n;i++)
	{
		read(c),read(q),adde(s,i,c),sm+=c;
		while(q--) read(x),read(y),adde(i,x+n,y);
	}
	for(int i=1,w;i<=m;i++) read(w),adde(i+n,t,w);
	return printf("%d\n",sm-dinic(s,t)),0;
}
```

---

## 作者：lhm_ (赞：0)

进行分析后，发现最大收益可以转化为最小代价，那么我们就可以考虑用最小割来解决这道题。

先算出总收益$sum$，总收益减去最小代价即为答案。

然后考虑如何建图，如何建立最小割的模型。

发现一个任务最终的处理只有两种情况：

① 不完成这个任务，那么我们需要支付$val$的代价。

② 完成这个任务，若任务中某个工序用租的方式来解决，则需要支付其租金的代价，若用买的方式来解决，则需要支付其购买费用的代价，且以后可以使用这台机器。

那么最小割的模型就可以建立了。

从源点$S$向每个任务连边，容量为收益$val$，割边表示不完成这个任务。

从每个任务向其所对应的机器连边，容量为租金，割边表示租机器来完成工序。

从每个机器向汇点$T$连边，容量为购买的费用，割边表示购买机器。

边的数组记得开大，实现细节就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 3000010
#define inf 200000000
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,s,t,sum;
struct edge
{
    int to,nxt,v;
}e[maxn];
int head[maxn],edge_cnt=1;
void add(int from,int to,int val)
{
    e[++edge_cnt]=(edge){to,head[from],val};
    head[from]=edge_cnt;
    e[++edge_cnt]=(edge){from,head[to],0};
    head[to]=edge_cnt;
}
int d[maxn],cur[maxn];
bool bfs()
{
    for(int i=s;i<=t;++i) cur[i]=head[i];
    memset(d,0,sizeof(d));
    d[s]=1;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to,v=e[i].v;
            if(d[y]||!v) continue;
            d[y]=d[x]+1;
            q.push(y);
        }
    }
    return d[t];
}
int dfs(int x,int lim)
{
    if(x==t) return lim;
    int flow,res=lim;
    for(int &i=cur[x];i;i=e[i].nxt)
    {
        int y=e[i].to,v=e[i].v;
        if(d[y]!=d[x]+1||!v) continue;
        if(flow=dfs(y,min(res,v)))
        {
            res-=flow;
            e[i].v-=flow;
            e[i^1].v+=flow;
            if(!res) break;
        }
    }
    return lim-res;
}
int dinic()
{
    int ans=0,flow;
    while(bfs())
        while(flow=dfs(s,inf))
            ans+=flow;
    return ans;
}
int main()
{
    read(n),read(m),t=n+m+1;
    for(int i=1;i<=n;++i)
    {
        int val,k;
        read(val),read(k);
        sum+=val,add(s,i,val);
        for(int j=1;j<=k;++j)
        {
            int num,cost;
            read(num),read(cost);
            add(i,n+num,cost);
        }
    }
    for(int i=1;i<=m;++i)
    {
        int cost;
        read(cost);
        add(n+i,t,cost);
    }
    printf("%d",sum-dinic());
	return 0;
}
```


---

## 作者：javalyc (赞：0)

[此题博客传送门qwq](https://www.cnblogs.com/LLTYYC/p/10764319.html)

好像并不需要会最大权闭合子图也能做

答案等于总工作价值减去最小失去的价值

考虑构建最小割模型

在 $S$割 的点表示选，在 $T$割 的点表示不选

不懂 $S$割 和 $T$割 的请看[这里](https://www.cnblogs.com/LLTYYC/p/10763685.html)qwq

对于机器（编号从 $n+1$ 到 $n+m$） $n+i$，连边 $(n+i,T,cost)$ 表示选的代价

即如果此边满流表示此机器在 $S$割，表示选了，代价就是 $cost$

对于工作 $i$，连边 $(S,i,money)$ 如果此边满流表示此工作在 $T$割，失去的价值为 $money$，表示不选的代价

对于工作 $i$ 需要工序 $n+j$，连边 $(i,n+j,once)$ 表示如果选择工作 $i$（在 $S$割），不选择机器 $j$（在 $T$割），产生的代价。

因为每个机器和工作都要确定选或者不选，所以图一定要分出 $S$割 和 $T$割

那么答案就是总工作价值减最小割

如果你 $TLE$ 或者 $RE$ 了，请注意边数要开大...

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
    return x*f;
}
const int N=1e5+7,M=4e6+7,INF=1e9+7;
int fir[N],from[M],to[M],val[M],cntt=1;
inline void add(int a,int b,int c)
{
    from[++cntt]=fir[a]; fir[a]=cntt;
    to[cntt]=b; val[cntt]=c;
    from[++cntt]=fir[b]; fir[b]=cntt;
    to[cntt]=a; val[cntt]=0;
}
int dep[N],Fir[N],S,T;
queue <int> q;
bool BFS()
{
    for(int i=S;i<=T;i++) Fir[i]=fir[i],dep[i]=0;
    q.push(S); dep[S]=1; int x;
    while(!q.empty())
    {
        x=q.front(); q.pop();
        for(int i=fir[x];i;i=from[i])
        {
            int &v=to[i]; if(dep[v]||!val[i]) continue;
            dep[v]=dep[x]+1; q.push(v);
        }
    }
    return dep[T]>0;
}
int DFS(int x,int mxf)
{
    if(x==T||!mxf) return mxf;
    int fl=0,res;
    for(int &i=Fir[x];i;i=from[i])
    {
        int &v=to[i]; if(dep[v]!=dep[x]+1||!val[i]) continue;
        if( res=DFS(v,min(mxf,val[i])) )
        {
            mxf-=res; fl+=res;
            val[i]-=res; val[i^1]+=res;
            if(!mxf) break;
        }
    }
    return fl;
}
inline int Dinic() { int res=0; while(BFS()) res+=DFS(S,INF); return res; }

int n,m,ans;
int main()
{
    n=read(),m=read();
    S=0,T=n+m+1;
    int v,t,a,c;
    for(int i=1;i<=n;i++)
    {
        v=read(),t=read(); add(S,i,v); ans+=v;
        for(int j=1;j<=t;j++)
        {
            a=read(),c=read();
            add(i,n+a,c);
        }
    }
    for(int i=1;i<=m;i++) add(n+i,T,read());
    printf("%d",ans-Dinic());
    return 0;
}
```


---

## 作者：sangshang (赞：0)

# Description

有 $n$ 个工作，$m$ 个机器。每个工作有一定收入，有它所需用到的机器，和对应用到机器的租金。机器可租可买。

# Solution

工作需要机器，因此考虑最小割求解。

>源点连工作，工作连机器，机器连汇点。从源点到汇点，经过工作和机器的路径上必须割掉至少一条边。割掉源点到工作的边，表示不做工作。割掉工作到机器的边，表示租机器。割掉机器到汇点的边，表示买机器。

>考虑一开始所有工作都做，可获得 $\sum_{i=1}^{n}x_i$ 的收入，$x$ 表示工作收入。之后计算最小割，无论是放弃工作，还是花销用于机器，都将从此基础上减去。

对于每个工作，连边源点到它，容量为工作收入。

如果割掉从源点到它的边，则表示放弃那工作。此时，此工作与源点不再联通，它所连的机器也不需要考虑是否因此工作购买或租用。否则，表示做工作。此时，源点可到达此工作，需考虑是将工作到机器的边割掉，表示租用机器；还是将机器到汇点的边割掉，表示买机器。

对于每个机器，从它到汇点连边，容量是购买机器的费用。

将此边割掉表示购买机器，此时，此机器不再能到达汇点，无论有多少工作因需要与此机器相连，都无需割掉工作到机器的边。否则，机器可到达汇点，需考虑放弃工作或租用机器。

对于每个需租用此机器的工作，连边工作到机器，容量为对应租金。

若没购买机器，机器一定可到达汇点；若做工作，源点一定可到达工作。此时就必须割掉工作到机器的边，表示租用机器。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Dinic {
	public:
		typedef int TYPE;
		static const int maxn = 1205 * 2, inf = 0x7f7f7f7f, maxm = inf;
		class edge {
			public:
				int to, rev;
				TYPE flow;
				edge(int to, TYPE flow, int rev): to(to), flow(flow), rev(rev) {}
				edge() {}
		};
		vector<edge>vec[maxn];
		int h[maxn], cur[maxn], n, m, s, t;
		Dinic(int n, int m, int s, int t): n(n), m(m), s(s), t(t) {}
		Dinic() {}
		inline bool bfs() {
			int que[maxn], front = 0, back = -1;
			memset(h, inf, sizeof(h)), h[t] = 0;
			memset(cur, 0, sizeof(cur));
			for (que[++back] = t; front <= back;) {
				int u = que[front++];
				for (edge &e : vec[u]) {
					int &v = e.to;
					if (vec[v][e.rev].flow && h[v] == inf) {
						h[v] = h[u] + 1;
						que[++back] = v;
					}
				}
			}
			return h[s] != inf;
		}
		inline TYPE dfs(int u, TYPE flow) {
			if (u == t || !flow) {
				return flow;
			}
			TYPE res = 0;
			int siz = vec[u].size();
			for (int i = cur[u]; i < siz && flow; ++i) {
				cur[u] = i;
				edge &e = vec[u][i];
				int &v = e.to;
				if (e.flow && h[v] + 1 == h[u]) {
					TYPE tmp = dfs(v, min(e.flow, flow));
					flow -= tmp, res += tmp;
					e.flow -= tmp, vec[v][e.rev].flow += tmp;
				}
			}
			return (res) ? (res) : (h[u] = inf, res);
		}
		inline TYPE GetMaxFlow() {
			TYPE res = 0;
			while (bfs()) {
				TYPE tmp = 0;
				while ((tmp = dfs(s, inf))) {
					res += tmp;
				}
			}
			return res;
		}
		inline void Add_Edge(int from, int to, TYPE flow) {
			vec[from].push_back(edge(to, flow, vec[to].size()));
			vec[to].push_back(edge(from, 0, vec[from].size() - 1));
		}
		inline void Solve() {
			int N, M;
			cin >> N >> M;
			this[0] = Dinic(N + M + 5, inf, 0, N + M + 2);
			TYPE sum = 0;
			for (int i = 1; i <= N; ++i) {
				int x, t;
				cin >> x >> t;
				sum += x;
				Add_Edge(s, i, x);
				for (int j = 1; j <= t; ++j) {
					int which, cost;
					cin >> which >> cost;
					Add_Edge(i, which + N, cost);
				}
			}
			for (int i = 1; i <= M; ++i) {
				int cost;
				cin >> cost;
				Add_Edge(i + N, t, cost);
			}
			cout << sum - GetMaxFlow() << "\n";
		}
};
Dinic Main;

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	Main.Solve();
	return 0;
}
```


---

## 作者：spider_oyster (赞：0)

最小割。

定义 $(u,v,w)$ 表示连有向边 $u \rightarrow v$，边权为 $w$。

对于每个工作 $i$，连边 $(S,i,x_i)$，连边 $(i,a_{i,j},b_{i,j})$。

对于每个机器 $j$，连边 $(j,T,y_i)$。

如果割掉 $(S,i)$，代表放弃这个工作。

如果割掉 $(j,T)$，代表购买这个机器，否则不割，显然要割掉所有与 $S$ 连通的 $(i,a_{i,j})$。

可以发现是个二分图，复杂度 $O(n^2\sqrt n)$，随便跑。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2405,M=1e6+5;
int n,m,S,T,ans;
int tot=1,pre[N],lv[N],cur[N];
struct edge{int to,nxt,w;} e[M*4];
void add(int u,int v,int w)
{
    e[++tot]={v,pre[u],w},pre[u]=tot;
    e[++tot]={u,pre[v],0},pre[v]=tot;
}

int bfs()
{
    memset(lv,0,sizeof(lv));
    memcpy(cur,pre,sizeof(cur));
    queue<int> q;lv[S]=1;q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=pre[u];i;i=e[i].nxt)
        {
            int v=e[i].to,w=e[i].w;
            if(!lv[v]&&w) lv[v]=lv[u]+1,q.push(v);
        }
    }
    return lv[T];
}

int dfs(int u=S,int flow=1e10)
{
    if(u==T) return flow;
    int lev=flow;
    for(int i=cur[u];i&&lev;i=e[i].nxt)
    {
        cur[u]=i;
        int v=e[i].to,w=e[i].w;
        if(lv[v]==lv[u]+1&&w)
        {
            int out=dfs(v,min(lev,w));
            e[i].w-=out,lev-=out,e[i^1].w+=out;
        }
    }
    return flow-lev;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    S=0,T=n+m+1;
    for(int i=1;i<=n;i++)
    {
        int x,t,a,b;cin>>x>>t;
        add(S,i,x),ans+=x;
        while(t--) cin>>a>>b,add(i,a+n,b);
    }
    for(int i=1,x;i<=m;i++) cin>>x,add(i+n,T,x);
    while(bfs()) ans-=dfs();
    cout<<ans<<'\n';
}
```

---

## 作者：Lvlinxi2010 (赞：0)

先看一道最大权值闭合子图模板题：[P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)

最大权闭合子图定义：
最大权闭合子图是最小割的一个模型。即每一个子图中的每一个点，其出边的点也全应该在这个子图中。而所有子图中，其点的权值和最大就是最大权闭合子图。

最大权闭合子图建图方式：

- 从源点向每个工作连边，权值为这个工作的收入。
- 从每个工作向每个工作所需机器连边，权值为 INF。
- 从每个机器向汇点连边，权值为这个购买这个机器的费用。

那我们考虑这道题如何修改建图，这道题唯一的不同点在于**租用**操作，我们考虑将工作和工作所需机器间连的边的权值改成租用的价格，问题就愉快解决了。

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 24e2 + 20;
const int MAXM = 2e6 + 10;
const ll INF = 1e18;
int n,m,s,t,ans,cnt=1;
int vis[MAXN],head[MAXN],now[MAXN],d[MAXN];
struct edge{
	int v;
	ll w,nxt;
}e[MAXM<<1];
void add(int u,int v,int w){
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
bool bfs(){
    queue<int> q;
	q.push(s);
    memset(d,0,sizeof(d));
	d[s]=1;
    while(!q.empty()){
        int u=q.front();
		q.pop();
        for(int i=now[u]=head[u];i;i=e[i].nxt){
        	int v=e[i].v;
        	int w=e[i].w;
        	if(w&&!d[v]){
        		q.push(v);
				d[v]=d[u]+1;
			}
		}
    }
    return d[t];
}
ll dinic(int u,ll in){
    if(u==t) return in;
	ll out=0;
    for(int i=now[u];i&&in;i=e[i].nxt){
        int v=e[i].v;
		ll w=e[i].w;
		now[u]=i;
        if(d[v]==d[u]+1&&w){
            ll flow=dinic(v,min(in,w));
            in-=flow;
			out+=flow;
            e[i].w-=flow;
			e[i^1].w+=flow;
        }
    }
    if(!out) d[u]=0;
	return out;
}
int main(){
    scanf("%d%d",&n,&m);
	s=0,t=n+m+1;
    FL(i,1,n){
		int tmp,x;
        scanf("%d%d",&x,&tmp);
		ans+=x;
        add(s,i,x);
		add(i,s,0);
        FL(j,1,tmp){
            int u,v;
			scanf("%d%d",&u,&v);
            add(i,n+u,v);
			add(n+u,i,0);
        }
    }
    FL(i,1,m){
    	int x;
        scanf("%d",&x);
        add(n+i,t,x);
		add(t,n+i,0);
    }
    ll num=0;
    while(bfs()) num+=dinic(s,INF);
	printf("%lld\n",ans-num);
    return 0;
}
```

---

## 作者：Gao_yc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4177)

### 前言

此题是一道很显然的最小割题目，但是这题对最大流模板卡的比较严，有一些不够优秀的模板会 **TLE**（调了4个多小时的痛）。但是从另一个角度看，调模板未必不是一件好事（至少我调完之后不可能会再次出问题了）。因此，本题只给**建图**部分的代码。



------------


### $ \mathcal{Solution} $：

看到题目，肯定会先想到直接跑最大流，但是那样的话我们无法判断此工序需要的所有机器是否齐全，而且边权为负也会出现问题。

所以我们换个思路，先假设所有的工作都做。

首先看工作，由源点向每个工作连边权为工作收入的边。割掉表示放弃此工作。

而机器，由每个机器向汇点连边权为**购买**费用的边，割掉表示**购买**此机器。

每个工作向其需要的机器连边权为**租用**费用的边，割掉表示做此工作时**租用**这个机器。

在这样建出的图上跑最小割，总收益减去最小割即为答案。

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=3e6;
int n,m,s,t;
int tot=1,head[3000],now[3000],ver[N],nxt[N],edge[N],ans;
void add(int u,int v,int w)
{
	ver[++tot]=v,edge[tot]=w,nxt[tot]=head[u],head[u]=tot;
	ver[++tot]=u,edge[tot]=0,nxt[tot]=head[v],head[v]=tot;
}
```
 
网络流部分代码省略。

```cpp
int main()
{
//	freopen("","r",stdin);
//	freopen("","w",stdout);
	scanf("%d%d",&n,&m);
	s=n+m+1,t=s+1;
	int x,tt,a,b,y;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&tt);
		add(s,i,x);
		ans+=x;
		for(int j=1;j<=tt;++j)
		{
			scanf("%d%d",&a,&b);
			add(i,a+n,b);
		}
	}
	for(int i=1;i<=m;++i) {scanf("%d",&y);add(i+n,t,y);}
	int flow=0;
	while(bfs())
	while(flow=dinic(s,N)) ans-=flow;
	printf("%d",ans);
   	return 0;
}
```


如果对我的算法有疑问，欢迎在评论区中评论。

---

## 作者：chenxia25 (赞：0)

一个奇怪的做法，就当练习一下优化网络流建图的技术罢。

首先发现 $b_{i,j}=+\infty$​ 的情况就是个裸的最大权闭合子图，所以原题不弱于最大权闭合子图，那基本上就可以确定是最大权闭合子图。$b_{i,j}<+\infty$​ 的情况怎么破呢？一个容易想到的想法是：先钦定所有工作全部租用机器，然后考虑进行一些买的操作，每次买可以减少一些代价。具体地：机器 $(i,j)$ 采用购买的方式，可以带来 $b_{i,j}$ 的收益，但同时要求工作 $i$ 和机器 $a_{i,j}$ 被选（机器 $x$ 被选的收益是 $-y_x$）。我们对每个 $(i,j)$ 都新建一个点，「同时要求 xx 和 xxx 被选」显然是可以最大权闭合子图表达出来的。

不过这样有 $\mathrm O(nm)$ 个点，1e6 跑个锤锤棒棒锤的网络流？考虑优化建图。考虑固定住当前 $i$，那么连边的画风其实是这样的：对每个 $(i,j)$，都有 $S\to (i,j)$ 边权为 $b_{i,j}$，$(i,j)\to i$ 边权为 $+\infty$，$(i,j)\to a_{i,j}$ 边权为 $+\infty$。现在只要把所有的 $j$ 全部压成一个点，总点数就是 $\mathrm O(n+m)$ 了。我们注意到：对于每个 $(i,j)$，它存在的意义相当于给 $i$ 和 $a_{i,j}$ 最多共 $b_{i,j}$ 的流量，而前者 $i$ 是固定的。我们考虑：先把不超过 $b_{i,j}$ 的流量分别分发给 $a_{i,j}$，然后把剩下来的一股脑给 $i$（利用了 $i$​ 固定这一性质）。这样显然就可以把 $j$ 们对应的 $(i,j)$ 缩起来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=5e3+10;
int n,m,s,t;
vector<pair<int,int> > nei[N+1];
vector<int> rv[N+1];
void ae(int x,int y,int z){
	nei[x].pb(mp(y,z)),nei[y].pb(mp(x,0));
	rv[x].pb(nei[y].size()-1),rv[y].pb(nei[x].size()-1);
}
int dep[N+1];
bool bfs(){
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X,c=nei[x][i].Y;
			if(c&&!~dep[y])dep[y]=dep[x]+1,q.push(y);
		}
	}
	return ~dep[t];
}
int now[N+1];
int dfs(int x=s,int flw=inf){
	if(x==t||!flw)return flw;
	int res=0,tmp;
	for(int &i=now[x];i<nei[x].size();i++){
		int y=nei[x][i].X,&c=nei[x][i].Y;
		if(dep[y]==dep[x]+1&&(tmp=dfs(y,min(flw,c)))){
			res+=tmp,flw-=tmp;
			c-=tmp,nei[y][rv[x][i]].Y+=tmp;
			if(!flw)break;
		}
	}
	return res;
}
int dinic(){
	int res=0;
	while(bfs()){
		memset(now,0,sizeof(now));
		res+=dfs();
	}
	return res;
}
int c1[N];
int noww,tot;
void add_node(int x,int v){
	if(v>=0)tot+=v,ae(s,x,v);
	else ae(x,t,-v);
}
signed main(){
	cin>>n>>m;
	s=1,t=2,noww=n+m+2;	
	for(int i=1;i<=n;i++){
		int x,t;
		cin>>x>>t;
		c1[i]=x;
		noww++,ae(noww,i+2,inf);
		int sum=0;
		while(t--){
			int a,b;
			scanf("%lld%lld",&a,&b);
			c1[i]-=b;
			tot+=b;
			sum+=b;
			ae(noww,a+n+2,b);
		}
		ae(s,noww,sum);
	}
	for(int i=1;i<=n;i++)add_node(i+2,c1[i]);
	for(int i=1;i<=m;i++){
		int v;
		cin>>v;
		add_node(i+n+2,-v);
	}
	cout<<tot-dinic();
	return 0;
}
```

---

## 作者：When (赞：0)

#### 算法

最大权闭合子图

#### 思路

首先，如果没有租借这个条件，就是一个最大权闭合子图的模板了，让我们背诵最大权闭合子图的建图方法：

> 1. 将源点与正权点连边，流量为权值；
> 2. 将负权点与汇点连边，流量为权值相反数（正数）；
> 3. 将原图中的边相连，流量为正无穷。
> 4. 最大权闭合子图$ =$ 原图正权点权值和$ -$ 最小割

##### 思考：我们为什么要把原图中的边设为正无穷？

$A:$将某点与源点的边割去表示将其划分在不选集合中，将与汇点的边割去表示在选择集合中，而原图中的边是不能割掉的，所以设为正无穷，这样我们再求最小割的时候就不会把ta割掉了。

那么，我们如何解救这道题呢？

想一想租借这个条件为什么会使原本的算法错误，因为有可能租借某个机器来满足工作需求比购买ta更划算，而租借机器是对其他的工作没有影响的。所以，我们可以把工作与机器之间的边的流量设成租借费用，这样就可以通过割掉租借边来把某个工作划分到选择集合中而不影响其他的工作。

#### 参考代码

```cpp
/*
 * @Author: When_C 
 * @Date: 2020-11-23 17:34:21 
 * @Last Modified by: When_C
 * @Last Modified time: 2020-11-23 18:35:43
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

const int maxm = 3e6 + 10,maxn = 1e5 + 10;
int n,m,head[maxn],num,S,T,Ans;
struct Edge{
    int then,to,val;
}e[maxm];

void add(int u, int v, int val){
    e[++num] = (Edge){head[u], v, val}; head[u] = num;
    e[++num] = (Edge){head[v], u, 0}; head[v] = num;
}

int vis[maxn],dep[maxn];
int bfs(int st, int en){
    memset(vis,0,sizeof(vis));
    for(int i = 1; i <= n + m + 2; ++ i) dep[i] = INF;
    queue<int> q;
    vis[st] = 1, dep[st] = 1, q.push(st);
    while(!q.empty()){
        int u = q.front();
        vis[u] = 0, q.pop();
        for(int i = head[u]; i; i = e[i].then){
            int v = e[i].to;
            if(dep[v] == INF && e[i].val){
                dep[v] = dep[u] + 1;
                if(!vis[v]){vis[v] = 1; q.push(v);}
            }
        }
    }
    return (dep[en] != INF);
}

int cur[maxn];
int dfs(int u, int sum){
    if(u == T) return sum;
    int now = 0;
    for(int &i = cur[u]; i; i = e[i].then){
        int v = e[i].to;
        if(dep[v] == dep[u] + 1 && e[i].val){
            int a = dfs(v, min(e[i].val, sum - now));
            now += a;
            e[i].val -= a, e[i ^ 1].val += a;
            if(now == sum) return now;
        }
    }
    return now;
}

int dinic(){
    int maxflow = 0;
    while(bfs(S, T)){
        memcpy(cur,head,sizeof(head));
        maxflow += dfs(S, INF);
    }
    return maxflow;
}

int main(){
    scanf("%d%d", &n, &m);
    num = 1, S = n + m + 1; T = S + 1;
    for(int i = 1; i <= n; ++ i){
        int x,t; scanf("%d%d", &x, &t);
        add(S, i, x); Ans += x;
        while(t--){
            int a,b; scanf("%d%d", &a, &b);
            add(i, a + n, b);
        }
    }
    for(int i = 1; i <= m; ++ i){
        int y; scanf("%d", &y);
        add(i + n, T, y);
    }
    printf("%d\n", Ans - dinic());
    return 0;
}
```



---

