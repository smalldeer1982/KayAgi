# 题目信息

# Flawed Flow

## 题目描述

Emuskald considers himself a master of flow algorithms. Now he has completed his most ingenious program yet — it calculates the maximum flow in an undirected graph. The graph consists of $ n $ vertices and $ m $ edges. Vertices are numbered from 1 to $ n $ . Vertices $ 1 $ and $ n $ being the source and the sink respectively.

However, his max-flow algorithm seems to have a little flaw — it only finds the flow volume for each edge, but not its direction. Help him find for each edge the direction of the flow through this edges. Note, that the resulting flow should be correct maximum flow.

More formally. You are given an undirected graph. For each it's undirected edge ( $ a_{i} $ , $ b_{i} $ ) you are given the flow volume $ c_{i} $ . You should direct all edges in such way that the following conditions hold:

1. for each vertex $ v $ $ (1&lt;v&lt;n) $ , sum of $ c_{i} $ of incoming edges is equal to the sum of $ c_{i} $ of outcoming edges;
2. vertex with number $ 1 $ has no incoming edges;
3. the obtained directed graph does not have cycles.

## 说明/提示

In the first test case, 10 flow units pass through path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/112cc3d7bc5d5ae260d516a02ced6ab796839bee.png), and 5 flow units pass directly from source to sink: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/851f40f264708d94590f3171217fe3d9e053dcee.png).

## 样例 #1

### 输入

```
3 3
3 2 10
1 2 10
3 1 5
```

### 输出

```
1
0
1
```

## 样例 #2

### 输入

```
4 5
1 2 10
1 3 10
2 3 5
4 2 15
3 4 5
```

### 输出

```
0
0
1
1
0
```

# AI分析结果

### 题目翻译
# 有缺陷的流

## 题目描述
Emuskald 自认为是流量算法大师。现在，他完成了他最巧妙的程序——计算无向图中的最大流。该图由 $n$ 个顶点和 $m$ 条边组成，顶点编号从 1 到 $n$，顶点 1 和 $n$ 分别为源点和汇点。

然而，他的最大流算法似乎有一个小缺陷——它只能找到每条边的流量，但找不到流量的方向。请帮助他找出每条边的流量方向，注意，得到的流应该是正确的最大流。

更正式地说，给定一个无向图，对于每条无向边 $(a_i, b_i)$，都给出了流量 $c_i$。你应该为所有边指定方向，使得以下条件成立：
1. 对于每个顶点 $v$（$1 < v < n$），入边的 $c_i$ 之和等于出边的 $c_i$ 之和；
2. 编号为 1 的顶点没有入边；
3. 得到的有向图没有环。

## 说明/提示
在第一个测试用例中，10 个流量单位通过路径![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/112cc3d7bc5d5ae260d516a02ced6ab796839bee.png)，5 个流量单位直接从源点流向汇点：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/851f40f264708d94590f3171217fe3d9e053dcee.png)。

## 样例 #1
### 输入
```
3 3
3 2 10
1 2 10
3 1 5
```
### 输出
```
1
0
1
```

## 样例 #2
### 输入
```
4 5
1 2 10
1 3 10
2 3 5
4 2 15
3 4 5
```
### 输出
```
0
0
1
1
0
```

### 综合分析与结论
这些题解的核心思路都是利用拓扑排序的思想，结合广度优先搜索（BFS）来确定无向图中每条边的方向，以满足流量守恒和无环的条件。
- **思路**：对于非源非汇点，其入流为所有连接边流量之和的一半。从源点开始进行 BFS，在搜索过程中确定边的方向，同时更新各点的剩余流量，当某个非汇点的剩余流量为 0 时，将其加入队列继续搜索。
- **算法要点**：建图时需要同时记录边的正反方向及相关信息；使用数组记录各点的初始流量和剩余流量；通过 BFS 遍历图，根据流量情况确定边的方向。
- **解决难点**：如何保证图中无环是关键，利用拓扑排序的思想，从源点开始逐步确定边的方向，确保不会形成环。同时，要正确处理各点的流量更新，保证除源点和汇点外的点入流等于出流。

