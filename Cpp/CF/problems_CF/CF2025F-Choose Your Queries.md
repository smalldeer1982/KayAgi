---
title: "Choose Your Queries"
layout: "post"
diff: 提高+/省选-
pid: CF2025F
tag: ['图论', '构造']
---

# Choose Your Queries

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers (numbered from $ 1 $ to $ n $ ). Initially, they are all zeroes.

You have to process $ q $ queries. The $ i $ -th query consists of two different integers $ x_i $ and $ y_i $ . During the $ i $ -th query, you have to choose an integer $ p $ (which is either $ x_i $ or $ y_i $ ) and an integer $ d $ (which is either $ 1 $ or $ -1 $ ), and assign $ a_p = a_p + d $ .

After each query, every element of $ a $ should be a non-negative integer.

Process all queries in such a way that the sum of all elements of $ a $ after the last query is the minimum possible.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 3 \cdot 10^5 $ ; $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of elements in $ a $ and the number of queries, respectively.

Then $ q $ lines follow. The $ i $ -th of these lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ) — the description of the $ i $ -th query.

## 输出格式

For each query, print a line containing two characters:

- the first character should be x if you choose $ p=x_i $ , or y if you choose $ p=y_i $ ;
- the second character should be + if you choose $ d=1 $ , or - if you choose $ d=-1 $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3 4
1 2
3 2
3 1
1 2
```

### 输出

```
y+
x+
x-
y-
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
3 2
```

### 输出

```
y+
y+
x-
y-
```

## 样例 #3

### 输入

```
4 2
2 1
4 3
```

### 输出

```
y+
x+
```

