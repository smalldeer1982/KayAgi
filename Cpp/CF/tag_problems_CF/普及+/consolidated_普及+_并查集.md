---
title: "Social Network"
layout: "post"
diff: 普及+/提高
pid: CF1609D
tag: ['并查集']
---

# Social Network

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/bd782248ee184d971343d4489aa3f05723b81f9f.png)William arrived at a conference dedicated to cryptocurrencies. Networking, meeting new people, and using friends' connections are essential to stay up to date with the latest news from the world of cryptocurrencies.

The conference has $ n $ participants, who are initially unfamiliar with each other. William can introduce any two people, $ a $ and $ b $ , who were not familiar before, to each other.

William has $ d $ conditions, $ i $ 'th of which requires person $ x_i $ to have a connection to person $ y_i $ . Formally, two people $ x $ and $ y $ have a connection if there is such a chain $ p_1=x, p_2, p_3, \dots, p_k=y $ for which for all $ i $ from $ 1 $ to $ k - 1 $ it's true that two people with numbers $ p_i $ and $ p_{i + 1} $ know each other.

For every $ i $ ( $ 1 \le i \le d $ ) William wants you to calculate the maximal number of acquaintances one person can have, assuming that William satisfied all conditions from $ 1 $ and up to and including $ i $ and performed exactly $ i $ introductions. The conditions are being checked after William performed $ i $ introductions. The answer for each $ i $ must be calculated independently. It means that when you compute an answer for $ i $ , you should assume that no two people have been introduced to each other yet.

## 输入格式

The first line contains two integers $ n $ and $ d $ ( $ 2 \le n \le 10^3, 1 \le d \le n - 1 $ ), the number of people, and number of conditions, respectively.

Each of the next $ d $ lines each contain two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n, x_i \neq y_i $ ), the numbers of people which must have a connection according to condition $ i $ .

## 输出格式

Output $ d $ integers. $ i $ th number must equal the number of acquaintances the person with the maximal possible acquaintances will have, if William performed $ i $ introductions and satisfied the first $ i $ conditions.

## 说明/提示

The explanation for the first test case:

In this explanation, the circles and the numbers in them denote a person with the corresponding number. The line denotes that William introduced two connected people. The person marked with red has the most acquaintances. These are not the only correct ways to introduce people.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/a4c52dc40d0c621cc37cb8aa412551d28349b4ab.png)

## 样例 #1

### 输入

```
7 6
1 2
3 4
2 4
7 6
6 5
1 7
```

### 输出

```
1
1
3
3
3
6
```

## 样例 #2

### 输入

```
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4
```

### 输出

```
1
2
3
4
5
5
6
8
```



---

---
title: "Tokitsukaze and Two Colorful Tapes"
layout: "post"
diff: 普及+/提高
pid: CF1677C
tag: ['贪心', '并查集']
---

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 输入格式

The first contains a single positive integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 1\leq n \leq 10^5 $ ) — the number of colors.

The second line contains $ n $ integers $ ca_1, ca_2, \ldots, ca_n $ ( $ 1 \leq ca_i \leq n $ ) — the color of each position of the first tape. It is guaranteed that $ ca $ is a permutation.

