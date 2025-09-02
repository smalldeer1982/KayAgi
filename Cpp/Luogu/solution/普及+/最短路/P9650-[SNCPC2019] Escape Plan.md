# [SNCPC2019] Escape Plan

## 题目描述

宝宝被困在了 Heltion 城中。

城市可以看做由 $n$ 个点与 $m$ 条边组成的**有权无向图**，最开始宝宝在 $1$ 号节点。城市中存在 $k$ 个出口，第 $i$ 个出口位置在 $e_i$ 号点 ，而宝宝需要以最快的速度到达**这些出口中的任意一个**以逃离 Heltion 城。

不巧的是，城市中有怪物游荡，对于点 $i$，有 $d_i$ 只怪物驻守在此。当宝宝到达点 $i$ 时，怪物会**随机封锁至多** $d_i$ **条**与之相邻的道路，宝宝不能通过这些被封锁的道路。而当宝宝**离开后**，点 $i$ 的怪物会回窝，这时被封锁的**道路会解开**。

请帮帮宝宝，求出最坏情况下，他逃出 Heltion 城需要多久。

## 说明/提示

对于 $100\%$ 的数据，$1\le n \le 10^5$，$\sum n \le 10^6$，$1\le m \le 10^6$，$\sum m \le 3\times 10^6$，$1\le k \le n$，$1\le e_i \le n$，$0\le d_i \le m$，$1\le x_i,y_i \le n$，$1\le w_i \le 10^4$。数据保证 $x_i \neq y_i$。

## 样例 #1

### 输入

```
2
3 4 1
3
1 1 1
1 2 1
1 2 2
2 3 1
2 3 2
3 2 2
2 3
2 0 0
1 2 1
1 3 1
```

### 输出

```
4
-1
```

# 题解

## 作者：liaoxingrui (赞：6)

## Content

给你一个 $n$ 点与 $m$ 条边组成的有权无向图，起点为 $1$ 号点，终点有 $k$ 个，第 $i$ 个出口在 $e_i$，每经过一个点 $i$ 都会随机封锁至多 $d_i$ 条与之相邻的道路，使得你到出口距离最大，但离开后就会解封。

现在问到达任意出口的距离最短是多少，若不能到达，则输出 `-1`。

## Solution

因为它有 $k$ 个出口，并不知道到哪个出口更优，所以我们可以把 $k$ 个出口当作起点，把 $1$ 号店当作出口，这样 $dis_1$ 就是答案了。

接下来我们考虑 $d_i$，由于道路可能被封锁，所以我们要判断这个点是否还会封锁，如果会，那么就将这条路封锁了（因为这个权值是现在最优的），否则就将这个点赋值。

## Code

