# 题目信息

# Spanning Tree with Maximum Degree

## 题目描述

You are given an undirected unweighted connected graph consisting of $ n $ vertices and $ m $ edges. It is guaranteed that there are no self-loops or multiple edges in the given graph.

Your task is to find any spanning tree of this graph such that the maximum degree over all vertices is maximum possible. Recall that the degree of a vertex is the number of edges incident to it.

## 说明/提示

Picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/679cb38fe66138eb41c68a27752c7ba6f50631eb.png)

In this example the number of edges of spanning tree incident to the vertex $ 3 $ is $ 3 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer.

Picture corresponding to the second example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/3901be7d0b3c499456efcd32ad4bf53709c399cf.png)

In this example the number of edges of spanning tree incident to the vertex $ 1 $ is $ 3 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer.

Picture corresponding to the third example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/4fb66d4828c313ca8131754e22e661e238cfd944.png)

In this example the number of edges of spanning tree incident to the vertex $ 2 $ is $ 4 $ . It is the maximum degree over all vertices of the spanning tree. It is easy to see that we cannot obtain a better answer. But because this example is symmetric, we can choose almost the same spanning tree but with vertex $ 5 $ instead of $ 2 $ .

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 5
4 3
1 5
```

### 输出

```
3 5
2 1
3 2
3 4
```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
4 1
1 2
1 3
```

## 样例 #3

### 输入

```
8 9
1 2
2 3
2 5
1 6
3 4
6 5
4 5
2 7
5 8
```

### 输出

```
3 2
2 5
8 5
6 1
2 7
1 2
3 4
```

# AI分析结果

### 题目翻译
# 最大度数的生成树

## 题目描述
给定一个由 $n$ 个顶点和 $m$ 条边组成的无向无权连通图。保证给定的图中没有自环或重边。

你的任务是找到该图的任意一棵生成树，使得所有顶点中的最大度数尽可能大。回想一下，顶点的度数是指与该顶点关联的边的数量。

## 说明/提示
对应第一个样例的图片：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/679cb38fe66138eb41c68a27752c7ba6f50631eb.png)

在这个样例中，生成树中与顶点 $3$ 关联的边的数量是 $3$。这是生成树中所有顶点的最大度数。很容易看出我们无法得到更好的答案。

对应第二个样例的图片：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/3901be7d0b3c499456efcd32ad4bf53709c399cf.png)

在这个样例中，生成树中与顶点 $1$ 关联的边的数量是 $3$。这是生成树中所有顶点的最大度数。很容易看出我们无法得到更好的答案。

对应第三个样例的图片：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F1/4fb66d4828c313ca8131754e22e661e238cfd944.png)

在这个样例中，生成树中与顶点 $2$ 关联的边的数量是 $4$。这是生成树中所有顶点的最大度数。很容易看出我们无法得到更好的答案。但是因为这个样例是对称的，我们可以选择几乎相同的生成树，只是用顶点 $5$ 代替顶点 $2$。

## 样例 #1
### 输入
```
5 5
1 2
2 3
3 5
4 3
1 5
```
### 输出
```
3 5
2 1
3 2
3 4
```

## 样例 #2
### 输入
```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```
### 输出
```
4 1
1 2
1 3
```

