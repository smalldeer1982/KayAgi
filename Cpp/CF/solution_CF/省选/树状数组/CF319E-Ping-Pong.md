# Ping-Pong

## 题目描述

In this problem at each moment you have a set of intervals. You can move from interval $ (a,b) $ from our set to interval $ (c,d) $ from our set if and only if $ c 
< a < d $ or $ c < b < d $ . Also there is a path from interval $ I_{1} $ from our set to interval $ I_{2} $ from our set if there is a sequence of successive moves starting from $ I_{1} $ so that we can reach $ I_{2} $ .

Your program should handle the queries of the following two types:

1. "1 x y" $ (x&lt;y) $ — add the new interval $ (x,y) $ to the set of intervals. The length of the new interval is guaranteed to be strictly greater than all the previous intervals.
2. "2 a b" $ (a≠b) $ — answer the question: is there a path from $ a $ -th (one-based) added interval to $ b $ -th (one-based) added interval?

Answer all the queries. Note, that initially you have an empty set of intervals.

## 样例 #1

### 输入

```
5
1 1 5
1 5 11
2 1 2
1 2 9
2 1 2
```

### 输出

```
NO
YES
```

# 题解

## 作者：yzy1 (赞：7)

## 前言

本题的所有做法均在将区间端点坐标离散化至 $O(n)$ 级别后进行，并在复杂度分析中认为 $n,m,l_i,r_i$ 同阶．

## 做法 $\textbf 1$

我会暴力！

分析题意，可以发现 $2$ 操作就是在判断有向图两点可达性，而 $1$ 操作是加边．

我们只要暴力加 $O(n^2)$ 条边，然后查询操作的时候暴力 DFS 判断是否连通就可以了！

时空复杂度：$O(n^2)$，显然不能通过此题．

## 做法 $\textbf 2$

观察一下这个题的性质．我们发现，两个区间 $R_1=(l_1,r_1)$ 和 $R_2=(l_2,r_2)$，我们可以把它们及它们的并集之间的关系分为三种：

- $R_1 \cap R_2=R_1$ 或者 $R_1 \cap R_2=R_2$；
- $R_1 \cap R_2=\varnothing$；
- $R_1 \cap R_2 \notin \{R_1, R_2, \varnothing\}$．

对于第一种关系，我们从长度小的区间对应的点向长度大的区间对应的点连一条单向边；对于第三种关系，我们在这两个区间对应的点之间连双向边．

**结论** $\mathbf 1$：若 $i\to j$ 可达，则存在一条 $i\to j$ 的路径，满足路径上至多经过一条单向边，其它的边全是双向边．且若经过单向边，则单向边一定是路径上的第一条边．

> 证明：若有存在有向边 $i\to k, k \to j$，则有向边 $i\to j$ 必然存在，直接跳 $i\to j$ 即可．

**结论** $\mathbf 2$：对于图的每一个强连通子图 $S$，设 $L=\min_{(l',r') \in S} l', R=\max_{(l',r') \in S} r'$，$(l,r)$ 是图中一个不在 $S$ 中的点 $p$ 所属的一个区间，则：

$$
(L<l<R) \lor (L<r<R) \Leftrightarrow p\textsf{ 可达 } S.
$$

> 证明：考虑一个强连通子图一定不重不漏的覆盖了这个区间，那么考虑跨到区间的点 $k$，一定有一个区间覆盖了 $k$．那么就能跳到那个区间，即跳到强连通子图的所有区间了．

考虑数据结构维护从点 $i$ 所在的强连通分量 $S_i$ 及该强连通分量在**结论** $\mathbf 2$ 中对应的区间 $[L_i,R_i]$．假设要判断 $p$ 是否可达 $i$，则：

- 若 $p \in S_i$，即 $i,p$ 在同一强连通分量，则显然可达．
- 若 $(L_i<l<R_i) \lor (L_i<r<R_i)$，根据结论 $2$，$p$ 可达 $i$．
- 其余情况不可达．

