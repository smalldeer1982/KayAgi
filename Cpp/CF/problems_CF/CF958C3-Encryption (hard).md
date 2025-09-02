---
title: "Encryption (hard)"
layout: "post"
diff: 提高+/省选-
pid: CF958C3
tag: []
---

# Encryption (hard)

## 题目描述

Heidi is now just one code away from breaking the encryption of the Death Star plans. The screen that should be presenting her with the description of the next code looks almost like the previous one, though who would have thought that the evil Empire engineers would fill this small screen with several million digits! It is just ridiculous to think that anyone would read them all...

Heidi is once again given a sequence $ A $ and two integers $ k $ and $ p $ . She needs to find out what the encryption key $ S $ is.

Let $ X $ be a sequence of integers, and $ p $ a positive integer. We define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given integers $ k $ and $ p $ . Her goal is to split $ A $ into $ k $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- No two parts overlap.
- The total sum $ S $ of the scores of those parts is minimized (not maximized!).

Output the sum $ S $ , which is the encryption code.

## 输入格式

The first line of the input contains three space-separated integers $ N $ , $ k $ and $ p $ ( $ k<=N<=500000 $ , $ 2<=k<=100 $ , $ 2<=p<=100 $ ) – the number of elements in $ A $ , the number of parts $ A $ should be split into, and the modulo for computing scores, respectively.

The second line contains $ N $ space-separated integers that are the elements of $ A $ . Each integer is from the interval $ [1,1000000] $ .

## 输出格式

Output the number $ S $ as described in the problem statement.

## 说明/提示

In the first example, if the input sequence is split as $ (3) $ , $ (4,7) $ , $ (2) $ , the total score would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C3/d85b82846e8d0ea943e5dbc022fe9af7d9ee19d2.png). It is easy to see that this score is the smallest possible.

In the second example, one possible way to obtain score $ 13 $ is to make the following split: $ (16,3) $ , $ (24) $ , $ (13) $ , $ (9,8) $ , $ (7,5,12,12) $ .

## 样例 #1

### 输入

```
4 3 10
3 4 7 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
10 5 12
16 3 24 13 9 8 7 5 12 12

```

### 输出

```
13

```

