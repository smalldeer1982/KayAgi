# Maximum Flow

## 题目描述

You are given a directed graph, consisting of $ n $ vertices and $ m $ edges. The vertices $ s $ and $ t $ are marked as source and sink correspondingly. Additionally, there are no edges ending at $ s $ and there are no edges beginning in $ t $ .

The graph was constructed in a following way: initially each edge had capacity $ c_{i}&gt;0 $ . A maximum flow with source at $ s $ and sink at $ t $ was constructed in this flow network. Let's denote $ f_{i} $ as the value of flow passing through edge with index $ i $ . Next, all capacities $ c_{i} $ and flow value $ f_{i} $ were erased. Instead, indicators $ g_{i} $ were written on edges — if flow value passing through edge $ i $ was positive, i.e. $ 1 $ if $ f_{i}&gt;0 $ and $ 0 $ otherwise.

Using the graph and values $ g_{i} $ , find out what is the minimum possible number of edges in the initial flow network that could be saturated (the passing flow is equal to capacity, i.e. $ f_{i}=c_{i} $ ). Also construct the corresponding flow network with maximum flow in it.

A flow in directed graph is described by flow values $ f_{i} $ on each of the edges so that the following conditions are satisfied:

- for each vertex, except source and sink, total incoming flow and total outcoming flow are equal,
- for each edge $ 0<=f_{i}<=c_{i} $

A flow is maximum if the difference between the sum of flow values on edges from the source, and the sum of flow values on edges to the source (there are no such in this problem), is maximum possible.

## 说明/提示

The illustration for second sample case. The saturated edges are marked dark, while edges with $ g_{i}=0 $ are marked with dotted line. The integer on edge is the index of this edge in input list. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843E/da38835a9ed43e4db05620dc1c76827cb3c4290c.png)

## 样例 #1

### 输入

```
5 6 1 5
1 2 1
2 3 1
3 5 1
1 4 1
4 3 0
4 5 1
```

### 输出

```
2
3 3
3 8
3 4
4 4
0 5
4 9
```

# 题解

## 作者：XiaoShanYunPan (赞：11)

# 题意

给出若干条边 $(u_i,v_i,g_i)$，需要给每条边赋一个正数 $f_i$ 作为容量。

在最后形成的图中跑最大流，要求构造方案使得所有 $g_i=0$ 的边没有流量，$g_i=1$ 的边有流量且满流的边数最少。

# 做法

考虑我们要使得 $g_i=0$ 的边无流量怎么做，尝试分析性质。

如果一条边 $(u_i,v_i,w_i)$ 没有流量，则在残量网络上 $v_i$ 到 $u_i$ 一定不连通，由于容量是正数，易得 $u_i$ 到 $v_i$ 一定连通。

这个性质如何利用？也许我们可以继续分析 $g_i=1$ 的情况的性质。

如果一条边 $(u_i,v_i,w_i)$ 有流量，则在残量网络上 $v_i$ 到 $u_i$ 一定连通，如果满流，$u_i$ 到 $v_i$ 不连通，否则连通。

感觉性质很有用，怎么用？

残量网络必然不连通，否则就还有更多的流量，这也就不满足一开始的残量网络的要求了，因此我们可以按照上述建出一个不连通的残量网络。

注意到此时的残量网络必然是一个满足了 $g_i$ 要求的网络跑完最大流剩下的，但是我们不知道其中满流的边的情况。

可以考虑，如果没有满流，则 $(u_i,v_i)$ 仍是连通的，如果这条边可以不满流，则意味着 $(u_i,v_i)$ 连通对残量网络不连通没有影响。

进一步，可以想到 **最小割**。我们把残量网络中有流量的边全部连通之后跑最小割即可知道哪些边必须满流。

具体来说，我们的建图策略如下：

+ 对于 $g_i=0$ 的边，连边 $(u_i,v_i,+\infty)$，强制使得二者连通。
+ 对于 $g_i=1$ 的边，连边 $(v_i,u_i,+\infty)$，强制使得二者连通，同时连边 $(u_i,v_i,1)$，表示可以割掉该边使其满流。

