# 题目信息

# [ABC375G] Road Blocked 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc375/tasks/abc375_g

AtCoder国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ M $ の番号がついた $ M $ 本の道路があります。  
 道路 $ i $ は都市 $ A_i $ と都市 $ B_i $ を双方向に結び長さは $ C_i $ です。

各 $ i=1,\ldots,M $ について、以下の $ 2 $ つの値が異なるかどうか判定してください。

- 全ての道路が通行可能なときの、都市 $ 1 $ から都市 $ N $ への最短距離
- 道路 $ i $ 以外の $ M-1 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ N $ への最短距離
 
ただし、一方では都市 $ 1 $ から都市 $ N $ に到達可能で、他方では到達不可能なとき、両者の値は異なるとみなします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ N $ へは到達可能
- 入力は全ては整数である
 
### Sample Explanation 1

全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ 3 $ への最短距離は $ 10 $ です。 - 道路 $ 1 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 10 $ です - 道路 $ 2 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 11 $ です - 道路 $ 3 $ 以外の $ 2 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 3 $ への最短距離 は $ 10 $ です

### Sample Explanation 2

全ての道路が通行可能なとき、都市 $ 1 $ から都市 $ 4 $ への最短距離は $ 1 $ です。 道路 $ 6 $ 以外の $ 5 $ 本の道路が通行可能なときの、都市 $ 1 $ から都市 $ 4 $ への最短距離 は $ 2 $ です。

### Sample Explanation 3

道路 $ 1 $ 以外の $ 0 $ 本の道路が通行可能なとき、都市 $ 1 $ から都市 $ 2 $ へは到達できません。

## 样例 #1

### 输入

```
3 3

1 2 5

1 3 10

2 3 6```

### 输出

```
No

Yes

No```

## 样例 #2

### 输入

```
4 6

2 3 1

2 4 1

3 4 1

1 2 1

1 3 1

1 4 1```

### 输出

```
No

No

No

No

No

Yes```

## 样例 #3

### 输入

```
2 1

1 2 1```

### 输出

```
Yes```

# AI分析结果



---

**唯一算法分类**：图论（最短路与桥）

---

### 题解思路与算法要点

#### 核心思路
1. **最短路筛选**：通过两次 Dijkstra 分别求出从起点 1 和终点 N 到所有点的最短距离（`d1[]` 和 `d2[]`），筛选出所有可能属于最短路的边。
2. **最短路图构建**：若边 `(u, v, w)` 满足 `d1[u] + w + d2[v] == 最短路长度` 或 `d1[v] + w + d2[u] == 最短路长度`，则该边属于最短路图。
3. **割边判定**：在最短路图中使用 Tarjan 算法寻找桥边。若某边是桥边，则删除后最短路必然改变。

#### 解决难点
- **高效筛选最短路边**：通过两次 Dijkstra 的预处理，将每条边的筛选复杂度降至 O(1)。
- **Tarjan 找桥**：通过 DFS 记录每个节点的访问顺序（`dfn[]`）和能回溯到的最早节点（`low[]`），快速判断割边。
- **大规模数据优化**：邻接表存储、优先队列优化 Dijkstra，确保总时间复杂度为 O(M log N + N + M)。

---

### 题解评分（≥4星）

1. **I_will_AKIOI（5星）**
   - **亮点**：代码结构清晰，直接构建最短路图后 Tarjan 找桥，注释简洁。
   - **关键代码**：
     ```cpp
     // 筛选最短路边并建图
     if (d1[x[i]] + z[i] + d2[y[i]] == d1[n] || d1[y[i]] + z[i] + d2[x[i]] == d1[n]) {
         G[x[i]].push_back({y[i], i});
         G[y[i]].push_back({x[i], i});
     }
     // Tarjan 找桥
     if (low[now.first] > dfn[k]) cut[now.second] = 1;
     ```

