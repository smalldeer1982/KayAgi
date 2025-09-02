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
本题要求计算满足奶牛挤奶先后顺序下的最小总时间，大部分题解采用拓扑排序算法，部分使用暴力搜索并进行记忆化优化。拓扑排序通过记录节点入度，从入度为 0 的节点开始，逐步删除边并更新后续节点的时间，最终得到最长路径即最小总时间。暴力搜索则从每个节点出发，递归计算后续节点的最大时间和，使用记忆化避免重复计算。

### 所选题解
- **作者：Datura_（5 星）**
    - **关键亮点**：思路清晰，代码简洁易懂，使用广搜删边法实现拓扑排序，详细注释便于理解。
    - **核心代码**：
```cpp
while(!q.empty())
{
    int u=q.front();
    q.pop();
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        d[v]--;
        tot[v]=max(tot[v],tot[u]+t[v]);
        if(d[v]==0)q.push(v);
    }
}
```
    - **核心思想**：从入度为 0 的节点开始，不断删除边并更新后续节点的最早完成时间，当节点入度为 0 时加入队列继续处理。

- **作者：Ginger_he（4 星）**
    - **关键亮点**：对题目进行深入分析，证明了所求为图的最长路，代码规范，注释清晰。
    - **核心代码**：
```cpp
while(!q.empty())
{
    int tmp=q.front();
    q.pop();
    for(int i=0;i<g[tmp].size();i++)
    {
        f[g[tmp][i]]=max(f[g[tmp][i]],f[tmp]+t[g[tmp][i]]);
        if(--r[g[tmp][i]]==0)
            q.push(g[tmp][i]);
    }
}
```
    - **核心思想**：利用拓扑排序，在处理每个节点时更新其后续节点的最早完成时间，确保满足先后顺序。

- **作者：编程客（4 星）**
    - **关键亮点**：详细介绍拓扑排序思路和本题解法，使用快读快写优化输入输出，提高代码效率。
    - **核心代码**：
```cpp
while(!q.empty())
{
    int u=q.front();
    q.pop();
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        s[v]=max(s[v],s[u]+t[v]);
        d[v]--;
        if(d[v]==0)
        {
            q.push(v);
        }
    }
}
```
    - **核心思想**：通过拓扑排序更新每个节点的挤奶完成时间，最终取最大值得到总时间。

### 最优关键思路或技巧
- **拓扑排序**：处理有先后顺序的问题，通过记录节点入度，从入度为 0 的节点开始，逐步更新后续节点的时间。
- **记忆化搜索**：在暴力搜索中，使用数组记录已经计算过的节点的结果，避免重复计算，降低时间复杂度。
- **快读快写**：在输入输出数据量较大时，使用快读快写优化输入输出，提高代码效率。

### 可拓展之处
同类型题如项目安排问题，每个项目有前置要求和所需时间，求完成所有项目的最短时间；课程安排问题，每门课程有先修课程和学时，求修完所有课程的最短时间。类似算法套路可用于解决有向无环图中的最长路径、最短路径问题。

### 推荐题目
- P1113 杂务：有多个任务，每个任务有前置任务和所需时间，求完成所有任务的最短时间。
- P1983 车站分级：有多个车站，每个车次有停靠站和不停靠站，求车站的最高等级。
- P2853 [USACO06DEC]Cow Picnic S：有多个牧场和奶牛，每个奶牛可以到达一些牧场，求所有奶牛都能到达的牧场数量。

### 个人心得摘录与总结
- **dingcx**：最初使用暴力搜索，后来学习拓扑排序发现两种方法有相似之处，同时指出暴力搜索可能会超内存，需要用 vector 优化。总结为学习新算法后可对比不同方法的异同，同时注意代码的空间复杂度。
- **编程客**：分享成为洛谷最优解的经验，强调时间复杂度的重要性，建议学习快读快写，多做题掌握算法。总结为优化代码复杂度可提高排名，多练习有助于掌握算法。 

---
处理用时：33.78秒