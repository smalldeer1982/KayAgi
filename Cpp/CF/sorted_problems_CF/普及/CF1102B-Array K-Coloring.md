---
title: "Array K-Coloring"
layout: "post"
diff: 普及/提高-
pid: CF1102B
tag: []
---

# Array K-Coloring

## 题目描述

You are given an array $ a $ consisting of $ n $ integer numbers.

You have to color this array in $ k $ colors in such a way that:

- Each element of the array should be colored in some color;
- For each $ i $ from $ 1 $ to $ k $ there should be at least one element colored in the $ i $ -th color in the array;
- For each $ i $ from $ 1 $ to $ k $ all elements colored in the $ i $ -th color should be distinct.

Obviously, such coloring might be impossible. In this case, print "NO". Otherwise print "YES" and any coloring (i.e. numbers $ c_1, c_2, \dots c_n $ , where $ 1 \le c_i \le k $ and $ c_i $ is the color of the $ i $ -th element of the given array) satisfying the conditions above. If there are multiple answers, you can print any.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 5000 $ ) — the length of the array $ a $ and the number of colors, respectively.

The second line of the input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 5000 $ ) — elements of the array $ a $ .

## 输出格式

If there is no answer, print "NO". Otherwise print "YES" and any coloring (i.e. numbers $ c_1, c_2, \dots c_n $ , where $ 1 \le c_i \le k $ and $ c_i $ is the color of the $ i $ -th element of the given array) satisfying the conditions described in the problem statement. If there are multiple answers, you can print any.

## 说明/提示

In the first example the answer $ 2~ 1~ 2~ 1 $ is also acceptable.

In the second example the answer $ 1~ 1~ 1~ 2~ 2 $ is also acceptable.

There exist other acceptable answers for both examples.

## 样例 #1

### 输入

```
4 2
1 2 2 3

```

### 输出

```
YES
1 1 2 2

```

## 样例 #2

### 输入

```
5 2
3 2 1 2 3

```

### 输出

```
YES
2 1 1 2 1

```

## 样例 #3

### 输入

```
5 2
2 1 1 2 1

```

### 输出

```
NO

```

