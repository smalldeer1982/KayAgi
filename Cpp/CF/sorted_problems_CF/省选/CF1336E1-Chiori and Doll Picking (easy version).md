---
title: "Chiori and Doll Picking (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1336E1
tag: []
---

# Chiori and Doll Picking (easy version)

## 题目描述

This is the easy version of the problem. The only difference between easy and hard versions is the constraint of $ m $ . You can make hacks only if both versions are solved.

Chiori loves dolls and now she is going to decorate her bedroom!

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336E1/7f2871c87cb2f7ef2408d5e1359121eb7612b9c0.png)As a doll collector, Chiori has got $ n $ dolls. The $ i $ -th doll has a non-negative integer value $ a_i $ ( $ a_i < 2^m $ , $ m $ is given). Chiori wants to pick some (maybe zero) dolls for the decoration, so there are $ 2^n $ different picking ways.

Let $ x $ be the bitwise-xor-sum of values of dolls Chiori picks (in case Chiori picks no dolls $ x = 0 $ ). The value of this picking way is equal to the number of $ 1 $ -bits in the binary representation of $ x $ . More formally, it is also equal to the number of indices $ 0 \leq i < m $ , such that $ \left\lfloor \frac{x}{2^i} \right\rfloor $ is odd.

Tell her the number of picking ways with value $ i $ for each integer $ i $ from $ 0 $ to $ m $ . Due to the answers can be very huge, print them by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 35 $ ) — the number of dolls and the maximum value of the picking way.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^m $ ) — the values of dolls.

## 输出格式

Print $ m+1 $ integers $ p_0, p_1, \ldots, p_m $ — $ p_i $ is equal to the number of picking ways with value $ i $ by modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 4
3 5 8 14
```

### 输出

```
2 2 6 6 0
```

## 样例 #2

### 输入

```
6 7
11 45 14 9 19 81
```

### 输出

```
1 2 11 20 15 10 5 0
```

