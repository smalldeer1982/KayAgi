---
title: "PermuTree (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1856E2
tag: []
---

# PermuTree (hard version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are the constraint on $ n $ and the time limit. You can make hacks only if both versions of the problem are solved.

You are given a tree with $ n $ vertices rooted at vertex $ 1 $ .

For some permutation $ ^\dagger $ $ a $ of length $ n $ , let $ f(a) $ be the number of pairs of vertices $ (u, v) $ such that $ a_u < a_{\operatorname{lca}(u, v)} < a_v $ . Here, $ \operatorname{lca}(u,v) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ u $ and $ v $ .

Find the maximum possible value of $ f(a) $ over all permutations $ a $ of length $ n $ .

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ).

The second line contains $ n - 1 $ integers $ p_2,p_3,\ldots,p_n $ ( $ 1 \le p_i < i $ ) indicating that there is an edge between vertices $ i $ and $ p_i $ .

## 输出格式

Output the maximum value of $ f(a) $ .

## 说明/提示

The tree in the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)One possible optimal permutation $ a $ is $ [2, 1, 4, 5, 3] $ with $ 4 $ suitable pairs of vertices:

- $ (2, 3) $ , since $ \operatorname{lca}(2, 3) = 1 $ and $ 1 < 2 < 4 $ ,
- $ (2, 4) $ , since $ \operatorname{lca}(2, 4) = 1 $ and $ 1 < 2 < 5 $ ,
- $ (2, 5) $ , since $ \operatorname{lca}(2, 5) = 1 $ and $ 1 < 2 < 3 $ ,
- $ (5, 4) $ , since $ \operatorname{lca}(5, 4) = 3 $ and $ 3 < 4 < 5 $ .

The tree in the third test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/d99652a679d9214ec6283dd777f9d3b7f1434695.png)The tree in the fourth test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/1b3604b93549da62e326378a176bbc03c4448da2.png)

## 样例 #1

### 输入

```
5
1 1 3 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
1 2 2 1 5
```

### 输出

```
7
```

## 样例 #4

### 输入

```
4
1 1 1
```

### 输出

```
2
```

