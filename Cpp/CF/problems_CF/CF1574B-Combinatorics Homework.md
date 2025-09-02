---
title: "Combinatorics Homework"
layout: "post"
diff: 普及-
pid: CF1574B
tag: []
---

# Combinatorics Homework

## 题目描述

You are given four integer values $ a $ , $ b $ , $ c $ and $ m $ .

Check if there exists a string that contains:

- $ a $ letters 'A';
- $ b $ letters 'B';
- $ c $ letters 'C';
- no other letters;
- exactly $ m $ pairs of adjacent equal letters (exactly $ m $ such positions $ i $ that the $ i $ -th letter is equal to the $ (i+1) $ -th one).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

Each of the next $ t $ lines contains the description of the testcase — four integers $ a $ , $ b $ , $ c $ and $ m $ ( $ 1 \le a, b, c \le 10^8 $ ; $ 0 \le m \le 10^8 $ ).

## 输出格式

For each testcase print "YES" if there exists a string that satisfies all the requirements. Print "NO" if there are no such strings.

You may print every letter in any case you want (so, for example, the strings yEs, yes, Yes and YES will all be recognized as positive answer).

## 说明/提示

In the first testcase strings "ABCAB" or "BCABA" satisfy the requirements. There exist other possible strings.

In the second testcase there's no way to put adjacent equal letters if there's no letter that appears at least twice.

In the third testcase string "CABBCC" satisfies the requirements. There exist other possible strings.

## 样例 #1

### 输入

```
3
2 2 1 0
1 1 1 1
1 2 3 2
```

### 输出

```
YES
NO
YES
```