## 样例 #3
### 输入
```
8 9
1 2
2 3
2 5
1 6
3 4
6 5
4 5
2 7
5 8
```
### 输出
```
3 2
2 5
8 5
6 1
2 7
1 2
3 4
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先找出图中度数最大的点，然后将与该点相连的边都加入生成树，再通过不同方法（BFS 或并查集）来保证生成树的连通性且无环。
- **思路对比**：lw21144 采用 BFS 搜索，从度数最大的点开始拓展节点；Li_Yichen、OIerZhang、Frozen_Ladybug、nynkqh_yzp 和 ⚡current⚡ 采用并查集的方法，先加入与度数最大点相连的边，再通过并查集判断其他边是否可以加入以保证无环。
- **算法要点**：
    - **BFS 方法**：需要使用队列存储待拓展的节点，通过链式前向星存储图的边信息。
    - **并查集方法**：需要实现并查集的初始化、查找和合并操作，通过判断两个点是否在同一集合来避免形成环。
- **解决难点**：主要难点在于如何保证生成树的最大度数最大且无环。通过先选择度数最大的点的所有边，再用 BFS 或并查集处理剩余边，可以有效解决这个问题。

### 题解列表
- **lw21144（4星）**：
    - **关键亮点**：思路清晰，使用 BFS 搜索，代码中包含快读快写和链式前向星存储图的边信息，时间复杂度为 $O(m)$。
    - **个人心得**：无。
- **Li_Yichen（4星）**：
    - **关键亮点**：思路简单明了，使用并查集实现，代码结构清晰。
    - **个人心得**：无。
- **⚡current⚡（4星）**：
    - **关键亮点**：提供了并查集和 BFS 两种方法，对思路解释详细。
    - **个人心得**：无。

### 重点代码
#### lw21144 的 BFS 方法核心代码
```cpp
// 链式前向星连边
inline void add(int u,int v){ 
    to[++tot]=v,nxt[tot]=head[u],head[u]=tot;
}
// bfs 搜索
while(!q.empty()){ 
    register int u=q.front(); q.pop();
    for(register int i=head[u];i!=-1;i=nxt[i]){
        register int v=to[i]; if(vis[v]) continue;
        print(u,v),vis[v]=1,q.push(v); //继续拓展节点
    }
}
```
核心实现思想：先通过链式前向星存储图的边信息，然后从度数最大的点开始 BFS 搜索，将未访问的节点加入队列并标记为已访问，同时输出边。

#### Li_Yichen 的并查集方法核心代码
```cpp
// 并查集查找
int find(int x){
    if(father[x] == x) return x;
    return father[x] = find(father[x]);
}
// 并查集合并
int merge(int x,int y){
    int u = find(x);
    int v = find(y);
    if(u != v) father[u] = v;
}
// 先加入与度数最大点相连的边
for(int i=1;i<=m;i++){
    if(u[i] == pos || v[i] == pos){
        cout << u[i] << " " << v[i] << endl;
        merge(u[i],v[i]);
    }
}
// 再加入其他不形成环的边
for(int i=1;i<=m;i++){
    if(find(u[i]) != find(v[i])){
        cout << u[i] << " " << v[i] << endl;
        merge(u[i],v[i]);
    }
}
```
核心实现思想：先实现并查集的查找和合并操作，然后先加入与度数最大点相连的边并合并节点，再遍历所有边，若两个端点不在同一集合则加入边并合并节点。

#### ⚡current⚡ 的并查集方法核心代码
```c++
// 并查集查找
int find(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
// 尝试把某条边加入生成树
inline void add_into_tree(int x)
{
    fau = find(u[x]), fav = find(v[x]);
    if(fau == fav) return;
    printf("%d %d\n", u[x], v[x]);
    fa[find(fau)] = fav;
}
// 先加度数最大点的邻边
for(int i = 1; i <= m; ++i) if(u[i] == maxn || v[i] == maxn) add_into_tree(i);
// 再加其他边
for(int i = 1; i <= m; ++i) add_into_tree(i);
```
核心实现思想：实现并查集的查找操作，定义一个函数尝试将边加入生成树，若两个端点不在同一集合则加入边并合并节点，先加入度数最大点的邻边，再加入其他边。

### 关键思路或技巧
- **贪心策略**：先找出度数最大的点，将其所有邻边加入生成树，保证最大度数最大。
- **并查集判环**：使用并查集判断两个点是否在同一集合，避免生成树中出现环。
- **BFS 拓展**：以度数最大的点为起点进行 BFS 搜索，保证生成树的连通性。

### 可拓展之处
同类型题或类似算法套路：
- 其他生成树相关问题，如最小生成树问题（Kruskal 算法、Prim 算法）。
- 图的连通性问题，可使用并查集或 DFS、BFS 来解决。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)

---
处理用时：61.21秒