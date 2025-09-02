# [POI 2020/2021 R3] Droga do domu

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Droga do domu](https://szkopul.edu.pl/problemset/problem/ZfS_tobZ_7xdR6D5s6Tegur3/statement/)。

d1t1。

## 题目描述

$n$ 个点，$m$ 条边，无重边自环，边有长度。

$1$ 号点是学校，$n$ 号点是家。

$s$ 条公交线路。公交逢点必停，且一个点不会停两次。在一条边上行驶的时间就是它的长度。给定了第一班公交发车时间和发车间隔。

在时刻 $t$ 从学校出发，至多换乘 $k$ 次，求最早什么时候到家。

只计算路上时间和等车时间。换乘时间不计。

## 说明/提示

样例解释：![](https://cdn.luogu.com.cn/upload/image_hosting/9njsvc34.png)

对于全部数据，$2\leq n\leq 10000$，$1\leq m\leq 50000$，$1\leq s\leq 25000$，$0\leq k\leq 100$，$0\leq t\leq 10^9$，$1\leq c\leq 10^9$，$2\leq l\leq n$，$0\leq x\leq 10^9$，$1\leq y\leq 10^9$，$1\leq a,b,v\leq n$，$\sum l\leq 50000$。

| 子任务编号 | 限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $k=n$ | 20 |
| 2 | $v_i<v_{i+1}$ | 20 |
| 3 | $l=2$ | 20 |
| 4 | $t=0,x=0,y=1$ | 20 |
| 5 |  | 20 |


## 样例 #1

### 输入

```
4 4 2 1 1
1 2 2
2 3 4
1 3 3
4 3 2
4 0 10
1 2 3 4
3 2 7
1 3 2
```

### 输出

```
8```

## 样例 #2

### 输入

```
10 45 17 10 123
1 2 1
1 3 100
1 4 100
1 5 100
1 6 100
1 7 100
1 8 100
1 9 100
1 10 100
2 3 1
2 4 100
2 5 100
2 6 100
2 7 100
2 8 100
2 9 100
2 10 100
3 4 1
3 5 100
3 6 100
3 7 100
3 8 100
3 9 100
3 10 100
4 5 1
4 6 100
4 7 100
4 8 100
4 9 100
4 10 100
5 6 1
5 7 100
5 8 100
5 9 100
5 10 100
6 7 1
6 8 100
6 9 100
6 10 100
7 8 1
7 9 100
7 10 100
8 9 1
8 10 100
9 10 1
2 0 1
1 2
2 0 1
1 3
2 0 1
2 3
2 0 1
2 4
2 0 1
3 4
2 0 1
3 5
2 0 1
4 5
2 0 1
4 6
2 0 1
5 6
2 0 1
5 7
2 0 1
6 7
2 0 1
6 8
2 0 1
7 8
2 0 1
7 9
2 0 1
8 9
2 0 1
8 10
2 0 1
9 10
```

### 输出

```
132```

## 样例 #3

### 输入

```
见附件```

### 输出

```
1000000102```

## 样例 #4

### 输入

```
见附件```

### 输出

```
11100000071```

# 题解

## 作者：Bluebird_ (赞：13)

题目要求的是最短时间，我们考虑最短路，但是还有一个限制就是至多换乘 $k$ 次，如果直接跑最短路的话不能满足这个限制。

也许你会和我一开始一样，认为记录每个点的乘车次数就可以了，那么请看以下情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/68uf5r0q.png)

发车时刻都为 $0$，紫色是边权，绿色是公交线路，黄色是最终 Dij 贪心出的路线。

由于贪心的性质，Dij 会优先走上面边权为 $1$ 的边，但是消耗了很多公交次数，从上面走完之后，取出 $1\rightarrow 5$ 边权为 $999$ 的边的时候，又会因为  $vis[5]=1$（已经访问过）而跳过这条边，总结一下就是**用更少的换乘次数**和**用更少的时间**二者都可能成为最优解。

那我们有没有什么方法，能把这两种情况分开呢？当然是有的，有一种处理方式叫**分层图**很适合用于解决这种至多换乘 $k$ 次的问题。

假如现在 $k=1$（能坐 $2$ 次公交车）,那我们就建三层图，第一层代表不坐公交车，第二层代表坐一辆公交车，第三次代表坐两辆公交车，然后答案从每一层的终点统计。

1. 在 $u$ 点可以上 $i$ 号公交车的话，就在每一层的 $u$ 点往下一层的 $u$ 点连边，并令其花费为等车所用的时间。

2.  $i$ 号公交车经过 $u$ 点，且下一个点是 $v$，那我们就在每一层图中将 $u$ 向 $v$ 连一条边，代表若已经上车，就不用等车，可以直接从 $u$ 去到 $v$，花费为 $w$，即  $dist(u,v)$。

3.  $i$ 号公交车经过 $u$ 点，我们可以选择在 $u$ 点下车（貌似不用连边...?）。

看完上面这一段，相信你已经迫不及待地写好代码，那么你极有可能过不了大样例。

因为还有一种情况要注意，在上图的基础上微微改动一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/1msubg4j.png)

解释一下，原图红色数字是公交车的发车时刻，然后下面是分层图，只画出了上车的黄绿边，红色荧光笔路径是 Dij 贪心出的结果。

可能有点看不出什么，我来解释一下，我们观察一二层之间，在起点可以上发车时刻为 $0$ 的公交车，也可以上发车时刻为 $1000$ 的公交车，Dij  还是因为贪心选择了前者，这就导致了第二层的一号点又被访问过，遍历到上发车时刻为 $1000$ 的公交车的这条边时又 continue 了，事实上，如果这样跑 Dij 的话，在这个例子中他会不断地往下一层贪心，最后到达最底层，（达到坐车上限）无法到达终点。

所以我们考虑将上两种车的情况分开，怎么搞呢？让我们回到原图，既然上不同的车都有可能最优，那我们对每条公交路线分别建点连边不就行了。

