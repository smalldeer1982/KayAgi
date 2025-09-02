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
本题核心是求所有牧场到指定F个点的最短路径之和的最小值。题解主要采用两种思路：**Floyd算法（多源最短路）**与**多次Dijkstra/SPFA（单源最短路）**。Floyd实现简单但时间复杂度高（O(n³)），适用于小规模数据；多次Dijkstra在稀疏图中更高效（O(n² log n)），适合本题数据规模。

---

### 精选题解与评分

#### 1. 万弘（★★★★★）
**关键亮点**：  
- 采用堆优化Dijkstra，时间复杂度显著优于Floyd。  
- 代码结构清晰，处理了不可达情况的边界条件（返回INF）。  
- 通过多次单源最短路计算，精准处理稀疏图。

**核心代码**：  
```cpp
ll Dij(ll s) {
    // 初始化距离数组
    for(ll i=1;i<=p;++i) dis[i]=INF;
    dis[s]=0;
    priority_queue<Heap> q;
    q.push({s,0});
    // Dijkstra核心松弛操作
    while(!q.empty()) {
        auto t=q.top(); q.pop();
        ll u=t.u;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:G[u]) {
            if(dis[u]+e.w < dis[e.v]) {
                dis[e.v] = dis[u]+e.w;
                q.push({e.v, dis[e.v]});
            }
        }
    }
    // 求和并返回结果
    ll sum=0;
    for(int j=1;j<=f;++j) sum += dis[a[j]];
    return sum;
}
```

#### 2. zhaoyp（★★★★☆）
**关键亮点**：  
- 详细解释Floyd动态规划原理，代码注释清晰。  
- 正确处理邻接矩阵初始化和双向边。  
- 强调Floyd的滚动数组优化，适合教学。

**核心代码**：  
```cpp
void DP_floyd() {
    for(int k=1;k<=p;++k)
        for(int i=1;i<=p;++i)
            for(int j=1;j<=p;++j)
                floyd[i][j] = min(floyd[i][j], floyd[i][k]+floyd[k][j]);
}
```

#### 3. zfn07（★★★★☆）
**关键亮点**：  
- 使用SPFA算法，提供另一种实现思路。  
- 通过队列优化避免重复松弛，代码简洁高效。  
- 明确处理不可达情况（累加时跳过INF）。

**核心代码**：  
```cpp
void spfa(int s) {
    // SPFA松弛与队列管理
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u=q.front(); q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].next) {
            int v=e[i].to;
            if(dis[u]+e[i].w < dis[v]) {
                dis[v] = dis[u]+e[i].w;
                if(!vis[v]) q.push(v), vis[v]=1;
            }
        }
    }
}
```

---

### 关键技巧与拓展
1. **算法选择**：稀疏图优先用堆优化Dijkstra或SPFA，稠密图可考虑Floyd。  
2. **初始化技巧**：最短路径问题中，务必正确设置对角线为0，其余为INF。  
3. **同类型题目**：  
   - [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)  
   - [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)  
   - [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)  

---

### 个人心得摘录
- **万弘**：调试时发现未初始化`dis`数组导致错误，强调初始化的必要性。  
- **autoint**：使用`INF`时注意溢出问题，改用`0x3fffffff`避免求和越界。  
- **Caicz**：因未赋初值导致WA，提醒初始值设置的重要性。  

总结：最短路径问题需特别注意初始化和边界条件，算法选择应结合数据规模与图的特点。

---
处理用时：67.53秒