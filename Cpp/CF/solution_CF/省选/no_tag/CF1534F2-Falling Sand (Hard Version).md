# Falling Sand (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is the constraints on $ a_i $ . You can make hacks only if all versions of the problem are solved.

Little Dormi has recently received a puzzle from his friend and needs your help to solve it.

The puzzle consists of an upright board with $ n $ rows and $ m $ columns of cells, some empty and some filled with blocks of sand, and $ m $ non-negative integers $ a_1,a_2,\ldots,a_m $ ( $ 0 \leq a_i \leq n $ ). In this version of the problem, $ a_i $ will always be not greater than the number of blocks of sand in column $ i $ .

When a cell filled with a block of sand is disturbed, the block of sand will fall from its cell to the sand counter at the bottom of the column (each column has a sand counter). While a block of sand is falling, other blocks of sand that are adjacent at any point to the falling block of sand will also be disturbed and start to fall. Specifically, a block of sand disturbed at a cell $ (i,j) $ will pass through all cells below and including the cell $ (i,j) $ within the column, disturbing all adjacent cells along the way. Here, the cells adjacent to a cell $ (i,j) $ are defined as $ (i-1,j) $ , $ (i,j-1) $ , $ (i+1,j) $ , and $ (i,j+1) $ (if they are within the grid). Note that the newly falling blocks can disturb other blocks.

In one operation you are able to disturb any piece of sand. The puzzle is solved when there are at least $ a_i $ blocks of sand counted in the $ i $ -th sand counter for each column from $ 1 $ to $ m $ .

You are now tasked with finding the minimum amount of operations in order to solve the puzzle. Note that Little Dormi will never give you a puzzle that is impossible to solve.

## 说明/提示

For example $ 1 $ , by disturbing both blocks of sand on the first row from the top at the first and sixth columns from the left, and the block of sand on the second row from the top and the fourth column from the left, it is possible to have all the required amounts of sand fall in each column. It can be proved that this is not possible with fewer than $ 3 $ operations, and as such the answer is $ 3 $ . Here is the puzzle from the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F2/3a2f28320c431f7fc4be328a7626876c2ea55199.png)For example $ 2 $ , by disturbing the cell on the top row and rightmost column, one can cause all of the blocks of sand in the board to fall into the counters at the bottom. Thus, the answer is $ 1 $ . Here is the puzzle from the second example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F2/a5e473b6fa07dabecf94f6cfb85782199edfaea0.png)For example $ 3 $ , by disturbing the cell on the top row and rightmost column, it is possible to have all the required amounts of sand fall in each column. It can be proved that this is not possible with fewer than $ 1 $ operation, and as such the answer is $ 1 $ . Here is the puzzle from the third example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F2/1fc3ea7256a4b5592bfedf787a418e8660ce837b.png)

## 样例 #1

### 输入

```
5 7
#....#.
.#.#...
#....#.
#....##
#.#....
4 1 1 1 0 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
#.#
#..
##.
3 1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
7 5
.#..#
#....
..##.
..##.
..###
..#..
#.##.
0 0 2 4 2```

### 输出

```
1```

# 题解

## 作者：AsunderSquall (赞：19)

其他题解做法说的很详细了，这里补充一个不需要 tarjan 缩点的，代码比较清新的做法。  

大体思路是一样的，但是我们不进行缩点。  
我们称每一列从下往上数的第 $a_i$ 个点为关键点，每一列的第一个点为起始点。    
对于每个关键点，求出最左能覆盖它的起始点在哪一列，最右能覆盖它的起始点在哪一列。这个可以用两遍 dfs 来解决。  

然后直接转移即可。  

具体可以见代码。

```cpp

int n,m,pos,ans;
char s[N],str[N];
int a[N],L[N],R[N],f[N];
int p(int x,int y){return x*m-m+y;}
void dfs1(int x,int y,int k)
{
	if(L[p(x,y)]!=-1) return;L[p(x,y)]=k;
	if(x<n) dfs1(x+1,y,k);
	if(x>1 && s[p(x-1,y)]=='#') dfs1(x-1,y,k);
	if(y>1 && s[p(x,y-1)]=='#') dfs1(x,y-1,k);
	if(y<m && s[p(x,y+1)]=='#') dfs1(x,y+1,k);
}
void dfs2(int x,int y,int k)
{
	if(R[p(x,y)]!=-1) return;R[p(x,y)]=k;
	if(x<n) dfs2(x+1,y,k);
	if(x>1 && s[p(x-1,y)]=='#') dfs2(x-1,y,k);
	if(y>1 && s[p(x,y-1)]=='#') dfs2(x,y-1,k);
	if(y<m && s[p(x,y+1)]=='#') dfs2(x,y+1,k);
}
signed main()
{
    rd(n);rd(m);
    for (int i=1;i<=n;i++) {scanf("%s",str+1);for (int j=1;j<=m;j++) s[p(i,j)]=str[j];}
    for (int i=1;i<=m;i++) rd(a[i]);
    memset(L,-1,sizeof(L));memset(R,-1,sizeof(R));
    for (int j=1;j<=m;j++) for (int i=1;i<=n;i++) if (s[p(i,j)]=='#') dfs1(i,j,j);
    for (int j=m;j>=1;j--) for (int i=1;i<=n;i++) if (s[p(i,j)]=='#') dfs2(i,j,j);
    for (int i=1;i<=m+2;i++) f[i]=m+2;
    for (int j=1;j<=m;j++) if (a[j]) for (int i=n;i>=1;i--) if (s[p(i,j)]=='#')
    {
        a[j]--;if (a[j]==0) {f[L[p(i,j)]]=min(f[L[p(i,j)]],R[p(i,j)]+1);break;}
    }
    for (int i=m+1;i>=1;i--) f[i]=min(f[i],f[i+1]);pos=1;
    while (pos<m+2) pos=f[pos],ans++;
    cout<<ans-1<<endl;
    
}
```


