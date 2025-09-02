---
title: "Wrong Addition"
layout: "post"
diff: 普及-
pid: CF1619C
tag: ['模拟']
---

# Wrong Addition

## 题目描述

Tanya is learning how to add numbers, but so far she is not doing it correctly. She is adding two numbers $ a $ and $ b $ using the following algorithm:

1. If one of the numbers is shorter than the other, Tanya adds leading zeros so that the numbers are the same length.
2. The numbers are processed from right to left (that is, from the least significant digits to the most significant).
3. In the first step, she adds the last digit of $ a $ to the last digit of $ b $ and writes their sum in the answer.
4. At each next step, she performs the same operation on each pair of digits in the same place and writes the result to the left side of the answer.

For example, the numbers $ a = 17236 $ and $ b = 3465 $ Tanya adds up as follows:

 $ $$$ \large{ \begin{array}{r} + \begin{array}{r} 17236\\ 03465\\ \end{array} \\ \hline \begin{array}{r} 1106911 \end{array} \end{array}}  $ $ </p><ul> <li> calculates the sum of  $ 6 + 5 = 11 $  and writes  $ 11 $  in the answer. </li><li> calculates the sum of  $ 3 + 6 = 9 $  and writes the result to the left side of the answer to get  $ 911 $ . </li><li> calculates the sum of  $ 2 + 4 = 6 $  and writes the result to the left side of the answer to get  $ 6911 $ . </li><li> calculates the sum of  $ 7 + 3 = 10 $ , and writes the result to the left side of the answer to get  $ 106911 $ . </li><li> calculates the sum of  $ 1 + 0 = 1 $  and writes the result to the left side of the answer and get  $ 1106911 $ . </li></ul><p>As a result, she gets  $ 1106911 $ .</p><p>You are given two positive integers  $ a $  and  $ s $ . Find the number  $ b $  such that by adding  $ a $  and  $ b $  as described above, Tanya will get  $ s $ . Or determine that no suitable  $ b$$$ exists.

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of a single line containing two positive integers $ a $ and $ s $ ( $ 1 \le a \lt s \le 10^{18} $ ) separated by a space.

## 输出格式

For each test case print the answer on a separate line.

If the solution exists, print a single positive integer $ b $ . The answer must be written without leading zeros. If multiple answers exist, print any of them.

If no suitable number $ b $ exists, output -1.

## 说明/提示

The first test case is explained in the main part of the statement.

In the third test case, we cannot choose $ b $ that satisfies the problem statement.

## 样例 #1

### 输入

```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20
```

### 输出

```
3465
4
-1
90007
10
-1
```

