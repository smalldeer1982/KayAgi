---
title: "Sonya and Bitwise OR"
layout: "post"
diff: 省选/NOI-
pid: CF1004F
tag: ['线段树']
---

# Sonya and Bitwise OR

## 题目描述

Sonya has an array $ a_1, a_2, \ldots, a_n $ consisting of $ n $ integers and also one non-negative integer $ x $ . She has to perform $ m $ queries of two types:

- $ 1 $ $ i $ $ y $ : replace $ i $ -th element by value $ y $ , i.e. to perform an operation $ a_{i} $ := $ y $ ;
- $ 2 $ $ l $ $ r $ : find the number of pairs ( $ L $ , $ R $ ) that $ l\leq L\leq R\leq r $ and bitwise OR of all integers in the range $ [L, R] $ is at least $ x $ (note that $ x $ is a constant for all queries).

Can you help Sonya perform all her queries?

Bitwise OR is a binary operation on a pair of non-negative integers. To calculate the bitwise OR of two numbers, you need to write both numbers in binary notation. The result is a number, in binary, which contains a one in each digit if there is a one in the binary notation of at least one of the two numbers. For example, $ 10 $ OR $ 19 $ = $ 1010_2 $ OR $ 10011_2 $ = $ 11011_2 $ = $ 27 $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ x $ ( $ 1\leq n, m\leq 10^5 $ , $ 0\leq x<2^{20} $ ) — the number of numbers, the number of queries, and the constant for all queries.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0\leq a_i<2^{20} $ ) — numbers of the array.

The following $ m $ lines each describe an query. A line has one of the following formats:

- $ 1 $ $ i $ $ y $ ( $ 1\leq i\leq n $ , $ 0\leq y<2^{20} $ ), meaning that you have to replace $ a_{i} $ by $ y $ ;
- $ 2 $ $ l $ $ r $ ( $ 1\leq l\leq r\leq n $ ), meaning that you have to find the number of subarrays on the segment from $ l $ to $ r $ that the bitwise OR of all numbers there is at least $ x $ .

## 输出格式

For each query of type 2, print the number of subarrays such that the bitwise OR of all the numbers in the range is at least $ x $ .

## 说明/提示

In the first example, there are an array \[ $ 0 $ , $ 3 $ , $ 6 $ , $ 1 $ \] and queries:

1. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
2. on the segment \[ $ 3\ldots4 $ \], you can choose pair ( $ 3 $ , $ 4 $ );
3. the first number is being replacing by $ 7 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 6 $ , $ 1 $ \];
4. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
5. on the segment \[ $ 1\ldots3 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 2 $ , $ 3 $ );
6. on the segment \[ $ 1\ldots1 $ \], you can choose pair ( $ 1 $ , $ 1 $ );
7. the third number is being replacing by $ 0 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 0 $ , $ 1 $ \];
8. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 1 $ , $ 4 $ ).

In the second example, there are an array \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 15 $ , $ 2 $ \] are queries:

1. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), ( $ 3 $ , $ 5 $ ), ( $ 4 $ , $ 4 $ ), and ( $ 4 $ , $ 5 $ );
2. the fourth number is being replacing by $ 4 $ , after this operation, the array will consist of \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 4 $ , $ 2 $ \];
3. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), and ( $ 3 $ , $ 5 $ );
4. on the segment \[ $ 3\ldots5 $ \], you can choose pairs ( $ 3 $ , $ 4 $ ) and ( $ 3 $ , $ 5 $ );
5. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ ).

## 样例 #1

### 输入

```
4 8 7
0 3 6 1
2 1 4
2 3 4
1 1 7
2 1 4
2 1 3
2 1 1
1 3 0
2 1 4

```

### 输出

```
5
1
7
4
1
4

```

## 样例 #2

### 输入

```
5 5 7
6 0 3 15 2
2 1 5
1 4 4
2 1 5
2 3 5
2 1 4

```

### 输出

```
9
7
2
4

```



---

---
title: "AI robots"
layout: "post"
diff: 省选/NOI-
pid: CF1045G
tag: ['线段树', '树套树', '概率论']
---

# AI robots

## 题目描述

In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

 Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

## 输入格式

The first line contains two integers, numbers $ N (1 \leq N \leq 10^5)  $ and $ K (0 \leq K \leq 20) $ .

Next $ N $ lines contain three numbers each $ x_i, r_i, q_i (0 \leq x_i,r_i,q_i \leq 10^9) $ — position, radius of sight and IQ of every robot respectively.

## 输出格式

Output contains only one number — solution to the problem.

## 说明/提示

The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.

## 样例 #1

### 输入

```
3 2
3 6 1
7 3 10
10 5 8

```

### 输出

```
1
```



---

---
title: "Tree or not Tree"
layout: "post"
diff: 省选/NOI-
pid: CF117E
tag: ['线段树', '树链剖分']
---

# Tree or not Tree

## 题目描述

You are given an undirected connected graph $ G $ consisting of $ n $ vertexes and $ n $ edges. $ G $ contains no self-loops or multiple edges. Let each edge has two states: on and off. Initially all edges are switched off.

You are also given $ m $ queries represented as $ (v,u) $ — change the state of all edges on the shortest path from vertex $ v $ to vertex $ u $ in graph $ G $ . If there are several such paths, the lexicographically minimal one is chosen. More formally, let us consider all shortest paths from vertex $ v $ to vertex $ u $ as the sequences of vertexes $ v,v_{1},v_{2},...,u $ . Among such sequences we choose the lexicographically minimal one.

After each query you should tell how many connected components has the graph whose vertexes coincide with the vertexes of graph $ G $ and edges coincide with the switched on edges of graph $ G $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 3<=n<=10^{5} $ , $ 1<=m<=10^{5} $ ). Then $ n $ lines describe the graph edges as $ a $ $ b $ ( $ 1<=a,b<=n $ ). Next $ m $ lines contain the queries as $ v $ $ u $ ( $ 1<=v,u<=n $ ).

It is guaranteed that the graph is connected, does not have any self-loops or multiple edges.

## 输出格式

Print $ m $ lines, each containing one integer — the query results.

## 说明/提示

Let's consider the first sample. We'll highlight the switched on edges blue on the image.

- The graph before applying any operations. No graph edges are switched on, that's why there initially are 5 connected components.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/6d848190f5d9993cf6ddd5c1e2cd0e57d9ae6288.png)
- The graph after query $ v=5,u=4 $ . We can see that the graph has three components if we only consider the switched on edges.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/2f3ad3d35eecb878e654ed5cd572ed4f02ecf9ff.png)
- The graph after query $ v=1,u=5 $ . We can see that the graph has three components if we only consider the switched on edges.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/31e75e1c5e9c21b4cec0bc2e71e38cbba47e290d.png)

Lexicographical comparison of two sequences of equal length of $ k $ numbers should be done as follows. Sequence $ x $ is lexicographically less than sequence $ y $ if exists such $ i $ ( $ 1<=i<=k $ ), so that $ x_{i}<y_{i} $ , and for any $ j $ ( $ 1<=j<i $ ) $ x_{j}=y_{j} $ .

## 样例 #1

### 输入

```
5 2
2 1
4 3
2 4
2 5
4 1
5 4
1 5

```

### 输出

```
3
3

```

## 样例 #2

### 输入

```
6 2
4 6
4 3
1 2
6 5
1 5
1 4
2 5
2 6

```

### 输出

```
4
3

```



---

---
title: "String"
layout: "post"
diff: 省选/NOI-
pid: CF123D
tag: ['线段树', '排序', '后缀数组 SA']
---

# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 输入格式

The only line contains the given string $ s $ , consisting only of small Latin letters ( $ 1<=|s|<=10^{5} $ ).

## 输出格式

Print the single number — the sought sum.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa

```

### 输出

```
20

```

## 样例 #2

### 输入

```
abcdef

```

### 输出

```
21

```

## 样例 #3

### 输入

```
abacabadabacaba

```

### 输出

```
188

```



---

---
title: "Cartesian Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1290E
tag: ['线段树']
---

# Cartesian Tree

## 题目描述

Ildar is the algorithm teacher of William and Harris. Today, Ildar is teaching Cartesian Tree. However, Harris is sick, so Ildar is only teaching William.

A cartesian tree is a rooted tree, that can be constructed from a sequence of distinct integers. We build the cartesian tree as follows:

1. If the sequence is empty, return an empty tree;
2. Let the position of the maximum element be $ x $ ;
3. Remove element on the position $ x $ from the sequence and break it into the left part and the right part (which might be empty) (not actually removing it, just taking it away temporarily);
4. Build cartesian tree for each part;
5. Create a new vertex for the element, that was on the position $ x $ which will serve as the root of the new tree. Then, for the root of the left part and right part, if exists, will become the children for this vertex;
6. Return the tree we have gotten.

For example, this is the cartesian tree for the sequence $ 4, 2, 7, 3, 5, 6, 1 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/acc7800e10b8c919d4950616a18f2140e891d16a.png)After teaching what the cartesian tree is, Ildar has assigned homework. He starts with an empty sequence $ a $ .

In the $ i $ -th round, he inserts an element with value $ i $ somewhere in $ a $ . Then, he asks a question: what is the sum of the sizes of the subtrees for every node in the cartesian tree for the current sequence $ a $ ?

Node $ v $ is in the node $ u $ subtree if and only if $ v = u $ or $ v $ is in the subtree of one of the vertex $ u $ children. The size of the subtree of node $ u $ is the number of nodes $ v $ such that $ v $ is in the subtree of $ u $ .

Ildar will do $ n $ rounds in total. The homework is the sequence of answers to the $ n $ questions.

The next day, Ildar told Harris that he has to complete the homework as well. Harris obtained the final state of the sequence $ a $ from William. However, he has no idea how to find the answers to the $ n $ questions. Help Harris!

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 150000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ). It is guarenteed that each integer from $ 1 $ to $ n $ appears in the sequence exactly once.

## 输出格式

Print $ n $ lines, $ i $ -th line should contain a single integer — the answer to the $ i $ -th question.

## 说明/提示

After the first round, the sequence is $ 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/b1534ebc83eb23d6f6505c6a2ab3b3a8035f9fce.png)The answer is $ 1 $ .

After the second round, the sequence is $ 2, 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/eff7476771d279f495520b7bd67cd481bc4c7064.png)The answer is $ 2+1=3 $ .

After the third round, the sequence is $ 2, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/c77bba87ff3ea714273a2609c35f8c7ab239c7fd.png)The answer is $ 2+1+3=6 $ .

After the fourth round, the sequence is $ 2, 4, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/dbef4f1eef8c88dd3dafdd5976421a830b9d116e.png)The answer is $ 1+4+1+2=8 $ .

After the fifth round, the sequence is $ 2, 4, 1, 5, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/044610082349c82baf738e950f52290ea3f1ea74.png)The answer is $ 1+3+1+5+1=11 $ .

## 样例 #1

### 输入

```
5
2 4 1 5 3
```

### 输出

```
1
3
6
8
11
```

## 样例 #2

### 输入

```
6
1 2 4 5 6 3
```

### 输出

```
1
3
6
8
12
17
```



---

---
title: "Complicated Computations"
layout: "post"
diff: 省选/NOI-
pid: CF1436E
tag: ['莫队', '线段树']
---

# Complicated Computations

## 题目描述

In this problem MEX of a certain array is the smallest positive integer not contained in this array.

Everyone knows this definition, including Lesha. But Lesha loves MEX, so he comes up with a new problem involving MEX every day, including today.

You are given an array $ a $ of length $ n $ . Lesha considers all the non-empty subarrays of the initial array and computes MEX for each of them. Then Lesha computes MEX of the obtained numbers.

An array $ b $ is a subarray of an array $ a $ , if $ b $ can be obtained from $ a $ by deletion of several (possible none or all) elements from the beginning and several (possibly none or all) elements from the end. In particular, an array is a subarray of itself.

Lesha understands that the problem is very interesting this time, but he doesn't know how to solve it. Help him and find the MEX of MEXes of all the subarrays!

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array.

## 输出格式

Print a single integer — the MEX of MEXes of all subarrays.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 4 3 1 2
```

### 输出

```
6
```



---

---
title: "Top-Notch Insertions"
layout: "post"
diff: 省选/NOI-
pid: CF1558D
tag: ['线段树', '二分', '平衡树', '组合数学']
---

# Top-Notch Insertions

## 题目描述

Consider the insertion sort algorithm used to sort an integer sequence $ [a_1, a_2, \ldots, a_n] $ of length $ n $ in non-decreasing order.

For each $ i $ in order from $ 2 $ to $ n $ , do the following. If $ a_i \ge a_{i-1} $ , do nothing and move on to the next value of $ i $ . Otherwise, find the smallest $ j $ such that $ a_i < a_j $ , shift the elements on positions from $ j $ to $ i-1 $ by one position to the right, and write down the initial value of $ a_i $ to position $ j $ . In this case we'll say that we performed an insertion of an element from position $ i $ to position $ j $ .

It can be noticed that after processing any $ i $ , the prefix of the sequence $ [a_1, a_2, \ldots, a_i] $ is sorted in non-decreasing order, therefore, the algorithm indeed sorts any sequence.

For example, sorting $ [4, 5, 3, 1, 3] $ proceeds as follows:

- $ i = 2 $ : $ a_2 \ge a_1 $ , do nothing;
- $ i = 3 $ : $ j = 1 $ , insert from position $ 3 $ to position $ 1 $ : $ [3, 4, 5, 1, 3] $ ;
- $ i = 4 $ : $ j = 1 $ , insert from position $ 4 $ to position $ 1 $ : $ [1, 3, 4, 5, 3] $ ;
- $ i = 5 $ : $ j = 3 $ , insert from position $ 5 $ to position $ 3 $ : $ [1, 3, 3, 4, 5] $ .

You are given an integer $ n $ and a list of $ m $ integer pairs $ (x_i, y_i) $ . We are interested in sequences such that if you sort them using the above algorithm, exactly $ m $ insertions will be performed: first from position $ x_1 $ to position $ y_1 $ , then from position $ x_2 $ to position $ y_2 $ , ..., finally, from position $ x_m $ to position $ y_m $ .

How many sequences of length $ n $ consisting of (not necessarily distinct) integers between $ 1 $ and $ n $ , inclusive, satisfy the above condition? Print this number modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m < n $ ) — the length of the sequence and the number of insertions.

The $ i $ -th of the following $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 2 \le x_1 < x_2 < \ldots < x_m \le n $ ; $ 1 \le y_i < x_i $ ). These lines describe the sequence of insertions in chronological order.

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Note that there is no constraint on the sum of $ n $ of the same kind.

