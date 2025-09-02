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
title: "Quadratic Set"
layout: "post"
diff: 省选/NOI-
pid: CF1622F
tag: ['图论', '哈希 hashing']
---

# Quadratic Set

## 题目描述

Let's call a set of positive integers $ a_1, a_2, \dots, a_k $ quadratic if the product of the factorials of its elements is a square of an integer, i. e. $ \prod\limits_{i=1}^{k} a_i! = m^2 $ , for some integer $ m $ .

You are given a positive integer $ n $ .

Your task is to find a quadratic subset of a set $ 1, 2, \dots, n $ of maximum size. If there are multiple answers, print any of them.

## 输入格式

A single line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

## 输出格式

In the first line, print a single integer — the size of the maximum subset. In the second line, print the subset itself in an arbitrary order.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
3
1 3 4
```

## 样例 #3

### 输入

```
7
```

### 输出

```
4
1 4 5 6
```

## 样例 #4

### 输入

```
9
```

### 输出

```
7
1 2 4 5 6 7 9
```



---

---
title: "Lenient Vertex Cover"
layout: "post"
diff: 省选/NOI-
pid: CF1680F
tag: ['图论', '二分图', '差分']
---

# Lenient Vertex Cover

## 题目描述

You are given a simple connected undirected graph, consisting of $ n $ vertices and $ m $ edges. The vertices are numbered from $ 1 $ to $ n $ .

A vertex cover of a graph is a set of vertices such that each edge has at least one of its endpoints in the set.

Let's call a lenient vertex cover such a vertex cover that at most one edge in it has both endpoints in the set.

Find a lenient vertex cover of a graph or report that there is none. If there are multiple answers, then print any of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains two integers $ n $ and $ m $ ( $ 2 \le n \le 10^6 $ ; $ n - 1 \le m \le \min(10^6, \frac{n \cdot (n - 1)}{2}) $ ) — the number of vertices and the number of edges of the graph.

Each of the next $ m $ lines contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ; $ v \neq u $ ) — the descriptions of the edges.

For each testcase, the graph is connected and doesn't have multiple edges. The sum of $ n $ over all testcases doesn't exceed $ 10^6 $ . The sum of $ m $ over all testcases doesn't exceed $ 10^6 $ .

## 输出格式

For each testcase, the first line should contain YES if a lenient vertex cover exists, and NO otherwise. If it exists, the second line should contain a binary string $ s $ of length $ n $ , where $ s_i = 1 $ means that vertex $ i $ is in the vertex cover, and $ s_i = 0 $ means that vertex $ i $ isn't.

If there are multiple answers, then print any of them.

## 说明/提示

Here are the graphs from the first example. The vertices in the lenient vertex covers are marked red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1680F/04fc7cc460e4db0f5f28c20a639501c9ca608abf.png)

## 样例 #1

### 输入

```
4
6 5
1 3
2 4
3 4
3 5
4 6
4 6
1 2
2 3
3 4
1 4
1 3
2 4
8 11
1 3
2 4
3 5
4 6
5 7
6 8
1 2
3 4
5 6
7 8
7 2
4 5
1 2
2 3
3 4
1 3
2 4
```

### 输出

```
YES
001100
NO
YES
01100110
YES
0110
```

## 样例 #2

### 输入

```
1
10 15
9 4
3 4
6 4
1 2
8 2
8 3
7 2
9 5
7 8
5 10
1 4
2 10
5 3
5 7
2 9
```

### 输出

```
YES
0101100100
```

## 样例 #3

### 输入

```
1
10 19
7 9
5 3
3 4
1 6
9 4
1 4
10 5
7 1
9 2
8 3
7 3
10 9
2 10
9 8
3 2
1 5
10 7
9 5
1 2
```

### 输出

```
YES
1010000011
```



---

---
title: "Labyrinth Adventures"
layout: "post"
diff: 省选/NOI-
pid: CF1681E
tag: ['动态规划 DP', '图论', '倍增', 'O2优化']
---

# Labyrinth Adventures

## 题目描述

有一个 $n\times n$ 的方格图，坐标编号类似平面直角坐标系，左下角为 $(1, 1)$。

这个方格图被分成了 $n$ 层，左下角 $(1, 1)$ 为第一层，随后每层都向外拓展一圈，如下图就是 $n=5$ 的时候的情况：

![](https://espresso.codeforces.com/003bbba1ff0347bde56714b878262c5fe414679d.png)

层与层之间有墙隔开，但每层都有两个门，分别分布在该层顶部和右侧，门是双向的。

现在给出这些门的坐标，有 $m$ 次询问，每次给定两个坐标 $(x_1, y_1)$ 和 $(x_2,y_2)$，请你回答两点之间的最短路。

## 输入格式

第一行一个 $n$。

接下来的 $n-1$ 行中，每行有四个整数 $d_{1,x}, d_{1,y}, d_{2,x}, d_{2,y}$，第 $i$ 行表示第 $i$ 层的两个门的坐标。前两个表示顶部门坐标，后两个表示右侧门坐标。

下一行输入 $m$。

## 输出格式

对每次询问，输出一行一个整数，表示两点之间的最短路长度。**长度的定义是移动的步数。**

#### 样例解释

下图是样例二的网格图，红色的是门。

![](https://espresso.codeforces.com/522ad0e61c0b740a60c9203c9178279992c8ab2e.png)

## 样例 #1

### 输入

```
2
1 1 1 1
10
1 1 1 1
1 1 1 2
1 1 2 1
1 1 2 2
1 2 1 2
1 2 2 1
1 2 2 2
2 1 2 1
2 1 2 2
2 2 2 2
```

### 输出

```
0
1
1
2
0
2
1
0
1
0
```

## 样例 #2

### 输入

```
4
1 1 1 1
2 1 2 2
3 2 1 3
5
2 4 4 3
4 4 3 3
1 2 3 3
2 2 4 4
1 4 2 3
```

### 输出

```
3
4
3
6
2
```



---

---
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF1697E
tag: ['动态规划 DP', '图论', '组合数学']
---

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of points.

Then $ n $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i, y_i \le 10^8 $ ).

No two points have the same coordinates (i. e. if $ i \ne j $ , then either $ x_i \ne x_j $ or $ y_i \ne y_j $ ).

## 输出格式

Print one integer — the number of ways to choose the colors for the points. Since it can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3
```

