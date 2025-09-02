# DerrickLo's City (UBC002C)

## 题目背景

DerrickLo 看到了一个 $n \le 7.5 \times 10^5$ 的题，并且发现很多人写了 $O(n^2)$ 过了。于是他想写 $O(n\log^3n)$，但是挂了。于是将原题的序列改成了树。

注：以上故事是将出题人的名字换成 DerrickLo 得到的。


## 题目描述

DerrickLo 在游戏中掌控着一个城市。这个城市内的团体间并不是非常的和谐，因此需要通过开会来增进关系。

已知这个组织所在的城市被分为了 $n$ 个镇，每一个镇上恰好有一个团体。其中编号为 $1$ 的镇上分布着团体 $1$，$2$ 号镇上有团体 $2$，等等。这 $n$ 个镇通过 $n-1$ 条路径相连，两两可以互相到达。

每次开会，DerrickLo 会指定一个区间 $[l, r]$，邀请编号在 $[l, r]$ 之间的团体来开会。由于团体比较分散，因此他还需要指定一个开会地址 $p$。因为团体的关系比较僵硬，所以前往开会的团体去 $p$ 的途中，不能到达别的与会团体所在的镇。

由于 DerrickLo 刚接触这个游戏，操作不太熟悉，确定 $p$ 的任务就交给你了。


## 说明/提示

对于第一个会议，$1, 2, 6$ 镇均可作为参会点。

对于第二个会议，无论选哪里作为参会点，$2, 4$ 两团体均会有一方经过另一镇。

### 数据范围

$1 \le n, q \le 10^5$。

保证道路 $(a_i, b_i)$ 使得任意两镇可互相到达。

$1 \le l_i \le r_i \le n$。


## 样例 #1

### 输入

```
6 2
1 2
1 3
2 4
2 5
1 6
3 5
2 4
```

### 输出

```
Yes
No
```

# 题解

## 作者：fzitb7912 (赞：7)

## 分析

直接算吧。先把 $\operatorname{LCA}(l,l+1,\dots,r)$ 求出来，记为 $x$。然后分类讨论：

1. $l \le x \le r$。那么除开 $x$ 外剩下的点不存在 $\operatorname{LCA}(i,j)=i$。记 $y$ 为它们的 $\operatorname{LCA}$，那么 $y \ne x$。
2. $x < l\lor x>r$。那么这些点不存在 $\operatorname{LCA(i,j)}=i$。

所以现在问题变成了一个判定区间内是否存在一对点 $(i,j)$，使得其中一个是另一个的祖先。这个是个典的东西。我们对于每个点 $u$ 记录 $pre_u$ 表示 $u$ 子树中最大的满足 $v < u$ 的 $v$ 值，$nxt_u$ 表示 $u$ 子树中最小的满足 $v>u$ 的 $v$ 值。那么当 $[l,r]$ 中存在一个点 $i$，满足 $pre_i \ge l \lor nxt_i \le r$，就一定存在至少一对点了。预处理这个可以跑一遍 DFS。

求区间 $\operatorname{LCA}$ 是典 trick，区间中相邻两个 $\operatorname{LCA}$ 深度最小的就是区间的 $\operatorname{LCA}$。

但是这么做会有一点小问题。就是如果我们一共有 $2$ 个点，且它们相邻，我们并不会判定它们不行。为什么呢，因为我们只看了 $y \ne x$。而 $y \ne x$ 时我们决策的 $p$ 是在 $y$ 点上的。所以如果 $y$ 上面有点就错了。这个特殊处理即可。那为什么点数 $>2$ 时不会错呢，因为我们一定有 $y$ 子树内某个点 $z$ 属于区间 $[l,r]$，已经判掉了。

这样做的时间复杂度为 $O(n\log n+q)$，标程在写什么。

## 代码

