# 题目信息

# Smooth Sailing (Easy Version)

## 题目描述

The only difference between the two versions of this problem is the constraint on $ q $ . You can make hacks only if both versions of the problem are solved.

Thomas is sailing around an island surrounded by the ocean. The ocean and island can be represented by a grid with $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The position of a cell at row $ r $ and column $ c $ can be represented as $ (r, c) $ . Below is an example of a valid grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/516df36ca6ac022124866d4043411e04ed0cf48c.png) Example of a valid gridThere are three types of cells: island, ocean and underwater volcano. Cells representing the island are marked with a '\#', cells representing the ocean are marked with a '.', and cells representing an underwater volcano are marked with a 'v'. It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is also guaranteed that the set of all island cells forms a single connected component $ ^{\dagger} $ and the set of all ocean cells and underwater volcano cells forms a single connected component. Additionally, it is guaranteed that there are no island cells at the edge of the grid (that is, at row $ 1 $ , at row $ n $ , at column $ 1 $ , and at column $ m $ ).

Define a round trip starting from cell $ (x, y) $ as a path Thomas takes which satisfies the following conditions:

- The path starts and ends at $ (x, y) $ .
- If Thomas is at cell $ (i, j) $ , he can go to cells $ (i+1, j) $ , $ (i-1, j) $ , $ (i, j-1) $ , and $ (i, j+1) $ as long as the destination cell is an ocean cell or an underwater volcano cell and is still inside the grid. Note that it is allowed for Thomas to visit the same cell multiple times in the same round trip.
- The path must go around the island and fully encircle it. Some path $ p $ fully encircles the island if it is impossible to go from an island cell to a cell on the grid border by only traveling to adjacent on a side or diagonal cells without visiting a cell on path $ p $ . In the image below, the path starting from $ (2, 2) $ , going to $ (1, 3) $ , and going back to $ (2, 2) $ the other way does not fully encircle the island and is not considered a round trip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/587237f643ee9a450f570eb64a27b00d982a357b.png) Example of a path that does not fully encircle the islandThe safety of a round trip is the minimum Manhattan distance $ ^{\ddagger} $ from a cell on the round trip to an underwater volcano (note that the presence of island cells does not impact this distance).

You have $ q $ queries. A query can be represented as $ (x, y) $ and for every query, you want to find the maximum safety of a round trip starting from $ (x, y) $ . It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

 $ ^{\dagger} $ A set of cells forms a single connected component if from any cell of this set it is possible to reach any other cell of this set by moving only through the cells of this set, each time going to a cell with a common side.

 $ ^{\ddagger} $ Manhattan distance between cells $ (r_1, c_1) $ and $ (r_2, c_2) $ is equal to $ |r_1 - r_2| + |c_1 - c_2| $ .

## 说明/提示

For the first example, the image below shows an optimal round trip starting from $ (1, 1) $ . The round trip has a safety of $ 3 $ as the minimum Manhattan distance from a cell on the round trip to an underwater volcano is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) Example of an optimal round tripFor the fourth example, remember that it is allowed for Thomas to visit the same cell multiple times in the same round trip. For example, doing so is necessary for the round trip starting from $ (7, 6) $ .

## 样例 #1

### 输入

```
9 9 3
.........
.........
....###..
...v#....
..###....
...##...v
...##....
.........
v........
1 1
9 1
5 7```

### 输出

```
3
0
3```

## 样例 #2

### 输入

```
3 3 5
..v
.#.
...
1 2
1 3
2 3
2 1
3 2```

### 输出

```
0
0
0
0
0```

## 样例 #3

### 输入

```
14 13 5
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
1 1
7 7
5 6
4 10
13 6```

### 输出

```
3
0
1
0
2```

## 样例 #4

### 输入

```
10 11 4
...........
..#######..
..#..#..#..
..#.....#..
..#..v..#..
..#.###.#..
..#.#.#.#..
..#...#.#..
..#####.#..
...........
7 6
3 7
6 8
1 1```

### 输出

```
1
2
3
4```

# AI分析结果



# 算法分类
**BFS**

---

# 题解思路与难点分析

