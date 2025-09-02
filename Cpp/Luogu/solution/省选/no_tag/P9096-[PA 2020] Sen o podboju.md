# [PA 2020] Sen o podboju

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 2 [Sen o podboju](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/sen/)**

国王 Byteur，Byteotia 的统治者，目前正梦想着征服 Bitotia。就像在现实世界中一样，在他的梦中他还远远没有打败敌人。因此，他想知道他能做些什么来削弱敌国的实力……

在他的梦中，Bitotia 由 $n$ 个城市（编号从 $1$ 到 $n$）组成，由 $n-1$ 条双向道路连接，可以只用这些道路从任意一个城市到达任意其他城市。换句话说，Bitotia 的地图形成了一棵树。然而，Byteur 并不记得 Bitotia 的确切道路网络……所以他的脑内生成了一个**随机**的道路网络。

国王得出的结论是，强行将 Bitotia 分割成 $k$ 个小国是个好主意。Byteur 所说的划分，是指秘密地破坏正好是 $k - 1$ 条道路，这将迫使 Bitotia 分解成 $k$ 个小国，这些小国是去除选定的边后形成的连通子图。

然而，对于国王来说，摧毁任何 $k-1$ 条道路都是不够的。每个 Bitotia 的城市都有一个**军事系数** $a_i$，也是由 Byteur 脑内想出来的。Byteur 知道，一个小国的军事力量越强，对 Byteotia 的威胁就越大。更准确地说：如果在一个小国，其城市的军事系数之和等于 $S$，那么来自这个小国的威胁就等于 $S^2$。对 Byteotia 的总威胁等于这 $k$ 个小国所产生的威胁之和。

现在 Byteur 求助于你——他的梦想（指的是字面意思！）程序员。请帮助他，计算出 Bitotia 分裂成各州后可能产生的最小总威胁。由于 Byteur 还没有决定参数 $k$ 的值，请计算 $k$ 取从 $1$ 到 $n$（包含两端）所有值的结果。

## 说明/提示

#### 样例 1 解释

以上测试数据使用随机数种子为 $8\ 122\ 020$，$t=2,n_{\min}=5,n_{\max}=7,a_{\max}=10$ 的参数生成。

对于第一个测试案例，输出的第一个数字是 $(9+1+4+2+6+4+7)^2=1089$，代表未被分割的 Bitotia 所带来的总威胁。输出的第二个数字对应的是如果连接 $5$ 号和 $7$ 号城市的道路被摧毁的总威胁；在这种情况下，威胁将是 $(9+7)^2+(1+4+2+6+4)^2=545$。

------------

#### 数据生成

本题的样例生成器在附件中给出。生成器将以下内容作为输入接受：生成器种子和数字 $t,n_{\min},n_{\max},a_{\max}$。本题的所有测试数据都将用与之相当的生成器生成（即用不同的伪随机数库，与编译器的实现无关）。

为了确保测试的随机性，每个测试点的 $t,n_{\min},n_{\max},a_{\max}$ 的值都是手动选择的，生成器的种子是随机选择的。

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le t\le 10$，$2\le n\le 300$，$1\le a_i\le 10^6$，$1\le b_i,c_i\le n$，$2\le n_{\min}\le n_{\max}\le 300$，$1\le a_{\max}\le 10^6$。

## 样例 #1

### 输入

```
2
7
9 1 4 2 6 4 7
1 7
6 4
2 3
5 7
3 4
5 3
5
4 8 2 3 1
4 3
3 1
4 2
5 1```

### 输出

```
1089 545 371 287 227 211 203
324 164 114 102 94```

# 题解

## 作者：Sol1 (赞：2)

upd. 修个笔误。

---

数据随机自然是乱搞。

考虑一个暴力 dp：$f_{i,j,k}$ 表示 $i$ 子树，断了 $j$ 条边，根所在连通块的 $a$ 的和是 $k$，最小的连通块平方和。

对于边 $(u,v)$，转移是：

- $f_{u,x,y}+f_{v,p,q}+2yq\rightarrow f_{u,x+p,y+q}'$（不断 $u,v$ 边）
- $f_{u,x,y}+f_{v,p,q}\rightarrow f_{u,x+p+1,y}'$（断 $u,v$ 边）

复杂度 $O(n^2w^2)$，显然过不了。

考虑剪枝，对于 $k_1<k_2$，如果 $f_{i,j,k_1}<f_{i,j,k_2}$，那么 $k_2$ 显然没用。

于是我们对每一个 $f_{i,j}$ 开个 vector 存所有有用的 $k$，每次暴力枚举两个 $k$ 转移，转移完暴力对所有 vector 按 $k$ 排序再暴力删掉所有没用的点。

然后这个算法就直接以最大点不到半秒的优异表现通过了这道题！

复杂度我不会严格分析，不过感性理解的话，假定 dp 数组在树和点权都均匀随机的情况下足够均匀随机，那么根据前缀最大值个数期望（也就是笛卡尔树深度期望），复杂度可以分析为 $O(n^2\log^2 w)$。

```cpp
const int N = 305;

struct Edge {
    int to, nxt;
    Edge() {
        nxt = -1;
    }
};
int n, hd[N], siz[N], pnt;
long long a[N];
Edge e[N << 1];
vector <pair <long long, long long> > dp[N][N], tmp[N];

inline void AddEdge(int u, int v) {
    e[++pnt].to = v;
    e[pnt].nxt = hd[u];
    hd[u] = pnt;
}

inline void Read() {
    n = qread();
    for (int i = 1;i <= n;i++) a[i] = qread();
    for (int i = 1;i < n;i++) {
        int u = qread(), v = qread();
        AddEdge(u, v); AddEdge(v, u);
    }
}

inline void Dfs(int u, int fa) {
    siz[u] = 1;
    for (int i = 0;i <= n;i++) dp[u][i].clear();
    dp[u][0].push_back(make_pair(a[u], a[u] * a[u]));
    for (int i = hd[u];~i;i = e[i].nxt) {
        int v = e[i].to;
        if (v != fa) {
            Dfs(v, u);
            for (int i = 0;i <= siz[v];i++) {
                for (int j = 0;j <= siz[u];j++) {
                    for (auto x : dp[v][i]) {
                        for (auto y : dp[u][j]) {
                            tmp[i + j].push_back(make_pair(x.first + y.first, x.second + y.second + 2 * x.first * y.first));
                            tmp[i + j + 1].push_back(make_pair(y.first, x.second + y.second));
                        }
                    }
                }
            }
            siz[u] += siz[v];
            for (int i = 0;i <= siz[u];i++) {
                dp[u][i].clear();
                sort(tmp[i].begin(), tmp[i].end());
                long long mnv = 0x3f3f3f3f3f3f3f3f;
                for (int j = 0;j < tmp[i].size();j++) {
                    if (tmp[i][j].second < mnv) {
                        mnv = tmp[i][j].second;
                        dp[u][i].push_back(tmp[i][j]);
                    }
                }
                tmp[i].clear();
            }
        }
    }
}
```

---

