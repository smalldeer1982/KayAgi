---
title: "Permutation Sum"
layout: "post"
diff: 普及+/提高
pid: CF285D
tag: []
---

# Permutation Sum

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

Petya decided to introduce the sum operation on the set of permutations of length $ n $ . Let's assume that we are given two permutations of length $ n $ : $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ . Petya calls the sum of permutations $ a $ and $ b $ such permutation $ c $ of length $ n $ , where $ c_{i}=((a_{i}-1+b_{i}-1)\ mod\ n)+1 $ $ (1<=i<=n) $ .

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Obviously, not for all permutations $ a $ and $ b $ exists permutation $ c $ that is sum of $ a $ and $ b $ . That's why Petya got sad and asked you to do the following: given $ n $ , count the number of such pairs of permutations $ a $ and $ b $ of length $ n $ , that exists permutation $ c $ that is sum of $ a $ and $ b $ . The pair of permutations $ x,y $ $ (x≠y) $ and the pair of permutations $ y,x $ are considered distinct pairs.

As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The single line contains integer $ n\ (1<=n<=16) $ .

## 输出格式

In the single line print a single non-negative integer — the number of such pairs of permutations $ a $ and $ b $ , that exists permutation $ c $ that is sum of $ a $ and $ b $ , modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3

```

### 输出

```
18

```

## 样例 #2

### 输入

```
5

```

### 输出

```
1800

```

