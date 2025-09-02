---
title: "Taxi"
layout: "post"
diff: 普及-
pid: CF158B
tag: []
---

# Taxi

## 题目描述

After the lessons $ n $ groups of schoolchildren went outside and decided to visit Polycarpus to celebrate his birthday. We know that the $ i $ -th group consists of $ s_{i} $ friends ( $ 1<=s_{i}<=4 $ ), and they want to go to Polycarpus together. They decided to get there by taxi. Each car can carry at most four passengers. What minimum number of cars will the children need if all members of each group should ride in the same taxi (but one taxi can take more than one group)?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of groups of schoolchildren. The second line contains a sequence of integers $ s_{1},s_{2},...,s_{n} $ ( $ 1<=s_{i}<=4 $ ). The integers are separated by a space, $ s_{i} $ is the number of children in the $ i $ -th group.

## 输出格式

Print the single number — the minimum number of taxis necessary to drive all children to Polycarpus.

## 说明/提示

In the first test we can sort the children into four cars like this:

- the third group (consisting of four children),
- the fourth group (consisting of three children),
- the fifth group (consisting of three children),
- the first and the second group (consisting of one and two children, correspondingly).

There are other ways to sort the groups into four cars.

## 样例 #1

### 输入

```
5
1 2 4 3 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8
2 3 4 4 2 1 3 1

```

### 输出

```
5

```

