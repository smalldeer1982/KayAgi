---
title: "Little Pony and Summer Sun Celebration"
layout: "post"
diff: 提高+/省选-
pid: CF453C
tag: []
---

# Little Pony and Summer Sun Celebration

## 题目描述

Twilight Sparkle learnt that the evil Nightmare Moon would return during the upcoming Summer Sun Celebration after one thousand years of imprisonment on the moon. She tried to warn her mentor Princess Celestia, but the princess ignored her and sent her to Ponyville to check on the preparations for the celebration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453C/076e2d37b9cb7b6614410629f2bfd3bd32464a7e.png)Twilight Sparkle wanted to track the path of Nightmare Moon. Unfortunately, she didn't know the exact path. What she knew is the parity of the number of times that each place Nightmare Moon visited. Can you help Twilight Sparkle to restore any path that is consistent with this information?

Ponyville can be represented as an undirected graph (vertices are places, edges are roads between places) without self-loops and multi-edges. The path can start and end at any place (also it can be empty). Each place can be visited multiple times. The path must not visit more than $ 4n $ places.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5}; 0<=m<=10^{5} $ ) — the number of places and the number of roads in Ponyville. Each of the following $ m $ lines contains two integers $ u_{i},v_{i} $ ( $ 1<=u_{i},v_{i}<=n; u_{i}≠v_{i} $ ), these integers describe a road between places $ u_{i} $ and $ v_{i} $ .

The next line contains $ n $ integers: $ x_{1},x_{2},...,x_{n} $ $ (0<=x_{i}<=1) $ — the parity of the number of times that each place must be visited. If $ x_{i}=0 $ , then the $ i $ -th place must be visited even number of times, else it must be visited odd number of times.

## 输出格式

Output the number of visited places $ k $ in the first line ( $ 0<=k<=4n $ ). Then output $ k $ integers — the numbers of places in the order of path. If $ x_{i}=0 $ , then the $ i $ -th place must appear in the path even number of times, else $ i $ -th place must appear in the path odd number of times. Note, that given road system has no self-loops, therefore any two neighbouring places in the path must be distinct.

If there is no required path, output -1. If there multiple possible paths, you can output any of them.

## 样例 #1

### 输入

```
3 2
1 2
2 3
1 1 1

```

### 输出

```
3
1 2 3

```

## 样例 #2

### 输入

```
5 7
1 2
1 3
1 4
1 5
3 4
3 5
4 5
0 1 0 1 0

```

### 输出

```
10
2 1 3 4 5 4 5 4 3 1 
```

## 样例 #3

### 输入

```
2 0
0 0

```

### 输出

```
0

```

