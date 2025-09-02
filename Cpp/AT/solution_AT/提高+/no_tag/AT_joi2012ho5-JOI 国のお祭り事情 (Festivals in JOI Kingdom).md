# JOI 国のお祭り事情 (Festivals in JOI Kingdom)

## 题目描述

给定一张 $n$ 点 $m$ 边的无向图，其中有 $k$ 个点上有特殊标记。你需要回答 $q$ 次询问，每次询问包含两个整数 $s_i$ 和 $t_i$，请求出从 $s_i$ 到 $t_i$ 的路径中，在尽可能远离有标记的点的情况下距离有标记的点的长度的最小值。

## 说明/提示

#### 样例 #1 解释

$6$ 个点 $6$ 条边，第 $1,6$ 个点做了标记。

从点 $3$ 到点 $4$ 的路径有`3 2 4`和`3 5 4`两条。前者的最短距离为 $5$，后者为 $7$，所以输出 $7$。

从点 $5$ 到点 $2$ 的路径中，点 $2$ 一定是距离标记点最近的点，所以输出 $5$。

从点 $1$ 到点 $4$ 的路径中，由于点 $1$ 被标记，所以输出 $0$。

#### 样例 #2 解释

（详细解释无，有需要者可以自行打开 PPT 看本样例的图）

#### 数据规模与约定

- $2 \le n \le 10^5$，$1 \le m \le 2 \times 10^5$，$1 \le k \le n$，$1 \le q \le 10^5$，$1 \le l_i \le 1000$；
- $1 \le a_i,b_i,f_i,s_i,t_i \le n$，给出的图无重边，无自环，保证图联通；
- 对于任意一组 $(s_i,t_i)$，保证 $s_i\neq t_i$。

# 题解

## 作者：Ray662 (赞：2)

比较暴力的做法。

容易 Dijkstra 求出每个点距离其最近的标记点的距离，设为 $f_i$。

考虑按照 $f$ 从大到小将每个点加入。每次对于一个 $i$，如果其相邻点 $j$ 满足 $f_j \ge f_i$，就将 $i, j$ 连边（枚举相邻点可以暴力枚举，因为每条边只会遍历两次）。如果某一个时刻 $u, v$ 连通了，那么询问 $(u, v)$ 的答案即为最后加入的点 $i$ 的 $f_i$。

考虑并查集维护。将每个询问 $(u, v)$ 的编号挂在 $u$ 和 $v$ 上，这个可以 set 维护，记为 $S_u$。每次两个点 $i, j$ 连边，可以直接回答 $S_i \cap S_j$ 的询问了。随后将能回答的删掉，其他的暴力 merge 起来。利用启发式合并，将 $S_i, S_j$ 中 size 较小的 merge 到 size 较大的，复杂度正确。

总复杂度 $O(m \log m + n \log n \log q)$。最慢点 273 ms。

[code](https://atcoder.jp/contests/joi2012ho/submissions/62977882)

---

## 作者：XCDRF_ (赞：1)

# AT\_joi2012ho5 JOI 国のお祭り事情 (Festivals in JOI Kingdom) 题解

[原题传送门](https://atcoder.jp/contests/joi2012ho/tasks/joi2012ho5)

[更好的阅读体验](https://www.luogu.com.cn/article/ddpshzyo)

## 解题思路

因为这个题用到了 Kruskal 重构树，所以我先讲一下。

相信大家都学过最小生成树，其中 Kruskal 算法的实现逻辑就是：先按边权排序，然后判断两点是否连通，如果不连通，就加到生成树里。但这个方法有个弊端，就是并查集会路径压缩，压缩后会丢失掉边权的大小关系。这时，我们就可以用 Kruskal 重构树解决这个问题。

Kruskal 重构树与普通 Kruskal 算法的唯一区别就是从点向点连边改为从点向点集连边。这里用最小生成树举例。比如下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rul4yr52.png)

这张图的最小生成树就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/nx9mbv7d.png)

是原图的子图。

但这张图的 Kruskal 重构树是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ca65vf4d.png)

连边时，新建一个节点，表示新集合，再由这个点向两个点所在的集合连边。边权和原来一样，这个点的点权为这两条边的边权。这样就建出了一棵重构树。

