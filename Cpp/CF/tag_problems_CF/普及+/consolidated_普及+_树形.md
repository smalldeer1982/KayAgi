---
title: "Dr. Evil Underscores"
layout: "post"
diff: 普及+/提高
pid: CF1285D
tag: ['字符串', '树形 DP', '字典树 Trie']
---

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 输入格式

The first line contains integer $ n $ ( $ 1\le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ).

## 输出格式

Print one integer — the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 5
```

### 输出

```
4
```



---

---
title: "Gardener and Tree"
layout: "post"
diff: 普及+/提高
pid: CF1593E
tag: ['贪心', '树形数据结构']
---

# Gardener and Tree

## 题目描述

一棵 $n$ 个结点的树。一个人做了多次操作，在每次操作中，他删除了树的所有叶结点。叶结点指的是树中至多有一个相邻节点的结点。

![](http://61.186.173.89:2019/2021/10/15/c4f2d0e1827d5.png)

如上图中所示的树。下图显示了对树进行一次操作后的结果。
![](http://61.186.173.89:2019/2021/10/15/14602247d6f15.png)

注意特殊操作的情况:

1、对空树($0$ 个顶点)进行操作时不会改变它;

2、对于仅有一个顶点的树进行操作时会移除这个顶点(这个顶点被当作一个叶子);

3、对于仅有两个顶点的树进行操作时将删除两个顶点(两个顶点都被当作叶子处理)。

求 $k$ 次操作后还剩下多少个顶点?

## 输入格式

第一行包含一个整数 $T$。然后是 $T$ 组测试数据。

对于每组测试数据，共 $n$ 行：第一行包含两个整数 $n$和 $k$——树中的顶点数和操作次数。然后是 $n−1$ 行，每一行包含两个整数 $u$ 和 $v$ ($1\le u,v≤n，u \ne v$)，表示一条无向边。保证是一个树，且每两组测试数据中间有一个换行。

## 输出格式

共 $T$ 行，每行一个正整数 $ans$，表示每组数据的答案。

## 样例 #1

### 输入

```
6

14 1
1 2
2 3
2 4
4 5
4 6
2 7
7 8
8 9
8 10
3 11
3 12
1 13
13 14

2 200000
1 2

3 2
1 2
2 3

5 1
5 1
3 2
2 1
5 4

6 2
5 1
2 5
5 6
4 2
3 4

7 1
4 3
5 1
1 3
6 1
1 7
2 1
```

### 输出

```
7
0
0
3
1
2
```



---

---
title: "Vlad and Unfinished Business"
layout: "post"
diff: 普及+/提高
pid: CF1675F
tag: ['贪心', '树形数据结构']
---

# Vlad and Unfinished Business

## 题目描述

### 题意简述

有一棵 $n$ 个节点的树，从节点 $x$ 出发，需要到 $a_1,a_2\dots a_k$ 节点完成任务（任意顺序），最终到达终点 $y$。走每条边的花费为 $1$，求最小花费。

## 输入格式

第一行一个正整数 $t$ 表示数据组数。

对于每组数据，第一行两个正整数 $n,k$ 表示节点数量和任务数量；第二行两个正整数 $x,y$ 表示起点编号和终点编号；第三行 $k$ 个正整数 $a_1,a_2\dots a_k$ 表示任务所在节点编号；接下来 $n-1$ 行，每行两个正整数表示一条边的两个端点编号。

## 输出格式

对于每组数据，输出一行一个正整数表示最小花费。

### 数据规模

$t\le 10^4,1\le n,k\le 2\times 10^5,\sum n\le2\times10^5$

## 样例 #1

### 输入

```
3

3 1
1 3
2
1 3
1 2

6 4
3 5
1 6 2 1
1 3
3 4
3 5
5 6
5 2

