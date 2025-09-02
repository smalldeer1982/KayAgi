# [BalticOI 2008] 黑手党

## 题目描述

Byteland 国警方收到了一条匿名举报，其中说当地黑帮老大正计划一次从港口到郊区仓库的运输。警方知道运输的时间并且知道运输需要用到国家的高速公路网。

高速公路网包含双向的高速公路段，每个路段直接连着两个不同的收费站。一个收费站可能与很多其他的收费站相连。汽车只能通过收费站进入或离开高速公路网。据所知，黑帮会距港口边最近的收费站进入高速公路，从距仓库最近的收费站离开（不会在出高速后重新进入）。特警组位于选定的收费站处。当运输车辆进入被监控的收费站时，它就会被警察抓住。

从这个角度看，最简单的办法就是在每个收费站处都安排特警班。然而，控制一个收费站需要特定的费用，每个收费站费用不同。警方想要让花费最小，所以他们需要制定一个收费站的最小控制集，这个集合满足两个条件：

-    所有从港口到仓库的交通必须至少经过集合中的一个收费站
-    监控这些收费站的费用（即监控每一个收费站费用之和）最小

你可以假设使用高速公路可以从港口到仓库。

#任务

写一个程序能够：

-    从标准输入中读取高速公路网，监控代价和运输的起点和终点
-    找到收费站的最小控制集
-    输出这个集合到标准输出


## 说明/提示

**样例解释**

![0](https://i.loli.net/2018/02/19/5a8af2c2ef8d7.gif)

这张图片显示了高速公路网中收费站的编号（在左上角）和控制费用。$1$ 号和 $4$ 号收费站组成了最小控制集，总控制费用为 $5$。

**数据范围**

对于 $40\%$ 的测试数据，$n\le 20$；

对于全部数据，$1\le n\le 200,1\le m \le 2\times 10^4$​​，$1 \le a,b \le n,a≠b$，$1\le c\le 10^7$​​，$1\le x<y\le n$。

## 样例 #1

### 输入

```
5 6
5 3
2
4
8
3
10
1 5
1 2
2 4
4 5
2 3
3 4```

### 输出

```
1 4```

# 题解

## 作者：Siyuan (赞：8)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Luogu 4662](https://www.luogu.org/problemnew/show/P4662)

Byteland 国警方收到了一条匿名举报，其中说当地黑帮老大正计划一次从港口到郊区仓库的运输。警方知道运输的时间并且知道运输需要用到国家的高速公路网。

高速公路网包含 $n$ 个收费站和 $m$ 条双向的高速公路，每个路段直接连着两个不同的收费站。一个收费站可能与很多其他的收费站相连。汽车只能通过收费站进入或离开高速公路网。据所知，黑帮会距港口边最近的收费站进入高速公路，从距仓库最近的收费站离开（不会在出高速后重新进入）。特警组位于选定的收费站处。当运输车辆进入被监控的收费站时，它就会被警察抓住。

从这个角度看，最简单的办法就是在每个收费站处都安排特警班。然而，控制第 $i$ 个收费站需要特定的费用 $c_i$，每个收费站费用不同。警方想要让花费最小，所以他们需要制定一个收费站的最小控制集，这个集合满足两个条件：

- 所有从港口到仓库的交通必须至少经过集合中的一个收费站。
- 监控这些收费站的费用（即监控每一个收费站费用之和）最小。
- 你可以假设使用高速公路可以从港口到仓库。

你需要找到收费站的最小控制集。

数据范围：$1\le n\le 200$，$1\le m\le 2\times 10^4$，$1\le c_i\le 10^7$

------

## Solution

我们需要将一些收费站安排特警班，使得源点和汇点不连通，于是这个问题就是最小割问题。

我们考虑如何将割点转化成割边。由于每个点只能被割一次，我们首先需要拆点：将点 $i$ 拆成 $i_1$ 和 $i_2$ 两个点，其中 $i_1$ 和 $i_2$ 之间连容量为**代价**（本题中代价为 $1$）的边。对于对于一条边 $(u,v)$，也就转化为 $(u_2,v_1,\texttt{INF})$ 和 $(v_2,u_1,0)$，其中容量为 $\texttt{INF}$ 使得这条边不可能被割掉，即割掉的边一定为 $(i_1,i_2)$ 这样的边。

由于源点和汇点也可以被割，所以源点转化为 $s_1$，汇点转化为 $t_2$。

最后我们证明一下**正确性**。此时，整张图的形态没有改变，每个点只能被割一次对应着每条边 $(i_1,i_2)$ 只能被割一次，正确性得证。

对于控制集，我们从源点 $s_1$ 出发沿着残量大于 $0$ 的边开始 $\texttt{DFS}$，将所有访问的点打标记。对于一条正向边 $(u,v)$，如果 $u$ 被打了标记而 $v$ 没有被打标记，那么就意味着这条边所代表的点被割掉了。

**时间复杂度**：$O(n^2m)$

------

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

const int N=4e2+5,M=1e5+5;
const int INF=1<<30;
int n,m,tot=1,lnk[N],ter[M],nxt[M],val[M],dep[N],cnr[N];
bool vis[N];

void add(int u,int v,int w) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void addedge(int u,int v,int w) {
    add(u,v,w),add(v,u,0);
}
int bfs(int s,int t) {
    memset(dep,0,sizeof(dep));
    memcpy(cnr,lnk,sizeof(lnk));
    std::queue<int> q;
    q.push(s),dep[s]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int i=lnk[u];i;i=nxt[i]) {
            int v=ter[i];
            if(val[i]&&!dep[v]) q.push(v),dep[v]=dep[u]+1;
        }
    }
    return dep[t];
}
int dfs(int u,int t,int flow) {
    if(u==t) return flow;
    int ans=0;
    for(int i=cnr[u];i&&ans<flow;i=nxt[i]) {
        cnr[u]=i;
        int v=ter[i];
        if(val[i]&&dep[v]==dep[u]+1) {
            int x=dfs(v,t,std::min(val[i],flow-ans));
            if(x) val[i]-=x,val[i^1]+=x,ans+=x;
        }
    }
    if(ans<flow) dep[u]=-1;
    return ans;
}
void dinic(int s,int t) {
    while(bfs(s,t)) while(dfs(s,t,INF));
}
void dfs(int u) {
    vis[u]=1;
    for(int i=lnk[u];i;i=nxt[i]) if(val[i]&&!vis[ter[i]]) dfs(ter[i]);
}
int main() {
    int s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=n;++i) {
        int x;
        scanf("%d",&x);
        addedge(i,i+n,x);
    }
    while(m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u+n,v,INF),addedge(v+n,u,INF);
    }
    dinic(s,t+n);
    dfs(s);
    std::vector<int> ans;
    for(int i=2;i<=tot;i+=2) {
        int u=ter[i^1],v=ter[i];
        if(vis[u]&&!vis[v]) ans.push_back(u);
    }
    std::sort(ans.begin(),ans.end());
    for(int sz=(int)ans.size()-1,i=0;i<=sz;++i) {
        printf("%d%c",ans[i]," \n"[i==sz]);
    }
    return 0;
}
```



---

## 作者：AubRain (赞：4)

这道题就是一个裸的最小割啊。。

把一个点拆成入点 $(x)$ 和出点 $(x+n)$，然后之间连一条边，流量为收费站的费用。

然后如果这条边被割了，就说明这个收费站被监视了。

**问题在于输出方案：**

不知道为什么另一篇题解要重新跑好多遍 $dinic$ ，直接在残量网络上 $dfs$ 一遍就好了。

$dfs$ 的时候只走还有流量剩余的边，然后如果一个点的入点被访问到了，但出点没有被访问到，就说明这个点被监视了。最后排个序输出就行了。

$100+ms$，用的 $dinic$ 算法，目前最优解前三

```cpp
#include<bits/stdc++.h>
#define N 100005
#define INF 1<<29
using namespace std;

