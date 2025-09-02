---
title: "PolandBall and Gifts"
layout: "post"
diff: 省选/NOI-
pid: CF755F
tag: ['贪心', '背包 DP', '进制']
---

# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 输入格式

The first line of input contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{6} $ , $ 0<=k<=n $ ), representing the number of Balls and the number of Balls who will forget to bring their presents.

The second line contains the permutation $ p $ of integers from $ 1 $ to $ n $ , where $ p_{i} $ is the index of Ball who should get a gift from the $ i $ -th Ball. For all $ i $ , $ p_{i}≠i $ holds.

## 输出格式

You should output two values — minimum and maximum possible number of Balls who will not get their presents, in that order.

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2

```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1

```

### 输出

```
2 2
```

