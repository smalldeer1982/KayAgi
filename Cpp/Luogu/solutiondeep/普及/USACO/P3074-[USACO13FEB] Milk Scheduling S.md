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
本题核心为拓扑排序求关键路径，所有题解均围绕该思路展开。关键点在于：在满足先后约束下，各并行任务链的最长耗时即为总最短时间（木桶效应）。最优解法为拓扑排序中动态维护各节点的最大完成时间。

---

### 高星题解推荐

#### 1. Datura_（5星）
**核心亮点**：  
- 标准拓扑排序模板，BFS实现清晰易懂  
- 使用`tot[]`数组记录各节点累计时间，逻辑简洁  
- 代码规范，变量命名合理，适合学习实现  

**核心代码**：
```cpp
// 拓扑排序核心部分
while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(int v : g[u]) {
        d[v]--;
        tot[v] = max(tot[v], tot[u] + t[v]); // 关键状态转移
        if(d[v] == 0) q.push(v);
    }
}
```

#### 2. Ginger_he（4星）
**核心亮点**：  
- 数学证明最长路径的合理性  
- 强调独立子图间的并行关系  
- 使用`f[]`数组命名更贴合语义  

**代码亮点**：
```cpp
// 状态转移方程
f[g[tmp][i]] = max(f[g[tmp][i]], f[tmp] + t[g[tmp][i]]);
```

#### 3. dingcx优化版（4星）
**核心亮点**：  
- 记忆化搜索实现拓扑逻辑  
- 使用vector优化空间效率  
- 提供暴力→优化的对比，启发式教学  

**核心函数**：
```cpp
int find(int x) {
    if(f[x]) return f[x];
    for(int v : rule[x]) 
        maxt = max(maxt, find(v));
    return f[x] = maxt + t[x];
}
```

---

### 关键思路总结
1. **拓扑排序框架**：维护入度为0的节点队列，逐步消解依赖关系  
2. **动态规划思想**：`dp[u] = max(dp[pre]) + t[u]`，记录节点u的最早完成时间  
3. **关键路径提取**：最终结果为所有节点dp值的最大值  

---

### 同类题目推荐
1. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)（拓扑排序+最长路径）  
2. [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)（拓扑排序计数应用）  
3. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)（拓扑排序处理隐含关系）

---

### 调试经验摘录
1. **Sunlight9**：初始暴力TLE，改用拓扑后注意"入度为0时才入队"的边界条件  
2. **dingcx**：二维数组MLE教训，改用vector优化空间  
3. **编程客**：强调快读快写对竞赛的重要性，即使算法正确也需注意常数优化  

> 调试启示：拓扑排序中节点的处理顺序直接影响结果，需确保状态转移时前驱节点已完全处理完毕。

---
处理用时：48.86秒