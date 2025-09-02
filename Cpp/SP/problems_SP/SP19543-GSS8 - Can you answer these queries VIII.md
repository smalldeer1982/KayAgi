---
title: "GSS8 - Can you answer these queries VIII"
layout: "post"
diff: 省选/NOI-
pid: SP19543
tag: []
---

# GSS8 - Can you answer these queries VIII

## 题目描述

You are given sequence A\[0\], A\[1\]...A\[N - 1\]. (0 <= A\[i\] < 2^32)

You are to perform Q operations:

1\. **I pos val**, insert number **val** in sequence before element with index **pos**. (0 <= val < 2^32, if **pos** = **current\_length** then you should add number to the end of the sequence)

2\. **D pos**, delete element with index **pos** from sequence.

3\. **R pos val**, replace element with idex **pos** by **val**. (0 <= val < 2^32)

4\. **Q l r k**, answer Σ A\[i\] \* (i - l + 1)^k modulo 2^32, for l <= i <= r. (0 <= k <= 10)

## 样例 #1

### 输入

```
4
1 2 3 5
7
Q 0 2 0
I 3 4
Q 2 4 1
D 0
Q 0 3 1
R 1 2
Q 0 1 0
```

### 输出

```
6
26
40
4
```

