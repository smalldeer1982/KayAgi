---
title: "Bicycles"
layout: "post"
diff: 普及+/提高
pid: CF1915G
tag: ['最短路']
---

# Bicycles

## 题目描述

给定 $n$ 个城市和 $m$ 条连接两个城市 $u_i$ 和 $v_i$ 的双向道路，长度为 $w_i$。

现在城市 $n$ 举办了一场派对，住在城市 $1$ 的 Slavic 想要去参加。在城市之间往返需要骑自行车，而 Slavic 没有自行车，所以他需要在这些城市里购买自行车以赶到城市 $n$。

从 $1$ 到 $n$ 的每个城市 $j$ 里都有且仅有一辆自行车可供购买，每辆自行车的速度系数为 $s_j$。

当 Slavic 骑上编号为 $j$ 的自行车后，他可以在任何时刻和任何地点通过一条道路 $i$，花费 $w_i\times s_j$ 的时间。

求 Slavic 骑车从城市 $1$ 赶到城市 $n$ 参加派对所需的最短时间。

## 输入格式

第一行包含一个整数 $ t\,  (  1 \leq t \leq 100  )$，代表测试数据组数。

每组数据的第一行包含两个整数 $n$ 和 $m$，代表城市的数量和道路的数量。

接下来的 $m$ 行中，第 $i$ 行包含三个整数 $u_i$、$v_i$ 和 $w_i$，代表一条连接城市 $u_i$ 和 $v_i$，长度为 $w_i$ 的双向道路。

每组数据的最后一行包含 $n$ 个整数 $ s_1, \ldots, s_n $，代表在城市 $i$ 可供购买的自行车的速度系数。

## 输出格式

对于每组测试数据，输出一个整数，代表从城市 $1$ 到达城市 $n$ 所需的最短时间。

## 说明/提示

$ 2 \leq n \leq 1000 $，$ n - 1 \leq m \leq 1000$，$ 1 \leq s_i \leq 1000 $；

$ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $，$ 1 \leq w_i \leq 10^5$；

所有测试数据的 $\sum n$、$\sum m$ 不超过 $1000$。

保证存在方案能从城市 $1$ 到达城市 $n$。

By Misaka16172

## 样例 #1

### 输入

```
3
5 5
1 2 2
3 2 1
2 4 5
2 5 7
4 5 1
5 2 1 3 3
5 10
1 2 5
1 3 5
1 4 4
1 5 8
2 3 6
2 4 3
2 5 2
3 4 1
3 5 8
4 5 2
7 2 8 4 1
7 10
3 2 8
2 1 4
2 5 7
2 6 4
7 1 2
4 3 5
6 4 2
6 7 1
6 7 4
4 5 9
7 6 5 4 3 2 1
```

### 输出

```
19
36
14
```



---

---
title: "Rudolf and Subway"
layout: "post"
diff: 普及+/提高
pid: CF1941G
tag: ['最短路']
---

# Rudolf and Subway

## 题目描述

建桥对伯纳德没有帮助，他去哪里都迟到。然后鲁道夫决定教他乘坐地铁。

鲁道夫将地铁地图描绘成一个无向连接图，没有自循环，其中顶点代表车站。任何一对顶点之间最多有一条边。

如果可以绕过其他站点，则可以通过一条边直接在相应站点之间移动，则两个顶点通过一条边连接。鲁道夫和伯纳德居住的城市的地铁有颜色符号。这意味着站点之间的任何边缘都具有特定的颜色。特定颜色的边缘共同形成一条地铁线。地铁线不能包含未连接的边，并形成给定地铁图的连接子图。

地铁地图示例如图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941G/7c6e3ab76399bc5859a6a1ea202bbed5b214c151.png)
 鲁道夫声称，如果这条路线通过最少数量的地铁线路，这条路线将是最佳的。

帮助 Bernard 确定给定出发站和目的地站的最小数量。

## 输入格式

第一行包含一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 表示测试用例的数量。

接下来是测试用例的描述。

每个测试用例的第一行包含两个整数 $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5, 1 \le m \le 2 \cdot 10^5 $ ) 表示地铁站数量和车站之间的直达路线数量 (即图形边缘).

