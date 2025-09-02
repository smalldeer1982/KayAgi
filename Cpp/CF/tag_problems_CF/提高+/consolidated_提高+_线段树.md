---
title: "One Occurrence"
layout: "post"
diff: 提高+/省选-
pid: CF1000F
tag: ['莫队', '线段树']
---

# One Occurrence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and $ q $ queries to it. $ i $ -th query is denoted by two integers $ l_i $ and $ r_i $ . For each query, you have to find any integer that occurs exactly once in the subarray of $ a $ from index $ l_i $ to index $ r_i $ (a subarray is a contiguous subsegment of an array). For example, if $ a = [1, 1, 2, 3, 2, 4] $ , then for query $ (l_i = 2, r_i = 6) $ the subarray we are interested in is $ [1, 2, 3, 2, 4] $ , and possible answers are $ 1 $ , $ 3 $ and $ 4 $ ; for query $ (l_i = 1, r_i = 2) $ the subarray we are interested in is $ [1, 1] $ , and there is no such element that occurs exactly once.

Can you answer all of the queries?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 5 \cdot 10^5 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ).

Then $ q $ lines follow, $ i $ -th line containing two integers $ l_i $ and $ r_i $ representing $ i $ -th query ( $ 1 \le l_i \le r_i \le n $ ).

## 输出格式

Answer the queries as follows:

If there is no integer such that it occurs in the subarray from index $ l_i $ to index $ r_i $ exactly once, print $ 0 $ . Otherwise print any such integer.

## 样例 #1

### 输入

```
6
1 1 2 3 2 4
2
2 6
1 2

```

### 输出

```
4
0

```



---

---
title: "Please, another Queries on Array?"
layout: "post"
diff: 提高+/省选-
pid: CF1114F
tag: ['线段树', '数论']
---

# Please, another Queries on Array?

## 题目描述

你有一个数组 $a_1,a_2,\cdots,a_n$。

现在你需要完成 $q$ 次操作，有以下两种操作形式：

1. `MULTIPLY l r x`，对于所有 $i(l\le i\le r)$，将 $a_i$ 乘上 $x$。

2. `TOTIENT l r`，求出 $\varphi(\prod_{i=l}^ra_i)$，对 $10^9+7$ 取模后的结果。其中 $\varphi$ 表示欧拉函数，$\varphi(n)$ 的定义为 $1\cdots n$ 中与 $n$ 互质的数的个数。


保证数据中至少有一次操作 $2$。

## 输入格式

输入的第一行有两个数 $n,q$，保证 $1\le n\le 4\times10^5,1\le q\le 2\times 10^5$，表示序列的长度以及询问的个数。

第二行是 $n$ 个数 $a_i$ 表示序列，满足 $1\le a_i\le 300$。

## 输出格式

对于每一个操作 $2$ 输出一行，表示答案。

## 说明/提示

在样例中：  
对于第 $1$ 个询问 $\varphi(1)=1$；  
对于第 $2$ 个询问 $\varphi(2)=1$；  
对于第 $3$ 个询问 $\varphi(6)=2$。

## 样例 #1

### 输入

```
4 4
5 9 1 2
TOTIENT 3 3
TOTIENT 3 4
MULTIPLY 4 4 3
TOTIENT 4 4

```

### 输出

```
1
1
2

```



---

---
title: "Linear Kingdom Races"
layout: "post"
diff: 提高+/省选-
pid: CF115E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Linear Kingdom Races

## 题目描述

你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有 $n$ 条连续的从左到右的道路。道路从左到右依次编号为从 $1$ 到 $n$，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润 $0$。**

输出你能获得的最大利润。

## 输入格式

第一行包括两个整数 $n,m$（$1 \leq n,m \leq 2\cdot 10^5$），分别表示道路的数量和比赛的数量。

接下来 $n$ 行，每行一个整数，表示这条道路修复需要的代价。

再接下来 $m$ 行，每行包括三个整数 $l_b,u_b,p$（$1 \leq l_b,u_b \leq n,1 \leq p \leq 10^9$），表示第 $b$ 场比赛需要使用道路 $[l_b,u_b]$，你会获得收益 $p$。

## 输出格式

输出一个整数，表示你能获得的最大利润。

## 说明/提示

在第一个样例中，最优解是修复 $1, 2, 3, 7$。你将会在第 $1, 2, 4$ 三场比赛中获得 $15$ 的收益。道路修理费用是 $11$，因此你的利润是 $4$。

## 样例 #1

### 输入

```
7 4
3
2
3
2
1
2
3
1 2 5
2 3 5
3 5 3
7 7 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 1
0
3
1 2 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 1
10
10
10
1 3 10

```

### 输出

```
0

```



---

---
title: "Boring Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1555E
tag: ['线段树', '排序', '双指针 two-pointer']
---

# Boring Segments

## 题目描述

You are given $ n $ segments on a number line, numbered from $ 1 $ to $ n $ . The $ i $ -th segments covers all integer points from $ l_i $ to $ r_i $ and has a value $ w_i $ .

You are asked to select a subset of these segments (possibly, all of them). Once the subset is selected, it's possible to travel between two integer points if there exists a selected segment that covers both of them. A subset is good if it's possible to reach point $ m $ starting from point $ 1 $ in arbitrary number of moves.

The cost of the subset is the difference between the maximum and the minimum values of segments in it. Find the minimum cost of a good subset.

In every test there exists at least one good subset.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 2 \le m \le 10^6 $ ) — the number of segments and the number of integer points.

Each of the next $ n $ lines contains three integers $ l_i $ , $ r_i $ and $ w_i $ ( $ 1 \le l_i < r_i \le m $ ; $ 1 \le w_i \le 10^6 $ ) — the description of the $ i $ -th segment.

In every test there exists at least one good subset.

## 输出格式

Print a single integer — the minimum cost of a good subset.

## 样例 #1

### 输入

```
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 10
1 10 23
```

### 输出

```
0
```



---

---
title: "William The Oblivious"
layout: "post"
diff: 提高+/省选-
pid: CF1609E
tag: ['线段树', '矩阵乘法']
---

# William The Oblivious

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609E/0e83a16b376d35306235c93a9bc0616a224b28a1.png)Before becoming a successful trader William got a university degree. During his education an interesting situation happened, after which William started to listen to homework assignments much more attentively. What follows is a formal description of the homework assignment as William heard it:

You are given a string $ s $ of length $ n $ only consisting of characters "a", "b" and "c". There are $ q $ queries of format ( $ pos, c $ ), meaning replacing the element of string $ s $ at position $ pos $ with character $ c $ . After each query you must output the minimal number of characters in the string, which have to be replaced, so that the string doesn't contain string "abc" as a subsequence. A valid replacement of a character is replacing it with "a", "b" or "c".

A string $ x $ is said to be a subsequence of string $ y $ if $ x $ can be obtained from $ y $ by deleting some characters without changing the ordering of the remaining characters.

## 输入格式

The first line contains two integers $ n $ and $ q $ $ (1 \le n, q \le 10^5) $ , the length of the string and the number of queries, respectively.

The second line contains the string $ s $ , consisting of characters "a", "b" and "c".

Each of the next $ q $ lines contains an integer $ i $ and character $ c $ $ (1 \le i \le n) $ , index and the value of the new item in the string, respectively. It is guaranteed that character's $ c $ value is "a", "b" or "c".

## 输出格式

For each query output the minimal number of characters that would have to be replaced so that the string doesn't contain "abc" as a subsequence.

## 说明/提示

Let's consider the state of the string after each query:

1. $ s =  $ "aaaaccccc". In this case the string does not contain "abc" as a subsequence and no replacements are needed.
2. $ s =  $ "aaabccccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "aaaaccccc". This string does not contain "abc" as a subsequence.
3. $ s =  $ "ababccccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ aaaaccccc". This string does not contain "abc" as a subsequence.
4. $ s =  $ "ababacccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaaaacccc". This string does not contain "abc" as a subsequence.
5. $ s =  $ "bbabacccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
6. $ s =  $ "bbababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
7. $ s =  $ "bbabcbccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbcbcbccc". This string does not contain "abc" as a subsequence.
8. $ s =  $ "baabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbbbcbccc". This string does not contain "abc" as a subsequence.
9. $ s =  $ "aaabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacccccc". This string does not contain "abc" as a subsequence.
10. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
11. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
12. $ s =  $ "aaababbcc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaababbbb". This string does not contain "abc" as a subsequence.

## 样例 #1

### 输入

```
9 12
aaabccccc
4 a
4 b
2 b
5 a
1 b
6 b
5 c
2 a
1 a
5 a
6 b
7 b
```

### 输出

```
0
1
2
2
1
2
1
2
2
2
2
2
```



---

---
title: "Anonymity Is Important"
layout: "post"
diff: 提高+/省选-
pid: CF1641C
tag: ['线段树', '二分']
---

# Anonymity Is Important

## 题目描述

In the work of a doctor, it is important to maintain the anonymity of clients and the results of tests. The test results are sent to everyone personally by email, but people are very impatient and they want to know the results right away.

That's why in the testing lab "De-vitro" doctors came up with an experimental way to report the results. Let's assume that $ n $ people took the tests in the order of the queue. Then the chief doctor Sam can make several statements, in each telling if there is a sick person among the people in the queue from $ l $ -th to $ r $ -th (inclusive), for some values $ l $ and $ r $ .

During the process, Sam will check how well this scheme works and will be interested in whether it is possible to find out the test result of $ i $ -th person from the information he announced. And if it can be done, then is that patient sick or not.

Help Sam to test his scheme.

## 输入格式

The first line contains two integers $ n $ , $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of people and the number of queries.

In each of the next $ q $ lines, the description of the query is given. The first number in the line is $ t $ ( $ t = 0 $ or $ t = 1 $ ) — the type of the query.

If $ t = 0 $ , the line contains three more integers $ l, r, x $ ( $ 1 \le l \le r \le n $ , $ x = 0 $ or $ x = 1 $ ). This query means that Sam tells that among the people in the queue from $ l $ -th to $ r $ -th (inclusive):

- there was at least one sick person, if $ x=1 $ ,
- there is no sick people, if $ x=0 $ .

If $ t = 1 $ , the line contains one more integer $ j $ ( $ 1 \le j \le n $ ) — the position of the patient in the queue, for which Sam wants to know the status.

All queries are correct, that means that there always exists an example of the queue of length $ n $ for which all reported results (statements from queries with $ t = 0 $ ) are true.

## 输出格式

After each Sam question (query with $ t = 1 $ ) print:

- "NO", if the patient is definitely not sick,
- "YES", if the patient is definitely sick.
- "N/A", if it is impossible to definitely identify the status of patient having the given information.

## 说明/提示

In the first test for the five first queries:

1. Initially Sam tells that people $ 4 $ , $ 5 $ are not sick.
2. In the next query Sam asks the status of the patient $ 5 $ . From the previous query, we know that the patient is definitely not sick.
3. In the next query Sam asks the status of the patient $ 6 $ . We don't know any information about that patient now.
4. After that Sam tells that there exists a sick patient among $ 4 $ , $ 5 $ , $ 6 $ .
5. In the next query Sam asks the status of the patient $ 6 $ . Now we can tell that this patient is definitely sick.

## 样例 #1

### 输入

```
6 9
0 4 5 0
1 5
1 6
0 4 6 1
1 6
0 2 5 1
0 2 2 0
1 3
1 2
```

### 输出

```
NO
N/A
YES
YES
NO
```



---

---
title: "Beard Graph"
layout: "post"
diff: 提高+/省选-
pid: CF165D
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# Beard Graph

## 题目描述

Let's define a non-oriented connected graph of $ n $ vertices and $ n-1 $ edges as a beard, if all of its vertices except, perhaps, one, have the degree of 2 or 1 (that is, there exists no more than one vertex, whose degree is more than two). Let us remind you that the degree of a vertex is the number of edges that connect to it.

Let each edge be either black or white. Initially all edges are black.

You are given the description of the beard graph. Your task is to analyze requests of the following types:

- paint the edge number $ i $ black. The edge number $ i $ is the edge that has this number in the description. It is guaranteed that by the moment of this request the $ i $ -th edge is white
- paint the edge number $ i $ white. It is guaranteed that by the moment of this request the $ i $ -th edge is black
- find the length of the shortest path going only along the black edges between vertices $ a $ and $ b $ or indicate that no such path exists between them (a path's length is the number of edges in it)

The vertices are numbered with integers from $ 1 $ to $ n $ , and the edges are numbered with integers from $ 1 $ to $ n-1 $ .

## 输入格式

The first line of the input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of vertices in the graph. Next $ n-1 $ lines contain edges described as the numbers of vertices $ v_{i} $ , $ u_{i} $ ( $ 1<=v_{i},u_{i}<=n $ , $ v_{i}≠u_{i} $ ) connected by this edge. It is guaranteed that the given graph is connected and forms a beard graph, and has no self-loops or multiple edges.

The next line contains an integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of requests. Next $ m $ lines contain requests in the following form: first a line contains an integer $ type $ , which takes values ​​from $ 1 $ to $ 3 $ , and represents the request type.

If $ type=1 $ , then the current request is a request to paint the edge black. In this case, in addition to number $ type $ the line should contain integer $ id $ ( $ 1<=id<=n-1 $ ), which represents the number of the edge to paint.

If $ type=2 $ , then the current request is a request to paint the edge white, its form is similar to the previous request.

If $ type=3 $ , then the current request is a request to find the distance. In this case, in addition to $ type $ , the line should contain two integers $ a $ , $ b $ ( $ 1<=a,b<=n $ , $ a $ can be equal to $ b $ ) — the numbers of vertices, the distance between which must be found.

The numbers in all lines are separated by exactly one space. The edges are numbered in the order in which they are given in the input.

## 输出格式

For each request to "find the distance between vertices $ a $ and $ b $ " print the result. If there is no path going only along the black edges between vertices $ a $ and $ b $ , then print "-1" (without the quotes). Print the results in the order of receiving the requests, separate the numbers with spaces or line breaks.

## 说明/提示

In the first sample vertices $ 1 $ and $ 2 $ are connected with edge number $ 1 $ , and vertices $ 2 $ and $ 3 $ are connected with edge number $ 2 $ . Before the repainting edge number $ 2 $ each vertex is reachable from each one along the black edges. Specifically, the shortest path between $ 1 $ and $ 3 $ goes along both edges.

If we paint edge number $ 2 $ white, vertex $ 3 $ will end up cut off from other vertices, that is, no path exists from it to any other vertex along the black edges.

## 样例 #1

### 输入

```
3
1 2
2 3
7
3 1 2
3 1 3
3 2 3
2 2
3 1 2
3 1 3
3 2 3

```

### 输出

```
1
2
1
1
-1
-1

```

## 样例 #2

### 输入

```
6
1 5
6 4
2 3
3 5
5 6
6
3 3 4
2 5
3 2 6
3 1 2
2 3
3 3 1

```

### 输出

```
3
-1
3
2

```



---

---
title: "Count the Trains"
layout: "post"
diff: 提高+/省选-
pid: CF1690G
tag: ['线段树']
---

# Count the Trains

## 题目描述

**【题目大意】**

铁轨上有 $n$ 节车厢，每节车厢在各自的引擎驱动下可以达到一个最高速度，记录在一个序列 $\{a_i\}$ 里. 车厢从左到右的编号依次为 $1$ 到 $n$.

现在让这些车厢向左尽可能快地开动，要求靠右的车厢实际速度不能超过靠左的车厢. 这样便会形成若干段速度一致的连续数节车厢，称这样的一段为**一节火车**. 例如序列 $a=[10,13,5,2,6]$ 对应的车厢的实际运行速度为 $[10,10,5,2,2]$，形成了 $3$ 节火车.

在车厢行驶时，依次收到了 $m$ 条形如 $k\ d$ 的信息，表示第 $k$ 节车厢的最高速度因引擎老化而下降了 $d$. 请维护这个过程中火车的总节数，每次收到信息后输出.

## 输入格式

输入的第一行为测试用例数 $t$. 每个测试用例的第 $1$ 行为空，第 $2$ 行为 $n$ 和 $m$，第 $3$ 行为序列 $\{a_i\}_{i=1}^n$，接下来 $m$ 行每行给出一条信息 $k_i\ d_i$.

## 输出格式

输出 $t$ 行对应 $t$ 个测试用例，每行用空格分隔 $m$ 个整数，表示收到每条信息后的火车节数.

## 说明/提示

所有数值均为整数.

$t∈[1,10^4];$

$n,m∈[1,10^5];$

$a_i∈[0,10^9](\forall i∈[1,n]);$

$k_j∈[1,n],\ d_j∈[0,a_{k_j}](\forall j∈[1,m])$.

所有测试用例的 $n$ 的总和及 $m$ 的总和均不超过 $10^5$.

## 样例 #1

### 输入

```
3

4 2
6 2 3 7
3 2
4 7

5 4
10 13 5 2 6
2 4
5 2
1 5
3 2

13 4
769 514 336 173 181 373 519 338 985 709 729 702 168
12 581
6 222
7 233
5 117
```

### 输出

```
3 4 
4 4 2 3 
5 6 6 5
```



---

---
title: "Permutation Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1696D
tag: ['贪心', '线段树', '分治']
---

# Permutation Graph

## 题目描述

给出一个 $1$ 到 $n$ 的排列 $ [a_1,a_2,\dots,a_n] $ 。对于 $1\le i < j\le n$ ，记 $ \operatorname{mn}(i,j) $ 为 $\min\limits_{k=i}^j a_k$ ，记  $ \operatorname{mx}(i,j) $ 为 $ \max\limits_{k=i}^j a_k $ 。

有一张 $n$ 个点的无向图，点的编号为 $1$ 到 $n$ 。对于每一对整数 $ 1\le i<j\le n $ ，如果同时满足 $ \operatorname{mn}(i,j)=a_i $ 且 $ \operatorname{mx}(i,j)=a_j $ ，或同时满足 $ \operatorname{mn}(i,j)=a_j $ 和 $ \operatorname{mx}(i,j)=a_i $ ，那么就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。

询问这张图中从 $1$ 到 $n$ 的最短路的长度。可以证明 $1$ 和 $n$ 总是连通，所以最短路总是存在。

## 输入格式

每个数据点包含多组数据。第一行一个整数 $t$ ( $ 1 \le t \le 5\cdot 10^4 $ ) 表示测试组数

对于每组数据，第一行一个整数 $n$ ( $ 1\le n\le 2.5\cdot 10^5 $ ) 。

第二行包含 $n$ 个整数 $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1\le a_i\le n $ ) 。保证 $a$ 是 $ 1 $ , $ 2 $ , $ \dots $ , $ n $ 的一个排列。

