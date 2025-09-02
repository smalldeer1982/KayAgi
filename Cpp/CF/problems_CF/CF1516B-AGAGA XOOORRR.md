---
title: "AGAGA XOOORRR"
layout: "post"
diff: 普及/提高-
pid: CF1516B
tag: []
---

# AGAGA XOOORRR

## 题目描述

Baby Ehab is known for his love for a certain operation. He has an array $ a $ of length $ n $ , and he decided to keep doing the following operation on it:

- he picks $ 2 $ adjacent elements; he then removes them and places a single integer in their place: their [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one.

Now he asks you if he can make all elements of the array equal. Since babies like to make your life harder, he requires that you leave at least $ 2 $ elements remaining.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 15 $ ) — the number of test cases you need to solve.

The first line of each test case contains an integers $ n $ ( $ 2 \le n \le 2000 $ ) — the number of elements in the array $ a $ .

The second line contains $ n $ space-separated integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_{n} $ ( $ 0 \le a_i < 2^{30} $ ) — the elements of the array $ a $ .

## 输出格式

If Baby Ehab can make all elements equal while leaving at least $ 2 $ elements standing, print "YES". Otherwise, print "NO".

## 说明/提示

In the first sample, he can remove the first $ 2 $ elements, $ 0 $ and $ 2 $ , and replace them by $ 0 \oplus 2=2 $ . The array will be $ [2,2] $ , so all the elements are equal.

In the second sample, there's no way to make all the elements equal.

## 样例 #1

### 输入

```
2
3
0 2 2
4
2 3 1 10
```

### 输出

```
YES
NO
```