紧随其后的是 $ m $ 行 表示边缘的描述。描述的每一行包含三个整数 $ u $ , $ v $ , and $ c $ ( $ 1 \le u, v \le n, u \ne v, 1 \le c \le 2 \cdot 10^5 $ ) ） — 有一条边的顶点的数目，以及这条边的颜色。保证相同颜色的边形成给定地铁图的连接子图。任意两个顶点的一对之间最多有一条边。

后面跟着两个整数 $ b $ 和 $ e $ ( $ 1 \le b, e \le n $ ) 表示出发站和目的地站。

所有测试用例上所有 $ n $ 的总和不超过 $ 2 \cdot 10^5 $ . 所有的总和 $ m $ 在所有测试用例中不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个测试用例，输出一个整数 — 从车站 $ b $ 到车站 $ e $ 的路线可以通过的最小地铁线路数。

## 样例 #1

### 样例输入 #1

```
5
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 3
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 6
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
6 6
4 3
1 2 1
1 3 1
4 1 1
2 3
6 7
1 2 43
1 3 34
4 6 43
6 3 43
2 3 43
5 3 43
4 5 43
1 6
```

### 样例输出 #1

```
1
2
0
1
1
```

## 样例 #2

### 样例输入 #2

```
3
7 9
2 4 1
3 6 1
2 3 5
1 7 1
4 7 1
2 5 4
5 4 4
3 4 1
3 7 1
5 3
6 5
6 5 83691
4 1 83691
5 4 83691
3 2 83691
4 3 83691
5 1
6 7
6 1 83691
6 2 83691
2 5 83691
5 6 83691
2 3 83691
5 4 83574
3 5 83691
1 4
```

### 样例输出 #2

```
2
1
2
```

## 说明/提示

第一个示例的地铁图如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941G/7c6e3ab76399bc5859a6a1ea202bbed5b214c151.png)

在第一个测试用例中，从顶点 $ 1 $ 到顶点 $ 3 $ ，可以沿着路径行进 $ 1 \rightarrow 2 \rightarrow 3 $ , 仅使用绿线。

在第二个测试用例中，从顶点 $ 1 $ 到顶点 $ 6 $ , 你可以沿着这条路旅行 $ 1 \rightarrow 2 \rightarrow 3 \rightarrow 6 $ , 使用绿线和蓝线。

在第三个测试用例中，不需要从顶点 $ 6 $ 移动到同一个顶点，所以行数为 $ 0 $ 。

