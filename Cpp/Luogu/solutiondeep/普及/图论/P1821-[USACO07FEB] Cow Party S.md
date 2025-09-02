# 题目信息

# [USACO07FEB] Cow Party S

## 题目描述

寒假到了，$n$ 头牛都要去参加一场在编号为 $x$ 的牛的农场举行的派对，农场之间有 $m$ 条有向路，每条路都有一定的长度。

每头牛参加完派对后都必须回家，无论是去参加派对还是回家，每头牛都会选择最短路径，求这 $n$ 头牛的最短路径（一个来回）中最长的一条路径长度。


## 说明/提示

### 样例 1 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/rl3com2y.png)

### 数据规模与约定

对于全部的测试点，保证 $1 \leq x \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1 \leq u,v \leq n$，$1 \leq w \leq 10^2$，保证从任何一个结点出发都能到达 $x$ 号结点，且从 $x$ 出发可以到达其他所有节点。

## 样例 #1

### 输入

```
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
```

### 输出

```
10```

# AI分析结果

### 综合分析与结论
本题主要求解每头牛参加派对并回家的最短路径中的最大值，由于是有向图，需要分别计算去程和回程的最短路径。各题解的核心思路大多是通过反向建图将单终点最短路转换为单源最短路，再结合不同的最短路算法（如 Dijkstra、SPFA、Bellman - Ford 等）来解决问题。

### 所选题解
- **作者：My_666 (赞：54)，4星**
    - **关键亮点**：思路清晰，详细阐述了反向建图的思想，推荐使用 Dijkstra 算法并给出了具体实现，代码注释丰富，可读性高。
    - **个人心得**：无
    - **核心代码**：
```cpp
// 反向建图，将单终点最短路转为单源最短路
for (int i = 1; i <= m; i++) addEdge(v[i], u[i], w[i]); 
// Dijkstra 算法
void dijkstra(int s) {
    for (int i = 1; i <= n; i++) dis[i] = 0x3f3f3f3f;  
    priority_queue< pair<int, int> > q;
    q.push(make_pair(0, s));
    dis[s] = 0;
    while (q.size()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}
```
- **作者：Anakin (赞：1)，4星**
    - **关键亮点**：将图封装成结构体，减少代码量且避免变量名冲突，代码结构清晰，实现了堆优化的 Dijkstra 算法。
    - **个人心得**：无
    - **核心代码**：
```cpp
struct G{//图的结构体
    Edge edge[MAXM];
    int cnt;
    int dis[MAXN], head[MAXN];//不用担心变量名冲突
    void init(){//链式前向星的准备
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
    inline void addedge(int u, int v, int w){//加边
        edge[++cnt].v = v;
        edge[cnt].w = w;
        edge[cnt].next = head[u];
        head[u] = cnt;
    }
    void dij(){//最短路
        memset(dis, INF, sizeof(dis));
        priority_queue<Node> q;
        q.push(Node{x, 0});
        dis[x] = 0;
        while (!q.empty()) {
            Node temp = q.top();
            q.pop();
            int u = temp.id;
            int d = temp.d;
            if (d != dis[u]) continue;
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].v, w = edge[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.push(Node{v, dis[v]});
                }
            }
        }
    }
} g1, g2; // 建两个图,一个正向边一个反向
```
- **作者：xiaohuang (赞：0)，4星**
    - **关键亮点**：使用 Dijkstra 算法，详细展示了正向建图和反向建图的过程，代码逻辑清晰，注释详细。
    - **个人心得**：无
    - **核心代码**：
```cpp
// 邻接表存图
inline void addedge(int u, int v, int val) {
    edge[++cnt].to = v; edge[cnt].val = val; edge[cnt].nxt = head[u]; head[u] = cnt;
}
// Dijkstra 最短路
inline void dijkstra(int S) {
    memset(dis, INF, sizeof(dis));
    priority_queue< pair<int, int> > Q;
    Q.push(make_pair(0, S));
    dis[S] = 0;
    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].val) {
                dis[v] = dis[u] + edge[i].val;
                Q.push(make_pair(-dis[v], v));
            }
        }
    }
}
```

### 最优关键思路或技巧
- **反向建图**：将单终点最短路问题转换为单源最短路问题，避免了从每个点都求一遍到终点的最短路，降低了时间复杂度。
- **堆优化的 Dijkstra 算法**：使用优先队列优化 Dijkstra 算法，提高了算法效率。
- **封装图结构**：将图封装成结构体，减少代码量，避免变量名冲突，提高代码的可读性和可维护性。

### 可拓展之处
同类型题或类似算法套路：
- **多源最短路问题**：可使用 Floyd 算法解决，但对于大规模数据，可考虑 Johnson 算法。
- **负权边问题**：使用 Bellman - Ford 算法或 SPFA 算法（注意 SPFA 可能被卡）。
- **最短路计数问题**：在求最短路的过程中，记录每个点的最短路数量。

### 推荐题目
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录与总结
- **EarthGiao**：通过全 WA 经历深刻认识到题目中的路是单向路，提醒我们做题时要仔细审题。
- **原子分子奶子**：因把 freopen 里的 party 打成 patry 少得 100 分，强调了代码书写的准确性和调试的重要性。

---
处理用时：40.31秒