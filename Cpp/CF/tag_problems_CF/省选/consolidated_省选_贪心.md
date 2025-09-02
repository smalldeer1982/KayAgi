---
title: "Greedy Change"
layout: "post"
diff: 省选/NOI-
pid: CF10E
tag: ['贪心', '枚举', '向量']
---

# Greedy Change

## 题目描述

给定 $n$ 种货币，每种货币数量无限。 现在要求以最少的货币数目表示一个数 $S$。 一种方法当然是 DP 求一个最优解了， 当然正常人的做法是贪心：每次取最大的不超过当前待表示数的货币。 现在，你的任务是证明正常人的表示法不一定最优：找到最小的 $S$，使得正常人的表示法比理论最优解差，或说明这样的 $S$ 不存在。

## 输入格式

第一行包含一个整数 $n$（$1\leq n\leq 400$）。第二行包含 $n$ 个整数 $a_i$（$1\leq a_i\leq 10^9$）为每个硬币面值。保证 $a$ 数组严格降序排列且 $a_n=1$。

## 输出格式

如果贪心能以最优的方式求出所以和，输出 `-1`。否则以非最优方式输出贪婪算法收集的最小和。

## 样例 #1

### 输入

```
5
25 10 5 2 1

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
3
4 3 1

```

### 输出

```
6

```



---

---
title: "Secret Letters"
layout: "post"
diff: 省选/NOI-
pid: CF1120F
tag: ['贪心']
---

# Secret Letters

## 题目描述

Little W and Little P decided to send letters to each other regarding the most important events during a day. There are $ n $ events during a day: at time moment $ t_i $ something happens to the person $ p_i $ ( $ p_i $ is either W or P, denoting Little W and Little P, respectively), so he needs to immediately send a letter to the other person. They can send a letter using one of the two ways:

- Ask Friendly O to deliver the letter directly. Friendly O takes $ d $ acorns for each letter.
- Leave the letter at Wise R's den. Wise R values free space, so he takes $ c \cdot T $ acorns for storing a letter for a time segment of length $ T $ . The recipient can take a letter from Wise R either when he leaves his own letter at Wise R's den, or at time moment $ t_{n + 1} $ , when everybody comes to Wise R for a tea. It is not possible to take a letter from Wise R's den at other time moments. The friends can store as many letters at Wise R's den as they want, paying for each one separately.

Help the friends determine the minimum possible total cost of sending all letters.

## 输入格式

The first line contains three integers $ n, c, d $ ( $ 1 \leq n \leq 10^5 $ , $ 1 \leq c \leq 10^2 $ , $ 1 \leq d \leq 10^8 $ ) — the number of letters, the cost of storing a letter for one time unit at Wise R's den and the cost of delivering a letter via Friendly O.

The next $ n $ describe the events. The $ i $ -th of them contains an integer $ t_i $ and a character $ p_i $ ( $ 0 \leq t_i \leq 10^6 $ , $ p_i $ is either W or P) — the time the $ i $ -th event happens and the person the event happens to.

The last line contains a single integer $ t_{n + 1} $ ( $ 0 \leq t_{n+1} \leq 10^6 $ ) — the time when everybody comes to Wise R for a tea and takes all remaining letters.

It is guaranteed that $ t_i < t_{i + 1} $ for all $ i $ from $ 1 $ to $ n $ .

## 输出格式

Print a single integer — the minimum possible cost of delivery of all letters.

## 说明/提示

One of optimal solutions in the first example:

- At time moment 0 Little P leaves the letter at Wise R's den.
- At time moment 1 Little W leaves his letter at Wise R's den and takes Little P's letter. This letter is at the den from time moment 0 to time moment 1, it costs $ 1 $ acorn.
- At time moment 3 Little P sends his letter via Friendly O, it costs $ 4 $ acorns.
- At time moment 5 Little P leaves his letter at the den, receiving Little W's letter which storage costs 4 acorns.
- At time moment 8 Little P leaves one more letter at the den.
- At time moment 10 Little W comes to the den for a tea and receives the two letters, paying 5 and 2 acorns.

The total cost of delivery is thus $ 1 + 4 + 4 + 5 + 2 = 16 $ acorns.

## 样例 #1

### 输入

```
5 1 4
0 P
1 W
3 P
5 P
8 P
10

```

### 输出

```
16

```

## 样例 #2

### 输入

```
10 10 94
17 W
20 W
28 W
48 W
51 P
52 W
56 W
62 P
75 P
78 P
87

```

### 输出

```
916

```



---

---
title: "Construct the Binary Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1311E
tag: ['贪心', '构造']
---

# Construct the Binary Tree

## 题目描述

You are given two integers $ n $ and $ d $ . You need to construct a rooted binary tree consisting of $ n $ vertices with a root at the vertex $ 1 $ and the sum of depths of all vertices equals to $ d $ .

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . The depth of the vertex $ v $ is the length of the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. The binary tree is such a tree that no vertex has more than $ 2 $ children.

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The only line of each test case contains two integers $ n $ and $ d $ ( $ 2 \le n, d \le 5000 $ ) — the number of vertices in the tree and the required sum of depths of all vertices.

It is guaranteed that the sum of $ n $ and the sum of $ d $ both does not exceed $ 5000 $ ( $ \sum n \le 5000, \sum d \le 5000 $ ).

## 输出格式

For each test case, print the answer.

If it is impossible to construct such a tree, print "NO" (without quotes) in the first line. Otherwise, print "{YES}" in the first line. Then print $ n-1 $ integers $ p_2, p_3, \dots, p_n $ in the second line, where $ p_i $ is the parent of the vertex $ i $ . Note that the sequence of parents you print should describe some binary tree.

## 说明/提示

Pictures corresponding to the first and the second test cases of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/514e626aa001052fb71d69f413a53a8e6f0cb5f0.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/6407c12a699d89084b087667ed6f21f3aeed074d.png)

## 样例 #1

### 输入

```
3
5 7
10 19
10 18
```

### 输出

```
YES
1 2 1 3 
YES
1 2 3 3 9 9 2 1 6 
NO
```



---

---
title: "Johnny and James"
layout: "post"
diff: 省选/NOI-
pid: CF1361D
tag: ['贪心']
---

# Johnny and James

## 题目描述

James Bond, Johnny's favorite secret agent, has a new mission. There are $ n $ enemy bases, each of them is described by its coordinates so that we can think about them as points in the Cartesian plane.

The bases can communicate with each other, sending a signal, which is the ray directed from the chosen point to the origin or in the opposite direction. The exception is the central base, which lies at the origin and can send a signal in any direction.

When some two bases want to communicate, there are two possible scenarios. If they lie on the same line with the origin, one of them can send a signal directly to the other one. Otherwise, the signal is sent from the first base to the central, and then the central sends it to the second base. We denote the distance between two bases as the total Euclidean distance that a signal sent between them has to travel.

Bond can damage all but some $ k $ bases, which he can choose arbitrarily. A damaged base can't send or receive the direct signal but still can pass it between two working bases. In particular, James can damage the central base, and the signal can still be sent between any two undamaged bases as before, so the distance between them remains the same. What is the maximal sum of the distances between all pairs of remaining bases that 007 can achieve by damaging exactly $ n - k $ of them?

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (2 \leq k \leq n \leq 5 \cdot 10^5) $ — the total number of bases and number of bases that have to remain, respectively.

Each of the next $ n $ lines contains two integers $ x $ and $ y $ $ (-10^9 \leq x, y \leq 10^9) $ , $ i $ -th line contains coordinates of the $ i $ -th base. You can assume that no two points coincide and that one of them is $ (0, 0) $ .

## 输出格式

You should output one number — the maximal possible sum of distances between all pairs of some $ k $ from given bases. Your answer will be accepted if the absolute or relative error is less than $ 10^{-6} $ .

## 说明/提示

In the first example, in an optimal solution Bond doesn't destroy bases with indices $ 4 $ and $ 6 $ (marked in orange):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/29ad68544f86790b6a0b555f8c0a2679b5e08738.png)The following picture represents an optimal solution for the second example. These bases are are not destroyed: $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ (marked in orange).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/92cf75fde42075888e781e37ed18062bceac6b94.png)An optimal solution for the third test is visible in the picture. Only bases $ 3 $ , $ 4 $ , $ 5 $ are destroyed. Again, the not destroyed bases are marked in orange.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/123419ed05a0a9745e9c96cf4f22f1857630f66d.png)

## 样例 #1

### 输入

```
6 2
0 0
1 1
2 2
3 3
0 1
0 2
```

### 输出

```
6.24264069
```

## 样例 #2

### 输入

```
6 5
0 0
1 1
2 2
3 3
0 1
0 2
```

### 输出

```
32.62741700
```

## 样例 #3

### 输入

```
13 10
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
8 0
9 0
0 -2
0 1
0 2
```

### 输出

```
237.00000000
```

## 样例 #4

### 输入

```
10 5
2 2
4 4
3 5
6 10
0 5
0 0
5 0
10 0
0 10
4 7
```

### 输出

```
181.52406315
```



---

---
title: "Village (Maximum)"
layout: "post"
diff: 省选/NOI-
pid: CF1387B2
tag: ['贪心', '树形数据结构']
---

# Village (Maximum)

## 题目描述

### 题意

