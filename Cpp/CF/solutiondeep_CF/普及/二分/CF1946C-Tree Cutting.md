# 题目信息

# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6```

### 输出

```
2
1
3
1
1
2```

# AI分析结果

### 题目翻译
给定一棵包含 $n$ 个节点的树。你的任务是找到一个最大的整数 $x$，使得可以从这棵树中删除恰好 $k$ 条边，并且每个剩余的连通分量的大小至少为 $x$。

### 说明/提示
第一组输入数据中的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)

删除边 $1$ — $3$ 后，树将如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)

树被分成了两个连通分量。第一个连通分量包含两个节点：$1$ 和 $2$。第二个连通分量包含三个节点：$3, 4$ 和 $5$。两个连通分量的大小都至少为 $2$。可以证明答案 $3$ 无法达到，因此答案为 $2$。

### 样例 #1

#### 输入
```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6
```

#### 输出
```
2
1
3
1
1
2
```

### 题解分析与结论
本题的核心思路是通过二分查找确定最大可能的 $x$，并通过贪心策略在树上进行边删除操作。各题解的主要思路相似，均采用二分答案结合树形DFS的策略，但在具体实现细节上有所不同。

#### 最优关键思路
1. **二分答案**：由于答案具有单调性，可以通过二分查找来确定最大的 $x$。
2. **贪心策略**：在DFS过程中，若某个子树的大小大于等于 $x$，则删除该子树与父节点的边，并增加连通块数量。
3. **树形DFS**：通过DFS遍历树，计算子树大小，并根据贪心策略进行边删除。

#### 推荐题解
1. **作者：spfa_**（★★★★★）
   - **关键亮点**：代码清晰，注释详细，二分查找与DFS结合紧密，贪心策略实现简洁。
   - **核心代码**：
     ```cpp
     bool check(int x) {
         tot = 1, w = x, sum = n; memset(sz, 0, sizeof(sz));
         dfs(1, 0); return tot > k;
     }
     ```
   - **实现思想**：通过DFS计算子树大小，若子树大小大于等于 $x$ 且剩余部分也大于等于 $x$，则删除该边并增加连通块数量。

2. **作者：cute_overmind**（★★★★☆）
   - **关键亮点**：使用 $lst_p$ 记录子树返回的节点数，贪心策略实现较为直观。
   - **核心代码**：
     ```cpp
     int dfs1(int p, int f, int x) {
         int lst = 1;
         for (int i = num[p]; i; i = e[i].nxt) {
             int t = e[i].t;
             if (t == f) continue;
             lst += dfs1(t, p, x);
         }
         if (lst >= x) ans++, lst = 0;
         return lst;
     }
     ```
   - **实现思想**：在DFS过程中，若子树返回的节点数大于等于 $x$，则增加连通块数量并将返回节点数置为0。

3. **作者：Shadow_T**（★★★★☆）
   - **关键亮点**：代码简洁，贪心策略实现直接，二分查找与DFS结合紧密。
   - **核心代码**：
     ```cpp
     bool check(int x) {
         tot = 0;
         for (int i = 1; i <= n; i++) vis[i] = false;
         vis[1] = true;
         int z = dfs(1, x);
         if (z < x) tot--;
         return tot >= k;
     }
     ```
   - **实现思想**：在DFS过程中，若子树大小大于等于 $x$，则删除该边并增加连通块数量，最后检查连通块数量是否满足要求。

### 扩展思路与推荐题目
1. **扩展思路**：本题的二分答案结合树形DFS的策略可以应用于其他树形结构的问题，如树的直径、树的重心等。
2. **推荐题目**：
   - [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
   - [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
   - [P2634 [国家集训队]聪聪可可](https://www.luogu.com.cn/problem/P2634)

### 个人心得摘录
- **调试经历**：部分题解中提到在调试过程中发现需要特判根节点的连通块大小是否满足条件，否则会导致错误。
- **踩坑教训**：在贪心策略中，若子树大小大于等于 $x$ 但剩余部分不满足条件，则不能删除该边。
- **顿悟感想**：二分答案结合树形DFS的策略在处理树形结构问题时非常有效，尤其是在需要最大化或最小化某个值时。

---
处理用时：43.86秒