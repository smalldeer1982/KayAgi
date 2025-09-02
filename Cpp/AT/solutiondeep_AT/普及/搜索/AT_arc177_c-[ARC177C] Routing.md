# 题目信息

# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5

RBRBB

RBRRR

RRRBR

RBBRB

BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5

RBBBB

BBBBB

BBBBB

BBBBB

BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10

RRBBBBBBBB

BRRBBBBBBB

BBRRBBBBBB

BBBRRBBBBB

BBBBRRBBBB

BBBBBRRBBB

BBBBBBRRBB

BBBBBBBRRB

BBBBBBBBRR

BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17

RBBRRBRRRRRBBBBBB

BBRBRBRRBRRBRRBBR

BRBRBBBRBBRBBRBBB

RBRRBBBBBBRRBRRRR

RRRRRBRBRRRBBRBBR

RRRRRBRRBRBBRRRBB

BBBRRRBRBRBBRRRBB

BBRRRBRBBBRBRRRBR

RRBBBBBBBBBBBRBRR

RRRBRRBRBRBRBRBBB

RRBRRRRBRBRRBRBBR

RRRBBRBRBBBRBBRBR

BBRBBRRBRRRBBRBBB

BBBRBRRRRRRRBBRBB

RRRRRBRBRBBRRBRRR

BRRRRBBBRRRBRRBBB

BBRRBBRRRBBBRBBBR```

### 输出

```
8```

# AI分析结果

### 题目内容重写
有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

### 题解分析与结论
各题解均采用了图论中的最短路算法（如 Dijkstra 或 01 BFS）来解决该问题。核心思路是将网格图转化为图论问题，通过计算从起点到终点的最短路来求解需要刷紫色的格子数。具体来说：
1. **问题分解**：将问题分解为两个子问题，分别计算从 $(1,1)$ 到 $(N,N)$ 和从 $(1,N)$ 到 $(N,1)$ 的最短路。
2. **图论建模**：将网格中的每个格子视为图中的一个节点，相邻格子之间连边，边权根据格子颜色决定（若目标格子颜色不符合要求，则边权为 1，否则为 0）。
3. **最短路算法**：使用 Dijkstra 或 01 BFS 计算最短路，最终将两个子问题的结果相加即为答案。

### 评分较高的题解
#### 1. 作者：__Floze3__ (4星)
**关键亮点**：
- 使用 01 BFS 优化了时间复杂度，适合边权仅为 0 和 1 的情况。
- 思路清晰，代码简洁，易于理解。

**核心代码**：
```cpp
void bfs(int sx, int sy, int ex, int ey, char ch) {
    q.push_front(aaa{sx, sy, (mp[sx][sy] != ch)});
    dis[sx][sy] = (mp[sx][sy] != ch);
    while (!q.empty()) {
        aaa now = q.front();
        q.pop_front();
        if (now.x == ex && now.y == ey) {
            ans += dis[ex][ey];
            return;
        }
        for (int i = 0; i < 4; i++) {
            int x = now.x + dx[i], y = now.y + dy[i];
            if (x < 1 || x > n || y < 1 || y > n) continue;
            if (dis[now.x][now.y] + (ch != mp[x][y]) < dis[x][y]) {
                dis[x][y] = dis[now.x][now.y] + (ch != mp[x][y]);
                if (ch != mp[x][y]) q.push_back(aaa{x, y, dis[x][y]});
                else q.push_front(aaa{x, y, dis[x][y]});
            }
        }
    }
}
```

#### 2. 作者：ma_niu_bi (4星)
**关键亮点**：
- 使用优先队列（Dijkstra）实现最短路，代码结构清晰。
- 详细解释了问题分解的思路，易于理解。

**核心代码**：
```cpp
priority_queue <node> q;
q.push({1, 1, b[1][1]});
while (!q.empty()) {
    node now = q.top(); q.pop();
    if (vis[now.x][now.y]) continue;
    vis[now.x][now.y] = 1;
    if (now.x == n && now.y == n) continue;
    for (int i = 0; i < 4; i++) {
        int xx = now.x + xz[i], yy = now.y + yz[i];
        if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
        if (b[xx][yy] > now.d + (s[xx][yy] == 'B')) {
            b[xx][yy] = now.d + (s[xx][yy] == 'B');
            q.push({xx, yy, b[xx][yy]});
        }
    }
}
```

#### 3. 作者：破壁人罗辑 (4星)
**关键亮点**：
- 使用广度优先搜索（BFS）实现最短路，适合边权为 0 和 1 的情况。
- 详细解释了问题分解和 BFS 的实现细节。

**核心代码**：
```cpp
queue<pair<int,int> >q,qp;
q.push(make_pair(1,1)); vis[1][1][0]=1;
while (!q.empty()) {
    pair<int,int>p=q.front(); q.pop();
    for (int i = 0; i < 4; i++) {
        int nx = p.first + dx[i], ny = p.second + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
        if (!vis[nx][ny][0]) {
            vis[nx][ny][0] = 1;
            if (c[nx][ny] == 'R') q.push(make_pair(nx, ny));
            else qp.push(make_pair(nx, ny));
            val[nx][ny][0] = val[p.first][p.second][0] + (c[nx][ny] != 'R');
        }
    }
}
```

### 最优关键思路与技巧
1. **问题分解**：将原问题分解为两个独立的子问题，分别求解从 $(1,1)$ 到 $(N,N)$ 和从 $(1,N)$ 到 $(N,1)$ 的最短路。
2. **图论建模**：将网格图转化为图论问题，相邻格子之间连边，边权根据格子颜色决定。
3. **最短路算法**：使用 Dijkstra 或 01 BFS 计算最短路，优化时间复杂度。

### 可拓展之处
- 类似问题可以扩展到三维网格或其他复杂图结构。
- 可以结合其他图论算法（如 A* 算法）进一步优化。

### 推荐题目
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

---
处理用时：54.41秒