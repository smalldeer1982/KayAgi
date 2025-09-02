---
title: "Ducci序列 Ducci Sequence"
layout: "post"
diff: 普及-
pid: UVA1594
tag: ['模拟']
---

# Ducci序列 Ducci Sequence

## 题目描述

对于一个 $n$ 元组（$a_1,a_2,\cdots,a_n$），可以对每个数求出它和下一个数的差的绝对值，得到一个新的 $n$ 元组（$|a_1-a_2|,|a_2-a_3|,\cdots,|a_n-a_1|$）。重复这个过程，得到的序列称为 Ducci 序列，例如：

$$(8,11,2,7)\rightarrow(3,9,5,1)\rightarrow(6,4,4,2)\rightarrow(2,0,2,4)\rightarrow(2,2,2,2)\rightarrow(0,0,0,0)$$

也有的 Ducci 序列最终会循环。输入 $n$ 元组（$3\le n\le15$），你的任务是判断它最终会变成0还是会循环。输入保证最多 $1000$ 步就会变成 $0$ 或循环。

## 输出格式

感谢 @andyli 提供的翻译

## 样例 #1

### 输入

```
4
4
8 11 2 7
5
4 2 0 2 0
7
0 0 0 0 0 0 0
6
1 2 3 1 2 3

```

### 输出

```
ZERO
LOOP
ZERO
LOOP

```

