# MCF

## 题目描述

You are given a graph consisting of $ n $ vertices and $ m $ directed arcs. The $ i $ -th arc goes from the vertex $ x_i $ to the vertex $ y_i $ , has capacity $ c_i $ and weight $ w_i $ . No arc goes into the vertex $ 1 $ , and no arc goes from the vertex $ n $ . There are no cycles of negative weight in the graph (it is impossible to travel from any vertex to itself in such a way that the total weight of all arcs you go through is negative).

You have to assign each arc a flow (an integer between $ 0 $ and its capacity, inclusive). For every vertex except $ 1 $ and $ n $ , the total flow on the arcs going to this vertex must be equal to the total flow on the arcs going from that vertex. Let the flow on the $ i $ -th arc be $ f_i $ , then the cost of the flow is equal to $ \sum \limits_{i = 1}^{m} f_i w_i $ . You have to find a flow which minimizes the cost.

Sounds classical, right? Well, we have some additional constraints on the flow on every edge:

- if $ c_i $ is even, $ f_i $ must be even;
- if $ c_i $ is odd, $ f_i $ must be odd.

Can you solve this problem?

## 样例 #1

### 输入

```
3 3
1 2 3 -10
1 2 3 -15
2 3 2 0```

### 输出

```
Possible
1 1 2```

## 样例 #2

### 输入

```
3 3
1 2 3 -10
1 2 3 -15
2 3 3 0```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
3 3
1 2 3 -10
1 2 3 -15
2 3 4 0```

### 输出

```
Possible
1 3 4```

## 样例 #4

### 输入

```
6 7
5 6 9 -40
1 2 3 -10
1 4 5 20
4 5 7 30
2 5 1 -15
1 3 3 5
3 5 3 0```

### 输出

```
Possible
5 1 1 1 1 3 3```

# 题解

## 作者：Alex_Wei (赞：3)

一个自然的想法是，对于所有容量为奇数的边，它的流量至少为 $1$。我们钦定它流 $1$ 单位流量。也就是说，将原图每条边的容量变成 $\lfloor \frac c 2\rfloor$，跑最小费用可行流，则每条边的流量为其新图流量的两倍，加上它的奇偶性。问题在于没有考虑到原来每条奇边的 $1$ 流量的影响。

简单，对于每个不为 $1$ 或 $n$ 的点，设它在仅考虑奇边的 $1$ 单位流量时，流入流量减去流出流量为 $in_i$。若 $in_i$ 为奇数，显然无解。否则，若 $in_i > 0$，说明所有奇边对 $i$ 的影响是让它多出 $in_i$ 滴流量。因此，在新图上从 $s\to i$ 连容量 **上下界** $\frac {in_i} 2$ 的边。费用任意，反正钦定流满了。

这样，我们将问题转化为 **有负权边的上下界最小费用可行流**。尽管原图保证无负环，但是为求可行流而连出的 $t\to s$ 可能导致新图产生负环，如样例 1。因此，还需使用负环费用流的技巧，钦定负权边流满，在反边上退流。

时间复杂度是一次费用流，注意构造方案的细节。[代码](https://codeforces.com/contest/1766/submission/185025112)。

---

## 作者：honglan0301 (赞：1)

## 题意简述
解决 $n\ (n\leq100)$ 个点， $m\ (m\leq200)$ 条弧的 **有源汇最小费用可行流** 问题（不要被题目翻译误导），要求对于每条弧，容量与流量的奇偶性相同。

## 题目分析
注意到每条弧的流量 $f$ 可以分为 $f/2$ 和 $f\bmod2$ 两部分，容量的奇偶性对于前者没有影响，而对于后者，容量为奇数会强制流量为 $1$, 否则强制为 $0$。

于是我们使用上下界网络流的方法，先强制让奇数弧流过 $0.5$, 再令新图的容量 $c'=c/2$。为了构造出可行流，根据每个点当前多流入流量的正负（如果非整数则无解），连 $s\rightarrow i$ 或 $i\rightarrow t$ 的费用为 $-INF$ 的弧（这里并不需要建新的源汇点，可以直接用原图上的 $s,t$ 连边，避免产生负环）。

之后直接在图上跑 $s\rightarrow t$ 的**最小费用流**即可（注意退出条件是 $dis>0$，因为不需要最大流），根据是否满流判无解。记得加上奇数弧的初始流量。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

#define int long long

int n,m,x[205],y[205],c[205],w[205],dy[105],ans[205],cnt,ncnt,head[105];
int s,t,dis[105],dep[105];
queue <int> Q;

struct edge
{
	int son;
	int val;
	int fey;
	int next;
}edge[1005];

void adde(int x,int y,int p,int q)
{
	cnt++;
	edge[cnt].son=y;
	edge[cnt].val=p;
	edge[cnt].fey=q;
	edge[cnt].next=head[x];
	head[x]=cnt;
}

bool spfa()
{
	memset(dis,127,sizeof(dis));
	memset(dep,127,sizeof(dep));
	dis[s]=dep[s]=0; Q.push(s);
	while(!Q.empty())
	{
		int nr=Q.front();
		Q.pop();
		for(int i=head[nr];i>0;i=edge[i].next)
		{
			if(edge[i].val)
			{
				if(dis[nr]+edge[i].fey<dis[edge[i].son])
				{
					dis[edge[i].son]=dis[nr]+edge[i].fey;
					dep[edge[i].son]=dep[nr]+1;
					Q.push(edge[i].son);
				}
			}
		}
	}
	return dis[t]<0;//注意
}
int dfs(int now,int nowflow)
{
	if(now==t) {return nowflow;}
	int nowuse=0;
	for(int i=head[now];i>0;i=edge[i].next)
	{
		if(edge[i].val&&dis[now]+edge[i].fey==dis[edge[i].son]&&dep[now]+1==dep[edge[i].son])
		{
			int flw=dfs(edge[i].son,min(edge[i].val,nowflow-nowuse));
			nowuse+=flw;
			edge[i].val-=flw;
			edge[((i-1)^1)+1].val+=flw;
		}
	}
	return nowuse;
}
void dinic()
{
	while(spfa())
	{
		int anss=dfs(1,100000000000000000);
	}
}//dinic

signed main()
{
	cin>>n>>m;
	s=1; t=n;
	for(int i=1;i<=m;i++)
	{
		cin>>x[i]>>y[i]>>c[i]>>w[i];
		if(c[i]&1)
		{
			dy[x[i]]--; dy[y[i]]++;
		}
		adde(x[i],y[i],c[i]/2,w[i]);
		adde(y[i],x[i],0,-w[i]);
	}
	ncnt=cnt+1;
	for(int i=2;i<=n-1;i++)
	{
		if(dy[i]&1) {cout<<"Impossible"<<endl; return 0;}
		if(dy[i]>0) 
		{
			adde(1,i,dy[i]/2,-10000000000000000);
			adde(i,1,0,10000000000000000);
		}
		else
		{
			adde(i,n,-dy[i]/2,-10000000000000000);
			adde(n,i,0,10000000000000000);
		}
	}
	dinic();
	for(int i=ncnt;i<=cnt;i+=2)
	{
		if(edge[i].val) {cout<<"Impossible"<<endl; return 0;}
	}
	cout<<"Possible"<<endl;
	for(int i=1;i<=m;i++)
	{
		cout<<edge[i*2].val*2+c[i]%2<<" ";
	}
}
```