## 输出格式

For each test case, print the number of sequences of length $ n $ consisting of integers from $ 1 $ to $ n $ such that sorting them with the described algorithm produces the given sequence of insertions, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the algorithm performs no insertions — therefore, the initial sequence is already sorted in non-decreasing order. There are $ 10 $ such sequences: $ [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 2, 3], [1, 3, 3], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3] $ .

In the second test case, the only sequence satisfying the conditions is $ [3, 2, 1] $ .

In the third test case, $ [4, 5, 3, 1, 3] $ is one of the sought sequences.

## 样例 #1

### 输入

```
3
3 0
3 2
2 1
3 1
5 3
3 1
4 1
5 3
```

### 输出

```
10
1
21
```



---

---
title: "Edges in MST"
layout: "post"
diff: 省选/NOI-
pid: CF160D
tag: ['线段树', '并查集', '生成树', '连通块']
---

# Edges in MST

## 题目描述

You are given a connected weighted undirected graph without any loops and multiple edges.

Let us remind you that a graph's spanning tree is defined as an acyclic connected subgraph of the given graph that includes all of the graph's vertexes. The weight of a tree is defined as the sum of weights of the edges that the given tree contains. The minimum spanning tree (MST) of a graph is defined as the graph's spanning tree having the minimum possible weight. For any connected graph obviously exists the minimum spanning tree, but in the general case, a graph's minimum spanning tree is not unique.

Your task is to determine the following for each edge of the given graph: whether it is either included in any MST, or included at least in one MST, or not included in any MST.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF160D/1841eb9adb257200301ec3daad18abd00c456982.png)) — the number of the graph's vertexes and edges, correspondingly. Then follow $ m $ lines, each of them contains three integers — the description of the graph's edges as " $ a_{i} $ $ b_{i} $ $ w_{i} $ " ( $ 1<=a_{i},b_{i}<=n,1<=w_{i}<=10^{6},a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the numbers of vertexes connected by the $ i $ -th edge, $ w_{i} $ is the edge's weight. It is guaranteed that the graph is connected and doesn't contain loops or multiple edges.

## 输出格式

Print $ m $ lines — the answers for all edges. If the $ i $ -th edge is included in any MST, print "any"; if the $ i $ -th edge is included at least in one MST, print "at least one"; if the $ i $ -th edge isn't included in any MST, print "none". Print the answers for the edges in the order in which the edges are specified in the input.

## 说明/提示

In the second sample the MST is unique for the given graph: it contains two first edges.

In the third sample any two edges form the MST for the given graph. That means that each edge is included at least in one MST.

## 样例 #1

### 输入

```
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

```

### 输出

```
none
any
at least one
at least one
any

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 2

```

### 输出

```
any
any
none

```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 1
1 3 1

```

### 输出

```
at least one
at least one
at least one

```



---

---
title: "e-Government"
layout: "post"
diff: 省选/NOI-
pid: CF163E
tag: ['字符串', '线段树', 'AC 自动机']
---

# e-Government

## 题目描述

The best programmers of Embezzland compete to develop a part of the project called "e-Government" — the system of automated statistic collecting and press analysis.

We know that any of the $ k $ citizens can become a member of the Embezzland government. The citizens' surnames are $ a_{1},a_{2},...,a_{k} $ . All surnames are different. Initially all $ k $ citizens from this list are members of the government. The system should support the following options:

- Include citizen $ a_{i} $ to the government.
- Exclude citizen $ a_{i} $ from the government.
- Given a newspaper article text, calculate how politicized it is. To do this, for every active government member the system counts the number of times his surname occurs in the text as a substring. All occurrences are taken into consideration, including the intersecting ones. The degree of politicization of a text is defined as the sum of these values for all active government members.

Implement this system.

## 输入格式

The first line contains space-separated integers $ n $ and $ k $ ( $ 1<=n,k<=10^{5} $ ) — the number of queries to the system and the number of potential government members.

Next $ k $ lines contain the surnames $ a_{1},a_{2},...,a_{k} $ , one per line. All surnames are pairwise different.

Next $ n $ lines contain queries to the system, one per line. Each query consists of a character that determines an operation and the operation argument, written consecutively without a space.

Operation "include in the government" corresponds to the character "+", operation "exclude" corresponds to "-". An argument of those operations is an integer between $ 1 $ and $ k $ — the index of the citizen involved in the operation. Any citizen can be included and excluded from the government an arbitrary number of times in any order. Including in the government a citizen who is already there or excluding the citizen who isn't there changes nothing.

The operation "calculate politicization" corresponds to character "?". Its argument is a text.

All strings — surnames and texts — are non-empty sequences of lowercase Latin letters. The total length of all surnames doesn't exceed $ 10^{6} $ , the total length of all texts doesn't exceed $ 10^{6} $ .

## 输出格式

For any "calculate politicization" operation print on a separate line the degree of the politicization of the given text. Print nothing for other operations.

## 样例 #1

### 输入

```
7 3
a
aa
ab
?aaab
-2
?aaab
-3
?aaab
+2
?aabbaa

```

### 输出

```
6
4
3
6

```



---

---
title: "Serious Business"
layout: "post"
diff: 省选/NOI-
pid: CF1648D
tag: ['动态规划 DP', '线段树', '动态规划优化']
---

# Serious Business

## 题目描述

Dima is taking part in a show organized by his friend Peter. In this show Dima is required to cross a $ 3 \times n $ rectangular field. Rows are numbered from $ 1 $ to $ 3 $ and columns are numbered from $ 1 $ to $ n $ .

The cell in the intersection of the $ i $ -th row and the $ j $ -th column of the field contains an integer $ a_{i,j} $ . Initially Dima's score equals zero, and whenever Dima reaches a cell in the row $ i $ and the column $ j $ , his score changes by $ a_{i,j} $ . Note that the score can become negative.

Initially all cells in the first and the third row are marked as available, and all cells in the second row are marked as unavailable. However, Peter offered Dima some help: there are $ q $ special offers in the show, the $ i $ -th special offer allows Dima to mark cells in the second row between $ l_i $ and $ r_i $ as available, though Dima's score reduces by $ k_i $ whenever he accepts a special offer. Dima is allowed to use as many special offers as he wants, and might mark the same cell as available multiple times.

Dima starts his journey in the cell $ (1, 1) $ and would like to reach the cell $ (3, n) $ . He can move either down to the next row or right to the next column (meaning he could increase the current row or column by 1), thus making $ n + 1 $ moves in total, out of which exactly $ n - 1 $ would be horizontal and $ 2 $ would be vertical.

Peter promised Dima to pay him based on his final score, so the sum of all numbers of all visited cells minus the cost of all special offers used. Please help Dima to maximize his final score.

## 输入格式

The first input line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 500\,000 $ ) — the number of columns in the field and the number of special offers.

The next three lines describe the field, $ i $ -th of them contains $ n $ integers $ a_{i1} $ , $ a_{i2} $ , ..., $ a_{in} $ ( $ -10^9 \le a_{ij} \le 10^9) $ — the values in the $ i $ -th row.

The next $ q $ lines describe special offers: the $ i $ -th offer is described by 3 integers $ l_i $ , $ r_i $ and $ k_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1\leq k_i\leq 10^9 $ ) — the segment that becomes unblocked and the cost of this special offer.

## 输出格式

Output one integer — the maximum final score Dima can achieve.

## 说明/提示

In the first example, it is optimal to use Peter's second offer of $ 4 $ rubles and go through the cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ , $ (3, 4) $ , earning $ 1 + 0 + 2 + 9 + 4 + 1 - 4 = 13 $ rubles in total.

In the second example, it is optimal to use Peter's second and third offers of $ 2 $ and $ 3 $ rubles, respectively, and go through the cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , earning $ -20 + 1 + 3 + 3 + 6 + 6 + 2 - 2 - 3= -4 $ rubles.

## 样例 #1

### 输入

```
4 3
1 0 2 -1
-3 1 9 2
3 2 4 1
1 2 5
2 3 4
1 4 14
```

### 输出

```
13
```

## 样例 #2

### 输入

```
5 4
-20 -10 -11 -10 1
1 3 3 6 3
14 -20 3 6 2
1 5 13
1 2 2
3 5 3
2 3 1
```

### 输出

```
-4
```



---

---
title: "Tower Defense"
layout: "post"
diff: 省选/NOI-
pid: CF1651F
tag: ['线段树', '可持久化线段树', '分块']
---

# Tower Defense

## 题目描述

Monocarp is playing a tower defense game. A level in the game can be represented as an OX axis, where each lattice point from $ 1 $ to $ n $ contains a tower in it.

The tower in the $ i $ -th point has $ c_i $ mana capacity and $ r_i $ mana regeneration rate. In the beginning, before the $ 0 $ -th second, each tower has full mana. If, at the end of some second, the $ i $ -th tower has $ x $ mana, then it becomes $ \mathit{min}(x + r_i, c_i) $ mana for the next second.

There are $ q $ monsters spawning on a level. The $ j $ -th monster spawns at point $ 1 $ at the beginning of $ t_j $ -th second, and it has $ h_j $ health. Every monster is moving $ 1 $ point per second in the direction of increasing coordinate.

When a monster passes the tower, the tower deals $ \mathit{min}(H, M) $ damage to it, where $ H $ is the current health of the monster and $ M $ is the current mana amount of the tower. This amount gets subtracted from both monster's health and tower's mana.

Unfortunately, sometimes some monsters can pass all $ n $ towers and remain alive. Monocarp wants to know what will be the total health of the monsters after they pass all towers.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of towers.

The $ i $ -th of the next $ n $ lines contains two integers $ c_i $ and $ r_i $ ( $ 1 \le r_i \le c_i \le 10^9 $ ) — the mana capacity and the mana regeneration rate of the $ i $ -th tower.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of monsters.

The $ j $ -th of the next $ q $ lines contains two integers $ t_j $ and $ h_j $ ( $ 0 \le t_j \le 2 \cdot 10^5 $ ; $ 1 \le h_j \le 10^{12} $ ) — the time the $ j $ -th monster spawns and its health.

The monsters are listed in the increasing order of their spawn time, so $ t_j < t_{j+1} $ for all $ 1 \le j \le q-1 $ .

## 输出格式

Print a single integer — the total health of all monsters after they pass all towers.

## 样例 #1

### 输入

```
3
5 1
7 4
4 2
4
0 14
1 10
3 16
10 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
2 1
4 1
5 4
7 5
8 3
9
1 21
2 18
3 14
4 24
5 8
6 25
7 19
8 24
9 24
```

### 输出

```
40
```



---

---
title: "Diverse Segments"
layout: "post"
diff: 省选/NOI-
pid: CF1684F
tag: ['线段树', '树状数组']
---

# Diverse Segments

## 题目描述

给定长度为 $n$ 的序列 $a$，以及 $m$ 个数对 $(l_i,r_i)$。  
你可以进行下列操作至多一次：

- 选择序列 $a$ 的一个子段，并将其中的每个元素的值都改成任意整数。

你需要保证执行完操作之后，对于每个整数 $i(1\leq i\leq m)$，都有 $a[l_i,r_i]$ 中所有元素互不相同。  
你需要最小化操作时选择的子段的长度，并求出这个长度的最小值。  
特别的如果没有必要进行操作，答案为 $0$。

## 输入格式

第一行输入一个整数 $t(1\leq t\leq100)$ 表示数据组数，接下来对于每组数据：  
第一行输入两个整数 $n,m(1\leq n,m,\sum n,\sum m\leq2\times10^5)$ 表示序列长度和给定的数对数。  
接下来一行输入 $n$ 个整数表示 $a_1,a_2,\cdots,a_n(1\leq a_i\leq10^9)$。  
接下来输入 $m$ 行，其中第 $i$ 行输入两个整数表示 $l_i,r_i(1\leq l_i\leq r_i\leq n)$。

## 输出格式

对于每组数据：  
输出进行操作的子段的长度的最小值。

### 样例解释

对于第一组数据，我们可以选择子段 $[1,2]$ 并将序列改成 $[114,514,2,1,3,3,5]$，此时：

- 对于第一个数对 $(1,4)$，我们有 $a[1,4]=[114,514,2,1]$。
- 对于第二个数对 $(4,5)$，我们有 $a[4,5]=[1,3]$。  
- 对于第三个数对 $(2,4)$，我们有 $a[2,4]=[514,2,1]$。

显然每个数对都满足要求，且我们可以证明没有更优的答案，因此答案为 $2$。  
对于第二组数据，我们没有必要进行操作。  
对于第三组数据，我们可以选择子段 $[1,1]$ 并将序列改成 $[1,7,5,6]$。

## 样例 #1

### 输入

```
5
7 3
1 1 2 1 3 3 5
1 4
4 5
2 4
5 2
10 1 6 14 1
4 5
2 4
4 5
5 7 5 6
2 2
1 3
2 4
3 3
3 4
7 3
2 2 2 7 8 2 2
4 4
4 4
5 5
1 1
123
1 1
```

### 输出

```
2
0
1
0
0
```



---

---
title: "LCM Sum (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1712E2
tag: ['线段树', '树状数组', '数论']
---

# LCM Sum (hard version)

## 题目描述

We are sum for we are many

Some Number



This version of the problem differs from the previous one only in the constraint on $ t $ . You can make hacks only if both versions of the problem are solved.

You are given two positive integers $ l $ and $ r $ .

Count the number of distinct triplets of integers $ (i, j, k) $ such that $ l \le i < j < k \le r $ and $ \operatorname{lcm}(i,j,k) \ge i + j + k $ .

Here $ \operatorname{lcm}(i, j, k) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ i $ , $ j $ , and $ k $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ \bf{1 \le t \le 10^5} $ ). Description of the test cases follows.

The only line for each test case contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 2 \cdot 10^5 $ , $ l + 2 \le r $ ).

## 输出格式

For each test case print one integer — the number of suitable triplets.

## 说明/提示

In the first test case, there are $ 3 $ suitable triplets:

- $ (1,2,3) $ ,
- $ (1,3,4) $ ,
- $ (2,3,4) $ .

In the second test case, there is $ 1 $ suitable triplet:

- $ (3,4,5) $ .

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868
```

### 输出

```
3
1
78975
969
109229059713337
```



---

---
title: "Swap and Maximum Block"
layout: "post"
diff: 省选/NOI-
pid: CF1716E
tag: ['线段树', '位运算']
---

# Swap and Maximum Block

## 题目描述

You are given an array of length $ 2^n $ . The elements of the array are numbered from $ 1 $ to $ 2^n $ .

You have to process $ q $ queries to this array. In the $ i $ -th query, you will be given an integer $ k $ ( $ 0 \le k \le n-1 $ ). To process the query, you should do the following:

- for every $ i \in [1, 2^n-2^k] $ in ascending order, do the following: if the $ i $ -th element was already swapped with some other element during this query, skip it; otherwise, swap $ a_i $ and $ a_{i+2^k} $ ;
- after that, print the maximum sum over all contiguous subsegments of the array (including the empty subsegment).

For example, if the array $ a $ is $ [-3, 5, -3, 2, 8, -20, 6, -1] $ , and $ k = 1 $ , the query is processed as follows:

- the $ 1 $ -st element wasn't swapped yet, so we swap it with the $ 3 $ -rd element;
- the $ 2 $ -nd element wasn't swapped yet, so we swap it with the $ 4 $ -th element;
- the $ 3 $ -rd element was swapped already;
- the $ 4 $ -th element was swapped already;
- the $ 5 $ -th element wasn't swapped yet, so we swap it with the $ 7 $ -th element;
- the $ 6 $ -th element wasn't swapped yet, so we swap it with the $ 8 $ -th element.

So, the array becomes $ [-3, 2, -3, 5, 6, -1, 8, -20] $ . The subsegment with the maximum sum is $ [5, 6, -1, 8] $ , and the answer to the query is $ 18 $ .

Note that the queries actually change the array, i. e. after a query is performed, the array does not return to its original state, and the next query will be applied to the modified array.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 18 $ ).

