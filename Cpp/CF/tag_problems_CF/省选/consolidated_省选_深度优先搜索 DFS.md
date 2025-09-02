---
title: "Crime Management"
layout: "post"
diff: 省选/NOI-
pid: CF107D
tag: ['字符串', '深度优先搜索 DFS', '概率论']
---

# Crime Management

## 题目描述

Zeyad 想要在埃及犯下 $n$ 起罪行，并且不受惩罚。罪行有几种类型。例如，贿赂是一种罪行，但如果重复两次，它就不被视为犯罪。因此，贿赂在重复偶数次时不被视为犯罪。超速也是一种罪行，但如果其重复的次数是 5 的倍数，它也不被视为犯罪。

更具体地说，已知有 $c$ 条关于罪行重复的条件。每个条件描述了罪行的类型 $t_{i}$ 及其重复的次数限制 $m_{i}$ 。如果 Zeyad 犯下的罪行 $t_{i}$ 的次数是 $m_{i}$ 的倍数，则 Zeyad 不会因为该罪行而受到惩罚。如果某种罪行出现多次，满足其中任意一个条件即可不受惩罚。当然，如果某罪行的次数为零，Zeyad 对该罪行无罪。

现在，Zeyad 想知道有多少种方式可以精确犯下 $n$ 起罪行且不受惩罚。

罪行的顺序是重要的。更正式地说，犯下 $n$ 起罪行的两种方式（序列 $w1$ 和 $w2$ ）如果对所有 $1 \leq i \leq n$ ，$w1_{i} = w2_{i}$ ，那么它们是相同的方式。

## 输入格式

第一行包含两个整数 $n$ 和 $c$ ($0 \leq n \leq 10^{18}, 0 \leq c \leq 1000$) —— Zeyad 想要犯下的罪行数量和他知道的条件数量。

接下来是 $c$ 条条件的定义。有 $26$ 种类型的罪行。每个罪行的定义由罪行类型（一个大写拉丁字母）和其重复次数的限制组成。

每个罪行的重复次数限制是一个正整数，并且所有限制的乘积不超过 $123$ 。输入中可能有重复的条件。

若某罪行的重复次数限制为 $1$ ，无论犯多少次都不会受到惩罚。法律的严格性由其非强制性来弥补。

显然，如果某罪行未在条件集中列出，那么 Zeyad 不会考虑它，因为犯下它不可避免地会受到惩罚。

请不要在 C++ 中使用 %lld 格式符来读写 64 位整数，建议使用 cin 流（你也可以使用 %I64d 格式符）。

## 输出格式

输出精确犯下 $n$ 起罪行且不受惩罚的不同方式数量，结果对 $12345$ 取模。

## 说明/提示

在第一个测试用例中，16 种方式是：AAAAA，AAABB，AABAB，AABBA，ABAAB，ABABA，ABBAA，BAAAB，BAABA，BABAA，BBAAA，ABBBB，BABBB，BBABB，BBBAB，BBBBA。

## 样例 #1

### 输入

```
5 2
A 1
B 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
6 3
A 1
B 2
C 3

```

### 输出

```
113

```

## 样例 #3

### 输入

```
8 3
A 2
A 3
B 2

```

### 输出

```
128

```



---

---
title: "Unordered Swaps"
layout: "post"
diff: 省选/NOI-
pid: CF1682E
tag: ['深度优先搜索 DFS']
---

# Unordered Swaps

## 题目描述

Alice had a permutation $ p $ of numbers from $ 1 $ to $ n $ . Alice can swap a pair $ (x, y) $ which means swapping elements at positions $ x $ and $ y $ in $ p $ (i.e. swap $ p_x $ and $ p_y $ ). Alice recently learned her first sorting algorithm, so she decided to sort her permutation in the minimum number of swaps possible. She wrote down all the swaps in the order in which she performed them to sort the permutation on a piece of paper.

For example,

- $ [(2, 3), (1, 3)] $ is a valid swap sequence by Alice for permutation $ p = [3, 1, 2] $ whereas $ [(1, 3), (2, 3)] $ is not because it doesn't sort the permutation. Note that we cannot sort the permutation in less than $ 2 $ swaps.
- $ [(1, 2), (2, 3), (2, 4), (2, 3)] $ cannot be a sequence of swaps by Alice for $ p = [2, 1, 4, 3] $ even if it sorts the permutation because $ p $ can be sorted in $ 2 $ swaps, for example using the sequence $ [(4, 3), (1, 2)] $ .

Unfortunately, Bob shuffled the sequence of swaps written by Alice.

You are given Alice's permutation $ p $ and the swaps performed by Alice in arbitrary order. Can you restore the correct sequence of swaps that sorts the permutation $ p $ ? Since Alice wrote correct swaps before Bob shuffled them up, it is guaranteed that there exists some order of swaps that sorts the permutation.

## 输入格式

