---
title: "Almost Sorted"
layout: "post"
diff: 省选/NOI-
pid: CF1730F
tag: []
---

# Almost Sorted

## 题目描述

You are given a permutation $ p $ of length $ n $ and a positive integer $ k $ . Consider a permutation $ q $ of length $ n $ such that for any integers $ i $ and $ j $ , where $ 1 \le i < j \le n $ , we have $ $$$p_{q_i} \le p_{q_j} + k. $ $ </p><p>Find the minimum possible number of inversions in a permutation  $ q $ .</p><p>A permutation is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array) and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4 $  in the array).</p><p>An inversion in a permutation  $ a $  is a pair of indices  $ i $  and  $ j $  ( $ 1 \\le i, j \\le n $ ) such that  $ i &lt; j $ , but  $ a\_i &gt; a\_j$$$.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 5000 $ , $ 1 \le k \le 8 $ ).

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ).

## 输出格式

Print the minimum possible number of inversions in the permutation $ q $ .

## 说明/提示

In the first example, the only permutation is $ q = [1] $ ( $ 0 $ inversions). Then $ p_{q_1} = 1 $ .

In the second example, the only permutation with $ 1 $ inversion is $ q = [1, 3, 2] $ . Then $ p_{q_1} = 2 $ , $ p_{q_2} = 1 $ , $ p_{q_3} = 3 $ .

In the third example, one of the possible permutations with $ 6 $ inversions is $ q = [3, 4, 5, 1, 2] $ . Then $ p_{q_1} = 3 $ , $ p_{q_2} = 2 $ , $ p_{q_3} = 1 $ , $ p_{q_4} = 5 $ , $ p_{q_5} = 4 $ .

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 1
2 3 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 2
5 4 3 2 1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
10 3
5 8 6 10 2 7 4 1 9 3
```

### 输出

```
18
```

