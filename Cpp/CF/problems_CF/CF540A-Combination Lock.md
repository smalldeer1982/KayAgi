---
title: "Combination Lock"
layout: "post"
diff: 入门
pid: CF540A
tag: []
---

# Combination Lock

## 题目描述

Scrooge McDuck keeps his most treasured savings in a home safe with a combination lock. Each time he wants to put there the treasures that he's earned fair and square, he has to open the lock.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/bc30440b728dab506bc0137277173502d20b8841.png)The combination lock is represented by $ n $ rotating disks with digits from 0 to 9 written on them. Scrooge McDuck has to turn some disks so that the combination of digits on the disks forms a secret combination. In one move, he can rotate one disk one digit forwards or backwards. In particular, in one move he can go from digit 0 to digit 9 and vice versa. What minimum number of actions does he need for that?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of disks on the combination lock.

The second line contains a string of $ n $ digits — the original state of the disks.

The third line contains a string of $ n $ digits — Scrooge McDuck's combination that opens the lock.

## 输出格式

Print a single integer — the minimum number of moves Scrooge McDuck needs to open the lock.

## 说明/提示

In the sample he needs 13 moves:

- 1 disk: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/74b81554af4ec904c00ba445de691ffae11c433d.png)
- 2 disk: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/f0e93fe15f009d2edfc9576e480c101f5ab03643.png)
- 3 disk: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/21d65ec4d88e83fe36e0cd828b25bd9d0b7477a4.png)
- 4 disk: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/59b1274875f62b1bcafaab3664524521999fe1f0.png)
- 5 disk: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540A/c41ce180478887e8a68b9ae3d8650975f2445329.png)

## 样例 #1

### 输入

```
5
82195
64723

```

### 输出

```
13

```