6 2
3 2
5 3
1 3
3 4
3 5
5 6
5 2
```

### 输出

```
3
7
2
```



---

---
title: "Fake Plastic Trees"
layout: "post"
diff: 普及+/提高
pid: CF1693B
tag: ['贪心', '树形数据结构']
---

# Fake Plastic Trees

## 题目描述

We are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is the vertex $ 1 $ and the parent of the vertex $ v $ is $ p_v $ .

There is a number written on each vertex, initially all numbers are equal to $ 0 $ . Let's denote the number written on the vertex $ v $ as $ a_v $ .

For each $ v $ , we want $ a_v $ to be between $ l_v $ and $ r_v $ $ (l_v \leq a_v \leq r_v) $ .

In a single operation we do the following:

- Choose some vertex $ v $ . Let $ b_1, b_2, \ldots, b_k $ be vertices on the path from the vertex $ 1 $ to vertex $ v $ (meaning $ b_1 = 1 $ , $ b_k = v $ and $ b_i = p_{b_{i + 1}} $ ).
- Choose a non-decreasing array $ c $ of length $ k $ of nonnegative integers: $ 0 \leq c_1 \leq c_2 \leq \ldots \leq c_k $ .
- For each $ i $ $ (1 \leq i \leq k) $ , increase $ a_{b_i} $ by $ c_i $ .

What's the minimum number of operations needed to achieve our goal?

## 输入格式

The first line contains an integer $ t $ $ (1\le t\le 1000) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2\le n\le 2 \cdot 10^5) $ — the number of the vertices in the tree.

The second line of each test case contains $ n - 1 $ integers, $ p_2, p_3, \ldots, p_n $ $ (1 \leq p_i < i) $ , where $ p_i $ denotes the parent of the vertex $ i $ .

The $ i $ -th of the following $ n $ lines contains two integers $ l_i $ and $ r_i $ $ (1 \le l_i \le r_i \le 10^9) $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output the minimum number of operations needed.

## 说明/提示

In the first test case, we can achieve the goal with a single operation: choose $ v = 2 $ and $ c = [1, 2] $ , resulting in $ a_1 = 1, a_2 = 2 $ .

In the second test case, we can achieve the goal with two operations: first, choose $ v = 2 $ and $ c = [3, 3] $ , resulting in $ a_1 = 3, a_2 = 3, a_3 = 0 $ . Then, choose $ v = 3, c = [2, 7] $ , resulting in $ a_1 = 5, a_2 = 3, a_3 = 7 $ .

## 样例 #1

### 输入

```
4
2
1
1 5
2 9
3
1 1
4 5
2 4
6 10
4
1 2 1
6 9
5 6
4 5
2 4
5
1 2 3 4
5 5
4 4
3 3
2 2
1 1
```

### 输出

```
1
2
2
5
```



---

---
title: "Tree XOR"
layout: "post"
diff: 普及+/提高
pid: CF1882D
tag: ['贪心', '树形 DP', '位运算']
---

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^{4} $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^{20} $ ).

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ ), denoting that there is an edge connecting two vertices $ u $ and $ v $ .

It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print $ m_1, m_2, \ldots, m_n $ on a new line.

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100
```

### 输出

```
8 6 12 10 
0
```



---

---
title: "Vlad and Trouble at MIT"
layout: "post"
diff: 普及+/提高
pid: CF1926G
tag: ['树形 DP']
---

# Vlad and Trouble at MIT

## 题目描述

Vladislav has a son who really wanted to go to MIT. The college dormitory at MIT (Moldova Institute of Technology) can be represented as a tree with $ n $ vertices, each vertex being a room with exactly one student. A tree is a connected undirected graph with $ n $ vertices and $ n-1 $ edges.

Tonight, there are three types of students:

- students who want to party and play music (marked with $ \texttt{P} $ ),
- students who wish to sleep and enjoy silence (marked with $ \texttt{S} $ ), and
- students who don't care (marked with $ \texttt{C} $ ).

