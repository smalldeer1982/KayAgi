---
title: "Esports in Berland"
layout: "post"
diff: 难度0
pid: CF2087G
tag: []
---

# Esports in Berland

## 题目描述

Recently, esports has been recognized as an official sport in Berland, and regular competitions have begun to take place. Riding the wave of popularity, Monocarp also decided to participate in the upcoming competitions (besides, prizes have never hurt anyone).

In each of the following $ n $ days, one competition will be held. Monocarp would like to participate in all of them, but unfortunately, his current skill level $ s $ is $ 0 $ . At the same time, the prize money Monocarp can earn in competitions depends on his skill level. Therefore, Monocarp decided that he could sacrifice participating in some competitions to train and increase his skill level on those days.

In general, on the $ i $ -th day, Monocarp can:

- either participate in the $ i $ -th competition and earn $ a_i + s $ units of money, where $ s $ is his current skill level;
- or skip the competition to train: Monocarp will earn nothing but will increase his skill level $ s $ by $ 1 $ .

Help Monocarp calculate his maximum total income and the number of training plans with such income. Two training plans are considered different if there exists a day that is a training day in one plan and a competition day in the other one.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of days when competitions will take place.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^6 $ ) — the base prize money that Monocarp can expect.

## 输出格式

Print two integers — the maximum total income that Monocarp can achieve with an optimal training plan and the number of such plans.

Since the number of plans may be too big, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, Monocarp can either participate or skip the competition — in both cases he will get $ 0 $ units.

In the second example, it is optimal to simply participate in the competition.

In the third example, there are two training plans. Monocarp can

1. either train for the first two days and then participate in the competitions on the remaining days: Monocarp will earn $ 3 \cdot (0 + 2) = 6 $ units;
2. or train for the first three days: Monocarp will earn $ 2 \cdot (0 + 3) = 6 $ units.

In the fourth example, Monocarp can either participate in all competitions or skip any one day.

## 样例 #1

### 输入

```
1
0
```

### 输出

```
0 2
```

## 样例 #2

### 输入

```
1
42
```

### 输出

```
42 1
```

## 样例 #3

### 输入

```
5
0 0 0 0 0
```

### 输出

```
6 2
```

## 样例 #4

### 输入

```
6
5 4 3 2 1 0
```

### 输出

```
15 7
```

## 样例 #5

### 输入

```
10
5 9 0 3 2 0 2 2 9 9
```

### 输出

```
53 3
```

