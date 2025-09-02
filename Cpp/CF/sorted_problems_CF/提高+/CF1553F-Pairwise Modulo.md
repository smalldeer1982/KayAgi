---
title: "Pairwise Modulo"
layout: "post"
diff: 提高+/省选-
pid: CF1553F
tag: []
---

# Pairwise Modulo

## 题目描述

You have an array $ a $ consisting of $ n $ distinct positive integers, numbered from $ 1 $ to $ n $ . Define $ p_k $ as $ $$$p_k = \sum_{1 \le i, j \le k} a_i \bmod a_j, $ $  where  $ x \\bmod y $  denotes the remainder when  $ x $  is divided by  $ y $ . You have to find and print  $ p\_1, p\_2, \\ldots, p\_n$$$.

## 输入格式

The first line contains $ n $ — the length of the array ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ space-separated distinct integers $ a_1, \ldots, a_n $ ( $ 1 \le a_i \le 3 \cdot 10^5 $ , $ a_i \neq a_j $ if $ i \neq j $ ).

## 输出格式

Print $ n $ integers $ p_1, p_2, \ldots, p_n $ .

## 样例 #1

### 输入

```
4
6 2 7 3
```

### 输出

```
0 2 12 22
```

## 样例 #2

### 输入

```
3
3 2 1
```

### 输出

```
0 3 5
```

