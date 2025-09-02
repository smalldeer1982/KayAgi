# 题目信息

# Make It Connected

## 题目描述

You are given an undirected graph consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is $ a_i $ . Initially there are no edges in the graph.

You may add some edges to this graph, but you have to pay for them. The cost of adding an edge between vertices $ x $ and $ y $ is $ a_x + a_y $ coins. There are also $ m $ special offers, each of them is denoted by three numbers $ x $ , $ y $ and $ w $ , and means that you can add an edge connecting vertices $ x $ and $ y $ and pay $ w $ coins for it. You don't have to use special offers: if there is a pair of vertices $ x $ and $ y $ that has a special offer associated with it, you still may connect these two vertices paying $ a_x + a_y $ coins for it.

What is the minimum number of coins you have to spend to make the graph connected? Recall that a graph is connected if it's possible to get from any vertex to any other vertex using only the edges belonging to this graph.

## 说明/提示

In the first example it is possible to connect $ 1 $ to $ 2 $ using special offer $ 2 $ , and then $ 1 $ to $ 3 $ without using any offers.

In next two examples the optimal answer may be achieved without using special offers.

## 样例 #1

### 输入

```
3 2
1 3 3
2 3 5
2 1 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 0
1 3 3 7
```

### 输出

```
16
```

## 样例 #3

### 输入

```
5 4
1 2 3 4 5
1 2 8
1 3 10
1 4 7
1 5 15
```

### 输出

```
18
```

# AI分析结果

### 题目内容中文重写
## 使其连通

### 题目描述
给定一个由 $n$ 个顶点组成的无向图。每个顶点上都写有一个数字；顶点 $i$ 上的数字是 $a_i$。初始时，图中没有边。

你可以向这个图中添加一些边，但需要为此付费。在顶点 $x$ 和 $y$ 之间添加一条边的成本是 $a_x + a_y$ 枚硬币。此外，还有 $m$ 个特殊优惠，每个优惠由三个数字 $x$、$y$ 和 $w$ 表示，意味着你可以花费 $w$ 枚硬币添加一条连接顶点 $x$ 和 $y$ 的边。你不必使用这些特殊优惠：如果有一对顶点 $x$ 和 $y$ 有与之关联的特殊优惠，你仍然可以花费 $a_x + a_y$ 枚硬币来连接这两个顶点。

要使图连通，你至少需要花费多少枚硬币？回想一下，如果可以仅使用属于该图的边从任何顶点到达任何其他顶点，则称该图是连通的。

### 说明/提示
在第一个示例中，可以使用特殊优惠 2 连接 1 和 2，然后不使用任何优惠连接 1 和 3。

在接下来的两个示例中，可以不使用特殊优惠来达到最优答案。

### 样例 #1
#### 输入
```
3 2
1 3 3
2 3 5
2 1 1
```
#### 输出
```
5
```

### 样例 #2
#### 输入
```
4 0
1 3 3 7
```
#### 输出
```
16
```