Initially, all the edges are thin walls which allow music to pass through, so when a partying student puts music on, it will be heard in every room. However, we can place some thick walls on any edges — thick walls don't allow music to pass through them.

The university wants to install some thick walls so that every partying student can play music, and no sleepy student can hear it.

Because the university lost a lot of money in a naming rights lawsuit, they ask you to find the minimum number of thick walls they will need to use.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The second line of each test case contains $ n-1 $ integers $ a_2, \dots , a_n $ ( $ 1 \leq a_i < i $ ) — it means there is an edge between $ i $ and $ a_i $ in the tree.

The third line of each test case contains a string $ s $ of length $ n $ consisting of characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{C} $ , denoting that student $ i $ is of type $ s_i $ .

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of thick walls needed.

## 说明/提示

In the first case, we can install one thick wall between rooms $ 1 $ and $ 2 $ , as shown below. We cannot install $ 0 $ walls, since then the music from room 3 will reach room 2 where a student wants to sleep, so the answer is $ 1 $ . There are other valid solutions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926G/db6834436606f869a9404c7ce68aa100c7fe544a.png)

## 样例 #1

### 输入

```
3
3
1 1
CSP
4
1 2 2
PCSS
4
1 2 2
PPSS
```

### 输出

```
1
1
2
```



---

---
title: "Game on Tree (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970C2
tag: ['博弈论', '树形 DP']
---

# Game on Tree (Medium)

## 题目描述

