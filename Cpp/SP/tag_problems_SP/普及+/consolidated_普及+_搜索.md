---
title: "SUMFOUR - 4 values whose sum is 0"
layout: "post"
diff: 普及+/提高
pid: SP1296
tag: ['搜索', '二分', '枚举']
---

# SUMFOUR - 4 values whose sum is 0

## 题目描述

The SUM problem can be formulated as follows: given four lists A, B, C, D of integer values, compute how many quadruplet (a, b, c, d ) belongs to A x B x C x D are such that a + b + c + d = 0 . In the following, we assume that all lists have the same size n

## 输入格式

 The first line of the input file contains the size of the lists n (this value can be as large as 4000). We then have n lines containing four integer values (with absolute value as large as 2 $ ^{28} $ ) that belong respectively to A, B, C and D .

(**Edited:** n <= 2500)

## 输出格式

Output should be printed on a single line.

## 样例 #1

### 输入

```
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
```

### 输出

```
5
```



---

---
title: "FREQUENT - Frequent values"
layout: "post"
diff: 普及+/提高
pid: SP1684
tag: ['搜索', '未知标签231']
---

# FREQUENT - Frequent values

## 题目描述

You are given a sequence of **n** integers **a $ _{1} $ , a $ _{2} $ , ... , a $ _{n} $**  in non-decreasing order. In addition to that, you are given several queries consisting of indices **i** and **j** (_1 ≤ i ≤ j ≤ n_). For each query, determine the most frequent value among the integers **a $ _{i} $ , ... , a $ _{j} $** .

   
#### Input Specification

 The input consists of several test cases. Each test case starts with a line containing two integers **n** and **q** (_1 ≤ n, q ≤ 100000_). The next line contains **n** integers **a $ _{1} $ , ... , a $ _{n} $**  (_-100000 ≤ a $ _{i} $ ≤ 100000_, for each _i ∈ {1, ..., n}_) separated by spaces. You can assume that for each _i ∈ {1, ..., n-1}: a $ _{i} $ ≤ a $ _{i+1} $_ . The following **q** lines contain one query each, consisting of two integers **i** and **j** (_1 ≤ i ≤ j ≤ n_), which indicate the boundary indices for the query.

 The last test case is followed by a line containing a single 0.

   
#### Output Specification

 For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.

   
#### Sample Input

 ```
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
```
   
#### Sample Output

 ```
1
4
3
```
- - - - - -

_A naive algorithm may not run in time!_



---

---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---

---
title: "YOKOF - Power Calculus"
layout: "post"
diff: 普及+/提高
pid: SP7579
tag: ['搜索']
---

# YOKOF - Power Calculus

## 题目描述

（略过没有营养的题干）

**题目大意**：
  给出正整数n,若只能使用乘法或除法，输出使x经过运算（自己乘或除自己，以及乘或除运算过程中产生的中间结果）变成x^n的最少步数

## 输入格式

若干行数据，每行一个正整数n，数据以单独成行的0结束

## 输出格式

若干行数据，对应每行输入的n所需的步数

## 样例 #1

### 输入

```
1
31
70
91
473
512
811
953
0
```

### 输出

```
0
6
8
9
11
9
13
12
```



---

---
title: "PUBLICAT - Publication"
layout: "post"
diff: 普及+/提高
pid: SP9255
tag: ['广度优先搜索 BFS']
---

# PUBLICAT - Publication

## 题目描述

Orizondo 数用于衡量某个科学家与 Rodrigo Orizondo 在学术论文合著中的“合作距离”。Rodrigo Orizondo 的 Orizondo 数是零。要获得有限的 Orizondo 数，科学家必须与至少一个已有有限 Orizondo 数的科学家共同发表论文。一个科学家的 Orizondo 数是他所有合作者中最低的 Orizondo 数加一。论文发表的顺序和编号分配顺序无关，因为每次发表后，系统会自动更新所有作者的 Orizondo 数。

你将得到一组 **论文** 数据，每篇论文包含一组作者，格式为 “AUTHOR\_1 AUTHOR\_2 ... AUTHOR\_N”（引号仅为明确表示）。其中，Rodrigo Orizondo 用 “ORIZONDO” 表示。

请输出所有作者的 Orizondo 数。输出格式为 “AUTHOR NUMBER”，若无法为某作者赋予有限的 Orizondo 数，仅输出 “AUTHOR”。作者的输出顺序应按字典序排列。

## 输入格式

第一行输入一个整数 \( C \)，表示测试用例的数量（\( 0 < C \)）。

每个测试用例首先包含一个整数 \( N \)，表示论文的数量，接着是 \( N \) 行，每行包含一组用空格分隔的作者姓名。

## 输出格式

对于每个测试用例，输出一行，包含每个作者及其 Orizondo 数，信息之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1
ORIZONDO
2
KLEITMAN LANDER
ORIZONDO KLEITMAN
4
ORIZONDO B
A B C
B A E
D F
```

### 输出

```
ORIZONDO 0
KLEITMAN 1 LANDER 2 ORIZONDO 0
A 2 B 1 C 2 D E 2 F ORIZONDO 0
```



---

