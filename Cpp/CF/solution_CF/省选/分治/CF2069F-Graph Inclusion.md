# Graph Inclusion

## 题目描述

在无向图中，连通分量（connected component）定义为满足以下条件的顶点集合 $S$：
- 对于 $S$ 中的任意顶点对 $(u, v)$，存在从 $u$ 到 $v$ 的路径；
- 不存在属于 $S$ 外部的顶点与 $S$ 内部的顶点之间存在路径。

例如，下图中的图有三个连通分量：$\{1, 3, 7, 8\}$、$\{2\}$、$\{4, 5, 6\}$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2069F/c7da17be18c82b1f53abfd338e215a533856c956.png)

我们称图 $A$ 包含（include）图 $B$，当且仅当图 $B$ 的每个连通分量都是图 $A$ 某个连通分量的子集。

给定两个图 $A$ 和 $B$，它们均包含 $n$ 个顶点（编号为 $1$ 到 $n$）。初始时两个图都没有边。你需要处理以下两种类型的查询：
- 向其中一个图添加一条边；
- 从其中一个图中删除一条边。

在每次查询后，你需要计算为了使图 $A$ 包含图 $B$ 所需要向图 $A$ 添加的最小边数，并输出该数值。注意这些边不会被实际添加，仅需计算数量。

## 样例 #1

### 输入

```
6 9
A 2 3
B 1 3
A 2 1
A 3 2
B 5 6
A 6 5
A 3 4
A 4 2
A 4 3```

### 输出

```
0
1
0
1
2
1
1
0
1```

# 题解

## 作者：MightZero (赞：4)

### Preface

赛时因为撤销没弹栈导致没过，我是奶龙/ll

### Solution

以下定义 $A_u,B_u$ 分别表示图 $A,B$ 中的编号为 $u$ 的点。

先不考虑删除边的操作，发现直接维护联通块判断 $A$ 要连多少条边才能满足 $B \subseteq A$ 并不好处理，考虑如下转化：

0. 初始情况下答案 $ans=0$；

1. 某个操作为连接 $B_u,B_v$：若 $B_u,B_v$ 已经联通则忽略该操作，否则连接 $B_u,B_v$，同时将 $ans$ 加 $1$；

2. 某个操作为连接 $A_u,A_v$：若 $A_u,A_v$ 已经联通则忽略该操作，否则同时连接 $A_u,A_v$ 和 $B_u,B_v$，若 $B_u,B_v$ 已经联通（必然是在某个操作 $1$ 中联通）则将 $ans$ 减 $1$。

这样做的好处在于任意时刻，实际维护的图 $A,B$ 都满足 $A\subseteq B$，从而转化为动态图连通性问题，可以直接用并查集来维护图的联通块。

接下来考虑删除边的操作，可以把普通并查集换成可撤销并查集来删边。但是注意到给定的加边与删边的操作不一定连续，无法直接撤销，因此需要将询问离线，预处理每条边实际存在的时刻范围，线段树分治即可。

具体实现请看代码，时间复杂度 $O(n\log^2n)$。

### Code

