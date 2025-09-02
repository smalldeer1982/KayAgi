# 题目信息

# [USACO07FEB] Lilypad Pond G

## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.


## 说明/提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$

## 样例 #1

### 输入

```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0
```

### 输出

```
2
3
```

# AI分析结果

---
# 💡 洛语云笺的C++算法解析：Lilypad Pond G 深入学习指南 💡

## 1. 题目解读与策略初探

✨ **本题核心挑战**：  
“如何在允许放置最少数量的荷叶（新莉莉垫）的前提下，让 Bessie 从起点以**象棋马步**跳到终点，并统计**所有最少放置方案**。”

✨ **核心算法标签**：  
- 最短路 (Shortest Path)  
- 最短路计数 (Shortest Path Counting)  
- 图建模 (Graph Modeling)  
- 状态压缩 / 网格图  

🗣️ **初步分析**：  
1. 直接 BFS 会被“原荷叶”干扰，无法区分“原荷叶”与“新荷叶”。  
2. 把原荷叶缩成连通块会重复计数，导致方案数错误。  
3. 关键在于**如何建图**：  
   - 节点 = 所有可站立的格子（水、起点、终点）。  
   - 边权 = 1 表示需要放 1 朵荷叶才能到达；0 表示原荷叶免费通过。  
   - 必须避免 **0 权环** 导致计数死循环。  

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 发现内容 |
|---|---|
| **问题目标** | “最小化新荷叶数量 + 统计方案数” → 最短路 + 计数。 |
| **移动方式** | 马步 8 方向 → 8 条出边。 |
| **障碍/免费通道** | 原荷叶可视为**免费通道**（边权 0），但会形成 0 环 → 需特殊处理。 |
| **数据规模** | 30×30=900 节点，可接受 O(N²) 或 O(N log N) 的最短路算法。 |

### 🧠 思维链构建：从线索到策略
> 1. 看到“最少”+“计数”→ 最短路 + 计数模板。  
> 2. 发现原荷叶可走但不计入方案 → 边权 0，会引入 0 环。  
> 3. 解决 0 环：  
>   - **方案 A**：把原荷叶连通块内所有“水”互相连边，边权 1。  
>   - **方案 B**：从每块“水”出发 DFS，找出“一步荷叶可达”的格子，建单向边权 1 的图。  
> 4. 最终选择 **方案 B**，无 0 边，可直接 SPFA / Dijkstra 计数。

---

## 2. 精选优质题解参考

**题解一：D_14134（赞：35）**  
- **亮点**：最早提出“避免 0 环”思想，用 DFS 从每块水出发，建立“一步荷叶可达”的边，再跑 SPFA 计数。  
- **技巧**：`dfs(o,x,y)` 内递归遍历原荷叶，找到所有“一步荷叶可达”的格子，建单向边。  

**题解二：s_ShotღMaki（赞：12）**  
- **亮点**：代码清晰，变量命名易懂，用 `This_is_for_you` 递归建图，SPFA 模板完整。  
- **技巧**：用 `bianhao[i][j]=(i-1)*m+j` 给格子编号，二维转一维。  

**题解三：寒鸽儿（赞：6）**  
- **亮点**：详细解释 0 环问题，用“跳过原荷叶”建图，二维 SPFA。  
- **技巧**：二维 `head[x][y]` + 邻接表，避免一维映射冲突。  

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（最优解法）

| 关键点 | 分析 | 学习笔记 |
|---|---|---|
| **1. 建图避免 0 环** | 从每个“水”格子出发 DFS，遇到原荷叶继续走，遇到“水/终点”则建边权 1。 | 将 0 权问题转化为 1 权图，简化计数。 |
| **2. 最短路计数** | 用 SPFA / Dijkstra，当 `dis[v] == dis[u]+1` 时累加 `cnt[v] += cnt[u]`。 | 注意终点不需再放荷叶，最终答案 `dis-1`。 |
| **3. 二维→一维映射** | `id = (x-1)*m + y`，减少内存访问。 | 统一编号，便于邻接表存储。 |

