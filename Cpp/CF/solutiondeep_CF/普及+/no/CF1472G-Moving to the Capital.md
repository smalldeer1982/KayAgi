# 题目信息

# Moving to the Capital

## 题目描述

### 题意
有一个由 $n$ 个点 $m$ 条边组成的有向图。边长均为 $1$。定义 $d_i$ 为点 $1$ 到点 $i$ 的最短距离。

你要通过以下方法走边，求出从每个点开始，在能到达的点 $i$ 中，$d_i$ 的最小值是多少。

- 若当前在 $i$，有一条 $i \to j$ 的有向边，且 $d_i<d_j$，可以走到 $j$ 无数次。
- 若当前在 $i$，有一条 $i \to j$ 的有向边，且 $d_i \ge d_j$，可以走到 $j$ 至多一次。

注意，至多一次指的是从每个点开始行走时，行走的路径上至多经过一次 $d _ i \ge d _ j$ 的边。

## 说明/提示

$1\leq t\leq 10^4$  
$2\leq n\leq 2\times 10^5$  
$1\leq m\leq 2\times 10^5$  
$1\leq u,v\leq n$  

Translated by @[Cym10x](/user/354015).

## 样例 #1

### 输入

```
3

6 7
1 2
1 3
2 5
2 4
5 1
3 6
6 2

2 2
1 2
2 1

6 8
1 2
1 5
2 6
6 1
2 3
3 4
4 2
5 4```

### 输出

```
0 0 1 2 0 1 
0 0 
0 0 2 1 1 0```

# AI分析结果

### 题目翻译
#### 搬到首都

##### 题目描述
有一个由 $n$ 个点和 $m$ 条边组成的有向图，所有边的长度均为 $1$。定义 $d_i$ 为从点 $1$ 到点 $i$ 的最短距离。

你需要通过以下规则走边，求出从每个点开始，在其能到达的点 $i$ 中，$d_i$ 的最小值。
- 若当前位于点 $i$，存在一条从 $i$ 到 $j$ 的有向边，且 $d_i < d_j$，则可以无数次走到 $j$。
- 若当前位于点 $i$，存在一条从 $i$ 到 $j$ 的有向边，且 $d_i \geq d_j$，则最多可以走到 $j$ 一次。

注意，“最多一次” 指的是从每个点开始行走时，行走路径上最多经过一次 $d_i \geq d_j$ 的边。

##### 说明/提示
$1\leq t\leq 10^4$  
$2\leq n\leq 2\times 10^5$  
$1\leq m\leq 2\times 10^5$  
$1\leq u,v\leq n$  

由 @[Cym10x](/user/354015) 翻译。

##### 样例 #1
**输入**
```
3

6 7
1 2
1 3
2 5
2 4
5 1
3 6
6 2

2 2
1 2
2 1

6 8
1 2
1 5
2 6
6 1
2 3
3 4
4 2
5 4
```
**输出**
```
0 0 1 2 0 1 
0 0 
0 0 2 1 1 0
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先求出点 $1$ 到各点的最短距离 $d_i$，再根据题目给定的行走规则，找出从每个点出发能到达的点中 $d_i$ 的最小值。

- **思路对比**：大部分题解采用先 BFS 求最短距离，再 DFS 遍历图来更新每个点的答案；部分题解使用 Dijkstra 算法求最短距离；还有题解使用分层图的思想。
- **算法要点**：BFS 或 Dijkstra 算法用于求最短距离，DFS 用于遍历图并更新答案。
- **解决难点**：处理 $d_i \geq d_j$ 边最多走一次的限制，通过在 DFS 中特殊处理这类边来解决。

### 所选题解
- **Cylete（4星）**
    - **关键亮点**：思路清晰，代码简洁，先使用 BFS 求最短距离，再用 DFS 遍历更新答案。
- **KSToki（4星）**
    - **关键亮点**：使用 Dijkstra 算法求最短距离，代码规范，注释详细。
- **_zuoqingyuan（4星）**
    - **关键亮点**：详细分析了不同情况下答案的更新方式，时间复杂度为 $O(n)$。

### 重点代码
#### Cylete 的代码
```cpp
inline void bfs() {
    queue<int> q;
    q.push(1); book[1] = 1; dis[1] = 0;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(auto y : edge[x]) {
            if(!book[y]) {
                book[y] = 1;
                dis[y] = dis[x] + 1;
                q.push(y); 
            }
        }
    } 
}

