---
title: "Bro Thinks He's Him"
layout: "post"
diff: 难度0
pid: CF2065H
tag: []
---

# Bro Thinks He's Him

## 题目描述

Skibidus thinks he's Him! He proved it by solving this difficult task. Can you also prove yourself?

Given a binary string $ ^{\text{∗}} $ $ t $ , $ f(t) $ is defined as the minimum number of contiguous substrings, each consisting of identical characters, into which $ t $ can be partitioned. For example, $ f(\texttt{00110001}) = 4 $ because $ t $ can be partitioned as $ \texttt{[00][11][000][1]} $ where each bracketed segment consists of identical characters.

Skibidus gives you a binary string $ s $ and $ q $ queries. In each query, a single character of the string is flipped (i.e. $ \texttt{0} $ changes to $ \texttt{1} $ and $ \texttt{1} $ changes to $ \texttt{0} $ ); changes are saved after the query is processed. After each query, output the sum over all $ f(b) $ where $ b $ is a non-empty subsequence $ ^{\text{†}} $ of $ s $ , modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ A binary string consists of only characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A subsequence of a string is a string which can be obtained by removing several (possibly zero) characters from the original string.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a binary string $ s $ ( $ 1 \leq |s| \leq 2 \cdot 10^5 $ ).

The following line of each test case contains an integer $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of queries.

The following line contains $ q $ integers $ v_1, v_2, \ldots, v_q $ ( $ 1 \leq v_i \leq |s| $ ), denoting $ s_{v_i} $ is flipped for the $ i $ 'th query.

It is guaranteed that the sum of $ |s| $ and the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ q $ integers on a single line — the answer after each query modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, $ s $ becomes $ \texttt{001} $ after the first query. Let's calculate the answer for each subsequence:

- $ f(s_1) = f(\texttt{0}) = 1 $
- $ f(s_2) = f(\texttt{0}) = 1 $
- $ f(s_3) = f(\texttt{1}) = 1 $
- $ f(s_1 s_2) = f(\texttt{00}) = 1 $
- $ f(s_1 s_3) = f(\texttt{01}) = 2 $
- $ f(s_2 s_3) = f(\texttt{01}) = 2 $
- $ f(s_1 s_2 s_3) = f(\texttt{001}) = 2 $

The sum of these values is $ 10 $ , modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```

