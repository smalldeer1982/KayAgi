---
title: "Strange Matrix"
layout: "post"
diff: 难度0
pid: CF2011H
tag: []
---

# Strange Matrix

## 题目描述

现有一个 $ n \times m $ 的矩阵 $ a $， 由 $ [0,31] $ 之间的整数构成。

若矩阵中的第 $ i $ 行和第 $ j $ 行 $(i \neq j)$ 同时满足以下条件，我们称其为“奇异矩阵”：

- 对于每行中的 $ k $ 项 $ (x_1, x_2, \dots, x_k) $，其中 $ 1 \le x_1 < x_2 < \cdots < x_k \le m $，等式 $ a_{i, x_1} \mathbin{\&} a_{j, x_1} \mathbin{\&} a_{i, x_2} \mathbin{\&} a_{j, x_2} \mathbin{\&} \cdots \mathbin{\&} a_{i, x_k} \mathbin{\&} a_{j, x_k} = 0 $ 成立（其中 $ \mathbin{\&} $ 表示按位与）；
- 对于每行中的 $ k $ 项 $ (x_1, x_2, \dots, x_k) $，其中 $ 1 \le x_1 < x_2 < \cdots < x_k \le m $，等式 $ a_{i, x_1} \mathbin{|} a_{j, x_1} \mathbin{|} a_{i, x_2} \mathbin{|} a_{j, x_2} \mathbin{|} \cdots \mathbin{|} a_{i, x_k} \mathbin{|} a_{j, x_k} = 31 $ 成立（其中 $ \mathbin{|} $ 表示按位或）。

你可以进行任意次的如下操作：取矩阵的任意一行和一个 $ [0,31] $ 之间的整数 $ y $；随后将这一行的每一项与 $ y $ 进行按位异或运算。将这一操作的代价记为 $ y $。

你的任务是计算出能否将矩阵 $ a $ 变为“奇异矩阵”，以及将其变为“奇异矩阵”的最小代价。

## 输入格式

每个测试点包含多组测试数据。第一行一个整数 $ t $（$ 1 \le t \le 100 $）表示数据组数。

每组测试数据的第一行包含三个整数 $ n $，$ m $，$ k $（$ 1 \le n, m \le 50 $；$ 1 \le k \le m $）。

接下来有 $ n $ 行，其中第 $ i $ 行包含 $ m $ 个整数 $ a_{i, 1}, a_{i, 2}, \dots, a_{i, m} $（$ 0 \le a_{i, j} \le 31 $）。

## 输出格式

对于每组测试数据，输出一个整数表示将这个矩阵变为“奇异矩阵”的最小代价；若无解，输出-1。

Translated By HShiDianLu.

## 样例 #1

### 输入

```
3
2 3 1
0 1 0
1 0 1
3 2 2
0 1
2 3
4 5
5 5 5
0 5 17 4 22
8 5 16 21 9
7 25 31 30 8
0 0 5 15 13
1 2 3 4 5
```

### 输出

```
30
-1
24
```