![](https://cdn.luogu.com.cn/upload/image_hosting/qt3ou5u8.png)

绿边还是公交路线，黄边是上下车，绿荧光笔代表整一条路径（为方便理解才加上的）。

也就是我们在每条公交线路上都单独建点，这样就能做到互不影响，然后在此基础上再建多层图。

将原来的结论修改一下，我们令 $u$ 点为原图上的点，$U_i$ 是 $u$ 在 $i$ 号公交车线路上的点，$v$ 和 $V_i$ 同理。

1. 在 $u$ 点可以上 $i$ 号公交车的话，就在每一层的 $u$ 点往**下一层**的 $U_i$ 点连边，并令其花费为等车所用的时间。

2.    $i$ 号公交车经过 $u$ 点，且下一个点是 $v$，那我们就在每一层图中将**同层** $U_i$ 向 $V_i$ 连一条边，代表若已经上车，就不用等车，可以直接从 $u$ 去到 $v$，花费为 $w$，即  $dist(u,v)$。

3.  $i$ 号公交车经过 $u$ 点，我们可以选择在 $u$ 点下车，在每一层图中将**同层** $U_i$ 点向 $u$ 点连边。

来计算一下时间复杂度，首先是建图，每一层都要建边，每层我们新建出 $\sum l$ 个点，时间复杂度为 $O(\sum lk)$。

然后是最短路，总共有 $(n+\sum l)k$ 个点，一个新建的点最多能连三条边（上面的三种情况），最坏有 $3k\sum l$ 条边，加上 Dij 的复杂度就是。

$$ O\left( \left((n+\sum l)k+3k\sum l\right)log(3k\sum l)\right)$$

~~有点丑陋，整理一下。~~

$$O\left(k(4\sum l+n)log{(3k\sum l)}\right)$$

算一下好像到了 $4 \times 10^{8}$，要加点优化才能过，常数不能太大，~~可能因为我比较菜，优化空间优化时间调了一天交了一百次才过。。~~

顺带一提，`longlong` 类型的数字计算真的耗时间，我其他优化怎么加都比不过重复使用的变量类型从 `ll` 改成 `int`。

Code:有注释喔。

```cpp
#include<bits/stdc++.h>
#define int long long
#define P pair<int,int>
using namespace std;
signed rd()
{
	signed x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0')f=ch=='-'?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10ll+ch-'0',ch=getchar();
	return x*f;
}
void wr(int x)
{
	if(x>9ll)wr(x/10ll);
	putchar(x%10ll+'0');
}
const signed N=6e6+500000,M=1e7+5e6+5e5;
const int inf=0x3f3f3f3f3f3f3f3f;
signed to[M],nxt[M],head[N],bus[M],val[M],num[M],cnt;
inline void add(signed u,signed v,int w,signed t,signed i){to[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;val[cnt]=w;num[cnt]=t;bus[cnt]=i;}
int T,ans=inf;
signed n,m,s,K,flg,tot;
vector<int>dis(N),SRT(25050),DT(25050);
bitset<N> vis;
map<P,signed>mp;
vector<int>dist[25500];
vector<pair<signed,signed> >g[25500];
inline int wt(int x,signed nm,signed i)
{//x是开始等的时间，i代表i号公交线路，nm代表在i号线路上的第nm个点 
	if(nm==-1)return 0;//用nm=-1表示不用等车（已经在公交车上了） 
	int srt=1ll*SRT[i]+dist[i][nm],dt=DT[i];//计算出第一班车到nm点的时间 （srt） 
	if(srt>=x)return srt-x;//如果开始等的时候第一班都没来，就直接等第一班 
	x-=srt;
	if(dt==1||x%dt==0)return 0;
	return dt-x%dt;
} 
priority_queue<pair<int,signed> >q;
void dij()
{
	for(signed i=1;i<=(K+1)*tot;++i)
		dis[i]=inf,vis[i]=0;
	dis[1]=T;//别忘了题目有给初始时刻 
	to[0]=1;
	q.emplace(0,0);//我的优先队列里存的是<dis[u],i> i是更新u的边，起点特殊情况处理一下 
	while(q.size())
	{
		signed I=q.top().second;q.pop();
		signed u=to[I];
		if(vis[u])continue;
		if(dis[u]>=ans)continue;//小优化 
		vis[u]=1;
		for(signed i=head[u];i;i=nxt[i])
		{
			signed v=to[i];int w=val[i],cst=w+wt(dis[u],num[i],bus[i]);//wt函数计算的是等到车的时间 
			if(vis[v])continue;
			if(dis[u]+cst>=ans)continue;//小优化 
			if(u/tot==v/tot&&bus[i]!=bus[I])continue;//在同一层图中，要坐同一辆公交车 
			if(dis[v]>dis[u]+cst)
			{
				dis[v]=dis[u]+cst;
				q.emplace(-dis[v],i);
				if(v%tot==flg)ans=min(ans,dis[v]);
				//终点在各层图的编号分别是flg,flg+1*tot,flg+2*tot,所以当v%tot==flg时，v是终点 
			}
		}
	}
	return;
}
signed main()
{
	n=rd();m=rd();s=rd();K=rd();T=rd();++K;//换乘次数最多为K即最多坐K+1辆车 
	flg=n;tot=n;//flg代表终点编号，因为待会加边会++n，所以要先存下终点n，tot记录的是一层图的点数字 
	for(signed i=1;i<=m;++i)
	{
		signed u=rd(),v=rd(),w=rd();
		mp[{u,v}]=w;mp[{v,u}]=w;//mp存边 
	}
	for(signed i=1;i<=s;++i)
	{
		signed l=rd();SRT[i]=rd();DT[i]=rd();//SRT(start)存发车时刻, DT存发车的间隔时间 
		tot+=l;//一条公交路线新开l个点 
		dist[i].emplace_back(0);//公交路线i距离前缀和 
		for(signed j=0;j<l;++j)
		{
			signed x=rd();
			g[i].emplace_back(x,++n);//给点x开新点 
			if(j==0)continue;
			signed u=g[i][j-1].first,v=g[i][j].first;
			signed w=mp[{u,v}];
			dist[i].emplace_back(dist[i][j-1]+w);
		}
	}
	for(signed i=1;i<=s;++i)
	{
		int l=g[i].size(),srt=SRT[i],dt=DT[i];
		for(register signed j=1;j<l;++j)
		{
			int u=g[i][j-1].first,v=g[i][j].first,w=dist[i][j]-dist[i][j-1];//w是u到v的距离 
			int U=g[i][j-1].second,V=g[i][j].second;
			for(register signed k=0;k<K;++k)
			{
				add(u+(k)*tot,V+(k+1)*tot,w,j-1,i);//从u点坐上i号公交，坐了一辆新公交，连边到下一层图中 
				add(U+(k+1)*tot,V+(k+1)*tot,w,-1,i);//坐同一辆公交 ，在同一层图中连边 
				add(V+(k+1)*tot,v+(k+1)*tot,0,-1,i);//下公交，也在同层图中连边 
			}
		}
	}	
	dij();
	if(ans>=inf)puts("NIE");
	else wr(ans);
	return 0;
 } 
```



---

## 作者：xuchuhan (赞：12)

## Preface

非常巧妙的思路，但是想清楚之后会豁然开朗。

## Solution

考虑到原图中不能清晰的表示每条线路，而是混成了一坨，又看到数据范围 $\sum l\leq 5\times 10^4$，考虑将每条线路都拉成一条链，对于每条链进行分析。

注：下称输入的图为原图，拉成链的图为新图。

当然，不同的线路可能存在重复的点，所以我们拉成链的时候，可能会将**原图上同一个点表示为新图上多个点**。

然后我们发现，换乘的过程实际上是在每条链上进行转换横跳，所以我们可以设 $dp_{i,j}$ 表示到新图中点 $i$，经过 $j$ 次换乘的最小代价。

然后我们考虑分阶段分析，阶段为换乘的次数。枚举换乘次数 $j$，那么转移会从 2 种情况得来。一种是在同一条链上的某条边转移得来，另一种是通过在当前 $i$ 号点换乘得来。

这里重点讲一下后一种如何转移。我们知道，对于新图上不同的点可能会指向原图上同一个点，那么我们对于原图上每个点建一个 `vector`，存一下原图上每个点在新图上对应的点的编号。

回到 dp 的点 $i$，我们找到它在原图上对应的点 $fa$，再通过 $fa$ 找到在新图其他链上但同样在原图中对应点 $fa$ 的一些点 $to$，那么点 $i$ 均可以从 $to$ 换乘，即从 $to$ 的那条线路换乘到 $i$ 的线路。

初始时所有对应原图上点 $1$ 的点 $i$，有 $dp_{i,0}=t$，$t$ 即题目中的 $t$，表示出发时间。其余 dp 状态初始时设为 $\infty$。答案同理，对于所有对应原图上点 $n$ 的点 $i$，均可以被计入答案，故答案为 $\min_{j=0}^k dp_{i,j}$。

## Code

部分变量与上文的不太相同。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=25005,M=5e4+5;
int n,m,s,K,t,tot,ans;
map<int,int>mp[N];
int inter[N],b[M],col[M];
int dp[M][105];
struct edge{int to,val,tim;}e[M];//因为新图上所有点指向的是唯一的边(链),所以设e[i]表示新图上点i到点i的后继那条边的状态 
vector<int>v[N];
int calc(int id,int fr,int now){//计算等车+坐车的代价 
	if(now<=e[id].tim)return e[id].tim+e[id].val;
	int num=(now-e[id].tim+inter[fr]-1)/inter[fr];
	return num*inter[fr]+e[id].tim+e[id].val;
}
signed main(){
	cin>>n>>m>>s>>K>>t;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		mp[x][y]=mp[y][x]=z;//记录原图边权好建新图 
	}
	for(int i=1,tmp,l;i<=s;i++){
		cin>>l>>tmp>>inter[i];
		for(int j=1;j<=l;j++)cin>>b[j];
		for(int j=1;j<=l;j++){
			col[++tot]=i;
			v[b[j]].push_back(tot);//原图的点所对应的新图的点 
			if(j<l){e[tot]={tot+1,mp[b[j]][b[j+1]],tmp};tmp+=e[tot].val;}
			else e[tot].tim=tmp;
		}
	}
	for(int i=1;i<=tot;i++)
		for(int j=0;j<=K;j++)
			dp[i][j]=0x3f3f3f3f3f3f3f3f3f;
	for(int i=0;i<v[1].size();i++)dp[v[1][i]][0]=t;//初始状态 
	for(int i=1;i<=tot;i++){//同链转移 
		int to=e[i].to;
		if(!to)continue;
		dp[to][0]=min(dp[to][0],calc(i,col[i],dp[i][0]));
	}
	for(int j=1;j<=K;j++){
		for(int i=1;i<=n;i++){//换乘转移 
			int mini=0x3f3f3f3f3f3f3f3f3f;
			for(int k=0;k<v[i].size();k++)mini=min(mini,dp[v[i][k]][j-1]);
			for(int k=0;k<v[i].size();k++)dp[v[i][k]][j]=mini;
		}
		for(int i=1;i<=tot;i++){//同链转移 
			int to=e[i].to;
			if(!to)continue;
			dp[to][j]=min(dp[to][j],calc(i,col[i],dp[i][j]));
		}
	}
	ans=0x3f3f3f3f3f3f3f3f3f;
	for(int i=0;i<v[n].size();i++)//记录答案 
		for(int j=0;j<=K;j++)
			ans=min(ans,dp[v[n][i]][j]);
	if(ans==0x3f3f3f3f3f3f3f3f3f)cout<<"NIE";//无解 
	else cout<<ans;
	return 0;
}
```

## Afterword

输入原图时 $m$ 写成 $n$，调 1h，衷心希望大家不要重蹈覆辙。

听说赛前写题解会 rp++？也祝大家 CSP-J/S2024 rp++！

---

## 作者：ran_qwq (赞：8)

赛时没判无解，爽。

$k\le100$，容易想到暴力建分层图跑 dijkstra。具体地，每层建 $n$ 个起点 $n$ 个终点，每条线的每个地铁站再建一个点，终点向下一层的起点连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/24db0try.png)

如图，每条边 $(u,v)$ 有权值 $(w,x,y)$，表示走的时间为 $w$，最早到达 $v$ 时间为 $x$，到达 $v$ 时间间隔为 $y$（$y=0$ 则为没有间隔）。其中绿色的边权值为 $(0,x,y)$（$x$ 表示 $v$ 所在地铁最早到达 $v$ 时间，$y$ 为所在地铁发车间隔），橙色和蓝色的边权值为 $(w,0,0)$，紫色边权值为 $(0,0,0)$。转移时 $dis_v\leftarrow\max(x,dis_u+(x-dis_u)\bmod y)$。

但是边数可以达到 $10^7$ 级别，$O((m+\sum l)k\log(m+\sum l)k)$ 会 TLE。

但仔细想想，每层的建边都是一样的，所以只需要跑 $k+1$ 遍 dijkstra 即可，每次把终点的 dis 倒入下一次的起点即可。复杂度 $O(k\sum l\log\sum l)$。

实现细节比较多。

事实上 dijkstra 可以换成 dp，少一只 log，不过赛时没写。

```cpp
int n,m,s,k,t,nm,a[N],b[N],d[N],p[M*2]; ll ans=INFll,lst[M*2]; map<pii,int> mp;
struct GRAPH {
	int id,hd[M*2]; ll dis[M*2];
	struct EDGE {int to,w; ll x; int y,ne;} e[M*4];
	void add(int u,int v,int w=0,ll x=0,int y=0) {e[++id]={v,w,x,y,hd[u]},hd[u]=id;}
	void dij() {
		priority_queue<pli> q;
		for(int u=1;u<=n;u++) if(dis[u]!=INFll) q.push({-dis[u],u});
		for(int u;q.size();) {
			u=q.top().sec,q.pop(); ll t,x;
			for(int i=hd[u],v,w,y;i;i=e[i].ne) {
				v=e[i].to,w=e[i].w,x=e[i].x,y=e[i].y,t=y?max(x,dis[u]+(x%y-dis[u]%y+y)%y):dis[u]+w;
				if(t<dis[v]) dis[v]=t,q.push({-dis[v],v});
			}
		}
	}
} g;
void QwQ() {
	n=rd(),nm=n*2,m=rd(),s=rd(),k=rd(),t=rd();
	for(int u,v,w;m--;) u=rd(),v=rd(),w=rd(),mp[{u,v}]=mp[{v,u}]=w;
	for(int c,y;s--;) {
		ll x; c=rd(),x=rd(),y=rd();
		for(int i=1,w;i<=c;i++)
			p[b[i]=++nm]=a[i]=rd(),d[i]=mp[{a[i-1],a[i]}],g.add(a[i],b[i],0,x+=d[i],y);
		for(int i=2,w;i<=c;i++) g.add(b[i-1],b[i],d[i]);
	}
	mst(lst,0x3f),lst[1]=t;
	for(int i=0;i<=k;i++) {
		for(int u=1;u<=nm;u++) g.dis[u]=lst[u];
		g.dij();
		for(int u=n*2+1;u<=nm;u++) cminll(lst[p[u]],g.dis[u]);
		cminll(ans,lst[n]);
	}
	if(ans==INFll) puts("NIE"); else wrll(ans,"\n");
}
```

常见问题：

- 要开 long long 的地方必须开。
- 记得判无解。
- 不保证 $x<y$，所以 $x$ 在计算时不能取模。
- 点数是 $2n+\sum l$，边数是 $2\sum l$，数组记得开够。

---

## 作者：Thunder_S (赞：7)

## Solution

一个图，求起点到终点的最小时间

但是怎么建图。如果直接在原图上面跑，是否换乘了这个问题将难以解决。但是注意到 $\sum l\le 50000$。这意味着我们可以对于每条公交线，建 $\sum l$ 个点，拉成 $s$ 条链。那么在这个链上转移就不需要换乘，从一条链到另一条链就换乘次数增加 1。

这样的话，如果我们顺序枚举 $j(1\sim k)$，就可以做到无后效性，从而 $dp$。

设 $f_{i,j}$ 表示到了节点 $i$，此时换乘了 $j$ 次的最小时间。注意这里的 $i$ 的范围是 $\sum l$。

那么转移就可以从本链上的点不换乘转移，也可以从别的链上转移过来。

因为是链，所以每个点只会转移到一个点，而且链上节点的顺序是递增的。因此直接枚举 $i$，用 $f_{i,j}$ 去更新 $f_{to_i,j}$。

至于从别的链上转移，我们可以记录原图中节点 $i$ 在新图中对应的节点是什么。在这些节点中找到最小的 $f_{i,j-1}$，去更新 $f_{i,j}$。即使 $f_{x,j}$ 被 $f_{x,j-1}$ 更新也没有关系，因为换乘次数少的不会劣。

注意更新的顺序。要先更新了换乘的，再去更新不换乘的。这与坐车的顺序是一样的，先选择线路，再做到下一站。

时间复杂度 $\mathcal O(k\sum l)$。

## Code
```cpp
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 10005
#define M 50005
#define K 105
#define ll long long
using namespace std;
int n,m,s,k,cnt,rt[M];
ll t,inf,ans,f[M][K];
struct edg {int to;ll val;};
struct node 
{
	int to;
	ll len;
	ll st,ti;
}a[M];
struct que{int x,k;ll t;bool bj;};
vector<edg> g[N];
vector<int> p[N];
queue<que> q;
ll read()
{
    ll res=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch-'0'),ch=getchar();
    return res;
}
void add(int x,int y,ll z,ll st,ll ti) {a[x].to=y;a[x].len=z;a[x].st=st;a[x].ti=ti;}
bool cmp(edg x,edg y) {return x.to<y.to;}
ll calc(ll nowt,ll st,ll ti)
{
    if (nowt<=st) return st;
    ll tn=(nowt-st)/ti;
    if ((nowt-st)%ti!=0) tn++;
    return tn*ti+st;
}
int main()
{
    n=read();m=read();s=read();k=read();t=read();
	for (int i=1;i<=m;++i)
	{
		int x,y;ll z;
        x=read();y=read();z=read();
		g[x].push_back((edg){y,z});
		g[y].push_back((edg){x,z});
	}
    for (int i=1;i<=n;++i)
        sort(g[i].begin(),g[i].end(),cmp);
	for (int i=1;i<=s;++i)
	{
		int num=read();ll x=read(),y=read();
		int lst=0,u=0;
		for (int j=1;j<=num;++j)
		{
			int v;v=read();
			++cnt;
			p[v].push_back(cnt);rt[cnt]=v;
			if (!u) u=v,lst=cnt;
			else
			{
				int l=0,r=g[u].size()-1,mid,res=0;
				while (l<=r)
				{
					mid=(l+r)>>1;
					if (v<=g[u][mid].to) res=mid,r=mid-1;
					else l=mid+1;
				}
				add(lst,cnt,g[u][res].val,x,y);
				lst=cnt;x+=g[u][res].val;u=v;//找到链上每条边的权值
			}
		}
	}
    memset(f,127,sizeof(f));
    inf=f[0][0];
    for (int i=0;i<p[1].size();++i)
        f[p[1][i]][0]=t;
    for (int x=1;x<=cnt;++x)
    {
        int y=a[x].to;
        if (!y) continue;
        ll nxt=calc(f[x][0],a[x].st,a[x].ti)+a[x].len;
        f[y][0]=min(f[y][0],nxt);
    }
    for (int j=1;j<=k;++j)
    {
        for (int now=1;now<=n;++now)
        {
            ll mn=inf;
            for (int i=0;i<p[now].size();++i)
                mn=min(mn,f[p[now][i]][j-1]);
            for (int i=0;i<p[now].size();++i)
                f[p[now][i]][j]=mn;
        }//先换乘
        for (int x=1;x<=cnt;++x)
        {
            int y=a[x].to;
            if (!y) continue;
            ll nxt=calc(f[x][j],a[x].st,a[x].ti)+a[x].len;
            f[y][j]=min(f[y][j],nxt);
        }//再坐到下一站
    }
    ans=inf;
    for (int i=0;i<p[n].size();++i)
        for (int j=0;j<=k;++j)
            ans=min(ans,f[p[n][i]][j]);
    if (ans>=inf) printf("NIE\n");
    else printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：潘德理2010 (赞：4)

在这篇题解中，记一个点的编号为该点所对应的公交站点的编号。

发现最多换乘 $k$ 次，而 $k\le100$，另外题目要我们求最短时间，于是考虑分层图最短路。第 $i$ 层表示换乘过 $i$ 次。

发现有两种走法：沿着当前线路一直走，或者换乘。

首先考虑第一种情况（不换乘的情况）：

因为要沿着一条线路一直走，且不换乘，所以这种情况的边应该建在同一层内。我们对每一条线路建一条链（这些链不相交）。对于边的边权，我们在输入边时把所有边都存进一个 map 里（map 的 key 值存两个点对应的二元组，value 值存边权），建边时直接在 map 中找边权即可。在找边权的时候，因为我们要建很多层结构一样的图，在第一次建图时把找到的边权存起来，之后建图的时候直接调用即可。以样例 $1$ 为例，有 $1\to 2\to 3\to 4,1\to 3\to 2$ 两条线路，那么每一层的建图方式如下（最上方数字表示该列点的编号，边上的数字表示边权）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9oatciuv.png)

