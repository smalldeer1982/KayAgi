# 题目信息

# [USACO2.4] 牛的旅行 Cow Tours

## 题目描述

Farmer John 的农场里有很多 **牧区**。有的路径连接一些特定的牧区。**一片所有连通的牧区** 称为一个 **牧场**。但是就目前而言，你能看到至少有两个牧区通过任何路径都不连通。这样，Farmer John 就有 **多个** 牧场了。

John 想在牧场里添加 **恰好** 一条路径。对这条路径有以下限制：

一个牧场的 **直径** 就是牧场中 **最远** 的两个牧区的距离（本题中所提到的所有距离指的都是 **最短的距离**）。考虑如下的有 5 个牧区的牧场，牧区用 `*` 表示，路径用直线表示。每一个牧区都有自己的坐标：

```plain
                (15,15) (20,15)
                 D       E
                 *-------*
                 |     _/|
                 |   _/  |
                 | _/    |
                 |/      |
        *--------*-------*
        A        B       C
     (10,10)  (15,10) (20,10)
```
这个牧场的直径大约是 $12.07106$，最远的两个牧区是 A 和 E，它们之间的最短路径是 $A \to B \to E$。

这里是 John 的另一个牧场：

```plain
                         *F(30,15)
                        / 
                      _/  
                    _/    
                   /      
                  *------* 
                  G      H
                  (25,10)   (30,10)
```

在这个例子中，他刚好有这两个牧场。John 将会在这两个牧场中各选一个牧区（即从 $\{A,B,C,D,E\}$ 中选择一个牧区，从 $\{F,G,H\}$ 中选择一个牧区），然后用一条路径将它们连起来，使得连通后这个新的更大的牧场的直径尽可能小。

注意，如果两条路径中途相交，我们不认为它们是连通的。只有两条路径在同一个牧区相交，我们才认为它们是连通的。

输入文件包括牧区、它们各自的坐标，还有一个如下的对称邻接矩阵：

```plain
　 A  B  C  D  E  F  G  H 
A  0  1  0  0  0  0  0  0
B  1  0  1  1  1  0  0  0
C  0  1  0  0  1  0  0  0
D  0  1  0  0  1  0  0  0
E  0  1  1  1  0  0  0  0
F  0  0  0  0  0  0  1  0
G  0  0  0  0  0  1  0  1
H  0  0  0  0  0  0  1  0
```

其他邻接表中可能直接使用行列而不使用字母来表示每一个牧区。输入数据中不包括牧区的名字。

输入文件 **至少** 包括两个不连通的牧区。

请编程找出一条连接属于两个 **不同牧场** 的牧区的路径，使得连上这条路径后，这个更大的新牧场的直径尽可能小。输出在所有合法的连接方案中，新牧场直径的最小值。

## 说明/提示

样例对应题目描述中的情况。

最优解是连接 C 牧区和 G 牧区，连接后图上只有一个牧场。这个牧场的直径为 $A \to B \to C \to G \to F$，长度约为 $22.071068$。可以证明不存在更优的方案。

USACO 2.4


## 样例 #1

### 输入

```
8
10 10
15 10
20 10
15 15
20 15
30 15
25 10
30 10
01000000
10111000
01001000
01001000
01110000
00000010
00000101
00000010```

### 输出

```
22.071068
```

# AI分析结果

### 综合分析与结论
这些题解核心思路一致，都是先找出所有牧场（连通块），计算任意两点间最短路，再算出每个牧场直径，最后枚举不同牧场的点对，添加边后取新牧场直径最小值。主要差异在于连通块标记方法（DFS 或并查集）和最短路计算算法（Floyd 或 Dijkstra）。

### 所选题解
- **作者：heidoudou（5 星）**
    - **关键亮点**：思路清晰，详细解释每个步骤，代码注释丰富，可读性强。
    - **个人心得**：无
- **作者：StudyingFather（4 星）**
    - **关键亮点**：明确指出部分错误做法，对新连通块直径构成情况分析清晰。
    - **个人心得**：指出不少做法只考虑一种情况，原数据较弱可通过，强调考虑情况的完整性。
- **作者：tribool4_in（4 星）**
    - **关键亮点**：图文结合分析新连通块直径的三种情况，代码模块化，使用并查集封装良好。
    - **个人心得**：提到旧做法只考虑一种情况无法通过测试点，强调新连通块直径需综合考虑多种情况。

