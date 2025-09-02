# MST Unification

## 题目描述

给定一个无向带权连通图，包含 $n$ 个顶点和 $m$ 条边，图中没有自环和重边。

第 $i$ 条边为 $e_i = (u_i, v_i, w_i)$，表示顶点 $u_i$ 和 $v_i$ 之间有一条权值为 $w_i$ 的边（$1 \le w_i$）。该图是连通的，即对于任意一对顶点，都存在仅由图中边组成的路径将它们连接起来。

最小生成树（MST）是指在所有能够连接所有顶点的边的子集中，总权值最小的那一个（总权值为所选边权值之和）。

你可以对给定的图进行如下操作：将某条边的权值增加 $1$。每条边可以被增加多次（也可以不增加）。

假设初始最小生成树的权值为 $k$。你的任务是通过最少次数的操作，使得最终图的最小生成树权值仍为 $k$，但最小生成树是唯一的（即只有一种方式选择最小生成树）。

请计算完成上述目标所需的最少操作次数。

## 说明/提示

第一个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1108F/0e263a00ca735dd5bb719bb03756b985166a7027.png)

你可以将边 $(1, 6)$ 或 $(6, 3)$ 的权值增加 $1$，即可使最小生成树唯一。

最后一个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1108F/3b58146df4c5be6d2405c28ffabd0f9fc53a7d4b.png)

你可以将边 $(1, 5)$ 和 $(2, 4)$ 的权值各增加 $1$，即可使最小生成树唯一。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8 10
1 2 1
2 3 2
2 4 5
1 4 2
6 3 3
6 1 3
3 5 2
3 7 1
4 8 1
6 2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 3
2 1 3
4 3 4
2 4 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 2
1 3 3
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3 3
1 2 1
2 3 3
1 3 3
```

### 输出

```
1
```

## 样例 #5

### 输入

```
1 0
```

### 输出

```
0
```

## 样例 #6

### 输入

```
5 6
1 2 2
2 3 1
4 5 3
2 4 2
1 4 2
1 5 3
```

### 输出

```
2
```

# 题解

## 作者：良心WA题人 (赞：13)

# 原题链接

[洛谷的](https://www.luogu.com.cn/problem/CF1108F)

[CF的](http://codeforces.com/problemset/problem/1108/F)

[VJ的](https://vjudge.net/problem/CodeForces-1108F)

# 题目描述

QwQ又是被洛谷翻译按在地上摩擦的一天。。。直接引用

>给定一个有n个点，m条边的无向连通图，每条边有边权。 定义一次操作为：选择一条图中的边，并将其权值+1。试求最小的操作次数，使得操作后的图的最小生成树是唯一的。

# 解题思路
## 法一
这种和最小生成树有关的题，无非就是上来先求一下最小生成树，然后再仔细钻研最小生成树的性质怎么套上来。我们得到了一个最小生成树，考虑加上一条非树边之后会如何。加上一条边后会组成一个环，根据最小生成树的性质（在这里就不详细证明了），我们让这条边最大就不会有其他的最小生成树。如果这条边已经是最大了就直接忽略，反之则一定会等于环上除去这条边的边中最长的一条的权值，直接给这条边的权值加一即可。所以我们只需要解决找这个环上的最大值了，然而这又刚好是树上路径求最长边，直接倍增就行了。最后，用这个路径中的最长边和新加的这条边比较计算答案即可。

平均时间复杂度$\Theta(m\log m+n\log n+m\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
struct node
{
	int u,v,w;
	bool use;
	bool operator<(const node&it)const
	{
		return w<it.w;
	}
}edge[NN];
int fa[NN],d[NN],up[24][NN],maxw[24][NN];
vector<pair<int,int> >g[NN];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void dfs(int u,int f,int w)
{
	d[u]=d[f]+1;
	up[0][u]=f;
	maxw[0][u]=w;
	for(int i=1;i<=20;i++)
	{
		up[i][u]=up[i-1][up[i-1][u]];
		maxw[i][u]=max(maxw[i-1][u],maxw[i-1][up[i-1][u]]);
	}
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i].first;
		if(v==f)
			continue;
		dfs(v,u,g[u][i].second);
	}
}
int maxedge(int x,int y)
{
	if(d[x]<d[y])
		swap(x,y);
	int res=0;
	for(int i=20;~i;i--)
		if(d[up[i][x]]>=d[y])
		{
			res=max(res,maxw[i][x]);
			x=up[i][x];
		}
	if(x==y)
		return res;
	for(int i=20;~i;i--)
		if(up[i][x]!=up[i][y])
		{
			res=max(res,max(maxw[i][x],maxw[i][y]));
			x=up[i][x];
			y=up[i][y];
		}
	return max(res,max(maxw[0][x],maxw[0][y]));
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
	sort(edge+1,edge+1+m);
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		int fu=find(edge[i].u),fv=find(edge[i].v);
		if(fu!=fv)
		{
			cnt++;
			fa[fv]=fu;
			edge[i].use=true;
			g[edge[i].u].push_back(make_pair(edge[i].v,edge[i].w));
			g[edge[i].v].push_back(make_pair(edge[i].u,edge[i].w));
			if(cnt==n-1)
				break;
		}
	}
	dfs(1,0,0);
	int ans=0;
	for(int i=1;i<=m;i++)
		if(!edge[i].use&&edge[i].w==maxedge(edge[i].u,edge[i].v))
			ans++;
	printf("%d",ans);
	return 0;
}
```
## 法二

