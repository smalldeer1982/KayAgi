---
title: "Common Number"
layout: "post"
diff: 提高+/省选-
pid: CF1271E
tag: []
---

# Common Number

## 题目描述

At first, let's define function $ f(x) $ as follows: $ $$$ \begin{matrix} f(x) & = & \left\{ \begin{matrix} \frac{x}{2} & \mbox{if } x \text{ is even} \\ x - 1 & \mbox{otherwise } \end{matrix} \right. \end{matrix}  $ $ </p><p>We can see that if we choose some value  $ v $  and will apply function  $ f $  to it, then apply  $ f $  to  $ f(v) $ , and so on, we'll eventually get  $ 1 $ . Let's write down all values we get in this process in a list and denote this list as  $ path(v) $ . For example,  $ path(1) = \[1\] $ ,  $ path(15) = \[15, 14, 7, 6, 3, 2, 1\] $ ,  $ path(32) = \[32, 16, 8, 4, 2, 1\] $ .</p><p>Let's write all lists  $ path(x) $  for every  $ x $  from  $ 1 $  to  $ n $ . The question is next: what is the maximum value  $ y $  such that  $ y $  is contained in at least  $ k $  different lists  $ path(x) $ ?</p><p>Formally speaking, you need to find maximum  $ y $  such that  $ \\left| \\{ x ~|~ 1 \\le x \\le n, y \\in path(x) \\} \\right| \\ge k$$$.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^{18} $ ).

## 输出格式

Print the only integer — the maximum value that is contained in at least $ k $ paths.

## 说明/提示

In the first example, the answer is $ 5 $ , since $ 5 $ occurs in $ path(5) $ , $ path(10) $ and $ path(11) $ .

In the second example, the answer is $ 4 $ , since $ 4 $ occurs in $ path(4) $ , $ path(5) $ , $ path(8) $ , $ path(9) $ , $ path(10) $ and $ path(11) $ .

In the third example $ n = k $ , so the answer is $ 1 $ , since $ 1 $ is the only number occuring in all paths for integers from $ 1 $ to $ 20 $ .

## 样例 #1

### 输入

```
11 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
11 6

```

### 输出

```
4

```

## 样例 #3

### 输入

```
20 20

```

### 输出

```
1

```

## 样例 #4

### 输入

```
14 5

```

### 输出

```
6

```

## 样例 #5

### 输入

```
1000000 100

```

### 输出

```
31248

```

