# Tree Queries

## 题目描述

You are given a tree consisting of $ n $ vertices. Recall that a tree is an undirected connected acyclic graph. The given tree is rooted at the vertex $ 1 $ .

You have to process $ q $ queries. In each query, you are given a vertex of the tree $ v $ and an integer $ k $ .

To process a query, you may delete any vertices from the tree in any order, except for the root and the vertex $ v $ . When a vertex is deleted, its children become the children of its parent. You have to process a query in such a way that maximizes the value of $ c(v) - m \cdot k $ (where $ c(v) $ is the resulting number of children of the vertex $ v $ , and $ m $ is the number of vertices you have deleted). Print the maximum possible value you can obtain.

The queries are independent: the changes you make to the tree while processing a query don't affect the tree in other queries.

## 说明/提示

The tree in the first example is shown in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1606F/193f000b14e337dd1e2d7be04d2ba07cfa4b60f5.png)Answers to the queries are obtained as follows:

1. $ v=1,k=0 $ : you can delete vertices $ 7 $ and $ 3 $ , so the vertex $ 1 $ has $ 5 $ children (vertices $ 2 $ , $ 4 $ , $ 5 $ , $ 6 $ , and $ 8 $ ), and the score is $ 5 - 2 \cdot 0 = 5 $ ;
2. $ v=1,k=2 $ : you can delete the vertex $ 7 $ , so the vertex $ 1 $ has $ 4 $ children (vertices $ 3 $ , $ 4 $ , $ 5 $ , and $ 6 $ ), and the score is $ 4 - 1 \cdot 2 = 2 $ .
3. $ v=1,k=3 $ : you shouldn't delete any vertices, so the vertex $ 1 $ has only one child (vertex $ 7 $ ), and the score is $ 1 - 0 \cdot 3 = 1 $ ;
4. $ v=7,k=1 $ : you can delete the vertex $ 3 $ , so the vertex $ 7 $ has $ 5 $ children (vertices $ 2 $ , $ 4 $ , $ 5 $ , $ 6 $ , and $ 8 $ ), and the score is $ 5 - 1 \cdot 1 = 4 $ ;
5. $ v=5,k=0 $ : no matter what you do, the vertex $ 5 $ will have no children, so the score is $ 0 $ ;
6. $ v=7,k=200000 $ : you shouldn't delete any vertices, so the vertex $ 7 $ has $ 4 $ children (vertices $ 3 $ , $ 4 $ , $ 5 $ , and $ 6 $ ), and the score is $ 4 - 0 \cdot 200000 = 4 $ .

## 样例 #1

### 输入

```
8
6 7
3 2
8 3
5 7
7 4
7 1
7 3
6
1 0
1 2
1 3
7 1
5 0
7 200000```

### 输出

```
5
2
1
4
0
4```

# 题解

## 作者：帽子 (赞：15)

分享一个大概是最快也是最好写的做法吧，是一位红名大哥在评论区提到的，不过他没有详细说明。

令 $dp[u][k]$ 为询问 $(u, k)$ 的答案，那么有 $dp[u][k] = \sum \limits_{v \in son(u)} \max(1, dp[v][k] - k)$

显然 $dp[u][k] \ge |son(u)|$，但是仔细想想 $k$ 很大的时候大多数点好像都会取到等号，所以可以只计算取到大于号的 $dp$, 剩下的都用 $|son(u)|$ 代替。

事实上最多只有 $O(n \log n)$ 对 $(u, k)$ 会取到大于号。为了证明这个结论，我们考虑一个固定的 $k$ 最多能有多少 $u$ 取到大于号。

对于某棵树，考虑取到大于号的最深的点 $v$, 显然它有一个儿子 $w$ 满足 $|son(w)| \gt k + 1$。如果它有不止一个儿子，我们可以只保留一个，把其他所有的点都变成保留下来的那个儿子的儿子，而 $dp[v][k]$ 不减。

