# 「yyOI R1」youyou 的军训

## 题目背景

在 youyou 的班上，身高可能是一个敏感的话题。

## 题目描述

youyou 的班上一共有 $n$ 位同学，$m$ 对朋友，第 $i$ 对朋友关系对于身高有一个敏感值 $k_i$，敏感值可能会改变。

我们定义两位同学如果互为**朋友**，那么必然存在某对关系，将两位同学**直接**相连。

我们定义两位同学如果互为**好友**，那么必然存在直接或间接的关系，将两位同学相连。

例如存在关系 $(1,2)$ 和 $(2,3)$，那么，$1$ 与 $2$ 是朋友，但 $1$ 与 $3$ 就是好友。

现在，马上就要军训了，同学们要去领军训的服装，如果一位同学领到了尺码为 $p$ 的服装，所有同学会与朋友关系敏感值小于 $p$ 的朋友断交。即对于所有的朋友关系，若其敏感值小于 $p$，那么该朋友关系就会断开。不过在下一位同学领到服装时，所有**之前**的断开的朋友关系会恢复。

由于军训领服装是一个复杂的过程，而 youyou 对此十分感兴趣，所以给出 $q$ 次操作，且一共有三种操作:

- 操作 $1$，形如 `1 x`，表示有一位同学领到尺码为 $x$ 的服装。

- 操作 $2$，形如 `2 x`，表示询问第 $x$ 位同学还有多少位好友（包括自己）。

- 操作 $3$，形如 `3 x y`，表示第 $x$ 对朋友的敏感值变为 $y$，特别地，**敏感值的相对大小不会变化$^*$**（详情见下方），同时原来已经断开的关系不会恢复。

**注意：好友跟朋友是两个概念，朋友一定是好友，但好友不一定是朋友。**

$^*$：相对大小不会变化，指对于当前所有的敏感值而言，修改后的敏感值与原来的敏感值**排名相同**。

例如，若原来所有对朋友之间敏感值是 $\{1,2,3,5,6\}$，$3$ 的排名为 $3$，因此 $3$ 只能修改为 $3,4$ 中的一个，这样才能保证排名不变，即相对大小位置不会变换。

## 说明/提示


## 样例解释 #1

如图所示，这是初始的关系图。

