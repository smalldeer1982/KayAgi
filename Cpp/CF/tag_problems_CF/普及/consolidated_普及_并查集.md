---
title: "Cthulhu"
layout: "post"
diff: 普及/提高-
pid: CF103B
tag: ['模拟', '并查集', '构造']
---

# Cthulhu

## 题目描述

...Once upon a time a man came to the sea. The sea was stormy and dark. The man started to call for the little mermaid to appear but alas, he only woke up Cthulhu...

Whereas on the other end of the world Pentagon is actively collecting information trying to predict the monster's behavior and preparing the secret super weapon. Due to high seismic activity and poor weather conditions the satellites haven't yet been able to make clear shots of the monster. The analysis of the first shot resulted in an undirected graph with $ n $ vertices and $ m $ edges. Now the world's best minds are about to determine whether this graph can be regarded as Cthulhu or not.

To add simplicity, let's suppose that Cthulhu looks from the space like some spherical body with tentacles attached to it. Formally, we shall regard as Cthulhu such an undirected graph that can be represented as a set of three or more rooted trees, whose roots are connected by a simple cycle.

It is guaranteed that the graph contains no multiple edges and self-loops.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF103B/33dc55a8762ea9a08fee5a98be66bd3670ec0fbb.png)

## 输入格式

The first line contains two integers — the number of vertices $ n $ and the number of edges $ m $ of the graph ($1 \le n \le 100$, $0 \le m \le \frac{n(n-1)}{2}$).

Each of the following $ m $ lines contains a pair of integers $ x $ and $ y $, that show that an edge exists between vertices $ x $ and $ y $ ($1 \le x, y \le n, x \ne y$). For each pair of vertices there will be at most one edge between them, no edge connects a vertex to itself.

## 输出格式

Print "NO", if the graph is not Cthulhu and "FHTAGN!" if it is.

## 说明/提示

Let us denote as a simple cycle a set of $ v $ vertices that can be numbered so that the edges will only exist between vertices number $ 1 $ and $ 2 $ , $ 2 $ and $ 3 $ , ..., $ v-1 $ and $ v $ , $ v $ and $ 1 $ .

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges ( $ n&gt;0 $ ).

A rooted tree is a tree where one vertex is selected to be the root.

## 样例 #1

### 输入

```
6 6
6 3
6 4
5 1
2 5
1 4
5 4

```

### 输出

```
FHTAGN!
```

## 样例 #2

### 输入

```
6 5
5 6
4 6
3 1
5 1
1 2

```

### 输出

```
NO
```



---

---
title: "pSort"
layout: "post"
diff: 普及/提高-
pid: CF28B
tag: ['图论', '并查集']
---

# pSort

## 题目描述

给定一个长度为 $n$ 的数列 $\{a_n\}$，初始时 $\{a_n\} = \{1, 2, \dots, n\}$。位置 $i$ 上的数可以和位置 $i \pm d_i$ 上的数交换。给定一个 $1 \sim n$ 的全排列，问初始的数列可否交换成给定的形式。

## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个互不相同的整数表示目标数列。

第三行 $n$ 个整数表示 $d_1, d_2, \dots, d_n$。

## 输出格式

如果能交换到给定样式，输出 `YES`，否则输出 `NO`。

## 说明/提示

$1 \le n \le 100$

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 1 1 1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
7
4 3 5 1 2 7 6
4 6 6 1 6 6 1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7
4 2 5 1 3 7 6
4 6 6 1 6 6 1

```

### 输出

```
YES

```



---

---
title: "Vessels"
layout: "post"
diff: 普及/提高-
pid: CF371D
tag: ['并查集', '链表']
---

# Vessels

## 题目描述

There is a system of $ n $ vessels arranged one above the other as shown in the figure below. Assume that the vessels are numbered from 1 to $ n $ , in the order from the highest to the lowest, the volume of the $ i $ -th vessel is $ a_{i} $ liters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371D/f198564e53bb2ea5c99e17b823930a432879118f.png)Initially, all the vessels are empty. In some vessels water is poured. All the water that overflows from the $ i $ -th vessel goes to the $ (i+1) $ -th one. The liquid that overflows from the $ n $ -th vessel spills on the floor.

Your task is to simulate pouring water into the vessels. To do this, you will need to handle two types of queries:

1. Add $ x_{i} $ liters of water to the $ p_{i} $ -th vessel;
2. Print the number of liters of water in the $ k_{i} $ -th vessel.

When you reply to the second request you can assume that all the water poured up to this point, has already overflown between the vessels.

## 输入格式

The first line contains integer $ n $ — the number of vessels ( $ 1<=n<=2·10^{5} $ ). The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ — the vessels' capacities ( $ 1<=a_{i}<=10^{9} $ ). The vessels' capacities do not necessarily increase from the top vessels to the bottom ones (see the second sample). The third line contains integer $ m $ — the number of queries ( $ 1<=m<=2·10^{5} $ ). Each of the next $ m $ lines contains the description of one query. The query of the first type is represented as " $ 1 p_{i} x_{i} $ ", the query of the second type is represented as " $ 2 k_{i} $ " ( $ 1<=p_{i}<=n $ , $ 1<=x_{i}<=10^{9} $ , $ 1<=k_{i}<=n $ ).

## 输出格式

For each query, print on a single line the number of liters of water in the corresponding vessel.

## 样例 #1

### 输入

```
2
5 10
6
1 1 4
2 1
1 2 5
1 1 4
2 1
2 2

