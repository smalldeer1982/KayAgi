---
title: "Game with Multiset"
layout: "post"
diff: 普及/提高-
pid: CF1913C
tag: []
---

# Game with Multiset

## 题目描述

In this problem, you are initially given an empty multiset. You have to process two types of queries:

1. ADD $ x $ — add an element equal to $ 2^{x} $ to the multiset;
2. GET $ w $ — say whether it is possible to take the sum of some subset of the current multiset and get a value equal to $ w $ .

## 输入格式

The first line contains one integer $ m $ ( $ 1 \le m \le 10^5 $ ) — the number of queries.

Then $ m $ lines follow, each of which contains two integers $ t_i $ , $ v_i $ , denoting the $ i $ -th query. If $ t_i = 1 $ , then the $ i $ -th query is ADD $ v_i $ ( $ 0 \le v_i \le 29 $ ). If $ t_i = 2 $ , then the $ i $ -th query is GET $ v_i $ ( $ 0 \le v_i \le 10^9 $ ).

## 输出格式

For each GET query, print YES if it is possible to choose a subset with sum equal to $ w $ , or NO if it is impossible.

## 样例 #1

### 输入

```
5
1 0
1 0
1 0
2 3
2 4
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
7
1 0
1 1
1 2
1 10
2 4
2 6
2 7
```

### 输出

```
YES
YES
YES
```

