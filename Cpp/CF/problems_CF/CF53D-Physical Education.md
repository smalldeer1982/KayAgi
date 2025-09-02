---
title: "Physical Education"
layout: "post"
diff: 普及/提高-
pid: CF53D
tag: ['排序']
---

# Physical Education

## 题目描述

Vasya is a school PE teacher. Unlike other PE teachers, Vasya doesn't like it when the students stand in line according to their height. Instead, he demands that the children stand in the following order: $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the height of the $ i $ -th student in the line and $ n $ is the number of students in the line. The children find it hard to keep in mind this strange arrangement, and today they formed the line in the following order: $ b_{1},b_{2},...,b_{n} $ , which upset Vasya immensely. Now Vasya wants to rearrange the children so that the resulting order is like this: $ a_{1},a_{2},...,a_{n} $ . During each move Vasya can swap two people who stand next to each other in the line. Help Vasya, find the sequence of swaps leading to the arrangement Vasya needs. It is not required to minimize the number of moves.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ) which is the number of students. The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) which represent the height of the student occupying the $ i $ -th place must possess. The third line contains $ n $ space-separated integers $ b_{i} $ ( $ 1<=b_{i}<=10^{9} $ ) which represent the height of the student occupying the $ i $ -th place in the initial arrangement. It is possible that some students possess similar heights. It is guaranteed that it is possible to arrange the children in the required order, i.e. $ a $ and $ b $ coincide as multisets.

## 输出格式

In the first line print an integer $ k $ ( $ 0<=k<=10^{6} $ ) which is the number of moves. It is not required to minimize $ k $ but it must not exceed $ 10^{6} $ . Then print $ k $ lines each containing two space-separated integers. Line $ p_{i} $ , $ p_{i}+1 $ ( $ 1<=p_{i}<=n-1 $ ) means that Vasya should swap students occupying places $ p_{i} $ and $ p_{i+1} $ .

## 样例 #1

### 输入

```
4
1 2 3 2
3 2 1 2

```

### 输出

```
4
2 3
1 2
3 4
2 3

```

## 样例 #2

### 输入

```
2
1 100500
1 100500

```

### 输出

```
0

```

