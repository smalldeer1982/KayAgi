---
title: "Space Isaac"
layout: "post"
diff: 提高+/省选-
pid: CF1045B
tag: ['字符串', '枚举', '位运算']
---

# Space Isaac

## 题目描述

Everybody seems to think that the Martians are green, but it turns out they are metallic pink and fat. Ajs has two bags of distinct nonnegative integers. The bags are disjoint, and the union of the sets of numbers in the bags is $ \{0,1,…,M-1\} $ , for some positive integer $ M $ . Ajs draws a number from the first bag and a number from the second bag, and then sums them modulo $ M $ .

What are the residues modulo $ M $ that Ajs cannot obtain with this action?

## 输入格式

The first line contains two positive integer $ N $ ( $ 1 \leq N \leq 200\,000 $ ) and $ M $ ( $ N+1 \leq M \leq 10^{9} $ ), denoting the number of the elements in the first bag and the modulus, respectively.

The second line contains $ N $ nonnegative integers $ a_1,a_2,\ldots,a_N $ ( $ 0 \leq a_1<a_2< \ldots< a_N<M $ ), the contents of the first bag.

## 输出格式

In the first line, output the cardinality $ K $ of the set of residues modulo $ M $ which Ajs cannot obtain.

In the second line of the output, print $ K $ space-separated integers greater or equal than zero and less than $ M $ , which represent the residues Ajs cannot obtain. The outputs should be sorted in increasing order of magnitude. If $ K $ =0, do not output the second line.

## 说明/提示

In the first sample, the first bag and the second bag contain $ \{3,4\} $ and $ \{0,1,2\} $ , respectively. Ajs can obtain every residue modulo $ 5 $ except the residue $ 2 $ : $  4+1 \equiv 0, \, 4+2 \equiv 1, \, 3+0 \equiv 3, \, 3+1 \equiv 4  $ modulo $ 5 $ . One can check that there is no choice of elements from the first and the second bag which sum to $ 2 $ modulo $ 5 $ .

In the second sample, the contents of the first bag are $ \{5,25,125,625\} $ , while the second bag contains all other nonnegative integers with at most $ 9 $ decimal digits. Every residue modulo $ 1\,000\,000\,000 $ can be obtained as a sum of an element in the first bag and an element in the second bag.

## 样例 #1

### 输入

```
2 5
3 4

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
4 1000000000
5 25 125 625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 4
1 3

```

### 输出

```
2
0 2

```



---

---
title: "AND-MEX Walk"
layout: "post"
diff: 提高+/省选-
pid: CF1659E
tag: ['图论', '并查集', '位运算']
---

# AND-MEX Walk

## 题目描述

There is an undirected, connected graph with $ n $ vertices and $ m $ weighted edges. A walk from vertex $ u $ to vertex $ v $ is defined as a sequence of vertices $ p_1,p_2,\ldots,p_k $ (which are not necessarily distinct) starting with $ u $ and ending with $ v $ , such that $ p_i $ and $ p_{i+1} $ are connected by an edge for $ 1 \leq i < k $ .

We define the length of a walk as follows: take the ordered sequence of edges and write down the weights on each of them in an array. Now, write down the bitwise AND of every nonempty prefix of this array. The length of the walk is the MEX of all these values.

More formally, let us have $ [w_1,w_2,\ldots,w_{k-1}] $ where $ w_i $ is the weight of the edge between $ p_i $ and $ p_{i+1} $ . Then the length of the walk is given by $ \mathrm{MEX}(\{w_1,\,w_1\& w_2,\,\ldots,\,w_1\& w_2\& \ldots\& w_{k-1}\}) $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Now you must process $ q $ queries of the form u v. For each query, find the minimum possible length of a walk from $ u $ to $ v $ .

The MEX (minimum excluded) of a set is the smallest non-negative integer that does not belong to the set. For instance:

- The MEX of $ \{2,1\} $ is $ 0 $ , because $ 0 $ does not belong to the set.
- The MEX of $ \{3,1,0\} $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the set, but $ 2 $ does not.
- The MEX of $ \{0,3,1,2\} $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the set, but $ 4 $ does not.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^5 $ ; $ n-1 \leq m \leq \min{\left(\frac{n(n-1)}{2},10^5\right)} $ ).