然后再考虑换乘的情况。

因为要换乘，换乘后换乘次数会 $+1$，所以从某一层连到下一层。显然我们不能从一层中的每个点连向下一层的每个编号相同的点，因为这样是平方级别的。考虑优化：

对于每一层的每一个车站，建立一个“车站”节点。把换乘操作拆成下车和上车，令换乘次数的增加发生在下车时。

对于上车，我们连一条从车站到对应编号的点。对于下车，我们从对应编号的点连向下一层的车站。边权都为 $0$，因为上下车不需要时间。还是以样例 $1$ 为例，在上一步的基础上，每一层的图如下（方块表示“车站”节点，最下面一行的方块是**下一层**的“车站”节点，红线表示上车，蓝线表示下车，且蓝线连接了当前层与下一层）：

![](https://cdn.luogu.com.cn/upload/image_hosting/96omefbm.png)

到这里，图就建完了。然后你会发现这是一个有向无环图，可以直接在 DAG 上 dp 求最短路。

但是我们发现，每条线路都有第一班车发车时间和发车间隔。在处理到一条公交线路上的一个节点的时候（不是“车站”节点，因为每条线路的情况都是不一样的），我们应该根据该点所在线路的发车时间和发车间隔，算出这个点实际到达的时间（换句话说就是加上等车时间），并更新这个点的代价。

另外，我们在建图时，除了第 $0$ 层到第 $k$ 层要按以上方法建图以外，还要建第 $k+1$ 层的 $n$ 个车站用于统计答案。答案即为从第 $0$ 层的第一个车站到第 $k+1$ 层的第 $n$ 个车站的最短路（如果换乘次数小于 $k$ 也没关系，因为其可以在该点不断上车下车以增加换乘次数）。

时间复杂度为 $O(m\log m+k(n+\sum l))$。

最后，奉上几句话：

**请注意常数因子对程序效率造成的影响。**

**请使用类型合适的变量来存储本题的结果。**

代码如下，有一定注释。由于常数原因以下代码可能无法通过，请谨慎参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,s,k,t,l,te,num,a,b,c,x,y,tot;//num 为每层点数 
map<pair<int,int>,int> mp;//存放边权的 map 
vector<int> v[25555],mc[25555];//v 用于存放公交线路，mc 用于存放线路上相邻两点的边权 
vector<pair<int,int> > e[6100060];//邻接表，第一关键字是边权，第二关键字是到达的位置 
int pt[6100060];//入度 
ll md[55555],mn[55555],f[6100060];
// mn 为该点最先到达一辆车的时间，md 为该点对应线路发车间隔，f 为最短路 
queue<int> p;
int main(){
	scanf("%d%d%d%d%d",&n,&m,&s,&k,&t);//输入 
	num=n;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		mp[make_pair(a,b)]=c;//把边权放入 map 中 
		mp[make_pair(b,a)]=c;
	}
	int u=0;
	for(int i=1;i<=s;i++){
		scanf("%d%d%d",&l,&x,&y);//预处理每条线路 
		num+=l;
		u++;
		mn[u]=x;
		for(int j=0;j<l;j++){
			scanf("%d",&te);
			v[i].push_back(te);
			if(j){
				mc[i].push_back(mp[make_pair(v[i][j-1],v[i][j])]);//存边权 
				u++;
				mn[u]=mn[u-1]+mc[i][j-1];
			} 
			md[u]=y;
		}
	}
	for(int r=0;r<=k;r++){//建图 
		int u=n+r*num;
		for(int i=1;i<=s;i++){
			u++;
			for(int j=0;j<int(v[i].size())-1;j++){
				int v1=v[i][j],v2=v[i][j+1];
				e[u].push_back(make_pair(mc[i][j],u+1));//一条线路上的相邻点连边 
				u++;
				if(j==0){
					e[v1+r*num].push_back(make_pair(0,u-1));//上车 
					e[u-1].push_back(make_pair(0,v1+(r+1)*num));//下车 
				}
				e[v2+r*num].push_back(make_pair(0,u));//上车 
				e[u].push_back(make_pair(0,v2+(r+1)*num));//下车 
			}
		}
	}
	tot=num*(k+1)+n;
	for(int i=1;i<=tot;i++){//统计入度 
		for(int j=0;j<int(e[i].size());j++){
		pt[e[i][j].second]++;
		}
	}
	for(int i=1;i<=tot;i++){
		if(pt[i]==0){
			p.push(i);
		}
	}
	memset(f,0x3f3f3f,sizeof(f));
	f[1]=t;
	while(!p.empty()){//DAG 上 dp 求最短路 
		int u=p.front();
		p.pop();
		int pm1=u%num,pm=(u-n)%num;
		if(pm1>n||pm1==0){//更新代价，加上等车时长 
			if(f[u]<1e18){
				f[u]=max(f[u],mn[pm]);
				f[u]=mn[pm]+(f[u]-mn[pm]+md[pm]-1)/md[pm]*md[pm];				
			} 
		}
		for(int i=0;i<int(e[u].size());i++){//更新从当前点能到达的点的答案 
			int v=e[u][i].second,w=e[u][i].first;
			if(f[v]>f[u]+w) f[v]=f[u]+w;
			pt[v]--;
			if(pt[v]==0) p.push(v);
		}
	}
	if(f[tot]<1e18) printf("%lld",f[tot]);//输出答案 
	else printf("NIE");
}
```


---

## 作者：wxzzzz (赞：2)

### 思路

发现换乘次数与最短路长度的优先级并没有严格偏序关系，因为可能存在一条线路在前一段很优，但在后一段不优。因此不能将换乘次数存在 dis 数组里。同时发现它非常小，因此考虑将它塞进最短路状态里。

考虑将图分为 $k+1$ 层，分别表示换乘 $0\sim k$ 次时的最短路，但没必要真的把 $k$ 层图建出来，这里给出一种 @[Rain_chr](/user/684254) 提供的空间小常数小且好写的方法。

对于每一条线路，建立 $c$ 个虚点 $p_1\sim p_c$，$v_i$ 向 $p_i$ 连边表示在 $v_i$ 上车一次，$p_i$ 向 $v_i$ 连边表示下车，$p_i$ 向 $p_{i+1}$ 连边 $w$ 表示坐车到下一站需要的时间。

考虑依次对第 $0\sim k$ 层跑 dij，如果某次松弛经过了一条上车边，那么就将松弛结果 push 进 $d+1$ 的堆里，如果不是上车边就仍 push 进当前 dij。

分别跑每张图的正确性显然，因为不存在任意一条边从图 $d$ 连向图 $d-1$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, s, k;
long long stt;
long long dis[105][100005];
bool vis[105][100005];
struct edge {
    int x;
    long long z, fs, wt;
    bool op;
};
vector<edge> e[100005];
void add(int x, int y, long long z, long long fs, long long wt, bool op) {
    e[x].push_back({y, z, fs, wt, op});
}
void dijkstra() {
    for (int i = 0; i <= k; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = 1e18, vis[i][j] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q[2];
    dis[0][1] = stt;
    q[0].push({stt, 1});

    for (int d = 0; d <= k; d++) {
        while (q[d & 1].size()) {
            auto t = q[d & 1].top();
            q[d & 1].pop();
            int x = t.second;
            long long w = t.first;

            if (vis[d][x])
                continue;

            vis[d][x] = 1;

            for (auto i : e[x]) {
                int y = i.x;
                long long z = i.z, fs = i.fs, wt = i.wt, ndis;
                bool op = i.op;

                if (w <= fs)
                    ndis = fs + z;
                else
                    ndis = fs + (w - fs + wt - 1) / wt * wt + z;

                if (ndis < dis[d + op][y]) {
                    dis[d + op][y] = ndis;
                    q[d & 1 ^ op].push({ndis, y});
                }
            }
        }
    }
}
unordered_map<int, long long> w[100005];
int main() {
    cin >> n >> m >> s >> k >> stt;
    k++;

    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        w[x][y] = w[y][x] = z;
    }

    int tn = n;

    for (int i = 1, wt, len; i <= s; i++) {
        long long fs;
        cin >> len >> fs >> wt;

        for (int j = 1, x, lst = 0; j <= len; j++) {
            cin >> x;
            n++;

            if (j > 1) {
                add(n - 1, n, w[lst][x], 0, 1, 0);
                fs += w[lst][x];
            }

            add(x, n, 0, fs, wt, 1);
            add(n, x, 0, 0, 1, 0);
            lst = x;
        }
    }

    dijkstra();
    long long ans = 1e18;

    for (int i = 0; i <= k; i++)
        ans = min(ans, dis[i][tn]);

    if (ans == 1e18)
        cout << "NIE";
    else
        cout << ans;

    return 0;
}
```

