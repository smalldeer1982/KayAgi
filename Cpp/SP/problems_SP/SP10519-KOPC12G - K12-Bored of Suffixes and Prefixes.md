---
title: "KOPC12G - K12-Bored of Suffixes and Prefixes"
layout: "post"
diff: 难度0
pid: SP10519
tag: []
---

# KOPC12G - K12-Bored of Suffixes and Prefixes

## 题目描述

现有一矩阵大小为 $N \times N$，矩阵中仅包含大写英文字母。您需要对这个矩阵进行两类操作：1) 更新操作；2) 查询操作。

## 输入格式

输入的第一行为一个整数 $T$，表示有多少组测试数据。

每组测试数据首先出现的两整数 $N$ 和 $q$，分别表示矩阵的尺寸和查询的次数。接下来是一个 $N \times N$ 的字母矩阵。矩阵之后紧接着有 $q$ 行的查询，每行描述一次操作。

- $T \leq 10$
- $N \leq 500, Q \leq 10000$
- $0 \leq x_1 < N, 0 \leq x_2 < N, 0 \leq y_1 < N, 0 \leq y_2 < N$
- $x_1 \leq x_2, y1 \leq y2$

注意：输入和输出的数据量可能非常大。

## 输出格式

对每个查询请求，逐行打印其结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
4 3
ABCD
ABCD
ABCD
ABCD
1 0 0 3 3 
0 0 2 PQRS
1 0 2 3 3
```

### 输出

```
40
58
```

