---
title: "Dominant Indices"
layout: "post"
diff: 省选/NOI-
pid: CF1009F
tag: ['动态规划 DP', '树上启发式合并', '枚举']
---

# Dominant Indices

## 题目描述

You are given a rooted undirected tree consisting of $ n $ vertices. Vertex $ 1 $ is the root.

Let's denote a depth array of vertex $ x $ as an infinite sequence $ [d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots] $ , where $ d_{x, i} $ is the number of vertices $ y $ such that both conditions hold:

- $ x $ is an ancestor of $ y $ ;
- the simple path from $ x $ to $ y $ traverses exactly $ i $ edges.

The dominant index of a depth array of vertex $ x $ (or, shortly, the dominant index of vertex $ x $ ) is an index $ j $ such that:

- for every $ k < j $ , $ d_{x, k} < d_{x, j} $ ;
- for every $ k > j $ , $ d_{x, k} \le d_{x, j} $ .

For every vertex in the tree calculate its dominant index.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of vertices in a tree.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ , $ x \ne y $ ). This line denotes an edge of the tree.

It is guaranteed that these edges form a tree.

## 输出格式

Output $ n $ numbers. $ i $ -th number should be equal to the dominant index of vertex $ i $ .

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
0
0
0
0

```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
1
0
0
0

```

## 样例 #3

### 输入

```
4
1 2
2 3
2 4

```

### 输出

```
2
1
0
0

```



---

---
title: "Poachers"
layout: "post"
diff: 省选/NOI-
pid: CF1585G
tag: ['博弈论', '树上启发式合并']
---

# Poachers

## 题目描述

Alice and Bob are two poachers who cut trees in a forest.

A forest is a set of zero or more trees. A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root. Children of vertex $ v $ are all nodes for which $ v $ is the parent. A vertex is a leaf if it has no children.

In this problem we define the depth of vertex as number of vertices on the simple path from this vertex to the root. The rank of a tree is the minimum depth among its leaves.

Initially there is a forest of rooted trees. Alice and Bob play a game on this forest. They play alternating turns with Alice going first. At the beginning of their turn, the player chooses a tree from the forest. Then the player chooses a positive cutting depth, which should not exceed the rank of the chosen tree. Then the player removes all vertices of that tree whose depth is less that or equal to the cutting depth. All other vertices of the tree form a set of rooted trees with root being the vertex with the smallest depth before the cut. All these trees are included in the game forest and the game continues.

A player loses if the forest is empty at the beginning of his move.

You are to determine whether Alice wins the game if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 5 \cdot 10^5 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ) — total number of vertices in the initial forest.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 0 \leq p_i \leq n $ ) — description of the forest. If $ p_i = 0 $ , then the $ i $ -th vertex is the root of a tree, otherwise $ p_i $ is the parent of the vertex $ i $ . It's guaranteed that $ p $ defines a correct forest of rooted trees.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print "YES" (without quotes) if Alice wins, otherwise print "NO" (without quotes). You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case Bob has a symmetric strategy, so Alice cannot win.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/504019013a3bfbf8eb56c8730800a342f1394e57.png)

In the second test case Alice can choose the second tree and cutting depth $ 1 $ to get a forest on which she has a symmetric strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/8fe2d012fa7f86edd6ce3b0992b73d46bc9c4b34.png)

In third test case the rank of the only tree is $ 2 $ and both possible moves for Alice result in a loss. Bob either can make the forest with a symmetric strategy for himself, or clear the forest.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/eed2cbe70e21303a782188eb3bbbd7989634e2f0.png)

In the fourth test case all leafs have the same depth, so Alice can clear the forest in one move.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/095a24a5876a4e208466c20d0a9b949b0c7e2ff3.png)

## 样例 #1

### 输入

```
4
4
0 1 0 3
7
0 1 2 0 4 5 6
4
0 1 1 2
7
0 1 1 2 2 3 3
```

### 输出

```
NO
YES
NO
YES
```



---

---
title: "Blood Cousins Return"
layout: "post"
diff: 省选/NOI-
pid: CF246E
tag: ['树上启发式合并']
---

# Blood Cousins Return

## 题目描述

Polycarpus got hold of a family tree. The found tree describes the family relations of $ n $ people, numbered from 1 to $ n $ . Every person in this tree has at most one direct ancestor. Also, each person in the tree has a name, the names are not necessarily unique.

We call the man with a number $ a $ a 1-ancestor of the man with a number $ b $ , if the man with a number $ a $ is a direct ancestor of the man with a number $ b $ .

We call the man with a number $ a $ a $ k $ -ancestor $ (k&gt;1) $ of the man with a number $ b $ , if the man with a number $ b $ has a 1-ancestor, and the man with a number $ a $ is a $ (k-1) $ -ancestor of the 1-ancestor of the man with a number $ b $ .

