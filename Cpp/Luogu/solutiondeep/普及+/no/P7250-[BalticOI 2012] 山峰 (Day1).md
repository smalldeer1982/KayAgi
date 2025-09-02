# 题目信息

# [BalticOI 2012] 山峰 (Day1)

## 题目描述

有一个 $N \times M$ 大小的岛屿，每个点有不同的海拔。定义相邻为两个点横纵坐标差均不超过 $1$。定义路径为任意两个连续点都相邻的序列。定义平坦的区域是一组联通的海拔相同的点的极大集合，山峰是一个不与任何海拔更高的点相邻的平坦区域。

给出这个岛屿上每个点的海拔，你需要求出岛屿上所有的山峰与前往比其高度更高的山峰所需经过的最低点的海拔的最大值。

## 说明/提示

**【样例解释】** 

![](https://cdn.luogu.com.cn/upload/image_hosting/flr0h9rs.png)  
如上图所示，其中圆圈圈出的为山峰，从海拔为15的山峰前往其他山峰的一条路径用深色标出。

**【数据范围】**

- 对于 15% 的数据，满足 $\min (N,M)\leq 2$
- 对于 50% 的数据，满足 $P \leq 500$
- 对于 80% 的数据，满足 $P \leq 5000$
- 对于 100% 的数据，满足 $1 \leq N,M \leq 2000$，$N \times M \leq 10^5$，$1 \leq E_{i,j} \leq 10^6$

**【说明】**

译自 [BalticOI 2012 Day1 T3. Peaks](http://www.boi2012.lv/data/day1/eng/peaks.pdf)

## 样例 #1

### 输入

```
6 6
21 16 9 11 6 7
21 21 10 14 15 9
18 20 8 9 13 14
11 10 9 9 8 13
8 12 12 14 13 8
7 13 12 9 5 1```

### 输出

```
4
21 0
15 11
14 13
13 12```

# AI分析结果

### 算法分类
并查集、广度优先搜索 BFS、图论

### 综合分析与结论
本题的核心在于通过并查集和BFS来处理岛屿的海拔数据，找出所有山峰，并计算从每个山峰到更高山峰所需经过的最低点的海拔最大值。各题解的主要思路相似，均通过BFS预处理连通块，并使用并查集来维护连通块之间的关系。不同题解在实现细节和优化上有所差异，如启发式合并、最大生成树等。

### 所选高分题解

#### 题解1：NaN_HQJ2007_NaN
- **星级**：4星
- **关键亮点**：通过BFS预处理连通块，并按高度排序后使用并查集维护连通块关系，处理山峰的最低点海拔最大值。代码结构清晰，逻辑严谨。
- **核心代码**：
```cpp
void bfs(int sx, int sy) {
    q.push(node2(sx, sy)); ++tot;
    b[tot].id = tot; b[tot].h = a[sx][sy];
    id[sx][sy] = tot;
    int f1 = 1; //该连通块是否为高地 
    while (!q.empty()) {
        node2 u = q.front(); q.pop();
        int f2 = 0; //该点是否在边缘上 
        for (int k = 0; k <= 7; ++k) {
            int tx = u.i + dx[k], ty = u.j + dy[k];
            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            if (a[tx][ty] == a[sx][sy] && !id[tx][ty]) q.push(node2(tx, ty)), id[tx][ty] = tot;
            if (a[tx][ty] != a[u.i][u.j]) f2 = 1;
            if (a[tx][ty] > a[u.i][u.j]) f1 = 0;
        }
        if (f2) b[tot].v.push_back((u.i - 1) * m + u.j); 
    }
    b[tot].type = f1;
}
```

#### 题解2：__Floze3__
- **星级**：4星
- **关键亮点**：通过并查集维护连通块，并按照海拔排序后逐步加入方格，实时更新连通性。使用了启发式合并来优化性能。
- **核心代码**：
```cpp
il void merge(int x, int y, int d) {
    x = find(x), y = find(y); // 连通块的并查集
    if (x == y) return ;
    int nx = find2(has[x]), ny = find2(has[y]); // 山峰编号的并查集
    if (a[peak[nx]] == a[peak[ny]]) {
        fa[x] = y, fa2[nx] = ny;
        return ;
    }
    else if (a[peak[nx]] > a[peak[ny]]) ans[ny] = max(ans[ny], d), fa[y] = x;
    else ans[nx] = max(ans[nx], d), fa[x] = y;
    return ;
}
```

#### 题解3：Day0
- **星级**：4星
- **关键亮点**：通过最大生成树的思想，使用Kruskal算法生成最大生成树，并在合并过程中更新山峰的答案。使用了启发式合并来优化性能。
- **核心代码**：
```cpp
void merge(int a, int b, int c) {
    a = getfa(a), b = getfa(b);  
    if(siz[a] > siz[b]) swap(a, b);
    if(a == b) return ;
    fa[a] = b; siz[b] += siz[a];
    while(!nds[a].empty() && !nds[b].empty() && p[nds[a][nds[a].size() - 1]] < p[nds[b][0]]) ans[nds[a][nds[a].size() - 1]] = c, nds[a].pop_back();
    while(!nds[a].empty() && !nds[b].empty() && p[nds[b][nds[b].size() - 1]] < p[nds[a][0]]) ans[nds[b][nds[b].size() - 1]] = c, nds[b].pop_back();
    rep(i, 0, signed(nds[a].size() - 1)) nds[b].pb(nds[a][i]);
}
```

### 最优关键思路或技巧
1. **BFS预处理连通块**：通过BFS预处理出所有连通块，并记录其高度和类型。
2. **并查集维护连通块关系**：使用并查集来维护连通块之间的关系，并在合并过程中更新山峰的答案。
3. **启发式合并优化**：在合并连通块时，使用启发式合并来优化性能，减少时间复杂度。

### 可拓展之处
类似的问题可以扩展到其他图论问题中，如最大生成树、最小生成树等。可以使用类似的思路来处理连通块之间的关系，并通过启发式合并来优化性能。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

### 个人心得总结
在实现过程中，调试并查集的合并逻辑是关键，特别是在处理山峰高度相同时的合并情况。启发式合并的使用大大优化了性能，减少了不必要的操作。

---
处理用时：29.47秒