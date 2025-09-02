# 题目信息

# [ABC398E] Tree Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc398/tasks/abc398_e

本题是一道**交互题**（你的程序需要通过输入输出与评测系统进行交互）。

给定一棵包含 $N$ 个顶点的树 $G$，顶点编号为 $1$ 至 $N$。第 $i$ 条边连接顶点 $U_i$ 和 $V_i$。

你和高桥君将使用这棵树 $G$ 进行游戏。首先，你选择先手或后手。之后，双方轮流进行以下操作（先手先行动）：

- 选择一个满足 $1 \leq i < j \leq N$ 的整数对 $(i, j)$，并满足以下两个条件：
  - $G$ 中当前不存在连接顶点 $i$ 和顶点 $j$ 的边。
  - 在 $G$ 中添加连接顶点 $i$ 和顶点 $j$ 的边后，不会形成奇环。
- 将该边添加到 $G$ 中。

无法进行操作的一方判负，另一方获胜。请通过实际与高桥君对弈取得胜利。

**奇环的定义**：顶点序列 $(v_0, v_1, \ldots, v_k)$ 满足以下所有条件时，称为 $G$ 的一个奇环：
- $k$ 为奇数。
- $v_0 = v_k$。
- 对所有 $1 \leq i \leq k$，存在连接 $v_{i-1}$ 和 $v_i$ 的边。
### 交互方式

本题是一道交互题，你的程序需通过标准输入输出与评测系统交互。

首先，通过标准输入接收 $N$ 及 $G$ 的信息，格式如下：

> $N$  
> $U_1$ $V_1$  
> $U_2$ $V_2$  
> $\vdots$  
> $U_{N-1}$ $V_{N-1}$  

接着，你需决定选择先手或后手。若选择先手，通过标准输出输出 `First`；若选择后手，输出 `Second`。

此后游戏开始。

你的回合时，需将选择的整数对 $(i, j)$ 按顺序以空格分隔输出至标准输出：

> $i$ $j$

高桥君的回合时，将通过标准输入给出两个整数 $i$ 和 $j$：

> $i$ $j$

当 $(i, j) = (-1, -1)$ 时，表示你已获胜且游戏结束，此时需立即终止程序。  
其他情况下，$(i, j)$ 表示高桥君选择的整数对。

## 说明/提示

### 约束条件

- $2 \leq N \leq 100$
- $1 \leq U_i < V_i \leq N$
- 给定的图是树。
- 输入均为整数。

### 注意事项