### 输出

```
240
```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0
```

### 输出

```
24
```



---

---
title: "Algebra Flash"
layout: "post"
diff: 省选/NOI-
pid: CF1767E
tag: ['状态合并', '图论建模', '快速沃尔什变换 FWT', '折半搜索 meet in the middle']
---

# Algebra Flash

## 题目描述

### 题目背景

Algebra Flash 2.2 刚刚发布！

更新日志：

- 全新游戏模式！

感谢您一直以来对游戏的支持！

就这？你略带失望地启动游戏，点进新的游戏模式，上面写着 "彩色平台"。


有 $n$ 个平台排成一列，编号从 $1$ 到 $n$。平台有 $m$ 种颜色，编号从 $1$ 到 $m$。第 $i$ 个平台的颜色是 $c_i$。

你从 $1$ 号平台开始，想要跳到 $n$ 号平台。在一次移动中，你可以从某个平台 $i$ 跳到平台 $i + 1$ 或 $i + 2$。

所有平台最初都未激活（包括平台 $1$ 和 $n$）。对于每种颜色 $j$，你可以支付 $x_j$ 枚金币来激活所有颜色为 $j$ 的平台。

你希望激活一些平台，然后从已激活的平台 $1$ 开始，跳过一些已激活的平台，到达已激活的平台 $n$。

要实现这个目标，你最少花费多少金币？

## 输入格式

第一行两个整数 $n$ 和 $m$（$2 \le n \le 3 \times 10^5$ ; $1 \le m \le 40$），分别表示平台数和颜色数。

第二行 $n$ 个整数 $c_1, c_2, \dots, c_n$（$1 \le c_i \le m$）表示平台的颜色。

第三行 $m$ 个整数 $x_1, x_2, \dots, x_m$（$1 \le x_i \le 10^7$）表示激活每种颜色的所有平台花费的金币数量。

## 输出格式

一行一个整数，表示从激活的平台 $1$ 开始，跳过一些激活的平台，到达激活的平台 $n$ 需要花费的最小金币数量。

Translated by UID 781046.

## 样例 #1

### 输入

```
5 3
1 3 2 3 1
1 10 100
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 3
1 3 2 3 1
1 200 20
```

### 输出

```
21
```

## 样例 #3

### 输入

```
4 2
2 2 1 1
5 5
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 10
3 8 6 2 10 5 2 3 7 3
9 7 4 2 1 8 2 6 2 2
```

### 输出

```
15
```



---

---
title: "Graph Coloring (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1792F1
tag: ['动态规划 DP', '图论', '组合数学']
---

# Graph Coloring (easy version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^3 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```



