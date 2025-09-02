---
title: "Special Permutation"
layout: "post"
diff: 普及-
pid: CF1612B
tag: ['构造']
---

# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots, p_n] $ which contains every integer from $ 1 $ to $ n $ (inclusive) exactly once. For example, $ p=[4, 2, 6, 5, 3, 1] $ is a permutation of length $ 6 $ .

You are given three integers $ n $ , $ a $ and $ b $ , where $ n $ is an even number. Print any permutation of length $ n $ that the minimum among all its elements of the left half equals $ a $ and the maximum among all its elements of the right half equals $ b $ . Print -1 if no such permutation exists.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ), the number of test cases in the test. The following $ t $ lines contain test case descriptions.

Each test case description contains three integers $ n $ , $ a $ , $ b $ ( $ 2 \le n \le 100 $ ; $ 1 \le a,b \le n $ ; $ a \ne b $ ), where $ n $ is an even number (i.e. $ n \bmod 2 = 0 $ ).

## 输出格式

For each test case, print a single line containing any suitable permutation. Print -1 no such permutation exists. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
7
6 2 5
6 1 3
6 4 3
4 2 4
10 5 3
2 1 2
2 2 1
```

### 输出

```
4 2 6 5 3 1
-1
6 4 5 1 3 2 
3 2 4 1 
-1
1 2 
2 1
```

