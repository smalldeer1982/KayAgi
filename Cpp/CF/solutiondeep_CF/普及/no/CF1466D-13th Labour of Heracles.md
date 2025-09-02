# 题目信息

# 13th Labour of Heracles

## 题目描述

You've probably heard about the twelve labors of Heracles, but do you have any idea about the thirteenth? It is commonly assumed it took him a dozen years to complete the twelve feats, so on average, a year to accomplish every one of them. As time flows faster these days, you have minutes rather than months to solve this task. But will you manage?

In this problem, you are given a tree with $ n $ weighted vertices. A tree is a connected graph with $ n - 1 $ edges.

Let us define its $ k $ -coloring as an assignment of $ k $ colors to the edges so that each edge has exactly one color assigned to it. Note that you don't have to use all $ k $ colors.

A subgraph of color $ x $ consists of these edges from the original tree, which are assigned color $ x $ , and only those vertices that are adjacent to at least one such edge. So there are no vertices of degree $ 0 $ in such a subgraph.

The value of a connected component is the sum of weights of its vertices. Let us define the value of a subgraph as a maximum of values of its connected components. We will assume that the value of an empty subgraph equals $ 0 $ .

There is also a value of a $ k $ -coloring, which equals the sum of values of subgraphs of all $ k $ colors. Given a tree, for each $ k $ from $ 1 $ to $ n - 1 $ calculate the maximal value of a $ k $ -coloring.

## 说明/提示

The optimal $ k $ -colorings from the first test case are the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/d2af7a338e536cf5cb74dc12f223baf263c91efb.png)In the $ 1 $ -coloring all edges are given the same color. The subgraph of color $ 1 $ contains all the edges and vertices from the original graph. Hence, its value equals $ 3 + 5 + 4 + 6 = 18 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/4196e1299ca3444421f255a73f95765dbb2837c9.png)In an optimal $ 2 $ -coloring edges $ (2, 1) $ and $ (3,1) $ are assigned color $ 1 $ . Edge $ (4, 3) $ is of color $ 2 $ . Hence the subgraph of color $ 1 $ consists of a single connected component (vertices $ 1, 2, 3 $ ) and its value equals $ 3 + 5 + 4 = 12 $ . The subgraph of color $ 2 $ contains two vertices and one edge. Its value equals $ 4 + 6 = 10 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/5febb146f8282f40f79782da3d6b349a0e6be93a.png)In an optimal $ 3 $ -coloring all edges are assigned distinct colors. Hence subgraphs of each color consist of a single edge. They values are as follows: $ 3 + 4 = 7 $ , $ 4 + 6 = 10 $ , $ 3 + 5 = 8 $ .

## 样例 #1

### 输入

```
4
4
3 5 4 6
2 1
3 1
4 3
2
21 32
2 1
6
20 13 17 13 13 11
2 1
3 1
4 1
5 1
6 1
4
10 6 6 6
1 2
2 3
4 1```

### 输出

```
18 22 25
53
87 107 127 147 167
28 38 44```

# AI分析结果

### 题目内容翻译

#### 题目描述

你可能听说过赫拉克勒斯的十二项任务，但你知道第十三项任务吗？通常认为他花了十二年时间完成了这十二项任务，因此平均每年完成一项。如今时间流逝得更快，你只有几分钟而不是几个月的时间来解决这个问题。你能成功吗？

在这个问题中，你被给定一棵有 $n$ 个带权顶点的树。树是一个有 $n - 1$ 条边的连通图。

我们定义它的 $k$ - 染色为将 $k$ 种颜色分配给边，使得每条边恰好被分配一种颜色。注意，你不需要使用所有的 $k$ 种颜色。

颜色为 $x$ 的子图由原始树中分配了颜色 $x$ 的边组成，并且只包含那些至少与一条这样的边相邻的顶点。因此，在这样的子图中没有度数为 $0$ 的顶点。

一个连通分量的值是其所有顶点的权重之和。我们定义一个子图的值为其所有连通分量值的最大值。我们假设空子图的值等于 $0$。

$k$ - 染色的值等于所有 $k$ 种颜色的子图值的总和。给定一棵树，对于每个 $k$ 从 $1$ 到 $n - 1$，计算 $k$ - 染色的最大值。

#### 说明/提示

