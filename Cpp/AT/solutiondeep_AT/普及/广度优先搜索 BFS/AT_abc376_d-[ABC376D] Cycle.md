# 题目信息

# [ABC376D] Cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点 $ M $ 辺の単純有向グラフがあります。$ i $ 番目の辺 $ (1\ \leq\ i\ \leq\ M) $ は頂点 $ a_i $ から頂点 $ b_i $ へ伸びる辺です。  
 頂点 $ 1 $ を含む閉路が存在するか判定して、存在する場合はそのような閉路のうち辺数が最小の閉路の辺数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min\ \left(\ \frac{N(N-1)}{2},\ 2\ \times\ 10^5\ \right) $
- $ 1\ \leq\ a_i\ \leq\ N $
- $ 1\ \leq\ b_i\ \leq\ N $
- $ a_i\ \neq\ b_i $
- $ i\ \neq\ j $ ならば $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ かつ $ (a_i,\ b_i)\ \neq\ (b_j,\ a_j) $
- 入力される値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ $ \to $ 頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ 頂点 $ 1 $ は辺数が $ 3 $ の閉路で、これが頂点 $ 1 $ を含む唯一の閉路です。

## 样例 #1

### 输入

```
3 3

1 2

2 3

3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 2

1 2

2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 9

6 1

1 5

2 6

2 1

3 6

4 2

6 4

3 5

5 4```

### 输出

```
4```

# AI分析结果

### 题目内容重写
【题目描述】
给定一个有向图，包含 $N$ 个顶点和 $M$ 条边。顶点编号从 $1$ 到 $N$，第 $i$ 条边从顶点 $a_i$ 指向顶点 $b_i$。判断是否存在包含顶点 $1$ 的环，如果存在，输出其中边数最少的环的边数。

【说明/提示】
- $2 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq \min\left(\frac{N(N-1)}{2}, 2 \times 10^5\right)$
- 输入的所有值均为整数

【样例解释】
样例1中，顶点 $1 \to 2 \to 3 \to 1$ 是一个边数为 $3$ 的环，且是唯一包含顶点 $1$ 的环。

### 题解分析与结论
本题的核心问题是在有向图中寻找包含顶点 $1$ 的最小环。大多数题解采用了广度优先搜索（BFS）或最短路径算法（如Dijkstra）来解决这个问题。BFS由于其适合处理边权为1的图，且时间复杂度较低，成为主流解法。

### 评分较高的题解
#### 1. 作者：Heldivis (5星)
**关键亮点**：
- 将问题转化为从顶点 $1$ 出发到某个顶点 $x$，再从 $x$ 返回顶点 $1$ 的最短路径问题。
- 使用BFS从顶点 $1$ 出发，计算到每个顶点的最短路径，然后检查是否存在从某个顶点返回顶点 $1$ 的路径。
- 代码简洁，时间复杂度为 $O(N)$，适合大规模数据。

**核心代码**：
```cpp
n = read(), m = read();
for (int i = 1; i <= m; ++i)
  int x = read(), y = read(), e[x].push_back(y);
queue<int> q;
memset(d, 0x3f, sizeof d);
for (int y : e[1]) q.push(y), d[y] = 1;
while (q.size()) {
  int x = q.front();
  q.pop();
  for (int y : e[x])
    if (d[y] > d[x] + 1) d[y] = d[x] + 1, q.push(y);
}
if (d[1] >= 1E9) d[1] = -1;
printf("%d\n", d[1]);
```

#### 2. 作者：chenxi2009 (4星)
**关键亮点**：
- 使用BFS从顶点 $1$ 开始搜索，记录每个顶点的最短路径。
- 当搜索到某个顶点 $x$ 时，如果存在边 $x \to 1$，则输出当前路径长度加1。
- 代码实现清晰，时间复杂度为 $O(N+M)$。

**核心代码**：
```cpp
q.push(make_pair(0,1));
while(q.size() && ans == -1){
    int w = q.front().first,u = q.front().second;
    q.pop();
    for(int i = 0;i < e[u].size();i ++){
        int v = e[u][i];
        if(v == 1){
            ans = w + 1;
            break;
        }
        if(arr[v]) continue;
        arr[v] = true;
        q.push(make_pair(w + 1,v));
    }
}
```

#### 3. 作者：Anins (4星)
**关键亮点**：
- 使用BFS从顶点 $1$ 开始搜索，记录每个顶点的最短路径。
- 当搜索到某个顶点 $x$ 时，如果存在边 $x \to 1$，则更新最小环的长度。
- 代码实现简洁，时间复杂度为 $O(N+M)$。

**核心代码**：
```cpp
dis[1]=0;
q.push(1);
while(!q.empty()) {
    ll u=q.front();
    q.pop();
    for(auto v:e[u]) {
        if(dis[v]==-1) {
            dis[v]=dis[u]+1;
            q.push(v); 
        } else if(v==1) {
            ans=min(ans, dis[u]+1);
        }
    }
}
```

### 最优关键思路
- **BFS的应用**：由于边权为1，BFS是最适合的算法，能够高效地找到最短路径。
- **问题转化**：将寻找包含顶点 $1$ 的最小环问题转化为从顶点 $1$ 出发到某个顶点 $x$，再从 $x$ 返回顶点 $1$ 的最短路径问题。

### 可拓展之处
- **类似问题**：在有向图中寻找包含特定顶点的最小环，或者寻找所有环。
- **算法优化**：对于边权不为1的图，可以使用Dijkstra算法或Floyd-Warshall算法。

### 推荐题目
1. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)
2. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
3. [P2865 [USACO06NOV]Roadblocks G](https://www.luogu.com.cn/problem/P2865)

---
处理用时：43.38秒