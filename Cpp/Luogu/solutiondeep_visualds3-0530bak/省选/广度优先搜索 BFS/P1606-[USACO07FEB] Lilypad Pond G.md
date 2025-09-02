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



# 分析报告

## 算法分类
**BFS**

---

## 题解思路与核心难点
### 核心思路
1. **预处理连通块**：利用 DFS/BFS 遍历所有可跳跃的荷叶（原图中的 1），将整个荷叶连通块视为一个「超级节点」。
2. **建图规则**：每个水点（0）或起点（3）通过一次跳跃（马步）能到达的所有位置，若遇到荷叶则递归展开整个连通块，最终将可到达的水点或终点（4）连接为边权 1 的边。
3. **SPFA 最短路计数**：在预处理后的图中，通过 SPFA 计算起点到终点的最短路径长度及方案数。

### 解决难点
- **0 权边问题**：原题中荷叶间跳跃无消耗，直接建图会导致 0 权环，无法正确统计方案数。预处理时将荷叶连通块展开为边权 1 的边，消除 0 权边。
- **方案数统计**：SPFA 松弛时动态更新 `dist` 和 `cnt`，确保路径不重复计数。

---

## 题解评分（≥4星）

1. **D_14134 (⭐⭐⭐⭐⭐)**  
   - **亮点**：DFS 预处理荷叶连通块，邻接表建图清晰，SPFA 实现简洁。  
   - **代码**：通过 `dfs` 函数递归展开荷叶区域，`adde` 构建边权 1 的图。

2. **s_ShotღMaki (⭐⭐⭐⭐)**  
   - **亮点**：详细注释与变量说明，强调 `long long` 必要性，代码可读性强。  
   - **技巧**：将二维坐标编码为一维节点，避免状态混乱。

3. **顾z (⭐⭐⭐⭐)**  
   - **亮点**：复古像素风可视化思路，结合音效与关卡设计增强交互性。  
   - **代码**：`dfs` 预处理后直接调用 SPFA，逻辑分层明确。

---

## 最优思路提炼
- **关键技巧**：将荷叶连通块展开为边权 1 的边，消除 0 权环干扰。
- **数据结构**：二维坐标编码为一维节点（`idx = (i-1)*m + j`），邻接表存图。
- **算法优化**：SPFA 动态松弛时同步更新最短路径数，避免重复计数。

---

## 同类型题目
1. **P1144 最短路计数**：无权图最短路方案数统计。
2. **P1608 路径统计**：带权图最短路计数，需处理重边。
3. **P1979 华容道**：状态转移与预处理建图的综合应用。

---

## 代码片段（D_14134 题解核心）
```cpp
void dfs(int o, int x, int y) { // 预处理荷叶连通块
    b[x][y] = 1;
    for (int k = 0; k < 8; k++) {
        int xx = x + dx[k], yy = y + dy[k];
        if (边界检查跳过...) continue;
        if (mp[xx][yy] == 1) dfs(o, xx, yy); // 递归展开荷叶区域
        else b[xx][yy] = 1, adde(o, p[xx][yy]); // 构建边权1的边
    }
}

void spfa() { // 最短路计数
    memset(d, 63, sizeof(d));
    d[st] = 0, vis[st] = f[st] = 1;
    q.push(st);
    while (!q.empty()) {
        x = q.front(); q.pop();
        for (int k = head[x]; k; k = a[k].next) {
            int v = a[k].to;
            if (d[v] > d[x] + 1) { // 松弛成功
                d[v] = d[x] + 1;
                f[v] = f[x];
                if (!vis[v]) q.push(v);
            } else if (d[v] == d[x] + 1) f[v] += f[x]; // 累加方案数
        }
    }
}
```

---

## 可视化设计
### 动画方案
- **节点状态**：  
  - 红色：起点（3）  
  - 绿色：终点（4）  
  - 蓝色：水（0）  
  - 黄色：荷叶（1）  
  - 黑色：岩石（2）  
- **搜索过程**：  
  1. **预处理阶段**：高亮当前 DFS/BFS 的荷叶连通块，逐步扩展为浅黄色区域。  
  2. **建图阶段**：从每个水点发射箭头到预处理后的可达节点，边权显示为 1。  
  3. **SPFA 阶段**：队列节点标记为橙色，已访问节点渐变为灰色，路径动态绘制为金色线条。

### 复古像素风格
- **Canvas 绘制**：32x32 像素网格，节点用 8 位色块表示，边为单色线条。  
- **音效**：  
  - 访问节点：8-bit "哔"声  
  - 找到路径：胜利音效（上升音阶）  
  - 失败：低沉嗡鸣  
- **自动演示**：按空格切换手动/自动模式，方向键控制单步执行。

---

## 个人心得
- **调试教训**：初始未处理荷叶连通块，直接建图导致方案数多算。  
- **关键顿悟**：荷叶区域应视为整体，预处理后才能正确统计添加的荷叶数。

---
处理用时：74.17秒