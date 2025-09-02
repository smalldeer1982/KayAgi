# 题目信息

# [USACO2.4] 回家 Bessie Come Home

## 题目描述

现在是晚餐时间，而母牛们在外面分散的牧场中。 

Farmer John 按响了电铃，所以她们开始向谷仓走去。 你的工作是要指出哪只母牛会最先到达谷仓（在给出的测试数据中，总会**有且只有**一只最快的母牛）。在挤奶的时候（晚餐前），每只母牛都在她自己的牧场上，一些牧场上可能没有母牛。

每个牧场由一条条道路和一个或多个牧场连接（可能包括自己）。有时，两个牧场（可能是字母相同的）之间会有超过一条道路相连。至少有一个牧场和谷仓之间有道路连接。因此，所有的母牛最后都能到达谷仓，并且母牛总是走最短的路径。当然，母牛能向着任意一方向前进，并且她们以相同的速度前进。牧场被标记为 $\texttt{a} \ldots \texttt{z}$ 和 $\texttt{A} \ldots \texttt{Y}$，在用大写字母表示的牧场中有一只母牛，小写字母中则没有。 谷仓的标记是 $\texttt{Z}$，注意没有母牛在谷仓中。

**注意 $\texttt{m}$ 和 $\texttt{M}$ 不是同一个牧场**。

## 说明/提示

翻译来自 NOCOW

USACO 2.4


## 样例 #1

### 输入

```
5
A d 6
B d 3
C e 9
d Z 8
e Z 3```

### 输出

```
B 11
```

# AI分析结果

### 综合分析与结论

本题的核心是求解从谷仓（Z）到所有有牛的牧场（A-Y）的最短路径，并找出其中最短的路径。由于牧场数量较少（最多52个点），多种最短路算法（如Dijkstra、Floyd、SPFA等）均适用。题解中主要使用了以下几种算法：

1. **Floyd算法**：适用于小规模图，代码简洁，但时间复杂度较高（O(n^3)）。
2. **Dijkstra算法**：经典的单源最短路算法，适合稀疏图，堆优化后效率更高。
3. **SPFA算法**：基于Bellman-Ford的优化算法，适合稀疏图，但最坏情况下时间复杂度较高。

大多数题解都采用了邻接矩阵或邻接表来存储图，并处理了重边和自环的情况。部分题解还使用了堆优化、优先队列等技巧来提升算法效率。

### 精选题解

#### 1. **作者：Obito (赞：13)**
- **星级**：★★★★★
- **关键亮点**：使用了Dijkstra算法，并结合邻接表和优先队列进行优化，代码结构清晰，注释详细，适合初学者理解。
- **核心代码**：
  ```cpp
  void dijkstra(int s){
      for(int i=0;i<=150;i++) dis[i]=INF;
      memset(pre,0,sizeof(pre));
      dis[s]=0;
      q.push(make_pair(0,s));
      while(q.size()){
          int x=q.top().second;
          q.pop();
          if(pre[x]) continue;
          pre[x]=1;
          for(int i=first[x];i;i=next[i]){
              int y=to[i];
              if(dis[y]>dis[x]+w[i]){
                  dis[y]=dis[x]+w[i];
                  q.push(make_pair(-dis[y],y));
              }
          }
      }   
  }
  ```
- **个人心得**：作者提到“堆优化的Dijkstra比标准Dijkstra和Floyd快很多”，强调了优化的重要性。

#### 2. **作者：Gamin (赞：23)**
- **星级**：★★★★☆
- **关键亮点**：使用了Dijkstra算法，结合邻接矩阵存储图，代码简洁易懂，适合初学者。
- **核心代码**：
  ```cpp
  void dj(){
      int u,min;
      for(int i=1;i<=51;i++){
          min=MAXN;
          for(int j=1;j<=51;j++){
              if(vis[j]==0&&dis[j]<min){
                  min=dis[j];
                  u=j;
              }
          }
          vis[u]=1;
          for(int v=1;v<=51;v++){
              if(dis[v]>dis[u]+tu[u][v]&&vis[v]==0&&tu[u][v]<MAXN)
                  dis[v]=dis[u]+tu[u][v];
          }
      }
  }
  ```
- **个人心得**：作者提到“存图当时我一点灵感没有”，最终选择了邻接矩阵，强调了选择合适的存储方式的重要性。

#### 3. **作者：Starlight237 (赞：4)**
- **星级**：★★★★☆
- **关键亮点**：使用了堆优化的Dijkstra算法，结合邻接表存储图，代码结构清晰，注释详细。
- **核心代码**：
  ```cpp
  void Dijkstra(int s){
      priority_queue<Node> Q;
      memset(d,0x3f,sizeof(d));
      d[s]=0;
      Q.push((Node){0,s});
      while(!Q.empty()){
          Node x=Q.top();
          int u=x.u;
          Q.pop();
          if(visd[u]) continue;
          visd[u]=1;
          for(int i=0;i<(int)G[u].size();i++){
              Edge& e=edge[G[u][i]];
              if(d[e.to]>e.dist+d[u]){
                  d[e.to]=e.dist+d[u];
                  Q.push((Node){d[e.to],e.to});
              }
          }
      }
  }
  ```
- **个人心得**：作者提到“堆优化的Dijkstra比标准Dijkstra和Floyd快很多”，强调了优化的重要性。

### 最优关键思路与技巧

1. **选择合适的算法**：对于小规模图，Floyd算法简单易实现；对于大规模稀疏图，Dijkstra算法（尤其是堆优化版本）更为高效。
2. **图的存储方式**：邻接矩阵适合稠密图，邻接表适合稀疏图，选择合适的存储方式可以提升算法效率。
3. **处理重边和自环**：在输入时，需要处理重边和自环，确保图中每条边的权值是最小的。

### 拓展与举一反三

1. **类似题目**：
   - [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
   - [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
   - [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

2. **调试与优化**：在实际编码中，调试和优化是关键。可以通过打印中间结果、使用调试工具等方式来排查问题，优化算法效率。

---
处理用时：40.23秒