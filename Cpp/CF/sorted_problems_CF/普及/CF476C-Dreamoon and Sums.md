---
title: "Dreamoon and Sums"
layout: "post"
diff: 普及/提高-
pid: CF476C
tag: []
---

# Dreamoon and Sums

## 题目描述

Dreamoon loves summing up something for no reason. One day he obtains two integers $ a $ and $ b $ occasionally. He wants to calculate the sum of all nice integers. Positive integer $ x $ is called nice if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/4c08c1c4aa605a7661ec02846fcac8a50385ec4f.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/199c47ec051f565599e933f0f95a0d9069b4a2ef.png), where $ k $ is some integer number in range $ \[1,a\] $ .

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/f26b8897bea7b2ad070a91154fff6b5d3d6ecc9d.png) we denote the quotient of integer division of $ x $ and $ y $ . By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/e60b09b62a19a62f637ba6a66556f554bcb4dbf9.png) we denote the remainder of integer division of $ x $ and $ y $ . You can read more about these operations here: http://goo.gl/AcsXhT.

The answer may be large, so please print its remainder modulo $ 1000000007 $ ( $ 10^{9}+7 $ ). Can you compute it faster than Dreamoon?

## 输入格式

The single line of the input contains two integers $ a $ , $ b $ ( $ 1<=a,b<=10^{7} $ ).

## 输出格式

Print a single integer representing the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first sample, there are no nice integers because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/05cf42fbd3551fd38e1ab2adca655a95016ccd28.png) is always zero.

For the second sample, the set of nice integers is $ {3,5} $ .

## 样例 #1

### 输入

```
1 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
8

```

