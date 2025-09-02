---
title: "Friends"
layout: "post"
diff: 省选/NOI-
pid: CF241B
tag: []
---

# Friends

## 题目描述

You have $ n $ friends and you want to take $ m $ pictures of them. Exactly two of your friends should appear in each picture and no two pictures should contain the same pair of your friends. So if you have $ n=3 $ friends you can take $ 3 $ different pictures, each containing a pair of your friends.

Each of your friends has an attractiveness level which is specified by the integer number $ a_{i} $ for the $ i $ -th friend. You know that the attractiveness of a picture containing the $ i $ -th and the $ j $ -th friends is equal to the exclusive-or ( $ xor $ operation) of integers $ a_{i} $ and $ a_{j} $ .

You want to take pictures in a way that the total sum of attractiveness of your pictures is maximized. You have to calculate this value. Since the result may not fit in a 32-bit integer number, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241B/9b22f23dc8d59dbe11b4e44a61cf25e2908e7225.png) — the number of friends and the number of pictures that you want to take.

Next line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ) — the values of attractiveness of the friends.

## 输出格式

The only line of output should contain an integer — the optimal total sum of attractiveness of your pictures.

## 样例 #1

### 输入

```
3 1
1 2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2
1 2 3

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 3
1 2 3

```

### 输出

```
6

```

