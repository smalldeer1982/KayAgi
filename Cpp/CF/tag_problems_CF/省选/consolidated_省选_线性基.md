---
title: "Gellyfish and Forget-Me-Not"
layout: "post"
diff: 省选/NOI-
pid: CF2115D
tag: ['贪心', '线性基']
---

# Gellyfish and Forget-Me-Not

## 题目描述

Gellyfish and Flower are playing a game.

The game consists of two arrays of $ n $ integers $ a_1,a_2,\ldots,a_n $ and $ b_1,b_2,\ldots,b_n $ , along with a binary string $ c_1c_2\ldots c_n $ of length $ n $ .

There is also an integer $ x $ which is initialized to $ 0 $ .

The game consists of $ n $ rounds. For $ i = 1,2,\ldots,n $ , the round proceeds as follows:

1. If $ c_i = \mathtt{0} $ , Gellyfish will be the active player. Otherwise, if $ c_i = \mathtt{1} $ , Flower will be the active player.
2. The active player will perform exactly one of the following operations: 
  - Set $ x:=x \oplus a_i $ .
  - Set $ x:=x \oplus b_i $ .

Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Gellyfish wants to minimize the final value of $  x  $ after $  n  $ rounds, while Flower wants to maximize it.

Find the final value of $  x  $ after all $  n  $ rounds if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of rounds of the game.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{60} $ ).

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < 2^{60} $ ).

The fourth line of each test case contains a binary string $ c $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the final value of $  x  $ after all $  n  $ rounds.

## 说明/提示

In the first test case, there's only one round and Gellyfish is the active player of that round. Therefore, she will choose $ a_1 $ , and the final value of $ x $ is $ 0 $ .

In the second test case, Flower will be the active player in both rounds. She will choose $ a_1 $ and $ b_2 $ , and the final value of $ x $ is $ a_1 \oplus b_2 = 15 $ . Flower may also choose $ b_1 $ and $ a_2 $ instead for the same result of $ x=a_2 \oplus b_1 = 15 $ .

In the third test case, $ a_1 = b_1 $ so it doesn't matter what decision Gellyfish makes in the first round. In the second round:

- If Flower chooses $ a_2 $ , then $ x $ will become $ 7 $ . Gellyfish will choose $ b_3 $ in the third round, so the final value of $ x $ will be $ 4 $ .
- Otherwise, Flower chooses $ b_2 $ , then $ x $ will become $ 4 $ . Gellyfish will choose $ a_3 $ in the third round, so the final value of $ x $ will be $ 6 $ .

Flower wants to maximize the final value of $ x $ , so Flower will choose $ b_2 $ in the second round. Therefore, the final value of $ x $ will be $ 6 $ .

## 样例 #1

### 输入

```
5
1
0
2
0
2
12 2
13 3
11
3
6 1 2
6 2 3
010
4
1 12 7 2
4 14 4 2
0111
9
0 5 10 6 6 2 6 2 11
7 3 15 3 6 7 6 7 8
110010010
```

### 输出

```
0
15
6
11
5
```



---

---
title: "Xor-matic Number of the Graph"
layout: "post"
diff: 省选/NOI-
pid: CF724G
tag: ['进制', '概率论', '线性基']
---

# Xor-matic Number of the Graph

## 题目描述

给你一个无向图，有n个顶点和m条边，每条边上都有一个非负权值。

我们称一个三元组  $(u,v,s)$ 是有趣的，当且仅当对于 $1 \le u < v \le n$ 且有一条从 $u$ 到 $v$ 的路径(可以经过相同的点和边多次)，其路径上的权值异或和为  $s$。对于一条路径，如果一条边经过了多次，则计算异或和时也应计算多次。不难证明，这样的三元组是有限的。

计算所有有趣的三元组中 $s$ 的和对于 $10^9+7$ 的模数

## 输入格式

第一行包括两个整数  $n,m,(n\in [1,10^5],m\in[0,2*10^5]$  ——图中点数与边数

接下来的  $m$  行每行包括3个整数  $u_i,v_i,t_i(u_i,v_i\in [1,n],t_i\in [0,10^{18}],u_i\not = v_i)$  ——边的两端点序号与边的权值

图中无自环与重边

## 输出格式

输出一个整数，即题目中的答案对于  $10^9+7$  的mod值

感谢@Dimitry_L 提供的翻译

## 样例 #1

### 输入

```
4 4
1 2 1
1 3 2
2 3 3
3 4 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 2
3 4 4
4 1 8

```

### 输出

```
90

```

## 样例 #3

### 输入

```
8 6
1 2 2
2 3 1
2 4 4
4 5 5
4 6 3
7 8 5

```

### 输出

```
62

```



---

---
title: "Shortest Path Problem?"
layout: "post"
diff: 省选/NOI-
pid: CF845G
tag: ['枚举', '线性基']
---

# Shortest Path Problem?

## 题目描述

You are given an undirected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times). You have to find the minimum length of path between vertex $ 1 $ and vertex $ n $ .

Note that graph can contain multiple edges and loops. It is guaranteed that the graph is connected.

## 输入格式

The first line contains two numbers $ n $ and $ m $ ( $ 1<=n<=100000 $ , $ n-1<=m<=100000 $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow, each line containing three integer numbers $ x $ , $ y $ and $ w $ ( $ 1<=x,y<=n $ , $ 0<=w<=10^{8} $ ). These numbers denote an edge that connects vertices $ x $ and $ y $ and has weight $ w $ .

## 输出格式

Print one number — the minimum length of path between vertices $ 1 $ and $ n $ .

## 样例 #1

### 输入

```
3 3
1 2 3
1 3 2
3 2 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2
1 1 3
1 2 3

```

### 输出

```
0

```



---

