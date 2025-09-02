# 鉄道運賃 (Train Fare)

## 题目描述

JOI 国有 $N$  个城市，编号分别为 $1, 2, \ldots, N$ 。城市 $1$  是 JOI 国的首都。  
JOI 国只有一家铁路公司，该公司在 JOI 国内共有 $M$  条线路，这些线路编号分别为 $1, 2, \ldots, M$ 。每条线路都可看作一条无向边，线路 $i(1\leqslant i\leqslant N)$  连接城市 $U_i$  和 $V_i$ 。假设你只能依靠铁路运输在不同的城市间来往。当然你可以换乘不同线路。保证任意两个城市间都有线路直接或间接连接。  
目前，任何线路的票价是 1 日元。该公司经营不善，只好计划在未来 $Q$  年里提高票价。从提价计划开始的第 $j$  年初 $(1\leqslant j\leqslant Q)$ ，线路 $R_j$  的票价会从 1 日元升至 2 日元。 之后该线路票价一直保持在 2 日元，不会再提高。

该公司每年都会对每个城市的居民进行满意度调查。在提价计划开始之前，任何一个城市的居民都对该公司感到满意。但由于价格上涨，可能有一些城市的居民会不满。每年的满意度调查都在当年提价后进行。因此，计划开始后第 $j$  年 $(1\leqslant j\leqslant Q)$  进行满意度调查时，线路 $R_1,R_2,\ldots,R_j$  已经提价，剩余线路的票价暂无变化。  
在第 $j$  年的满意度调查中，如果**当年城市 $k(2\leqslant k\leqslant N)$  到首都的最低总票价 大于 提价计划开始前城市 $k$  到首都的最低总票价**，城市 $k$  的居民会对铁路公司感到不满。  
使用多条路线的费用是每条路线的运费的总和。首都人民不会对该公司感到不满。提价后最低费用的路线可能与计划开始前最低费用的路线有所不同。

## 样例 #1

### 输入

```
5 6 5
1 2
1 3
4 2
3 2
2 5
5 3
5
2
4
1
3```

### 输出

```
0
2
2
4
4```

## 样例 #2

### 输入

```
4 6 6
1 2
1 3
1 4
2 3
2 4
3 4
1
4
2
5
3
6```

### 输出

```
1
1
2
2
3
3```

## 样例 #3

### 输入

```
2 1 1
1 2
1```

### 输出

```
1```

# 题解

## 作者：Fading (赞：4)

这是我们的模拟赛题，我成功切掉此题成为全场唯一一个$AC$（有一个巨佬数组开小了）

而且就我是在线的！其他人都是离线。。。

首先一条边改变了权值可以当成断边处理。

考虑建出最短路树。但是一棵树边断掉了，可能还有另一条最短路怎么办呢？

那就建出“最短路图”，满足$1$号节点到每一个节点的任意一条路径都是一条最短路！由于边权都是$1$，这个是可以直接建出来的。

而且这个“最短路图”是一个$DAG!!!$

断掉一条边，就在最短路图上对应终点的入度减一，如果入度减为$0$，那么这个点就不能到达了，再把这个点的出边全部给删掉，继续判断这个点减后入度是否为$0$，继续执行。这样可以用类似于拓扑排序的方法实现。

复杂度为$O(N+M+Q)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int dep[1000001],Q,n,m,head[1000001],tot,heade[1000001],tote;
struct edge{
	int from,to,nxt,ID;
}g[1000001],e[1000001];
inline void made(int from,int to){
	g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
	g[tot].from=from;
}
int indo[1000001];
inline void maded(int from,int to){
	e[++tote].to=to;e[tote].nxt=heade[from];heade[from]=tote;
	e[tote].from=from;indo[to]++;
}
int vis[1000001];
inline void bfs(){
	for (int i=1;i<=n;i++) dep[i]=999999999;
	dep[1]=0;
	queue<int> dl;
	while (!dl.empty()) dl.pop();
	dl.push(1);
	while (!dl.empty()){
		int u=dl.front();dl.pop();
		for (int i=head[u];i;i=g[i].nxt){
			int v=g[i].to;
			if (dep[v]==999999999)
				dep[v]=dep[u]+1,dl.push(v);
		}
	}
	for (int i=1;i<=tot;i++){
		int u=g[i].from,v=g[i].to;
		if (dep[u]+1==dep[v]) maded(u,v),g[i].ID=tote;
	}
}
signed main(){
	n=read(),m=read(),Q=read();
	for (int i=1;i<=m;i++){
		int x=read(),y=read();made(x,y);made(y,x);
	}
	bfs();
	int ANS=0;
	queue<int> dl;
	while (Q--){
		int x=read();
		int ed=0;
		if (g[2*x].ID) ed=g[2*x].ID;
		else if (g[2*x-1].ID) ed=g[2*x-1].ID;
		if (ed&&!vis[ed]){
			indo[e[ed].to]--;vis[ed]=1;
			if (indo[e[ed].to]<=0){
				while (!dl.empty()) dl.pop();
				dl.push(e[ed].to);
				while (!dl.empty()){
					int u=dl.front();dl.pop();
					ANS++;
					for (int i=heade[u];i;i=e[i].nxt){
						if (vis[i]) continue;
						vis[i]=1;
						if ((--indo[e[i].to])<=0){
							dl.push(e[i].to);
						}
					}
				}
			}
		}
		printf("%d\n",ANS);
	}
	return 0;
}

