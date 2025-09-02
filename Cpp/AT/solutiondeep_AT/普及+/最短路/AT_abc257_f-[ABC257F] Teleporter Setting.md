# 题目信息

# [ABC257F] Teleporter Setting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc257/tasks/abc257_f

$ N $ 個の町と $ M $ 個のテレポーターがあり、 町は町 $ 1 $, 町 $ 2 $, $ \ldots $, 町$ N $ と番号づけられています。  
 それぞれのテレポーターは $ 2 $ つの町を双方向に結んでおり、テレポーターを使用する事によってその $ 2 $ つの町の間を $ 1 $ 分で移動することができます。

$ i $ 番目のテレポーターは町 $ U_i $ と町 $ V_i $ を双方向に結んでいますが、 いくつかのテレポーターについては結ぶ町の片方が決まっておらず、 $ U_i=0 $ のときそのテレポーターが結ぶ町の片方は町 $ V_i $ であるが、 もう片方が未定であることを意味します。

$ i=1,2,\ldots,N $ それぞれについて、次の問題を解いてください。

> 結ぶ町の片方が未定となっているテレポーターの結ぶ先をすべて町 $ i $ とする。 この時に町 $ 1 $ から町 $ N $ まで移動するのに最小で何分かかるか求めよ。 町 $ 1 $ から町 $ N $ までテレポーターのみを使って移動するのが不可能な場合は $ -1 $ を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\times\ 10^5 $
- $ 1\leq\ M\leq\ 3\times\ 10^5 $
- $ 0\leq\ U_i\ <\ V_i\leq\ N $
- $ i\ \neq\ j $ ならば $ (U_i,V_i)\neq\ (U_j,V_j) $
- 入力は全て整数

### Sample Explanation 1

結ぶ先が未定となっているテレポーターの結び先を町 $ 1 $ としたとき、 $ 1 $ 番目と $ 2 $ 番目のテレポーターはともに町 $ 1 $ と町 $ 2 $ を結びます。 このとき、町 $ 1 $ から町 $ 3 $ への移動はできません。 結ぶ先が未定となっているテレポーターの結び先を町 $ 2 $ としたとき、 $ 1 $ 番目のテレポーターは町 $ 2 $ 同士を、 $ 2 $ 番目のテレポーターは町 $ 1 $ と町 $ 2 $ を結びます。 このときもやはり、町 $ 1 $ から町 $ 3 $ への移動はできません。 結ぶ先が未定となっているテレポーターの結び先を町 $ 3 $ としたとき、 $ 1 $ 番目のテレポーターは町 $ 3 $ と町 $ 2 $ を、 $ 2 $ 番目のテレポーターは町 $ 1 $ と町 $ 2 $ を結びます。 この時、次のようにして町 $ 1 $ から町 $ 3 $ へ $ 2 $ 分で移動できます。 - $ 2 $ 番目のテレポーターを使用し、町 $ 1 $ から町 $ 2 $ まで移動する。 - $ 1 $ 番目のテレポーターを使用し、町 $ 2 $ から町 $ 3 $ まで移動する。 よって、$ -1,-1,2 $ をこの順に出力します。 結ぶ先が未定となっているテレポーターの結び先によっては、 同じ町同士を結ぶテレポーターが存在する可能性や、 ある $ 2 $ つの町を結ぶテレポーターが複数存在する可能性がある事に注意してください。

## 样例 #1

### 输入

```
3 2

0 2

1 2```

### 输出

```
-1 -1 2```

## 样例 #2

### 输入

```
5 5

1 2

1 3

3 4

4 5

0 2```

### 输出

```
3 3 3 3 2```

# AI分析结果

### 题目中文重写
有 $N$ 个城镇和 $M$ 个传送门，城镇编号为城镇 $1$、城镇 $2$、$\cdots$、城镇 $N$。
每个传送门双向连接两个城镇，使用传送门可以在 $1$ 分钟内往返于这两个城镇之间。
第 $i$ 个传送门双向连接城镇 $U_i$ 和城镇 $V_i$，但有些传送门连接的城镇有一个尚未确定，当 $U_i = 0$ 时，表示该传送门连接的一个城镇是城镇 $V_i$，另一个尚未确定。
对于 $i = 1, 2, \cdots, N$，分别解决以下问题：
> 将所有连接城镇尚未确定的传送门的连接目标都设为城镇 $i$。此时，求从城镇 $1$ 到城镇 $N$ 移动最少需要多少分钟。如果仅使用传送门无法从城镇 $1$ 移动到城镇 $N$，则输出 $-1$。

