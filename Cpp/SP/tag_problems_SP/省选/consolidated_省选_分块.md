---
title: "MOD - Power Modulo Inverted"
layout: "post"
diff: 省选/NOI-
pid: SP3105
tag: ['枚举', '分块']
---

# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0
```

### 输出

```
9
No Solution
```



---

---
title: "PRIMES2 - Printing some primes (Hard)"
layout: "post"
diff: 省选/NOI-
pid: SP6488
tag: ['数学', '素数判断,质数,筛法', '分块']
---

# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 输入格式

There is not input.

## 输出格式

To make the problem less output related write out only the 1st, 501st, 1001st, ... 1st mod 500.

## 样例 #1

### 输入

```

```

### 输出

```
2

3581

7927

...

999978527

999988747

999999151
```



---

---
title: "VLATTICE - Visible Lattice Points"
layout: "post"
diff: 省选/NOI-
pid: SP7001
tag: ['数学', '莫比乌斯反演', '整除分块']
---

# VLATTICE - Visible Lattice Points

## 题目描述

Consider a N\*N\*N lattice. One corner is at (0,0,0) and the opposite one is at (N,N,N). How many lattice points are visible from corner at (0,0,0) ? A point X is visible from point Y iff no other lattice point lies on the segment joining X and Y.   
   
Input :   
The first line contains the number of test cases T. The next T lines contain an interger N   
   
Output :   
Output T lines, one corresponding to each test case.   
   
Sample Input :   
3   
1   
2   
5   
   
Sample Output :   
7   
19   
175   
   
Constraints :   
T <= 50   
1 <= N <= 1000000



---