![](https://cdn.luogu.com.cn/upload/image_hosting/68hzm5mr.png)

第一次操作为：有一位同学领到尺码为 $26963$ 的服装，这样，图中所有的边都会断开。

下一次操作：第三对朋友即边 $(2,3)$ 的权变为 $40$。

下一次操作：询问同学 $4$ 的好友数量，因为没有任何存在的边，因此答案为 $1$。
 
## 数据范围
| 测试点编号 | $n$ | $q$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1,2$ | $\le 10$ | $\le 4 \times 10^5$ | 无 |
| $3$ | $\le 10^3$ | $\le 10^3$ | 无 |
| $4$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $3$ |
| $5,6$ | $\le 10^5$ | $\le 10^3$ | 无 |
| $7$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $1$ |
| $8,9,10$ | $\le 4 \times 10^5$ | $\le 4 \times 10^5$ | 无 |

用 $c_i$ 表示询问中同学领到服装尺码的大小，$e_i$ 表示修改后敏感值的大小。

对于 $100\%$ 的数据，$1 \le n,m,q,x_i,y_i \le 4  \times  10^5$，$1 \le k_i,c_i,e_i \le 1 \times 10^9$，$m\le \min\{\frac{n(n-1)}{2},4 \times 10^5\}$。

同时数据保证在任何时刻，所有对朋友关系之间的敏感值**互不相同**。

**请注意常数因子对时间和空间产生的影响。**

## 样例 #1

### 输入

```
4 3 3
1 2 156
1 4 42
2 3 0
1 26963
3 3 40
2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
7 6 7
1 2 292
1 3 274
1 4 221
1 5 156
3 4 42
3 6 40
1 30
3 4 50
2 6
3 3 250
3 1 298
1 280
2 1```

### 输出

```
6
2```

# 题解

## 作者：__DDDDDD__ (赞：6)

## 题面描述

[$Link$](https://www.luogu.com.cn/problem/P9638)

给定一个带权无向图，有如下三种操作：

- `1 x`，表示断开边权 $\leq x$ 的所有边，并恢复此前因该操作而断开的边；

- `2 x`，询问当前 $x$ 能到达的所有点的数量（包括自己）；

- `3 x y`，表示将第 $x$ 条边的边权修改为 $y$，保证修改后边权大小排名不变。

## 题目分析

记录下每次操作一的 $x$，原题转化为询问一个点 $u$ 只走边权不小于 $x$ 的边能到达的点 $v$ 的个数。又保证了操作三的修改不改变边权排名，故可以使用 Kruskal 重构树。

以样例二为例，如下的一张图：

![原图](https://cdn.luogu.com.cn/upload/image_hosting/5her3c2d.png)

其最大生成树：

![最大生成树](https://cdn.luogu.com.cn/upload/image_hosting/62m1hhqb.png)

建出其 Kruskal 重构树：（边上的数字为其点权）

![Kruskal重构树](https://cdn.luogu.com.cn/upload/image_hosting/ki20lkym.png)

要查询一个点只走边权不小于 $x$ 的边能到达的点的个数，只需要在 Kruskal 重构树上向上跳，找到最浅的点权不小于 $x$ 的点，返回它所包含 $1\leq u \leq n$ 的点 $u$ 个数即可。（代码中采用了倍增查找）

对于修改操作，由于其不改变边权排名，所以不用修改树的形态。直接记录下每条边的 $id$，修改其点权即可。

代码实现如下：

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
inline int read(){
	re int x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
const int maxn=1e6+10;	//点、边个数至少为2n，数组大小要大于4e5*2
int n,m,q;
struct edge{
	int from,to,cost,id;
	inline bool operator <(const edge &x){
		return cost>x.cost;		//按边权由大到小排序 
	}
}e[maxn];

int fa[maxn];	//并查集 
inline int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}
int w[maxn],tot;
int to_edge[maxn];
vector<int>G[maxn];
inline void buildKruskal(){		//建Kruskal重构树 
	sort(e+1,e+m+1);
	tot=n;
	for(int i=1;i<=m;i++){
		int u=get(e[i].from),v=get(e[i].to);
		if(u==v)continue;
		int f=++tot;
		fa[u]=fa[v]=f;
		G[f].push_back(u);
		G[f].push_back(v);
		w[f]=e[i].cost;
		to_edge[e[i].id]=f;		//记录下id方便执行操作3 
	}
}

int f[maxn][21],sz[maxn];
inline void dfs(int x){			//预处理倍增与子树大小 
	for(int i=1;i<=20;i++){
		f[x][i]=f[f[x][i-1]][i-1];
	}
	if(x<=n){		//虚点不计入子树大小 
		sz[x]=1;
		return;
	}
	for(auto y:G[x]){
		if(sz[y])continue;
		f[y][0]=x;
		dfs(y);
		sz[x]+=sz[y];
	}
}
int limit;		//记录操作一 
inline int findmax(int x){		//倍增查找最浅的点权>=limit的节点 
	for(int i=20;i>=0;i--){
		if(f[x][i]&&w[f[x][i]]>=limit)x=f[x][i];
	}
	return x;
}

signed main(){
	n=read();m=read();q=read();
	for(int i=1;i<=n*2;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		e[i].from=read();e[i].to=read();e[i].cost=read();
		e[i].id=i;
	}
	buildKruskal();
	for(int i=tot;i;i--){	//图有可能不连通 
		if(!sz[i])dfs(i);
	}
	while(q--){
		int opt=read();
		if(opt==1){
			limit=read();
		}else if(opt==2){
			int x=read();
			printf("%lld\n",sz[findmax(x)]);
		}else if(opt==3){
			int x=read(),y=read();
			w[to_edge[x]]=y;
		}
	}
	return 0;
}
```


---

## 作者：AllenKING_RED (赞：6)

## Description

给定一个图，每次询问问将边权小于 $q$ 的边断开并询问一个点所在连通块的大小，边权可变。

## Solution

我们首先考虑暴力怎么做：

可以暴力维护询问值和边权，每次询问时暴力遍历连通块。

时间复杂度 $O(nq)$，期望得分 $30$ 分。

- 考虑测试点 $4$：

由于边权不会修改，可以考虑将询问离线。

按照边权从大到小排序，将每次询问时操作 `1` 的值也从大到小排序，每次询问时把边权大于当前操作 `1` 值的边依次加入，这样可以保证不经过边权不合法的边，再用并查集维护连通块的大小即可。

时间复杂度 $O(m \log n)$，加上其他组部分分，期望得分 $40$ 分。

- 考虑优化：

由于最大生成树的性质，所以不在最大生成树中的边对答案没有影响。

看到特殊性质，**边权的相对位置不变**，我们可以按照最大生成树的顺序建立虚点，用点权表示边权，再将虚点和边的两端连边。

此时，由于最大生成树的性质，深度浅的点的点权一定小于等于深度深的点，而修改时，我们可以直接 $O(1)$ 修改每条边对应虚点的点权。

我们可以从当前点倍增跳到自己的祖宗节点（复杂度为 $O(\log n)$），直到点权小于上次操作 `1` 的值，这时，所有该点子树中的点都一定是可以达到的，而子树外的点，必然要经过点权不合法的点，也就是经过此时断开的边才能达到。

由于新数中所有叶子节点都代表着原图中的点，所以可以得出结论：此时该点子树中叶子节点个数就是答案的值。

时间复杂度 $O(q \log n)$，期望得分 $100$ 分。

~~其实出题人自己也不知道剩下的特殊性质怎么写。~~

---

## 作者：Madsome (赞：4)

给一篇不用倍增的题解。
## 题意
给定一个无向图，每次**在原图基础上**删去所有边权**小于 $q$** 的边，查询一个点所在联通块的大小。边权带修，但相对大小不变。
## 题解
可以发现，删完边以后最多只有 $n$ 种状态，考虑将其预处理。题目保证：所有对朋友关系之间的敏感值**互不相同**，所以可以看作每次从小到大将一条边删去，维护每个点的连通块大小。考虑其逆过程，非常巧啊，这不就是 Kruskal 算法生成**最大生成树**吗！而且题目保证：修改后的敏感值与原来的敏感值**排名相同**，所以最大生成树的**形态不会改变**。

定义 $siz_i$ 表示 $i$ 所在的连通块大小，$fa_i$ 表示 $i$ 所在的连生成树的根节点。为了方便维护连通块的大小，只需要维护 $siz_{fa_i}$ 的大小即可。每次合并时，只需修改根节点的 $siz$ 即可。

但这样还不够，空间复杂度不能接受，用可持久化数组就太过麻烦了。考虑直接将询问离线，在每次 $1$ 操作时，将当前状态要删的边数下有哪几个节点需要查询记录下来即可。对于每个 $3$ 操作，可以发现一个点的答案，**只与当前要删几条边有关**，所以直接在原数组修改即可。

时间复杂度 $\mathcal O(n \log n)$，瓶颈在排序以及二分。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Size=(1<<20)+1;
char buf[Size],*p1=buf,*p2=buf;
char buffer[Size];
int op1=-1;
const int op2=Size-1;
inline char readchar(){
	if(p1!=p2) {
		return *p1++;
	}
	return p1==(p2=(p1=buf)+fread(buf,1,Size-1,stdin))?EOF:*p1++;
}
inline void flush(){
	fwrite(buffer,1,op1+1,stdout),op1=-1;
}
inline void writechar(const char &x) {
	if(op1==op2) flush();
	buffer[++op1]=x;
}
#ifndef ONLINE_JUDGE
#define readchar getchar
#endif
#define putchar writechar
inline int read() {
	int s=1,c=readchar(),x=0;
	while(c<=32) {
		c=readchar();
	}
	if(c=='-') {
		s=-1,c=readchar();
	}
	for(; ('0'<=c && c<='9'); c=readchar()) {
		x=x*10+c-'0';
	}
	return x*s;
}
inline void print(long long x) {
	if(x<0) {
		writechar('-'),x=-x;
	}
	char s[25];
	int n=0;
	while(x||!n) {
		s[n++]='0'+x%10,x/=10;
	}
	while(n--) {
		writechar(s[n]);
	}
}
const int N=4e5+5;
int n,m,T,i,j,rk[N],ans[N],cnt,opt,x,y,l,r,mid,len,fa[N],siz[N];
struct ed{
	int x,y,k,id;
}a[N];
struct nd{
   int id,val;
};
vector<nd>g[N];
inline bool cmp(ed x,ed y){
	return x.k>y.k;
}
inline int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
signed main() {
    n=read();m=read();T=read();
    for(i=1;i<=m;i++){
		a[i].x=read();a[i].y=read();
		a[i].k=read();a[i].id=i;
	}
    sort(a+1,a+m+1,cmp);
	for(i=1;i<=m;i++)
	   rk[a[i].id]=i;
	int cur=m;
	for(i=1;i<=T;i++){
		opt=read();x=read();
		if(opt==1){
			l=1;r=m;
			int ans=0;
			while(l<=r){//二分出要保留几条边
				mid=l+r>>1;
				if(a[mid].k>=x){
					l=mid+1;
                    ans=mid;
				}
				else r=mid-1;
			}
			cur=ans;
		}
		else if(opt==2){
			nd tmp;
			tmp.id=++len;tmp.val=x;
            g[cur].push_back(tmp);
		}
        else a[rk[x]].k=read();
	}
    for(i=1;i<=n;i++)fa[i]=i,rk[i]=siz[i]=1;//注意，这里的rk数组用于并查集按秩合并，为了省空间用了相同的数组
	for(auto i:g[0])ans[i.id]=1;
    for(i=1;i<=m;i++){
		int fx=find(a[i].x),fy=find(a[i].y);
        if(fx!=fy){//按秩合并
		   	 if(rk[fx]<=rk[fy])fa[fy]=fx,siz[fx]+=siz[fy];
		    else fa[fy]=fx,siz[fy]+=siz[fx];
		    if(rk[fx]==rk[fy]&&fx!=fy)rk[fy]++;
        }
		for(auto j:g[i])
		   ans[j.id]=siz[find(j.val)];
	} 
	for(i=1;i<=len;i++)
	  print(ans[i]),putchar('\n');
	flush();
	return 0;
}
```

---

## 作者：SXqwq (赞：3)

### Description

共有 $q$ 次操作。

- `1 x` 断开边权 $< x$ 的边，并恢复先前操作断开的边。

- `2 x` 询问点 $x$ 所位于连通块大小。即点 $x$ 能到达多少个点（包括本身。）

- `3 x y` 将编号为 $x$ 的边权值修改为 $y$，保证修改后边权相对大小不变。

$n,q\le 4\times 10^5$。

### Analysis

前置知识：Kruskal 重构树，倍增。

注意到操作 $1$ 之间互不影响，故查询时，**一条边能走当且仅当边权 $\ge limit$**。（$limit$ 在操作 $1$ 时更新。）

我们将边按照权值从大到小排序，建立 Kruskal 重构树。找到点 $x$ 向上跳到最小的满足边权 $\ge x$ 的边，以其为父节点，下面叶子节点数量即为答案。（在 Kruskal 重构树中，叶子节点即为实点。）

因此，建出 Kruskal 重构树后，我们预处理出**每个虚点下面叶子节点的数量，记为 $size$**。这很简单，dfs 扫一遍即可。

对于操作 $1$，更新当前限制 $limit$。（$limit$ 表示点 $x$ 仅允许走边权 $\ge limit$ 的边。）

对于操作 $3$，题目保证**修改后边权的相对大小不变**。即 Kruskal 重构树形态不变。在读入边时，我们记录每条边的编号，在 Kruskal 重构树上单点修改即可。

对于操作 $2$，我们倍增查询。这就用到了先前处理的 $size$ 数组。向上跳到最小的符合条件的边，输出其 $size$ 值即可。

### Code

```cpp
namespace solution
{
    constexpr int N = 1000010;
    typedef pair<int,int> PAIR;
    int n,m,q,limi;
    int tot;
    struct Node
    {
        int u,v,w,id;
        bool operator <(const Node& a)const{
            return a.w < w;
        }
    };
    vector <Node> edge;
    vector <PAIR> Edge[N];
    int edge_num[N],fa[N][50],siz[N];
    int val[N];
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=n*2+1;i++) fa[i] = i;}
        int find(int x)
        {
            if(x == fa[x]) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        } 
        void merge(int x,int y)
        {
            int i = find(x),j = find(y);
            if(i == j) return;
            fa[i] = j;
        }
    }dsu;
    void kruskal()
    {
        sort(edge.begin(),edge.end());
        tot = n; 
        dsu.init();
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),w = t.w;
            if(u == v) continue;
            tot ++;
            dsu.merge(u,tot),dsu.merge(v,tot);
            Edge[tot].push_back(PAIR(u,w)),Edge[tot].push_back(PAIR(v,w));
            edge_num[t.id] = tot;
            val[tot] = w;
        }
    }
    void dfs(int u,int fat)
    {
        #define x first
        #define y second
        for(int i=1;i<=30;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        if(u <= n) 
        {
            siz[u] = 1;
            return;
        }
        for(auto t:Edge[u])
        {
            int v = t.x;
            if(siz[t.x] || t.x == fat) continue;
            fa[t.x][0] = u;
            dfs(t.x,u);
            siz[u] += siz[v];
        }
    }
    int find_max(int u)
    {
        for(int i=30;i>=0;i--)
            if(fa[u][i] && val[fa[u][i]] >= limi) u = fa[u][i];
        return u;
    }
    void solve()
    {
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            edge.push_back({u,v,w,i});
        }
        kruskal();
        cerr<<tot<<endl;
        for(int i=tot;i;i--) if(!siz[i]) dfs(i,0);
        while(q--)
        {
            int op;
            cin>>op;
            if(op == 1) 
                cin>>limi;
            else if(op == 2)
            {
                int x;
                cin>>x;
                cout<<siz[find_max(x)]<<endl;
            }
            else if(op == 3)
            {
                int x,y;
                cin>>x>>y;
                val[edge_num[x]] = y;
            }
        }
        return;
    }
}
```

---

## 作者：happybob (赞：3)

Kruskal 重构树板子。

考虑建边权从大到小排序后跑 Kruskal 的重构树，对于当前点 $u$ 和参数 $w$，只能走 $\geq w$ 边，即能去的点是 $u$ 祖先中最浅的点权 $\geq w$ 的点所在子树内每个叶子节点。

发现边权修改后，相对大小不变，直接在重构树点权修改即可。

倍增处理，复杂度 $O(q \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int N = 8e5 + 5;
int p[N];

struct Edge
{
	int u, v, w;

	Edge() = default;

	Edge(int u, int v, int w)
		: u(u), v(v), w(w)
	{
	}

	bool operator==(const Edge& other) const
	{
		return u == other.u && v == other.v && w == other.w;
	}
}e[N];

int n, m, q;
int u[N], v[N], w[N];
int res[N];
int nfa[N][21];
map<pair<int, int>, int> mp;

class Union_Find
{
public:
	int fa[N], idx;
	int val[N], res[N];
	vector<int> G[N];
	void Init()
	{
		mp.clear();
		for (int i = 0; i < N; i++) fa[i] = i, val[i] = 0, G[i].clear();
		for (int i = 1; i <= n; i++) res[i] = 1;
		idx = n;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	void merge(int u, int v, int w)
	{
		if (find(u) == find(v)) return;
		mp[make_pair(u, v)] = ++idx;
		u = find(u), v = find(v);
		val[idx] = w;
		G[idx].emplace_back(u), G[idx].emplace_back(v);
		nfa[u][0] = nfa[v][0] = idx;
		fa[u] = fa[v] = idx;
		res[idx] += res[u] + res[v];
	}
}uf;

int val[N];
vector<int> G[N];

void kruskal()
{
	uf.Init();
	sort(e + 1, e + m + 1, [&](const Edge& x, const Edge& y) {return x.w > y.w; });
	for (int i = 1; i <= m; i++) uf.merge(e[i].u, e[i].v, e[i].w);
	for (int i = 0; i < N; i++) val[i] = uf.val[i], G[i].swap(uf.G[i]);
}

int get(int u, int x)
{
	for (int i = 20; i >= 0; i--)
	{
		if (nfa[u][i] && val[nfa[u][i]] >= x) u = nfa[u][i];
	}
	return u;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++)
	{
		cin >> u[i] >> v[i] >> w[i];
		e[i] = Edge(u[i], v[i], w[i]);
	}
	kruskal();
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 0; j < N; j++) nfa[j][i] = nfa[nfa[j][i - 1]][i - 1];
	}
	for (int i = 0; i < N; i++) res[i] = uf.res[i];
	int now = 0;
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			cin >> now;
		}
		else if (op == 2)
		{
			int x;
			cin >> x;
			cout << res[get(x, now)] << "\n";
		}
		else
		{
			int x, y;
			cin >> x >> y;
			if (mp.count(make_pair(u[x], v[x])))
			{
				val[mp[make_pair(u[x], v[x])]] = y;
			}
		}
	}
	return 0;
}
```


---

## 作者：SegTree (赞：3)

### 题意

一个 $n$ 点 $m$ 边的无向图，边有边权，有一个值 $w$。三种操作：

+ `1 x` 表示 $w\gets x$。

+ `2 x` 询问保留所有边权 $\ge q$ 的边后 $x$ 所在连通块大小。

+ `3 x y` 修改第 $x$ 条边边权为 $y$。

保证修改前后所有边权的排名不变。

### 题解

不难想到建出一颗 Kruskal 重构树（就是最大生成树在 Kruskal 的时候将合并两个连通块形成的新连通块与这两个连通块连边建成一颗树）。为了方便，我们将这个新连通块的点权设为连接着两个连通块的这条边的边权。

查询在建出的树上倍增跳到最高的边权 $\ge x$ 的结点，那么这棵子树内的都能到达，则答案为这颗子树的叶子结点数。

你发现修改边权排名不变就保证了 Kruskal 重构树上对应的边编号不变，所以修改能直接 $\mathcal{O}(1)$ 修改对应的点权即可。

查询 $\mathcal{O}(\log n)$ 倍增就做完了。

[代码](https://www.luogu.com.cn/paste/4ijyx6ux)。

---

## 作者：Mugino_Shizuri (赞：2)

先放一个帖子：[link](https://www.luogu.com.cn/discuss/863721)。

这题有一个细节，后面再说。

首先我们发现这个题面十分抽象，所以先提取关键信息，发现没有 $3$ 操作的问题可以转化为：走边权不超过 $k$ 的边能走到多少点，其实也就是瓶颈路问题。

考虑 Kruskal 重构树，则每次能走到的点对应到重构树上刚好就是一个子树，因为 LCA 肯定是瓶颈，既然 LCA 都能走，子树内一定畅通无阻。

那这个方法对于有 $3$ 操作的该题是否有启发呢？答案是显然的。~~不然我为啥讲~~。

发现权值的相对关系始终不变，所以树的形态也一定不会变，所以每次修改边权就直接修改 LCA 的点权就行了，不过要提前判断这条边是否在 Kruskal 重构树上，否则只有 $90$ 分。

然后就牵扯到上面的帖子了，题面中说了修改边权不会是断掉的边是不会重连的，所以有些题解的代码有点问题。

具体实现 $3$ 操作的方式有很多，我在代码中选择使用 vector 进行懒删除，每次操作 $1$ 时集体下放修改。

还有就是这道题你不管操作 $3$ 也有 $90$ 分，数据很水。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer& operator << (const char* str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer(){}
	}cout;
}
#define fi first
#define endl '\n'
#define sec second
#define mk make_pair
#define cin Fastio :: cin
#define cout Fastio :: cout

const int B=20;
const int N=1e6+10;
typedef pair<int,int> pii;
struct edge{
	int x,y,z;
	edge(int x=0,int y=0,int z=0):x(x),y(y),z(z){;}
	bool operator <(const edge &t)const{return z>t.z;}
}a[N],b[N];
int siz[N],f[N][B+1],fa[N],ls[N],rs[N],tot,n,m,q,w[N],las,dep[N];
int root(int x){return x==fa[x]?x:fa[x]=root(fa[x]);}
vector < pii > Q;

void Kruskal(){
	sort(a+1,a+1+m);
	for(int i=1;i<=m;++i){
		int x=root(a[i].x);
		int y=root(a[i].y);
		if(x==y) continue;
		w[++tot]=a[i].z;
		fa[x]=fa[y]=tot;
		ls[tot]=x;rs[tot]=y;
	}
}

void dfs(int x,int y){
	f[x][0]=y;dep[x]=dep[y]+1;
	for(int i=1;i<=B;++i) f[x][i]=f[f[x][i-1]][i-1];
	if(x<=n) siz[x]=1;
	else {
		dfs(ls[x],x);dfs(rs[x],x);
		siz[x]=siz[ls[x]]+siz[rs[x]];
	}
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=B;~i;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=B;~i;--i) if(f[x][i]!=f[y][i]){x=f[x][i];y=f[y][i];}
	return f[x][0];
} 

inline int jump(int x){
	for(int i=B;~i;--i) if(f[x][i]&&w[f[x][i]]>=las) x=f[x][i];
	return siz[x];
}

int main(){
	cin>>n>>m>>q;tot=n;
	for(int i=1;i<=(n<<1);++i) fa[i]=i;
	for(int i=1;i<=m;++i) cin>>a[i].x>>a[i].y>>a[i].z;
	for(int i=1;i<=m;++i) b[i]=a[i];Kruskal();
	for(int i=tot;i;--i) if(!siz[i]) dfs(i,0);
	for(int i=1,opt,x,y;i<=q;++i){
		cin>>opt>>x;
		if(opt==1){for(auto i:Q) w[i.fi]=i.sec;Q.clear();las=x;}
		else if(opt==2) cout<<jump(x)<<endl;
		else {
			cin>>y;
			int lca=LCA(b[x].x,b[x].y);
			if(w[lca]!=b[x].z) continue;
			Q.emplace_back(lca,b[x].z=y);
		}
	}
	return 0;
}
//这条边有可能本来就没影响。输。 
```

---

## 作者：uid_310801 (赞：2)

由于敏感值相对大小不会变化，所以图的形态最多只有 $n$ 种。即按敏感值从小到大排序后断开一段前缀边。

先离线下来所有读入，每次 1 操作和 3 操作更新当前图的形态，对于询问操作直接在当前形态存储下来这次询问。最后利用并查集依次加边并处理询问即可。更新图的形态的时候可以使用二分法，总时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=4e5+10;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
ll n,m,q,cnt;
ll fa[N],sz[N],pos[N],ans[N];
vector<pii> v[N];
struct Edge{
	ll x,y,k,bh;
	bool operator<(const Edge &a1) const{
		if(k==a1.k)	return bh<a1.bh;
		return k<a1.k;
	}
}e[N];
ll get(ll x){
	if(x==fa[x])	return x;
	return fa[x]=get(fa[x]);
}
void merge(ll x,ll y){
	ll xx=get(x),yy=get(y);
	if(xx==yy)	return;
	if(sz[xx]>sz[yy])	swap(xx,yy);
	fa[xx]=yy,sz[yy]+=sz[xx];
}
signed main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++){
		e[i].x=read(),e[i].y=read(),e[i].k=read();
		e[i].bh=i;
	}
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++){
		fa[i]=i;sz[i]=1;
	}
	for(int i=1;i<=m;i++){
		pos[e[i].bh]=i;
	}
	ll nws=0,nwpos=0;
	while(q--){
		ll opt=read();
		if(opt==1){
			nws=read();
			nwpos=upper_bound(e+1,e+m+1,(Edge){0,0,nws,0})-e-1;
//			printf("%lld\n",nwpos);
		}	
		else if(opt==2){
			ll x=read();
			v[nwpos].push_back(mp(x,++cnt));
		}
		else{
			ll x=read(),nwf=read();
			e[pos[x]].k=nwf;
			nwpos=upper_bound(e+1,e+m+1,(Edge){0,0,nws,0})-e-1;
//			printf("%lld\n",nwpos);
		}
	}
	for(int i=m;i>=0;i--){
		for(int j=0;j<v[i].size();j++){
			ans[v[i][j].se]=sz[get(v[i][j].fi)];
		}
		if(i!=0)	merge(e[i].x,e[i].y);
	}
	for(int i=1;i<=cnt;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/P9638)