inline void dfs(int x) {
    vis[x] = 1;
    f[x] = dis[x];
    for(auto y : edge[x]) {
        if(!vis[y] && dis[x] < dis[y])
            dfs(y);
        if(dis[x] < dis[y]) f[x] = min(f[x], f[y]);
        else f[x] = min(f[x], dis[y]);
    } 
}
```
**核心实现思想**：`bfs` 函数通过广度优先搜索求出点 $1$ 到各点的最短距离；`dfs` 函数通过深度优先搜索更新每个点能到达的点中 $d_i$ 的最小值。

#### KSToki 的代码
```cpp
I void dijkstra()
{
    for(R int i=1;i<=n;++i)
    {
        dis[i]=0x7fffffff/3;
        vis[i]=0;
    }
    dis[1]=0;
    q.push(mp(0,1));
    while(!q.empty())
    {
        x=q.top().second;
        q.pop();
        if(vis[x])
            continue;
        vis[x]=1;
        for(R int i=head[x];i;i=nxt[i])
        {
            y=to[i];
            if(dis[y]>dis[x]+1)
            {
                dis[y]=dis[x]+1;
                q.push(mp(-dis[y],y));
            }
        }
    }
}

void dfs(int x)
{
    vis[x]=1;
    res[x]=dis[x];
    for(R int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if((!vis[y])&&dis[x]<dis[y])
            dfs(y);
        if(dis[x]<dis[y])
            res[x]=min(res[x],res[y]);
        else
            res[x]=min(res[x],dis[y]);
    }
}
```
**核心实现思想**：`dijkstra` 函数使用 Dijkstra 算法求出点 $1$ 到各点的最短距离；`dfs` 函数通过深度优先搜索更新每个点能到达的点中 $d_i$ 的最小值。

#### _zuoqingyuan 的代码
```cpp
void bfs(int s){
    q.push(s),d[s]=0,mk[s]=1;
    while(q.size()){
        int x=q.front();q.pop();
        for(int i=ver[x];i;i=nxt[i]){
            int y=to[i];
            if(!mk[y]){
                mk[y]=1,d[y]=d[x]+1;
                q.push(y);
            }
        }
    }
    return;
}

void dfs(int x){
    low[x]=d[x],vis[x]=1;
    for(int i=ver[x];i;i=nxt[i]){
        int y=to[i];
        if(!vis[y]&&d[y]>d[x])dfs(y);
        if(d[y]>d[x])low[x]=min(low[x],low[y]);
        else low[x]=min(low[x],d[y]);
    }
    return;
}
```
**核心实现思想**：`bfs` 函数通过广度优先搜索求出点 $1$ 到各点的最短距离；`dfs` 函数通过深度优先搜索更新每个点能到达的点中 $d_i$ 的最小值，详细分析了不同情况下答案的更新方式。

### 最优关键思路或技巧
- 先使用 BFS 或 Dijkstra 算法求出点 $1$ 到各点的最短距离。
- 利用 DFS 遍历图，根据 $d_i$ 和 $d_j$ 的大小关系更新每个点的答案，处理 $d_i \geq d_j$ 边最多走一次的限制。

### 可拓展之处
同类型题或类似算法套路：
- 其他图的遍历问题，如拓扑排序、强连通分量等。
- 带有特殊限制的图的最短路径问题，如边权有正负、有时间限制等。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 个人心得
- **KSToki**：“我太菜了这翻译看不懂。”，反映出阅读题目描述时可能会遇到理解困难的情况。
- **_ChongYun_**：“其实可以跑 bfs，但我脑抽敲了个 dij。”，说明在选择算法时可能会出现失误。

---
处理用时：54.13秒