- $\footnotesize\color{red}\textsf{\textbf{每次输出后，需在末尾添加换行符并刷新标准输出缓冲区。否则可能导致评测结果为 \colorbox{#f0ad4e}{\color{white}{TLE}}。}}$
- **若在交互过程中输出格式错误或程序意外终止，评测结果将不确定。**
- 游戏结束后请立即终止程序，否则评测结果不确定。

### 交互示例

|输入|输出|解释|
|:-|:-|:-|
|$\begin{matrix} \texttt{4 { }} \\ \texttt{1 2} \\ \texttt{2 3} \\ \texttt{3 4} \end{matrix}$| |首先，你收到 $N$ 和 $G$ 的边信息。|
||$\texttt{First}$|你选择先手行动。|
||$\texttt{1 4}$|你在顶点 $1$ 和 $4$ 之间添加一条边|
|$\texttt{-1 -1}$||高桥无法继续操作，你获胜。评测结果返回 $\colorbox{#5cb85c}{\footnotesize\textsf{\textbf{\color{white}{AC}}}}$。|

# AI分析结果



## 算法分类
**二分图染色 & 博弈论**

---

## 题解分析与结论

### 核心思路
1. **二分图性质**：树本身是二分图，通过黑白染色后，合法边只能是异色节点间的边。
2. **合法边统计**：计算所有未连接的异色边总数，奇偶性决定先手/后手策略。
3. **博弈策略**：若合法边数为奇数，先手必胜（最后一步由己方操作），否则后手必胜。

### 解决难点
- **合法边判定**：需快速统计所有异色且未在树中存在的边，避免重复计算。
- **交互实现**：需维护动态边集合，在对手操作后快速找到剩余合法边。

### 题解对比
- **染色法 vs LCA法**：染色法直接利用二分图性质，复杂度为 $O(N)$；而LCA法需计算路径长度，复杂度 $O(N^2 \log N)$，但实际处理更繁琐。
- **集合维护**：多数题解使用 `set` 或 `map` 动态维护剩余合法边，保证快速查询和删除。

---

## 题解评分（≥4星）

1. **Little_x_starTYJ（5星）**  
   - 思路清晰，直接利用染色统计异色边，代码简洁高效。  
   - 维护 `vector` 和 `map` 快速处理边集合，交互逻辑明确。  
   - **关键代码**：  
     ```cpp
     dfs(1, 0); // 染色
     for (i,j) 异色且未连接 → v2.push_back({i,j});
     if (v2.size() % 2) 先手，否则后手;
     ```

2. **zyn0309（4.5星）**  
   - 使用 `set` 维护合法边，输出时直接取首元素。  
   - 代码简洁，交互处理流畅，但未处理输入边排序问题。  
   - **关键代码**：  
     ```cpp
     for (i,j) 异色且未连接 → st.insert({i,j});
     if (st.size() % 2) 先手;
     ```

3. **xxgirlxx（4星）**  
   - 通过 LCA 计算路径长度判断奇偶，适用于更复杂场景。  
   - 代码稍复杂，但思路完整，处理了链的特殊情况。  
   - **关键代码**：  
     ```cpp
     int tmp = lca(i,j);
     int len = deep[i] + deep[j] - 2*deep[tmp] + 1;
     if (len % 2 == 0) → 合法边;
     ```

---

## 最优思路提炼
1. **染色定二分图**：对树进行黑白染色，合法边为异色节点对。
2. **奇偶博弈策略**：合法边总数奇偶性决定先手/后手选择。
3. **集合维护动态边**：使用 `set` 或 `vector` 存储合法边，交互时快速删除已选边。

---

## 相似题目推荐
1. **洛谷 P2737 [游戏]**: 基于二分图的博弈问题。
2. **洛谷 P4105 [奇环判定]**: 结合奇环判定的交互题。
3. **洛谷 CF1105D (Board Game)**: 动态维护合法操作的博弈策略。

---

## 可视化设计

### 动画方案
1. **像素风格染色**：  
   - 节点按黑白交替染色，初始树边显示为绿色，合法边为灰色。  
   - 每次操作后，所选边变为红色，对手边变为蓝色。

2. **动态集合展示**：  
   - 右侧面板显示剩余合法边数量及奇偶性，高亮当前操作者。

3. **音效与反馈**：  
   - 添加边时播放“连接”音效，游戏结束播放胜利/失败音效。

### 关键代码（Canvas 绘制）
```javascript
// 绘制树节点（8位风格）
function drawNode(x, y, color) {
    ctx.fillStyle = color ? "#000" : "#FFF";
    ctx.fillRect(x*40 + 10, y*40 + 10, 20, 20);
}
// 合法边动态变化
function highlightEdge(i, j) {
    ctx.strokeStyle = "#FF0000";
    ctx.beginPath();
    ctx.moveTo(nodes[i].x, nodes[i].y);
    ctx.lineTo(nodes[j].x, nodes[j].y);
    ctx.stroke();
}
```

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> g[105];
map<pair<int, int>, bool> exist;
vector<pair<int, int>> edges;
bool color[105];

void dfs(int u, int fa) {
    for (int v : g[u]) {
        if (v != fa) {
            color[v] = !color[u];
            dfs(v, u);
        }
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
        exist[{u, v}] = exist[{v, u}] = true;
    }
    dfs(1, 0);
    // 统计合法边
    for (int i = 1; i <= n; ++i)
        for (int j = i+1; j <= n; ++j)
            if (color[i] != color[j] && !exist[{i, j}])
                edges.emplace_back(i, j);
    // 决定先后手
    if (edges.size() % 2) {
        cout << "First" << endl;
        auto [u, v] = edges.back();
        cout << u << " " << v << endl;
        edges.pop_back();
    } else {
        cout << "Second" << endl;
    }
    // 交互处理
    while (!edges.empty()) {
        int u, v; cin >> u >> v;
        if (u == -1) break;
        edges.erase(find(edges.begin(), edges.end(), pair{min(u,v), max(u,v)}));
        auto [x, y] = edges.back();
        cout << x << " " << y << endl;
        edges.pop_back();
    }
    return 0;
}
```

---
处理用时：76.79秒