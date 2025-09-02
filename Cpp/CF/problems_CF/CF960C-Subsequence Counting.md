---
title: "Subsequence Counting"
layout: "post"
diff: 普及/提高-
pid: CF960C
tag: []
---

# Subsequence Counting

## 题目描述

Pikachu had an array with him. He wrote down all the non-empty subsequences of the array on paper. Note that an array of size $ n $ has $ 2^{n}-1 $ non-empty subsequences in it.

Pikachu being mischievous as he always is, removed all the subsequences in which Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=d $

Pikachu was finally left with $ X $ subsequences.

However, he lost the initial array he had, and now is in serious trouble. He still remembers the numbers $ X $ and $ d $ . He now wants you to construct any such array which will satisfy the above conditions. All the numbers in the final array should be positive integers less than $ 10^{18} $ .

Note the number of elements in the output array should not be more than $ 10^{4} $ . If no answer is possible, print $ -1 $ .

## 输入格式

The only line of input consists of two space separated integers $ X $ and $ d $ ( $ 1<=X,d<=10^{9} $ ).

## 输出格式

Output should consist of two lines.

First line should contain a single integer $ n $ ( $ 1<=n<=10000 $ )— the number of integers in the final array.

Second line should consist of $ n $ space separated integers — $ a_{1},a_{2},...\ ,a_{n} $ ( $ 1<=a_{i}<10^{18} $ ).

If there is no answer, print a single integer -1. If there are multiple answers, print any of them.

## 说明/提示

In the output of the first example case, the remaining subsequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=5 $ are $ [5],[5,7],[5,6],[5,7,6],[50],[7],[7,6],[15],[6],[100] $ . There are $ 10 $ of them. Hence, the array $ [5,50,7,15,6,100] $ is valid.

Similarly, in the output of the second example case, the remaining sub-sequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=2 $ are $ [10],[100],[1000],[10000] $ . There are $ 4 $ of them. Hence, the array $ [10,100,1000,10000] $ is valid.

## 样例 #1

### 输入

```
10 5

```

### 输出

```
6
5 50 7 15 6 100
```

## 样例 #2

### 输入

```
4 2

```

### 输出

```
4
10 100 1000 10000
```

