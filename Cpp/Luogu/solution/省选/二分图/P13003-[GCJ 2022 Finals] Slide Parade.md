# [GCJ 2022 Finals] Slide Parade

## 题目描述

**Gooli** 是一家巨型公司，在一个丘陵地区拥有 $\mathbf{B}$ 栋编号为 1 到 $\mathbf{B}$ 的建筑。六年前，Gooli 修建了滑梯，允许员工从一栋建筑滑向另一栋建筑。每个滑梯只能从其出发建筑滑向目标建筑，而不能反向滑行。Gooli 的 CEO 对公司的滑梯系统非常自豪，并希望组织一场滑梯游戏。她将设计路线的任务交给了 **Melek**——Gooli 的交通主管兼解题爱好者。

![](https://cdn.luogu.com.cn/upload/image_hosting/njzcunb7.png)

CEO 对路线提出了以下要求：

* 路线必须从建筑 1（她的办公室所在地）出发并最终回到建筑 1。
* 每栋建筑的访问次数必须相同。起点位于建筑 1 不算作对建筑 1 的一次访问。
* 每条滑梯必须至少被使用一次。
* 路线长度不超过 $10^6$ 步。

给定建筑和滑梯的布局，帮助 Melek 找到一条满足 CEO 所有要求的路线（如果存在）。

## 说明/提示

**样例解释**

在样例 #1 中，另一条可接受的路线是从建筑 1 滑到建筑 2 再返回，总步数为 2 步。

![](https://cdn.luogu.com.cn/upload/image_hosting/udzlxptm.png)

在样例 #2 中，没有滑梯通向建筑 1，因此不存在有效路线。

![](https://cdn.luogu.com.cn/upload/image_hosting/pp27u0fj.png)

在样例 #3 中，样例输出展示的路线使每栋建筑被访问两次。

![](https://cdn.luogu.com.cn/upload/image_hosting/e7pjon34.png)

样例 #4 如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ff4gi295.png)

样例 #5 是题目描述中图示的案例。在样例输出的路线中，从 2 到 3 和从 4 到 1 的滑梯被使用了两次，其余滑梯各使用一次。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{U}_i \leq \mathbf{B}$，对所有 $i$。
- $1 \leq \mathbf{V}_i \leq \mathbf{B}$，对所有 $i$。
- $\mathbf{U}_i \neq \mathbf{V}_i$，对所有 $i$。
- $(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{U}_j, \mathbf{V}_j)$，对所有 $i \neq j$。

**测试集 1（11 分，可见判定）**

- 时间限制：10 秒。
- $2 \leq \mathbf{B} \leq 10$。
- $2 \leq \mathbf{S} \leq 10$。

**测试集 2（24 分，隐藏判定）**

- 时间限制：20 秒。
- $2 \leq \mathbf{B} \leq 200$。
- $2 \leq \mathbf{S} \leq 5000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 2
2 1
1 2
3 4
2 3
1 2
3 2
1 3
3 6
1 2
1 3
2 1
2 3
3 1
3 2
3 4
1 2
2 1
1 3
3 1
4 6
1 2
1 4
2 3
3 2
3 4
4 1```

### 输出

```
Case #1: 7
1 2 1 2 1 2 1
Case #2: IMPOSSIBLE
Case #3: 7
1 2 3 1 3 2 1
Case #4: IMPOSSIBLE
Case #5: 9
1 4 1 2 3 2 3 4 1```

# 题解

## 作者：stardust_Ray (赞：0)

我们先判掉不连通的情况，接下来讨论的都是连通图。

考虑如何判断是否有解，我们存在结论：假如我们对于图中的每条边 $u\to v$，在二分图上建边 $u\to v'$，那么一定存在一个包含 $(u, v')$ 的完美匹配。

先证明充分性，如果存在，我们取出完美匹配中的所有边，在新图上连上这些边，那么最终得到的这张图上每个点的入度都等于出度，存在欧拉回路，同时每条边都出现了至少一次。

然后证明必要性，假如有解，那么我们对于答案路径 $ans$，我们在二分图上连边 $ans_i\to ans_{i + 1}'$，那么这是一张 $k$ 正则二分图，所以一定可以划分成 $k$ 个完美匹配，因为每条边都在路径中出现了一次，所以对于每条边都存在包含它的完美匹配。

构造同证明，每次用匈牙利算法退流即可。由于只会有 $nm$ 条边，所以路径长度也是 $nm \le 10^6$ 的。

```cpp
#include <bits/stdc++.h>
#define For(i, j, k) for (int i = (j); i <= (k); ++i)
#define ForDown(i, j, k) for (int i = (j); i >= (k); --i)
#define Debug(fmt, args...) fprintf(stderr, "(func %s, line #%d): " fmt, __func__, __LINE__, ##args), fflush(stderr)
#define debug(fmt, args...) fprintf(stderr, fmt, ##args), fflush(stderr)
#define within :
#define LJY main
using namespace std;
typedef long long ll;
const int N = 205, M = 1e6 + 5;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
inline int read() {
  char ch = getchar(); int x = 0, f = 1;
  while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * f;
}
int n, m, fa[N], u[M], v[M]; int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
vector<int> G[N], F[N]; int ans[M], tot, mat[N], Mat[N]; bool vis[N];
bool dfs(int u) {
  vis[u] = 1; 
  for(int v within G[u]) if(!mat[v]) {mat[v] = u; Mat[u] = v; return 1;}
  for(int v within G[u]) if(!vis[mat[v]] && dfs(mat[v])) {mat[v] = u; Mat[u] = v; return 1;}
  return 0;
}
void euler(int u) {
  while(!F[u].empty()) { int v = F[u].back(); F[u].pop_back(); euler(v);}
  ans[++tot] = u;
}
void ljy(int tc) {
  printf("Case #%d: ", tc);
  n = read(); m = read(); For(i, 1, n) fa[i] = i, G[i].clear(), F[i].clear();
  For(i, 1, m) {
    u[i] = read(), v[i] = read(); G[u[i]].emplace_back(v[i]);
    fa[find(u[i])] = find(v[i]);
  } For(i, 2, n) if(find(i) != find(1)) {puts("IMPOSSIBLE"); return;}
  memset(mat, 0, sizeof(mat)); memset(Mat, 0, sizeof(Mat));
  For(i, 1, n) {memset(vis, 0, sizeof(vis)); if(!dfs(i)) {puts("IMPOSSIBLE"); return;}}
  For(i, 1, m) {
    if(mat[v[i]] != u[i]) {
      int p = mat[v[i]]; mat[v[i]] = u[i]; mat[Mat[u[i]]] = 0; Mat[u[i]] = v[i];
      memset(vis, 0, sizeof(vis)); vis[u[i]] = 1;
      if(!dfs(p)) {puts("IMPOSSIBLE"); return;}
    } For(j, 1, n) F[mat[j]].emplace_back(j);
  } tot = 0; euler(1); reverse(ans + 1, ans + 1 + tot);
  printf("%d\n", tot);
  For(i, 1, tot) printf("%d ", ans[i]); puts("");
}
signed LJY() { int T = read(); For(i, 1, T) ljy(i);}
```

---

