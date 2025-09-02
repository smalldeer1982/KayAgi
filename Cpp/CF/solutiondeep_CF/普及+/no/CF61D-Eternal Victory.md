# 题目信息

# Eternal Victory

## 题目描述

经历了一场激烈的战斗之后，Valerian被Shapur抓住了。这个胜利是如此的伟大，以至于Shapur决定把Valerian的失败（也就是他的胜利）的场景雕刻在山上。所以他必须找到最好的地方使他的胜利永远被保存。

他决定到波斯的n个城市去寻找可以使用的最好的山，但是战斗后他太累了，所以不想走太多的路。因此，他希望以最短的路径走遍所有的n个城市。某些城市以双向道路相连。你可以通过这些道路从一个城市到另一个城市。在两个城市间最多只有一条双向道路。所有城市被从1到n编号。

Shapur目前在城市1，他想以最短的路径访问所有其他城市。他可以在任何城市结束他的旅行。

帮助Shapur算出他最少要走多远的路。

## 样例 #1

### 输入

```
3
1 2 3
2 3 4
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3
1 2 3
1 3 3
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 永恒的胜利

## 题目描述
经历了一场激烈的战斗之后，瓦莱里安（Valerian）被沙普尔（Shapur）抓住了。这场胜利意义非凡，以至于沙普尔决定将瓦莱里安的失败场景（也就是他的胜利）雕刻在山上。为此，他必须找到最佳地点，让他的胜利永垂不朽。

他决定前往波斯的n个城市，寻找最适合的山，但战斗结束后他疲惫不堪，不想长途跋涉。因此，他希望以最短路径走遍这n个城市。部分城市之间由双向道路相连，通过这些道路可以从一个城市到达另一个城市。任意两个城市之间最多只有一条双向道路。所有城市从1到n编号。

沙普尔目前在城市1，他希望以最短路径访问其他所有城市，并且可以在任意城市结束旅程。

请帮助沙普尔计算他至少需要行走多远的路程。

## 样例 #1
### 输入
```
3
1 2 3
2 3 4
```
### 输出
```
7
```

## 样例 #2
### 输入
```
3
1 2 3
1 3 3
```
### 输出
```
9
```
### 算法分类
贪心
### 综合分析与结论
所有题解思路一致，均基于贪心策略。由于图为树结构，若从1号节点出发遍历所有节点再回到1号节点，所有边会被经过两次，而题目允许在任意城市结束旅行，所以可让最长链只走一次，其余边都走两次，最终答案为边权和的两倍减去最长链的长度。各题解主要差异在于实现方式，如存储图结构（链式前向星、邻接表等）和求最长链的方法（DFS居多，也有用Dijkstra算法）。
### 所选的题解
- **作者：Kobe303 (5星)**
  - **关键亮点**：思路清晰，先阐述核心思路，再给出详细代码。使用链式前向星存图，代码简洁明了，变量命名规范。
  - **核心代码**：
```cpp
il void add(int u, int v, int w) {
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    e[cnt].w = w;
    head[u] = cnt;
}
il void dfs(int u, int fa, ll sum) {
    longest = std::max(longest, sum);
    for(reg int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v, u, sum + e[i].w);
    }
    return;
}
//...
int main() {
    n = qrint();
    for(reg int i = 1; i < n; ++i) {
        int u = qrint(), v = qrint(), w = qrint();
        add(u, v, w);
        add(v, u, w);
        ans += w;
    }
    dfs(1, 0, 0);
    printf("%lld", ans * 2 - longest);
    return 0;
}
```
  - **核心实现思想**：`add`函数用于构建链式前向星存储图结构。`dfs`函数从1号节点出发，通过递归寻找最长链。在`main`函数中，先读入数据构建图并累加边权和，然后调用`dfs`函数求最长链，最后输出结果。
- **作者：_lxy_ (4星)**
  - **关键亮点**：对题意分析详细，配有图形辅助理解。代码使用邻接表存图，利用Dijkstra算法求最长链，虽然用该算法稍显复杂，但也是一种可行思路。
  - **核心代码**：
```cpp
void add_edge(int u, int v, int w) {
    edge.push_back(Edge{v, w, head[u]});
    head[u] = edge.size() - 1;
}
void dijkstra(int s) {
    mem(dis, 0x7f); mem(vis, 0);
    dis[s] = 0;
    q.push(make_pair(0, s));
    while(!q.empty()) {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = head[u]; i!= -1; i = edge[i].nxt) {
            if(dis[edge[i].to] > dis[u] + edge[i].dis) {
                dis[edge[i].to] = dis[u] + edge[i].dis;
                q.push(make_pair(-dis[edge[i].to], edge[i].to));
            }
        }
    }
}
//...
signed main() {
    scanf("%lld", &n);
    mem(head, -1);
    int i, j, sum = 0;
    for(i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w); sum += w * 2;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dijkstra(1); int mx = 0;
    for(i = 1; i <= n; i++) mx = max(mx, dis[i]); 
    printf("%lld\n", sum - mx);
    return 0;
}
```
  - **核心实现思想**：`add_edge`函数构建邻接表。`dijkstra`函数以1号节点为源点求到其他各点的最短路，实际是在树中求最长链。在`main`函数中，读入数据构建图并累加边权和，调用`dijkstra`函数求最长链，最后输出结果。
- **作者：fjy666 (4星)**
  - **关键亮点**：思路简洁明了，直接阐述通过DFS求以1开头的最长链，代码风格简洁，使用`vector`存储图结构，代码可读性较好。
  - **核心代码**：
```cpp
void dfs(int x, int sum, int fat) {
    M = max(M, sum);
    for(auto to : e[x]) 
        if(to.first!= fat) 
            dfs(to.first, sum + to.second, x);
}
//...
int main() {
    scanf("%d", &n);
    int s = 0;
    _rep(i, 1, n - 1) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        e[a].push_back(make_pair(b, w));
        e[b].push_back(make_pair(a, w));
        s += w;
    }
    dfs(1, 0, -1);
    printf("%lld\n", s * 2ll - M);
    return 0;
}
```
  - **核心实现思想**：`dfs`函数从1号节点出发，递归寻找最长链，`main`函数读入数据构建图并累加边权和，调用`dfs`函数求最长链，最后输出结果。
### 最优关键思路或技巧
- **贪心策略**：利用题目可在任意城市结束旅行这一条件，贪心选择让最长链只走一次，从而简化问题。
- **DFS应用**：多数题解使用DFS遍历树来寻找最长链，利用递归特性简洁地实现。
### 可拓展之处
此类题目可拓展到更复杂的图结构或增加限制条件，如给定多个起始点、路径上有特殊点需特殊处理等。类似算法套路是在图论问题中，分析图的结构特点，利用贪心、搜索等算法优化路径选择。
### 推荐洛谷题目
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)：同样是关于树的图论问题，涉及最小生成树和贪心思想。
- [P3366 最小生成树](https://www.luogu.com.cn/problem/P3366)：经典的最小生成树问题，加深对图论中树结构相关算法的理解。
- [P1396 营救](https://www.luogu.com.cn/problem/P1396)：结合最短路算法与图的遍历，与本题类似，需分析图结构来优化路径。
### 个人心得摘录与总结
部分作者提到初看题目以为是TSP（旅行商问题），但深入分析发现是树结构的特殊路径问题。这提示在解题时不能仅看表面，需深入挖掘题目条件和图的特性，避免陷入复杂算法，找到更简洁有效的解法。 

---
处理用时：64.25秒