---
title: "Problemsolving Log"
layout: "post"
diff: 入门
pid: CF1914A
tag: []
---

# Problemsolving Log

## 题目描述

Monocarp is participating in a programming contest, which features $ 26 $ problems, named from 'A' to 'Z'. The problems are sorted by difficulty. Moreover, it's known that Monocarp can solve problem 'A' in $ 1 $ minute, problem 'B' in $ 2 $ minutes, ..., problem 'Z' in $ 26 $ minutes.

After the contest, you discovered his contest log — a string, consisting of uppercase Latin letters, such that the $ i $ -th letter tells which problem Monocarp was solving during the $ i $ -th minute of the contest. If Monocarp had spent enough time in total on a problem to solve it, he solved it. Note that Monocarp could have been thinking about a problem after solving it.

Given Monocarp's contest log, calculate the number of problems he solved during the contest.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 1 \le n \le 500 $ ) — the duration of the contest, in minutes.

The second line contains a string of length exactly $ n $ , consisting only of uppercase Latin letters, — Monocarp's contest log.

## 输出格式

For each testcase, print a single integer — the number of problems Monocarp solved during the contest.

## 样例 #1

### 输入

```
3
6
ACBCBC
7
AAAAFPC
22
FEADBBDFFEDFFFDHHHADCC
```

### 输出

```
3
1
4
```