```

### 输出

```
4
5
8

```

## 样例 #2

### 输入

```
3
5 10 8
6
1 1 12
2 2
1 1 6
1 3 2
2 2
2 3

```

### 输出

```
7
10
5

```



---

---
title: "Destroying Array"
layout: "post"
diff: 普及/提高-
pid: CF722C
tag: ['线段树', '并查集']
---

# Destroying Array

## 题目描述

给你一个由 $n$ 个非负整数组成的数列 $a_1$，$a_2$，$\cdots$，$a_n$。

你将要一个一个摧毁这个数列中的数。并且，现在给你一个由 $1$ 到 $n$ 组成的序列来告诉你每个数被摧毁的时间顺序。

每当一个元素被摧毁时，你需要找到这个当前数列中的未被摧毁的数组成的和最大的连续子序列，另外，如果当前剩余的序列是空的的话，最大和就是 $0$。

## 输入格式

第一行包含一个整数 $n (1\le n\le 100000)$ , 代表数列的长度。

第二行包含 $n$ 个整数 $a_1$，$a_2$，$\cdots$，$a_n$ $(0\le a_i\le 10^9)$。

第三行包含一个由 $1$ 到 $n$ 的整数组成的序列，代表数被摧毁的顺序。

## 输出格式

输出有 $n$ 行，第 $i$ 行包含一个整数 —— 在第 $i$ 个操作已经执行完之后，数列中连续的最大和。

## 说明/提示

第一个样例：

1.第三个数被删除了，现在的数列是 1 3 x 5 ，5由一个数5组成。

2.第四个数被删除了，现在的数列是 1 3 x x ，4由两个数1和3组成。

3.第一个数被删除了，现在的数列是 x 3 x x ，3由一个数3组成。

4.最后一个剩下的数被删除了，现在的数列中没有东西啦，所以答案是0呢！


感谢 @FangHaosb 提供的翻译

## 样例 #1

### 输入

```
4
1 3 2 5
3 4 1 2

```

### 输出

```
5
4
3
0

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4 2 3 5 1

```

### 输出

```
6
5
5
1
0

```

## 样例 #3

### 输入

```
8
5 5 4 4 6 6 5 5
5 2 8 7 1 3 4 6

```

### 输出

```
18
16
11
8
8
6
6
0

```



---

---
title: "Arpa's weak amphitheater and Mehrdad's valuable"
layout: "post"
diff: 普及/提高-
pid: CF741B
tag: ['并查集', '背包 DP']
---

# Arpa's weak amphitheater and Mehrdad's valuable

## 题目描述

有 $n$ 个人 $(1\le n\le1000)$。每个人有一个重量 $w_i(1\le w_i\le 1000)$ 和一个魅力值 $b_i(1\le b_i\le 10^6)$。 $n$ 个人之间有 $m(1\le m\le\min(\frac{n\times(n-1)}{2}, 10^5))$ 个关系。第 $i$ 个关系由两个数字 $x_i$ 和 $y_i$ 组成，表示第 $x_i$ 个人和第 $y_i$ 个人是朋友，朋友关系是双向的。

已知若 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友。 现在 Mehrdad 要邀请一些人来到派对，使这些人的重量总和不超过 $w\ (1\le w\le1000)$，且魅力值总和尽量大。同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请。

## 输入格式

第一行，三个整数 $n,m,w$

第二行，$n$ 个整数 $w_1,w_2,\cdots,w_n$

第三行，$n$ 个整数 $b_1,b_2,\cdots,b_n$

接下来 $m$ 行，每行表示一个关系，第 $i$ 行有两个整数 $x_i$ 和 $y_i$。每一组朋友关系都是不同的。

## 输出格式

一行，表示最大的魅力值总和。

## 样例 #1

### 输入

```
3 1 5
3 2 5
2 4 2
1 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 2 11
2 4 6 6
6 4 2 1
1 2
2 3

```

### 输出

```
7

```



---

