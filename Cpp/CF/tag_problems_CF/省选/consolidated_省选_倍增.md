---
title: "Split the Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1059E
tag: ['动态规划 DP', '倍增']
---

# Split the Tree

## 题目描述

You are given a rooted tree on $ n $ vertices, its root is the vertex number $ 1 $ . The $ i $ -th vertex contains a number $ w_i $ . Split it into the minimum possible number of vertical paths in such a way that each path contains no more than $ L $ vertices and the sum of integers $ w_i $ on each path does not exceed $ S $ . Each vertex should belong to exactly one path.

A vertical path is a sequence of vertices $ v_1, v_2, \ldots, v_k $ where $ v_i $ ( $ i \ge 2 $ ) is the parent of $ v_{i - 1} $ .

## 输入格式

The first line contains three integers $ n $ , $ L $ , $ S $ ( $ 1 \le n \le 10^5 $ , $ 1 \le L \le 10^5 $ , $ 1 \le S \le 10^{18} $ ) — the number of vertices, the maximum number of vertices in one path and the maximum sum in one path.

The second line contains $ n $ integers $ w_1, w_2, \ldots, w_n $ ( $ 1 \le w_i \le 10^9 $ ) — the numbers in the vertices of the tree.

The third line contains $ n - 1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ is the parent of the $ i $ -th vertex in the tree.

## 输出格式

Output one number — the minimum number of vertical paths. If it is impossible to split the tree, output $ -1 $ .

## 说明/提示

In the first sample the tree is split into $ \{1\},\ \{2\},\ \{3\} $ .

In the second sample the tree is split into $ \{1,\ 2\},\ \{3\} $ or $ \{1,\ 3\},\ \{2\} $ .

In the third sample it is impossible to split the tree.

## 样例 #1

### 输入

```
3 1 3
1 2 3
1 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 6
1 2 3
1 1

```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 1 10000
10001

```

### 输出

```
-1
```



---

---
title: "Smile House"
layout: "post"
diff: 省选/NOI-
pid: CF147B
tag: ['倍增', '枚举']
---

# Smile House

## 题目描述

n个点，m条边，无向图但一条无向边的两个方向的边权不同，求图上最小正环的大小（定义正环为从一个点出发再回到这个点经过所有边边权之和为正）（定义最小正环的含义为这个正环经过的点数最少）

## 输入格式

第一行两个整数n，m，表示点数和边数



接下来m行，一行四个整数x,y,z,w，表示x到y有一条边，x到y的边权为z，y到x的边权为w

## 输出格式

一行一个整数，表示最小正环的大小（即这个正环上点的个数），如果没有正环输出0

## 样例 #1

### 输入

```
4 4
1 2 -10 3
1 3 1 -10
2 4 -10 -1
3 4 0 -3

```

### 输出

```
4

```



---

---
title: "Chips on a Board"
layout: "post"
diff: 省选/NOI-
pid: CF1511G
tag: ['倍增']
---

# Chips on a Board

## 题目描述

Alice and Bob have a rectangular board consisting of $ n $ rows and $ m $ columns. Each row contains exactly one chip.

Alice and Bob play the following game. They choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le m $ and cut the board in such a way that only the part of it between column $ l $ and column $ r $ (inclusive) remains. So, all columns to the left of column $ l $ and all columns to the right of column $ r $ no longer belong to the board.

After cutting the board, they move chips on the remaining part of the board (the part from column $ l $ to column $ r $ ). They make alternating moves, and the player which cannot make a move loses the game. The first move is made by Alice, the second — by Bob, the third — by Alice, and so on. During their move, the player must choose one of the chips from the board and move it any positive number of cells to the left (so, if the chip was in column $ i $ , it can move to any column $ j < i $ , and the chips in the leftmost column cannot be chosen).

Alice and Bob have $ q $ pairs of numbers $ L_i $ and $ R_i $ . For each such pair, they want to determine who will be the winner of the game if $ l = L_i $ and $ r = R_i $ . Note that these games should be considered independently (they don't affect the state of the board for the next games), and both Alice and Bob play optimally.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the number of rows and columns on the board, respectively.

The second line contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le m $ ), where $ c_i $ is the index of the column where the chip in the $ i $ -th row is located (so, the chip in the $ i $ -th row is in the $ c_i $ -th column).

The third line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ L_i $ and $ R_i $ ( $ 1 \le L_i \le R_i \le m $ ).

## 输出格式

Print a string of $ q $ characters. The $ i $ -th character should be A if Alice wins the game with $ l = L_i $ and $ r = R_i $ , or B if Bob wins it.

## 样例 #1

### 输入

```
8 10
1 3 3 7 4 2 6 9
7
2 3
1 3
1 4
1 10
5 10
8 10
9 10
```

### 输出

```
BAAAAAB
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
title: "Beautiful Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1904F
tag: ['倍增', '强连通分量', 'Tarjan', '最近公共祖先 LCA']
---

# Beautiful Tree

## 题目描述

