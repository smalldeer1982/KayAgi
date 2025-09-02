# 题目信息

# [AGC039B] Graph Partition

## 题目描述

给定一张 $N$ 个顶点，$M$ 条边的无向连通图。  
顶点以 $1\ldots N$ 编号，边以仅包含 $\texttt{0/1}$ 的邻接矩阵的形式给出。

请判断是否能够将顶点分为 $k$ 个非空集合 $V_1,\ldots,V_k$，使得其满足以下条件。若可以，则最大化 $k$：
 - 对于每条边 $(i,j)$，存在 $1 \le t \le k-1$ 满足 $i \in V_t, j \in V_{t+1}$ 或 $i \in V_{t+1}, j \in V_t$。

## 说明/提示

### 数据限制
- $N \in [2,200] \bigcap \mathbb Z$。
- 邻接矩阵仅由 $\texttt0$ 与 $\texttt1$ 组成。
- 邻接矩阵关于主对角线对称。
- 邻接矩阵主对角线均为 $\texttt0$（无自环）。
- 图一定连通。

#### 样例解释 #1
可以分别将顶点 $1,2$ 分入 $V_1,V_2$。

## 样例 #1

### 输入

```
2

01

10```

### 输出

```
2```

## 样例 #2

### 输入

```
3

011

101

110```

### 输出

```
-1```

## 样例 #3

### 输入

```
6

010110

101001

010100

101000

100000

010000```

### 输出

```
4```

# AI分析结果

### 题目翻译
给定一张有 $N$ 个顶点和 $M$ 条边的无向连通图。  
顶点编号为 $1$ 到 $N$，边以仅包含 $\texttt{0/1}$ 的邻接矩阵形式给出。

请判断是否能够将顶点划分为 $k$ 个非空集合 $V_1,\ldots,V_k$，并满足以下条件。若可以，则最大化 $k$：
 - 对于每条边 $(i,j)$，存在 $1 \le t \le k - 1$ 使得 $i \in V_t$ 且 $j \in V_{t + 1}$，或者 $i \in V_{t + 1}$ 且 $j \in V_t$。

### 综合分析与结论
这三道题解的核心思路都是先利用二分图染色判断是否有解，若有解再进一步求最大的 $k$ 值。不同之处在于求最大 $k$ 值的方法：
- **Rushroom**：使用 Floyd 算法求任意两点间的最短路，然后枚举端点找最大路径长度，加 1 得到 $k$。
- **wowwowwow**：以每个点为起点进行 BFS，记录每个点所属集合编号，找到所有方案中的最大值。
- **GTAyin**：对每个点用 SPFA 算法求最短路，取最大值加 1 得到 $k$。

### 题解评分与选择
- **Rushroom**：3 星。思路清晰，但代码中使用三维的 Floyd 数组较冗余，增加了空间复杂度。
- **wowwowwow**：3 星。思路独特，代码可读性较好，但 BFS 多次遍历会有一定时间开销。
- **GTAyin**：3 星。思路正确，但使用 SPFA 算法在某些情况下可能会超时。

由于所有题解均不足 4 星，故只给出通用建议与扩展思路。

### 通用建议与扩展思路
- **思路**：先利用二分图染色判断图是否可划分，若可划分再通过最短路算法求最大划分数量。
- **算法优化**：可以考虑使用更高效的最短路算法，如 Dijkstra 算法。
- **同类型题或类似算法套路**：此类题目通常涉及图的染色和路径搜索，可参考二分图匹配、图的连通性等相关问题。

### 推荐题目
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：考察二分图染色。
2. [P2825 [HEOI2016/TJOI2016]游戏](https://www.luogu.com.cn/problem/P2825)：涉及图的建模和二分图匹配。
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：考察最短路算法。

### 重点代码与核心思想
#### Rushmush 的 Floyd 求最短路
```cpp
repp(k, n) {
    repp(x, n) {
        repp(y, n) {
            f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y]);
        }
    }
}
repp(i, n)repp(j, n)ans = max(ans, f[n][i][j]);
```
核心思想：通过 Floyd 算法求出任意两点间的最短路，然后枚举端点找到最大路径长度。

#### wowwowwow 的 BFS 求最大划分
```cpp
int BFS(int st){
    for(int i = 1; i <= n; i++) t[i] = 0, vis[i] = 0;
    q.push(st); t[st] = 1; vis[st] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : g[u])
            if(!vis[v]){
                vis[v] = 1;
                t[v] = t[u] + 1;
                q.push(v);
            }
    }
    int maxn = 0;
    for(int i = 1; i <= n; i++){
        maxn = max(maxn, t[i]);
    } 
    return maxn;
}
```
核心思想：以每个点为起点进行 BFS，记录每个点所属集合编号，找到所有方案中的最大值。

#### GTAyin 的 SPFA 求最短路
```cpp
void spfa(int s){
    queue<int> p;
    for(int i=1;i<=n;i++){
        dis[i]=inf;
        bk[i]=false;
    }
    p.push(s);
    dis[s]=0;
    bk[s]=true;
    while(!p.empty()){
        int k=p.front();
        p.pop();
        bk[k]=false;
        for(int i=head[k];i;i=e[i].Next){
            int v=e[i].To;
            if(dis[v]>dis[k]+1){
                dis[v]=dis[k]+1;
                if(!bk[v]){
                    p.push(v);
                    bk[v]=true;
                }
            }
        }
    }
}
```
核心思想：对每个点使用 SPFA 算法求最短路，取最大值加 1 得到最大划分数量。

---
处理用时：32.63秒