inline void rd(int &X){
    X=0;int w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while(isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    X=w?-X:X;
}

vector<int> ans;
int n,m,s,t,f,k;
int head[N],cnt=1,d[N],v[N];
struct nd{int nxt,to,v;}e[N<<1];
#define For(x) for(int y,i=head[x];(y=e[i].to);i=e[i].nxt)

void add(int x,int y,int w){
    e[++cnt]=(nd){head[x],y,w};head[x]=cnt;
    e[++cnt]=(nd){head[y],x,0};head[y]=cnt;
}
bool bfs()
{
    queue<int> q; q.push(s);
    memset(d,0,sizeof d); d[s]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        For(x) if(e[i].v&&!d[y]){
            q.push(y); d[y]=d[x]+1;
            if(y==t) return 1;
        }
    } return 0;
}

int dinic(int x,int flow)
{
    if(x==t) return flow; int re=flow;
    for(int y,i=head[x];(y=e[i].to)&&re;i=e[i].nxt)
        if(e[i].v&&d[y]==d[x]+1)
        {
            int k=dinic(y,min(re,e[i].v));
            if(!k) d[y]=0;
            e[i].v-=k;e[i^1].v+=k;re-=k; 
        }
    return flow-re;
}
void build()
{
	rd(n);rd(m);rd(s);rd(t);t+=n;
	for(int x,i=1;i<=n;i++)
		rd(x),add(i,i+n,x);
	for(int x,y,i=1;i<=m;i++)
		rd(x),rd(y),add(x+n,y,INF),add(y+n,x,INF);
}
void dfs(int x){
	v[x]=1;
	For(x) if(e[i].v>0 and !v[y])
		dfs(y);
}
void print()
{
	dfs(s);
	for(int i=2;i<cnt;i+=2)
		if(v[e[i^1].to] and !v[e[i].to])
			ans.push_back(e[i^1].to);
	sort(ans.begin(),ans.end());
	for(int x:ans) printf("%d ",x);
}
int main()
{
   	build();
    while(bfs())
        while(f=dinic(s,INF));
   	print();
}
```

---

## 作者：Coffee_zzz (赞：2)

比较经典的题目。

### 分析

我们的目的是让 $a$ 点和 $b$ 点不连通，容易想到最小割。

考虑一下怎么建模。

我们令 $inf$ 表示一个极大值。

- 对于给定的公路，我们不能破坏，所以割掉给定的公路的费用为 $inf$。

- 对于给定的收费站，我们可以破坏，但是删掉一个点是最小割无法做到的。我们需要把收费站 $u$ 拆成两个点 $u$ 和 $u+n$，再从 $u$ 向 $u+n$ 连一条割掉费用为 $c_u$ 的边。其中，$u+n$ 可以替换成其他值，保证不会出现两个点的下标相同的情况即可。

这样的话，最小割一定不会割掉费用为 $inf$ 的边，只会割掉我们拆点之后加的边，这样就实现了删点的操作。

这时我们要注意，因为我们把一个收费站拆成了两个点，所以我们在连公路时需要注意，是由 $x+n$ 向 $y$ 连边而非由 $x$ 向 $y$ 连边，同时，汇点也从 $b$ 变成了 $b+n$。

接下来我们用 dinic 算法跑出最大流，在残余网络上求方案。

我们从源点开始搜索所有可以到达的点，给可以到达的点打标记。对于任意一对点 $u$ 和 $u+n$，如果 $u$ 被打上了标记而 $u+n$ 没有，说明 $u$ 和 $u+n$ 之间的边被割掉了，也就说明这个点被删掉了。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005,M=1e5+5,inf=1e18;
int n,m,s,t,to[M],nxt[M],cap[M],flow[M],head[N],cur[N],dep[N],cnt=1,mf,c[N];
bool vis[N];
queue <int> q;
void add(int u,int v,int w){
	cnt++;
	to[cnt]=v;
	nxt[cnt]=head[u];
	cap[cnt]=w;
	head[u]=cnt;
}
bool bfs(){
	int u,v;
	memset(dep,0,sizeof dep);
	while(!q.empty()) q.pop();
	dep[s]=1;
	q.push(s);
	while(!q.empty()){
		u=q.front(),q.pop();
		for(int i=head[u];i;i=nxt[i]){
			v=to[i];
			if(!dep[v]&&cap[i]>flow[i]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t];
}
int dfs(int u,int f){
	if(u==t||!f) return f;
	int ret=0,v,d;
	for(int &i=cur[u];i;i=nxt[i]){
		v=to[i];
		if(dep[u]+1!=dep[v]) continue;
		d=dfs(v,min(f-ret,cap[i]-flow[i]));
		ret=ret+d;
		flow[i]=flow[i]+d;
		flow[i^1]=flow[i^1]-d;
		if(ret==f) return ret;
	}
	return ret;
}
void dinic(){
	while(bfs()){
		memcpy(cur,head,sizeof cur);
		mf=mf+dfs(s,inf);
	}
}
void qwq(int u){
	int v;
	for(int i=head[u];i;i=nxt[i]){
		v=to[i];
		if(!vis[v]&&cap[i]>flow[i]) vis[v]=1,qwq(v);
	}
}
signed main(){
	int u,v;
	cin>>n>>m>>s>>t;t=t+n;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) add(i,i+n,c[i]),add(i+n,i,0);
	for(int i=1;i<=m;i++) cin>>u>>v,add(u+n,v,inf),add(v,u+n,0),add(v+n,u,inf),add(u,v+n,0);
	dinic();
	vis[s]=1,qwq(s);
	for(int i=1;i<=n;i++) if(vis[i]^vis[i+n]) cout<<i<<' ';
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# P4662 [BalticOI 2008] 黑手党 题解

### 解析

一眼网络流。

考虑经典建图套路：因为本题里要割的是点，所以考虑把**一个点 $i$ 拆成两个点 $i$ 和 $i+n$**，中间**由一条边连接**，边权为 $c_i$。对于输入的点对，同样将其本身和拆出的点连边，然后跑最小割即可。

根据“最小割=最大流”，于是我们直接跑最大流即可。

最后对于每一条 $i\leftrightarrow i+n$ 的边，如果没有流量，证明其需要被割掉，于是输出这些 $i$ 即可。

### 代码

（含详细注释+坑点）

[网络流模板（含注释）](https://www.luogu.com.cn/article/7l496152)。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,inf=2e9;
int n,m,s,t,c;
int u,v;
struct Edge{
	int to,nxt,value;
}edges[N];
int head[N],cnt=1;
int cur[N],dep[N];
bool vis[N];
void add(int u,int v,int w){ 
	edges[++cnt]={v,head[u],w};
	head[u]=cnt;
}
bool bfs(){
	memcpy(cur,head,sizeof cur);
	for(int i=1;i<=2*n;i++){ //注意这里要开到 2*n，因为一个点拆成了两个点 
		dep[i]=inf;
	}
	dep[s]=1;
	queue<int>Q;
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front(); Q.pop();
		for(int i=head[u];i;i=edges[i].nxt){
			int v=edges[i].to;
			if(dep[v]>dep[u]+1&&edges[i].value){
				dep[v]=dep[u]+1; Q.push(v);
			}
		}
	}
return dep[t]!=inf;
}
int dfs(int u,int flow){
	if(u==t){
		return flow;
	}
	int used=0;
	for(int i=cur[u];i;i=edges[i].nxt){
		cur[u]=i;
		int v=edges[i].to;
		if(dep[v]==dep[u]+1&&edges[i].value){
			int rflow=dfs(v,min(edges[i].value,flow-used));
			if(rflow){
				used+=rflow;
				edges[i].value-=rflow;
				edges[i^1].value+=rflow;
				if(flow==used){
					return used;
				}
			}
		}
	}
return used;
}
void dinic(){
	while(bfs()){
		dfs(s,inf);
	}
}
void bl(int u){ //不要写成 dfs，上面的函数用过 dfs 了 
	vis[u]=1;
	for(int i=head[u];i;i=edges[i].nxt){
		int v=edges[i].to;
		if(vis[v]==0&&edges[i].value){ //如果残量网络中还有余流则继续遍历 
			bl(v);
		}
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>s>>t;
	t+=n;
	for(int i=1;i<=n;i++){
		cin>>c;
		add(i,i+n,c);
		add(i+n,i,0);
	}
	while(m--){
		cin>>u>>v;
		add(u+n,v,inf);
		add(v,u+n,0);
		add(v+n,u,inf);
		add(u,v+n,0);
	}
	dinic();
	bl(s);
	for(int i=1;i<=n;i++){
		if(vis[i]^vis[i+n]){ //如果一边走过一边没有走过说明没有余流，需要割掉 
			cout<<i<<" ";
		}
	}
return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：1)

### Problem

有 $n$ 个收费站和 $m$ 条高速公路，黑帮会从第 $s$ 个收费站进入高速公路，从 $t$ 个收费站离开。警方监控一个收费站的费用是 $1$，求最少需要多少费用使黑帮被完全控制，输出任意一个控制方案。

### Solve

第一道紫题的题解 QwQ

双倍经验：[P1345 奶牛的电信](https://www.luogu.com.cn/problem/P1345)

就是求一个网络流的最小割。

但是题目中说的是割点，而不是割边，我们要把它转化成割点。

怎么转化呢？

考虑把一个点拆成 点—边—点 的形式。

即对于一个点 $u$，我们把它拆成 $u_1=u,u_2=u+n$，$u_1$ 负责入，$u_2$ 负责出，连接一条 $u_1\to u_2$ 的有向边，权值为 $1$，即割掉这条边（也就是原来的点 $u$）的费用为 $1$；

而对于输入的 $m$ 条无向边 $a\leftrightarrow b$，它们的作用就是用来连接点，也就是把 $a,b$ 两点首尾相连，即连接 $a_2\to b_1$，$b_2\to a_1$，但是我们不能让这两条边被割掉，要把它们的权值设为 $\texttt{INF}$。

因为最大流 = 最小割，我们只需要用 Dinic 跑一遍 $s_1$ 到 $t_2$ 的最大流，就可以求出最小的费用。

但是还没有做完，题目要求输出一个可行方案，我们可以从源点 $s_1$ 对残量大于 $0$ 的边 dfs，然后遍历所有的边，对于一条边 $u_1\to u_2$，如果在刚才的 dfs 过程中访问到了 $u_1$ 而没有访问到 $u_2$，就说明 $u$ 点被割掉了。

最后别忘了把答案的集合排序后再输出。


### Code

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 100010
#define MAXM 100010
#define int long long
const int INF = 1e18;
int head[MAXN], cnt = 1;
struct edge {
	int v, w, nxt;
	edge() {}
	edge(int vv, int ww, int nn) {
		v = vv, w = ww, nxt = nn;
	}
} e[MAXM];
void add_edge(int u, int v, int w) {
	e[++cnt] = edge(v, w, head[u]);
	head[u] = cnt; 
}
void addedge(int u, int v, int w) {
	add_edge(u, v, w);
	add_edge(v, u, 0);
}
int n, m, s, t;
int dep[MAXN];
bool book[MAXN];
bool bfs() {
	memset(dep, 0, sizeof dep);
	dep[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w;
			if (w && !dep[v]) {
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return dep[t];
}
int dfs(int u, int in) {
	if (u == t) return in;
	if (dep[u] > dep[t]) return 0;
	if (in <= 0) return 0;
	int out = 0;
	for (int i = head[u]; i && in; i = e[i].nxt) {
		int v = e[i].v;
		if (e[i].w && dep[v] == dep[u] + 1) {
			int res = dfs(v, min(e[i].w, in));
			e[i].w -= res;
			e[i ^ 1].w += res;
			in -= res;
			out += res;
		}
	}
	if (out == 0)
		dep[u] = 0;
	return out;
}
int Dinic() {
	int ans = 0;
	while (bfs()) 
		ans += dfs(s, INF);
	return ans;
}
bool vis[MAXN];
void ddfs(int u) {
	vis[u] = true;
	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].w && !vis[e[i].v])
			ddfs(e[i].v);
}
int ans[MAXN], cntt;
signed main() {
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= n; i++) {
		int c; cin >> c;
		addedge(i, i + n, c);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addedge(u + n, v, INF);
		addedge(v + n, u, INF); 
	}
	t += n;
	Dinic();
	ddfs(s);
	for (int i = 2; i <= cnt; i += 2)
		if (vis[e[i ^ 1].v] && !vis[e[i].v])
			ans[++cntt] = e[i ^ 1].v;
	sort(ans + 1, ans + cntt + 1);
	for (int i = 1; i <= cntt; i++)
		cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：2018LZY (赞：1)

>题意:镇守每个点都需要一定的代价.现在需要选择最少代价的镇守方法使得$st\rightarrow ed$的每一条路径都有点被选择.

由于是点有限制,所以我们考虑拆点——每个点转换为入点、出点，然后之间连容量等于代价的边。原图的边转化为出点和入点之间容量为$INF$的边即可.

然后这就很明显是最小割的模型了——用最少的代价割这个网络。

所以问题就其实就是找割边。

跑一遍最大流,再从起点出发遍历残余网络,设遍历到的点集为$S$,其他部分为$T$,则$S\rightarrow T$的边是割边.

$Isap$做法(最后$bfs/dfs$判断联通性):
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar()
using namespace std;
const int N = 520, M = 1e5 + 10, inf = 1 << 30;

void qr(int &x) {
    x = 0;
    char c = gc;
    while (!isdigit(c)) c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
}

int n, m, d[N], q[N], st, ed, c[N], ans, l, r;
struct edge {
    int y, next, c;
} a[M];
int len = 1, last[N], cur[N];
void ins(int x, int y, int c) {
    a[++len] = (edge){ y, last[x], c };
    last[x] = len;
}
void add(int x, int y, int c) {
    ins(x, y, c);
    ins(y, x, 0);
}

void bfs() {
    q[l = r = 1] = ed;
    ++c[d[ed] = 1];
    for (int i = 1; i <= 2 * n; i++) cur[i] = last[i];
    while (l <= r) {
        int x = q[l++];
        for (int k = last[x], y; k; k = a[k].next)
            if (!d[y = a[k].y]) {
                ++c[d[y] = d[x] + 1];
                q[++r] = y;
            }
    }
}

int dfs(int x, int f) {
    if (x == ed)
        return f;
    int s = 0, t;
    for (int &k = cur[x], y, z; k; k = a[k].next) {
        y = a[k].y;
        z = a[k].c;
        if (z && d[y] + 1 == d[x]) {
            s += t = dfs(y, min(f - s, z));
            a[k].c -= t;
            a[k ^ 1].c += t;
            if (s == f)
                return f;
        }
    }
    if (!--c[d[x]])
        d[st] = 2 * n + 1;
    ++c[++d[x]];
    cur[x] = last[x];
    return s;
}

void BFS() {
    q[l = r = 1] = st;
    memset(d + 1, 0, n << 3);
    d[st] = 1;
    for (int x = st; l <= r; x = q[++l])
        for (int k = last[x], y; k; k = a[k].next)
            if (!d[y = a[k].y] && a[k].c)
                d[y] = 1, q[++r] = y;
}

int main() {
    qr(n);
    qr(m);
    qr(st);
    qr(ed);
    ed += n;
    for (int i = 1, x; i <= n; i++) qr(x), add(i, i + n, x);
    for (int i = 1, x, y; i <= m; i++) qr(x), qr(y), add(x + n, y, inf), add(y + n, x, inf);
    bfs();
    while (d[st] <= 2 * n) ans += dfs(st, inf);
    BFS();
    for (int i = 1; i <= n; i++)
        if (d[i] && !d[i + n])
            printf("%d ", i);
    return 0;
}
```
当然如果我们用$dicnic$的话直接利用最后一次的$bfs$就不用另外的$dfs/bfs$求割边了.

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 422, M = 1e5 + 10, inf = 1 << 30;

