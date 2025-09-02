# [ABC383E] Sum of Max Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc383/tasks/abc383_e

頂点に $ 1 $ から $ N $ の番号が、辺に $ 1 $ から $ M $ の番号が付いた $ N $ 頂点 $ M $ 辺の重み付き単純連結無向グラフが与えられます。辺 $ i $ $ (1\ \leq\ i\ \leq\ M) $ は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結び、重みは $ w_i $ です。

あるパスに対してその重みをそのパスに含まれる辺の重みの最大値とします。 また、$ f(x,y) $ を 頂点 $ x $ から頂点 $ y $ へのパスの重みとしてありえる最小値とします。

長さ $ K $ の数列 $ (A_1,A_2,\ldots,A_K) $ と $ (B_1,B_2,\ldots,B_K) $ が与えられます。ここで、$ A_i\ \neq\ B_j $ $ (1\ \leq\ i,j\ \leq\ K) $ が成り立つことが保証されます。

数列 $ B $ を自由に並べ替えて、$ \displaystyle\sum_{i=1}^{K}f(A_i,B_i) $ を最小化してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min(\frac{N\ \times\ (N-1)}{2},2\ \times\ 10^5) $
- $ 1\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ w_i\ \leq\ 10^9 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ K) $
- $ A_i\ \neq\ B_j $ $ (1\ \leq\ i,j\ \leq\ K) $
- 与えられるグラフは単純かつ連結
- 入力は全て整数

### Sample Explanation 1

$ B $ を並び替えて、$ B=(2,4,4) $ としたとき、 - $ f(1,2)=5 $ : 頂点 $ 1 $ から頂点 $ 4 $ を経由し頂点 $ 2 $ に行くパスがあり、辺 $ 3 $ の重み $ 5 $ が最大値を取ります。また、辺の重みの最大値が $ 4 $ 以下になるようなパスは存在しないため $ 5 $ が最小値です。 - $ f(1,4)=2 $ : 頂点 $ 1 $ から頂点 $ 3 $ を経由し頂点 $ 4 $ に行くパスがあり、辺 $ 1 $ の重み $ 2 $ が最大値を取ります。また、辺の重みの最大値が $ 1 $ 以下になるようなパスは存在しないため $ 2 $ が最小値です。 - $ f(3,4)=1 $ : 頂点 $ 3 $ から頂点 $ 4 $ への辺を通るパスがあり、辺の重みは $ 1 $ でこれが辺の重みの最大値です。また、パスの重みが $ 0 $ 以下になることはないため $ 1 $ が最小値です。 よって、この場合 $ \displaystyle\ \sum_{i=1}^{3}f(A_i,B_i)=5+2+1=8 $ となります。また、$ B $ をどのように並び替えても $ 7 $ 以下になることはないため、答えは $ 8 $ です。

## 样例 #1

### 输入

```
4 4 3
1 3 2
3 4 1
2 4 5
1 4 4
1 1 3
4 4 2```

### 输出

```
8```

## 样例 #2

### 输入

```
3 3 2
1 2 5
2 3 2
1 3 1
1 1
2 3```

### 输出

```
3```

# 题解

## 作者：gesong (赞：10)

