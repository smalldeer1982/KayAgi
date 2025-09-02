# 题目信息

# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 样例 #1

### 输入

```
1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
```

### 输出

```
9
```

# AI分析结果



# 算法分类  
**BFS + 数学规律**

---

## 题解思路与核心难点分析  
### 核心思路  
- **BFS预处理**：当 `k ≤ step` 时，用 BFS 暴力扩展可达区域。  
- **数学公式推导**：当 `k > step` 时，利用等差数列公式计算后续步数的可达数。  
- **关键验证**：通过打表发现，当 `k ≥ 5` 时，每步新增可达格子数为定值 28，公式为 `28k - 20`。

### 解决难点  
1. **无限棋盘处理**：常规 BFS 无法处理无限扩展，通过观察可达区域的增长模式，发现等差数列规律。  
2. **障碍物影响**：假设障碍物远离原点（符合题目数据范围限制），不影响增长模式的稳定性。  
3. **公式验证**：通过数学归纳法或论文引用（如题解引用的米勒-法恩斯沃斯论文）验证公式正确性。

---

## 题解评分（≥4星）  
1. **ttq012（5星）**  
   - 思路清晰，代码简洁，结合 BFS 和数学公式。  
   - 关键亮点：通过 `step=456` 暴力与公式切换，高效处理大范围数据。  
2. **封禁用户（4星）**  
   - 提供数学证明思路，分区域讨论增长模式。  
   - 不足：图示和分区域逻辑较复杂，代码未完整展示。  
3. **pufanyi（4星）**  
   - 通过打表验证等差数列，代码完整展示暴力与公式结合。  
   - 亮点：验证删除格子对规律的影响，增强算法鲁棒性。

---

## 最优思路提炼  
1. **暴力与数学结合**：  
   - 对 `k` 较小的情况，用 BFS 计算每一步的可达格子数。  
   - 对 `k` 较大的情况，利用公式 `28k - 20` 直接计算。  
2. **打表验证模式**：  
   - 输出前若干步的可达数差值，观察是否稳定为 28。  
3. **坐标偏移处理**：  
   - 将棋盘原点平移（如 `(1001, 1001)`）避免负数坐标。

---

## 同类型题推荐  
1. **CF 57E**：骑士在无限棋盘上的可达区域数（本题原题）。  
2. **洛谷 P2730**：马的遍历（有限棋盘 BFS）。  
3. **LeetCode 688**：骑士在棋盘上的概率（动态规划+有限步数）。

---

## 代码核心实现  
```cpp
// BFS预处理部分（以 pufanyi 的代码为例）
void bfs(int x, int y) {
    queue<Node> q;
    q.push({x, y});
    vis[x][y] = 1;
    while (!q.empty()) {
        Node u = q.front(); q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = u.x + dx[i], ny = u.y + dy[i];
            if (vis[nx][ny] || is_blocked(nx, ny)) continue;
            vis[nx][ny] = vis[u.x][u.y] + 1;
            q.push({nx, ny});
        }
    }
}

// 公式计算部分
if (k <= 500) {
    // 累加前 k 步的 BFS 结果
} else {
    long long base = ans[500];
    long long d = 28; // 等差数列公差
    long long cnt = (k - 500) * d;
    total = base + cnt * (k - 500 + 1) / 2;
}
```

---

## 可视化设计  
### 复古像素风格动画  
1. **棋盘绘制**：  
   - 使用 Canvas 绘制无限棋盘的局部（中心区域），骑士用 8x8 像素方块表示。  
   - 颜色方案：可达区域用绿色渐变，障碍物用红色，当前扩展的格子高亮为黄色。  
2. **动画流程**：  
   - **BFS 扩展**：每帧显示队列中的一个节点，扩展 8 个方向，新增格子闪烁提示。  
   - **公式切换**：当步数超过阈值时，屏幕显示 "Formula Activated!"，并动态绘制等差数列增长曲线。  
3. **音效与交互**：  
   - 骑士移动时播放“马蹄声”音效（8 位风格）。  
   - 按空格键暂停/继续，方向键调整动画速度。

---

## 个人心得  
- **打表找规律**是解决复杂问题的有效捷径，尤其当数学证明困难时。  
- **坐标系平移**技巧可避免负数索引，简化代码实现。  
- **边界验证**：删除的障碍物若靠近原点可能破坏规律，需特殊处理。

---
处理用时：58.00秒