Each of the next $ m $ lines contains three integers $ a $ , $ b $ , and $ w $ ( $ 1 \leq a, b \leq n $ , $ a \neq b $ ; $ 0 \leq w < 2^{30} $ ) indicating an undirected edge between vertex $ a $ and vertex $ b $ with weight $ w $ . The input will not contain self-loops or duplicate edges, and the provided graph will be connected.

The next line contains a single integer $ q $ ( $ 1 \leq q \leq 10^5 $ ).

Each of the next $ q $ lines contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n $ , $ u \neq v $ ), the description of each query.

## 输出格式

For each query, print one line containing a single integer — the answer to the query.

## 说明/提示

The following is an explanation of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1659E/e80c1510937e2e4c165cad1b2b45b357811161d4.png)The graph in the first example.Here is one possible walk for the first query:

 $ $$$1 \overset{5}{\rightarrow} 3 \overset{3}{\rightarrow} 2 \overset{1}{\rightarrow} 1 \overset{5}{\rightarrow} 3 \overset{1}{\rightarrow} 4 \overset{2}{\rightarrow} 5. $ $ </p><p>The array of weights is  $ w=\[5,3,1,5,1,2\] $ . Now if we take the bitwise AND of every prefix of this array, we get the set  $ \\{5,1,0\\} $ . The MEX of this set is  $ 2$$$. We cannot get a walk with a smaller length (as defined in the statement).

## 样例 #1

### 输入

```
6 7
1 2 1
2 3 3
3 1 5
4 5 2
5 6 4
6 4 6
3 4 1
3
1 5
1 2
5 3
```

### 输出

```
2
0
1
```

## 样例 #2

### 输入

```
9 8
1 2 5
2 3 11
3 4 10
3 5 10
5 6 2
5 7 1
7 8 5
7 9 5
10
5 7
2 5
7 1
6 4
5 2
7 6
4 1
6 2
4 7
2 8
```

### 输出

