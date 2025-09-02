# 题目信息

# Tree Tag

## 题目描述

Alice and Bob are playing a fun game of tree tag.

The game is played on a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Recall that a tree on $ n $ vertices is an undirected, connected graph with $ n-1 $ edges.

Initially, Alice is located at vertex $ a $ , and Bob at vertex $ b $ . They take turns alternately, and Alice makes the first move. In a move, Alice can jump to a vertex with distance at most $ da $ from the current vertex. And in a move, Bob can jump to a vertex with distance at most $ db $ from the current vertex. The distance between two vertices is defined as the number of edges on the unique simple path between them. In particular, either player is allowed to stay at the same vertex in a move. Note that when performing a move, a player only occupies the starting and ending vertices of their move, not the vertices between them.

If after at most $ 10^{100} $ moves, Alice and Bob occupy the same vertex, then Alice is declared the winner. Otherwise, Bob wins.

Determine the winner if both players play optimally.

## 说明/提示

In the first test case, Alice can win by moving to vertex $ 1 $ . Then wherever Bob moves next, Alice will be able to move to the same vertex on the next move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/49586895aed4babac3e35aba1e1c4162a3ac0674.png)In the second test case, Bob has the following strategy to win. Wherever Alice moves, Bob will always move to whichever of the two vertices $ 1 $ or $ 6 $ is farthest from Alice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/514885d88075ac42c59e9da88fb4903131f99500.png)

## 样例 #1

### 输入

```
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10```

### 输出

```
Alice
Bob
Alice
Alice```

# AI分析结果

### 题目翻译
## 树标签

### 题目描述
爱丽丝（Alice）和鲍勃（Bob）正在玩一个有趣的树标签游戏。

游戏在一棵有 $n$ 个顶点的树上进行，顶点编号从 $1$ 到 $n$。回想一下，有 $n$ 个顶点的树是一个无向、连通且有 $n - 1$ 条边的图。

最初，爱丽丝位于顶点 $a$，鲍勃位于顶点 $b$。他们轮流行动，爱丽丝先行动。在一次行动中，爱丽丝可以跳到距离当前顶点最多为 $da$ 的顶点。在一次行动中，鲍勃可以跳到距离当前顶点最多为 $db$ 的顶点。两个顶点之间的距离定义为它们之间唯一简单路径上的边数。特别地，任何一个玩家都可以在一次行动中停留在同一个顶点。注意，在行动时，玩家只占据行动的起点和终点，而不是它们之间的顶点。

如果在最多 $10^{100}$ 次行动后，爱丽丝和鲍勃占据同一个顶点，那么爱丽丝获胜。否则，鲍勃获胜。

如果两个玩家都采取最优策略，确定获胜者。

### 说明/提示
在第一个测试用例中，爱丽丝可以移动到顶点 $1$ 获胜。然后无论鲍勃下一步移动到哪里，爱丽丝都能够在下一步移动到同一个顶点。

![图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/49586895aed4babac3e35aba1e1c4162a3ac0674.png)
在第二个测试用例中，鲍勃有以下获胜策略。无论爱丽丝移动到哪里，鲍勃总是会移动到顶点 $1$ 或 $6$ 中距离爱丽丝最远的那个顶点。

![图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/514885d88075ac42c59e9da88fb4903131f99500.png)

### 样例 #1
#### 输入
```
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10
```
#### 输出
```
Alice
Bob
Alice
Alice
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是判断在哪些情况下爱丽丝能获胜，其他情况则鲍勃获胜。爱丽丝获胜的情况主要有三种：初始距离小于等于 $da$、$2\times da\geq db$、树的直径小于等于 $2\times da$。

在算法要点上，大部分题解都采用深度优先搜索（DFS）来计算树的直径和两点间的距离。解决的难点在于如何全面地分析出爱丽丝获胜的所有情况，并通过合理的代码实现来判断这些情况。

### 所选题解
- **作者：AFOier (赞：7)，4星**
    - **关键亮点**：思路清晰，先明确爱丽丝获胜的几种情况，再通过代码实现判断，代码结构简洁，可读性高。
- **作者：CYZZ (赞：4)，4星**
    - **关键亮点**：对爱丽丝获胜的三种情况分析详细，代码实现中对树的直径和初始距离的计算采用 DFS 方法，逻辑清晰。
- **作者：lory1608 (赞：1)，4星**
    - **关键亮点**：直接给出爱丽丝获胜的三个条件，然后通过代码依次判断，简洁明了。

### 重点代码
以下是作者为 AFOier 的题解的核心代码，实现思路是先通过 DFS 计算树的直径，再判断爱丽丝是否满足获胜条件：
```cpp
void dfs(int w, int fa) {
    dis[w] = dis[fa] + 1;
    for(int i = 0; i < (int)e[w].size(); i++) {
        int ver = e[w][i];
        if(ver != fa) dfs(ver, w);
    }
}
void solve() {
    scanf("%d%d%d%d%d", &n, &a, &b, &da, &db);
    for(int i = 1; i <= n; i++) e[i].clear();
    for(int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1, 0); int maxw = 0;
    for(int i = 1; i <= n; i++) 
        if(dis[maxw] < dis[i]) maxw = i;
    dfs(maxw, 0);
    maxw = 0;
    for(int i = 1; i <= n; i++) 
        if(dis[maxw] < dis[i]) maxw = i;
    if(dis[maxw] <= da*2+1) {
        printf("Alice\n");
        return;
    }
    dfs(a, 0);
    if(dis[b] <= da+1) {
        printf("Alice\n");
        return;
    }
    if(2*da >= db) {
        printf("Alice\n");
        return;
    }
    printf("Bob\n");
}
```

### 可拓展思路
同类型题目可能会改变游戏规则，如增加更多玩家、改变移动规则等，但核心思路仍然是分析每个玩家的获胜条件。类似算法套路主要是利用图论中的搜索算法（如 DFS、BFS）来计算图的相关属性（如直径、两点间距离等）。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及图的拓扑排序和图的遍历。
- [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)：图的欧拉路径问题。
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)：最小生成树问题，与图的结构和边的权重有关。

### 个人心得摘录与总结
- **作者：lory1608**：表示比赛时没想清楚导致没做出来，提醒我们在比赛时要理清思路，全面分析问题。
- **作者：神光qwq**：分享了自己的思维历程，强调了分析问题时要逐步考虑各种因素，从简单情况入手，再结合题目条件的特殊性质（如树的性质）来完善思路。 

---
处理用时：48.36秒