---

## 作者：zhangjunyan2580 (赞：11)

## 题意

给一个 $n \times m$ 的网格，某些格子里有沙子，其他格子里没有。你可以选择一些沙子使其掉落。沙子在下落过程中会扰动相邻（上下左右）的沙子，使它们一同掉落。问至少要选择多少沙子才能使第 $i$ 列下落的沙子最少为 $a_i$ 个。

## Easy Version

在Easy Version中，所有的沙子都要掉落。

考虑将扰动的关系建成图。我们对每个沙子向其上方一格的沙子、下方第一个沙子、左边一列和右边一列与当前沙子相邻或在当前沙子下方的沙子中最上方的沙子连边。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/li346bje.png)

容易发现一个沙子 $A$ 能扰动另一个沙子 $B$ 的充要条件是 $A$ 到 $B$ 有一条路径。问题变成了选取最少的点使得从这些点出发能到达图中的所有点。

我们可以先缩点变为有向无环图，易得所有入度为$0$的点都要被选取。

时间复杂度 $O(nm)$ 或 $O(nm \log (nm))$，取决于建图的时间复杂度。

## Hard Version

显然如果一个沙子掉落了其下的所有沙子也会掉落。所以我们只需扰动每一列中从下向上数第 $a_i$ 个沙子。我们称这些沙子对应的点为特殊点。问题转化成选取一些点，从这些点出发能覆盖到这些沙子对应的点。

如果从一个特殊点 $X$ 能到另一个特殊点 $Y$，则我们可以不考虑 $Y$，因为如果能到 $X$ 就一定能到 $Y$ 。我们从特殊点中删去这些点，按列排序可以得到一个数组 $A$。可以发现从图中任意一个点 $X$ 能到达的在 $A$ 中的特殊点在 $A$ 中的下标是连续的。

证：假如说从 $X$ 出发到达的 $A$ 中的特殊点不是连续的，那么存在两个 $A$ 中的点 $i, j$（$i$ 在 $j$ 的左边），从 $X$ 能到达 $i$ 和 $j$ 但不能到达 $i, j$ 中间的列的 $A$ 中的点。假设一个不能到达的 $A$ 中的点是 $Z$。由于扰动的列是连续的，一定存在一个点 $k$ 使得 $k$ 和 $Z$ 在同一列且从 $X$ 能到 $k$。假如 $k$ 在 $Z$ 上方，则 $X$ 能到 $Z$；假如 $k$ 在 $Z$ 下方，则 $Z$ 能到 $j$ ，则 $j$ 不在 $A$ 中，矛盾。

我们能用 DP 算出每个点能到的在 $A$ 中的点的区间。问题转换成了有若干条线段，我们要选取若干条线段使得它们能覆盖一个区间。这是一个经典问题，可以用贪心解决。

时间复杂度 $O(nm)$ 或 $O(nm \log (nm))$，取决于建图的时间复杂度。

代码：