[最小值版本](https://www.luogu.com.cn/problem/CF1387B1)

村里 $n$ 个房子构成了一个 $n$ 点 $n-1$ 条边的**树**结构（下标从 $1$ 开始），每条边长度均为 $1$。一开始每个房子里分别有一个村民。

现在所有村民都需要搬家（改变自己所在的点），搬家后依然需要满足每个房子里**有且只有一个**村民。也就是说，如果原本位于点 $i$ 的村民搬到了点 $v_i$，那么应当满足：

- 对于任意点 $i$，有 $i \neq v_i$。

- 对于任意两个不同的点 $i$ 与 $j$，有 $v_i \neq v_j$。

村民 $i$ 搬家的花费是点 $i$ 到点 $v_i$ 的树上距离（即树上二点间相隔的边数），总花费为所有村民花费之和。求总花费的**最大值**及其方案。

## 输入格式

第一行一个正整数 $n$，表示树的点数。

接下来 $n-1$ 行每行二整数 $a$ 和 $b$，表示树上有一条连接 $a$ 和 $b$，长度为 $1$ 的边。

## 输出格式

第一行一个整数，表示总花费的**最大值**。

第二行 $n$ 个整数 $v_1 \dots v_n$，表示搬家的方案：如果原本位于点 $i$ 的村民搬到了点 $v_i$。

输出**任意一组**合法方案即可。

## 说明/提示

- $2 \leq n \leq 10^5$

- $1 \leq a,b \leq n$

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
8
4 3 2 1
```

## 样例 #2

### 输入

```
7
4 2
5 7
3 4
6 3
1 3
4 5
```

### 输出

```
18
2 7 4 1 3 5 6
```



---

---
title: "Squid Game"
layout: "post"
diff: 省选/NOI-
pid: CF1610H
tag: ['贪心']
---

# Squid Game

## 题目描述

After watching the new over-rated series Squid Game, Mashtali and Soroush decided to hold their own Squid Games! Soroush agreed to be the host and will provide money for the winner's prize, and Mashtali became the Front Man!

 $ m $ players registered to play in the games to win the great prize, but when Mashtali found out how huge the winner's prize is going to be, he decided to kill eliminate all the players so he could take the money for himself!

Here is how evil Mashtali is going to eliminate players:

There is an unrooted tree with $ n $ vertices. Every player has $ 2 $ special vertices $ x_i $ and $ y_i $ .

In one operation, Mashtali can choose any vertex $ v $ of the tree. Then, for each remaining player $ i $ he finds a vertex $ w $ on the simple path from $ x_i $ to $ y_i $ , which is the closest to $ v $ . If $ w\ne x_i $ and $ w\ne y_i $ , player $ i $ will be eliminated.

Now Mashtali wondered: "What is the minimum number of operations I should perform so that I can remove every player from the game and take the money for myself?"

Since he was only thinking about the money, he couldn't solve the problem by himself and asked for your help!

## 输入格式

The first line contains $ 2 $ integer $ n $ and $ m $ $ (1 \le n, m \le 3 \cdot 10^5) $ — the number of vertices of the tree and the number of players.

The second line contains $ n-1 $ integers $ par_2, par_3, \ldots, par_n $ $ (1 \le par_i < i) $ — denoting an edge between node $ i $ and $ par_i $ .

The $ i $ -th of the following $ m $ lines contains two integers $ x_i $ and $ y_i $ $ (1 \le x_i, y_i \le n, x_i \ne y_i) $ — the special vertices of the $ i $ -th player.

## 输出格式

Print the minimum number of operations Mashtali has to perform.

If there is no way for Mashtali to eliminate all the players, print $ -1 $ .

## 说明/提示

Explanation for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1610H/2f92b74ef3689103fc27552fedd0869997b9492b.png)In the first operation, Mashtali can choose vertex $ 1 $ and eliminate players with colors red and blue. In the second operation, he can choose vertex $ 6 $ and eliminate the player with orange color.In the second sample, Mashtali can't eliminate the first player.

## 样例 #1

### 输入

```
6 3
1 1 1 4 4
1 5
3 4
2 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3
1 1 3 3
1 2
1 4
1 5
```

### 输出

```
-1
```



---

---
title: "Middle Duplication"
layout: "post"
diff: 省选/NOI-
pid: CF1623E
tag: ['贪心', '树形数据结构']
---

# Middle Duplication

## 题目描述

A binary tree of $ n $ nodes is given. Nodes of the tree are numbered from $ 1 $ to $ n $ and the root is the node $ 1 $ . Each node can have no child, only one left child, only one right child, or both children. For convenience, let's denote $ l_u $ and $ r_u $ as the left and the right child of the node $ u $ respectively, $ l_u = 0 $ if $ u $ does not have the left child, and $ r_u = 0 $ if the node $ u $ does not have the right child.

Each node has a string label, initially is a single character $ c_u $ . Let's define the string representation of the binary tree as the concatenation of the labels of the nodes in the in-order. Formally, let $ f(u) $ be the string representation of the tree rooted at the node $ u $ . $ f(u) $ is defined as follows: $ $$$ f(u) = \begin{cases} \texttt{<empty string>}, & \text{if }u = 0; \\ f(l_u) + c_u + f(r_u) & \text{otherwise}, \end{cases}  $ $  where  $ + $  denotes the string concatenation operation.</p><p>This way, the string representation of the tree is  $ f(1) $ .</p><p>For each node, we can <span class="tex-font-style-it">duplicate</span> its label <span class="tex-font-style-bf">at most once</span>, that is, assign  $ c\_u $  with  $ c\_u + c\_u $ , but only if  $ u $  is the root of the tree, or if its parent also has its label duplicated.</p><p>You are given the tree and an integer  $ k $ . What is the lexicographically smallest string representation of the tree, if we can duplicate labels of at most  $ k $  nodes?</p><p>A string  $ a $  is lexicographically smaller than a string  $ b $  if and only if one of the following holds: </p><ul> <li>  $ a $  is a prefix of  $ b $ , but  $ a \\ne b $ ; </li><li> in the first position where  $ a $  and  $ b $  differ, the string  $ a $  has a letter that appears earlier in the alphabet than the corresponding letter in  $ b$$$.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ).

The second line contains a string $ c $ of $ n $ lower-case English letters, where $ c_i $ is the initial label of the node $ i $ for $ 1 \le i \le n $ . Note that the given string $ c $ is not the initial string representation of the tree.

The $ i $ -th of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 0 \le l_i, r_i \le n $ ). If the node $ i $ does not have the left child, $ l_i = 0 $ , and if the node $ i $ does not have the right child, $ r_i = 0 $ .

It is guaranteed that the given input forms a binary tree, rooted at $ 1 $ .

## 输出格式

Print a single line, containing the lexicographically smallest string representation of the tree if at most $ k $ nodes have their labels duplicated.

## 说明/提示

The images below present the tree for the examples. The number in each node is the node number, while the subscripted letter is its label. To the right is the string representation of the tree, with each letter having the same color as the corresponding node.

Here is the tree for the first example. Here we duplicated the labels of nodes $ 1 $ and $ 3 $ . We should not duplicate the label of node $ 2 $ because it would give us the string "bbaaab", which is lexicographically greater than "baaaab".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/8e9bc3e39a0385947c6f1b7db86d59f03e67d645.png)In the second example, we can duplicate the labels of nodes $ 1 $ and $ 2 $ . Note that only duplicating the label of the root will produce a worse result than the initial string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/dca73cc51ea6acbb902f1315cd4594d96b4d3160.png)In the third example, we should not duplicate any character at all. Even though we would want to duplicate the label of the node $ 3 $ , by duplicating it we must also duplicate the label of the node $ 2 $ , which produces a worse result.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/967abfb10aaf17f05381c2a0e362eea9288d9011.png)There is no way to produce string "darkkcyan" from a tree with the initial string representation "darkcyan" :(.

## 样例 #1

### 输入

```
4 3
abab
2 3
0 0
0 4
0 0
```

### 输出

```
baaaab
```

## 样例 #2

### 输入

```
8 2
kadracyn
2 5
3 4
0 0
0 0
6 8
0 7
0 0
0 0
```

### 输出

```
daarkkcyan
```

## 样例 #3

### 输入

```
8 3
kdaracyn
2 5
0 3
0 4
0 0
6 8
0 7
0 0
0 0
```

### 输出

```
darkcyan
```



---

---
title: "Connectivity Addicts"
layout: "post"
diff: 省选/NOI-
pid: CF1738F
tag: ['贪心', '构造']
---

# Connectivity Addicts

## 题目描述

This is an interactive problem.

Given a simple undirected graph with $ n $ vertices numbered from $ 1 $ to $ n $ , your task is to color all the vertices such that for every color $ c $ , the following conditions hold:

1. The set of vertices with color $ c $ is connected;
2. $ s_c \leq n_c^2 $ , where $ n_c $ is the number of vertices with color $ c $ , and $ s_c $ is the sum of degrees of vertices with color $ c $ .

 It can be shown that there always exists a way to color all the vertices such that the above conditions hold. Initially, you are only given the number $ n $ of vertices and the degree of each vertex.

In each query, you can choose a vertex $ u $ . As a response, you will be given the $ k $ -th edge incident to $ u $ , if this is the $ k $ -th query on vertex $ u $ .

You are allowed to make at most $ n $ queries.

An undirected graph is simple if it does not contain multiple edges or self-loops.

The degree of a vertex is the number of edges incident to it.

A set $ S $ of vertices is connected if for every two different vertices $ u, v \in S $ , there is a path, which only passes through vertices in $ S $ , that connects $ u $ and $ v $ . That is, there is a sequence of edges $ (u_1, v_1), (u_2, v_2), \dots, (u_k, v_k) $ with $ k \geq 1 $ such that

1. $ u_1 = u $ , $ v_k = v $ , and $ v_i = u_{i+1} $ for every $ 1 \leq i < k $ ; and
2. $ u_k \in S $ and $ v_k \in S $ for every $ 1 \leq i \leq k $ .

 Especially, a set containing only one vertex is connected.

## 输出格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The following lines contain the description and the interactive section of each test case.

For each test case, you begin the interaction by reading an integer $ n $ ( $ 1\le n \le 1000 $ ) in the first line, indicating the number of vertices in the graph.

The second line contains $ n $ integers $ d_1, d_2, \dots, d_n $ ( $ 0 \leq d_i \leq n - 1 $ ), where $ d_i $ is the degree of vertex $ i $ .

To make a query on vertex $ u $ ( $ 1 \leq u \leq n $ ), you should output

- "? $ u $ "

 in a separate line. If this is the $ k $ -th query on vertex $ u $ , vertex $ e_{u, k} $ will be given in the next separate line, where $ \left(u, e_{u, k}\right) $ is the $ k $ -th edge incident to vertex $ u $ . In case of $ k > d_u $ , define $ e_{u, k} = -1 $ . You should make no more than $ n $  "?" queries.To give the answer, you should output

- "! $ c_1 $ $ c_2 $ $ \dots $ $ c_n $ "

 in a separate line, where $ c_i $ ( $ 1 \leq c_i \leq n $ ) is the color of vertex $ i $ . After that, your program should continue to the next test case, or terminate if this is the last test case. It is guaranteed that the graph is a simple undirected graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

In case your query format is invalid, or you have made more than $ n $ "?" queries, you will receive Wrong Answer verdict.

After printing a query, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hack Format

The first line of the hack contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ), indicating the number of test cases. The following lines contain the description of each test case.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 1000 $ ), indicating the number of vertices in the graph.

Then $ n $ lines follow. The $ i $ -th line contains an integer $ d_i $ ( $ 0 \leq d_i \leq n - 1 $ ), indicating the degree of vertex $ i $ , and then $ d_i $ distinct integers $ e_{i,1}, e_{i,2}, \dots, e_{i,d_i} $ ( $ 1 \leq e_{i, j} \leq n $ and $ e_{i,j} \neq i $ ), where $ \left(i, e_{i,j}\right) $ is the $ j $ -th edge incident to vertex $ i $ .

It should be guaranteed that the graph is a simple undirected graph.

It should be guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 说明/提示

In the example, there is only one test case.

In the test case, there are $ n = 5 $ vertices with vertices $ 1, 2, 3, 4 $ of degree $ 2 $ and vertex $ 5 $ of degree $ 0 $ . It is obvious that vertex $ 5 $ is isolated, i.e., it does not connect to any other vertices.

A possible interaction is shown in the sample input and output, where $ 4 $ "?" queries are made on vertex $ 1 $ twice and vertex $ 3 $ twice. According to the responses to these queries, we know that each of vertex $ 1 $ and vertex $ 3 $ connects to two vertices $ 2 $ and $ 4 $ .

A possible solution is shown in the sample output, where vertex $ 1 $ and vertex $ 2 $ are colored by $ 1 $ , vertex $ 3 $ and vertex $ 4 $ are colored by $ 2 $ , and vertex $ 5 $ is colored by $ 3 $ . It can be seen that this solution satisfies the required conditions as follows.

- For color $ c = 1 $ , vertex $ 1 $ and vertex $ 2 $ are connected. Moreover, $ n_1 = 2 $ and $ s_1 = d_1 + d_2 = 2 + 2 = 4 \leq n_1^2 = 2^2 = 4 $ ;
- For color $ c = 2 $ , vertex $ 3 $ and vertex $ 4 $ are connected. Moreover, $ n_2 = 2 $ and $ s_2 = d_3 + d_4 = 2 + 2 = 4 \leq n_2^2 = 2^2 = 4 $ ;
- For color $ c = 3 $ , there is only one vertex (vertex $ 5 $ ) colored by $ 3 $ . Moreover, $ n_3 = 1 $ and $ s_3 = d_5 = 0 \leq n_3^2 = 1^2 = 1 $ .

## 样例 #1

### 输入

```
1
5
2 2 2 2 0

2

4

2

4
```

### 输出

```
? 1

? 1

? 3

? 3

! 1 1 2 2 3
```



---

---
title: "Halve or Subtract"
layout: "post"
diff: 省选/NOI-
pid: CF1799F
tag: ['贪心', '堆', '网络流']
---

# Halve or Subtract

## 题目描述

# Halve or Subtract


给定一个长度为 $n$ 的数列 $ a_1, a_2, \ldots, a_n $ ，一个正整数 $b$ 和两种操作：

1. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \lceil \frac{a_i}{2} \rceil $ 。
2. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \max(a_i - b, 0) $ 。

同时给定两个非负整数 $0 \le k_1, k_2 \le n$， 要求至多进行 $k_1$ 次操作1， $k_2$ 次操作2，同时对于每个元素，每种操作至多进行一次。 

求出进行若干次满足条件的操作后 $a_1 + a_2 + \ldots + a_n$ 的最小值。

## 输入格式

多组数据， 第一行为数据组数 $t$,( $ 1 \le t \le 5000 $ )。

每组数据的第一行有四个整数 $ n $ , $ b $ , $ k_1 $, $ k_2 $ ( $ 1 \le n \le 5000 $ , $ 1 \le b \le 10^9 $ , $ 0 \le k_1, k_2 \le n $ )。

每组数据的第二行有 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ )。

保证所有数据的 $n$ 之和不超过 $5000$。

## 输出格式

对于每组数据输出一行一个整数表示 $a_i$ 的和的最小值。

## 样例 #1

### 输入

```
7
3 2 1 1
9 3 5
2 1 2 0
1000000000 1
5 3 1 1
2 8 3 19 3
6 9 4 2
1 2 3 4 5 6
3 10 3 3
1 2 3
5 1 0 0
999999999 999999999 999999999 999999999 999999999
5 5 4 3
5 9 10 7 4
```

### 输出

```
11
500000001
23
6
0
4999999995
6
```



---

---
title: "T-shirt"
layout: "post"
diff: 省选/NOI-
pid: CF183D
tag: ['贪心', '背包 DP', '期望']
---

# T-shirt

## 题目描述

你将在CodeForces的一个$n$人团队实习，n个工程师由1到$n$编号。你决定给每个工程师一个纪念品：一件来自你的国家的T恤（T恤在CodeForces很受欢迎）。不幸的是，你不知道$n$个工程师各自衣服的尺寸。一共有1到m共m种不同的尺寸，并且每个工程师只适合一个尺寸。

你不知道每个工程师的尺寸，所以你询问你的朋友Gerald。很遗憾，他也不知道每个工程师的尺寸，但他知道对于第$i$个工程师，适合第j种T恤的概率。

最后你带来了$n$件T恤（这$n$件T恤可以是任意组合，你也可以带多件同样尺寸的衣服），在你准备T恤的时候并不知道每个工程师的尺寸，所以你只能根据Gerald提供的概率决定你所带的T恤。

你的任务是最大化收到适合自己的衣服的工程师数量的期望值。

当你到达办公室后，你会询问每个工程师他适合的T恤的尺寸，如果你有那个尺寸的衣服，你就会给他一件，否则就不给他T恤。你会从$1$号问起，一直问到$n$号

---

## 输入格式

第一行为两个用空格分开的整数n和m（$1<=n<=3000$,$1<=m<=300$)，分别代表工程师数量和衣服尺寸数量

接下来有$n$行，每行$m$个空格分开的整数，第$i$行第$j$个数字代表第$i$个工程师适合第$j$种T恤的概率。每个整数在$1$到$1000$之间。实际上的概率应为每个整数除以1000。

保证对于每个工程师适合每种T恤的概率之和为$1$。

## 输出格式

输出一行，一个实数代表收到T恤的工程师数量的最大期望值。允许最大误差为$10^{-9}$。

感谢@LJZ_C 提供的翻译

## 样例 #1

### 输入

```
2 2
500 500
500 500

```

### 输出

```
1.500000000000

```

## 样例 #2

### 输入

```
3 3
1000 0 0
1000 0 0
0 1000 0

```

### 输出

```
3.000000000000

```

## 样例 #3

### 输入

```
1 4
100 200 300 400

```

### 输出

```
0.400000000000

```



---

---
title: "Remove Bridges"
layout: "post"
diff: 省选/NOI-
pid: CF1976F
tag: ['贪心']
---

# Remove Bridges

## 题目描述

You are given a rooted tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Vertex $ 1 $ is the root. Additionally, the root only has one child.

You are asked to add exactly $ k $ edges to the tree (possibly, multiple edges and/or edges already existing in the tree).

Recall that a bridge is such an edge that, after you remove it, the number of connected components in the graph increases. So, initially, all edges of the tree are bridges.

After $ k $ edges are added, some original edges of the tree are still bridges and some are not anymore. You want to satisfy two conditions:

- for every bridge, all tree edges in the subtree of the lower vertex of that bridge should also be bridges;
- the number of bridges is as small as possible.

Solve the task for all values of $ k $ from $ 1 $ to $ n - 1 $ and output the smallest number of bridges.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ) — the number of vertices of the tree.

Each of the next $ n - 1 $ lines contain two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the description of the edges of the tree. It's guaranteed that the given edges form a valid tree.

Additional constraint on the input: the root (vertex $ 1 $ ) has exactly one child.

The sum of $ n $ over all testcases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each testcase, print $ n - 1 $ integers. For each $ k $ from $ 1 $ to $ n - 1 $ print the smallest number of bridges that can be left after you add $ k $ edges to the tree.

## 样例 #1

### 输入

```
4
2
1 2
12
4 10
5 12
12 11
3 6
9 6
1 6
12 7
11 6
2 11
10 9
10 8
8
1 2
2 3
2 4
3 5
3 6
4 7
4 8
5
1 2
2 3
3 4
4 5
```

### 输出

```
0 
7 3 1 0 0 0 0 0 0 0 0 
4 1 0 0 0 0 0 
0 0 0 0
```



---

---
title: "Tensor"
layout: "post"
diff: 省选/NOI-
pid: CF1977E
tag: ['贪心']
---

# Tensor

## 题目描述

This is an interactive problem.

You are given an integer $ n $ .

The jury has hidden from you a directed graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and some number of edges. You additionally know that:

- The graph only contains edges of the form $ i \leftarrow j $ , where $ 1 \le i < j \le n $ .
- For any three vertices $ 1 \le i < j < k \le n $ , at least one of the following holds $ ^\dagger $ : 
  - Vertex $ i $ is reachable from vertex $ j $ , or
  - Vertex $ i $ is reachable from vertex $ k $ , or
  - Vertex $ j $ is reachable from vertex $ k $ .

You want to color each vertex in either black or white such that for any two vertices $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) of the same color, vertex $ i $ is reachable from vertex $ j $ .

To do that, you can ask queries of the following type:

- ? i j — is vertex $ i $ reachable from vertex $ j $ ( $ 1 \le i < j \le n $ )?

Find any valid vertex coloring of the hidden graph in at most $ 2 \cdot n $ queries. It can be proven that such a coloring always exists.

Note that the grader is not adaptive: the graph is fixed before any queries are made.

 $ ^\dagger $ Vertex $ a $ is reachable from vertex $ b $ if there exists a [path](https://en.wikipedia.org/wiki/Path_(graph_theory)) from vertex $ b $ to vertex $ a $ in the graph.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 3 \le n \le 100 $ ) — the number of vertices in the hidden graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

The interaction for each test case begins by reading the integer $ n $ .

To make a query, output "? i j" without quotes ( $ 1 \le i < j \le n $ ). If vertex $ i $ is reachable from vertex $ j $ , you will get YES as an answer. Otherwise, you will get NO as an answer.

If you receive the integer $ -1 $ instead of an answer or a valid value of $ n $ , it means your program has made an invalid query, has exceeded the limit of queries, or has given an incorrect answer on the previous test case. Your program must terminate immediately to receive a Wrong Answer verdict. Otherwise, you can get an arbitrary verdict because your solution will continue to read from a closed stream.

When you are ready to give the final answer, output "! $ c_1 \ c_2 \ \ldots \ c_n $ " without quotes — the colors of the vertices, where $ c_i = 0 $ if the vertex is black, and $ c_i = 1 $ if the vertex is white. After solving all test cases, your program should be terminated immediately.

After printing a query, do not forget to output an end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks

To hack, use the following format:

The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3 \le n \le 100 $ , $ 0 \le m \le \frac{n\cdot(n - 1)}{2} $ ) — the number of vertices and edges in the graph.

Each of the following $ m $ lines should contain two integers $ a $ and $ b $ ( $ 1 \le b < a \le n $ ), indicating that there is the edge $ a \rightarrow b $ in the graph. The graph should satisfy the conditions above.

The sum of $ n $ over all test cases should not exceed $ 1000 $ .

## 说明/提示

The hidden graph in the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/d9f22ee8ab749a5ad0bef404d190145b53c9cc18.png)The hidden graph in the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/eba30883018cd14dec28ecbab62d3af607fa7b41.png)The interaction happens as follows:

SolutionJuryExplanation2There are $ 2 $ test cases.4In the first test case, the graph has $ 4 $ vertices.? 1 2 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 2 $ , and the jury answers YES.? 2 3 YESThe solution asks if vertex $ 2 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 3 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 4 NOThe solution asks if vertex $ 1 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 2 4 NOThe solution asks if vertex $ 2 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 3 4 NOThe solution asks if vertex $ 3 $ is reachable from vertex $ 4 $ , and the jury answers NO.! 0 0 0 1The solution has somehow determined a valid coloring and outputs it. Since the output is correct, the jury continues to the next test case.5In the second test case, the graph has $ 5 $ vertices.! 1 1 0 1 0The solution has somehow determined a valid coloring, and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
4

YES

YES

YES

NO

NO

NO

5
```

### 输出

```
? 1 2

? 2 3

? 1 3

? 1 4

? 2 4

? 3 4

! 0 0 0 1

! 1 1 0 1 0
```



---

---
title: "Grid Reset"
layout: "post"
diff: 省选/NOI-
pid: CF1991G
tag: ['贪心', '构造']
---

# Grid Reset

## 题目描述

给定一个 $n$ 行 $m$ 列的格子矩阵，初始所有格子都是白色。另外给定一个整数 $k$。

你将执行如下两类操作共 $q$ 次：

- $\texttt H$（水平操作）：在格子矩阵中选择一个 $1$ 行 $k$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。
- $\texttt V$（纵向操作）：在格子矩阵中选择一个 $k$ 行 $1$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。

每次操作之后，如果任意一行或一列所有格子都被涂成了黑色，则这一行或一列的所有格子自动被重置成白色。特别的，如果某一个格子所在的行和列都被涂成了黑色，则该格子所处的行和列的所有格子也将自动被重置成白色。

现在，对于 $q$ 次操作中的每次操作，请指定一个矩阵，使得所有 $q$ 次操作都能够进行，或者报告无论如何指定矩阵都不能使得所有 $q$ 次操作都能够进行。

## 输入格式

**本题包含多组数据。**

第一行输入一个整数 $t$，表示数据组数。

对于每组数据，第一行输入四个整数 $n,m,k,q$，分别代表格子矩阵的行数、列数、每次操作选定的矩阵的大小和操作次数。  
第二行输入一个长度为 $q$ 的字符串 $s$，表示操作序列。

## 输出格式

对于每组数据，如果无论如何指定矩阵都不能使得所有 $q$ 次操作都能够进行，输出一行 $-1$。否则，输出 $q$ 行，第 $x$ 行两个整数 $i,j$，表示第 $x$ 次操作所指定的矩阵的左上角的格子所在的行和列。

## 说明/提示

对于所有数据：

- $1\leqslant t\leqslant 1000$。
- $1\leqslant n,m\leqslant 100,\color{Red}1\leqslant k\leqslant \min\{n,m\}$。
- $1\leqslant q\leqslant 1000,\sum q\leqslant 1000$。

输入输出样例参见下文。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
1
4 5 3 6
HVVHHV
```

### 输出

```
1 1
2 1
1 1
2 3
3 3
2 2
```



---

---
title: "Iris and Adjacent Products"
layout: "post"
diff: 省选/NOI-
pid: CF2006D
tag: ['贪心', '分块']
---

# Iris and Adjacent Products

## 题目描述

Iris has just learned multiplication in her Maths lessons. However, since her brain is unable to withstand too complex calculations, she could not multiply two integers with the product greater than $ k $ together. Otherwise, her brain may explode!

Her teacher sets a difficult task every day as her daily summer holiday homework. Now she is given an array $ a $ consisting of $ n $ elements, and she needs to calculate the product of each two adjacent elements (that is, $ a_1 \cdot a_2 $ , $ a_2 \cdot a_3 $ , and so on). Iris wants her brain to work safely, and in order to do that, she would like to modify the array $ a $ in such a way that $ a_i \cdot a_{i + 1} \leq k $ holds for every $ 1 \leq i < n $ . There are two types of operations she can perform:

1. She can rearrange the elements of the array $ a $ in an arbitrary way.
2. She can select an arbitrary element of the array $ a $ and change its value to an arbitrary integer from $ 1 $ to $ k $ .

Iris wants to minimize the number of operations of type $ 2 $  that she uses.

However, that's completely not the end of the summer holiday! Summer holiday lasts for $ q $ days, and on the $ i $ -th day, Iris is asked to solve the Math homework for the subarray $ b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i} $ . Help Iris and tell her the minimum number of type $ 2 $ operations she needs to perform for each day. Note that the operations are independent for each day, i.e. the array $ b $ is not changed.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5\cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ q $ and $ k $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \leq q \leq 10^5 $ , $ 1 \leq k \leq 10^6 $ ) — the length of array $ b $ , the number of days, and the upper bound for the multiplication calculation.

The second line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq k $ ) — the elements of the array $ b $ .

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq n $ ) — the boundaries of the subarray on the $ i $ -th day.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test, output a single line containing $ q $ integers — the minimum number of operations of type $ 2 $ needed for each day.

## 说明/提示

In the first test case, as Iris can always multiply $ 1 $ and $ 1 $ together, no operations are needed, so the answer is $ 0 $ .

In the second test case, the first day's homework is $ [1, 10, 9] $ . Iris can rearrange its elements to get $ [9, 1, 10] $ , so no operations of type $ 2 $ are needed. The second day's homework is $ [10, 9] $ , and she can change one element to get the array $ [1, 9] $ , so one operation of type $ 2 $ is needed.

## 样例 #1

### 输入

```
5
3 1 1
1 1 1
1 3
3 2 10
1 10 9
1 3
2 3
5 4 2
2 2 2 2 2
1 2
2 4
2 5
1 5
6 5 10
3 2 5 10 10 1
1 4
3 6
1 6
2 5
5 6
10 10 10
10 9 8 7 6 5 4 3 2 1
1 10
1 9
1 8
1 7
2 10
3 10
4 10
5 10
3 9
6 8
```

### 输出

```
0 
0 1 
1 1 2 2 
1 1 1 1 0 
3 3 4 3 2 2 1 1 2 1
```



---

---
title: "Game in Tree (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2013F1
tag: ['贪心', 'ST 表']
---

# Game in Tree (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ \mathbf{u = v} $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob are playing a fun game on a tree. This game is played on a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Recall that a tree with $ n $ vertices is an undirected connected graph with $ n - 1 $ edges.

Alice and Bob take turns, with Alice going first. Each player starts at some vertex.

On their turn, a player must move from the current vertex to a neighboring vertex that has not yet been visited by anyone. The first player who cannot make a move loses.

You are given two vertices $ u $ and $ v $ . Represent the simple path from vertex $ u $ to $ v $ as an array $ p_1, p_2, p_3, \ldots, p_m $ , where $ p_1 = u $ , $ p_m = v $ , and there is an edge between $ p_i $ and $ p_{i + 1} $ for all $ i $ ( $ 1 \le i < m $ ).

You need to determine the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_j $ for each $ j $ (where $ 1 \le j \le m $ ).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

Each of the following $ n - 1 $ lines contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ ), denoting an undirected edge between vertices $ a $ and $ b $ . It is guaranteed that these edges form a tree.

The last line of each test case contains two integers $ u $ and $ v $ ( $ 2 \le u, v \le n $ , $ \mathbf{u = v} $ ).

It is guaranteed that the path from $ u $ to $ v $ does not pass through vertex $ 1 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ m $ lines.

In the $ i $ -th line, print the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_i $ . Print "Alice" (without quotes) if Alice wins, or "Bob" (without quotes) otherwise.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2013F1/e1cf544a0db6c078ce895e1ac7918ee5810cf6b5.png) Tree from the first and second examples.In the first test case, the path will be ( $ 2,2 $ ). Bob starts at vertex $ 2 $ , Alice will not be able to move anywhere on her first turn and will lose.

In the second test case, the path will be ( $ 3,3 $ ). Bob starts at vertex $ 3 $ , Alice will move to vertex $ 2 $ , and Bob will have no remaining vertices to visit and will lose.

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 2
3
1 2
2 3
3 3
6
1 2
1 3
2 4
2 5
1 6
4 4
```

### 输出

```
Bob
Alice
Alice
```



---

---
title: "Variable Damage"
layout: "post"
diff: 省选/NOI-
pid: CF2025G
tag: ['贪心', '分块']
---

# Variable Damage

## 题目描述

Monocarp is gathering an army to fight a dragon in a videogame.

The army consists of two parts: the heroes and the defensive artifacts. Each hero has one parameter — his health. Each defensive artifact also has one parameter — its durability.

Before the battle begins, Monocarp distributes artifacts to the heroes so that each hero receives at most one artifact.

The battle consists of rounds that proceed as follows:

- first, the dragon deals damage equal to $ \frac{1}{a + b} $ (a real number without rounding) to each hero, where $ a $ is the number of heroes alive and $ b $ is the number of active artifacts;
- after that, all heroes with health $ 0 $ or less die;
- finally, some artifacts are deactivated. An artifact with durability $ x $ is deactivated when one of the following occurs: the hero holding the artifact either dies or receives $ x $ total damage (from the start of the battle). If an artifact is not held by any hero, it is inactive from the beginning of the battle.

The battle ends when there are no heroes left alive.

Initially, the army is empty. There are $ q $ queries: add a hero with health $ x $ or an artifact with durability $ y $ to the army. After each query, determine the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of queries.

In the $ i $ -th of the following $ q $ lines, there are two integers $ t_i $ and $ v_i $ ( $ t_i \in \{1, 2\} $ ; $ 1 \le v_i \le 10^9 $ ) — the type of the query and the value of the query parameter. If the type is $ 1 $ , a hero with health $ v_i $ is added. If the type is $ 2 $ , an artifact with durability $ v_i $ is added.

## 输出格式

Print $ q $ integers. After each query, output the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 说明/提示

Let's consider the first example.

- An artifact with durability $ 5 $ is added. Since there are no heroes yet, the battle ends immediately.
- A hero with health $ 4 $ is added. Monocarp can give him an artifact with durability $ 5 $ . First, there are rounds in which the hero takes $ \frac{1}{1 + 1} = \frac{1}{2} $ damage. After $ 8 $ such rounds, a total of $ 4 $ damage will have been dealt, and the hero will die, while the artifact will deactivate. There are no more heroes alive, so the battle ends after $ 8 $ rounds.
- A hero with health $ 10 $ is added. Now let the artifact with durability $ 5 $ be with this hero. Then, in the first $ 12 $ rounds, the heroes will take $ 12 \cdot \frac{1}{2 + 1} = 4 $ damage, and the first hero will die. The second hero has $ 6 $ health left, and the artifact has $ 1 $ durability. Now the damage is $ \frac{1}{2} $ , so after another $ 2 $ rounds, the artifact will deactivate. The second hero has $ 5 $ health left. After another $ 5 $ rounds, the second hero will die. Therefore, the answer is $ 12 + 2 + 5 = 19 $ .

## 样例 #1

### 输入

```
3
2 5
1 4
1 10
```

### 输出

```
0
8
19
```

## 样例 #2

### 输入

```
10
1 9
1 6
2 4
1 8
1 3
2 10
1 3
1 6
1 10
2 6
```

### 输出

```
9
15
19
27
30
39
42
48
59
65
```



---

---
title: "Barrels"
layout: "post"
diff: 省选/NOI-
pid: CF2038E
tag: ['数学', '贪心']
---

# Barrels

## 题目描述

假设你拥有 $n$ 个水桶，它们依次排放，编号为 $1$ 到 $n$。

每个水桶是相同的，底面积为一个单位，因此水桶内的水量对应水柱的高度。起初，第 $i$ 个水桶中含有 $v_i$ 单位的水。

相邻的水桶之间通过管道相连。具体来说，对于每个从 $1$ 到 $n-1$ 的 $i$，水桶 $i$ 与水桶 $i+1$ 通过一个高度为 $h_i$ 的水平管道相连。管道的宽度可以忽略不计。这些管道可以让水在水桶之间流动。

现在，你想对这些水桶进行操作。你的目标是通过向水桶中投放粘土来最大化第一个水桶中的水量。每一步，你可以选择任意一个水桶，向其中添加一单位的粘土。粘土的单位体积与水相同，但粘土比水重且不会与水混合，因此它会下沉并均匀分布在桶底。

由于粘土具有黏性，当粘土的高度足够时，它会封住管道。更确切地说，如果管道的高度为 $h$，当粘土的高度达到或低于 $h$ 时，管道仍然能正常工作。然而，一旦你向水桶中多加了一单位的粘土，管道就会立刻被封住，阻止水在水桶之间流动。

你拥有大量的粘土，因此可以多次执行上述操作。但在每次操作之后，你需要等待水达到新的平衡状态。

你能让第一个水桶中的水量达到的最大值是多少？

假定水桶足够高，因此不会溢出，并且可以忽略管道的宽度。

## 输入格式

第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示水桶的数量。

第二行包含 $n$ 个整数 $v_1, v_2, \dots, v_n$（$0 \le v_i \le 10^6$），表示每个水桶的初始水量。

第三行包含 $n - 1$ 个整数 $h_1, h_2, \dots, h_{n - 1}$（$1 \le h_i \le 10^6$），表示水桶之间的管道高度。

请注意，输入数据保证水最初处于平衡状态。

## 输出格式

输出一个数字，表示第一个水桶中可能达到的最大水量。你的答案将被认为是正确的，如果其绝对误差或相对误差不超过 $10^{-6}$。

格式上，设你的答案为 $a$，标准答案为 $b$。当且仅当 $\frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6}$ 时，答案被接受。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
1 2
2
```

### 输出

```
2.500000000000000
```

## 样例 #2

### 输入

```
3
3 0 0
6 9
```

### 输出

```
3.000000000000000
```

## 样例 #3

### 输入

```
5
10 0 0 0 5
11 1 2 5
```

### 输出

```
11.916666666666667
```



---

---
title: "Vertex Pairs"
layout: "post"
diff: 省选/NOI-
pid: CF2042E
tag: ['贪心', '最近公共祖先 LCA']
---

# Vertex Pairs

## 题目描述

给定一个由$ 2n $个顶点组成的树。回想一下，树是一个没有环的连通无向图。每个顶点上都写了一个从$ 1 $到$ n $的整数。从$ 1 $到$ n $的每个值都恰好写在两个不同的顶点上。每个顶点也有成本-顶点$ i $成本$ 2^i $。

你需要选择树的一个顶点子集，如下所示：

- 子集是连通的；也就是说，从子集中的每个顶点，只通过子集中的顶点可达子集中的每个其他顶点；
- 从$ 1 $到$ n $的每个值都至少写在子集中的一个顶点上。

在所有这样的子集中，您需要找到其中顶点的总代价最小的子集。注意，您不需要最小化子集中的顶点数量。

## 输入格式

第一行包含一个整数$ n $ （$ 1 \le n \le 2 \cdot 10^5 $）。

第二行包含$ 2n $整数$ a_1, a_2, \dots, a_{2n} $ （$ 1 \le a_i \le n $）。从$ 1 $到$ n $的每个值恰好出现两次。

接下来的$ 2n-1 $行中每行包含两个整数$ v $和$ u $ （$ 1 \le v, u \le 2n $）——树的边。这些边构成了一棵有效的树。

## 输出格式

在第一行中，打印一个整数$ k $——子集中的顶点数。

在第二行中，打印从$ 1 $到$ 2n $的$ k $个不同整数——所选子集中顶点的索引。顶点可以以任意顺序打印。

## 样例 #1

### 输入

```
3
1 1 3 2 3 2
4 2
1 6
6 2
6 3
2 5
```

### 输出

```
3
2 4 5
```

## 样例 #2

### 输入

```
3
2 3 1 3 2 1
6 4
2 4
5 2
3 6
3 1
```

### 输出

```
4
1 3 4 6
```

## 样例 #3

### 输入

```
6
5 2 3 4 6 4 2 5 6 1 1 3
10 8
2 10
12 7
4 10
5 9
6 2
1 9
3 4
12 6
11 5
4 5
```

### 输出

```
6
2 3 4 5 8 10
```



---

---
title: "Cheops and a Contest (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2046E1
tag: ['贪心', '构造']
---

# Cheops and a Contest (Easy Version)

## 题目描述

这是问题的简单版本。在这个版本中，$m$ 固定为 $2$。只有解决了问题的所有版本后，你才能进行 hack。

在古埃及有一场问题解决比赛，参赛者有 $n$ 名，编号从 $1$ 到 $n$。每位参赛者来自一个特定的城市，城市的编号从 $1$ 到 $m$。保证每个城市至少有一名参赛者。

每位参赛者拥有力量 $a_i$，专长 $s_i$，以及智慧 $b_i$，并且 $b_i \ge a_i$。比赛中的每个问题都有一个难度 $d$ 和一个独特的主题 $t$。如果满足以下条件之一，第 $i$ 位参赛者可以解决这个问题：

- $a_i \ge d$，即参赛者的力量大于或等于问题的难度；
- $s_i = t$ 并且 $b_i \ge d$，即参赛者的专长等于问题的主题，同时智慧不低于问题的难度。

Cheops 的愿望是设计一组问题，使得来自城市 $i$ 的每位参赛者比来自城市 $j$ 的每位参赛者解决更多的问题，且 $i < j$。

请找到一个不超过 $5n$ 个问题的集合，其中所有问题的主题各不相同，能够满足 Cheops 的愿望，或者说明这个愿望无法实现。

## 输入格式

输入包含多个测试用例。第一行为测试用例的数量 $T$，满足 $1 \le T \le 10^4$。接下来的部分描述每个测试用例。

对于每个测试用例，第一行包含两个整数 $n$ 和 $m$，其中 $2 = m \le n \le 3 \cdot 10^5$，分别表示参赛者数量和城市数量。

接下来的 $n$ 行描述了每位参赛者。第 $i$ 行包含三个整数 $a_i$，$b_i$ 和 $s_i$，其中 $0 \le a_i, b_i, s_i \le 10^9$ 且 $a_i \le b_i$，依次表示第 $i$ 位参赛者的力量、智慧和专长。

接下来的 $m$ 行描述每个城市的参赛者情况。第 $i$ 行首先是一个整数 $k_i$，表示来自于第 $i$ 个城市的参赛者数量，满足 $1 \le k_i \le n$。接着是该城市参赛者的编号序列 $q_{i, 1}, q_{i, 2}, \ldots, q_{i, k_i}$，其中 $1 \le q_{i, j} \le n$ 且 $1 \le j \le k_i$。保证每位参赛者的编号恰好被提及一次。

保证所有测试用例中 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在一组问题满足 Cheops 的条件，则输出一个整数 $p$，表示问题数量，满足 $1 \le p \le 5n$。

接下来输出 $p$ 行，每行包含两个整数 $d$ 和 $t$，分别表示问题的难度和主题。不同问题的主题必须各不相同。

如果无法找到符合条件的问题集合，请输出 $-1$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 2
5 7 1
6 7 2
3 9 2
5 10 3
4 4 1
2 1 2
3 3 4 5
2 2
1 2 1
1 2 1
1 2
1 1
```

