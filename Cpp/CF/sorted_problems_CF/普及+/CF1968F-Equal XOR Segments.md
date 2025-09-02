---
title: "Equal XOR Segments"
layout: "post"
diff: 普及+/提高
pid: CF1968F
tag: ['贪心', '位运算']
---

# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_1,\dots,a_n $ ( $ 0 \le a_i < 2^{30} $ ) — elements of the array.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) describing the query.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" if the subarray is interesting and "NO" otherwise.

You can output "Yes" and "No" in any case (for example, the strings "yES", "yes", and "Yes" will be recognized as correct answers).

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11
```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES
```