接下来考虑 $v$ 的父亲 $p$。这里 $p$ 可能还有一些取到大于号的儿子，我们把除了 $v$ 之外的子树中，取到大于号的点塞到 $p$ 和 $v$ 之间，取到等于号的点塞到 $w$ 下面，这个过程中取到大于号的点的数量不减，$dp[p][k]$ 也不减。

重复这个过程，我们就把任意一棵树变成了一个扫把型，从 $1$ 到 $w$ 构成一条链，所有的叶子都接在 $w$ 上。在这个过程中，取到大于号的 $u$ 不减，因此我们证明了这样的形状能使 $u$ 的数量最大。

现在我们可以轻松求出有多少点取到大于号。假设叶子数量是 $m$, 那么 $dp[v][k] = m - k, dp[fa(v)][k] = m - 2k, ...$ ，而每个点的 $son$ 都为 $1$, 所以最多有 $\frac m k \lt \frac n k$ 个点取得大于号。对所有的 $k$ 求和就可以得到满足条件的 $(u, k)$ 只有 $O(n \log n)$ 对。

证明完这个结论之后，我们只需要按照上面的式子记忆化搜索即可，然后每次只把 $\gt k+1$ 的 $dp$ 值传给父亲。


```cpp
#include<bits/stdc++.h>
#define sz(x) int(x.size())
#define endl '\n'
using namespace std;
typedef long long ll;
typedef vector<int> VI;

const int maxn = 2e5 + 5;

VI dp[maxn];
VI ans[maxn];
VI g[maxn];
int son[maxn];

void dfs(int u, int f)
{
    son[u] = sz(g[u]) - (u != 1);
    int sz = son[u];
    for(int v : g[u])
    {
        if(v == f) continue;
        dfs(v, u);
        sz = max(sz, sz(dp[v]));
    }
    dp[u].resize(sz);
    VI add(sz + 1);
    for(int v : g[u])
    {
        if(v == f) continue;
        for(int i = 0; i < sz(dp[v]); i++)
            dp[u][i] += dp[v][i] - i;
        add[sz(dp[v])]++;
    }
    for(int i = 0; i < sz; i++)
    {
        if(i) add[i] += add[i - 1];
        dp[u][i] += add[i];
    }
    ans[u] = dp[u];
    while(sz(dp[u]) && dp[u].back() <= sz(dp[u]))
        dp[u].pop_back(); 
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    int q;
    cin >> q;
    while(q--)
    {
        int u, k;
        cin >> u >> k;
        if(k >= sz(ans[u]))
            cout << son[u] << endl;
        else
            cout << ans[u][k] << endl;
    }
}
```


---

## 作者：juicyyou (赞：14)

根号算法万岁！

和 longer_name 神仙一起整的根号算法（（

首先注意到答案一定非负，那么对于一个 $k$ 的 $m$ 最大是 $\frac{n}{k}$ 的，于是我们不妨考虑根号分治

考虑当 $k < \sqrt{n}$ 时，我们直接进行树上 DP，设 $f_{i,j}$ 表示 $i$ 的子树里当 $k = j$ 时的答案，那么转移的时候我们直接考虑当前子节点删不删，这样这部分复杂度就是 $\mathcal O(n \sqrt{n})$ 的

然后考虑当 $k \ge \sqrt{n}$ 的时候，一定有 $m \le \sqrt{n}$，这样的话考虑树形背包，记 $g_{i, j}$ 表示 $i$ 子树里删 $j$ 个点的最大儿子数，这样进行树形背包，考虑每个儿子删不删，由于树形背包的复杂度是 $\mathcal O(n k)$ 的，所以这部分复杂度就是 $\mathcal O(n \sqrt{n})$

那么这个题时限 6s，你就可以过了！

不过如果直接这么做空间会萎，于是你把询问离线下来，分成两部分做就卡进 ML 了