在第四个测试用例中，图的所有边都属于一条线，所以答案是 $ 1 $ 。

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 3
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 6
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
6 6
4 3
1 2 1
1 3 1
4 1 1
2 3
6 7
1 2 43
1 3 34
4 6 43
6 3 43
2 3 43
5 3 43
4 5 43
1 6
```

### 输出

```
1
2
0
1
1
```

## 样例 #2

### 输入

```
3
7 9
2 4 1
3 6 1
2 3 5
1 7 1
4 7 1
2 5 4
5 4 4
3 4 1
3 7 1
5 3
6 5
6 5 83691
4 1 83691
5 4 83691
3 2 83691
4 3 83691
5 1
6 7
6 1 83691
6 2 83691
2 5 83691
5 6 83691
2 3 83691
5 4 83574
3 5 83691
1 4
```

### 输出

```
2
1
2
```



---

---
title: "Determine Winning Islands in Race"
layout: "post"
diff: 普及+/提高
pid: CF1998D
tag: ['动态规划 DP', '最短路']
---

# Determine Winning Islands in Race

## 题目描述

MOOOOOOOOOOOOOOOOO

— Bessie the Cow, The Art of Racing on Islands



Two of Farmer John's cows, Bessie and Elsie, are planning to race on $ n $ islands. There are $ n - 1 $ main bridges, connecting island $ i $ to island $ i + 1 $ for all $ 1 \leq i \leq n - 1 $ . Additionally, there are $ m $ alternative bridges. Elsie can use both main and alternative bridges, while Bessie can only use main bridges. All bridges are one way and can only be used to travel from an island with a lower index to an island with a higher index.

Initially, Elsie starts on island $ 1 $ , and Bessie starts on island $ s $ . The cows alternate turns, with Bessie making the first turn. Suppose the cow is on island $ i $ . During a cow's turn, if there are any bridges connecting island $ i $ to island $ j $ , then the cow can move to island $ j $ . Then, island $ i $ collapses, and all bridges connecting to island $ i $ also collapse. Also, note the following:

- If there are no bridges connecting island $ i $ to another island, then island $ i $ collapses, and this cow is eliminated from the race.
- If the other cow is also on island $ i $ , then after this cow moves to another island, the island collapses, and the other cow is eliminated from the race.
- After an island or bridge collapses, no cows may use them.
- If a cow is eliminated, their turn is skipped for the rest of the race.

The race ends once either cow reaches island $ n $ . It can be shown that regardless of the cows' strategies, at least one cow reaches island $ n $ . Bessie wins if and only if she reaches island $ n $ first.

For each $ 1 \leq s \leq n - 1 $ , determine whether Bessie wins if she starts the race on island $ s $ . Assume both cows follow optimal strategies to ensure their own respective victories.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

The first line of each test case contains $ n $ and $ m $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq m \leq 2 \cdot 10^5 $ ) – the number of islands and the number of alternative bridges.

The next $ m $ lines of each test case contain $ u $ and $ v $ ( $ 1 \leq u < v \leq n $ ) – the islands that the alternative bridge connects. It is guaranteed all alternative bridges are distinct, and they do not coincide with the main bridges.

It is guaranteed that neither the sum of $ n $ nor the sum of $ m $ over all test cases exceeds $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a binary string of length $ n - 1 $ on a new line. The $ i $ 'th character is $ 1 $ if it is possible for Bessie to win if she starts on island $ i $ . Otherwise, it is $ 0 $ .

## 说明/提示

In the first test case, there are no alternative bridges for Elsie to overtake Bessie and reach island $ n $ first, so Bessie will win on all islands because she always moves first.

In the second case, Bessie will lose if she starts on island $ 3 $ because:

- Bessie's Turn: Take a main bridge from island $ 3 $ to island $ 4 $ .
- Elsie's Turn: Take a main bridge from island $ 1 $ to island $ 2 $ .
- Bessie's Turn: Take a main bridge from island $ 4 $ to island $ 5 $ .
- Elsie's Turn: Take an alternative bridge from island $ 2 $ to island $ 6 $ . Elsie reaches island $ n $ first.

## 样例 #1

### 输入

```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15
```

### 输出

```
11111
11011
10011
100001111
11000111000111
```



---

---
title: "Rendez-vous de Marian et Robin"
layout: "post"
diff: 普及+/提高
pid: CF2014E
tag: ['最短路']
---

# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers $ n $ , $ m $ , $ h $ ( $ 2 \le n \le 2 \cdot 10^5, \;1 \le m \le 2 \cdot 10^5, \; 1 \le h \le n $ ) — the number of vertices, the number of edges and the number of vertices that have a single horse.

The second line of each test case contains $ h $ distinct integers $ a_1, a_2, \ldots, a_h $ ( $ 1 \le a_i \le n $ ) — the vertices that have a single horse available.

Then follow $ m $ lines of each test case, each with three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1\le u_i,v_i \le n, \; 2\le w_i \le 10^6 $ ) — meaning that there is an edge between vertices $ u_i $ and $ v_i $ with travel cost $ w_i $ seconds without a horse.

There are no self loops or multiple edges. By good fortune, all $ w_i $ are even integers.

It is guaranteed that the sums of both $ n $ and $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer, the earliest time Robin and Marian can meet. If it is impossible for them to meet, output $ -1 $ .

## 说明/提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 样例 #1

### 输入

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4
```

### 输出

```
5
-1
6
19
14
12
```



---

---
title: "Skipping"
layout: "post"
diff: 普及+/提高
pid: CF2023B
tag: ['动态规划 DP', '图论', '线段树', '最短路']
---

# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 输入格式

