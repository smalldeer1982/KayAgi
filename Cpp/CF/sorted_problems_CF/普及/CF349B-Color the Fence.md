---
title: "Color the Fence"
layout: "post"
diff: 普及/提高-
pid: CF349B
tag: []
---

# Color the Fence

## 题目描述

Igor has fallen in love with Tanya. Now Igor wants to show his feelings and write a number on the fence opposite to Tanya's house. Igor thinks that the larger the number is, the more chance to win Tanya's heart he has.

Unfortunately, Igor could only get $ v $ liters of paint. He did the math and concluded that digit $ d $ requires $ a_{d} $ liters of paint. Besides, Igor heard that Tanya doesn't like zeroes. That's why Igor won't use them in his number.

Help Igor find the maximum number he can write on the fence.

## 输入格式

The first line contains a positive integer $ v $ $ (0<=v<=10^{6}) $ . The second line contains nine positive integers $ a_{1},a_{2},...,a_{9} $ $ (1<=a_{i}<=10^{5}) $ .

## 输出格式

Print the maximum number Igor can write on the fence. If he has too little paint for any digit (so, he cannot write anything), print -1.

## 样例 #1

### 输入

```
5
5 4 3 2 1 2 3 4 5

```

### 输出

```
55555

```

## 样例 #2

### 输入

```
2
9 11 1 12 5 8 9 10 6

```

### 输出

```
33

```

## 样例 #3

### 输入

```
0
1 1 1 1 1 1 1 1 1

```

### 输出

```
-1

```

