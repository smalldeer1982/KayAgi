---
title: "Binary Strings are Fun"
layout: "post"
diff: 普及/提高-
pid: CF1762C
tag: []
---

# Binary Strings are Fun

## 题目描述

A binary string $ ^\dagger $ $ b $ of odd length $ m $ is good if $ b_i $ is the median $ ^\ddagger $ of $ b[1,i]^\S $ for all odd indices $ i $ ( $ 1 \leq i \leq m $ ).

For a binary string $ a $ of length $ k $ , a binary string $ b $ of length $ 2k-1 $ is an extension of $ a $ if $ b_{2i-1}=a_i $ for all $ i $ such that $ 1 \leq i \leq k $ . For example, 1001011 and 1101001 are extensions of the string 1001. String $ x= $ 1011011 is not an extension of string $ y= $ 1001 because $ x_3 \neq y_2 $ . Note that there are $ 2^{k-1} $ different extensions of $ a $ .

You are given a binary string $ s $ of length $ n $ . Find the sum of the number of good extensions over all prefixes of $ s $ . In other words, find $ \sum_{i=1}^{n} f(s[1,i]) $ , where $ f(x) $ gives number of good extensions of string $ x $ . Since the answer can be quite large, you only need to find it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A binary string is a string whose elements are either $ \mathtt{0} $ or $ \mathtt{1} $ .

 $ ^\ddagger $ For a binary string $ a $ of length $ 2m-1 $ , the median of $ a $ is the (unique) element that occurs at least $ m $ times in $ a $ .

 $ ^\S $ $ a[l,r] $ denotes the string of length $ r-l+1 $ which is formed by the concatenation of $ a_l,a_{l+1},\ldots,a_r $ in that order.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), where $ n $ is the length of the binary string $ s $ .

The second line of each test case contains the binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first and second test cases, $ f(s[1,1])=1 $ .

In the third test case, the answer is $ f(s[1,1])+f(s[1,2])=1+2=3 $ .

In the fourth test case, the answer is $ f(s[1,1])+f(s[1,2])+f(s[1,3])=1+1+1=3 $ .

 $ f(\mathtt{11})=2 $ because two good extensions are possible: 101 and 111.

 $ f(\mathtt{01})=1 $ because only one good extension is possible: 011.

## 样例 #1

### 输入

```
6
1
1
1
0
2
11
3
010
9
101101111
37
1011011111011010000011011111111011111
```

### 输出

```
1
1
3
3
21
365
```

