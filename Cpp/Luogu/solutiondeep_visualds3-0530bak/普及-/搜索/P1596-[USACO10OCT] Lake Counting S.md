# 题目信息

# [USACO10OCT] Lake Counting S

## 题目描述

Due to recent rains, water has pooled in various places in Farmer John's field, which is represented by a rectangle of N x M (1 <= N <= 100; 1 <= M <= 100) squares. Each square contains either water ('W') or dry land ('.'). Farmer John would like to figure out how many ponds have formed in his field. A pond is a connected set of squares with water in them, where a square is considered adjacent to all eight of its neighbors. Given a diagram of Farmer John's field, determine how many ponds he has.






## 说明/提示

OUTPUT DETAILS: There are three ponds: one in the upper left, one in the lower left, and one along the right side.


## 样例 #1

### 输入

```
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.
```

### 输出

```
3
```

# AI分析结果



## 【算法分类】
**DFS**

---

## 【题解思路与算法要点】

### 核心思路
本题是典型的连通块计数问题，通过 DFS/BFS 遍历所有相连的 'W' 区域。每个水坑由 8 方向相邻的 'W' 组成，每次发现未访问的 'W' 时启动搜索并计数。

### 解决难点
1. **八方向遍历**：需正确处理 8 个相邻方向（上下左右及对角线）的坐标偏移。
2. **访问标记**：必须在搜索过程中即时标记已访问的节点（如将 'W' 改为 '.'），避免重复计数。
3. **边界检查**：确保搜索不越出网格范围。

---

## 【题解评分（≥4星）】

1. **Fractures（DFS/BFS对比）** ⭐⭐⭐⭐⭐  
   - 详细对比 DFS/BFS 的优缺点，提供完整代码和优化思路。
   - 亮点：通过双重循环处理 8 方向，代码清晰易读。

2. **高铁1号（DFS）** ⭐⭐⭐⭐  
   - 使用方向数组简化代码，适合新手理解。
   - 亮点：预处理方向偏移量，代码简洁。

3. **liujiayuan（BFS）** ⭐⭐⭐⭐  
   - 手写队列优化性能，避免 STL 队列的 TLE 问题。
   - 亮点：结构体存储坐标，逻辑清晰。

---

## 【最优思路提炼】

### 关键技巧
1. **DFS 递归标记**：发现 'W' 后立即标记为 '.'，递归访问 8 个方向。
2. **方向数组优化**：预定义 8 个方向的坐标偏移量，简化遍历逻辑。
3. **输入优化**：按行读取字符串避免逐字符处理换行符。

### 核心代码片段（DFS）
```cpp
void dfs(int x, int y) {
    a[x][y] = '.'; // 标记为已访问
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == 'W') {
                dfs(nx, ny); // 递归访问相邻节点
            }
        }
    }
}
```

---

## 【同类型题与算法套路】

### 相似题目
1. **洛谷 P1451 求细胞数量**：4 方向连通块计数。
2. **洛谷 P1162 填涂颜色**：BFS 标记闭合区域。
3. **LeetCode 200. 岛屿数量**：2D 网格中的连通块计数。

### 通用解法
- **网格遍历**：使用双重循环遍历每个单元格。
- **搜索剪枝**：遇到目标时启动搜索并标记，避免重复处理。

---

## 【可视化与算法演示】

### 动画设计
1. **网格渲染**：  
   - 用 Canvas 绘制 N×M 网格，'W' 显示为蓝色方块，'.' 为灰色。
   - 当前访问节点高亮为红色，已访问节点渐变为灰色。

2. **搜索过程**：  
   - **DFS**：递归时用栈动画展示，每次深入一个方向。
   - **BFS**：队列扩展动画，节点按层级逐渐变红。

3. **复古风格**：  
   - **8-bit 像素风**：节点用 16×16 像素块，音效采用芯片音乐。
   - **音效触发**：访问节点时播放短促“哔”声，计数时播放胜利音效。

### 交互功能
- **步进控制**：支持暂停/继续/单步执行。
- **模式切换**：DFS/BFS 对比演示，展示遍历顺序差异。

---

## 【推荐题目】
1. **P1451 求细胞数量**（4 方向连通块）  
2. **P1162 填涂颜色**（BFS 标记闭合区域）  
3. **P1141 01迷宫**（连通块预处理）

---

## 【个人心得摘录】
> **Fractures 的调试经验**：  
> “BFS 使用 STL 队列会 TLE，手写队列后通过。优化后代码效率显著提升，适合大数据量。”

---

## 【可视化实现核心逻辑（JS片段）】
```javascript
// Canvas 绘制网格
function drawGrid(grid) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            ctx.fillStyle = grid[i][j] === 'W' ? '#00f' : '#888';
            ctx.fillRect(j * 20, i * 20, 18, 18);
        }
    }
}

// DFS 动画演示
async function animateDFS(x, y) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] !== 'W') return;
    grid[x][y] = '.'; // 标记访问
    drawGrid(grid);
    await sleep(200); // 延迟展示过程
    for (let dx = -1; dx <= 1; dx++) {
        for (let dy = -1; dy <= 1; dy++) {
            await animateDFS(x + dx, y + dy);
        }
    }
}
```

---
处理用时：73.22秒