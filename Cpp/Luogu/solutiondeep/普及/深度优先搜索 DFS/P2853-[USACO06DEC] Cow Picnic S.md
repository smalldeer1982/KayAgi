# 题目信息

# [USACO06DEC] Cow Picnic S

## 题目描述

The cows are having a picnic! Each of Farmer John's K (1 ≤ K ≤ 100) cows is grazing in one of N (1 ≤ N ≤ 1,000) pastures, conveniently numbered 1...N. The pastures are connected by M (1 ≤ M ≤ 10,000) one-way paths (no path connects a pasture to itself).

The cows want to gather in the same pasture for their picnic, but (because of the one-way paths) some cows may only be able to get to some pastures. Help the cows out by figuring out how many pastures are reachable by all cows, and hence are possible picnic locations.

$K(1 \le K \le 100)$ 只奶牛分散在 $N(1 \le N \le 1000)$ 个牧场．现在她们要集中起来进餐。牧场之间有 $M(1 \le M \le 10000)$ 条有向路连接，而且不存在起点和终点相同的有向路．她们进餐的地点必须是所有奶牛都可到达的地方。那么，有多少这样的牧场可供进食呢？

## 说明/提示

The cows can meet in pastures 3 or 4.


## 样例 #1

### 输入

```
2 4 4
2
3
1 2
1 4
2 3
3 4```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

本题的核心问题是在有向图中找到所有奶牛都能到达的牧场。题解中主要采用了DFS、BFS、反向建边、最短路等算法。大多数题解的思路是从每个奶牛的位置出发，遍历图并记录每个牧场被访问的次数，最后统计被所有奶牛访问过的牧场数量。部分题解通过反向建边或最短路优化了算法效率。

### 所选高星题解

#### 1. 作者：xueyangkai (赞：133)  
**星级：5星**  
**关键亮点：**  
- 使用DFS从每个奶牛的位置出发，记录每个牧场被访问的次数，最后统计被所有奶牛访问过的牧场数量。  
- 代码简洁，思路清晰，使用了`vector`存储图结构，适合初学者理解。  
- 通过`mk`数组记录每个牧场的访问次数，避免了复杂的反向建边或最短路算法。

**核心代码：**
```cpp
void dfs(int x) {
    vis[x] = 1;  mk[x]++;
    for(int i = 0; i < b[x].size(); i++)
        if(!vis[b[x][i]])
            dfs(b[x][i]);
}
```
**实现思想：**  
从每个奶牛的位置出发进行DFS，记录每个牧场的访问次数，最后统计被所有奶牛访问过的牧场数量。

#### 2. 作者：Lates (赞：14)  
**星级：4星**  
**关键亮点：**  
- 采用反向建边+DFS的思路，从每个牧场出发，判断是否能到达所有奶牛的位置。  
- 通过`vis`数组记录每个牧场的访问情况，避免了复杂的统计逻辑。  
- 代码结构清晰，适合有一定基础的读者。

**核心代码：**
```cpp
void dfs(int now) {
    vis[now] = 1;
    for(register int i = head[now]; i; i = e[i].next) {
        if(!vis[e[i].e]) dfs(e[i].e);
    }
}
```
**实现思想：**  
通过反向建边，从每个牧场出发进行DFS，判断是否能到达所有奶牛的位置，最后统计符合条件的牧场数量。

#### 3. 作者：Khassar (赞：7)  
**星级：4星**  
**关键亮点：**  
- 使用BFS从每个奶牛的位置出发，记录每个牧场的访问次数，最后统计被所有奶牛访问过的牧场数量。  
- 通过`cnt`数组记录每个牧场的访问次数，避免了复杂的反向建边或最短路算法。  
- 代码结构清晰，适合初学者理解。

**核心代码：**
```cpp
void bfs(int x) {
    queue<int> q;
    q.push(x);
    vis[x] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            if(!vis[v]) {
                vis[v] = 1;
                s[v]++;
                q.push(v);
            }
        }
    }
}
```
**实现思想：**  
从每个奶牛的位置出发进行BFS，记录每个牧场的访问次数，最后统计被所有奶牛访问过的牧场数量。

### 最优关键思路与技巧

1. **DFS/BFS遍历**：从每个奶牛的位置出发，遍历图并记录每个牧场的访问次数，最后统计被所有奶牛访问过的牧场数量。  
2. **反向建边**：通过反向建边，从每个牧场出发，判断是否能到达所有奶牛的位置，简化了问题的复杂度。  
3. **统计访问次数**：通过数组记录每个牧场的访问次数，避免了复杂的反向建边或最短路算法。

### 可拓展之处

1. **类似问题**：可以考虑在无向图中找到所有节点都能到达的节点，或者在有向图中找到所有节点都能到达的节点。  
2. **算法优化**：可以考虑使用Tarjan缩点、Dijkstra、SPFA等算法进一步优化时间复杂度。

### 推荐题目

1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)  
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)  
3. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)

### 个人心得总结

- **调试经历**：部分题解提到在调试过程中忘记清空`vis`数组，导致WA，提醒我们在写图论算法时要注意初始化。  
- **顿悟感想**：通过反向建边，问题变得简单，提醒我们在面对复杂问题时，可以尝试转换思路，简化问题。

---
处理用时：24.04秒