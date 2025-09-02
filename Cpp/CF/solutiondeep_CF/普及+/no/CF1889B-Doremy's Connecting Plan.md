# 题目信息

# Doremy's Connecting Plan

## 题目描述

Doremy lives in a country consisting of $ n $ cities numbered from $ 1 $ to $ n $ , with $ a_i $ people living in the $ i $ -th city. It can be modeled as an undirected graph with $ n $ nodes.

Initially, there are no edges in the graph. Now Doremy wants to make the graph connected.

To do this, she can add an edge between $ i $ and $ j $ if

 $ $$$ \sum_{k \in S} a_k \ge i\cdot j \cdot c,  $ $ </p><p>where  $ S $  is the set of all the nodes that are currently in the same connected component of either  $ i $  or  $ j $ , and  $ c $  is a given constant.</p><p>Can Doremy make the graph connected?</p><p>Two nodes  $ (i, j) $  are in the same connected component if there exists a path from  $ i $  to  $ j$$$. A graph is connected if all its nodes are in the same connected component.

## 说明/提示

In the first test case, Doremy can add edges in the following order:

1. Add $ (1,2) $ . This operation is valid because $ a_1 + a_2 = 20 \ge i\cdot j \cdot c = 20 $ .
2. Add $ (1,3) $ . This operation is valid because $ a_1 + a_2 + a_3 = 35 \ge i \cdot j \cdot c = 30 $ .
3. Add $ (1,4) $ . This operation is valid because $ a_1 + a_2 + a_3 + a_4 = 45 \ge i \cdot j \cdot c = 40 $ .

In the second test case, Doremy can add edge $ (1,2) $ because $ a_1 + a_2 =2 \ge 1 \cdot 2 \cdot 1 $ . After that, the graph is connected.

In the third test case, Doremy can add edges in the order $ (5,4) $ , $ (5,3) $ , $ (5,2) $ and $ (5,1) $ .

In the fourth test case, Doremy cannot add any edge at all.

## 样例 #1

### 输入

```
7
4 10
0 20 15 10
2 1
1 1
5 1
0 1 0 4 199
5 2
1 1 3 1 1
5 5
5 6 1 10 2
5 1000000
1000000000000 1000000000000 1000000000000 1000000000000 1000000000000
3 1
0 0 2```

### 输出

```
Yes
Yes
Yes
No
No
Yes
No```

# AI分析结果

### 题目内容
Doremy生活在一个由$n$个城市组成的国家，编号从$1$到$n$，第$i$个城市有$a_i$个人居住。可以将这个国家建模为一个无向图，初始时图中没有边。现在Doremy想要使图连通。

她可以在$i$和$j$之间添加一条边，条件是：
$$
\sum_{k \in S} a_k \ge i \cdot j \cdot c,
$$
其中$S$是当前与$i$或$j$连通的所有节点的集合，$c$是一个给定的常数。

问Doremy是否能够使图连通。

### 算法分类
贪心

### 题解分析与结论
1. **核心思路**：所有题解都基于贪心策略，认为如果图可以连通，那么存在一种方案使得所有边都与节点$1$相连。通过将其他节点按$i \cdot c - a_i$排序，逐步连接节点$1$与这些节点，判断是否满足条件。
2. **难点对比**：主要难点在于如何证明贪心策略的正确性，以及如何高效地排序和判断连接条件。不同题解在证明和实现细节上略有不同，但整体思路一致。
3. **最优思路**：通过证明如果两个节点$i$和$j$可以连接，那么至少有一个节点可以与节点$1$连接，从而将问题简化为只考虑与节点$1$的连接。然后按$i \cdot c - a_i$从小到大排序，贪心地连接节点。

### 评分较高的题解
1. **作者：Cocoly1990 (5星)**
   - **关键亮点**：提供了详细的证明，证明了贪心策略的正确性，并给出了线性时间复杂度的优化思路。
   - **代码实现**：按$i \cdot c - a_i$排序，贪心地连接节点$1$与其他节点。
   ```cpp
   sort(a.begin() + 2, a.begin() + n + 1, [&](pii a, pii b) {
       return a.F - a.S * c > b.F - b.S * c;
   });
   int s = a[1].F;
   rep(i, 2, n) {
       if(a[i].S * c <= s + a[i].F) s += a[i].F;
       else { cout << "No\n"; return; }
   }
   cout << "Yes\n";
   ```

2. **作者：bmatrix (4星)**
   - **关键亮点**：通过反证法证明了贪心策略的正确性，并提供了详细的代码实现。
   - **代码实现**：按$i \cdot c - a_i$排序，贪心地连接节点$1$与其他节点。
   ```cpp
   sort(b + 2, b + n + 1);
   int flag = 1, sum = a[1];
   for(int i = 2; i <= n; i++) {
       if(sum >= b[i].x) sum += a[b[i].id];
       else { flag = 0; break; }
   }
   if(flag) cout << "Yes\n";
   else cout << "No\n";
   ```

3. **作者：_Ink (4星)**
   - **关键亮点**：通过反证法证明了贪心策略的正确性，并提供了详细的代码实现。
   - **代码实现**：按$i \cdot c - a_i$排序，贪心地连接节点$1$与其他节点。
   ```cpp
   sort(ct + 2, ct + 1 + n);
   long long sum = ct[1].a;
   for(int i = 2; i <= n; i++) {
       if(sum + ct[i].a >= 1ll * ct[i].rk * c) sum += ct[i].a;
       else { cout << "No\n"; return; }
   }
   cout << "Yes\n";
   ```

### 关键思路与技巧
- **贪心策略**：通过证明所有边都可以与节点$1$相连，将问题简化为只考虑与节点$1$的连接。
- **排序优化**：按$i \cdot c - a_i$从小到大排序，确保优先连接更容易满足条件的节点。
- **反证法**：通过反证法证明贪心策略的正确性，确保算法的可靠性。

### 拓展思路
- **类似问题**：可以拓展到其他需要贪心策略的图论问题，如最小生成树、最短路径等。
- **优化思路**：可以考虑进一步优化排序和判断过程，减少时间复杂度。

### 推荐题目
1. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

---
处理用时：36.86秒