Lunchbox has a tree of size $ n $ rooted at node $ 1 $ . Each node is then assigned a value. Lunchbox considers the tree to be beautiful if each value is distinct and ranges from $ 1 $ to $ n $ . In addition, a beautiful tree must also satisfy $ m $ requirements of $ 2 $ types:

- "1 a b c" — The node with the smallest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .
- "2 a b c" — The node with the largest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .

Now, you must assign values to each node such that the resulting tree is beautiful. If it is impossible to do so, output $ -1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 2 \cdot 10^5 $ ).

The next $ n - 1 $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n, u \ne v $ ) — denoting an edge between nodes $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The next $ m $ lines each contain four integers $ t $ , $ a $ , $ b $ , and $ c $ ( $ t \in \{1,2\} $ , $ 1 \le a, b, c \le n $ ). It is guaranteed that node $ c $ is on the path between nodes $ a $ and $ b $ .

## 输出格式

If it is impossible to assign values such that the tree is beautiful, output $ -1 $ . Otherwise, output $ n $ integers, the $ i $ -th of which denotes the value of node $ i $ .

## 样例 #1

### 输入

```
7 5
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
1 2 7 1
1 7 5 7
2 4 2 2
```

### 输出

```
1 6 7 5 3 4 2
```

## 样例 #2

### 输入

```
2 2
1 2
1 1 2 1
1 1 2 2
```

### 输出

```
-1
```



---

---
title: "Your Loss"
layout: "post"
diff: 省选/NOI-
pid: CF1983G
tag: ['倍增', '树形 DP']
---

# Your Loss

## 题目描述

You are given a tree with $ n $ nodes numbered from $ 1 $ to $ n $ , along with an array of size $ n $ . The value of $ i $ -th node is $ a_{i} $ . There are $ q $ queries. In each query, you are given 2 nodes numbered as $ x $ and $ y $ .

Consider the path from the node numbered as $ x $ to the node numbered as $ y $ . Let the path be represented by $ x = p_0, p_1, p_2, \ldots, p_r = y $ , where $ p_i $ are the intermediate nodes. Compute the sum of $ a_{p_i}\oplus i $ for each $ i $ such that $ 0 \le i \le r $ where $ \oplus $ is the [XOR](https://en.wikipedia.org/wiki/Exclusive_or) operator.

More formally, compute
$$
\sum_{i =0}^{r} a_{p_i}\oplus i
$$
.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Each test case contains several sets of input data.

The first line of each set of input data contains a single integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the number of nodes.

The next $ n-1 $ lines of each set of input data contain $ 2 $ integers, $ u $ and $ v $ representing an edge between the node numbered $ u $ and the node numbered $ v $ . It is guaranteed that $ u \ne v $ and that the edges form a tree.

The next line of each set of input data contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 5 \cdot 10^5 $ ) — values of the nodes.

The next line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries.

The next $ q $ lines describe the queries. The $ i $ -th query contains $ 2 $ integers $ x $ and $ y $ ( $ 1 \le x,y \le n $ ) denoting the starting and the ending node of the path.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ and sum of $ q $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each query, output a single number — the sum from the problem statement.

## 样例 #1

### 输入

```
1
4
1 2
2 3
3 4
2 3 6 5
3
1 4
3 4
1 1
```

### 输出

```
14
10
2
```



---

---
title: "Tropical Season"
layout: "post"
diff: 省选/NOI-
pid: CF2066E
tag: ['倍增', '分块']
---

# Tropical Season

## 题目描述

您有 $n$ 个容量无限的桶。第 $i$ 个桶初始装有 $a_i$ 千克水。在此问题中，我们假设所有桶自身重量相同。

已知恰好有一个桶的表面含有少量热带毒药，总重量为 $0.179$ 千克。但您不知道具体是哪个桶含有毒药。您的任务是确定这个有毒的桶。

所有桶都放置在秤上。然而秤不会显示每个桶的确切重量，而是为每对桶显示它们的重量比较结果。因此，对于任意两个桶，您可以判断它们的重量是否相等，若不相等则可知哪个桶更重。毒药和水的重量均计入桶的总重量。

秤始终处于开启状态，其信息可无限次使用。

您还可以进行倒水操作：可以将任意数量的水从任意一个桶倒入另一个桶（两者可为不同桶）。

但倒水时，您必须物理接触被倒出的桶。如果该桶恰好是含毒桶，您将死亡。必须避免这种情况发生。

但您可以将水倒入含毒桶而无需触碰它。

换言之，您可以选择参数 $i, j, x$（$i \neq j$，$1 \leq i, j \leq n$，$0 < x \leq a_i$，且编号 $i$ 的桶不含毒）并执行操作 $a_i := a_i - x$，$a_j := a_j + x$。其中 $x$ 不必是整数。

在利用倒水操作和秤的信息时，能否保证确定含毒桶的同时存活？已知毒药必定存在于恰好一个桶中。

此外，您需要处理 $q$ 次查询。每次查询将移除一个现有桶，或添加一个装有指定水量新桶。每次查询后，您需要回答在恰好存在一个含毒桶的条件下，能否保证确定该桶。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^6$）——现有桶中的水量。

