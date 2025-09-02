# 题目信息

# [USACO07OCT] Obstacle Course S

## 题目描述

Consider an N x N (1 <= N <= 100) square field composed of 1

by 1 tiles. Some of these tiles are impassible by cows and are marked with an 'x' in this 5 by 5 field that is challenging to navigate:

```cpp
. . B x . 
. x x A . 
. . . x . 
. x . . . 
. . x . . 
```
Bessie finds herself in one such field at location A and wants to move to location B in order to lick the salt block there.  Slow, lumbering creatures like cows do not like to turn and, of course, may only move parallel to the edges of the square field. For a given field, determine the minimum number of ninety degree turns in any path from A to B. The path may begin and end with Bessie facing in any direction. Bessie knows she can get to the salt lick.



## 说明/提示

只可以上下左右四个方向行走，并且不能走出这些格子之外。开始和结束时的方向可以任意。

### 数据范围及约定

对于全部数据，保证 $2\le N\le 100$。


## 样例 #1

### 输入

```
3
. x A
. . .
B x .```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

本题的核心在于找到从起点到终点的路径，且转弯次数最少。由于转弯次数的计算与路径长度无关，传统的BFS无法直接应用，因此需要对其进行优化或改造。题解中主要采用了以下几种思路：

1. **BFS + 方向记录**：通过记录每个点的方向信息，确保在扩展时能够正确计算转弯次数。
2. **洪水填充**：在BFS的基础上，通过“洪水填充”技巧，一次性扩展一个方向上的所有点，减少重复计算。
3. **Dijkstra + 双端队列**：将转弯次数作为边权，使用双端队列优化的Dijkstra算法，确保每次扩展时优先选择转弯次数较少的路径。
4. **DFS + 记忆化**：通过DFS遍历所有可能的路径，并使用记忆化剪枝，避免重复计算。

从题解的质量来看，部分题解思路清晰，代码实现简洁，优化到位，值得推荐。以下是评分较高的题解：

---

### 精选题解

#### 1. **作者：GNAQ (赞：36)**  
**星级：⭐⭐⭐⭐⭐**  
**关键亮点**：  
- 使用BFS + 方向记录，通过“洪水填充”技巧，一次性扩展一个方向上的所有点，减少重复计算。
- 代码结构清晰，优化到位，时间复杂度较低。
- 通过证明确保了算法的正确性。

**核心代码**：
```cpp
while (!q.empty()) {
    node u = q.front();
    q.pop();
    if ((u.x == ex) && (u.y == ey)) break;
    Point V;
    for (int i = 0; i < maxWay; ++i) {
        V.x = u.x + dx[i]; V.y = u.y + dy[i];
        while (check(V.x, V.y) == true) {
            if (step[V.x][V.y] > step[u.x][u.y] + 1) {
                step[V.x][V.y] = step[u.x][u.y] + 1;
                q.push(V);
            }
            V.x += dx[i]; V.y += dy[i];
        }
    }
}
```
**核心思想**：通过while循环一次性扩展一个方向上的所有点，确保每次扩展时转弯次数最少。

---

#### 2. **作者：hht2005 (赞：2)**  
**星级：⭐⭐⭐⭐**  
**关键亮点**：  
- 使用双端队列优化的Dijkstra算法，将转弯次数作为边权，确保每次扩展时优先选择转弯次数较少的路径。
- 代码简洁，思路清晰，时间复杂度较低。

**核心代码**：
```cpp
while (!q.empty()) {
    node x = q.front();
    q.pop_front();
    if (x.x == tx && x.y == ty) {
        printf("%d\n", v[x.x][x.y][x.f]);
        return 0;
    }
    if (b[x.x][x.y][x.f]) continue;
    b[x.x][x.y][x.f] = 1;
    for (int i = 0; i < 4; i++) {
        int x1 = x.x + dx[i], y1 = x.y + dy[i];
        if (a[x1][y1] == '.' && v[x.x][x.y][x.f] + (x.f != i) < v[x1][y1][i]) {
            v[x1][y1][i] = v[x.x][x.y][x.f] + (i != x.f);
            if (i == x.f) q.push_front((node){x1, y1, i});
            else q.push_back((node){x1, y1, i});
        }
    }
}
```
**核心思想**：通过双端队列优化Dijkstra，确保每次扩展时优先选择转弯次数较少的路径。

---

#### 3. **作者：ykuouzf (赞：10)**  
**星级：⭐⭐⭐⭐**  
**关键亮点**：  
- 使用DFS + 记忆化，通过记录每个点的转弯次数，避免重复计算。
- 代码简洁，思路清晰，适合小规模数据。

**核心代码**：
```cpp
void dfs(int x, int y, int sum, int p) {
    if (q[p][x][y] <= sum) return;
    q[p][x][y] = sum;
    if (x == s1 && y == s2) return;
    for (int i = 1; i <= 4; i++) {
        int ux = x + ax[i], uy = y + ay[i];
        if (ux < 1 || uy < 1 || ux > n || uy > n) continue;
        if (a[ux][uy] == 'x') continue;
        if (!vis[ux][uy]) {
            vis[ux][uy] = 1;
            if (p == i % 2 || p == 2) dfs(ux, uy, sum, i % 2);
            else dfs(ux, uy, sum + 1, i % 2);
            vis[ux][uy] = 0;
        }
    }
}
```
**核心思想**：通过DFS遍历所有可能的路径，并使用记忆化剪枝，避免重复计算。

---

### 最优关键思路总结

1. **方向记录与洪水填充**：通过记录每个点的方向信息，结合“洪水填充”技巧，一次性扩展一个方向上的所有点，减少重复计算。
2. **双端队列优化Dijkstra**：将转弯次数作为边权，使用双端队列优化的Dijkstra算法，确保每次扩展时优先选择转弯次数较少的路径。
3. **DFS + 记忆化**：通过DFS遍历所有可能的路径，并使用记忆化剪枝，避免重复计算。

---

### 推荐题目

1. **P2937 [USACO09OPEN]障碍训练Obstacle Course**：与本题类似，考察最小转弯次数的路径搜索。
2. **P1141 01迷宫**：考察BFS的应用，适合练习方向记录与扩展技巧。
3. **P1162 填涂颜色**：考察洪水填充的应用，适合练习一次性扩展技巧。

---

### 个人心得总结

- **调试经历**：部分题解提到调试时发现方向记录不准确，导致转弯次数计算错误，提醒我们在实现时要特别注意方向的处理。
- **踩坑教训**：部分题解提到DFS在小规模数据上表现良好，但在大规模数据上容易超时，提醒我们选择合适的算法。
- **顿悟感想**：通过“洪水填充”技巧，一次性扩展一个方向上的所有点，大大减少了重复计算，提升了算法效率。

---
处理用时：34.46秒