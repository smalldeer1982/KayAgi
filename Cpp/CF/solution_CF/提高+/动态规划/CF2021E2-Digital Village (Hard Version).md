# Digital Village (Hard Version)

## 题目描述

**这是问题的困难版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0```

# 题解

## 作者：int08 (赞：7)

## 前言
写这句话是为了不让我的题解没有前言。
## 题意
给一个边有边权的无向图，有给定的 $k$ 点需要网络，选择一些点装服务器之后，需要网络的点会连向延迟最小的服务器，延迟定义为路径上的最大边权，求装了 $x$ 台服务器的情况下最小的延迟和。
# Solution

看到这个“路径上的最大边权”，想都不想跑一个最小生成树，显然需要网络的点会走树上的路径。

考虑从小到大加入最小生成树的边，每次会合并两个连通块，我们尝试合并它们的答案，设 $dp_{u,i}$ 表示 $u$ 所在连通块使用 $i$ 个服务器的最小延迟和。

枚举两个连通块的服务器数，设为 $i,j$。

如果两者都不为 $0$，那么连通它们的边显然不会走（从小到大加边，两个连通块里的边绝对更小），没有贡献。

如果其中一个为 $0$，那么这个连通块里的所有需要网络的点（记作 $sz_u$）都会从这条边到对面去，产生 $sz_u\times w$ 的贡献。

于是发现合并两个连通块复杂度为 $O(sz_u\times sz_v)$，全部合并起来复杂度为 $O(n^2)$，证明同树上背包复杂度证明，可以通过 E2。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 5080
int T,n,m,k,i,j,sz[N],fa[N],x,res[N];
int dp[N][N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int u,v,w;
vector<pair<int,pair<int,int> > > e;
#define fi first
#define se second
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>k;
		for(i=1;i<=n;i++) fa[i]=i;
		for(i=1;i<=k;i++) cin>>x,sz[x]=1;
		for(i=1;i<=m;i++) cin>>u>>v>>w,e.push_back({w,{u,v}});
		sort(e.begin(),e.end());
		for(auto x:e)
		{
			u=x.se.fi,v=x.se.se,w=x.fi;
			int fu=find(u),fv=find(v);
			if(fu==fv) continue;
			fa[fv]=fu;
			for(i=1;i<=sz[fu]+sz[fv];i++) res[i]=1e18;
			for(i=1;i<=sz[fu];i++) res[i]=min(res[i],dp[fu][i]+w*sz[fv]);
			for(i=1;i<=sz[fv];i++) res[i]=min(res[i],dp[fv][i]+w*sz[fu]);
			for(i=1;i<=sz[fu];i++)
				for(j=1;j<=sz[fv];j++) res[i+j]=min(res[i+j],dp[fu][i]+dp[fv][j]);
			for(i=1;i<=sz[fu]+sz[fv];i++) dp[fu][i]=res[i];
			sz[fu]+=sz[fv];
		}
		int rt=find(1);
		for(i=1;i<=n;i++) cout<<dp[rt][i]<<" ";
		cout<<endl;
		for(i=0;i<=n;i++)
		{
			sz[i]=0,fa[i]=0,res[i]=0;
			for(j=0;j<=n;j++) dp[i][j]=0;
		}
		e.clear();
	}
	return 0;
 } 
```
# The End.

---

## 作者：harmis_yz (赞：1)

E3 太难了，只能秒 E2。

## 分析

要使得路径最大值最小，优先考虑建一棵重构树出来。那么问题转化为树形 DP。定义状态函数 $f_{i,j}$ 表示 $i$ 为根的子树中选择 $j$ 的点的最小路径长度和。因为重构树是一棵二叉树，且点权表示了两个子树中任意两个点的路径长度最小最大值。所以有：$f_{v0,0}=cnt_{v0}\times val_u,f_{v1,0}=cnt_{v1}\times val_u$。其它的 $f_{v,j}$ 都已经求出来了，暴力枚举即可。转移方程为：$f_{u,i+j}=\min\{f_{v0,i}+f_{v1,j}|0 \le i \le siz_{v0} \land 0 \le j \le siz_{v1}\}$。这里 $cnt_i$ 表示 $i$ 为根的子树中关键点的数量，$siz_i$ 表示 $i$ 为根的子树中原本图上的点的数量。复杂度 $O(n^2)$。

