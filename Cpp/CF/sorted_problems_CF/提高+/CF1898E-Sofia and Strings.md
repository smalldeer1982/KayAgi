---
title: "Sofia and Strings"
layout: "post"
diff: 提高+/省选-
pid: CF1898E
tag: []
---

# Sofia and Strings

## 题目描述

Sofia has a string $ s $ of length $ n $ , consisting only of lowercase English letters. She can perform operations of the following types with this string.

1. Select an index $ 1 \le i \le |s| $ and remove the character $ s_i $ from the string.
2. Select a pair of indices $ (l, r) $ ( $ 1 \le l \le r \le |s| $ ) and sort the substring $ s_{l} s_{l+1} \ldots s_r $ in alphabetical order.

 Here, $ |s| $ denotes the current length of $ s $ . In particular, $ |s| = n $ before the first operation. For example, if $ s = \mathtt{sofia} $ , then performing the operation of the first type with $ i=4 $ results in $ s $ becoming $ \mathtt{sofa} $ , and performing the operation of the second type with $ (l, r) = (2, 4) $ after that results in $ s $ becoming $ \mathtt{safo} $ .Sofia wants to obtain the string $ t $ of length $ m $ after performing zero or more operations on string $ s $ as described above. Please determine whether it is possible or not.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10\,000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1\leq m \leq n \leq 2\cdot 10^5 $ ) — the lengths of string $ s $ and $ t $ , respectively.

The second line of each test case contains the string $ s $ of length $ n $ , consisting only of lowercase English letters.

The third line of each test case contains the string $ t $ of length $ m $ , consisting only of lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if Sofia can obtain the string $ t $ from $ s $ using the operations above. Otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, Sofia can perform the following operation:

1. operation of the second type with $ l=1 $ and $ r=5 $ : string $ s $ becomes $ \mathtt{afios} $ after it.

In the second test case, Sofia can perform the following operations:

1. operation of the second type with $ l=1 $ and $ r=2 $ : string $ s $ becomes $ \mathtt{bca} $ after it;
2. operation of the first type with $ i=3 $ : string $ s $ becomes $ \mathtt{bc} $ after it.

In the third test case, it can be shown that it is impossible to obtain $ t $ from $ s $ using the provided operations.

## 样例 #1

### 输入

```
8
5 5
sofia
afios
3 2
cba
bc
5 1
sofia
e
15 7
anavolimilovana
aamanan
26 4
abcdefghijklmnopqrstuvwxyz
nope
26 4
zyxwvutsrqponmlkjihgfedcba
nope
7 3
apricot
cat
3 3
cba
acb
```

### 输出

```
YES
YES
NO
YES
NO
YES
NO
YES
```