---

## 作者：Purslane (赞：0)

# Solution

唐完了。

先计算每个点总流量的奇偶性。除了 $1$ 和 $n$ 每个点，如果总流量 $\bmod 2$ 为 $1$，那么必定无解。

把奇数边强制流 $1$ 的流量。然后所有边的流量可以除以 $2$ 了。但是这样对 $1$ 号点和 $n$ 号点并不友好，他们的总流量可能是奇数。不过这时候只需要加一条 $1$ 到 $n$ 容量为 $1$ 费用任意的边即可。

这样转化为普通的无源汇上下界最小费用可行流问题。直接建立虚拟源汇点跑费用流即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXV=100+10,MAXE=20000+10;
int n,m,s,t,tot=1,DEG[MAXV],Flg[MAXE],in[MAXV],flg[MAXE],hd[MAXV],deg[MAXV],cur[MAXV],dis[MAXV];
struct Edge {int to,nxt,f,c;}edge[MAXE];
void add_edge(int u,int v,int w,int c) {
	edge[++tot]={v,hd[u],w,c},hd[u]=tot;
	edge[++tot]={u,hd[v],0,-c},hd[v]=tot;
	return ;	
}
int spfa(void) {
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0; queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u=q.front();
		q.pop(),in[u]=0,cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,f=edge[i].f,c=edge[i].c;
			if(!f) continue ;
			if(dis[u]+c<dis[to]) {
				dis[to]=dis[u]+c;
				if(!in[to]) in[to]=1,q.push(to);	
			}
		}
	}
	return dis[t]!=dis[t+1];
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	int res=0;
	in[u]=1;
	for(int i=cur[u];i;i=edge[i].nxt) {
		cur[u]=i;
		int to=edge[i].to,f=edge[i].f,c=edge[i].c;
		if(in[to]||dis[to]!=dis[u]+c||!f) continue ;
		int tmp=dinic(to,min(mx,f));
		if(tmp) {
			edge[i].f-=tmp,edge[i^1].f+=tmp,res+=tmp,mx-=tmp;
			if(!mx) break ;
		}	
		else dis[to]=-0x3f3f3f3f;
	}
	return in[u]=0,res;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	s=0,t=n+1;
	ffor(i,1,m) {
		int u,v,w,c;
		cin>>u>>v>>w>>c;
		if(w&1) deg[u]++,deg[v]--,flg[i]=1;
		if(c>=0) add_edge(u,v,w/2,c);
		else DEG[u]+=w/2,Flg[i]=1,DEG[v]-=w/2,add_edge(v,u,w/2,-c);
	}
	if(deg[1]&1) deg[1]++,deg[n]--;
	ffor(i,2,n-1) if(deg[i]&1) return cout<<"Impossible",0;
	ffor(i,1,n) deg[i]=deg[i]/2+DEG[i];
	ffor(i,1,n) if(deg[i]>0) add_edge(i,t,deg[i],0); else add_edge(s,i,-deg[i],0);
	add_edge(n,1,100000000,0);
	while(spfa()) while(dinic(s,1000000000));
	for(int i=hd[s];i;i=edge[i].nxt) if(edge[i].f&&edge[i].to!=n) return cout<<"Impossible",0;
	for(int i=hd[t];i;i=edge[i].nxt) if(edge[i^1].f&&edge[i].to!=1) return cout<<"Impossible",0;
	cout<<"Possible\n";
	ffor(i,1,m) {
		if(Flg[i]==0) cout<<edge[(i<<1)^1].f*2+flg[i]<<' ';
		else cout<<edge[i<<1].f*2+flg[i]<<' ';
	}
	return 0;
}
```

---

## 作者：Leasier (赞：0)

这道题是一个**带流量奇偶限制的最小费用可行流**。

注意到对于 $c_i$ 为奇数的情况，最终流量 $\geq 1$，则我们可以将这些边先统一流走 $1$ 的流量，然后将容量除以 $2$ 下取整，然后通过在 $1, n$ 与每个点 $i$ 加边来平衡流量，最后再来跑费用流即可。

最终每条边的答案为费用流跑出来的流量 $\times 2$，若容量为奇数还要加 $1$。

平衡流量时存在某个点尚未平衡的流量为奇数或最终跑出来的流不能真的平衡时无解。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
	int dis;
	int cost;
} Edge;

int cnt = 1;
int x[207], y[207], deg[107], head[107], pos[207], pre_dot[107], pre_edge[107], flow[107], ans[207];
ll dis[107];
bool mark[207], vis[107];
Edge edge[797];
queue<int> q;

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		dis[i] = 0x7fffffffffffffffll;
		vis[i] = false;
	}
}

inline void add_edge(int start, int end, int dis, int cost){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
	edge[cnt].cost = cost;
}

inline void spfa(int start){
	dis[start] = 0;
	vis[start] = true;
	q.push(start);
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		vis[cur] = false;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			if (edge[i].dis != 0){
				int x = edge[i].end;
				ll y = dis[cur] + edge[i].cost;
				if (dis[x] > y){
					dis[x] = y;
					pre_dot[x] = cur;
					pre_edge[x] = i;
					if (!vis[x]){
						vis[x] = true;
						q.push(x);
					}
				}
			}
		}
	}
}

inline pair<int, ll> mincost_maxflow(int n, int start, int end){
	pair<int, ll> ans(0, 0);
	while (true){
		init(n);
		spfa(start);
		if (dis[end] >= 0) break;
		int flow = 0x7fffffff;
		for (register int i = end; i != start; i = pre_dot[i]){
			flow = min(flow, edge[pre_edge[i]].dis);
		}
		for (register int i = end; i != start; i = pre_dot[i]){
			edge[pre_edge[i]].dis -= flow;
			edge[pre_edge[i] ^ 1].dis += flow;
		}
		ans.first += flow;
		ans.second += flow * dis[end];
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	for (register int i = 1; i <= m; i++){
		int c, w;
		cin >> x[i] >> y[i] >> c >> w;
		if (c % 2 == 1){
			c--;
			deg[x[i]]--;
			deg[y[i]]++;
			mark[i] = true;
		}
		c /= 2;
		add_edge(x[i], y[i], c, w);
		add_edge(y[i], x[i], 0, -w);
		pos[i] = cnt;
	}
	for (register int i = 2; i < n; i++){
		if (deg[i] % 2 == 1){
			cout << "Impossible";
			return 0;
		}
		deg[i] /= 2;
		if (deg[i] > 0){
			add_edge(1, i, deg[i], 0x80000001);
			add_edge(i, 1, 0, 0x7fffffff);
		} else if (deg[i] < 0){
			add_edge(i, n, -deg[i], 0x80000001);
			add_edge(n, i, 0, 0x7fffffff);
		}
	}
	mincost_maxflow(n, 1, n);
	for (register int i = 1; i <= m; i++){
		ans[i] = edge[pos[i]].dis * 2 + (mark[i] ? 1 : 0);
		flow[x[i]] -= ans[i];
		flow[y[i]] += ans[i];
	}
	for (register int i = 2; i < n; i++){
		if (flow[i] != 0){
			cout << "Impossible";
			return 0;
		}
	}
	cout << "Possible" << endl;
	for (register int i = 1; i <= m; i++){
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：Cxny (赞：0)

最小费用可行流，但是限制了边流量奇偶性与容量奇偶性相同。

考虑将容量为奇数的边拆分，强制流 $1$ 的流量。这样就转化为所有边流量均为偶数。

然后就简单了。所有边容量除以 $2$，新图上流量 $1$ 代表原图流量 $2$，直接跑费用流即可。

注意流完后再 check 一下是否真的符合条件。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 110, maxm = 1e3, inf = 1e7;
struct Edge{
    int s, t, wei, cost, nxt;
}edge[maxm];
int n, m, cnt, ind[maxm], deg[maxn], h[maxn];
bool odd[maxm], inq[maxn], qwq;
void addedge(int s, int t, int wei, int cost){
    edge[cnt] = {s, t, wei, cost, h[s]}, h[s] = cnt++;
}
void add(int s, int t, int wei, int cost){addedge(s, t, wei, cost), addedge(t, s, 0, -cost);}
int s, t, pre[maxn], sum[maxn], ans[maxm];
ll mc, mf, dist[maxn];
bool SPFA(){
    fill(dist + 1, dist + n + 1, inf), fill(pre + 1, pre + n + 1, -1);
    queue<int> q; dist[s] = 0, q.push(s), inq[s] = 1;
    int cnt = 0;
    while(!q.empty()){
        int u = q.front(); q.pop(), inq[u] = 0;
        for(int i = h[u]; ~i; i = edge[i].nxt) if(edge[i].wei){
            cnt++;
            int v = edge[i].t;
            if(dist[v] > dist[u] + edge[i].cost){ 
                pre[v] = i, dist[v] = dist[u] + edge[i].cost;
                if(!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return dist[t] != inf;
}
signed main(){
    scanf("%d%d", &n, &m), s = 1, t = n, fill(h + 1, h + n + 1, -1);
    for(int i = 1, x, y, w, c; i <= m; i++){
        scanf("%d%d%d%d", &x, &y, &w, &c);
        if(w & 1) w--, odd[i] = 1, deg[x]--, deg[y]++;
        w >>= 1, ind[i] = cnt, add(x, y, w, c);
    }
    for(int i = 2; i < n; i++) if(deg[i] & 1) return puts("Impossible"), 0;
    for(int i = 2; i < n; i++) if(deg[i] >>= 1){
        if(deg[i] > 0) add(s, i, deg[i], -inf);
        else add(i, t, -deg[i], -inf);
    }
    int cnt = 0;
    while(SPFA()){
        int flow = inf; cnt++;
        for(int i = t; i != s; i = edge[pre[i]].s) flow = min(flow, edge[pre[i]].wei);
        if(1ll * flow * dist[t] > 0) break;
        for(int i = t; i != s; i = edge[pre[i]].s) edge[pre[i]].wei -= flow, edge[pre[i] ^ 1].wei += flow;
        mc += 1ll * flow * dist[t], mf += flow;
    }
    for(int i = 1; i <= m; i++){
        ans[i] = (edge[ind[i] ^ 1].wei << 1) | odd[i];
        sum[edge[ind[i]].s] -= ans[i], sum[edge[ind[i]].t] += ans[i];
    }
    for(int i = 2; i < n; i++) if(sum[i]) return puts("Impossible"), 0;
    puts("Possible");
    for(int i = 1; i <= m; i++) printf("%d ", ans[i]);
    return 0;
}
```

---