刚刚法一给出了一个思路：找一条能在树上组成环且这个环的最大值不止一个的边，我们现在直接在这个思路上做工作。之前我们发现，两个边只有在权相等的情况下才有可能对答案有贡献，所以我们可以把所有边权相等的边放在一起处理。可以先假设所有的边加上之后都对答案有贡献，然后除去没有贡献的边。在合并时，如果之前（还没有加入某个权的边之前）两个连通块就已经合并了，就一定不会对答案有贡献，因为加上这条边之后组成的环其他边都更小。然后考虑相同边权之间的冲突，如果两个连通块需要合并则加入这条边之前没有相同的边权加入，一定没有贡献，但是合并之后所有连通这两个连通块的相同边权的边都会对答案有贡献。于是，我们可以边做$Kruskal$边算答案。

平均时间复杂度$\Theta(m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
struct node
{
	int u,v,w;
	bool use;
	bool operator<(const node&it)const
	{
		return w<it.w;
	}
}edge[NN];
int fa[NN],maxx[NN];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
	sort(edge+1,edge+1+m);
	int ans=0,i=1;
	while(i<=m)
	{
		int j=i;
		while(edge[i].w==edge[j].w)
			j++;
		for(int k=i;k<j;k++)
			if(find(edge[k].u)!=find(edge[k].v))
				ans++;
		for(int k=i;k<j;k++)
		{
			int fu=find(edge[k].u),fv=find(edge[k].v);
			if(fu!=fv)
			{
				ans--;
				fa[fv]=fu;
			}
		}
		i=j;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Brilliant11001 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/CF1108F)

### 题目大意：

给定一个有 $n$ 个点，$m$ 条边的无向连通图，每次操作是将某条边的权值加一，求最少操作次数使得该无向连通图的最小生成树唯一。

**修改操作不能改变 MST 的权值和。**

### 思路：

**修改操作不能改变 MST 的权值和。** 这句话很关键，它告诉我们只能在最开始的最小生成树上考虑，否则情况就很冗杂了。

所以我们肯定得先求出原图的最小生成树。

不难想到当最小生成树不唯一时，会有其他非树边去替换最小生成树上的边，那么什么时候可以替换呢？

假设我们已经求出了原图的一颗最小生成树，并且扫描到一条非树边 $ e = (a, b, w)$，那么它必定和最小生成树上 $a,b$ 之间的路径构成一个环，在这个环上，断掉任意一条边，它一定还是一棵生成树。

设这条环上权值最大的树边为 $e'$，如果在这条环上的**树边的最大权值等于了这条非树边**，即 $e'_w = e_w$，那么断掉 $e$ 或断掉 $e'$ 都是可行方案了，即这时候 $e$ 可以替换 $e'$，这就会使最小生成树不唯一。

为了防止这种情况发生，我们只需要将 $e_w + 1$ 即可，**就算 $e'$ 可能会有很多条**，但因为 $e_w$ 已经大于环上所有的边权了，所以无法替换。

求树上两点之间的最大边权可以用倍增 LCA 解决。

综上所述，我们先用 $\texttt{kruskal}$ 算法求出最小生成树，顺便将最小生成树的边存下来，再 bfs 预处理一下最小生成树的 LCA，然后依次扫描每条非树边，若满足上述性质，则答案加一。

时间复杂度为 $O(n\log n)$。（假设 $n,m$ 同级）

$\texttt{Talk is cheap, show you the code.}$


```cpp
#include <queue>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;
int n, m;
int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;
struct node{
    int a, b, w;
    bool type;
    bool operator< (const node &o) const {
        return w < o.w;
    }
}edges[N];
int p[N];
int dep[N], f[N][22], T;
int maxd[N][22]; //maxd[i][j] 表示节点 i 到它的 2^j 辈祖先这条路径上的最大边权

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    dep[s] = 1;
    while(!q.empty()) {
        int t = q.front();
        q.pop();
        for(int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j]) continue;
            dep[j] = dep[t] + 1;
            f[j][0] = t;
            maxd[j][0] = w[i];
            for(int k = 1; k <= T; k++) {
                f[j][k] = f[f[j][k - 1]][k - 1];
                maxd[j][k] = max(maxd[j][k - 1], maxd[f[j][k - 1]][k - 1]);
            }
            q.push(j);
        }
    }
}

int lca(int x, int y) {
    int res = -0x3f3f3f3f;
    if(dep[x] > dep[y]) swap(x, y);
    for(int i = T; i >= 0; i--) 
        if(dep[f[y][i]] >= dep[x]) {
            res = max(res, maxd[y][i]);
            y = f[y][i];
        }
    if(x == y) return res;
    for(int i = T; i >= 0; i--)
        if(f[x][i] != f[y][i]) {
            res = max(res, maxd[x][i]);
            res = max(res, maxd[y][i]);
            x = f[x][i], y = f[y][i];
        }
    res = max(res, maxd[x][0]);
    res = max(res, maxd[y][0]);
    return res;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    int a, b, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }
    sort(edges + 1, edges + m + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) p[i] = i;
    int ori = 0; //随便找一个起点
    for(int i = 1; i <= m; i++) {
        a = edges[i].a, b = edges[i].b, w = edges[i].w;
        int x = find(a), y = find(b);
        if(x != y) {
            p[x] = y;
            add(a, b, w), add(b, a, w);
            edges[i].type = true; //树边标记一下
            ++sum;
            ori = a;
        }
        if(sum == n - 1) break;
    }
    T = (int)log2(n);
    bfs(ori);
    int res = 0;
    for(int i = 1; i <= m; i++)
        if(!edges[i].type) { //如果是非树边
            int tmp = lca(edges[i].a, edges[i].b);
            if(edges[i].w == tmp) ++res; //满足上述性质则累加答案
        }
    printf("%d", res);
    return 0;
}
```

---

## 作者：樱洛CHANGE (赞：4)

考虑什么情况会出现最小生成树不唯一的情况，显然至少有对于一个树边，存在至少一条非树边与其权值相同。

所以我们只需在 $\text{Kruskal}$ 的过程中寻找边权相同的**合法边（不成环）**，同时将剩下的边权相同的边边权加一，并累计答案即可。

需要注意的是，我们累计答案的边一定是与当前边集不成环的。

原因是，成环时一定存在**一条边被选中在边集中**，我们只需要将**其他边**的边权改变就可以达到目的。

或者我们反过来想，为什么一定要不成环时才进行上述操作。假设我们当前选择的边是 $x$，我们将其加入边集，下一次再选择的边是 $y$，且 $ y$ 与 $ x$ 边权相等，则由于**两条边不会构成环**，**故 $ y$ 要被添加到同一棵最小生成树中**，所以不构成多个最小生成树。

具体地，我们先把所有的边权相同的边进行统计，统计结束后再判断是否成环，若成环，则从合法边中减去不合法的数量（即答案减一），即可。

代码：

```cpp
#include<bits/stdc++.h>
#define awa 2147483647
#define zhale exit(0)
#define re register
#define rint re int
using namespace std;
/*Shioiri Kukuri*/

typedef long long ll;
typedef unsigned long long ull;
typedef double qwq;
typedef pair<int,int> P;
typedef pair<ll,ll> llP;
#define rll re ll
#define rqwq re qwq

/*Otho Ai*/

template<class T>
void Swap(T &x,T &y)
{
    T z=x;
    x=y;
    y=z;
}

//#define PairOP
#ifdef PairOP
template<class T1,class T2>
inline const pair<T1,T2> operator + (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
    return pair<T1,T2>(p1.first+p2.first,p1.second+p2.second);
}

template<class T1,class T2>
inline const pair<T1,T2> operator - (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
    return pair<T1,T2>(p1.first-p2.first,p1.second-p2.second);
}
#endif

//#define FastIO
#ifdef FastIO
    char buf[1<<21],*p1,*p2;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif

template<class T>
T Read()
{
    T x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
//int (*read)()=Read<int>;
ll (*readll)()=Read<ll>;
#define read Read<int>

const int N=2e5+5;

int n,m;
class Edge{
    public:
        int x,y,z;
        Edge(){}
        inline friend bool operator < (const Edge &a,const Edge &b){
            return a.z<b.z;
        }
        inline void In(){
            x=read(),y=read(),z=read();
        }
}e[N];

namespace Dsu{
    int fa[N];
    inline int Find(rint x){
        return fa[x]==0?fa[x]=x:fa[x]==x?x:fa[x]=Find(fa[x]);
    }
    inline void Merge(rint x,rint y){
        fa[Find(x)]=Find(y);
    }
}
using Dsu::Find;
using Dsu::Merge;

inline int True()
{
//#define Freopen
#ifdef Freopen
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif

//#define Clock
#ifdef Clock
    rint STR=clock();
#endif

    n=read(),m=read();
    for(rint i=1;i<=m;++i)
    e[i].In();
    sort(e+1,e+1+m);
    rint i=1,ans=0;
    while(i<=m)
    {
        rint ok=0,j=i;
        while(e[i].z==e[j].z) ++j;
        for(rint k=i;k<j;++k)
        {
            rint x=Find(e[k].x),y=Find(e[k].y);
            if(x^y) ++ok;
        }
        for(rint k=i;k<j;++k)
        {
            rint x=Find(e[k].x),y=Find(e[k].y);
            if(x^y) Merge(x,y),--ok;
        }
        i=j,ans+=ok;
    }
    printf("%d\n",ans);

#ifdef Clock
    rint END=clock();
    printf("Time:%dms\n",int((END-STR)/(qwq)CLOCKS_PER_SEC*1000));
    printf("Time:%ds\n",int((END-STR)/(qwq)CLOCKS_PER_SEC));
#endif
    return (0-0);//q(0-0)p q(>-<)p
}

int Love=True();

signed main(){;}
```

---

## 作者：_louhc (赞：4)

先求出最小生成树，对于那些没被选中的边$(u,v)$，我们设最小生成树中$u$到$v$的路径为$S$,由于要保证最小生成树唯一确定，我们要使$(u,v)$不能替换$S$路径中的任何一条边。因此，求出最小生成树中$(u,v)$路径中边权最大的边$e$。只要让这条边的边权$>v_e$即可。可行性与最优性不难证明，请自行思考。

至于怎么求，我们用倍增LCA实现。总的时间复杂度为$O(nlgn)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define LL long long

struct edge{
	int x, y, v; bool c;
	inline void input(){ scanf( "%d%d%d", &x, &y, &v ); c = 0; }
	bool operator < ( const edge &t )const{ return v < t.v; }
}a[MAXN];

int N, M;
int fa[MAXN];
int hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot;
int ft[MAXN][20], mx[MAXN][20], dep[MAXN];

void Add( int x, int y, int z ){
	nxt[++tot] = hd[x]; hd[x] = tot; to[tot] = y; val[tot] = z;
	nxt[++tot] = hd[y]; hd[y] = tot; to[tot] = x; val[tot] = z;
}

int find( int x ){ return fa[x] == x ? x : ( fa[x] = find(fa[x]) ); }
//LCA和并查集都不会的去问度娘
void DFS( int x ){
	dep[x] = dep[ft[x][0]] + 1;
	for ( int i = 1; i <= 17; ++i ) ft[x][i] = ft[ft[x][i - 1]][i - 1], mx[x][i] = max( mx[x][i - 1], mx[ft[x][i - 1]][i - 1] );
	for ( int i = hd[x]; i; i = nxt[i] ) if ( to[i] != ft[x][0] ) ft[to[i]][0] = x, mx[to[i]][0] = val[i], DFS(to[i]);
}

int LCA( int x, int y ){
	int ans(INT_MIN);
	if ( dep[x] < dep[y] ) swap( x, y );
	for ( int i = 17; i >= 0; --i ) if ( dep[ft[x][i]] > dep[y] ) ans = max( ans, mx[x][i] ), x = ft[x][i];
	if ( dep[x] > dep[y] ) ans = max( ans, mx[x][0] ), x = ft[x][0];
	for ( int i = 17; i >= 0; --i ) if ( ft[x][i] != ft[y][i] ) ans = max( ans, max( mx[x][i], mx[y][i] ) ), x = ft[x][i], y = ft[y][i];
	if ( x != y ) ans = max( ans, max( mx[x][0], mx[y][0] ) ), x = ft[x][0], y = ft[y][0];
	return ans;
}

int main(){
	scanf( "%d%d", &N, &M );
	for ( int i = 1; i <= M; ++i ) a[i].input(), fa[i] = i;//读入并初始化求最小生成树用的并查集
	sort( a + 1, a + M + 1 );//排序
	int c(0);
	for ( int i = 1; i <= M; ++i ){
		int x(find(a[i].x)), y(find(a[i].y));
		if ( x != y ){
			fa[x] = y; c++; a[i].c = 1; Add( a[i].x, a[i].y, a[i].v );//最小生成树部分。a[i].c表示是否为最小生成树上的边
			if ( c >= N - 1 ) break;//已构成生成树，退出
		}
	}
	ft[1][0] = 1; mx[1][0] = INT_MIN; DFS(1);//深搜预处理ft父亲与最大边权mx
	LL ans(0);//注意开long long
	for ( int i = 1; i <= M; ++i ){
		if ( !a[i].c ){//不是最小生成树上的边，进行处理
			int t(LCA( a[i].x, a[i].y ));
			if ( a[i].v <= t ) ans += t + 1 - a[i].v;//可以替换某一条边，增大它
		}
	}
	printf( "%lld\n", ans );
	return 0;
}

```



---

## 作者：Silvestorm (赞：1)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1108F)

给定一个有 $n$ 个点，$m$ 条边的无向连通图，每条边有边权。 定义一次操作为：选择一条图中的边，并将其权值 +1。

试求最小的操作次数，使得操作后的图的最小生成树是唯一的。

$1\le n\le 2\times 10^5$，$n-1 \le m\le 2\times 10^5$。

### 题目类型

MST。

### 解题思路

首先，形成最小生成树的边不能改，这是确定的。

其次，每条边最多修改1次，即修改后这条边就被淘汰了。一个简单的证明：一条边会被修改意味着它与另一条边冲突，即两条边同时存在时会产生环，所以淘汰的这条边后续也不会再加进这个图里，哪怕边权再小也不行，因为会产生环。

那么这道题就解决了。

先把所以边按照边权升序排序，并且变迁相同的边为同一层次。后续遍历时，一层一层的去遍历处理。

遍历到某一层时，先统计这一层的边有那些是可以添加到图中，然后对这些边进行处理，把能添加的边先添加，不能添加的边就忽略。

最后，得到的答案里会包括组成最小生成树的边，减去即可。

代码难度不高，排序离散化加并查集即可，时间复杂度为 $O(m\log{m}+n\log{n})$。

### code


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t = 1;
int n, m, k, x, tem, ans, num[1000200], fa[200100];
struct lint
{
	ll a, b, w;
};
bool cmp(lint q, lint e) { return q.w < e.w; }
vector<lint> v, v1[200100];
ll find(ll x)
{
	if (fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}
void solve()
{

	cin >> n >> m;
	for (int i = 0; i < n + 20; i++)
		fa[i] = i;
	ll a, b, c;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b >> c;
		v.push_back({a, b, c});
	}

	k = 1;
	sort(v.begin(), v.end(), cmp); // 排序，离散化
	if (m > 0)
		v1[k].push_back({v[0].a, v[0].b, v[0].w});
	for (int i = 1; i < m; i++)
	{
		if (v[i].w != v[i - 1].w)
			k++;
		v1[k].push_back({v[i].a, v[i].b, v[i].w});
	}
	ans = 0;
	for (int i = 0; i <= k; i++)
	{
		if (x >= n - 1)
			break;
		for (int j = 0; j < v1[i].size(); j++)				  // 先处理同一层次边权的边
			if (fa[find(v1[i][j].a)] != fa[find(v1[i][j].b)]) // 如果这条边能加进图里面，才会统计进答案里
				ans++;
		for (int j = 0; j < v1[i].size(); j++)
			if (fa[find(v1[i][j].a)] != fa[find(v1[i][j].b)]) // 添加进图里
				fa[find(v1[i][j].a)] = find(v1[i][j].b), x++;
	}
	cout << ans - n + 1 << "\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
既然题目要求操作完之后，最小生成树要是唯一的，那么我们直接先找出这张图的最小生成树，然后遍历每一条非树边是否要加一就行了。~~怎么这么像次小生成树。~~
## 2. 题目做法
我们先用 Kruskal 算法即可在 $O(n\log n)$ 的时间复杂度求出最小生成树，一边求一边将树边进行标记，并将所有树边连接，形成一张图。  
之后我们遍历每一条非树边时，我们要求出以非树边的两点为起点，在图上的最近公共祖先的路径上最长的边，若最长边等于非树边的长度，那么非树边需要加一，我们将答案加一。  
如何求最近公共祖先路径上的最长边呢？我用的是倍增版 lca 求的，具体见代码。  
至此我们便可完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=400010;//记得开双倍 
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int head[N],ne[M],e[M],w[M],idx;
inline void add(int x,int y,int z)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y;
	w[idx]=z; 
}
struct B{
	int x,y,z;
	bool f;
}a[N];
bool 
int n,m;
int death[N],fa[N][20],mx[N][20];
queue<int>q;
int t;
void bfs()//用BFS预处理lca数组 
{
	q.push(1);
	death[1]=1;
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		for(int i=head[t];i;i=ne[i])
		{
			int c=e[i];
			if(!death[c])
			{
				q.push(c);
				death[c]=death[t]+1;
				fa[c][0]=t,mx[c][0]=w[i];
				for(int i=1;i<=17;i++)
				{
					fa[c][i]=fa[fa[c][i-1]][i-1];
					mx[c][i]=max(mx[c][i-1],mx[fa[c][i-1]][i-1]);
				}
			}
		}
	}
}
int lca(int x,int y)//lca求最大值 
{
	int maxx=0;
	if(death[x]<death[y])
		swap(x,y);
	for(int i=17;i>=0;i--)
	{
		int c=fa[x][i];
		if(death[c]>=death[y])
		{
			maxx=max(maxx,mx[x][i]);
			x=c;
		}
	}
	if(x==y)
		return maxx;
	for(int i=17;i>=0;i--)
	{
		int c1=fa[x][i],c2=fa[y][i];
		if(c1!=c2)
		{
			maxx=max(maxx,mx[x][i]);
			maxx=max(maxx,mx[y][i]);
			x=c1,y=c2;
		}
	}
	maxx=max(maxx,mx[x][0]);
	maxx=max(maxx,mx[y][0]);
	return maxx;
}
inline bool cmp(B a1,B a2)
{
	return a1.z<a2.z;
}
int pr[N];
inline int find(int x)
{
	if(pr[x]==x)
		return x;
	return pr[x]=find(pr[x]);
}
int x,y,cnt;
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
		a[i]={read(),read(),read()};
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++)
		pr[i]=i;
	for(int i=1;i<=m;i++)
	{
		x=find(a[i].x),y=find(a[i].y);
		if(x!=y)
		{
			pr[x]=y;
			add(a[i].x,a[i].y,a[i].z);
			add(a[i].y,a[i].x,a[i].z);
			a[i].f=1;
			cnt++;
		}
		if(cnt==n-1)
			break;
	}
	bfs();
	cnt=0;
	for(int i=2;i<=m;i++)
	{
		if(!a[i].f)
		{
			t=lca(a[i].x,a[i].y);
			if(t==a[i].z)
				cnt++;
		}
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：KidA (赞：0)

对于 MST 相关题目，先画出 MST，从而发现性质。

![](https://cdn.luogu.com.cn/upload/image_hosting/8wavt6gr.png)

观察样例，蓝边组成的联通块即为原图的 MST。

显然，边权为 $3$ 的红、蓝两边可以互相替代，使得 MST 不唯一。

于是我们发现：只有**边权相等**且**合法**的一组边才有可能对答案有贡献。

其中合法的定义是，这组边中的任意一边都不会与前面已经选的边构成环。

进一步思考，是不是其中的所有边都对答案有贡献？

我们考虑将每组边权相等且合法的边继续分为**必要边**与**非必要边**。

其中，必要边是指满足两端点在不同联通块的边，非必要边则不满足。

（注意，非必要边是**合法的**，它不满足两端点在不同联通块是在**连了必要边的情况下**。换言之，必要边与非必要边实际上是等价的，每条非必要边都可以替代一条必要边。）

显然，必要边是必须要连的，不然构成不了 MST。

于是我们发现只有非必要边对答案有贡献，

将它们的权值都加一即可令 MST 唯一，

于是它们对答案的贡献即为非必要边的数量。

实现时边跑 kruskal 边统计贡献即可。时间复杂度 $O(n \log n)$。

[record](https://codeforces.com/contest/1108/submission/276346294)。

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1108F)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/01/10/CF1108F%20MST%20Unification/)

## 前言

一种 MST 被出烂的套路。

## 分析

考虑先用 Kruscal 随便建一棵 MST 出来，然后我们考虑一条非树边 $(u, v, w)$ 在什么时候可能会在 MST 中。

显然地，若连 $(u, v, w)$，那么原来的 MST 上会多一个环，所以要在环上换一条边，由于我们建出来的已经是 MST，所以被换的只可能是 $w$ 最大的那条，所以如果当前边的 $w$ 和 MST 上 $u \rightarrow v$ 的最大边权相等答案就加一，用树剖维护路径边权最大值即可。

```c++
#include <bits/stdc++.h>
 
using namespace std;
const int N = 2e5 + 10;
int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;
int a[N], b[N], fa[N], dep[N], sz[N], son[N], top[N], dfn[N], tt;
struct node {
	int x, y, z;
	bool operator<(const node &e) const {
		return z < e.z;
	}
} edges[N];
struct tree {
	int l, r, max;
} t[N << 2];
int n, m;
int vis[N], p[N];
 
inline int read() {
	int x = 0, y = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * y;
}
 
inline void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
 
inline int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}
 
