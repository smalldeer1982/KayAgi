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



### 综合分析与结论
题目要求从起点出发，经过两个特定点的最短路径。核心思路是计算两种顺序（PB→PA1→PA2 或 PB→PA2→PA1）的最小值，公式为：  
`min(PB到PA1的最短路 + PA1到PA2的最短路, PB到PA2的最短路 + PA2到PA1的最短路)`  
由于是无向图，PA1-PA2与PA2-PA1距离相等，只需计算一次。多数题解采用 Dijkstra 堆优化（稳定通过），部分使用 SPFA+SLF 优化（需注意数据卡常）。

---

### 精选题解与评分

#### 1. 作者：Kalium（评分：★★★★★）
- **关键亮点**：代码结构清晰，注释详细，三次 Dijkstra 调用分别计算 PB→PA1/PA2 及 PA1→PA2，逻辑严谨。
- **核心思路**：  
  ```cpp
  dijkstra(pb); // PB到各点
  dijkstra(pa1); // PA1到各点
  dijkstra(pa2); // PA2到各点
  ans = min(dis_pb_pa1 + dis_pa1_pa2, dis_pb_pa2 + dis_pa2_pa1);
  ```
- **个人心得**：强调输入顺序（边数在前，点数在后）易错点，避免低级错误。

#### 2. 作者：Star1_3st（评分：★★★★☆）
- **关键亮点**：使用 SPFA+SLF 优化，对比 Dijkstra 的优劣，并分享调试经验。
- **核心代码**：双端队列优化入队策略
  ```cpp
  if (b.size() && dis[edge[i].to] < dis[b.front()])
      b.push_front(edge[i].to);
  else
      b.push_back(edge[i].to);
  ```
- **调试教训**：未判断队列空时访问 `front()` 导致 RE，强调代码鲁棒性。

#### 3. 作者：流逝丶（评分：★★★★）
- **关键亮点**：简洁的 Dijkstra 实现，两次最短路解决问题，代码易读。
- **核心代码**：两次调用 Dijkstra
  ```cpp
  dijkstra(s); // 计算PB到PA1/PA2
  ans = min(dis[s1], dis[s2]);
  dijkstra(s2); // 计算PA2到PA1
  ans += dis[s3];
  ```

---

### 关键技巧总结
1. **算法选择**：正权图优先 Dijkstra 堆优化（稳定 O(m log n)），SPFA 需加 SLF/LLL 优化应对卡常。
2. **路径分析**：只需比较两种顺序的最短路径和，无需考虑复杂分支。
3. **代码优化**：避免冗余计算（如 PA1-PA2 距离只需计算一次），合理复用数据结构。

---

### 推荐相似题目
1. [P4779 - 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)  
   **练习点**：Dijkstra 堆优化模板。
2. [P1119 - 灾后重建](https://www.luogu.com.cn/problem/P1119)  
   **练习点**：动态更新最短路径，多时间点查询。
3. [P1462 - 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)  
   **练习点**：最短路与条件（费用限制）结合。

---
处理用时：57.77秒