---

---
title: "Group Division"
layout: "post"
diff: 省选/NOI-
pid: CF1916F
tag: ['图论']
---

# Group Division

## 题目描述

In the $ 31 $ st lyceum, there were two groups of olympiad participants: computer science and mathematics. The number of computer scientists was $ n_1 $ , and the number of mathematicians was $ n_2 $ . It is not known for certain who belonged to which group, but it is known that there were friendly connections between some pairs of people (these connections could exist between a pair of people from the same group or from different groups).

The connections were so strong that even if one person is removed along with all their friendly connections, any pair of people still remains acquainted either directly or through mutual friends.

 $ ^{\dagger} $ More formally, two people $ (x, y) $ are acquainted in the following case: there are people $ a_1, a_2, \ldots,a_n $ ( $ 1 \le a_i \le n_1 + n_2 $ ) such that the following conditions are simultaneously met:

 $ \bullet $ Person $ x $ is directly acquainted with $ a_1 $ .

 $ \bullet $ Person $ a_n $ is directly acquainted with $ y $ .

 $ \bullet $ Person $ a_i $ is directly acquainted with $ a_{i + 1} $ for any ( $ 1 \le i \le n - 1 $ ).

The teachers were dissatisfied with the fact that computer scientists were friends with mathematicians and vice versa, so they decided to divide the students into two groups in such a way that the following two conditions are met:

 $ \bullet $ There were $ n_1 $ people in the computer science group, and $ n_2 $ people in the mathematics group.

 $ \bullet $ Any pair of computer scientists should be acquainted (acquaintance involving mutual friends, who must be from the same group as the people in the pair, is allowed), the same should be true for mathematicians.

Help them solve this problem and find out who belongs to which group.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains three integers $ n_1 $ , $ n_2 $ , and $ m $ ( $ 1 \le n_1, n_2 \le 2000 $ , $ 1 \le m \le 5000 $ ). $ n_1 $ , $ n_2 $ are the sizes of the two groups described in the problem, and $ m $ is the number of friendly connections initially.

The following $ m $ lines describe the friendly connections: in the $ i $ -th ( $ 1 \le i \le m $ ) line, a pair of numbers $ (a, b) $ is given, which means that the person with number $ a $ is friends with the person with number $ b $ (and vice versa).

It is guaranteed that for each test case, all friendly connections are distinct.

It is guaranteed that the sum of $ n_1 + n_2 $ for all test cases does not exceed $ 2000 $ , and the sum of $ m $ for all test cases does not exceed $ 5000 $ .

It is also guaranteed that for each test case, a solution exists.

If there are several answers, print any of them.

## 输出格式

For each test case, output two lines.

In the first line, output $ n_1 $ distinct numbers $ a_i $ ( $ 1 \le a_i \le n_1 + n_2 $ ) — the people belonging to the first group.

In the second line, output $ n_2 $ distinct numbers $ b_i $ ( $ 1 \le b_i \le n_1 + n_2 $ ) — the people belonging to the second group.

All numbers must be distinct.

If there are several possible answers, print any one.

## 说明/提示

Consider the third test case. The division into groups looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1916F/61a6b120f4c32c6f1c36976b3b60c3a388509a79.png)  The students selected as computer scientists are colored in green, and those selected as mathematicians are colored in blue.Consider all pairs of computer scientists and how they are acquainted:

