---
title: "Yet Another Array Queries Problem"
layout: "post"
diff: 普及+/提高
pid: CF863D
tag: []
---

# Yet Another Array Queries Problem

## 题目描述

You are given an array $ a $ of size $ n $ , and $ q $ queries to it. There are queries of two types:

- $ 1 $ $ l_{i} $ $ r_{i} $ — perform a cyclic shift of the segment $ [l_{i},r_{i}] $ to the right. That is, for every $ x $ such that $ l_{i}<=x<r_{i} $ new value of $ a_{x+1} $ becomes equal to old value of $ a_{x} $ , and new value of $ a_{li} $ becomes equal to old value of $ a_{ri} $ ;
- $ 2 $ $ l_{i} $ $ r_{i} $ — reverse the segment $ [l_{i},r_{i}] $ .

There are $ m $ important indices in the array $ b_{1} $ , $ b_{2} $ , ..., $ b_{m} $ . For each $ i $ such that $ 1<=i<=m $ you have to output the number that will have index $ b_{i} $ in the array after all queries are performed.

## 输入格式

The first line contains three integer numbers $ n $ , $ q $ and $ m $ ( $ 1<=n,q<=2·10^{5} $ , $ 1<=m<=100 $ ).

The second line contains $ n $ integer numbers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Then $ q $ lines follow. $ i $ -th of them contains three integer numbers $ t_{i} $ , $ l_{i} $ , $ r_{i} $ , where $ t_{i} $ is the type of $ i $ -th query, and $ [l_{i},r_{i}] $ is the segment where this query is performed ( $ 1<=t_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ ).

The last line contains $ m $ integer numbers $ b_{1} $ , $ b_{2} $ , ..., $ b_{m} $ ( $ 1<=b_{i}<=n $ ) — important indices of the array.

## 输出格式

Print $ m $ numbers, $ i $ -th of which is equal to the number at index $ b_{i} $ after all queries are done.

## 样例 #1

### 输入

```
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3

```

### 输出

```
3 3 1 5 2 

```

