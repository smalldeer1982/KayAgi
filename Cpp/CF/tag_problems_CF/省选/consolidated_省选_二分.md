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
title: "Magnets"
layout: "post"
diff: 省选/NOI-
pid: CF1491F
tag: ['二分', '构造']
---

# Magnets

## 题目描述

This is an interactive problem.

Kochiya Sanae is playing with magnets. Realizing that some of those magnets are demagnetized, she is curious to find them out.

There are $ n $ magnets, which can be of the following $ 3 $ types:

- N
- S
- - — these magnets are demagnetized.

Note that you don't know the types of these magnets beforehand.

You have a machine which can measure the force between the magnets, and you can use it at most $ n+\lfloor \log_2n\rfloor $ times.

You can put some magnets to the left part of the machine and some to the right part of the machine, and launch the machine. Obviously, you can put one magnet to at most one side (you don't have to put all magnets). You can put the same magnet in different queries.

Then the machine will tell the force these magnets produce. Formally, let $ n_1,s_1 $ be the number of N and S magnets correspondently on the left and $ n_2,s_2 $ — on the right. Then the force between them would be $ n_1n_2+s_1s_2-n_1s_2-n_2s_1 $ . Please note that the force is a signed value.

However, when the absolute value of the force is strictly larger than $ n $ , the machine will crash into pieces.

You need to find all magnets of type - (all demagnetized ones), without breaking the machine.

Note that the interactor is not adaptive. The types of the magnets are fixed before the start of the interaction and do not change with queries.

It is guaranteed that there are at least $ 2 $ magnets whose type is not -, and at least $ 1 $ magnet of type -.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

## 输出格式

For each test case you should start by reading an integer $ n $ ( $ 3 \leq n \leq 2000 $ ) — the number of the magnets.

It is guaranteed that the total sum of all $ n $ over all test cases doesn't exceed $ 2000 $ .

After that you can put some magnets into the machine and make a query from the statement.

You have to print each query in three lines:

- In the first line print "? l r" (without quotes) where $ l $ and $ r $ ( $ 1 \leq l,r < n $ , $ l+r \leq n $ ) respectively denote the number of the magnets you put to left and right.
- In the second line print $ l $ integers $ a_1, \dots, a_l $ ( $ 1 \leq a_i \leq n $ , $ a_i \neq a_j $ if $ i \neq j $ ) — the indices of the magnets you put to left.
- In the third line print $ r $ integers $ b_1, \dots, b_r $ ( $ 1 \leq b_i \leq n $ , $ b_i \neq b_j $ if $ i \neq j $ ) — the indices of the magnets you put to right.
- The same magnet can't be put to both sides in the same query. Formally, you should guarantee that $ a_i \neq b_j $ for any $ i $ and $ j $ . However, you may leave some magnets unused.

After printing a query do not forget to output end of line and flush the output. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

After this, you should read an integer $ F $ — the force these magnets produce.

Note that if your query is invalid(either the query limit exceeds, the machine crashes or the arguments are invalid), the interactor will terminate immediately. In this case terminate your program to receive verdict Wrong Answer instead of arbitrary verdicts.

If you are confident about your answer, use the following format to report it:

- "! k A", where $ k $ is the number of magnets you found, and $ A $ is an array consisting of $ k $ different integers from $ 1 $ to $ n $ denoting the indices of the magnets of type - that you found. You may print elements of $ A $ in arbitrary order.
- After that, if this is the last test case, you have to terminate your program; otherwise you should immediately continue to deal with the next test case.

Note that the interactor is not adaptive. The types of the magnets are fixed before the start of interaction and do not change with queries.

Hacks

To hack a solution, use the following format:

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases in your hack.

Then follow the descriptions of the $ t $ test cases, each printed in two lines:

- The first line contains a single integer $ n $ ( $ 3 \leq n \leq 2000 $ ) — the number of magnets.
- The second line contains a string $ S $ of length $ n $ consisting of only N, S and -, denoting the magnets' types.
- Each of your test case should guarantee that there are at least $ 2 $ magnets whose type is not -, and at least $ 1 $ magnet of type -. Meanwhile, the total sum of $ n $ in all test cases should not exceed $ 2000 $ .

## 说明/提示

The empty lines in the sample are just for you to better understand the interaction process. You're not required to print them.

In the sample, the types of the magnets are NN--.

At first, you put the third magnet on the left and the fourth one on the right. Both of them have type -, thus no force is produced.

Then you put the first magnet on the left and the second and third one on the right. The third magnet has type -, while the other two magnets are of type N, so the force produced is $ 1 $ .

In the following two queries, the force is $ 0 $ since there is only a magnet with property - on the right.

Then we can determine that the magnets of type - are the third and the fourth one, so we should print ! 2 3 4 and exit.

## 样例 #1

### 输入

```
1
4



0



1



0



0
```

### 输出

```
? 1 1
3
4

? 1 2
1
2 3

? 1 1
1
4

? 1 1
1
3

! 2 3 4
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
title: "Doremy's Perfect DS Class (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1764G1
tag: ['二分']
---

# Doremy's Perfect DS Class (Easy Version)

## 题目描述

The only difference between this problem and the other two versions is the maximum number of queries. In this version, you are allowed to ask at most $ \mathbf{30} $ queries. You can make hacks only if all versions of the problem are solved.

This is an interactive problem.

"Everybody! Doremy's Perfect Data Structure Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's Data Structure class, Doremy is teaching everyone a powerful data structure — Doremy tree! Now she gives you a quiz to prove that you are paying attention in class.

Given an array $ a $ of length $ m $ , Doremy tree supports the query $ Q(l,r,k) $ , where $ 1 \leq l \leq r \leq m $ and $ 1 \leq k \leq m $ , which returns the number of distinct integers in the array $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ .

Doremy has a secret permutation $ p $ of integers from $ 1 $ to $ n $ . You can make queries, in one query, you give $ 3 $ integers $ l,r,k $ ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ ) and receive the value of $ Q(l,r,k) $ for the array $ p $ . Can you find the index $ y $ ( $ 1 \leq y \leq n $ ) such that $ p_y=1 $ in at most $ \mathbf{30} $ queries?

Note that the permutation $ p $ is fixed before any queries are made.

## 输出格式

You begin the interaction by reading an integer $ n $ ( $ 3 \le n \le 1024 $ ) in the first line — the length of the permutation.

To make a query, you should output

- "? $ l\ r\ k $ " ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ )

 in a separate line. After each query, you should read an integer $ x $ — the value of $ Q(l,r,k) $ for $ p $ . In this version of the problem, you can make at most $ 30 $ such queries.To give the answer, you should output

- "! $ y $ " ( $ 1 \leq y \leq n $ )

 in a separate line, where $ p_y=1 $ .After printing a query or the answer, do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks Format

The first line of the hack contains an integer $ n $ ( $ 3 \le n \le 1024 $ ) — the length of the permutation.

The second line of the hack contains $ n $ distinct integers $ p_1,p_2,\ldots,p_n $ ( $ 1 \le p_i\le n $ ) — the permutation.

## 说明/提示

The permutation in the example is $ [3,5,2,1,4] $ .

The input and output for example illustrate possible interaction on that test (empty lines are inserted only for clarity).

In this interaction process:

- For the first query, $ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $ , so the answer is $ 2 $ .
- For the second query, $ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $ , so the answer is still $ 2 $ .
- For the third query, $ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $ , so the answer is $ 1 $ .
- For the fourth query, $ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $ , so the answer is $ 3 $ .

The correct answer is got after $ 4 $ queries, so this process will be judged correct.

## 样例 #1

### 输入

```
5

2

2

1

3
```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4
```



---

---
title: "Doremy's Perfect DS Class (Medium Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1764G2
tag: ['二分']
---

# Doremy's Perfect DS Class (Medium Version)

## 题目描述

The only difference between this problem and the other two versions is the maximum number of queries. In this version, you are allowed to ask at most $ \mathbf{25} $ queries. You can make hacks only if all versions of the problem are solved.

This is an interactive problem.

"Everybody! Doremy's Perfect Data Structure Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's Data Structure class, Doremy is teaching everyone a powerful data structure — Doremy tree! Now she gives you a quiz to prove that you are paying attention in class.

Given an array $ a $ of length $ m $ , Doremy tree supports the query $ Q(l,r,k) $ , where $ 1 \leq l \leq r \leq m $ and $ 1 \leq k \leq m $ , which returns the number of distinct integers in the array $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ .

Doremy has a secret permutation $ p $ of integers from $ 1 $ to $ n $ . You can make queries, in one query, you give $ 3 $ integers $ l,r,k $ ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ ) and receive the value of $ Q(l,r,k) $ for the array $ p $ . Can you find the index $ y $ ( $ 1 \leq y \leq n $ ) such that $ p_y=1 $ in at most $ \mathbf{25} $ queries?

