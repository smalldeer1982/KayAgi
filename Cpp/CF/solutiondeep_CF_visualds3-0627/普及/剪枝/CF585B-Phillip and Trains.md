# 题目信息

# Phillip and Trains

## 题目描述

The mobile application store has a new game called "Subway Roller".

The protagonist of the game Philip is located in one end of the tunnel and wants to get out of the other one. The tunnel is a rectangular field consisting of three rows and $ n $ columns. At the beginning of the game the hero is in some cell of the leftmost column. Some number of trains rides towards the hero. Each train consists of two or more neighbouring cells in some row of the field.

All trains are moving from right to left at a speed of two cells per second, and the hero runs from left to right at the speed of one cell per second. For simplicity, the game is implemented so that the hero and the trains move in turns. First, the hero moves one cell to the right, then one square up or down, or stays idle. Then all the trains move twice simultaneously one cell to the left. Thus, in one move, Philip definitely makes a move to the right and can move up or down. If at any point, Philip is in the same cell with a train, he loses. If the train reaches the left column, it continues to move as before, leaving the tunnel.

Your task is to answer the question whether there is a sequence of movements of Philip, such that he would be able to get to the rightmost column.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585B/309f950d64c5a7d55f4952aae670b86363abc76b.png)

## 说明/提示

In the first set of the input of the first sample Philip must first go forward and go down to the third row of the field, then go only forward, then go forward and climb to the second row, go forward again and go up to the first row. After that way no train blocks Philip's path, so he can go straight to the end of the tunnel.

Note that in this problem the challenges are restricted to tests that contain only one testset.

## 样例 #1

### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...
```

### 输出

```
YES
NO
```

# AI分析结果



---

## 算法分类
**广度优先搜索 (BFS) / 深度优先搜索 (DFS)**

---

## 题解思路与核心难点

### 核心思路
**相对运动转换**：将火车的左移转换为人物右移，简化移动逻辑。每回合人物实际需向右移动 3 格（1 步向右 + 2 步火车等效移动），同时允许上下换行，需保证路径中无火车。

### 算法要点
1. **预处理障碍**：将火车位置标记为障碍物数组 `a[i][j]`。
2. **移动三步检测**：每次移动需检查三个连续格子是否安全（当前行向右 1 格，换行后向右 2 格）。
3. **剪枝优化**：使用 `vis` 数组避免重复访问同一状态。

### 解决难点
- **火车移动同步性**：通过相对运动转换消除实时更新火车位置的计算。
- **碰撞检测**：三步移动中任何一格存在火车则路径非法。
- **边界处理**：换行时确保不越界（行号保持在 1~3）。

---

## 题解评分（≥4星）

1. **lraM41（DFS）**  
   ⭐⭐⭐⭐  
   - 亮点：代码简洁，利用相对运动转换和递归剪枝。
   - 关键代码：检查三格安全后递归 `dfs(i, y+3)`。

2. **installb（BFS）**  
   ⭐⭐⭐⭐  
   - 亮点：队列实现状态扩展，显式处理三步移动。
   - 关键代码：分步检查 `tx = aa.lin + 1/2/3` 的障碍。

3. **Jinzixun（动态规划）**  
   ⭐⭐⭐⭐  
   - 亮点：反向递推预处理路径可行性。
   - 关键代码：从终点反向推导 `dp[i][j] |= dp[i+d][j+3]`。

---

## 最优思路提炼

1. **相对运动转换**  
   将火车的左移两步等价于人物右移两步，简化碰撞检测逻辑。

2. **三步移动检测**  
   ```cpp
   if (!a[i][y+1] && !a[i][y+2] && !a[i][y+3]) dfs(i, y+3);
   ```
   确保移动路径上无火车。

3. **状态剪枝**  
   使用 `vis` 数组记录访问状态，避免重复搜索相同位置。

---

## 类似题目推荐

1. **[P1131 后缀表达式](https://www.luogu.com.cn/problem/P1131)**  
   - 相似点：状态转移与路径搜索。

2. **[P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)**  
   - 相似点：BFS 处理连通区域。

3. **[P1120 小木棍](https://www.luogu.com.cn/problem/P1120)**  
   - 相似点：DFS 剪枝优化。

---

## 核心代码实现

**lraM41 的 DFS 实现（关键部分）**  
```cpp
void dfs(int x, int y) {
    if (y >= n) { f = 1; return; }
    if (vis[x][y] || f) return;
    vis[x][y] = 1;
    if (a[x][y+1]) return; // 碰撞检测
    for (int i = x-1; i <= x+1; i++) { // 上下换行
        if (i < 1 || i > 3) continue;
        if (!a[i][y+1] && !a[i][y+2] && !a[i][y+3])
            dfs(i, y+3); // 三步移动
    }
}
```

---

## 可视化设计

### 动画演示方案
1. **网格绘制**：Canvas 绘制 3 行 × n 列的网格，人物用绿色方块，火车用红色方块。
2. **移动高亮**：当前检测的三个格子用黄色高亮，安全路径显示为蓝色箭头。
3. **步进控制**：支持暂停/继续，单步执行观察 DFS/BFS 的递归/队列变化。

### 复古游戏化元素
- **像素风格**：使用 16 色调色板，人物和火车用 8-bit 风格精灵图。
- **音效设计**：
  - **移动成功**：短促 "beep" 音效。
  - **碰撞失败**：低音 "buzz"。
  - **到达终点**：胜利旋律（8-bit 音阶）。

### 自动演示模式
- **AI 决策**：按 BFS 队列顺序自动播放移动路径。
- **积分系统**：每安全移动三步得 10 分，碰撞扣 5 分。

---

## 个人心得摘录

> **lraM41**：  
> “根据相对论简化火车移动逻辑，直接判断三步路径是否安全即可。”  
> **调试经验**：初始未考虑换行后两步的障碍检测，导致碰撞误判。

> **installb**：  
> “BFS 必须清空队列再退出，否则多组数据会残留状态。”  
> **优化点**：显式分步检测 `tx+1`、`tx+2` 提高可读性。

---
处理用时：72.83秒