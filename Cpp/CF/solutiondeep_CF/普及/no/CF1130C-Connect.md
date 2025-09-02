# 题目信息

# Connect

## 题目描述

Alice lives on a flat planet that can be modeled as a square grid of size $ n \times n $ , with rows and columns enumerated from $ 1 $ to $ n $ . We represent the cell at the intersection of row $ r $ and column $ c $ with ordered pair $ (r, c) $ . Each cell in the grid is either land or water.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1130C/b5659671b82592e81ced0ea1b88b58d8fa94b02e.png)An example planet with $ n = 5 $ . It also appears in the first sample test.Alice resides in land cell $ (r_1, c_1) $ . She wishes to travel to land cell $ (r_2, c_2) $ . At any moment, she may move to one of the cells adjacent to where she is—in one of the four directions (i.e., up, down, left, or right).

Unfortunately, Alice cannot swim, and there is no viable transportation means other than by foot (i.e., she can walk only on land). As a result, Alice's trip may be impossible.

To help Alice, you plan to create at most one tunnel between some two land cells. The tunnel will allow Alice to freely travel between the two endpoints. Indeed, creating a tunnel is a lot of effort: the cost of creating a tunnel between cells $ (r_s, c_s) $ and $ (r_t, c_t) $ is $ (r_s-r_t)^2 + (c_s-c_t)^2 $ .

For now, your task is to find the minimum possible cost of creating at most one tunnel so that Alice could travel from $ (r_1, c_1) $ to $ (r_2, c_2) $ . If no tunnel needs to be created, the cost is $ 0 $ .

## 说明/提示

In the first sample, a tunnel between cells $ (1, 4) $ and $ (4, 5) $ should be created. The cost of doing so is $ (1-4)^2 + (4-5)^2 = 10 $ , which is optimal. This way, Alice could walk from $ (1, 1) $ to $ (1, 4) $ , use the tunnel from $ (1, 4) $ to $ (4, 5) $ , and lastly walk from $ (4, 5) $ to $ (5, 5) $ .

In the second sample, clearly a tunnel between cells $ (1, 3) $ and $ (3, 1) $ needs to be created. The cost of doing so is $ (1-3)^2 + (3-1)^2 = 8 $ .

## 样例 #1

### 输入

```
5
1 1
5 5
00001
11111
00111
00110
00110
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3
1 3
3 1
010
101
010
```

### 输出

```
8
```

# AI分析结果

【题目内容】
# Connect

## 题目描述

Alice 住在一个平坦的星球上，该星球可以建模为一个大小为 $n \times n$ 的正方形网格，行和列从 $1$ 到 $n$ 编号。我们用有序对 $(r, c)$ 表示位于第 $r$ 行和第 $c$ 列交叉处的单元格。网格中的每个单元格要么是陆地，要么是水。

Alice 居住在陆地单元格 $(r_1, c_1)$。她希望前往陆地单元格 $(r_2, c_2)$。在任何时刻，她可以移动到与她当前位置相邻的单元格之一——即上下左右四个方向之一。

不幸的是，Alice 不会游泳，除了步行之外没有其他可行的交通工具（即她只能在陆地上行走）。因此，Alice 的旅行可能无法完成。

为了帮助 Alice，你计划在最多两个陆地单元格之间创建一个隧道。隧道将允许 Alice 在两个端点之间自由旅行。创建隧道的成本为 $(r_s-r_t)^2 + (c_s-c_t)^2$。

你的任务是找到创建最多一个隧道的最小成本，以便 Alice 可以从 $(r_1, c_1)$ 旅行到 $(r_2, c_2)$。如果不需要创建隧道，则成本为 $0$。

## 说明/提示

在第一个样例中，应该在单元格 $(1, 4)$ 和 $(4, 5)$ 之间创建隧道。这样做的成本是 $(1-4)^2 + (4-5)^2 = 10$，这是最优的。这样，Alice 可以从 $(1, 1)$ 走到 $(1, 4)$，使用隧道从 $(1, 4)$ 到 $(4, 5)$，最后从 $(4, 5)$ 走到 $(5, 5)$。

