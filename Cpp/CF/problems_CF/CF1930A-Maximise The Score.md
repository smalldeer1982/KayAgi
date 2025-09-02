---
title: "Maximise The Score"
layout: "post"
diff: 普及-
pid: CF1930A
tag: ['贪心']
---

# Maximise The Score

## 题目描述

There are $ 2n $ positive integers written on a whiteboard. Being bored, you decided to play a one-player game with the numbers on the whiteboard.

You start with a score of $ 0 $ . You will increase your score by performing the following move exactly $ n $ times:

- Choose two integers $ x $ and $ y $ that are written on the whiteboard.
- Add $ \min(x,y) $ to your score.
- Erase $ x $ and $ y $ from the whiteboard.

Note that after performing the move $ n $ times, there will be no more integers written on the whiteboard.

Find the maximum final score you can achieve if you optimally perform the $ n $ moves.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the number of integers written on the whiteboard is $ 2n $ .

The second line of each test case contains $ 2n $ integers $ a_1,a_2,\ldots,a_{2n} $ ( $ 1 \leq a_i \leq 10^7 $ ) — the numbers written on the whiteboard.

## 输出格式

For each test case, output the maximum final score that you can achieve.

## 说明/提示

In the first test case, you can only make one move. You select $ x=2 $ and $ y=3 $ , and your score will be $ \min(x,y)=2 $ .

In the second test case, the following is a sequence of moves that achieves a final score of $ 2 $ :

- In the first move, select $ x=1 $ and $ y=1 $ . Then, add $ \min(x,y)=1 $ to the score. After erasing $ x $ and $ y $ , the integers left on the whiteboard are $ 1 $ and $ 2 $ .
- In the second move, select $ x=1 $ and $ y=2 $ . Then, add $ \min(x,y)=1 $ to the score. After removing $ x $ and $ y $ , no more integers will be left on the whiteboard.

 It can be proved that it is not possible to get a score greater than $ 2 $ .In the third test case, you will perform the move thrice, adding $ 1 $ to the score each time.

## 样例 #1

### 输入

```
3
1
2 3
2
1 1 2 1
3
1 1 1 1 1 1
```

### 输出

```
2
2
3
```