void qr(int &x) { scanf("%d", &x); }

int n, m, d[N], q[N], l, r, ans, st, ed;
struct edge {
    int y, next, c;
} a[M];
int len = 1, last[N], cur[N];
void ins(int x, int y, int c) {
    a[++len] = (edge){ y, last[x], c };
    last[x] = len;
}
void add(int x, int y, int c) {
    ins(x, y, c);
    ins(y, x, 0);
}

bool bfs() {
    q[l = r = 1] = st;
    memset(d, 0, sizeof d);
    d[st] = 1;
    for (int x = st; l <= r; x = q[++l])
        for (int k = last[x], y; k; k = a[k].next)
            if (a[k].c && !d[y = a[k].y])
                d[y] = d[x] + 1, q[++r] = y;
    return d[ed];
}

int dfs(int x, int f) {
    if (x == ed)
        return f;
    int s = 0, t;
    for (int &k = cur[x], y, z; k; k = a[k].next) {
        y = a[k].y;
        z = a[k].c;
        if (z && d[y] == d[x] + 1) {
            s += t = dfs(y, min(f - s, z));
            a[k].c -= t;
            a[k ^ 1].c += t;
            if (s == f)
                return f;
        }
    }
    if (!s)
        d[x] = 0;
    return s;
}

int main() {
    qr(n);
    qr(m);
    qr(st);
    qr(ed);
    ed += n;
    for (int i = 1, x; i <= n; i++) qr(x), add(i, i + n, x);
    for (int i = 1, x, y; i <= m; i++) qr(x), qr(y), add(x + n, y, inf), add(y + n, x, inf);
    while (bfs()) memcpy(cur + 1, last + 1, n << 3), ans += dfs(st, inf);
    for (int i = 1; i <= n; i++)
        if (d[i] && !d[i + n])
            printf("%d ", i);
    return 0;
}
```
PS:这个代码在$loj$暂时跑到$rk 1$.

---

## 作者：okbj (赞：1)

```
给定一张无向图，其中节点有限制，
求出最小割点集，
按照字典序输出割点。
网络流的基础是边限制，
所以我们将一个点i拆为i‘和i’‘，
并且连接i’至i‘’，
容量为点限制。
对于原图中存在的边（i，j），
我们将i‘’连向j‘，容量为inf。
我们很容易就可以通过从源点到汇点的最大流求出最小割，
也就是要取出的点的最小代价。
但是题目的要求是按字典序输出点的编号，
那么我们就不能用dfs的方式来求出割点集。
所以我们将原图拷贝后，
依次枚举断边e。
如果断边后的最大流，
设为G’，
和原来最大流G的差值恰好为该边的容量，
那么e必为原图中的最小割。
```
```
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int N,M,n;
int st,ed;
int a[205];
struct Pipe{int next,to,flow,f;}pipe[500005];//通过f标记表示该边是否存在 
Pipe tg[500005],ttg[500005];
int h[2005],cnt=1;
inline void add(int x,int y,int z){
	pipe[++cnt].to=y;pipe[cnt].next=h[x];h[x]=cnt;pipe[cnt].flow=z;pipe[cnt].f=1;
	pipe[++cnt].to=x;pipe[cnt].next=h[y];h[y]=cnt;pipe[cnt].flow=0;pipe[cnt].f=1;//双向加边，并且打上标记
        return;
}
inline int read(){
	char c;int rec=0;
	while((c=getchar())<'0'||c>'9');
	while(c>='0'&&c<='9')rec=rec*10+c-'0',c=getchar();
	return rec;
}
int Gap[5005],dis[5005];
int ans=0,sum;
inline int SAP(int v,int maxflow){
	if(v==ed+N)return maxflow;
	int temp=maxflow,i,j,p;
	for(i=h[v];i;i=pipe[i].next){
		if(pipe[i].f==0)continue;//已删除的边就不再考虑 
		j=pipe[i].to;
		if(pipe[i].flow&&dis[v]==dis[j]+1){
			p=SAP(j,min(pipe[i].flow,temp));
			temp-=p;pipe[i].flow-=p;pipe[i^1].flow+=p;
			if(dis[st]==n||temp==0)return maxflow-temp;
		}
	}
	if(--Gap[dis[v]]==0)dis[st]=n;
	else Gap[++dis[v]]++;
	return maxflow-temp;
}
inline void GET(){
	memset(Gap,0,sizeof(Gap));
	memset(dis,0,sizeof(dis));
	Gap[0]=n;sum=0;
	while(dis[st]<n)sum+=SAP(st,inf);//得出当前网络中的最大流 
	return ;
}
void Solve(){
        int i,j,k;
	ans=sum;
	for(i=1;i<=N;i++){//只考虑删除点限度的边，而非原有的容量为inf的边 
		if(pipe[i*2].f){//该边存在 
			for(j=1;j<=cnt;j++)tg[j]=pipe[j];//拷贝 
			for(j=1;j<=cnt;j++)pipe[j]=ttg[j];//还原 
			pipe[i*2].f=0;pipe[i*2+1].f=0;
			GET();
			if(ans-sum==a[i]){//当且仅当差值为该边容量时，该边一定属于最小割集 
				cout<<i<<" ";
				ttg[i*2].f=ttg[i*2+1].f=0;//删除该边 
				ans=sum;
			}
			else for(j=1;j<=cnt;j++)pipe[j]=tg[j];//还原 
		}
	}
	return ;
}
int main(){
	N=read();M=read();st=read();ed=read();
	int i,x,y;
	for(i=1;i<=N;i++)a[i]=read();
	for(i=1;i<=N;i++)add(i,i+N,a[i]);//连上限制条件 
	for(i=1;i<=M;i++){
		x=read();y=read();
		add(x+N,y,inf);add(y+N,x,inf);//无向图 
	}
	n=N*2;//拆点后的总点数 
	for(i=1;i<=cnt;i++)ttg[i]=pipe[i];
	GET();
	Solve();
	return 0;
}