The second line contains $ 2^n $ integers $ a_1, a_2, \dots, a_{2^n} $ ( $ -10^9 \le a_i \le 10^9 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains one integer $ k $ ( $ 0 \le k \le n-1 $ ) describing the $ i $ -th query.

## 输出格式

For each query, print one integer — the maximum sum over all contiguous subsegments of the array (including the empty subsegment) after processing the query.

## 说明/提示

Transformation of the array in the example: $ [-3, 5, -3, 2, 8, -20, 6, -1] \rightarrow [-3, 2, -3, 5, 6, -1, 8, -20] \rightarrow [2, -3, 5, -3, -1, 6, -20, 8] \rightarrow [5, -3, 2, -3, -20, 8, -1, 6] $ .

## 样例 #1

### 输入

```
3
-3 5 -3 2 8 -20 6 -1
3
1
0
1
```

### 输出

```
18
8
13
```



---

---
title: "M-tree"
layout: "post"
diff: 省选/NOI-
pid: CF1810F
tag: ['数学', '线段树']
---

# M-tree

## 题目描述

A rooted tree is called good if every vertex of the tree either is a leaf (a vertex with no children) or has exactly $ m $ children.

For a good tree, each leaf $ u $ has a positive integer $ c_{u} $ written on it, and we define the value of the leaf as $ c_{u} + \mathrm{dep}_{u} $ , where $ \mathrm{dep}_{u} $ represents the number of edges of the path from vertex $ u $ to the root (also known as the depth of $ u $ ). The value of a good tree is the maximum value of all its leaves.

Now, you are given an array of $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ , which are the integers that should be written on the leaves. You need to construct a good tree with $ n $ leaves and write the integers from the array $ a $ to all the leaves. Formally, you should assign each leaf $ u $ an index $ b_{u} $ , where $ b $ is a permutation of length $ n $ , and represent that the integer written on leaf $ u $ is $ c_u = a_{b_{u}} $ . Under these constraints, you need to minimize the value of the good tree.

You have $ q $ queries. Each query gives you $ x $ , $ y $ and changes $ a_{x} $ to $ y $ , and after that, you should output the minimum value of a good tree based on the current array $ a $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Their description follows.

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 1\le n,q \le 2 \cdot 10^5 $ , $ 2\le m \le 2\cdot 10^5 $ , $ n \equiv 1 \pmod {m - 1} $ ) — the number of the leaves, the constant $ m $ , and the number of queries.

The second line contains $ n $ integers $ a_{1},a_{2}, \ldots, a_{n} $ ( $ 1 \le a_{i} \le n $ ) — the initial array.

For the following $ q $ lines, each line contains two integers $ x $ and $ y $ ( $ 1\le x,y\le n $ ), representing a query changing $ a_{x} $ to $ y $ .

It is guaranteed that both the sum of $ n $ and the sum of $ q $ do not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ q $ integers in one line, the $ i $ -th of which is the minimum tree value after the $ i $ -th change.

## 说明/提示

In the first test case, after the first query, the current array $ a $ is $ [4,3,4,4,5] $ . We can construct such a good tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1810F/88a3cbbc1b6fe16413368f21af94bcc26c8f2029.png)The first number inside a vertex is its index (in this problem, the indices do not matter, but help to understand the figure). If a vertex is a leaf, the second number inside the vertex is the integer written on it.

We can tell that $ \mathrm{dep}_{3}=\mathrm{dep}_{4}=1,\mathrm{dep}_{5}=\mathrm{dep}_{6}=\mathrm{dep}_{7}=2 $ and the value of the tree, which is the maximum value over all leaves, is $ 5+1=6 $ . The value of leaves $ 5 $ , $ 6 $ , $ 7 $ is also equal to $ 6 $ . It can be shown that this tree has the minimum value over all valid trees.

## 样例 #1

### 输入

```
3
5 3 3
3 3 4 4 5
1 4
2 4
3 5
5 2 4
3 3 4 4 5
1 4
2 5
3 5
4 5
7 3 4
1 2 2 3 3 3 4
1 4
2 1
5 5
6 6
```

### 输出

```
6 6 6
7 7 7 8
6 6 6 7
```



---

---
title: "Rollbacks (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1858E2
tag: ['可持久化线段树']
---

# Rollbacks (Hard Version)

## 题目描述

This is a hard version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

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

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query, so don't forget to flush output after printing answers. You can use functions like fflush(stdout) in C++ and BufferedWriter.flush in Java or similar after each writing in your program.

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
2. After the second query, $ a=[1, 1\,000\,000] $ .
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
title: "Babysitting"
layout: "post"
diff: 省选/NOI-
pid: CF1903F
tag: ['线段树', '2-SAT']
---

# Babysitting

## 题目描述

Theofanis wants to play video games, however he should also take care of his sister. Since Theofanis is a CS major, he found a way to do both. He will install some cameras in his house in order to make sure his sister is okay.

His house is an undirected graph with $ n $ nodes and $ m $ edges. His sister likes to play at the edges of the graph, so he has to install a camera to at least one endpoint of every edge of the graph. Theofanis wants to find a [vertex cover](https://en.wikipedia.org/wiki/Vertex_cover) that maximizes the minimum difference between indices of the chosen nodes.

More formally, let $ a_1, a_2, \ldots, a_k $ be a vertex cover of the graph. Let the minimum difference between indices of the chosen nodes be the minimum $ \lvert a_i - a_j \rvert $ (where $ i \neq j $ ) out of the nodes that you chose. If $ k = 1 $ then we assume that the minimum difference between indices of the chosen nodes is $ n $ .

Can you find the maximum possible minimum difference between indices of the chosen nodes over all vertex covers?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10^{5}, 1 \le m \le 2 \cdot 10^{5} $ ) — the number of nodes and the number of edges.

The $ i $ -th of the following $ m $ lines in the test case contains two positive integers $ u_i $ and $ v_i $ ( $ 1 \le u_i,v_i \le n $ ), meaning that there exists an edge between them in the graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^{5} $ .

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print the maximum minimum difference between indices of the chosen nodes over all vertex covers.

## 说明/提示

In the first test case, we can install cameras at nodes $ 1 $ , $ 3 $ , and $ 7 $ , so the answer is $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1903F/d75ed844401c37d1caa07fbd47253f2f681dd7c5.png)In the second test case, we can install only one camera at node $ 1 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
3
7 6
1 2
1 3
1 4
1 6
2 3
5 7
3 3
1 2
1 3
1 1
2 4
1 2
1 2
2 1
1 1
```

### 输出

```
2
3
2
```



---

---
title: "Tree Queries"
layout: "post"
diff: 省选/NOI-
pid: CF1904E
tag: ['线段树', '树的遍历']
---

# Tree Queries

## 题目描述

Those who don't work don't eat. Get the things you want with your own power. But believe, the earnest and serious people are the ones who have the last laugh... But even then, I won't give you a present.

—Santa, Hayate no Gotoku!



Since Hayate didn't get any Christmas presents from Santa, he is instead left solving a tree query problem.

Hayate has a tree with $ n $ nodes.

Hayate now wants you to answer $ q $ queries. Each query consists of a node $ x $ and $ k $ other additional nodes $ a_1,a_2,\ldots,a_k $ . These $ k+1 $ nodes are guaranteed to be all distinct.

For each query, you must find the length of the longest simple path starting at node $ x^\dagger $ after removing nodes $ a_1,a_2,\ldots,a_k $ along with all edges connected to at least one of nodes $ a_1,a_2,\ldots,a_k $ .

 $ ^\dagger $ A simple path of length $ k $ starting at node $ x $ is a sequence of distinct nodes $ x=u_0,u_1,\ldots,u_k $ such that there exists a edge between nodes $ u_{i-1} $ and $ u_i $ for all $ 1 \leq i \leq k $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of nodes of the tree and the number of queries.

The following $ n - 1 $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \ne v $ ) — denoting an edge between nodes $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The following $ q $ lines describe the queries. Each line contains the integers $ x $ , $ k $ and $ a_1,a_2,\ldots,a_k $ ( $ 1 \leq x \leq n $ , $ 0 \leq k < n $ , $ 1 \leq a_i \leq n $ ) — the starting node, the number of removed nodes and the removed nodes.

It is guaranteed that for each query, $ x,a_1,a_2,\ldots,a_k $ are all distinct.

It is guaranteed that the sum of $ k $ over all queries will not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output a single integer denoting the answer for that query.

## 说明/提示

In the first example, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1904E/c5f1379037fd66e966f2028dba5fe4bd6a86c16c.png)In the first query, no nodes are missing. The longest simple path starting from node $ 2 $ is $ 2 \to 1 \to 3 \to 4 $ . Thus, the answer is $ 3 $ .

In the third query, nodes $ 1 $ and $ 6 $ are missing and the tree is shown below. The longest simple path starting from node $ 2 $ is $ 2 \to 5 $ . Thus, the answer is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1904E/a4bba31c35c424ba9748f1f5381325841a00f680.png)

## 样例 #1

### 输入

```
7 7
1 2
1 3
3 4
2 5
2 6
6 7
2 0
2 1 1
2 2 1 6
3 1 4
3 1 1
5 0
5 2 1 6
```

### 输出

```
3
2
1
4
1
4
1
```

## 样例 #2

### 输入

```
4 4
1 2
1 3
2 4
2 1 3
3 1 4
2 1 4
2 3 1 3 4
```

### 输出

```
1
2
2
0
```



---

---
title: "Wine Factory (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1919F2
tag: ['线段树']
---

# Wine Factory (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

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

The fourth line contains $ n - 1 $ integers $ c_1, c_2, \ldots, c_{n - 1} $ ( $ 0 \le c_i \color{red}{\le} 10^{18} $ ) — the capacity of the pipe connecting water tower $ i $ to $ i + 1 $ .

Each of the next $ q $ lines contains four integers $ p $ , $ x $ , $ y $ and $ z $ ( $ 1 \le p \le n $ , $ 0 \le x, y \le 10^9 $ , $ 0 \le z \color{red}{\le} 10^{18} $ ) — the updates done to arrays $ a $ , $ b $ and $ c $ .

Note that $ c_n $ does not exist, so the value of $ z $ does not matter when $ p = n $ .

## 输出格式

Print $ q $ lines, each line containing a single integer representing $ W(a, b, c) $ after each update.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. Even though there are $ 2 $ liters of water remaining, only $ 1 $ liter of water can flow into tower 4.
- When $ i = 4 $ , there are $ 4 $ liters of water in tower 4. All $ 4 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 4 = 11 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [5, 1, 1] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. Even though there are $ 6 $ liters of water remaining, only $ 1 $ liter of water can flow to tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. Even though there are $ 2 $ liters of water remaining, only $ 1 $ liter of water can flow into tower 4.
- When $ i = 4 $ , there are $ 4 $ liters of water in tower 4. All $ 4 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 4 = 8 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [5, 1, 0] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. Even though there are $ 6 $ liters of water remaining, only $ 1 $ liter of water can flow to tower 3.
- When $ i = 3 $ , there is $ 1 $ liter of water in tower 3 and $ 0 $ liters of water is turned into wine. Even though there is $ 1 $ liter of water remaining, no water can flow to tower 4.
- When $ i = 4 $ , there are $ 3 $ liters of water in tower 4. All $ 3 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 3 = 5 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
5 2 1
4 3 8 1000000000
2 5 1 1
3 0 0 0
```

### 输出

