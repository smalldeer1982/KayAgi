---
title: "La Vaca Saturno Saturnita"
layout: "post"
diff: 提高+/省选-
pid: CF2094H
tag: ['二分', '数论', '根号分治']
---

# La Vaca Saturno Saturnita

## 题目描述

Saturnita 的情绪取决于一个长度为 $n$ 的数组 $a$（只有他知道其含义）以及一个函数 $f(k, a, l, r)$（只有他知道如何计算）。以下是该函数的伪代码实现：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

给定 $q$ 个查询，每个查询包含整数 $k$、$l$ 和 $r$。对于每个查询，请输出 $f(k,a,l,r)$ 的值。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \leq n \leq 10^5$，$1 \leq q \leq 5 \cdot 10^4$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$2 \leq a_i \leq 10^5$）。

接下来的 $q$ 行，每行包含三个整数 $k$、$l$ 和 $r$（$1 \leq k \leq 10^5$，$1 \leq l \leq r \leq n$）。

保证所有测试用例的 $n$ 之和不超过 $10^5$，且所有测试用例的 $q$ 之和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个查询，在新的一行输出答案。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
2 3 5 7 11
2 1 5
2 2 4
2310 1 5
4 3
18 12 8 9
216 1 2
48 2 4
82944 1 4
```

### 输出

```
5
6
1629
13
12
520
```