保证所有数据的 $n$ 之和不超过 $ 5\cdot 10^5 $

## 输出格式

对于每组数据，输出一个整数表示从 $1$ 到 $n$ 的最短路长度

## 样例 #1

### 输入

```
5
1
1
2
1 2
5
1 4 2 3 5
5
2 1 5 3 4
10
7 4 8 1 6 10 3 5 2 9
```

### 输出

```
0
1
1
4
6
```



---

---
title: "Points"
layout: "post"
diff: 提高+/省选-
pid: CF1701F
tag: ['线段树', '组合数学']
---

# Points

## 题目描述

若 $ i < j < k $ 且 $ k - i \le d $ 那么在数轴上的三个点 $ i $ , $ j $ 与 $ k $ 是美丽的一组点。 $d$ 是“定义三元组是否美丽的参数”。

在一个初始为空的数轴上给出一些点，你需要：

- 增加一个点
- 移除一个点
- 计算美丽的点的组数

## 输入格式

第一行两个整数 $q$ 和 $d$ ，分别代表查询数和定义三元组是否美丽的参数。

第二行 $q$ 个整数 $ a_1, a_2, \dots, a_q $ 整数 $a_i$ 表示第 $i$ 个查询，对于每一次查询：
- 如果存在点 $a_i$ 那么移除它，否则将他加入到数轴。
- 输出当前美丽的点的组数

## 输出格式

一共 $q$ 行，表示 $q$ 次查询。对于每次查询，输出一个整数，表示美丽的点的组数。

## 说明/提示

对于 $100\%$ 的数据， $1\le q , d\le 2\cdot 10^5$ $ 1 \le a_i \le 2 \cdot 10^5 $

## 样例 #1

### 输入

```
7 5
8 5 3 2 1 5 6
```

### 输出

```
0
0
1
2
5
1
5
```



---

---
title: "Mark and Professor Koro"
layout: "post"
diff: 提高+/省选-
pid: CF1705E
tag: ['线段树', '二分', '位运算']
---

# Mark and Professor Koro

## 题目描述

After watching a certain anime before going to sleep, Mark dreams of standing in an old classroom with a blackboard that has a sequence of $ n $ positive integers $ a_1, a_2,\dots,a_n $ on it.

Then, professor Koro comes in. He can perform the following operation:

- select an integer $ x $ that appears at least $ 2 $ times on the board,
- erase those $ 2 $ appearances, and
- write $ x+1 $ on the board.

Professor Koro then asks Mark the question, "what is the maximum possible number that could appear on the board after some operations?"

Mark quickly solves this question, but he is still slower than professor Koro. Thus, professor Koro decides to give Mark additional challenges. He will update the initial sequence of integers $ q $ times. Each time, he will choose positive integers $ k $ and $ l $ , then change $ a_k $ to $ l $ . After each update, he will ask Mark the same question again.

Help Mark answer these questions faster than Professor Koro!

Note that the updates are persistent. Changes made to the sequence $ a $ will apply when processing future updates.

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2\leq n\leq 2\cdot 10^5 $ , $ 1\leq q\leq 2\cdot 10^5 $ ) — the length of the sequence $ a $ and the number of updates, respectively.

The second line contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1\leq a_i\leq 2\cdot 10^5 $ )

Then, $ q $ lines follow, each consisting of two integers $ k $ and $ l $ ( $ 1\leq k\leq n $ , $ 1\leq l\leq 2\cdot 10^5 $ ), telling to update $ a_k $ to $ l $ .

## 输出格式

Print $ q $ lines. The $ i $ -th line should consist of a single integer — the answer after the $ i $ -th update.

## 说明/提示

In the first example test, the program must proceed through $ 4 $ updates.

The sequence after the first update is $ [2,3,2,4,5] $ . One sequence of operations that achieves the number $ 6 $ the following.

- Initially, the blackboard has numbers $ [2,3,2,4,5] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,5,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [4,5,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [5,\color{red}{5}] $ .
- Erase two copies of $ 5 $ and write $ 6 $ , yielding $ [\color{red}{6}] $ .

Then, in the second update, the array is changed to $ [2,3,2,4,3] $ . This time, Mark cannot achieve $ 6 $ . However, one sequence that Mark can use to achieve $ 5 $ is shown below.

- Initially, the blackboard has $ [2,3,2,4,3] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,3,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [3,4,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [3,\color{red}{5}] $ .

In the third update, the array is changed to $ [2,3,2,1,3] $ . One way to achieve $ 4 $ is shown below.

- Initially, the blackboard has $ [2,3,2,1,3] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [2,2,1,\color{red}{4}] $ .

## 样例 #1

### 输入

```
5 4
2 2 2 4 5
2 3
5 3
4 1
1 4
```

### 输出

```
6
5
4
5
```

## 样例 #2

### 输入

```
2 1
200000 1
2 200000
```

### 输出

```
200001
```



---

---
title: "Chopping Carrots (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1706D2
tag: ['数学', '线段树', '双指针 two-pointer']
---

# Chopping Carrots (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 输入格式

第一行包括一个整数 $t$（$ 1 \le t \le 100 $），表示接下来测试组的数量。

对于每一个测试组，第一行包括两个整数 $n$ 和 $k$（$ 1 \le n, k \le 10^5 $）。

对于每一个测试组，第二行包括 $n$ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 10^5 $）。

保证 $\sum n \le 10^5$。

## 输出格式

对于每一个测试组，输出一个整数，表示满足上述条件的数组 $p$ 的花费的最小值。

## 样例 #1

### 样例输入 #1

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 样例输出 #1

```
2
0
13
1
4
7
0
```

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 输出

```
2
0
13
1
4
7
0
```



---

---
title: "Qpwoeirut and Vertices"
layout: "post"
diff: 提高+/省选-
pid: CF1706E
tag: ['线段树', 'Kruskal 重构树', 'ST 表', '整体二分']
---

# Qpwoeirut and Vertices

## 题目描述

You are given a connected undirected graph with $ n $ vertices and $ m $ edges. Vertices of the graph are numbered by integers from $ 1 $ to $ n $ and edges of the graph are numbered by integers from $ 1 $ to $ m $ .

Your task is to answer $ q $ queries, each consisting of two integers $ l $ and $ r $ . The answer to each query is the smallest non-negative integer $ k $ such that the following condition holds:

- For all pairs of integers $ (a, b) $ such that $ l\le a\le b\le r $ , vertices $ a $ and $ b $ are reachable from one another using only the first $ k $ edges (that is, edges $ 1, 2, \ldots, k $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ q $ ( $ 2\le n\le 10^5 $ , $ 1\le m, q\le 2\cdot 10^5 $ ) — the number of vertices, edges, and queries respectively.

Each of the next $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ ) — ends of the $ i $ -th edge.

It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1\le l\le r\le n $ ) — descriptions of the queries.

It is guaranteed that that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print $ q $ integers — the answers to the queries.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/8251767c792df96adbc7d8ce1ae896aca10bb309.png)Graph from the first test case. The integer near the edge is its number.In the first test case, the graph contains $ 2 $ vertices and a single edge connecting vertices $ 1 $ and $ 2 $ .

In the first query, $ l=1 $ and $ r=1 $ . It is possible to reach any vertex from itself, so the answer to this query is $ 0 $ .

In the second query, $ l=1 $ and $ r=2 $ . Vertices $ 1 $ and $ 2 $ are reachable from one another using only the first edge, through the path $ 1 \longleftrightarrow 2 $ . It is impossible to reach vertex $ 2 $ from vertex $ 1 $ using only the first $ 0 $ edges. So, the answer to this query is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/af65cd675bd4523d08062174925e59fd8900ee43.png)Graph from the second test case. The integer near the edge is its number.In the second test case, the graph contains $ 5 $ vertices and $ 5 $ edges.

In the first query, $ l=1 $ and $ r=4 $ . It is enough to use the first $ 3 $ edges to satisfy the condition from the statement:

- Vertices $ 1 $ and $ 2 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 $ (edge $ 1 $ ).
- Vertices $ 1 $ and $ 3 $ are reachable from one another through the path $ 1 \longleftrightarrow 3 $ (edge $ 2 $ ).
- Vertices $ 1 $ and $ 4 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 1 $ and $ 3 $ ).
- Vertices $ 2 $ and $ 3 $ are reachable from one another through the path $ 2 \longleftrightarrow 1 \longleftrightarrow 3 $ (edges $ 1 $ and $ 2 $ ).
- Vertices $ 2 $ and $ 4 $ are reachable from one another through the path $ 2 \longleftrightarrow 4 $ (edge $ 3 $ ).
- Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ).

If we use less than $ 3 $ of the first edges, then the condition won't be satisfied. For example, it is impossible to reach vertex $ 4 $ from vertex $ 1 $ using only the first $ 2 $ edges. So, the answer to this query is $ 3 $ .

In the second query, $ l=3 $ and $ r=4 $ . Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ). If we use any fewer of the first edges, nodes $ 3 $ and $ 4 $ will not be reachable from one another.

## 样例 #1

### 输入

```
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3
```

### 输出

```
0 1 
3 3 0 5 5 
2
```



---

---
title: "Intersection and Union"
layout: "post"
diff: 提高+/省选-
pid: CF1743F
tag: ['动态规划 DP', '数学', '线段树']
---

# Intersection and Union

## 题目描述

You are given $ n $ segments on the coordinate axis. The $ i $ -th segment is $ [l_i, r_i] $ . Let's denote the set of all integer points belonging to the $ i $ -th segment as $ S_i $ .

Let $ A \cup B $ be the union of two sets $ A $ and $ B $ , $ A \cap B $ be the intersection of two sets $ A $ and $ B $ , and $ A \oplus B $ be the symmetric difference of $ A $ and $ B $ (a set which contains all elements of $ A $ and all elements of $ B $ , except for the ones that belong to both sets).

Let $ [\mathbin{op}_1, \mathbin{op}_2, \dots, \mathbin{op}_{n-1}] $ be an array where each element is either $ \cup $ , $ \oplus $ , or $ \cap $ . Over all $ 3^{n-1} $ ways to choose this array, calculate the sum of the following values:

 $ $$$|(((S_1\ \mathbin{op}_1\ S_2)\ \mathbin{op}_2\ S_3)\ \mathbin{op}_3\ S_4)\ \dots\ \mathbin{op}_{n-1}\ S_n| $ $ </p><p>In this expression,  $ |S| $  denotes the size of the set  $ S$$$.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ).

Then, $ n $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 0 \le l_i \le r_i \le 3 \cdot 10^5 $ ).

## 输出格式

