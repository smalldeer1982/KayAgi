# 题目信息

# Edgy Trees

## 题目描述

You are given a tree (a connected undirected graph without cycles) of $ n $ vertices. Each of the $ n - 1 $ edges of the tree is colored in either black or red.

You are also given an integer $ k $ . Consider sequences of $ k $ vertices. Let's call a sequence $ [a_1, a_2, \ldots, a_k] $ good if it satisfies the following criterion:

- We will walk a path (possibly visiting same edge/vertex multiple times) on the tree, starting from $ a_1 $ and ending at $ a_k $ .
- Start at $ a_1 $ , then go to $ a_2 $ using the shortest path between $ a_1 $ and $ a_2 $ , then go to $ a_3 $ in a similar way, and so on, until you travel the shortest path between $ a_{k-1} $ and $ a_k $ .
- If you walked over at least one black edge during this process, then the sequence is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1139C/fceedad9154dba8252692b9078d5d0099b72c637.png)Consider the tree on the picture. If $ k=3 $ then the following sequences are good: $ [1, 4, 7] $ , $ [5, 5, 3] $ and $ [2, 3, 7] $ . The following sequences are not good: $ [1, 4, 6] $ , $ [5, 5, 5] $ , $ [3, 7, 3] $ .

There are $ n^k $ sequences of vertices, count how many of them are good. Since this number can be quite large, print it modulo $ 10^9+7 $ .

## 说明/提示

In the first example, all sequences ( $ 4^4 $ ) of length $ 4 $ except the following are good:

- $ [1, 1, 1, 1] $
- $ [2, 2, 2, 2] $
- $ [3, 3, 3, 3] $
- $ [4, 4, 4, 4] $

In the second example, all edges are red, hence there aren't any good sequences.

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 1
3 4 1
```

### 输出

```
252```

## 样例 #2

### 输入

```
4 6
1 2 0
1 3 0
1 4 0
```

### 输出

```
0```

## 样例 #3

### 输入

```
3 5
1 2 1
2 3 0
```

### 输出

```
210```

# AI分析结果

### 题目翻译
## 带边树

### 题目描述
给定一棵具有 $n$ 个顶点的树（一个无环的连通无向图）。树的 $n - 1$ 条边中的每一条都被染成黑色或红色。

同时给定一个整数 $k$。考虑长度为 $k$ 的顶点序列。如果一个序列 $ [a_1, a_2, \ldots, a_k] $ 满足以下条件，则称其为好序列：
- 我们将在树上走一条路径（可能多次访问同一条边或同一个顶点），从 $ a_1 $ 开始，到 $ a_k $ 结束。
- 从 $ a_1 $ 出发，然后使用 $ a_1 $ 和 $ a_2 $ 之间的最短路径到达 $ a_2 $，接着以类似的方式到达 $ a_3 $，依此类推，直到走过 $ a_{k - 1} $ 和 $ a_k $ 之间的最短路径。
- 如果在这个过程中至少走过一条黑色边，那么这个序列就是好序列。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1139C/fceedad9154dba8252692b9078d5d0099b72c637.png)
考虑图中的树。如果 $ k = 3 $，那么以下序列是好序列：$ [1, 4, 7] $、$ [5, 5, 3] $ 和 $ [2, 3, 7] $。以下序列不是好序列：$ [1, 4, 6] $、$ [5, 5, 5] $、$ [3, 7, 3] $。

总共有 $ n^k $ 个顶点序列，计算其中好序列的数量。由于这个数字可能非常大，请将结果对 $ 10^9 + 7 $ 取模后输出。

### 说明/提示
在第一个样例中，除以下序列外，所有长度为 $ 4 $ 的序列（$ 4^4 $ 个）都是好序列：
- $ [1, 1, 1, 1] $
- $ [2, 2, 2, 2] $
- $ [3, 3, 3, 3] $
- $ [4, 4, 4, 4] $

在第二个样例中，所有边都是红色的，因此没有好序列。

### 样例 #1
#### 输入
```
4 4
1 2 1
2 3 1
3 4 1
```
#### 输出
```
252
```

### 样例 #2
#### 输入
```
4 6
1 2 0
1 3 0
1 4 0
```
#### 输出
```
0
```

### 样例 #3
#### 输入
```
3 5
1 2 1
2 3 0
```
#### 输出
```
210
```

### 算法分类
并查集

### 综合分析与结论
这些题解的核心思路都是正难则反，通过计算所有可能的序列数 $n^k$ 减去不包含黑边的序列数，得到至少包含一条黑边的好序列数。不包含黑边的序列意味着这些顶点都在由红边构成的连通块内，对于每个红边连通块，其内部的 $k$ 个顶点的序列都不包含黑边，数量为该连通块顶点数的 $k$ 次方。

各题解的主要区别在于计算红边连通块的方法，有的使用并查集，有的使用深度优先搜索（DFS）。并查集通过合并操作将红边连接的顶点合并到同一个集合中，最后统计每个集合的顶点数；DFS 则是从一个未访问的顶点开始，遍历所有与之相连的红边顶点，统计连通块的顶点数。

### 所选题解
- **作者：CXY07 (赞：10)，4星**
  - 关键亮点：思路清晰，详细阐述了思考过程，代码注释丰富，可读性高。
  - 个人心得：作者分享了比赛时的思路，提到看到数据范围后意识到不能暴力求解，从而考虑反向思考，具有一定的参考价值。
- **作者：xht (赞：4)，4星**
  - 关键亮点：简洁明了地概括了思路，指出求连通块用 DFS 或并查集都可以，代码实现简洁。
- **作者：Silence_water (赞：3)，4星**
  - 关键亮点：分析清晰，代码注释详细，对每个步骤的解释较为清楚。

### 重点代码
#### CXY07 的并查集实现
```cpp
//简单并查集，没啥解释的
ll find(ll x) {
    if(x == f[x]) return x;
    return f[x] = find(f[x]);
} 
//并查集合并操作
void unity(int x,int y) {
    if(find(x) != find(y))
        f[find(x)] = find(y);
} 
// 快速幂
ll qpow(ll a,ll b) {
    ll res = 1,base = a;
    while(b) {
        if(b & 1) (res *= base) %= mod;
        (base *= base) %= mod;
        b >>= 1;
    }
    return res;
} 
```
核心思想：使用并查集合并红边连接的顶点，统计每个连通块的顶点数，再用快速幂计算每个连通块内的序列数，最后用总序列数减去这些序列数得到好序列数。

#### xht 的 DFS 实现
```cpp
//快速幂
inline int ksm(int a, int b) {
    int c = 1;
    while (b) {
        if (b & 1) c = (ll)c * a % P;
        a = (ll)a * a % P;
        b >>= 1;
    }
    return c;
}

