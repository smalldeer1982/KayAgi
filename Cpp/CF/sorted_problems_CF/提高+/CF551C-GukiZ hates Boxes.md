---
title: "GukiZ hates Boxes"
layout: "post"
diff: 提高+/省选-
pid: CF551C
tag: []
---

# GukiZ hates Boxes

## 题目描述

Professor GukiZ is concerned about making his way to school, because massive piles of boxes are blocking his way.

In total there are $ n $ piles of boxes, arranged in a line, from left to right, $ i $ -th pile ( $ 1<=i<=n $ ) containing $ a_{i} $ boxes. Luckily, $ m $ students are willing to help GukiZ by removing all the boxes from his way. Students are working simultaneously. At time $ 0 $ , all students are located left of the first pile. It takes one second for every student to move from this position to the first pile, and after that, every student must start performing sequence of two possible operations, each taking one second to complete. Possible operations are:

1. If $ i≠n $ , move from pile $ i $ to pile $ i+1 $ ;
2. If pile located at the position of student is not empty, remove one box from it.

GukiZ's students aren't smart at all, so they need you to tell them how to remove boxes before professor comes (he is very impatient man, and doesn't want to wait). They ask you to calculate minumum time $ t $ in seconds for which they can remove all the boxes from GukiZ's way. Note that students can be positioned in any manner after $ t $ seconds, but all the boxes must be removed.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ), the number of piles of boxes and the number of GukiZ's students.

The second line contains $ n $ integers $ a_{1},a_{2},...\ a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ) where $ a_{i} $ represents the number of boxes on $ i $ -th pile. It's guaranteed that at least one pile of is non-empty.

## 输出格式

In a single line, print one number, minimum time needed to remove all the boxes in seconds.

## 说明/提示

First sample: Student will first move to the first pile ( $ 1 $ second), then remove box from first pile ( $ 1 $ second), then move to the second pile ( $ 1 $ second) and finally remove the box from second pile ( $ 1 $ second).

Second sample: One of optimal solutions is to send one student to remove a box from the first pile and a box from the third pile, and send another student to remove a box from the third pile. Overall, $ 5 $ seconds.

Third sample: With a lot of available students, send three of them to remove boxes from the first pile, four of them to remove boxes from the second pile, five of them to remove boxes from the third pile, and four of them to remove boxes from the fourth pile. Process will be over in $ 5 $ seconds, when removing the boxes from the last pile is finished.

## 样例 #1

### 输入

```
2 1
1 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 2
1 0 2

```

### 输出

```
5

```

## 样例 #3

### 输入

```
4 100
3 4 5 4

```

### 输出

```
5

```

