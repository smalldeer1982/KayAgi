---
title: "Funny Game"
layout: "post"
diff: 普及+/提高
pid: CF1994D
tag: ['数论', '鸽笼原理']
---

# Funny Game

## 题目描述

Vanya has a graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and an array $ a $ of $ n $ integers; initially, there are no edges in the graph. Vanya got bored, and to have fun, he decided to perform $ n - 1 $ operations.

Operation number $ x $ (operations are numbered in order starting from $ 1 $ ) is as follows:

- Choose $ 2 $ different numbers $ 1 \leq u,v \leq n $ , such that $ |a_u - a_v| $ is divisible by $ x $ .
- Add an undirected edge between vertices $ u $ and $ v $ to the graph.

Help Vanya get a connected $ ^{\text{∗}} $ graph using the $ n - 1 $ operations, or determine that it is impossible.

 $ ^{\text{∗}} $ A graph is called connected if it is possible to reach any vertex from any other by moving along the edges.

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{3} $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains the number $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of vertices in the graph.

The second line of each test case contains $ n $ numbers $ a_1, a_2, \cdots a_n $ ( $ 1 \leq a_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, if there is no solution, then output "No" (without quotes).

Otherwise, output "Yes" (without quotes), and then output $ n - 1 $ lines, where in the $ i $ -th line, output the numbers $ u $ and $ v $ that need to be chosen for operation $ i $ .

You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

Let's consider the second test case.

- First operation $ (x = 1) $ : we can connect vertices $ 4 $ and $ 1 $ , since $ |a_4 - a_1| = |13 - 99| = |-86| = 86 $ , and $ 86 $ is divisible by $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f454bbc6f9e0e97455a35659663326d5f1b7732f.png)- Second operation $ (x = 2) $ : we can connect vertices $ 2 $ and $ 1 $ , since $ |a_2 - a_1| = |7 - 99| = |-92| = 92 $ , and $ 92 $ is divisible by $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/9f40b6b2ea3eceff5de09b1a367a88713eeb53f7.png)- Third operation $ (x = 3) $ : we can connect vertices $ 3 $ and $ 2 $ , since $ |a_3 - a_2| = |1 - 7| = |-6| = 6 $ , and $ 6 $ is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f0db9ab0c3e7fd24f5ff083e0932405157cd111f.png) From the picture, it can be seen that a connected graph is obtained.

## 样例 #1

### 输入

```
8
2
1 4
4
99 7 1 13
5
10 2 31 44 73
5
87 6 81 44 32
5
62 35 33 79 16
5
6 51 31 69 42
5
52 63 25 21 5
12
33 40 3 11 31 43 37 8 50 5 12 22
```

### 输出

```
YES
2 1
YES
4 1
2 1
3 2
YES
5 1
4 1
3 1
2 1
YES
4 1
3 1
2 1
5 4
YES
3 1
5 1
2 1
4 2
YES
4 1
5 1
2 1
3 2
YES
2 1
5 2
3 1
4 3
YES
9 1
12 9
11 1
10 1
6 1
7 6
2 1
8 2
5 2
3 1
4 1
```



---

---
title: "Matrix game"
layout: "post"
diff: 普及+/提高
pid: CF2120D
tag: ['组合数学', '鸽笼原理']
---

# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case contains a single line with three space-separated integers $ a, b $ and $ k $ ( $ 1\leq a,b,k\leq 10^5 $ ).

It is guaranteed that the sum of $ \max(a, b, k) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single line containing two space-separated integers $ n $ and $ m $ , denoting the answer to the problem. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000
```

### 输出

```
1 1
3 7
299929959 603196135
```



---

