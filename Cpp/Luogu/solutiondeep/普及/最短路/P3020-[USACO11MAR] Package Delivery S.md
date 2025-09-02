# 题目信息

# [USACO11MAR] Package Delivery S

## 题目描述

Farmer John must deliver a package to Farmer Dan, and is preparing to make his journey. To keep the peace, he gives a tasty treat to every cow that he meets along his way and, of course, FJ is so frugal that he would like to encounter as few cows as possible.

农夫约翰必须送一个包裹给农夫丹，并准备去旅行。为了保持和平，他必须给每一头遇到的奶牛一些吃的，当然，FJ很节俭，他想可能遇到尽可能少的奶牛。

FJ has plotted a map of N (1 <= N <= 50,000) barns, connected by M (1 <= M <= 50,000) bi-directional cow paths, each with C\_i (0 <= C\_i <= 1,000) cows ambling along it. A cow path connects two distinct barns, A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i). Two barns may be directly connected by more than one path. He is currently located at barn 1, and Farmer Dan is located at barn N.

FJ 已经绘制了 $N(1 \le N \le 50000)$ 个谷仓的地图，通过 $M(1 \le M \le 50000)$ 条双向牛道，每条双向牛道上有 $c[i](0 \le c[i] \le 1000)$ 奶牛漫步。双向牛道连接两个不同的谷仓，$a[i]$ 和 $b[i](1 \le a[i] \le N,1 \le b[i] \le N, a[i] \neq b[i])$。两个谷仓可以由一条以上的小路直接连接。他目前在 $1$ 号谷仓，农夫丹位于 $N$ 号谷仓。

Consider the following map:

```cpp
           [2]---
          / |    \
         /1 |     \ 6
        /   |      \
     [1]   0|    --[3]
        \   |   /     \2
        4\  |  /4      [6]
          \ | /       /1
           [4]-----[5] 
                3  
```
The best path for Farmer John to take is to go from 1 -> 2 -> 4 -> 5 -> 6, because it will cost him 1 + 0 + 3 + 1 = 5 treats.

Given FJ's map, what is the minimal number of treats that he should bring with him, given that he will feed each distinct cow he meets exactly one treat? He does not care about the length of his journey.


## 样例 #1

### 输入

```
6 8 
4 5 3 
2 4 0 
4 1 4 
2 1 1 
5 6 1 
3 6 2 
3 2 6 
3 4 4 
```

### 输出

```
5 
```

# AI分析结果

### 综合分析与结论

本题是一个典型的最短路问题，要求从起点到终点的路径上遇到的奶牛数量最少。由于数据规模较大（N和M均可达50000），因此需要高效的算法来解决。题解中主要采用了Dijkstra算法（尤其是堆优化版本）和SPFA算法。Dijkstra算法在无负权边的情况下表现稳定且高效，而SPFA算法虽然在平均情况下表现良好，但在最坏情况下可能退化为Bellman-Ford算法，时间复杂度较高。

### 所选高质量题解

#### 1. 作者：Sober_Clever (5星)
- **关键亮点**：代码简洁，使用了堆优化的Dijkstra算法，时间复杂度为O((M+N)logN)，适合本题的数据规模。代码结构清晰，易于理解。
- **个人心得**：作者提到这是“最短路裸题”，适合练手，体现了对算法基础知识的扎实掌握。

```cpp
void dij()
{
    memset(vis,0,sizeof(vis));
    memset(d,127,sizeof(d));
    priority_queue<pair<int,int> > Q;
    d[1]=0,Q.push(make_pair(0,1));
    while(!Q.empty())
    {
        int u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(d[v]>d[u]+e[i].w)
            {
                d[v]=d[u]+e[i].w;
                Q.push(make_pair(-d[v],v));
            }
        }
    }
}
```

#### 2. 作者：寒鸽儿 (4星)
- **关键亮点**：同样使用了堆优化的Dijkstra算法，代码结构清晰，且作者提到使用`if(dnow > d[cur]) continue;`来代替`if(!vis[cur])`，进一步优化了性能。
- **个人心得**：作者建议使用更快的优化技巧，体现了对算法性能的深入理解。

```cpp
void dijkstra() {
    priority_queue<pii> Q;
    memset(d, 0x3f, sizeof(d));
    d[1] = 0; Q.push(make_pair(0, 1));
    while(!Q.empty()) {
        int cur = Q.top().second, dmen = -Q.top().first; Q.pop();
        if(dmen > d[cur]) continue;
        for(int i = head[cur]; i != -1; i = nex[i])
            if(d[ver[i]] > d[cur] + wei[i]) {
                d[ver[i]] = d[cur] + wei[i];
                Q.push(make_pair(-d[ver[i]], ver[i]));
            }
    }
}
```

#### 3. 作者：Exschawasion (4星)
- **关键亮点**：详细对比了多种最短路算法的优缺点，并提供了SPFA和Dijkstra的实现代码，适合对算法有深入了解的读者。
- **个人心得**：作者建议在比赛中尽量使用优化的Dijkstra算法，除非出现负边否则不使用SPFA，体现了对算法选择的谨慎态度。

```cpp
void spfa() {
    memset(d, 0x3f, sizeof(d));
    memset(vis, false, sizeof(vis));
    d[1] = 0, vis[1] = true;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()) {
        int x = Q.front(); Q.pop();
        vis[x] = false;
        for(int i = head[x]; i; i = next[i]) {
            int to = ver[i], len = w[i];
            if(d[to] > d[x] + len) {
                d[to] = d[x] + len;
                if(!vis[to]) Q.push(to), vis[to] = true;
            }
        }
    }
}
```

### 最优关键思路与技巧

- **堆优化的Dijkstra算法**：在无负权边的情况下，堆优化的Dijkstra算法是最佳选择，时间复杂度为O((M+N)logN)，适合大规模数据。
- **SPFA算法的谨慎使用**：虽然SPFA在平均情况下表现良好，但在最坏情况下可能退化为O(NM)，因此在不确保数据性质的情况下，应优先选择Dijkstra算法。

### 拓展思路与类似题目

- **拓展思路**：在处理最短路问题时，除了Dijkstra和SPFA，还可以考虑A*算法、Floyd-Warshall算法等，具体选择应根据问题的特点和数据规模。
- **类似题目**：
  1. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
  2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
  3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得总结

- **调试与优化**：在实际编码中，调试和优化是不可避免的。例如，使用`if(dnow > d[cur]) continue;`来代替`if(!vis[cur])`可以进一步提升性能。
- **算法选择**：在比赛中，算法的选择至关重要。优先选择稳定且高效的算法，如堆优化的Dijkstra算法，避免使用可能被卡掉的算法，如SPFA。

---
处理用时：37.11秒