```
11
8
5
```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
6 5 9 2
5 4 9 1
1 1 1 1
2 7 4 8
4 1 1 1
1 8 3 3
```

### 输出

```
31
25
29
21
23
```



---

---
title: "Digital Patterns"
layout: "post"
diff: 省选/NOI-
pid: CF1928F
tag: ['线段树']
---

# Digital Patterns

## 题目描述

Anya is engaged in needlework. Today she decided to knit a scarf from semi-transparent threads. Each thread is characterized by a single integer — the transparency coefficient.

The scarf is made according to the following scheme: horizontal threads with transparency coefficients $ a_1, a_2, \ldots, a_n $ and vertical threads with transparency coefficients $ b_1, b_2, \ldots, b_m $ are selected. Then they are interwoven as shown in the picture below, forming a piece of fabric of size $ n \times m $ , consisting of exactly $ nm $ nodes:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1928F/7b752ff6c6aa2dba727d3451b2fd110135821975.png) Example of a piece of fabric for $ n = m = 4 $ .After the interweaving tightens and there are no gaps between the threads, each node formed by a horizontal thread with number $ i $ and a vertical thread with number $ j $ will turn into a cell, which we will denote as $ (i, j) $ . Cell $ (i, j) $ will have a transparency coefficient of $ a_i + b_j $ .

The interestingness of the resulting scarf will be the number of its sub-squares $ ^{\dagger} $ in which there are no pairs of neighboring $ ^{\dagger \dagger} $ cells with the same transparency coefficients.

Anya has not yet decided which threads to use for the scarf, so you will also be given $ q $ queries to increase/decrease the coefficients for the threads on some ranges. After each query of which you need to output the interestingness of the resulting scarf.

 $ ^{\dagger} $ A sub-square of a piece of fabric is defined as the set of all its cells $ (i, j) $ , such that $ x_0 \le i \le x_0 + d $ and $ y_0 \le j \le y_0 + d $ for some integers $ x_0 $ , $ y_0 $ , and $ d $ ( $ 1 \le x_0 \le n - d $ , $ 1 \le y_0 \le m - d $ , $ d \ge 0 $ ).

 $ ^{\dagger \dagger} $ . Cells $ (i_1, j_1) $ and $ (i_2, j_2) $ are neighboring if and only if $ |i_1 - i_2| + |j_1 - j_2| = 1 $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ , $ 0 \le q \le 3 \cdot 10^5 $ ) — the number of horizontal threads, the number of vertical threads, and the number of change requests.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the transparency coefficients for the horizontal threads, with the threads numbered from top to bottom.

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ -10^9 \le b_i \le 10^9 $ ) — the transparency coefficients for the vertical threads, with the threads numbered from left to right.

The next $ q $ lines specify the change requests. Each request is described by a quadruple of integers $ t $ , $ l $ , $ r $ , and $ x $ ( $ 1 \le t \le 2 $ , $ l \le r $ , $ -10^9 \le x \le 10^9 $ ). Depending on the parameter $ t $ in the request, the following actions are required:

- $ t=1 $ . The transparency coefficients for the horizontal threads in the range $ [l, r] $ are increased by $ x $ (in other words, for all integers $ l \le i \le r $ , the value of $ a_i $ is increased by $ x $ );
- $ t=2 $ . The transparency coefficients for the vertical threads in the range $ [l, r] $ are increased by $ x $ (in other words, for all integers $ l \le i \le r $ , the value of $ b_i $ is increased by $ x $ ).

## 输出格式

Output $ (q+1) $ lines. In the $ (i + 1) $ -th line ( $ 0 \le i \le q $ ), output a single integer — the interestingness of the scarf after applying the first $ i $ requests.

## 说明/提示

In the first example, the transparency coefficients of the cells in the resulting plate are as follows:

 2334233434454556Then there are the following sub-squares that do not contain two neighboring cells with the same transparency coefficient:

- Each of the $ 16 $ cells separately;
- A sub-square with the upper left corner at cell $ (3, 1) $ and the lower right corner at cell $ (4, 2) $ ;
- A sub-square with the upper left corner at cell $ (2, 3) $ and the lower right corner at cell $ (3, 4) $ ;
- A sub-square with the upper left corner at cell $ (2, 1) $ and the lower right corner at cell $ (3, 2) $ ;
- A sub-square with the upper left corner at cell $ (3, 3) $ and the lower right corner at cell $ (4, 4) $ .

In the second example, after the first query, the transparency coefficients of the horizontal threads are $ [1, 2, 2] $ . After the second query, the transparency coefficients of the vertical threads are $ [2, -4, 2] $ .

## 样例 #1

### 输入

```
4 4 0
1 1 2 3
1 2 2 3
```

### 输出

```
20
```

## 样例 #2

### 输入

```
3 3 2
1 1 1
2 2 8
1 2 3 1
2 2 3 -6
```

### 输出

```
9
10
11
```

## 样例 #3

### 输入

```
3 2 2
-1000000000 0 1000000000
-1000000000 1000000000
1 1 1 1000000000
2 2 2 -1000000000
```

### 输出

```
8
7
7
```



---

---
title: "Frequency Mismatch (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1957F1
tag: ['线段树', '哈希 hashing']
---

# Frequency Mismatch (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of nodes in the tree.

The next line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ) — the value written on each node of the tree.

Then $ n - 1 $ lines follow. Each line contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n, u \neq v $ ) denoting an edge of the tree. It is guaranteed that the given edges form a tree.

The next line contains one integer $ q $ ( $ 1 \leq q \leq 10^5 $ ) — the number of queries.

Then $ q $ lines follow. Each line contains five integers $ u_1, v_1, u_2, v_2, k $ ( $ 1 \leq u_1, v_1, u_2, v_2 \leq n $ , $ k = 1 $ ).

## 输出格式

For each query, output on a separate line. For a query, first output $ \min(z, k) $ and then on the same line, output any $ \min(z, k) $ values in any order which occur a different number of times in each path.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print one of them.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
3
1 4 4 5 1
2 3 2 3 1
5 5 4 3 1
```

### 输出

```
1 5
0
1 2
```



---

---
title: "Frequency Mismatch (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1957F2
tag: ['线段树', '哈希 hashing']
---

# Frequency Mismatch (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of nodes in the tree.

The next line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ) — the value written on each node of the tree.

Then $ n - 1 $ lines follow. Each line contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n, u \neq v $ ) denoting an edge of the tree. It is guaranteed that the given edges form a tree.

The next line contains one integer $ q $ ( $ 1 \leq q \leq 10^5 $ ) — the number of queries.

Then $ q $ lines follow. Each line contains five integers $ u_1, v_1, u_2, v_2, k $ ( $ 1 \leq u_1, v_1, u_2, v_2 \leq n $ , $ 1 \leq k \leq 10 $ ).

## 输出格式

For each query, output on a separate line. For a query, first output $ \min(z, k) $ and then on the same line, output any $ \min(z, k) $ values in any order which occur a different number of times in each path.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print them both.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , we have the same paths as query $ 1 $ , but we need to output only $ 1 $ value, hence we output $ 5 $ .

In query $ 4 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
4
1 4 4 5 3
2 3 2 3 1
1 4 4 5 1
5 5 4 3 10
```

### 输出

```
2 3 5
0
1 5
3 5 2 4
```



---

---
title: "Sorting Problem Again"
layout: "post"
diff: 省选/NOI-
pid: CF1982F
tag: ['线段树', '二分']
---

# Sorting Problem Again

## 题目描述

已知一个序列，给定 $q$ 次修改。对于初始序列和每次修改后的序列，你需要做到：

找到长度最小的连续的子串，使得如果这个子串按升序排序，整个序列也就满足单调不降。输出这个子串的起始位置 $l, r$；若此时序列已经满足单调不降，认为 $l, r$ 均为 $-1$。

注意，对这个子串的“升序排序”只是一个假想出的操作，并不会改变原序列。

## 输入格式

**本题有多组数据**。

第一行输入一个正整数 $T$（$1 \leq T \leq 10$），表示测试数据的组数。对于每组数据：

第一行输入序列长度 $n$（$1 \leq n \leq 5 \cdot 10^5$）。

第二行输入 $n$ 个整数 $a_i$，即给定的序列（$0 \leq |a_i| \leq 10^9$）。

第三行输入修改操作的个数 $q$（$0 \leq q \leq 5 \cdot 10^5$）。

接下来 $q$ 行，每行输入两个整数 $p$ 和 $v$（$1 \leq p \leq n$ 且 $0 \leq |v| \leq 10^9$），表示 $a_p \gets v$。

保证 $\sum n, \sum p \leq 5 \cdot 10^5$。

## 输出格式

对于每组测试数据，输出 $q + 1$ 行。

每行输出两个整数 $l, r$，含义见题面。

## 说明/提示

对于第一个样例：

- 一开始，序列 $a$ 已经满足单调不降：$[2, 2, 3, 4, 5]$。
- 第一次修改后，序列 $a$ 长这样：$[\color{red}{2}, \color{red}{1}, \color{black}{3}, 4, 5]$。
- 第二次修改后，序列 $a$ 长这样：$[\color{red}{2}, \color{red}{1}, \color{red}{3}, \color{red}{1}, \color{black}{5}]$。
- 第三次修改后，序列 $a$ 长这样：$[1, 1, \color{red}{3}, \color{red}{1}, 5]$。

标红的部分即为题目所求。

## 样例 #1

### 输入

```
2
5
2 2 3 4 5
3
2 1
4 1
1 1
5
1 2 3 4 5
9
1 4
2 3
5 2
3 1
1 1
5 1
4 1
3 1
2 1
```

### 输出

```
-1 -1
1 2
1 4
3 4
-1 -1
1 3
1 3
1 5
1 5
2 5
2 5
2 5
2 5
-1 -1
```



---

---
title: "Let Me Teach You a Lesson (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1995E2
tag: ['线段树', '矩阵乘法']
---

# Let Me Teach You a Lesson (Hard Version)

## 题目描述

This is the hard version of a problem. The only difference between an easy and a hard version is the constraints on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

Arthur is giving a lesson to his famous $ 2 n $ knights. Like any other students, they're sitting at the desks in pairs, but out of habit in a circle. The knight $ 2 i - 1 $ is sitting at the desk with the knight $ 2 i $ .

Each knight has intelligence, which can be measured by an integer. Let's denote the intelligence of the $ i $ -th knight as $ a_i $ . Arthur wants the maximal difference in total intelligence over all pairs of desks to be as small as possible. More formally, he wants to minimize $ \max\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) - \min\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) $ .

However, the Code of Chivalry only allows swapping the opposite knights in the circle, i.e., Arthur can simultaneously perform $ a_i := a_{i + n} $ , $ a_{i + n} := a_i $ for any $ 1 \le i \le n $ . Arthur can make any number of such swaps. What is the best result he can achieve?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. It is followed by descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100\,000 $ ) — the number of desks.

The second line consists of $ 2n $ integers $ a_1, a_2, \ldots, a_{2 n} $ ( $ 1 \le a_i \le 10^9 $ ) — the intelligence values of the knights.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100\,000 $ .

## 输出格式

For each test case, output a single line containing one integer — the minimal difference Arthur can achieve.

## 说明/提示

In the first test case, Arthur can swap the second and the fourth knights. Then the total intelligence at both desks will be $ 10 $ .

In the third test case, Arthur can make $ 0 $ operations, which will result in the total intelligence of $ 11 $ at each of the desks.

In the fourth test case, Arthur can swap knights with indices $ 2 $ and $ 5 $ and achieve the difference of $ 2 $ . It can be proven that he cannot improve his result any further.

## 样例 #1

### 输入

```
5
2
6 6 4 4
1
10 17
3
1 10 1 10 1 10
3
3 3 4 5 5 4
5
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
0
0
0
2
4
```



---

---
title: "Points"
layout: "post"
diff: 省选/NOI-
pid: CF19D
tag: ['线段树', '递归', '离散化']
---

# Points

## 题目描述

Pete and Bob invented a new interesting game. Bob takes a sheet of paper and locates a Cartesian coordinate system on it as follows: point $ (0,0) $ is located in the bottom-left corner, $ Ox $ axis is directed right, $ Oy $ axis is directed up. Pete gives Bob requests of three types:

- add x y — on the sheet of paper Bob marks a point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is not yet marked on Bob's sheet at the time of the request.
- remove x y — on the sheet of paper Bob erases the previously marked point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is already marked on Bob's sheet at the time of the request.
- find x y — on the sheet of paper Bob finds all the marked points, lying strictly above and strictly to the right of point $ (x,y) $ . Among these points Bob chooses the leftmost one, if it is not unique, he chooses the bottommost one, and gives its coordinates to Pete.

Bob managed to answer the requests, when they were 10, 100 or 1000, but when their amount grew up to $ 2·10^{5} $ , Bob failed to cope. Now he needs a program that will answer all Pete's requests. Help Bob, please!

## 输入格式

The first input line contains number $ n $ ( $ 1<=n<=2·10^{5} $ ) — amount of requests. Then there follow $ n $ lines — descriptions of the requests. add x y describes the request to add a point, remove x y — the request to erase a point, find x y — the request to find the bottom-left point. All the coordinates in the input file are non-negative and don't exceed $ 10^{9} $ .

## 输出格式

For each request of type find x y output in a separate line the answer to it — coordinates of the bottommost among the leftmost marked points, lying strictly above and to the right of point $ (x,y) $ . If there are no points strictly above and to the right of point $ (x,y) $ , output -1.

## 样例 #1

### 输入

```
7
add 1 1
add 3 4
find 0 0
remove 1 1
find 0 0
add 1 1
find 0 0

```

### 输出

```
1 1
3 4
1 1

```

## 样例 #2

### 输入

```
13
add 5 5
add 5 6
add 5 7
add 6 5
add 6 6
add 6 7
add 7 5
add 7 6
add 7 7
find 6 6
remove 7 7
find 6 6
find 4 4

```

### 输出

```
7 7
-1
5 5

