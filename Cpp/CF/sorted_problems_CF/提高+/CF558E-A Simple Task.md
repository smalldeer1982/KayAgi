---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF558E
tag: ['字符串', '线段树', '排序']
---

# A Simple Task

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 输入格式

The first line will contain two integers $ n,q $ ( $ 1<=n<=10^{5} $ , $ 0<=q<=50000 $ ), the length of the string and the number of queries respectively.

Next line contains a string $ S $ itself. It contains only lowercase English letters.

Next $ q $ lines will contain three integers each $ i,j,k $ ( $ 1<=i<=j<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/7c3e064c95015e1bd5569e78df83991726b5fb24.png)).

## 输出格式

Output one line, the string $ S $ after applying the queries.

## 说明/提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 样例 #1

### 输入

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1

```

### 输出

```
cbcaaaabdd
```

## 样例 #2

### 输入

```
10 1
agjucbvdfk
1 10 1

```

### 输出

```
abcdfgjkuv
```