考虑把每个 $1$ 操作加入的区间看作一个三维空间内的点 $(T_i,l_i,r_i)$，$T_i$ 表示该区间被加入的时间．问题转化为：$1$ 操作将 $i$ 向满足 $T_j < T_i, l_j < l_i, l_i < r_j < r_i$ 或 $T_j < T_i, l_i < l_j < r_i.r_i<r_j$ 的所有 $j$ 连一条无向边．这相当于一个点向一个三维矩形内的所有点加边，同时维护 $S_i,L_i,R_i$．

- 如果使用三维线段树和并查集来维护之，我们得到了一个复杂度和常数都巨大的 $O(n\log^3 n \alpha (n))$ 做法，显然无法通过此题．
- 如果使用 3-D Tree 和并查集维护之，我们得到了一个 $O(n^{5/3} \alpha(n))$ 的做法，具体表现未测试，如果有人使用了这个做法 AC 了请私信我．

## 做法 $\mathbf 3$

可以发现，题目中给出了一个性质：保证加入的区间长度严格单调递增，即新区间一定不会被旧区间包含．我们的**做法** $\textbf 2$ 并没有利用这个性质．

考虑把每个区间放到线段树上，线段树每个区间开一个 `std::vector`，每加入一个区间 $R=(l,r)$，就在线段树上对应的 $O(\log n)$ 个节点的 `std::vector` 里加入该区间的编号．

