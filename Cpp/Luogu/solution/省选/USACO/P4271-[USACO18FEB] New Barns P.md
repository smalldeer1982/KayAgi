# [USACO18FEB] New Barns P

## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。

## 说明/提示

【数据范围】  

对于 $100\%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu

## 样例 #1

### 输入

```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2```

### 输出

```
0
2
1
```

# 题解

## 作者：ywy_c_asm (赞：13)

这个做法不仅能支持加边，还能支持删边。

考虑直接在LCT上查询最大的深度，像我们维护子树$size$那样我们在每个点上开个可删堆或者set维护轻儿子的子树内的最大深度，由于轻边实际上是父亲与这棵Splay上深度最小的点连的边，我们设$f[i]$为从i这棵**Splay子树**内深度最小的点往下的最大深度，当然，由于我们的Splay需要支持翻转操作，我们还要维护一个转移顺序和$f[i]$完全相反的$g[i]$，即把这个Splay完全翻转过来之后，现在深度最小的点是原来深度最大的点，从这个点“往下”的最大深度，那么翻转的时候$swap$一下$f$和$g$即可。

考虑$f$的转移，首先显然有$f[i]=max(f[i],f[ch[i][0]])$，这个可能在深度小于$i$的部分就转到了轻儿子上，当然还可能把$i$上面的一部分都取了，可以转到$i$下面的部分：$f[i]=max(f[i],f[ch[i][1]]+size[ch[i][0]])$，还可以在$i$转到轻儿子上：$f[i]=max(f[i],size[ch[i][0]]+heap[i].top())$，（$heap[i].top()$是维护轻儿子的堆的堆顶）。然后access和link的时候注意维护堆。$O(n\log^2n)$。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 100011
#define opp(_o) (_o == ch[fa[_o]][1])
#define isroot(_o) (_o != ch[fa[_o]][1] && _o != ch[fa[_o]][0])
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int ch[N][2], fa[N], size[N], mxzheng[N], mxfan[N], stk[N];
	unsigned char bj[N];
	typedef struct _heap {
	    priority_queue<int> me, del;
	    inline int top() {
	        while (!me.empty() && !del.empty() && me.top() == del.top()) me.pop(), del.pop();
	        if (me.empty())
	            return (0);
	        return (me.top());
	    }
	    inline int empty() {
	        while (!me.empty() && !del.empty() && me.top() == del.top()) me.pop(), del.pop();
	        return (me.empty());
	    }
	    inline void push(int x) {
	        me.push(x);
	    }
	    inline void erase(int x) {
	        del.push(x);
	    }
	} heap;
	heap hp[N];
	inline void down(int tree) {
	    if (!bj[tree])
	        return;
	    swap(mxzheng[ch[tree][0]], mxfan[ch[tree][0]]);
	    bj[tree] = 0;
	    swap(mxzheng[ch[tree][1]], mxfan[ch[tree][1]]);
	    swap(ch[tree][0], ch[tree][1]);
	    bj[ch[tree][0]] ^= 1;
	    bj[ch[tree][1]] ^= 1;
	}
	inline void up(int tree) {
	    size[tree] = size[ch[tree][0]] + size[ch[tree][1]] + 1;
	    mxzheng[tree] = mxfan[tree] = hp[tree].top();
	    if (ch[tree][0]) {
	        mxzheng[tree] = max(mxzheng[tree], mxzheng[ch[tree][0]]);
	        mxfan[tree] = max(mxfan[tree], mxfan[ch[tree][0]] + 1 + size[ch[tree][1]]);
	        mxzheng[tree] = max(mxzheng[tree], size[ch[tree][0]]);
	        if (!hp[tree].empty()) {
	            mxzheng[tree] = max(mxzheng[tree], size[ch[tree][0]] + hp[tree].top());
	        }
	    }
	    if (ch[tree][1]) {
	        mxzheng[tree] = max(mxzheng[tree], mxzheng[ch[tree][1]] + 1 + size[ch[tree][0]]);
	        mxfan[tree] = max(mxfan[tree], mxfan[ch[tree][1]]);
	        mxfan[tree] = max(mxfan[tree], size[ch[tree][1]]);
	        if (!hp[tree].empty()) {
	            mxfan[tree] = max(mxfan[tree], size[ch[tree][1]] + hp[tree].top());
	        }
	    }
	    if (ch[tree][0] && ch[tree][1]) {
	        mxzheng[tree] = max(mxzheng[tree], size[ch[tree][0]] + 1 + mxzheng[ch[tree][1]]);
	        mxfan[tree] = max(mxfan[tree], size[ch[tree][1]] + 1 + mxfan[ch[tree][0]]);
	    }
	    if (!hp[tree].empty()) {
	        mxzheng[tree] = max(mxzheng[tree], hp[tree].top() + size[ch[tree][0]]);
	        mxfan[tree] = max(mxfan[tree], hp[tree].top() + size[ch[tree][1]]);
	    }
	}
	inline void xuan(int me) {
	    int tree = fa[me], cjr = fa[tree];
	    down(cjr);
	    down(tree);
	    down(me);
	    int op = opp(me), ls = ch[me][op ^ 1];
	    ch[tree][op] = ls;
	    fa[ls] = tree;
	    ch[me][op ^ 1] = tree;
	    if (!isroot(tree))
	        ch[cjr][opp(tree)] = me;
	    fa[tree] = me;
	    fa[me] = cjr;
	    up(tree);
	    up(me);
	}
	inline void splay(int tree) {
	    if (isroot(tree)) {
	        down(tree);
	        return;
	    }
	    int tmp = tree, sp = 0;
	    while (!isroot(tmp)) stk[sp] = tmp, sp++, tmp = fa[tmp];
	    down(tmp);
	    while (sp) sp--, down(stk[sp]);
	    while (!isroot(tree)) {
	        int cjr = fa[tree];
	        if (!isroot(cjr))
	            xuan((opp(cjr) == opp(tree)) ? cjr : tree);
	        xuan(tree);
	    }
	    up(tree);
	}
	inline void access(int tree) {
	    splay(tree);
	    down(tree);
	    if (ch[tree][1]) {
	        hp[tree].push(mxzheng[ch[tree][1]] + 1);
	        ch[tree][1] = 0;
	        up(tree);
	    }
	    while (fa[tree]) {
	        int cjr = fa[tree];
	        splay(cjr);
	        down(cjr);
	        if (ch[cjr][1]) {
	            hp[cjr].push(mxzheng[ch[cjr][1]] + 1);
	            ch[cjr][1] = 0;
	            up(cjr);
	        }
	        hp[cjr].erase(mxzheng[tree] + 1);
	        ch[cjr][1] = tree;
	        up(cjr);
	        splay(tree);
	    }
	    up(tree);
	}
	inline void makeroot(int tree) {
	    access(tree);
	
	    splay(tree);
	    bj[tree] ^= 1;
	    swap(mxzheng[tree], mxfan[tree]);
	}
	inline void link(int a, int b) {
	    makeroot(a);
	    makeroot(b);
	    hp[a].push(mxzheng[b] + 1);
	    fa[b] = a;
	    up(a);
	}
	inline char cget() {
	    char c;
	    while ((c = getchar()) || 23333)
	        if (c >= 'A' && c <= 'Z')
	            return (c);
	}
	void ywymain() {
	    mxzheng[0] = -1;
	    mxfan[0] = -1;
	    int q = get();
	    int gn = 1;
	    while (q) {
	        q--;
	        char c = cget();
	        if (c == 'B') {
	            int x = get(), me = gn;
	            gn++;
	            size[me] = 1;
	            if (x == -1)
	                continue;
	            link(me, x);
	        } else {
	            int x = get();
	            makeroot(x);
	            printf("%d\n", mxzheng[x]);
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：暴力出奇迹 (赞：12)

真不懂这题为啥要 LCT，~~虽然我一开始想的也是 LCT......~~

结论：一个点 $u$ 在树内的最远点（之一），一定是**这棵树的直径的一个端点。**

另一个结论：**两棵树用一条边连起来的时候，新的直径一定是两棵树各自的直径的两两组合中，最长的那一条。**

考虑先离线建出整棵树，倍增维护 LCA，用公式 $dist(u,v)=depth_u+depth_v-2 \times depth_{lca(u,v)}$ 计算两点间距离。

然后按顺序操作，碰到 $\texttt{B}$ 加边操作，合并两棵树，并且我们发现其中一棵只有一个点，那么上面说的四个点两两组合，可以简化为 $3$ 种组合方式，选出距离最大的一种作为新的直径并记录。

碰到 $\texttt{Q}$ 查询操作，直接找到 $k$ 点所在的树的直径，然后分别算出 $k$ 到直径两个端点距离，取较大值即可。

再考虑如何记录直径，我一开始想的是用并查集，把一条直径记录在并查集的代表元的位置。后来想想并查集都不用了，离线建树的过程中，直接求出每个点所在的树的根，把直径记录在根的位置就行了，还省掉了并查集的常数。

时间复杂度：假设操作数是 $q$，结点数是 $n$，如果倍增，预处理复杂度 $O(n \log n)$，单次求 $lca$ 复杂度 $O(\log n)$，总复杂度约为 $O((n+q)\log n)$；用欧拉序列 + ST 表求 $lca$ 的总复杂度 $O(n \log n + q)$，~~再用四毛子优化就可以做到线性了。~~

具体细节看代码吧：

```cpp
#include <cstdio>
using namespace std;
const int N = 100010;
const int LOGN = 17;
struct Edge {
	int to, nxt;
}edges[N];
int point[N][2]; //记录直径的两个端点
int fa[N][LOGN], depth[N];
int opt[N], queryu[N], idx[N];
int head[N], root[N], n, m, nedge; //root[u] 表示 u 点所在的树的根
inline int max(int x, int y) {return x > y ? x : y;}
inline void swap(int &x, int &y) {x ^= y; y ^= x; x ^= y;}
inline void addedge(int u, int v) {
	edges[++nedge].to = v;
	edges[nedge].nxt = head[u];
	head[u] = nedge;
}
inline void dfs(int u) {
	for(register int i = 1; (1 << i) <= depth[u]; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(register int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		fa[v][0] = u; depth[v] = depth[u] + 1;
		if(u == 0) root[v] = v;
		else root[v] = root[u];
		dfs(v);
	}
}
inline int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u, v);
	for(register int i = LOGN - 1; i >= 0; --i)
		if((1 << i) <= depth[u] - depth[v]) u = fa[u][i];
	if(u == v) return u;
	for(register int i = LOGN - 1; i >= 0; --i)
		if(fa[u][i] != fa[v][i]) {u = fa[u][i]; v = fa[v][i];}
	return fa[u][0];
}
inline int dist(int u, int v) {
	return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}
int main() {
	scanf("%d", &m);
	for(register int i = 1; i <= m; ++i) {
		char op[5];
		scanf("%s %d", op, &queryu[i]);
		if(op[0] == 'B') opt[i] = 1; else opt[i] = 2;
		if(opt[i] == 1) {idx[i] = ++n; addedge(queryu[i] > -1 ? queryu[i] : 0, n);} //idx[i] 记录第 i 步（如果是 B 操作）新建的点的编号
	}
	dfs(0);
	for(register int u = 1; u <= n; ++u) point[u][0] = point[u][1] = u;
	for(register int i = 1; i <= m; ++i) {
		if(opt[i] == 1 && queryu[i] != -1) {
			int x = root[queryu[i]];
			int dist1 = dist(point[x][0], point[x][1]);
			int dist2 = dist(point[x][0], idx[i]), dist3 = dist(point[x][1], idx[i]);
			if(dist1 >= dist2 && dist1 >= dist3) {}
			else if(dist2 >= dist1 && dist2 >= dist3) point[x][1] = idx[i];
			else point[x][0] = idx[i]; //三个距离选最大的记录下来（注意以上的 >= 不能写成 >，具体原因自行思考）
		}
		if(opt[i] == 2) {
			int x = root[queryu[i]];
			printf("%d\n", max(dist(point[x][0], queryu[i]), dist(point[x][1], queryu[i])));
		}
	}
	return 0;
}
```

---

## 作者：Genius_Z (赞：8)

这题可以算是$LCT$动态维护树的直径的模板题

考虑这样两个性质：

- **两棵树合并后的直径的两个端点来源于两条直径中的四个端点**
- **从一点出发搜到最远的点一定是直径两端点之一**

证明：（蒟蒻数学不好，要是写错了请各位大佬指出

设直径为$s-t$

- 当该点$u$为直径上的点时，设搜到的最远点为$x$，则$dis(u,x)>dis(u,t)$且$dis(u,x)>dis(u,s)$，若$x$不为$s$或$t$中一点则直径就不是$s-t$，而是$u-x$。
- 当该点$u$不为直径上的点时：
  - 若$u$走到了$s-t$上的某点$x$，最后肯定走到某个端点，假设是$s$；
  - 若$u$到最远点$v$的路径与$s-t$无交点，则$dis(u,v)>dis(u,x)+dis(s,x)$，那么$dis(u,v)+dis(x,t)>dis(u,x)+dis(s,x)+dis(x,t)$，移项可得$dis(u,v)+dis(x,t)-dis(u,x)>dis(s,t)$

一张好看的图（雾

![](https://s2.ax1x.com/2019/03/27/AdNDN6.png)

code：

```cpp
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <list>
#define inl inline
#define re register int
#define ll long long
#define fa(x) t[x].fa
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define lowbit(x) ((x) & (-x))
const int inf = 0x7fffffff;
using namespace std;
template < class Read >
inl Read read() {
	Read x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
struct link_cut_tree {
	struct node {
		int child[2], fa, w, size;
		bool filp;
	} t[1000001];
	inl void upd(int x) {
		t[x].size = t[ls(x)].size + t[rs(x)].size + 1;
	}
	inl void reverse(int x) {
		swap(ls(x), rs(x));
		t[x].filp ^= 1;
	}
	inl void pushdown(int x) {
		if (t[x].filp) {
			if (ls(x))reverse(ls(x));
			if (rs(x))reverse(rs(x));
			t[x].filp = 0;
		}
	}
	inl bool poi(int x) {
		return rs(fa(x)) == x;
	}
	inl bool nroot(int x) {
		return ls(fa(x)) == x || rs(fa(x)) == x;
	}
	inl void rotate(int x) {
		int f = fa(x), gf = fa(f), fs = poi(x), gfs = poi(f), s = t[x].child[fs ^ 1];
		if (nroot(f))t[gf].child[gfs] = x;
		t[f].child[fs] = s, t[x].child[fs ^ 1] = f;
		fa(x) = gf, fa(f) = x;
		if (s)fa(s) = f;
		upd(f);
	}
	inl void push(int x) {
		if (nroot(x))push(fa(x));
		pushdown(x);
	}
	inl void splay(int x) {
		push(x);
		while (nroot(x)) {
			if (nroot(fa(x)))poi(x) == poi(fa(x)) ? rotate(fa(x)) : rotate(x);
			rotate(x);
		}
		upd(x);
	}
	inl void access(int x) {
		for (re i = 0; x; x = t[i = x].fa) {
			splay(x), rs(x) = i, upd(x);
		}
	}
	inl void makeroot(int x) {
		access(x), splay(x), reverse(x);
	}
	inl void split(int x, int y) {
		makeroot(y), access(x), splay(x);
	}
	inl void link(int x, int y) {
		if (!x || !y || x == y)return;
		split(x, y);
		t[y].fa = x;
	}
	inl void cut(int x, int y) {
		if (!x || !y || x == y)return;
		split(x, y);
		if (t[x].size <= 2)ls(x) = fa(y) = 0;
	}
	struct diameter {
		int x, y, w;
	}d[1000001];
	int fa[1000001];
	inl int find(int x) {
		if (fa[x] != x)return fa[x] = find(fa[x]);
		return x;
	}
	inl int query(int x, int y) {
		split(x, y);
		return t[x].size - 1;
	}
	inl void merge(int x, int y) {
		link(x, y);
		y = find(y), fa[x] = y;
		re a = x, b = d[y].x, c = d[y].y, maxn = d[y].w, tmp = query(a, b);
		if (tmp > maxn)maxn = tmp, d[y].x = a, d[y].y = b;
		tmp = query(a, c);
		if (tmp > maxn)maxn = tmp, d[y].x = a, d[y].y = c;
		tmp = query(b, c);
		if (tmp > maxn)maxn = tmp, d[y].x = b, d[y].y = c;
		d[y].w = maxn;
	}
	inl int spread() {
		char c = getchar();
		while (c != 'Q'&&c != 'B') c = getchar();
		return c == 'Q' ? 0 : 1;
	}
	inl void work(void) {
		re m = read<int>(), n = 0, op, x, y;
		while (m--) {
			op = spread();
			if (op) {
				x = ++n, y = read<int>();
				d[x].x = x, d[x].y = x, fa[x] = x;
				if (~y)merge(x, y);
			}
			else {
				x = read<int>(), y = find(x);
				printf("%d\n", max(query(x, d[y].x), query(x, d[y].y)));
			}
		}
	}
}lct;
signed main() {
	lct.work();
	return 0;
}
```



---

## 作者：LPA20020220 (赞：6)

大概题意就是合并两个连通块， 查询连通块内点到其他点的最大距离。

注意到对于一个点， 在其连通块内与其距离最大的点一定为直径所在两点的一点， 所以我们可以在合并连通块的时候顺带维护直径所在的两个点。 当然这两个点也一定是原来四个点中的两个， 所以我们只需要求出两两之间距离即可。

对于这道题更简单， 因为每次只有一个点和一个连通块合并， 所以直接求两次距离即可。

怎么求距离？可以倍增LCA动态插入， 但是LCT大法好！！

每个点的权值设为1，split后上面那个点的sum-1即为距离...

总复杂度O(Nlog(N))。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#define R register
#define IN inline
#define gc getchar()
#define W while
#define dad tree[now].fat
#define ls tree[now].son[0]
#define rs tree[now].son[1]
#define MX 100050
int q, top, arr;
int bel[MX], sta[MX], dis[MX];
struct Bound
{int a, b;}bd[MX];
struct Node
{
    int son[2], fat, sum;
    bool rev;
}tree[MX];
namespace DSU
{
    void reset()
    {
        for (R int i = 1; i <= q; ++i)
        bel[i] = i, tree[i].sum = 1, bd[i] = {i, i};
    }
    int find(const int &now) {return now == bel[now] ? now : bel[now] = find(bel[now]);}
}
namespace LCT
{
    IN bool get(const int &now) {return tree[dad].son[1] == now;}
    IN bool nroot(const int &now) {return tree[dad].son[1] == now || tree[dad].son[0] == now;}
    IN void pushup(const int &now) {tree[now].sum = tree[ls].sum + tree[rs].sum + 1;}
    IN void pushrev(const int &now) {std::swap(ls, rs), tree[now].rev ^= 1;}
    IN void pushdown(const int &now) {if(tree[now].rev) tree[now].rev = false, pushrev(ls), pushrev(rs);}
    IN void rotate(const int &now)
    {
        R bool dir = get(now);
        R int fa = dad, grand = tree[fa].fat;
        tree[fa].son[dir] = tree[now].son[dir ^ 1];
        tree[tree[now].son[dir ^ 1]].fat = fa;
        if(nroot(fa)) tree[grand].son[get(fa)] = now;
        tree[now].fat = grand;
        tree[now].son[dir ^ 1] = fa;
        tree[fa].fat = now;
        pushup(fa);
    }
    IN void splay(R int now)
    {
        int tmp = now, fa;
        sta[top = 1] = now;
        W (nroot(now)) sta[++top] = now = dad;
        W (top) pushdown(sta[top--]);
        now = tmp;
        W (nroot(now))
        {
            fa = dad;
            if(nroot(fa)) rotate(get(now) == get(fa) ? fa : now);
            rotate(now);
        }
        pushup(now);
    }
    IN void access(R int now)
    {
        for (R int x = 0; now; x = now, now = dad)
        {splay(now); rs = x; pushup(now);}
    }
    IN void makeroot(const int &now)
    {access(now), splay(now), pushrev(now);}
    IN void link(const int &x, const int &y)
    {makeroot(x); tree[x].fat = y;}
    IN void split(const int &x, const int &y)
    {makeroot(x); access(y); splay(y);}
}
int main(void)
{
    scanf("%d", &q); DSU::reset();
    char buf[3]; int a, tar, mx1, mx2;
    W (q--)
    {
        scanf("%s%d", buf, &a);
        if(buf[0] == 'B')
        {
            ++arr;
            if(a == -1) continue;
            else
            {
                tar = DSU::find(a);
                LCT::link(arr, a);
                bel[arr] = tar;
                LCT::split(arr, bd[tar].a);
                mx1 = tree[bd[tar].a].sum - 1;
                LCT::split(arr, bd[tar].b);
                mx2 = tree[bd[tar].b].sum - 1;
                if(mx1 > dis[tar]) dis[tar] = mx1, bd[tar] = {arr, bd[tar].a};
                if(mx2 > dis[tar]) dis[tar] = mx2, bd[tar] = {arr, bd[tar].b};
            }
        }
        else
        {
            tar = DSU::find(a);
            LCT::split(a, bd[tar].a);
            mx1 = tree[bd[tar].a].sum - 1;
            LCT::split(a, bd[tar].b);
            mx2 = tree[bd[tar].b].sum - 1;
            printf("%d\n", std::max(mx1, mx2));
        }
    }
}
```

---

## 作者：曹老师 (赞：6)

~~水过~~~

动态点分治？LCT？~~都不会~~

**解法：LCA 树的直径**

对于每一个节点维护直径的左右端点

下次输入的时候只需查看要不要更新端点

```cpp
int dis1=lca(top,tree[o].l),dis2=lca(tree[o].l,tree[o].r);
if(dis1>dis2)   tree[o].r=top;
int dis3=lca(top,tree[o].r);
if(dis3>dis2)   tree[o].l=top;
```

以上代码~~很~~容易错

要注意dis3 一定要放在这里 不要else！

如果要确定每一个点在那个直径上（一棵树有多条直径

**不要用类似并查集似的查找father** ~~或许只有我这么菜才这样写吧~~

会被卡常 直接用group数组记录一下就可以

输出直接求这个点到两个端点的距离

**距离用LCA求 要倍增的那种！**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
using namespace std;
const int L=1e5+5;
struct node{
    int l,r;
};
node tree[L];
int n,top,deep[L],fa[L][17],group[L];
int lca(int x,int y)
{
    int dis=0,k;
    if(deep[x]>deep[y])
        swap(x,y);
    for(int i=deep[y]-deep[x],j=0;i>0;i>>=1,j++)
    	if(i&1)
    	{
    		dis+=pow(2,j);
   	 		y=fa[y][j];
  	  	}
    if(x==y)
    	return dis;
    for(k=0;(1<<k)<=deep[x];k++);
    for(;k>=0;k--)
    	if((1<<k)<=deep[x]&&fa[x][k]!=fa[y][k])
    	{
    		dis+=pow(2,k+1);
    		x=fa[x][k];
    		y=fa[y][k];
    	}
    return dis+2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int t;
        char c;
        cin>>c>>t;
        if(c=='Q')
        {
            int a1=group[t],a2=lca(t,tree[a1].l),a3=lca(t,tree[a1].r);
            printf("%d\n",max(a2,a3));
        }
        else
        {
            ++top;
            if(t==-1)
            {
                group[top]=top;
                deep[top]=0;
                fa[top][0]=top;
                tree[top].l=tree[top].r=top;
                continue;
            }
            fa[top][0]=t;
            deep[top]=deep[t]+1;
            group[top]=group[t];
    		for(int i=1;(1<<i)<=deep[top];i++)
        		fa[top][i]=fa[fa[top][i-1]][i-1];
        	int o=group[t];
            int dis1=lca(top,tree[o].l),dis2=lca(tree[o].l,tree[o].r);
            if(dis1>dis2)
                tree[o].r=top;
            int dis3=lca(top,tree[o].r);
                if(dis3>dis2)
                    tree[o].l=top;
        }
    }
    return 0;
}
```

---

## 作者：Karry5307 (赞：3)

### 题意

给一个一开始没有点的图，有 $q$ 次操作，每次为加点连边或者查询一个点到连通块内所有点的距离最大值。

$\texttt{Data Range}:1\leq q\leq 10^5$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13812799.html)

跟[「雅礼集训 2017 Day5」远行](https://loj.ac/problem/6038)很像的一个题，都是 LCT 维护直径。

注意到树上一个点到其他点的距离最大值只可能在直径的两个端点处取到，而且又存在加边操作，所以可以直接使用 LCT 来维护。

当合并两个连通块的时候需要在两个连通块各自的直径端点中选两个成为新的直径，需要讨论 $6$ 种情况，这个暴力搞就行了。

但是这个题不用这么麻烦。因为每一次合并的一边是一个点，所以只需要讨论两次就好了。

同时，维护直径的两个端点和直径的距离可以使用并查集来维护，查询两点距离的话就先 `split` 把两个点的路径拉出来放到同一个 Splay 上，再用根节点的大小减 $1$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51;
ll n,c,d,x,fx,fy,mx,lx,rx;
char op;
ll ffa[MAXN],l[MAXN],r[MAXN],dist[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
	{
	    ch=getchar();
	}
    if(ch=='-')
	{
	    neg=-1;
	    ch=getchar();
	}
    while(isdigit(ch))
	{
	    num=(num<<3)+(num<<1)+(ch-'0');
	    ch=getchar();
	}
    return num*neg;
}
inline ll find(ll x)
{
	return x==ffa[x]?x:ffa[x]=find(ffa[x]);
}
namespace LCT{
    struct Node{
	    ll fa,rv,sz;
	    ll ch[2];
	};
    struct LinkCutTree{
	    Node nd[MAXN];
		ll st[MAXN];
		#define ls nd[x].ch[0]
		#define rs nd[x].ch[1]
		inline bool nroot(ll x)
		{
			return nd[nd[x].fa].ch[0]==x||nd[nd[x].fa].ch[1]==x;
		}
		inline void update(ll x)
		{
			nd[x].sz=nd[ls].sz+nd[rs].sz+1;
		}
		inline void reverse(ll x)
		{
			swap(ls,rs),nd[x].rv^=1;
		}
		inline void spread(ll x)
		{
			if(nd[x].rv)
			{
				ls?reverse(ls):(void)1,rs?reverse(rs):(void)1;
				nd[x].rv=0;
			}
		}
		inline void rotate(ll x)
		{
			ll fa=nd[x].fa,gfa=nd[fa].fa;
			ll dir=nd[fa].ch[1]==x,son=nd[x].ch[!dir];
			if(nroot(fa))
			{
				nd[gfa].ch[nd[gfa].ch[1]==fa]=x;
			}
			nd[x].ch[!dir]=fa,nd[fa].ch[dir]=son;
			if(son)
			{
				nd[son].fa=fa;
			}
			nd[fa].fa=x,nd[x].fa=gfa,update(fa);
		}
		inline void splay(ll x)
		{
			ll fa=x,gfa,cur=0;
			st[++cur]=fa;
			while(nroot(fa))
			{
				st[++cur]=fa=nd[fa].fa;
			}
			while(cur)
			{
				spread(st[cur--]);
			}
			while(nroot(x))
			{
				fa=nd[x].fa,gfa=nd[fa].fa;
				if(nroot(fa))
				{
					rotate((nd[fa].ch[0]==x)^(nd[gfa].ch[0]==fa)?x:fa);
				}
				rotate(x);
			}
			update(x);
		}
		inline void access(ll x)
		{
			for(register int i=0;x;x=nd[i=x].fa)
			{
				splay(x),rs=i,update(x);
			}
		}
		inline void makeRoot(ll x)
		{
			access(x),splay(x),reverse(x);
		}
		inline ll findRoot(ll x)
		{
			access(x),splay(x);
			while(ls)
			{
				spread(x),x=ls;
			}
			return x;
		}
		inline void split(ll x,ll y)
		{
			makeRoot(x),access(y),splay(y);
		}
		inline void link(ll x,ll y)
		{
			makeRoot(x);
			if(findRoot(y)!=x)
			{
				nd[x].fa=y;
			}
		}
		#undef ls
		#undef rs
	};
}
LCT::LinkCutTree lct;
inline ll getDist(ll x,ll y)
{
	lct.split(x,y);
	return lct.nd[y].sz-1;	
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		ffa[i]=l[i]=r[i]=i,lct.nd[i].sz=1;
	}
	for(register int i=0;i<n;i++)
	{
		cin>>op,x=read();
		if(op=='B')
		{
			++c;
			if(x==-1)
			{
				continue;
			}
			fx=c,fy=find(x),mx=dist[fx],lx=l[fx],rx=r[fx];
			if(mx<dist[fy])
			{
				lx=l[fy],rx=r[fy],mx=dist[fy];
			}
			lct.link(c,x);
			if((d=getDist(l[fx],l[fy]))>mx)
			{
				mx=d,lx=l[fx],rx=l[fy];
			}
			if((d=getDist(l[fx],r[fy]))>mx)
			{
				mx=d,lx=l[fx],rx=r[fy];
			}
			l[fx]=lx,r[fx]=rx,dist[fx]=mx,ffa[fy]=fx;
		}
		if(op=='Q')
		{
			fx=find(x);
			printf("%d\n",max(getDist(x,l[fx]),getDist(x,r[fx])));
		}
	}
}
```

---

## 作者：hzoi_Shadow (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P4271)

# 前置知识

[树的直径](https://oi-wiki.org/graph/tree-diameter/) | [最近公共祖先](https://oi-wiki.org/graph/lca/) | [并查集](https://oi-wiki.org/ds/dsu/)

# 解法

一个显而易见的结论：设点集 $A$ 的直径的两个端点为 $u_{1},v_{1}$，另一个点集 $B$ 的直径的两个端点为 $u_{2},v_{2}$，则 $A \bigcup B$ 的直径端点一定是 $\{ u_{1},v_{1},u_{2},v_{2} \}$ 中的两个。

还有另外一个结论：点集 $A$ 中一个点 $x$ 到点集中其他点中最远点的距离一定是到直径两个端点的距离取 $\max$。
  - 证明
	- 当 $x$ 在直径上时，显然。
	- 当 $x$ 不在直径上时，先走到直径上，就转化到了上述情况。

并查集维护连通块内直径的两个端点即可。

倍增来支持动态连边操作，做法同 [luogu P3302 [SDOI2013] 森林](https://www.luogu.com.cn/problem/P3302)。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	ll nxt,to;
}e[200010];
ll head[200010],fa[200010][25],dep[200010],N,cnt=0;
void add(ll u,ll v)
{
	cnt++;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs(ll x,ll father)
{
	dep[x]=dep[father]+1;
	fa[x][0]=father;
	for(ll i=1;i<=N;i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(ll i=head[x];i!=0;i=e[i].nxt)
	{
		if(e[i].to!=father)
		{
			dfs(e[i].to,x);
		}
	}
}
ll lca(ll x,ll y)
{
	if(dep[x]>dep[y])
	{
		swap(x,y);
	}
	for(ll i=N;i>=0;i--)
	{
		if(dep[x]+(1<<i)<=dep[y])
		{
			y=fa[y][i];
		}
	}
	if(x==y)
	{
		return x;
	}
	else
	{
		for(ll i=N;i>=0;i--)
		{
			if(fa[x][i]!=fa[y][i])
			{
				x=fa[x][i];
				y=fa[y][i];
			}
		}
		return fa[x][0];
	}
}
ll dis(ll x,ll y)
{
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
struct DSU
{
	ll fa[200010],pt[200010][2],tmp[5];
	void init(ll n)
	{
		for(ll i=1;i<=n;i++)
		{
			fa[i]=i;
			pt[i][0]=pt[i][1]=i;
		}
	}
	ll find(ll x)
	{
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	void merge(int x,int y)
	{
		dfs(y,x);
		x=find(x);
		y=find(y);
		fa[y]=x;
		ll maxx=0;
		tmp[1]=pt[x][0];
		tmp[2]=pt[x][1];
		tmp[3]=pt[y][0];
		tmp[4]=pt[y][1];
		for(ll i=1;i<=4;i++)
		{
			for(ll j=i+1;j<=4;j++)
			{
				if(dis(tmp[i],tmp[j])>maxx)
				{
					maxx=dis(tmp[i],tmp[j]);
					pt[x][0]=tmp[i];
					pt[x][1]=tmp[j];
				}
			}
		}
	}
	ll ask(ll x)
	{
		ll y=find(x);
		return max(dis(x,pt[y][0]),dis(x,pt[y][1]));
	}
}D;
int main()
{
	ll q,x,n=0,i;
	char pd;
	cin>>q;
	N=log2(q)+1;
	D.init(q);
	for(i=1;i<=q;i++)
	{
		cin>>pd>>x;
		if(pd=='B')
		{
			n++;
			if(x==-1)
			{
				dfs(n,0);
			}
			else
			{
				D.merge(x,n);
			}
		}
		else
		{
			cout<<D.ask(x)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ccxswl (赞：2)

# P4271 [USACO18FEB] New Barns P

这是一个不需要 LCT 的 $n\log n$ 做法。

 - 题意：
    > 给你一棵树，初始没有节点。你需要支持两种操作：
    > `B p` 表示新建一个节点，将它与 $p$ 节点连接；若 $p=-1$，则表示不与其它节点相连。
    > `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。


每次连边操作实际上是将两棵树连边（或新建一颗只有根节点的树），最后的状态是一个森林。

有两个性质：

 1. 一棵树中，距离一个点最远的点是直径的其中一个端点。
 1. 把两棵树相连，它直径的两个端点一定是原来两棵树直径端点中的某两个。

我们建一个源点把这个森林连成树，可以预处理出每个点的深度以及求 LCA 需要的一些信息，便于快速求出两点距离。

最后重新跑一遍操作，在连边时处理直径的两个端点。

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            w = -w;
        c = getchar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - 48;
        c = getchar();
    }
    return s * w;
}

const int maxN = 1e5 + 7;

int m, n;

vector<int> E[maxN];

int st[20][maxN], tot, idx[maxN], dep[maxN];
void dfs(int x, int f) {
    dep[x] = dep[f] + 1;
    idx[x] = ++tot;
    st[0][idx[x]] = f;
    for (auto to : E[x])
        if (to != f)
            dfs(to, x);
}
int get(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}
void init() {
    for (int t = 1; t <= 20; t++)
        for (int i = 1; i + (1 << t) - 1 <= n + 1; i++)
            st[t][i] = get(st[t - 1][i], st[t - 1][i + (1 << (t - 1))]);
}
int lca(int x, int y) {
    if (x == y) return x;
    x = idx[x], y = idx[y];
    if (x > y) swap(x, y);
    x++;
    int t = __lg(y - x + 1);
    return get(st[t][x], st[t][y - (1 << t) + 1]);
}
int dis(int x, int y) {
    int l = lca(x, y);
    return dep[x] + dep[y] - dep[l] * 2;
}

int fa[maxN];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int d1[maxN], d2[maxN];

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    int tmp[6] = {d1[x], d2[x], d1[y], d2[y]};
    int res = -1e9;
    for (int i = 0; i < 4; i++)
        for (int j = 0, L; j < 4; j++)
            if ((L = dis(tmp[i], tmp[j])) > res)
                res = L, d1[x] = tmp[i], d2[x] = tmp[j];
    fa[y] = x;
}

