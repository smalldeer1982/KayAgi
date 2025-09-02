---
title: "Maximal Intersection"
layout: "post"
diff: 普及/提高-
pid: CF1029C
tag: ['贪心', '枚举', '优先队列']
---

# Maximal Intersection

## 题目描述

给定n个闭区间,现在要求从这些闭区间中删除一个区间，使得剩下的（n-1）个区间的交集的长度最大，求这个最大值。

（p.s.：若这个区间为空集或它的左端点与右端点重合，则长度为0；否则其长度为右端点在数轴上表示的数-左端点在数轴上表示的数）

## 输入格式

第一行输入一个正整数n（2<=n<=3e5）。

后面的n行中每行输入两个自然数l、r，表示一个闭区间[l,r]（0<=l<=r<=1e9）。

## 输出格式

输出一个数，表示这个最大值。

Translated by @lhy930

## 样例 #1

### 输入

```
4
1 3
2 6
0 4
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
2 6
1 3
0 4
1 20
0 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
4 5
1 2
9 20

```

### 输出

```
0

```

## 样例 #4

### 输入

```
2
3 10
1 5

```

### 输出

```
7

```



---

---
title: "Valid BFS?"
layout: "post"
diff: 普及/提高-
pid: CF1037D
tag: ['排序', '广度优先搜索 BFS', '队列']
---

# Valid BFS?

## 题目描述