注意直接用 `std::stack` 极大概率会直接 `MLE`；至于具体原因......`std::stack` 的默认容器是 `std::deque`，后面忘了。/qd

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = int;
using pll = pair<ll,ll>;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
struct dsu
{
    vector<ll> fa,sz;
    stack<pll,vector<pll>> ops;
    dsu(){}
    dsu(ll n):fa(vector<ll>(n+2)),sz(vector<ll>(n+2,1))
    {
        iota(fa.begin(),fa.end(),0);
        ops=stack<pll,vector<pll>>{};
    }
    ll find(ll x)
    {
        if(fa[x]==x)return x;
        else return find(fa[x]);
    }
    void merge(ll u,ll v)
    {
        ll fu=find(u),fv=find(v);
        if(fu==fv)
        {
            ops.push({-1,-1});
            return ;
        }
        if(sz[fu]<sz[fv])swap(fu,fv);
        fa[fv]=fu,sz[fu]+=sz[fv];
        ops.push({fu,fv});
    }
    void undo()
    {
        if(!ops.size())return;
        auto [u,v]=ops.top();
        ops.pop();
        if(u==-1)return;
        fa[v]=v,sz[u]-=sz[v];
    }
}dsuA,dsuB;
const ll N=4e5+5;
ll rans=0;
struct sgt
{
    #define L tr[rt].l
    #define R tr[rt].r
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    struct node
    {
        ll l,r;
        vector<tuple<ll,ll,ll>> ops;
        stack<ll,vector<ll>> opps;
    }tr[N<<2];
    ll ans[N];
    void build(ll l,ll r,ll rt)
    {
        L=l,R=r;
        if(l==r)return;
        ll mid=l+r>>1;
        build(l,mid,ls);
        build(mid+1,r,rs);
    }
    void modify(ll l,ll r,const tuple<ll,ll,ll>& x,ll rt)
    {
        if(L>r||l>R)return;
        if(l<=L&&R<=r)return tr[rt].ops.push_back(x);
        modify(l,r,x,ls);
        modify(l,r,x,rs);
    }
    void dfs(ll rt)
    {
        for(auto &[opt,opu,opv]:tr[rt].ops)
        {
            if(opt==1)
            {
                ll fub=dsuB.find(opu),fvb=dsuB.find(opv);
                if(fub^fvb)
                {
                    rans++;
                    tr[rt].opps.push(2);
                }
                dsuB.merge(opu,opv);
                tr[rt].opps.push(1);
            }
            else if(opt==0)
            {
                ll fua=dsuA.find(opu),fva=dsuA.find(opv);
                ll fub=dsuB.find(opu),fvb=dsuB.find(opv);
                if(fua^fva)
                {
                    dsuA.merge(fua,fva);
                    tr[rt].opps.push(0);
                    if(fub==fvb)rans--,tr[rt].opps.push(3);
                    dsuB.merge(opu,opv);
                    tr[rt].opps.push(1);
                }
            }
        }
        if(L==R)ans[L]=rans;
        else dfs(ls),dfs(rs);
        while(tr[rt].opps.size())
        {
            auto op=tr[rt].opps.top();
            tr[rt].opps.pop();
            if(op==0)dsuA.undo();
            else if(op==1)dsuB.undo();
            else if(op==2)rans--;
            else if(op==3)rans++;
        }
    }
    #undef L
    #undef R
    #undef ls
    #undef rs
}tree;
ll n,q;
char str[10];
map<tuple<ll,ll,ll>,ll> mpv;
tuple<ll,ll,ll> qs[N];
signed main()
{
    n=read(),q=read();
    dsuA=dsu(n),dsuB=dsu(n);
    tree.build(1,q,1);
    loop(i,1,q)
    {
        scanf("%s",str);
        ll u=read(),v=read();
        if(u>v)swap(u,v);
        qs[i]={*str=='B',u,v};
        auto it=mpv.find(qs[i]);
        if(it==mpv.end())mpv.insert({qs[i],i});
        else tree.modify(it->second,i-1,qs[i],1),mpv.erase(it);
    }
    for(auto &[x,y]:mpv)tree.modify(y,q,x,1);
    tree.dfs(1);
    loop(i,1,q)printf("%lld\n",tree.ans[i]);
    return 0;
}
```

### Postscript

感谢 [@murder_drones](https://www.luogu.com.cn/user/610393) 的大力支持/bx/bx/bx

---

## 作者：arrow_king (赞：4)

笑点解析：笔者场上不想写这题。

这不就是动态图连通性板子题吗，使用线段树分治解决。

首先考虑答案怎么求。容易发现答案就是（$A$ 的连通块数量）$-$（$A\cup B$ 的连通块数量）。证明是简单的：考虑 $B$ 中联通但是在 $A$ 中不连通的两个点，将他们在 $A$ 中连接一条边，重复以上过程，可以发现如果两个点 $u,v$ 在 $A,B$ 中的一张图中联通，那么它们在 $A\cup B$ 中也联通，因此最终图的连通块个数是 $A\cup B$ 的连通块数量。连接一条边会减少一个连通块数量，因此总答案是（$A$ 的连通块数量）$-$（$A\cup B$ 的连通块数量），证明完毕。

解决了静态的情况之后可以考虑增加修改，要维护图中连通块的数量。考虑离线使用线段树分治，需要使用启发式合并的可撤销并查集维护边联通情况，然后就做完了。

时间复杂度 $O(n\log^2n)$，空间复杂度 $O(n\log n)$。

放一下线段树分治部分的代码，可以作为动态图连通性的板子使用。

```cpp
int fa[2][N],res[2],siz[2][N];
vector<pii> edge[2][N<<2];
il void Insert(int nl,int nr,int l,int r,int now,int idx,pii e) {
	if(nl<=l&&r<=nr) {
		edge[idx][now].push_back(e);
		return;
	}
	int mid=(l+r)>>1;
	if(nl<=mid) Insert(nl,nr,l,mid,lc(now),idx,e);
	if(mid<nr) Insert(nl,nr,mid+1,r,rc(now),idx,e);
}
int top[2];
vector<int> st[2][N];
il int findf(int idx,int x) {return x==fa[idx][x]?x:findf(idx,fa[idx][x]);}
il void Union(int idx,int x,int y) {
	x=findf(idx,x),y=findf(idx,y);
	if(x==y) return;
	if(siz[idx][x]>siz[idx][y]) swap(x,y);
	st[idx][++top[idx]]={x,fa[idx][x],y,siz[idx][y]};
	fa[idx][x]=y,siz[idx][y]+=siz[idx][x];
	--res[idx];
}
int itop[2][N<<2];
il void DFS(int now,int l,int r) {
	itop[0][now]=top[0],itop[1][now]=top[1];
	for(auto e:edge[0][now]) Union(0,e.fi,e.se),Union(1,e.fi,e.se);
	for(auto e:edge[1][now]) Union(1,e.fi,e.se);
	if(l==r) {
		printf("%d\n",res[0]-res[1]);
		while(top[0]!=itop[0][now]) {
			fa[0][st[0][top[0]][0]]=st[0][top[0]][1];
			siz[0][st[0][top[0]][2]]=st[0][top[0]][3];
			--top[0],++res[0];
		}
		while(top[1]!=itop[1][now]) {
			fa[1][st[1][top[1]][0]]=st[1][top[1]][1];
			siz[1][st[1][top[1]][2]]=st[1][top[1]][3];
			--top[1],++res[1];
		}
		return;
	}
	int mid=(l+r)>>1;
	DFS(lc(now),l,mid),DFS(rc(now),mid+1,r);
	while(top[0]!=itop[0][now]) {
		fa[0][st[0][top[0]][0]]=st[0][top[0]][1];
		siz[0][st[0][top[0]][2]]=st[0][top[0]][3];
		--top[0],++res[0];
	}
	while(top[1]!=itop[1][now]) {
		fa[1][st[1][top[1]][0]]=st[1][top[1]][1];
		siz[1][st[1][top[1]][2]]=st[1][top[1]][3];
		--top[1],++res[1];
	}
}
```

---

## 作者：冷却心 (赞：1)

upd 250224: 在题解中使用了【数据删除】被 ban。

E 是什么【数据删除】题，场上调了一个小时多没过，遗憾离场，赛时只看了一眼 F 感觉是线段树分治，然后去 E 之后就没写了，告诉我们永远要相信线段树。线段树好闪，拜谢线段树。

> 注意到，对于一张给定的 $A,B$ 图，需要添加的边条数为 $A$ 的连通块数减去 $A\cup B$ 的连通块数。

解释一下。我们得到的图需要包含图 $B$，显然 $B$ 中每一条边的两端在新图中一定属于同一个连通块，那么我们把 $B$ 的所有边加入这个新图一定不劣，因为没有添加额外的边连接两个不必须连通的点。并且我们的新图必须包含原有的 $A$ 的边，所以再把 $A$ 的边全部加入，所以得到的 $A\cup B$ 是不劣的。

显然 $A\cup B$ 包含图 $A$，那么 $A$ 变成 $A\cup B$ 添加的边数就是连通块数之差，因为 $A$ 变成 $A\cup B$ 相当于加了若干边连通了若干块，那么最小的加入边数就是连通块之差。

所以其实已经做完了。我们需要维护一个支持动态插入删除，查询连通块数的数据结构，这个是难以维护的。但是我们把删除转化为时间轴上不加入即可，其实就是线段树分治板子。

线段树分治套并查集维护图 $A$ 和图 $A\cup B$ 的连通块数即可。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 4e5 + 10;
int n, Q, Ans[N]; 
map<LL, int> mp; set<int> sa, sb;
struct Edge { int u, v; } e[N]; int m = 0, lsta[N], lstb[N];

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
vector<int> tra[N << 2], trb[N << 2];
void updatea(int p, int l, int r, int x, int y, int k) {
	if (x > r || y < l) return ;
	if (x <= l && y >= r) { tra[p].emplace_back(k); return ; }
	int mid = (l + r) >> 1; 
	updatea(ls(p), l, mid, x, y, k); updatea(rs(p), mid + 1, r, x, y, k);
}
void updateb(int p, int l, int r, int x, int y, int k) {
	if (x > r || y < l) return ;
	if (x <= l && y >= r) { trb[p].emplace_back(k); return ; }
	int mid = (l + r) >> 1; 
	updateb(ls(p), l, mid, x, y, k); updateb(rs(p), mid + 1, r, x, y, k);
}

struct DSU {
	int fa[N], sz, rnk[N], tp, stk[2][N];
	void init(int n) {
		sz = n; tp = 0; for (int i = 1; i <= n; i ++) fa[i] = i, rnk[i] = 1;
	}
	int find(int x) { return (fa[x] == x ? x : find(fa[x])); }
	void merge(int u, int v) {
		u = find(u), v = find(v); if (u == v) return ;
		sz --; ++ tp;
		if (rnk[u] < rnk[v]) swap(u, v);
		if (rnk[u] == rnk[v]) stk[1][tp] = u, rnk[u] ++;
		stk[0][tp] = v; fa[v] = u; return ;
	}
	void undo() {
		fa[stk[0][tp]] = stk[0][tp]; if (stk[1][tp]) rnk[stk[1][tp]] --;
		tp --; ++ sz;
	}
} dsuA, dsuB;

void DFS(int p, int l, int r) {
	int tpa = dsuA.tp, tpb = dsuB.tp;
	for (int i : tra[p]) {
		dsuA.merge(e[i].u, e[i].v), dsuB.merge(e[i].u, e[i].v);
	}
	for (int i : trb[p]) dsuB.merge(e[i].u, e[i].v);
	if (l == r) { Ans[l] = dsuA.sz - dsuB.sz; }
	else {
		int mid = (l + r) >> 1; DFS(ls(p), l, mid); DFS(rs(p), mid + 1, r);
	}
	while (dsuA.tp > tpa) dsuA.undo();
	while (dsuB.tp > tpb) dsuB.undo();
}
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> Q; char c; int u, v;
	for (int i = 1; i <= Q; i ++) {
		cin >> c >> u >> v;
		if (u > v) swap(u, v);
		if (mp.find(1ll * u * n + v) == mp.end()) 
			mp[1ll * u * n + v] = ++ m, e[m] = {u, v};
		int id = mp[1ll * u * n + v];
		if (c == 'A') {
			if (sa.find(id) == sa.end()) sa.insert(id), lsta[id] = i;
			else sa.erase(id), updatea(1, 1, Q, lsta[id], i - 1, id);
		} else {
			if (sb.find(id) == sb.end()) sb.insert(id), lstb[id] = i;
			else sb.erase(id), updateb(1, 1, Q, lstb[id], i - 1, id);
		}
	} 
	for (int i : sa) updatea(1, 1, Q, lsta[i], Q, i);
	for (int i : sb) updateb(1, 1, Q, lstb[i], Q, i);
	dsuA.init(n); dsuB.init(n); DFS(1, 1, Q);
	for (int i = 1; i <= Q; i ++) cout << Ans[i] << "\n";
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

有两个 $n$ 个点的无向图 $A,B$，有 $m$ 次操作，每次选定一个无向图并给出一条边 $(x,y)$，如果在对应的图中存在，就删除这条边，否则连接这条边。

在每一次操作结束时，你需要求出最少在 $A$ 中添加多少条边，使得对于 $B$ 的每个连通块 $S$，都可以找到 $A$ 的一个连通块 $T$，使得 $S\subseteq T$。

$1\leq n,m\leq 4\times 10^5$。

## 思路

首先题目中要求的东西非常抽象，不妨加以转化。我们不妨这样考虑：对于在 $B$ 中位于同一个连通块的两个点 $x,y$，如果在 $A$ 中分属两个连通块，那么这两个连通块中就需要连接一条边。那么当 $A$ 连最少的边以符合条件后，只要对于边 $(x,y)\in A\lor (x,y)\in B$，则 $x,y$ 就属于同一个连通块，故其实最后形成的图的所有连通块其实与 $A\cup B$ 相同。

若 $A\cup B$ 的连通块数比 $A$ 的连通块数少 $x$，那么就需要连 $x$ 条边以合并连通块。所以答案就是 $A$ 的连通块数量与 $A\cup B$ 的连通块数量之差。

于是我们需要维护一个动态图加边删边，求连通块数。直接维护极为困难，不过只加边可以用并查集轻易地完成，所以只需要线段树分治即可。时间复杂度 $O(m\log^2 n)$。

[Submission](https://codeforces.com/contest/2069/submission/307389153)。

---

## 作者：Silvestorm (赞：1)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF2069F)

给出空的图 $A,B$，有 $Q$ 次操作，每次操作往一个图里增加或删除一条边，每次操作结束后求最小需要往 $A$ 里添加多少条边使得图 $B$ 是图 $A$ 子图。

### 题目类型

图论，启发式合并，线段树分治，并查集。

### 解题思路

每条边存在一段时间后消失，动态维护图连通性的信息，是线段树分治的经典用法，即线段树维护边存在的时间段。这样递归到叶子节点的时候，通过并查集不断合并就可以得到这个时刻图的信息，同时进行回溯的时候，利用进栈出栈的方式可以做到 $O(1)$ 的删边。

接下可以考虑对答案的计算。添加最少的边，就是不断合并连通块。在图 $A$ 的一个连通块里，有些点是多余的，删了他们也不会影响图 $A$ 是图 $B$ 的子图，但它影响了图 $A$ 的连通块总数，为了消除这些影响，可以考虑往图 $B$ 里添加相应的边，换而言之，就是将图 $A$ 和图 $B$ 合并，得到新的图 $B$，那么图 $A$ 多余的连通块就是我们要合并的东西，它们的个数就是答案。

并查集的合并需要用到启发式合并，这样才好撤销，时间复杂度为均摊 $O(\log n)$。

时间复杂度为 $O(n\log n\log n)$，空间复杂度为 $O(n\log n)$。

### code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128_t
ll n, m, tot, cnt, ans[500100][2], flag, root, x, k, mod = 998244353;
const int len = 500010;
ll num[500100][2];
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }
vector<pair<ll, ll>> v[2000100][2];
void update(ll nl, ll nr, ll l, ll r, ll p, ll k, pair<ll, ll> x)//线段树分治
{
    if (nl <= l && r <= nr)
    {
        if (!k)
            v[p][1].push_back(x);
        v[p][k].push_back(x);
        return;
    }
    ll mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, ls(p), k, x);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rs(p), k, x);
}
ll fa[400100], siz[400100];
bool merge(ll &x, ll &y)//启发式合并
{
    while (fa[x] != x)
        x = fa[x];
    while (fa[y] != y)
        y = fa[y];
    if (x == y)
        return 0;
    if (siz[x] > siz[y])
        swap(x, y);
    siz[y] += x;
    fa[x] = y;
    cnt--;
    return 1;
}

void roll(ll x, ll y)//回溯，删除边
{
    siz[y] -= siz[x];
    fa[x] = x;
    cnt++;
}
map<pair<ll, ll>, ll> mp;
void query(ll l, ll r, ll p, ll k)
{
    ll g = cnt;
    vector<pair<ll, ll>> a;
    for (auto [i, j] : v[p][k])
        if (merge(i, j))
            a.push_back({i, j});
    reverse(a.begin(), a.end());//模拟栈的话需要将数组翻转

    if (l == r)
        ans[l][k] = cnt;
    else
    {
        ll mid = (l + r) >> 1;
        query(l, mid, ls(p), k);
        query(mid + 1, r, rs(p), k);
    }
    for (auto [i, j] : a)
        roll(i, j);
}
void Solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        siz[i] = 1;
    }
    map<pair<ll, ll>, int> mp1, mp2;
    for (int i = 1; i <= m; i++)
    {
        string op;
        ll a, b;
        cin >> op >> a >> b;
        if (a > b)
            swap(a, b);
        if (op == "A")
        {
            if (mp1[{a, b}])
            {
                update(mp1[{a, b}], i - 1, 1, m, 1, 0, {a, b});
                mp1.erase({a, b});
            }
            else
                mp1[{a, b}] = i;//记录添加边的时间点
        }
        else
        {
            if (mp2[{a, b}])
            {
                update(mp2[{a, b}], i - 1, 1, m, 1, 1, {a, b});
                mp2.erase({a, b});
            }
            else
                mp2[{a, b}] = i;
        }
    }
    for (auto [a, b] : mp1)
        update(b, m, 1, m, 1, 0, a);
    for (auto [a, b] : mp2)
        update(b, m, 1, m, 1, 1, a);
    cnt = n;
    query(1, m, 1, 0);//图A的连通块数
    cnt = n;
    query(1, m, 1, 1);//图B的连通块数
    for (int i = 1; i <= m; i++)
        cout << ans[i][0] - ans[i][1] << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Solve();
    return 0;
}
```