Print one integer — the sum of $ |(((S_1\ \mathbin{op}_1\ S_2)\ \mathbin{op}_2\ S_3)\ \mathbin{op}_3\ S_4)\ \dots\ \mathbin{op}_{n-1}\ S_n| $ over all possible ways to choose $ [\mathbin{op}_1, \mathbin{op}_2, \dots, \mathbin{op}_{n-1}] $ . Since the answer can be huge, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
3 5
4 8
2 2
1 9
```

### 输出

```
162
```

## 样例 #2

### 输入

```
4
1 9
3 5
4 8
2 2
```

### 输出

```
102
```



---

---
title: "Bracket Cost"
layout: "post"
diff: 提高+/省选-
pid: CF1750E
tag: ['线段树', '树状数组']
---

# Bracket Cost

## 题目描述

Daemon Targaryen decided to stop looking like a Metin2 character. He turned himself into the most beautiful thing, a bracket sequence.

For a bracket sequence, we can do two kind of operations:

- Select one of its substrings $ ^\dagger $ and cyclic shift it to the right. For example, after a cyclic shift to the right, "(())" will become ")(()";
- Insert any bracket, opening '(' or closing ')', wherever you want in the sequence.

We define the cost of a bracket sequence as the minimum number of such operations to make it balanced $ ^\ddagger $ .

Given a bracket sequence $ s $ of length $ n $ , find the sum of costs across all its $ \frac{n(n+1)}{2} $ non-empty substrings. Note that for each substring we calculate the cost independently.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the bracket sequence.

The second line of each test case contains a string $ s $ , consisting only of characters '(' and ')', of length $ n $ — the bracket sequence.

It is guaranteed that sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the sum of costs of all substrings of $ s $ .

## 说明/提示

In the first test case, there is the only substring ")". Its cost is $ 1 $ because we can insert '(' to the beginning of this substring and get a string "()", that is a balanced string.

In the second test case, the cost of each substring of length one is $ 1 $ . The cost of a substring ")(" is $ 1 $ because we can cyclically shift it to right and get a string "()". The cost of strings ")()" and "()(" is $ 1 $ because its enough to insert one bracket to each of them. The cost of substring ")()(" is $ 1 $ because we can cyclically shift it to right and get a string "()()". So there are $ 4 + 2 + 2 + 1 = 9 $ substring of cost $ 1 $ and $ 1 $ substring of cost $ 0 $ . So the sum of the costs is $ 9 $ .

In the third test case,

- "(", the cost is $ 1 $ ;
- "()", the cost is $ 0 $ ;
- "())", the cost is $ 1 $ ;
- ")", the cost is $ 1 $ ;
- "))", the cost is $ 2 $ ;
- ")", the cost is $ 1 $ .

So the sum of the costs is $ 6 $ .

## 样例 #1

### 输入

```
5
1
)
4
)()(
3
())
5
(((((
10
)(())))())
```

### 输出

```
1
9
6
35
112
```



---

---
title: "Monsters (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1784C
tag: ['贪心', '线段树']
---

# Monsters (hard version)

## 题目描述

This is the hard version of the problem. In this version, you need to find the answer for every prefix of the monster array.

In a computer game, you are fighting against $ n $ monsters. Monster number $ i $ has $ a_i $ health points, all $ a_i $ are integers. A monster is alive while it has at least $ 1 $ health point.

You can cast spells of two types:

1. Deal $ 1 $ damage to any single alive monster of your choice.
2. Deal $ 1 $ damage to all alive monsters. If at least one monster dies (ends up with $ 0 $ health points) as a result of this action, then repeat it (and keep repeating while at least one monster dies every time).

Dealing $ 1 $ damage to a monster reduces its health by $ 1 $ .

Spells of type 1 can be cast any number of times, while a spell of type 2 can be cast at most once during the game.

For every $ k = 1, 2, \ldots, n $ , answer the following question. Suppose that only the first $ k $ monsters, with numbers $ 1, 2, \ldots, k $ , are present in the game. What is the smallest number of times you need to cast spells of type 1 to kill all $ k $ monsters?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case consists of two lines. The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of monsters.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — monsters' health points.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers. The $ k $ -th of these integers must be equal to the smallest number of times you need to cast spells of type 1 to kill all $ k $ monsters, if only monsters with numbers $ 1, 2, \ldots, k $ are present in the game.

## 说明/提示

In the first test case, for $ k = n $ , the initial health points of the monsters are $ [3, 1, 2] $ . It is enough to cast a spell of type 2:

- Monsters' health points change to $ [2, 0, 1] $ . Since monster number $ 2 $ dies, the spell is repeated.
- Monsters' health points change to $ [1, 0, 0] $ . Since monster number $ 3 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ .

Since it is possible to use no spells of type 1 at all, the answer is $ 0 $ .

In the second test case, for $ k = n $ , the initial health points of the monsters are $ [4, 1, 5, 4, 1, 1] $ . Here is one of the optimal action sequences:

- Using a spell of type 1, deal $ 1 $ damage to monster number $ 1 $ . Monsters' health points change to $ [3, 1, 5, 4, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ . Monsters' health points change to $ [3, 1, 5, 3, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ again. Monsters' health points change to $ [3, 1, 5, 2, 1, 1] $ .
- Use a spell of type 2:
  - Monsters' health points change to $ [2, 0, 4, 1, 0, 0] $ . Since monsters number $ 2 $ , $ 5 $ , and $ 6 $ die, the spell is repeated.
  - Monsters' health points change to $ [1, 0, 3, 0, 0, 0] $ . Since monster number $ 4 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 2, 0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 1, 0, 0, 0] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 3 $ . Monsters' health points change to $ [0, 0, 0, 0, 0, 0] $ .

Spells of type 1 are cast $ 4 $ times in total. It can be shown that this is the smallest possible number.

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1
```

### 输出

```
2 1 0
3 2 4 4 4 4
```



---

---
title: "Hot Start Up (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1799D2
tag: ['动态规划 DP', '线段树']
---

# Hot Start Up (hard version)

## 题目描述

This is a hard version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 10^5 $ ).

The first line of each test case contains $ n $ and $ k $ ( $ 1 \le n, k \le 3 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le k $ ).

The third line of each test case contains $ k $ integers $ cold_1, cold_2, \ldots, cold_k $ ( $ 1 \le cold_i \le 10^9 $ ).

The fourth line of each test case contains $ k $ integers $ hot_1, hot_2, \ldots, hot_k $ ( $ 1 \le hot_i \le cold_i $ ).

It is guaranteed the sum of $ n $ and the sum of $ k $ over all test cases do not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print the minimum time needed to run all programs in the given order.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5
```

### 输出

```
6
11
301
225
8
4999999996
11
6
63
```



---

---
title: "Rollbacks (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1858E1
tag: ['可持久化线段树']
---

# Rollbacks (Easy Version)

## 题目描述

This is an easy version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 输入格式

The first line contains an integer $ q $ ( $ 1 \leq q \leq 10^6 $ ) — the number of queries.

The next $ q $ lines contain the queries as described above.

It is guaranteed that

- in the queries of the first type, $ 1 \le x \le 10^6 $ ;
- in the queries of the second type, $ k \ge 1 $ and $ k $ does not exceed the current length of the array $ a $ ;
- at the moment of the queries of the third type, there is at least one query of the first or of the second type that can be rolled back.

It is also guaranteed that the number of queries of the fourth type (?) does not exceed $ 10^5 $ .

## 输出格式

For each query of the fourth type output one integer — the number of distinct elements in array $ a $ at the moment of query.

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?
```

### 输出

```
2
1
1
```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?
```

### 输出

```
2
0
```



---

---
title: "One-X"
layout: "post"
diff: 提高+/省选-
pid: CF1905E
tag: ['递推', '线段树']
---

# One-X

## 题目描述

In this sad world full of imperfections, ugly segment trees exist.

A segment tree is a tree where each node represents a segment and has its number. A segment tree for an array of $ n $ elements can be built in a recursive manner. Let's say function $ \operatorname{build}(v,l,r) $ builds the segment tree rooted in the node with number $ v $ and it corresponds to the segment $ [l,r] $ .

Now let's define $ \operatorname{build}(v,l,r) $ :

- If $ l=r $ , this node $ v $ is a leaf so we stop adding more edges
- Else, we add the edges $ (v, 2v) $ and $ (v, 2v+1) $ . Let $ m=\lfloor \frac{l+r}{2} \rfloor $ . Then we call $ \operatorname{build}(2v,l,m) $ and $ \operatorname{build}(2v+1,m+1,r) $ .

So, the whole tree is built by calling $ \operatorname{build}(1,1,n) $ .

Now Ibti will construct a segment tree for an array with $ n $ elements. He wants to find the sum of $ \operatorname{lca}^\dagger(S) $ , where $ S $ is a non-empty subset of leaves. Notice that there are exactly $ 2^n - 1 $ possible subsets. Since this sum can be very large, output it modulo $ 998\,244\,353 $ .

 $ ^\dagger\operatorname{lca}(S) $ is the number of the least common ancestor for the nodes that are in $ S $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^{18} $ ) — the length of the array for which the segment tree is built.

## 输出格式

For each test case, output a single integer — the required sum modulo $ 998\,244\,353 $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905E/fbb65ae036ad668eae2530f36a15f5bf19bb463d.png)In the first test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{2\})=2 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{2,3\})=1 $ .

Thus, the answer is $ 2+3+1=6 $ .

In the second test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{4\})=4 $ ;
- $ \operatorname{lca}(\{5\})=5 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{4,5\})=2 $ ;
- $ \operatorname{lca}(\{4,3\})=1 $ ;
- $ \operatorname{lca}(\{5,3\})=1 $ ;
- $ \operatorname{lca}(\{4,5,3\})=1 $ ;

Thus, the answer is $ 4+5+3+2+1+1+1=17 $ .

## 样例 #1

### 输入

```
5
2
3
4
5
53278
```

### 输出

```
6
17
36
69
593324855
```



---

---
title: "Maximize The Value"
layout: "post"
diff: 提高+/省选-
pid: CF1906F
tag: ['线段树']
---

# Maximize The Value

## 题目描述

You are given a one-based array consisting of $ N $ integers: $ A_1, A_2, \cdots, A_N $ . Initially, the value of each element is set to $ 0 $ .

There are $ M $ operations (numbered from $ 1 $ to $ M $ ). Operation $ i $ is represented by $ \langle L_i, R_i, X_i \rangle $ . If operation $ i $ is executed, all elements $ A_j $ for $ L_i \leq j \leq R_i $ will be increased by $ X_i $ .

You have to answer $ Q $ independent queries. Each query is represented by $ \langle K, S, T \rangle $ which represents the following task. Choose a range $ [l, r] $ satisfying $ S \leq l \leq r \leq T $ , and execute operations $ l, l + 1, \dots, r $ . The answer to the query is the maximum value of $ A_K $ after the operations are executed among all possible choices of $ l $ and $ r $ .

## 输入格式

The first line consists of two integers $ N $ $ M $ ( $ 1 \leq N, M \leq 100\,000 $ ).

Each of the next $ M $ lines consists of three integers $ L_i $ $ R_i $ $ X_i $ ( $ 1 \leq L_i \leq R_i \leq N; -100\,000 \leq X_i \leq 100\,000 $ ).

The following line consists of an integer $ Q $ ( $ 1 \leq Q \leq 100\,000 $ ).

Each of the next $ Q $ lines consists of three integers $ K $ $ S $ $ T $ ( $ 1 \leq K \leq N; 1 \leq S \leq T \leq M $ ).

## 输出格式

For each query, output in a single line, an integer which represent the answer of the query.

## 说明/提示

Explanation for the sample input/output #1

For query $ 1 $ , one of the solutions is to execute operation $ 4 $ and $ 5 $ .

For query $ 2 $ , one of the solutions is to execute operation $ 4 $ , $ 5 $ , and $ 6 $ .

For query $ 3 $ , the only solution is to execute operation $ 3 $ .

For query $ 4 $ , the only solution is to execute operation $ 1 $ .

For query $ 6 $ , the only solution is to execute operation $ 2 $ .

## 样例 #1

### 输入

```
2 6
1 1 -50
1 2 -20
2 2 -30
1 1 60
1 2 40
2 2 10
5
1 1 6
2 1 6
1 1 3
2 1 3
1 1 2
```

### 输出

```
100
50
0
0
-20
```

## 样例 #2

### 输入

```
5 3
1 3 3
2 4 -2
3 5 3
6
1 1 3
2 1 3
3 1 3
3 2 3
2 2 3
2 2 2
```

### 输出

```
3
3
4
3
0
-2
```



---

---
title: "Happy Life in University"
layout: "post"
diff: 提高+/省选-
pid: CF1916E
tag: ['线段树', '深度优先搜索 DFS']
---

# Happy Life in University

## 题目描述

Egor and his friend Arseniy are finishing school this year and will soon enter university. And since they are very responsible guys, they have started preparing for admission already.

First of all, they decided to take care of where they will live for the long four years of study, and after visiting the university's website, they found out that the university dormitory can be represented as a root tree with $ n $ vertices with the root at vertex $ 1 $ . In the tree, each vertex represents a recreation with some type of activity $ a_i $ . The friends need to choose $ 2 $ recreations (not necessarily different) in which they will settle. The guys are convinced that the more the value of the following function $ f(u, v) = diff(u, lca(u, v)) \cdot diff(v, lca(u, v)) $ , the more fun their life will be. Help Egor and Arseniy and find the maximum value of $ f(u, v) $ among all pairs of recreations!

 $ ^{\dagger} diff(u, v) $ — the number of different activities listed on the simple path from vertex $ u $ to vertex $ v $ .

 $ ^{\dagger} lca(u, v) $ — a vertex $ p $ such that it is at the maximum distance from the root and is a parent of both vertex $ u $ and vertex $ v $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^{5} $ ).

The second line of each test case contains $ {n - 1} $ integers $ p_2, p_3, \ldots,p_n $ ( $ 1 \le p_i \le i - 1 $ ), where $ p_i $ — the parent of vertex $ i $ .

The third line of each test case contains $ {n} $ integers $ a_1, a_2, \ldots,a_n $ ( $ 1 \le a_i \le n $ ), where $ a_i $ — the number of the activity located at vertex $ i $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of $ f(u, v) $ for all pairs of recreations $ (u, v) $ .

## 说明/提示

Consider the fourth test case. The tree has the following structure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1916E/310c7cd8a93a46df2248a6a8b87aa515f4626d82.png)  All recreations are colored. The same colors mean that the activities in the recreations match. Consider the pair of vertices $ (11, 12) $ , $ lca(11, 12) = 1 $ . Write down all activities on the path from $ 11 $ to $ 1 $ — $ [11, 5, 1, 11] $ , among them there are $ 3 $ different activities, so $ diff(11, 1) = 3 $ . Also write down all activities on the path from $ 12 $ to $ 1 $ — $ [7, 8, 2, 11] $ , among them there are $ 4 $ different activities, so $ diff(12, 1) = 4 $ . We get that $ f(11, 12) = diff(12, 1) \cdot diff(11, 1) = 4 \cdot 3 = 12 $ , which is the answer for this tree. It can be shown that a better answer is impossible to obtain.

## 样例 #1

### 输入

```
4
2
1
1 2
7
1 1 2 2 3 3
6 5 2 3 6 5 6
13
1 1 1 2 2 2 3 3 4 5 6 6
2 2 2 1 4 9 7 2 5 2 1 11 2
12
1 1 1 2 2 3 4 4 7 7 6
11 2 1 11 12 8 5 8 8 5 11 7
```

### 输出

```
2
9
9
12
```



---

---
title: "Wine Factory (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1919F1
tag: ['线段树', '前缀和']
---

# Wine Factory (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

There are three arrays $ a $ , $ b $ and $ c $ . $ a $ and $ b $ have length $ n $ and $ c $ has length $ n-1 $ . Let $ W(a,b,c) $ denote the liters of wine created from the following process.

Create $ n $ water towers. The $ i $ -th water tower initially has $ a_i $ liters of water and has a wizard with power $ b_i $ in front of it. Furthermore, for each $ 1 \le i \le n - 1 $ , there is a valve connecting water tower $ i $ to $ i + 1 $ with capacity $ c_i $ .

For each $ i $ from $ 1 $ to $ n $ in this order, the following happens:

1. The wizard in front of water tower $ i $ removes at most $ b_i $ liters of water from the tower and turns the removed water into wine.
2. If $ i \neq n $ , at most $ c_i $ liters of the remaining water left in water tower $ i $ flows through the valve into water tower $ i + 1 $ .

There are $ q $ updates. In each update, you will be given integers $ p $ , $ x $ , $ y $ and $ z $ and you will update $ a_p := x $ , $ b_p := y $ and $ c_p := z $ . After each update, find the value of $ W(a,b,c) $ . Note that previous updates to arrays $ a $ , $ b $ and $ c $ persist throughout future updates.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 5\cdot 10^5 $ , $ 1 \le q \le 5\cdot 10^5 $ ) — the number of water towers and the number of updates.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the number of liters of water in water tower $ i $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i \le 10^9 $ ) — the power of the wizard in front of water tower $ i $ .

The fourth line contains $ n - 1 $ integers $ c_1, c_2, \ldots, c_{n - 1} $ ( $ c_i \color{red}{=} 10^{18} $ ) — the capacity of the pipe connecting water tower $ i $ to $ i + 1 $ .

Each of the next $ q $ lines contains four integers $ p $ , $ x $ , $ y $ and $ z $ ( $ 1 \le p \le n $ , $ 0 \le x, y \le 10^9 $ , $ z \color{red}{=} 10^{18} $ ) — the updates done to arrays $ a $ , $ b $ and $ c $ .

Note that $ c_n $ does not exist, so the value of $ z $ does not matter when $ p = n $ .

## 输出格式

Print $ q $ lines, each line containing a single integer representing $ W(a, b, c) $ after each update.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 2 $ liters of water flows into tower 4.
- When $ i = 4 $ , there are $ 5 $ liters of water in tower 4. All $ 5 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 5 = 12 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 9 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 7 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 10 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 8 = 12 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 6 $ liters of water in tower 3 and $ 0 $ liters of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 9 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 8 = 10 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
1000000000000000000 1000000000000000000 1000000000000000000
4 3 8 1000000000000000000
2 5 1 1000000000000000000
3 0 0 1000000000000000000
```

