---
title: "Cyclic Hamming (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1896H1
tag: []
---

# Cyclic Hamming (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

In this statement, all strings are $ 0 $ -indexed.

For two strings $ a $ , $ b $ of the same length $ p $ , we define the following definitions:

- The hamming distance between $ a $ and $ b $ , denoted as $ h(a, b) $ , is defined as the number of positions $ i $ such that $ 0 \le i < p $ and $ a_i \ne b_i $ .
- $ b $ is a cyclic shift of $ a $ if there exists some $ 0 \leq k < p $ such that $ b_{(i+k) \bmod p} = a_i $ for all $ 0 \le i < p $ . Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

You are given two binary strings $ s $ and $ t $ of length $ 2^{k+1} $ each. Both strings may contain missing characters (denoted by the character '?'). Your task is to count the number of ways to replace the missing characters in both strings with the characters '0' or '1' such that:

- Each string $ s $ and $ t $ contains exactly $ 2^k $ occurrences of each character '0' and '1'
- $ h(s, c) \ge 2^k $ for all strings $ c $ that is a cyclic shift of $ t $ .

As the result can be very large, you should print the value modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains a single integer $ k $ ( $ 1 \le k \le 7 $ ).

The second line of the input contains string $ s $ of size $ 2^{k+1} $ , consisting of the characters '0', '1' and '?'.

The third line of the input contains string $ t $ of size $ 2^{k+1} $ , consisting of the characters '0', '1' and '?'.

It is guaranteed that both strings $ s $ and $ t $ contains no more than $ 2^k $ character '0' or '1'.

## 输出格式

Print a single integer — the answer to the problem modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, we can check that the condition $ h(s, c) \ge 2^k $ for all cyclic shift $ c $ of $ t $ is satisfied. In particular:

- for $ c = \mathtt{0101} $ , $ h(s, c) = h(\mathtt{0110}, \mathtt{0101}) = 2 \ge 2^1 $ ;
- for $ c = \mathtt{1010} $ , $ h(s, c) = h(\mathtt{0110}, \mathtt{1010}) = 2 \ge 2^1 $ .

In the second example, there exists a cycle shift $ c $ of $ t $ such that $ h(s, c) < 2^k $ (in particular, $ c = \mathtt{0011} $ , and $ h(s, c) = h(\mathtt{0011}, \mathtt{0011}) = 0 $ ).

In the third example, there are $ 2 $ possible ways to recover the missing characters:

- $ s = \mathtt{0101} $ , $ t = \mathtt{0110} $ ;
- $ s = \mathtt{0011} $ , $ t = \mathtt{0101} $ .

In the fourth example, there are $ 3 $ possible ways to recover the missing characters:

- $ s = \mathtt{00011110} $ , $ t = \mathtt{01010101} $ ;
- $ s = \mathtt{00011011} $ , $ t = \mathtt{01010101} $ ;
- $ s = \mathtt{00001111} $ , $ t = \mathtt{01010101} $ .

## 样例 #1

### 输入

```
1
0011
0101
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
0011
0110
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1
0??1
01??
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2
000?????
01010101
```

### 输出

```
3
```

## 样例 #5

### 输入

```
2
0???????
1???????
```

### 输出

```
68
```

## 样例 #6

### 输入

```
5
0101010101010101010101010101010101010101010101010101010101010101
????????????????????????????????????????????????????????????????
```

### 输出

```
935297567
```

