# [CCC 2025 Senior] 熔岩路 / Floor is Lava

## 题目背景

译自 CCC 2025 Senior T4。本题满分为 $15$。


## 题目描述


你被困在一个炽热的地牢中。

地牢由 $n$ 个房间组成，房间编号 $1\sim n$。这些房间通过 $m$ 条**双向**隧道相连，第 $i$ 条**双向**隧道连接房间 $a_i$ 和 $b_i$，且地板被温度为 $c_i$ 的熔岩覆盖。  

为了穿越熔岩隧道，你穿着一双耐热靴子，初始**冷却等级**为 $0$。当你经过温度为 $c$ 的熔岩时，靴子的冷却等级必须**恰好**为 $c$，否则会被烫伤/冻伤。

幸运的是，当你站在一个房间里时，你可以调整靴子的冷却等级，每次增加或减少 $d$ 需要支付 $d$ 枚金币。  

你从房间 $1$ 出发，目标是到达房间 $n$。到出口所需的最小金币花费是多少？


## 说明/提示


#### 样例解释



![](https://cdn.luogu.com.cn/upload/image_hosting/mpdmjywj.png)

地牢的构造如上图所示。

按照 $1\to 2\to 3\to 4\to 5$ 的路线花费为 $|3-0|+|2-3|+|3-2|+|4-3|=9$，可以证明是最优的。

#### 子任务

对于 $100\%$ 的数据，保证：

- $1\le n,m\le 2\times 10^5$；
- $1\le a_i,b_i\le n$；
- $a_i\neq b_i$；
- $1\le c_i\le 10^9$；
- 任意一对房间之间只有至多一条隧道;
- 从房间 $1$ 可以到达任意一个其他的房间。

---

- $\text{Subtask 0(0 points)}$：样例。
- $\text{Subtask 1(2 points)}$：$m=n-1$。
- $\text{Subtask 2(4 points)}$：$1\le c_i\le 10$。
- $\text{Subtask 3(4 points)}$：每个房间至多连着 $5$ 条隧道。
- $\text{Subtask 4(5 points)}$：无特殊限制。

## 样例 #1

### 输入

```
5 7
1 2 3
2 3 2
1 3 6
3 4 3
4 5 7
2 4 1
2 5 10```

### 输出

```
9```

# 题解

## 作者：chenxi2009 (赞：10)

## 思路
### $M=N-1$
图是一颗树，任意两点间路径唯一。从 $1$ 开始搜索，记录走到每一个点时的花费和当前温度。时间复杂度 $O(N)$。
### $1\le c_i\le10$
可以把每个点拆成十个走最短路，新点中每个点表示对应到达旧点的某个温度。时间复杂度 $O(cN\log(cN)+cM)$。
### 每个点出边数量 $\le5$
还是拆点，每个点表示对应旧点出发时的温度。令 $\text{num}\leftarrow5$，时间复杂度 $O(\text{num}N\log(\text{num}N)+M)$。
### 无特殊限制
一条路径的总花费是这条路径上所有相邻的两条边温度之差。

考虑**把每一条边看作一个新点**，这个问题相当于是在每两条共点边之间连一条新边，新边长为两条边的温度差，求一条与 $1$ 相连的边到与 $N$ 相连的边的最短路。要额外累加与 $1$ 相连的边的 $c$。

这样连边是不行的，如果有一个菊花图显然任意两条边都是共点边，需要的新边数量量级达到 $M^2$。

我们需要从这一道题的性质上入手优化。发现新边长是新点权差，那么我们其实并不用给一个点所有的邻边都两两连新边，而是把这些边按温度排序，温度大小相邻的边之间连新边就行了，因为温度大小不相邻的边互相抵达可以通过温度在中间的点中转，而不影响消耗。

新边量级为 $O(M)$，再建一个超级源点导向 $1$ 的邻边，超级汇点由 $N$ 的邻边导向，跑这两点之间的最短路就好了。

时间复杂度 $O(M\log M)$。

还有一种做法，延续每个点出度 $\le5$ 的做法，还是拆点，和它相连的边的每个温度都拆出一个点，同一个旧点的温度相邻的新点之间连边，时间复杂度 $O(M\log M)$。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,w;
long long dis[300000];
bool vis[300000];
vector<pair<int,int>>e[300000],ne[300000];
priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>q;
inline void shortest_path(){//最短路板子 
	while(q.size()){
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto [v,w] : e[u]) if(dis[v] > dis[u] + w) q.push({dis[v] = dis[u] + w,v});
	}
	return;
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	read(n,m);
	for(int i = 1;i <= m;i ++) read(u,v,w),ne[u].push_back({w,i}),ne[v].push_back({w,i});//旧边只需要保存温度和边编号 
	for(int i = 2;i < n;i ++){
		sort(ne[i].begin(),ne[i].end());//给一个点的邻边按温度排序 
		for(int j = 1;j < ne[i].size();j ++){//任意温度相邻的边之间连新边 
			e[ne[i][j].second].push_back({ne[i][j - 1].second,abs(ne[i][j].first - ne[i][j - 1].first)});
			e[ne[i][j - 1].second].push_back({ne[i][j].second,abs(ne[i][j].first - ne[i][j - 1].first)});
		}
	}
	for(auto i : ne[1]) e[0].push_back({i.second,i.first});//超级源点 0 号新点 
	for(auto i : ne[n]) e[i.second].push_back({m + 1,0});//超级汇点 M+1 号新点 
	dis[0] = 0,q.push({0,0});
	shortest_path();
	printf("%lld",dis[m + 1]);
	return 0;
}
```

---

## 作者：liaochengrui (赞：3)

建议先做[这道题（ NOI2025D1T1 ）](https://www.luogu.com.cn/problem/P13271)

## 题意

给定一个图，图中有一些边，走这些边需满足靴子的冷却等级和这条边的 $wi$ **相同**，走边不消耗金币，但改变靴子的冷却等级要消耗。

初始在 $1$ 号节点，靴子的冷却等级为 $0$，求走到 $n$ 号节点所消耗的金币数。

## solution

对于在节点上操作有贡献的情况，考虑**拆点**。

新图上的点需要 $2$ 个参数表示编号，一个 $x$ 是原图的节点编号，另一个 $y$ 是此时的冷却等级。

$rnk[i]$ 表示新图上编号为 $i$ 在原图上对应的点的编号。

```cpp
int idx(int x,int y){
	if(!mp[{x,y}])  mp[{x,y}]=++cnt,rnk[cnt]=x;
	return mp[{x,y}];
}
```

这道题和 [NOI2025D1T1](https://www.luogu.com.cn/problem/P13271) 建图有些许区别。

NOI 的那道题有

- $1 \leq n, m \leq 3 \times 10^5$，$1 \leq k \leq 2.5 \times 10^5$；
- 对于所有 $1 \leq i \leq n$，均有 $0 \leq d_i \leq k$，且 $\sum_{i=1}^{n} d_i = m$。

所以建边的空间就是 $O(m)$，绰绰有余。

但在本题中有

- $1\le c_i\le 10^9$。

如果还用前者的建边方法就会炸掉。

没必要修改冷却等级时一点一点修，所以考虑把到达 $i$ 点时所有可能的冷却等级保存下来，排个序，去个重，再把相邻的冷却等级建边即可，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/o7bvfpd9.png)

整张图的 $w$ 种数为 $m$，那么建边的复杂度就被降到了 $O(m)$。

建好后跑个 dijk 即可求出答案。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=(2e5+5)*10,M=(2e5+5)*10;
const int INF=1e18;
struct node{
	int v,nxt;
	int w;
}e[M];
struct edge{
	int to;
	int cs;
};
struct point{
	int dis;
	int id;
};
bool operator > (const point &a,const point &b){
	return a.dis>b.dis;
}
int n,m;
int first[N],tot=0;
vector<int> val[N];
int dist[N],ans[N];
vector<edge> G[N];    //临时存图，最终跑dijk在邻接表上跑
priority_queue< point,vector<point>,greater<point> > q;
bool f[N];
map<pair<int,int>,int> mp;
int rnk[N],cnt=0;
int idx(int x,int y){
	if(!mp[{x,y}])  mp[{x,y}]=++cnt,rnk[cnt]=x;
	return mp[{x,y}];
}
void add(int u1,int v1,int w1){
	e[++tot].v=v1;e[tot].w=w1;
	e[tot].nxt=first[u1];
	first[u1]=tot;
}
void dijk(){
	for(int i=1;i<N-5;++i)  dist[i]=ans[i]=INF;
	memset(f,0,sizeof(f));
	dist[idx(1,0)]=0;
	ans[1]=0;
	q.push({0,idx(1,0)});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(f[u])  continue;
		f[u]=1;
		for(int i=first[u];i;i=e[i].nxt){
			int v1=e[i].v;
			int w1=e[i].w;
			if(dist[v1]>dist[u]+w1){
//				printf("u=%d v=%d rnk_u=%d rnk_v=%d\n",u,v1,rnk[u],rnk[v1]);
				dist[v1]=dist[u]+w1;
				ans[rnk[v1]]=min(ans[rnk[v1]],dist[v1]);
				q.push({dist[v1],v1});
			}
		}
	}
}
signed main(){
	cin>>n>>m;
	memset(first,0,sizeof(first));
	for(int i=1;i<=m;++i){
		int ui,vi,wi;
		scanf("%lld%lld%lld",&ui,&vi,&wi);
		G[ui].push_back({vi,wi});    //因为是临时存图，所以只需要存单向即可
		val[ui].push_back(wi);
		val[vi].push_back(wi);
//		G[vi].push_back({ui,wi});
	}
	val[1].push_back(0);
	for(int i=1;i<=n;++i){
		sort(val[i].begin(),val[i].end());
		val[i].erase(unique(val[i].begin(),val[i].end()),val[i].end());
		for(int j=0;j<val[i].size()-1;++j){
			add(idx(i,val[i][j]),idx(i,val[i][j+1]),val[i][j+1]-val[i][j]);
			add(idx(i,val[i][j+1]),idx(i,val[i][j]),val[i][j+1]-val[i][j]);
		}
	}
	for(int i=1;i<=n;++i)
	  for(int j=0;j<G[i].size();++j){
	  	int v1=G[i][j].to,w1=G[i][j].cs;
	  	add(idx(i,w1),idx(v1,w1),0);
	  	add(idx(v1,w1),idx(i,w1),0);
	  }
	dijk();
	printf("%lld\n",ans[n]);
	return 0;
}
```