---

## 作者：djyqjy (赞：1)

### 题目大意
给定两图 $A$，$B$。图 $A$ 包含图 $B$，当且仅当图 $B$ 的每个连通分量都是图 $A$ 某个连通分量的子集。求在图 $A$ 中加入多少条边，才能使图 $A$ 包含图 $B$。支持加边和删边操作。

### 题目思路
看到支持插入删除，首先想到线段树分治，这样只需要处理加边的情况。我们发现只维护 $A$ 和 $B$ 不太好做，考虑维护图 $A$ 与 $A\cup B$。

当在图 $A$ 中加边时，若其端点在图 $A$ 中不联通而在图 $A\cup B$ 中联通，说明需要将之前统计过的答案撤回，$ans$ 减 1。否则，容易证明无需修改答案。

同理，在图 $B$ 中加边时，若其端点在图 $A$ 和图 $A\cup B$ 中均不联通，$ans$ 加 1，否则无需修改答案。

因为要维护连通性，所以使用并查集即可。注意因为用了线段树分治，所以不能使用路径压缩。

时间复杂度 $O(n\log^2n)$。

### Code

```cpp
//代码写得烂，凑合看吧
#include<bits/stdc++.h>
using namespace std;
inline int re()
{
    int f=1,num=0;
   char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') num=num*10+c-'0',c=getchar();
    return num*f;
}
const int N=400010;
struct query
{
    int x,y,lt,rt,type;//x,y:边，lt,rt:边的存在时间，type:0表示A，1表示B
}qs[N];
struct node
{
    int x,y,type;
};
vector<node> vec[4*N];//存线段树节点的操作
map<pair<int,int>,int> mp[2];//0表示A，1表示B
int n,q;
char c[5];
int res[N];//记录答案
int ans;//当前答案
vector<pair<int&,int> > stk;//回溯栈
void add_seg(int ql,int qr,int x,int y,int type,int l,int r,int p)//l,r:当前区间，p:当前树上位置
{
    if(ql<=l&&r<=qr)
    {
        vec[p].push_back((node){x,y,type});
        return;
    }
    int mid=(l+r)/2;
    if(ql<=mid) add_seg(ql,qr,x,y,type,l,mid,p<<1);
    if(mid<qr) add_seg(ql,qr,x,y,type,mid+1,r,p<<1|1);
    return;
}
int fa[N][2],sz[N][2];
int get(int x,int s)
{
    if(fa[x][s]==x) return x;
    return get(fa[x][s],s);
}
void merge(int x,int y,int s)
{
    x=get(x,s);y=get(y,s);
    if(x==y) return;
    if(sz[x][s]>sz[y][s]) swap(x,y);
    stk.emplace_back(fa[x][s],fa[x][s]);
    stk.emplace_back(sz[y][s],sz[y][s]);
    fa[x][s]=y;
    sz[y][s]+=sz[x][s];
    return;
}
void add_edge(int x,int y,int t)
{
    stk.emplace_back(ans,ans);
    if(t==0)
    {
        if(get(x,0)!=get(y,0)&&get(x,1)==get(y,1)) ans--;
        merge(x,y,0);merge(x,y,1);
    }
    else
    {
        if(get(x,0)!=get(y,0)&&get(x,1)!=get(y,1)) ans++;
        merge(x,y,1);
    }
    return;
}
void dfs(int l,int r,int p)
{
    int top=stk.size();//记录原栈顶
    for(auto z:vec[p]) add_edge(z.x,z.y,z.type);
    if(l==r) res[l]=ans;
    else
    {
        int mid=(l+r)/2;
        dfs(l,mid,p<<1);dfs(mid+1,r,p<<1|1);
    }
    while(stk.size()>top) stk.back().first=stk.back().second,stk.pop_back();//回溯
    return;
}
int main()
{
    n=re();q=re();
    for(int i=1;i<=n;i++) fa[i][0]=fa[i][1]=i,sz[i][0]=sz[i][1]=1;
    for(int i=1,x,y,t;i<=q;i++)
    {
        scanf("%s",c);
        if(c[0]=='A') t=0;
        else t=1;
        x=re();y=re();
        if(x>y) swap(x,y);
        if(!mp[t].count(make_pair(x,y))||mp[t][make_pair(x,y)]==0)
        {
            mp[t][make_pair(x,y)]=i;
            qs[i]=(query){x,y,i,q,t};
        }
        else qs[mp[t][make_pair(x,y)]].rt=i-1,mp[t][make_pair(x,y)]=0;
    }
    for(int i=1;i<=q;i++) if(qs[i].x) add_seg(qs[i].lt,qs[i].rt,qs[i].x,qs[i].y,qs[i].type,1,q,1);//建树
    dfs(1,q,1);//线段树分治
    for(int i=1;i<=q;i++) printf("%d\n",res[i]);
    return 0;
}
```