### 综合分析与结论
这些题解的核心思路都是先预处理出从节点 $1$ 和节点 $N$ 到其他节点的最短路径，再考虑不确定边对最短路的影响，通过分析不同的路径情况来计算最终答案。
- **思路**：大部分题解通过建一个超级源点（编号为 $0$），将所有不确定的边连向这个点，每次查询相当于从 $i$ 到 $0$ 连一条边权为 $0$ 的边。然后从节点 $1$ 和节点 $N$ 分别跑单源最短路，对于每个 $i$，答案通常有三种情况：不经过 $i$ 直接从 $1$ 到 $N$；从 $1$ 到 $0$ 再到 $i$ 再到 $N$；从 $1$ 到 $i$ 再到 $0$ 再到 $N$。
- **算法要点**：主要使用了 Dijkstra 或 BFS 来求单源最短路径，通过预处理减少重复计算，时间复杂度可以接受。
- **解决难点**：难点在于如何处理不确定的边以及如何高效地计算不同情况下的最短路。通过引入超级源点和预处理单源最短路，将问题转化为几种固定情况的比较，避免了每次查询都重新计算最短路。

### 所选题解
- **mz2022（4星）**
    - **关键亮点**：思路清晰，通过建超级源点的方式简化问题，代码实现简洁明了，使用优先队列优化的 Dijkstra 算法求单源最短路。
- **qiliu（4星）**
    - **关键亮点**：详细分析了最短路的几种情况，通过预处理两个 $dis$ 数组，实现 $O(1)$ 统计答案，代码有详细注释，可读性高。
- **FreedomKing（4星）**
    - **关键亮点**：同样考虑了不确定边对最短路的贡献，通过预处理最小值，减少计算量，代码结构清晰。

### 重点代码
#### mz2022
```cpp
// 加边函数
void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
// 从 1 开始的 Dijkstra
void d1() {
    memset(vis, 0, sizeof(vis));
    memset(dis1, 0x3f, sizeof(dis1));
    q.push(make_pair(0, 1));
    dis1[1] = 0;
    while (!q.empty()) {
        int now = q.top().second;
        q.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        for (int i = head[now]; i; i = e[i].next)
            if (dis1[now] + e[i].w < dis1[e[i].to]) {
                dis1[e[i].to] = dis1[now] + e[i].w;
                q.push(make_pair(dis1[e[i].to], e[i].to));
            }
    }
}
// 从 n 开始的 Dijkstra
void d2() {
    memset(vis, 0, sizeof(vis));
    memset(dis2, 0x3f, sizeof(dis2));
    q.push(make_pair(0, n));
    dis2[n] = 0;
    while (!q.empty()) {
        int now = q.top().second;
        q.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        for (int i = head[now]; i; i = e[i].next)
            if (dis2[now] + e[i].w < dis2[e[i].to]) {
                dis2[e[i].to] = dis2[now] + e[i].w;
                q.push(make_pair(dis2[e[i].to], e[i].to));
            }
    }
}
// 主函数
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v, 1);
        add(v, u, 1);
    }
    d1();
    d2();
    for (int i = 1; i <= n; i++) {
        int ans = min({dis1[n], dis1[0] + dis2[i], dis1[i] + dis2[0]});
        if (ans == 0x3f3f3f3f) cout << -1 << " ";
        else cout << ans << " ";
    }
    return 0;
}
```
**核心实现思想**：通过邻接表存储图，使用优先队列优化的 Dijkstra 算法分别求出从 $1$ 和 $n$ 到其他节点的最短路径，最后对于每个 $i$，取三种情况的最小值作为答案。

