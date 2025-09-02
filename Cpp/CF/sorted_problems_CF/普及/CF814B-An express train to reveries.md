---
title: "An express train to reveries"
layout: "post"
diff: 普及/提高-
pid: CF814B
tag: []
---

# An express train to reveries

## 题目描述

Sengoku still remembers the mysterious "colourful meteoroids" she discovered with Lala-chan when they were little. In particular, one of the nights impressed her deeply, giving her the illusion that all her fancies would be realized.

On that night, Sengoku constructed a permutation $ p_{1},p_{2},...,p_{n} $ of integers from $ 1 $ to $ n $ inclusive, with each integer representing a colour, wishing for the colours to see in the coming meteor outburst. Two incredible outbursts then arrived, each with $ n $ meteorids, colours of which being integer sequences $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ respectively. Meteoroids' colours were also between $ 1 $ and $ n $ inclusive, and the two sequences were not identical, that is, at least one $ i $ ( $ 1<=i<=n $ ) exists, such that $ a_{i}≠b_{i} $ holds.

Well, she almost had it all — each of the sequences $ a $ and $ b $ matched exactly $ n-1 $ elements in Sengoku's permutation. In other words, there is exactly one $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}≠p_{i} $ , and exactly one $ j $ ( $ 1<=j<=n $ ) such that $ b_{j}≠p_{j} $ .

For now, Sengoku is able to recover the actual colour sequences $ a $ and $ b $ through astronomical records, but her wishes have been long forgotten. You are to reconstruct any possible permutation Sengoku could have had on that night.

## 输入格式

The first line of input contains a positive integer $ n $ ( $ 2<=n<=1000 $ ) — the length of Sengoku's permutation, being the length of both meteor outbursts at the same time.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) — the sequence of colours in the first meteor outburst.

The third line contains $ n $ space-separated integers $ b_{1},b_{2},...,b_{n} $ ( $ 1<=b_{i}<=n $ ) — the sequence of colours in the second meteor outburst. At least one $ i $ ( $ 1<=i<=n $ ) exists, such that $ a_{i}≠b_{i} $ holds.

## 输出格式

Output $ n $ space-separated integers $ p_{1},p_{2},...,p_{n} $ , denoting a possible permutation Sengoku could have had. If there are more than one possible answer, output any one of them.

Input guarantees that such permutation exists.

## 说明/提示

In the first sample, both $ 1,2,5,4,3 $ and $ 1,2,3,4,5 $ are acceptable outputs.

In the second sample, $ 5,4,2,3,1 $ is the only permutation to satisfy the constraints.

## 样例 #1

### 输入

```
5
1 2 3 4 3
1 2 5 4 5

```

### 输出

```
1 2 5 4 3

```

## 样例 #2

### 输入

```
5
4 4 2 3 1
5 4 5 3 1

```

### 输出

```
5 4 2 3 1

```

## 样例 #3

### 输入

```
4
1 1 3 4
1 4 3 4

```

### 输出

```
1 2 3 4

```

