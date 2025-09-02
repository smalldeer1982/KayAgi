---
title: "Two Segments"
layout: "post"
diff: 省选/NOI-
pid: CF193D
tag: []
---

# Two Segments

## 题目描述

Nick has some permutation consisting of $ p $ integers from $ 1 $ to $ n $ . A segment $ [l,r] $ ( $ l<=r $ ) is a set of elements $ p_{i} $ satisfying $ l<=i<=r $ .

Nick calls a pair of segments $ [a_{0},a_{1}] $ and $ [b_{0},b_{1}] $ ( $ 1<=a_{0}<=a_{1}&lt;b_{0}<=b_{1}<=n $ ) good if all their $ (a_{1}-a_{0}+b_{1}-b_{0}+2) $ elements, when sorted in ascending order, form an arithmetic progression with a difference of $ 1 $ . That is, when they sorted in ascending order, the elements are in the form $ {x,x+1,x+2,...,x+m-1} $ , for some $ x $ and $ m $ .

Your task is to find the number of distinct pairs of good segments in the given permutation. Two pairs of segments are considered distinct if the sets of elements contained in these pairs of segments are distinct. For example, any segment $ [l,r] $ $ (l&lt;r) $ can be represented as a pair of segments, as $ [l,i] $ and $ [i+1,r] $ ( $ l<=i<=r $ ). As all these pairs consist of the same set of elements, they are considered identical.

See the notes accompanying the sample tests for clarification.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the permutation size. The second line contains $ n $ space-separated distinct integers $ p_{i} $ , ( $ 1<=p_{i}<=n $ ).

## 输出格式

Print a single integer — the number of good pairs of segments of permutation $ p $ .

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample the following pairs of segments are good: ( $ [1,1] $ , $ [2,2] $ ); ( $ [2,2] $ , $ [3,3] $ ); ( $ [1,2] $ , $ [3,3] $ ). Pair of segments ( $ [1,1] $ , $ [2,3] $ ) is by definition equivalent to pair ( $ [1,2] $ , $ [3,3] $ ), since both of them covers the same set of elements, namely $ {1,2,3} $ .

In the third sample the following pairs of segments are good: ( $ [4,4] $ , $ [5,5] $ ); ( $ [3,3] $ , $ [4,5] $ ); ( $ [2,2] $ , $ [3,5] $ ); ( $ [1,1] $ , $ [2,5] $ ); ( $ [3,3] $ , $ [5,5] $ ); ( $ [2,3] $ , $ [5,5] $ ); ( $ [1,3] $ , $ [5,5] $ ); ( $ [2,2] $ , $ [3,3] $ ); ( $ [1,1] $ , $ [2,3] $ ); ( $ [1,1] $ , $ [2,2] $ ).

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
1 4 5 3 2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
5
5 4 3 1 2

```

### 输出

```
10

```