第一个测试用例的最优 $k$ - 染色如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/d2af7a338e536cf5cb74dc12f223baf263c91efb.png)在 $1$ - 染色中，所有边都被赋予相同的颜色。颜色 $1$ 的子图包含原始图中的所有边和顶点。因此，它的值等于 $3 + 5 + 4 + 6 = 18$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/4196e1299ca3444421f255a73f95765dbb2837c9.png)在最优的 $2$ - 染色中，边 $(2, 1)$ 和 $(3,1)$ 被赋予颜色 $1$。边 $(4, 3)$ 被赋予颜色 $2$。因此，颜色 $1$ 的子图由一个连通分量（顶点 $1, 2, 3$）组成，其值等于 $3 + 5 + 4 = 12$。颜色 $2$ 的子图包含两个顶点和一条边，其值等于 $4 + 6 = 10$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1466D/5febb146f8282f40f79782da3d6b349a0e6be93a.png)在最优的 $3$ - 染色中，所有边都被赋予不同的颜色。因此，每种颜色的子图由一条边组成。它们的值如下：$3 + 4 = 7$，$4 + 6 = 10$，$3 + 5 = 8$。

#### 样例 #1

##### 输入

```
4
4
3 5 4 6
2 1
3 1
4 3
2
21 32
2 1
6
20 13 17 13 13 11
2 1
3 1
4 1
5 1
6 1
4
10 6 6 6
1 2
2 3
4 1```

##### 输出

```
18 22 25
53
87 107 127 147 167
28 38 44```

### 算法分类
贪心

### 题解分析与结论

#### 综合分析
1. **核心思路**：所有题解都基于贪心策略，通过优先选择权重较大的节点来增加贡献，从而最大化染色方案的总值。
2. **实现难点**：如何高效地计算每个节点的贡献次数，并确保每个节点的贡献次数不超过其度数。
3. **优化点**：通过排序和贪心策略，可以高效地计算每个染色方案的最大值。

#### 所选高星题解

1. **SSerxhs (4星)**
   - **关键亮点**：通过证明同色边必连通，简化了问题，直接转化为贪心策略，代码简洁高效。
   - **核心代码**：
     ```cpp
     sort(q+1,q+n+1);
     i=1;printf("%lld",ans);
     while (i<=n)
     {
         if (q[i].rd) --q[i].rd,ans+=q[i].w,printf(" %lld",ans); else ++i;
     }
     ```
   - **实现思想**：按节点权重降序排序，依次增加贡献，直到每个节点的贡献次数达到其度数。

2. **georgehe (4星)**
   - **关键亮点**：通过感性思考得出结论，每添加一种颜色可以增加一个节点的值，代码清晰易懂。
   - **核心代码**：
     ```cpp
     sort(edge+1,edge+n+1,cmp);
     int now=1;
     cout<<ans<<" ";
     for(int i=2;i<=n-1;i++)
     {
         while(edge[now].cnt==1)
             now++;
         ans+=edge[now].val;
         edge[now].cnt--;
         cout<<ans<<" ";
     }
     ```
   - **实现思想**：按节点权重降序排序，依次增加贡献，直到每个节点的贡献次数达到其度数。

3. **liuzhongrui (4星)**
   - **关键亮点**：通过记录每个顶点的度数，并排序非叶子节点的权重，逐步增加贡献，代码结构清晰。
   - **核心代码**：
     ```cpp
     sort(b+1,b+cnt+1);
     cout<<ans<<' ';
     for (i=cnt; i>=1; i--)
         ans+=b[i],cout<<ans<<' ';
     ```
   - **实现思想**：按非叶子节点的权重降序排序，依次增加贡献，直到每个节点的贡献次数达到其度数。

### 最优关键思路或技巧
1. **贪心策略**：优先选择权重较大的节点来增加贡献，确保每次增加的值最大。
2. **排序优化**：通过排序节点权重，可以高效地选择下一个贡献节点。
3. **度数限制**：确保每个节点的贡献次数不超过其度数，避免重复计算。

### 可拓展之处
1. **类似问题**：其他需要最大化某种值的树形结构问题，如最大匹配、最大独立集等。
2. **算法套路**：贪心策略在树形结构中的应用，优先选择局部最优解以达到全局最优。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：46.33秒