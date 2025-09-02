---
title: "Simultaneous Coloring"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1989F
tag: ['强连通分量', '整体二分']
---

# Simultaneous Coloring

## 题目描述

You are given a matrix, consisting of $ n $ rows and $ m $ columns.

You can perform two types of actions on it:

- paint the entire column in blue;
- paint the entire row in red.

Note that you cannot choose which color to paint the row or column.

In one second, you can perform either one action or multiple actions at the same time. If you perform one action, it will be free. If you perform $ k > 1 $ actions at the same time, it will cost $ k^2 $ coins. When multiple actions are performed at the same time, for each cell affected by actions of both types, the color can be chosen independently.

You are asked to process $ q $ queries. Before each query, all cells become colorless. Initially, there are no restrictions on the color of any cells. In the $ i $ -th query, a restriction of the following form is added:

- $ x_i~y_i~c_i $ — the cell in row $ x_i $ in column $ y_i $ should be painted in color $ c_i $ .

Thus, after $ i $ queries, there are $ i $ restrictions on the required colors of the matrix cells. After each query, output the minimum cost of painting the matrix according to the restrictions.

## 输入格式

The first line contains three integers $ n, m $ and $ q $ ( $ 1 \le n, m, q \le 2 \cdot 10^5 $ ) — the size of the matrix and the number of queries.

In the $ i $ -th of the next $ q $ lines, two integers $ x_i, y_i $ and a character $ c_i $ ( $ 1 \le x_i \le n $ ; $ 1 \le y_i \le m $ ; $ c_i \in $ {'R', 'B'}, where 'R' means red, and 'B' means blue) — description of the $ i $ -th restriction. The cells in all queries are pairwise distinct.

## 输出格式

Print $ q $ integers — after each query, output the minimum cost of painting the matrix according to the restrictions.

## 样例 #1

### 输入

```
2 2 4
1 1 R
2 2 R
1 2 B
2 1 B
```

### 输出

```
0
0
0
16
```

## 样例 #2

### 输入

```
3 5 10
1 1 B
2 5 B
2 2 B
2 3 R
2 1 B
3 2 R
3 3 B
1 2 R
1 3 B
3 1 B
```

### 输出

```
0
0
0
0
0
0
16
16
25
25
```



---

---
title: "Grid Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2041G
tag: ['并查集', '强连通分量']
---

# Grid Game

## 题目描述

Claire 喜欢画线。她拿到一张 $ n \times n $ 的网格纸，并开始在上面画所谓的「线」。不过，Claire 所说的「线」并不是我们通常意义上的，而是指一组连续的竖直网格单元格。当她画这样的「线」时，这些单元格会被涂黑。最初，所有单元格都是白色的，画线会将其中的一些变成黑色。画了几条线后，Claire 想知道：她可以将多少个额外的白色单元格涂黑，以确保剩下的白色单元格不再形成一个单一连通块。

在网格中，两个单元格直接相连是指它们共享一个边。如果两个单元格 $ x $ 和 $ y $ 间接相连，说明存在一个单元格序列 $ c_0, c_1, \ldots, c_k $ ，且 $ k > 1 $ ，使得 $ c_0 = x $ ，$ c_k = y $ ，并且对于每个 $ i \in \{1, 2, \ldots, k\} $ ，单元格 $ c_i $ 和 $ c_{i-1} $ 是直接相连的。如果一组单元格中任意两个单元格都是直接或间接相连的，那么它们就形成一个连通块。

网格有 $ n $ 行和 $ n $ 列，编号从 $ 1 $ 到 $ n $ 。Claire 将在上面画 $ q $ 条线。第 $ i $ 条线在 $ y_i $ 列上，从 $ s_i $ 行画到 $ f_i $ 行，每个 $ i \in \{1, 2, \ldots, q\} $ 都满足 $ s_i \leq f_i $ 。注意，每一条被线通过的单元格都会被涂黑。下图展示了一个 $ 20 \times 20 $ 的网格，在其中画了 $ q = 67 $ 条线。标记为红色星号的单元格表示，如果 Claire 将这些单元格涂黑，那么所有的白色单元格将不再形成一个连通的整体。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041G/34528cf71cdc006466f176fdbe6936874dda2994.png)

可以假设，在画完 $ q $ 条线之后，剩余的白色单元格仍形成一个包含至少三个白色单元格的连通块。

## 输入格式

第一行输入一个整数 $ t $ ，代表测试用例的数量。接下来的每一个测试用例从一行开始，这一行包含两个整数 $ n $ 和 $ q $ ，表示网格的尺寸是 $ n \times n $ ，并且 Claire 将在其上画 $ q $ 条线。接下来的 $ q $ 行中，每行包含三个整数 $ y_i $ 、$ s_i $ 和 $ f_i $ 。

