---
title: "Nikita and LCM"
layout: "post"
diff: 普及+/提高
pid: CF1977C
tag: ['动态规划 DP', '数论']
---

# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output a single integer — the length of the longest special subsequence of $ a $ .

## 说明/提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\,003] $ , its LCM is equal to $ 600\,018 $ , which is not contained in $ a $ .

## 样例 #1

### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1
```

### 输出

```
0
4
4
5
8
0
```

