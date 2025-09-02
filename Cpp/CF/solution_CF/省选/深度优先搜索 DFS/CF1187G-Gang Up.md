# Gang Up

## 题目描述

某个极为神秘的组织的首领决定邀请所有其他成员参加一次会议。该组织的所有成员都住在同一个小镇上，这个小镇可以表示为 $n$ 个路口，通过 $m$ 条双向街道连接。会议将在首领的家中举行，首领的家靠近路口 $1$。有 $k$ 名成员被邀请参加会议，第 $i$ 位成员住在路口 $a_i$ 附近。

所有成员会在同一时刻收到会议通知，并开始前往会议地点。每分钟的开始时，每个人都位于某个路口。他或她可以选择在当前路口等待一分钟，或者花一分钟沿着某条街道从当前路口走到另一个路口（显然，只有当街道的一端是当前路口时，才能开始沿该街道行走）。在第一分钟的开始时，每个人都在自己居住的路口。一旦某人到达路口 $1$，他或她会立即进入首领的家并参加会议。

显然，首领希望所有成员尽早到达。但由于组织极为神秘，首领又不希望引起太多关注。我们将首领的不满度定义如下：

- 初始时不满度为 $0$；
- 每当有一人到达路口 $1$ 时，不满度增加 $c \cdot x$，其中 $c$ 是某个固定常数，$x$ 是该人到达路口 $1$ 所花费的分钟数；
- 每当有 $x$ 名成员在同一时刻、同一方向上沿同一条街道行走时，不满度增加 $dx^2$，其中 $d$ 是某个固定常数。这个惩罚不会叠加：例如，如果有两个人在同一时刻、同一方向上沿同一条街道行走，则增加 $4d$，而不是 $5d$。

在发送会议通知前，首领可以为每位成员指定他们应选择的路径和等待的地点。请帮助首领为每位成员制定计划，使他们都能到达路口 $1$，并且总不满度最小。

## 说明/提示

对于第一个测试样例，最佳方案如下：