然后 E1 和 E2 就能一起过了。但是如果你直接开这样一个二维数组可能会爆空间，开动态数组即可（每个点开到 $siz$ 就够了）。

## 代码

```cpp
il int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
il void dfs(int u){
	siz[u]=0,Siz[u]=0;
	v[u].clear();
	if(!tr[u].ch[2]){
		v[u].push_back(0),v[u].push_back(0);
		siz[u]=vis[u],Siz[u]=1;
		return ;
	}
	dfs(tr[u].ch[0]),dfs(tr[u].ch[1]);
	for(re int i=0;i<=n;++i) dp[i]=1e18;
	v[tr[u].ch[0]][0]=(siz[tr[u].ch[0]]?siz[tr[u].ch[0]]*tr[u].val:0ll);
	v[tr[u].ch[1]][0]=(siz[tr[u].ch[1]]?siz[tr[u].ch[1]]*tr[u].val:0ll);
	for(re int i=0;i<=Siz[tr[u].ch[0]];++i)
	for(re int j=0;j<=Siz[tr[u].ch[1]];++j)
		if(i==0&&j==0) dp[i+j]=0;
		else dp[i+j]=min(dp[i+j],v[tr[u].ch[0]][i]+v[tr[u].ch[1]][j]);	
	siz[u]=siz[tr[u].ch[0]]+siz[tr[u].ch[1]];
	Siz[u]=Siz[tr[u].ch[0]]+Siz[tr[u].ch[1]];
	for(re int i=0;i<=Siz[u];++i) v[u].push_back(dp[i]);
	return ;
}

il void solve(){
	n=rd,m=rd,p=rd,idx=0,cnt=0;
	for(re int i=1;i<=2*n;++i) h[i]=0,tr[i]={0,0,0},f[i]=i,vis[i]=0;
	for(re int i=1;i<=p;++i) vis[rd]=1;
	for(re int i=1;i<=m;++i) E[i]={rd,rd,rd};
	sort(E+1,E+m+1),cnt=n;
	for(re int i=1;i<=m;++i){
		int x=E[i].x,y=E[i].y;
		if(find(x)==find(y)) continue;
		++cnt;
		tr[cnt].ch[0]=find(x),tr[cnt].ch[1]=find(y);
		tr[cnt].val=E[i].z;
		f[find(x)]=f[find(y)]=find(cnt);
	}
	dfs(cnt);
	for(re int i=1;i<=n;++i) printf("%lld ",v[cnt][i]);
    return ;
}
```

---

## 作者：lfxxx (赞：0)

首先建出 kruskal 重构树。

房屋到一个服务器的代价就是两点在重构树上的 LCA 所代表的边的边权。

然后我们观察一下，对于一个子树而言，假若子树中存在至少一个服务器，那么子树内的所有点与这个服务器匹配，代价为子树根的权值，是优于与子树外任意服务器匹配的，因为重构树上一个点的权值小于等于其所有祖先的权值。

因此一个子树对子树外而言只有两种状态，子树内存在至少一台服务器使得子树内所有需要联网的房屋全部满足要求，或者子树内一台服务器都不存在。

因此设计状态 $f_{u,i}$ 表示子树 $u$ 内有 $i$ 台服务器时子树 $u$ 内需要联网的房屋的最小花费之和，再令 $sz_u$ 表示 $u$ 子树内需要联网的房屋数量，有 $f_{u,i} = \min(\min(f_{ls,i} + sz_{rs} \times w_u,f_{rs,i} + sz_{ls} \times w_u),\min_{1 \leq j < i}(f_{ls,j} + f_{rs,i-j}))$。

这个形式有点丑，但是不妨令 $f_{u,0} = sz_u \times w_{fa}$，那么你发现 $f_{u,i}$ 就是由 $f_{ls,i}$ 与 $f_{rs,i}$ 先做闵可夫斯基和再将 $f_{u,0}$ 增加一个非负数得到。