---

## 作者：postpone (赞：0)

先不考虑询问，就给你两个静态的图 $A$ 和 $B$，怎么求添加的最少边数，使 $A$ 能包含 $B$ 呢？

我们把 $A$ 和 $B$ 并起来，令 $C=A\cup B$，即 $A$ 如果要包含 $B$，就“至少”得长成 $C$ 的样子。则我们要的答案就是 $A$ 与 $C$ 的连通块个数的差（一条边能减少一个连通块）。

再想想动态的情况要怎么处理。首先，最暴力地，维护现有的边，对于每个询问，我们都从头开始合并，然后计算答案。

要怎么优化呢？是不是可以把询问抽象成时间，这样这道题就等价于：一些边会在某时刻出现，在某时刻消失（或一直不消失），要对每个时刻计算答案。这就是一个非常经典的线段树分治模型。通过线段树分治，我们能将时间这个维度优化成对数级别。

总复杂度为 $O(q\log n\log q)$。代码如下，参考了哥哥的写法，打了一些注释便于大家理解。

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, q;
    cin >> n >> q;
 
    map<array<int, 2>, int> edges[2];
 
    vector<vector<array<int, 3>>> f(4 * q);
    auto addEdge = [&](this auto &&self, int p, int l, int r, int x, int y, int t, int u, int v) {
        if (l >= y or r <= x) {
            return;
        }
        if (l >= x and r <= y) {
            f[p].push_back({t, u, v});
            return;
        }
        int m = (l + r) / 2;
        self(2 * p, l, m, x, y, t, u, v);
        self(2 * p + 1, m, r, x, y, t, u, v);
    };
 
    for (int i = 0; i < q; i++) {
        char g;
        int x, y;
        cin >> g >> x >> y;
        x--;
        y--;
 
        if (x > y) {
            swap(x, y);
        }
        int t = g - 'A';
        if (edges[t].contains({x, y})) {
            addEdge(1, 0, q, edges[t][{x, y}], i, t, x, y);
            edges[t].erase({x, y});
        } else {
            edges[t][{x, y}] = i;
        }
    }
    for (int t = 0; t < 2; t++) {
        for (auto [e, i] : edges[t]) {
            auto [x, y] = e;
            addEdge(1, 0, q, i, q, t, x, y);
        }
    }
 
    // dsu[0] : A 和 B 的并
    // dsu[1] : A
    DSU dsu[2] {n, n};
    // 我们维护并集的连通块个数，和 A 的连通块个数，答案就是后者减去前者。
    auto work = [&](this auto &&self, int p, int l, int r, int S, int A) -> void {
        int tm[2] = {dsu[0].his.size(), dsu[1].his.size()};
 
        for (auto [t, u, v] : f[p]) {
            S -= dsu[0].merge(u, v);
            if (t == 0) {
                A -= dsu[1].merge(u, v);
            }
        }
        if (r - l == 1) {
            cout << A - S << "\n";
        } else {
            int m = (l + r) / 2;
            self(2 * p, l, m, S, A);
            self(2 * p + 1, m, r, S, A);
        }
        for (int t = 0; t < 2; t++) {
            dsu[t].undo(tm[t]);
        }
    };
    work(1, 0, q, n, n);
 
    return 0;
}
```

---

## 作者：Otue (赞：0)

## [CF2069F Graph Inclusion](https://www.luogu.com.cn/problem/CF2069F)

### 题目大意

有两张空图 $A,B$，每一时刻在 $A$ 或 $B$ 图中加入或删除一条无向边。

每一时刻求出最少在 $A$ 中加多少条边，满足 $B$ 图中任意两连通的点 $(u,v)$，在 $A$ 图中也连通。

### 题目思路

对于 $B$ 图中的每一条边 $(u,v)$，如果在 $A$ 图中不联通，那么就加入这条边，否则就不加入。那么等价 $A$ 图与 $B$ 图合成新的联通块。这个混合图的联通块的连通分量个数就是最终的个数。因为每次加边，联通块个数会减去 $1$。所以最少加边条数就是混合图的连通分量个数减去 $A$ 图的连通分量个数。

现在用线段树分治维护两个图的连通性，是轻松的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)

const int N = 4e5 + 5;

int n, m, p[N], sz[N], tot, dep[N], res[N][2], cnt;  
map<PII, int> visa, visb;

struct node {
  int u, v, add;
}st[N];

int find(int x) {
  if (p[x] != x) return find(p[x]);
  return p[x];
}

void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (fx == fy) return;
  cnt--;
  if (dep[fx] > dep[fy]) swap(fx, fy);
  st[++tot] = {fx, fy, dep[fx] == dep[fy]};
  p[fx] = fy;
  sz[fy] += sz[fx];
  if (dep[fx] == dep[fy]) dep[fy]++;
}

vector<PII> t[N * 4][2];
void modify(int p, int l, int r, int L, int R, int op, int u, int v) {
  if (R < l || r < L) return;
  if (l <= L && R <= r) {
    if (op == 0) {
      t[p][0].push_back({u, v});
      t[p][1].push_back({u, v});
    }
    else t[p][1].push_back({u, v});
    return;
  }
  int mid = (L + R) >> 1;
  modify(p << 1, l, r, L, mid, op, u, v);
  modify(p << 1 | 1, l, r, mid + 1, R, op, u, v);
}

void query(int u, int l, int r, int op) {
  int lst = tot;
  for (auto e : t[u][op]) {
    int u = e.first, v = e.second;
    merge(u, v); 
  }
  if (l == r) res[l][op] = cnt;
  else {
    int mid = (l + r) >> 1;
    query(u << 1, l, mid, op);
    query(u << 1 | 1, mid + 1, r, op);
  }
  while (tot > lst) {
    dep[st[tot].v] -= st[tot].add;
    p[st[tot].u] = st[tot].u;
    sz[st[tot].v] -= sz[st[tot].u];
    tot--;
    cnt++;
  }
}

signed main() {
  cin >> n >> m;
  _for(i, 1, m) {
    char op; int u, v;
    cin >> op >> u >> v;
    if (u > v) swap(u, v);
    if (op == 'A') {
      if (visa[{u, v}] != 0) modify(1, visa[{u, v}], i - 1, 1, m, 0, u, v), visa[{u, v}] = 0;
      else visa[{u, v}] = i;
    }
    else {
      if (visb[{u, v}] != 0) modify(1, visb[{u, v}], i - 1, 1, m, 1, u, v), visb[{u, v}] = 0;
      else visb[{u, v}] = i;
    }
  }
  for (auto e : visa) {
    int u = e.first.first, v = e.first.second;
//    cout << "P=" << u << ' ' << v << ' ' << e.second << endl;
    if (e.second == 0) continue;
    modify(1, e.second, m, 1, m, 0, u, v); 
  }
  for (auto e : visb) {
    int u = e.first.first, v = e.first.second;
    if (e.second == 0) continue;
    modify(1, e.second, m, 1, m, 1, u, v); 
  }
  cnt = n;
  _for(i, 1, n) p[i] = i, sz[i] = dep[i] = 1;
  query(1, 1, m, 0);
  cnt = n;
  _for(i, 1, n) p[i] = i, sz[i] = dep[i] = 1;
  query(1, 1, m, 1);
  _for(i, 1, m) cout << res[i][0] - res[i][1] << endl;
}
```