- 第一位成员沿街道 $2$ 到达路口 $2$，然后沿街道 $1$ 到达路口 $1$ 并参加会议；
- 第二位成员在路口 $3$ 等待一分钟，然后沿街道 $2$ 到达路口 $2$，再沿街道 $1$ 到达路口 $1$ 并参加会议；
- 第三位成员在路口 $3$ 等待两分钟，然后沿街道 $2$ 到达路口 $2$，再沿街道 $1$ 到达路口 $1$ 并参加会议；
- 第四位成员在路口 $3$ 等待三分钟，然后沿街道 $2$ 到达路口 $2$，再沿街道 $1$ 到达路口 $1$ 并参加会议。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 4 2 3
3 3 3 3
1 2
2 3
```

### 输出

```
52
```

## 样例 #2

### 输入

```
3 3 4 2 3
3 2 2 3
1 2
2 3
2 3
```

### 输出

```
38
```

# 题解

## 作者：CAICAIA (赞：5)

# 【题解】CF1187G Gang Up

## 题意

给定一个图，有 $k$ 个人要走到 $1$ 号节点，问最小花费。

## 解法

一眼丁真，鉴定为费用流。

考虑到这道题花费会与时间有关，所以 `分层图，启动!`。

按时刻分层，现在分析每个人在第 $k$ 时刻的动向：

    1. 呆着不动。
    2. 走到下一个节点。

对于动向 $1$ ，从时刻 $k$ 连向 时刻 $k+1$ ，流量 $inf$ ，费用 $0$ 的边。

对于动向 $2$ ，由于代价 $a^2$ 有关，所以不能直接建边。

我们分析一下每增加一个人会增加多少费用，也就是考虑怎么把这个平方拆开，直接上公式 $n^2=\sum\limits_{i=1}^n{2\times i-1}$。

把每一条原图中的边拆为 $k$ 条边，对于第 $i$ 条边，建一条 容量为 $1$，费用为 $d\times(2\times-1)$ 的边。

其他边就很好建了，不多赘述 (直接看代码吧)。

## 代码

注意数组不要开小了。

```cpp
#include<bits/stdc++.h>
using namespace std;//不过是水题罢了 
const int MX_N=50100,MX_M=5010000,INF=0x3f3f3f3f;
const int tim=120;
struct node{
    int next,to;
    int w,c;
}edge[MX_M<<1];
int head[MX_N]={0},edge_cnt=0;
inline void Add(int x,int y,int w,int c){
    node &i=edge[edge_cnt];
    i.next=head[x],i.w=w,i.c=c,i.to=y;
    head[x]=edge_cnt++;
}
inline void add(int x,int y,int w,int c){
    Add(x,y,w,c),Add(y,x,0,-c);
}
int s=0,t=MX_N-1;
int dist[MX_N]={0},pre[MX_N]={0},lim[MX_N]={0};
bool vis[MX_N]={0};
bool spfa(){
    for(int i=0;i<MX_N;i++)  dist[i]=INF,lim[i]=vis[i]=0;
    queue<int > qu;qu.push(s);vis[s]=1,dist[s]=0,lim[s]=INF;
    while(!qu.empty()){
        int now=qu.front();qu.pop();vis[now]=0;
        for(int i=head[now];~i;i=edge[i].next){
            int to=edge[i].to,w=edge[i].w,c=edge[i].c;
            if(dist[to]>dist[now]+c&&w){
                dist[to]=dist[now]+c;
                pre[to]=i;
                lim[to]=min(lim[now],w);
                if(!vis[to]){
                    qu.push(to);
                    vis[to]=1;
                }
            }
        }
    }
    return lim[t]>0;
}
void EK(int &flow,int &cost){
    flow=cost=0;
    while(spfa()){
        flow+=lim[t];
        cost+=lim[t]*dist[t];
        for(int i=t;i!=s;i=edge[pre[i]^1].to){
            edge[pre[i]].w-=lim[t];
            edge[pre[i]^1].w+=lim[t];
        }
    }
}
int n,m,k,c,d;
inline int has(int now,int ti){
    return ti*n+now;
}
signed main(){
    memset(head,-1,sizeof(head));
    //=======================================
    scanf("%d%d%d%d%d",&n,&m,&k,&c,&d);
    for(int i=1;i<=k;i++){
        int ai;scanf("%d",&ai);
        add(s,has(ai,0),1,0);
    }
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        for(int j=0;j<=tim;j++){
            for(int x=1;x<=k;x++){
                add(has(u,j),has(v,j+1),1,d*(x*2-1));
                add(has(v,j),has(u,j+1),1,d*(x*2-1));
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=tim;j++){
            add(has(i,j-1),has(i,j),INF,0);
        }
    }
    for(int j=0;j<=tim;j++)  add(has(1,j),t,INF,c*j);
    int flow,cost;EK(flow,cost);
    printf("%d",cost);
    //=======================================
    return 0;
}//CF1187G
```

求关注，求过。

---

## 作者：Purslane (赞：2)

# Solution

一眼看出这是网络流题目。由于有时间限制，考虑使用分层图。

不过有一个很尴尬的问题：我们建多少层。考虑我们每条边不让多个人同时通过，最多要花多少时间才能让所有人到 $1$ 节点。最终的时间必定不会超过这个。（因为一条边有多个人同时通过只会使时间不降，如果你最终时间超过了这个值，必定可以有所调整使得所有人到终点的时间不降）。

考虑我们随便求出这个图的一个生成树，简化问题。那么每个时刻我们都可以选择把一个人提向他的父节点。每个节点内可能囤了好多人，我们就按先来后到的顺序让他们出去。考虑计算一个人等待的时间。而他跑路的时间显然是小于等于 $n$ 的。然后你发现另外一个人最多会给它造成一次等待。所以总的时间是 $n+m$ 以内的（或者说，如果有一个人给它造成了二次等待，必定有一个人没给他造成等待。）

然后考虑怎么把平方这个贡献拆开。很简单，分别搞容量为 $1$ 价值为 $d$，$3d$，$5d$，$\dots$ 的边。

注意别把图建错了。。。记得分清各种变量的实际值。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+5,MAXM=100+5;
int n,m,k,c,d,s,t,cnt,tcnt,ans,cur[MAXN*MAXM],id[MAXM][MAXM],hd[MAXN*MAXM],tot=1,dis[MAXN*MAXM],in[MAXN*MAXM];
int u[MAXN],v[MAXN],vis[MAXN*MAXM];
struct Edge {int to,nxt,w,c;}edge[MAXN*MAXM*MAXN*4];
void add_edge(int u,int v,int w,int c) {
	edge[++tot]={v,hd[u],w,c},hd[u]=tot;
	edge[++tot]={u,hd[v],0,-c},hd[v]=tot;
	return ;	
}
int spfa(void) {
	memset(dis,0x3f,sizeof(dis)),memset(in,0,sizeof(in));
	queue<int> q; q.push(s),dis[s]=0,in[s]=0;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		in[u]=0,cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,w=edge[i].w,c=edge[i].c;
			if(w==0) continue ;
			if(dis[to]>dis[u]+c) {
				dis[to]=dis[u]+c;
				if(in[to]==0) in[to]=1,q.push(to);	
			}
		}
	}
	return dis[t]!=dis[t+1];
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	vis[u]=1;
	int res=0;
	for(int i=cur[u];i;i=edge[i].nxt) {
		cur[u]=i;
		int to=edge[i].to,w=edge[i].w,c=edge[i].c;
		if(w==0||dis[u]+c!=dis[to]||vis[to]) continue;
		int tmp=dinic(to,min(mx,w));
		if(tmp) {
			res+=tmp,edge[i].w-=tmp,edge[i^1].w+=tmp,ans+=tmp*c,mx-=tmp;
			if(mx==0) break;
		} else vis[to]=1;
	}
	return res;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>c>>d,tcnt=100;
	ffor(i,0,tcnt) ffor(j,1,n) id[j][i]=++cnt;
	t=++cnt;
	ffor(i,1,k) {int pos; cin>>pos; add_edge(s,id[pos][0],1,0);}
	ffor(i,1,m) cin>>u[i]>>v[i];
	add_edge(id[1][tcnt],t,k,c*tcnt);
	ffor(i,0,tcnt-1) {
		add_edge(id[1][i],t,k,c*i);
		ffor(j,1,m) ffor(x,1,k) add_edge(id[u[j]][i],id[v[j]][i+1],1,d*(2*x-1)),add_edge(id[v[j]][i],id[u[j]][i+1],1,d*(2*x-1));
		ffor(j,1,n) add_edge(id[j][i],id[j][i+1],k,0);
	}
	while(spfa()) {
		int tmp=0; memset(vis,0,sizeof(vis));
		while(tmp=dinic(s,n+1));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Shapy_UI_Tools (赞：2)

## 前言
高质量还挺有意思的费用流题，值得一做。
## 解法
### 思路
多个人同一时间经过一条边会产生平方级别的代价，而“同一时间”用一般网络流并不能维护，因为一般网络流的流量不具有时间性。因此，考虑按照时间建立分层图，第 $i$ 层的点表示走到一个点花费了 $i$ 秒。之后考虑建图：

设 $p(i,j)$ 表示第 $i$ 层的 $j$ 号点，$s$ 表示源点，$t$ 表示汇点。
1. 对于每个**有人的**点 $j$，建立 $s \rightarrow p(0,j)$，流量为 $1$，费用为 $0$。含义：相当于把一个人放到这个点上，初始时间为 $0$。
2. 对于每一层 $i$ 建立 $p(i,1) \rightarrow t$，流量为 $\infty$，费用为 $i \times c$。含义：一个人已经走到 $1$ 号点了，此时用时为 $i$，因此要支付 $i \times c$ 的费用。
3. 对于每一层 $i$ 的每个点 $j$，建立 $p(i,j) \rightarrow p(i+1,j)$，流量为 $\infty$，费用为 $0$。含义：一个人在一个点暂时不走，原地等待 $1$ 单位时间。
4. 按照原图的每一条无向边 $(u,v)$，对于每一层 $i$ 建立 $p(i,u) \rightarrow p(i+1,v)$ 和 $p(i,v) \rightarrow p(i+1,u)$ **各 $k$ 条**，流量均为 $1$，对于其中的第 $j$ 条 $(j \in [0,k))$，其费用为 $(j \times 2+1) \times d$。含义：因为已经按时间建立分层图，所以每条边的流量就表示在这同一时刻内有多少人经过这条边，而根据式子 $d \times a^2$ 可以知道，当同一时间经过这条边的人数从 $a$ 变为 $a+1$ 时，代价就增加了 $d \times (a+1)^2-d \times a^2=d \times (2a+1)$。因此，只需要这样建边就可以表示多了一个人在这一时刻经过这条边时会产生夺少代价。

跑一遍最小费用最大流，流量必然为 $k$，因为必然所有人都能到达 $1$ 号点。费用就是答案。
### 实现
按照这种建图方法，总点数为 $2nk$，总边数为 $2mk$。用 Dinic 和 SPFA 跑费用流，SPFA 最坏复杂度为 $O(nkmk)$，则总时间复杂度为 $O(n^2k^2nkmk) \approx O(n^8)$……啊？~~你猜我咋过的？~~注意到我们建的是分层图，图中所有边全部是连接奇数层和偶数层，所以整张图是一个二分图，因此总时间复杂度为 $O(nkmk \sqrt{nk}) \approx O(n^5)$，$4$ 秒很充足。
## 代码
[提交记录](https://www.luogu.com.cn/record/132895452)
```cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 60, INF = 0x3f3f3f3f;

