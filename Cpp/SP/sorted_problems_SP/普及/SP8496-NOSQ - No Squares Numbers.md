---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```

