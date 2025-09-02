# 题目信息

# [USACO09OPEN] Hide and Seek S

## 题目描述

Bessie is playing hide and seek (a game in which a number of players hide and a single player (the seeker) attempts to find them after which various penalties and rewards are assessed; much fun usually ensues).

She is trying to figure out in which of N (2 <= N <= 20,000) barns conveniently numbered 1..N she should hide. She knows that FJ (the seeker) starts out in barn 1. All the barns are connected by M (1 <= M <= 50,000) bidirectional paths with endpoints A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i); it is possible to reach any barn from any other through the paths.

Bessie decides that it will be safest to hide in the barn that has the greatest distance from barn 1 (the distance between two barns is the smallest number of paths that one must traverse to get from one to the other). Help Bessie figure out the best barn in which to hide.

奶牛贝西和农夫约翰（FJ）玩捉迷藏，现在有N个谷仓，FJ开始在第一个谷仓，贝西为了不让FJ找到她，当然要藏在距离第一个谷仓最远的那个谷仓了。现在告诉你N个谷仓，和M个两两谷仓间的“无向边”。每两个仓谷间当然会有最短路径，现在要求距离第一个谷仓（FJ那里）最远的谷仓是哪个（所谓最远就是距离第一个谷仓最大的最短路径）？如有多个则输出编号最小的。以及求这最远距离是多少，和有几个这样的谷仓距离第一个谷仓那么远。


## 说明/提示

The farm layout is as follows:

 ![](https://cdn.luogu.com.cn/upload/pic/2815.png) 

Barns 4, 5, and 6 are all a distance of 2 from barn 1. We choose barn 4 because it has the smallest index.



这里谷仓4，5，6距离1号谷仓都是2，但是4编号最小所以输出4.因此最远距离是2且有3个谷仓，依次输出：2和3。 

感谢 wjcwinmt 的贡献翻译


## 样例 #1

### 输入

```
6 7 
3 6 
4 3 
3 2 
1 3 
1 2 
2 4 
5 2 
```

### 输出

```
4 2 3 
```

# AI分析结果

### 综合分析与结论

本题的核心是求解从起点（谷仓1）到其他所有谷仓的最短路径，并找出距离最远的谷仓及其相关信息。由于边的权重均为1，因此可以使用广度优先搜索（BFS）或单源最短路径算法（如Dijkstra、SPFA）来解决。大多数题解都采用了Dijkstra或SPFA算法，部分题解还使用了堆优化来提升效率。

### 所选高星题解

#### 1. 作者：Eason_AC (赞：8)  
**星级：5星**  
**关键亮点：**
- 使用了Dijkstra+堆优化，代码清晰且高效。
- 详细解释了Dijkstra的实现细节，尤其是堆优化的部分。
- 提供了对最大最短路径的处理方法，思路清晰。

**核心代码：**
```cpp
void dj() {
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    q.push(make_pair(0, 1));
    while(!q.empty()) {
        int x = q.top().second;
        q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = h[x]; i; i = e[i].nxt) {
            int v = e[i].to, z = e[i].v;
            if(dis[v] > dis[x] + z) {
                dis[v] = dis[x] + z;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}
```
**个人心得：**
- 强调了`memset`的使用技巧，避免因赋值错误导致程序崩溃。

#### 2. 作者：zengxr (赞：6)  
**星级：4星**  
**关键亮点：**
- 使用了Dijkstra+堆优化，代码简洁。
- 通过优先队列实现了堆优化，代码可读性较高。

**核心代码：**
```cpp
void dijkstra() {
    priority_queue<node> q;
    for(int i = 1; i <= n; i++) dist[i] = 9999999999;
    dist[s] = 0;
    q.push((node){dist[s], s});
    while(!q.empty()) {
        node temp = q.top();
        q.pop();
        int x = temp.pos;
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = now[x]; i; i = pre[i]) {
            int y = son[i];
            if(dist[y] > dist[x] + V[i]) {
                dist[y] = dist[x] + V[i];
                q.push((node){dist[y], y});
            }
        }
    }
}
```

#### 3. 作者：peterwuyihong (赞：4)  
**星级：4星**  
**关键亮点：**
- 使用了SPFA算法，代码简洁且易于理解。
- 通过队列实现了SPFA，适合初学者理解。

**核心代码：**
```cpp
void SPFA() {
    q[++r] = 1;
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    while(l <= r) {
        int x = q[l++];
        v[x] = 0;
        for(int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if(d[y] > d[x] + 1) {
                d[y] = d[x] + 1;
                if(!v[y]) q[++r] = y, v[y] = 1;
            }
        }
    }
}
```

### 最优关键思路与技巧

1. **Dijkstra+堆优化**：在处理单源最短路径问题时，Dijkstra算法结合堆优化可以有效提升效率，尤其是在边权为非负的情况下。
2. **SPFA**：虽然SPFA在最坏情况下时间复杂度较高，但在实际应用中，尤其是在边权为1的情况下，SPFA的表现通常较好，且代码实现简单。
3. **最大最短路径的处理**：通过遍历所有点的最短路径，找出最大值及其对应的点，再统计满足条件的点的数量。

### 可拓展之处

- **负权边**：如果图中存在负权边，Dijkstra算法不再适用，可以考虑使用Bellman-Ford或SPFA算法。
- **多源最短路径**：如果需要求解多源最短路径，可以考虑Floyd-Warshall算法。

### 推荐题目

1. **P3371 【模板】单源最短路径（弱化版）**  
   考察Dijkstra算法的基本实现。
   
2. **P4779 【模板】单源最短路径（标准版）**  
   考察Dijkstra+堆优化的实现。

3. **P3385 【模板】负环**  
   考察SPFA算法及其在负权图中的应用。

### 个人心得总结

- **调试经历**：多位作者提到在实现Dijkstra时，`memset`的使用需要注意，避免因赋值错误导致程序崩溃。
- **顿悟感想**：通过优先队列实现堆优化，可以大大提升Dijkstra算法的效率，尤其是在处理大规模数据时。

---
处理用时：44.74秒