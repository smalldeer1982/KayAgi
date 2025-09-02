---
title: "INTCOMB - Combination Of Integers"
layout: "post"
diff: 难度0
pid: SP8281
tag: []
---

# INTCOMB - Combination Of Integers

## 题目描述

给定 $n$ 个正整数 $a_1, a_2, \ldots, a_n$。一个非负整数组合表示为形如 $a_1 \cdot b_1 + a_2 \cdot b_2 + \cdots + a_n \cdot b_n$ 的形式，其中每个 $b_1, b_2, \ldots, b_n$ 都是非负整数。你需要找出有多少个正整数不能通过这些数的非负整数组合形式表示出来。

## 输入格式

第一行包含一个整数，表示测试用例的数量（约 30 个）。每个测试用例由一行构成。行的第一个整数为 $n$，表示有 $n$ 个整数 $a_1, a_2, \ldots, a_n$。接着是 $n$ 个整数，每个整数范围在 $1$ 到 $100,000$ 之间。整数之间以空格分隔。

## 输出格式

对于每个测试用例，输出一行结果。如果存在有限个正整数不能表示为通过 $a_1, a_2, \ldots, a_n$ 组合得到的形式，输出这个数量。若无法计数，则输出 `Infinite`（无引号）。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3 \n2 2 4 \n2 4 5 \n3 11 12 13\n
```

### 输出

```
Infinite \n6 \n30\nExplanation\nSample Test 2 :\nYou cannot express 1,2,3,6,7 and 11 using only the integers 4 and 5.\n\n
```

