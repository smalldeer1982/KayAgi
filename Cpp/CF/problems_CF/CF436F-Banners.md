---
title: "Banners"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF436F
tag: []
---

# Banners

## 题目描述

All modern mobile applications are divided into free and paid. Even a single application developers often release two versions: a paid version without ads and a free version with ads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF436F/c46aedeefaad64d2bb027e2acfd0cd5cd5b8a0fc.png)Suppose that a paid version of the app costs $ p $ ( $ p $ is an integer) rubles, and the free version of the application contains $ c $ ad banners. Each user can be described by two integers: $ a_{i} $ — the number of rubles this user is willing to pay for the paid version of the application, and $ b_{i} $ — the number of banners he is willing to tolerate in the free version.

The behavior of each member shall be considered strictly deterministic:

- if for user $ i $ , value $ b_{i} $ is at least $ c $ , then he uses the free version,
- otherwise, if value $ a_{i} $ is at least $ p $ , then he buys the paid version without advertising,
- otherwise the user simply does not use the application.

Each user of the free version brings the profit of $ c×w $ rubles. Each user of the paid version brings the profit of $ p $ rubles.

Your task is to help the application developers to select the optimal parameters $ p $ and $ c $ . Namely, knowing all the characteristics of users, for each value of $ c $ from $ 0 $ to $ (max b_{i})+1 $ you need to determine the maximum profit from the application and the corresponding parameter $ p $ .

## 输入格式

The first line contains two integers $ n $ and $ w $ $ (1<=n<=10^{5}; 1<=w<=10^{5}) $ — the number of users and the profit from a single banner. Each of the next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ $ (0<=a_{i},b_{i}<=10^{5}) $ — the characteristics of the $ i $ -th user.

## 输出格式

Print $ (max b_{i})+2 $ lines, in the $ i $ -th line print two integers: $ pay $ — the maximum gained profit at $ c=i-1 $ , $ p $ $ (0<=p<=10^{9}) $ — the corresponding optimal app cost. If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
2 1
2 0
0 2

```

### 输出

```
0 3
3 2
4 2
2 2

```

## 样例 #2

### 输入

```
3 1
3 1
2 2
1 3

```

### 输出

```
0 4
3 4
7 3
7 2
4 2

```