### 输出

```
12
12
10
```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000
5 4 9 1000000000000000000
1 1 1 1000000000000000000
2 7 4 1000000000000000000
4 1 1 1000000000000000000
1 8 3 1000000000000000000
```

### 输出

```
34
25
29
21
27
```



---

---
title: "Space Harbour"
layout: "post"
diff: 提高+/省选-
pid: CF1924B
tag: ['线段树', '树状数组']
---

# Space Harbour

## 题目描述

There are $ n $ points numbered $ 1 $ to $ n $ on a straight line. Initially, there are $ m $ harbours. The $ i $ -th harbour is at point $ X_i $ and has a value $ V_i $ . It is guaranteed that there are harbours at the points $ 1 $ and $ n $ . There is exactly one ship on each of the $ n $ points. The cost of moving a ship from its current location to the next harbour is the product of the value of the nearest harbour to its left and the distance from the nearest harbour to its right. Specifically, if a ship is already at a harbour, the cost of moving it to the next harbour is $ 0 $ .

Additionally, there are $ q $ queries, each of which is either of the following $ 2 $ types:

- $ 1 $ $ x $ $ v $ — Add a harbour at point $ x $ with value $ v $ . It is guaranteed that before adding the harbour, there is no harbour at point $ x $ .
- $ 2 $ $ l $ $ r $ — Print the sum of the cost of moving all ships at points from $ l $ to $ r $ to their next harbours. Note that you just need to calculate the cost of moving the ships but not actually move them.

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 2 \le m \le n \le 3 \cdot 10^5 $ , $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of points, harbours, and queries, respectively.

The second line contains $ m $ distinct integers $ X_1, X_2, \ldots, X_m(1 \le X_i \le n) $ — the position at which the $ i $ -th harbour is located.

The third line contains $ m $ integers $ V_1, V_2, \ldots, V_m(1 \le V_i \le 10^7) $ — the value of the $ i $ -th harbour.

Each of the next $ q $ lines contains three integers. The first integer is $ t $ ( $ 1\le t \le 2 $ ) — type of query. If $ t=1 $ , then the next two integers are $ x $ and $ v $ ( $ 2 \le x \le n - 1 $ , $ 1 \le v \le 10^7 $ ) — first-type query. If $ t=2 $ , then the next two integers are $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — second-type query.

It is guaranteed that there is at least one second-type query.

## 输出格式

For every second-type query, print one integer in a new line — answer to this query.

## 说明/提示

For the first type $ 2 $ query, the cost for ships at positions $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ are $ 3(3 \times 1) $ , $ 0 $ , $ 96(24 \times 4) $ and $ 72(24 \times 3) $ respectively.

For the second type $ 2 $ query, since the ship at position $ 5 $ is already at a harbour, so the cost is $ 0 $ .

For the third type $ 2 $ query, the cost for ships at position $ 7 $ and $ 8 $ are $ 15(15 \times 1) $ and $ 0 $ respectively.

## 样例 #1

### 输入

```
8 3 4
1 3 8
3 24 10
2 2 5
1 5 15
2 5 5
2 7 8
```

### 输出

```
171
0
15
```



---

---
title: "Unique Array"
layout: "post"
diff: 提高+/省选-
pid: CF1969E
tag: ['贪心', '线段树']
---

# Unique Array

## 题目描述

You are given an integer array $ a $ of length $ n $ . A subarray of $ a $ is one of its contiguous subsequences (i. e. an array $ [a_l, a_{l+1}, \dots, a_r] $ for some integers $ l $ and $ r $ such that $ 1 \le l < r \le n $ ). Let's call a subarray unique if there is an integer that occurs exactly once in the subarray.

You can perform the following operation any number of times (possibly zero): choose an element of the array and replace it with any integer.

Your task is to calculate the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 说明/提示

In the second test case, you can replace the $ 1 $ -st and the $ 3 $ -rd element, for example, like this: $ [3, 4, 1, 4] $ .

In the third test case, you can replace the $ 4 $ -th element, for example, like this: $ [3, 1, 2, 3, 2] $ .

## 样例 #1

### 输入

```
4
3
2 1 2
4
4 4 4 4
5
3 1 2 1 2
5
1 3 2 1 2
```

### 输出

```
0
2
1
0
```



---

---
title: "Chain Queries"
layout: "post"
diff: 提高+/省选-
pid: CF1975E
tag: ['线段树', '树链剖分']
---

# Chain Queries

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Initially, all vertices are colored white or black.

You are asked to perform $ q $ queries:

- "u" — toggle the color of vertex $ u $ (if it was white, change it to black and vice versa).

After each query, you should answer whether all the black vertices form a chain. That is, there exist two black vertices such that the simple path between them passes through all the black vertices and only the black vertices. Specifically, if there is only one black vertex, they form a chain. If there are no black vertices, they do not form a chain.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1\leq n,q\leq 2\cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ c_1,c_2,\ldots,c_n $ ( $ c_i \in \{ \mathtt{0}, \mathtt{1} \} $ ) — the initial color of the vertices. $ c_i $ denotes the color of vertex $ i $ where $ \mathtt{0} $ denotes the color white, and $ \mathtt{1} $ denotes the color black.

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

The following $ q $ lines each contain an integer $ u_i $ ( $ 1 \le u_i \le n $ ), indicating the color of vertex $ u_i $ needs to be toggled.

It is guaranteed that the sum of $ n $ and $ q $ over all test cases respectively does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each query, output "Yes" if the black vertices form a chain, and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the second test case, the color of the vertices are as follows:

The initial tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/d67482a066522c11f266b4eca3d7a1ef0055849d.png)The first query toggles the color of vertex $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/4a07e30139deb2cb81867b3706db8e9ec51e4318.png)The second query toggles the color of vertex $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/fd56e11f35468c4b51183822460fd341cde05e88.png)The third query toggles the color of vertex $ 2 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/f1f02d1c42e642ef8cfd2174f0e71d8955cb85ac.png)The fourth query toggles the color of vertex $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/72ebf27a994a252cc8de91446a4beacafa646ddb.png)

## 样例 #1

### 输入

```
2
2 1
1 0
1 2
1
5 4
1 0 0 0 0
1 2
1 3
1 5
3 4
4
3
2
5
```

### 输出

```
No
No
Yes
Yes
No
```

## 样例 #2

### 输入

```
4
5 3
1 1 1 1 1
3 5
2 5
3 4
1 5
1
1
1
4 4
0 0 0 0
1 2
2 3
1 4
1
2
3
2
1 1
1
1
1 1
0
1
```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
No
Yes
```



---

---
title: "Invertible Bracket Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF1976D
tag: ['线段树', 'ST 表']
---

# Invertible Bracket Sequences

## 题目描述

### 题意翻译
### 题面描述
我们定义一个合法的括号序列，是仅由 `(` 和 `)` 构成的字符串且：
1. 空串 $\epsilon$ 是合法的括号序列。
2. 若 $s$ 为合法的括号序列，则 $(s)$ 也为合法的括号序列。
3. 若 $s,t$ 均为合法的括号序列，则 $st$ 也为合法的括号序列。（其中 $st$ 表示将字符串 $s$ 和 $t$ 拼接。）

定义对一个括号序列的**翻转**操作为：将这个括号序列的所有 `(` 变为 `)`，所有 `)` 变为 `(`。

如 `()(((` 翻转后成为 `)()))`。

给定一个**保证合法**的字符串 $s$。

你可以选择字符串 $s$ 的一个**子串**进行翻转操作。（注意是**子串**，与**子序列区分**，子串要求**连续**。）

问**翻转**了一个**子串**后得到的字符串 $s'$ 仍然是**合法括号序列**的方案数。

## 输入格式

先是一个数字 $t$ 表示数据组数。

接下来 $t$ 行，每行一个合法括号序列 $s$。

## 输出格式

对于每组数据，输出一个数字 $x$，表示翻转 $s$ 的一个子串后仍然是合法括号序列的方案数。

## 说明/提示

在本题中，不可以翻转长度为 $0$ 的子串。

translate by Hoks。

## 样例 #1

### 输入

```
4
(())
()
()()()
(()())(())
```

### 输出

```
1
0
3
13
```



---

---
title: "Penacony"
layout: "post"
diff: 提高+/省选-
pid: CF1996G
tag: ['线段树']
---

# Penacony

## 题目描述

在梦乡 $\text{Penacony}$ ，有 $n$ 栋房子和 $n$ 条双向的路。第 $i$ 栋和第 $i+1$ 栋房子（包括第 $n$ 和第 $1$ 栋之间）有双向的路连接。然而，由于梦乡的危机，领主陷入债务，难以维护所有的路。

梦乡的居民之中，有 $m$ 对好朋友。如果住在 $a$ 栋的居民和住在 $b$ 栋的居民是好朋友，那么他们必须能够通过受到维护的道路相互来往，即要求维护 $a$ 栋和 $b$ 栋之间那些的路。

请求出梦乡的领主最少需要维护多少条路。

## 输入格式

第一行是 $t$ ，表示测试组数。 

接下来每组的第一行是 $n$ 和 $m$，有 $3 \le n \le 2\cdot10^5, 1 \le m \le 2\cdot10^5$，表示房子栋数和好朋友对数。  
之后的 $m$ 行每行有两个整数 $a$ 和 $b$ ，有 $1\le a < b\le n$ ，表示 $a$ 栋和 $b$ 栋的居民是好朋友。保证每对 $(a,b)$ 都不同。

同时还保证所有测试组的 $n$ 和 $m$ 之和不超过 $2\cdot10^5$.

## 输出格式

每组输出一行，表示最少需要维护的道路数。

## 样例 #1

### 输入

```
7
8 3
1 8
2 7
4 5
13 4
1 13
2 12
3 11
4 10
10 2
2 3
3 4
10 4
3 8
5 10
2 10
4 10
4 1
1 3
5 2
3 5
1 4
5 2
2 5
1 3
```

### 输出

```
4
7
2
7
2
3
3
```



---

---
title: "Level Up"
layout: "post"
diff: 提高+/省选-
pid: CF1997E
tag: ['线段树', '二分', '树状数组']
---

# Level Up

## 题目描述

Monocarp正在玩一款电脑游戏。他从等级 $ 1 $ 开始。他将依次与 $ n $ 只怪物战斗，这些怪物的等级从 $ 1 $ 到 $ n $ 不等。

对于按顺序给出的每个怪物，Monocarp的遭遇如下：

- 如果Monocarp的等级高于怪物的等级，则怪物会逃跑；
- 否则，Monocarp会与怪物战斗。

在每与第 $ k $ 个怪物战斗（逃跑的怪物不计算在内）后，Monocarp的等级会增加 $ 1 $ 。因此，他在与 $ k $ 个怪物战斗后等级变为 $ 2 $ ，在与 $ 2k $ 个怪物战斗后等级变为 $ 3 $ ，以此类推。

你需要处理 $ q $ 个查询，每个查询的格式如下：

- $ i~x $ ：如果参数 $ k $ 等于 $ x $ ，Monocarp是否会与第 $ i $ 个怪物战斗？

## 输入格式

第一行包含两个整数 $ n $ 和 $ q $ （ $ 1 \le n, q \le 2 \cdot 10^5 $ ） — 怪物的数量和查询的数量。

第二行包含 $ n $ 个整数 $ a_1, a_2, \dots, a_n $ （ $ 1 \le a_i \le 2 \cdot 10^5 $ ） — 每个怪物的等级。

接下来的 $ q $ 行，每行包含两个整数 $ i $ 和 $ x $ （ $ 1 \le i, x \le n $ ） — 查询中指定的怪物索引和需要升级的战斗次数。

## 输出格式

对于每个查询，如果Monocarp会与第 $ i $ 个怪物战斗，则输出 "YES" ，否则输出 "NO" 。

## 样例 #1

### 输入

```
4 16
2 1 2 1
1 1
2 1
3 1
4 1
1 2
2 2
3 2
4 2
1 3
2 3
3 3
4 3
1 4
2 4
3 4
4 4
```

### 输出

```
YES
NO
YES
NO
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
```

## 样例 #2

### 输入

```
7 15
1 1 2 1 1 1 1
5 3
2 2
2 2
1 6
5 1
5 5
7 7
3 5
7 4
4 3
2 5
1 2
5 6
4 1
6 1
```

### 输出

```
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
YES
YES
NO
NO
```



---

---
title: "Eliminating Balls With Merging (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1998E1
tag: ['线段树', '分治', 'ST 表', '单调栈']
---

# Eliminating Balls With Merging (Easy Version)

## 题目描述

_喝水_ 

—— 孙武，程序员健康指南

**这是问题的简单版本。本题中 $x=n$ 。你必须同时解决这两个版本的问题，才能  hack**。

给你两个整数 $n$ 和 $x$ ( $x=n$ )。有 $n$ 个球排成一排，从左到右编号为 $1$ 到 $n$ 。最初，在第 $i$ 个球上写着一个值 $a_i$。

对于从 $1$ 到 $n$ 的每个整数 $i$ ，我们定义一个函数 $f(i)$ 如下：

- 假设有一个集合 $S = \{1, 2, \ldots, i\}$ 。
    
- 在每次运算中，必须从 $S$ 中选择一个整数 $l$ ( $1 \leq l < i$ )，使得 $l$ 不是 $S$ 的最大元素。假设 $r$ 是 $S$ 中大于 $l$ 的最小元素。
    
    - 如果是 $a_l > a_r$ ，则令 $a_l = a_l + a_r$ 并从 $S$ 中删除 $r$ 。
    - 如果是 $a_l < a_r$ ，则令 $a_r = a_l + a_r$ ，并从 $S$ 删除 $l$ 。
    - 如果是 $a_l = a_r$ ，则从 $S$ 中选择删除整数 $l$ 或 $r$ ：
        - 如果选择从 $S$ 中删除 $l$ ，则设置 $a_r = a_l + a_r$ 并从 $S$ 中删除 $l$ 。
        - 如果您选择从 $S$ 中删除 $r$ ，则需要设置 $a_l = a_l + a_r$ ，并从 $S$ 中删除 $r$ 。
    
- $f(i)$ 表示这样的整数 $j$ ( $1 \le j \le i$ )的个数，即执行上述操作恰好 $i - 1$ 次后可以得到 $S = \{j\}$ 。

对 $x$ 到 $n$ 的每个整数 $i$ 都需要求出 $f(i)$ 。

## 输入格式

第一行包含 $t$ ( $1 \leq t \leq 10^4$ ) ，表示测试用例数。

每个测试用例的第一行包含两个整数 $n$ 和 $x$ ( $1 \leq n \leq 2 \cdot 10^5; x = n$ )--球的个数和最小索引 $i$ ，您需要找到该索引的 $f(i)$ 。

每个测试用例的第二行包含 $a_1, a_2, \ldots, a_n$ ( $1 \leq a_i \leq 10^9$ ) - 写在每个球上的初始数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，在一行中输出 $n-x+1$ 个空格分隔的整数，其中第 $j$ 个整数表示 $f(x+j-1)$ 。

**样例解释**

在第一个测试用例中，要计算 $f(5)$ 。可以看出，经过 $4$ 次运算后， $S$ 可以包含 $2$ 、 $3$ 或 $4$ 。下面是生成 $S = \{4\}$ 所需的运算。

