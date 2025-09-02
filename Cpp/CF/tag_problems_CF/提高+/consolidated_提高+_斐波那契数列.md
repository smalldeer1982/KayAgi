---
title: "Anniversary"
layout: "post"
diff: 提高+/省选-
pid: CF226C
tag: ['枚举', '斐波那契数列']
---

# Anniversary

## 题目描述

There are less than 60 years left till the 900-th birthday anniversary of a famous Italian mathematician Leonardo Fibonacci. Of course, such important anniversary needs much preparations.

Dima is sure that it'll be great to learn to solve the following problem by the Big Day: You're given a set $ A $ , consisting of numbers $ l $ , $ l+1 $ , $ l+2 $ , $ ... $ , $ r $ ; let's consider all its $ k $ -element subsets; for each such subset let's find the largest common divisor of Fibonacci numbers with indexes, determined by the subset elements. Among all found common divisors, Dima is interested in the largest one.

Dima asked to remind you that Fibonacci numbers are elements of a numeric sequence, where $ F_{1}=1 $ , $ F_{2}=1 $ , $ F_{n}=F_{n-1}+F_{n-2} $ for $ n>=3 $ .

Dima has more than half a century ahead to solve the given task, but you only have two hours. Count the residue from dividing the sought largest common divisor by $ m $ .

## 输入格式

The first line contains four space-separated integers $ m $ , $ l $ , $ r $ and $ k $ $ (1<=m<=10^{9}; 1<=l&lt;r<=10^{12}; 2<=k<=r-l+1) $ .

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specifier.

## 输出格式

Print a single integer — the residue from dividing the sought greatest common divisor by $ m $ .

## 样例 #1

### 输入

```
10 1 8 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 1 8 3

```

### 输出

```
1

```



---

---
title: "DZY Loves Fibonacci Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF446C
tag: ['数学', '线段树', '斐波那契数列']
---

# DZY Loves Fibonacci Numbers

## 题目描述

In mathematical terms, the sequence $ F_{n} $ of Fibonacci numbers is defined by the recurrence relation

 $ F_{1}=1; F_{2}=1; F_{n}=F_{n-1}+F_{n-2} (n>2). $ DZY loves Fibonacci numbers very much. Today DZY gives you an array consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Moreover, there are $ m $ queries, each query has one of the two types:

1. Format of the query " $ 1\ l\ r $ ". In reply to the query, you need to add $ F_{i-l+1} $ to each element $ a_{i} $ , where $ l<=i<=r $ .
2. Format of the query " $ 2\ l\ r $ ". In reply to the query you should output the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF446C/9b1c73158dd7a4166f7d8fde16bb75f36899bc0e.png) modulo $ 1000000009 (10^{9}+9) $ .

Help DZY reply to all the queries.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=300000 $ ). The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} (1<=a_{i}<=10^{9}) $ — initial array $ a $ .

Then, $ m $ lines follow. A single line describes a single query in the format given in the statement. It is guaranteed that for each query inequality $ 1<=l<=r<=n $ holds.

## 输出格式

For each query of the second type, print the value of the sum on a single line.

## 说明/提示

After the first query, $ a=[2,3,5,7] $ .

For the second query, $ sum=2+3+5+7=17 $ .

After the third query, $ a=[2,4,6,9] $ .

For the fourth query, $ sum=2+4+6=12 $ .

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3

```

### 输出

```
17
12

```



---