此时跑出的最小割即为答案。

至于方案，只需要对所有 $g_i=1$ 的边设置上下界即可，下界为 $1$，上界为 $+\infty$，这样跑一个有源汇上下界可行流即可。

代码太丑陋就不放了。

---

## 作者：zyxawa (赞：8)

### CF843E Maximum Flow

考虑到最小割一定是满流，此时最小割边数就是答案。

对于 $g_i=0$，连接 $(u_i,v_i,inf)$，没有流量则一定可以走到，还需要防止隔断；对于 $g_i=1$，连接 $(u_i,v_i,1),(v_i,u_i,inf)$，该边有流量则反向边一定有残余容量，且如果没满流，那么 $u_i$ 可以到达 $v_i$，否则就选择它假如最小割并认为它满流。

对于方案，直接上下界网络流跑有流边的方案，也就是下界为 $1$，上界为 $inf$，此时每条边的流量就是它此时的流量（注意加上下界），如果它是我们选定的最小割，则容量为它流量，否则为 $inf$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,t,tot=1,flow,maxflow,es[1001],a[1001],b[1001],g[1001],vis[301],dep[301],head[301],now[301],nex[30001],edge[30001],ver[30001];
queue <int> q;
void add(int u,int v,int w){
    ver[++tot]=v,edge[tot]=w,nex[tot]=head[u],head[u]=tot;
    ver[++tot]=u,edge[tot]=0,nex[tot]=head[v],head[v]=tot;
}
bool bfs(){
    memset(dep,0,sizeof(dep));
    while(q.size()) q.pop();
    q.push(s);
    dep[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=nex[i]){
            if(edge[i]&&!dep[ver[i]]){
                q.push(ver[i]);
                dep[ver[i]]=dep[x]+1;
                if(ver[i]==t) return true;
            }
        }
    }
    return false;
}
int dinic(int x,int flow){
    if(x==t) return flow;
    int rest=flow,k;
    for(int i=now[x];i&&rest;i=nex[i]){
        now[x]=i;
        if(edge[i]&&dep[ver[i]]==dep[x]+1){
            k=dinic(ver[i],min(edge[i],rest));
            if(!k) dep[ver[i]]=0;
            rest-=k;
            edge[i]-=k;
            edge[i^1]+=k;
        }
    }
    return flow-rest;
}
void dfs(int x){
	vis[x]=1;
	for(int i=head[x];i;i=nex[i]) if(!vis[ver[i]]&&edge[i]) dfs(ver[i]);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a[i],&b[i],&g[i]);
		if(g[i]) add(a[i],b[i],1),add(b[i],a[i],1e6);
		else add(a[i],b[i],1e6);
	}
	while(bfs()){
		for(int i=1;i<=n;i++) now[i]=head[i];
		while(flow=dinic(s,1e6)) maxflow+=flow;
	}
	dfs(s);
	printf("%d\n",maxflow);
	for(int i=1;i<=n;i++) head[i]=maxflow=0,tot=1;
	add(t,s,1e6);
	s=0,t=n+1;
	for(int i=1;i<=m;i++){
		if(g[i]){
			add(a[i],b[i],(1e6-1));
			add(s,b[i],1);
			add(a[i],t,1);
			es[i]=tot-4;
		}
	}
	while(bfs()){
		for(int i=0;i<=n+1;i++) now[i]=head[i];
		while(flow=dinic(s,1e6)) maxflow+=flow;
	}
	for(int i=1;i<=m;i++){
		if(g[i]){
			if(vis[a[i]]!=vis[b[i]]) printf("%d %d\n",edge[es[i]]+1,edge[es[i]]+1);
			else printf("%d 1000000\n",edge[es[i]]+1);
		}
		else printf("0 1000000\n");
	}
	return 0;
}
```

---

## 作者：123456xwd (赞：0)

我们先考虑如何求解满流的边数量最小，由于最大流等于最小割，在最小割上考虑就相当于要被割掉的边最少，在残量网络上考虑。

对于 $g_i=0$ 的情况，连接 $(u_i,v_i,\inf)$，相当于 $(u_i,v_i)$ 一定是联通的，不会被割掉，由于其没有流量，反边不考虑。

对于 $g_i=1$ 的情况，连接 $(v_i,u_i,\inf),(u_i,v_i,1)$，第一个限制表示残量网络上 $(v_i,u_i)$ 一定是连同的，相当于钦定 $(u_i,v_i)$ 有流量；第二个限制表示你可以花费 $1$ 的代价，将其割掉，相当于使得 $(u_i,v_i)$ 满流。

跑最小割即可。

设我们跑完残量网络，和 $s$ 相连的点在集合 $A$ 内，反之在集合 $B$ 内，则满流的边则满足：$g_i=1\land u_i\in A\land v_i\in B$。

然后考虑如何构造出来一组可行流，其实就是有汇源上下界可行流的模板，对于 $g_i=0$ 的边不用管；反之下界为 $1$，上界为 $10^9$，直接套模板即可。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
//#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=205,M=1005,INF=2e9,V=1e9;


int n,m;
struct node{
	int u,v,g;
}G[N*10];
struct edge{
	int to,nt,val;
}a[M<<3];
int head[N],at=1,s,t;
int deep[N],now[N];
void add(int u,int v,int w){
	a[++at].nt=head[u],head[u]=at,a[at].to=v,a[at].val=w;
}
void Add(int u,int v,int w){
	//printf("%lld %lld %lld\n",u,v,w);
	add(u,v,w);
	add(v,u,0);
}
bool bfs(){
	for(int i=1;i<=n+2;i++) now[i]=head[i],deep[i]=0;
	queue<int> q;int u,v,w;
	q.push(s),deep[s]=1;
	while(!q.empty()){
		u=q.front();q.pop();
		for(int i=head[u];i;i=a[i].nt){
			v=a[i].to,w=a[i].val;
			if(!deep[v]&&w){
				deep[v]=deep[u]+1;
				q.push(v);
			}
		}
	}
	return deep[t];
}
int dfs(int u,int flow){
	if(u==t||!flow) return flow;
	int tmp=0,v,w;
	for(int i=now[u];i;i=a[i].nt){
		v=a[i].to,w=a[i].val;
		now[u]=i;
		if(deep[v]==deep[u]+1&&w){
			int k=dfs(v,min(w,flow-tmp));
			if(!k) deep[v]=0;
			a[i].val-=k,a[i^1].val+=k,tmp+=k;
			if(tmp==flow) break;
		}
	}
	return tmp;
}
int Dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(s,INF);
	return ans;
}
void clean(){
	at=1;
	memset(head,0,sizeof(head));
}
int in[N],out[N],id[M];
bool vis[N];
void DFS(int u){
	vis[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		int v=a[i].to,w=a[i].val;
		if(!vis[v]&&w) DFS(v);
	}
}
int main(){
	n=rd(),m=rd(),s=rd(),t=rd();
	for(int i=1;i<=m;i++){
		G[i].u=rd(),G[i].v=rd(),G[i].g=rd();
		if(G[i].g){
			Add(G[i].v,G[i].u,INF);
			Add(G[i].u,G[i].v,1);
		}
		else Add(G[i].u,G[i].v,INF);
	}
	printf("%d\n",Dinic());
	DFS(s);clean();
	Add(t,s,INF);
	s=n+1,t=n+2;
	for(int i=1;i<=m;i++){
		if(!G[i].g) continue;
		Add(G[i].u,G[i].v,V-1);
		id[i]=at;
		out[G[i].u]++,in[G[i].v]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i]>out[i]) Add(s,i,in[i]-out[i]);
		if(in[i]<out[i]) Add(i,t,out[i]-in[i]);
	}
	Dinic();
	for(int i=1;i<=m;i++){
		if(G[i].g){
			if(vis[G[i].u]&&!vis[G[i].v]) printf("%d %d\n",a[id[i]].val+1,a[id[i]].val+1);
			else printf("%d %d\n",a[id[i]].val+1,V);
		}
		else printf("%d %d\n",0,V);
	}
    return 0;
}
```

---

