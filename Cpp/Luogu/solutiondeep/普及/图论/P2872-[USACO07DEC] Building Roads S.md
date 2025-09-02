# 题目信息

# [USACO07DEC] Building Roads S

## 题目描述

Farmer John had just acquired several new farms! He wants to connect the farms with roads so that he can travel from any farm to any other farm via a sequence of roads; roads already connect some of the farms.

Each of the N (1 ≤ N ≤ 1,000) farms (conveniently numbered 1..N) is represented by a position (Xi, Yi) on the plane (0 ≤ Xi ≤ 1,000,000; 0 ≤ Yi ≤ 1,000,000). Given the preexisting M roads (1 ≤ M ≤ 1,000) as pairs of connected farms, help Farmer John determine the smallest length of additional roads he must build to connect all his farms.

给定 $n$ 个点的坐标，第 $i$ 个点的坐标为 $(x_i,y_i)$，这 $n$ 个点编号为 $1$ 到 $n$。给定 $m$ 条边，第 $i$ 条边连接第 $u_i$ 个点和第 $v_i$ 个点。现在要求你添加一些边，并且能使得任意一点都可以连通其他所有点。求添加的边的总长度的最小值。


## 说明/提示

### 数据规模与约定

对于 $100\%$ 的整数，$1 \le n,m \le 1000$，$1 \le x_i,y_i \le 10^6$，$1 \le u_i,v_i \le n$。

### 说明

Translated by 一只书虫仔。

## 样例 #1

### 输入

```
4 1
1 1
3 1
2 3
4 3
1 4```

### 输出

```
4.00```

# AI分析结果

### 综合分析与结论
本题是最小生成树的经典应用，要求在给定部分已连接边的情况下，计算使所有点连通所需添加边的最小总长度。题解主要采用了Kruskal和Prim两种最小生成树算法，通过预处理已有的边（将其权值设为0），再进行最小生成树的构建。

Kruskal算法通过将所有边按权值排序，利用并查集判断边的两个端点是否属于不同集合，若不同则合并集合并累加边权；Prim算法则从一个点开始，不断选择与当前最小生成树连接的权值最小的边，更新距离数组。

各题解的主要难点在于处理距离计算的精度问题，以及合理处理已有的边。

### 所选题解
- **作者：lzpclxf（5星）**
    - **关键亮点**：思路清晰，详细分析了题目中的问题及解决办法，代码注释丰富，对距离计算的精度问题有详细说明。
    - **个人心得**：交了7遍都不过原因竟是double的问题，一定要控制精度，否则#2 #8 #9 #10会挂掉。
- **作者：Hexarhy（4星）**
    - **关键亮点**：提供了Prim + 堆优化和Kruskal + 路径压缩两种思路，并对两种算法的时间和空间复杂度进行了比较，给出了详细的易错点提示。
    - **个人心得**：这是一道比较模板的最小生成树，调试了很久，注意两点距离公式平方时要强转`double`，建立堆时要注意变量标识顺序，初始化$\infty$时别忘了是`double`类型。
- **作者：没有输入（4星）**
    - **关键亮点**：对最小生成树的概念和Kruskal算法的基本思路进行了详细解释，代码结构清晰，步骤注释明确。

### 重点代码
#### lzpclxf的Kruskal算法核心代码
```cpp
// 计算两点间距离
double jl(int x, int y) {
    return (double)(sqrt((double)(E[x].x - E[y].x) * (E[x].x - E[y].x) + (double)(E[x].y - E[y].y) * (E[x].y - E[y].y)));
}
// 并查集查找
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
// 主函数
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) 
        E[i].x = read(), E[i].y = read();
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            double z = jl(i, j);
            add(i, j, z);
        }
    }
    for(int i = 1; i <= m; i++) {
        int x = read(), y = read();
        add(x, y, 0.0);
    }
    sort(e + 1, e + 1 + cnt, cmp);
    for(int i = 1; i <= cnt; i++) {
        int fx = find(e[i].from), fy = find(e[i].to);
        if(fx != fy) {
            fa[fx] = fy;
            sum++;
            ans += e[i].w;
        }
        if(sum == n - 1) break;
    }
    printf("%.2lf\n", ans);
    return 0;
}
```
**核心实现思想**：先读取点的坐标，计算所有点对之间的距离并存储边信息，将已有的边权值设为0，然后对边按权值排序，使用并查集判断边的两个端点是否属于不同集合，若不同则合并集合并累加边权，直到边数达到$n - 1$。