接下来 $q$ 行每行包含一个查询，格式为 + x 或 - x，分别表示添加和移除一个装有 $x$ 千克水的桶。保证执行 - x 查询时存在水量为 $x$ 的桶，且所有查询后至少保留一个桶。所有查询中 $1 \leq x \leq 10^6$。

## 输出格式

输出 $q+1$ 行，依次为初始状态及每次查询后的答案。若可确定含毒桶则输出 "Yes"，否则输出 "No"。输出不区分大小写（如 "yEs"、"YES" 等均视为肯定回答）。

## 说明/提示

第一个测试案例中，初始桶的水量为 $[2, 2, 4, 11]$。可先比较第一和第二个桶的重量：若不等则可断定较重桶含毒；若相等则二者均不含毒。接着可将第一桶所有水倒入第二桶，此时第二和第三桶均有 $4$ 千克水。再次比较二者重量：若不等则较重桶含毒；否则二者均不含毒。唯一可能含毒的桶变为第四个。通过此策略可安全确定含毒桶。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 7
2 2 4 11
- 2
+ 4
+ 30
+ 40
- 4
+ 2
+ 2
```

### 输出

```
Yes
No
Yes
No
Yes
No
No
Yes
```

## 样例 #2

### 输入

```
6 7
5000 1000 400 400 100 99
+ 1
- 5000
- 1
- 400
- 400
- 100
- 99
```

### 输出

```
No
Yes
Yes
Yes
No
No
No
Yes
```



---

---
title: "Duff in the Army"
layout: "post"
diff: 省选/NOI-
pid: CF587C
tag: ['线段树', '倍增', '树链剖分']
---

# Duff in the Army

## 题目描述

Duff是一个军队中的一名士兵。Malek是**她**的上司。

他们在一个名为Andarz Gu的国家里，这个国家有 $n$  个城市，分别编号 $1-n$  。有 $n-1$  条双向通行的道路联通整个国家。

一共有 $m$  个人居住在这个国家中的一些城市里，每一个人有他的身份号（第 $i$  个人的身份号是 $i$  ）。注意，有可能有多个人居住在同一个城市，也有可能有些城市无人居住。

Malek喜欢对别人下命令，所以他让Duff回答他的q个提问，每一个提问包含三个数 $v$  , $u$  和 $a$  。

为了回答一个提问：  
设想一共有 $x$  个人居住在从城市 $u$  到城市 $v$  （包含）的路径上，他们的身份号从小到大排序后分别是 $p_1,p_2,...,p_x$  。如果设 $k=min(x,a)$  ，那么Duff应该按顺序告诉Malek $k,p_1,p_2,...,p_k$  。从另一种说法来说，Malek想要知道在路径上身份编号前 $a$  小的人（或者更少，如果这条路上总共居住的人少于 $a$  个）。

Duff现在非常忙碌，所以她让你来帮助她回答Malek的提问。

## 输入格式

输入的第一行包括3个整数， $n$  , $m$  和 $q$  。($1<=n,m,q<=10^5$ ）

接下来的 $n-1$  行描述了连通城市的道路。每一行包括两个整数 $u$  和 $v$  ，表示从城市 $u$  到城市 $v$  有一条双向道路。（$1<=u,v<=n , u≠v$ ）

接下来的一行包括 $m$  个正整数 $c_1,c_2,...,c_m$  ， $c_i$  表示编号为 $i$  的人居住在城市 $c_i$  里。（$1<=c_i<=n$ ，对于每一个 $i$  有 $1<=i<=m$ ）

接下来的 $q$  行描述了Malek的提问。每一行包括三个正整数 $u$  , $v$  和 $a$  （$1<=v,u<=n$ ，$1<=a<=10$ ，含义见题面）

## 输出格式

对于每一次提问，输出一行，包括 $k,p_1,p_2,...,p_k$  （含义见题面）。

感谢@星烁晶熠辉  提供的翻译

## 样例 #1

### 输入

```
5 4 5
1 3
1 2
1 4
4 5
2 1 4 3
4 5 6
1 5 2
5 5 10
2 3 3
5 3 1

```

### 输出

```
1 3
2 2 3
0
3 1 2 4
1 2

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
title: "NN country"
layout: "post"
diff: 省选/NOI-
pid: CF983E
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ means that cities $ p_i $ and $ i $ are connected by road.

The third line contains a single integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of bus routes.

Each of the next $ m $ lines contains $ 2 $ integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ , $ a \neq b $ ), meaning that there is a bus route between cities $ a $ and $ b $ . It is possible that there is more than one route between two cities.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of questions you are interested in.

Each of the next $ q $ lines contains $ 2 $ integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ), meaning that you are interested if it is possible to get from city $ v $ to city $ u $ and what is the minimum number of buses you need to use for it.

## 输出格式

Print the answer for each question on a separate line. If there is no way to get from one city to another, print $ -1 $ . Otherwise print the minimum number of buses you have to use.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3

```

### 输出

```
1
3
-1
1
2
3

```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3

```

### 输出

```
1
-1
-1
1
-1
1

```



---

