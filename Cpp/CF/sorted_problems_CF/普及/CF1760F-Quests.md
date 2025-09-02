---
title: "Quests"
layout: "post"
diff: 普及/提高-
pid: CF1760F
tag: []
---

# Quests

## 题目描述

There are $ n $ quests. If you complete the $ i $ -th quest, you will gain $ a_i $ coins. You can only complete at most one quest per day. However, once you complete a quest, you cannot do the same quest again for $ k $ days. (For example, if $ k=2 $ and you do quest $ 1 $ on day $ 1 $ , then you cannot do it on day $ 2 $ or $ 3 $ , but you can do it again on day $ 4 $ .)

You are given two integers $ c $ and $ d $ . Find the maximum value of $ k $ such that you can gain at least $ c $ coins over $ d $ days. If no such $ k $ exists, output Impossible. If $ k $ can be arbitrarily large, output Infinity.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n,c,d $ ( $ 2 \leq n \leq 2\cdot10^5 $ ; $ 1 \leq c \leq 10^{16} $ ; $ 1 \leq d \leq 2\cdot10^5 $ ) — the number of quests, the number of coins you need, and the number of days.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the rewards for the quests.

The sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ , and the sum of $ d $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, output one of the following.

- If no such $ k $ exists, output Impossible.
- If $ k $ can be arbitrarily large, output Infinity.
- Otherwise, output a single integer — the maximum value of $ k $ such that you can gain at least $ c $ coins over $ d $ days.

 Please note, the checker is case-sensitive, and you should output strings exactly as they are given.

## 说明/提示

In the first test case, one way to earn $ 5 $ coins over $ 4 $ days with $ k=2 $ is as follows:

- Day 1: do quest 2, and earn $ 2 $ coins.
- Day 2: do quest 1, and earn $ 1 $ coin.
- Day 3: do nothing.
- Day 4: do quest 2, and earn $ 2 $ coins.

 In total, we earned $ 2+1+2=5 $ coins.In the second test case, we can make over $ 20 $ coins on the first day itself by doing the first quest to earn $ 100 $ coins, so the value of $ k $ can be arbitrarily large, since we never need to do another quest.

In the third test case, no matter what we do, we can't earn $ 100 $ coins over $ 3 $ days.

## 样例 #1

### 输入

```
6
2 5 4
1 2
2 20 10
100 10
3 100 3
7 2 6
4 20 3
4 5 6 7
4 100000000000 2022
8217734 927368 26389746 627896974
2 20 4
5 1
```

### 输出

```
2
Infinity
Impossible
1
12
0
```

