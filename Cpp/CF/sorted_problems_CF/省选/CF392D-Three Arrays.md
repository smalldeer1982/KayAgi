---
title: "Three Arrays"
layout: "post"
diff: 省选/NOI-
pid: CF392D
tag: []
---

# Three Arrays

## 题目描述

There are three arrays $ a $ , $ b $ and $ c $ . Each of them consists of $ n $ integers. SmallY wants to find three integers $ u $ , $ v $ , $ w $ $ (0<=u,v,w<=n) $ such that the following condition holds: each number that appears in the union of $ a $ , $ b $ and $ c $ , appears either in the first $ u $ elements of $ a $ , or in the first $ v $ elements of $ b $ , or in the first $ w $ elements of $ c $ . Of course, SmallY doesn't want to have huge numbers $ u $ , $ v $ and $ w $ , so she wants sum $ u+v+w $ to be as small as possible.

Please, help her to find the minimal possible sum of $ u+v+w $ .

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ — array $ a $ . The third line contains the description of array $ b $ in the same format. The fourth line contains the description of array $ c $ in the same format. The following constraint holds: $ 1<=a_{i},b_{i},c_{i}<=10^{9} $ .

## 输出格式

Print a single integer — the minimum possible sum of $ u+v+w $ .

## 说明/提示

In the first example you should choose $ u=3,v=0,w=2 $ .

In the second example you should choose $ u=1,v=3,w=1 $ .

## 样例 #1

### 输入

```
3
1 1 101
1 2 1
3 2 1

```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 1 2 2 3
2 2 4 3 3
3 3 1 1 1

```

### 输出

```
5
```

