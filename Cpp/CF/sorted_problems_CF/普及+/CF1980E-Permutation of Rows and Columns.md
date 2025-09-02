---
title: "Permutation of Rows and Columns"
layout: "post"
diff: 普及+/提高
pid: CF1980E
tag: ['哈希 hashing']
---

# Permutation of Rows and Columns

## 题目描述

You have been given a matrix $ a $ of size $ n $ by $ m $ , containing a permutation of integers from $ 1 $ to $ n \cdot m $ .

A permutation of $ n $ integers is an array containing all numbers from $ 1 $ to $ n $ exactly once. For example, the arrays $ [1] $ , $ [2, 1, 3] $ , $ [5, 4, 3, 2, 1] $ are permutations, while the arrays $ [1, 1] $ , $ [100] $ , $ [1, 2, 4, 5] $ are not.

A matrix contains a permutation if, when all its elements are written out, the resulting array is a permutation. Matrices $ [[1, 2], [3, 4]] $ , $ [[1]] $ , $ [[1, 5, 3], [2, 6, 4]] $ contain permutations, while matrices $ [[2]] $ , $ [[1, 1], [2, 2]] $ , $ [[1, 2], [100, 200]] $ do not.

You can perform one of the following two actions in one operation:

- choose columns $ c $ and $ d $ ( $ 1 \le c, d \le m $ , $ c \ne d $ ) and swap these columns;
- choose rows $ c $ and $ d $ ( $ 1 \le c, d \le n $ , $ c \ne d $ ) and swap these rows.

You can perform any number of operations.

You are given the original matrix $ a $ and the matrix $ b $ . Your task is to determine whether it is possible to transform matrix $ a $ into matrix $ b $ using the given operations.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The descriptions of the test cases follow.

The first line of each test case description contains $ 2 $ integers $ n $ and $ m $ ( $ 1 \le n, m \le n \cdot m \le 2 \cdot 10^5 $ ) — the sizes of the matrix.

The next $ n $ lines contain $ m $ integers $ a_{ij} $ each ( $ 1 \le a_{ij} \le n \cdot m $ ). It is guaranteed that matrix $ a $ is a permutation.

The next $ n $ lines contain $ m $ integers $ b_{ij} $ each ( $ 1 \le b_{ij} \le n \cdot m $ ). It is guaranteed that matrix $ b $ is a permutation.

It is guaranteed that the sum of the values $ n \cdot m $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if the second matrix can be obtained from the first, and "NO" otherwise.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the second example, the original matrix looks like this:

 $  \begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}  $

By swapping rows $ 1 $ and $ 2 $ , it becomes:

 $  \begin{pmatrix} 3 & 4 \\ 1 & 2 \end{pmatrix}  $

By swapping columns $ 1 $ and $ 2 $ , it becomes equal to matrix $ b $ :

 $  \begin{pmatrix} 4 & 3 \\ 2 & 1 \end{pmatrix}  $

## 样例 #1

### 输入

```
7
1 1
1
1
2 2
1 2
3 4
4 3
2 1
2 2
1 2
3 4
4 3
1 2
3 4
1 5 9 6
12 10 4 8
7 11 3 2
1 5 9 6
12 10 4 8
7 11 3 2
3 3
1 5 9
6 4 2
3 8 7
9 5 1
2 4 6
7 8 3
2 3
1 2 6
5 4 3
6 1 2
3 4 5
1 5
5 1 2 3 4
4 2 5 1 3
```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
```