题目传送门：[[ABC383E] Sum of Max Matching](https://www.luogu.com.cn/problem/AT_abc383_e)。
# 思路
考虑**贪心**。

首先对于任意两个点 $u,v$ 的 $f$ 值的路径一定出现在这个图的最小生成树上，于是我们一开始预处理最小生成树，由于我们需要尽量小的代价，于是我们将所有的树边按照边权排序，然后按照如下方法贪心：

考虑一个慢慢加边的过程：设当前的边为 $(u,v)$，设以 $i$ 为子树的 $A$ 数组的个数为 $sza_i$，$B$ 数组的个数为 $szb_i$，我们要尽量让 $u$ 的子树和 $v$ 的子树的 $A,B$ 数组匹配，于是就按照代码中的分类讨论即可，然后将这条边加入图中。

用并查集维护一下加边即可，具体的细节可以看代码。
# 代码

由于笔者比较懒，于是将最小生成树的 Kruskal 算法和本题贪心合在一起。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int f[N];
int find(int x){
	if (f[x]==x) return x;
	return f[x]=find(f[x]);
}
struct nord{
	int u,v,w;
	bool operator <(const nord &x) const{
		return w<x.w;
	}
}a[N];
int sza[N],szb[N],vis[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int n=read(),m=read(),k=read();
	for (int i=1;i<=m;i++) a[i]={read(),read(),read()};
	sort(a+1,a+m+1);
	for (int i=1;i<=k;i++) sza[read()]++;
	for (int i=1;i<=k;i++) szb[read()]++;
	for (int i=1;i<=n;i++) f[i]=i;
	int ans=0;
	for (int i=1;i<=m;i++){
		int u=a[i].u,v=a[i].v,w=a[i].w;
		if (find(u)==find(v)) continue;
		u=find(u),v=find(v);
		int cnt=0;
		if (sza[u]>=szb[v]) cnt+=szb[v],sza[u]-=szb[v],szb[v]=0;
		else cnt+=sza[u],szb[v]-=sza[u],sza[u]=0; 
		if (szb[u]>=sza[v]) cnt+=sza[v],szb[u]-=sza[v],sza[v]=0;
		else cnt+=szb[u],sza[v]-=szb[u],szb[u]=0;
		ans+=w*cnt;
		sza[u]+=sza[v],szb[u]+=szb[v];
		f[v]=u;
	}
	cout <<ans;
    return 0;
}
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
```

---

## 作者：cqsunny (赞：5)

由于求最大的最小，最开始想到二分。

如果直接二分边权判断是否能够联通，复杂度会炸。

-----

思考一下：二分在做什么？

二分其实就是将边权小于等于二分值的边连接起来，判断是否联通。也就是最小生成树。

因此，我们可以将二分转化为 Kruskal，将边权从小到大排序，每次取出端点 $a, b$，边权为 $w$，找到 $a, b$ 代表 $t1, t2$，判断 $t1, t2$ 之间是否有边相连。如果有，就忽略这条边。如果没有，则将 $t1$ 的集合和 $t2$ 的集合合并。

-----

接下来是如何维护 $a$ 和 $b$ 的问题。

拿两个数组 $mp1, mp2$ 分别记录第 $i$ 个点在 $a/b$ 中出现的次数。在合并 $t1$ 和 $t2$ 时，将 $t1$ 和 $t2$ 的个数合并到新的代表处（假设为 $t2$），并且答案增加 $\min(mp1_{t2}, mp2_{t2}) \times w$。由于已经连接了 $\min(mp1_{t2}, mp2_{t2})$ 条边，所以 $t1$ 和 $t2$ 对连接的需求也需要减少 $\min(mp1_{t2}, mp2_{t2})$ 条。

然后本题就做完了，记得开 `long long`。

附上重点代码：
```cpp
u 为并查集，a 为边的数组（x,y,z 分别为端点，端点，边权）
mp1,mp2 记录 a,b 的个数
//初始化并查集
for(int i = 1; i <= n; ++ i){
	u[i] = i;
}
//输入并统计 a,b
for(int i = 1; i <= k; ++ i){
	scanf("%d", &x);
	mp1[x] ++;
}
for(int i = 1; i <= k; ++ i){
	scanf("%d", &x);
	mp2[x] ++;
}
sort(a + 1, a + m + 1, cmp);//按边权从小到大
int ans = 0;
for(int i = 1; i <= m; ++ i){
	int t1 = get_father(a[i].x), t2 = get_father(a[i].y);//找到代表
	if(t1 == t2){
		continue;
	}
	//合并
	u[t1] = t2;
	mp1[t2] += mp1[t1];
	mp2[t2] += mp2[t1]; 
	int minn = min(mp1[t2], mp2[t2]);
	ans += minn * a[i].z;
	mp1[t2] -= minn, mp2[t2] -= minn;
}
```

---

## 作者：MMXIandCCXXII (赞：4)

$\Large{\text{Solution}}$

看题解知道了这种像 $\text{Kruskal}$ 的巧妙方法，第一次了解到 $\text{Kruskal}$ 重构树就是这样的。

将边权从小到大排序后依次加入并查集，不难发现已经在一个连通块里的点都可以在不经过比最后一条被加入的边边权更大的边互相到达。

进一步可以发现如果一个起点 $i$ 和一个终点 $j$ 所在连通块在加入某条长 $w$ 边时被连通，$f(i,j)=w$。

这时我们就可以通过一个并查集记录连通块以及连通块的起点、终点数，加边时统计有多少对起点和终点之间的最大边权是这条边即可。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int u, v, w;
} e[200010];
bool cmp(node x, node y)
{
    return x.w < y.w;
}
int f[200010], st[200010], ed[200010];
int find(int x)
{
    if (f[x] == x) return x;
    return f[x] = find (f[x]);
}

signed main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= k; i++)
    {
        int x;
        cin >> x;
        st[x]++;
    }
    for (int i = 1; i <= k; i++)
    {
        int x;
        cin >> x;
        ed[x]++;
    }
    sort (e + 1, e + m + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        u = find (u), v = find (v);
        if (u == v) continue;
        f[u] = v, st[v] += st[u], ed[v] += ed[u];
        int minn = min (st[v], ed[v]);
        st[v] -= minn;
        ed[v] -= minn;
        ans += minn * w;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Hanggoash (赞：3)

# ABC383E 题解

## 题意

给定一张包含 $n$ 个节点和 $m$ 条无向带权边的图，以及两个序列 $A_k,B_k$ 分别表示图中的某些节点，定义 $f(A_i,B_j)$ 为从 $A_i$ 到 $B_j$ 所有路径各自包含的边权最大值中的最小值，可以任意排列 $B$ 中的元素，使得 $\sum_{i=1}^kf(A_i,B_i)$ 最小化，求出这个最小值。

## 分析

### 结论

转化为最小生成树的问题，贪心，在 Kruskal 的过程中额外记录一下每个点集中待匹配的 $A,B$ 元素个数，每次连接两个不连通点集 $V_1,V_2$ 的时候，尽可能多地把 $V_1$ 中的 $A$ 和 $V_2$ 中的 $B$ 匹配，把 $V_1$ 中的 $B$ 和 $V_2$ 中的 $A$ 匹配，代价为：当前边的边权 乘以 匹配数。

### 证明1

首先，需要明确为什么“当前边的边权”是路径中的“边权最大值”。

根据 Kruskal 算法的原理，我们先对边权进行了排序，那么我们一定是按照边权大小升序排序来枚举边。

假设在枚举过程中，当前枚举到了一条权值为 $w$，可以连接 $u$ 和 $v$ 两个未连通点的边，那么我们会选择这条边，并把 $u,v$ 所在集合连接起来，所以 $u$ 到 $v$ 路径中一定包含了这条边（因为在最后的最小生成树中，任意两节点之间的路径唯一），并且这条边的边权是当前考虑过的所有边中最大的，显然它也是这条路径上最大的。

在之后对边的枚举中，任何选取都不会对 $u,v$ 路径产生影响了。

### 证明2

然而这条最小生成树中的路径的情况，只是一条路径的边权最大值，那么它为什么是 $u$ 到 $v$ 所有路径的边权最大值中的“最小值”呢？

采用反证法，记我们在最小生成树的流程中选出来的这条边的边权为 $MX1$ ，假设存在另一条以 $MX2$ 为边权最大值的路径，使得 $MX2<MX1$，那么画个图思考一下会发现，我们根本就不会选择 $MX1$ 这条边作为最小生成树的一部分，矛盾，所以假设不成立。

### 证明3

至于为什么要"尽可能多地匹配"，这一点从贪心地角度想应该是很明了的，由于 $B$ 内部是可以取任意顺序的，又因为我们枚举边的顺序是从小到大，无论如何都要做满 $k$ 次匹配，那肯定是让每一次匹配尽量产生较小的答案，最后的答案一定是最小的。

### 细节
1. $A$ 和 $B$ 彼此之间没有交集，但是不代表集合内部不重，从样例就可以看出来。
2. 开 longlong。
## Code

```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
const int N=2e5+10;
struct Edge
{
    int u,v,w;
    const bool operator <(Edge tmp)const{return w<tmp.w;}
}e[N];
int a[N],b[N];
int fa[N];
int siza[N],sizb[N];
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1,u,v,w;i<=m;++i)
    {
        cin>>u>>v>>w;
        e[i]={u,v,w};
    }
    for(int i=1;i<=k;++i)cin>>a[i],siza[a[i]]++;
    for(int i=1;i<=k;++i)cin>>b[i],sizb[b[i]]++;
    for(int i=1;i<=n;++i)fa[i]=i;
    sort(e+1,e+m+1);
    int ans=0;
    for(int i=1;i<=m;++i)
    {
        int fx=find(e[i].u),fy=find(e[i].v);
        if(fx==fy)continue;
        int w=e[i].w;
        int mn=min(siza[fx],sizb[fy]);
        ans+=w*mn,siza[fx]-=mn,sizb[fy]-=mn;
        
        mn=min(sizb[fx],siza[fy]);
        ans+=w*mn,sizb[fx]-=mn,siza[fy]-=mn;

        fa[fx]=fy;
        siza[fy]+=siza[fx],sizb[fy]+=sizb[fx];
        siza[fx]=0,sizb[fx]=0;
        //merge
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Dream_poetry (赞：2)

### 思路：

我们发现对于那些大的边权一定不会经过，即若有多条路径从 $i$ 走到 $j$，也就是出现了环的情况下，我们肯定想办法不会经过边权最大的那条边，所以这条边可以删去。

然后显然最小生成树。

记录一下每个点起始和终止的差值，跑 kruskal 时我们必然要合并两个集合，在此时我们考虑左右两个集合还有多少个点没有被配对，两者取 $\min$ 乘该边边权计入答案即可。

当最小生成树合并完之后，答案也就统计完了。

### 代码：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,fa[200005],sum[200005];
pair<int,pair<int,int> > e[200005];
int ans;
inline int find(int x){
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>e[i].second.first;
		cin>>e[i].second.second;
		cin>>e[i].first;
	}
	sort(e+1,e+m+1);
	for(int i=1;i<=k;i++){
		int x;
		cin>>x;
		sum[x]++;
	}
	for(int i=1;i<=k;i++){
		int x;
		cin>>x;
		sum[x]--;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int w=e[i].first;
		int x=e[i].second.first;
		int y=e[i].second.second;
		x=find(x);
		y=find(y);
		if(x==y){
			continue;
		}
		if(sum[x]>0&&sum[y]<0){
			int d=min(sum[x],-sum[y]);
			ans+=w*d;
			sum[x]-=d;
			sum[y]+=d;
		}
		else if(sum[x]<0 && sum[y]>0){
			int d=min(-sum[x],sum[y]);
			ans+=w*d;
			sum[x]+=d;
			sum[y]-=d;
		}
		sum[x]+=sum[y];
		fa[y]=x;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：11400F (赞：1)

### AT_ABC383_E 题解

#### 题目大意

有一个 $N$ 个点，$M$ 条边的简单连通无向图，每一条**边**有一个权值，定义一条**路径**的权值为这条路径上所有的边的权值的最大值，$f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中权值最小的路径的权值。

给定了我们一个起点序列 $A$ 和终点序列 $B$，并且 $A$ 中的元素和 $B$ 中的元素无交。让我们将 $B$ 自由排列使 $\displaystyle\sum_{i=1}^{K} f(A_i, B_i)$ 最小。

#### 思路

看到这道题我们首先就可以想到对这些边按照边权的从小到大进行排序。然后从 $1$ 到 $M$ 遍历这些边。

因为我们知道，一条边是连接了两个点的，所以他最多会让两个不同的连通块 $U, V$ 通过这条边而互相连通。

又知道，因为是从边权值从小到大遍历的，所以 $U$ 里面的点想到 $V$ 那里去，就必须走这一条新边。

所以我们可以先把这两个连通块合并，然后统计这两个连通块里面一共有多少个起点和终点。如果又有起点又有终点，那么就定义一个值 $bas$ 为起点数和终点数的最小值，因为你只能两两匹配。把这个最小值乘上这条边边权作为对答案的贡献，然后再让新的连通块的起点数和终点数同时减去 $bas$ 即可。这样就能做到贪心选最优。因为你走其他路肯定是不比这条路优的，因为这条边边权都要小于等于后面边的边权。

用并查集维护连通块和每一个连通块的起点个数、终点个数即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
int n, m, k;
typedef long long ll;
struct Edge{
    int from, to, w;
}edge[N];
namespace DSU{
    int fa[N], sttcnt[N], eddcnt[N];
    void init(){
        for(int i=1;i<=n;i++){
            fa[i] = i;
        }
    }
    int getfa(int x){
        return (fa[x]==x)?x:fa[x]=getfa(fa[x]);
    }
}
using namespace DSU;
bool cmp(Edge x, Edge y){
    return x.w < y.w;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>k;
    int u, v, w;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        edge[i] = {u, v, w};
    }
    init();
    for(int i=1;i<=k;i++){
        cin>>u;
        sttcnt[u] ++;
    }
    for(int i=1;i<=k;i++){
        cin>>u;
        eddcnt[u] ++;
    }
    ll ans = 0;
    sort(edge+1, edge+1+m, cmp);
    for(int i=1;i<=m;i++){
        int x = getfa(edge[i].from), y = getfa(edge[i].to);
        if(x == y) continue;
        fa[x] = y;
        sttcnt[y] += sttcnt[x];
        eddcnt[y] += eddcnt[x];
        if(sttcnt[y] && eddcnt[y]){
            ll bas = min(sttcnt[y], eddcnt[y]);
            ans += (bas * edge[i].w);
            sttcnt[y] -= bas;
            eddcnt[y] -= bas;
        }
    }
    cout<<ans;
    
    
    return 0;
}
```

---

## 作者：VitrelosTia (赞：1)

似乎还算简单。但是前面的题写得太慢了。

看到“最小的最大边权”可以想到 kruskal 重构树，建出来之后问题转化到树上，有一些 A 点和一些 B 点，要两两匹配他们使得他们 LCA 的权值和最小，又考虑到 kruskal 重构树上点权单调递减，那我们肯定考虑要尽量把 LCA 往下放。对于一个点，递归完子树之后把剩下处理不了的点在这里处理掉就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 4e5 + 5;
int n, m, k, a[N], b[N];
struct edge { int u, v, w; } g[N];

struct Node { int ls, rs; } p[N];
namespace UnionSet {
	int fa[N];
	void init(int n) { for (int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { fa[find(x)] = find(y); }
} using namespace UnionSet;
int val[N], now;
void kruskal() {
	init(2 * n - 1);
	sort(g + 1, g + m + 1, [](edge x, edge y) { return x.w < y.w; });
	now = n;
	for (int i = 1; i <= m; i++) {
		int u = find(g[i].u), v = find(g[i].v), w = g[i].w;
		if (u != v) {
			val[++now] = w;
			merge(u, now); merge(v, now);
			p[now] = {u, v};
		}
	}
}

int ca[N], cb[N], ans;
void solve(int u) {
	if (p[u].ls) solve(p[u].ls);
	if (p[u].rs) solve(p[u].rs);
	ca[u] += ca[p[u].ls] + ca[p[u].rs];
	cb[u] += cb[p[u].ls] + cb[p[u].rs];
	while (ca[u] && cb[u]) ans += val[u], ca[u]--, cb[u]--;
}

signed main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) cin >> g[i].u >> g[i].v >> g[i].w;
	for (int i = 1; i <= k; i++) cin >> a[i], ca[a[i]]++;
	for (int i = 1; i <= k; i++) cin >> b[i], cb[b[i]]++;
	kruskal(); solve(now); cout << ans;
	return 0;
}
```

---

## 作者：Dtw_ (赞：1)

[at](https://atcoder.jp/contests/abc383/tasks/abc383_e)
## 题意
给你一张图，定义两个点的距离为这两个点的路径上边权最大的那个，给两个序列 $A,B$，$B$ 中的元素你可以随便换顺序，定义 $f(u, v)$ 为 $u$ 到 $v$ 路径的权值，求 $\min \sum_{i = 1}^k f(A_i, B_i)$。

## Solution
考虑路径的权值只和最大的边权相关，所以我们只关注路径上的最大值，所以我们可以跑最小生成树。

我们把 $A_i$ 称为起点，$B_i$ 称为终点。

然后我们考虑怎样算答案呢？肯定是先尽可能走小的边，那就是按照边权从小到大，考虑第 $i$ 条边，我们可以把第 $i$ 条边劈开，分成左边和右边，那就是看一下左边有多少起点右边有多少终点，同理左边有多少终点和右边多少起点，这就是经过这条边的路径条数，然后乘上这条边的边权就行。

具体的我们可以在跑最小生成树并查集合并的时候直接按照上述过程做就行。

$w_i \leq 10^9$ 所以别忘了开 `long long`。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10;

int n, m, a[N], b[N], k;

struct Edge
{
	int u, v, w;
} e[N];

int p[N];

int fifa(int x)
{
	if (p[x] == x) return x;
	return p[x] = fifa(p[x]);
}

int ans = 0;

bool join(int x, int y, int w)
{
	x = fifa(x), y = fifa(y);
	if (x != y)
	{
		p[x] = y;
		int c = min(a[x], b[y]);
		ans += w * c;
		a[x] -= c, b[y] -= c;
		c = min(b[x], a[y]);
		ans += w * c;
		b[x] -= c, a[y] -= c;
		a[y] += a[x];
		b[y] += b[x];
		return 1;
	}
	return 0;
}

bool cmp(Edge x, Edge y) { return x.w < y.w; }

void kruskal()
{
	sort (e + 1, e + m + 1, cmp);
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (join(u, v, w))
		{
			cnt++;
			if (cnt == n - 1) return;
		}
	}
}

signed main()
{
	fst
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		e[i] = {u, v, w};
	}
    for (int i = 1, x; i <= k; i++) cin >> x, a[x]++;
    for (int i = 1, x; i <= k; i++) cin >> x, b[x]++;
    kruskal();
	cout << ans;
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
看到题目很难不想到重构树。

不会的可以去学。

由于要让两点之间的路最短，所以考虑贪心。

可以证明，重构树从叶子到根节点点权依次增大，故每次加边时将两子树内的点分别连接即可。

统计数量即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005,M=1000005,L=19;
struct E
{
	int ne,to;
}e[2*M];
struct P
{
	int x,y,z;
}ee[M];
int he[N],idx,fath[N],idxp,a[N];
int fa[N][L+1],d[N],u[N],v[N];
int cnt1[N],cnt2[N];
void add(int x,int y)
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
}
bool cmp(P a,P b)
{
	return a.z<b.z;
}
int find(int x)
{
	if(x==fath[x])return x;
	return fath[x]=find(fath[x]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
		cin>>ee[i].x>>ee[i].y>>ee[i].z;
	for(int i=1;i<=k;i++)
	{
		cin>>u[i];
		cnt1[u[i]]++;
	}
	for(int i=1;i<=k;i++)
	{
		cin>>v[i];
		cnt2[v[i]]++;
	}
	sort(ee+1,ee+m+1,cmp);
	for(int i=1;i<=2*n;i++)fath[i]=i;
	idxp=n;
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		int x=find(ee[i].x),y=find(ee[i].y);
		if(x==y)continue;
		fath[x]=++idxp;
		fath[y]=idxp;
		add(idxp,x);
		add(idxp,y);
		int d=min(cnt1[x],cnt2[y]);//注意到一个子树内只有一种A或B的节点
		ans+=1ll*d*ee[i].z;
		cnt1[x]-=d;
		cnt2[y]-=d;
		d=min(cnt2[x],cnt1[y]);
		ans+=1ll*d*ee[i].z;//计算答案
		cnt2[x]-=d;
		cnt1[y]-=d;
		cnt1[idxp]=cnt1[x]+cnt1[y];
		cnt2[idxp]=cnt2[x]+cnt2[y];
		a[idxp]=ee[i].z;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[ABC383E] Sum of Max Matching](https://www.luogu.com.cn/problem/AT_abc383_e)

非常妙的贪心。

在 $\text{Kruskal}$ 重构树上考虑该问题。

在 $\text{Kruskal}$ 重构树上 $\text{DFS}$ 的过程中，实时维护 $sz1_u$ 和 $sz2_u$ 表示以 $u$ 为根的子树内未匹配的 $A$ 和 $B$ 的数量。能在当前节点匹配的数量就是 $\min\left(sz1_u, sz2_u\right)$，直接匹配即可。

因为 $\text{Kruskal}$ 重构树点权满足大根堆性质，故 $A$ 和 $B$ 在深度大的点匹配答案一定不劣。

时间复杂度 $O\left(n\log n\right)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k, ans, fa[400005], val[400005], A[400005], B[400005], sz1[400005], sz2[400005];

vector < int > G[400005];

struct node
{
	int u, v, w;
} a[200005];

bool cmp(node q, node p)
{
	return q.w < p.w;
}

int search(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = search(fa[x]);
}

void kruskal()
{
	int cnt = n;
	for (int i = 1; i <= 2 * n - 1; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u = search(a[i].u), v = search(a[i].v);
		if (u != v)
		{
			++cnt;
			fa[u] = fa[v] = cnt;
			val[cnt] = a[i].w;
			G[cnt].push_back(u);
			G[cnt].push_back(v);
			if (cnt == 2 * n - 1) break;
		}
	}
}

void dfs(int u)
{
	if (!G[u].size()) return;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		dfs(v);
	}
	sz1[u] = sz1[G[u][0]] + sz1[G[u][1]];
	sz2[u] = sz2[G[u][0]] + sz2[G[u][1]];
	if (sz1[G[u][0]] > 0 && sz2[G[u][1]] > 0)
	{
		ans += val[u] * min(sz1[G[u][0]], sz2[G[u][1]]);
		sz1[u] -= min(sz1[G[u][0]], sz2[G[u][1]]);
		sz2[u] -= min(sz1[G[u][0]], sz2[G[u][1]]);
	}
	else if (sz2[G[u][0]] > 0 && sz1[G[u][1]] > 0)
	{
		ans += val[u] * min(sz2[G[u][0]], sz1[G[u][1]]);
		sz1[u] -= min(sz2[G[u][0]], sz1[G[u][1]]);
		sz2[u] -= min(sz2[G[u][0]], sz1[G[u][1]]);	
	}
}

signed main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
		cin >> a[i].u >> a[i].v >> a[i].w;
	for (int i = 1; i <= k; i++)
		cin >> A[i];
	for (int i = 1; i <= k; i++)
		cin >> B[i];
	for (int i = 1; i <= k; i++)
		sz1[A[i]]++;
	for (int i = 1; i <= k; i++)
		sz2[B[i]]++;
	sort(a + 1, a + m + 1, cmp);
	kruskal();
	dfs(2 * n - 1);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
两个贪心。
- 所有两点之间的最短路径（一条路径的长度即为它经过的边权最大值）一定在最小生成树上，根据最小生成树性质易得。

- 每次在 $A$ 和 $B$ 中选择一对距离最短（$f(A_i,B_j)$ 最小）的消去，一定可以得到最优解。\
证明：反证，假设存在一对符合上述贪心的配对交换后得到更优解，设贪心的配对为 $(A_1,B_1),(A_2,B_2)$，其中 $f(A_1,B_1)\le\min(f(A_1,B_2),f(A_2,B_1),f(A_2,B_2))$，交换后为 $(A_1,B_2),(A_2,B_1)$。\
交换后更优，就要有 $f(A_1,B_1)+f(A_2,B_2)>f(A_1,B_2)+f(A_2,B_1)$\
然可以发现存在路线 $A_2\rightarrow B_1\rightarrow A_1\rightarrow B_2$\
所以 $f(A_2,B_2)\le\max(f(A_2,B_1),f(A_1,B_1),f(A_1,B_2))= \max(f(A_1,B_2),f(A_2,B_1))$\
而 $f(A_1,B_1)\le\min(f(A_1,B_2),f(A_2,B_1))$\
所以有 $f(A_1,B_1)+f(A_2,B_2)\le f(A_1,B_2)+f(A_2,B_1)$，矛盾。

考虑边排序生成最小生成树，每次加入边时，连通了两个块，在这个过程中如果发现 $A$ 中有一块内点而 $B$ 中有另一块内点，则消去，然后合并二块，消去一次就累加答案这条边的长度，因为边是按长度加入的，两个连通块连起来后这条边一定是它们的点之间最长的边。

这个过程需要平衡树，然而我们可以通过桶记录 $A$、$B$ 中结点所属的块（最小生成树需要并查集，这里可以直接使用并查集的根作为连通块号）解决，甚至连 set 都不需要。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int u,v,w;
};
int n,m,k,inp,f[200001],cnt,a[200001],b[200001];
long long ans;
node e[200001];
inline bool cmp(node a,node b){
	return a.w < b.w;
}
int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= m;i ++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e + 1,e + m + 1,cmp);
	for(int i = 1;i <= k;i ++) scanf("%d",&inp),a[inp] ++;
	for(int i = 1;i <= k;i ++) scanf("%d",&inp),b[inp] ++;
	for(int i = 1;i <= n;i ++) f[i] = i;//并查集初始化
	for(int i = 1;i <= m;i ++){
		int u = find(e[i].u),v = find(e[i].v);
		if(u == v) continue;
		cnt ++,f[u] = v;//以上为最小生成树部分
		int x = min(a[u],b[v]);
		a[u] -= x,b[v] -= x;//把 A 中的 u 和 B 中的 v 消除
		ans += (long long)x * e[i].w;
		x = min(a[v],b[u]);
		a[v] -= x,b[u] -= x;//把 A 中的 v 和 B 中的 u 消除
		ans += (long long)x * e[i].w;
		a[v] += a[u],b[v] += b[u];//u 连通块被并入到 v 中，A、B 中的 u 也要转换成 v
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

要某个和尽可能小，那么每项都得小，因此我们可以将边权从小到大排序。

提前记录每个点分别在 $a,b$ 中出现多少次。

对于每个新加的边，如果两个点不在同一个连通块的话，找出多少满足 $a_x$ 在 $l$ 的连通块内且 $b_y$ 在 $r$ 的连通块内的点对 $(x,y)$，其中 $l,r$ 是这条边的两个端点，将这些 $(x,y)$ 配对在一起，贡献必定是这条边的边权。

用并查集即可。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,p[200010],k,d[200010],e[200010],L;
long long ans;
struct edge{
	int a,b,c;
	bool operator<(const edge&t){return c<t.c;}
}s[200010];
void merge(int a,int b){p[a]=b,d[b]+=d[a],e[b]+=e[a];}
int find(int i){return (p[i]==i)?i:p[i]=find(p[i]);}
int main(){
	scanf("%d%d%d",&n,&m,&L);
	for(int w=1;w<=m;w++)scanf("%d%d%d",&s[w].a,&s[w].b,&s[w].c);
	for(int w=1;w<=L;w++)scanf("%d",&k),d[k]++;
	for(int w=1;w<=L;w++)scanf("%d",&k),e[k]++;
	for(int w=1;w<=n;w++)p[w]=w;
	sort(s+1,s+m+1);
	for(int w=1;w<=m;w++){
		int q=find(s[w].a),r=find(s[w].b);
		if(q==r)continue;
		int P=min(d[q],e[r]),Q=min(d[r],e[q]);
		ans+=1ll*P*s[w].c+1ll*Q*s[w].c,d[q]-=P,e[r]-=P,d[r]-=Q,e[q]-=Q,merge(q,r);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

### [[ABC383E] Sum of Max Matching](https://www.luogu.com.cn/problem/AT_abc383_e)

> $n$ 个点 $m$ 条边的无向图，给定 $a_{1\sim k},b_{1\sim k}$，任意排列 $b$，最小化 $\sum_{i=1}^{k} f(a_i,b_i)$，其中 $f(u,v)$ 为 $u$ 到 $v$ 最小瓶颈路上最大边权。$n,m,k\le 5\cdot 10^6$。

最小瓶颈路上最大边权，想到最小生成树，问题转化为树上点对最优匹配。

想到费用流，但数据范围不支持。

想到 kruskal 重构树，贪心地，我们希望优先匹配 lca 深度更大的 $(a_i,b_i)$，然而在重构树上这是不方便实现的。

考虑求最小生成树的过程，我们按边权从小到大枚举边，每次选一条边相当于连接了两个连通块，且**二者之间的最小瓶颈路最大边就是当前边**。

考虑合并两个连通块时将二者内剩余的未匹配的点对两两匹配，贪心可知正确性。

于是直接在并查集中维护连通块内未匹配的点数 $f$，具体地，初始时对于所有 $i$ 令 $f_{a_i}\gets f_{a_i}+1,f_{b_i}\gets f_{b_i}-1$。合并连通块 $u,v$ 时能匹配的点对数为 $\min\{|f_u|,|f_v|\}$，并令 $f_u\gets f_u+f_v$ 即可。时间复杂度 $\Theta(n\log n)$。

---

## 作者：201012280925LSY (赞：0)

## 题意
给你一个无向连通图，有 $N$ 个点，同时 $M$ 个双向边。

现在两个有长度为 $K$ 的序列 $A$ 和 $B$，定义一条路径的权值为路径上值最大的一条边的值，同时令函数 $f(x,y)$ 为在这个图上节点 $x$ 到节点 $y$ 的可行路径中权值最小的一条路径的权值。你可以任意排列序列 $A$ 和 $B$，请你输出最小的 $\sum_{i=1}^k f(A_i,B_i)$。

## 思路

讲一下为什么是用并查集来求答案。

因为你显然不可能真的去枚举 $A$ 和 $B$ 的排列，这样显然会超时。那么在看完题目之后，相信大家都已经猜到是通过计数然后乘上某个值，从而得到答案。

然后从路径的权值是通过路径上的最大值，所以我们可以先对输入的每条路径按值从小到大排列。

开始的时候，每一个点都是一个单独的点，而不与其他的点联通，之后才通过连边能够互相到达。假设我们新连的一条边连接了两个连通块 $U$ 和 $V$，而在 $U$ 中有一个点恰好是序列 $A$ 中一个点 $x$，而 $V$ 中也有一个点恰好是序列 $B$ 中一个点 $y$。所以 $f(x,y)$ 答案就是新连的这条边的值。因为从 $x$ 到 $y$ 你无论如何都要走新连的这条边，并且我们已经排过序了，所以新的这条边就一定是当前值最大的边。你也不可能继续等下一个连着 $U$ 和 $V$ 的边，因为那条边的值一定比这条边大。

所以维护联通块就得用并查集。剩下的按照讲的做即可。

具体细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=200010;
long long n,m,k,cnt_start[N],cnt_end[N];
long long answer;
struct Edge
{
	long long u,v,w;
}a[N];
bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}
long long fa[N];
long long find_father(long long x)
{
	if(fa[x]!=x)return fa[x]=find_father(fa[x]);
	else return x;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) 
	{
		cin>>a[i].u>>a[i].v>>a[i].w;
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=k;i++)
	{
		long long x;
		cin>>x;
		cnt_start[x]++;//记录在序列 A 中一个数出现了几次。
	}
	for(int i=1;i<=k;i++)
	{
		long long x;
		cin>>x;
		cnt_end[x]++; //记录在序列 B 中一个数出现了几次。
	} 
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		long long xx=find_father(a[i].u),yy=find_father(a[i].v);
		if(xx==yy)continue;//在同一个连通块里。
		fa[yy]=xx;//变成同一个连通块。
		cnt_start[xx]+=cnt_start[yy];//把在 yy 连通块里的起点和终点加到 xx 连通块里。 
		cnt_end[xx]+=cnt_end[yy];
		if(cnt_start[xx]&&cnt_end[xx])
		{
			long long minn=min(cnt_start[xx],cnt_end[xx]); //只能两两配对。
			answer+=minn*a[i].w; // 加上权值。
			cnt_start[xx]-=minn;
			cnt_end[xx]-=minn; 
		}
	}
	cout<<answer;//输出。
	return 0;
}

