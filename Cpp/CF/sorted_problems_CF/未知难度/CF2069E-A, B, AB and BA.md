---
title: "A, B, AB and BA"
layout: "post"
diff: 难度0
pid: CF2069E
tag: []
---

# A, B, AB and BA

## 题目描述

You are given a string $ s $ consisting of characters A and B.

Your task is to split it into blocks of length $ 1 $ and $ 2 $ in such a way that

- there are no more than $ a $ strings equal to "A";
- there are no more than $ b $ strings equal to "B";
- there are no more than $ ab $ strings "AB";
- there are no more than $ ba $ strings "BA";

Strings "AA" and "BB" are prohibited. Each character of the initial string $ s $ should belong to exactly one block.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Next, $ t $ independent cases follow.

The first line of each test case contains a single string $ s $ ( $ 1 \le |s| \le 5 \cdot 10^5 $ ) consisting only of characters A and/or B.

The second line of each test case contains four integers $ a $ , $ b $ , $ ab $ , and $ ba $ ( $ 0 \le a, b, ab, ba \le 5 \cdot 10^5 $ ) — the maximum allowed number of strings "A", "B", "AB", and "BA" correspondingly.

It's guaranteed that the total length of $ s $ doesn't exceed $ 5 \cdot 10^5 $ over all test cases.

## 输出格式

For each test case, print YES if it's possible to split string $ s $ . Otherwise, print NO.

## 说明/提示

In the third test case, all possible splits are: A|B|A, AB|A or A|BA. All of them have at least one "A".

In the fourth test case, one of the possible splits is the following: A|B|B|A|B|A|A|B.

In the fifth test case, one of the possible splits is the following: A|BA|B|BA|AB|BA|AB.

## 样例 #1

### 输入

```
7
A
0 0 10 10
B
0 1 0 0
ABA
0 0 1 1
ABBABAAB
5 5 0 0
ABABBAABBAAB
1 1 2 3
ABBBBAB
0 3 2 0
BAABBA
1 3 2 0
```

### 输出

```
NO
YES
NO
YES
YES
YES
NO
```

