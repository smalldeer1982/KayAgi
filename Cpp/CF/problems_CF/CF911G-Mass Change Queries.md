---
title: "Mass Change Queries"
layout: "post"
diff: 提高+/省选-
pid: CF911G
tag: ['线段树', '枚举']
---

# Mass Change Queries

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to process $ q $ queries to this array; each query is given as four numbers $ l $ , $ r $ , $ x $ and $ y $ , denoting that for every $ i $ such that $ l<=i<=r $ and $ a_{i}=x $ you have to set $ a_{i} $ equal to $ y $ .

Print the array after all queries are processed.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ) — the size of array $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=100 $ ) — the elements of array $ a $ .

The third line contains one integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries you have to process.

Then $ q $ lines follow. $ i $ -th line contains four integers $ l $ , $ r $ , $ x $ and $ y $ denoting $ i $ -th query ( $ 1<=l<=r<=n $ , $ 1<=x,y<=100 $ ).

## 输出格式

Print $ n $ integers — elements of array $ a $ after all changes are made.

## 样例 #1

### 输入

```
5
1 2 3 4 5
3
3 5 3 5
1 5 5 1
1 5 1 5

```

### 输出

```
5 2 5 4 5 
```

