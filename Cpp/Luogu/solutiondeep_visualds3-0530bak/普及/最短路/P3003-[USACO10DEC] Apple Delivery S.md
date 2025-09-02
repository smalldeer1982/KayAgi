# 题目信息

# [USACO10DEC] Apple Delivery S

## 题目描述

Bessie has two crisp red apples to deliver to two of her friends in the herd. Of course, she travels the C (1 <= C <= 200,000)

cowpaths which are arranged as the usual graph which connects P (1 <= P <= 100,000) pastures conveniently numbered from 1..P: no cowpath leads from a pasture to itself, cowpaths are bidirectional, each cowpath has an associated distance, and, best of all, it is always possible to get from any pasture to any other pasture. Each cowpath connects two differing pastures P1\_i (1 <= P1\_i <= P) and P2\_i (1 <= P2\_i <= P) with a distance between them of D\_i. The sum of all the distances D\_i does not exceed 2,000,000,000.

What is the minimum total distance Bessie must travel to deliver both apples by starting at pasture PB (1 <= PB <= P) and visiting pastures PA1 (1 <= PA1 <= P) and PA2 (1 <= PA2 <= P) in any order. All three of these pastures are distinct, of course.

Consider this map of bracketed pasture numbers and cowpaths with distances:

```cpp
               3        2       2
           [1]-----[2]------[3]-----[4]
             \     / \              /
             7\   /4  \3           /2
               \ /     \          /
               [5]-----[6]------[7]
                    1       2
```
If Bessie starts at pasture [5] and delivers apples to pastures [1] and [4], her best path is:

5 -> 6-> 7 -> 4\* -> 3 -> 2 -> 1\*

with a total distance of 12.

## 样例 #1

### 输入

```
9 7 5 1 4 
5 1 7 
6 7 2 
4 7 2 
5 6 1 
5 2 4 
4 3 2 
1 2 3 
3 2 2 
2 6 3 
```

### 输出

```
12 
```

# AI分析结果



---

## 算法分类
**最短路径**

---

## 综合分析与结论

### 核心思路与解决难点
1. **公式推导**：  
   `ans = min(dis[PB][PA1], dis[PB][PA2]) + dis[PA1][PA2]`  
   该公式源于两点间最短路径的对称性，无论先访问哪个目标点，总路径长度由起点到较近目标点的距离加上两目标点间的最短距离决定。

2. **算法选择**：  
   - **Dijkstra堆优化**：正权图的最优解，时间复杂度稳定为 O(m + n log n)。  
   - **SPFA+SLF优化**：通过双端队列优化入队顺序，提升稀疏图效率，但存在被极端数据卡时间的风险。

3. **关键难点**：  
   - 正确推导路径组合的最优表达式  
   - 处理大规模图时的时间复杂度控制  
   - 邻接表存储与优先队列的配合实现

---

## 题解清单（评分≥4星）

### 1. 作者：_流逝丶（★★★★☆）
- **核心亮点**：  
  使用 Dijkstra 堆优化，代码简洁易读，三次最短路径计算清晰体现核心公式。  
  完整处理了图的邻接表存储和优先队列操作，适合模板学习。
- **关键代码**：
  ```cpp
  void dijkstra(int s) {
      memset(dis, 0x3f, sizeof(dis));
      priority_queue<node> q;
      dis[s] = 0;
      q.push({0, s});
      while (!q.empty()) {
          int u = q.top().u; q.pop();
          if (vis[u]) continue;
          vis[u] = true;
          for (int i = head[u]; i; i = e[i].nxt) {
              int v = e[i].to;
              if (dis[v] > dis[u] + e[i].dis) {
                  dis[v] = dis[u] + e[i].dis;
                  q.push({dis[v], v});
              }
          }
      }
  }
  ```

### 2. 作者：Kalium（★★★★☆）
- **核心亮点**：  
  结构化的 Dijkstra 实现，使用自定义堆结构优化性能。  
  提供完整的输入输出处理和清晰的变量命名，适合工程实践。
- **调试心得**：  
  特别强调输入参数顺序（m 和 n 易混淆），避免低级错误。

### 3. 作者：Sober_Clever（★★★★☆）
- **核心亮点**：  
  采用三次 Dijkstra 计算所有必要距离，代码模块化程度高。  
  使用 `g[3][3]` 矩阵存储关键点间距离，提升代码可维护性。

---

## 最优思路与技巧提炼

### 核心实现思想
1. **三次最短路径计算**：  
   - 起点 PB 到 PA1、PA2 的最短距离  
   - PA1 到 PA2 的最短距离（双向图对称，只需计算一次）

2. **邻接表存储**：  
   链式前向星存储图结构，适应大规模稀疏图：
   ```cpp
   struct Edge { int to, w, next; };
   void add(int u, int v, int w) {
       edge[++cnt] = {v, w, head[u]};
       head[u] = cnt;
   }
   ```

3. **优先队列优化**：  
   使用 `priority_queue` 实现 Dijkstra 的 O(m log n) 时间复杂度：
   ```cpp
   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
   ```

---

## 同类型题推荐
1. **P4779** - 【模板】单源最短路径（标准版）  
   （Dijkstra 堆优化模板题）

2. **P1629** - 邮递员送信  
   （往返最短路径，正向图与反向图结合）

3. **P1144** - 最短路计数  
   （最短路径数统计，BFS/Dijkstra 变种）

---

## 可视化与算法演示设计

### 动画方案（像素风格）
1. **节点状态标记**：  
   - **白色**：未访问  
   - **绿色**：正在处理（优先队列顶部）  
   - **红色**：已确定最短路径  

2. **边松弛过程**：  
   - 当前处理的边显示为黄色  
   - 成功更新距离时边闪烁蓝色  

3. **控制面板**：  
   - 步进/暂停按钮控制动画速度  
   - 显示当前节点距离的更新过程  
   - 底部状态栏显示算法步骤说明

### 音效设计（Web Audio API）
- **节点入队**：8-bit "哔"声（短促高频）  
- **路径更新**：电子"滴答"声  
- **完成计算**：经典 FC 过关音效  

---

## 核心代码实现（Dijkstra 堆优化）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5, INF = 0x3f3f3f3f;
struct Edge { int to, w, next; } edges[MAXN * 4];
int head[MAXN], cnt, dis[MAXN], vis[MAXN];

void add(int u, int v, int w) {
    edges[++cnt] = {v, w, head[u]};
    head[u] = cnt;
}

void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dis[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to, w = edges[i].w;
            if (dis[v] > d + w) {
                dis[v] = d + w;
                pq.emplace(dis[v], v);
            }
        }
    }
}

int main() {
    int m, n, pb, pa1, pa2;
    cin >> m >> n >> pb >> pa1 >> pa2;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    
    dijkstra(pb);
    int d1 = dis[pa1], d2 = dis[pa2];
    
    memset(vis, 0, sizeof(vis));
    dijkstra(pa1);
    
    cout << min(d1, d2) + dis[pa2] << endl;
    return 0;
}
```

---
处理用时：91.57秒