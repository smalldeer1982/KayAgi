---
title: "Remove the Ends"
layout: "post"
diff: 普及-
pid: CF2064C
tag: []
---

# Remove the Ends

## 题目描述

You have an array $ a $ of length $ n $ consisting of non-zero integers. Initially, you have $ 0 $ coins, and you will do the following until $ a $ is empty:

- Let $ m $ be the current size of $ a $ . Select an integer $ i $ where $ 1 \le i \le m $ , gain $ |a_i| $ $ ^{\text{∗}} $ coins, and then: 
  - if $ a_i < 0 $ , then replace $ a $ with $ [a_1,a_2,\ldots,a_{i - 1}] $ (that is, delete the suffix beginning with $ a_i $ );
  - otherwise, replace $ a $ with $ [a_{i + 1},a_{i + 2},\ldots,a_m] $ (that is, delete the prefix ending with $ a_i $ ).

Find the maximum number of coins you can have at the end of the process.

 $ ^{\text{∗}} $ Here $ |a_i| $ represents the absolute value of $ a_i $ : it equals $ a_i $ when $ a_i > 0 $ and $ -a_i $ when $ a_i < 0 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each testcase contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ -10^9 \le a_i \le 10^9 $ , $ a_i \ne 0 $ ).

The sum of $ n $ across all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum number of coins you can have at the end of the process.

## 说明/提示

An example of how to get $ 23 $ coins in the first testcase is as follows:

- $ a = [3, 1, 4, -1, -5, \color{red}{-9}] \xrightarrow{i = 6} a = [3, 1, 4, -1, -5]  $ , and get $ 9 $ coins.
- $ a = [\color{red}{3}, 1, 4, -1, -5] \xrightarrow{i = 1} a = [1, 4, -1, -5]  $ , and get $ 3 $ coins.
- $ a = [\color{red}{1}, 4, -1, -5] \xrightarrow{i = 1} a = [4, -1, -5]  $ , and get $ 1 $ coin.
- $ a = [4, -1, \color{red}{-5}] \xrightarrow{i = 3} a = [4, -1]  $ , and get $ 5 $ coins.
- $ a = [4, \color{red}{-1}] \xrightarrow{i = 2} a = [4]  $ , and get $ 1 $ coin.
- $ a = [\color{red}{4}] \xrightarrow{i = 1} a = []  $ , and get $ 4 $ coins.

 After all the operations, you have $ 23 $ coins.An example of how to get $ 40 $ coins in the second testcase is as follows:

- $ a = [-10, -3, -17, \color{red}{1}, 19, 20] \xrightarrow{i = 4} a = [19, 20]  $ , and get $ 1 $ coin.
- $ a = [\color{red}{19}, 20] \xrightarrow{i = 1} a = [20]  $ , and get $ 19 $ coins.
- $ a = [\color{red}{20}] \xrightarrow{i = 1} a = []  $ , and get $ 20 $ coins.

 After all the operations, you have $ 40 $ coins.

## 样例 #1

### 输入

```
3
6
3 1 4 -1 -5 -9
6
-10 -3 -17 1 19 20
1
1
```

### 输出

```
23
40
1
```