在第二个样例中，显然需要在单元格 $(1, 3)$ 和 $(3, 1)$ 之间创建隧道。这样做的成本是 $(1-3)^2 + (3-1)^2 = 8$。

## 样例 #1

### 输入

```
5
1 1
5 5
00001
11111
00111
00110
00110
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3
1 3
3 1
010
101
010
```

### 输出

```
8
```

【算法分类】
广度优先搜索 BFS

【题解分析与结论】
本题的核心思路是通过 BFS 或 DFS 找出起点和终点所能到达的所有陆地单元格，然后在这些单元格之间寻找最小成本的隧道。由于数据范围较小（$n \leq 50$），可以直接使用暴力枚举的方法。

【评分较高的题解】

1. **作者：封禁用户 (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 使用 BFS 分别从起点和终点出发，记录所有可达的陆地单元格。
     - 通过暴力枚举所有可能的隧道组合，计算最小成本。
     - 代码结构清晰，使用了队列和标记数组来优化搜索过程。
   - **核心代码：**
     ```cpp
     void bfs(bool f, int sx, int sy) {
         vis[sx][sy] = 1;
         q.push((go){sx, sy});
         if (f == 0) {
             start_tot++;
             st[start_tot].x = sx;
             st[start_tot].y = sy;
         } else {
             end_tot++;
             en[end_tot].x = sx;
             en[end_tot].y = sy;
         }
         while (!q.empty()) {
             int x = q.front().x;
             int y = q.front().y;
             q.pop();
             for (int i = 0; i < 4; i++) {
                 int xx = x + bx[i];
                 int yy = y + by[i];
                 if (xx > 0 && xx <= n && yy > 0 && yy <= n && !vis[xx][yy] && m[xx][yy] == 0) {
                     vis[xx][yy] = 1;
                     q.push((go){xx, yy});
                     if (f == 0) {
                         start_tot++;
                         st[start_tot].x = xx;
                         st[start_tot].y = yy;
                     } else {
                         end_tot++;
                         en[end_tot].x = xx;
                         en[end_tot].y = yy;
                     }
                 }
             }
         }
     }
     ```

2. **作者：Hisaishi_Kanade (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用 DFS 从起点和终点分别搜索所有可达的陆地单元格。
     - 在搜索过程中记录所有可达点，并通过暴力枚举计算最小隧道成本。
     - 代码简洁，使用了递归实现 DFS，易于理解。
   - **核心代码：**
     ```cpp
     void dfs(int x, int y) {
         v[x][y] = true;
         l[++cnt] = x; r[cnt] = y;
         if (x == fx && y == fy) {
             puts("0");
             exit(0);
         }
         for (int i = 0; i < 4; ++i) {
             x += dx[i]; y += dy[i];
             if (1 <= x && x <= n && 1 <= y && y <= n && !v[x][y])
                 dfs(x, y);
             x -= dx[i]; y -= dy[i];
         }
         return;
     }
     ```

3. **作者：xyf007 (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用 DFS 分别从起点和终点出发，记录所有可达的陆地单元格。
     - 通过暴力枚举所有可能的隧道组合，计算最小成本。
     - 代码结构清晰，使用了递归实现 DFS，易于理解。
   - **核心代码：**
     ```cpp
     void dfs1(int x, int y) {
         vis[x][y] = 1;
         a1[++len1] = std::make_pair(x, y);
         for (int i = 0; i < 4; i++) {
             int tox = x + dx[i], toy = y + dy[i];
             if (!vis[tox][toy] && !a[tox][toy] && tox > 0 && tox <= n && toy > 0 && toy <= n) {
                 dfs1(tox, toy);
             }
         }
     }
     ```

【最优关键思路】
通过 BFS 或 DFS 分别从起点和终点出发，记录所有可达的陆地单元格，然后在这些单元格之间寻找最小成本的隧道。由于数据范围较小，可以直接使用暴力枚举的方法。

【拓展思路】
类似的问题可以扩展到更复杂的地图或更大的数据范围，此时可以考虑使用并查集或更高效的搜索算法来优化。

【推荐题目】
1. P1130 - 连通性检查
2. P1141 - 迷宫
3. P1162 - 填涂颜色

---
处理用时：47.28秒