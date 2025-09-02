# Opening Portals

## 题目描述

Pavel 正在玩一个著名的电子游戏，在这个游戏中，玩家将管理整个国家，并在国家中旅行，完成任务以获取经验。

这个国家有 $n$ 个由 $m$ 条长度不同的无向道路联通的城市。这些城市中共有 $k$ 个传送门，在游戏开始时都是关闭的，每当玩家到达一个有传送门的城市时，就可以把这个城市的传送门永久的开启。玩家可以在两个开启的传送门之间任意的传送，且不需要花费时间。

游戏开始时，Pavel 处于 $1$ 号城市，他想要尽可能快的开启所有的传送门，试求他最小要花费的时间。

## 说明/提示

在第二个样例中，Pavel 首先来到了 $2$ 号城市并开启了传送门，之后前往了 $3$ 号城市并开启传送门，又传送回 $2$ 号城市，最后前往 $4$ 号城市并开启传送门，达成目标。

Translated by [@Colinxu2020](https://www.luogu.com.cn/user/579631).

## 样例 #1

### 输入

```
3 3
1 2 1
1 3 1
2 3 1
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
1 2 1
2 3 5
2 4 10
3
2 3 4
```

### 输出

```
16
```

## 样例 #3

### 输入

```
4 3
1 2 1000000000
2 3 1000000000
3 4 1000000000
4
1 2 3 4
```

### 输出

```
3000000000
```

# 题解

## 作者：LlLlCc (赞：8)

## 题意：
给出一个有$n$个结点，$m$条带权边的无向连通图，边权为经过这条边所需的时间。有$k$个点设有传送门，初始时，传送门都关闭。你从$1$号点出发，每当你到达一个已开启传送门的点，那个传送门就会永久开启，你可以从一个开启的传送门花费$0$时间到达另一个开启的传送门。求开启所有传送门所需的最小时间。

## 题解
从有传送门的点$0$花费传送到已走过的有传送门的点，这个性质非常妙，其实就是$Prim$算法找与当前连通块最近的点。所以题目就变成了在一个$n$个点，$m$条边的的无向图中求最小生成树

于是我们可以跑一遍全源最短路，知道每个有传送门的点之间的距离，然后直接$Prim$或者$Kruskal$。不过显然，这样过不去

上面这样做瓶颈在哪呢？是跑全源最短路，求任意两个有传送门的点之间的距离

考虑优化这一步

根据$Prim$或者$Kruskal$的性质，每次我们都是找最近的那一条边，因为最近的那一条边是不可能被其他的边更新的。因此，我们可以对每条边拆解，求出两个端点最近的有传送门的点

找最近的有传送门的点，我们可以把所有有传送门的点放进堆里跑一遍多源点的$dijkstra$

如对于边$(x \rightarrow  y)$，我们求出哪个有传送门的点到$x$最近，$y$也一样，然后这条边的边权加上$dis_x+dis_y$，这条边也就变成了连接两个有传送门的点的边

建图建完后，只有跑$Prim$或者$Kruskal$就行

## code
```
#include<bits/stdc++.h>
#define maxn 1000005
#define maxe 10000005
#define ll long long
using namespace std;
const ll INF=1e16;
int Id[maxe],n,m,x,y,z,lnk[maxn],Now,nxt[maxn],tot,N,son[maxn],Q[maxn],Nx[maxn],w[maxn],fa[maxn];
ll heap[maxe],dis[maxn],Ans=INF;
bool vis[maxn];
struct lc{
	int x,y;ll z;
	bool operator <(const lc b)const{return z<b.z;}
}e[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void Swap(int x,int y){swap(heap[x],heap[y]);swap(Id[x],Id[y]);}
inline void add(int x,int y,int z){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;w[tot]=z;}
inline void Put(int id,ll x){heap[Now=++tot]=x;Id[tot]=id;while (Now>1&&heap[Now]<heap[Now>>1]) Swap(Now,Now>>1),Now>>=1;}
inline int Get(){
	int Mi=Id[1];Id[1]=Id[tot],heap[1]=heap[tot],tot--,Now=1;int Son=2;
	while (Son<=tot){
		if (Son<tot&&heap[Son+1]<heap[Son]) Son++;
		if (heap[Now]>heap[Son]) Swap(Now,Son),Now=Son,Son=Now<<1;
	    else break;
	}
	return Mi;
}
inline void Dij(){
	for (int i=1;i<=n;i++) Nx[i]=vis[i]=0,dis[i]=INF;tot=0;
	for (int i=1;i<=N;i++) dis[Q[i]]=0,Nx[Q[i]]=Q[i],Put(Q[i],0);
	while (tot){
		int Nn=Get();if (vis[Nn]) continue;vis[Nn]=1;
	    for (int i=lnk[Nn];i;i=nxt[i])
		  if (!vis[son[i]]&&dis[Nn]+w[i]<dis[son[i]]) dis[son[i]]=dis[Nn]+w[i],Nx[son[i]]=Nx[Nn],Put(son[i],dis[son[i]]);
	}
}
inline int Getfa(int x){return fa[x]==x? x:fa[x]=Getfa(fa[x]);}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++) x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z),e[i]=(lc){x,y,z};
	Q[++N]=1;tot=0;
	Dij();N=read();
	for (int i=1;i<=N;i++) Q[i]=read(),Ans=min(Ans,dis[Q[i]]);
	Dij();
	for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=m;i++){
		e[i].z+=dis[e[i].x]+dis[e[i].y];
		e[i].x=Nx[e[i].x],e[i].y=Nx[e[i].y];
	}
	sort(e+1,e+m+1);
	for (int i=1;i<=m;i++){
		int fx=Getfa(e[i].x),fy=Getfa(e[i].y);
		if (fx==fy) continue;
		Ans+=e[i].z;fa[fx]=fy;
	}
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：KSCD_ (赞：7)

### 思路
复杂度中认为 $n,m,k$ 同级。

发现打开第一个传送门后，打开新传送门的过程类似于 Prim 求最小生成树，也就是找到已打开点集和未打开点集之间的最短路径，然后直接传送到已打开的 $S$ 点，再走到未打开的 $T$ 点并打开。

显然中间走的路径是最短路，所以对 $k$ 个点建完全图，边权为两个点在原图上的最短路径。之后在 $k$ 个点的新图上跑最小生成树，答案即为最小生成树的权值和加上起点到传送门的最短距离。时间复杂度瓶颈在预处理两点之间最短路径，用 Dijkstra 的话大概是 $O(n^2\log n)$。

考虑减少新图中的边数，设 $p_i$ 表示离 $i$ 最近的传送门编号，$dis_i$ 为距传送门的距离。那么对于一条权值为 $w$ 的边 $(u,v)$，在新图上建边 $p_u\to p_v$，边权为 $dis_u+dis_v+w$，这样就能包含所有最终最小生成树中的边。

笔者太菜了，完全想不出这个方法，读了官方题解之后自己证明如下：

以下设 $d_{i,j}$ 表示点 $i$ 和点 $j$ 之间的最短路径长度，两个集合即为上述已开启和未开启的点集。

对于最终在最小生成树中的一条边（原图中的路径） $S\to T$，若路径前半部分的 $p_i=S$，后半部分的 $p_i=T$，那么路径上一定存在一条边 $(u,v)$ 满足 $p_u=S$ 且 $p_v=T$。现在只需要证明路径上 $p$ 的情况如此即可。

使用反证法，假设 $S\to u$ 的路径上有点 $x$ 使得 $p_x\ne S$，设 $p_x=E$，那么 $x\to u$ 的路径上点的 $p$ 均为 $E$。

若 $E$ 与 $S$ 属于同一集合，与 $T$ 属于不同集合，那么由于 $d_{E,u}\le d_{S,u}$，可以取 $E \to T$ 这条路径。

否则 $E$ 与 $S$ 属于不同集合，由于路径的包含和 $p$ 数组的定义，有 $d_{E,x}\le d_{E,u}\le d_{S,u}\le d_{u,T}\le d_{x,T}$，最终得到 $d_{E,x}\le d_{T,x}$，可以取 $S\to E$ 这条路径。

$v\to T$ 路径上的情况相同。式子比较抽象，可以结合下面~~丑陋~~的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/y60pi125.png)

所以最终只需要以 $k$ 个点为起点用 Dijkstra 跑单源最短路，预处理出 $p,dis$ 数组即可，时间复杂度降为 $O(n\log n)$。
### 代码

```cpp
#include<iostream>
#include<vector> 
#include<queue>
#include<algorithm>
#define pii pair<int,int>
#define int long long
using namespace std; 
const int N=1e5+10;
const int inf=2e18;
int n,m,k,res,p[N],to[N],dis[N],tu[N],tv[N],tw[N],f[N];
bool vis[N];
vector <pii> edge[N];
struct nod {int u,v,w;}ne[N];
bool cmp(nod ta,nod tb) {return ta.w<tb.w;}
priority_queue <pii> q;
int finds(int x) {return (f[x]==x?x:f[x]=finds(f[x]));}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++)
	{
		cin>>u>>v>>w,tu[i]=u,tv[i]=v,tw[i]=w;
		edge[u].push_back({v,w}),edge[v].push_back({u,w});
	}
	for(int i=1;i<=n;i++) dis[i]=inf,to[i]=-1;
	cin>>k;
	for(int i=1;i<=k;i++) cin>>p[i],to[p[i]]=i,dis[p[i]]=0,q.push({0,p[i]});
	while(q.size())
	{
		int u=q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(pii te:edge[u])
		{
			int v=te.first,w=te.second;
			if(dis[v]>dis[u]+w) dis[v]=dis[u]+w,to[v]=to[u],q.push({-dis[v],v});
		}
	} //Dijkstra 预处理 
	for(int i=1;i<=m;i++) ne[i]={to[tu[i]],to[tv[i]],dis[tu[i]]+dis[tv[i]]+tw[i]};
	sort(ne+1,ne+1+m,cmp);
	for(int i=1;i<=k;i++) f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int fu=finds(ne[i].u),fv=finds(ne[i].v),w=ne[i].w;
		if(fu!=fv) f[fu]=fv,res+=w;
	} //建新图 Kruskal 跑最小生成树 
	cout<<res+dis[1];
	return 0;
}
```

---

## 作者：Dimly_dust (赞：7)

首先，简化一下题目。当到达第一个传送门点后，因为已经过传送门可以互相传送，所以剩下的时间就是所有传送门点两两之间连权值等于最短路的边建成的完全图的最小生成树。**因此答案就是那个最小生成树，再加上$ 1$ 号点到最近的传送门的距离。**

因此，我们得到了一个 $O(n^2\log n)$ 的算法。

接下来，问题就变成了如何快速求最小生成树。不难想到，如果传送门点 $u$ 到 $v$ 的最短路上有其他传送门点，那么 $(u,v)$ 一定不在MST上。遗憾的是，单单这么剪枝是没有用的，边数还是会被下图所示的菊花卡成 $O(n^2)$。

![](https://images.cnblogs.com/cnblogs_com/cly-none/1215696/o_tmp.png)

但是，这个失败的尝试启示我们要剪去一些不可能在最小生成树上的边。考虑Kruskal的过程，一条边只要在一个其他边都“小于”它的环上（指边权小于或边权等于但枚举顺序靠前），就一定不在最小生成树上。

**下面我们来进行优化：**

我们难以直接判断这个条件，但是，对于一条最短路径，如果它上面的每一条边两端最近的传送门点都不是这条路径的两个端点，就可以排除了。

因此，我们构建一张新图 $G'$，对于原图上每一条边 $(u,v)$，设与 $u$ 最近的任意一个传送门点为 $nex_u$，与 $v$ 最近的是$nex_v$，那么，在新图上建一条 $(nex_u,nex_v)$ 的边，边权是原边权加上 $dis(nex_u,u)+dis(nex_v,v)$ 。这相当于考虑所有边所在的最短路，并且，所有没有被考虑到的 最短路一定是可以删去的。这样，我们就把边数剪到了 $O(n)$ 级别。

总复杂度 $O(n\log n)$。

---

## 作者：LJ07 (赞：4)

+ 跟 [CF1253F](https://www.luogu.com.cn/problem/CF1253F) 本质相同。
+ 联通有传递性：如果 $u\to v$，$v\to w$，则 $u\to w$（均指传送门）。
+ 有暴力：考虑暴力建出所有传送门之间的边（只需全源最短路），然后跑最小生成树。
+ 不显示建图。考虑模拟 kruskal 的过程，先找出最小的边。很神奇啊，你发现可以这样求：以传送门点集为源点跑单源最短路，然后你枚举所有边，边两端端点所到的最近传送门不同时计算这个贡献。如果 $d_u$ 表示 $u$ 到达传送门的最近距离，那么 $(u,v,w)$ 贡献就是 $d_u+d_v+w$。原因是*一定会在最小边中点统计到最小边*。

+ 接下来考虑依次按照边权从小到大加入边，如果是边 $(a,b)$（此时点均为传送门）
+ 很容易发现：
1. 如果与之前边不交，*可以按照最小边的统计方式统计到*。
1. 如果相交。$a$ 或 $b$ 一定位于一个大小大于 $1$ 的联通块（不妨设其为 $a$）。设边上第一个交点为 $t$，一定有 $dis(t,b)\ge dis(t,a)$（否则应该先加入 $b$），此时该边中点之前一定没被覆盖过。还是可以*按照最小边的统计方式统计到*。
+ 综上最终在 MST 上的边一定会被边上中点统计到。
+ 那么你就对原图上的每一条边 $(u,v,w)$ 在传送门图上建出 $(u',v',w+d_u+d_v)$。这里 $u'$ 指离 $u$ 最近的传送门，$v'$ 同理。
+ 最后直接输出最小生成树的边权和即可。

注：上文中中点可以感性理解为路径 $(u,v)$ 上的一条边 $(a,b)$，有 $dis(u,a)\le dis(v,a)$，$dis(u,b)\ge dis(v,b)$ 这样的一个性质。中点可能不止一个，但是不影响正确性。

---

## 作者：出言不逊王子 (赞：3)

我们现在在 $1$ 号节点。我们需要走到一个传送门把他开起来。

我们现在走到了一个传送门。我们需要再走到一个传送门。

我们现在走到了两个传送门。我们想走到第三个传送门。

我们可以传送到第一个传送门再走过去。也可以直接从第二个传送门走到第三个传送门。

我们现在有了三个传送门。

以此类推，我们每次只要选取距离下一个传送门最近的一个传送门，然后走过去即可。

也就是说，最终我们留下的轨迹是这些传送门的**最小生成树**。

那么我们一开始从 $1$ 号节点开始到第一个传送门，就只要选取 $1$ 号节点到这些传送门当中的最短路径即可了。

现在问题变成了如何求这 $k$ 个点之间的最小生成树。

有趣的事实：对于两个特殊点 $u$ 和 $v$，我们希望不关心这两个点当中的非特殊点，而只考虑 $u$ 和 $v$ 二者的关联。

那么我们考虑：**经过这条边后最快能怎样到特殊点**？

我们发现，给一个无向图安一个超级原点，和一部分点连边，就能实现**所有和超级原点连边的点**与**每一个不和超级原点连边的点**的最短路。

那么我们对于每一条边，预处理出这条边的两个端点到最近的特殊点的最短路，然后重新建一条边，两个端点 $u$ 和 $v$ 是原图的两个端点能到达的**最近的传送门**，而边权就是 $w_{u,v}+d_u+d_v$，其中 $d_i$ 是 $i$ 到**最近的传送门**的最短距离。

然后跑最小生成树即可。

然后你会发现样例 $2$ 过不去。

因为在最终最小生成树的图中，编号为 $1$ 的点被孤立了，所以**当前被纳入最小生成树的点 $\ge n$** 这一条件无法实现。

所以我们排序后遍历每一条边，如果所有的边都找完了那就退出即可。

一个小细节：在每次找边时如果当前边的编号大于 $m$ 了要及时退出，否则会在第六个点出错。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define pii pair<int,int>
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=400001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct edge{int w,nx,v,u;}e[N<<1],e2[N<<1];//e2作MST
int hd[N],totm,dis[N],hd2[N],totm2,point[N],done[N];//建一个超级原点连向所有充电站，边权是0
int n,m,k,q,dad[N],pts[N],dis0=inf,pt[N];
void add(int u,int v,int w){
	e[++totm].v=v;e[totm].w=w;e[totm].u=u;
	e[totm].nx=hd[u];hd[u]=totm;
}
bool cmp(edge x,edge y){return x.w<y.w;}
priority_queue<pii,vector<pii>,greater<pii>> pq;
void dij(int s){
	ms(dis,0x3f);dis[s]=0;ms(point,0);fs(i,1,k,1) point[pts[i]]=pts[i];
	pq.push({0,s});
	while(!pq.empty()){
		pii now=pq.top();pq.pop();
		int u=now.second,dist=now.first;
		if(dist!=dis[u]) continue;
		for(int i=hd[u];i;i=e[i].nx){
			int v=e[i].v;
			if(dis[u]+e[i].w<dis[v]){
				dis[v]=dis[u]+e[i].w,pq.push({dis[v],v});
				if(!pt[v]) point[v]=point[u];
			} 
		}
	}
}
int find(int x){return dad[x]==x?x:dad[x]=find(dad[x]);}
void mrg(int x,int y){x=find(x),y=find(y);dad[max(x,y)]=min(x,y);}
int kruskal(){
	//cout<<"motherfucking m is "<<m<<'\n';
	sort(e2+1,e2+m+1,cmp);
	int finding=0,cur=1,res=0;
	while(cur<=m&&finding<n){
		bool did=0;
	//	cout<<"cur is "<<cur<<'\n'; 
		assert(cur<=m);
		while(!did){
			assert(cur<=m);
			if(find(e2[cur].u)!=find(e2[cur].v)){
				mrg(e2[cur].u,e2[cur].v);did=1,finding+=((bool(done[e2[cur].u])^1)+(bool(done[e2[cur].v])^1));
				done[e2[cur].u]=done[e2[cur].v]=1;
				res+=e2[cur].w;
				//printf("we choosed %lld now total is %lld\n",cur,res);//如果不加那个break的限制的话，这里cur会跑到800007
			}
			cur++;
			if(!did&&cur>m) break;
		}
	}
	//fs(i,1,n,1) cout<<find(i)<<' ';
	//cout<<'\n';
	return res;
}
signed main(){
	n=read(),m=read();fs(i,1,n,1) dad[i]=i;//并查集 
	fs(i,1,m,1){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
		e2[i]={w,0,v,u};
	}
	k=read();dij(1);fs(i,1,k,1) pts[i]=read(),dis0=min(dis0,dis[pts[i]]),pt[pts[i]]=1;//1到每个点的最短距离 
	fs(i,1,k,1) add(n+1,pts[i],0),add(pts[i],n+1,0);
	dij(n+1);
	fs(i,1,m,1) e2[i].w+=dis[e2[i].v]+dis[e2[i].u],e2[i].v=point[e2[i].v],e2[i].u=point[e2[i].u];//跑每个点到他的最小距离
	//fs(i,1,m,1) cout<<e2[i].u<<' '<<e2[i].v<<' '<<e2[i].w<<'\n'; 
	//那么也就是说，这样转变以后 
	//puts("ok");
	//然后我们要做一个新图，这里就是最小的代价
	int d=kruskal();//assert(d!=-1);
	cout<<d+dis0;
	return 0;
}
//这里我们要求出来每个点到传送门的最短距离
//考虑像上一题一样
//求出每个点到关键点的最短路
//然后呢？对于一个边，可以把[距离他们最近的传送门的点]连起来，权值为[dis[i]+dis[j]+w[i][j]] 
//那么具体地，怎么去记录呢
//比如我们现在走到了一个关口，那么我们就可以记录，记录啥呢
//他到底是跟着谁
//因为你这个
```

