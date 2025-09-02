---
title: "Chess For Three"
layout: "post"
diff: 普及-
pid: CF1973A
tag: ['数学']
---

# Chess For Three

## 题目描述

Three friends gathered to play a few games of chess together.

In every game, two of them play against each other. The winner gets $ 2 $ points while the loser gets $ 0 $ , and in case of a draw, both players get $ 1 $ point each. Note that the same pair of players could have played any non-negative number of times (possibly zero). It is also possible that no games were played at all.

You've been told that their scores after all the games were played were $ p_1 $ , $ p_2 $ and $ p_3 $ . Additionally, it is guaranteed that $ p_1 \leq p_2 \leq p_3 $ holds.

Find the maximum number of draws that could have happened and print it. If there isn't any way to obtain $ p_1 $ , $ p_2 $ and $ p_3 $ as a result of a non-negative number of games between the three players, print $ -1 $ instead.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ p_1 $ , $ p_2 $ and $ p_3 $ ( $ 0 \leq p_1 \leq p_2 \leq p_3 \leq 30 $ ) — the scores of the three players, sorted non-decreasingly.

## 输出格式

For each testcase, print one number — the maximum possible number of draws that could've happened, or $ -1 $ if the scores aren't consistent with any valid set of games and results.

## 说明/提示

In the first example, no games were played at all, so no draws could occur either.

For the second example, exactly one game occurred between the second and the third player and it ended in draw, so the answer is $ 1 $ .

It's easy to see that there's no set of games achieving the scores in third example, so the answer for it is $ -1 $ .

## 样例 #1

### 输入

```
7
0 0 0
0 1 1
1 1 1
1 1 2
3 3 3
3 4 5
1 1 10
```

### 输出

```
0
1
-1
2
-1
6
2
```

