---
title: "Nezzar and Binary String"
layout: "post"
diff: 提高+/省选-
pid: CF1477B
tag: []
---

# Nezzar and Binary String

## 题目描述

Nezzar has a binary string $ s $ of length $ n $ that he wants to share with his best friend, Nanako. Nanako will spend $ q $ days inspecting the binary string. At the same time, Nezzar wants to change the string $ s $ into string $ f $ during these $ q $ days, because it looks better.

It is known that Nanako loves consistency so much. On the $ i $ -th day, Nanako will inspect a segment of string $ s $ from position $ l_i $ to position $ r_i $ inclusive. If the segment contains both characters '0' and '1', Nanako becomes unhappy and throws away the string.

After this inspection, at the $ i $ -th night, Nezzar can secretly change strictly less than half of the characters in the segment from $ l_i $ to $ r_i $ inclusive, otherwise the change will be too obvious.

Now Nezzar wonders, if it is possible to avoid Nanako being unhappy and at the same time have the string become equal to the string $ f $ at the end of these $ q $ days and nights.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of test cases.

The first line of each test case contains two integers $ n,q $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le q \le 2 \cdot 10^5 $ ).

The second line of each test case contains a binary string $ s $ of length $ n $ .

The third line of each test case contains a binary string $ f $ of length $ n $ .

Then $ q $ lines follow, $ i $ -th of them contains two integers $ l_i,r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — bounds of the segment, that Nanako will inspect on the $ i $ -th day.

It is guaranteed that the sum of $ n $ for all test cases doesn't exceed $ 2 \cdot 10^5 $ , and the sum of $ q $ for all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print "YES" on the single line if it is possible to avoid Nanako being unhappy and have the string $ f $ at the end of $ q $ days and nights. Otherwise, print "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case, $ \underline{00000} \rightarrow \underline{000}11 \rightarrow 00111 $ is one of the possible sequences of string changes.

In the second test case, it can be shown that it is impossible to have the string $ f $ at the end.

## 样例 #1

### 输入

```
4
5 2
00000
00111
1 5
1 3
2 1
00
01
1 2
10 6
1111111111
0110001110
1 10
5 9
7 10
1 7
3 5
6 10
5 2
10000
11000
2 5
1 3
```

### 输出

```
YES
NO
YES
NO
```

