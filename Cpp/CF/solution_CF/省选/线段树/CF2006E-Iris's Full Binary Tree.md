# Iris's Full Binary Tree

## 题目描述

Iris likes full binary trees.

Let's define the depth of a rooted tree as the maximum number of vertices on the simple paths from some vertex to the root. A full binary tree of depth $ d $ is a binary tree of depth $ d $ with exactly $ 2^d - 1 $ vertices.

Iris calls a tree a  $ d $ -binary tree if some vertices and edges can be added to it to make it a full binary tree of depth $ d $ . Note that any vertex can be chosen as the root of a full binary tree.

Since performing operations on large trees is difficult, she defines the binary depth of a tree as the minimum $ d $ satisfying that the tree is $ d $ -binary. Specifically, if there is no integer $ d \ge 1 $ such that the tree is $ d $ -binary, the binary depth of the tree is $ -1 $ .

Iris now has a tree consisting of only vertex $ 1 $ . She wants to add $ n - 1 $ more vertices to form a larger tree. She will add the vertices one by one. When she adds vertex $ i $ ( $ 2 \leq i \leq n $ ), she'll give you an integer $ p_i $ ( $ 1 \leq p_i < i $ ), and add a new edge connecting vertices $ i $ and $ p_i $ .

Iris wants to ask you the binary depth of the tree formed by the first $ i $ vertices for each $ 1 \le i \le n $ . Can you tell her the answer?

## 说明/提示

In the first test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)- The tree consisting of the vertex $ 1 $ has the binary depth $ 1 $ (the tree itself is a full binary tree of depth $ 1 $ ).
- The tree consisting of the vertices $ 1 $ and $ 2 $ has the binary depth $ 2 $ (we can add the vertex $ 3 $ to make it a full binary tree of depth $ 2 $ ).
- The tree consisting of the vertices $ 1 $ , $ 2 $ and $ 3 $ has the binary depth $ 2 $ (the tree itself is a full binary tree of depth $ 2 $ ).

In the second test case, the formed full binary tree after adding some vertices to the tree consisting of $ n $ vertices is shown below (bolded vertices are added):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/90faca99e1781d73f69b5b60a32aa2a2da38a68c.png)The depth of the formed full binary tree is $ 4 $ .

In the fifth test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/2c0d039efae462812828b42368688f46ffc8b41e.png)It can be proved that Iris can't form any full binary tree by adding vertices and edges, so the binary depth is $ -1 $ .

## 样例 #1

### 输入

```
7
3
1 1
6
1 2 3 4 5
7
1 1 3 2 5 1
10
1 1 2 1 4 2 4 5 8
10
1 1 3 1 3 2 2 2 6
20
1 1 2 2 4 4 5 5 7 6 8 6 11 14 11 8 13 13 12
25
1 1 3 3 1 5 4 4 6 8 11 12 8 7 11 13 7 13 15 6 19 14 10 23```

### 输出

```
1 2 2 
1 2 2 3 3 4 
1 2 2 3 3 4 4 
1 2 2 3 3 3 4 4 5 5 
1 2 2 3 3 4 4 4 -1 -1 
1 2 2 3 3 4 4 4 4 5 5 5 5 6 6 6 6 6 6 7 
1 2 2 3 3 4 4 4 4 5 5 6 6 6 6 6 7 7 7 7 7 8 8 8 8```

# 题解

## 作者：Conan15 (赞：3)

第一眼感觉动态加点维护答案是困难的，所以先来考虑一下静态问题。

一个较为简单的做法是枚举根在哪里，然后树的深度就是距离根**最远**点的距离。\
而且还要满足**可以构成二叉树**，即需要满足如下两个性质：

- 根节点的 $deg \leq 2$。
- 其余节点的 $deg \leq 3$。（$deg$ 表示节点度数）

然后我们再试图优化一下枚举根的过程，发掘一下性质，会发现：距离 $u$ 最远的点距离相当于 $u$ 先到达树的中心 $c$ 的距离再加上直径的一半。\
证明如下：

> 显然最远点一定是直径端点之一。\
> 那么相当于 $u$ 先从某个点 $v$ 进入直径，然后再走到更远的端点。\
> 可以想到把从 $v$ 到中心 $c$ 点的路径合并进 $u$ 到 $v$ 的路径里，就变成了 $u$ 到中心 $c$ 再加上直径一半。

