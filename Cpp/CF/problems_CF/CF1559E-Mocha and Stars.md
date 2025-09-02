---
title: "Mocha and Stars"
layout: "post"
diff: 省选/NOI-
pid: CF1559E
tag: []
---

# Mocha and Stars

## 题目描述

Mocha wants to be an astrologer. There are $ n $ stars which can be seen in Zhijiang, and the brightness of the $ i $ -th star is $ a_i $ .

Mocha considers that these $ n $ stars form a constellation, and she uses $ (a_1,a_2,\ldots,a_n) $ to show its state. A state is called mathematical if all of the following three conditions are satisfied:

- For all $ i $ ( $ 1\le i\le n $ ), $ a_i $ is an integer in the range $ [l_i, r_i] $ .
- $ \sum \limits _{i=1} ^ n a_i \le m $ .
- $ \gcd(a_1,a_2,\ldots,a_n)=1 $ .

Here, $ \gcd(a_1,a_2,\ldots,a_n) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a_1,a_2,\ldots,a_n $ .

Mocha is wondering how many different mathematical states of this constellation exist. Because the answer may be large, you must find it modulo $ 998\,244\,353 $ .

Two states $ (a_1,a_2,\ldots,a_n) $ and $ (b_1,b_2,\ldots,b_n) $ are considered different if there exists $ i $ ( $ 1\le i\le n $ ) such that $ a_i \ne b_i $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n \le 50 $ , $ 1 \le m \le 10^5 $ ) — the number of stars and the upper bound of the sum of the brightness of stars.

Each of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le m $ ) — the range of the brightness of the $ i $ -th star.

## 输出格式

Print a single integer — the number of different mathematical states of this constellation, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, there are $ 4 $ different mathematical states of this constellation:

- $ a_1=1 $ , $ a_2=1 $ .
- $ a_1=1 $ , $ a_2=2 $ .
- $ a_1=2 $ , $ a_2=1 $ .
- $ a_1=3 $ , $ a_2=1 $ .

## 样例 #1

### 输入

```
2 4
1 3
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 10
1 10
1 10
1 10
1 10
1 10
```

### 输出

```
251
```

## 样例 #3

### 输入

```
5 100
1 94
1 96
1 91
4 96
6 97
```

### 输出

```
47464146
```

