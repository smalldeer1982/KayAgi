---
title: "ADAFEAR - Ada and Primal Fear"
layout: "post"
diff: 提高+/省选-
pid: SP33999
tag: ['费用流', '素数判断,质数,筛法']
---

# ADAFEAR - Ada and Primal Fear

## 题目描述

As you might already know, Ada the Ladybug is a farmer. She grows many vegetables. During past months, her crop was attacked by colony of parasites. Each vegetable was attacked by **A $ _{i} $**  parasites. Ada has only limited answer for this. She bought a few bottles with **Primal Fear**, which is a mixture agains parasites.

**Primal Fear** works in following way: Each **Primal Fear** bottle has a power assigned to it (which is coincidentally a prime number). If it is applied to a vegetable with  **N**  parasites on it, either the **N** is divisible by its **power**, then the size of colony is reduced to **N/power**, or - if the size is not divisible - then it has no effect. Also, as soon as you apply mixture against a colony, the rest of colony will become immune agains **Primal Fear**.

Ada didn't know what to buy so she bought one bottle of every possible **power**. Can you find out the best strategy to fight agains parasites?

## 输入格式

The first line of input will contain **1 , the number of vegetable.**

The line will contain **N** numbers **1 , the size of colony on **i $ ^{th} $**  vegetable.**

## 输出格式

Print the minimum sum of sizes of colonies which could be achieved after applying **Primal Fear** optimally.



---

---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```



---