Note that the permutation $ p $ is fixed before any queries are made.

## 输出格式

You begin the interaction by reading an integer $ n $ ( $ 3 \le n \le 1024 $ ) in the first line — the length of the permutation.

To make a query, you should output

- "? $ l\ r\ k $ " ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ )

 in a separate line. After each query, you should read an integer $ x $ — the value of $ Q(l,r,k) $ for $ p $ . In this version of the problem, you can make at most $ 25 $ such queries.To give the answer, you should output

- "! $ y $ " ( $ 1 \leq y \leq n $ )

 in a separate line, where $ p_y=1 $ .After printing a query or the answer, do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks Format

The first line of the hack contains an integer $ n $ ( $ 3 \le n \le 1024 $ ) — the length of the permutation.

The second line of the hack contains $ n $ distinct integers $ p_1,p_2,\ldots,p_n $ ( $ 1 \le p_i\le n $ ) — the permutation.

## 说明/提示

The permutation in the example is $ [3,5,2,1,4] $ .

The input and output for example illustrate possible interaction on that test (empty lines are inserted only for clarity).

In this interaction process:

- For the first query, $ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $ , so the answer is $ 2 $ .
- For the second query, $ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $ , so the answer is still $ 2 $ .
- For the third query, $ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $ , so the answer is $ 1 $ .
- For the fourth query, $ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $ , so the answer is $ 3 $ .

The correct answer is got after $ 4 $ queries, so this process will be judged correct.

## 样例 #1

### 输入

```
5

2

2

1

3
```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4
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
title: "Segmentation Folds"
layout: "post"
diff: 省选/NOI-
pid: CF2041F
tag: ['二分', '素数判断,质数,筛法', '双指针 two-pointer']
---

