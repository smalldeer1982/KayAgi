---
title: "Yet Another LCP Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1073G
tag: ['字符串', '图论', '后缀自动机 SAM', '虚树', '后缀数组 SA', '后缀树']
---

# Yet Another LCP Problem

## 题目描述

Let $ \text{LCP}(s, t) $ be the length of the longest common prefix of strings $ s $ and $ t $ . Also let $ s[x \dots y] $ be the substring of $ s $ from index $ x $ to index $ y $ (inclusive). For example, if $ s =  $ "abcde", then $ s[1 \dots 3] = $ "abc", $ s[2 \dots 5] = $ "bcde".

You are given a string $ s $ of length $ n $ and $ q $ queries. Each query is a pair of integer sets $ a_1, a_2, \dots, a_k $ and $ b_1, b_2, \dots, b_l $ . Calculate $ \sum\limits_{i = 1}^{i = k} \sum\limits_{j = 1}^{j = l}{\text{LCP}(s[a_i \dots n], s[b_j \dots n])} $ for each query.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the length of string $ s $ and the number of queries, respectively.

The second line contains a string $ s $ consisting of lowercase Latin letters ( $ |s| = n $ ).

Next $ 3q $ lines contains descriptions of queries — three lines per query. The first line of each query contains two integers $ k_i $ and $ l_i $ ( $ 1 \le k_i, l_i \le n $ ) — sizes of sets $ a $ and $ b $ respectively.

The second line of each query contains $ k_i $ integers $ a_1, a_2, \dots a_{k_i} $ ( $ 1 \le a_1 < a_2 < \dots < a_{k_i} \le n $ ) — set $ a $ .

The third line of each query contains $ l_i $ integers $ b_1, b_2, \dots b_{l_i} $ ( $ 1 \le b_1 < b_2 < \dots < b_{l_i} \le n $ ) — set $ b $ .

It is guaranteed that $ \sum\limits_{i = 1}^{i = q}{k_i} \le 2 \cdot 10^5 $ and $ \sum\limits_{i = 1}^{i = q}{l_i} \le 2 \cdot 10^5 $ .

## 输出格式

Print $ q $ integers — answers for the queries in the same order queries are given in the input.

## 说明/提示

Description of queries:

1. In the first query $ s[1 \dots 7] = \text{abacaba} $ and $ s[2 \dots 7] = \text{bacaba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{bacaba}) + \text{LCP}(\text{bacaba}, \text{abacaba}) + \text{LCP}(\text{bacaba}, \text{bacaba}) = 7 + 0 + 0 + 6 = 13 $ .
2. In the second query $ s[1 \dots 7] = \text{abacaba} $ , $ s[2 \dots 7] = \text{bacaba} $ , $ s[3 \dots 7] = \text{acaba} $ and $ s[7 \dots 7] = \text{a} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{a}) + \text{LCP}(\text{bacaba}, \text{a}) + \text{LCP}(\text{acaba}, \text{a}) = 1 + 0 + 1 = 2 $ .
3. In the third query $ s[1 \dots 7] = \text{abacaba} $ are compared with all suffixes. The answer is the sum of non-zero values: $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{acaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{abacaba}, \text{a}) = 7 + 1 + 3 + 1 = 12 $ .
4. In the fourth query $ s[1 \dots 7] = \text{abacaba} $ and $ s[5 \dots 7] = \text{aba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{aba}, \text{abacaba}) + \text{LCP}(\text{aba}, \text{aba}) = 7 + 3 + 3 + 3 = 16 $ .

## 样例 #1

### 输入

```
7 4
abacaba
2 2
1 2
1 2
3 1
1 2 3
7
1 7
1
1 2 3 4 5 6 7
2 2
1 5
1 5

```

### 输出

```
13
2
12
16

```



---

---
title: "Kingdom and its Cities"
layout: "post"
diff: 省选/NOI-
pid: CF613D
tag: ['动态规划 DP', '虚树']
---

# Kingdom and its Cities

## 题目描述

Meanwhile, the kingdom of K is getting ready for the marriage of the King's daughter. However, in order not to lose face in front of the relatives, the King should first finish reforms in his kingdom. As the King can not wait for his daughter's marriage, reforms must be finished as soon as possible.

The kingdom currently consists of $ n $ cities. Cities are connected by $ n-1 $ bidirectional road, such that one can get from any city to any other city. As the King had to save a lot, there is only one path between any two cities.