跑的非常的快

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5 + 5;
const ll maxv = 2e5;
const ll B = 450;
ll n, q;
vector<ll> adj[maxn];
int f[maxn][B + 2];
vector<pair<pair<ll, ll>, ll>> op[2];
ll num[maxn];
void dfs1(ll now, ll fa){
    // ll num = (int)(adj[now].size()) - (now != 1);
    for(auto t : adj[now]){
        if(t == fa) continue;
        dfs1(t, now);
        for(int j = 0;j <= B;j++){
            f[now][j] = max(f[now][j] + 1, f[now][j] - j + f[t][j]);
        }
    }
    return ;
}
ll sz[maxn];
int g[B + 5];
void dfs2(ll now, ll fa){
    memset(f[now], -0x3f, sizeof(f[now]));
    memset(g, -0x3f, sizeof(g));
    sz[now] = 1;
    f[now][0] = 0;
    for(auto t : adj[now]){
        if(t == fa) continue;
        dfs2(t, now);
        for(int i = 0;i <= sz[now] && i <= B;i++){
            for(int j = 0;j <= sz[t] && j + i <= B;j++){
                g[i + j] = max(g[i + j], f[now][i] + 1);
                g[i + j + 1] = max(g[i + j + 1], f[now][i] + f[t][j]);
            }
        }
        sz[now] += sz[t];
        for(int i = 0;i <= sz[now] && i <= B;i++){
            f[now][i] = g[i]; g[i] = -0x3f3f3f3f;
        }
    }
    return ;
}
ll ans[maxn];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1;i < n;i++){
        ll ux, vx; cin >> ux >> vx; adj[ux].push_back(vx);
        adj[vx].push_back(ux);
    }
    cin >> q;
    for(int i = 1;i <= q;i++){
        ll ux, kx; cin >> ux >> kx;
        if(kx > B) op[1].emplace_back(make_pair(ux, kx), i);
        else op[0].emplace_back(make_pair(ux, kx), i);
    }
    dfs1(1, 0);
    for(auto fr : op[0]){
        ll t = fr.first.first, vv = fr.first.second;
        ll id = fr.second;
        ans[id] = f[t][vv];
    }
    dfs2(1, 0);
    for(auto fr : op[1]){
        ll t = fr.first.first, vv = fr.first.second;
        ll id = fr.second;
        for(int j = 0;j <= B;j++){
            // cout << f[t][j] - vv * j << " \n"[j == B];
            ans[id] = max(ans[id], (ll)f[t][j] - vv * j);
        }
        // cout << id << " " << ans[id] << endl;
    }
    for(int i = 1;i <= q;i++) cout << ans[i] << "\n";
    cout.flush(); return 0;
}

