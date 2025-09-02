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



## 算法分类
**最短路计数 + 预处理建图**

---

## 综合分析与结论

### 核心思路
1. **预处理建图**：  
   - 对每个水格子（0）或起点（3）进行 DFS/BFS，找到其通过马步跳能到达的所有位置（需放置 1 个荷叶）。  
   - 将起点到这些位置建边，边权为 1（代表放置 1 个荷叶）。  
   - 原有荷叶（1）视为通路，递归处理其跳跃可达区域，避免出现 0 权边导致的环路。

2. **最短路计数**：  
   - 使用 SPFA 或 Dijkstra 计算起点到终点的最短路，并在松弛过程中维护路径数量。  
   - 每次找到更短路径时重置计数，路径等长时累加计数。

### 解决难点
- **原有荷叶的处理**：通过 DFS 将荷叶连通区域视为一个整体，避免多次跳跃导致重复计算边权。  
- **0 权边问题**：预处理后所有边权均为 1，确保最短路算法正确性。  
- **方案数统计**：在松弛时动态维护路径数，需注意数值类型用 `long long`。

---

## 题解评分（≥4星）

1. **D_14134（⭐⭐⭐⭐⭐）**  
   - 亮点：通过 DFS 预处理建图，代码简洁高效，SPFA 实现清晰。  
   - 关键代码：  
     ```cpp
     void dfs(int o, int x, int y) {
         for (所有马步跳方向) {
             if (遇到荷叶) 递归扩展;
             else 添加边 o → (nx, ny);
         }
     }
     ```

2. **s_ShotღMaki（⭐⭐⭐⭐⭐）**  
   - 亮点：详细注释 + 邻接表建图，强调 `long long` 的必要性。  
   - 关键代码：  
     ```cpp
     void This_is_for_you(int num, int x, int y) {
         for (所有马步跳方向) {
             if (遇到荷叶) 递归;
             else 添加边 num → 目标点;
         }
     }
     ```

3. **顾z（⭐⭐⭐⭐）**  
   - 亮点：像素风格示意图辅助理解编号方式，代码可读性强。  
   - 关键代码：  
     ```cpp
     void dfs(int nx, int ny, int tx, int ty) {
         if (遇到荷叶) 递归;
         else 添加边 nx → tx;
     }
     ```

---

## 最优思路提炼

### 关键技巧
- **DFS 预处理**：将荷叶连通区域一次性处理，避免后续计算中的环和重复边权。  
- **边权统一为 1**：保证所有跳跃操作对应相同代价，简化最短路逻辑。  
- **动态维护计数**：在 SPFA 松弛过程中同步更新路径数，避免二次遍历。

### 类似题目
1. **P1144 最短路计数**（基础最短路计数）  
2. **P1608 路径统计**（带权最短路计数）  
3. **P1979 华容道**（复杂预处理建图 + BFS）

---

## 可视化设计

### 算法演示方案
1. **网格绘制**：  
   - 用 Canvas 绘制 30x30 网格，不同颜色标记起点、终点、岩石、水和荷叶。  
   - **当前处理节点**：高亮为红色，扩展中的节点为黄色。

2. **跳跃动画**：  
   - 显示马步跳跃路径，新增荷叶时用绿色闪烁效果。  
   - 边权为 1 的边用蓝色线条连接。

3. **SPFA 过程**：  
   - 队列节点用队列动画展示，松弛成功的边用橙色高亮。  
   - 实时更新每个节点的最短距离和路径数。

### 复古像素风格
- **8-bit 音效**：  
  - 跳跃时播放 `jump.wav`（8-bit 短音效）。  
  - 找到最短路径时播放 `success.wav`（上扬音调）。  
- **像素颜色**：  
  - 水：浅蓝色（#6CF），荷叶：绿色（#3C3），岩石：灰色（#888）。

### 交互功能
- **步进控制**：支持暂停/继续、单步执行。  
- **速度调节**：拖动条控制动画速度（1x~5x）。  
- **自动演示**：AI 模式自动完成预处理和 SPFA。

---

## 核心代码片段

### 预处理建图（D_14134）
```cpp
void dfs(int o, int x, int y) {
    b[x][y] = 1;
    for (int k = 0; k < 8; k++) {
        int xx = x + dx[k], yy = y + dy[k];
        if (越界或已访问) continue;
        if (mp[xx][yy] == 1) dfs(o, xx, yy); // 荷叶递归处理
        else {
            b[xx][yy] = 1;
            adde(o, p[xx][yy]); // 添加边 o → (xx,yy)
        }
    }
}
```

### SPFA 计数（s_ShotღMaki）
```cpp
void spfa() {
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (遍历邻接表) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                cnt[v] = cnt[u]; // 重置计数
            } else if (dis[v] == dis[u] + 1) {
                cnt[v] += cnt[u]; // 累加计数
            }
        }
    }
}
```

---

## 个人心得摘录
- **D_14134**：  
  > "原有荷叶会让最短路计数出错，必须预处理跳过它们。"  
- **wurzang**：  
  > "写了个并查集挂了，最后 DFS 十几次才过样例，心态爆炸。"  
- **HRLYB**：  
  > "建图是这类题的灵魂，想清楚每个状态如何转移。"

---

通过上述分析和实现，可系统解决此类「预处理建图 + 最短路计数」问题，核心在于正确处理原有障碍物的连通性，保证边权统一后简化计算。

---
处理用时：82.66秒