### 输出

```
7
6 4
6 5
5 6
5 7
4 8
4 9
7 1
-1
```



---

---
title: "Maximum Polygon"
layout: "post"
diff: 省选/NOI-
pid: CF2077D
tag: ['贪心']
---

# Maximum Polygon

## 题目描述

给定一个长度为 $n$ 的数组 $a$，确定字典序最大的 $^{\text{∗}}$ 子序列 $^{\text{†}}$ $s$，使得 $s$ 可以作为多边形的边长。

当且仅当 $|s| \geq 3$ 且满足以下条件时，$s$ 可以作为多边形的边长：

$$ 2 \cdot \max(s_1, s_2, \ldots, s_{|s|}) < s_1 + s_2 + \ldots + s_{|s|}. $$

如果不存在这样的子序列 $s$，输出 $-1$。

$^{\text{∗}}$ 序列 $x$ 的字典序小于序列 $y$，当且仅当以下条件之一成立：
- $x$ 是 $y$ 的前缀，但 $x \neq y$；
- 在 $x$ 和 $y$ 第一个不同的位置，$x$ 的元素小于 $y$ 中对应的元素。

$^{\text{†}}$ 序列 $x$ 是序列 $y$ 的子序列，当且仅当 $x$ 可以通过从 $y$ 中删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行输入一个整数 $n$（$3 \leq n \leq 2 \cdot 10^5$）——数组 $a$ 的长度。