The third line contains $ n $ integers $ cb_1, cb_2, \ldots, cb_n $ ( $ 1 \leq cb_i \leq n $ ) — the color of each position of the second tape. It is guaranteed that $ cb $ is a permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print a single integer — the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1
```

### 输出

```
18
10
0
```



---

---
title: "Microcycle"
layout: "post"
diff: 普及+/提高
pid: CF1927F
tag: ['并查集', '深度优先搜索 DFS', '生成树']
---

# Microcycle

## 题目描述

Given an undirected weighted graph with $ n $ vertices and $ m $ edges. There is at most one edge between each pair of vertices in the graph, and the graph does not contain loops (edges from a vertex to itself). The graph is not necessarily connected.

A cycle in the graph is called simple if it doesn't pass through the same vertex twice and doesn't contain the same edge twice.

Find any simple cycle in this graph in which the weight of the lightest edge is minimal.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3 \le n \le m \le \min(\frac{n\cdot(n - 1)}{2}, 2 \cdot 10^5) $ ) — the size of the graph and the number of edges.

The next $ m $ lines of the test case contain three integers $ u $ , $ v $ , and $ w $ ( $ 1 \le u, v \le n $ , $ u \ne v $ , $ 1 \le w \le 10^6 $ ) — vertices $ u $ and $ v $ are connected by an edge of weight $ w $ .

It is guaranteed that there is at most one edge between each pair of vertices. Note that under the given constraints, there is always at least one simple cycle in the graph.

It is guaranteed that the sum of the values of $ m $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a pair of numbers $ b $ and $ k $ , where:

- $ b $ — the minimum weight of the edge in the found cycle,
- $ k $ — the number of vertices in the found cycle.

On the next line, output $ k $ numbers from $ 1 $ to $ n $ — the vertices of the cycle in traversal order.

Note that the answer always exists, as under the given constraints, there is always at least one simple cycle in the graph.

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
3 1 1
4 5 1
5 6 1
6 4 1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
6 15
1 2 4
5 2 8
6 1 7
6 3 10
6 5 1
3 2 8
4 3 4
5 3 6
2 6 6
5 4 5
4 1 3
6 4 5
4 2 1
3 1 7
1 5 5
4 6
2 3 2
1 3 10
1 4 1
3 4 7
2 4 5
1 2 2
4 5
2 1 10
3 1 3
4 2 6
1 4 7
2 3 3
```

### 输出

```
1 3
1 2 3 
3 3
6 4 5 
1 5
4 2 1 6 3 
1 4
1 4 3 2 
3 3
2 3 1
```



---

---
title: "Connect the Dots"
layout: "post"
diff: 普及+/提高
pid: CF2020D
tag: ['并查集']
---

# Connect the Dots

## 题目描述

### 题意描述
爱丽丝画了一条直线，并在上面标记了n个点，从1到n进行索引。最初，点之间没有弧，所以它们都是不相交的。之后，Alice执行以下类型的m个操作：

1.   她选了三个整数ai bi和ki
2.   她选择点ai，ai+di,ai+2di......ai+ki*di，并用弧线连接每对点。

在完成所有m操作后，她想知道这些点形成的连接组件的数量。

如果两个点之间通过几个（**可能为零**）弧和其他点存在路径，则称这两个点位于一个连接的组件中。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量t。每个测试用例的描述如下:


每个测试用例的第一行包含两个整数n和m。
以下m行中的第i行包含三个整数。

保证所有测试用例中的n和m之和不超过2*1e5。

## 输出格式

对于每个测试用例，输出连接的组件数量。

## 样例 #1

### 输入

```
3
10 2
1 2 4
2 2 4
100 1
19 2 4
100 3
1 2 5
7 2 6
17 2 31
```

### 输出

```
2
96
61
```



---

---
title: "Baggage Claim"
layout: "post"
diff: 普及+/提高
pid: CF2097B
tag: ['图论', '并查集']
---

# Baggage Claim

## 题目描述

每个机场都有一个行李提取区，Balbesovo 机场也不例外。某天，Sheremetyevo 机场的一位管理员提出了一个不同寻常的想法：将传统的行李传送带形状从旋转盘改为更复杂的形式。

假设行李提取区被表示为一个 $n \times m$ 的矩形网格。管理员提议传送带的路径应穿过单元格 $p_1, p_2, \ldots, p_{2k+1}$，其中 $p_i = (x_i, y_i)$。

对于每个单元格 $p_i$ 和下一个单元格 $p_{i+1}$（其中 $1 \leq i \leq 2k$），这两个单元格必须共享一条公共边。此外，路径必须是简单的，即对于任意两个不同的索引 $i \neq j$，单元格 $p_i$ 和 $p_j$ 不能重合。

不幸的是，路径计划被意外洒出的咖啡弄脏了，只保留了路径中奇数索引的单元格：$p_1, p_3, p_5, \ldots, p_{2k+1}$。你的任务是给定这些 $k+1$ 个单元格，计算恢复原始完整路径 $p_1, p_2, \ldots, p_{2k+1}$ 的可能方式的数量。

由于答案可能非常大，请输出其对 $10^9+7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 3 \cdot 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$1 \le n, m \le 1000$，$n \cdot m \ge 3$，$1 \le k \le \left\lfloor \frac12 (n m - 1) \right\rfloor$）—— 网格的尺寸和定义路径长度的参数。

