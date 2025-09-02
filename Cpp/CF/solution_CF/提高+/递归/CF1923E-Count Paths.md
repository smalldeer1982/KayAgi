# Count Paths

## 题目描述

You are given a tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Every vertex is colored in some color, denoted by an integer from $ 1 $ to $ n $ .

A simple path of the tree is called beautiful if:

- it consists of at least $ 2 $ vertices;
- the first and the last vertices of the path have the same color;
- no other vertex on the path has the same color as the first vertex.

Count the number of the beautiful simple paths of the tree. Note that paths are considered undirected (i. e. the path from $ x $ to $ y $ is the same as the path from $ y $ to $ x $ ).

## 样例 #1

### 输入

```
4
3
1 2 1
1 2
2 3
5
2 1 2 1 2
1 2
1 3
3 4
4 5
5
1 2 3 4 5
1 2
1 3
3 4
4 5
4
2 2 2 2
3 1
3 2
3 4```

### 输出

```
1
3
0
3```

# 题解

## 作者：ganpig (赞：20)

~~最后十分钟极限速度切此题才没掉大分~~

一种又快又简洁的线性做法。

只需 DFS 一遍，维护 $cnt_i$，表示若当前结点颜色为 $i$，有多少个结点可以直接连过来。

容易发现 $u$ 的子树内与 $u$ 同色的结点不可能连到这颗子树外，因此 DFS 到 $u$ 的时候先将原来的 $cnt_{c_u}$ 记录为 $bak$ 并加入答案，每次进入下一层时设为 $1$（$u$ 可以连到子树内），最后再还原为 $bak+1$（除了原来的结点，$u$ 也可以跟后面的结点连）。

因为是按 DFS 序来的，一条路径不会重复计算，不用考虑去重。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        std::vector<int> c(n + 1);
        for (int i = 1; i <= n; i++)
            std::cin >> c[i];
        std::vector<std::vector<int>> g(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            std::cin >> u >> v;
            g[u].emplace_back(v), g[v].emplace_back(u);
        }

        std::vector<int> cnt(n + 1);
        long long ans = 0;
        auto dfs = [&](auto self, int u, int fa) -> void {
            int bak = cnt[c[u]];
            for (int v : g[u])
                if (v != fa)
                    cnt[c[u]] = 1, self(self, v, u);
            ans += bak, cnt[c[u]] = bak + 1;
        };
        dfs(dfs, 1, 0);
        std::cout << ans << '\n';
    }
}
```

---

## 作者：wxzzzz (赞：5)

### 思路

考虑对于每种颜色建出虚树，原问题就转化为：

对于颜色 $k$，以所有 $u\ (c_u=k)$ 为关键点建出其虚树，求其虚树上有多少对点 $(x,y)$，满足 $x,y$ 之间的简单路径上所有点 $u\ (u\notin \{x,y\})$，满足 $c_u\ne k$。

以下图为例（加粗的点为关键点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/5q3a9meb.png)

可以发现，对于每个白色连通块，令 $cnt$ 为与其相连的黑点数，其贡献为 $\dfrac{cnt\times(cnt-1)}{2}$。

但是这样会漏算，因为相邻的黑点也满足要求。

考虑在每两个点之间新加一个颜色为 $-1$ 的点，就可以直接用上述方法统计答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/viuajmy5.png)

### 代码

注意初始化细节。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, ts, idx, root, s[1000005], d[1000005], f[1000005], c[1000005], p[1000005];
int v[1000005], h[1000005], ne[1000005], son[1000005], top[1000005], dfn[1000005];
long long ans;
vector<int> tp[1000005];
bitset<1000005> vis;
void add(int x, int y) {
    v[++idx] = y, ne[idx] = h[x], h[x] = idx;
}
bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}
void dfs1(int x) {
    s[x] = 1;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == f[x])
            continue;

        f[y] = x, d[y] = d[x] + 1;
        dfs1(y), s[x] += s[y];

        if (s[y] > s[son[x]])
            son[x] = y;
    }
}
void dfs2(int x, int tp) {
    dfn[x] = ++ts, top[x] = tp;

    if (son[x])
        dfs2(son[x], tp);

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y != son[x] && y != f[x])
            dfs2(y, y);
    }
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (d[top[x]] > d[top[y]])
            x = f[top[x]];
        else
            y = f[top[y]];
    }

    if (d[x] > d[y])
        swap(x, y);

    return x;
}
int dfs3(int x, int F, int col) {
    int ret = 0;
    vis[x] = 1;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == F)
            continue;

        if (c[y] == col)
            ret++;
        else
            ret += dfs3(y, x, col);
    }

    return ret;
}
long long solve(int x) {
    for (int i = 1; i <= m; i++)
        h[p[i]] = -1, vis[p[i]] = 0;

    for (int i = 1; i <= idx; i++)
        v[i] = ne[i] = 0;

    idx = m = 0;
    sort(tp[x].begin(), tp[x].end(), cmp);

    for (int i = 0; i < tp[x].size(); i++) {
        p[++m] = tp[x][i];

        if (i)
            p[++m] = LCA(tp[x][i - 1], tp[x][i]);
    }

    sort(p + 1, p + m + 1, cmp);
    m = unique(p + 1, p + m + 1) - p - 1;
    int tm = m, cnt = n;

    for (int i = 2, lca; i <= tm; i++) {
        lca = LCA(p[i - 1], p[i]);

        if (lca != p[i]) {
            p[++m] = ++cnt;
            c[p[m]] = -1;
            add(lca, p[m]), add(p[m], lca);
            add(p[m], p[i]), add(p[i], p[m]);
        }
    }

    long long ret = 0;

    for (int i = 1, tmp; i <= m; i++) {
        if (c[p[i]] != x && !vis[p[i]]) {
            tmp = dfs3(p[i], 0, x);
            ret += 1ll * tmp * (tmp - 1) / 2;
        }
    }

    return ret;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> t;

    while (t--) {
        for (int i = 1; i <= n * 2; i++) {
            h[i] = -1, vis[i] = 0;
            f[i] = d[i] = s[i] = 0;
            son[i] = top[i] = dfn[i] = 0;
            tp[i].clear();
        }

        for (int i = 1; i <= idx; i++)
            v[i] = ne[i] = 0;

        ans = idx = ts = 0;
        cin >> n;

        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            tp[c[i]].push_back(i);
        }

        for (int i = 1, x, y; i < n; i++) {
            cin >> x >> y;
            add(x, y), add(y, x);
        }

        dfs1(1), dfs2(1, 1);

        for (int i = 1; i <= n; i++)
            h[i] = -1;

        for (int i = 1; i <= idx; i++)
            v[i] = ne[i] = 0;

        idx = 0;

        for (int i = 1; i <= n; i++)
            ans += solve(i);

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：HHZZLL (赞：4)

树上静态路径问题，考虑用点分治做。

设 $same_u$ 表示 $\text{root}$ 到 $u$ 是否有与 $u$ 同色的点。

设 $sum_k$ 表示 $\text{root}$ 的子树（不含根）的 $k$ 颜色总和，所以 $sum_c=\sum_{v\in son_u} sum_{c_v}$。

怎么统计经过 $\text{root}$ 的答案？

有两种情况考虑。

第一种，直接算 $(\text{root},v)$ 的贡献（$v$ 为其子树内一点）。

在其子树内，当找到第一个 $c_v$ 与根同色时加贡献。

第二种，$(u, \text{root})\rightarrow(\text{root},v)$。

当 $u,v$ 颜色相等且各到根的路径上颜色不等，加贡献。

对于 $u$，显然是加上所有 $u$ 子树外的满足此性质的 $v$ 的数量，为其余子树对应的 $sum_c$ 和。

每次 $u\rightarrow v,v\rightarrow u$，一个点被算了两次，所以答案需除以 $2$。

时间复杂度 $O(n\log n)$。

### CODE:
```cpp
// Reformed, started formatting code style.
#include <bits/stdc++.h>
#define int long long
namespace My {
    #define mod 998244353
    #define X first
    #define Y second
    #define vec vector
    #define p_b push_back
    #define pii pair <int, int>
    #define mem(a, x) memset(a, x, sizeof a)
    #define rep(i, a, b) for(int i = a; i <= b; i++)
    #define lop(i, b, a) for(int i = b; i >= a; i--)
    #define eg(i, u) for(auto i : e[u])
} using namespace My;
int n, ans, c[N];
namespace Tree {
    std::vec <int> e[N];
    void add(int u, int v) {
        e[u].p_b(v), e[v].p_b(u);
    }
    namespace PointDiv {
        int root, mx[N], sz[N], sum[N], col[N];
        bool vis[N], same[N];
        void get_root(int u, int fa, int SZ) {
            mx[u] = 0, sz[u] = 1;
            eg(v, u) {
                if(v == fa || vis[v]) continue;
                get_root(v, u, SZ);
                sz[u] += sz[v];
                mx[u] = std::max(mx[u], sz[v]);
            }
            mx[u] = std::max(mx[u], SZ - sz[u]);
            if(mx[u] < mx[root]) root = u;
        }
        void get_dis(int rt, int u, int fa) {
            if(!col[c[u]]) same[u] = 0, sum[c[u]]++;
            else {
            	same[u] = 1;
            	if(c[u] == c[rt] && col[c[u]] == 1) ans += 2; // 根的答案
            }
            col[c[u]]++;
            eg(v, u)
                if(v != fa && !vis[v]) get_dis(rt, v, u);
            col[c[u]]--;
        }
        void get_sum(int u, int fa, int sign) {
            if(!same[u]) sum[c[u]] += sign;
            eg(v, u)
                if(v != fa && !vis[v]) get_sum(v, u, sign);
        }
        void calc(int u, int fa) {
            if(!same[u]) ans += sum[c[u]];
            eg(v, u)
                if(v != fa && !vis[v]) calc(v, u);
        }
        void clear(int u, int fa) {
        	sum[c[u]] = 0;
        	eg(v, u)
        		if(v != fa && !vis[v]) clear(v, u);
        }
        void get_ans(int u) {
        	col[c[u]] = 1;
            eg(v, u) {
                if(vis[v]) continue;
                get_dis(u, v, u);
            }
            col[c[u]] = 0;
			same[u] = 1;
            eg(v, u) {
                if(vis[v]) continue;
                get_sum(v, u, -1); // 算 v 子树内的点，就不考虑 v 子树内的贡献，所以减掉
                calc(v, u);
                get_sum(v, u, 1);
            }
            clear(u, 0);
        }
        void solve(int u) {
            vis[u] = true;
            get_ans(u);
            eg(v, u) {
                if(vis[v]) continue;
                root = 0;
                get_root(v, u, sz[v]);
                solve(root);
            }
        }
    } using namespace PointDiv;
} using namespace Tree;
signed main() {
	std::cerr << (&ed - &at) / 1024.0 / 1024.0 << "\n";
    for(int T = rd(); T--; ans = 0) {
    	rep(i, 1, n) {
    		vis[i] = sum[c[i]] = 0;
    		e[i].clear();
    	}
        rd(n);
        rep(i, 1, n) rd(c[i]);
        rep(i, 1, n - 1) {
        	int u = rd(), v = rd();
        	add(u, v);
        }
        mx[root = 0] = n;
        get_root(1, 0, n);
        solve(root);
        wr(ans / 2, '\n');
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：4)

最后 $15$ 分钟 dsu 速切才没有掉分。 

考虑设计状态 $dp_{u,i}$ 表示 $u$ 的子树内一个颜色为 $i$ 的点到 $u$ 的链且路径上没有其他颜色为 $i$ 的链数量。

那么考虑点 $u$ 加入一个儿子 $v$ 时，假若把 $v$ 中的链和 $u$ 拼起来，答案变化量是 $dp_{v,col_u}$，加入是把其与 $u$ 中另一条链拼起来，答案变化量就是 $dp_{u,x} \times dp_{v,x}$，然后需要让 $dp_{u,x}$ 增加 $dp_{v,x}$ 也就是把链算入 $u$ 的子树贡献中，当然整个过程中因为链一定经过了点 $u$ 所以 $dp_{u,col_u}$ 始终需要为 $0$。算完所有贡献之后再算从点 $u$ 自己开始的链，也就是让 $dp_{u,col_u}$ 为 $1$。

注意到复杂度瓶颈在将 $dp_{v,x}$ 合并到 $dp_{u,x}$ 上，由于两个状态只要一个为空就不产生变化，因此一个点 $v$ 的状态数至多为 $v$ 的子树大小，考虑树上启发式合并，每次将小的状态暴力插入大的状态中并更新贡献，由于每个点最多被暴力插入 $\log n$ 次，再加上这里用 map 维护一个点的所有状态，因此是 $O(n \log^2 n)$ 的。

[代码](https://codeforces.com/contest/1923/submission/247975579)

---

## 作者：OtterZ (赞：3)

~~教你玩爆CF2000的题~~  
# 1.方法本质
这道题的解法不难，我们将所求路径分为两种情况：

1. 两点为祖先关系，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/55btf66p.png)
2. 两点并非祖先关系，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/269cv25d.png)
为了去重，我们按如下计数顺序处理：

