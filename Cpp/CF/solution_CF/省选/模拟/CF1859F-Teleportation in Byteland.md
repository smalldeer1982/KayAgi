# Teleportation in Byteland

## 题目描述

# 在比特兰的传送


比特兰有 $ n $ 个城市，其中一些城市由道路连接，道路可以双向通行。第 $ i $ 条道路有其自身的难度参数 $ w_i $。以难度为 $ w_i $ 的道路上的通行时间为 $ \lceil\frac{w_i}{c}\rceil $，其中 $ c $ 是当前驾驶技能。

比特兰的旅行网络是一棵树。换句话说，在任意两个城市之间，最多只有一条经过每个城市的路径。

在一些城市中，您可以参加驾驶课程。完成单个课程需要 $ T $ 时间，并且完成课程后驾驶员的技能 $ c $ 翻倍。请注意，完成课程所需的时间 $ T $ 在所有城市中是相同的，并且可以在同一个城市中多次完成课程。

您需要回答 $ q $ 个查询：如果您从技能 $ c = 1 $ 开始旅行，从城市 $ a $ 到城市 $ b $ 所需的最短时间是多少？

## 说明/提示

在第一个测试案例的唯一一个查询中，最优的策略是忽略驾驶课程。然后，所需的最短时间等于顶点 $ 1 $ 到顶点 $ 2 $ 之间的距离，即 $ 1 $。

在第二个测试案例的第一个查询中，我们可以在城市号为 $ 1 $ 花费 $ 3 $ 时间参加驾驶课程，然后前往顶点 $ 5 $。然后，所需的最短时间为 $ 3 + \lceil\frac{5}{2}\rceil + \lceil\frac{10}{2}\rceil = 11 $。

## 样例 #1

### 输入

```
2
2 3
1 2 1
11
1
1 2
5 3
1 4 5
1 3 8
2 3 8
4 5 10
11001
5
1 5
2 5
5 1
3 4
4 2```

### 输出

```
1
11
14
11
13
15```

# 题解

## 作者：OrezTsim (赞：6)

为啥这题 3200 啊，评分虚高了吧。

---

首先，经过 $\log$ 次学习后整张图的边权相当于都变成 $1$。

贪心地找到在学习 $k$ 次的情况下，从每个点出发学习后再回到这个点的经过的最短路径。

这部分可以通过多源 dijkstra 解决。

剩下的部分就可以分类讨论了。

有如下标记。

- 当前学习 $k$ 次。
- $d_k(c)$ 表示每一条边的边权 $p_i \leftarrow \left \lceil \dfrac{p_i}{2^{k}} \right \rceil$ 后，点 $c$ 到根节点的路径和。 
- $f_k(c)$ 表示从 $c$ 出发到某点学习 $k$ 次后再回到这个点经过的最短路径。

假设当前要从 $x \rightarrow \text{lca}(x,y) \rightarrow y$，那么：

- 从 $x \rightarrow \text{lca}(x,y)$ 的路径上一点 $v$ 出发去学习，那么答案为 $d_0(x)-d_0(v)+f_k(v)+d_k(v)+d_k(y)-2 \times d_k(\text{lca}(x,y))$。
- 从 $\text{lca}(x,y) \rightarrow y$ 的路径上一点 $v$ 出发去学习，那么答案为 $d_0(x)+d_0(v)-2\times d_0(\text{lca}(x,y))+f_k(v)+d_k(y)-d_k(v)$。

发现变化的项，即仅与 $v$ 有关的项可以提出来倍增求最值。

维护 $\min\{f_k(v)+d_k(v)-d_0(v)\}$ 与 $\min\{f_k(v)+d_0(v)-d_k(v)\}$ 即可。

时间复杂度 $O(n \log^2 n)$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10, inf = 1e12;
int t, n, q, mul, d[N], dat[N], res[N], dis[N], dep[N], fa[17][N], vl[2][17][N];
vector <pair <int, int> > g[N], r[N]; bool vis[N];
int x[N], y[N], lc[N]; char sta[N];

inline void dfs(int cur, int f) {
    dep[cur] = dep[f] + 1, fa[0][cur] = f;
    for (int i = 1; i < 17; ++i) fa[i][cur] = fa[i - 1][fa[i - 1][cur]];
    for (auto [to, v]: g[cur]) if (to ^ f) d[to] = d[cur] + v, dfs(to, cur);
}

