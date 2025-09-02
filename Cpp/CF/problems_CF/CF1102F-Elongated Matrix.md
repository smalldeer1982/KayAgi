---
title: "Elongated Matrix"
layout: "post"
diff: 普及+/提高
pid: CF1102F
tag: []
---

# Elongated Matrix

## 题目描述

You are given a matrix $ a $ , consisting of $ n $ rows and $ m $ columns. Each cell contains an integer in it.

You can change the order of rows arbitrarily (including leaving the initial order), but you can't change the order of cells in a row. After you pick some order of rows, you traverse the whole matrix the following way: firstly visit all cells of the first column from the top row to the bottom one, then the same for the second column and so on. During the traversal you write down the sequence of the numbers on the cells in the same order you visited them. Let that sequence be $ s_1, s_2, \dots, s_{nm} $ .

The traversal is $ k $ -acceptable if for all $ i $ ( $ 1 \le i \le nm - 1 $ ) $ |s_i - s_{i + 1}| \ge k $ .

Find the maximum integer $ k $ such that there exists some order of rows of matrix $ a $ that it produces a $ k $ -acceptable traversal.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 16 $ , $ 1 \le m \le 10^4 $ , $ 2 \le nm $ ) — the number of rows and the number of columns, respectively.

Each of the next $ n $ lines contains $ m $ integers ( $ 1 \le a_{i, j} \le 10^9 $ ) — the description of the matrix.

## 输出格式

Print a single integer $ k $ — the maximum number such that there exists some order of rows of matrix $ a $ that it produces an $ k $ -acceptable traversal.

## 说明/提示

In the first example you can rearrange rows as following to get the $ 5 $ -acceptable traversal:

```
<br></br>5 3<br></br>10 8<br></br>4 3<br></br>9 9<br></br>
```

Then the sequence $ s $ will be $ [5, 10, 4, 9, 3, 8, 3, 9] $ . Each pair of neighbouring elements have at least $ k = 5 $ difference between them.

In the second example the maximum $ k = 0 $ , any order is $ 0 $ -acceptable.

In the third example the given order is already $ 3 $ -acceptable, you can leave it as it is.

## 样例 #1

### 输入

```
4 2
9 9
10 8
5 3
4 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2 4
1 2 3 4
10 3 7 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 1
3
6
2
5
1
4

```

### 输出

```
3

```