- 最初是 $S = \{1, 2, 3, 4, 5\}$ 和 $a = [1, 2, 3, 2, 1]$ 。
- 选择 $l = 1$ 。自然是 $r = 2$ 。由于 $a_1< a_2$ ，我们设置 $a_2 = 1 + 2$ ，并从 $S$ 中删除 $1$ 。现在， $S = \{2, 3, 4, 5\}$ 和 $a = [1, 3, 3, 2, 1]$ 。
- 选择 $l = 4$ 。自然是 $r = 5$ 。由于 $a_4> a_5$ ，我们设置 $a_4 = 2 + 1$ ，并从 $S$ 中删除 $5$ 。现在， $S = \{2, 3, 4\}$ 和 $a = [1, 3, 3, 3, 1]$ 。
- 选择 $l = 3$ 。自然是 $r = 4$ 。由于 $a_3 = a_4$ ，我们可以选择删除 $3$ 或 $4$ 。既然要保留 $4$ ，那么就删除 $3$ 。因此，设置 $a_4 = 3 + 3$ 并从 $S$ 中删除 $3$ 。现在， $S = \{2, 4\}$ 和 $a = [1, 3, 3, 6, 1]$ 。
- 选择 $l = 2$ 。自然是 $r = 4$ 。由于 $a_2< a_4$ ，我们设置 $a_4 = 3 + 6$ ，并从 $S$ 中删除 $2$ 。最后是 $S = \{4\}$ 和 $a = [1, 3, 3, 9, 1]$ 。

在第二个测试案例中，要求计算 $f(7)$ 。可以证明，经过 $6$ 次运算后， $S$ 可以包含 $2$ 、 $4$ 、 $6$ 或 $7$ 。

## 样例 #1

### 输入

```
3
5 5
1 2 3 2 1
7 7
4 5 1 2 1 4 5
11 11
1 2 3 1 1 9 3 2 4 1 3
```

### 输出

```
3
4
4
```



---

---
title: "Ksyusha and the Loaded Set"
layout: "post"
diff: 提高+/省选-
pid: CF2000H
tag: ['线段树', '二分']
---

# Ksyusha and the Loaded Set

## 题目描述

Ksyusha 决定创办一家游戏开发公司。为了在竞争中脱颖而出并取得成功，她决定编写一个属于自己的游戏引擎。这个引擎需要支持一个初始包含 $n$ 个不同整数 $a_1, a_2, \ldots, a_n$ 的集合。

接下来，这个集合将依次进行 $m$ 次操作。可进行的操作类型如下：

- 向集合中插入一个元素 $x$；
- 从集合中移除一个元素 $x$；
- 查询集合的 $k$-负载。

集合的 $k$-负载定义为最小的正整数 $d$，使得整数 $d, d + 1, \ldots, d + (k - 1)$ 全都不在这个集合中。例如，集合 $\{3, 4, 6, 11\}$ 的 $3$-负载是 $7$，因为数字 $7, 8, 9$ 不在集合里，并且没有更小的值满足这个条件。

由于 Ksyusha 忙于管理工作，所以需要你来帮忙实现这个引擎的操作支持。

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^4$），表示有 $t$ 组测试用例。

接下来的行描述每个测试用例。

每个测试用例的第一行输入一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示集合的初始大小。

接着一行输入 $n$ 个严格递增的整数 $a_1, a_2, \ldots, a_n$（$1 \le a_1 < a_2 < \ldots < a_n \le 2 \cdot 10^6$），表示集合的初始状态。

然后一行输入一个整数 $m$（$1 \le m \le 2 \cdot 10^5$），表示操作的数量。

接下来的 $m$ 行描述这些操作，格式如下：

- `+ x`（插入元素 $x$，$1 \le x \le 2 \cdot 10^6$，保证 $x$ 不在集合中）；
- `- x`（删除元素 $x$，$1 \le x \le 2 \cdot 10^6$，保证 $x$ 在集合中）；
- `? k`（查询 $k$-负载，$1 \le k \le 2 \cdot 10^6$）。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$，$m$ 的总和也不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出所有 `?` 类型操作的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 2 5 905 2000000
15
- 2
? 2
? 1
- 1
? 1
+ 4
+ 2
? 2
+ 6
- 4
+ 7
? 2
? 3
? 4
? 2000000
5
3 4 5 6 8
9
? 5
- 5
? 5
+ 1
? 2
- 6
- 8
+ 6
? 5
5
6 7 8 9 10
10
? 5
- 6
? 4
- 10
+ 5
- 8
+ 3
+ 2
- 3
+ 10
```

### 输出

```
2 2 1 6 3 8 8 2000001 
9 9 9 7 
1 1
```



---

---
title: "Yunli's Subarray Queries (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2009G2
tag: ['线段树', '倍增']
---

# Yunli's Subarray Queries (hard version)

## 题目描述

这是问题的困难版本。在此版本中，保证所有查询的 $r\geq l+k-1$。

对于任意数组 $b$，Yunli 可以执行以下操作任意次数：

- 选择一个索引 $i$。设置 $b_i=x$，其中 $x$ 是她想要的任何整数（$x$ 不限于区间 $[1,n]$）。

将 $f(b)$ 表示为她需要执行的最小操作数，直到 $b$ 中存在长度至少为 $k$ 的连续子数组$^{\text{*}}$。

Yunli 收到一个大小为 $n$ 的数组 $a$，并询问 $q$ 次。在每次查询中，你需要计算 $\sum_{j=l+k-1}^{r}f([a_l,a_{l+1},\ldots,a_j])$。

$^{\text{*}}$ 如果存在一个长度为 $k$ 的连续子数组，从索引 $i$ 开始（$1\leq i\leq |b|-k+1$），那么对于所有 $i<j\leq i+k-1$，$b_j=b_{j-1}+1$。

## 输入格式

第一行包含 $t$（$1\leq t\leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$k$ 和 $q$（$1\leq k\leq n\leq 2\cdot 10^5$，$1\leq 2 \cdot 10^ 5$）——数组的长度、连续子数组的长度和查询次数。

下一行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$（$1\leq a_i\leq n$）。

以下 $q$ 行包含两个整数 $l$ 和 $r$（$1\leq l\leq r\leq n$，$r\geq l+k-1$）——查询的边界。

保证所有测试用例中 $n$ 的总和不超过 $2\cdot 10^5$，所有测试用例的 $q$ 总和不超过 $2\cdot 10^5$。

## 输出格式

对于每组测试数据上的每次查询，输出 $\sum_{j=l+k-1}^{r}f([a_l,a_{l+1},\ldots,a_j])$。

## 说明/提示

在第一组测试用例的第二次查询中，我们计算了以下函数值：

- $f([2,3,2,1,2])=3$，因为 Yunli 可以设置 $b_3=4$、$b_4=5$ 和 $b_5=6$，从而在 $3$ 次操作中形成一个大小为 $5$ 的连续子阵列。
- $f([2,3,2,1,2,3])=2$，因为我们可以设置 $b_3=0$ 和 $b_2=-1$，在 $2$ 次操作中中（从位置 $2$ 开始）形成一个大小为$5$的连续子阵列。

这个查询的答案是 $3+2=5$。

翻译 @Cure_Wing。

## 样例 #1

### 输入

```
3
7 5 3
1 2 3 2 1 2 3
1 7
2 7
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
5 4 2
4 5 1 2 3
1 4
1 5
```

### 输出

```
6
5
2
2
5
2
3
```



---

---
title: "Speedbreaker"
layout: "post"
diff: 提高+/省选-
pid: CF2018B
tag: ['贪心', '线段树']
---

# Speedbreaker

## 题目描述

[Djjaner - Speedbreaker](https://soundcloud.com/luciano-ferrari-151560131/speedbreaker)

⠀



There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.

- At time $ 1 $ , you conquer exactly one city, called the starting city.
- At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.

You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the deadlines for conquering the cities.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the number of starting cities that allow you to win.

## 说明/提示

In the first test case, cities $ 2 $ , $ 3 $ , and $ 4 $ are good starting cities.

In the second test case, there are no good starting cities.

In the third test case, the only good starting city is city $ 5 $ .

## 样例 #1

### 输入

```
3
6
6 3 3 3 5 5
6
5 6 4 1 4 5
9
8 6 4 2 1 3 5 7 9
```

### 输出

```
3
0
1
```



---

---
title: "Max Plus Min Plus Size"
layout: "post"
diff: 提高+/省选-
pid: CF2018D
tag: ['动态规划 DP', '线段树', '并查集']
---

# Max Plus Min Plus Size

## 题目描述

[EnV - 尘龙酒馆](https://soundcloud.com/envyofficial/env-the-dusty-dragon-tavern)

----------------
给定一个由正整数组成的数组 $a_1, a_2, \ldots, a_n$ 。

你可以将数组中的一些元素涂成红色，但不能有两个相邻的红色元素（即对于 $1 \leq i \leq n-1$ 来说， $a_i$ 和 $a_{i+1}$ 中至少有一个元素不能是红色的）。

您的得分是红色元素的最大值加上红色元素的最小值，再加上红色元素的数量。请找出您能得到的最高分。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^4$ )。对每个测试用例输入如下：

每个测试用例的第一行都包含一个整数 $n$ ( $1 \le n \le 2 \cdot 10^5$ ) ，表示数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) 表示给定的数组。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数：根据题意将某些元素染成红色后可能得到的最大分数。

**样例解释**

在第一个测试用例中，可以对数组着色如下： $[\color{red}{5}\color{black}, 4, \color{red}{5} \color{black}]$ .您的得分是 $\max([5, 5]) + \min([5, 5]) + \text{size}([5, 5]) = 5+5+2 = 12$ 。这是你能得到的最高分。

在第二个测试案例中，您可以对数组着色如下： $[4, \color{red}{5},\color{black} 4]$ .您的得分是 $\max([5]) + \min([5]) + \text{size}([5]) = 5+5+1 = 11$ 。这是你能得到的最高分。

在第三个测试案例中，您可以对数组着色如下： $[\color{red}{3}\color{black}, 3, \color{red}{3} \color{black},3, \color{red}{4}\color{black}, 1, 2, \color{red}{3}, \color{black}5, \color{red}{4} \color{black}]$ .您的得分是 $\max([3, 3, 4, 3, 4]) + \min([3, 3, 4, 3, 4]) + \text{size}([3, 3, 4, 3, 4]) = 4+3+5 = 12$ 。这是你能得到的最高分。

## 样例 #1

### 输入

```
4
3
5 4 5
3
4 5 4
10
3 3 3 3 4 1 2 3 5 4
10
17 89 92 42 29 41 92 14 70 45
```

### 输出

```
12
11
12
186
```



---

---
title: "The Endspeaker (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2027D2
tag: ['动态规划 DP', '线段树']
---

# The Endspeaker (Hard Version)

## 题目描述

这是这道题目的困难版本。与简单版本的区别在于，你还需要输出达到最优解的操作序列数量。你需要解决这两种版本才能进行 hack。

现在给定一个数组 $ a $，长度为 $ n $，以及一个数组 $ b $，长度为 $ m $（保证 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $ 成立）。初始时，$ k $ 的值为 $ 1 $。你的目标是通过执行以下两种操作之一反复将数组 $ a $ 变为空：

- 类型 $ 1 $ 操作 — 在 $ k < m $ 且数组 $ a $ 不为空时，你可以将 $ k $ 的值加 $ 1 $。这种操作不需要花费任何代价。
- 类型 $ 2 $ 操作 — 你可以移除数组 $ a $ 的一个非空前缀，使得这个前缀的和不大于 $ b_k $。这种操作的代价为 $ m - k $。

你需要让将数组 $ a $ 变为空的总操作代价最小化。如果无法通过任何操作序列达到这一目标，请输出 $ -1 $。否则，输出最小总操作代价以及产生命中该代价的操作序列数量，对 $ 10^9 + 7 $ 取模。

若两个操作序列在任一步骤中选择了不同种类的操作，或移除前缀的大小不同，则它们视为不同。

## 输入格式

每个测试用例包含多个测试，第一行为测试用例数量 $ t $（$ 1 \le t \le 1000 $）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $ n $ 和 $ m $（$ 1 \le n, m \le 3 \cdot 10^5 $，且 $ 1 \le n \cdot m \le 3 \cdot 10^5 $）。

每个测试用例的第二行包含长度为 $ n $ 的整数数组 $ a $，其中每个 $ a_i $ 满足 $ 1 \le a_i \le 10^9 $。

每个测试用例的第三行包含长度为 $ m $ 的整数数组 $ b $，$ 1 \le b_i \le 10^9 $，并且满足 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $。

保证所有测试用例的总 $ n \cdot m $ 不超过 $ 3 \cdot 10^5 $。

## 输出格式

对于每个测试用例，如果可以使数组 $ a $ 变为空，则输出两个整数：最小的操作总费用，以及达到该最小费用的操作序列数量，结果对 $ 10^9 + 7 $ 取模。

如果没有可能的操作序列能使数组 $ a $ 变为空，则输出单个整数 $ -1 $。

## 说明/提示

以下为一个测试用例的示例，其中最优操作序列的总费用为 $ 1 $，共有 $ 3 $ 种：

- 所有这 $ 3 $ 种序列都以类型 $ 2 $ 的操作开头，移除前缀 $ [9] $，使得 $ a = [3, 4, 3] $，产生代价 $ 1 $。然后执行类型 $ 1 $ 操作，把 $ k $ 提升一位，此后所有操作均无代价。
- 一种序列依次移除前缀 $ [3, 4] $ 和 $ [3] $。
- 另一种序列依次移除前缀 $ [3] $ 和 $ [4, 3] $。
- 还有一种序列依次移除前缀 $ [3] $，再移除 $ [4] $，最后移除 $ [3] $。

在第二个测试用例中，由于 $ a_1 > b_1 $，无法移除任何前缀，因此无论如何都无法使数组 $ a $ 变为空。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1
```

### 输出

```
1 3
-1
2 11
10 42
4 1
```



---

---
title: "Orangutan Approved Subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF2030F
tag: ['线段树']
---

# Orangutan Approved Subarrays

## 题目描述

Suppose you have an array $ b $ . Initially, you also have a set $ S $ that contains all distinct elements of $ b $ . The array $ b $ is called orangutan-approved if it can be emptied by repeatedly performing the following operation:

- In one operation, select indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq |b| $ ) such that $ v = b_l = b_{l+1} = \ldots = b_r $ and $ v $ is present in $ S $ . Remove $ v $ from $ S $ , and simultaneously remove all $ b_i $ such that $ l \leq i \leq r $ . Then, reindex the elements $ b_{r+1}, b_{r+2}, \ldots $ as $ b_l, b_{l+1}, \ldots $ accordingly.

You are given an array $ a $ of length $ n $ and $ q $ queries.

Each query consists of two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), and you need to determine whether or not the subarray $ a_{l}, a_{l+1}, \ldots, a_r $ is orangutan-approved.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains integers $ n $ and $ q $ ( $ 1 \leq n,q \leq 2 \cdot 10^5 $ ) — the size of $ a $ and the number of queries, respectively.

The following line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array $ a $ .

The following $ q $ lines contain two integers $ l $ and $ r $ — the endpoints of the subarray for each query ( $ 1 \leq l \leq r \leq n $ ).

It is guaranteed that the sum of $ n $ and $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" (without quotes) if the subarray from $ l $ to $ r $ is orangutan-approved, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first query of the first testcase, the answer is YES.

- Initially, $ S=\{1,2\} $ and $ b=[1,2,2,1] $
- Select $ l=2 $ and $ r=3 $ . Since $ b_2=b_3=2 $ is in $ S $ , we may erase $ b_2 $ and $ b_3 $ from the array, as well as erasing $ 2 $ from $ S $ . The set $ S $ becomes $ \{1\} $ and the array becomes $ [1,1] $ .
- Select $ l=1 $ and $ r=2 $ . Since $ b_1=b_2=1 $ is in $ S $ , we may erase $ b_1 $ and $ b_2 $ from the array, as well as erasing $ 1 $ from $ S $ . The set $ S $ becomes $ \{\} $ and the array becomes $ [] $ .
- Since the array is now empty, we can say the original array is orangutan-approved.

In the first query of the second testcase, the answer is NO, because it can be shown that the subarray $ [2,1,2,1] $ cannot become empty through any sequence of valid operations.