1. 有祖先关系时，层数较小的节点处理此路线。
2. 无祖先关系的，后遍历的节点处理此路线。

# 2.整体处理
我们用 $a_i$ 处理 $i$ 号颜色的情况 $1$ 路径计数，$b_i$ 处理 $i$ 号颜色情况 $2$ 的方案数，接下来深搜遍历每个节点 $v$ 并按顺序作如下操作：

1. 预存 $va = a_{c_v},vb = b_{c_v}$；
2. 得到 $vb$ 条对应情况 $2$ 的路径；
3. 遍历子节点，因为父节点拦截了子树外的同色节点，所以遍历前 $b_{c_v} = 0$；
4. 我们得到了从子节点来的 $a_{c_v} - va$ 条对应情况 $1$ 的新路径。
5. 因为该节点会拦截子树内同色节点，并贡献该节点，最后改 $a_{c_v} = va + 1,b_{c_v} = vb + 1$。

# 3 选择原因

1. 速度：时间复杂度 $\operatorname{O}(n)$，并且常数小，本人代码可以在使用 `cin` 与 `cout` 且不关同步时仍然卡进 $1 \text{ s}$。
3. 空间：复杂度 $\operatorname{O}(n)$，且用的数组数量少，具体的，本人代码空间 $17700 \text{ KB}$。
2. 难度：思维和代码难度简单，支持普及组实力选手学习和使用。

# 4.代码

用 `scanf` 和 `printf` (时间 $240\text{ ms}$ 左右，空间 $17700\text{ KB}$ 左右)：

```cpp
#include<cstdio>
#include<vector>
using namespace std;
int t,n,c[200009],u,v;
int cntc[200009],up[200009];
vector<int>e[200005];
long long ans;
void srh(int v,int fa){
	int u = cntc[c[v]],s = up[c[v]];
	ans += s;
	for(int i = 0; i < e[v].size(); i ++){
		if(e[v][i] == fa)
			continue;
		up[c[v]] = 0;
		srh(e[v][i],v);
	}
	ans += cntc[c[v]] - u;
	cntc[c[v]] = u + 1;
	up[c[v]] = s + 1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i = 1; i <= n; i ++){
			scanf("%d",&c[i]);
			cntc[c[i]] = up[c[i]] = 0;
			e[i].clear();
		}
		ans = 0;
		for(int i = 1; i < n; i ++){
			scanf("%d %d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		srh(1,0);
		printf("%lld\n",ans);
	}
	return 0;
}
```

用 `cin`，`cout` 代码（不关同步，空间不变，时间 $820\text{ ms}$ 左右）：