```

---

## 作者：Cry_For_theMoon (赞：11)

[传送门](https://codeforces.com/contest/1606/problem/F)

神题啊...

首先，对于一次以 $r$ 为根的询问我们忽略 $r$ 子树以外的所有节点去考虑。

然后，发现如果我们一开始把 $r$ 删除了，输出答案的时候再加回去，那么删除的点是 $r$ 子树内一个包含 $r$ 的连通块。

考虑树形 $dp$。容易对于每次询问，设计出这样一个转移：

$$f(u)=-k+\sum_{u\rightarrow v}\max\{1,f(v)\}$$

其中 $k$ 是单次询问给定的参数 $k$。

这样就有了一个 $O(nm)$ 的暴力解法。

考虑如果忽略掉和 $1$ 去取 $\max$ ，这东西实际上是 $f(u)=-k\,\times\,sz_u$，其中 $sz$ 代表子树大小。所以就尝试去掉 $\max$。我们记 $a_u$ 为 $u$ 的儿子个数，不难得到：

$$f(u)=a_u-k+\sum_{u\rightarrow v}\max\{0,f(v)-1\}$$

如果一个儿子 $v$ 满足 $f(v)\lt 1$ 我们可以忽略它和父亲的边，因为其贡献为 $0$。这样会形成一个新的树（森林）结构。在这个结构上，$dp$ 方程可以简化为：

$$f(u)=a_u-k+\sum_{u\rightarrow v}(f(v)-1)$$

记 $sum_u$ 为 $u$ 子树内 $a$ 之和，我们得到：

$$f(u)=sum_u-k\,\times\,sz_u-sz_u+1$$

也就是说如果我们能维护这个新森林每个点的 $sum$ 和 $sz$ 就可以直接利用它们计算答案。发现关键是 $f\ge 1$。

不难发现 $f$ 满足单调递减性质。换言之一个点 $u$ 到 $fa_u$ 的连边最初被忽略，同时存在一个 $lim$，使得 $k\ge lim$ 的时候这条边存在（即 $f(u)\ge 1$，否则被忽略。）

解不等式 $sum_u-lim\,\times\,sz_u-sz_u\ge 0$ 可以得到 

$$lim\le \lfloor \frac{sum_u-sz_u}{sz_u} \rfloor$$

右侧的值就是它的上界。

所以我们把 $q$ 个询问按照 $k$ 降序排序，每次处理所有未和父亲连边的，且 $lim\ge k$ 的点。但是注意 $lim_u$ 可能会因为 $u$ 子树内发生了合并而产生变化，所以我们需要考虑产生修改的 $lim$ 还有快速修改 $sz$ 和 $sum$ 值。

首先发现已经合并过的点不需要考虑 $lim$ 了，所以可以并查集维护每个点往上第一个未向上合并的祖先 $top$，只有这个点的 $lim$ 会改变。

发现一个点 $u$ 和父亲合并后只会影响其一段祖先（不超过 $top$，因为 $top$ 和它父亲还没有连边过）的 $sz$ 和 $sum$。这个东西可以转为 $dfs$ 序上单点修改区间求和的问题。利用树状数组可以解决。

总复杂度 $O((n+q)\log n)$。 CF上时限 6s 但是本方法大常数也不会超过 1s，难道是最后一部分放了树剖过去（雾）。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
int n,q,f[MAXN];
int L[MAXN],R[MAXN],tot;
ll sum[MAXN],sz[MAXN];
int fa[MAXN],vis[MAXN];
vector<int>e[MAXN];
struct Qry{
	int v,k,idx;ll ans;
}qry[MAXN];
struct BIT{
	ll tree[MAXN];
	void update(int x,ll val){for(;x<=n;x+=lowbit(x))tree[x]+=val;}
	ll query(int x){ll ret=0;for(;x;x-=lowbit(x))ret+=tree[x];return ret;}
	ll query(int L,int R){return query(R)-query(L-1);}
}t1,t2; 
struct Node{
	ll val;int idx;
	bool operator<(const Node& n2)const{return val<n2.val;}
};
priority_queue<Node>pq;
bool cmp1(const Qry& q1,const Qry& q2){return q1.k>q2.k;}
bool cmp2(const Qry& q1,const Qry& q2){return q1.idx<q2.idx;}
int Find(int x){
	if(fa[x]==x)return x;
	return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){if(Find(x)==Find(y))return;fa[Find(x)]=Find(y);}
ll D(ll x,ll y){if(y<0)x=-x,y=-y;return (x<0)?(-((-x+y-1)/y)):(x/y);}
void dfs(int u){
	L[u]=++tot;
	for(auto v:e[u]){if(v==f[u])continue;
		f[v]=u;dfs(v);sum[u]++;
	}
	R[u]=tot;
}
void solve(){
	dfs(1);
	rep(i,1,n){fa[i]=i;sz[i]=1;}
	rep(i,1,n){pq.push((Node){D(sum[i]-sz[i],sz[i]),i});}
	rep(i,1,q){
		Qry& now=qry[i];
		while(pq.size()){
			Node cur=pq.top();if(cur.val<now.k)break;
			pq.pop();
			if(vis[cur.idx])continue;
			vis[cur.idx]=1;
			if(cur.idx==1)continue;
			Merge(cur.idx,f[cur.idx]);
			int top=Find(cur.idx);
			ll nsz=sz[cur.idx]+t1.query(L[cur.idx],R[cur.idx]);
			ll nsum=sum[cur.idx]+t2.query(L[cur.idx],R[cur.idx]);
			t1.update(L[f[cur.idx]],nsz);
			if(f[top])t1.update(L[f[top]],-nsz);
			t2.update(L[f[cur.idx]],nsum);
			if(f[top])t2.update(L[f[top]],-nsum);
			if(vis[top])continue;
			nsz=sz[top]+t1.query(L[top],R[top]);
			nsum=sum[top]+t2.query(L[top],R[top]);
			pq.push((Node){D(nsum-nsz,nsz),top});
		}
		int u=now.v;
		ll nsz=sz[u]+t1.query(L[u],R[u]);
		ll nsum=sum[u]+t2.query(L[u],R[u]);
		now.ans=nsum-nsz*now.k+now.k-nsz+1;
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		e[u].pb(v);e[v].pb(u);
	}
	scanf("%d",&q);
	rep(i,1,q){
		scanf("%d%d",&qry[i].v,&qry[i].k);
		qry[i].idx=i;
	}
	sort(qry+1,qry+1+q,cmp1);
	solve();
	sort(qry+1,qry+1+q,cmp2);
	rep(i,1,q){
		printf("%lld\n",qry[i].ans);
	}

	return 0;
}

```

