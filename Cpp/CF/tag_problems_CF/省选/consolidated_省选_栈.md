---
title: "Narrower Passageway"
layout: "post"
diff: 省选/NOI-
pid: CF2045E
tag: ['数学', 'ST 表', '单调栈']
---

# Narrower Passageway

## 题目描述

你是 ICPC 王国的一名战略家，近日你收到情报，王国附近的一条狭窄通道将遭遇怪物的袭击。这条通道可以简化为一个 2 行 $N$ 列的网格。我们用 $(r, c)$ 表示网格中第 $r$ 行第 $c$ 列的格子。每天会安排一个力量值为 $P_{r, c}$ 的士兵驻守在 $(r, c)$ 位置上。

这里常年大雾，每列都有 $50\%$ 的概率被雾气笼罩。一旦某列被雾气覆盖，两个驻守该列的士兵将无法执行任务。否则，士兵将正常部署。

我们定义一个连通区域 $[u, v]$（$u \leq v$）为从第 $u$ 列到第 $v$ 列连续且无雾的列。下面的示例中，灰色部分代表被雾覆盖的格子，共有四个连通区域：$[1, 2]$、$[4, 6]$、$[9, 9]$ 和 $[11, 11]$。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/47744495c3a12fb362399d4924e5c674c3e83888.png)

连通区域 $[u, v]$ 的力量可以这样计算。设 $m_1$ 和 $m_2$ 分别为该区域内第一行和第二行士兵力量的最大值。具体来说，对于 $r \in \{1, 2\}$，有 $m_r = \max (P_{r, u}, P_{r, u + 1}, \dots, P_{r, v})$。如果 $m_1 = m_2$，则该区域的力量是 $0$；否则，力量为 $\min (m_1, m_2)$。

一个工作日的总力量定义为所有连通区域力量的总和。请计算在任意一天部署的期望总力量。

## 输入格式

第一行是一个整数 $N$，表示列数（$1 \leq N \leq 100\,000$）。

接下来的两行，每行包含 $N$ 个整数，表示士兵的力量值 $P_{r, c}$（$1 \leq P_{r, c} \leq 200\,000$）。

## 输出格式

设 $M = 998\,244\,353$。可以证明期望总力量表示为一个不可约分数 $\frac{x}{y}$，其中 $x$ 和 $y$ 是整数，且 $y \not\equiv 0 \pmod{M}$。请输出一个整数 $k$，使得 $0 \leq k < M$ 且 $k \cdot y \equiv x \pmod{M}$。

## 说明/提示

样例输入/输出 #1 解释

这条通道可能有 $8$ 种不同的布局。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/70a3bbc18f3f05a2f49fd32453ba66ee47116d57.png)

每种布局出现的概率是相同的。因此，期望总力量为 $(0 + 5 + 10 + 5 + 5 + 0 + 5 + 0) / 8 = \frac{15}{4}$。由于 $249\,561\,092 \cdot 4 \equiv 15 \pmod{998\,244\,353}$，所以样例的输出为 $249\,561\,092$。

样例输入/输出 #2 解释

期望总力量为 $\frac{67}{16}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
8 4 5
5 4 8
```

### 输出

```
249561092
```

## 样例 #2

### 输入

```
5
10 20 5 8 5
5 20 7 5 8
```

### 输出

```
811073541
```



---

---
title: "Another Folding Strip"
layout: "post"
diff: 省选/NOI-
pid: CF2077E
tag: ['贪心', '二分图', '单调栈']
---

# Another Folding Strip

## 题目描述

对于一个长度为 $m$ 的数组 $b$，定义 $f(b)$ 如下：

考虑一个 $1 \times m$ 的纸带，所有单元格初始暗度为 $0$。你需要通过以下操作将其转化为第 $i$ 个位置的暗度为 $b_i$ 的纸带。每次操作包含两个步骤：

1. 在任意两个单元格之间的线上折叠纸带。你可以进行任意次折叠（包括不折叠）。
2. 选择一个位置滴下黑色染料。染料会从顶部渗透并向下流动，使其路径上所有单元格的暗度增加 $1$。滴完染料后展开纸带。

令 $f(b)$ 为达成目标配置所需的最小操作次数。可以证明总能通过有限次操作达成目标。

给定一个长度为 $n$ 的数组 $a$，计算

$$ \sum_{l=1}^n\sum_{r=l}^n f(a_l a_{l+1} \ldots a_r) $$

模 $998\,244\,353$ 的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行输入一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——数组 $a$ 的长度。

第二行输入 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq 10^9$）——表示数组 $a$。

保证所有测试用例的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——所求结果模 $998\,244\,353$ 的值。


## 说明/提示

第一个测试用例中：
- $f(a_1)=f(\mathtt{0})=0$
- $f(a_1a_2)=f(\mathtt{01})=1$
- $f(a_1a_2a_3)=f(\mathtt{010})=1$
- $f(a_2)=f(\mathtt{1})=1$
- $f(a_2a_3)=f(\mathtt{10})=1$
- $f(a_3)=f(\mathtt{0})=0$

总和为 $0+1+1+1+1+0 = 4$。

第二个测试用例中，$f(a_1a_2a_3a_4a_5a_6) = 2$。下图展示了一种可能的操作序列：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2077E/80a2b52ea34f6bea16eaab9b1e723d17328eb717.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
0 1 0
6
1 0 0 1 2 1
5
2 1 2 4 3
12
76 55 12 32 11 45 9 63 88 83 32 6
```