```cpp
#include<cstdio>
#include<vector>
#include<iostream>
using namespace std;
int t,n,c[200009],u,v;
int cntc[200009],up[200009];
vector<int>e[200005];
long long ans;
void srh(int v,int fa){
	int u = cntc[c[v]],s = up[c[v]];
	ans += s;
	for(int i = 0; i < e[v].size(); i ++){
		if(e[v][i] == fa)
			continue;
		up[c[v]] = 0;
		srh(e[v][i],v);
	}
	ans += cntc[c[v]] - u;
	cntc[c[v]] = u + 1;
	up[c[v]] = s + 1;
}
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i ++){
			cin >> c[i];
			cntc[c[i]] = up[c[i]] = 0;
			e[i].clear();
		}
		ans = 0;
		for(int i = 1; i < n; i ++){
			cin >> u >> v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		srh(1,0);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：hanjinghao (赞：3)

## 题意

多组询问，每组询问给定一棵 $ n $ 个点的树，第 $ i $ 个点的颜色为 $ c_i $。

问有多少条**长度至少为二的简单路径**满足起点和终点的颜色相同且路径上没有其他点和这两个点的颜色相同。

注意：起点是 $ x $、终点是 $ y $ 的简单路径和起点是 $ y $、终点是 $ x $ 的简单路径算是**同一条路径**。

保证 $ 1 \le c_i \le n \le 2 \times 10^5 $。

## 思路

不需要十级知识点虚树，也不需要其他任何数据结构。只要你把它当做简单题，那它就是简单题。

显然每种颜色是独立的。我们令 $ cnt_a $ 表示当前 $ a $ 这种颜色出现的次数，然后对整棵树进行深搜。有这几个关键点：

一、在搜索到点 $ x $ 时，答案加上 $ cnt_{c_x} $。

二、在进入以 $ i $ 为根的子树时，把 $ cnt_{c_i} $ 设为 $ 1 $。证明：因为路径上不能有其他点的颜色和起点终点相同，所以 $ x $ 的子树外的颜色和 $ x $ 相同的点到 $ x $ 的子树内的颜色和 $ x $ 相同的点**之间的路径一定不合法**。

三、在遍历完 $ x $ 的所有子树后，把 $ cnt_{c_x} $ 的值设为其在遍历子树前的值加 $ 1 $。证明：令根节点为 $ y $，按顺序考虑 $ y $ 的子树，每棵子树只有顶部的点（上面没有颜色与之相同的点）到 $ y $ 的路径是合法的，子树与子树之间也是只有顶部的点合法，加 $ 1 $ 就表示加上 $ x $ 这个顶部的点。

分析可得每种方案恰好被计算一次。

时间复杂度 $ O(n) $。代码非常简短，知识点也不超出普及组范围。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5;
int c[N], cnt[N];
long long ans;
vector < int > G[N];

void dfs(int x, int fa)
{
	int num = cnt[c[x]];
	ans += num;
	for (auto &i : G[x])
		if (i != fa)
		{
			cnt[c[x]] = 1;
			dfs(i, x);
		}
	cnt[c[x]] = num + 1;
}

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n;
		read(n);
		for (int i = 1; i <= n; ++i)
		{
			cnt[i] = 0;
			G[i].clear();
		}
		for (int i = 1; i <= n; ++i)
			read(c[i]);
		for (int i = 1; i < n; ++i)
		{
			int x, y;
			read(x);
			read(y);
			G[x].emplace_back(y);
			G[y].emplace_back(x);
		}
		ans = 0;
		dfs(1, 0);
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：ATZdhjeb (赞：3)

### 题目大意

给定一棵 $n$ 个点的树，点 $i$ 有颜色 $c_i$，定义树上一条简单路径是优美的当且仅当：

1. 路径中至少有两个点。

2. 路径的两个端点的颜色相同。

3. 路径中任一非端点的点颜色均和端点不同。

求给定树上的优美路径条数。

数据范围：

$1\le T\le 10^4$。

$2\le \sum n\le2\times10^5$。

$1\le c_i\le n$。

### 简要分析

~~怎么 CF 也放板题/yiw？~~

~~当然可能有更好的做法就当我没说。~~

发现如果只有两种颜色的话可以直接淀粉质。

但是现在有很多颜色，就很烦。

我们直接枚举每一种颜色 $i$，把所有颜色为 $i$ 的点拎出来建一棵虚树，然后虚树上要么是颜色为 $i$ 的点，要么是颜色不为 $i$ 的点，因为我们此刻只对颜色 $i$ 统计答案，所以直接看作是两种颜色跑点分治就好了。

时间复杂度 $O(n\log n)$，常数巨大，但是反正能过。

### 代码实现

~~多测不清空，【】【】两行泪。~~

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pii pair<int,int>
#define cpx complex<double>
#define INF 0x3f3f3f3f
#define mod 998244353
#define rep(i,a,b) for (int (i) = (a); (i) <= (b); ++(i))
#define per(i,a,b) for (int (i) = (a); (i) >= (b); --(i))

using namespace std;

inline int input() {
	int x = 0,f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

inline char get() {
	char c = getchar();
	while (isspace(c)) c = getchar();
	return c;
}

const double PI = acos(-1);

int T,n,c[200010],dfn[200010],dep[200010],anc[200010][20],cnt,siz[200010],cur,stk[200010],top,isk[200010],del[200010],sz;
vector<int> e[200010],tr[200010],vec,col[200010];
ll Ans;

void DFS1(int u) {
	dfn[u] = ++cnt;
	rep (i,1,19) anc[u][i] = anc[anc[u][i - 1]][i - 1];
	dep[u] = dep[anc[u][0]] + 1;
	for (int i : e[u]) if (i != anc[u][0]) {
		anc[i][0] = u;
		DFS1(i);
	}
}

int get_LCA(int u,int v) {
	if (dep[u] < dep[v]) swap(u,v);
	if (dep[u] != dep[v]) per (i,19,0) if (anc[u][i] && dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	per (i,19,0) if (anc[u][i] != anc[v][i]) {
		u = anc[u][i];
		v = anc[v][i];
	}
	return anc[u][0];
}

bool cmp(int a,int b) {
	return dfn[a] < dfn[b];
}

void create(int t) {
	stk[top = 1] = 1;
	tr[1] = vector<int>();
	sort(vec.begin(),vec.end(),cmp);
	for (int i : vec) {
		isk[i] = t;
		if (i == 1) continue;
		int lca = get_LCA(stk[top],i);
		if (lca != stk[top]) {
			while (dfn[lca] < dfn[stk[top - 1]]) {
				tr[stk[top]].push_back(stk[top - 1]);
				tr[stk[top - 1]].push_back(stk[top]);
				--top;
			}
			if (lca != stk[top - 1]) {
				tr[lca] = vector<int>();
				tr[stk[top]].push_back(lca);
				tr[lca].push_back(stk[top]);
				stk[top] = lca;
			} else {
				tr[stk[top]].push_back(stk[top - 1]);
				tr[stk[top - 1]].push_back(stk[top]);
				--top;
			}
		}
		tr[i] = vector<int>();
		stk[++top] = i;
	}
	rep (i,1,top - 1) {
		tr[stk[i]].push_back(stk[i + 1]);
		tr[stk[i + 1]].push_back(stk[i]);
	}
}

void get_rt(int u,int p,int& minn,int t) {
	siz[u] = 1;
	int maxn = -INF;
	for (int i : tr[u]) if (i != p && del[i] != t) {
		get_rt(i,u,minn,t);
		siz[u] += siz[i];
		maxn = max(maxn,siz[i]);
	}
	maxn = max(maxn,sz - siz[u]);
	if (maxn < minn) {
		minn = maxn;
		cur = u;
	}
}

void get_dis(int u,int p,int t,int& tot) {
	if (isk[u] == t) return void(++tot);
	for (int i : tr[u]) if (i != p && del[i] != t) get_dis(i,u,t,tot);
} 

void calc(int rt,int t) {
	int sum = 0;
	for (int i : tr[rt]) if (del[i] != t) {
		int tot = 0;
		get_dis(i,rt,t,tot);
		if (isk[rt] != t) {
			Ans += 1LL * tot * sum;
			sum += tot;
		} else Ans += tot;
	}
}

void devision(int rt,int t) {
	calc(rt,t);
	del[rt] = t;
	for (int i : tr[rt]) if (del[i] != t) {
		int minn = INF;
		get_rt(i,rt,minn,t);
		minn = INF;
		sz = siz[i];
		get_rt(i,rt,minn,t);
		devision(cur,t);
	}
}

void solve() {
	cnt = Ans = 0;
	n = input();
	int maxc = -INF;
	rep (i,1,n) col[i] = vector<int>();
	rep (i,1,n) {
		maxc = max(c[i] = input(),maxc);
		col[c[i]].push_back(i);
		e[i] = vector<int>();
		isk[i] = del[i] = 0;
	}
	rep (i,1,n - 1) {
		int u = input(),v = input();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	DFS1(1);
	rep (i,1,maxc) {
		vec = col[i];
		create(i);
		int minn = INF;
		get_rt(1,0,minn,i);
		sz = siz[1];
		get_rt(1,0,minn,i);
		devision(cur,i);
	}
	printf("%lld\n",Ans);
}

int main() {
	T = input();
	while (T--) solve();
	return 0;
}
```

