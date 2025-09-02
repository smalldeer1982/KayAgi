---
title: "Ones and Twos"
layout: "post"
diff: 提高+/省选-
pid: CF1896D
tag: []
---

# Ones and Twos

## 题目描述

You are given a $ 1 $ -indexed array $ a $ of length $ n $ where each element is $ 1 $ or $ 2 $ .

Process $ q $ queries of the following two types:

- "1 s": check if there exists a subarray $ ^{\dagger} $ of $ a $ whose sum equals to $ s $ .
- "2 i v": change $ a_i $ to $ v $ .

 $ ^{\dagger} $ An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1\le n,q\le 10^5 $ ) — the length of array $ a $ and the number of queries.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ a_i $ is $ 1 $ or $ 2 $ ) — the elements of array $ a $ .

Each of the following $ q $ lines of each test case contains some integers. The first integer $ \mathrm{op} $ is either $ 1 $ or $ 2 $ .

- If $ \mathrm{op} $ is $ 1 $ , it is followed by one integer $ s $ ( $ 1 \leq s \leq 2n $ ).
- If $ \mathrm{op} $ is $ 2 $ , it is followed by two integers $ i $ and $ v $ ( $ 1 \leq i \leq n $ , $ v $ is $ 1 $ or $ 2 $ ).

It is guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases both do not exceed $ 10^5 $ .

## 输出格式

For each query with $ \mathrm{op}=1 $ , output "YES" in one line if there exists a subarray of $ a $ whose sum is equals to $ s $ , otherwise output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

Consider the first example:

- The answer for the first query is "YES" because $ a_1+a_2+a_3=2+1+2=5 $ .
- The answer for the second query is "YES" because $ a_1+a_2+a_3+a_4=2+1+2+1=6 $ .
- The answer for the third query is "NO" because we cannot find any subarray of $ a $ whose sum is $ 7 $ .
- After the fourth query, the array $ a $ becomes $ [2,1,2,2,2] $ .
- The answer for the fifth query is "YES" because $ a_2+a_3+a_4+a_5=1+2+2+2=7 $ .

## 样例 #1

### 输入

```
2
5 5
2 1 2 1 2
1 5
1 6
1 7
2 4 2
1 7
3 2
2 2 2
1 6
1 5
```

### 输出

```
YES
YES
NO
YES
YES
NO
```