```



---

---
title: "Iris's Full Binary Tree"
layout: "post"
diff: 省选/NOI-
pid: CF2006E
tag: ['线段树', '树的遍历', '树的直径']
---

# Iris's Full Binary Tree

## 题目描述

Iris likes full binary trees.

Let's define the depth of a rooted tree as the maximum number of vertices on the simple paths from some vertex to the root. A full binary tree of depth $ d $ is a binary tree of depth $ d $ with exactly $ 2^d - 1 $ vertices.

Iris calls a tree a  $ d $ -binary tree if some vertices and edges can be added to it to make it a full binary tree of depth $ d $ . Note that any vertex can be chosen as the root of a full binary tree.

Since performing operations on large trees is difficult, she defines the binary depth of a tree as the minimum $ d $ satisfying that the tree is $ d $ -binary. Specifically, if there is no integer $ d \ge 1 $ such that the tree is $ d $ -binary, the binary depth of the tree is $ -1 $ .

Iris now has a tree consisting of only vertex $ 1 $ . She wants to add $ n - 1 $ more vertices to form a larger tree. She will add the vertices one by one. When she adds vertex $ i $ ( $ 2 \leq i \leq n $ ), she'll give you an integer $ p_i $ ( $ 1 \leq p_i < i $ ), and add a new edge connecting vertices $ i $ and $ p_i $ .

Iris wants to ask you the binary depth of the tree formed by the first $ i $ vertices for each $ 1 \le i \le n $ . Can you tell her the answer?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 5 \cdot 10^5 $ ) — the final size of the tree.

The second line of each test case contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \leq p_i < i $ ) — descriptions of all edges of the tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case output $ n $ integers, $ i $ -th of them representing the binary depth of the tree formed by the first $ i $ vertices.

## 说明/提示

In the first test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)- The tree consisting of the vertex $ 1 $ has the binary depth $ 1 $ (the tree itself is a full binary tree of depth $ 1 $ ).
- The tree consisting of the vertices $ 1 $ and $ 2 $ has the binary depth $ 2 $ (we can add the vertex $ 3 $ to make it a full binary tree of depth $ 2 $ ).
- The tree consisting of the vertices $ 1 $ , $ 2 $ and $ 3 $ has the binary depth $ 2 $ (the tree itself is a full binary tree of depth $ 2 $ ).

In the second test case, the formed full binary tree after adding some vertices to the tree consisting of $ n $ vertices is shown below (bolded vertices are added):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/90faca99e1781d73f69b5b60a32aa2a2da38a68c.png)The depth of the formed full binary tree is $ 4 $ .

In the fifth test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/2c0d039efae462812828b42368688f46ffc8b41e.png)It can be proved that Iris can't form any full binary tree by adding vertices and edges, so the binary depth is $ -1 $ .

## 样例 #1

### 输入

```
7
3
1 1
6
1 2 3 4 5
7
1 1 3 2 5 1
10
1 1 2 1 4 2 4 5 8
10
1 1 3 1 3 2 2 2 6
20
1 1 2 2 4 4 5 5 7 6 8 6 11 14 11 8 13 13 12
25
1 1 3 3 1 5 4 4 6 8 11 12 8 7 11 13 7 13 15 6 19 14 10 23
```

### 输出

```
1 2 2 
1 2 2 3 3 4 
1 2 2 3 3 4 4 
1 2 2 3 3 3 4 4 5 5 
1 2 2 3 3 4 4 4 -1 -1 
1 2 2 3 3 4 4 4 4 5 5 5 5 6 6 6 6 6 6 7 
1 2 2 3 3 4 4 4 4 5 5 6 6 6 6 6 7 7 7 7 7 8 8 8 8
```



---

---
title: "Yunli's Subarray Queries (extreme version)"
layout: "post"
diff: 省选/NOI-
pid: CF2009G3
tag: ['莫队', '线段树']
---

# Yunli's Subarray Queries (extreme version)

## 题目描述

这是问题的极限版本。在这个版本中，每个查询的输出与简单版和困难版不同。保证对于所有的查询都有 $ r \geq l+k-1 $。

对于一个任意数组 $ b $，云莉可以无数次进行以下操作：

- 选择一个下标 $ i $，将 $ b_i $ 设置为任意她想要的整数 $ x $（$ x $ 不限制在 $ [1, n] $ 区间内）。

定义 $ f(b) $ 为所需的最小操作次数，以使得 $ b $ 中存在一个长度至少为 $ k $ 的连续子数组。

云莉给出一个大小为 $ n $ 的数组 $ a $ 并询问你 $ q $ 次，你需要在每次查询中计算并输出 $\sum_{i=l}^{r-k+1} \sum_{j=i+k-1}^{r} f([a_i, a_{i+1}, \ldots, a_j])$。

如果数组中存在从下标 $ i $ 开始的长度为 $ k $ 的连续子数组（$ 1 \leq i \leq |b|-k+1 $），那么在该子数组中，对于 $ i < j \leq i+k-1 $，必须满足 $ b_j = b_{j-1} + 1 $。

## 输入格式

第一行输入 $ t $（$ 1 \leq t \leq 10^4 $）—— 表示测试用例的数量。

接下来的每个测试用例的第一行包含三个整数 $ n $、$ k $ 和 $ q $（$ 1 \leq k \leq n \leq 2 \cdot 10^5 $，$ 1 \leq q \leq 2 \cdot 10^5 $），分别表示数组的长度、连续子数组的长度和查询的次数。

接下来是一行，包含 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \leq a_i \leq n $）。

接下来的 $ q $ 行中，每行包含两个整数 $ l $ 和 $ r $（$ 1 \leq l \leq r \leq n $，$ r \geq l+k-1 $），表示查询的区间。

保证所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $，所有测试用例中 $ q $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个查询，输出一行结果，即 $\sum_{i=l}^{r-k+1} \sum_{j=i+k-1}^{r} f([a_i, a_{i+1}, \ldots, a_j])$。

## 说明/提示

在第一个测试用例的第一个查询中，我们可以通过如下方法来计算结果：

- 当 $ i = 4 $ 且 $ j = 5 $ 时，$ f([2, 1])=1 $，因为云莉可以将 $ b_2 $ 设为 3，从而一步操作后形成长度为 2 的连续子数组。
- 当 $ i = 4 $ 且 $ j = 6 $ 时，$ f([2, 1, 2])=0 $，因为已经存在长度为 2 的连续子数组。
- 当 $ i = 5 $ 且 $ j = 6 $ 时，$ f([1, 2])=0 $，因为已经存在长度为 2 的连续子数组。

此查询的答案为 $ 1+0+0=1 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
7 2 4
1 2 3 2 1 2 3
4 6
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
10 4 8
2 3 6 5 8 9 8 10 10 1
2 7
6 10
1 9
1 6
3 9
4 10
2 10
1 8
10 7 4
3 4 5 3 4 5 9 10 8 9
1 9
2 10
1 10
2 9
```

### 输出

```
1
3
3
3
2
7
2
4
8
6
28
7
16
20
32
19
18
15
26
9
```



---

---
title: "Graph Inclusion"
layout: "post"
diff: 省选/NOI-
pid: CF2069F
tag: ['线段树', '线段树分治']
---

# Graph Inclusion

## 题目描述

在无向图中，连通分量（connected component）定义为满足以下条件的顶点集合 $S$：
- 对于 $S$ 中的任意顶点对 $(u, v)$，存在从 $u$ 到 $v$ 的路径；
- 不存在属于 $S$ 外部的顶点与 $S$ 内部的顶点之间存在路径。

例如，下图中的图有三个连通分量：$\{1, 3, 7, 8\}$、$\{2\}$、$\{4, 5, 6\}$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2069F/c7da17be18c82b1f53abfd338e215a533856c956.png)

我们称图 $A$ 包含（include）图 $B$，当且仅当图 $B$ 的每个连通分量都是图 $A$ 某个连通分量的子集。

给定两个图 $A$ 和 $B$，它们均包含 $n$ 个顶点（编号为 $1$ 到 $n$）。初始时两个图都没有边。你需要处理以下两种类型的查询：
- 向其中一个图添加一条边；
- 从其中一个图中删除一条边。

在每次查询后，你需要计算为了使图 $A$ 包含图 $B$ 所需要向图 $A$ 添加的最小边数，并输出该数值。注意这些边不会被实际添加，仅需计算数量。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（$2 \le n \le 4 \cdot 10^5$；$1 \le q \le 4 \cdot 10^5$）——分别表示顶点数和查询数。

接下来 $q$ 行描述查询，其中第 $i$ 行描述第 $i$ 个查询。查询描述以一个字符 $c_i$（A 或 B）开头，表示该查询作用的图。接着是两个整数 $x_i$ 和 $y_i$（$1 \le x_i, y_i \le n$；$x_i \ne y_i$）。如果对应图中存在边 $(x_i, y_i)$，则删除该边；否则添加该边。

## 输出格式

对于每个查询，输出一个整数——为使图 $A$ 包含图 $B$ 所需向图 $A$ 添加的最小边数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 9
A 2 3
B 1 3
A 2 1
A 3 2
B 5 6
A 6 5
A 3 4
A 4 2
A 4 3
```

### 输出

```
0
1
0
1
2
1
1
0
1
```



---

---
title: "Towering Arrays"
layout: "post"
diff: 省选/NOI-
pid: CF2071F
tag: ['线段树', '二分']
---

# Towering Arrays

## 题目描述

称一个长度为 $m$ 的数组 $b = [b_1, b_2, \ldots, b_m]$ 为 $p$-towering，当且仅当存在一个下标 $i$（$1 \le i \le m$），使得对于所有下标 $j$（$1 \le j \le m$）满足以下条件：

$$b_j \ge p - |i - j|. $$

给定一个长度为 $n$ 的数组 $a = [a_1, a_2, \ldots, a_n]$，你可以删除最多 $k$ 个元素。求剩余数组能够构成 $p$-towering 的最大 $p$ 值。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$0 \le k < n \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——剩余数组能构成 $p$-towering 的最大 $p$ 值。

## 说明/提示

第一个测试用例中，无法删除任何元素。剩余数组为 $[2, 1, 4, {\color{red}{5}}, 2]$，当选择 $i = 4$ 时满足 $p = 3$：
- $a_1 = 2 \ge p - |i - 1| = 3 - |4 - 1| = 0$；
- $a_2 = 1 \ge p - |i - 2| = 3 - |4 - 2| = 1$；
- $a_3 = 4 \ge p - |i - 3| = 3 - |4 - 3| = 2$；
- $a_4 = 5 \ge p - |i - 4| = 3 - |4 - 4| = 3$；
- $a_5 = 2 \ge p - |i - 5| = 3 - |4 - 5| = 2$。

第二个测试用例中，可以删除第 1、2、5 个元素得到数组 $[4, \color{red}{5}]$。当选择 $i = 2$ 时，该数组满足 $p = 5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
5 0
2 1 4 5 2
5 3
2 1 4 5 2
6 1
1 2 3 4 5 1
11 6
6 3 8 5 8 3 2 1 2 7 1
14 3
3 2 3 5 5 2 6 7 4 8 10 1 8 9
2 0
1 1
```

### 输出

```
3
5
5
7
9
1
```



---

---
title: "Beautiful Sequence Returns"
layout: "post"
diff: 省选/NOI-
pid: CF2075F
tag: ['线段树']
---

# Beautiful Sequence Returns

## 题目描述

我们称一个整数序列为美丽的，当且仅当其满足以下条件：
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 2]$、$[42]$、$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（可能为零个）而不改变剩余元素顺序得到的新序列。

给定一个长度为 $n$ 的整数数组 $a$。请找出数组 $a$ 的最长美丽子序列，并输出其长度。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。接下来给出 $t$ 个独立测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5 \cdot 10^5$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^6$）——数组 $a$。

输入数据的额外约束：所有测试用例的 $n$ 之和不超过 $5 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个整数——数组 $a$ 的最长美丽子序列的长度。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1
42
5
1 2 3 4 5
6
6 5 4 3 2 1
7
1 1 3 4 2 3 4
6
2 3 1 1 2 4
```

### 输出

```
1
5
1
5
3
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
title: "Wonderful Impostors"
layout: "post"
diff: 省选/NOI-
pid: CF2096F
tag: ['线段树', '二分', '双指针 two-pointer']
---

# Wonderful Impostors

## 题目描述

你是一位名为 Gigi Murin 的骄傲主播。今天，你将与编号为 $1$ 到 $n$ 的 $n$ 名观众进行一场游戏。

在游戏中，每位玩家要么是船员，要么是冒名顶替者。你并不知道每位观众的角色。

共有 $m$ 条编号为 $1$ 到 $m$ 的陈述，每条陈述要么为真，要么为假。对于每条从 $1$ 到 $m$ 的 $i$，陈述 $i$ 属于以下两种类型之一：

- $0\:a_i\:b_i$（$1 \leq a_i \leq b_i \leq n$）——在观众 $a_i, a_i + 1, \ldots, b_i$ 中没有冒名顶替者；
- $1\:a_i\:b_i$（$1 \leq a_i \leq b_i \leq n$）——在观众 $a_i, a_i + 1, \ldots, b_i$ 中至少有一名冒名顶替者。

回答 $q$ 个以下形式的问题：

- $l\:r$（$1 \leq l \leq r \leq m$）——陈述 $l, l + 1, \ldots, r$ 是否可能全部为真？

注意，题目不保证所有观众中至少有一名冒名顶替者，也不保证所有观众中至少有一名船员。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \leq n, m \leq 2 \cdot 10^5$）——观众的数量和陈述的数量。

接下来的 $m$ 行中，第 $i$ 行包含三个整数 $x_i$、$a_i$ 和 $b_i$（$x_i \in \{0, 1\}$，$1 \leq a_i \leq b_i \leq n$）——描述第 $i$ 条陈述。

接下来一行包含一个整数 $q$（$1 \le q \le 2 \cdot 10^5$）——问题的数量。

接下来的 $q$ 行中，每行包含两个整数 $l$ 和 $r$（$1 \leq l \leq r \leq m$）——描述一个问题。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$，所有测试用例的 $m$ 之和不超过 $2 \cdot 10^5$，且所有测试用例的 $q$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个问题，如果请求的陈述可能全部为真，则输出 "YES"；否则输出 "NO"。

答案可以以任意大小写形式输出（例如，"yEs"、"yes"、"Yes" 和 "YES" 均被视为肯定回答）。


## 说明/提示

在第一个测试用例中，有 $4$ 名观众和 $3$ 条陈述。陈述如下：

- 陈述 $1$：在观众 $1$、$2$ 和 $3$ 中至少有一名冒名顶替者；
- 陈述 $2$：在观众 $2$、$3$ 和 $4$ 中至少有一名冒名顶替者；
- 陈述 $3$：在观众 $2$ 和 $3$ 中没有冒名顶替者。

可以看出，陈述 $1$、$2$ 和 $3$ 可能全部为真。例如，以下是其中一种可能的情况：

- 观众 $1$ 是冒名顶替者；
- 观众 $2$ 是船员；
- 观众 $3$ 是船员；
- 观众 $4$ 是冒名顶替者。

在第二个测试用例中，有 $5$ 名观众和 $2$ 条陈述。陈述如下：

- 陈述 $1$：在观众 $1$、$2$、$3$、$4$ 和 $5$ 中至少有一名冒名顶替者；
- 陈述 $2$：在观众 $1$、$2$、$3$、$4$ 和 $5$ 中没有冒名顶替者。

