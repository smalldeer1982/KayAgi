# 题目信息

# [USACO18FEB] New Barns P

## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。

## 说明/提示

【数据范围】  

对于 $100\%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu

## 样例 #1

### 输入

```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2```

### 输出

```
0
2
1
```

# AI分析结果



### 唯一算法分类
树的直径维护

---

### 综合分析与结论
**核心思路**：利用树的直径性质（任意点的最远点必为直径端点），通过动态维护连通块的直径端点实现高效查询。

**解决难点**：
1. **动态维护直径**：每次合并时，新直径端点只能来源于原端点与新节点的组合，避免枚举所有可能路径。
2. **高效距离计算**：通过离线构建树结构并预处理 LCA，用 `depth[u] + depth[v] - 2*depth[lca(u,v)]` 公式快速计算距离。

**可视化设计**：
- **动画演示**：用不同颜色标记当前操作节点、直径端点、合并路径。每次合并时高亮四个候选端点并显示距离计算过程。
- **复古像素风格**：用 8-bit 风格绘制树结构，节点显示为方块，连接线为直线。合并时播放经典“连接”音效，查询时显示路径动画。
- **自动演示模式**：模拟贪吃蛇式移动，逐步展示新节点连接和直径更新逻辑。

---

### 题解清单（≥4星）
1. **暴力出奇迹（5星）**
   - **亮点**：离线预处理 LCA + 并查集维护直径端点，代码简洁高效。
   - **代码片段**：
     ```cpp
     void merge(int x, int y) {
         x = find(x), y = find(y);
         int a = d[x][0], b = d[x][1], c = d[y][0], d_ = d[y][1];
         int max_len = max({dis(a,b), dis(a,c), dis(a,d_), dis(b,c), dis(b,d_), dis(c,d_)});
         // 更新新直径端点...
     }
     ```

2. **Karry5307（4星）**
   - **亮点**：LCT 实现动态直径维护，适合在线场景。

3. **LPA20020220（4星）**
   - **亮点**：简洁的并查集 + LCA 组合，强调直径端点性质。

---

### 最优思路提炼
**关键技巧**：
1. **直径端点性质**：任意点的最远点必为直径端点，无需枚举所有节点。
2. **离线预处理**：先建完整棵树再处理操作，避免动态维护 LCA 的复杂度。
3. **四端点枚举法**：合并时只需检查两树原直径端点的六种组合。

---

### 相似题目推荐
1. **P3304 [SDOI2013] 森林** - 动态维护树的直径与 LCA。
2. **P4381 [IOI2008] Island** - 基环树直径的扩展应用。
3. **P1099 [NOIP2007 提高组] 树网的核** - 树直径性质的综合应用。

---

### 可视化算法演示
```javascript
// 伪代码：Canvas绘制树结构并动态更新直径
class TreeVisualizer {
    constructor(canvas) {
        this.nodes = new Map(); // 节点坐标
        this.links = [];        // 边集合
        this.diameter = [];     // 当前直径端点
    }

    addNode(u, parent) {
        // 绘制新节点并连接父节点
        if (parent !== -1) this.links.push({u, parent});
        this.nodes.set(u, calculatePosition(u, parent));
        this.updateDiameter(u);
    }

    updateDiameter(u) {
        // 检查新节点是否成为直径端点
        const [a, b] = this.diameter;
        const d1 = distance(a, b), d2 = distance(a, u), d3 = distance(b, u);
        if (d2 > d1 && d2 >= d3) this.diameter = [a, u];
        else if (d3 > d1 && d3 >= d2) this.diameter = [b, u];
    }
}
```

---

### 核心代码实现（暴力出奇迹题解）
```cpp
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5 + 5, LOG = 20;
vector<int> G[N];
int dep[N], fa[N][LOG], root[N], d[N][2], q_cnt;

void dfs(int u, int f) {
    fa[u][0] = f;
    for (int i = 1; i < LOG; ++i) 
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int v : G[u]) if (v != f) 
        dep[v] = dep[u] + 1, dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = LOG-1; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    for (int i = LOG-1; i >= 0; --i)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int dis(int u, int v) { 
    return dep[u] + dep[v] - 2 * dep[lca(u, v)]; 
}

void merge(int x, int y) {
    x = root[x], y = root[y];
    int a = d[x][0], b = d[x][1], c = d[y][0], d_ = d[y][1];
    int max_d = max({dis(a,b), dis(a,c), dis(a,d_), dis(b,c), dis(b,d_)});
    // 更新新直径端点...
}

int main() {
    // 离线处理操作，构建树结构
    // 处理查询时直接取当前连通块的直径端点计算
}
```

---
处理用时：103.14秒