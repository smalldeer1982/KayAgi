---
title: "ABBB"
layout: "post"
diff: 普及/提高-
pid: CF1428C
tag: []
---

# ABBB

## 题目描述

Zookeeper is playing a game. In this game, Zookeeper must use bombs to bomb a string that consists of letters 'A' and 'B'. He can use bombs to bomb a substring which is either "AB" or "BB". When he bombs such a substring, the substring gets deleted from the string and the remaining parts of the string get concatenated.

For example, Zookeeper can use two such operations: AABABBA $ \to $ AABBA $ \to $ AAA.

Zookeeper wonders what the shortest string he can make is. Can you help him find the length of the shortest string?

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 20000) $ — the number of test cases. The description of the test cases follows.

Each of the next $ t $ lines contains a single test case each, consisting of a non-empty string $ s $ : the string that Zookeeper needs to bomb. It is guaranteed that all symbols of $ s $ are either 'A' or 'B'.

It is guaranteed that the sum of $ |s| $ (length of $ s $ ) among all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer: the length of the shortest string that Zookeeper can make.

## 说明/提示

For the first test case, you can't make any moves, so the answer is $ 3 $ .

For the second test case, one optimal sequence of moves is BABA $ \to $ BA. So, the answer is $ 2 $ .

For the third test case, one optimal sequence of moves is AABBBABBBB $ \to $ AABBBABB $ \to $ AABBBB $ \to $ ABBB $ \to $ AB $ \to $ (empty string). So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
AAA
BABA
AABBBABBBB
```

### 输出

```
3
2
0
```

