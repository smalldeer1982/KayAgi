# Git Gud

## 题目描述

[problemUrl]: https://atcoder.jp/contests/toyota2023spring-final/tasks/toyota2023spring_final_g

プログラミング初心者のすぬけくんが，以下のようなコードを書きました．

```
N = read_integer()

parent = array(N, -1) //長さ N の配列 parent を作り，すべての要素を -1 で初期化

find(v):
    if parent[v] == -1:
        return v
    else:
        return find(parent[v])

union(a,b):
    parent[find(b)] = find(a)

for i = 0 to N-2:
    A_i = read_integer()
    B_i = read_integer()
    union(A_i,B_i)
```

これは，$ N $ 頂点の木の情報を受けとり，Union-Find で辺を結ぶだけのプログラムです．

プログラミングマスターのりんごさんは，このプログラムの欠陥に気が付きました． すなわち，Union-Find に一切の高速化が施されていないのです．

今，りんごさんは $ N $ 頂点からなる木 $ T $ を持っています． $ T $ の頂点には $ 0 $ から $ N-1 $ までの番号が，辺には $ 0 $ から $ N-2 $ までの番号がついています． 辺 $ i $ は頂点 $ A_i $ と頂点 $ B_i $ を結ぶ辺です．

りんごさんは，すぬけくんのプログラムに $ T $ を入力として与えようとしています． ただしその前に，$ T $ の辺の番号と，辺の端点の順番を自由に入れ替えることができます．

りんごさんは，すぬけくんのプログラムが非効率的であることを示すために，`find` 関数が呼ばれる回数を最大化したいです． `find` 関数が呼ばれる回数の最大値を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ A_i,B_i\ \leq\ N-1 $
- $ A_i\ \neq\ B_i $
- 入力されるグラフは木である

### Sample Explanation 1

`find` 関数は必ず $ 2 $ 回呼ばれます．

### Sample Explanation 2

辺 $ 0 $ の端点の順番を入れ替え，以下のような入力を作ると，`find` 関数が $ 5 $ 回呼ばれます． ``` 3 1 0 0 2 ```

### Sample Explanation 3

辺の順番と辺の端点の順番を適切に入れ替え，以下のような入力を作ると，`find` 関数が $ 13 $ 回呼ばれます． ``` 5 3 0 4 3 1 0 0 2 ```

## 样例 #1

### 输入

```
2
0 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 1
0 2```

### 输出

```
5```

## 样例 #3

### 输入

```
5
0 1
0 2
0 3
3 4```

### 输出

```
13```

## 样例 #4

### 输入

```
20
6 16
10 6
16 8
1 5
9 4
5 3
13 16
19 10
12 2
14 10
12 18
0 2
15 16
12 7
11 14
1 10
6 4
17 8
12 1```

### 输出

```
148```

# 题解

## 作者：Mine_King (赞：4)

考虑连一条边对其他边的贡献。  
连一条边会使一边的连通块所有点深度 $+ 1$，则这些点未连的边的贡献都会增加 $1$，因此定义一个连通块的权值为未连的边的数量，则连接一条边会增加权值较大的连通块的权值，然后合并后新连通块的权值为原权值之和 $- 2$。  
可以将每个点的初始权值设为度数 $- 2$，这样合并就不需要减了，最后额外加上 $2 n - 2$ 即可。

观察发现一定是一个点一个点加到一个大连通块里最优。因此就变成了找一个根，然后按某种顺序遍历树，遍历到一个点就加到连通块里。考虑一个点若在 $t$ 时刻加入，则其权值会贡献 $n - t$ 次。  
不妨改成 $n - t + 1$ 次，最后答案再 $+ 2$ 即可。然后考虑将点向父亲合并。  
对于两个连通块 $A, B$，设其答案为 $aval, bval$，权值之和为 $asum, bsum$，连通块大小为 $asiz, bsiz$，则 $A$ 在 $B$ 前的贡献为 $aval + asum \times bsiz + bval$，$B$ 在 $A$ 前的贡献为 $bval + bsum \times asiz + aval$，稍作变换可以得到 $A$ 在 $B$ 前更优当且仅当 $\frac{asum}{asiz} > \frac{bsum}{bsiz}$，也就是每次选择平均权值最大的连通块与父亲合并更优。  
那么直接用堆和并查集维护并计算贡献即可。

