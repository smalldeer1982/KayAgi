---
title: "Only Pluses"
layout: "post"
diff: 普及-
pid: CF1992A
tag: ['数学', '贪心']
---

# Only Pluses

## 题目描述

Kmes has written three integers $ a $ , $ b $ and $ c $ in order to remember that he has to give Noobish\_Monk $ a \times b \times c $ bananas.

Noobish\_Monk has found these integers and decided to do the following at most $ 5 $ times:

- pick one of these integers;
- increase it by $ 1 $ .

For example, if $ a = 2 $ , $ b = 3 $ and $ c = 4 $ , then one can increase $ a $ three times by one and increase $ b $ two times. After that $ a = 5 $ , $ b = 5 $ , $ c = 4 $ . Then the total number of bananas will be $ 5 \times 5 \times 4 = 100 $ .

What is the maximum value of $ a \times b \times c $ Noobish\_Monk can achieve with these operations?

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The first and only line of each test case contains three integers $ a $ , $ b $ and $ c $ ( $ 1 \le a, b, c \le 10 $ ) — Kmes's integers.

## 输出格式

For each test case, output a single integer — the maximum amount of bananas Noobish\_Monk can get.

## 样例 #1

### 输入

```
2
2 3 4
10 1 10
```

### 输出

```
100
600
```