---

## 作者：SUNCHAOYI (赞：0)

对于一组询问，答案为 $A$ 中连通块的数量 - $A \cup B$ 中的连通块数量。

设在 $A$ 中添加了若干条边后变为 $A'$。当两个顶点 $u,v$ 在 $A$ 或 $B$ 中属于同一个连通分量，那么在 $A'$ 中必同属于一个连通分量。因此，我们不难得出上述结论。

由于存在动态的加边删边，不难想到时间戳的线段树分治。对于在某一张图的边，记录下出现时间和消失时间 $l,r$，则由题目可知，该边在 $[l,r - 1]$ 范围内产生贡献。注意，若一条边在加入之后一直存在，则该边在 $[l,q]$ 范围内产生贡献。

至于如何计算连通块的个数，初始值显然为 $n$。与此同时，可以在并查集的合并时增加一个返回值，若形成一次有效的合并时，连通块的个数便会减少 $1$。

由于需要分别维护 $A$ 和 $A \cup B$ 的连通块数量，我们可以先求解出 $A$，然后在此基础上加入 $B$ 的边即可得到 $A \cup B$ 的答案。

由于并查集不能路径压缩，最后时间复杂度为 $O(q \log q \log n)$，代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int> 
using namespace std;
const int MAX = 4e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
pii st[MAX],e[MAX]; 
vector <pii> ve[MAX << 2];
map <pii,int> mp;
int n,q,top,ans[3][MAX],fa[MAX],sz[MAX];char ty[MAX][1];
int getfa (int u);
bool merge (int u,int v);
void modify (int cur,int l,int r,int x,int y,pii v);
void solve (int res[],int cur,int l,int r,int tot);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();q = read ();
	for (int i = 1;i <= n;++i) fa[i] = i,sz[i] = 1;
	for (int i = 1;i <= q;++i)
	{
		scanf ("%s",ty[i]);int u = read (),v = read ();
		if (u > v) swap (u,v);
		e[i] = {u,v};
	}
	for (int i = 1;i <= q;++i)
	{
		if (ty[i][0] == 'B') continue;
		if (!mp[e[i]]) mp[e[i]] = i;
		else 
		{
			modify (1,1,q,mp[e[i]],i - 1,e[i]);
			mp[e[i]] = 0;
		}
	}
	for (auto item : mp)
		if (item.second) modify (1,1,q,item.second,q,item.first);
	solve (ans[1],1,1,q,n);
	mp.clear ();
	for (int i = 1;i <= q;++i)
	{
		if (ty[i][0] == 'A') continue;
		if (!mp[e[i]]) mp[e[i]] = i;
		else
		{
			modify (1,1,q,mp[e[i]],i - 1,e[i]);
			mp[e[i]] = 0;
		}
	}
	for (auto item : mp)
		if (item.second) modify (1,1,q,item.second,q,item.first);
	solve (ans[2],1,1,q,n);
	for (int i = 1;i <= q;++i) printf ("\t%d\n",ans[1][i] - ans[2][i]);//A - A U B
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
int getfa (int u) {return fa[u] == u ? u : getfa (fa[u]);} 
bool merge (int u,int v)
{
	u = getfa (u),v = getfa (v);
	if (u == v) return 0;
	if (sz[u] > sz[v]) swap (u,v);
	st[++top] = {u,v};// u -> v
	fa[u] = v;sz[v] += sz[u];
	return 1;
}
void modify (int cur,int l,int r,int x,int y,pii v)
{
	if (x <= l && y >= r) {ve[cur].push_back (v);return ;}
	int mid = (l + r) >> 1;
	if (x <= mid) modify (cur << 1,l,mid,x,y,v);
	if (y > mid) modify (cur << 1 | 1,mid + 1,r,x,y,v); 
}
void solve (int res[],int cur,int l,int r,int tot)
{
	int la = top;
	for (auto p : ve[cur]) tot -= merge (p.first,p.second);
	if (l == r) res[l] = tot;
	else
	{
		int mid = (l + r) >> 1;
		solve (res,cur << 1,l,mid,tot);solve (res,cur << 1 | 1,mid + 1,r,tot);
	}
	while (top > la)
	{
		sz[st[top].second] -= sz[st[top].first];
		fa[st[top].first] = st[top].first;
		--top;
	}
}
```

---