# Segmentation Folds

## 题目描述

Peter 喜欢折线段玩。有一条线段位于数轴上的区间 $[\ell, r]$。现如今正是折叠线段的好时机，Peter 决定小心翼翼地对这条线段进行折叠。每次操作中，他可以选择以下两种方式之一（在可能的情况下）：

1. 操作 $\tt{LTR}$：他从左向右折线段，使得左端点 $\ell$ 与某个点 $x$ 重合（$\ell < x \le r$），并且 $\ell + x$ 是质数。当他选择此操作时，总是选取最大的 $x$ 值。折叠后，线段所在的区间变为 $[\frac{1}{2}(\ell + x), r]$。
   
2. 操作 $\tt{RTL}$：他从右向左折线段，使得右端点 $r$ 与某个点 $x$ 重合（$\ell \le x < r$），并且 $r + x$ 是质数。当他选择此操作时，总是选取最小的 $x$ 值。折叠后，线段所在的区间变为 $[\ell, \frac{1}{2}(r + x)]$。

一个折叠序列是指这两种操作的组合。Peter 想要通过多次折叠，使线段的长度尽可能短，且无法再缩短。区间的长度自然定义为 $r - \ell$。考虑以下例子：假设我们折叠一段初始为 $[1, 30]$ 的线段。有三种折叠方式能使最终区间长度最短，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041F/be032bc113ac39f401b84d34f2c5f31947b110d1.png)

请你帮助 Peter 确定有多少种不同的折叠序列可以使线段达到最短长度。结果需要对 $998244353$ 取模。

注：一个大于 $1$ 的整数 $p$ 是质数，当且仅当不存在整数 $a, b > 1$ 使得 $p = ab$。

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量。接下来的 $t$ 行中，每行包含两个整数 $\ell$ 和 $r$。

- $1 \le t \le 10$
- $1 \le \ell < r \le 10^{12}$
- $r - \ell \le 10^5$

## 输出格式

对于每个测试用例，输出一行，表示能将给定线段折叠到最短长度的折叠序列数量，结果对 $998244353$ 取模。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1 30
16 18
142857 240135
```

### 输出

```
3
1
63
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
title: "Numbers and Strings"
layout: "post"
diff: 省选/NOI-
pid: CF2104F
tag: ['二分', '数位 DP']
---

# Numbers and Strings

## 题目描述

对于每个从 $1$ 到 $n$ 的整数 $x$，我们将按照以下规则生成字符串 $S(x)$：

- 计算 $x+1$；
- 将 $x$ 和 $x+1$ 在十进制表示下无分隔符、无前导零地拼接在一起；
- 将得到的字符串中的所有数字按非递减顺序排序。

例如，字符串 $S(139)$ 是 `011349`（排序前的拼接结果是 `139140`）。字符串 $S(99)$ 是 `00199`。

你的任务是统计 $S(1), S(2), \dots, S(n)$ 中不同字符串的数量。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

每个测试用例由一行组成，包含一个整数 $n$（$1 \le n \le 10^{9} - 2$）。

## 输出格式

对于每个测试用例，输出一个整数，表示表示不同的字符串数量。

## 样例 #1

### 输入

```
2
42
1337
```

### 输出

```
42
948
```



---

---
title: "Fallen Towers"
layout: "post"
diff: 省选/NOI-
pid: CF2108F
tag: ['二分']
---

# Fallen Towers

## 题目描述

Pizano 建造了一个由 $n$ 座高塔组成的数组 $a$，每座高塔由 $a_i \ge 0$ 个方块组成。

Pizano 可以推倒一座高塔，使得接下来的 $a_i$ 座高塔各增加 $1$ 个方块。换句话说，他可以选取元素 $a_i$，将接下来的 $a_i$ 个元素各加 $1$，然后将 $a_i$ 设为 $0$。如果推倒的高塔方块数超出数组范围，则这些方块会消失。如果 Pizano 推倒一座 $0$ 方块的高塔，则不会发生任何变化。

Pizano 希望以任意顺序推倒所有 $n$ 座高塔，每座高塔恰好被推倒一次。也就是说，对于每个 $i$ 从 $1$ 到 $n$，他将恰好推倒位置 $i$ 的高塔一次。

此外，最终的高塔高度数组必须是非递减的。这意味着在他推倒所有 $n$ 座高塔后，对于任意 $i < j$，位置 $i$ 的高塔高度不能超过位置 $j$ 的高塔高度。

你需要输出最终高塔高度数组的最大 $\text{MEX}$ 值。

$\text{MEX}$ 是指数组中缺失的最小非负整数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 10^5$）——高塔的数量。

每个测试用例的第二行包含 $n$ 个整数——高塔的初始高度 $a_1, \ldots, a_n$（$0 \leq a_i \leq 10^9$）。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数——最终数组的最大 $\text{MEX}$ 值。


## 说明/提示

第一个测试用例的解释：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108F/aa04335da43131aa6a37290f90705cf6ef46ee3d.png)

