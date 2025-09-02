---
title: "Session in BSU"
layout: "post"
diff: 省选/NOI-
pid: CF1027F
tag: ['网络流', '连通块', '二分图']
---

# Session in BSU

## 题目描述

Polycarp studies in Berland State University. Soon he will have to take his exam. He has to pass exactly $ n $ exams.

For the each exam $ i $ there are known two days: $ a_i $ — day of the first opportunity to pass the exam, $ b_i $ — day of the second opportunity to pass the exam ( $ a_i < b_i $ ). Polycarp can pass at most one exam during each day. For each exam Polycarp chooses by himself which day he will pass this exam. He has to pass all the $ n $ exams.

Polycarp wants to pass all the exams as soon as possible. Print the minimum index of day by which Polycarp can pass all the $ n $ exams, or print -1 if he cannot pass all the exams at all.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of exams.

The next $ n $ lines contain two integers each: $ a_i $ and $ b_i $ ( $ 1 \le a_i < b_i \le 10^9 $ ), where $ a_i $ is the number of day of the first passing the $ i $ -th exam and $ b_i $ is the number of day of the second passing the $ i $ -th exam.

## 输出格式

If Polycarp cannot pass all the $ n $ exams, print -1. Otherwise print the minimum index of day by which Polycarp can do that.

## 样例 #1

### 输入

```
2
1 5
1 7

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
5 13
1 5
1 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3
10 40
40 80
10 80

```

### 输出

```
80

```

## 样例 #4

### 输入

```
3
99 100
99 100
99 100

```

### 输出

```
-1

```



---

---
title: "Fair Share"
layout: "post"
diff: 省选/NOI-
pid: CF1634E
tag: ['二分图']
---

# Fair Share

## 题目描述

Even a cat has things it can do that AI cannot.

— Fei-Fei Li



You are given $ m $ arrays of positive integers. Each array is of even length.

You need to split all these integers into two equal multisets $ L $ and $ R $ , that is, each element of each array should go into one of two multisets (but not both). Additionally, for each of the $ m $ arrays, exactly half of its elements should go into $ L $ , and the rest should go into $ R $ .

Give an example of such a division or determine that no such division exists.

## 输入格式

The first line contains an integer $ m $ ( $ 1 \le m \le 10 ^ 5 $ ) — the number of arrays.

The next $ 2 \cdot m $ lines contain descriptions of the arrays.

For each array, the first line contains an even integer $ n $ ( $ 2 \le n \le 2 \cdot 10 ^ 5 $ ) — the length of the array. The second line consists of $ n $ space-separated integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10 ^ 9 $ ) — array elements.

It is guaranteed that the sum of $ n $ over all arrays does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

If the answer exists, print "YES", and then print $ m $ lines.

On each line, for each element, print the letter "L" or "R" (capitalized, without spaces), depending on which multiset the element should go into.

If there is no answer, print "NO" on the only line.

## 说明/提示

In the first array, we add the first element to $ R $ and the second to $ L $ . Now $ L = \{2\} $ , and $ R = \{1\} $ .

In the second array, we add the first and third elements to $ L $ and the rest to $ R $ . Now $ L = \{1, 2, 3\} $ and $ R = \{1, 2, 3\} $ .

In the third array, we add elements 2, 3, and 6 to $ L $ , and others — to $ R $ . As a result, $ L = R = \{1, 1, 2, 2, 3, 3\} $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3
```

### 输出

```
YES
RL
LRLR
RLLRRL
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
title: "Matching Reduction"
layout: "post"
diff: 省选/NOI-
pid: CF1721F
tag: ['网络流', '二分图']
---

# Matching Reduction

## 题目描述

You are given a bipartite graph with $ n_1 $ vertices in the first part, $ n_2 $ vertices in the second part, and $ m $ edges. The maximum matching in this graph is the maximum possible (by size) subset of edges of this graph such that no vertex is incident to more than one chosen edge.

You have to process two types of queries to this graph:

- $ 1 $ — remove the minimum possible number of vertices from this graph so that the size of the maximum matching gets reduced exactly by $ 1 $ , and print the vertices that you have removed. Then, find any maximum matching in this graph and print the sum of indices of edges belonging to this matching;
- $ 2 $ — query of this type will be asked only after a query of type $ 1 $ . As the answer to this query, you have to print the edges forming the maximum matching you have chosen in the previous query.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains four integers $ n_1 $ , $ n_2 $ , $ m $ and $ q $ ( $ 1 \le n_1, n_2 \le 2 \cdot 10^5 $ ; $ 1 \le m \le \min(n_1 \cdot n_2, 2 \cdot 10^5) $ ; $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ m $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i \le n_1 $ ; $ 1 \le y_i \le n_2 $ ) meaning that the $ i $ -th edge connects the vertex $ x_i $ in the first part and the vertex $ y_i $ in the second part. There are no pairs of vertices that are connected by more than one edge.

