---
title: "Vasya and Robot"
layout: "post"
diff: 普及+/提高
pid: CF1073C
tag: ['二分', '枚举', '前缀和']
---

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 输入格式

The first line contains one integer number $ n~(1 \le n \le 2 \cdot 10^5) $ — the number of operations.

The second line contains the sequence of operations — a string of $ n $ characters. Each character is either U, D, L or R.

The third line contains two integers $ x, y~(-10^9 \le x, y \le 10^9) $ — the coordinates of the cell where the robot should end its path.

## 输出格式

Print one integer — the minimum possible length of subsegment that can be changed so the resulting sequence of operations moves the robot from $ (0, 0) $ to $ (x, y) $ . If this change is impossible, print $ -1 $ .

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
RULR
1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
UUU
100 100

```

### 输出

```
-1

```

