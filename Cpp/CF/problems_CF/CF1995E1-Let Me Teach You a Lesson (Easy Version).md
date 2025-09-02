---
title: "Let Me Teach You a Lesson (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1995E1
tag: []
---

# Let Me Teach You a Lesson (Easy Version)

## 题目描述

This is the easy version of a problem. The only difference between an easy and a hard version is the constraints on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

Arthur is giving a lesson to his famous $ 2 n $ knights. Like any other students, they're sitting at the desks in pairs, but out of habit in a circle. The knight $ 2 i - 1 $ is sitting at the desk with the knight $ 2 i $ .

Each knight has intelligence, which can be measured by an integer. Let's denote the intelligence of the $ i $ -th knight as $ a_i $ . Arthur wants the maximal difference in total intelligence over all pairs of desks to be as small as possible. More formally, he wants to minimize $ \max\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) - \min\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) $ .

However, the Code of Chivalry only allows swapping the opposite knights in the circle, i.e., Arthur can simultaneously perform $ a_i := a_{i + n} $ , $ a_{i + n} := a_i $ for any $ 1 \le i \le n $ . Arthur can make any number of such swaps. What is the best result he can achieve?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. It is followed by descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the number of desks.

The second line consists of $ 2n $ integers $ a_1, a_2, \ldots, a_{2 n} $ ( $ 1 \le a_i \le 10^9 $ ) — the intelligence values of the knights.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output a single line containing one integer — the minimal difference Arthur can achieve.

## 说明/提示

In the first test case, Arthur can swap the second and the fourth knights. Then the total intelligence at both desks will be $ 10 $ .

In the third test case, Arthur can make $ 0 $ operations, which will result in the total intelligence of $ 11 $ at each of the desks.

In the fourth test case, Arthur can swap knights with indices $ 2 $ and $ 5 $ and achieve the difference of $ 2 $ . It can be proven that he cannot improve his result any further.

## 样例 #1

### 输入

```
5
2
6 6 4 4
1
10 17
3
1 10 1 10 1 10
3
3 3 4 5 5 4
5
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
0
0
0
2
4
```