Kuskral 重构树板子。

因为相对边权不变，所以重构树的形态不变。

那其实就是期望连通块内任意两个点路径的最小值最大。重构树内点的点权的含义就是他叶子节点相互抵达的路径上权值最大值。这个我们容易用重构树维护出来，然后实际上我们只用不断地往上跳到 $>p$ 就停止即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int n,m,q,siz[N],F[N],fa[N][23],dep[N],lst;
vector<int> g[N];
struct node{
	int u,v,w,id;
}a[N],b[N];
struct edge{
	int id,val;
}c[N];
bool cmp(node a,node b){
	return a.w>b.w;
}
int Find(int x){
	return x==F[x]?x:F[x]=Find(F[x]);
}
void Kuskral_SG(){
	for(int i=1;i<=m;i++)	b[i].u=a[i].u,b[i].v=a[i].v,b[i].w=a[i].w,b[i].id=i;
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=2*n-1;i++)	F[i]=i;
	int cnt=n;
	for(int i=1;i<=m;i++){
		int u=Find(b[i].u),v=Find(b[i].v);
		if(u==v)	continue;
		cnt++; F[u]=cnt,F[v]=cnt,c[cnt].val=b[i].w,c[cnt].id=b[i].id,g[cnt].push_back(u),g[cnt].push_back(v);
	}
}
void dfs(int u,int fath){
	dep[u]=dep[fath]+1,fa[u][0]=fath;
	if(g[u].size()==0)	siz[u]++;	
	for(int i=1;(1<<i)<=dep[u];i++)	fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fath)	continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])	swap(x,y);
	int d=dep[x]-dep[y];
	for(int i=22;i>=0;i--)	if((1<<i)&d)	x=fa[x][i];
	if(x==y)	return x;
	for(int i=22;i>=0;i--)	if(fa[x][i]!=fa[y][i])	x=fa[x][i],y=fa[y][i];
	return fa[x][0];	
}
int Query(int x){
	for(int i=22;i>=0;i--)	if(fa[x][i]&&c[fa[x][i]].val>=lst)	x=fa[x][i];
	return siz[x];
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("ans.out","w",stdout);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++)	cin>>a[i].u>>a[i].v>>a[i].w;
	Kuskral_SG();
	for(int i=1;i<=2*n-1;i++)	if(Find(i)==i)	dfs(i,0);
	while(q--){
		int op,x,y;
		cin>>op;
		if(op==1)	cin>>x,lst=x;
		else if(op==2)	cin>>x,cout<<Query(x)<<endl;
		else{
			cin>>x>>y;
			if(c[LCA(b[x].u,b[x].v)].id==x)	c[LCA(b[x].u,b[x].v)].val=y;
		}
	}
}
```


---

## 作者：VitrelosTia (赞：0)

独立完成了，虽然有点板但还是写题解纪念一下！

翻译一下题意，给定一个带权图，每次会改变一条边权（边权都不一样且相对大小关系不变），或者询问在去掉边权 $<k$ 的边之后 $u$ 所在连通块的大小。

直接从 $u$ 入手感觉比较困难，思考 $u,v$ 联通的条件，是 $u,v$ 之间的路径中，存在一条路径没有被断掉，也就是说，所有路径中最大的边权最小值 $\ge k$。

这种问题肯定考虑建个 kruskal 重构树，又由于题目给出的修改有着非常好的性质，我们知道这个树的形态是不会变的。

然后求答案就考虑倍增，因为 kruskal 重构树点权递增，直接往上跳，对于 $>n$ 的节点记个 $\le n$ 的后代的个数就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cerr << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 1e6 + 5;
int n, m, Q; struct Edge { int u, v, w, o; } e[N];
int tot, fa[N], siz[N], val[N], pos[N]; vector <int> g[N];
void add(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { if (x == y) return; fa[x] = y; siz[y] += siz[x]; }
void kruskal() {
    for (int i = 1; i <= 2 * n; i++) {
        fa[i] = i;
        if (i <= n) siz[i] = 1;
    } tot = n;
    sort(e + 1, e + m + 1, [](Edge x, Edge y) { return x.w > y.w; });
    for (int i = 1; i <= m; i++) if (find(e[i].u) != find(e[i].v)) {
        int u = find(e[i].u), v = find(e[i].v), w = e[i].w; tot++;
        merge(u, tot); merge(v, tot); val[tot] = w; pos[e[i].o] = tot;
        add(u, tot); add(v, tot);
    }
}
int f[N][26];
void dfs(int u, int fa) { 
    f[u][0] = fa;
    for (int i = 1; i < 26; i++) f[u][i] = f[f[u][i - 1]][i - 1]; 
    for (int v : g[u]) if (v != fa) dfs(v, u);
}
int query(int u, int k) {
    for (int i = 25; i >= 0; i--) if (val[f[u][i]] >= k && f[u][i]) u = f[u][i];
    return siz[u];
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> Q;
    for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w, e[i].o = i;
    kruskal(); for (int i = 1; i <= tot; i++) if (fa[i] == i) dfs(i, 0);
    for (int i = 1, lst = 0, o, x, y; Q--; ) {
        cin >> o >> x;
        if (o == 1) lst = x;
        if (o == 2) cout << query(x, lst) << '\n';
        if (o == 3) cin >> y, val[pos[x]] = y;
    }
    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

板子。

很显然一操作查询相当于只走边权 $\ge x$ 的边能到达的联通点数。这里我们考虑最大生成树，这样就能保证两个点的路径中经过的**最大最小值**是多少，经典老题 [P1967](https://www.luogu.com.cn/problem/P1967) 的套路。

这里使用 Kruskal 重构树，然后操作二直接跳节点即可，操作三直接修改即可，因为它不会破坏相对排名所以可以直接把树上的权值给改了。

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct Point{
	int u,v,w,id;
}edge[N];
int w[N],f[N][21];
vector <int> e[N];
bool cmp(Point x,Point y){
	return x.w>y.w;
}
int ft[N];
int getf(int u){
	if(ft[u]==u)return u;
	return ft[u]=getf(ft[u]);
}
int n,m,q,tot,a[N],siz[N],op;
void add(int x,int y){
	e[x].push_back(y);
}
void dfs(int u){
	if(u<=n)siz[u]=1;
	for(int i = 0;i < e[u].size();i++){
		int v=e[u][i];
		f[v][0]=u;
		dfs(v);
		siz[u]+=siz[v];
	}
}
int tmp;
inline int query(int x){
	for(int i = 20;i >= 0;i--)
		if(f[x][i]&&a[f[x][i]]>=tmp)
			x=f[x][i];
	return x;
}
int x,y;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= m;i++)
		cin >> edge[i].u >> edge[i].v >> edge[i].w,edge[i].id=i;
	sort(edge+1,edge+1+m,cmp);
	for(int i = 1;i <= n*2;i++)ft[i]=i;
	tot=n;
	for(int i = 1;i <= m;i++){
		int u = edge[i].u,v =edge[i].v;
		u=getf(u),v=getf(v);
		if(u!=v){
			tot++;
			ft[u]=ft[v]=tot;
			a[tot]=edge[i].w;
			add(tot,u);
			add(tot,v);
			w[edge[i].id]=tot;
		}
	}
	for(int i = tot;i >= 1;i--)
		if(!siz[i])
			dfs(i);
	for(int j = 1;j <= 20;j++)
		for(int i = 1;i <= tot;i++)
			f[i][j]=f[f[i][j-1]][j-1];
	for(int i = 1;i <= q;i++){
		cin >> op;
		if(op==1){
			cin >> x;
			tmp=x;
		}
		else if(op==2){
			cin >> x;
			cout << siz[query(x)] << "\n";
		}
		else{
			cin >> x >> y;
			a[w[x]]=y;
		}
	}
	return 0;
}
```

---

