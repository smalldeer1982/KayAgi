---
title: "Add Odd or Subtract Even"
layout: "post"
diff: 普及-
pid: CF1311A
tag: []
---

# Add Odd or Subtract Even

## 题目描述

You are given two positive integers $ a $ and $ b $ .

In one move, you can change $ a $ in the following way:

- Choose any positive odd integer $ x $ ( $ x > 0 $ ) and replace $ a $ with $ a+x $ ;
- choose any positive even integer $ y $ ( $ y > 0 $ ) and replace $ a $ with $ a-y $ .

You can perform as many such operations as you want. You can choose the same numbers $ x $ and $ y $ in different moves.

Your task is to find the minimum number of moves required to obtain $ b $ from $ a $ . It is guaranteed that you can always obtain $ b $ from $ a $ .

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then $ t $ test cases follow. Each test case is given as two space-separated integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^9 $ ).

## 输出格式

For each test case, print the answer — the minimum number of moves required to obtain $ b $ from $ a $ if you can perform any number of moves described in the problem statement. It is guaranteed that you can always obtain $ b $ from $ a $ .

## 说明/提示

In the first test case, you can just add $ 1 $ .

In the second test case, you don't need to do anything.

In the third test case, you can add $ 1 $ two times.

In the fourth test case, you can subtract $ 4 $ and add $ 1 $ .

In the fifth test case, you can just subtract $ 6 $ .

## 样例 #1

### 输入

```
5
2 3
10 10
2 4
7 4
9 3
```

### 输出

```
1
0
2
2
1
```

