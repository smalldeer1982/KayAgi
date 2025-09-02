---
title: "Slime Combining"
layout: "post"
diff: 入门
pid: CF618A
tag: []
---

# Slime Combining

## 题目描述

Your friend recently gave you some slimes for your birthday. You have $ n $ slimes all initially with value $ 1 $ .

You are going to play a game with these slimes. Initially, you put a single slime by itself in a row. Then, you will add the other $ n-1 $ slimes one by one. When you add a slime, you place it at the right of all already placed slimes. Then, while the last two slimes in the row have the same value $ v $ , you combine them together to create a slime with value $ v+1 $ .

You would like to see what the final state of the row is after you've added all $ n $ slimes. Please print the values of the slimes in the row from left to right.

## 输入格式

The first line of the input will contain a single integer, $ n $ ( $ 1<=n<=100000 $ ).

## 输出格式

Output a single line with $ k $ integers, where $ k $ is the number of slimes in the row after you've finished the procedure described in the problem statement. The $ i $ -th of these numbers should be the value of the $ i $ -th slime from the left.

## 说明/提示

In the first sample, we only have a single slime with value $ 1 $ . The final state of the board is just a single slime with value $ 1 $ .

In the second sample, we perform the following steps:

Initially we place a single slime in a row by itself. Thus, row is initially 1.

Then, we will add another slime. The row is now 1 1. Since two rightmost slimes have the same values, we should replace these slimes with one with value $ 2 $ . Thus, the final state of the board is 2.

In the third sample, after adding the first two slimes, our row is 2. After adding one more slime, the row becomes 2 1.

In the last sample, the steps look as follows:

1. 1
2. 2
3. 2 1
4. 3
5. 3 1
6. 3 2
7. 3 2 1
8. 4

## 样例 #1

### 输入

```
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3

```

### 输出

```
2 1

```

## 样例 #4

### 输入

```
8

```

### 输出

```
4

```

