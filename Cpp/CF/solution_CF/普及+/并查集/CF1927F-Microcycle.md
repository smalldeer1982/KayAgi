# Microcycle

## 题目描述

Given an undirected weighted graph with $ n $ vertices and $ m $ edges. There is at most one edge between each pair of vertices in the graph, and the graph does not contain loops (edges from a vertex to itself). The graph is not necessarily connected.

A cycle in the graph is called simple if it doesn't pass through the same vertex twice and doesn't contain the same edge twice.

Find any simple cycle in this graph in which the weight of the lightest edge is minimal.

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
3 1 1
4 5 1
5 6 1
6 4 1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
6 15
1 2 4
5 2 8
6 1 7
6 3 10
6 5 1
3 2 8
4 3 4
5 3 6
2 6 6
5 4 5
4 1 3
6 4 5
4 2 1
3 1 7
1 5 5
4 6
2 3 2
1 3 10
1 4 1
3 4 7
2 4 5
1 2 2
4 5
2 1 10
3 1 3
4 2 6
1 4 7
2 3 3```

### 输出

```
1 3
1 2 3 
3 3
6 4 5 
1 5
4 2 1 6 3 
1 4
1 4 3 2 
3 3
2 3 1```

# 题解

## 作者：CYZZ (赞：7)

# [CF1927F](https://www.luogu.com.cn/problem/CF1927F)
非常快口胡出来，但是数组没清零暴调 3h，绷不住了。
## 思路
看到找环的题可以先考虑建 dfs 树，这样所有可能的环就必须经过**非树边**（不在树上的边）。

由于环的长度没有限制，可以对于每个非树边，取两个端点到 lca 构成的环，这样一定是最优的。这个环的权值可以用倍增 lca 求出。最后所有环取最优就行了。

记住，多测要清空，尤其是像 fa 数组这样的也要清空（别问我怎么知道的）。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define PII pair<int,int>
#define fi first
#define se second
int n,m;
int tot1,tot2,hd1[N],hd2[N];
struct Edge
{
    int next,to,w;
}e1[N<<1],e2[N<<1];
void add_edge1(int u,int v,int w){e1[++tot1]={hd1[u],v,w};hd1[u]=tot1;}
void add_edge2(int u,int v,int w){e2[++tot2]={hd2[u],v,w};hd2[u]=tot2;}
int idx,dfn[N],bk[N];
vector<Edge>vec;
void dfs1(int u,int fat)
{
    bk[u]=1;dfn[u]=++idx;
    for(int i=hd1[u];i;i=e1[i].next)
    {
        int v=e1[i].to;Edge tmp={u,v,e1[i].w};
        if(v==fat) continue;
        if(bk[v]) {vec.emplace_back(tmp);continue;}
        else add_edge2(u,v,e1[i].w);
        dfs1(v,u);
    }
}
namespace L_C_A
{
    int fa[N][21],mn[N][21],dep[N],vis[N];
    void dfs2(int u)
    {
        vis[u]=1;dep[u]=dep[fa[u][0]]+1;
        for(int i=1;i<=20;i++)
        {
            fa[u][i]=fa[fa[u][i-1]][i-1];
            mn[u][i]=min(mn[u][i-1],mn[fa[u][i-1]][i-1]);
        }
        for(int i=hd2[u];i;i=e2[i].next)
        {
            int v=e2[i].to;
            if(v==fa[u][0]||vis[v]) continue;
            fa[v][0]=u;mn[v][0]=e2[i].w;
            dfs2(v);
        }
    }
    PII LCA(int x,int y)
    {
        int ret=1e9;
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=20;i>=0;i--)
        {
            if(dep[fa[x][i]]>=dep[y])
                ret=min(ret,mn[x][i]),x=fa[x][i];
        }
        if(x==y) return {x,ret};
        for(int i=20;i>=0;i--)
        {
            if(fa[x][i]!=fa[y][i])
            {
                ret=min(ret,mn[x][i]),x=fa[x][i];
                ret=min(ret,mn[y][i]),y=fa[y][i];
            }
        }
        return {fa[x][0],min({ret,mn[x][0],mn[y][0]})};
    }
}using namespace L_C_A;
vector<int>Ans;
int bkk[N];
void Find(int u,int tar)
{
    while(u!=tar)
    {
        if(bkk[u]) break;
        bkk[u]=1;
        Ans.emplace_back(u);
        u=fa[u][0];
    }
}
void init()
{
    tot1=tot2=idx=0;
    for(int i=0;i<=n;i++)
    {
    	hd1[i]=hd2[i]=bk[i]=vis[i]=dep[i]=dfn[i]=bkk[i]=0;
    	for(int j=0;j<=20;j++) mn[i][j]=1e9,fa[i][j]=0;
	}
    Ans.clear();vec.clear();
}
void solve()
{
    scanf("%d%d",&n,&m);
    init();
    for(int i=1,x,y,z;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add_edge1(x,y,z);
        add_edge1(y,x,z);
    }
    for(int i=1;i<=n;i++) if(!bk[i]) dfs1(i,0);
    for(int i=1;i<=n;i++) if(!vis[i]) dfs2(i);
    int pos=0,ans=1e9;Edge ed;
    bool flag=0;
    for(Edge i:vec)
    {
        PII tmp=LCA(i.next,i.to);
        tmp.se=min(tmp.se,i.w);
        if(tmp.se<ans) ans=tmp.se,pos=tmp.fi,ed=i,flag=1;
    }
    Find(ed.next,pos);Ans.emplace_back(pos);
    Find(ed.to,pos);
    printf("%d %d\n",ans,Ans.size());
    for(int i:Ans) printf("%d ",i);putchar('\n');
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        solve();
    }
}
```
点个赞再走吧。