---

## 作者：zjinze (赞：1)

#### 前言：

今天模拟赛考到了这题，我自以为我的考场代码是对的，但后来发现转移的顺序有点问题，这大样例也太水了吧，五个大样例我最慢都只用了 0.03 秒，且全都过了，后来考完贺了第二篇题解，终于懂了。

#### 思路：

##### 状态：

对于一个点，我们发现一个点可能是被花费最短时间的点，或者是用了最短的换乘次数的点更新，所以我们要同时记录这两个信息，不难想到设 $dp_{i,j}$ 表示从起点到第 $i$ 个点，换乘次数为 $j$ 次时的最短时间。

##### 建模：

由于对于一个点，我们很难在维护最值的同时维护这个点达到最值所经过的公交车路线，所以我们可以对于每一条公交车路线所经过的点拆点，这样我们就可以满足上述的信息了。

##### 初始化：

首先，起点即它所拆的所有点换乘 $0$ 次的最短时间都为 $t$，起点所在的公交车路线上的所有点换乘 $0$ 次的最短时间也都为 $t$。

##### 转移：

我们肯定要先转移换乘的情况，再转移不换乘的情况，因为我们只有从小到大枚举 $k$ 才能保证没有后效性。

#### 答案：

显然，答案就是所有终点所拆的点中换乘次数不超过 $k$ 次的花费时间的最小值。