---

## 作者：tzc_wk (赞：5)

[Codeforces 题面传送门](https://codeforces.ml/contest/1606/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1606F)

显然我们选择删除的点连同 $u$ 会形成一个连通块，否则我们如果选择不删除不与 $u$ 在同一连通块中的点，答案一定更优。

注意到如果我们选择删除 $u$ 的某个儿子 $v$，那么答案的增量为 $chd_v-1-k$，其中 $chd_v$ 为节点 $v$ 儿子的个数。而初始时刻答案为 $chd_u$ 是个定值，因此我们的任务可以等效于，给每个点赋上一个点权 $chd_u-1-k$，然后要找到一个以 $u$ 为根的树上连通块，使得这个连通块中除去点 $u$ 之外其他点点权之和尽可能大。

因此我们有了一个复杂度 $\Theta(n^2)$ 的做法：对于每一个 $k$ 都跑一遍树形 $dp$，即设 $dp_u$ 表示以 $u$ 为根的连通块点权之和的最大值，那么显然有转移 $dp_u=chd_u-1-k+\sum\limits_{v\in son_u}\max(dp_v,0)$。注意到我们选出的树上连通块边界上（也就是所有满足 $x$ 在树上连通块中，但 $x$ 的所有儿子都不在树上连通块）中的点的点权必定都是正的，否则我们扣掉那些点权非正且在连通块边界上的点，答案肯定变得更优。因此考虑对于每个 $k$ 将所有点权为正的点拎出来建一棵虚树——由于 $\sum\limits_{i=1}^nchd_i=n-1$，所以对于所有 $k$，点权为正的点的总个数是 $\Theta(n)$ 的，然后对它们跑树形 $dp$，然后每次查询一个点 $u$ 为根的连通块点权之和的最大值时，如果点 $u$ 本身就在虚树上，直接返回 $u$ 的 DP 值即可，否则我们找到 $u$ 在虚树上所在的链下方的节点 $v$——这个可以拿个 `set` 存储所有在虚树上的节点的 DFS 序，然后直接在 `set` 中 `lower_bound`。那么以 $u$ 为根的连通块点权和的最大值就是 $dp_v$ 加上 $fa_v\to u$ 这段路径和的点权和。

时间复杂度 $\Theta(n\log n)$​​。

```cpp
const int MAXN=2e5;
const int LOG_N=18;
int n,qu,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int chd[MAXN+5],dep[MAXN+5],fa[MAXN+5][LOG_N+2];
int dfn[MAXN+5],tim=0,rid[MAXN+5],edt[MAXN+5];
void dfs0(int x,int f){
	fa[x][0]=f;rid[dfn[x]=++tim]=x;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		chd[x]++;dep[y]=dep[x]+1;dfs0(y,x);
	} edt[x]=tim;
}
int sum_chd[MAXN+5];
void dfs_chd(int x,int f){
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		sum_chd[y]=sum_chd[x]+chd[y];
		dfs_chd(y,x);
	}
}
void lca_init(){
	dep[1]=1;dfs0(1,0);
	for(int i=1;i<=LOG_N;i++) for(int j=1;j<=n;j++)
		fa[j][i]=fa[fa[j][i-1]][i-1];
}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=LOG_N;~i;i--) if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=LOG_N;~i;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
vector<int> pos[MAXN+5];
int stk[MAXN+5],tp=0;set<int> st;
vector<pii> qv[MAXN+5];
ll calc_sum(int u,int v,int k){//u is ancestor of v
	return (sum_chd[v]-sum_chd[u])-1ll*(k+1)*(dep[v]-dep[u]);
}
int calc_val(int u,int k){return chd[u]-1-k;}
vector<int> g[MAXN+5];
ll dp[MAXN+5],res[MAXN+5];
void insert(int x){
	if(!tp) return stk[++tp]=x,void();
	int lc=getlca(x,stk[tp]);
//	printf("LCA of %d %d is %d\n",x,stk[tp],lc);
//	printf("stack: ");
//	for(int i=1;i<=tp;i++) printf("%d%c",stk[i]," \n"[i==tp]);
	while(tp>1&&dep[stk[tp-1]]>dep[lc]){
//		printf("adde %d %d\n",stk[tp-1],lc);
		g[stk[tp-1]].pb(stk[tp]);--tp;
	}
	if(tp&&dep[stk[tp]]>dep[lc]){
//		printf("adde %d %d\n",lc,stk[tp]);
		g[lc].pb(stk[tp--]);
	}
	if(!tp||stk[tp]!=lc) stk[++tp]=lc;
	stk[++tp]=x;
}
void fin(){
	while(tp>=2){
//		printf("adde %d %d\n",stk[tp-1],stk[tp]);
		g[stk[tp-1]].pb(stk[tp]);--tp;
	} tp=0;
}
void dfs_dp(int x,int k){
	dp[x]=calc_val(x,k);st.insert(dfn[x]);
	for(int y:g[x]){
		dfs_dp(y,k);
		dp[x]+=max(dp[y]+calc_sum(x,y,k)-calc_val(y,k),0ll);
//		printf("calc_sum %d %d %d = %lld\n",x,y,k,calc_sum(x,y,k));
	} //printf("DP %d %lld\n",x,dp[x]);
}
void clr(int x){for(int y:g[x]) clr(y);g[x].clear();}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	lca_init();sum_chd[1]=chd[1];dfs_chd(1,0);scanf("%d",&qu);
//	for(int i=1;i<=n;i++) printf("chd[%d]=%d\n",i,chd[i]);
	for(int i=1;i<=n;i++) for(int j=0;j<chd[i];j++) pos[j].pb(i);
	for(int i=1,u,k;i<=qu;i++) scanf("%d%d",&u,&k),qv[k].pb(mp(u,i));
	for(int i=0;i<=MAXN;i++){
		st.clear();
		if(!pos[i].empty()){
//			printf("solving %d\n",i);
			sort(pos[i].begin(),pos[i].end(),[&](int x,int y){return dfn[x]<dfn[y];});
			if(pos[i][0]!=1) insert(1);
			for(int x:pos[i]) insert(x);
			fin();dfs_dp(1,i);
		}
		for(pii p:qv[i]){
			int u=p.fi,id=p.se;
			set<int>::iterator it=st.lower_bound(dfn[u]);
			if(it==st.end()||(*it)>edt[u]) res[id]=chd[u];
			else{
				int pt=rid[*it];
//				printf("%d %d\n",id,pt);
//				printf("%lld\n",calc_sum(fa[u][0],fa[pt][0],i));
				res[id]=chd[u]+max(0ll,dp[pt]+calc_sum(fa[u][0],fa[pt][0],i)-calc_val(u,i));
			}
		}
		clr(1);
	}
	for(int i=1;i<=qu;i++) printf("%lld\n",res[i]);
	return 0;
}
/*
11
1 2
2 3
2 4
1 5
5 6
5 7
7 8
7 9
7 10
1 11
4
1 0
1 1
5 2
11 0
*/
```



---

## 作者：FjswYuzu (赞：3)

注意到，一棵点数为 $n$ 的子树，最多会操作 $\dfrac{n}{k}$ 次。这个 $\dfrac{n}{k}$ 非常的蹊跷。考虑根号分治。

- $k \leq \sqrt n$：注意到因为 $k$ 的取值只有 $\sqrt n +1$ 个，我们定义 $dp_{i,j}$ 为，结点 $i$ 为根，当 $k=j$ 的时候，最大的答案是多少。在计算 $dp_{u,i}$ 的时候，对于一棵子树，只有要（贡献为 $1$，花费为 $0$）或者不要（贡献为 $dp_{v,i}$，花费为 $i$）两种选择。直接选最大值转移；   
- $k > \sqrt n$：注意上面的过程是，知道 $k$，转移 $c(v) - mk$；这里无法确定 $k$，我们假设知道 $m$，即定义 $dp_{i,j}$ 为，结点 $i$ 为根，已经经过了 $j$ 次操作，$c(v)$ 的最大值。这样就可以表示答案。这个过程类似于树上背包。加上上界优化之后转移时间复杂度 $O(n \sqrt n)$。

然后比较卡空间，数组重复用。结束。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
struct Query{int v,k,ans;}ret[200005];
vector<int> G[200005];
int n,Sqr,dp[200005][455],siz[200005],tmp[455];
void dfs1(int now,int pre)
{
	for(auto st:G[now])
	{
		if(st==pre)	continue;
		dfs1(st,now);
		for(int j=0;j<=Sqr;++j)	dp[now][j]+=max(1,dp[st][j]-j);
	}
}
const int inf=1e9;
void dfs2(int now,int pre)
{
	siz[now]=1;
	for(int i=0;i<=Sqr;++i)	dp[now][i]=-inf;
	dp[now][0]=0;
	for(auto st:G[now])
	{
		if(st==pre)	continue;
		dfs2(st,now);
		for(int i=0;i<=Sqr;++i)	tmp[i]=-inf;
		for(int i=0;i<=min(siz[now],Sqr);++i)	for(int j=0;j<=min(siz[st],Sqr) && i+j<=Sqr;++j)	tmp[i+j]=max(tmp[i+j],dp[now][i]+1),tmp[i+j+1]=max(tmp[i+j+1],dp[now][i]+dp[st][j]);
		memcpy(dp[now],tmp,sizeof tmp);
		siz[now]+=siz[st];
	}
}
int main(){
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	Sqr=sqrt(n);
	int q=read();
	for(int i=1;i<=q;++i)	ret[i].v=read(),ret[i].k=read();
	dfs1(1,0);
	for(int i=1;i<=q;++i)	if(ret[i].k<=Sqr)	ret[i].ans=dp[ret[i].v][ret[i].k];
	dfs2(1,0);
	for(int i=1;i<=q;++i)	if(ret[i].k>Sqr)	for(int j=0;j<=Sqr;++j)	ret[i].ans=max(ret[i].ans,dp[ret[i].v][j]-j*ret[i].k);
	for(int i=1;i<=q;++i)	write(ret[i].ans),puts("");
	return 0;
}
```



---

## 作者：Acee (赞：1)

感觉很可做啊。

这题先转化模型，设 $val_i$ 为 $c_i - 1 - k$，其中 $c_i$ 为他的儿子数量，然后题目就转化为了求子树最大连通块。

然后发现 $k$ 最大只有 $2 \cdot 10^5$，所以可以考虑平衡规划。

但有一种更好想的思路，暴力 DP 显然，写了可发现若 $c_i < k$ 了那就不必要 DP 了，所以就有了关键点，可以建虚树 DP，但复杂度还是接受不了。而 $\sum c_i = n$，所以 $c_i$ 只有 $\sqrt n$ 种，所以每次暴力重构虚树，重新 DP 即可。

时间复杂度 $O(n \sqrt n)$。

代码从 emacs 中拷出来的，缩进有问题就不放代码了。

---