The [BFS](https://en.wikipedia.org/wiki/Breadth-first_search) algorithm is defined as follows.

1. Consider an undirected graph with vertices numbered from $ 1 $ to $ n $ . Initialize $ q $ as a new [queue](http://gg.gg/queue_en) containing only vertex $ 1 $ , mark the vertex $ 1 $ as used.
2. Extract a vertex $ v $ from the head of the queue $ q $ .
3. Print the index of vertex $ v $ .
4. Iterate in arbitrary order through all such vertices $ u $ that $ u $ is a neighbor of $ v $ and is not marked yet as used. Mark the vertex $ u $ as used and insert it into the tail of the queue $ q $ .
5. If the queue is not empty, continue from step 2.
6. Otherwise finish.

Since the order of choosing neighbors of each vertex can vary, it turns out that there may be multiple sequences which BFS can print.

In this problem you need to check whether a given sequence corresponds to some valid BFS traversal of the given tree starting from vertex $ 1 $ . The [tree](http://gg.gg/tree_en) is an undirected graph, such that there is exactly one simple path between any two vertices.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) which denotes the number of nodes in the tree.

The following $ n - 1 $ lines describe the edges of the tree. Each of them contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ ) — the endpoints of the corresponding edge of the tree. It is guaranteed that the given graph is a tree.

The last line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the sequence to check.

## 输出格式

Print "Yes" (quotes for clarity) if the sequence corresponds to some valid BFS traversal of the given tree and "No" (quotes for clarity) otherwise.

You can print each letter in any case (upper or lower).

## 说明/提示

Both sample tests have the same tree in them.

In this tree, there are two valid BFS orderings:

- $ 1, 2, 3, 4 $ ,
- $ 1, 3, 2, 4 $ .

The ordering $ 1, 2, 4, 3 $ doesn't correspond to any valid BFS order.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 2 3 4

```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
1 2
1 3
2 4
1 2 4 3

```

### 输出

```
No
```



---

---
title: "Cinema Cashier"
layout: "post"
diff: 普及/提高-
pid: CF10B
tag: ['模拟', '树状数组', '队列']
---

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 输入格式

The first line contains two integers $ N $ and $ K $ ( $ 1<=N<=1000,1<=K<=99 $ ) — the amount of requests and the hall size respectively. The second line contains $ N $ space-separated integers $ M_{i} $ from the range $ [1,K] $ — requests to the program.

## 输出格式

Output $ N $ lines. In the $ i $ -th line output «-1» (without quotes), if it is impossible to find $ M_{i} $ successive seats in one row, otherwise output three numbers $ x,y_{l},y_{r} $ . Separate the numbers with a space.

## 样例 #1

### 输入

```
2 1
1 1

```

### 输出

```
1 1 1
-1

```

## 样例 #2

### 输入

```
4 3
1 2 3 1

```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1

```



---

---
title: "Fighting Tournament"
layout: "post"
diff: 普及/提高-
pid: CF1719C
tag: ['队列']
---

# Fighting Tournament

## 题目描述

## 题意 

Burenka正准备去观看一年中最有趣的体育活动 —— 她朋友Tonya组织的格斗锦标赛。

有 **n** 名运动员参加了大赛，标号分别为为 1，2，... ，n 。第 **i** 名运动员的实力是 **$a_i（1 \le a_i \le n）$** 。**每个运动员的实力是不同的，也就是说，数组 a 是 n 的 一种 全排列** 。

大赛的流程是这样的：

一开始，运动员们**按标号从小到大**排成一列，队头为 **1** 号运动员，队尾为 **n** 号运动员。

每轮一次比赛，**队头**的两个人进行格斗，**赢的人（实力较强的人）变成队头，输的人变成队尾** 。

Burenka 问了 Tonya **q** 个问题，每个问题包含两个整数 **i** 和 **k** ，表示 **i 号运动员在前 k 轮中会胜多少场**。

## 输入格式

第一行一个整数 **t** $(1\le t\le 10^4)$，表示数据组数。

对于每组数据：

第一行两个整数 **n** 和 **q** $(2\le n \le 10^5,1\le q\le 10^5)$，表示 参加大赛的运动员数量 和 问题数量。

第二行 **n** 个整数 **$a_1,a_2,...,a_n(1\le a_i\le n)$**，表示数组 **a**，而且是个 **全排列**。

接下来的 **q** 行表示每个问题，每行两个整数 **i** 和 **k** $(1\le i\le n,1\le k\le 10^9)$，表示**运动员的标号** 和 **轮数**。

## 输出格式

对于每个问题，一行一个整数表示 **问题的答案**。

## 样例 #1

### 输入

```
3
3 1
3 1 2
1 2
4 2
1 3 4 2
4 5
3 2
5 2
1 2 3 5 4
5 1000000000
4 6
```

### 输出

```
2
0
1
0
4
```



---

---
title: "Action Figures"
layout: "post"
diff: 普及/提高-
pid: CF2026C
tag: ['贪心', '队列']
---

# Action Figures

## 题目描述

在 Monocarp 家附近有一家商店，专门售卖手办。近期，这家店将推出一套新的手办系列，总共包含 $n$ 个手办。其中，第 $i$ 个手办的价格为 $i$ 枚金币。在第 $i$ 天到第 $n$ 天之间，这个手办都是可以购买的。

Monocarp 知道他在这 $n$ 天中的哪几天可以去商店。

每次去商店的时候，他可以购买多件手办（当然，不能买尚未发售的手办）。如果他在同一天购买了至少两个手办，他可以享受一个折扣：他所购买的最贵手办是免费的，也就是说他无需为该手办支付费用。

Monocarp 的目标是从这个手办系列中，分别购买一个第 $1$ 个手办、一个第 $2$ 个手办……一直到一个第 $n$ 个手办。注意，每个手办只能购买一次。请你帮他计算，他最少需要花费多少金币？

## 输入格式

第一行输入一个整数 $t$，表示有多少个测试用例（$1 \le t \le 10^4$）。

每个测试用例包含两行：

- 第一行是一个整数 $n$，表示手办的数量（也是销售天数）（$1 \le n \le 4 \cdot 10^5$）；
- 第二行是一个长度为 $n$ 的字符串 $s$。如果在第 $i$ 天 Monocarp 可以去商店，$s_i$ 就为 1；否则为 0。

额外的限制条件有：

- 在每个测试用例中，字符串 $s$ 的最后一个字符 $s_n$ 一定是 1，所以 Monocarp 无论如何都能在最后一天买到所有手办。
- 所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$。

## 输出格式

对每个测试用例，输出一个整数，表示 Monocarp 最少需要花费的金币数。

## 说明/提示

在第一个测试用例中，Monocarp 可以在第一天购买第一个手办，花费 1 枚金币。

在第二个测试用例中，他可以在第三天购买第 1 和第 3 个手办，在第四天购买第 2 和第 4 个手办，在第六天购买第 5 和第 6 个手办。这样总费用为 $1+2+5=8$ 枚金币。

在第三个测试用例中，他可以在第三天购买第 2 和第 3 个手办，其余手办在第七天购买，最终花费 $1+2+4+5+6 = 18$ 枚金币。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
1
6
101101
7
1110001
5
11111
```

### 输出

```
1
8
18
6
```



---

---
title: "Sharky Surfing"
layout: "post"
diff: 普及/提高-
pid: CF2037D
tag: ['贪心', '堆', '优先队列']
---

# Sharky Surfing

## 题目描述

Mualani 喜欢在她的大鲨鱼冲浪板上冲浪！

Mualani 的冲浪路径可以用一个数轴来表示。她从位置 $1$ 开始，路径的终点是位置 $L$。当她处于位置 $x$ 且跳跃能力为 $k$ 时，她可以跳到区间 $[x, x+k]$ 内的任意整数位置。最初，她的跳跃能力为 $1$。

然而，她的冲浪路径并不完全平坦。她的路径上有 $n$ 个障碍物。每个障碍物由一个区间 $[l, r]$ 表示，意味着她不能跳到区间 $[l, r]$ 内的任何位置。

在路径上还有 $m$ 个能量提升点。第 $i$ 个能量提升点位于位置 $x_i$，其值为 $v_i$。当 Mualani 处于位置 $x_i$ 时，她可以选择收集该能量提升点，将她的跳跃能力增加 $v_i$。在同一个位置可能有多个能量提升点。当她处于有多个能量提升点的位置时，她可以选择收集或忽略每个单独的能量提升点。没有能量提升点位于任何障碍物的区间内。

Mualani 必须收集最少的能量提升点数才能到达位置 $L$ 完成冲浪路径。如果无法完成冲浪路径，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) — 测试用例的数量。

每个测试用例的第一行包含三个整数 $n$, $m$, 和 $L$ ($1 \leq n, m \leq 2 \cdot 10^5, 3 \leq L \leq 10^9$) — 障碍物的数量，能量提升点的数量，以及终点的位置。

接下来的 $n$ 行每行包含两个整数 $l_i$ 和 $r_i$ ($2 \leq l_i \leq r_i \leq L-1$) — 第 $i$ 个障碍物的区间边界。保证对于所有 $1 \leq i < n$，有 $r_i + 1 < l_{i+1}$（即所有障碍物都是非重叠的，按递增位置排序，并且前一个障碍物的终点与下一个障碍物的起点不连续）。

接下来的 $m$ 行每行包含两个整数 $x_i$ 和 $v_i$ ($1 \leq x_i, v_i \leq L$) — 第 $i$ 个能量提升点的位置和值。在所有测试用例中，能量提升点的数量总和不超过 $2 \cdot 10^5$。保证对于所有 $1 \leq i < m$，有 $x_i \leq x_{i+1}$（即能量提升点按非递减位置排序），并且没有能量提升点位于任何障碍物的区间内。

## 输出格式

对于每个测试用例，输出她必须收集的最少能量提升点数才能到达位置 $L$。如果无法完成，则输出 $-1$。

## 样例 #1

### 输入

```
4
2 5 50
7 14
30 40
2 2
3 1
3 5
18 2
22 32
4 3 50
4 6
15 18
20 26
34 38
1 2
8 2
10 2
1 4 17
10 14
1 6
1 2
1 2
16 9
1 2 10
5 9
2 3
2 2
```

### 输出

```
4
-1
1
2
```



---

---
title: "Chimpanzini Bananini"
layout: "post"
diff: 普及/提高-
pid: CF2094G
tag: ['队列']
---

# Chimpanzini Bananini

## 题目描述

Chimpanzini Bananini 正站在一场重大战斗的边缘——这场战斗注定会带来终结。

对于任意长度为 $m$ 的数组 $b$，我们定义该数组的"炫酷值"为 $\sum_{i=1}^m b_i \cdot i = b_1 \cdot 1 + b_2 \cdot 2 + b_3 \cdot 3 + \ldots + b_m \cdot m$。

Chimpanzini Bananini 给你一个空数组。你可以对它进行三种类型的操作：

1. 对数组进行循环移位。即数组 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_n, a_1, a_2, \ldots, a_{n-1}]$。
2. 反转整个数组。即数组 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_n, a_{n-1}, \ldots, a_1]$。
3. 在数组末尾追加一个元素。即数组 $[a_1, a_2, \ldots, a_n]$ 在追加 $k$ 后变为 $[a_1, a_2, \ldots, a_n, k]$。