### 题解评分
- **灵茶山艾府**：5 星。思路清晰，代码简洁，直接点明使用拓扑排序思想结合 BFS 解决问题，代码实现逻辑清晰，易于理解。
- **OIer_ACMer**：4 星。思路详细，有具体步骤说明，但代码中使用了大量自定义函数和结构体，增加了代码的复杂度。
- **Graph_Theory**：3 星。思路有一定的分析，但代码中使用 `#define int long long` 可能会带来不必要的内存开销，且代码注释较少。
- **SFlyer**：3 星。思路简洁，但代码中使用 `using namespace std;` 可能会导致命名冲突，且代码解释不够详细。
- **Erica_N_Contina**：3 星。思路分析较为清晰，但代码只是部分代码，没有完整的实现。

### 所选题解
- **灵茶山艾府（5 星）**：
    - **关键亮点**：思路清晰，代码简洁，直接套用拓扑排序思想，将入流当作入度进行 BFS 搜索，代码逻辑一目了然。
    - **核心代码**：
```go
package main

import (
    "bufio"
   . "fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    var n, m, v, w, c int
    Fscan(in, &n, &m)
    type edge struct{ to, i, d, f int }
    g := make([][]edge, n+1)
    f := make([]int, n+1)
    for i := 0; i < m; i++ {
        Fscan(in, &v, &w, &c)
        g[v] = append(g[v], edge{w, i, 0, c})
        g[w] = append(g[w], edge{v, i, 1, c})
        f[v] += c
        f[w] += c
    }
    for i := range f {
        f[i] >>= 1
    }

    ans := make([]int, m)
    for i := range ans {
        ans[i] = -1
    }
    q := []int{1}
    for len(q) > 0 {
        v := q[0]
        q = q[1:]
        for _, e := range g[v] {
            if ans[e.i] == -1 {
                ans[e.i] = e.d
                w := e.to
                f[w] -= e.f
                if w!= n && f[w] == 0 {
                    q = append(q, w)
                }
            }
        }
    }
    for _, d := range ans {
        Fprintln(out, d)
    }
}
```
- **OIer_ACMer（4 星）**：
    - **关键亮点**：思路详细，有具体步骤说明，适合初学者理解。
    - **核心代码**：
```c++
void bfs()
{
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;
        for (int i = head[u]; ~i; i = edge[i].next)
        {
            Edge e = edge[i];
            if (!e.flag)
            {
                continue;
            }
            int v = e.to;
            if (vis[v])
            {
                continue;
            }
            liuliang[v] -= 2 * e.w; // 将流量减去二倍
            dirc[e.id] = e.d;
            edge[i ^ 1].flag = false;
            if (!liuliang[v] && v!= n)
            {
                q.push(v);
            }
        }
    }
}
```

### 最优关键思路或技巧
- **拓扑排序思想**：将入流当作入度，利用 BFS 进行拓扑排序，确保图中无环，同时逐步确定边的方向。
- **流量更新**：通过减去二倍边权来更新各点的流量，保证除源点和汇点外的点入流等于出流。

### 可拓展之处
同类型题或类似算法套路：
- 网络流中的最小费用最大流问题，在确定流量方向的基础上，还需要考虑费用的最小化。
- 有向图的拓扑排序问题，在不同的条件下确定图的拓扑序。

### 洛谷相似题目推荐
- P3376 【模板】网络最大流
- P4722 【模板】最大流 加强版 / 预流推进
- P2740 [USACO4.2]草地排水Drainage Ditches

### 个人心得摘录与总结
- **OIer_ACMer**：“这道题刚刚拿到的时候一脸懵逼，看到了绿色的标识就觉得自己行了，但是仔细读完题目后，不仅觉得这道题很有意义，而且——太难了（建议升蓝或紫）”。总结：不要被题目难度标签误导，要仔细分析题目，有些看似简单的题目可能有一定难度。 

---
处理用时：45.18秒