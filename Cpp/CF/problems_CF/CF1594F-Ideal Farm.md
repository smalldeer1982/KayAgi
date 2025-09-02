---
title: "Ideal Farm"
layout: "post"
diff: 提高+/省选-
pid: CF1594F
tag: []
---

# Ideal Farm

## 题目描述

Theofanis decided to visit his uncle's farm. There are $ s $ animals and $ n $ animal pens on the farm. For utility purpose, animal pens are constructed in one row.

Uncle told Theofanis that a farm is lucky if you can distribute all animals in all pens in such a way that there are no empty pens and there is at least one continuous segment of pens that has exactly $ k $ animals in total.

Moreover, a farm is ideal if it's lucky for any distribution without empty pens.

Neither Theofanis nor his uncle knows if their farm is ideal or not. Can you help them to figure it out?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first and only line of each test case contains three integers $ s $ , $ n $ , and $ k $ ( $ 1 \le s, n, k \le 10^{18} $ ; $ n \le s $ ).

## 输出格式

For each test case, print YES (case-insensitive), if the farm is ideal, or NO (case-insensitive) otherwise.

## 说明/提示

For the first and the second test case, the only possible combination is $ [1] $ so there always will be a subsegment with $ 1 $ animal but not with $ 2 $ animals.

## 样例 #1

### 输入

```
4
1 1 1
1 1 2
100 50 200
56220 47258 14497
```

### 输出

```
YES
NO
NO
YES
```

