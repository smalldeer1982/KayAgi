---
title: "Iris and the Tree"
layout: "post"
diff: 普及+/提高
pid: CF2006B
tag: ['树的遍历']
---

# Iris and the Tree

## 题目描述

Given a rooted tree with the root at vertex $ 1 $ . For any vertex $ i $ ( $ 1 < i \leq n $ ) in the tree, there is an edge connecting vertices $ i $ and $ p_i $ ( $ 1 \leq p_i < i $ ), with a weight equal to $ t_i $ .

Iris does not know the values of $ t_i $ , but she knows that $ \displaystyle\sum_{i=2}^n t_i = w $ and each of the $ t_i $ is a non-negative integer.

The vertices of the tree are numbered in a special way: the numbers of the vertices in each subtree are consecutive integers. In other words, the vertices of the tree are numbered in the order of a depth-first search.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/ed42d3ad002b849b19e2cab01dc8c80b05d343e1.png) The tree in this picture satisfies the condition. For example, in the subtree of vertex $ 2 $ , the vertex numbers are $ 2, 3, 4, 5 $ , which are consecutive integers.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/fbbdad2f1a4867f5d12408bb700e0a02f6731145.png) The tree in this picture does not satisfy the condition, as in the subtree of vertex $ 2 $ , the vertex numbers $ 2 $ and $ 4 $ are not consecutive integers.We define $ \operatorname{dist}(u, v) $ as the length of the simple path between vertices $ u $ and $ v $ in the tree.

Next, there will be $ n - 1 $ events:

- Iris is given integers $ x $ and $ y $ , indicating that $ t_x = y $ .

After each event, Iris wants to know the maximum possible value of $ \operatorname{dist}(i, i \bmod n + 1) $ independently for each $ i $ ( $ 1\le i\le n $ ). She only needs to know the sum of these $ n $ values. Please help Iris quickly get the answers.

Note that when calculating the maximum possible values of $ \operatorname{dist}(i, i \bmod n + 1) $ and $ \operatorname{dist}(j, j \bmod n + 1) $ for $ i \ne j $ , the unknown edge weights may be different.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ w $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 0 \leq w \leq 10^{12} $ ) — the number of vertices in the tree and the sum of the edge weights.

The second line of each test case contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \leq p_i < i $ ) — the description of the edges of the tree.

Then follow $ n-1 $ lines indicating the events. Each line contains two integers $ x $ and $ y $ ( $ 2 \leq x \leq n $ , $ 0 \leq y \leq w $ ), indicating that $ t_x = y $ .

It is guaranteed that all $ x $ in the events are distinct. It is also guaranteed that the sum of all $ y $ equals $ w $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one line containing $ n-1 $ integers, each representing the answer after each event.

## 说明/提示

In the first test case, $ \operatorname{dist}(1, 2) = \operatorname{dist}(2, 1) = t_2 = w = 10^{12} $ , so $ \operatorname{dist}(1, 2) + \operatorname{dist}(2, 1) = 2 \cdot 10^{12} $ .

In the second test case, the tree after Iris found out all $ t_x $ is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/cb4bc8b1d32fd5015d0673154cd358fe4ee772d9.png) $ \operatorname{dist}(1, 2) = t_2 $ , $ \operatorname{dist}(2, 3) = t_2 + t_3 $ , $ \operatorname{dist}(3, 4) = t_3 + t_4 $ , $ \operatorname{dist}(4, 1) = t_4 $ . After the first event, she found out that $ t_2 = 2 $ , so $ \operatorname{dist}(1, 2) = 2 $ . At the same time:

- $ \operatorname{dist}(2, 3) $ is maximized if $ t_3 = 7 $ , $ t_4 = 0 $ . Then $ \operatorname{dist}(2, 3) = 9 $ .
- $ \operatorname{dist}(3, 4) $ and $ \operatorname{dist}(4, 1) $ are maximized if $ t_3 = 0 $ , $ t_4 = 7 $ . Then $ \operatorname{dist}(3, 4) = \operatorname{dist}(4, 1) = 7 $ .

Thus, the answer is $ 2 + 9 + 7 + 7 = 25 $ .

After the second event, she found out that $ t_4 = 4 $ , then $ t_3 = w - t_2 - t_4 = 4 $ . $ \operatorname{dist}(1, 2) = 2 $ , $ \operatorname{dist}(2, 3) = 2 + 3 = 5 $ , $ \operatorname{dist}(3, 4) = 3 + 4 = 7 $ , $ \operatorname{dist}(4, 1) = 4 $ . Thus, the answer is $ 2 + 5 + 7 + 4 = 18 $ .

## 样例 #1

### 输入

```
4
2 1000000000000
1
2 1000000000000
4 9
1 1 1
2 2
4 4
3 3
6 100
1 2 3 2 1
6 17
3 32
2 4
4 26
5 21
10 511
1 2 2 4 2 1 1 8 8
3 2
6 16
10 256
9 128
2 1
5 8
8 64
4 4
7 32
```

### 输出

```
2000000000000
25 18 18
449 302 247 200 200
4585 4473 2681 1567 1454 1322 1094 1022 1022
```