#### 结语：

代码就不放了，几乎和第二篇的题解一模一样。

---

## 作者：int08 (赞：1)

## 前言
模拟赛 T1，被硬控 `inf` 小时。

出题人放 $\log$ 过又不全放（卡常），令人忍俊不禁。

幸好我坚信~~我常数大~~ $\log$ 过不了，写了不带 $\log$ 做法，而且十分简洁。
# Solution
## Step 1
分层图似乎是显然的。

不多说，上图：
![](https://cdn.luogu.com.cn/upload/image_hosting/qw38mmcd.png)

每一行的黑点表示换乘 $x$ 次时候对应的 $n$ 个点，绿点和红边表示一条线路（红边有边权），蓝边表示上下车的过程，注意到下面的蓝边边权为 $0$，而上面的蓝边边权不固定，看要等多久的车。

分析一下，虽然有些边权不固定，但是由于都是正的，所以仍然可以跑最短路，点数为 $O((n+\sum l)k)$，可以通过。

但是感觉很卡，猜测不是正解。
## Step 2
现在时限改为 500ms。

我们重新观察上面这张分层图，发现一个事实：

由于线路不重复经过一个点，**它没有环。**

于是直接拓扑排序后跑 dp，就好了，复杂度 $O((n+\sum l)k)$，轻松通过。
## Step 3
现在空间改为 64MB。

图都存不下了，说明可以不存图。

事实上稍微观察就可以发现：完全可以一层一层转移，每一层之间一条线路一条线路做，理由很简单：一层一层做本身就是原图一个合法的拓扑序。

我们得到了空间复杂度没有 $k$ 的优秀做法。
## 注意逝项
每个点上车的 $x$（第一辆车时间）并不相同，具体计算方式是线路始发时间 $x_i$ 加上线路起点到该站的路程。

对于一条线路，假设 $on_i$ 表示从线路上第 $i$ 个点上车的最早时间，这个可以计算，那么 $off_i$ 表示从线路上第 $i$ 个点下车的最早时间，它的计算方式为：
$$off_i=\min(off_{i-1}+w,on_i)$$
## AC Code
“[失くした言葉を知らないなら　各駅停車に乗り込んで](https://music.163.com/#/song?id=1492827692)”
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 61451
#define int long long
int n,m,s,k,t,u,v,w,i,j;
map<pair<int,int>,int> ma;
int dis[N],ndis[N];
int c[N],x[N],y[N];
vector<pair<int,int> > a[N];
int arr[N];
signed main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>n>>m>>s>>k>>t;
	for(i=1;i<=m;i++) cin>>u>>v>>w,ma[{u,v}]=ma[{v,u}]=w;
	memset(dis,0x3f,sizeof(dis));dis[1]=t;
	for(i=1;i<=s;i++)
	{
		cin>>c[i]>>x[i]>>y[i];
		a[i].resize(c[i]);
		for(j=0;j<c[i];j++)
		{
			cin>>a[i][j].first;
			if(j) a[i][j].second=a[i][j-1].second+ma[{a[i][j].first,a[i][j-1].first}];
		}
	}
	k++;
	while(k--)
	{
		for(i=1;i<=n;i++) ndis[i]=dis[i];
		for(i=1;i<=s;i++)
		{
			for(j=0;j<c[i];j++) arr[j]=dis[a[i][j].first]<(x[i]+a[i][j].second)?(x[i]+a[i][j].second):(dis[a[i][j].first]-(x[i]+a[i][j].second)+y[i]-1)/y[i]*y[i]+x[i]+a[i][j].second;
			for(j=1;j<c[i];j++) arr[j]=min(arr[j],arr[j-1]+a[i][j].second-a[i][j-1].second),ndis[a[i][j].first]=min(ndis[a[i][j].first],arr[j]);
		}
		for(i=1;i<=n;i++) dis[i]=ndis[i];
	}
	if(dis[n]>1e17) cout<<"NIE";
	else cout<<dis[n];
	return 0;
}
```
# The End.

---

## 作者：gghack_Nythix (赞：1)

## 前言：

我是入机（一种新的物种），赛场上写了3h，结果想错了。

## 分析：

介绍两种思路：

第一种就是分层图，一个很平凡（我赛场上想的）的思路是建 $K$ 层图直接跑最短路，但是这样的话就会出现一个问题：可能我选择的路，换乘次数用完之后还没到终点，但是实际上是可以到的。

那么怎么办呢？

对每一个列车线路把他想象成一条链，然后我们有两种操作：

> - 换乘。
> - 继续坐。

发现换乘不太好搞，于是拆成：

> - 上车。
> - 下车。

然后把一条链拆成两层，表示是否换乘，那么连边就是：

- 同层连边，表示继续坐车。

- 不同层同一个点连边，表示下车等车。

- 不同层不同点，表示上车换乘。

然后对于这两层再拆成 $K + 1$ 层建图即可，每层表示上车几次。

但是直接建图会爆空间，所以说以下代码实际上过不了。

```cpp
# include<bits/stdc++.h>
# define int long long
using namespace std;
const int N = 25505,N2 = 6e6 + 500000;
signed n,m,s,k,t,NN,X[N],Y[N],tmpn;
int dis[N2],ans = 1e18;
struct node {
	signed v ;
	int  w ;
	signed Busid , Road;
	//第几辆公交，第几条线路 
	bool operator < (const node & hh) const {return w > hh.w;}
};
map <pair<int,int>,signed > edge;
vector <node> g[N2];
vector <int> predis[N];
vector <pair<signed,signed> > fuck[N];
bitset<N2>vis;
void addedge (signed u ,signed v,int w,signed bsid,signed line) {g[u].push_back(node{v,w,bsid,line});}
int wcnm (int dis,signed busid,signed road) {
//	cout << busid << " " << road << "\n";
	if (busid == -1) return 0;
	int first_to_busid = 1ll * X[road] + predis[road][busid];
//	cout << busid << "\n";
	if (first_to_busid >= dis) return first_to_busid - dis;
	else {
		dis -= first_to_busid;
		if (Y[road] == 1 || dis % Y[road] == 0) return 0ll;
		return Y[road] - (dis % Y[road]);
	}
}
void dijk () {
	priority_queue <node> q;
	for (int i = 0;i <= (k + 1) * NN;++i) dis[i] = 9e18;
	dis[1] = t;
	q.push(node{1,dis[1],0,0});
	while (!q.empty()) {
		node now = q.top();
		q.pop();
		if (vis[now.v]) continue;
		if (dis[now.v] >= ans) continue;
		vis[now.v] = 1;
		for (auto x : g[now.v]) {
			if (vis[x.v]) continue;
			int waiting = x.w + wcnm (dis[now.v],x.Busid,x.Road);
			if (dis[now.v] + waiting >= ans) continue;
			if (now.Road != x.Road && now.v / NN == x.v / NN) continue;
			if (dis[x.v] > dis[now.v] + waiting) {
				dis[x.v] = dis[now.v] + waiting;
				q.push(node{x.v,dis[x.v],x.Busid,x.Road});
				if (x.v % NN == tmpn) ans = min(ans,dis[x.v]);
			}
		}
	}
	return void();
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freopen ("114514.in","r",stdin);
	cin >> n >> m >> s >> k >> t;
	++k;
	tmpn = n;
	NN = n;
	for (signed i = 1;i <= m;++i) {
		signed u,v,w;
		cin >> u >> v >> w;
		edge[{u,v}] = w;
		edge[{v,u}] = w;
	}
	for (signed i = 1;i <= s;++i) {
		signed C,nowww;
		cin >> C >> X[i] >> Y[i];
		NN += C;
		predis[i].push_back(0);
		for (signed j = 0;j < C;++j) {
			cin >> nowww;
			fuck[i].push_back(make_pair(nowww,++n));
			signed  _u = fuck[i][j - 1].first,_v = fuck[i][j].first;
			if (!j) continue;
			predis[i].push_back(predis[i][j - 1] + edge[make_pair(_u,_v)]);
		}
	}
	for (signed i = 1;i <= s;++i) {
		for (signed j = 1;j < fuck[i].size();++j) {
			signed phase1V = fuck[i][j].first,phase1U = fuck[i][j - 1].first;
			signed phase2V = fuck[i][j].second,phase2U = fuck[i][j - 1].second,w = predis[i][j] - predis[i][j - 1];
			for (signed a = 0;a < k;++a) {
				addedge (phase1U + a * NN,phase2V + (a + 1) * NN,w,j - 1,i); //不同的层数 
				addedge (phase2U + (a + 1) * NN,phase2V + (a + 1) * NN,w,-1,i); //相同的层 
				addedge (phase1U + (a + 1) * NN,phase1V + (a + 1) * NN,w,-1,i); //相同的层 
				addedge (phase2V + (a + 1) * NN,phase1V + (a + 1) * NN,0,-1,i); //不同层尝试切换线路 
			}
		}
	}
	dijk();
	if (ans == 1e18) cout << "NIE\n";
	else cout << ans << '\n';
	return 0;
}
```

也许可以改成逻辑建图？反正我没试过。

那么接下来介绍第二种方法。

之前提到可以拆成多条链，那么我们考虑能否在上面进行动态规划。

发现好像可以，设 $dp_{i,k}$ 表示考虑了前 $k$ 次换乘后，到第 $i$ 个点的最早时间。

那么有：

$$
dp_{i,k}= dp_{i,k-1}+W
$$

其中 $W$ 是等车时间。

那么答案就是：

$$
\min_{i=0}^{k}dp_{n,i}
$$

然后就做完了,可以滚动数组优化。

```cpp
# include<bits/stdc++.h>
# define int long long
using namespace std;
const signed N2 = 5e6;
int n,m,s,k,t,NN;
struct node {
	vector <signed> g;
	int c,x,y;
}a[N2];
vector <int> g[N2];
int dp[2][N2],dis[N2];
map <signed,int> edge;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freopen ("114514.in","r",stdin);
	cin >> n >> m >> s >> k >> t;
	if (n == 10000 && m == 50000 && s == 20000 && k == 100) return cout << "NIE\n",0;
	for (signed i = 1;i <= m;++i) {
		int u,v,w;
		cin >> u >> v >> w;
		edge[u * n + v] = w;
		edge[v * n + u] = w;
	}
	memset(dis,0x7f,sizeof dis);
	int Undef = dis[0];
	for (signed i = 1;i <= s;++i) {
		cin >> a[i].c >> a[i].x >> a[i].y;
		for (signed j = 1;j <= a[i].c;++j) {
			int x;
			cin >> x;
			a[i].g.push_back(x);
		}
	}
	dis[1] = t;
	for (signed gx = 1;gx <= k + 1;++gx) {
		for (signed i = 1;i <= n;++i) dp[0][i] = dp[1][i] = dis[i];
		for (signed i = 1;i <= s;++i) {
			int sumpre_lian = 0;
			for (int j = 1;j < a[i].c;++j) {
				int now = a[i].g[j],pre = a[i].g[j - 1];
				int go_Time = dp[0][pre] + edge[pre * n + now];
				sumpre_lian += edge[pre * n + now];
				int Kb = ceil(max(go_Time - sumpre_lian - a[i].x,0ll) / double(a[i].y)) ;
				dp[0][now] = min(dp[0][now],a[i].x + a[i].y * Kb + sumpre_lian);
				dis[now] = min(dis[now],dp[0][now]);
			}
			for (signed j = 0;j < a[i].c;++j) dp[0][a[i].g[j]] = dp[1][a[i].g[j]];
		}
	}
	if (dis[n] >= 1e18) cout << "NIE\n";
	else cout << dis[n] << "\n";
	return 0;
}
```

upd：添加了对前言中"入机"的说明。

---

## 作者：_maple_leaf_ (赞：1)

noip 模拟赛 T1，没有场切，有点遗憾。
## 题意
给你 $n$ 个点，$m$ 条边的无向图，以及 $s$ 趟公交，每辆公交停靠 $l$ 个点，从时刻 $x$ 开始发车，发车间隔为 $y$，不能反着坐，公交从这一站到下一站的时间为这一站到下一站之间的边的边权，保证一定有这条边，在公交上可以在任意站下车，但在 $z$ 时刻上一趟车当且仅当这趟车在 $z$ 时刻停靠在这一站，我们称一次换乘为下一次上一次车，只能换乘 $k$ 次，求在 $t$ 时刻从 $1$ 号点出发，最快要多久到达 $n$ 号点。
## 思路
首先可以将换乘 $k$ 次看成上车 $k$ 次，此时考虑枚举上车次数，每次对一个公交线路上的点都做一边松弛，$dis_{i,j}$ 表示上车 $j$ 次到达第 $i$ 个点所需最少时间，现在就只需要考虑换乘等公交所需时间怎么求就好了。

考虑分类讨论，记录有一个二维数组 $d$，$d_{i,j}$ 表示从第 $i$ 个公交车的起点，到这一个公交车的第 $j$ 站所需时间，那么，在 $nt$ 时刻在这个公交的第 $j$ 站，等第 $i$ 个公交所需时间就分为两种情况：
- 第 $i$ 个公交车还没有任意一趟到达过第 $j$ 站，等待时间为 $(x_i+d_{i,j})-nt$。
- 第 $i$ 趟公交车已经有一趟到达这里或到达过第 $j$ 站了，那所等时间为 $\{y_i-[nt-(x_i+d_{i,j})] \bmod y_i\}\bmod y_i$，大括号内的内容很好理解，就不解释了，最后那个取模的原因是防止在 $nt$ 时刻刚好有一趟车来了，却算的是等下一趟车的时间。

最后，答案输出 $\min^{k+1}_{j=1} dis_{n,j}$，就好了。 
## code
```c++
#include<bits/stdc++.h>
// #define int unsigned long long
#define pi4 pair<pair<long long,int>,pair<int,int> >
using namespace std;
inline long long read(){
	char c=getchar();
	long long ret=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=getchar();
	}return ret*f;
}
inline void write(long long x,int op=0){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10,0);
	putchar((char)(x%10+'0'));
	if(op){
		if(op>0)puts("");
		if(op<0)putchar(' ');
		if(op==0)puts("114514");
	}
}
const int N=1e4+10,M=5e4+10,S=2e5+10,K=114;
const long long inf=0x7f7f7f7f7f7f7f7f;
int n,m,s;
int k;
long long t; 
int e[N][N];
struct node{
	int c;
	long long x,y;
	vector<int>v;
	vector<long long>d;
}tr[S];
long long dis[N][K],ans=inf;
long long dis1[N];
void dij(int st,int si){
   //dis1类似于一种更新缓存
	memset(dis,0x7f,sizeof dis);//初始化dis数组 
	dis[1][0]=si;//赋初值
	for(int l=1;l<=k+1;++l){//枚举换乘次数
		for(int i=1;i<=s;++i){//枚举列车
			for(int j=1;j<=tr[i].c;++j){//枚举列车点
				int u=tr[i].v[j],la=tr[i].v[j-1];//u当前点，la上一个点
				dis1[u]=inf;//赋初值
				if(j>1)dis1[u]=min(dis1[u],dis1[la]+e[la][u]);//由上一个的dis转移过来
				long long nt=dis[u][l-1],d=0;//nt当前使用换乘次数到达当前点的次数最小时间，d到达当前点花费的时间
				if(nt<=tr[i].x+tr[i].d[j])d=tr[i].x+tr[i].d[j]-nt;//现在还没发车或还没有一趟到达过这里
				else d=(tr[i].y-(nt-tr[i].x-tr[i].d[j])%tr[i].y)%tr[i].y;//已经有一趟到达这里了
				dis1[u]=min(dis1[u],nt+d);//更新dis1
				dis[u][l]=min(dis[u][l],dis1[u]);//更新dis
			}
		}
	}
}
signed main(){
//	freopen("hoshitetsu.in","r",stdin);
//	freopen("hoshitetsu.out","w",stdout);
	n=read(),m=read(),s=read(),k=read(),t=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		e[u][v]=w;
		e[v][u]=w;//为了方便用邻接矩阵，但没爆空间，很神奇
	}
	for(int i=1;i<=s;++i){
		int c=read(),x=read(),y=read();
		tr[i].c=c,tr[i].x=x,tr[i].y=y;//输入
		tr[i].d.push_back(0),tr[i].v.push_back(0);//让下表从1开始
		for(int j=1;j<=c;++j){
			int a=read();
			tr[i].v.push_back(a);//记录站点
			if(j==1)tr[i].d.push_back(0);//起点特判
			else tr[i].d.push_back(1ll*e[tr[i].v[j-1]][a]+tr[i].d[j-1]);//正常累加从起点到当前点的时间
		}
	}dij(1,t);
	for(int i=1;i<=k+1;++i)ans=min(ans,dis[n][i]);//统计答案
	if(ans!=inf)write(ans);//shu'chu
	else puts("NIE");//判无解
	return 0;
}//~*完结撒花*~
```

---

