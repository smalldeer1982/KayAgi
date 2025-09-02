# 题目信息

# Three States

## 题目描述

The famous global economic crisis is approaching rapidly, so the states of Berman, Berance and Bertaly formed an alliance and allowed the residents of all member states to freely pass through the territory of any of them. In addition, it was decided that a road between the states should be built to guarantee so that one could any point of any country can be reached from any point of any other State.

Since roads are always expensive, the governments of the states of the newly formed alliance asked you to help them assess the costs. To do this, you have been issued a map that can be represented as a rectangle table consisting of $ n $ rows and $ m $ columns. Any cell of the map either belongs to one of three states, or is an area where it is allowed to build a road, or is an area where the construction of the road is not allowed. A cell is called passable, if it belongs to one of the states, or the road was built in this cell. From any passable cells you can move up, down, right and left, if the cell that corresponds to the movement exists and is passable.

Your task is to construct a road inside a minimum number of cells, so that it would be possible to get from any cell of any state to any cell of any other state using only passable cells.

It is guaranteed that initially it is possible to reach any cell of any state from any cell of this state, moving only along its cells. It is also guaranteed that for any state there is at least one cell that belongs to it.

## 样例 #1

### 输入

```
4 5
11..2
#..22
#.323
.#333```

### 输出

```
2```

## 样例 #2

### 输入

```
1 5
1#2#3
```

### 输出

```
-1
```

# AI分析结果



# 算法分类：广度优先搜索（BFS）/ 多源最短路径

## 题解思路与算法要点
**核心思路**：  
1. **多源最短路径预处理**：使用 01BFS 计算三个国家到每个网格点的最短距离。国家领土边权为 0，道路修建边权为 1，不可通行区域跳过。
2. **交汇点枚举**：遍历所有网格点，计算三个国家到该点的距离之和。若该点为道路（`.`），需减 2（避免重复计算修建次数）。
3. **两两路径组合**：计算国家间两两最短路径，取三种组合的最小和（如 `d12 + d23`、`d13 + d23` 等）。

**解决难点**：  
1. **动态边权处理**：通过 01BFS 将国家领土视为 0 权边，道路视为 1 权边，优化搜索效率。
2. **重复计算修正**：交汇点的类型（国家/道路）需不同处理，确保最终代价正确。
3. **全情况覆盖**：同时考虑「三路交汇」与「两两连接」两种最优路径场景。

## 题解评分（≥4星）
1. **AKPC（5星）**  
   - 亮点：完整实现 01BFS 算法，代码结构清晰，预处理逻辑高效。
   - 优化：双端队列处理不同边权，显著提升搜索速度。

2. **MyukiyoMekya（4.5星）**  
   - 亮点：同时考虑交汇点与两两路径组合，覆盖所有可能情况。
   - 优化：代码模块化设计，使用 `checkmin` 简化最小值更新。

3. **wxzzzz（4星）**  
   - 亮点：独立计算两两最短路径，结构清晰易扩展。
   - 优化：分离交汇点枚举与路径组合逻辑，提升可读性。

## 最优思路与技巧提炼
1. **01BFS 动态处理**：双端队列实现，0 权边插队首，1 权边插队尾，时间复杂度降至 O(nm)。
2. **状态复用优化**：预处理国家到所有点的距离，避免重复计算。
3. **多情况覆盖策略**：通过枚举交汇点 + 两两路径组合，确保所有最优解可能被捕获。

## 类似算法套路
- **多源最短路径**：适用于网格中多个起点到各点的最短距离计算（如 [CF 1520G]）。
- **动态边权 BFS**：处理边权仅两种值的图搜索问题（如 [洛谷 P4667]）。

## 推荐相似题目
1. P4667 [SCOI2007] 棋盘（动态边权 BFS）
2. P1948 [USACO08JAN] Telephone Lines（分层图最短路）
3. P6062 [USACO05JAN] Muddy Fields（二分图匹配 + 网格覆盖）

## 个人心得摘录
- **AKPC**：强调 01BFS 的本质是 Dijkstra 的优化，启发式理解数据结构选择。
- **MyukiyoMekya**：通过归纳法证明最优交汇点的存在性，强化逻辑严谨性。
- **wxzzzz**：调试时输出各国家距离矩阵，直观验证预处理正确性。

## 可视化与算法演示
**核心逻辑动画设计**：
1. **网格绘制**：用 Canvas 绘制 n×m 网格，不同颜色区分国家、道路、障碍。
2. **BFS 扩散效果**：以水波纹动画展示三个国家的距离扩散过程，同步显示当前处理队列。
3. **交汇点高亮**：闪烁显示候选交汇点，动态计算并显示三距离之和。
4. **路径组合对比**：并排展示「交汇点模式」与「两两组合模式」的路径连接动画。

**复古游戏化实现**：
- **8-bit 像素风格**：使用 16 色调色板，国家用红/绿/蓝方块，道路为灰色，障碍为黑色。
- **音效触发**：
  - `01BFS 扩散`：播放短促电子音（不同音高区分 0/1 边权）。
  - **最优解发现**：播放经典 FC 过关音效。
- **自动演示模式**：按空格切换手动/自动播放，AI 自动遍历关键步骤。

**关键代码片段（JS 伪代码）**：
```javascript
// 01BFS 实现片段
function bfs(grid, startPoints, distMatrix) {
  let deque = new Deque();
  startPoints.forEach(p => { 
    deque.unshift(p);
    distMatrix[p.x][p.y] = 0;
  });

  while (!deque.isEmpty()) {
    let {x, y} = deque.popFront();
    for (let dir of directions) {
      let nx = x + dir[0], ny = y + dir[1];
      if (!isValid(nx, ny)) continue;
      
      let cost = grid[nx][ny] === '.' ? 1 : 0;
      if (distMatrix[nx][ny] > distMatrix[x][y] + cost) {
        distMatrix[nx][ny] = distMatrix[x][y] + cost;
        cost === 0 ? deque.unshift({x: nx, y: ny}) 
                   : deque.push({x: nx, y: ny});
      }
    }
  }
}
```

**交互面板功能**：
- **速度控制**：滑动条调节动画速度（0.5x~5x）。
- **模式切换**：高亮显示当前计算模式（交汇点/两两组合）。
- **单步调试**：按 `→` 键逐步执行 BFS 扩散步骤。

---
处理用时：107.31秒