void dfs(int x) {
    v[x] = 1;
    ++cnt;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        dfs(y);
    }
}
```
核心思想：使用 DFS 遍历红边构成的连通块，统计每个连通块的顶点数，用快速幂计算每个连通块内的序列数，最后用总序列数减去这些序列数得到好序列数。

#### Silence_water 的 DFS 实现
```cpp
void dfs(int u)
{
    mark[u]=true;
    sum[cnt]++;
    for(int i=0;i<e[u].size();i++)
        if(!mark[e[u][i]])dfs(e[u][i]);
}
```
核心思想：通过 DFS 统计每个红边连通块的顶点数，用循环计算总序列数和每个连通块内的序列数，最后用总序列数减去这些序列数得到好序列数。

### 关键思路或技巧
- **反向思维**：直接计算好序列数比较困难，通过计算坏序列数（不包含黑边的序列数），用总序列数减去坏序列数得到好序列数。
- **并查集**：可以高效地合并红边连接的顶点，统计连通块的顶点数。
- **DFS**：可以遍历红边构成的连通块，统计连通块的顶点数。
- **快速幂**：用于计算 $n^k$ 和每个连通块顶点数的 $k$ 次方，提高计算效率。

### 拓展思路
同类型题目通常涉及图的连通性问题，可能会有不同的约束条件，例如边的权重、顶点的属性等。类似的算法套路包括使用并查集或 DFS 计算连通块的信息，通过反向思维简化问题的求解。

### 推荐题目
- [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：并查集的经典应用，涉及集合的合并和元素之间的距离计算。
- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)：并查集的拓展应用，通过并查集维护元素之间的对立关系。
- [P2024 食物链](https://www.luogu.com.cn/problem/P2024)：并查集的高级应用，需要维护元素之间的多种关系。

---
处理用时：58.41秒