---

## 作者：yyrwlj (赞：4)

## 题意简述

给定一个无向图，边带权，找到最小的边权最小的环，输出这个最小的边权、环上点的个数和环上每个点的编号。

## 思路

回顾 Kruskal 求最小生成树的过程，若当前边所连的两个点在并查集上处于同一个集合，那么连上这条边就会产生环。

我们让边权降序排序，那么最后一个出现上述情况的边就是题目中要输出边权的边。

不升序排序看第一个出现这种情况的边，是因为可能因为没连边权大的边导致当前边没出现这种情况。

输出路径 dfs 即可，设刚才求出的边所连的两点分别是 $a$ 和 $b$，那么从 $b$ 开始 dfs，直到搜到 $a$ 为止，dfs 过程中用数组记录编号即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200005;
struct Edge{
    int a, b, c;
}g[N];
int f[N];
struct EDGE{
    int to, nxt;
}G[N << 1];
int h[N], idx;
bool vis[N];
int ans[N], tot, End;
bool cmp(Edge A,Edge B)
{
    return A.c > B.c;
}
int find(int x)
{
    if (x == f[x])
        return x;
    return f[x] = find(f[x]);
}
void add(int a,int b)
{
    G[++idx].to = b, G[idx].nxt = h[a], h[a] = idx;
}
bool dfs(int u,int fa)
{
    ans[++tot] = u;
    if (u == End)
    {
        printf("%d\n", tot);
        for (int i=1;i<=tot;i++)
            printf("%d ", ans[i]);
        putchar('\n');
        return true;
    }
    vis[u] = true;
    for (int i = h[u]; i; i = G[i].nxt)
    {
        int j = G[i].to;
        if (j == fa || vis[j])
            continue;
        if (dfs(j, u))
            return true;
    }
    tot --;
    return false;
}
void work()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i=1;i<=m;i++)
        scanf("%d%d%d", &g[i].a, &g[i].b, &g[i].c);
    sort(g + 1, g + m + 1, cmp);
    for (int i=1;i<=n;i++)
        f[i] = i;
    int mn;
    for (int i=1;i<=m;i++)
    {
        int fa = find(g[i].a), fb = find(g[i].b);
        if (fa == fb)
            mn = i;
        else
            f[fa] = fb;
    }
    printf("%d ", g[mn].c);
    for (int i=1;i<=n;i++)
        h[i] = 0;
    idx = 0;
    for (int i=1;i<=m;i++)
    {
        add(g[i].a, g[i].b);
        add(g[i].b, g[i].a);
    }
    for (int i=1;i<=n;i++)
        vis[i] = false;
    int u = g[mn].a, v = g[mn].b;
    End = u;
    tot = 0;
    dfs(v, u);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：escapist404 (赞：4)

