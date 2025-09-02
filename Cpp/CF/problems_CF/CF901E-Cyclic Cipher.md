---
title: "Cyclic Cipher"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF901E
tag: []
---

# Cyclic Cipher

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/09d58666f469d1212864032a997630308f9a2d24.png)Senor Vorpal Kickass'o invented an innovative method to encrypt integer sequences of length $ n $ . To encrypt a sequence, one has to choose a secret sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/9d7f596ac3bfcb4de56caec3ed98f54b8c38886c.png), that acts as a key.

Vorpal is very selective, so the key should be such a sequence $ b_{i} $ , that its cyclic shifts are linearly independent, that is, there is no non-zero set of coefficients $ x_{0},x_{1},...,x_{n-1} $ , such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/14fc308524a42e2bfab7fa5bbb60c1743e7911b3.png) for all $ k $ at the same time.

After that for a sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/5656a7a50865b0a2e60963f7abba52e4c4e82222.png) you should build the following cipher:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/d8113c9899e75c215e4f30da73d960636a7306eb.png)In other words, you are to compute the quadratic deviation between each cyclic shift of $ b_{i} $ and the sequence $ a_{i} $ . The resulting sequence is the Kickass's cipher. The cipher is in development right now and Vorpal wants to decipher a sequence after it has been encrypted. You are to solve this problem for him. You are given sequences $ c_{i} $ and $ b_{i} $ . You are to find all suitable sequences $ a_{i} $ .

## 输入格式

The first line contains a single integer $ n $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/a561449171a1bc59fbb05203f289e5e1c414774f.png)).

The second line contains $ n $ integers $ b_{0},b_{1},...,b_{n-1} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/2a78fbaa6d9660a0c2b6472729af999a0faba958.png)).

The third line contains $ n $ integers $ c_{0},c_{1},...,c_{n-1} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901E/51a6ffa808ccafa5d6d5accd5a8a674e36e0a223.png)).

It is guaranteed that all cyclic shifts of sequence $ b_{i} $ are linearly independent.

## 输出格式

In the first line print a single integer $ k $ — the number of sequences $ a_{i} $ , such that after encrypting them with key $ b_{i} $ you get the sequence $ c_{i} $ .

After that in each of $ k $ next lines print $ n $ integers $ a_{0},a_{1},...,a_{n-1} $ . Print the sequences in lexicographical order.

Note that $ k $ could be equal to $ 0 $ .

## 样例 #1

### 输入

```
1
1
0

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
1
100
81

```

### 输出

```
2
91
109

```

## 样例 #3

### 输入

```
3
1 1 3
165 185 197

```

### 输出

```
2
-6 -9 -1
8 5 13

```

