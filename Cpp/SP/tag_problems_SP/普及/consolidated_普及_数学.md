---
title: "FAST2 - Fast Sum of two to an exponent"
layout: "post"
diff: 普及/提高-
pid: SP11383
tag: ['数学', '高精度']
---

# FAST2 - Fast Sum of two to an exponent

## 题目描述

There is people that really like to do silly thinks, one of them is sum the numbers from 2^0 to 2^n, task is actually really simple, just do a ultra fast sum of term 2^0 to 2^n

## 输入格式

the first line starts with a number, T, wich is the number of test cases, T lines will follow

each line contains a number "n" that is the nth term of the sum from 2^0 to 2^n

0<=n<=500

## 输出格式

Output the sum from 2^0 to 2^n MODULO 1298074214633706835075030044377087

## 样例 #1

### 输入

```
3\n0\n1\n2\n\n
```

### 输出

```
1\n3\n7 \n\nExtra: TLE is equal to 0.15s\n
```



---

---
title: "ADATEAMS - Ada and Teams"
layout: "post"
diff: 普及/提高-
pid: SP28304
tag: ['组合数学', '逆元']
---

# ADATEAMS - Ada and Teams

## 题目描述

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择$D$ 名学生参赛，问一共有多少种不同的选择方案。

## 输入格式

多组数据，每组数据一行，包含 $N, A, B, D (1 \le A \le N ≤ 10^6, 1 \le D \le B \le 10^6)$ 四个整数。

## 输出格式

输出答案对 $10^9+7$ 取模的结果。



---

---
title: "JGTLE - Jalil Got TLE"
layout: "post"
diff: 普及/提高-
pid: SP34011
tag: ['数学', '枚举']
---

# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 输入格式

输入的第一行将包含一个正整数 $T$，表示测试用例的数量。

在每个测试用例中，将有 $3$ 个正整数 $a$、$b$ 和 $c$。

## 输出格式

对于每个测试用例，打印与上述程序相同的输出。


---

Translated by User 735713.

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777
```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "JULKA - Julka"
layout: "post"
diff: 普及/提高-
pid: SP54
tag: ['字符串', '数学', '高精度']
---

# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 输入格式

 Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10 $ ^{100} $ (1 and 100 zeros) apples together. As you can see apples can be very small.

## 输出格式

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.

## 样例 #1

### 输入

```
10

2

[and 9 test cases more]
```

### 输出

```
6

4

[and 9 test cases more]
```



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---

