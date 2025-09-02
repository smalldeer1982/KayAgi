# csh和zzy的战争

## 题目背景

（背景~~有点~~长，你可以选择读完，也可以选择跳过。）

公元 2040 年，csh 和 zzy 在丑国蛙谷展开了关于非线性配微分方程的正确性与否的相关辩论，史称第四次数学危机。两个人近千页的非人类学术性论文，使整个世界没有其他人听得懂他们在说什么，于是，以 csh 为首的 A 派科学家和以 zzy 为首的 B 派科学家展开了在多次对抗无果之后开始使用武装革命解决，进而引发了全球性的第三次世界大战。作为战争中立派的居润国不想卷入任何一方的斗争，只想喝完手中的咖啡，然而两方元首在多次对抛出橄榄枝无果之后，对居润国提出了一个要求：解决他们在战争中的运送物资问题，当然这个问题早就在 $10^0$ s 内被他们解决，但是居润国却不知道怎么办，而且也不能报上错误的答案，于是就求助了聪明的你们。

## 题目描述

现在有 $n$ 个货物发源地，里面是一些待运送的货物。前方有 $m$ 个中转小岛，而你的目的是将所有货物运到战争前沿的军事基地，其运送规则如下：

1. 小岛只能由特定的货物发源地发货，其中只有几个指定的小岛可以向军事基地发货。
2. 小岛与小岛之间有 $e$ 条航道，每条航道上有一个权值 $v$ 代表这条道路开通的代价，而两个小岛之间开通货运的代价 $K$ 是两个小岛之间的最短路径长度。
3. 每个小岛上同时最多不能超过 $w$ 个货物。
4. 每个小岛一次性至多对外运输 $d$ 个货物，小岛对每个目的地至多送货一次。
5. 有 $x$ 个特殊货物发源地（不包含在 $n$ 内）会运送 csh 和 zzy 两个人的一些私人的货物，这些货物会被任何一个小岛无条件接受和送出，即不受 3，4 法则的影响。
6. 整条航路的开发费用为每对小岛开通费用 $K$ 中的最大值 $V$。

请你寻找一个最小的 $V$ 使得所有货物都能按照要求运送到军事基地。

## 说明/提示

对于 $100\%$ 的数据， $n \le 3 \times 10^2$，$e \le 10^3$。

几个提示：[https://www.luogu.com.cn/discuss/47710](https://www.luogu.com.cn/discuss/47710)。

## 样例 #1

### 输入

```
2 3 1 1
2 2 2
4 4 4
2 1 1
1 1 1
1 2 1
1 3 1
2 3 4```

### 输出

```
4```

# 题解

## 作者：忘怀星 (赞：2)

### 简述题意

给定一些货源地，一些中转岛，以及一个终点——军事基地。

货源地分为两种，普通货和特殊货。

对于中转岛 $i$ ，最多可以中转 $w_i$ 件货物，中转岛发向另一个中转岛或军事基地的货物分别不能超过 $d_i$ 。

上面货物皆指普通货物，特殊货物不会受到限制。

中转岛之间有 $e$ 条航道，航道 $i$ 有边权。开辟航线 $u-v$ 的代价是 $u$ 和 $v$ 之间的最短路。

最后全局的代价是航线代价的最大值。

要求在所有货物都能够到达军事基地的前提下，最小代价是多少。

### 解题思路

看到代价是最大值，要求其最小，考虑可以二分。将代价小于等于二分答案 $\text{mid}$ 的航线全都加进去，看是否能将所有货物都送达军事基地。二分正确性显然。

分别考虑特殊货物和普通货物。

首先考虑特殊货物，只要货源地和军事基地相连，即可全部运往军事基地。我们将所有航线全部连上，并连反边（基地连向中转岛，中转岛连向货源地）。中转岛间边权设为航线开辟代价。从军事基地开始使用最短路算法，最小化到各个货源地的路径上的最大边权。可以发现将所有特殊货源地的答案取 $\text{max}$ 是二分下界。

至于如何求出两岛间航线代价，使用 $n^3$ 的最短路即可。

然后考虑如何求是否所有普通货物都可到达军事基地。

使用网络流求最大流。货源地连中转岛容量为 $\text{inf}$ ，中转岛之间和中转岛到军事基地的边容量为 $d$ ，将中转岛拆点控制经过岛的流量不超过 $w$ 。

随后跑最大流就好了，此题解决。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define int long long
#define Mp make_pair
#define val lim
#define pb push_back
using namespace std;

int read()
{
	int a = 0,x = 1;char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
	return a*x;
}
const int N=1e6+7,inf = 1e9+7;
int n,m,X,E,a[N],w[N],d[N],b[N],M,s,t;
vector<int>g[307];
int mp[500][500],dis[N],vis[N];
int head[N],go[N],nxt[N],cnt,lim[N],cur[N];
void add(int u,int v,int w)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
	lim[cnt] = w;
}
struct node{int u,v,w;}edge[N];
void dij(int pos)
{
	priority_queue<pair<int,int> >q;
	q.push(Mp(0,pos));
	while(!q.empty()) {
		int u = q.top().second;
		if(vis[u]) {q.pop();continue;}
		dis[u] = -q.top().first;q.pop();vis[u] = 1;
		for(int e = head[u];e;e = nxt[e]) {
			int v = go[e];if(dis[v]) continue;
			q.push(Mp(min(-dis[u],-lim[e]),v));
		}
	}
}

