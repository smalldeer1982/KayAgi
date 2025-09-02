---
title: "Maxim and Array"
layout: "post"
diff: 普及+/提高
pid: CF721D
tag: []
---

# Maxim and Array

## 题目描述

Recently Maxim has found an array of $ n $ integers, needed by no one. He immediately come up with idea of changing it: he invented positive integer $ x $ and decided to add or subtract it from arbitrary array elements. Formally, by applying single operation Maxim chooses integer $ i $ ( $ 1<=i<=n $ ) and replaces the $ i $ -th element of array $ a_{i} $ either with $ a_{i}+x $ or with $ a_{i}-x $ . Please note that the operation may be applied more than once to the same position.

Maxim is a curious minimalis, thus he wants to know what is the minimum value that the product of all array elements (i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721D/ae24ba75281e48338d849938ea05477ca771d520.png)) can reach, if Maxim would apply no more than $ k $ operations to it. Please help him in that.

## 输入格式

The first line of the input contains three integers $ n,k $ and $ x $ ( $ 1<=n,k<=200000,1<=x<=10^{9} $ ) — the number of elements in the array, the maximum number of operations and the number invented by Maxim, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721D/572ce5a5b9bda792f62b8b3f471edc8abe20d325.png)) — the elements of the array found by Maxim.

## 输出格式

Print $ n $ integers $ b_{1},b_{2},...,b_{n} $ in the only line — the array elements after applying no more than $ k $ operations to the array. In particular, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721D/b40db9bc1a1c2c92af05e7feaa65d75eb4d3773f.png) should stay true for every $ 1<=i<=n $ , but the product of all array elements should be minimum possible.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
5 3 1
5 4 3 5 2

```

### 输出

```
5 4 3 5 -1 

```

## 样例 #2

### 输入

```
5 3 1
5 4 3 5 5

```

### 输出

```
5 4 0 5 5 

```

## 样例 #3

### 输入

```
5 3 1
5 4 4 5 5

```

### 输出

```
5 1 4 5 5 

```

## 样例 #4

### 输入

```
3 2 7
5 4 2

```

### 输出

```
5 11 -5 

```