dp 的边界条件是 $f_{u,0} = sz_u \times w_{fa},f_{u,1} = 0$，此时 $f_{u,i}$ 是凸的，因此在经过上述合并操作后依然是凸的，所以直接用可并堆维护差分数组即可做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int ls[maxn<<1],rs[maxn<<1];
int w[maxn<<1];
int fa[maxn<<1];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int n,m,p,tot;
pair<int,pair<int,int> > e[maxn];
const int inf = 1e9+114;
int root[maxn<<1];
int g[maxn<<1];
struct node{
    int v,ls,rs,dist;
    node(){
        v=ls=rs=dist=0;
    }
}tr[maxn];//大根堆
int cnt;
void pushup(int cur){
    if(tr[tr[cur].ls].dist<tr[tr[cur].rs].dist) swap(tr[cur].ls,tr[cur].rs);
    tr[cur].dist=tr[tr[cur].rs].dist+1;
}
int merge(int a,int b){
    if(a==0||b==0) return a+b;
    if(tr[a].v>tr[b].v){
        tr[a].rs=merge(tr[a].rs,b);
        pushup(a);
        return a;
    }
    tr[b].rs=merge(tr[b].rs,a);
    pushup(b);
    return b;
}
int sz[maxn<<1];
void dp(int u,int fa){
    if(u<=n){
        g[u]=sz[u]*w[fa];
        cnt++;
        tr[cnt].v=g[u];
        root[u]=cnt;
        return ;
    }
    dp(ls[u],u),dp(rs[u],u);
    root[u]=merge(root[ls[u]],root[rs[u]]);
    g[u]=g[ls[u]]+g[rs[u]];
    sz[u]=sz[ls[u]]+sz[rs[u]];
    tr[root[u]].v+=sz[u]*w[fa]-g[u];
    g[u]=sz[u]*w[fa];
    return ;
}
void work(){
    cin>>n>>m>>p;
    tot=n;
    for(int i=1;i<=p;i++){
        int x;
        cin>>x;
        sz[x]=1;
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) cin>>e[i].second.first>>e[i].second.second>>e[i].first;
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++){
        int u=found(e[i].second.first),v=found(e[i].second.second);
        if(u!=v){
            tot++;
            ls[tot]=u,rs[tot]=v;
            fa[tot]=fa[u]=fa[v]=tot;
            w[tot]=e[i].first;
        }
    }
    w[0]=inf;
    dp(tot,0);
    for(int i=1;i<=n;i++){
        g[tot]-=tr[root[tot]].v;
        root[tot]=merge(tr[root[tot]].ls,tr[root[tot]].rs);
        cout<<g[tot]<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=cnt;i++) tr[i]=node();
    for(int i=1;i<=tot;i++) sz[i]=g[i]=root[i]=ls[i]=rs[i]=w[i]=fa[i]=0;
    cnt=tot=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：Zeoykkk (赞：0)

## CF2021E2. Digital Village

>给定一个 $n$ 个点 $m$ 条边的无向图，其中有 $p$ 个点为特殊点，假设图上有 $k$ 个点存在服务器，我们的目标是花费最小的代价使得所有的特殊点都连接上服务器，例如特殊点 $u$ 连接到服务器 $v$ 的代价为 $u$ 到 $v$ 所有路径中边的最大权值的最小值。求当 $k = 1,2,...,n$ 时所有特殊点都连接上服务器的最小代价和。$n, m, p \leq 5\times 10^3$

### Sol

