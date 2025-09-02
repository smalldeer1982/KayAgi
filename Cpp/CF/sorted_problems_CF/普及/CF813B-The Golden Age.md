---
title: "The Golden Age"
layout: "post"
diff: 普及/提高-
pid: CF813B
tag: []
---

# The Golden Age

## 题目描述

Unlucky year in Berland is such a year that its number $ n $ can be represented as $ n=x^{a}+y^{b} $ , where $ a $ and $ b $ are non-negative integer numbers.

For example, if $ x=2 $ and $ y=3 $ then the years 4 and 17 are unlucky ( $ 4=2^{0}+3^{1} $ , $ 17=2^{3}+3^{2}=2^{4}+3^{0} $ ) and year 18 isn't unlucky as there is no such representation for it.

Such interval of years that there are no unlucky years in it is called The Golden Age.

You should write a program which will find maximum length of The Golden Age which starts no earlier than the year $ l $ and ends no later than the year $ r $ . If all years in the interval $ [l,r] $ are unlucky then the answer is 0.

## 输入格式

The first line contains four integer numbers $ x $ , $ y $ , $ l $ and $ r $ ( $ 2<=x,y<=10^{18} $ , $ 1<=l<=r<=10^{18} $ ).

## 输出格式

Print the maximum length of The Golden Age within the interval $ [l,r] $ .

If all years in the interval $ [l,r] $ are unlucky then print 0.

## 说明/提示

In the first example the unlucky years are 2, 3, 4, 5, 7, 9 and 10. So maximum length of The Golden Age is achived in the intervals $ [1,1] $ , $ [6,6] $ and $ [8,8] $ .

In the second example the longest Golden Age is the interval $ [15,22] $ .

## 样例 #1

### 输入

```
2 3 1 10

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 5 10 22

```

### 输出

```
8

```

## 样例 #3

### 输入

```
2 3 3 5

```

### 输出

```
0

```

