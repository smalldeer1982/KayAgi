---
title: "Tokitsukaze and Gems"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1677F
tag: []
---

# Tokitsukaze and Gems

## 题目描述

Tokitsukaze has a sequence with length of $ n $ . She likes gems very much. There are $ n $ kinds of gems. The gems of the $ i $ -th kind are on the $ i $ -th position, and there are $ a_i $ gems of the same kind on that position. Define $ G(l,r) $ as the multiset containing all gems on the segment $ [l,r] $ (inclusive).

A multiset of gems can be represented as $ S=[s_1,s_2,\ldots,s_n] $ , which is a non-negative integer sequence of length $ n $ and means that $ S $ contains $ s_i $ gems of the $ i $ -th kind in the multiset. A multiset $ T=[t_1,t_2,\ldots,t_n] $ is a multisubset of $ S=[s_1,s_2,\ldots,s_n] $ if and only if $ t_i\le s_i $ for any $ i $ satisfying $ 1\le i\le n $ .

Now, given two positive integers $ k $ and $ p $ , you need to calculate the result of

 $ $$$\sum_{l=1}^n \sum_{r=l}^n\sum\limits_{[t_1,t_2,\cdots,t_n] \subseteq G(l,r)}\left(\left(\sum_{i=1}^n p^{t_i}t_i^k\right)\left(\sum_{i=1}^n[t_i>0]\right)\right), $ $ </p><p>where  $ \[t\_i&gt;0\]=1 $  if  $ t\_i&gt;0 $  and  $ \[t\_i&gt;0\]=0 $  if  $ t\_i=0 $ .</p><p>Since the answer can be quite large, print it modulo  $ 998\\,244\\,353$$$.

## 输入格式

The first line contains three integers $ n $ , $ k $ and $ p $ ( $ 1\le n \le 10^5 $ ; $ 1\le k\le 10^5 $ ; $ 2\le p\le 998\,244\,351 $ ) — the length of the sequence, the numbers $ k $ and $ p $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1\le a_i\le 998\,244\,351 $ ) — the number of gems on the $ i $ -th position.

## 输出格式

Print a single integers — the result modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
5 2 2
1 1 1 2 2
```

### 输出

```
6428
```

## 样例 #2

### 输入

```
6 2 2
2 2 2 2 2 3
```

### 输出

```
338940
```

