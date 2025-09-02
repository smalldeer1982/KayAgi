---
title: "Max History"
layout: "post"
diff: 提高+/省选-
pid: CF938E
tag: []
---

# Max History

## 题目描述

You are given an array $ a $ of length $ n $ . We define $ f_{a} $ the following way:

- Initially $ f_{a}=0 $ , $ M=1 $ ;
- for every $ 2<=i<=n $ if $ a_{M}<a_{i} $ then we set $ f_{a}=f_{a}+a_{M} $ and then set $ M=i $ .

Calculate the sum of $ f_{a} $ over all $ n! $ permutations of the array $ a $ modulo $ 10^{9}+7 $ .

Note: two elements are considered different if their indices differ, so for every array $ a $ there are exactly $ n! $ permutations.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1\ 000\ 000 $ ) — the size of array $ a $ .

Second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the only integer, the sum of $ f_{a} $ over all $ n! $ permutations of the array $ a $ modulo $ 10^{9}+7 $ .

## 说明/提示

For the second example all the permutations are:

- $ p=[1,2,3] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[1,3,2] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[2,1,3] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[2,3,1] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[3,1,2] $ : $ f_{a} $ is equal to $ 0 $ ;
- $ p=[3,2,1] $ : $ f_{a} $ is equal to $ 0 $ .

Where $ p $ is the array of the indices of initial array $ a $ . The sum of $ f_{a} $ is equal to $ 4 $ .

## 样例 #1

### 输入

```
2
1 3

```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 1 2

```

### 输出

```
4
```

