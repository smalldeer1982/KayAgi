---
title: "Maxim and Increasing Subsequence"
layout: "post"
diff: 省选/NOI-
pid: CF261D
tag: ['线段树', '树状数组', '枚举']
---

# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 输入格式

The first line contains four integers $ k $ , $ n $ , $ maxb $ and $ t $ $ (1<=k<=10; 1<=n,maxb<=10^{5}; 1<=t<=10^{9}; n×maxb<=2·10^{7}) $ . Each of the next $ k $ lines contain $ n $ integers $ b_{1},b_{2},...,b_{n} $ $ (1<=b_{i}<=maxb) $ .

Note that for each variant of the sequence $ a $ the values $ n $ , $ maxb $ and $ t $ coincide, the only arrays $ b $ s differ.

The numbers in the lines are separated by single spaces.

## 输出格式

Print $ k $ integers — the answers for the variants of the sequence $ a $ . Print the answers in the order the variants follow in the input.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1

```

### 输出

```
2
3
3

```