int n, m, k, c, d;

inline int getidx(int x, int y) {//第x层的y号点的编号
	return x * n + y;
}

struct node {
	int to, next, siz, len;
	node() {}
	node(int _to, int _next, int _siz, int _len) {
		to = _to, next = _next, siz = _siz, len = _len;
	}
}ed[(N * N * N * 4) << 1];
int pre[N * N * 2] = { 1 }, rad[N * N * 2];

void add(int x, int y, int siz, int len) {
	ed[++pre[0]] = node(y, pre[x], siz, len);
	pre[x] = pre[0];
	ed[++pre[0]] = node(x, pre[y], 0, -len);
	pre[y] = pre[0];
}

int s, t;
int ans_siz, ans_dis;

int dis[N * N * 2];
queue<int> q;
bool inqueue[N * N * 2];

bool spfa() {
	memset(dis, 0x3f, sizeof(dis));
	memset(inqueue, 0, sizeof(inqueue));
	dis[s] = 0;
	q.push(s);
	inqueue[s] = true;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		rad[now] = pre[now];
		inqueue[now] = false;
		for (int i = pre[now]; i != 0; i = ed[i].next) {
			if (dis[ed[i].to] <= dis[now] + ed[i].len || ed[i].siz == 0) continue;
			dis[ed[i].to] = dis[now] + ed[i].len;
			if (!inqueue[ed[i].to]) {
				q.push(ed[i].to);
				inqueue[ed[i].to] = true;
			}
		}
	}
	return dis[t] != INF;
}