```

---

## 作者：YangRuibin (赞：0)

## 找性质
因为两个点路径的代价是途经边权的最大值，所以只有在图的**最小生成树**上的边才是有用的。因为最小生成树上的边权一定**不比**其余的大，且能保证任意两点连通。

## 求解过程
考虑 Kruskal 求最小生成树的过程，因为是从小到大加边，所以对于两个点，首次将它们连通的边权即为路径的最小代价。

如何快速得知两个点在某一时刻是否连通？我们可以建出 Kruskal 重构树，这两个点的 LCA 就代表它们首次连通的时间。对于树上的每个点，还需要记录如下信息。

- 产生这个点的边权，即对应路径的代价。
- 如果 $A_i$ 或 $B_j$ **首次**通过这条边与外界连通，则按所在序列分类记录。

因为建树是自下而上的，所以可以直接 DFS，在回溯时贪心匹配。如果有剩余的，就传到父节点上。

## 代码
~~赛时写的，可能有些乱。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5;//开两倍空间
int n,m,kk,head[N],tot,num,a[N],b[N],nn;
int ff[N],va[N],vb[N],ans,vva[N],vvb[N];
int ga[N],gb[N],ds[N];
//ga: 此节点对应的边首次连通的 A 点个数。
//gb: 此节点对应的边首次连通的 B 点个数。
//ds: 此节点对应的边权。
struct nodeedge{
	int from,to,dis;
	bool operator<(const nodeedge &x)const
	{
		return dis<x.dis;
	}
}ee[N];
struct node{
	int to,dis,next;
}edge[N*2];
void add(int from,int to,int dis)
{
	++num;
	ee[num].from=from;
	ee[num].to=to;
	ee[num].dis=dis;
}
void add2(int from,int to,int dis)
{
	++tot;
	edge[tot].to=to;
	ds[from]=dis;
	edge[tot].next=head[from];
	head[from]=tot;
}
int find(int x)
{
	if(ff[x]==x)return x;
	return ff[x]=find(ff[x]);
}
void dfs(int x,int fat)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fat)continue;
		dfs(to,x);
		ga[x]+=ga[to],gb[x]+=gb[to];//回溯时加上剩余的点
	}
	ga[x]+=vva[x];gb[x]+=vvb[x];
	while(ga[x]&&gb[x])
	{
		--ga[x],--gb[x];ans+=ds[x];
	}
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&kk);nn=n;
	for(int i=1,x,y,w;i<=m;i++)scanf("%lld%lld%lld",&x,&y,&w),add(x,y,w);
	for(int i=1;i<=kk;i++)scanf("%lld",a+i),va[a[i]]++;
	for(int i=1;i<=kk;i++)scanf("%lld",b+i),vb[b[i]]++;
	sort(ee+1,ee+num+1);
	for(int i=1;i<=n*2;i++)ff[i]=i;
	for(int i=1,cnt=1;cnt<n;i++)
	{
		int x=ee[i].from,y=ee[i].to;
		x=find(x),y=find(y);
		if(x==y)continue;
		++nn;ff[x]=ff[y]=nn;++cnt;
		if(va[ee[i].from])vva[nn]+=va[ee[i].from],va[ee[i].from]=0;
		if(vb[ee[i].from])vvb[nn]+=vb[ee[i].from],vb[ee[i].from]=0;
		if(va[ee[i].to])vva[nn]+=va[ee[i].to],va[ee[i].to]=0;
		if(vb[ee[i].to])vvb[nn]+=vb[ee[i].to],vb[ee[i].to]=0;
		add2(nn,x,ee[i].dis);
		add2(nn,y,ee[i].dis);
	}
	dfs(nn,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：luogu_starblue (赞：0)

~~感觉打完 NOIP 把脑子也打掉了，这次赛时就做出了 ABC 然后赛后做出了 DEF，毕竟现在是半退役选手了。~~

首先要想让 $f(x,y)$ 最小那么路径肯定是选择这张图最小生成树上的。

然后我们发现重排的本质是让 $A$ 和 $B$ 中选择一对进行配对。 

那么做最小生成树的时候并查集维护每个联通块中 $A$ 的个数和 $B$ 的个数，贪心地匹配，合并 $2$ 个联通块时若有可以匹配的 $A$ 或者 $B$，那么就用当前的边进行匹配，因为是这张图的最小生成树，所以是正确的。

可以通过比较联通块中 $A$ 和 $B$ 的数量来判断是否有可以匹配的 $A$ 或 $B$。 

时间复杂度就是最小生成树的复杂度 $O(m\log m)$。

具体见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+9;
struct node
{
	int u,v,w;
};
vector<node>G;
bool cmp(node x,node y)
{
	return x.w<y.w;
}
int f[maxn];
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
int siza[maxn],sizb[maxn];
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
	}
	while(m--)
	{
		int u,v,w;
		cin>>u>>v>>w;
		G.push_back({u,v,w});
	}
	for(int i=1;i<=k;i++)
	{
		int x;
		cin>>x;
		siza[x]++;
	}
	for(int j=1;j<=k;j++)
	{
		int x;cin>>x;
		sizb[x]++;
	}
	long long ans=0;
	sort(G.begin(),G.end(),cmp);
	for(auto it:G)//最小生成树 
	{
		int u=it.u,v=it.v,w=it.w;
		u=find(u),v=find(v);
		if(u==v)continue;
		f[v]=u;
		
		if(siza[u]>sizb[u])//通过比较 A 和 B 的数量来判断是否有可以匹配的 A 或 B。 
		{
			if(sizb[v]>siza[v])
			{
				ans+=1ll*min(siza[u]-sizb[u],sizb[v]-siza[v])*w;//u中的A与v中的B匹配。 
			}
		}
		swap(u,v);
		if(siza[u]>sizb[u])
		{
			if(sizb[v]>siza[v])
			{
				ans+=1ll*min(siza[u]-sizb[u],sizb[v]-siza[v])*w;//u中的B与v中的A匹配。 
			}
		}
		swap(u,v);
		siza[u]+=siza[v];//注意在匹配完成之后再进行size的合并 
		sizb[u]+=sizb[v];
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：kkxacj (赞：0)

#### 思路

容易想到一个贪心做法：按边权排序，每次合并，两边能匹配的都匹配。

考虑证明这个为什么是对的，若一对点在第 $i$ 条边可以被匹配，说明这两个点**一定无法通过走 $<w_i$ 与其它点匹配**，否则这个点会匹配完就不存在了，所以这一对匹配是最优的。

用个并查集每次合并，统计 $a,b$ 的个数就好了。

**code**


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10;
int n,m,k,c[N],d[N],f[N],head[N],siz[N],siz1[N],cnt,l,r,o,o1,ans;
struct w
{
	int x,y,z;
}a[N<<1];
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
bool cmp(w a,w b){return a.z < b.z;}
signed main()
{
	read(n),read(m),read(k);
	for(int i = 1;i <= n;i++) f[i] = i;
	for(int i = 1;i <= m;i++) read(a[i].x),read(a[i].y),read(a[i].z);
	sort(a + 1,a + 1 + m,cmp);
	for(int i = 1;i <= k;i++) read(c[i]),siz[c[i]]++;
	for(int i = 1;i <= k;i++) read(d[i]),siz1[d[i]]++;
	for(int i = 1;i <= m;i++) 
	{
		if(find(a[i].x) != find(a[i].y))
		{
			ans += min(siz[find(a[i].x)],siz1[find(a[i].y)])*a[i].z;
			ans += min(siz1[find(a[i].x)],siz[find(a[i].y)])*a[i].z;
			o = min(siz[find(a[i].x)],siz1[find(a[i].y)]),o1 = min(siz1[find(a[i].x)],siz[find(a[i].y)]);
			siz[find(a[i].x)] = siz[find(a[i].x)]+siz[find(a[i].y)]-o-o1;
			siz1[find(a[i].x)] = siz1[find(a[i].x)]+siz1[find(a[i].y)]-o-o1;
			f[find(a[i].y)] = find(a[i].x);
		}
		else 
		{
			ans += min(siz[find(a[i].x)],siz1[find(a[i].y)])*a[i].z;
			o = min(siz[find(a[i].x)],siz1[find(a[i].y)]);
			siz[find(a[i].x)] = siz[find(a[i].x)]-o;
			siz1[find(a[i].x)] = siz1[find(a[i].x)]-o;
		}
	}
	print(ans); flush();
	return 0;
}
```

