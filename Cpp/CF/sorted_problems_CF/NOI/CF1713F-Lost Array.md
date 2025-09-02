---
title: "Lost Array"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1713F
tag: ['快速沃尔什变换 FWT']
---

# Lost Array

## 题目描述

My orzlers, we can optimize this problem from $ O(S^3) $ to $ O\left(T^\frac{5}{9}\right) $ !

— Spyofgame, founder of Orzlim religion



A long time ago, Spyofgame invented the famous array $ a $ ( $ 1 $ -indexed) of length $ n $ that contains information about the world and life. After that, he decided to convert it into the matrix $ b $ ( $ 0 $ -indexed) of size $ (n + 1) \times (n + 1) $ which contains information about the world, life and beyond.

Spyofgame converted $ a $ into $ b $ with the following rules.

- $ b_{i,0} = 0 $ if $ 0 \leq i \leq n $ ;
- $ b_{0,i} = a_{i} $ if $ 1 \leq i \leq n $ ;
- $ b_{i,j} = b_{i,j-1} \oplus b_{i-1,j} $ if $ 1 \leq i, j \leq n $ .

Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Today, archaeologists have discovered the famous matrix $ b $ . However, many elements of the matrix has been lost. They only know the values of $ b_{i,n} $ for $ 1 \leq i \leq n $ (note that these are some elements of the last column, not the last row).

The archaeologists want to know what a possible array of $ a $ is. Can you help them reconstruct any array that could be $ a $ ?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ b_{1,n}, b_{2,n}, \ldots, b_{n,n} $ ( $ 0 \leq b_{i,n} < 2^{30} $ ).

## 输出格式

If some array $ a $ is consistent with the information, print a line containing $ n $ integers $ a_1, a_2, \ldots, a_n $ . If there are multiple solutions, output any.

If such an array does not exist, output $ -1 $ instead.

## 说明/提示

If we let $ a = [1,2,3] $ , then $ b $ will be:

  $ \bf{0} $  $ \bf{1} $  $ \bf{2} $  $ \bf{3} $  $ \bf{0} $  $ 1 $  $ 3 $  $ 0 $  $ \bf{0} $  $ 1 $  $ 2 $  $ 2 $  $ \bf{0} $  $ 1 $  $ 3 $  $ 1 $ The values of $ b_{1,n}, b_{2,n}, \ldots, b_{n,n} $ generated are $ [0,2,1] $ which is consistent with what the archaeologists have discovered.

## 样例 #1

### 输入

```
3
0 2 1
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
1
199633
```

### 输出

```
199633
```

## 样例 #3

### 输入

```
10
346484077 532933626 858787727 369947090 299437981 416813461 865836801 141384800 157794568 691345607
```

### 输出

```
725081944 922153789 481174947 427448285 516570428 509717938 855104873 280317429 281091129 1050390365
```