Pairs $ (4, 5), (4, 6) $ are directly acquainted.

Pair $ (5, 6) $ is acquainted through the computer scientist with number $ 4 $ .

Consider all pairs of mathematicians and how they are acquainted:

Pairs $ (1, 2), (2, 3) $ are directly acquainted.

Pair $ (1, 3) $ is acquainted through the mathematician with number $ 2 $ .

We conclude that any pair of people belonging to the same group is acquainted with each other, thus the division into two groups is correct.

## 样例 #1

### 输入

```
3
1 2 3
2 3
1 3
1 2
1 4 7
2 5
3 4
2 4
1 2
3 5
4 5
1 5
3 3 7
1 2
1 6
2 3
2 5
3 4
4 5
4 6
```

### 输出

```
3 
1 2 
5 
1 2 3 4 
4 5 6 
1 2 3
```



---

---
title: "Nene and the Passing Game"
layout: "post"
diff: 省选/NOI-
pid: CF1956F
tag: ['图论', '并查集']
---

# Nene and the Passing Game

## 题目描述

Nene is training her team as a basketball coach. Nene's team consists of $ n $ players, numbered from $ 1 $ to $ n $ . The $ i $ -th player has an arm interval $ [l_i,r_i] $ . Two players $ i $ and $ j $ ( $ i \neq j $ ) can pass the ball to each other if and only if $ |i-j|\in[l_i+l_j,r_i+r_j] $ (here, $ |x| $ denotes the absolute value of $ x $ ).

Nene wants to test the cooperation ability of these players. In order to do this, she will hold several rounds of assessment.

- In each round, Nene will select a sequence of players $ p_1,p_2,\ldots,p_m $ such that players $ p_i $ and $ p_{i+1} $ can pass the ball to each other for all $ 1 \le i < m $ . The length of the sequence $ m $ can be chosen by Nene. Each player can appear in the sequence $ p_1,p_2,\ldots,p_m $ multiple times or not appear in it at all.
- Then, Nene will throw a ball to player $ p_1 $ , player $ p_1 $ will pass the ball to player $ p_2 $ and so on... Player $ p_m $ will throw a ball away from the basketball court so it can no longer be used.

As a coach, Nene wants each of $ n $ players to appear in at least one round of assessment. Since Nene has to go on a date after school, Nene wants you to calculate the minimum number of rounds of assessment needed to complete the task.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2\cdot 10^5 $ ). The description of test cases follows.

The first line contains a single integer $ n $ ( $ 1 \le n \le 2\cdot 10^6 $ ) — the number of players.

The $ i $ -th of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1\leq l_i\leq r_i\leq n $ ) — the arm interval of the $ i $ -th player.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^6 $ .

## 输出格式

For each test case, output one integer — the minimum number of rounds of assessment Nene needs to complete her work.

## 说明/提示

In the first two test cases, Nene can host two rounds of assessment: one with $ p=[1] $ and one with $ p=[2] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