---

## 作者：masonpop (赞：2)

个人认为相当巧妙的一道题。

以下假设 $n,m$ 同阶。

首先这个在传送门之间任意移动就等价于每次找一个点加入当前连通块。如果建一个点数为传送门个数，边权为传送门间最短路的完全图，那么答案就是该完全图的 MST 大小加上 $1$ 到任意一个传送门的最短路径。直接跑全源最短路然后暴力求 MST 就能得到一个 $O(n^2\log n)$ 的垃圾做法。

发现瓶颈在于建出来的图是完全图太恶心了，考虑通过操作剪掉一定不属于 MST 的边，即什么样的传送门之间的路径可能被使用。这里有一个很智慧的结论，就是，我们直接考虑每条边 $(x,y)$，并把距离 $x,y$ 最近的传送门 $(d_x,d_y)$ 之间的边加入。可以证明，这样一定能覆盖所有可能用到的边。大部分题解没有对这个关键结论给出比较严格的证明，这里补一个。

考虑 Prim 求最小生成树的过程，即每次找到一个距离当前点集 $S$ 最近的点。假设路径 $(s,t)$ 在某一次操作中被选中，我们证明其一定能选取一条上述边 $(x,y)$。

反证若不存在这样的 $(x,y)$ 一定不合法。对不满足条件的边 $(x,y)$，如果 $d_x\in S$ 或 $d_y\not\in S$ 则 $(s,t)$ 一定能被替换。否则一定有对 $s\to t$ 最短路径上的所有边 $(x,y)$，有 $d_x\not\in S$ 且 $d_y\in S$。此时你直接取相邻两条边不难推出矛盾。

（上述是个人认为最便于理解且严谨的证明方式）

这样边数就降到了 $O(n)$，然后你跑一个多源 dij 就行了。复杂度 $O(n\log n)$。[代码](https://codeforces.com/contest/196/submission/280298161)。

---