This is the medium version of the problem. The difference in this version is that $ t=1 $ and we work on trees.

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ t=1 $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots, u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t=1 $ line which is either "Ron" or "Hermione".

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 4
3 5
1
```

### 输出

```
Ron
```



---

---
title: "Paint the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1975D
tag: ['贪心', '树形数据结构']
---

# Paint the Tree

## 题目描述

378QAQ has a tree with $ n $ vertices. Initially, all vertices are white.

There are two chess pieces called $ P_A $ and $ P_B $ on the tree. $ P_A $ and $ P_B $ are initially located on vertices $ a $ and $ b $ respectively. In one step, 378QAQ will do the following in order:

1. Move $ P_A $ to a neighboring vertex. If the target vertex is white, this vertex will be painted red.
2. Move $ P_B $ to a neighboring vertex. If the target vertex is colored in red, this vertex will be painted blue.

Initially, the vertex $ a $ is painted red. If $ a=b $ , the vertex $ a $ is painted blue instead. Note that both the chess pieces must be moved in each step. Two pieces can be on the same vertex at any given time.

378QAQ wants to know the minimum number of steps to paint all vertices blue.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1\leq n\leq 2\cdot 10^5 $ ).

The second line of each test case contains two integers $ a $ and $ b $ ( $ 1\leq a,b\leq n $ ).

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of steps to paint all vertices blue.

## 说明/提示

In the first test case, 378QAQ can paint all vertices blue in the following order:

- Initially, $ P_A $ is located on the vertex $ 1 $ , and $ P_B $ is located on the vertex $ 2 $ . The vertex $ 1 $ is painted red and the vertex $ 2 $ is white.
- 378QAQ moves $ P_A $ to the vertex $ 2 $ and paints it red. Then 378QAQ moves $ P_B $ to the vertex $ 1 $ and paints it blue.
- 378QAQ moves $ P_A $ to the vertex $ 1 $ . Then 378QAQ moves $ P_B $ to the vertex $ 2 $ and paints it blue.

## 样例 #1

### 输入

```
3
2
1 2
1 2
5
1 2
1 2
1 3
1 4
1 5
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4
```

### 输出

```
2
8
13
```



---

---
title: "The Omnipotent Monster Killer"
layout: "post"
diff: 普及+/提高
pid: CF1988D
tag: ['树形 DP']
---

# The Omnipotent Monster Killer

## 题目描述

You, the monster killer, want to kill a group of monsters. The monsters are on a tree with $ n $ vertices. On vertex with number $ i $ ( $ 1\le i\le n $ ), there is a monster with $ a_i $ attack points. You want to battle with monsters for $ 10^{100} $ rounds.

In each round, the following happens in order:

1. All living monsters attack you. Your health decreases by the sum of attack points of all living monsters.
2. You select some (possibly all or none) monsters and kill them. After being killed, the monster will not be able to do any attacks in the future.

There is a restriction: in one round, you cannot kill two monsters that are directly connected by an edge.

If you choose what monsters to attack optimally, what is the smallest health decrement you can have after all rounds?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1\le n\le 3\cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1,\ldots,a_n $ ( $ 1\le a_i\le 10^{12} $ ).

The following $ n-1 $ lines each contain two integers $ x,y $ ( $ 1\le x,y\le n $ ), denoting an edge on the tree connecting vertex $ x $ and $ y $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, print one integer: the minimum possible health decrement.

## 说明/提示

In the first test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1 $ , so your health decreases by $ 10^{12} $ . Then kill the monster on vertex $ 1 $ .
- In the second round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 10^{12} $ .

In the second test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1,2,3,4,5 $ , so your health decreases by $ 47+15+32+29+23=146 $ . Then kill the monsters on vertex $ 1,4,5 $ .
- In the second round: first, receive the attack from the monster on vertex $ 2,3 $ , so your health decreases by $ 15+32=47 $ . Then kill the monsters on vertex $ 2,3 $ .
- In the third round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 193 $ .

In the third test case, an optimal sequence of operations would be:

- In the first round: first, receive the attack from the monster on vertex $ 1,2,3,4,5,6,7 $ , so your health decreases by $ 8+10+2+3+5+7+4=39 $ . Then kill the monsters on vertex $ 1,3,6,7 $ .
- In the second round: first, receive the attack from the monster on vertex $ 2,4,5 $ , so your health decreases by $ 10+3+5=18 $ . Then kill the monsters on vertex $ 2,4,5 $ .
- In the third round to the $ 10^{100} $ -th round: all monsters have been killed, so nothing happens.

The total health decrement is $ 57 $ .

## 样例 #1

### 输入

```
3
1
1000000000000
5
47 15 32 29 23
1 2
1 3
2 4
2 5
7
8 10 2 3 5 7 4
1 2
1 4
3 2
5 3
6 2
7 5
```

### 输出

```
1000000000000
193
57
```



---

---
title: "Sheriff's Defense"
layout: "post"
diff: 普及+/提高
pid: CF2014F
tag: ['树形 DP']
---

# Sheriff's Defense

## 题目描述

给定一张 $n$ 结点 $n - 1$ 条边的有点权的树。初始每个结点都是黑色。

你可以执行任意次以下操作：将一个黑点染成白色，并将所有与它相邻的结点的权值减去 $c$（不包括自己）。

最大化全部白点的权值之和。

## 输入格式

多组数据。

第一行一个整数 $t\ (1 \le t \le 10 ^ 4)$，表示数据组数。

对于每组数据：第一行两个整数 $n$，$c\ (1 \le n \le 2 \cdot 10 ^ 5, 1 \le c \le 10 ^ 9)$，含义如题面所述。接下来 $n - 1$ 行，每行两个整数 $u$，$v\ (1 \le u, v \le n, u \ne v)$，表示有一条 $u \to v$ 的边。

保证 $\sum n \le 2 \cdot 10 ^ 5$。

## 输出格式

输出 $t$ 行，表示最大的全部白点的权值之和。

Translated by liuli688

## 样例 #1

### 输入

```
5
3 1
2 3 1
1 2
2 3
3 1
3 6 3
1 2
2 3
3 1
-2 -3 -1
1 2
2 3
6 1
5 -4 3 6 7 3
4 1
5 1
3 5
3 6
1 2
8 1
3 5 2 7 8 5 -3 -4
7 3
1 8
4 3
3 5
7 6
8 7
2 1
```

### 输出

```
3
8
0
17
26
```



---

---
title: "Penchick and Chloe's Trees"
layout: "post"
diff: 普及+/提高
pid: CF2031E
tag: ['树形 DP']
---

# Penchick and Chloe's Trees

## 题目描述

离 Penchick 和 Chloe 前往新加坡的时间只剩下几个小时了，他们迫不及待地想去看看新加坡植物园的参天大树！为了抑制激动的心情，Penchick 制作了一棵有根树，让 Chloe 和他自己忙个不停。

Penchick 有一棵**有根树**，由 $n$ 个节点组成，编号从 $1$ 到 $n$，节点 $1$ 是根，Chloe 可以选择一个非负整数 $d$ 来创建一棵深度为 $d$ 的**满二叉树**。

由于 Penchick 和 Chloe 是好朋友，Chloe 希望自己的树与 Penchick 的树**同构**。为了满足这个条件，Chloe 可以在自己的树上执行以下操作，次数不限：

+ 选择边 $(u,v)$，其中 $u$ 是 $v$ 的父亲。
+ 删除顶点 $v$ 和所有连接到 $v$ 的边，然后将 $v$ 之前的所有子节点直接连接到 $u$。

具体来说，在 $v$ 为叶子的边 $(u,v)$ 上进行操作，可以删除顶点 $v$，而不会添加任何新的边。

由于构建满二叉树非常耗时，Chloe 希望选择最小值 $d$，这样深度为 $d$ 的满二叉树就可以通过上述操作与 Penchick 的树同构。注意，她不能改变树的根。

**有根树**：树是没有环的连通图。有根树是指有一个节点是特殊的，叫做根。节点 $v$ 的父节点是从 $v$ 到根的简单路径上的第一个节点。根没有父节点。节点  $v$ 的子节点是以 $v$ 为父节点的任意节点 $u$。叶是任何没有子节点的节点。

**满二叉树**：一棵 Full Binary Tree 是有根树，其中每个节点都有 $0$ 或 $2$ 个子节点。满二叉树是指每个叶子与根的距离都相同的 Full Binary Tree。树的深度就是树根到树叶的距离。

**同构**：如果存在顶点的排列 $p$，使得当且仅当边  $(p_u,p_v)$ 存在于第二棵树中时，边 $(u,v)$ 存在于第一棵树中，并且 $p_{r_1}=r_2$。则两棵根分别为 $r_1,r_2$ 的树被认为是同构的。

## 输入格式

本题有多组测试数据。

第一行包含测试数据的数量 $t(1\le t\le10^5)$。每组测试数据说明如下。

每组测试数据的第一行都包含一个整数 $n(2\le n\le10^6)$，表示 Penchick 的树的节点数。

每组测试数据的第二行包含 $n-1$ 个整数 $p_2,p_3,\cdots,p_n(1\le p_i\le i-1)$，表示节点 $i$ 的父节点。

保证所有测试数据中 $n$ 的总和不超过 $10^6$。

## 输出格式

对于每个测试用例，每行输出一个整数：Chloe 的满二叉树的最小深度。

### 样例 1 解释

对于第一个测试用例，创建一棵深度为 $2$ 的满二叉树。

![](https://cdn.luogu.com.cn/upload/image_hosting/l2lstw2q.png)

考虑对边 $AC$ 进行操作。然后删除边 $AC$、$CF$ 和 $CG$ 并添加边 $AF$ 和 $AG$。

生成的树与输入的树同构。可以证明，在任何一棵深度小于 $2$ 的二叉树上进行的任何操作序列都不会导致一棵与输入所给树同构的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/nm4yi9jr.png)

在第二个测试案例中，树已经与深度为 $3$ 的完美二叉树同构。

translated by @[chaynflow](https://www.luogu.com.cn/user/559665).

## 样例 #1

### 输入

```
5
6
1 2 2 1 1
15
1 1 2 2 3 3 4 4 5 5 6 6 7 7
5
1 2 2 2
7
1 1 2 1 1 2
10
1 1 1 2 2 2 4 3 3
```

### 输出

```
2
3
3
3
3
```



---

---
title: "Resourceful Caterpillar Sequence"
layout: "post"
diff: 普及+/提高
pid: CF2053E
tag: ['动态规划 DP', '博弈论', '树形 DP']
---

# Resourceful Caterpillar Sequence

## 题目描述

无尽的七日轮回

— r-906, [Panopticon](https://www.youtube.com/watch?v=_-Vd0ZGB-lo)

在一个由 $n$ 个顶点组成的树中，定义了一种“毛毛虫”。一个毛毛虫用整数对 $(p, q)$（$1 \leq p, q \leq n$，且 $p \neq q$）表示，它的头在顶点 $p$，尾在顶点 $q$，并且该毛毛虫支配从 $p$ 到 $q$ 的简单路径上的所有顶点（包括 $p$ 和 $q$）。$(p, q)$ 的毛毛虫序列是按到 $p$ 的距离递增排序后的路径上的顶点序列。

Nora 和 Aron 轮流移动这条毛毛虫，Nora 先手。两个人都采用各自的最优策略来进行游戏：

- 他们会尽全力争取胜利；
- 如果无法赢得胜利，他们将努力阻止对方获胜（这样，游戏就会以平局收场）。

在 Nora 的回合中，她需要从与顶点 $p$ 相邻且未被毛毛虫支配的顶点中选择一个 $u$，然后将毛毛虫向顶点 $u$ 移动一个边。同样，在 Aron 的回合中，他需要从与顶点 $q$ 相邻且未被毛毛虫支配的顶点中选择一个 $v$，并将毛毛虫向顶点 $v$ 移动一个边。注意，两位玩家的移动方式是不同的。

若 $p$ 是叶子节点时，Nora 赢得胜利。而当 $q$ 是叶子节点时，Aron 赢得胜利。如果初始时 $p$ 和 $q$ 都是叶子，或经过 $10^{100}$ 回合游戏仍未结束，最终结果为平局。

请统计能让 Aron 赢得游戏的整数对 $(p, q)$ 的数量：$1 \leq p, q \leq n$ 且 $p \neq q$。

*用简单的话来说：当前的毛毛虫序列是 $c_1, c_2, \ldots, c_k$，移动后，新序列变为 $d(u, c_1), d(u, c_2), \ldots, d(u, c_k)$。这里，$d(x, y)$ 表示从 $y$ 到 $x$ 的简单路径上的下一个顶点。

*在树中，一个顶点的度数为1时，该顶点称为叶子节点。

*因此，只要游戏未结束，Nora 总能找到一个顶点 $u$ 来进行移动。Aron 也是一样。

## 输入格式

每个测试组包含多个测试用例。第一行给出一个整数 $t$（$1 \leq t \leq 2 \cdot 10^4$），表示测试用例的数量。接下来是各个测试用例的具体描述。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示树中的顶点数。

接下来的 $n - 1$ 行，每行有两个整数 $u$ 和 $v$（$1 \leq u, v \leq n$），表示顶点 $u$ 和 $v$ 之间存在一条边。保证这些边构成了一棵树。

保证所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，表示能够让 Aron 得胜的整数对 $(p, q)$ 的数量。

## 说明/提示

在第一个测试例中，所有可能的毛毛虫是 $(1, 2)$ 和 $(2, 1)$。由于初始时 $p$ 和 $q$ 都是叶子，因此结果为平局。

在第二个测试例中，满足 Aron 赢得游戏的毛毛虫包括：$(1, 3)$、$(1, 4)$、$(1, 5)$、$(2, 3)$、$(2, 4)$、$(2, 5)$。下面我们来具体分析一些毛毛虫的情况：

- 对于毛毛虫 $(1, 5)$：顶点 $p = 1$ 不是叶子，而 $q = 5$ 是叶子，因此 Aron 在一开始就胜利。
- 对于毛毛虫 $(2, 1)$：顶点 $p = 2$ 不是叶子，$q = 1$ 也不是叶子。在 Nora 的第一次移动中，她可以选择将毛毛虫移向顶点 $5$，此时毛毛虫变为 $(5, 2)$，顶点 $p = 5$ 是叶子，因此 Nora 在下一步中胜利。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
5
1 2
1 3
2 4
2 5
12
1 6
11 2
4 8
12 3
2 7
6 12
8 1
2 3
5 12
9 2
10 3
10
1 2
2 3
3 4
4 5
5 6
4 7
6 8
4 9
4 10
25
1 16
11 22
6 14
3 1
20 14
23 17
25 19
10 11
3 18
10 6
2 21
4 5
11 12
4 9
9 13
8 6
6 1
3 7
8 19
10 24
15 13
1 2
3 4
17 8
```

