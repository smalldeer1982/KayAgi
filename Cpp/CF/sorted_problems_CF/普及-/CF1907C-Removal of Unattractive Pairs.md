---
title: "Removal of Unattractive Pairs"
layout: "post"
diff: 普及-
pid: CF1907C
tag: []
---

# Removal of Unattractive Pairs

## 题目描述

Vlad found a string $ s $ consisting of $ n $ lowercase Latin letters, and he wants to make it as short as possible.

To do this, he can remove any pair of adjacent characters from $ s $ any number of times, provided they are different. For example, if $ s $ =racoon, then by removing one pair of characters he can obtain the strings coon, roon, raon, and raco, but he cannot obtain racn (because the removed letters were the same) or rcon (because the removed letters were not adjacent).

What is the minimum length Vlad can achieve by applying any number of deletions?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string $ s $ .

The second line of each test case contains the string $ s $ consisting of $ n $ lowercase Latin letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number—the minimum length of the string $ s $ , after removing pairs of adjacent characters with different values.

## 说明/提示

In the first test case of the example, you need to act as follows: "aabc" $ \rightarrow $ "ac" $ \rightarrow $ "". Note that with a different order of deletions, the string will not become empty.

## 样例 #1

### 输入

```
10
4
aabc
5
abaca
10
avbvvcvvvd
7
abcdefg
5
dabbb
8
aacebeaa
7
bbbbacc
6
dacfcc
6
fdfcdc
9
dbdcfbbdc
```

### 输出

```
0
1
2
1
1
0
1
0
0
1
```