#### Update

欸只有两种颜色是不是不用跑点分啊？不管了不管了，学 useless algorithms 导致的。。。

---

## 作者：fedoralxy (赞：2)

## 思路1

这道题可以直接深搜。

$dp_{i}$ 表示当前点的颜色是 $i$ 在子树内有几个点能与其相连。

我们一直往下搜索，很显然到叶子节点的时候就是 $0$。

每一次进入，记录原先 $dp_i$ 的值，然后遍历子节点，将 $dp_i$ 赋值为 $1$ 并继续向下搜索，到最后求和即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
namespace solve1 {
	vector <ll> v[N];
	ll col[N], n, ans, dp[N];
	inline void dfs (ll u, ll fa) {
		ll org = dp[col[u]];
		for (ll y : v[u]) {
			if (y != fa) {
				dp[col[u]] = 1;
				dfs (y, u);
			}
		}
		ans += org;
		dp[col[u]] = org + 1;
	}
	inline void sol () {
		ans = 0;
		for (int i = 1; i <= n; ++ i) {
			dp[i] = 0;
			v[i].clear ();
		} 				
		cin >> n;
		for (int i = 1; i <= n; ++ i) {
			 cin >> col[i];
		}
		for (int i = 1; i < n; ++ i) {
			ll x, y;
			cin >> x >> y;
			v[x].push_back (y);
			v[y].push_back (x);
		}
		dfs (1, 0);
		cout << ans << '\n';
	}
}
int main () {
	ll t;
	cin >> t;
	while (t --) {
		sovle1::sol ();
	}
	return 0;
}
```

## 思路2

很显然如果只有两种颜色就可以跑点分治。

对于点 $i$ 构建虚树，就可以当成两种颜色，跑点分治了。

---

## 作者：BrotherCall (赞：1)

笔者在看了 @ganpig 的[题解](https://www.luogu.com.cn/article/vu78qbti)后感到非常巧妙，但是由于自身水平限制，又难以理解这种巧妙的思路是如何产生的，于是决定深入探究一下。

令 $i$ 号点的颜色为 $a_i$。不难发现题目即要求有多少颜色相同的点对满足点对的之间的路径不存在该颜色。

考虑 $\texttt{dfs}$ 的过程，假设我们现在在 $x$ 点。

令 $c_i$ 代表走到点 $x$ 之前，有多少个颜色为 $i$ 且有贡献的的点。

那么对于每一个 $x$，$c_{a_x}$ 的总和即为答案。

考虑如何计算这个贡献。

首先找到 $x$ 的祖先中颜色为 $a_x$ 且深度最深的点，记这个点为 $y$。

$y$ 点有 $1$ 的贡献，且由于这个点的存在，在这个点之前走到的同色点全部没有贡献。

所以 $y$ 点和 $y$ 点之前走到的点的贡献就被统计完了，现在需要计算 $y$ 点之后走到的点的贡献。

不难发现在 $x$ 点回溯的时候，以 $x$ 为根的子树的点（除 $x$）都被 $x$ 遮住了，也就是只有 $x$ 产生 $1$ 的贡献，其下面的点都不产生贡献。

于是每个点的 $c_{a_x}$ 就被动态维护出来了。

精巧的代码：
```cpp
void dfs(int fa,int u) {
      int res = c[a[u]];
      for(int v:G[u]) {
          if(v == fa) continue;
          c[a[u]] = 1;
          dfs(u , v);
      }
      ans += res;
      c[a[u]] = res + 1;
  }
