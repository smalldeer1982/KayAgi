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
title: "Unique Occurrences"
layout: "post"
diff: 省选/NOI-
pid: CF1681F
tag: ['树形 DP', '动态树 LCT']
---

# Unique Occurrences

## 题目描述

You are given a tree, consisting of $ n $ vertices. Each edge has an integer value written on it.

Let $ f(v, u) $ be the number of values that appear exactly once on the edges of a simple path between vertices $ v $ and $ u $ .

Calculate the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ 1 \le v < u \le n $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^5 $ ) — the number of vertices in the tree.

Each of the next $ n-1 $ lines contains three integers $ v, u $ and $ x $ ( $ 1 \le v, u, x \le n $ ) — the description of an edge: the vertices it connects and the value written on it.

The given edges form a tree.

## 输出格式

Print a single integer — the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ v < u $ .

## 样例 #1

### 输入

```
3
1 2 1
1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 2 2
1 3 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 4 4
1 2 3
3 4 4
4 5 5
```

### 输出

```
14
```

## 样例 #4

### 输入

```
2
2 1 1
```

### 输出

```
1
```

## 样例 #5

### 输入

```
10
10 2 3
3 8 8
4 8 9
5 8 5
3 10 7
7 8 2
5 6 6
9 3 4
1 6 3
```

### 输出

```
120
```



---

---
title: "Partial Virtual Trees"
layout: "post"
diff: 省选/NOI-
pid: CF1707D
tag: ['数学', '树形 DP', '容斥原理']
---

# Partial Virtual Trees

## 题目描述

Kawashiro Nitori is a girl who loves competitive programming. One day she found a rooted tree consisting of $ n $ vertices. The root is vertex $ 1 $ . As an advanced problem setter, she quickly thought of a problem.

Kawashiro Nitori has a vertex set $ U=\{1,2,\ldots,n\} $ . She's going to play a game with the tree and the set. In each operation, she will choose a vertex set $ T $ , where $ T $ is a partial virtual tree of $ U $ , and change $ U $ into $ T $ .

A vertex set $ S_1 $ is a partial virtual tree of a vertex set $ S_2 $ , if $ S_1 $ is a subset of $ S_2 $ , $ S_1 \neq S_2 $ , and for all pairs of vertices $ i $ and $ j $ in $ S_1 $ , $ \operatorname{LCA}(i,j) $ is in $ S_1 $ , where $ \operatorname{LCA}(x,y) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ x $ and $ y $ on the tree. Note that a vertex set can have many different partial virtual trees.

Kawashiro Nitori wants to know for each possible $ k $ , if she performs the operation exactly $ k $ times, in how many ways she can make $ U=\{1\} $ in the end? Two ways are considered different if there exists an integer $ z $ ( $ 1 \le z \le k $ ) such that after $ z $ operations the sets $ U $ are different.

Since the answer could be very large, you need to find it modulo $ p $ . It's guaranteed that $ p $ is a prime number.

## 输入格式

The first line contains two integers $ n $ and $ p $ ( $ 2 \le n \le 2000 $ , $ 10^8 + 7 \le p \le 10^9+9 $ ). It's guaranteed that $ p $ is a prime number.

Each of the next $ n-1 $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), representing an edge between $ u_i $ and $ v_i $ .

It is guaranteed that the given edges form a tree.

## 输出格式

The only line contains $ n-1 $ integers — the answer modulo $ p $ for $ k=1,2,\ldots,n-1 $ .

## 说明/提示

In the first test case, when $ k=1 $ , the only possible way is:

1. $ \{1,2,3,4\} \to \{1\} $ .

When $ k=2 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,3\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,4\} \to \{1\} $ .

When $ k=3 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,2\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,4\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,3\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,4\} \to \{1\} $ .

## 样例 #1

### 输入

```
4 998244353
1 2
2 3
1 4
```

### 输出

```
1 6 6
```

## 样例 #2

### 输入

```
7 100000007
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
1 47 340 854 880 320
```

## 样例 #3

### 输入

```
8 1000000007
1 2
2 3
3 4
4 5
5 6
6 7
7 8
```

### 输出

```
1 126 1806 8400 16800 15120 5040
```



---

---
title: "Multiset of Strings"
layout: "post"
diff: 省选/NOI-
pid: CF1709F
tag: ['树形 DP', '快速傅里叶变换 FFT']
---

# Multiset of Strings

## 题目描述

You are given three integers $ n $ , $ k $ and $ f $ .

Consider all binary strings (i. e. all strings consisting of characters $ 0 $ and/or $ 1 $ ) of length from $ 1 $ to $ n $ . For every such string $ s $ , you need to choose an integer $ c_s $ from $ 0 $ to $ k $ .

