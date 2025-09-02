---
title: "Preparing for the Contest"
layout: "post"
diff: 入门
pid: CF1914B
tag: ['构造']
---

# Preparing for the Contest

## 题目描述

Monocarp is practicing for a big contest. He plans to solve $ n $ problems to make sure he's prepared. Each of these problems has a difficulty level: the first problem has a difficulty level of $ 1 $ , the second problem has a difficulty level of $ 2 $ , and so on, until the last ( $ n $ -th) problem, which has a difficulty level of $ n $ .

Monocarp will choose some order in which he is going to solve all $ n $ problems. Whenever he solves a problem which is more difficult than the last problem he solved, he gets excited because he feels like he's progressing. He doesn't get excited when he solves the first problem in his chosen order.

For example, if Monocarp solves the problems in the order $ [3, \underline{5}, 4, 1, \underline{6}, 2] $ , he gets excited twice (the corresponding problems are underlined).

Monocarp wants to get excited exactly $ k $ times during his practicing session. Help him to choose the order in which he has to solve the problems!

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 50 $ ; $ 0 \le k \le n - 1 $ ).

## 输出格式

For each test case, print $ n $ distinct integers from $ 1 $ to $ n $ , denoting the order in which Monocarp should solve the problems. If there are multiple answers, print any of them.

It can be shown that under the constraints of the problem, the answer always exists.

## 样例 #1

### 输入

```
3
6 2
5 4
5 0
```

### 输出

```
3 5 4 1 6 2
1 2 3 4 5
5 4 3 2 1
```

