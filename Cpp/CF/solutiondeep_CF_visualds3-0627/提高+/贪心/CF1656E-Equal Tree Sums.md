# 题目信息

# Equal Tree Sums

## 题目描述

You are given an undirected unrooted tree, i.e. a connected undirected graph without cycles.

You must assign a nonzero integer weight to each vertex so that the following is satisfied: if any vertex of the tree is removed, then each of the remaining connected components has the same sum of weights in its vertices.

## 说明/提示

In the first case, when removing vertex $ 1 $ all remaining connected components have sum $ 5 $ and when removing vertex $ 3 $ all remaining connected components have sum $ 2 $ . When removing other vertices, there is only one remaining connected component so all remaining connected components have the same sum.

## 样例 #1

### 输入

```
2
5
1 2
1 3
3 4
3 5
3
1 2
1 3```

### 输出

```
-3 5 1 2 2
1 1 1```

# AI分析结果



---

## 综合分析与结论

### 题目核心思路
1. **核心构造策略**：利用树的二分图性质进行黑白染色，将黑色节点权值设为度数，白色节点设为负度数。
2. **正确性证明**：
   - 整棵树权值和为 $0$（每条边贡献 $+1$ 和 $-1$）。
   - 删除任意节点 $u$ 后，每条与 $u$ 相连的边会分离出一个连通块，其权值和为 $\pm1$。
3. **贪心策略**：通过染色快速确定正负号，直接根据度数计算权值，无需复杂动态规划。

### 解决难点
- **构造思路的发现**：树的结构特性（二分图）与权值构造的关联性。
- **连通块和的证明**：删除节点后，相邻连通块的权值和均为 $\pm1$，满足题目要求。

---

## 题解清单（≥4星）

### 1. I_am_Accepted（★★★★☆）
- **核心亮点**：简洁直接，利用黑白染色和度数构造权值，代码仅需一次DFS。
- **代码可读性**：高，无冗余逻辑。
- **关键代码**：
  ```cpp
  dfs(1,0);
  for(int i=1;i<=n;i++) 
    cout << (col[i] ? deg[i] : -deg[i]) << " ";
  ```

### 2. Shunpower（★★★★★）
- **核心亮点**：数学推导严谨，通过子树和 $sum_x = (-1)^{d_x}$ 构造权值。
- **实践价值**：提供完整的数学归纳过程，便于理解构造正确性。
- **关键公式**：
  $$
  a_x = deg_x \cdot (-1)^{d_x}
  $$

### 3. E1_de5truct0r（★★★★☆）
- **核心亮点**：代码清晰，直接通过DFS染色并计算权值。
- **个人心得**：强调“父亲和儿子颜色相反”的二分图特性，简化证明过程。

---

## 最优思路提炼

### 关键技巧
1. **二分图染色**：利用树的天然二分图性质确定正负号。
2. **度数映射**：权值绝对值等于节点度数，确保删除后各连通块和为 $\pm1$。
3. **全局平衡**：整棵树权值和为 $0$，保证父连通块与子连通块的对称性。

### 数学归纳
- 设删除节点 $u$ 的度数为 $d$，其相邻边将分割出 $d$ 个连通块。
- 每个连通块权值和为 $+1$（若 $u$ 是黑节点）或 $-1$（若白节点）。

---

## 同类型题目推荐
1. **P1355 树的染色**：类似二分图染色与权值分配。
2. **P2582 函数的美**：利用树结构性质构造特定函数。
3. **CF741D Arpa’s letter-marked tree**：基于DFS的树结构处理。

---

## 可视化与算法演示

### 贪心策略动画设计
1. **像素化树结构**：
   - 节点用矩形表示，内部显示度数。
   - 黑色节点用蓝色像素块，白色用红色。
2. **交互操作**：
   - **点击节点**：删除该节点，高亮各连通块。
   - **自动模式**：依次删除所有节点，展示结果。
3. **音效反馈**：
   - 删除节点时播放“切割”音效。
   - 正确时播放上升音阶，错误时蜂鸣声。

### 核心代码片段（JavaScript）
```javascript
// 8位像素风格渲染树
function drawTree() {
  ctx.fillStyle = "#2D2D2D"; // 背景色
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  nodes.forEach(node => {
    ctx.fillStyle = node.color === 0 ? "#3498db" : "#e74c3c"; // 蓝/红
    ctx.fillRect(node.x*50, node.y*50, 40, 40); // 像素块
    ctx.fillStyle = "white";
    ctx.fillText(node.deg, node.x*50+15, node.y*50+25); // 显示度数
  });
}

// 删除节点动画
function deleteNode(node) {
  playSound("cut"); // 播放切割音效
  node.deleted = true;
  highlightComponents(node); // 高亮连通块
}
```

---

## 代码实现（C++）

### 核心代码（I_am_Accepted 改进版）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector<int> g[N];
int col[N], deg[N];

void dfs(int u, int fa) {
  col[u] = ~col[fa] ? !col[fa] : 0; // 根节点初始化为0
  for(int v : g[u]) 
    if(v != fa) dfs(v, u);
}

void solve() {
  int n; cin >> n;
  for(int i=1; i<=n; ++i) g[i].clear(), deg[i] = 0;
  for(int i=1; i<n; ++i) {
    int u, v; cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
    ++deg[u], ++deg[v];
  }
  memset(col, -1, sizeof col);
  dfs(1, -1);
  for(int i=1; i<=n; ++i) 
    cout << (col[i] ? deg[i] : -deg[i]) << " \n"[i==n];
}

int main() {
  int T; cin >> T;
  while(T--) solve();
}
```

### 代码说明
- **DFS染色**：从根节点开始交替染色。
- **权值计算**：直接根据颜色和度数输出。
- **时间复杂度**：$O(n)$，一次DFS遍历。

---

## 个人心得摘录
> "将问题转化为已知的树结构特性（如二分图），往往能快速找到突破口。" —— Shunpower  
> "构造题的关键在于发现模式，而非复杂计算。" —— E1_de5truct0r

---

## 总结
本题通过二分图染色与度数映射的巧妙结合，实现了线性复杂度的构造方案。其核心在于利用树的结构特性，将看似复杂的条件转化为简单的符号分配问题。可视化设计通过像素风格和音效反馈，可直观展示算法正确性，增强理解。

---
处理用时：71.58秒