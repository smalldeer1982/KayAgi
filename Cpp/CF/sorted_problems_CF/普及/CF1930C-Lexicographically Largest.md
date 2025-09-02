---
title: "Lexicographically Largest"
layout: "post"
diff: 普及/提高-
pid: CF1930C
tag: ['贪心']
---

# Lexicographically Largest

## 题目描述

Stack has an array $ a $ of length $ n $ . He also has an empty set $ S $ . Note that $ S $ is not a multiset.

He will do the following three-step operation exactly $ n $ times:

1. Select an index $ i $ such that $ 1 \leq i \leq |a| $ .
2. Insert $ ^\dagger $ $ a_i + i $ into $ S $ .
3. Delete $ a_i $ from $ a $ . Note that the indices of all elements to the right of $ a_i $ will decrease by $ 1 $ .

Note that after $ n $ operations, $ a $ will be empty.

Stack will now construct a new array $ b $ which is $ S $ sorted in decreasing order. Formally, $ b $ is an array of size $ |S| $ where $ b_i $ is the $ i $ -th largest element of $ S $ for all $ 1 \leq i \leq |S| $ .

Find the lexicographically largest $ ^\ddagger $ $ b $ that Stack can make.

 $ ^\dagger $ A set can only contain unique elements. Inserting an element that is already present in a set will not change the elements of the set.

 $ ^\ddagger $ An array $ p $ is lexicographically larger than a sequence $ q $ if and only if one of the following holds:

- $ q $ is a prefix of $ p $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the array $ p $ has a larger element than the corresponding element in $ q $ .

Note that $ [3,1,4,1,5] $ is lexicographically larger than $ [3,1,3] $ , $ [\,] $ , and $ [3,1,4,1] $ but not $ [3,1,4,1,5,9] $ , $ [3,1,4,1,5] $ , and $ [4] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_{n} $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of array $ a $ .

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the lexicographically largest $ b $ .

## 说明/提示

In the first test case, select $ i=1 $ in the first operation, insert $ a_1 + 1 = 3 $ in $ S $ , and delete $ a_1 $ from $ a $ . After the first operation, $ a $ becomes $ a=[1] $ . In the second operation, we select $ i=1 $ again and insert $ a_1 + 1 = 2 $ in $ S $ . Thus $ S=\{2, 3\} $ , and $ b = [3, 2] $ .

Note that if you select $ i=2 $ in the first operation, and $ i=1 $ in the second operation, $ S=\{3\} $ as $ 3 $ will be inserted twice, resulting in $ b=[3] $ .

As $ [3,2] $ is lexicographically larger than $ [3] $ , we should select $ i=1 $ in the first operation.

In the second test case, in each operation, select the last element.

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8
```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6
```

