# [NERC2024] DAG Serialization

## 题目描述

考虑一个简单的单比特布尔寄存器，它支持两个操作：

- $\textbf{set}$ —— 如果寄存器是 $\textbf{false}$，则将其设置为 $\textbf{true}$，并返回 $\textbf{true}$；否则，返回 $\textbf{false}$；
- $\textbf{unset}$ —— 如果寄存器是 $\textbf{true}$，则将其设置为 $\textbf{false}$，并返回 $\textbf{true}$；否则，返回 $\textbf{false}$。

寄存器的初始状态为 $\textbf{false}$。假设有 $n$ 个操作 $op_i$（$1 \le i \le n$），并且 **至多有两个操作返回 true**。同时，我们给出了操作的部分顺序，表示为一个有向无环图（DAG）：边 $i \rightarrow j$ 表示 $op_i$ 在 $op_j$ 之前发生。你的任务是判断是否可能将这些操作排列成某个线性顺序，使得符合给定的部分顺序，并且如果按照该顺序执行操作，得到的结果与给定的一致。

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
5 2```

### 输出

```
5 1 3 2 4```

## 样例 #2

### 输入

```
3
unset true
unset false
set true
0```

### 输出

```
2 3 1```

## 样例 #3

### 输入

```
2
unset false
set true
1
2 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
2
unset false
set false
0```

### 输出

```
-1```