每次操作后，你需要计算当前数组的炫酷值。

注意所有操作都是持久化的。这意味着每个操作都会修改数组，后续操作都应基于前一次操作后的数组状态进行。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

输入的第一行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——对数组执行的操作次数。

接下来的 $q$ 行首先包含一个整数 $s$（$1 \leq s \leq 3$）——操作类型：
- 如果 $s=1$，则执行循环移位操作。
- 如果 $s=2$，则执行反转操作。
- 如果 $s=3$，则该行还会包含一个额外的整数 $k$（$1 \leq k \leq 10^6$），表示要追加到数组末尾的元素。

保证所有测试用例的 $q$ 之和不超过 $2 \cdot 10^5$。此外，保证每个测试用例的第一个操作都是 $s=3$ 类型的操作。

## 输出格式

对于每个测试用例，输出 $q$ 行，每行输出每次操作后数组的炫酷值。


## 说明/提示

数组前六次操作后的状态：
- $[1]$
- $[1, 2]$
- $[1, 2, 3]$
- $[3, 1, 2]$
- $[3, 1, 2, 4]$
- $[4, 2, 1, 3]$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
13
3 1
3 2
3 3
1
3 4
2
3 5
1
3 6
2
3 7
2
1
```

### 输出

```
1
5
14
11
27
23
48
38
74
73
122
102
88
```



---

---
title: "Chat Order"
layout: "post"
diff: 普及/提高-
pid: CF637B
tag: ['队列']
---

# Chat Order

## 题目描述

有一个队列，初始时为空。现在依次插入 $n$ 个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

## 输入格式

第一行，一个整数 $n$ ( $1 \le n \le 200000 $)，表示单词的数量。接下来 $n$ 行，每行一个单词，每个单词都由小写字母构成，非空且长度均不超过 $10$ 。

## 输出格式

若干行，每行一个单词，依次表示从队首到队尾的每个单词。

## 样例 #1

### 输入

```
4
alex
ivan
roman
ivan