---

---
title: "Tree Pruning"
layout: "post"
diff: 普及+/提高
pid: CF2018C
tag: ['贪心', '树的遍历']
---

# Tree Pruning

## 题目描述

[t+pazolite, ginkiha, Hommarju - Paved Garden](https://soundcloud.com/fractalex-gd/ginkiha-paved-garden-little)

⠀



You are given a tree with $ n $ nodes, rooted at node $ 1 $ . In this problem, a leaf is a non-root node with degree $ 1 $ .

In one operation, you can remove a leaf and the edge adjacent to it (possibly, new leaves appear). What is the minimum number of operations that you have to perform to get a tree, also rooted at node $ 1 $ , where all the leaves are at the same distance from the root?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 5 \cdot 10^5 $ ) — the number of nodes.

Each of the next $ n-1 $ lines contains two integers $ u $ , $ v $ ( $ 1 \leq u, v \leq n $ , $ u \neq v $ ), describing an edge that connects $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the minimum number of operations needed to achieve your goal.

## 说明/提示

In the first two examples, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2018C/46789adad3b93ca642b297f7ca0ca574c7f98f60.png)In the first example, by removing edges $ (1, 3) $ and $ (2, 5) $ , the resulting tree has all leaves (nodes $ 6 $ and $ 7 $ ) at the same distance from the root (node $ 1 $ ), which is $ 3 $ . The answer is $ 2 $ , as it is the minimum number of edges that need to be removed to achieve the goal.

In the second example, removing edges $ (1, 4) $ and $ (5, 7) $ results in a tree where all leaves (nodes $ 4 $ and $ 5 $ ) are at the same distance from the root (node $ 1 $ ), which is $ 2 $ .

## 样例 #1

### 输入

```
3
7
1 2
1 3
2 4
2 5
4 6
4 7
7
1 2
1 3
1 4
2 5
3 6
5 7
15
12 9
1 6
6 14
9 11
8 7
3 5
13 5
6 10
13 15
13 6
14 12
7 2
8 1
1 4
```

### 输出

```
2
2
5
```



---

---
title: "Skibidus and Slay"
layout: "post"
diff: 普及+/提高
pid: CF2065F
tag: ['树的遍历']
---

# Skibidus and Slay

## 题目描述

我们定义一个长度为 $k$ 的序列的**多数元素**为：该序列中唯一一个出现次数严格大于 $\lfloor \frac{k}{2} \rfloor$ 的数值。如果不存在这样的数值，则称该序列没有多数元素。例如，序列 $[1,3,2,3,3]$ 的多数元素为 $3$（因为 $3$ 出现了 $3$ 次，$3 > \lfloor \frac{5}{2} \rfloor = 2$），而序列 $[1,2,3,4,5]$ 和 $[1,3,2,3,4]$ 则没有多数元素。

Skibidus 找到了一棵有 $n$ 个顶点的树 $ ^{\text{∗}} $ 以及一个长度为 $n$ 的数组 $a$。其中，顶点 $i$ 上写有数值 $a_i$，且 $a_i$ 是区间 $[1,n]$ 内的一个整数。

对于每个 $i$（$1 \le i \le n$），请判断是否存在一条非平凡的简单路径 $ ^{\text{†}} $，使得该路径上顶点构成的数值序列的多数元素为 $i$。

 $ ^{\text{∗}} $ 树指的是一个无环的连通图。
 
 $ ^{\text{†}} $ 非平凡的简单路径指的是一个顶点序列 $v_1, v_2, \dots, v_m$（其中 $m \ge 2$），满足对于所有 $1 \le i \le m-1$，顶点 $v_i$ 与 $v_{i+1}$ 之间存在一条边，并且所有顶点均互不相同。注意路径至少包含 $2$ 个顶点。

## 输入格式

每个测试包含多个测试用例。输入的第一行给出测试用例的数量 $t$（$1 \le t \le 10^4$）。随后是各个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 5 \cdot 10^5$），表示顶点数。

每个测试用例的第二行包含 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$），表示写在顶点上的整数。

接下来 $n-1$ 行，每行包含两个整数 $u_i$ 和 $v_i$，表示一条连接顶点 $u_i$ 与 $v_i$ 的边（$1 \le u_i,v_i \le n$ 且 $u_i \neq v_i$）。

题目保证给定的边构成一棵树，并且所有测试用例中 $n$ 的总和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个长度为 $n$ 的二进制字符串 $s$。其中第 $i$ 个字符 $s_i$ 定义如下：

- 如果存在一条非平凡路径，使得该路径上顶点构成的数值序列的多数元素为 $i$，则 $s_i$ 为 `1`；
- 否则，$s_i$ 为 `0`。

## 说明/提示

- 在第一个测试用例中，没有任何一条非平凡路径能使得 $1$、$2$ 或 $3$ 成为多数元素，因此输出的二进制字符串为 `000`。
- 在第二个测试用例中，路径 $1 \rightarrow 2 \rightarrow 4$ 是一条非平凡路径，在该路径上 $3$ 为多数元素。

## 样例 #1

### 输入

