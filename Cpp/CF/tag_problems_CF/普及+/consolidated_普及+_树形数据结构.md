---
title: "Gardener and Tree"
layout: "post"
diff: 普及+/提高
pid: CF1593E
tag: ['贪心', '树形数据结构']
---

# Gardener and Tree

## 题目描述

一棵 $n$ 个结点的树。一个人做了多次操作，在每次操作中，他删除了树的所有叶结点。叶结点指的是树中至多有一个相邻节点的结点。

![](http://61.186.173.89:2019/2021/10/15/c4f2d0e1827d5.png)

如上图中所示的树。下图显示了对树进行一次操作后的结果。
![](http://61.186.173.89:2019/2021/10/15/14602247d6f15.png)

注意特殊操作的情况:

1、对空树($0$ 个顶点)进行操作时不会改变它;

2、对于仅有一个顶点的树进行操作时会移除这个顶点(这个顶点被当作一个叶子);

3、对于仅有两个顶点的树进行操作时将删除两个顶点(两个顶点都被当作叶子处理)。

求 $k$ 次操作后还剩下多少个顶点?

## 输入格式

第一行包含一个整数 $T$。然后是 $T$ 组测试数据。

对于每组测试数据，共 $n$ 行：第一行包含两个整数 $n$和 $k$——树中的顶点数和操作次数。然后是 $n−1$ 行，每一行包含两个整数 $u$ 和 $v$ ($1\le u,v≤n，u \ne v$)，表示一条无向边。保证是一个树，且每两组测试数据中间有一个换行。

## 输出格式

共 $T$ 行，每行一个正整数 $ans$，表示每组数据的答案。

## 样例 #1

### 输入

```
6

14 1
1 2
2 3
2 4
4 5
4 6
2 7
7 8
8 9
8 10
3 11
3 12
1 13
13 14

2 200000
1 2

3 2
1 2
2 3

5 1
5 1
3 2
2 1
5 4

6 2
5 1
2 5
5 6
4 2
3 4

7 1
4 3
5 1
1 3
6 1
1 7
2 1
```

### 输出

```
7
0
0
3
1
2
```



---

---
title: "Vlad and Unfinished Business"
layout: "post"
diff: 普及+/提高
pid: CF1675F
tag: ['贪心', '树形数据结构']
---

# Vlad and Unfinished Business

## 题目描述

### 题意简述

有一棵 $n$ 个节点的树，从节点 $x$ 出发，需要到 $a_1,a_2\dots a_k$ 节点完成任务（任意顺序），最终到达终点 $y$。走每条边的花费为 $1$，求最小花费。

## 输入格式

第一行一个正整数 $t$ 表示数据组数。

对于每组数据，第一行两个正整数 $n,k$ 表示节点数量和任务数量；第二行两个正整数 $x,y$ 表示起点编号和终点编号；第三行 $k$ 个正整数 $a_1,a_2\dots a_k$ 表示任务所在节点编号；接下来 $n-1$ 行，每行两个正整数表示一条边的两个端点编号。

## 输出格式

对于每组数据，输出一行一个正整数表示最小花费。

### 数据规模

$t\le 10^4,1\le n,k\le 2\times 10^5,\sum n\le2\times10^5$

## 样例 #1

### 输入

```
3

3 1
1 3
2
1 3
1 2

6 4
3 5
1 6 2 1
1 3
3 4
3 5
5 6
5 2

6 2
3 2
5 3
1 3
3 4
3 5
5 6
5 2
```

### 输出

```
3
7
2
```



---

---
title: "Fake Plastic Trees"
layout: "post"
diff: 普及+/提高
pid: CF1693B
tag: ['贪心', '树形数据结构']
---

# Fake Plastic Trees

## 题目描述

We are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is the vertex $ 1 $ and the parent of the vertex $ v $ is $ p_v $ .

There is a number written on each vertex, initially all numbers are equal to $ 0 $ . Let's denote the number written on the vertex $ v $ as $ a_v $ .

For each $ v $ , we want $ a_v $ to be between $ l_v $ and $ r_v $ $ (l_v \leq a_v \leq r_v) $ .

In a single operation we do the following:

- Choose some vertex $ v $ . Let $ b_1, b_2, \ldots, b_k $ be vertices on the path from the vertex $ 1 $ to vertex $ v $ (meaning $ b_1 = 1 $ , $ b_k = v $ and $ b_i = p_{b_{i + 1}} $ ).
- Choose a non-decreasing array $ c $ of length $ k $ of nonnegative integers: $ 0 \leq c_1 \leq c_2 \leq \ldots \leq c_k $ .
- For each $ i $ $ (1 \leq i \leq k) $ , increase $ a_{b_i} $ by $ c_i $ .

What's the minimum number of operations needed to achieve our goal?

## 输入格式

The first line contains an integer $ t $ $ (1\le t\le 1000) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2\le n\le 2 \cdot 10^5) $ — the number of the vertices in the tree.

The second line of each test case contains $ n - 1 $ integers, $ p_2, p_3, \ldots, p_n $ $ (1 \leq p_i < i) $ , where $ p_i $ denotes the parent of the vertex $ i $ .

The $ i $ -th of the following $ n $ lines contains two integers $ l_i $ and $ r_i $ $ (1 \le l_i \le r_i \le 10^9) $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output the minimum number of operations needed.

## 说明/提示

In the first test case, we can achieve the goal with a single operation: choose $ v = 2 $ and $ c = [1, 2] $ , resulting in $ a_1 = 1, a_2 = 2 $ .

In the second test case, we can achieve the goal with two operations: first, choose $ v = 2 $ and $ c = [3, 3] $ , resulting in $ a_1 = 3, a_2 = 3, a_3 = 0 $ . Then, choose $ v = 3, c = [2, 7] $ , resulting in $ a_1 = 5, a_2 = 3, a_3 = 7 $ .

## 样例 #1

### 输入

```
4
2
1
1 5
2 9
3
1 1
4 5
2 4
6 10
4
1 2 1
6 9
5 6
4 5
2 4
5
1 2 3 4
5 5
4 4
3 3
2 2
1 1
```

### 输出

```
1
2
2
5
```



---

---
title: "Paint the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1975D
tag: ['贪心', '树形数据结构']
---

# Paint the Tree

## 题目描述

378QAQ has a tree with $ n $ vertices. Initially, all vertices are white.

There are two chess pieces called $ P_A $ and $ P_B $ on the tree. $ P_A $ and $ P_B $ are initially located on vertices $ a $ and $ b $ respectively. In one step, 378QAQ will do the following in order:

1. Move $ P_A $ to a neighboring vertex. If the target vertex is white, this vertex will be painted red.
2. Move $ P_B $ to a neighboring vertex. If the target vertex is colored in red, this vertex will be painted blue.

Initially, the vertex $ a $ is painted red. If $ a=b $ , the vertex $ a $ is painted blue instead. Note that both the chess pieces must be moved in each step. Two pieces can be on the same vertex at any given time.

378QAQ wants to know the minimum number of steps to paint all vertices blue.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1\leq n\leq 2\cdot 10^5 $ ).

The second line of each test case contains two integers $ a $ and $ b $ ( $ 1\leq a,b\leq n $ ).

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of steps to paint all vertices blue.

## 说明/提示

In the first test case, 378QAQ can paint all vertices blue in the following order:

- Initially, $ P_A $ is located on the vertex $ 1 $ , and $ P_B $ is located on the vertex $ 2 $ . The vertex $ 1 $ is painted red and the vertex $ 2 $ is white.
- 378QAQ moves $ P_A $ to the vertex $ 2 $ and paints it red. Then 378QAQ moves $ P_B $ to the vertex $ 1 $ and paints it blue.
- 378QAQ moves $ P_A $ to the vertex $ 1 $ . Then 378QAQ moves $ P_B $ to the vertex $ 2 $ and paints it blue.

## 样例 #1

### 输入

```
3
2
1 2
1 2
5
1 2
1 2
1 3
1 4
1 5
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4
```

### 输出

```
2
8
13
```



---