第二个测试用例的解释：注意所有高塔都被恰好推倒一次，且最终的高度数组是非递减的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108F/93831ffd87d4f17502d74b13db29c4368e8cf0f9.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
1 2
4
2 1 0 0
10
5 9 3 7 1 5 1 5 4 3
10
1 1 1 1 1 1 1 1 1 1
10
3 2 1 0 3 2 1 0 3 2
5
5 2 0 5 5
1
1000000000
7
4 0 1 0 2 7 7
```

### 输出

```
2
3
7
4
5
4
1
3
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
title: "Ciel and Gondolas"
layout: "post"
diff: 省选/NOI-
pid: CF321E
tag: ['动态规划 DP', '单调队列', '凸完全单调性（wqs 二分）']
---

# Ciel and Gondolas

## 题目描述

Fox Ciel is in the Amusement Park. And now she is in a queue in front of the Ferris wheel. There are $ n $ people (or foxes more precisely) in the queue: we use first people to refer one at the head of the queue, and $ n $ -th people to refer the last one in the queue.

There will be $ k $ gondolas, and the way we allocate gondolas looks like this:

- When the first gondolas come, the $ q_{1} $ people in head of the queue go into the gondolas.
- Then when the second gondolas come, the $ q_{2} $ people in head of the remain queue go into the gondolas. ...
- The remain $ q_{k} $ people go into the last ( $ k $ -th) gondolas.

Note that $ q_{1} $ , $ q_{2} $ , ..., $ q_{k} $ must be positive. You can get from the statement that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321E/5aa86331c628d3d47e29fa23648bea351737ffff.png) and $ q_{i}>0 $ .

You know, people don't want to stay with strangers in the gondolas, so your task is to find an optimal allocation way (that is find an optimal sequence $ q $ ) to make people happy. For every pair of people $ i $ and $ j $ , there exists a value $ u_{ij} $ denotes a level of unfamiliar. You can assume $ u_{ij}=u_{ji} $ for all $ i,j $ $ (1<=i,j<=n) $ and $ u_{ii}=0 $ for all $ i $ $ (1<=i<=n) $ . Then an unfamiliar value of a gondolas is the sum of the levels of unfamiliar between any pair of people that is into the gondolas.

A total unfamiliar value is the sum of unfamiliar values for all gondolas. Help Fox Ciel to find the minimal possible total unfamiliar value for some optimal allocation.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=4000 $ and $ 1<=k<=min(n,800) $ ) — the number of people in the queue and the number of gondolas. Each of the following $ n $ lines contains $ n $ integers — matrix $ u $ , ( $ 0<=u_{ij}<=9 $ , $ u_{ij}=u_{ji} $ and $ u_{ii}=0 $ ).

Please, use fast input methods (for example, please use BufferedReader instead of Scanner for Java).

## 输出格式

Print an integer — the minimal possible total unfamiliar value.

## 说明/提示

In the first example, we can allocate people like this: {1, 2} goes into a gondolas, {3, 4, 5} goes into another gondolas.

In the second example, an optimal solution is : {1, 2, 3} | {4, 5, 6} | {7, 8}.

## 样例 #1

### 输入

```
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0

```

### 输出

```
0

```

## 样例 #2

### 输入

```
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3 2
0 2 0
2 0 3
0 3 0

```

### 输出

```
2

```



---

---
title: "Dreamoon and Notepad"
layout: "post"
diff: 省选/NOI-
pid: CF477E
tag: ['模拟', '二分', 'ST 表', '分类讨论']
---

# Dreamoon and Notepad

## 题目描述

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输入格式

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输出格式

For each query print the result of the query.

## 说明/提示

In the first sample, the first query can be solved with keys: HOME, right.

The second query can be solved with keys: down, down, down, END, down.

The third query can be solved with keys: down, END, down.

The fourth query can be solved with keys: END, down.

## 样例 #1

### 输入

```
9
1 3 5 3 1 3 5 3 1
4
3 5 3 1
3 3 7 3
1 0 3 3
6 0 7 3

```

### 输出

```
2
5
3
2

```

## 样例 #2

### 输入

```
2
10 5
1
1 0 1 5

```

### 输出

```
3

```



---

---
title: "Mr. Kitayuta vs. Bamboos"
layout: "post"
diff: 省选/NOI-
pid: CF505E
tag: ['模拟', '二分']
---

# Mr. Kitayuta vs. Bamboos

## 题目描述

Mr. Kitayuta's garden is planted with $ n $ bamboos. (Bamboos are tall, fast-growing tropical plants with hollow stems.) At the moment, the height of the $ i $ -th bamboo is $ h_{i} $ meters, and it grows $ a_{i} $ meters at the end of each day.

Actually, Mr. Kitayuta hates these bamboos. He once attempted to cut them down, but failed because their stems are too hard. Mr. Kitayuta have not given up, however. He has crafted Magical Hammer with his intelligence to drive them into the ground.

He can use Magical Hammer at most $ k $ times during each day, due to his limited Magic Power. Each time he beat a bamboo with Magical Hammer, its height decreases by $ p $ meters. If the height would become negative by this change, it will become $ 0 $ meters instead (it does not disappear). In other words, if a bamboo whose height is $ h $ meters is beaten with Magical Hammer, its new height will be $ max(0,h-p) $ meters. It is possible to beat the same bamboo more than once in a day.

Mr. Kitayuta will fight the bamboos for $ m $ days, starting today. His purpose is to minimize the height of the tallest bamboo after $ m $ days (that is, $ m $ iterations of "Mr. Kitayuta beats the bamboos and then they grow"). Find the lowest possible height of the tallest bamboo after $ m $ days.

