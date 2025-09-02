# 题目信息

# [USACO09JAN] Best Spot S

## 题目描述

Bessie, always wishing to optimize her life, has realized that she really enjoys visiting F (1 <= F <= P) favorite pastures F\_i of the P (1 <= P <= 500; 1 <= F\_i <= P) total pastures (conveniently

numbered 1..P) that compose Farmer John's holdings.

Bessie knows that she can navigate the C (1 <= C <= 8,000) bidirectional cowpaths (conveniently numbered 1..C) that connect various pastures to travel to any pasture on the entire farm. Associated with each path P\_i is a time T\_i (1 <= T\_i <= 892) to traverse that path (in either direction) and two path endpoints a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P).

Bessie wants to find the number of the best pasture to sleep in so that when she awakes, the average time to travel to any of her F favorite pastures is minimized.

By way of example, consider a farm laid out as the map below shows, where \*'d pasture numbers are favorites. The bracketed numbers are times to traverse the cowpaths.

```cpp

            1*--[4]--2--[2]--3
                     |       |
                    [3]     [4]
                     |       |
                     4--[3]--5--[1]---6---[6]---7--[7]--8*
                     |       |        |         |
                    [3]     [2]      [1]       [3]
                     |       |        |         |
                    13*      9--[3]--10*--[1]--11*--[3]--12*
```
The following table shows distances for potential 'best place' of pastures 4, 5, 6, 7, 9, 10, 11, and 12:

```cpp
      * * * * * * Favorites * * * * * *
 Potential      Pasture Pasture Pasture Pasture Pasture Pasture     Average
Best Pasture       1       8      10      11      12      13        Distance
------------      --      --      --      --      --      --      -----------
    4              7      16       5       6       9       3      46/6 = 7.67
    5             10      13       2       3       6       6      40/6 = 6.67
    6             11      12       1       2       5       7      38/6 = 6.33
    7             16       7       4       3       6      12      48/6 = 8.00
    9             12      14       3       4       7       8      48/6 = 8.00
   10             12      11       0       1       4       8      36/6 = 6.00 ** BEST
   11             13      10       1       0       3       9      36/6 = 6.00
   12             16      13       4       3       0      12      48/6 = 8.00

```
Thus, presuming these choices were the best ones (a program would have to check all of them somehow), the best place to sleep is pasture 10.

约翰拥有 $P(1 \leq P \leq 500)$ 个牧场，贝茜特别喜欢其中的 $F$ 个。所有的牧场由 $C(1 < C \leq 8000)$条双向路连接，第 $i$ 条路连接着 $a_i,b_i$，需要 $T_i(1 \leq T_i < 892)$ 个单位时间来通过。

作为一只总想优化自己生活方式的奶牛，贝茜喜欢自己某一天醒来，到达所有那 $F$ 个她喜欢的牧场的平均需时最小。那她前一天应该睡在哪个牧场呢？请帮助贝茜找到这个最佳牧场。

由样例解释可见，在样例环境下，牧场 $10$ 到所有贝茜喜欢的牧场的平均距离最小，为最佳牧场。


## 说明/提示

As the problem statement


As the problem statement.


## 样例 #1

### 输入

```
13 6 15 
11 
13 
10 
12 
8 
1 
2 4 3 
7 11 3 
10 11 1 
4 13 3 
9 10 3 
2 3 2 
3 5 4 
5 9 2 
6 7 6 
5 6 1 
1 2 4 
4 5 3 
11 12 3 
6 10 1 
7 8 7 
```

### 输出

```
10 
```

# AI分析结果

### 综合分析与结论
该题要求找出到指定F个牧场平均距离最小的牧场。多数题解采用Floyd算法求多源最短路，也有题解使用Dijkstra或SPFA算法。
1. **思路**：
    - **Floyd算法**：通过动态规划，利用状态转移方程$f_{k,i,j} = \min(f_{k - 1,i,j},f_{0,i,k}+f_{0,k,j})$，可求出任意两点间的最短距离，时间复杂度$O(n^3)$。之后枚举每个点到F个喜欢牧场的距离和，找出最小距离和对应的点。
    - **Dijkstra算法**：对每个点都跑一次Dijkstra算法求单源最短路，时间复杂度$O(n^2logn)$，再统计每个点到F个喜欢牧场的距离和，取最小值对应的点。
    - **SPFA算法**：与Dijkstra类似，对每个点跑一次SPFA求单源最短路，然后累加距离和找最小值对应的点。
2. **算法要点**：
    - **Floyd**：需正确初始化距离矩阵，注意状态转移方程的实现以及三层循环的顺序。
    - **Dijkstra**：使用优先队列优化，每次从优先队列中取出距离最小的点进行松弛操作。
    - **SPFA**：利用队列存储待更新的点，通过不断更新距离和入队操作求最短路。
3. **难点**：
    - **Floyd**：理解状态转移方程和循环顺序，正确处理距离矩阵的初始化，避免溢出问题。
    - **Dijkstra/SPFA**：多次运行单源最短路算法，注意每次运行前的初始化，以及数据结构的合理使用。