接下来是 $k+1$ 行，第 $i$ 行包含两个整数 $x_{2i-1}$ 和 $y_{2i-1}$（$1 \le x_{2i-1} \le n$，$1 \le y_{2i-1} \le m$）—— 路径上单元格 $p_{2i-1}$ 的坐标。

保证所有 $(x_{2i-1}, y_{2i-1})$ 对都是不同的。

保证所有测试用例的 $n \cdot m$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出一个整数——恢复原始完整路径的方式数量对 $10^9+7$ 取模的结果。

## 说明/提示

在第一个测试用例中，有两种可能的路径：

- $(1,1) \to (2,1) \to (2, 2) \to (2, 3) \to (2, 4)$
- $(1,1) \to (1,2) \to (2, 2) \to (2, 3) \to (2, 4)$

在第二个测试用例中，没有合适的路径，因为单元格 $(1,1)$ 和 $(1,4)$ 没有共同的相邻单元格。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 4 2
1 1
2 2
2 4
1 4 1
1 1
1 4
5 5 11
2 5
3 4
4 5
5 4
4 3
5 2
4 1
3 2
2 1
1 2
2 3
1 4
3 4 4
1 2
2 1
3 2
2 3
3 4
3 3 2
2 2
1 1
1 3
```

### 输出

```
2
0
2
5
1
```



---

---
title: "Goblin"
layout: "post"
diff: 普及+/提高
pid: CF2106F
tag: ['并查集', '前缀和']
---

# Goblin

## 题目描述

TC 博士有一位新病人叫哥布林。他想测试哥布林的智力，但对标准测试感到厌倦了，于是决定增加难度。

首先，他创建一个长度为 $n$ 的二进制字符串$^{\text{∗}}$ $s$。然后，他创建 $n$ 个二进制字符串 $a_1, a_2, \ldots, a_n$。已知 $a_i$ 是通过先复制 $s$，再翻转第 $i$ 个字符（$\texttt{1}$ 变为 $\texttt{0}$，反之亦然）得到的。创建完所有 $n$ 个字符串后，他将它们排列成一个 $n \times n$ 的网格 $g$，其中 $g_{i, j} = a_{i_j}$。

一个大小为 $k$ 的集合 $S$ 被认为是好的，如果它满足以下条件：

1. 对于所有 $1 \leq i \leq k$，有 $1 \leq x_i, y_i \leq n$；
2. 对于所有 $1 \leq i \leq k$，有 $g_{x_i, y_i} = \texttt{0}$；
3. 对于任意两个整数 $i$ 和 $j$（$1 \leq i, j \leq k$），坐标 $(x_i, y_i)$ 可以通过一系列相邻的（共享一条边的）值为 $\texttt{0}$ 的单元格到达 $(x_j, y_j)$。

哥布林的任务是找出一个好的集合 $S$ 的最大可能大小。由于 TC 博士很慷慨，这次给了他两秒而不是一秒来找出答案。哥布林以不诚实著称，所以他请你帮他作弊。

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\texttt{1}$ 和 $\texttt{0}$ 组成的字符串。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 10^3$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——二进制字符串 $s$ 的长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串 $s$。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个数字，表示网格中好的单元格集合的最大可能大小。


## 说明/提示

在第一个示例中，网格如下：

```
1 0 0
0 1 0
0 0 1
```

由单元格 $(1, 2)$ 和 $(1, 3)$ 组成的集合是好的。由单元格 $(1, 1)$ 和 $(1, 2)$ 组成的集合不是好的，因为单元格 $(1, 1)$ 的值不是 $\texttt{0}$。由单元格 $(1, 2)$、$(1, 3)$ 和 $(2, 3)$ 组成的集合是好的，且最大大小为 $3$。注意，由单元格 $(2, 1)$、$(3, 1)$ 和 $(3, 2)$ 组成的集合也是好的，最大大小同样为 $3$。

在第二个示例中，网格如下：

```
1 0 1 0
0 1 1 0
0 0 0 0
0 0 1 1
```

好的集合的最大可能大小为 $9$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3
000
4
0010
7
1011001
4
0001
2
11
1
0
```

### 输出

```
3
9
10
7
1
0
```



---

---
title: "Omg Graph"
layout: "post"
diff: 普及+/提高
pid: CF2117G
tag: ['图论', '并查集', '最短路']
---

# Omg Graph

## 题目描述

给定一个带权无向连通图，定义一条长度为 $k$ 路径的费用如下：