What is the point of the reform? The key ministries of the state should be relocated to distinct cities (we call such cities important). However, due to the fact that there is a high risk of an attack by barbarians it must be done carefully. The King has made several plans, each of which is described by a set of important cities, and now wonders what is the best plan.

Barbarians can capture some of the cities that are not important (the important ones will have enough protection for sure), after that the captured city becomes impassable. In particular, an interesting feature of the plan is the minimum number of cities that the barbarians need to capture in order to make all the important cities isolated, that is, from all important cities it would be impossible to reach any other important city.

Help the King to calculate this characteristic for each of his plan.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cities in the kingdom.

Each of the next $ n-1 $ lines contains two distinct integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — the indices of the cities connected by the $ i $ -th road. It is guaranteed that you can get from any city to any other one moving only along the existing roads.

The next line contains a single integer $ q $ ( $ 1<=q<=100000 $ ) — the number of King's plans.

Each of the next $ q $ lines looks as follows: first goes number $ k_{i} $ — the number of important cities in the King's plan, ( $ 1<=k_{i}<=n $ ), then follow exactly $ k_{i} $ space-separated pairwise distinct numbers from 1 to $ n $ — the numbers of important cities in this plan.

The sum of all $ k_{i} $ 's does't exceed $ 100000 $ .

## 输出格式

For each plan print a single integer — the minimum number of cities that the barbarians need to capture, or print $ -1 $ if all the barbarians' attempts to isolate important cities will not be effective.

## 说明/提示

In the first sample, in the first and the third King's plan barbarians can capture the city 3, and that will be enough. In the second and the fourth plans all their attempts will not be effective.

In the second sample the cities to capture are 3 and 5.

## 样例 #1

### 输入

```
4
1 3
2 3
4 3
4
2 1 2
3 2 3 4
3 1 2 4
4 1 2 3 4

```

### 输出

```
1
-1
1
-1

```

## 样例 #2

### 输入

```
7
1 2
2 3
3 4
1 5
5 6
5 7
1
4 2 4 6 7

```

### 输出

```
2

```



---

---
title: "Envy"
layout: "post"
diff: 省选/NOI-
pid: CF891C
tag: ['生成树', '连通块', '虚树']
---

# Envy

## 题目描述

For a connected undirected weighted graph $ G $ , MST (minimum spanning tree) is a subgraph of $ G $ that contains all of $ G $ 's vertices, is a tree, and sum of its edges is minimum possible.

You are given a graph $ G $ . If you run a MST algorithm on graph it would give you only one MST and it causes other edges to become jealous. You are given some queries, each query contains a set of edges of graph $ G $ , and you should determine whether there is a MST containing all these edges or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2<=n,m<=5·10^{5} $ , $ n-1<=m $ ) — the number of vertices and edges in the graph and the number of queries.

The $ i $ -th of the next $ m $ lines contains three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ u_{i}≠v_{i} $ , $ 1<=w_{i}<=5·10^{5} $ ) — the endpoints and weight of the $ i $ -th edge. There can be more than one edges between two vertices. It's guaranteed that the given graph is connected.

The next line contains a single integer $ q $ ( $ 1<=q<=5·10^{5} $ ) — the number of queries.

 $ q $ lines follow, the $ i $ -th of them contains the $ i $ -th query. It starts with an integer $ k_{i} $ ( $ 1<=k_{i}<=n-1 $ ) — the size of edges subset and continues with $ k_{i} $ distinct space-separated integers from $ 1 $ to $ m $ — the indices of the edges. It is guaranteed that the sum of $ k_{i} $ for $ 1<=i<=q $ does not exceed $ 5·10^{5} $ .

## 输出格式

For each query you should print "YES" (without quotes) if there's a MST containing these edges and "NO" (of course without quotes again) otherwise.

## 说明/提示

This is the graph of sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891C/d7f37868e211da76f9c523f75a033c3f4d56f21c.png)Weight of minimum spanning tree on this graph is $ 6 $ .

MST with edges $ (1,3,4,6) $ , contains all of edges from the first query, so answer on the first query is "YES".

Edges from the second query form a cycle of length $ 3 $ , so there is no spanning tree including these three edges. Thus, answer is "NO".

## 样例 #1

### 输入

```
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 1 7
2 1 2

```

### 输出

```
YES
NO
YES
NO

```



---