inline void _dfs(int cur, int f) {
    vl[0][0][cur] = dis[cur] + dat[cur] - d[cur];
    vl[1][0][cur] = dis[cur] + d[cur] - dat[cur];
    for (int i = 1; i < 17; ++i) {
        vl[0][i][cur] = min(vl[0][i - 1][cur], vl[0][i - 1][fa[i - 1][cur]]);
        vl[1][i][cur] = min(vl[1][i - 1][cur], vl[1][i - 1][fa[i - 1][cur]]);
    }
    for (auto [to, v]: r[cur])
        if (to ^ f) dat[to] = dat[cur] + v, _dfs(to, cur);
}

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 16; ~i; --i) if (dep[fa[i][u]] >= dep[v]) u = fa[i][u];
    if (u == v) return u;
    for (int i = 16; ~i; --i) if (fa[i][u] ^ fa[i][v]) u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}

inline void init(int div) {
	priority_queue <pair <int, int> > p;
    for (int i = 1; i <= n; ++i) {
		dis[i] = inf, vis[i] = false;
        if (sta[i] == '1') p.push({dis[i] = 0, i});
    }
    while (!p.empty()) {
        int cur = p.top().second; p.pop();
        if (vis[cur]) continue; vis[cur] = true;
        for (auto [to, v]: g[cur]) if (dis[to] > dis[cur] + v + (v - 1) / div + 1)
            dis[to] = dis[cur] + v + (v - 1) / div + 1, p.push({-dis[to], to});
    }
}