```

[提交记录](https://codeforces.com/gym/555698/submission/284730965)

---

## 作者：w9095 (赞：1)

[CF1923E Count Paths](https://www.luogu.com.cn/problem/CF1923E)

点分治模板题。

假设当前处理的树根为 $x$，我们考虑如何统计经过点 $x$ 的合法路径。

$1$：存在一个与 $x$ 颜色相同的点，且这个点到 $x$ 的路径上没有与之颜色相同的点，那么这个点和 $x$ 就构成了一条合法路径。

$2$：存在一个与 $x$ 颜色不相同的点，且这个点到 $x$ 的路径上没有与之颜色相同的点。那么这个点与 $x$ 的其他子树中与之颜色相同的点构成一条合法路径。

情况 $2$ 可以通过记录一个颜色数组，将访问过的到 $x$ 的路径上没有与之颜色相同的点的节点的颜色进行统计。两棵不同的子树之间的路径匹配时，直接使用颜色数组即可。

接下来就是点分治模板了。每次取重心，统计贡献，删除，递归点分治子树。即可统计所有合法路径。

实现得比较差，常数较大。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt;
}e[600000];
long long t,n,a[300000],s[300000],h[300000],del[300000],he=0,cnt=0,ans=1e10,tol=0;
long long pre[300000],x[300000],sum[300000],g[300000];
void init()
{
	for(int i=1;i<=n;i++)del[i]=0,h[i]=0;
	tol=0,cnt=0;
}

void add_edge(long long u,long long v)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
}
 
long long dfs1(long long now,long long fa,long long cnt)
{
    long long maxn=0;
    s[now]=1;
    if(del[now])return 0;
    for(long long i=h[now];i;i=e[i].nxt)
        if(e[i].v!=fa)
            {
            long long z=dfs1(e[i].v,now,cnt);
            s[now]+=z,maxn=max(maxn,z);
            }
    if(max(maxn,cnt-s[now])<ans)ans=min(ans,max(maxn,cnt-s[now])),he=now;
    return s[now];
}

void dfs2(long long now,long long fa)
{
	if(del[now])return;
	s[now]=1,pre[now]=x[a[now]],x[a[now]]=now;
	if(pre[now]==0)
	   {
	   	if(a[now]==a[he])tol++;
	   	else 
	   	   {
	   	   tol+=sum[a[now]];
		   g[a[now]]++;
		   }
	   }
	for(long long i=h[now];i;i=e[i].nxt)
	    if(e[i].v!=fa)
	       {
		   dfs2(e[i].v,now);
		   if(del[e[i].v]==0)s[now]+=s[e[i].v];
	       }
	x[a[now]]=pre[now];
}

void update(long long now,long long fa)
{
	if(del[now])return;
	sum[a[now]]+=g[a[now]],g[a[now]]=0;
	for(long long i=h[now];i;i=e[i].nxt)
	    if(e[i].v!=fa)update(e[i].v,now);
}

void clear(long long now,long long fa)
{
	if(del[now])return;
	pre[now]=0,x[a[now]]=0,sum[a[now]]=0;
	for(long long i=h[now];i;i=e[i].nxt)
	    if(e[i].v!=fa)clear(e[i].v,now);
}
 
void dfz(long long now,long long siz)
{
	if(del[now])return;
	ans=1e10;
	dfs1(now,0,siz);
	for(long long i=h[he];i;i=e[i].nxt)
	    {
	    dfs2(e[i].v,he);
	    update(e[i].v,he);
	    }
	for(long long i=h[he];i;i=e[i].nxt)clear(e[i].v,he);
	del[he]=1;
	for(long long i=h[he];i;i=e[i].nxt)dfz(e[i].v,s[e[i].v]);    
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
		{
	    scanf("%lld",&n);
	    init();
	    for(long long i=1;i<=n;i++)scanf("%lld",&a[i]);
	    for(long long i=1;i<=n-1;i++)
	        {
	        	long long u=0,v=0;
	        	scanf("%lld%lld",&u,&v);
	        	add_edge(u,v),add_edge(v,u);
			}
		dfz(1,n);
	    printf("%lld\n",tol);
	    }
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

虚树 + 简单换根 dp。

## 简要题意

给定一个 $n$ 个点的树，点 $i$ 有点权 $c_i$，计算满足下列所有条件的路径 $(u,v)$ 数量：

- $u\neq v$。
- $c_u=c_v$。
- $(u,v)$ 路径上除了端点的其他点（可能不存在）的点权均与 $a_u,a_v$ 不同。

$T$ 组数据。$1\leq \sum n\leq 2\times 10^5,1\leq c_i\leq n$。

## 思路

首先考虑如果如果 $c_i\leq 10$ 怎么做，那么不妨枚举每一个点权 $x$，计算路径端点点权为 $x$，路径其余点点权不为 $x$ 的数量，则为了方便讨论，可以令 $a_i=[c_i=x]$，这样点权只有 $0/1$ 了。

这个形式就可以换根 dp。设 $f(i)$ 表示以 $i$ 的子树中的一个点权为 $1$ 的点为端点，$i$ 为路径上的一点（不为**另一个**端点）的方案数。

则有：

$$
f(u)=\begin{cases}
1& a_u=1\\
\sum_{v\in\mathrm{son}(u)} f(v)& a_u=0
\end{cases}
$$

接着就是换根，假如当前根为 $u$，若 $a_u=1$，则 $u$ 可以为一个端点，此时答案贡献是 $\sum_{v\in\mathrm{son}(u)} f(v)$。换根到 $v$ 的时候只需要令 $f(u)\gets f(u)-f(v)+f(\mathrm{fa}(u))$（若 $a_u=0$）表示去除 $v$ 的贡献，添加父亲的贡献。

注意这样对于路径 $(u,v),(v,u)$ 各会计算一次，所以答案要减半。

回到本题，由于颜色很多，不可能每次对全树跑一遍换根 dp，所以可以改为对每个颜色的点建虚树，这些点 $a_i=1$，则其余的辅助点 $a_i=0$，然后正常跑换根 dp 即可，由于对 $k$ 个点建虚树的点数仍然是 $O(k)$，所以复杂度是正确的。

单组数据时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N], dfn[N], top[N], dep[N], siz[N], father[N], son[N];
vector<int> b[N];
vector<int> g[N], t[N];
using i64 = long long;

void dfs1(int u, int fa){
    dfn[u] = ++dfn[0], dep[u] = dep[fa] + 1, father[u] = fa, siz[u] = 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa){
    if(son[u]) top[son[u]] = top[u], dfs2(son[u], u);
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, dfs2(v,u);
    }
}

int lca(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = father[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

i64 f[N];
bool is[N];

void dp1(int u){
    for(int v : t[u]) dp1(v);
    if(is[u]) f[u] = 1;
    else{
        for(int v : t[u]) f[u] += f[v];
    }
}

i64 ans;

void dp2(int u, int fa){
    if(is[u]){
        for(int v : t[u]) ans += f[v];
        ans += f[fa];
    }
    i64 tmp = f[u];
    for(int v : t[u]){
        if(!is[u]) f[u] = tmp - f[v] + f[fa];
        dp2(v, u);
        f[u] = tmp;
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i], b[a[i]].push_back(i);
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    top[1] = 1, dfs1(1, 0), dfs2(1, 0);
    for(int i=1;i<=n;i++){
        vector<int> vct; vct.swap(b[i]);
        if(vct.size() <= 1) continue;
        int siz = vct.size();
        for(int i : vct) is[i] = true;
        sort(vct.begin(), vct.end(), [](int x, int y){
            return dfn[x] < dfn[y];
        });
        for(int j=1;j<siz;j++) vct.push_back(lca(vct[j - 1], vct[j]));
        sort(vct.begin(), vct.end(), [](int x, int y){
            return dfn[x] < dfn[y];
        });
        vct.erase(unique(vct.begin(), vct.end()), vct.end());
        for(size_t j=1;j<vct.size();j++) t[lca(vct[j - 1], vct[j])].push_back(vct[j]);
        dp1(vct[0]), dp2(vct[0], 0);
        for(int j : vct) is[j] = false, f[j] = 0;
        for(size_t j=1;j<vct.size();j++){
            int x = lca(vct[j - 1], vct[j]);
            f[x] = 0, t[x].clear();
        }
    }
    cout << (ans >> 1) << '\n';
}

void clear(){
    for(int i=1;i<=n;i++) g[i].clear(), siz[i] = son[i] = 0;
    ans = 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Priestess_SLG (赞：0)

首先树上路径计数一类的问题肯定可以上点分，但是有做法可以做到严格 $O(n)$。

考虑对于树上的一个点 $u$，在其子树点集 $S_u$ 中的点 $v$（$v\in S_u$）满足 $c_u=c_v$，则显然 $v$ 只能和 $S_u$ 中除了 $u$ 以外的结点做贡献。于是考虑从根节点 $1$ 开始对树做 dfs。对于当前结点 $u$，枚举儿子结点 $v$ 并把当前 dfs 的结点移动到 $v$。显然此时 $v$ 不会和 $u$ 以上所有颜色同样为 $c_u$ 的结点产生贡献，因此此时记录 $c_u$ 出现的颜色次数为 $1$，dfs 完之后再回溯即可。时间复杂度确实为 $O(n)$。

```cpp
const int N = 1000100;
const int mod = 998244353;
vector<int> adj[N];
int a[N], buc[N], n, s;
void dfs(int u, int fa) {
    int now = buc[a[u]];
    s += now;
    for (auto &v : adj[u])
        if (v != fa) {
            buc[a[u]] = 1;
            dfs(v, u);
        }
    buc[a[u]] = now + 1;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) adj[i].clear(), buc[i] = 0;
        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].eb(y), adj[y].eb(x);
        }
        s = 0;
        dfs(1, 0);
        cout << s << '\n';
    }
}
```

---

## 作者：xukehg (赞：0)

不会有人写虚树吧。

考虑颜色虽然很多，但总共只有 $n$ 个点，且只在意能否达到的路径中无其他点即不在意边权，考虑虚树。板子过后开始设计如何计数。

令 $g_i$ 表示 $i$ 的子树内有多少个点可以不经过同色点到达 $i$。于是有两种情况：如果 $i$ 是被标记的点，则统计答案后 $g_i$ 修改为 $1$；否则有 $g_i$ 为 $\sum_{v \in son_i}g_v$。
计算贡献分两种情况：如果这个节点被标记，贡献为 $g_i$；否则，贡献为 $(\sum_{v \in son_i}g_v) ^ 2 - \sum_{v \in son_i} g_v ^ 2$ 再除以二，即任意两个子树的 $g_v$ 相乘。

[记录。](https://codeforces.com/contest/1923/submission/289117204)

---

## 作者：Flanksy (赞：0)

### 线段树合并

没人写线段树合并的题解，我来写一篇。

------------------

首先指定根节点为 $1$，合法路径数量与树是否有根无关。

使用线段树合并维护节点 $i$ 子树中所有**有效颜色**的出现次数（如果路径 $(i,j)$ 上除 $j$ 外没有其他颜色为 $c_j$ 的节点，且节点 $j$ 在节点 $i$ 子树中，就认为 $c_j$ 是节点 $i$ 子树中的有效颜色），在线段树合并过程中可以计算所有路径端点以 $i$ 为最近公共祖先的合法路径数量。

对于端点颜色为 $c_i$ 的路径，由于 $i$ 的颜色已经是 $c_i$，可以通过在**合并 $i$ 的所有儿子节点，不包含 $i$ 自身信息的线段树**上查询有效颜色 $c_i$ 的出现次数 $cnt$ 计算贡献，其对答案的贡献就是 $cnt$ 本身。

对于端点颜色不为 $c_i$ 的路径，节点 $i$ 的每个孩子节点的子树中的有效颜色节点可以两两搭配，对答案的贡献是一个经典的乘积之和形式，这可以在合并线段树的叶子节点时计算。

在合并 $i$ 的所有儿子节点得到节点 $i$ 的线段树后，将节点 $i$ 的颜色信息加入线段树。也就是将有效颜色 $c_i$ 的出现次数置为 $1$，因为从 $i$ 子树外任意颜色为 $c_i$ 的节点到达 $i$ 子树内的节点都需要经过 $i$，这样一来原先所有颜色为 $c_i$ 的有效节点都不再是合法的路径端点。

**笔者的实现中合并了计算端点颜色为 $c_i$ 的路径与将节点 $i$ 的信息加入线段树的操作，在计入颜色 $c_i$ 的贡献后直接将 $c_i$ 的出现次数置为 $1$ 以减少代码量。**

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Segment{int w,ls,rs;}s[200'005*20];
int n,seg,a[200'005],ro[200'005];
vector<int> v[200'005];
long long ans;
void update(int &u,int l,int r,int p){
    if(u==0) u=++seg;
    if(l==r) return ans+=s[u].w,s[u].w=1,void();
    int mid=(l+r)>>1;
    if(p<=mid) update(s[u].ls,l,mid,p);
    else update(s[u].rs,mid+1,r,p);
}
int merge(int x,int y,int l,int r,int co){
    if(x==0||y==0) return x+y;
    if(l==r){
        if(l!=co) ans+=1ll*s[x].w*s[y].w;
        s[x].w+=s[y].w;
    }
    else{
        int mid=(l+r)>>1;
        s[x].ls=merge(s[x].ls,s[y].ls,l,mid,co);
        s[x].rs=merge(s[x].rs,s[y].rs,mid+1,r,co);
    }
    return x;
}
void dfs(int x,int las){
    for(int i:v[x]) if(i!=las){
        dfs(i,x);
        ro[x]=merge(ro[x],ro[i],1,n,a[x]);
    }
    update(ro[x],1,n,a[x]);
}
void solution(){
    for(int i=1;i<=seg;i++) s[i].w=0,s[i].ls=0,s[i].rs=0;
    cin>>n,seg=0,ans=0ll;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) ro[i]=0,v[i].clear();
    for(int i=1;i<=n-1;i++){
        static int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1,0);
    cout<<ans<<'\n';
}
int T;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--) solution();
    return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

# 大致解析：

由题意可知，这是一道很明显的图论题，不过，如果你用图论一股脑地想，还是稍有欠缺（指根本过不了第二个数据）。

那么，我们可以发现，题目是一道**很经典的求方案数**的问题，直接暴力显然不现实，那么，我们从优化着手，毕竟图论题不用搜索就得不到每个点的状态。

我们可以先遍历每一个点，不过，在深度优先搜索的同时，我们可以进行搜索中的在线配对，就像输出一样到那个点就得到那个点的答案。我们设 $sum_i$ 代表到了当前点，颜色为 $i$ 有多少可以配对，就是可以组成路径的，维护规则如下文。

当我们遍历到一个点时每往子节点遍历，由于子树内，颜色与当前节点相同的节点，能接触到的深度优先搜索序最小的节点就是当前节点，**因为根据树的性质，子树的节点的边无法连接到该子树父节点以外的节点**，所以要令当前颜色的 $sum$ 值为 $1$，所有子节点遍历完成后，设当前节点颜色为 $c$，由于接下来遍历的节点可以接触，并可以记录在答案中，所以在接下来上爬的过程中就将 $c$ 颜色的节点的 $sum$ 值加 $1$。

最后告诫两点。

第一点，**一定要记得每次清空数组**，多测不清空，爆零两行泪。

第二点，在清空时用最基本的循环，不要用 STL，因为那样会直接将空间内的数据全部清空，很耗时间，而且最多有 $10000$ 组数据，还是很恐怖的。

---



# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node
{
    int to, next;
} edge[2000009];
int head[2000009];
int cnt;
void add(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
int sum[2000005];
int color[2000005];
int ans = 0;
void dfs(int x, int fa)
{
    int c = color[x];
    int ls = sum[c];
    ans += ls;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (y == fa)
        {
            continue;
        }
        sum[c] = 1;
        dfs(y, x);
    }
    ls++;
    sum[c] = ls;
}
int n;
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cnt = 0;
        ans = 0;
        cin >> n;
        for (int i = 0; i <= n + 10; i++)
        {
            head[i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            sum[i] = 0;
            cin >> color[i];
        }
        for (int i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            add(x, y);
            add(y, x);
        }
        dfs(1, 0);
        cout << ans << '\n';
        // ans = 0;
    }
    return 0;
}


```