### ✨ 解题技巧总结
- **问题转化**：把“原荷叶”视为“免费通道”会引入 0 环，需用 DFS 预处理边。  
- **计数公式**：`cnt[v] += cnt[u]` 仅在边权相等时生效，避免重复。  
- **边界处理**：终点格子不计入“新荷叶”，输出 `dis[ed]-1`。

### ⚔️ 策略竞技场

| 策略 | 核心思想 | 优点 | 缺点 | 适用场景 |
|---|---|---|---|---|
| **暴力 BFS** | 直接跑 BFS，原荷叶可走 | 代码短 | 无法区分原/新荷叶，计数错误 | 样例 |
| **连通块缩点** | 把原荷叶缩成超级点 | 减少节点 | 会重复计数 | 不适用 |
| **DFS 建图 + SPFA** | 从水出发 DFS 建 1 权图 | 无 0 环，计数正确 | 建图略复杂 | **最优解** |

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 35, M = N * N, inf = 0x3f3f3f3f;
int n, m, g[N][N], st, ed, dx[8] = {2,2,-2,-2,1,-1,1,-1}, dy[8] = {-1,1,-1,1,2,2,-2,-2};
int id(int x, int y) { return (x - 1) * m + y; }

// 建图
vector<int> e[M];
void dfs(int sx, int sy, int from) {
    static bool vis[N][N];
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int>> q;
    q.push({sx, sy}); vis[sx][sy] = 1;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 1 || ny < 1 || nx > n || ny > m || vis[nx][ny]) continue;
            if (g[nx][ny] == 2) continue;
            vis[nx][ny] = 1;
            if (g[nx][ny] == 1) q.push({nx, ny}); // 原荷叶继续走
            else e[from].push_back(id(nx, ny));   // 水/终点 建边
        }
    }
}

// SPFA 计数
int dis[M];
long long cnt[M];
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(st); dis[st] = 0; cnt[st] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : e[u]) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                cnt[v] = cnt[u];
                q.push(v);
            } else if (dis[v] == dis[u] + 1) {
                cnt[v] += cnt[u];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
            if (g[i][j] == 3) st = id(i, j);
            if (g[i][j] == 4) ed = id(i, j);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (g[i][j] == 0 || g[i][j] == 3)
                dfs(i, j, id(i, j));
    spfa();
    if (dis[ed] == inf) cout << "-1\n";
    else cout << dis[ed] - 1 << '\n' << cnt[ed] << '\n';
    return 0;
}
```

---

## 5. 算法可视化：像素动画演示

**主题**：**“像素骑士·荷叶跳跃”**  
- **场景**：30×30 像素网格，起点绿色，终点红色，原荷叶绿色闪烁，水蓝色。  
- **动画流程**：
  1. **建图阶段**：从蓝色水格子发射“像素箭头”，穿过绿色荷叶，最终落在另一蓝色格子，箭头变为“+1”提示。  
  2. **SPFA**：像素队列动态展示，当前节点闪烁黄色，更新最短路与计数时播放“叮”音效。  
  3. **终点庆祝**：到达终点后，路径高亮金色，播放 8 位胜利音，显示“最少荷叶数”与“方案数”。

**交互**：  
- 步进 / 自动播放按钮。  
- 速度滑块（1-10 FPS）。  
- 点击格子查看“一步可达”预览。

---

## 6. 拓展练习与相似问题思考

| 题目 | 推荐理由 |
|---|---|
| **P1144 最短路计数** | 裸最短路计数，巩固模板。 |
| **P1608 路径统计** | 带权图计数，需处理 0 权边。 |
| **P1979 华容道** | 网格图状态建模 + 最短路。 |

---

## 7. 学习心得与经验分享

> **寒鸽儿**：“第一次独立 AC 紫题，最大的教训是**不要忽视 0 权环**！用 DFS 建图后，计数瞬间清爽。”  
> **cghAndy**：“建图思路比代码更重要，想清楚再写，能少调 3 小时。”  

---

<conclusion>
掌握“网格图建图 + 最短路计数”后，你会惊喜地发现：很多看似复杂的棋盘问题，都能被这一套路轻松化解。下次见！

---
处理用时：58.21秒