# 题目信息

# [USACO13FEB] Milk Scheduling S

## 题目描述

Farmer John's N cows (1 <= N <= 10,000) are conveniently numbered 1..N. Each cow i takes T(i) units of time to milk.  Unfortunately, some cows must be milked before others, owing to the layout of FJ's barn.  If cow A must be milked before cow B, then FJ needs to completely finish milking A before he can start milking B.

In order to milk his cows as quickly as possible, FJ has hired a large number of farmhands to help with the task -- enough to milk any number of cows at the same time.  However, even though cows can be milked at the same time, there is a limit to how quickly the entire process can proceed due to the constraints requiring certain cows to be milked before others.  Please help FJ compute the minimum total time the milking process must take.

农民约翰有N头奶牛(1<=N<=10,000)，编号为1...N。每一头奶牛需要T(i)单位的时间来挤奶。不幸的是，由于FJ的仓库布局，一些奶牛要在别的牛之前挤奶。比如说，如果奶牛A必须在奶牛B前挤奶，FJ就需要在给奶牛B挤奶前结束给奶牛A的挤奶。


为了尽量完成挤奶任务，FJ聘请了一大批雇工协助任务——同一时刻足够去给任意数量的奶牛挤奶。然而，尽管奶牛可以同时挤奶，但仍需要满足以上的挤奶先后顺序。请帮助FJ计算挤奶过程中的最小总时间。


## 说明/提示

There are 3 cows.  The time required to milk each cow is 10, 5, and 6, respectively.  Cow 3 must be fully milked before we can start milking cow 2.


Cows 1 and 3 can initially be milked at the same time.  When cow 3 is finished with milking, cow 2 can then begin.  All cows are finished milking after 11 units of time have elapsed.


## 样例 #1

### 输入

```
3 1 
10 
5 
6 
3 2 
```

### 输出

```
11 
```

# AI分析结果

### 综合分析与结论

本题的核心是通过拓扑排序解决有向无环图（DAG）中的任务调度问题，目标是找到所有任务完成的最小总时间。大多数题解都采用了拓扑排序的思路，结合广度优先搜索（BFS）或深度优先搜索（DFS）来实现。拓扑排序的关键在于处理任务的依赖关系，并通过动态规划或贪心策略来计算每个任务的最早完成时间。

### 所选高星题解

#### 1. 作者：Datura_ (5星)
**关键亮点**：
- 使用了标准的拓扑排序模板，代码简洁且易于理解。
- 通过队列管理入度为0的节点，逐步处理依赖关系。
- 使用 `tot` 数组记录每个节点的最早完成时间，最终取最大值作为结果。

**核心代码**：
```cpp
while(!q.empty()) {
    int u=q.front();
    q.pop();
    for(int i=0;i<g[u].size();i++) {
        int v=g[u][i];
        d[v]--; // 删边
        tot[v]=max(tot[v],tot[u]+t[v]); // 更新最早完成时间
        if(d[v]==0) q.push(v); // 入度为0的节点入队
    }
}
```
**个人心得**：
- 作者提到“拓扑排序模板题”，强调了该题的标准性，适合初学者掌握拓扑排序的基本应用。

#### 2. 作者：Ginger_he (4星)
**关键亮点**：
- 详细解释了拓扑排序的应用场景，并指出本题实际上是求图的最长路。
- 通过 `f` 数组记录每个节点的最早完成时间，最终取最大值作为结果。

**核心代码**：
```cpp
while(!q.empty()) {
    int tmp=q.front();
    q.pop();
    for(int i=0;i<g[tmp].size();i++) {
        f[g[tmp][i]]=max(f[g[tmp][i]],f[tmp]+t[g[tmp][i]]); // 更新最早完成时间
        if(--r[g[tmp][i]]==0) q.push(g[tmp][i]); // 入度为0的节点入队
    }
}
```
**个人心得**：
- 作者提到“虽然这道题问的是总时间的最小值，但我们要求的是这张图的最长路”，强调了问题的本质。

#### 3. 作者：编程客 (4星)
**关键亮点**：
- 使用了快读快写优化输入输出，提升了代码的效率。
- 通过 `s` 数组记录每个节点的最早完成时间，最终取最大值作为结果。

**核心代码**：
```cpp
while(!q.empty()) {
    int u=q.front();
    q.pop();
    for(int i=0;i<g[u].size();i++) {
        int v=g[u][i];
        s[v]=max(s[v],s[u]+t[v]); // 更新最早完成时间
        d[v]--;
        if(d[v]==0) q.push(v); // 入度为0的节点入队
    }
}
```
**个人心得**：
- 作者提到“洛谷的最优解主要在于时间复杂度和空间复杂的”，强调了代码优化的必要性。

### 最优关键思路与技巧

1. **拓扑排序**：通过处理入度为0的节点，逐步解决依赖关系，确保任务按顺序执行。
2. **动态规划**：通过 `tot` 或 `f` 数组记录每个节点的最早完成时间，最终取最大值作为结果。
3. **队列管理**：使用队列管理入度为0的节点，确保拓扑排序的高效执行。

### 可拓展之处

- **类似问题**：任务调度、项目管理、课程安排等涉及依赖关系的场景。
- **算法优化**：可以结合优先队列（堆）优化任务调度顺序，进一步提升效率。

### 推荐题目

1. [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
2. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)
3. [P2742 [USACO5.1]圈奶牛Fencing the Cows](https://www.luogu.com.cn/problem/P2742)

### 个人心得总结

- **调试经历**：多位作者提到在调试过程中发现数组越界或重复计算的问题，强调了代码细节的重要性。
- **顿悟感想**：通过拓扑排序解决依赖关系问题，理解了图论在实际应用中的强大功能。

---
处理用时：36.95秒