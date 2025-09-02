---
title: "Vika and Price Tags"
layout: "post"
diff: 普及+/提高
pid: CF1848C
tag: []
---

# Vika and Price Tags

## 题目描述

Vika came to her favorite cosmetics store "Golden Pear". She noticed that the prices of $ n $ items have changed since her last visit.

She decided to analyze how much the prices have changed and calculated the difference between the old and new prices for each of the $ n $ items.

Vika enjoyed calculating the price differences and decided to continue this process.

Let the old prices be represented as an array of non-negative integers $ a $ , and the new prices as an array of non-negative integers $ b $ . Both arrays have the same length $ n $ .

In one operation, Vika constructs a new array $ c $ according to the following principle: $ c_i = |a_i - b_i| $ . Then, array $ c $ renamed into array $ b $ , and array $ b $ renamed into array $ a $ at the same time, after which Vika repeats the operation with them.

For example, if $ a = [1, 2, 3, 4, 5, 6, 7] $ ; $ b = [7, 6, 5, 4, 3, 2, 1] $ , then $ c = [6, 4, 2, 0, 2, 4, 6] $ . Then, $ a = [7, 6, 5, 4, 3, 2, 1] $ ; $ b = [6, 4, 2, 0, 2, 4, 6] $ .

Vika decided to call a pair of arrays $ a $ , $ b $ dull if after some number of such operations all elements of array $ a $ become zeros.

Output "YES" if the original pair of arrays is dull, and "NO" otherwise.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of items whose prices have changed.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the old prices of the items.

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i \le 10^9 $ ) — the new prices of the items.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" if the pair of price arrays is dull, and "NO" otherwise.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first test case, the array $ a $ is initially zero.

In the second test case, after the first operation $ a = [1, 2, 3], b = [0, 0, 0] $ . After the second operation $ a = [0, 0, 0], b = [1, 2, 3] $ .

In the third test case, it can be shown that the array $ a $ will never become zero.

## 样例 #1

### 输入

```
9
4
0 0 0 0
1 2 3 4
3
1 2 3
1 2 3
2
1 2
2 1
6
100 23 53 11 56 32
1245 31 12 6 6 6
7
1 2 3 4 5 6 7
7 6 5 4 3 2 1
3
4 0 2
4 0 2
3
2 5 2
1 3 4
2
6 1
4 2
2
0 0
0 3
```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
```