```cpp
#include<bits/stdc++.h>
#define p pair<int,int>
#define m(x,y) make_pair(x,y)
#define now next[i].x
#define vall next[i].val
using namespace std;
const int N=1e5+5;
const int M=3e6+5;
int t,n,m,k,x,y,z,tot;
int d[N],out[N],dis[N],head[N];
bool flag[N];
priority_queue<p,vector<p>,greater<p> > a;
struct node{
	int x,y,val;
}next[M];
inline void add(int x,int y,int z){
	tot++;
	next[tot].x=y;
	next[tot].y=head[x];
	next[tot].val=z;
	head[x]=tot;
}
inline void dijkstra(){
	while(!a.empty()){
		int x=a.top().second,val=a.top().first;
		a.pop();
		if(d[x]){
			d[x]--;
			continue;
		}
		if(flag[x])
			continue;
		flag[x]=true;
		dis[x]=val;
		for(int i=head[x];i;i=next[i].y)
			if(!flag[now])
				a.push(m(val+vall,now));
	}
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
		    dis[i]=-1;
		    head[i]=flag[i]=0;
		}
		for(int i=1;i<=k;i++){
			cin>>out[i];
			dis[out[i]]=0;
			a.push(m(0,out[i]));
		}
		for(int i=1;i<=n;i++)
			cin>>d[i];
		for(int i=1;i<=k;i++)
		    d[out[i]]=0;
		while(m--){
			cin>>x>>y>>z;
			add(x,y,z);
			add(y,x,z);
		}
		dijkstra();
		cout<<dis[1]<<endl;
	}
	return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：3)

## Part 1 题意

宝宝被困在了 Heltion 城中。

城市可以看做由 $n$ 个点与 $m$ 条边组成的有权无向图，最开始宝宝在 $1$ 号节点。城市中存在 $k$ 个出口，第 $o$ 个出口位置在 $e_i$ 号点 ，而宝宝需要以最快的速度到达这些出口中的任意一个以逃离 Heltion 城。

不巧的是，城市中有怪物游荡，对于点 $i$，有 $d_i$ 只怪物驻守在此。当宝宝到达点 $i$ 时，怪物会随机封锁至 $d_i$ 条与之相邻的道路，宝宝不能通过这些被封锁的道路。而当宝宝离开后，点 $i$ 的怪物会回窝，这时被封锁的道路会解开。

请帮帮宝宝，求出最坏情况下，他逃出 Heltion 城需要多久。

## Part 2 引入

不难发现，这是最短路算法的变式。需要求的是起点与多个终点中在最差情况下的最短路径。

由于 $1 \leq n \leq 10^5,1 \leq m \leq 10^6$，使用 SPFA 算法的最大时间复杂度为 $O(nm)$，所以我们使用时间复杂度是 $n \log n$ 的 Dijkstra 算法堆优化。

## Part 3 思路

显而易见，起点只有一个，而终点可能有多个。由于是无向图，因此我们可以交换终点和起点，让多个起点同时进行最短路操作，我们要的结果就是 $dis_1$。

由于怪物会将以节点 $i$ 为中心的 $d_i$ 条道路随机封锁，那最坏的情况就是将以节点 $i$ 为中心的 $d_i$ 条尽可能短的最短路封锁。

我们不难发现，在进行 Dijkstra 算法的时候，每一次从堆里面取出来的点都是目前找到的最佳的点，也就是已经确定最短路的点。既然怪物要封锁的是尽可能最短的道路，那如果还能封锁的话，封锁该点的道路就是最坏的情况。

换言之，每次从队列中取出点，如果该点还能封锁的道路为 $0$，那么我们就继续操作，否则不操作并将该店还能够封锁的道路数减一。

## Part 4 代码

```

#include <bits/stdc++.h>
using namespace std;
const int maxn=5e6+5;
int n,m,k,out[maxn],sca[maxn],u[maxn],v[maxn],w[maxn];
int sum,las[maxn],nex[maxn],to[maxn],len[maxn];
long long dis[maxn];
bool vis[maxn];
priority_queue< pair<long long,int> > que;
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
inline void clear()
{
	sum=0;
	memset(las,0,sizeof(las));
	memset(nex,0,sizeof(nex));
	memset(to,0,sizeof(to));
	memset(len,0,sizeof(len));
	memset(vis,false,sizeof(vis));
	while (!que.empty()) que.pop();
	return ;
}
inline void add(int x,int y,int z)
{
	sum++,to[sum]=y,len[sum]=z,nex[sum]=las[x],las[x]=sum;
	return ;
}
inline void dijkstra()
{
	for (int i=1;i<=n;i++) dis[i]=1e18;
	for (int i=1;i<=k;i++)
	{
		dis[out[i]]=0;sca[out[i]]=0;que.push(make_pair(0,out[i]));
	}
	while (!que.empty())
	{
		int x=que.top().second,z=que.top().first;
		que.pop();
		if (sca[x]!=0) { sca[x]--;continue;	}
		if (vis[x]) continue;
		vis[x]=true;
		dis[x]=-z;
		for (int i=las[x];i;i=nex[i])
		{
			int y=to[i],lon=len[i];
			if (vis[y]) continue;
			que.push(make_pair(z-lon,y));
		}
	}
	return ;
}
int main()
{
	// cout<<sizeof(las)/1024/1024<<endl;
	int t=read();while (t--)
	{
		clear();
		n=read(),m=read(),k=read();
		for (int i=1;i<=k;i++) out[i]=read();
		for (int i=1;i<=n;i++) sca[i]=read();
		for (int i=1;i<=m;i++)
		{
			u[i]=read(),v[i]=read(),w[i]=read();
			add(u[i],v[i],w[i]),add(v[i],u[i],w[i]);
		}
		dijkstra();
		if (dis[1]!=1e18) cout<<dis[1]<<endl;
		else cout<<"-1"<<endl;
	}
	return 0;
}
```

---

## 作者：WhitD (赞：2)

（~~第一眼以为是个 Dijkstra，其实它就是 Dijkstra~~）。
## 思路
这题和普通的最短路区别在于有的路径会被封堵，而且是时效性的，我们求的是最坏情况下的最短路。

显然直接正着跑一遍 Dijkstra 是不正确的，因为不知道哪条路径最短（要堵哪条路）；那就考虑反着跑，设 $dis_i$ 表示 $i$ 在最坏情况下到任意终点的最短距离（$dis_{\texttt{终点}}=0$），从终点倒推回起点求 $dis$，最后 $dis_1$ 就是我们所求的答案。

跑 Dijkstra 时：当我们从堆顶第一次取出节点 $x$ 时，记节点对应的边是 $(x,y)$，这说明我们从 $x$ 出发，走 $(x,y)$ 这条边是前往终点的最短路线。因为我们求的是最坏情况，需要把这条边堵上（保证让答案最差）。

以此类推，只要我们还可以堵塞道路，我们就需要把取出来的点所对应的边给堵上。

记 $x$ 点的堵塞次数为 $d_x$，当我们从堆顶第 $d_x+1$ 次取出节点 $x$ 时，因为 $x$ 点的堵塞次数已经用完了，那么 $dis_x$ 的值就确定为本次取的距离。

继续由 $x$ 点继续向相邻节点转移，重复上述过程。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
typedef long long ll;
typedef pair<ll,int> pi;
ll dis[N];
int T,n,m,k,d[N];
vector<int> g[N],v[N],e; 
void add(int x,int y,int w)
{
	g[x].push_back(y),v[x].push_back(w);
	g[y].push_back(x),v[y].push_back(w);
}
void dij()
{
	priority_queue<pi,vector<pi>,greater<pi>> q;
	for(int i:e)
		q.push(pi(0,i));
	while(!q.empty())
	{
		pi x=q.top();
		q.pop();
		int s=x.second;
		if(dis[s]>=0||--d[s]>=0)
            continue;
		dis[s]=x.first;
		for(int i=0;i<g[s].size();i++)
			q.push(pi(dis[s]+v[s][i],g[s][i]));
	}
}
int main()
{
	cin>>T;
	while(T--)
	{
	    memset(dis,-1,sizeof(dis));
	    for(int i=1;i<=n;i++)
			g[i].clear(),v[i].clear();
	    e.clear();
		cin>>n>>m>>k;
		for(int i=1,x;i<=k;i++)
			cin>>x,e.push_back(x);
		for(int i=1;i<=n;i++)
			cin>>d[i];
		for(int i:e) 
			d[i]=0;
		for(int i=1,x,y,w;i<=m;i++)
			cin>>x>>y>>w,add(x,y,w);
		dij();
		cout<<dis[1]<<endl;
	}
}
```


