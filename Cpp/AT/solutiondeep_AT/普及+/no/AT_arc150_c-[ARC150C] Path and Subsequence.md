# 题目信息

# [ARC150C] Path and Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc150/tasks/arc150_c

$ N $ 頂点 $ M $ 辺の連結無向グラフ $ G $ があります。頂点には $ 1 $ から $ N $ の番号がついています。$ i $ 番目の辺は頂点 $ U_i,\ V_i $ を結びます。

また、長さ $ N $ の整数列 $ A=(A_1,\ A_2,\ \dots,\ A_N) $ 、および長さ $ K $ の整数列 $ B=(B_1,\ B_2,\ \dots,\ B_K) $ が与えられます。

$ G,\ A,\ B $ が以下の条件を満たすか判定してください。

- $ G $ における頂点 $ 1 $ から $ N $ への任意の単純パス $ v=(v_1,\ v_2,\ \dots,\ v_k)\ (v_1=1,\ v_k=N) $ に対し、$ B $ は $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ の（連続とは限らない）部分列になる。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N $
- $ N-1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_i\ <\ V_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (U_i,\ V_i)\ \neq\ (U_j,\ V_j) $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 入力される値はすべて整数
- 与えられるグラフ $ G $ は連結

### Sample Explanation 1

頂点 $ 1 $ から頂点 $ 6 $ への単純パスは $ (1,\ 2,\ 4,\ 6),\ (1,\ 3,\ 5,\ 6) $ の $ 2 $ 通りであり、これらに対する $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ はそれぞれ $ (1,\ 2,\ 5,\ 6),\ (1,\ 4,\ 2,\ 6) $ です。 これらはいずれも $ B=(1,\ 2,\ 6) $ を部分列に持つので答えは `Yes` です。

### Sample Explanation 2

頂点 $ 1 $ から頂点 $ 5 $ への単純パスである $ (1,\ 2,\ 5) $ に対する $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ は $ (1,\ 2,\ 2) $ であり、これは $ B=(1,\ 3,\ 2) $ を部分列に持ちません。

## 样例 #1

### 输入

```
6 6 3

1 2

1 3

2 4

3 5

4 6

5 6

1 2 4 5 2 6

1 2 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 5 3

1 2

2 3

3 4

4 5

2 5

1 2 3 5 2

1 3 2```

### 输出

```
No```

## 样例 #3

### 输入

```
10 20 3

5 6

5 10

5 7

3 5

3 7

2 6

3 8

4 5

5 8

7 10

1 6

1 9

4 6

1 2

1 4

6 7

4 8

2 5

3 10

6 9

2 5 8 5 1 5 1 1 5 10

2 5 1```

### 输出

```
Yes```

# AI分析结果

### 题目内容重写

【题目描述】

给定一个包含 $N$ 个顶点和 $M$ 条边的连通无向图 $G$。顶点编号从 $1$ 到 $N$。第 $i$ 条边连接顶点 $U_i$ 和 $V_i$。

此外，给定一个长度为 $N$ 的整数序列 $A=(A_1, A_2, \dots, A_N)$，以及一个长度为 $K$ 的整数序列 $B=(B_1, B_2, \dots, B_K)$。

请判断 $G$、$A$、$B$ 是否满足以下条件：

- 对于 $G$ 中从顶点 $1$ 到 $N$ 的任意简单路径 $v=(v_1, v_2, \dots, v_k)\ (v_1=1, v_k=N)$，$B$ 是 $(A_{v_1}, A_{v_2}, \dots, A_{v_k})$ 的（不一定连续的）子序列。

### 算法分类
最短路

### 题解分析与结论

题目要求判断从顶点 $1$ 到 $N$ 的所有简单路径中，路径上的点权序列是否都包含 $B$ 作为子序列。核心思路是将问题转化为求从 $1$ 到 $N$ 的路径中，与 $B$ 匹配最少的路径的匹配数量。如果这个最小匹配数量等于 $K$，则输出 `Yes`，否则输出 `No`。

各题解的主要思路是通过 Dijkstra 或 0-1 BFS 来计算每个顶点 $u$ 的最小匹配数量 $dis_u$，并在遍历过程中更新 $dis_v$。难点在于如何将匹配问题转化为最短路问题，并确保算法的正确性和效率。

### 所选高星题解

#### 题解1：do_while_true (4星)
**关键亮点**：
- 使用 Dijkstra 算法计算每个顶点的最小匹配数量。
- 通过优先队列优化，确保时间复杂度为 $O(N\log N + M + K)$。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
dis[1] = a[1] == b[1];
priority_queue<pii, vector<pii>, greater<pii>> q;
q.push(mp(dis[1], 1));
while (!q.empty()) {
    int x = q.top().se; q.pop();
    if (vis[x]) continue;
    vis[x] = 1;
    for (auto v : eg[x]) {
        int w = dis[x] + (a[v] == b[dis[x] + 1]);
        if (dis[v] == inf) dis[v] = w, q.push(mp(dis[v], v));
    }
}
if (dis[n] >= k) Win;
Lose;
```

#### 题解2：luxiaomao (4星)
**关键亮点**：
- 使用 Dijkstra 算法，思路清晰，代码简洁。
- 通过 $dis_i$ 表示从 $1$ 到 $i$ 的路径中最少匹配的 $B$ 序列数量。
- 代码可读性强，适合初学者理解。

**核心代码**：
```cpp
dis[1] = (a[1] == b[1]);
q.push(make_pair(dis[1], 1));
while (!q.empty()) {
    int u = q.top().second; q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = 0; i < (int)mp[u].size(); i++) {
        int v = mp[u][i];
        if (dis[u] < dis[v]) {
            dis[v] = dis[u] + (a[v] == b[dis[u] + 1]);
            q.push(make_pair(dis[v], v));
        }
    }
}
printf("%s\n", dis[n] == k ? "Yes" : "No");
```

#### 题解3：mountain_climber (4星)
**关键亮点**：
- 使用 Dijkstra 算法，思路清晰，代码简洁。
- 通过 $dis_u$ 表示从 $1$ 到 $u$ 的路径中最少匹配的 $B$ 序列数量。
- 代码结构清晰，适合快速理解。

**核心代码**：
```cpp
dis[1] = v[1] == b[1];
q.push({dis[1], 1});
while (q.size()) {
    node tp = q.top(); q.pop();
    if (!vis[tp.u]) {
        vis[tp.u] = true;
        for (auto i : g[tp.u]) {
            if (dis[i] > dis[tp.u] + (v[i] == b[dis[tp.u] + 1])) {
                dis[i] = dis[tp.u] + (v[i] == b[dis[tp.u] + 1]);
                q.push({dis[i], i});
            }
        }
    }
}
cout << (dis[n] == k ? "Yes\n" : "No\n");
```

### 最优关键思路
将匹配问题转化为最短路问题，通过 Dijkstra 或 0-1 BFS 计算每个顶点的最小匹配数量，确保所有路径都能匹配 $B$ 序列。

### 拓展思路
类似的问题可以通过将匹配问题转化为最短路或动态规划问题来解决。例如，判断图中是否存在一条路径满足特定条件，可以通过类似的思路进行优化。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---
处理用时：40.82秒