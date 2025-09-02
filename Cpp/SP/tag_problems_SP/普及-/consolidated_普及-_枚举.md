---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "TAKIN - Taskin and apple tree"
layout: "post"
diff: 普及-
pid: SP33795
tag: ['枚举', '剪枝', '背包 DP']
---

# TAKIN - Taskin and apple tree

## 题目描述

# TAKIN - Taskin和苹果树


Taskin有一个苹果园，每天早上他都会去果园采摘苹果。他有一个篮子，可以携带**不超过 M个**苹果。Taskin将所摘的苹果放入篮子里，对于每一棵树，他要么将这棵树上的所有苹果摘完，要么跳过这棵树不摘。现在让你制定一个方案，使Taskin所摘的苹果数量最多。

## 输入格式

在第一行输入一个整数T，表示有T个测试数据。

每组测试数据以两个整数 M 和 N 开始，分别表示果园中的苹果树的数量和篮子最多能装的苹果数。

接下来有N个整数：a[1],a[2],a[3],...,a[n],其中a[i]表示第i棵苹果树所结苹果的个数。

## 输出格式

输出一个整数，表示所能摘的最大的苹果数。

## 输入输出样例
### 输入样例＃1：

```cpp
2 
5 6 
2 1 2 7 8 
5 10 
1 2 4 4 6
```
### 输出样例＃1：

```cpp
5 
10
```

## 说明/提示

T<=10,N<=20,M<=2*10^10,a[i]<=10^9

翻译提供者：right_cat

## 样例 #1

### 输入

```
2
5 6
2 1 2 7 8
5 10
1 2 4 4 6
```

### 输出

```
5
10
```



---

