# 题目信息

# Hydra

## 题目描述

One day Petya got a birthday present from his mom: a book called "The Legends and Myths of Graph Theory". From this book Petya learned about a hydra graph.

A non-oriented graph is a hydra, if it has a structure, shown on the figure below. Namely, there are two nodes $ u $ and $ v $ connected by an edge, they are the hydra's chest and stomach, correspondingly. The chest is connected with $ h $ nodes, which are the hydra's heads. The stomach is connected with $ t $ nodes, which are the hydra's tails. Note that the hydra is a tree, consisting of $ h+t+2 $ nodes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/d6e514f088f194e43f02ecd959e99753f276fecc.png)Also, Petya's got a non-directed graph $ G $ , consisting of $ n $ nodes and $ m $ edges. Petya got this graph as a last year birthday present from his mom. Graph $ G $ contains no self-loops or multiple edges.

Now Petya wants to find a hydra in graph $ G $ . Or else, to make sure that the graph doesn't have a hydra.

## 说明/提示

The first sample is depicted on the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/b7fc0e169a7806a7f3ca6b4c9c4c40eca2a230e7.png)

## 样例 #1

### 输入

```
9 12 2 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
8 7
9 1
```

### 输出

```
YES
4 1
5 6 
9 3 2 
```

## 样例 #2

### 输入