#### Hexarhy的Prim + 堆优化核心代码
```cpp
// 计算两点间距离
double dis(int xa,int ya,int xb,int yb) {
    return sqrt((double)(xa-xb)*(xa-xb)+(double)(ya-yb)*(ya-yb));
}
// Prim算法
void prim(void) {
    for(int i = 1; i <= n; i++)
        dis[i] = INF;
    typedef pair<double,int> pdi;
    priority_queue <pdi,vector<pdi>,greater<pdi> > q;
    q.push(pdi(0, 1));
    dis[1] = 0;
    int stop = 0;
    while(!q.empty() && stop < n) {
        const double distance = q.top().first;
        const int u = q.top().second;
        q.pop();
        if(visit[u])
            continue;
        visit[u] = true;
        ans += distance;
        stop++;
        for(int v = 1; v <= n; v++)
            if(edge[u][v] != -1.0 && dis[v] > edge[u][v]) {
                dis[v] = edge[u][v];
                q.push(pdi(dis[v], v));
            }
    }
}
```
**核心实现思想**：初始化距离数组为无穷大，将起点加入优先队列，不断从优先队列中取出距离最小的点，标记该点已访问，更新与该点相连的点的距离，并将更新后的点加入优先队列，直到所有点都被访问。

#### 没有输入的Kruskal算法核心代码
```cpp
// 并查集查找
int Find(int x) {
    if(x == pre[x]) return x;
    return pre[x] = Find(pre[x]);
}
// 主函数
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]), pre[i] = i;
    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <= n; j++) e[++l].u = i, e[l].v = j, e[l].w = (double)sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) + (double)(y[i] - y[j]) * (y[i] - y[j]));
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[++l].u = u, e[l].v = v, e[l].w = 0.0;
    }
    sort(e + 1, e + l + 1, cmp);
    for(int i = 1; i <= l; i++) {
        if(sum == n - 1) break;
        int a = Find(e[i].u), b = Find(e[i].v);
        if(a == b) continue;
        sum++, ans += e[i].w;
        pre[a] = Find(pre[b]);
    }
    printf("%.2lf", ans);
    return 0;
}
```
**核心实现思想**：读取点的坐标，计算所有点对之间的距离并存储边信息，将已有的边权值设为0，对边按权值排序，使用并查集判断边的两个端点是否属于不同集合，若不同则合并集合并累加边权，直到边数达到$n - 1$。

### 最优关键思路或技巧
- **距离计算精度**：在计算两点间距离时，要将坐标差值强制转换为`double`类型，避免精度丢失。
- **已有的边处理**：将已有的边权值设为0，这样在最小生成树算法中会优先选择这些边。
- **算法选择**：稀疏图中Kruskal算法更优，稠密图中Prim算法更优，可根据图的特点选择合适的算法。

### 可拓展之处
同类型题或类似算法套路：
- 最小生成树的变种问题，如最大生成树、次小生成树等。
- 带权图的连通性问题，可使用并查集或最小生成树算法解决。
- 图的遍历问题，如深度优先搜索（DFS）、广度优先搜索（BFS）等。

### 推荐题目
- P1195 口袋的天空
- P2330 [SCOI2005]繁忙的都市
- P3366 【模板】最小生成树

### 个人心得总结
- 很多题解都提到了距离计算的精度问题，在计算两点间距离时，要将坐标差值强制转换为`double`类型，否则可能会导致部分测试点错误。
- 数组大小要足够大，否则可能会出现运行时错误（RE）。
- 在使用堆优化时，要注意变量标识的顺序，避免出现错误。

---
处理用时：52.51秒