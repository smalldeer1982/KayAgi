---
title: "Minibuses on Venus (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1808E3
tag: []
---

# Minibuses on Venus (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the three versions is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

Maxim is a minibus driver on Venus.

To ride on Maxim's minibus, you need a ticket. Each ticket has a number consisting of $ n $ digits. However, as we know, the residents of Venus use a numeral system with base $ k $ , rather than the decimal system. Therefore, the ticket number can be considered as a sequence of $ n $ integers from $ 0 $ to $ k-1 $ , inclusive.

The residents of Venus consider a ticket to be lucky if there is a digit on it that is equal to the sum of the remaining digits, modulo $ k $ . For example, if $ k=10 $ , then the ticket $ 7135 $ is lucky because $ 7 + 1 + 5 \equiv 3 \pmod{10} $ . On the other hand, the ticket $ 7136 $ is not lucky because no digit is equal to the sum of the others modulo $ 10 $ .

Once, while on a trip, Maxim wondered: how many lucky tickets exist? At the same time, Maxim understands that this number can be very large, so he is interested only in the answer modulo some prime number $ m $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808E3/2314a7c75bce1209ddf61a583b83dbea8efe39a0.png)

## 输入格式

The only line of the input contains three integers $ n $ , $ k $ and $ m $ ( $ 1 \le n \le 10^{18} $ , $ 1 \le k \le 2000 $ , $ 10^8 \le m \le 10^9 + 7 $ , $ m $ is a prime number) — the number of digits on the ticket, the base of the numeral system on Venus, and the module for answer calculation.

## 输出格式

Print one integer — the number of lucky tickets modulo $ m $ , i. e. the remainder after dividing the answer by $ m $ .

## 说明/提示

In the first example, there are only four lucky tickets: $ 000 $ , $ 011 $ , $ 101 $ , and $ 110 $ .

## 样例 #1

### 输入

```
3 2 1000000007
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4 1000000007
```

### 输出

```
28
```