对于静态问题，直径的一半是定值，那么我们只要求出距离中心最近的 $deg \leq 2$ 的点即可，这一问题可以直接 dfs 用 $O(n)$ 的时间复杂度求解。


----------


考虑如何解决动态问题。首先要解决动态求中心的问题，即动态维护直径。\
容易发现加入一个节点 $u$ 的时候，只需要把它**到直径两端点**的距离分别的当前直径长度比较即可。中心可以倍增跳，不过有较为简单的维护方法：

观察到每次加入点，中心移动距离不会超过 $0.5$，即它要么在点上要么在一条树边的中心。\
所以我们只要动态维护当前的树中心，维护方法是记录一个二元组 $(u,v)$，如果 $u=v$ 表示中心在点 $u$ 上，否则表示在 $(u,v)$ 边的中点上。

接下来就不能直接用 dfs 求最近点了，怎么办呢？\
好像直接把树拍扁成 dfs 序然后线段树维护就好了呢。

~~代码写的就很魔怔。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 15, M = N << 1, INF = 0x3f3f3f3f;
int T, n, p[N];
int h[N], e[M], ne[M], idx = 0;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

struct SegmentTree {    //线段树内维护每个点到最远点的距离
    struct Tree {
        int l, r;
        int Min, flag;
    } tr[N << 2];
    void pushup(int u) { tr[u].Min = min(tr[u << 1].Min, tr[u << 1 | 1].Min); }
    void pushdown(int u) {
        if (tr[u].flag) {
            tr[u << 1].flag += tr[u].flag;
            tr[u << 1 | 1].flag += tr[u].flag;
            tr[u << 1].Min += tr[u].flag;
            tr[u << 1 | 1].Min += tr[u].flag;
            tr[u].flag = 0;
        }
    }
    void build(int u, int l, int r) {
        tr[u].l = l, tr[u].r = r, tr[u].flag = 0;
        if (l == r) {
            if (l == 1) tr[u].Min = 0;
            else tr[u].Min = INF;
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void change(int u, int x, int d) {  //单点改
        if (tr[u].l == tr[u].r) return tr[u].Min = d, void();
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) change(u << 1, x, d);
        else change(u << 1 | 1, x, d);
        pushup(u);
    }
    void add(int u, int l, int r, int d) {  //区间加
        if (l > r || tr[u].r < l || tr[u].l > r) return;
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].Min += d, tr[u].flag += d;
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) add(u << 1, l, r, d);
        if (r > mid) add(u << 1 | 1, l, r, d);
        pushup(u);
    }
    int query() { return tr[1].Min; }
} tr;