```
0
0
2
0
0
2
1
0
1
1
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
title: "2+ doors"
layout: "post"
diff: 提高+/省选-
pid: CF1715D
tag: ['2-SAT', '位运算']
---

# 2+ doors

## 题目描述

Narrator有一个长度为 $n$ 的整数数组 $a$ ，但是他只会告诉你 $n$ 的大小和 $q$ 个要求，每个要求包括三个整数 $i,j,x$ ，要求满足 $a_i\mid a_j = x$，其中 $|$ 表示按位或运算

找到满足所有要求的字典序最小的数组 $a$

## 输入格式

第一行读入两个整数 $n$ 和 $q$ ( $1 \le  n \le 10^5$ , $0 \le q \le 2 \cdot 10^5$ )

接下来 $q$ 行，读入三个整数 $i$ , $j$ , $x$ ( $1 \le i, j \le n $ , $ 0 \le x < 2^{30} $ )

保证所有 $q$ 个要求至少满足一个数组 $a$

## 输出格式

一行 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $0 \le a_i < 2^{30}$ )

## 样例 #1

### 输入

```
4 3
1 2 3
1 3 2
4 1 2
```

### 输出

```
0 3 2 2
```

## 样例 #2

### 输入

```
1 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 1
1 1 1073741823
```

### 输出

```
1073741823 0
```



---

---
title: "ConstructOR"
layout: "post"
diff: 提高+/省选-
pid: CF1748D
tag: ['贪心', '中国剩余定理 CRT', '位运算', '构造']
---

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, containing three integers $ a $ , $ b $ , and $ d $ ( $ 1 \le a,b,d \lt 2^{30} $ ).

## 输出格式

For each test case print one integer. If there exists an integer $ x $ which satisfies all of the conditions from the statement, print $ x $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999
```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983
```



---

---
title: "The Harmonization of XOR"
layout: "post"
diff: 提高+/省选-
pid: CF1787E
tag: ['位运算', '构造']
---

# The Harmonization of XOR

## 题目描述

给定 $n$ 个数 $[1,2,3,\ldots,n]$ 和两个正整数 $k$ 和 $x$。

将这些数分成恰好 $k$ 组使得每组的异或和都是 $x$。具体地，每个数都必须出现在恰好一组内。

例如，$n = 15,k = 6,x = 7$ 时，下列分法是合法的（$\oplus$ 表示按位异或运算）：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[8,15]$, $8 \oplus 15 = 7$
- $[7]$, $7 = 7$

下列分法是不合法的：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[7]$, $7 = 7$

因为 $8$ 和 $15$ 没有出现。

下列分法也不合法：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$,
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$,
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$,
- $[3,4]$, $3 \oplus 4 = 7$,
- $[8,15]$, $8 \oplus 15 = 7$,
- $[7]$, $7 = 7$.

因为 $1$ 和 $2$ 未出现且 $3$ 出现两次。

~~这题本来是 C~~


保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 输入格式

第一行一个正整数 $t$（$1\le t\le 10^4$）表示测试数据组数。

## 输出格式

对于每组测试数据，若不存在合法方案，输出 `NO`。若存在，先输出 `YES`，接下来 $k$ 行输出方案。具体地，每一行第一个数字输出这一组的长度 $s_i$，后接 $s_i$ 个数字表示这一组的数字。注意每一组中的数字可以按任意顺序给出。

### 样例解释

第一组测试数据中，给出的一组合法方案如下：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[8,15]$, $8 \oplus 15 = 7$
- $[7]$, $7 = 7$

第二组测试数据中，给出的一组合法方案如下：

- $[1,4]$, $1 \oplus 4 = 5$
- $[2,7]$, $2 \oplus 7 = 5$
- $[3,6]$, $3 \oplus 6 = 5$
- $[5,8,9,10,11]$, $5 \oplus 8 \oplus 9 \oplus 10 \oplus 11 = 5$

同时下面的方案也合法：

- $[1,4]$, $1 \oplus 4 = 5$
- $[2,7]$, $2 \oplus 7 = 5$
- $[5]$, $5 = 5$
- $[3,6,8,9,10,11]$, $3 \oplus 6 \oplus 8 \oplus 9 \oplus 10 \oplus 11 = 5$

## 样例 #1

### 输入

```
7
15 6 7
11 4 5
5 3 2
4 1 4
6 1 7
11 5 5
11 6 5
```

### 输出

```
YES
3 6 10 11
3 5 12 14
3 3 9 13
3 1 2 4
2 8 15
1 7
YES
2 1 4
2 2 7
2 3 6
5 5 8 9 10 11
NO
YES
4 1 2 3 4
YES
6 1 2 3 4 5 6
NO
NO
```



---

---
title: "Billetes MX (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2022E1
tag: ['并查集', '位运算']
---

# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ and $ q $ ( $ 2 \le n, m \le 10^5 $ ; $ 0 \le k \le 10^5 $ ; $ q = 0 $ ) — the number of rows, the number of columns, the number of fixed cells, and the number of updates.

The following $ k $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

The following $ q $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

It is guaranteed that the pairs $ (r,c) $ over all assignments are distinct.

It is guaranteed that the sum of $ n $ , $ m $ , $ k $ and $ q $ over all test cases does not exceed $ 10^5 $ respectively.

## 输出格式

For each test case, output $ q + 1 $ lines. The $ i $ -th line of output should contain the answer of the $ i $ -th state of the grid modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30
```

### 输出

```
1
489373567
```



---

---
title: "Billetes MX (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2022E2
tag: ['并查集', '位运算']
---

# Billetes MX (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is guaranteed that $ q \leq 10^5 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ and $ q $ ( $ 2 \le n, m \le 10^5 $ ; $ 0 \le k, q \leq 10^5 $ ) — the number of rows, the number of columns, the number of fixed cells, and the number of updates.

The following $ k $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) indicating that $ G_{r, c} $ is assigned the integer $ v $ .

The following $ q $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) indicating that $ G_{r, c} $ is assigned the integer $ v $ .

It is guaranteed that the pairs $ (r,c) $ over all assignments are distinct.

It is guaranteed that the sum of $ n $ , $ m $ , $ k $ and $ q $ over all test cases does not exceed $ 10^5 $ respectively.

