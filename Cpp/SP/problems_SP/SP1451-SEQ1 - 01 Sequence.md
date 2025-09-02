---
title: "SEQ1 - 01 Sequence"
layout: "post"
diff: 难度0
pid: SP1451
tag: []
---

# SEQ1 - 01 Sequence

## 题目描述

The input consists of exactly 5 test cases in the following format:

## 输入格式

```
N A0 B0 L0 A1 B1 L1 [3<=N<=1000,1<=A0<=B0<=L0<=N,1<=A1<=B1<=L1<=N]
```

## 输出格式

Exactly 5 lines,each contains:

a) A N-character sequence (We name it S) consisting of only characters '0' and '1' and no extra whitespaces, which satisfy the following conditions:

- The number of '0' in any consecutive subsequence of S whose length is L0 is not more than B0 and not less than A0.
- The number of '1' in any consecutive subsequence of S whose length is L1 is not more than B1 and not less than A1.

## 样例 #1

### 输入

```
6 1 2 3 1 1 2
[and 4 test cases more]
```

### 输出

```
010101
[and 4 test cases more]
```