~4秒的时限还是绰绰有余~。

---

## 作者：Your_Name (赞：3)

## 题解
这道题其实是[这个题](https://www.luogu.com.cn/problem/P6822)改了点。

但作为负责任的题解，我还是要讲讲这种题怎么做。

首先发现走的花费只与边权的相对关系有关，那么我们考虑一个很典的结论：

**把边看成点**。

具体来说，我们设正边为 $i$，反边为 $i+m$。

然后可以直接把从一个点出发的边两两连接，那么边权显然就是两条边权的差的绝对值。

但是我们发现，通过上面这么处理之后，我们只连了从某个点出去的边之间的关系，也就是说，我们没有把正反边联系起来。

在这道题中，由于花费只是差值（在我给的原题更麻烦），所以我们把每一条边的正反边之间连一条权值为 $0$ 的边即可。

然后，我们再把 $0$ 号点（即虚拟的出发点）连上从 $1$ 号点出发的边。把从 $n$ 号点出发的边连上 $m+m+1$ 号点（即虚拟的结束点）。

然后我们发现，光建图的复杂度就是 $O(\sum_{i=1}^n d_i^2)$（$d_i$ 是出度）了。显然如果图是菊花就爆了，那么我们考虑把一个点的出边按边权排序，然后只加相邻的双边，权值为 $w_i-w_{i-1}$。

考虑为什么这么做是对的。显然，我在经过某个点时，一定是从一条出边走到另一条出边。那么，我经过的权值就是两条边权值的差。而在我们刚刚提到的建图方法中，如果我要从权值为 $w_i$ 走到 $w_j$，那么花费即为：
$$
(w_{i+1}-w_i)+(w_{i+2}-w_{i+1})+...+(w_{j-1}-w_{j-2}) +(w_{j}-w_{j-1})
$$
发现中间全部被约掉了，就剩：
$$
w_j-w_i
$$
满足题意。
而且易证得这种方式可以表示出任意的走法。

那么有人就问了：我们建了环为什么他不会走回头路呢？

因为我们等会跑的是最短路，显然走回头路不优，也就不会走到。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<long long, long long>
#define xx first
#define yy second
const int N = 4e5 + 10;//注意两边空间
int n, m, dis[N];
vector<PII> G[N], H[N];
bool sure[N];
priority_queue<PII, vector<PII>, greater<PII>> q; 
void dij(){
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0;
	q.push({0, 0});
	while(!q.empty()){
		auto u = q.top();
		q.pop();
		if(sure[u.yy])continue;
		sure[u.yy] = 1;
		for(auto v : H[u.yy]){
			if(dis[v.xx] > dis[u.yy] + v.yy){
				dis[v.xx] = dis[u.yy] + v.yy;
				q.push({dis[v.xx], v.xx});
			}
		}
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({w, i});
        G[v].push_back({w, i + m});
        H[i].push_back({i + m, 0});
        H[i + m].push_back({i, 0});//正反边
    }
    for(int i = 1; i <= n; i ++){
        sort(G[i].begin(), G[i].end());//边权排序
        for(int j = 0; j < G[i].size() - 1; j ++){
            H[G[i][j].yy].push_back({G[i][j + 1].yy, G[i][j + 1].xx - G[i][j].xx});
            H[G[i][j + 1].yy].push_back({G[i][j].yy, G[i][j + 1].xx - G[i][j].xx});
        }//加相邻的边
    }
    for(auto i : G[1])H[0].push_back({i.yy, i.xx});
    for(auto i : G[n])H[i.yy].push_back({m + m + 1, 0});//起点终点
    dij();
    cout << dis[m + m + 1];
    return 0;
}
```
 _完结撒花。_

---

## 作者：MaiJingYao666 (赞：2)

# P11860 [CCC 2025 Senior] 熔岩路 / Floor is Lava 题解  
作为一名蒟蒻，听说 NOI2025 的 D1T1 和这题形似而神生，发现我竟然会做，故写下此题解。  
### 解题思路  
好，非常非常显然，这题要求最短路。再非常非常显然，这题要求最小金币的花费，所以题目中本来就有的双向边边权都是 0。  

考虑怎么方便地表示“调节冷却等级”这一过程。不妨将每个节点内冷却等级不一样的点拆成多个，可以证明点数 $\le 2\times m$，用 `map` 记录即可。  

但直接对所有同一房间的节点两两连边容易被菊花图卡死，边数将变得非常大。观察边权计算方式，我们发现有大量边是无意义的。  

举个例子，房间一中有温度为 1,3,5 的节点，此时节点 1 到节点 5 的连边就是无效的，因为不需要这条边两点之间的距离也是 4。因此，在同一房间内，我们按节点的温度排序（`map` 自带），只用相邻的连边就行了，边权就是温度之差。  

还有就是单独建一个房间一内温度为 0 的节点。答案统计从所有房间 $n$ 的节点中取最小值即可。  

剩下的就是朴素的最短路了。  
### AC 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+50;
typedef long long ll;
typedef pair<ll,ll> PII;
const ll inf=8e18+7;
int n,m;
map<int,int> mapp[N];
int cnt;
vector<PII> G[N<<2];
ll dis[N<<2];
bool vis[N<<2];
inline void dijkstra(){
	priority_queue<PII,vector<PII>,greater<PII>> q;
	for(int i=1;i<=cnt;i++){
		vis[i]=0;
		dis[i]=inf;
	}
	dis[mapp[1][0]]=0;
	q.push({0,mapp[1][0]});
	while(q.size()){
		int ver=q.top().second;
		q.pop();
		if(vis[ver]) continue;
		vis[ver]=1;
		for(auto j:G[ver]){
			if(dis[ver]+j.second<dis[j.first]){
				dis[j.first]=dis[ver]+j.second;
				q.push({dis[j.first],j.first});
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		ll c;
		scanf("%d%d%lld",&a,&b,&c);
		if(mapp[a][c]==0) mapp[a][c]=++cnt;
		if(mapp[b][c]==0) mapp[b][c]=++cnt;
		G[mapp[a][c]].push_back({mapp[b][c],0});
		G[mapp[b][c]].push_back({mapp[a][c],0});
	}
	if(mapp[1][0]==0) mapp[1][0]=++cnt;
	for(int i=1;i<=n;i++){
		int las=0,laid=0;
		for(auto j:mapp[i]){
			if(laid!=0){
				G[j.second].push_back({laid,j.first-las});
				G[laid].push_back({j.second,j.first-las});
			}
			las=j.first;
			laid=j.second;
		}
	}
	dijkstra();
	ll ans=inf;
	for(auto j:mapp[n]){
		ans=min(ans,dis[j.second]);
	}
	printf("%lld",ans);
}
```

---

## 作者：Night_sea_64 (赞：2)

首先看到这个题很分层图，所以考虑如何建图能在时空限制内完成答案。

不难发现可以给每个点连的每条边的 $c$ 值都开一个新点。设这些 $c$ 值分别为 $c_1\sim c_k$（已从小到大排序），则 $\forall 1\le i<k$，在 $c_i$ 对应的新点和 $c_{i+1}$ 对应的新点之间连一条边权为 $c_{i+1}-c_i$ 的双向边，这样可以实现在每个点处切换冷却值。特殊的应该对 $(1,0)$ 也开一个

然后对于所有边 $(u,v,w)$，就在 $(u,w)$ 对应的点和 $(v,w)$ 对应的点之间连一条边权为 $0$ 的双向边即可。这样跑 Dij 显然可以求出正确答案。

分析一下点数和边数：点数为 $2m+1$，双向边数不超过 $m+2m=3m$，完全没有问题。

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
int n,m;
int l[200010],r[200010],cur;
struct node{int id,x;}a[400010];
bool operator<(const node &x,const node &y){
    if(x.id!=y.id)return x.id<y.id;
    return x.x<y.x;
}
struct edge{int x,w;};
vector<edge>vv[400010];
vector<edge>v[400010];
bool flag[400010];
int d[400010];
struct node2{int x,d;};
bool operator<(const node2 &x,const node2 &y){
    return x.d>y.d;
}
void dij()
{
    priority_queue<node2>q;
    memset(d,999999,sizeof(d));
    d[1]=0;
    q.push((node2){1,0});
    while(!q.empty())
    {
        int x=q.top().x;
        q.pop();
        if(flag[x])continue;
        flag[x]=1;
        for(auto e:v[x])
            if(d[x]+e.w<d[e.x])
            {
                d[e.x]=d[x]+e.w;
                q.push((node2){e.x,d[e.x]});
            }
    }
}
signed main()
{
    cin>>n>>m;
    a[++cur]=(node){1,0};
    for(int i=1;i<=m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        a[++cur]=(node){x,w};
        a[++cur]=(node){y,w};
        vv[x].push_back((edge){y,w});
        vv[y].push_back((edge){x,w});
    }
    sort(a+1,a+cur+1);
    for(int i=2;i<=cur;i++)
        if(a[i].id==a[i-1].id)
        {
            v[i-1].push_back((edge){i,a[i].x-a[i-1].x});
            v[i].push_back((edge){i-1,a[i].x-a[i-1].x});
        }
    for(int i=1;i<=n;i++)
    {
        for(auto e:vv[i])
        {
            int posi=lower_bound(a+1,a+cur+1,(node){i,e.w})-a;
            int posj=lower_bound(a+1,a+cur+1,(node){e.x,e.w})-a;
            v[posi].push_back((edge){posj,0});
        }
    }
    dij();
    int ans=9e18;
    for(int i=1;i<=cur;i++)
        if(a[i].id==n)ans=min(ans,d[i]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Sunrise_beforeglow (赞：1)

首先肯定不能直接采用 Dijkstra 算法，因为我们不确定到点 $i$ 时鞋子的温度是多少。

但是我们发现一个性质：我们如果确定走到了那条边后，一定能确定鞋子的温度。

所以我们考虑把边看作点，跑 Dijkstra。

那么考虑两条有公共点的边 $u_1,u_2$。

设它们的权值分别为 $w_1,w_2$。

那么从第 $u_1$ 条边走到第 $u_2$ 条边，显然会花费 $|w_1-w_2|$ 的代价。我们定义这种方式建立的边称之为新边。

那么问题来了，这样建边，会有 $n^2$ 条新边。

我们又发现一个性质，如果 $a\le b\le c$，那么 $|c-a|=|c-b|+|b-a|$。

于是我们有了一个思路，对于每个点 $i$，将它连的所有边按边权排序，再照上面的方法连新边即可。这样就只有 $m$ 条新边。

最后统计答案时，只需要使用超级原点与超级终点跑 Dijkstra 即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
struct edge{
	int v;
	ll w;
	int t;
	edge(int V=0,ll W=0,int T=0):v(V),w(W),t(T){}
	bool operator<(edge b)const{
		return w<b.w;
	}
};
struct node{
	int n;
	ll d;
	node(int W=0,int J=0):n(W),d(J){}
	bool operator<(node b)const{
		return b.d<d;
	}
};
vector<edge>l[N],g[N];
int tot,n,m;
ll dist[N];
bool dis[N];
priority_queue< node >q;
void dij(){
	memset(dist,0x3f,sizeof dist);
	dist[tot]=0;
	q.push(node(tot,0));
	while(!q.empty()){
		node fr=q.top();
		q.pop();
		if(dis[fr.n])continue;
		dis[fr.n]=1;
		int d=fr.d;
		for(int i=0;i<(int)g[fr.n].size();i++){
			int v=g[fr.n][i].v,w=g[fr.n][i].w;
			if(dist[v]>d+w){
				dist[v]=d+w;
				q.push(node(v,d+w));
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,w;
		ll v;
		cin>>u>>v>>w;
		l[u].push_back(edge(v,w,++tot));
		l[v].push_back(edge(u,w,tot));
	}
	for(int i=2;i<n;i++){
		sort(l[i].begin(),l[i].end());
		for(int j=0;j<(int)l[i].size()-1;j++){
			ll ans=abs(l[i][j].w-l[i][j+1].w);
			g[l[i][j].t].push_back(edge(l[i][j+1].t,ans,0));
			g[l[i][j+1].t].push_back(edge(l[i][j].t,ans,0));
		}
	}
	++tot;
	for(int i=0;i<(int)l[1].size();i++){
		g[tot].push_back(edge(l[1][i].t,l[1][i].w,0));
	}
	dij();
	ll ans=1e18;
	for(int i=0;i<(int)l[n].size();i++){
		ans=min(ans,dist[l[n][i].t]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ericnoi (赞：1)

# 思路

### $M = N - 1$

显然该图为树，两点之间只有一条简单路径，不存在选择，直接模拟即可。

### $1 \le c_i \le 10$

因为到达一个点时只有有限种状态，而在这个点的状态又会影响接下来的事件，所以可以进行**拆点**，或者叫**分层图**。即把一个点的每一种状态抽象成新图上的一个点，在状态之间转移的代价抽象成新图上的边与边权。

在这里我们将在一个点时**不同的冷却等级**拆分成不同的点，显然一个点能拆出 $10$ 个点，一个点在新图上内部的边权即为冷却等级之差，点与点之间在新图上的边权设置成 $0$，因为通过一条边并不会直接造成代价。

于是在新图上跑最短路即可。

### 无特殊限制

大体思路还是拆点，只不过 $c_i$ 的范围变大了。注意到如果一个点没有边权为 $w$ 的邻边，那么在这个点时冷却等级也不可能为 $w$，所以说只需要拆成 $x$ 个点，$x$ 为这个点邻边的数量。

但是如果在拆出的 $x$ 个点中两两连接，建边的复杂度上界可以达到 $O(M^2)$，这是不可接受的。所以还要优化建图。只需要连接第 $1$ 个点和第 $2$ 个点，第 $2$ 个点和第 $3$ 个点 …… 一直到第 $n$ 个点，就相当于连接了所有 $n$ 个点。这样所建边的数量就降到了 $O(M)$。

# 代码实现

为了编码的简便使用了 ```std::map``` 和 ```std::set```，由于时间限制比较宽松所以无伤大雅。

Code：

```cpp
#include <bits/stdc++.h>
#define inf (0x3f3f3f3f)
#define INF (INFINITY)
#define LIMIT (INT_MAX)
// #define LL
// #define getchar getchar_unlocked
#ifdef LL
#define int long long
#undef inf
#define inf (0x3f3f3f3f3f3f3f3f)
#undef LIMIT
#define LIMIT (LLONG_MAX)
#endif
#define pb push_back
#define ps push
#define lowbit(x) ((x) & (-(x)))
#define ls (i << 1)
#define rs (i << 1 | 1)
#define fill(x, y) memset(x, y, sizeof(x))
#define heap priority_queue<int, vector<int>, greater<int>>
#define pow2(x) (1 << (x))
#define changeif(a, b, c) ((a) == (b) ? (c) : (a))
#define addedge(u, v) a[u].pb(v); a[v].pb(u)
#define addedgew(u, v, w) a[u].pb(edge(v, w)); a[v].pb(edge(u, w))
#define aminos printf("debug : in line %d\n", __LINE__)
// #define f(x, y) ((m) * ((x) - 1) + (y))
#define kth(x, y) (x & (1 << (y - 1)))
#define kth1(x) (1 << (x - 1))
#define all1(x) ((1 << (x)) - 1)
#define gcd(x, y) (1ll * x * y == 0 ? x + y : __gcd((x), (y)))
#define lcm(x, y) ((x) / gcd((x), (y)) * (y))
#define chkmax(x, y) ((x) = max((x), (y)))
#define chkmin(x, y) ((x) = min((x), (y)))
#define add(x, y) (((x) + (y)) % mod)
#define addto(x, y) ((x) = add((x), (y)))
#define minus(x, y) (((x) - (y) + (mod)) % (mod))
#define minusto(x, y) ((x) = minus((x), (y)))
#define times(x, y) ((1ll * (x) * (y)) % (mod))
#define timesto(x, y) ((x) = times((x), (y)))
#define divide(x, y) (times(x, inv(y)))
#define divideto(x, y) ((x) = divide((x), (y)))
#define isnumber(x) (((x) >= '0') && ((x) <= '9'))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<class T> inline T read(T &x) { 
	int f = 1; x = 0; char s = getchar();
	while(!isnumber(s)) {if(s == '-') f = -1; s = getchar();}
	while(isnumber(s)) x = (x << 1) + (x << 3) + (s ^ '0'), s = getchar();
	return x *= f;
}
inline int read(char* s) {return scanf("%s", s);}
inline double read(double &x) {scanf("%lf", &x); return x;}
template<class T> inline void print(T x, char suf = 0, int base = 10) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x >= base) print(x / base, 0, base);
	putchar(48 ^ (x % base));
	if(suf) putchar(suf);
}
template<class T> inline void printarr(T* a, int n, int off = 0, int base = 10) {
	int i; for(i = 1 ; i + 8 <= n ; i += 8) {
		print(a[i+off], ' ', base); print(a[i+1+off], ' ', base);
		print(a[i+2+off], ' ', base); print(a[i+3+off], ' ', base);
		print(a[i+4+off], ' ', base); print(a[i+5+off], ' ', base);
		print(a[i+6+off], ' ', base); print(a[i+7+off], ' ', base);
	}
	while(i <= n) {print(a[i+off], ' ', base); i++;}
	putchar('\n');
}
template<class T> inline void readarr(T* a, int n) {
	int i; for(i = 1 ; i + 8 <= n ; i += 8) {
		read(a[i]); read(a[i+1]);
		read(a[i+2]); read(a[i+3]);
		read(a[i+4]); read(a[i+5]);
		read(a[i+6]); read(a[i+7]);
	}
	while(i <= n) {read(a[i]); i++;}
}
int cx = 1;
const int N = 2e5 + 5;
int n, m;
struct edge {
	int to, w;
	edge() {}
	edge(int a, int b) {
		to = a, w = b;
	}
};
vector<edge> a[N], g[N<<2];
int cnt, d[N<<2];
map<int, int> mp[N];
set<int> s[N];
struct node {
    int d, u;
    node() {}
    node(int a, int b) {
        d = a, u = b;
    }
};
void dijkstra(vector<edge>* a, int* dis, int sizeofdis, int s) {
    auto cmp = [](node a, node b) -> bool {
        return a.d > b.d;
    };
    priority_queue<node, vector<node>, decltype(cmp)> q(cmp);
    memset(dis, 0x3f, sizeofdis);
    dis[s] = 0;
    q.ps(node(0, s));
    while(q.size()) {
        node now = q.top();
        q.pop();
        int u = now.u, d = now.d;
        for(edge e : a[u]) {
            int v = e.to, w = e.w;
            if(d + w < dis[v]) {
                dis[v] = d + w;
                q.ps(node(dis[v], v));
            }
        }
    }
}
void solve() {
	read(n), read(m);
	for(int i = 1 ; i <= m ; i++) {
		int u, v, w;
		read(u), read(v), read(w);
		addedgew(u, v, w);
		s[u].insert(w);
		s[v].insert(w);
	}
	s[1].insert(0);
	vector<int> vec;
	for(int u = 1 ; u <= n ; u++) {
		vec.clear();
		for(int c : s[u]) {
			mp[u][c] = ++cnt;
			vec.pb(c);
		}
		for(int i = 0 ; i < vec.size() - 1 ; i++) {
			int x = mp[u][vec[i]], y = mp[u][vec[i+1]], z = vec[i+1] - vec[i];
			g[x].pb(edge(y, z));
			g[y].pb(edge(x, z));
		}
	}
	for(int u = 1 ; u <= n ; u++) {
		for(edge e : a[u]) {
			int v = e.to, w = e.w;
			int x = mp[u][w], y = mp[v][w], z = 0;
			g[x].pb(edge(y, z));
		}
	}
	dijkstra(g, d, sizeof(d), 1);
	int ans = inf;
	for(int c : vec) {
		chkmin(ans, d[mp[n][c]]);
	}
	print(ans, '\n');
}
signed main() {
    // int st_t = clock();
    // read(cx);
	// init();
    while(cx--) {
        solve();
    }
    // cerr << clock() - st_t << "ms" << endl; 
    return 0;
}



```

---

## 作者：Coffee_zzz (赞：1)

我们考虑建立一个新图：

- 对于原图中的每条边 $i$，把这条边看成新图中的一个点 $i$；
- 对于原图中的每个点 $u$，将「原图中任意两条不同的与 $u$ 相邻的边 $i,j$」在新图中对应的点 $i,j$ 之间连一条权值为 $|c_i-c_j|$ 的边；
- 建立一个超级起点 $s$，将 $s$ 与所有「原图中与 $1$ 相邻的边 $i$」在新图中对应的点 $i$ 之间连一条权值为 $c_i$ 的边；
- 建立一个超级终点 $t$，将 $t$ 与所有「原图中与 $n$ 相邻的边 $i$」在新图中对应的点 $i$ 之间连一条权值为 $0$ 的边。

显然，在这个新图上直接求 $s$ 到 $t$ 的最短路即可得到我们所求的答案，但是这个新图的边数是 $\mathcal O(m^2)$ 的，我们需要考虑优化。

注意到，新图中的边权是绝对值形式的，而绝对值有一个性质是，若 $a\le b\le c$ 或 $a\ge b \ge c$，则 $|a-b|+|b-c|=|a-c|$，所以我们可以把原图中所有与 $u$ 相邻的边 $i$ 按照 $c_i$ 从小到大排序，只在「排序后相邻的两条边 $i,j$」在新图中对应的点 $i,j$ 之间连一条权值为 $|c_i-c_j|$ 的边即可。这样我们就用 $\mathcal O(m)$ 条边代替掉了原来的 $\mathcal O(m^2)$ 条边，跑 Dijkstra 即可，时间复杂度 $\mathcal O(m \log m)$。

---

## 作者：Kevin911 (赞：1)

## 思路
考虑在便边与边之间建边。直接在边与边之间建边 $O(m^2)$ 会炸，思考怎么优化建边。
对于菊花图，发现跟一个点相关的k条边之间从小到大排个序然后在相邻的两条边建一条新边即可即可，只用建条 $k-1$ 双向边。

为什么这样是对的？令排完序之后的权值序列为 $w_1$ 到 $w_k$，想从 $i$ 到 $j(i<j)$,有 $\lvert w_i-w_j\rvert=\lvert w_i-w_{i+1}\rvert+\lvert w_{i+1}-w_{i+2}\rvert+ \cdots +\lvert w_{j-1}-w_{j}\rvert$，反之亦然。

跑最短路即可，代码如下。

```cpp
#pragma GCC ("Ofast")
#include<bits/stdc++.h>
#define ll long long
#define pii pair<ll,int>
using namespace std;
const int maxn=2e5+10;
int n,m;
ll ans=1e18;
int a[maxn],b[maxn],c[maxn];
ll d[maxn];
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > q;
vector<int> e[maxn],g[maxn];
bool cmp(int x,int y)
{
	return c[x]<c[y];
}
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c&15);
		c=getchar();
	}
	return x;
}
void print(ll x)
{
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
void dij()
{
	for(int i=1;i<=m;i++)
	{
		d[i]=1e18;
		if(a[i]==1||b[i]==1) d[i]=c[i],q.push({d[i],i});
	}
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			if(d[v]>d[u]+abs(c[u]-c[v]))
			{
				d[v]=d[u]+abs(c[u]-c[v]);
				q.push({d[v],v});
			}
		}
	}
}
signed main()
{
	n=read(),m=read(); 
	for(int i=1;i<=m;i++)
	{
		a[i]=read(),b[i]=read(),c[i]=read(); 
		e[a[i]].push_back(i),e[b[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		sort(e[i].begin(),e[i].end(),cmp);
		for(int j=0;j<e[i].size()-1;j++) g[e[i][j]].push_back(e[i][j+1]),g[e[i][j+1]].push_back(e[i][j]);
	}
	dij();
	for(int i=1;i<=m;i++)
		if(a[i]==n||b[i]==n) ans=min(ans,d[i]);
	print(ans);
}
```

---

## 作者：modfish_ (赞：1)

## 思路
Subtask 1 是一棵树，只有一种走法，DFS 一遍即可。

Subtask 2 只有 $10$ 种温度，可以建虚点，或者分层图（本质一样）。

Subtask 3 点的度数极小，可以把边变成点，所有共点的边互相连边即可。

根据 Subtask 3 启示，边变点本身是一种不错的方案，然而连得边数太多了。有无优化方法？

很简单，把一个点周围的边按温度排序，只需将相邻的边连边即可。显然是正确的。然后直接跑最短路即可。

复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e6 + 5;

vector<pair<int, int> > V[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
ll ww[maxn << 1], dis[maxn];

void match(int u, int v, ll w){
    nxt[++ cnt] = head[u], to[cnt] = v, ww[cnt] = w, head[u] = cnt;
}
int vis[maxn];
void dijkstra(int s){
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    dis[s] = 0;
    q.push(make_pair(0, s));
    while(!q.empty()){
        int x = q.top().second;
        q.pop();
        vis[x] = 1;
        for(int i = head[x]; i; i = nxt[i]){
            int j = to[i];
            ll w = ww[i];
            if(dis[x] + w < dis[j]){
                dis[j] = dis[x] + w;
                if(!vis[j]) q.push(make_pair(dis[j], j));
            }
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i ++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        V[u].push_back(make_pair(w, i)), V[v].push_back(make_pair(w, i));
        dis[i] = (ll)1e18;
    }
    for(int x = 1; x <= n; x ++){
        sort(V[x].begin(), V[x].end());
        int pv = 0, pw = 0;
        for(int i = 0; i < V[x].size(); i ++){
            int v = V[x][i].second, w = V[x][i].first;
            if(!i){
                if(x == 1) match(0, v, w), match(v, 0, w);
            }else match(pv, v, w - pw), match(v, pv, w - pw);
            pv = v, pw = w;
        }
    }
    dijkstra(0);
    ll ans = (ll)1e18;
    for(int i = 0; i < V[n].size(); i ++) ans = min(ans, dis[V[n][i].second]);
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：SunburstFan (赞：0)

## [P11860 [CCC 2025 Senior] 熔岩路 / Floor is Lava](https://www.luogu.com.cn/problem/P11860)

### 题目大意
你被困在一个有 $n$ 个房间和 $m$ 条双向隧道构成的地牢中。隧道地板上覆盖着温度为 $c$ 的熔岩，只有当你的耐热靴子冷却等级恰好等于 $c$ 时，才能安全经过。你从房间 $1$ 出发，初始冷却等级为 $0$，在房间内可以花费硬币调整冷却等级（每增加或减少 $1$ 需 $1$ 枚金币），目标是以最小金币花费到达房间 $n$。

### 解题思路
方案核心在于将问题转化为求一条路径上温度调整的最小成本。对于一条选定的路径，如果依次经过温度 $c_1, c_2, …, c_k$ 的隧道，总花费为 $|c_1 − 0| + |c_2 − c_1| + … + |c_k − c_{k-1}|$。

考虑每个房间内相邻隧道的温度调整问题：  
- 对于同一个房间，把所有出入该房间的隧道按温度排序，任意相邻两隧道间调整的花费即为它们温度之差。  
- 从房间 $1$ 出发，初始冷却等级为 $0$，因此进入该房间的每条隧道的起始花费为隧道温度。  
- 对于房间 $n$，只需保证通过某条隧道到达即可。

因此，我们构造一个以隧道为“节点”的图，  
- 对于每个房间，将该房间中排序后的隧道节点两两建立边，权值为温度差（双向边）。  
- 接着，对于所有出自房间 $1$ 的隧道，初始代价为它们各自的温度；对于所有经过房间 $n$ 的隧道，记录到达终点的代价。  

最后，利用 Dijkstra 在该图上求最短路径，答案即为最低总调整花费。

该方法在构造边时对每个房间按隧道温度排序，所以整体时间复杂度为 $O(m\times \log m)$。

```cpp
#include<bits/stdc++.h>
using  namespace std;

#define ll long long
const ll INF=1e18;

struct edge{
    int u,v,c,id;
};

namespace sunburstfan{
    vector<edge> e;
    vector<vector<int> >raw_e;
    vector<vector<pair<int,ll> > > G;

    bool cmp(int a,int b){
        return e[a-1].c<e[b-1].c;
    }

    ll Dij(int n){
        vector<ll> dis(e.size()+1,INF);
        priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;

        for(auto u:raw_e[1]){
            dis[u]=e[u-1].c;
            pq.push({dis[u],u});
        }

        while(!pq.empty()){
            auto p=pq.top(); pq.pop();

            ll u=p.second,c=p.first;
            if(c>dis[u]) continue;

            for(auto v:G[u]){
                if(dis[v.first]>dis[u]+v.second){
                    dis[v.first]=dis[u]+v.second;
                    pq.push({dis[v.first],v.first});
                }
            }

        }

        ll ans=INF;
        for(auto u:raw_e[n]){
            if(dis[u]!=INF){
                ans=min(ans,dis[u]);
            }
        }

        return ans;
    }

}
using namespace sunburstfan;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int n,m;
    cin>>n>>m;

    if(n==1){
        cout<<0<<"\n";
        return 0;
    }

    raw_e.resize(n+1),G.resize(m+1);
    for(int i=1;i<=m;i++){
        int u,v,c;
        cin>>u>>v>>c;

        e.push_back({u,v,c,i});
        raw_e[u].push_back(i);
        raw_e[v].push_back(i);
    }   

    for(int i=1;i<=n;i++){
        sort(raw_e[i].begin(),raw_e[i].end(),cmp);

        for(int j=1;j<raw_e[i].size();j++){
            int u=raw_e[i][j-1],v=raw_e[i][j];
            ll c=abs(e[v-1].c-e[u-1].c);

            G[u].push_back({v,c});
            G[v].push_back({u,c});
        }
    }
    
    cout<<Dij(n)<<"\n";

    return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

#### sub 1

直接走简单路径即可。

#### sub 2

可以考虑图上 DP，多加一维保存到此点时的热度为多少，然后跑 Dij 即可。

#### sub 3

同样图上 DP，只是新加的一维保存的是走的上一条边的编号。

#### sub 4

通过前两个 sub 观察可以得到，一条边所付出的代价只于其通过的前一条边有关，且代价很好得出，考虑边化点重新建图，新边的边权为两个边热度的差值，再整两个新的源点汇点即可。但如此建图的话绝对会爆的，建边数会被菊花图卡到 $M^2$。

考虑优化，发现相邻的边之间没必要建完全图，如果三个相邻的边的权值分别为 $10,3,2$，从最大到最小是 $10 \to 2$，代价为 $8$。但如果是 $10 \to 3 \to 2$，代价依然为 $8$。从而想到对于相邻的边，只要排序后建热度相邻的边之间的新边即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5 + 5;
int n, m, x, y, z, pw, pv, dis[200005], vis[200005], ans = 0x3f3f3f3f3f3f3f3f;
vector<pair<int, int>> r[200005], e[200005];//r为旧边，e为新边
bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}
struct node {
	int u, dis;
	bool operator <(const node &a) const {
		return a.dis < dis;
	}
};
priority_queue<node> q;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		r[x].push_back({i, z});
		r[y].push_back({i, z});//不难想到以前的边到哪里根本不重要，所以保存编号就好
	}
	for (int i = 1; i <= n; i++) {
		sort(r[i].begin(), r[i].end(), cmp);
		for (int u = 0; u < r[i].size(); u++) {
			int v = r[i][u].first, w = r[i][u].second;
			if (u == 0) {
				if (i == 1) {
					e[0].push_back({v, w});
					e[v].push_back({0, w});
				}
			} else {
				e[pv].push_back({v, abs(pw - w)});
				e[v].push_back({pv, abs(pw - w)});
			}
			pv = v, pw = w;
		}
	}
	q.push({0, 0});
	memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	while (!q.empty()) {
		int u = q.top().u;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto v : e[u]) {
			if (dis[v.first] > dis[u] + v.second) {
				dis[v.first] = dis[u] + v.second;
				if (!vis[v.first]) q.push({v.first, dis[v.first]});
			}
		}
	}
	for (auto i : r[n]) ans = min(ans, dis[i.first]);
	cout << ans;
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

总花费是答案路径上所有相邻边的权值之差，所以由此可以推出部分分的做法：把原图中所有边当做点建一个新图，连接共点边作为新边，权值为原图中边权之差。建一个超级源点和一个超级汇点，跑最短路即可。

优化比较明确：在一个点上改变自身权值多次，只要始末态不变，花费就不变，所以只需要给原图中的点的连边按照边权排序，给排位相邻的边建新边即可，其它的边可以通过这些边中转，结果不变。

记得把初始值开大一点哦～

```cpp
const ll N=2e5+10;
ll n,m;
vector<pll> g[N],gg[N];

void input() {
//	freopen("P11860_2.in.txt","r",stdin);
	cin>>n>>m;

	rep(i,1,m) {
		ll u,v,w;
		cin>>u>>v>>w;
		g[u].pb({w,i});
		g[v].pb({w,i});
	}
}

void instruct() {
	rep(i,2,n-1) {
		sort(g[i].begin(),g[i].end());

		rep(j,1,g[i].size()-1) {
			ll u=g[i][j].se,v=g[i][j-1].se,w=abs(g[i][j].fi-g[i][j-1].fi);
			gg[u].pb({v,w});
			gg[v].pb({u,w});
		}
	}

	for(pll i:g[1]) {
		ll u=0,v=i.se,w=i.fi;
		gg[u].pb({v,w});
		gg[v].pb({u,w});
	}
	
	for(pll i:g[n]) {
		ll u=m+1,v=i.se,w=0;
		gg[u].pb({v,w});
		gg[v].pb({u,w});
	}
	
//	rep(i,0,m+1){
//		cout<<"i="<<i<<":";
//		
//		for(pll j:gg[i]) cout<<j.fi<<' ';
//		
//		endl;
//	}
//	
//	pause;
}

const ll inf=922337203685477580;
ll ans[N];
bool vis[N];
pqueue(pll,greater) pq;

void dij(){
	rep(i,1,m+1) ans[i]=inf;
	
	pq.push({0,0});
	
	while(pq.empty()==0){
		pll cur;
		xtop(cur,pq);
		
		if(vis[cur.se]) ctn;
		else vis[cur.se]=1;
		
		for(pll i:gg[cur.se]) {
//			update(ans[i.fi],cur.fi+i.se,min);
			
			if(cur.fi+i.se<ans[i.fi]){
				ans[i.fi]=cur.fi+i.se;
				pq.push({ans[i.fi],i.fi});
			}
		}
	}
	
//	cout<<"ans[]:";
//	
//	rep(i,0,m+1) cout<<ans[i]<<' ';
//	
//	endl;
//	pause;
}

void output(){
	cout<<ans[m+1];
}

int main() {
	input();
	instruct();
	dij();
	output();
}
```

---

## 作者：冷却心 (赞：0)

[更好的阅读体验](https://ladexx.github.io/2025/03/19/P11860-sol/)。简单最短路。

**算法 1**：分层图最短路。把原图上每个点拆成他的每种权值，记 $(u,k)$ 表示冷却等级为 $k$ 的点 $u$，考虑连边。一种边是同一个点，上下相邻不同层，连一条权值为 $1$ 的边表示升降冷却等级，另一种边是同一层，冷却等级恰好为两点间的边权，则这两个点连一条权值为 $0$ 的边，最后跑最短路即可。设 $V$ 为边权值域，则点数为 $O(nV)$，边数和点数同阶，时间复杂度爆炸。

**算法 2**：注意到到达每个点时的权值只有可能是这个点的出边的权值，即实际有用的虚点个数只有 $O(m)$ 个，于是我们不把每个点拆成 $V$ 个点，而是拆成其度数个点即可，然后连边类似上文的算法，相同层连 $0$ 边，同一个点不同权值连权值之差的边。然后跑最短路，由于无向图度数之和是 $O(m)$ 的，所以点数 $O(m)$，边数也是 $O(m)$，时间复杂度 $O(m\log m)$。这里给每个虚点赋一个编号使用了 `unordered_map`，实测 `gp_hash_table` 被神秘卡飞了，每个 subtask 都 TLE 一个点。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 4e5 + 10;
int n, m, tot; unordered_map<LL, int> idx;
vector<int> vec[N]; vector<pair<int, int> > G[N];
int getid(int u, int w) {
	LL t = 1ll * w * (n + 1) + u;
	if (idx.find(t) == idx.end()) idx[t] = ++ tot;
	return idx[t];
}
LL dist[N]; bool vis[N];
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m; vec[1].emplace_back(0);
	for (int i = 1, u, v, w; i <= m; i ++) {
		cin >> u >> v >> w; vec[u].emplace_back(w); vec[v].emplace_back(w);
		int a = getid(u, w), b = getid(v, w);
		G[a].emplace_back(make_pair(b, 0)); G[b].emplace_back(make_pair(a, 0));
	}
	for (int i = 1; i <= n; i ++) {
		sort(vec[i].begin(), vec[i].end()); int t = vec[i].size();
		for (int j = 1; j < t; j ++) {
			int a = getid(i, vec[i][j - 1]), b = getid(i, vec[i][j]);
			G[a].emplace_back(make_pair(b, vec[i][j] - vec[i][j - 1]));
			G[b].emplace_back(make_pair(a, vec[i][j] - vec[i][j - 1]));
		} 
	}
	memset(dist, 0x3f, sizeof dist); dist[getid(1, 0)] = 0;
	priority_queue<pair<LL, int> > pq; pq.push(make_pair(0, getid(1, 0)));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) { continue; } vis[u] = 1;
		for (auto [v, w] : G[u]) if (dist[v] > dist[u] + w) 
			pq.push(make_pair(-(dist[v] = dist[u] + w), v));
	}
	LL Ans = 1e18;
	for (int i : vec[n]) Ans = min(Ans, dist[getid(n, i)]);
	cout << Ans << "\n";
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

自己想出来，写篇题解庆祝一下。

首先套路的，这题我们就是可以分层图，这样子任务二就可以解决了，获得四分。

子任务一显然是树，任意两点在树上只有一条简单路径，不讲解。

关注子任务三，其实是希望我们对子任务二的做法做优化，我们在这个点鞋子的冷却等级实际上只会是所有入边和出边涉及到的权（如果是点 $1$，还可能是 $0$）。

于是我们就不需要对一个点分所有冷却等级的点，只需要分上述提到的所有冷却等级那些点即可。

这样我们建的边数最大大概是 $O(m)$ 的。

如果希望过题，没有了性质，我们建的边数最大就会变成 $O(m^2)$ 的。

我们有一种做法是，把一个点所有冷却等级按照数值从小到大连边。这样我们连的边是 $O(m)$ 的。这样做正确的原因是我们可以正确表示所有冷却等级改变的代价。

上文只是估计的边数，实际上最多有 $8m$ 条边。

```cpp
// Problem: P11860 [CCC 2025 Senior] 熔岩路 / Floor is Lava
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11860?contestId=234304
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int h[N], ne[N], e[N], w[N], idx, top;
int dist[N], st[N];
vector<PII> points[200000 + 10];
map<PII, int> ori;
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}
void dijkstra() {
    priority_queue<PII, vector<PII>, greater<PII>> qq;
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    qq.push({0, 1});
    dist[1] = 0;
    while (qq.size()) {
        auto iter = qq.top();
        qq.pop();
        int ver = iter.y;
        if (st[ver]) continue;
        st[ver] = 1;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                qq.push({dist[j], j});
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    memset(h, -1, sizeof h);
    cin >> n >> m;
    top = n;
    upp(i, 1, n) ori[{i, 0}] = i;
    upp(i, 1, m) {
        int x, y, z;
        cin >> x >> y >> z;
        if (!ori[{x, z}]) ori[{x, z}] = ++top;
        if (!ori[{y, z}]) ori[{y, z}] = ++top;
        add(ori[{x, z}], ori[{y, z}], 0);
        add(ori[{y, z}], ori[{x, z}], 0);
        if (!z) continue;
        points[x].push_back({z, ori[{x, z}]});
        points[y].push_back({z, ori[{y, z}]});
    }
    upp(i, 1, n) {
        points[i].push_back({0, i});
        sort(points[i].begin(), points[i].end());
        upp(j, 0, (int)points[i].size() - 2) {
            add(points[i][j + 1].y, points[i][j].y,
                points[i][j + 1].x - points[i][j].x);
            add(points[i][j].y, points[i][j + 1].y,
                points[i][j + 1].x - points[i][j].x);
        }
    }

    dijkstra();

    int minn = dist[n];
    upp(i, 0, (int)points[n].size() - 1) {
        minn = min(minn, dist[points[n][i].y]);
    }
    cout << minn << endl;
    return 0;
}
```

---