---

## 作者：NOI_O2 (赞：0)

# [ABC383E] Sum of Max Matching 题解

## 题目概述

给定一个带权重的无向连通图，以及两个长度为 $K$ 的序列 $A$ 和 $B$。我们需要重新排列序列 $B$，使得 $\sum_{i=1}^{K} f(A_i, B_i)$ 的值最小，其中 $f(x, y)$ 表示从顶点 $x$ 到顶点 $y$ 的路径中，边权重的最大值的最小可能值。

## 解题思路

### 1. 预处理

首先，我们需要预处理出从每个顶点出发到其他所有顶点的路径中，边权重的最大值的最小可能值。这可以通过使用**二分查找**和**并查集**来实现。

#### 并查集

我们使用并查集来维护图的连通性，并快速判断两个顶点是否连通。

#### 二分查找

对于每个顶点 $u$，我们使用二分查找来确定从 $u$ 出发到其他顶点 $v$ 的路径中，边权重的最大值的最小可能值。具体步骤如下：

1. **初始化**：将所有边按权重从小到大排序。
2. **二分查找**：对于每个顶点 $u$，使用二分查找确定从 $u$ 出发到其他顶点 $v$ 的路径中，边权重的最大值的最小可能值。

### 2. 计算最小值

在预处理完成后，我们得到了从每个顶点出发到其他所有顶点的路径中，边权重的最大值的最小可能值。接下来，我们重新排列序列 $B$，使得 $\sum_{i=1}^{K} f(A_i, B_i)$ 的值最小。