---

## 作者：luan341502 (赞：1)

Dijkstra 变式。

考虑反向跑图，如果一个结点是第一次取出，那么一定存在一条由起点到终点经过它的最优道路，符合题目说的删除要求，我们每次把它按要求减去 $1$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<long long,int> PII;
const int N=1e5+5,M=1e6+5;
struct node{
	int w,next,v;
}e[2*M];
int n,m,k,T,head[N],cnt,d[N],pos[N],vis[N];
long long dis[N];
void add(int u,int v,int w){
	e[++cnt].next=head[u];
	e[cnt].w=w;
	e[cnt].v=v;
	head[u]=cnt;
}
long long Dij(){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) dis[i]=1e18;
	priority_queue<PII,vector<PII>,greater<PII> > q;
	for(int i=1;i<=k;i++){
		q.push((PII){0,pos[i]});
		dis[pos[i]]=0;
		d[pos[i]]=0;
	}
	while(!q.empty()){
		PII u=q.top();
		q.pop();
		if(d[u.second]){
			d[u.second]=max(d[u.second]-1,0);
			continue;
		}
		if(vis[u.second]) continue;
		vis[u.second]=1;
		dis[u.second]=u.first;
		for(int i=head[u.second];i;i=e[i].next){
			int v=e[i].v;
			if(vis[v]) continue;
			q.push((PII){u.first+e[i].w,v});
		}
	}
	if(dis[1]==1e18){
		return -1;
	}else{
		return dis[1];
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		memset(e,0,sizeof(e));
		cnt=0;
		memset(d,0,sizeof(d));
		memset(head,-1,sizeof(head));
		memset(pos,0,sizeof(pos));
		for(int i=1;i<=k;i++){
			scanf("%d",&pos[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&d[i]);
		}
		for(int i=1;i<=m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			add(u,v,w);
			add(v,u,w);
		}
		printf("%lld\n",Dij());
	}
	return 0;
}
```


---

## 作者：FarmarJohn (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P9650)
### 分析
这题一开始看着唬人，~~实际还是唬人~~。其实它就是 Dijkstra 最短路算法的改版。

不知道最短路的来[这里](https://www.luogu.com.cn/problem/P4779)看这道题第一篇题解。

那**改**在了哪里？

由于我们不知道怪物要堵住哪条路，所以一个 Dijkstra 板子是没法过的。所以我们考虑一下反向跑图（也就是从终点开始跑），每次取出一个结点，假如这个结点是第一次取出，那么一定存在一条由起点到终点经过它的最优道路，我们就把它按要求减去即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010,M=5000010;
typedef pair<long long,int>lli;
struct edge
{
	int dis,next,to;
}e[M];
int n,m,k,T,head[N],cnt,d[N],tmp[N],vis[N];
long long dis[N];
inline void add(int u,int v,int w)
{
	++cnt;
	e[cnt].dis=w;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
priority_queue<lli,vector<lli>,greater<lli> >q;
inline long long dijkstra()
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;++i)dis[i]=1e18;
	for(int i=1;i<=k;++i)
	{
		q.push((lli){0,tmp[i]});
		dis[tmp[i]]=0;
		d[tmp[i]]=0;
	}
	while(!q.empty())
	{
		lli u=q.top();
		q.pop();
		if(d[u.second])
		{
			d[u.second]=max(d[u.second]-1,0);
			continue;
		}
		if(vis[u.second])continue;
		vis[u.second]=1;
		dis[u.second]=u.first;
		for(int i=head[u.second];i;i=e[i].next)
		{
			int v=e[i].to;
			if(vis[v])continue;
			q.push((lli){u.first+e[i].dis,v});
		}
	}
	if(dis[1]==1e18)return -1;
	else return dis[1];
}
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n >> m >> k;
		cnt=0;
		memset(d,0,sizeof(d));
		memset(tmp,0,sizeof(tmp));
		memset(head,-1,sizeof(head));
		memset(e,0,sizeof(e));
		for(int i=1;i<=k;++i)cin >> tmp[i];
		for(int i=1;i<=n;++i)cin >> d[i];
		for(int i=1;i<=m;++i)
		{
			int u,v,w;
			cin >> u >> v >> w;
			add(u,v,w);
			add(v,u,w);
		}
		printf("%lld\n",dijkstra());
	}
	return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：0)

这题考你到底会不会 Dijkstra。如果你确实明白这个算法到底在干什么，这个题可以直接秒掉。

重新定义 ``dis[x]`` 表示最差情况下从 $x$ 走到任意终点的最短路，并假设你从终点开始 Dijkstra。在你从堆顶第一次取出 $v$ 结点，那么说明有一条边 $u\rightarrow v$ 是去终点的一条最优道路，那么堵上就好。

同样的对后续结点进行一样的操作，堵塞次数使用完了之后 ``dis[1]`` 就是答案。

```cpp
#include <bits/stdc++.h>
#define floop(i, b, e) for(int i = b; i <= e; ++ i)
using namespace std;
using ll = long long;
using PI = pair<long long, int>;
const long long inf = 1e18;
const int MAXN = 2e6 + 3;
int head[MAXN], nxt[MAXN], G[MAXN], cnt, n, m, k, pos[MAXN], d[MAXN], w[MAXN];
ll dis[MAXN], st[MAXN];
inline void add(int u, int v, int w1) { G[++ cnt] = v, nxt[cnt] = head[u], w[cnt] = w1, head[u] = cnt; }
inline void dij() {
    floop(i, 1, n) dis[i] = inf, st[i] = 0;
    priority_queue<PI, vector<PI>, greater<PI>> q;
    floop(i, 1, k) q.push({0, pos[i]}), dis[pos[i]] = d[pos[i]] = 0;
    while(q.size()) {
        auto t = q.top(); q.pop();
        if(d[t.second]) {
            d[t.second] = max(d[t.second] - 1, 0);
            continue;
        }
        if(st[t.second]) continue;
        st[t.second] = 1, dis[t.second] = t.first;
        for(int u, i = head[t.second]; i; i = nxt[i]) {
            u = G[i];
            if(st[u]) continue;
            q.push({t.first + w[i], u});
        }
    }
    cout << ((dis[1] == inf) ? -1 : dis[1]) << endl;
    return;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for(; T; -- T) {
        cnt = 0;
        cin >> n >> m >> k;
        floop(i, 1, n) head[i] = -1; floop(i, 1, k) cin >> pos[i]; floop(i, 1, n) cin >> d[i];
        for(int u, v, w, i = 1; i <= m; ++ i) cin >> u >> v >> w, add(u, v, w), add(v, u, w);
        dij();
    }
}
```

---