struct modi {
    int op, x;
} mo[maxN];

int main() {
    for (int i = 0; i <= 1e5 + 1; i++)
        fa[i] = d1[i] = d2[i] = i;
    m = read();
    for (int i = 1; i <= m; i++) {
        char op;
        cin >> op;
        mo[i].op = (op == 'B');
        mo[i].x = read();
        if (mo[i].op) {
            ++n;
            if (mo[i].x > 0) {
                E[mo[i].x].push_back(n);
                E[n].push_back(mo[i].x);
                fa[find(n)] = find(mo[i].x);
            }
        }
    }
    
    for (int i = 1; i <= n; i++)
        if (find(i) != find(n + 1)) {
            E[n + 1].push_back(i);
            E[i].push_back(n + 1);
            fa[find(i)] = find(n + 1);
        }
    for (int i = 0; i <= n + 1; i++)
        fa[i] = i;

    dfs(n + 1, 0);
    init();

    n = 0;
    for (int i = 1; i <= m; i++) {
        if (mo[i].op) {
            n++;
            if (mo[i].x > 0)
                merge(mo[i].x, n);
        }
        else
            cout << max(dis(d1[find(mo[i].x)], mo[i].x), dis(d2[find(mo[i].x)], mo[i].x)) << '\n';
    }
}
```

---

性质 1 太简单了。

性质 2 简单证明：

 - 新树的直径如果不经过那条链接的边，那么新的直径为原来两条直径的一条。
 - 如果经过那条边，设那条边起点为 $u$，终点为 $v$。新直径一定经过 $u,v$。利用性质 1，第一棵树中距离 $u$ 最远的点为直径的端点，在第二棵树中距离 $v$ 最远的点也是直径的端点。

性质 2 得证。

---

## 作者：Hoks (赞：2)

## 前言
[『究极折磨篇』LCT 题单](https://www.luogu.com.cn/training/440260#information)里的，顺便宣传下[『从入门到入土』树链剖分学习笔记](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)。
## 思路分析
因为题目中有动态加边操作，形态也是森林，所以直接考虑使用 LCT。

是否在同一颗树中考虑使用并查集解决，那么剩下的问题就是如何求这颗树中离 $k$ 最远的点了。

考虑离他最远的点肯定是树的直径的两个端点之一，题意就变成了 LCT 维护直径。

那么新加一个点的时候，考虑加上原本直径的两个点，一共三个点，两两求个距离取最大即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls son[x][0]
#define rs son[x][1]
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
struct node
{int x,y,w;}d[N];
int n,m;
int f[N],s[N],son[N][2],st[N],r[N],fa[N];
static char buf[1000000],*paa=buf,*pd=buf;
//#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*t;
}
inline void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline bool ntrt(int x){return son[f[x]][1]==x||son[f[x]][0]==x;}
inline void pushup(int x){s[x]=s[ls]+s[rs]+1;}
inline void pushson(int x){swap(ls,rs),r[x]^=1;}
inline void pushdown(int x)
{
	if(r[x])
	{
		if(ls) pushson(ls);
		if(rs) pushson(rs);
		r[x]=0;
	}
}
inline void rotate(int x)
{
	int y=f[x],z=f[y],k=(son[y][1]==x),w=son[x][!k];
	if(ntrt(y)) son[z][son[z][1]==y]=x;son[x][!k]=y;son[y][k]=w;
	if(w) f[w]=y;f[y]=x;f[x]=z;
	pushup(y);
}
inline void Splay(int x)
{
	int y=x,tot=0;st[++tot]=y;
	while(ntrt(y)) st[++tot]=y=f[y];
	while(tot) pushdown(st[tot--]);
	while(ntrt(x))
	{
		y=f[x];int z=f[y];
		if(ntrt(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void access(int x){for(int y=0;x;x=f[y=x]) Splay(x),rs=y,pushup(x);}
inline void makert(int x){access(x);Splay(x);pushson(x);}
inline int findrt(int x)
{
	access(x);Splay(x);
	while(ls) pushdown(x),x=ls;
	Splay(x);return x;
}
inline void split(int x,int y){makert(x);access(y);Splay(y);}
inline void link(int x,int y){makert(x);if(findrt(y)!=x)f[x]=y;}
inline int query(int x,int y){split(x,y);return s[y]-1;}
signed main()
{
	m=read();
	for(int i=1,x;i<=m;i++)
	{
		char op=getchar();while(op!='B'&&op!='Q') op=getchar();x=read();fa[i]=i;
		if(op=='B')
		{
			n++;d[n].x=n,d[n].y=n;
			if(~x)
			{
				link(n,x);x=find(x);fa[n]=x;
				int a=n,b=d[x].x,c=d[x].y,mx=d[x].w,t=query(a,b);
				if(t>mx) mx=t,d[x].x=a,d[x].y=b;t=query(a,c);
				if(t>mx) mx=t,d[x].x=a,d[x].y=c;t=query(b,c);
				if(t>mx) mx=t,d[x].x=b,d[x].y=c;d[x].w=mx;
			}
		}
		else print(max(query(x,d[find(x)].x),query(x,d[find(x)].y))),puts("");
	}
	return 0;
}

```


