# 题目信息

# [ABC218F] Blocked Roads

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_f

$ N $ 頂点 $ M $ 辺の有向グラフが与えられます。頂点には $ 1 $ から $ N $ の番号、辺には $ 1 $ から $ M $ の番号がついています。辺 $ i\,(1\ \leq\ i\ \leq\ M) $ は頂点 $ s_i $ から頂点 $ t_i $ に向かう長さ $ 1 $ の辺です。

各 $ i\,(1\ \leq\ i\ \leq\ M) $ について、辺 $ i $ のみ通れないときの頂点 $ 1 $ から頂点 $ N $ までの最短距離を求めてください。ただし、頂点 $ 1 $ から頂点 $ N $ にたどり着けない場合は `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ M\ \leq\ N(N-1) $
- $ 1\ \leq\ s_i,t_i\ \leq\ N $
- $ s_i\ \neq\ t_i $
- $ (s_i,t_i)\ \neq\ (s_j,t_j) $ $ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 2

辺 $ 1 $ のみ通れないとき、頂点 $ 1 $ から頂点 $ N $ にたどり着けないので `-1` を出力します。

## 样例 #1

### 输入

```
3 3

1 2

1 3

2 3```

### 输出

```
1

2

1```

## 样例 #2

### 输入

```
4 4

1 2

2 3

2 4

3 4```

### 输出

```
-1

2

3

2```

## 样例 #3

### 输入

```
5 10

1 2

1 4

1 5

2 1

2 3

3 1

3 2

3 5

4 2

4 3```

### 输出

```
1

1

3

1

1

1

1

1

1

1```

## 样例 #4

### 输入

```
4 1

1 2```

### 输出

```
-1```

# AI分析结果

### 题目内容重写
给定一个包含 $N$ 个顶点和 $M$ 条边的有向图。顶点编号为 $1$ 到 $N$，边编号为 $1$ 到 $M$。每条边 $i$ 从顶点 $s_i$ 指向顶点 $t_i$，长度为 $1$。

对于每条边 $i$，求在删除该边后，从顶点 $1$ 到顶点 $N$ 的最短路径长度。如果无法到达，则输出 `-1`。

### 算法分类
最短路、广度优先搜索 BFS

### 题解分析与结论
该题的核心问题是在删除每条边后，求从起点到终点的最短路径。直接暴力解法是每次删除一条边后跑一次 BFS，时间复杂度为 $O((n + m)m)$，在稠密图下会达到 $O(n^4)$，无法通过。

优化思路是利用最短路径的性质：最短路径经过的边数不超过 $n-1$ 条。因此，只有删除这些边时，最短路径才可能发生变化。可以先求出原图的最短路径，记录路径上的边，然后只对这些边进行 BFS 重计算，其他边直接输出原最短路径长度。这样时间复杂度降为 $O((n + m)n + m)$。

### 精选题解
#### 题解作者：SkyWave (5星)
**关键亮点**：
- 利用最短路径边数不超过 $n-1$ 的性质，减少 BFS 次数。
- 代码清晰，逻辑严谨，优化思路明确。

**核心代码**：
```cpp
void bfs(int start, const pii &del) {
    memset(dis, -1, sizeof(dis));
    dis[start] = 0;
    int queue[N];
    int front = 1, rear = 0;
    queue[++rear] = start;
    while (front <= rear) {
        int tmp = queue[front++];
        for (auto i : vec[tmp]) {
            if (pii(tmp, i) == del) continue;
            if (dis[i] == -1) {
                pre[i] = tmp;
                dis[i] = dis[tmp] + 1;
                queue[++rear] = i;
            }
        }
    }
}
```
**实现思想**：通过 BFS 计算最短路径，并记录路径上的边。对于需要删除的边，跳过该边进行 BFS。

#### 题解作者：_Ponder_ (4星)
**关键亮点**：
- 同样利用最短路径边数不超过 $n-1$ 的性质，优化 BFS 次数。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
int bfs(int notedge) {
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    while(!q.empty()) q.pop();
    q.push(1);dis[1]=0;
    while(!q.empty()){
        int now=q.front();q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(int v:to[now]){
            if(edge[notedge]==make_pair(now,v)) continue;
            if(dis[v]>dis[now]+1){
                dis[v]=dis[now]+1;
                q.push(v);
                if(!notedge) pre[v]=now;
            }
        }
    }
    if(dis[n]==inf) return -1;
    return dis[n];
}
```
**实现思想**：通过 BFS 计算最短路径，并记录路径上的边。对于需要删除的边，跳过该边进行 BFS。

### 最优关键思路
1. **最短路径性质**：利用最短路径经过的边数不超过 $n-1$ 的性质，减少 BFS 次数。
2. **路径记录**：通过 BFS 记录最短路径上的边，只对这些边进行重计算。
3. **跳过删除边**：在 BFS 过程中，跳过需要删除的边，避免重复计算。

### 拓展思路
类似问题可以扩展到其他图论问题，如删除点后求最短路径、删除多条边后求最短路径等。可以通过记录路径或利用其他图的性质进行优化。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---
处理用时：26.95秒