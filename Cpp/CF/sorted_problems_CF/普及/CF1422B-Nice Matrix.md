---
title: "Nice Matrix"
layout: "post"
diff: 普及/提高-
pid: CF1422B
tag: []
---

# Nice Matrix

## 题目描述

A matrix of size $ n \times m $ is called nice, if all rows and columns of the matrix are palindromes. A sequence of integers $ (a_1, a_2, \dots , a_k) $ is a palindrome, if for any integer $ i $ ( $ 1 \le i \le k $ ) the equality $ a_i = a_{k - i + 1} $ holds.

Sasha owns a matrix $ a $ of size $ n \times m $ . In one operation he can increase or decrease any number in the matrix by one. Sasha wants to make the matrix nice. He is interested what is the minimum number of operations he needs.

Help him!

## 输入格式

The first line contains a single integer $ t $ — the number of test cases ( $ 1 \le t \le 10 $ ). The $ t $ tests follow.

The first line of each test contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — the size of the matrix.

Each of the next $ n $ lines contains $ m $ integers $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^9 $ ) — the elements of the matrix.

## 输出格式

For each test output the smallest number of operations required to make the matrix nice.

## 说明/提示

In the first test case we can, for example, obtain the following nice matrix in $ 8 $ operations:

```
<pre class="verbatim"><br></br>2 2<br></br>4 4<br></br>4 4<br></br>2 2<br></br>
```

In the second test case we can, for example, obtain the following nice matrix in $ 42 $ operations:

```
<pre class="verbatim"><br></br>5 6 6 5<br></br>6 6 6 6<br></br>5 6 6 5<br></br>
```

## 样例 #1

### 输入

```
2
4 2
4 2
2 4
4 2
2 4
3 4
1 2 3 4
5 6 7 8
9 10 11 18
```

### 输出

```
8
42
```