- $ 1 \le t \le 125 $
- $ 2 \le n \le 10^9 $
- $ q \ge 1 $ ，所有 $ q $ 的总和不超过 $ 10^5 $ 。
- $ 1 \le y_i \le n $
- $ 1 \le s_i \le f_i \le n $
- 至少有三个白色单元格，并且所有白色单元格形成一个连通块。

## 输出格式

输出一个整数，指示 Claire 可以选择多少种方式将额外的白色单元格涂成黑色，以便剩余的白色单元格不再组成一个单一的连通块。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3 1
2 1 2
5 2
2 1 4
4 2 5
```

### 输出

```
5
15
```



---

---
title: "Trophic Balance Species"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2041K
tag: ['动态规划 DP', '强连通分量']
---

# Trophic Balance Species

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041K/3f57ffd2f2e31a820fdb012c2016af22cc748377.png) 图像由 ChatGPT 4o 生成。在一项跨学科的合作中，一位生态系统科学家与一位计算机科学家联手，通过计算方法分析复杂生态系统的结构。生态系统科学家将整个系统建模成一个有向图 $D = (V, A)$，其中每个物种用一个节点 $v \in V$ 表示，每一对捕食关系由从被捕食者 $x$ 到捕食者 $y$ 的有向边 $(x, y) \in A$ 表示。这种图的结构可以用来模拟生态系统中能量在不同物种间的流动。

在这个系统中，有两个重要概念：

- **独立营养群**：如果集合 $S$ 中的任何物种 $x \in S$ 无法通过一系列有向捕食关系到达集合 $S$ 中的其他物种 $y \in S$（其中 $y \ne x$），那么这个集合 $S$ 就是一个独立营养群，即从 $x$ 到 $y$ 没有有向路径。

- **营养平衡物种**：一个物种如果它受到的影响来自直接或间接捕食者的数量（可以通过有向路径到达的物种，不包括自身）和来自直接或间接被捕食者的数量（可以通过有向路径达到该物种，不包括自身）之间的差值在所有物种中最小，就称为营养平衡物种。

考虑一个含有 $n = 4$ 个物种和 $m = 3$ 条捕食关系的生态系统：

- 物种 1：草（节点 1）
- 物种 2：兔子（节点 2）
- 物种 3：狐狸（节点 3）
- 物种 4：鹰（节点 4）

捕食关系用以下有向边表示：

- $(1, 2)$：草被兔子吃掉。
- $(2, 3)$：兔子被狐狸吃掉。
- $(2, 4)$：兔子也被鹰吃掉。

现在，考虑集合 $S = \{3, 4\}$（狐狸和鹰）。在节点 3（狐狸）和节点 4（鹰）之间没有有向路径；狐狸无法到达鹰，而鹰也无法到达狐狸。因此，这个集合符合独立营养群的定义。

接下来看各物种情况：

- 物种 1（草）：
  - 能到达的物种数：3（兔子、狐狸、鹰）
  - 能被到达的物种数：0（无）
  - 绝对差值：$|3 - 0| = 3$

- 物种 2（兔子）：
  - 能到达的物种数：2（狐狸、鹰）
  - 能被到达的物种数：1（草）
  - 绝对差值：$|2 - 1| = 1$

- 物种 3（狐狸）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

- 物种 4（鹰）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

在这些物种中，兔子的绝对差值最小，为 1，因此，兔子被认为是该生态系统的营养平衡物种。

题目已知生态系统中任何独立营养群的大小最多为 $k$。你的任务是找到生态系统中所有的营养平衡物种。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，其中 $n$ 代表节点数，$m$ 代表边数。这些节点是编号为 $1, 2, \ldots, n$ 的物种。接下来的 $m$ 行，每一行包含两个整数 $x_i$ 和 $y_i$，表示有一条从节点 $x_i$ 指向节点 $y_i$ 的有向边。

- $1 \le n \le 2 \times 10^5$
- $0 \le m \le \min\{n(n-1), 4 \times 10^5\}$
- $k$ 不是输入数据，但保证 $1 \le k \le 16$
- 对于每一个 $i$（$1 \le i \le m$），$1 \le x_i, y_i \le n$ 且 $x_i \ne y_i$
- 在输入中，任意有序对 $(x_i, y_i)$ 最大只出现一次

## 输出格式

在一行上输出所有营养平衡物种的节点编号，��升序排列。节点编号之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
1 2
1 3
1 4
2 3
3 2
```

### 输出

```
2 3 4
```



---