第二行输入 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$）——数组 $a$。

保证所有测试用例的 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，按以下格式输出答案：

如果存在答案，按以下格式输出：

第一行输出整数 $k$（$1 \leq k \leq n$）——子序列 $s$ 的长度。

第二行输出 $k$ 个整数 $s_1, s_2, \ldots, s_k$（$1 \leq s_i \leq 10^9$，$s$ 是 $a$ 的子序列）——子序列 $s$。注意输出的是元素值，而非下标。

否则，输出一行整数 $-1$。

## 说明/提示

在第一个测试用例中，不存在可以作为多边形边长的子序列。

在第二个测试用例中，有两个可以作为多边形边长的子序列：$1, 4, 2, 3$ 和 $4, 2, 3$。后者是字典序更大的子序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
3 1 2
4
1 4 2 3
6
1 6 4 5 3 2
6
43 12 99 53 22 4
7
9 764 54 73 22 23 1
```

### 输出

```
-1
3
4 2 3 
4
6 5 3 2 
5
43 99 53 22 4 
4
54 73 23 1
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
title: "Quaternary Matrix"
layout: "post"
diff: 省选/NOI-
pid: CF2081C
tag: ['贪心', '构造']
---

# Quaternary Matrix

## 题目描述

若矩阵中所有元素均为 $0$、$1$、$2$ 或 $3$，则称该矩阵为四元矩阵。