## 输入格式

The first line of the input contains four space-separated integers $ n $ , $ m $ , $ k $ and $ p $ ( $ 1<=n<=10^{5},1<=m<=5000,1<=k<=10,1<=p<=10^{9} $ ). They represent the number of the bamboos in Mr. Kitayuta's garden, the duration of Mr. Kitayuta's fight in days, the maximum number of times that Mr. Kitayuta beat the bamboos during each day, and the power of Magic Hammer, respectively.

The following $ n $ lines describe the properties of the bamboos. The $ i $ -th of them ( $ 1<=i<=n $ ) contains two space-separated integers $ h_{i} $ and $ a_{i} $ ( $ 0<=h_{i}<=10^{9},1<=a_{i}<=10^{9} $ ), denoting the initial height and the growth rate of the $ i $ -th bamboo, respectively.

## 输出格式

Print the lowest possible height of the tallest bamboo after $ m $ days.

## 样例 #1

### 输入

```
3 1 2 5
10 10
10 10
15 2

```

### 输出

```
17

```

## 样例 #2

### 输入

```
2 10 10 1000000000
0 10
0 10

```

### 输出

```
10

```

## 样例 #3

### 输入

```
5 3 3 10
9 5
9 2
4 7
9 10
3 8

```

### 输出

```
14

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
title: "Preorder Test"
layout: "post"
diff: 省选/NOI-
pid: CF627D
tag: ['二分', '深度优先搜索 DFS']
---

# Preorder Test

## 题目描述

For his computer science class, Jacob builds a model tree with sticks and balls containing $ n $ nodes in the shape of a tree. Jacob has spent $ a_{i} $ minutes building the $ i $ -th ball in the tree.

Jacob's teacher will evaluate his model and grade Jacob based on the effort he has put in. However, she does not have enough time to search his whole tree to determine this; Jacob knows that she will examine the first $ k $ nodes in a DFS-order traversal of the tree. She will then assign Jacob a grade equal to the minimum $ a_{i} $ she finds among those $ k $ nodes.

Though Jacob does not have enough time to rebuild his model, he can choose the root node that his teacher starts from. Furthermore, he can rearrange the list of neighbors of each node in any order he likes. Help Jacob find the best grade he can get on this assignment.

A DFS-order traversal is an ordering of the nodes of a rooted tree, built by a recursive DFS-procedure initially called on the root of the tree. When called on a given node $ v $ , the procedure does the following:

1. Print $ v $ .
2. Traverse the list of neighbors of the node $ v $ in order and iteratively call DFS-procedure on each one. Do not call DFS-procedure on node $ u $ if you came to node $ v $ directly from $ u $ .

## 输入格式

The first line of the input contains two positive integers, $ n $ and $ k $ ( $ 2<=n<=200000 $ , $ 1<=k<=n $ ) — the number of balls in Jacob's tree and the number of balls the teacher will inspect.

The second line contains $ n $ integers, $ a_{i} $ ( $ 1<=a_{i}<=1000000 $ ), the time Jacob used to build the $ i $ -th ball.

Each of the next $ n-1 $ lines contains two integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ u_{i}≠v_{i} $ ) representing a connection in Jacob's tree between balls $ u_{i} $ and $ v_{i} $ .

## 输出格式

Print a single integer — the maximum grade Jacob can get by picking the right root of the tree and rearranging the list of neighbors.

## 说明/提示

In the first sample, Jacob can root the tree at node $ 2 $ and order $ 2 $ 's neighbors in the order $ 4 $ , $ 1 $ , $ 5 $ (all other nodes have at most two neighbors). The resulting preorder traversal is $ 2 $ , $ 4 $ , $ 1 $ , $ 3 $ , $ 5 $ , and the minimum $ a_{i} $ of the first $ 3 $ nodes is $ 3 $ .

In the second sample, it is clear that any preorder traversal will contain node $ 1 $ as either its first or second node, so Jacob cannot do better than a grade of $ 1 $ .

## 样例 #1

### 输入

```
5 3
3 6 1 4 2
1 2
2 4
2 5
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 2
1 5 5 5
1 2
1 3
1 4

```

### 输出

```
1

