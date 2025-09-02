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