这样的话，若需要检查另外一个区间 $R'=(l',r')$ 是否满足 $R \cap R' \notin \{R, R', \varnothing\}$，只需要检查线段树上所有包含 $l'$ 或 $r'$ 的区间中的 `std::vector` 中有没有 $R$ 即可．

我们只需在每次 $1$ 操作加入区间 $R$ 时，首先检查所有满足上述条件的 $R'$，将 $R$ 和 $R'$ 在并查集上并起来，然后将 $R$ 加入线段树即可．

查询操作和**做法** $\textbf 2$ 类似，这里不再重复讲述．

时间复杂度 $O(n \log n \alpha(n))$，可以通过此题．

## 代码参考

见 [原始 OJ 提交](https://codeforces.com/contest/319/submission/212773508)．


---

## 作者：elbissoPtImaerD (赞：4)

对于两个区间，若他们包含，则连一条单向边，否则若相交，则连双向边。

感受一下，不会走超过一条单向包含边。这个反证也容易。

考虑图中两个 SCC $S_1: (L_1,R_1)$，$S_2: (L_2,R_2)$，猜测：$p \in S_1$ 可达 $S_2$ 等价于 $(L_1,R_1) \subseteq (L_2,R_2)$。

事实上是显然的：必要性就是走一条单向边，充分性则是 $S_1,S_2$ 必然不可能不包含地相交，否则就不是两个 SCC，不交更不行，所以只能是包含。

对于一次插入 $(l,r)$，我们只需维护其是否能并入若干个 SCC，即查询 $l,r$ 两点有何区间覆盖。这是因为题目保证了后插入的区间不会被前面的区间包含。

对于查询，我们只需维护两个点的 SCC 对应的 $L,R$ 判断即可。

使用并查集维护 SCC，线段树维护插入的区间覆盖、单点查询，可以做到 $O(\alpha(n)n\log n)$。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/319/submission/261988961)

---

## 作者：EuphoricStar (赞：4)

## 思路

首先这道题的询问“从第 $a$ 个区间移动到第 $b$ 个”让我们想到了并查集。区间与区间之间如果可移动就互相连边，因此回答询问只用判断 $a$ 和 $b$ 是否在同一连通分量中或者存在包含关系。

因此这道题的难点就在于如何“批量连边”。我们可以将左右端点离散化后使用线段树。对于每个连通分量的代表元，我们维护两个信息 $minl_i$，$maxr_i$ 分别代表这个连通分量覆盖的最左端点和最右端点。然后对于每条线段的左端点和右端点，我们可以在线段树上 dfs，遍历线段树上每个包含左端点或右端点的结点的“待处理线段”，合并集合的同时更新当前连通分量的 $minl_i$ 和 $maxr_i$。之后再把当前边加入线段树上被它包含的结点的“待处理线段”。

然后这题就可以在近似 $O(n \log n\ \alpha(n))$ 的时间复杂度内解决了。

## 代码

[code](https://pastebin.ubuntu.com/p/yczt5pFJ3Z/)

---

## 作者：pldzy (赞：3)

Happy New Year!

## Solution

### 1

考虑这样的 subtask 如何做：给定的区间保证互不包含。此时很简单，直接把有交的区间用并查集合并，查询时看两个区间是否在同一连通块即可。

为何区间包含会困难。不妨记 $D_a$ 被 $D_b$ 所包含。在上面的 subtask 中，这种“可达性”是双向的，但此时 $D_a \rightarrow D_b$，而 $D_b \nrightarrow D_a$。发现这种包含和相交关系可能会很复杂。

### 2

也许能沿用 subtask 的做法，即使只是优化一点？考虑依旧把相交的区间用并查集合并起来，意义依旧是同一连通块的区间互相可达。

此时若我们把合并到一起的区间看成一个大的连续区间：

- 这些新区间相互不可能相交；
- 这些新区间可能存在包含关系。

啊这就很好处理了哇。因为对于包含关系，那必然都是形如 $D_a \rightarrow D_b$ 这样的行走方式了。因为路程中非形如 $D_a \rightarrow D_b$ 的行走方式已经都被我们压入并查集的同一个连通块不予考虑了。

### 3

咋维护。这时候一直没用上的特殊性质“保证每次给出的区间长度单增”终于能用上了。

此时我们会把符合下述条件之一的大区间和新区间 $[l,r]$ 合并：

- 大区间 $[L,R]$ 和 $[l,r]$ 完全不相交；
- 大区间 $[L,R]$ 完全包含 $[l,r]$。

原因很简单吧。同时，特殊性质告诉我们，只要 $[L,R]$ 包含 $[l,r]$，则 $[l,r]$ 必然和其中某个小区间相交，也即这俩区间可以合并。反证法，如果不存在，说明存在某一个小区间完全包含了 $[l,r]$，但因为长度单增，所以不可能。

那直接用线段树维护一下覆盖到 $l$ 和 $r$ 的区间有哪些就行了。

## Code

复杂度就是单老哥，并查集懒得优化了，常数略大。

````cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define per(i, a, b) for(int i = (a); i >= (b); --i)
#define pii pair<int, int>
#define fi first
#define se second
#define mkp make_pair

const int maxn = 1e5 + 5, maxm = 1e6 + 6;

int n, b[maxm], m;
pii D[maxn], Q[maxn]; int op[maxn], fa[maxn], d;

inline void ckmn(int &x, int v){ if(v < x) x = v; }
inline void ckmx(int &x, int v){ if(v > x) x = v; }

inline int fnd(int x){
	return fa[x] == x ? x : fa[x] = fnd(fa[x]);
}

#define ls (x << 1)
#define rs (x << 1 | 1)

vector<int> t[maxn << 2];

inline void updtr(int x, int l, int r, int L, int R, int id){
	if(L > R) return;
	if(l >= L and r <= R) return t[x].push_back(id), void();
	int mid = l + r >> 1;
	if(L <= mid) updtr(ls, l, mid, L, R, id);
	if(R > mid) updtr(rs, mid + 1, r, L, R, id);
}

vector<int> A;
inline void qryp(int x, int l, int r, int p){
	for(int v : t[x]) A.push_back(v); t[x].clear();
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) qryp(ls, l, mid, p); else qryp(rs, mid + 1, r, p);
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	
	cin >> n;
	rep(i, 1, n) cin >> op[i] >> Q[i].fi >> Q[i].se, fa[i] = i;
	rep(i, 1, n) if(op[i] == 1) b[++m] = Q[i].fi, b[++m] = Q[i].se;
	
	sort(b + 1, b + m + 1);
	m = unique(b + 1, b + m + 1) - b - 1;
	rep(i, 1, n) if(op[i] == 1) 
		Q[i].fi = lower_bound(b + 1, b + m + 1, Q[i].fi) - b,
		Q[i].se = lower_bound(b + 1, b + m + 1, Q[i].se) - b;
	
	rep(i, 1, n){
		if(op[i] == 1){
			A.clear(); qryp(1, 1, m, Q[i].fi), qryp(1, 1, m, Q[i].se);
			++d;
			D[d].fi = Q[i].fi, D[d].se = Q[i].se;
			for(int x : A) 
				fa[x] = d, ckmn(D[d].fi, D[x].fi), ckmx(D[d].se, D[x].se);
			updtr(1, 1, m, D[d].fi + 1, D[d].se - 1, d);
		} else{
			int x = fnd(Q[i].fi), y = fnd(Q[i].se);
			if(x == y or (D[x].fi >= D[y].fi and D[x].se <= D[y].se)) cout << "YES" << '\n';
			else cout << "NO" << '\n';
		}
	}
	return 0;
}
````

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF319E)