inline void solve() {
    cin >> n >> mul;
    for (int i = 1, u, v, w; i < n; ++i)
        cin >> u >> v >> w, g[u].push_back({v, w}), g[v].push_back({u, w});
    for (int i = 1; i <= n; ++i) cin >> sta[i]; dfs(1, 0), cin >> q;
    for (int i = 1; i <= q; ++i) cin >> x[i] >> y[i], lc[i] = lca(x[i], y[i]);
    for (int i = 1; i <= q; ++i) res[i] = d[x[i]] + d[y[i]] - 2 * d[lc[i]];
    for (int k = 1, ml = 2; k < 21; ++k, ml <<= 1) {
        for (int i = 1; i <= n; ++i) {
            r[i].clear();
            for (auto [to, v]: g[i])
                r[i].push_back({to, (v - 1) / ml + 1});
        }
        init(ml), _dfs(1, 0);
        for (int i = 1; i <= q; ++i) {
            int cx = x[i], cy = y[i], tmp = inf;
			int add = d[x[i]] + dat[y[i]] - 2 * dat[lc[i]];
            for (int j = 16; ~j; --j)
                if (fa[j][cx] && dep[fa[j][cx]] + 1 >= dep[lc[i]])
                    tmp = min(tmp, vl[0][j][cx] + add), cx = fa[j][cx];
            add = d[x[i]] + dat[y[i]] - 2 * d[lc[i]];
            for (int j = 16; ~j; --j)
                if (fa[j][cy] && dep[fa[j][cy]] + 1 >= dep[lc[i]])
                    tmp = min(tmp, vl[1][j][cy] + add), cy = fa[j][cy];
            tmp = min(tmp, vl[1][0][lc[i]] + add);
            res[i] = min(res[i], tmp + k * mul);
        }
    }
    for (int i = 1; i <= q; ++i) cout << res[i] << endl;
    for (int i = 1; i <= n; ++i) g[i].clear();
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：LJ07 (赞：2)

+ $O(\log V)$ 次学习后再学习是无意义的。因为此时硬度已经全部降为 $1$。
+ 每个点学习一定是到离它最近的点反复学习。这个可以用最短路简单处理（当然此时要根据初始学习次数进行处理）。
+ 根据贪心，你发现你一定在一个点学习完。所以可以枚举学习次数。dp 变为 $f_{u,0/1}$ 表示当前点是 $u$，是否达到目标学习次数。
+ 线性变换考虑暴躁矩阵快速幂。$+,\times$ 换成 $\min,+$ 即可： $\left [ \begin{matrix}f_0,f_1\end{matrix}\right ]\left [ \begin{matrix}w,c\\\inf,\lfloor\frac{w}{2^{cnt}}\rfloor\end{matrix}\right ]=\left [ \begin{matrix}f_0,f_1\end{matrix}\right ]$。其中 $w$ 表示到当前点的硬度，$cnt$ 表示当前学习的次数。$c$ 表示到离当前点最近可以学习的地方学习 $cnt$ 次然后回来的硬度之和（这是可以预处理的）。
+ 树剖简单预处理整条链可以做到 $O(w^{2}n\log V+w^{2}q\log n\log V)$。
+ 可以适当使用向量乘矩阵优化复杂度。或者你把这个矩阵优化成正常转移也行。

---

## 作者：larsr (赞：1)

评分虚高。感觉是 [P11324](https://www.luogu.com.cn/problem/P11324) 的加强版？

首先对 $\log V$ 种 $c$ 枚举。对于询问 $[a,b]$，它们的 LCA 是 $l$，设上课的点是 $w$，该点离 $a,b$ 链上最近的点是 $p$。分别考虑 $p$ 在 $[a,l]$ 上和 $[b,l]$ 上即可，拆贡献+树形 DP 即可，复杂度 $O(n\log^2n)$。

[sub](https://codeforces.com/contest/1859/submission/303486844)

---

## 作者：_ZSR_ (赞：1)

### [CF1859F Teleportation in Byteland](https://www.luogu.com.cn/problem/CF1859F)

因为课程所需的时间是相同的，所以我们不会跑到两个不同的地方去上课。这样的话，每次从 $x$ 到 $y$ 的过程中，要么直接从 $x$ 到 $y$，要么先从 $x$ 到 $x,y$ 路径上的一点 $u$，再从 $u$ 到 $v$ 去上课并且回到 $u$，最后从 $u$ 到 $y$。

第一种情况直接预处理到根的路径长度就可以了，考虑第二种。很自然的，第二种情况可以分为三段计算。第一段跟第一种情况一样算，第三段差不多，换一下边权即可。剩下的就是要处理从一个点出发，上 $k$ 节课后回到这个点的最短时间。这个做一遍多源 dijkstra 就可以了，一开始把所有可以上课的点入队。但是我们不知道要上几节课。其实，最多上 $\log V$ 次课后所有的边权就变成 $1$ 了，所以暴力枚举就行。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10,INF=1e12;
typedef pair<int,int> pii;
int T,n,q,m;
int h[N],to[N<<1],nxt[N<<1],edge[N<<1],idx;
int d[N],disk[N],ans[N],improve[N],dep[N],fa[N][20],f[N][20],g[N][20];
bool vis[N];
int x[N],y[N],lc[N]; 
char sta[N];
inline void add(int a,int b,int c)
{
    to[++idx]=b;
    nxt[idx]=h[a];
    edge[idx]=c;
    h[a]=idx;
}
inline void dfs1(int u,int fath) 
{
    dep[u]=dep[fath]+1;
    fa[u][0]=fath;
    for (int i=1;i<=17;++i) fa[u][i]=fa[fa[u][i-1]][i-1];
    for (int i=h[u];i;i=nxt[i]) 
    {
        int v=to[i];
        if (v^fath) 
        {
            d[v]=d[u]+edge[i];
            dfs1(v,u);
        }
    }
}
inline void dfs2(int u,int fath,int div) 
{
    f[u][0]=improve[u]+disk[u]-d[u];
    g[u][0]=improve[u]+d[u]-disk[u];
    for (int i=1;i<=17;++i) 
    {
        f[u][i]=min(f[u][i-1],f[fa[u][i-1]][i-1]);
        g[u][i]=min(g[u][i-1],g[fa[u][i-1]][i-1]);
    }
    for (int i=h[u];i;i=nxt[i])
    {
        int v=to[i];
        if (v^fath) 
        {
            disk[v]=disk[u]+(edge[i]-1)/div+1;
            dfs2(v,u,div);
        }
    }
}
inline int lca(int u, int v) 
{
    if (dep[u]<dep[v]) swap(u,v);
    for (int i=17;i>=0;--i) if (dep[fa[u][i]]>=dep[v]) u=fa[u][i];
    if (u==v) return u;
    for (int i=17;i>=0;--i) if (fa[u][i]^fa[v][i]) u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
inline void dijkstra(int div) 
{
	priority_queue<pii,vector<pii>,greater<pii>> q;
    for (int i=1;i<=n;++i) 
    {
		improve[i]=INF,vis[i]=false;
        if (sta[i]=='1') q.push({improve[i]=0,i});
    }
    while (!q.empty()) 
    {
        int u=q.top().second; 
        q.pop();
        if (vis[u]) continue; 
        vis[u]=true;
        for (int i=h[u];i;i=nxt[i]) 
        {
            int v=to[i];
            if (improve[v]>improve[u]+edge[i]+(edge[i]-1)/div+1)
            {
                improve[v]=improve[u]+edge[i]+(edge[i]-1)/div+1;
                q.push({improve[v],v});
            }
        }
    }
}
signed main() 
{
    scanf("%lld",&T);
    while (T--)
    {
        idx=0;
        memset(h,0,sizeof h);
        scanf("%lld%lld",&n,&m);
        for (int i=1;i<n;++i)
        {
            int u,v,w;
            scanf("%lld%lld%lld",&u,&v,&w);
            add(u,v,w),add(v,u,w);
        }
        scanf("%s",sta+1);
        dfs1(1,0);
        scanf("%lld",&q);
        for (int i=1;i<=q;++i) scanf("%lld%lld",&x[i],&y[i]),lc[i]=lca(x[i],y[i]);
        for (int i=1;i<=q;++i) ans[i]=d[x[i]]+d[y[i]]-2*d[lc[i]];
        for (int k=1,aby=2;k<=20;++k,aby<<=1) 
        {
            dijkstra(aby);
            dfs2(1,0,aby);
            for (int i=1;i<=q;++i) 
            {
                int cx=x[i],cy=y[i],res=INF;
                int add=d[x[i]]+disk[y[i]]-2*disk[lc[i]];
                for (int j=17;j>=0;--j)
                {
                    if (fa[cx][j]&&dep[fa[cx][j]]+1>=dep[lc[i]])
                    {
                        res=min(res,f[cx][j]+add);
                        cx=fa[cx][j];
                    }
                }
                add=d[x[i]]+disk[y[i]]-2*d[lc[i]];
                for (int j=17;j>=0;--j)
                {
                    if (fa[cy][j]&&dep[fa[cy][j]]+1>=dep[lc[i]])
                    {
                        res=min(res,g[cy][j]+add);
                        cy=fa[cy][j];
                    }       
                }
                res=min(res,g[lc[i]][0]+add);
                ans[i]=min(ans[i],res+k*m);
            }
        }
        for (int i=1;i<=q;++i) printf("%lld\n",ans[i]);
    }
    return 0;
}
```


---

## 作者：lzytag (赞：1)

大概是简单树剖题，$3200$ 的评分有一点虚高了。

下文中我们简称值域位 $V$，即 $10^6$。

首先我们发现我们最多学 $\log V$ 次车，且我们只会在经过的第一个学车点把能学的车全部学完。

我们发现我们基本是沿着树上 $x$ 到 $y$ 的路径，我们可以套路树剖，先找到第一个可以学车的点和 $u$，$v$ 的 $lca$ ，然后枚举学几次车，再提前预处理出树上 $\lceil\frac{w_i}{c}\rceil( 0\le c\le\log V)$ 的前缀和即可解决。

但这时我们发现我们可能会为了学车而走向不在我们原来路径上的点，这让我们想起了 CSP-2022 的 T4，我们可以用类似的做法：预处理出对于学 $c (0<c\le\log V)$ 次车，从每个点到最近的学车点往返一趟所需要的时间，可以通过 $\log V$ 次 Dijkstra 算出，最后在树剖的每一个节点上维护走完这一个区间学过 $c$ 此车所需的时间，从左往右走从没学过到学过 $c$ 次车所需的时间，从右往左从没学过到学过 $c$ 此车所用的时间，直接树剖即可。

总复杂度 $O(n\log V\log N)$。

[附上大常数代码](https://codeforces.com/problemset/submission/1859/220369836)。

---

## 作者：daniEl_lElE (赞：1)

这题 3200？

不难发现我们的行程只有两种可能：

* 直接去往终点
* 到一个有驾驶课程的城市，学习 $x$ 节课，去往终点。

第一种是容易计算的，考虑第二种。

我们可以预处理出从每个点 $i$ 开始，走到某个有驾驶课程的城市，学习 $j$ 节课，再回到这个点，至少需要的时间，记为 $t_{i,j}$。

不难发现一次行程一定可以分为以下三个部分。

* 从起点 $u$ 到某个在 $u\rightarrow v$ 路径上的点 $i$；
* 从 $i$ 点走到某个有驾驶课程的城市学习 $j$ 节课再回到 $i$（这个有驾驶课程的城市可以是 $i$）；
* 从 $i$ 走到终点 $v$。

考虑将 $u\rightarrow v$ 的路径分为 $u\rightarrow \operatorname{LCA}(u,v)$，$\operatorname{LCA}(u,v)\rightarrow v$ 两部分。我们希望预处理出来前一部分和后一部分分别 $i$ 在两段上的最小值。

考虑倍增，$f_{i,j,k,0}$ 表示从 $i$ 向上 $2^j$ 步，学习了 $k$ 节课，以 $i$ 为起点 $i$ 向上 $2^j$ 步的点为终点最短时间。不难发现合并两个 $f$ 只需要考虑刚才所说的去驾驶课程的城市的点在前一半还是后一半即可。

然而有的时候我们要需要计算以 $i$ 向上 $2^j$ 步的点为起点以 $i$ 为终点的答案，用另一个倍增数组 $f_{i,j,k,1}$ 预处理即可。

容易发现这样做空间会爆，考虑将问题离线对于每个 $k$ 分别对每个询问回答即可。复杂度是 $O(n\log n\log w)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
struct qry{
	int a,b;
}p[100005];
vector<pair<int,int>> vc[100005];
int f[100005][18],clz[100005],len[100005],nlen[100005],dep[100005],minv1[100005][18],minv2[100005][18],tag,trn[100005],ans[100005],up[100005];
void dfs0(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=1;i<=17;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		len[v.first]=len[now]+v.second;
		up[v.first]=v.second;
		dfs0(v.first,now);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=17;i>=0;i--) if(dep[f[u][i]]>=dep[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=17;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int qlen(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	int ans=0;
	for(int i=17;i>=0;i--) if(dep[f[u][i]]>=dep[v]) ans+=len[u]-len[f[u][i]],u=f[u][i];
	if(u==v) return ans;
	for(int i=17;i>=0;i--) if(f[u][i]!=f[v][i]) ans+=len[u]-len[f[u][i]]+len[v]-len[f[v][i]],u=f[u][i],v=f[v][i];
	return ans+len[u]-len[f[u][0]]+len[v]-len[f[v][0]];
}
void dfs1(int now,int fa){
	clz[now]=1e18;
	if(trn[now]) clz[now]=0;
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		nlen[v.first]=nlen[now]+(v.second+(1<<tag)-1)/(1<<tag);
		dfs1(v.first,now);
		clz[now]=min(clz[now],clz[v.first]+v.second+(v.second+(1<<tag)-1)/(1<<tag));
	}
}
void dfs2(int now,int fa){
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		clz[v.first]=min(clz[v.first],clz[now]+v.second+(v.second+(1<<tag)-1)/(1<<tag));
		dfs2(v.first,now);
	}
}
void dfs3(int now,int fa){
	minv1[now][0]=min(clz[now]+up[now],clz[f[now][0]]+(up[now]+(1<<tag)-1)/(1<<tag)),minv2[now][0]=min(clz[now]+(up[now]+(1<<tag)-1)/(1<<tag),clz[f[now][0]]+up[now]);
	for(int j=1;j<=17;j++){
		minv1[now][j]=min(minv1[now][j-1]+len[f[now][j-1]]-len[f[now][j]],minv1[f[now][j-1]][j-1]+nlen[now]-nlen[f[now][j-1]]);
		minv2[now][j]=min(minv2[now][j-1]+nlen[f[now][j-1]]-nlen[f[now][j]],minv2[f[now][j-1]][j-1]+len[now]-len[f[now][j-1]]);
//		if(j<=3) cout<<minv1[now][j]<<" "<<minv2[now][j]<<"  ";
	}
//	cout<<now<<"\n";
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs3(v.first,now);
	} 
}
signed main(){
    ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--){
		int n,T; cin>>n>>T;
		for(int i=1;i<=n;i++) vc[i].clear();
		for(int i=1;i<n;i++){
			int u,v,w; cin>>u>>v>>w;
			vc[u].push_back(make_pair(v,w));
			vc[v].push_back(make_pair(u,w));
		}
		char c; for(int i=1;i<=n;i++) cin>>c,trn[i]=(c=='1');
		dfs0(1,0);
		int q; cin>>q;
		for(int i=1;i<=q;i++){
			cin>>p[i].a>>p[i].b;
			ans[i]=qlen(p[i].a,p[i].b);
		}
		for(tag=1;tag<=20;tag++){
			dfs1(1,0);
			dfs2(1,0);
			dfs3(1,0);
			for(int i=1;i<=q;i++){
				int L=lca(p[i].a,p[i].b);
				int now;
				if(L==p[i].a){
					int mv1=1e18; now=p[i].b;
					for(int j=17;j>=0;j--){
						if(dep[f[now][j]]>=dep[p[i].a]){
							mv1=min(mv1+len[now]-len[f[now][j]],minv1[now][j]+nlen[p[i].b]-nlen[now]);
							now=f[now][j];
						}
					}
					ans[i]=min(ans[i],mv1+T*tag);
//					cout<<mv1<<"\n";
				}
				else if(L==p[i].b){
					int mv2=1e18; now=p[i].a;
					for(int j=17;j>=0;j--){
						if(dep[f[now][j]]>=dep[p[i].b]){
							mv2=min(mv2+nlen[now]-nlen[f[now][j]],minv2[now][j]+len[p[i].a]-len[now]);
							now=f[now][j];
						}
					}
					ans[i]=min(ans[i],mv2+T*tag);
				}
				else{
					int mv1=1e18; now=p[i].b;
					for(int j=17;j>=0;j--){
						if(dep[f[now][j]]>=dep[L]){
							mv1=min(mv1+len[now]-len[f[now][j]],minv1[now][j]+nlen[p[i].b]-nlen[now]);
							now=f[now][j];
						}
					}
					ans[i]=min(ans[i],mv1+T*tag+len[p[i].a]-len[L]);
					int mv2=1e18; now=p[i].a;
					for(int j=17;j>=0;j--){
						if(dep[f[now][j]]>=dep[L]){
							mv2=min(mv2+nlen[now]-nlen[f[now][j]],minv2[now][j]+len[p[i].a]-len[now]);
							now=f[now][j];
						}
					}
//					cout<<mv1<<" "<<mv2<<"\n";
					ans[i]=min(ans[i],mv2+T*tag+nlen[p[i].b]-nlen[L]);
				}
			}
		}
		for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
	}
	return 0;
}

```

---

## 作者：TallBanana (赞：0)

感觉没有 3200。我都能想出来。

首先如果你要参加课程，那么你一定是在只会一个节点学习。否则不优。

那么我们走的路大概张这样：![](https://cdn.luogu.com.cn/upload/image_hosting/mx1bm7xp.png)

其中 $u,v$ 是询问给出的节点，$x$ 是 $u,v$ 上的一个分界点，$y$ 是我们去参加课程的那个节点。我们的路径是 $u\xrightarrow{dis_0(u,x)}x\xrightarrow{dis_0(x,y)}y\xrightarrow{dis_i(x,y)}x\xrightarrow{dis_i(x,v)}$。

其中 $dis_i(u,v)$ 表示当 $c=2^i$ 的时候，$u\rightarrow v$ 的距离。

我们可以**枚举参加课程次数 $i$**，再枚举 $x$，$x\xrightarrow{dis_0(x,y)}y\xrightarrow{dis_i(x,y)}x$ 的这段贡献可以变成一个固定的数 $f_{i,x}$。

那答案是 $\min_x dis_0(u,x)+f_{i,x}+dis_i(x,v)$，那么我们可以通过倍增维护这个东西。注意维护两个方向的值。

那么我们如何解决 $f_{i,x}$ 是多少的问题呢？我们可以把这个东西定义为 $\min_y dis_0(x,y)+dis_i(x,y)$。那你发现这个东西不受 $u,v$ 的影响，因为如果走回头路了，就会不优，然后被其他更优的值代替掉。

细节：
* 把每个 $i$ 都独立做一遍，这样不仅省空间，还写起来没有那么臭。
* 注意不参加课程的情况。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL N=1e5+10,inf=1e16;
LL n,T,q,tot,dfn[N],f[N][17],g[N][17],val[2][N][17];
LL zxz[N],dep[N],F[N],G[N],ans[N];
LL a[N],b[N],lv;
char s[N];
vector<PII> e[N];
LL W(LL w) { return (w>>lv)+((w&(1<<lv)-1)>0); }
void dfs1(LL u,LL fa)
{
	f[u][0]=fa; dfn[u]=++tot;
	for(int i=1;i<=16;i++) f[u][i]=f[f[u][i-1]][i-1];
	F[u]=G[u]=inf;
	for(auto i:e[u])
	{
		LL v=i.first,w=i.second;
		if(v==fa) continue;
		zxz[v]=zxz[u]+w;
		dep[v]=dep[u]+W(w);
		dfs1(v,u);
		F[u]=min(F[u],F[v]+w+W(w));
	}
	if(s[u]=='1') F[u]=G[u]=lv*T;
}
void dfs2(LL u,LL fa)
{
	LL res=G[u];
	for(auto i:e[u])
	{
		LL v=i.first,w=i.second;
		if(v==fa) continue;
		res=min(res,F[v]+w+W(w));
	}
	for(auto i:e[u])
	{
		LL v=i.first,w=i.second;
		if(v==fa) continue;
		G[v]=min(G[v],res+w+W(w));
		dfs2(v,u);
	}
	F[u]=min(F[u],G[u]);
}
void dfs3(LL u,LL fa)
{
	val[0][u][0]=val[1][u][0]=F[u];
	g[u][0]=u;
	for(int i=1,v=u;i<=16;i++)
	{
		val[0][u][i]=min(val[0][u][i-1]+zxz[v]-zxz[f[v][i-1]],val[0][f[u][i-1]][i-1]+dep[u]-dep[f[u][i-1]]);
		val[1][u][i]=min(val[1][u][i-1]+dep[v]-dep[f[v][i-1]],val[1][f[u][i-1]][i-1]+zxz[u]-zxz[f[u][i-1]]);
		v=f[v][i-1]; g[u][i]=v;
	}
	for(auto i:e[u])
	{
		LL v=i.first,w=i.second;
		if(v==fa) continue;
		dfs3(v,u);
	}
}
LL LCA(LL u,LL v)
{
	if(u==v) return u;
	if(dfn[u]>dfn[v]) swap(u,v);
	for(int i=16;i>=0;i--)
		if(dfn[f[v][i]]>dfn[u])
			v=f[v][i];
	return f[v][0];
}
void solve()
{
	scanf("%lld%lld",&n,&T);
	for(int i=1;i<n;i++)
	{
		LL u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	scanf("%s%lld",s+1,&q);
	for(int i=1;i<=q;i++) scanf("%lld%lld",a+i,b+i),ans[i]=inf;
	for(lv=0;lv<=20;lv++)
	{
		dfs1(1,0); dfs2(1,0); dfs3(1,0);
		for(int i=1;i<=q;i++)
		{
			LL u=a[i],v=b[i],t=LCA(u,v);
			LL lenA=zxz[u]-zxz[t];
			LL lenB=dep[v]-dep[t];
			LL o=u; ans[i]=min(ans[i],zxz[u]+zxz[v]-2*zxz[t]);
			for(int j=16;j>=0;j--)
			{
				if(dfn[g[o][j]]>=dfn[t])
				{
					ans[i]=min(ans[i],val[1][o][j]+zxz[u]-zxz[o]+dep[g[o][j]]-dep[t]+lenB);
					o=f[o][j];
				}
			}
			o=v;
			for(int j=16;j>=0;j--)
			{
				if(dfn[g[o][j]]>=dfn[t])
				{
					ans[i]=min(ans[i],val[0][o][j]+dep[v]-dep[o]+zxz[g[o][j]]-zxz[t]+lenA);
					o=f[o][j];
				}
			}
		}
	}
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
	tot=0;
	for(int i=1;i<=n;i++) e[i].clear();
}
int main()
{
	LL t; scanf("%lld",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

对于当前速度为 $c=2^k$，在任意两点 $u,v$之间移动所需时间，把这个值设为 $dis_{u,v,k}$。我们首先可以倍增预处理一个点到他所有 $2$ 的整数次方的父亲，然后在 $k$ 
的时间内求出 $dis_{u,v,k}$。如果我们的路径不是从 $u$ 直达 $v$，那么一定是从某个点离开路径练车，再由这个点返回路径。

出发点为 $u$，终点为 $v$，假设我们从点 $x$
离开路径，在 $y$
练车，我们所需要的时间就是 $\min^{20}_{i=1}(dis_{u,x,0}+dis_{x,y,0}+dis_{y,x,i}+dis_{x,v,i}+Ti)$ $\text{or}$ $dis_{u,v,0}$。

后者我们可以直接求出，前者我们先用 ```BFS``` 维护出每个点 $x$ 往一个点练车 $i$ 次然后回到该点的最小时间，把这个值设为 $diss_{x,i}$。

可以对倍增中的每个区间 $x$ 到他的往上第 $2^y$
个父亲，维护出：
- $dis1_{x,y,i}=$ 从 $x$
出发，练了 $0$
次车，最后到达父亲 $y$，练了 $i$
次车的最小时间
- $dis2_{x,y,i}=$ 从 $x$
的父亲 $y$
出发，练了 $0$
次车，最后到达 $x$，练了 $i$
次车的最小时间 $dis1_{x,0,i}=dis2_{x,0,i}=diss_{x,i}$。

然后对每个区间都按照这个求一遍最小的距离，一定包含最优解
开 ```long long```
会 ```MLE```，每个区间的答案对 $2 \times 10^9$ 取，时间复杂度 $n\log^3n$。进行前缀和优化可以达到 $n\log^2n$。


---

## 作者：Zimo_666 (赞：0)

## F. Teleportation in Byteland

第一个 *3200。

### Statement

比特兰有 $ n $ 个城市，其中一些城市由道路连接，道路可以双向通行。第 $ i $ 条道路有其自身的难度参数 $ w_i $。以难度为 $ w_i $ 的道路上的通行时间为 $ \lceil\frac{w_i}{c}\rceil $，其中 $ c $ 是当前驾驶技能。

比特兰的旅行网络是一棵树。换句话说，在任意两个城市之间，最多只有一条经过每个城市的路径。

在一些城市中，您可以参加驾驶课程。完成单个课程需要 $ T $ 时间，并且完成课程后驾驶员的技能 $ c $ 翻倍。请注意，完成课程所需的时间 $ T $ 在所有城市中是相同的，并且可以在同一个城市中多次完成课程。

您需要回答 $ q $ 个查询：如果您从技能 $ c = 1 $ 开始旅行，从城市 $ a $ 到城市 $ b $ 所需的最短时间是多少？

### Solution

首先，经过 $\log$ 次学习之后肯定是无效的，而且我们对于一次询问 $u\to v$，我们策略要么是不学习，要么就是 $u\to v$ 路径上某个点 $x$  一次性学习 $K(K<\log)$ 次，然后从 $x$ 走到 $v$。

我们设 $f_{x,k}$ 表示从 $x$ 走到某个距离它最近的可以学习的点经过 $k$ 次学习之后再走回来的最近距离。

设 $g_{x,k}$ 表示路径经过 $k$ 次学习之后，从 $x$ 走到根的最短距离，特别的 $dis_{x}=g_{x,0}$。

将询问离线下来，然后考虑枚举学习次数，每个次数分别处理每个询问。

考虑答案会是什么样子的，如果什么也不学，那么答案就是 $dis_x+dis_y-2\times dis_{lca(x,y)}$。

如果从 $x\to lca(x,y)$ 路径上一点 $v$ 出发去某个点学习，那么答案就是 $dis_x+g_{y,k}-2\times g_{lca(x,y),k}+f_v-dis_v+g_{i,k}+m\times k$。

如果从 $lca(x,y)\to y$ 路径上一点 $v$ 出发去某个点学习，那么答案就是 $dis_x+g_{y,k}-2\times dis_{lca(x,y)}+f_v+dis_v-g_{i,k}+m\times k$。

其中 $f_v-dis_v+g_{i,k}$ 和 $f_v+dis_v-g{i,k}$ 可以用树剖+ST 表维护路径上的最小值，复杂度 $\log$。

$f_{x,k}$ 可以用 Dijkstra 最短路，开始先把所有特殊点丢进优先队列中，其中对于每次每次枚举的学习次数，分别处理边权即可。

代码还是比较好写的，注意一些细节比如枚举学习次数的上限是 $\log \max w$，最大值要 $10^{18}$，对于不需要加减的最大值可以赋 `Long_Long_Max`，树剖的东西要每次清空，LCA 不要写挂诸如此类的。

还是比较好实现的，具体可以看看代码。

[Code](https://codeforces.com/contest/1859/submission/229940373)



---