A multiset of binary strings of length exactly $ n $ is considered beautiful if for every binary string $ s $ with length from $ 1 $ to $ n $ , the number of strings in the multiset such that $ s $ is their prefix is not exceeding $ c_s $ .

For example, let $ n = 2 $ , $ c_{0} = 3 $ , $ c_{00} = 1 $ , $ c_{01} = 2 $ , $ c_{1} = 1 $ , $ c_{10} = 2 $ , and $ c_{11} = 3 $ . The multiset of strings $ \{11, 01, 00, 01\} $ is beautiful, since:

- for the string $ 0 $ , there are $ 3 $ strings in the multiset such that $ 0 $ is their prefix, and $ 3 \le c_0 $ ;
- for the string $ 00 $ , there is one string in the multiset such that $ 00 $ is its prefix, and $ 1 \le c_{00} $ ;
- for the string $ 01 $ , there are $ 2 $ strings in the multiset such that $ 01 $ is their prefix, and $ 2 \le c_{01} $ ;
- for the string $ 1 $ , there is one string in the multiset such that $ 1 $ is its prefix, and $ 1 \le c_1 $ ;
- for the string $ 10 $ , there are $ 0 $ strings in the multiset such that $ 10 $ is their prefix, and $ 0 \le c_{10} $ ;
- for the string $ 11 $ , there is one string in the multiset such that $ 11 $ is its prefix, and $ 1 \le c_{11} $ .

Now, for the problem itself. You have to calculate the number of ways to choose the integer $ c_s $ for every binary string $ s $ of length from $ 1 $ to $ n $ in such a way that the maximum possible size of a beautiful multiset is exactly $ f $ .

## 输入格式

The only line of input contains three integers $ n $ , $ k $ and $ f $ ( $ 1 \le n \le 15 $ ; $ 1 \le k, f \le 2 \cdot 10^5 $ ).

## 输出格式

Print one integer — the number of ways to choose the integer $ c_s $ for every binary string $ s $ of length from $ 1 $ to $ n $ in such a way that the maximum possible size of a beautiful multiset is exactly $ f $ . Since it can be huge, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, the three ways to choose the integers $ c_s $ are:

- $ c_0 = 0 $ , $ c_1 = 2 $ , then the maximum beautiful multiset is $ \{1, 1\} $ ;
- $ c_0 = 1 $ , $ c_1 = 1 $ , then the maximum beautiful multiset is $ \{0, 1\} $ ;
- $ c_0 = 2 $ , $ c_1 = 0 $ , then the maximum beautiful multiset is $ \{0, 0\} $ .

## 样例 #1

### 输入

```
1 42 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 37 13
```

### 输出

```
36871576
```

## 样例 #3

### 输入

```
4 1252 325
```

### 输出

```
861735572
```

## 样例 #4

### 输入

```
6 153 23699
```

### 输出

```
0
```

## 样例 #5

### 输入

```
15 200000 198756
```

### 输出

```
612404746
```



---

---
title: "Min-Fund Prison (Hard)"
layout: "post"
diff: 省选/NOI-
pid: CF1970G3
tag: ['树形 DP']
---

# Min-Fund Prison (Hard)

## 题目描述

现给出一张由 $n$ 个点 $m$ 条边构成的无向图，其 $m$ 条边为 $(u_i, v_i)$ ( $1\leq i\leq m$ )，表示 $u_i,v_i$ 相连。图中不存在重边，也没有自环。

你可以以 $c$ 的成本在任意两个点 $x, y$ 之间连一条边（连边操作进行之后图必须连通）。这个操作可以进行任意次，设你操作了 $k$ 次。要求操作结束后图是连通的。

在连边操作之后，你必须删去一条割边，使得剩下的图恰由 $2$ 个连通块组成。设两个连通块的大小为 $x,y$ ，请问 $x^2+y^2+kc$ 的最小值为何？

## 输入格式

第一行输入样例个数 $t$ ( $1\leq t\leq 10^5$ ) 。接下来输入 $t$ 个样例，每个样例形式如下——

每个样例的第一行包含三个整数 $n, m, c$ ( $2\leq n\leq 10^5, 1\leq m\leq 5\times 10^5, 1\leq c\leq 10^9$ )，表示点数，边数和加边操作的成本。

接下来 $m$ 行，每一行输入两个整数 $u, v$ ( $1\leq u,v\leq n,u\neq v$ )，表示 $u,v$ 之间有一条边。

保证对于所有输入的样例，满足 $\sum n\leq 10^5,\sum m\leq 5\times 10^5$ 。

## 输出格式

如果能够使得最后结果为两个连通块，输出 $x^2+y^2+kc$ 的最小值；否则，输出 $-1$ 。

## 样例 #1

### 输入