```cpp
il void dfs(int u,int fa){
	dep[u]=dep[fa]+1,
	f[u][0]=fa;
	for(re int i=1;i<20;++i) f[u][i]=f[f[u][i-1]][i-1];
	auto it=st.lower_bound(u);
	if(it!=st.begin()){
		--it;
		nxt[*it]=min(nxt[*it],u);
	}
	it=st.lower_bound(u);
	if(it!=st.end()){
		pre[*it]=max(pre[*it],u);
	}
	st.insert(u);
	for(auto v:e[u])
	if(v!=fa) dfs(v,u);
	st.erase(u);
	return ;
}
il int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re int i=19;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re int i=19;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0]; 
}
il int query_lca(int l,int r){
	if(l>r) return l;
	int k=__[r-l+1];
	if(dep[lc[l][k]]<=dep[lc[r-(1ll<<k)+1][k]]) return lc[l][k];
	return lc[r-(1ll<<k)+1][k];
}
il int query_min(int l,int r){
	if(l>r) return inf;
	int k=__[r-l+1];
	return min(Min[l][k],Min[r-(1ll<<k)+1][k]);
}
il int query_max(int l,int r){
	if(l>r) return -inf;
	int k=__[r-l+1];
	return max(Max[l][k],Max[r-(1ll<<k)+1][k]);
}

il void solve(){
	n=rd,q=rd;
	for(re int i=1;i< n;++i){
		int u=rd,v=rd;
		e[u].push_back(v),
		e[v].push_back(u); 
	}
	for(re int i=1;i<=n;++i) pre[i]=-inf,nxt[i]=inf;
	dfs(1,0);
	for(re int i=0;i< N;++i) __[i]=log2(i);
	for(re int i=1;i<=n;++i){
		if(i<n) lc[i][0]=lca(i,i+1);
		Min[i][0]=nxt[i],
		Max[i][0]=pre[i];
	}
	for(re int j=1;j<20;++j)
	for(re int i=1;i+(1ll<<j)-1<=n;++i){
		if(dep[lc[i][j-1]]<=dep[lc[i+(1ll<<(j-1))][j-1]]) lc[i][j]=lc[i][j-1];
		else lc[i][j]=lc[i+(1ll<<(j-1))][j-1];
		Min[i][j]=min(Min[i][j-1],Min[i+(1ll<<(j-1))][j-1]),
		Max[i][j]=max(Max[i][j-1],Max[i+(1ll<<(j-1))][j-1]);
	}
	while(q--){
		int l=rd,r=rd;
		if(l==r){
			puts("Yes");
			continue;
		}
		int x=query_lca(l,r-1);
		if(x<l||x>r){
			int mx=query_max(l,r);
			int mi=query_min(l,r);
			if(mx>=l||mi<=r) puts("No");
			else puts("Yes");
		}
		else{
			int Lca;
			if(x==l) Lca=query_lca(l+1,r-1);
			else if(x==r) Lca=query_lca(l,r-2);
			else Lca=lca(query_lca(l,x-2),query_lca(x+1,r-1));
			if(Lca==x){
				puts("No");
				continue;
			}
			if(dep[Lca]==dep[x]+1&&r-l+1==2){
				puts("No");
				continue;
			}
			int mi=min(query_min(l,x-1),query_min(x+1,r));
			int mx=max(query_max(l,x-1),query_max(x+1,r));
			if(mi<=r||mx>=l) puts("No");
			else puts("Yes");
		}
	}
    return ;
}
```

---

## 作者：WorldMachine (赞：4)

好题不难。

题意就是说，对于区间 $[l,r]$ 内的点，是否存在一个 $p$，使得 $\forall i\in[l,r]$，$\text{path}(p,i)\cap[l,r]=\{i\}$。

首先长的区间可以短的区间一定可以，那就双指针，问题转化为快速增删判合法性。

发掘问题本身的性质。首先如果有两点相邻肯定不行。然后考虑类似 top tree 的过程，可以 compress 和 rake **非关键点**，合法的区间最后一定会变成一个菊花图，中心是非关键点，其余一圈关键点，这个图的性质是没有三个关键点共链。

所以考虑怎么判共链。对于区间 $[l,r]$，记 $S=\bigcup\limits_{l\le i<j\le r}\text{path}(i,j)$。

加入 $r+1$ 时，首先需要保证 $r+1\not\in S$，不然 $[l,r]$ 中必定有点要经过 $r+1$；其次要保证 $\text{path}(r,r+1)\cap S\not=\{r\}$，否则 $p$ 要想到 $r+1$ 就到不了 $[l,r]$ 了；最后还要保证 $\text{path}(r,r+1)\cap[l,r]=\{r\}$，因为不能经过区间内其它的点。

有一个性质：$S=\bigcup\limits_{i=l}^{r-1}\text{path}(i,i+1)$，这个就是 NOIP 2024 T4 那个结论。

