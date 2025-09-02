---
title: "Find Divisible"
layout: "post"
diff: 入门
pid: CF1096A
tag: []
---

# Find Divisible

## 题目描述

You are given a range of positive integers from $ l $ to $ r $ .

Find such a pair of integers $ (x, y) $ that $ l \le x, y \le r $ , $ x \ne y $ and $ x $ divides $ y $ .

If there are multiple answers, print any of them.

You are also asked to answer $ T $ independent queries.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 1000 $ ) — the number of queries.

Each of the next $ T $ lines contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 998244353 $ ) — inclusive borders of the range.

It is guaranteed that testset only includes queries, which have at least one suitable pair.

## 输出格式

Print $ T $ lines, each line should contain the answer — two integers $ x $ and $ y $ such that $ l \le x, y \le r $ , $ x \ne y $ and $ x $ divides $ y $ . The answer in the $ i $ -th line should correspond to the $ i $ -th query from the input.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
1 10
3 14
1 10

```

### 输出

```
1 7
3 9
5 10

```

