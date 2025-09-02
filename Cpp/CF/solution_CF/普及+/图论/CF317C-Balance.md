# Balance

## 题目描述

A system of $ n $ vessels with water is given. Several pairs of vessels are connected by tubes with transfusion mechanisms. One may transfer an integer amount of liters of water between two vessels connected by such tube (tube works in both directions). There might be multiple tubes between two vessels. Total number of tubes equals $ e $ . Volume of each vessel equals $ v $ liters. Of course, the amount of the water in any vessel cannot exceed $ v $ liters in the process of transfusions.

Given the initial amounts $ a_{i} $ of water in the vessels and the desired amounts $ b_{i} $ find a sequence of transfusions that deals with the task. Total number of transfusions must not exceed $ 2·n^{2} $ .

## 样例 #1

### 输入

```
2 10 1
1 9
5 5
1 2
```

### 输出

```
1
2 1 4
```

## 样例 #2

### 输入

```
2 10 0
5 2
4 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 10 0
4 2
4 2
```

### 输出

```
0
```

# 题解

## 作者：xyf007 (赞：2)

首先如果 $\sum_{i=1}^na_i \neq \sum_{i=1}^nb_i$，显然无解。  
接下来考虑依次满足所有水桶的要求。任取两个水桶 $s,t$ 满足 $a_s>b_s,a_t<b_t$，则可以运输 $\min(a_s-b_s,b_t-a_t)$ 的水。用一个递归函数 `f(s, t, d)` 表示从 $s$ 向 $t$ 运输 $d$ 的水的过程。设 $t^\prime$ 为 $s \rightarrow t$ 路径上 $t$ 之前的那个点，则先尽量多的从 $t^\prime$ 向 $t$ 运输水，接着运行 `f(s, t', d)`。如果第一次水不够用，再补足不足的水。这样一次运输过程最多使用 $2n$ 次操作，因此总次数不超过 $2n^2$。  
由于 $n$ 很小，可以暴力存储所有的路径，因此实现较为简单。注意特判两点不连通的情况。
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
char Gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  int f = 1;
  char c;
  while ((c = Gc()) < '0' || c > '9')
    if (c == '-') f = -1;
  x = c - '0';
  while ((c = Gc()) >= '0' && c <= '9') x = x * 10 + (c - '0');
  x *= f;
}
template <typename T, typename... Args>
void Read(T &x, Args &...args) {
  Read(x);
  Read(args...);
}
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
struct Edge {
  int to, nxt;
} e[100001];
int n, v, m, E, head[301], a[301], b[301], s;
std::vector<int> v1, v2, g[301][301], tmp;
std::vector<std::tuple<int, int, int>> ans;
bool vis[301];
void Add(int f, int t) {
  e[E].to = t;
  e[E].nxt = head[f];
  head[f] = E++;
}
void Dfs(int u) {
  g[s][u] = tmp;
  for (int i = head[u]; i != -1; i = e[i].nxt) {
    int v = e[i].to;
    if (vis[v]) continue;
    tmp.emplace_back(v);
    vis[v] = true;
    Dfs(v);
    tmp.pop_back();
  }
}
void Transfer(int s, int t, int d) {
  if (s == t || g[s][t].empty()) return;
  int pre = g[s][t][g[s][t].size() - 2], cnt = std::min(a[pre], d);
  ans.emplace_back(pre, t, cnt);
  a[pre] -= cnt;
  a[t] += cnt;
  Transfer(s, pre, d);
  if (cnt < d) {
    ans.emplace_back(pre, t, d - cnt);
    a[pre] -= d - cnt;
    a[t] += d - cnt;
  }
}
int main(int argc, char const *argv[]) {
  std::memset(head, -1, sizeof(head));
  Read(n, v, m);
  for (int i = 1; i <= n; i++) Read(a[i]);
  for (int i = 1; i <= n; i++) Read(b[i]);
  if (std::accumulate(a + 1, a + n + 1, 0LL) !=
      std::accumulate(b + 1, b + n + 1, 0LL)) {
    std::printf("NO");
    return 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    Read(u, v);
    Add(u, v);
    Add(v, u);
  }
  for (int i = 1; i <= n; i++)
    if (a[i] > b[i])
      v1.emplace_back(i);
    else if (a[i] < b[i])
      v2.emplace_back(i);
  for (s = 1; s <= n; s++) {
    std::memset(vis, false, sizeof(vis));
    tmp.emplace_back(s);
    vis[s] = true;
    Dfs(s);
    tmp.pop_back();
  }
  std::size_t p1 = 0, p2 = 0;
  while (p1 < v1.size() && p2 < v2.size())
    if (a[v1[p1]] - b[v1[p1]] == b[v2[p2]] - a[v2[p2]]) {
      int d = a[v1[p1]] - b[v1[p1]];
      Transfer(v1[p1++], v2[p2++], d);
    } else if (a[v1[p1]] - b[v1[p1]] < b[v2[p2]] - a[v2[p2]]) {
      int d = a[v1[p1]] - b[v1[p1]];
      Transfer(v1[p1++], v2[p2], d);
    } else {
      int d = b[v2[p2]] - a[v2[p2]];
      Transfer(v1[p1], v2[p2++], d);
    }
  for (int i = 1; i <= n; i++)
    if (a[i] != b[i]) {
      std::printf("NO");
      return 0;
    }
  std::printf("%d\n", static_cast<int>(ans.size()));
  for (auto &&i : ans)
    std::printf("%d %d %d\n", std::get<0>(i), std::get<1>(i), std::get<2>(i));
  return 0;
}
```

---

## 作者：清烛 (赞：1)

那么首先明确，$a_i<b_i$ 的点是需要别的点引入的，而 $a_i>b_i$ 的点是需要供给给别的点的。首先对于每个连通块 $\sum a_i\ne \sum b_i$ 则一定无解。那么我们便可以将问题放在生成树上考虑，因为 $O(n^2)$ 的操作次数还是比较松的。

那么有一个最朴素的思路就是枚举这些 $a_i < b_i$ 的点，然后让同一连通块内的 $a_i > b_i$ 点对其进行供给，由于有 $v$ 的限制，最多需要进行 $2(n-1)$ 次（一次不行咱就两次）。

但同时我们也有更优的思路：从叶子节点开始，若其满足 $a_i < b_i$，则从其邻近节点“吸血”以满足自己的条件，若邻近节点不够就递归继续吸，然后满足了这个叶子节点的限制后，删掉这个叶子节点。问题便变成了规模 $-1$ 的子问题（当然前提是有解），而一次这样的调整最多需要 $n-1$ 次操作，所以这样做上界就是 $n^2$ 的了（而且感觉比较松）。对于 $a_i > b_i$ 的点就递归释放即可，思路类似。

代码细节稍微有一点小多，需要好好实现一下。


```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
const int maxn = 305;
int n, V, m, a[maxn], b[maxn];
vector<int> G[maxn], T[maxn];
int vis[maxn], deg[maxn];
long long suma, sumb;
queue<int> q;

