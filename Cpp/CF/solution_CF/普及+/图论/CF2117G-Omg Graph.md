# Omg Graph

## 题目描述

给定一个带权无向连通图，定义一条长度为 $k$ 路径的费用如下：

- 设路径经过边的权值为 $w_1,w_2,\dots,w_k$。
- 路径的费用定义为 $(\min_{i=1}^k w_i) + (\max_{i=1}^k w_i)$，也就是最大的边权加上最小的边权。

请求出所有从结点 $1$ 到结点 $n$ 的路径中最小的费用。注意路径未必是简单路径。

## 说明/提示

对于第二个测试用例，最优路径之一是 $1 \rightarrow 2 \rightarrow 1 \rightarrow 3$。经过的边权分别为 $5,5,13$，因此费用为 $\min(5,5,13)+\max(5,5,13)=18$。可以证明不存在费用更低的路径。

## 样例 #1

### 输入

```
4
3 2
1 2 1
2 3 1
3 2
1 3 13
1 2 5
8 9
1 2 6
2 3 5
3 8 6
1 4 7
4 5 4
5 8 7
1 6 5
6 7 5
7 8 5
3 3
1 3 9
1 2 8
2 3 3```

### 输出

```
2
18
10
11```

# 题解

## 作者：CirnoNine9 (赞：5)

