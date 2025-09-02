---
title: "Partitions"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF961G
tag: []
---

# Partitions

## 题目描述

You are given a set of $ n $ elements indexed from $ 1 $ to $ n $ . The weight of $ i $ -th element is $ w_{i} $ . The weight of some subset of a given set is denoted as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961G/fbf0c843290b6183affbaf7ada0d6cecd6d2fbbd.png). The weight of some partition $ R $ of a given set into $ k $ subsets is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961G/0aeb77393cfc4b9aa3d9c64303202277f9c1f051.png) (recall that a partition of a given set is a set of its subsets such that every element of the given set belongs to exactly one subset in partition).

Calculate the sum of weights of all partitions of a given set into exactly $ k $ non-empty subsets, and print it modulo $ 10^{9}+7 $ . Two partitions are considered different iff there exist two elements $ x $ and $ y $ such that they belong to the same set in one of the partitions, and to different sets in another partition.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=2·10^{5} $ ) — the number of elements and the number of subsets in each partition, respectively.

The second line contains $ n $ integers $ w_{i} $ ( $ 1<=w_{i}<=10^{9} $ )— weights of elements of the set.

## 输出格式

Print one integer — the sum of weights of all partitions of a given set into $ k $ non-empty subsets, taken modulo $ 10^{9}+7 $ .

## 说明/提示

Possible partitions in the first sample:

1. $ \{\{1,2,3\},\{4\}\} $ , $ W(R)=3\cdot(w_{1}+w_{2}+w_{3})+1\cdot w_{4}=24 $ ;
2. $ \{\{1,2,4\},\{3\}\} $ , $ W(R)=26 $ ;
3. $ \{\{1,3,4\},\{2\}\} $ , $ W(R)=24 $ ;
4. $ \{\{1,2\},\{3,4\}\} $ , $ W(R)=2\cdot(w_{1}+w_{2})+2\cdot(w_{3}+w_{4})=20 $ ;
5. $ \{\{1,3\},\{2,4\}\} $ , $ W(R)=20 $ ;
6. $ \{\{1,4\},\{2,3\}\} $ , $ W(R)=20 $ ;
7. $ \{\{1\},\{2,3,4\}\} $ , $ W(R)=26 $ ;

Possible partitions in the second sample:

1. $ \{\{1,2,3,4\},\{5\}\} $ , $ W(R)=45 $ ;
2. $ \{\{1,2,3,5\},\{4\}\} $ , $ W(R)=48 $ ;
3. $ \{\{1,2,4,5\},\{3\}\} $ , $ W(R)=51 $ ;
4. $ \{\{1,3,4,5\},\{2\}\} $ , $ W(R)=54 $ ;
5. $ \{\{2,3,4,5\},\{1\}\} $ , $ W(R)=57 $ ;
6. $ \{\{1,2,3\},\{4,5\}\} $ , $ W(R)=36 $ ;
7. $ \{\{1,2,4\},\{3,5\}\} $ , $ W(R)=37 $ ;
8. $ \{\{1,2,5\},\{3,4\}\} $ , $ W(R)=38 $ ;
9. $ \{\{1,3,4\},\{2,5\}\} $ , $ W(R)=38 $ ;
10. $ \{\{1,3,5\},\{2,4\}\} $ , $ W(R)=39 $ ;
11. $ \{\{1,4,5\},\{2,3\}\} $ , $ W(R)=40 $ ;
12. $ \{\{2,3,4\},\{1,5\}\} $ , $ W(R)=39 $ ;
13. $ \{\{2,3,5\},\{1,4\}\} $ , $ W(R)=40 $ ;
14. $ \{\{2,4,5\},\{1,3\}\} $ , $ W(R)=41 $ ;
15. $ \{\{3,4,5\},\{1,2\}\} $ , $ W(R)=42 $ .

## 样例 #1

### 输入

```
4 2
2 3 2 3

```

### 输出

```
160

```

## 样例 #2

### 输入

```
5 2
1 2 3 4 5

```

### 输出

```
645

```

