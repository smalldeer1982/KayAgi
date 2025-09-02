---
title: "Hamming Triples"
layout: "post"
diff: 省选/NOI-
pid: CF406E
tag: []
---

# Hamming Triples

## 题目描述

Little Chris is having a nightmare. Even in dreams all he thinks about is math.

Chris dreams about $ m $ binary strings of length $ n $ , indexed with numbers from 1 to $ m $ . The most horrifying part is that the bits of each string are ordered in either ascending or descending order. For example, Chris could be dreaming about the following 4 strings of length 5:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF406E/2bc92794d57f524d37633fb25d36a0e9463e28fd.png)The Hamming distance $ H(a,b) $ between two strings $ a $ and $ b $ of length $ n $ is the number of positions at which the corresponding symbols are different.

Сhris thinks that each three strings with different indices constitute a single triple. Chris's delusion is that he will wake up only if he counts the number of such string triples $ a $ , $ b $ , $ c $ that the sum $ H(a,b)+H(b,c)+H(c,a) $ is maximal among all the string triples constructed from the dreamed strings.

Help Chris wake up from this nightmare!

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ m $ ( $ 1<=n<=10^{9} $ ; $ 3<=m<=10^{5} $ ), the length and the number of strings. The next $ m $ lines contain the description of the strings. The $ i $ -th line contains two space-separated integers $ s_{i} $ and $ f_{i} $ ( $ 0<=s_{i}<=1 $ ; $ 1<=f_{i}<=n $ ), the description of the string with index $ i $ ; that means that the first $ f_{i} $ bits of the $ i $ -th string are equal to $ s_{i} $ , and the remaining $ n-f_{i} $ bits are equal to $ 1-s_{i} $ . There can be multiple equal strings in Chris's dream.

## 输出格式

Output a single integer, the number of such string triples among the given that the sum of the Hamming distances between the strings of the triple is maximal.

## 样例 #1

### 输入

```
5 4
0 3
0 5
1 4
1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 4
1 5
0 5
0 5
1 5

```

### 输出

```
4

```