当四元矩阵 $A$ 满足以下两个性质时，Ecrade 称其为好矩阵：
1. 矩阵 $A$ 的每一行中所有数字的按位异或（bitwise XOR）结果等于 $0$。
2. 矩阵 $A$ 的每一列中所有数字的按位异或（bitwise XOR）结果等于 $0$。

Ecrade 有一个 $n \times m$ 的四元矩阵。他想知道将该矩阵变为好矩阵所需修改的最少元素数量，并希望得到其中一个可能的修改后矩阵。

由于问题有一定难度，请你帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 2 \cdot 10^5$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^3$）。

接下来输入 $n$ 行，每行包含恰好 $m$ 个字符，且每个字符均为 $0$、$1$、$2$ 或 $3$，描述 Ecrade 的矩阵。

保证所有测试用例的 $n \cdot m$ 总和不超过 $10^6$。

## 输出格式

对于每个测试用例：
1. 第一行输出使矩阵变为好矩阵所需修改的最少元素数量。
2. 随后输出 $n$ 行，每行包含恰好 $m$ 个字符（均为 $0$、$1$、$2$ 或 $3$），描述其中一个可能的修改后矩阵。

若存在多个可行的修改后矩阵，可输出任意一个。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 3
313
121
313
3 3
000
000
000
4 4
0123
1230
2301
3012
4 4
1232
2110
3122
1311
4 4
1232
2110
3122
1312
```

### 输出

```
3
213
101
312
0
000
000
000
0
0123
1230
2301
3012
6
0132
2310
3131
1313
5
0132
2310
3120
1302
```



---

---
title: "Skyscape"
layout: "post"
diff: 省选/NOI-
pid: CF2084F
tag: ['贪心', '线段树', '树状数组']
---

# Skyscape

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$。

我们称一个长度为 $n$ 的排列 $b$ 是好的，如果在最多进行 $n$ 次（可以是零次）以下操作后，排列 $a$ 和 $b$ 可以变得相同：

- 选择两个整数 $l, r$，满足 $1 \le l < r \le n$ 且 $a_r = \min(a_l, a_{l + 1}, \ldots, a_r)$。
- 将子段 $[a_l, a_{l + 1}, \ldots, a_r]$ 循环右移一位。换句话说，将 $a$ 替换为：
  $$
  [a_1, \ldots, a_{l - 1}, \; a_r, a_l, a_{l + 1}, \ldots, a_{r - 1}, \; a_{r + 1}, \ldots, a_n]
  $$

同时给定一个长度为 $n$ 的排列 $c$，其中部分元素缺失（用 $0$ 表示）。

你需要找到一个好的排列 $b_1, b_2, \ldots, b_n$，使得 $b$ 可以通过填充 $c$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $c_i \ne 0$，则 $b_i = c_i$）。如果不存在这样的排列，输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 5 \cdot 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）。保证 $a$ 是一个长度为 $n$ 的排列。  
第三行包含 $n$ 个整数 $c_1, c_2, \ldots, c_n$（$0 \le c_i \le n$）。保证 $c$ 中非 $0$ 的元素互不相同。  

保证所有测试用例的 $n$ 之和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例：

- 如果无法找到满足条件的好排列 $b$，输出一个整数 $-1$。
- 否则，输出 $n$ 个整数 $b_1, b_2, \ldots, b_n$——你找到的好排列 $b$。需要确保对于所有 $1 \le i \le n$，如果 $c_i \ne 0$，则 $b_i = c_i$。如果有多个解，输出任意一个即可。


## 说明/提示

- 在第一个测试用例中，$b = [1, 2]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[1, 2]$。

- 在第二个测试用例中，$b = [2, 3, 4, 1]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[2, 3, 4, 1]$。

- 在第三个测试用例中，$b = [1, 3, 2, 4, 5]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 3$ 并循环右移子段 $[a_1, a_2, a_3]$。此时 $a$ 变为 $[1, 3, 2, 5, 4]$。
  - 选择 $l = 4, r = 5$ 并循环右移子段 $[a_4, a_5]$。此时 $a$ 变为 $[1, 3, 2, 4, 5]$。

- 在第四个测试用例中，$b = [3, 2, 1, 5, 4]$ 是一个有效解，因为 $a$ 和 $b$ 已经相同。

- 在第五个测试用例中，不存在满足条件的好排列 $b$，因此输出 $-1$。

- 在第六个测试用例中，$b = [3, 2, 1, 5, 4, 6]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 2, r = 4$ 并循环右移子段 $[a_2, a_3, a_4]$。此时 $a$ 变为 $[3, 2, 5, 6, 1, 4]$。
  - 选择 $l = 3, r = 5$ 并循环右移子段 $[a_3, a_4, a_5]$。此时 $a$ 变为 $[3, 2, 1, 5, 6, 4]$。
  - 选择 $l = 5, r = 6$ 并循环右移子段 $[a_5, a_6]$。此时 $a$ 变为 $[3, 2, 1, 5, 4, 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
9
2
2 1
1 2
4
3 2 4 1
2 0 0 1
5
3 2 1 5 4
1 3 0 0 0
5
3 2 1 5 4
3 2 1 5 4
5
3 2 1 5 4
3 2 5 1 4
6
3 5 6 2 1 4
0 2 0 5 0 0
6
3 5 6 2 1 4
0 2 0 6 4 0
9
6 9 2 4 1 7 8 3 5
0 2 5 9 0 0 0 8 0
9
8 5 3 9 1 7 4 6 2
0 0 8 0 7 0 4 0 2
```