### 样例 #3
#### 输入
```
5 4
1 2 3 4 5
1 2 8
1 3 10
1 4 7
1 5 15
```
#### 输出
```
18
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是将问题转化为最小生成树问题。由于直接 $O(n^2)$ 建图不可行，大家都利用了完全图最小生成树的性质：以权值最小的点为核心，它与其他点相连的边权和最小，所以只需要加入这些边和特殊边，再用 Kruskal 算法求最小生成树即可。

各题解的主要区别在于实现细节，如输入输出优化、数据结构的使用等。部分题解使用堆来维护点权最小的集合，部分题解直接找出最小权值点并建边。

### 所选题解
- **一扶苏一（4星）**
    - **关键亮点**：思路清晰，对克鲁斯卡尔算法的本质进行了详细分析，使用堆来维护点权最小的集合，代码有输入输出优化。
- **starseven（4星）**
    - **关键亮点**：详细分析了无用边，通过推理得出只需要加入 $n - 1$ 条边，降低了时间和空间复杂度，代码结构清晰。
- **ytm2004（4星）**
    - **关键亮点**：核心思想明确，代码简洁易懂，直接实现了以最小权值点为核心建边的思路。

### 重点代码
#### 一扶苏一：
```cpp
// 堆的使用及边的合并
struct Zay {
    int id;
    ll v;
    inline bool operator<(const Zay &_others) const {
        return this->v > _others.v;
    }
};
std::priority_queue<Zay>Q;
// 克鲁斯卡尔算法核心部分
for (rg int i = 1, cur = 1; i < n; ++i) {
    while ((cur <= m) && (find(edge[cur].from) == find(edge[cur].to))) ++cur;
    Zay t1 = Q.top(); Q.pop(); Zay t2 = Q.top(); Q.pop();
    while (find(t1.id) == find(t2.id)) {t2 = Q.top(); Q.pop();}
    if ((t1.v + t2.v) <= edge[cur].v) {
        int fa = find(t1.id), fb = find(t2.id);
        ans += t1.v + t2.v;
        if (rk[fa] < rk[fb]) ufs[fb] = fa;
        else if (rk[fa] > rk[fb]) ufs[fa] = fb;
        else ufs[fa] = fb, ++rk[fb];
        Q.push((Zay){find(fa), t1.v});
        vec[find(fa)] = vec[fa];
    } else {
        int fa = find(edge[cur].from), fb = find(edge[cur].to);
        ans += edge[cur].v;
        if (rk[fa] < rk[fb]) ufs[fb] = fa;
        else if (rk[fa] > rk[fb]) ufs[fa] = fb;
        else ufs[fa] = fb, ++rk[fb];
        Q.push((Zay){find(fa), MU[vec[fa]]});
        vec[find(fa)] = vec[fa];
        Q.push(t1); Q.push(t2);
    }
}
```
核心思想：使用堆维护点权最小的集合，每次比较特殊边和最小点权集合间的边权，选择较小的边进行合并。

#### starseven：
```cpp
// 找出最小权值点并建边
sort(num + 1, num + 1 + n, cmp);
for(ri i = 2; i <= n; i++) Add(num[1].id, num[i].id, num[1].val + num[i].val);
// 加入特殊边
for(ri i = 1; i <= m; i++){
    int x, y; ll va;
    cin >> x >> y >> va;
    Add(x, y, va);
}
// 克鲁斯卡尔算法核心部分
sort(tr + 1, tr + 1 + cnt, cmd);
int judge = 0;
for(ri i = 1; i <= cnt; i++){
    int fx = Find(tr[i].from), fy = Find(tr[i].to);
    if(fx == fy) continue;
    fa[fx] = fy;
    ans += tr[i].cos;
    judge++;
    if(judge == n - 1) break;
}
```
核心思想：先找出最小权值点，将其与其他点相连建边，再加入特殊边，最后对所有边排序，用并查集实现 Kruskal 算法。

#### ytm2004：
```cpp
// 找出最小权值点并建边
minn = 1;
for(ll i = 1; i <= n; i++){
    scanf("%lld", &a[i]);
    if(a[minn] > a[i]) minn = i;
}
for(ll i = 1; i <= n; i++){
    if(minn == i) continue;
    e[i + m].u = minn;
    e[i + m].v = i;
    e[i + m].w = a[i] + a[minn];
}
// 克鲁斯卡尔算法核心部分
sort(e + 1, e + m + n + 1, cmp);
ll tot = 0, cnt = 0;
for(ll i = 2; i <= m + n; i++){
    if(merge(e[i].u, e[i].v)){
        tot += e[i].w;
        cnt++;
        if(cnt == n) break;
    }
}
```
核心思想：找出最小权值点，将其与其他点建边，加入特殊边后排序，用并查集实现 Kruskal 算法，满足条件后提前退出循环。

### 最优关键思路或技巧
- **利用完全图最小生成树性质**：完全图的最小生成树可以由权值最小的点与其他点相连构成，从而避免了 $O(n^2)$ 建图。
- **Kruskal 算法**：将所有边按权值排序，依次选择最小边加入生成树，直到图连通。

### 可拓展之处
同类型题或类似算法套路：
- 带权图的最小生成树问题，如 Prim 算法求最小生成树。
- 图的连通性问题，可使用并查集维护连通分量。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)

### 个人心得摘录与总结
- **starseven**：最开始想到了要和最小点连边，但没有想到最小生成树，而是想一个一个加入 $m$ 条边然后判断是否能替换，说明对图论知识点不够熟悉，需要加强学习。总结：在解决图论问题时，要全面考虑各种算法和性质，不能局限于局部思路。 

---
处理用时：60.18秒