```

---

## 作者：X____ (赞：0)

## P4662 [BalticOI 2008] 黑手党 题解

### 题目大意

给出一个无向图，割掉一些点使得源点无法到达汇点，求割点方案中费用之和最小的方案。

### 解题思路

分析题目，容易想到是最小割问题。

由于是割点，考虑进行边点转换，对于一个点 $u$，我们可以拆成入点 $u_1$ 和出点 $u_2$，两点的边权就是 $u$ 的点权。跑一边最大流即可。

考虑如何输出方案，该点被割掉的一个条件是该点拆出来的边流量流满，但是如果这样判断就会输出多余的点导致错误，比如如下数据。
```
4 3
1 4
2
1
1
2
1 2
2 3
3 4
```
所以我们应该从源点开始进行搜索，如果该点没有流满就访问，将能访问的点进行标记，如果一个点其入点被访问过，但出点没有被访问过，那么该点被割掉。

代码如下。

```cpp
#define F(i, l, r) for(int (i) = (l); (i) <= (r); (i) ++)
using namespace std;
const int N = 1e5+3, M = 1e6+3;
struct Edge{
	int to, nxt, w;
}e[M];
int head[N], ide = 1;
void add(int u, int v, int w) {
	e[++ide] = (Edge){v, head[u], w};
	head[u] = ide;
	e[++ide] = (Edge){u, head[v], 0};
	head[v] = ide;
}
int n, m, s, t, inf = 1e9;
int dis[N], cur[N];
bitset<N>vis;
bool Bfs() {
	F(i, 1, n*2) dis[i] = -1, cur[i] = head[i];
	queue<int>q;
	q.push(s);
	dis[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = e[i].nxt) {
			int to = e[i].to;
			if(dis[to] == -1 and e[i].w > 0) {
				dis[to] = dis[u] + 1;
				q.push(to);
			}
		}
	}
	return dis[t] != -1;
}
int Dfs(int u, int flow) {
	if(u == t) return flow;
	int lef = flow;
	for(int i = head[u]; i; i = e[i].nxt) {
		int to = e[i].to;
		if(dis[to] == dis[u] + 1 and e[i].w > 0) {
			int curflow = Dfs(to, min(lef, e[i].w));
			lef -= curflow;
			e[i].w -=  curflow;
			e[i^1].w += curflow;
			if(!lef) break;
		}
	}
	if(lef == flow) dis[u] = -1;
	return flow - lef;
}
void Work(int u, int f) {
	vis[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int to = e[i].to;
		if(to == f) continue;
		if(e[i].w > 0 and !vis[to]) Work(to, u); 
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
	cin >> n >> m >> s >> t;
	t += n;
	int x, op=0;
	F(i, 1, n) {
		cin >> x;
		add(i, i+n, x);
	}
	F(i, 1, m) {
		int u, v;
		cin >> u >> v;
		add(u+n, v, inf);	
		add(v+n, u, inf);
	}
	int res = 0;
	while(Bfs()) {
		res += Dfs(s, inf);
	}
	F(i, 1, n*2) vis[i] = 0;
	Work(s, 0);
	F(i, 1, n) {
		if(vis[i] == 1 and vis[i+n] == 0) 
			cout << i << " ";
	}
	return 0;
}
```

---

## 作者：MrSWdAxiv (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/P4662)

[更好的阅读体验](https://www.cnblogs.com/MithrilSwordXIV/p/18295918)

## 题目大意

从一个点 $S$ 到另一个点 $T$，截断指定点使 $S$ 和 $T$ 不连通，并且费用最小，求截断哪些点。

## 思路

显然是最小割。

但是我们需要切割边而不是点，因此我们需要将指定点分成两个点，之间连一条流量为费用的边。所以对于一个指定的点 $i$，
可以从 $i$ 向 $i+n$ 连一条流量为 $c_i$ 的边。此外对于一条路径 $(u,v)$，也就变成了 $(u+n,v)$ 和 $(v+n,u)$ 两条边，又因为我们只能切割指定点被拆后出现的边，因此指定点之间的边的流量需要设成无穷大，使它不能被切割。

剩下的就是最小割模板了，这里我用的是 Dinic。

割完之后，我们需要判断哪些指定点被割了。这是可以走一遍深搜，标记一下所有起点能到达的点，然后再遍历一遍指定点的拆点，如果一个被标记了另一个没有，则证明拆点之间的边被割了，即点被割了。而判断两点的布尔值是否相同自然是用异或了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAX 200005
#define inf 0x7f7f7f7f //极大值 
using namespace std;
int n,m,S,T,c[MAX],cnt=1,head[MAX],maxflow;//cnt别忘了初值 
int now[MAX],dep[MAX];
bool vis[MAX];
struct MRS{
	int to,next,val;
}edge[MAX*2];
void add(int u,int v,int w){
	cnt++;
	edge[cnt].to=v;
	edge[cnt].val=w;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
/*-------------------------Dinic模板-------------------------*/
bool bfs(){
	queue<int> q;
	memset(dep,0,sizeof(dep));
	memcpy(now,head,sizeof(now));
	dep[S]=1;
	q.push(S);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to,w=edge[i].val;
			if(!dep[v]&&w){
				q.push(v);
				dep[v]=dep[u]+1;
				if(v==T)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int flow){
	if(u==T)return flow;
	int rest=flow,k=0;
	for(int i=now[u];i&&rest;i=edge[i].next){
		now[u]=i;
		int v=edge[i].to,w=edge[i].val;
		if(dep[v]==dep[u]+1&&w){
			k=dfs(v,min(rest,w));
			if(!k)dep[v]=0;
			edge[i].val-=k;
			edge[i^1].val+=k;
			rest-=k;
		}
	}
	return flow-rest;
}
/*-------------------------DFS遍历-------------------------*/
void DFS(int u){
	vis[u]=1;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to,w=edge[i].val;
		if(!vis[v]&&w)vis[v]=1,DFS(v);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>S>>T;
	T+=n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		add(i,i+n,c[i]);
		add(i+n,i,0);
	}
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		add(x+n,y,inf);
		add(y,x+n,0);
		add(y+n,x,inf);
		add(x,y+n,0);
	}
	while(bfs())maxflow+=dfs(S,inf);
	DFS(S);
	for(int i=1;i<=n;i++)
		if(vis[i]^vis[i+n])cout<<i<<' ';//判断 
	return 0;
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

给出一个无向图，每个点拥有一个点权，找到一个点集满足所有从 $a$ 到 $b$ 的路径都经过点集中的至少一个点（点集中可以含有 $a$ 和 $b$ ），并使得点集中的点点权和最小。你需要输出任意一种方案下点集中的所有点。

## 解题思路

目的是让 $a$ 与 $b$ 不连通，很容易看出是最小割问题，只不过边权变为了点权。考虑拆点：对于每一个点 $p$，将点 $p$ 拆为 $p_1,p_2$ 两点，所有终点是 $p$ 的边连到 $p_1$ 上，所有起点是 $p$ 的边连到 $p_2$ 上，容量均为 $\inf$；并在 $p_1$ 与 $p_2$ 间连边，容量为 $c$。这样割掉 $p_1,p_2$ 间的边就相当于删去了点 $p$。建图后跑最小割即可。

值得注意的是，这样建图的终点应为 $b_2$，而不是 $b_1$。否则你就会获得 $98$ 分的好成绩。

输出方案时，从源点出发 DFS 遍历残余流量不为 $0$ 的边（即没有被割去的边），标记所能到达的点，即为 $a$ 所在的那部分图。对于每一个点 $p$，若 $p_1$ 被标记且 $p_2$ 没有被标记，则点 $p$ 被删去。

AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 10000, M = 100000;
struct edge { int st, ed, v; } e[M];
vector<int> g[N];
int n, m, s, t, u, v, w, cnt = -1, pre[N], minf[N], vis[N];
long long ans;
void add(int st, int ed, int v) {
    e[++cnt] = {st, ed, v};
    g[st].push_back(cnt);
    e[++cnt] = {ed, st, 0};
    g[ed].push_back(cnt);
}
bool bfs() {
    memset(minf, 0, sizeof minf);
    queue<int> q; q.push(s);
    minf[s] = 0x3f3f3f3f;
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int id : g[p]) {
            edge ed = e[id];
            if (minf[ed.ed] || ed.v == 0) continue;
            pre[ed.ed] = id;
            minf[ed.ed] = min(minf[ed.st], ed.v);
            q.push(ed.ed);
        }
        if (minf[t]) break;
    }
    return minf[t];
}
void EK() {
    while (bfs()) {
        for (int p = t; p != s; p = e[pre[p]].st) {
            e[pre[p]].v -= minf[t];
            e[pre[p] ^ 1].v += minf[t];
        }
        ans += minf[t];
    }
}
void dfs(int p) {
    vis[p] = 1;
    for (int id : g[p])
        if (!vis[e[id].ed] && e[id].v)
            dfs(e[id].ed);
}
int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    t = t + n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);
        add(i, i + n, w);
        add(i + n, i, w);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        add(u + n, v, 0x3f3f3f3f);
        add(v + n, u, 0x3f3f3f3f);
    }
    EK();
    dfs(s);
    for (int i = 1; i <= n; i++)
        if (vis[i] != vis[i + n])
            printf("%d ", i);
    return 0;
}
```

---

## 作者：xzf_200906 (赞：0)

此题有如下明显的特征：
+ 要求割去若干个点使得某两点之间无法到达。
+ 数据范围较小。
+ ~~tag 是最小割。~~

由此，此题应使用最小割。

但是最小割割的是边，而此题要求割去的是点，于是可以使用拆点的技巧，具体地说：
+ 对于原图中的每一个点 $i$，在新图 $G$ 中连一条从 $i$ 连向 $i+n$，边权为 $c_i$ 的边。
+ 对于原图中的边 $\langle u,v\rangle$，在图 $G$ 中分别从 $u+n$ 向 $v$ 以及从 $v+n$ 向 $u$ 连一条边权为正无穷的边。
+ 则最小花费为图 $G$ 中点 $a+n$ 到点 $b$ 的最小割。

然而此题要求输出一个方案。对于最小割的输出方案，有一个很直接的思路，即输出所有满流的边，但是**这是错的**。考虑以下数据：

```
2 1
1 2
1 1
1 2
```

使用这种方法求最小割方案会得出割去 $1$ 号点和 $2$ 号点，而正确的方案仅需要任意去掉其中一个点即可。

正确的方法是在标记所有残量网络中从源点可达的点，方案即为割去所有从标记过的点连向未标记的点的边。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Dinic{
	int now[10000],head[10000],dis[10000],tot=-1,n,s,t;
	struct edge{
		int to,nxt,cur,lim;
	}ed[100005];
	void init(int n_){
		n=n_;
		for(int i=1;i<=n;i++) head[i]=-1;
	}
	void add(int u,int v,int w){
		ed[++tot]={v,head[u],0,w};
		head[u]=tot;
		ed[++tot]={u,head[v],0,0};
		head[v]=tot;
	}
	bool bfs(){
		queue<int> q;
		q.push(s);
		for(int i=1;i<=n;i++) dis[i]=-1,now[i]=head[i];
		dis[s]=0;
		while(!q.empty()){
			int p=q.front();
			q.pop();
			for(int now=head[p];now!=-1;now=ed[now].nxt){
				if(dis[ed[now].to]==-1&&ed[now].cur<ed[now].lim){
					dis[ed[now].to]=dis[p]+1;
					q.push(ed[now].to);
				}
			}
		}
		return dis[t]!=-1;
	}
	long long dfs(int p,long long las){
		if(p==t) return las;
		long long num=0;
		for(;now[p]!=-1;now[p]=ed[now[p]].nxt){
			if(dis[ed[now[p]].to]==dis[p]+1&&ed[now[p]].cur<ed[now[p]].lim){
				long long val=min((long long)ed[now[p]].lim-ed[now[p]].cur,las);
				val=dfs(ed[now[p]].to,val);
				las-=val;
				ed[now[p]].cur+=val;
				ed[now[p]^1].cur-=val;
				num+=val;
				if(las==0) break;
			}
		}
		return num;
	}
	long long work(int s_,int t_){
		s=s_,t=t_;
		long long ret=0;
		while(bfs()) ret+=dfs(s,LONG_LONG_MAX);
		return ret;
	}
};
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	Dinic d;
	d.init(n*2);
	for(int i=1;i<=n;i++){
		int c;
		cin>>c;
		d.add(i,i+n,c);
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		d.add(a+n,b,1000000000);
		d.add(b+n,a,1000000000);
	}
	d.work(a,b+n);
	for(int i=1;i<=n;i++){
		int ed=(i-1)<<1;
		if(d.dis[d.ed[ed].to]==-1&&d.dis[d.ed[ed^1].to]!=-1) cout<<i<<' ';
	}
}
```

---

## 作者：Z1qqurat (赞：0)

最小割点。考虑**转点为边**。

考虑将每个点 $i$ 拆为入点 $i$ 和出点 $i + n$，从 $i$ 到 $i + n$ 连容量为 $c_i$ 的边，这样就将最小割点转化为了求图的最小割问题；如果我们从在点 $u$ 和 $v$ 之间连无向边，那么我们就转化为在 $u + n$ 和 $v$，$v + n$ 和 $u$ 之间连容量为 $\infty$ 的边。这是因为我们希望的是**只能割点而不能割边**，所以我们将点边的容量设为其原点权，原边的容量设为无限大，这样在选取最小割的时候就怎么都不会选择原边了，达成了我们求最小割点的目的。

可能你会好奇这样拆点的正确性，这里感性理解一下：
![](https://pic.imgdb.cn/item/64a3c7681ddac507cce41c0a.png)

现在我们要控制边 $(u, v)$，在原图中我们会花出 $\min(c_u, c_v)$ 的代价，在新图中相当于**求 $u$ 到 $v + n$ 的最小割**（注意是 $v + n$，因为这里是从一个入点到一个出点！），也就是从 $u$ 到 $v + n$ 跑最大流，那么最大流求出来就是 $\min(c_u, c_v)$，最小割就是选择 $(u, u + n)$ 或者 $(v, v + n)$。所以就是说，只要保证了**连边是从入点到出点连有向边，跑最大流也是从入点到出点**，就能保证拆点的正确性。希望这个例子能让你明白。

所以建了图之后只需要从 $s$ 到 $t + n$ 跑最大流。这里需要注意，由于 $t + n$ 才是出点，所以实际上我们新图中的汇点是 $t + n$，很多模版里面原先用 $t$ 判断的都需要改为 $t + n$。为了方便起见，建议在这种拆点的题目里面都直接将 $t$ 赋值为 $t + n$，就省去对模版的修改了。（如果你是 $98$ 分可能就是这里没有注意……）

现在就是最小割的方案输出问题。说明一下，就是说**不是所有的满流边都有可能出现在最小割中**。举一个反例：

![](https://pic.imgdb.cn/item/64a3cb141ddac507cced4d20.png)

图中网络的源点为 $1$，汇点为 $6$。边 $(2, 4)$ 是满流边，但是它不可能在最小割中，因为一组含 $(2, 4)$ 的 $s-t$ 割，如 $(2, 4)$ 和 $(3, 4)$，其边权总和至少为 $4$，而如果选择边 $(4, 5)$，其也是一组可行的 $s - t$ 割，但是边权总和更小，只有 $2$。

所以我们求最小割是这样的：在 $\mathrm{Dinic}$ 算法过程中，有一个数组 $dis_u$ 表示源点 $s$ 到 $u$ 的最少经过的边数，如果 $dis_u = -1$ 则表示目前 $s$ 无法到达 $u$。如果对于点 $u$，满足 $dis_u \ne -1,dis_{u + n} = -1$（或 $dis_{u + n} \ne -1,dis_u = -1$），那么 $(u, u + n)$ 在最小割边集中，也就是说 $u$ 为最小割点。当然，如果满足这种条件，$(u, u + n)$ 自然是满流边咯。其实这就不需要再 dfs 一遍啥的，最后一次分完层就是天然的局面。

可能你会好奇，我写的不完全 bfs 优化会不会影响最小割方案的输出啊？（解释一下，不完全 bfs 优化就是在 $\mathrm{Dinic}$ 的 bfs 分层中，当遍历到了汇点 $t$ 就停止 bfs，正确性是因为已经到过 $t$ 了，那么也不可能再搜出更短的增广路了）是不会影响的，简单地证明一下：只有**满流，且在残量网络中，两个端点一个和 $s$ 在同一个 $scc$ 中，另一个和 $t$ 在同一个 $scc$ 中**的边会在最小割集中。如果边 $(u, v)$ 满足这样的条件，那么 $u$ 肯定会在 $t$ 之前被遍历（肯定比 $t$ 更靠近内层嘛~~再靠近一点就要被融化~~），而 $v$ 是无法到达的点，所以无论如何 $dis_v = -1$，没有影响。大概就是这样，瞎口糊的。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define ll long long
using namespace std;
const int N = 1000, M = 1e5 + 5;
int n, m, s, t, cnt = 1, id[N], to[M], nxt[M], head[N], cur[N], dis[N];
ll limit[M];
queue <int> q;
vector <int> ans;

void AddEdge(int u, int v, ll w) {
    to[++cnt] = v, limit[cnt] = w, nxt[cnt] = head[u], head[u] = cnt;
    to[++cnt] = u, limit[cnt] = 0, nxt[cnt] = head[v], head[v] = cnt;
    return ;
}

ll Augmenting(int u, ll rest) {
    if(u == t) return rest;
    ll ret = 0;
    for (int i = cur[u]; i && rest; i = nxt[i]) {
        cur[u] = i;
        int v = to[i]; ll c = min(rest, limit[i]);
        if(dis[v] == dis[u] + 1 && c) {
            ll f = Augmenting(v, c);
            rest -= f, ret += f;
            limit[i] -= f, limit[i ^ 1] += f;
        }
    }
    if(!ret) dis[u] = -1;
    return ret;
}

ll MaxFlow(int s, int t) {
    ll maxflow = 0;
    while(1) {
        bool bl = 0;
        memset(dis, -1, sizeof(dis));
        memcpy(cur, head, sizeof(head));
        while(!q.empty()) q.pop();
        q.push(s), dis[s] = 0;
        while(!q.empty()) {
            if(bl) break;
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if(limit[i] && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    if(v == t) {
                        bl = 1; break;
                    }
                    q.push(v);
                }
            }
        }
        if(dis[t] == -1) return maxflow;
        maxflow += Augmenting(s, 1e18);
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    t += n;
    for (int i = 1; i <= n; ++i) {
        int a; scanf("%d", &a);
        AddEdge(i, n + i, a);
        id[i] = cnt - 1;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        AddEdge(n + u, v, 1e18), AddEdge(n + v, u, 1e18);
    }
    MaxFlow(s, t);
    for (int i = 1; i <= n; ++i) {
        if((dis[i] == -1) != (dis[n + i] == -1) && !limit[id[i]]) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
```

