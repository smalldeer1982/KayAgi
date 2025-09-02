---
title: "Unique Occurrences"
layout: "post"
diff: 省选/NOI-
pid: CF1681F
tag: ['树形 DP', '动态树 LCT']
---

# Unique Occurrences

## 题目描述

You are given a tree, consisting of $ n $ vertices. Each edge has an integer value written on it.

Let $ f(v, u) $ be the number of values that appear exactly once on the edges of a simple path between vertices $ v $ and $ u $ .

Calculate the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ 1 \le v < u \le n $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^5 $ ) — the number of vertices in the tree.

Each of the next $ n-1 $ lines contains three integers $ v, u $ and $ x $ ( $ 1 \le v, u, x \le n $ ) — the description of an edge: the vertices it connects and the value written on it.

The given edges form a tree.

## 输出格式

Print a single integer — the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ v < u $ .

## 样例 #1

### 输入

```
3
1 2 1
1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 2 2
1 3 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 4 4
1 2 3
3 4 4
4 5 5
```

### 输出

```
14
```

## 样例 #4

### 输入

```
2
2 1 1
```

### 输出

```
1
```

## 样例 #5

### 输入

```
10
10 2 3
3 8 8
4 8 9
5 8 5
3 10 7
7 8 2
5 6 6
9 3 4
1 6 3
```

### 输出

```
120
```



---

---
title: "Clearing the Snowdrift"
layout: "post"
diff: 省选/NOI-
pid: CF2097E
tag: ['动态树 LCT', '线段树合并']
---

# Clearing the Snowdrift

## 题目描述

男孩 Vasya 非常喜欢旅行。特别是乘坐飞机旅行给他带来了极大的快乐。他正要飞往另一个城市，但跑道被厚厚的积雪覆盖，需要清理。

跑道可以表示为编号从 $1$ 到 $n$ 的 $n$ 个连续区域。暴风雪相当猛烈，但现在已经停止，因此 Vasya 计算出第 $i$ 个区域覆盖了 $a_i$ 米厚的积雪。针对这种情况，机场有一台工作方式相当特殊的扫雪机。每分钟，扫雪机可以执行以下操作：

- 选择一个长度不超过 $d$ 的连续区段，并从积雪最多的区域中移除一米积雪。具体来说，可以选择 $1 \le l \le r \le n$（$r - l + 1 \le d$）。然后计算 $c = \max \{ a_l, a_{l + 1}, \ldots , a_r \}$，如果 $c > 0$，则对于所有满足 $a_i = c$ 的 $i \colon l \le i \le r$，将 $a_i$ 的值减一。

Vasya 为这次飞行准备了很长时间，他想知道自己还需要等待多少时间才能让所有区域完全清除积雪。换句话说，需要计算扫雪机将所有区域的积雪清除（即对所有 $i$ 从 $1$ 到 $n$ 满足 $a_i = 0$）所需的最少分钟数。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 2 \cdot 10^5$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $d$（$1 \le n \le 5 \cdot 10^5, 1 \le d \le n$）——跑道的区域数量和扫雪机可以选择的区段的最大长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$），其中 $a_i$ 表示第 $i$ 个区域的积雪厚度。

保证所有测试用例的 $n$ 之和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——扫雪机将所有区域的积雪清除所需的最少分钟数。

## 说明/提示

在第一个测试用例中，存在一个最优的操作序列。首先，选择区段 $[2, 3]$ 四次。经过三次操作后，$a_2$ 将变为 $2$，数组 $a$ 将变为 $[1, 2, 2, 1, 2]$。第四次操作后，数组 $a$ 将变为 $[1, 1, 1, 1, 2]$。接下来，可以通过依次选择区段 $[1, 2]$、$[3, 3]$、$[5, 5]$ 和 $[4, 5]$ 将数组清零。

在第二个测试用例中，$d = 1$，这意味着每个区域需要独立清除，答案等于所有 $a_i$ 的总和。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 2
1 5 2 1 2
3 1
1000000000 1000000000 1000000000
```

### 输出

```
8
3000000000
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

