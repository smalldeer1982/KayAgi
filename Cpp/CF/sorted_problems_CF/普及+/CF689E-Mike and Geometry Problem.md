---
title: "Mike and Geometry Problem"
layout: "post"
diff: 普及+/提高
pid: CF689E
tag: []
---

# Mike and Geometry Problem

## 题目描述

Mike wants to prepare for IMO but he doesn't know geometry, so his teacher gave him an interesting geometry problem. Let's define $ f([l,r])=r-l+1 $ to be the number of integer points in the segment $ [l,r] $ with $ l<=r $ (say that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/eeb8344fc6181df63840b4617c77d0b7d8f368f7.png)). You are given two integers $ n $ and $ k $ and $ n $ closed intervals $ [l_{i},r_{i}] $ on $ OX $ axis and you have to find:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/babb2cf528ef0c11f1d2962e2d5be706b0377f3a.png)In other words, you should find the sum of the number of integer points in the intersection of any $ k $ of the segments.

As the answer may be very large, output it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

Mike can't solve this problem so he needs your help. You will help him, won't you?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=200000 $ ) — the number of segments and the number of segments in intersection groups respectively.

Then $ n $ lines follow, the $ i $ -th line contains two integers $ l_{i},r_{i} $ $ (-10^{9}<=l_{i}<=r_{i}<=10^{9}) $ , describing $ i $ -th segment bounds.

## 输出格式

Print one integer number — the answer to Mike's problem modulo $ 1000000007 $ ( $ 10^{9}+7 $ ) in the only line.

## 说明/提示

In the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/7f9f6f2b3fe972c0968e2bbe39c55090c69a5e96.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/0c85a7c8eabbf8ea75307cc85322cc7194a52b51.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/05a4f7cd13ee1be29210f871f739a0914a5c363f.png).

So the answer is $ 2+1+2=5 $ .

## 样例 #1

### 输入

```
3 2
1 2
1 3
2 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 3
1 3
1 3
1 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3 1
1 2
2 3
3 4

```

### 输出

```
6

```