In the third test case, Nene can host two rounds of assessment: one with $ p=[1,3] $ and one with $ p=[2] $ . Player $ 1 $ can pass the ball to player $ 3 $ as $ |3-1|=2 \in [1+1,3+3] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
5
2
1 1
1 1
2
1 1
2 2
3
1 3
1 3
1 3
5
1 1
2 2
1 5
2 2
1 1
6
1 2
5 5
2 3
2 3
2 2
1 2
```

### 输出

```
2
2
2
1
3
```



---

---
title: "Two Paths"
layout: "post"
diff: 省选/NOI-
pid: CF36E
tag: ['图论', '连通块', '欧拉回路']
---

# Two Paths

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Once archaeologists found $ m $ mysterious papers, each of which had a pair of integers written on them. Ancient people were known to like writing down the indexes of the roads they walked along, as « $ a $ $ b $ » or « $ b $ $ a $ », where $ a,b $ are the indexes of two different cities joint by the road . It is also known that the mysterious papers are pages of two travel journals (those days a new journal was written for every new journey).

During one journey the traveler could walk along one and the same road several times in one or several directions but in that case he wrote a new entry for each time in his journal. Besides, the archaeologists think that the direction the traveler took on a road had no effect upon the entry: the entry that looks like « $ a $ $ b $ » could refer to the road from $ a $ to $ b $ as well as to the road from $ b $ to $ a $ .

The archaeologists want to put the pages in the right order and reconstruct the two travel paths but unfortunately, they are bad at programming. That’s where you come in. Go help them!

## 输入格式

The first input line contains integer $ m $ ( $ 1<=m<=10000 $ ). Each of the following $ m $ lines describes one paper. Each description consists of two integers $ a,b $ ( $ 1<=a,b<=10000 $ , $ a≠b $ ).

## 输出格式

In the first line output the number $ L_{1} $ . That is the length of the first path, i.e. the amount of papers in its description. In the following line output $ L_{1} $ space-separated numbers — the indexes of the papers that describe the first path. In the third and fourth lines output similarly the length of the second path $ L_{2} $ and the path itself. Both paths must contain at least one road, i.e. condition $ L_{1}&gt;0 $ and $ L_{2}&gt;0 $ must be met. The papers are numbered from $ 1 $ to $ m $ according to the order of their appearance in the input file. The numbers should be output in the order in which the traveler passed the corresponding roads. If the answer is not unique, output any.

If it’s impossible to find such two paths, output «-1».

Don’t forget that each paper should be used exactly once, i.e $ L_{1}+L_{2}=m $ .

## 样例 #1

### 输入

```
2
4 5
4 3

```

### 输出

```
1
2 
1
1

```

## 样例 #2

### 输入

```
1
1 2

```

### 输出

```
-1

```



---

---
title: "Circling Round Treasures"
layout: "post"
diff: 省选/NOI-
pid: CF375C
tag: ['图论', '状态合并', '最短路']
---

# Circling Round Treasures

## 题目描述

给你一个 $N \times M$ 的地图（$N,M \le 20$），地图上 `#` 表示障碍物，`B` 表示炸弹，数字表示宝藏序号（宝藏+炸弹个数 $\le 8$），每个宝藏有价值（$-200 \le v \le 200$），`S` 表示出发点。每次移动可以从一个格子移动到相邻格子（上下左右）。寻找一条路径从 `S` 出发再回到 `S` 的封闭路径，移动步数记为 $K$，这个路径所包围的宝藏价值总和记为 $V$，则这条路径的价值为 $V - K$。题目即是求可行的最大的路径价值，并且不能包围炸弹。

## 输入格式

第一行两个整数 $N, M$ 表示地图的长和宽 

接下来 $N$ 行，每行 $M$ 个字符，描述整个地图，地图只可能包含如下字符: 

字符 `B` 表示炸弹；

字符 `S` 表示起点,保证有且只有一个；

数字 $c$（$1 \sim 8$）代表宝藏标号，宝藏和炸弹加起来最多只有 $8$ 个；

字符 `.` 表示空白格；

字符 `#` 表示障碍物(墙)；

假设地图包含 $t$ 个宝藏，接下来 $t$ 行，每行一个整数 $v_i$（$-200 \le v_i \le 200$），依序表示第 $i$ 个宝藏的价值。

## 输出格式

一个整数，即能够获得的最大价值

感谢@xjdx 提供的翻译

## 样例 #1

### 输入

```
4 4
....
.S1.
....
....
10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 7
.......
.1###2.
.#...#.
.#.B.#.
.3...4.
..##...
......S
100
100
100
100

```

### 输出

```
364

```

## 样例 #3

### 输入

```
7 8
........
........
....1B..
.S......
....2...
3.......
........
100
-100
100

```

### 输出

```
0

```

## 样例 #4

### 输入

```
1 1
S

```

### 输出

```
0

```



---

---
title: "Mike and Fish"
layout: "post"
diff: 省选/NOI-
pid: CF547D
tag: ['图论', '欧拉回路', '二分图']
---

# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=2×10^{5} $ ).

The next $ n $ lines contain the information about the points, $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=2×10^{5} $ ), the $ i $ -th point coordinates.

It is guaranteed that there is at least one valid answer.