#### 贪心算法

我们可以使用贪心算法来重新排列序列 $B$。具体步骤如下：

1. **初始化**：将序列 $B$ 按照从 $A$ 中对应顶点的路径权重最大值的最小可能值从小到大排序。
2. **计算结果**：按照排序后的序列 $B$ 计算 $\sum_{i=1}^{K} f(A_i, B_i)$ 的值。

## 赛时代码

```cpp
#include <bits/stdc++.h>

#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 200010

using namespace std;

int n,m,k,fa[N],sum[N];
pair<int,pair<int,int> > eds[N];
ll ans=0;
int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&eds[i].S.F,&eds[i].S.S,&eds[i].F);
		eds[i].S.F--,eds[i].S.S--;
	}
	sort(eds,eds+m);
	for(int i=0;i<k;i++)
	{
		int x;
		scanf("%d",&x);
		x--;
		sum[x]++;
	}
	for(int i=0;i<k;i++)
	{
		int x;
		scanf("%d",&x);
		x--;
		sum[x]--;
	}
	for(int i=0;i<n;i++) fa[i]=i;
	for(int i=0;i<m;i++)
	{
		int w=eds[i].F,x=eds[i].S.F,y=eds[i].S.S;
		x=getf(x),y=getf(y);
		if(x==y) continue;
		if(sum[x]>0&&sum[y]<0)
		{
			int d=min(sum[x],-sum[y]);
			ans+=1ll*w*d;
			sum[x]-=d,sum[y]+=d;
		}
		else if(sum[x]<0&&sum[y]>0)
		{
			int d=min(-sum[x],sum[y]);
			ans+=1ll*w*d;
			sum[x]+=d,sum[y]-=d;
		}
		sum[x]+=sum[y];
		fa[y]=x;
	}
	printf("%lld\n",ans);
	return 0;
}
```

## 总结

通过预处理每个顶点出发到其他所有顶点的路径中，边权重的最大值的最小可能值，并使用贪心算法重新排列序列 $B$，我们可以高效地解决这个问题。时间复杂度主要取决于预处理部分，为 $O(N \log N + M \log M)$，其中 $N$ 是顶点数，$M$ 是边数。

---

