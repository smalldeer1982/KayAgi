# 题目信息

# [USACO05MAR] Checking an Alibi 不在场的证明

## 题目描述

农场有 $F$ 个点，已知 $P$ 条边以及每条边的起点终点和通过时间，给出 $C$ 个有牛的点，求在规定时间 $M$ 内能从起点到达牛当前位置的牛的数量，并按升序输出牛的编号。

谷仓里发现谷物被盗！FJ 正试图从 $C$ 只奶牛里找出那个偷谷物的罪犯。幸运的是，一个恰好路过的卫星拍下谷物被盗前 $M$ 秒的农场的图片。这样约翰就能通过牛们的位置来判断谁有足够的时间来盗窃谷物。

约翰农场有 $F$ 草地，标号 $1$ 到 $F$，还有 $P$ 条双向路连接着它们。通过这些路需要的时间在 $1$ 到 $70000$ 秒的范围内。田地 $1$ 上建有那个被盗的谷仓。给出农场地图，以及卫星照片里每只牛所在的位置，请判断哪些牛有可能犯罪。

请注意：数据里可能存在重边（起点和终点相同的边）。

## 说明/提示

#### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/ik4552lc.png)

#### 数据约定

对于 $100\%$ 的数据：$1 \le M \le 70000$，$1 \le C \le 100$，$1 \le P \le 1000$，$1 \le F \le 500$。

## 样例 #1

### 输入

```
7 6 5 8
1 4 2
1 2 1
2 3 6
3 5 5
5 4 6
1 7 9
1
4
5
3
7```

### 输出

```
4
1
2
3
4```

# AI分析结果



# 算法分类
**单源最短路径**

# 题解思路与核心难点

## 核心思路
题目要求判断各奶牛位置到谷仓（1号点）的最短路径是否在时间限制内。核心是**单源最短路径算法**，以1号点为起点计算到所有点的最短路径。通过Dijkstra或SPFA算法实现，筛选满足条件的奶牛编号。

## 解决难点
1. **重边处理**：需保留两点间的最短边。
2. **输出顺序**：按输入顺序存储奶牛编号，最后按升序输出符合条件的编号。
3. **算法选择**：边权均为正数，Dijkstra更高效；但SPFA在本题数据规模下表现良好。

# 题解评分（≥4星）

1. **一只书虫仔（SPFA实现）**  
   ⭐⭐⭐⭐  
   代码简洁，使用SPFA，逻辑清晰。统计答案部分处理得当，适合快速实现。

2. **WanderingTrader（Dijkstra实现）**  
   ⭐⭐⭐⭐  
   提供朴素Dijkstra与堆优化版本，讲解详细，代码结构规范，适合不同层次学习者。

3. **封禁用户（Dijkstra堆优化）**  
   ⭐⭐⭐⭐  
   使用优先队列优化，代码高效，注释明确，适合理解堆优化原理。

# 最优思路与技巧

1. **反向建图**：将各奶牛点到1号点的最短路径转换为1号点到各点的最短路径，避免多次计算。
2. **邻接表存图**：高效处理稀疏图，自动过滤重边（存储时取最小值）。
3. **统一预处理**：一次计算1号点到所有点的最短路径，避免重复运算。

# 类似题目推荐

1. **P4779 【模板】单源最短路径（标准版）**  
   Dijkstra堆优化模板题，适合巩固基础。

2. **P3371 【模板】单源最短路径（弱化版）**  
   SPFA实现，数据规模较小。

3. **P1629 邮递员送信**  
   往返最短路径，考察反向建图思想。

# 代码核心片段（Dijkstra堆优化）

```cpp
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii>> pq;
vector<pii> graph[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
```

# 可视化算法设计

## 动画方案
1. **节点状态标记**  
   - 红色：当前处理节点  
   - 绿色：已确定最短路径  
   - 黄色：队列中待处理节点  

2. **边更新效果**  
   - 蓝色闪烁：被松弛的边  
   - 显示实时距离值在节点旁  

3. **复古像素风格**  
   - 8-bit字体显示距离，节点用16x16像素块表示  
   - 背景音乐：FC风格8-bit循环音轨  

## 交互功能
- **步进控制**：空格暂停/继续，方向键单步执行  
- **速度调节**：滑块控制动画速度（0.5x~3x）  
- **音效反馈**：  
  - "滴"声：节点入队  
  - "嘟"声：路径松弛成功  

# 个人心得摘录
> "SPFA在数据随机的情况下效率接近Dijkstra，但要注意最坏情况的时间复杂度。本题因边权范围大但数据规模小，SPFA反而更易编码。" —— 一只书虫仔

> "朴素Dijkstra在n=500时完全够用，堆优化版反而增加了代码复杂度，选择合适的最重要。" —— WanderingTrader

# 完整代码（SPFA实现）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f, MAXN = 505;
vector<pair<int,int>> edges[MAXN];
int dist[MAXN], inQueue[MAXN];

void spfa(int start) {
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist));
    dist[start] = 0;
    q.push(start); inQueue[start] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = 0;
        for (auto [v, w] : edges[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = 1;
                }
            }
        }
    }
}

int main() {
    int F, P, C, M; 
    cin >> F >> P >> C >> M;
    while (P--) {
        int u, v, w; cin >> u >> v >> w;
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }
    spfa(1);
    vector<int> ans;
    for (int i=1; i<=C; ++i) {
        int x; cin >> x;
        if (dist[x] <= M) ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for (int id : ans) cout << id << "\n";
}
```

---
处理用时：89.37秒