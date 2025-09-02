---
title: "GRE - GRE Words"
layout: "post"
diff: 省选/NOI-
pid: SP9941
tag: []
---

# GRE - GRE Words

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP9941/ed2c106f86e6f13dd6fa1b849ef2a65782a89f48.png)

## 输入格式

The first line contains an integer **T** (1 ≤ **T** ≤ 50), indicating the number of test cases.

Each test case contains several lines. The first line contains an integer **N** (1 ≤ **N** ≤ 2×10 $ ^{4} $ ), indicating the number of words.

Then **N** lines follows, each contains a string **S** $ _{i} $ and an integer **W** $ _{i} $ , representing the word and its importance. **S** $ _{i} $ contains only lowercase letters.

You can assume that the total length of all words will not exceeded 3×10 $ ^{5} $ .

## 输出格式

For each test case in the input, print one line: "Case #X: Y", where **X** is the test case number (starting with 1) and **Y** is the largest importance of the remaining sequence of words.

## 样例 #1

### 输入

```
1
5
a 1
ab 2
abb 3
baba 5
abbab 8
```

### 输出

```
Case #1: 14
```

