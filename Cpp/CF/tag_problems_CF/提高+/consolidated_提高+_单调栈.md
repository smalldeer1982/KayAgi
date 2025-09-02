---
title: "Set To Max (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1904D2
tag: ['贪心', '单调栈']
---

# Set To Max (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the arrays.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if you can make $ a $ into $ b $ using any number of operations, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2
```

### 输出

```
YES
NO
YES
NO
NO
```



---

---
title: "Eliminating Balls With Merging (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1998E1
tag: ['线段树', '分治', 'ST 表', '单调栈']
---

# Eliminating Balls With Merging (Easy Version)

## 题目描述

_喝水_ 

—— 孙武，程序员健康指南

**这是问题的简单版本。本题中 $x=n$ 。你必须同时解决这两个版本的问题，才能  hack**。

给你两个整数 $n$ 和 $x$ ( $x=n$ )。有 $n$ 个球排成一排，从左到右编号为 $1$ 到 $n$ 。最初，在第 $i$ 个球上写着一个值 $a_i$。

对于从 $1$ 到 $n$ 的每个整数 $i$ ，我们定义一个函数 $f(i)$ 如下：

- 假设有一个集合 $S = \{1, 2, \ldots, i\}$ 。
    
- 在每次运算中，必须从 $S$ 中选择一个整数 $l$ ( $1 \leq l < i$ )，使得 $l$ 不是 $S$ 的最大元素。假设 $r$ 是 $S$ 中大于 $l$ 的最小元素。
    
    - 如果是 $a_l > a_r$ ，则令 $a_l = a_l + a_r$ 并从 $S$ 中删除 $r$ 。
    - 如果是 $a_l < a_r$ ，则令 $a_r = a_l + a_r$ ，并从 $S$ 删除 $l$ 。
    - 如果是 $a_l = a_r$ ，则从 $S$ 中选择删除整数 $l$ 或 $r$ ：
        - 如果选择从 $S$ 中删除 $l$ ，则设置 $a_r = a_l + a_r$ 并从 $S$ 中删除 $l$ 。
        - 如果您选择从 $S$ 中删除 $r$ ，则需要设置 $a_l = a_l + a_r$ ，并从 $S$ 中删除 $r$ 。
    
- $f(i)$ 表示这样的整数 $j$ ( $1 \le j \le i$ )的个数，即执行上述操作恰好 $i - 1$ 次后可以得到 $S = \{j\}$ 。

对 $x$ 到 $n$ 的每个整数 $i$ 都需要求出 $f(i)$ 。

## 输入格式

第一行包含 $t$ ( $1 \leq t \leq 10^4$ ) ，表示测试用例数。

每个测试用例的第一行包含两个整数 $n$ 和 $x$ ( $1 \leq n \leq 2 \cdot 10^5; x = n$ )--球的个数和最小索引 $i$ ，您需要找到该索引的 $f(i)$ 。

每个测试用例的第二行包含 $a_1, a_2, \ldots, a_n$ ( $1 \leq a_i \leq 10^9$ ) - 写在每个球上的初始数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，在一行中输出 $n-x+1$ 个空格分隔的整数，其中第 $j$ 个整数表示 $f(x+j-1)$ 。

**样例解释**

在第一个测试用例中，要计算 $f(5)$ 。可以看出，经过 $4$ 次运算后， $S$ 可以包含 $2$ 、 $3$ 或 $4$ 。下面是生成 $S = \{4\}$ 所需的运算。

- 最初是 $S = \{1, 2, 3, 4, 5\}$ 和 $a = [1, 2, 3, 2, 1]$ 。
- 选择 $l = 1$ 。自然是 $r = 2$ 。由于 $a_1< a_2$ ，我们设置 $a_2 = 1 + 2$ ，并从 $S$ 中删除 $1$ 。现在， $S = \{2, 3, 4, 5\}$ 和 $a = [1, 3, 3, 2, 1]$ 。
- 选择 $l = 4$ 。自然是 $r = 5$ 。由于 $a_4> a_5$ ，我们设置 $a_4 = 2 + 1$ ，并从 $S$ 中删除 $5$ 。现在， $S = \{2, 3, 4\}$ 和 $a = [1, 3, 3, 3, 1]$ 。
- 选择 $l = 3$ 。自然是 $r = 4$ 。由于 $a_3 = a_4$ ，我们可以选择删除 $3$ 或 $4$ 。既然要保留 $4$ ，那么就删除 $3$ 。因此，设置 $a_4 = 3 + 3$ 并从 $S$ 中删除 $3$ 。现在， $S = \{2, 4\}$ 和 $a = [1, 3, 3, 6, 1]$ 。
- 选择 $l = 2$ 。自然是 $r = 4$ 。由于 $a_2< a_4$ ，我们设置 $a_4 = 3 + 6$ ，并从 $S$ 中删除 $2$ 。最后是 $S = \{4\}$ 和 $a = [1, 3, 3, 9, 1]$ 。

在第二个测试案例中，要求计算 $f(7)$ 。可以证明，经过 $6$ 次运算后， $S$ 可以包含 $2$ 、 $4$ 、 $6$ 或 $7$ 。

## 样例 #1

### 输入

```
3
5 5
1 2 3 2 1
7 7
4 5 1 2 1 4 5
11 11
1 2 3 1 1 9 3 2 4 1 3
```

### 输出

```
3
4
4
```



---

---
title: "Cosmic Rays"
layout: "post"
diff: 提高+/省选-
pid: CF2002E
tag: ['动态规划 DP', '单调栈']
---

# Cosmic Rays

## 题目描述

Given an array of integers $ s_1, s_2, \ldots, s_l $ , every second, cosmic rays will cause all $ s_i $ such that $ i=1 $ or $ s_i\neq s_{i-1} $ to be deleted simultaneously, and the remaining parts will be concatenated together in order to form the new array $ s_1, s_2, \ldots, s_{l'} $ .

Define the strength of an array as the number of seconds it takes to become empty.

You are given an array of integers compressed in the form of $ n $ pairs that describe the array left to right. Each pair $ (a_i,b_i) $ represents $ a_i $ copies of $ b_i $ , i.e. $ \underbrace{b_i,b_i,\cdots,b_i}_{a_i\textrm{ times}} $ .

For each $ i=1,2,\dots,n $ , please find the strength of the sequence described by the first $ i $ pairs.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le3\cdot10^5 $ ) — the length of sequence $ a $ .

The next $ n $ lines contain two integers each $ a_i $ , $ b_i $ ( $ 1\le a_i\le10^9,0\le b_i\le n $ ) — the pairs which describe the sequence.

It is guaranteed that the sum of all $ n $ does not exceed $ 3\cdot10^5 $ .

It is guaranteed that for all $ 1\le i<n $ , $ b_i\neq b_{i+1} $ holds.

## 输出格式

For each test case, print one line containing $ n $ integers — the answer for each prefix of pairs.

## 说明/提示

In the first test case, for the prefix of length $ 4 $ , the changes will be $ [0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[] $ , so the array becomes empty after $ 5 $ seconds.

In the second test case, for the prefix of length $ 4 $ , the changes will be $ [6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[] $ , so the array becomes empty after $ 7 $ seconds.

## 样例 #1

### 输入

```
4
4
2 0
1 1
3 0
5 1
6
4 6
1 3
4 6
4 0
7 6
6 3
7
9 0
7 1
5 0
7 1
9 0
1 1
2 0
10
10 7
4 9
2 2
7 9
2 8
8 5
11 7
15 5
12 7
4 0
```

### 输出

```
2 2 4 5 
4 4 7 7 10 10 
9 9 9 9 9 9 10 
10 10 10 10 10 10 12 15 15 15
```



---

