---
title: "Triple Flips"
layout: "post"
diff: 省选/NOI-
pid: CF1031E
tag: ['枚举']
---

# Triple Flips

## 题目描述

You are given an array $ a $ of length $ n $ that consists of zeros and ones.

You can perform the following operation multiple times. The operation consists of two steps:

1. Choose three integers $ 1 \le x < y < z \le n $ , that form an arithmetic progression ( $ y - x = z - y $ ).
2. Flip the values $ a_x, a_y, a_z $ (i.e. change $ 1 $ to $ 0 $ , change $ 0 $ to $ 1 $ ).

Determine if it is possible to make all elements of the array equal to zero. If yes, print the operations that lead the the all-zero state. Your solution should not contain more than $ (\lfloor \frac{n}{3} \rfloor + 12) $ operations. Here $ \lfloor q \rfloor $ denotes the number $ q $ rounded down. We can show that it is possible to make all elements equal to zero in no more than this number of operations whenever it is possible to do so at all.

## 输入格式

The first line contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 1 $ ) — the elements of the array.

## 输出格式

Print "YES" (without quotes) if the answer exists, otherwise print "NO" (without quotes). You can print each letter in any case (upper or lower).

If there is an answer, in the second line print an integer $ m $ ( $ 0 \le m \le (\lfloor \frac{n}{3} \rfloor + 12) $ ) — the number of operations in your answer.

After that in ( $ i + 2 $ )-th line print the $ i $ -th operations — the integers $ x_i, y_i, z_i $ . You can print them in arbitrary order.

## 说明/提示

In the first sample the shown output corresponds to the following solution:

- 1 1 0 1 1 (initial state);
- 0 1 1 1 0 (the flipped positions are the first, the third and the fifth elements);
- 0 0 0 0 0 (the flipped positions are the second, the third and the fourth elements).

Other answers are also possible. In this test the number of operations should not exceed $ \lfloor \frac{5}{3} \rfloor + 12 = 1 + 12 = 13 $ .

In the second sample the only available operation is to flip all the elements. This way it is only possible to obtain the arrays 0 1 0 and 1 0 1, but it is impossible to make all elements equal to zero.

## 样例 #1

### 输入

```
5
1 1 0 1 1

```

### 输出

```
YES
2
1 3 5
2 3 4

```

## 样例 #2

### 输入

```
3
0 1 0

```

### 输出

```
NO

```

