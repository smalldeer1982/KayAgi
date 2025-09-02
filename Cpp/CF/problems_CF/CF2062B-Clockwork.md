---
title: "Clockwork"
layout: "post"
diff: 普及-
pid: CF2062B
tag: []
---

# Clockwork

## 题目描述

You have a sequence of $ n $ time clocks arranged in a line, where the initial time on the $ i $ -th clock is $ a_i $ . In each second, the following happens in order:

- Each clock's time decreases by $ 1 $ . If any clock's time reaches $ 0 $ , you lose immediately.
- You can choose to move to an adjacent clock or stay at the clock you are currently on.
- You can reset the time of the clock you are on back to its initial value $ a_i $ .

Note that the above events happen in order. If the time of a clock reaches $ 0 $ in a certain second, even if you can move to this clock and reset its time during that second, you will still lose.

You can start from any clock. Determine if it is possible to continue this process indefinitely without losing.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 2 \leq n \leq 5 \cdot 10^5 $ ) — the number of time clocks.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the initial times set on the clocks.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5\cdot 10^5 $ .

## 输出格式

For each test case, print "YES" (without quotes) if it is possible to continue this process indefinitely, or "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first test case, you can move back and forth between the two clocks, resetting them repeatedly.

In the third test case, assuming that you start from clock $ 1 $ and follow the strategy below:

Initially, $ a=[4,10,5] $ .

1. $ a $ becomes $ [3, 9, 4] $ . You move to clock $ 2 $ and reset its time, resulting in $ a=[3, 10, 4] $ .
2. $ a $ becomes $ [2, 9, 3] $ . You move to clock $ 3 $ and reset its time, resulting in $ a=[2, 9, 5] $ .
3. $ a $ becomes $ [1, 8, 4] $ . You move to clock $ 2 $ and reset its time, resulting in $ a=[1, 10, 4] $ .
4. $ a $ becomes $ [0, 9, 3] $ . You move to clock $ 1 $ , but you lose because $ a_1 $ reaches $ 0 $ .

It can be proven that no other strategy allows you to continue this process indefinitely.

## 样例 #1

### 输入

```
5
2
4 10
2
2 2
3
4 10 5
3
5 3 5
5
12 13 25 17 30
```

### 输出

```
YES
NO
NO
YES
YES
```