### 输出

```
0
6
40
27
171
```



---

---
title: "Choosing Capital for Treeland"
layout: "post"
diff: 普及+/提高
pid: CF219D
tag: ['动态规划 DP', '树形 DP']
---

# Choosing Capital for Treeland

## 题目描述

Treeland 国有 $n$ 个城市，有些城市间存在 **单向** 道路。这个国家一共有 $n - 1$ 条路。我们知道，如果把边视作双向的，那么从任意城市出发能到达任意城市。

城市的委员会最近决定为 Treeland 国选择一个首都，显然首都会是国中的一个城市。委员会将在首都开会，并经常取其他城市（这里不考虑从其他城市回到首都）。因此，如果城市 $a$ 被选为首都，那么所有的道路应该被定向，以使得我们能从城市 $a$ 到达其他城市。所以，有些路可能需要反转方向。
   
帮助委员会选择首都使得他们需要反转道路的次数最小。

## 输入格式

第一行有一个整数 $n$（$2 \le n \le 2 \times 10^5$），表示城市的数量。

接下来 $n- 1$ 行描述道路，每个道路一行，用一对整数 $s_i,t_i$（$1 \le s_i,t_i\le n$，$s_i \ne t_i$）表示该道路连接的两个城市，第 $i$ 条道路的方向是从城市 $s_i$ 到城市 $t_i$。

