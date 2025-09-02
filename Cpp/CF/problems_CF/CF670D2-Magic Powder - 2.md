---
title: "Magic Powder - 2"
layout: "post"
diff: 普及/提高-
pid: CF670D2
tag: []
---

# Magic Powder - 2

## 题目描述

The term of this problem is the same as the previous one, the only exception — increased restrictions.

## 输入格式

The first line contains two positive integers $ n $ and $ k $ ( $ 1<=n<=100000,1<=k<=10^{9} $ ) — the number of ingredients and the number of grams of the magic powder.

The second line contains the sequence $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ), where the $ i $ -th number is equal to the number of grams of the $ i $ -th ingredient, needed to bake one cookie.

The third line contains the sequence $ b_{1},b_{2},...,b_{n} $ ( $ 1<=b_{i}<=10^{9} $ ), where the $ i $ -th number is equal to the number of grams of the $ i $ -th ingredient, which Apollinaria has.

## 输出格式

Print the maximum number of cookies, which Apollinaria will be able to bake using the ingredients that she has and the magic powder.

## 样例 #1

### 输入

```
1 1000000000
1
1000000000

```

### 输出

```
2000000000

```

## 样例 #2

### 输入

```
10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1 1 1 1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 1
2 1 4
11 3 16

```

### 输出

```
4

```

## 样例 #4

### 输入

```
4 3
4 3 5 6
11 12 14 20

```

### 输出

```
3

```