```cpp
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>

int n, m, a[400005];
std::vector<int> sandl[400005];

struct edge {
    int to, nxt;
} g[2000005], g2[2000005], g3[2000005];
int head[400005], cnt, dgr[400005];
int low[400005], dfn[400005], in_stack[400005], stack[400005], h, dfs_id, belong[400005], bcnt;
int head2[400005], head3[400005], cnt2, indgr[400005];
int marked[400005];

int A_cnt, L[400005], R[400005], seg_cnt, ans;
struct segment {
    int l, r;
} segs[400005];

inline void add_edge(int f, int t) {
    g[++cnt].to = t;
    g[cnt].nxt = head[f];
    head[f] = cnt;
    ++dgr[f];
    ++dgr[t];
}
inline int node_num(int i, int j) {
    return (i - 1) * m + j;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_id;
    in_stack[u] = 1;
    stack[++h] = u;

    for (int i = head[u]; i; i = g[i].nxt) {
        if (!dfn[g[i].to]) {
            tarjan(g[i].to);
            if (low[g[i].to] < low[u])
                low[u] = low[g[i].to];
        } else if (in_stack[g[i].to] && dfn[g[i].to] < low[u])
            low[u] = dfn[g[i].to];
    }

    if (dfn[u] == low[u]) {
        ++bcnt;
        int j;
        do {
            j = stack[h--];
            in_stack[j] = 0;
            belong[j] = bcnt;
        } while (j != u);
    }
}

inline void add_edge2(int f, int t) {
    g2[++cnt2].to = t;
    g2[cnt2].nxt = head2[f];
    head2[f] = cnt2;
    g3[cnt2].to = f;
    g3[cnt2].nxt = head3[t];
    head3[t] = cnt2;
    ++indgr[f];
}
void mark(int u) {
    for (int i = head2[u]; i; i = g2[i].nxt)
        if (!marked[g2[i].to]) {
            marked[g2[i].to] = 1;
            mark(g2[i].to);
        }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            char c;
            scanf(" %c", &c);
            if (c == '#')
                sandl[j].push_back(i);
        }
    for (int i = 1; i <= m; ++i)
        scanf("%d", a + i);

    for (int i = 1; i <= m; ++i)
        for (unsigned j = 0; j < sandl[i].size(); ++j) {
            add_edge(node_num(sandl[i][j], i), node_num(sandl[i][j], i));

            if (j && sandl[i][j - 1] == sandl[i][j] - 1)
                add_edge(node_num(sandl[i][j], i), node_num(sandl[i][j] - 1, i));
            if (j != sandl[i].size() - 1)
                add_edge(node_num(sandl[i][j], i), (sandl[i][j + 1] - 1) * m + i);
            
            if (i != 1) {
                auto lq = std::lower_bound(sandl[i - 1].begin(), sandl[i - 1].end(), sandl[i][j]);
                if (lq != sandl[i - 1].end())
                    add_edge(node_num(sandl[i][j], i), node_num(*lq, i - 1));
            }
            if (i != m) {
                auto rq = std::lower_bound(sandl[i + 1].begin(), sandl[i + 1].end(), sandl[i][j]);
                if (rq != sandl[i + 1].end())
                    add_edge(node_num(sandl[i][j], i), node_num(*rq, i + 1));
            }
        }

    for (int i = 1; i <= n * m; ++i)
        if (dgr[i] && !dfn[i])
            tarjan(i);

    for (int i = 1; i <= n * m; ++i)
        for (int j = head[i]; j; j = g[j].nxt)
            if (belong[i] != belong[g[j].to])
                add_edge2(belong[i], belong[g[j].to]);

    for (int j = 1; j <= m; ++j)
        if (a[j])
            mark(belong[node_num(sandl[j][sandl[j].size() - a[j]], j)]);

    memset(L, 0x3f, sizeof(L));

    for (int j = 1; j <= m; ++j)
        if (a[j]) {
            int i = sandl[j][sandl[j].size() - a[j]];
            if (!marked[belong[node_num(i, j)]] && !R[belong[node_num(i, j)]]) {
                L[belong[node_num(i, j)]] = ++A_cnt;
                R[belong[node_num(i, j)]] = A_cnt;
            }
        }

    h = 0;

    for (int i = 1; i <= bcnt; ++i)
        if (!indgr[i])
            stack[++h] = i;

    while (h) {
        int u = stack[h--];

        for (int i = head3[u]; i; i = g3[i].nxt) {
            if (L[u] < L[g3[i].to])
                L[g3[i].to] = L[u];
            if (R[u] > R[g3[i].to])
                R[g3[i].to] = R[u];

            --indgr[g3[i].to];
            if (!indgr[g3[i].to])
                stack[++h] = g3[i].to;
        }
    }

    for (int i = 1; i <= bcnt; ++i)
        if (L[i] <= R[i]) {
            segs[++seg_cnt].l = L[i];
            segs[seg_cnt].r = R[i];
        }

    std::sort(segs + 1, segs + seg_cnt + 1, [](const segment & a, const segment & b) {
        return a.l == b.l ? a.r > b.r : a.l < b.l;
    });

    for (int i = 1, rmost = 0, rfur = 0, j = 1; i <= A_cnt; ++i) {
        while (j <= seg_cnt && segs[j].l <= i) {
            if (segs[j].r > rfur)
                rfur = segs[j].r;
            ++j;
        }
        if (i > rmost) {
            ++ans;
            rmost = rfur;
        }
    }

    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：RiverHamster (赞：7)

[在我的 cnblogs 上阅读](https://www.cnblogs.com/RiverHamster/p/sol-cf1534f2.html)

对所有的 `#` 编号并构造有向图：若 $i$ 被“影响”后能影响 $j$，则 $i$ 向 $j$ 连边。对于同一列的点，可以只对相邻的点连边。

先找出原图中的所有极大强连通分量并缩点。对于 Easy Version，答案即为缩点图中入度为 $0$ 的点数。

对于 Hard Version，若 $a_i > 0$，将第 $i$ 列的第 $a_i$ 个点标记为**关键点**。我们需要选出最少的点，使得它们可以到达所有关键点。

设关键点的集合为 $S$，若存在 $u, v \in S$，$u$ 可达 $v$，那么将 $v$ 从 $S$ 中删除。

有结论：每个点可以覆盖的存在关键点的列形成连续区间。

证明：不失一般性地，设**从左到右**存在关键点 $u, v, w \in S$，$u$ 可达 $w$，但不可达 $v$。那么 $u$ 必须经过 $v$ 列中的某点 $i$，然后到达 $w$，因为 $v$ 高于 $i$（否则可以到达 $v$），所以 $v$ 可达 $w$，故 $w \notin S$。

那么通过一次 DAG 上 DP 求出所有关键点和每个点对应的区间，对区间左端点排序后贪心即可。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

#define LOG(f...) fprintf(stderr, f)
#define all(cont) begin(cont), end(cont)

using ll = long long;

template<class T> void read(T &x) {
  char ch; x = 0;
  int f = 1;
  while (isspace(ch = getchar()));
  if (ch == '-') ch = getchar(), f = -1;
  do x = x * 10 + (ch - '0'); while(isdigit(ch = getchar()));
  x *= f;
}
template<class T, class ...A> void read(T &x, A&... args) { read(x); read(args...); }

const int N = 400005;

vector<int> pos[N];
char s[N];
int pre_id[N];
int a[N];

int dfn[N], low[N], scc[N], dfc = 0, stk[N], top = 0, scc_cnt;
bool instk[N];
vector<int> G[N], RG[N];
int r_ind[N];
bool key[N], vis[N];
int key_id[N], key_cnt;

struct range {
  int l, r;
  bool operator<(const range &r) const { return l < r.l; }
} ran[N];

void tarjan(int x) {
  dfn[x] = low[x] = ++dfc;
  stk[++top] = x; instk[x] = true;
  for (int v : G[x])
    if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
    else if (instk[v]) low[x] = min(low[x], dfn[v]);
  if (low[x] == dfn[x]) {
    int tp;
    do {
      tp = stk[top--];
      instk[tp] = false;
      scc[tp] = scc_cnt;
    } while (tp != x);
    ++scc_cnt;
  }
}