可以看出，陈述 $1$ 可能为真，陈述 $2$ 也可能为真。然而，陈述 $1$ 和 $2$ 不可能同时为真。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 3
1 1 3
1 2 4
0 2 3
1
1 3
5 2
0 1 5
1 1 5
3
1 1
2 2
1 2
1 2
0 1 1
1 1 1
2
1 1
2 2
7 9
1 2 2
1 4 5
0 5 6
1 2 2
1 1 1
0 4 7
0 3 7
0 2 7
0 6 6
5
1 5
2 6
3 7
4 8
5 9
```

### 输出

```
YES
YES
YES
NO
YES
YES
YES
NO
YES
NO
YES
```



---

---
title: "Clearing the Snowdrift"
layout: "post"
diff: 省选/NOI-
pid: CF2097E
tag: ['动态树 LCT', '线段树合并']
---

# Clearing the Snowdrift

## 题目描述

男孩 Vasya 非常喜欢旅行。特别是乘坐飞机旅行给他带来了极大的快乐。他正要飞往另一个城市，但跑道被厚厚的积雪覆盖，需要清理。

跑道可以表示为编号从 $1$ 到 $n$ 的 $n$ 个连续区域。暴风雪相当猛烈，但现在已经停止，因此 Vasya 计算出第 $i$ 个区域覆盖了 $a_i$ 米厚的积雪。针对这种情况，机场有一台工作方式相当特殊的扫雪机。每分钟，扫雪机可以执行以下操作：

- 选择一个长度不超过 $d$ 的连续区段，并从积雪最多的区域中移除一米积雪。具体来说，可以选择 $1 \le l \le r \le n$（$r - l + 1 \le d$）。然后计算 $c = \max \{ a_l, a_{l + 1}, \ldots , a_r \}$，如果 $c > 0$，则对于所有满足 $a_i = c$ 的 $i \colon l \le i \le r$，将 $a_i$ 的值减一。

Vasya 为这次飞行准备了很长时间，他想知道自己还需要等待多少时间才能让所有区域完全清除积雪。换句话说，需要计算扫雪机将所有区域的积雪清除（即对所有 $i$ 从 $1$ 到 $n$ 满足 $a_i = 0$）所需的最少分钟数。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 2 \cdot 10^5$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $d$（$1 \le n \le 5 \cdot 10^5, 1 \le d \le n$）——跑道的区域数量和扫雪机可以选择的区段的最大长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$），其中 $a_i$ 表示第 $i$ 个区域的积雪厚度。

保证所有测试用例的 $n$ 之和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——扫雪机将所有区域的积雪清除所需的最少分钟数。

## 说明/提示

在第一个测试用例中，存在一个最优的操作序列。首先，选择区段 $[2, 3]$ 四次。经过三次操作后，$a_2$ 将变为 $2$，数组 $a$ 将变为 $[1, 2, 2, 1, 2]$。第四次操作后，数组 $a$ 将变为 $[1, 1, 1, 1, 2]$。接下来，可以通过依次选择区段 $[1, 2]$、$[3, 3]$、$[5, 5]$ 和 $[4, 5]$ 将数组清零。

在第二个测试用例中，$d = 1$，这意味着每个区域需要独立清除，答案等于所有 $a_i$ 的总和。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 2
1 5 2 1 2
3 1
1000000000 1000000000 1000000000
```

### 输出

```
8
3000000000
```



---

---
title: "Maximize Nor"
layout: "post"
diff: 省选/NOI-
pid: CF2103F
tag: ['线段树', '位运算']
---

# Maximize Nor

## 题目描述

对于一个包含 $k$ 位整数的数组 $b_1, b_2, \ldots, b_m$，其按位或非运算$^{\text{∗}}$可以通过从左到右累积计算得到。更正式地说，对于 $m \ge 2$，$\operatorname{nor}(b_1, b_2, \ldots, b_m) = \operatorname{nor}(\operatorname{nor}(b_1, b_2, \ldots, b_{m - 1}), b_m)$，而 $\operatorname{nor}(b_1) = b_1$。

给定一个包含 $k$ 位整数的数组 $a_1, a_2, \ldots, a_n$。对于每个下标 $i$（$1 \le i \le n$），找出所有包含下标 $i$ 的子数组$^{\text{†}}$中按位或非运算的最大值。换句话说，对于每个下标 $i$，找出所有满足 $1 \le l \le i \le r \le n$ 的子数组 $a_l, a_{l+1}, \ldots, a_r$ 中 $\operatorname{nor}(a_l, a_{l+1}, \ldots, a_r)$ 的最大值。

$^{\text{∗}}$ 两个布尔值的逻辑或非运算定义为：当两个值都为 $0$ 时结果为 $1$，否则为 $0$。两个 $k$ 位整数的按位或非运算是对每对对应位进行逻辑或非运算得到的结果。

例如，将 $2$ 和 $6$ 表示为 $4$ 位二进制数时，计算 $\operatorname{nor}(2, 6)$。$2$ 的二进制表示为 $0010_2$，$6$ 为 $0110_2$。因此，$\operatorname{nor}(2,6) = 1001_2 = 9$，因为从左到右逐位进行逻辑或非运算：
- $\operatorname{nor}(0,0) = 1$
- $\operatorname{nor}(0,1) = 0$
- $\operatorname{nor}(1,0) = 0$
- $\operatorname{nor}(1,1) = 0$

注意，如果 $2$ 和 $6$ 表示为 $3$ 位整数，则 $\operatorname{nor}(2,6) = 1$。

$^{\text{†}}$ 数组 $x$ 是数组 $y$ 的子数组，当且仅当 $x$ 可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^5$，$1 \le k \le 17$）——数组的元素个数和数组元素的位数。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 2^k - 1$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数，其中第 $i$ 个整数是所有包含下标 $i$ 的子数组中按位或非运算的最大值。


## 说明/提示

在第一个测试用例中：
- 包含下标 $1$ 的子数组有 $[1]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $1$ 和 $0$。因此，下标 $1$ 的答案为 $1$。
- 包含下标 $2$ 的子数组有 $[3]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $3$ 和 $0$。因此，下标 $2$ 的答案为 $3$。

在第二个测试用例中：
- 对于 $i = 1$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 2$，按位或非运算最大的子数组是 $[a_2] = [7]$，$\operatorname{nor}(7) = 7$。
- 对于 $i = 3$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 4$，按位或非运算最大的子数组是 $[a_4] = [6]$，$\operatorname{nor}(6) = 6$。
- 对于 $i = 5$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2 2
1 3
5 3
1 7 4 6 2
```

### 输出

```
1 3
5 7 5 6 5
```



---

---
title: "Modulo 3"
layout: "post"
diff: 省选/NOI-
pid: CF2104G
tag: ['并查集', '数论', '线段树分治']
---

# Modulo 3

## 题目描述

给定基环内向森林，每个点有且仅有一条出边 $g_i$，可能有自环。

所有点的初始颜色均为 $1$，你可以执行如下操作**任意次**（可以为零次）：

- 选择一个顶点 $u \in [1,n]$，再选择一种颜色 $c \in [1,k]$，将 $u$ 能到达的所有点（包括 $u$ 本身）染成颜色 $c$。

你需要求出，最终能形成的不同的图的数量，**答案对 $3$ 取模**。

两个图不同，当且仅当存在一个编号为 $i$ 的节点，它的颜色在两图中不同。

现在有 $q$ 次修改操作，每次给定 $x,y,k$：

- 将 $g_x$ 修改为 $y$。
- 对于本次输入的 $k$，输出答案，对 $3$ 取模。

对 $g_x$ 的修改操作是永久的，对后面有影响。但是在每次询问答案时，所有顶点的初始颜色都是 $1$。

## 输入格式

第一行包含两个整数 $n$ 和 $q$。

第二行包含 $n$ 个整数 $g_1, g_2, \dots, g_n$。

接下来是 $q$ 行，第 $i$ 行包含三个整数 $x_i$ 、 $y_i$ 和 $k_i$ （$1 \le k_i \le 10^9$ ）。

## 输出格式

共 $q$ 行，每行一个在 $[0,3)$ 的整数。

## 说明/提示

$1 \le n, q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
4 5
2 3 1 4
4 3 1
2 1 2
3 4 3
4 1 5
2 4 4
```

### 输出

```
1
2
0
2
1
```

## 样例 #2

### 输入

```
8 10
7 4 6 8 7 7 1 4
1 7 5
2 3 3
8 6 1
3 1 3
7 2 5
5 2 4
2 7 4
4 6 5
5 2 3
4 5 1
```

### 输出

```
1
0
1
0
2
1
1
2
0
1
```



---

---
title: "Two Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF213E
tag: ['线段树', '平衡树', '枚举', '哈希 hashing']
---

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 输入

```
1 1
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 2
1
2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3

```

### 输出

```
0

```



---

---
title: "Fence"
layout: "post"
diff: 省选/NOI-
pid: CF232D
tag: ['线段树', '后缀数组 SA']
---

# Fence

## 题目描述

John Doe has a crooked fence, consisting of $ n $ rectangular planks, lined up from the left to the right: the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has width 1 and height $ h_{i} $ . We will assume that the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has index $ i $ .

A piece of the fence from $ l $ to $ r $ $ (1<=l<=r<=n) $ is a sequence of planks of wood with indices from $ l $ to $ r $ inclusive, that is, planks with indices $ l,l+1,...,r $ . The width of the piece of the fence from $ l $ to $ r $ is value $ r-l+1 $ .

Two pieces of the fence from $ l_{1} $ to $ r_{1} $ and from $ l_{2} $ to $ r_{2} $ are called matching, if the following conditions hold:

- the pieces do not intersect, that is, there isn't a single plank, such that it occurs in both pieces of the fence;
- the pieces are of the same width;
- for all $ i $ $ (0<=i<=r_{1}-l_{1}) $ the following condition holds: $ h_{l1+i}+h_{l2+i}=h_{l1}+h_{l2} $ .

John chose a few pieces of the fence and now wants to know how many distinct matching pieces are for each of them. Two pieces of the fence are distinct if there is a plank, which belongs to one of them and does not belong to the other one.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of wood planks in the fence. The second line contains $ n $ space-separated integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9} $ ) — the heights of fence planks.

The third line contains integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries. Next $ q $ lines contain two space-separated integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the boundaries of the $ i $ -th piece of the fence.

## 输出格式

For each query on a single line print a single integer — the number of pieces of the fence that match the given one. Print the answers to the queries in the order, in which the queries are given in the input.

## 样例 #1

### 输入

```
10
1 2 2 1 100 99 99 100 100 100
6
1 4
1 2
3 4
1 5
9 10
10 10

```

### 输出

```
1
2
2
0
2
9

```



---

---
title: "Little Elephant and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF258E
tag: ['线段树']
---

# Little Elephant and Tree

## 题目描述

小象对一棵根节点编号为$1$，节点数为$n$的有根树进行$m$次操作。

这棵树每个节点都有一个集合。

第$i$次操作给出$a_i$和$b_i$，把$i$这个数字放入$a_i$和$b_i$这两个点为根的子树里的所有集合中。（包括$a_i$和$b_i$）

在操作完后，输出$c_i$，$c_i$表示有多少个结点（不包括$i$）的集合至少与$i$结点的集合有一个公共数字。

## 输入格式

第一行一个$ n,m(1 \le n,m \le 10^5) $，表示结点数和操作数。

接下来$n-1$行，两个数$u_i$和$v_i$，表示$u_i$到$v_i$有一条边。

接下来$m$行，第$i$行两个数$a_i$和$b_i$表示对这两个点为根节点的子树进行操作。

## 输出格式

输出一行，$n$个数，$c_1,c_2,c_3......c_n$

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 5
3 4
2 3

```

### 输出

```
0 3 3 3 3 
```

## 样例 #2

### 输入

```
11 3
1 2
2 3
2 4
1 5
5 6
5 7
5 8
6 9
8 10
8 11
2 9
3 6
2 8

```

### 输出

```
0 6 7 6 0 2 0 5 4 5 5 
```



---

---
title: "Maxim and Increasing Subsequence"
layout: "post"
diff: 省选/NOI-
pid: CF261D
tag: ['线段树', '树状数组', '枚举']
---

# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 输入格式

The first line contains four integers $ k $ , $ n $ , $ maxb $ and $ t $ $ (1<=k<=10; 1<=n,maxb<=10^{5}; 1<=t<=10^{9}; n×maxb<=2·10^{7}) $ . Each of the next $ k $ lines contain $ n $ integers $ b_{1},b_{2},...,b_{n} $ $ (1<=b_{i}<=maxb) $ .

Note that for each variant of the sequence $ a $ the values $ n $ , $ maxb $ and $ t $ coincide, the only arrays $ b $ s differ.

The numbers in the lines are separated by single spaces.

## 输出格式

Print $ k $ integers — the answers for the variants of the sequence $ a $ . Print the answers in the order the variants follow in the input.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1

```

### 输出

```
2
3
3

```



---

---
title: "Cow Tennis Tournament"
layout: "post"
diff: 省选/NOI-
pid: CF283E
tag: ['线段树', '离散化', '排序']
---

# Cow Tennis Tournament

## 题目描述

Farmer John is hosting a tennis tournament with his $ n $ cows. Each cow has a skill level $ s_{i} $ , and no two cows having the same skill level. Every cow plays every other cow exactly once in the tournament, and each cow beats every cow with skill level lower than its own.

However, Farmer John thinks the tournament will be demoralizing for the weakest cows who lose most or all of their matches, so he wants to flip some of the results. In particular, at $ k $ different instances, he will take two integers $ a_{i},b_{i} $ $ (a_{i}<b_{i}) $ and flip all the results between cows with skill level between $ a_{i} $ and $ b_{i} $ inclusive. That is, for any pair $ x,y $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283E/7acc269d103239529ceb47c1b525554954b93d55.png) he will change the result of the match on the final scoreboard (so if $ x $ won the match, the scoreboard will now display that $ y $ won the match, and vice versa). It is possible that Farmer John will change the result of a match multiple times. It is not guaranteed that $ a_{i} $ and $ b_{i} $ are equal to some cow's skill level.

Farmer John wants to determine how balanced he made the tournament results look. In particular, he wants to count the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ . Help him determine this number.

Note that two triples are considered different if they do not contain the same set of cows (i.e. if there is a cow in one triple that is not in the other).

## 输入格式

On the first line are two space-separated integers, $ n $ and $ k $ $ (3<=n<=10^{5}; 0<=k<=10^{5}) $ . On the next line are $ n $ space-separated distinct integers, $ s_{1},s_{2},...,s_{n} $ $ (1<=s_{i}<=10^{9}) $ , denoting the skill levels of the cows. On the next $ k $ lines are two space separated integers, $ a_{i} $ and $ b_{i} $ $ (1<=a_{i}<b_{i}<=10^{9}) $ representing the changes Farmer John made to the scoreboard in the order he makes it.

## 输出格式

A single integer, containing the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ .

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample, cow 3 > cow 1, cow 3 > cow 2, and cow 2 > cow 1. However, the results between cows 1 and 2 and cows 2 and 3 are flipped, so now FJ's results show that cow 1 > cow 2, cow 2 > cow 3, and cow 3 > cow 1, so cows 1, 2, and 3 form a balanced triple.

## 样例 #1

### 输入

```
3 2
1 2 3
1 2
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 3
5 9 4 1 7
1 7
2 8
3 9

```

### 输出

```
3

```



---

---
title: "Mystic Carvings"
layout: "post"
diff: 省选/NOI-
pid: CF297E
tag: ['线段树', '树状数组', '容斥原理']
---

# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=10^{5} $ ) — the number of lines.

Each of the following $ n $ lines contains two integers $ a_{i},b_{i} $ ( $ 1<=a_{i},b_{i}<=2n $ ), which means that there is a line carved on the ice connecting the $ a_{i} $ –th and $ b_{i} $ –th endpoint.

It's guaranteed that each endpoints touches exactly one line.

## 输出格式

Print the number of ways to build the caves.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12

```

### 输出

```
6

```



---

---
title: "Optimize!"
layout: "post"
diff: 省选/NOI-
pid: CF338E
tag: ['线段树']
---

# Optimize!

## 题目描述

Manao is solving a problem with the following statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF338E/5342825b0bbcbbc06536e5a019fb46969a4849f8.png)He came up with a solution that produces the correct answers but is too slow. You are given the pseudocode of his solution, where the function getAnswer calculates the answer to the problem:

```
getAnswer(a[1..n], b[1..len], h)
  answer = 0
  for i = 1 to n-len+1
    answer = answer + f(a[i..i+len-1], b, h, 1)
  return answer

f(s[1..len], b[1..len], h, index)
  if index = len+1 then
    return 1
  for i = 1 to len
    if s[index] + b[i] >= h
      mem = b[i]
      b[i] = 0
      res = f(s, b, h, index + 1)
      b[i] = mem
      if res > 0
        return 1
  return 0
```

Your task is to help Manao optimize his algorithm.

## 输入格式

The first line contains space-separated integers $ n $ , $ len $ and $ h $ ( $ 1<=len<=n<=150000; 1<=h<=10^{9} $ ). The second line contains $ len $ space-separated integers $ b_{1},b_{2},...,b_{len} $ ( $ 1<=b_{i}<=10^{9} $ ). The third line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print a single number — the answer to Manao's problem.

## 样例 #1

### 输入

```
5 2 10
5 3
1 8 5 5 7

```

### 输出

```
2

```



---

---
title: "Iahub and Xors"
layout: "post"
diff: 省选/NOI-
pid: CF341D
tag: ['线段树', '树状数组', '树套树']
---

# Iahub and Xors

## 题目描述

Iahub does not like background stories, so he'll tell you exactly what this problem asks you for.

You are given a matrix $ a $ with $ n $ rows and $ n $ columns. Initially, all values of the matrix are zeros. Both rows and columns are 1-based, that is rows are numbered 1, 2, ..., $ n $ and columns are numbered 1, 2, ..., $ n $ . Let's denote an element on the $ i $ -th row and $ j $ -th column as $ a_{i,j} $ .

We will call a submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ such elements $ a_{i,j} $ for which two inequalities hold: $ x_{0}<=i<=x_{1} $ , $ y_{0}<=j<=y_{1} $ .

Write a program to perform two following operations:

1. Query( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ ): print the xor sum of the elements of the submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ .
2. Update( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ ): each element from submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ gets xor-ed by value $ v $ .

## 输入格式

The first line contains two integers: $ n $ ( $ 1<=n<=1000 $ ) and $ m $ ( $ 1<=m<=10^{5} $ ). The number $ m $ represents the number of operations you need to perform. Each of the next $ m $ lines contains five or six integers, depending on operation type.

If the $ i $ -th operation from the input is a query, the first number from $ i $ -th line will be 1. It will be followed by four integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ . If the $ i $ -th operation is an update, the first number from the $ i $ -th line will be 2. It will be followed by five integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ .

It is guaranteed that for each update operation, the following inequality holds: $ 0<=v<2^{62} $ . It is guaranteed that for each operation, the following inequalities hold: $ 1<=x_{0}<=x_{1}<=n $ , $ 1<=y_{0}<=y_{1}<=n $ .

## 输出格式

For each query operation, output on a new line the result.

## 说明/提示

After the first $ 3 $ operations, the matrix will look like this:

```
1 1 2
1 1 2
3 3 3
```
The fourth operation asks us to compute 1 xor 2 xor 3 xor 3 = 3.

The fifth operation asks us to compute 1 xor 3 = 2.

## 样例 #1

### 输入

```
3 5
2 1 1 2 2 1
2 1 3 2 3 2
2 3 1 3 3 3
1 2 2 3 3
1 2 2 3 2

```

### 输出

```
3
2

```



---

---
title: "Tourists"
layout: "post"
diff: 省选/NOI-
pid: CF487E
tag: ['线段树', '强连通分量', '树链剖分', '圆方树']
---

# Tourists

## 题目描述

Cyberland 有 $n$ 座城市，编号从 $1$ 到 $n$，有 $m$ 条双向道路连接这些城市。第 $j$ 条路连接城市 $a_j$ 和 $b_j$。每天，都有成千上万的游客来到 Cyberland 游玩。

在每一个城市，都有纪念品售卖，第 $i$ 个城市售价为 $w_i$。这个售价有时会变动。

每一个游客的游览路径都有固定起始城市和终止城市，且不会经过重复的城市。

他们会在路径上的城市中，售价最低的那个城市购买纪念品。

你能求出每一个游客在所有合法的路径中能购买的最低售价是多少吗？

你要处理 $q$ 个操作：

`C a w`： 表示 $a$ 城市的纪念品售价变成 $w$。

`A a b`： 表示有一个游客要从 $a$ 城市到 $b$ 城市，你要回答在所有他的旅行路径中最低售价的最低可能值。

## 输入格式

第一行包含用一个空格隔开的三个数 $n, m, q$。

接下来 $n$ 行，每行包含一个数 $w_i$。

接下来 $m$ 行，每行包含用一个空格隔开的两个数 $a_j$,$b_j$。（$1 \le a _ j, b _ j \le n,a _ j \neq b _ j$）

数据保证没有两条道路连接同样一对城市，也没有一条道路两端是相同的城市。并且任意两个城市都可以相互到达。

接下来 $q$ 行，每行是 `C a w` 或 `A a b` ，描述了一个操作。

## 输出格式

对于每一个 A 类操作，输出一行表示对应的答案。

## 样例 #1

### 输入

```
3 3 3
1
2
3
1 2
2 3
1 3
A 2 3
C 1 5
A 2 3

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
7 9 4
1
2
3
4
5
6
7
1 2
2 5
1 5
2 3
3 4
2 4
5 6
6 7
5 7
A 2 3
A 6 4
A 6 7
A 3 3

```

### 输出

```
2
1
5
3

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
title: "Kefa and Watch"
layout: "post"
diff: 省选/NOI-
pid: CF580E
tag: ['字符串', '线段树', '哈希 hashing']
---

# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 输入格式

The first line of the input contains three positive integers $ n $ , $ m $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 1<=m+k<=10^{5} $ ) — the length of the serial number, the number of change made by Kefa and the number of quality checks.

The second line contains a serial number consisting of $ n $ digits.

Then $ m+k $ lines follow, containing either checks or changes.

The changes are given as 1 $ l $ $ r $ $ c $ ( $ 1<=l<=r<=n $ , $ 0<=c<=9 $ ). That means that Kefa changed all the digits from the $ l $ -th to the $ r $ -th to be $ c $ .

The checks are given as 2 $ l $ $ r $ $ d $ ( $ 1<=l<=r<=n $ , $ 1<=d<=r-l+1 $ ).

## 输出格式

For each check on a single line print "YES" if the watch passed it, otherwise print "NO".

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1

```

### 输出

```
NO
YES

```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1

```

### 输出

```
NO
YES
NO

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
title: "Sasha and Array"
layout: "post"
diff: 省选/NOI-
pid: CF718C
tag: ['线段树', '斐波那契数列', '矩阵乘法']
---

# Sasha and Array

## 题目描述

Sasha has an array of integers $ a_{1},a_{2},...,a_{n} $ . You have to perform $ m $ queries. There might be queries of two types:

1. 1 l r x — increase all integers on the segment from $ l $ to $ r $ by values $ x $ ;
2. 2 l r — find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF718C/9868345ffca37ba44cd594bdeb805f21011d5d1d.png), where $ f(x) $ is the $ x $ -th Fibonacci number. As this number may be large, you only have to find it modulo $ 10^{9}+7 $ .

In this problem we define Fibonacci numbers as follows: $ f(1)=1 $ , $ f(2)=1 $ , $ f(x)=f(x-1)+f(x-2) $ for all $ x>2 $ .

Sasha is a very talented boy and he managed to perform all queries in five seconds. Will you be able to write the program that performs as well as Sasha?

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n<=100000 $ , $ 1<=m<=100000 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Then follow $ m $ lines with queries descriptions. Each of them contains integers $ tp_{i} $ , $ l_{i} $ , $ r_{i} $ and may be $ x_{i} $ ( $ 1<=tp_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ , $ 1<=x_{i}<=10^{9} $ ). Here $ tp_{i}=1 $ corresponds to the queries of the first type and $ tp_{i} $ corresponds to the queries of the second type.

It's guaranteed that the input will contains at least one query of the second type.

## 输出格式

For each query of the second type print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

Initially, array $ a $ is equal to $ 1 $ , $ 1 $ , $ 2 $ , $ 1 $ , $ 1 $ .

The answer for the first query of the second type is $ f(1)+f(1)+f(2)+f(1)+f(1)=1+1+1+1+1=5 $ .

After the query 1 2 4 2 array $ a $ is equal to $ 1 $ , $ 3 $ , $ 4 $ , $ 3 $ , $ 1 $ .

The answer for the second query of the second type is $ f(3)+f(4)+f(3)=2+3+2=7 $ .

The answer for the third query of the second type is $ f(1)+f(3)+f(4)+f(3)+f(1)=1+2+3+2+1=9 $ .

## 样例 #1

### 输入

```
5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5

```

### 输出

```
5
7
9

```



---

---
title: "Anton and Permutation"
layout: "post"
diff: 省选/NOI-
pid: CF785E
tag: ['线段树', '树状数组']
---

# Anton and Permutation

## 题目描述

Anton likes permutations, especially he likes to permute their elements. Note that a permutation of $ n $ elements is a sequence of numbers $ {a_{1},a_{2},...,a_{n}} $ , in which every number from $ 1 $ to $ n $ appears exactly once.

One day Anton got a new permutation and started to play with it. He does the following operation $ q $ times: he takes two elements of the permutation and swaps these elements. After each operation he asks his friend Vanya, how many inversions there are in the new permutation. The number of inversions in a permutation is the number of distinct pairs $ (i,j) $ such that $ 1<=i<j<=n $ and $ a_{i}>a_{j} $ .

Vanya is tired of answering Anton's silly questions. So he asked you to write a program that would answer these questions instead of him.

Initially Anton's permutation was $ {1,2,...,n} $ , that is $ a_{i}=i $ for all $ i $ such that $ 1<=i<=n $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ $ (1<=n<=200000,1<=q<=50000) $ — the length of the permutation and the number of operations that Anton does.

Each of the following $ q $ lines of the input contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i},r_{i}<=n) $ — the indices of elements that Anton swaps during the $ i $ -th operation. Note that indices of elements that Anton swaps during the $ i $ -th operation can coincide. Elements in the permutation are numbered starting with one.

## 输出格式

Output $ q $ lines. The $ i $ -th line of the output is the number of inversions in the Anton's permutation after the $ i $ -th operation.

## 说明/提示

Consider the first sample.

After the first Anton's operation the permutation will be $ {1,2,3,5,4} $ . There is only one inversion in it: $ (4,5) $ .

After the second Anton's operation the permutation will be $ {1,5,3,2,4} $ . There are four inversions: $ (2,3) $ , $ (2,4) $ , $ (2,5) $ and $ (3,4) $ .

After the third Anton's operation the permutation will be $ {1,4,3,2,5} $ . There are three inversions: $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

After the fourth Anton's operation the permutation doesn't change, so there are still three inversions.

## 样例 #1

### 输入

```
5 4
4 5
2 4
2 5
2 2

```

### 输出

```
1
4
3
3

```

## 样例 #2

### 输入

```
2 1
2 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6 7
1 4
3 5
2 3
3 3
3 6
2 1
5 1

```

### 输出

```
5
6
7
7
10
11
8

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
title: "Subtree Minimum Query"
layout: "post"
diff: 省选/NOI-
pid: CF893F
tag: ['可持久化线段树']
---

# Subtree Minimum Query

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Each vertex has a number written on it; number $ a_{i} $ is written on vertex $ i $ .

Let's denote $ d(i,j) $ as the distance between vertices $ i $ and $ j $ in the tree (that is, the number of edges in the shortest path from $ i $ to $ j $ ). Also let's denote the  $ k $ -blocked subtree of vertex $ x $ as the set of vertices $ y $ such that both these conditions are met:

- $ x $ is an ancestor of $ y $ (every vertex is an ancestor of itself);
- $ d(x,y)<=k $ .

You are given $ m $ queries to the tree. $ i $ -th query is represented by two numbers $ x_{i} $ and $ k_{i} $ , and the answer to this query is the minimum value of $ a_{j} $ among such vertices $ j $ such that $ j $ belongs to $ k_{i} $ -blocked subtree of $ x_{i} $ .

Write a program that would process these queries quickly!

Note that the queries are given in a modified way.

## 输入格式

The first line contains two integers $ n $ and $ r $ ( $ 1<=r<=n<=100000 $ ) — the number of vertices in the tree and the index of the root, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the numbers written on the vertices.

Then $ n-1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1<=x,y<=n $ ) and representing an edge between vertices $ x $ and $ y $ . It is guaranteed that these edges form a tree.

Next line contains one integer $ m $ ( $ 1<=m<=10^{6} $ ) — the number of queries to process.

Then $ m $ lines follow, $ i $ -th line containing two numbers $ p_{i} $ and $ q_{i} $ , which can be used to restore $ i $ -th query ( $ 1<=p_{i},q_{i}<=n $ ).

 $ i $ -th query can be restored as follows:

Let $ last $ be the answer for previous query (or $ 0 $ if $ i=1 $ ). Then $ x_{i}=((p_{i}+last)modn)+1 $ , and $ k_{i}=(q_{i}+last)modn $ .

## 输出格式

Print $ m $ integers. $ i $ -th of them has to be equal to the answer to $ i $ -th query.

## 样例 #1

### 输入

```
5 2
1 3 2 3 5
2 3
5 1
3 4
4 1
2
1 2
2 3

```

### 输出

```
2
5

```



---

---
title: "Yet Another Maxflow Problem"
layout: "post"
diff: 省选/NOI-
pid: CF903G
tag: ['线段树', '最小割']
---

# Yet Another Maxflow Problem

## 题目描述

