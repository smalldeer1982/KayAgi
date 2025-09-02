---
title: "Mark the Photographer"
layout: "post"
diff: 普及-
pid: CF1705A
tag: ['贪心']
---

# Mark the Photographer

## 题目描述

Mark is asked to take a group photo of $ 2n $ people. The $ i $ -th person has height $ h_i $ units.

To do so, he ordered these people into two rows, the front row and the back row, each consisting of $ n $ people. However, to ensure that everyone is seen properly, the $ j $ -th person of the back row must be at least $ x $ units taller than the $ j $ -th person of the front row for each $ j $ between $ 1 $ and $ n $ , inclusive.

Help Mark determine if this is possible.

## 输入格式

The first line contains one integer $ t $ ( $ 1\leq t\leq 100 $ ) — the number of test cases. Each test case consists of two lines.

The first line of each test case contains two positive integers $ n $ and $ x $ ( $ 1\leq n\leq 100 $ , $ 1\leq x\leq 10^3 $ ) — the number of people in each row and the minimum difference Mark wants.

The second line of each test case contains $ 2n $ positive integers $ h_1,h_2,\ldots,h_{2n} $ ( $ 1\leq h_i\leq 10^3 $ ) — the height of each person in units.

Note that the sum of $ n $ over all test cases is not bounded.

## 输出格式

For each test case, print a single line containing "YES" if Mark could arrange people satisfying his condition and "NO" otherwise.

You may print each letter in any case (for example, YES, Yes, yes, yEs will all be recognized as positive answers).

## 说明/提示

In the first test case, one possible order is to have the third, fifth, and sixth person on the back row and the second, first, and fourth on the front row. The heights of the people will look like this.

 Back $ 9 $  $ 12 $  $ 16 $ Front $ 3 $  $ 1 $  $ 10 $ It works because

- $ h_3-h_2 = 9-3 \geq 6 $ ,
- $ h_5-h_1 = 12-1\geq 6 $ , and
- $ h_6-h_4 = 16-10\geq 6 $ .

In the second test case, it can be shown there is no way to order people in a way that satisfies the condition.

In the third test case, the only way to arrange people to satisfy the condition is to have the first person on the back row and the second person on the front row.

## 样例 #1

### 输入

```
3
3 6
1 3 9 10 12 16
3 1
2 5 2 2 2 5
1 2
8 6
```

### 输出

```
YES
NO
YES
```