bool BFS()
{
	for(int i = s;i <= t;i ++) dis[i] = 0;
	queue<int>q;q.push(s);dis[s] = 1;
	while(!q.empty()) {
		int u = q.front();q.pop();
		for(int e = head[u];e;e = nxt[e]) {
			int v = go[e];
			if(dis[v] || !lim[e]) continue;
			dis[v] = dis[u] + 1;q.push(v);
		}
	}
	return dis[t];
}

int DFS(int u,int limit)
{
	if(u == t || !limit) return limit;
	int ret = 0;
	for(int &e = head[u];e; e= nxt[e]) {
		int v = go[e];if(dis[v] != dis[u] + 1|| !lim[e]) continue;
		int tmp = DFS(v,min(lim[e],limit));
		lim[e] -= tmp,lim[e^1] += tmp;
		limit -= tmp,ret += tmp;
		if(!limit) break;
	}
	return ret;
}

bool check(int limit)
{
	for(int i = s;i <= t;i ++) head[i] = 0;cnt = 1;int sum = 0;
	for(int i = 1;i <= n;i ++) add(s,i,a[i]),add(i,s,0),sum += a[i];
    //货源地和中转岛
	for(int i = 1;i <= m;i ++) {
		if(b[i]) add(i+n+m,t,d[i]),add(t,i+n+m,0);
        //中转岛和军事基地
		add(i+n,i+n+m,w[i]);add(i+n+m,i+n,0);
        //拆点部分
		for(auto it = g[i].begin();it != g[i].end();++ it) {
			if(*it <= n) add(*it,i+n,inf),add(i+n,*it,0);
            //只连普通货源地，特殊货源地不必理会
		}
	}
	for(int i = 1;i <= M && edge[i].w <= limit;i ++) {
		add(edge[i].u+n+m,edge[i].v+n,d[edge[i].u]);add(edge[i].v+n,edge[i].u+n+m,0);
		add(edge[i].v+n+m,edge[i].u+n,d[edge[i].v]);add(edge[i].u+n,edge[i].v+n+m,0);
        //连上可以连的边
	}
//	puts("!");printf("sum=%d\n",sum);
	for(int i = s;i <= t;i ++) cur[i] = head[i];
	while(BFS()) {sum -= DFS(s,inf);for(int i = s;i <= t;i ++) head[i] = cur[i];}
	return !sum;//sum=0说明所有货物都可以送到军事基地
}
bool cmp(node a,node b) {return a.w < b.w;}
signed main()
{
//	freopen("in.in","r",stdin);
	n = read(),m = read(),X = read(),E = read();
	for(int i = 1;i <= n+X;i ++) a[i] = read();
	for(int i = 1;i <= m;i ++) w[i] = read();
	for(int i = 1;i <= m;i ++) d[i] = read();
	for(int i = 1;i <= m;i ++) {
		int k = read();
		for(int j = 1;j <= k;j ++) {
			int u = read();g[i].pb(u);
			add(n+X+i,u,0);
		}
		b[i] = read();if(b[i]) add(n+X+m+1,n+X+i,0); 
	}
	for(int i = 1;i <= E;i ++) {
		int u = read(),v = read(),w = read();
		mp[u][v] += w,mp[v][u] += w;//这里是看讨论区提到的，我就这么写了
	}
	for(int i = 1;i <= m;i ++) for(int j = 1;j <= m;j ++) if(!mp[i][j]) mp[i][j] = inf; else if(i!=j) add(n+X+i,n+X+j,mp[i][j]);
   	//边先连上，为处理特殊货物做准备，显然不需要连那些本来没有直接连边的航线。连接他们不会使答案更优。
	for(int k = 1;k <= m;k ++) for(int i = 1;i <= m;i ++) for(int j = 1;j <= m;j ++) mp[i][j] = min(mp[i][j],mp[i][k]+mp[k][j]);
	dij(n+m+X+1);int l = 0,r,mid;//跑最短路
	for(int i = n+1;i <= n+X;i ++) l = max(l,dis[i]);//赋值下界
	memset(head,0,sizeof(head)); cnt = 1;s = 0,t = n+2*m+1;
	for(int i = 1;i <= m;i ++) for(int j = i+1;j <= m;j ++) if(mp[i][j] < inf) edge[++M] = (node){i,j,mp[i][j]};
    //把所有航线拿出来排序
	sort(edge+1,edge+1+M,cmp);r = inf;
	while(l<r) {//二分答案
		mid = l+r>>1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	//	printf("mid=%d\n",mid); 
	} 
	if(l != inf) printf("%lld",l);
	else printf("-1");
}
```

---

## 作者：yizhiming (赞：1)

鉴于题面确实有点抽象，所以写篇题解帮助后来人。

[Link](https://www.luogu.com.cn/problem/P3652)

## 题目大意

有 $n$ 个货源，$x$ 个特殊货源，$m$ 个小岛，$e$ 条边连接小岛，有边权，其中部分小岛与军事基地相连，部分与货源相连，你需要将所有的货物都送到军事基地，具体的规则见下。

- 一对小岛之间想要运输货物，需要开辟航道，开辟航道的代价是这两个岛之间的最短路权值大小。

- 第 $i$ 个小岛最多只能中转 $w_i$ 个货物，且这个岛向每个出边所连接的点分别最多运输 $d_i$ 个货物，且包括军事基地，注意这里的出边是指上一条限制的航道，而非原图的边。

- $x$ 个特殊货源不受上述两个条件影响，只需要保证所有的特殊货源能够通过航道运输到军事基地即可。

你要在保证所有货物送到的前提下，令所有开辟航道的代价的最大值尽可能的小。

无解要输出 `-1`，可能出现重边，此时那条边的边权视作所有的重边边权之和。

$n\leq 300,e\leq 10^3$。

$x,m$ 的范围未知，但从讨论区来看貌似总点数在 $[300,400]$ 之间。

## 题目分析

看到最大值尽可能小这种限制，自然可以想到二分最大值 $mid$，每次只增加长度 $\leq mid$ 的边即可。

二分边界是什么？首先我们先想特殊货源，发现特殊货源要求我们将所有的特殊货源都送到军事基地，那么我们求出军事基地到所有特殊货源的最短路的最大值即可，只要限制 $mid\geq$ 这个值，那么就能保证特殊货源能够送到，所以可以建反图跑最短路，预处理出来二分的下界。

上界自然是值域大小。

如何判断合法？首先枚举所有的小岛对，把符合条件的先连好，发现出边是有限制的，很容易想到用网络流对流量进行限制，所以所有的出边，改成流量为 $d_i$ 的网络流的边即可，如何限制每个点只能中转 $w_i$？将每个点拆成出点入点，入点向出点连一条流量为 $w_i$ 的边即可，最后只需要跑一遍最大流看看是否流满即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1005;
int val[N][N],a[N],n,m,x,e,sum,S,T;
int w[N],d[N],dis[N],inf = 1e9+5;
int head[N],tote,top,dep[N];
bool ise[N][N],flg[N],vis[N][N];
struct aa{
	int nxt,to,val;
}edge[N*N],E[N*N];
void lnk(int u,int v,int w){
	edge[++tote] = (aa){head[u],v,w};head[u] = tote;
}
void link(int u,int v,int w){
	lnk(u,v,w);lnk(v,u,0);
}
vector<int>ed[N];
struct bb{
	int u,val;
	bool operator<(const bb &z)const{
		return val>z.val;
	} 
};
priority_queue<bb>pq;
queue<int>q;
void dij(){
	memset(dis,0x3f,sizeof(dis));
	dis[T] = 0;
	pq.push((bb){T,0});
	while(!pq.empty()){
		int u = pq.top().u;
		pq.pop();
		if(flg[u]){
			continue;
		}
		flg[u] = 1;
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(dis[now]>dis[u]+edge[i].val){
				dis[now] = dis[u]+edge[i].val;
				pq.push((bb){now,dis[now]});
			}
		}
	}
} 
bool bfs(){
	memset(dep,0,sizeof(dep));
	dep[S] = 1;
	q.push(S);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(!dep[now]&&edge[i].val){
				dep[now] = dep[u]+1;
				q.push(now);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int f){
	if(u==T){
		return f;
	}
	int used = 0;
	for(int i=head[u];i&&f;i=edge[i].nxt){
		int now = edge[i].to;
		if(dep[now]==dep[u]+1&&edge[i].val){
			int w = dfs(now,min(f,edge[i].val));
			f-=w;used+=w;
			edge[i].val-=w;edge[i^1].val+=w;
		}
	}
	if(!used){
		dep[u] = 0;
	}
	return used;
}
int flow;
void dinic(){
	flow = 0;
	while(bfs()){
		flow+=dfs(S,inf);
	}
}
bool check(int k){
	memset(head,0,sizeof(head));tote = 1;
	for(int i=1;i<=n;i++){
		link(S,i,a[i]);
	}
	for(int i=1;i<=m;i++){
		link(i+n,i+n+m,w[i]);
		for(auto u:ed[i]){
			if(u==T){
				link(i+n+m,T,d[i]);
			}else{
				link(u,i+n,inf);
			}
		}
	}
	for(int i=1;i<=top;i++){
		if(E[i].val<=k){
			link(E[i].nxt+n+m,E[i].to+n,d[E[i].nxt]);
		}
	}
	dinic();
	return flow>=sum;
}
signed main(){
	n = read();m = read();x = read();e = read();
	for(int i=1;i<=n+x;i++){
		a[i] = read();
		sum+=(i<=n)*a[i];
	}
	for(int i=1;i<=m;i++){
		w[i] = read();
	}
	for(int i=1;i<=m;i++){
		d[i] = read();
	}
	S = 0;T = n+x+2*m+1;
	for(int i=1;i<=m;i++){
		int k = read(),u;
		while(k--){
			u = read();
			
			lnk(i+n+x,u,0);lnk(u,i+n+x,0);
			if(u<=n){
				ed[i].push_back(u);
			}
		}
		u = read();
		if(u==1){
			ed[i].push_back(T);
			lnk(T,i+n+x,0);lnk(i+n+x,T,0);
		}
	}
	for(int i=1;i<=e;i++){
		int u,v,k;
		u = read();v = read();k = read();
		if(!vis[u][v]){
			vis[u][v]=1;
			vis[v][u]=1;
		}
		val[u][v]+=k;val[v][u]+=k;
	}
	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			if(vis[i][j]){
				lnk(i+n+x,j+n+x,val[i][j]);
				lnk(j+n+x,i+n+x,val[i][j]);
			}else{
				val[i][j] = inf;
				val[j][i] = inf;
			}
		}
	}
	dij();
	int l=0,r=1e9,ans=-1;
	for(int i=n+1;i<=n+x;i++){
		l = max(l,dis[i]);
	}
//	cout<<"L:"<<l<<"\n";
	for(int k=1;k<=m;k++){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				val[i][j] = min(val[i][j],val[i][k]+val[k][j]);
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(i==j||val[i][j]>=inf){
				continue;
			}
			E[++top] = {i,j,val[i][j]};
		}
	}
//	for(int i=0;i<=1770;i++){
//		check(i);
//		cout<<"CHECK:"<<i<<" "<<flow<<" "<<sum<<"\n";
//	}
	while(l<=r){
		int mid = (l+r)/2;
		if(check(mid)){
			ans = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：orz_z (赞：1)

给定一些货源地，一些中转岛，以及一个终点。

货源地分为两种，普通货和特殊货。

对于中转岛 $i$ ，最多可以中转 $w_i$ 件货物，中转岛发向另一个中转岛或军事基地的货物分别不能超过 $d_i$。

上面货物皆指普通货物，特殊货物不会受到限制。

中转岛之间有 $e$ 条航道，航道 $i$ 有边权，开辟航线 $u-v$ 的代价是 $u$ 和 $v$ 之间的最短路。

最后全局的代价是航线代价的最大值。

要求在所有货物都能够到达军事基地的前提下，最小代价是多少。

#### std

首先考虑二分最小代价 $g$，将代价 $\leq g$ 的航线加入图中，判断是否能将所有货物都送达军事基地即可。

然后考虑特殊货物，只需要先用 `dij` 求出每个特殊货源地到终点的最短路，然后二分下界即是每个特殊货源地到终点的最短路的最大值。

再考虑普通货物，先 $\mathcal O(n^3)$ 求出两点之间最短路，然后建图跑网络流即可。

$\text{1.19s / 26.07MB / 4.13KB C++20 O2}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

typedef int tp;

const int _ = 5e5 + 10, inf = 1e9 + 7;

int n, m, s, t, lv[_], cur[_];

int tot = 1, head[_], to[_ << 1], nxt[_ << 1];

tp w[_ << 1];

inline void add(int u, int v, tp lv)
{
	to[++tot] = v;
	nxt[tot] = head[u];
	w[tot] = lv;
	head[u] = tot;
}

inline void Add(int u, int v, tp lv)
{
	add(u, v, lv);
	add(v, u, 0);
}

inline bool bfs()
{
	memset(lv, -1, sizeof(lv));
	lv[s] = 0;
	memcpy(cur, head, sizeof(head));
	queue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int p = q.front();
		q.pop();
		for (int eg = head[p]; eg; eg = nxt[eg])
		{
			int v = to[eg];
			tp vol = w[eg];
			if (vol > 0 && lv[v] == -1)
				lv[v] = lv[p] + 1, q.push(v);
		}
	}
	return lv[t] != -1;
}

tp dfs(int p = s, tp flow = inf)
{
	if (p == t)
		return flow;
	tp rmn = flow;
	for (int eg = cur[p]; eg && rmn; eg = nxt[eg])
	{
		cur[p] = eg;
		int v = to[eg];
		tp vol = w[eg];
		if (vol > 0 && lv[v] == lv[p] + 1)
		{
			tp c = dfs(v, min(vol, rmn));
			rmn -= c;
			w[eg] -= c;
			w[eg ^ 1] += c;
		}
	}
	return flow - rmn;
}

inline tp dinic()
{
	tp ans = 0;
	while (bfs())
		ans += dfs();
	return ans;
}

struct node
{
	int u, v, w;
} ed[_];

bool cmp(node a, node b)
{
	return a.w < b.w;
}

int X, E, M, a[_], ww[_], b[_], d[_], dis[_], mp[507][507];

vector<int> g[307];

bool check(int lit)
{
	tot = 1;
	memset(head, 0, sizeof head);
	int sum = 0;
	for (int i = 1; i <= n; i++)
		Add(s, i, a[i]), sum += a[i];
	for (int i = 1; i <= m; i++)
	{
		if (b[i])
			Add(i + n + m, t, d[i]);
		Add(i + n, i + n + m, ww[i]);
		for (auto j : g[i])
			if (j <= n)
				Add(j, i + n, inf);
	}
	for (int i = 1; i <= M && ed[i].w <= lit; i++)
	{
		Add(ed[i].u + n + m, ed[i].v + n, d[ed[i].u]);
		Add(ed[i].v + n + m, ed[i].u + n, d[ed[i].v]);
	}
	return !(sum - dinic());
}

struct abc
{
	int u, val;
	bool operator < (const abc tmp) const
	{
		return tmp.val < val;
	}
};

void dij(int u)
{
	priority_queue<abc> q;
	q.push({u, 0});
	for(int i = 0; i < _; ++i) dis[i] = inf, lv[i] = 0;
	dis[u] = 0;
	while(!q.empty())
	{
		abc tmp = q.top();
		int now = tmp.u;
		q.pop();
		if(lv[now]) continue;
		lv[now] = 1;
		for(int i = head[now]; i; i = nxt[i])
		{
			int v = to[i];
			if(dis[v] > dis[now] + w[i])
			{
				dis[v] = dis[now] + w[i];
				if(!lv[v]) q.push({v, dis[v]});
			}
		}
	}
}

signed main()
{
	int x, y, z;
	n = read(), m = read(), X = read(), E = read();
	for (int i = 1; i <= n + X; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++)
		ww[i] = read();
	for (int i = 1; i <= m; i++)
		d[i] = read();
	for (int i = 1; i <= m; i++)
	{
		x = read();
		for (int j = 1; j <= x; j++)
		{
			y = read();
			g[i].push_back(y);
			add(n + X + i, y, 0);
		}
		b[i] = read();
		if (b[i])
			add(n + X + m + 1, n + X + i, 0);
	}
	for (int i = 1; i <= E; i++)
	{
		x = read(), y = read(), z = read();
		mp[x][y] += z, mp[y][x] += z;
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (!mp[i][j])
				mp[i][j] = inf;
			else if (i != j)
				add(n + X + i, n + X + j, mp[i][j]);
	for (int k = 1; k <= m; k++)
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
	dij(n + m + X + 1);
	s = 0, t = _ - 1;
	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= m; j++)
			if (mp[i][j] < inf)
				ed[++M] = (node){i, j, mp[i][j]};
	sort(ed + 1, ed + M + 1, cmp);
	int l = 0, r = inf, mid;
	for (int i = n + 1; i <= n + X; i++)
		l = max(l, lv[i]);
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	}
	if (r != inf)
		write(r + 1);
	else
		write(-1);
	return 0;
}
```



---

