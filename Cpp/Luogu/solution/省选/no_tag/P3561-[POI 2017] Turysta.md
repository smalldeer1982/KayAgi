# [POI 2017] Turysta

## 题目描述

给出一个 $n$ 个点的有向图，任意两个点之间有且仅一条有向边。

对于每个点 $v$，求出从 $v$ 出发的一条经过点数最多，且没有重复经过同一个点两次及两次以上的简单路径。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 2 \times 10^3$。

## 样例 #1

### 输入

```
4
1
1 1
1 0 1```

### 输出

```
4 1 2 3 4
3 2 3 4
3 3 4 2
3 4 2 3```

# 题解

## 作者：Semsue (赞：11)

板子题：https://www.luogu.com.cn/problem/P3561

### 此题题意

给你定一个竞赛图，对每个点求出一条不重复经过点的路径，使其经过的点最多。$1\le n\le 2000$。

### 竞赛图的一些性质

1，缩点之后是一条链

准确地说不是一条链，而是对于每个拓扑序在前的连通分量，都会向拓扑序再后的连通分量连边。由竞赛图的定义易知。

那么这么看这个性质就很显然了。任意两个拓扑序相邻的连通分量必有连边。

2，竞赛图必有哈密顿通路

这个可以构造证明，下文将会提到。

3，强连通竞赛图必有哈密顿回路。

这个也是构造证明，还是下文会提到。

### 做法

那么此题做法就很显然了，先缩点，然后对于每个强连通分量，求哈密顿回路。然后就可以对任意一个强连通分量任意点进，任意点出了。

那么重点是如何求哈密顿通路/回路。

这里给出一个 $O(n^2)$ 的构造。记 $x\to y$ 代表存在 $x$ 到 $y$ 的路径。

首先构造哈密顿通路，考虑增量构造。

假设我已经求出前 $i-1$ 个点的一个哈密顿通路，考虑将 $i$ 加入。设前面的哈密顿通路起点为 $s$ 终点为 $t$，每个点 $x$ 下一个点为 $nxt_x$。如果 $t\to i$ 或者 $i\to s$ 那么直接将 $i$ 加入这条链即可，将 $t$ 或 $s$ 设成 $i$。

否则一定是下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/nr3i76pb.png)

那么显然一定存在一个 $x$ 使得 $x\to i,i\to nxt_x$。将 $i$ 插到 $x,nxt_x$ 之间，即令 $nxt_i=nxt_x,nxt_x=i$ 即可。

至此我们完成了哈密顿通路的构造。时间复杂度 $O(n^2)$。

之后考虑强连通竞赛图的哈密顿回路，首先求出哈密顿通路，还是设起点为 $s$，终点为 $t$。

考虑找到第一个 $x$ 使得 $x\to s$，也就是第一可以成环的位置，设为新的 $t$。现在得到了一个环 $s-> nxt_s-> \dots -> t-> s$。这里我们不把 $t-> s$ 这条边显示出来，也就是说 $nxt_t$ 还是哈密顿通路上的下一个点。另外由于这个图是强连通的，所以一定可以找到这样一个 $x$。

然后考虑加入 $nxt_t$，还是设为 $i$。

如果 $i\to s$，那么直接扩展即可。否则我们直接找到第一个 $x$ 使得 $i\to x$，那么我们可以简单地构造出下面这样的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/9dln2v5z.png)

即设 $x$ 的前一个是 $y$，那么构造 $i-> x-> \dots->t-> s-> \dots-> y->i$。此时为了保证 $nxt_t$ 还是哈密顿通路上的点，我们令 $s=t,t=i$，修改 $nxt_s$ 为原来的 $s$，$nxt_y$ 为 $i$ 即可。由于 $x$ 是第一个 $i\to x$，所以一定有 $y\to i$。

如果压根找不到 $x$ 呢？仔细想想发现确实有这种情况，因为只有后继节点有一个连向前面那么就保证了强连通的性质。既然如此，那这些点不如直接摆烂，让后面那个点去往前连，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/htufw549.png)

即 $i->x->\dots ->t->s->\dots->y->nxt_t->\dots->i$。注意这里这里 $nxt_t$ 即 $t$ 在哈密顿通路中的下一个点，即图中圆圈中最左边的点。然后和上面类似，只需把 $nxt_y=i$ 修改为 $nxt_y=nxt_t$，这里 $t$ 是原来的 $t$。注意由于红圈中的点没有向前面连边，那么前面的每个点都会向其中的点连边，所以一定有 $y\to nxt_t$。

然后这样一直跑，由于强连通，所以 $x$ 最后一定存在，所以一定会求出一条哈密顿回路其中的一条链，其中起点是 $s$，终点是 $t$ 且 $t\to s$。

容易发现这个流程的复杂度为 $O(n^2)$。

好像可以做到更优复杂度，还是算了/qd。

### 参考代码

板子题：https://www.luogu.com.cn/problem/P3561