### 输出

```
1 2
2 3 4 1
1 3 2 4 5
3 2 1 5 4
-1
3 2 1 5 4 6
-1
-1
1 3 8 5 7 9 4 6 2
```



---

---
title: "Serval and Colorful Array (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2085F2
tag: ['贪心', '枚举', '差分']
---

# Serval and Colorful Array (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中 $n \leq 4 \cdot 10^5$。仅当您解决了该问题的所有版本时才能进行 hack。

Serval 有一个魔法数 $k$（$k \geq 2$）。我们称数组 $r$ 为 colorful 当且仅当：
- $r$ 的长度为 $k$，且
- $1$ 到 $k$ 之间的每个整数在 $r$ 中恰好出现一次。

给定一个由 $n$ 个介于 $1$ 到 $k$ 的整数组成的数组 $a$。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。您可以对 $a$ 执行以下操作：
- 选择一个下标 $i$（$1 \leq i < n$），然后交换 $a_i$ 和 $a_{i+1}$。

求使得 $a$ 中至少存在一个 colorful 子数组$^{\text{∗}}$所需的最小操作次数。可以证明在题目约束下这总是可行的。

$^{\text{∗}}$数组 $b$ 是数组 $a$ 的子数组，当且仅当 $b$ 可以通过从 $a$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$2 \leq k \leq n \leq 4 \cdot 10^5$）——数组 $a$ 的长度和 Serval 的魔法数。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq k$）——数组 $a$ 的元素。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。

保证所有测试用例的 $n$ 之和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 使得 $a$ 中至少存在一个 colorful 子数组所需的最小操作次数。

## 说明/提示

第一个测试案例中，由于子数组 $[a_1, a_2] = [1, 2]$ 和 $[a_2, a_3] = [2, 1]$ 已经是 colorful 的，因此无需执行任何操作。答案为 $0$。