那么就变成链上加链上和了，树剖或者 GBST 都可以做。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, q, fa[N], dep[N], siz[N], son[N], tot, dfn[N], top[N], R[N], D[N];
vector<int> G[N];
void dfs1(int u, int f) {
	fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
	for (int v : G[u]) if (v != f) { dfs1(v, u), siz[u] += siz[v]; if (siz[v] > siz[son[u]]) son[u] = v; }
}
void dfs2(int u, int f) {
	dfn[u] = ++tot, top[u] = f;
	if (son[u]) dfs2(son[u], f);
	for (int v : G[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
}
struct seg {
	int t[N << 2], tag[N << 2];
	#define lc p << 1
	#define rc lc | 1
	#define rt 1, 1, n
	#define Lc lc, l, mid
	#define Rc rc, mid + 1, r
	void psd(int p, int l, int r, int mid) {
		if (tag[p]) t[lc] += (mid - l + 1) * tag[p], tag[lc] += tag[p], t[rc] += (r - mid) * tag[p], tag[rc] += tag[p], tag[p] = 0;
	}
	void upd(int p, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) return t[p] += (r - l + 1) * x, tag[p] += x, void();
		int mid = (l + r) >> 1; psd(p, l, r, mid);
		if (L <= mid) upd(Lc, L, R, x); if (R > mid) upd(Rc, L, R, x); t[p] = t[lc] + t[rc];
	}
	int qry(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return t[p];
		int mid = (l + r) >> 1, ans = 0; psd(p, l, r, mid);
		if (L <= mid) ans += qry(Lc, L, R); if (R > mid) ans += qry(Rc, L, R); return ans;
	}
} t1, t2;
int dis(int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += dep[u] - dep[top[u]] + 1, u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	return ans + dep[v] - dep[u];
}
void upd(seg &t, int u, int v, int x) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		t.upd(rt, dfn[top[u]], dfn[u], x), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	t.upd(rt, dfn[u], dfn[v], x);
}
int qry(seg &t, int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += t.qry(rt, dfn[top[u]], dfn[u]), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	return ans + t.qry(rt, dfn[u], dfn[v]);
}
void mdf(int u, int v, int x) { t2.upd(rt, dfn[v], dfn[v], x); if (u && u <= n) upd(t1, u, v, x); }
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1, u, v; i < n; i++) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
	dfs1(1, 0), dfs2(1, 1);
	for (int l = 1, r = 0; l <= n; l++) {
		while (r < n) {
			bool flg = 0;
			if (l >= r) flg = 1;
			else {
				flg = !t1.qry(rt, dfn[r + 1], dfn[r + 1]);
				flg = flg && (qry(t1, r, r + 1) != t1.qry(rt, dfn[r], dfn[r]));
				flg = flg && (qry(t2, r, r + 1) == t2.qry(rt, dfn[r], dfn[r]));
			}
			if (!flg) break;
			mdf(r, r + 1, 1), r++;
		}
		R[l] = r, mdf(l + 1, l, -1);
	}
	for (int i = 1; i < n; i++) D[i] = dis(i, i + 1);
	int l, r;
	while (q--) {
		cin >> l >> r;
		if (l == r) cout << "Yes\n";
		else if (l == r - 1 && D[l] == 1) cout << "No\n";
		else cout << (r <= R[l] ? "Yes\n" : "No\n");
	}
}
```

---

## 作者：cosf (赞：2)

没想到竟然把 $O(n^2)$ 放过了。以后有时间再来造 hack 吧。

---

下面用 $[l, r]$ 表示点 $l, l + 1, \dots, r$ 组成的点集，$\text{path}(i, j)$ 表示点 $i$ 到点 $j$ 最短路径经过的点集，$\text{dis}(i, j) = |\text{path}(i, j)|$。

首先我们先转化题意：

> 给定一个 $n$ 个点的树，每次询问给定区间 $[l, r]$，求是否存在一个一个异于 $[l, r]$ 且在 $[l, r]$ 最小连通块中的点 $p$。
>
> 还有一个特例：当 $l = r$ 时，唯一满足的点 $p = l$，输出 `Yes`。

不难发现，其必要条件是 $[l, r]$ 中不存在三点共链。除此之外，如果 $r \gt l + 1$ 或者 $\text{dis}(l, l + 1) \ge 3$，则能反推出 $p$ 的存在性。因此考虑是否存在三点共链。

令 $r_i$ 表示最大的 $r$，使得点 $i, i + 1, \dots, r$ 中不存在三点共链。显然，$[l, r]$ 不存在三点共链等价于 $r \le r_l$。并且，$r_i$ 存在单调性。证明：考虑反证，若存在 $i \lt j, r_j \lt r_i$，则 $j, \dots, r_j + 1$ 中存在三点共链，$i, r_i$ 也必然存在，矛盾。所以我们可以使用双指针来求。

假设当前区间为 $[l, r]$。我们可以维护两种点权 $T_1, T_2$。$T_1$ 将 $\text{path}(i, i + 1), \forall l \le i \lt r$ 赋为非零值，$T_2$ 将 $i, \forall l \le i \le r$ 赋为 $1$。当我们想判断 $r + 1$ 的加入是否会导致三点共链时，只需检查三个东西：

- $T_1$ 中 $r+1$ 为 $0$。
- $T_1$ 中 $\text{path}(r, r + 1)$ 和不为 $r$ 的点权。
- $T_2$ 中 $\text{path}(r, r + 1)$ 和为 $r$ 的点权。

确认不会造成共链后，更新相应的权值即可。它的正确性利用了一个引理：

> $\bigcup_{i=l}^{r - 1}\text{path}(i, i + 1) = \bigcup_{i, j \in [l, r]}\text{path}(i, j)$。

这个引理的证明可以通过对每一条边计算贡献得到。具体证明就是分类讨论，就不写了。注：如果只有两个点则一定满足，不需要前面三条条件。

因此这部分是可以做到 $O(n\log^2 n)$ 的。最终的复杂度是 $O(n\log^2n + q\log n)$。当然计算 $\text{dis}(l, l + 1)$ 可以丢到预处理，这样就关于 $q$ 线性了。

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100005

using ll = long long;

int n, q;

struct SegTree
{
    struct Tree
    {
        ll s, t;
    } t[MAXN << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)

    void pushup(int p)
    {
        t[p].s = t[ls].s + t[rs].s;
    }

    void pushdown(int p, int l, int r)
    {
        if (t[p].t)
        {
            int mid = (l + r) >> 1;
            t[ls].s += (mid - l + 1) * t[p].t;
            t[ls].t += t[p].t;
            t[rs].s += (r - mid) * t[p].t;
            t[rs].t += t[p].t;
            t[p].t = 0;
        }
    }

    void add(int p, int l, int r, int ql, int qr, ll v)
    {
        if (ql <= l && r <= qr)
        {
            t[p].s += v * (r - l + 1);
            t[p].t += v;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (mid >= ql)
        {
            add(ls, l, mid, ql, qr, v);
        }
        if (mid < qr)
        {
            add(rs, mid + 1, r, ql, qr, v);
        }
        pushup(p);
    }

    ll query(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return t[p].s;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        ll res = 0;
        if (mid >= ql)
        {
            res += query(ls, l, mid, ql, qr);
        }
        if (mid < qr)
        {
            res += query(rs, mid + 1, r, ql, qr);
        }
        return res;
    }
} T1, T2;

vector<int> e[MAXN];

int fa[MAXN], son[MAXN], sz[MAXN], dep[MAXN];
int top[MAXN], rnk[MAXN], dfn[MAXN], idx = 0;

void dfs1(int p, int f)
{
    fa[p] = f;
    sz[p] = 1;
    dep[p] = dep[f] + 1;
    for (int u : e[p])
    {
        if (u == f)
        {
            continue;
        }
        dfs1(u, p);
        sz[p] += sz[u];
        if (sz[u] > sz[son[p]])
        {
            son[p] = u;
        }
    }
}

void dfs2(int p, int t)
{
    top[p] = t;
    dfn[p] = ++idx;
    rnk[idx] = p;
    if (!son[p])
    {
        return;
    }
    dfs2(son[p], t);
    for (int u : e[p])
    {
        if (u == fa[p] || u == son[p])
        {
            continue;
        }
        dfs2(u, u);
    }
}

void addPath(int u, int v, int w, SegTree &t) // 我也不知道我为什么要写三遍 lca
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            swap(u, v);
        }
        t.add(1, 1, n, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    t.add(1, 1, n, dfn[v], dfn[u], w);
}

ll queryPath(int u, int v, SegTree &t)
{
    ll res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            swap(u, v);
        }
        res += t.query(1, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    return res + t.query(1, 1, n, dfn[v], dfn[u]);
}

int dis(int u, int v)
{
    int res = dep[u] + dep[v];
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            swap(u, v);
        }
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
    {
        swap(u, v);
    }
    return res - 2 * dep[v];
}

int las[MAXN];

bool check(int l, int r)
{
    if (l + 2 > r)
    {
        return true;
    }
    return !T1.query(1, 1, n, dfn[r], dfn[r]) &&
           (queryPath(r - 1, r, T1) != T1.query(1, 1, n, dfn[r - 1], dfn[r - 1])) &&
           (queryPath(r - 1, r, T2) == T2.query(1, 1, n, dfn[r - 1], dfn[r - 1]));
}

void add(int l, int r, int w)
{
    T2.add(1, 1, n, dfn[r], dfn[r], w);
    if (l && l <= n)
    {
        addPath(l, r, w, T1);
    }
}

int main()
{
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    for (int l = 1, r = 0; l <= n; l++)
    {
        while (r < n && check(l, r + 1))
        {
            r++;
            add(r - 1, r, 1);
        }
        las[l] = r;
        add(l + 1, l, -1);
    }
    for (int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        if (l == r)
        {
            cout << "Yes" << endl;
        }
        else if (r > las[l])
        {
            cout << "No" << endl;
        }
        else if (r > l + 1 || dis(l, r) > 1)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}

```

---

