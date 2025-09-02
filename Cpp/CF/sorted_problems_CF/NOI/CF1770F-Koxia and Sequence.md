---
title: "Koxia and Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1770F
tag: []
---

# Koxia and Sequence

## 题目描述

Mari has three integers $ n $ , $ x $ , and $ y $ .

Call an array $ a $ of $ n $ non-negative integers good if it satisfies the following conditions:

- $ a_1+a_2+\ldots+a_n=x $ , and
- $ a_1 \, | \, a_2 \, | \, \ldots \, | \, a_n=y $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

The score of a good array is the value of $ a_1 \oplus a_2 \oplus \ldots \oplus a_n $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Koxia wants you to find the total bitwise XOR of the scores of all good arrays. If there are no good arrays, output $ 0 $ instead.

## 输入格式

The first line of input contains three integers $ n $ , $ x $ and $ y $ ( $ 1 \leq n < 2^{40} $ , $ 0 \leq x < 2^{60} $ , $ 0 \leq y < 2^{20} $ ).

## 输出格式

Output a single integer — the total bitwise XOR of the scores of all good arrays.

## 说明/提示

In the first test case, there are $ 12 $ good arrays totally as follows.

- $ [0,2,3] $ , $ [0,3,2] $ , $ [2,0,3] $ , $ [2,3,0] $ , $ [3,0,2] $ and $ [3,2,0] $ — the score is $ 0 \oplus 2 \oplus 3 = 1 $ ;
- $ [1, 2, 2] $ , $ [2, 1, 2] $ and $ [2, 2, 1] $ — the score is $ 1 \oplus 2 \oplus 2 = 1 $ ;
- $ [1, 1, 3] $ , $ [1, 3, 1] $ and $ [3, 1, 1] $ — the score is $ 1 \oplus 1 \oplus 3 = 3 $ .

Therefore, the total bitwise xor of the scores is $ \underbrace{1 \oplus \ldots \oplus 1}_{9\text{ times}} \oplus 3 \oplus 3 \oplus 3 = 2 $ .

In the second test case, there are no good sequences. The output should be $ 0 $ .

## 样例 #1

### 输入

```
3 5 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 0 100
```

### 输出

```
0
```

## 样例 #3

### 输入

```
79877974817 749875791743978 982783
```

### 输出

```
64
```

