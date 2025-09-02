---
title: "Applejack and Storages"
layout: "post"
diff: 普及/提高-
pid: CF1393B
tag: []
---

# Applejack and Storages

## 题目描述

你一开始有 $n$ 根木棍，接下来有 $q$ 次操作。

操作如下:
* `+ x` 增加一根长度为 $x$ 的木棍。
* `- x` 减少一根长度为 $x$ 的木棍，保证减少之前有长为 $x$ 的木棍。

你要计算出每次操作之后能否用 $8$ 根木棍拼出一个矩形（可以是正方形）和一个正方形。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 输入格式

第一行为 $n(1 \leq n \leq 10^5)$.
第二行 $a_1, a_2, \dots, a_n(1 \leq a_i \leq 10^5)$ 个正整数，表示一开始你拥有的木棍。

## 输出格式

每个询问输出一行答案，`YES` 或者 `NO`。

## 样例 #1

### 输入

```
6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2
```

### 输出

```
NO
YES
NO
NO
NO
YES
```