#### qiliu
```cpp
// bfs 处理出 dis
void get_dis(int S, int *dis) {
    queue<int> q;
    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0, to; i < a[now].size(); i++) {
            to = a[now][i];
            if (dis[to] > dis[now] + 1) dis[to] = dis[now] + 1, q.push(to);
        }
    }
    return;
}
// 主函数
signed main() {
    n = rd(), m = rd();
    for (int i = 1; i <= m; i++) {
        int u = rd(), v = rd();
        if (u == 0) leaf.push_back(v);
        else a[u].push_back(v), a[v].push_back(u);
    }
    get_dis(1, dis1), get_dis(n, disn);
    int minn_of_dis1 = INF, minn_of_disn = INF, dis1_min = -1, disn_min = -1;
    for (auto x : leaf) {
        if (minn_of_dis1 > dis1[x])  minn_of_dis1 = dis1[x], dis1_min = x;
        if (minn_of_disn > disn[x])  minn_of_disn = disn[x], disn_min = x;
    }
    for (int i = 1; i <= n; i++) {
        int ans = min({dis1[n],
                       (dis1_min == -1 || disn_min == -1 ? INF : dis1[dis1_min] + 2 + disn[disn_min]),
                       (disn_min == -1 ? INF : dis1[i] + 1 + disn[disn_min]),
                       (dis1_min == -1 ? INF : dis1[dis1_min] + 1 + disn[i])});
        wt(ans < INF ? ans : -1), putchar(' ');
    }
    return 0;
}
```
**核心实现思想**：使用 BFS 预处理出从 $1$ 和 $n$ 到其他节点的最短路径，同时找出所有叶子节点中到 $1$ 和 $n$ 距离最近的节点，最后对于每个 $i$，根据四种情况计算答案。

#### FreedomKing
```cpp
// bfs 求最短路
inline void bfs(int x, int *dis) {
    for (int i = 1; i <= n; i++) dis[i] = 1e9;
    queue<int> q;
    dis[x] = 0;
    q.push(x);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < e[u].size(); i++) {
            int v = e[u][i];
            if (dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return;
}
// 主函数
signed main() {
    n = qr;
    int m = qr;
    for (int i = 1; i <= m; i++) {
        int u = qr, v = qr;
        if (!u) p.push_back(v);
        else {
            e[u].push_back(v);
            e[v].push_back(u);
        }
    }
    bfs(1, dis1);
    bfs(n, disn);
    int min1 = 1e9, minn = 1e9;
    for (int i = 0; i < p.size(); i++) {
        int v = p[i];
        min1 = min(min1, dis1[v]);
        minn = min(minn, disn[v]);
    }
    for (int i = 1; i <= n; i++) {
        int ans = min({dis1[n], min1 + 2 + minn, dis1[i] + 1 + minn, min1 + 1 + disn[i]});
        if (ans >= 1e9) qws(-1);
        else qws(ans);
    }
    return 0;
}
```
**核心实现思想**：使用 BFS 预处理出从 $1$ 和 $n$ 到其他节点的最短路径，同时找出所有不确定边的确定节点中到 $1$ 和 $n$ 距离最近的节点，最后对于每个 $i$，取四种情况的最小值作为答案。

### 最优关键思路或技巧
- **引入超级源点**：将所有不确定的边连向一个超级源点，简化了不确定边的处理，将问题转化为固定的几种路径情况。
- **预处理单源最短路**：通过从节点 $1$ 和节点 $N$ 分别跑单源最短路，减少了重复计算，提高了效率。

### 可拓展之处
同类型题或类似算法套路：
- 对于有多种状态变化的图的最短路问题，可以考虑通过预处理和分析不同状态下的路径情况来解决。
- 可以将超级源点的思想应用到其他图论问题中，简化复杂边的处理。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 个人心得摘录与总结
- **Robin_kool**：一开始的错解没有把 $0$ 考虑进去，导致预处理出来的最短路可能不准确，后来考虑把 $0$ 当做真实的一个点，将 $0$ 到 $i$ 看成有一条长度为 $0$ 的边，问题就好解决了。总结：在处理图论问题时，要充分考虑所有节点和边的影响，避免遗漏关键信息。
- **_ldyex_**：看到其他巨佬用 Dijkstra，自己和同学用 BFS 写出来，说明解决问题的方法不唯一，要勇于尝试不同的算法。总结：在算法选择上，要根据问题特点和自身掌握情况灵活选择，不要局限于一种方法。

---
处理用时：66.99秒