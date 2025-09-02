---
title: "RATAR - Ratar"
layout: "post"
diff: 省选/NOI-
pid: SP16180
tag: ['枚举', '前缀和', '概率论']
---

# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 输入格式

The first line of input contains the positive integer N (1

land plot.

Each of the following N lines contains N space-separated numbers Aij (-1000 < Aij < 1000), the income

provided by the respective cell.

## 输出格式

The first and only line of output must contain the total number of plot pairs satisfying the given

condition.

## 样例 #1

### 输入

```
3

1 2 3

2 3 4

3 4 8
```

### 输出

```
7
```



---

---
title: "RNG - Random Number Generator"
layout: "post"
diff: 省选/NOI-
pid: SP2002
tag: ['计算几何', '容斥原理', '概率论', '微积分']
---

# RNG - Random Number Generator

## 题目描述

LoadingTime got a RNG (_Random Number Generator_) from his classmate several weeks ago. And he spent a lot of time study it. He found that RNG can generate a real number in range \[-**S**,**S**\] by executing following steps. First RNG generates n integer **X** $ _{1} $ ..**X** $ _{n} $ , the sum of which is equal to **S**. Then for each **X** $ _{i} $ , it generates a real number in range \[-**X** $ _{i} $ ,**X** $ _{i} $ \] randomly. The output (a real number) of RNG will be the sum of the **N** generated real numbers. LoadingTime noticed that the distribution of the output was very interesting, and he wanted to know: for given **N** and **X**, what's the probability that the generated number is in range \[**A**,**B**\]. Could you help him?

## 输入格式

The first line contains an integer T representing the number of test cases.

For each test case, the first line contains three integers **N**, **A**, **B**(1 ≤ **N** ≤ 10, -100 ≤ **A** ≤ **B** ≤ 100) In the second line of the test case, you are given **X** $ _{1} $ ...**X** $ _{n} $ (1 ≤ **X** $ _{i} $ ≤ 10).

## 输出格式

For each test case, print a line contains a real number representing the probablity as the problem required. It must be printed with exactly nine decimal places.

## 样例 #1

### 输入

```
5

1 -100 100

10

1 10 90

10

1 -20 5

10

2 -20 5

5 5

5 -5 10

1 2 3 4 5
```

### 输出

```
1.000000000

0.000000000

0.750000000

0.875000000

0.864720052
```



---

---
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "QTREE4 - Query on a tree IV"
layout: "post"
diff: 省选/NOI-
pid: SP2666
tag: ['递归', '分治', '动态树 LCT', '概率论']
---

# QTREE4 - Query on a tree IV

## 题目描述

You are given a tree (an acyclic undirected connected graph) with $N$ nodes, and nodes numbered $1,2,3\ldots,N$. Each edge has an integer value assigned to it (note that the value can be negative). Each node has a color, white or black. We define $dist(a, b)$ as the sum of the value of the edges on the path from node $a$ to node $b$.

All the nodes are white initially.

We will ask you to perfrom some instructions of the following form:

- `C a` : change the color of node $a$.(from black to white or from white to black)
- `A` : ask for the maximum $dist(a, b)$, both of node a and node $b$ must be white ($a$ can be equal to $b$). Obviously, as long as there is a white node, the result will alway be non negative.

## 输入格式

- In the first line there is an integer $N$. ($N \leq 100000$)
- In the next $N-1$ lines, the $i$-th line describes the $i$-th edge: a line with three integers $a,b,c$ denotes an edge between $a, b$ of value $c$. ($-10^3 \leq c \leq 10^3$)
- In the next line, there is an integer $Q$ denotes the number of instructions. ($Q \leq 100000$)
- In the next $Q$ lines, each line contains an instruction `C a` or `A`.

## 输出格式

For each `A` operation, write one integer representing its result. If there is no white node in the tree, you should write `They have disappeared.`.

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```

### 输出

```
2
2
0
They have disappeared.
```



---