此题**多测**，第一行一个整数$t(1\leq t\leq 10^5$，为测试数据组数。每组数据如下：

第一行一个整数$n(1\leq n\leq 4\cdot10^5)$，表示题目数量

第二行一行$n$个整数$a_1,a_2……a_n(1\leq a_i\leq 10^9)$表示题目分数。

第三行一行$n$个整数$b_1,b_2……b_n(1\leq b_i\leq n)$表示题目参数。

保证所有测试数据的$\sum n$不超过$4\cdot 10^5$。

## 输出格式

每行输出一个整数，为小p最大的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1
```

### 输出

```
16
200
100
1000
```



---

---
title: "Alice's Adventures in Cards"
layout: "post"
diff: 普及+/提高
pid: CF2028D
tag: ['动态规划 DP', '树状数组', '最短路']
---

# Alice's Adventures in Cards

## 题目描述

Alice 正在和红心皇后、红心国王以及红心杰克玩纸牌游戏。这个游戏中有 $ n $ 种不同的纸牌类型。Alice 手上现在有一张类型为 $ 1 $ 的纸牌，她需要通过一系列的交换，得到类型为 $ n $ 的纸牌，才能逃出仙境。而其他三名玩家手上各自持有每种类型的纸牌一张。

在这个游戏中，Alice 可以与这些玩家进行纸牌交换。每位玩家对不同类型纸牌的偏好用排列 $ q $、$ k $ 和 $ j $ 来表示，分别对应红心皇后、红心国王和红心杰克。

对于任意玩家，如果在他们的排列 $ p $ 中，满足 $ p_a > p_b $ ，那么该玩家就认为类型为 $ a $ 的纸牌比类型为 $ b $ 的更有价值。于是，他们愿意用类型为 $ b $ 的纸牌换取类型为 $ a $ 的纸牌。而 Alice 的偏好简单直观：纸牌类型 $ a $ 比类型 $ b $ 更有价值，当且仅当 $ a > b $ ，并且她只会按照这种偏好进行交换。

请判断 Alice 能否通过与其他玩家的交换，从类型为 $ 1 $ 的纸牌升级到类型为 $ n $ 的纸牌。如果可以，请给出可能的交换方案。

$ ^{\text{∗}} $ 长度为 $ n $ 的排列是一个包含 $ n $ 个不同整数（从 $ 1 $ 到 $ n $）的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 和 $ [1,3,4] $ 则不是。

## 输入格式

输入包含多个测试用例。第一行给出测试用例的数量 $ t $ （$ 1 \le t \le 10^4 $）。随后是每个测试用例的详细描述。

对于每个测试用例，首先提供一个整数 $ n $ （$ 2 \le n \le 2 \cdot 10^5 $），代表纸牌类型的数量。

接下来的三行分别是红心皇后、红心国王和红心杰克对纸牌的偏好排列。每行包括 $ n $ 个整数 $ p_1, p_2, \ldots, p_n $ （$ 1 \le p_i \le n $），表示每个玩家对纸牌的偏好顺序。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一行，写上 "YES" 或 "NO" 来表示 Alice 是否能通过交换得到类型为 $ n $ 的纸牌。

如果可以输出 "YES"，接下来一行输出一个整数 $ k $ ，表示 Alice 将进行的交换次数。随后的 $ k $ 行，每行描述一次交换，以一个字符 $ c \in \{\texttt{q}, \texttt{k}, \texttt{j}\} $ 和一个整数 $ x $ 的形式出现，表示 Alice 与玩家 $ c $ 进行交换，以获得类型为 $ x $ 的纸牌。最终必须确保在第 $ k $ 次交换后，得到的纸牌为类型 $ n $。如果存在多种解决方案，输出任意一个即可。

输出中的字母大小写不固定。例如，"yEs"、"yes"、"Yes" 和 "YES" 都被视为肯定回答。同样，代表玩家的字符 $ c $ 也可以使用大写形式（$\texttt{Q}$、$\texttt{K}$、$\texttt{J}$）。

## 说明/提示

在第一个测试用例中，Alice 可以与红心国王交换以获得类型为 $ 2 $ 的纸牌，接着再与红心皇后交换以得到类型为 $ 3 $ 的纸牌。

在第二个测试用例中，尽管 Alice 能与红心皇后交换得到类型为 $ 3 $ 的纸牌，再接着与红心国王交换得到类型为 $ 2 $，最后与红心杰克交换得到类型为 $ 4 $ 的纸牌，但这种方案不符合 Alice 的偏好原则，因此无效。我们可以证明在这种情况下 Alice 无法获得类型为 $ 4 $ 的纸牌。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3
1 3 2
2 1 3
1 2 3
4
2 3 1 4
1 2 3 4
1 4 2 3
```

### 输出

```
YES
2
k 2
q 3
NO
```



---

---
title: "Another Exercise on Graphs (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2057E1
tag: ['图论', '最短路']
---

# Another Exercise on Graphs (Easy Version)

## 题目描述

这是该问题的简单版本。不同版本间的区别在于此版本对 $m$ 有额外约束。只有在你解决了该问题的所有版本后，才能进行 hack。

最近，"T-generation" 的导师需要筹备一场训练赛。他们发现缺少一道题目，且整场比赛中没有图论相关的问题，于是设计了如下题目。

给定一个包含 $n$ 个顶点和 $m$ 条边的连通带权无向图，图中无自环和重边。

处理 $q$ 次形如 $(a, b, k)$ 的查询：在从顶点 $a$ 到顶点 $b$ 的所有路径中，找出路径上边权的第 $k$ 小最大值$^{\dagger}$。

导师们认为这个问题非常有趣，但存在一个问题：他们不知道如何解决它。请帮助他们解决这个问题，因为距离比赛开始仅剩几小时。

$^{\dagger}$ 设 $w_1 \ge w_2 \ge \ldots \ge w_{h}$ 为某条路径中所有边权按非递增顺序排列后的结果。该路径边权的第 $k$ 大值即为 $w_{k}$。


## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \le t \le 100$）表示测试用例数量。每个测试用例的描述如下：

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $q$（$2 \le n \le 400$，$n - 1 \le m \le \operatorname{min}(\mathbf{400}, \frac{n \cdot (n - 1)}{2})$，$1 \le q \le 3 \cdot 10^5$）分别表示顶点数、边数和查询数。

接下来每个测试用例的 $m$ 行中，每行包含三个整数 $v$、$u$ 和 $w$（$1 \le v, u \le n$，$1 \le w \le 10^9$）表示一条边的两个端点及其权重。保证图中无自环和重边。

接下来每个测试用例的 $q$ 行中，每行包含三个整数 $a$、$b$ 和 $k$（$1 \le a, b \le n$，$k \ge 1$）表示一次查询。保证从顶点 $a$ 到顶点 $b$ 的任何路径至少包含 $k$ 条边。

保证所有测试用例的 $n$ 之和不超过 $400$。

保证所有测试用例的 $m$ 之和不超过 $400$。

保证所有测试用例的 $q$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出所有查询的答案。

## 说明/提示

在第一个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 3 \rightarrow 4$，该路径边权的第 $2$ 大值为 $1$。第二次查询的最优路径之一是 $2 \rightarrow 4 \rightarrow 3$，边权的第 $1$ 大值为 $2$。

在第二个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 6$，该路径边权的第 $3$ 大值为 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 4 2
1 2 2
2 4 2
1 3 4
3 4 1
1 4 2
2 3 1
6 7 3
1 2 10
2 3 3
3 4 9
4 5 2
5 6 1
2 4 10
4 6 10
1 6 3
1 6 2
2 4 1
11 17 10
1 4 5
1 3 19
1 2 10
3 2 13
4 5 1
4 6 11
3 5 9
3 6 18
2 7 17
5 8 15
5 10 8
6 9 4
7 10 20
7 8 16
8 11 3
9 11 6
10 11 14
3 11 1
3 11 3
1 11 1
1 11 4
1 11 3
8 2 2
10 4 1
3 9 2
3 9 1
6 7 3
```

### 输出

```
1 2
2 9 9
11 3 11 1 3 10 8 4 11 4
```



---

---
title: "D/D/D"
layout: "post"
diff: 普及+/提高
pid: CF2109D
tag: ['图论', '最短路']
---

# D/D/D

## 题目描述

当然，这道以字母 D 开头的题目是由 Declan Akaba 赞助的。

给定一个简单、连通的无向图，包含 $n$ 个顶点和 $m$ 条边。图中没有自环或重边。同时给定一个包含 $\ell$ 个元素的多重集 $A$：
$$ A = \{A_1, A_2, \ldots, A_\ell\} $$

从顶点 $1$ 出发，你可以执行以下操作任意次数（只要多重集 $A$ 不为空）：
- 从多重集 $A$ 中选择一个元素 $k$ 并移除它（必须移除 $k$ 的一个实例）。
- 遍历恰好包含 $k$ 条边的任意路径$^{\text{∗}}$，到达某个顶点（可以是起始顶点本身）。

对于每个 $i$（$1 \le i \le n$），判断是否存在一个操作序列，使得从顶点 $1$ 出发，使用原始多重集 $A$，最终能到达顶点 $i$。

注意：对每个顶点 $i$ 的检查是独立的——每次都需要从顶点 $1$ 重新开始，并使用原始多重集 $A$。

$^{\text{∗}}$ 长度为 $k$ 的路径是指一个顶点序列 $v_0, v_1, \ldots, v_{k-1}, v_k$，其中每对相邻顶点 $(v_i, v_{i+1})$ 都由图中的一条边连接。序列中允许包含重复的顶点。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $\ell$（$2 \leq n \leq 2 \cdot 10^5$，$n-1 \leq m \leq 4 \cdot 10^5$，$1 \leq \ell \leq 2 \cdot 10^5$）——分别表示顶点数、边数和多重集的大小。

第二行包含 $\ell$ 个整数 $A_1, A_2, \ldots, A_{\ell}$（$1 \leq A_i \leq 10^4$）——多重集的元素。

接下来的 $m$ 行，每行包含两个整数 $u$ 和 $v$（$1 \le u < v \le n$）——表示图中的一条边。

保证边构成一个简单、连通的无向图，没有自环或重边。

保证所有测试用例的 $n$ 之和、$m$ 之和以及 $\ell$ 之和分别不超过 $2 \cdot 10^5$、$4 \cdot 10^5$ 和 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个长度为 $n$ 的二进制字符串，其中第 $i$ 个字符为 $\mathtt{1}$ 表示存在到达顶点 $i$ 的操作序列，否则为 $\mathtt{0}$。


## 说明/提示

**第一个测试用例解释：**
- 顶点 $1$ 无需任何操作即可到达。
- 顶点 $2$ 可通过选择 $A$ 中的元素 $3$ 到达，例如路径 $[1 \rightarrow 2 \rightarrow 1 \rightarrow 2]$。
- 顶点 $3$ 可通过选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$ 到达。
- 顶点 $4$ 可通过选择 $A$ 中的元素 $3$ 并走路径 $[1 \rightarrow 2 \rightarrow 3 \rightarrow 4]$ 到达。
- 顶点 $5$ 无法通过任何有效操作序列到达。
- 顶点 $6$ 可通过以下方式到达：
  1. 选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$；
  2. 选择 $A$ 中的元素 $3$ 并走路径 $[3 \rightarrow 4 \rightarrow 5 \rightarrow 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
6 5 2
2 3
1 2
2 3
3 4
4 5
5 6
5 5 1
5
1 2
2 3
3 4
4 5
3 5
5 4 3
100 200 300
1 2
1 3
1 4
2 5
```

### 输出

```
111101
11111
10001
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
title: "Roads in Berland"
layout: "post"
diff: 普及+/提高
pid: CF25C
tag: ['最短路']
---

# Roads in Berland

## 题目描述

There are $ n $ cities numbered from 1 to $ n $ in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build $ k $ new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=300 $ ) — amount of cities in Berland. Then there follow $ n $ lines with $ n $ integer numbers each — the matrix of shortest distances. $ j $ -th integer in the $ i $ -th row — $ d_{i,j} $ , the shortest distance between cities $ i $ and $ j $ . It is guaranteed that $ d_{i,i}=0,d_{i,j}=d_{j,i} $ , and a given matrix is a matrix of shortest distances for some set of two-way roads with integer lengths from 1 to 1000, such that from each city it is possible to get to any other city using these roads.

Next line contains integer $ k $ ( $ 1<=k<=300 $ ) — amount of planned roads. Following $ k $ lines contain the description of the planned roads. Each road is described by three space-separated integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n,a_{i}≠b_{i},1<=c_{i}<=1000 $ ) — $ a_{i} $ and $ b_{i} $ — pair of cities, which the road connects, $ c_{i} $ — the length of the road. It can be several roads between a pair of cities, but no road connects the city with itself.

## 输出格式

Output $ k $ space-separated integers $ q_{i} $ ( $ 1<=i<=k $ ). $ q_{i} $ should be equal to the sum of shortest distances between all pairs of cities after the construction of roads with indexes from 1 to $ i $ . Roads are numbered from 1 in the input order. Each pair of cities should be taken into account in the sum exactly once, i. e. we count unordered pairs.

## 样例 #1

### 输入

```
2
0 5
5 0
1
1 2 3

```

### 输出

```
3 
```

## 样例 #2

### 输入

```
3
0 4 5
4 0 9
5 9 0
2
2 3 8
1 2 1

```

### 输出

```
17 12 
```



---

---
title: "Greg and Graph"
layout: "post"
diff: 普及+/提高
pid: CF295B
tag: ['枚举', '最短路', '概率论']
---

# Greg and Graph

## 题目描述

Greg 有一个有边权的有向图，包含 $n$ 个点。这个图的每两个点之间都有两个方向的边。Greg 喜欢用他的图玩游戏，现在他发明了一种新游戏：

- 游戏包含 $n$ 步。
- 第 $i$ 步 Greg 从图中删掉编号为 $x_i$ 的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg 想知道所有点对间最短路长度的和。最短路可以经过任何没删掉的点。换句话说，如果我们假设 $d(i, v, u)$ 是在删掉 $x_i$ 前 $v$ 和 $u$ 间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮 Greg，输出每一步之前要求的值。

## 输入格式

第一行包含一个整数 $n \ (1 \leq n \leq 500)$ ，代表图中的点数。

下面 $n$ 行每行包含 $n$ 个整数，代表边权：第 $i$ 行的第 $j$ 个数 $a_{ij} \ (1 \leq a_{ij} \leq 10^5, a_{ii} = 0)$ 代表从 $i$ 到 $j$ 的边权。

最后一行包含 $n$ 个整数：$x_1, x_2, \dots, x_n \ (1 \leq x_i \leq n)$ ，分别为Greg每一步删掉的点的编号。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数等于游戏的第 $i$ 步之前统计的求和值。

请不要在 C++ 中使用 `%lld` 标志来输出 64 位整数 `long long`，推荐使用 `cin, cout` 流或者用 `%I64d` 标志。

Translated by @KSkun

## 样例 #1

### 输入

```
1
0
1

```

### 输出

```
0 
```

## 样例 #2

### 输入

```
2
0 5
4 0
1 2

```

### 输出

```
9 0 
```

## 样例 #3

### 输入

```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3

```

### 输出

```
17 23 404 0 
```



---

---
title: "World Tour"
layout: "post"
diff: 普及+/提高
pid: CF666B
tag: ['枚举', '最短路']
---

# World Tour

## 题目描述

A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are $ n $ cities and $ m $ one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png). Four cities in the order of visiting marked as overlines: $ [1,5,2,4] $ .

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

## 输入格式

In the first line there is a pair of integers $ n $ and $ m $ ( $ 4<=n<=3000,3<=m<=5000 $ ) — a number of cities and one-way roads in Berland.

Each of the next $ m $ lines contains a pair of integers $ u_{i},v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — a one-way road from the city $ u_{i} $ to the city $ v_{i} $ . Note that $ u_{i} $ and $ v_{i} $ are not required to be distinct. Moreover, it can be several one-way roads between the same pair of cities.

## 输出格式

Print four integers — numbers of cities which Cicasso will visit according to optimal choice of the route. Numbers of cities should be printed in the order that Cicasso will visit them. If there are multiple solutions, print any of them.

## 说明/提示

Let $ d(x,y) $ be the shortest distance between cities $ x $ and $ y $ . Then in the example $ d(2,1)=3,d(1,8)=7,d(8,7)=3 $ . The total distance equals $ 13 $ .

## 样例 #1

### 输入

```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5

```

### 输出

```
2 1 8 7

```



---

