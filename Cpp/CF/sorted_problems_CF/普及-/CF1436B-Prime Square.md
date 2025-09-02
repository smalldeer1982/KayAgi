---
title: "Prime Square"
layout: "post"
diff: 普及-
pid: CF1436B
tag: []
---

# Prime Square

## 题目描述

Sasha likes investigating different math objects, for example, magic squares. But Sasha understands that magic squares have already been studied by hundreds of people, so he sees no sense of studying them further. Instead, he invented his own type of square — a prime square.

A square of size $ n \times n $ is called prime if the following three conditions are held simultaneously:

- all numbers on the square are non-negative integers not exceeding $ 10^5 $ ;
- there are no prime numbers in the square;
- sums of integers in each row and each column are prime numbers.

Sasha has an integer $ n $ . He asks you to find any prime square of size $ n \times n $ . Sasha is absolutely sure such squares exist, so just help him!

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10 $ ) — the number of test cases.

Each of the next $ t $ lines contains a single integer $ n $ ( $ 2 \le n \le 100 $ ) — the required size of a square.

## 输出格式

For each test case print $ n $ lines, each containing $ n $ integers — the prime square you built. If there are multiple answers, print any.

## 样例 #1

### 输入

```
2
4
2
```

### 输出

```
4 6 8 1
4 9 9 9
4 10 10 65
1 4 4 4
1 1
1 1
```

