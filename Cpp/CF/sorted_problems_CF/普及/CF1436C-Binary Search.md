---
title: "Binary Search"
layout: "post"
diff: 普及/提高-
pid: CF1436C
tag: []
---

# Binary Search

## 题目描述

Andrey thinks he is truly a successful developer, but in reality he didn't know about the binary search algorithm until recently. After reading some literature Andrey understood that this algorithm allows to quickly find a certain number $ x $ in an array. For an array $ a $ indexed from zero, and an integer $ x $ the pseudocode of the algorithm is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1436C/98f912f0399d121a6bf6605fa8d3ccffae3c8c30.png)Note that the elements of the array are indexed from zero, and the division is done in integers (rounding down).

Andrey read that the algorithm only works if the array is sorted. However, he found this statement untrue, because there certainly exist unsorted arrays for which the algorithm find $ x $ !

Andrey wants to write a letter to the book authors, but before doing that he must consider the permutations of size $ n $ such that the algorithm finds $ x $ in them. A permutation of size $ n $ is an array consisting of $ n $ distinct integers between $ 1 $ and $ n $ in arbitrary order.

Help Andrey and find the number of permutations of size $ n $ which contain $ x $ at position $ pos $ and for which the given implementation of the binary search algorithm finds $ x $ (returns true). As the result may be extremely large, print the remainder of its division by $ 10^9+7 $ .

## 输入格式

The only line of input contains integers $ n $ , $ x $ and $ pos $ ( $ 1 \le x \le n \le 1000 $ , $ 0 \le pos \le n - 1 $ ) — the required length of the permutation, the number to search, and the required position of that number, respectively.

## 输出格式

Print a single number — the remainder of the division of the number of valid permutations by $ 10^9+7 $ .

## 说明/提示

All possible permutations in the first test case: $ (2, 3, 1, 4) $ , $ (2, 4, 1, 3) $ , $ (3, 2, 1, 4) $ , $ (3, 4, 1, 2) $ , $ (4, 2, 1, 3) $ , $ (4, 3, 1, 2) $ .

## 样例 #1

### 输入

```
4 1 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
123 42 24
```

### 输出

```
824071958
```

