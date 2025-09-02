---
title: "Fibonotci"
layout: "post"
diff: 省选/NOI-
pid: CF575A
tag: []
---

# Fibonotci

## 题目描述

Fibonotci sequence is an integer recursive sequence defined by the recurrence relation

 $ F_{n}=s_{n-1}·F_{n-1}+s_{n-2}·F_{n-2} $  with  $ F_{0}=0,F_{1}=1 $ Sequence $ s $ is an infinite and almost cyclic sequence with a cycle of length $ N $ . A sequence $ s $ is called almost cyclic with a cycle of length $ N $ if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/489fd2e5fb549725a7a9de5a934f7a838952563f.png), for $ i>=N $ , except for a finite number of values $ s_{i} $ , for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/3f92eca313b934333be63d48e6d251e408e4922e.png) ( $ i>=N $ ).

Following is an example of an almost cyclic sequence with a cycle of length 4:

 s = (5,3,8,11,5,3,7,11,5,3,8,11,…) Notice that the only value of $ s $ for which the equality ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/c723ac9c89791a5b8e370fa82e33937eb7ce6a73.png) does not hold is $ s_{6} $ ( $ s_{6}=7 $ and $ s_{2}=8 $ ). You are given $ s_{0},s_{1},...s_{N-1} $ and all the values of sequence $ s $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/3f92eca313b934333be63d48e6d251e408e4922e.png) ( $ i>=N $ ).

Find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/1ed5b2d60749876c1857042c6e156873ebb4e0f0.png).

## 输入格式

The first line contains two numbers $ K $ and $ P $ . The second line contains a single number $ N $ . The third line contains $ N $ numbers separated by spaces, that represent the first $ N $ numbers of the sequence $ s $ . The fourth line contains a single number $ M $ , the number of values of sequence $ s $ for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/3f92eca313b934333be63d48e6d251e408e4922e.png). Each of the following $ M $ lines contains two numbers $ j $ and $ v $ , indicating that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/61d61b0cd4f25e1afcd53e14ccd0e5748081a98b.png) and $ s_{j}=v $ . All j-s are distinct.

- $ 1<=N,M<=50000 $
- $ 0<=K<=10^{18} $
- $ 1<=P<=10^{9} $
- $ 1<=s_{i}<=10^{9} $ , for all $ i=0,1,...N-1 $
- $ N<=j<=10^{18} $
- $ 1<=v<=10^{9} $
- All values are integers

## 输出格式

Output should contain a single integer equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575A/1ed5b2d60749876c1857042c6e156873ebb4e0f0.png).

## 样例 #1

### 输入

```
10 8
3
1 2 1
2
7 3
5 4

```

### 输出

```
4

```