### 重点代码及核心思想
#### 作者：heidoudou
```cpp
// DFS 标记连通块
void dfs(int i, int id)
{
    field[i] = id;
    for (int j = 0; j < n; ++j)
        if (!field[j] && dist[i][j] < INF)
            dfs(j, id);
}

// Floyd-Warshall 算法计算最短路
for (k = 0; k < n; ++k)
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (dist[i][k] + dist[k][j] < dist[i][j])
                dist[i][j] = dist[i][k] + dist[k][j];

// 计算每个牧场直径
for (i = 0; i < n; ++i)
{
    max_sp[i] = 0.0;
    for (j = 0; j < n; ++j)
        if (dist[i][j] < INF)
            max_sp[i] = max(max_sp[i], dist[i][j]);
    diameter[field[i]] = max(diameter[field[i]], max_sp[i]);
}

// 枚举点对找答案
for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j)
        if (field[i]!= field[j])
        {
            max_d = max(max(diameter[field[i]], diameter[field[j]]),
                        max_sp[i] + a[i].distance(a[j]) + max_sp[j]);
            min_d = min(min_d, max_d);
        }
```
核心思想：先 DFS 标记连通块，再用 Floyd 算最短路，接着计算每个牧场直径，最后枚举不同牧场点对求新牧场最小直径。

#### 作者：StudyingFather
```cpp
// 并查集初始化
struct dsu {
  int fa[155], n;
  void init(int n) {
    this->n = n;
    for (int i = 1; i <= n; i++) fa[i] = i;
  }
  int find(int x) { return fa[x] == x? x : fa[x] = find(fa[x]); }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    fa[y] = x;
  }
  bool together(int x, int y) { return find(x) == find(y); }
} ds;

// Floyd 算法计算最短路
for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

// 计算每个牧场直径
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
        if (ds.together(i, j))
            maxd[i] = max(maxd[i], d[i][j]);
    ad[ds.find(i)] = max(ad[ds.find(i)], maxd[i]);
}

// 枚举点对找答案
for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
        if (!ds.together(i, j))
            ans = min(ans,
                      max(maxd[i] + maxd[j] + dist(p[i].x, p[i].y, p[j].x, p[j].y),
                          max(ad[ds.find(i)], ad[ds.find(j)])));
```
核心思想：用并查集维护连通块，Floyd 算最短路，计算每个牧场直径，枚举不同连通块点对求新牧场最小直径。

#### 作者：tribool4_in
```cpp
// 并查集类
class dsu {
    private:
        int n;
        int *fa;
        void init(int n) {
            fa = new int[n + 10];
            for (int i = 0; i <= n; i++) fa[i] = i;
        }
    public:
        dsu(int n):n(n) { init(n); }
        int find(int x) {
            if (fa[x] == x) return x;
            return fa[x] = find(fa[x]);
        }
        bool together(int x, int y) { return find(x) == find(y); }
        void merge(int x, int y) {
            x = find(x), y = find(y);
            if (x!= y) fa[x] = y;
        }
};

// Floyd 算法计算最短路
for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
        }
    }
}

// 计算每个牧场直径
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (ds.together(i, j)) {
            d[i] = max(d[i], f[i][j]);
        }
    }
    dd[ds.find(i)] = max(dd[ds.find(i)], d[i]);
}

// 枚举点对找答案
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (!ds.together(i, j)) {
            d2 = min(d2,
                    max(d[i] + d[j] + dis(i, j),
                    max(dd[ds.find(i)], dd[ds.find(j)])));
        }
    }
}
```
核心思想：使用并查集类维护连通块，Floyd 算最短路，计算每个牧场直径，枚举不同连通块点对求新牧场最小直径。

### 最优关键思路或技巧
- **连通块标记**：可使用 DFS 或并查集标记不同牧场（连通块）。
- **最短路计算**：数据规模小（$n\leq150$）时，用 Floyd 算法计算任意两点间最短路，代码简洁。
- **新牧场直径计算**：新牧场直径需考虑原两个牧场直径和添加边后的新路径，取三者最大值。

### 拓展思路
同类型题或类似算法套路：
- 图的连通性问题，如求连通分量个数、判断两点是否连通，可用 DFS、BFS 或并查集。
- 最短路问题，根据数据规模选合适算法，如 Floyd、Dijkstra、Bellman-Ford 等。
- 图的合并问题，合并多个连通块使新图满足特定条件，枚举合并方案并评估。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及 Floyd 算法在动态图中的应用。
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：考察 Dijkstra 算法。
- [P1396 营救](https://www.luogu.com.cn/problem/P1396)：涉及图的连通性和最短路问题。

### 个人心得总结
部分题解指出旧做法只考虑新连通块直径的一种情况，无法通过部分测试点，强调新连通块直径需综合考虑原两个牧场直径和添加边后的新路径，做题时要全面分析情况。 

---
处理用时：48.26秒