```



---

---
title: "Bear and Tower of Cubes"
layout: "post"
diff: 省选/NOI-
pid: CF679B
tag: ['二分']
---

# Bear and Tower of Cubes

## 题目描述

Limak是一只可爱的北极熊。他正在用一堆木块搭塔。每一个木块都是一个有着正整数边长的正方体。Limak有无数块木块。显然的，每一块边长为$a$  的木块的体积为$a^3$  ，而一个塔的体积为组成这个塔的所有木块的体积和。**这里，我们定义一个塔的高度是组成这个塔的木块数量。**

Limak现在要搭建一个塔。首先，他让你告诉他一个正整数$X$  ，表示这个塔的总体积。然后，他将会贪心地搭建这个塔（每次总是尽可能地添加最大的木块，即先选一个体积最大的正方体作为第一层，第一层的体积满足体积不超过$X$  。然后选一个最大的正方体做第二层，使得前两层的体积和满足不超过$X$  。然后再选一个最大的正方体做第三层，使得前三层的体积和满足不超过$X$  。依次类推，直到建好一座体积为$X$  的塔）。

Limak想让你在$1$  - $m$  之间选择一个$X$  ，使他能够搭建的塔的总高度$h$  最高。同时，在总高度最高的情况下，让塔的总体积$X$  最大。

（实在没看懂题意可以看看样例解释）

## 输入格式

输入包含一行，一个正整数$m$  ，表示Limak想让你从$1$  到$m$  之间（包括$1$  和$m$  ）选择$X$  。

## 输出格式

请输出一行，包含两个正整数：$h$  ，表示可以搭建出的塔的最大高度，以及$X$  ，表示当$h$  最大时整个塔的最大体积。

# 输入输出样例

略

## 说明/提示

对于样例1，当$X=23$  或$X=42$  时$h$  有最大值为9。因为Limak想让你最大化塔的体积，所以应该选择42。

在选择$X=42$  之后，具体的建塔过程为：

> - 首先，Limak选择一块边长为3的木块，因为这是体积不超过42的最大木块。剩下的体积为$42-27=15$  。 
> - 然后，同样的，Limak会选择边长为2的木块，所以剩下的体积为$15-8=7$  。 
> - 最后，Limak放上7块边长为1的木块。  

所以，这座塔的高度为9，总体积为$3^3+2^3+7*1^3=27+8+7=42$  。

感谢@星烁晶熠辉 提供的翻译

## 样例 #1

### 输入

```
48

```

### 输出

```
9 42

```

## 样例 #2

### 输入

```
6

```

### 输出

```
6 6

```



---

---
title: "Gosha is hunting"
layout: "post"
diff: 省选/NOI-
pid: CF739E
tag: ['二分', '费用流', '期望']
---

# Gosha is hunting

## 题目描述

Gosha is hunting. His goal is to catch as many Pokemons as possible. Gosha has $ a $ Poke Balls and $ b $ Ultra Balls. There are $ n $ Pokemons. They are numbered $ 1 $ through $ n $ . Gosha knows that if he throws a Poke Ball at the $ i $ -th Pokemon he catches it with probability $ p_{i} $ . If he throws an Ultra Ball at the $ i $ -th Pokemon he catches it with probability $ u_{i} $ . He can throw at most one Ball of each type at any Pokemon.

The hunting proceeds as follows: at first, Gosha chooses no more than $ a $ Pokemons at which he will throw Poke Balls and no more than $ b $ Pokemons at which he will throw Ultra Balls. After that, he throws the chosen Balls at the chosen Pokemons. If he throws both Ultra Ball and Poke Ball at some Pokemon, he is caught if and only if he is caught by any of these Balls. The outcome of a throw doesn't depend on the other throws.

Gosha would like to know what is the expected number of the Pokemons he catches if he acts in an optimal way. In other words, he would like to know the maximum possible expected number of Pokemons can catch.

## 输入格式

The first line contains three integers $ n $ , $ a $ and $ b $ ( $ 2<=n<=2000 $ , $ 0<=a,b<=n $ ) — the number of Pokemons, the number of Poke Balls and the number of Ultra Balls.

The second line contains $ n $ real values $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=1 $ ), where $ p_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws a Poke Ball to it.

The third line contains $ n $ real values $ u_{1},u_{2},...,u_{n} $ ( $ 0<=u_{i}<=1 $ ), where $ u_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws an Ultra Ball to it.

All the probabilities are given with exactly three digits after the decimal separator.

## 输出格式

Print the maximum possible expected number of Pokemons Gosha can catch. The answer is considered correct if it's absolute or relative error doesn't exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
3 2 2
1.000 0.000 0.500
0.000 1.000 0.500

```

### 输出

```
2.75

```

## 样例 #2

### 输入

```
4 1 3
0.100 0.500 0.500 0.600
0.100 0.500 0.900 0.400

```

### 输出

```
2.16

```

## 样例 #3

### 输入

```
3 2 0
0.412 0.198 0.599
0.612 0.987 0.443

```

### 输出

```
1.011
```



---

---
title: "Till I Collapse"
layout: "post"
diff: 省选/NOI-
pid: CF786C
tag: ['二分', '根号分治']
---

# Till I Collapse

## 题目描述

Rick and Morty want to find MR. PBH and they can't do it alone. So they need of Mr. Meeseeks. They Have generated $ n $ Mr. Meeseeks, standing in a line numbered from $ 1 $ to $ n $ . Each of them has his own color. $ i $ -th Mr. Meeseeks' color is $ a_{i} $ .

Rick and Morty are gathering their army and they want to divide Mr. Meeseeks into some squads. They don't want their squads to be too colorful, so each squad should have Mr. Meeseeks of at most $ k $ different colors. Also each squad should be a continuous subarray of Mr. Meeseeks in the line. Meaning that for each $ 1<=i<=e<=j<=n $ , if Mr. Meeseeks number $ i $ and Mr. Meeseeks number $ j $ are in the same squad then Mr. Meeseeks number $ e $ should be in that same squad.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786C/f2b873f46d1ce1d5117f05fee6c23499da101533.png)Also, each squad needs its own presidio, and building a presidio needs money, so they want the total number of squads to be minimized.

Rick and Morty haven't finalized the exact value of $ k $ , so in order to choose it, for each $ k $ between $ 1 $ and $ n $ (inclusive) need to know the minimum number of presidios needed.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — number of Mr. Meeseeks.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ separated by spaces ( $ 1<=a_{i}<=n $ ) — colors of Mr. Meeseeks in order they standing in a line.

