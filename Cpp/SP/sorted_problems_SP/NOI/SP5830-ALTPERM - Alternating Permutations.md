---
title: "ALTPERM - Alternating Permutations"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP5830
tag: []
---

# ALTPERM - Alternating Permutations

## 题目描述

You are given K indices, A\[1\], A\[2\], ... , A\[K\].

A\[1\] < A\[2\] < ... < A\[K\].

A\[1\] = 1 and A\[K\] = N.

A permutation of the numbers between 1 and N is called valid if :

The numbers in the permutation between indices A\[1\] and A\[2\] (inclusive) form an increasing sequence, the numbers in the permutation between indices A\[2\] and A\[3\] (inclusive) form a decreasing sequence, those between A\[3\] and A\[4\] (inclusive) form an increasing sequence and so on.

Count the number of valid permutations.

**Input**

There will be multiple test cases. The first line contains the number of test cases T.

There follow 2\*T lines, 2 lines for each test case. The first line for each test case contains the numbers N and K. The second line contains K space seperated numbers, ie. A\[1\] to A\[K\].

**Output**

Output T lines, one for each test case. All answers should be output MOD 1000000007.

**Example**

 ```
Sample Input :
3
3 3
1 2 3
4 3
1 3 4
10 6
1 2 5 7 8 10

Sample Output :
2
3
6166



Constraints
T <= 111
2 <= N <= 20000
2 <= K <= 22K <= NA[1] < A[2] < ... < A[K].
A[1] = 1 and A[K] = N.
```