第一次写题解，来写一发我的做法(

### 观察 1

边权从小到大排序后加边，若从点 $1$ 出发能到达的最大边权为 $w$，那么最小边权就是从点 $1$ 出发可到达的最小边权。

### 观察 2

并查集可以完美实现以上内容。

### 实现
用并查集维护每个点可到达的最小边权，从小到大加边，更新从点 $1$ 出发可到达的最小边权，如果此时点 $1$ 可到达点 $n$，更新答案 $ans \gets \min(ans,w + \min\{点 1 可到达的边权\})$。

时间复杂度 $O(m\log m)$，复杂度瓶颈在对边排序。



参考代码：
```cpp
const int INF = 1e18;

struct DSU {
    vector<int> fa,sz,mn;
    
    DSU(int n) {
        fa.resize(n+1);
        sz.resize(n+1);
        mn.resize(n+1);
        iota(fa.begin(),fa.end(),0);
        fill(sz.begin(),sz.end(),1);
        fill(mn.begin(),mn.end(),INF);
    }
    
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    int qry(int x) {
        return mn[find(x)];
    }
    
    void merge(int u, int v, int w) {
        int X = find(u), Y = find(v);
        if (sz[X] < sz[Y]) swap(X,Y);
        mn[X] = min({mn[Y],mn[X],w});
        fa[Y] = X;
        sz[X] += sz[Y]; 
    }
    
    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<array<int,3>> e;
    for (int i = 1; i <= m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        e.push_back({w,u,v});
    }
    sort(e.begin(),e.end());

    DSU dsu(n);

    int ans = INF;
    for (auto [w,u,v] : e) {
        dsu.merge(u,v,w);
        if (dsu.same(1,n)) {
            ans = min(ans,w+dsu.qry(1));
        }
    }
    cout << ans << endl;
}
```

---

## 作者：yzjznbQWQ (赞：2)

# CF2117G 题解

[题目传送门](https://codeforces.com/problemset/problem/2117/G)

## 题目描述

给你一张带权无向联通图，让你找出一条从 $1$ 到 $n$ 的路径（可以不是简单路径），是得其所经过边的权值最大值加最小值最小。

## 思路

因为能重复经过某条边，我们可以参考最小生成树的思想，考虑枚举边权最大值，即将边按照从小到大的顺序加入图中，维护连通块最小边权值，在 $1$ 和 $n$ 连通时更新答案。

具体实现：将边按照边权排序，从小到大加入，对每个点维护一个他们此时所能达到最小边权的并查集，在加边时更新并查集，并检查 $1$ 和 $n$ 是否连通。若连通则将答案更新为：**当前枚举到的边权最大值+当前包含起点的连通块的最小边权**

复杂度 $O(m \log m + m \alpha(n))$，其中 $m$ 为边数，$\alpha(n)$ 为反阿克曼函数。

---

## 作者：sSkYy (赞：1)

## 题解

模拟寻找路径的过程，因为可以重复经过一条边，所以我们实际上是在从所有边中中挑出一些边来，使得挑出的边的集合满足题目的条件。

具体的，我们设**最终**选择出来的边的集合为 $S$，$S$ 中 $1$ 和 $n$ 是联通的，且费用最小，注意可能有多个满足要求的 $S$。

设一个空边集为 $V$，构造边集 $S$ 的方法就是将边按边权从小到大加入边集 $V$，$V$ 就会在某一时刻成为满足要求的 $S$，我们要做的事只有维护这个边集 $V$，并在满足 $1$ 和 $n$ 联通的前提下统计答案。

维护一个边集肯定是用**并查集**啦，并查集里要维护最大边权和最小边权，容易实现，详见代码。

为什么从小到大加入边是对的？

> 证明：如果先加边权更大的边再加边权小的边就可能漏掉费用更小且 $1$ 和 $n$ 联通的情况，反过来，先加边权小的边，即使最后该边不在最终路径里，但也不会使答案变劣，因为费用 $\min w_i +\max w_i$ 中的 $\max$ 肯定不会选中边权更小的边。

注意：不要一旦 $1$ 和 $n$ 联通就输出答案，这样可能会漏情况，全部边跑完即可，你也不差那点时间。

代码复杂度为 $O(m\log m+m\alpha(n))$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
struct edge{
    int u,v,w;
    bool operator < (const edge x)const{
        return w<x.w;
    }
}e[N];
struct DSU{
    int fa[N],mn[N],mx[N];
    void init(int n){for(int i=1;i<=n;i++) fa[i]=i,mn[i]=INT_MAX,mx[i]=INT_MIN;}
    int find(int x){
        if(x==fa[x]) return x;
        return fa[x]=find(fa[x]);
    }
    void merge(int x,int y,int z){
        int fx=find(x),fy=find(y);
        if(fx==fy) return;
        fa[fy]=fx;
        mn[fx]=min({mn[fx],mn[fy],z});
        mx[fx]=max({mx[fx],mx[fy],z});
    }
}dsu;
void solve(){
    cin>>n>>m;
    dsu.init(n);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        e[i]={u,v,w};
    }
    sort(e+1,e+m+1);
    int ans=INT_MAX;
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v,w=e[i].w;
        dsu.merge(u,v,w);
        int x=dsu.find(1),y=dsu.find(n);
        if(x==y) ans=min(ans,dsu.mx[x]+dsu.mn[x]);
    }
    cout<<ans<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：little_grass_sage (赞：1)

## 思路  
考虑从小到大加入边，通过并查集来维护集合和最小最大值。  
加入一条边后就统计一次答案。  
如果合并后 $1$ 和 $n$ 联通，设 $mi_i$ 是 $i$ 所在的集合中最小的一条边，$ma_i$ 是 $i$ 所在的集合中最大的一条边 ，此时将 $ans$ 设为 $\min(ans,mi_1+ma_1)$ 。  
## 证明  
假设现在有一个边的集合 $S$ 表示选择的边。    
如果最长边不在我们最后选择的路径中，则删掉最长边对答案没有影响，所以我们假设最长边在 $S$ 中。
既然最长边在我们最后选择的路径中，则将所有比这条边小的边加入集合一定不会让答案更大。  
所以剩下的所有 $S$ 就都是从小到大加入的边。  
## code  
~~码风有点差~~。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct st{
	int x,y,z;
	friend bool operator <(st x,st y){
		return x.z<y.z;
	}
}sz[200009];
int f[200009],ma[200009],mi[200009];
int gf(int x){
	if(f[x]!=x)f[x]=gf(f[x]);
	return f[x];
}
int main(){
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		int a,b;
		long long ans=2e10;
		cin>>a>>b;
		for(int i=1;i<=a;i++)f[i]=i,ma[i]=-1,mi[i]=1e9+7;
		for(int i=1,x,y,z;i<=b;i++)cin>>x>>y>>z,sz[i]={x,y,z};
		sort(sz+1,sz+b+1);
		for(int i=1;i<=b;i++){
			int x=sz[i].x,y=sz[i].y,z=sz[i].z;
			int fx=gf(x),fy=gf(y);
			if(fx==fy)continue;
			f[fx]=fy,ma[fy]=max({ma[fy],ma[fx],z}),mi[fy]=min({mi[fy],mi[fx],z});
			if(gf(1)==gf(a)){
				ans=min(ans,0ll+ma[gf(1)]+mi[gf(1)]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：dbywsc (赞：1)

## 思路

由于路径的代价之关系到最小边权和最大边权，所以我们可以接用 kruskal 算法的思想，枚举每一条边来比对最小答案。

将所有的边按边权升序排序，然后维护一个并查集，枚举到当前边的时候就将两个端点合并，同时维护一个数组 $best_{N}$ 表示当前连通块中边权最小的边。由于我们已经排序过所有的边了，因此枚举到当前边的时候可以将它当作目前边权最大的边进行计算。如果合并后点 $1$

和点 $n$ 处在同一个连通块中，设当前连通块为 $t$，此时答案应该取 $\min (ans, best_{t} +w_i)$，最后的最小值就是我们的答案。

需要注意的是这道题中要将上界设置的足够大（因为这个我吃了两发罚时。。。）

## 代码

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define endl '\n'
using i64 = long long;
const i64 INF = 4e18 + 10;
const int N = 2e5 + 10;
const int P = 1e9 + 7;
struct Edge {
    int u, v;
    i64 w;
    bool operator<(const Edge& x) {
        return w < x.w;
    }
};
int p[N];
i64 best[N];
int find(int x) {
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
void unite(Edge x) {
    int u = x.u, v = x.v; i64 w = x.w;
    u = find(u), v = find(v);
    if(u == v) {
        best[u] = std::min(best[u], w);
        return;
    }
    p[v] = u;
    best[u] = std::min({best[u], best[v], w});
}
void solve(void) {
    memset(best, 0x3f, sizeof(best));
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> e(m);
    for(int i =0 ; i < m; i++) {
        std::cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e.begin(), e.end());
    for(int i = 1; i <= n; i++) p[i] = i;
    i64 ans = INF;
    for(auto i : e) {
        unite(i);
        int l = find(1), r = find(n);
        if(l == r) {
            i64 t = i.w + best[l];
            ans = std::min(ans, t);
        }
    }
    std::cout << ans << endl;
}
int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while(t--) solve();
}
```

---

## 作者：nnn233 (赞：1)

## 思路
由于题目不要求简单路径，也就是可以走重复的点或边，于是我们可以从节点 $1$ 先走到一条钦定的最短边，接着原路返回节点 $1$，再走一条最短路（此处指路径上的最大权最小）到节点 $n$。

用 dijkstra 算法预处理出从节点 $1$ 到节点 $i$ 的最短路（此处指路径上的最大权最小），记作 $dis_i$。

枚举节点 $x$，设与 $x$ 节点相连的边的最小边权为 $mini_x$，尝试用 $mini_x+\max(dis_x,dis_n)$ 更新答案即可。
## 为什么这么做是对的？
感性理解：

答案由 $\max$ 与 $\min$ 两部分组成。  
$max$ 部分下界是 $dis_n$；  
而 $min$ 部分我们枚举了所有可能的边。
## CODE
```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
bool Mbe;
//#define int long long
#define pb emplace_back
typedef long long ll;
const int mod=1e9+7;
const int MOD=998244353;
const int N=2e5+50;
const int inf=2e9;
int T=1,Q;
int n,m,k,ans;
int a[N];
inline int in() {
    int w=1,x=0;
    char ch=0;
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch-'0');
        ch=getchar();
    }
    return x*w;
}
struct Edge{
    int v,w,nex;
}e[N<<1];
int fir[N],eCnt=1;
inline void add(int u,int v,int w=1){
    e[++eCnt]=(Edge){v,w,fir[u]},fir[u]=eCnt;
}
int dis[N],vis[N],mini[N];
struct node{
    int d,id;
};
inline bool operator >(const node &x,const node &y){return x.d>y.d;}
priority_queue<node,vector<node>,greater<node> > pq;
void dijkstra(int n, int s) {
    for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
    dis[s]=0;
    pq.push({0,s});
    while (!pq.empty()) {
        int u=pq.top().id;
        pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for (int i=fir[u];i;i=e[i].nex) {
            int v=e[i].v,w=e[i].w;
            if(dis[v]>max(dis[u],w))dis[v]=max(dis[u],w),pq.push((node){dis[v],v});
        }
    }
}
void solve(){
    eCnt=0,ans=inf;
    n=in(),m=in();
    for(int i=1;i<=n;++i)fir[i]=0,mini[i]=inf;
    for(int i=1,u,v,w;i<=m;i++){
        u=in(),v=in(),w=in();
        add(u,v,w);add(v,u,w);
        mini[u]=min(mini[u],w);
        mini[v]=min(mini[v],w);
    }
    dijkstra(n,1);
    for(int i=1;i<=n;i++)ans=min(ans,mini[i]+max(dis[i],dis[n]));
    cout<<ans<<"\n";
}
bool Med;
signed main(){
    T=in();
    while(T--){solve();}
    return 0;
}
/*
文件名: CF2118G.cpp
创建时间: 2025-06-12 10:21:22
作者: nnn233
*/
```

---