### 输出

```
4
28
47
7001
```



---

---
title: "On Changing Tree"
layout: "post"
diff: 省选/NOI-
pid: CF396C
tag: ['树状数组', '前缀和', '栈']
---

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of vertices in the tree. The second line contains $ n-1 $ integers $ p_{2},p_{3},...\ p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ is the number of the vertex that is the parent of vertex $ i $ in the tree.

The third line contains integer $ q $ ( $ 1<=q<=3·10^{5} $ ) — the number of queries. Next $ q $ lines contain the queries, one per line. The first number in the line is $ type $ . It represents the type of the query. If $ type=1 $ , then next follow space-separated integers $ v,x,k $ ( $ 1<=v<=n $ ; $ 0<=x&lt;10^{9}+7 $ ; $ 0<=k&lt;10^{9}+7 $ ). If $ type=2 $ , then next follows integer $ v $ ( $ 1<=v<=n $ ) — the vertex where you need to find the value of the number.

## 输出格式

For each query of the second type print on a single line the number written in the vertex from the query. Print the number modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2

```

### 输出

```
2
1

```



---

---
title: "Jzzhu and Apples"
layout: "post"
diff: 省选/NOI-
pid: CF449C
tag: ['枚举', '素数判断,质数,筛法', '栈']
---

# Jzzhu and Apples

## 题目描述

Jzzhu has picked $ n $ apples from his big apple tree. All the apples are numbered from $ 1 $ to $ n $ . Now he wants to sell them to an apple store.

Jzzhu will pack his apples into groups and then sell them. Each group must contain two apples, and the greatest common divisor of numbers of the apples in each group must be greater than 1. Of course, each apple can be part of at most one group.

Jzzhu wonders how to get the maximum possible number of groups. Can you help him?

## 输入格式

A single integer $ n $ $ (1<=n<=10^{5}) $ , the number of the apples.

## 输出格式

The first line must contain a single integer $ m $ , representing the maximum number of groups he can get. Each of the next $ m $ lines must contain two integers — the numbers of apples in the current group.

If there are several optimal answers you can print any of them.

## 样例 #1

### 输入

```
6

```

### 输出

```
2
6 3
2 4

```

## 样例 #2

### 输入

```
9

```

### 输出

```
3
9 3
2 4
6 8

```

## 样例 #3

### 输入

```
2

```

### 输出

```
0

```



---

---
title: "Arthur and Brackets"
layout: "post"
diff: 省选/NOI-
pid: CF508E
tag: ['模拟', '贪心', '栈']
---

# Arthur and Brackets

## 题目描述

你需要构造一个长为 $2n$ 的小括号序列 $S$，左、右括号各 $n$ 个。

对于从左到右的第 $i$ 个左括号 $S_a$，需要与其配对的右括号 $S_b$ 满足 $b - a \in [L_i, R_i]$。

## 输入格式

第一行一个正整数 $n ~ (1 \leq n \leq 600)$。

接下来的 $n$ 行，每行两个正整数 $L_i, R_i ~ (1 \leq L_i, R_i \leq 2n)$。

## 输出格式

如果可以构造 $S$，输出任意一种方案。

如果无法构造，输出 `IMPOSSIBLE`。

## 样例 #1

### 输入

```
4
1 1
1 1
1 1
1 1

