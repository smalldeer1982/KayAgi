---
title: "Special Positions"
layout: "post"
diff: 省选/NOI-
pid: CF1641E
tag: []
---

# Special Positions

## 题目描述

You are given an array $ a $ of length $ n $ . Also you are given $ m $ distinct positions $ p_1, p_2, \ldots, p_m $ ( $ 1 \leq p_i \leq n $ ).

A non-empty subset of these positions $ T $ is randomly selected with equal probability and the following value is calculated: $ $$$\sum_{i=1}^{n} (a_i \cdot \min_{j \in T} \left|i - j\right|). $ $  In other word, for each index of the array,  $ a\_i $  and the distance to the closest chosen position are multiplied, and then these values are summed up.</p><p>Find the expected value of this sum.</p><p>This value must be found modulo  $ 998\\,244\\,353 $ . More formally, let  $ M = 998\\,244\\,353 $ . It can be shown that the answer can be represented as an irreducible fraction  $ \\frac{p}{q} $ , where  $ p $  and  $ q $  are integers and  $ q \\neq 0 $  (mod  $ M $ ). Output the integer equal to  $ p \\cdot q^{-1} $  (mod  $ M $ ). In other words, output such integer  $ x $  that  $ 0 \\leq x &lt; M $  and  $ x \\cdot q = p $  (mod  $ M$$$).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 998\,244\,353 $ ).

The third line contains $ m $ distinct integers $ p_1, p_2, \ldots, p_m $ ( $ 1 \leq p_i \le n $ ).

For every $ 1 \leq i < m $ it is guaranteed that $ p_i < p_{i+1} $ .

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first test:

- If only $ 1 $ is choosen, than the value equals to $ 1 \cdot 0 + 2 \cdot 1 + 3 \cdot 2 + 4 \cdot 3 = 20 $ .
- If only $ 4 $ is choosen, than the value equals to $ 1 \cdot 3 + 2 \cdot 2 + 3 \cdot 1 + 4 \cdot 0 = 10 $ .
- If both positions are chosen, than the value equals to $ 1 \cdot 0 + 2 \cdot 1 + 3 \cdot 1 + 4 \cdot 0 = 5 $ .

The answer to the problem is $ \frac{20 + 10 + 5}{3} = \frac{35}{3} = 665\,496\,247 $ (modulo $ 998\,244\,353 $ ).

## 样例 #1

### 输入

```
4 2
1 2 3 4
1 4
```

### 输出

```
665496247
```

## 样例 #2

### 输入

```
6 6
4 2 4 2 4 2
1 2 3 4 5 6
```

### 输出

```
855638030
```