2. **yzljy（4.5星）**
   - **亮点**：详细注释与可视化示例图，强调桥边的意义。
   - **个人心得**：提到“第一次场切 G 题”，体现对算法流程的深刻理解。

3. **shinzanmono（4星）**
   - **亮点**：代码中显式处理双向边，通过 `bridge[p] = bridge[p^1] = true` 确保割边标记正确。

---

### 最优思路与技巧

#### 关键步骤
1. **双源最短路**：通过 `d1[]` 和 `d2[]` 快速判断边是否在最短路上。
   ```cpp
   if (d1[u] + w + d2[v] == total_dis || d1[v] + w + d2[u] == total_dis) {
       // 边属于最短路图
   }
   ```
2. **Tarjan 割边算法**：只需一次 DFS，时间复杂度 O(N + M)。
   ```cpp
   void tarjan(int u, int fa_edge) {
       dfn[u] = low[u] = ++timer;
       for (auto &e : adj[u]) {
           int v = e.to, idx = e.idx;
           if (idx == fa_edge) continue;
           if (!dfn[v]) {
               tarjan(v, idx);
               low[u] = min(low[u], low[v]);
               if (low[v] > dfn[u]) is_bridge[idx] = true;
           } else {
               low[u] = min(low[u], dfn[v]);
           }
       }
   }
   ```

---

### 同类型题与推荐题目

1. **P3388（割点）**：Tarjan 算法的经典应用。
2. **P2146 [NOI2015] 软件包管理器**：树边与桥的动态维护。
3. **P1354 房间最短路问题**：几何建模与最短路径的结合。

---

### 个人心得摘录

- **I_will_AKIOI**：赛时未通过，次日调试发现桥边标记错误，强调“反向边必须同步标记”。
- **SwordDance**：提到“最短路图边的索引处理容易出错”，建议用 `pair<u, v>` 哈希替代数组存储。

---

### 可视化与算法演示

#### 动画设计
1. **像素风格渲染**：
   - **颜色**：最短路边用绿色，桥边用红色，普通边用灰色。
   - **Canvas 网格**：节点以圆形表示，边用直线连接，桥边闪烁提示。
2. **操作演示**：
   - **Step 1**：展示原图，播放 Dijkstra 过程（节点按访问顺序点亮）。
   - **Step 2**：高亮最短路图，逐步标记候选边。
   - **Step 3**：运行 Tarjan 算法，用红色标记桥边，播放“发现桥边”音效。
3. **交互控制**：
   - **速度调节**：滑块控制动画速度（0.5x~2x）。
   - **单步执行**：按空格暂停/继续，方向键步进。

#### 复古音效（Web Audio API）
- **桥边发现**：播放 `8-bit` 风格上升音阶（频率 800Hz → 1200Hz）。
- **错误提示**：短促“哔”声（200Hz，50ms）。

---

### 核心代码实现

```cpp
// Dijkstra 双源最短路
void dijkstra(int s, ll dist[]) {
    priority_queue<pair<ll, int>> pq;
    fill(dist, dist + N, LLONG_MAX);
    dist[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (-d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(-dist[v], v);
            }
        }
    }
}

// Tarjan 找桥
void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++timer;
    for (auto [v, e] : g[u]) {
        if (e == pe) continue;
        if (!dfn[v]) {
            tarjan(v, e);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[e] = true;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
```

---

**可视化演示示例（伪代码）**：
```javascript
// Canvas 初始化
const canvas = document.getElementById('graph-canvas');
const ctx = canvas.getContext('2d');
// 绘制节点与边
function drawEdge(u, v, color) {
    ctx.beginPath();
    ctx.moveTo(u.x, u.y);
    ctx.lineTo(v.x, v.y);
    ctx.strokeStyle = color;
    ctx.stroke();
}
// 自动播放
function animate() {
    if (step === 0) runDijkstra();
    else if (step === 1) highlightShortestEdges();
    else if (step === 2) runTarjan();
    requestAnimationFrame(animate);
}
```

---
处理用时：110.82秒