注意一个小细节：最开始考虑贡献的时候每条边都少算了 $1$ 的贡献，因此最后要加上 $n - 1$，也就是算完后总贡献要加上 $3 n - 1$。

```cpp
// Think twice, code once.
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

int n, deg[2005], ans;
struct graph {
	int tot, hd[2005];
	int nxt[4005], to[4005];

	void add(int u, int v) {
		nxt[++tot] = hd[u];
		hd[u] = tot;
		to[tot] = v;
		return ;
	}
} g;
int fa[2005];
struct node {
	int id, val, siz;
	
	node() = default;
	node(int _id, int _val, int _siz): id(_id), val(_val), siz(_siz) {}
	bool operator<(const node &x) const {return val * x.siz < x.val * siz;}
};
struct dsu {
	int fa[2005];
	
	void clear() {for (int i = 1; i < 2005; i++) fa[i] = i; return ;}
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	void merge(int x, int y) {fa[find(x)] = find(y); return ;}
} d;
int val[2005], sum[2005], siz[2005];

void dfs(int now, int F) {
	fa[now] = F;
	for (int i = g.hd[now]; i; i = g.nxt[i])
		if (g.to[i] != F) dfs(g.to[i], now);
	return ;
}
int solve(int root) {
	dfs(root, 0);
	priority_queue<node> q;
	for (int i = 1; i <= n; i++) q.emplace(i, val[i] = sum[i] = deg[i], siz[i] = 1);
	d.clear();
	while (!q.empty()) {
		node now = q.top();
		q.pop();
		if (now.id == root || d.find(now.id) != now.id) continue;
		int to = d.find(fa[now.id]);
		val[to] += sum[to] * siz[now.id] + val[now.id];
		q.emplace(to, sum[to] += sum[now.id], siz[to] += siz[now.id]);
		d.merge(now.id, to);
	}
	return val[root] + 3 * n - 1;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u++, v++;
		g.add(u, v), g.add(v, u);
		deg[u]++, deg[v]++;
	}
	for (int i = 1; i <= n; i++) deg[i] -= 2;
	for (int i = 1; i <= n; i++) ans = max(ans, solve(i));
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：kyEEcccccc (赞：4)

拜谢 Magic Duck 大神。其次我很喜欢洛谷逆天翻译把大翻译成小……

首先考虑算一下贡献，考虑每个点的深度，一开始都是 1，进行合并以后相当于首先把两个端点的深度累计到答案里，然后再选择一边给它的联通块内每个点深度增加 1。那么容易发现我们可以算贡献转化为每个联通块权值为它向外的度数，每次合并任意选择一边将它的权值累积进答案（当然一定选择大的那边），然后合并两联通块。那么合并联通块度数相加还会损失 2，这里的一个技巧是把权值设为度数减二，这样就可以直接相加了。最后再把答案加上 $2n - 2$，这是因为合并次数是已知的。于是这个问题得到了比较好的转化。

考虑一个结论：任何一次合并不会选择两个已经被合并过的联通块将它们合并。随便考虑四个块排成一排，发现总是能构造出一种依次合并进某个块的顺序，使得它优于分别合并两边再合并中间的边的方案。那么最优的合并顺序一定是选择一个根，然后依次把下面的节点合并进根里。此外，我们不妨假设任何一次合并时，根处的权值都大于被合并的另一个权值，否则换成下面那个点为根一定更优。

于是枚举这个根，问题变成了给定一棵有根树，每个点有点权，给每个点赋 $[1, n]$ 内互不相同的整数系数，要求父亲系数大于儿子，最大化系数乘点权的和。这是经典问题，考虑权值最大的点标号一定等于它父亲的标号减一，那么直接考虑把它合并进父亲，于是每个点有一个大小和一个权值和，我们容易发现它的“等效权值”就是它的权值和除以它的大小。于是用并查集之类的随便合并一下就可以了。

---

## 作者：LPhang (赞：1)

并查集的过程相当于在建一棵树，一次 $find(u)$ 的操作次数相当于点 $u$ 的深度。考虑点 $u$ 向点 $v$ 合并，会使得点 $u$ 所在连通块的所有点深度加一，相应的，$u$ 所在连通块的还未连接的边，在之后连接的时候对答案的贡献会增加一。考虑将一个连通块的未连接的边数作为权值，那么每次连接一条边，肯定都是选择权值大的一边进行贡献，考虑到合并之后连通块的权值会 $-2$，不妨初始让所有连通块的权值都 $-2$，那么每次合并之后连通块的权值都是正确值 $-2$，这样两个连通块合并权值就可以直接相加。由于只计算了一个连通块的权值，每次合并还会少计算一个合并的那条边的贡献，调整后的权值每次合并少计算了 $2$。由于合并次数固定为 $n-1$，所以最后答案加上 $3n-3$ 即可。

发现两个权值为 $x$ 和 $y (x<y)$ 的连通块合并，不如让权值为 $x$ 的连通块拆成一个一个单点依次与另一个连通块合并。因为这样权值为 $x$ 的连通块中的每个点至少都会贡献 $y$ ，而原本这个连通块内的点的贡献都不超过 $x$，且 $x<y$，所以这样合并更优。

于是问题现在转化为选择一个根，照一定顺序依次选择与根所在连通块相邻的点合并进去，使得最后答案最大。考虑当点 $u$ 合并进去后，还有 $x$ 个点未被合并进去，那么点 $u$ 的权值就会贡献 $x$ 次。考虑一个集合 $A$ 比集合 $B$ 要先合并进去，集合内部分别会产生 $val_A$ 和 $val_B$ 的贡献，集合 $A,B$ 的权值和大小分别是 $sum_A,sum_B$ 和 $siz_A,siz_B$。由于 $B$ 后合并进去，所以 $A$ 集合的权值会贡献 $siz_B$ 次，所以此时总共会产生 $val_A + sum_A\times siz_B + val_B$ 的贡献，因此集合 $A$ 比集合 $B$ 先合并更优当且仅当 $sum_A\times siz_B > sum_B\times siz_A \iff \frac{sum_A}{siz_A}>\frac{sum_B}{siz_B}$。由于合并的方向是向根的，也就是向父亲合并，我们考虑维护这样的集合（在树上是一个连通块），类似于邻项交换的思想——贪心的选择 $\frac{sum}{siz}$ 最大的连通块向父亲合并。用大根堆和并查集实现即可。

```cpp
#include<bits/stdc++.h>
#define rep1(i, a, b) for(int i = a; i <= b; ++i)
#define rep2(i, a, b) for(int i = a; i >= b; --i)
#define ft first
#define sd second
#define pii pair <int, int>
#define ll long long
#define ld long double
#define pb push_back
#define vect basic_string
#define all(a) a.begin(), a.end()
#define debug puts("----------------------------")
const int N = 2e3 + 10;
using namespace std;
vect <int> e[N];
int f[N], pa[N], sum[N], sz[N];
ll ans[N];
void dfs(int u, int pa) {
    f[u] = pa;
    for(auto v : e[u]) if(v ^ pa) dfs(v, u);
}
int find(int x) {return pa[x] == x ? x : pa[x] = find(pa[x]);}
void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return ; pa[u] = v;
    ans[v] += sum[v] * sz[u] + ans[u];
    sz[v] += sz[u]; sum[v] += sum[u];
}
void solve() {
    int n; cin >> n;
    rep1(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        ++u; ++v;
        e[u] += v; e[v] += u;
    }
    ll answer = 0;
    rep1(i, 1, n) {
        dfs(i, i);

        struct node {
            int id, v, s;
        } ;
        auto cmp = [](node &x, node &y) {return 1ll * x.v * y.s < 1ll * y.v * x.s;};
        priority_queue <node, vector <node>, decltype(cmp)> q(cmp);

        rep1(j, 1, n) {
            pa[j] = j, sz[j] = 1; ans[j] = 0;
            sum[j] = e[j].size() - 2;
            if(j ^ i) q.push({j, sum[j], sz[j]});
        }
        while(q.size()) {
            node x = q.top(); q.pop();
            int u = x.id;
            if(sum[u] != x.v || sz[u] != x.s) continue;
            merge(u, f[u]); int g = find(u);
            if(g ^ i) q.push({g, sum[g], sz[g]});
        }
        answer = max(answer, ans[i] + 3 * (n - 1));
    }
    cout << answer << '\n';
}
int main() {
    int T = 1;
    while(T--) solve();
    return 0;
}
```

---

## 作者：StayAlone (赞：1)

拆贡献，合并两个连通块时，会使某一个连通块的深度 $+1$，故答案增加该连通块未连的边数。

设一个连通块的权值为未连边数，合并时答案增加两连通块的较大权值，新连通块的权值为两者权值之和 $-2$。为了方便，将初始权值设为度数 $-2$，则容易发现合并时权值直接相加，每次的答案都少算 $2$，最后要加上 $2n-2$。

观察到最优解一定是将单点一个个插入某个连通块中。则枚举第一个点作为根，第 $i$ 个插入的点 $p_i$ 会贡献 $(n-i)\times val_{p_i}$。为了方便，改写为 $(n-i+1)\times val_{p_i}$，则多算了 $\sum val_{i} = 2(n-1)-2n=-2$，最后要加回来。

于是问题转化成，给每个点赋权 $rnk$，使得父亲的 $rnk$ 大于儿子的 $rnk$，且 $rnk$ 构成 $1\sim n$ 的排列，要求 $\sum val_i\times rnk_i$ 最大。这是一个经典问题：[UVA1205](https://www.luogu.com.cn/problem/UVA1205)，推出排序方式后用并查集和堆进行连通块合并即可。

在实际合并时，上述算法遗漏了单点调用的一次 `find`，共漏了 $n-1$ 次。加上之前的偏移，共 $3n-1$。

时间复杂度 $\mathcal O(n^2\log n)$。

[AC record](https://atcoder.jp/contests/toyota2023spring-final/submissions/67067687)

```cpp
int n, rt, opt = -inf, pa[MAXN], vis[MAXN], ind[MAXN];
vector <int> lnk[MAXN];