综合来看，Floyd算法代码实现相对简洁，但时间复杂度较高；Dijkstra和SPFA在本题数据规模下也能通过，且时间复杂度相对较低。

### 所选的题解
1. **作者：Cxs3 (5星)**
    - **关键亮点**：思路清晰，先明确指出题目需用Floyd算法求出每个点到F个点的最小距离，再详细阐述步骤，代码实现完整且注释详细，易于理解。
    - **个人心得**：无
    - **重点代码 - Floyd算法实现**：
```cpp
for(k=1;k<=n;k++)
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//DP动态转移方程
```
核心思想：通过三层循环，利用中间节点k更新i到j的最短距离。
    - **重点代码 - 计算距离和并找最小**：
```cpp
for(i=1;i<=n;i++)
{
    sum=0;
    for(j=1;j<=p;j++) sum+=f[i][like[j]];//累加距离和
    if(sum<mi){mi=sum; ans=i;}//更新答案
}
```
核心思想：枚举每个点，计算其到F个喜欢牧场的距离和，与当前最小值比较并更新。
2. **作者：zhaoyp (4星)**
    - **关键亮点**：先详细介绍Floyd算法原理，包括思想、状态转移方程推导等，再针对题目分析步骤，代码结构清晰，函数模块化。
    - **个人心得**：无
    - **重点代码 - Floyd算法实现**：
```cpp
void DP_floyd()//floyd最短路 
{
    for(int k = 1;k <= p;++k)
        for(int i = 1;i <= p;++i)
            for(int j = 1;j <= p;++j)
                floyd[i][j] = min(floyd[i][j],floyd[i][k]+floyd[k][j]);//DP状态转移方程 
}
```
核心思想同Cxs3的Floyd实现。
    - **重点代码 - 遍历所有牧场计算距离和并找最小**：
```cpp
void check()//遍历所有牧场 
{
    for(int i = 1;i <= p;++i)
    {
        sum = 0;
        for(int j = 1;j <= f;++j)
            sum += floyd[i][a[j]];
        if(sum < ans)    ans = sum,cnt = i;//注意如果最好的牧场多于一个，则选择最小的牧场。所以不能用 <= 
    }        
    printf("%d",cnt);    
}
```
核心思想：遍历每个牧场，计算其到喜欢牧场的距离和，更新最小距离和对应的牧场编号。
3. **作者：万弘 (4星)**
    - **关键亮点**：采用Dijkstra算法解决问题，提供了完整代码，对Dijkstra算法实现细节注释清晰，且指出暴力Dijkstra在本题中比Floyd快。
    - **个人心得**：无
    - **重点代码 - Dijkstra算法实现**：
```cpp
ll Dij(ll s)
{
    for(ll i=1;i<=p;++i)dis[i]=INF;
    dis[s]=0;
    q.push((Heap){s,0});
    ll u,v,w,ans=0;
    while(!q.empty())
    {
        t=q.top();q.pop();
        u=t.u;
        if(dis[u]!=t.dis)continue;
        for(ll i=G[u].size()-1;i>=0;--i)
        {
            v=G[u][i].v,w=G[u][i].w;
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                q.push((Heap){v,dis[v]});
            }
        }
    }
    for(ll i=1;i<=f;++i)
    {
        if(dis[a[i]]==INF)return INF;
        ans+=dis[a[i]];
    }
    return ans;
}
```
核心思想：从起点s开始，利用优先队列不断取出距离最小的点，更新其邻接点距离，最后计算到F个喜欢牧场的距离和。

### 最优关键思路或技巧
1. **算法选择**：在数据规模较小时，Floyd算法代码简洁，实现方便；而当数据规模较大时，Dijkstra或SPFA算法的时间复杂度优势更明显，可根据题目数据范围灵活选择算法。
2. **初始化**：无论是哪种算法，正确的初始化至关重要，如Floyd中距离矩阵的初始化，Dijkstra和SPFA中距离数组和访问标记数组的初始化。

### 可拓展思路
1. **同类型题**：此类题目属于图论中求特定点与一组目标点距离相关问题，类似题目常涉及不同的图结构（有向图、无向图）、边权（正权、负权）等变化。
2. **类似算法套路**：在解决多源最短路问题时，Floyd算法是经典选择；对于单源最短路，Dijkstra适用于正权图，SPFA可处理含负权边的图（但SPFA在某些情况下可能会超时）。

### 相似知识点洛谷题目
1. **P1119 灾后重建**：涉及图的动态变化下的最短路问题，可使用Floyd算法结合时间因素求解。
2. **P3371 【模板】单源最短路径（弱化版）**：经典的单源最短路问题，可用于练习Dijkstra算法。
3. **P3385 【模板】负环**：判断图中是否存在负环，可使用SPFA算法进行拓展应用。

### 个人心得摘录与总结
1. **作者：Caicz**：强调了给ans赋极大值以及f数组赋初值的重要性，否则可能导致结果错误，这是在处理最小值比较问题时常见的易错点。 

---
处理用时：37.78秒