In this problem you will have to deal with a very special network.

The network consists of two parts: part $ A $ and part $ B $ . Each part consists of $ n $ vertices; $ i $ -th vertex of part $ A $ is denoted as $ A_{i} $ , and $ i $ -th vertex of part $ B $ is denoted as $ B_{i} $ .

For each index $ i $ ( $ 1<=i<n $ ) there is a directed edge from vertex $ A_{i} $ to vertex $ A_{i+1} $ , and from $ B_{i} $ to $ B_{i+1} $ , respectively. Capacities of these edges are given in the input. Also there might be several directed edges going from part $ A $ to part $ B $ (but never from $ B $ to $ A $ ).

You have to calculate the [maximum flow value](https://en.wikipedia.org/wiki/Maximum_flow_problem) from $ A_{1} $ to $ B_{n} $ in this network. Capacities of edges connecting $ A_{i} $ to $ A_{i+1} $ might sometimes change, and you also have to maintain the maximum flow value after these changes. Apart from that, the network is fixed (there are no changes in part $ B $ , no changes of edges going from $ A $ to $ B $ , and no edge insertions or deletions).

Take a look at the example and the notes to understand the structure of the network better.

## 输入格式

The first line contains three integer numbers $ n $ , $ m $ and $ q $ ( $ 2<=n,m<=2·10^{5} $ , $ 0<=q<=2·10^{5} $ ) — the number of vertices in each part, the number of edges going from $ A $ to $ B $ and the number of changes, respectively.

Then $ n-1 $ lines follow, $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ denoting that the edge from $ A_{i} $ to $ A_{i+1} $ has capacity $ x_{i} $ and the edge from $ B_{i} $ to $ B_{i+1} $ has capacity $ y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{9} $ ).

Then $ m $ lines follow, describing the edges from $ A $ to $ B $ . Each line contains three integers $ x $ , $ y $ and $ z $ denoting an edge from $ A_{x} $ to $ B_{y} $ with capacity $ z $ ( $ 1<=x,y<=n $ , $ 1<=z<=10^{9} $ ). There might be multiple edges from $ A_{x} $ to $ B_{y} $ .

And then $ q $ lines follow, describing a sequence of changes to the network. $ i $ -th line contains two integers $ v_{i} $ and $ w_{i} $ , denoting that the capacity of the edge from $ A_{vi} $ to $ A_{vi}+1 $ is set to $ w_{i} $ ( $ 1<=v_{i}<n $ , $ 1<=w_{i}<=10^{9} $ ).

## 输出格式

Firstly, print the maximum flow value in the original network. Then print $ q $ integers, $ i $ -th of them must be equal to the maximum flow value after $ i $ -th change.

## 说明/提示

This is the original network in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF903G/dcc7a52e873b883e6fea740d5c4aff84e5c0da8d.png)

## 样例 #1

### 输入

```
4 3 2
1 2
3 4
5 6
2 2 7
1 4 8
4 3 9
1 100
2 100

```

### 输出

```
9
14
14

```



---

---
title: "Jamie and To-do List"
layout: "post"
diff: 省选/NOI-
pid: CF916D
tag: ['线段树', '可持久化线段树', '可持久化']
---

# Jamie and To-do List

## 题目描述

“为什么我要完成这么多作业？”

Jamie 正忙于他的学校生活。

他开始忘记他必须做的作业。他决定把这些事情写在 To-Do List 上。

他为他的每项任务分配一个价值优先级(较低的价值意味着更重要)，这样他就可以决定他需要花更多的时间在哪个任务上。

几天后，Jamie 发现名单太大了，他甚至不能自己管理名单！由于您是 Jamie 的好朋友，请帮助他编写一个程序来支持待办事项列表中的以下操作:

`set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。

`remove a_i`：删除该任务。

`query a_i`：求优先级比 $a_i$ 小的任务个数，如果没有则输出 $-1$。

`undo sum`：删除此次操作之前的 $sum$ 次操作。

在 Day 0，To-Do List 为空，在接下来 $Q$ 个日子内，Jamie 都会在四个操作中任选一个执行。

对于每个询问操作，输出对应的答案。

## 输入格式

第一行是一个整数 $Q$。

接下来的 $Q$ 行为任一个操作，第 $i$ 为第 $i$ 天的操作。

**保证最后一行是询问操作。**

## 输出格式

对于所有的查询操作，输出对应的答案。

## 说明/提示

保证输入的字符串由小写字符构成，设其长度为 $len$，则 $1\leq len\leq15$。

$1\le Q\le10^5$，并且保证对于所有的 undo 操作，$sum$ 不超过该天之前的天数。

## 样例 #1

### 输入

```
8
set chemlabreport 1
set physicsexercise 2
set chinesemockexam 3
query physicsexercise
query chinesemockexam
remove physicsexercise
query physicsexercise
query chinesemockexam

```

### 输出

```
1
2
-1
1

```

## 样例 #2

### 输入

```
8
set physicsexercise 2
set chinesemockexam 3
set physicsexercise 1
query physicsexercise
query chinesemockexam
undo 4
query physicsexercise
query chinesemockexam

```

### 输出

```
0
1
0
-1

```

## 样例 #3

### 输入

```
5
query economicsessay
remove economicsessay
query economicsessay
undo 2
query economicsessay

```

### 输出

```
-1
-1
-1

```

## 样例 #4

### 输入

```
5
set economicsessay 1
remove economicsessay
undo 1
undo 1
query economicsessay

```

### 输出

```
-1

```



---

---
title: "Jamie and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF916E
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# Jamie and Tree

## 题目描述

To your surprise, Jamie is the final boss! Ehehehe.

Jamie has given you a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Initially, the root of the tree is the vertex with number $ 1 $ . Also, each vertex has a value on it.

Jamie also gives you three types of queries on the tree:

 $ 1\ v $ — Change the tree's root to vertex with number $ v $ .

 $ 2\ u\ v\ x $ — For each vertex in the subtree of smallest size that contains $ u $ and $ v $ , add $ x $ to its value.

 $ 3\ v $ — Find sum of values of vertices in the subtree of vertex with number $ v $ .

A subtree of vertex $ v $ is a set of vertices such that $ v $ lies on shortest path from this vertex to root of the tree. Pay attention that subtree of a vertex can change after changing the tree's root.

Show your strength in programming to Jamie by performing the queries accurately!

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ q $ ( $ 1<=n<=10^{5},1<=q<=10^{5} $ ) — the number of vertices in the tree and the number of queries to process respectively.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{8}<=a_{i}<=10^{8} $ ) — initial values of the vertices.

Next $ n-1 $ lines contains two space-separated integers $ u_{i},v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) describing edge between vertices $ u_{i} $ and $ v_{i} $ in the tree.

The following $ q $ lines describe the queries.

Each query has one of following formats depending on its type:

 $ 1\ v $ ( $ 1<=v<=n $ ) for queries of the first type.

 $ 2\ u\ v\ x $ ( $ 1<=u,v<=n,-10^{8}<=x<=10^{8} $ ) for queries of the second type.

 $ 3\ v $ ( $ 1<=v<=n $ ) for queries of the third type.

All numbers in queries' descriptions are integers.

The queries must be carried out in the given order. It is guaranteed that the tree is valid.

## 输出格式

For each query of the third type, output the required answer. It is guaranteed that at least one query of the third type is given by Jamie.

## 说明/提示

The following picture shows how the tree varies after the queries in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916E/9b296178af98e90dbbac00c785fb2ed88745e7bd.png)

## 样例 #1

### 输入

```
6 7
1 4 2 8 5 7
1 2
3 1
4 3
4 5
3 6
3 1
2 4 6 3
3 4
1 6
2 2 4 -5
1 4
3 3

```

### 输出

```
27
19
5

```

## 样例 #2

### 输入

```
4 6
4 3 5 6
1 2
2 3
3 4
3 1
1 3
2 2 4 3
1 1
2 2 4 -3
3 1

```

### 输出

```
18
21

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

---
title: "Shortest Path Queries"
layout: "post"
diff: 省选/NOI-
pid: CF938G
tag: ['线段树分治']
---

# Shortest Path Queries

## 题目描述

You are given an undirected connected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times).

There are three types of queries you have to process:

- $ 1 $ $ x $ $ y $ $ d $ — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

Print the answers for all queries of type $ 3 $ .

## 输入格式

The first line contains two numbers $ n $ and $ m $ ( $ 1<=n,m<=200000 $ ) — the number of vertices and the number of edges in the graph, respectively.

Then $ m $ lines follow denoting the edges of the graph. Each line contains three integers $ x $ , $ y $ and $ d $ ( $ 1<=x<y<=n $ , $ 0<=d<=2^{30}-1 $ ). Each pair $ (x,y) $ is listed at most once. The initial graph is connected.

Then one line follows, containing an integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries you have to process.

Then $ q $ lines follow, denoting queries in the following form:

- $ 1 $ $ x $ $ y $ $ d $ ( $ 1<=x<y<=n $ , $ 0<=d<=2^{30}-1 $ ) — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ ( $ 1<=x<y<=n $ ) — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ ( $ 1<=x<y<=n $ ) — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

It is guaranteed that at least one query has type $ 3 $ .

## 输出格式

Print the answers for all queries of type $ 3 $ in the order they appear in input.

## 样例 #1

### 输入

```
5 5
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
5
3 1 5
1 1 3 1
3 1 5
2 1 5
3 1 5

```

### 输出

```
1
1
2

```



---

---
title: "Santa's Gift"
layout: "post"
diff: 省选/NOI-
pid: CF960H
tag: ['线段树', '树链剖分', '期望']
---

# Santa's Gift

## 题目描述

Santa has an infinite number of candies for each of $ m $ flavours. You are given a rooted tree with $ n $ vertices. The root of the tree is the vertex $ 1 $ . Each vertex contains exactly one candy. The $ i $ -th vertex has a candy of flavour $ f_i $ .

Sometimes Santa fears that candies of flavour $ k $ have melted. He chooses any vertex $ x $ randomly and sends the subtree of $ x $ to the Bakers for a replacement. In a replacement, all the candies with flavour $ k $ are replaced with a new candy of the same flavour. The candies which are not of flavour $ k $ are left unchanged. After the replacement, the tree is restored.

The actual cost of replacing one candy of flavour $ k $ is $ c_k $ (given for each $ k $ ). The Baker keeps the price fixed in order to make calculation simple. Every time when a subtree comes for a replacement, the Baker charges $ C $ , no matter which subtree it is and which flavour it is.

Suppose that for a given flavour $ k $ the probability that Santa chooses a vertex for replacement is same for all the vertices. You need to find out the expected value of error in calculating the cost of replacement of flavour $ k $ . The error in calculating the cost is defined as follows.

 $ $$$ Error\ E(k) =\ (Actual Cost\ –\ Price\ charged\ by\ the\ Bakers) ^ 2. $ $ </p><p>Note that the actual cost is the cost of replacement of one candy of the flavour  $ k $  multiplied by the number of candies in the subtree.</p><p>Also, sometimes Santa may wish to replace a candy at vertex  $ x $  with a candy of some flavour from his pocket.</p><p>You need to handle two types of operations: </p><ul> <li> Change the flavour of the candy at vertex  $ x $  to  $ w $ . </li><li> Calculate the expected value of error in calculating the cost of replacement for a given flavour  $ k$$$.

## 输入格式

The first line of the input contains four integers $ n $ ( $ 2 \leqslant n \leqslant 5 \cdot 10^4 $ ), $ m $ , $ q $ , $ C $ ( $ 1 \leqslant m, q \leqslant 5 \cdot 10^4 $ , $ 0 \leqslant C \leqslant 10^6 $ ) — the number of nodes, total number of different flavours of candies, the number of queries and the price charged by the Bakers for replacement, respectively.

The second line contains $ n $ integers $ f_1, f_2, \dots, f_n $ ( $ 1 \leqslant f_i \leqslant m $ ), where $ f_i $ is the initial flavour of the candy in the $ i $ -th node.

The third line contains $ n - 1 $ integers $ p_2, p_3, \dots, p_n $ ( $ 1 \leqslant p_i \leqslant n $ ), where $ p_i $ is the parent of the $ i $ -th node.

The next line contains $ m $ integers $ c_1, c_2, \dots c_m $ ( $ 1 \leqslant c_i \leqslant 10^2 $ ), where $ c_i $ is the cost of replacing one candy of flavour $ i $ .

The next $ q $ lines describe the queries. Each line starts with an integer $ t $ ( $ 1 \leqslant t \leqslant 2 $ ) — the type of the query.

If $ t = 1 $ , then the line describes a query of the first type. Two integers $ x $ and $ w $ follow ( $ 1 \leqslant  x \leqslant  n $ , $ 1 \leqslant  w \leqslant m $ ), it means that Santa replaces the candy at vertex $ x $ with flavour $ w $ .

Otherwise, if $ t = 2 $ , the line describes a query of the second type and an integer $ k $ ( $ 1 \leqslant k \leqslant m $ ) follows, it means that you should print the expected value of the error in calculating the cost of replacement for a given flavour $ k $ .

The vertices are indexed from $ 1 $ to $ n $ . Vertex $ 1 $ is the root.

## 输出格式

Output the answer to each query of the second type in a separate line.

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . The checker program considers your answer correct if and only if $ \frac{|a-b|}{max(1,b)}\leqslant 10^{-6} $ .

## 说明/提示

For $ 1 $ -st query, the error in calculating the cost of replacement for flavour $ 1 $ if vertex $ 1 $ , $ 2 $ or $ 3 $ is chosen are $ 66^2 $ , $ 66^2 $ and $ (-7)^2 $ respectively. Since the probability of choosing any vertex is same, therefore the expected value of error is $ \frac{66^2+66^2+(-7)^2}{3} $ .

Similarly, for $ 2 $ -nd query the expected value of error is $ \frac{41^2+(-7)^2+(-7)^2}{3} $ .

After $ 3 $ -rd query, the flavour at vertex $ 2 $ changes from $ 1 $ to $ 3 $ .

For $ 4 $ -th query, the expected value of error is $ \frac{(-7)^2+(-7)^2+(-7)^2}{3} $ .

Similarly, for $ 5 $ -th query, the expected value of error is $ \frac{89^2+41^2+(-7)^2}{3} $ .

## 样例 #1

### 输入

```
3 5 5 7
3 1 4
1 1
73 1 48 85 89
2 1
2 3
1 2 3
2 1
2 3

```

### 输出

```
2920.333333333333
593.000000000000
49.000000000000
3217.000000000000

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