Then $ q $ lines follow. The $ i $ -th of them contains one integer, $ 1 $ or $ 2 $ , denoting the $ i $ -th query. Additional constraints on queries:

- the number of queries of type $ 1 $ won't exceed the size of the maximum matching in the initial graph;
- the number of queries of type $ 2 $ won't exceed $ 3 $ ;
- each query of type $ 2 $ is preceded by a query of type $ 1 $ ;
- your solution is allowed to read the $ i $ -th query only after printing the answer for the $ (i-1) $ -th query and flushing the output.

## 输出格式

For a query of type $ 1 $ , print the answer in three lines as follows:

- the first line should contain the number of vertices you remove;
- the second line should contain the indices of vertices you remove, as follows: if you remove the vertex $ x $ from the left part, print $ x $ ; if you remove the vertex $ y $ from the right part, print $ -y $ (negative index);
- the third line should contain the sum of indices of edges in some maximum matching in the resulting graph. The edges are numbered from $ 1 $ to $ m $ .

For a query of type $ 2 $ , print the answer in two lines as follows:

- the first line should contain the size of the maximum matching;
- the second line should contain the indices of the edges belonging to the maximum matching. Note that the sum of these indices should be equal to the number you printed at the end of the previous query of type $ 1 $ ;

After printing the answer to a query, don't forget to flush the output.

## 说明/提示

In this problem, you may receive the verdict "Idleness Limit Exceeded" since it is in online mode. If it happens, it means that either the output format is wrong, or you don't meet some constraint of the problem. You may treat this verdict as "Wrong Answer".

For your convenience, the output for queries in the example is separated by the line ===. Don't print this line in your program, it is done only to make sure that it's easy to distinguish between answers for different queries in the statement.

## 样例 #1

### 输入

```
3 4 4 4
2 2
1 3
2 1
3 4
1
2
1
2
```

### 输出

```
1
-4
3
===
2
1 2
===
1
2
2
===
1
2
```



---

---
title: "Double Sort II"
layout: "post"
diff: 省选/NOI-
pid: CF1783F
tag: ['网络流', '二分图']
---

# Double Sort II

## 题目描述

You are given two permutations $ a $ and $ b $ , both of size $ n $ . A permutation of size $ n $ is an array of $ n $ elements, where each integer from $ 1 $ to $ n $ appears exactly once. The elements in each permutation are indexed from $ 1 $ to $ n $ .

You can perform the following operation any number of times:

- choose an integer $ i $ from $ 1 $ to $ n $ ;
- let $ x $ be the integer such that $ a_x = i $ . Swap $ a_i $ with $ a_x $ ;
- let $ y $ be the integer such that $ b_y = i $ . Swap $ b_i $ with $ b_y $ .

Your goal is to make both permutations sorted in ascending order (i. e. the conditions $ a_1 < a_2 < \dots < a_n $ and $ b_1 < b_2 < \dots < b_n $ must be satisfied) using minimum number of operations. Note that both permutations must be sorted after you perform the sequence of operations you have chosen.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ; all $ a_i $ are distinct).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ; all $ b_i $ are distinct).

## 输出格式

First, print one integer $ k $ ( $ 0 \le k \le 2n $ ) — the minimum number of operations required to sort both permutations. Note that it can be shown that $ 2n $ operations are always enough.