---

## 作者：Exber (赞：0)

## 做法

最小割。

考虑建图，由于只能控制收费站，所以要把一个收费站拆成入点和出点，分别为 $i$ 和 $i+n$，从 $i$ 到 $i+n$ 连流量为 $c_i$ 的边；对于原图的一条边 $(u_i,v_i)$，需要从 $u_i+n$ 到 $v_i$ 和 $v_i+n$ 到 $u_i$ 连流量为 `inf` 的边；源点连一条流量为 `inf` 的边到 $a$，$b+n$ 连一条流量为 `inf` 的边到汇点。最后跑一遍网络最大流即可。

但题目要求输出方案，所以需要在跑完网络最大流的图上跑 `dfs`。从源点出发，只经过还有流量的边，并且访问到一个点就把它标记。这样跑完之后，如果第 $i$ 条边 $u_i$ 被标记了但 $v_i$ 没有，就说明收费站 $u_i$ 被控制了。

## AC 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

#define S 100005
#define MS 10005

typedef long long ll;

int n,m,s,t;
ll need[MS];
int esum,to[S],nxt[S],h[MS];
ll c[S];
int cur[MS],dep[MS];
bool vis[MS];

inline void add(int x,int y,ll w)
{
	to[++esum]=y;
	c[esum]=w;
	nxt[esum]=h[x];
	h[x]=esum;
}

