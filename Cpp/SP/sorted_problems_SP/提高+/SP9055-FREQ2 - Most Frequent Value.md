---
title: "FREQ2 - Most Frequent Value"
layout: "post"
diff: 提高+/省选-
pid: SP9055
tag: []
---

# FREQ2 - Most Frequent Value

## 题目描述

给定一个长度为 $n$ 的整数序列 $a$，以及多个查询，每次查询给定查询区间 $i$ 和 $j$（满足 $0 \le i \le j < n$）。对于每个查询，确定在区间中出现次数最多的整数的出现次数。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（满足 $1 \le n,q$）。接下来一行包含 $n$ 个整数，即序列 $a$ 的值（满足 $0 \le a_i \le 10^9$）。接下来的 $q$ 行中，每行包含两个整数 $i$ 和 $j$（满足 $0 \le i \le j < n$），表示一个查询。

## 输出格式

对于每个查询，输出一个整数，表示给定区间中出现次数最多的整数的出现次数。  

由 @[Yangbowen0108](https://www.luogu.com.cn/user/702258) 提供翻译

## 样例 #1

### 输入

```
\n\n5 3\n1 2 1 3 3\n0 2\n1 2\n0 4
```

### 输出

```
\n2\n1\n2\n\nNOTE - This problem is similar to a problem Frequent values.
```