## 核心思路
采用**二分答案 + BFS验证**的策略：
1. **预处理**：多源BFS计算每个点到最近火山的曼哈顿距离。
2. **二分答案**：对每个查询点，二分可能的答案`k`。
3. **验证逻辑**：
   - 标记所有从起点出发，仅通过`dis ≥ k`的点形成的区域。
   - 从岛屿出发，通过八连通BFS检查是否能到达边界而不经过标记区域。

## 解决难点
- **包围判定**：通过八连通BFS模拟“绕过路径”的岛屿扩展，若无法到达边界则说明路径有效。
- **效率优化**：二分答案将复杂度降至对数级别，BFS保证线性遍历。

---

# 题解评分 (≥4星)

1. **FL_sleake（4.5星）**  
   - **亮点**：代码结构清晰，注释详细，预处理与验证逻辑分离。  
   - **个人心得**：调试时发现岛屿点需排除在标记区域外，确保包围判定正确性。

2. **sunkuangzheng（4星）**  
   - **亮点**：封装BFS为函数，代码简洁，复用性强。  
   - **优化**：使用`vector<pair<int,int>>`管理队列，减少冗余代码。

3. **Z1qqurat（4星）**  
   - **亮点**：强调八连通的正确性验证，实现中明确处理对角线移动。  
   - **实践提示**：注意岛屿点不可作为路径的一部分。

---

# 最优思路提炼

1. **二分答案**：快速缩小可能的解空间，每次验证`O(nm)`。
2. **双BFS验证**：
   - **四联通标记可达区域**：确保路径仅包含安全点。
   - **八联通包围检查**：模拟岛屿扩散，若无法到达边界则有效。
3. **曼哈顿距离预处理**：多源BFS初始化，为后续判定提供基础。

---

# 类似算法套路

- **迷宫类问题**：如寻找最大安全路径或判断连通性。
- **二分+BFS组合**：如“最大最小路径”（LeetCode 778）。

---

# 推荐题目
1. **P1141**：01迷宫连通块（BFS基础）。
2. **P1162**：填色包围检查（八连通应用）。
3. **P2296**：寻找可行路径中的边权限制（二分+BFS）。

---

# 可视化与算法演示

## 动画方案
- **预处理阶段**：火山点向外扩散，逐步染色每个点的曼哈顿距离（颜色深浅表示距离）。
- **二分验证阶段**：
  - **绿色区域**：当前`k`值允许的路径区域（四联通扩散）。
  - **红色区域**：岛屿八连通扩散，若触及边界则闪烁警告。
- **交互控制**：支持步进、调整`k`值，实时显示验证结果。

## 复古游戏化设计
- **像素风格**：每个单元格为16x16像素，火山用红色方块，岛屿用棕色，海洋渐变蓝。
- **音效**：
  - **扩散音效**：BFS每一步的“滴答”声。
  - **成功/失败**：高音“叮”或低音“嗡”。
- **自动演示**：AI模拟二分过程，自动切换`k`并展示验证路径。

---

# 核心代码片段

```cpp
// 预处理曼哈顿距离（多源BFS）
void Get_dis() {
    queue<node> q;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            if (s[i][j] == 'v') {
                dis[i][j] = 0;
                q.push({i, j});
            }
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (int i=0; i<4; i++) {
            int tx = u.x + dx[i], ty = u.y + dy[i];
            if (tx<1 || ty<1 || tx>n || ty>m) continue;
            if (dis[tx][ty] > dis[u.x][u.y] + 1) {
                dis[tx][ty] = dis[u.x][u.y] + 1;
                q.push({tx, ty});
            }
        }
    }
}

// 检查k值是否可行
bool check(int k) {
    // 标记可达区域（四联通）
    Mark_points(k);
    // 八连通检查包围
    queue<node> q;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            if (s[i][j] == '#') {
                q.push({i, j});
                vis[i][j] = 1;
            }
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        if (u.x == 1 || u.x == n || u.y == 1 || u.y == m) return false; // 到达边界
        for (int i=0; i<8; i++) {
            int tx = u.x + dx8[i], ty = u.y + dy8[i];
            if (tx<1 || ty<1 || tx>n || ty>m) continue;
            if (Mark[tx][ty] || vis[tx][ty]) continue;
            vis[tx][ty] = 1;
            q.push({tx, ty});
        }
    }
    return true;
}
```

---
处理用时：84.71秒