bool vis[N * N * 2];

int dfs(int now, int sum) {
	if (now == t) {
		ans_dis += sum * dis[t];
		return sum;
	}
	int val = sum;
	vis[now] = true;
	for (int i = rad[now]; i != 0; i = ed[i].next) {
		rad[now] = i;
		if (dis[ed[i].to] != dis[now] + ed[i].len || ed[i].siz == 0 || vis[ed[i].to]) continue;
		int tmp = dfs(ed[i].to, min(val, ed[i].siz));
		ed[i].siz -= tmp;
		ed[i ^ 1].siz += tmp;
		val -= tmp;
		if (val == 0) break;
	}
	vis[now] = false;
	return sum - val;
}

void dinic() {
	int tmp = 0;
	while (spfa()) while (tmp = dfs(s, INF)) ans_siz += tmp;
}

int main() {
	scanf("%d%d%d%d%d", &n, &m, &k, &c, &d);
	s = n * (n + k + 1) + 1, t = n * (n + k + 1) + 2;
	for (int i = 0; i <= n + k; i++) add(getidx(i, 1), t, INF, c * i);
	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		add(s, getidx(0, x), 1, 0);
	}
	for (int i = 0; i < n + k; i++)
		for (int j = 1; j <= n; j++)
			add(getidx(i, j), getidx(i + 1, j), INF, 0);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		for (int i = 0; i < n + k; i++) {
			for (int j = 1; j <= k; j++) {
				add(getidx(i, x), getidx(i + 1, y), 1, d * (j * 2 - 1));
				add(getidx(i, y), getidx(i + 1, x), 1, d * (j * 2 - 1));
			}
		}
	}
	dinic();
	printf("%d", ans_dis);
}
```

---

## 作者：kouylan (赞：2)

## 题解 CF1187G 【Gang Up】

### 【[题意](https://www.luogu.com.cn/problem/CF1187G)】

[CF题面](https://codeforces.com/contest/1187/problem/G)

给定一张图，有 $k$ 个人，每个人要走到 $1$ 号点，途中要花费代价，问最小花费。

### 【分析】

因为题中花费与时间有关，所以我们考虑按时间分层，每一层代表了每一分钟的节点。又因为 $n$ 只有$50$，所以每一个人最多需要花$50$分钟到 $1$ 号点，为了避免多个人走同一条道路的情况，我们让他们把时间错开，所以分 $100$ 层即可。建立虚拟源点连向$0$分钟时（第一层）人初始点，汇点就是第$100$层的 $1$ 号点。

接下来我们考虑花费。每一个人在每分钟有两种选择：呆在当前点不动，或者走到下一个点。第一种情况只要从这一层的点连向下一层的对应点即可，容量为 $\inf$ 花费为 $c$，注意特判 $1$ 号点花费为 $0$。第二种情况需要拆边，设一个人是第 $k$ 个在同一时间（层）走上这条边的，总花费是 $d\times k^2+k\times c$，相较于前一个人，增加了$d\times k^2-d\times (k-1)^2+c$，所以我们对于原图的每条路径，从这一层的路径端点连若干条边向下一层的路径的另一个端点，容量为 $1$花费为上述。

跑最小费用最大流即可。

下面是AC代码

```cpp
/*
luogu CF1187G
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int n,m,s,t,p,c,d,x[505],y[505];
int mxf,mnc;
int ee=1,h[5000005],nex[5000005<<1],to[5000005<<1],val[5000005<<1],cost[5000005<<1];
int dis[5000005],pre[5000005],last[5000005],flow[5000005];
bool vis[5000005];

void addedge(int x,int y,int z,int c)
{
	nex[++ee] = h[x];
	to[ee] = y;
	val[ee] = z;
	cost[ee] = c;
	h[x] = ee;
}

bool spfa()
{
	memset(dis,INF,sizeof(dis));
	memset(vis,false,sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s] = true;
	dis[s] = 0;
	flow[s] = INF;
	pre[t] = -1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x] = false;
		for(int i=h[x];i;i=nex[i])
			if(val[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]] = dis[x]+cost[i];
				pre[to[i]] = x;
				last[to[i]] = i;
				flow[to[i]] = min(flow[x],val[i]);
				if(!vis[to[i]])
				{
					vis[to[i]] = true;
					q.push(to[i]);
				}
			}
	}
	return pre[t]!=-1;
}

void mcmf()
{
	mxf = mnc = 0;
	while(spfa())
	{
		int now=t;
		mxf += flow[t];
		mnc += flow[t]*dis[t];
		while(now!=s)
		{
			val[last[now]] -= flow[t]; 
			val[last[now]^1] += flow[t];
			now = pre[now];
		}
	}
}

int zh(int t,int x)
{
	return t*n+x;
}

int main()
{
	cin>>n>>m>>p>>c>>d;
	s = 0, t = n*99+1;
	for(int i=1,x;i<=p&&cin>>x;i++)
		addedge(s,zh(0,x),1,0), addedge(zh(0,x),s,0,0);
	for(int i=1;i<=m;cin>>x[i]>>y[i],i++);
	for(int i=0;i<=99;i++)
	{
		addedge(zh(i,1),zh(i+1,1),INF,0), addedge(zh(i+1,1),zh(i,1),0,0);
		for(int j=2;j<=n;j++)
			addedge(zh(i,j),zh(i+1,j),INF,c), addedge(zh(i+1,j),zh(i,j),0,-c);
		for(int j=1;j<=m;j++)
			for(int k=1;k<=p;k++)
			{
				int cst=d*k*k-d*(k-1)*(k-1)+c;
				addedge(zh(i,x[j]),zh(i+1,y[j]),1,cst), addedge(zh(i+1,y[j]),zh(i,x[j]),0,-cst);
				addedge(zh(i,y[j]),zh(i+1,x[j]),1,cst), addedge(zh(i+1,x[j]),zh(i,y[j]),0,-cst);
			}
	}
	mcmf();
	cout<<mnc<<endl;
	
	return 0;
}
```

祝大家AC愉快！

---

## 作者：qianfujia (赞：2)

这题其实没有黑题吧

网络流，按照时间分层建图

超级源向有人点流1费0

除1外下层点向上层点流inf费c

1号点下层向上层流inf费0

每条边(u,v)这个$d*a^2$拆成d*奇数之和

因为$1+3+5+...+n*2-1=n^2$
>下层u向上层v建流1费d+c，流1费d*3+c...

>下层v向上层u同理

建完后汇点为顶层1，跑一遍最小费用最大流即可

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 5e6;
struct edge{
	int to, flow, w, nxt;
}g[M << 1];
int tot = 0, head[M];
inline void add(int u, int v, int flow, int w){
	g[tot] = edge{v, flow, w, head[u]}, head[u] = tot++;
	g[tot] = edge{u, 0, -w, head[v]}, head[v] = tot++;
}
bool vis[M];
int dis[M], flow[M], pre[M], cur[M];
int n, m, s, t;
queue <int> q;
#define clr0(x) memset(x, 0, sizeof(x))
#define clrmx(x) memset(x, 127/3, sizeof(x))
inline bool spfa(){
	clr0(vis); clrmx(dis); clrmx(flow);
	q.push(s); dis[s] = 0; vis[s] = 1; pre[t] = -1;
	while(! q.empty()){
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i = head[u]; ~i; i = g[i].nxt){
			int v = g[i].to;
			if(dis[v] > dis[u] + g[i].w && g[i].flow > 0){
				dis[v] = dis[u] + g[i].w; pre[v] = u; cur[v] = i;
				flow[v] = min(flow[u], g[i].flow);
				if(! vis[v]){vis[v] = 1; q.push(v);}
			}
		}
	}
	return pre[t] != -1;
}
inline void input(){
	memset(head, -1, sizeof(head));
	int k, c, d; scanf("%d%d%d%d%d", &n, &m, &k, &c, &d);
	for(int i = 1; i <= k; ++ i){int u; scanf("%d", &u); add(0, u, 1, 0);}
	for(int i = 1; i <= m; ++ i){
		int u, v; scanf("%d%d", &u, &v);
		for(int j = 1; j <= n + k; ++ j)
			for(int l = 1; l <= k; ++ l){
				add(u + (j - 1) * n, v + j * n, 1, d * l * 2 - d + c);
				add(v + (j - 1) * n, u + j * n, 1, d * l * 2 - d + c);
			}
	}
	for(int i = 1; i < n + k; ++ i){
		for(int j = 2; j <= n; ++ j)
			add(j + (i - 1) * n, j + i * n, 1e9, c);
		add(1 + (i - 1) * n, 1 + i * n, 1e9, 0);
	}
	s = 0, t = 1 + (n + k - 1) * n;
}
inline void solve(){
	int minw = 0;
	while(spfa()){
		int now = t; minw += flow[t] * dis[t];
		while(now != s){
			g[cur[now]].flow -= flow[t];
			g[cur[now]^1].flow += flow[t];
			now = pre[now];
		}
	}
	printf("%d", minw);
}
int main(){
	input(); solve();
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1187G)。

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16162734.html)

### $\texttt{Description}$

$k$ 个人位于一张无向图上，每个时间可以选择走动或停留。

有 $a$ 个人同时经过一条边需要 $d\times a^2$ 的代价。

一个人到达 $1$ 的时间为 $t$，则需要话费 $c\times t$ 的代价。

求所有人到达 $1$ 后的最小代价。

$1\le n,m,k\le 50$。

### $\texttt{Solution}$

发现题目中涉及到了时间，直接想到按照时间分层。

第 $i$ 个点，在第 $j$ 个时间的编号为 $i+j\times n$。

我们用 $(i,j)$ 表示第 $i$ 个点第 $j$ 个时间的状态。

一开始对于每一个 $a_i$，从 $s$ 向 $(a_i,0)$ 连一条容量为 $1$，费用为 $0$ 的边，这是很显然的。

每一个人都可以选择停留，所以将 $(i,j)$ 向 $(i,j+1)$ 连一条容量为 $\infty$，费用为 $c$。特别的，若 $i=1$，则费用为 $0$，因为已经到了 $1$ 号点，任务就结束了。

但是你会发现 $d^2$ 这个条件特别不好处理。

但是你会把 $d^2$ 转化成 $\sum_{i=1}^d(2\times d-1)$ 的形式，所以就可以根据[这道题](https://www.luogu.com.cn/problem/CF863F)的 $\texttt{trick}$，从对于原图的一条 $u$ 到 $v$ 的边，但不同的是，对于每一层，连 $k$ 条边，对于第 $t$ 条边，容量为 $1$，费用为 $d\times (2t-1)+c$。

这个怎么解释呢，容量一定的情况下，我们肯定会从最小的费用的那条边到尽可能流的最大费用的这些边流满，这些边求和肯定就是 $d^2a$ 了。其中 $a$ 为我们的流量。

然后就做完了，数组不要开小，代码：

```cpp
int main()
{
	n=read(),m=read(),k=read(),c=read(),D=read();
	int s=0;
	for(register int i=1;i<=k;i++)
	{
		int x=read();
		add_edge(s,x,1,0);
	}
	for(register int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		for(register int j=1;j<=n+k;j++)
			for(register int kk=1;kk<=k;kk++)
				add_edge(u+(j-1)*n,v+j*n,1,D*((kk<<1)-1)+c),add_edge(v+(j-1)*n,u+j*n,1,D*((kk<<1)-1)+c);;
	}
	for(register int i=1;i<k+n;i++)
	{
		for(register int j=2;j<=n;j++)
			add_edge(j+(i-1)*n,j+i*n,INF,c);
		add_edge(1+(i-1)*n,1+i*n,INF,0);
	}
	t=1+(k+n-1)*n;
	MCMF();
	return 0;
}
```

$$\texttt{The End.by UF}$$

---

## 作者：yyy爱编程 (赞：0)

分层图费用流

---- 

给定一张$n$个点$m$条边的无向连通图，有$k$个人分别从一些点，想走到$1$号点。走$1$一条边要$1$个时刻，$1$个时刻可以走$1$条边也可以不走。一个人如果$t$时刻才到$1$号点，要花费$c \cdot t$的代价。一条边**一个方向上**某一时刻如果有$a$个人同时经过，要花费$d \cdot a^2$的代价。$c$和$d$都是给定常数。求最小代价。

按照走过的边数，建原图的分层图。

对每个时刻的每个点，向下一时刻的同一个点连边，表示不走。

最多一共会有$(n+k)$个时刻，需要建$n(n+k)+2$个点。

对于一条边，拆成$2k(n+k)$条边。

然后跑费用流。

要注意加边时尽可能把价值小的边放在前面，这样不被卡常，常数小。

---

