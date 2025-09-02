# 题目信息

# [USACO05FEB] Part Acquisition S

## 题目描述

奶牛们接到了寻找一种新型挤奶机的任务，为此它们准备依次经过 $N(1\le N\le 5\times 10^4)$ 颗行星，在行星上进行交易。为了方便，奶牛们已经给可能出现的 $K(1\le K\le 10^3)$ 种货物进行了由 $1$ 到 $K$ 的标号。由于这些行星都不是十分发达。没有流通的货币，所以在每个市场里都只能用固定的一种货物去换取另一种货物。奶牛们带着一种上好的饲料从地球出发，希望在使用的物品的种类数量最少的情况下，最终得到所需要的机器。饲料的标号为 $1$，所需要的机器的标号为 $K$。如果任务无法完成，输出 $-1$。

## 说明/提示

奶牛们至少需要 $4$ 种不同标号的物品，先用 $1$ 去交换 $3$，再用 $3$ 去交换 $2$，最后用 $2$ 交换得到 $5$。

$1\le N\le 5\times 10^4$，$1\le K\le 10^3$。

## 样例 #1

### 输入

```
6 5
1 3
3 2
2 3
3 1
2 5
5 4```

### 输出

```
4```

# AI分析结果

### 综合分析与结论

本题的核心是将货物交换问题转化为图的最短路径问题，使用Dijkstra、SPFA或BFS等算法求解。大多数题解都采用了这一思路，但在实现细节、代码可读性和优化程度上存在差异。以下是对各题解的要点提炼和评分：

1. **思路清晰度**：大部分题解都能清晰地表达将问题转化为图的最短路径问题，并选择合适的算法求解。
2. **代码可读性**：部分题解代码结构清晰，注释详细，易于理解；而有些代码则较为冗长，缺乏必要的注释。
3. **优化程度**：部分题解在算法选择上进行了优化，如使用堆优化的Dijkstra或SPFA，而有些则使用了较为基础的BFS或未优化的Dijkstra。

### 所选高星题解

#### 题解1：DESCENDANTSOFDRAGON (4星)
- **关键亮点**：详细解释了Dijkstra和SPFA的算法流程，代码结构清晰，注释详细，易于理解。
- **核心实现思想**：使用链式前向星存储图，优先队列实现Dijkstra算法，SPFA算法通过队列实现。
- **核心代码片段**：
  ```cpp
  void dijkstra() {
      for(int i=1;i<=n;i++) dis[i]=INF;
      dis[1]=0;
      q.push((node){0,1});
      while(!q.empty()) {
          node x=q.top(); q.pop();
          int u=x.now;
          if(vis[u]) continue;
          vis[u]=1;
          for(int i=head[u];i;i=edge[i].next) {
              int v=edge[i].v;
              if(dis[v]>dis[u]+edge[i].w) {
                  dis[v]=dis[u]+edge[i].w;
                  q.push((node){dis[v],v});
              }
          }
      }
  }
  ```

#### 题解2：jiangxinyang2012 (4星)
- **关键亮点**：简洁明了地解释了SPFA的实现，代码结构清晰，易于理解。
- **核心实现思想**：使用链式前向星存储图，队列实现SPFA算法。
- **核心代码片段**：
  ```cpp
  void spfa() {
      queue<int> q;
      for(int i=1;i<=n;i++) dis[i]=INF;
      q.push(1); dis[1]=1; vis[1]=1;
      while(!q.empty()) {
          int u=q.front(); q.pop(); vis[u]=0;
          for(int i=head[u];i;i=edge[i].next) {
              int v=edge[i].to;
              if(dis[v]>dis[u]+1) {
                  dis[v]=dis[u]+1;
                  if(!vis[v]) {
                      vis[v]=1;
                      q.push(v);
                  }
              }
          }
      }
  }
  ```

#### 题解3：Luxingguang (4星)
- **关键亮点**：详细解释了Dijkstra的堆优化实现，代码结构清晰，注释详细。
- **核心实现思想**：使用链式前向星存储图，优先队列实现Dijkstra算法。
- **核心代码片段**：
  ```cpp
  void dijkstra() {
      memset(dis,0x3f,sizeof(dis));
      memset(vis,0,sizeof(vis));
      dis[1]=0;
      q.push(make_pair(0,1));
      while(q.size()) {
          long long x=q.top().second; q.pop();
          if(vis[x]) continue;
          vis[x]=1;
          for(long long i=head[x];i;i=edge[i].nxt) {
              if(dis[edge[i].to]>dis[x]+edge[i].dis) {
                  dis[edge[i].to]=dis[x]+edge[i].dis;
                  q.push(make_pair(-dis[edge[i].to],edge[i].to));
              }
          }
      }
  }
  ```

### 最优关键思路与技巧

1. **图的最短路径转化**：将货物交换问题转化为图的最短路径问题，选择合适的算法（如Dijkstra、SPFA或BFS）求解。
2. **链式前向星存储图**：使用链式前向星存储图，节省空间且易于遍历。
3. **优先队列优化**：在Dijkstra算法中使用优先队列（堆）优化，提高算法效率。

### 可拓展之处

- **同类型题**：类似的最短路径问题可以应用于其他场景，如网络路由、交通规划等。
- **算法套路**：掌握Dijkstra、SPFA、BFS等最短路径算法，能够解决多种图论问题。

### 推荐题目

1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录

- **调试经历**：部分题解提到在实现过程中遇到无解情况的处理，提醒在代码中要特别注意边界条件的判断。
- **踩坑教训**：有题解提到在Dijkstra算法中未使用堆优化导致效率低下，建议使用优先队列进行优化。
- **顿悟感想**：通过将实际问题转化为图论问题，能够更清晰地理解问题的本质，并选择合适的算法进行求解。

---
处理用时：35.68秒