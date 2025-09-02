---
title: "Array Painting"
layout: "post"
diff: 普及+/提高
pid: CF1849D
tag: []
---

# Array Painting

## 题目描述

You are given an array of $ n $ integers, where each integer is either $ 0 $ , $ 1 $ , or $ 2 $ . Initially, each element of the array is blue.

Your goal is to paint each element of the array red. In order to do so, you can perform operations of two types:

- pay one coin to choose a blue element and paint it red;
- choose a red element which is not equal to $ 0 $ and a blue element adjacent to it, decrease the chosen red element by $ 1 $ , and paint the chosen blue element red.

What is the minimum number of coins you have to spend to achieve your goal?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2 $ ).

## 输出格式

Print one integer — the minimum number of coins you have to spend in order to paint all elements red.

## 说明/提示

In the first example, you can paint all elements red with having to spend only one coin as follows:

1. paint the $ 2 $ -nd element red by spending one coin;
2. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 1 $ -st element red;
3. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 3 $ -rd element red.

In the second example, you can paint all elements red spending only two coins as follows:

1. paint the $ 4 $ -th element red by spending one coin;
2. decrease the $ 4 $ -th element by $ 1 $ and paint the $ 3 $ -rd element red;
3. paint the $ 1 $ -st element red by spending one coin;
4. decrease the $ 3 $ -rd element by $ 1 $ and paint the $ 2 $ -nd element red.

## 样例 #1

### 输入

```
3
0 2 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
0 0 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
0 1 0 0 1 0 2
```

### 输出

```
4
```

