---
title: "Vacations"
layout: "post"
diff: 普及/提高-
pid: CF698A
tag: []
---

# Vacations

## 题目描述

Vasya has $ n $ days of vacations! So he decided to improve his IT skills and do sport. Vasya knows the following information about each of this $ n $ days: whether that gym opened and whether a contest was carried out in the Internet on that day. For the $ i $ -th day there are four options:

1. on this day the gym is closed and the contest is not carried out;
2. on this day the gym is closed and the contest is carried out;
3. on this day the gym is open and the contest is not carried out;
4. on this day the gym is open and the contest is carried out.

On each of days Vasya can either have a rest or write the contest (if it is carried out on this day), or do sport (if the gym is open on this day).

Find the minimum number of days on which Vasya will have a rest (it means, he will not do sport and write the contest at the same time). The only limitation that Vasya has — he does not want to do the same activity on two consecutive days: it means, he will not do sport on two consecutive days, and write the contest on two consecutive days.

## 输入格式

The first line contains a positive integer $ n $ ( $ 1<=n<=100 $ ) — the number of days of Vasya's vacations.

The second line contains the sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=3 $ ) separated by space, where:

- $ a_{i} $ equals 0, if on the $ i $ -th day of vacations the gym is closed and the contest is not carried out;
- $ a_{i} $ equals 1, if on the $ i $ -th day of vacations the gym is closed, but the contest is carried out;
- $ a_{i} $ equals 2, if on the $ i $ -th day of vacations the gym is open and the contest is not carried out;
- $ a_{i} $ equals 3, if on the $ i $ -th day of vacations the gym is open and the contest is carried out.

## 输出格式

Print the minimum possible number of days on which Vasya will have a rest. Remember that Vasya refuses:

- to do sport on any two consecutive days,
- to write the contest on any two consecutive days.

## 说明/提示

In the first test Vasya can write the contest on the day number 1 and do sport on the day number 3. Thus, he will have a rest for only 2 days.

In the second test Vasya should write contests on days number 1, 3, 5 and 7, in other days do sport. Thus, he will not have a rest for a single day.

In the third test Vasya can do sport either on a day number 1 or number 2. He can not do sport in two days, because it will be contrary to the his limitation. Thus, he will have a rest for only one day.

## 样例 #1

### 输入

```
4
1 3 2 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
1 3 3 2 1 2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2
2 2

```

### 输出

```
1

```