```

### 输出

```
ivan
roman
alex

```

## 样例 #2

### 输入

```
8
alina
maria
ekaterina
darya
darya
ekaterina
maria
alina

```

### 输出

```
alina
maria
ekaterina
darya

```



---

---
title: "Merge Equals"
layout: "post"
diff: 普及/提高-
pid: CF962D
tag: ['排序', '优先队列', '队列']
---

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 150\,000 $ ) — the number of elements in the array.

The second line contains a sequence from $ n $ elements $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ) — the elements of the array.

## 输出格式

In the first line print an integer $ k $ — the number of elements in the array after all the performed operations. In the second line print $ k $ integers — the elements of the array after all the performed operations.

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1

```

### 输出

```
4
3 8 2 1 

```

## 样例 #2

### 输入

```
5
1 1 3 1 1

```

### 输出

```
2
3 4 

```

## 样例 #3

### 输入

```
5
10 40 20 50 30

```

### 输出

```
5
10 40 20 50 30 

```



---

---
title: "Fair"
layout: "post"
diff: 普及/提高-
pid: CF986A
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# Fair

## 题目描述

一些公司将在Byteland举办商品交易会（or博览会？）。在Byteland有 $n$ 个城市，城市间有 $m$ 条双向道路。当然，城镇之间两两连通。
Byteland生产的货物有 $k$ 种类型，每个城镇只生产一种。
为了举办商品交易会，你必须至少带来 $s$ 种不同类型的商品。将货物从 $u$ 镇带到城镇 $v$ 将花费 $d(u,v)$ 的费用，其中 $d(u,v)$ 是从 $u$ 到 $v$ 的最短路径的长度。
路径的长度是这个路径中的道路的数量。              
组织者将支付所有的运输费用，但他们可以选择从哪些城镇带来货物。现在他们想计算每个城镇举办商品交易会的最小费用。

## 输入格式

第一行 $4$ 个整数$n$ , $m$ , $k$ , $s$ ($1\le n\le 10^5 $,$1\le m\le 10^5 $,$1\le s\le k\le min(n,100)$ )——分别表示 城镇数，道路数，生产的货物数，举办商品交易会所需的货物数。

接下来一行$n$个整数$a_1,a_2,...,a_n(1\le a_i \le k)$ , $a_i$是第$i$个城镇生产的商品种类.保证$1$和$k$之间的所有整数在整数$a_i$中至少出现一次。 

接下来$m$行表示道路。每行两个整数 $u$ $v$ $(1 \le u$,$v \le n, u\ne v)$ 表示  $u$ $v$ 之间有一条双向道路。保证每两个城镇之间只有一条路。并且城镇之间两两连通。

## 输出格式

输出$n$个数。第$i$个数表示在第$i$个城镇举办商品交易会所需花在运输上的最小费用。数与数之间用空格分开。

## 样例 #1

### 输入

```
5 5 4 3
1 2 4 3 2
1 2
2 3
3 4
4 1
4 5

```

### 输出

```
2 2 2 2 3 

```

## 样例 #2

### 输入

```
7 6 3 2
1 2 3 3 2 2 1
1 2
2 3
3 4
2 5
5 6
6 7

```

### 输出

```
1 1 1 2 2 1 1 

```



---

