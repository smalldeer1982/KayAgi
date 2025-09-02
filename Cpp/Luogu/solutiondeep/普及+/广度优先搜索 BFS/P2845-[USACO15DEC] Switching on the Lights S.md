# 题目信息

# [USACO15DEC] Switching on the Lights S

## 题目背景

来源：usaco-2015-dec

Farm John 最近新建了一批巨大的牛棚。这些牛棚构成了一个 $N \times N$ 的矩形网络 $(1 < N < 100)$。

然而 Bessie 十分怕黑，他想计算可以把多少个牛棚的灯打开。

## 题目描述

有 $N \times N$ 个房间，组成了一张 $N \times N$ 的网格图，Bessie 一开始位于左上角 $(1,1)$，并且只能上下左右行走。


一开始，只有 $(1,1)$ 这个房间的灯是亮着的，Bessie 只能在亮着灯的房间里活动。


有另外 $M$ 条信息，每条信息包含四个数 $a,b,c,d$，表示房间 $(a,b)$ 里有房间 $(c,d)$ 的灯的开关。


请计算出最多有多少个房间的灯可以被打开。

## 说明/提示

Bessie 可以使用 $(1,1)$ 的开关打开 $(1,2),(1,3)$ 的灯，然后走到 $(1,3)$ 并打开 $(2,1)$ 的灯，走到 $(2,1)$ 并打开 $(2,2)$ 的灯。$(2,3)$ 的开关无法到达。因此可以点亮 $5$ 个房间。

## 样例 #1

### 输入

```
3 6
1 1 1 2
2 1 2 2
1 1 1 3
2 3 3 1
1 3 1 2
1 3 2 1
```

### 输出

```
5```

# AI分析结果

### 综合分析与结论

本题的核心是通过搜索算法（DFS或BFS）模拟Bessie在牛棚中移动并打开灯的过程。难点在于如何高效地处理灯的开闭状态以及Bessie的移动路径，尤其是在某些灯被打开后，Bessie可能能够访问之前无法到达的区域。题解中主要采用了DFS或BFS，并结合了邻接表、队列等数据结构来优化搜索过程。

大部分题解的思路相似，但在实现细节和优化程度上有所差异。部分题解通过多次DFS或BFS来确保所有可能的灯都被打开，而另一些则通过引入额外的数据结构（如`canv`数组）来记录哪些房间的灯可以被打开且Bessie能够到达。

### 评分较高的题解

#### 1. **作者：JMercury (5星)**
   - **关键亮点**：使用了BFS并结合了邻接表来存储每个房间的开关信息。通过队列管理Bessie的移动路径，并在每次打开灯后检查新点是否可以访问，确保了所有可能的灯都被打开。
   - **个人心得**：作者提到本题与另一道题[P2446 [SDOI2010]大陆争霸](https://www.luogu.org/problemnew/show/P2446)相似，表明其通过类比其他题目来优化本题的解法。
   - **核心代码**：
     ```cpp
     void spfa() {
         queue<P> q; q.push((P){1,1}); vis[1][1] = true; MAP[1][1] = true; ans++;
         while (!q.empty()) {
             P u = q.front(); q.pop();
             for (int i = 0; i < 4; i++) {
                 int vx = u.x + dx[i], vy = u.y + dy[i];
                 if (!Inside(vx, vy) || vis[vx][vy]) continue;
                 if (MAP[vx][vy]) q.push((P){vx, vy}), vis[vx][vy] = true;
             }
             for (int i = 0; i < Lamp[u.x][u.y].size(); i++) {
                 P v = Lamp[u.x][u.y][i];
                 if (vis[v.x][v.y] || MAP[v.x][v.y]) continue;
                 MAP[v.x][v.y] = true; ans++;
                 for (int i = 0; i < 4; i++)
                     if (vis[v.x + dx[i]][v.y + dy[i]]) {
                         q.push((P){v.x, v.y}), vis[v.x][v.y] = true;
                         break;
                     }
             }
         }
     }
     ```

#### 2. **作者：BoAn (4星)**
   - **关键亮点**：通过多次DFS来确保所有可能的灯都被打开，每次DFS后检查是否有新的灯被打开，直到没有新的灯被打开为止。这种方法虽然简单，但确保了所有可能的灯都被打开。
   - **核心代码**：
     ```cpp
     void dfs(int x, int y) {
         for (int i = 1; i <= m[x][y].top; i++)
             mark[m[x][y].x[i]][m[x][y].y[i]] = 1;
         for (int i = 0; i < 4; i++)
             if (x + dx[i] >= 1 && x + dx[i] <= n && y + dy[i] >= 1 && y + dy[i] <= n && mark[x + dx[i]][y + dy[i]] && !z[x + dx[i]][y + dy[i]]) {
                 z[x + dx[i]][y + dy[i]] = 1;
                 dfs(x + dx[i], y + dy[i]);
             }
     }
     ```

#### 3. **作者：bobxie (4星)**
   - **关键亮点**：使用了BFS并结合了链式前向星来存储开关信息，通过队列管理Bessie的移动路径，并在每次打开灯后检查新点是否可以访问。
   - **核心代码**：
     ```cpp
     int bfs() {
         int cnt = 1;
         queue<note> Q;
         Q.push((note){1, 1});
         mp[1][1] = used[1][1] = 1;
         while (!Q.empty()) {
             note top = Q.front();
             Q.pop();
             for (int i = 0; i < 4; ++i) {
                 int xx = top.x + dx[i], yy = top.y + dy[i];
                 if (xx < 1 || yy < 1 || xx > n || yy > n || used[xx][yy]) continue;
                 if (!mp[xx][yy]) continue;
                 used[xx][yy] = 1;
                 Q.push((note){xx, yy});
             }
             for (int i = head[top.x][top.y]; i; i = e[i].nxt) {
                 int xx = e[i].to1, yy = e[i].to2;
                 if (!mp[xx][yy]) {
                     cnt++;
                     mp[xx][yy] = 1;
                     if (!used[xx][yy] && (used[xx - 1][yy] || used[xx + 1][yy] || used[xx][yy + 1] || used[xx][yy - 1])) {
                         Q.push((note){xx, yy});
                         used[xx][yy] = 1;
                     }
                 }
             }
         }
         return cnt;
     }
     ```

### 最优关键思路与技巧

1. **BFS与DFS结合**：通过BFS或DFS管理Bessie的移动路径，并在每次打开灯后检查新点是否可以访问，确保所有可能的灯都被打开。
2. **邻接表与链式前向星**：使用邻接表或链式前向星来存储每个房间的开关信息，优化了搜索过程。
3. **多次搜索**：通过多次DFS或BFS确保所有可能的灯都被打开，避免了遗漏。

### 可拓展之处

本题的解法可以拓展到其他类似的搜索问题，尤其是那些需要在搜索过程中动态改变状态的问题。例如，某些迷宫问题中，路径的状态会随着玩家的移动而改变，类似于本题中灯的开闭状态。

### 推荐题目

1. [P2446 [SDOI2010]大陆争霸](https://www.luogu.org/problemnew/show/P2446)
2. [P1162 填涂颜色](https://www.luogu.org/problemnew/show/P1162)
3. [P1443 马的遍历](https://www.luogu.org/problemnew/show/P1443)

### 个人心得摘录

- **JMercury**：通过类比其他题目来优化本题的解法，表明其通过类比其他题目来优化本题的解法。
- **BoAn**：通过多次DFS来确保所有可能的灯都被打开，每次DFS后检查是否有新的灯被打开，直到没有新的灯被打开为止。

---
处理用时：48.34秒