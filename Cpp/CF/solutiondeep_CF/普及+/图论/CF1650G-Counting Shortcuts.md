# 题目信息

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2```

### 输出

```
2
4
1
11```

# AI分析结果

### 题目翻译
## 计算捷径数量

### 题目描述
给定一个具有 $n$ 个顶点和 $m$ 条边的无向连通图。该图不包含自环（从一个顶点到自身的边）和重边（即每对顶点之间最多只有一条边）。图的顶点编号从 $1$ 到 $n$。

找出从顶点 $s$ 到顶点 $t$ 的路径数量，这些路径的长度与从 $s$ 到 $t$ 的最短路径长度相差不超过 $1$。需要考虑所有合适的路径，即使它们多次经过相同的顶点或边（即它们不是简单路径）。

![由 6 个顶点和 8 条边组成的图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)

例如，设 $n = 6$，$m = 8$，$s = 6$，$t = 1$，且图如上所示。那么从 $s$ 到 $t$ 的最短路径长度为 $1$。考虑所有长度至多为 $1 + 1 = 2$ 的路径：
- $6 \rightarrow 1$，路径长度为 $1$。
- $6 \rightarrow 4 \rightarrow 1$，路径长度为 $2$。
- $6 \rightarrow 2 \rightarrow 1$，路径长度为 $2$。
- $6 \rightarrow 5 \rightarrow 1$，路径长度为 $2$。

总共有 $4$ 条符合条件的路径。

### 样例 #1
#### 输入
```
4
4 4
1 4
1 2
3 4
2 3
2 4
6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6
5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4
8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2
```

#### 输出
```
2
4
1
11
```

### 综合分析与结论
这些题解主要围绕寻找从顶点 $s$ 到顶点 $t$ 且长度与最短路相差不超过 1 的路径数量展开。思路大致可分为两类：一是通过分层图结合 BFS 或 Dijkstra 算法，计算经过层内边的路径数量；二是使用动态规划（DP）的方法，定义状态并根据最短路信息进行状态转移。

### 所选题解
- **作者：StudyingFather（5星）**
    - **关键亮点**：思路清晰，通过对图分层，明确层间边和层内边的性质，利用 BFS 求出最短路径和最短路径数，再枚举层内边计算满足条件的路径数量，代码实现简洁易懂。
    - **核心代码**：
```cpp
void bfs(int s, int* dis, int* f) {
  queue<int> q;
  memset(dis, -1, sizeof(int) * (n + 1));
  memset(f, 0, sizeof(int) * (n + 1));
  dis[s] = 0, f[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : e[u])
      if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        f[v] = f[u];
        q.push(v);
      } else if (dis[v] == dis[u] + 1)
        f[v] = (f[v] + f[u]) % mod;
  }
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    //...
    bfs(s, dis1, f1);
    bfs(t, dis2, f2);
    long long ans = f1[t];
    for (int i = 1; i <= m; i++) {
      int u = ed[i].first, v = ed[i].second;
      if (dis1[u] == dis1[v]) {
        if (dis1[u] + dis2[v] == dis1[t])
          ans = (ans + 1ll * f1[u] * f2[v]) % mod;
        if (dis1[v] + dis2[u] == dis1[t])
          ans = (ans + 1ll * f1[v] * f2[u]) % mod;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
```
    - **核心思想**：`bfs` 函数用于从起点 $s$ 出发，计算到各点的最短距离 `dis` 和最短路径数 `f`。在 `main` 函数中，分别从 $s$ 和 $t$ 进行 BFS，然后枚举所有边，若为层内边且满足路径长度条件，则更新答案。

- **作者：AmamiyaYuuko（4星）**
    - **关键亮点**：使用 Dijkstra 算法求出最短路，结合记忆化搜索实现动态规划，状态转移方程明确，代码简洁。
    - **核心代码**：
```cpp
void dijkstra() {
    for (int i = 1; i <= n; ++i)    d[i] = 2e9;
    d[s] = 0;
    std::priority_queue<Node> q;
    q.push((Node){s, 0});
    while (!q.empty()) {
        Node now = q.top();
        q.pop();
        if (vis[now.pos])    continue;
        vis[now.pos] = true;
        for (auto i : g[now.pos]) {
            if (d[i] > d[now.pos] + 1) {
                d[i] = d[now.pos] + 1;
                q.push((Node){i, d[i]});
            }
        }
    }
}

LL dp(int x, int k) {
    if (~f[x][k])    return f[x][k];
    LL s = 0;
    for (auto i : g[x]) {
        if (d[i] + 1 == d[x])    s += dp(i, k), s %= mod;
        else if (d[i] == d[x] && k == 1)    s += dp(i, k - 1), s %= mod;
    }
    return f[x][k] = s;
}
```
    - **核心思想**：`dijkstra` 函数用于求出从 $s$ 到各点的最短路。`dp` 函数为记忆化搜索，根据状态转移方程计算在点 $x$ 与最短路相差 $k$ 的方案数。

- **作者：daniEl_lElE（4星）**
    - **关键亮点**：通过 BFS 对图按最短距离分层，在分层过程中进行动态规划状态转移，思路直观，代码实现较为清晰。
    - **核心代码**：
```cpp
queue<int> q;
q.push(s);
f[s][0]=1;
minv[s]=0;
while(!q.empty()){
    int lev=minv[q.front()];
    queue<int> sq;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        sq.push(u);
        for(auto v:g[u]){
            if(minv[v]==minv[u]){
                f[v][1]=(f[v][1]+f[u][0])%mod;
            }
        }
    }
    while(!sq.empty()){
        int u=sq.front();
        sq.pop();
        for(auto v:g[u]){
            if(minv[v]==1e18){
                minv[v]=minv[u]+1;
                f[v][0]=f[u][0];
                f[v][1]=f[u][1];
                q.push(v);
            }
            else if(minv[v]==minv[u]+1){
                f[v][0]+=f[u][0];
                f[v][1]+=f[u][1];
            }
            f[v][0]%=mod;
            f[v][1]%=mod;
        }
    }
}
```
    - **核心思想**：使用 BFS 对图进行分层，在每一层中，先处理同层节点之间的状态转移，再处理到下一层节点的状态转移。

### 最优关键思路或技巧
- 对图进行分层，明确层间边和层内边的性质，利用层内边来寻找比最短路长 1 的路径。
- 使用动态规划，定义合适的状态和状态转移方程，结合记忆化搜索或分层处理避免重复计算。

### 拓展思路
同类型题目可能会改变图的类型（如有向图、带权图）、路径长度的限制条件（如相差不超过 2 等）。类似算法套路包括分层图、多源最短路、动态规划与图论的结合等。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：考察最短路计数，与本题计算最短路径数的思路相关。
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：基础的单源最短路问题，可作为本题 Dijkstra 或 BFS 部分的练习。
- [P2850 [USACO06DEC]River Hopscotch S](https://www.luogu.com.cn/problem/P2850)：涉及路径选择和距离限制，与本题寻找满足特定长度条件的路径有一定相似性。

### 个人心得摘录与总结
- **作者：char_phi**：最初使用 `dfs` 实现动态规划转移时，由于重复转移导致结果错误，通过清空 `dp` 值或按 `dis` 分层处理解决了重复转移问题，但 `dfs` 常数大，最终采用分层转移的方法。总结：在动态规划转移时要注意避免重复转移，同时要考虑算法的时间复杂度。
- **作者：daniEl_lElE**：赛时忘记在最后结果相加后取模。总结：在涉及取模运算的题目中，要注意在所有可能溢出的地方进行取模，特别是最终结果。 

---
处理用时：55.31秒