---
title: "Rewards"
layout: "post"
diff: 入门
pid: CF448A
tag: []
---

# Rewards

## 题目描述

Bizon the Champion is called the Champion for a reason.

Bizon the Champion has recently got a present — a new glass cupboard with $ n $ shelves and he decided to put all his presents there. All the presents can be divided into two types: medals and cups. Bizon the Champion has $ a_{1} $ first prize cups, $ a_{2} $ second prize cups and $ a_{3} $ third prize cups. Besides, he has $ b_{1} $ first prize medals, $ b_{2} $ second prize medals and $ b_{3} $ third prize medals.

Naturally, the rewards in the cupboard must look good, that's why Bizon the Champion decided to follow the rules:

- any shelf cannot contain both cups and medals at the same time;
- no shelf can contain more than five cups;
- no shelf can have more than ten medals.

Help Bizon the Champion find out if we can put all the rewards so that all the conditions are fulfilled.

## 输入格式

The first line contains integers $ a_{1} $ , $ a_{2} $ and $ a_{3} $ $ (0<=a_{1},a_{2},a_{3}<=100) $ . The second line contains integers $ b_{1} $ , $ b_{2} $ and $ b_{3} $ $ (0<=b_{1},b_{2},b_{3}<=100) $ . The third line contains integer $ n $ $ (1<=n<=100) $ .

The numbers in the lines are separated by single spaces.

## 输出格式

Print "YES" (without the quotes) if all the rewards can be put on the shelves in the described manner. Otherwise, print "NO" (without the quotes).

## 样例 #1

### 输入

```
1 1 1
1 1 1
4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 1 3
2 3 4
2

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1 0 0
1 0 0
1

```

### 输出

```
NO

```

