---
title: "Juicer"
layout: "post"
diff: 入门
pid: CF709A
tag: []
---

# Juicer

## 题目描述

Kolya is going to make fresh orange juice. He has $ n $ oranges of sizes $ a_{1},a_{2},...,a_{n} $ . Kolya will put them in the juicer in the fixed order, starting with orange of size $ a_{1} $ , then orange of size $ a_{2} $ and so on. To be put in the juicer the orange must have size not exceeding $ b $ , so if Kolya sees an orange that is strictly greater he throws it away and continues with the next one.

The juicer has a special section to collect waste. It overflows if Kolya squeezes oranges of the total size strictly greater than $ d $ . When it happens Kolya empties the waste section (even if there are no more oranges) and continues to squeeze the juice. How many times will he have to empty the waste section?

## 输入格式

The first line of the input contains three integers $ n $ , $ b $ and $ d $ ( $ 1<=n<=100000 $ , $ 1<=b<=d<=1000000 $ ) — the number of oranges, the maximum size of the orange that fits in the juicer and the value $ d $ , which determines the condition when the waste section should be emptied.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=1000000 $ ) — sizes of the oranges listed in the order Kolya is going to try to put them in the juicer.

## 输出格式

Print one integer — the number of times Kolya will have to empty the waste section.

## 说明/提示

In the first sample, Kolya will squeeze the juice from two oranges and empty the waste section afterwards.

In the second sample, the orange won't fit in the juicer so Kolya will have no juice at all.

## 样例 #1

### 输入

```
2 7 10
5 6

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 5 10
7

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 10 10
5 7 7

```

### 输出

```
1

```

## 样例 #4

### 输入

```
1 1 1
1

```

### 输出

```
0

```

