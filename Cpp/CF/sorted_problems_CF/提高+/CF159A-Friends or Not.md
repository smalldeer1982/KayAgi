---
title: "Friends or Not"
layout: "post"
diff: 提高+/省选-
pid: CF159A
tag: []
---

# Friends or Not

## 题目描述

Polycarpus has a hobby — he develops an unusual social network. His work is almost completed, and there is only one more module to implement — the module which determines friends. Oh yes, in this social network one won't have to add friends manually! Pairs of friends are deduced in the following way. Let's assume that user $ A $ sent user $ B $ a message at time $ t_{1} $ , and user $ B $ sent user $ A $ a message at time $ t_{2} $ . If $ 0&lt;t_{2}-t_{1}<=d $ , then user $ B $ 's message was an answer to user $ A $ 's one. Users $ A $ and $ B $ are considered to be friends if $ A $ answered at least one $ B $ 's message or $ B $ answered at least one $ A $ 's message.

You are given the log of messages in chronological order and a number $ d $ . Find all pairs of users who will be considered to be friends.

## 输入格式

The first line of the input contains two integers $ n $ and $ d $ ( $ 1<=n,d<=1000 $ ). The next $ n $ lines contain the messages log. The $ i $ -th line contains one line of the log formatted as " $ A_{i} $ $ B_{i} $ $ t_{i} $ " (without the quotes), which means that user $ A_{i} $ sent a message to user $ B_{i} $ at time $ t_{i} $ ( $ 1<=i<=n $ ). $ A_{i} $ and $ B_{i} $ are non-empty strings at most $ 20 $ characters long, consisting of lowercase letters ('a' ... 'z'), and $ t_{i} $ is an integer ( $ 0<=t_{i}<=10000 $ ). It is guaranteed that the lines are given in non-decreasing order of $ t_{i} $ 's and that no user sent a message to himself. The elements in the lines are separated by single spaces.

## 输出格式

In the first line print integer $ k $ — the number of pairs of friends. In the next $ k $ lines print pairs of friends as " $ A_{i} $ $ B_{i} $ " (without the quotes). You can print users in pairs and the pairs themselves in any order. Each pair must be printed exactly once.

## 说明/提示

In the first sample test case Vasya and Petya are friends because their messages' sending times are one second apart. Anya and Ivan are not, because their messages' sending times differ by more than one second.

## 样例 #1

### 输入

```
4 1
vasya petya 1
petya vasya 2
anya ivan 2
ivan anya 4

```

### 输出

```
1
petya vasya

```

## 样例 #2

### 输入

```
1 1000
a b 0

```

### 输出

```
0

```