## 样例 #1

### 输入

```
3
4 2
1 2 2 1
1 4
1 3
5 3
1 2 1 2 1
2 5
3 5
1 3
8 4
1 2 3 2 1 3 2 3
1 5
2 8
3 5
6 8
```

### 输出

```
YES
YES
NO
YES
YES
YES
NO
YES
YES
```



---

---
title: "Two Subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF2042F
tag: ['动态规划 DP', '线段树', '矩阵运算', '动态规划优化']
---

# Two Subarrays

## 题目描述

给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。

我们定义子数组 $[l, r]$ 的代价为 $a_l + a_{l + 1} + \cdots + a_r + b_l + b_r$。如果 $l = r$，那么代价计算为 $a_l + 2 \cdot b_l$。

你需要执行以下三种类型的查询：

- "1 $p$ $x$" — 把 $a_p$ 更新为 $x$；
- "2 $p$ $x$" — 把 $b_p$ 更新为 $x$；
- "3 $l$ $r$" — 在区间 $[l, r]$ 内找到两个不相交且非空的子数组，使它们的总代价最大，并输出这个总代价。

## 输入格式

第一行是一个整数 $n$，表示数组的长度（$2 \le n \le 2 \cdot 10^5$）。

第二行是 $n$ 个整数，分别表示数组 $a$ 的元素：$a_1, a_2, \dots, a_n$（每个 $a_i$ 满足 $-10^9 \le a_i \le 10^9$）。

第三行是 $n$ 个整数，分别表示数组 $b$ 的元素：$b_1, b_2, \dots, b_n$（每个 $b_i$ 满足 $-10^9 \le b_i \le 10^9$）。

第四行是一个整数 $q$，表示查询的数量（$1 \le q \le 2 \cdot 10^5$）。

接下来的 $q$ 行，每行一个查询，可能是以下三种之一：

- "1 $p$ $x$"：更新 $a$ 数组的第 $p$ 个元素为 $x$；
- "2 $p$ $x$"：更新 $b$ 数组的第 $p$ 个元素为 $x$；
- "3 $l$ $r$"：在区间 $[l, r]$ 找到两个不重叠且非空的子数组，使它们的总代价最大，并输出该代价。

可以保证至少存在一个第三种类型的查询。

## 输出格式

对于每一个第三种类型的查询，输出在区间 $[l, r]$ 内的两个不相交且非空子数组的最大可能总代价。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 -1 4 -3 2 4 0
0 6 1 0 -3 -2 -1
6
3 1 7
1 2 0
3 3 6
2 5 -3
1 3 2
3 1 5
```

### 输出

```
18
7
16
```

## 样例 #2

### 输入

```
10
2 -1 -3 -2 0 4 5 6 2 5
2 -4 -5 -1 6 2 5 -6 4 2
10
3 6 7
1 10 -2
3 5 7
3 2 8
2 1 -5
2 7 4
3 1 3
3 3 8
3 2 3
1 4 4
```

### 输出

```
23
28
28
-17
27
-22
```



---

---
title: "Adventurers"
layout: "post"
diff: 提高+/省选-
pid: CF2046C
tag: ['线段树', '二分', '树状数组', '扫描线']
---

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^5 $ ) — the number of cities on the map.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cities.

Note that some points may coincide. This is because some cities may be so close that they cannot be distinguished on the map at the given scale.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, in the first line, print a single integer $ k $ ( $ 0 \le k \le \frac{n}{4} $ ) — the maximum possible number of cities that each merchant can get at a minimum.

In the second line, print two integers $ x_0 $ and $ y_0 $ ( $ |x_0|, |y_0| \le 10^9 $ ) — the coordinates of the dividing point. If there are multiple suitable points, print any of them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1
```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0
```



---

---
title: "Earnest Matrix Complement"
layout: "post"
diff: 提高+/省选-
pid: CF2053F
tag: ['动态规划 DP', '线段树']
---

# Earnest Matrix Complement

## 题目描述

3, 2, 1, ... 我们是 —— RiOI 团队！

—— Felix & All, [特别感谢 3](https://www.luogu.com.cn/problem/T351681)

- Peter: 好消息，我的题目 T311013 已获批！
- $ \delta $: 幸好我的电脑没电，不然我可能参加了 wyrqwq 的比赛并得到负分。
- Felix: \[点赞\] 关于一首被删除歌曲的题目陈述！
- Aquawave: 我该为我的化学课感到悲伤吗？
- E.Space: 啊？
- Trine: 面包。
- Iris: 为什么总是我来测试题目？

时光荏苒，未来我们也许会重逢。回顾过去，每个人都在追寻自己向往的生活。

Aquawave 有一个大小为 $ n \times m $ 的矩阵 $ A $，其中的元素只允许是 $ [1, k] $ 区间内的整数。矩阵中的一些位置已被填上整数，其余位置用 $ -1 $ 表示，代表尚未填充。

你的任务是将矩阵 $ A $ 填满所有空白位置，接着定义 $ c_{u,i} $ 为第 $ i $ 行中数字 $ u $ 出现的次数。Aquawave 将矩阵的美丽定义为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1}. $$

请找出在最佳填充方案下的矩阵 $ A $ 的最大美丽值。

## 输入格式

输入第一行为一个整数 $ t $（$ 1 \leq t \leq 2 \cdot 10^4 $），表示测试用例的数量。以下为每个测试用例的详细描述。

每个测试用例第一行包含三个整数 $ n $、$ m $ 和 $ k $（$ 2 \leq n \leq 2 \cdot 10^5 $，$ 2 \leq m \leq 2 \cdot 10^5 $，$ n \cdot m \leq 6 \cdot 10^5 $，$ 1 \leq k \leq n \cdot m $），分别代表矩阵 $ A $ 的行数、列数以及矩阵中整数的范围。

接下来的 $ n $ 行，每行包含 $ m $ 个整数 $ A_{i,1}, A_{i,2}, \ldots, A_{i,m} $（$ 1 \leq A_{i,j} \leq k $ 或 $ A_{i,j} = -1 $），表示矩阵 $ A $ 中的各个元素。

保证所有测试用例中 $ n \cdot m $ 的总和不超过 $ 6 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个整数，表示最大可能的美丽值。

## 说明/提示

在第一个测试用例中，矩阵 $ A $ 已经确定，其美丽值为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1} = c_{1,1} \cdot c_{1,2} + c_{1,2} \cdot c_{1,3} + c_{2,1} \cdot c_{2,2} + c_{2,2} \cdot c_{2,3} + c_{3,1} \cdot c_{3,2} + c_{3,2} \cdot c_{3,3} = 1 \cdot 1 + 1 \cdot 1 + 2 \cdot 0 + 0 \cdot 1 + 0 \cdot 2 + 2 \cdot 1 = 4。$$

在第二个测试用例中，可以这样填充矩阵：

$$ \begin{bmatrix} 2 & 3 & 3 \\ 2 & 2 & 3 \end{bmatrix}, $$

得到的美丽值为 $ 4 $。这可以被证明是最大的可能值。

在第三个测试用例中，以下为一种可能的最优填充方案：

$$ \begin{bmatrix} 1 & 1 & 1 \\ 1 & 2 & 1 \\ 1 & 1 & 4 \end{bmatrix}. $$

在第四个测试用例中，下面是一种可能的最优配置：

$$ \begin{bmatrix} 1 & 3 & 2 & 3 \\ 1 & 3 & 2 & 1 \\ 3 & 1 & 5 & 1 \end{bmatrix}. $$

在第五个测试用例中，以下是一种可能的最优填充：

$$ \begin{bmatrix} 5 & 5 & 2 \\ 1 & 8 & 5 \\ 7 & 5 & 6 \\ 7 & 7 & 4 \\ 4 & 4 & 4 \end{bmatrix}. $$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
9
3 3 3
1 2 2
3 1 3
3 2 1
2 3 3
-1 3 3
2 2 -1
3 3 6
-1 -1 1
1 2 -1
-1 -1 4
3 4 5
1 3 2 3
-1 -1 2 -1
3 1 5 1
5 3 8
5 -1 2
1 8 -1
-1 5 6
7 7 -1
4 4 4
6 6 5
-1 -1 5 -1 -1 -1
-1 -1 -1 -1 2 -1
-1 1 3 3 -1 -1
-1 1 -1 -1 -1 4
4 2 -1 -1 -1 4
-1 -1 1 2 -1 -1
6 6 4
-1 -1 -1 -1 1 -1
3 -1 2 2 4 -1
3 1 2 2 -1 -1
3 3 3 3 -1 2
-1 3 3 -1 1 3
3 -1 2 2 3 -1
5 5 3
1 1 3 -1 1
2 2 -1 -1 3
-1 -1 -1 2 -1
3 -1 -1 -1 2
-1 1 2 3 -1
6 2 7
-1 7
-1 6
7 -1
-1 -1
-1 -1
2 2
```

### 输出

```
4
4
10
10
8
102
93
58
13
```



---

---
title: "Bro Thinks He's Him"
layout: "post"
diff: 提高+/省选-
pid: CF2065H
tag: ['动态规划 DP', '线段树', '树状数组', '矩阵加速', '前缀和']
---

# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个二进制字符串 $s$（$1 \leq |s| \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——查询次数。

每个测试用例的第三行包含 $q$ 个整数 $v_1, v_2, \ldots, v_q$（$1 \leq v_i \leq |s|$），表示第 $i$ 次查询翻转 $s_{v_i}$ 处的字符。

保证所有测试用例的 $|s|$ 之和与 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出 $q$ 个整数——每次查询后的答案模 $998\,244\,353$。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```



---

---
title: "Game with Binary String"
layout: "post"
diff: 提高+/省选-
pid: CF2070E
tag: ['博弈论', '线段树']
---

# Game with Binary String

## 题目描述

考虑以下游戏。两个玩家拥有一个二进制字符串（一个由字符 0 和/或 1 组成的字符串）。玩家轮流行动，由第一位玩家先手。在玩家的回合中，必须选择字符串中恰好两个相邻元素并移除它们（首元素和末元素也被视为相邻）。此外，根据当前行动玩家的不同存在额外约束：

- 如果是第一位玩家的回合，所选的两个字符必须都是 0；
- 如果是第二位玩家的回合，所选的两个字符中至少有一个必须是 1。

无法进行有效移动的玩家输掉游戏。这也意味着如果当前字符串长度小于 2，当前玩家输掉游戏。

给定一个长度为 $n$ 的二进制字符串 $s$。你需要计算其满足以下条件的子串数量：若在该子串上进行游戏且双方都采取最优决策，第一位玩家将获胜。换句话说，计算满足 $1 \le l \le r \le n$ 的有序对 $(l, r)$ 的数量，使得在字符串 $s_l s_{l+1} \dots s_r$ 上第一位玩家拥有必胜策略。

## 输入格式

第一行包含一个整数 $n$（$1 \le n \le 3 \cdot 10^5$）。

第二行包含字符串 $s$，由恰好 $n$ 个字符组成。每个字符为 0 或 1。

## 输出格式

输出一个整数——满足条件的子串数量（即第一位玩家能获胜的子串数量）。


## 说明/提示

第一个示例中，以下子串是第一位玩家的必胜子串（$s[l:r]$ 表示 $s_l s_{l+1} \dots s_r$）：

- $s[1:2]$；
- $s[1:3]$；
- $s[1:7]$；
- $s[2:4]$；
- $s[2:8]$；
- $s[3:5]$；
- $s[4:5]$；
- $s[4:6]$；
- $s[5:7]$；
- $s[6:8]$；
- $s[7:8]$；
- $s[7:9]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
10
0010010011
```

### 输出

```
12
```



---

---
title: "Mani and Segments"
layout: "post"
diff: 提高+/省选-
pid: CF2101D
tag: ['线段树', '枚举', '扫描线']
---

# Mani and Segments

## 题目描述

一个长度为 $|b|$ 的数组 $b$ 被称为"可爱的"，当且仅当其最长递增子序列（LIS）的长度与最长递减子序列（LDS）的长度 $^{\text{∗}}$ 之和恰好比数组长度大 1。更正式地说，数组 $b$ 是可爱的当且仅当 $\operatorname{LIS}(b) + \operatorname{LDS}(b) = |b| + 1$。

给定一个长度为 $n$ 的排列 $a$ $^{\text{†}}$。你的任务是统计排列 $a$ 中所有非空子数组 $^{\text{‡}}$ 中满足可爱条件的数量。

$^{\text{∗}}$ 序列 $x$ 是序列 $y$ 的子序列，如果可以通过从 $y$ 中删除任意位置（可能为零或全部）的元素得到 $x$。

数组的最长递增（递减）子序列是指元素按严格递增（递减）顺序排列的最长子序列。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

$^{\text{‡}}$ 数组 $x$ 是数组 $y$ 的子数组，如果可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到 $x$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——排列 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）——排列 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出排列 $a$ 中满足可爱条件的非空子数组数量。

## 说明/提示

在第一个测试用例中，所有 6 个非空子数组都是可爱的：
- $[3]$：$\operatorname{LIS}([3]) + \operatorname{LDS}([3]) = 1 + 1 = 2$
- $[1]$：$\operatorname{LIS}([1]) + \operatorname{LDS}([1]) = 1 + 1 = 2$
- $[2]$：$\operatorname{LIS}([2]) + \operatorname{LDS}([2]) = 1 + 1 = 2$
- $[3, 1]$：$\operatorname{LIS}([3, 1]) + \operatorname{LDS}([3, 1]) = 1 + 2 = 3$
- $[1, 2]$：$\operatorname{LIS}([1, 2]) + \operatorname{LDS}([1, 2]) = 2 + 1 = 3$
- $[3, 1, 2]$：$\operatorname{LIS}([3, 1, 2]) + \operatorname{LDS}([3, 1, 2]) = 2 + 2 = 4$

在第二个测试用例中，一个可爱的子数组是 $[2, 3, 4, 5, 1]$，因为 $\operatorname{LIS}([2, 3, 4, 5, 1]) = 4$ 且 $\operatorname{LDS}([2, 3, 4, 5, 1]) = 2$，满足 $4 + 2 = 5 + 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
3 1 2
5
2 3 4 5 1
4
3 4 1 2
7
1 2 3 4 5 6 7
10
7 8 2 4 5 10 1 3 6 9
```

### 输出

```
6
15
9
28
36
```



---

---
title: "Incessant Rain"
layout: "post"
diff: 提高+/省选-
pid: CF2117H
tag: ['线段树', '扫描线']
---

# Incessant Rain

## 题目描述

**注意本题的内存限制与通常不同。**

银狼给了你一个长度为 $n$ 的数组 $a$ 和 $q$ 个查询。在每个查询中，她替换数组中的一个元素。在每个查询后，她将询问你 $k$ 的最大值，使得存在一个整数 $x$ 和 $a$ 的一个子数组 $^*$，其中 $x$ 是该子数组的 $k$-多数。

若 $y$ 在数组 $b$ 中出现了至少 $\left\lfloor\frac{|b|+1}{2}\right\rfloor+k$ 次（其中 $|b|$ 表示 $b$ 的长度），则称 $y$ 是数组 $b$ 的 $k$-多数。注意 $b$ 可能不存在一个 $k$-多数。

$^*$ 若数组 $a$ 在删除开头和结尾的若干（可能为零或者全部）元素后可以得到数组 $b$，则称 $b$ 是 $a$ 的一个子数组。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 3 \cdot 10^5$），表示 $a$ 的长度和查询的数量。
- 第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$）。
- 接下来的 $q$ 行中每行包含两个整数 $i$ 和 $x$，表示当前查询将 $a_i$ 替换为 $x$（$1 \le i,x \le n$）。

输入数据保证所有测试用例的 $n$ 和 $q$ 之和均不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出每个查询的回答，并以空格分隔。

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
3 4
1 4
2 4
4 3
2 3
7 8
3 2 3 3 2 2 3
2 3
5 3
6 3
3 4
4 4
7 4
6 4
2 4
```

