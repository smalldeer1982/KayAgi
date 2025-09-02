---
title: "Acyclic Organic Compounds"
layout: "post"
diff: 省选/NOI-
pid: CF601D
tag: []
---

# Acyclic Organic Compounds

## 题目描述

You are given a tree $ T $ with $ n $ vertices (numbered $ 1 $ through $ n $ ) and a letter in each vertex. The tree is rooted at vertex $ 1 $ .

Let's look at the subtree $ T_{v} $ of some vertex $ v $ . It is possible to read a string along each simple path starting at $ v $ and ending at some vertex in $ T_{v} $ (possibly $ v $ itself). Let's denote the number of distinct strings which can be read this way as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/a0c9096effba09473c4b51e3186b592318344485.png).

Also, there's a number $ c_{v} $ assigned to each vertex $ v $ . We are interested in vertices with the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png).

You should compute two statistics: the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png) and the number of vertices $ v $ with the maximum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1<=n<=300000 $ ) — the number of vertices of the tree.

The second line contains $ n $ space-separated integers $ c_{i} $ ( $ 0<=c_{i}<=10^{9} $ ).

The third line contains a string $ s $ consisting of $ n $ lowercase English letters — the $ i $ -th character of this string is the letter in vertex $ i $ .

The following $ n-1 $ lines describe the tree $ T $ . Each of them contains two space-separated integers $ u $ and $ v $ ( $ 1<=u,v<=n $ ) indicating an edge between vertices $ u $ and $ v $ .

It's guaranteed that the input will describe a tree.

## 输出格式

Print two lines.

On the first line, print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/ab594599a15dce04b620c4b306a1a124f3c93d49.png) over all $ 1<=i<=n $ .

On the second line, print the number of vertices $ v $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/f0eef52a01ab9da1eb6f064715fdae90a5a11537.png).

## 说明/提示

In the first sample, the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/9244e4a8ade3af9b76853a18eae8ae654a6d5be1.png)The sets of strings that can be read from individual vertices are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/b0a25806e20ff995abfb34a167834abd113ae6f1.png)Finally, the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png) are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/6c3fc4aa4c72ec4c2646ac39d7110bd6544e120f.png)In the second sample, the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/4c35255ca2e85f9a2c304b6b5d98f8aa96f62b0c.png) are $ (5,4,2,1,1,1) $ . The distinct strings read in $ T_{2} $ are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/6427dc79a89c97e7e81a3e52fb54938acda3e0b8.png); note that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/ff39f896bb407bf8e8d94b0a5b47a67e60c595d8.png) can be read down to vertices $ 3 $ or $ 4 $ .

## 样例 #1

### 输入

```
10
1 2 7 20 20 30 40 50 50 50
cacabbcddd
1 2
6 8
7 2
6 2
5 4
5 9
3 10
2 5
2 3

```

### 输出

```
51
3

```

## 样例 #2

### 输入

```
6
0 2 4 1 1 1
raaaba
1 2
2 3
2 4
2 5
3 6

```

### 输出

```
6
2

```

