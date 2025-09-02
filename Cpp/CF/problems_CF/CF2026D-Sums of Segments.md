---
title: "Sums of Segments"
layout: "post"
diff: 普及+/提高
pid: CF2026D
tag: ['二分', '前缀和']
---

# Sums of Segments

## 题目描述

You are given a sequence of integers $ [a_1, a_2, \dots, a_n] $ . Let $ s(l,r) $ be the sum of elements from $ a_l $ to $ a_r $ (i. e. $ s(l,r) = \sum\limits_{i=l}^{r} a_i $ ).

Let's construct another sequence $ b $ of size $ \frac{n(n+1)}{2} $ as follows: $ b = [s(1,1), s(1,2), \dots, s(1,n), s(2,2), s(2,3), \dots, s(2,n), s(3,3), \dots, s(n,n)] $ .

For example, if $ a = [1, 2, 5, 10] $ , then $ b = [1, 3, 8, 18, 2, 7, 17, 5, 15, 10] $ .

You are given $ q $ queries. During the $ i $ -th query, you are given two integers $ l_i $ and $ r_i $ , and you have to calculate $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10 \le a_i \le 10 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le \frac{n(n+1)}{2} $ ).

## 输出格式

Print $ q $ integers, the $ i $ -th of which should be equal to $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 样例 #1

### 输入

```
4
1 2 5 10
15
1 1
1 2
1 3
1 4
1 5
1 10
5 10
6 10
2 8
3 4
3 10
3 8
5 6
5 5
1 8
```

### 输出

```
1
4
12
30
32
86
56
54
60
26
82
57
9
2
61
```