inline void dfs1(int u, int p) {
	fa[u] = p, dep[u] = dep[p] + 1, sz[u] = 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == p) continue;
		a[v] = w[i], dfs1(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}
 
inline void dfs2(int u, int t) {
	top[u] = t, dfn[u] = ++tt, b[tt] = a[u];
	if (!son[u]) return;
	dfs2(son[u], t);
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
 
inline void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].max = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].max = max(t[p << 1].max, t[p << 1 | 1].max); 
}
 
inline int query(int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) return t[p].max;
	int mid = (t[p].l + t[p].r) >> 1, res = 0;
	if (l <= mid) res = max(res, query(p << 1, l, r));
	if (r > mid) res = max(res, query(p << 1 | 1, l, r));
	return res;
}
 
inline int query_path(int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = max(res, query(1, dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	return res = max(res, query(1, dfn[u] + 1, dfn[v]));
}
 
int main() {
	memset(h, -1, sizeof h);
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), z = read();
		edges[i] = {x, y, z};
	}
	sort(edges + 1, edges + m + 1);
	for (int i = 1; i <= n; i++) p[i] = i;
	int k = 0;
	for (int i = 1; i <= m; i++) {
		int px = find(edges[i].x), py = find(edges[i].y);
		if (px == py) continue;
		p[px] = py, vis[i] = true;
		add(edges[i].x, edges[i].y, edges[i].z), add(edges[i].y, edges[i].x, edges[i].z);
		if (++k == n - 1) break;
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	int res = 0;
	for (int i = 1; i <= m; i++) {
		if (vis[i]) continue;
		res += edges[i].z == query_path(edges[i].x, edges[i].y);
	}
	printf("%d\n", res);
	return 0;
}
```



---

## 作者：_stellar (赞：0)

对xht37的[题解](https://xht37.blog.luogu.org/cf1108f-mst-unification)的补充。

首先分享一篇写的不错的[题解](https://blog.csdn.net/Floraqiu/article/details/86630053)


在MST构造过程中，对于一系列待选的边，**如果他们的权值都是相同的，那么构造的MST是不唯一的**。

所以要使其**唯一**，在处理时就要对相同权值的一组边做出如下**决策**：**选定一条边且不会成环，其他所有相同权值的边+1**

于是就有了如下思路。

在朴素的Kruskal构造过程中，我们要干以下的事：

1.寻找权值相同的边，累计数量。

2.判断准备加入的边是否成环。如果是，答案-1

3.对相同权值的边集进行一次决策。

我的代码：

```
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define rep0(i,l,k) for(int i=(l);i<=(k);i++)
#define rep1(i,l,k) for(int i=(l);i<(k);i++)
#define hack! I AK IOI
template <typename A, typename B> inline bool Min(A &a,B b){if(a>b) {a=b; return true;} return false;}
template <typename A, typename B> inline bool Max(A &a,B b){if(a<b) {a=b; return true;} return false;}
struct Node{int u,v,w;}E[N];
bool comp(Node a,Node b){return a.w<b.w;}
int n,m,fa[N];
int fd(int x){return x==fa[x]?x:fa[x]=fd(fa[x]);}
void mg(int x,int y){x=fd(x),y=fd(y);if(x!=y) fa[x]=y;}
void init(){rep0(i,1,n) fa[i]=i;}
int ip(){
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        rep1(i,0,m) E[i].u=ip(),E[i].v=ip(),E[i].w=ip();init();
        sort(E,E+m,comp);int ans=0;
        for(int i=0;i<m;){
            int sum=0,j=i;
            while(E[i].w==E[j].w) j++;
            rep1(k,i,j) {int x=fd(E[k].u),y=fd(E[k].v);if(x!=y) sum++;}
            rep1(k,i,j) {int x=fd(E[k].u),y=fd(E[k].v);if(x!=y) mg(x,y),sum--;}
            i=j;ans+=sum;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：Memory_of_winter (赞：0)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10335626.html)

**题目大意：**给一张$n(n\leqslant2\times10^5)$个点$m(m\leqslant2\times10^5)$条边的无向带权图，定义一次操作为把一条边边权加一，求要使最小生成树唯一的最少操作数。

**题解：**先求一个最小生成树，对于任意一条不在最小生成树上的边，只有当它连上后形成的环上有和它边权相同的边时，最小生成树才是不唯一的，这是就要把这条边边权加一，并且，相同的那一条边一定是这个环上边权最大的边。所以可以用树上倍增求这条边，然后比较一下就行了。



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#define maxn 200010

int head[maxn], cnt;
struct Edge {
	int to, nxt, w;
	inline bool operator < (const Edge &rhs) const {
		return w < rhs.w;
	}
} e[maxn << 1], E[maxn];
inline void addedge(int a, int b, int c) {
	e[++cnt] = (Edge) { b, head[a], c }; head[a] = cnt;
	e[++cnt] = (Edge) { a, head[b], c }; head[b] = cnt;
}

int n, m;
int f[maxn];
int find(int x) { return x == f[x] ? x : (f[x] = find(f[x])); }
bool used[maxn];

#define M 17
int fa[maxn][M + 1], Mx[maxn][M + 1], dep[maxn];
void dfs(int u) {
	for (int i = 1; i <= M; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		Mx[u][i] = std::max(Mx[u][i - 1], Mx[fa[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != *fa[u]) {
			*fa[v] = u;
			*Mx[v] = e[i].w;
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	}
}
#define chkmin(x, i) res = std::max(res, Mx[x][i]), x = fa[x][i]
inline int calc(int x, int y) {
	int res = 0;
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = dep[x] - dep[y]; i; i &= i - 1) chkmin(x, __builtin_ctz(i));
	if (x == y) return res;
	for (int i = M; ~i; --i) if (fa[x][i] != fa[y][i]) chkmin(x, i), chkmin(y, i);
	return std::max(res, std::max(*Mx[x], *Mx[y]));
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &E[i].to, &E[i].nxt, &E[i].w);
	std::sort(E, E + m);
	for (int i = 1; i <= n; ++i) f[i] = i;
	{
		int num = n - 1;
		for (int i = 0; i < m && num; ++i) {
			int u = E[i].to, v = E[i].nxt, x = find(u), y = find(v);
			if (x != y) {
				f[x] = y;
				--num;
				used[i] = true;
				addedge(u, v, E[i].w);
			}
		}
	}
	dfs(1);
	int ans = 0;
	for (int i = 0; i < m; ++i) if (!used[i]) ans += E[i].w == calc(E[i].to, E[i].nxt);
	printf("%d\n", ans);
	return 0;
}

```



---

## 作者：muller (赞：0)

题目要求最小生成树

首先用kruskal算法或带堆prim算法求出这个图的任意一棵最小生成树

枚举不在这颗最小生成树上的每一条边(u,v,w)

若加入这条边 ，则形成了一个环，

若环上的边权除这条边外的最大值=w，

那么说明可以用这条边替换环上权值=w的边，

我们需要将这条边的权值加一，否则着两条边可以互相替换

如何求解呢？倍增即可，lca同时记录u到fa[u][i]的边权最大值为mx[u][i]

时间复杂度 : O((N + M)logN)

放一下我丑陋的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005, M = N << 1;
struct edge {
	int u, v, w;
} e[M];
int fa[N][21], mx[N][21], depth[N], f[N], fir[N], nxt[M], to[M], len[M], ecnt;
long long ans = 0;
bool intr[N];
bool cmp(edge a, edge b) {return a.w < b.w;}
void ae(int u, int v, int w) {
	to[++ecnt] = v; len[ecnt] = w; nxt[ecnt] = fir[u]; fir[u] = ecnt;
	to[++ecnt] = u; len[ecnt] = w; nxt[ecnt] = fir[v]; fir[v] = ecnt;
}
int find(int u) {return f[u] = f[u] == u ? u : find(f[u]);}
void dfs(int u, int dep, int f) {
	int i, v;
	depth[u] = dep; fa[u][0] = f;
	for (i = 1; i <= 20; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		mx[u][i] = max(mx[u][i - 1], mx[fa[u][i - 1]][i - 1]);
	}
	for (i = fir[u]; i; i = nxt[i])
		if ((v = to[i]) != f) {
			mx[v][0] = len[i];
			dfs(v, dep + 1, u);
		}
}
int calc(int u, int v) {
	int i, res = 0;
	if (depth[u] < depth[v]) swap(u, v);
	for (i = 20; ~i; --i) if (depth[fa[u][i]] >= depth[v]) res = max(res, mx[u][i]), u = fa[u][i];
	if (u == v) return res;
	for (i = 20; ~i; --i)
		if (fa[u][i] != fa[v][i]) {
			res = max(res, max(mx[u][i], mx[v][i]));
			u = fa[u][i]; v = fa[v][i]; 
		}
	return max(res, max(mx[u][0], mx[v][0]));
}
int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1, cmp);
	for (i = 1; i <= n; ++i) f[i] = i;
	for (i = 1; i <= m; ++i) {
		int u = find(e[i].u), v = find(e[i].v);
		if (u != v) {
			ae(e[i].u, e[i].v, e[i].w);
			intr[i] = true; f[u] = v;
		}
	}
	dfs(1, 1, 0);
	for (i = 1; i <= m; ++i)
		if (!intr[i]) {
			int u = e[i].u, v = e[i].v, w = e[i].w, l = calc(u, v);
			if (l >= w) ans += l + 1 - w;
		}
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：Caro23333 (赞：0)

这个题比赛的时候脑子卡住了没做出来......我真是菜爆

然后现在让我来口胡一个题解吧

### 算法流程：

首先跑一遍kruskal，求出在最小生成树（MST）中出现的每种边权各出现了几次。在这里，我们记cnt[i]为MST上边权为i的边的数量。

容易证明，对于一个无向连通图，其任意不同的生成树中c[i]的值都是不变的。

然后再跑一遍kruskal，但这次需要注意并查集维护的顺序。我们并不是每遍历一条边就在并查集中将两个顶点连起来，而是找出所有边权相同（比如设为k吧）的边，再将它们一起加入并查集。

在将这些边加入并查集之前，要找到其中有多少条边的两个顶点不在已有的同一个联通块内，这样的边数量记为tcnt[k]。
那么这样，答案就要加上tcnt[k]-cnt[k]。

如果上面的文字不太容易理解的话，可以考虑如下的样例：

5 6

1 3 1

2 3 1

2 4 2

1 5 3

1 2 3

3 5 3

当k为3时，并查集中已经连的边是所有边权小于3的边，也就是(1,3),(2,3),(2,4)三条边。

我们只要在这个并查集中查找所有边权为3的边中有多少条边两个端点不在同一个联通块内，对于这个样例来说就是(1,5）和(3,5)两条边，所以tcnt[3]就等于2。

### 正确性证明：

不会。反正它过了，而且我认为它极大概率是对的。

### 一些细节：

需要把边权离散化，这样才能用O(1)的桶来储存cnt和tcnt，O(logn)的map有一定tle危险。

### 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int MAXN = 200005;
int n,m,p[MAXN],cnt = 0;
struct Edge
{
    int u,v,c;
    bool operator<(const Edge t) const
    {
        return c<t.c;
    }
}s[MAXN];
int fa[MAXN];
inline int getFather(int v)
{
    if(v==fa[v]) return v;
    return fa[v] = getFather(fa[v]);
}
int mp[MAXN];
inline int binarySearch(int x)
{
    int left = 1, right = cnt, mid,res = -1;
    while(left<=right)
    {
        mid = (left+right)>>1;
        if(p[mid]<x) left = mid+1;
        else
        {
            right = mid-1;
            res = mid;
        }
    }
    return res;
}

int main()
{
    //freopen("data.in","r",stdin);
    cin >> n >> m;
    for(int i = 1; i<=m; i++)
    {
        scanf("%d%d%d",&s[i].u,&s[i].v,&s[i].c);
        p[++cnt] = s[i].c;
    }
    sort(p+1,p+cnt+1);
    cnt = unique(p+1,p+cnt+1)-p;
    for(int i = 1; i<=m; i++)
        s[i].c = binarySearch(s[i].c);
    //cout << "test" << endl; 
    for(int i = 1; i<=n; i++)
        fa[i] = i;
    sort(s+1,s+m+1);
    int tmpcnt = 0;
    s[m+1].c = -1, s[m+1].u = s[m+1].v = 1;
    for(int i = 1; i<=m+1; i++)
    {
        if(s[i].c!=s[i-1].c)
        {
            if(i>1) mp[s[i-1].c] = tmpcnt;
            tmpcnt = 0;
        }
        if(i==m+1) break;
        int fu = getFather(s[i].u), fv = getFather(s[i].v);
        if(fu!=fv)
        {
            tmpcnt++;
            fa[fu] = fv;
        }
    }
    tmpcnt = 0;  
    //cout << "test1" << endl;
    for(int i = 1; i<=n; i++)
        fa[i] = i;
    int lpos = 1, rpos,ans = 0;
    for(int i = 1; i<=m; i++)
    {
    	int fu = getFather(s[i].u), fv = getFather(s[i].v);
        if(fu!=fv)
            tmpcnt++;
        if(s[i].c!=s[i+1].c)
        {
            rpos = i;
            for(int j = lpos; j<=rpos; j++)
            {
                int fx = getFather(s[j].u), fy = getFather(s[j].v);
                if(fx!=fy)
                    fa[fx] = fy;
            }
            ans += tmpcnt-mp[s[i].c];
            tmpcnt = 0;
            lpos = i+1;
        }
    }
    cout << ans << endl;
 	return 0;
}
```


---