---

## 作者：zhylj (赞：2)

为了更好的阅读体验，你可以前往[我的博客](http://zhylj.cc/index.php/archives/14/).

## 分析

这是一个离线做法，我们先把最终的森林给建出来。

我们考虑对于一个对点 $u$ 的询问，可能对它产生贡献的点必然要满足：其到 $u$ 这条路径上所有边出现时间的最大值不超过这个询问所在的时间。

可以发现这是个简单的关于路径的偏序问题，所以我们考虑点分治，每次计算所有经过根的路径，处理 $\operatorname {tmx}_i$ 表示 $i$ 到根的路径上出现时间最晚的边以及 $d_i$ 表示 $i$ 的深度，正反扫两边所有子树，用树状数组维护一下（下标为出现时间的）前缀最大值就好了。

最后的时间复杂度是 $\mathcal O(n\log^2n)$ 的。

## 代码

```cpp
const int kN = 1e5 + 5, kInf = 0x3f3f3f3f;

int n, q, t[kN], ans[kN];
std::vector <int> Q[kN], E[kN];

void Add(int u, int v) {
	E[u].push_back(v);
	E[v].push_back(u);
}

int tr[kN];
void Modify(int o, int v) {
	for(; o <= q; o += o & -o)
		tr[o] = std::max(tr[o], v);
}
int Query(int o) {
	int ret = 0;
	for(; o; o -= o & -o)
		ret = std::max(ret, tr[o]);
	return ret;
}
void Clear(int o) {
	for(; o <= q; o += o & -o)
		tr[o] = 0;
}

int siz[kN]; bool vis[kN];
void GetRoot(int u, int tot, int &rt, int &rt_mn_siz) {
	vis[u] = true;
	int mx_siz = 0; siz[u] = 1;
	for(auto v : E[u]) if(!vis[v]) {
		vis[v] = true; GetRoot(v, tot, rt, rt_mn_siz);
		siz[u] += siz[v]; mx_siz = std::max(mx_siz, siz[v]);
	}
	mx_siz = std::max(mx_siz, tot - siz[u]);
	if(mx_siz < rt_mn_siz) rt = u, rt_mn_siz = mx_siz;
	vis[u] = false;
}

int d[kN], t_mx[kN];
void GetQuery(int u, int p) {
	vis[u] = true;
	d[u] = d[p] + 1; siz[u] = 1;
	t_mx[u] = std::max(t[u], t_mx[p]);
	for(auto x : Q[u]) {
		if(t_mx[u] <= x)
			ans[x] = std::max(ans[x], d[u] + Query(x));
	}
	for(auto v : E[u]) if(!vis[v]) {
		GetQuery(v, u);
	}
	vis[u] = false;
}
void GetDep(int u, int p) {
	vis[u] = true;
	d[u] = d[p] + 1; siz[u] = 1;
	t_mx[u] = std::max(t[u], t_mx[p]);
	Modify(t_mx[u], d[u]);
	for(auto v : E[u]) if(!vis[v]) {
		GetDep(v, u);
		siz[u] += siz[v];
	}
	vis[u] = false;
}
void Init(int u) {
	vis[u] = true; Clear(t_mx[u]);
	for(auto v : E[u]) if(!vis[v])
		Init(v);
	vis[u] = false;
}
void Div(int u, int tot) {
	int rt = 0, rt_mn_siz = kInf;
	GetRoot(u, tot, rt, rt_mn_siz);
	d[rt] = 0; t_mx[rt] = t[rt]; vis[rt] = true;
	for(auto v : E[rt]) if(!vis[v]) {
		GetQuery(v, rt);
		GetDep(v, rt);
	}
	for(auto x : Q[rt])
		ans[x] = std::max(ans[x], Query(x));
	for(auto v : E[rt]) if(!vis[v])
		Init(v);
	std::reverse(E[rt].begin(), E[rt].end());
	for(auto v : E[rt]) if(!vis[v]) {
		GetQuery(v, rt);
		GetDep(v, rt);
	}
	for(auto v : E[rt]) if(!vis[v])
		Init(v);
	for(auto v : E[rt]) if(!vis[v])
		Div(v, siz[v]);
}

int dsu_fa[kN], dsu_siz[kN];
int Find(int x) { return dsu_fa[x] == x ? x : dsu_fa[x] = Find(dsu_fa[x]); }
void Merge(int x, int y) {
	int f_x = Find(x), f_y = Find(y);
	if(f_x == f_y) return;
	dsu_fa[f_x] = f_y; dsu_siz[f_y] += dsu_siz[f_x];
}

int main() { 
	int T = 1; //rd(T);
	while(T--) {
		memset(ans, ~0x3f, sizeof(ans));
		rd(q);
		for(int i = 1; i <= q; ++i)
			dsu_fa[i] = i, dsu_siz[i] = 1;
		for(int i = 1; i <= q; ++i)  {
			char opt[5]; int x;
			scanf("%s", opt + 1); rd(x);
			if(opt[1] == 'B') {
				t[++n] = i;
				if(~x) {
					Add(n, x);
					Merge(n, x);
				}
			} else {
				Q[x].push_back(i);
			}
		}
		for(int i = 1; i <= n; ++i) if(dsu_fa[i] == i) {
			Div(i, dsu_siz[i]);
		}
		for(int i = 1; i <= q; ++i) {
			if(ans[i] >= 0) printf("%d\n", ans[i]);
		}
	} return 0;
}
```


---

## 作者：Reaper_gsm (赞：2)

## 【BZOJ5192】【洛谷P4271】New Barns

[洛谷传送门](https://www.luogu.com.cn/problem/P4271)

### 题目大意：已经比BZOJ的题意简单很多了....



### 题解

显然这始终是一个树形结构，因为每个点要么没有Father边，要么有一条连向编号小于自己的边。不难想到，用树链剖分或者是倍增数组来维护树上信息。题目的所求是多次询问距离某个点最远的点的距离。

#### 结论一 ： 距离某个点最远的点，肯定有一个是所在树的直径的端点。
所以，如果我们能够实时维护树的直径，就能够快速求解答案。那么，这么一颗动态的树，支持加入节点和树上距离查询，就是LCT了。

#### 结论二 ： 对于两棵树，如果第一棵树直径两端点为(u,v)(u,v)，第二棵树直径两端点为(x,y)(x,y)，用一条边将两棵树连接，那么新树的直径一定是u ,v ,x ,y ,中的两个点

明白了这个结论，我们就可以维护合并之后的树的直径端点。可以用并查集维护每个连通块的标志点，记录每个标志点所在连通块直径的两端点，连边时对 u , v , x , y 四点两两求距离更新直径信息。

```cpp
#include<cstdio>
#define lc(x) son[x][0]
#define rc(x) son[x][1]

const int N = 1e5 + 100;

inline int max(int x ,int y){return x < y ? y : x;}
inline void swap(int &x,int &y){int t = x;x = y , y = t;}
inline void read(int &x)
{
	int f = x = 0;char c = getchar();
	while(c > '9' || c < '0') (c == '-') && (f = 1) , c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - '0' , c = getchar();
	(f) && (x = -x);
}

int val[N] , key[N] , fa[N] , Fa[N] , son[N][2] , tipe[N] , r[N] , l[N] , Q , tot;

inline int getfa(int x){return x == Fa[x] ? x : Fa[x] = getfa(Fa[x]);}

inline void update(int x){val[x] = key[x] + val[lc(x)] + val[rc(x)];}
inline int isrt(int x){return rc(fa[x]) != x && lc(fa[x]) != x;}
inline int Rela(int x){return rc(fa[x]) == x;}
inline void flip(int x){tipe[x] ^= 1 , swap(lc(x) , rc(x));}
inline void down(int x){if(tipe[x]) tipe[x] = 0 , flip(lc(x)) , flip(rc(x));}
inline void deal(int x){if(!isrt(x)) deal(fa[x]);down(x);}
inline void Roll(int x)
{
	int f = fa[x] , g = fa[f] , K = Rela(x);
	if(!isrt(f)) son[g][Rela(f)] = x;fa[x] = g;
	son[f][K] = son[x][K ^ 1] , fa[son[x][K ^ 1]] = f;
	son[x][K ^ 1] = f , fa[f] = x , update(f) , update(x);
}

inline void splay(int x)
{
	for(deal(x) ; !isrt(x) ; Roll(x))
		if(!isrt(fa[x])) Roll(Rela(fa[x]) == Rela(x) ? fa[x] : x);
}	

inline void access(int x){for(int f = 0 ; x ; f = x , x = fa[x]) splay(x) , rc(x) = f , update(x);}
inline void makert(int x){access(x) , splay(x) , flip(x);}
inline void link(int x , int y)
{
	makert(x) , access(y) , splay(y);
	fa[x] = y;	
}
inline int dist(int x , int y)
{
	makert(x) , access(y) , splay(y);
	return val[y] - 1;
}

int main()
{
	char c;read(Q);
	for(int v , len1 , len2 , len3 , t; Q -- ; )
	{
		scanf(" %c",&c) , read(v);
		
		if(c == 'B')
		{
			++ tot ,  key[tot] = val[tot] = 1;
			if(v == -1) Fa[tot] = l[tot] = r[tot] = tot;
			else
			{
				link(tot , v) , v = getfa(v) , Fa[tot] = v;
				len1 = dist(tot , l[v]) , len2 = dist(tot , r[v]) , len3 = dist(l[v] , r[v]);
				if(len1 >= len2 && len1 >= len3) r[v] = tot;
				else if(len2 >= len1 && len2 >= len3) l[v] = tot;  
			}
		}
		else
			t = getfa(v) , printf("%d\n",max(dist(v , l[t]) , dist(v , r[t])));
	}
	
	return 0;
}
```




---

## 作者：happybob (赞：1)

注意到一个点到连通块中最远的点，必然是两直径端点之一。

我们需要添加一个点并连边，动态维护直径。经典结论是，两个连通块合并，新的直径端点必然是原来两个连通块的 $4$ 个直径之中。

由于这题只新增一个点而非连通块合并，所以我们只需要比较 $3$ 条路径长度即可。

使用 LCT 动态维护加边和求路径长度即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#include <string>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

int q;

class Union_Find
{
public:
	int fa[N];
	int l[N], r[N];
	void Init()
	{
		for (int i = 0; i < N; i++) fa[i] = l[i] = r[i] = i;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	void merge(int u, int v, int nl, int nr)
	{
		fa[find(u)] = find(v);
		l[find(v)] = nl, r[find(v)] = nr;
	}
}uf;

class Link_Cut_Tree
{
public:
	struct Node
	{
		int val, son[2], fa, sz, sum;
		bool rev;
	}tr[N];
	void pushup(int u)
	{
		tr[u].sum = tr[tr[u].son[0]].sum + tr[tr[u].son[1]].sum + tr[u].val;
	}
	int get(int x)
	{
		return (x == tr[tr[x].fa].son[1]);
	}
	bool isroot(int x)
	{
		return (tr[tr[x].fa].son[1] != x) && (tr[tr[x].fa].son[0] != x);
	}
	void rev(int u)
	{
		tr[u].rev ^= 1;
		swap(tr[u].son[0], tr[u].son[1]);
	}
	void pushdown(int u)
	{
		if (tr[u].rev)
		{
			rev(tr[u].son[0]);
			rev(tr[u].son[1]);
			tr[u].rev = 0;
		}
	}
	void rotate(int x)
	{
		int y = tr[x].fa, z = tr[y].fa;
		int chkx = get(x), chky = get(y), p = isroot(y);
		tr[y].son[chkx] = tr[x].son[chkx ^ 1];
		if (tr[x].son[chkx ^ 1]) tr[tr[x].son[chkx ^ 1]].fa = y;
		tr[x].son[chkx ^ 1] = y;
		tr[y].fa = x;
		tr[x].fa = z;
		if (z && !p) tr[z].son[chky] = x;
		pushup(y);
		pushup(x);
	}
	void update(int u)
	{
		stack<int> st;
		st.push(u);
		while (!isroot(u))
		{
			u = tr[u].fa;
			st.push(u);
		}
		while (st.size())
		{
			pushdown(st.top());
			st.pop();
		}
	}
	void splay(int u)
	{
		update(u);
		while (!isroot(u))
		{
			int y = tr[u].fa, z = tr[y].fa;
			if (!isroot(y))
			{
				if (get(y) ^ get(u)) rotate(u);
				else rotate(y);
			}
			rotate(u);
		}
	}
	void access(int u)
	{
		int z = u;
		for (int y = 0; u; y = u, u = tr[u].fa)
		{
			splay(u);
			tr[u].son[1] = y;
			pushup(u);
		}
		splay(z);
	}
	int findroot(int u)
	{
		access(u);
		while (tr[u].son[0])
		{
			pushdown(u);
			u = tr[u].son[0];
		}
		splay(u);
		return u;
	}
	void makeroot(int u)
	{
		access(u);
		rev(u);
	}
	void link(int x, int y)
	{
		makeroot(x);
		if (findroot(y) != x)
		{
			tr[x].fa = y;
		}
	}
	void split(int u, int v)
	{
		makeroot(u);
		access(v);
	}
}lct;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	uf.Init();
	cin >> q;
	int idx = 0;
	while (q--)
	{
		char c;
		cin >> c;
		if (c == 'B')
		{
			idx++;
			int p;
			cin >> p;
			lct.tr[idx].val = 1;
			lct.pushup(idx);
			if (~p)
			{
				int nl = uf.l[uf.find(p)], nr = uf.r[uf.find(p)];
				lct.link(idx, p);
				lct.split(idx, nl);
				int v1 = lct.tr[nl].sum - 1;
				lct.split(idx, nr);
				int v2 = lct.tr[nr].sum - 1;
				lct.split(nl, nr);
				int v3 = lct.tr[nr].sum - 1;
				if (v3 >= v1 && v3 >= v2) uf.merge(idx, p, nl, nr);
				else if (v1 >= v2 && v1 >= v3) uf.merge(idx, p, idx, nl);
				else uf.merge(idx, p, idx, nr);
			}
		}
		else
		{
			int x;
			cin >> x;
			int l = uf.l[uf.find(x)], r = uf.r[uf.find(x)];
			lct.split(x, r);
			int ans = lct.tr[r].sum - 1;
			lct.split(x, l);
			ans = max(ans, lct.tr[l].sum - 1);
			cout << ans << "\n";
		}
	}
	return 0;
}
```


---

## 作者：fanypcd (赞：1)

给出一个离线，复杂度 $n \log^2 n$ 的做法。

考虑建出所有操作结束后的森林，并对每个点标记操作加入的时间。

对于某个点的查询，假设这是第 $lim$ 次操作，那么只有这个点的子树中加入时间 $\leq lim$ 的点组成的路径是合法的。

直接点分治即可，在每个分治重心处维护下辖范围的所有点到重心的距离。（以到达重心路径上的点的最晚加入时间为下标，维护前缀最大）。

需要记录原树上 $x$ 点到（点分树上 $x$ 的前 $k$ 层祖先）的路径长和经过点的加入时间的最大值（倍增维护）。

注意可能有分治重心处的最大值本身就是从需要查询的子树，所以需要记录最大值、最大值的来向子树，非最大值来向子树贡献的最大值，和前者的来向。如果冲突就换成非最大值来向子树贡献的最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template <class T> inline void read(T &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define inf 0x3f3f3f3f
#define N 100005
int first[N], Next[N << 1], to[N << 1], tot;
inline void add(int x, int y)
{
	Next[++tot] = first[x];
	first[x] = tot;
	to[tot] = y;
	return;
}
int n, m, ord[N];
int bel[N], size[N];
struct LCA
{
	int dep[N], fa[N][21], maxx[N][21];
	void dfs(int u, int pre, int col)
	{
		size[u] = 1;
		bel[u] = col;
		for(int i = first[u]; i; i = Next[i])
		{
			int v = to[i];
			if(v == pre)
			{
				continue;
			}
			dep[v] = dep[u] + 1;
			fa[v][0] = u;
			maxx[v][0] = max(ord[u], ord[v]);
			dfs(v, u, col);
			size[u] += size[v];
		}
	}
	inline void init()
	{
		for(int i = 1; i <= n; i++)
		{
			if(!bel[i])
			{
				dep[i] = 1;
				dfs(i, 0, i);
			}
		}
		for(int j = 1; j <= 20; j++)
		{
			for(int i = 1; i <= n; i++)
			{
				fa[i][j] = fa[fa[i][j - 1]][j - 1];
				maxx[i][j] = max(maxx[i][j - 1], maxx[fa[i][j - 1]][j - 1]);
			}
		}
		return;
	}
	pair<int, int> lca(int x, int y)
	{
		int retsec = 0;
		if(dep[x] > dep[y])
		{
			swap(x, y);
		}
		for(int i = 20; i >= 0; i--)
		{
			if(dep[fa[y][i]] >= dep[x])
			{
				retsec = max(retsec, maxx[y][i]);
				y = fa[y][i];
			}
		}
		if(x == y)
		{
			return make_pair(x, retsec);
		}
		for(int i = 20; i >= 0; i--)
		{
			if(fa[x][i] != fa[y][i])
			{
				retsec = max(retsec, max(maxx[x][i], maxx[y][i]));
				x = fa[x][i], y = fa[y][i];
			}
		}
		retsec = max(retsec, max(maxx[x][0], maxx[y][0]));
		return make_pair(fa[x][0], retsec);
	}
	pair<int, int> query(int x, int y)
	{
		pair<int, int> lc = lca(x, y);
		return make_pair(dep[x] + dep[y] - 2 * dep[lc.first], lc.second);
	}
};
LCA tree;
struct value
{
	int val1, fr1, val2, fr2;
	inline void update(pair<int, int> x)
	{
		if(x.first > val1 || (x.first == val1 && x.second != fr1))
		{
			if(x.second != fr1)
			{
				val2 = val1, fr2 = fr1;
			}
			val1 = x.first, fr1 = x.second;
		}
		else if(x.first > val2 && x.second != fr1)
		{
			val2 = x.first, fr2 = x.second;
		}
		return;
	}
	inline void update(value &x)
	{
		update(make_pair(x.val1, x.fr1)), update(make_pair(x.val2, x.fr2));
		return;
	}
};
struct node
{
	int ord;
	value val;
};
bool operator < (const node &a, const node &b)
{
	return a.ord < b.ord;
}
vector<node> ch[N];
value query(vector<node> &x, int lim)
{
	int pos = upper_bound(x.begin(), x.end(), (node){lim, (value){0, 0, 0, 0}}) - x.begin() - 1;
	return x[pos].val;
}
int vis[N], ban[N], sum, root;
void getroot(int u, int pre)
{
	size[u] = 1, ban[u] = 0;
	for(int i = first[u]; i; i = Next[i])
	{
		int v = to[i];
		if(v == pre || vis[v])
		{
			continue;
		}
		getroot(v, u);
		size[u] += size[v];
		ban[u] = max(ban[u], size[v]);
	}
	ban[u] = max(ban[u], sum - size[u]);
	if(ban[u] < ban[root])
	{
		root = u;
	}
	return;
}
void dfs(int u, int pre, int mxord, int dep, vector<node> &ch)
{
	ch.emplace_back((node){mxord, (value){dep, root, 0, 0}});
	for(int i = first[u]; i; i = Next[i])
	{
		int v = to[i];
		if(v == pre || vis[v])
		{
			continue;
		}
		dfs(v, u, max(mxord, ord[v]), dep + 1, ch);
	}
	return;
}
int dep[N], fat[N];
void solve(int u)
{
	vis[u] = 1;
	ch[u].resize(size[u]);
	ch[u].emplace_back((node){ord[u], (value){0, u, 0, 0}});
	for(int i = first[u]; i; i = Next[i])
	{
		int v = to[i];
		if(vis[v])
		{
			continue;
		}
		sum = size[v];
		getroot(v, root = 0);
		dfs(v, 0, ord[v], 1, ch[u]);
		fat[root] = u;
		dep[root] = dep[u] + 1;
		getroot(root, 0);
		solve(root);
	}
	sort(ch[u].begin(), ch[u].end());
	for(int i = 1; i < (int)ch[u].size(); i++)
	{
		ch[u][i].val.update(ch[u][i - 1].val);
	}
	return;
}
pair<int, int> d[N][21], ques[N];
int qtot;
signed main()
{
	int q;
	read(q);
	char opt[2];
	int x;
	for(int i = 1; i <= q; i++)
	{
		scanf("%s %d", opt, &x);
		if(opt[0] == 'B')
		{
			ord[++n] = i;
			if(x != -1)
			{
				add(n, x), add(x, n);
			}
		}
		else
		{
			ques[++qtot] = make_pair(x, i);
		}
	}
	tree.init();
	ban[0] = inf;
	for(int i = 1; i <= n; i++)
	{
		if(bel[i] == i)
		{
			sum = size[i];
			getroot(i, root = 0);
			dep[root] = 1;
			getroot(root, 0);
			solve(root);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = fat[i]; j; j = fat[j])
		{
			d[i][dep[i] - dep[j]] = tree.query(i, j);
		}
	}
	for(int task = 1; task <= qtot; task++)
	{
		int x = ques[task].first, lim = ques[task].second;
		value ans = query(ch[x], lim);
		for(int i = x; fat[i]; i = fat[i])
		{
			value qfa = query(ch[fat[i]], lim);
			if(d[x][dep[x] - dep[fat[i]]].second <= lim)
			{
				if(qfa.fr1 == i)
				{
					ans.update(make_pair(qfa.val2 + d[x][dep[x] - dep[fat[i]]].first, qfa.fr2));
				}
				else
				{
					ans.update(make_pair(qfa.val1 + d[x][dep[x] - dep[fat[i]]].first, qfa.fr1));
				}
			}
		}
		printf("%d\n", ans.val1);
	}
	return 0;
}
```

---

## 作者：huta0 (赞：0)

看到动态加边果断选择 LCT 来做。

注意到是离 $k$ 距离最远的点，考虑到此点一定是树上直径两端点的其中一个，于是我们考虑用 LCT 维护这个森林中树的直径。

加点操作时用并查集即可，然后再考虑是否能用新点更新树直径两端点的某一个。

最后查询操作，答案即为 $k$ 到树直径上两端点其中之一的距离的最大值。

```cpp
#include<iostream>
#include<unordered_map>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define a_all a.begin(),a.end()
using namespace std;
typedef long long ll;
const int N = 100010;
int n,a,b,cnt;
char op;
unordered_map<int,pair<int,int>> m;
namespace hikari {
	struct dsu {
		int fat[200010];
		void init(int siz=n) {
			rep(i,1,n) fat[i]=i,m[i]={i,i};
		}
		int find(int x) {
			return fat[x]==x?x:fat[x]=find(fat[x]);
		}
		void merge(int x,int y) {
			if(find(x)!=find(y))
			    fat[find(x)]=find(y);
		}
	};
	dsu aa;
	struct node {
		int p,v=1,sum,tag,siz;
		int s[2];
	} tr[2*N];
	#define fa(x) tr[x].p
	#define lc(x) tr[x].s[0]
	#define rc(x) tr[x].s[1]
	#define ntrt(x) lc(fa(x))==x||rc(fa(x))==x
	void pushup(int x) {
		tr[x].sum=tr[lc(x)].sum+tr[rc(x)].sum+tr[x].v;
		tr[x].siz=tr[lc(x)].siz+tr[rc(x)].siz+1;
	}
	void pushdown(int x) {
		if(tr[x].tag) {
			swap(lc(x),rc(x));
			tr[lc(x)].tag^=1;
			tr[rc(x)].tag^=1;
			tr[x].tag=0;
		}
	}
	void pushall(int x) {
		if(ntrt(x)) pushall(fa(x));
		pushdown(x);
	}
	void rotate(int x) {
		int y=fa(x),z=fa(y);
		int k= rc(y)==x;
		if(ntrt(y))
		    tr[z].s[rc(z)==y]=x;
		fa(x)=z;
		tr[y].s[k]=tr[x].s[k^1];
		fa(tr[x].s[k^1])=y;
		tr[x].s[k^1]=y;
		fa(y)=x;
		pushup(y); pushup(x);    
	}
	void splay(int x) {
		pushall(x);
		while(ntrt(x)) {
			int y=fa(x),z=fa(y);
			if(ntrt(y))
			   rotate(rc(y)==x^rc(z)==y?x:y);
			rotate(x);   
		}
	}
	void access(int x) {
		int y=0;
		while(x) {
			splay(x);
			rc(x)=y;
			pushup(x);
			y=x; x=fa(x);
		}
	}
	void mkrt(int x) {
		access(x);
		splay(x);
		tr[x].tag^=1;
	}
	inline int fdrt(int x) {
		access(x);
		splay(x);
		while(lc(x)) pushdown(x),x=lc(x);
		splay(x);
		return x;
	}
	void split(int x,int y) {
		mkrt(x);
		access(y);
		splay(y);
	}
	void link(int x,int y) {
		mkrt(x);
		if(fdrt(y)!=x) fa(x)=y;
	}
	void cut(int x,int y) {
		mkrt(x);
		if(fdrt(y)==x&&fa(y)==x&&!lc(y))
		   rc(x)=fa(y)=0,pushup(x);   
	}
	void change(int x,int val) {
		splay(x);
		tr[x].v=val;
	}
};
using namespace hikari;
int main() {
	cin.tie(0); cout.tie(0);
    cin>>n;
    aa.init();
    rep(i,1,n) {
    	cin>>op>>a;
    	if(op=='B') {
    	    if(a==-1) {
    	    	cnt++;
    	    	continue;
			}
    		if(a!=-1) {
    			link(++cnt,a);
    			aa.merge(cnt,a);
    			
    			int d1=0,d2=0,d3=0;
    			split(m[aa.find(a)].first,m[aa.find(a)].second);
    			d1=tr[m[aa.find(a)].second].sum;
    			split(m[aa.find(a)].first,cnt);
    			d2=tr[cnt].sum;
    			split(m[aa.find(a)].second,cnt);
    			d3=tr[cnt].sum;
    			if(d2>d1) m[aa.find(a)].second=cnt,d1=d2;
    			if(d3>d1) m[aa.find(a)].first=cnt,d1=d3;
			}
		} else {
			int sp = aa.find(a),d1=0,d2=0;
			split(m[sp].second,a);
			d1=tr[a].sum;
			split(m[sp].first,a);
			d2=tr[a].sum;
			cout<<max(d1,d2)-1<<endl;
		}
	}
    return 0;
}
``````

---

## 作者：syLph (赞：0)

显然有动态加边的操作，考虑 LCT。

而这道题其实是要求动态维护连通块（树）的直径。

容易想到每次加边之后，直径仍为 一棵树的两个直径端点和另一棵树的两个直径端点之间的两两距离的最大值。

于是我们只需要用 LCT 去维护一下树上两个点之间的权值距离即可。

同时还需要一个小小的并查集来维护连通块。

即把每个点的权值设为 1，然后 split 一下，答案就是 $siz_{u} - 1$。

然后把两个距离判一下即可。

Code:

```
#include<bits/stdc++.h>
using namespace std;
#define zz cout << 114514 << endl;
#define yy cout << " ------- " << endl;
#define pp cout << " I AKIOI " << endl; 
const int maxn = 200010;
typedef struct{int a,b;} tup;
int ch[maxn][2],rev[maxn],siz[maxn],fa[maxn],num,m,q,Fa[maxn],sy[maxn],lph[maxn];
tup ar[maxn];

inline void init(){
	for(int i = 1 ; i <= q ; i ++) Fa[i] = i,siz[i] = 1,ar[i] = {i,i};	
}

inline int find(int x){
	if(x == Fa[x]) return x;
	return Fa[x] = find(Fa[x]);
} 

inline void clear(int x){
    rev[x] = ch[x][0] = ch[x][1] = fa[x] = siz[x] = 0;
}

inline int is_root(int x){
    return (ch[fa[x]][0] != x || !ch[fa[x]][0]) && (ch[fa[x]][1] != x || !ch[fa[x]][1]);
}

inline int is_right_ch(int x){
    return ch[fa[x]][1] == x;
}

inline void pushup(int x){
    siz[x] = ((!ch[x][0]) ? 0 : siz[ch[x][0]]) + 1 + ((!ch[x][1]) ? 0 : siz[ch[x][1]]);
    return;
}

inline void pushdown(int x){
    if(rev[x]){
        if(ch[x][0]) swap(ch[ch[x][0]][0],ch[ch[x][0]][1]),rev[ch[x][0]] ^= 1;
        if(ch[x][1]) swap(ch[ch[x][1]][0],ch[ch[x][1]][1]),rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
}

void update(int x){
    if(!is_root(x)) update(fa[x]);
    pushdown(x);
}

void rotate(int x){
    int y = fa[x],z = fa[y],cx = is_right_ch(x),cy = is_right_ch(y);
    int &t = ch[x][cx^1];
    fa[x] = z; if(!is_root(y)) ch[z][cy] = x;
    ch[y][cx] = t,fa[t] = y,t = y,fa[y] = x;
    pushup(y),pushup(x),pushup(z);
}

void splay(int x){
    update(x);
    for(int f = fa[x] ; f = fa[x],!is_root(x) ; rotate(x))
        if(!is_root(f)) rotate(is_right_ch(x)==is_right_ch(f)?f:x);
}

void access(int x){
    for(int f = 0 ; x ; f = x,x = fa[x])
        splay(x),ch[x][1] = f,pushup(x);
}

void make_root(int x){
    access(x),splay(x),swap(ch[x][0],ch[x][1]),rev[x] ^= 1;
}

void split(int x,int y){
    make_root(x),access(y),splay(y);
}

int find_root(int x){
    access(x),splay(x);
    while(ch[x][0]) x = ch[x][0];
    splay(x); return x;
}

void cut(int x,int y){
    split(x,y);
    if(!ch[x][1] && x == ch[y][0]) fa[x] = ch[y][0] = 0;
}

void link(int x,int y){
    if(find_root(x) != find_root(y)){
        make_root(x),fa[x] = y;
    }
}

signed int main(){
	scanf("%d",&q);init();
	for(signed int i = 1 ; i <= q ; i ++){
		char r[3]; int a,dis1,dis2;
		scanf("%s%d",r,&a);
		if(r[0] == 'B'){
			num += 1;
			if(a == -1) continue;
			else {
				int k = find(a); 
				Fa[num] = k;
				link(num,a);
				split(num,ar[k].a);dis1 = siz[ar[k].a] - 1;
				split(num,ar[k].b);dis2 = siz[ar[k].b] - 1;	
				if(dis1>lph[k]) lph[k] = dis1,ar[k] = {num,ar[k].a};
				if(dis2>lph[k]) lph[k] = dis2,ar[k] = {num,ar[k].b};
			}
		}
		else{
			int k = find(a);
			split(a,ar[k].a);  dis1 = siz[ar[k].a] - 1;
			split(a,ar[k].b);  dis2 = siz[ar[k].b] - 1;
			printf("%d\n",max(dis1,dis2));
		}
	}
	return 0; 	
}
```



---

## 作者：CrTsIr400 (赞：0)

# 完全在线，单 log 小清新做法

别被难度是紫就吓着了，这题做法没那么难。感觉大家的什么 LCT 什么点分治的做法都太复杂了。

一个很显然的结论是，距离每个点最远的点，无非就是每个点所在树的直径的端点之一。

考虑直接维护直径。因为 `B` 操作就是给某点下面挂一个新节点，这样我们维护这个新节点的倍增 `father` 数组，顺便维护深度数组。

这个新节点有可能构成直径。于是我们还要支持查询这个点到直径两个端点的距离，此时可以使用深度数组 + LCA 直接做。顺便用并查集（实际上直接记录就行了）维护每个点所在树的根就行了，把直径的距离、两个端点记录在树根上。

然后查询一个点 $x$ 就查询它和所在树直径两个端点距离最大值就行了。

时间复杂度 $O(q\log q)$。代码极短，只有 1.1k。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=1e5+10;
#define IL inline
I n,f[N][18],fa[N],d[N];
array<I,3>ltk[N];
IL I gf(I x){return x==fa[x]?x:fa[x]=gf(fa[x]);}
IL V mrg(I x,I y){fa[gf(x)]=gf(y);}
IL I lca(I x,I y){if(gf(x)!=gf(y))return 0;
	if(d[x]<d[y])swap(x,y);
	for(I i=17;~i;--i)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	for(I i=17;~i;--i)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];}
IL I dis(I x,I y){return d[x]+d[y]-d[lca(x,y)]*2;}
IL V nwnd(I faid){++n;
	if(-1!=faid){
		mrg(n,gf(faid));
		d[n]=d[faid]+1;
		f[n][0]=faid;
		fo(i,1,17)f[n][i]=f[f[n][i-1]][i-1];
		auto&cur=ltk[gf(n)];
		cur=max({cur,{dis(cur[1],n),cur[1],n},{dis(cur[2],n),cur[2],n}});
	}else ltk[n]={0,n,n},d[n]=1;
}I q;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>q;
	iota(fa,fa+N,0);
	fo(i,1,q){char c;I x;
		cin>>c>>x;
		if(c=='B')nwnd(x);
		else {auto cur=ltk[gf(x)];
			printf("%d\n",max(dis(cur[1],x),dis(cur[2],x)));}}
	return 0;}
```

---

## 作者：Rushroom (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4271)

> 有一棵树，初始没有节点。有 $q$ 次操作，操作分两种：
>
> 1. 新建一个节点，将它与 $p$ 节点连接。（若 $p=-1$，则不与其它节点相连 ）
> 2. 查询在 $k$ 节点所在的连通块中，距它最远的点的距离。
>
> $q \le 10^5$。
>

树的直径入门题目。

经典结论：树中距离一个节点最远的点一定是直径的两个端点之一。证明见 [OI Wiki](https://oi-wiki.org/graph/tree-diameter/#做法-1-两次-dfs)。

于是我们只需要维护树的直径，先把所有操作离线下来，建出最终的树，倍增求 LCA。新加节点时用两个直径端点到它的距离更新直径即可。

## Code

```cpp
int q, n = 0, p[N], fa[N][20], dep[N];
char op[N];
int dis(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int X = x, Y = y;
	for (int i = 19; i >= 0; i--) {
		if (fa[X][i] != -1 && dep[fa[X][i]] >= dep[Y]) {
			X = fa[X][i];
		}
	}
	if (X == Y) return dep[x] - dep[X];
	for (int i = 19; i >= 0; i--) {
		if (fa[X][i] != -1 && fa[Y][i] != -1 && fa[X][i] != fa[Y][i]) {
			X = fa[X][i];
			Y = fa[Y][i];
		}
	}
	return dep[x] - dep[X] + dep[y] - dep[Y] + 2;
}
int rt[N], d[N][2], cnt = -1;
void solve() {
	cin >> q;
	rep(i, q) {
		cin >> op[i] >> p[i];
		if (p[i] != -1) p[i]--;
		if (op[i] == 'B') {
			if (p[i] != -1) dep[n] = dep[p[i]] + 1, rt[n] = rt[p[i]];
			else rt[n] = n;
			fa[n++][0] = p[i];
		}
	}
	repp(i, 19) {
		rep(j, n) {
			if (fa[j][i - 1] == -1) fa[j][i] = -1;
			else fa[j][i] = fa[fa[j][i - 1]][i - 1];
		}
	}
	rep(i, q) {
		if (op[i] == 'B') {
			++cnt;
			if (p[i] ==  -1) d[cnt][0] = d[cnt][1] = cnt;
			else {
				int x = d[rt[p[i]]][0], y = d[rt[p[i]]][1];
				if (dis(x, cnt) > dis(d[rt[p[i]]][0], d[rt[p[i]]][1])) {
					d[rt[p[i]]][0] = x;
					d[rt[p[i]]][1] = cnt;
				}
				if (dis(y, cnt) > dis(d[rt[p[i]]][0], d[rt[p[i]]][1])) {
					d[rt[p[i]]][0] = y;
					d[rt[p[i]]][1] = cnt;
				}
			}
		}
		else {
			int x = d[rt[p[i]]][0], y = d[rt[p[i]]][1];
			cout << max(dis(x, p[i]), dis(y, p[i])) << endl;
		}
	}
}
```



---