void scc_dp() {
  vector<int> ord;
  for (int i = 0; i < scc_cnt; ++i)
    if (!r_ind[i]) ord.push_back(i);
  for (int i = 0; i < scc_cnt; ++i) {
    int x = ord[i];
    if (vis[x]) key[x] = false;
    if (key[x]) vis[x] = true;
    for (int v : RG[x]) {
      --r_ind[v];
      if (vis[x] || key[x]) vis[v] = true;
      if (!r_ind[v]) ord.push_back(v);
    }
  }
  for (int i = 0; i < scc_cnt; ++i)
    if (key[i]) key_id[i] = key_cnt++;
  for (auto i = rbegin(ord); i != rend(ord); ++i) {
    int x = *i;
    ran[x].l = key[x] ? key_id[x] : numeric_limits<int>::max();
    ran[x].r = key[x] ? key_id[x] : numeric_limits<int>::min();
    for (int v : RG[x]) {
      ran[x].l = min(ran[x].l, ran[v].l);
      ran[x].r = max(ran[x].r, ran[v].r);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, m;
  read(n, m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    for (int j = 0; j < m; ++j)
      if (s[j] == '#') pos[j].push_back(n - 1 - i);
  }
  for (int i = 0; i < m; ++i)
    read(a[i]);
  for (int i = 0; i < m; ++i)
    reverse(all(pos[i]));
  pre_id[0] = 0;
  for (int i = 1; i <= m; ++i)
    pre_id[i] = pre_id[i - 1] + pos[i - 1].size();
  for (int i = 0; i < m; ++i)
    for (auto it = begin(pos[i]); it != end(pos[i]); ++it) {
      int id = pre_id[i] + (it - begin(pos[i]));
      if (it != begin(pos[i])) G[id].push_back(id - 1);
      if (next(it) != end(pos[i]) && it[1] == *it + 1) G[id].push_back(id + 1);
      if (i != 0) {
        auto t = upper_bound(all(pos[i - 1]), *it);
        if (t != begin(pos[i - 1])) G[id].push_back(pre_id[i - 1] - 1 + (t - begin(pos[i - 1])));
      }
      if (i + 1 != m) {
        auto t = upper_bound(all(pos[i + 1]), *it);
        if (t != begin(pos[i + 1])) G[id].push_back(pre_id[i + 1] - 1 + (t - begin(pos[i + 1])));
      }
    }
  int nc = pre_id[m];
  for (int i = 0; i < nc; ++i)
    if (!dfn[i]) tarjan(i);
  for (int i = 0; i < m; ++i)
    if (a[i])
      key[scc[pre_id[i] + a[i] - 1]] = true;
  for (int i = 0; i < nc; ++i)
    for (int v : G[i])
      if (scc[i] != scc[v]) RG[scc[i]].push_back(scc[v]), ++r_ind[scc[v]];
  scc_dp();
  sort(ran, ran + scc_cnt);
  int max_r = -1, nmax_r = 0, res = 0;
  for (int i = 0; i < scc_cnt && max_r + 1 < key_cnt; ++i) {
    nmax_r = max(nmax_r, ran[i].r);
    if (i + 1 == scc_cnt || ran[i + 1].l > max_r + 1)
      ++res, max_r = nmax_r;
  }
  printf("%d\n", res);
  return 0;
}
```



---

## 作者：gyh20 (赞：6)

如果您没有看过 F1 的题解，建议先看一看 -> [link](https://www.luogu.com.cn/blog/gyh20/solution-cf1534f1)

先从一些显而易见的结论开始：

$1.$ 如果某一个沙掉落，那么下面的所有沙掉落。

也就是说，只需要第 $a_i$ 个沙掉下来即可。

令每一列前 $a_i$ 个点为 $A$ 类点，其余点为 $B$ 类点。

$2.$ 假设只看 $A$ 类点，我们只用管缩点之后的 $0$ 度点（像 F1 一样求）。

这些 $0$ 度点必须被扰动，而扰动之后所有点都会被扰动。

也就是说，我们只需要管这些 $0$ 度点与 $B$ 类点构成的图。

$3.$ 每一列的 $0$ 度点至多只有 $1$ 个。

$4.$ 所有的 $A$ 类点都在同列的 $B$ 类点下方。

此时，我们可以再次建图，求出每个 $B$ 类点能影响到的所有 $0$ 度点，然后就转成了 DAG 上的奇怪问题， $n\leq 4\times 10^5$ 时完全无法解决。

当感觉一个问题不可做时，可以检查一下自己转化问题的时候是不是漏了什么性质。

每个 $B$ 类点影响的 $0$ 度点到底是什么样的？

先给出结论：一段区间！

证明：如果第 $i$ 列的 $B$ 类点影响了第 $x(x>i)$ 列的 $0$ 度点，由于我们初始的连边只有 $i$ 向 $[i-1,i+1]$ 的点连边，那么在中途 $i<k<x$ 所有第 $k$ 列中且在两点纵坐标之间的点一定存在。

那么对于中间的每一列，这个纵坐标的点一定为 $B$ 类点，否则，若第 $x$ 列的那个点为 $A$ 类点，而根据最开始连边的定义，$0$ 度点是 $A$ 类点缩点之后入度为 $0$ 的点，也就是说，不可能存在其它的 $A$ 类点可达，而这个 $B$ 类点一定会影响下面的 $0$ 度点。

于是，这个问题就转为了线段覆盖的经典问题。

代码还没写，先咕着。


---

## 作者：Sky_Maths (赞：5)

# 前言

这道题题解共有两种写法，分别是缩点和深搜，我认为后一种更好写且更易理解，代码也比较清楚，但该类型的题解比较少，故讲解后一种做法。

当中引用了一些 AsunderSquall 的命名方法，故可以将本题解认为是对其的补充？

# 内容
首先，给出结论，存在一种最优解法，最后选择的节点一定都是最上面的点（因为上面的点一定可以带动下面，可以用调整法证明）。

我们称第 $j$ 列从下向上第 $a_j$ 个点为关键点，每一列的第一个点为起始点。

对于每个关键点，求出最左能覆盖它的起始点在哪一列 $L_j$，最右能覆盖它的起始点在哪一列 $R_j$，我们**可以认为**在 $L_j$ 与 $R_j$ 中只要任选一个起始点，就可以使第 $j$ 个关键点被影响。

这里说明一下，可能有人会想，如果在 $L_j$ 与 $j$ 中（$R_j$ 同理）存在一列 $k$，$L_j$ 可以影响 $j$ 但 $k$ 不能影响 $j$ 的话，最后若选择 $k$ 岂不是 $j$ 就不会被影响了？

是的，最后若选择 $k$，第 $j$ 个关键点就不会被影响，但是——我们想一下上述情况中三者的关系。发现 $L_j$ 可以影响 $j$ 但 $k$ 不能影响 $j$，故 $L_j$ 应该是从 $k$ 的上方连接 $j$ 的，否则 $k$ 下坠会影响该“桥梁”，也就是说 $L_j$ 必定可以影响 $k$。那么选 $L_j$ 一定不会比选 $k$ 劣，因为 $L_j$ 所能影响的点已经包含了 $k$，即 $k$ 一定不在答案中。

于是最后题目就变成了，给定 $n$ 个区间 $[l,r]$ ，其中 $1\le l\le r\le n$ 要求选择一些点，使每个区间 $[l,r]$ 中都有至少一个点被选择，问最少选择几个点。

可以贪心，即将区间按照右端点排序，若当前区间中已有点被选择就不用管可以跳过，否则在答案中加入当前区间的右端点。

# 代码
```cpp
#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##end(r);i<=i##end;++i)
#define per(i,r,l) for(int i(r),i##end(l);i>=i##end;--i)
using namespace std;
typedef pair<int,int> pii;
const int N = 4e5 + 9;
int n,m,ans,now;
int a[N],l[N],r[N],L[N],R[N];
char ch[N];
set<pii>st;
int h(int i,int j) {
    return (i-1)*m+j;
}
void dfsl(int i,int j,int k) {
    if(l[h(i,j)]!=-1) return;
    l[h(i,j)]=k;
    if(i<n) dfsl(i+1,j,k);
    if(i>1&&ch[h(i-1,j)]=='#') dfsl(i-1,j,k);
    if(j>1&&ch[h(i,j-1)]=='#') dfsl(i,j-1,k);
    if(j<m&&ch[h(i,j+1)]=='#') dfsl(i,j+1,k);
}
void dfsr(int i,int j,int k) {
    if(r[h(i,j)]!=-1) return;
    r[h(i,j)]=k;
    if(i<n) dfsr(i+1,j,k);
    if(i>1&&ch[h(i-1,j)]=='#') dfsr(i-1,j,k);
    if(j>1&&ch[h(i,j-1)]=='#') dfsr(i,j-1,k);
    if(j<m&&ch[h(i,j+1)]=='#') dfsr(i,j+1,k);
}
int main() {
    scanf("%d%d",&n,&m);
    rep(i,1,n) {
        rep(j,1,m) {
            scanf(" %c",&ch[h(i,j)]);
        }
    }
    rep(i,1,m) scanf("%d",&a[i]);
    memset(l,-1,sizeof(l));
    memset(r,-1,sizeof(r));
    rep(j,1,m) rep(i,1,n) 
        if(ch[h(i,j)]=='#') dfsl(i,j,j);
    per(j,m,1) rep(i,1,n) 
        if(ch[h(i,j)]=='#') dfsr(i,j,j);
    rep(j,1,m) {
        if(a[j]){
            per(i,n,1) {
                if(ch[h(i,j)]=='#') {
                    a[j]--;
                    if(a[j]==0) {
                        L[j]=l[h(i,j)];
                        R[j]=r[h(i,j)];
                        break;
                    }
                }
            }
        }
    }
    rep(j,1,m) {
        if(L[j]!=0) {
            st.insert(make_pair(R[j],L[j]));
        }
    }
    while(true) {
        if(st.empty()) break;
        pii top=*st.begin();
        st.erase(st.begin());
        if(now<top.second) {
            ++ans;
            now=top.first;
        }
    }
    printf("%d\n",ans);
    return 0;

```

---

## 作者：The_Godfather (赞：1)

## Problem
[题目传送门](https://www.luogu.com.cn/problem/CF1534F2)
## Solution
- 初拿到题我们先考虑对于 $(i,j)$ 向上下左右连出的有向边，缩点后答案就是 $in\lbrack i \rbrack$ 为0的个数。
- 其次我们对该问题有两个技巧：

1. 对于这个图，我们只需要让第 $i$ 行第 $a\lbrack i \rbrack$ 块掉下，将其标记。
2. 观察到图的特征是仅向相邻的列连边，所以猜测选取某一个点消除的影响是 $\lbrack l , r \rbrack$。

- 如果特殊点 $X$ 可以到 $Y$ 的话，我们将 $Y$ 删掉，因为只需要得到 $X$ 即可。这样将剩下的点按从左到右的顺序重新编号，可以证明选取图中某一节点，会覆盖新编号节点中的一段连续区间。这样在缩点后的 dag 上 dp，只需要记录最左和最右节点，做一次区间覆盖即可。

## Code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define PII pair<int, int>
#define All(x) x.begin(), x.end()
#define INF 0x3f3f3f3f
using namespace std;
const int mx = 4e5 + 5;
int n, m, cnt, low[mx], dfn[mx], num, bl, c[mx], vis[mx], in[mx], a[mx], b[mx], l[mx], r[mx], siz, marked[mx], idx;
PII d[mx];
queue<int> q;
stack<int> st;
set<PII> s[mx];
vector<PII> s2[mx];
vector<PII> v, e;
vector<int> sp;
vector<int> g[mx], g2[mx];
void tarjan(int x)
{
    low[x] = dfn[x] = ++num;
    vis[x] = 1, st.push(x);
    for (auto y : g[x])
    {
        if (!dfn[y])
        {
            tarjan(y), low[x] = min(low[x], low[y]);
        }
        else if (vis[y])
        {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (dfn[x] == low[x])
    {
        int tmp = 0;
        bl++;
        do
        {
            tmp = st.top();
            st.pop();
            c[tmp] = bl, vis[tmp] = 0;
        } while (tmp != x);
    }
}
void dfs(int x)
{
    if (marked[x])
        return;
    marked[x] = 1;
    for (auto y : g2[x])
    {
        dfs(y);
    }
}
int main()
{
    cin >> n >> m;
    memset(l, INF, sizeof(l));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char c;
            cin >> c;
            if (c == '#')
            {
                s2[j].push_back(make_pair(i, cnt));
                s[j].insert(make_pair(i, cnt++));
                v.push_back(make_pair(i, j));
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        if (!a[i])
            continue;
        b[i] = s2[i][s2[i].size() - a[i]].second;
        sp.push_back(b[i]);
    }
    for (int i = 0; i < cnt; i++)
    {
        int x = v[i].fi, y = v[i].se;
        auto it = s[y].upper_bound(make_pair(x, INF));
        if (it != s[y].end())
        {
            e.push_back(make_pair(i, it->second));
            g[i].push_back(it->second);
        }
        it = s[y - 1].lower_bound(make_pair(x, 0));
        if (it != s[y - 1].end())
        {
            e.push_back(make_pair(i, it->second));
            g[i].push_back(it->second);
        }
        it = s[y + 1].lower_bound(make_pair(x, 0));
        if (it != s[y + 1].end())
        {
            e.push_back(make_pair(i, it->second));
            g[i].push_back(it->second);
        }
        it = s[y].lower_bound(make_pair(x, 0));
        if (it-- != s[y].begin() && it->first + 1 == x)
        {
            e.push_back(make_pair(i, it->second));
            g[i].push_back(it->second);
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 0; i < e.size(); i++)
    {
        int x = e[i].fi, y = e[i].se;
        x = c[x], y = c[y];
        if (x != y)
        {
            g2[x].push_back(y);
        }
    }
    for (int i = 0; i < sp.size(); i++)
    {
        int x = sp[i];
        x = c[x];
        for (auto y : g2[x])
        {
            dfs(y);
        }
    }
    for (int i = 1; i <= bl; i++)
        g2[i].clear();
    for (int i = 0; i < sp.size(); i++)
    {
        int x = sp[i];
        x = c[x];
        if (marked[x])
            continue;
        idx++; // 重新编号
        l[x] = min(l[x], idx);
        r[x] = max(r[x], idx);
    }
    for (int i = 0; i < e.size(); i++)
    {
        int x = e[i].fi, y = e[i].se;
        x = c[x], y = c[y];
        if (x != y)
        {
            g2[y].push_back(x);
            in[x]++;
        }
    }
    for (int i = 1; i <= bl; i++)
    {
        if (!in[i])
        {
            q.push(i);
        }
    }
    while (q.size())
    {
        int x = q.front();
        q.pop();
        for (auto y : g2[x])
        {
            l[y] = min(l[y], l[x]);
            r[y] = max(r[y], r[x]);
            if (--in[y] == 0)
                q.push(y);
        }
        if (!g2[x].size() && l[x] <= r[x])
        {
            d[++siz] = make_pair(l[x], r[x]);
        }
    }
    sort(d + 1, d + 1 + siz);
    int res(0), Max(1), p(1);
    while (Max <= idx)
    {
        int R(0);
        while (p <= siz && d[p].fi <= Max)
            R = max(R, d[p].se), p++;
        res++, Max = R + 1;
    }
    cout << res;
}

```

---

## 作者：int08 (赞：0)

## 前言

警告：这个做法是乱搞，正确性没有保证，谨慎食用。

但是 CF 上过了，而且应该挺难卡的。

## 题意

原题目题意清楚~~因为题目沙子的掉落逻辑就是 Minecraft 里沙子的掉落逻辑。~~

### part 1

首先有一个大家都能发现的事实：掉落的沙子必然是每一列最下面的一些，因为上面的沙子掉落会把它正下方所有都带着一起掉，所以我们显然可以确定每一列要完成任务至少要掉到哪个。

同时每一列某个沙子掉落会带动相邻列低于等于它的所有沙子一起掉，所以有结论一：相邻两个任务完成高的就必然直接完成低的。

于是高的往低的建边就行了？并不是。

因为我们发现有些时候下面掉了还可以传动到上面去！具体情况：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F2/a5e473b6fa07dabecf94f6cfb85782199edfaea0.png)

第一列最下面那个掉了之后会把上面两个也拉走，高度就提升了。

于是我们需要关注 $dp_{i,j}$ 为第 $i$ 行 $j$ 列的沙子掉了之后能传动到的本列最高的沙子。

是“上下连起来就能传上去，否则不能”吗？不是，比如说下面这个例子：

```
###
#..
###
..#
###
```
对于中间一列最下面的，尽管与上面不相连，却通过左右两侧带上去了。

于是设 $dp1_{i,j,0/1}$ 分别表示从左、右侧能到达的本列最高的沙子，有转移方程：

$$dp1_{i,j,0}=\max(i,pre_{dp_{i,j-1,0},j})$$

其中 $pre_{i,j}$ 表示第 $j$ 列下面 $i$ 行里最高的沙子。

为了便于向上传递，把一些上下相连的沙子高度都标为最顶上那个。

于是我们可以通过 $dp1$ 数组推出需要的 $dp$ 数组了：

$$dp_{i,j}=dp_{\max(dp_{i,j,0},dp_{i,j,1}),j}$$

（注意 $i$ 从上往下枚举）

很遗憾这个是假的，hack：


```
#####..
#......
###....
..#....
###...#
#...##.
####...
```

注意观察，由于第 $7$ 行第 $4$ 列的沙子需要左右两个方向的转移才能得出正确答案，导致 $dp_{6,5}$ 错了，没有探测到上面。

咋办？我提出一个乱搞：接着用相邻两侧的 $dp$ 数组再更新本列的 $dp$ 数组，多做几次总能传过去的。

这个明显拆东墙补西墙，不过它通过了，而且估计比较难 hack。

### part 2
那现在~~假设~~我们已经获得了正确的 $dp$ 数组了，然后呢？

我们猜测点某一个沙子（显然是每列最高的沙子）能完成任务的列应该是包含本身的一段区间，如果是的话，就是一个简单的区间覆盖问题了。

但是并不是：

```
.#.
#..
###

```
发现如果点了第三个列的沙子，能完成 $1,3$ 两列的任务。

但是有最重要的结论二：**点某一个沙子能完成的任务，有用的部分只有这段区间。**

为啥？以上面为例：

```
√×√
```

由于第一列任务完成了而第二列没有，推断出第一列不能带动第二列完成，由结论一：第二列必然可以带动第一列完成！

那么区间外面被隔开的点没有意义，就不用管了。

现在只需要处理点某一个沙子能带动的区间，不算很难，跑一个和 $dp1$ 相似的东西就好了。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 404404
vector<int> a[N],pmx[N],dp1l[N],dp1r[N],dp2[N],dp3l[N],dp3r[N];
int n,m,i,j,b[N],req[N],tag,tr[N],ans;
char op;
int main()
{
	cin>>n>>m;
	for(i=0;i<=m+5;i++) a[i].resize(n+5),pmx[i].resize(n+5),dp1l[i].resize(n+5),dp1r[i].resize(n+5),dp2[i].resize(n+5),dp3l[i].resize(n+5),dp3r[i].resize(n+5);  
	for(i=n;i>=1;i--)
		for(j=1;j<=m;j++)
		{
			cin>>op;
			if(op=='#') a[j][i]=max(a[j][i+1],i);
		}
	for(j=1;j<=m;j++)
	{
		cin>>b[j];tag+=b[j];
		for(i=1;i<=n;i++) pmx[j][i]=max(pmx[j][i-1],a[j][i]);
		for(i=1;i<=n;i++) if(a[j][i]&&!--b[j]) req[j]=i;
	}
	if(!tag) cout<<0,exit(0);
	for(i=1;i<=n;i++) if(a[1][i]==i) dp1l[1][i]=i;
	for(j=2;j<=m;j++)
		for(i=1;i<=n;i++)
			if(a[j][i]==i) dp1l[j][i]=max(i,pmx[j][dp1l[j-1][pmx[j-1][i]]]);
	for(i=1;i<=n;i++) if(a[m][i]==i) dp1r[m][i]=i;
	for(j=m-1;j>=1;j--)
		for(i=1;i<=n;i++)
			if(a[j][i]==i) dp1r[j][i]=max(i,pmx[j][dp1r[j+1][pmx[j+1][i]]]);
	for(j=1;j<=m;j++)
		for(i=n;i>=1;i--) if(a[j][i]==i) dp2[j][i]=max(i,dp2[j][max(dp1l[j][i],dp1r[j][i])]);
	for(j=2;j<=m;j++)
		for(i=1;i<=n;i++)
			if(a[j][i]==i) dp2[j][i]=max(dp2[j][i],pmx[j][dp2[j-1][pmx[j-1][i]]]);
	for(j=m-1;j>=1;j--)
		for(i=1;i<=n;i++)
			if(a[j][i]==i) dp2[j][i]=max(dp2[j][i],pmx[j][dp2[j+1][pmx[j+1][i]]]);
	for(i=0;i<=n;i++)
	{
		if(i>=req[1]) dp3l[1][i]=1;
		else dp3l[1][i]=m+1;
	}
	for(j=2;j<=m;j++)
		for(i=0;i<=n;i++)
		{
			if(i>=req[j]) dp3l[j][i]=min(j,dp3l[j-1][dp2[j-1][pmx[j-1][dp2[j][i]]]]);
			else dp3l[j][i]=m+1;
		}
	for(i=0;i<=n;i++)
		if(i>=req[m]) dp3r[m][i]=m;
	for(j=m-1;j>=1;j--)
		for(i=0;i<=n;i++)
			if(i>=req[j]) dp3r[j][i]=max(j,dp3r[j+1][dp2[j+1][pmx[j+1][dp2[j][i]]]]);
	for(i=1;i<=m;i++) tr[dp3l[i][pmx[i][n]]-1]=max(dp3r[i][pmx[i][n]],tr[dp3l[i][pmx[i][n]]-1]);
	for(i=1;i<m;i++) tr[i]=max(tr[i],tr[i-1]);
	int prs=0;
	while(prs<m) ans++,prs=tr[prs];
	cout<<ans;
}
```
# The End.

---

## 作者：_ANIG_ (赞：0)

先建图，如果 $i$ 能击落 $j$，则 $i$ 可以到达 $j$。

如果任意两个都连边，边数可能很大。由于一列中上面的一定可以击落下面的，所以每一列只需要连能击落的最靠上的即可。

然后缩点变成 DAG。

转化一下题意，可以发现第 $i$ 列至少击落 $a_i$ 个，当且仅当第 $i$ 列从下往上数第 $a_i$ 个被击落。

这样就从击落一定数量转化为了击落一个点。

可以发现入度为 $0$ 的点对应的列构成的集合是不会相交的，并且有单调性，所以可以直接按这些点对应的列的编号排序。

这样，能到达点 $i$ 的所有入度为 $0$ 的点的编号是一个区间。

拓扑排序一次求出所有点的这样的区间，问题变成选若干个点，使得每个区间都有至少一个点被选。

按左端点排序，维护一个指针 $pos$ 表示上一个选的点在哪，如果当前的 $l\le pos$，则令 $pos=\min(pos,r)$，否则令 $pos=r$，并且答案加一。

附上写的很烂的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5;
int n,m,sl[N],dfn[N],low[N],idx,mk[N],cnt,bhs[N],dx[N],dy[N],rd[N],res,lst[N],root[N],sm[N],nd[N],ls[N],rs[N];
vector<vector<int> >w,bh;
vector<int>emp,p[N],e[N],hs[N],rt,xy;
stack<int>q;
map<pair<int,int>,bool>mks;
vector<pair<int,int> >ps;
void dfs(int x){
    q.push(x);
    dfn[x]=low[x]=++idx;mk[x]=1;
    for(int i=0;i<p[x].size();i++){
        int c=p[x][i];
        if(!dfn[c]){
            dfs(c);
            low[x]=min(low[x],low[c]);
        }else if(mk[c])low[x]=min(low[x],dfn[c]);
    }
    if(low[x]==dfn[x]){
        int y;cnt++;
        do{
            y=q.top();q.pop();mk[y]=0;bhs[y]=cnt;
            if(w[dx[y]][dy[y]])hs[cnt].push_back(dy[y]);
        }while(y!=x);
        root[cnt]=x;
    }
}
bool cmp(int a,int b){
    return dy[root[a]]<dy[root[b]];
}
deque<int>qs;
signed main(){
    cin>>n>>m;
    w.push_back(emp);
    bh.push_back(emp);
    w[0].resize(m+1);
    for(int i=1;i<=n;i++){
        w.push_back(emp);
        w[i].push_back(0);
        bh.push_back(emp);
        bh[i].push_back(0);
        for(int j=1;j<=m;j++){
            char c;
            scanf(" %c",&c);
            w[i].push_back(c=='#');
            bh[i].push_back((i-1)*m+j);
            dx[bh[i][j]]=i,dy[bh[i][j]]=j;
        }
    }
    for(int i=1;i<=m;i++)scanf("%lld",&nd[i]);
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++)if(w[i][j])lst[j]=sl[j],sl[j]=bh[i][j],sm[j]++;
        for(int j=1;j<=m;j++){
            if(!w[i][j])continue;
            if(sl[j-1])p[bh[i][j]].push_back(sl[j-1]);
            if(sl[j+1])p[bh[i][j]].push_back(sl[j+1]);
            if(lst[j])p[bh[i][j]].push_back(lst[j]);
            if(w[i-1][j])p[bh[i][j]].push_back(bh[i-1][j]);
            if(sm[j]==nd[j]){
                xy.push_back(bh[i][j]);
            }
        }
    }
    for(int i=1;i<=n*m;i++)if(!dfn[i])dfs(i);
    for(int i=1;i<=n*m;i++){
        for(int j=0;j<p[i].size();j++){
            int c=p[i][j];
            if(bhs[i]==bhs[c])continue;
            if(mks[make_pair(bhs[i],bhs[c])])continue;
            mks[make_pair(bhs[i],bhs[c])]=1;
            e[bhs[i]].push_back(bhs[c]);
            rd[bhs[c]]++;
        }
    }
    memset(ls,0x3f,sizeof(ls));
    for(int i=1;i<=cnt;i++)if(rd[i]==0&&hs[i].size())rt.push_back(i),qs.push_back(i);
    sort(rt.begin(),rt.end(),cmp);
    for(int i=0;i<rt.size();i++)ls[rt[i]]=rs[rt[i]]=i+1;
    while(qs.size()){
        int qq=qs.front();
        qs.pop_front();
        for(int i=0;i<e[qq].size();i++){
            int c=e[qq][i];
            rd[c]--;
            ls[c]=min(ls[c],ls[qq]),rs[c]=max(rs[c],rs[qq]);
            if(rd[c]==0)qs.push_back(c);
        }
    }
    for(int i=0;i<xy.size();i++)ps.push_back(make_pair(ls[bhs[xy[i]]],rs[bhs[xy[i]]]));
    sort(ps.begin(),ps.end());
    int nw=0;
    for(int i=0;i<ps.size();i++){
        int l=ps[i].first,r=ps[i].second;
        if(nw>=l)nw=min(nw,r);
        else res++,nw=r;
    }
    cout<<res;
}
```


---

