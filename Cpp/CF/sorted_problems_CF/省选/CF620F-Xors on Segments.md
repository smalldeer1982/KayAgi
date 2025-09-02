---
title: "Xors on Segments"
layout: "post"
diff: 省选/NOI-
pid: CF620F
tag: []
---

# Xors on Segments

## 题目描述

You are given an array with $ n $ integers $ a_{i} $ and $ m $ queries. Each query is described by two integers $ (l_{j},r_{j}) $ .

Let's define the function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF620F/f18ed64d02d5b1c443dfe0810af3982715620dfd.png). The function is defined for only $ u<=v $ .

For each query print the maximal value of the function $ f(a_{x},a_{y}) $ over all $ l_{j}<=x,y<=r_{j},\ a_{x}<=a_{y} $ .

## 输入格式

The first line contains two integers $ n,m $ ( $ 1<=n<=5·10^{4},\ 1<=m<=5·10^{3} $ ) — the size of the array and the number of the queries.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array $ a $ .

Each of the next $ m $ lines contains two integers $ l_{j},r_{j} $ ( $ 1<=l_{j}<=r_{j}<=n $ ) – the parameters of the $ j $ -th query.

## 输出格式

For each query print the value $ a_{j} $ on a separate line — the maximal value of the function $ f(a_{x},a_{y}) $ over all $ l_{j}<=x,y<=r_{j},\ a_{x}<=a_{y} $ .

## 样例 #1

### 输入

```
6 3
1 2 3 4 5 6
1 6
2 5
3 4

```

### 输出

```
7
7
7

```

## 样例 #2

### 输入

```
1 1
1
1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6 20
10 21312 2314 214 1 322
1 1
1 2
1 3
1 4
1 5
1 6
2 2
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 4
4 5
4 6
5 5
5 6
6 6

```

### 输出

```
10
21313
21313
21313
21313
21313
21312
21313
21313
21313
21313
2314
2315
2315
214
215
323
1
323
322

```

