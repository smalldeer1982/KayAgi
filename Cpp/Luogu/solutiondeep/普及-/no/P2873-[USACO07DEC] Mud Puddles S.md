# 题目信息

# [USACO07DEC] Mud Puddles S

## 题目描述

Farmer John is leaving his house promptly at 6 AM for his daily milking of Bessie. However, the previous evening saw a heavy rain, and the fields are quite muddy. FJ starts at the point (0, 0) in the coordinate plane and heads toward Bessie who is located at (X, Y) (-500 ≤ X ≤ 500; -500 ≤ Y ≤ 500). He can see all N (1 ≤ N ≤ 10,000) puddles of mud, located at points (Ai, Bi) (-500 ≤ Ai ≤ 500; -500 ≤ Bi ≤ 500) on the field. Each puddle occupies only the point it is on.

Having just bought new boots, Farmer John absolutely does not want to dirty them by stepping in a puddle, but he also wants to get to Bessie as quickly as possible. He's already late because he had to count all the puddles. If Farmer John can only travel parallel to the axes and turn at points with integer coordinates, what is the shortest distance he must travel to reach Bessie and keep his boots clean? There will always be a path without mud that Farmer John can take to reach Bessie.

## 样例 #1

### 输入

```
1 2 7
0 2
-1 3
3 1
1 1
4 2
-1 1
2 2```

### 输出

```
11```

# AI分析结果

### 算法分类
广度优先搜索 BFS

### 综合分析与结论
本题的核心是通过BFS寻找从起点到终点的最短路径，同时避免经过泥坑。所有题解都采用了BFS算法，但处理负数坐标的方式有所不同。大多数题解通过将坐标加500来避免负数下标问题，而部分题解使用了`map`来处理负数坐标。此外，部分题解还提到了一些优化技巧，如剪枝和直接输出第一个找到的解。

### 所选题解
1. **作者：Horizon20182201**  
   - **星级：5星**  
   - **关键亮点**：代码清晰，结构完整，使用了STL队列，处理负数坐标的方式简单直接。  
   - **个人心得**：作者提到“这题其实是个裸的bfs”，强调了BFS的适用性。  
   - **核心代码**：
     ```cpp
     int bfs () {
         while (!qwq.empty()) {
             int xx = qwq.front().x;
             int yy = qwq.front().y;
             int s = qwq.front().sum;
             for (int i = 0; i < 4; i++) {
                 int nx = xx + dir[i][0];
                 int ny = yy + dir[i][1];
                 if (nx == X && ny == Y) return s + 1;
                 if (!mmap[nx][ny]) {
                     mmap[nx][ny] = true;
                     qwq.push({nx, ny, s + 1});
                 }
             }
             qwq.pop();
         }
     }
     ```

2. **作者：Steinway**  
   - **星级：4星**  
   - **关键亮点**：代码简洁，使用了STL队列，处理负数坐标的方式与第一题解类似。  
   - **核心代码**：
     ```cpp
     while (!q.empty()) {
         Node x = q.front(); q.pop();
         for (int i = 0; i < 4; i++) {
             int nx = x.x + dx[i];
             int ny = x.y + dy[i];
             if (nx == ex + 500 && ny == ey + 500) {
                 printf("%d\n", x.sum + 1);
                 return 0;
             }
             if (legal(nx, ny) && Map[nx][ny] == 0) {
                 Map[nx][ny] = 1;
                 q.push({nx, ny, x.sum + 1});
             }
         }
     }
     ```

3. **作者：Leaved_**  
   - **星级：4星**  
   - **关键亮点**：直接输出第一个找到的解，强调了BFS的第一个解即为最优解的特性。  
   - **核心代码**：
     ```cpp
     void Bfs() {
         while (head <= tail) {
             int now_x = que[head][0], now_y = que[head][1], sum = que[head][2];
             head++;
             for (int i = 0; i < 4; i++) {
                 int tx = now_x + go[i][0], ty = now_y + go[i][1];
                 if (tx == endx && ty == endy) {
                     p(sum + 1);
                     return;
                 }
                 if (can_bfs(tx, ty)) {
                     if (!map_t[tx][ty] && !vis[tx][ty]) {
                         ++tail;
                         que[tail][0] = tx; que[tail][1] = ty; que[tail][2] = sum + 1;
                         vis[tx][ty] = 1;
                     }
                 }
             }
         }
     }
     ```

### 最优关键思路或技巧
- **处理负数坐标**：通过将坐标加500来避免负数下标问题，这是一种简单且有效的处理方式。
- **BFS优化**：直接输出第一个找到的解，因为BFS的第一个解即为最优解。
- **剪枝**：在扩展节点时，如果当前步数已经大于已知的最优解，则跳过该节点。

### 可拓展之处
- **类似算法套路**：BFS常用于求解最短路径问题，尤其是在无权图中。类似的题目可以考察在不同约束条件下的最短路径问题。
- **数据结构**：可以使用`map`来处理更复杂的坐标问题，尤其是在坐标范围不确定或非常大的情况下。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)

---
处理用时：34.46秒