```
4
4 6 5
4 3
2 3
2 4
1 2
4 1
3 1
6 6 2
1 4
2 5
3 6
1 5
3 5
6 5
6 5 7
1 4
2 5
3 6
3 5
6 5
7 5 4
1 4
3 6
3 5
6 5
2 7
```

### 输出

```
-1
20
25
33
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
title: "Information Reform"
layout: "post"
diff: 省选/NOI-
pid: CF70E
tag: ['树形 DP']
---

# Information Reform

## 题目描述

尽管现在已经是21世纪了，但是大众传播媒介在$Walrusland$依然没有普及开来。这里的城市通过能够在城市间的道路来往的信使来互相传递消息。在$Walrusland$，城市间的道路保证信使可以从一座城市到任意另一座城市，而且这些道路是等长的。  
北极政府决定实施一项信息改革。几座城市被选中成为区域信息中心。维护一座区域信息中心每年需要花费$k$个$fishlar$（这是当地的货币）。假设每座区域信息中心总是能即时获得最新的消息。  
每一座不是区域信息中心的城市，都会被安排通过一座区域信息中心来保持信息通达。这样，每年维护费用将会等于$d_{len} \ $个$fishlar$，其中$len$表示这座城市到它的区域信息中心的距离，即一个人从这座城市到它的区域信息中心需要走过的道路条数。  
你的任务是求出实行这项改革的最小开销。

## 输入格式

第一行包含两个给定的整数$n$和$k$（$1<=n<=180$，$1<=k<=10^{5}$）；  
第二行包含$n-1$个整数$d_i$，下标从$1$开始。（$d_{i}<=d_{i+1},0<=d_{i}<=10^{5}$）  
接下来的$n-1$行包含被一条道路连接的城市对。

## 输出格式

第一行，输出每年维护信息联系的最小花销。（单位：$fishlar$）；
第二行，输出$n$个整数，第$i$个整数代表第$i$座城市所由编号为$a_i$的区域信息中心的负责；如果第$i$座城市是一座区域信息中心，你只需输出数字$i$。  
如果此题有多解，只需输出任意一组。  
     
翻译 By @若如初见

## 样例 #1

### 输入

```
8 10
2 5 9 11 15 19 20
1 4
1 3
1 7
4 6
2 8
2 3
3 5

```

### 输出

```
38
3 3 3 4 3 4 3 3 
```



---

---
title: "Escape Through Leaf"
layout: "post"
diff: 省选/NOI-
pid: CF932F
tag: ['线段树', '树形 DP']
---

# Escape Through Leaf

## 题目描述

You are given a tree with $ n $ nodes (numbered from $ 1 $ to $ n $ ) rooted at node $ 1 $ . Also, each node has two values associated with it. The values for $ i $ -th node are $ a_{i} $ and $ b_{i} $ .

You can jump from a node to any node in its subtree. The cost of one jump from node $ x $ to node $ y $ is the product of $ a_{x} $ and $ b_{y} $ . The total cost of a path formed by one or more jumps is sum of costs of individual jumps. For every node, calculate the minimum total cost to reach any leaf from that node. Pay attention, that root can never be leaf, even if it has degree $ 1 $ .

Note that you cannot jump from a node to itself.

## 输入格式

The first line of input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of nodes in the tree.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n}(-10^{5}<=a_{i}<=10^{5}) $ .

The third line contains $ n $ space-separated integers $ b_{1},b_{2},...,b_{n}(-10^{5}<=b_{i}<=10^{5}) $ .

Next $ n-1 $ lines contains two space-separated integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) describing edge between nodes $ u_{i} $ and $ v_{i} $ in the tree.

## 输出格式

Output $ n $ space-separated integers, $ i $ -th of which denotes the minimum cost of a path from node $ i $ to reach any leaf.

## 说明/提示

In the first example, node $ 3 $ is already a leaf, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 3 $ with cost $ a_{2}×b_{3}=50 $ . For node $ 1 $ , jump directly to node $ 3 $ with cost $ a_{1}×b_{3}=10 $ .

In the second example, node $ 3 $ and node $ 4 $ are leaves, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 4 $ with cost $ a_{2}×b_{4}=100 $ . For node $ 1 $ , jump to node $ 2 $ with cost $ a_{1}×b_{2}=-400 $ followed by a jump from $ 2 $ to $ 4 $ with cost $ a_{2}×b_{4}=100 $ .

## 样例 #1

### 输入

```
3
2 10 -1
7 -7 5
2 3
2 1

```

### 输出

```
10 50 0 
```

## 样例 #2

### 输入

```
4
5 -10 5 7
-8 -80 -3 -10
2 1
2 4
1 3

```

### 输出

```
-300 100 0 0 
```



---