第二个测试案例中，我们可以交换 $a_1$ 和 $a_2$ 得到 $[1, \underline{2, 1, 3}, 1, 1, 2]$，其中包含一个 colorful 子数组 $[a_2, a_3, a_4] = [2, 1, 3]$。由于原数组初始时没有 colorful 子数组，因此答案为 $1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2
1 2 1
7 3
2 1 1 3 1 1 2
6 3
1 1 2 2 2 3
6 3
1 2 2 2 2 3
10 5
5 1 3 1 1 2 2 4 1 3
9 4
1 2 3 3 3 3 3 2 4
```

### 输出

```
0
1
2
3
4
5
```



---

---
title: "Andryusha and CCB"
layout: "post"
diff: 省选/NOI-
pid: CF2092F
tag: ['贪心']
---

# Andryusha and CCB

## 题目描述

我们定义一个二进制字符串 $z$ 的**美感值**为满足 $1 \le i < |z|$ 且 $z_i \neq z_{i+1}$ 的索引 $i$ 的数量。

在等待 CCB 的朋友们到来时，Andryusha 烤了一个馅饼，表示为一个长度为 $n$ 的二进制字符串 $s$。为了避免冒犯任何人，他想要将这个字符串分割成 $k$ 个子字符串，使得每个字符属于恰好一个子字符串，且所有子字符串的美感值相同。

Andryusha 不知道会有多少 CCB 的朋友来他家，因此他希望找出满足条件的所有 $k$ 值的数量。然而，他的兄弟 Tristan 认为这个问题的表述过于简单。因此，他要求你为字符串的每个前缀找出这样的 $k$ 值的数量。换句话说，对于每个 $i$（从 $1$ 到 $n$），你需要找出满足可以将前缀 $s_1 s_2 \ldots s_i$ 分割成恰好 $k$ 个具有相同美感值的子字符串的 $k$ 值的数量。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \le t \le 10^5$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \leq n \leq 10^6$) —— 二进制字符串的长度。  
第二行包含一个长度为 $n$ 的二进制字符串，仅由字符 0 和 1 组成。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出一行包含 $n$ 个整数 $c_i$ ($0 \le c_i \le n$) —— 表示对于前缀 $s_1 s_2 \ldots s_i$ 满足条件的 $k$ 值的数量。

## 说明/提示

第三个测试案例中，满足条件的 $k$ 值为：

1. $i = 1$: $k \in \{1\}$，
2. $i = 2$: $k \in \{1, 2\}$，
3. $i = 3$: $k \in \{1, 2, 3\}$，
4. $i = 4$: $k \in \{1, 3, 4\}$，
5. $i = 5$: $k \in \{1, 2, 4, 5\}$，
6. $i = 6$: $k \in \{1, 5, 6\}$，
7. $i = 7$: $k \in \{1, 5, 6, 7\}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5
00011
10
0101010101
7
0010100
```

### 输出

```
1 2 3 4 5
1 2 2 3 2 4 2 4 3 4
1 2 3 3 4 3 4
```



---

---
title: "Cycling (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2107F2
tag: ['动态规划 DP', '贪心', '斜率优化']
---

# Cycling (Hard Version)

## 题目描述

> 这是此问题的困难版本，和其他版本的区别是此版本中 $1\le n\le 10^6$，且需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

额外地，Leo 想知道对于每个 $i(1\le i\le n)$，当只有骑手 $1,2,\cdots,i$ 存在时，他超过所有 $i$ 名骑手的最小代价。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$，表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 10^6)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证单个测试点中 $\sum n\le 10^6$。

## 输出格式

对于每组数据，输出一行 $n$ 个整数，第 $i$ 个数表示只存在前 $i$ 个骑手时的答案。

## 说明/提示

**样例解释**

第一组数据中，当存在所有 $n$ 名骑手时，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中，当存在所有 $n$ 名骑手时，如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2
```

### 输出

```
1 3 7
1 2 3 4
1 3
4 3 6 8
```



---

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
title: "Privatization"
layout: "post"
diff: 省选/NOI-
pid: CF212A
tag: ['贪心', '网络流']
---

# Privatization

## 题目描述

There is a developed network of flights between Berland and Beerland. All of them belong to the Berland state company BerAvia. Each flight connects some Berland city with some Beerland city. For each flight airplanes fly in both directions.

Changes are coming to Berland — the state decided to privatize BerAvia, namely, to sell out all flights to $ t $ private companies. Each of these companies wants to get the maximal number of flights, so if the Berland flights are sold unevenly, Berland can be accused of partiality. Berland Government decided to sell the flights as evenly as possible between the $ t $ companies.

The unevenness of the distribution of flights between companies is calculated as follows. For each city $ i $ (both Berland and Beerland) we'll calculate the value of

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212A/8cb4dc3a97b60ddf7de9158fd0e56414b7e627be.png) where $ a_{ij} $ is the number of flights from city $ i $ , which belong to company $ j $ . The sum of $ w_{i} $ for all cities in both countries is called the unevenness of the distribution. The distribution with the minimal unevenness is the most even one.Help the Berland government come up with the most even distribution plan of selling flights.

## 输入格式

The first input line contains four integers $ n,m,k $ and $ t $ ( $ 1<=n,m,t<=200;1<=k<=5000 $ ), where $ n,m $ are the numbers of cities in Berland and Beerland, correspondingly, $ k $ is the number of flights between them, and $ t $ is the number of private companies. Next $ k $ lines describe the flights, one per line, as pairs of positive integers $ x_{i},y_{i} $ ( $ 1<=x_{i}<=n;1<=y_{i}<=m $ ), where $ x_{i} $ and $ y_{i} $ are the indexes of cities in Berland and Beerland, correspondingly, connected by the $ i $ -th flight. There is at most one flight between any pair of cities, each flight connects cities of different countries. The cities in Berland are indexed from 1 to $ n $ , and in Beerland — from 1 to $ m $ .

## 输出格式

Print the unevenness of the sought plan on the first line. On the second line print a sequence of $ k $ integers $ c_{1},c_{2},...,c_{k} $ ( $ 1<=c_{i}<=t $ ), where $ c_{i} $ is the index of the company that should buy the $ i $ -th flight. Assume that the flights are indexed from 1 to $ k $ in the order they appear in the input. If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
3 5 8 2
1 4
1 3
3 3
1 2
1 1
2 1
1 5
2 2

```

### 输出

```
4
2 1 2 1 2 1 2 2 
```



---

---
title: "Sheep"
layout: "post"
diff: 省选/NOI-
pid: CF309E
tag: ['贪心', '二分']
---

# Sheep

## 题目描述

Information technologies are developing and are increasingly penetrating into all spheres of human activity. Incredible as it is, the most modern technology are used in farming!

A large farm has a meadow with grazing sheep. Overall there are $ n $ sheep and each of them contains a unique number from 1 to $ n $ — because the sheep need to be distinguished and you need to remember information about each one, and they are so much alike! The meadow consists of infinite number of regions numbered from 1 to infinity. It's known that sheep $ i $ likes regions from $ l_{i} $ to $ r_{i} $ .

There are two shepherds taking care of the sheep: First and Second. First wakes up early in the morning and leads the sheep graze on the lawn. Second comes in the evening and collects all the sheep.

One morning, First woke up a little later than usual, and had no time to lead the sheep graze on the lawn. So he tied together every two sheep if there is a region they both like. First thought that it would be better — Second would have less work in the evening, because sheep won't scatter too much, being tied to each other!

In the evening Second came on the lawn, gathered the sheep and tried to line them up in a row. But try as he might, the sheep wouldn't line up as Second want! Second had neither the strength nor the ability to untie the sheep so he left them as they are, but with one condition: he wanted to line up the sheep so that the maximum distance between two tied sheep was as small as possible. The distance between the sheep is the number of sheep in the ranks that are between these two.

Help Second find the right arrangement.

## 输入格式

The first input line contains one integer $ n $ ( $ 1<=n<=2000 $ ). Each of the following $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i},r_{i}<=10^{9}; l_{i}<=r_{i}) $ .

## 输出格式

In the single output line print $ n $ space-separated numbers — the sought arrangement of the sheep. The $ i $ -th value in the line must represent the number of the sheep that took the $ i $ -th place from left in the optimal arrangement line.

If there are multiple optimal arrangements, print any of them.

## 样例 #1

### 输入

```
3
1 3
5 7
2 4

```

### 输出

```
1 3 2
```

## 样例 #2

### 输入

```
5
1 5
2 4
3 6
1 7
2 6

```

### 输出

```
2 1 3 5 4
```

## 样例 #3

### 输入

```
4
1 3
4 6
5 7
2 3

```

### 输出

```
1 4 2 3
```



---

---
title: "Free Market"
layout: "post"
diff: 省选/NOI-
pid: CF364B
tag: ['贪心']
---

# Free Market

## 题目描述

John Doe has recently found a "Free Market" in his city — that is the place where you can exchange some of your possessions for other things for free.

John knows that his city has $ n $ items in total (each item is unique). You can bring any number of items to the market and exchange them for any other one. Note that each item is one of a kind and that means that you cannot exchange set $ {a,b} $ for set $ {v,a} $ . However, you can always exchange set $ x $ for any set $ y $ , unless there is item $ p $ , such that $ p $ occurs in $ x $ and $ p $ occurs in $ y $ .

For each item, John knows its value $ c_{i} $ . John's sense of justice doesn't let him exchange a set of items $ x $ for a set of items $ y $ , if $ s(x)+d&lt;s(y) $ ( $ s(x) $ is the total price of items in the set $ x $ ).

During one day John can exchange only one set of items for something else. Initially, he has no items. John wants to get a set of items with the maximum total price. Find the cost of such set and the minimum number of days John can get it in.

## 输入格式

The first line contains two space-separated integers $ n $ , $ d $ ( $ 1<=n<=50 $ , $ 1<=d<=10^{4} $ ) — the number of items on the market and John's sense of justice value, correspondingly. The second line contains $ n $ space-separated integers $ c_{i} $ ( $ 1<=c_{i}<=10^{4} $ ).

## 输出格式

Print two space-separated integers: the maximum possible price in the set of items John can get and the minimum number of days needed to get such set.

## 说明/提示

In the first sample John can act like this:

- Take the first item ( $ 1-0<=2 $ ).
- Exchange the first item for the second one ( $ 3-1<=2 $ ).
- Take the first item ( $ 1-0<=2 $ ).

## 样例 #1

### 输入

```
3 2
1 3 10

```

### 输出

```
4 3

```

## 样例 #2

### 输入

```
3 5
1 2 3

```

### 输出

```
6 2

```

## 样例 #3

### 输入

```
10 10000
10000 9999 1 10000 10000 10000 1 2 3 4

```

### 输出

