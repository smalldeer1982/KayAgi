---
title: "Two Towers"
layout: "post"
diff: 入门
pid: CF1795A
tag: []
---

# Two Towers

## 题目描述

There are two towers consisting of blocks of two colors: red and blue. Both towers are represented by strings of characters B and/or R denoting the order of blocks in them from the bottom to the top, where B corresponds to a blue block, and R corresponds to a red block.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795A/69c3335e48895bcb4c761995acd0b1c64b9e8d07.png) These two towers are represented by strings BRBB and RBR.You can perform the following operation any number of times: choose a tower with at least two blocks, and move its top block to the top of the other tower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795A/1c4aa5e98141199029dbc159f3efac85b139c1b9.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795A/e96b9925d26bf52f3d8e10b859d46a71421db524.png)The pair of towers is beautiful if no pair of touching blocks has the same color; i. e. no red block stands on top of another red block, and no blue block stands on top of another blue block.

You have to check if it is possible to perform any number of operations (possibly zero) to make the pair of towers beautiful.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 20 $ ) — the number of blocks in the first tower and the number of blocks in the second tower, respectively;
- the second line contains $ s $ — a string of exactly $ n $ characters B and/or R, denoting the first tower;
- the third line contains $ t $ — a string of exactly $ m $ characters B and/or R, denoting the second tower.

## 输出格式

For each test case, print YES if it is possible to perform several (possibly zero) operations in such a way that the pair of towers becomes beautiful; otherwise print NO.

You may print each letter in any case (YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 说明/提示

In the first test case, you can move the top block from the first tower to the second tower (see the third picture).

In the second test case, you can move the top block from the second tower to the first tower $ 6 $ times.

In the third test case, the pair of towers is already beautiful.

## 样例 #1

### 输入

```
4
4 3
BRBB
RBR
4 7
BRBR
RRBRBRB
3 4
RBR
BRBR
5 4
BRBRR
BRBR
```

### 输出

```
YES
YES
YES
NO
```

