---
title: "Minimise Oneness"
layout: "post"
diff: 普及-
pid: CF2030B
tag: ['数学', '贪心']
---

# Minimise Oneness

## 题目描述

For an arbitrary binary string $ t $ $ ^{\text{∗}} $ , let $ f(t) $ be the number of non-empty subsequences $ ^{\text{†}} $ of $ t $ that contain only $ \mathtt{0} $ , and let $ g(t) $ be the number of non-empty subsequences of $ t $ that contain at least one $ \mathtt{1} $ .

Note that for $ f(t) $ and for $ g(t) $ , each subsequence is counted as many times as it appears in $ t $ . E.g., $ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ .

We define the oneness of the binary string $ t $ to be $ |f(t)-g(t)| $ , where for an arbitrary integer $ z $ , $ |z| $ represents the absolute value of $ z $ .

You are given a positive integer $ n $ . Find a binary string $ s $ of length $ n $ such that its oneness is as small as possible. If there are multiple strings, you can print any of them.

 $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements. For example, subsequences of $ \mathtt{1011101} $ are $ \mathtt{0} $ , $ \mathtt{1} $ , $ \mathtt{11111} $ , $ \mathtt{0111} $ , but not $ \mathtt{000} $ nor $ \mathtt{11100} $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of $ s $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, output $ s $ on a new line. If multiple answers exist, output any.

## 说明/提示

In the first test case, for the example output, $ f(t)=1 $ because there is one subsequence that contains only $ \mathtt{0} $ ( $ \mathtt{0} $ ), and $ g(t)=0 $ because there are no subsequences that contain at least one $ 1 $ . The oneness is $ |1-0|=1 $ . The output $ \mathtt{1} $ is correct as well because its oneness is $ |0-1|=1 $ .

For the example output of the second test case, $ f(t)=1 $ because there is one non-empty subsequence that contains only $ \mathtt{0} $ , and $ g(t)=2 $ because there are two non-empty subsequences that contain at least one $ \mathtt{1} $ ( $ \mathtt{01} $ and $ \mathtt{1} $ ). The oneness is thus $ |1-2|=1 $ . It can be shown that $ 1 $ is the minimum possible value of its oneness over all possible binary strings of size $ 2 $ .

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
0
01
010
```