---

## 作者：_zuoqingyuan (赞：0)

如果当成淀粉质做的话，还是很板的。

# 思路分析

对于一条合法路径 $x\to y$，令 $z$ 为 $x,y$ 的最近公共祖先，根据题目要求，显然满足 $c_x=c_y$ 且 $z\to x,z\to y$ 都不包含颜色 $c_x$。

如果我们确定这个点 $z$，显然可以快速统计出从 $z\to x$ 的路劲上不包括 $c_x$ 的 $x$ 的数量，如果 $x$ 为一条合法路径的一端，则路径另一端 $y$ 也必然满足 $z\to y$ 的路径上不包含 $c_x$，且 $x,y$ 位于 $z$ 的两个不同儿子的子树内。

令 $S_{col}$ 表示 $1\sim i-1$ 个儿子中，满足上述条件的且 $c_x=col$ 的 $x$ 的数量，假设当前找到了一个满足条件的节点 $y$，则以 $y$ 为端点，经过 $z$ 的合法路径就有 $S_{c_y}$ 条，我们可以一边统计一边计算。

我们发现路径只分为经过 $z$ 的和没经过 $z$ 的，套点分治模板即可解决，时间复杂度 $O(n\log n)$。

容易错的点：

- 注意到 $z$ 也可能成为端点，所以我们要始终保证 $S_{c_z}=1$，避免出现少统计或多统计。

- 因为 $n\le 2\times 10^5$，所以统计答案记得开 `long long`。

最后处理好多测清空的问题就可以了。

