---
title: "Maximum modulo equality"
layout: "post"
diff: 普及/提高-
pid: CF2050F
tag: ['数论', 'ST 表']
---

# Maximum modulo equality

## 题目描述

给你一个长度为 $n$ 的数组 $a$ 和 $q$ 次查询。  
每次查询给定两个数 $l$ 和 $r$，求出最大的 $m$ 使得 $a_l \bmod m = a_{l + 1} \bmod m = \dots = a_r \bmod m$，其中 $a \bmod b$ 是 $a$ 除以 $b$ 的余数。  
**特别的，当 $m$ 可能是无限大时，请输出 $0$。**

## 输入格式

第一行输入一个整数 $t(1 \le t \le 10^4)$，表示测试用例数。  
对于每个测试用例：
+ 第一行输入两个整数 $n$ 和 $q(1 \le n, q \le 2 \times 10^5)$，表示数组长度和查询次数。  
+ 第二行输入 $n$ 个整数 $a_i(1 \le a_i \le 10^9)$，表示数组中的元素。  
+ 接下来的 $q$ 行中，每行输入两个整数 $l$ 和 $r(1 \le l \le r \le n)$，表示查询范围。

保证 $\sum n, \sum q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
3
5 5
5 14 2 6 3
4 5
1 4
2 4
3 5
1 1
1 1
7
1 1
3 2
1 7 8
2 3
1 2
```

### 输出

```
3 1 4 1 0 
0 
1 6
```

