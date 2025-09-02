# 题目信息

# Journey

## 题目描述

Recently Irina arrived to one of the most famous cities of Berland — the Berlatov city. There are $ n $ showplaces in the city, numbered from $ 1 $ to $ n $ , and some of them are connected by one-directional roads. The roads in Berlatov are designed in a way such that there are no cyclic routes between showplaces.

Initially Irina stands at the showplace $ 1 $ , and the endpoint of her journey is the showplace $ n $ . Naturally, Irina wants to visit as much showplaces as she can during her journey. However, Irina's stay in Berlatov is limited and she can't be there for more than $ T $ time units.

Help Irina determine how many showplaces she may visit during her journey from showplace $ 1 $ to showplace $ n $ within a time not exceeding $ T $ . It is guaranteed that there is at least one route from showplace $ 1 $ to showplace $ n $ such that Irina will spend no more than $ T $ time units passing it.

## 样例 #1

### 输入

```
4 3 13
1 2 5
2 3 7
2 4 8
```

### 输出

```
3
1 2 4 
```

## 样例 #2

### 输入

```
6 6 7
1 2 2
1 3 3
3 6 3
2 4 2
4 6 2
6 5 1
```

### 输出

```
4
1 2 4 6 
```

## 样例 #3

### 输入

```
5 5 6
1 3 3
3 5 3
1 2 2
2 4 3
4 5 2
```

### 输出

```
3
1 3 5 
```

# AI分析结果

### 题目重写

#### 题目描述

最近，Irina 来到了 Berland 最著名的城市之一——Berlatov 市。该城市有 $n$ 个景点，编号从 $1$ 到 $n$，其中一些景点通过单向道路连接。Berlatov 的道路设计使得景点之间没有循环路线。

Irina 最初站在景点 $1$，她的旅程终点是景点 $n$。自然地，Irina 希望在旅程中尽可能多地参观景点。然而，Irina 在 Berlatov 的停留时间有限，她不能在该城市停留超过 $T$ 个时间单位。

请帮助 Irina 确定她在从景点 $1$ 到景点 $n$ 的旅程中，在不超过 $T$ 个时间单位的情况下，最多可以参观多少个景点。保证至少存在一条从景点 $1$ 到景点 $n$ 的路线，使得 Irina 花费的时间不超过 $T$ 个时间单位。

#### 样例 #1

##### 输入

```
4 3 13
1 2 5
2 3 7
2 4 8
```

##### 输出

```
3
1 2 4 
```

#### 样例 #2

##### 输入

```
6 6 7
1 2 2
1 3 3
3 6 3
2 4 2
4 6 2
6 5 1
```

##### 输出

```
4
1 2 4 6 
```

#### 样例 #3

##### 输入

```
5 5 6
1 3 3
3 5 3
1 2 2
2 4 3
4 5 2
```

##### 输出

```
3
1 3 5 
```

### 题解分析与结论

#### 综合分析

本题是一个典型的 DAG（有向无环图）上的动态规划问题。由于题目要求的是在时间限制内尽可能多地访问景点，因此需要找到一条从起点到终点的路径，使得路径上的景点数量最多且总时间不超过 $T$。

#### 题解对比与评分

1. **作者：_ReClouds_**  
   - **评分：5星**  
   - **关键亮点**：  
     - 将问题转化为 DAG 上的背包问题，通过枚举点数求距离的最小值，避免了直接枚举距离导致的空间爆炸问题。
     - 使用拓扑排序进行 DP 转移，确保无后效性。
     - 详细解释了状态转移方程，并提供了完整的代码实现。
   - **个人心得**：  
     - 强调了 DAG 的拓扑排序在 DP 中的重要性，确保每个状态的计算顺序正确。

2. **作者：kouylan**  
   - **评分：4星**  
   - **关键亮点**：  
     - 使用二维 DP 状态，$f[i][j]$ 表示从 $1$ 到 $i$ 经过 $j$ 个点的最短路径。
     - 通过拓扑排序确定 DP 的顺序，确保每个点的前驱都被处理完毕。
     - 提供了路径记录的方法，使用 $pre[x][j]$ 记录前驱节点。
   - **个人心得**：  
     - 强调了 DP 状态设计的重要性，尤其是在数据范围较大的情况下，如何通过状态压缩来优化空间。

3. **作者：Purslane**  
   - **评分：4星**  
   - **关键亮点**：  
     - 重新定义 DP 状态，$dp_{i,j}$ 表示到 $i$ 点，经过 $j$ 个点的最短路径。
     - 通过拓扑排序进行 DP 转移，确保无后效性。
     - 提供了路径记录的方法，使用 $pre$ 数组记录前驱节点。
   - **个人心得**：  
     - 强调了 DP 状态设计的灵活性，尤其是在面对大范围数据时，如何通过状态转换来优化空间和时间。

#### 最优关键思路

- **状态设计**：将 DP 状态设计为 $f[i][j]$，表示从起点到第 $i$ 个点，经过 $j$ 个点的最短路径。这种设计避免了直接枚举距离导致的空间爆炸问题。
- **拓扑排序**：通过拓扑排序确定 DP 的计算顺序，确保每个点的前驱都被处理完毕，从而保证 DP 的无后效性。
- **路径记录**：使用 $pre$ 数组记录每个状态的前驱节点，方便最终路径的输出。

#### 可拓展之处

- **类似问题**：类似的问题可以出现在其他 DAG 上的路径优化问题中，如最短路径、最长路径等。
- **算法套路**：DAG 上的动态规划问题通常可以通过拓扑排序来确保无后效性，状态设计则需要根据具体问题进行调整。

#### 推荐题目

1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
3. [P4017 最大流](https://www.luogu.com.cn/problem/P4017)

#### 个人心得摘录

- **调试经历**：在处理 DAG 上的 DP 问题时，拓扑排序的顺序非常重要，确保每个点的前驱都被处理完毕，否则会导致 DP 状态计算错误。
- **踩坑教训**：在状态设计时，直接枚举距离会导致空间爆炸，因此需要通过状态转换来优化空间。
- **顿悟感想**：DP 状态设计的灵活性是解决问题的关键，尤其是在面对大范围数据时，如何通过状态转换来优化空间和时间。

### 核心代码片段

```cpp
void Toposort() {
    queue<int> q;
    q.push(1), f[1][1] = 0, g[1][1] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto it = vec[u].begin(); it != vec[u].end(); it++) {
            int v = it -> first, w = it -> second;
            for(int i = 1; i <= n; i++) {
                if(g[u][i - 1] && f[u][i - 1] + w <= k && f[u][i - 1] + w < f[v][i]) {
                    f[v][i] = f[u][i - 1] + w;
                    g[v][i] = u;
                }
            }
            --in[v]; if(!in[v]) q.push(v);
        }
    }
}
```

**核心实现思想**：通过拓扑排序确定 DP 的计算顺序，确保每个点的前驱都被处理完毕。在 DP 转移过程中，更新从起点到当前点经过 $j$ 个点的最短路径，并记录前驱节点以便输出路径。

---
处理用时：55.59秒