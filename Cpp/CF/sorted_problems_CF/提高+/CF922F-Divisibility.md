---
title: "Divisibility"
layout: "post"
diff: 提高+/省选-
pid: CF922F
tag: []
---

# Divisibility

## 题目描述

Imp is really pleased that you helped him. But it you solve the last problem, his gladness would raise even more.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/80a786f701ecc7d26672fb3b926d9dbbafc0495c.png) Let's define ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/473e0c7367d2c6c65b609424fc67aa6d9df96dba.png) for some set of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png) as the number of pairs $ a $ , $ b $ in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png), such that:- $ a $ is strictly less than $ b $ ;
- $ a $ divides $ b $ without a remainder.

You are to find such a set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png), which is a subset of $ {1,2,...,n} $ (the set that contains all positive integers not greater than $ n $ ), that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/8b010c35295a2181d8d3d9dae7832a9cb8742631.png).

## 输入格式

The only line contains two integers $ n $ and $ k $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/8abf4553781ebbfe2252497213ee6d6360c3f2f4.png).

## 输出格式

If there is no answer, print "No".

Otherwise, in the first line print "Yes", in the second — an integer $ m $ that denotes the size of the set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png) you have found, in the second line print $ m $ integers — the elements of the set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/b0118d24df19910ba6c937fa885fbcac0ee6712c.png), in any order.

If there are multiple answers, print any of them.

## 说明/提示

In the second sample, the valid pairs in the output set are $ (1,2) $ , $ (1,4) $ , $ (1,5) $ , $ (1,6) $ , $ (2,4) $ , $ (2,6) $ . Thus, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/4055df47b045359cddfa03da919a728d3502ec96.png).

In the third example, the valid pairs in the output set are $ (2,4) $ , $ (4,8) $ , $ (2,8) $ . Thus, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922F/8e639a6dd37ec9bd64a5d37b32a72070668e9569.png).

## 样例 #1

### 输入

```
3 3

```

### 输出

```
No

```

## 样例 #2

### 输入

```
6 6

```

### 输出

```
Yes
5
1 2 4 5 6 
```

## 样例 #3

### 输入

```
8 3

```

### 输出

```
Yes
4
2 4 5 8

```

