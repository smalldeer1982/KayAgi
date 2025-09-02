---
title: "Matrix Rank (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1916H2
tag: ['线性代数']
---

# Matrix Rank (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given integers $ n $ , $ p $ and $ k $ . $ p $ is guaranteed to be a prime number.

For each $ r $ from $ 0 $ to $ k $ , find the number of $ n \times n $ matrices $ A $ of the field $ ^\dagger $ of integers modulo $ p $ such that the rank $ ^\ddagger $ of $ A $ is exactly $ r $ . Since these values are big, you are only required to output them modulo $ 998\,244\,353 $ .

 $ ^\dagger $ [https://en.wikipedia.org/wiki/Field\_(mathematics)](https://en.wikipedia.org/wiki/Field_(mathematics))

 $ ^\ddagger $ [https://en.wikipedia.org/wiki/Rank\_(linear\_algebra)](https://en.wikipedia.org/wiki/Rank_(linear_algebra))

## 输入格式

The first line of input contains three integers $ n $ , $ p $ and $ k $ ( $ 1 \leq n \leq 10^{18} $ , $ 2 \leq p < 998\,244\,353 $ , $ 0 \leq k \leq 5 \cdot 10^5 $ ).

It is guaranteed that $ p $ is a prime number.

## 输出格式

Output $ k+1 $ integers, the answers for each $ r $ from $ 0 $ to $ k $ .

## 样例 #1

### 输入

```
3 2 3
```

### 输出

```
1 49 294 168
```

## 样例 #2

### 输入

```
1 51549919 2
```

### 输出

```
1 51549918 0
```

