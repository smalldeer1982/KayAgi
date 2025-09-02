---
title: "DCES - Dynamic Congruence Equation System"
layout: "post"
diff: 难度0
pid: SP9543
tag: []
---

# DCES - Dynamic Congruence Equation System

## 题目描述

设有以下形式的同余方程组：

\[ x[1] = k_1 x[p_1] + b_1 \pmod{10007} \]
\[ x[2] = k_2 x[p_2] + b_2 \pmod{10007} \]
\[ \vdots \]
\[ x[n] = k_n x[p_n] + b_n \pmod{10007} \]

你需要根据以下指令来实现操作：

- `A i`：询问当前第 \( i \) 个未知数 \( x[i] \) 的值。如果没有解则输出 `-1`，如果有多个解则输出 `-2`。
- `C i k p b`：将第 \( i \) 个方程修改为新的同余方程。

## 输入格式

第一行为两个整数 \( N \) 和 \( Q \)，表示同余方程的个数和查询的次数。接下来的 \( Q \) 行分别给出具体的查询内容。

## 输出格式

对于每个查询，输出相应的结果。

## 说明/提示

1 ≤ \( N, Q \) ≤ 100,000。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1:\n5\n2 2 1\n2 3 2\n2 4 3\n2 5 4\n2 3 5\n5\nA 1\nA 2\nC 5 3 1 1\nA 4\nA 5
```

### 输出

```
1:\n4276\n7141\n4256\n2126\n\nInput 2:\n4\n0 1 0\n1 3 0\n1 4 0\n1 2 0\n6\nA 1\nA 2\nA 3\nA 4\nC 1 1 5 1\nA 1\n\nOutput 2:\n0\n-2\n-2\n-2\n-1\n\n
```

