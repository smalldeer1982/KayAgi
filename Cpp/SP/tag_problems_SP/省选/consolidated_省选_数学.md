---
title: "NTHPRIME - Nth Prime"
layout: "post"
diff: 省选/NOI-
pid: SP25024
tag: ['数学', '二分', '素数判断,质数,筛法']
---

# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 输入格式

The input consists of a single line containing an integer **N,** **N** **10^9**.

## 输出格式

For each input file, output the **Nth** prime number.

## 样例 #1

### 输入

```
4
```

### 输出

```
7
```



---

---
title: "PAGAIN - Prime Again"
layout: "post"
diff: 省选/NOI-
pid: SP3587
tag: ['数学', '枚举']
---

# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 输入格式

The first line contains an integer T specifying the number of test cases. (T <= 10000)

T lines follow, each line contains an integer N.

## 输出格式

For each test case, output the result on one line.

## 样例 #1

### 输入

```
3

5 

10

17
```

### 输出

```
3

7

13
```



---

---
title: "MSKYCODE - Sky Code"
layout: "post"
diff: 省选/NOI-
pid: SP4191
tag: ['数学']
---

# MSKYCODE - Sky Code

## 题目描述

Stancu likes space travels but he is a poor software developer and will never be able to buy his own spacecraft. That is why he is preparing to steal the spacecraft of Petru. There is only one problem – Petru has locked the spacecraft with a sophisticated cryptosystem based on the ID numbers of the stars from the Milky Way Galaxy. For breaking the system Stancu has to check each subset of four stars such that the only common divisor of their numbers is $1$. Nasty, isn’t it?

Fortunately, Stancu has succeeded to limit the number of the interesting stars to $n$ but, any way, the possible subsets of four stars can be too many. Help him to find their number and to decide if there is a chance to break the system.

## 输入格式

In the input file several test cases are given. For each test case on the first line the number $n$ of interesting stars is given $(1 \leq n \leq 10000)$.

The second line of the test case contains the list of ID numbers of the interesting stars, separated by spaces. Each ID is a positive integer which is no greater than $10000$. The input data terminate with the end of file.

## 输出格式

For each test case the program should print one line with the number of subsets with the asked property.

## 样例 #1

### 输入

```
4
2 3 4 5
4
2 4 6 8
7
2 3 4 5 7 6 8
```

### 输出

```
1
0
34
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