### 输出

```
1 1 2 1 0 
2 2 3 2 1 1 1 2
```



---

---
title: "Ice Baby"
layout: "post"
diff: 提高+/省选-
pid: CF2121H
tag: ['动态规划 DP', '线段树', '动态规划优化', '标签504']
---

# Ice Baby

## 题目描述

The longest non-decreasing subsequence of an array of integers $ a_1, a_2, \ldots, a_n $ is the longest sequence of indices $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ such that $ a_{i_1} \leq a_{i_2} \leq \ldots \leq a_{i_k} $ . The length of the sequence is defined as the number of elements in the sequence. For example, the length of the longest non-decreasing subsequence of the array $ a = [3, 1, 4, 1, 2] $ is $ 3 $ .

You are given two arrays of integers $ l_1, l_2, \ldots, l_n $ and $ r_1, r_2, \ldots, r_n $ . For each $ 1 \le k \le n $ , solve the following problem:

- Consider all arrays of integers $ a $ of length $ k $ , such that for each $ 1 \leq i \leq k $ , it holds that $ l_i \leq a_i \leq r_i $ . Find the maximum length of the longest non-decreasing subsequence among all such arrays.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the arrays $ l $ and $ r $ .

The next $ n $ lines of each test case contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers: for each $ k $ from $ 1 $ to $ n $ , output the maximum length of the longest non-decreasing subsequence among all suitable arrays.

## 说明/提示

In the first test case, the only possible array is $ a = [1] $ . The length of the longest non-decreasing subsequence of this array is $ 1 $ .

In the second test case, for $ k = 2 $ , no matter how we choose the values of $ a_1 $ and $ a_2 $ , the condition $ a_1 > a_2 $ will always hold. Therefore, the answer for $ k = 2 $ will be $ 1 $ .

In the third test case, for $ k = 4 $ , we can choose the array $ a = [5, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

In the fourth test case, for $ k = 8 $ , we can choose the array $ a = [7, 5, 3, 5, 3, 3, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 5 $ .

In the fifth test case, for $ k = 5 $ , we can choose the array $ a = [2, 8, 5, 3, 3] $ . The length of the longest non-decreasing subsequence of this array is $ 3 $ .

## 样例 #1

### 输入

```
6
1
1 1
2
3 4
1 2
4
4 5
3 4
1 3
3 3
8
6 8
4 6
3 5
5 5
3 4
1 3
2 4
3 3
5
1 2
6 8
4 5
2 3
3 3
11
35 120
66 229
41 266
98 164
55 153
125 174
139 237
30 72
138 212
109 123
174 196
```

### 输出

```
1 
1 1 
1 2 2 3 
1 2 2 3 3 3 4 5 
1 2 2 2 3 
1 2 3 4 5 6 7 7 8 8 9
```



---

---
title: "Water Tree"
layout: "post"
diff: 提高+/省选-
pid: CF343D
tag: ['线段树', '树链剖分']
---

# Water Tree

## 题目描述

Mad scientist Mike has constructed a rooted tree, which consists of $ n $ vertices. Each vertex is a reservoir which can be either empty or filled with water.

The vertices of the tree are numbered from 1 to $ n $ with the root at vertex 1. For each vertex, the reservoirs of its children are located below the reservoir of this vertex, and the vertex is connected with each of the children by a pipe through which water can flow downwards.

Mike wants to do the following operations with the tree:

1. Fill vertex $ v $ with water. Then $ v $ and all its children are filled with water.
2. Empty vertex $ v $ . Then $ v $ and all its ancestors are emptied.
3. Determine whether vertex $ v $ is filled with water at the moment.

 Initially all vertices of the tree are empty.Mike has already compiled a full list of operations that he wants to perform in order. Before experimenting with the tree Mike decided to run the list through a simulation. Help Mike determine what results will he get after performing all the operations.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=500000 $ ) — the number of vertices in the tree. Each of the following $ n-1 $ lines contains two space-separated numbers $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ) — the edges of the tree.

The next line contains a number $ q $ ( $ 1<=q<=500000 $ ) — the number of operations to perform. Each of the following $ q $ lines contains two space-separated numbers $ c_{i} $ ( $ 1<=c_{i}<=3 $ ), $ v_{i} $ ( $ 1<=v_{i}<=n $ ), where $ c_{i} $ is the operation type (according to the numbering given in the statement), and $ v_{i} $ is the vertex on which the operation is performed.

It is guaranteed that the given graph is a tree.

## 输出格式

For each type 3 operation print 1 on a separate line if the vertex is full, and 0 if the vertex is empty. Print the answers to queries in the order in which the queries are given in the input.

## 样例 #1

### 输入

```
5
1 2
5 1
2 3
4 2
12
1 1
2 3
3 1
3 2
3 3
3 4
1 2
2 4
3 1
3 3
3 4
3 5

```

### 输出

```
0
0
0
1
0
1
0
1

```



---

---
title: "Propagating tree"
layout: "post"
diff: 提高+/省选-
pid: CF383C
tag: ['模拟', '线段树', '深度优先搜索 DFS']
---

# Propagating tree

## 题目描述

很久以前，有一棵神橡树(oak)，上面有$n$个节点，从$1$~$n$编号，由$n-1$条边相连。它的根是$1$号节点。  

这棵橡树每个点都有一个权值，你需要完成这两种操作：
$1$ $u$ $val$ 表示给$u$节点的权值增加$val$  
$2$ $u$ 表示查询$u$节点的权值   

但是这不是普通的橡树，它是神橡树。  
所以它还有个神奇的性质：当某个节点的权值增加$val$时，它的子节点权值都增加$-val$，它子节点的子节点权值增加$-(-val)$...... 如此一直进行到树的底部。

## 输入格式

第一行两个正整数$n,m$，表示节点数量和操作数量。  
第二行$n$个正整数$a_i$，依次表示每个节点的权值。     
接下来$n-1$行，每行两个正整数$u,v$，表示$u,v$之间有一条边相连。  
最后$m$行，每行若干个正整数，表示一次操作。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 说明/提示

$1\le n,m \le 2\times 10^5$  
$1\le a_i,val \le 1000$  
$1\le u,v \le n$

## 样例 #1

### 输入

```
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4

```

### 输出

```
3
3
0

```



---

---
title: "George and Cards"
layout: "post"
diff: 提高+/省选-
pid: CF387E
tag: ['贪心', '线段树', '二分']
---

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 输入格式

The first line contains integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{6} $ ) — the initial and the final number of cards.

The second line contains $ n $ distinct space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the initial row of cards.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ — the row of cards that you need to get. It is guaranteed that it's possible to obtain the given row by using the remove operation for $ n-k $ times.

## 输出格式

Print a single integer — the maximum number of pieces of sausage that George can get if he acts optimally well.

## 样例 #1

### 输入

```
3 2
2 1 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10

```

### 输出

```
30

```



---

---
title: "Maze 2D"
layout: "post"
diff: 提高+/省选-
pid: CF413E
tag: ['线段树', '倍增']
---

# Maze 2D

## 题目描述

The last product of the R2 company in the 2D games' field is a new revolutionary algorithm of searching for the shortest path in a $ 2×n $ maze.

Imagine a maze that looks like a $ 2×n $ rectangle, divided into unit squares. Each unit square is either an empty cell or an obstacle. In one unit of time, a person can move from an empty cell of the maze to any side-adjacent empty cell. The shortest path problem is formulated as follows. Given two free maze cells, you need to determine the minimum time required to go from one cell to the other.

Unfortunately, the developed algorithm works well for only one request for finding the shortest path, in practice such requests occur quite often. You, as the chief R2 programmer, are commissioned to optimize the algorithm to find the shortest path. Write a program that will effectively respond to multiple requests to find the shortest path in a $ 2×n $ maze.

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n<=2·10^{5}; 1<=m<=2·10^{5}) $ — the width of the maze and the number of queries, correspondingly. Next two lines contain the maze. Each line contains $ n $ characters, each character equals either '.' (empty cell), or 'X' (obstacle).

Each of the next $ m $ lines contains two integers $ v_{i} $ and $ u_{i} $ $ (1<=v_{i},u_{i}<=2n) $ — the description of the $ i $ -th request. Numbers $ v_{i} $ , $ u_{i} $ mean that you need to print the value of the shortest path from the cell of the maze number $ v_{i} $ to the cell number $ u_{i} $ . We assume that the cells of the first line of the maze are numbered from $ 1 $ to $ n $ , from left to right, and the cells of the second line are numbered from $ n+1 $ to $ 2n $ from left to right. It is guaranteed that both given cells are empty.

## 输出格式

Print $ m $ lines. In the $ i $ -th line print the answer to the $ i $ -th request — either the size of the shortest path or -1, if we can't reach the second cell from the first one.

## 样例 #1

### 输入

```
4 7
.X..
...X
5 1
1 3
7 7
1 4
6 1
4 7
5 7

```

### 输出

```
1
4
0
5
2
2
2

```

## 样例 #2

### 输入

```
10 3
X...X..X..
..X...X..X
11 7
7 18
18 10

```

### 输出

```
9
-1
3

```



---

---
title: "The Child and Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF438D
tag: ['线段树']
---

# The Child and Sequence

## 题目描述

有一个长度为 $n$ 的数列 $\{a_n\}$ 和 $m$ 次操作，操作内容如下：

1. 格式为 `1 l r`，表示求 $\sum \limits _{i=l}^{r} a_i$ 的值并输出。
2. 格式为 `2 l r x`，表示对区间 $[l,r]$ 内每个数取模，模数为 $x$。
3. 格式为 `3 k x`，表示将 $a_k$ 修改为 $x$。

$1 \le n,m \le 10^5$，$1\le l,r,k\le n$，$1\le x \le 10^9$。

## 输入格式

第一行两个正整数 $n,m$，分别表示数列长度和操作次数。

第二行给出长为 $n$ 的数列 $\{a_n\}$。

接下来 $m$ 行，每行表示一次操作。

## 输出格式

对于每个操作 $1$，输出答案，每行一个整数。答案可能大于 $2^{31}-1$。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
2 3 5 4
3 3 5
1 2 5
2 1 3 3
1 1 3

```

### 输出

```
8
5

```

## 样例 #2

### 输入

```
10 10
6 9 6 7 6 1 10 10 9 5
1 3 9
2 7 10 9
2 5 10 8
1 4 7
3 3 7
2 7 9 9
1 2 4
1 6 6
1 5 9
3 1 10

```

### 输出

```
49
15
23
1
9

```



---

---
title: "DZY Loves Fibonacci Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF446C
tag: ['数学', '线段树', '斐波那契数列']
---

# DZY Loves Fibonacci Numbers

## 题目描述

In mathematical terms, the sequence $ F_{n} $ of Fibonacci numbers is defined by the recurrence relation

 $ F_{1}=1; F_{2}=1; F_{n}=F_{n-1}+F_{n-2} (n>2). $ DZY loves Fibonacci numbers very much. Today DZY gives you an array consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Moreover, there are $ m $ queries, each query has one of the two types:

1. Format of the query " $ 1\ l\ r $ ". In reply to the query, you need to add $ F_{i-l+1} $ to each element $ a_{i} $ , where $ l<=i<=r $ .
2. Format of the query " $ 2\ l\ r $ ". In reply to the query you should output the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF446C/9b1c73158dd7a4166f7d8fde16bb75f36899bc0e.png) modulo $ 1000000009 (10^{9}+9) $ .

Help DZY reply to all the queries.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=300000 $ ). The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} (1<=a_{i}<=10^{9}) $ — initial array $ a $ .

Then, $ m $ lines follow. A single line describes a single query in the format given in the statement. It is guaranteed that for each query inequality $ 1<=l<=r<=n $ holds.

## 输出格式

For each query of the second type, print the value of the sum on a single line.

## 说明/提示

After the first query, $ a=[2,3,5,7] $ .

For the second query, $ sum=2+3+5+7=17 $ .

After the third query, $ a=[2,4,6,9] $ .

For the fourth query, $ sum=2+4+6=12 $ .

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3

```

### 输出

```
17
12

```



---

---
title: "Ant colony"
layout: "post"
diff: 提高+/省选-
pid: CF474F
tag: ['线段树', '离散化']
---

# Ant colony

## 题目描述

Mole is hungry again. He found one ant colony, consisting of $ n $ ants, ordered in a row. Each ant $ i $ ( $ 1<=i<=n $ ) has a strength $ s_{i} $ .

In order to make his dinner more interesting, Mole organizes a version of «Hunger Games» for the ants. He chooses two numbers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) and each pair of ants with indices between $ l $ and $ r $ (inclusively) will fight. When two ants $ i $ and $ j $ fight, ant $ i $ gets one battle point only if $ s_{i} $ divides $ s_{j} $ (also, ant $ j $ gets one battle point only if $ s_{j} $ divides $ s_{i} $ ).

After all fights have been finished, Mole makes the ranking. An ant $ i $ , with $ v_{i} $ battle points obtained, is going to be freed only if $ v_{i}=r-l $ , or in other words only if it took a point in every fight it participated. After that, Mole eats the rest of the ants. Note that there can be many ants freed or even none.

In order to choose the best sequence, Mole gives you $ t $ segments $ [l_{i},r_{i}] $ and asks for each of them how many ants is he going to eat if those ants fight.

## 输入格式

The first line contains one integer $n$ ($1 ≤ n ≤ 10^5$), the size of the ant colony.

The second line contains $n$ integers $s_1, s_2, \ldots, s_n$ ($1 ≤ s_i ≤ 10^9$), the strengths of the ants.

The third line contains one integer $t$ ($1 ≤ t ≤ 10^5$), the number of test cases.

Each of the next $t$ lines contains two integers $l_i$ and $r_i$ ($1 ≤ l_i ≤ r_i ≤ n$), describing one query.

## 输出格式

Print to the standard output $t$ lines. The $i$-th line contains number of ants that Mole eats from the segment $[l_i, r_i]$.

## 说明/提示

In the first test battle points for each ant are $v = [4, 0, 2, 0, 2]$, so ant number $1$ is freed. Mole eats the ants $2, 3, 4, 5$.

In the second test case battle points are $v = [0, 2, 0, 2]$, so no ant is freed and all of them are eaten by Mole.

In the third test case battle points are $v = [2, 0, 2]$, so ants number $3$ and $5$ are freed. Mole eats only the ant $4$.

In the fourth test case battle points are $v = [0, 1]$, so ant number $5$ is freed. Mole eats the ant $4$.

## 样例 #1

### 输入

```
5
1 3 2 4 2
4
1 5
2 5
3 5
4 5

```

### 输出

```
4
4
1
1

```



---

---
title: "Interesting Array"
layout: "post"
diff: 提高+/省选-
pid: CF482B
tag: ['线段树', '进制', '构造']
---

# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输入格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输出格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3

```

### 输出

```
YES
3 3 3

```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2

```

### 输出

```
NO

```



---

---
title: "Traffic Jams in the Land"
layout: "post"
diff: 提高+/省选-
pid: CF498D
tag: ['线段树']
---

# Traffic Jams in the Land

## 题目描述

Some country consists of $ (n+1) $ cities, located along a straight highway. Let's number the cities with consecutive integers from $ 1 $ to $ n+1 $ in the order they occur along the highway. Thus, the cities are connected by $ n $ segments of the highway, the $ i $ -th segment connects cities number $ i $ and $ i+1 $ . Every segment of the highway is associated with a positive integer $ a_{i}&gt;1 $ — the period of traffic jams appearance on it.

In order to get from city $ x $ to city $ y $ ( $ x&lt;y $ ), some drivers use the following tactics.

Initially the driver is in city $ x $ and the current time $ t $ equals zero. Until the driver arrives in city $ y $ , he perfors the following actions:

