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

本题的核心是通过最短路算法求解从起点出发，经过两个终点的最短路径。大多数题解都采用了Dijkstra算法或SPFA算法，部分题解还引入了优化策略（如SLF、LLL优化）来提升性能。整体来看，Dijkstra算法由于其稳定性和效率，更适合本题的正权图。SPFA虽然在某些情况下表现良好，但容易被卡，因此不推荐在正权图中使用。

### 所选高星题解

#### 1. **作者：Star1_3st (赞：11)**
- **星级**：★★★★★
- **关键亮点**：
  - 使用了SPFA算法，并引入了SLF优化，显著提升了性能。
  - 通过两次最短路求解，思路清晰，代码简洁。
  - 提供了详细的优化思路和调试经验，帮助读者理解SPFA的优化策略。
- **个人心得**：
  - 作者在调试过程中发现SLF优化时未判断队列是否为空，导致RE，提醒读者在优化时要注意边界条件。
- **核心代码**：
  ```cpp
  int spfa(int s,int t)
  {
      memset(book,0,sizeof(book));
      memset(dis,0x7f,sizeof(dis));
      b.push_front(s);
      book[s]=1;
      dis[s]=0;
      while(b.size())
      {
          int x=b.front();
          b.pop_front();
          book[x]=0;
          for(int i=head[x];i;i=edge[i].next)
              if(dis[edge[i].to]>dis[x]+edge[i].dis)
              {
                  dis[edge[i].to]=dis[x]+edge[i].dis;
                  if(!book[edge[i].to])
                  {
                      book[edge[i].to]=1;
                      if(b.size()&&dis[edge[i].to]<dis[b.front()])
                          b.push_front(edge[i].to);
                      else
                          b.push_back(edge[i].to);
                  }
              }
      }
      return dis[t];
  }
  ```
  **核心思想**：通过SLF优化SPFA，优先处理距离更小的节点，减少队列操作次数。

#### 2. **作者：流逝丶 (赞：9)**
- **星级**：★★★★☆
- **关键亮点**：
  - 使用Dijkstra算法，代码结构清晰，易于理解。
  - 通过两次Dijkstra求解，分别计算起点到两个终点的最短路径，再计算两个终点之间的最短路径。
  - 代码中使用了优先队列优化，提升了算法效率。
- **核心代码**：
  ```cpp
  void di(int s)
  {
      for(int i=1;i<=n;++i)d[i]=2147483647;
      memset(in,0,sizeof(in));
      dij.push((edge){0,s});
      d[s]=0;
      while(!dij.empty())
      {
          int t=dij.top().nm;
          dij.pop();
          if(in[t])continue;
          in[t]=1;
          for(int i=head[t];i!=0;i=e[i].nxt)
          {
              if(!in[e[i].to]&&d[t]+e[i].dis<d[e[i].to])
              {
                  d[e[i].to]=d[t]+e[i].dis;
                  dij.push((edge){d[e[i].to],e[i].to});
              }	
          }
      }
  }
  ```
  **核心思想**：通过Dijkstra算法计算单源最短路径，使用优先队列优化。

#### 3. **作者：_jimmywang_ (赞：6)**
- **星级**：★★★★☆
- **关键亮点**：
  - 使用Dijkstra算法，代码简洁明了。
  - 通过两次Dijkstra求解，分别计算起点到两个终点的最短路径，再计算两个终点之间的最短路径。
  - 代码中使用了优先队列优化，提升了算法效率。
- **核心代码**：
  ```cpp
  void dijkstra(int x)
  {
      memset(vis,0,sizeof(vis));
      memset(dis,127,sizeof(dis));
      q.push((node){0,x});
      dis[x]=0;
      while(!q.empty())
      {
          int u=q.top().now;
          q.pop();
          if(vis[u])continue;
          vis[u]=1;
          for(int i=head[u];i;i=e[i].nx)
          {
              int v=e[i].v;
              if(dis[v]>dis[u]+e[i].w)
              {
                  dis[v]=dis[u]+e[i].w;
                  q.push((node){dis[v],v});
              }
          }
      }
  }
  ```
  **核心思想**：通过Dijkstra算法计算单源最短路径，使用优先队列优化。

### 最优关键思路与技巧
1. **Dijkstra算法**：在正权图中，Dijkstra算法是最稳定且高效的选择，尤其是结合优先队列优化后，能够快速求解单源最短路径。
2. **SPFA优化**：在负权图中，SPFA算法表现良好，但在正权图中容易被卡。如果使用SPFA，建议引入SLF或LLL优化来提升性能。
3. **路径组合**：通过两次最短路求解，分别计算起点到两个终点的最短路径，再计算两个终点之间的最短路径，最终取最小值。

### 可拓展之处
- **多终点问题**：类似题目可以扩展到多个终点，求解经过多个终点的最短路径。
- **负权图**：如果图中存在负权边，可以考虑使用SPFA或Bellman-Ford算法。

### 推荐题目
1. **P4779 【模板】单源最短路径（标准版）**：练习Dijkstra算法的经典题目。
2. **P3371 【模板】单源最短路径（弱化版）**：适合练习SPFA算法。
3. **P5905 【模板】Johnson 全源最短路径**：适合练习多源最短路径算法。

### 个人心得总结
- **调试经验**：在优化SPFA时，注意边界条件，如队列是否为空，避免RE。
- **算法选择**：在正权图中，优先选择Dijkstra算法，避免SPFA被卡。
- **代码简洁性**：清晰的代码结构和注释有助于提高代码的可读性和可维护性。

---
处理用时：48.85秒