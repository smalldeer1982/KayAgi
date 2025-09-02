---
title: "Restore the Permutation"
layout: "post"
diff: 普及+/提高
pid: CF1759G
tag: []
---

# Restore the Permutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all numbers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

For a permutation $ p $ of even length $ n $ you can make an array $ b $ of length $ \frac{n}{2} $ such that:

- $ b_i = \max(p_{2i - 1}, p_{2i}) $ for $ 1 \le i \le \frac{n}{2} $

For example, if $ p $ = \[ $ 2, 4, 3, 1, 5, 6 $ \], then:

- $ b_1 = \max(p_1, p_2) = \max(2, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(3,1)=3 $
- $ b_3 = \max(p_5, p_6) = \max(5,6) = 6 $

 As a result, we made $ b $ = $ [4, 3, 6] $ .For a given array $ b $ , find the lexicographically minimal permutation $ p $ such that you can make the given array $ b $ from it.

If $ b $ = \[ $ 4,3,6 $ \], then the lexicographically minimal permutation from which it can be made is $ p $ = \[ $ 1,4,2,3,5,6 $ \], since:

- $ b_1 = \max(p_1, p_2) = \max(1, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(2, 3) = 3 $
- $ b_3 = \max(p_5, p_6) = \max(5, 6) = 6 $

A permutation $ x_1, x_2, \dots, x_n $ is lexicographically smaller than a permutation $ y_1, y_2 \dots, y_n $ if and only if there exists such $ i $ ( $ 1 \le i \le n $ ) that $ x_1=y_1, x_2=y_2, \dots, x_{i-1}=y_{i-1} $ and $ x_i<y_i $ .

## 输入格式

The first line of input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The description of the test cases follows.

The first line of each test case contains one even integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains exactly $ \frac{n}{2} $ integers $ b_i $ ( $ 1 \le b_i \le n $ ) — elements of array $ b $ .

It is guaranteed that the sum of $ n $ values over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print on a separate line:

- lexicographically minimal permutation $ p $ such that you can make an array $ b $ from it;
- or a number -1 if the permutation you are looking for does not exist.

## 说明/提示

The first test case is parsed in the problem statement.

## 样例 #1

### 输入

```
6
6
4 3 6
4
2 4
8
8 7 2 3
6
6 4 2
4
4 4
8
8 7 4 5
```

### 输出

```
1 4 2 3 5 6 
1 2 3 4 
-1
5 6 3 4 1 2 
-1
1 8 6 7 2 4 3 5
```