# $\text{Code}$：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N=2e5+10;
vector<int>g[N];
int T,n,c[N],siz[N],maxn[N],root,vis[N],cnt[N],mk[N],tot,last,tmp[N];
long long ans;
void add(int x,int y){
    g[x].push_back(y);
}
int dfs_root(int x,int fa,int sum){
    siz[x]=1,maxn[x]=0;
    for(auto y:g[x]){
        if(vis[y]||y==fa)continue;
        siz[x]+=(siz[y]=dfs_root(y,x,sum));
        maxn[x]=max(maxn[x],siz[y]);
    }
    maxn[x]=max(maxn[x],sum-siz[x]);
    if(maxn[root]>maxn[x])root=x;
    return siz[x];
}
void dfs_dis(int x,int fa){
    if(!mk[c[x]])cnt[++tot]=c[x];
    mk[c[x]]++;
    for(auto y:g[x]){
        if(vis[y]||y==fa)continue;
        dfs_dis(y,x);
    }
    mk[c[x]]--;
}
void calc(int u){
    tot=last=1;tmp[c[u]]=1;
    for(auto v:g[u]){
        if(vis[v])continue;
        dfs_dis(v,u);
        for(int i=last;i<=tot;i++)ans+=tmp[cnt[i]];
        for(int i=last;i<=tot;i++)tmp[cnt[i]]++;tmp[c[u]]=1;
        last=tot+1;
    }
    for(int i=1;i<=tot;i++)tmp[cnt[i]]=0;
    tmp[c[u]]=0;
}
void solve(int u){
    vis[u]=1;
    calc(u);
    for(auto v:g[u]){
        if(vis[v])continue;
        root=0;dfs_root(v,u,siz[v]);
        solve(root);
    }
    return;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",c+i);
        }
        for(int i=1,u,v;i<n;i++){
            scanf("%d %d",&u,&v);
            add(u,v),add(v,u);
        }
        maxn[0]=N;root=0;
        dfs_root(1,-1,n);
        solve(root);
        printf("%lld\n",ans);
        for(int i=1;i<=n;i++)g[i].clear(),vis[i]=0;
        ans=0;
    }
    return 0;
}
```

如有错误，请指出。

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
求出树上题目所要求的路径的数量即可。
## 大体思路
我们先把树建好，拿 DFS 处理一下。

来介绍一个非常好的手法，我们先初始化所有的颜色出现的个数 $sum$ 为零，在深搜遍历的记录，这样我们就可以边遍历边记录答案了，那么具体怎么实现呢？

深搜开始先用变量 $xx$ 记录在这个点之前出现过和他一样颜色的点个数（按深搜顺序），加到答案里，那么怎么处理两个同样颜色的中间还有和他俩一样颜色的情况呢？

这就展开去重操作，是个妙手，由于深搜顺序是根左右的先序遍历，所以和离着当前处理点最近的同样颜色的点的祖先连边必然会出现中间夹带私货（夹着和端点一样颜色的点）的情况，所以我们可以直接将 $sum_i$ 置为 $1$，这样就只会考虑当前点和当前点最近的祖先，不会出现上述情况。

别忘了回溯。

处理完答案直接输出即可。

重点考虑一下前面的操作会对后面的影响，这样的计数是正确的，因为后面的由于前面的处理不会计算两个同样颜色的中间还有和他俩一样颜色的情况。下面看代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std; 
long long sum[200005];//颜色出现次数 
long long a[200005];
vector<int> tu[200005];
long long ans=0;
void dfs(int x,int f){
	int xx=sum[a[x]];//按深搜顺序，在这个点之前出现过和他一样颜色的点xx个 
	ans+=xx;
	for(auto v:tu[x]){
		if(v==f){
			continue ; 
		}
		sum[a[x]]=1;//在上面提到的颜色数归1操作 
		dfs(v,x);//遍历儿子 
	}
	sum[a[x]]=xx+1;//转换成正常的颜色数
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			sum[i]=0;
			tu[i].clear();//正常清零 
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<n;i++){
			int x,y;
			cin>>x>>y;//正常存图 
			tu[x].push_back(y);
			tu[y].push_back(x);
		}
		ans=0;
		dfs(1,0);//进入DFS 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/18049302)！

简单易懂的线性做法。

考虑对一条路径 $(u,v)$ 在 **dfs** 序更大的点 $v$ 处算贡献。

记 $cnt_i$ 表示到当前点时颜色 $i$ 应该算的贡献大小。考虑做到点 $x$，此时**依次**做如下操作：

- 把除了 $1\to x$ 路径外之前 **dfs** 过的点**累加**到 $cnt$ 中对应颜色。

- 遍历 $1\to x$ 路径，把路径上的每个颜色 $cnt$ 值更改为 $1$。

- 计算 $x$ 点贡献，即 $ans\gets cnt_{c_x}$。

动态地在 **dfs** 时维护此过程即可。具体细节看[代码](https://codeforces.com/contest/1923/submission/249320726)。

复杂度线性。

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1923E)

## $\mathtt{Solution}$

考虑点分治，假设当前的分治中心为 $x$。

对于所有的颜色 $i$，求出有多少个节点的所有祖先（$x$ 除外）的颜色都与它不同，记这个数为 $num_i$。

对于 $c_x$，由于路径的两端只能是 $x$ 与另外一个节点，所以答案加上 $num_{c_i}$。

对于其他的颜色，两两配对即可，答案加上 $\dfrac{1}{2}num_i(num_i-1)$。

最后求每一个子树的中心，分治递归即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int t, n, ans, root, Size, msiz, a[MAXN], siz[MAXN], num[MAXN], vis[MAXN], used[MAXN];
vector<int>g[MAXN];
void get_siz(int x, int fa){
	siz[x] = 1;
	for(int v : g[x]){
		if(v == fa || vis[v])continue;
		get_siz(v, x);
		siz[x] += siz[v];
	}
}
void get_rt(int x, int fa){
	int tmp = Size - siz[x];
	for(int v : g[x]){
		if(v == fa || vis[v])continue;
		get_rt(v, x);
		tmp = max(tmp, siz[v]);
	}
	if(tmp < msiz)root = x, msiz = tmp;
}
void insert(int x, int fa, int z){
	int h = 0, p = 0;
	if(!used[a[x]])h = 1, p = z;
	used[a[x]] += h, num[a[x]] += p;
//	printf("node : %lld %lld %lld %lld %lld %lld\n", x, a[x], h, p, used[a[x]], num[a[x]]);
	for(int v : g[x]){
		if(v == fa || vis[v])continue;
		insert(v, x, z);
	}
	used[a[x]] -= h;
}
void calc(int x, int fa, int col){
	int h = 0;
	if(!used[a[x]]){
		if(a[x] == col)ans ++;
		else ans += num[a[x]];
		h = 1;
	}
	used[a[x]] += h;
	for(int v : g[x]){
		if(v == fa || vis[v])continue;
		calc(v, x, col);
	}
	used[a[x]] -= h;
}
void solve(int x){
	vis[x] = 1;
	for(int v : g[x]){
		if(!vis[v])calc(v, x, a[x]), insert(v, x, 1);
	}
//	printf("root : %lld\n", x);
//	for(int i = 1;i <= n;i ++)printf("%lld %lld\n", i, num[i]);
//	puts("");
	for(int v : g[x]){
		if(!vis[v])insert(v, x, -1);
	}
	get_siz(x, 0);
	for(int v : g[x]){
		if(!vis[v]){
			msiz = 1145141919, Size = siz[v];
			get_rt(v, x);
			solve(root);
		}
	}
}
signed main(){
	t = read();
	while(t --){
		n = read(), ans = root = Size = msiz = 0;
		for(int i = 1;i <= n;i ++)a[i] = read();
		for(int i = 1;i <= n;i ++)g[i].clear(), vis[i] = 0;
		for(int i = 1;i < n;i ++){
			int u = read(), v = read();
			g[u].push_back(v);
			g[v].push_back(u);
		}
		solve(1);
		printf("%lld\n", ans);
	}
	return 0;
}

```

---

## 作者：Diaоsi (赞：0)