## 输出格式

For each test case, output $ q + 1 $ lines. The $ i $ -th line of output should contain the answer of the $ i $ -th state of the grid modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case of the example, we initially have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ , so the first answer is $ 1 $ . For the second query, the grid does not satisfy the condition, and thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
3 3 8 1
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
3 3 1
2 5 2 0
1 1 10
1 2 30
2 5 0 2
1 1 10
1 2 30
```

### 输出

```
1
0
489373567
651321892
769740174
489373567
```



---

---
title: "Matrix Transformation"
layout: "post"
diff: 提高+/省选-
pid: CF2043E
tag: ['图论', '贪心', '位运算']
---

# Matrix Transformation

## 题目描述

给定两个大小为 $n \times m$ 的矩阵 $A$ 和 $B$，其中元素是 $0$ 到 $10^9$ 之间的整数。你可以对矩阵 $A$ 执行以下任意次数的操作，且操作顺序不受限制：

- **按位与操作**：选择某一行 $i$ 和一个非负整数 $x$，将这一行的每个元素用 $x$ 进行按位与运算。具体来说，对于行 $i$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ & } x$。
- **按位或操作**：选择某一列 $j$ 和一个非负整数 $x$，将这一列的每个元素用 $x$ 进行按位或运算。具体来说，对于列 $j$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ | } x$。

可以在每次操作中选择不同的 $x$ 值。

你的任务是判断是否可以通过上述操作，将矩阵 $A$ 转变为矩阵 $B$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。接下来是 $t$ 组测试用例。

每个测试用例如下：

- 第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^3$ 且 $n \cdot m \le 10^3$），表示矩阵 $A$ 和 $B$ 的行数和列数。
- 接下来的 $n$ 行描述矩阵 $A$，每行包含 $m$ 个整数 $A_{i,1}, A_{i,2}, \dots, A_{i,m}$，表示该行的所有元素（$0 \le A_{i,j} \le 10^9$）。
- 再接下来的 $n$ 行描述矩阵 $B$，每行包含 $m$ 个整数 $B_{i,1}, B_{i,2}, \dots, B_{i,m}$，表示该行的所有元素（$0 \le B_{i,j} \le 10^9$）。

## 输出格式

对于每个测试用例，如果可以将矩阵 $A$ 转换为矩阵 $B$，请输出 `Yes`；否则输出 `No`。输出中的字母大小写不作要求。

## 说明/提示

以第二组输入数据为例，展示如何通过操作将矩阵 $A$ 转换为矩阵 $B$：

初始状态下，矩阵 $A$ 如下：

$$
\begin{bmatrix}
10 & 10 \\
42 & 42 \\
\end{bmatrix}
$$

1. 对第一行：应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
42 & 42 \\
\end{bmatrix}
$$

2. 对第二行：再次应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
0 & 0 \\
\end{bmatrix}
$$

3. 对第一列：应用按位或操作，选择 $x = 21$，矩阵变为：

$$
\begin{bmatrix}
21 & 0 \\
21 & 0 \\
\end{bmatrix}
$$

4. 对第二列：再次应用按位或操作，选择 $x = 21$，最终矩阵为：

$$
\begin{bmatrix}
21 & 21 \\
21 & 21 \\
\end{bmatrix}
$$

通过这一系列操作，我们成功将矩阵 $A$ 转换为矩阵 $B$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1 1
12
13
2 2
10 10
42 42
21 21
21 21
2 2
74 10
42 106
21 85
85 21
2 4
1 2 3 4
5 6 7 8
3 2 3 4
1 0 1 0
```

### 输出

```
Yes
Yes
No
Yes
```



---

---
title: "Bitwise Slides"
layout: "post"
diff: 提高+/省选-
pid: CF2066C
tag: ['动态规划 DP', '离散化', '位运算']
---

# Bitwise Slides

## 题目描述

给定一个数组 $a_1, a_2, \ldots, a_n$，以及三个初始值为零的变量 $P, Q, R$。

你需要按从 $1$ 到 $n$ 的顺序依次处理所有数字 $a_1, a_2, \ldots, a_n$。当处理当前元素 $a_i$ 时，你必须从以下三个操作中任选一个执行：
1. $P := P \oplus a_i$
2. $Q := Q \oplus a_i$
3. $R := R \oplus a_i$

