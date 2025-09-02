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

这道题主要围绕奶牛挤奶先后顺序，求最小总挤奶时间，众多题解都采用拓扑排序算法。
1. **思路**：构建有向图，奶牛为节点，挤奶先后顺序为边，通过拓扑排序遍历图，计算每头牛完成挤奶的时间，全局最大时间即答案。
2. **算法要点**：记录每个节点入度，入度为0的节点先处理；遍历节点时，更新后续节点完成时间；最终取所有节点完成时间的最大值。
3. **解决难点**：理解题目中先后顺序与拓扑排序的联系，明确计算每头牛完成时间的方式，以及如何处理图可能不连通的情况。

对各题解的评分如下：
1. **作者：Datura_ (赞：19)**：★★★★
    - **关键亮点**：思路清晰，代码简洁，直接套用拓扑排序删边法模板，注释详细，易理解。
    - **重点代码**：
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
核心实现思想：从队列取出节点u，遍历其邻接节点v，更新v的入度和完成时间，若v入度为0则入队。
2. **作者：Ginger_he (赞：8)**：★★★★
    - **关键亮点**：先证明所求为图的最长路，思路独特清晰，代码规范简洁。
    - **重点代码**：
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
核心实现思想：与上一代码类似，从队列取节点tmp，更新邻接节点g[tmp][i]的完成时间，若其入度为0则入队。
3. **作者：编程客 (赞：3)**：★★★
    - **关键亮点**：详细阐述拓扑排序思路及本题应用，还介绍快读快写优化方法。
    - **重点代码**：
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
核心实现思想：从队列取节点u，更新邻接节点v的完成时间s[v]，更新v入度，若为0则入队。

**最优关键思路或技巧**：利用拓扑排序处理有先后顺序的任务调度问题，通过记录入度确定任务执行顺序，在遍历过程中动态更新任务完成时间，最后取最大值得到总时间。

**同类型题或类似算法套路**：此类题通常涉及有向无环图的任务调度，关键是建立图结构并正确使用拓扑排序。类似套路可用于课程安排（课程先后顺序）、工序安排等问题。

**推荐题目**：
1. P1983 车站分级：给定列车停靠站点信息，确定最少的车站级别，需用拓扑排序确定车站之间的等级关系。
2. P2882 [USACO07MAR]Face The Right Way G：奶牛转向问题，通过分析转向先后关系，用拓扑排序解决。
3. P3387 【模板】缩点：先对有向图缩点，再在新图上进行拓扑排序解决问题。

**个人心得摘录与总结**：部分作者提到拓扑排序是解决此类先后顺序问题的常用方法；还有作者指出暴力方法易超时或超空间，需用vector优化或记忆化搜索剪枝；有的强调数组大小要合适，避免运行时错误。 

---
处理用时：23.57秒