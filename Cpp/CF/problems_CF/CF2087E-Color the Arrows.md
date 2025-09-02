---
title: "Color the Arrows"
layout: "post"
diff: 难度0
pid: CF2087E
tag: []
---

# Color the Arrows

## 题目描述

There are $ n $ arrows drawn in a row on a strip of paper, numbered from $ 1 $ to $ n $ . Each arrow points either to the left or to the right. Initially, all arrows are painted blue.

In one operation, you can repaint a blue arrow into red. For the first operation, you can choose any arrow. For each subsequent operation, you are only allowed to choose such an arrow that the arrow repainted on the previous operation points in its direction. That is, if the arrow repainted in the previous operation is a left arrow, then, for the current operation, you have to choose an arrow at a smaller index than the previous one. Similarly, if the previous arrow was a right arrow, the current one has to be at a greater index than it. Note that the arrows don't have to be adjacent.

Each arrow has an integer reward for repainting it into red (which can be negative, positive, or zero).

The final score is the sum of the rewards for the repainted arrows. What is the maximum score that can be achieved if you are allowed to perform any number of operations (including zero)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

In the first line of each test case, there is a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the number of arrows.

In the second line, there is a string consisting of $ n $ characters '&lt;' and/or '&gt;' (ASCII codes 60 and 62, respectively).

In the third line, there are $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ -10^9 \le c_i \le 10^9 $ ) — the reward for repainting each arrow.

An additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the maximum score that can be achieved if you are allowed to perform any number of operations (including zero).

## 说明/提示

In the first test case, you can first repaint the arrow at index $ 2 $ . This arrow points to the right, so in the next operation, you have to choose an arrow to the right of it. Let's repaint the arrow at index $ 3 $ . This arrow also points to the right, so no more arrows can be repainted. The answer is $ c_2 + c_3 = 4 + 6 = 10 $ .

In the second test case, you can repaint arrows $ 3 $ , then $ 1 $ .

In the third test case, it is most optimal to not repaint any arrows. This will yield an answer of $ 0 $ , while repainting at least one arrow would lead to a negative answer.

In the fourth test case, you can repaint the arrows in the following order: $ 3, 7, 1, 5 $ .

In the fifth test case, you can repaint the arrows in the following order: $ 4, 3, 2, 1, 5 $ .

## 样例 #1

### 输入

```
5
3
&lt;&gt;&gt;
5 4 6
5
&lt;&gt;&lt;&gt;&gt;
5 -2 4 -3 7
2
&gt;&gt;
-1 -2
8
&gt;&gt;&gt;&gt;&lt;&lt;&lt;&lt;
1 -1 1 -1 1 -1 1 -1
5
&gt;&lt;&lt;&lt;&gt;
-1 100 100 100 100
```

### 输出

```
10
9
0
4
399
```