```
50010 6

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
title: "Shop"
layout: "post"
diff: 省选/NOI-
pid: CF521D
tag: ['贪心']
---

# Shop

## 题目描述

Vasya plays one very well-known and extremely popular MMORPG game. His game character has $ k $ skill; currently the $ i $ -th of them equals to $ a_{i} $ . Also this game has a common rating table in which the participants are ranked according to the product of all the skills of a hero in the descending order.

Vasya decided to 'upgrade' his character via the game store. This store offers $ n $ possible ways to improve the hero's skills; Each of these ways belongs to one of three types:

1. assign the $ i $ -th skill to $ b $ ;
2. add $ b $ to the $ i $ -th skill;
3. multiply the $ i $ -th skill by $ b $ .

Unfortunately, a) every improvement can only be used once; b) the money on Vasya's card is enough only to purchase not more than $ m $ of the $ n $ improvements. Help Vasya to reach the highest ranking in the game. To do this tell Vasya which of improvements he has to purchase and in what order he should use them to make his rating become as high as possible. If there are several ways to achieve it, print any of them.

## 输入格式

The first line contains three numbers — $ k,n,m $ ( $ 1<=k<=10^{5} $ , $ 0<=m<=n<=10^{5} $ ) — the number of skills, the number of improvements on sale and the number of them Vasya can afford.

The second line contains $ k $ space-separated numbers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ), the initial values of skills.

Next $ n $ lines contain $ 3 $ space-separated numbers $ t_{j},i_{j},b_{j} $ ( $ 1<=t_{j}<=3,1<=i_{j}<=k,1<=b_{j}<=10^{6} $ ) — the type of the $ j $ -th improvement (1 for assigning, 2 for adding, 3 for multiplying), the skill to which it can be applied and the value of $ b $ for this improvement.

## 输出格式

The first line should contain a number $ l $ ( $ 0<=l<=m $ ) — the number of improvements you should use.

The second line should contain $ l $ distinct space-separated numbers $ v_{i} $ ( $ 1<=v_{i}<=n $ ) — the indices of improvements in the order in which they should be applied. The improvements are numbered starting from $ 1 $ , in the order in which they appear in the input.

## 样例 #1

### 输入

```
2 4 3
13 20
1 1 14
1 2 30
2 1 6
3 2 2

```

### 输出

```
3
2 3 4

```



---

---
title: "Dividing Kingdom II"
layout: "post"
diff: 省选/NOI-
pid: CF687D
tag: ['贪心', '并查集']
---

# Dividing Kingdom II

## 题目描述

Long time ago, there was a great kingdom and it was being ruled by The Great Arya and Pari The Great. These two had some problems about the numbers they like, so they decided to divide the great kingdom between themselves.

The great kingdom consisted of $ n $ cities numbered from $ 1 $ to $ n $ and $ m $ bidirectional roads between these cities, numbered from $ 1 $ to $ m $ . The $ i $ -th road had length equal to $ w_{i} $ . The Great Arya and Pari The Great were discussing about destructing some prefix (all road with numbers less than some $ x $ ) and suffix (all roads with numbers greater than some $ x $ ) of the roads so there will remain only the roads with numbers $ l,l+1,...,r-1 $ and $ r $ .

After that they will divide the great kingdom into two pieces (with each city belonging to exactly one piece) such that the hardness of the division is minimized. The hardness of a division is the maximum length of a road such that its both endpoints are in the same piece of the kingdom. In case there is no such road, the hardness of the division is considered to be equal to $ -1 $ .

Historians found the map of the great kingdom, and they have $ q $ guesses about the $ l $ and $ r $ chosen by those great rulers. Given these data, for each guess $ l_{i} $ and $ r_{i} $ print the minimum possible hardness of the division of the kingdom.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,q<=1000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687D/4c89fcb1064dcf8d1c87b4349a7b3c1469f276b5.png)) — the number of cities and roads in the great kingdom, and the number of guesses, respectively.

The $ i $ -th line of the following $ m $ lines contains three integers $ u_{i} $ , $ v_{i} $ and $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n,0<=w_{i}<=10^{9} $ ), denoting the road number $ i $ connects cities $ u_{i} $ and $ v_{i} $ and its length is equal $ w_{i} $ . It's guaranteed that no road connects the city to itself and no pair of cities is connected by more than one road.

Each of the next $ q $ lines contains a pair of integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=m $ ) — a guess from the historians about the remaining roads in the kingdom.

## 输出格式

For each guess print the minimum possible hardness of the division in described scenario.

## 样例 #1

### 输入

```
5 6 5
5 4 86
5 1 0
1 3 38
2 1 33
2 4 28
2 3 40
3 5
2 6
1 3
2 3
1 6

```

### 输出

```
-1
33
-1
-1
33

```



---

---
title: "Family Photos"
layout: "post"
diff: 省选/NOI-
pid: CF725F
tag: ['贪心', '排序']
---

# Family Photos

## 题目描述

Alice and Bonnie are sisters, but they don't like each other very much. So when some old family photos were found in the attic, they started to argue about who should receive which photos. In the end, they decided that they would take turns picking photos. Alice goes first.

There are $ n $ stacks of photos. Each stack contains exactly two photos. In each turn, a player may take only a photo from the top of one of the stacks.

Each photo is described by two non-negative integers $ a $ and $ b $ , indicating that it is worth $ a $ units of happiness to Alice and $ b $ units of happiness to Bonnie. Values of $ a $ and $ b $ might differ for different photos.

It's allowed to pass instead of taking a photo. The game ends when all photos are taken or both players pass consecutively.

The players don't act to maximize their own happiness. Instead, each player acts to maximize the amount by which her happiness exceeds her sister's. Assuming both players play optimal, find the difference between Alice's and Bonnie's happiness. That is, if there's a perfectly-played game such that Alice has $ x $ happiness and Bonnie has $ y $ happiness at the end, you should print $ x-y $ .

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of two-photo stacks. Then follow $ n $ lines, each describing one of the stacks. A stack is described by four space-separated non-negative integers $ a_{1} $ , $ b_{1} $ , $ a_{2} $ and $ b_{2} $ , each not exceeding $ 10^{9} $ . $ a_{1} $ and $ b_{1} $ describe the top photo in the stack, while $ a_{2} $ and $ b_{2} $ describe the bottom photo in the stack.

## 输出格式

Output a single integer: the difference between Alice's and Bonnie's happiness if both play optimally.

## 样例 #1

### 输入

```
2
12 3 4 7
1 15 9 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
5 4 8 8
4 12 14 0

```

### 输出

```
4

```

## 样例 #3

### 输入

```
1
0 10 0 10

```

### 输出

```
-10

```



---

---
title: "PolandBall and Gifts"
layout: "post"
diff: 省选/NOI-
pid: CF755F
tag: ['贪心', '背包 DP', '进制']
---

# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 输入格式

The first line of input contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{6} $ , $ 0<=k<=n $ ), representing the number of Balls and the number of Balls who will forget to bring their presents.

The second line contains the permutation $ p $ of integers from $ 1 $ to $ n $ , where $ p_{i} $ is the index of Ball who should get a gift from the $ i $ -th Ball. For all $ i $ , $ p_{i}≠i $ holds.

## 输出格式

You should output two values — minimum and maximum possible number of Balls who will not get their presents, in that order.

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2

```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1

```

### 输出

```
2 2
```



---

---
title: "Royal Questions"
layout: "post"
diff: 省选/NOI-
pid: CF875F
tag: ['贪心', '并查集', '二分图']
---

# Royal Questions

## 题目描述

In a medieval kingdom, the economic crisis is raging. Milk drops fall, Economic indicators are deteriorating every day, money from the treasury disappear. To remedy the situation, King Charles Sunnyface decided make his $ n $ sons-princes marry the brides with as big dowry as possible.

In search of candidates, the king asked neighboring kingdoms, and after a while several delegations arrived with $ m $ unmarried princesses. Receiving guests, Karl learned that the dowry of the $ i $ th princess is $ w_{i} $ of golden coins.

Although the action takes place in the Middle Ages, progressive ideas are widespread in society, according to which no one can force a princess to marry a prince whom she does not like. Therefore, each princess has an opportunity to choose two princes, for each of which she is ready to become a wife. The princes were less fortunate, they will obey the will of their father in the matter of choosing a bride.

Knowing the value of the dowry and the preferences of each princess, Charles wants to play weddings in such a way that the total dowry of the brides of all his sons would be as great as possible. At the same time to marry all the princes or princesses is not necessary. Each prince can marry no more than one princess, and vice versa, each princess can marry no more than one prince.

Help the king to organize the marriage of his sons in the most profitable way for the treasury.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2<=n<=200000 $ , $ 1<=m<=200000 $ ) — number of princes and princesses respectively.

Each of following $ m $ lines contains three integers $ a_{i} $ , $ b_{i} $ , $ w_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , $ 1<=w_{i}<=10000 $ ) — number of princes, which $ i $ -th princess is ready to marry and the value of her dowry.

## 输出格式

Print the only integer — the maximum number of gold coins that a king can get by playing the right weddings.

## 样例 #1

### 输入

```
2 3
1 2 5
1 2 1
2 1 10

```

### 输出

```
15
```

## 样例 #2

### 输入

```
3 2
1 2 10
3 2 20

```

### 输出

```
30
```



---

---
title: "Short Code"
layout: "post"
diff: 省选/NOI-
pid: CF965E
tag: ['字符串', '贪心', '递归']
---

# Short Code

## 题目描述

Arkady's code contains $ n $ variables. Each variable has a unique name consisting of lowercase English letters only. One day Arkady decided to shorten his code.

He wants to replace each variable name with its non-empty prefix so that these new names are still unique (however, a new name of some variable can coincide with some old name of another or same variable). Among such possibilities he wants to find the way with the smallest possible total length of the new names.

A string $ a $ is a prefix of a string $ b $ if you can delete some (possibly none) characters from the end of $ b $ and obtain $ a $ .

Please find this minimum possible total length of new names.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of variables.

The next $ n $ lines contain variable names, one per line. Each name is non-empty and contains only lowercase English letters. The total length of these strings is not greater than $ 10^5 $ . The variable names are distinct.

## 输出格式

Print a single integer — the minimum possible total length of new variable names.

## 说明/提示

In the first example one of the best options is to shorten the names in the given order as "cod", "co", "c".

In the second example we can shorten the last name to "aac" and the first name to "a" without changing the other names.

## 样例 #1

### 输入

```
3
codeforces
codehorses
code

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
abba
abb
ab
aa
aacada

```

### 输出

```
11

```

## 样例 #3

### 输入

```
3
telegram
digital
resistance

```

### 输出

```
3

```



---