[Count Paths](https://www.luogu.com.cn/problem/CF1923E)

首先考虑固定一个颜色 $c$，怎么数出以 $c$ 为端点的符合条件的路径数。

有一个显然的 DP，设 $f_{x}$ 表示以 $x$ 为根的子树中，端点颜色为 $c$ 且该点到 $x$ 的路径上没有其他颜色为 $c$ 的点的路径数。

有以下转移：

$$f_x\leftarrow f_x+f_y\quad,\, \text{col}(x)\neq c$$

$$f_x\leftarrow 1\quad,\, \text{col}(x)= c$$

其中 $y$ 为 $x$ 的儿子，接下来考虑如何记录答案，考虑枚举路径的 $\text{lca}$，同样有两种情况。

当 $\text{lca}$ 颜色不为 $c$ 时，记其儿子为 $y$。考虑在合并子树时计算贡献，当把以 $y$ 为根的子树作为儿子合并到以 $x$ 为根的子树时，产生的新路径数为 $f_x\times f_y$ 条。

当 $\text{lca}$ 颜色为 $c$ 时，$\text{lca}$ 只能作为路径的一端，所以跨过当前 $\text{lca}$ 的路径数就是所有 $f_y$ 的和。

跟上面的 DP 整合一下，有如下式子：

$$\begin{aligned}ans&\leftarrow ans+f_x\times f_y\\f_x&\leftarrow f_x+f_y\end{aligned}\quad\quad\text{col}(x)\neq c$$

$$\begin{aligned}ans&\leftarrow ans + \sum\limits_{y\in\text{son}(x)}f_y\\f_x&\leftarrow 1\end{aligned}\quad\text{col}(x)= c$$

枚举所有颜色，对每个颜色做 DP，这题就做完了。但是这个做法的时间复杂度是 $\mathcal{O}(n^2)$ 的，过不去。

注意到每个颜色的点只占整棵树的一部分，记某个颜色的点数为 $k$，发现 $\mathcal{O}\left(\sum k\right)$ 是 $\mathcal{O}(n)$ 的，所以我们可以对每个颜色单独建立一个大小为 $\mathcal{O}(k)$ 的虚树，在这个虚树上面进行 DP。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在排序。

Code:
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int head[N],ver[M],Next[M],tot;
int T,n,m,rt,ts,num,top,s[M],c[N],d[N],vis[N],sz[N],in[N],id[N],lg[N<<1],st[N<<1][21];
ll ans,f[N];
vector<int> h[N],v[N];
bool cmp(int x,int y){return id[x]<id[y];}
void add(int x,int y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
void dfs(int x,int fa){
    d[x]=d[fa]+1;
    in[x]=++ts;st[ts][0]=x;
    id[x]=++num;
    for(int i=head[x];i;i=Next[i]){
        int y=ver[i];
        if(y==fa)continue;
        dfs(y,x);
    }
    ++ts;
    if(fa)st[ts][0]=fa;
    else st[ts][0]=0;
}
void init(){
    for(int j=1;(1<<j)<=ts;j++)
        for(int i=1;i+(1<<j)-1<=ts;i++){
            int x=st[i][j-1],y=st[i+(1<<(j-1))][j-1];
            st[i][j]=(d[x]<d[y])?x:y;
        }
}
int lca(int x,int y){
    int l=in[x],r=in[y];
    if(l>r)swap(l,r);int ln=lg[r-l+1];
    return d[st[l][ln]]<d[st[r-(1<<ln)+1][ln]]?st[l][ln]:st[r-(1<<ln)+1][ln];
}
void dp(int x,int fa,int col){
	f[x]=0;
	for(int y:h[x]){
		if(y==fa)continue;
		dp(y,x,col);
	}
	for(int y:h[x]){
		if(y==fa)continue;
		if(c[x]^col){
			ans+=f[x]*f[y];
			f[x]+=f[y];
		}
		else ans+=f[y];
	}
	if(c[x]==col)f[x]=1;
}
void solve(int col){
	vis[col]=1;top=0;
	for(int z:v[col])s[++top]=z;
	sort(s+1,s+top+1,cmp);
	int k=top;
	for(int i=1;i<k;i++){
		int l=lca(s[i],s[i+1]);
		if(l!=s[i]&&l!=s[i+1])s[++top]=l;
	}
	sort(s+1,s+top+1);
	top=unique(s+1,s+top+1)-s-1;
	sort(s+1,s+top+1,cmp);
	for(int i=2;i<=top;i++){
		int l=lca(s[i-1],s[i]);
		h[l].push_back(s[i]);
	}
	dp(s[1],0,col);
	for(int i=1;i<=top;i++)h[s[i]].clear();
}
void solve(){
	scanf("%d",&n);
	ans=tot=num=ts=0;
	for(int i=1;i<=n;i++)
		v[i].clear(),head[i]=vis[i]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		v[c[i]].push_back(i);
	}
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	init();
	for(int i=1;i<=n;i++)
		if(!vis[c[i]])solve(c[i]);
	printf("%lld\n",ans);
}
int main(){
	for(int i=2;i<N<<1;i++)lg[i]=lg[i>>1]+1;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

线性做法。

$1$ 为根，考虑将合法路径按端点是否有祖先关系拆成两类考虑。

有祖先关系：对于每个点，我们求出其到 $1$ 的路径上第一个同色点。这个在 dfs 中维护一个桶容易做到。

没有祖先关系：我们考虑在路径两端点的 LCA 到 $1$ 的路径上的首个与端点同色的点处统计答案。

具体地，对于节点 $u$ 维护 $a_{u,c}$ 表示 $u$ 子树从 $u$ 出发不经过颜色 $c$ 能到达的 $c$ 颜色点个数。

每次回溯的时候将对应颜色清零即可。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1923/submission/248026086)

---

## 作者：YBaggio (赞：0)

[https://codeforces.com/contest/1923/problem/E](https://codeforces.com/contest/1923/problem/E)

[更好的阅读体验（maybe](https://ybaggio.fun/index.php/archives/84/)
# 题意
给你一棵树，它由 $n$ 个顶点组成，编号从 $1$ 到 $n$。每个顶点都有某种颜色 $a_i$ 满足 $1 \le a_i \le n$。

如果符合以下条件，那么这棵树的一条简单路径就叫做美丽路径：

- 至少由 $2$ 个顶点组成；
- 路径的第一个顶点和最后一个顶点的颜色相同；
- 路径上没有其他顶点的颜色与第一个顶点相同。

计算这棵树的美丽简单路径的数量。请注意，路径是不定向的（即从 $x$ 到 $y$ 的路径与从 $y$ 到 $x$ 的路径算作一条路径）。
# 题解
树上路径问题，我们考虑点分治。
[关于点分治](https://ybaggio.fun/index.php/archives/82/)
考虑分治到点 $x$，路径分为经过 $x$ 的路径与不经过 $x$ 的路径，后者我们会分治到 $x$ 的子树时处理，我们现在考虑如何求解前者。

计算前者，我们遍历所有子树，分别记录 $mp_{v}$ 表示满足颜色为 $v$，且路径 $(x, fa_y)$ 上任意点颜色不等于 $a_y$ 的路径 $(x,y)$ 的数量。实现的话可以在遍历子树时，记录从 $x$ 到当前节点的每个颜色出现的次数。最后将所有子树的每“半条路径”拼接起来，计算答案。
```cpp
#include <iostream>
#include <vector>
#pragma GCC optimize ("Ofast")
#pragma GCC optimize (3)
#define inf 1000000000
using namespace std;
typedef long long ll;
const int maxn = 200010;
int T;
int n, a[maxn], cnt, h[maxn];
int s[maxn], ms[maxn];
int sum, rt;
bool vis[maxn];
int b[maxn], c[maxn];
ll ans;
vector <int> t, _t;
struct E {
  int to, ne;
} e[maxn << 1];
inline void add (int u, int v) {
  e[++cnt].to = v; e[cnt].ne = h[u]; h[u] = cnt;
}
void find (int x, int fa) { //寻找重心并计算子树大小
  ms[x] = 0;
  s[x] = 1;
  for (int i = h[x]; i; i = e[i].ne) {
    int y = e[i].to;
    if (!vis[y] && y != fa) {
      find (y, x);
      s[x] += s[y];
      ms[x] = max (ms[x], s[y]);
    }
  }
  ms[x] = max (ms[x], sum - s[x]);
  if (ms[x] < ms[rt]) rt = x;
}
void getinfo (int x, int fa) { //遍历子树寻找“半条路径”
  if (!b[a[x]]) t.push_back (a[x]);//一条合法的“半条路径”
  b[a[x]]++; //记录颜色出现次数
  for (int i = h[x]; i; i = e[i].ne) {
    int y = e[i].to;
    if (!vis[y] && y != fa) {
      getinfo (y, x);
    }
  }
  b[a[x]]--; //记录颜色出现次数
}
void dfs (int x, int fa) {
  vis[x] = true;
  for (int i = h[x]; i; i = e[i].ne) {
    int y = e[i].to;
    if (y != fa && !vis[y]) {
      getinfo (y, x);
      for (int d : t) {
        if (d == a[x]) ans++;
        else ans += c[d];
      } //合并“半条路径”
      for (int d : t) {
        if (c[d]++ == 0) _t.push_back (d);
      }
    }
    t.clear ();
  }
  for (int x : _t) c[x] = 0; //c相当于mp，不能暴力清空，因此需要记下每次所更改的位置
  _t.clear ();
  for (int i = h[x]; i; i = e[i].ne) {
    int y = e[i].to;
    if (y != fa && !vis[y]) {
      sum = s[y];
      ms[rt = 0] = inf;
      find (y, x);
      find (rt, 0);
      dfs (rt, x);//继续分治
    }    
  }
}
int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  cin >> T;
  while (T--) {
    cin >> n;
    fill (vis + 1, vis + n + 1, false);
    fill (h + 1, h + n + 1, 0);
    fill (c + 1, c + n + 1, 0);
    ans = cnt = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
      int u, v; 
      cin >> u >> v;
      add (u, v); add (v, u);
    }
    ms[rt = 0] = inf;
    sum = n;
    find (1, 0);
    find (rt, 0);
    dfs (rt, 0);
    cout << ans << '\n';
  }
  return 0;
}
```

---