struct node {
    int siz, f, val;
} a[MAXN];
priority_queue <pair <double, int>> q;

il int fpa(int x) {
    return x ^ pa[x] ? pa[x] = fpa(pa[x]) : x;
}

int main() {
    read(n);
    rep1(i, 1, n - 1) {
        int u, v; read(u, v);
        ++ind[u + 1]; ++ind[v + 1];
        lnk[u + 1].eb(v + 1); lnk[v + 1].eb(u + 1);
    }
    auto dfs = [&](auto self, int x) -> void {
        for (auto v : lnk[x]) if (v ^ a[x].f) a[v].f = x, self(self, v);
    };
    rep1(rt, 1, n) {
        int ans = 0;
        rep1(i, 1, n) {
            a[i].siz = 1, ans += (a[i].val = ind[i] - 2);
            pa[i] = i; vis[i] = 0;
            if (i != rt) q.emplace(a[i].val, i);
        } a[rt].f = 0; dfs(dfs, rt);
        while (q.size()) {
            int x = q.top().snd; q.pop();
            if (vis[x]) continue;
            vis[x] = 1; int g = fpa(a[x].f);
            ans += a[x].siz * a[g].val;
            a[g].siz += a[x].siz; a[g].val += a[x].val; pa[x] = g;
            if (g ^ rt) q.emplace(1. * a[g].val / a[g].siz, g);
        } gmax(opt, ans);
    } printf("%d", opt + 3 * n - 1);
    return 0;
}
```

---