In the tree the family ties do not form cycles. In other words there isn't a person who is his own direct or indirect ancestor (that is, who is an $ x $ -ancestor of himself, for some $ x $ , $ x > 0 $ ).

We call a man with a number $ a $ the $ k $ -son of the man with a number $ b $ , if the man with a number $ b $ is a $ k $ -ancestor of the man with a number $ a $ .

Polycarpus is very much interested in how many sons and which sons each person has. He took a piece of paper and wrote $ m $ pairs of numbers $ v_{i} $ , $ k_{i} $ . Help him to learn for each pair $ v_{i} $ , $ k_{i} $ the number of distinct names among all names of the $ k_{i} $ -sons of the man with number $ v_{i} $ .

## 输入格式

The first line of the input contains a single integer $ n $ $ (1 \le n \le 10^{5}) $ — the number of people in the tree. Next $ n $ lines contain the description of people in the tree. The $ i $ -th line contains space-separated string $ s_{i} $ and integer $ r_{i} $ $ (0<=r_{i}<=n) $ , where $ s_{i} $ is the name of the man with a number $ i $ , and $ r_{i} $ is either the number of the direct ancestor of the man with a number $ i $ or 0, if the man with a number $ i $ has no direct ancestor.

The next line contains a single integer $ m $ $ (1 \le m \le 10^{5}) $ — the number of Polycarpus's records. Next $ m $ lines contain space-separated pairs of integers. The $ i $ -th line contains integers $ v_{i} $ , $ k_{i} $ $ (1 \le v_{i},k_{i} \le n) $ .

It is guaranteed that the family relationships do not form cycles. The names of all people are non-empty strings, consisting of no more than $20$ lowercase English letters.

## 输出格式

Print $ m $ whitespace-separated integers — the answers to Polycarpus's records. Print the answers to the records in the order, in which the records occur in the input.

## 样例 #1

### 输入

```
6
pasha 0
gerald 1
gerald 1
valera 2
igor 3
olesya 1
5
1 1
1 2
1 3
3 1
6 1

```

### 输出

```
2
2
0
1
0

```

## 样例 #2

### 输入

```
6
valera 0
valera 1
valera 1
gerald 0
valera 4
kolya 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1

```

### 输出

```
1
0
0
0
2
0
0

```



---

---
title: "Tree and Queries"
layout: "post"
diff: 省选/NOI-
pid: CF375D
tag: ['莫队', '树上启发式合并']
---

# Tree and Queries

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from 1 to $ n $ . Then we represent the color of vertex $ v $ as $ c_{v} $ . The tree root is a vertex with number 1.

In this problem you need to answer to $ m $ queries. Each query is described by two integers $ v_{j},k_{j} $ . The answer to query $ v_{j},k_{j} $ is the number of such colors of vertices $ x $ , that the subtree of vertex $ v_{j} $ contains at least $ k_{j} $ vertices of color $ x $ .

You can find the definition of a rooted tree by the following link: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5}; 1<=m<=10^{5}) $ . The next line contains a sequence of integers $ c_{1},c_{2},...,c_{n} $ $ (1<=c_{i}<=10^{5}) $ . The next $ n-1 $ lines contain the edges of the tree. The $ i $ -th line contains the numbers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n; a_{i}≠b_{i}) $ — the vertices connected by an edge of the tree.

Next $ m $ lines contain the queries. The $ j $ -th line contains two integers $ v_{j},k_{j} $ $ (1<=v_{j}<=n; 1<=k_{j}<=10^{5}) $ .

## 输出格式

Print $ m $ integers — the answers to the queries in the order the queries appear in the input.

## 说明/提示

A subtree of vertex $ v $ in a rooted tree with root $ r $ is a set of vertices $ {u :dist(r,v)+dist(v,u)=dist(r,u)} $ . Where $ dist(x,y) $ is the length (in edges) of the shortest path between vertices $ x $ and $ y $ .

## 样例 #1

### 输入

```
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3

```

### 输出

```
2
2
1
0
1

```

## 样例 #2

### 输入

```
4 1
1 2 3 4
1 2
2 3
3 4
1 1

```

### 输出

```
4

```



---

---
title: "Tree Requests"
layout: "post"
diff: 省选/NOI-
pid: CF570D
tag: ['树上启发式合并']
---

# Tree Requests

## 题目描述

Roman planted a tree consisting of $ n $ vertices. Each vertex contains a lowercase English letter. Vertex $ 1 $ is the root of the tree, each of the $ n-1 $ remaining vertices has a parent in the tree. Vertex is connected with its parent by an edge. The parent of vertex $ i $ is vertex $ p_{i} $ , the parent index is always less than the index of the vertex (i.e., $ p_{i}&lt;i $ ).

The depth of the vertex is the number of nodes on the path from the root to $ v $ along the edges. In particular, the depth of the root is equal to $ 1 $ .

