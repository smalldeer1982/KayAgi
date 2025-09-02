---
title: "TL"
layout: "post"
diff: 普及-
pid: CF350A
tag: []
---

# TL

## 题目描述

Valera wanted to prepare a Codesecrof round. He's already got one problem and he wants to set a time limit (TL) on it.

Valera has written $ n $ correct solutions. For each correct solution, he knows its running time (in seconds). Valera has also wrote $ m $ wrong solutions and for each wrong solution he knows its running time (in seconds).

Let's suppose that Valera will set $ v $ seconds TL in the problem. Then we can say that a solution passes the system testing if its running time is at most $ v $ seconds. We can also say that a solution passes the system testing with some "extra" time if for its running time, $ a $ seconds, an inequality $ 2a<=v $ holds.

As a result, Valera decided to set $ v $ seconds TL, that the following conditions are met:

1. $ v $ is a positive integer;
2. all correct solutions pass the system testing;
3. at least one correct solution passes the system testing with some "extra" time;
4. all wrong solutions do not pass the system testing;
5. value $ v $ is minimum among all TLs, for which points $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ hold.

Help Valera and find the most suitable TL or else state that such TL doesn't exist.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=100 $ ). The second line contains $ n $ space-separated positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=100 $ ) — the running time of each of the $ n $ correct solutions in seconds. The third line contains $ m $ space-separated positive integers $ b_{1},b_{2},...,b_{m} $ ( $ 1<=b_{i}<=100 $ ) — the running time of each of $ m $ wrong solutions in seconds.

## 输出格式

If there is a valid TL value, print it. Otherwise, print -1.

## 样例 #1

### 输入

```
3 6
4 5 2
8 9 6 10 7 11

```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 1
3 4 5
6

```

### 输出

```
-1

```