Then, print $ k $ integers $ op_1, op_2, \dots, op_k $ ( $ 1 \le op_j \le n $ ), where $ op_j $ is the value of $ i $ you choose during the $ j $ -th operation.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
5
1 3 2 4 5
2 1 3 4 5
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
2
1 2
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
1 3 4 2
4 3 2 1
```

### 输出

```
2
3 4
```



---

---
title: "Contingency Plan 2"
layout: "post"
diff: 省选/NOI-
pid: CF1906I
tag: ['二分图']
---

# Contingency Plan 2

## 题目描述

You are working as a manager in The ICPC Company. In the company building, there are $ N $ computers (numbered from $ 1 $ to $ N $ ). There are $ N - 1 $ cables, numbered from $ 1 $ to $ N - 1 $ , that connect all the computers into a single network. Cable $ i $ connects computer $ U_i $ and $ V_i $ . Each cable can be set into emergency mode, where cable $ i $ only transfers data from computer $ U_i $ to computer $ V_i $ , but not the other way around. During a disaster, it is mandatory for all cables to be in emergency mode.

Through your research, you discover a new way to determine the vulnerability of a network. You want to add zero or more new cables to the current network such that it is not vulnerable during a disaster. Your network is not vulnerable if and only if there is exactly one permutation of $ 1 $ to $ N $ such that $ u $ appears before $ v $ in the permutation for all cables that connect computer $ u $ and $ v $ . In other words, it should have exactly one topological order.

The following illustration shows examples of not vulnerable networks and vulnerable networks.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906I/ff9330023f2ecf78266212977dcfc3bc8b6c375c.png)For the not vulnerable networks, the only permutation that satisfies the requirement for the networks on the left and on the right are $ [1, 2, 3] $ and $ [3, 1, 2] $ , respectively. Meanwhile, for the vulnerable networks, there are $ 2 $ permutations that satisfy the requirement for the network on the left: $ [1, 2, 3] $ and $ [3, 1, 2] $ ; while there is no permutation that satisfies the requirement for the network on the right.

You are interested in the minimum number of new cables that should be added to the current network such that it is not vulnerable during a disaster. Furthermore, you want to know, which pairs of computers should be connected by using the minimum number of cables. If there are several ways to connect, you can connect in any way of your choice. Under the given constraints, it can be proven that there exists a way to make the network not vulnerable.

## 输入格式

The first line consists of an integer $ N $ ( $ 2 \leq N \leq 100\,000 $ ).

Each of the next $ N - 1 $ lines consists of two integers $ U_i $ $ V_i $ ( $ 1 \leq U_i, V_i \leq N $ ). The input edges form a tree.

## 输出格式

The first line consists of an integer, representing the minimum number of new cables that should be added to the current network such that it is no longer vulnerable during a disaster. Denote this number as $ K $ and the new cables are numbered from $ 1 $ to $ K $ .

If $ K $ is not $ 0 $ , then output $ K $ lines. Each of the next $ K $ lines consists of two integers $ A_i $ $ B_i $ , representing the computers that are connected by the new cable $ i $ . During a disaster, new cable $ i $ only transfers data from computer $ A_i $ to computer $ B_i $ , but not the other way around. If there exist several solutions, you can output any of them.

## 说明/提示

Explanation for the sample input/output #3

The following illustration shows the original network and the new network with the added cables during a disaster. The only permutation that satisfies the requirement is $ [1, 2, 3, 4, 5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906I/9707ade040aa4f162ed2448ef1274e451a9777c6.png)

## 样例 #1

### 输入

```
3
1 2
3 2
```

### 输出

```
1
3 1
```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 2
1 3
3 4
3 5
```

### 输出

```
2
2 3
4 5
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
title: "Desk Disorder"
layout: "post"
diff: 省选/NOI-
pid: CF859E
tag: ['二分图', '概率论']
---

# Desk Disorder

## 题目描述

A new set of desks just arrived, and it's about time! Things were getting quite cramped in the office. You've been put in charge of creating a new seating chart for the engineers. The desks are numbered, and you sent out a survey to the engineering team asking each engineer the number of the desk they currently sit at, and the number of the desk they would like to sit at (which may be the same as their current desk). Each engineer must either remain where they sit, or move to the desired seat they indicated in the survey. No two engineers currently sit at the same desk, nor may any two engineers sit at the same desk in the new seating arrangement.

How many seating arrangements can you create that meet the specified requirements? The answer may be very large, so compute it modulo $ 1000000007=10^{9}+7 $ .

## 输入格式

Input will begin with a line containing $ N $ ( $ 1<=N<=100000 $ ), the number of engineers.

 $ N $ lines follow, each containing exactly two integers. The $ i $ -th line contains the number of the current desk of the $ i $ -th engineer and the number of the desk the $ i $ -th engineer wants to move to. Desks are numbered from $ 1 $ to $ 2·N $ . It is guaranteed that no two engineers sit at the same desk.

## 输出格式

Print the number of possible assignments, modulo $ 1000000007=10^{9}+7 $ .

## 说明/提示

These are the possible assignments for the first example:

- 1 5 3 7
- 1 2 3 7
- 5 2 3 7
- 1 5 7 3
- 1 2 7 3
- 5 2 7 3

## 样例 #1

### 输入

```
4
1 5
5 2
3 7
7 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
1 10
2 10
3 10
4 10
5 5

```

### 输出

```
5

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