你可以认为 Treeland 国的城市被编号为 $1$ 到 $n$。

## 输出格式

第一行输出需要反转的道路数量的最小值。第二行输出所有可能的选择首都的方式，你需要以从小到大的顺序输出所有可能的城市编号。

Translated by uid $408071$.

## 样例 #1

### 输入

```
3
2 1
2 3

```

### 输出

```
0
2 

```

## 样例 #2

### 输入

```
4
1 4
2 4
3 4

```

### 输出

```
2
1 2 3 

```



---

---
title: "Garland"
layout: "post"
diff: 普及+/提高
pid: CF767C
tag: ['动态规划 DP', '剪枝', '树形 DP']
---

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 输入格式

The first line contains single integer $ n $ ( $ 3<=n<=10^{6} $ ) — the number of lamps in the garland.

Then $ n $ lines follow. The $ i $ -th of them contain the information about the $ i $ -th lamp: the number lamp $ a_{i} $ , it is hanging on (and $ 0 $ , if is there is no such lamp), and its temperature $ t_{i} $ ( $ -100<=t_{i}<=100 $ ). The lamps are numbered from $ 1 $ to $ n $ .

## 输出格式

If there is no solution, print -1.

Otherwise print two integers — the indexes of the lamps which mean Dima should cut the wires they are hanging on. If there are multiple answers, print any of them.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2

```

### 输出

```
1 4

```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2

```

### 输出

```
-1

```



---