给定简单无向图，边带权。求一个简单环，最小化环上边权最小值。

记图上点数为 $n$，边数为 $m$，则 $3 \le n \le m \le \min \left( \frac{n \cdot (n - 1)}{2}, 2 \cdot 10^5 \right)$。每条边的边权为正整数，且不超过 $10^6$。

---

要找一个环上的最小边，考虑模仿 Kruscal 算法的过程：将边权从大到小依次插入并查集里。只要两端点处在同一个集合里就说明有环。

记录最后一条两端点在同一集合中的边（记为 $e$），则这条边即为最小边权。证明考虑反证法。

思考怎么找这个环。在图上进行 dfs 即可。设 $e$ 连接点 $u, v$，则设 $u$ 的父亲为 $v$，从 $u$ 出发进行 dfs（不经过父节点），将经过的点入栈，搜索到 $v$ 时输出栈中的点。

或者，你可以试试用 LCT 做这个题，[LCT](https://www.luogu.com.cn/blog/Diaosi114514/solution-cf1927f) 做法。

---

```cpp
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class Dsu {
	std::vector<int> data;

public:
	int get(const int x) {
		if (data[x] > 0)
			return x;
		else {
			data[x] = -get(-data[x]);
			return -data[x];
		}
	}
	void merge(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) return;
		if (data[x] < data[y]) std::swap(x, y);
		data[x] += data[y], data[y] = -x;
		return;
	}
	bool same(int x, int y) { return get(x) == get(y); }
	Dsu(const int n) : data(n, 1) {}
};

void solve_single() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> ed(n);
	std::vector<std::tuple<int, int, int>> ed_t;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		--u, --v;
		ed[u].push_back(v), ed[v].push_back(u);
		ed_t.emplace_back(u, v, w);
	}
	std::sort(ed_t.begin(), ed_t.end(),
			  [](auto i, auto j) { return std::get<2>(i) > std::get<2>(j); });

	Dsu D(n);
	int id = -1;
	for (int i = 0; i < m; ++i) {
		auto [u, v, w] = ed_t[i];
		if (D.same(u, v)) id = i;
		D.merge(u, v);
	}

	int u, v, w;
	std::tie(u, v, w) = ed_t[id];
	bool ok = false;
	std::vector<bool> visit(n);
	std::vector<int> stack;
	auto dfs = [&](auto self, const int x, const int f) -> void {
		stack.push_back(x);
		visit[x] = true;
		if (x == v) {
			std::cout << w << " " << stack.size() << "\n";
			for (auto i : stack) std::cout << i + 1 << " ";
			std::cout << "\n";
			ok = true;
		}
		for (const auto i : ed[x]) {
			if (ok) break;
			if (i == f) continue;
			if (visit[i]) continue;
			self(self, i, x);
		}
		stack.pop_back();
	};
	dfs(dfs, u, v);
}

int main() {
	int tt;
	std::cin >> tt;
	while (tt--) {
		solve_single();
	}
	return 0;
}
```

---

## 作者：Diaоsi (赞：3)

[Microcycle](https://www.luogu.com.cn/problem/CF1927F)

以下是赛时做法：

注意到能成为答案的边一定在最小生成树上。证明很简单，若这条边不在最小生成树上，则可以通过调整使得这条边成为生成树的边从而使得生成树更小。

把最小生成树建出来后，剩下的每条非树边都会跟生成树构成一个环，对于非树边 $(u,v)$，它所在的环由它自身和树上 $u\rightarrow v$ 的路径构成。

对于所有的非树边，只需要查询树上路径 $u\rightarrow v$ 上的边权最小值并更新答案，输出方案只需要一遍 $\mathtt{DFS}$。

问题变成了树上路径查询，由于图可能不联通，用树剖维护略显麻烦，所以我选用了 $\mathtt{LCT}$ 进行维护。

时间复杂度为 $\mathcal{O}(m\log n)$，不够优秀。[Code](https://codeforces.com/contest/1927/submission/245353785)



------------


然而这题有线性做法：

首先环肯定属于边双连通分量，因此只要把所有的边双连通分量找出来，然后再判断每条边所连接的两个点是否属于同一个边双连通分量。若是，则这条边便能更新答案。

确定答案后，由更新答案的边出发做一遍 $\mathtt{DFS}$ 找环即可。

时间复杂度 $\mathcal{O}(n+m)$。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int head[N],ver[M],Next[M],edge[M],tot;
int T,n,m,ans,num,col,top,v[N],bl[N],st[N],dfn[N],low[N];
struct rec{int x,y,z;};
vector<rec> h;
void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void tarjan(int x,int fa=0){
	dfn[x]=low[x]=++num;
	st[++top]=x;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(y==fa)continue;
		if(!dfn[y]){
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
		}
		else low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int y;++col;
		do{
			y=st[top--];
			bl[y]=col;
		}while(x!=y);
	}
}
bool dfs(int x,int fa,int t){
	st[++top]=x;v[x]=1;
	if(x==t){
		printf("%d\n",top);
		for(int i=1;i<=top;i++)
			printf("%d ",st[i]);
		puts("");
		return 1;
	}
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(y==fa||v[y]||bl[y]!=bl[x])continue;
		if(dfs(y,x,t))return 1;
	}
	--top;
	return 0;
}
void solve(){
	scanf("%d%d",&n,&m);
	ans=INF;h.clear();
	num=top=tot=col=0;
	for(int i=1;i<=n;i++)
		head[i]=dfn[i]=low[i]=bl[i]=v[i]=0;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		h.push_back((rec){x,y,z});
		add(x,y,z),add(y,x,z);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	for(int i=0;i<m;i++){
		int x=h[i].x,y=h[i].y,z=h[i].z;
		if(bl[x]!=bl[y])continue;
		ans=min(ans,z);
	}
	printf("%d ",ans);top=0;
	for(int i=0;i<m;i++){
		int x=h[i].x,y=h[i].y,z=h[i].z;
		if(bl[x]!=bl[y])continue;
		if(z==ans){dfs(x,y,y);break;}
	}
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```


---

## 作者：SamHJD (赞：1)

## Microcycle

### Description

给出一个 $n$ 个点 $m$ 条边的无向图，找出一个环使环上最小的边权最小。

### Solution

在无向连通图中，一条边是环上的边仅当去掉该边后图连通。

按边权大到小加边，用并查集判断当前要加的边两端是否连通，是则将答案边更新为此边。

此处保证正确，反证：假设当前为答案边但两端点不连通，那么若不连此边，后面一定有一条边权比其小的边加入使这两个端点连通，那么答案边不为当前这条边，而应为后面使这两个端点连通的边。

找出边权最小的在环上的边后，用广搜得出环即可。

### [code](https://codeforces.com/contest/1927/submission/245433330)

---

## 作者：Wf_yjqd (赞：1)

水。

------------

我们要求最小的一条在环上的边所在的环。

想到在 kruskal 时，若一条边连接的两个点已经在同一联通块内了，这条边就在环上。

我们要让这样一条边最小，就求最大生成树。

这样所有比他大的边都联通了，若两个端点仍不联通，则他一定不优于更小的边。

找到最小的非树边并 dfs 找到环即可。

复杂度 $\operatorname{O}(n\log n)$。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
struct Edge{
    int u,v,w;
    friend bool operator<(Edge xy,Edge zb){
        return xy.w>zb.w;
    }
}e[maxn];
int T,n,m,u,v,w,fu,fv,id,fa[maxn];
inline int Find(int x){
    return x==fa[x]?x:fa[x]=Find(fa[x]);
}
namespace Sherry_Graph{
    struct edge{
        int to,ne,val;
    }E[maxn<<1];
    int ecnt=2,head[maxn],ffa[maxn];
    inline void add(Edge e){
        E[ecnt]={e.v,head[e.u],e.w};
        head[e.u]=ecnt++;
        E[ecnt]={e.u,head[e.v],e.w};
        head[e.v]=ecnt++;
        return ;
    }
    inline void dfs(int x,int f){
        ffa[x]=f;
        for(int i=head[x];i;i=E[i].ne)
            if(E[i].to!=f)
                dfs(E[i].to,x);
        return ;
    }
}
using namespace Sherry_Graph;
int st[maxn],top;
inline void Up(int x,int flag){
    st[++top]=x;
    if(x==flag)
        return ;
    Up(ffa[x],flag);
    return ;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
        sort(e+1,e+m+1);
        for(int i=1;i<=n;i++){
            fa[i]=i;
            head[i]=0;
        }
        ecnt=2;
        for(int i=1;i<=m;i++){
            fu=Find(e[i].u);
            fv=Find(e[i].v);
            if(fu==fv)
                id=i;
            else{
                fa[fu]=fv;
                add(e[i]);
            }
        }
        printf("%d ",e[id].w);
        dfs(e[id].u,0);
        top=0;
        Up(e[id].v,e[id].u);
        printf("%d\n",top);
        for(int i=1;i<=top;i++)
            printf("%d ",st[i]);
        puts("");
    }
    return 0;
}
```


---

## 作者：MrPython (赞：0)

这个题还算挺套路的。

我的思路如下：
1. tarjan 找到所有非割边
2. 按照这些边重新建图
3. 在这些边中找到权值最小的边
4. 以这条边的一个端点为起点，另一个为终点，跑 bfs 找环

~~相信各位大佬还有更好的思路，但是我这应该是不太需要脑子的~~
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
using graph=vector<vector<pair<size_t,ui>>>;
struct edge{
    size_t u,v;ui w;
};
void tarjan(size_t p,size_t fa,vector<edge>& ans,vector<size_t>& dfn,vector<size_t>& low,size_t& t,graph const& mp){
    low[p]=dfn[p]=t++;
    for (pair<size_t,ui> const& i:mp[p])
        if(!~dfn[i.first]){
            tarjan(i.first,p,ans,dfn,low,t,mp);
            low[p]=min(low[p],low[i.first]);
            if(low[i.first]<=dfn[p]) ans.push_back({p,i.first,i.second}),ans.push_back({i.first,p,i.second});
        }else{
            if(i.first!=fa) low[p]=min(low[p],dfn[i.first]),
                ans.push_back({p,i.first,i.second});
        }
}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n,m;cin>>n>>m;
        graph mp(n);
        while (m--){
            edge i;cin>>i.u>>i.v>>i.w;--i.u,--i.v;
            mp[i.u].emplace_back(i.v,i.w),mp[i.v].emplace_back(i.u,i.w);
        }
        vector<edge> e;vector<size_t> dfn(n,~0),low(n,~0);size_t t=0;
        for (size_t i=0;i<n;++i) if (!~dfn[i]) tarjan(i,~0,e,dfn,low,t,mp);
        edge mine=e.front();
        for (edge const& i:e) if (i.w<mine.w) mine=i;
        graph nmp(n);
        for (edge const& i:e) nmp[i.u].push_back({i.v,i.w});
        vector<size_t> prev(n,~0);queue<size_t> q({mine.u});prev[mine.u]=n;
        while (!q.empty()){
            size_t p=q.front();q.pop();
            if (p==mine.v) goto ok;
            for (pair<size_t,ui>& i:nmp[p]) if (!~prev[i.first]&&!(p==mine.u&&i.first==mine.v))
                prev[i.first]=p,q.push(i.first);
        }
        throw;
        ok:;
        vector<size_t> ans;
        for (size_t i=mine.v;i!=n;i=prev[i]) ans.push_back(i);
        cout<<mine.w<<' '<<ans.size()<<'\n';
        for (size_t i:ans) cout<<i+1<<' ';
        cout.put('\n');
    }
    return 0;
}
```

---

## 作者：Zemu_Ooo (赞：0)

作为我在 CF 上第一次 AK 的一场 Div，我对这道题印象再深不过了，因为做这道题忘了图不连通，吃了两发罚时，与 rk 3 失之交臂（

题意：在给定的无向加权图中找到一个简单环，使得环中最轻的边的权重最小。

首先识别图中的所有桥边（即删除该边会增加图的连通分量数量的边）。这是因为一个简单环不可能包含桥边，否则去除桥边后环将无法形成。在所有非桥边中寻找权重最小的边，这样可以保证找到的环中最轻的边权重尽可能小。这部分用 Tarjan 找桥边即可。

然后构建包含这条边的简单环。可以通过从这条边的一个端点开始，用广搜找到一条到另一个端点的路径。这条路径与选定的边一起就形成了所需的简单环。

最后输出所找到的环中最轻的边的权重，环中顶点的数量以及环的顶点序列就行。

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

#define int long long
const int MAXN = 1e6;
vector<pair<int, int>> vv[MAXN];
int low[MAXN], dfn[MAXN], tot;
int minn = 1e18, ansx, ansy;
map<pair<int, int>, bool> mp;

// 找桥边
void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++tot;
    for (auto &edge : vv[u]) {
        int v = edge.first;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                mp[{u, v}] = mp[{v, u}] = true; // 标记桥边
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 找从st到ed的路径
void bfs(int st, int ed, vector<int> &pre) {
    queue<int> q;
    q.push(st);
    pre[st] = st;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto &y : vv[x]) {
            if (pre[y.first] || (x == st && y.first == ed)) continue;
            pre[y.first] = x;
            q.push(y.first);
        }
    }
}

// 输出路径
void Cout(int x, const vector<int> &pre, vector<int> &ans) {
    if (pre[x] != x) Cout(pre[x], pre, ans);
    ans.push_back(x);
}

void work() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        vv[x].push_back({y, w});
        vv[y].push_back({x, w});
    }

    tot = 0;
    minn = 1e18;
    mp.clear();
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);

    for (int i = 1; i <= n; i++) {
        for (auto &y : vv[i]) {
            if (mp[{i, y.first}]) continue; // 忽略桥边
            if (y.second < minn) {
                minn = y.second;
                ansx = i, ansy = y.first;
            }
        }
    }

    vector<int> ans, pre(n + 1, 0);
    bfs(ansx, ansy, pre);
    Cout(ansy, pre, ans);

    cout << minn << ' ' << ans.size() << endl;
    for (auto &v : ans) cout << v << ' ';
    cout << endl;

    for (int i = 1; i <= n; i++) {
        vv[i].clear();
        pre[i] = 0;
        low[i] = 0;
        dfn[i] = 0;
    }
}

signed main() {
    int TT;
    cin >> TT;
    while (TT--) work();
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

考虑枚举可能的最小边。

发现边 $(u,v)$ 可以与其它边连成一个环，当且仅当这条边不是桥，于是我们求出所有的桥，找到合法的最小边再 dfs 一遍找环即可。

时间复杂度 $\mathcal{O}(n+m)$。[Link](https://codeforces.com/contest/1927/submission/245226680)。

---