## 输出格式

In the first and only line of input print $ n $ integers separated by spaces. $ i $ -th integer should be the minimum number of presidios needed if the value of $ k $ is $ i $ .

## 说明/提示

For the first sample testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[3],[4],[3,3] $
2. $ [1],[3,4,3,3] $
3. $ [1,3,4,3,3] $
4. $ [1,3,4,3,3] $
5. $ [1,3,4,3,3] $

For the second testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[5],[7],[8],[1],[7],[6],[1] $
2. $ [1,5],[7,8],[1,7],[6,1] $
3. $ [1,5,7],[8],[1,7,6,1] $
4. $ [1,5,7,8],[1,7,6,1] $
5. $ [1,5,7,8,1,7,6,1] $
6. $ [1,5,7,8,1,7,6,1] $
7. $ [1,5,7,8,1,7,6,1] $
8. $ [1,5,7,8,1,7,6,1] $

## 样例 #1

### 输入

```
5
1 3 4 3 3

```

### 输出

```
4 2 1 1 1 

```

## 样例 #2

### 输入

```
8
1 5 7 8 1 7 6 1

```

### 输出

```
8 4 3 2 1 1 1 1 

```



---

---
title: "Selling Souvenirs"
layout: "post"
diff: 省选/NOI-
pid: CF808E
tag: ['动态规划 DP', '二分']
---

# Selling Souvenirs

## 题目描述

## 题目背景
Berland经过了多次改革后，许多游客打算来这儿游玩。居民们知道这是一个改行旅游服务业来赚钱的好机会，Petya也离开了他以前工作的IT公司，改在市场买礼品了。

像平常一样，今早Petya回来到市场。他有 $n$ 个不同的礼品要卖；第 $i$ 个礼品有重量 $w_{i}$ 和价格 $c_{i}$ 两个属性。Petya知道他不能把所有礼品扛到市场，便想要选一部分总重量不超过 $m$ 的礼品，而总价格越高越好。

帮帮Petya确定最大的总价格吧。

## 输入格式

第一行包括两个整数 $n$ 和 $m$（$1<=n<=100000$ , $1<=m<=300000$）——Petya的礼品数量和他能带去市场的最大重量。

然后下面$n$行中第$i$行各有两个整数 $w_{i}$  
和 $c_{i}$（$1<=w_{i}<=3$ , $1<=c_{i}<=10^{9}$）——第 $i$ 个礼品的重量和价格。

## 输出格式

输出一个数字——Petya能带去的礼品的最大总价格。

## 样例 #1

### 输入

```
1 1
2 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 2
1 3
2 2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4 3
3 10
2 7
2 8
1 1

```

### 输出

```
10

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
title: "Gotta Go Fast"
layout: "post"
diff: 省选/NOI-
pid: CF865C
tag: ['动态规划 DP', '二分', '期望']
---

# Gotta Go Fast

## 题目描述

You're trying to set the record on your favorite video game. The game consists of $ N $ levels, which must be completed sequentially in order to beat the game. You usually complete each level as fast as possible, but sometimes finish a level slower. Specifically, you will complete the $ i $ -th level in either $ F_{i} $ seconds or $ S_{i} $ seconds, where $ F_{i}&lt;S_{i} $ , and there's a $ P_{i} $ percent chance of completing it in $ F_{i} $ seconds. After completing a level, you may decide to either continue the game and play the next level, or reset the game and start again from the first level. Both the decision and the action are instant.

Your goal is to complete all the levels sequentially in at most $ R $ total seconds. You want to minimize the expected amount of time playing before achieving that goal. If you continue and reset optimally, how much total time can you expect to spend playing?

## 输入格式

The first line of input contains integers $ N $ and $ R $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/2edb953537ce7c8db1b280cf3e041068762c4830.png), the number of levels and number of seconds you want to complete the game in, respectively. $ N $ lines follow. The $ i $ th such line contains integers $ F_{i},S_{i},P_{i} $ $ (1<=F_{i}&lt;S_{i}<=100,80<=P_{i}<=99) $ , the fast time for level $ i $ , the slow time for level $ i $ , and the probability (as a percentage) of completing level $ i $ with the fast time.

## 输出格式

Print the total expected time. Your answer must be correct within an absolute or relative error of $ 10^{-9} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer will be considered correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/cde5c1e0715ef65086b3065853dd22ee5a37eede.png).

## 说明/提示

In the first example, you never need to reset. There's an $ 81% $ chance of completing the level in $ 2 $ seconds and a $ 19% $ chance of needing $ 8 $ seconds, both of which are within the goal time. The expected time is $ 0.81·2+0.19·8=3.14 $ .

In the second example, you should reset after the first level if you complete it slowly. On average it will take $ 0.25 $ slow attempts before your first fast attempt. Then it doesn't matter whether you complete the second level fast or slow. The expected time is $ 0.25·30+20+0.85·3+0.15·9=31.4 $ .

## 样例 #1

### 输入

```
1 8
2 8 81

```

### 输出

```
3.14

```

## 样例 #2

### 输入

```
2 30
20 30 80
3 9 85

```

### 输出

```
31.4

```

## 样例 #3

### 输入

```
4 319
63 79 89
79 97 91
75 87 88
75 90 83

