---
title: "Turtle and Piggy Are Playing a Game 2"
layout: "post"
diff: 普及-
pid: CF2003B
tag: ['贪心']
---

# Turtle and Piggy Are Playing a Game 2

## 题目描述

Turtle and Piggy are playing a game on a sequence. They are given a sequence $ a_1, a_2, \ldots, a_n $ , and Turtle goes first. Turtle and Piggy alternate in turns (so, Turtle does the first turn, Piggy does the second, Turtle does the third, etc.).

The game goes as follows:

- Let the current length of the sequence be $ m $ . If $ m = 1 $ , the game ends.
- If the game does not end and it's Turtle's turn, then Turtle must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \max(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .
- If the game does not end and it's Piggy's turn, then Piggy must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \min(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .

Turtle wants to maximize the value of $ a_1 $ in the end, while Piggy wants to minimize the value of $ a_1 $ in the end. Find the value of $ a_1 $ in the end if both players play optimally.

You can refer to notes for further clarification.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the length of the sequence.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the elements of the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the value of $ a_1 $ in the end if both players play optimally.

## 说明/提示

In the first test case, initially $ a = [1, 2] $ . Turtle can only choose $ i = 1 $ . Then he will set $ a_1 $ to $ \max(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ becomes $ [2] $ . Then the length of the sequence becomes $ 1 $ , and the game will end. The value of $ a_1 $ is $ 2 $ , so you should output $ 2 $ .

In the second test case, one of the possible game processes is as follows:

- Initially $ a = [1, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [1, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 1 $ and remove $ a_2 $ . The sequence $ a $ will become $ [1] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 1 $ in the end.

In the fourth test case, one of the possible game processes is as follows:

- Initially $ a = [3, 1, 2, 2, 3] $ .
- Turtle can choose $ i = 4 $ . Then he will set $ a_4 $ to $ \max(a_4, a_5) = 3 $ and remove $ a_5 $ . The sequence $ a $ will become $ [3, 1, 2, 3] $ .
- Piggy can choose $ i = 3 $ . Then he will set $ a_3 $ to $ \min(a_3, a_4) = 2 $ and remove $ a_4 $ . The sequence $ a $ will become $ [3, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [3, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ will become $ [2] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 2 $ in the end.

## 样例 #1

### 输入

```
5
2
1 2
3
1 1 2
3
1 2 3
5
3 1 2 2 3
10
10 2 5 2 7 9 2 5 10 7
```

### 输出

```
2
1
2
2
7
```