```
7 10 3 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Hydra

## 题目描述
一天，Petya 从妈妈那里得到了一份生日礼物：一本名为《图论的传说与神话》的书。从这本书中，Petya 了解到了九头蛇图。

一个无向图如果具有如下图所示的结构，那么它就是一个九头蛇图。具体来说，存在两个节点 $u$ 和 $v$ 通过一条边相连，它们分别是九头蛇的胸部和腹部。胸部与 $h$ 个节点相连，这些节点是九头蛇的头。腹部与 $t$ 个节点相连，这些节点是九头蛇的尾巴。注意，九头蛇图是一棵树，由 $h + t + 2$ 个节点组成。

![九头蛇图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/d6e514f088f194e43f02ecd959e99753f276fecc.png)

此外，Petya 还得到了一个无向图 $G$，由 $n$ 个节点和 $m$ 条边组成。Petya 是在去年生日时从妈妈那里得到这个图的。图 $G$ 不包含自环或重边。

现在，Petya 想在图 $G$ 中找到一个九头蛇图。或者，确定该图中不存在九头蛇图。

## 说明/提示
第一个样例如下图所示：

![第一个样例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/b7fc0e169a7806a7f3ca6b4c9c4c40eca2a230e7.png)

## 样例 #1
### 输入
```
9 12 2 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
8 7
9 1
```
### 输出
```
YES
4 1
5 6 
9 3 2 
```

## 样例 #2
### 输入
```
7 10 3 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
```
### 输出
```
NO
```

### 算法分类
枚举 + 贪心

### 题解综合分析与结论
这些题解的核心思路都是通过枚举图中的边，判断每条边连接的两个节点能否分别作为九头蛇的胸部和腹部，进而找到符合条件的九头蛇图结构。

算法要点在于：
1. 先统计每个点的度数，对于枚举的边 $(u, v)$，若 $u$ 的度数小于 $h$ 或者 $v$ 的度数小于 $t$，则直接跳过，因为这种情况下不可能构成九头蛇图。
2. 对于满足度数条件的边，通过贪心策略选取头和尾的节点。比如先优先选取仅与胸部或腹部其中一个点相连的节点，不够时再选取与两者都相连的节点。

解决难点在于如何高效地判断和选取满足条件的节点，同时避免重复计算。各题解在实现细节上有所不同，如节点信息的存储方式、贪心选取的具体实现等。

### 所选的题解
- **作者：XL4453 (赞：1)  星级：4星**
    - **关键亮点**：思路清晰，详细阐述了贪心策略和复杂度分析。代码实现中，通过数组和链表结构存储图，在枚举边时，利用数组标记节点状态，按贪心策略选取头和尾节点，实现较为简洁明了。
    - **重点代码**：
```cpp
// 存储图的相关数组初始化
const int MAXN = 200005;
int n, m, h, t, head[MAXN], nxt[MAXN], num[MAXN], tot, st[MAXN], x[MAXN], y[MAXN];
int ans1[MAXN], ans2[MAXN], u, v, cnt1, cnt2, tt[MAXN];
void add(int x, int y) {
    nxt[++tot] = head[x];
    head[x] = tot;
    num[tot] = y;
}
// 主函数中枚举边并判断
for (int l = 1; l <= m; l++) {
    if (tt[x[l]] < h || tt[y[l]] < t) continue;
    cnt1 = cnt2 = 0;
    for (int i = head[x[l]]; i; i = nxt[i]) if (num[i]!= y[l]) st[num[i]]++;
    for (int i = head[y[l]]; i; i = nxt[i]) if (num[i]!= x[l]) st[num[i]]++;
    cnt1 = cnt2 = 0;

    for (int i = head[x[l]]; i; i = nxt[i]) {
        if (st[num[i]] == 1) ans1[++cnt1] = num[i];
        if (cnt1 >= h) break;
    }
    for (int i = head[x[l]]; i; i = nxt[i]) {
        if (st[num[i]] == 2 && cnt1 < h) ans1[++cnt1] = num[i], st[num[i]] = 3;
        if (cnt1 >= h) break;
    }

    for (int i = head[y[l]]; i; i = nxt[i]) {
        if (st[num[i]] == 1) ans2[++cnt2] = num[i];
        if (cnt2 >= t) break;
    }
    for (int i = head[y[l]]; i; i = nxt[i]) {
        if (st[num[i]] == 2 && cnt2 < t) ans2[++cnt2] = num[i], st[num[i]] = 3;
        if (cnt2 >= t) break;
    }

    if (cnt1 >= h && cnt2 >= t) {
        printf("YES\n");
        printf("%d %d\n", x[l], y[l]);
        for (int i = 1; i <= h; i++) printf("%d ", ans1[i]);
        printf("\n");
        for (int i = 1; i <= t; i++) printf("%d ", ans2[i]);
        printf("\n");
        return 0;
    }

    for (int i = head[x[l]]; i; i = nxt[i]) st[num[i]] = 0;
    for (int i = head[y[l]]; i; i = nxt[i]) st[num[i]] = 0;
}
```
    - **核心实现思想**：通过 `add` 函数构建图的邻接表。在主循环中枚举边，先判断两个端点度数是否满足基本条件，然后标记与端点相连节点的状态，按贪心策略选取头和尾节点，若满足要求则输出结果并结束程序，否则清空标记继续下一轮枚举。
- **作者：Jerrywang09 (赞：0)  星级：4星**
    - **关键亮点**：代码简洁，逻辑清晰。利用 `vector` 存储图结构，在枚举边时，通过数组标记节点与胸部和腹部节点的连接状态，按贪心策略选取头和尾节点，整体实现简洁高效。
    - **重点代码**：
```cpp
// 主函数中枚举边并判断
rep(u, 1, n) for (int v : g[u]) {
    if (g[u].size() <= h || g[v].size() <= t) continue;
    for (int x : g[u]) if (x!= v)
        st[x] = 1;
    k = 0;
    for (int x : g[v]) if (x!= u) {
        st[x] += 2;
        if (st[x] == 3) rest[++k] = x;
    }
    vector<int> head, tail;
    for (int x : g[u]) if (x!= v && st[x] == 1) {
        head.push_back(x);
        if (head.size() >= h) break;
    }
    for (int x : g[v]) if (x!= u && st[x] == 2) {
        tail.push_back(x);
        if (tail.size() >= t) break;
    }
    while (head.size() < h && k)
        head.push_back(rest[k--]);
    while (tail.size() < t && k)
        tail.push_back(rest[k--]);
    if (head.size() >= h && tail.size() >= t) {
        puts("YES");
        printf("%d %d\n", u, v);
        for (int x : head) printf("%d ", x);
        puts("");
        for (int x : tail) printf("%d ", x);
        return 0;
    }
    for (int x : g[u]) st[x] = 0;
    for (int x : g[v]) st[x] = 0;
}
```
    - **核心实现思想**：在双重循环枚举边时，先对胸部节点相连的非腹部节点标记为 `1`，再对腹部节点相连的非胸部节点标记，若节点标记变为 `3` 则存入 `rest` 数组。然后按贪心策略从标记为 `1` 和 `2` 的节点中选取头和尾节点，不足时从 `rest` 中选取，若满足条件则输出并结束，否则清空标记继续枚举。
- **作者：Ryo_Yamada (赞：0)  星级：4星**
    - **关键亮点**：对复杂度分析清晰，考虑到 $h$ 和 $t$ 较小的特点，在枚举边时针对不同度数情况进行分类讨论，优化了判断过程，提高了效率。
    - **重点代码**：
```cpp
// 主函数中枚举边并判断
rep(u, 1, n) {
    if (e[u].size() <= h) continue;
    for (int v : e[u]) {
        if (e[v].size() <= t) continue;
        if (e[u].size() >= h + t + 1) {
            puts("YES");
            cout << u << ' ' << v << endl;
            vis[v] = 1;
            int siz = t - 1;
            rep(j, 0, siz) if (e[v][j] == u) ++siz; else vis[e[v][j]] = 1;
            int cnt = 0;
            for (int w : e[u]) if (!vis[w]) {
                cout << w << ' ';
                if (++cnt == h) break;
            }
            puts("");
            rep(j, 0, siz) if (e[v][j]!= u) cout << e[v][j] << ' ';
            puts("");
            return 0;
        }
        if (e[v].size() >= h + t + 1) {
            puts("YES");
            cout << u << ' ' << v << endl;
            vis[u] = 1;
            int siz = h - 1;
            rep(j, 0, siz) if (e[u][j] == v) ++siz; else cout << e[u][j] << ' ', vis[e[u][j]] = 1;
            puts("");
            int cnt = 0;
            for (int w : e[v]) if (!vis[w]) {
                cout << w << ' ';
                if (++cnt == t) break;
            }
            puts("");
            return 0;
        }
        int cnt = 0, cu = 0, cv = 0;
        for (int w : e[u]) if (w!= v) { if (++vis[w] == 1) ++cnt; }
        for (int w : e[v]) if (w!= u) { if (++vis[w] == 1) ++cnt; }
        if (cnt < h + t) {
            for (int w : e[u]) vis[w] = 0;
            for (int w : e[v]) vis[w] = 0;
            continue;
        }
        for (int w : e[u]) if (vis[w] == 1 && cu < h) ansu[++cu] = w;
        for (int w : e[v]) if (vis[w] == 1 && cv < t) ansv[++cv] = w;
        for (int w : e[u]) if (vis[w] == 2 && cu < h) vis[w] = 0, ansu[++cu] = w;
        for (int w : e[v]) if (vis[w] == 2 && cv < t) vis[w] = 0, ansv[++cv] = w;
        puts("YES");
        cout << u << ' ' << v << endl;
        rep(j, 1, h) cout << ansu[j] << ' ';
        puts("");
        rep(j, 1, t) cout << ansv[j] << ' ';
        puts("");
        return 0;
    }
}
```
    - **核心实现思想**：先枚举胸部节点 `u`，若其度数小于等于 `h` 则跳过。对于每个相连的腹部节点 `v`，若其度数小于等于 `t` 也跳过。若 `u` 或 `v` 的度数大于等于 `h + t + 1`，则直接确定有解并输出。否则，统计与 `u` 和 `v` 相连节点中仅与一个点相连的节点个数，若总数小于 `h + t` 则继续下一轮。最后按贪心策略从仅与一个点相连和与两个点都相连的节点中选取头和尾节点，满足条件则输出。

### 最优关键思路或技巧
1. **利用度数信息快速筛选**：通过提前统计每个点的度数，在枚举边时，对于不满足最小度数要求的边直接跳过，减少无效计算。
2. **贪心策略选取节点**：优先选取仅与胸部或腹部其中一个点相连的节点作为头或尾，不够时再从与两者都相连的节点中选取，确保在满足条件的情况下高效找到九头蛇图结构。

### 同类型题或类似算法套路拓展
此类题目属于图论中基于特定结构查找的问题。类似套路是先分析目标结构的特征，利用度数、连通性等信息对图中的节点或边进行筛选，再通过贪心、枚举等策略去寻找符合条件的子结构。例如，在一些寻找特定子图（如二分图、完全子图等）的问题中，也可以先通过度数、染色等方式进行初步判断和筛选，再进一步搜索符合条件的子图。

### 洛谷相似题目推荐
1. **P1330 封锁阳光大学**：同样是图论相关问题，需要根据图的结构特点，通过合理的策略对节点进行选择，与本题在分析图结构和选取节点策略上有相似之处。
2. **P2756 飞行员配对方案问题**：涉及图的匹配问题，在处理图中节点关系和寻找满足条件的组合时，思路与本题有一定相似性，都需要对图的结构进行分析和处理。
3. **P1129 驾车旅行**：虽然场景不同，但在根据图中节点间的关系（如距离等），通过枚举和贪心策略来寻找最优路径或方案，与本题在算法思想上有相通之处。 

---
处理用时：109.71秒