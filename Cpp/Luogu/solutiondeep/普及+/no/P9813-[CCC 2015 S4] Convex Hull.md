# 题目信息

# [CCC 2015 S4] Convex Hull

## 题目描述

给定一个 $n$ 个点，$m$ 条边的无向图，每条边有两个边权 $t_{i}$ 和 $h_{i}$。

你需要找到一条从 $s$ 到 $t$ 的路径，满足路径上边的 $h_{i}$ 之和 $<k$ 且 $t_{i}$ 之和最小，只需要输出这个最小值即可，如果无法找到满足条件的路径，输出 $-1$。

## 说明/提示

**【数据范围】：**

对于 $20\%$ 的数据，$k = 1$，$2 \leq n \leq 200$。

对于另外 $20\%$ 的数据，$k = 1$，$2 \leq n \leq 2 \times 10^{3}$。

对于 $100\%$ 的数据，$0 \leq h_{i} \leq 200$，$1 \leq t_{i} \leq 10^{5}$，$1 \leq k \leq 200$，$2 \leq n \leq 2 \times 10^{3}$，$1 \leq m \leq 10^{4}$，$s \neq t$。

## 样例 #1

### 输入

```
10 4 7
1 2 4 4
1 3 7 2
3 1 8 1
3 2 2 2
4 2 1 6
3 4 1 1
1 4 6 12
1 4```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3 3
1 2 5 1
3 2 8 2
1 3 1 3
1 3```

### 输出

```
-1```

# AI分析结果

### 算法分类
最短路

### 综合分析与结论
本题的核心是寻找一条从起点到终点的路径，满足路径上边的 $h_i$ 之和小于 $k$，且 $t_i$ 之和最小。这是一个典型的最短路问题，但由于多了一个 $h_i$ 的限制，需要采用分层图或二维状态的最短路算法来解决。

### 所选高星题解
1. **作者：过氧化氢_syq0057 (5星)**
   - **关键亮点**：使用二维 $dis$ 和 $vis$ 数组，结合 Dijkstra 算法，通过松弛操作更新状态。代码清晰，思路明确，优化程度高。
   - **核心代码**：
     ```cpp
     void dijkstra(int st) {
         memset(dis, 0x3f, sizeof(dis));
         dis[st][0] = 0;
         Q.push((node){st, 0, 0});
         int q, u, v, h;
         while (!Q.empty()) {
             u = Q.top().x, h = Q.top().H;
             Q.pop();
             if (vis[u][h]) continue;
             vis[u][h] = 1;
             for (int i=head[u]; ~i; i=Next[i]) {
                 v = ver[i];
                 if (h + edgeh[i] < k && dis[v][h + edgeh[i]] > dis[u][h] + edge[i]) {
                     dis[v][h + edgeh[i]] = dis[u][h] + edge[i];
                     if (!vis[v][h + edge[i]]) Q.push((node){v, dis[v][h + edgeh[i]], h + edgeh[i]});
                 }
             }
         }
     }
     ```

2. **作者：RAINBOW_ddd (4星)**
   - **关键亮点**：通过二维 $dis$ 数组和优先队列实现 Dijkstra 算法，代码简洁，思路清晰，适合初学者理解。
   - **核心代码**：
     ```cpp
     void dj(){
         memset(dis,0x3f,sizeof(dis));
         dis[S][0]=0;
         priority_queue<pair<int,int> >q;
         q.push(make_pair(0,S));
         while(!q.empty()){
             int now=q.top().second;q.pop();
             for(int i=head[now];i;i=E[i].nxt){
                 int v=E[i].v,t=E[i].t,h=E[i].h;
                 int minn=0x3f3f3f3f;
                 for(int j=0;j<K-h;j++){
                     if(dis[now][j]+t<dis[v][j+h]){
                         dis[v][j+h]=dis[now][j]+t;
                         minn=min(minn,dis[v][j+h]);
                     }
                 }
                 if(minn!=0x3f3f3f3f) q.push(make_pair(-minn,v));
             }
         }
     }
     ```

3. **作者：Ifyoung (4星)**
   - **关键亮点**：使用二维 $dis$ 数组和优先队列，结合 Dijkstra 算法，通过松弛操作更新状态。代码结构清晰，适合进阶学习。
   - **核心代码**：
     ```cpp
     void dijkstra(int s) {
         memset(dis, 0x3f, sizeof dis);
         dis[s][0] = 0;
         priority_queue <PII, vector <PII>, greater <PII> > q;
         q.push({0, s});
         while (q.size()) {
             auto p = q.top();
             q.pop();
             int u = p.second;
             for (int i = he[u]; i; i = e[i].nxt) {
                 int v = e[i].to, h = e[i].h, t = e[i].t;
                 int minn = 0x3f3f3f3f;
                 for (int j = 0; j < k - h; j ++ ) {
                     if (dis[v][j + h] > dis[u][j] + t) {
                         dis[v][j + h] = dis[u][j] + t;
                         minn = min(minn, dis[v][j + h]);
                     }
                 }
                 if (minn != 0x3f3f3f3f) q.push({minn, v});
             }
         }
     }
     ```

### 最优关键思路或技巧
1. **分层图思想**：通过将图分层，每层代表不同的 $h_i$ 和，从而将问题转化为标准的最短路问题。
2. **二维状态 Dijkstra**：使用二维数组记录状态，通过松弛操作更新最短路径，确保 $h_i$ 和小于 $k$。

### 可拓展之处
- **类似问题**：可以扩展到其他带限制条件的最短路问题，如路径长度限制、边权限制等。
- **算法优化**：可以考虑使用 A* 算法或其他启发式搜索算法进一步优化。

### 推荐题目
1. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录
- **调试经历**：在实现过程中，需要注意二维数组的初始化，以及优先队列的使用，避免重复入队。
- **踩坑教训**：在松弛操作时，确保 $h_i$ 和不超过 $k$，否则会导致错误结果。
- **顿悟感想**：通过分层图的思想，将复杂问题转化为标准的最短路问题，思路清晰，易于实现。

---
处理用时：33.13秒