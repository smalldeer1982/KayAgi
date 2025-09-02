---
title: "Marin and Photoshoot"
layout: "post"
diff: 入门
pid: CF1658A
tag: []
---

# Marin and Photoshoot

## 题目描述

Today, Marin is at a cosplay exhibition and is preparing for a group photoshoot!

For the group picture, the cosplayers form a horizontal line. A group picture is considered beautiful if for every contiguous segment of at least $ 2 $ cosplayers, the number of males does not exceed the number of females (obviously).

Currently, the line has $ n $ cosplayers which can be described by a binary string $ s $ . The $ i $ -th cosplayer is male if $ s_i = 0 $ and female if $ s_i = 1 $ . To ensure that the line is beautiful, you can invite some additional cosplayers (possibly zero) to join the line at any position. You can't remove any cosplayer from the line.

Marin wants to know the minimum number of cosplayers you need to invite so that the group picture of all the cosplayers is beautiful. She can't do this on her own, so she's asking you for help. Can you help her?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains a positive integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the number of cosplayers in the initial line.

The second line of each test case contains a binary string $ s $ of length $ n $ — describing the cosplayers already in line. Each character of the string is either 0 describing a male, or 1 describing a female.

Note that there is no limit on the sum of $ n $ .

## 输出格式

For each test case, print the minimum number of cosplayers you need to invite so that the group picture of all the cosplayers is beautiful.

## 说明/提示

In the first test case, for each pair of adjacent cosplayers, you can invite two female cosplayers to stand in between them. Then, $ 000 \rightarrow 0110110 $ .

In the third test case, you can invite one female cosplayer to stand next to the second cosplayer. Then, $ 010 \rightarrow 0110 $ .

## 样例 #1

### 输入

```
9
3
000
3
001
3
010
3
011
3
100
3
101
3
110
3
111
19
1010110000100000101
```

### 输出

```
4
2
1
0
2
0
0
0
17
```