We say that vertex $ u $ is in the subtree of vertex $ v $ , if we can get from $ u $ to $ v $ , moving from the vertex to the parent. In particular, vertex $ v $ is in its subtree.

Roma gives you $ m $ queries, the $ i $ -th of which consists of two numbers $ v_{i} $ , $ h_{i} $ . Let's consider the vertices in the subtree $ v_{i} $ located at depth $ h_{i} $ . Determine whether you can use the letters written at these vertices to make a string that is a palindrome. The letters that are written in the vertexes, can be rearranged in any order to make a palindrome, but all letters should be used.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=500000 $ ) — the number of nodes in the tree and queries, respectively.

The following line contains $ n-1 $ integers $ p_{2},p_{3},...,p_{n} $ — the parents of vertices from the second to the $ n $ -th ( $ 1<=p_{i}&lt;i $ ).

The next line contains $ n $ lowercase English letters, the $ i $ -th of these letters is written on vertex $ i $ .

Next $ m $ lines describe the queries, the $ i $ -th line contains two numbers $ v_{i} $ , $ h_{i} $ ( $ 1<=v_{i},h_{i}<=n $ ) — the vertex and the depth that appear in the $ i $ -th query.

## 输出格式

Print $ m $ lines. In the $ i $ -th line print "Yes" (without the quotes), if in the $ i $ -th query you can make a palindrome from the letters written on the vertices, otherwise print "No" (without the quotes).

## 说明/提示

String $ s $ is a palindrome if reads the same from left to right and from right to left. In particular, an empty string is a palindrome.

Clarification for the sample test.

In the first query there exists only a vertex 1 satisfying all the conditions, we can form a palindrome "z".

In the second query vertices 5 and 6 satisfy condititions, they contain letters "с" and "d" respectively. It is impossible to form a palindrome of them.

In the third query there exist no vertices at depth 1 and in subtree of 4. We may form an empty palindrome.

In the fourth query there exist no vertices in subtree of 6 at depth 1. We may form an empty palindrome.

In the fifth query there vertices 2, 3 and 4 satisfying all conditions above, they contain letters "a", "c" and "c". We may form a palindrome "cac".

## 样例 #1

### 输入

```
6 5
1 1 1 3 3
zacccd
1 1
3 3
4 1
6 1
1 2

```

### 输出

```
Yes
No
Yes
Yes
Yes

```



---

---
title: "Lomsat gelral"
layout: "post"
diff: 省选/NOI-
pid: CF600E
tag: ['搜索', '线段树', '树上启发式合并', '搜索']
---

# Lomsat gelral

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=n $ ), $ c_{i} $ — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j},y_{j} $ ( $ 1<=x_{j},y_{j}<=n $ ) — the edge of the tree. The first vertex is the root of the tree.

## 输出格式

Print $ n $ integers — the sums of dominating colours for each vertex.

## 样例 #1

### 输入

```
4
1 2 3 4
1 2
2 3
2 4

```

### 输出

```
10 9 3 4

```

## 样例 #2

### 输入

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13

```

### 输出

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3

```



---

---
title: "Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths"
layout: "post"
diff: 省选/NOI-
pid: CF741D
tag: ['树上启发式合并']
---

# Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths

## 题目描述

Just in case somebody missed it: we have wonderful girls in Arpa’s land.

Arpa has a rooted tree (connected acyclic graph) consisting of $ n $ vertices. The vertices are numbered $ 1 $ through $ n $ , the vertex $ 1 $ is the root. There is a letter written on each edge of this tree. Mehrdad is a fan of Dokhtar-kosh things. He call a string Dokhtar-kosh, if we can shuffle the characters in string such that it becomes palindrome.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF741D/ae6eaea25c446dd1a9c02c7621129601f3a81ec1.png)He asks Arpa, for each vertex $ v $ , what is the length of the longest simple path in subtree of $ v $ that form a Dokhtar-kosh string.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the number of vertices in the tree.

 $ (n-1) $ lines follow, the $ i $ -th of them contain an integer $ p_{i+1} $ and a letter $ c_{i+1} $ ( $ 1<=p_{i+1}<=i $ , $ c_{i+1} $ is lowercase English letter, between a and v, inclusively), that mean that there is an edge between nodes $ p_{i+1} $ and $ i+1 $ and there is a letter $ c_{i+1} $ written on this edge.

## 输出格式

Print $ n $ integers. The $ i $ -th of them should be the length of the longest simple path in subtree of the $ i $ -th vertex that form a Dokhtar-kosh string.

## 样例 #1

### 输入

```
4
1 s
2 a
3 s

```

### 输出

```
3 1 1 0 
```

## 样例 #2

### 输入

```
5
1 a
2 h
1 a
4 h

```

### 输出

```
4 1 0 1 0 
```



---