```

### 输出

```
314.159265358

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
title: "Prime Gift"
layout: "post"
diff: 省选/NOI-
pid: CF912E
tag: ['搜索', '二分', '素数判断,质数,筛法']
---

# Prime Gift

## 题目描述

Opposite to Grisha's nice behavior, Oleg, though he has an entire year at his disposal, didn't manage to learn how to solve number theory problems in the past year. That's why instead of Ded Moroz he was visited by his teammate Andrew, who solemnly presented him with a set of $ n $ distinct prime numbers alongside with a simple task: Oleg is to find the $ k $ -th smallest integer, such that all its prime divisors are in this set.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=16 $ ).

The next line lists $ n $ distinct prime numbers $ p_{1},p_{2},...,p_{n} $ ( $ 2<=p_{i}<=100 $ ) in ascending order.

The last line gives a single integer $ k $ ( $ 1<=k $ ). It is guaranteed that the $ k $ -th smallest integer such that all its prime divisors are in this set does not exceed $ 10^{18} $ .

## 输出格式

Print a single line featuring the $ k $ -th smallest integer. It's guaranteed that the answer doesn't exceed $ 10^{18} $ .

## 说明/提示

The list of numbers with all prime divisors inside $ {2,3,5} $ begins as follows:

 $ (1,2,3,4,5,6,8,...) $

The seventh number in this list ( $ 1 $ -indexed) is eight.

## 样例 #1

### 输入

```
3
2 3 5
7

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5
3 7 11 13 31
17

```

### 输出

```
93

```



---

---
title: "List Of Integers"
layout: "post"
diff: 省选/NOI-
pid: CF920G
tag: ['二分', '枚举', '容斥原理']
---

# List Of Integers

## 题目描述

Let's denote as $ L(x,p) $ an infinite sequence of integers $ y $ such that $ gcd(p,y)=1 $ and $ y>x $ (where $ gcd $ is the greatest common divisor of two integer numbers), sorted in ascending order. The elements of $ L(x,p) $ are $ 1 $ -indexed; for example, $ 9 $ , $ 13 $ and $ 15 $ are the first, the second and the third elements of $ L(7,22) $ , respectively.

You have to process $ t $ queries. Each query is denoted by three integers $ x $ , $ p $ and $ k $ , and the answer to this query is $ k $ -th element of $ L(x,p) $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=30000 $ ) — the number of queries to process.

Then $ t $ lines follow. $ i $ -th line contains three integers $ x $ , $ p $ and $ k $ for $ i $ -th query ( $ 1<=x,p,k<=10^{6} $ ).

## 输出格式

Print $ t $ integers, where $ i $ -th integer is the answer to $ i $ -th query.

## 样例 #1

### 输入

```
3
7 22 1
7 22 2
7 22 3

```

### 输出

```
9
13
15

```

## 样例 #2

### 输入

```
5
42 42 42
43 43 43
44 44 44
45 45 45
46 46 46

```

### 输出

```
187
87
139
128
141

```



---

---
title: "Round Marriage"
layout: "post"
diff: 省选/NOI-
pid: CF981F
tag: ['二分', '枚举', '构造']
---

# Round Marriage

## 题目描述

It's marriage season in Ringland!

Ringland has a form of a circle's boundary of length $ L $ . There are $ n $ bridegrooms and $ n $ brides, and bridegrooms decided to marry brides.

Of course, each bridegroom should choose exactly one bride, and each bride should be chosen by exactly one bridegroom.

All objects in Ringland are located on the boundary of the circle, including the capital, bridegrooms' castles and brides' palaces. The castle of the $ i $ -th bridegroom is located at the distance $ a_i $ from the capital in clockwise direction, and the palace of the $ i $ -th bride is located at the distance $ b_i $ from the capital in clockwise direction.

Let's define the inconvenience of a marriage the maximum distance that some bride should walk along the circle from her palace to her bridegroom's castle in the shortest direction (in clockwise or counter-clockwise direction).

Help the bridegrooms of Ringland to choose brides in such a way that the inconvenience of the marriage is the smallest possible.

## 输入格式

The first line contains two integers $ n $ and $ L $ ( $ 1 \leq n \leq 2 \cdot 10^{5} $ , $ 1 \leq L \leq 10^{9} $ ) — the number of bridegrooms and brides and the length of Ringland.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < L $ ) — the distances from the capital to the castles of bridegrooms in clockwise direction.

The next line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < L $ ) — the distances from the capital to the palaces of brides in clockwise direction.

## 输出格式

In the only line print the smallest possible inconvenience of the wedding, where the inconvenience is the largest distance traveled by a bride.

## 说明/提示

In the first example the first bridegroom should marry the second bride, the second bridegroom should marry the first bride. This way, the second bride should walk the distance of $ 1 $ , and the first bride should also walk the same distance. Thus, the inconvenience is equal to $ 1 $ .

In the second example let $ p_i $ be the bride the $ i $ -th bridegroom will marry. One of optimal $ p $ is the following: $ (6,8,1,4,5,10,3,2,7,9) $ .

## 样例 #1

### 输入

```
2 4
0 1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 100
3 14 15 92 65 35 89 79 32 38
2 71 82 81 82 84 5 90 45 23

```

### 输出

```
27

```



---