struct Op {
    int x, y, d;
    Op(int _x = 0, int _y = 0, int _d = 0) : x(_x), y(_y), d(_d) {}
};
vector<Op> ans;

void dfs0(int u) {
    vis[u] = 1;
    suma += a[u], sumb += b[u];
    for (auto &v : G[u]) if (!vis[v]) {
        T[u].push_back(v), T[v].push_back(u);
        ++deg[u], ++deg[v];
        dfs0(v);
    }
    if (deg[u] == 1) q.push(u);
    return;
}

int dfs1(int u, int fa, int in) { // 返回消化了的流量
    int ta = a[u] + in, orga = a[u], out = 0;
    if (ta >= 0 && ta <= V) {
        a[u] = ta;
        if (in >= 0) ans.push_back(Op(fa, u, in));
        else ans.push_back(Op(u, fa, -in));
        return in;
    } else if (ta < 0) { // in < 0 fa 吸血 u
        for (auto &v : T[u]) if (v != fa && vis[v] != 2) {
            int cur = dfs1(v, u, ta);
            ta -= cur, out += cur;
            if (ta >= 0) break;
        }
        a[u] = max(0, ta);
        ans.push_back(Op(u, fa, orga - a[u] - out));
        return a[u] - orga + out;
    } else if (ta > V) {
        for (auto &v : T[u]) if (v != fa && vis[v] != 2) {
            int cur = dfs1(v, u, ta - V);
            ta -= cur, out += cur;
            if (ta <= V) break;
        }
        a[u] = min(V, ta);
        ans.push_back(Op(fa, u, a[u] - orga + out));
        return a[u] - orga + out;
    }
    return 0;
}

int main() {
    cin >> n >> V >> m;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) cin >> b[i];
    FOR(i, 1, m) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    FOR(i, 1, n) if (!vis[i]) {
        suma = sumb = 0;
        dfs0(i);
        if (suma != sumb) return puts("NO"), 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int v = -1;
            for (auto &vv : T[u]) if (vis[vv] != 2) {
                v = vv;
                break;
            }
            if (v == -1) continue;
            dfs1(v, u, a[u] - b[u]);
            a[u] = b[u];
            vis[u] = 2;
            if (--deg[v] == 1) q.push(v);
        }
    }
    cout << ans.size() << endl;
    for (auto &o : ans) cout << o.x << ' ' << o.y << ' ' << o.d << '\n';
    return 0;
}
```



---

## 作者：Mobius127 (赞：1)

[题传](https://www.luogu.com.cn/problem/CF317C)

显然对于每一个连通块若 $\sum_{i=1}^{|S|}a_{S_i}\ne\sum_{i=1}^{|S|}b_{S_i}$ 无解，否则我们必然珂以构造出一组解（不考虑步数限制）。

上面最后一句话引导我们想到图的连通性是解题要点，冗余的边没用，将图缩小到树，即随便求一棵原图的生成森林，在上面求解。

当一个点满足了 $a_i=b_i$，我们称其是锁定的，现在考虑一个非常暴力地做法。

对于一棵子树，假设其除了根节点外的点都已经锁定，那么我们不再使用儿子取满足根的条件，而是用子树外所有未锁定的点（当我们只做了子树的时候，这些点显然还是能构成一个连通块）去满足，这里假设根的现状是 $a>b$ （小于同理），具体操作如下：

1. 从当前根出发进行向外的 dfs，设递归到 $x$

1. 每当递归完 $x$ 的一个后继结点 $y$ 之后，将 $x$ 内的值尽可能地推向 $y$。

1. 回溯。

特别的，当第二布中 $x$ 为子树的根时，我们将 $x$ 需要减小到的下界从 $0$ 调到 $b$。

其实这就类似于让所有非锁定结点（相对于根的位置）尽量往后面挪，腾出位置把 $a-b$ 的水排出来。（小于就相当于把所有的水往根聚拢）。

分析：每次都至少会让当前子树的根锁定，在一轮中每个点只会与自己的父亲产生一次交换，因此交换次数（应该是）最多只有 $O(n(n-1))$ 次的，十分宽裕。

复杂度 $O(n^2+m)$。

[$Code$](https://codeforces.com/problemset/submission/317/158742684)

---