## 思路

首先我们考虑连边，存在边 $u \rightarrow v$ 当且仅当区间 $u$ 能移动到区间 $v$。

不难发现如果 $u,v$ 连的是双向边那么 $u,v$ 相交且互不包含。

对于这些双向边，我们显然可以将边的两端合并到同一个等价类中，这样图就变成只有单向边的 DAG 了。

我们先忽略有向边，考虑使用数据结构维护这张 DAG 上的所有点，那么问题就是如何维护新加入的区间。

不难发现，由于 DAG 上每个点代表的等价类所覆盖的区间是连续的，所以点 $x$ 实际上相当于一个区间 $(mini_x,maxi_x)$，分别表示这个等价类中的最小左端点与最小右端点。

设新加入的区间是 $(L,R)$，DAG 上某个点 $x$ 能与新区间合并的条件就是 $L$ 或 $R$ 在 $x$ 的区间内。

又因为题目保证了加入的区间长度连续，因此我们不需要考虑当前区间被之前区间所包含的情况。

所以我们使用线段树维护 DAG 上每个点的区间，每次查询就是查找左端点 $<x$ 的所有区间中含有最大右端点的那个区间，然后判断是否合法，若合法则合并，然后将此区间删去，否则退出。

我们现在已经维护好了 DAG 上的点，接着我们观察 DAG 的形态，发现若存在边 $(x,y),(y,z)$，那么一定存在边 $(x,z)$。

因此对于一个询问 $(X,Y)$，我们只需要查询 $X$ 对应的等价类能否到达 $Y$ 对应的等价类即可。

这个判断比较简单，一种简单粗暴的办法就是在每个等价类维护一个 $\rm set$ 表示这个等价类的端点集合，判断 $X$ 能否到达 $Y$ 仅需在 $X$ 的 $\rm set$ 上查询是否存在 $(mini_Y,maxi_Y)$ 中的数即可。

时间复杂度是 $\Theta(n \log^2 n + n \alpha(n))$，如果使用线段树合并维护端点集合可以做到一只 $\log$。

## 代码

