---
title: "Common Generator"
layout: "post"
diff: 提高+/省选-
pid: CF2029E
tag: ['数学', '数论', '标签475']
---

# Common Generator

## 题目描述

For two integers $ x $ and $ y $ ( $ x,y\ge 2 $ ), we will say that $ x $ is a generator of $ y $ if and only if $ x $ can be transformed to $ y $ by performing the following operation some number of times (possibly zero):

- Choose a divisor $ d $ ( $ d\ge 2 $ ) of $ x $ , then increase $ x $ by $ d $ .

For example,

- $ 3 $ is a generator of $ 8 $ since we can perform the following operations: $ 3 \xrightarrow{d = 3} 6 \xrightarrow{d = 2} 8 $ ;
- $ 4 $ is a generator of $ 10 $ since we can perform the following operations: $ 4 \xrightarrow{d = 4} 8 \xrightarrow{d = 2} 10 $ ;
- $ 5 $ is not a generator of $ 6 $ since we cannot transform $ 5 $ into $ 6 $ with the operation above.

Now, Kevin gives you an array $ a $ consisting of $ n $ pairwise distinct integers ( $ a_i\ge 2 $ ).

You have to find an integer $ x\ge 2 $ such that for each $ 1\le i\le n $ , $ x $ is a generator of $ a_i $ , or determine that such an integer does not exist.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 2\le a_i\le 4\cdot 10^5 $ ) — the elements in the array $ a $ . It is guaranteed that the elements are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer $ x $ — the integer you found. Print $ -1 $ if there does not exist a valid $ x $ .

If there are multiple answers, you may output any of them.

## 说明/提示

In the first test case, for $ x=2 $ :

- $ 2 $ is a generator of $ 8 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 4} 8 $ ;
- $ 2 $ is a generator of $ 9 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 3} 9 $ .
- $ 2 $ is a generator of $ 10 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 2} 8 \xrightarrow{d = 2} 10 $ .

In the second test case, it can be proven that it is impossible to find a common generator of the four integers.

## 样例 #1

### 输入

```
4
3
8 9 10
4
2 3 4 5
2
147 154
5
3 6 8 25 100000
```

### 输出

```
2
-1
7
3
```