```

### 输出

```
()()()()

```

## 样例 #2

### 输入

```
3
5 5
3 3
1 1

```

### 输出

```
((()))

```

## 样例 #3

### 输入

```
3
5 5
3 3
2 2

```

### 输出

```
IMPOSSIBLE

```

## 样例 #4

### 输入

```
3
2 3
1 4
1 4

```

### 输出

```
(())()

```



---

---
title: "Tavas and Pashmaks"
layout: "post"
diff: 省选/NOI-
pid: CF535E
tag: ['排序', '栈', '凸包']
---

# Tavas and Pashmaks

## 题目描述

现在有两个比赛项目:跑步和游泳.每一个人在这两个项目都有一个正整数的值,第i个人分别为$a_i,b_i$,表示他在这个项目上的速度.
我们假定游泳的距离为$S_1$,跑步的距离为$S_2$(都是**正实数**),知道每一个人的值,如果对于第i个人,存在这样子的$S_1$和$S_2$使得$S_1/a_i+S_2/b_i<=S_1/a_j+S_2/b_j(1<=j<=n)$,那么就称这个人可以夺冠.
求出有多少个人可以夺冠.

## 输入格式

第$1$行一个正整数$n$,表示有$n$个人.
第$2$~$n+1$,每行有$2$个正整数分别表示每一个人在跑步和游泳上的速度.

## 输出格式

一行,输出所有可以夺冠的人.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1

```

### 输出

```
1 2 3 

```

## 样例 #2

### 输入

```
3
1 2
1 1
2 1

```

### 输出

```
1 3 

```



---

---
title: "Painting Edges"
layout: "post"
diff: 省选/NOI-
pid: CF576E
tag: ['线段树', '分治', '栈']
---

# Painting Edges

## 题目描述

Note the unusual memory limit for this problem.

You are given an undirected graph consisting of $ n $ vertices and $ m $ edges. The vertices are numbered with integers from $ 1 $ to $ n $ , the edges are numbered with integers from $ 1 $ to $ m $ . Each edge can be unpainted or be painted in one of the $ k $ colors, which are numbered with integers from $ 1 $ to $ k $ . Initially, none of the edges is painted in any of the colors.

You get queries of the form "Repaint edge $ e_{i} $ to color $ c_{i} $ ". At any time the graph formed by the edges of the same color must be bipartite. If after the repaint this condition is violated, then the query is considered to be invalid and edge $ e_{i} $ keeps its color. Otherwise, edge $ e_{i} $ is repainted in color $ c_{i} $ , and the query is considered to valid.

Recall that the graph is called bipartite if the set of its vertices can be divided into two parts so that no edge connected vertices of the same parts.

For example, suppose you are given a triangle graph, that is a graph with three vertices and edges $ (1,2) $ , $ (2,3) $ and $ (3,1) $ . Suppose that the first two edges are painted color $ 1 $ , and the third one is painted color $ 2 $ . Then the query of "repaint the third edge in color $ 1 $ " will be incorrect because after its execution the graph formed by the edges of color $ 1 $ will not be bipartite. On the other hand, it is possible to repaint the second edge in color $ 2 $ .

You receive $ q $ queries. For each query, you should either apply it, and report that the query is valid, or report that the query is invalid.

## 输入格式

The first line contains integers $ n $ , $ m $ , $ k $ , $ q $ ( $ 2<=n<=5·10^{5} $ , $ 1<=m,q<=5·10^{5} $ , $ 1<=k<=50 $ ) — the number of vertices, the number of edges, the number of colors and the number of queries.

Then follow $ m $ edges of the graph in the form $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ).

Then follow $ q $ queries of the form $ e_{i} $ , $ c_{i} $ ( $ 1<=e_{i}<=m $ , $ 1<=c_{i}<=k $ ).

It is guaranteed that the graph doesn't contain multiple edges and loops.

## 输出格式

For each query print "YES" (without the quotes), if it is valid, or "NO" (without the quotes), if this query destroys the bipartivity of the graph formed by the edges of some color.

## 样例 #1

### 输入

```
3 3 2 5
1 2
2 3
1 3
1 1
2 1
3 2
3 1
2 2

```

### 输出

```
YES
YES
YES
NO
YES

```



---

