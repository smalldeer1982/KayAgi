---
title: "The Neutral Zone"
layout: "post"
diff: 提高+/省选-
pid: CF1017F
tag: []
---

# The Neutral Zone

## 题目描述

Notice: unusual memory limit!

After the war, destroyed cities in the neutral zone were restored. And children went back to school.

The war changed the world, as well as education. In those hard days, a new math concept was created.

As we all know, logarithm function can be described as: $ $$$ \log(p_1^{a_1}p_2^{a_2}...p_k^{a_2}) = a_1 \log p_1 + a_2 \log p_2 + ... + a_k \log p_k  $ $  Where  $ p\_1^{a\_1}p\_2^{a\_2}...p\_k^{a\_2} $  is the prime factorization of a integer. A problem is that the function uses itself in the definition. That is why it is hard to calculate.</p><p>So, the mathematicians from the neutral zone invented this:  $ $  \text{exlog}_f(p_1^{a_1}p_2^{a_2}...p_k^{a_2}) = a_1 f(p_1) + a_2 f(p_2) + ... + a_k f(p_k)  $ $ </p><p>Notice that  $ \\text{exlog}\_f(1) $  is always equal to  $ 0 $ .</p><p>This concept for any function  $ f $  was too hard for children. So teachers told them that  $ f $  can only be a polynomial of degree no more than  $ 3 $  in daily uses (i.e.,  $ f(x) = Ax^3+Bx^2+Cx+D $ ).</p><p>"Class is over! Don't forget to do your homework!" Here it is:  $ $  \sum_{i=1}^n \text{exlog}_f(i)  $ $ </p><p>Help children to do their homework. Since the value can be very big, you need to find the answer modulo  $ 2^{32}$$$.

## 输入格式

The only line contains five integers $ n $ , $ A $ , $ B $ , $ C $ , and $ D $ ( $ 1 \le n \le 3 \cdot 10^8 $ , $ 0 \le A,B,C,D \le 10^6 $ ).

## 输出格式

Print the answer modulo $ 2^{32} $ .

## 说明/提示

In the first sample:

 $ \text{exlog}_f(1) = 0 $

 $ \text{exlog}_f(2) = 2 $

 $ \text{exlog}_f(3) = 3 $

 $ \text{exlog}_f(4) = 2 + 2 = 4 $

 $ \text{exlog}_f(5) = 5 $

 $ \text{exlog}_f(6) = 2 + 3 = 5 $

 $ \text{exlog}_f(7) = 7 $

 $ \text{exlog}_f(8) = 2 + 2 + 2 = 6 $

 $ \text{exlog}_f(9) = 3 + 3 = 6 $

 $ \text{exlog}_f(10) = 2 + 5 = 7 $

 $ \text{exlog}_f(11) = 11 $

 $ \text{exlog}_f(12) = 2 + 2 + 3 = 7 $

 $  \sum_{i=1}^{12} \text{exlog}_f(i)=63  $

In the second sample:

 $ \text{exlog}_f(1) = 0 $

 $ \text{exlog}_f(2) = (1 \times 2^3 + 2 \times 2^2 + 3 \times 2 + 4) = 26 $

 $ \text{exlog}_f(3) = (1 \times 3^3 + 2 \times 3^2 + 3 \times 3 + 4) = 58 $

 $ \text{exlog}_f(4) = 2 \times \text{exlog}_f(2) = 52 $

 $  \sum_{i=1}^4 \text{exlog}_f(i)=0+26+58+52=136  $

## 样例 #1

### 输入

```
12 0 0 1 0

```

### 输出

```
63

```

## 样例 #2

### 输入

```
4 1 2 3 4

```

### 输出

```
136

```