变量稍有不同。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
const int maxn = 2005;
template <typename T>
void read(T &x) {
	T flag = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') flag = -1;
	for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= flag;
}
int a[maxn][maxn];
int n, dfn[maxn], low[maxn], stk[maxn], col[maxn], top, Dfn, cnt;
bool vis[maxn];
vector<int> vec[maxn], G[maxn], V[maxn], ans[maxn];
int in[maxn];
void tarjan(int u) {
	dfn[u] = low[u] = ++Dfn;
	stk[++top] = u;
	vis[u] = 1;
	for (int v : vec[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		cnt++;
		while (stk[top] != u){
			col[stk[top]] = cnt;
			vis[stk[top]] = 0;
			top--;
		}
		col[u] = cnt;
		vis[u] = 0;
		top--;
	}
}
int nxt[maxn];
queue<int> q;
void solve(int c) {
	// 求强连通分量 c 的一条哈密顿回路 
	// 先求一条哈密顿通路 
	if (V[c].size() == 1)
		return;
	int s = V[c][0], t = s;
	for (int i = 1; i < (int)V[c].size(); i++) {
		int x = V[c][i];
		if (a[t][x]) nxt[t] = x, t = x;
		else if (a[x][s]) nxt[x] = s, s = x;
		else
			for (int j = s; j != t; j = nxt[j])
				if (a[j][x] && a[x][nxt[j]]) 
					{ nxt[x] = nxt[j]; nxt[j] = x; break; }
	}
	t = 0;
	for (int i = nxt[s]; i != 0; i = nxt[i]){
		if (t) {
			if (a[i][s])
				{ t = i; continue; }
			for (int j = s, k = nxt[s]; j != t; j = k, k = nxt[k]) {
				if (a[i][k]) 
					{ nxt[j] = nxt[t]; nxt[t] = s; s = k; t = i; break; }
			}
		} else if (a[i][s]) t = i;
	}
	nxt[t] = s;
}
int pos[maxn];
int main() {
	read(n);
	for (int i = 2; i <= n; i++)
		for (int j = 1, x; j <= i - 1; j++){
			read(x);
			if (x)
				vec[j].eb(i), a[j][i] = 1;
			else
				vec[i].eb(j), a[i][j] = 1;
		}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) V[col[i]].eb(i);
	for (int i = 1; i <= n; i++)
		for (int j : vec[i])
			if (col[i] != col[j])
				G[col[i]].eb(col[j]), in[col[j]]++;
	for (int i = 1; i <= cnt; i++)
		if (!in[i]) q.push(i);
	top = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		stk[++top] = u; pos[u] = top;
		for (int v : G[u]) {
			in[v]--;
			if (!in[v]) q.push(v);
		}
	}
	for (int i = 1; i <= top; i++)
		solve(stk[i]);
	for (int i = 1; i <= n; i++) {
		int lst = i, now = pos[col[i]];
		while (1) {
			if (V[stk[now]].size() == 1) {
				ans[i].eb(lst);
				if (now == top) break;
				lst = V[stk[++now]][0];
				continue;
			}
			ans[i].eb(lst);
			for (int x = nxt[lst]; x != lst; x = nxt[x])
				ans[i].eb(x);
			if (now == top) break;
			lst = V[stk[++now]][0];
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", (int)ans[i].size());
		for (int j : ans[i])
			printf("%d ", j);
		puts("");
	}
	return 0;
}
```

### reference

https://www.cnblogs.com/TheRoadToTheGold/p/8439160.html#_label1

https://www.cnblogs.com/Hs-black/p/13749764.html

# 最后的最后

![](https://cdn.luogu.com.cn/upload/image_hosting/jh934nfg.png)

---

## 作者：jiangly (赞：5)

#### 题意

给定一张 $n$ ($2\le n\le 2000$) 个点的竞赛图，找到从每个点开始的经过点数最多的简单路径。

#### 题解

众所周知 $\ge 3$ 个点的强连通竞赛图有哈密顿回路，因此从 $u$ 开始最长的路径就是拓扑序在 $u$ 所属的强连通分量之后 (包括其本身) 的强连通分量的哈密顿路径相连。在每个强连通分量找到哈密顿回路即可。找哈密顿回路时，首先找到一条哈密顿路径 (按任意顺序加点即可)，然后找到路径上第一个向第一个点有边的点，作为初始的环。之后每次找到第一个向环中点有边的点，将它及之前未加入的点加入即可。

时间复杂度：$O(n^2)$。

#### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
int n;
std::vector<std::vector<bool>> g;
int cntScc, dfsClock;
std::vector<int> dfn, low, belong;
std::vector<int> stk;
std::vector<std::vector<int>> ans;
std::vector<std::vector<int>> h;
void tarjan(int u) {
    dfn[u] = low[u] = dfsClock++;
    stk.push_back(u);
    for (int v = 0; v < n; ++v) {
        if (g[u][v]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if (belong[v] == -1) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        do {
            v = stk.back();
            belong[v] = cntScc;
            stk.pop_back();
        } while (v != u);
        ++cntScc;
    }
}
auto solve(std::vector<int> v) {
    if (int(v.size()) == 1)
        return v;
    std::vector<int> h;
    for (auto u : v)
        h.insert(std::find_if(h.begin(), h.end(), [&](int v) {return g[u][v];}), u);
    auto it = std::find_if(h.begin(), h.end(), [&](int v) {return g[v][h[0]];}) + 1;
    std::vector<int> c(h.begin(), it);
    while (it != h.end()) {
        auto r = it;
        while (std::find_if(c.begin(), c.end(), [&](int v) {return g[*r][v];}) == c.end())
            ++r;
        auto p = c.begin();
        while (p + 1 != c.end() && !(g[*p][*it] && g[*r][*(p + 1)]))
            ++p;
        c.insert(p == c.end() ? c.begin() : p + 1, it, r + 1);
        it = r + 1;
    }
    return c;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    g.assign(n, std::vector<bool>(n));
    dfn.assign(n, -1);
    low.resize(n);
    belong.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int x;
            std::cin >> x;
            g[i][j] = x ^ 1;
            g[j][i] = x;
        }
    }
    for (int i = 0; i < n; ++i)
        if (dfn[i] == -1)
            tarjan(i);
    h.resize(cntScc);
    ans.resize(n);
    for (int i = 0; i < n; ++i)
        h[belong[i]].push_back(i);
    for (int i = 0; i < cntScc; ++i) {
        h[i] = solve(h[i]);
        for (auto it = h[i].begin(); it != h[i].end(); ++it) {
            int u = *it;
            ans[u].insert(ans[u].end(), it, h[i].end());
            ans[u].insert(ans[u].end(), h[i].begin(), it);
            for (int j = i - 1; j >= 0; --j)
                ans[u].insert(ans[u].end(), h[j].begin(), h[j].end());
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i].size();
        for (int u : ans[i])
            std::cout << " " << u + 1;
        std::cout << "\n";
    }
    return 0;
}

```



---

## 作者：hjxhjx (赞：3)

好像大家都是利用竞赛图的神奇性质做的，这里给出一个适合我这种无脑选手的做法。

首先对于每个出发点 $S$，以 $S$ 为根搜出一棵 dfs 树。答案路径的长度显然不能超过这棵树的大小。

然后我们观察树上的一个分叉（根节点为 $1$，图上忽略了非树边）：