```

---

## 作者：Mirasycle (赞：2)

模拟赛乱搞，居然 AC 了。

第一篇题解是建立最短路图，我之前只搞过最短路树，考场上想到了推广到最短路图但是没信心不敢写。于是换了一种做法。

我们可以发现如果增加一条边的边权后，还希望修改后的最短路长度与修改前相同的话，那么必然修改后不会经过这条边。于是等价于将这条边删去。

但是删边操作后不容易修改最短路，可以考虑**倒序操作**，将删边变成加边，也就是先把所以操作边删去，再倒着扫描加进去，这样就好办多了。我们只需要在加入一条边后更新一下最短路即可。

更新如果全局重做的话复杂太高，可以找出哪些点受影响，也就是先找到被操作边两端连接点，用最短路小的去更新大的，如果更新失败直接返回，否则将更新后的点入队。然后 bfs 一遍去继续更新。注意更新条件为如果更新后路径长度为最短路长度，才能更新，否则更新后也不是最短路对答案也就没有影响，不如等到最后可以是最短路了再一并更新。

顺便说一句，本题和洛谷上另一道一模一样的题的数据很水，只要满足路径长度缩小而非最短路就更新也能过，但这这种方法可以构造数据 Hack 掉。

以下为代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<ctime>
using namespace std;
const int maxn=1e5+10;
const int maxm=2e5+10;
const int inf=0x3f3f3f3f;
struct edge{
	int to,Next;
}edges[maxm<<1];
int r[maxm],head[maxn],n,m,q,tot=0,cnt=1;
int d[maxn][2],ans[maxm];
bool vis[maxn],lim[maxm<<1];
void add(int u,int v){
	edges[++tot]=(edge){v,head[u]};
	head[u]=tot;
}
void bfs(int t){
	queue<int> q;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) d[i][t]=inf;
	q.push(1); d[1][t]=0; vis[1]=1;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=edges[i].Next){
			int v=edges[i].to;
			if(vis[v]||lim[i]) continue;
			vis[v]=1; d[v][t]=d[u][t]+1; q.push(v);
		}
	}
}
void change(int x,int y){
	int Max=max(d[x][1],d[y][1]),Min=min(d[x][1],d[y][1]);
	if(Max==Min||Max==Min+1) return ;
	if(d[x][1]>d[y][1]) swap(x,y);
	d[y][1]=d[x][1]+1;
	if(d[y][1]!=d[y][0]) return ;
	queue<int> q; q.push(y);
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		int u=q.front(); q.pop();
		cnt++;
		for(int i=head[u];i;i=edges[i].Next){
			int v=edges[i].to;
			if(vis[v]||lim[i]||d[v][1]<=d[u][1]+1) continue;
			vis[v]=1; d[v][1]=d[u][1]+1; 
			if(d[v][1]==d[v][0]) q.push(v);//注意只有是最短路才有更新的意义 
		}
	}
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v; scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	for(int i=1;i<=q;i++) scanf("%d",&r[i]);
	bfs(0);
	for(int i=1;i<=q;i++) lim[r[i]*2-1]=lim[r[i]*2]=1;
	bfs(1);
	for(int i=2;i<=n;i++)
		if(d[i][0]==d[i][1]) cnt++;
	for(int i=q;i>=1;i--){
		ans[i]=n-cnt;
		lim[r[i]*2-1]=lim[r[i]*2]=0;
		int u=edges[r[i]*2-1].to,v=edges[r[i]*2].to;
		change(u,v);
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Skicyer (赞：1)

# [鉄道運賃 (Train Fare)](https://www.luogu.com.cn/problem/AT_joi2016ho_c)

## 题意
自己看，还有[双倍经验](https://www.luogu.com.cn/problem/P1710)。
## 题解
一眼大水题，可以很容易的求出每个站点最早的不满意时间。

设 $d_i$ 表示 $i$ 点到 $1$ 的最短距离，$w_i$ 表示最早的不满意的时间。

那么转移很明显了，利用广搜找出最短路，对等价的前一站对不满意时间取最大值。

那么就 $A$ 了这道题。
## 代码
码风应该还好
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
int fst[maxn],e[maxn<<1],nxt[maxn<<1],cnt;
int d[maxn],op[maxn],w[maxn],r[maxn],ans[maxn];
int n,m,q;
inline int val(int x) {
	if(!r[x]) {
		return 1e9;
	}
	return r[x];
}
void add(int x,int y,int z) {
	nxt[++cnt]=fst[x];
	fst[x]=cnt;
	e[cnt]=y;
	op[cnt]=z;//记录第几条路 
}
void solve() {
	queue<int> q;
	memset(d,0x3f,sizeof(d));
	q.push(1);
	d[1]=0;
	w[1]=1e9;
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=fst[x]; i; i=nxt[i]) {
			int to=e[i];
			if(d[x]+1<d[to]) {
				d[to]=d[x]+1;
				w[to]=min(val(op[i]),w[x]);
				q.push(to);
			}
			else if(d[x]+1==d[to]) {
				w[to]=max(w[to],min(val(op[i]),w[x]));
			}
		}
	}
}
signed main() {
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v; i<=m; i++) {
		scanf("%d%d",&u,&v);
		add(u,v,i);
		add(v,u,i);
	}
	for(int i=1,x; i<=q; i++) {
		scanf("%d",&x);
		r[x]=i;
	}
	solve();
	for(int i=1; i<=n; i++) {
		if(w[i]<1e9) {
			ans[w[i]]++;//统计答案 
		}
	}
	for(int i=1; i<=q; i++) {
		ans[i]+=ans[i-1];//前缀和 
		printf("%d\n",ans[i]);
	}
	return 0;
}

```


