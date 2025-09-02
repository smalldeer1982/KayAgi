---
title: "Burenka, an Array and Queries"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1718F
tag: []
---

# Burenka, an Array and Queries

## 题目描述

Eugene 给 Burenka 送上了他的生日礼物——一个长度为 $ n $ 的数组 $ a $ ，其中包含从 $ 1 $ 到 $ m $ 的整数。 Burenka 知道 Eugene 非常喜欢互质的两个整数（互质：指整数 $ x $ 和 $ y $ 的最大公约数为 $1$），所以她想问 Eugene $ q $ 关于礼物的问题。

每次 Burenka 都会选择数组 $a$ 的一个子段$ a_l, a_{l + 1}, \ldots, a_r $，并计算这些数字的乘积 $ p = a_l \cdot a_{l + 1} \cdot ... \cdot a_r $ 。然后她会要求 Eugene 计算在 $1 $ 和 $C$ 之间与 $p$ 互质的整数个数。

请帮助 Eugene 回答所有问题。

## 输入格式

在输入的第一行有四个整数 $ n $ , $ m $ , $ C $ , $ q $ ( $ 1 \leq n, q \leq 10^5 $ , $ 1 \leq m \leq 2\cdot 10^4 $ , $ 1 \leq C \leq 10^5 $ ) —— 数组 $ a $ 的长度、$ a_{i} $ 的最大可能值、$ C $ 的值和查询次数.

第二行包含 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_{i} \leq m $ )， 指数组 $ a $ 。

在接下来的 $ q $ 行中每一行代表一次查询。每个查询由两个整数 $ l $ 和 $ r $ ( $ 1 \leq l \leq r \leq n $ ) 组成。

## 输出格式

对于每个询问，输出一个整数 —— Burenka 查询的答案。

## 说明/提示

以下是样例的解释：

1. 在第一个查询中，乘积等于 $1$，与 $1,2,3,4,5$ 互质。
2. 在第二个查询中，乘积等于 $12$，它与 $1$ 和 $5$ 互质。
3. 在第三个查询中，乘积等于 $10$，它与 $1$ 和 $3$ 互质。

## 样例 #1

### 输入

```
5 5 5 3
1 2 3 2 5
1 1
2 4
4 5
```

### 输出

```
5
2
2
```