---
title: "Gift"
layout: "post"
diff: 省选/NOI-
pid: CF76A
tag: ['排序', '生成树', '栈']
---

# Gift

## 题目描述

The kingdom of Olympia consists of $ N $ cities and $ M $ bidirectional roads. Each road connects exactly two cities and two cities can be connected with more than one road. Also it possible that some roads connect city with itself making a loop.

All roads are constantly plundered with bandits. After a while bandits became bored of wasting time in road robberies, so they suggested the king of Olympia to pay off. According to the offer, bandits want to get a gift consisted of gold and silver coins. Offer also contains a list of restrictions: for each road it is known $ g_{i} $ — the smallest amount of gold and $ s_{i} $ — the smallest amount of silver coins that should be in the gift to stop robberies on the road. That is, if the gift contains $ a $ gold and $ b $ silver coins, then bandits will stop robberies on all the roads that $ g_{i}<=a $ and $ s_{i}<=b $ .

Unfortunately kingdom treasury doesn't contain neither gold nor silver coins, but there are Olympian tugriks in it. The cost of one gold coin in tugriks is $ G $ , and the cost of one silver coin in tugriks is $ S $ . King really wants to send bandits such gift that for any two cities there will exist a safe path between them. Your task is to find the minimal cost in Olympian tugriks of the required gift.

## 输入格式

The first line of the input contains two integers $ N $ and $ M $ ( $ 2<=N<=200 $ , $ 1<=M<=50000 $ ) — the number of cities and the number of roads, respectively. The second line contains two integers $ G $ and $ S $ ( $ 1<=G,S<=10^{9} $ ) — the prices of gold and silver coins in tugriks. The following $ M $ lines contain information about the offer. Each of the records in list is given as four integers $ x_{i},y_{i},g_{i},s_{i} $ , where $ x_{i} $ and $ y_{i} $ are the numbers of cities that the road connects and $ g_{i} $ , $ s_{i} $ are minimal gold and silver coins requirements for the $ i $ -th road ( $ 1<=x_{i},y_{i}<=N $ , $ 1<=g_{i},s_{i}<=10^{9} $ ). Cities are numbered from $ 1 $ to $ N $ . It is possible that there are more than one road between a pair of cities. It is possible that a road connects the city with itself.

## 输出格式

The output should contain the minimal cost of the gift in Olympian tugriks. If there is no gift that satisfies the given requirements output ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF76A/843ffcb025f9d699cf4e412e21508ca44c9ae26c.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1

```

### 输出

```
30

```



---

---
title: "Good Subsegments"
layout: "post"
diff: 省选/NOI-
pid: CF997E
tag: ['线段树', '排序', '栈']
---

# Good Subsegments

## 题目描述

A permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ) .

Let's call the subsegment $ [l,r] $ of the permutation good if all numbers from the minimum on it to the maximum on this subsegment occur among the numbers $ p_l, p_{l+1}, \dots, p_r $ .

For example, good segments of permutation $ [1, 3, 2, 5, 4] $ are:

- $ [1, 1] $ ,
- $ [1, 3] $ ,
- $ [1, 5] $ ,
- $ [2, 2] $ ,
- $ [2, 3] $ ,
- $ [2, 5] $ ,
- $ [3, 3] $ ,
- $ [4, 4] $ ,
- $ [4, 5] $ ,
- $ [5, 5] $ .

You are given a permutation $ p_1, p_2, \ldots, p_n $ .

You need to answer $ q $ queries of the form: find the number of good subsegments of the given segment of permutation.

In other words, to answer one query, you need to calculate the number of good subsegments $ [x \dots y] $ for some given segment $ [l \dots r] $ , such that $ l \leq x \leq y \leq r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 120000 $ ) — the number of elements in the permutation.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ separated by spaces ( $ 1 \leq p_i \leq n $ ).

The third line contains an integer $ q $ ( $ 1 \leq q \leq 120000 $ ) — number of queries.

The following $ q $ lines describe queries, each line contains a pair of integers $ l $ , $ r $ separated by space ( $ 1 \leq l \leq r \leq n $ ).

## 输出格式

Print a $ q $ lines, $ i $ -th of them should contain a number of good subsegments of a segment, given in the $ i $ -th query.

## 样例 #1

### 输入

```
5
1 3 2 5 4
15
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5

```

### 输出

```
1
2
5
6
10
1
3
4
7
1
2
4
1
3
1

```



---

