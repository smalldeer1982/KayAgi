---
title: "D-Function"
layout: "post"
diff: 普及/提高-
pid: CF1985G
tag: ['数学']
---

# D-Function

## 题目描述

Let $ D(n) $ represent the sum of digits of $ n $ . For how many integers $ n $ where $ 10^{l} \leq n < 10^{r} $ satisfy $ D(k \cdot n) = k \cdot D(n) $ ? Output the answer modulo $ 10^9+7 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

Each test case contains three integers $ l $ , $ r $ , and $ k $ ( $ 0 \leq l < r \leq 10^9 $ , $ 1 \leq k \leq 10^9 $ ).

## 输出格式

For each test case, output an integer, the answer, modulo $ 10^9 + 7 $ .

## 说明/提示

For the first test case, the only values of $ n $ that satisfy the condition are $ 1 $ and $ 2 $ .

For the second test case, the only values of $ n $ that satisfy the condition are $ 1 $ , $ 10 $ , and $ 11 $ .

For the third test case, all values of $ n $ between $ 10 $ inclusive and $ 100 $ exclusive satisfy the condition.

## 样例 #1

### 输入

```
6
0 1 4
0 2 7
1 2 1
1 2 3
582 74663 3
0 3 1
```

### 输出

```
2
3
90
12
974995667
999
```

