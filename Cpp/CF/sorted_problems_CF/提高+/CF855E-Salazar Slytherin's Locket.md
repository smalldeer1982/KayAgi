---
title: "Salazar Slytherin's Locket"
layout: "post"
diff: 提高+/省选-
pid: CF855E
tag: ['数位 DP', '状态合并', '进制']
---

# Salazar Slytherin's Locket

## 题目描述

Harry came to know from Dumbledore that Salazar Slytherin's locket is a horcrux. This locket was present earlier at 12 Grimmauld Place, the home of Sirius Black's mother. It was stolen from there and is now present in the Ministry of Magic in the office of Dolorous Umbridge, Harry's former Defense Against the Dark Arts teacher.

Harry, Ron and Hermione are infiltrating the Ministry. Upon reaching Umbridge's office, they observed a code lock with a puzzle asking them to calculate count of magic numbers between two integers $ l $ and $ r $ (both inclusive).

Harry remembered from his detention time with Umbridge that she defined a magic number as a number which when converted to a given base $ b $ , all the digits from $ 0 $ to $ b-1 $ appear even number of times in its representation without any leading zeros.

You have to answer $ q $ queries to unlock the office. Each query has three integers $ b_{i} $ , $ l_{i} $ and $ r_{i} $ , the base and the range for which you have to find the count of magic numbers.

## 输入格式

First line of input contains $ q $ ( $ 1<=q<=10^{5} $ ) — number of queries.

Each of the next $ q $ lines contain three space separated integers $ b_{i} $ , $ l_{i} $ , $ r_{i} $ ( $ 2<=b_{i}<=10 $ , $ 1<=l_{i}<=r_{i}<=10^{18} $ ).

## 输出格式

You have to output $ q $ lines, each containing a single integer, the answer to the corresponding query.

## 说明/提示

In sample test case $ 1 $ , for first query, when we convert numbers $ 4 $ to $ 9 $ into base $ 2 $ , we get:

- $ 4=100_{2} $ ,
- $ 5=101_{2} $ ,
- $ 6=110_{2} $ ,
- $ 7=111_{2} $ ,
- $ 8=1000_{2} $ ,
- $ 9=1001_{2} $ .

Out of these, only base $ 2 $ representation of $ 9 $ has even number of $ 1 $ and $ 0 $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
2
2 4 9
3 1 10

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
2
2 1 100
5 1 100

```

### 输出

```
21
4

```

