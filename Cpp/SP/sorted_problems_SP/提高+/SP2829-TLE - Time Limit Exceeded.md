---
title: "TLE - Time Limit Exceeded"
layout: "post"
diff: 提高+/省选-
pid: SP2829
tag: ['枚举', '状态合并', '前缀和']
---

# TLE - Time Limit Exceeded

## 题目描述

Given integers N (1 ≤ N ≤ 50) and M (1 ≤ M ≤ 15), compute the number of sequences a $ _{1} $ , ..., a $ _{N} $ such that:

- 0 ≤ a $ _{i} $ < 2 $ ^{M} $
- a $ _{i} $ is not divisible by c $ _{i} $ (0 < c $ _{i} $ ≤ 2 $ ^{M} $ )
- a $ _{i} $ & a $ _{i+1} $ = 0 (that is, a $ _{i} $ and a $ _{i+1} $ have no common bits in their binary representation)

## 输入格式

The first line contains the number of test cases, T (1 ≤ T ≤ 10). For each test case, the first line contains the integers N and M, and the second line contains the integers c $ _{1} $ , ..., c $ _{N} $ .

## 输出格式

For each test case, output a single integer: the number of sequences described above, modulo 1,000,000,000.

## 样例 #1

### 输入

```
1
2 2
3 2
```

### 输出

```
1
```