## 输出格式

Print the answer as a sequence of $ n $ characters 'r' (for red) or 'b' (for blue) where $ i $ -th character denotes the color of the fish in the $ i $ -th point.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2

```

### 输出

```
brrb

```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1

```

### 输出

```
brr

```



---

---
title: "Legacy"
layout: "post"
diff: 省选/NOI-
pid: CF786B
tag: ['线段树', '图论建模', '最短路']
---

# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 输入格式

The first line of input contains three integers $ n $ , $ q $ and $ s $ ( $ 1<=n,q<=10^{5} $ , $ 1<=s<=n $ ) — number of planets, number of plans and index of earth respectively.

The next $ q $ lines contain the plans. Each line starts with a number $ t $ , type of that plan ( $ 1<=t<=3 $ ). If $ t=1 $ then it is followed by three integers $ v $ , $ u $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v,u<=n $ , $ 1<=w<=10^{9} $ ). Otherwise it is followed by four integers $ v $ , $ l $ , $ r $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v<=n $ , $ 1<=l<=r<=n $ , $ 1<=w<=10^{9} $ ).

## 输出格式

In the first and only line of output print $ n $ integers separated by spaces. $ i $ -th of them should be minimum money to get from earth to $ i $ -th planet, or $ -1 $ if it's impossible to get to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17

```

### 输出

```
0 28 12 

```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16

```

### 输出

```
0 -1 -1 12 

```



---

---
title: "Exploration plan"
layout: "post"
diff: 省选/NOI-
pid: CF852D
tag: ['网络流', '图论建模', '最短路']
---

# Exploration plan

## 题目描述

The competitors of Bubble Cup X gathered after the competition and discussed what is the best way to get to know the host country and its cities.

After exploring the map of Serbia for a while, the competitors came up with the following facts: the country has $ V $ cities which are indexed with numbers from $ 1 $ to $ V $ , and there are $ E $ bi-directional roads that connect the cites. Each road has a weight (the time needed to cross that road). There are $ N $ teams at the Bubble Cup and the competitors came up with the following plan: each of the $ N $ teams will start their journey in one of the $ V $ cities, and some of the teams share the starting position.

They want to find the shortest time $ T $ , such that every team can move in these $ T $ minutes, and the number of different cities they end up in is at least $ K $ (because they will only get to know the cities they end up in). A team doesn't have to be on the move all the time, if they like it in a particular city, they can stay there and wait for the time to pass.

Please help the competitors to determine the shortest time $ T $ so it's possible for them to end up in at least $ K $ different cities or print -1 if that is impossible no matter how they move.

Note that there can exist multiple roads between some cities.

## 输入格式

The first line contains four integers: $ V $ , $ E $ , $ N $ and $ K\ (1<=V<=600,\ 1<=E<=20000,\ 1<=N<=min(V,200),\ 1<=K<=N) $ , number of cities, number of roads, number of teams and the smallest number of different cities they need to end up in, respectively.

The second line contains $ N $ integers, the cities where the teams start their journey.

Next $ E $ lines contain information about the roads in following format: $ A_{i}\ B_{i}\ T_{i}\ (1<=A_{i},B_{i}<=V,\ 1<=T_{i}<=10000) $ , which means that there is a road connecting cities $ A_{i} $ and $ B_{i} $ , and you need $ T_{i} $ minutes to cross that road.

## 输出格式

Output a single integer that represents the minimal time the teams can move for, such that they end up in at least $ K $ different cities or output -1 if there is no solution.

If the solution exists, result will be no greater than $ 1731311 $ .

## 说明/提示

Three teams start from city 5, and two teams start from city 2. If they agree to move for 3 minutes, one possible situation would be the following: Two teams in city 2, one team in city 5, one team in city 3 , and one team in city 1. And we see that there are four different cities the teams end their journey at.

## 样例 #1

### 输入

```
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3

```

### 输出

```
3
```



---

---
title: "Winning Strategy"
layout: "post"
diff: 省选/NOI-
pid: CF97C
tag: ['倍增', '背包 DP', '图论建模']
---

# Winning Strategy

## 题目描述