The first line contains $ 2 $ integers $ n $ and $ m $ $ (2 \le n \le 2 \cdot 10^5, 1 \le m \le n - 1) $ — the size of permutation and the minimum number of swaps required to sort the permutation.

The next line contains $ n $ integers $ p_1, p_2, ..., p_n $ ( $ 1 \le p_i \le n $ , all $ p_i $ are distinct) — the elements of $ p $ . It is guaranteed that $ p $ forms a permutation.

Then $ m $ lines follow. The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ — the $ i $ -th swap $ (x_i, y_i) $ .

It is guaranteed that it is possible to sort $ p $ with these $ m $ swaps and that there is no way to sort $ p $ with less than $ m $ swaps.

## 输出格式

Print a permutation of $ m $ integers — a valid order of swaps written by Alice that sorts the permutation $ p $ . See sample explanation for better understanding.

In case of multiple possible answers, output any.

## 说明/提示

In the first example, $ p = [2, 3, 4, 1] $ , $ m = 3 $ and given swaps are $ [(1, 4), (2, 1), (1, 3)] $ .

There is only one correct order of swaps i.e $ [2, 3, 1] $ .

1. First we perform the swap $ 2 $ from the input i.e $ (2, 1) $ , $ p $ becomes $ [3, 2, 4, 1] $ .
2. Then we perform the swap $ 3 $ from the input i.e $ (1, 3) $ , $ p $ becomes $ [4, 2, 3, 1] $ .
3. Finally we perform the swap $ 1 $ from the input i.e $ (1, 4) $ and $ p $ becomes $ [1, 2, 3, 4] $ which is sorted.

In the second example, $ p = [6, 5, 1, 3, 2, 4] $ , $ m = 4 $ and the given swaps are $ [(3, 1), (2, 5), (6, 3), (6, 4)] $ .

One possible correct order of swaps is $ [4, 2, 1, 3] $ .

1. Perform the swap $ 4 $ from the input i.e $ (6, 4) $ , $ p $ becomes $ [6, 5, 1, 4, 2, 3] $ .
2. Perform the swap $ 2 $ from the input i.e $ (2, 5) $ , $ p $ becomes $ [6, 2, 1, 4, 5, 3] $ .
3. Perform the swap $ 1 $ from the input i.e $ (3, 1) $ , $ p $ becomes $ [1, 2, 6, 4, 5, 3] $ .
4. Perform the swap $ 3 $ from the input i.e $ (6, 3) $ and $ p $ becomes $ [1, 2, 3, 4, 5, 6] $ which is sorted.

There can be other possible answers such as $ [1, 2, 4, 3] $ .

## 样例 #1

### 输入

```
4 3
2 3 4 1
1 4
2 1
1 3
```

### 输出

```
2 3 1
```

## 样例 #2

### 输入

```
6 4
6 5 1 3 2 4
3 1
2 5
6 3
6 4
```

### 输出

```
4 1 3 2
```



---

---
title: "Preorder Test"
layout: "post"
diff: 省选/NOI-
pid: CF627D
tag: ['二分', '深度优先搜索 DFS']
---

# Preorder Test

## 题目描述

For his computer science class, Jacob builds a model tree with sticks and balls containing $ n $ nodes in the shape of a tree. Jacob has spent $ a_{i} $ minutes building the $ i $ -th ball in the tree.

Jacob's teacher will evaluate his model and grade Jacob based on the effort he has put in. However, she does not have enough time to search his whole tree to determine this; Jacob knows that she will examine the first $ k $ nodes in a DFS-order traversal of the tree. She will then assign Jacob a grade equal to the minimum $ a_{i} $ she finds among those $ k $ nodes.

Though Jacob does not have enough time to rebuild his model, he can choose the root node that his teacher starts from. Furthermore, he can rearrange the list of neighbors of each node in any order he likes. Help Jacob find the best grade he can get on this assignment.

A DFS-order traversal is an ordering of the nodes of a rooted tree, built by a recursive DFS-procedure initially called on the root of the tree. When called on a given node $ v $ , the procedure does the following:

1. Print $ v $ .
2. Traverse the list of neighbors of the node $ v $ in order and iteratively call DFS-procedure on each one. Do not call DFS-procedure on node $ u $ if you came to node $ v $ directly from $ u $ .

## 输入格式

The first line of the input contains two positive integers, $ n $ and $ k $ ( $ 2<=n<=200000 $ , $ 1<=k<=n $ ) — the number of balls in Jacob's tree and the number of balls the teacher will inspect.

The second line contains $ n $ integers, $ a_{i} $ ( $ 1<=a_{i}<=1000000 $ ), the time Jacob used to build the $ i $ -th ball.

Each of the next $ n-1 $ lines contains two integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ u_{i}≠v_{i} $ ) representing a connection in Jacob's tree between balls $ u_{i} $ and $ v_{i} $ .

## 输出格式

