---
title: "DAG Serialization"
layout: "post"
diff: 难度0
pid: CF2052D
tag: []
---

# DAG Serialization

## 题目描述

考虑一个简单的单比特布尔寄存器，支持两种操作：

- **set** — 如果寄存器当前值为 false，则将其设置为 true，并返回 true；否则，返回 false。
- **unset** — 如果寄存器当前值为 true，则将其设置为 false，并返回 true；否则，返回 false。

寄存器的初始状态为 false。假设有 $n$ 个操作 $op_i$ ($1 \leq i \leq n$)，其中至多有两个操作返回 true。并且我们给出了操作的部分顺序关系，表示为有向无环图（DAG）：有一条边 $i \rightarrow j$，表示操作 $op_i$ 在操作 $op_j$ 之前发生。

你的任务是判断是否可以将这些操作按某种线性顺序排列，既满足给定的部分顺序关系，又使得如果按照这个顺序执行操作，得到的结果与题目中给定的结果一致。

## 输入格式

- 第一行，一个整数 $n$，表示操作的数量 ($1 \leq n \leq 10^5$)。
- 接下来的 $n$ 行，每行一个操作，格式为 `"type result"`，其中 `type` 是 `"set"` 或 `"unset"`，`result` 是 `"true"` 或 `"false"`。题目保证最多只有两个操作的 `result` 为 `"true"`。
- 接下来的第一行，一个整数 $m$，表示DAG的边数 ($0 \leq m \leq 10^5$)。
- 接下来的 $m$ 行，每行描述一条边，格式为两个整数 $a$ 和 $b$，表示有一条从操作 $op_a$ 到操作 $op_b$ 的边，表示操作 $op_a$ 在操作 $op_b$ 之前执行。

## 输出格式

输出一个满足DAG约束并且操作结果符合给定要求的操作线性顺序。如果无法找到这样的顺序，则输出 $-1$。

## 样例 #1

### 输入

```
5
set true
unset true
set false
unset false
unset false
2
1 4
5 2
```

### 输出

```
5 1 3 2 4
```

## 样例 #2

### 输入

```
3
unset true
unset false
set true
0
```

### 输出

```
2 3 1
```

## 样例 #3

### 输入

```
2
unset false
set true
1
2 1
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
unset false
set false
0
```

### 输出

```
-1
```

