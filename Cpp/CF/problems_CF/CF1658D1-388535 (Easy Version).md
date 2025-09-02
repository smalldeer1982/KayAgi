---
title: "388535 (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1658D1
tag: []
---

# 388535 (Easy Version)

## 题目描述

This is the easy version of the problem. The difference in the constraints between both versions is colored below in red. You can make hacks only if all versions of the problem are solved.

Marin and Gojou are playing hide-and-seek with an array.

Gojou initially performs the following steps:

- First, Gojou chooses $ 2 $ integers $ l $ and $ r $ such that $ l \leq r $ .
- Then, Gojou makes an array $ a $ of length $ r-l+1 $ which is a permutation of the array $ [l,l+1,\ldots,r] $ .
- Finally, Gojou chooses a secret integer $ x $ and sets $ a_i $ to $ a_i \oplus x $ for all $ i $ (where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Marin is then given the values of $ l,r $ and the final array $ a $ . She needs to find the secret integer $ x $ to win. Can you help her?

Note that there may be multiple possible $ x $ that Gojou could have chosen. Marin can find any possible $ x $ that could have resulted in the final value of $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

In the first line of each test case contains two integers $ l $ and $ r $ ( $  \color{red}{\boldsymbol{0} \boldsymbol{=} \boldsymbol{l}} \le r < 2^{17} $ ).

The second line contains $ r - l + 1 $ integers of $ a_1,a_2,\ldots,a_{r-l+1} $ ( $ 0 \le a_i < 2^{17} $ ). It is guaranteed that $ a $ can be generated using the steps performed by Gojou.

It is guaranteed that the sum of $ r - l + 1 $ over all test cases does not exceed $ 2^{17} $ .

## 输出格式

For each test case print an integer $ x $ . If there are multiple answers, print any.

## 说明/提示

In the first test case, the original array is $ [3, 2, 1, 0] $ .

In the second test case, the original array is $ [0, 3, 2, 1] $ .

In the third test case, the original array is $ [2, 1, 0] $ .

## 样例 #1

### 输入

```
3
0 3
3 2 1 0
0 3
4 7 6 5
0 2
1 2 3
```

### 输出

```
0
4
3
```

