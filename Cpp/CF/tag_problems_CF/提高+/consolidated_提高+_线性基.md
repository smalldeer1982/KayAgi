---
title: "Square Subsets"
layout: "post"
diff: 提高+/省选-
pid: CF895C
tag: ['数学', '状态合并', '线性基', '位运算']
---

# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 输入格式

First line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of elements in the array.

Second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=70 $ ) — the elements of the array.

## 输出格式

Print one integer — the number of different ways to choose some elements so that their product is a square of a certain integer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1

```

### 输出

```
15

```

## 样例 #2

### 输入

```
4
2 2 2 2

```

### 输出

```
7

```

## 样例 #3

### 输入

```
5
1 2 4 5 8

```

### 输出

```
7

```



---

---
title: "Mahmoud and Ehab and yet another xor task"
layout: "post"
diff: 提高+/省选-
pid: CF959F
tag: ['排序', '线性基']
---

# Mahmoud and Ehab and yet another xor task

## 题目描述

Ehab has an array $ a $ of $ n $ integers. He likes the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and he likes to bother Mahmoud so he came up with a problem. He gave Mahmoud $ q $ queries. In each of them, he gave Mahmoud 2 integers $ l $ and $ x $ , and asked him to find the number of subsequences of the first $ l $ elements of the array such that their bitwise-xor sum is $ x $ . Can you help Mahmoud answer the queries?

A subsequence can contain elements that are not neighboring.

## 输入格式

The first line contains integers $ n $ and $ q $ $ (1<=n,q<=10^{5}) $ , the number of elements in the array and the number of queries.

The next line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (0<=a_{i}<2^{20}) $ , the elements of the array.

The next $ q $ lines, each contains integers $ l $ and $ x $ $ (1<=l<=n $ , $ 0<=x<2^{20}) $ , representing the queries.

## 输出格式

For each query, output its answer modulo $ 10^{9}+7 $ in a newline.

## 说明/提示

The bitwise-xor sum of the empty set is 0 and the bitwise-xor sum of a set containing one element is that element itself.

## 样例 #1

### 输入

```
5 5
0 1 2 3 4
4 3
2 0
3 7
5 7
5 8

```

### 输出

```
4
2
0
4
0

```

## 样例 #2

### 输入

```
3 2
1 1 1
3 1
2 0

```

### 输出

```
4
2

```



---