```
4
3
1 2 3
1 3
2 3
4
3 1 1 3
1 2
2 3
4 2
4
2 4 4 2
1 2
2 3
3 4
13
1 4 4 7 4 7 1 1 7 11 11 11 11
1 2
2 3
3 4
4 5
4 6
2 7
7 8
2 9
6 10
5 11
11 12
10 13
```

### 输出

```
000
1010
0001
1001001000100
```



---

---
title: "Tree Jumps"
layout: "post"
diff: 普及+/提高
pid: CF2070D
tag: ['动态规划 DP', '广度优先搜索 BFS', '树的遍历']
---

# Tree Jumps

## 题目描述

给定一棵包含 $n$ 个顶点的有根树。树中顶点编号为 $1$ 到 $n$，根为顶点 $1$。定义 $d_x$ 为根到顶点 $x$ 的距离（最短路径上的边数）。

初始时，一个棋子被放置在根节点。你可以执行以下操作任意次（包括零次）：

- 将棋子从当前顶点 $v$ 移动到顶点 $u$，满足 $d_u = d_v + 1$。如果 $v$ 是根节点，可以选择任意满足此约束的顶点 $u$；但如果 $v$ 不是根节点，则 $u$ 不能是 $v$ 的邻居（即 $v$ 和 $u$ 之间不能有直接边相连）。

例如在上图的树结构中，允许的移动包括：$1 \rightarrow 2$，$1 \rightarrow 5$，$2 \rightarrow 7$，$5 \rightarrow 3$，$5 \rightarrow 4$，$3 \rightarrow 6$，$7 \rightarrow 6$。

如果一个顶点序列满足：存在一种棋子移动方式，使得棋子按顺序恰好访问序列中的所有顶点（且仅这些顶点），则该序列被称为有效的。

你的任务是计算有效顶点序列的数量。由于答案可能很大，请输出其对 $998244353$ 取模的结果。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 3 \cdot 10^5$）。

第二行包含 $n-1$ 个整数 $p_2, p_3, \dots, p_n$（$1 \le p_i < i$），其中 $p_i$ 表示第 $i$ 个顶点的父节点。顶点 $1$ 是根节点。

输入额外约束：所有测试用例的 $n$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——有效顶点序列的数量模 $998244353$ 的结果。

## 说明/提示

第一个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 4]$，$[1, 4, 3]$。

第二个示例中，有效序列为：$[1]$，$[1, 2]$。

第三个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 2, 7]$，$[1, 2, 7, 6]$，$[1, 5]$，$[1, 5, 3]$，$[1, 5, 3, 6]$，$[1, 5, 4]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
1 2 1
3
1 2
7
1 2 2 1 4 5
```

### 输出

```
4
2
8
```



---

---
title: "Trapmigiano Reggiano"
layout: "post"
diff: 普及+/提高
pid: CF2071C
tag: ['搜索', '贪心', '树的遍历']
---

# Trapmigiano Reggiano

## 题目描述

在一个意大利村庄中，一只饥饿的老鼠从给定树 $^{\text{∗}}$ 的顶点 $\textrm{st}$ 出发，该树包含 $n$ 个顶点。

给定一个长度为 $n$ 的排列 $p$ $^{\text{†}}$，共有 $n$ 个步骤。在第 $i$ 步时：

- 一块诱人的帕尔马干酪出现在顶点 $p_i$。若老鼠当前位于顶点 $p_i$，它将停留并享用；否则，它将沿简单路径向 $p_i$ 移动一条边。

你的任务是找到这样的排列，使得经过所有 $n$ 步后，老鼠必定到达陷阱所在的顶点 $\textrm{en}$。

注意：老鼠必须在完成所有 $n$ 步后到达 $\textrm{en}$，但在过程中可能提前经过 $\textrm{en}$。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$\textrm{st}$ 和 $\textrm{en}$（$1 \le n \le 10^5$；$1 \le \textrm{st}, \textrm{en} \le n$）——分别表示树的顶点数、起始顶点和陷阱顶点。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$）——表示通过边连接的顶点编号。

保证输入的边构成一棵树。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例：

- 若无解，输出 $-1$；
- 否则，输出 $n$ 个整数 $p_1, p_2, \ldots, p_n$，表示干酪在顶点出现的顺序，确保老鼠最终落入陷阱顶点 $\textrm{en}$。

若存在多个解，输出任意一个即可。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，成功捕获老鼠：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 = \textrm{en}. $$

第二个测试用例中，当 $n = 2$ 时一个可能的排列是 $p = [1, 2]$：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 \overset{p_2 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

第三个测试用例中，当 $n = 3$ 时一个可能的排列是 $p = [3, 1, 2]$：

$$ \textrm{st} = 2 \overset{p_1 = 3}{\xrightarrow{\hspace{1.3cm}}} 3 \overset{p_2 = 1}{\xrightarrow{\hspace{1.3cm}}} 2 \overset{p_3 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 1 1
2 1 2
1 2
3 2 2
1 2
2 3
6 1 4
1 2
1 3
4 5
5 6
1 4
```

### 输出

```
1 
1 2 
3 1 2 
1 4 3 2 6 5
```



---