这棵树有如下性质：

1. 任意两点之间的边权最大值是它们的 lca 的点权。也就是说生成树上的两点边权瓶颈就是重构树上它们的 lca 的点权。
2. 除了叶子节点以外，其余节点都代表了一条边的信息。
3. 自下而上所有的边边权是单调不降的，除叶子结点外，自下而上所有点的点权也是单调不降的。
4. 实际上这棵树就是一个二叉堆。

再讲这个题的做法。

题目要求路径上距离标记点最近的点里标记点最远。到标记点的距离好求，一个多起点的 Dijkstra 就可以。现在我们得到了点权，但并不好处理，于是先把它们转化为边权。这样题目就变成了求两点之间路径最小边权的最大值（就是[货车运输](https://www.luogu.com.cn/problem/P1967)）。我们就可以按最大生成树建出 Kruskal 重构树，找到两点的 lca，输出点权即可。

## 参考代码

代码中使用了 dfs 序求 lca，有兴趣的话可以去[模板区](https://www.luogu.com.cn/problem/solution/P3379)看一下。

```cpp
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=5e5+5;
int n,m,k,l,tot,tot2,dfnn,cnt;
int head[N],h[N],dis[N],f[N],dfn[N],st[N][25];
bool vis[N];
priority_queue<pii,vector<pii>,greater<pii>> q;
struct Edge{
	int nxt,to,w;
}edge[N],e[N];
struct E{
	int f,t,w;
	friend bool operator<(E a,E b){//需要排序，重载一下小于号
		return a.w>b.w;
	}
}ee[N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void add(int x,int y,int w){
	edge[++tot]={head[x],y,w};
	head[x]=tot;
}
void add2(int x,int y,int w){
	e[++tot2]={h[x],y,w};
	h[x]=tot2;
}
void dijk(int s){//dijkstra
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(mp(0,s));
	while(!q.empty()){
		pii t=q.top();
		q.pop();
		int x=t.se;
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nxt){
			int xx=edge[i].to;
			if(dis[xx]>dis[x]+edge[i].w) dis[xx]=dis[x]+edge[i].w;
			q.push(mp(dis[xx],xx));
		}
	}
}
int get(int x,int y){
	return dfn[x]<dfn[y]?x:y;
} 
void dfs(int x,int fa){
	dfn[x]=++dfnn;
	st[dfnn][0]=fa;
	for(int i=h[x];i;i=e[i].nxt){
		int xx=e[i].to;
		dfs(xx,x);
	}
}
int lca(int x,int y){
	if(x==y) return x;
	x=dfn[x],y=dfn[y];
	if(x>y) swap(x,y);
	int d=log2(y-x);
	x++;
	return get(st[x][d],st[y-(1<<d)+1][d]);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k>>l;
	for(int i=1,x,y,z;i<=m;i++){
		cin>>x>>y>>z;
		add(x,y,z);//为跑最短路建边
		add(y,x,z);
		ee[i]={x,y,0};//存下来每一条边的起点，终点，和边权
	}  
	n++;
	for(int i=1,x;i<=k;i++){
		cin>>x;
		add(n,x,0);
	}
	dijk(n);
	for(int i=1;i<=m;i++) ee[i].w=min(dis[ee[i].f],dis[ee[i].t]);//边权为两端点的最小值
	sort(ee+1,ee+m+1);//按边权从大到小排序
	cnt=n;
	for(int i=1;i<(n<<1);i++) f[i]=i;
	for(int i=1;i<=m;i++){
		int x=find(ee[i].f),y=find(ee[i].t);
		if(x!=y){
			add2(++cnt,x,ee[i].w);//建 Kruskal 重构树
			add2(cnt,y,ee[i].w);
			f[x]=f[y]=cnt;
		} 
	}
	dfs(cnt,0);
	for(int j=1;j<=log2(n)+1;j++)
		for(int i=1;i+(1<<j)-1<(n<<1);i++) st[i][j]=get(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i=1,x,y;i<=l;i++){
		cin>>x>>y;
		cout<<e[h[lca(x,y)]].w<<'\n';//找到lca输出点权
	}
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/joi2012ho/submissions/64612522)

---

## 作者：11400F (赞：0)

## [JOI2012T5 JOI 国のお祭りの事情 IN Lv.15](https://www.luogu.com.cn/problem/AT_joi2012ho5)

[不知道怎么样的阅读体验](https://www.11490dx.net/2025/02/14/ds-hld/#JOI2012T5-JOI-%E5%9B%BD%E3%81%AE%E3%81%8A%E7%A5%AD%E3%82%8A%E3%81%AE%E4%BA%8B%E6%83%85-IN-Lv-15)

---

这道题要让我们求出路径的距离有标记的点的长度的最小值，那么肯定就要求路径上的每一个点距离有标记的点的长度的最小值了。

那么就可以首先预处理出所有点到有标记的点的最小距离。这个多源点 Dijkstra 再取最小值不好弄，就可以将超级源点向所有有标记的点连一条有向边，然后从超级源点跑一遍单源 Dijkstra 就可以了。

现在求出了所有的点到有标记的点的值。及其为 $val$。那么我们就要求一条从 $s \to t$ 的路径 $P$ 使 $\min_{u \in P}(val_u)$ 最大。那么我们就可以建一条最大生成树。因为一条路径必定有边，所以可以设边 $(u,v)$ 的权值为 $\min(val_u, val_v)$ 来求最大生成树。这样就可以保证整条路径取的 $\min$ 不漏。之后你走路径从 $s$ 到 $t$ 也就只会从这棵生成树上走了。（注：建最大生成树的方法和最小生成树相同。）

所以最终答案就是最大生成树上链 $s \to t$ 的 $\min$ 值了。可以使用树链剖分 + $\min$ 线段树处理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
const int M = 2e5+5;
struct Edge{
    int u, v, w;
}alledge[M];
bool cmp(Edge x, Edge y){
    return x.w > y.w;
}
typedef pair<int,int> pii;
vector<pii> edge[N];
int cnt;
void add(int u, int v, int w){
    edge[u].push_back({v, w});
    edge[v].push_back({u, w});
    alledge[++cnt] = {u, v, w};
}
int n, m, k, q;
int f[N];
int dis[N];
bool vis[N];
void Dijkstra(int x);
struct DSU{
    int fa[N], siz[N];
    void init(int x);
    int getfa(int x);
    void merge(int x, int y);
}dsu;
int fa[N], dep[N], son[N], idx[N], ord[N], top[N], siz[N], idxcnt;
void dfs1(int x, int father);
void dfs2(int x, int topx);
struct Minimum_Seg_Tr{
    int val[N<<2];
    void pushup(int x);
    void build(int x, int l, int r);
    int query(int x, int l, int r, int ql, int qr);
}segtr;
int query(int x, int y); // 树链剖分 query 路径最小值
void init(){
    // 建超级源点跑 Dijkstra 求得每一个点离有标记的点的最小距离
    for(int i=1;i<=k;i++){
        edge[0].push_back({f[i], 0});
    }
    Dijkstra(0);
    // 然后开始根据点的距离建最大生成树，边权为这两个点的 dis 的 min
    for(int i=0;i<=n;i++) edge[i].clear();
    for(int i=1;i<=m;i++){
        int u = alledge[i].u, v = alledge[i].v;
        alledge[i].w = min(dis[u], dis[v]);
    }
    sort(alledge+1, alledge+1+m, cmp);
    dsu.init(n);
    for(int i=1;i<=m;i++){
        int u = alledge[i].u, v = alledge[i].v, w = alledge[i].w;
        int x = dsu.getfa(u), y = dsu.getfa(v);
        if(x == y) continue;
        // cerr<<u<<" --"<<w<<"--> "<<v<<'\n';
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
        dsu.merge(x, y);
    }
    // 建完最大生成树之后，开始树剖。因为要求路径的 min 值，所以树剖+线段树
    dfs1(1, 0);
    dfs2(1, 1);
    segtr.build(1, 1, n);
}
int main(){
    cin>>n>>m>>k>>q;
    int u, v, w;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        add(u, v, w);
    }
    for(int i=1;i<=k;i++){
        cin>>f[i];
    }
    init();
    while(q--){
        int x, y;
        cin>>x>>y;
        cout<<query(x, y)<<'\n';
    }
    return 0;
}
```

---