Print a single integer — the maximum grade Jacob can get by picking the right root of the tree and rearranging the list of neighbors.

## 说明/提示

In the first sample, Jacob can root the tree at node $ 2 $ and order $ 2 $ 's neighbors in the order $ 4 $ , $ 1 $ , $ 5 $ (all other nodes have at most two neighbors). The resulting preorder traversal is $ 2 $ , $ 4 $ , $ 1 $ , $ 3 $ , $ 5 $ , and the minimum $ a_{i} $ of the first $ 3 $ nodes is $ 3 $ .

In the second sample, it is clear that any preorder traversal will contain node $ 1 $ as either its first or second node, so Jacob cannot do better than a grade of $ 1 $ .

## 样例 #1

### 输入

```
5 3
3 6 1 4 2
1 2
2 4
2 5
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 2
1 5 5 5
1 2
1 3
1 4

```

### 输出

```
1

```



---

---
title: "The Chocolate Spree"
layout: "post"
diff: 省选/NOI-
pid: CF633F
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS']
---

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 输入格式

The first line of the input contains the single integer $ n $ ( $ 2<= $ n $ <=100000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ), $ i $ -th of these numbers stands for the number of chocolates stored at the node $ i $ .

Then follow $ n-1 $ lines that describe the tree. Each of them contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — indices of vertices connected by the $ i $ -th edge.

## 输出格式

Print the number of chocolates Alice and Bob can collect together if they behave optimally.

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9

```

### 输出

```
25

```

## 样例 #2

### 输入

```
2
20 10
1 2

```

### 输出

```
30

```



---

---
title: "Best Edge Weight"
layout: "post"
diff: 省选/NOI-
pid: CF827D
tag: ['深度优先搜索 DFS', '生成树', '动态树 LCT']
---

# Best Edge Weight

## 题目描述

You are given a connected weighted graph with $ n $ vertices and $ m $ edges. The graph doesn't contain loops nor multiple edges. Consider some edge with id $ i $ . Let's determine for this edge the maximum integer weight we can give to it so that it is contained in all minimum spanning trees of the graph if we don't change the other weights.

You are to determine this maximum weight described above for each edge. You should calculate the answer for each edge independently, it means there can't be two edges with changed weights at the same time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ), where $ n $ and $ m $ are the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines contains three integers $ u $ , $ v $ and $ c $ ( $ 1<=v,u<=n $ , $ v≠u $ , $ 1<=c<=10^{9} $ ) meaning that there is an edge between vertices $ u $ and $ v $ with weight $ c $ .

## 输出格式

Print the answer for each edge in the order the edges are given in the input. If an edge is contained in every minimum spanning tree with any weight, print -1 as the answer.

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 2
3 4 2
4 1 3

```

### 输出

```
2 2 2 1 
```

## 样例 #2

### 输入

```
4 3
1 2 2
2 3 2
3 4 2

```

### 输出

```
-1 -1 -1 
```



---

---
title: "Xor-MST"
layout: "post"
diff: 省选/NOI-
pid: CF888G
tag: ['深度优先搜索 DFS', '生成树', '进制']
---

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
8

```



---

---
title: "NN country"
layout: "post"
diff: 省选/NOI-
pid: CF983E
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ means that cities $ p_i $ and $ i $ are connected by road.

The third line contains a single integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of bus routes.

Each of the next $ m $ lines contains $ 2 $ integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ , $ a \neq b $ ), meaning that there is a bus route between cities $ a $ and $ b $ . It is possible that there is more than one route between two cities.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of questions you are interested in.

Each of the next $ q $ lines contains $ 2 $ integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ), meaning that you are interested if it is possible to get from city $ v $ to city $ u $ and what is the minimum number of buses you need to use for it.

## 输出格式

Print the answer for each question on a separate line. If there is no way to get from one city to another, print $ -1 $ . Otherwise print the minimum number of buses you have to use.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3

```

### 输出

```
1
3
-1
1
2
3

```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3

```

### 输出

```
1
-1
-1
1
-1
1

```



---

---
title: "AND Graph"
layout: "post"
diff: 省选/NOI-
pid: CF986C
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS', '位运算']
---

# AND Graph

## 题目描述

给定一个 $m$ 个整数的集合，每个整数在 $0$ 到 $2^n-1$ 之间，以每一个整数作为顶点建无向图，当两个点 $x$ 和 $y$ 做与运算值为 $0$ 时，则认为 $x$ 和 $y$ 是连通的，即 $x$ 和 $y$ 之间有一条无向边。请求出图中连通块的个数。

## 输入格式

第一行输入两个整数 $n$ 和 $m$（$0 \leq  n\leq22$，$1 \leq  m\leq2^n$）。  
第二行输入 $m$ 个整数，即集合里的元素。

## 输出格式

一个整数，表示图中连通块的个数。

## 样例 #1

### 输入

```
2 3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5
5 19 10 20 12

```

### 输出

```
2

```



---

