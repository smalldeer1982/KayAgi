---
title: "Lucky Mask"
layout: "post"
diff: 普及/提高-
pid: CF146B
tag: []
---

# Lucky Mask

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya calls a mask of a positive integer $ n $ the number that is obtained after successive writing of all lucky digits of number $ n $ from the left to the right. For example, the mask of number $ 72174994 $ is number $ 7744 $ , the mask of $ 7 $ is $ 7 $ , the mask of $ 9999047 $ is $ 47 $ . Obviously, mask of any number is always a lucky number.

Petya has two numbers — an arbitrary integer $ a $ and a lucky number $ b $ . Help him find the minimum number $ c $ $ (c&gt;a) $ such that the mask of number $ c $ equals $ b $ .

## 输入格式

The only line contains two integers $ a $ and $ b $ $ (1<=a,b<=10^{5}) $ . It is guaranteed that number $ b $ is lucky.

## 输出格式

In the only line print a single number — the number $ c $ that is sought by Petya.

## 样例 #1

### 输入

```
1 7

```

### 输出

```
7

```

## 样例 #2

### 输入

```
100 47

```

### 输出

```
147

```