- if the current time $ t $ is a multiple of $ a_{x} $ , then the segment of the highway number $ x $ is now having traffic problems and the driver stays in the current city for one unit of time (formally speaking, we assign $ t=t+1 $ );
- if the current time $ t $ is not a multiple of $ a_{x} $ , then the segment of the highway number $ x $ is now clear and that's why the driver uses one unit of time to move to city $ x+1 $ (formally, we assign $ t=t+1 $ and $ x=x+1 $ ).

You are developing a new traffic control system. You want to consecutively process $ q $ queries of two types:

1. determine the final value of time $ t $ after the ride from city $ x $ to city $ y $ ( $ x&lt;y $ ) assuming that we apply the tactics that is described above. Note that for each query $ t $ is being reset to $ 0 $ .
2. replace the period of traffic jams appearing on the segment number $ x $ by value $ y $ (formally, assign $ a_{x}=y $ ).

Write a code that will effectively process the queries given above.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of highway segments that connect the $ n+1 $ cities.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 2<=a_{i}<=6 $ ) — the periods of traffic jams appearance on segments of the highway.

The next line contains a single integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries to process.

The next $ q $ lines contain the descriptions of the queries in the format $ c $ , $ x $ , $ y $ ( $ c $ — the query type).

If $ c $ is character 'A', then your task is to process a query of the first type. In this case the following constraints are satisfied: $ 1<=x&lt;y<=n+1 $ .

If $ c $ is character 'C', then you need to process a query of the second type. In such case, the following constraints are satisfied: $ 1<=x<=n $ , $ 2<=y<=6 $ .

## 输出格式

For each query of the first type output a single integer — the final value of time $ t $ after driving from city $ x $ to city $ y $ . Process the queries in the order in which they are given in the input.

## 样例 #1

### 输入

```
10
2 5 3 2 3 5 3 4 2 4
10
C 10 6
A 2 6
A 1 3
C 3 4
A 3 11
A 4 9
A 5 6
C 7 3
A 8 10
A 2 5

```

### 输出

```
5
3
14
6
2
4
4

```



---

---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF558E
tag: ['字符串', '线段树', '排序']
---

# A Simple Task

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 输入格式

The first line will contain two integers $ n,q $ ( $ 1<=n<=10^{5} $ , $ 0<=q<=50000 $ ), the length of the string and the number of queries respectively.

Next line contains a string $ S $ itself. It contains only lowercase English letters.

Next $ q $ lines will contain three integers each $ i,j,k $ ( $ 1<=i<=j<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/7c3e064c95015e1bd5569e78df83991726b5fb24.png)).

## 输出格式

Output one line, the string $ S $ after applying the queries.

## 说明/提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 样例 #1

### 输入

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1

```

### 输出

```
cbcaaaabdd
```

## 样例 #2

### 输入

```
10 1
agjucbvdfk
1 10 1

```

### 输出

```
abcdfgjkuv
```



---

---
title: "New Year Tree"
layout: "post"
diff: 提高+/省选-
pid: CF620E
tag: ['线段树', '状态合并', '进制']
---

# New Year Tree

## 题目描述

The New Year holidays are over, but Resha doesn't want to throw away the New Year tree. He invited his best friends Kerim and Gural to help him to redecorate the New Year tree.

The New Year tree is an undirected tree with $ n $ vertices and root in the vertex $ 1 $ .

You should process the queries of the two types:

1. Change the colours of all vertices in the subtree of the vertex $ v $ to the colour $ c $ .
2. Find the number of different colours in the subtree of the vertex $ v $ .

## 输入格式

The first line contains two integers $ n,m $ ( $ 1<=n,m<=4·10^{5} $ ) — the number of vertices in the tree and the number of the queries.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=60 $ ) — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j},y_{j} $ ( $ 1<=x_{j},y_{j}<=n $ ) — the vertices of the $ j $ -th edge. It is guaranteed that you are given correct undirected tree.

The last $ m $ lines contains the description of the queries. Each description starts with the integer $ t_{k} $ ( $ 1<=t_{k}<=2 $ ) — the type of the $ k $ -th query. For the queries of the first type then follows two integers $ v_{k},c_{k} $ ( $ 1<=v_{k}<=n,1<=c_{k}<=60 $ ) — the number of the vertex whose subtree will be recoloured with the colour $ c_{k} $ . For the queries of the second type then follows integer $ v_{k} $ ( $ 1<=v_{k}<=n $ ) — the number of the vertex for which subtree you should find the number of different colours.

## 输出格式

For each query of the second type print the integer $ a $ — the number of different colours in the subtree of the vertex given in the query.

Each of the numbers should be printed on a separate line in order of query appearing in the input.

## 样例 #1

### 输入

```
7 10
1 1 1 1 1 1 1
1 2
1 3
1 4
3 5
3 6
3 7
1 3 2
2 1
1 4 3
2 1
1 2 5
2 1
1 6 4
2 1
2 2
2 3

```

### 输出

```
2
3
4
5
1
2

```

## 样例 #2

### 输入

```
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4

```

### 输出

```
6
1
3
3
2
1
2
3
5
5
1
2
2
1
1
1
2
3

```



---

---
title: "Mishka and Interesting sum"
layout: "post"
diff: 提高+/省选-
pid: CF703D
tag: ['线段树', '树状数组', '离散化']
---

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 输入格式

The first line of the input contains single integer $ n $ ( $ 1<=n<=1000000 $ ) — the number of elements in the array.

The second line of the input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — array elements.

The third line of the input contains single integer $ m $ ( $ 1<=m<=1000000 $ ) — the number of queries.

Each of the next $ m $ lines describes corresponding query by a pair of integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) — the bounds of query segment.

## 输出格式

Print $ m $ non-negative integers — the answers for the queries in the order they appear in the input.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5

```

### 输出

```
0
3
1
3
2

```



---

---
title: "PolandBall and Polygon"
layout: "post"
diff: 提高+/省选-
pid: CF755D
tag: ['数学', '线段树', '树状数组']
---

# PolandBall and Polygon

## 题目描述

PolandBall has such a convex polygon with $ n $ veritces that no three of its diagonals intersect at the same point. PolandBall decided to improve it and draw some red segments.

He chose a number $ k $ such that $ gcd(n,k)=1 $ . Vertices of the polygon are numbered from $ 1 $ to $ n $ in a clockwise way. PolandBall repeats the following process $ n $ times, starting from the vertex $ 1 $ :

Assume you've ended last operation in vertex $ x $ (consider $ x=1 $ if it is the first operation). Draw a new segment from vertex $ x $ to $ k $ -th next vertex in clockwise direction. This is a vertex $ x+k $ or $ x+k-n $ depending on which of these is a valid index of polygon's vertex.

Your task is to calculate number of polygon's sections after each drawing. A section is a clear area inside the polygon bounded with drawn diagonals or the polygon's sides.

## 输入格式

There are only two numbers in the input: $ n $ and $ k $ ( $ 5<=n<=10^{6} $ , $ 2<=k<=n-2 $ , $ gcd(n,k)=1 $ ).

## 输出格式

You should print $ n $ values separated by spaces. The $ i $ -th value should represent number of polygon's sections after drawing first $ i $ lines.

## 说明/提示

The greatest common divisor (gcd) of two integers $ a $ and $ b $ is the largest positive integer that divides both $ a $ and $ b $ without a remainder.

For the first sample testcase, you should output "2 3 5 8 11". Pictures below correspond to situations after drawing lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/4990bd3c0c7dd5836fdcc579f970dcdca8dbd872.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/6451ef95db9646f275ba3ec79da2a8d5b0b028d0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/da900464c60a214ba6c5242ba8fc65122871a490.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/a8b3c0780f20737fed12f744f83c0f1eab3d538f.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/c214010a205eb51e891b2376aacedcb09475410e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/ac2e2680dc9611afb331663a01c918e0c001e832.png)

## 样例 #1

### 输入

```
5 2

```

### 输出

```
2 3 5 8 11 
```

## 样例 #2

### 输入

```
10 3

```

### 输出

```
2 3 4 6 9 12 16 21 26 31 
```



---

---
title: "MEX Queries"
layout: "post"
diff: 提高+/省选-
pid: CF817F
tag: ['线段树', '离散化']
---

# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ).

Next $ n $ lines contain three integer numbers $ t,l,r $ ( $ 1<=t<=3,1<=l<=r<=10^{18} $ ) — type of the query, left and right bounds.

## 输出格式

Print MEX of the set after each query.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3

```

### 输出

```
1
3
1

```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6

```

### 输出

```
4
4
4
1

```



---

---
title: "The Bakery"
layout: "post"
diff: 提高+/省选-
pid: CF833B
tag: ['动态规划 DP', '线段树', '枚举', '动态规划优化']
---

# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=35000 $ , $ 1<=k<=min(n,50) $ ) – the number of cakes and the number of boxes, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) – the types of cakes in the order the oven bakes them.

## 输出格式

Print the only integer – the maximum total value of all boxes with cakes.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7

```

### 输出

```
6

```



---

---
title: "Sum of Medians"
layout: "post"
diff: 提高+/省选-
pid: CF85D
tag: ['线段树', '枚举', '排序', '分块']
---

# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=10^{5} $ ), the number of operations performed.

Then each of $ n $ lines contains the description of one of the three operations:

- add $ x $  — add the element $ x $ to the set;
- del $ x $  — delete the element $ x $ from the set;
- sum — find the sum of medians of the set.

For any add $ x $  operation it is true that the element $ x $ is not included in the set directly before the operation.

For any del $ x $  operation it is true that the element $ x $ is included in the set directly before the operation.

All the numbers in the input are positive integers, not exceeding $ 10^{9} $ .

## 输出格式

For each operation sum print on the single line the sum of medians of the current set. If the set is empty, print 0.

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams (also you may use the %I64d specificator).

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum

```

### 输出

```
3

```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum

```

### 输出

```
5
11
13

```



---

---
title: "High Cry"
layout: "post"
diff: 提高+/省选-
pid: CF875D
tag: ['线段树', '概率论', '栈']
---

# High Cry

## 题目描述

Disclaimer: there are lots of untranslateable puns in the Russian version of the statement, so there is one more reason for you to learn Russian :)

Rick and Morty like to go to the ridge High Cry for crying loudly — there is an extraordinary echo. Recently they discovered an interesting acoustic characteristic of this ridge: if Rick and Morty begin crying simultaneously from different mountains, their cry would be heard between these mountains up to the height equal the bitwise OR of mountains they've climbed and all the mountains between them.

Bitwise OR is a binary operation which is determined the following way. Consider representation of numbers $ x $ and $ y $ in binary numeric system (probably with leading zeroes) $ x=x_{k}...\ x_{1}x_{0} $ and $ y=y_{k}...\ y_{1}y_{0} $ . Then $ z=x | y $ is defined following way: $ z=z_{k}...\ z_{1}z_{0} $ , where $ z_{i}=1 $ , if $ x_{i}=1 $ or $ y_{i}=1 $ , and $ z_{i}=0 $ otherwise. In the other words, digit of bitwise OR of two numbers equals zero if and only if digits at corresponding positions is both numbers equals zero. For example bitwise OR of numbers $ 10=1010_{2} $ and $ 9=1001_{2} $ equals $ 11=1011_{2} $ . In programming languages C/C++/Java/Python this operation is defined as «|», and in Pascal as «or».

Help Rick and Morty calculate the number of ways they can select two mountains in such a way that if they start crying from these mountains their cry will be heard above these mountains and all mountains between them. More formally you should find number of pairs $ l $ and $ r $ ( $ 1<=l&lt;r<=n $ ) such that bitwise OR of heights of all mountains between $ l $ and $ r $ (inclusive) is larger than the height of any mountain at this interval.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=200000 $ ), the number of mountains in the ridge.

Second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{9} $ ), the heights of mountains in order they are located in the ridge.

## 输出格式

Print the only integer, the number of ways to choose two different mountains.

## 说明/提示

In the first test case all the ways are pairs of mountains with the numbers (numbering from one):

 $ (1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5) $ In the second test case there are no such pairs because for any pair of mountains the height of cry from them is $ 3 $ , and this height is equal to the height of any mountain.

## 样例 #1

### 输入

```
5
3 2 1 6 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
3 3 3 3

```

### 输出

```
0

```



---

---
title: "Mass Change Queries"
layout: "post"
diff: 提高+/省选-
pid: CF911G
tag: ['线段树', '枚举']
---

# Mass Change Queries

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to process $ q $ queries to this array; each query is given as four numbers $ l $ , $ r $ , $ x $ and $ y $ , denoting that for every $ i $ such that $ l<=i<=r $ and $ a_{i}=x $ you have to set $ a_{i} $ equal to $ y $ .

Print the array after all queries are processed.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ) — the size of array $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=100 $ ) — the elements of array $ a $ .

The third line contains one integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries you have to process.

Then $ q $ lines follow. $ i $ -th line contains four integers $ l $ , $ r $ , $ x $ and $ y $ denoting $ i $ -th query ( $ 1<=l<=r<=n $ , $ 1<=x,y<=100 $ ).

## 输出格式

Print $ n $ integers — elements of array $ a $ after all changes are made.

## 样例 #1

### 输入

```
5
1 2 3 4 5
3
3 5 3 5
1 5 5 1
1 5 1 5

```

### 输出

```
5 2 5 4 5 
```



---

---
title: "SUM and REPLACE"
layout: "post"
diff: 提高+/省选-
pid: CF920F
tag: ['线段树', '递归', '分块']
---

# SUM and REPLACE

## 题目描述

Let $ D(x) $ be the number of positive divisors of a positive integer $ x $ . For example, $ D(2)=2 $ ( $ 2 $ is divisible by $ 1 $ and $ 2 $ ), $ D(6)=4 $ ( $ 6 $ is divisible by $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ ).

You are given an array $ a $ of $ n $ integers. You have to process two types of queries:

1. REPLACE $ l $ $ r $ — for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/8c67e39bbb4a436ecb9bbf84b28c1b332f05ca94.png) replace $ a_{i} $ with $ D(a_{i}) $ ;
2. SUM $ l $ $ r $ — calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/1deabb69ce88e0c9a5b8e5232e5782460ccfe87b.png).

Print the answer for each SUM query.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of elements in the array and the number of queries to process, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Then $ m $ lines follow, each containing $ 3 $ integers $ t_{i} $ , $ l_{i} $ , $ r_{i} $ denoting $ i $ -th query. If $ t_{i}=1 $ , then $ i $ -th query is REPLACE $ l_{i} $ $ r_{i} $ , otherwise it's SUM $ l_{i} $ $ r_{i} $ ( $ 1<=t_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ ).

There is at least one SUM query.

## 输出格式

For each SUM query print the answer to it.

## 样例 #1

### 输入

```
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7

```

### 输出

```
30
13
4
22

```



---

---
title: "Addition on Segments"
layout: "post"
diff: 提高+/省选-
pid: CF981E
tag: ['线段树', '分治', '背包 DP']
---

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 10^{4} $ ) — the length of the array and the number of queries in the initial problem.

The following $ q $ lines contain queries, one per line. The $ i $ -th of these lines contains three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ), denoting a query of adding $ x_i $ to the segment from $ l_i $ -th to $ r_i $ -th elements of the array, inclusive.

## 输出格式

In the first line print the only integer $ k $ , denoting the number of integers from $ 1 $ to $ n $ , inclusive, that can be equal to the maximum in the array after applying some subset (possibly empty) of the given operations.

In the next line print these $ k $ integers from $ 1 $ to $ n $ — the possible values of the maximum. Print these integers in increasing order.

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4

```

### 输出

```
4
1 2 3 4 

```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2

```

### 输出

```
3
1 2 3 

```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6

```

### 输出

```
6
2 3 5 6 8 9 

```



---