One university has just found out about a sport programming contest called ACM ICPC v2.0. This contest doesn't differ much from the well-known ACM ICPC, for example, the participants are not allowed to take part in the finals more than two times. However, there is one notable difference: the teams in the contest should consist of exactly $ n $ participants.

Having taken part in several ACM ICPC v2.0 finals and having not won any medals, the students and the university governors realized that it's high time they changed something about the preparation process. Specifically, as the first innovation it was decided to change the teams' formation process. Having spent considerable amount of time on studying the statistics of other universities' performance, they managed to receive some interesting information: the dependence between the probability of winning a medal and the number of team members that participated in the finals in the past. More formally, we know $ n+1 $ real numbers $ p_{0}<=p_{1}<=...<=p_{n} $ , where $ p_{i} $ is the probability of getting a medal on the finals if the team has $ i $ participants of previous finals, and other $ n-i $ participants arrived to the finals for the first time.

Despite such useful data, the university governors are unable to determine such team forming tactics that would provide the maximum probability of winning a medal at ACM ICPC v2.0 finals on average (we are supposed to want to provide such result to the far future and we are also supposed to have an endless supply of students). And how about you, can you offer such optimal tactic? At the first stage the university governors want to know the value of maximum average probability.

More formally, suppose that the university sends a team to the $ k $ -th world finals. The team has $ a_{k} $ participants of previous finals ( $ 0<=a_{k}<=n $ ). Since each person can participate in the finals no more than twice, the following condition must be true: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/b04e8ade7d007ad0702101fe8e64b638ac1fbbe2.png). Your task is to choose sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) so that the limit $ Ψ $ exists and it's value is maximal:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/cb2ffabcf620f29ef29bcdc17d35b1562b965de1.png)As ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) is an infinite sequence, you should only print the maximum value of the $ Ψ $ limit.

## 输入格式

The first line contains an integer $ n $ ( $ 3<=n<=100 $ ), $ n $ is the number of team participants. The second line contains $ n+1 $ real numbers with no more than 6 digits after decimal point $ p_{i} $ ( $ 0<=i<=n,0<=p_{i}<=1 $ ) — the probability of that the team will win a medal if it contains $ i $ participants who has already been on the finals. Also the condition $ p_{i}<=p_{i+1} $ should be fulfilled for all $ 0<=i<=n-1 $ .

## 输出格式

Print the only real number — the expected average number of medals won per year if the optimal strategy is used. The result may have absolute or relative error $ 10^{-6} $ .

## 说明/提示

In the second test, no matter what participants the team contains, it is doomed to be successful.

## 样例 #1

### 输入

```
3
0.115590 0.384031 0.443128 0.562356

```

### 输出

```
0.4286122500

```

## 样例 #2

### 输入

```
3
1 1 1 1

```

### 输出

```
0.9999999999

```



---

---
title: "Team Players"
layout: "post"
diff: 省选/NOI-
pid: CF985G
tag: ['图论', '容斥原理']
---

# Team Players

## 题目描述

### 题目大意

有 $n$ 个点和 $m$ 条边，点编号依次为 $0,1,\cdots, n-1$。

如果一个点的三元组 $(i,j,k)~(i<j<k)$ 两两**没有边**相连，那么它的贡献为 $A\times i+B\times j+C\times k$。

求出所有三元组的贡献和，答案对 $2^{64}$ 取模。

## 输入格式

第一行两个整数 $n, m$（$3 \le n \le 2\times 10 ^ 5, 0\le m \le 2\times 10 ^ 5$）。

接下来一行三个小于等于 $10 ^ 6$ 的正整数 $A, B, C$。

接下来 $m$ 行，每行两个整数 $u, v$ 表示 $u, v$ 间有一条边。

## 输出格式

一行一个整数表示答案。

## 样例 #1

### 输入

```
4 0
2 3 4

```

### 输出

```
64

```

## 样例 #2

### 输入

```
4 1
2 3 4
1 0

```

### 输出

```
38

```

## 样例 #3

### 输入

```
6 4
1 5 3
0 3
3 5
5 4
4 3

```

### 输出

```
164

```



---