>贪心的，我们只会在特殊点上建服务器。
>
>若 $n \leq 400$，则考虑先通过 floyd 求得图上所有点对之间连接的最小代价，即 $dis[u][v]$ 代表 $u$ 到 $v$ 的所有路径中边的最大权值的最小值。然后通过迭代 $k$，每次迭代求出每次最优的新的服务器站点。复杂度 $O(n^3)$。
>
>若 $n \leq 5000 $，容易想到 $u$ 到 $v$ 的代价等价于在原图的最小生成树上 $u$ 到 $v$ 的简单路径上的最大边权。考虑到该性质，不妨考虑对原图建 kruskal 重构树后树上背包，定义 $dp[u][i]$ 代表在 $u$ 的子树中有 $i$ 个特殊点存在服务器，然后使得子树中所有特殊点都连接上服务器的最小代价和。
>
>因为kruskal 重构树是二叉树，转移的话枚举左右子树中特殊点的数量转移即可，需要注意的是，在kruskal 重构树上点 $u$ 所代表的边能够产生贡献，当且仅当左右子树中存在一个子树中不存在服务器，但仍有特殊点需要连接服务器，因为如果左右子树中都有服务器，则子树中的特殊点连接服务器一定不会经过点 $u$ 所代表的边。
>$$
>\begin{equation}
>	\left\{
>		\begin{array}{lr}
>		ndp[i + j] = \min(ndp[i + j], dp[u][i] + dp[v][j]), & 1\leq i \leq sz[u], 1 \leq j \leq sz[v]  \\
>		ndp[i] = \min(ndp[i], dp[u][i] + w \times sz[v]), & 1\leq i \leq sz[u] \\
>		ndp[i] = \min(ndp[i], dp[v][i] + w\times sz[u]), & 1\leq i \leq sz[v]
>		\end{array}
>	\right. 
>\end{equation}
>$$
>其中 $sz[u]$ 代表子树 $u$ 中特殊点的数量，$w$ 代表重构树上点 $u$ 所代表的边的边权。复杂度 $O(n^2)$。但是如果真的将重构树建出来然后树上背包就被卡空间了，但实际上我们只要在并查集合并 $(u, v, w)$ 的时候都合并到 $u$ 或 $v$ 即可，不需要新建节点。
```cpp
// 被卡空间的 Code
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
// #define int long long
#define pb push_back
#define endl '\n'
using ll = long long;
constexpr ll inf = 1ll << 60;
constexpr ll mod = 1000000007;
const int N = 5e3 + 10;

int n, m, p;
bool ins[N];
array<int, 3> edge[N];

int fa[N << 1], a[N << 1], sz[N << 1], tot;
ll dp[N << 1][N];
vector<int> adj[N << 1];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y, int w) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    ++tot;
    a[tot] = w;
    adj[tot].pb(fx), adj[tot].pb(fy);
    fa[fx] = fa[fy] = tot;
}

inline void dfs(int u) {
    if (!SZ(adj[u])) {
        if (ins[u]) {
            sz[u] = 1;
            dp[u][1] = 0;
        } else sz[u] = 0;
        return;
    }
    sz[u] = 0;
    static ll tmp[N];
    for (auto v : adj[u]) {
        dfs(v);
        for (int i = 0; i <= sz[u] + sz[v]; ++i) tmp[i] = inf;
        for (int i = 1; i <= sz[u]; ++i) {
            for (int j = 1; j <= sz[v]; ++j) {
                tmp[i + j] = min(tmp[i + j], dp[u][i] + dp[v][j]);
            }
        }
        for (int i = 1; i <= sz[u]; ++i) {
            tmp[i] = min(tmp[i], dp[u][i] + 1ll * a[u] * sz[v]);
        }
        for (int i = 1; i <= sz[v]; ++i) {
            tmp[i] = min(tmp[i], dp[v][i] + 1ll * a[u] * sz[u]);
        }
        for (int i = 1; i <= sz[u] + sz[v]; ++i) dp[u][i] = tmp[i];
        sz[u] += sz[v];
    }
}

void solve() {
    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) ins[i] = false;
    for (int i = 1; i <= p; ++i) {
        int x; cin >> x;
        ins[x] = true;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = {w, u, v};
    }
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= 2 * n; ++i) {
        fa[i] = i;
        adj[i].clear();
    }
    tot = n;
    for (int i = 1; i <= m; ++i) {
        auto [w, u, v] = edge[i];
        merge(u, v, w);
    }
    dfs(tot);
    for (int i = 1; i <= n; ++i) {
        if (i >= p) cout << 0 << " ";
        else cout << dp[tot][i] << " ";
    }
    cout << endl;
}
signed main(void) {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Test = 1;
    cin >> Test;
    while (Test--) solve();
    return 0;
}
```
```cpp
// 正解
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
// #define int long long
#define pb push_back
#define endl '\n'
using ll = long long;
constexpr ll inf = 1ll << 60;
constexpr ll mod = 1000000007;
const int N = 5e3 + 10;

int n, m, p;
bool ins[N];
array<int, 3> edge[N];

int fa[N], sz[N];
ll dp[N][N], tmp[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y, int w) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    if (sz[fx] > sz[fy]) swap(fx, fy), swap(x, y);
    for (int i = 1; i <= sz[fx] + sz[fy]; ++i) tmp[i] = inf;
    for (int i = 1; i <= sz[fx]; ++i) {
        for (int j = 1; j <= sz[fy]; ++j) {
            tmp[i + j] = min(tmp[i + j], dp[fx][i] + dp[fy][j]);
        }
    }
    for (int i = 1; i <= sz[fx]; ++i) {
        tmp[i] = min(tmp[i], dp[fx][i] + 1ll * w * sz[fy]);
    }
    for (int i = 1; i <= sz[fy]; ++i) {
        tmp[i] = min(tmp[i], dp[fy][i] + 1ll * w * sz[fx]);
    }
    for (int i = 1; i <= sz[fx] + sz[fy]; ++i) dp[fy][i] = tmp[i];
    fa[fx] = fy;
    sz[fy] += sz[fx];
}

void solve() {
    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) ins[i] = false;
    for (int i = 1; i <= p; ++i) {
        int x; cin >> x;
        ins[x] = true;
    }
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        if (ins[i]) sz[i] = 1, dp[i][1] = 0;
        else sz[i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = {w, u, v};
    }
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; ++i) {
        auto [w, u, v] = edge[i];
        merge(u, v, w);
    }
    for (int i = 1; i <= n; ++i) {
        if (i >= p) cout << 0 << " ";
        else cout << dp[find(i)][i] << " ";
    }
    cout << endl;
}
signed main(void) {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Test = 1;
    cin >> Test;
    while (Test--) solve();
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

考虑 Kruskal 重构树。

显然把重构树建出来之后，一个点 $u$ 到另一个点 $v$ 的最小瓶颈路就是 $w_{\operatorname{lca}(u,v)}$，然后我们发现可以直接背包。记 $f_{u,i}$ 表示在以 $u$ 为根的子树内，选了 $i$  个点作为服务器的最小代价。那么转移就是类似树上背包地转移，注意如果 $u$ 的儿子 $v$ 的子树内一个服务器都没有，那么还要再加上 $sz_v\times w_u$ 转移，其中 $sz_v$ 表示以 $v$ 为根的子树内的关键点的个数。

时间复杂度也和树上背包一样，是 $\mathcal O(n^2)$ 的，可能有些卡空间。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,p,fa[10005],cnt,w[10005],sz[10005],vis[10005],x,sz2[10005],g[10005];
vector<int>ve[10005],f[10005];
struct ee{
	int u,v,w;
	friend bool operator<(const ee&a,const ee&b){
		return a.w<b.w;
	}
}e[10005];
int find(int x){
	return(fa[x]==x)?x:fa[x]=find(fa[x]);
}
void dfs(int u,int fa){
	sz[u]=1;
	if(vis[u]){
		f[u].resize(2);
		f[u][0]=f[u][1]=0,sz2[u]=1;
		return;
	}
	int now=0;
	for(int v:ve[u]){
		if(v==fa)continue;
		dfs(v,u),now+=sz2[v];
	}
	f[u].resize(now+1,(int)1e18),f[u][0]=0;
	for(int v:ve[u]){
		if(v==fa)continue;
		for(int i=0;i<=n;i++)g[i]=1e18;
		for(int j=sz2[u];~j;j--)for(int i=0;i<=sz2[v];i++){
			if(i==0)g[j+i]=min(g[j+i],f[u][j]+sz2[v]*w[u]);
			else g[j+i]=min(g[j+i],f[u][j]+f[v][i]);
		}
		sz[u]+=sz[v],sz2[u]+=sz2[v];
		for(int i=0;i<=sz2[u];i++)f[u][i]=g[i];
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>p,cnt=n;
		for(int i=1;i<=2*n;i++)fa[i]=i,ve[i].clear(),vis[i]=0,sz[i]=sz2[i]=0;
		for(int i=1;i<=p;i++)cin>>x,vis[x]=1;
		for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w;
		sort(e+1,e+m+1);
		for(int i=1;i<=m;i++){
			int fx=find(e[i].u),fy=find(e[i].v);
			if(fx==fy)continue;
			cnt++,fa[fx]=fa[fy]=cnt,ve[cnt].emplace_back(fx),ve[cnt].emplace_back(fy),w[cnt]=e[i].w;
		}
		dfs(cnt,0);
		for(int i=1;i<=n;i++){
			if(sz2[cnt]<i)cout<<0<<" ";
			else cout<<f[cnt][i]<<" ";
		}cout<<"\n"; 
	}
}
```

---

