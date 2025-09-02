---
title: "Partial Sums"
layout: "post"
diff: 普及+/提高
pid: CF223C
tag: []
---

# Partial Sums

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers. The array elements are indexed from 1 to $ n $ . Let's determine a two step operation like that:

1. First we build by the array $ a $ an array $ s $ of partial sums, consisting of $ n $ elements. Element number $ i $ ( $ 1<=i<=n $ ) of array $ s $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF223C/c051478f9fc3965030766767424a5562a646a777.png). The operation $ x mod y $ means that we take the remainder of the division of number $ x $ by number $ y $ .
2. Then we write the contents of the array $ s $ to the array $ a $ . Element number $ i $ ( $ 1<=i<=n $ ) of the array $ s $ becomes the $ i $ -th element of the array $ a $ ( $ a_{i}=s_{i} $ ).

You task is to find array $ a $ after exactly $ k $ described operations are applied.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=2000 $ , $ 0<=k<=10^{9} $ ). The next line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ — elements of the array $ a $ ( $ 0<=a_{i}<=10^{9} $ ).

## 输出格式

Print $ n $ integers — elements of the array $ a $ after the operations are applied to it. Print the elements in the order of increasing of their indexes in the array $ a $ . Separate the printed numbers by spaces.

## 样例 #1

### 输入

```
3 1
1 2 3

```

### 输出

```
1 3 6

```

## 样例 #2

### 输入

```
5 0
3 14 15 92 6

```

### 输出

```
3 14 15 92 6

```