[提交记录](https://codeforces.com/problemset/submission/319/259939474)

---

## 作者：SunnyYuan (赞：1)

## 题意

如果两个线段相交（不包括端点），那么你可以从一个线段移动到另外一个线段。动态添加线段，询问能否从一个线段前往另外一个线段。

## 思路

我们不难想到利用 $scc$ 来解决点对之间的关系（经典例题《炸弹》），离散化后使用权值线段树保存点对关系。

具体来说，用有向边表示两个线段能相互影响，如果有个线段 $x$ 和另外一个线段 $y$ 相交（不包括端点），那么在 $x$ 和 $y$ 之间连接双向边，它们一定在一个 $scc$ 中；如果一个线段完全包含在一个线段之中，那么只有大线段能影响小线段，所以只从大线段连边到小线段。

这样我们跑完有向图缩点，一个 $scc$ 之中所有线段可以互相到达，而不同 $scc$ 之间的点只能走一些单向边相互联系。

而这个题目非常仁慈，“保证加入的区间长度严格单调递增”，所以如果后面的一个线段的一个端点在前面的一个区间之内，那它们一定相交而不被包含，它们一定在一个 $scc$ 之内。

因此我们不用真正把图建出来再跑强连通分量，用并查集维护强连通分量。当有新线段来时，将这条线段两个端点与所有线段进行比较，如果相交，则将起并入一个 $scc$，为了高效比较，将所有线段放入线段树进行处理。

对于询问，如果两条线段在一个 $scc$ 中，那么一定是 `YES`，如果两线段对应的 $scc$ 有包含关系，那么也是 `YES`，不可能出现其他情况，否则就被并入一个 $scc$ 了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100010;           // Be Happy

struct node {                   // Segment Tree
    vector<int> ver;
} tr[N << 2];

struct query {                  // record all queries
    int opt, a, b;
} q[N];

struct union_find {             // union find
    int fa[N];
    int l[N], r[N];             // record the 'l' and 'r' of all the segments in a scc
    
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        l[y] = min(l[y], l[x]);
        r[y] = max(r[y], r[x]);
        fa[x] = y;
    }

    union_find() { iota(fa, fa + N, 0); }// init
} f;

int l[N], r[N];             // record 'l' and 'r'

void add(int u, int l, int r, int x, int seg) { // merge a new segment and the old segments to a scc
    if (tr[u].ver.size()) {                     // merge
        while (tr[u].ver.size()) {
            f.merge(tr[u].ver.back(), seg);
            tr[u].ver.pop_back();
        }
        tr[u].ver.push_back(seg);
    }
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) add(u << 1, l, mid, x, seg);
    else add(u << 1 | 1, mid + 1, r, x, seg);
}

void addtag(int u, int l, int r, int pl, int pr, int seg) { // add a new segment into the Segment Tree
    if (pl <= l && r <= pr) {
        tr[u].ver.push_back(seg);
        return;
    }

    int mid = l + r >> 1;
    if (pl <= mid) addtag(u << 1, l, mid, pl, pr, seg);
    if (pr > mid) addtag(u << 1 | 1, mid + 1, r, pl, pr, seg);
}

int n;

void solve() {
    cin >> n;
    vector<int> data;
    for (int i = 1; i <= n; i++) {
        cin >> q[i].opt >> q[i].a >> q[i].b;
        if (q[i].opt == 1) {
            data.emplace_back(q[i].a);
            data.emplace_back(q[i].b);
        }
    }

    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()), data.end());

    for (int i = 1; i <= n; i++) {                              // Discretization [刚学的]（离散化）
        if (q[i].opt == 1) {
            q[i].a = lower_bound(data.begin(), data.end(), q[i].a) - data.begin() + 1;
            q[i].b = lower_bound(data.begin(), data.end(), q[i].b) - data.begin() + 1;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (q[i].opt == 1) {
            cnt++;
            l[cnt] = f.l[cnt] = q[i].a, r[cnt] = f.r[cnt] = q[i].b;
            add(1, 1, data.size(), q[i].a, cnt);
            add(1, 1, data.size(), q[i].b, cnt);
            if (q[i].a + 1 <= q[i].b - 1) addtag(1, 1, data.size(), q[i].a + 1, q[i].b - 1, cnt);
        }
        else {
            int fa = f.find(q[i].a);
            int fb = f.find(q[i].b);
            if (fa == fb || (f.l[fb] <= f.l[fa] && f.r[fa] <= f.r[fb] && (l[fa] != f.l[fb] || r[fa] != f.r[fb]))) cout << "YES\n";// if the segment is in other segments or it is in a scc, output "YES"
            else cout << "NO\n"; 
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
```

---

