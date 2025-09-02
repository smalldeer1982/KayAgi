---
title: "Good Number"
layout: "post"
diff: 普及-
pid: CF365A
tag: []
---

# Good Number

## 题目描述

Let's call a number $ k $ -good if it contains all digits not exceeding $ k $ ( $ 0,...,k $ ). You've got a number $ k $ and an array $ a $ containing $ n $ numbers. Find out how many $ k $ -good numbers are in $ a $ (count each number every time it occurs in array $ a $ ).

## 输入格式

The first line contains integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 0<=k<=9 $ ). The $ i $ -th of the following $ n $ lines contains integer $ a_{i} $ without leading zeroes ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print a single integer — the number of $ k $ -good numbers in $ a $ .

## 样例 #1

### 输入

```
10 6
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560

```

### 输出

```
10

```

## 样例 #2

### 输入

```
2 1
1
10

```

### 输出

```
1

```

