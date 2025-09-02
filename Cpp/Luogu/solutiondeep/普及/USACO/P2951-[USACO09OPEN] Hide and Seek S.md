# 题目信息

# [USACO09OPEN] Hide and Seek S

## 题目描述

Bessie is playing hide and seek (a game in which a number of players hide and a single player (the seeker) attempts to find them after which various penalties and rewards are assessed; much fun usually ensues).

She is trying to figure out in which of N (2 <= N <= 20,000) barns conveniently numbered 1..N she should hide. She knows that FJ (the seeker) starts out in barn 1. All the barns are connected by M (1 <= M <= 50,000) bidirectional paths with endpoints A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i); it is possible to reach any barn from any other through the paths.

Bessie decides that it will be safest to hide in the barn that has the greatest distance from barn 1 (the distance between two barns is the smallest number of paths that one must traverse to get from one to the other). Help Bessie figure out the best barn in which to hide.

奶牛贝西和农夫约翰（FJ）玩捉迷藏，现在有N个谷仓，FJ开始在第一个谷仓，贝西为了不让FJ找到她，当然要藏在距离第一个谷仓最远的那个谷仓了。现在告诉你N个谷仓，和M个两两谷仓间的“无向边”。每两个仓谷间当然会有最短路径，现在要求距离第一个谷仓（FJ那里）最远的谷仓是哪个（所谓最远就是距离第一个谷仓最大的最短路径）？如有多个则输出编号最小的。以及求这最远距离是多少，和有几个这样的谷仓距离第一个谷仓那么远。


## 说明/提示

The farm layout is as follows:

 ![](https://cdn.luogu.com.cn/upload/pic/2815.png) 

Barns 4, 5, and 6 are all a distance of 2 from barn 1. We choose barn 4 because it has the smallest index.



这里谷仓4，5，6距离1号谷仓都是2，但是4编号最小所以输出4.因此最远距离是2且有3个谷仓，依次输出：2和3。 

感谢 wjcwinmt 的贡献翻译


## 样例 #1

### 输入

```
6 7 
3 6 
4 3 
3 2 
1 3 
1 2 
2 4 
5 2 
```

### 输出

```
4 2 3 
```

# AI分析结果



### 综合分析与结论
本题核心是求解单源最短路径的最长距离。由于边权为1，BFS是最优选择（复杂度O(N+M)），但多数题解采用Dijkstra堆优化或SPFA。关键优化点包括：正确初始化距离数组、高效统计结果、处理编号最小等条件。

---

### 高星题解推荐

#### 1. 作者：Fuko_Ibuki（★★★★★）
**关键亮点**：  
- 两次BFS遍历：第一次计算最短路径，第二次统计结果，避免重复计算。  
- 逆序遍历数组快速确定最小编号点。  
- 代码简洁高效，充分结合题目特性（边权为1）。  

**核心代码**：  
```cpp
void bfs() {
    queue<node> q;
    q.push(node(1,0));
    vis[1] = 1;
    while (!q.empty()) {
        node u = q.front(); q.pop();
        da = u.step; // 更新最大距离
        for (int i : lj[u.to]) 
            if (!vis[i]) {
                vis[i] = 1;
                q.push(node(i, u.step + 1));
            }
    }
    // 第二次遍历统计结果
}
```

#### 2. 作者：Eason_AC（★★★★☆）
**关键亮点**：  
- 详细讲解Dijkstra堆优化的实现细节，如memset初始化技巧。  
- 分离距离计算与结果统计，逻辑清晰。  

**核心代码**：  
```cpp
void dj() {
    memset(dis, 0x3f, sizeof(dis)); // 正确初始化
    priority_queue<pair<int, int>> q;
    q.push({0, 1});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) 
            if (dis[v] > dis[u] + 1) // 松弛操作
                q.push({-dis[v], v});
    }
}
```

#### 3. 作者：99NL（★★★★☆）
**关键亮点**：  
- 利用BFS替代最短路算法，时间复杂度更低。  
- 动态维护最大距离及对应节点，代码简洁。  

**调试心得**：  
> "第一次写时忘记出队导致死循环，卡了10分钟。" —— 强调队列操作的重要性。

---

### 关键思路与技巧总结
1. **算法选择**：边权为1时，BFS是最优解（O(N+M)）；若边权不固定则用Dijkstra堆优化。  
2. **结果统计**：逆序遍历距离数组可快速找到最小编号的节点。  
3. **初始化技巧**：`memset(dis, 0x3f, sizeof(dis))`初始化为极大值，避免溢出。  

---

### 相似题目推荐
1. **P3371** 【模板】单源最短路径（弱化版）  
2. **P4779** 【模板】单源最短路径（标准版）  
3. **P1144** 最短路计数（BFS应用拓展）  

---

### 个人心得摘录
- **队列操作**：SPFA中未及时标记出队状态可能导致死循环（见Law_Aias题解）。  
- **初始化坑点**：`memset`按字节赋值，`0x3f3f3f3f`需谨慎使用（Eason_AC强调）。  
- **逆向思维**：统计结果时从后向前遍历可快速确定最小索引（Fuko_Ibuki的优化）。  

（完整代码请参考原题解，核心逻辑已提炼至上述分析中。）

---
处理用时：51.52秒