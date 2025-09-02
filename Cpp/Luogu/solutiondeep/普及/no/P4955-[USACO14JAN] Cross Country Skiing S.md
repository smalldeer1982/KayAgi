# 题目信息

# [USACO14JAN] Cross Country Skiing S

## 题目描述

The cross-country skiing course at the winter Moolympics is described by an $M * N$ grid of elevations (1 <= M,N <= 500), each elevation being in the range 0 .. 1,000,000,000.  

Some of the cells in this grid are designated as waypoints for the course.  The organizers of the Moolympics want to assign a difficulty rating $D$ to the entire course so that a cow can reach any waypoint from any other waypoint by repeatedly skiing from a cell to an adjacent cell with absolute elevation difference at most $D$.  Two cells are adjacent if one is directly north, south, east, or west of the other.  The difficulty rating of the course is the minimum value of $D$ such that all waypoints are mutually reachable in this fashion.

## 说明/提示

If D = 21, the three waypoints are reachable from each-other.  If D < 21, then the upper-right waypoint cannot be reached from the other two.

## 样例 #1

### 输入

```
3 5
20 21 18 99 5
19 22 20 16 26
18 17 40 60 80
1 0 0 0 1
0 0 0 0 0
0 0 0 0 1```

### 输出

```
21```

# AI分析结果



**算法分类**: 二分

**综合分析**  
本题需找到最小难度D使得所有关键点连通。主流解法为二分答案+搜索验证，或并查集按边权合并。二分法通过调整D值并检查连通性，而并查集直接处理边权排序，逐步合并关键点。

---

**精选题解**  

1. **ustze的题解**（5星）  
   **亮点**: 使用BFS进行验证，代码简洁高效，避免递归栈溢出风险。  
   **关键思路**: 二分D值，每次BFS遍历所有可达点，检查是否覆盖全部关键点。  
   **核心代码**:  
   ```cpp
   bool check(int mid) {
       memset(vis, 0, sizeof(vis));
       queue<node> q;
       q.push({sx, sy});
       vis[sx][sy] = 1;
       while (!q.empty()) {
           node t = q.front(); q.pop();
           for (int i = 0; i < 4; i++) {
               int xx = t.x + dx[i], yy = t.y + dy[i];
               if (xx >= 1 && yy >= 1 && xx <= n && yy <= m && !vis[xx][yy] 
                   && abs(a[xx][yy] - a[t.x][t.y]) <= mid) {
                   vis[xx][yy] = 1;
                   q.push({xx, yy});
               }
           }
       }
       // 检查所有关键点是否被访问
   }
   ```

2. **DQYdqy的题解**（4星）  
   **亮点**: 并查集按边权排序合并，直接求最大连通边的最小值。  
   **关键思路**: 构造网格边，按高度差排序后合并，直至所有关键点同属一个集合。  
   **核心代码**:  
   ```cpp
   sort(w+1, w+cnt+1, cmp); // 按边权排序
   for (int i=1; i<=cnt; i++) {
       int x=find(w[i].x), y=find(w[i].y);
       if (x != y) {
           fa[y] = x;
           if (u[x]+u[y] == tt) { // 所有关键点连通
               ans = w[i].v;
               break;
           }
       }
   }
   ```

3. **iorit的题解**（4星）  
   **亮点**: 明确验证逻辑，BFS实现清晰，处理关键点计数优化。  
   **心得**: 强调关键点互相可达只需从任意一点出发验证全局覆盖，简化判断逻辑。

---

**最优技巧总结**  
- **二分框架**：对答案D进行二分，每次验证连通性。
- **BFS验证**：避免递归深度问题，适合大网格场景。
- **并查集优化**：按边权升序合并，维护关键点连通性，直接求最大边权。

**拓展应用**  
类似问题如最小生成树最大边（P1546）、水位扩散问题（P1584）等，均需处理连通性约束下的极值。

**推荐题目**  
1. P1396 营救（二分/最小生成树）  
2. P1546 [USACO3.1]最短网络（最小生成树）  
3. P1991 无线通讯网（连通性+极值）

---
处理用时：76.09秒