inline void init()
{
	memset(h,0,sizeof(h));
	esum=1;
}

inline bool bfs()
{
	memset(dep,0,sizeof(dep));
	queue<int> q;
	q.push(s);
	dep[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=nxt[i])
		{
			int v=to[i];
			if(c[i]>0&&dep[v]==0)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]>0;
}

ll dfs(int u,ll w)
{
	if(u==t)
	{
		return w;
	}
	ll sum=0;
	for(int &i=cur[u];i;i=nxt[i])
	{
		int v=to[i];
		if(c[i]>0&&dep[v]==dep[u]+1)
		{
			ll re=dfs(v,min(w,c[i]));
			c[i]-=re;
			c[i^1]+=re;
			w-=re;
			sum+=re;
			if(w==0)
			{
				break;
			}
		}
	}
	return sum;
}

inline ll dinic()
{
	ll ans=0;
	while(bfs())
	{
		for(int i=1;i<=n*2;i++)
		{
			cur[i]=h[i];
		}
		ans+=dfs(s,1e17);
	}
	return ans;
}

void dfss(int u)
{
	vis[u]=true;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=to[i];
		if(c[i]>0&&!vis[v])
		{
			dfss(v);
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&s,&t);
	t+=n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&need[i]);
	}
	init();
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u+n,v,1e17);
		add(v,u+n,0);
		add(v+n,u,1e17);
		add(u,v+n,0);
	}
	for(int i=1;i<=n;i++)
	{
		add(i,i+n,need[i]);
		add(i+n,i,0);
	}
	dinic();
	dfss(s);
	vector<int> v;
	for(int i=2;i<=esum;i+=2)
	{
		if(!vis[to[i]]&&vis[to[i^1]])
		{
			v.push_back(to[i^1]);
		}
	}
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
	{
		printf("%d ",v[i]);
	}
	printf("\n");
	return 0;
}
```


---