其中 $\oplus$ 表示按位异或操作。

执行操作时必须遵守核心规则：每次操作后，三个数 $P, Q, R$ 必须满足两两不互异。

所有 $n$ 个操作共有 $3^n$ 种可能的执行方式。求其中不违反核心规则的方式数量。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出不违反核心规则的操作方式数量对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试用例中，存在 3 种合法操作序列：PPP、QQQ、RRR。

第二个测试用例中，存在 9 种合法操作序列：PPPP、PPPQ、PPPR、QQQP、QQQQ、QQQR、RRRP、RRRQ、RRRR。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
1 7 9
4
179 1 1 179
5
1 2 3 3 2
12
8 2 5 3 9 1 8 12 9 9 9 4
1
1000000000
```

### 输出

```
3
9
39
123
3
```



---

---
title: "Infinite Sequence (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2071D2
tag: ['位运算']
---

# Infinite Sequence (Hard Version)

## 题目描述

这是该问题的困难版本。不同版本的区别在于此版本中 $l \leq r$。仅当您解决了该问题的所有版本时才能进行 hack。

给定一个正整数 $n$ 和一个无限二进制序列 $a$ 的前 $n$ 项，该序列定义如下：

- 对于 $m > n$，$a_m = a_1 \oplus a_2 \oplus \ldots \oplus a_{\lfloor \frac{m}{2} \rfloor}$ $^{\text{∗}}$。

你的任务是计算给定区间 $[l, r]$ 内元素的和：$a_l + a_{l + 1} + \ldots + a_r$。

$^{\text{∗}}$ $\oplus$ 表示[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$l$ 和 $r$（$1 \le n \le 2 \cdot 10^5$，$1 \le l \leq r \le 10^{18}$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$\color{red}{a_i \in \{0, 1\}}$）——序列 $a$ 的前 $n$ 项。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——给定区间内元素的和。

## 说明/提示

在第一个测试用例中，序列 $a$ 为：

$$[\underline{\color{red}{1}}, 1, 1, 0, 0, 1, 1, 1, 1, 1, \ldots]$$ 

其中 $l = 1$，$r = 1$。区间 $[1, 1]$ 的元素和为 $a_1 = 1$。

在第二个测试用例中，序列 $a$ 为：

$$ [\text{\color{red}{1}}, \text{\color{red}{0}}, \underline{1}, 1, 1, 0, 0, 1, 1, 0, \ldots] $$

其中 $l = 3$，$r = 10$。区间 $[3, 10]$ 的元素和为

$$ a_3 + a_4 + \ldots + a_{10} = 1 + 1 + 1 + 0 + 0 + 1 + 1 + 0 = 5. $$

翻译由 DeepSeek R1 完成


## 样例 #1

### 输入

```
9
1 1 1
1
2 3 10
1 0
3 5 25
1 1 1
1 234 567
0
5 1111 10000000000
1 0 1 0 1
1 1000000000000000000 1000000000000000000
1
10 41 87
0 1 1 1 1 1 1 1 0 0
12 65 69
1 0 0 0 0 1 0 1 0 1 1 0
13 46 54
0 1 0 1 1 1 1 1 1 0 1 1 1
```

### 输出

```
1
5
14
0
6666665925
0
32
3
2
```



---

---
title: "Wonderful Lightbulbs"
layout: "post"
diff: 提高+/省选-
pid: CF2096D
tag: ['位运算', 'Ad-hoc']
---

# Wonderful Lightbulbs

## 题目描述

你是一个无限大灯泡网格的骄傲拥有者，这些灯泡以[笛卡尔坐标系](https://en.wikipedia.org/wiki/Cartesian_coordinate_system)排列。初始时，所有灯泡都处于关闭状态，除了一个灯泡——那里埋藏着你最骄傲的宝藏。

为了隐藏宝藏的位置，你可以执行以下操作任意次数（包括零次）：
- 选择两个整数 $x$ 和 $y$，然后切换位于 $(x,y)$、$(x,y+1)$、$(x+1,y-1)$ 和 $(x+1,y)$ 的 4 个灯泡的状态。换句话说，对于每个灯泡，如果它原本是关闭的就打开它，如果原本是打开的就关闭它。注意 $x$ 和 $y$ 没有任何限制。

最终，有 $n$ 个灯泡处于打开状态，坐标分别为 $(x_1,y_1), (x_2,y_2), \ldots, (x_n,y_n)$。不幸的是，你已经忘记了宝藏最初埋藏的位置，现在需要找出一个可能的宝藏位置。祝你好运！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——处于打开状态的灯泡数量。

接下来的 $n$ 行中，第 $i$ 行包含两个整数 $x_i$ 和 $y_i$（$-10^8 \le x_i, y_i \le 10^8$）——第 $i$ 个灯泡的坐标。保证所有坐标都是不同的。

额外约束：存在至少一个位置 $(s,t)$（$-10^9 \le s, t \le 10^9$），使得如果初始时位于 $(s,t)$ 的灯泡是打开的，那么在执行任意次操作（包括零次）后，可以得到给定的灯泡配置。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出两个整数 $s$ 和 $t$（$-10^9 \le s, t \le 10^9$）——一个可能的宝藏埋藏位置。如果存在多个解，输出其中任意一个即可。

本题禁用 hack。

## 说明/提示

对于第一个测试用例，一种可能的情况是你将宝藏埋在位置 $(2,3)$。然后你没有执行任何操作。

最终，只有位于 $(2,3)$ 的灯泡是打开的。

对于第二个测试用例，一种可能的情况是你将宝藏埋在位置 $(-2,-2)$。然后你执行了 1 次操作，选择 $x=-2$，$y=-2$。

这次操作切换了位于 $(-2,-2)$、$(-2,-1)$、$(-1,-3)$ 和 $(-1,-2)$ 的 4 个灯泡的状态。

最终，位于 $(-2,-1)$、$(-1,-2)$ 和 $(-1,-3)$ 的灯泡是打开的。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1
2 3
3
-2 -1
-1 -2
-1 -3
7
7 26
6 27
6 28
7 27
8 26
8 27
7 28
11
70 9
69 8
69 0
73 5
70 -1
70 5
71 7
70 4
73 4
71 3
72 3
```