int fa[N][25], dep[N], sz[N];
int dfn[N], tot = 0;
void dfs(int u) {
    dfn[u] = ++tot, sz[u] = 1;
    dep[u] = dep[p[u]] + 1, fa[u][0] = p[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == p[u]) continue;
        dfs(v);
        sz[u] += sz[v];
    }
}
int lca(int u, int v) {
    if (u == v) return u;
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    for (int i = 20; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
int getk(int u, int k) {
    for (int i = 20; i >= 0; i--)
        if (k & (1 << i)) u = fa[u][i];
    return u;
}
int deg[N];

int a, b, r;    //中心二元组 (a,b)、树的半径
void clr() {
    a = b = 1, r = 0;
    for (int i = 1; i <= n; i++) h[i] = -1, deg[i] = 0;
    idx = tot = 0;
}
void init() {
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= n; j++) fa[j][i] = fa[fa[j][i - 1]][i - 1];
}
void move(int &a, int x) {  //a 往 x 走一步（这之前要特判是否需要移动）
    int l = lca(a, x);
    if (l == a) {   //x in subtree(a)
        tr.add(1, 1, n, 1);
        a = getk(x, dep[x] - dep[a] - 1);
        tr.add(1, dfn[a], dfn[a] + sz[a] - 1, -1);
    } else {
        tr.add(1, dfn[a], dfn[a] + sz[a] - 1, 1);
        a = p[a];
    }
}

int insert(int x) { //返回 x 点的最远距离
    if (a == b) {   //单点中心
        int d = dis(a, x);
        if (d <= r) return d + r;
        move(a, x);
        r++;
        return r * 2 - 1;
    } else {    //边上中心
        int da = dis(a, x), db = dis(b, x), mx = max(da, db);
        if (mx <= r) return mx + r - 1;
        //此时要把更远的端点移过去
        if (da > db) move(a, x);
        else move(b, x);
        return r * 2;
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        clr();
        for (int i = 2; i <= n; i++) scanf("%d", &p[i]), add(i, p[i]), add(p[i], i);
        dfs(1), init();
        tr.build(1, 1, n);

        printf("1 ");
        bool flag = 0;
        for (int i = 2; i <= n; i++) {
            if (flag) { printf("-1 "); continue; }
            deg[p[i]]++, deg[i] = 1;

            int far = insert(i);
            tr.change(1, dfn[i], far);
            if (deg[p[i]] >= 3) {
                if (deg[p[i]] == 3) tr.change(1, dfn[p[i]], INF); // deg>=3 的不能作为根节点，所以默认距离为 INF
                else { printf("-1 "); flag = 1; continue; }  //出现度数 >=4 显然不能构成二叉树
            }
            // cout << '\t' << i << ' ' << a << ' ' << b << endl;
            printf("%d ", tr.query() + 1);  //本题中根节点深度为 1
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2006E)

**题目大意**

> 定义一棵树的权值为最小的 $k$ 使得该树是高度为 $k$ 的满二叉树的导出子图。
>
> 给一棵 $n$ 个点的树，对于 $i=1\sim n$，求 $1\sim i$ 点的导出子图的权值。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

刻画一棵树的权值，显然这棵树过二叉树的根，且不能有 $\ge4$ 度点。

我们发现只要根节点是 $\le 2$ 度点，其他点度数无限制。

显然根不可能是 $1$ 度点因此一棵树的权值就是所有 $2$ 度点到其他点距离最大值的最小值。

取出树的中心，容易发现最优的 $2$ 度点就是离中心最近的一个。

那么在树上不断加点，中心每次至多移动 $0.5$ 的距离。

每次中心移动都是对某个子树内或子树外的距离 $\pm 1$，可以 dfn 序上线段树维护，对于未加入的点以及 $3$ 度点，直接将距离设成 $\infty$，加入该点的时候直接求出距离即可。

此时答案就是线段树上的最小值。

时间复杂度 $\mathcal  O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5,inf=1e9;
int n;
struct SegmentTree {
	int tr[MAXN<<2],tg[MAXN<<2];
	void psu(int p) { tr[p]=min(tr[p<<1],tr[p<<1|1]); }
	void adt(int p,int k) { tg[p]+=k,tr[p]+=k; }
	void psd(int p) { adt(p<<1,tg[p]),adt(p<<1|1,tg[p]),tg[p]=0; }
	void init(int l=1,int r=n,int p=1) {
		tr[p]=inf,tg[p]=0;
		if(l==r) return ;
		int mid=(l+r)>>1;
		init(l,mid,p<<1),init(mid+1,r,p<<1|1);
	}
	void set(int u,int k,int l=1,int r=n,int p=1) {
		if(l==r) return tr[p]=k,void();
		int mid=(l+r)>>1; psd(p);
		u<=mid?set(u,k,l,mid,p<<1):set(u,k,mid+1,r,p<<1|1);
		psu(p);
	}
	void add(int ul,int ur,int k,int l=1,int r=n,int p=1) {
		if(ul>ur) return ;
		if(ul<=l&&r<=ur) return adt(p,k);
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) add(ul,ur,k,l,mid,p<<1);
		if(mid<ur) add(ul,ur,k,mid+1,r,p<<1|1);
		psu(p);
	}
}	T;
vector <int> G[MAXN];
int fa[MAXN],L[MAXN],R[MAXN],dep[MAXN],st[MAXN][20],dcnt;
void dfs(int u) {
	dep[u]=dep[fa[u]]+1,L[u]=++dcnt,st[dcnt][0]=fa[u];
	for(int v:G[u]) dfs(v);
	R[u]=dcnt;
}
int bit(int x) { return 1<<x; }
int cmp(int x,int y) { return L[x]<L[y]?x:y; }
int LCA(int x,int y) {
	if(x==y) return x;
	int l=min(L[x],L[y])+1,r=max(L[x],L[y]),k=__lg(r-l+1);
	return cmp(st[l][k],st[r-bit(k)+1][k]);
}
int dis(int x,int y) { return dep[x]+dep[y]-2*dep[LCA(x,y)]; }
int nxt(int x,int y) {
	if(L[x]<=L[y]&&L[y]<=R[x]) {
		return *--upper_bound(G[x].begin(),G[x].end(),y,[&](int i,int j){ return L[i]<L[j]; });
	}
	return fa[x];
}
int u,v,x,y,deg[MAXN];
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) G[i].clear(),deg[i]=0;
	for(int i=2;i<=n;++i) cin>>fa[i],G[fa[i]].push_back(i);
	dcnt=0,dfs(1);
	for(int k=1;k<20;++k) for(int i=1;i+bit(k)-1<=n;++i) {
		st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	}
	u=v=x=y=1,T.init(),T.set(1,0),cout<<"1 ";
	for(int p=2;p<=n;++p) {
		++deg[fa[p]],++deg[p];
		T.set(L[p],min(dis(p,x),dis(p,y)));
		if(deg[fa[p]]>3) {
			for(int i=p;i<=n;++i) cout<<"-1 ";
			cout<<"\n";
			return ;
		}
		if(deg[fa[p]]==3) T.set(L[fa[p]],inf);
		if(dis(u,p)<dis(v,p)) swap(u,v),swap(x,y);
		if(dis(u,p)>dis(u,v)) {
			if(x!=y) {
				if(fa[x]==y) T.add(L[x],R[x],1);
				else T.add(1,L[y]-1,1),T.add(R[y]+1,n,1);
				x=y;
			} else {
				y=nxt(y,p);
				if(fa[y]==x) T.add(L[y],R[y],-1);
				else T.add(1,L[x]-1,-1),T.add(R[x]+1,n,-1);
			}
			v=p;
		}
		cout<<T.tr[1]+(dis(u,v)+1)/2+1<<" ";
	}
	cout<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：irris (赞：1)

## Preface

> 直径 / DFS 序 / 线段树 / Top Tree

~~如此美味多汁的题目。~~

1600，出题人题解。

## Solution

> **引理 1**：树上到某个点距离最大的点，其中之一一定为某条直径的两个端点之一。  
> **引理 2**：在两棵树之间连一条边，以此合并两棵树。我们在合并前，对每一棵树取出一条直径，得到两个端点。对于新树，至少有一条新直径，其端点在四个直径端点中产生。

为节省篇幅，不在此处展开证明。

我们考虑前 $k$ 个点组成的子树，它对应在那棵深度为 $d$ 的满二叉树上，一定有且仅有一个深度最小的节点（否则，这就不联通了）。如果深度最小的节点深度大于 $1$，那么我们可以将所有节点的深度减少 $1$，容易发现这样不会产生冲突，而 $d$ 应减少 $1$。于是：

> **结论 1**：一定有一个节点对应为满二叉树的根。

同时，由于满二叉树的度数，得到：

> **结论 2**：这个对应为根的节点应满足度数 $\leq 2$；若存在度数 $\gt 3$ 的节点，那么这个 $k$ 及之后的所有询问，应当有 $d = -1$。

我们不妨考虑以每个点为根的情况，由于 **引理 1**，可以得到 $d$ 为该点到两个直径端点的距离最大值再加 $1$。选取让这个最大值最小的度数 $\leq 2$ 的点为根即可。

暴力做法可以做到 $\mathcal O(n^2)$。考虑优化。

根据 **引理 2**，每次加入一个点后，直径长度要么不变，要么增加 $1$。在增加 $1$ 的情况中，我们上文提及的，考察所有点的距离最大值（暂时忽视其度数）。

如果我们考虑了实时维护其变化，那么比较显然的是：若新直径距离为偶数，相当于，对除新直径中点的某棵子树外所有点该最大距离均 $+1$；否则相当于对原直径中点的子树所有点最大距离 $+1$。注意上文中的子树，其中整棵树的树根为可变的，不过这无关紧要。

我们可以把所有节点按照 DFS 序遍历编号，这样每个点的子树都在一个区间内，因此 **不定根的子树也可以用 $\bm{\mathcal O(1)}$ 个区间表示**。可以用线段树方便维护上文中的 $+1$ 操作。

此外，考虑到度数的影响，只需要对所有度数变为 $3$ 的节点的距离增加 $+\infin$ 即可，这是同样容易做到的。最终，每次操作结束只需要查询全局最小值。

时间复杂度 $\mathcal O(\sum n\log n)$。

---

