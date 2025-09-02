# 题目信息

# [USACO11OPEN] Corn Maze S

## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?


## 说明/提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。

## 样例 #1

### 输入

```
5 6
###=##
#.W.##
#.####
#.@W##
######
```

### 输出

```
3```

# AI分析结果



### 综合分析与结论
本题核心是 BFS 最短路径问题，核心难点在于传送门的强制转移与重复使用问题。题解主要围绕 BFS 展开，部分解法通过双向 BFS、SPFA、拆点等方法进行优化。关键难点集中在传送门处理逻辑与状态标记策略。

---

### 高星题解推荐（评分 ≥4★）

#### 1. 作者：lxzy_（193赞） | 评分：4.5★
**关键亮点**  
- **标准 BFS + 传送门即时跳转**：遇到传送门立即跳转至对应点，代码简洁清晰。  
- **独立处理状态标记**：传送后节点标记在跳转后的位置，避免重复访问。  
- **代码可读性高**：结构明确，注释详细，适合学习基础 BFS 框架。

**核心代码片段**  
```cpp
void goto_another(int &nx, int &ny, int k) {
    for (遍历所有点寻找对应传送门端点)
        if (找到对应端点) { nx = i; ny = j; return; }
}

while (!que.empty()) {
    point f = que.front();
    if (是传送门) goto_another(f.x, f.y); // 强制跳转
    for (四方向扩展) {
        if (新坐标合法且未访问) {
            vis[nx][ny] = true;
            que.push({nx, ny, f.t+1});
        }
    }
}
```

---

#### 2. 作者：lzxhdxx（87赞） | 评分：4.2★  
**关键亮点**  
- **双向 BFS 优化**：从起点和终点同时扩展，减少搜索空间。  
- **复杂状态管理**：区分传送门使用次数（1次/2次），避免错误相遇判定。  
- **应对特殊用例**：处理传送门多次中转场景，保证正确性。

**核心技巧**  
- 双向队列交替扩展，优先处理状态较少的方向。  
- 相遇时需验证传送门使用次数是否合法。

---

#### 3. 作者：ThinkofBlank（11赞） | 评分：4.0★  
**关键亮点**  
- **拆点法建模**：将每个点分为「传送前」和「传送后」状态，避免重复访问。  
- **SPFA 算法应用**：将迷宫转化为带权图，处理 0 权值边（传送门）。  
- **通用性较强**：可扩展至更复杂的图结构问题。

**核心代码思路**  
```cpp
struct node { int v, w, nex; }; // 边结构
void AddEdge(int u, int v, int w) { ... } // 建立双向边

// 拆点：0 表示普通移动状态，1 表示传送后状态
for (四方向扩展) {
    if (是传送门) addedge(u, 对应传送点+虚拟节点, 0);
    else addedge(u, 邻接点, 1);
}
```

---

### 关键思路总结
1. **BFS 基础框架**：优先考虑标准 BFS，正确处理状态标记与队列扩展。  
2. **传送门处理**：强制跳转后立即更新坐标，标记目标点而非起点。  
3. **双向 BFS 优化**：适用于大规模数据，需注意状态同步与终止条件。  
4. **拆点法与图论建模**：将复杂规则转化为图结构，利用最短路算法解决。

---

### 推荐练习题目
1. **P1443 马的遍历** - BFS 基础训练（[题目链接](https://www.luogu.com.cn/problem/P1443)）  
2. **P1746 离开中山路** - 双向 BFS 应用（[题目链接](https://www.luogu.com.cn/problem/P1746)）  
3. **P1141 01迷宫** - 连通块与状态扩展（[题目链接](https://www.luogu.com.cn/problem/P1141)）  

---

### 个人心得摘录
- **作者 lzxhdxx**：  
  > *「双向 BFS 必须验证传送门使用次数，否则可能错误计算路径」*  
  → 多次使用传送门需单独设计状态验证逻辑。  
- **作者 ThinkofBlank**：  
  > *「拆点法将每个点分为流入/流出状态，完美解决强制传送问题」*  
  → 通过状态分离简化复杂规则，值得同类问题借鉴。

---
处理用时：75.63秒