---

## 作者：shinkuu (赞：0)

说实话，我一开始的想法也和楼上大佬有点类似，但是感觉有点乱，于是去想其他做法。

这题难点就在于想到离线。一般来说，这种有后效性的修改操作离线不太可行。但是考虑最后答案只和起点间的路径有关，所以可以先给升价的边打上一个时间戳，后面再处理。

首先有一个显然的结论：在任意时刻，一条从起点到一个满意的城市的路不会经过一条升过价的路，所以可以等价于将这条路断掉。

此时，问题就转换成了：每次删边后是否存在一条从起点到 $i$ 的路径使得该长度等于原图两点最短路。我们可以将问题离线，维护每个点最早到什么时候不符合上述要求。考虑在 bfs 计算起点到 $i$ 最短距离同时 dp。则有转移：

$$dp_v=\max(dp_v,\min(dp_u,t_i))$$

$u,v$ 是路径两端，$i$ 是路径编号，$t_i$ 是这条边被删去时间。

最后，发现每个点都会对答案序列的一段后缀产生 $1$ 的贡献。差分维护即可。

code：

```cpp
int n,m,q,dis[N],f[N],ans[N<<1];
bool vis[N];
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<2];
queue<int> que;
inline void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v,q+1);
		add(v,u,q+1);
	}
	rep(i,1,q){
		int x;
		scanf("%d",&x);
		e[x*2].cw=e[x*2-1].cw=i;
	}
	mems(dis,0x3f);
	f[1]=q+1;
	dis[1]=0;
	que.push(1);
	while(que.size()){
		int u=que.front();
		que.pop();
		ans[f[u]]++;
		go(i,u){
			int v=e[i].to;
			if(dis[v]<dis[u]+1)
				continue;
			if(dis[v]==dis[u]+1)
				f[v]=max(f[v],min(f[u],e[i].cw));
			else{
				dis[v]=dis[u]+1;
				f[v]=min(f[u],e[i].cw);
				que.push(v);
			}
		}
	}
	rep(i,1,q){
		printf("%d\n",ans[i]+=ans[i-1]);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

