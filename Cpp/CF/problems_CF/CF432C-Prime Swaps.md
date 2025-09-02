---
title: "Prime Swaps"
layout: "post"
diff: 普及+/提高
pid: CF432C
tag: ['数论']
---

# Prime Swaps

## 题目描述

You have an array $ a[1],a[2],...,a[n] $ , containing distinct integers from $ 1 $ to $ n $ . Your task is to sort this array in increasing order with the following operation (you may need to apply it multiple times):

- choose two indexes, $ i $ and $ j $ ( $ 1<=i&lt;j<=n $ ; $ (j-i+1) $ is a prime number);
- swap the elements on positions $ i $ and $ j $ ; in other words, you are allowed to apply the following sequence of assignments: $ tmp=a[i],a[i]=a[j],a[j]=tmp $ ( $ tmp $ is a temporary variable).

You do not need to minimize the number of used operations. However, you need to make sure that there are at most $ 5n $ operations.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ . The next line contains $ n $ distinct integers $ a[1],a[2],...,a[n] $ $ (1<=a[i]<=n) $ .

## 输出格式

In the first line, print integer $ k $ $ (0<=k<=5n) $ — the number of used operations. Next, print the operations. Each operation must be printed as " $ i $ $ j $ " ( $ 1<=i&lt;j<=n $ ; $ (j-i+1) $ is a prime).

If there are multiple answers, you can print any of them.

## 样例 #1

### 输入

```
3
3 2 1

```

### 输出

```
1
1 3

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
4 2 3 1

```

### 输出

```
3
2 4
1 2
2 4

```