- 设路径经过边的权值为 $w_1,w_2,\dots,w_k$。
- 路径的费用定义为 $(\min_{i=1}^k w_i) + (\max_{i=1}^k w_i)$，也就是最大的边权加上最小的边权。

请求出所有从结点 $1$ 到结点 $n$ 的路径中最小的费用。注意路径未必是简单路径。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含两个整数 $n$ 和 $m$（$2 \le n \le 2 \cdot 10^5$，$n-1 \le m \le \min\left(2 \cdot 10^5, \frac{n(n-1)}{2}\right)$）。
- 接下来的 $m$ 行中每行包含三个整数 $u$，$v$ 和 $w$（$1 \le u, v \le n$，$1 \le w \le 10^9$），表示一条从结点 $u$ 连接到结点 $v$，权值为 $w$ 的无向边。输入数据保证这些边组成一个连通图，且图中不含自环或重边。

输入数据保证所有测试用例的 $n$ 和 $m$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，代表从结点 $1$ 到结点 $n$ 的最小费用。

## 说明/提示

对于第二个测试用例，最优路径之一是 $1 \rightarrow 2 \rightarrow 1 \rightarrow 3$。经过的边权分别为 $5,5,13$，因此费用为 $\min(5,5,13)+\max(5,5,13)=18$。可以证明不存在费用更低的路径。

## 样例 #1

### 输入

```
4
3 2
1 2 1
2 3 1
3 2
1 3 13
1 2 5
8 9
1 2 6
2 3 5
3 8 6
1 4 7
4 5 4
5 8 7
1 6 5
6 7 5
7 8 5
3 3
1 3 9
1 2 8
2 3 3
```

### 输出

```
2
18
10
11
```



---

---
title: "Knight Tournament"
layout: "post"
diff: 普及+/提高
pid: CF356A
tag: ['搜索', '并查集', '枚举']
---

# Knight Tournament

## 题目描述

（题目大意）：有n个骑士，他们每个人都被从1-n进行编号，他们现在需要进行一次比赛，且总共会进行m场比赛。每场比赛会在编号在Li-Ri这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为Xi，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 输入格式

第一行为两个整数n，m。代表有n个骑士参加m场比赛；

之后的m行，每行3个整数Li，Ri，Xi，代表第i场比赛在编号在Li-Ri之间的骑士举行，胜利者的编号为Xi。

保证输入数据正确，保证至少有两名骑士参加每一场战斗；

## 输出格式

输出只有一行，包括n个整数，第i个数代表第i个骑士被编号为第i个数的骑士打败，特别的，如果第i个骑士是最后的胜者，输出0；

## 样例 #1

### 输入

```
4 3
1 2 1
1 3 3
1 4 4

```

### 输出

```
3 1 4 0 
```

## 样例 #2

### 输入

```
8 4
3 5 4
3 7 6
2 8 8
1 8 1

```

### 输出

```
0 8 4 6 4 8 6 1 
```



---

---
title: "Two Sets"
layout: "post"
diff: 普及+/提高
pid: CF468B
tag: ['贪心', '并查集', '2-SAT']
---

# Two Sets

## 题目描述

> 给出 $n$ 个各不相同的数字，将它们分别放入 $A$ 和 $B$ 两个集合中，使它们满足：
> * 若数字 $x$ 在集合 $A$ 中，那么数字 $a-x$ 也在集合 $A$ 中；
> * 若数字 $x$ 在集合 $B$ 中，那么数字 $b-x$ 也在集合 $B$ 中。

## 输入格式

> 
> 输入的第一行输入三个整数 $n,a,b (1 \leq n \leq 10^{5} ; 1 \leq a,b \leq 10^{9} )$。
> 
> 输入的第二行有 $n$ 个各不相同的正整数，且每个正整数的数值大小都在 $[1,10^{9}]$ 内。

## 输出格式

> 
> 若不能能将这 $n$ 个数在满足条件的情况下全部放入 $A$ 和 $B$ 这两个集合中，则输出 `NO` 。
>
> 若这 $n$ 个数在满足条件的情况下能被全部放入 $A$ 和 $B$ 这两个集合中，则第一行输出 `YES` ，第二行输出 $n$ 个数 $0$ 或 $1$ ，第 $i$ 个数为 $0$ 表示第 $i$ 个数在集合 $A$ 中，第 $i$ 个数为 $1$ 表示第 $i$ 个数在集合 $B$ 中。

