---
title: "Vasya And The Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1016D
tag: ['进制', '构造']
---

# Vasya And The Matrix

## 题目描述

Now Vasya is taking an exam in mathematics. In order to get a good mark, Vasya needs to guess the matrix that the teacher has constructed!

Vasya knows that the matrix consists of $ n $ rows and $ m $ columns. For each row, he knows the xor (bitwise excluding or) of the elements in this row. The sequence $ a_{1},a_{2},...,a_{n} $ denotes the xor of elements in rows with indices $ 1 $ , $ 2 $ , ..., $ n $ , respectively. Similarly, for each column, he knows the xor of the elements in this column. The sequence $ b_{1},b_{2},...,b_{m} $ denotes the xor of elements in columns with indices $ 1 $ , $ 2 $ , ..., $ m $ , respectively.

Help Vasya! Find a matrix satisfying the given constraints or tell him that there is no suitable matrix.

## 输入格式

The first line contains two numbers $ n $ and $ m (2<=n,m<=100) $ — the dimensions of the matrix.

The second line contains $ n $ numbers $ a_{1},a_{2},...,a_{n} (0<=a_{i}<=10^{9}) $ , where $ a_{i} $ is the xor of all elements in row $ i $ .

The third line contains $ m $ numbers $ b_{1},b_{2},...,b_{m} (0<=b_{i}<=10^{9}) $ , where $ b_{i} $ is the xor of all elements in column $ i $ .

## 输出格式

If there is no matrix satisfying the given constraints in the first line, output "NO".

Otherwise, on the first line output "YES", and then $ n $ rows of $ m $ numbers in each $ c_{i1},c_{i2},...\ ,c_{im} (0<=c_{ij}<=2·10^{9}) $ — the description of the matrix.

If there are several suitable matrices, it is allowed to print any of them.

## 样例 #1

### 输入

```
2 3
2 9
5 3 13

```

### 输出

```
YES
3 4 5
6 7 8

```

## 样例 #2

### 输入

```
3 3
1 7 6
2 15 12

```

### 输出

```
NO

```

