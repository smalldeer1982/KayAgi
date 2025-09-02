---
title: "Iva & Pav"
layout: "post"
diff: 普及/提高-
pid: CF1878E
tag: ['线段树', '二分', 'ST 表']
---

# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of array $ a $ .

The third line of each test case contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries Iva gave Pav.

The next $ q $ lines of each test case contains two numbers, $ l $ and $ k $ ( $ 1 \le l \le n $ , $ 1 \le k \le 10^9 $ ) — the left bound for the subsegment, and the integer $ k $ described in statement.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Also, it is guaranteed that the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query output maximal index $ r $ ( $ l \le r \le n $ ) such that $ a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r \ \ge \ k $ .

If such $ r $ doesn't exist, output $ -1 $ .

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7
```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5
```



---

---
title: "Maximum modulo equality"
layout: "post"
diff: 普及/提高-
pid: CF2050F
tag: ['数论', 'ST 表']
---

# Maximum modulo equality

## 题目描述

给你一个长度为 $n$ 的数组 $a$ 和 $q$ 次查询。  
每次查询给定两个数 $l$ 和 $r$，求出最大的 $m$ 使得 $a_l \bmod m = a_{l + 1} \bmod m = \dots = a_r \bmod m$，其中 $a \bmod b$ 是 $a$ 除以 $b$ 的余数。  
**特别的，当 $m$ 可能是无限大时，请输出 $0$。**

## 输入格式

第一行输入一个整数 $t(1 \le t \le 10^4)$，表示测试用例数。  
对于每个测试用例：
+ 第一行输入两个整数 $n$ 和 $q(1 \le n, q \le 2 \times 10^5)$，表示数组长度和查询次数。  
+ 第二行输入 $n$ 个整数 $a_i(1 \le a_i \le 10^9)$，表示数组中的元素。  
+ 接下来的 $q$ 行中，每行输入两个整数 $l$ 和 $r(1 \le l \le r \le n)$，表示查询范围。

保证 $\sum n, \sum q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
3
5 5
5 14 2 6 3
4 5
1 4
2 4
3 5
1 1
1 1
7
1 1
3 2
1 7 8
2 3
1 2
```

### 输出

```
3 1 4 1 0 
0 
1 6
```



---

