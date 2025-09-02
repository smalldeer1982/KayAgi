---
title: "Single-use Stones"
layout: "post"
diff: 普及+/提高
pid: CF965D
tag: []
---

# Single-use Stones

## 题目描述

A lot of frogs want to cross a river. A river is $ w $ units width, but frogs can only jump $ l $ units long, where $ l < w $ . Frogs can also jump on lengths shorter than $ l $ . but can't jump longer. Hopefully, there are some stones in the river to help them.

The stones are located at integer distances from the banks. There are $ a_i $ stones at the distance of $ i $ units from the bank the frogs are currently at. Each stone can only be used once by one frog, after that it drowns in the water.

What is the maximum number of frogs that can cross the river, given that then can only jump on the stones?

## 输入格式

The first line contains two integers $ w $ and $ l $ ( $ 1 \le l < w \le 10^5 $ ) — the width of the river and the maximum length of a frog's jump.

The second line contains $ w - 1 $ integers $ a_1, a_2, \ldots, a_{w-1} $ ( $ 0 \le a_i \le 10^4 $ ), where $ a_i $ is the number of stones at the distance $ i $ from the bank the frogs are currently at.

## 输出格式

Print a single integer — the maximum number of frogs that can cross the river.

## 说明/提示

In the first sample two frogs can use the different stones at the distance $ 5 $ , and one frog can use the stones at the distances $ 3 $ and then $ 8 $ .

In the second sample although there are two stones at the distance $ 5 $ , that does not help. The three paths are: $ 0 \to 3 \to 6 \to 9 \to 10 $ , $ 0 \to 2 \to 5 \to 8 \to 10 $ , $ 0 \to 1 \to 4 \to 7 \to 10 $ .

## 样例 #1

### 输入

```
10 5
0 0 1 0 2 0 0 1 0

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 3
1 1 1 1 2 1 1 1 1

```

### 输出

```
3

```