![](https://cdn.luogu.com.cn/upload/image_hosting/m9q79tnu.png)

dfs 的顺序是：$1→2→4→3→5$。

因为这是个竞赛图，所以我们知道 $2$ 和 $5$ 之间的非树边一定是 $5→2$，否则 $5$ 应该是 $2$ 的儿子。

换句话说，给 dfs 遍历到的点赋一个时间戳，对于 dfs 树上任意两个没有祖先关系的点，他们之间的边一定是从时间戳大的指向时间戳小的。

那么做法也就呼之欲出了：每次走时间戳最大的儿子，需要回溯时就通过非树边一步跳到需要到的点，答案路径长度等于 dfs 树大小。

对于上图，答案路径就是 $1→3→5→2→4$。容易发现这其实是翻转的后序遍历。

直接做的复杂度是 $O(n^3)$，使用 bitset 优化可以做到 $O(\frac{n^3}{w})$，可以通过本题。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline static int read(){
    int sum=0,neg=0,ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=sum*10+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

int n,L,arr[2005],l;
struct Bit{
    ull a[32];
    ull&operator[](int x){return a[x];}
    void flip(int x){a[x>>6]^=1ull<<(x&63);}
    int operator&(Bit&b){
        for(int i=0;i<=L;i++) if(a[i]&b[i])
            return __builtin_ctzll(a[i]&b[i])|i<<6;
        return 0;
    }
}e[2005],vis;
void dfs(int u,int v=0){
    for(vis.flip(u);(v=e[u]&vis);) dfs(v);
    arr[++l]=u;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n=read(),L=n>>6;
    for(int i=2;i<=n;i++) for(int j=1;j<i;j++)
        if(read()) e[j].flip(i); else e[i].flip(j);
    for(int i=1;i<=n;putchar('\n'),l=0,i++){
        memset(&vis,0xff,8*L+8),dfs(i),printf("%d ",l);
        for(int j=l;j>=1;j--) printf("%d ",arr[j]);
    } return 0;
}

```

---

## 作者：CommandSR (赞：2)

## 题意

[link](https://www.luogu.com.cn/problem/P3561)

## 题解

首先给出两条引理：

- Reidei 定理：竞赛图一定有汉密尔顿路径。
- Camion-Moon 定理：强连通竞赛图一定有汉密尔顿回路。

首先给出的图一定是一个竞赛图，根据引理 1，我们尝试先随便构造一条哈密尔顿路径。考虑现在已有路径 $s \rightarrow t$，考虑插入点 $x$，若存在连边 $x \rightarrow s$ 则插入头部，若存在连边 $t \rightarrow x$ 则插入尾部，否则根据竞赛图性质必有两个点 $u$，$v$ 满足 $u \rightarrow x$ 且 $x \rightarrow v$，将 $x$ 插入中间即可。

然后 Tarjan 缩点，根据引理 2，发现所有 SCC 对应了哈密尔顿路径上的一段区间，考虑对于每一个 SCC 构造哈密尔顿回路。仍然考虑之前的增量构造方式，每次取出一段路径的开头点，尝试用之前的方法把它扔到尽量靠后的位置，以给后面的点留出更大的答案。最后对于每一个点的答案就是对应 SCC 的答案和后面的 SCC 构成的哈密尔顿路径区间连起来。

## Code

```cpp
// Problem: P3561
#include <bits/stdc++.h>
#define ll long long
#define sz(x) (int)x.size()
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define D(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline ll rd() {
	ll x = 0; bool f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = 0; ch = getchar(); }
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return (f ? x : (-x));
}
const int N = 2e3 + 3;
int n, e[N][N];
vector<int> ans[N], path, st;
int low[N], dfn[N], dfc, stk[N], top, scc[N], scnt;
bool vis[N];
void Tarjan(int u) {
	dfn[u] = low[u] = ++dfc, stk[++top] = u, vis[u] = 1;
	F(v, 1, n) {
		if (!e[u][v]) continue;
		if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int tmp; ++scnt;
		do {
			tmp = stk[top--];
			vis[tmp] = 0, scc[tmp] = scnt;
		} while (tmp != u);
	}
}
int main() {
	// 竞赛图一定存在哈密尔顿路径，先动态加点求出一条
	n = rd();
	F(i, 2, n) {
		F(j, 1, i-1) {
			bool x = rd();
			if (x) e[j][i] = 1;
			else e[i][j] = 1;
		}
	}
	F(i, 1, n) {
		if (!path.size()) { path.push_back(i); continue; }
		if (e[i][path.front()]) { path.insert(path.begin(), i); continue; }
		if (e[path.back()][i]) {path.push_back(i); continue; }
		F(j, 1, sz(path)-1) {
			if (e[path[j-1]][i] && e[i][path[j]]) {
				path.insert(path.begin()+j, i);
				break;
			}
		}
	}
	F(i, 1, n) if (!dfn[i]) Tarjan(i);
	memset(vis, 0, sizeof vis);
	for (int l = 0; l < n; ) { // 双指针确定 scc
		int r = l;
		while (r+1 < n && scc[path[l]] == scc[path[r+1]]) ++r;
		st.clear();
		F(j, l, r) st.push_back(path[j]);
		int cnt = 0;
		while (cnt < r - l + 1) {
			if (!vis[st.front()]) {
				vis[st.front()] = 1, ++cnt;
				for (int v : st) ans[st.front()].push_back(v);
			}
			if (cnt >= r - l + 1) break;
			int t = st[0]; // 尝试把 t 丢到靠后面位置使后入的路径长度更长
			st.erase(st.begin());
			if (e[st.back()][t]) { st.push_back(t); continue; }
			D(j, sz(st)-1, 1) {
				if (e[st[j-1]][t] && e[t][st[j]]) {
					st.insert(st.begin()+j, t);
					break;
				}
			}
		}
		F(j, l, r) F(k, r + 1, sz(path)-1) ans[path[j]].push_back(path[k]);
		l = r + 1;
	}
	F(i, 1, n) {
		cout << sz(ans[i]) << ' ';
		for (int u : ans[i]) cout << u << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

这种可达性问题肯定要考虑缩点求强联通分量。

一个很重要的观察：由于本题的图是**竞赛图**，如果强联通分量 $U$ 能到达强联通分量 $V$，那么 $\forall u\in U,v\in V$，边 $(u,v)$ 的方向都是 $u \to v$。

因此我们只需要关注**强联通分量内部的最长路径**即可，因为**强联通分量内部路径的终点不影响答案**，只需要其路径最长即可。

我们声称必存在一条路径包含了强联通分量内的所有点。

考虑增量构造，假设我们找了路径 $u \to x_1 \to x_2 \cdots \to x_t$。考虑所有未在路径中但是在同一强联通分量中的点的集合 $S$。

如果 $\exists v \in S$ 使得 $(x_t,v)$ 的方向为 $x_t \to v$，直接将其接到末尾；否则，如果 $\exists v \in S$ 使得 $(x_{t-1},v)$ 的方向为 $x_{t-1} \to v$，将 $x_{t-1} \to x_t$ 替换为 $x_{t-1} \to v \to x_t$；否则，再考虑 $x_{t-2}$，替换为 $x_{t-2} \to v \to x_{t-1} \to x_t$……

因为它们是强联通的，所以必定能找到这样的 $x_i$ 和 $v$，将 $x_i$ 之后的路径替换为 $x_i \to v \to x_{i+1} \to x_{i+2} \to \cdots \to x^t$ 即可。

但是很遗憾，这样会使你的复杂度起飞，应该只能做到 $O(\dfrac{n^4}{w})$。但是如果你能找到一条哈密顿回路，那就完美了——所有点都可以用上。

我们依旧通过构造的方式找到哈密顿回路。显然我们可以找到第一个路径上的点 $x_i$ 满足 $x_i \to u$ 的边存在，这样我们找到了一个环 $C_1$。

考虑 $x_{i+1}$、$x_{i+2}$、$\cdots$，必然有一个点向 $C$ 有连边，找到第一个，不妨设这条边是 $x_t \to c_0$。考虑 $c_0$ 在环上的上一个点为 $c_1$，则容易知道对于 $\forall i+1 \le j < t$，都存在 $c_1 \to x_j$ 的边。那么在环中 $c_1 \to c_0$ 的中间插入 $c_1 \to x_{i+1} \to \cdots \to x_t \to c_0$ 即可。

考虑这个过程中每条边最多被检查一次，所以复杂度为 $O(m)=O(n^2)$。

感觉自己能做出来纯粹是因为提前被透露了“本题是构造题”这个基本原则，实际上很容易让人陷入“本题是最优化题”的陷阱。

代码（感觉还是有一点细节的）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10;
int n,tot,cs,col[MAXN],low[MAXN],dfn[MAXN],in[MAXN],to[MAXN][MAXN];
vector<int> occ[MAXN],ans[MAXN],G[MAXN];
stack<int> st[MAXN],tmp;
void tarjan(int u) {
	low[u]=dfn[u]=++tot,in[u]=1,tmp.push(u);
	for(auto v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);	
	}
	if(low[u]==dfn[u]) {
		++cs;
		while(tmp.top()!=u) col[tmp.top()]=cs,in[tmp.top()]=0,tmp.pop();
		col[tmp.top()]=cs,in[tmp.top()]=0,tmp.pop();
	}
	return ;
}
vector<int> hcir[MAXN];
int vis[MAXN];
void solve(int c) {
	vector<int> chain;
	for(auto id:occ[c]) for(auto v:G[id]) if(col[v]==c) st[id].push(v);
	chain.push_back(occ[c][0]),vis[occ[c][0]]=1;
	ffor(i,1,occ[c].size()-1) {
		roff(j,chain.size()-1,0) {
			int id=chain[j],psl=-1;
			while(!st[id].empty()) {
				int v=st[id].top();
				st[id].pop();
				if(col[v]==c&&!vis[v]) {
					vis[v]=1,psl=v;
					break ;
				}
			}
			if(psl!=-1) {
				chain.insert(chain.begin()+j+1,psl);
				break ;	
			}
		}
	}
	int st=-1;
	ffor(i,0,chain.size()-1) if(to[chain[i]][chain[0]]) st=i;
	if(st==-1) return hcir[c]=chain,void();
	for(auto id:chain) vis[id]=0;
	ffor(i,0,st) hcir[c].push_back(chain[i]),vis[chain[i]]=1;
	ffor(i,st+1,chain.size()-1) {
		int id=chain[i],flg=0;
		for(auto v:G[id]) if(col[v]==c&&vis[v]) flg=v;
		if(flg) {
			int pos=0;
			ffor(j,0,hcir[c].size()-1) if(hcir[c][j]==flg) pos=j;
			if(st+1==i) {
				ffor(j,0,hcir[c].size()-1) {
					int id1=hcir[c][j],id2=hcir[c][(j+1)%hcir[c].size()];
					if(to[id1][id]&&to[id][id2]) {
						hcir[c].insert(hcir[c].begin()+j+1,id);
						break ;	
					}
				}
				vis[id]=1,st=i;
			}
			else {
				roff(j,i,st+1) hcir[c].insert(hcir[c].begin()+pos,chain[j]),vis[chain[j]]=1;
				st=i;
			}
		}
	}
	return ;
}
void get(int u) {
	int tpos=0;
	ffor(i,0,hcir[col[u]].size()-1) if(hcir[col[u]][i]==u) tpos=i;
	ffor(i,0,hcir[col[u]].size()-1) ans[u].push_back(hcir[col[u]][tpos]),tpos=(tpos+1)%hcir[col[u]].size();
	int lst=ans[u][ans[u].size()-1];
	pair<int,int> mx={0,0};
	for(auto v:G[u]) if(col[v]!=col[u]) {
		if(!ans[v].size()) get(v);
		mx=max(mx,{ans[v].size(),v});
	}
	for(auto id:ans[mx.second]) ans[u].push_back(id);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		ffor(j,1,i-1) {
			int flg;
			cin>>flg;
			to[j][i]=flg,to[i][j]=flg^1;
			if(flg) G[j].push_back(i);
			else G[i].push_back(j);
		}
	}
	ffor(i,1,n) if(!dfn[i]) tarjan(i);
	ffor(i,1,n) occ[col[i]].push_back(i);
	ffor(i,1,cs) solve(i);
	ffor(i,1,n) if(!ans[i].size()) get(i);
	ffor(i,1,n) {
		cout<<ans[i].size()<<' ';
		for(auto j:ans[i]) cout<<j<<' ';
		cout<<'\n';	
	}
	return 0;
}
```

---

## 作者：ELECTRON_wa (赞：2)

## P3561 Turysta

[P3561](https://www.luogu.com.cn/problem/P3561 "P3561")
#### 题意：
一 $n$ 个点的有向图，保证任意两个点间有且仅有一条边，对于每个点 $u$，求出一条从 $u$ 出发的经过点最多的路径（点不能重复走）。
#### 题解
先说明几个概念：
1. 竞赛图：一个有向图，每对顶点之间都有一条边。
1. 哈密顿通路：在一个有向图或无向图中经过每个节点一次且仅一次的通路称作哈密顿通路。
2. 哈密顿回路：图G的一个回路，若它只通过图的每一个节点一次，就是哈密顿回路。
3. 哈密顿图：能找到一条路径，从一点出发，必须经过所有的点一次,最终回到起点的图（图中有的边可以不经过,但是不会有边被经过两次）。

还有几个性质：

1. 竞赛图一定存在哈密顿通路。
2. 强连通竞赛图一定存在哈密顿回路。

现在描述如何通过竞赛图构造哈密顿通路。

假设现在已经有一条路径 $v_1\to v_2\to v_3\to v_4$。如果下一个点 $v_5$ 直接和路径起点 $(s)\ \ v_1$ 连边，路径起点换到 $v_5$，整个路径变为$v_5\to v_1\to v_2\to v_3\to v_4$（恭喜我们的路径延长啦）。如果$v_5$和路径尾部 $(t)$ 直接连边同理。其余情况一定有中间某一个点（设为 $v_x$）向 $v_5$ 连边，$v_5$ 再向 $v_x$ 在原路径上的下一个点连边（把这句话简单证明一下：在竞赛图中 $v_5$ 会和所有的点有边相连，假设是路径上其他点向 $v_5$ 连边为状态 $0$，$v_5$ 向路径上其他点连边为状态 $0$，如果路径上相邻两点状态不同 $v_5$ 就可以插入其中，此时路径首尾点和 $v_5$ 的状态一定不同（此时为 $s$ 指向 $v_5$，$v_5$ 指向 $t$）），这样就可以把 $v_5$ 插入到 $v_x$ 后面（恭喜我们的路径有扩张啦）。

现在已经有哈密顿通路（起点为 $s$，终点为 $t$）啦，考虑在强连通竞赛图中构造哈密顿回路。

先在路径上找到一个指向 $s$ 的点 $x_1$（第一个可以成环），把 $x_1$ 变成新的 $t$，现在有了的一个环。设点 $x_1$ 的下一个点为 $i$，如果 $i$ 直接指向 $s$，就直接扩展，要不然可以顺着从 $s$ 到 $t$（现在的 $t$ 是找到第一个环后新的 $t$）找到第一个 $x_2$ 满足 $i\to x_2$，设 $x_2$ 在路径上前面一个点为 $y$，现在构造出了一条 $i\to x_2\to ... \to t\to s\to... \to y\to i$ 的路径，现在让刚刚得 $t$ 成为新的 $s$，刚刚的 $i$ 成为新的 $t$。如果找不到 $x_2$ 满足 $i\to x_2$ 就跳过这个 $i$ 顺着路径找到下一个点使它成为新的 $i$。

现在我们已经有了每一个强连通分量中的哈密顿回路，可以做到任意进出每一个强连通分量，对所有的强连通分量拓扑排序，然后对每个点求答案，先按照所在强连通分量的哈密顿回路取每个点，然后在跳到拓扑序在这个强连通分量后面的强连通分量中继续取哈密顿回路上的点，最后输出答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn=2e3+10;
int scc[maxn],dfn[maxn],low[maxn],vis[maxn],s[maxn],tp,dfn1,scc1;
vector<int> v[maxn];
int to[maxn][maxn],nxt[maxn];
vector<int> ans[maxn];
void tarjan(int u)
{
    dfn[u]=low[u]=++dfn1; s[++tp]=u; vis[u]=1;
    for(int v=1;v<=n;v++)
    {
    	if(to[u][v])
    	{
			if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
			else if(vis[v]) low[u]=min(low[u],dfn[v]);
		}
    }
    if(dfn[u]==low[u])
    {
        scc1++;
        while(s[tp]!=u)
        {
            v[scc1].push_back(s[tp]); scc[s[tp]]=scc1; vis[s[tp]]=0; tp--;
        }
        v[scc1].push_back(u); scc[u]=scc1; vis[u]=0; tp--;
    }
}
void solve(int a)
{
	if(v[a].size()==1) return;
	int s,t,x;
	s=t=v[a][0];
	for(int i=1;i<v[a].size();i++)
	{
		x=v[a][i];
		if(to[t][x]){nxt[t]=x;t=x;continue;}
		if(to[x][s]){nxt[x]=s;s=x;continue;}
		for(int j=s;j!=t;j=nxt[j])
		{
			if(to[j][x]&&to[x][nxt[j]])
			{
				nxt[x]=nxt[j];
				nxt[j]=x;
				break;
			}
		}
	}
	t=0;
	for(int i=nxt[s];i;i=nxt[i])
	{
		if(to[i][s]) t=i;
		else if(t!=0)
		{
			for(int j=s;j!=t;j=nxt[j])
			{
				if(to[i][nxt[j]])
				{
					x=nxt[j];nxt[j]=nxt[t];nxt[t]=s;s=x;t=i;break;
				}
			}
		}
	}
	nxt[t]=s;
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i-1;j++)
        {
            int x; scanf("%d",&x);
            if(x==1) to[j][i]=1;
            else to[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=scc1;i++)
    {
        solve(i);
    }
    int x,k;
    for(int i=1;i<=n;i++)
    {
        x=i;k=scc[i];
        while(1)
        {
            ans[i].push_back(x);
            if(v[k].size()==1)
            {
                if(k==1) break;
                k--;
                x=v[k][0]; continue;
            }
            for(int j=nxt[x];j!=x;j=nxt[j])
            {
                ans[i].push_back(j);
            }
            if(k==1) break;
            k--; x=v[k][0];
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i].size()<<' ';
        for(int j=0;j<ans[i].size();j++)
        {
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
}
```


---

## 作者：LastKismet (赞：1)

# 前置知识
## 竞赛图
可以视作给无向完全图的每条边设置了一个方向产生的有向图。
## 哈密顿路径
一条只经过图上的边使得每个点都被经过且仅被经过 $1$ 次的路径。
## 哈密顿回路
一条哈密顿路径，倘若末尾可以连向开头，那么就形成了一条哈密顿回路。

# 竞赛图有关性质
每个竞赛图必然存在哈密顿路径（Redei 定理），强连通竞赛图必然存在哈密顿回路（Camion-Moon 定理）。竞赛图缩点之后形成链状 DAG，且仍然是竞赛图。

以上性质都比较显然，可以感性理解或者自行搜索。

# 找哈密顿路径
以任意顺序依次向路径中加入当前图内的点即可，具体加入流程为：
* 若当前点指向路径开头，那么就加入到路径开头。
* 若当前点被路径结尾指向，那么就加入到路径结尾。
* 否则顺次遍历路径找到第一个当前点可指向的点，然后把当前点插入到这个点前面。这个选中的位置前一个点必然指向当前点，且必然存在这样一个点，因为当前点必然指向路径结尾。

# 找哈密顿回路
首先这必须得是一个强连通竞赛图。

为了方便，我们先找出一条哈密顿路径，然后在路径上顺序遍历更新。

假如我们当前已经得到了左侧一个环和右侧一条链，其中链就是哈密顿路径的一部分，现在有这条链的下一个节点。

首先必然存在链尾连向当前点的边，因此可以直接把当前点加入链尾。

然后遍历整个环，如果能找到一个位置，使得环上这一点存在向链头的连边，且链尾可以连向下一点，那么就把整条链插入这个位置。

初始时找到第一个连向路径开头的位置即可得到一个环了。

为什么这样必然有解，考虑这个竞赛图强连通，且在上述策略下，如果一个点无法加入环，必然是因为环中全是连向这个点的（由于是按哈密顿路径来依次搞得因此环内至少有一个点连向当前点），那么当链尾存在向环的连边时，前一个位置必然连向链头。而整个图强连通，因此最后一个点必然指向环。

模板就直接详见代码了。

# 题解
上面说过，缩点之后整个图仍是 DAG，那么每个强连通分量内都可以跑哈密顿回路，然后在缩完点的图内 topo 即可，不难发现缩完点后，一个强连通分量指向另一个强连通分量，那么前者内每个节点都存在指向后者内每个节点的边，因此除了起始分量需要以起始点为回路起点，此后的所有分量均可任意开头遍历且任意位置结束，这样找方案会简单很多。

这道题重点就在于输出方案以练习找哈密顿回路。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
template<typename Type> using vec=vector<Type>;
template<typename Type> using grheap=priority_queue<Type>;
template<typename Type> using lrheap=priority_queue<Type,vector<Type>,greater<Type>>;
#define fir first
#define sec second
#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define chmax(a,b) a=max(a,b)
#define chmin(a,b) a=min(a,b)
#define rep(i,x,y) for(int i=(x);i<=(y);++i)
#define per(i,x,y) for(int i=(x);i>=(y);--i)
#define repl(i,x,y) for(int i=(x);i<(y);++i)
#define ReadFile(f) freopen(#f".in","r",stdin);freopen(#f".out","w",stdout);

struct mint {
	int x,mod;
	inline mint(int o=0,int p=998244353){x=o;mod=p;}
	inline mint & operator=(ll o){return x=o%mod,(x+=mod)>=mod&&(x-=mod),*this;}
	inline mint & operator+=(mint o){return (x+=o.x)>=mod&&(x-=mod),*this;}
	inline mint & operator-=(mint o){return (x-=o.x)<0&&(x+=mod),*this;}
	inline mint & operator*=(mint o){return x=(ll)x*o.x%mod,*this;}
	inline mint & operator^=(ll b){mint res(1,mod);for(;b;b>>=1,*this*=*this)if(b&1)res*=*this;return x=res.x,*this;}
	inline mint & operator^=(mint o){return *this^=o.x;}
	inline mint & operator/=(mint o){return *this*=(o^=(mod-2));}
	inline mint & operator++(){return *this+=1;}
	inline mint & operator--(){return *this-=1;}
	inline mint operator++(int o){mint res=*this;return *this+=1,res;}
	inline mint operator--(int o){mint res=*this;return *this-=1,res;}
	friend inline mint operator+(mint a,mint b){return a+=b;}
	friend inline mint operator-(mint a,mint b){return a-=b;}
	friend inline mint operator*(mint a,mint b){return a*=b;}
	friend inline mint operator/(mint a,mint b){return a/=b;}
	friend inline mint operator^(mint a,ll b){return a^=b;}
	friend inline mint operator^(mint a,mint b){return a^=b;}
	friend inline bool operator<(mint a,mint b){return a.x<b.x;}
	friend inline bool operator>(mint a,mint b){return a.x>b.x;}
	friend inline bool operator<=(mint a,mint b){return a.x<=b.x;}
	friend inline bool operator>=(mint a,mint b){return a.x>=b.x;}
	friend inline bool operator==(mint a,mint b){return a.x==b.x;}
	friend inline istream & operator>>(istream &in,mint &o){ll x;return in>>x,o=x,in;}
	friend inline ostream & operator<<(ostream &ot,mint o){return ot<<o.x,ot;}
};

typedef double flt;

template<typename Type> inline void read(Type &x){x=0;Type f=1,s=1;char ch=getchar();while(!isdigit(ch)&&~ch){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch))x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))s/=10,x=x+(ch-48)*s,ch=getchar();}x*=f;}
template<typename Type> inline void write(Type x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');}
inline void read(string &s){s.clear();char ch=getchar();while(isspace(ch))ch=getchar();while(!isspace(ch)&&~ch)s+=ch,ch=getchar();}
inline void read(char &ch){ch=getchar();while(isspace(ch))ch=getchar();}
inline void write(const string &s){for(auto c:s)putchar(c);}
inline void write(const char &ch){putchar(ch);}
inline void write(const flt &x){printf("%.18LF",(long double)x);}
inline void write(const mint &m){write(m.x);}
inline void write(const char *x){while(*x)putchar(*(x++));}
template<typename Type,typename...T> inline void read(Type &x,T&...y){read(x),read(y...);}
template<typename Type> inline void put(const Type &x,char ch='\n'){write(x);if(ch)putchar(ch);}

const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

const int N=2e3+5;

int n;
vec<int> g[N];

int dcnt;
int dfn[N],low[N];
stack<int> stk;bool ins[N];
int scnt;
int scc[N],siz[N];
vec<int> SCC[N];
void tarjan(int now){
    dfn[now]=low[now]=++dcnt;
    stk.push(now),ins[now]=1;
    for(auto nxt:g[now]){
        if(!dfn[nxt]){
            tarjan(nxt);
            chmin(low[now],low[nxt]);
        }else if(ins[nxt])chmin(low[now],dfn[nxt]);
    }
    if(low[now]>=dfn[now]){
        ++scnt;
        while(1){
            int tp=stk.top();
            scc[tp]=scnt,++siz[scnt];
            stk.pop();ins[tp]=0;
            SCC[scnt].pub(tp);
            if(tp==now)break;
        }
    }
}

vec<int> g2[N];
int d[N];

int tcnt;
int nb[N],arr[N];
void topo(){
    queue<int> q;
    rep(i,1,scnt)if(!d[i])q.push(i);
    while(!q.empty()){
        int now=q.front();q.pop();
        arr[nb[now]=++tcnt]=now;
        for(auto nxt:g2[now])if(!--d[nxt])q.push(nxt);
    }
}

int suf[N];

int hd[N],tl,pne[N];
bool G[N][N];
void gpath(int sid){
    hd[sid]=0,tl=0;
    for(auto i:SCC[sid]){
        if(!hd[sid]){
            hd[sid]=tl=i;
            continue;
        }
        if(G[i][hd[sid]])pne[i]=hd[sid],hd[sid]=i;
        else if(G[tl][i])pne[tl]=i,tl=i;
        else{
            for(int j=hd[sid];1;j=pne[j])if(G[i][pne[j]]){
                pne[i]=pne[j];
                pne[j]=i;
                break;
            }
        }
    }
    int k=0;
    for(int i=hd[sid];i;i=pne[i])if(G[i][hd[sid]]){
        k=i;
        break;
    }
    for(int i=pne[k];i;i=pne[i]){
        if(G[i][hd[sid]]&&G[k][pne[k]])k=i;
        else{
            for(int j=hd[sid];j!=k;j=pne[j]){
                if(G[i][pne[j]]&&G[j][pne[k]]){
                    int be=pne[k];
                    pne[k]=pne[i];
                    pne[i]=pne[j];
                    pne[j]=be;
                    i=k;
                    break;
                }
            }
        }
    }
    if(!k)k=hd[sid];
    pne[k]=hd[sid];
    if(siz[sid]>1)for(int i=pne[k];1;i=pne[i]){
        assert(G[i][pne[i]]);
        if(i==k)break;
    }
}

inline void Main(){
    read(n);
    rep(i,1,n)repl(j,1,i){
        int o;read(o);
        if(o)g[j].pub(i);
        else g[i].pub(j);
    }
    rep(i,1,n)if(!dfn[i])tarjan(i);
    rep(i,1,n)for(auto j:g[i]){
        if(scc[i]!=scc[j])g2[scc[i]].pub(scc[j]),++d[scc[j]];
        else G[i][j]=1;
    }
    topo();
    per(i,scnt,1)suf[i]=suf[i+1]+siz[arr[i]];
    rep(i,1,scnt)gpath(i);
    rep(i,1,n){
        put(suf[nb[scc[i]]],' ');
        put(i,' ');
        for(int j=pne[i];j!=i;j=pne[j])put(j,' ');
        rep(j,nb[scc[i]]+1,scnt){
            put(hd[arr[j]],' ');
            for(int k=pne[hd[arr[j]]];k!=hd[arr[j]];k=pne[k])put(k,' ');
        }
        puts("");
    }
}
int main(){
	// ReadFile(___);
	// #define MultiTasks
	#ifdef MultiTasks
	int t;read(t);while(t--)
	#endif
	Main();
	return 0;
}
```

---

## 作者：xxxxxzy (赞：1)

竞赛图哈密顿路构造板子，写篇题解。

## 哈密顿路径构造

Redei 定理：任意 $n$ 阶竞赛图都存在哈密顿路径。

从一个顶点开始，依次加入竞赛图中的每个顶点，加入顶点 $x$ 时，假设已经构造出路径 $p_1\to p_2 \to... \to p_k$：

+ 如果 $(x,p_1) \in E$，将 $x$ 添加到路径首，将路径变为 $x \to p_1\to p_2 \to... \to p_k$。
+ 如果 $(p_k,x) \in E$，将 $x$ 添加到路径尾，将路径变为 $p_1\to p_2 \to... \to p_k \to x$。
+ 否则一定存在路径上的一对相邻点 $p_i \to p_{i+1}$，满足 $(p_i,x),(x,p_{i+1})\in E$，暴力找到 $i$ 并将 $x$ 插入即可，将路径变为 $p_1\to p_2 \to... \to p_i \to x \to p_{i+1} \to ... \to p_k$。

## 哈密顿回路构造

Camion - Moon 定理：强连通竞赛图一定存在哈密顿回路。

首先找出竞赛图的一条哈密顿路径，设为 $p_1\to p_2 \to... \to p_n$。

其次，暴力找到最小的 $x$ 满足 $(p_x,p_1) \in E$，这样 $p_1\to p_2 \to ... \to p_x \to p_1$ 就形成了一个环。

同时维护环 $p_{1\sim k}$ 和一条链 $q_{1\sim m}$，初始 $k=x,m=0$，且满足环上的每个点 $a$ 对链上的每个点 $b$ 有 $(a,b)\in E$，考虑按顺序加入 $p_{x+1}$ 到 $p_n$ 的所有点。假设现在加入点 $y$：

+ 如果 $\forall z\in[1,k],(p_z,i) \in E$，那么把 $z$ 加入链的尾部。
+ 否则一定会存在 $(p_z,q_1),(q_m,p_{z+1})\in E$，那么把整条链加入环并清空链。

由图的强连通性可知，这样的构造一定合法。

## P3561

回到本题，首先考虑给原图跑强连通分量缩点，由竞赛图的性质可以知道，竞赛图缩点后是一条链加上若干条链前方往后方连的边。

所以说最优方案肯定是从链上的点出发，把后面的所有点全部遍历完，为了达到这个目标，我们对每个强连通分量跑哈密顿回路，然后就可以构造出来了。

给一个自己写的丑陋实现：

```cpp
#include <bits/stdc++.h> 
#define Debug(fmt, args...) fprintf(stderr, "(func %s, line #%d): " fmt, __func__, __LINE__, ##args), fflush(stderr)
#define debug(fmt, args...) fprintf(stderr, fmt, ##args), fflush(stderr)
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define U(i, a, b) for (int i = (a); i < (b); i++)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vi vector <ll>
#define fv inline void
#define fn inline static
#define sz(x) (i32)(x.size())
#define bp(x) __builtin_popcount(x)
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i8 = char; using i16 = short; using i32 = int; using i64 = ll; using i128 = __int128_t; using db = long double;
using namespace std;
const i32 N = 2e3 + 5;
i32 dfn[N], low[N], in[N], stk[N], ins[N], c[N], siz[N], idt[N], tid[N], ans[N], e[N][N], scc, cnt, n, x, tot, tp;
vi G[N], E[N], S[N];
fv Tarjan(i32 u) {
  dfn[u] = low[u] = ++tot, stk[++tp] = u, ins[u] = 1;
  for (i32 v : G[u]) {
    if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
    else if (ins[v]) low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    scc++; i32 x;
    do x = stk[tp--], c[x] = scc, ins[x] = 0, siz[scc]++, S[scc].pb(x);
    while (x != u);
  }
}
fv tpsort() {
  queue <i32> q;
  rep (i, 1, scc) if (!in[i]) ans[i] = siz[i], q.push(i);
  while (q.size()) {
    i32 u = q.front(); q.pop();
    idt[u] = ++cnt, tid[cnt] = u;
    for (i32 v : E[u]) {
      ans[v] = ans[u] + siz[v];
      if (--in[v] == 0) q.push(v);
    }
  }
}
struct List {
  i32 nxt[N], pre[N], head, tail;
  List() { head = N - 1, tail = N - 2, nxt[head] = tail, pre[tail] = head; }
  fv clr() { head = N - 1, tail = N - 2, nxt[head] = tail, pre[tail] = head; }
  i32 back() { return pre[tail]; }
  i32 front() { return nxt[head]; }
  bool empty() { return nxt[head] == tail; }
  fv ins(i32 x, i32 y, i32 z) { nxt[x] = y, nxt[y] = z, pre[z] = y, pre[y] = x; }
  fv ins(i32 x, vi& y, i32 z) {
    rep (i, 0, (i32)y.size() - 2) nxt[y[i]] = y[i + 1], pre[y[i + 1]] = y[i];
    nxt[x] = y.front(), pre[y.front()] = x, nxt[y.back()] = z, pre[z] = y.back();
  }
} R[N];
List P, U;
fn List findpath(i32 k) {
  P.clr();
  for (i32 u : S[k]) {
    if (P.empty()) P.ins(P.head, u, P.tail);
    else if (e[P.back()][u]) P.ins(P.back(), u, P.tail);
    else if (e[u][P.front()]) P.ins(P.head, u, P.front());
    else {
      for (i32 x = P.nxt[P.front()]; x != P.tail; x = P.nxt[x]) {
        if (e[P.pre[x]][u] && e[u][x]) {
          P.ins(P.pre[x], u, x); break;
        }
      }
    }
  }
  return P;
}
fn List findring(i32 k) {
  if (siz[k] == 1) {
    List P; P.nxt[S[k][0]] = P.pre[S[k][0]] = S[k][0];
    return P;
  }
  P = findpath(k), U.clr();
  i32 x;
  for (x = P.front(); x != P.tail; x = P.nxt[x]) {
    U.ins(U.back(), x, U.tail);
    if (e[x][P.front()]) break;
  }
  x = P.nxt[x];
  
  i32 b = U.back(), f = U.front();
  U.nxt[b] = f, U.pre[f] = b; vi T;
//  cerr << k << "\n";
//  i32 y = P.front(), z = y;
//  do {
//    cerr << z << " "; z = U.nxt[z];
//  } while (z != y);
  for (; x != P.tail; x = P.nxt[x]) {
    T.pb(x); i32 y = P.front();
    bool flg = 0;
    do {
      i32 ny = U.nxt[y];
      if (e[T.back()][ny] && e[y][T.front()]) {
        U.ins(y, T, ny), T.clear(), flg = 1; break;
      }
      y = ny;
    } while (y != P.front());
  }
  
  return U;
}
int main() {
//  IOS;
  cin >> n;
  rep (i, 2, n) rep (j, 1, i - 1) {
    cin >> x;
    if (x) G[j].pb(i), e[j][i] = 1;
    else G[i].pb(j), e[i][j] = 1;
  } 
  rep (i, 1, n) if (!dfn[i]) Tarjan(i);
  rep (u, 1, n) {
    for (i32 v : G[u]) {
      if (c[u] != c[v]) E[c[v]].pb(c[u]), in[c[u]]++;
    }
  }
  tpsort();
  rep (i, 1, scc) R[i] = findring(i);
  rep (i, 1, n) {
    i32 k = c[i]; cout << ans[k] << " "; i32 x = i;
    do cout << x << " ", x = R[k].nxt[x];
    while (x != i);
    drep (j, idt[k] - 1, 1) {
      i32 k = tid[j], y = S[k][0], x = y;
      do cout << x << " ", x = R[k].nxt[x];
      while (x != y);
    }
    cout << "\n";
  }
}
```

---

## 作者：_Ch1F4N_ (赞：0)

考虑缩点，由于是竞赛图所以缩点后一定是一条链。

先考察答案大小，我们猜测一个竞赛图中的 SCC 一定存在任意点出发的哈密顿路径，于是答案就是把点所在的 SCC 以及这个 SCC 在链上可以抵达的所有 SCC 大小加和。

构造答案等价于对每个点找其所在 SCC 中从其出发的哈密顿路径，为了好做，我们强化下问题，不妨对每个 SCC 直接构造哈密顿回路。

考虑建立 dfs 生成树构造，任选一个点建立 dfs 生成树，观察到树上横叉边一定是 dfs 序大的指向小的，且由于是竞赛图所有横叉边一定存在，于是考虑在 dfs 生成树上按照访问顺序的倒序合并一个点的所有子树的序列，再把这个点本身加入到序列开头，最后根处会得到从根出发的一条哈密顿路径。

但是我们想找的是一条回路，注意到找到的哈密顿路劲上最后一个点是 dfs 生成树上最左边的点（先访问的点放在左边），如果这个点存在到根的返祖边就最好，否则我们找到这个点的返祖边能回到的最浅的点，以这个点作为新根再次 dfs，优先遍历这个点到原先 dfs 生成树上最左边的点间的路径，得到的新 dfs 生成树再按照上面构造哈密顿路径的方法构造，得到的结果便是一条哈密顿回路。

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3+114;
bool E[maxn][maxn];
int n;
int dfn[maxn],low[maxn],dfncnt;
int col[maxn],cl,sz[maxn];
int vis[maxn],stk[maxn],tp;
bool e[maxn][maxn];
vector<int> seq[maxn];
int F[maxn];
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    stk[++tp]=u;
    vis[u]=1;
    for(int v=1;v<=n;v++){
        if(E[u][v]==1){
            if(dfn[v]==0){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]==1){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if(low[u]>=dfn[u]){
        cl++;
        F[cl]=u;
        while(stk[tp]!=u){
            col[stk[tp]]=cl;
            sz[cl]++;
            vis[stk[tp]]=0;
            tp--;
        }
        col[u]=cl;
        vis[u]=0;
        sz[cl]++;
        tp--;
    }
}
int dp[maxn],nxt[maxn];
int use[maxn];
int dep[maxn];
int g[maxn];
int root;
void dfs(int u,int now){
    use[u]=1;
    int d=0;
    for(int v=1;v<=n;v++){
        if(col[v]==now&&E[u][v]==1){
            if(use[v]==0){
                if(g[u]==0) g[u]=v;
                d++;
                dep[v]=dep[u]+1;
                dfs(v,now);
            }
        }
    }
    if(d==0&&root==0){
        for(int v=1;v<=n;v++){
            if(col[v]==now&&E[u][v]==1){
                if(root==0||dep[v]<dep[root]) root=v;
            }
        }
    }
}
vector<int> sol(int u,int now){
    use[u]=1;
    vector<int> res={u};
    vector< vector<int> > son;
    if(use[g[u]]==0&&g[u]!=0){
        son.push_back(sol(g[u],now));
    }   
    for(int v=1;v<=n;v++){
        if(col[v]==now&&E[u][v]==1&&use[v]==0&&v!=g[u]){
            son.push_back(sol(v,now));
        }
    }
    reverse(son.begin(),son.end());
    for(vector<int> x:son){
        for(int y:x) res.push_back(y);
    }
    return res;
}
void build(){
    int s=1;
    for(int i=2;i<=cl;i++){ 
        if(e[s][i]==1) s=i;
    }
    dp[s]=sz[s];
    for(int i=2;i<=cl;i++){
        int t=0;
        for(int j=1;j<=cl;j++){
            if(dp[j]==0){
                t=j;
            }
        }
        for(int j=1;j<=cl;j++){
            if(dp[j]==0){
                if(e[t][j]==1) t=j;
            }
        }
        dp[t]=sz[t]+dp[s];
        nxt[t]=s;
        s=t;
    }
    //构造哈密顿回路
    for(int i=1;i<=cl;i++){
        if(sz[i]!=1){
            root=0;
            dfs(F[i],i);
            memset(use,0,sizeof(use));
            seq[i]=sol(root,i);
        }else seq[i].push_back(F[i]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            cin>>E[j][i];
            E[i][j]=E[j][i]^1;
        }
    }
    for(int i=1;i<=n;i++){
        if(dfn[i]==0) tarjan(i);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(col[i]!=col[j]) e[col[i]][col[j]]|=E[i][j];
    build();
    for(int i=1;i<=n;i++){
        cout<<dp[col[i]]<<" ";
        int t=0;
        for(int j=0;j<seq[col[i]].size();j++){
            if(seq[col[i]][j]==i) t=j;
        }
        for(int j=0;j<seq[col[i]].size();j++,t=(t+1)%seq[col[i]].size()) cout<<seq[col[i]][t]<<" ";
        int now=nxt[col[i]];
        while(now!=0){
            for(int x:seq[now]) cout<<x<<" ";
            now=nxt[now];
        }
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：_LiWenX_ (赞：0)

一种构造的方法。

首先是竞赛图，不难想到先求出一条这个竞赛图的哈密顿路径，然后将它缩点，不同的 SCC 把这个哈密顿路径划分成了若干个区间。

先简述一下如何求哈密顿路径，考虑对于一个长度为 $n-1$ 的哈密顿路径中添加节点 $n$，如果当前链的末尾到 $n$ 有边，直接接进去，如果 $n$ 到链开头有边，可以把 $n$ 设为开头，否则，我们一定可以在链上找到两个相邻的节点 $x,y$，满足存在边 $x\to n,n\to y$，把 $n$ 插入到它们之间即可，显然这是正确并且必然可以添加进去的。

现在的问题是，对于一个 SCC 中的点，每一个点都求出一个在这个 SCC 中的哈密顿路径。

首先我们找到其中的任何一条哈密顿路径，这是容易的，设链的开头是 $s$，我们把 $s$ 放到尽量考后的位置，具体来说，如果链末尾 $t$，存在边 $t\to s$，直接把 $s$ 插入到末尾，否则寻找链上最靠后的 $x,y$，满足存在边 $x\to s,s\to y$，将 $s$ 在这里插入即可。由于这些点在一个 SCC 中，所以这样的 $x,y$ 是一定可以找到的，这样不断的操作就一定可以求出以 SCC 中每一个点开头的哈密顿路径。

简单证明一下，我们只用说明初始链中末尾节点 $t$，可以找到以 $t$ 开头的哈密顿路径即可。

由于这是一个 SCC，必然存在 $x$ 满足 $t\to x$，那么假如我们找到了以 $x$ 开头的哈密顿路径即可证明，发现 $x+1\sim t$ 中的点在 $x$ 找到哈密顿路径后都有解了，不妨把这些点的连边合并到 $x$ 上，然后删掉这些节点，此时 $s\sim x$ 这些点显然还在一个 SCC 中，但是问题的规模已经减小了，我们可以一直把这个问题递归下去，直到问题变成 $s$ 开头的哈密顿路径，那么我们就证明完成了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,e[2005][2005];
int sta[2005],top,vis[2005],dfn[2005],low[2005],D;
int col[2005],k;
void tar(int now){
	sta[++top]=now;
	vis[now]=1;
	dfn[now]=low[now]=++D;
	for(int u=1;u<=n;u++){
		if(!e[now][u]) continue;
		if(dfn[u]){
			if(vis[u]) low[now]=min(low[now],dfn[u]);
		}
		else{
			tar(u);
			low[now]=min(low[now],low[u]);
		}
	}
	if(low[now]==dfn[now]){
		k++;
		while(sta[top+1]!=now){
			col[sta[top]]=k;
			vis[sta[top]]=0;
			top--;
		}
	}
}
vector<int> ans[2005];
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			int x;cin>>x;
			if(x) e[j][i]=1;
			else e[i][j]=1;
		}
	}
	vector<int> vec;
	for(int i=1;i<=n;i++){
		if(!vec.size()){
			vec.push_back(i);
			continue;
		}
		if(e[i][vec[0]]){
			vec.insert(vec.begin(),i);
			continue;
		}
		if(e[vec.back()][i]){
			vec.push_back(i);
			continue;
		}
		for(int j=1;j<(int)vec.size();j++){
			if(e[vec[j-1]][i]&&e[i][vec[j]]){
				vec.insert(vec.begin()+j,i);
				break; 
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tar(i);
	}
	memset(vis,0,sizeof(vis));
	for(int l=0;l<n;l++){
		int r=l;
		while(r+1<n&&col[vec[r+1]]==col[vec[l]]) r++;
		vector<int> t;
		for(int i=l;i<=r;i++) t.push_back(vec[i]);
		int num=0;
		while(num<r-l+1){
			if(!vis[t[0]]){
				num++;
				for(int u:t) ans[t[0]].push_back(u);
				vis[t[0]]=1;
			}
			if(num==r-l+1) break;
			int s=t[0];
			t.erase(t.begin());
			if(e[t.back()][s]){
				t.push_back(s);
				continue;
			}
			for(int i=t.size();i>=1;i--){
				if(e[s][t[i]]&&e[t[i-1]][s]){
					t.insert(t.begin()+i,s);
					break;
				}
			}
		}
		for(int i=l;i<=r;i++){
			for(int j=r+1;j<(int)vec.size();j++){
				ans[vec[i]].push_back(vec[j]);
			}
		}
		l=r;
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i].size()<<' ';
		for(int u:ans[i]) cout<<u<<' ';
		cout<<'\n';
	}
}
```

---

