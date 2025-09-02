---
title: "Strange Triples"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1796F
tag: []
---

# Strange Triples

## 题目描述

Let's call a triple of positive integers ( $ a, b, n $ ) strange if the equality $ \frac{an}{nb} = \frac{a}{b} $ holds, where $ an $ is the concatenation of $ a $ and $ n $ and $ nb $ is the concatenation of $ n $ and $ b $ . For the purpose of concatenation, the integers are considered without leading zeroes.

For example, if $ a = 1 $ , $ b = 5 $ and $ n = 9 $ , then the triple is strange, because $ \frac{19}{95} = \frac{1}{5} $ . But $ a = 7 $ , $ b = 3 $ and $ n = 11 $ is not strange, because $ \frac{711}{113} \ne \frac{7}{3} $ .

You are given three integers $ A $ , $ B $ and $ N $ . Calculate the number of strange triples $ (a, b, n $ ), such that $ 1 \le a < A $ , $ 1 \le b < B $ and $ 1 \le n < N $ .

## 输入格式

The only line contains three integers $ A $ , $ B $ and $ N $ ( $ 1 \le A, B \le 10^5 $ ; $ 1 \le N \le 10^9 $ ).

## 输出格式

Print one integer — the number of strange triples $ (a, b, n $ ) such that $ 1 \le a < A $ , $ 1 \le b < B $ and $ 1 \le n < N $ .

## 说明/提示

In the first example, there are $ 7 $ strange triples: $ (1, 1, 1 $ ), ( $ 1, 4, 6 $ ), ( $ 1, 5, 9 $ ), ( $ 2, 2, 2 $ ), ( $ 2, 5, 6 $ ), ( $ 3, 3, 3 $ ) and ( $ 4, 4, 4 $ ).

## 样例 #1

### 输入

```
5 6 10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
10 10 100
```

### 输出

```
29
```

## 样例 #3

### 输入

```
1 10 25
```

### 输出

```
0
```

## 样例 #4

### 输入

```
4242 6969 133333337
```

### 输出

```
19536
```

## 样例 #5

### 输入

```
94841 47471 581818184
```

### 输出

```
98715
```