### 输出

```
2 3
-2 -2
7 27
72 7
```



---

---
title: "Xor-sequences"
layout: "post"
diff: 提高+/省选-
pid: CF691E
tag: ['模拟', '进制', '位运算']
---

# Xor-sequences

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ .

A sequence of integers $ x_{1},x_{2},...,x_{k} $ is called a "xor-sequence" if for every $ 1<=i<=k-1 $ the number of ones in the binary representation of the number $ x_{i} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) $ x_{i+1} $ 's is a multiple of $ 3 $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/187abd20483c4318d7cd71518f323b9990bcdd61.png) for all $ 1<=i<=k $ . The symbol ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) is used for the binary exclusive or operation.

How many "xor-sequences" of length $ k $ exist? Output the answer modulo $ 10^{9}+7 $ .

Note if $ a=[1,1] $ and $ k=1 $ then the answer is $ 2 $ , because you should consider the ones from $ a $ as different.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{18} $ ) — the number of given integers and the length of the "xor-sequences".

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{18} $ ).

## 输出格式

Print the only integer $ c $ — the number of "xor-sequences" of length $ k $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5 2
15 1 2 4 8

```

### 输出

```
13

```

## 样例 #2

### 输入

```
5 1
15 1 2 4 8

```

### 输出

```
5

```



---

---
title: "Square Subsets"
layout: "post"
diff: 提高+/省选-
pid: CF895C
tag: ['数学', '状态合并', '线性基', '位运算']
---

# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 输入格式

First line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of elements in the array.

Second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=70 $ ) — the elements of the array.

## 输出格式

Print one integer — the number of different ways to choose some elements so that their product is a square of a certain integer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1

```

### 输出

```
15

```

## 样例 #2

### 输入

```
4
2 2 2 2

```

### 输出

```
7

```

## 样例 #3

### 输入

```
5
1 2 4 5 8

```

### 输出

```
7

```



---