## 样例 #1

### 输入

```
4 5 9
2 3 4 5

```

### 输出

```
YES
0 0 1 1

```

## 样例 #2

### 输入

```
3 3 4
1 2 4

```

### 输出

```
NO

```



---

---
title: "Anton and Tree"
layout: "post"
diff: 普及+/提高
pid: CF734E
tag: ['并查集', '强连通分量', '树的直径']
---

# Anton and Tree

## 题目描述

Anton is growing a tree in his garden. In case you forgot, the tree is a connected acyclic undirected graph.

There are $ n $ vertices in the tree, each of them is painted black or white. Anton doesn't like multicolored trees, so he wants to change the tree such that all vertices have the same color (black or white).

To change the colors Anton can use only operations of one type. We denote it as $ paint(v) $ , where $ v $ is some vertex of the tree. This operation changes the color of all vertices $ u $ such that all vertices on the shortest path from $ v $ to $ u $ have the same color (including $ v $ and $ u $ ). For example, consider the tree

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)and apply operation $ paint(3) $ to get the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/eabfeb953964c829d6d1820bd3bcad690b9ae826.png)Anton is interested in the minimum number of operation he needs to perform in order to make the colors of all vertices equal.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ color_{i} $ ( $ 0<=color_{i}<=1 $ ) — colors of the vertices. $ color_{i}=0 $ means that the $ i $ -th vertex is initially painted white, while $ color_{i}=1 $ means it's initially painted black.

Then follow $ n-1 $ line, each of them contains a pair of integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i} $ ) — indices of vertices connected by the corresponding edge. It's guaranteed that all pairs $ (u_{i},v_{i}) $ are distinct, i.e. there are no multiple edges.

## 输出格式

Print one integer — the minimum number of operations Anton has to apply in order to make all vertices of the tree black or all vertices of the tree white.

## 说明/提示

In the first sample, the tree is the same as on the picture. If we first apply operation $ paint(3) $ and then apply $ paint(6) $ , the tree will become completely black, so the answer is $ 2 $ .

In the second sample, the tree is already white, so there is no need to apply any operations and the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 0 0 0
1 2
2 3
3 4

```

### 输出

```
0

```



---

---
title: "String Reconstruction"
layout: "post"
diff: 普及+/提高
pid: CF827A
tag: ['模拟', '字符串', '并查集']
---

# String Reconstruction

## 题目描述

Ivan有一个只包含小写英文字母的字符串s。然而他的朋友Julia为了捉弄他藏起了字符串s。

相比起找回原来的字符串，Ivan更倾向于造一个新的。

 

Ivan知道一些有关于字符串s的信息。这意味着他记得字符串$t_{i}$在字符串s中至少出现了$k_{i}$次，以及$k_{i}$个$t_{i}$在s中出现的位置--$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$。他记得n个这样的字符串$t_{i}$。



 你要重建出一个符合Ivan记得的所有信息的字符串，如果有多个答案符合要求，取字典序最小的一个。字符串$t_{i}$只包含小写字母。

## 输入格式

第一行包括一个整数n(1<=n<=$10^{5}$),代表了Ivan所记得的字符串数量。



下面的n行包括有关于这些字符串的信息。第i+1包括一个非空字符串$t_{i}$，一个正整数$k_{i}$(代表了$t_{i}$在字符串s中出现的次数)，然后是$k_{i}$个正整数$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$（升序输入），代表了$t_{i}$在字符串s中出现的起始位置。



保证字符串$t_{i}$的长度之和不超过$10^{6}$，1<=$x_{i,j}$<=$10^{6}$，1<=$k_{i}$<=$10^{6}$，且$k_{i}$的和不超过$10^{6}$。可能存在相同的$t_{i}$。



数据保证一定有解。

## 输出格式

输出满足条件的字典序最小的字符串。

## 样例 #1

### 输入

```
3
a 4 1 3 5 7
ab 2 1 5
ca 1 4

```

### 输出

```
abacaba

```

## 样例 #2

### 输入

```
1
a 1 3

```

### 输出

```
aaa

```

## 样例 #3

### 输入

```
3
ab 1 1
aba 1 3
ab 2 3 5

```

### 输出

```
ababab

```



---

